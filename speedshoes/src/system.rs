use std::{
    cell::{RefCell, UnsafeCell},
    collections::{HashMap, HashSet},
    fmt::Display,
    fs,
    rc::Rc,
    sync::{LazyLock, OnceLock, RwLock},
};

use itertools::Itertools;
use r68k_emu::cpu::ProcessingState;
use r68k_tools::{disassembler::Disassembler, memory::MemoryVec, Exception, OpcodeInstance, PC};

use crate::{
    comma_separated,
    emu::{SpeedShoesCore, SystemEmulator, SystemEmulatorRegister},
    script::ScriptEngine,
    vdp::Vdp,
    GAME_HEIGHT, GAME_WIDTH,
};

pub(crate) const SYSTEM_RAM_SIZE: usize = 0x1_0000;

#[derive(Clone, Copy)]
pub struct Input {
    pub up: bool,
    pub down: bool,
    pub left: bool,
    pub right: bool,
    pub a: bool,
    pub b: bool,
    pub c: bool,
    pub start: bool,
}
impl Default for Input {
    fn default() -> Self {
        Self {
            up: false,
            down: false,
            left: false,
            right: false,
            a: false,
            b: false,
            c: false,
            start: false,
        }
    }
}

static mut OUR_SYSTEM_GLOBAL: Option<*mut System> = None;
static DISASSEMBLER: OnceLock<Disassembler> = OnceLock::new();
fn get_disassembler() -> &'static Disassembler<'static> {
    DISASSEMBLER.get_or_init(|| Disassembler::new())
}
static mut INST_CACHE: Option<HashMap<u32, (PC, OpcodeInstance)>> = None;
static mut DESYNC_SCRIPT_MESSAGE: Option<String> = None;

fn calculate_sub_address(opcode: &OpcodeInstance, core: &SpeedShoesCore) -> Option<u32> {
    if opcode.operands.len() != 1 {
        return None;
    }
    if opcode.mnemonic != "JSR" && opcode.mnemonic != "BSR" {
        return None;
    }
    Some(match opcode.operands[0] {
        r68k_tools::operand::Operand::DataRegisterDirect(_) => unreachable!(),
        r68k_tools::operand::Operand::AddressRegisterDirect(_) => unreachable!(),
        r68k_tools::operand::Operand::AddressRegisterIndirect(regnum) => {
            core.get_reg(SystemEmulatorRegister::from(8 + regnum as usize))
        }
        r68k_tools::operand::Operand::AddressRegisterIndirectWithPredecrement(regnum) => {
            core.get_reg(SystemEmulatorRegister::from(8 + regnum as usize))
                - match opcode.size {
                    r68k_tools::Size::Unsized => unreachable!(),
                    r68k_tools::Size::Byte => 1,
                    r68k_tools::Size::Word => 2,
                    r68k_tools::Size::Long => 4,
                }
        }
        r68k_tools::operand::Operand::AddressRegisterIndirectWithPostincrement(regnum) => {
            core.get_reg(SystemEmulatorRegister::from(8 + regnum as usize))
        }
        r68k_tools::operand::Operand::AddressRegisterIndirectWithDisplacement(regnum, disp) => {
            ((core.get_reg(SystemEmulatorRegister::from(8 + regnum as usize)) as i32)
                + (disp as i32)) as u32
        }
        r68k_tools::operand::Operand::AddressRegisterIndirectWithIndex(regnum, dregnum, index) => {
            ((core.get_reg(SystemEmulatorRegister::from(8 + regnum as usize)) as i32)
                + (index as i32)) as u32
                + (core.get_reg(SystemEmulatorRegister::from(dregnum as usize)) & 0xffff)
        }
        r68k_tools::operand::Operand::PcWithDisplacement(disp) => {
            ((core.pc as i32) + (disp as i32)) as u32 + 2
        }
        r68k_tools::operand::Operand::PcWithIndex(regnum, index) => {
            ((core.pc as i32) + (index as i32)) as u32
                + (core.get_reg(SystemEmulatorRegister::from(regnum as usize)) & 0xffff)
                + 2
        }
        r68k_tools::operand::Operand::AbsoluteWord(addr) => ((addr as i16) as i32) as u32,
        r68k_tools::operand::Operand::AbsoluteLong(addr) => addr,
        r68k_tools::operand::Operand::Immediate(size, _) => todo!(),
        r68k_tools::operand::Operand::StatusRegister(size) => todo!(),
        r68k_tools::operand::Operand::Branch(size, addr) => addr,
        r68k_tools::operand::Operand::Number(size, _) => unreachable!(),
        r68k_tools::operand::Operand::Registers(_, _) => unreachable!(),
        r68k_tools::operand::Operand::UserStackPointer => unreachable!(),
    })
}

pub fn synchronize_script(pc: u32, checkmem: bool) -> bool {
    unsafe {
        if DESYNC_SCRIPT_MESSAGE.is_some() {
            return false;
        }
    }
    let our_system = unsafe { OUR_SYSTEM_GLOBAL.unwrap().as_mut().unwrap() };
    /*let msg = format!(
        "synchronizing emu to script {} -> {}",
        our_system.get_symbol(our_system.core.pc),
        our_system.get_symbol(pc)
    );
    our_system.print_nested(msg);*/
    let mut inst_sync_counter = 0;
    const MAX_SYNC_INSTS: usize = 896_040 / 1024;
    let mut sync_pcs = Vec::with_capacity(MAX_SYNC_INSTS / 32);
    our_system.catching_up_to_script = true;
    while our_system.core.pc != pc {
        our_system.run_instruction(false, Some(pc));
        sync_pcs.push(our_system.core.pc);
        our_system.emu_machine_instructions_ran += 1;
        inst_sync_counter += 1;
        if inst_sync_counter == MAX_SYNC_INSTS {
            break;
        }
    }
    our_system.catching_up_to_script = false;
    assert_eq!(
        our_system.core.pc,
        pc,
        "{}",
        comma_separated(sync_pcs.iter())
    );
    let ret = match our_system.check_accuracy(checkmem) {
        Ok(_) => true,
        Err(msg) => {
            unsafe {
                DESYNC_SCRIPT_MESSAGE = Some(msg);
            }
            false
        }
    };
    if !ret {
        return ret;
    }
    our_system
        .script_engine
        .as_mut()
        .unwrap()
        .sync_emu_with_script(&mut our_system.core);
    ret
}

pub struct System {
    id: &'static str,
    symbol_map: HashMap<u32, String>,
    symbol_cache: HashMap<u32, String>,
    script_machine_instructions_ran: u64,
    emu_machine_instructions_ran: u64,
    initial_pc: u32,
    initial_sp: u32,
    vblank_addr: u32,
    catching_up_to_script: bool,
    rom_backup: MemoryVec,
    pub vdp: Rc<RefCell<Vdp>>,
    pub(crate) core: SpeedShoesCore,
    script_engine: Option<Box<ScriptEngine>>,
    pub unimplemented_subs_frame: HashSet<u32>,
    unimplemented_subs_total: HashSet<u32>,
    pub fb_plane_a_low: Box<[u32]>,
    pub fb_plane_b: Box<[u32]>,
    pub fb_plane_s_low: Box<[u32]>,
    pub fb_plane_a_high: Box<[u32]>,
    pub fb_plane_s_high: Box<[u32]>,
}

impl Drop for System {
    fn drop(&mut self) {
        const FILENAME: &str = "todo_subs.txt";
        if fs::exists(FILENAME).unwrap_or(true) {
            _ = fs::remove_file(FILENAME);
        }
        if !self.unimplemented_subs_total.is_empty() {
            let mut subs_vec: Vec<_> = self.unimplemented_subs_total.iter().collect();
            subs_vec.sort();
            _ = fs::write(
                "todo_subs.txt",
                subs_vec
                    .iter()
                    .map(|s| format!("{:X}", s))
                    .reduce(|a, b| format!("{}\n{}", a, b))
                    .unwrap(),
            );
        }
    }
}

impl System {
    fn print_nested(&self, msg: String) {
        println!(
            "{}",
            "  ".repeat((self.initial_sp - self.core.ssp()) as usize / 4) + &msg
        );
    }

    fn get_symbol(&mut self, at: u32) -> String {
        if let Some(sym) = self.symbol_cache.get(&at) {
            return sym.clone();
        }
        let sym = format!(
            "{:X} ({})",
            at,
            match self.symbol_map.get(&at) {
                Some(sym) => sym.clone(),
                None => {
                    let base_key = self
                        .symbol_map
                        .iter()
                        .filter(|s| *s.0 < at)
                        .sorted_by_key(|s| s.0.abs_diff(at))
                        .nth(0);
                    match base_key {
                        Some(base_key) => {
                            let offset = base_key.0.abs_diff(at);
                            base_key.1.clone()
                                + &(if offset == 0 {
                                    "".to_string()
                                } else {
                                    format!("+{:X}", offset)
                                })
                        }
                        None => format!("<unknown_{:X}>", at),
                    }
                }
            }
        );
        self.symbol_cache.insert(at, sym.clone());
        sym
    }

    fn get_instruction(&self, at: u32) -> Result<&(PC, OpcodeInstance), Exception> {
        unsafe {
            let cache = INST_CACHE.get_or_insert_default();
            if !cache.contains_key(&at) {
                cache.insert(
                    at,
                    get_disassembler()
                        .disassemble(PC(at), &self.rom_backup)?
                        .clone(),
                );
            }
            Ok(&cache.get(&at).unwrap())
        }
    }

    fn check_accuracy(&self, checkmem: bool) -> Result<(), String> {
        let script_engine = self.script_engine.as_ref().unwrap();
        let emu_reg_state = self.core.get_reg_state();
        let script_reg_state = script_engine.get_reg_state();
        let emu_ram = self.ram();
        let script_ram = script_engine.ram();
        let mut ram_differences: Vec<String> = Vec::new();
        let mut reg_differences: Vec<String> = Vec::new();
        for i in 0..17 {
            if i == 15 {
                continue;
            }
            let mut emu_reg = emu_reg_state[i];
            let mut script_reg = script_reg_state[i];
            if (8..16).contains(&i) {
                emu_reg &= 0xff_ffff;
                script_reg &= 0xff_ffff;
            }
            if emu_reg != script_reg {
                reg_differences.push(format!(
                    "{:?}: expected {:#010X}, got {:#010X}",
                    SystemEmulatorRegister::from(i),
                    emu_reg,
                    script_reg,
                ))
            }
        }
        // if checkmem || !reg_differences.is_empty() {
        {
            let emu_ram_u64 = emu_ram.borrow().as_ptr() as *const u64;
            let script_ram_u64 = script_ram.borrow().as_ptr() as *const u64;
            let mut differing_u64s = Vec::new();
            unsafe {
                for i in 0..0x2000 {
                    // skip over sound driver ram & stack
                    if (0x1E00..0x1EB8).contains(&i) || (0x1F98..0x1FC0).contains(&i) {
                        continue;
                    }
                    if *emu_ram_u64.add(i) != *script_ram_u64.add(i) {
                        differing_u64s.push(i);
                    }
                }
                for diff in differing_u64s {
                    let emu_u64 = (*emu_ram_u64.add(diff)).to_be_bytes();
                    let script_u64 = (*script_ram_u64.add(diff)).to_be_bytes();
                    for i in 0..8 {
                        let control_u8 = emu_u64[i];
                        let our_u8 = script_u64[i];
                        if control_u8 != our_u8 {
                            ram_differences.push(format!(
                                "ram_{:X}: expected {:#X}, got {:#X}",
                                (diff * 8) + i,
                                control_u8,
                                our_u8
                            ));
                        }
                    }
                }
            }
            /*let emu_ram = emu_ram.as_ref().borrow();
            let script_ram = script_ram.as_ref().borrow();
            for i in 0..0x1_0000usize {
                if (0xF000..0xF600).contains(&i) || (0xFCC0..0xFE00).contains(&i) {
                    continue;
                }

                let control_u8 = emu_ram[i];
                let our_u8 = script_ram[i];
                if control_u8 != our_u8 {
                    ram_differences.push(format!(
                        "ram_{:X}: expected {:#X}, got {:#X}",
                        i, control_u8, our_u8
                    ));
                }
            }*/
        }

        if !ram_differences.is_empty() || !reg_differences.is_empty() {
            return Err(format!(
                "Simulation mismatch at pc {:#X}:\n{}",
                self.core.pc(),
                reg_differences.join("\n") + "\n" + &ram_differences.join("\n"),
            ));
        } else {
            Ok(())
        }
    }

    pub fn new(
        name: &'static str,
        rom_things: (&Vec<u8>, u32),
        symbol_map: Option<HashMap<u32, String>>,
        use_scripts: bool,
        test_mode: bool,
    ) -> Result<System, String> {
        unsafe {
            DESYNC_SCRIPT_MESSAGE = None;
        }
        let rom = Rc::new(rom_things.0.clone());
        let ram = Rc::new(RefCell::new(vec![0u8; SYSTEM_RAM_SIZE]));
        let vdp = Rc::new(RefCell::new(Vdp::new(rom.clone(), ram.clone())));
        let sp_addr = u32::from_be_bytes(rom[0..4].try_into().unwrap());
        let pc_addr = u32::from_be_bytes(rom[4..8].try_into().unwrap());

        let mut core = SpeedShoesCore::new("sonic1", rom, ram, vdp.clone()).unwrap();
        core.reset();

        // core.set_reg(SystemEmulatorRegister::A7, sp_addr);
        // core.pc = pc_addr;

        let mut ret = System {
            id: name,
            symbol_map: symbol_map.unwrap_or_default(),
            symbol_cache: HashMap::new(),
            script_machine_instructions_ran: 0,
            emu_machine_instructions_ran: 0,
            initial_pc: pc_addr,
            initial_sp: sp_addr,
            vblank_addr: rom_things.1,
            catching_up_to_script: false,
            rom_backup: MemoryVec::new8(PC(0), rom_things.0.clone()),
            fb_plane_a_low: vec![0u32; (GAME_WIDTH * GAME_HEIGHT) as usize].into_boxed_slice(),
            fb_plane_b: vec![0u32; (GAME_WIDTH * GAME_HEIGHT) as usize].into_boxed_slice(),
            fb_plane_s_low: vec![0u32; (GAME_WIDTH * GAME_HEIGHT) as usize].into_boxed_slice(),
            fb_plane_a_high: vec![0u32; (GAME_WIDTH * GAME_HEIGHT) as usize].into_boxed_slice(),
            fb_plane_s_high: vec![0u32; (GAME_WIDTH * GAME_HEIGHT) as usize].into_boxed_slice(),
            vdp,
            core,
            script_engine: None,
            unimplemented_subs_frame: HashSet::new(),
            unimplemented_subs_total: HashSet::new(),
        };
        let script_engine = if use_scripts {
            Some(Box::new(ScriptEngine::new(name, ret.core.mem.rom.clone())?))
        } else {
            None
        };
        ret.script_engine = script_engine;
        Ok(ret)
    }

    fn ram(&self) -> Rc<RefCell<Vec<u8>>> {
        self.core.ram().clone()
    }

    pub fn script_machine_instructions_ran(&self) -> u64 {
        self.script_machine_instructions_ran
    }

    pub fn emu_machine_instructions_ran(&self) -> u64 {
        self.emu_machine_instructions_ran
    }

    fn call_function(&mut self, target_pc: Option<u32>, opcode_raw: u16) -> Result<bool, String> {
        let (next_addr, opcode) = self
            .get_instruction(self.core.pc)
            .map(|(pc, op)| (pc.0, op))
            .unwrap();

        let sub_addr = calculate_sub_address(&opcode, &self.core).unwrap();
        /*let msg = format!(
            "calling subroutine {} -> {}",
            self.get_symbol(self.core.pc),
            self.get_symbol(next_addr.0),
        );
        self.print_nested(msg);*/
        if let Some(target_pc) = target_pc {
            if self.core.pc == target_pc {
                return Ok(false);
            }
        }
        match &mut self.script_engine {
            Some(_) => {
                if self.script_engine.as_ref().unwrap().hook_exists(sub_addr) {
                    let checkmem = self
                        .script_engine
                        .as_mut()
                        .unwrap()
                        .call_hook(&mut self.core, sub_addr)
                        .unwrap();
                    unsafe {
                        if let Some(msg) = (&raw const DESYNC_SCRIPT_MESSAGE).as_ref().unwrap() {
                            return Err(msg.clone());
                        }
                    }
                    while self.core.pc != next_addr {
                        self.run_emu_instruction();
                        self.emu_machine_instructions_ran += 1;
                    }
                    self.check_accuracy(checkmem)?;
                    self.script_engine
                        .as_mut()
                        .unwrap()
                        .sync_emu_with_script(&mut self.core);
                    Ok(sub_addr == self.vblank_addr)
                } else {
                    self.unimplemented_subs_frame.insert(sub_addr);
                    self.run_emu_instruction();
                    self.script_machine_instructions_ran += 1;
                    self.emu_machine_instructions_ran += 1;
                    Ok(opcode_raw == 0b0100_1110_0111_0011)
                }
            }
            None => {
                self.run_emu_instruction();
                self.script_machine_instructions_ran += 1;
                self.emu_machine_instructions_ran += 1;
                Ok(opcode_raw == 0b0100_1110_0111_0011)
            }
        }
    }

    fn run_instruction(
        &mut self,
        call_hooks: bool,
        target_pc: Option<u32>,
    ) -> Result<bool, String> {
        let opcode_raw = self.core.read_16(self.core.pc);
        let is_call = ((opcode_raw & 0b1111_1111_1100_0000) == 0b0100_1110_1000_0000)
            || ((opcode_raw & 0b1111_1111_0000_0000) == 0b0110_0001_0000_0000);
        if is_call && call_hooks {
            self.call_function(target_pc, opcode_raw)
        } else {
            self.run_emu_instruction();
            self.script_machine_instructions_ran += 1;
            self.emu_machine_instructions_ran += 1;
            Ok(opcode_raw == 0b0100_1110_0111_0011)
        }
    }

    pub fn run_frame(&mut self, input: Input) -> Result<(), String> {
        // let ourselves be accessible to scripts
        // for checking accuracy
        unsafe {
            OUR_SYSTEM_GLOBAL = Some(self);
        }
        self.emu_machine_instructions_ran = 0;
        self.script_machine_instructions_ran = 0;
        self.unimplemented_subs_frame.clear(); // will be populated over the frame
        self.core.set_input(input); // controller input

        loop {
            // we check for error conditions before running
            // any instructions, just in case we ended up
            // in a very weird state

            // stop on 68k exception
            if self.exception_encountered() {
                return Err(match self.core.pc {
                    _ => "Exception hit!",
                }
                .to_string()
                    + &format!(" pc = {:X}", self.core.pc));
            }

            // check for error from script check
            unsafe {
                if let Some(msg) = &DESYNC_SCRIPT_MESSAGE {
                    return Err(msg.clone());
                }
            }

            // actually run the instruction
            if self.run_instruction(true, None)? {
                break;
            }
        }

        // accumulate our unimplemented subroutines
        for sub in &self.unimplemented_subs_frame {
            self.unimplemented_subs_total.insert(*sub);
        }
        Ok(())
    }

    fn run_emu_instruction(&mut self) {
        let pc_before = self.core.pc;
        let sp_before = self.core.dar[15];
        self.core.execute1();
        if self.exception_encountered() {
            panic!();
        }
        /*let pc_after = self.core.pc;
        {
            let msg = format!(
                "{} -> {}",
                self.get_symbol(pc_before),
                self.get_symbol(pc_after),
            );
            self.print_nested(msg);
        }*/
    }

    fn exception_encountered(&self) -> bool {
        (0x3B8..0x5F0).contains(&self.core.pc)
    }

    pub fn reset(&mut self) -> Result<(), String> {
        self.core.sr_to_flags(0);
        self.core.reset();
        if let Some(script_engine) = &mut self.script_engine {
            _ = script_engine
                .reset(&mut self.core)
                .map_err(|e| println!("{}", e));
        }
        Ok(())
    }

    pub fn render(&mut self) -> Result<(), String> {
        let vdp = self.vdp();
        if vdp.as_ref().borrow().display_enabled() {
            self.fb_plane_s_high.fill(0);
            self.fb_plane_s_low.fill(0);
            for y in 0usize..224 {
                let fb_range =
                    (y * GAME_WIDTH as usize)..((y * GAME_WIDTH as usize) + GAME_WIDTH as usize);
                vdp.as_ref().borrow_mut().render_screen_line(
                    y as u16,
                    &mut self.fb_plane_b[fb_range.clone()],
                    &mut self.fb_plane_a_low[fb_range.clone()],
                    &mut self.fb_plane_s_low[fb_range.clone()],
                    &mut self.fb_plane_a_high[fb_range.clone()],
                    &mut self.fb_plane_s_high[fb_range],
                );
            }
        }
        Ok(())
    }

    pub fn bg_color(&self) -> u32 {
        self.vdp.as_ref().borrow().bg_color()
    }

    fn vdp(&self) -> Rc<RefCell<Vdp>> {
        self.vdp.clone()
    }
}
