#pragma once

#include "system.h"

extern void (*game_state)(void);
extern bool exit_mainloop;

extern void (*game_state_palette)(void);
extern void (*game_state_pause)(void);

void rom_388_nosega(void);

#define SET_GM_SEGA() move_tomem_8(0x0, 0xFFFFF600);
#define SET_GM_TITLE() move_tomem_8(0x4, 0xFFFFF600);
#define SET_GM_DEMO() move_tomem_8(0x8, 0xFFFFF600);
#define SET_GM_LEVEL() move_tomem_8(0xC, 0xFFFFF600);
#define SET_GM_SPECIAL() move_tomem_8(0x10, 0xFFFFF600);
#define SET_GM_CONTINUE() move_tomem_8(0x14, 0xFFFFF600);
#define SET_GM_ENDING() move_tomem_8(0x18, 0xFFFFF600);
#define SET_GM_CREDITS() move_tomem_8(0x1C, 0xFFFFF600);