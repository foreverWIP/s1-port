use std::{fs, ops::Range};

use itertools::Itertools;

// patch our rom to work better with the engine
pub fn patch_rom(rom: &mut Vec<u8>) {
    fn patch_nop(rom: &mut Vec<u8>, at: usize) {
        rom[at] = 0x4e;
        rom[at + 1] = 0x71;
    }
    fn patch_rts(rom: &mut Vec<u8>, at: usize) {
        rom[at] = 0x4e;
        rom[at + 1] = 0x75;
    }
    // skips checksum check
    rom[0x30e..0x310].copy_from_slice(&u16::to_be_bytes(0x602e));
    // skip some initialization already handled by emulator
    rom[0x206] = 0b01001110;
    rom[0x207] = 0b11111001;
    rom[0x208] = 0x00;
    rom[0x209] = 0x00;
    rom[0x20a] = 0x03;
    rom[0x20b] = 0x00;
    patch_nop(rom, 0x33E);
    patch_nop(rom, 0x340);
    patch_nop(rom, 0x342);
    patch_nop(rom, 0x344);
    patch_nop(rom, 0x346);
    patch_nop(rom, 0x348);
    patch_nop(rom, 0x34A);
    patch_nop(rom, 0x34C);
    patch_nop(rom, 0x364);
    patch_nop(rom, 0x366);
    patch_nop(rom, 0x368);
    patch_nop(rom, 0x36A);
    patch_nop(rom, 0x36C);
    patch_nop(rom, 0x36E);
    patch_nop(rom, 0x370);
    patch_nop(rom, 0x372);
    patch_nop(rom, 0x374);

    // return immediately from sound driver
    patch_rts(rom, 0x71b4c);
    // skip sound driver load
    patch_rts(rom, 0x134a);

    // patch WaitForVBla with a jump to the vblank handler
    rom[0x29a0] = 0x4e;
    rom[0x29a1] = 0xf9;
    rom[0x29a2] = 0x00;
    rom[0x29a3] = 0x00;
    rom[0x29a4] = 0x0b;
    rom[0x29a5] = 0x10;

    // patch rte in vblank handler with normal rts
    rom[0xb6d] = 0x75;
}

#[derive(Clone, Default)]
pub struct ASSymbol {
    pub name: String,
    pub value: u32,
    pub size: Option<usize>,
    pub used: bool,
    pub variable: bool,
}
impl From<String> for ASSymbol {
    fn from(value: String) -> Self {
        let mut ret = Self::default();
        let words: Vec<_> = value.split_ascii_whitespace().collect();
        ret.name = words[0].to_string();
        ret.value = usize::from_str_radix(words[2], 16).unwrap() as u32;
        ret.size = match isize::from_str_radix(words[3], 10) {
            Ok(size) => {
                if size >= 1 {
                    Some(size as usize)
                } else {
                    None
                }
            }
            Err(_) => None,
        };
        ret.used = if words[4] == "1" { true } else { false };
        ret.variable = if words[4] == "1" { true } else { false };
        ret
    }
}
pub fn read_as_symbols(file: &str) -> Vec<ASSymbol> {
    let mut ret = Vec::new();
    let starting_line = file
        .lines()
        .position(|l| l == "Symbols in Segment CODE")
        .unwrap()
        + 1;
    for line in file.lines().skip(starting_line) {
        ret.push(ASSymbol::from(line.to_string()));
    }
    ret
}

#[derive(Clone, Debug)]
pub struct DataDef {
    pub name: String,
    pub start: u32,
    pub end: u32,
}
impl DataDef {
    fn new(name: &str, start: u32, end: u32) -> Self {
        Self {
            name: name.to_string(),
            start,
            end,
        }
    }
}

pub fn get_data_defs() -> Vec<DataDef> {
    if !cfg!(debug_assertions) {
        return Vec::new();
    }
    let mut SKIP_AREAS = vec![
        0x0..0xB10,
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
        0x1D93A..u32::MAX,
    ];
    let as_symbols = read_as_symbols(&fs::read_to_string("../sonic.map").unwrap());
    let filtered_symbols: Vec<_> = as_symbols
        .iter()
        .filter(|sym| symbol_filter(sym, &SKIP_AREAS))
        .map(|s| s.clone())
        .sorted_by(|a, b| Ord::cmp(&a.value, &b.value))
        .collect();
    let mut unique_symbols = filtered_symbols.clone();
    unique_symbols.dedup_by(|a, b| a.value == b.value);
    for i in 0..(unique_symbols.len() - 1) {
        let sym_start = &unique_symbols[i];
        let sym_end = &unique_symbols[i + 1];
        if !symbol_syntax_filter(&sym_start.name) {
            continue;
        }
        if !symbol_value_filter(sym_start.value, &SKIP_AREAS) {
            continue;
        }
        if !symbol_name_filter(&sym_start.name) {
            SKIP_AREAS.push(sym_start.value..sym_end.value);
        }
    }
    let mut data_defs: Vec<DataDef> = Vec::new();
    {
        for i in 0..(unique_symbols.len() - 1) {
            if SKIP_AREAS
                .iter()
                .any(|a| a.contains(&unique_symbols[i].value))
            {
                continue;
            }
            match data_defs.last_mut() {
                Some(def) => {
                    if unique_symbols[i].value == def.start {
                        def.end = unique_symbols[i + 1].value;
                    } else {
                        let name = unique_symbols[i].name.clone();
                        data_defs.push(DataDef::new(
                            &name,
                            unique_symbols[i].value,
                            unique_symbols[i + 1].value,
                        ))
                    }
                }
                None => {
                    let name = unique_symbols[i].name.clone();
                    data_defs.push(DataDef::new(
                        &name,
                        unique_symbols[i].value,
                        unique_symbols[i + 1].value,
                    ))
                }
            }
        }
    }
    data_defs
}

fn symbol_value_filter(v: u32, SKIP_AREAS: &Vec<Range<u32>>) -> bool {
    ((v & 1) == 0) && !SKIP_AREAS.iter().any(|r| r.contains(&v))
}

fn symbol_syntax_filter(s: &str) -> bool {
    !s.starts_with("v_")
        && !s.starts_with("z")
        && ((s.starts_with("Newt_Action"))
            || (s.starts_with("Bas_Action"))
            || (s.starts_with("Plat_Move"))
            || (s.starts_with("Debug_"))
            || (s == "ReactToItem.proximity")
            || (!s.contains(".")))
}

fn symbol_name_filter(s: &str) -> bool {
    !s.starts_with("SonPLC_")
        && !s.starts_with("Kos_")
        && !s.starts_with("Nem_")
        && !s.starts_with("Eni_")
        && !s.starts_with("Art_")
        && !s.starts_with("PLC_")
        && !s.starts_with("Pal_")
        && !s.starts_with("Map_")
        && !s.starts_with("ptr_")
        && !s.starts_with("MS_")
        && !s.starts_with("M_")
        && !s.starts_with("Ani_")
        && !s.starts_with("byte_")
        && !s.starts_with("word_")
        && !s.starts_with("SonicDynPLC")
        && !s.starts_with("DebugList")
        && !s.starts_with("ObjPos_")
        && !s.starts_with("Blk16_")
        && !s.starts_with("Blk256_")
        && !s.starts_with("Geyser_Types")
        && !s.starts_with("Hud_1")
        && !s.starts_with("AniArt_Index")
        && !s.starts_with("AniArt_MZextra")
        && !s.starts_with("AniArt_Ending_Flower3_sequence")
        && !s.starts_with("SonAni_")
        && !s.starts_with("A_CSon_1")
        && !s.ends_with("_Index")
        && !s.ends_with("_Data")
}

fn symbol_filter(s: &&ASSymbol, SKIP_AREAS: &Vec<Range<u32>>) -> bool {
    symbol_value_filter(s.value, SKIP_AREAS)
        && symbol_syntax_filter(&s.name)
        && symbol_name_filter(&s.name)
}
