#![feature(const_vec_string_slice, int_roundings)]
mod periodic_timer;
mod renderer;

use std::{
    borrow::Borrow,
    collections::{HashMap, VecDeque},
    env::args,
    ffi::c_float,
    fs::{self, File},
    io::{Cursor, Write},
    num::NonZeroU32,
    ops::Range,
    panic::set_hook,
    path::{Path, PathBuf},
    rc::Rc,
    sync::{
        Arc, RwLock,
        mpsc::{Sender, SyncSender},
    },
};

use glow::{
    HasContext, NativeFramebuffer, NativeProgram, NativeTexture, PixelPackData, PixelUnpackData,
};
use image::ExtendedColorType;
use imgui::{Context, Image, SliderFlags, TextureId, Ui, WindowFlags};
use imgui_glow_renderer::{AutoRenderer, Renderer};
use imgui_sdl2_support::SdlPlatform;
use itertools::Itertools;
use periodic_timer::PeriodicTimer;
use sdl2::{
    audio::AudioSpecDesired,
    event::Event,
    keyboard::Scancode,
    video::{GLProfile, Window},
};
use smps::driver::SoundDriver;
use sonic1::{get_data_defs, patch_rom, read_as_symbols};
use speedshoes::{
    DataSize, GAME_HEIGHT,
    gamesettings::GameSettings,
    system::{self, Input, System},
};

const ROM_PATH: &str = if cfg!(debug_assertions) {
    "../sonic1.bin"
} else {
    "sonic1.bin"
};

const REV01_MD5: &str = "09dadb5071eb35050067a32462e39c5f";

const REPRO_INPUTS_PATH: &str = "repro_inputs.bin";

// Create a new glow context.
fn glow_context(window: &Window) -> glow::Context {
    unsafe {
        glow::Context::from_loader_function(|s| window.subsystem().gl_get_proc_address(s) as _)
    }
}

fn main() -> Result<(), String> {
    let mut test_mode = false;
    let mut wide_mode = false;
    for arg in args() {
        if cfg!(debug_assertions) {
            if arg == "--test" {
                test_mode = true;
            }
        }
        if arg == "--wide" {
            wide_mode = true;
        }
    }

    let mut rom = fs::read(ROM_PATH).expect("Sonic 1 ROM not found.");
    if (format!("{:0x}", md5::compute(&rom)) != REV01_MD5) {
        panic!("Not a valid Sonic 1 ROM. Make sure you're using Revision 1.");
    }

    // patch our rom to work better with the engine
    patch_rom(&mut rom);
    run_window(
        rom,
        test_mode,
        fs::read(REPRO_INPUTS_PATH)
            .and_then(|bs| Ok(bs.iter().map(|b| (*b).into()).collect_vec()))
            .unwrap_or_default(),
        &GameSettings {
            screen_width: if wide_mode { 432 } else { 320 },
        },
    )
}

fn run_simulation(
    game: &mut Option<Sonic1>,
    rom: &Vec<u8>,
    test_mode: bool,
    repro_inputs: &Vec<Input>,
    should_reset: &mut bool,
    should_speed_up: bool,
    should_step: bool,
    system_input: Input,
    should_draw: bool,
    sound_driver_sender: Arc<Sender<i16>>,
    default_settings: &GameSettings,
) -> Result<bool, String> {
    if *should_reset {
        if game.is_none() {
            let data_defs = get_data_defs();
            let kvps = Some(
                data_defs
                    .iter()
                    .map(|d| (d.start, d.name.clone()))
                    .collect(),
            );
            *game = Some(Sonic1 {
                our_system: System::new(
                    "sonic1",
                    (&rom, 0x29A0),
                    kvps,
                    true,
                    test_mode,
                    true,
                    sound_driver_sender,
                    Arc::new(RwLock::new(default_settings.clone())),
                )?,
                debug_pause: false,
                current_playing_music: 0,
                is_current_music_sped_up: false,
                frame_counter: 0,
                input_history: repro_inputs.clone(),
            });
        }
        game.as_mut().unwrap().our_system.reset()?;
        *should_reset = false;
    }
    let num_game_frames = if should_speed_up {
        Sonic1::FAST_FRAME_COUNT
    } else {
        1
    };
    if let Some(game) = game {
        if game.debug_pause && should_step {
            game.run_game_frames(system_input, 1, should_draw)
        } else {
            game.run_game_frames(system_input, num_game_frames, should_draw)
        }
    } else {
        Ok(true)
    }
}

fn take_screenshot(
    gl_handle: &glow::Context,
    plane_renderer: &renderer::Renderer,
) -> (Vec<u8>, i32, i32) {
    unsafe {
        let width = renderer::PlaneTexture::SIZE.0 as i32;
        let height = renderer::PlaneTexture::SIZE.1 as i32;
        gl_handle.bind_framebuffer(glow::FRAMEBUFFER, Some(plane_renderer.fb()));
        let mut out_buf = vec![0u8; width as usize * height as usize * 4];
        gl_handle.read_pixels(
            0,
            0,
            width,
            height,
            glow::RGBA,
            glow::UNSIGNED_BYTE,
            PixelPackData::Slice(&mut out_buf),
        );
        gl_handle.bind_framebuffer(glow::FRAMEBUFFER, None);
        (out_buf, width, height)
    }
}

fn save_screenshot(name: &str, frame: &Vec<u8>, width: i32, height: i32) {
    image::save_buffer(
        name,
        frame,
        width as u32,
        height as u32,
        ExtendedColorType::Rgba8,
    )
    .unwrap();
}

fn run_window(
    rom: Vec<u8>,
    test_mode: bool,
    repro_inputs: Vec<Input>,
    default_settings: &GameSettings,
) -> Result<(), String> {
    let mut capture_video = false;
    let mut capture_video_prev = false;
    let mut capture_video_audio = None;
    let (mut capture_video_sender, mut capture_video_reciever) = (None, None);
    let mut capture_video_thread = None;

    /* initialize SDL and its video subsystem */
    let sdl = sdl2::init()?;
    let audio_subsystem = sdl.audio()?;
    let desired_spec = AudioSpecDesired {
        freq: Some(44_100),
        channels: Some(2),
        samples: None,
    };
    let audio_device = audio_subsystem.open_queue::<i16, _>(None, &desired_spec)?;

    let (sound_driver_id_sender, sound_driver_id_receiver) = std::sync::mpsc::channel::<i16>();
    let sound_driver_id_sender = Arc::new(sound_driver_id_sender);
    let thread_rom = Arc::new(rom.clone());
    let audio_spec = audio_device.spec().clone();
    let mut sound_driver = Box::new(SoundDriver::new(thread_rom, audio_spec.freq as u16));
    sound_driver.update();

    audio_device.resume();

    let video_subsystem = sdl.video().unwrap();

    let gl_attr = video_subsystem.gl_attr();

    gl_attr.set_context_version(4, 1);
    gl_attr.set_context_profile(GLProfile::Core);

    /* create a new window, be sure to call opengl method on the builder when using glow! */
    let window = video_subsystem
        .window(
            "Sonic the Hedgehog",
            default_settings.screen_width as u32,
            GAME_HEIGHT,
        )
        .allow_highdpi()
        .maximized()
        .opengl()
        .position_centered()
        .resizable()
        .build()
        .unwrap();

    /* create a new OpenGL context and make it current */
    let gl_context = window.gl_create_context().unwrap();
    window.gl_make_current(&gl_context).unwrap();

    /* enable vsync to cap framerate */
    window.subsystem().gl_set_swap_interval(1).unwrap();

    /* create new glow and imgui contexts */
    let gl = glow_context(&window);
    unsafe {
        gl.enable(glow::BLEND);
        gl.blend_color(1.0, 1.0, 1.0, 1.0);
    }

    /* create context */
    let mut imgui = Context::create();

    /* disable creation of files on disc */
    imgui.set_ini_filename(None);
    imgui.set_log_filename(None);

    /* setup platform and renderer, and fonts to imgui */
    imgui
        .fonts()
        .add_font(&[imgui::FontSource::DefaultFontData { config: None }]);

    /* create platform and renderer */
    let mut platform = SdlPlatform::new(&mut imgui);
    // let mut renderer = AutoRenderer::new(gl, &mut imgui).unwrap();
    // let gl_handle = renderer.gl_context().clone();
    let mut texture_map = imgui_glow_renderer::SimpleTextureMap::default();
    let mut renderer =
        Renderer::new(&gl, &mut imgui, &mut texture_map, false).map_err(|e| e.to_string())?;
    let gl_handle = Arc::new(gl);

    let mut working_game_width = default_settings.screen_width;
    let mut plane_renderer = renderer::Renderer::new(gl_handle.clone(), working_game_width);

    let mut game: Option<Sonic1> = None;

    // let script_watcher = FileWatcher::new("scripts");

    let mut should_reset = true;
    let mut error_string: Option<String> = None;
    let mut system_input = Input::default();

    let sdl_timer = &sdl.timer().unwrap();
    let target_frame_time = sdl_timer.performance_frequency() / 60;
    let mut start_frame_time: u64;
    let mut current_frame_time = 0u64;

    let ui_popup_id = "Simulation Errors";

    let mut native_percent_store = VecDeque::new();

    let mut should_draw = true;

    let mut frame_count = 0usize;

    let initial_repro_input_size = repro_inputs.len();
    let mut wrote_repro_inputs = false;

    let mut main_frame_timer = PeriodicTimer::new(60);
    let mut sim_frame_timer = PeriodicTimer::new(60);
    let mut render_frame_timer = PeriodicTimer::new(60);

    /* start main loop */
    let mut event_pump = sdl.event_pump().unwrap();

    'main: loop {
        start_frame_time = sdl_timer.performance_counter();

        main_frame_timer.start();

        let mut should_step = false;
        let mut should_speed_up = false;

        if cfg!(debug_assertions) {
            capture_video_prev = capture_video;
        }

        for event in event_pump.poll_iter() {
            /* pass all events to imgui platfrom */
            platform.handle_event(&mut imgui, &event);

            match event {
                Event::Quit { .. } => break 'main,
                Event::KeyDown { scancode, .. } => {
                    if scancode.is_some() {
                        match scancode.unwrap() {
                            Scancode::Up => system_input.up = true,
                            Scancode::Down => system_input.down = true,
                            Scancode::Left => system_input.left = true,
                            Scancode::Right => system_input.right = true,
                            Scancode::A => system_input.a = true,
                            Scancode::S => system_input.b = true,
                            Scancode::D => system_input.c = true,
                            Scancode::Return => system_input.start = true,

                            Scancode::F1 => {
                                error_string = None;
                                should_reset = true;
                            }
                            Scancode::F10 => {
                                if let Some(game) = &mut game {
                                    game.debug_pause = !game.debug_pause;
                                }
                            }
                            Scancode::F11 => should_step = true,
                            Scancode::Backspace => should_speed_up = true,
                            Scancode::Num0 => {
                                plane_renderer.shader_selection_plane.fill(0);
                                plane_renderer.shader_selection_screen = 0;
                            }
                            Scancode::Num1 => {
                                plane_renderer.shader_selection_plane[0] = 0;
                            }
                            Scancode::Num2 => {
                                plane_renderer.shader_selection_plane[0] = 1;
                            }
                            Scancode::Num5 => {
                                plane_renderer.shader_selection_screen = 0;
                            }
                            Scancode::Num6 => {
                                plane_renderer.shader_selection_screen = 1;
                            }
                            Scancode::F9 => {
                                let res = take_screenshot(&gl_handle, &plane_renderer);
                                save_screenshot("screenshot.png", &res.0, res.1, res.2);
                            }
                            Scancode::Minus => {
                                if cfg!(debug_assertions) {
                                    capture_video = !capture_video
                                }
                            }
                            Scancode::Equals => {
                                if cfg!(debug_assertions) {
                                    if fs::exists(REPRO_INPUTS_PATH).map_err(|e| e.to_string())? {
                                        fs::remove_file(REPRO_INPUTS_PATH)
                                            .map_err(|e| e.to_string())?;
                                    }
                                    fs::write(
                                        REPRO_INPUTS_PATH,
                                        game.as_ref()
                                            .unwrap()
                                            .input_history
                                            .iter()
                                            .map(|i| (*i).into())
                                            .collect_vec(),
                                    );
                                }
                            }
                            _ => {}
                        }
                    }
                }
                Event::KeyUp { scancode, .. } => {
                    if scancode.is_some() {
                        match scancode.unwrap() {
                            Scancode::Up => system_input.up = false,
                            Scancode::Down => system_input.down = false,
                            Scancode::Left => system_input.left = false,
                            Scancode::Right => system_input.right = false,
                            Scancode::A => system_input.a = false,
                            Scancode::S => system_input.b = false,
                            Scancode::D => system_input.c = false,
                            Scancode::Return => system_input.start = false,
                            _ => {}
                        }
                    }
                }
                Event::Window {
                    timestamp,
                    window_id,
                    win_event,
                } => {
                    /*if window.id() == window_id {
                        match win_event {
                            sdl2::event::WindowEvent::Shown => should_draw = true,
                            sdl2::event::WindowEvent::Exposed => should_draw = true,
                            sdl2::event::WindowEvent::Hidden => should_draw = false,
                            // sdl2::event::WindowEvent::Enter => todo!(),
                            // sdl2::event::WindowEvent::Leave => todo!(),
                            sdl2::event::WindowEvent::FocusGained => should_draw = true,
                            sdl2::event::WindowEvent::FocusLost => should_draw = false,
                            sdl2::event::WindowEvent::Close => should_draw = false,
                            _ => {}
                        }
                    }*/
                }
                _ => {}
            }
        }

        if cfg!(debug_assertions) {
            if capture_video != capture_video_prev {
                if capture_video {
                    _ = fs::remove_dir_all("movie");
                    _ = fs::create_dir("movie");

                    capture_video_audio = Some(
                        hound::WavWriter::create(
                            "movie/movie.wav",
                            hound::WavSpec {
                                channels: 2,
                                sample_rate: 44100,
                                bits_per_sample: 16,
                                sample_format: hound::SampleFormat::Int,
                            },
                        )
                        .unwrap(),
                    );
                    (capture_video_sender, capture_video_reciever) = {
                        let ret = std::sync::mpsc::channel::<Option<(Vec<u8>, i32, i32)>>();
                        (Some(ret.0), Some(ret.1))
                    };

                    capture_video_thread = Some(std::thread::spawn(move || {
                        let mut frame_count = 0;
                        loop {
                            if let Ok(frame) = capture_video_reciever.as_ref().unwrap().try_recv() {
                                if let Some((frame, width, height)) = frame {
                                    save_screenshot(
                                        &format!("movie/movie{}.qoi", frame_count),
                                        &frame,
                                        width,
                                        height,
                                    );
                                    frame_count += 1;
                                } else {
                                    break;
                                }
                            }
                        }
                    }));
                } else {
                    capture_video_audio = None;
                    capture_video_sender.as_ref().unwrap().send(None).unwrap();
                    capture_video_thread.unwrap().join().unwrap();
                    capture_video_thread = None;
                    (capture_video_sender, capture_video_reciever) = (None, None);
                }
            }
        }

        if let Some(game) = game.as_mut() {
            should_speed_up |= game.frame_counter < initial_repro_input_size;
            game.our_system.game_settings.write().unwrap().screen_width = working_game_width;
        }

        let sim_result = match error_string {
            Some(ref err) => Err(err.clone()),
            None => {
                sim_frame_timer.start();
                let ret = run_simulation(
                    &mut game,
                    &rom,
                    test_mode,
                    &repro_inputs,
                    &mut should_reset,
                    should_speed_up,
                    should_step,
                    system_input,
                    should_draw,
                    sound_driver_id_sender.clone(),
                    default_settings,
                );
                sim_frame_timer.finish();
                ret
            }
        };

        render_frame_timer.start();

        /* call prepare_frame before calling imgui.new_frame() */
        platform.prepare_frame(&mut imgui, &window, &event_pump);

        let ui = imgui.new_frame();
        /* create imgui UI here */

        let bg_color_f32 = match &game {
            Some(game) => game
                .our_system
                .bg_color()
                .to_ne_bytes()
                .map(|b| b as f32 / 255.0),
            None => [0.0; 4],
        };

        match sim_result {
            Err(ref m) => {
                /*if let Some(game) = &mut game {
                    game.render();
                }*/
                if !wrote_repro_inputs {
                    wrote_repro_inputs = true;
                    if fs::exists(REPRO_INPUTS_PATH).map_err(|e| e.to_string())? {
                        fs::remove_file(REPRO_INPUTS_PATH).map_err(|e| e.to_string())?;
                    }
                    fs::write(
                        REPRO_INPUTS_PATH,
                        game.as_ref()
                            .unwrap()
                            .input_history
                            .iter()
                            .map(|i| (*i).into())
                            .collect_vec(),
                    );
                }
                error_string = Some(m.clone());
                ui.open_popup(ui_popup_id);
                if let Some(_token) = ui
                    .modal_popup_config(ui_popup_id)
                    .resizable(false)
                    .always_auto_resize(false)
                    .collapsible(false)
                    .movable(false)
                    .begin_popup()
                {
                    ui.text(m);
                }
            }
            Ok(should_redraw) => {
                ui.close_current_popup();
                if should_redraw {
                    if let Some(game) = &game {
                        let time = (game.frame_counter as f32) / 60.0;
                        plane_renderer.render(
                            &gl_handle,
                            game.our_system.fb_plane_b_low(),
                            game.our_system.fb_plane_a_low(),
                            game.our_system.fb_plane_s_low(),
                            game.our_system.fb_plane_b_high(),
                            game.our_system.fb_plane_a_high(),
                            game.our_system.fb_plane_s_high(),
                            time,
                            working_game_width,
                            bg_color_f32,
                            &game
                                .our_system
                                .vdp()
                                .as_ref()
                                .borrow()
                                .palette_f32()
                                .try_into()
                                .unwrap(),
                        );
                    }
                }
            }
        }

        unsafe {
            gl_handle.clear_color(
                bg_color_f32[0],
                bg_color_f32[1],
                bg_color_f32[2],
                bg_color_f32[3],
            );
        }

        let output_aspect: f32 = window.drawable_size().0 as f32 / window.drawable_size().1 as f32;
        let preferred_aspect: f32 = game
            .as_ref()
            .map(|s1| s1.our_system.game_settings.read().unwrap().screen_width)
            .unwrap_or(320) as f32
            / GAME_HEIGHT as f32;

        let mut game_view_rect = (0f32, 0f32, 0f32, 0f32);

        if output_aspect <= preferred_aspect {
            let present_height = window.drawable_size().0 as f32 / preferred_aspect + 0.5;
            let bar_height = (window.drawable_size().1 as f32 - present_height) / 2.0;

            game_view_rect = (
                0.0,
                bar_height,
                window.drawable_size().0 as f32,
                present_height,
            );
        } else {
            let present_width = window.drawable_size().1 as f32 * preferred_aspect + 0.5;
            let bar_width = (window.drawable_size().0 as f32 - present_width) / 2.0;

            game_view_rect = (
                bar_width,
                0.0,
                present_width,
                window.drawable_size().1 as f32,
            );
        }

        ui.get_background_draw_list()
            .add_image(
                TextureId::new(plane_renderer.fb_tex().0.get() as usize),
                [game_view_rect.0, game_view_rect.1],
                [
                    game_view_rect.0 + game_view_rect.2,
                    game_view_rect.1 + game_view_rect.3,
                ],
            )
            .build();

        if let Some(game) = &game {
            let script_inst_count = game.our_system.script_machine_instructions_ran();
            let emu_inst_count = game.our_system.emu_machine_instructions_ran();
            const MAX_AVERAGE_COUNT: usize = 10;
            let native_percent =
                (1.0 - ((script_inst_count as f64) / (emu_inst_count.max(1) as f64))) * 100.0;
            native_percent_store.push_back(native_percent);
            if native_percent_store.len() > MAX_AVERAGE_COUNT {
                native_percent_store.pop_front();
            }

            if cfg!(debug_assertions) {
                if test_mode {
                    ui.window("Debug Info")
                        .no_decoration()
                        .position([0.0, 0.0], imgui::Condition::Always)
                        .always_auto_resize(true)
                        .no_inputs()
                        .build(|| {
                            ui.text(format!("Frame {}", game.frame_counter()));
                            /*ui.text(format!(
                                "Instructions emulated w/ scripts: {}",
                                script_inst_count,
                            ));
                            ui.text(format!(
                                "Instructions to emulate w/o scripts: {}",
                                emu_inst_count,
                            ));
                            ui.text(format!(
                                "{}% native code",
                                native_percent_store.iter().sum::<f64>() / (MAX_AVERAGE_COUNT as f64)
                            ));*/
                        });
                    /*ui.window("Input display")
                        .no_decoration()
                        .position([0.0, 80.0], imgui::Condition::Always)
                        .always_auto_resize(true)
                        .no_inputs()
                        .build(|| {
                            ui.text(
                                (game.input_history.get(game.frame_counter))
                                    .map(|i| i.clone())
                                    .unwrap_or_default()
                                    .to_string(),
                            )
                        });
                    ui.window("Unimplemented funcs")
                        .no_decoration()
                        .position([0.0, 120.0], imgui::Condition::Always)
                        .always_auto_resize(true)
                        .no_inputs()
                        .build(|| {
                            for sub in &game.our_system.unimplemented_subs_frame {
                                ui.text(format!("{:X}", sub));
                            }
                        });*/
                }
            }

            if cfg!(debug_assertions) {
                ui.window("Stats")
                    .no_decoration()
                    .position([0.0, 0.0], imgui::Condition::Always)
                    .always_auto_resize(true)
                    .no_inputs()
                    .build(|| {
                        ui.text(format!(
                            "Overall FPS: {:.2}",
                            main_frame_timer.get_average_periodicity()
                        ));
                        ui.text(format!(
                            "Sim time ms: {:.2}",
                            sim_frame_timer.get_average_duration() * 100.0,
                        ));
                        ui.text(format!(
                            "Render time ms: {:.2}",
                            render_frame_timer.get_average_duration() * 100.0,
                        ));
                    });
                ui.window("Game Settings")
                    .no_decoration()
                    .position([0.0, 64.0], imgui::Condition::Always)
                    .always_auto_resize(true)
                    .nav_inputs(false)
                    .nav_focus(false)
                    .build(|| {
                        if !test_mode {
                            let mut tmp = working_game_width as i32;
                            ui.slider("Game Width", 320, 432, &mut tmp);
                            working_game_width = tmp.next_multiple_of(8) as u16;
                        }
                    });
            }
        }

        /* render */
        let draw_data = imgui.render();

        unsafe {
            gl_handle.clear(glow::COLOR_BUFFER_BIT);
        }
        // renderer.render(&draw_data).unwrap();
        renderer
            .render(gl_handle.as_ref(), &texture_map, draw_data)
            .unwrap();

        window.gl_swap_window();

        render_frame_timer.finish();

        if cfg!(debug_assertions) {
            if capture_video {
                capture_video_sender
                    .as_ref()
                    .unwrap()
                    .send(Some(take_screenshot(&gl_handle, &plane_renderer)))
                    .unwrap();
            }
        }

        const SOUND_DRIVER_PLAY_SOUND: i16 = 0x02;
        const SOUND_DRIVER_PLAY_SOUND_SPECIAL: i16 = 0x03;
        loop {
            if let Ok(id) = sound_driver_id_receiver.try_recv() {
                if (id >> 8) == SOUND_DRIVER_PLAY_SOUND {
                    sound_driver.play_sound((id & 0xff) as u8);
                } else if (id >> 8) == SOUND_DRIVER_PLAY_SOUND_SPECIAL {
                    sound_driver.play_sound_special((id & 0xff) as u8);
                }
            } else {
                break;
            }
        }

        sound_driver.update();
        if audio_device.size() < audio_device.spec().size {
            audio_device
                .queue_audio(&sound_driver.safe_audio_buffer)
                .unwrap();
        }

        if cfg!(debug_assertions) {
            if let Some(capture_video_audio) = &mut capture_video_audio {
                for sample in &sound_driver.safe_audio_buffer {
                    capture_video_audio.write_sample(*sample);
                }
            }
        }

        main_frame_timer.finish();
        loop {
            current_frame_time = sdl_timer.performance_counter();
            if (current_frame_time - start_frame_time) > target_frame_time {
                frame_count += 1;
                break;
            }
        }
    }

    if cfg!(debug_assertions) {
        if capture_video {
            capture_video_sender.unwrap().send(None).unwrap();
            capture_video_thread.unwrap().join().unwrap();
        }
    }

    Ok(())
}

struct Sonic1 {
    our_system: System,
    debug_pause: bool,
    pub current_playing_music: u8,
    is_current_music_sped_up: bool,
    frame_counter: usize,
    input_history: Vec<Input>,
}

impl Sonic1 {
    const FAST_FRAME_COUNT: u8 = 8;

    fn render(&mut self) -> Result<(), String> {
        self.our_system.render()
    }

    fn frame_counter(&self) -> usize {
        self.frame_counter
    }

    fn run_game_frames(
        &mut self,
        system_input: Input,
        num_frames: u8,
        render: bool,
    ) -> Result<bool, String> {
        self.current_playing_music = 0;
        let mut should_redraw = false;
        if !self.debug_pause {
            for _ in 0..num_frames {
                while self.frame_counter >= self.input_history.len() {
                    self.input_history.push(system_input);
                }
                // println!("Frame {}", self.frame_counter);
                self.our_system
                    .run_frame(self.input_history[self.frame_counter])
                    .map_err(|e| {
                        println!("{}", e);
                        e
                    })?;

                self.frame_counter += 1;
            }
            if render {
                self.render()?;
            }

            should_redraw = true;
        }
        Ok(should_redraw)
    }
}
