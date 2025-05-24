#pragma once
#include "system.h"
#define CCR_C (SR & 0x1)
#define CCR_V (SR & 0x2)
#define CCR_Z (SR & 0x4)
#define CCR_N (SR & 0x8)
#define CCR_X (SR & 0x10)
#define CCR_HI ((!CCR_C) & (!CCR_Z))
#define CCR_LS (CCR_C | CCR_Z)
#define CCR_CC (!CCR_C)
#define CCR_CS CCR_C
#define CCR_NE (!CCR_Z)
#define CCR_EQ CCR_Z
#define CCR_VC (!CCR_V)
#define CCR_VS CCR_V
#define CCR_PL (!CCR_N)
#define CCR_MI CCR_N
#define CCR_GE ((CCR_MI ^ CCR_VS) == 0)
#define CCR_LT (!CCR_GE)
#define CCR_GT (CCR_GE && CCR_NE)
#define CCR_LE (CCR_LT || CCR_EQ)
#if __TINYC__
extern void add_tomem_16(u32 src, u32 dst);
extern void add_tomem_32(u32 src, u32 dst);
extern void add_tomem_8(u32 src, u32 dst);
extern void add_toreg_16(u32 src, u32 *dst);
extern void add_toreg_32(u32 src, u32 *dst);
extern void add_toreg_8(u32 src, u32 *dst);
extern void and_tomem_16(u32 src, u32 dst);
extern void and_tomem_32(u32 src, u32 dst);
extern void and_tomem_8(u32 src, u32 dst);
extern void and_toreg_16(u32 src, u32 *dst);
extern void and_toreg_32(u32 src, u32 *dst);
extern void and_toreg_8(u32 src, u32 *dst);
extern void asl_mem_16(u32 dst);
extern void asl_toreg_16(u32 src, u32 *dst);
extern void asl_toreg_32(u32 src, u32 *dst);
extern void asr_mem_16(u32 dst);
extern void asr_toreg_16(u32 src, u32 *dst);
extern void asr_toreg_32(u32 src, u32 *dst);
extern void asr_toreg_8(u32 src, u32 *dst);
extern void bchg_tomem_8(u32 src, u32 dst);
extern void bchg_toreg_32(u32 src, u32 *dst);
extern void bclr_tomem_8(u32 src, u32 dst);
extern void bclr_toreg_32(u32 src, u32 *dst);
extern void bset_tomem_8(u32 src, u32 dst);
extern void bset_toreg_32(u32 src, u32 *dst);
extern void btst_tomem_8(u32 src, u32 dst);
extern void btst_toreg_32(u32 src, u32 *dst);
extern void clr_mem_16(u32 dst);
extern void clr_mem_32(u32 dst);
extern void clr_mem_8(u32 dst);
extern void clr_reg_16(u32 *dst);
extern void clr_reg_8(u32 *dst);
extern void cmp_tomem_16(u32 src, u32 dst);
extern void cmp_tomem_32(u32 src, u32 dst);
extern void cmp_tomem_8(u32 src, u32 dst);
extern void cmp_toreg_16(u32 src, u32 *dst);
extern void cmp_toreg_32(u32 src, u32 *dst);
extern void cmp_toreg_8(u32 src, u32 *dst);
extern void dec_reg_16(u32 *dst);
extern void divs_toreg_16(u32 src, u32 *dst);
extern void divu_toreg_16(u32 src, u32 *dst);
extern void eor_tomem_8(u32 src, u32 dst);
extern void eor_toreg_16(u32 src, u32 *dst);
extern void eor_toreg_32(u32 src, u32 *dst);
extern void eor_toreg_8(u32 src, u32 *dst);
extern void exg_toreg_32(u32 *src, u32 *dst);
extern void ext_reg_16(u32 *dst);
extern void ext_reg_32(u32 *dst);
extern void lsl_toreg_16(u32 src, u32 *dst);
extern void lsl_toreg_32(u32 src, u32 *dst);
extern void lsl_toreg_8(u32 src, u32 *dst);
extern void lsr_toreg_16(u32 src, u32 *dst);
extern void lsr_toreg_32(u32 src, u32 *dst);
extern void lsr_toreg_8(u32 src, u32 *dst);
extern void move_sr_toreg_16(u32 sr, u32 *dst);
extern void move_tomem_16(u32 src, u32 dst);
extern void move_tomem_32(u32 src, u32 dst);
extern void move_tomem_8(u32 src, u32 dst);
extern void move_toreg_16(u32 src, u32 *dst);
extern void move_toreg_32(u32 src, u32 *dst);
extern void move_toreg_8(u32 src, u32 *dst);
extern void move_toccr_8(u32 src, u32 *sr);
extern void move_tosr_16(u32 src, u32 *sr);
extern void muls_toreg_16(u32 src, u32 *dst);
extern void mulu_toreg_16(u32 src, u32 *dst);
extern void neg_mem_16(u32 dst);
extern void neg_mem_8(u32 dst);
extern void neg_reg_16(u32 *dst);
extern void neg_reg_8(u32 *dst);
extern void not_mem_8(u32 dst);
extern void not_reg_16(u32 *dst);
extern void not_reg_8(u32 *dst);
extern void or_tomem_16(u32 src, u32 dst);
extern void or_tomem_32(u32 src, u32 dst);
extern void or_tomem_8(u32 src, u32 dst);
extern void or_toreg_16(u32 src, u32 *dst);
extern void or_toreg_32(u32 src, u32 *dst);
extern void or_toreg_8(u32 src, u32 *dst);
extern void rol_toreg_16(u32 src, u32 *dst);
extern void rol_toreg_32(u32 src, u32 *dst);
extern void rol_toreg_8(u32 src, u32 *dst);
extern void ror_toreg_16(u32 src, u32 *dst);
extern void ror_toreg_32(u32 src, u32 *dst);
extern void ror_toreg_8(u32 src, u32 *dst);
extern void roxl_toreg_16(u32 src, u32 *dst);
extern void sub_tomem_16(u32 src, u32 dst);
extern void sub_tomem_32(u32 src, u32 dst);
extern void sub_tomem_8(u32 src, u32 dst);
extern void sub_toreg_16(u32 src, u32 *dst);
extern void sub_toreg_32(u32 src, u32 *dst);
extern void sub_toreg_8(u32 src, u32 *dst);
// extern void swap_reg_16(u32 *dst);
extern void tst_mem_16(u32 dst);
extern void tst_mem_32(u32 dst);
extern void tst_mem_8(u32 dst);
extern void tst_reg_16(u32 *dst);
extern void tst_reg_32(u32 *dst);
extern void tst_reg_8(u32 *dst);
#else
extern const u8 m68ki_shift_8_table[65];
extern const u16 m68ki_shift_16_table[65];
extern const u32 m68ki_shift_32_table[65];
extern u32 SIZE_MASKS[];
extern u32 SIZE_SIGNS[];
#ifndef OPCODES_H_IMPLEMENTATION
#define OPCODES_H_IMPLEMENTATION
#endif
#endif

#ifdef OPCODES_H_IMPLEMENTATION

// ~96 unique instructions
// ~31 unique instruction mnemonics

#define NFLAG_SET 0x80
#define NFLAG_CLEAR 0
#define CFLAG_SET 0x100
#define CFLAG_CLEAR 0
#define XFLAG_SET 0x100
#define XFLAG_CLEAR 0
#define VFLAG_SET 0x80

// XNZVC
#define GET_FLAG_X CCR_X
#define GET_FLAG_N CCR_N
#define GET_FLAG_Z CCR_Z
#define GET_FLAG_V CCR_V
#define GET_FLAG_C CCR_C
#define SET_FLAG_X(value) SR = ((SR & 0xffef) | (((value) != 0) << 4))
#define SET_FLAG_N(value) SR = ((SR & 0xfff7) | (((value) != 0) << 3))
#define SET_FLAG_Z(value) SR = ((SR & 0xfffb) | (((value) != 0) << 2))
#define SET_FLAG_V(value) SR = ((SR & 0xfffd) | (((value) != 0) << 1))
#define SET_FLAG_C(value) SR = ((SR & 0xfffe) | (((value) != 0) << 0))

#define MASKED(value, bits) ((value) & SIZE_MASKS[bits >> 4])
#define SIGNMASK(bits) SIZE_SIGNS[(bits) >> 4]

#define BINOP_TOREG_8(funcname)                                                \
  SETBYTE(*dst, funcname(src, *dst, 8, is_data_reg(dst)))
#define BINOP_TOREG_16(funcname)                                               \
  SETWORD(*dst, funcname(src, *dst, 16, is_data_reg(dst)))
#define BINOP_TOREG_32(funcname)                                               \
  *dst = funcname(src, *dst, 32, is_data_reg(dst))

#define BINOP_TOMEM_8(funcname)                                                \
  write_8(dst, funcname(src, read_8(dst), 8, true))
#define BINOP_TOMEM_16(funcname)                                               \
  write_16(dst, funcname(src, read_16(dst), 16, true))
#define BINOP_TOMEM_32(funcname)                                               \
  write_32(dst, funcname(src, read_32(dst), 32, true))

#if (TEST_LEVEL != 0)
INLINE bool is_data_reg(u32 *reg) {
  return (reg == &D0) || (reg == &D1) || (reg == &D2) || (reg == &D3) ||
         (reg == &D4) || (reg == &D5) || (reg == &D6) || (reg == &D7);
}
#else
#define is_data_reg(reg) true
#endif

INLINE u32 add(u32 src, u32 dst, u8 bits, bool setflags) {
  src = MASKED(src, bits);
  dst = MASKED(dst, bits);
  u32 res = src + dst;

  if (setflags) {
    SET_FLAG_N(MASKED(res, bits) >= SIGNMASK(bits));
    SET_FLAG_V((((src ^ res) & (dst ^ res)) >> (bits - 8)) & VFLAG_SET);
    if (bits == 32) {
      SET_FLAG_C((((src & dst) | (~res & (src | dst))) >> 23) & CFLAG_SET);
    } else {
      SET_FLAG_C((res >> (bits - 8)) & CFLAG_SET);
    }
    SET_FLAG_X(GET_FLAG_C);
    SET_FLAG_Z(MASKED(res, bits) == 0);
  }

  return MASKED(res, bits);
}

INLINE u32 addx(u32 src, u32 dst, u8 bits, bool setflags) {
  src = MASKED(src, bits);
  dst = MASKED(dst, bits);
  u32 res = src + dst + GET_FLAG_X;

  if (setflags) {
    SET_FLAG_N(MASKED(res, bits) >= SIGNMASK(bits));
    SET_FLAG_V((((src ^ res) & (dst ^ res)) >> (bits - 8)) & VFLAG_SET);
    SET_FLAG_C((res >> (bits - 8)) & CFLAG_SET);
    SET_FLAG_X(GET_FLAG_C);
    if (MASKED(res, bits) != 0) {
      SET_FLAG_Z(0);
    }
  }

  return MASKED(res, bits);
}

INLINE u32 and (u32 src, u32 dst, u8 bits, bool setflags) {
  u32 res = MASKED(dst & src, bits);

  SET_FLAG_N(res >= SIGNMASK(bits));
  SET_FLAG_Z(res == 0);
  SET_FLAG_V(0);
  SET_FLAG_C(0);

  return res;
}

INLINE u32 asl(u32 src, u32 dst, u8 bits, bool setflags) {
  u32 shift = src & 0x3f;
  src = MASKED(dst, bits);
  u32 res = MASKED((shift >= 32) ? 0 : (src << shift), bits);

  SET_FLAG_N(res >= SIGNMASK(bits));
  SET_FLAG_Z(res == 0);
  switch (bits) {
  case 8:
    SET_FLAG_C((src << shift) & CFLAG_SET);
    src &= m68ki_shift_8_table[shift + 1];
    SET_FLAG_V(
        ((!(src == 0 || (src == m68ki_shift_8_table[shift + 1] && shift < 8)))
         << 7) &
        VFLAG_SET);
    break;
  case 16:
    SET_FLAG_C((src >> (8 - shift)) & CFLAG_SET);
    src &= m68ki_shift_16_table[shift + 1];
    SET_FLAG_V(((!(src == 0 || src == m68ki_shift_16_table[shift + 1])) << 7) &
               VFLAG_SET);
    break;
  case 32:
    SET_FLAG_C((src >> (24 - shift)) & CFLAG_SET);
    src &= m68ki_shift_32_table[shift + 1];
    SET_FLAG_V(((!(src == 0 || src == m68ki_shift_32_table[shift + 1])) << 7) &
               VFLAG_SET);
    break;
  }
  SET_FLAG_X(GET_FLAG_C);

  return res;
}

INLINE u32 asr_8(u32 src, u32 dst, u8 bits, bool setflags) {
  u32 shift = (src & 0x3f);
  src = (dst & 0xff);
  u32 res = src >> (shift & 0x1f);

  if (shift != 0) {
    if (shift < 8) {
      if (src & 0x80) {
        res |= m68ki_shift_8_table[shift];
      }

      SET_FLAG_X((src << (9 - shift)) & XFLAG_SET);
      SET_FLAG_C(GET_FLAG_X);
      SET_FLAG_N((res & 0xff) >= 0x80);
      SET_FLAG_Z((res & 0xff) == 0);
      SET_FLAG_V(0);
      return res;
    }

    if (src & 0x80) {
      SET_FLAG_C(1);
      SET_FLAG_X(1);
      SET_FLAG_N(1);
      SET_FLAG_Z(0);
      SET_FLAG_V(0);
      return 0xff;
    }

    SET_FLAG_C(0);
    SET_FLAG_X(0);
    SET_FLAG_N(0);
    SET_FLAG_Z(1);
    SET_FLAG_V(0);
    return 0;
  }

  SET_FLAG_C(0);
  SET_FLAG_N((src & 0xff) >= 0x80);
  SET_FLAG_Z((src & 0xff) == 0);
  SET_FLAG_V(0);
  return dst;
}

INLINE u32 asr_16(u32 src, u32 dst, u8 bits, bool setflags) {
  u32 shift = (src & 0x3f);
  src = (dst & 0xffff);
  u32 res = src >> (shift & 0x1f);

  if (shift != 0) {
    if (shift < 16) {
      if (src & 0x8000) {
        res |= m68ki_shift_16_table[shift];
      }

      SET_FLAG_X(((src >> (shift - 1)) << 8) & XFLAG_SET);
      SET_FLAG_C(GET_FLAG_X);
      SET_FLAG_N((res & 0xffff) >= 0x8000);
      SET_FLAG_Z((res & 0xffff) == 0);
      SET_FLAG_V(0);
      return res;
    }

    if (src & 0x8000) {
      SET_FLAG_C(1);
      SET_FLAG_X(1);
      SET_FLAG_N(1);
      SET_FLAG_Z(0);
      SET_FLAG_V(0);
      return 0xffff;
    }

    SET_FLAG_C(0);
    SET_FLAG_X(0);
    SET_FLAG_N(0);
    SET_FLAG_Z(1);
    SET_FLAG_V(0);
    return 0;
  }

  SET_FLAG_C(0);
  SET_FLAG_N((src & 0xffff) >= 0x8000);
  SET_FLAG_Z((src & 0xffff) == 0);
  SET_FLAG_V(0);
  return dst;
}

INLINE u32 asr_32(u32 src, u32 dst, u8 bits, bool setflags) {
  u32 shift = (src & 0x3f);
  src = dst;
  u32 res = src >> (shift & 0x1f);

  if (shift != 0) {
    if (shift < 32) {
      if (src & 0x80000000) {
        res |= m68ki_shift_32_table[shift];
      }

      SET_FLAG_X(((src >> (shift - 1)) << 8) & XFLAG_SET);
      SET_FLAG_C(GET_FLAG_X);
      SET_FLAG_N(res >= 0x80000000);
      SET_FLAG_Z(res == 0);
      SET_FLAG_V(0);

      return res;
    }

    if (src & 0x80000000) {
      SET_FLAG_C(1);
      SET_FLAG_X(1);
      SET_FLAG_N(1);
      SET_FLAG_Z(0);
      SET_FLAG_V(0);
      return 0xffffffff;
    }

    SET_FLAG_C(0);
    SET_FLAG_X(0);
    SET_FLAG_N(0);
    SET_FLAG_Z(1);
    SET_FLAG_V(0);
    return 0;
  }

  SET_FLAG_C(0);
  SET_FLAG_N(src >= 0x80000000);
  SET_FLAG_Z(src == 0);
  SET_FLAG_V(0);

  return dst;
}

INLINE u32 bchg(u32 src, u32 dst, u8 bits, bool setflags) {
  u32 mask = 1 << ((src & (bits - 1)) & 0x1f);

  SET_FLAG_Z((dst & mask) == 0);
  return dst ^ mask;
}

INLINE u32 bclr(u32 src, u32 dst, u8 bits, bool setflags) {
  u32 mask = 1 << ((src & (bits - 1)) & 0x1f);

  SET_FLAG_Z((dst & mask) == 0);
  return dst & ~mask;
}

INLINE u32 bset(u32 src, u32 dst, u8 bits, bool setflags) {
  u32 mask = 1 << ((src & (bits - 1)) & 0x1f);

  SET_FLAG_Z((dst & mask) == 0);
  return dst | mask;
}

INLINE u32 btst(u32 src, u32 dst, u8 bits, bool setflags) {
  u32 mask = 1 << ((src & (bits - 1)) & 0x1f);
  SET_FLAG_Z((dst & mask) == 0);
  return dst;
}

INLINE u32 clr(u32 src, u32 dst, u8 bits, bool setflags) {
  SET_FLAG_N(0);
  SET_FLAG_V(0);
  SET_FLAG_C(0);
  SET_FLAG_Z(1);

  return dst & ~SIZE_MASKS[bits >> 4];
}

INLINE u32 cmp(u32 src, u32 dst, u8 bits, bool setflags) {
  u32 dstbackup = dst;
  src = MASKED(src, bits);
  dst = MASKED(dst, bits);
  u32 res = dst - src;

  SET_FLAG_N(MASKED(res, bits) >= SIGNMASK(bits));
  SET_FLAG_Z(MASKED(res, bits) == 0);
  SET_FLAG_V((((src ^ dst) & (res ^ dst)) >> (bits - 8)) & VFLAG_SET);
  switch (bits) {
  case 8:
  case 16:
    SET_FLAG_C((res >> (bits - 8)) & CFLAG_SET);
    break;
  case 32:
    SET_FLAG_C((((src & res) | (~dst & (src | res))) >> 23) & CFLAG_SET);
  }

  return dstbackup;
}

INLINE u32 divu(u32 src, u32 dst, u8 bits, bool setflags) {
  u32 quotient = dst / src;
  u32 remainder = dst % src;
  if (quotient < 0x10000) {
    SET_FLAG_Z(quotient == 0);
    SET_FLAG_N((quotient >> 8) & NFLAG_SET);
    SET_FLAG_V(0);
    SET_FLAG_C(0);
    return (remainder << 16) | (quotient & 0xffff);
  } else {
    return dst;
  }
}

INLINE u32 divs(u32 src, u32 dst, u8 bits, bool setflags) {
  src = (s32)((s16)src);
  if ((dst == 0x80000000) && ((s32)src == -1)) {
    SET_FLAG_N(0);
    SET_FLAG_V(0);
    SET_FLAG_C(0);
    SET_FLAG_Z(1);
    return 0;
  }
  s32 quotient = ((s32)dst) / ((s32)src);
  s32 remainder = ((s32)dst) % ((s32)src);
  if (quotient == ((s32)((s16)quotient))) {
    SET_FLAG_Z(quotient == 0);
    SET_FLAG_N(quotient < 0);
    SET_FLAG_V(0);
    SET_FLAG_C(0);
    return ((remainder << 16) | (((u32)quotient) & 0xffff));
  } else {
    SET_FLAG_V(1);
    return dst;
  }
}

INLINE u32 eor(u32 src, u32 dst, u8 bits, bool setflags) {
  u32 res = MASKED(dst ^ src, bits);

  SET_FLAG_N(res >= SIGNMASK(bits));
  SET_FLAG_Z(res == 0);
  SET_FLAG_C(0);
  SET_FLAG_V(0);

  return res;
}

INLINE u32 ext(u32 src, u32 dst, u8 bits, bool setflags) {
  u32 res = 0;
  if (bits == 16) {
    res = (u16)((s16)((s8)dst));
  } else if (bits == 32) {
    res = (s32)((s16)dst);
  }
  SET_FLAG_N(MASKED(res, bits) >= SIGNMASK(bits));
  SET_FLAG_Z(MASKED(res, bits) == 0);
  SET_FLAG_V(0);
  SET_FLAG_C(0);
  return res;
}

INLINE u32 lsl(u32 src, u32 dst, u8 bits, bool setflags) {
  //   u32 *r_dst = &DY;
  u32 shift = src & 0x3f;
  src = MASKED(dst, bits);
  u32 res = MASKED(src << (shift & 0x1f), bits);

  if (shift != 0) {
    if (shift <= bits) {
      //   *r_dst = MASK_OUT_BELOW_16(*r_dst) | res;
      switch (bits) {
      case 8:
        SET_FLAG_C((src << shift) & CFLAG_SET);
        break;
      case 16:
        SET_FLAG_C(((src << shift) >> 8) & CFLAG_SET);
        break;
      case 32:
        SET_FLAG_C(((src >> (32 - shift)) << 8) & CFLAG_SET);
        break;
      }
      SET_FLAG_X(GET_FLAG_C);
      SET_FLAG_N((res >> (bits - 8)) & NFLAG_SET);
      SET_FLAG_Z(res == 0);
      SET_FLAG_V(0);
      return res;
    }

    // *r_dst &= 0xffff0000;
    SET_FLAG_X(0);
    SET_FLAG_C(0);
    SET_FLAG_N(0);
    SET_FLAG_Z(1);
    SET_FLAG_V(0);
    return 0;
  }

  SET_FLAG_C(0);
  SET_FLAG_N(src >= SIGNMASK(bits));
  SET_FLAG_Z(src == 0);
  SET_FLAG_V(0);
  return dst;
}

INLINE u32 lsr(u32 src, u32 dst, u8 bits, bool setflags) {
  //   u32 *r_dst = &DY;
  u32 shift = src & 0x3f;
  src = MASKED(dst, bits);
  u32 res = src >> (shift & 0x1f);

  if (shift != 0) {
    if (shift <= bits) {
      //   *r_dst = MASK_OUT_BELOW_16(*r_dst) | res;
      SET_FLAG_N(0);
      SET_FLAG_Z(res == 0);
      SET_FLAG_V(0);
      switch (bits) {
      case 8:
        SET_FLAG_C((src << ((9 - shift) & 0x1f)) & CFLAG_SET);
        break;
      case 16:
        SET_FLAG_C(((src >> (shift - 1)) << 8) & CFLAG_SET);
        break;
      case 32:
        SET_FLAG_C(((src >> (shift - 1)) << 8) & CFLAG_SET);
        break;
      }
      SET_FLAG_X(GET_FLAG_C);
      return res;
    }

    // *r_dst &= 0xffff0000;
    SET_FLAG_X(0);
    SET_FLAG_C(0);
    SET_FLAG_N(0);
    SET_FLAG_Z(1);
    SET_FLAG_V(0);
    return 0;
  }

  SET_FLAG_C(0);
  SET_FLAG_N(src >= SIGNMASK(bits));
  SET_FLAG_Z(src == 0);
  SET_FLAG_V(0);
  return dst;
}

INLINE u32 move(u32 src, u32 dst, u8 bits, bool setflags) {
  src = MASKED(src, bits);
  if (setflags) {
    SET_FLAG_N(src >= SIGNMASK(bits));
    SET_FLAG_Z(src == 0);
    SET_FLAG_V(0);
    SET_FLAG_C(0);
  }
  return src;
}

INLINE u32 neg(u32 src, u32 dst, u8 bits, bool setflags) {
  u32 res = 0 - MASKED(dst, bits);

  SET_FLAG_N(MASKED(res, bits) >= SIGNMASK(bits));
  SET_FLAG_C(MASKED(res, bits) != 0);
  SET_FLAG_X(GET_FLAG_C);
  SET_FLAG_V(((dst & res) >> (bits - 8)) & VFLAG_SET);
  SET_FLAG_Z(MASKED(res, bits) == 0);

  return MASKED(res, bits);
}

INLINE u32 not(u32 src, u32 dst, u8 bits, bool setflags) {
  u32 res = MASKED(~dst, bits);

  SET_FLAG_Z(res == 0);
  SET_FLAG_N(res >= SIGNMASK(bits));
  SET_FLAG_C(0);
  SET_FLAG_V(0);

  return res;
}

INLINE u32 or (u32 src, u32 dst, u8 bits, bool setflags) {
  u32 res = MASKED(dst | src, bits);

  SET_FLAG_N(res >= SIGNMASK(bits));
  SET_FLAG_Z(res == 0);
  SET_FLAG_C(0);
  SET_FLAG_V(0);

  return res;
}

INLINE u32 rol_8(u32 src, u32 dst, u8 bits, bool setflags) {
  u32 orig_shift = (src & 0x3f);
  u32 shift = (orig_shift & 7);
  src = (dst & 0xff);
  u32 res = (((src << shift) | (src >> (8 - (shift)))) & 0xff);

  if (orig_shift != 0) {
    if (shift != 0) {
      SET_FLAG_C((src << shift) & CFLAG_SET);
      SET_FLAG_N(res & NFLAG_SET);
      SET_FLAG_Z(res == 0);
      SET_FLAG_V(0);
      return res;
    }
    SET_FLAG_C(((src & 1) << 8) & CFLAG_SET);
    SET_FLAG_N(src & NFLAG_SET);
    SET_FLAG_Z(src == 0);
    SET_FLAG_V(0);
    return dst;
  }

  SET_FLAG_C(0);
  SET_FLAG_N(src & NFLAG_SET);
  SET_FLAG_Z(src == 0);
  SET_FLAG_V(0);
  return src;
}

INLINE u32 rol_16(u32 src, u32 dst, u8 bits, bool setflags) {
  u32 orig_shift = (src & 0x3f);
  u32 shift = (orig_shift & 15);
  src = (dst & 0xffff);
  u32 res = (((src << shift) | (src >> (16 - (shift)))) & 0xffff);

  if (orig_shift != 0) {
    if (shift != 0) {
      SET_FLAG_C(((src << shift) >> 8) & CFLAG_SET);
      SET_FLAG_N((res >> 8) & NFLAG_SET);
      SET_FLAG_Z(res == 0);
      SET_FLAG_V(0);
      return res;
    }
    SET_FLAG_C(((src & 1) << 8) & CFLAG_SET);
    SET_FLAG_N((src >> 8) & NFLAG_SET);
    SET_FLAG_Z(src == 0);
    SET_FLAG_V(0);
    return dst;
  }

  SET_FLAG_C(0);
  SET_FLAG_N((src >> 8) & NFLAG_SET);
  SET_FLAG_Z(src == 0);
  SET_FLAG_V(0);
  return dst;
}

INLINE u32 rol_32(u32 src, u32 dst, u8 bits, bool setflags) {
  u32 orig_shift = src;
  src = dst;
  if (orig_shift != 0) {
    u32 shift = (orig_shift & 31);
    u32 res = ((src << shift) | (src >> (32 - (shift))));
    SET_FLAG_N((res >> 24) & NFLAG_SET);
    SET_FLAG_Z(res == 0);
    SET_FLAG_C(((src >> (32 - shift)) << 8) & CFLAG_SET);
    SET_FLAG_V(0);
    return res;
  } else {
    SET_FLAG_N((src >> 24) & NFLAG_SET);
    SET_FLAG_Z(src == 0);
    SET_FLAG_V(0);
    SET_FLAG_C(0);
    return src;
  }
}

INLINE u32 ror(u32 src, u32 dst, u8 bits, bool setflags) {
  u32 shift = (src & 0x1f);
  src = MASKED(src, bits);
  dst = MASKED(dst, bits);
  u32 res = MASKED((dst >> shift) | (dst << (bits - (shift))), bits);

  SET_FLAG_N(res >= SIGNMASK(bits));
  SET_FLAG_Z(res == 0);
  SET_FLAG_C((dst << (9 - shift)) & CFLAG_SET);
  SET_FLAG_V(0);

  return res;
}

INLINE u32 roxl(u32 src, u32 dst, u8 bits, bool setflags) {
  u32 orig_shift = src;
  if (orig_shift != 0) {
    u32 shift = (orig_shift % (bits + 1));
    src = MASKED(dst, bits);
    u32 xbits = ((GET_FLAG_X >> 4) << bits);
    u32 srcxbits = (src | xbits);
    u32 res = ((srcxbits << shift) | (srcxbits >> (17 - shift)));

    SET_FLAG_X((res >> (bits - 8)) & XFLAG_SET);
    SET_FLAG_C(GET_FLAG_X);
    res = MASKED(res, bits);
    SET_FLAG_N((res >> 8) & NFLAG_SET);
    SET_FLAG_Z(res == 0);
    SET_FLAG_V(0);
    return res;
  } else {
    SET_FLAG_C(GET_FLAG_X);
    SET_FLAG_N((dst >> 8) & NFLAG_SET);
    SET_FLAG_Z(MASKED(dst, bits) == 0);
    SET_FLAG_V(0);
    return dst;
  }
}

INLINE u32 sub(u32 src, u32 dst, u8 bits, bool setflags) {
  dst = MASKED(dst, bits);
  src = MASKED(src, bits);
  u32 res = dst - src;

  if (setflags) {
    u32 res_hi = (res >> (bits - 8));
    SET_FLAG_N(res_hi & NFLAG_SET);
    SET_FLAG_V((((src ^ dst) & (res ^ dst)) >> (bits - 8)) & VFLAG_SET);
    if (bits == 32) {
      SET_FLAG_C((((src & res) | (~dst & (src | res))) >> 23) & CFLAG_SET);
    } else {
      SET_FLAG_C(res_hi & CFLAG_SET);
    }
    SET_FLAG_X(GET_FLAG_C);
    SET_FLAG_Z(MASKED(res, bits) == 0);
  }

  return MASKED(res, bits);
}

INLINE u32 tst(u32 src, u32 dst, u8 bits, bool setflags) {
  SET_FLAG_N(MASKED(dst, bits) >= SIGNMASK(bits));
  SET_FLAG_Z(MASKED(dst, bits) == 0);
  SET_FLAG_V(0);
  SET_FLAG_C(0);
  return dst;
}

#define TODO(funcname) print("TODO: " #funcname)

INLINE void add_tomem_16(u32 src, u32 dst) { BINOP_TOMEM_16(add); }
INLINE void add_tomem_32(u32 src, u32 dst) { BINOP_TOMEM_32(add); }
INLINE void add_tomem_8(u32 src, u32 dst) { BINOP_TOMEM_8(add); }
INLINE void add_toreg_16(u32 src, u32 *dst) {
  if (is_data_reg(dst)) {
    BINOP_TOREG_16(add);
  } else {
    *dst = add((s32)((s16)src), *dst, 32, false);
  }
}
INLINE void add_toreg_32(u32 src, u32 *dst) { BINOP_TOREG_32(add); }
INLINE void add_toreg_8(u32 src, u32 *dst) { BINOP_TOREG_8(add); }
INLINE void addx_toreg_16(u32 src, u32 *dst) { TODO(addx_toreg_16); }
INLINE void and_tomem_16(u32 src, u32 dst) { BINOP_TOMEM_16(and); }
INLINE void and_tomem_32(u32 src, u32 dst) { BINOP_TOMEM_32(and); }
INLINE void and_tomem_8(u32 src, u32 dst) { BINOP_TOMEM_8(and); }
INLINE void and_toreg_16(u32 src, u32 *dst) { BINOP_TOREG_16(and); }
INLINE void and_toreg_32(u32 src, u32 *dst) { BINOP_TOREG_32(and); }
INLINE void and_toreg_8(u32 src, u32 *dst) { BINOP_TOREG_8(and); }
INLINE void asl_mem_16(u32 dst) {
  u32 src = 1;
  BINOP_TOMEM_16(asl);
}
INLINE void asl_toreg_16(u32 src, u32 *dst) { BINOP_TOREG_16(asl); }
INLINE void asl_toreg_32(u32 src, u32 *dst) { BINOP_TOREG_32(asl); }
INLINE void asr_mem_16(u32 dst) {
  u32 src = 1;
  BINOP_TOMEM_16(asr_16);
}
INLINE void asr_toreg_16(u32 src, u32 *dst) { BINOP_TOREG_16(asr_16); }
INLINE void asr_toreg_32(u32 src, u32 *dst) { BINOP_TOREG_32(asr_32); }
INLINE void asr_toreg_8(u32 src, u32 *dst) { BINOP_TOREG_8(asr_8); }
INLINE void bchg_tomem_8(u32 src, u32 dst) { BINOP_TOMEM_8(bchg); }
INLINE void bchg_toreg_32(u32 src, u32 *dst) { BINOP_TOREG_32(bchg); }
INLINE void bclr_tomem_8(u32 src, u32 dst) { BINOP_TOMEM_8(bclr); }
INLINE void bclr_toreg_32(u32 src, u32 *dst) { BINOP_TOREG_32(bclr); }
INLINE void bset_tomem_8(u32 src, u32 dst) { BINOP_TOMEM_8(bset); }
INLINE void bset_toreg_32(u32 src, u32 *dst) { BINOP_TOREG_32(bset); }
INLINE void btst_tomem_8(u32 src, u32 dst) { btst(src, read_8(dst), 8, true); }
INLINE void btst_toreg_32(u32 src, u32 *dst) { btst(src, *dst, 32, true); }
INLINE void clr_mem_16(u32 dst) {
  u32 src = 0;
  BINOP_TOMEM_16(clr);
}
INLINE void clr_mem_32(u32 dst) {
  u32 src = 0;
  BINOP_TOMEM_32(clr);
}
INLINE void clr_mem_8(u32 dst) {
  u32 src = 0;
  BINOP_TOMEM_8(clr);
}
INLINE void clr_reg_16(u32 *dst) {
  u32 src = 0;
  BINOP_TOREG_16(clr);
}
INLINE void clr_reg_8(u32 *dst) {
  u32 src = 0;
  BINOP_TOREG_8(clr);
}
INLINE void cmp_tomem_16(u32 src, u32 dst) { cmp(src, read_16(dst), 16, true); }
INLINE void cmp_tomem_32(u32 src, u32 dst) { cmp(src, read_32(dst), 32, true); }
INLINE void cmp_tomem_8(u32 src, u32 dst) { cmp(src, read_8(dst), 8, true); }
INLINE void cmp_toreg_16(u32 src, u32 *dst) { cmp(src, *dst, 16, true); }
INLINE void cmp_toreg_32(u32 src, u32 *dst) { cmp(src, *dst, 32, true); }
INLINE void cmp_toreg_8(u32 src, u32 *dst) { cmp(src, *dst, 8, true); }
INLINE void dec_reg_16(u32 *reg) { SETWORD(*reg, *reg - 1); }
INLINE void divs_toreg_16(u32 src, u32 *dst) { BINOP_TOREG_32(divs); }
INLINE void divu_toreg_16(u32 src, u32 *dst) { BINOP_TOREG_32(divu); }
INLINE void eor_tomem_8(u32 src, u32 dst) { BINOP_TOMEM_8(eor); }
INLINE void eor_toreg_16(u32 src, u32 *dst) { BINOP_TOREG_16(eor); }
INLINE void eor_toreg_32(u32 src, u32 *dst) { BINOP_TOREG_32(eor); }
INLINE void eor_toreg_8(u32 src, u32 *dst) { BINOP_TOREG_8(eor); }
INLINE void exg_toreg_32(u32 *reg1, u32 *reg2) {
  u32 tmp = *reg2;
  *reg2 = *reg1;
  *reg1 = tmp;
}
INLINE void ext_reg_16(u32 *dst) {
  u32 src = 0;
  BINOP_TOREG_16(ext);
}
INLINE void ext_reg_32(u32 *dst) {
  u32 src = 0;
  BINOP_TOREG_32(ext);
}
INLINE void lsl_toreg_16(u32 src, u32 *dst) { BINOP_TOREG_16(lsl); }
INLINE void lsl_toreg_32(u32 src, u32 *dst) { BINOP_TOREG_32(lsl); }
INLINE void lsl_toreg_8(u32 src, u32 *dst) { BINOP_TOREG_8(lsl); }
INLINE void lsr_toreg_16(u32 src, u32 *dst) { BINOP_TOREG_16(lsr); }
INLINE void lsr_toreg_32(u32 src, u32 *dst) { BINOP_TOREG_32(lsr); }
INLINE void lsr_toreg_8(u32 src, u32 *dst) { BINOP_TOREG_8(lsr); }
INLINE void move_sr_toreg_16(u32 sr, u32 *dst) {
  SETWORD(*dst, move(sr, *dst, 16, false));
}
INLINE void move_tomem_16(u32 src, u32 dst) { BINOP_TOMEM_16(move); }
INLINE void move_tomem_32(u32 src, u32 dst) { BINOP_TOMEM_32(move); }
INLINE void move_tomem_8(u32 src, u32 dst) { BINOP_TOMEM_8(move); }
INLINE void move_toreg_16(u32 src, u32 *dst) {
  if (is_data_reg(dst)) {
    BINOP_TOREG_16(move);
  } else {
    u32 res = (s32)((s16)move(src, *dst, 16, false));
    *dst = res;
  }
}
INLINE void move_toreg_32(u32 src, u32 *dst) { BINOP_TOREG_32(move); }
INLINE void move_toreg_8(u32 src, u32 *dst) { BINOP_TOREG_8(move); }
INLINE void move_toccr_8(u32 src, u32 *sr) {
  SETBYTE(*sr, move(src, *sr, 8, false));
}
INLINE void move_tosr_16(u32 src, u32 *sr) {
  SETWORD(*sr, move(src, *sr, 16, false));
}
INLINE void muls_toreg_16(u32 src, u32 *dst) {
  u32 res = (u32)(((s32)((s16)src)) * ((s32)((s16)*dst)));
  SET_FLAG_Z(res == 0);
  SET_FLAG_N(res >= 0x80000000);
  SET_FLAG_V(0);
  SET_FLAG_C(0);
  *dst = res;
}
INLINE void mulu_toreg_16(u32 src, u32 *dst) {
  u32 res = (u32)(((u16)src) * ((u16)*dst));
  SET_FLAG_Z(res == 0);
  SET_FLAG_N(res >= 0x80000000);
  SET_FLAG_V(0);
  SET_FLAG_C(0);
  *dst = res;
}
INLINE void neg_mem_16(u32 dst) {
  u32 src = 0;
  BINOP_TOMEM_16(neg);
}
INLINE void neg_mem_8(u32 dst) {
  u32 src = 0;
  BINOP_TOMEM_8(neg);
}
INLINE void neg_reg_16(u32 *dst) {
  u32 src = 0;
  BINOP_TOREG_16(neg);
}
INLINE void neg_reg_8(u32 *dst) {
  u32 src = 0;
  BINOP_TOREG_8(neg);
}
INLINE void not_mem_8(u32 dst) {
  u32 src = 0;
  BINOP_TOMEM_8(not);
}
INLINE void not_reg_16(u32 *dst) {
  u32 src = 0;
  BINOP_TOREG_16(not);
}
INLINE void not_reg_8(u32 *dst) {
  u32 src = 0;
  BINOP_TOREG_8(not);
}
INLINE void or_tomem_16(u32 src, u32 dst) { BINOP_TOMEM_16(or); }
INLINE void or_tomem_32(u32 src, u32 dst) { BINOP_TOMEM_32(or); }
INLINE void or_tomem_8(u32 src, u32 dst) { BINOP_TOMEM_8(or); }
INLINE void or_toreg_16(u32 src, u32 *dst) { BINOP_TOREG_16(or); }
INLINE void or_toreg_32(u32 src, u32 *dst) { BINOP_TOREG_32(or); }
INLINE void or_toreg_8(u32 src, u32 *dst) { BINOP_TOREG_8(or); }
INLINE void rol_toreg_16(u32 src, u32 *dst) { BINOP_TOREG_16(rol_16); }
INLINE void rol_toreg_32(u32 src, u32 *dst) { BINOP_TOREG_32(rol_32); }
INLINE void rol_toreg_8(u32 src, u32 *dst) { BINOP_TOREG_8(rol_8); }
INLINE void ror_toreg_16(u32 src, u32 *dst) { BINOP_TOREG_16(ror); }
INLINE void ror_toreg_32(u32 src, u32 *dst) { BINOP_TOREG_32(ror); }
INLINE void ror_toreg_8(u32 src, u32 *dst) { BINOP_TOREG_8(ror); }
INLINE void roxl_toreg_16(u32 src, u32 *dst) { BINOP_TOREG_16(roxl); }
INLINE void sub_tomem_16(u32 src, u32 dst) { BINOP_TOMEM_16(sub); }
INLINE void sub_tomem_32(u32 src, u32 dst) { BINOP_TOMEM_32(sub); }
INLINE void sub_tomem_8(u32 src, u32 dst) { BINOP_TOMEM_8(sub); }
INLINE void sub_toreg_16(u32 src, u32 *dst) { BINOP_TOREG_16(sub); }
INLINE void sub_toreg_32(u32 src, u32 *dst) { BINOP_TOREG_32(sub); }
INLINE void sub_toreg_8(u32 src, u32 *dst) { BINOP_TOREG_8(sub); }
/*INLINE void swap_reg_16(u32 *reg) {
  *reg = ((*reg << 16) | (*reg >> 16));
  SET_FLAG_N(*reg >= 0x80000000);
  SET_FLAG_Z(*reg == 0);
  SET_FLAG_V(0);
  SET_FLAG_C(0);
}*/
INLINE void tst_mem_16(u32 dst) { tst(0, read_16(dst), 16, true); }
INLINE void tst_mem_32(u32 dst) { tst(0, read_32(dst), 32, true); }
INLINE void tst_mem_8(u32 dst) { tst(0, read_8(dst), 8, true); }
INLINE void tst_reg_16(u32 *dst) { tst(0, *dst, 16, true); }
INLINE void tst_reg_32(u32 *dst) { tst(0, *dst, 32, true); }
INLINE void tst_reg_8(u32 *dst) { tst(0, *dst, 8, true); }
#endif