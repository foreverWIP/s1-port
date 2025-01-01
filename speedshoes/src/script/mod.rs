use std::borrow::Borrow;
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
use crate::{DataSize, GAME_HEIGHT, GAME_WIDTH};

type VoidCFunc = extern "C" fn() -> ();

#[repr(C)]
struct FFIInfo {
    emu: *const u8,
    read_8_cb: fn(emu: &ScriptEngine, loc: u32) -> u8,
    read_16_cb: fn(emu: &ScriptEngine, loc: u32) -> u16,
    read_32_cb: fn(emu: &ScriptEngine, loc: u32) -> u32,
    write_8_cb: fn(emu: &mut ScriptEngine, loc: u32, value: u8) -> (),
    write_16_cb: fn(emu: &mut ScriptEngine, loc: u32, value: u16) -> (),
    write_32_cb: fn(emu: &mut ScriptEngine, loc: u32, value: u32) -> (),
    sync_cb: fn(pc: u32) -> bool,
}

pub(crate) struct ScriptEngine {
    libname: String,
    dependent_libs: Vec<dlopen2::symbor::Library>,
    lib: Option<dlopen2::symbor::Library>,
    hooks: HashMap<u32, *const u8>,
    regs: Vec<*mut u32>,
    pub(crate) bus: Box<SpeedShoesBus>,
    last_state_ram: Rc<RefCell<Vec<u8>>>,
}

impl ScriptEngine {
    pub fn new(
        libname: &str,
        rom: Rc<Vec<u8>>,
        last_state_ram: Rc<RefCell<Vec<u8>>>,
    ) -> Result<Self, String> {
        let ram = Rc::new(RefCell::new(vec![0u8; 0x1_0000]));
        let vdp = Vdp::new(rom.clone(), ram.clone());
        let bus = SpeedShoesBus {
            id: "script",
            rom,
            ram,
            vdp: Rc::new(RefCell::new(vdp)),
            fb_plane_a_low: vec![0u32; (GAME_WIDTH * GAME_HEIGHT) as usize].into_boxed_slice(),
            fb_plane_b: vec![0u32; (GAME_WIDTH * GAME_HEIGHT) as usize].into_boxed_slice(),
            fb_plane_s_low: vec![0u32; (GAME_WIDTH * GAME_HEIGHT) as usize].into_boxed_slice(),
            fb_plane_a_high: vec![0u32; (GAME_WIDTH * GAME_HEIGHT) as usize].into_boxed_slice(),
            fb_plane_s_high: vec![0u32; (GAME_WIDTH * GAME_HEIGHT) as usize].into_boxed_slice(),
            current_input: Input::default(),
            input_th_toggle: false,
        };
        Ok(Self {
            dependent_libs: Vec::new(),
            libname: libname.to_string(),
            lib: None,
            hooks: HashMap::new(),
            regs: Vec::new(),
            bus: Box::new(bus),
            last_state_ram,
        })
    }

    pub fn ram(&self) -> Rc<RefCell<Vec<u8>>> {
        self.bus.ram.clone()
    }

    fn read_8(&self, loc: u32) -> u8 {
        self.bus.read_memory::<{ DataSize::Byte }>(loc) as u8
    }

    fn read_16(&self, loc: u32) -> u16 {
        self.bus.read_memory::<{ DataSize::Word }>(loc) as u16
    }

    fn read_32(&self, loc: u32) -> u32 {
        self.bus.read_memory::<{ DataSize::Long }>(loc)
    }

    fn write_8(&mut self, loc: u32, value: u8) {
        self.bus
            .write_memory::<{ DataSize::Byte }>(loc, value as u32);
    }

    fn write_16(&mut self, loc: u32, value: u16) {
        self.bus
            .write_memory::<{ DataSize::Word }>(loc, value as u32);
    }

    fn write_32(&mut self, loc: u32, value: u32) {
        self.bus
            .write_memory::<{ DataSize::Long }>(loc, value as u32);
    }

    pub fn reset(&mut self) -> Result<(), String> {
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
        if cfg!(target_os = "windows") {
            self.dependent_libs
                .push(dlopen2::symbor::Library::open("msvcrt.dll").map_err(|e| e.to_string())?);
        }
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

            let reset = lib
                .symbol::<VoidCFunc>("reset_game")
                .map_err(|e| e.to_string())?;
            reset();
        }
        self.bus
            .ram
            .borrow_mut()
            .copy_from_slice(&self.last_state_ram.as_ref().borrow());
        Ok(())
    }

    pub fn get_reg_state(&self) -> [u32; 17] {
        let mut ret = [0; 17];
        unsafe {
            for i in 0..self.regs.len() {
                ret[i] = *self.regs[i];
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
        // self.bus.ram.borrow_mut()[..0xFCC0].copy_from_slice(&emu.ram().borrow()[..0xFCC0]);
        // self.bus.ram.borrow_mut()[0xFE00..].copy_from_slice(&emu.ram().borrow()[0xFE00..]);
        self.bus
            .ram
            .borrow_mut()
            .copy_from_slice(&emu.ram().as_ref().borrow());
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
        emu.mem.ram.borrow_mut()[..0xFCC0]
            .copy_from_slice(&self.bus.ram.as_ref().borrow()[..0xFCC0]);
        emu.mem.ram.borrow_mut()[0xFE00..]
            .copy_from_slice(&self.bus.ram.as_ref().borrow()[0xFE00..]);
    }

    fn call_hook_internal(&mut self, hook: *const u8, loc: u32, emu: &mut SpeedShoesCore) {
        unsafe {
            self.sync_script_with_emu(emu);
            let code = std::mem::transmute::<*const u8, VoidCFunc>(hook);
            code();
        }
    }

    pub fn hook_exists(&self, loc: u32) -> bool {
        let func_name = format!("rom_{:X}", loc);
        let lib = self.lib.as_ref().unwrap();
        unsafe { lib.symbol::<*const u8>(&func_name).is_ok() }
    }

    pub fn call_hook(&mut self, emu: &mut SpeedShoesCore, loc: u32) -> Result<(), ()> {
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

    pub fn run_frame(&mut self, input: Input) -> Result<(), String> {
        self.bus.current_input = input;
        let lib = self.lib.as_ref().unwrap();
        unsafe {
            let run_game_frame = lib
                .symbol::<VoidCFunc>("run_game_frame")
                .map_err(|e| e.to_string())?;
            run_game_frame();
        }
        self.bus.render()?;
        Ok(())
    }
}
