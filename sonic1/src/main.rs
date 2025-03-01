mod plane_texture;

use std::{
    borrow::Borrow,
    collections::{HashMap, VecDeque},
    env::args,
    ffi::c_float,
    fs::{self, File},
    io::Write,
    num::NonZeroU32,
    ops::Range,
    panic::set_hook,
    path::{Path, PathBuf},
    rc::Rc,
};

use glow::{HasContext, NativeProgram, NativeTexture, PixelUnpackData};
use imgui::{Context, Image, TextureId, Ui, WindowFlags};
use imgui_glow_renderer::{AutoRenderer, Renderer};
use imgui_sdl2_support::SdlPlatform;
use itertools::Itertools;
use plane_texture::PlaneTexture;
use sdl2::{
    audio::AudioSpecDesired,
    event::Event,
    keyboard::Scancode,
    video::{GLProfile, Window},
};
use sonic1::{get_data_defs, patch_rom, read_as_symbols};
use speedshoes::{
    system::{self, Input, System},
    DataSize, GAME_HEIGHT, GAME_WIDTH,
};

const ROM_PATH: &str = if cfg!(debug_assertions) {
    "../s1built.bin"
} else {
    "s1built.bin"
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
    for arg in args() {
        if arg == "--test" {
            test_mode = true;
            break;
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
    )
}

fn run_simulation(
    game: &mut Option<Sonic1>,
    rom: &Vec<u8>,
    test_mode: bool,
    hw_planes_mode: bool,
    repro_inputs: &Vec<Input>,
    should_reset: &mut bool,
    should_speed_up: bool,
    should_step: bool,
    system_input: Input,
    should_draw: bool,
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
                    hw_planes_mode,
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

fn run_window(rom: Vec<u8>, test_mode: bool, repro_inputs: Vec<Input>) -> Result<(), String> {
    /* initialize SDL and its video subsystem */
    let sdl = sdl2::init()?;
    let audio_subsystem = sdl.audio()?;
    let desired_spec = AudioSpecDesired {
        freq: Some(44_100),
        channels: Some(2),
        // mono  -
        samples: None, // default sample size
    };
    let audio_device = audio_subsystem.open_queue::<i16, _>(None, &desired_spec)?;

    let video_subsystem = sdl.video().unwrap();

    /* hint SDL to initialize an OpenGL 3.3 core profile context */
    let gl_attr = video_subsystem.gl_attr();

    gl_attr.set_context_version(4, 1);
    gl_attr.set_context_profile(GLProfile::Core);

    /* create a new window, be sure to call opengl method on the builder when using glow! */
    let window = video_subsystem
        .window("Sonic the Hedgehog", GAME_WIDTH, GAME_HEIGHT)
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
    let gl_handle = gl;

    let hw_planes_mode = false;

    let mut fb_plane_b_low_handle = PlaneTexture::new(&gl_handle);
    let mut fb_plane_a_low_handle = PlaneTexture::new(&gl_handle);
    let mut fb_plane_s_low_handle = PlaneTexture::new(&gl_handle);
    let mut fb_plane_b_high_handle = PlaneTexture::new(&gl_handle);
    let mut fb_plane_a_high_handle = PlaneTexture::new(&gl_handle);
    let mut fb_plane_s_high_handle = PlaneTexture::new(&gl_handle);

    let mut game: Option<Sonic1> = None;

    // let script_watcher = FileWatcher::new("scripts");

    let mut should_reset = true;
    let mut error_string: Option<String> = None;
    let mut system_input = Input::default();

    let target_frame_time = sdl.timer().unwrap().performance_frequency() / 60;
    let mut start_frame_time: u64;

    let ui_popup_id = "Simulation Errors";

    let mut apply_filter = false;

    let mut native_percent_store = VecDeque::new();

    let mut should_draw = true;

    let initial_repro_input_size = repro_inputs.len();
    let mut wrote_repro_inputs = false;

    /* start main loop */
    let mut event_pump = sdl.event_pump().unwrap();

    'main: loop {
        start_frame_time = sdl.timer().unwrap().performance_counter();

        let mut should_step = false;
        let mut should_speed_up = false;

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
                            Scancode::Num1 => apply_filter = !apply_filter,
                            Scancode::Equals => {
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
        if let Some(game) = game.as_ref() {
            should_speed_up |= game.frame_counter < initial_repro_input_size;
        }

        let sim_result = match error_string {
            Some(ref err) => Err(err.clone()),
            None => run_simulation(
                &mut game,
                &rom,
                test_mode,
                hw_planes_mode,
                &repro_inputs,
                &mut should_reset,
                should_speed_up,
                should_step,
                system_input,
                should_draw,
            ),
        };

        /* call prepare_frame before calling imgui.new_frame() */
        platform.prepare_frame(&mut imgui, &window, &event_pump);

        let ui = imgui.new_frame();
        /* create imgui UI here */

        /*match error_string.clone().and_then(|_| {
            run_simulation(
                &mut game,
                &rom,
                test_mode,
                &mut should_reset,
                should_speed_up,
                should_step,
                system_input,
                should_draw,
            )
        })*/
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
                        let time = (game.frame_counter as f64) / 60.0;
                        let window_size: [f32; 2] = ui.io().display_size;
                        if hw_planes_mode {
                            fb_plane_b_low_handle.render(
                                &gl_handle,
                                &window_size,
                                game.our_system.fb_plane_b_low(),
                                apply_filter,
                                time as f32,
                            );
                            fb_plane_a_low_handle.render(
                                &gl_handle,
                                &window_size,
                                game.our_system.fb_plane_a_low(),
                                false,
                                time as f32,
                            );
                            fb_plane_s_low_handle.render(
                                &gl_handle,
                                &window_size,
                                game.our_system.fb_plane_s_low(),
                                false,
                                time as f32,
                            );
                            fb_plane_b_high_handle.render(
                                &gl_handle,
                                &window_size,
                                game.our_system.fb_plane_b_high(),
                                apply_filter,
                                time as f32,
                            );
                        }
                        fb_plane_a_high_handle.render(
                            &gl_handle,
                            &window_size,
                            game.our_system.fb_plane_a_high(),
                            false,
                            time as f32,
                        );
                        if hw_planes_mode {
                            fb_plane_s_high_handle.render(
                                &gl_handle,
                                &window_size,
                                game.our_system.fb_plane_s_high(),
                                false,
                                time as f32,
                            );
                        }
                    }
                }
            }
        }

        let bg_color_f32 = match &game {
            Some(game) => game
                .our_system
                .bg_color()
                .to_ne_bytes()
                .map(|b| b as f32 / 255.0),
            None => [0.0; 4],
        };

        unsafe {
            gl_handle.clear_color(
                bg_color_f32[0],
                bg_color_f32[1],
                bg_color_f32[2],
                bg_color_f32[3],
            );
        }

        let output_aspect: f32 = window.drawable_size().0 as f32 / window.drawable_size().1 as f32;
        const PREFERRED_ASPECT: f32 = GAME_WIDTH as f32 / GAME_HEIGHT as f32;

        let mut game_view_rect = (0f32, 0f32, 0f32, 0f32);

        if output_aspect <= PREFERRED_ASPECT {
            let present_height = window.drawable_size().0 as f32 / PREFERRED_ASPECT + 0.5;
            let bar_height = (window.drawable_size().1 as f32 - present_height) / 2.0;

            game_view_rect = (
                0.0,
                bar_height,
                window.drawable_size().0 as f32,
                present_height,
            );
        } else {
            let present_width = window.drawable_size().1 as f32 * PREFERRED_ASPECT + 0.5;
            let bar_width = (window.drawable_size().0 as f32 - present_width) / 2.0;

            game_view_rect = (
                bar_width,
                0.0,
                present_width,
                window.drawable_size().1 as f32,
            );
        }

        for handle in if hw_planes_mode {
            vec![
                &fb_plane_b_low_handle,
                &fb_plane_a_low_handle,
                &fb_plane_s_low_handle,
                &fb_plane_b_high_handle,
                &fb_plane_a_high_handle,
                &fb_plane_s_high_handle,
            ]
        } else {
            vec![&fb_plane_a_high_handle]
        } {
            ui.get_background_draw_list()
                .add_image(
                    TextureId::new(handle.frame_texture_handle.0.get() as usize),
                    [game_view_rect.0, game_view_rect.1],
                    [
                        game_view_rect.0 + game_view_rect.2,
                        game_view_rect.1 + game_view_rect.3,
                    ],
                )
                .build();
        }

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

            if test_mode {
                ui.window("Debug Info")
                    .no_decoration()
                    .position([0.0, 0.0], imgui::Condition::Always)
                    .always_auto_resize(true)
                    .no_inputs()
                    .build(|| {
                        ui.text(format!("Frame {}", game.frame_counter()));
                        ui.text(format!(
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
                        ));
                    });
                ui.window("Input display")
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
            .render(&gl_handle, &texture_map, draw_data)
            .unwrap();

        window.gl_swap_window();

        loop {
            let current_frame_time = sdl.timer().unwrap().performance_counter();
            if (current_frame_time - start_frame_time) > target_frame_time {
                break;
            }
        }
    }

    fb_plane_b_low_handle.destroy(&gl_handle);
    fb_plane_a_low_handle.destroy(&gl_handle);
    fb_plane_s_low_handle.destroy(&gl_handle);
    fb_plane_b_high_handle.destroy(&gl_handle);
    fb_plane_a_high_handle.destroy(&gl_handle);
    fb_plane_s_high_handle.destroy(&gl_handle);
    Ok(())
}

struct Sonic1 {
    our_system: System,
    debug_pause: bool,
    current_playing_music: u8,
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
