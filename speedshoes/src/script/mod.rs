use std::cell::RefCell;
use std::cmp::Ordering;
use std::collections::HashMap;
use std::env::consts::{DLL_PREFIX, DLL_SUFFIX};
use std::fs;
use std::rc::Rc;

use dlopen2::symbor::Symbol;

use crate::emu::SystemEmulator;
use crate::emu::{SpeedShoesBus, SpeedShoesCore};
use crate::system::{synchronize_script, Input, System};
use crate::vdp::Vdp;
use crate::DataSize;

type VoidCFunc = fn() -> ();

#[repr(C)]
struct FFIInfo {
    emu: *const u8,
    read_8_cb: fn(emu: &ScriptEngine, loc: u32) -> u8,
    read_16_cb: fn(emu: &ScriptEngine, loc: u32) -> u16,
    read_32_cb: fn(emu: &ScriptEngine, loc: u32) -> u32,
    write_8_cb: fn(emu: &mut ScriptEngine, loc: u32, value: u8) -> (),
    write_16_cb: fn(emu: &mut ScriptEngine, loc: u32, value: u16) -> (),
    write_32_cb: fn(emu: &mut ScriptEngine, loc: u32, value: u32) -> (),
    sync_cb: fn(pc: u32, bool) -> bool,
}

pub(crate) struct ScriptEngine {
    libname: String,
    lib: Option<dlopen2::symbor::Library>,
    hooks: HashMap<u32, *const u8>,
    regs: Vec<*mut u32>,
    bus: Box<SpeedShoesBus>,
}

impl ScriptEngine {
    pub fn new(libname: &str, rom: Rc<Vec<u8>>) -> Result<Self, String> {
        let ram = Rc::new(RefCell::new(vec![0u8; 0x1_0000]));
        let vdp = Vdp::new(rom.clone(), ram.clone());
        let bus = SpeedShoesBus {
            id: "script",
            rom,
            ram,
            vdp: Rc::new(RefCell::new(vdp)),
            current_input: Input::default(),
            input_th_toggle: false,
        };
        Ok(Self {
            libname: libname.to_string(),
            lib: None,
            hooks: HashMap::new(),
            regs: Vec::new(),
            bus: Box::new(bus),
        })
    }

    pub fn ram(&self) -> Rc<RefCell<Vec<u8>>> {
        self.bus.ram.clone()
    }

    fn read_8(&self, loc: u32) -> u8 {
        self.bus.read_memory(loc, DataSize::Byte) as u8
    }

    fn read_16(&self, loc: u32) -> u16 {
        self.bus.read_memory(loc, DataSize::Word) as u16
    }

    fn read_32(&self, loc: u32) -> u32 {
        self.bus.read_memory(loc, DataSize::Long)
    }

    fn write_8(&mut self, loc: u32, value: u8) {
        self.bus.write_memory(loc, value as u32, DataSize::Byte);
    }

    fn write_16(&mut self, loc: u32, value: u16) {
        self.bus.write_memory(loc, value as u32, DataSize::Word);
    }

    fn write_32(&mut self, loc: u32, value: u32) {
        self.bus.write_memory(loc, value as u32, DataSize::Long);
    }

    pub fn reset(&mut self, emu: &mut SpeedShoesCore) -> Result<(), String> {
        {
            if self.lib.is_some() {
                self.lib = None;
            }
        }
        self.hooks.clear();
        self.regs.clear();
        let ffi_info = FFIInfo {
            emu: unsafe { std::mem::transmute::<&mut ScriptEngine, *const u8>(self) },
            read_8_cb: Self::read_8,
            read_16_cb: Self::read_16,
            read_32_cb: Self::read_32,
            write_8_cb: Self::write_8,
            write_16_cb: Self::write_16,
            write_32_cb: Self::write_32,
            sync_cb: synchronize_script,
        };
        let libname = format!(
            "{}{}{}{}",
            if cfg!(debug_assertions) { "../" } else { "" },
            DLL_PREFIX,
            self.libname,
            DLL_SUFFIX
        );
        println!("loading library {}", libname);
        // fs::copy(libname, libname_use.clone()).map_err(|e| e.to_string())?;
        self.lib = Some(dlopen2::symbor::Library::open(&libname).map_err(|e| e.to_string())?);
        let lib = self.lib.as_ref().unwrap();
        let bind_func = unsafe {
            lib.symbol::<unsafe extern "C" fn(*const FFIInfo) -> ()>("speedshoes__bind_functions")
                .map_err(|e| e.to_string())?
        };
        unsafe {
            bind_func(&ffi_info);
        }
        for i in 0..16 {
            let first_char = if i < 8 { "d" } else { "a" };
            let second_char = (i % 8).to_string();
            unsafe {
                let reg_ref = lib
                    .reference_mut::<u32>(&format!("speedshoes__{}{}", first_char, second_char))
                    .map_err(|e| e.to_string())?;
                self.regs.push(reg_ref);
            }
        }
        unsafe {
            let reg_ref = lib
                .reference_mut::<u32>("speedshoes__sr")
                .map_err(|e| e.to_string())?;
            self.regs.push(reg_ref);
        }
        Ok(())
    }

    pub fn get_reg_state(&self) -> Vec<u32> {
        let mut ret = Vec::new();
        unsafe {
            for reg in &self.regs {
                ret.push(**reg);
            }
        }
        ret
    }

    pub fn sync_script_with_emu(&mut self, emu: &mut SpeedShoesCore) {
        // println!("synching script with emu");
        // remember that CCR is index 16!
        unsafe {
            for i in 0..self.regs.len() {
                /*if i == 15 {
                    continue;
                }*/
                let script_reg = self.regs[i];
                let emu_reg = emu.get_reg(i.into());
                // println!("reg {}: {:X} -> {:X}", i, *script_reg, emu_reg);
                *script_reg = emu_reg;
            }
        }
        self.bus.ram.borrow_mut()[..0xFCC0].copy_from_slice(&emu.ram().borrow()[..0xFCC0]);
        self.bus.ram.borrow_mut()[0xFE00..].copy_from_slice(&emu.ram().borrow()[0xFE00..]);
        self.bus.current_input = emu.mem.current_input;
    }

    pub fn sync_emu_with_script(&mut self, emu: &mut SpeedShoesCore) {
        unsafe {
            for i in 0..self.regs.len() {
                if i == 15 {
                    continue;
                }
                let script_reg = self.regs[i];
                let reg_after = *script_reg;
                // println!("{:?} = {:#X}", SystemEmulatorRegister::from(i), reg_after);
                emu.set_reg(i.into(), reg_after);
            }
        }
        emu.mem.ram.borrow_mut()[..0xFCC0].copy_from_slice(&self.bus.ram.borrow()[..0xFCC0]);
        emu.mem.ram.borrow_mut()[0xFE00..].copy_from_slice(&self.bus.ram.borrow()[0xFE00..]);
        emu.mem.current_input = self.bus.current_input;
    }

    fn call_hook_internal(&mut self, hook: *const u8, loc: u32, emu: &mut SpeedShoesCore) -> bool {
        unsafe {
            let wrotemem = self
                .lib
                .as_ref()
                .unwrap()
                .reference_mut::<bool>("speedshoes__wrotemem")
                .unwrap();
            *wrotemem = false;
            self.sync_script_with_emu(emu);
            let code = std::mem::transmute::<*const u8, VoidCFunc>(hook);
            code();
            let wrotemem = self
                .lib
                .as_ref()
                .unwrap()
                .reference::<bool>("speedshoes__wrotemem")
                .unwrap();
            let vblank_end = self
                .lib
                .as_ref()
                .unwrap()
                .reference_mut::<bool>("speedshoes__vblank_end")
                .unwrap();
            *vblank_end = false;
            *wrotemem
        }
    }

    pub fn hook_exists(&self, loc: u32) -> bool {
        let func_name = format!("rom_{:X}", loc);
        let lib = self.lib.as_ref().unwrap();
        unsafe { lib.symbol::<*const u8>(&func_name).is_ok() }
    }

    pub fn call_hook(&mut self, emu: &mut SpeedShoesCore, loc: u32) -> Result<bool, ()> {
        let lib = &self.lib;
        if lib.is_none() {
            panic!("script library not loaded!");
        }
        if let Some(hook) = self.hooks.get(&loc) {
            return Ok(self.call_hook_internal(*hook, loc, emu));
        }

        let lib = self.lib.as_ref().unwrap();
        let func_name = format!("rom_{:X}", loc);
        let bind_func = unsafe { lib.symbol::<*const u8>(&func_name).map_err(|e| ())? };
        self.hooks.insert(loc, *bind_func);
        Ok(self.call_hook_internal(*bind_func, loc, emu))
    }
}
