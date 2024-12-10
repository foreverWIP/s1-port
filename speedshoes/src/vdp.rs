use std::{cell::RefCell, rc::Rc};

use crate::{GAME_HEIGHT, GAME_WIDTH};

#[derive(Clone, Copy)]
pub(crate) enum HScrollMode {
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

#[derive(Clone, Copy)]
pub(crate) enum VScrollMode {
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

#[derive(Clone, Copy)]
pub(crate) enum PlaneSize {
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
pub(crate) enum VdpRegion {
    Vram,
    Cram,
    Vsram,
}

type VdpPtr = (bool, VdpRegion, u32);

#[derive(Clone, Copy, PartialEq)]
enum DmaType {
    CpuToVram,
    VramFill,
    VramToVram,
}

#[derive(Clone, Copy)]
struct TileAttributes {
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
struct Sprite {
    pub x: i16,
    pub y: i16,
    pub width_pixels: u16,
    pub height_pixels: u16,
    pub attributes: TileAttributes,
    pub next: u8,
}
impl Sprite {
    pub fn new(vram: &Box<[u8; VRAM_SIZE_BYTES]>, address: u16) -> Self {
        let address = address as usize;
        let long1 = ((vram[address as usize + 0] as u32) << 24)
            | ((vram[address as usize + 1] as u32) << 16)
            | ((vram[address as usize + 2] as u32) << 8)
            | (vram[address as usize + 3] as u32);
        let long2 = ((vram[address as usize + 4] as u32) << 24)
            | ((vram[address as usize + 5] as u32) << 16)
            | ((vram[address as usize + 6] as u32) << 8)
            | (vram[address as usize + 7] as u32);
        Self {
            x: (long2 & 0x1ff) as i16 - 128,
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

#[derive(Clone, Copy, Eq, PartialEq, Hash)]
pub enum PlaneToRender {
    PlaneBLow,
    PlaneALow,
    SpriteLow,
    PlaneBHigh,
    PlaneAHigh,
    SpriteHigh,
}

const CHANNEL_LOOKUP: [u32; 8] = [0, 52, 87, 116, 144, 172, 206, 255];

pub const VRAM_SIZE_BYTES: usize = 0x1_0000;

#[derive(Clone, Copy, Debug)]
pub struct VdpPerLineState {
    palette: [u16; 64],
}
impl VdpPerLineState {
    pub fn swap_state(&mut self, vdp: &mut Vdp) {
        let backup = vdp.palette.clone();
        vdp.palette.copy_from_slice(&self.palette);
        self.palette = backup;
    }
}

macro_rules! pal_index_to_32bit {
    ($vdp:expr, $index:expr) => {
        pal_index_to_32bit!($vdp, $vdp.palette, $index)
    };
    ($vdp:expr, $pal:expr, $index:expr) => {
        $vdp.color_lut[$pal[($index & 0x3f) as usize] as usize]
    };
}

pub struct Vdp {
    pub(crate) vram: Box<[u8; VRAM_SIZE_BYTES]>,
    /// Mask the high bit of each color channel.
    /// 3-bit color -> 2-bit color
    pub low_color_mode: bool,
    /// When false, only displays a solid color
    /// (the current background color).
    show_planes_and_sprites: bool,
    pub(crate) plane_a_location: u16,
    pub(crate) plane_b_location: u16,
    pub(crate) sprite_table_location: u16,
    pub bg_color_index: u8,
    pub(crate) hscroll_mode: HScrollMode,
    pub(crate) vscroll_mode: VScrollMode,
    pub(crate) vscroll_buffer: [u16; 80 / 2],
    pub(crate) hscroll_location: u16,
    increment_value: u8,
    pub(crate) plane_size: PlaneSize,
    pub(crate) dst_ptr: VdpPtr,
    pub(crate) palette: [u16; 64],
    per_line_state: Box<[Option<VdpPerLineState>; GAME_HEIGHT as usize]>,
    color_lut: Box<[u32; 0x1_0000]>,
    dma_length: u16,
    dma_src: u32,
    dma_type: DmaType,
    dma_vram_fill_ready: bool,
    ctrl_cachedword: Option<u16>,
    vint_enabled: bool,
    disable_display: bool,
    rom: Rc<Vec<u8>>,
    ram: Rc<RefCell<Vec<u8>>>,
}
impl Vdp {
    pub fn new(rom: Rc<Vec<u8>>, ram: Rc<RefCell<Vec<u8>>>) -> Vdp {
        let mut color_lut = vec![0u32; 0x1_0000].into_boxed_slice();
        for i in 0..color_lut.len() {
            let r = CHANNEL_LOOKUP[(i >> 1) & 0b111];
            let g = CHANNEL_LOOKUP[(i >> 5) & 0b111];
            let b = CHANNEL_LOOKUP[(i >> 9) & 0b111];
            color_lut[i] = (0xff << 24) | (b << 16) | (g << 8) | (r << 0);
        }
        Vdp {
            vram: vec![0u8; VRAM_SIZE_BYTES]
                .into_boxed_slice()
                .try_into()
                .unwrap(),
            low_color_mode: false,
            show_planes_and_sprites: false,
            plane_a_location: 0,
            plane_b_location: 0,
            sprite_table_location: 0,
            bg_color_index: 0,
            hscroll_mode: HScrollMode::FullScreen,
            vscroll_mode: VScrollMode::FullScreen,
            vscroll_buffer: [0u16; 80 / 2],
            hscroll_location: 0,
            increment_value: 2,
            plane_size: PlaneSize::Size64x32Cells,
            dst_ptr: (false, VdpRegion::Vram, 0),
            per_line_state: vec![None; GAME_HEIGHT as usize]
                .into_boxed_slice()
                .try_into()
                .unwrap(),
            palette: [0; 64],
            color_lut: color_lut.try_into().unwrap(),
            dma_length: 0,
            dma_src: 0,
            dma_type: DmaType::CpuToVram,
            dma_vram_fill_ready: false,
            ctrl_cachedword: None,
            vint_enabled: false,
            disable_display: false,
            ram,
            rom,
        }
    }

    pub fn show_planes_and_sprites(&self) -> bool {
        self.show_planes_and_sprites
    }

    pub fn display_enabled(&self) -> bool {
        !self.disable_display
    }

    pub fn bg_color(&self) -> u32 {
        pal_index_to_32bit!(self, self.bg_color_index)
    }

    pub fn clear_all_vram(&mut self) {
        self.vram.fill(0);
    }

    pub fn clear_all_cram(&mut self) {
        self.palette.fill(0);
    }

    pub fn clear_all_vsram(&mut self) {
        self.vscroll_buffer.fill(0);
    }

    pub fn set_plane_a_location(&mut self, loc: u16) {
        self.plane_a_location = loc;
    }

    pub fn set_plane_b_location(&mut self, loc: u16) {
        self.plane_b_location = loc;
    }

    pub fn set_bg_color_index(&mut self, index: u8) {
        self.bg_color_index = index & 0x3f;
    }

    pub fn seek_vram(&mut self, loc: u16) {
        self.dst_ptr = (false, VdpRegion::Vram, loc as u32);
    }

    pub fn plane_size_cells(&self) -> (u8, u8) {
        match self.plane_size {
            PlaneSize::Size32x32Cells => (32, 32),
            PlaneSize::Size64x32Cells => (64, 32),
            PlaneSize::Size128x32Cells => (128, 32),
            PlaneSize::Size32x64Cells => (32, 64),
            PlaneSize::Size64x64Cells => (64, 64),
            PlaneSize::Size32x128Cells => (32, 128),
        }
    }

    pub fn handle_reg_write(&mut self, reg_value: u16) {
        let reg_num = (reg_value >> 8) as u8;
        let value = reg_value & 0xff;
        match reg_num {
            0x80 => {
                self.disable_display = (value & 1) != 0;
            }
            0x81 => {
                self.show_planes_and_sprites = (value & 0b0100_0000) != 0;
                self.vint_enabled = (value & 0b10_0000) != 0;
            }
            0x82 => {
                self.plane_a_location = value * 0x400;
            }
            0x84 => {
                self.plane_b_location = value * 0x2000;
            }
            0x85 => {
                self.sprite_table_location = value << 9;
            }
            0x87 => {
                self.bg_color_index = value as u8;
            }
            0x8b => {
                self.hscroll_mode = match value & 0b11 {
                    0b10 => HScrollMode::PerTile,
                    0b11 => HScrollMode::PerScanline,
                    _ => HScrollMode::FullScreen,
                };
            }
            0x8d => {
                self.hscroll_location = value * 0x400;
            }
            0x8f => {
                self.increment_value = value as u8;
            }
            0x90 => {
                self.plane_size = match value {
                    0b00_00_00 => PlaneSize::Size32x32Cells,
                    0b00_00_01 => PlaneSize::Size64x32Cells,
                    0b00_00_11 => PlaneSize::Size128x32Cells,
                    0b01_00_00 => PlaneSize::Size32x64Cells,
                    0b01_00_01 => PlaneSize::Size64x64Cells,
                    0b11_00_00 => PlaneSize::Size32x128Cells,
                    _ => panic!("invalid plane size {:#06b}", value),
                };
            }
            0x93 => {
                self.dma_length = (self.dma_length & 0xff00) | value;
            }
            0x94 => {
                self.dma_length = (self.dma_length & 0x00ff) | (value << 8);
            }
            0x95 => {
                self.dma_src = (self.dma_src & 0x1ff_fe00) | ((value as u32) << 1);
            }
            0x96 => {
                self.dma_src = (self.dma_src & 0x1fe_01fe) | ((value as u32) << 9);
            }
            0x97 => {
                self.dma_src = (self.dma_src & 0x01fffe) | (((value as u32) & 0b0011_1111) << 17);
                match value >> 6 {
                    0b00 => {
                        self.dma_type = DmaType::CpuToVram;
                    }
                    0b01 => {
                        self.dma_type = DmaType::CpuToVram;
                        self.dma_src |= 0x80_0000;
                    }
                    0b10 => {
                        self.dma_type = DmaType::VramFill;
                    }
                    0b11 => {
                        self.dma_type = DmaType::VramToVram;
                    }

                    _ => panic!("unknown dma source?!"),
                }
            }

            _ => {}
        }
    }

    fn read_memory_simple(&self, address: u32) -> u8 {
        if (address as usize) < self.rom.len() {
            // ROM
            self.rom[address as usize]
        } else if address >= 0xff_0000 {
            // RAM
            self.ram.borrow()[(address - 0xff_0000) as usize]
        } else {
            panic!("can't read from here with _simple");
        }
    }

    fn do_dma(&mut self, prep_value: u32) {
        match self.dma_type {
            DmaType::CpuToVram => {
                let cd12 = (prep_value >> 31) | ((prep_value >> 3) & 0b10);
                match cd12 {
                    0 => {
                        for i in 0..(self.dma_length * (self.increment_value as u16)) {
                            self.write_vram(
                                self.dst_ptr.2.wrapping_add(i as u32) as u16,
                                self.read_memory_simple(self.dma_src + (i as u32)),
                            );
                        }
                    }
                    1 => {
                        for i in 0..(self.dma_length * (self.increment_value as u16)) {
                            self.write_cram(
                                (self.dst_ptr.2 + (i as u32)) as u8,
                                self.read_memory_simple(self.dma_src + (i as u32)),
                            );
                        }
                    }
                    2 => {
                        for i in 0..(self.dma_length * (self.increment_value as u16)) {
                            self.write_vsram(
                                (self.dst_ptr.2 + (i as u32)) as u8,
                                self.read_memory_simple(self.dma_src + (i as u32)),
                            );
                        }
                    }
                    _ => panic!("unknown dma type (cpu to vram) ?!"),
                }
                self.dst_ptr.2 = self
                    .dst_ptr
                    .2
                    .wrapping_add((self.dma_length * (self.increment_value as u16)) as u32);
            }
            DmaType::VramFill => {
                for i in 0..(self.dma_length) {
                    self.write_vram(
                        self.dst_ptr.2.wrapping_add(i as u32) as u16,
                        (prep_value >> 8) as u8,
                    );
                }
            }
            DmaType::VramToVram => {}
        }
    }

    fn decode_ptr(prep_value: u32) -> VdpPtr {
        let cd10 = (prep_value >> 30) & 0b11;
        let cd32 = (prep_value >> 2) & 0b1100;
        let a1514 = ((prep_value & 0b11) << 14) as u16;
        let a130 = ((prep_value >> 16) & 0x3fff) as u16;
        let address: u16 = a1514 | a130;
        match cd10 | cd32 {
            0b0000 => (true, VdpRegion::Vram, address as u32),
            0b0001 => (false, VdpRegion::Vram, address as u32),
            0b1000 => (true, VdpRegion::Cram, (address as u8) as u32),
            0b0011 => (false, VdpRegion::Cram, (address as u8) as u32),
            0b0100 => (true, VdpRegion::Vsram, address as u32),
            0b0101 => (false, VdpRegion::Vsram, address as u32),
            _ => panic!("unknown vdp ptr?!"),
        }
    }

    pub fn handle_control_word(&mut self, word: u16) {
        let mut prep_value: u32 = word as u32;
        let mut should_start_dma = false;
        match self.ctrl_cachedword {
            Some(cachedword) => {
                prep_value |= (cachedword as u32) << 16;
                should_start_dma = (prep_value & 0x80) != 0;
                self.dst_ptr = Self::decode_ptr(prep_value);
                self.ctrl_cachedword = None;
            }
            None => self.ctrl_cachedword = Some(word),
        }

        if should_start_dma {
            if self.dma_type == DmaType::VramFill {
                self.dma_vram_fill_ready = true;
            } else {
                self.do_dma(prep_value);
            }
        }
    }

    fn write_vsram(&mut self, address: u8, value: u8) {
        Self::write_byte_to_word_slice(&mut self.vscroll_buffer, address as u16, value);
    }

    fn write_cram(&mut self, address: u8, value: u8) {
        Self::write_byte_to_word_slice(&mut self.palette, address as u16, value);
    }

    fn write_byte_to_word_slice(slice: &mut [u16], address: u16, value: u8) {
        match address & 1 {
            0 => {
                slice[(address / 2) as usize] =
                    (slice[(address / 2) as usize] & 0x00ff) | ((value as u16) << 8)
            }
            1 => {
                slice[(address / 2) as usize] =
                    (slice[(address / 2) as usize] & 0xff00) | ((value as u16) << 0)
            }
            _ => unreachable!(),
        }
    }

    fn read_vram_word(&self, address: u16) -> u16 {
        ((self.vram[address as usize] as u16) << 8) | (self.vram[address as usize + 1] as u16)
    }

    fn read_vram_long(&self, address: u16) -> u32 {
        ((self.vram[address as usize] as u32) << 24)
            | ((self.vram[address as usize + 1] as u32) << 16)
            | ((self.vram[address as usize + 2] as u32) << 8)
            | (self.vram[address as usize + 3] as u32)
    }

    fn write_vram(&mut self, address: u16, value: u8) {
        self.vram[address as usize] = value;
    }

    pub fn handle_data_write_byte(&mut self, offset: u16, value: u8) {
        match self.dst_ptr.1 {
            VdpRegion::Vram => {
                if !self.dst_ptr.0 {
                    self.write_vram((self.dst_ptr.2 + (offset as u32)) as u16, value);
                }
            }
            VdpRegion::Cram => {
                if !self.dst_ptr.0 {
                    self.write_cram((self.dst_ptr.2 + (offset as u32)) as u8, value);
                }
            }
            VdpRegion::Vsram => {
                if !self.dst_ptr.0 {
                    self.write_vsram((self.dst_ptr.2 + (offset as u32)) as u8, value);
                }
            }
        }
    }

    pub fn handle_data_write(&mut self, value: u16, inc_ptr: bool) {
        if self.dma_vram_fill_ready && self.dma_type == DmaType::VramFill {
            self.do_dma(value as u32);
            self.dma_vram_fill_ready = false;
        } else {
            self.handle_data_write_byte(0, (value >> 8) as u8);
            self.handle_data_write_byte(1, value as u8);
            if inc_ptr {
                self.dst_ptr.2 = self.dst_ptr.2.wrapping_add(self.increment_value as u32);
            }
        }
    }

    fn render_sprites_line(&self, y: u16, screen_buf_low: &mut [u32], screen_buf_high: &mut [u32]) {
        let mut cur_sprite_count = 0u8;
        let mut cur_sprite_pixel_count = 0u16;
        let mut cur_sprite_link = 0u8;
        while cur_sprite_count < 80 {
            let sprite = Sprite::new(
                &self.vram,
                self.sprite_table_location + ((cur_sprite_link as u16) << 3),
            );

            let fb = if sprite.attributes.priority {
                &mut *screen_buf_high
            } else {
                &mut *screen_buf_low
            };

            let sprite_in_y_range =
                (y as i16) >= sprite.y && (y as i16) < (sprite.y + (sprite.height_pixels as i16));
            let sprite_viable_for_draw = sprite.x < GAME_WIDTH as i16
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
                let draw_x_end = if (sprite.x + (sprite.width_pixels as i16)) < (GAME_WIDTH as i16)
                {
                    sprite.width_pixels as i16
                } else {
                    (sprite.width_pixels as i16)
                        - ((sprite.x + (sprite.width_pixels as i16)) - (GAME_WIDTH as i16))
                } as u16;
                while draw_x < draw_x_end {
                    let pattern_strip =
                        self.read_vram_long(sprite.pattern_index_at_pos(draw_x, draw_y));

                    let cell_x = if !sprite.attributes.horizontal_flip {
                        8 - (draw_x & 7) - 1
                    } else {
                        draw_x & 7
                    };
                    let index = ((pattern_strip >> (cell_x << 2)) & 0xf) as u8;

                    if index != 0 {
                        let buf_index = (sprite.x + draw_x as i16) as usize;
                        if buf_index < GAME_WIDTH as usize {
                            if fb[buf_index] == 0 {
                                fb[buf_index] = pal_index_to_32bit!(
                                    self,
                                    sprite.attributes.palette_line | index
                                );
                            }
                        }
                    }

                    draw_x += 1;
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

    fn render_plane_line_b(&self, screen_buf_low: &mut [u32], y: u16) {
        let (plane_size_cells_mask_x, plane_size_cells_mask_y) = {
            match self.plane_size {
                PlaneSize::Size32x32Cells => (32 - 1, 32 - 1),
                PlaneSize::Size64x32Cells => (64 - 1, 32 - 1),
                PlaneSize::Size128x32Cells => (128 - 1, 32 - 1),
                PlaneSize::Size32x64Cells => (32 - 1, 64 - 1),
                PlaneSize::Size64x64Cells => (64 - 1, 64 - 1),
                PlaneSize::Size32x128Cells => (32 - 1, 128 - 1),
            }
        };
        let scroll_x = (-(self.read_vram_word(
            self.hscroll_location
                .wrapping_add(y.wrapping_mul(4).wrapping_add(2)),
        ) as i16))
            .wrapping_add(8) as u16;
        let scroll_x_within_tile = (scroll_x & 0x7) as u16;

        let plane_location = self.plane_b_location;

        let clear_color = self.bg_color();

        for cur_cell_x in 0u16..41 {
            let scroll_y = {
                let x = match self.vscroll_mode {
                    VScrollMode::FullScreen => 0,
                    VScrollMode::PerTile => cur_cell_x,
                    VScrollMode::PerTwoTiles => cur_cell_x >> 1,
                };
                self.vscroll_buffer[(x.wrapping_add(2) >> 1) as usize]
            };

            let pos_x_cells = (cur_cell_x.wrapping_sub(1) << 3).wrapping_add(scroll_x) >> 3;
            let pos_y_cells = y.wrapping_add(scroll_y) >> 3;
            let cur_cell = TileAttributes::new(
                self.read_vram_word(
                    plane_location.wrapping_add(
                        (pos_y_cells & plane_size_cells_mask_y)
                            .wrapping_mul(plane_size_cells_mask_x + 1)
                            .wrapping_add(pos_x_cells & plane_size_cells_mask_x)
                            .wrapping_shl(1),
                    ),
                ),
            );
            let fb_primary = &mut *screen_buf_low;
            let mut pixel_y = ((y + scroll_y) % 8) as u8;
            if cur_cell.vertical_flip {
                pixel_y = 8 - pixel_y - 1;
            }
            let pattern_strip = self.read_vram_long(
                ((((cur_cell.tile_index as usize) & 0x7ff).wrapping_shl(5))
                    .wrapping_add((pixel_y.wrapping_shl(2)) as usize)) as u16,
            );

            let buf_index = (cur_cell_x << 3) as usize;
            if cur_cell.horizontal_flip {
                for p_x in 0..8 {
                    let buf_index = buf_index
                        .wrapping_add(p_x)
                        .wrapping_sub(scroll_x_within_tile as usize);
                    if buf_index < (GAME_WIDTH as usize) {
                        let index = ((pattern_strip >> (p_x << 2)) & 0xf) as u8;

                        if index != 0 {
                            fb_primary[buf_index] =
                                pal_index_to_32bit!(self, cur_cell.palette_line | index);
                        } else {
                            fb_primary[buf_index] = clear_color;
                        }
                    }
                }
            } else {
                for p_x in 0..8 {
                    let buf_index = buf_index
                        .wrapping_add(p_x)
                        .wrapping_sub(scroll_x_within_tile as usize);
                    if buf_index < (GAME_WIDTH as usize) {
                        let p_x = 8 - p_x - 1;

                        let index = ((pattern_strip >> (p_x << 2)) & 0xf) as u8;

                        if index != 0 {
                            fb_primary[buf_index] =
                                pal_index_to_32bit!(self, cur_cell.palette_line | index);
                        } else {
                            fb_primary[buf_index] = clear_color;
                        }
                    }
                }
            }
        }
    }

    fn render_plane_line_a(&self, screen_buf_low: &mut [u32], screen_buf_high: &mut [u32], y: u16) {
        let (plane_size_cells_mask_x, plane_size_cells_mask_y) = {
            match self.plane_size {
                PlaneSize::Size32x32Cells => (32 - 1, 32 - 1),
                PlaneSize::Size64x32Cells => (64 - 1, 32 - 1),
                PlaneSize::Size128x32Cells => (128 - 1, 32 - 1),
                PlaneSize::Size32x64Cells => (32 - 1, 64 - 1),
                PlaneSize::Size64x64Cells => (64 - 1, 64 - 1),
                PlaneSize::Size32x128Cells => (32 - 1, 128 - 1),
            }
        };
        let scroll_x = (-(self.read_vram_word(self.hscroll_location.wrapping_add(y.wrapping_mul(4)))
            as i16))
            .wrapping_add(8) as u16;
        let scroll_x_within_tile = (scroll_x & 0x7) as u16;

        for cur_cell_x in 0u16..41 {
            let scroll_y = {
                let x = match self.vscroll_mode {
                    VScrollMode::FullScreen => 0,
                    VScrollMode::PerTile => cur_cell_x,
                    VScrollMode::PerTwoTiles => cur_cell_x >> 1,
                };
                self.vscroll_buffer[(x >> 1) as usize]
            };

            let pos_x_cells = (cur_cell_x.wrapping_sub(1) << 3).wrapping_add(scroll_x) >> 3;
            let pos_y_cells = y.wrapping_add(scroll_y) >> 3;
            let cur_cell = TileAttributes::new(
                self.read_vram_word(
                    self.plane_a_location.wrapping_add(
                        (pos_y_cells & plane_size_cells_mask_y)
                            .wrapping_mul(plane_size_cells_mask_x + 1)
                            .wrapping_add(pos_x_cells & plane_size_cells_mask_x)
                            .wrapping_shl(1),
                    ),
                ),
            );
            let (fb_primary, fb_secondary) = if cur_cell.priority {
                (&mut *screen_buf_high, &mut *screen_buf_low)
            } else {
                (&mut *screen_buf_low, &mut *screen_buf_high)
            };
            let mut pixel_y = ((y + scroll_y) % 8) as u8;
            if cur_cell.vertical_flip {
                pixel_y = 8 - pixel_y - 1;
            }
            let pattern_strip = self.read_vram_long(
                ((((cur_cell.tile_index as usize) & 0x7ff).wrapping_shl(5))
                    .wrapping_add((pixel_y.wrapping_shl(2)) as usize)) as u16,
            );

            let buf_index = (cur_cell_x << 3) as usize;
            if cur_cell.horizontal_flip {
                for p_x in 0..8 {
                    let buf_index = buf_index
                        .wrapping_add(p_x)
                        .wrapping_sub(scroll_x_within_tile as usize);
                    if buf_index < (GAME_WIDTH as usize) {
                        let index = ((pattern_strip >> (p_x << 2)) & 0xf) as u8;

                        if index != 0 {
                            fb_primary[buf_index] =
                                pal_index_to_32bit!(self, cur_cell.palette_line | index);
                        } else {
                            fb_primary[buf_index] = 0;
                        }
                        fb_secondary[buf_index] = 0;
                    }
                }
            } else {
                for p_x in 0..8 {
                    let buf_index = buf_index
                        .wrapping_add(p_x)
                        .wrapping_sub(scroll_x_within_tile as usize);
                    if buf_index < (GAME_WIDTH as usize) {
                        let p_x = 8 - p_x - 1;

                        let index = ((pattern_strip >> (p_x << 2)) & 0xf) as u8;

                        if index != 0 {
                            fb_primary[buf_index] =
                                pal_index_to_32bit!(self, cur_cell.palette_line | index);
                        } else {
                            fb_primary[buf_index] = 0;
                        }
                        fb_secondary[buf_index] = 0;
                    }
                }
            }
        }
    }

    pub(crate) fn render_screen_line(
        &mut self,
        y: u16,
        fb_plane_b: &mut [u32],
        fb_plane_a_low: &mut [u32],
        fb_plane_s_low: &mut [u32],
        fb_plane_a_high: &mut [u32],
        fb_plane_s_high: &mut [u32],
    ) {
        let line_state = self.per_line_state[y as usize];
        if line_state.is_some() {
            line_state.unwrap().swap_state(self);
        }
        self.render_plane_line_b(fb_plane_b, y);
        self.render_plane_line_a(fb_plane_a_low, fb_plane_a_high, y);
        self.render_sprites_line(y, fb_plane_s_low, fb_plane_s_high);
        if line_state.is_some() {
            line_state.unwrap().swap_state(self);
        }
    }
}
