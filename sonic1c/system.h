#pragma once

#ifndef DEBUG_EMU
#define DEBUG_EMU 0
#endif

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

#define ROMFUNC(funcname) EXPORT void funcname(void)

typedef uint8_t u8;
typedef int8_t s8;
typedef uint16_t u16;
typedef int16_t s16;
typedef uint32_t u32;
typedef int32_t s32;
typedef uint64_t u64;
typedef int64_t s64;

extern u32 speedshoes__read_8(u32 loc);
extern u32 speedshoes__read_16(u32 loc);
extern u32 speedshoes__read_32(u32 loc);
extern void speedshoes__write_8(u32 loc, u8 value);
extern void speedshoes__write_16(u32 loc, u16 value);
extern void speedshoes__write_32(u32 loc, u32 value);

extern void speedshoes__synchronize(u32 pc);
extern void speedshoes__callemu(u32 loc);

#if DEBUG_EMU
#define read_8(loc)                                                            \
  (speedshoes__readbuf = speedshoes__read_8(loc),                              \
   print("read_8(0x%06x) = 0x%02x", loc, speedshoes__readbuf),                 \
   speedshoes__readbuf)
#define read_16(loc)                                                           \
  (speedshoes__readbuf = speedshoes__read_16(loc),                             \
   print("read_16(0x%06x) = 0x%04x", loc, speedshoes__readbuf),                \
   speedshoes__readbuf)
#define read_32(loc)                                                           \
  (speedshoes__readbuf = speedshoes__read_32(loc),                             \
   print("read_32(0x%06x) = 0x%08x", loc, speedshoes__readbuf),                \
   speedshoes__readbuf)
#define write_8(loc, value)                                                    \
  printf("write8(0x%06x, 0x%02x)\n", loc, value);                              \
  speedshoes__write_8(loc, value)
#define write_16(loc, value)                                                   \
  printf("write16(0x%06x, 0x%04x)\n", loc, value);                             \
  speedshoes__write_16(loc, value)
#define write_32(loc, value)                                                   \
  printf("write32(0x%06x, 0x%08x)\n", loc, value);                             \
  speedshoes__write_32(loc, value)
#else
#define read_8 speedshoes__read_8
#define read_16 speedshoes__read_16
#define read_32 speedshoes__read_32
#define write_8 speedshoes__write_8
#define write_16 speedshoes__write_16
#define write_32 speedshoes__write_32
#endif

#include "romlocs.h"
#include "object.h"

extern EXPORT u32 speedshoes__d0;
extern EXPORT u32 speedshoes__d1;
extern EXPORT u32 speedshoes__d2;
extern EXPORT u32 speedshoes__d3;
extern EXPORT u32 speedshoes__d4;
extern EXPORT u32 speedshoes__d5;
extern EXPORT u32 speedshoes__d6;
extern EXPORT u32 speedshoes__d7;
extern EXPORT u32 speedshoes__a0;
extern EXPORT u32 speedshoes__a1;
extern EXPORT u32 speedshoes__a2;
extern EXPORT u32 speedshoes__a3;
extern EXPORT u32 speedshoes__a4;
extern EXPORT u32 speedshoes__a5;
extern EXPORT u32 speedshoes__a6;
extern EXPORT u32 speedshoes__a7;
extern EXPORT u32 speedshoes__sr;
extern EXPORT u32 speedshoes__readbuf;
extern EXPORT bool speedshoes__wrotemem;
extern EXPORT bool speedshoes__desynched;
extern bool speedshoes__vblank_end;

#define D0 speedshoes__d0
#define D1 speedshoes__d1
#define D2 speedshoes__d2
#define D3 speedshoes__d3
#define D4 speedshoes__d4
#define D5 speedshoes__d5
#define D6 speedshoes__d6
#define D7 speedshoes__d7
#define A0 speedshoes__a0
#define A1 speedshoes__a1
#define A2 speedshoes__a2
#define A3 speedshoes__a3
#define A4 speedshoes__a4
#define A5 speedshoes__a5
#define A6 speedshoes__a6
#define A7 speedshoes__a7
#define SR speedshoes__sr

#define SETWORD(reg, value) reg = ((reg & 0xffff0000) | ((value) & 0x0000ffff))
#define SETBYTE(reg, value) reg = ((reg & 0xffffff00) | ((value) & 0x000000ff))

extern void print(const char *msg, ...);

#define PRINTVAL(val) print(#val " = 0x%X", val)
#define PRINTREG(reg) print(#reg " = 0x%X", reg)

#if (defined CHECK_STUFF)
#define DEF_ROMLOC(loc)                                                        \
  /*if (speedshoes__vblank_end) {                                                \
    print("hit end of vblank!");                                               \
    return;                                                                    \
  }*/                                                                            \
  rom_##loc : if (speedshoes__desynched) { return; }                           \
  /*print("script pc before checking stuff: %X", 0x##loc);*/                   \
  if (CHECK_STUFF(0x##loc)) {                                                  \
    speedshoes__synchronize(0x##loc);                                          \
    if (speedshoes__desynched) {                                               \
      return;                                                                  \
    }                                                                          \
  }                                                                            \
  rom_##loc##_colon
#else
#define DEF_ROMLOC(loc) rom_##loc
#endif