// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_1ABFE) {
  DEF_ROMLOC(1ABFE) : rom_DCCE();
  return; // JMP	$0000DCCE
}
ROMFUNC(rom_1AC04) {
  u8 switchindex = 0;
  DEF_ROMLOC(1AC04) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(1AC06) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(1AC0A)
      : move_toreg_16(read_16(0x1AC12 + (s16)(D0 & 0xffff)),
                      &D0); // MOVE.W	6(PC,D0),D0
  // DEF_ROMLOC(1AC0E): goto rom_1AC12 + (s16)(D0 & 0xffff); // JMP	2(PC,D0)
  DEF_ROMLOC(1AC0E) : switch (switchindex) {
  case 0:
    rom_1AC28();
    break;
  case 1:
    rom_1AC84();
    break;
  case 2:
    rom_1AD34();
    break;
  }
}
ROMFUNC(rom_1AC28) {
  DEF_ROMLOC(1AC28) : move_toreg_32(0x1AC18, &A1);          // LEA.L	-18(PC),A1
  DEF_ROMLOC(1AC2C) : move_toreg_32(0x0, &D0);              // MOVEQ.L	$00,D0
  DEF_ROMLOC(1AC2E) : move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B
                                                            // 40(A0),D0
  DEF_ROMLOC(1AC32) : add_toreg_16(D0, &D0);                // ADD.W	D0,D0
  DEF_ROMLOC(1AC34) : add_toreg_16(D0, &A1);                // ADDA.W	D0,A1
  DEF_ROMLOC(1AC36) : move_tomem_8(0x4, A0 + 0x1);          // MOVE.B	#$04,1(A0)
  DEF_ROMLOC(1AC3C) : bset_tomem_8(0x7, A0 + 0x1);          // BSET.B	#$07,1(A0)
  DEF_ROMLOC(1AC42) : bset_tomem_8(0x4, A0 + 0x1);          // BSET.B	#$04,1(A0)
  DEF_ROMLOC(1AC48) : move_tomem_16(0x300, A0 + 0x2); // MOVE.W	#$0300,2(A0)
  DEF_ROMLOC(1AC4E)
      : move_tomem_32(0x1AE2C, A0 + 0x4); // MOVE.L	#$0001AE2C,4(A0)
  DEF_ROMLOC(1AC56)
      : move_tomem_16(read_16((A1 += 2, A1 - 2)),
                      A0 + 0x8); // MOVE.W	(A1)+,8(A0)
  DEF_ROMLOC(1AC5A)
      : move_tomem_16(read_16(A1), A0 + 0xC); // MOVE.W	(A1),12(A0)
  DEF_ROMLOC(1AC5E)
      : move_tomem_16(read_16((A1 += 2, A1 - 2)),
                      A0 + 0x38);                    // MOVE.W	(A1)+,56(A0)
  DEF_ROMLOC(1AC62) : move_tomem_8(0x20, A0 + 0x16); // MOVE.B	#$20,22(A0)
  DEF_ROMLOC(1AC68) : move_tomem_8(0x60, A0 + 0x17); // MOVE.B	#$60,23(A0)
  DEF_ROMLOC(1AC6E) : move_tomem_8(0x20, A0 + 0x19); // MOVE.B	#$20,25(A0)
  DEF_ROMLOC(1AC74) : move_tomem_8(0x60, A0 + 0x16); // MOVE.B	#$60,22(A0)
  DEF_ROMLOC(1AC7A) : move_tomem_8(0x3, A0 + 0x18);  // MOVE.B	#$03,24(A0)
  DEF_ROMLOC(1AC80) : add_tomem_8(0x2, A0 + 0x24);   // ADDQ.B	#$02,36(A0)
  rom_1AC84(); // Detected flow into next function
}
ROMFUNC(rom_1AC84) {
  DEF_ROMLOC(1AC84) : cmp_tomem_8(0x2, A0 + 0x28); // CMPI.B	#$02,40(A0)
  DEF_ROMLOC(1AC8A) : if (CCR_LE) goto rom_1AC92;  // BLE.B	$1AC92
  DEF_ROMLOC(1AC8C) : bset_tomem_8(0x1, A0 + 0x1); // BSET.B	#$01,1(A0)
  DEF_ROMLOC(1AC92) : clr_mem_32(A0 + 0x3C);       // CLR.L	60(A0)
  DEF_ROMLOC(1AC96) : tst_mem_8(A0 + 0x29);        // TST.B	41(A0)
  DEF_ROMLOC(1AC9A) : if (CCR_EQ) {
    rom_1ACA0();
    return;
  }                                                // BEQ.B	$1ACA0
  DEF_ROMLOC(1AC9C) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  rom_1ACA0();
}
ROMFUNC(rom_1ACA0) {
  DEF_ROMLOC(1ACA0)
      : move_toreg_32(read_32(A0 + 0x3C), &D0); // MOVE.L	60(A0),D0
  DEF_ROMLOC(1ACA4)
      : move_toreg_32(read_32(A0 + 0x38), &D1);       // MOVE.L	56(A0),D1
  DEF_ROMLOC(1ACA8) : add_toreg_32(D0, &D1);          // ADD.L	D0,D1
  DEF_ROMLOC(1ACAA) : SWAPWORDS(D1);                  // SWAP.W	D1
  DEF_ROMLOC(1ACAC) : move_tomem_16(D1, A0 + 0xC);    // MOVE.W	D1,12(A0)
  DEF_ROMLOC(1ACB0) : cmp_tomem_8(0x4, A0 + 0x24);    // CMPI.B	#$04,36(A0)
  DEF_ROMLOC(1ACB6) : if (!CCR_EQ) goto rom_1ACDA;    // BNE.B	$1ACDA
  DEF_ROMLOC(1ACB8) : tst_mem_16(A0 + 0x30);          // TST.W	48(A0)
  DEF_ROMLOC(1ACBC) : if (CCR_PL) goto rom_1ACDA;     // BPL.B	$1ACDA
  DEF_ROMLOC(1ACBE) : move_toreg_32(0xFFFFFFF6, &D0); // MOVEQ.L	$F6,D0
  DEF_ROMLOC(1ACC0) : cmp_tomem_8(0x2, A0 + 0x28);    // CMPI.B	#$02,40(A0)
  DEF_ROMLOC(1ACC6) : if (CCR_LE) goto rom_1ACCA;     // BLE.B	$1ACCA
  DEF_ROMLOC(1ACC8) : move_toreg_32(0xE, &D0);        // MOVEQ.L	$0E,D0
  DEF_ROMLOC(1ACCA) : add_toreg_16(D0, &D1);          // ADD.W	D0,D1
  DEF_ROMLOC(1ACCC)
      : move_toreg_32(read_32(A0 + 0x34), &A1);    // MOVEA.L	52(A0),A1
  DEF_ROMLOC(1ACD0) : move_tomem_16(D1, A1 + 0xC); // MOVE.W	D1,12(A1)
  DEF_ROMLOC(1ACD4)
      : move_tomem_16(read_16(A0 + 0x8), A1 + 0x8); // MOVE.W	8(A0),8(A1)
  DEF_ROMLOC(1ACDA) : move_toreg_16(0x2B, &D1);     // MOVE.W	#$002B,D1
  DEF_ROMLOC(1ACDE) : move_toreg_16(0x60, &D2);     // MOVE.W	#$0060,D2
  DEF_ROMLOC(1ACE2) : move_toreg_16(0x61, &D3);     // MOVE.W	#$0061,D3
  DEF_ROMLOC(1ACE6)
      : move_toreg_16(read_16(A0 + 0x8), &D4); // MOVE.W	8(A0),D4
  DEF_ROMLOC(1ACEA) : rom_10062();             // JSR	$00010062
  DEF_ROMLOC(1ACF0) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(1ACF2)
      : move_toreg_16(read_16(A0 + 0x3C), &D1);    // MOVE.W	60(A0),D1
  DEF_ROMLOC(1ACF6) : if (CCR_PL) goto rom_1AD06;  // BPL.B	$1AD06
  DEF_ROMLOC(1ACF8) : neg_reg_16(&D1);             // NEG.W	D1
  DEF_ROMLOC(1ACFA) : sub_toreg_16(0x8, &D1);      // SUBQ.W	#$08,D1
  DEF_ROMLOC(1ACFC) : if (CCR_CS) goto rom_1AD12;  // BCS.B	$1AD12
  DEF_ROMLOC(1ACFE) : add_toreg_8(0x1, &D0);       // ADDQ.B	#$01,D0
  DEF_ROMLOC(1AD00) : asr_toreg_16(0x4, &D1);      // ASR.W	#$04,D1
  DEF_ROMLOC(1AD02) : add_toreg_16(D1, &D0);       // ADD.W	D1,D0
  goto rom_1AD12;                                  // BRA.B	$1AD12
  DEF_ROMLOC(1AD06) : sub_toreg_16(0x27, &D1);     // SUBI.W	#$0027,D1
  DEF_ROMLOC(1AD0A) : if (CCR_CS) goto rom_1AD12;  // BCS.B	$1AD12
  DEF_ROMLOC(1AD0C) : add_toreg_8(0x1, &D0);       // ADDQ.B	#$01,D0
  DEF_ROMLOC(1AD0E) : asr_toreg_16(0x4, &D1);      // ASR.W	#$04,D1
  DEF_ROMLOC(1AD10) : add_toreg_16(D1, &D0);       // ADD.W	D1,D0
  DEF_ROMLOC(1AD12) : move_tomem_8(D0, A0 + 0x1A); // MOVE.B	D0,26(A0)
  DEF_ROMLOC(1AD16)
      : move_toreg_16(read_16(0xFFFFD008), &D0); // MOVE.W	$D008,D0
  DEF_ROMLOC(1AD1A)
      : sub_toreg_16(read_16(A0 + 0x8), &D0);     // SUB.W	8(A0),D0
  DEF_ROMLOC(1AD1E) : if (CCR_MI) goto rom_1AD2E; // BMI.B	$1AD2E
  DEF_ROMLOC(1AD20) : sub_toreg_16(0x140, &D0);   // SUBI.W	#$0140,D0
  DEF_ROMLOC(1AD24) : if (CCR_MI) goto rom_1AD2E; // BMI.B	$1AD2E
  DEF_ROMLOC(1AD26) : tst_mem_8(A0 + 0x1);        // TST.B	1(A0)
  DEF_ROMLOC(1AD2A) : if (CCR_PL) {
    rom_1ABFE();
    return;
  } // BPL.W	$1ABFE
  DEF_ROMLOC(1AD2E) : rom_DC92();
  return; // JMP	$0000DC92
}
ROMFUNC(rom_1AD34) {
  u8 switchindex = 0;
  DEF_ROMLOC(1AD34) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(1AD36) : move_toreg_8(read_8(A0 + 0x28), &D0);
  switchindex = D0 / 2; // MOVE.B	40(A0),D0
  DEF_ROMLOC(1AD3A)
      : move_toreg_16(read_16(0x1AD46 + (s16)(D0 & 0xffff)),
                      &D0); // MOVE.W	10(PC,D0),D0
  // DEF_ROMLOC(1AD3E): rom_1AD46 + (s16)(D0 & 0xffff)(); // JSR	6(PC,D0)
  DEF_ROMLOC(1AD3E) : switch (switchindex) {
  case 0:
    rom_1AD4E();
    break;
  case 1:
    rom_1AD4E();
    break;
  case 2:
    rom_1ADBA();
    break;
  case 3:
    rom_1ADBA();
    break;
  }
  rom_1ACA0(); // BRA.W	$1ACA0
}
ROMFUNC(rom_1AD4E) {
  DEF_ROMLOC(1AD4E) : tst_mem_8(A0 + 0x29);        // TST.B	41(A0)
  DEF_ROMLOC(1AD52) : if (!CCR_EQ) goto rom_1AD8A; // BNE.B	$1AD8A
  DEF_ROMLOC(1AD54)
      : move_toreg_32(read_32(A0 + 0x34), &A1);    // MOVEA.L	52(A0),A1
  DEF_ROMLOC(1AD58) : tst_mem_8(A1 + 0x21);        // TST.B	33(A1)
  DEF_ROMLOC(1AD5C) : if (!CCR_EQ) goto rom_1AD6A; // BNE.B	$1AD6A
  DEF_ROMLOC(1AD5E) : rom_1800C();                 // BSR.W	$1800C
  DEF_ROMLOC(1AD62)
      : sub_tomem_32(0x10000, A0 + 0x3C); // SUBI.L	#$00010000,60(A0)
  DEF_ROMLOC(1AD6A)
      : add_tomem_32(0x20000, A0 + 0x3C);         // ADDI.L	#$00020000,60(A0)
  DEF_ROMLOC(1AD72) : if (CCR_CC) goto rom_1ADB8; // BCC.B	$1ADB8
  DEF_ROMLOC(1AD74) : clr_mem_32(A0 + 0x3C);      // CLR.L	60(A0)
  DEF_ROMLOC(1AD78)
      : move_toreg_32(read_32(A0 + 0x34), &A1);     // MOVEA.L	52(A0),A1
  DEF_ROMLOC(1AD7C) : sub_tomem_16(0x1, A1 + 0x32); // SUBQ.W	#$01,50(A1)
  DEF_ROMLOC(1AD80) : clr_mem_16(A1 + 0x30);        // CLR.W	48(A1)
  DEF_ROMLOC(1AD84) : sub_tomem_8(0x2, A0 + 0x24);  // SUBQ.B	#$02,36(A0)
  DEF_ROMLOC(1AD88) : return;                       // RTS
  DEF_ROMLOC(1AD8A)
      : cmp_tomem_16(0xFFFFFFF0, A0 + 0x3C);      // CMPI.W	#$FFF0,60(A0)
  DEF_ROMLOC(1AD90) : if (CCR_GE) goto rom_1AD9A; // BGE.B	$1AD9A
  DEF_ROMLOC(1AD92)
      : sub_tomem_32(0x28000, A0 + 0x3C); // SUBI.L	#$00028000,60(A0)
  DEF_ROMLOC(1AD9A)
      : sub_tomem_32(0x8000, A0 + 0x3C); // SUBI.L	#$00008000,60(A0)
  DEF_ROMLOC(1ADA2)
      : cmp_tomem_16(0xFFFFFF60, A0 + 0x3C);      // CMPI.W	#$FF60,60(A0)
  DEF_ROMLOC(1ADA8) : if (CCR_GT) goto rom_1ADB8; // BGT.B	$1ADB8
  DEF_ROMLOC(1ADAA) : clr_mem_16(A0 + 0x3E);      // CLR.W	62(A0)
  DEF_ROMLOC(1ADAE)
      : move_tomem_16(0xFFFFFF60, A0 + 0x3C); // MOVE.W	#$FF60,60(A0)
  DEF_ROMLOC(1ADB4) : clr_mem_8(A0 + 0x29);   // CLR.B	41(A0)
  DEF_ROMLOC(1ADB8) : return;                 // RTS
}
ROMFUNC(rom_1ADBA) {
  DEF_ROMLOC(1ADBA) : bset_tomem_8(0x1, A0 + 0x1); // BSET.B	#$01,1(A0)
  DEF_ROMLOC(1ADC0) : tst_mem_8(A0 + 0x29);        // TST.B	41(A0)
  DEF_ROMLOC(1ADC4) : if (!CCR_EQ) goto rom_1ADFC; // BNE.B	$1ADFC
  DEF_ROMLOC(1ADC6)
      : move_toreg_32(read_32(A0 + 0x34), &A1);    // MOVEA.L	52(A0),A1
  DEF_ROMLOC(1ADCA) : tst_mem_8(A1 + 0x21);        // TST.B	33(A1)
  DEF_ROMLOC(1ADCE) : if (!CCR_EQ) goto rom_1ADDC; // BNE.B	$1ADDC
  DEF_ROMLOC(1ADD0) : rom_1800C();                 // BSR.W	$1800C
  DEF_ROMLOC(1ADD4)
      : add_tomem_32(0x10000, A0 + 0x3C); // ADDI.L	#$00010000,60(A0)
  DEF_ROMLOC(1ADDC)
      : sub_tomem_32(0x20000, A0 + 0x3C);         // SUBI.L	#$00020000,60(A0)
  DEF_ROMLOC(1ADE4) : if (CCR_CC) goto rom_1AE2A; // BCC.B	$1AE2A
  DEF_ROMLOC(1ADE6) : clr_mem_32(A0 + 0x3C);      // CLR.L	60(A0)
  DEF_ROMLOC(1ADEA)
      : move_toreg_32(read_32(A0 + 0x34), &A1);      // MOVEA.L	52(A0),A1
  DEF_ROMLOC(1ADEE) : sub_tomem_16(0x1, A1 + 0x32);  // SUBQ.W	#$01,50(A1)
  DEF_ROMLOC(1ADF2) : clr_mem_16(A1 + 0x30);         // CLR.W	48(A1)
  DEF_ROMLOC(1ADF6) : sub_tomem_8(0x2, A0 + 0x24);   // SUBQ.B	#$02,36(A0)
  DEF_ROMLOC(1ADFA) : return;                        // RTS
  DEF_ROMLOC(1ADFC) : cmp_tomem_16(0x10, A0 + 0x3C); // CMPI.W	#$0010,60(A0)
  DEF_ROMLOC(1AE02) : if (CCR_LT) goto rom_1AE0C;    // BLT.B	$1AE0C
  DEF_ROMLOC(1AE04)
      : add_tomem_32(0x28000, A0 + 0x3C); // ADDI.L	#$00028000,60(A0)
  DEF_ROMLOC(1AE0C)
      : add_tomem_32(0x8000, A0 + 0x3C);             // ADDI.L	#$00008000,60(A0)
  DEF_ROMLOC(1AE14) : cmp_tomem_16(0xA0, A0 + 0x3C); // CMPI.W	#$00A0,60(A0)
  DEF_ROMLOC(1AE1A) : if (CCR_LT) goto rom_1AE2A;    // BLT.B	$1AE2A
  DEF_ROMLOC(1AE1C) : clr_mem_16(A0 + 0x3E);         // CLR.W	62(A0)
  DEF_ROMLOC(1AE20) : move_tomem_16(0xA0, A0 + 0x3C); // MOVE.W	#$00A0,60(A0)
  DEF_ROMLOC(1AE26) : clr_mem_8(A0 + 0x29);           // CLR.B	41(A0)
  DEF_ROMLOC(1AE2A) : return;                         // RTS
  DEF_ROMLOC(1AE2C) : or_tomem_8(0x37, A0++);         // ORI.B	#$37,(A0)+
  DEF_ROMLOC(1AE30) : or_tomem_16(0x93, A0 -= 2);     // ORI.W	#$0093,-(A0)
  rom_1AF90(); // Detected flow into next function
}