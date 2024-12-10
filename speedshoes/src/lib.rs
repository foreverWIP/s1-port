use std::{
    fmt::{Display, UpperHex},
    slice::Iter,
};

pub(crate) mod emu;
pub(crate) mod script;
pub mod system;
pub mod vdp;

pub const GAME_WIDTH: u32 = 320;
pub const GAME_HEIGHT: u32 = 224;

pub(crate) type Registers = [u32; 16];

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum DataSize {
    Byte,
    Word,
    Long,
}
impl TryFrom<usize> for DataSize {
    type Error = ();

    fn try_from(value: usize) -> Result<Self, Self::Error> {
        match value {
            1 => Ok(Self::Byte),
            2 => Ok(Self::Word),
            4 => Ok(Self::Long),
            _ => Err(()),
        }
    }
}
impl Display for DataSize {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        f.write_str(match self {
            DataSize::Byte => "b",
            DataSize::Word => "w",
            DataSize::Long => "l",
        })
    }
}

pub(crate) fn comma_separated<T>(mut it: Iter<'_, T>) -> String
where
    T: UpperHex,
{
    format!(
        "[{}]",
        match it.len() {
            0 => String::default(),
            1 => format!("{:X}", it.nth(0).unwrap()),
            _ => it
                .map(|e| format!("{:X}", e))
                .reduce(|a, b| format!("{}, {}", a, b))
                .unwrap(),
        }
    )
}
