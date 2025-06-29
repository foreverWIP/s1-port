#include "system.h"
#include "opcodes.h"
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
u16 (*speedshoes__get_game_width_cb)(void *emu);

void *speedshoes__emu;
bool speedshoes__dirtymem = false;
void (*speedshoes__print_cb)(char *buf);

u8 read_joy1(void) {
  CHECK_EMU() 0;
  return speedshoes__read_8_cb(speedshoes__emu, 0xa10003);
}
u8 read_joy2(void) {
  CHECK_EMU() 0;
  return speedshoes__read_8_cb(speedshoes__emu, 0xa10005);
}
void write_joy1(u8 value) {
  CHECK_EMU();
  speedshoes__write_8_cb(speedshoes__emu, 0xa10003, value);
}
void write_joy2(u8 value) {
  CHECK_EMU();
  speedshoes__write_8_cb(speedshoes__emu, 0xa10005, value);
}
void set_vdp_register(u8 reg, u8 value) {
  write_vdp_control_16((((u16)reg) << 8) | value);
}
u16 read_vdp_control_16(void) {
  CHECK_EMU() 0;
  return speedshoes__read_16_cb(speedshoes__emu, VDP_CONTROL_PORT);
}
void speedshoes__play_sound(void) {
  CHECK_EMU();
  speedshoes__play_sound_cb(speedshoes__emu, D0);
}
void speedshoes__play_sound_special(void) {
  CHECK_EMU();
  speedshoes__play_sound_special_cb(speedshoes__emu, D0);
}

u16 speedshoes__get_game_width(void) {
  CHECK_EMU() 320;
  return speedshoes__get_game_width_cb(speedshoes__emu);
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
  speedshoes__get_game_width_cb = ffiinfo->get_game_width;
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

void sonic1__print(const char *msg, ...) {
  va_list args;

  va_start(args, msg);
  vsnprintf(stringbuf, sizeof(stringbuf), msg, args);
  sprintf(stringbuf, "%.*s\n", (int)sizeof(stringbuf) - 1, stringbuf);
  va_end(args);
  printf("%s", stringbuf);
  fflush(stdout);
  if (speedshoes__print_cb) {
    speedshoes__print_cb(stringbuf);
  }
}

u32 sonic1__next_power_of_2(u32 value) {
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

void fill_vram(u8 value, u16 start, u16 end) {
  A5 = VDP_CONTROL_PORT;
  set_vdp_register(0x8f, 0x01);
  u16 length = end - start - 1;
  set_vdp_register(0x94, length >> 8);
  set_vdp_register(0x93, length & 0xff);
  set_vdp_register(0x97, 0x80);
  write_vdp_control_32(0x40000080 + (((u32)start & 0x3FFF) << 16) +
                       (((u32)start & 0xC000) >> 14));
  write_vdp_data_16(0x0000);
  set_vdp_register(0x8f, 0x02);
  SETWORD(D1, 0);
}

void write_vram_dma(u32 source, u32 source_end, u16 destination) {
  u32 length = source_end - source;
  A5 = VDP_CONTROL_PORT;
  set_vdp_register(0x93, (length >> 1) & 0xFF);
  set_vdp_register(0x94, ((length >> 1) & 0xFF00) >> 8);
  set_vdp_register(0x95, (source >> 1) & 0xFF);
  set_vdp_register(0x96, ((source >> 1) & 0xFF00) >> 8);
  set_vdp_register(0x97, ((source >> 1) & 0x7F0000) >> 16);
  write_vdp_control_16(0x4000 + (destination & 0x3FFF));
  move_tomem_16(0x80 + ((destination & 0xC000) >> 14), v_vdp_buffer2);
  write_vdp_control_16(read_16(v_vdp_buffer2));
}

void write_cram_dma(u32 source, u32 source_end, u16 destination) {
  u32 length = source_end - source;
  A5 = VDP_CONTROL_PORT;
  set_vdp_register(0x93, (length >> 1) & 0xFF);
  set_vdp_register(0x94, ((length >> 1) & 0xFF00) >> 8);
  set_vdp_register(0x95, (source >> 1) & 0xFF);
  set_vdp_register(0x96, ((source >> 1) & 0xFF00) >> 8);
  set_vdp_register(0x97, (((source >> 1) & 0xFF0000) >> 16) & 0x7F);
  write_vdp_control_16(0xc000 + (destination & 0x3FFF));
  move_tomem_16(0x80 + ((destination & 0xC000) >> 14), v_vdp_buffer2);
  write_vdp_control_16(read_16(0xFFFFF640));
}