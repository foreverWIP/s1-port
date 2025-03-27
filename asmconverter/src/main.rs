use std::collections::HashSet;
use std::fmt::{Debug, Display};
use std::fs;
use std::sync::{LazyLock, Mutex, OnceLock};
use std::time::Instant;
use std::{collections::HashMap, fs::File, io::Write, ops::Range};

use itertools::Itertools;
use r68k_tools::memory::Memory;
use r68k_tools::{
    OpcodeInstance, PC, Size, disassembler::Disassembler, memory::MemoryVec, operand::Operand,
};
use sonic1::{DataDef, get_data_defs, patch_rom, read_as_symbols};

const ROM: &[u8; 0x80000] = include_bytes!("../../s1built.bin");

fn write_line(file: &mut Vec<String>, line: &str) -> Result<(), String> {
    let mut bytes = line.bytes().collect::<Vec<_>>();
    bytes.append(&mut vec![b'\n']);
    // file.write(&bytes).map(|_| ()).map_err(|e| e.to_string())
    file.push(String::from_utf8(bytes).unwrap());
    Ok(())
}

#[derive(Clone, Copy, Eq, PartialEq)]
enum GeneralOperandType {
    Register,
    StatusRegister,
    Memory,
    Value,
    Other,
}

fn get_operand_general_type(operand: &Operand) -> GeneralOperandType {
    match operand {
        Operand::DataRegisterDirect(_) => GeneralOperandType::Register,
        Operand::AddressRegisterDirect(_) => GeneralOperandType::Register,
        Operand::AddressRegisterIndirect(_) => GeneralOperandType::Memory,
        Operand::AddressRegisterIndirectWithPredecrement(_) => GeneralOperandType::Memory,
        Operand::AddressRegisterIndirectWithPostincrement(_) => GeneralOperandType::Memory,
        Operand::AddressRegisterIndirectWithDisplacement(_, _) => GeneralOperandType::Memory,
        Operand::AddressRegisterIndirectWithIndex(_, _, _) => GeneralOperandType::Memory,
        Operand::PcWithDisplacement(_) => GeneralOperandType::Memory,
        Operand::PcWithIndex(_, _) => GeneralOperandType::Memory,
        Operand::AbsoluteWord(_) => GeneralOperandType::Memory,
        Operand::AbsoluteLong(_) => GeneralOperandType::Memory,
        Operand::Immediate(size, _) => GeneralOperandType::Value,
        Operand::StatusRegister(size) => GeneralOperandType::StatusRegister,
        Operand::Branch(size, _) => GeneralOperandType::Memory,
        Operand::Number(size, _) => GeneralOperandType::Value,
        Operand::Registers(_, _) => GeneralOperandType::Other,
        Operand::UserStackPointer => GeneralOperandType::Register,
    }
}

fn get_calculated_address(
    operand: &Operand,
    cur_pc: u32,
    next_pc: u32,
    size: Size,
    is_dst: bool,
    calculated_pc_change: bool,
) -> Result<String, ()> {
    match operand {
        Operand::DataRegisterDirect(regnum) => {
            Ok(format!("{}D{}", if is_dst { "&" } else { "" }, regnum))
        }
        Operand::AddressRegisterDirect(regnum) => {
            if *regnum == 7 {
                if [
                    0xD7E, 0x5568, 0xA600, 0xE760, 0x10638, 0x1121E, 0x113FA, 0x12B82, 0x12BD0,
                    0x13B1C, 0x1626A, 0x162DC, 0x16B3C, 0x16F00,
                ]
                .contains(&cur_pc)
                {
                    Err(())
                } else {
                    Ok(format!("{}A{}", if is_dst { "&" } else { "" }, regnum))
                }
            } else {
                Ok(format!("{}A{}", if is_dst { "&" } else { "" }, regnum))
            }
        }
        Operand::AddressRegisterIndirect(regnum) => Ok(format!("A{}", regnum)),
        Operand::AddressRegisterIndirectWithPredecrement(regnum) => Ok(format!(
            "{}",
            match size {
                Size::Unsized => unimplemented!(),
                Size::Byte => format!("--A{}", regnum),
                Size::Word => format!("A{} -= 2", regnum),
                Size::Long => format!("A{} -= 4", regnum),
            }
        )),
        Operand::AddressRegisterIndirectWithPostincrement(regnum) => Ok(format!(
            "{}",
            match size {
                Size::Unsized => unimplemented!(),
                Size::Byte => format!("A{}++", regnum),
                Size::Word => format!("(A{} += 2, A{} - 2)", regnum, regnum),
                Size::Long => format!("(A{} += 4, A{} - 4)", regnum, regnum),
            }
        )),
        Operand::AddressRegisterIndirectWithDisplacement(regnum, disp) => Ok(format!(
            "A{} {}",
            regnum,
            match disp {
                0.. => format!("+ {:#X}", disp),
                _ => format!("- {:#X}", disp.abs()),
            }
        )),
        Operand::AddressRegisterIndirectWithIndex(regnum, index, disp) => Ok(format!(
            "(s32)A{} + (s8){:#X} + (s16)D{}",
            regnum, disp, index
        )),
        Operand::PcWithDisplacement(disp) => Ok(if calculated_pc_change {
            format!("{:X}", ((cur_pc as i32) + (*disp as i32)) as u32 + 2)
        } else {
            format!("{:#X}", ((cur_pc as i32) + (*disp as i32)) as u32 + 2)
        }),
        Operand::PcWithIndex(index, disp) => Ok(if calculated_pc_change {
            format!(
                "{:X} + (s16)(D{} & 0xffff)",
                ((cur_pc as i32) + (*disp as i32)) as u32 + 2,
                index
            )
        } else {
            format!(
                "{:#X} + (s16)(D{} & 0xffff)",
                ((cur_pc as i32) + (*disp as i32)) as u32 + 2,
                index
            )
        }),
        Operand::AbsoluteWord(addr) => Ok(format!("{:#X}", ((*addr as i16) as i32) as u32,)),
        Operand::AbsoluteLong(addr) => Ok(if calculated_pc_change {
            format!("{:X}", addr)
        } else {
            format!("{:#X}", addr)
        }),
        Operand::Immediate(size, imm) => Ok(if calculated_pc_change {
            format!(
                "{:X}",
                match size {
                    Size::Unsized => *imm,
                    Size::Byte => ((*imm as i8) as i32) as u32,
                    Size::Word => ((*imm as i16) as i32) as u32,
                    Size::Long => *imm,
                }
            )
        } else {
            format!(
                "{:#X}",
                match size {
                    Size::Unsized => *imm,
                    Size::Byte => ((*imm as i8) as i32) as u32,
                    Size::Word => ((*imm as i16) as i32) as u32,
                    Size::Long => *imm,
                }
            )
        }),
        Operand::StatusRegister(size) => Ok(if is_dst {
            "&SR".to_string()
        } else {
            "SR".to_string()
        }),
        Operand::Branch(size, addr) => Ok(format!("{:X}", addr)),
        Operand::Number(size, number) => Ok(if calculated_pc_change {
            format!(
                "{:X}",
                match size {
                    Size::Unsized => *number,
                    Size::Byte => (*number as i8) as i32,
                    Size::Word => (*number as i16) as i32,
                    Size::Long => *number,
                }
            )
        } else {
            format!(
                "{:#X}",
                match size {
                    Size::Unsized => *number,
                    Size::Byte => (*number as i8) as i32,
                    Size::Word => (*number as i16) as i32,
                    Size::Long => *number,
                }
            )
        }),
        Operand::Registers(_, _) => Err(()),
        Operand::UserStackPointer => Err(()),
    }
}

fn calc_generic_func_name(opcode: &OpcodeInstance) -> Result<String, ()> {
    let new_mnemonic = match opcode.mnemonic.to_lowercase().as_str() {
        "moveq" => "move",
        "lea" => "move",
        "movea" => "move",
        "addq" => "add",
        "adda" => "add",
        "addi" => "add",
        "andi" => "and",
        "ori" => "or",
        "suba" => "sub",
        "subi" => "sub",
        "subq" => "sub",
        "cmpi" => "cmp",
        "cmpa" => "cmp",
        "eori" => "eor",
        "dbf" => "dec_reg_16",
        "dbeq" => "dec_reg_16",
        m => &m,
    }
    .to_string();
    if new_mnemonic == "dec_reg_16" {
        return Ok(new_mnemonic);
    }
    match opcode.operands.len() {
        1 => Ok(format!(
            "{}{}{}",
            new_mnemonic,
            match get_operand_general_type(&opcode.operands[0]) {
                GeneralOperandType::Register => "_reg",
                GeneralOperandType::StatusRegister => "_sr",
                GeneralOperandType::Memory => "_mem",
                GeneralOperandType::Value => "_val",
                GeneralOperandType::Other => "",
            },
            match opcode.size {
                Size::Unsized => "",
                Size::Byte => "_8",
                Size::Word => "_16",
                Size::Long => "_32",
            }
        )),
        2 => {
            let operand_types = (
                get_operand_general_type(&opcode.operands[0]),
                get_operand_general_type(&opcode.operands[1]),
            );
            Ok(format!(
                "{}_{}{}",
                new_mnemonic,
                if operand_types.0 == GeneralOperandType::StatusRegister {
                    match operand_types.1 {
                        GeneralOperandType::Register => "sr_toreg",
                        GeneralOperandType::StatusRegister => unreachable!(),
                        GeneralOperandType::Memory => "sr_tomem",
                        GeneralOperandType::Value => unreachable!(),
                        GeneralOperandType::Other => "",
                    }
                } else {
                    match operand_types.1 {
                        GeneralOperandType::Register => "toreg",
                        GeneralOperandType::StatusRegister => "tosr",
                        GeneralOperandType::Memory => "tomem",
                        GeneralOperandType::Value => unreachable!(),
                        GeneralOperandType::Other => "",
                    }
                },
                match opcode.size {
                    Size::Unsized => "",
                    Size::Byte => "_8",
                    Size::Word => "_16",
                    Size::Long => "_32",
                }
            ))
        }
        _ => Err(()),
    }
}

fn get_statement(
    opcode: &OpcodeInstance,
    cur_pc: u32,
    new_pc: u32,
    unique_operations: &mut HashSet<String>,
) -> Result<String, ()> {
    match opcode.mnemonic {
        "JMP" | "BRA" | "BEQ" | "BNE" | "BCC" | "BCS" | "BMI" | "BPL" | "BGE" | "BGT" | "BLT"
        | "BLE" | "BHI" | "BLS" => {
            let conditional = if opcode.mnemonic == "BRA" || opcode.mnemonic == "JMP" {
                "".to_string()
            } else {
                format!(
                    "if ({}) ",
                    match opcode.mnemonic {
                        "BEQ" => "CCR_EQ",
                        "BNE" => "!CCR_EQ",
                        "BCC" => "CCR_CC",
                        "BCS" => "CCR_CS",
                        "BMI" => "CCR_MI",
                        "BPL" => "CCR_PL",
                        "BGE" => "CCR_GE",
                        "BGT" => "CCR_GT",
                        "BLT" => "CCR_LT",
                        "BLE" => "CCR_LE",
                        "BHI" => "CCR_HI",
                        "BLS" => "CCR_LS",
                        _ => "TODO",
                    }
                    .to_string()
                )
            };
            Ok(format!(
                "{}goto rom_{}",
                conditional,
                get_calculated_address(
                    &opcode.operands[0],
                    cur_pc,
                    new_pc,
                    opcode.size,
                    false,
                    true
                )
                .unwrap()
            ))
        }
        "DBF" => {
            let generic_func_name = calc_generic_func_name(opcode)?;
            unique_operations.insert(generic_func_name.clone());
            let reg = format!("{}", opcode.operands[0]);
            Ok(format!(
                "{}(&{}); if (({} & 0xffff) != 0xffff) goto rom_{}",
                generic_func_name,
                reg,
                reg,
                get_calculated_address(
                    &opcode.operands[1],
                    cur_pc,
                    new_pc,
                    opcode.size,
                    false,
                    true
                )
                .unwrap()
            ))
        }
        "DBEQ" => {
            let generic_func_name = calc_generic_func_name(opcode)?;
            unique_operations.insert(generic_func_name.clone());
            let reg = format!("{}", opcode.operands[0]);
            Ok(format!(
                "if (!CCR_EQ) {{{}(&{}); if (({} & 0xffff) != 0xffff) goto {};}}",
                generic_func_name,
                reg,
                reg,
                get_calculated_address(
                    &opcode.operands[1],
                    cur_pc,
                    new_pc,
                    opcode.size,
                    false,
                    true
                )
                .unwrap()
            ))
        }
        "JSR" | "BSR" => {
            match get_calculated_address(
                &opcode.operands[0],
                cur_pc,
                new_pc,
                opcode.size,
                false,
                true,
            ) {
                Ok(addr) => Ok(format!("rom_{}()", addr)),
                Err(_) => Err(()),
            }
        }
        "RTS" | "RTE" => Ok("return".to_string()),
        "NOP" => Ok("{}".to_string()),
        _ => {
            /*let operand_results = opcode
            .operands
            .iter()
            .map(|o| get_calculated_address(&o, cur_pc, new_pc, opcode.size, false, false))
            .collect_vec();*/
            let mut operand_results = Vec::new();
            for i in 0..opcode.operands.len() {
                operand_results.push(get_calculated_address(
                    &opcode.operands[i],
                    cur_pc,
                    new_pc,
                    opcode.size,
                    (opcode.operands.len() == 2 && i == 1) || (opcode.operands.len() == 1),
                    false,
                ));
            }
            if operand_results.iter().any(|r| r.is_err()) {
                return Err(());
            }
            /*let operand_strings = operand_results
            .iter()
            .map(|r| r.clone().unwrap())
            .reduce(|a, b| format!("{}, {}", a, b))
            .unwrap_or("".to_string());*/
            let mut operand_strings = Vec::new();
            for i in 0..operand_results.len() {
                if i == 0 && opcode.mnemonic != "LEA" && operand_results.len() == 2 {
                    if get_operand_general_type(&opcode.operands[0]) == GeneralOperandType::Memory {
                        operand_strings.push(format!(
                            "read_{}({})",
                            match opcode.size {
                                Size::Unsized => unreachable!(),
                                Size::Byte => "8",
                                Size::Word => "16",
                                Size::Long => "32",
                            },
                            operand_results[i].clone().unwrap()
                        ));
                    } else {
                        operand_strings.push(operand_results[i].clone().unwrap());
                    }
                } else {
                    operand_strings.push(operand_results[i].clone().unwrap());
                }
            }
            let operand_strings = operand_strings
                .iter()
                .map(|r| r.clone())
                .reduce(|a, b| format!("{}, {}", a, b))
                .unwrap_or("".to_string());
            let generic_func_name = calc_generic_func_name(opcode)?;
            unique_operations.insert(generic_func_name.clone());
            Ok(format!("{}({})", generic_func_name, operand_strings))
        }
    }
}

static SKIP_AREAS: LazyLock<Vec<Range<u32>>> = LazyLock::new(|| {
    vec![
        0x0..0x200,
        0x396..0xB10,
        0x412E..0x4170,
        0x41C8..0x4208,
        0x4A48..0x4BF0,
        0x6EF2..0x6F54,
        0x7898..0x789E,
        0x85D8..0x85F2,
        0x8F9A..0x8FB2,
        0xB7A2..0xB866,
        0xC56A..0xC574,
        0xE5A8..0xE688,
        0xF852..0xF85A,
        0x10492..0x104A2,
        0x10920..0x10934,
        0x1145E..0x11464,
        0x114D4..0x114D8,
        0x11556..0x11564,
        0x118E8..0x118EE,
        0x1200E..0x120CA,
        0x125E6..0x125EC,
        0x148CE..0x148D4,
        0x153B4..0x15446,
        0x17014..0x1709C,
        0x17918..0x1791C,
        0x1835E..0x18364,
        0x197C8..0x197DA,
        0x1B30E..0x1B32E,
        0x1B5E4..0x1B62A,
        0x1D2A6..0x1D6E6,
        // 0x1D93A..u32::MAX,
        0x1D93A..0x71B4C,
        0x72E7C..u32::MAX,
    ]
});

#[derive(Default, PartialEq, Eq)]
enum FunctionFlow {
    #[default]
    Return,
    FlowIntoNextInstruction,
    TailCall,
}

struct DisassembledFunction<'op> {
    instructions: Vec<(u32, u32, OpcodeInstance<'op>)>,
    flow: FunctionFlow,
    end: u32,
}

fn try_disassemble_block<'dis>(
    func: &DataDef,
    rom_memvec: &dyn Memory,
    disassembler: &'dis Disassembler,
) -> Result<DisassembledFunction<'dis>, ()> {
    let mut instructions = Vec::new();
    let mut last_instruction_mnemonic = String::default();
    let mut cur_pc = PC(func.start);
    loop {
        if cur_pc.0 == func.end {
            break;
        }
        unsafe {
            if SKIP_AREAS.iter().any(|a| a.contains(&cur_pc.0)) {
                break;
            }
        }
        match disassembler.disassemble(cur_pc, rom_memvec) {
            Ok((new_pc, opcode)) => {
                last_instruction_mnemonic = opcode.mnemonic.to_string();
                instructions.push((
                    cur_pc.0,
                    new_pc.0,
                    OpcodeInstance {
                        mnemonic: opcode.mnemonic,
                        size: opcode.size,
                        operands: opcode.operands.clone(),
                    },
                ));
                cur_pc = new_pc;
            }
            Err(_) => {
                if func.name == "GameProgram" {
                    println!("break");
                }
                break;
            }
        };
    }
    if instructions.len() > 0 {
        Ok(DisassembledFunction {
            instructions,
            flow: match last_instruction_mnemonic.as_str() {
                "RTS" => FunctionFlow::Return,
                "JMP" | "BRA" => FunctionFlow::TailCall,
                _ => FunctionFlow::FlowIntoNextInstruction,
            },
            end: func.end,
        })
    } else {
        Err(())
    }
}

fn main() -> Result<(), String> {
    let data_defs = get_data_defs();

    let mut outfile = Vec::new();

    let mut patched_rom = ROM.to_vec();
    patch_rom(&mut patched_rom);
    let ROM_U16: Vec<_> = patched_rom
        .chunks(2)
        .map(|c| u16::from_be_bytes((*c).try_into().unwrap()))
        .collect();
    let ROM_MEMVEC = MemoryVec::new16(PC(0), ROM_U16);

    let mut unique_operations: HashSet<String> = HashSet::with_capacity(0x4000);
    let mut disassembled_instructions = Vec::new();
    let disassembler = Disassembler::new();
    println!("Disassembling functions...");
    let dis_time_start = Instant::now();
    for func in &data_defs {
        // println!("disassembling {}", func.name);
        match try_disassemble_block(func, &ROM_MEMVEC, &disassembler) {
            Ok(v) => disassembled_instructions.push(v),
            Err(_) => continue,
        }
    }
    let dis_time_end = Instant::now();

    for func in &disassembled_instructions {
        let func_start = func.instructions[0].0;
        write_line(&mut outfile, &format!("ROMFUNC(rom_{:X});", func_start))?;
    }

    println!("Mapping functions...");
    let mut num_romlocs = 0usize;
    let map_time_start = Instant::now();
    for func in disassembled_instructions {
        let func_start = func.instructions[0].0;
        // println!("mapping {:X}", func_start);
        write_line(&mut outfile, &format!("/*ROMFUNC(rom_{:X}) {{", func_start))?;

        for opcode in &func.instructions {
            let pc = PC(opcode.0);
            if opcode.2.mnemonic == "BRA" && pc == func.instructions.last().unwrap().0 {
                write_line(
                    &mut outfile,
                    &format!(
                        // "\t{}; // rom_{:X}: {}",
                        "\trom_{}(); // {}",
                        get_calculated_address(
                            &opcode.2.operands[0],
                            pc.0,
                            opcode.1,
                            opcode.2.size,
                            false,
                            true
                        )
                        .unwrap(),
                        // pc,
                        opcode.2
                    ),
                )?;
                num_romlocs += 1;
            } else {
                write_line(
                    &mut outfile,
                    &format!(
                        "\tDEF_ROMLOC({:X}): {}; // {}",
                        pc.0,
                        match get_statement(&opcode.2, pc.0, opcode.1, &mut unique_operations) {
                            Ok(s) => {
                                s
                            }
                            Err(_) => {
                                "// TODO".to_string()
                            }
                        },
                        // pc,
                        opcode.2
                    ),
                )?;
                num_romlocs += 1;
            }
        }
        if func.flow == FunctionFlow::FlowIntoNextInstruction {
            write_line(
                &mut outfile,
                &format!(
                    "\trom_{:X}(); // Detected flow into next function",
                    func.end
                ),
            )?;
        }

        write_line(&mut outfile, &"}*/")?;
    }
    let map_time_end = Instant::now();
    const FUNCSFILE: &str = "../sonic1c/funcs.gen.c";
    prep_file(FUNCSFILE);
    let mut outfile_disk = File::options()
        .create(true)
        .write(true)
        .open(FUNCSFILE)
        .map_err(|e| e.to_string())?;
    outfile_disk
        .write(
            ("#include \"system.h\"\n#include \"opcodes.h\"\n".to_string() + &outfile.concat())
                .as_bytes(),
        )
        .map_err(|e| e.to_string())?;
    const OPSHEADERFILE: &str = "../sonic1c/opcodes.gen.h";
    prep_file(OPSHEADERFILE);
    // XNZVC
    fs::write(
        OPSHEADERFILE,
        "#pragma once\n\
#include \"system.h\"\n\
#define CCR_C (SR & 0x1)
#define CCR_V (SR & 0x2)
#define CCR_Z (SR & 0x4)
#define CCR_N (SR & 0x8)
#define CCR_X (SR & 0x10)
#define CCR_HI ((!CCR_C)&(!CCR_Z))\n\
#define CCR_LS (CCR_C|CCR_Z)\n\
#define CCR_CC (!CCR_C)\n\
#define CCR_CS CCR_C\n\
#define CCR_NE (!CCR_Z)\n\
#define CCR_EQ CCR_Z\n\
#define CCR_VC (!CCR_V)\n\
#define CCR_VS CCR_V\n\
#define CCR_PL (!CCR_N)\n\
#define CCR_MI CCR_N\n\
#define CCR_GE ((CCR_MI^CCR_VS)==0)\n\
#define CCR_LT (!CCR_GE)\n\
#define CCR_GT (CCR_GE&&CCR_NE)\n\
#define CCR_LE (CCR_LT||CCR_EQ)\n\
"
        .to_string()
            + &unique_operations
                .iter()
                .sorted()
                .map(|op| format!("extern void {}({});", op, gen_signature_for_operation(op)))
                .join("\n"),
    )
    .map_err(|e| e.to_string())?;
    println!("{} unique operations", unique_operations.len());
    {
        let mut unique_subops = unique_operations
            .iter()
            .map(|op| op.split("_").collect_vec()[0])
            .sorted()
            .collect_vec();
        unique_subops.dedup_by(|a, b| a == b);

        println!("{} unique suboperations", unique_subops.len());
    }
    println!("~{} individual instructions", num_romlocs);
    println!(
        "Disassembled all instructions in {:?}",
        dis_time_end - dis_time_start
    );
    println!(
        "Mapped all instructions in {:?}",
        map_time_end - map_time_start
    );

    Ok(())
}

fn gen_signature_for_operation(operation: &str) -> String {
    let split = operation.split("_").collect_vec();
    let parts_count = split.len() - 2;
    let mut calced_parts = Vec::new();
    if split[0] == "exg" {
        calced_parts.push("u32 *src".to_string());
        calced_parts.push("u32 *dst".to_string());
    } else {
        match split[1] {
            "toreg" => {
                calced_parts.push("u32 src".to_string());
                calced_parts.push("u32 *dst".to_string());
            }
            "tosr" => {
                calced_parts.push("u32 src".to_string());
                calced_parts.push("u32 *sr".to_string());
            }
            "tomem" => {
                calced_parts.push("u32 src".to_string());
                calced_parts.push("u32 dst".to_string());
            }
            "reg" => {
                calced_parts.push("u32 *dst".to_string());
            }
            "mem" => {
                calced_parts.push("u32 dst".to_string());
            }
            "sr" => match split[2] {
                "toreg" => {
                    calced_parts.push("u32 sr".to_string());
                    calced_parts.push("u32 *dst".to_string());
                }
                "tomem" => {
                    calced_parts.push("u32 sr".to_string());
                    calced_parts.push("u32 dst".to_string());
                }
                _ => unreachable!(),
            },
            _ => unreachable!(),
        }
    }
    calced_parts
        .iter()
        .map(|s| s.clone())
        .reduce(|a, b| format!("{}, {}", a, b))
        .unwrap()
}

fn prep_file(path: &str) {
    if fs::exists(path).unwrap() {
        _ = fs::remove_file(path);
    }
}
