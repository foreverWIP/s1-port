// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_1709C) {
  u8 switchindex = 0;
  DEF_ROMLOC(1709C) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(1709E) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(170A2)
      : move_toreg_16(read_16(0x170AA + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(170A6): goto rom_170AA + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(170A6) : switch (switchindex) {
  case 0:
    rom_170BA();
    break;
  case 1:
    rom_171AA();
    break;
  case 2:
    rom_17354();
    break;
  case 3:
    rom_17322();
    break;
  case 4:
    rom_17354();
    break;
  case 5:
    rom_1722E();
    break;
  case 6:
    rom_1746C();
    break;
  }
}
ROMFUNC(rom_170B8) {
  DEF_ROMLOC(170B8) : return; // RTS
}
ROMFUNC(rom_170BA) {
  DEF_ROMLOC(170BA) : move_tomem_8(0x7, A0 + 0x16); // MOVE.B	#$07,22(A0)
  DEF_ROMLOC(170C0) : move_tomem_8(0x8, A0 + 0x17); // MOVE.B	#$08,23(A0)
  DEF_ROMLOC(170C6) : rom_DC40();                   // JSR	$0000DC40
  DEF_ROMLOC(170CC) : rom_15580();                  // JSR	$00015580
  DEF_ROMLOC(170D2) : tst_reg_16(&D1);              // TST.W	D1
  DEF_ROMLOC(170D4) : if (CCR_PL) {
    rom_170B8();
    return;
  }                                                // BPL.B	$170B8
  DEF_ROMLOC(170D6) : add_tomem_16(D1, A0 + 0xC);  // ADD.W	D1,12(A0)
  DEF_ROMLOC(170DA) : clr_mem_16(A0 + 0x12);       // CLR.W	18(A0)
  DEF_ROMLOC(170DE) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(170E2)
      : move_tomem_32(0x1751A, A0 + 0x4); // MOVE.L	#$0001751A,4(A0)
  DEF_ROMLOC(170EA) : move_tomem_16(0x22B0, A0 + 0x2); // MOVE.W
                                                       // #$22B0,2(A0)
  DEF_ROMLOC(170F0) : cmp_tomem_8(0x5, 0xFFFFFE10);    // CMPI.B	#$05,$FE10
  DEF_ROMLOC(170F6) : if (CCR_EQ) goto rom_170FE;      // BEQ.B	$170FE
  DEF_ROMLOC(170F8) : move_tomem_16(0x24FF, A0 + 0x2); // MOVE.W
                                                       // #$24FF,2(A0)
  DEF_ROMLOC(170FE) : and_tomem_8(0x3, A0 + 0x1);      // ANDI.B	#$03,1(A0)
  DEF_ROMLOC(17104) : or_tomem_8(0x4, A0 + 0x1);       // ORI.B	#$04,1(A0)
  DEF_ROMLOC(1710A)
      : move_tomem_8(read_8(A0 + 0x1), A0 + 0x22);  // MOVE.B	1(A0),34(A0)
  DEF_ROMLOC(17110) : move_tomem_8(0x4, A0 + 0x18); // MOVE.B	#$04,24(A0)
  DEF_ROMLOC(17116) : move_tomem_8(0x8, A0 + 0x19); // MOVE.B	#$08,25(A0)
  DEF_ROMLOC(1711C) : move_tomem_8(0xB, A0 + 0x20); // MOVE.B	#$0B,32(A0)
  DEF_ROMLOC(17122)
      : move_toreg_16(read_16(A0 + 0x8), &D2);      // MOVE.W	8(A0),D2
  DEF_ROMLOC(17126) : move_toreg_32(0xC, &D5);      // MOVEQ.L	$0C,D5
  DEF_ROMLOC(17128) : btst_tomem_8(0x0, A0 + 0x22); // BTST.B	#$00,34(A0)
  DEF_ROMLOC(1712E) : if (CCR_EQ) goto rom_17132;   // BEQ.B	$17132
  DEF_ROMLOC(17130) : neg_reg_16(&D5);              // NEG.W	D5
  DEF_ROMLOC(17132) : move_toreg_8(0x4, &D6);       // MOVE.B	#$04,D6
  DEF_ROMLOC(17136) : move_toreg_32(0x0, &D3);      // MOVEQ.L	$00,D3
  DEF_ROMLOC(17138) : move_toreg_32(0x4, &D4);      // MOVEQ.L	$04,D4
  DEF_ROMLOC(1713A) : move_toreg_32(A0, &A2);       // MOVEA.L	A0,A2
  DEF_ROMLOC(1713C) : move_toreg_32(0x2, &D1);      // MOVEQ.L	$02,D1
  DEF_ROMLOC(1713E) : rom_E130();                   // JSR	$0000E130
  DEF_ROMLOC(17144) : if (!CCR_EQ) {
    rom_17214();
    return;
  }                                                 // BNE.W	$17214
  DEF_ROMLOC(17148) : move_tomem_8(0x78, A1 + 0x0); // MOVE.B	#$78,0(A1)
  DEF_ROMLOC(1714E) : move_tomem_8(D6, A1 + 0x24);  // MOVE.B	D6,36(A1)
  DEF_ROMLOC(17152) : add_toreg_8(0x2, &D6);        // ADDQ.B	#$02,D6
  DEF_ROMLOC(17154)
      : move_tomem_32(read_32(A0 + 0x4), A1 + 0x4); // MOVE.L	4(A0),4(A1)
  DEF_ROMLOC(1715A)
      : move_tomem_16(read_16(A0 + 0x2), A1 + 0x2); // MOVE.W	2(A0),2(A1)
  DEF_ROMLOC(17160) : move_tomem_8(0x5, A1 + 0x18); // MOVE.B	#$05,24(A1)
  DEF_ROMLOC(17166) : move_tomem_8(0x8, A1 + 0x19); // MOVE.B	#$08,25(A1)
  DEF_ROMLOC(1716C)
      : move_tomem_8(0xFFFFFFCB, A1 + 0x20);       // MOVE.B	#$CB,32(A1)
  DEF_ROMLOC(17172) : add_toreg_16(D5, &D2);       // ADD.W	D5,D2
  DEF_ROMLOC(17174) : move_tomem_16(D2, A1 + 0x8); // MOVE.W	D2,8(A1)
  DEF_ROMLOC(17178)
      : move_tomem_16(read_16(A0 + 0xC), A1 + 0xC); // MOVE.W	12(A0),12(A1)
  DEF_ROMLOC(1717E)
      : move_tomem_8(read_8(A0 + 0x22), A1 + 0x22); // MOVE.B	34(A0),34(A1)
  DEF_ROMLOC(17184)
      : move_tomem_8(read_8(A0 + 0x22), A1 + 0x1);  // MOVE.B	34(A0),1(A1)
  DEF_ROMLOC(1718A) : move_tomem_8(0x8, A1 + 0x1A); // MOVE.B	#$08,26(A1)
  DEF_ROMLOC(17190) : move_tomem_32(A2, A1 + 0x3C); // MOVE.L	A2,60(A1)
  DEF_ROMLOC(17194) : move_tomem_8(D4, A1 + 0x3C);  // MOVE.B	D4,60(A1)
  DEF_ROMLOC(17198) : add_toreg_8(0x4, &D4);        // ADDQ.B	#$04,D4
  DEF_ROMLOC(1719A) : move_toreg_32(A1, &A2);       // MOVEA.L	A1,A2
  DEF_ROMLOC(1719C) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_1713E;                                 // DBF.W	D1,$1713E
  DEF_ROMLOC(171A0) : move_tomem_8(0x7, A0 + 0x2A); // MOVE.B	#$07,42(A0)
  DEF_ROMLOC(171A6) : clr_mem_8(A0 + 0x3C);         // CLR.B	60(A0)
  rom_171AA(); // Detected flow into next function
}
ROMFUNC(rom_17238);
ROMFUNC(rom_171AA) {
  u8 switchindex = 0;
  DEF_ROMLOC(171AA) : tst_mem_8(A0 + 0x22); // TST.B	34(A0)
  DEF_ROMLOC(171AE) : if (CCR_MI) {
    rom_17442();
    return;
  }                                            // BMI.W	$17442
  DEF_ROMLOC(171B2) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(171B4) : move_toreg_8(read_8(A0 + 0x25), &D0);
  switchindex = D0 / 2; // MOVE.B	37(A0),D0
  DEF_ROMLOC(171B8)
      : move_toreg_16(read_16(0x17234 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	122(PC,D0),D1
  // DEF_ROMLOC(171BC): rom_17234 + (s16)(D1 & 0xffff)(); // JSR
  // 118(PC,D1)
  DEF_ROMLOC(171BC) : switch (switchindex) {
  case 0:
    rom_17238();
    break;
  case 1:
    rom_1726C();
    break;
  }
  DEF_ROMLOC(171C0)
      : move_toreg_8(read_8(A0 + 0x2B), &D1);      // MOVE.B	43(A0),D1
  DEF_ROMLOC(171C4) : if (CCR_PL) goto rom_171F0;  // BPL.B	$171F0
  DEF_ROMLOC(171C6) : move_toreg_32(0x1749A, &A1); // LEA.L	$0001749A,A1
  DEF_ROMLOC(171CC)
      : move_toreg_8(read_8(A0 + 0x26), &D0);      // MOVE.B	38(A0),D0
  DEF_ROMLOC(171D0) : and_toreg_16(0x7F, &D0);     // ANDI.W	#$007F,D0
  DEF_ROMLOC(171D4) : add_tomem_8(0x4, A0 + 0x26); // ADDQ.B	#$04,38(A0)
  DEF_ROMLOC(171D8)
      : move_toreg_8(read_8((s32)A1 + (s8)0x0 + (s16)D0),
                     &D0);                          // MOVE.B	0(A1,D0),D0
  DEF_ROMLOC(171DC) : if (CCR_PL) goto rom_171E6;   // BPL.B	$171E6
  DEF_ROMLOC(171DE) : bclr_tomem_8(0x7, A0 + 0x2B); // BCLR.B	#$07,43(A0)
  DEF_ROMLOC(171E4) : goto rom_171F0;               // BRA.B	$171F0
  DEF_ROMLOC(171E6) : and_toreg_8(0x10, &D1);       // ANDI.B	#$10,D1
  DEF_ROMLOC(171EA) : add_toreg_8(D1, &D0);         // ADD.B	D1,D0
  DEF_ROMLOC(171EC) : move_tomem_8(D0, A0 + 0x1A);  // MOVE.B	D0,26(A0)
  DEF_ROMLOC(171F0)
      : move_toreg_16(read_16(A0 + 0x8), &D0);       // MOVE.W	8(A0),D0
  DEF_ROMLOC(171F4) : and_toreg_16(0xFFFFFF80, &D0); // ANDI.W	#$FF80,D0
  DEF_ROMLOC(171F8)
      : move_toreg_16(read_16(0xFFFFF700), &D1);     // MOVE.W	$F700,D1
  DEF_ROMLOC(171FC) : sub_toreg_16(0x80, &D1);       // SUBI.W	#$0080,D1
  DEF_ROMLOC(17200) : and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
  DEF_ROMLOC(17204) : sub_toreg_16(D1, &D0);         // SUB.W	D1,D0
  DEF_ROMLOC(17206) : cmp_toreg_16(0x280, &D0);      // CMPI.W	#$0280,D0
  DEF_ROMLOC(1720A) : if (CCR_HI) {
    rom_17214();
    return;
  }                               // BHI.W	$17214
  DEF_ROMLOC(1720E) : rom_DC92(); // JMP	$0000DC92
}
ROMFUNC(rom_17214) {
  DEF_ROMLOC(17214) : move_toreg_32(0xFFFFFC00, &A2); // LEA.L	$FC00,A2
  DEF_ROMLOC(17218) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(1721A)
      : move_toreg_8(read_8(A0 + 0x23), &D0);     // MOVE.B	35(A0),D0
  DEF_ROMLOC(1721E) : if (CCR_EQ) goto rom_17226; // BEQ.B	$17226
  DEF_ROMLOC(17220)
      : bclr_tomem_8(0x7,
                     (s32)A2 + (s8)0x2 + (s16)D0);  // BCLR.B	#$07,2(A2,D0)
  DEF_ROMLOC(17226) : move_tomem_8(0xA, A0 + 0x24); // MOVE.B	#$0A,36(A0)
  DEF_ROMLOC(1722C) : return;                       // RTS
}
ROMFUNC(rom_1722E) {
  DEF_ROMLOC(1722E) : rom_DCCE(); // JMP	$0000DCCE
}
ROMFUNC(rom_17234) {
  DEF_ROMLOC(17234) : or_toreg_8(0x38, &D4); // ORI.B	#$38,D4
  rom_17238();
}
ROMFUNC(rom_17238) {
  DEF_ROMLOC(17238) : sub_tomem_8(0x1, A0 + 0x2A);   // SUBQ.B	#$01,42(A0)
  DEF_ROMLOC(1723C) : if (CCR_MI) goto rom_17240;    // BMI.B	$17240
  DEF_ROMLOC(1723E) : return;                        // RTS
  DEF_ROMLOC(17240) : add_tomem_8(0x2, A0 + 0x25);   // ADDQ.B	#$02,37(A0)
  DEF_ROMLOC(17244) : move_tomem_8(0x10, A0 + 0x2A); // MOVE.B	#$10,42(A0)
  DEF_ROMLOC(1724A)
      : move_tomem_16(0xFFFFFF40, A0 + 0x10);         // MOVE.W	#$FF40,16(A0)
  DEF_ROMLOC(17250) : move_tomem_16(0x40, A0 + 0x14); // MOVE.W	#$0040,20(A0)
  DEF_ROMLOC(17256) : bchg_tomem_8(0x4, A0 + 0x2B);   // BCHG.B	#$04,43(A0)
  DEF_ROMLOC(1725C) : if (!CCR_EQ) goto rom_17266;    // BNE.B	$17266
  DEF_ROMLOC(1725E) : clr_mem_16(A0 + 0x10);          // CLR.W	16(A0)
  DEF_ROMLOC(17262) : neg_mem_16(A0 + 0x14);          // NEG.W	20(A0)
  DEF_ROMLOC(17266) : bset_tomem_8(0x7, A0 + 0x2B);   // BSET.B	#$07,43(A0)
  rom_1726C(); // Detected flow into next function
}
ROMFUNC(rom_1726C) {
  DEF_ROMLOC(1726C) : sub_tomem_8(0x1, A0 + 0x2A); // SUBQ.B	#$01,42(A0)
  DEF_ROMLOC(17270) : if (CCR_MI) goto rom_172CA;  // BMI.B	$172CA
  DEF_ROMLOC(17272) : tst_mem_16(A0 + 0x10);       // TST.W	16(A0)
  DEF_ROMLOC(17276) : if (CCR_EQ) goto rom_172C8;  // BEQ.B	$172C8
  DEF_ROMLOC(17278)
      : move_toreg_32(read_32(A0 + 0x8), &D2); // MOVE.L	8(A0),D2
  DEF_ROMLOC(1727C) : move_toreg_32(D2, &D3);  // MOVE.L	D2,D3
  DEF_ROMLOC(1727E)
      : move_toreg_16(read_16(A0 + 0x10), &D0);     // MOVE.W	16(A0),D0
  DEF_ROMLOC(17282) : btst_tomem_8(0x0, A0 + 0x22); // BTST.B	#$00,34(A0)
  DEF_ROMLOC(17288) : if (CCR_EQ) goto rom_1728C;   // BEQ.B	$1728C
  DEF_ROMLOC(1728A) : neg_reg_16(&D0);              // NEG.W	D0
  DEF_ROMLOC(1728C) : ext_reg_32(&D0);              // EXT.L	D0
  DEF_ROMLOC(1728E) : asl_toreg_32(0x8, &D0);       // ASL.L	#$08,D0
  DEF_ROMLOC(17290) : add_toreg_32(D0, &D2);        // ADD.L	D0,D2
  DEF_ROMLOC(17292) : move_tomem_32(D2, A0 + 0x8);  // MOVE.L	D2,8(A0)
  DEF_ROMLOC(17296) : swap_reg_16(&D3);             // SWAP.W	D3
  DEF_ROMLOC(17298)
      : cmp_toreg_16(read_16(A0 + 0x8), &D3);        // CMP.W	8(A0),D3
  DEF_ROMLOC(1729C) : if (CCR_EQ) goto rom_172C8;    // BEQ.B	$172C8
  DEF_ROMLOC(1729E) : rom_15580();                   // JSR	$00015580
  DEF_ROMLOC(172A4) : cmp_toreg_16(0xFFFFFFF8, &D1); // CMPI.W	#$FFF8,D1
  DEF_ROMLOC(172A8) : if (CCR_LT) goto rom_172DE;    // BLT.B	$172DE
  DEF_ROMLOC(172AA) : cmp_toreg_16(0xC, &D1);        // CMPI.W	#$000C,D1
  DEF_ROMLOC(172AE) : if (CCR_GE) goto rom_172DE;    // BGE.B	$172DE
  DEF_ROMLOC(172B0) : add_tomem_16(D1, A0 + 0xC);    // ADD.W	D1,12(A0)
  DEF_ROMLOC(172B4) : move_toreg_32(0x0, &D0);       // MOVEQ.L	$00,D0
  DEF_ROMLOC(172B6)
      : move_toreg_8(read_8(A0 + 0x3C), &D0);      // MOVE.B	60(A0),D0
  DEF_ROMLOC(172BA) : add_tomem_8(0x1, A0 + 0x3C); // ADDQ.B	#$01,60(A0)
  DEF_ROMLOC(172BE) : and_tomem_8(0xF, A0 + 0x3C); // ANDI.B	#$0F,60(A0)
  DEF_ROMLOC(172C4)
      : move_tomem_8(D1,
                     (s32)A0 + (s8)0x2C + (s16)D0); // MOVE.B	D1,44(A0,D0)
  DEF_ROMLOC(172C8) : return;                       // RTS
  DEF_ROMLOC(172CA) : sub_tomem_8(0x2, A0 + 0x25);  // SUBQ.B	#$02,37(A0)
  DEF_ROMLOC(172CE) : move_tomem_8(0x7, A0 + 0x2A); // MOVE.B	#$07,42(A0)
  DEF_ROMLOC(172D4) : clr_mem_16(A0 + 0x10);        // CLR.W	16(A0)
  DEF_ROMLOC(172D8) : clr_mem_16(A0 + 0x14);        // CLR.W	20(A0)
  DEF_ROMLOC(172DC) : return;                       // RTS
  DEF_ROMLOC(172DE) : move_toreg_32(0x0, &D0);      // MOVEQ.L	$00,D0
  DEF_ROMLOC(172E0)
      : move_toreg_8(read_8(A0 + 0x3C), &D0); // MOVE.B	60(A0),D0
  DEF_ROMLOC(172E4)
      : move_tomem_8(0xFFFFFF80,
                     (s32)A0 + (s8)0x2C + (s16)D0); // MOVE.B	#$80,44(A0,D0)
  DEF_ROMLOC(172EA) : neg_mem_16(A0 + 0xA);         // NEG.W	10(A0)
  DEF_ROMLOC(172EE) : if (CCR_EQ) goto rom_1730A;   // BEQ.B	$1730A
  DEF_ROMLOC(172F0) : btst_tomem_8(0x0, A0 + 0x22); // BTST.B	#$00,34(A0)
  DEF_ROMLOC(172F6) : if (CCR_EQ) goto rom_1730A;   // BEQ.B	$1730A
  DEF_ROMLOC(172F8) : sub_tomem_16(0x1, A0 + 0x8);  // SUBQ.W	#$01,8(A0)
  DEF_ROMLOC(172FC) : add_tomem_8(0x1, A0 + 0x3C);  // ADDQ.B	#$01,60(A0)
  DEF_ROMLOC(17300) : move_toreg_32(0x0, &D0);      // MOVEQ.L	$00,D0
  DEF_ROMLOC(17302)
      : move_toreg_8(read_8(A0 + 0x3C), &D0); // MOVE.B	60(A0),D0
  DEF_ROMLOC(17306)
      : clr_mem_8((s32)A0 + (s8)0x2C + (s16)D0);    // CLR.B	44(A0,D0)
  DEF_ROMLOC(1730A) : bchg_tomem_8(0x0, A0 + 0x22); // BCHG.B	#$00,34(A0)
  DEF_ROMLOC(17310)
      : move_tomem_8(read_8(A0 + 0x22), A0 + 0x1); // MOVE.B	34(A0),1(A0)
  DEF_ROMLOC(17316) : add_tomem_8(0x1, A0 + 0x3C); // ADDQ.B	#$01,60(A0)
  DEF_ROMLOC(1731A) : and_tomem_8(0xF, A0 + 0x3C); // ANDI.B	#$0F,60(A0)
  DEF_ROMLOC(17320) : return;                      // RTS
}
ROMFUNC(rom_17322) {
  DEF_ROMLOC(17322)
      : move_toreg_32(read_32(A0 + 0x3C), &A1); // MOVEA.L	60(A0),A1
  DEF_ROMLOC(17326)
      : move_tomem_8(read_8(A1 + 0x2B), A0 + 0x2B); // MOVE.B	43(A1),43(A0)
  DEF_ROMLOC(1732C) : if (CCR_PL) {
    rom_17354();
    return;
  }                                                // BPL.B	$17354
  DEF_ROMLOC(1732E) : move_toreg_32(0x1749A, &A1); // LEA.L	$0001749A,A1
  DEF_ROMLOC(17334)
      : move_toreg_8(read_8(A0 + 0x26), &D0);      // MOVE.B	38(A0),D0
  DEF_ROMLOC(17338) : and_toreg_16(0x7F, &D0);     // ANDI.W	#$007F,D0
  DEF_ROMLOC(1733C) : add_tomem_8(0x4, A0 + 0x26); // ADDQ.B	#$04,38(A0)
  DEF_ROMLOC(17340)
      : tst_mem_8((s32)A1 + (s8)0x4 + (s16)D0);    // TST.B	4(A1,D0)
  DEF_ROMLOC(17344) : if (CCR_PL) goto rom_1734A;  // BPL.B	$1734A
  DEF_ROMLOC(17346) : add_tomem_8(0x4, A0 + 0x26); // ADDQ.B	#$04,38(A0)
  DEF_ROMLOC(1734A)
      : move_toreg_8(read_8((s32)A1 + (s8)0x0 + (s16)D0),
                     &D0);                         // MOVE.B	0(A1,D0),D0
  DEF_ROMLOC(1734E) : add_toreg_8(0x8, &D0);       // ADDQ.B	#$08,D0
  DEF_ROMLOC(17350) : move_tomem_8(D0, A0 + 0x1A); // MOVE.B	D0,26(A0)
  rom_17354();
}
ROMFUNC(rom_17354) {
  DEF_ROMLOC(17354)
      : move_toreg_32(read_32(A0 + 0x3C), &A1);   // MOVEA.L	60(A0),A1
  DEF_ROMLOC(17358) : tst_mem_8(A0 + 0x22);       // TST.B	34(A0)
  DEF_ROMLOC(1735C) : if (CCR_MI) goto rom_1743C; // BMI.W	$1743C
  DEF_ROMLOC(17360)
      : move_tomem_8(read_8(A1 + 0x2B), A0 + 0x2B); // MOVE.B	43(A1),43(A0)
  DEF_ROMLOC(17366)
      : move_tomem_8(read_8(A1 + 0x25), A0 + 0x25); // MOVE.B	37(A1),37(A0)
  DEF_ROMLOC(1736C) : if (CCR_EQ) goto rom_17410;   // BEQ.W	$17410
  DEF_ROMLOC(17370)
      : move_tomem_16(read_16(A1 + 0x14), A0 + 0x14); // MOVE.W	20(A1),20(A0)
  DEF_ROMLOC(17376)
      : move_toreg_16(read_16(A1 + 0x10), &D0); // MOVE.W	16(A1),D0
  DEF_ROMLOC(1737A)
      : add_toreg_16(read_16(A0 + 0x14), &D0);      // ADD.W	20(A0),D0
  DEF_ROMLOC(1737E) : move_tomem_16(D0, A0 + 0x10); // MOVE.W	D0,16(A0)
  DEF_ROMLOC(17382)
      : move_toreg_32(read_32(A0 + 0x8), &D2); // MOVE.L	8(A0),D2
  DEF_ROMLOC(17386) : move_toreg_32(D2, &D3);  // MOVE.L	D2,D3
  DEF_ROMLOC(17388)
      : move_toreg_16(read_16(A0 + 0x10), &D0);     // MOVE.W	16(A0),D0
  DEF_ROMLOC(1738C) : btst_tomem_8(0x0, A0 + 0x22); // BTST.B	#$00,34(A0)
  DEF_ROMLOC(17392) : if (CCR_EQ) goto rom_17396;   // BEQ.B	$17396
  DEF_ROMLOC(17394) : neg_reg_16(&D0);              // NEG.W	D0
  DEF_ROMLOC(17396) : ext_reg_32(&D0);              // EXT.L	D0
  DEF_ROMLOC(17398) : asl_toreg_32(0x8, &D0);       // ASL.L	#$08,D0
  DEF_ROMLOC(1739A) : add_toreg_32(D0, &D2);        // ADD.L	D0,D2
  DEF_ROMLOC(1739C) : move_tomem_32(D2, A0 + 0x8);  // MOVE.L	D2,8(A0)
  DEF_ROMLOC(173A0) : swap_reg_16(&D3);             // SWAP.W	D3
  DEF_ROMLOC(173A2)
      : cmp_toreg_16(read_16(A0 + 0x8), &D3);     // CMP.W	8(A0),D3
  DEF_ROMLOC(173A6) : if (CCR_EQ) goto rom_17410; // BEQ.B	$17410
  DEF_ROMLOC(173A8) : move_toreg_32(0x0, &D0);    // MOVEQ.L	$00,D0
  DEF_ROMLOC(173AA)
      : move_toreg_8(read_8(A0 + 0x3C), &D0); // MOVE.B	60(A0),D0
  DEF_ROMLOC(173AE)
      : move_toreg_8(read_8((s32)A1 + (s8)0x2C + (s16)D0),
                     &D1);                          // MOVE.B	44(A1,D0),D1
  DEF_ROMLOC(173B2) : cmp_toreg_8(0xFFFFFF80, &D1); // CMPI.B	#$80,D1
  DEF_ROMLOC(173B6) : if (!CCR_EQ) goto rom_173FC;  // BNE.B	$173FC
  DEF_ROMLOC(173B8)
      : move_tomem_8(D1,
                     (s32)A0 + (s8)0x2C + (s16)D0); // MOVE.B	D1,44(A0,D0)
  DEF_ROMLOC(173BC) : neg_mem_16(A0 + 0xA);         // NEG.W	10(A0)
  DEF_ROMLOC(173C0) : if (CCR_EQ) goto rom_173E4;   // BEQ.B	$173E4
  DEF_ROMLOC(173C2) : btst_tomem_8(0x0, A0 + 0x22); // BTST.B	#$00,34(A0)
  DEF_ROMLOC(173C8) : if (CCR_EQ) goto rom_173E4;   // BEQ.B	$173E4
  DEF_ROMLOC(173CA)
      : cmp_tomem_16(0xFFFFFF40, A0 + 0x10);       // CMPI.W	#$FF40,16(A0)
  DEF_ROMLOC(173D0) : if (!CCR_EQ) goto rom_173E4; // BNE.B	$173E4
  DEF_ROMLOC(173D2) : sub_tomem_16(0x1, A0 + 0x8); // SUBQ.W	#$01,8(A0)
  DEF_ROMLOC(173D6) : add_tomem_8(0x1, A0 + 0x3C); // ADDQ.B	#$01,60(A0)
  DEF_ROMLOC(173DA) : move_toreg_32(0x0, &D0);     // MOVEQ.L	$00,D0
  DEF_ROMLOC(173DC)
      : move_toreg_8(read_8(A0 + 0x3C), &D0); // MOVE.B	60(A0),D0
  DEF_ROMLOC(173E0)
      : clr_mem_8((s32)A0 + (s8)0x2C + (s16)D0);    // CLR.B	44(A0,D0)
  DEF_ROMLOC(173E4) : bchg_tomem_8(0x0, A0 + 0x22); // BCHG.B	#$00,34(A0)
  DEF_ROMLOC(173EA)
      : move_tomem_8(read_8(A0 + 0x22), A0 + 0x1); // MOVE.B	34(A0),1(A0)
  DEF_ROMLOC(173F0) : add_tomem_8(0x1, A0 + 0x3C); // ADDQ.B	#$01,60(A0)
  DEF_ROMLOC(173F4) : and_tomem_8(0xF, A0 + 0x3C); // ANDI.B	#$0F,60(A0)
  goto rom_17410;                                  // BRA.B	$17410
  DEF_ROMLOC(173FC) : ext_reg_16(&D1);             // EXT.W	D1
  DEF_ROMLOC(173FE) : add_tomem_16(D1, A0 + 0xC);  // ADD.W	D1,12(A0)
  DEF_ROMLOC(17402) : add_tomem_8(0x1, A0 + 0x3C); // ADDQ.B	#$01,60(A0)
  DEF_ROMLOC(17406) : and_tomem_8(0xF, A0 + 0x3C); // ANDI.B	#$0F,60(A0)
  DEF_ROMLOC(1740C)
      : move_tomem_8(D1,
                     (s32)A0 + (s8)0x2C + (s16)D0); // MOVE.B	D1,44(A0,D0)
  DEF_ROMLOC(17410) : cmp_tomem_8(0xC, A1 + 0x24);  // CMPI.B	#$0C,36(A1)
  DEF_ROMLOC(17416) : if (CCR_EQ) goto rom_1743C;   // BEQ.B	$1743C
  DEF_ROMLOC(17418) : cmp_tomem_8(0x27, A1 + 0x0);  // CMPI.B	#$27,0(A1)
  DEF_ROMLOC(1741E) : if (CCR_EQ) goto rom_17428;   // BEQ.B	$17428
  DEF_ROMLOC(17420) : cmp_tomem_8(0xA, A1 + 0x24);  // CMPI.B	#$0A,36(A1)
  DEF_ROMLOC(17426) : if (!CCR_EQ) goto rom_1742E;  // BNE.B	$1742E
  DEF_ROMLOC(17428) : move_tomem_8(0xA, A0 + 0x24); // MOVE.B	#$0A,36(A0)
  DEF_ROMLOC(1742E) : rom_DC92();
  return;                                           // JMP	$0000DC92
  DEF_ROMLOC(1743C) : bset_tomem_8(0x7, A1 + 0x22); // BSET.B	#$07,34(A1)
  rom_17442(); // Detected flow into next function
}
ROMFUNC(rom_17442) {
  DEF_ROMLOC(17442) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(17444)
      : move_toreg_8(read_8(A0 + 0x24), &D0); // MOVE.B	36(A0),D0
  DEF_ROMLOC(17448)
      : move_toreg_16(read_16(0x17432 + (s16)(D0 & 0xffff)),
                      &D0);                         // MOVE.W	-24(PC,D0),D0
  DEF_ROMLOC(1744C) : btst_tomem_8(0x0, A0 + 0x22); // BTST.B	#$00,34(A0)
  DEF_ROMLOC(17452) : if (CCR_EQ) goto rom_17456;   // BEQ.B	$17456
  DEF_ROMLOC(17454) : neg_reg_16(&D0);              // NEG.W	D0
  DEF_ROMLOC(17456) : move_tomem_16(D0, A0 + 0x10); // MOVE.W	D0,16(A0)
  DEF_ROMLOC(1745A)
      : move_tomem_16(0xFFFFFC00, A0 + 0x12);       // MOVE.W	#$FC00,18(A0)
  DEF_ROMLOC(17460) : move_tomem_8(0xC, A0 + 0x24); // MOVE.B	#$0C,36(A0)
  DEF_ROMLOC(17466)
      : and_tomem_8(0xFFFFFFF8, A0 + 0x1A); // ANDI.B	#$F8,26(A0)
  rom_1746C();                              // Detected flow into next function
}
ROMFUNC(rom_1746C) {
  DEF_ROMLOC(1746C) : rom_DC40();                 // JSR	$0000DC40
  DEF_ROMLOC(17472) : tst_mem_16(A0 + 0x12);      // TST.W	18(A0)
  DEF_ROMLOC(17476) : if (CCR_MI) goto rom_1748C; // BMI.B	$1748C
  DEF_ROMLOC(17478) : rom_15580();                // JSR	$00015580
  DEF_ROMLOC(1747E) : tst_reg_16(&D1);            // TST.W	D1
  DEF_ROMLOC(17480) : if (CCR_PL) goto rom_1748C; // BPL.B	$1748C
  DEF_ROMLOC(17482) : add_tomem_16(D1, A0 + 0xC); // ADD.W	D1,12(A0)
  DEF_ROMLOC(17486)
      : move_tomem_16(0xFFFFFC00, A0 + 0x12); // MOVE.W	#$FC00,18(A0)
  DEF_ROMLOC(1748C) : tst_mem_8(A0 + 0x1);    // TST.B	1(A0)
  DEF_ROMLOC(17490) : if (CCR_PL) {
    rom_17214();
    return;
  }                               // BPL.W	$17214
  DEF_ROMLOC(17494) : rom_DC92(); // JMP	$0000DC92
}