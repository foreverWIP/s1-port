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
#include "special.h"
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

  GM_MASK = 0b11100,

  GM_TITLECARD_FLAG_BIT = 7,
  GM_TITLECARD_FLAG = (1 << GM_TITLECARD_FLAG_BIT),
};

#define GAME_WIDTH 320
// #define GAME_WIDTH 432

extern void (*game_state)(void);
extern bool exit_mainloop;

extern void (*game_state_palette)(void);
extern void (*game_state_pause)(void);

void rom_388_nosega(void);
