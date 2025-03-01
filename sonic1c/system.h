#pragma once

#include <math.h>
#include <setjmp.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

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

extern u32 speedshoes__read_8(u32 loc);
extern u32 speedshoes__read_16(u32 loc);
extern u32 speedshoes__read_32(u32 loc);
extern void speedshoes__write_8(u32 loc, u8 value);
extern void speedshoes__write_16(u32 loc, u16 value);
extern void speedshoes__write_32(u32 loc, u32 value);

extern bool speedshoes__synchronize(u32 pc);
extern void speedshoes__callemu(u32 loc);

#define read_8(loc) speedshoes__read_8(loc)
#define read_16(loc) speedshoes__read_16(loc)
#define read_32(loc) speedshoes__read_32(loc)
#define write_8(loc, value) speedshoes__write_8(loc, value)
#define write_16(loc, value) speedshoes__write_16(loc, value)
#define write_32(loc, value) speedshoes__write_32(loc, value)

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
extern jmp_buf speedshoes__desync_jumpbuf;

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

#define GETWORD(value) ((value) & 0xffff)
#define GETBYTE(value) ((value) & 0xff)
#define SETWORD(reg, value) reg = ((reg & 0xffff0000) | ((value) & 0x0000ffff))
#define SETBYTE(reg, value) reg = ((reg & 0xffffff00) | ((value) & 0x000000ff))

#define SWAPWORDS(dst)                                                         \
  {                                                                            \
    dst = ((dst << 16) | (dst >> 16));                                         \
  }

u8 read_joy1(void);
u8 read_joy2(void);
void write_joy1(u8 value);
void write_joy2(u8 value);

#define VDP_DATA_PORT 0xC00000
#define VDP_CONTROL_PORT 0xC00004

void write_vdp_data_16(u16 value);
void write_vdp_control_16(u16 value);
u16 read_vdp_control_16(void);
void write_vdp_data_32(u32 value);
void write_vdp_control_32(u32 value);

#define VRAM_PTR_TO_VDP_COMMAND(loc)                                           \
  (0x40000000 + (((loc) & 0x3FFF) << 16) + (((loc) & 0xC000) >> 14))
#define set_vram_ptr(loc)                                                      \
  {                                                                            \
    loc = VRAM_PTR_TO_VDP_COMMAND(loc);                                        \
    write_vdp_control_32(loc);                                                 \
  }

#define PLANE_SIZE_64X32 0x1000

extern void print(const char *msg, ...);

#define PRINTVAL(val) print(#val " = 0x%X", val)
#define PRINTREG(reg) print(#reg " = 0x%X", reg)

#define DEF_ROMLOC(loc)                                                        \
  rom_##loc : if (CHECK_STUFF && (TEST_LEVEL & TEST_PER_INSTRUCTION)) {        \
    print("synching to romloc " #loc);                                         \
    if (!speedshoes__synchronize(0x##loc)) {                                   \
      longjmp(speedshoes__desync_jumpbuf, 1);                                  \
    }                                                                          \
  }                                                                            \
  rom_##loc##_colon

#include "game.h"

u32 next_power_of_2(u32 value);