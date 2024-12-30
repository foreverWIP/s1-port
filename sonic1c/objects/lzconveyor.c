// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

static bool exit_early = false;

ROMFUNC(rom_12A10) {
  u8 switchindex = 0;
  exit_early = false;
  DEF_ROMLOC(12A10) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(12A12) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(12A16)
      : move_toreg_16(read_16(0x12A66 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	78(PC,D0),D1
  // DEF_ROMLOC(12A1A): rom_12A66 + (s16)(D1 & 0xffff)(); // JSR
  // 74(PC,D1)
  DEF_ROMLOC(12A1A) : switch (switchindex) {
  case 0:
    rom_12A6E();
    break;
  case 1:
    rom_12B86();
    break;
  case 2:
    rom_12B96();
    break;
  case 3:
    rom_12BB2();
    break;
  }
  if (exit_early)
    return;
  DEF_ROMLOC(12A1E)
      : move_toreg_16(read_16(A0 + 0x30), &D0);      // MOVE.W	48(A0),D0
  DEF_ROMLOC(12A22) : and_toreg_16(0xFFFFFF80, &D0); // ANDI.W	#$FF80,D0
  DEF_ROMLOC(12A26)
      : move_toreg_16(read_16(0xFFFFF700), &D1);     // MOVE.W	$F700,D1
  DEF_ROMLOC(12A2A) : sub_toreg_16(0x80, &D1);       // SUBI.W	#$0080,D1
  DEF_ROMLOC(12A2E) : and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
  DEF_ROMLOC(12A32) : sub_toreg_16(D1, &D0);         // SUB.W	D1,D0
  DEF_ROMLOC(12A34) : cmp_toreg_16(0x280, &D0);      // CMPI.W	#$0280,D0
  DEF_ROMLOC(12A38) : if (CCR_HI) goto rom_12A3E;    // BHI.B	$12A3E
  DEF_ROMLOC(12A3A) : rom_DC92();
  return;                                            // BRA.W	$DC92
  DEF_ROMLOC(12A3E) : cmp_tomem_8(0x2, 0xFFFFFE11);  // CMPI.B	#$02,$FE11
  DEF_ROMLOC(12A44) : if (!CCR_EQ) goto rom_12A4C;   // BNE.B	$12A4C
  DEF_ROMLOC(12A46) : cmp_toreg_16(0xFFFFFF80, &D0); // CMPI.W	#$FF80,D0
  DEF_ROMLOC(12A4A) : if (CCR_CC) goto rom_12A3A;    // BCC.B	$12A3A
  DEF_ROMLOC(12A4C)
      : move_toreg_8(read_8(A0 + 0x2F), &D0); // MOVE.B	47(A0),D0
  DEF_ROMLOC(12A50) : if (CCR_PL) {
    rom_DCCE();
    return;
  }                                                   // BPL.W	$DCCE
  DEF_ROMLOC(12A54) : and_toreg_16(0x7F, &D0);        // ANDI.W	#$007F,D0
  DEF_ROMLOC(12A58) : move_toreg_32(0xFFFFF7C1, &A2); // LEA.L	$F7C1,A2
  DEF_ROMLOC(12A5C)
      : bclr_tomem_8(0x0,
                     (s32)A2 + (s8)0x0 + (s16)D0); // BCLR.B	#$00,0(A2,D0)
  rom_DCCE();                                      // BRA.W	$DCCE
}
ROMFUNC(rom_12A6E) {
  DEF_ROMLOC(12A6E)
      : move_toreg_8(read_8(A0 + 0x28), &D0);      // MOVE.B	40(A0),D0
  DEF_ROMLOC(12A72) : if (CCR_MI) goto rom_12B34;  // BMI.W	$12B34
  DEF_ROMLOC(12A76) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(12A7A)
      : move_tomem_32(0x12D50, A0 + 0x4); // MOVE.L	#$00012D50,4(A0)
  DEF_ROMLOC(12A82) : move_tomem_16(0x43F6, A0 + 0x2); // MOVE.W
                                                       // #$43F6,2(A0)
  DEF_ROMLOC(12A88) : or_tomem_8(0x4, A0 + 0x1);       // ORI.B	#$04,1(A0)
  DEF_ROMLOC(12A8E) : move_tomem_8(0x10, A0 + 0x19);   // MOVE.B	#$10,25(A0)
  DEF_ROMLOC(12A94) : move_tomem_8(0x4, A0 + 0x18);    // MOVE.B	#$04,24(A0)
  DEF_ROMLOC(12A9A) : cmp_tomem_8(0x7F, A0 + 0x28);    // CMPI.B	#$7F,40(A0)
  DEF_ROMLOC(12AA0) : if (!CCR_EQ) goto rom_12AB6;     // BNE.B	$12AB6
  DEF_ROMLOC(12AA2) : add_tomem_8(0x4, A0 + 0x24);     // ADDQ.B	#$04,36(A0)
  DEF_ROMLOC(12AA6) : move_tomem_16(0x3F6, A0 + 0x2);  // MOVE.W	#$03F6,2(A0)
  DEF_ROMLOC(12AAC) : move_tomem_8(0x1, A0 + 0x18);    // MOVE.B	#$01,24(A0)
  rom_12BB2();
  return;                                           // BRA.W	$12BB2
  DEF_ROMLOC(12AB6) : move_tomem_8(0x4, A0 + 0x1A); // MOVE.B	#$04,26(A0)
  DEF_ROMLOC(12ABC) : move_toreg_32(0x0, &D0);      // MOVEQ.L	$00,D0
  DEF_ROMLOC(12ABE)
      : move_toreg_8(read_8(A0 + 0x28), &D0);      // MOVE.B	40(A0),D0
  DEF_ROMLOC(12AC2) : move_toreg_16(D0, &D1);      // MOVE.W	D0,D1
  DEF_ROMLOC(12AC4) : lsr_toreg_16(0x3, &D0);      // LSR.W	#$03,D0
  DEF_ROMLOC(12AC6) : and_toreg_16(0x1E, &D0);     // ANDI.W	#$001E,D0
  DEF_ROMLOC(12ACA) : move_toreg_32(0x12CBC, &A2); // LEA.L	496(PC),A2
  DEF_ROMLOC(12ACE)
      : add_toreg_16(read_16((s32)A2 + (s8)0x0 + (s16)D0),
                     &A2); // ADDA.W	0(A2,D0),A2
  DEF_ROMLOC(12AD2)
      : move_tomem_16(read_16((A2 += 2, A2 - 2)),
                      A0 + 0x38); // MOVE.W	(A2)+,56(A0)
  DEF_ROMLOC(12AD6)
      : move_tomem_16(read_16((A2 += 2, A2 - 2)),
                      A0 + 0x30);                   // MOVE.W	(A2)+,48(A0)
  DEF_ROMLOC(12ADA) : move_tomem_32(A2, A0 + 0x3C); // MOVE.L	A2,60(A0)
  DEF_ROMLOC(12ADE) : and_toreg_16(0xF, &D1);       // ANDI.W	#$000F,D1
  DEF_ROMLOC(12AE2) : lsl_toreg_16(0x2, &D1);       // LSL.W	#$02,D1
  DEF_ROMLOC(12AE4) : move_tomem_8(D1, A0 + 0x38);  // MOVE.B	D1,56(A0)
  DEF_ROMLOC(12AE8) : move_tomem_8(0x4, A0 + 0x3A); // MOVE.B	#$04,58(A0)
  DEF_ROMLOC(12AEE) : tst_mem_8(0xFFFFF7C0);        // TST.B	$F7C0
  DEF_ROMLOC(12AF2) : if (CCR_EQ) goto rom_12B20;   // BEQ.B	$12B20
  DEF_ROMLOC(12AF4) : move_tomem_8(0x1, A0 + 0x3B); // MOVE.B	#$01,59(A0)
  DEF_ROMLOC(12AFA) : neg_mem_8(A0 + 0x3A);         // NEG.B	58(A0)
  DEF_ROMLOC(12AFE) : move_toreg_32(0x0, &D1);      // MOVEQ.L	$00,D1
  DEF_ROMLOC(12B00)
      : move_toreg_8(read_8(A0 + 0x38), &D1); // MOVE.B	56(A0),D1
  DEF_ROMLOC(12B04)
      : add_toreg_8(read_8(A0 + 0x3A), &D1); // ADD.B	58(A0),D1
  DEF_ROMLOC(12B08)
      : cmp_toreg_8(read_8(A0 + 0x39), &D1);      // CMP.B	57(A0),D1
  DEF_ROMLOC(12B0C) : if (CCR_CS) goto rom_12B1C; // BCS.B	$12B1C
  DEF_ROMLOC(12B0E) : move_toreg_8(D1, &D0);      // MOVE.B	D1,D0
  DEF_ROMLOC(12B10) : move_toreg_32(0x0, &D1);    // MOVEQ.L	$00,D1
  DEF_ROMLOC(12B12) : tst_reg_8(&D0);             // TST.B	D0
  DEF_ROMLOC(12B14) : if (CCR_PL) goto rom_12B1C; // BPL.B	$12B1C
  DEF_ROMLOC(12B16)
      : move_toreg_8(read_8(A0 + 0x39), &D1);      // MOVE.B	57(A0),D1
  DEF_ROMLOC(12B1A) : sub_toreg_8(0x4, &D1);       // SUBQ.B	#$04,D1
  DEF_ROMLOC(12B1C) : move_tomem_8(D1, A0 + 0x38); // MOVE.B	D1,56(A0)
  DEF_ROMLOC(12B20)
      : move_tomem_16(read_16((s32)A2 + (s8)0x0 + (s16)D1),
                      A0 + 0x34); // MOVE.W	0(A2,D1),52(A0)
  DEF_ROMLOC(12B26)
      : move_tomem_16(read_16((s32)A2 + (s8)0x2 + (s16)D1),
                      A0 + 0x36);  // MOVE.W	2(A2,D1),54(A0)
  DEF_ROMLOC(12B2C) : rom_12C44(); // BSR.W	$12C44
  rom_12B86();
  return;                                             // BRA.W	$12B86
  DEF_ROMLOC(12B34) : move_tomem_8(D0, A0 + 0x2F);    // MOVE.B	D0,47(A0)
  DEF_ROMLOC(12B38) : and_toreg_16(0x7F, &D0);        // ANDI.W	#$007F,D0
  DEF_ROMLOC(12B3C) : move_toreg_32(0xFFFFF7C1, &A2); // LEA.L	$F7C1,A2
  DEF_ROMLOC(12B40)
      : bset_tomem_8(0x0,
                     (s32)A2 + (s8)0x0 + (s16)D0); // BSET.B	#$00,0(A2,D0)
  DEF_ROMLOC(12B46) : if (!CCR_EQ) {
    rom_DCCE();
    return;
  }                                                // BNE.W	$DCCE
  DEF_ROMLOC(12B4A) : add_toreg_16(D0, &D0);       // ADD.W	D0,D0
  DEF_ROMLOC(12B4C) : and_toreg_16(0x1E, &D0);     // ANDI.W	#$001E,D0
  DEF_ROMLOC(12B50) : add_toreg_16(0x70, &D0);     // ADDI.W	#$0070,D0
  DEF_ROMLOC(12B54) : move_toreg_32(0x6B000, &A2); // LEA.L	$0006B000,A2
  DEF_ROMLOC(12B5A)
      : add_toreg_16(read_16((s32)A2 + (s8)0x0 + (s16)D0),
                     &A2); // ADDA.W	0(A2,D0),A2
  DEF_ROMLOC(12B5E)
      : move_toreg_16(read_16((A2 += 2, A2 - 2)), &D1); // MOVE.W	(A2)+,D1
  DEF_ROMLOC(12B60) : move_toreg_32(A0, &A1);           // MOVEA.L	A0,A1
  goto rom_12B6A;                                       // BRA.B	$12B6A
  DEF_ROMLOC(12B64) : rom_E11A();                       // BSR.W	$E11A
  DEF_ROMLOC(12B68) : if (!CCR_EQ) goto rom_12B7E;      // BNE.B	$12B7E
  DEF_ROMLOC(12B6A) : move_tomem_8(0x63, A1 + 0x0);     // MOVE.B	#$63,0(A1)
  DEF_ROMLOC(12B70)
      : move_tomem_16(read_16((A2 += 2, A2 - 2)),
                      A1 + 0x8); // MOVE.W	(A2)+,8(A1)
  DEF_ROMLOC(12B74)
      : move_tomem_16(read_16((A2 += 2, A2 - 2)),
                      A1 + 0xC); // MOVE.W	(A2)+,12(A1)
  DEF_ROMLOC(12B78)
      : move_toreg_16(read_16((A2 += 2, A2 - 2)), &D0); // MOVE.W	(A2)+,D0
  DEF_ROMLOC(12B7A) : move_tomem_8(D0, A1 + 0x28);      // MOVE.B	D0,40(A1)
  DEF_ROMLOC(12B7E) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_12B64;                      // DBF.W	D1,$12B64
  DEF_ROMLOC(12B82) : exit_early = true; // TODO; // ADDQ.L	#$04,A7
  DEF_ROMLOC(12B84) : return;            // RTS
}
ROMFUNC(rom_12B86) {
  DEF_ROMLOC(12B86) : move_toreg_32(0x0, &D1); // MOVEQ.L	$00,D1
  DEF_ROMLOC(12B88)
      : move_toreg_8(read_8(A0 + 0x19), &D1); // MOVE.B	25(A0),D1
  DEF_ROMLOC(12B8C) : rom_7ACA();             // JSR	$00007ACA
  rom_12BD6();                                // BRA.W	$12BD6
}
ROMFUNC(rom_12B96) {
  DEF_ROMLOC(12B96) : move_toreg_32(0x0, &D1); // MOVEQ.L	$00,D1
  DEF_ROMLOC(12B98)
      : move_toreg_8(read_8(A0 + 0x19), &D1); // MOVE.B	25(A0),D1
  DEF_ROMLOC(12B9C) : rom_7C3E();             // JSR	$00007C3E
  DEF_ROMLOC(12BA2)
      : move_tomem_16(read_16(A0 + 0x8), A7 -= 2); // MOVE.W	8(A0),-(A7)
  DEF_ROMLOC(12BA6) : rom_12BD6();                 // BSR.W	$12BD6
  DEF_ROMLOC(12BAA)
      : move_toreg_16(read_16((A7 += 2, A7 - 2)), &D2); // MOVE.W	(A7)+,D2
  DEF_ROMLOC(12BAC) : {
    rom_81AC();
    return;
  } // JMP	$000081AC
}
ROMFUNC(rom_12BB2) {
  DEF_ROMLOC(12BB2)
      : move_toreg_16(read_16(0xFFFFFE04), &D0);   // MOVE.W	$FE04,D0
  DEF_ROMLOC(12BB6) : and_toreg_16(0x3, &D0);      // ANDI.W	#$0003,D0
  DEF_ROMLOC(12BBA) : if (!CCR_EQ) goto rom_12BD0; // BNE.B	$12BD0
  DEF_ROMLOC(12BBC) : move_toreg_32(0x1, &D1);     // MOVEQ.L	$01,D1
  DEF_ROMLOC(12BBE) : tst_mem_8(0xFFFFF7C0);       // TST.B	$F7C0
  DEF_ROMLOC(12BC2) : if (CCR_EQ) goto rom_12BC6;  // BEQ.B	$12BC6
  DEF_ROMLOC(12BC4) : neg_reg_8(&D1);              // NEG.B	D1
  DEF_ROMLOC(12BC6) : add_tomem_8(D1, A0 + 0x1A);  // ADD.B	D1,26(A0)
  DEF_ROMLOC(12BCA) : and_tomem_8(0x3, A0 + 0x1A); // ANDI.B	#$03,26(A0)
  DEF_ROMLOC(12BD0) : exit_early = true;           // TODO; // ADDQ.L	#$04,A7
  rom_FD38();                                      // BRA.W	$FD38
}
ROMFUNC(rom_12BD6) {
  DEF_ROMLOC(12BD6) : tst_mem_8(0xFFFFF7EE);         // TST.B	$F7EE
  DEF_ROMLOC(12BDA) : if (CCR_EQ) goto rom_12BF4;    // BEQ.B	$12BF4
  DEF_ROMLOC(12BDC) : tst_mem_8(A0 + 0x3B);          // TST.B	59(A0)
  DEF_ROMLOC(12BE0) : if (!CCR_EQ) goto rom_12BF4;   // BNE.B	$12BF4
  DEF_ROMLOC(12BE2) : move_tomem_8(0x1, A0 + 0x3B);  // MOVE.B	#$01,59(A0)
  DEF_ROMLOC(12BE8) : move_tomem_8(0x1, 0xFFFFF7C0); // MOVE.B	#$01,$F7C0
  DEF_ROMLOC(12BEE) : neg_mem_8(A0 + 0x3A);          // NEG.B	58(A0)
  goto rom_12C08;                                    // BRA.B	$12C08
  DEF_ROMLOC(12BF4)
      : move_toreg_16(read_16(A0 + 0x8), &D0); // MOVE.W	8(A0),D0
  DEF_ROMLOC(12BF8)
      : cmp_toreg_16(read_16(A0 + 0x34), &D0);     // CMP.W	52(A0),D0
  DEF_ROMLOC(12BFC) : if (!CCR_EQ) goto rom_12C3E; // BNE.B	$12C3E
  DEF_ROMLOC(12BFE)
      : move_toreg_16(read_16(A0 + 0xC), &D0); // MOVE.W	12(A0),D0
  DEF_ROMLOC(12C02)
      : cmp_toreg_16(read_16(A0 + 0x36), &D0);     // CMP.W	54(A0),D0
  DEF_ROMLOC(12C06) : if (!CCR_EQ) goto rom_12C3E; // BNE.B	$12C3E
  DEF_ROMLOC(12C08) : move_toreg_32(0x0, &D1);     // MOVEQ.L	$00,D1
  DEF_ROMLOC(12C0A)
      : move_toreg_8(read_8(A0 + 0x38), &D1); // MOVE.B	56(A0),D1
  DEF_ROMLOC(12C0E)
      : add_toreg_8(read_8(A0 + 0x3A), &D1); // ADD.B	58(A0),D1
  DEF_ROMLOC(12C12)
      : cmp_toreg_8(read_8(A0 + 0x39), &D1);      // CMP.B	57(A0),D1
  DEF_ROMLOC(12C16) : if (CCR_CS) goto rom_12C26; // BCS.B	$12C26
  DEF_ROMLOC(12C18) : move_toreg_8(D1, &D0);      // MOVE.B	D1,D0
  DEF_ROMLOC(12C1A) : move_toreg_32(0x0, &D1);    // MOVEQ.L	$00,D1
  DEF_ROMLOC(12C1C) : tst_reg_8(&D0);             // TST.B	D0
  DEF_ROMLOC(12C1E) : if (CCR_PL) goto rom_12C26; // BPL.B	$12C26
  DEF_ROMLOC(12C20)
      : move_toreg_8(read_8(A0 + 0x39), &D1);      // MOVE.B	57(A0),D1
  DEF_ROMLOC(12C24) : sub_toreg_8(0x4, &D1);       // SUBQ.B	#$04,D1
  DEF_ROMLOC(12C26) : move_tomem_8(D1, A0 + 0x38); // MOVE.B	D1,56(A0)
  DEF_ROMLOC(12C2A)
      : move_toreg_32(read_32(A0 + 0x3C), &A1); // MOVEA.L	60(A0),A1
  DEF_ROMLOC(12C2E)
      : move_tomem_16(read_16((s32)A1 + (s8)0x0 + (s16)D1),
                      A0 + 0x34); // MOVE.W	0(A1,D1),52(A0)
  DEF_ROMLOC(12C34)
      : move_tomem_16(read_16((s32)A1 + (s8)0x2 + (s16)D1),
                      A0 + 0x36);  // MOVE.W	2(A1,D1),54(A0)
  DEF_ROMLOC(12C3A) : rom_12C44(); // BSR.W	$12C44
  DEF_ROMLOC(12C3E) : rom_DC6C();  // BSR.W	$DC6C
  DEF_ROMLOC(12C42) : return;      // RTS
}
ROMFUNC(rom_12C44) {
  DEF_ROMLOC(12C44) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(12C46) : move_toreg_16(0xFFFFFF00, &D2); // MOVE.W	#$FF00,D2
  DEF_ROMLOC(12C4A)
      : move_toreg_16(read_16(A0 + 0x8), &D0); // MOVE.W	8(A0),D0
  DEF_ROMLOC(12C4E)
      : sub_toreg_16(read_16(A0 + 0x34), &D0);        // SUB.W	52(A0),D0
  DEF_ROMLOC(12C52) : if (CCR_CC) goto rom_12C58;     // BCC.B	$12C58
  DEF_ROMLOC(12C54) : neg_reg_16(&D0);                // NEG.W	D0
  DEF_ROMLOC(12C56) : neg_reg_16(&D2);                // NEG.W	D2
  DEF_ROMLOC(12C58) : move_toreg_32(0x0, &D1);        // MOVEQ.L	$00,D1
  DEF_ROMLOC(12C5A) : move_toreg_16(0xFFFFFF00, &D3); // MOVE.W	#$FF00,D3
  DEF_ROMLOC(12C5E)
      : move_toreg_16(read_16(A0 + 0xC), &D1); // MOVE.W	12(A0),D1
  DEF_ROMLOC(12C62)
      : sub_toreg_16(read_16(A0 + 0x36), &D1);    // SUB.W	54(A0),D1
  DEF_ROMLOC(12C66) : if (CCR_CC) goto rom_12C6C; // BCC.B	$12C6C
  DEF_ROMLOC(12C68) : neg_reg_16(&D1);            // NEG.W	D1
  DEF_ROMLOC(12C6A) : neg_reg_16(&D3);            // NEG.W	D3
  DEF_ROMLOC(12C6C) : cmp_toreg_16(D0, &D1);      // CMP.W	D0,D1
  DEF_ROMLOC(12C6E) : if (CCR_CS) goto rom_12C96; // BCS.B	$12C96
  DEF_ROMLOC(12C70)
      : move_toreg_16(read_16(A0 + 0x8), &D0); // MOVE.W	8(A0),D0
  DEF_ROMLOC(12C74)
      : sub_toreg_16(read_16(A0 + 0x34), &D0);      // SUB.W	52(A0),D0
  DEF_ROMLOC(12C78) : if (CCR_EQ) goto rom_12C82;   // BEQ.B	$12C82
  DEF_ROMLOC(12C7A) : ext_reg_32(&D0);              // EXT.L	D0
  DEF_ROMLOC(12C7C) : asl_toreg_32(0x8, &D0);       // ASL.L	#$08,D0
  DEF_ROMLOC(12C7E) : divs_toreg_16(D1, &D0);       // DIVS.W	D1,D0
  DEF_ROMLOC(12C80) : neg_reg_16(&D0);              // NEG.W	D0
  DEF_ROMLOC(12C82) : move_tomem_16(D0, A0 + 0x10); // MOVE.W	D0,16(A0)
  DEF_ROMLOC(12C86) : move_tomem_16(D3, A0 + 0x12); // MOVE.W	D3,18(A0)
  DEF_ROMLOC(12C8A) : swap_reg_16(&D0);             // SWAP.W	D0
  DEF_ROMLOC(12C8C) : move_tomem_16(D0, A0 + 0xA);  // MOVE.W	D0,10(A0)
  DEF_ROMLOC(12C90) : clr_mem_16(A0 + 0xE);         // CLR.W	14(A0)
  DEF_ROMLOC(12C94) : return;                       // RTS
  DEF_ROMLOC(12C96)
      : move_toreg_16(read_16(A0 + 0xC), &D1); // MOVE.W	12(A0),D1
  DEF_ROMLOC(12C9A)
      : sub_toreg_16(read_16(A0 + 0x36), &D1);      // SUB.W	54(A0),D1
  DEF_ROMLOC(12C9E) : if (CCR_EQ) goto rom_12CA8;   // BEQ.B	$12CA8
  DEF_ROMLOC(12CA0) : ext_reg_32(&D1);              // EXT.L	D1
  DEF_ROMLOC(12CA2) : asl_toreg_32(0x8, &D1);       // ASL.L	#$08,D1
  DEF_ROMLOC(12CA4) : divs_toreg_16(D0, &D1);       // DIVS.W	D0,D1
  DEF_ROMLOC(12CA6) : neg_reg_16(&D1);              // NEG.W	D1
  DEF_ROMLOC(12CA8) : move_tomem_16(D1, A0 + 0x12); // MOVE.W	D1,18(A0)
  DEF_ROMLOC(12CAC) : move_tomem_16(D2, A0 + 0x10); // MOVE.W	D2,16(A0)
  DEF_ROMLOC(12CB0) : swap_reg_16(&D1);             // SWAP.W	D1
  DEF_ROMLOC(12CB2) : move_tomem_16(D1, A0 + 0xE);  // MOVE.W	D1,14(A0)
  DEF_ROMLOC(12CB6) : clr_mem_16(A0 + 0xA);         // CLR.W	10(A0)
  DEF_ROMLOC(12CBA) : return;                       // RTS
}