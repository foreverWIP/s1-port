#pragma once

#include <math.h>
#include <setjmp.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define EXPORT

typedef uint8_t u8;
typedef int8_t s8;
typedef uint16_t u16;
typedef int16_t s16;
typedef uint32_t u32;
typedef int32_t s32;
typedef uint64_t u64;
typedef int64_t s64;

#ifndef CHECK_STUFF
#define CHECK_STUFF 0
#endif

#define TEST_NONE (0 << 0)
#define TEST_REGS (1 << 0)
#define TEST_SR (1 << 1)
#define TEST_MEM (1 << 2)
#define TEST_PER_INSTRUCTION (1 << 3)

#define TEST_LEVEL (TEST_REGS | TEST_MEM | TEST_PER_INSTRUCTION)

#define ROMFUNC(funcname) EXPORT void funcname(void)

extern u32 smps__read_8(u32 loc);
extern u32 smps__read_16(u32 loc);
extern u32 smps__read_32(u32 loc);
extern void smps__write_8(u32 loc, u8 value);
extern void smps__write_16(u32 loc, u16 value);
extern void smps__write_32(u32 loc, u32 value);

#define read_8(loc) smps__read_8(loc)
#define read_16(loc) smps__read_16(loc)
#define read_32(loc) smps__read_32(loc)
#define write_8(loc, value) smps__write_8(loc, value)
#define write_16(loc, value) smps__write_16(loc, value)
#define write_32(loc, value) smps__write_32(loc, value)

extern EXPORT u32 smps__d0;
extern EXPORT u32 smps__d1;
extern EXPORT u32 smps__d2;
extern EXPORT u32 smps__d3;
extern EXPORT u32 smps__d4;
extern EXPORT u32 smps__d5;
extern EXPORT u32 smps__d6;
extern EXPORT u32 smps__d7;
extern EXPORT u32 smps__a0;
extern EXPORT u32 smps__a1;
extern EXPORT u32 smps__a2;
extern EXPORT u32 smps__a3;
extern EXPORT u32 smps__a4;
extern EXPORT u32 smps__a5;
extern EXPORT u32 smps__a6;
extern EXPORT u32 smps__a7;
extern EXPORT u32 smps__sr;
extern EXPORT u32 smps__readbuf;
extern jmp_buf smps__desync_jumpbuf;

#define D0 smps__d0
#define D1 smps__d1
#define D2 smps__d2
#define D3 smps__d3
#define D4 smps__d4
#define D5 smps__d5
#define D6 smps__d6
#define D7 smps__d7
#define A0 smps__a0
#define A1 smps__a1
#define A2 smps__a2
#define A3 smps__a3
#define A4 smps__a4
#define A5 smps__a5
#define A6 smps__a6
#define A7 smps__a7
#define SR smps__sr

#define GETWORD(value) ((value) & 0xffff)
#define GETBYTE(value) ((value) & 0xff)
#define SETWORD(reg, value) reg = ((reg & 0xffff0000) | ((value) & 0x0000ffff))
#define SETBYTE(reg, value) reg = ((reg & 0xffffff00) | ((value) & 0x000000ff))

#define SWAPWORDS(dst)                                                         \
  {                                                                            \
    dst = ((dst << 16) | (dst >> 16));                                         \
  }

extern void print(const char *msg, ...);

#define PRINTVAL(val) print(#val " = 0x%X", val)
#define PRINTREG(reg) print(#reg " = 0x%X", reg)

#define DEF_ROMLOC(loc)                                                        \
  rom_##loc : if (CHECK_STUFF && (TEST_LEVEL & TEST_PER_INSTRUCTION)) {        \
    print("synching to romloc " #loc);                                         \
  }                                                                            \
  rom_##loc##_colon

u32 next_power_of_2(u32 value);

extern void write_fm_i(u8 a, u8 v);
extern void write_fm_ii(u8 a, u8 v);
extern void write_psg(u8 data);
extern void set_dac_sample(u8 sample);