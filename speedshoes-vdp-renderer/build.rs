use std::{env, fs, path::PathBuf};

fn main() -> Result<(), String> {
    let src_dir = PathBuf::from(env::var("CARGO_MANIFEST_DIR").unwrap()).join("src");
    const CHANNEL_LOOKUP: [u32; 8] = [0, 52, 87, 116, 144, 172, 206, 255];
    let mut color_lut = vec![0u32; 0x1_0000];
    for i in 0..color_lut.len() {
        let r = CHANNEL_LOOKUP[(i >> 1) & 0b111];
        let g = CHANNEL_LOOKUP[(i >> 5) & 0b111];
        let b = CHANNEL_LOOKUP[(i >> 9) & 0b111];
        color_lut[i] = (0xff << 24) | (b << 16) | (g << 8) | (r << 0);
    }
    let mut out_lut = String::from("pub const COLOR_LUT: &[u32; 0x1_0000] = &[");
    for c in color_lut {
        out_lut += &format!("{:#010X},", c);
    }
    out_lut += "];";
    fs::write(src_dir.join("color_lut.rs"), out_lut).map_err(|e| e.to_string())?;
    Ok(())
}
