#include "system.h"
#include <stdarg.h>
#include <stdio.h>

u32 smps__d0;
u32 smps__d1;
u32 smps__d2;
u32 smps__d3;
u32 smps__d4;
u32 smps__d5;
u32 smps__d6;
u32 smps__d7;
u32 smps__a0;
u32 smps__a1;
u32 smps__a2;
u32 smps__a3;
u32 smps__a4;
u32 smps__a5;
u32 smps__a6;
u32 smps__a7;
u32 smps__sr;
u32 smps__readbuf;

u8 *smps_rom_ptr;
u8 *smps_ram_ptr;

u32 smps__read_8(u32 loc) {
  loc &= 0xffffff;
  if (loc >= 0xfff000) {
    loc -= 0xfff000;
	// print("read ram %x", loc);
    return smps_ram_ptr[loc];
  }
  if (loc < 0x80000) {
	// print("read rom %x", loc);
	if (loc < 0x71990) {
		print("read before sound data at %x", loc);
	}
    return smps_rom_ptr[loc];
  }
  return 0;
}
u32 smps__read_16(u32 loc) {
  u16 byte0 = smps__read_8(loc);
  u16 byte1 = smps__read_8(loc + 1);
  return (byte0 << 8) | byte1;
}
u32 smps__read_32(u32 loc) {
  u32 byte0 = smps__read_8(loc);
  u32 byte1 = smps__read_8(loc + 1);
  u32 byte2 = smps__read_8(loc + 2);
  u32 byte3 = smps__read_8(loc + 3);
  return (byte0 << 24) | (byte1 << 16) | (byte2 << 8) | byte3;
}
void smps__write_8(u32 loc, u8 value) {
  loc &= 0xffffff;
  if (loc >= 0xff0000) {
    loc -= 0xfff000;
	if (value != 0) {
	// print("write %x -> %x", value, loc);
	}
    smps_ram_ptr[loc] = value;
	return;
  }
  if (loc == 0xa01fff) {
	// print("dac sample = %d", value);
	smps_ram_ptr[0xfff] = value;
  }
  if (loc >= 0xa00000) {
	return;
  }
  print("unhandled write to %x", loc);
}
void smps__write_16(u32 loc, u16 value) {
  smps__write_8(loc, value >> 8);
  smps__write_8(loc + 1, value);
}
void smps__write_32(u32 loc, u32 value) {
  smps__write_8(loc, value >> 24);
  smps__write_8(loc + 1, value >> 16);
  smps__write_8(loc + 2, value >> 8);
  smps__write_8(loc + 3, value);
}

static char stringbuf[0x400];

void print(const char *msg, ...) {
  va_list args;

  va_start(args, msg);
  vsnprintf(stringbuf, sizeof(stringbuf), msg, args);
  sprintf(stringbuf, "%.*s\n", (s32)sizeof(stringbuf) - 1, stringbuf);
  va_end(args);
  printf("%s", stringbuf);
  fflush(stdout);
}

u32 next_power_of_2(u32 value) {
  u32 v = value; // compute the next highest power of 2 of 32-bit v

  v--;
  v |= v >> 1;
  v |= v >> 2;
  v |= v >> 4;
  v |= v >> 8;
  v |= v >> 16;
  v++;

  return v;
}