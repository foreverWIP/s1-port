#pragma once

void color_move_towards_white(void);
void palette_move_towards_white(void);
void palette_fade_to_white_runvblank(void);
void palette_fade_to_white_loop(void);
void palette_fade_in_runvblank(void);
void palette_fade_in_loop(void);
void palette_move_from_black(void);
void color_move_from_black(void);
void palette_fade_from_white_runvblank(void);
void palette_fade_from_white_loop(void);
void level_palette_cycle_ghz(bool title_screen);
void level_palette_cycle_lz(void);
void level_palette_cycle_mz(void);
void level_palette_cycle_slz(void);
void level_palette_cycle_syz(void);
void level_palette_cycle_sbz(void);
void palette_move_from_white(void);
void color_move_from_white(void);
void palette_fade_out_runvblank(void);
void palette_fade_out_loop(void);
void palette_move_toward_black(void);
void color_move_toward_black(void);
void palette_fade_out(void);
void load_palette_fading(void);
void palette_fade_in(bool full_palette);
void palette_fade_from_white(void);
void load_palette(void);
void palette_fade_to_white(void);