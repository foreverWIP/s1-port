use std::{cell::RefCell, fmt::Display, num::Wrapping, rc::Rc};

use r68k_emu::{
    cpu::{ConfiguredCore, ProcessingState},
    interrupts::AutoInterruptController,
    ram::{AddressBus, ADDRBUS_MASK},
};

use crate::{system::Input, vdp::Vdp, DataSize};

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
    fn get_reg_state(&self) -> Vec<u32> {
        let mut ret = Vec::new();
        for i in 0..17 {
            ret.push(self.get_reg(i.try_into().unwrap()));
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
                current_input: Input::default(),
                input_th_toggle: false,
            },
        );
        Ok(ret)
    }

    fn read_8(&mut self, loc: u32) -> u8 {
        let size = DataSize::Byte;
        let value = self.mem.read_memory(loc, size);
        value as u8
    }

    fn read_16(&mut self, loc: u32) -> u16 {
        let size = DataSize::Word;
        let value = self.mem.read_memory(loc, size);
        value as u16
    }

    fn read_32(&mut self, loc: u32) -> u32 {
        let size = DataSize::Long;
        let value = self.mem.read_memory(loc, size);
        value
    }

    fn write_8(&mut self, loc: u32, value: u8) {
        let size = DataSize::Byte;
        self.mem.write_memory(loc, value as u32, size);
    }

    fn write_16(&mut self, loc: u32, value: u16) {
        let size = DataSize::Word;
        self.mem.write_memory(loc, value as u32, size);
    }

    fn write_32(&mut self, loc: u32, value: u32) {
        let size = DataSize::Long;
        self.mem.write_memory(loc, value as u32, size);
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

#[derive(Clone)]
pub struct SpeedShoesBus {
    pub id: &'static str,
    pub(crate) rom: Rc<Vec<u8>>,
    pub(crate) ram: Rc<RefCell<Vec<u8>>>,
    pub(crate) vdp: Rc<RefCell<Vdp>>,
    pub(crate) current_input: Input,
    pub(crate) input_th_toggle: bool,
}

impl SpeedShoesBus {
    pub fn read_memory(&self, address: u32, size: DataSize) -> u32 {
        let match_addr: usize = (address & ADDRBUS_MASK) as usize;
        let ret = match match_addr {
            0..=0x7f_ffff => {
                let match_addr_end = match_addr
                    + match size {
                        DataSize::Byte => 0,
                        DataSize::Word => 1,
                        DataSize::Long => 3,
                    };
                if match_addr_end < self.rom.len() {
                    // ROM
                    match size {
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
                let ret = match size {
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
        /*if address == 0x129E {
            println!("{} {:X} = {:X}", self.id, address, ret);
        }*/
        ret
    }

    pub fn write_memory(&mut self, address: u32, value: u32, size: DataSize) {
        /*if (0xfffc..0xffff).contains(&(address & 0xffff)) {
            println!("{} write_{} {:#X} -> {:#X}", self.id, size, value, address);
        }*/
        let mut match_addr: usize = (address & ADDRBUS_MASK) as usize;
        let match_addr_max = match_addr
            + match size {
                DataSize::Byte => 0,
                DataSize::Word => 1,
                DataSize::Long => 3,
            };
        if (match_addr_max as usize) < self.rom.len() {
            // ROM
            panic!(
                "attempted to write to rom address {:#X}: data of size {}: {:#X}",
                address, size, value
            );
        } else if match_addr >= 0xff_0000 {
            // RAM
            let mut ram = self.ram.as_ref().borrow_mut();
            match_addr -= 0xff_0000;
            match size {
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
            match size {
                DataSize::Byte => {
                    vdp.handle_data_write_byte(0, value as u8);
                }
                DataSize::Word => vdp.handle_data_write((value & 0xffff) as u16, true),
                DataSize::Long => {
                    vdp.handle_data_write((value >> 16) as u16, true);
                    vdp.handle_data_write((value & 0xffff) as u16, true);
                }
            };
        } else if match_addr == 0xc0_0004 && size == DataSize::Word {
            // vdp control port
            let mut vdp = self.vdp.as_ref().borrow_mut();
            let value_msb = value >> 8;
            if value_msb >= 0x80 && value_msb < 0x98 {
                vdp.handle_reg_write(value as u16);
            } else {
                vdp.handle_control_word(value as u16);
            }
        } else if match_addr == 0xc0_0004 && size == DataSize::Long {
            // vdp control port
            let mut vdp = self.vdp.as_ref().borrow_mut();
            let value_msb = value >> 24;
            if value_msb >= 0x80 && value_msb < 0x98 {
                vdp.handle_reg_write((value >> 16) as u16);
                vdp.handle_reg_write((value & 0xffff) as u16);
            } else {
                vdp.handle_control_word((value >> 16) as u16);
                vdp.handle_control_word((value & 0xffff) as u16);
            }
        } else if match_addr == 0xa1_0003 {
            self.input_th_toggle = (value & 0x40) != 0;
        }
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
        self.read_memory(address, DataSize::Byte)
    }

    fn read_word(&mut self, _address_space: r68k_emu::ram::AddressSpace, address: u32) -> u32 {
        self.read_memory(address, DataSize::Word)
    }

    fn read_long(&mut self, _address_space: r68k_emu::ram::AddressSpace, address: u32) -> u32 {
        self.read_memory(address, DataSize::Long)
    }

    fn write_byte(
        &mut self,
        _address_space: r68k_emu::ram::AddressSpace,
        address: u32,
        value: u32,
    ) {
        self.write_memory(address, value, DataSize::Byte);
    }

    fn write_word(
        &mut self,
        _address_space: r68k_emu::ram::AddressSpace,
        address: u32,
        value: u32,
    ) {
        self.write_memory(address, value, DataSize::Word);
    }

    fn write_long(
        &mut self,
        _address_space: r68k_emu::ram::AddressSpace,
        address: u32,
        value: u32,
    ) {
        self.write_memory(address, value, DataSize::Long);
    }
}
