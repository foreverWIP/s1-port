use std::{
    borrow::Borrow,
    cell::{RefCell, UnsafeCell},
    collections::{HashMap, HashSet},
    fmt::Display,
    fs,
    panic::set_hook,
    rc::Rc,
    sync::{LazyLock, OnceLock, RwLock},
};

use itertools::Itertools;
use r68k_emu::cpu::ProcessingState;
use r68k_tools::{disassembler::Disassembler, memory::MemoryVec, Exception, OpcodeInstance, PC};

use crate::{
    comma_separated,
    emu::{SpeedShoesCore, SystemEmulator, SystemEmulatorRegister},
    script::{ScriptEngine, TestFlags},
    vdp::Vdp,
    DataSize, GAME_HEIGHT, GAME_WIDTH,
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
impl Display for Input {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        f.write_fmt(format_args!(
            "{}{}{}{}{}{}{}{}",
            if self.up { "^" } else { " " },
            if self.down { "v" } else { " " },
            if self.left { "<" } else { " " },
            if self.right { ">" } else { " " },
            if self.a { "a" } else { " " },
            if self.b { "b" } else { " " },
            if self.c { "c" } else { " " },
            if self.start { "s" } else { " " },
        ))
    }
}
impl From<u8> for Input {
    fn from(value: u8) -> Self {
        Self {
            up: ((value >> 7) & 1) != 0,
            down: ((value >> 6) & 1) != 0,
            left: ((value >> 5) & 1) != 0,
            right: ((value >> 4) & 1) != 0,
            a: ((value >> 3) & 1) != 0,
            b: ((value >> 2) & 1) != 0,
            c: ((value >> 1) & 1) != 0,
            start: ((value >> 0) & 1) != 0,
        }
    }
}
impl From<Input> for u8 {
    fn from(value: Input) -> Self {
        (if value.up { 0x80 } else { 0 })
            | (if value.down { 0x40 } else { 0 })
            | (if value.left { 0x20 } else { 0 })
            | (if value.right { 0x10 } else { 0 })
            | (if value.a { 0x08 } else { 0 })
            | (if value.b { 0x04 } else { 0 })
            | (if value.c { 0x02 } else { 0 })
            | (if value.start { 0x01 } else { 0 })
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

pub fn synchronize_script(pc: u32) -> bool {
    unsafe {
        if DESYNC_SCRIPT_MESSAGE.is_some() {
            return false;
        }
    }
    let our_system = unsafe { OUR_SYSTEM_GLOBAL.unwrap().as_mut().unwrap() };
    if !our_system.test_mode {
        return true;
    }
    let test_level = our_system.script_engine.get_test_level();
    if test_level == TestFlags::TEST_NONE {
        return true;
    }
    our_system.last_script_pc = pc;
    let mut inst_sync_counter = 0;
    const MAX_SYNC_INSTS: usize = 896_040 * 60 * 10;
    our_system.sync_pcs.fill(0);
    /*{
        let msg = format!("script pc: {}", our_system.get_symbol(pc),);
        our_system.print_nested(&msg);
    }*/
    while our_system.core.as_ref().unwrap().pc != pc {
        let pc_before = our_system.core.as_ref().unwrap().pc;
        our_system.run_emu_instruction();
        let pc_after = our_system.core.as_ref().unwrap().pc;
        /*if !(0x1438..0x2160).contains(&pc_before)
            && !(0x132AC..0x15DF6).contains(&pc_before)
            && !(0x9B6E..0xE14C).contains(&pc_before)
            && !(0x626E..0x73B6).contains(&pc_before)
            && !(0x1B59A..0x1B7AA).contains(&pc_before)
            && !(0xB88..0x11B6).contains(&pc_before)
            && !(0x1C7DA..0x1D104).contains(&pc_before)
            && !(0xADA2..0xAE4E).contains(&pc_before)
            && !(0xFD38..0xFD70).contains(&pc_before)
        {
            let msg = format!(
                "{} -> {}",
                our_system.get_symbol(pc_before),
                our_system.get_symbol(pc_after),
            );
            our_system.print_nested(&msg);
        }*/
        if inst_sync_counter < our_system.sync_pcs.len() {
            our_system.sync_pcs[inst_sync_counter] = our_system.core.as_ref().unwrap().pc;
        }
        our_system.emu_machine_instructions_ran += 1;
        inst_sync_counter += 1;
        /*if inst_sync_counter >= MAX_SYNC_INSTS {
            assert_eq!(
                our_system.core.as_ref().unwrap().pc,
                pc,
                "{}",
                comma_separated(our_system.sync_pcs.iter())
            );
            break;
        }*/
    }
    match our_system.check_accuracy(test_level) {
        Ok(_) => true,
        Err(msg) => {
            unsafe {
                DESYNC_SCRIPT_MESSAGE = Some(msg);
            }
            false
        }
    }
}

pub struct System {
    id: &'static str,
    symbol_map: HashMap<u32, String>,
    symbol_cache: HashMap<u32, String>,
    script_machine_instructions_ran: u64,
    emu_machine_instructions_ran: u64,
    currently_executing_function: u32,
    sync_pcs: Vec<u32>,
    trace_log: Vec<String>,
    initial_pc: u32,
    last_script_pc: u32,
    initial_sp: u32,
    vblank_addr: u32,
    rom_backup: MemoryVec,
    pub last_frame_ram: Option<Vec<u8>>,
    pub vdp: Rc<RefCell<Vdp>>,
    pub(crate) core: Option<SpeedShoesCore>,
    script_engine: Box<ScriptEngine>,
    pub unimplemented_subs_frame: HashSet<u32>,
    unimplemented_subs_total: HashSet<u32>,
    test_mode: bool,
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
    pub fn fb_plane_a_low(&self) -> &Box<[u32]> {
        &self.script_engine.bus.fb_plane_a_low
    }
    pub fn fb_plane_b_low(&self) -> &Box<[u32]> {
        &self.script_engine.bus.fb_plane_b_low
    }
    pub fn fb_plane_b_high(&self) -> &Box<[u32]> {
        &self.script_engine.bus.fb_plane_b_high
    }
    pub fn fb_plane_s_low(&self) -> &Box<[u32]> {
        &self.script_engine.bus.fb_plane_s_low
    }
    pub fn fb_plane_a_high(&self) -> &Box<[u32]> {
        &self.script_engine.bus.fb_plane_a_high
    }
    pub fn fb_plane_s_high(&self) -> &Box<[u32]> {
        &self.script_engine.bus.fb_plane_s_high
    }

    fn print_nested(&mut self, msg: &str) {
        /*self.trace_log.push(format!(
            "{}",
            "  ".repeat((self.initial_sp - self.core.ssp()) as usize / 4) + &msg
        ));*/
        println!(
            "{}",
            "  ".repeat(
                (self.initial_sp - self.core.as_ref().map(|c| c.ssp()).unwrap_or_default())
                    as usize
                    / 4
            ) + &msg
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

    fn check_accuracy(&mut self, test_flags: TestFlags) -> Result<(), String> {
        if !self.test_mode {
            return Ok(());
        }
        let emu_reg_state = self.core.as_ref().unwrap().get_reg_state();
        let script_reg_state = self.script_engine.get_reg_state();
        let emu_ram = self.ram();
        let script_ram = self.script_engine.ram();
        let mut ram_differences: Vec<String> = Vec::new();
        let mut reg_differences: Vec<String> = Vec::new();
        if test_flags.contains(TestFlags::TEST_REGS) {
            for i in 0..17 {
                if i == 15 {
                    continue;
                }
                if i == 16 && !test_flags.contains(TestFlags::TEST_SR) {
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
        }
        if test_flags.contains(TestFlags::TEST_MEM) {
            let emu_ram_u64 = emu_ram.as_ref().borrow().as_ptr() as *const u64;
            let script_ram_u64 = script_ram.as_ref().borrow().as_ptr() as *const u64;
            let mut differing_u64s = Vec::new();
            let mut contiguous = true;
            unsafe {
                for i in 0..0x2000 {
                    // skip over sound driver ram & stack
                    if (0x1E00..0x1EB8).contains(&i) || (0x1F98..0x1FC0).contains(&i) {
                        continue;
                    }
                    if *emu_ram_u64.add(i) != (*script_ram_u64.add(i)) {
                        differing_u64s.push(i);
                    }
                }
                let mut last_diff = differing_u64s.get(0).map(|d| *d).unwrap_or_default();
                for diff in differing_u64s {
                    let last_contiguous = contiguous;
                    contiguous = diff.abs_diff(last_diff) == 1;
                    last_diff = diff;
                    if contiguous {
                        if !last_contiguous {
                            ram_differences.push("...".to_string());
                        }
                        continue;
                    }
                    for i in 0..8 {
                        let control_u8 = emu_ram.as_ref().borrow()[(diff * 8) + i];
                        let our_u8 = script_ram.as_ref().borrow()[(diff * 8) + i];
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
            let emu_ram = emu_ram.as_ref().borrow();
            let script_ram = script_ram.as_ref().borrow();
            for i in 0..0x1_0000usize {
                if (0xF000..0xF600).contains(&i) || (0xFCC0..0xFE00).contains(&i) {
                    continue;
                }

                let control_u8 = emu_ram[i];
                let our_u8 = script_ram[i];
                if control_u8 != our_u8 {
                    ram_differences.push(format!(
                        "ram_{:04X}: expected {:#04X}, got {:#04X}",
                        i, control_u8, our_u8
                    ));
                }
            }
            let emu_vram = &self.vdp.as_ref().borrow().vram;
            let script_vram = &self.script_engine.bus.vdp.as_ref().borrow().vram;
            for i in 0..(0x1_0000 / 2) {
                let control_word: u16 =
                    ((emu_vram[i * 2] as u16) << 8) | (emu_vram[i * 2 + 1] as u16);
                let our_word: u16 =
                    ((script_vram[i * 2] as u16) << 8) | (script_vram[i * 2 + 1] as u16);
                if control_word != our_word {
                    ram_differences.push(format!(
                        "vdp_{:04X}: expected {:#06X}, got {:#06X}",
                        i * 2,
                        control_word,
                        our_word
                    ));
                    break;
                }
            }
        }

        {
            let emu_vdp = &self.vdp.as_ref().borrow();
            let script_vdp = &self.script_engine.bus.vdp.as_ref().borrow();
            if emu_vdp.dst_ptr != script_vdp.dst_ptr {
                ram_differences.push(format!(
                    "vdp_dst_ptr: expected {:?}, got {:?}",
                    emu_vdp.dst_ptr, script_vdp.dst_ptr
                ));
            }
            if emu_vdp.ctrl_cachedword != script_vdp.ctrl_cachedword {
                ram_differences.push(format!(
                    "vdp_cachedword: expected {:?}, got {:?}",
                    emu_vdp.ctrl_cachedword, script_vdp.ctrl_cachedword
                ));
            }
        }

        if !ram_differences.is_empty() || !reg_differences.is_empty() {
            dbg!(self.vdp.as_ref().borrow());
            dbg!(self.script_engine.bus.vdp.as_ref().borrow());
            return Err(format!(
                "Simulation mismatch at pc {} (calling function {}):\nFirst {} PCs ran: {}\n{}",
                self.get_symbol(self.core.as_ref().unwrap().pc()),
                self.get_symbol(self.currently_executing_function),
                self.sync_pcs.len(),
                comma_separated(self.sync_pcs.iter()),
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
        hw_planes_mode: bool,
    ) -> Result<System, String> {
        unsafe {
            DESYNC_SCRIPT_MESSAGE = None;
        }
        let rom = Rc::new(rom_things.0.clone());
        let ram = vec![0u8; SYSTEM_RAM_SIZE];
        let our_ram = Rc::new(RefCell::new(ram.clone()));
        let vdp = Rc::new(RefCell::new(Vdp::new(
            rom.clone(),
            our_ram.clone(),
            hw_planes_mode,
        )));
        let sp_addr = u32::from_be_bytes(rom[0..4].try_into().unwrap());
        let pc_addr = u32::from_be_bytes(rom[4..8].try_into().unwrap());

        let mut core = if test_mode {
            Some({
                let mut ret =
                    SpeedShoesCore::new("sonic1", rom.clone(), our_ram, vdp.clone()).unwrap();
                ret.reset();
                ret
            })
        } else {
            None
        };

        // core.set_reg(SystemEmulatorRegister::A7, sp_addr);
        // core.pc = pc_addr;

        Ok(System {
            id: name,
            symbol_map: symbol_map.unwrap_or_default(),
            symbol_cache: HashMap::new(),
            script_machine_instructions_ran: 0,
            emu_machine_instructions_ran: 0,
            currently_executing_function: pc_addr,
            sync_pcs: vec![0; 16],
            trace_log: Vec::new(),
            initial_pc: pc_addr,
            last_script_pc: 0,
            initial_sp: sp_addr,
            vblank_addr: rom_things.1,
            rom_backup: MemoryVec::new8(PC(0), rom_things.0.clone()),
            last_frame_ram: None,
            vdp,
            core,
            script_engine: Box::new(ScriptEngine::new(
                name,
                rom,
                Rc::new(RefCell::new(ram.clone())),
                hw_planes_mode,
            )?),
            unimplemented_subs_frame: HashSet::new(),
            unimplemented_subs_total: HashSet::new(),
            test_mode,
        })
    }

    fn ram(&self) -> Rc<RefCell<Vec<u8>>> {
        self.core.as_ref().unwrap().ram().clone()
    }

    pub fn script_machine_instructions_ran(&self) -> u64 {
        self.script_machine_instructions_ran
    }

    pub fn emu_machine_instructions_ran(&self) -> u64 {
        self.emu_machine_instructions_ran
    }

    fn call_function(&mut self, target_pc: Option<u32>, opcode_raw: u16) -> Result<bool, String> {
        let (next_addr, opcode) = self
            .get_instruction(self.core.as_ref().unwrap().pc)
            .map(|(pc, op)| (pc.0, op))
            .unwrap();

        let sub_addr = calculate_sub_address(&opcode, &self.core.as_ref().unwrap()).unwrap();
        let prev_executing_function = self.currently_executing_function;
        self.currently_executing_function = sub_addr;
        if let Some(target_pc) = target_pc {
            if self.core.as_ref().unwrap().pc == target_pc {
                return Ok(false);
            }
        }
        let result = if self.script_engine.hook_exists(sub_addr) {
            self.script_engine
                .call_hook(&mut self.core.as_mut().unwrap(), sub_addr)
                .unwrap();
            unsafe {
                if let Some(msg) = (&raw const DESYNC_SCRIPT_MESSAGE).as_ref().unwrap() {
                    return Err(msg.clone());
                }
            }
            self.sync_pcs.fill(0);
            let mut inst_sync_counter = 0;
            while self.core.as_ref().unwrap().pc != next_addr {
                if inst_sync_counter < self.sync_pcs.len() {
                    self.sync_pcs[inst_sync_counter] = self.core.as_ref().unwrap().pc;
                }
                self.run_emu_instruction();
                self.emu_machine_instructions_ran += 1;
                inst_sync_counter += 1;
            }
            self.check_accuracy(self.script_engine.get_test_level())?;
            self.script_engine
                .sync_emu_with_script(&mut self.core.as_mut().unwrap());
            Ok(sub_addr == self.vblank_addr)
        } else {
            self.unimplemented_subs_frame.insert(sub_addr);
            self.run_emu_instruction();
            self.script_machine_instructions_ran += 1;
            self.emu_machine_instructions_ran += 1;
            Ok(opcode_raw == 0b0100_1110_0111_0011)
        };
        self.currently_executing_function = prev_executing_function;
        result
    }

    fn run_instruction(
        &mut self,
        call_hooks: bool,
        target_pc: Option<u32>,
    ) -> Result<bool, String> {
        let pc = self.core.as_ref().unwrap().pc;
        let opcode_raw = self.core.as_mut().unwrap().read_16(pc);
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
        if let Some(core) = self.core.as_mut() {
            core.set_input(input); // controller input
        }

        if let Some(ram) = &self.last_frame_ram {
            let ram = ram.clone();
            set_hook(Box::new(move |phi| {
                // fs::write("lastram.bin", &ram);
            }));
        }

        self.last_script_pc = 0;
        self.script_engine.run_frame(input)?;

        if self.test_mode {
            let mut prev_pc = self.core.as_ref().unwrap().pc;
            loop {
                // we check for error conditions before running
                // any instructions, just in case we ended up
                // in a very weird state

                // stop on 68k exception
                if self.exception_encountered() {
                    return Err(match self.core.as_ref().unwrap().pc {
                        _ => "Exception hit!",
                    }
                    .to_string()
                        + &format!(" pc = {:X}", self.core.as_ref().unwrap().pc));
                }

                // check for error from script check
                unsafe {
                    if let Some(msg) = &DESYNC_SCRIPT_MESSAGE {
                        return Err(msg.clone());
                    }
                }

                // actually run the instruction
                /*if self.run_instruction(true, None)? {
                    break;
                }*/

                if prev_pc == 0xB6C {
                    if let Some(core) = &self.core {
                        let our_vblank_count = self
                            .script_engine
                            .bus
                            .read_memory::<{ DataSize::Long }>(0xFFFE0C);
                        let emu_vblank_count = core.mem.read_memory::<{ DataSize::Long }>(0xFFFE0C);
                        if emu_vblank_count >= our_vblank_count {
                            break;
                        }
                    }
                }
                self.run_emu_instruction();
                prev_pc = self.core.as_ref().unwrap().pc;
            }

            self.check_accuracy(self.script_engine.get_test_level())?;

            if let Some(ram) = &mut self.last_frame_ram {
                ram.copy_from_slice(&self.core.as_ref().unwrap().ram().as_ref().borrow());
            } else {
                self.last_frame_ram =
                    Some(self.core.as_ref().unwrap().ram().as_ref().borrow().clone());
            }

            // accumulate our unimplemented subroutines
            for sub in &self.unimplemented_subs_frame {
                self.unimplemented_subs_total.insert(*sub);
            }
        }
        Ok(())
    }

    fn run_emu_instruction(&mut self) {
        let pc_before = self.core.as_ref().unwrap().pc;
        let sp_before = self.core.as_ref().unwrap().dar[15];
        self.core.as_mut().unwrap().execute1();
        let pc_after = self.core.as_ref().unwrap().pc;
        /*{
            let msg = format!(
                "{} -> {}",
                self.get_symbol(pc_before),
                self.get_symbol(pc_after),
            );
            self.print_nested(&msg);
        }*/
    }

    fn exception_encountered(&self) -> bool {
        (0x3B8..0x5F0).contains(&self.core.as_ref().unwrap().pc)
    }

    pub fn reset(&mut self) -> Result<(), String> {
        unsafe {
            OUR_SYSTEM_GLOBAL = Some(self);
        }
        if let Some(core) = self.core.as_mut() {
            core.sr_to_flags(0);
            core.reset();
        }
        _ = self.script_engine.reset().map_err(|e| println!("{}", e));
        Ok(())
    }

    pub fn render(&mut self) -> Result<(), String> {
        // self.core.mem.render()?;
        self.script_engine.bus.render()?;
        Ok(())
    }

    pub fn bg_color(&self) -> u32 {
        self.script_engine.bus.vdp.as_ref().borrow().bg_color()
    }

    fn vdp(&self) -> Rc<RefCell<Vdp>> {
        self.vdp.clone()
    }
}
