use crate::kosinski;

#[derive(Clone, Copy)]
pub enum DacSampleMode {
    Dpcm4Bit,
    Pcm8Bit,
}
pub struct DacSample {
    pub data: Vec<u8>,
    pub sample_rate: u16,
    pub mode: DacSampleMode,
}
pub struct DacDriver {
    just_got_sample: bool,
    sample_id: u8,
    sample_data_index: usize,
    sample_data_len: usize,
    sample_data: Vec<DacSample>,
    sample_accum: u8,
    low_nibble: bool,
}
impl DacDriver {
    const DAC_DECODE_TABLE: &[u8] = &[
        0x0, 0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80, 0xff, 0xfe, 0xfc, 0xf8, 0xf0, 0xe0, 0xc0,
    ];

    pub fn cur_sample_rate(&self) -> u16 {
        if self.sample_id < 0x81 {
            return 0;
        }
        self.sample_data[self.sample_id as usize - 0x81].sample_rate
    }

    pub fn cur_sample_mode(&self) -> Option<DacSampleMode> {
        if self.sample_id < 0x81 {
            return None;
        }
        Some(self.sample_data[self.sample_id as usize - 0x81].mode)
    }

    pub fn new(rom: &[u8]) -> Self {
        let dac_driver = kosinski::decompress(&rom[(0x72e7c)..]).unwrap();
        Self {
            just_got_sample: false,
            sample_id: 0,
            low_nibble: false,
            sample_accum: 0,
            sample_data_index: 0,
            sample_data: vec![
                // kick
                DacSample {
                    data: dac_driver[0xee..0x440].to_vec(),
                    sample_rate: 8250,
                    mode: DacSampleMode::Dpcm4Bit,
                },
                // snare
                DacSample {
                    data: dac_driver[0x440..0xbb0].to_vec(),
                    sample_rate: 24000,
                    mode: DacSampleMode::Dpcm4Bit,
                },
                // timpani hi
                DacSample {
                    data: dac_driver[0xbb0..0x1bc6].to_vec(),
                    sample_rate: 9750,
                    mode: DacSampleMode::Dpcm4Bit,
                },
                // timpani mid
                DacSample {
                    data: dac_driver[0xbb0..0x1bc6].to_vec(),
                    sample_rate: 8750,
                    mode: DacSampleMode::Dpcm4Bit,
                },
                // timpani midlow
                DacSample {
                    data: dac_driver[0xbb0..0x1bc6].to_vec(),
                    sample_rate: 7150,
                    mode: DacSampleMode::Dpcm4Bit,
                },
                // timpani low
                DacSample {
                    data: dac_driver[0xbb0..0x1bc6].to_vec(),
                    sample_rate: 7000,
                    mode: DacSampleMode::Dpcm4Bit,
                },
                // dummy
                DacSample {
                    data: dac_driver[0xbb0..0x1bc6].to_vec(),
                    sample_rate: 0,
                    mode: DacSampleMode::Dpcm4Bit,
                },
                // sega
                DacSample {
                    data: rom[0x79688..0x80000].to_vec(),
                    sample_rate: 16000,
                    mode: DacSampleMode::Pcm8Bit,
                },
            ],
            sample_data_len: 0,
        }
    }

    pub fn play_sample(&mut self, sample: u8) {
        self.sample_id = sample;
        if self.sample_id > 0x80 && self.sample_id < 0x89 {
            if self.sample_id == 0x88 {
                println!("playing sega sound");
            }
            self.just_got_sample = true;
        }
    }

    pub fn update(&mut self, write_i: extern "C" fn(a: u8, v: u8)) {
        if self.sample_id < 0x80 {
            return;
        }
        let sample_metadata = &self.sample_data[self.sample_id as usize - 0x81];
        if self.just_got_sample {
            self.just_got_sample = false;
            self.sample_data_index = 0;
            self.sample_data_len = sample_metadata.data.len();
            self.sample_accum = 0x80;
            self.low_nibble = false;
            write_i(0x2b, 0x80);
        }
        let sample = sample_metadata.data[self.sample_data_index];
        match sample_metadata.mode {
            DacSampleMode::Dpcm4Bit => {
                let nibble = if self.low_nibble {
                    self.sample_data_index += 1;
                    sample & 0xf
                } else {
                    sample >> 4
                };
                self.sample_accum = self
                    .sample_accum
                    .wrapping_add(Self::DAC_DECODE_TABLE[nibble as usize]);
                write_i(0x2a, self.sample_accum);
            }
            DacSampleMode::Pcm8Bit => {
                self.sample_data_index += 1;
                write_i(0x2a, sample);
            }
        }

        self.low_nibble = !self.low_nibble;
        if self.sample_data_index >= self.sample_data_len {
            self.sample_id = 0;
        }
    }
}
