#![no_std]
#![feature(adt_const_params)]
extern crate alloc;

use core::{
    cell::{LazyCell, OnceCell, UnsafeCell},
    marker::ConstParamTy,
};

use alloc::vec::Vec;

/*
   let src_dir = PathBuf::from(env::var("CARGO_MANIFEST_DIR").unwrap()).join("src");
   const CHANNEL_LOOKUP: [u32; 8] = [0, 52, 87, 116, 144, 172, 206, 255];
   let mut color_lut = vec![0u32; 0x1_0000];
   for i in 0..color_lut.len() {
       let r = CHANNEL_LOOKUP[(i >> 1) & 0b111];
       let g = CHANNEL_LOOKUP[(i >> 5) & 0b111];
       let b = CHANNEL_LOOKUP[(i >> 9) & 0b111];
       color_lut[i] = (0xff << 24) | (b << 16) | (g << 8) | (r << 0);
   }
   let mut out_lut = String::from("pub const COLOR_LUT: &[u32; 0x1_0000] = &[");
   for c in color_lut {
       out_lut += &format!("{:#010X},", c);
   }
   out_lut += "];";
   fs::write(src_dir.join("color_lut.rs"), out_lut).map_err(|e| e.to_string())?;
   Ok(())
*/

#[repr(transparent)]
pub struct SyncUnsafeCell<T>(UnsafeCell<T>);

unsafe impl<T: Sync> Sync for SyncUnsafeCell<T> {}

const CHANNEL_LOOKUP_RAW: [u32; 8] = [0, 52, 87, 116, 144, 172, 206, 255];

macro_rules! pal_index_to_32bit {
    ($pal:expr, $index:expr) => {{
        let i = $pal[($index & 0x3f) as usize] as usize;
        let r = CHANNEL_LOOKUP_RAW[(i >> 1) & 0b111];
        let g = CHANNEL_LOOKUP_RAW[(i >> 5) & 0b111];
        let b = CHANNEL_LOOKUP_RAW[(i >> 9) & 0b111];
        (0xff << 24) | (b << 16) | (g << 8) | (r << 0)
    }};
}

#[derive(Clone, Copy, ConstParamTy, PartialEq, Eq)]
enum PlaneRenderMode {
    Low = 0b01,
    High = 0b10,
    Both = 0b11,
}

#[derive(Clone, Copy, Debug)]
pub enum HScrollMode {
    FullScreen,
    PerTile,
    PerScanline,
}
impl From<u8> for HScrollMode {
    fn from(value: u8) -> Self {
        match value {
            0 => Self::FullScreen,
            1 => Self::PerTile,
            2 => Self::PerScanline,
            _ => Self::FullScreen,
        }
    }
}

#[derive(Clone, Copy, Debug)]
pub enum VScrollMode {
    FullScreen,
    PerTile,
    PerTwoTiles,
}
impl From<u8> for VScrollMode {
    fn from(value: u8) -> Self {
        match value {
            0 => Self::FullScreen,
            1 => Self::PerTile,
            2 => Self::PerTwoTiles,
            _ => Self::FullScreen,
        }
    }
}

#[derive(Clone, Copy, Debug)]
pub enum PlaneSize {
    Size32x32Cells,
    Size64x32Cells,
    Size128x32Cells,
    Size32x64Cells,
    Size64x64Cells,
    Size32x128Cells,
}
impl From<u8> for PlaneSize {
    fn from(value: u8) -> Self {
        match value {
            0 => Self::Size32x32Cells,
            1 => Self::Size64x32Cells,
            2 => Self::Size128x32Cells,
            3 => Self::Size32x64Cells,
            4 => Self::Size64x64Cells,
            5 => Self::Size32x128Cells,
            _ => Self::Size32x32Cells,
        }
    }
}

#[derive(Clone, Copy)]
pub struct TileAttributes {
    pub priority: bool,
    pub vertical_flip: bool,
    pub horizontal_flip: bool,
    pub palette_line: u8,
    pub tile_index: u16,
}
impl TileAttributes {
    pub fn new(word: u16) -> Self {
        Self {
            priority: (word & 0x8000) != 0,
            vertical_flip: (word & 0x1000) != 0,
            horizontal_flip: (word & 0x800) != 0,
            palette_line: ((word >> 9) & 0b11_0000) as u8,
            tile_index: (word & 0x7ff) as u16,
        }
    }
}

#[derive(Clone, Copy)]
pub struct Sprite {
    pub x: i16,
    pub y: i16,
    pub width_pixels: u16,
    pub height_pixels: u16,
    pub attributes: TileAttributes,
    pub next: u8,
}
impl Sprite {
    pub fn new(sprite_bytes: u64) -> Self {
        let long1 = (sprite_bytes >> 32) as u32;
        let long2 = sprite_bytes as u32;
        Self {
            x: long2 as i16 - 128,
            y: ((long1 >> 16) & 0x3ff) as i16 - 128,
            width_pixels: (((long1 >> 10) & 0b11) as u16 + 1) << 3,
            height_pixels: (((long1 >> 8) & 0b11) as u16 + 1) << 3,
            attributes: TileAttributes::new((long2 >> 16) as u16),
            next: (long1 & 0x7f) as u8,
        }
    }
    pub fn pattern_index_at_pos(&self, x: u16, y: u16) -> u16 {
        let x_off = (if self.attributes.horizontal_flip {
            self.width_pixels - x - 1
        } else {
            x
        } >> 3)
            * (self.height_pixels * 4);
        let y_off = y << 2;
        (self.attributes.tile_index << 5) + x_off + y_off
    }
}

const fn read_word(slice: &[u8]) -> u16 {
    unsafe { core::ptr::read::<u16>(slice.as_ptr() as *const u16).swap_bytes() }
}

const fn read_long(slice: &[u8]) -> u32 {
    unsafe { core::ptr::read::<u32>(slice.as_ptr() as *const u32).swap_bytes() }
}

const fn read_dlong(slice: &[u8]) -> u64 {
    unsafe { core::ptr::read::<u64>(slice.as_ptr() as *const u64).swap_bytes() }
}

pub fn render_sprites_line_low(
    pattern_data: &[u8],
    palette: &[u16; 64],
    sprite_table: &[u8],
    y: u16,
    line_width: u16,
    screen_buf: &mut [u32],
    hw_mode: bool,
) {
    render_sprites_line_common::<{ PlaneRenderMode::Low }>(
        sprite_table,
        pattern_data,
        palette,
        y,
        line_width,
        screen_buf,
        hw_mode,
    )
}

pub fn render_sprites_line_high(
    pattern_table: &[u8],
    palette: &[u16; 64],
    sprite_table: &[u8],
    y: u16,
    line_width: u16,
    screen_buf: &mut [u32],
    hw_mode: bool,
) {
    render_sprites_line_common::<{ PlaneRenderMode::High }>(
        sprite_table,
        pattern_table,
        palette,
        y,
        line_width,
        screen_buf,
        hw_mode,
    )
}

fn render_sprites_line_common<const MODE: PlaneRenderMode>(
    sprite_table: &[u8],
    pattern_data: &[u8],
    palette: &[u16; 64],
    y: u16,
    line_width: u16,
    screen_buf: &mut [u32],
    hw_mode: bool,
) {
    let hw_screen_buf = unsafe { core::mem::transmute::<&mut [u32], &mut [u8]>(screen_buf) };

    let mut cur_sprite_count = 0u8;
    let mut cur_sprite_pixel_count = 0u16;
    let mut cur_sprite_link = 0u8;

    while cur_sprite_count < 80 {
        let sprite = Sprite::new(read_dlong(
            &sprite_table[(((cur_sprite_link as u16) << 3) as usize)..],
        ));

        let sprite_in_y_range =
            (y as i16) >= sprite.y && (y as i16) < (sprite.y + (sprite.height_pixels as i16));
        if (sprite.attributes.priority && MODE != PlaneRenderMode::Low)
            || (!sprite.attributes.priority && MODE != PlaneRenderMode::High)
        {
            let sprite_viable_for_draw = sprite.x < line_width as i16
                && sprite.x + sprite.width_pixels as i16 >= 0
                && sprite_in_y_range;

            if sprite_viable_for_draw {
                let draw_y = if sprite.attributes.vertical_flip {
                    sprite.height_pixels - ((y as i16) - sprite.y) as u16 - 1
                } else {
                    ((y as i16) - sprite.y) as u16
                };
                let mut draw_x = if sprite.x >= 0 {
                    0u16
                } else {
                    sprite.x.abs() as u16
                };
                let draw_x_end = if (sprite.x + (sprite.width_pixels as i16)) < (line_width as i16)
                {
                    sprite.width_pixels as i16
                } else {
                    (sprite.width_pixels as i16)
                        - ((sprite.x + (sprite.width_pixels as i16)) - (line_width as i16))
                } as u16;
                while draw_x < draw_x_end {
                    let pattern_strip = read_long(
                        &pattern_data[(sprite.pattern_index_at_pos(draw_x, draw_y) as usize)..],
                    );

                    let cell_x = if !sprite.attributes.horizontal_flip {
                        8 - (draw_x & 7) - 1
                    } else {
                        draw_x & 7
                    };
                    let index = ((pattern_strip >> (cell_x << 2)) & 0xf) as u8;
                    if index != 0 {
                        let buf_index = (sprite.x + draw_x as i16) as usize;
                        if buf_index < line_width as usize {
                            if hw_mode {
                                if hw_screen_buf[buf_index] == 0 {
                                    hw_screen_buf[buf_index] =
                                        sprite.attributes.palette_line | index;
                                }
                            } else {
                                if screen_buf[buf_index] == 0 {
                                    screen_buf[buf_index] = pal_index_to_32bit!(
                                        palette,
                                        sprite.attributes.palette_line | index
                                    );
                                }
                            }
                        }
                    }

                    draw_x += 1;
                }
            }
        }
        cur_sprite_link = sprite.next;
        if sprite_in_y_range {
            cur_sprite_pixel_count += sprite.width_pixels;
        }

        if cur_sprite_pixel_count >= 320 || cur_sprite_link == 0 {
            break;
        }

        cur_sprite_count = cur_sprite_count.wrapping_add(1);
    }
}

pub fn render_plane_line_a_high(
    y: u16,
    line_width: u16,
    pattern_data: &[u8],
    palette: &[u16; 64],
    plane_size: PlaneSize,
    plane_a_nametable: &[u8],
    hscroll_buffer: &[u8],
    vscroll_buffer: &[u16; 80 / 2],
    vscroll_mode: VScrollMode,
    screen_buf: &mut [u32],
    hw_mode: bool,
) {
    render_plane_line_common::<true, { PlaneRenderMode::High }>(
        y,
        line_width,
        pattern_data,
        palette,
        plane_size,
        plane_a_nametable,
        hscroll_buffer,
        vscroll_buffer,
        vscroll_mode,
        screen_buf,
        hw_mode,
    )
}

pub fn render_plane_line_a_low(
    y: u16,
    line_width: u16,
    pattern_data: &[u8],
    palette: &[u16; 64],
    plane_size: PlaneSize,
    plane_a_nametable: &[u8],
    hscroll_buffer: &[u8],
    vscroll_buffer: &[u16; 80 / 2],
    vscroll_mode: VScrollMode,
    screen_buf: &mut [u32],
    hw_mode: bool,
) {
    render_plane_line_common::<true, { PlaneRenderMode::Low }>(
        y,
        line_width,
        pattern_data,
        palette,
        plane_size,
        plane_a_nametable,
        hscroll_buffer,
        vscroll_buffer,
        vscroll_mode,
        screen_buf,
        hw_mode,
    )
}

pub fn render_plane_line_b_high(
    y: u16,
    line_width: u16,
    pattern_data: &[u8],
    palette: &[u16; 64],
    plane_size: PlaneSize,
    plane_b_nametable: &[u8],
    hscroll_buffer: &[u8],
    vscroll_buffer: &[u16; 80 / 2],
    vscroll_mode: VScrollMode,
    screen_buf: &mut [u32],
    hw_mode: bool,
) {
    render_plane_line_common::<false, { PlaneRenderMode::High }>(
        y,
        line_width,
        pattern_data,
        palette,
        plane_size,
        plane_b_nametable,
        hscroll_buffer,
        vscroll_buffer,
        vscroll_mode,
        screen_buf,
        hw_mode,
    )
}

pub fn render_plane_line_b_low(
    y: u16,
    line_width: u16,
    pattern_data: &[u8],
    palette: &[u16; 64],
    plane_size: PlaneSize,
    plane_b_nametable: &[u8],
    hscroll_buffer: &[u8],
    vscroll_buffer: &[u16; 80 / 2],
    vscroll_mode: VScrollMode,
    screen_buf: &mut [u32],
    hw_mode: bool,
) {
    render_plane_line_common::<false, { PlaneRenderMode::Low }>(
        y,
        line_width,
        pattern_data,
        palette,
        plane_size,
        plane_b_nametable,
        hscroll_buffer,
        vscroll_buffer,
        vscroll_mode,
        screen_buf,
        hw_mode,
    )
}

fn render_plane_line_common<const PLANEA: bool, const MODE: PlaneRenderMode>(
    y: u16,
    line_width: u16,
    pattern_data: &[u8],
    palette: &[u16; 64],
    plane_size: PlaneSize,
    plane_nametable: &[u8],
    hscroll_buffer: &[u8],
    vscroll_buffer: &[u16; 80 / 2],
    vscroll_mode: VScrollMode,
    screen_buf: &mut [u32],
    hw_mode: bool,
) {
    let hw_screen_buf = unsafe { core::mem::transmute::<&mut [u32], &mut [u8]>(screen_buf) };
    let (plane_size_cells_mask_x, plane_size_cells_mask_y) = {
        match plane_size {
            PlaneSize::Size32x32Cells => (32 - 1, 32 - 1),
            PlaneSize::Size64x32Cells => (64 - 1, 32 - 1),
            PlaneSize::Size128x32Cells => (128 - 1, 32 - 1),
            PlaneSize::Size32x64Cells => (32 - 1, 64 - 1),
            PlaneSize::Size64x64Cells => (64 - 1, 64 - 1),
            PlaneSize::Size32x128Cells => (32 - 1, 128 - 1),
        }
    };
    let scroll_x = if PLANEA {
        (-(read_word(&hscroll_buffer[(y.wrapping_mul(4) as usize)..]) as i16)).wrapping_add(8)
            as u16
    } else {
        (-(read_word(&hscroll_buffer[(y.wrapping_mul(4).wrapping_add(2) as usize)..]) as i16))
            .wrapping_add(8) as u16
    };
    let scroll_x_within_tile = (scroll_x & 0x7) as u16;

    for cur_cell_x in 0u16..((line_width / 8) + 1) {
        let scroll_y = {
            let x = match vscroll_mode {
                VScrollMode::FullScreen => 0,
                VScrollMode::PerTile => cur_cell_x,
                VScrollMode::PerTwoTiles => cur_cell_x >> 1,
            };
            if PLANEA {
                vscroll_buffer[(x >> 1) as usize]
            } else {
                vscroll_buffer[(x.wrapping_add(2) >> 1) as usize]
            }
        };

        let pos_x_cells = (cur_cell_x.wrapping_sub(1) << 3).wrapping_add(scroll_x) >> 3;
        let pos_y_cells = y.wrapping_add(scroll_y) >> 3;
        let cur_cell = TileAttributes::new(read_word(
            &plane_nametable[((pos_y_cells & plane_size_cells_mask_y)
                .wrapping_mul(plane_size_cells_mask_x + 1)
                .wrapping_add(pos_x_cells & plane_size_cells_mask_x)
                .wrapping_shl(1) as usize)..],
        ));
        let buf_index = (cur_cell_x << 3) as usize;
        if (cur_cell.priority && MODE == PlaneRenderMode::Low)
            || (!cur_cell.priority && MODE == PlaneRenderMode::High)
        {
            continue;
        }
        let mut pixel_y = ((y.wrapping_add(scroll_y)) % 8) as u8;
        if cur_cell.vertical_flip {
            pixel_y = 8 - pixel_y - 1;
        }
        let pattern_strip = read_long(
            &pattern_data[((((cur_cell.tile_index as usize) & 0x7ff).wrapping_shl(5))
                .wrapping_add((pixel_y.wrapping_shl(2)) as usize))..],
        );

        if cur_cell.horizontal_flip {
            for p_x in 0..8 {
                let buf_index = buf_index
                    .wrapping_add(p_x)
                    .wrapping_sub(scroll_x_within_tile as usize);
                if buf_index < (line_width as usize) {
                    let index = ((pattern_strip >> (p_x << 2)) & 0xf) as u8;
                    if hw_mode {
                        hw_screen_buf[buf_index] = cur_cell.palette_line | index;
                    } else {
                        if screen_buf[buf_index] == 0 {
                            if index != 0 {
                                screen_buf[buf_index] =
                                    pal_index_to_32bit!(palette, cur_cell.palette_line | index);
                            }
                        }
                    }
                }
            }
        } else {
            for p_x in 0..8 {
                let buf_index = buf_index
                    .wrapping_add(p_x)
                    .wrapping_sub(scroll_x_within_tile as usize);
                if buf_index < (line_width as usize) {
                    let p_x = 8 - p_x - 1;
                    let index = ((pattern_strip >> (p_x << 2)) & 0xf) as u8;
                    if hw_mode {
                        hw_screen_buf[buf_index] = cur_cell.palette_line | index;
                    } else {
                        if screen_buf[buf_index] == 0 {
                            if index != 0 {
                                screen_buf[buf_index] =
                                    pal_index_to_32bit!(palette, cur_cell.palette_line | index);
                            }
                        }
                    }
                }
            }
        }
    }
}

pub fn render_screen_line(
    pattern_data: &[u8],
    palette: &[u16; 64],
    bg_color_index: u8,
    plane_a_nametable: &[u8],
    plane_b_nametable: &[u8],
    hscroll_buffer: &[u8],
    sprite_table: &[u8],
    vscroll_buffer: &[u16; 80 / 2],
    vscroll_mode: VScrollMode,
    y: u16,
    line_width: u16,
    plane_size: PlaneSize,
    fb: &mut [u32],
) {
    fb.fill(0);
    render_sprites_line_high(
        &pattern_data,
        &palette,
        sprite_table,
        y,
        line_width,
        fb,
        false,
    );
    render_plane_line_a_high(
        y,
        line_width,
        &pattern_data,
        &palette,
        plane_size,
        plane_a_nametable,
        hscroll_buffer,
        &vscroll_buffer,
        vscroll_mode,
        fb,
        false,
    );
    render_plane_line_b_high(
        y,
        line_width,
        &pattern_data,
        &palette,
        plane_size,
        plane_b_nametable,
        hscroll_buffer,
        &vscroll_buffer,
        vscroll_mode,
        fb,
        false,
    );
    render_sprites_line_low(
        &pattern_data,
        &palette,
        sprite_table,
        y,
        line_width,
        fb,
        false,
    );
    render_plane_line_a_low(
        y,
        line_width,
        &pattern_data,
        &palette,
        plane_size,
        plane_a_nametable,
        hscroll_buffer,
        &vscroll_buffer,
        vscroll_mode,
        fb,
        false,
    );
    render_plane_line_b_low(
        y,
        line_width,
        &pattern_data,
        &palette,
        plane_size,
        plane_b_nametable,
        hscroll_buffer,
        &vscroll_buffer,
        vscroll_mode,
        fb,
        false,
    );
    for p in fb {
        if *p == 0 {
            *p = pal_index_to_32bit!(palette, bg_color_index);
        }
    }
}
