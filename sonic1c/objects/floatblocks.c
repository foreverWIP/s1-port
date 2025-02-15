// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_10912) {
  u8 switchindex = 0;
  DEF_ROMLOC(10912) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(10914) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(10918)
      : move_toreg_16(read_16(0x10920 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(1091C): goto rom_10920 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(1091C) : switch (switchindex) {
  case 0:
    rom_10934();
    break;
  case 1:
    rom_10A34();
    break;
  }
}
ROMFUNC(rom_10934) {
  DEF_ROMLOC(10934) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(10938)
      : move_tomem_32(0x10DD4, A0 + 0x4); // MOVE.L	#$00010DD4,4(A0)
  DEF_ROMLOC(10940)
      : move_tomem_16(0x4000, A0 + 0x2);            // MOVE.W
                                                    // #$4000,2(A0)
  DEF_ROMLOC(10946) : cmp_tomem_8(ZONE_LZ, v_zone); // CMPI.B	#$01,$FE10
  DEF_ROMLOC(1094C) : if (!CCR_EQ) goto rom_10954;  // BNE.B	$10954
  DEF_ROMLOC(1094E)
      : move_tomem_16(0x43C4, A0 + 0x2);            // MOVE.W
                                                    // #$43C4,2(A0)
  DEF_ROMLOC(10954) : move_tomem_8(0x4, A0 + 0x1);  // MOVE.B	#$04,1(A0)
  DEF_ROMLOC(1095A) : move_tomem_8(0x3, A0 + 0x18); // MOVE.B	#$03,24(A0)
  DEF_ROMLOC(10960) : move_toreg_32(0x0, &D0);      // MOVEQ.L	$00,D0
  DEF_ROMLOC(10962)
      : move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B
                                              // 40(A0),D0
  DEF_ROMLOC(10966) : lsr_toreg_16(0x3, &D0); // LSR.W	#$03,D0
  DEF_ROMLOC(10968) : and_toreg_16(0xE, &D0); // ANDI.W	#$000E,D0
  DEF_ROMLOC(1096C)
      : move_toreg_32(0x10924 + (s16)(D0 & 0xffff),
                      &A2); // LEA.L	-74(PC,D0),A2
  DEF_ROMLOC(10970)
      : move_tomem_8(read_8(A2++), A0 + 0x19); // MOVE.B	(A2)+,25(A0)
  DEF_ROMLOC(10974)
      : move_tomem_8(read_8(A2), A0 + 0x16);       // MOVE.B	(A2),22(A0)
  DEF_ROMLOC(10978) : lsr_toreg_16(0x1, &D0);      // LSR.W	#$01,D0
  DEF_ROMLOC(1097A) : move_tomem_8(D0, A0 + 0x1A); // MOVE.B	D0,26(A0)
  DEF_ROMLOC(1097E)
      : move_tomem_16(read_16(A0 + 0x8), A0 + 0x34); // MOVE.W	8(A0),52(A0)
  DEF_ROMLOC(10984)
      : move_tomem_16(read_16(A0 + 0xC), A0 + 0x30);  // MOVE.W	12(A0),48(A0)
  DEF_ROMLOC(1098A) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(1098C) : move_toreg_8(read_8(A2), &D0);  // MOVE.B	(A2),D0
  DEF_ROMLOC(1098E) : add_toreg_16(D0, &D0);          // ADD.W	D0,D0
  DEF_ROMLOC(10990) : move_tomem_16(D0, A0 + 0x3A);   // MOVE.W	D0,58(A0)
  DEF_ROMLOC(10994) : cmp_tomem_8(0x37, A0 + 0x28);   // CMPI.B	#$37,40(A0)
  DEF_ROMLOC(1099A) : if (!CCR_EQ) goto rom_109C0;    // BNE.B	$109C0
  DEF_ROMLOC(1099C) : cmp_tomem_16(0x1BB8, A0 + 0x8); // CMPI.W	#$1BB8,8(A0)
  DEF_ROMLOC(109A2) : if (!CCR_EQ) goto rom_109B0;    // BNE.B	$109B0
  DEF_ROMLOC(109A4) : tst_mem_8(0xFFFFF7CE);          // TST.B	$F7CE
  DEF_ROMLOC(109A8) : if (CCR_EQ) goto rom_109C0;     // BEQ.B	$109C0
  DEF_ROMLOC(109AA) : rom_DCCE();
  return;                                          // JMP	$0000DCCE
  DEF_ROMLOC(109B0) : clr_mem_8(A0 + 0x28);        // CLR.B	40(A0)
  DEF_ROMLOC(109B4) : tst_mem_8(0xFFFFF7CE);       // TST.B	$F7CE
  DEF_ROMLOC(109B8) : if (!CCR_EQ) goto rom_109C0; // BNE.B	$109C0
  DEF_ROMLOC(109BA) : rom_DCCE();
  return;                                           // JMP	$0000DCCE
  DEF_ROMLOC(109C0) : move_toreg_32(0x0, &D0);      // MOVEQ.L	$00,D0
  DEF_ROMLOC(109C2) : cmp_tomem_8(ZONE_LZ, v_zone); // CMPI.B	#$01,$FE10
  DEF_ROMLOC(109C8) : if (CCR_EQ) goto rom_109EA;   // BEQ.B	$109EA
  DEF_ROMLOC(109CA)
      : move_toreg_8(read_8(A0 + 0x28), &D0);         // MOVE.B
                                                      // 40(A0),D0
  DEF_ROMLOC(109CE) : and_toreg_16(0xF, &D0);         // ANDI.W	#$000F,D0
  DEF_ROMLOC(109D2) : sub_toreg_16(0x8, &D0);         // SUBQ.W	#$08,D0
  DEF_ROMLOC(109D4) : if (CCR_CS) goto rom_109EA;     // BCS.B	$109EA
  DEF_ROMLOC(109D6) : lsl_toreg_16(0x2, &D0);         // LSL.W	#$02,D0
  DEF_ROMLOC(109D8) : move_toreg_32(0xFFFFFE8A, &A2); // LEA.L	$FE8A,A2
  DEF_ROMLOC(109DC)
      : move_toreg_32((s32)A2 + (s8)0x0 + (s16)D0,
                      &A2);                         // LEA.L	0(A2,D0),A2
  DEF_ROMLOC(109E0) : tst_mem_16(A2);               // TST.W	(A2)
  DEF_ROMLOC(109E2) : if (CCR_PL) goto rom_109EA;   // BPL.B	$109EA
  DEF_ROMLOC(109E4) : bchg_tomem_8(0x0, A0 + 0x22); // BCHG.B	#$00,34(A0)
  DEF_ROMLOC(109EA)
      : move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B
                                              // 40(A0),D0
  DEF_ROMLOC(109EE) : if (CCR_PL) {
    rom_10A34();
    return;
  }                                                   // BPL.B	$10A34
  DEF_ROMLOC(109F0) : and_toreg_8(0xF, &D0);          // ANDI.B	#$0F,D0
  DEF_ROMLOC(109F4) : move_tomem_8(D0, A0 + 0x3C);    // MOVE.B	D0,60(A0)
  DEF_ROMLOC(109F8) : move_tomem_8(0x5, A0 + 0x28);   // MOVE.B	#$05,40(A0)
  DEF_ROMLOC(109FE) : cmp_tomem_8(0x7, A0 + 0x1A);    // CMPI.B	#$07,26(A0)
  DEF_ROMLOC(10A04) : if (!CCR_EQ) goto rom_10A12;    // BNE.B	$10A12
  DEF_ROMLOC(10A06) : move_tomem_8(0xC, A0 + 0x28);   // MOVE.B	#$0C,40(A0)
  DEF_ROMLOC(10A0C) : move_tomem_16(0x80, A0 + 0x3A); // MOVE.W	#$0080,58(A0)
  DEF_ROMLOC(10A12) : move_toreg_32(0xFFFFFC00, &A2); // LEA.L	$FC00,A2
  DEF_ROMLOC(10A16) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(10A18)
      : move_toreg_8(read_8(A0 + 0x23), &D0); // MOVE.B
                                              // 35(A0),D0
  DEF_ROMLOC(10A1C) : if (CCR_EQ) {
    rom_10A34();
    return;
  } // BEQ.B	$10A34
  DEF_ROMLOC(10A1E)
      : bclr_tomem_8(0x7,
                     (s32)A2 + (s8)0x2 + (s16)D0); // BCLR.B	#$07,2(A2,D0)
  DEF_ROMLOC(10A24)
      : btst_tomem_8(0x0,
                     (s32)A2 + (s8)0x2 + (s16)D0); // BTST.B	#$00,2(A2,D0)
  DEF_ROMLOC(10A2A) : if (CCR_EQ) {
    rom_10A34();
    return;
  }                                                // BEQ.B	$10A34
  DEF_ROMLOC(10A2C) : add_tomem_8(0x1, A0 + 0x28); // ADDQ.B	#$01,40(A0)
  DEF_ROMLOC(10A30) : clr_mem_16(A0 + 0x3A);       // CLR.W	58(A0)
  rom_10A34(); // Detected flow into next function
}
ROMFUNC(rom_10ABC);
ROMFUNC(rom_10ABE);
ROMFUNC(rom_10ACA);
ROMFUNC(rom_10AEC);
ROMFUNC(rom_10AF8);
ROMFUNC(rom_10B1A);
ROMFUNC(rom_10BAE);
ROMFUNC(rom_10C12);
ROMFUNC(rom_10D14);
ROMFUNC(rom_10D26);
ROMFUNC(rom_10D36);
ROMFUNC(rom_10D46);
ROMFUNC(rom_10C4E);
ROMFUNC(rom_10CB0);
ROMFUNC(rom_10A34) {
  u8 switchindex = 0;
  DEF_ROMLOC(10A34)
      : move_tomem_16(read_16(A0 + 0x8), A7 -= 2); // MOVE.W	8(A0),-(A7)
  DEF_ROMLOC(10A38) : move_toreg_32(0x0, &D0);     // MOVEQ.L	$00,D0
  DEF_ROMLOC(10A3A)
      : move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B
                                              // 40(A0),D0
  DEF_ROMLOC(10A3E) : and_toreg_16(0xF, &D0);
  switchindex = D0;                          // ANDI.W	#$000F,D0
  DEF_ROMLOC(10A42) : add_toreg_16(D0, &D0); // ADD.W	D0,D0
  DEF_ROMLOC(10A44)
      : move_toreg_16(read_16(0x10AA0 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	90(PC,D0),D1
  // DEF_ROMLOC(10A48): rom_10AA0 + (s16)(D1 & 0xffff)(); // JSR
  // 86(PC,D1)
  DEF_ROMLOC(10A48) : switch (switchindex) {
  case 0:
    rom_10ABC();
    break;
  case 1:
    rom_10ABE();
    break;
  case 2:
    rom_10ACA();
    break;
  case 3:
    rom_10AEC();
    break;
  case 4:
    rom_10AF8();
    break;
  case 5:
    rom_10B1A();
    break;
  case 6:
    rom_10BAE();
    break;
  case 7:
    rom_10C12();
    break;
  case 8:
    rom_10D14();
    break;
  case 9:
    rom_10D26();
    break;
  case 0xa:
    rom_10D36();
    break;
  case 0xb:
    rom_10D46();
    break;
  case 0xc:
    rom_10C4E();
    break;
  case 0xd:
    rom_10CB0();
    break;
  }
  DEF_ROMLOC(10A4C)
      : move_toreg_16(read_16((A7 += 2, A7 - 2)), &D4); // MOVE.W	(A7)+,D4
  DEF_ROMLOC(10A4E) : tst_mem_8(A0 + 0x1);              // TST.B	1(A0)
  DEF_ROMLOC(10A52) : if (CCR_PL) goto rom_10A6C;       // BPL.B	$10A6C
  DEF_ROMLOC(10A54) : move_toreg_32(0x0, &D1);          // MOVEQ.L	$00,D1
  DEF_ROMLOC(10A56)
      : move_toreg_8(read_8(A0 + 0x19), &D1);  // MOVE.B	25(A0),D1
  DEF_ROMLOC(10A5A) : add_toreg_16(0xB, &D1);  // ADDI.W	#$000B,D1
  DEF_ROMLOC(10A5E) : move_toreg_32(0x0, &D2); // MOVEQ.L	$00,D2
  DEF_ROMLOC(10A60)
      : move_toreg_8(read_8(A0 + 0x16), &D2); // MOVE.B
                                              // 22(A0),D2
  DEF_ROMLOC(10A64) : move_toreg_16(D2, &D3); // MOVE.W	D2,D3
  DEF_ROMLOC(10A66) : add_toreg_16(0x1, &D3); // ADDQ.W	#$01,D3
  DEF_ROMLOC(10A68) : rom_10062();            // BSR.W	$10062
  DEF_ROMLOC(10A6C)
      : move_toreg_16(read_16(A0 + 0x34), &D0);      // MOVE.W	52(A0),D0
  DEF_ROMLOC(10A70) : and_toreg_16(0xFFFFFF80, &D0); // ANDI.W	#$FF80,D0
  DEF_ROMLOC(10A74)
      : move_toreg_16(read_16(0xFFFFF700), &D1);     // MOVE.W	$F700,D1
  DEF_ROMLOC(10A78) : sub_toreg_16(0x80, &D1);       // SUBI.W	#$0080,D1
  DEF_ROMLOC(10A7C) : and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
  DEF_ROMLOC(10A80) : sub_toreg_16(D1, &D0);         // SUB.W	D1,D0
  DEF_ROMLOC(10A82) : cmp_toreg_16(0x280, &D0);      // CMPI.W	#$0280,D0
  DEF_ROMLOC(10A86) : if (CCR_HI) goto rom_10A8C;    // BHI.B	$10A8C
  DEF_ROMLOC(10A88) : rom_DC92();
  return;                                           // BRA.W	$DC92
  DEF_ROMLOC(10A8C) : cmp_tomem_8(0x37, A0 + 0x28); // CMPI.B	#$37,40(A0)
  DEF_ROMLOC(10A92) : if (!CCR_EQ) goto rom_10A9A;  // BNE.B	$10A9A
  DEF_ROMLOC(10A94) : tst_mem_8(A0 + 0x38);         // TST.B	56(A0)
  DEF_ROMLOC(10A98) : if (!CCR_EQ) goto rom_10A88;  // BNE.B	$10A88
  DEF_ROMLOC(10A9A) : rom_DCCE();
  return; // JMP	$0000DCCE
}
ROMFUNC(rom_10ABC) {
  DEF_ROMLOC(10ABC) : return; // RTS
}
ROMFUNC(rom_10AD4);
ROMFUNC(rom_10ABE) {
  DEF_ROMLOC(10ABE) : move_toreg_16(0x40, &D1); // MOVE.W	#$0040,D1
  DEF_ROMLOC(10AC2) : move_toreg_32(0x0, &D0);  // MOVEQ.L	$00,D0
  DEF_ROMLOC(10AC4)
      : move_toreg_8(read_8(0xFFFFFE68), &D0); // MOVE.B	$FE68,D0
  rom_10AD4();                                 // BRA.B	$10AD4
}
ROMFUNC(rom_10ACA) {
  DEF_ROMLOC(10ACA) : move_toreg_16(0x80, &D1); // MOVE.W	#$0080,D1
  DEF_ROMLOC(10ACE) : move_toreg_32(0x0, &D0);  // MOVEQ.L	$00,D0
  DEF_ROMLOC(10AD0)
      : move_toreg_8(read_8(0xFFFFFE7C), &D0); // MOVE.B	$FE7C,D0
  rom_10AD4(); // Detected flow into next function
}
ROMFUNC(rom_10AE0);
ROMFUNC(rom_10AD4) {
  DEF_ROMLOC(10AD4) : btst_tomem_8(0x0, A0 + 0x22); // BTST.B	#$00,34(A0)
  DEF_ROMLOC(10ADA) : if (CCR_EQ) {
    rom_10AE0();
    return;
  }                                          // BEQ.B	$10AE0
  DEF_ROMLOC(10ADC) : neg_reg_16(&D0);       // NEG.W	D0
  DEF_ROMLOC(10ADE) : add_toreg_16(D1, &D0); // ADD.W	D1,D0
  rom_10AE0();                               // Detected flow into next function
}
ROMFUNC(rom_10AE0) {
  DEF_ROMLOC(10AE0)
      : move_toreg_16(read_16(A0 + 0x34), &D1);    // MOVE.W	52(A0),D1
  DEF_ROMLOC(10AE4) : sub_toreg_16(D0, &D1);       // SUB.W	D0,D1
  DEF_ROMLOC(10AE6) : move_tomem_16(D1, A0 + 0x8); // MOVE.W	D1,8(A0)
  DEF_ROMLOC(10AEA) : return;                      // RTS
}
ROMFUNC(rom_10B02);
ROMFUNC(rom_10AEC) {
  DEF_ROMLOC(10AEC) : move_toreg_16(0x40, &D1); // MOVE.W	#$0040,D1
  DEF_ROMLOC(10AF0) : move_toreg_32(0x0, &D0);  // MOVEQ.L	$00,D0
  DEF_ROMLOC(10AF2)
      : move_toreg_8(read_8(0xFFFFFE68), &D0); // MOVE.B	$FE68,D0
  rom_10B02();                                 // BRA.B	$10B02
}
ROMFUNC(rom_10AF8) {
  DEF_ROMLOC(10AF8) : move_toreg_16(0x80, &D1); // MOVE.W	#$0080,D1
  DEF_ROMLOC(10AFC) : move_toreg_32(0x0, &D0);  // MOVEQ.L	$00,D0
  DEF_ROMLOC(10AFE)
      : move_toreg_8(read_8(0xFFFFFE7C), &D0); // MOVE.B	$FE7C,D0
  rom_10B02(); // Detected flow into next function
}
ROMFUNC(rom_10B0E);
ROMFUNC(rom_10B02) {
  DEF_ROMLOC(10B02) : btst_tomem_8(0x0, A0 + 0x22); // BTST.B	#$00,34(A0)
  DEF_ROMLOC(10B08) : if (CCR_EQ) {
    rom_10B0E();
    return;
  }                                          // BEQ.B	$10B0E
  DEF_ROMLOC(10B0A) : neg_reg_16(&D0);       // NEG.W	D0
  DEF_ROMLOC(10B0C) : add_toreg_16(D1, &D0); // ADD.W	D1,D0
  rom_10B0E();                               // Detected flow into next function
}
ROMFUNC(rom_10B0E) {
  DEF_ROMLOC(10B0E)
      : move_toreg_16(read_16(A0 + 0x30), &D1);    // MOVE.W	48(A0),D1
  DEF_ROMLOC(10B12) : sub_toreg_16(D0, &D1);       // SUB.W	D0,D1
  DEF_ROMLOC(10B14) : move_tomem_16(D1, A0 + 0xC); // MOVE.W	D1,12(A0)
  DEF_ROMLOC(10B18) : return;                      // RTS
}
ROMFUNC(rom_10B1A) {
  DEF_ROMLOC(10B1A) : tst_mem_8(A0 + 0x38);        // TST.B	56(A0)
  DEF_ROMLOC(10B1E) : if (!CCR_EQ) goto rom_10B6E; // BNE.B	$10B6E
  DEF_ROMLOC(10B20)
      : cmp_tomem_16(ZONE16_LZ, v_zone);          // CMPI.W
                                                   // #$0100,$FE10
  DEF_ROMLOC(10B26) : if (!CCR_EQ) goto rom_10B44; // BNE.B	$10B44
  DEF_ROMLOC(10B28) : cmp_tomem_8(0x3, A0 + 0x3C); // CMPI.B	#$03,60(A0)
  DEF_ROMLOC(10B2E) : if (!CCR_EQ) goto rom_10B44; // BNE.B	$10B44
  DEF_ROMLOC(10B30) : clr_mem_8(0xFFFFF7C9);       // CLR.B	$F7C9
  DEF_ROMLOC(10B34)
      : move_toreg_16(read_16(0xFFFFD008), &D0);            // MOVE.W	$D008,D0
  DEF_ROMLOC(10B38) : cmp_toreg_16(read_16(A0 + 0x8), &D0); // CMP.W	8(A0),D0
  DEF_ROMLOC(10B3C) : if (CCR_CC) goto rom_10B44;           // BCC.B	$10B44
  DEF_ROMLOC(10B3E) : move_tomem_8(0x1, 0xFFFFF7C9);        // MOVE.B	#$01,$F7C9
  DEF_ROMLOC(10B44) : move_toreg_32(0xFFFFF7E0, &A2);       // LEA.L	$F7E0,A2
  DEF_ROMLOC(10B48) : move_toreg_32(0x0, &D0);              // MOVEQ.L	$00,D0
  DEF_ROMLOC(10B4A)
      : move_toreg_8(read_8(A0 + 0x3C), &D0); // MOVE.B
                                              // 60(A0),D0
  DEF_ROMLOC(10B4E)
      : btst_tomem_8(0x0,
                     (s32)A2 + (s8)0x0 + (s16)D0); // BTST.B	#$00,0(A2,D0)
  DEF_ROMLOC(10B54) : if (CCR_EQ) goto rom_10B78;  // BEQ.B	$10B78
  DEF_ROMLOC(10B56)
      : cmp_tomem_16(ZONE16_LZ, v_zone);           // CMPI.W
                                                    // #$0100,$FE10
  DEF_ROMLOC(10B5C) : if (!CCR_EQ) goto rom_10B68;  // BNE.B	$10B68
  DEF_ROMLOC(10B5E) : cmp_toreg_8(0x3, &D0);        // CMPI.B	#$03,D0
  DEF_ROMLOC(10B62) : if (!CCR_EQ) goto rom_10B68;  // BNE.B	$10B68
  DEF_ROMLOC(10B64) : clr_mem_8(0xFFFFF7C9);        // CLR.B	$F7C9
  DEF_ROMLOC(10B68) : move_tomem_8(0x1, A0 + 0x38); // MOVE.B	#$01,56(A0)
  DEF_ROMLOC(10B6E) : tst_mem_16(A0 + 0x3A);        // TST.W	58(A0)
  DEF_ROMLOC(10B72) : if (CCR_EQ) goto rom_10B92;   // BEQ.B	$10B92
  DEF_ROMLOC(10B74) : sub_tomem_16(0x2, A0 + 0x3A); // SUBQ.W	#$02,58(A0)
  DEF_ROMLOC(10B78)
      : move_toreg_16(read_16(A0 + 0x3A), &D0);     // MOVE.W	58(A0),D0
  DEF_ROMLOC(10B7C) : btst_tomem_8(0x0, A0 + 0x22); // BTST.B	#$00,34(A0)
  DEF_ROMLOC(10B82) : if (CCR_EQ) goto rom_10B86;   // BEQ.B	$10B86
  DEF_ROMLOC(10B84) : neg_reg_16(&D0);              // NEG.W	D0
  DEF_ROMLOC(10B86)
      : move_toreg_16(read_16(A0 + 0x30), &D1);       // MOVE.W	48(A0),D1
  DEF_ROMLOC(10B8A) : add_toreg_16(D0, &D1);          // ADD.W	D0,D1
  DEF_ROMLOC(10B8C) : move_tomem_16(D1, A0 + 0xC);    // MOVE.W	D1,12(A0)
  DEF_ROMLOC(10B90) : return;                         // RTS
  DEF_ROMLOC(10B92) : add_tomem_8(0x1, A0 + 0x28);    // ADDQ.B	#$01,40(A0)
  DEF_ROMLOC(10B96) : clr_mem_8(A0 + 0x38);           // CLR.B	56(A0)
  DEF_ROMLOC(10B9A) : move_toreg_32(0xFFFFFC00, &A2); // LEA.L	$FC00,A2
  DEF_ROMLOC(10B9E) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(10BA0)
      : move_toreg_8(read_8(A0 + 0x23), &D0);     // MOVE.B	35(A0),D0
  DEF_ROMLOC(10BA4) : if (CCR_EQ) goto rom_10B78; // BEQ.B	$10B78
  DEF_ROMLOC(10BA6)
      : bset_tomem_8(0x0,
                     (s32)A2 + (s8)0x2 + (s16)D0); // BSET.B	#$00,2(A2,D0)
  goto rom_10B78;                                  // BRA.B	$10B78
}
ROMFUNC(rom_10BAE) {
  DEF_ROMLOC(10BAE) : tst_mem_8(A0 + 0x38);           // TST.B	56(A0)
  DEF_ROMLOC(10BB2) : if (!CCR_EQ) goto rom_10BCA;    // BNE.B	$10BCA
  DEF_ROMLOC(10BB4) : move_toreg_32(0xFFFFF7E0, &A2); // LEA.L	$F7E0,A2
  DEF_ROMLOC(10BB8) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(10BBA)
      : move_toreg_8(read_8(A0 + 0x3C), &D0); // MOVE.B
                                              // 60(A0),D0
  DEF_ROMLOC(10BBE)
      : tst_mem_8((s32)A2 + (s8)0x0 + (s16)D0);     // TST.B	0(A2,D0)
  DEF_ROMLOC(10BC2) : if (CCR_PL) goto rom_10BDC;   // BPL.B	$10BDC
  DEF_ROMLOC(10BC4) : move_tomem_8(0x1, A0 + 0x38); // MOVE.B	#$01,56(A0)
  DEF_ROMLOC(10BCA) : move_toreg_32(0x0, &D0);      // MOVEQ.L	$00,D0
  DEF_ROMLOC(10BCC)
      : move_toreg_8(read_8(A0 + 0x16), &D0); // MOVE.B
                                              // 22(A0),D0
  DEF_ROMLOC(10BD0) : add_toreg_16(D0, &D0);  // ADD.W	D0,D0
  DEF_ROMLOC(10BD2)
      : cmp_toreg_16(read_16(A0 + 0x3A), &D0);      // CMP.W	58(A0),D0
  DEF_ROMLOC(10BD6) : if (CCR_EQ) goto rom_10BF6;   // BEQ.B	$10BF6
  DEF_ROMLOC(10BD8) : add_tomem_16(0x2, A0 + 0x3A); // ADDQ.W	#$02,58(A0)
  DEF_ROMLOC(10BDC)
      : move_toreg_16(read_16(A0 + 0x3A), &D0);     // MOVE.W	58(A0),D0
  DEF_ROMLOC(10BE0) : btst_tomem_8(0x0, A0 + 0x22); // BTST.B	#$00,34(A0)
  DEF_ROMLOC(10BE6) : if (CCR_EQ) goto rom_10BEA;   // BEQ.B	$10BEA
  DEF_ROMLOC(10BE8) : neg_reg_16(&D0);              // NEG.W	D0
  DEF_ROMLOC(10BEA)
      : move_toreg_16(read_16(A0 + 0x30), &D1);       // MOVE.W	48(A0),D1
  DEF_ROMLOC(10BEE) : add_toreg_16(D0, &D1);          // ADD.W	D0,D1
  DEF_ROMLOC(10BF0) : move_tomem_16(D1, A0 + 0xC);    // MOVE.W	D1,12(A0)
  DEF_ROMLOC(10BF4) : return;                         // RTS
  DEF_ROMLOC(10BF6) : sub_tomem_8(0x1, A0 + 0x28);    // SUBQ.B	#$01,40(A0)
  DEF_ROMLOC(10BFA) : clr_mem_8(A0 + 0x38);           // CLR.B	56(A0)
  DEF_ROMLOC(10BFE) : move_toreg_32(0xFFFFFC00, &A2); // LEA.L	$FC00,A2
  DEF_ROMLOC(10C02) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(10C04)
      : move_toreg_8(read_8(A0 + 0x23), &D0);     // MOVE.B	35(A0),D0
  DEF_ROMLOC(10C08) : if (CCR_EQ) goto rom_10BDC; // BEQ.B	$10BDC
  DEF_ROMLOC(10C0A)
      : bclr_tomem_8(0x0,
                     (s32)A2 + (s8)0x2 + (s16)D0); // BCLR.B	#$00,2(A2,D0)
  goto rom_10BDC;                                  // BRA.B	$10BDC
}
ROMFUNC(rom_10C12) {
  DEF_ROMLOC(10C12) : tst_mem_8(A0 + 0x38);         // TST.B	56(A0)
  DEF_ROMLOC(10C16) : if (!CCR_EQ) goto rom_10C28;  // BNE.B	$10C28
  DEF_ROMLOC(10C18) : tst_mem_8(0xFFFFF7EF);        // TST.B	$F7EF
  DEF_ROMLOC(10C1C) : if (CCR_EQ) goto rom_10C4C;   // BEQ.B	$10C4C
  DEF_ROMLOC(10C1E) : move_tomem_8(0x1, A0 + 0x38); // MOVE.B	#$01,56(A0)
  DEF_ROMLOC(10C24) : clr_mem_16(A0 + 0x3A);        // CLR.W	58(A0)
  DEF_ROMLOC(10C28) : add_tomem_16(0x1, A0 + 0x8);  // ADDQ.W	#$01,8(A0)
  DEF_ROMLOC(10C2C)
      : move_tomem_16(read_16(A0 + 0x8), A0 + 0x34);  // MOVE.W	8(A0),52(A0)
  DEF_ROMLOC(10C32) : add_tomem_16(0x1, A0 + 0x3A);   // ADDQ.W	#$01,58(A0)
  DEF_ROMLOC(10C36) : cmp_tomem_16(0x380, A0 + 0x3A); // CMPI.W	#$0380,58(A0)
  DEF_ROMLOC(10C3C) : if (!CCR_EQ) goto rom_10C4C;    // BNE.B	$10C4C
  DEF_ROMLOC(10C3E) : move_tomem_8(0x1, 0xFFFFF7CE);  // MOVE.B	#$01,$F7CE
  DEF_ROMLOC(10C44) : clr_mem_8(A0 + 0x38);           // CLR.B	56(A0)
  DEF_ROMLOC(10C48) : clr_mem_8(A0 + 0x28);           // CLR.B	40(A0)
  DEF_ROMLOC(10C4C) : return;                         // RTS
}
ROMFUNC(rom_10C4E) {
  DEF_ROMLOC(10C4E) : tst_mem_8(A0 + 0x38);           // TST.B	56(A0)
  DEF_ROMLOC(10C52) : if (!CCR_EQ) goto rom_10C6C;    // BNE.B	$10C6C
  DEF_ROMLOC(10C54) : move_toreg_32(0xFFFFF7E0, &A2); // LEA.L	$F7E0,A2
  DEF_ROMLOC(10C58) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(10C5A)
      : move_toreg_8(read_8(A0 + 0x3C), &D0); // MOVE.B
                                              // 60(A0),D0
  DEF_ROMLOC(10C5E)
      : btst_tomem_8(0x0,
                     (s32)A2 + (s8)0x0 + (s16)D0);  // BTST.B	#$00,0(A2,D0)
  DEF_ROMLOC(10C64) : if (CCR_EQ) goto rom_10C76;   // BEQ.B	$10C76
  DEF_ROMLOC(10C66) : move_tomem_8(0x1, A0 + 0x38); // MOVE.B	#$01,56(A0)
  DEF_ROMLOC(10C6C) : tst_mem_16(A0 + 0x3A);        // TST.W	58(A0)
  DEF_ROMLOC(10C70) : if (CCR_EQ) goto rom_10C94;   // BEQ.B	$10C94
  DEF_ROMLOC(10C72) : sub_tomem_16(0x2, A0 + 0x3A); // SUBQ.W	#$02,58(A0)
  DEF_ROMLOC(10C76)
      : move_toreg_16(read_16(A0 + 0x3A), &D0);     // MOVE.W	58(A0),D0
  DEF_ROMLOC(10C7A) : btst_tomem_8(0x0, A0 + 0x22); // BTST.B	#$00,34(A0)
  DEF_ROMLOC(10C80) : if (CCR_EQ) goto rom_10C88;   // BEQ.B	$10C88
  DEF_ROMLOC(10C82) : neg_reg_16(&D0);              // NEG.W	D0
  DEF_ROMLOC(10C84) : add_toreg_16(0x80, &D0);      // ADDI.W	#$0080,D0
  DEF_ROMLOC(10C88)
      : move_toreg_16(read_16(A0 + 0x34), &D1);       // MOVE.W	52(A0),D1
  DEF_ROMLOC(10C8C) : add_toreg_16(D0, &D1);          // ADD.W	D0,D1
  DEF_ROMLOC(10C8E) : move_tomem_16(D1, A0 + 0x8);    // MOVE.W	D1,8(A0)
  DEF_ROMLOC(10C92) : return;                         // RTS
  DEF_ROMLOC(10C94) : add_tomem_8(0x1, A0 + 0x28);    // ADDQ.B	#$01,40(A0)
  DEF_ROMLOC(10C98) : clr_mem_8(A0 + 0x38);           // CLR.B	56(A0)
  DEF_ROMLOC(10C9C) : move_toreg_32(0xFFFFFC00, &A2); // LEA.L	$FC00,A2
  DEF_ROMLOC(10CA0) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(10CA2)
      : move_toreg_8(read_8(A0 + 0x23), &D0);     // MOVE.B	35(A0),D0
  DEF_ROMLOC(10CA6) : if (CCR_EQ) goto rom_10C76; // BEQ.B	$10C76
  DEF_ROMLOC(10CA8)
      : bset_tomem_8(0x0,
                     (s32)A2 + (s8)0x2 + (s16)D0); // BSET.B	#$00,2(A2,D0)
  goto rom_10C76;                                  // BRA.B	$10C76
}
ROMFUNC(rom_10CB0) {
  DEF_ROMLOC(10CB0) : tst_mem_8(A0 + 0x38);           // TST.B	56(A0)
  DEF_ROMLOC(10CB4) : if (!CCR_EQ) goto rom_10CCC;    // BNE.B	$10CCC
  DEF_ROMLOC(10CB6) : move_toreg_32(0xFFFFF7E0, &A2); // LEA.L	$F7E0,A2
  DEF_ROMLOC(10CBA) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(10CBC)
      : move_toreg_8(read_8(A0 + 0x3C), &D0); // MOVE.B
                                              // 60(A0),D0
  DEF_ROMLOC(10CC0)
      : tst_mem_8((s32)A2 + (s8)0x0 + (s16)D0);     // TST.B	0(A2,D0)
  DEF_ROMLOC(10CC4) : if (CCR_PL) goto rom_10CDA;   // BPL.B	$10CDA
  DEF_ROMLOC(10CC6) : move_tomem_8(0x1, A0 + 0x38); // MOVE.B	#$01,56(A0)
  DEF_ROMLOC(10CCC) : move_toreg_16(0x80, &D0);     // MOVE.W	#$0080,D0
  DEF_ROMLOC(10CD0)
      : cmp_toreg_16(read_16(A0 + 0x3A), &D0);      // CMP.W	58(A0),D0
  DEF_ROMLOC(10CD4) : if (CCR_EQ) goto rom_10CF8;   // BEQ.B	$10CF8
  DEF_ROMLOC(10CD6) : add_tomem_16(0x2, A0 + 0x3A); // ADDQ.W	#$02,58(A0)
  DEF_ROMLOC(10CDA)
      : move_toreg_16(read_16(A0 + 0x3A), &D0);     // MOVE.W	58(A0),D0
  DEF_ROMLOC(10CDE) : btst_tomem_8(0x0, A0 + 0x22); // BTST.B	#$00,34(A0)
  DEF_ROMLOC(10CE4) : if (CCR_EQ) goto rom_10CEC;   // BEQ.B	$10CEC
  DEF_ROMLOC(10CE6) : neg_reg_16(&D0);              // NEG.W	D0
  DEF_ROMLOC(10CE8) : add_toreg_16(0x80, &D0);      // ADDI.W	#$0080,D0
  DEF_ROMLOC(10CEC)
      : move_toreg_16(read_16(A0 + 0x34), &D1);       // MOVE.W	52(A0),D1
  DEF_ROMLOC(10CF0) : add_toreg_16(D0, &D1);          // ADD.W	D0,D1
  DEF_ROMLOC(10CF2) : move_tomem_16(D1, A0 + 0x8);    // MOVE.W	D1,8(A0)
  DEF_ROMLOC(10CF6) : return;                         // RTS
  DEF_ROMLOC(10CF8) : sub_tomem_8(0x1, A0 + 0x28);    // SUBQ.B	#$01,40(A0)
  DEF_ROMLOC(10CFC) : clr_mem_8(A0 + 0x38);           // CLR.B	56(A0)
  DEF_ROMLOC(10D00) : move_toreg_32(0xFFFFFC00, &A2); // LEA.L	$FC00,A2
  DEF_ROMLOC(10D04) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(10D06)
      : move_toreg_8(read_8(A0 + 0x23), &D0);     // MOVE.B	35(A0),D0
  DEF_ROMLOC(10D0A) : if (CCR_EQ) goto rom_10CDA; // BEQ.B	$10CDA
  DEF_ROMLOC(10D0C)
      : bclr_tomem_8(0x0,
                     (s32)A2 + (s8)0x2 + (s16)D0); // BCLR.B	#$00,2(A2,D0)
  goto rom_10CDA;                                  // BRA.B	$10CDA
}
ROMFUNC(rom_10D54);
ROMFUNC(rom_10D14) {
  DEF_ROMLOC(10D14) : move_toreg_16(0x10, &D1); // MOVE.W	#$0010,D1
  DEF_ROMLOC(10D18) : move_toreg_32(0x0, &D0);  // MOVEQ.L	$00,D0
  DEF_ROMLOC(10D1A)
      : move_toreg_8(read_8(0xFFFFFE88), &D0); // MOVE.B	$FE88,D0
  DEF_ROMLOC(10D1E) : lsr_toreg_16(0x1, &D0);  // LSR.W	#$01,D0
  DEF_ROMLOC(10D20)
      : move_toreg_16(read_16(0xFFFFFE8A), &D3); // MOVE.W	$FE8A,D3
  rom_10D54();                                   // BRA.B	$10D54
}
ROMFUNC(rom_10D26) {
  DEF_ROMLOC(10D26) : move_toreg_16(0x30, &D1); // MOVE.W	#$0030,D1
  DEF_ROMLOC(10D2A) : move_toreg_32(0x0, &D0);  // MOVEQ.L	$00,D0
  DEF_ROMLOC(10D2C)
      : move_toreg_8(read_8(0xFFFFFE8C), &D0); // MOVE.B	$FE8C,D0
  DEF_ROMLOC(10D30)
      : move_toreg_16(read_16(0xFFFFFE8E), &D3); // MOVE.W	$FE8E,D3
  rom_10D54();                                   // BRA.B	$10D54
}
ROMFUNC(rom_10D36) {
  DEF_ROMLOC(10D36) : move_toreg_16(0x50, &D1); // MOVE.W	#$0050,D1
  DEF_ROMLOC(10D3A) : move_toreg_32(0x0, &D0);  // MOVEQ.L	$00,D0
  DEF_ROMLOC(10D3C)
      : move_toreg_8(read_8(0xFFFFFE90), &D0); // MOVE.B	$FE90,D0
  DEF_ROMLOC(10D40)
      : move_toreg_16(read_16(0xFFFFFE92), &D3); // MOVE.W	$FE92,D3
  rom_10D54();                                   // BRA.B	$10D54
}
ROMFUNC(rom_10D46) {
  DEF_ROMLOC(10D46) : move_toreg_16(0x70, &D1); // MOVE.W	#$0070,D1
  DEF_ROMLOC(10D4A) : move_toreg_32(0x0, &D0);  // MOVEQ.L	$00,D0
  DEF_ROMLOC(10D4C)
      : move_toreg_8(read_8(0xFFFFFE94), &D0); // MOVE.B	$FE94,D0
  DEF_ROMLOC(10D50)
      : move_toreg_16(read_16(0xFFFFFE96), &D3); // MOVE.W	$FE96,D3
  rom_10D54(); // Detected flow into next function
}
ROMFUNC(rom_10D54) {
  DEF_ROMLOC(10D54) : tst_reg_16(&D3);             // TST.W	D3
  DEF_ROMLOC(10D56) : if (!CCR_EQ) goto rom_10D62; // BNE.B	$10D62
  DEF_ROMLOC(10D58) : add_tomem_8(0x1, A0 + 0x22); // ADDQ.B	#$01,34(A0)
  DEF_ROMLOC(10D5C) : and_tomem_8(0x3, A0 + 0x22); // ANDI.B	#$03,34(A0)
  DEF_ROMLOC(10D62)
      : move_toreg_8(read_8(A0 + 0x22), &D2);      // MOVE.B	34(A0),D2
  DEF_ROMLOC(10D66) : and_toreg_8(0x3, &D2);       // ANDI.B	#$03,D2
  DEF_ROMLOC(10D6A) : if (!CCR_EQ) goto rom_10D82; // BNE.B	$10D82
  DEF_ROMLOC(10D6C) : sub_toreg_16(D1, &D0);       // SUB.W	D1,D0
  DEF_ROMLOC(10D6E)
      : add_toreg_16(read_16(A0 + 0x34), &D0);     // ADD.W	52(A0),D0
  DEF_ROMLOC(10D72) : move_tomem_16(D0, A0 + 0x8); // MOVE.W	D0,8(A0)
  DEF_ROMLOC(10D76) : neg_reg_16(&D1);             // NEG.W	D1
  DEF_ROMLOC(10D78)
      : add_toreg_16(read_16(A0 + 0x30), &D1);     // ADD.W	48(A0),D1
  DEF_ROMLOC(10D7C) : move_tomem_16(D1, A0 + 0xC); // MOVE.W	D1,12(A0)
  DEF_ROMLOC(10D80) : return;                      // RTS
  DEF_ROMLOC(10D82) : sub_toreg_8(0x1, &D2);       // SUBQ.B	#$01,D2
  DEF_ROMLOC(10D84) : if (!CCR_EQ) goto rom_10DA0; // BNE.B	$10DA0
  DEF_ROMLOC(10D86) : sub_toreg_16(0x1, &D1);      // SUBQ.W	#$01,D1
  DEF_ROMLOC(10D88) : sub_toreg_16(D1, &D0);       // SUB.W	D1,D0
  DEF_ROMLOC(10D8A) : neg_reg_16(&D0);             // NEG.W	D0
  DEF_ROMLOC(10D8C)
      : add_toreg_16(read_16(A0 + 0x30), &D0);     // ADD.W	48(A0),D0
  DEF_ROMLOC(10D90) : move_tomem_16(D0, A0 + 0xC); // MOVE.W	D0,12(A0)
  DEF_ROMLOC(10D94) : add_toreg_16(0x1, &D1);      // ADDQ.W	#$01,D1
  DEF_ROMLOC(10D96)
      : add_toreg_16(read_16(A0 + 0x34), &D1);     // ADD.W	52(A0),D1
  DEF_ROMLOC(10D9A) : move_tomem_16(D1, A0 + 0x8); // MOVE.W	D1,8(A0)
  DEF_ROMLOC(10D9E) : return;                      // RTS
  DEF_ROMLOC(10DA0) : sub_toreg_8(0x1, &D2);       // SUBQ.B	#$01,D2
  DEF_ROMLOC(10DA2) : if (!CCR_EQ) goto rom_10DBE; // BNE.B	$10DBE
  DEF_ROMLOC(10DA4) : sub_toreg_16(0x1, &D1);      // SUBQ.W	#$01,D1
  DEF_ROMLOC(10DA6) : sub_toreg_16(D1, &D0);       // SUB.W	D1,D0
  DEF_ROMLOC(10DA8) : neg_reg_16(&D0);             // NEG.W	D0
  DEF_ROMLOC(10DAA)
      : add_toreg_16(read_16(A0 + 0x34), &D0);     // ADD.W	52(A0),D0
  DEF_ROMLOC(10DAE) : move_tomem_16(D0, A0 + 0x8); // MOVE.W	D0,8(A0)
  DEF_ROMLOC(10DB2) : add_toreg_16(0x1, &D1);      // ADDQ.W	#$01,D1
  DEF_ROMLOC(10DB4)
      : add_toreg_16(read_16(A0 + 0x30), &D1);     // ADD.W	48(A0),D1
  DEF_ROMLOC(10DB8) : move_tomem_16(D1, A0 + 0xC); // MOVE.W	D1,12(A0)
  DEF_ROMLOC(10DBC) : return;                      // RTS
  DEF_ROMLOC(10DBE) : sub_toreg_16(D1, &D0);       // SUB.W	D1,D0
  DEF_ROMLOC(10DC0)
      : add_toreg_16(read_16(A0 + 0x30), &D0);     // ADD.W	48(A0),D0
  DEF_ROMLOC(10DC4) : move_tomem_16(D0, A0 + 0xC); // MOVE.W	D0,12(A0)
  DEF_ROMLOC(10DC8) : neg_reg_16(&D1);             // NEG.W	D1
  DEF_ROMLOC(10DCA)
      : add_toreg_16(read_16(A0 + 0x34), &D1);     // ADD.W	52(A0),D1
  DEF_ROMLOC(10DCE) : move_tomem_16(D1, A0 + 0x8); // MOVE.W	D1,8(A0)
  DEF_ROMLOC(10DD2) : return;                      // RTS
}