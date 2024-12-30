#pragma once
#include "system.h"
#define CCR_C (SR & 0x1)
#define CCR_V (SR & 0x2)
#define CCR_Z (SR & 0x4)
#define CCR_N (SR & 0x8)
#define CCR_X (SR & 0x10)
#define CCR_HI ((!CCR_C)&(!CCR_Z))
#define CCR_LS (CCR_C|CCR_Z)
#define CCR_CC (!CCR_C)
#define CCR_CS CCR_C
#define CCR_NE (!CCR_Z)
#define CCR_EQ CCR_Z
#define CCR_VC (!CCR_V)
#define CCR_VS CCR_V
#define CCR_PL (!CCR_N)
#define CCR_MI CCR_N
#define CCR_GE ((CCR_MI^CCR_VS)==0)
#define CCR_LT (!CCR_GE)
#define CCR_GT (CCR_GE&&CCR_NE)
#define CCR_LE (CCR_LT||CCR_EQ)
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
extern void swap_reg_16(u32 *dst);
extern void tst_mem_16(u32 dst);
extern void tst_mem_32(u32 dst);
extern void tst_mem_8(u32 dst);
extern void tst_reg_16(u32 *dst);
extern void tst_reg_32(u32 *dst);
extern void tst_reg_8(u32 *dst);