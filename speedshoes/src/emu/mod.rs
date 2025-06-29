use std::{cell::RefCell, fmt::Display, num::Wrapping, rc::Rc};

use r68k_emu::{
    cpu::{ConfiguredCore, ProcessingState},
    interrupts::AutoInterruptController,
    ram::{ADDRBUS_MASK, AddressBus},
};

use crate::{DataSize, GAME_HEIGHT, system::Input, vdp::Vdp};

#[derive(Clone, Copy, PartialEq, Eq)]
pub enum SystemEmulatorDataSize {
    Byte,
    Word,
    Long,
}

#[derive(Clone, Copy, PartialEq, Eq, Debug)]
pub enum SystemEmulatorRegister {
    D0,
    D1,
    D2,
    D3,
    D4,
    D5,
    D6,
    D7,
    A0,
    A1,
    A2,
    A3,
    A4,
    A5,
    A6,
    A7,
    SR,
    PC,
}
impl From<usize> for SystemEmulatorRegister {
    fn from(value: usize) -> Self {
        use SystemEmulatorRegister::*;
        match value {
            0 => D0,
            1 => D1,
            2 => D2,
            3 => D3,
            4 => D4,
            5 => D5,
            6 => D6,
            7 => D7,
            8 => A0,
            9 => A1,
            10 => A2,
            11 => A3,
            12 => A4,
            13 => A5,
            14 => A6,
            15 => A7,
            16 => SR,
            17 => PC,
            _ => unreachable!(),
        }
    }
}

pub trait SystemEmulator {
    fn new(
        id: &'static str,
        rom: Rc<Vec<u8>>,
        ram: Rc<RefCell<Vec<u8>>>,
        vdp: Rc<RefCell<Vdp>>,
    ) -> Result<Self, String>
    where
        Self: Sized;
    fn reset(&mut self) -> Result<(), String>;
    fn get_reg(&self, reg: SystemEmulatorRegister) -> u32;
    fn get_reg_state(&self) -> [u32; 17] {
        let mut ret = [0; 17];
        for i in 0..17 {
            ret[i] = self.get_reg(i.try_into().unwrap());
        }
        ret
    }
    fn set_reg(&mut self, reg: SystemEmulatorRegister, value: u32);
    fn execute1(&mut self);
    fn start_vblank(&mut self);
    fn pc(&self) -> u32;
    fn set_input(&mut self, input: Input);
    fn ram(&self) -> Rc<RefCell<Vec<u8>>>;
    fn read_8(&mut self, loc: u32) -> u8;
    fn read_16(&mut self, loc: u32) -> u16;
    fn read_32(&mut self, loc: u32) -> u32;
    fn write_8(&mut self, loc: u32, value: u8);
    fn write_16(&mut self, loc: u32, value: u16);
    fn write_32(&mut self, loc: u32, value: u32);
}

pub type SpeedShoesCore = ConfiguredCore<AutoInterruptController, SpeedShoesBus>;

impl SystemEmulator for SpeedShoesCore {
    fn reset(&mut self) -> Result<(), String> {
        self.reset();
        let mut ram = self.mem.ram.as_ref().borrow_mut();
        ram.fill(0);
        self.dar[..14].fill(0);
        Ok(())
    }

    fn get_reg(&self, reg: SystemEmulatorRegister) -> u32 {
        match reg {
            SystemEmulatorRegister::PC => self.pc,
            SystemEmulatorRegister::SR => self.status_register() as u32,
            _ => self.dar[reg as usize],
        }
    }

    fn set_reg(&mut self, reg: SystemEmulatorRegister, value: u32) {
        match reg {
            SystemEmulatorRegister::PC => self.pc = value,
            SystemEmulatorRegister::SR => {
                // XNZVC
                self.sr_to_flags(value as u16);
            }
            _ => self.dar[reg as usize] = value,
        }
    }

    fn execute1(&mut self) {
        self.execute1();
    }

    fn start_vblank(&mut self) {
        self.handle_interrupt(6, 30);
    }

    fn pc(&self) -> u32 {
        self.pc
    }

    fn set_input(&mut self, input: Input) {
        self.mem.current_input = input;
    }

    fn ram(&self) -> Rc<RefCell<Vec<u8>>> {
        self.mem.ram.clone()
    }

    fn new(
        id: &'static str,
        rom: Rc<Vec<u8>>,
        ram: Rc<RefCell<Vec<u8>>>,
        vdp: Rc<RefCell<Vdp>>,
    ) -> Result<Self, String> {
        let base = u32::from_be_bytes(rom[4..8].try_into().unwrap());
        let ret = SpeedShoesCore::new_with(
            base,
            AutoInterruptController::new(),
            SpeedShoesBus {
                id,
                rom: rom.clone(),
                ram,
                vdp,
                fb_plane_a_low: vec![0u32; (432 * GAME_HEIGHT) as usize].into_boxed_slice(),
                fb_plane_b_low: vec![0u32; (432 * GAME_HEIGHT) as usize].into_boxed_slice(),
                fb_plane_b_high: vec![0u32; (432 * GAME_HEIGHT) as usize].into_boxed_slice(),
                fb_plane_s_low: vec![0u32; (432 * GAME_HEIGHT) as usize].into_boxed_slice(),
                fb_plane_a_high: vec![0u32; (432 * GAME_HEIGHT) as usize].into_boxed_slice(),
                fb_plane_s_high: vec![0u32; (432 * GAME_HEIGHT) as usize].into_boxed_slice(),
                current_input: Input::default(),
                input_th_toggle: false,
            },
        );
        Ok(ret)
    }

    fn read_8(&mut self, loc: u32) -> u8 {
        let value = self.mem.read_memory::<{ DataSize::Byte }>(loc);
        value as u8
    }

    fn read_16(&mut self, loc: u32) -> u16 {
        let value = self.mem.read_memory::<{ DataSize::Word }>(loc);
        value as u16
    }

    fn read_32(&mut self, loc: u32) -> u32 {
        let value = self.mem.read_memory::<{ DataSize::Long }>(loc);
        value
    }

    fn write_8(&mut self, loc: u32, value: u8) {
        self.mem
            .write_memory::<{ DataSize::Byte }>(loc, value as u32);
    }

    fn write_16(&mut self, loc: u32, value: u16) {
        self.mem
            .write_memory::<{ DataSize::Word }>(loc, value as u32);
    }

    fn write_32(&mut self, loc: u32, value: u32) {
        self.mem
            .write_memory::<{ DataSize::Long }>(loc, value as u32);
    }
}

#[derive(Clone, Copy, PartialEq, Eq, Debug)]
pub struct MemWrite {
    pub pc: u32,
    pub loc: u32,
    pub value: u32,
    pub size: DataSize,
}
impl Display for MemWrite {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        f.write_fmt(format_args!(
            "{} write of {:#X} to {:#X}",
            self.size, self.value, self.loc
        ))
    }
}

// #[derive(Clone)]
pub struct SpeedShoesBus {
    pub id: &'static str,
    pub(crate) rom: Rc<Vec<u8>>,
    pub(crate) ram: Rc<RefCell<Vec<u8>>>,
    pub(crate) vdp: Rc<RefCell<Vdp>>,
    pub fb_plane_a_low: Box<[u32]>,
    pub fb_plane_b_low: Box<[u32]>,
    pub fb_plane_b_high: Box<[u32]>,
    pub fb_plane_s_low: Box<[u32]>,
    pub fb_plane_a_high: Box<[u32]>,
    pub fb_plane_s_high: Box<[u32]>,
    pub(crate) current_input: Input,
    pub(crate) input_th_toggle: bool,
}

impl SpeedShoesBus {
    pub fn read_memory<const SIZE: DataSize>(&self, address: u32) -> u32 {
        let match_addr: usize = (address & ADDRBUS_MASK) as usize;
        let ret = match match_addr {
            0..=0x7f_ffff => {
                let match_addr_end = match_addr
                    + match SIZE {
                        DataSize::Byte => 0,
                        DataSize::Word => 1,
                        DataSize::Long => 3,
                    };
                if match_addr_end < self.rom.len() {
                    // ROM
                    match SIZE {
                        DataSize::Byte => self.rom[match_addr] as u32,
                        DataSize::Word => u16::from_be_bytes(
                            self.rom[match_addr..(match_addr + 2)].try_into().unwrap(),
                        ) as u32,
                        DataSize::Long => u32::from_be_bytes(
                            self.rom[match_addr..(match_addr + 4)].try_into().unwrap(),
                        ),
                    }
                } else {
                    0
                }
            }
            0xff_0000.. => {
                // RAM
                let ram = self.ram.as_ref().borrow();
                let ret = match SIZE {
                    DataSize::Byte => {
                        let ret = ram[match_addr - 0xff_0000] as u32;
                        ret
                    }
                    DataSize::Word => u16::from_be_bytes(
                        ram[(match_addr - 0xff_0000)..((match_addr - 0xff_0000) + 2)]
                            .try_into()
                            .unwrap(),
                    ) as u32,
                    DataSize::Long => u32::from_be_bytes(
                        ram[(match_addr - 0xff_0000)..((match_addr - 0xff_0000) + 4)]
                            .try_into()
                            .unwrap(),
                    ),
                };
                ret
            }
            0xa1_0001 =>
            // hardware version register
            {
                0b0010_0000
            }
            0xa1_0003 => {
                !if self.input_th_toggle {
                    (if self.current_input.c { 0x20 } else { 0 })
                        | (if self.current_input.b { 0x10 } else { 0 })
                        | (if self.current_input.right { 0x08 } else { 0 })
                        | (if self.current_input.left { 0x04 } else { 0 })
                        | (if self.current_input.down { 0x02 } else { 0 })
                        | (if self.current_input.up { 0x01 } else { 0 })
                        | 0x40
                } else {
                    (if self.current_input.start { 0x20 } else { 0 })
                        | (if self.current_input.a { 0x10 } else { 0 })
                        | (if self.current_input.down { 0x02 } else { 0 })
                        | (if self.current_input.up { 0x01 } else { 0 })
                }
            }
            _ => {
                // anything we don't need to emulate
                // vdp status register can prob do this too?
                0
            }
        };
        /*if match_addr == 0xa1_0003 {
            println!("{} read_{} {:X} = {:X}", self.id, size, address, ret);
        }*/
        ret
    }

    pub fn write_memory<const SIZE: DataSize>(&mut self, address: u32, value: u32) {
        /*if address == 0xFFF602 || address == 0xFFF603 || address == 0xFFF604 || address == 0xFFF605
        {
            println!("{} write_{} {:#X} -> {:#X}", self.id, size, value, address);
        }*/
        let mut match_addr: usize = (address & ADDRBUS_MASK) as usize;
        let match_addr_max = match_addr
            + match SIZE {
                DataSize::Byte => 0,
                DataSize::Word => 1,
                DataSize::Long => 3,
            };
        if match_addr >= 0xff_0000 {
            // RAM
            let mut ram = self.ram.as_ref().borrow_mut();
            match_addr -= 0xff_0000;
            match SIZE {
                DataSize::Byte => {
                    ram[match_addr] = value as u8;
                }
                DataSize::Word => {
                    let val_bytes = u16::to_be_bytes(value as u16);
                    ram[match_addr] = val_bytes[0];
                    ram[match_addr + 1] = val_bytes[1];
                }
                DataSize::Long => {
                    let val_bytes = u32::to_be_bytes(value);
                    ram[match_addr] = val_bytes[0];
                    ram[match_addr + 1] = val_bytes[1];
                    ram[match_addr + 2] = val_bytes[2];
                    ram[match_addr + 3] = val_bytes[3];
                }
            }
        } else if match_addr == 0xc0_0000 {
            // vdp data port
            let mut vdp = self.vdp.as_ref().borrow_mut();
            match SIZE {
                DataSize::Byte => {
                    vdp.handle_data_write_byte(0, value as u8);
                }
                DataSize::Word => vdp.handle_data_write((value & 0xffff) as u16, true),
                DataSize::Long => {
                    vdp.handle_data_write((value >> 16) as u16, true);
                    vdp.handle_data_write((value & 0xffff) as u16, true);
                }
            };
        } else if match_addr == 0xc0_0004 {
            // vdp control port
            let mut vdp = self.vdp.as_ref().borrow_mut();
            if SIZE == DataSize::Word {
                vdp_write_word(self.id, &mut vdp, value as u16);
            } else if SIZE == DataSize::Long {
                vdp_write_word(self.id, &mut vdp, (value >> 16) as u16);
                vdp_write_word(self.id, &mut vdp, value as u16);
            }
            fn vdp_write_word(id: &str, vdp: &mut Vdp, word: u16) {
                let value_msb = word >> 8;
                if value_msb >= 0x80 && value_msb < 0x98 {
                    vdp.handle_reg_write(word);
                } else {
                    // println!("{}: write control word {:04X}", id, word);
                    vdp.handle_control_word(word);
                }
            }
        } else if match_addr == 0xa1_0003 {
            self.input_th_toggle = (value & 0x40) != 0;
        }
    }

    pub fn render(&mut self, width: u16) -> Result<(), String> {
        if self.vdp.as_ref().borrow().display_enabled() {
            let mut vdp = self.vdp.as_ref().borrow_mut();
            if vdp.hw_planes_mode {
                let plane_len = self.fb_plane_b_low.len();
                self.fb_plane_b_low[..(plane_len / 4)].fill(0);
                self.fb_plane_a_low[..(plane_len / 4)].fill(0);
                self.fb_plane_s_low[..(plane_len / 4)].fill(0);
                self.fb_plane_b_high[..(plane_len / 4)].fill(0);
                self.fb_plane_a_high[..(plane_len / 4)].fill(0);
                self.fb_plane_s_high[..(plane_len / 4)].fill(0);
            } else {
                self.fb_plane_b_low.fill(0);
                self.fb_plane_a_low.fill(0);
                self.fb_plane_s_low.fill(0);
                self.fb_plane_b_high.fill(0);
                self.fb_plane_a_high.fill(0);
                self.fb_plane_s_high.fill(0);
            }
            let stride = if vdp.hw_planes_mode {
                width as usize / 4
            } else {
                width as usize
            };
            for y in 0usize..(GAME_HEIGHT as usize) {
                let fb_range = (y * stride as usize)..((y * stride as usize) + width as usize);
                vdp.render_screen_line(
                    y as u16,
                    width,
                    &mut self.fb_plane_b_low[fb_range.clone()],
                    &mut self.fb_plane_b_high[fb_range.clone()],
                    &mut self.fb_plane_a_low[fb_range.clone()],
                    &mut self.fb_plane_s_low[fb_range.clone()],
                    &mut self.fb_plane_a_high[fb_range.clone()],
                    &mut self.fb_plane_s_high[fb_range],
                );
            }
        }
        Ok(())
    }
}

impl AddressBus for SpeedShoesBus {
    fn copy_from(&mut self, other: &Self) {
        self.rom = other.rom.clone();
        other
            .ram
            .as_ref()
            .borrow_mut()
            .copy_from_slice(self.ram.as_ref().borrow().as_slice());
    }

    fn read_byte(&mut self, _address_space: r68k_emu::ram::AddressSpace, address: u32) -> u32 {
        self.read_memory::<{ DataSize::Byte }>(address)
    }

    fn read_word(&mut self, _address_space: r68k_emu::ram::AddressSpace, address: u32) -> u32 {
        self.read_memory::<{ DataSize::Word }>(address)
    }

    fn read_long(&mut self, _address_space: r68k_emu::ram::AddressSpace, address: u32) -> u32 {
        self.read_memory::<{ DataSize::Long }>(address)
    }

    fn write_byte(
        &mut self,
        _address_space: r68k_emu::ram::AddressSpace,
        address: u32,
        value: u32,
    ) {
        self.write_memory::<{ DataSize::Byte }>(address, value);
    }

    fn write_word(
        &mut self,
        _address_space: r68k_emu::ram::AddressSpace,
        address: u32,
        value: u32,
    ) {
        self.write_memory::<{ DataSize::Word }>(address, value);
    }

    fn write_long(
        &mut self,
        _address_space: r68k_emu::ram::AddressSpace,
        address: u32,
        value: u32,
    ) {
        self.write_memory::<{ DataSize::Long }>(address, value);
    }
}
