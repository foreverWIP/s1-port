use std::{cell::RefCell, rc::Rc};

use speedshoes_vdp_renderer::{
    render_plane_line_a_high, render_plane_line_a_low, render_plane_line_b_high,
    render_plane_line_b_low, render_screen_line, render_sprites_line_high, render_sprites_line_low,
    HScrollMode, PlaneSize, Sprite, TileAttributes, VScrollMode,
};

use crate::{GAME_HEIGHT, GAME_WIDTH};

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
    pub hw_planes_mode: bool,
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
    pub fn new(rom: Rc<Vec<u8>>, ram: Rc<RefCell<Vec<u8>>>, hw_planes_mode: bool) -> Vdp {
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
            hw_planes_mode,
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

    pub(crate) fn render_screen_line(
        &mut self,
        y: u16,
        fb_plane_b_low: &mut [u32],
        fb_plane_b_high: &mut [u32],
        fb_plane_a_low: &mut [u32],
        fb_plane_s_low: &mut [u32],
        fb_plane_a_high: &mut [u32],
        fb_plane_s_high: &mut [u32],
    ) {
        if self.hw_planes_mode {
            let line_state = self.per_line_state[y as usize];
            if line_state.is_some() {
                line_state.unwrap().swap_state(self);
            }
            render_plane_line_b_low(
                y,
                GAME_WIDTH as u16,
                &self.vram,
                &self.palette,
                self.plane_size,
                self.plane_b_location,
                self.hscroll_location,
                &self.vscroll_buffer,
                self.vscroll_mode,
                fb_plane_b_low,
            );
            render_plane_line_a_low(
                y,
                GAME_WIDTH as u16,
                &self.vram,
                &self.palette,
                self.plane_size,
                self.plane_a_location,
                self.hscroll_location,
                &self.vscroll_buffer,
                self.vscroll_mode,
                fb_plane_a_low,
            );
            render_sprites_line_low(
                &self.vram,
                &self.palette,
                self.sprite_table_location,
                y,
                GAME_WIDTH as u16,
                fb_plane_s_low,
            );
            render_plane_line_b_high(
                y,
                GAME_WIDTH as u16,
                &self.vram,
                &self.palette,
                self.plane_size,
                self.plane_b_location,
                self.hscroll_location,
                &self.vscroll_buffer,
                self.vscroll_mode,
                fb_plane_b_high,
            );
            render_plane_line_a_high(
                y,
                GAME_WIDTH as u16,
                &self.vram,
                &self.palette,
                self.plane_size,
                self.plane_a_location,
                self.hscroll_location,
                &self.vscroll_buffer,
                self.vscroll_mode,
                fb_plane_a_high,
            );
            render_sprites_line_high(
                &self.vram,
                &self.palette,
                self.sprite_table_location,
                y,
                GAME_WIDTH as u16,
                fb_plane_s_high,
            );
            if line_state.is_some() {
                line_state.unwrap().swap_state(self);
            }
        } else {
            render_screen_line(
                &self.vram,
                &self.palette,
                self.bg_color_index,
                self.plane_a_location,
                self.plane_b_location,
                self.hscroll_location,
                self.sprite_table_location,
                &self.vscroll_buffer,
                self.vscroll_mode,
                y,
                GAME_WIDTH as u16,
                self.plane_size,
                fb_plane_a_high,
            );
        }
    }
}
