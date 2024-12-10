#include "system.h"
#include <stdarg.h>
#include <stdio.h>

typedef struct {
  void *emu;
  u8 (*read_8_cb)(void *emu, u32 loc);
  u16 (*read_16_cb)(void *emu, u32 loc);
  u32 (*read_32_cb)(void *emu, u32 loc);
  void (*write_8_cb)(void *emu, u32 loc, u8 value);
  void (*write_16_cb)(void *emu, u32 loc, u16 value);
  void (*write_32_cb)(void *emu, u32 loc, u32 value);
  bool (*synchronize)(u32 pc, bool checkmem);
} FFIInfo;

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
EXPORT bool speedshoes__wrotemem;
EXPORT bool speedshoes__desynched;
bool speedshoes__vblank_end;

u8 (*speedshoes__read_8_cb)(void *emu, u32 loc);
u16 (*speedshoes__read_16_cb)(void *emu, u32 loc);
u32 (*speedshoes__read_32_cb)(void *emu, u32 loc);
void (*speedshoes__write_8_cb)(void *emu, u32 loc, u8 value);
void (*speedshoes__write_16_cb)(void *emu, u32 loc, u16 value);
void (*speedshoes__write_32_cb)(void *emu, u32 loc, u32 value);
bool (*speedshoes__synchronize_cb)(u32 pc, bool checkmem);

void *speedshoes__emu;

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
  speedshoes__wrotemem = 1;
  speedshoes__write_8_cb(speedshoes__emu, loc, value);
}
void speedshoes__write_16(u32 loc, u16 value) {
  CHECK_EMU();
  speedshoes__wrotemem = 1;
  speedshoes__write_16_cb(speedshoes__emu, loc, value);
}
void speedshoes__write_32(u32 loc, u32 value) {
  CHECK_EMU();
  speedshoes__wrotemem = 1;
  speedshoes__write_32_cb(speedshoes__emu, loc, value);
}

EXPORT void speedshoes__bind_functions(FFIInfo *ffiinfo) {
  print("Binding functions...");
  speedshoes__vblank_end = false;
  speedshoes__wrotemem = false;
  speedshoes__emu = ffiinfo->emu;
  speedshoes__read_8_cb = ffiinfo->read_8_cb;
  speedshoes__read_16_cb = ffiinfo->read_16_cb;
  speedshoes__read_32_cb = ffiinfo->read_32_cb;
  speedshoes__write_8_cb = ffiinfo->write_8_cb;
  speedshoes__write_16_cb = ffiinfo->write_16_cb;
  speedshoes__write_32_cb = ffiinfo->write_32_cb;
  speedshoes__synchronize_cb = ffiinfo->synchronize;
}

void speedshoes__synchronize(u32 pc) {
  CHECK_EMU();
  if (speedshoes__synchronize_cb) {
    speedshoes__desynched =
        !speedshoes__synchronize_cb(pc, speedshoes__wrotemem);
    if (speedshoes__desynched) {
      return;
    }
    speedshoes__wrotemem = 0;
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
}

EXPORT void speedshoes__runframe(void) {
	
}