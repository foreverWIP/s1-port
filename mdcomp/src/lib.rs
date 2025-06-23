pub mod kosinski;
pub mod nemesis;

#[cfg(test)]
mod tests {
    use std::fs;

    use crate::nemesis;

    #[test]
    fn test_nemesis() {
        let rom = fs::read("../sonic1.bin").unwrap();
        let nem_eggman = 0x5D0FC;
        fs::write("test.bin", nemesis::decompress(&rom[nem_eggman..]).unwrap());
    }
}
