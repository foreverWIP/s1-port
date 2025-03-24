#![feature(concat_idents)]

mod dacdriver;
pub mod driver;
mod kosinski;
pub(crate) mod vgm_ffi;

pub(crate) const MD_CLOCK: f64 = 53693175.0;
pub(crate) const M68K_CLOCK: f64 = MD_CLOCK / 7.0;
pub(crate) const Z80_CLOCK: f64 = MD_CLOCK / 15.0;
pub(crate) const FM_SAMPLE_RATE: f64 = M68K_CLOCK / (6.0 * 6.0 * 4.0);
pub(crate) const PSG_SAMPLE_RATE: f64 = Z80_CLOCK / 16.0;
pub(crate) const MCYCLES_FRAME: usize = 896_040;
pub(crate) const FM_CYCLES_FRAME: usize = MCYCLES_FRAME / 7;
pub(crate) const PSG_CYCLES_FRAME: usize = MCYCLES_FRAME / 15;

pub(crate) fn read_slice_u8(slice: &[u8], addr: u32) -> u8 {
    slice[addr as usize]
}
pub(crate) fn read_slice_i8(slice: &[u8], addr: u32) -> i8 {
    slice[addr as usize] as i8
}
pub(crate) fn read_slice_u8_inc(slice: &[u8], addr: &mut u32) -> u8 {
    println!("{:X}++", addr);
    *addr += 1;
    slice[*addr as usize - 1]
}
pub(crate) fn read_slice_i8_inc(slice: &[u8], addr: &mut u32) -> i8 {
    read_slice_u8_inc(slice, addr) as i8
}
pub(crate) fn read_slice_u16(slice: &[u8], addr: u32) -> u16 {
    (read_slice_u8(slice, addr) as u16) << 8 | read_slice_u8(slice, addr + 1) as u16
}
pub(crate) fn read_slice_i16(slice: &[u8], addr: u32) -> i16 {
    read_slice_u16(slice, addr) as i16
}
pub(crate) fn read_slice_u16_inc(slice: &[u8], addr: &mut u32) -> u16 {
    ((read_slice_u8_inc(slice, addr) as u16) << 8) | (read_slice_u8_inc(slice, addr) as u16)
}
pub(crate) fn read_slice_i16_inc(slice: &[u8], addr: &mut u32) -> i16 {
    read_slice_u16_inc(slice, addr) as i16
}
pub(crate) fn read_slice_u32(slice: &[u8], addr: u32) -> u32 {
    ((read_slice_u8(slice, addr) as u32) << 24)
        | ((read_slice_u8(slice, addr + 1) as u32) << 16)
        | ((read_slice_u8(slice, addr + 2) as u32) << 8)
        | (read_slice_u8(slice, addr + 3) as u32)
}

#[cfg(test)]
mod tests {
    use std::{f64, rc::Rc, sync::Arc, time::Instant};

    use crate::{FM_SAMPLE_RATE, driver::SoundDriver};

    const ROM: &[u8; 0x80000] = include_bytes!("../../s1built.bin");

    #[test]
    fn parse_smps() {
        const OUTPUT_FREQ: usize = 44100;
        let spec = hound::WavSpec {
            channels: 2,
            sample_rate: OUTPUT_FREQ as u32,
            bits_per_sample: 16,
            sample_format: hound::SampleFormat::Int,
        };
        let mut writer = hound::WavWriter::create("test.wav", spec).unwrap();
        let mut driver = SoundDriver::new(Arc::new(ROM.to_vec()), 44100);
        driver.update();
        driver.play_sound(0x86);
        let max_frames = 60 * 60;
        let mut time_buf = Vec::with_capacity(max_frames);
        for frame in 0..max_frames {
            // println!("rendering frame {}", frame);
            let now = Instant::now();
            driver.update();
            let after = Instant::now();
            time_buf.push((after - now).as_secs_f64());
            println!("update took {}s", time_buf.last().unwrap());
            let sound_buffer = &driver.safe_audio_buffer;
            for i in 0..driver.safe_audio_buffer.len().min(44100 * 2) {
                writer
                    .write_sample(sound_buffer[i as usize] as i16)
                    .unwrap();
            }
        }
        writer.finalize().unwrap();
        println!(
            "avg update time: {}",
            time_buf.iter().sum::<f64>() / time_buf.len() as f64
        );
    }
}
