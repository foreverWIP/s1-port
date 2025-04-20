use std::io::{Cursor, Read};

#[derive(Clone)]
struct NemesisState<'state> {
    source: Cursor<&'state [u8]>,
    dictionary: Vec<u8>,
    xor_mode: bool,
    destination: Vec<u8>,
    remaining: u16,
    row_pixels_left: u16,
    compressed_accum: u16,
    bit_counter: u16,
}
impl<'state> NemesisState<'state> {
    fn new(source: &'state [u8]) -> Self {
        Self {
            source: Cursor::new(source),
            dictionary: vec![0; 0x200],
            xor_mode: Default::default(),
            destination: Vec::new(),
            remaining: Default::default(),
            row_pixels_left: Default::default(),
            compressed_accum: Default::default(),
            bit_counter: Default::default(),
        }
    }

    fn read_byte(&mut self) -> Result<u8, String> {
        let mut buf = [0];
        self.source.read(&mut buf).map_err(|e| e.to_string())?;
        // println!("read {:X}", buf[0]);
        Ok(buf[0])
    }

    fn read_word(&mut self) -> Result<u16, String> {
        let mut buf = [0, 0];
        self.source.read(&mut buf).map_err(|e| e.to_string())?;
        // println!("read {:X}", buf[0]);
        Ok(u16::from_be_bytes(buf))
    }

    fn write_bytes(&mut self, values: &[u8]) {
        for value in values {
            self.destination.push(*value);
        }
    }

    fn add_to_dictionary(&mut self, at: usize, value: u8) {
        // println!("dict[{:X}] {:X}", at, value);
        self.dictionary[at as usize] = value;
    }

    fn get_next_compressed(&mut self) -> Result<(), String> {
        if self.bit_counter < 9 {
            self.bit_counter += 8;

            self.compressed_accum <<= 8;
            self.compressed_accum |= self.read_byte()? as u16;
        }
        Ok(())
    }
}

fn build_dictionary(state: &mut NemesisState) -> Result<(), String> {
    let mut d0: u8;
    let mut d7: u8;

    d7 = state.read_byte()?;

    if d7 == 0xff {
        return Ok(());
    }

    loop {
        loop {
            d0 = state.read_byte()?;

            if (d0 & 0x80) == 0 {
                break;
            }

            if d0 == 0xff {
                return Ok(());
            }

            d7 = d0;
        }

        d7 &= 0xf;
        d7 |= d0 & 0x70;
        d0 &= 0xf;

        let d1 = 8 - d0;

        if d1 == 0 {
            let index: usize = state.read_byte()? as usize * 2;

            state.add_to_dictionary(index, d0);
            state.add_to_dictionary(index + 1, d7);
        } else {
            let mut index: usize = ((state.read_byte()? as usize) << d1) * 2;
            for _ in 0..(1 << d1) {
                state.add_to_dictionary(index, d0);
                state.add_to_dictionary(index + 1, d7);
                index += 2;
            }
        }
    }
}

pub fn decompress(src: &[u8]) -> Result<Vec<u8>, String> {
    let mut state = NemesisState::new(src);
    let header = state.read_word()?;

    state.xor_mode = (header & 0x8000) != 0;

    state.remaining = (header << 3) & 0xffff;

    state.row_pixels_left = 8;
    let mut d2 = 0;
    let mut d4 = 0;

    build_dictionary(&mut state)?;

    state.compressed_accum = state.read_word()?;

    state.bit_counter = 16;

    let mut d0 = 0;
    let mut d1 = 0;

    loop {
        while d0 != 0 {
            d0 -= 1;
            d4 <<= 4;
            d4 |= d1 as u32;

            state.row_pixels_left -= 1;
            if state.row_pixels_left == 0 {
                if state.xor_mode {
                    d2 ^= d4;
                    state.write_bytes(&d2.to_be_bytes());
                } else {
                    state.write_bytes(&d4.to_be_bytes());
                }

                state.remaining -= 1;
                if state.remaining == 0 {
                    return Ok(state.destination);
                }

                d4 = 0;
                state.row_pixels_left = 8;
            }
        }

        let mut index: usize = (state.compressed_accum >> (state.bit_counter - 8)) as usize & 0xff;

        if index < 0xfc {
            index *= 2;

            state.bit_counter -= state.dictionary[index] as u16;

            state.get_next_compressed()?;

            d0 = state.dictionary[index + 1];
            d1 = d0;

            d1 &= 0xf;
            d0 &= 0xf0;
        } else {
            state.bit_counter -= 6;

            state.get_next_compressed()?;

            state.bit_counter -= 7;

            d0 = (state.compressed_accum >> state.bit_counter) as u8;
            d1 = d0;

            d1 &= 0xf;
            d0 &= 0x70;

            state.get_next_compressed()?;
        }

        d0 >>= 4;

        d0 += 1;
    }
}
