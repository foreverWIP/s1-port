use std::io::{Cursor, Read};

pub fn decompress<'src>(src: &'src [u8]) -> Result<Vec<u8>, String> {
    type ByteCursor<'src> = Cursor<&'src [u8]>;
    struct DecompressState<'state> {
        cursor: ByteCursor<'state>,
        cur_descriptor: u16,
        cur_descriptor_bits_left: u8,
    }
    impl<'state> DecompressState<'state> {
        pub fn new(src: &'state [u8]) -> Self {
            Self {
                cursor: ByteCursor::new(src),
                cur_descriptor: 0,
                cur_descriptor_bits_left: 0,
            }
        }

        pub fn get_byte(&mut self) -> Result<u8, String> {
            let mut ret = [0u8];
            self.cursor
                .read_exact(&mut ret)
                .map_err(|e| e.to_string())?;
            Ok(ret[0])
        }

        pub fn get_new_descriptor(&mut self) -> Result<(), String> {
            let mut descriptor_bytes = [0u8, 0u8];
            self.cursor
                .read_exact(&mut descriptor_bytes)
                .map_err(|e| e.to_string())?;
            self.cur_descriptor = u16::from_le_bytes(descriptor_bytes);
            self.cur_descriptor_bits_left = 16;
            Ok(())
        }

        pub fn get_bit(&mut self) -> Result<bool, String> {
            let ret = (self.cur_descriptor & 1) != 0;
            self.cur_descriptor >>= 1;
            self.cur_descriptor_bits_left -= 1;
            if self.cur_descriptor_bits_left == 0 {
                self.get_new_descriptor()?;
            }
            Ok(ret)
        }
    }

    let mut dst = Vec::with_capacity(src.len());
    let mut state = DecompressState::new(src);

    state.get_new_descriptor()?;

    loop {
        if state.get_bit()? {
            dst.push(state.get_byte()?);
        } else {
            let (len, offset) = if !state.get_bit()? {
                let mut len = 0;
                if state.get_bit()? {
                    len += 2;
                }
                if state.get_bit()? {
                    len += 1;
                }
                len += 1;

                (len, state.get_byte()? as isize - 0x100)
            } else {
                let low = state.get_byte()?;
                let high = state.get_byte()?;

                let len = match high % 8 {
                    0 => {
                        let ret = state.get_byte()?;
                        if ret == 0 {
                            break;
                        }
                        if ret == 1 {
                            continue;
                        }
                        ret as usize
                    }
                    high => high as usize + 1,
                };
                (len, u16::from_le_bytes([low, high >> 3]) as isize - 0x2000)
            };

            for _ in 0..=len {
                dst.push(dst[(dst.len() as isize + offset) as usize]);
            }
        }
    }

    Ok(dst)
}
