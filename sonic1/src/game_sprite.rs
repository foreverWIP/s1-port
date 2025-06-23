use std::{
    io::{Cursor, Read},
    ptr::swap_nonoverlapping,
    sync::{Arc, LazyLock, OnceLock},
};

fn get_byte(cursor: &mut Cursor<&[u8]>) -> u8 {
    let mut ret = [0];
    cursor.read(&mut ret);
    ret[0]
}

fn get_word(cursor: &mut Cursor<&[u8]>) -> u16 {
    let mut ret = [0, 0];
    cursor.read(&mut ret);
    u16::from_be_bytes(ret)
}

fn bpp_4_to_8(bpp_4: &[u8]) -> Vec<u8> {
    let mut ret = Vec::with_capacity(bpp_4.len() * 2);
    for i in 0..bpp_4.len() {
        ret.push(bpp_4[i] >> 4);
        ret.push(bpp_4[i] & 0xf);
    }
    ret
}

fn bpp_8_to_4(bpp_8: &[u8]) -> Option<Vec<u8>> {
    if !bpp_8.len().is_multiple_of(2) {
        return None;
    }
    let mut ret = Vec::with_capacity(bpp_8.len() / 2);
    for bs in bpp_8.chunks(2) {
        ret.push((bs[0] << 4) | (bs[1] & 0xf));
    }
    Some(ret)
}

fn flip_x<T>(pixels: &mut [T], width: usize) -> bool {
    if !pixels.len().is_multiple_of(width) {
        return false;
    }

    let height = pixels.len() / width;
    for y in 0..height {
        // if x is even, then this covers exactly half of elements in a row (width / 2 swaps)
        // this also works for odd values because integer division rounds toward 0 ((width / 2) - 1 swaps, leaves middle element untouched)
        for x in 0..(width / 2) {
            pixels.swap(y * width + x, y * width + (width - x - 1));
        }
    }

    true
}

fn flip_y<T>(pixels: &mut [T], width: usize) -> bool {
    if !pixels.len().is_multiple_of(width) {
        return false;
    }

    let height = pixels.len() / width;
    for y in 0..(height / 2) {
        unsafe {
            let top_row_ptr = pixels.as_mut_ptr().add(width * y);
            let bottom_row_ptr = pixels.as_mut_ptr().add(width * (height - y - 1));
            swap_nonoverlapping(top_row_ptr, bottom_row_ptr, width);
        }
    }

    true
}

type VDPCell = [u8; 0x20];

struct SpriteSubMapping {
    x: i8,
    y: i8,
    width_tiles: u8,
    height_tiles: u8,
    tile_metadata: TileMetadata,
    rendered: OnceLock<Vec<u8>>,
}
impl SpriteSubMapping {
    pub fn decode(cursor: &mut Cursor<&[u8]>) -> Self {
        let y = get_byte(cursor) as i8;
        let (width_tiles, height_tiles) = {
            let wh = get_byte(cursor);
            ((wh >> 2) + 1, (wh & 0b11) + 1)
        };
        let tile_metadata = TileMetadata::decode(cursor);
        let x = get_byte(cursor) as i8;

        Self {
            x,
            y,
            width_tiles,
            height_tiles,
            tile_metadata,
            rendered: OnceLock::new(),
        }
    }

    pub fn render(&self, art_8bpp: &[u8]) -> &Vec<u8> {
        let width_tiles = self.width_tiles as usize;
        let height_tiles = self.height_tiles as usize;
        let width = self.width_tiles as usize * 8;
        let height = self.height_tiles as usize * 8;
        let flip_x = self.tile_metadata.flip_x;
        let flip_y = self.tile_metadata.flip_y;
        let tile_start = self.tile_metadata.tile_start as usize;
        self.rendered.get_or_init(|| {
            let mut ret = vec![0u8; width * height];

            let mut cur_art_row = tile_start * 0x40;

            for tile_x in 0..width_tiles {
                for tile_y in 0..height_tiles {
                    for y in 0..8 {
                        let art_row = &art_8bpp[cur_art_row..(cur_art_row + 8)];

                        let out_index = ((tile_y * 8) + y) * width;

                        for x in 0..8 {
                            ret[out_index + (tile_x * 8) + x] = art_row[x];
                        }

                        cur_art_row += 8;
                    }
                }
            }

            if flip_x {
                self::flip_x(&mut ret, width);
            }

            if flip_y {
                self::flip_y(&mut ret, width);
            }

            ret
        })
    }
}

struct SpriteFrame {
    submaps: Vec<SpriteSubMapping>,
    rendered: OnceLock<Vec<u8>>,
}
impl SpriteFrame {
    pub fn decode(cursor: &mut Cursor<&[u8]>) -> Self {
        let num_sprite_pieces = get_byte(cursor);

        let mut ret = Vec::new();
        for _ in 0..num_sprite_pieces {
            ret.push(SpriteSubMapping::decode(cursor));
        }
        ret.reverse();
        Self {
            submaps: ret,
            rendered: OnceLock::new(),
        }
    }

    pub fn render(&self, art_8bpp: &[u8]) -> &Vec<u8> {
        let submaps = &self.submaps;

        self.rendered.get_or_init(|| {
            let (width, height, center_x, center_y) = {
                let mut min_x = 0i16;
                let mut max_x = 0i16;
                let mut min_y = 0i16;
                let mut max_y = 0i16;

                for sm in submaps {
                    min_x = min_x.min(sm.x as i16);
                    min_y = min_y.min(sm.y as i16);
                    max_x = max_x.max(sm.x as i16 + sm.width_tiles as i16 * 8);
                    max_y = max_y.max(sm.y as i16 + sm.height_tiles as i16 * 8);
                }

                (
                    (min_x.abs() + max_x + 1) as usize,
                    (min_y.abs() + max_y + 1) as usize,
                    min_x.abs() as u16,
                    min_y.abs() as u16,
                )
            };

            let mut ret = vec![0; width as usize * height as usize];

            for sm in submaps {
                let sm_pixels = sm.render(art_8bpp);
                let sm_width = sm.width_tiles as usize * 8;
                let sm_height = sm.height_tiles as usize * 8;
                let tile_draw_pos_x = (sm.x as i16 + center_x as i16);
                let tile_draw_pos_y = (sm.y as i16 + center_y as i16);
                assert!(tile_draw_pos_x >= 0);
                assert!(tile_draw_pos_y >= 0);
                let tile_draw_pos_x = tile_draw_pos_x as usize;
                let tile_draw_pos_y = tile_draw_pos_y as usize;
                assert!(tile_draw_pos_x + sm_width < width);
                assert!(tile_draw_pos_y + sm_height < height);

                for y in 0..sm_height {
                    for x in 0..sm_width {
                        let out_idx = (tile_draw_pos_y + y) * width + (tile_draw_pos_x + x);
                        let sm_pixel = sm_pixels[y * sm_width + x];
                        if sm_pixel > 0 {
                            ret[out_idx] = sm_pixel;
                        }
                    }
                }
            }

            ret
        })
    }
}

#[derive(Clone, Copy)]
struct TileMetadata {
    high_priority: bool,
    palette_line: u8,
    flip_x: bool,
    flip_y: bool,
    tile_start: u16,
}
impl TileMetadata {
    pub fn decode(cursor: &mut Cursor<&[u8]>) -> Self {
        let raw = get_word(cursor);
        Self {
            high_priority: raw >= 0x8000,
            palette_line: ((raw >> 0x1fffu16.count_ones()) & 0b11) as u8,
            flip_x: ((raw >> 0x7ffu16.count_ones()) & 1) != 0,
            flip_y: ((raw >> 0xfffu16.count_ones()) & 1) != 0,
            tile_start: raw & 0x7ff,
        }
    }
}

#[derive(Clone, Copy)]
enum ArtCompression {
    None,
    Nemesis,
    Kosinski,
}

fn get_sprite_frames(rom: &[u8], mappings_addr: u32) -> Vec<SpriteFrame> {
    let mut frame_offset_cursor = Cursor::new(&rom[(mappings_addr as usize)..]);
    let mut ret = Vec::new();

    fn build_frame(ret: &mut Vec<SpriteFrame>, rom: &[u8], offset: u32) {
        ret.push(SpriteFrame::decode(&mut Cursor::new(
            &rom[(offset as usize)..],
        )));
    }

    let first_frame_offset = mappings_addr + get_word(&mut frame_offset_cursor) as u32;
    build_frame(&mut ret, rom, first_frame_offset);
    let num_frames = (first_frame_offset - mappings_addr) / 2;
    for _ in 1..num_frames {
        let offset = mappings_addr + get_word(&mut frame_offset_cursor) as u32;
        build_frame(&mut ret, rom, offset);
    }

    ret
}

#[cfg(test)]
mod tests {
    use std::fs;

    use super::{bpp_4_to_8, get_sprite_frames};

    #[test]
    fn render_sprite() {
        let rom = fs::read("../sonic1.bin").unwrap();
        let test_map = 0xAF12;
        let test_art_ptr = 0x1FD8C;
        let test_art = bpp_4_to_8(&mdcomp::nemesis::decompress(&rom[test_art_ptr..]).unwrap());
        let frames = get_sprite_frames(&rom, test_map);
        println!("{} frames", frames.len());
        for i in 0..frames.len() {
            fs::write(format!("test{}.bin", i), &frames[i].render(&test_art));
        }
    }
}
