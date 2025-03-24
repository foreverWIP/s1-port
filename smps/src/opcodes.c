#include "opcodes.h"
#include "system.h"

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

static u32 SIZE_MASKS[] = {
    0x000000ff,
    0x0000ffff,
    0xffffffff,
};
#define MASKED(value, bits) ((value) & SIZE_MASKS[bits >> 4])
static u32 SIZE_SIGNS[] = {
    0x00000080,
    0x00008000,
    0x80000000,
};
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
static bool is_data_reg(u32 *reg) {
  return (reg == &D0) || (reg == &D1) || (reg == &D2) || (reg == &D3) ||
         (reg == &D4) || (reg == &D5) || (reg == &D6) || (reg == &D7);
}
#else
#define is_data_reg(reg) true
#endif

u32 add(u32 src, u32 dst, u8 bits, bool setflags) {
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

u32 addx(u32 src, u32 dst, u8 bits, bool setflags) {
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

u32 and (u32 src, u32 dst, u8 bits, bool setflags) {
  u32 res = MASKED(dst & src, bits);

  SET_FLAG_N(res >= SIGNMASK(bits));
  SET_FLAG_Z(res == 0);
  SET_FLAG_V(0);
  SET_FLAG_C(0);

  return res;
}

const u8 m68ki_shift_8_table[65] = {
    0x00, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
const u16 m68ki_shift_16_table[65] = {
    0x0000, 0x8000, 0xc000, 0xe000, 0xf000, 0xf800, 0xfc00, 0xfe00, 0xff00,
    0xff80, 0xffc0, 0xffe0, 0xfff0, 0xfff8, 0xfffc, 0xfffe, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff};
const u32 m68ki_shift_32_table[65] = {
    0x00000000, 0x80000000, 0xc0000000, 0xe0000000, 0xf0000000, 0xf8000000,
    0xfc000000, 0xfe000000, 0xff000000, 0xff800000, 0xffc00000, 0xffe00000,
    0xfff00000, 0xfff80000, 0xfffc0000, 0xfffe0000, 0xffff0000, 0xffff8000,
    0xffffc000, 0xffffe000, 0xfffff000, 0xfffff800, 0xfffffc00, 0xfffffe00,
    0xffffff00, 0xffffff80, 0xffffffc0, 0xffffffe0, 0xfffffff0, 0xfffffff8,
    0xfffffffc, 0xfffffffe, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
    0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
    0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
    0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
    0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
    0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff};

u32 asl(u32 src, u32 dst, u8 bits, bool setflags) {
  u32 shift = src & 0x1f;
  src = MASKED(dst, bits);
  u32 res = MASKED(src << shift, bits);

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

u32 asr_8(u32 src, u32 dst, u8 bits, bool setflags) {
  u32 shift = (src & 0x3f);
  src = (dst & 0xff);
  u32 res = src >> shift;

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

u32 asr_16(u32 src, u32 dst, u8 bits, bool setflags) {
  u32 shift = (src & 0x3f);
  src = (dst & 0xffff);
  u32 res = src >> shift;

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

u32 asr_32(u32 src, u32 dst, u8 bits, bool setflags) {
  u32 shift = (src & 0x3f);
  src = dst;
  u32 res = src >> shift;

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

u32 bchg(u32 src, u32 dst, u8 bits, bool setflags) {
  u32 mask = 1 << (src & (bits - 1));

  SET_FLAG_Z((dst & mask) == 0);
  return dst ^ mask;
}

u32 bclr(u32 src, u32 dst, u8 bits, bool setflags) {
  u32 mask = 1 << (src & (bits - 1));

  SET_FLAG_Z((dst & mask) == 0);
  return dst & ~mask;
}

u32 bset(u32 src, u32 dst, u8 bits, bool setflags) {
  u32 mask = 1 << (src & (bits - 1));

  SET_FLAG_Z((dst & mask) == 0);
  return dst | mask;
}

u32 btst(u32 src, u32 dst, u8 bits, bool setflags) {
  u32 mask = 1 << (src & (bits - 1));
  SET_FLAG_Z((dst & mask) == 0);
  return dst;
}

u32 clr(u32 src, u32 dst, u8 bits, bool setflags) {
  SET_FLAG_N(0);
  SET_FLAG_V(0);
  SET_FLAG_C(0);
  SET_FLAG_Z(1);

  return dst & ~SIZE_MASKS[bits >> 4];
}

u32 cmp(u32 src, u32 dst, u8 bits, bool setflags) {
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

u32 divu(u32 src, u32 dst, u8 bits, bool setflags) {
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

u32 divs(u32 src, u32 dst, u8 bits, bool setflags) {
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

u32 eor(u32 src, u32 dst, u8 bits, bool setflags) {
  u32 res = MASKED(dst ^ src, bits);

  SET_FLAG_N(res >= SIGNMASK(bits));
  SET_FLAG_Z(res == 0);
  SET_FLAG_C(0);
  SET_FLAG_V(0);

  return res;
}

u32 ext(u32 src, u32 dst, u8 bits, bool setflags) {
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

u32 lsl(u32 src, u32 dst, u8 bits, bool setflags) {
  //   u32 *r_dst = &DY;
  u32 shift = src & 0x3f;
  src = MASKED(dst, bits);
  u32 res = MASKED(src << shift, bits);

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

u32 lsr(u32 src, u32 dst, u8 bits, bool setflags) {
  //   u32 *r_dst = &DY;
  u32 shift = src & 0x3f;
  src = MASKED(dst, bits);
  u32 res = src >> shift;

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

u32 move(u32 src, u32 dst, u8 bits, bool setflags) {
  src = MASKED(src, bits);
  if (setflags) {
    SET_FLAG_N(src >= SIGNMASK(bits));
    SET_FLAG_Z(src == 0);
    SET_FLAG_V(0);
    SET_FLAG_C(0);
  }
  return src;
}

u32 neg(u32 src, u32 dst, u8 bits, bool setflags) {
  u32 res = 0 - MASKED(dst, bits);

  SET_FLAG_N(MASKED(res, bits) >= SIGNMASK(bits));
  SET_FLAG_C(MASKED(res, bits) != 0);
  SET_FLAG_X(GET_FLAG_C);
  SET_FLAG_V(((dst & res) >> (bits - 8)) & VFLAG_SET);
  SET_FLAG_Z(MASKED(res, bits) == 0);

  return MASKED(res, bits);
}

u32 not(u32 src, u32 dst, u8 bits, bool setflags) {
  u32 res = MASKED(~dst, bits);

  SET_FLAG_Z(res == 0);
  SET_FLAG_N(res >= SIGNMASK(bits));
  SET_FLAG_C(0);
  SET_FLAG_V(0);

  return res;
}

u32 or (u32 src, u32 dst, u8 bits, bool setflags) {
  u32 res = MASKED(dst | src, bits);

  SET_FLAG_N(res >= SIGNMASK(bits));
  SET_FLAG_Z(res == 0);
  SET_FLAG_C(0);
  SET_FLAG_V(0);

  return res;
}

u32 rol_8(u32 src, u32 dst, u8 bits, bool setflags) {
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
}

u32 rol_16(u32 src, u32 dst, u8 bits, bool setflags) {
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

u32 rol_32(u32 src, u32 dst, u8 bits, bool setflags) {
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

u32 ror(u32 src, u32 dst, u8 bits, bool setflags) {
  u32 orig_shift = (src & 0x3f);
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

u32 roxl(u32 src, u32 dst, u8 bits, bool setflags) {
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

u32 sub(u32 src, u32 dst, u8 bits, bool setflags) {
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

u32 tst(u32 src, u32 dst, u8 bits, bool setflags) {
  SET_FLAG_N(MASKED(dst, bits) >= SIGNMASK(bits));
  SET_FLAG_Z(MASKED(dst, bits) == 0);
  SET_FLAG_V(0);
  SET_FLAG_C(0);
  return dst;
}

#define TODO(funcname) print("TODO: " #funcname)

void add_tomem_16(u32 src, u32 dst) { BINOP_TOMEM_16(add); }
void add_tomem_32(u32 src, u32 dst) { BINOP_TOMEM_32(add); }
void add_tomem_8(u32 src, u32 dst) { BINOP_TOMEM_8(add); }
void add_toreg_16(u32 src, u32 *dst) {
  if (is_data_reg(dst)) {
    BINOP_TOREG_16(add);
  } else {
    *dst = add((s32)((s16)src), *dst, 32, false);
  }
}
void add_toreg_32(u32 src, u32 *dst) { BINOP_TOREG_32(add); }
void add_toreg_8(u32 src, u32 *dst) { BINOP_TOREG_8(add); }
void addx_toreg_16(u32 src, u32 *dst) { TODO(addx_toreg_16); }
void and_tomem_16(u32 src, u32 dst) { BINOP_TOMEM_16(and); }
void and_tomem_32(u32 src, u32 dst) { BINOP_TOMEM_32(and); }
void and_tomem_8(u32 src, u32 dst) { BINOP_TOMEM_8(and); }
void and_toreg_16(u32 src, u32 *dst) { BINOP_TOREG_16(and); }
void and_toreg_32(u32 src, u32 *dst) { BINOP_TOREG_32(and); }
void and_toreg_8(u32 src, u32 *dst) { BINOP_TOREG_8(and); }
void asl_mem_16(u32 dst) {
  u32 src = 1;
  BINOP_TOMEM_16(asl);
}
void asl_toreg_16(u32 src, u32 *dst) { BINOP_TOREG_16(asl); }
void asl_toreg_32(u32 src, u32 *dst) { BINOP_TOREG_32(asl); }
void asr_mem_16(u32 dst) {
  u32 src = 1;
  BINOP_TOMEM_16(asr_16);
}
void asr_toreg_16(u32 src, u32 *dst) { BINOP_TOREG_16(asr_16); }
void asr_toreg_32(u32 src, u32 *dst) { BINOP_TOREG_32(asr_32); }
void asr_toreg_8(u32 src, u32 *dst) { BINOP_TOREG_8(asr_8); }
void bchg_tomem_8(u32 src, u32 dst) { BINOP_TOMEM_8(bchg); }
void bchg_toreg_32(u32 src, u32 *dst) { BINOP_TOREG_32(bchg); }
void bclr_tomem_8(u32 src, u32 dst) { BINOP_TOMEM_8(bclr); }
void bclr_toreg_32(u32 src, u32 *dst) { BINOP_TOREG_32(bclr); }
void bset_tomem_8(u32 src, u32 dst) { BINOP_TOMEM_8(bset); }
void bset_toreg_32(u32 src, u32 *dst) { BINOP_TOREG_32(bset); }
void btst_tomem_8(u32 src, u32 dst) { btst(src, read_8(dst), 8, true); }
void btst_toreg_32(u32 src, u32 *dst) { btst(src, *dst, 32, true); }
void clr_mem_16(u32 dst) {
  u32 src = 0;
  BINOP_TOMEM_16(clr);
}
void clr_mem_32(u32 dst) {
  u32 src = 0;
  BINOP_TOMEM_32(clr);
}
void clr_mem_8(u32 dst) {
  u32 src = 0;
  BINOP_TOMEM_8(clr);
}
void clr_reg_16(u32 *dst) {
  u32 src = 0;
  BINOP_TOREG_16(clr);
}
void clr_reg_8(u32 *dst) {
  u32 src = 0;
  BINOP_TOREG_8(clr);
}
void cmp_tomem_16(u32 src, u32 dst) { cmp(src, read_16(dst), 16, true); }
void cmp_tomem_32(u32 src, u32 dst) { cmp(src, read_32(dst), 32, true); }
void cmp_tomem_8(u32 src, u32 dst) { cmp(src, read_8(dst), 8, true); }
void cmp_toreg_16(u32 src, u32 *dst) { cmp(src, *dst, 16, true); }
void cmp_toreg_32(u32 src, u32 *dst) { cmp(src, *dst, 32, true); }
void cmp_toreg_8(u32 src, u32 *dst) { cmp(src, *dst, 8, true); }
void dec_reg_16(u32 *reg) { SETWORD(*reg, *reg - 1); }
void divs_toreg_16(u32 src, u32 *dst) { BINOP_TOREG_32(divs); }
void divu_toreg_16(u32 src, u32 *dst) { BINOP_TOREG_32(divu); }
void eor_tomem_8(u32 src, u32 dst) { BINOP_TOMEM_8(eor); }
void eor_toreg_16(u32 src, u32 *dst) { BINOP_TOREG_16(eor); }
void eor_toreg_32(u32 src, u32 *dst) { BINOP_TOREG_32(eor); }
void eor_toreg_8(u32 src, u32 *dst) { BINOP_TOREG_8(eor); }
void exg_toreg_32(u32 *reg1, u32 *reg2) {
  u32 tmp = *reg2;
  *reg2 = *reg1;
  *reg1 = tmp;
}
void ext_reg_16(u32 *dst) {
  u32 src = 0;
  BINOP_TOREG_16(ext);
}
void ext_reg_32(u32 *dst) {
  u32 src = 0;
  BINOP_TOREG_32(ext);
}
void lsl_toreg_16(u32 src, u32 *dst) { BINOP_TOREG_16(lsl); }
void lsl_toreg_32(u32 src, u32 *dst) { BINOP_TOREG_32(lsl); }
void lsl_toreg_8(u32 src, u32 *dst) { BINOP_TOREG_8(lsl); }
void lsr_toreg_16(u32 src, u32 *dst) { BINOP_TOREG_16(lsr); }
void lsr_toreg_32(u32 src, u32 *dst) { BINOP_TOREG_32(lsr); }
void lsr_toreg_8(u32 src, u32 *dst) { BINOP_TOREG_8(lsr); }
void move_sr_toreg_16(u32 sr, u32 *dst) {
  SETWORD(*dst, move(sr, *dst, 16, false));
}
void move_tomem_16(u32 src, u32 dst) { BINOP_TOMEM_16(move); }
void move_tomem_32(u32 src, u32 dst) { BINOP_TOMEM_32(move); }
void move_tomem_8(u32 src, u32 dst) { BINOP_TOMEM_8(move); }
void move_toreg_16(u32 src, u32 *dst) {
  if (is_data_reg(dst)) {
    BINOP_TOREG_16(move);
  } else {
    u32 res = (s32)((s16)move(src, *dst, 16, false));
    *dst = res;
  }
}
void move_toreg_32(u32 src, u32 *dst) { BINOP_TOREG_32(move); }
void move_toreg_8(u32 src, u32 *dst) { BINOP_TOREG_8(move); }
void move_toccr_8(u32 src, u32 *sr) { SETBYTE(*sr, move(src, *sr, 8, false)); }
void move_tosr_16(u32 src, u32 *sr) { SETWORD(*sr, move(src, *sr, 16, false)); }
void muls_toreg_16(u32 src, u32 *dst) {
  u32 res = (u32)(((s32)((s16)src)) * ((s32)((s16)*dst)));
  SET_FLAG_Z(res == 0);
  SET_FLAG_N(res >= 0x80000000);
  SET_FLAG_V(0);
  SET_FLAG_C(0);
  *dst = res;
}
void mulu_toreg_16(u32 src, u32 *dst) {
  u32 res = (u32)(((u16)src) * ((u16)*dst));
  SET_FLAG_Z(res == 0);
  SET_FLAG_N(res >= 0x80000000);
  SET_FLAG_V(0);
  SET_FLAG_C(0);
  *dst = res;
}
void neg_mem_16(u32 dst) {
  u32 src = 0;
  BINOP_TOMEM_16(neg);
}
void neg_mem_8(u32 dst) {
  u32 src = 0;
  BINOP_TOMEM_8(neg);
}
void neg_reg_16(u32 *dst) {
  u32 src = 0;
  BINOP_TOREG_16(neg);
}
void neg_reg_8(u32 *dst) {
  u32 src = 0;
  BINOP_TOREG_8(neg);
}
void not_mem_8(u32 dst) {
  u32 src = 0;
  BINOP_TOMEM_8(not );
}
void not_reg_16(u32 *dst) {
  u32 src = 0;
  BINOP_TOREG_16(not );
}
void not_reg_8(u32 *dst) {
  u32 src = 0;
  BINOP_TOREG_8(not );
}
void or_tomem_16(u32 src, u32 dst) { BINOP_TOMEM_16(or); }
void or_tomem_32(u32 src, u32 dst) { BINOP_TOMEM_32(or); }
void or_tomem_8(u32 src, u32 dst) { BINOP_TOMEM_8(or); }
void or_toreg_16(u32 src, u32 *dst) { BINOP_TOREG_16(or); }
void or_toreg_32(u32 src, u32 *dst) { BINOP_TOREG_32(or); }
void or_toreg_8(u32 src, u32 *dst) { BINOP_TOREG_8(or); }
void rol_toreg_16(u32 src, u32 *dst) { BINOP_TOREG_16(rol_16); }
void rol_toreg_32(u32 src, u32 *dst) { BINOP_TOREG_32(rol_32); }
void rol_toreg_8(u32 src, u32 *dst) { BINOP_TOREG_8(rol_8); }
void ror_toreg_16(u32 src, u32 *dst) { BINOP_TOREG_16(ror); }
void ror_toreg_32(u32 src, u32 *dst) { BINOP_TOREG_32(ror); }
void ror_toreg_8(u32 src, u32 *dst) { BINOP_TOREG_8(ror); }
void roxl_toreg_16(u32 src, u32 *dst) { BINOP_TOREG_16(roxl); }
void sub_tomem_16(u32 src, u32 dst) { BINOP_TOMEM_16(sub); }
void sub_tomem_32(u32 src, u32 dst) { BINOP_TOMEM_32(sub); }
void sub_tomem_8(u32 src, u32 dst) { BINOP_TOMEM_8(sub); }
void sub_toreg_16(u32 src, u32 *dst) { BINOP_TOREG_16(sub); }
void sub_toreg_32(u32 src, u32 *dst) { BINOP_TOREG_32(sub); }
void sub_toreg_8(u32 src, u32 *dst) { BINOP_TOREG_8(sub); }
/*void swap_reg_16(u32 *reg) {
  *reg = ((*reg << 16) | (*reg >> 16));
  SET_FLAG_N(*reg >= 0x80000000);
  SET_FLAG_Z(*reg == 0);
  SET_FLAG_V(0);
  SET_FLAG_C(0);
}*/
void tst_mem_16(u32 dst) { tst(0, read_16(dst), 16, true); }
void tst_mem_32(u32 dst) { tst(0, read_32(dst), 32, true); }
void tst_mem_8(u32 dst) { tst(0, read_8(dst), 8, true); }
void tst_reg_16(u32 *dst) { tst(0, *dst, 16, true); }
void tst_reg_32(u32 *dst) { tst(0, *dst, 32, true); }
void tst_reg_8(u32 *dst) { tst(0, *dst, 8, true); }