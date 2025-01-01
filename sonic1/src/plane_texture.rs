use std::{collections::HashMap, hash::Hash, rc::Rc};

use const_format::formatcp;
use glow::*;
use imgui::*;
use speedshoes::{GAME_HEIGHT, GAME_WIDTH};
use std::num::NonZeroU32;

const PLANE_SCALE: usize = 1;

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

const NORMAL_VERTEX_SHADER_SOURCE: &str = formatcp!(
    r#"
precision highp float;
layout (location = 0) in vec2 Position;
layout (location = 1) in vec2 UV;
uniform sampler2D CurTexture;
uniform vec2 WindowSize;
layout (location = 0) out vec2 Frag_UV;
void main()
{{
	Frag_UV = UV.xy;
	gl_Position = vec4(Position.xy,0,1);
}}"#
);

const NORMAL_FRAGMENT_SHADER_SOURCE: &str = formatcp!(
    r#"
precision mediump float;
uniform sampler2D CurTexture;
uniform float iTime;
layout (location = 0) in vec2 Frag_UV;
layout (location = 0) out vec4 Out_Color;
void main()
{{
	Out_Color = texture(CurTexture, Frag_UV.st / vec2({GAME_WIDTH}, {GAME_HEIGHT}));
}}"#
);

/*const FILTER_FRAGMENT_SHADER_SOURCE: &str = r#"
precision mediump float;
uniform sampler2D CurTexture;
uniform float iTime;
uniform vec2 WindowSize;
layout (location = 0) in vec2 Frag_UV;
layout (location = 0) out vec4 Out_Color;
float normpdf(in float x, in float sigma)
{
return 0.39894*exp(-0.5*x*x/(sigma*sigma))/sigma;
}

void main()
{

    vec3 c = texture(CurTexture, Frag_UV.xy /*/
 WindowSize.xy*/).rgb;
//declare stuff
	const int mSize = 11;
	const int kSize = (mSize-1)/2;
	float kernel[mSize];
	vec3 final_colour = vec3(0.0);

//create the 1-D kernel
	float sigma = 7.0;
	float Z = 0.0;
	for (int j = 0; j <= kSize; ++j)
	{
		kernel[kSize+j] = kernel[kSize-j] = normpdf(float(j), sigma);
	}

//get the normalization factor (as the gaussian has been clamped)
	for (int j = 0; j < mSize; ++j)
	{
		Z += kernel[j];
	}

//read out the texels
	for (int i=-kSize; i <= kSize; ++i)
	{
		for (int j=-kSize; j <= kSize; ++j)
		{
			final_colour += kernel[kSize+j]*kernel[kSize+i]*texture(CurTexture, Frag_UV.xy+(vec2(float(i),float(j)) / WindowSize.xy)).rgb;

		}
	}


	Out_Color = vec4(final_colour/(Z*Z), 1.0);
}"#;*/

static mut SHADER_CACHE: Option<HashMap<md5::Digest, NativeShader>> = None;

fn build_shader_program(
    gl: &glow::Context,
    vertex: &str,
    fragment: &str,
) -> <glow::Context as HasContext>::Program {
    unsafe {
        // let normal_program = gl.create_program().expect("Cannot create program");
        // let filter_program = gl.create_program().expect("Cannot create program");

        let program = gl.create_program().expect("Cannot create program");

        let mut shaders = Vec::new();
        for (shader_source, shader_type) in [
            (vertex, glow::VERTEX_SHADER),
            (fragment, glow::FRAGMENT_SHADER),
        ] {
            if SHADER_CACHE.is_none() {
                SHADER_CACHE = Some(HashMap::new());
            }
            let shader = {
                let shader_cache = SHADER_CACHE.as_mut().unwrap();
                let digest = md5::compute(shader_source);
                if let Some(shader) = shader_cache.get(&digest) {
                    *shader
                } else {
                    let shader = gl.create_shader(shader_type).expect("Cannot create shader");
                    gl.shader_source(shader, &format!("{}\n{}", "#version 410", shader_source));
                    gl.compile_shader(shader);
                    if !gl.get_shader_compile_status(shader) {
                        panic!("{}", gl.get_shader_info_log(shader));
                    }
                    shader
                }
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

const VERTICES: &[Vertex; 6] = &[
    vertex(-1.0, -1.0, 0.0, 0.0),
    vertex(1.0, -1.0, GAME_WIDTH as f32, 0.0),
    vertex(-1.0, 1.0, 0.0, GAME_HEIGHT as f32),
    vertex(1.0, -1.0, GAME_WIDTH as f32, 0.0),
    vertex(1.0, 1.0, GAME_WIDTH as f32, GAME_HEIGHT as f32),
    vertex(-1.0, 1.0, 0.0, GAME_HEIGHT as f32),
];

pub struct PlaneTexture {
    pub normal_program: <glow::Context as HasContext>::Program,
    // pub filter_program: <glow::Context as HasContext>::Program,
    pub vertex_array: <glow::Context as HasContext>::VertexArray,
    pub vertex_buffer: <glow::Context as HasContext>::Buffer,
    pub frame_texture_handle: NativeTexture,
    buffer_switch: bool,
    filter: bool,
}

impl PlaneTexture {
    pub fn new(gl: &glow::Context) -> Self {
        unsafe {
            let normal_program = build_shader_program(
                gl,
                NORMAL_VERTEX_SHADER_SOURCE,
                NORMAL_FRAGMENT_SHADER_SOURCE,
            );
            /*let filter_program = build_shader_program(
                gl,
                NORMAL_VERTEX_SHADER_SOURCE,
                FILTER_FRAGMENT_SHADER_SOURCE,
            );*/

            let (vbo, vao) = Self::create_vertex_buffer(&gl);
            /*let fb = gl
                .create_framebuffer()
                .expect("unable to create plane framebuffer");
            gl.bind_framebuffer(glow::FRAMEBUFFER, Some(fb));
            let fb_texture = gl.create_texture().unwrap();
            gl.bind_texture(glow::TEXTURE_2D, Some(fb_texture));
            gl.tex_image_2d(
                glow::TEXTURE_2D,
                0,
                glow::RGBA as i32,
                GAME_WIDTH as i32 * PLANE_SCALE as i32,
                GAME_HEIGHT as i32 * PLANE_SCALE as i32,
                0,
                glow::RGBA,
                glow::UNSIGNED_BYTE,
                None,
            );
            gl.tex_parameter_i32(
                glow::TEXTURE_2D,
                glow::TEXTURE_MIN_FILTER,
                glow::NEAREST as i32,
            );
            gl.tex_parameter_i32(
                glow::TEXTURE_2D,
                glow::TEXTURE_MAG_FILTER,
                glow::NEAREST as i32,
            );
            gl.framebuffer_texture_2d(
                glow::FRAMEBUFFER,
                glow::COLOR_ATTACHMENT0,
                glow::TEXTURE_2D,
                Some(fb_texture),
                0,
            );*/

            let mut frame_texture_handle_a = None;
            let mut frame_texture_handle_b = None;
            for handle in [&mut frame_texture_handle_a, &mut frame_texture_handle_b] {
                let texture_handle = gl.create_texture().unwrap();
                gl.bind_texture(glow::TEXTURE_2D, Some(texture_handle));
                gl.tex_image_2d(
                    glow::TEXTURE_2D,
                    0,
                    glow::RGBA as i32,
                    GAME_WIDTH as i32,
                    GAME_HEIGHT as i32,
                    0,
                    glow::RGBA,
                    glow::UNSIGNED_BYTE,
                    None,
                );
                gl.texture_parameter_i32(
                    texture_handle,
                    glow::TEXTURE_MIN_FILTER,
                    glow::NEAREST as i32,
                );
                gl.texture_parameter_i32(
                    texture_handle,
                    glow::TEXTURE_MAG_FILTER,
                    glow::NEAREST as i32,
                );
                gl.bind_texture(glow::TEXTURE_2D, None);
                *handle = Some(texture_handle);
            }

            Self {
                normal_program,
                // filter_program,
                vertex_array: vao,
                vertex_buffer: vbo,
                frame_texture_handle: frame_texture_handle_a.unwrap(),
                buffer_switch: false,
                filter: false,
            }
        }
    }

    fn get_current_program(&self) -> NativeProgram {
        /*if self.filter {
            self.filter_program
        } else {
            self.normal_program
        }*/
        self.normal_program
    }

    unsafe fn create_vertex_buffer(gl: &glow::Context) -> (NativeBuffer, NativeVertexArray) {
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

    unsafe fn use_vertex_buffer(&self, gl: &glow::Context) {
        gl.bind_buffer(glow::ARRAY_BUFFER, Some(self.vertex_buffer));
        gl.bind_vertex_array(Some(self.vertex_array));
        gl.enable_vertex_attrib_array(0);
        gl.enable_vertex_attrib_array(1);
    }

    unsafe fn set_uniform_float(&self, gl: &glow::Context, name: &str, value: f32) {
        let location = gl.get_uniform_location(self.get_current_program(), name);
        gl.uniform_1_f32(location.as_ref(), value);
    }

    unsafe fn set_uniform_vec2(&self, gl: &glow::Context, name: &str, x: f32, y: f32) {
        let location = gl.get_uniform_location(self.get_current_program(), name);
        gl.uniform_2_f32(location.as_ref(), x, y);
    }

    unsafe fn set_uniform_mat4(&self, gl: &glow::Context, name: &str, mat: &[f32]) {
        let location = gl.get_uniform_location(self.get_current_program(), name);
        gl.uniform_matrix_4_f32_slice(location.as_ref(), false, mat);
    }

    pub fn render(
        &mut self,
        gl: &glow::Context,
        window_size: &[f32; 2],
        contents: &Box<[u32]>,
        filter: bool,
        time: f32,
    ) {
        unsafe {
            self.filter = filter;

            let cur_texture = self.frame_texture_handle;
            gl.bind_texture(glow::TEXTURE_2D, Some(cur_texture));
            gl.tex_sub_image_2d(
                glow::TEXTURE_2D,
                0,
                0,
                0,
                GAME_WIDTH as i32,
                GAME_HEIGHT as i32,
                glow::RGBA,
                glow::UNSIGNED_BYTE,
                PixelUnpackData::Slice(std::slice::from_raw_parts(
                    contents.as_ptr() as *const u8,
                    contents.len() * 4,
                )),
            );
            gl.bind_texture(glow::TEXTURE_2D, None);
            self.buffer_switch = !self.buffer_switch;
            {
                gl.use_program(Some(self.get_current_program()));
                self.use_vertex_buffer(gl);
                // gl.bind_framebuffer(glow::FRAMEBUFFER, Some(self.frame_fb));
                let cur_location =
                    gl.get_uniform_location(self.get_current_program(), "CurTexture");

                gl.active_texture(glow::TEXTURE0);
                gl.bind_texture(glow::TEXTURE_2D, Some(cur_texture));

                gl.uniform_1_i32(cur_location.as_ref(), 0);
            }
            self.set_uniform_vec2(&gl, "WindowSize", window_size[0], window_size[1]);
            self.set_uniform_float(&gl, "iTime", time);
            gl.draw_arrays(glow::TRIANGLES, 0, 6);
            // gl.bind_framebuffer(glow::FRAMEBUFFER, None);
        }
    }

    pub fn destroy(&self, gl: &glow::Context) {
        unsafe {
            gl.delete_texture(self.frame_texture_handle);
            gl.delete_program(self.normal_program);
            gl.delete_vertex_array(self.vertex_array);
        }
    }
}
