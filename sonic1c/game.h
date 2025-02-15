#pragma once

#include "anim.h"
#include "continue.h"
#include "enigma.h"
#include "graphics.h"
#include "input.h"
#include "level.h"
#include "nemesis.h"
#include "object.h"
#include "palette.h"
#include "plc.h"
#include "ramlocs.h"
#include "romlocs.h"
#include "sega.h"
#include "sound.h"
#include "system.h"
#include "util.h"
#include "vblank.h"

enum {
  GM_SEGA = 4 * 0,
  GM_TITLE = 4 * 1,
  GM_DEMO = 4 * 2,
  GM_LEVEL = 4 * 3,
  GM_SPECIAL = 4 * 4,
  GM_CONTINUE = 4 * 5,
  GM_ENDING = 4 * 6,
  GM_CREDITS = 4 * 7,
};

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