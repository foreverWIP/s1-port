use std::{
    cell::{LazyCell, OnceCell},
    collections::HashMap,
    ffi::c_void,
    hash::Hash,
    rc::Rc,
    sync::{Arc, LazyLock},
};

use const_format::formatcp;
use glow::*;
use imgui::*;
use sdl2::{
    pixels::{Color, PixelFormatEnum},
    rect::{Point, Rect},
    render::SurfaceCanvas,
    surface::Surface,
};
use speedshoes::{GAME_HEIGHT, GAME_WIDTH};
use std::num::NonZeroU32;

#[repr(C)]
#[derive(Clone, Copy)]
struct Vertex {
    pos: [f32; 2],
    uv: [f32; 2],
}

const fn vertex(x: f32, y: f32, s: f32, t: f32) -> Vertex {
    Vertex {
        pos: [x, y],
        uv: [s, t],
    }
}

static VERTEX_SHADER_SCREEN_NORMAL: LazyLock<String> = LazyLock::new(|| {
    format!(
        "precision mediump float;
layout (location = 0) in vec2 Position;
layout (location = 1) in vec2 UV;
layout (location = 0) out vec2 Frag_UV;
void main()
{{
	Frag_UV = UV.xy;
	gl_Position = vec4(Position.xy,0,1);
}}",
    )
});

static VERTEX_SHADER_PLANE_NORMAL: LazyLock<String> = LazyLock::new(|| {
    format!(
        "precision mediump float;
layout (location = 0) in vec2 Position;
layout (location = 1) in vec2 UV;
layout (location = 0) out vec2 Frag_UV;
void main()
{{
	Frag_UV = UV.xy * vec2({}, {});
	gl_Position = vec4(Position.xy,0,1);
}}",
        PlaneTexture::SIZE.0,
        PlaneTexture::SIZE.1,
    )
});

static FRAG_SHADERS_PLANE: &[(&'static str, &'static str)] = &[
    ("normal", include_str!("shaders/plane-normal.frag")),
    ("blur", include_str!("shaders/plane-blur.frag")),
];

static FRAG_SHADERS_SCREEN: &[(&'static str, &'static str)] = &[
    ("normal", include_str!("shaders/screen-normal.frag")),
    ("ntsc", include_str!("shaders/screen-ntsc.frag")),
];

static INDEXED_PROLOGUE: &str = "\nvec4 readtex(usampler2D tex, vec2 uv)
{
	uint lookup = texture(tex, uv).r;
	if (mod(lookup, 16) == 0) discard;
	return palette[lookup];
}\n";

static RGBA_PROLOGUE: &str = "\nvec4 readtex(sampler2D tex, vec2 uv)
{
	return texture(tex, uv);
}\n";

const VERTICES: &[Vertex; 6] = &[
    vertex(-1.0, -1.0, 0.0, 0.0),
    vertex(1.0, -1.0, 1.0, 0.0),
    vertex(-1.0, 1.0, 0.0, 1.0),
    vertex(1.0, -1.0, 1.0, 0.0),
    vertex(1.0, 1.0, 1.0, 1.0),
    vertex(-1.0, 1.0, 0.0, 1.0),
];

unsafe fn set_uniform_float(gl: &glow::Context, program: Program, name: &str, value: f32) {
    let location = gl.get_uniform_location(program, name);
    gl.uniform_1_f32(location.as_ref(), value);
}

pub struct PlaneTexture<'plane> {
    pub frame_texture_handle: NativeTexture,
    indexed_color: bool,
    pub(self) sdl_renderer: SurfaceCanvas<'plane>,
}

impl PlaneTexture<'_> {
    pub const SCALE: usize = 4;
    pub const SIZE: (usize, usize) = (
        GAME_WIDTH as usize * Self::SCALE,
        GAME_HEIGHT as usize * Self::SCALE,
    );

    pub(self) fn new(gl: &glow::Context, indexed_color: bool) -> Self {
        unsafe {
            let frame_texture_handle = gl.create_texture().unwrap();
            gl.bind_texture(glow::TEXTURE_2D, Some(frame_texture_handle));
            gl.tex_image_2d(
                glow::TEXTURE_2D,
                0,
                if indexed_color {
                    glow::R8UI as i32
                } else {
                    glow::RGBA8 as i32
                },
                GAME_WIDTH as i32,
                GAME_HEIGHT as i32,
                0,
                if indexed_color {
                    glow::RED_INTEGER
                } else {
                    glow::RGBA
                },
                glow::UNSIGNED_BYTE,
                None,
            );
            gl.texture_parameter_i32(
                frame_texture_handle,
                glow::TEXTURE_MIN_FILTER,
                glow::NEAREST as i32,
            );
            gl.texture_parameter_i32(
                frame_texture_handle,
                glow::TEXTURE_MAG_FILTER,
                glow::NEAREST as i32,
            );
            gl.texture_parameter_i32(
                frame_texture_handle,
                glow::TEXTURE_WRAP_S,
                glow::CLAMP_TO_EDGE as i32,
            );
            gl.texture_parameter_i32(
                frame_texture_handle,
                glow::TEXTURE_WRAP_T,
                glow::CLAMP_TO_EDGE as i32,
            );
            gl.bind_texture(glow::TEXTURE_2D, None);

            Self {
                frame_texture_handle,
                indexed_color,
                sdl_renderer: SurfaceCanvas::from_surface(
                    Surface::new(
                        GAME_WIDTH as u32,
                        GAME_HEIGHT as u32,
                        if indexed_color {
                            PixelFormatEnum::Index8
                        } else {
                            PixelFormatEnum::ARGB8888
                        },
                    )
                    .unwrap(),
                )
                .unwrap(),
            }
        }
    }

    unsafe fn set_uniform_vec4_array(
        &self,
        gl: &glow::Context,
        program: Program,
        name: &str,
        value: &[f32],
    ) {
        let location = gl.get_uniform_location(program, name);
        gl.uniform_4_f32_slice(location.as_ref(), value);
    }

    unsafe fn set_uniform_vec2(
        &self,
        gl: &glow::Context,
        program: Program,
        name: &str,
        x: f32,
        y: f32,
    ) {
        let location = gl.get_uniform_location(program, name);
        gl.uniform_2_f32(location.as_ref(), x, y);
    }

    unsafe fn set_uniform_mat4(
        &self,
        gl: &glow::Context,
        program: Program,
        name: &str,
        mat: &[f32],
    ) {
        let location = gl.get_uniform_location(program, name);
        gl.uniform_matrix_4_f32_slice(location.as_ref(), false, mat);
    }

    pub fn draw_line(&mut self, x1: i16, y1: i16, x2: i16, y2: i16) {
        self.sdl_renderer
            .draw_line(
                Point::new(x1 as i32, y1 as i32),
                Point::new(x2 as i32, y2 as i32),
            )
            .unwrap();
    }

    pub fn draw_rect(&mut self, x: i16, y: i16, width: u16, height: u16) {
        self.sdl_renderer
            .draw_rect(Rect::new(x as i32, y as i32, width as u32, height as u32))
            .unwrap();
    }

    pub(self) fn draw_plane(&mut self, contents: &[u32]) {
        unsafe {
            (*self.sdl_renderer.surface_mut().raw())
                .pixels
                .copy_from(contents.as_ptr() as *const c_void, contents.len());
        }
    }

    pub(self) fn render(
        &mut self,
        gl: &glow::Context,
        time: f32,
        fb_all_planes: NativeFramebuffer,
        program: NativeProgram,
    ) {
        unsafe {
            let cur_texture = self.frame_texture_handle;
            gl.viewport(0, 0, Self::SIZE.0 as i32, Self::SIZE.1 as i32);
            gl.bind_texture(glow::TEXTURE_2D, Some(cur_texture));
            gl.tex_sub_image_2d(
                glow::TEXTURE_2D,
                0,
                0,
                0,
                GAME_WIDTH as i32,
                GAME_HEIGHT as i32,
                if self.indexed_color {
                    glow::RED_INTEGER
                } else {
                    glow::RGBA
                },
                glow::UNSIGNED_BYTE,
                PixelUnpackData::Slice(self.sdl_renderer.surface().without_lock().unwrap()),
            );
            gl.bind_texture(glow::TEXTURE_2D, None);
            gl.bind_framebuffer(glow::FRAMEBUFFER, Some(fb_all_planes));
            {
                gl.use_program(Some(program));
                let cur_location = gl.get_uniform_location(program, "CurTexture");

                gl.active_texture(glow::TEXTURE0);
                gl.bind_texture(glow::TEXTURE_2D, Some(cur_texture));

                gl.uniform_1_i32(cur_location.as_ref(), 0);
            }
            set_uniform_float(&gl, program, "iTime", time);
            if !self.indexed_color {
                gl.blend_func(glow::SRC_ALPHA, glow::ONE_MINUS_SRC_ALPHA);
            }
            gl.draw_arrays(glow::TRIANGLES, 0, 6);
            gl.bind_framebuffer(glow::FRAMEBUFFER, None);
        }
    }

    pub(self) fn destroy(&self, gl: &glow::Context) {
        unsafe {
            gl.delete_texture(self.frame_texture_handle);
        }
    }
}

pub struct Renderer<'renderer> {
    vertex_array: NativeVertexArray,
    vertex_buffer: NativeBuffer,

    shader_cache_plane_indexed: Vec<NativeProgram>,
    shader_cache_plane_rgba: Vec<NativeProgram>,
    shader_cache_screen: Vec<NativeProgram>,
    common_uniforms: glow::NativeBuffer,

    gl: Arc<glow::Context>,
    fb: NativeFramebuffer,
    fb_tex: NativeTexture,
    composite_fb: NativeFramebuffer,
    composite_tex: NativeTexture,

    plane_b_low_tex: PlaneTexture<'renderer>,
    plane_a_low_tex: PlaneTexture<'renderer>,
    plane_s_low_tex: PlaneTexture<'renderer>,
    plane_b_high_tex: PlaneTexture<'renderer>,
    plane_a_high_tex: PlaneTexture<'renderer>,
    plane_s_high_tex: PlaneTexture<'renderer>,
    plane_s_extra_tex: PlaneTexture<'renderer>,

    pub shader_selection_plane: [usize; 7],
    pub shader_selection_screen: usize,
}
impl Drop for Renderer<'_> {
    fn drop(&mut self) {
        self.plane_b_low_tex.destroy(&self.gl);
        self.plane_a_low_tex.destroy(&self.gl);
        self.plane_s_low_tex.destroy(&self.gl);
        self.plane_b_high_tex.destroy(&self.gl);
        self.plane_a_high_tex.destroy(&self.gl);
        self.plane_s_high_tex.destroy(&self.gl);
        self.plane_s_extra_tex.destroy(&self.gl);
        unsafe {
            self.gl.delete_framebuffer(self.fb);
            self.gl.delete_texture(self.fb_tex);
            self.gl.delete_texture(self.composite_tex);
            self.gl.delete_buffer(self.common_uniforms);
            self.gl.delete_vertex_array(self.vertex_array);
            self.gl.delete_buffer(self.vertex_buffer);
        }
    }
}
const COMMON_UNIFORMS_SIZE: usize = (std::mem::size_of::<f32>() * 4 * 64);
impl Renderer<'_> {
    pub fn new(gl_context: Arc<glow::Context>) -> Self {
        let fb = unsafe { gl_context.create_framebuffer().unwrap() };
        let fb_tex = unsafe {
            let ret = gl_context.create_texture().unwrap();
            gl_context.bind_texture(glow::TEXTURE_2D, Some(ret));
            gl_context.tex_image_2d(
                glow::TEXTURE_2D,
                0,
                glow::RGB as i32,
                PlaneTexture::SIZE.0 as i32,
                PlaneTexture::SIZE.1 as i32,
                0,
                glow::RGB,
                glow::UNSIGNED_BYTE,
                None,
            );
            gl_context.tex_parameter_i32(
                glow::TEXTURE_2D,
                glow::TEXTURE_MAG_FILTER,
                glow::NEAREST as i32,
            );
            gl_context.tex_parameter_i32(
                glow::TEXTURE_2D,
                glow::TEXTURE_MIN_FILTER,
                glow::NEAREST as i32,
            );
            gl_context.texture_parameter_i32(ret, glow::TEXTURE_WRAP_S, glow::CLAMP_TO_EDGE as i32);
            gl_context.texture_parameter_i32(ret, glow::TEXTURE_WRAP_T, glow::CLAMP_TO_EDGE as i32);
            gl_context.bind_framebuffer(glow::FRAMEBUFFER, Some(fb));
            gl_context.framebuffer_texture(
                glow::FRAMEBUFFER,
                glow::COLOR_ATTACHMENT0,
                Some(ret),
                0,
            );
            ret
        };
        let composite_fb = unsafe { gl_context.create_framebuffer().unwrap() };
        let composite_tex = unsafe {
            let ret = gl_context.create_texture().unwrap();
            gl_context.bind_texture(glow::TEXTURE_2D, Some(ret));
            gl_context.tex_image_2d(
                glow::TEXTURE_2D,
                0,
                glow::RGB as i32,
                PlaneTexture::SIZE.0 as i32,
                PlaneTexture::SIZE.1 as i32,
                0,
                glow::RGB,
                glow::UNSIGNED_BYTE,
                None,
            );
            gl_context.tex_parameter_i32(
                glow::TEXTURE_2D,
                glow::TEXTURE_MAG_FILTER,
                glow::NEAREST as i32,
            );
            gl_context.tex_parameter_i32(
                glow::TEXTURE_2D,
                glow::TEXTURE_MIN_FILTER,
                glow::NEAREST as i32,
            );
            gl_context.texture_parameter_i32(ret, glow::TEXTURE_WRAP_S, glow::CLAMP_TO_EDGE as i32);
            gl_context.texture_parameter_i32(ret, glow::TEXTURE_WRAP_T, glow::CLAMP_TO_EDGE as i32);
            gl_context.bind_framebuffer(glow::FRAMEBUFFER, Some(composite_fb));
            gl_context.framebuffer_texture(
                glow::FRAMEBUFFER,
                glow::COLOR_ATTACHMENT0,
                Some(ret),
                0,
            );
            ret
        };
        let mut shader_cache_plane_indexed = Vec::new();
        let mut shader_cache_plane_rgba = Vec::new();
        let mut shader_cache_screen = Vec::new();
        let fragment_header_plane_indexed = format!(
            "#version 410
precision mediump float;
uniform usampler2D CurTexture;
uniform float iTime;
layout (std140) uniform common_uniforms {{
vec4 palette[64];
}};
layout (location = 0) in vec2 Frag_UV;
layout (location = 0) out vec4 Out_Color;
const vec2 texture_size = vec2({}, {});
",
            PlaneTexture::SIZE.0,
            PlaneTexture::SIZE.1,
        );
        let fragment_header_plane_rgba = format!(
            "#version 410
precision mediump float;
uniform sampler2D CurTexture;
uniform float iTime;
layout (std140) uniform common_uniforms {{
vec4 palette[64];
}};
layout (location = 0) in vec2 Frag_UV;
layout (location = 0) out vec4 Out_Color;
const vec2 texture_size = vec2({}, {});
",
            PlaneTexture::SIZE.0,
            PlaneTexture::SIZE.1,
        );
        let fragment_header_screen = format!(
            "#version 410
precision mediump float;
uniform sampler2D CurTexture;
uniform float iTime;
layout (std140) uniform common_uniforms {{
vec4 palette[64];
}};
layout (location = 0) in vec2 Frag_UV;
layout (location = 0) out vec4 Out_Color;
const vec2 texture_size = vec2({}, {});
",
            PlaneTexture::SIZE.0,
            PlaneTexture::SIZE.1,
        );
        for frag_shader in FRAG_SHADERS_PLANE {
            let program = Self::build_shader_program(
                &gl_context,
                &VERTEX_SHADER_PLANE_NORMAL,
                &(fragment_header_plane_indexed.to_owned() + INDEXED_PROLOGUE + frag_shader.1),
            );
            unsafe {
                let index = gl_context
                    .get_uniform_block_index(program, "common_uniforms")
                    .unwrap();
                gl_context.uniform_block_binding(program, index, 0);
            }
            shader_cache_plane_indexed.push(program);
            let program = Self::build_shader_program(
                &gl_context,
                &VERTEX_SHADER_PLANE_NORMAL,
                &(fragment_header_plane_rgba.to_owned() + RGBA_PROLOGUE + frag_shader.1),
            );
            unsafe {
                let index = gl_context
                    .get_uniform_block_index(program, "common_uniforms")
                    .unwrap();
                gl_context.uniform_block_binding(program, index, 0);
            }
            shader_cache_plane_rgba.push(program);
        }
        for frag_shader in FRAG_SHADERS_SCREEN {
            let program = Self::build_shader_program(
                &gl_context,
                &VERTEX_SHADER_SCREEN_NORMAL,
                &(fragment_header_screen.to_owned() + frag_shader.1),
            );
            unsafe {
                let index = gl_context
                    .get_uniform_block_index(program, "common_uniforms")
                    .unwrap();
                gl_context.uniform_block_binding(program, index, 0);
            }
            shader_cache_screen.push(program);
        }
        let plane_b_low_tex = PlaneTexture::new(&gl_context, true);
        let plane_a_low_tex = PlaneTexture::new(&gl_context, true);
        let plane_s_low_tex = PlaneTexture::new(&gl_context, true);
        let plane_b_high_tex = PlaneTexture::new(&gl_context, true);
        let plane_a_high_tex = PlaneTexture::new(&gl_context, true);
        let plane_s_high_tex = PlaneTexture::new(&gl_context, true);
        let plane_s_extra_tex = PlaneTexture::new(&gl_context, false);
        let (vertex_buffer, vertex_array) = Self::create_vertex_buffer(&gl_context);
        Self {
            vertex_array,
            vertex_buffer,
            shader_cache_plane_indexed,
            shader_cache_plane_rgba,
            shader_cache_screen,
            common_uniforms: unsafe {
                let ret = gl_context.create_buffer().unwrap();
                gl_context.bind_buffer(glow::UNIFORM_BUFFER, Some(ret));
                gl_context.buffer_data_size(
                    glow::UNIFORM_BUFFER,
                    COMMON_UNIFORMS_SIZE as i32,
                    glow::STATIC_DRAW,
                );
                gl_context.bind_buffer(glow::UNIFORM_BUFFER, None);
                gl_context.bind_buffer_range(
                    glow::UNIFORM_BUFFER,
                    0,
                    Some(ret),
                    0,
                    COMMON_UNIFORMS_SIZE as i32,
                );
                ret
            },
            gl: gl_context.clone(),
            fb,
            fb_tex,
            composite_fb,
            composite_tex,
            plane_b_low_tex,
            plane_a_low_tex,
            plane_s_low_tex,
            plane_b_high_tex,
            plane_a_high_tex,
            plane_s_high_tex,
            plane_s_extra_tex,
            shader_selection_plane: [0; 7],
            shader_selection_screen: 0,
        }
    }

    pub fn fb_tex(&self) -> NativeTexture {
        self.fb_tex
    }

    pub fn fb(&self) -> NativeFramebuffer {
        self.fb
    }

    fn get_program(&self, id: usize, indexed: bool) -> NativeProgram {
        if indexed {
            self.shader_cache_plane_indexed[id]
        } else {
            self.shader_cache_plane_rgba[id]
        }
    }

    pub fn render(
        &mut self,
        gl: &glow::Context,
        plane_b_low: &[u32],
        plane_a_low: &[u32],
        plane_s_low: &[u32],
        plane_b_high: &[u32],
        plane_a_high: &[u32],
        plane_s_high: &[u32],
        time: f32,
        bg_color_f32: [f32; 4],
        palette: &[f32; 64 * 4],
    ) {
        unsafe {
            gl.bind_framebuffer(glow::FRAMEBUFFER, Some(self.composite_fb));
            gl.clear_color(
                bg_color_f32[0],
                bg_color_f32[1],
                bg_color_f32[2],
                bg_color_f32[3],
            );
            gl.clear(glow::COLOR_BUFFER_BIT);
            gl.bind_framebuffer(glow::FRAMEBUFFER, None);

            gl.bind_buffer(glow::UNIFORM_BUFFER, Some(self.common_uniforms));
            gl.buffer_sub_data_u8_slice(
                glow::UNIFORM_BUFFER,
                0,
                std::mem::transmute::<&[f32; 64 * 4], &[u8; COMMON_UNIFORMS_SIZE]>(palette),
            );
            gl.bind_buffer(glow::UNIFORM_BUFFER, None);
            gl.bind_framebuffer(glow::FRAMEBUFFER, Some(self.composite_fb));
        }
        self.plane_b_low_tex.draw_plane(plane_b_low);
        self.plane_b_low_tex.render(
            &gl,
            time as f32,
            self.composite_fb,
            self.get_program(
                self.shader_selection_plane[0],
                self.plane_b_low_tex.indexed_color,
            ),
        );
        self.plane_a_low_tex.draw_plane(plane_a_low);
        self.plane_a_low_tex.render(
            &gl,
            time as f32,
            self.composite_fb,
            self.get_program(
                self.shader_selection_plane[1],
                self.plane_a_low_tex.indexed_color,
            ),
        );
        self.plane_s_low_tex.draw_plane(plane_s_low);
        self.plane_s_low_tex.render(
            &gl,
            time as f32,
            self.composite_fb,
            self.get_program(
                self.shader_selection_plane[2],
                self.plane_s_low_tex.indexed_color,
            ),
        );
        self.plane_b_high_tex.draw_plane(plane_b_high);
        self.plane_b_high_tex.render(
            &gl,
            time as f32,
            self.composite_fb,
            self.get_program(
                self.shader_selection_plane[3],
                self.plane_b_high_tex.indexed_color,
            ),
        );
        self.plane_a_high_tex.draw_plane(plane_a_high);
        self.plane_a_high_tex.render(
            &gl,
            time as f32,
            self.composite_fb,
            self.get_program(
                self.shader_selection_plane[4],
                self.plane_a_high_tex.indexed_color,
            ),
        );
        self.plane_s_high_tex.draw_plane(plane_s_high);
        self.plane_s_high_tex.render(
            &gl,
            time as f32,
            self.composite_fb,
            self.get_program(
                self.shader_selection_plane[5],
                self.plane_s_high_tex.indexed_color,
            ),
        );
        self.plane_s_extra_tex
            .sdl_renderer
            .set_draw_color(Color::RGB(255, 0, 255));
        // self.plane_s_extra_tex.draw_line(0, 0, 100, 100);
        self.plane_s_extra_tex.render(
            &gl,
            time as f32,
            self.composite_fb,
            self.get_program(
                self.shader_selection_plane[6],
                self.plane_s_extra_tex.indexed_color,
            ),
        );
        unsafe {
            gl.viewport(
                0,
                0,
                PlaneTexture::SIZE.0 as i32,
                PlaneTexture::SIZE.1 as i32,
            );
            let program = self.shader_cache_screen[self.shader_selection_screen];
            gl.bind_framebuffer(glow::FRAMEBUFFER, Some(self.fb));
            {
                gl.use_program(Some(program));
                self.use_vertex_buffer(gl);
                let cur_location = gl.get_uniform_location(program, "CurTexture");

                gl.active_texture(glow::TEXTURE0);
                gl.bind_texture(glow::TEXTURE_2D, Some(self.composite_tex));

                gl.uniform_1_i32(cur_location.as_ref(), 0);
            }
            set_uniform_float(&gl, program, "iTime", time);
            gl.draw_arrays(glow::TRIANGLES, 0, 6);
            gl.bind_framebuffer(glow::FRAMEBUFFER, None);
        }
    }

    fn use_vertex_buffer(&self, gl: &glow::Context) {
        unsafe {
            gl.bind_buffer(glow::ARRAY_BUFFER, Some(self.vertex_buffer));
            gl.bind_vertex_array(Some(self.vertex_array));
            gl.enable_vertex_attrib_array(0);
            gl.enable_vertex_attrib_array(1);
        }
    }

    fn create_vertex_buffer(gl: &glow::Context) -> (NativeBuffer, NativeVertexArray) {
        unsafe {
            // This is a flat array of f32s that are to be interpreted as vec2s.
            let triangle_vertices = VERTICES;
            let triangle_vertices_u8: &[u8] = core::slice::from_raw_parts(
                triangle_vertices.as_ptr() as *const u8,
                triangle_vertices.len() * core::mem::size_of::<Vertex>(),
            );

            // We construct a buffer and upload the data
            let vbo = gl.create_buffer().unwrap();
            gl.bind_buffer(glow::ARRAY_BUFFER, Some(vbo));
            gl.buffer_data_u8_slice(glow::ARRAY_BUFFER, triangle_vertices_u8, glow::STATIC_DRAW);

            // We now construct a vertex array to describe the format of the input buffer
            let vao = gl.create_vertex_array().unwrap();
            gl.bind_vertex_array(Some(vao));
            gl.enable_vertex_attrib_array(0);
            gl.enable_vertex_attrib_array(1);
            gl.vertex_attrib_pointer_f32(
                0,
                2,
                glow::FLOAT,
                true,
                core::mem::size_of::<Vertex>() as i32,
                0,
            );
            gl.vertex_attrib_pointer_f32(
                1,
                2,
                glow::FLOAT,
                true,
                core::mem::size_of::<Vertex>() as i32,
                8,
            );

            (vbo, vao)
        }
    }

    fn build_shader_program(
        gl: &glow::Context,
        vertex: &str,
        fragment: &str,
    ) -> <glow::Context as HasContext>::Program {
        unsafe {
            let program = gl.create_program().expect("Cannot create program");

            let mut shaders = Vec::new();

            for (shader_source, shader_type) in [
                (vertex, glow::VERTEX_SHADER),
                (fragment, glow::FRAGMENT_SHADER),
            ] {
                let shader = {
                    let shader = gl.create_shader(shader_type).expect("Cannot create shader");
                    gl.shader_source(
                        shader,
                        &(if shader_type == glow::VERTEX_SHADER {
                            format!("{}\n{}", "#version 410", shader_source)
                        } else {
                            format!("{}", shader_source)
                        }),
                    );
                    gl.compile_shader(shader);
                    if !gl.get_shader_compile_status(shader) {
                        panic!("{}", gl.get_shader_info_log(shader));
                    }
                    shader
                };
                gl.attach_shader(program, shader);
                shaders.push(shader);
            }

            gl.link_program(program);
            if !gl.get_program_link_status(program) {
                panic!("{}", gl.get_program_info_log(program));
            }

            for shader in shaders {
                gl.detach_shader(program, shader);
                gl.delete_shader(shader);
            }

            program
        }
    }
}
