#pragma once

#include "system.h"

#define VRAM_FG 0xc000
#define VRAM_BG 0xe000
#define VRAM_SPRITES 0xf800
#define VRAM_HSCROLL 0xfc00
#define TILE_WIDTH 8
#define TILE_HEIGHT TILE_WIDTH
#define TILE_SIZE_PIXELS (TILE_WIDTH * TILE_HEIGHT)
#define TILE_SIZE_BYTES (TILE_SIZE_PIXELS / 2)

#define copy_tilemap(src, dst_base, dst_x, dst_y, width, height)               \
  {                                                                            \
    copy_tilemap_to_vram(                                                      \
        src,                                                                   \
        VRAM_PTR_TO_VDP_COMMAND(dst_base + ((dst_y * 2) * 64) + (dst_x * 2)),  \
        width - 1, height - 1);                                                \
  }

void copy_tilemap_to_vram(u32 src_addr, u32 dst_command, u8 width, u8 height);
void clear_screen(void);
void vdp_setup(void);
void handle_scroll_horiz(void);
void handle_scroll_vert(void);
void scroll_bg_full(void);
void scroll_bg_y_relative(void);
void scroll_bg_y(void);
void scroll_bg_y_absolute(void);
void scroll_bg_layer_1(void);
void scroll_bg_layer_2(void);
void scroll_bg_layer_3(void);
void scroll_update_tiles_bg(void);
void scroll_update_tiles(void);
void draw_bg_layer_1(void);
void draw_blocks_scroll_vert_full(void);
void draw_blocks_scroll_vert_alt(void);
void calc_vram_pos_relative(void);
void calc_vram_pos(void);
void draw_bg_layer_3_alt(void);
void update_tiles_on_start(void);
void draw_chunks(void);