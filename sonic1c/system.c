#include "system.h"
#include "ramlocs.h"
#include <stdarg.h>
#include <stdio.h>

EXPORT u32 speedshoes__d0;
EXPORT u32 speedshoes__d1;
EXPORT u32 speedshoes__d2;
EXPORT u32 speedshoes__d3;
EXPORT u32 speedshoes__d4;
EXPORT u32 speedshoes__d5;
EXPORT u32 speedshoes__d6;
EXPORT u32 speedshoes__d7;
EXPORT u32 speedshoes__a0;
EXPORT u32 speedshoes__a1;
EXPORT u32 speedshoes__a2;
EXPORT u32 speedshoes__a3;
EXPORT u32 speedshoes__a4;
EXPORT u32 speedshoes__a5;
EXPORT u32 speedshoes__a6;
EXPORT u32 speedshoes__a7;
EXPORT u32 speedshoes__sr;
EXPORT u32 speedshoes__readbuf;

u8 (*speedshoes__read_8_cb)(void *emu, u32 loc);
u16 (*speedshoes__read_16_cb)(void *emu, u32 loc);
u32 (*speedshoes__read_32_cb)(void *emu, u32 loc);
void (*speedshoes__write_8_cb)(void *emu, u32 loc, u8 value);
void (*speedshoes__write_16_cb)(void *emu, u32 loc, u16 value);
void (*speedshoes__write_32_cb)(void *emu, u32 loc, u32 value);
bool (*speedshoes__synchronize_cb)(u32 pc);
void (*speedshoes__play_sound_cb)(void *emu, u8 sound);
void (*speedshoes__play_sound_special_cb)(void *emu, u8 sound);

void *speedshoes__emu;
bool speedshoes__dirtymem = false;

#define CHECK_EMU()                                                            \
  if (!speedshoes__emu)                                                        \
  return

u32 speedshoes__read_8(u32 loc) {
  CHECK_EMU() 0;
  return speedshoes__read_8_cb(speedshoes__emu, loc);
}
u32 speedshoes__read_16(u32 loc) {
  CHECK_EMU() 0;
  return speedshoes__read_16_cb(speedshoes__emu, loc);
}
u32 speedshoes__read_32(u32 loc) {
  CHECK_EMU() 0;
  return speedshoes__read_32_cb(speedshoes__emu, loc);
}
void speedshoes__write_8(u32 loc, u8 value) {
  CHECK_EMU();
  speedshoes__dirtymem |= true;
  speedshoes__write_8_cb(speedshoes__emu, loc, value);
}
void speedshoes__write_16(u32 loc, u16 value) {
  CHECK_EMU();
  speedshoes__dirtymem |= true;
  speedshoes__write_16_cb(speedshoes__emu, loc, value);
}
void speedshoes__write_32(u32 loc, u32 value) {
  CHECK_EMU();
  speedshoes__dirtymem |= true;
  speedshoes__write_32_cb(speedshoes__emu, loc, value);
}
u8 read_joy1(void) {
  CHECK_EMU() 0;
  speedshoes__read_8_cb(speedshoes__emu, 0xa10003);
}
u8 read_joy2(void) {
  CHECK_EMU() 0;
  speedshoes__read_8_cb(speedshoes__emu, 0xa10005);
}
void write_joy1(u8 value) {
  CHECK_EMU();
  speedshoes__write_8_cb(speedshoes__emu, 0xa10003, value);
}
void write_joy2(u8 value) {
  CHECK_EMU();
  speedshoes__write_8_cb(speedshoes__emu, 0xa10005, value);
}
void write_vdp_data_16(u16 value) {
  CHECK_EMU();
  speedshoes__write_16_cb(speedshoes__emu, VDP_DATA_PORT, value);
}
void write_vdp_control_16(u16 value) {
  CHECK_EMU();
  speedshoes__write_16_cb(speedshoes__emu, VDP_CONTROL_PORT, value);
}
u16 read_vdp_control_16(void) {
  CHECK_EMU() 0;
  speedshoes__read_16_cb(speedshoes__emu, VDP_CONTROL_PORT);
}
void write_vdp_data_32(u32 value) {
  CHECK_EMU();
  speedshoes__write_32_cb(speedshoes__emu, VDP_DATA_PORT, value);
}
void write_vdp_control_32(u32 value) {
  CHECK_EMU();
  speedshoes__write_32_cb(speedshoes__emu, VDP_CONTROL_PORT, value);
}
void speedshoes__play_sound(void) {
	CHECK_EMU();
	speedshoes__play_sound_cb(speedshoes__emu, D0);
}
void speedshoes__play_sound_special(void) {
	CHECK_EMU();
	speedshoes__play_sound_special_cb(speedshoes__emu, D0);
}

EXPORT void speedshoes__bind_functions(FFIInfo *ffiinfo) {
  print("Binding functions...");
  speedshoes__emu = ffiinfo->emu;
  speedshoes__read_8_cb = ffiinfo->read_8_cb;
  speedshoes__read_16_cb = ffiinfo->read_16_cb;
  speedshoes__read_32_cb = ffiinfo->read_32_cb;
  speedshoes__write_8_cb = ffiinfo->write_8_cb;
  speedshoes__write_16_cb = ffiinfo->write_16_cb;
  speedshoes__write_32_cb = ffiinfo->write_32_cb;
  speedshoes__synchronize_cb = ffiinfo->synchronize;
  speedshoes__play_sound_cb = ffiinfo->play_sound;
  speedshoes__play_sound_special_cb = ffiinfo->play_sound_special;
}

bool speedshoes__synchronize(u32 pc) {
  //   CHECK_EMU();
  serialize_ram();
  if (speedshoes__synchronize_cb) {
    return speedshoes__synchronize_cb(pc);
  } else {
	return true;
  }
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

EXPORT void speedshoes__runframe(void) {}

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