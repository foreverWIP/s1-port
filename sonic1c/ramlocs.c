#include "system.h"
#include "ramlocs.h"

u8 v_gamemode;

#define write_ram(loc, value, bits) write_##bits(0xff0000|loc, value)

void serialize_ram(void) {
  write_ram(0xf600, v_gamemode, 8);
}