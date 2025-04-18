// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

static bool return_early = false;

ROMFUNC(rom_169D2) {
  u8 switchindex = 0;
  return_early = false;
  DEF_ROMLOC(169D2) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(169D4) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(169D8)
      : move_toreg_16(read_16(0x16A2A + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	80(PC,D0),D1
  // DEF_ROMLOC(169DC): rom_16A2A + (s16)(D1 & 0xffff)(); // JSR
  // 76(PC,D1)
  DEF_ROMLOC(169DC) : switch (switchindex) {
  case 0:
    rom_16A2E();
    break;
  case 1:
    rom_16B40();
    break;
  }
  if (return_early)
    return;
  DEF_ROMLOC(169E0)
      : move_toreg_16(read_16(A0 + 0x30), &D0);      // MOVE.W	48(A0),D0
  DEF_ROMLOC(169E4) : and_toreg_16(0xFFFFFF80, &D0); // ANDI.W	#$FF80,D0
  DEF_ROMLOC(169E8)
      : move_toreg_16(read_16(v_screenposx), &D1);   // MOVE.W	$F700,D1
  DEF_ROMLOC(169EC) : sub_toreg_16(0x80, &D1);       // SUBI.W	#$0080,D1
  DEF_ROMLOC(169F0) : and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
  DEF_ROMLOC(169F4) : sub_toreg_16(D1, &D0);         // SUB.W	D1,D0
  DEF_ROMLOC(169F6)
      : cmp_toreg_16(128 + GAME_WIDTH + 192, &D0); // CMPI.W	#$0280,D0
  DEF_ROMLOC(169FA) : if (CCR_HI) goto rom_16A02;  // BHI.B	$16A02
  DEF_ROMLOC(169FC) : queue_sprite();
  return;                                            // JMP	$0000DC92
  DEF_ROMLOC(16A02) : cmp_tomem_8(0x2, v_act);       // CMPI.B	#$02,$FE11
  DEF_ROMLOC(16A08) : if (!CCR_EQ) goto rom_16A10;   // BNE.B	$16A10
  DEF_ROMLOC(16A0A) : cmp_toreg_16(0xFFFFFF80, &D0); // CMPI.W	#$FF80,D0
  DEF_ROMLOC(16A0E) : if (CCR_CC) goto rom_169FC;    // BCC.B	$169FC
  DEF_ROMLOC(16A10)
      : move_toreg_8(read_8(A0 + 0x2F), &D0);         // MOVE.B
                                                      // 47(A0),D0
  DEF_ROMLOC(16A14) : if (CCR_PL) goto rom_16A24;     // BPL.B	$16A24
  DEF_ROMLOC(16A16) : and_toreg_16(0x7F, &D0);        // ANDI.W	#$007F,D0
  DEF_ROMLOC(16A1A) : move_toreg_32(0xFFFFF7C1, &A2); // LEA.L	$F7C1,A2
  DEF_ROMLOC(16A1E)
      : bclr_tomem_8(0x0,
                     (s32)A2 + (s8)0x0 + (s16)D0); // BCLR.B	#$00,0(A2,D0)
  DEF_ROMLOC(16A24) : rom_DCCE();
  return; // JMP	$0000DCCE
}
ROMFUNC(rom_16A2E) {
  DEF_ROMLOC(16A2E)
      : move_toreg_8(read_8(A0 + 0x28), &D0);      // MOVE.B	40(A0),D0
  DEF_ROMLOC(16A32) : if (CCR_MI) goto rom_16AE8;  // BMI.W	$16AE8
  DEF_ROMLOC(16A36) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(16A3A)
      : move_tomem_32(0x160A2, A0 + 0x4);             // MOVE.L	#$000160A2,4(A0)
  DEF_ROMLOC(16A42) : move_tomem_16(0x4DF, A0 + 0x2); // MOVE.W	#$04DF,2(A0)
  DEF_ROMLOC(16A48) : move_tomem_8(0x10, A0 + 0x19);  // MOVE.B	#$10,25(A0)
  DEF_ROMLOC(16A4E) : or_tomem_8(0x4, A0 + 0x1);      // ORI.B	#$04,1(A0)
  DEF_ROMLOC(16A54) : move_tomem_8(0x4, A0 + 0x18);   // MOVE.B	#$04,24(A0)
  DEF_ROMLOC(16A5A) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(16A5C)
      : move_toreg_8(read_8(A0 + 0x28), &D0);      // MOVE.B	40(A0),D0
  DEF_ROMLOC(16A60) : move_toreg_16(D0, &D1);      // MOVE.W	D0,D1
  DEF_ROMLOC(16A62) : lsr_toreg_16(0x3, &D0);      // LSR.W	#$03,D0
  DEF_ROMLOC(16A64) : and_toreg_16(0x1E, &D0);     // ANDI.W	#$001E,D0
  DEF_ROMLOC(16A68) : move_toreg_32(0x16C0E, &A2); // LEA.L	420(PC),A2
  DEF_ROMLOC(16A6C)
      : add_toreg_16(read_16((s32)A2 + (s8)0x0 + (s16)D0),
                     &A2); // ADDA.W	0(A2,D0),A2
  DEF_ROMLOC(16A70)
      : move_tomem_16(read_16((A2 += 2, A2 - 2)),
                      A0 + 0x38); // MOVE.W	(A2)+,56(A0)
  DEF_ROMLOC(16A74)
      : move_tomem_16(read_16((A2 += 2, A2 - 2)),
                      A0 + 0x30);                   // MOVE.W	(A2)+,48(A0)
  DEF_ROMLOC(16A78) : move_tomem_32(A2, A0 + 0x3C); // MOVE.L	A2,60(A0)
  DEF_ROMLOC(16A7C) : and_toreg_16(0xF, &D1);       // ANDI.W	#$000F,D1
  DEF_ROMLOC(16A80) : lsl_toreg_16(0x2, &D1);       // LSL.W	#$02,D1
  DEF_ROMLOC(16A82) : move_tomem_8(D1, A0 + 0x38);  // MOVE.B	D1,56(A0)
  DEF_ROMLOC(16A86) : move_tomem_8(0x4, A0 + 0x3A); // MOVE.B	#$04,58(A0)
  DEF_ROMLOC(16A8C) : tst_mem_8(0xFFFFF7C0);        // TST.B	$F7C0
  DEF_ROMLOC(16A90) : if (CCR_EQ) goto rom_16ABE;   // BEQ.B	$16ABE
  DEF_ROMLOC(16A92) : move_tomem_8(0x1, A0 + 0x3B); // MOVE.B	#$01,59(A0)
  DEF_ROMLOC(16A98) : neg_mem_8(A0 + 0x3A);         // NEG.B	58(A0)
  DEF_ROMLOC(16A9C) : move_toreg_32(0x0, &D1);      // MOVEQ.L	$00,D1
  DEF_ROMLOC(16A9E)
      : move_toreg_8(read_8(A0 + 0x38), &D1); // MOVE.B
                                              // 56(A0),D1
  DEF_ROMLOC(16AA2)
      : add_toreg_8(read_8(A0 + 0x3A), &D1); // ADD.B
                                             // 58(A0),D1
  DEF_ROMLOC(16AA6)
      : cmp_toreg_8(read_8(A0 + 0x39), &D1);      // CMP.B	57(A0),D1
  DEF_ROMLOC(16AAA) : if (CCR_CS) goto rom_16ABA; // BCS.B	$16ABA
  DEF_ROMLOC(16AAC) : move_toreg_8(D1, &D0);      // MOVE.B	D1,D0
  DEF_ROMLOC(16AAE) : move_toreg_32(0x0, &D1);    // MOVEQ.L	$00,D1
  DEF_ROMLOC(16AB0) : tst_reg_8(&D0);             // TST.B	D0
  DEF_ROMLOC(16AB2) : if (CCR_PL) goto rom_16ABA; // BPL.B	$16ABA
  DEF_ROMLOC(16AB4)
      : move_toreg_8(read_8(A0 + 0x39), &D1);      // MOVE.B	57(A0),D1
  DEF_ROMLOC(16AB8) : sub_toreg_8(0x4, &D1);       // SUBQ.B	#$04,D1
  DEF_ROMLOC(16ABA) : move_tomem_8(D1, A0 + 0x38); // MOVE.B	D1,56(A0)
  DEF_ROMLOC(16ABE)
      : move_tomem_16(read_16((s32)A2 + (s8)0x0 + (s16)D1),
                      A0 + 0x34); // MOVE.W	0(A2,D1),52(A0)
  DEF_ROMLOC(16AC4)
      : move_tomem_16(read_16((s32)A2 + (s8)0x2 + (s16)D1),
                      A0 + 0x36);                   // MOVE.W	2(A2,D1),54(A0)
  DEF_ROMLOC(16ACA) : tst_reg_16(&D1);              // TST.W	D1
  DEF_ROMLOC(16ACC) : if (!CCR_EQ) goto rom_16AD4;  // BNE.B	$16AD4
  DEF_ROMLOC(16ACE) : move_tomem_8(0x1, A0 + 0x1C); // MOVE.B	#$01,28(A0)
  DEF_ROMLOC(16AD4) : cmp_toreg_16(0x8, &D1);       // CMPI.W	#$0008,D1
  DEF_ROMLOC(16AD8) : if (!CCR_EQ) goto rom_16AE0;  // BNE.B	$16AE0
  DEF_ROMLOC(16ADA) : move_tomem_8(0x0, A0 + 0x1C); // MOVE.B	#$00,28(A0)
  DEF_ROMLOC(16AE0) : rom_12C44();                  // BSR.W	$12C44
  rom_16B40();
  return;                                             // BRA.W	$16B40
  DEF_ROMLOC(16AE8) : move_tomem_8(D0, A0 + 0x2F);    // MOVE.B	D0,47(A0)
  DEF_ROMLOC(16AEC) : and_toreg_16(0x7F, &D0);        // ANDI.W	#$007F,D0
  DEF_ROMLOC(16AF0) : move_toreg_32(0xFFFFF7C1, &A2); // LEA.L	$F7C1,A2
  DEF_ROMLOC(16AF4)
      : bset_tomem_8(0x0,
                     (s32)A2 + (s8)0x0 + (s16)D0); // BSET.B	#$00,0(A2,D0)
  DEF_ROMLOC(16AFA) : if (CCR_EQ) goto rom_16B02;  // BEQ.B	$16B02
  DEF_ROMLOC(16AFC) : rom_DCCE();
  return;                                          // JMP	$0000DCCE
  DEF_ROMLOC(16B02) : add_toreg_16(D0, &D0);       // ADD.W	D0,D0
  DEF_ROMLOC(16B04) : and_toreg_16(0x1E, &D0);     // ANDI.W	#$001E,D0
  DEF_ROMLOC(16B08) : add_toreg_16(0x80, &D0);     // ADDI.W	#$0080,D0
  DEF_ROMLOC(16B0C) : move_toreg_32(0x6B000, &A2); // LEA.L	$0006B000,A2
  DEF_ROMLOC(16B12)
      : add_toreg_16(read_16((s32)A2 + (s8)0x0 + (s16)D0),
                     &A2); // ADDA.W	0(A2,D0),A2
  DEF_ROMLOC(16B16)
      : move_toreg_16(read_16((A2 += 2, A2 - 2)), &D1); // MOVE.W	(A2)+,D1
  DEF_ROMLOC(16B18) : move_toreg_32(A0, &A1);           // MOVEA.L	A0,A1
  goto rom_16B24;                                       // BRA.B	$16B24
  DEF_ROMLOC(16B1C) : rom_E11A();                       // JSR	$0000E11A
  DEF_ROMLOC(16B22) : if (!CCR_EQ) goto rom_16B38;      // BNE.B	$16B38
  DEF_ROMLOC(16B24)
      : move_tomem_8(OBJ_SPINCONVEY,
                     A1 + offsetof(object, id)); // MOVE.B	#$6F,0(A1)
  DEF_ROMLOC(16B2A)
      : move_tomem_16(read_16((A2 += 2, A2 - 2)),
                      A1 + 0x8); // MOVE.W	(A2)+,8(A1)
  DEF_ROMLOC(16B2E)
      : move_tomem_16(read_16((A2 += 2, A2 - 2)),
                      A1 + 0xC); // MOVE.W	(A2)+,12(A1)
  DEF_ROMLOC(16B32)
      : move_toreg_16(read_16((A2 += 2, A2 - 2)), &D0); // MOVE.W	(A2)+,D0
  DEF_ROMLOC(16B34) : move_tomem_8(D0, A1 + 0x28);      // MOVE.B	D0,40(A1)
  DEF_ROMLOC(16B38) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_16B1C;                        // DBF.W	D1,$16B1C
  DEF_ROMLOC(16B3C) : return_early = true; // TODO; // ADDQ.L	#$04,A7
  DEF_ROMLOC(16B3E) : return;              // RTS
}
ROMFUNC(rom_16B8C) {
  DEF_ROMLOC(16B8C)
      : move_toreg_16(read_16(A0 + 0x8), &D0); // MOVE.W	8(A0),D0
  DEF_ROMLOC(16B90)
      : cmp_toreg_16(read_16(A0 + 0x34), &D0);     // CMP.W	52(A0),D0
  DEF_ROMLOC(16B94) : if (!CCR_EQ) goto rom_16BEC; // BNE.B	$16BEC
  DEF_ROMLOC(16B96)
      : move_toreg_16(read_16(A0 + 0xC), &D0); // MOVE.W	12(A0),D0
  DEF_ROMLOC(16B9A)
      : cmp_toreg_16(read_16(A0 + 0x36), &D0);     // CMP.W	54(A0),D0
  DEF_ROMLOC(16B9E) : if (!CCR_EQ) goto rom_16BEC; // BNE.B	$16BEC
  DEF_ROMLOC(16BA0) : move_toreg_32(0x0, &D1);     // MOVEQ.L	$00,D1
  DEF_ROMLOC(16BA2)
      : move_toreg_8(read_8(A0 + 0x38), &D1); // MOVE.B
                                              // 56(A0),D1
  DEF_ROMLOC(16BA6)
      : add_toreg_8(read_8(A0 + 0x3A), &D1); // ADD.B
                                             // 58(A0),D1
  DEF_ROMLOC(16BAA)
      : cmp_toreg_8(read_8(A0 + 0x39), &D1);      // CMP.B	57(A0),D1
  DEF_ROMLOC(16BAE) : if (CCR_CS) goto rom_16BBE; // BCS.B	$16BBE
  DEF_ROMLOC(16BB0) : move_toreg_8(D1, &D0);      // MOVE.B	D1,D0
  DEF_ROMLOC(16BB2) : move_toreg_32(0x0, &D1);    // MOVEQ.L	$00,D1
  DEF_ROMLOC(16BB4) : tst_reg_8(&D0);             // TST.B	D0
  DEF_ROMLOC(16BB6) : if (CCR_PL) goto rom_16BBE; // BPL.B	$16BBE
  DEF_ROMLOC(16BB8)
      : move_toreg_8(read_8(A0 + 0x39), &D1);      // MOVE.B	57(A0),D1
  DEF_ROMLOC(16BBC) : sub_toreg_8(0x4, &D1);       // SUBQ.B	#$04,D1
  DEF_ROMLOC(16BBE) : move_tomem_8(D1, A0 + 0x38); // MOVE.B	D1,56(A0)
  DEF_ROMLOC(16BC2)
      : move_toreg_32(read_32(A0 + 0x3C), &A1); // MOVEA.L	60(A0),A1
  DEF_ROMLOC(16BC6)
      : move_tomem_16(read_16((s32)A1 + (s8)0x0 + (s16)D1),
                      A0 + 0x34); // MOVE.W	0(A1,D1),52(A0)
  DEF_ROMLOC(16BCC)
      : move_tomem_16(read_16((s32)A1 + (s8)0x2 + (s16)D1),
                      A0 + 0x36);                   // MOVE.W	2(A1,D1),54(A0)
  DEF_ROMLOC(16BD2) : tst_reg_16(&D1);              // TST.W	D1
  DEF_ROMLOC(16BD4) : if (!CCR_EQ) goto rom_16BDC;  // BNE.B	$16BDC
  DEF_ROMLOC(16BD6) : move_tomem_8(0x1, A0 + 0x1C); // MOVE.B	#$01,28(A0)
  DEF_ROMLOC(16BDC) : cmp_toreg_16(0x8, &D1);       // CMPI.W	#$0008,D1
  DEF_ROMLOC(16BE0) : if (!CCR_EQ) goto rom_16BE8;  // BNE.B	$16BE8
  DEF_ROMLOC(16BE2) : move_tomem_8(0x0, A0 + 0x1C); // MOVE.B	#$00,28(A0)
  DEF_ROMLOC(16BE8) : rom_12C44();                  // BSR.W	$12C44
  DEF_ROMLOC(16BEC) : rom_DC6C();
  return; // JMP	$0000DC6C
}
ROMFUNC(rom_16B40) {
  DEF_ROMLOC(16B40) : move_toreg_32(0x16BF2, &A1); // LEA.L	$00016BF2,A1
  DEF_ROMLOC(16B46) : animate_sprite();            // JSR	$0000ADA2
  DEF_ROMLOC(16B4C) : tst_mem_8(A0 + 0x1A);        // TST.B	26(A0)
  DEF_ROMLOC(16B50) : if (!CCR_EQ) goto rom_16B6C; // BNE.B	$16B6C
  DEF_ROMLOC(16B52)
      : move_tomem_16(read_16(A0 + 0x8), A7 -= 2); // MOVE.W	8(A0),-(A7)
  DEF_ROMLOC(16B56) : rom_16B8C();                 // BSR.W	$16B8C
  DEF_ROMLOC(16B5A) : move_toreg_16(0x1B, &D1);    // MOVE.W	#$001B,D1
  DEF_ROMLOC(16B5E) : move_toreg_16(0x7, &D2);     // MOVE.W	#$0007,D2
  DEF_ROMLOC(16B62) : move_toreg_16(D2, &D3);      // MOVE.W	D2,D3
  DEF_ROMLOC(16B64) : add_toreg_16(0x1, &D3);      // ADDQ.W	#$01,D3
  DEF_ROMLOC(16B66)
      : move_toreg_16(read_16((A7 += 2, A7 - 2)), &D4); // MOVE.W	(A7)+,D4
  rom_10062();
  return;                                             // BRA.W	$10062
  DEF_ROMLOC(16B6C) : btst_tomem_8(0x3, A0 + 0x22);   // BTST.B	#$03,34(A0)
  DEF_ROMLOC(16B72) : if (CCR_EQ) goto rom_16B88;     // BEQ.B	$16B88
  DEF_ROMLOC(16B74) : move_toreg_32(0xFFFFD000, &A1); // LEA.L	$D000,A1
  DEF_ROMLOC(16B78) : bclr_tomem_8(0x3, A1 + 0x22);   // BCLR.B	#$03,34(A1)
  DEF_ROMLOC(16B7E) : bclr_tomem_8(0x3, A0 + 0x22);   // BCLR.B	#$03,34(A0)
  DEF_ROMLOC(16B84) : clr_mem_8(A0 + 0x25);           // CLR.B	37(A0)
  DEF_ROMLOC(16B88) : rom_16B8C();
  return; // BRA.W	$16B8C
}