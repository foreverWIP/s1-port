// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_90E0) {
  DEF_ROMLOC(90E0) : rom_9158();                    // BSR.W	$9158
  DEF_ROMLOC(90E4) : if (CCR_EQ) goto rom_9126;     // BEQ.B	$9126
  DEF_ROMLOC(90E6) : if (CCR_MI) goto rom_9142;     // BMI.W	$9142
  DEF_ROMLOC(90EA) : tst_reg_16(&D0);               // TST.W	D0
  DEF_ROMLOC(90EC) : if (CCR_EQ) goto rom_9110;     // BEQ.W	$9110
  DEF_ROMLOC(90F0) : if (CCR_MI) goto rom_90FA;     // BMI.B	$90FA
  DEF_ROMLOC(90F2) : tst_mem_16(A1 + 0x10);         // TST.W	16(A1)
  DEF_ROMLOC(90F6) : if (CCR_MI) goto rom_9110;     // BMI.B	$9110
  goto rom_9100;                                    // BRA.B	$9100
  DEF_ROMLOC(90FA) : tst_mem_16(A1 + 0x10);         // TST.W	16(A1)
  DEF_ROMLOC(90FE) : if (CCR_PL) goto rom_9110;     // BPL.B	$9110
  DEF_ROMLOC(9100) : sub_tomem_16(D0, A1 + 0x8);    // SUB.W	D0,8(A1)
  DEF_ROMLOC(9104) : move_tomem_16(0x0, A1 + 0x14); // MOVE.W	#$0000,20(A1)
  DEF_ROMLOC(910A) : move_tomem_16(0x0, A1 + 0x10); // MOVE.W	#$0000,16(A1)
  DEF_ROMLOC(9110) : btst_tomem_8(0x1, A1 + 0x22);  // BTST.B	#$01,34(A1)
  DEF_ROMLOC(9116) : if (!CCR_EQ) goto rom_9134;    // BNE.B	$9134
  DEF_ROMLOC(9118) : bset_tomem_8(0x5, A1 + 0x22);  // BSET.B	#$05,34(A1)
  DEF_ROMLOC(911E) : bset_tomem_8(0x5, A0 + 0x22);  // BSET.B	#$05,34(A0)
  DEF_ROMLOC(9124) : return;                        // RTS
  DEF_ROMLOC(9126) : btst_tomem_8(0x5, A0 + 0x22);  // BTST.B	#$05,34(A0)
  DEF_ROMLOC(912C) : if (CCR_EQ) goto rom_9140;     // BEQ.B	$9140
  DEF_ROMLOC(912E) : move_tomem_16(0x1, A1 + 0x1C); // MOVE.W	#$0001,28(A1)
  DEF_ROMLOC(9134) : bclr_tomem_8(0x5, A0 + 0x22);  // BCLR.B	#$05,34(A0)
  DEF_ROMLOC(913A) : bclr_tomem_8(0x5, A1 + 0x22);  // BCLR.B	#$05,34(A1)
  DEF_ROMLOC(9140) : return;                        // RTS
  DEF_ROMLOC(9142) : tst_mem_16(A1 + 0x12);         // TST.W	18(A1)
  DEF_ROMLOC(9146) : if (CCR_PL) goto rom_9156;     // BPL.B	$9156
  DEF_ROMLOC(9148) : tst_reg_16(&D3);               // TST.W	D3
  DEF_ROMLOC(914A) : if (CCR_PL) goto rom_9156;     // BPL.B	$9156
  DEF_ROMLOC(914C) : sub_tomem_16(D3, A1 + 0xC);    // SUB.W	D3,12(A1)
  DEF_ROMLOC(9150) : move_tomem_16(0x0, A1 + 0x12); // MOVE.W	#$0000,18(A1)
  DEF_ROMLOC(9156) : return;                        // RTS
}
ROMFUNC(rom_9158) {
  DEF_ROMLOC(9158) : move_toreg_32(0xFFFFD000, &A1); // LEA.L	$D000,A1
  DEF_ROMLOC(915C)
      : move_toreg_16(read_16(A1 + 0x8), &D0); // MOVE.W	8(A1),D0
  DEF_ROMLOC(9160)
      : sub_toreg_16(read_16(A0 + 0x8), &D0);              // SUB.W	8(A0),D0
  DEF_ROMLOC(9164) : add_toreg_16(D1, &D0);                // ADD.W	D1,D0
  DEF_ROMLOC(9166) : if (CCR_MI) goto rom_91C6;            // BMI.B	$91C6
  DEF_ROMLOC(9168) : move_toreg_16(D1, &D3);               // MOVE.W	D1,D3
  DEF_ROMLOC(916A) : add_toreg_16(D3, &D3);                // ADD.W	D3,D3
  DEF_ROMLOC(916C) : cmp_toreg_16(D3, &D0);                // CMP.W	D3,D0
  DEF_ROMLOC(916E) : if (CCR_HI) goto rom_91C6;            // BHI.B	$91C6
  DEF_ROMLOC(9170) : move_toreg_8(read_8(A1 + 0x16), &D3); // MOVE.B
                                                           // 22(A1),D3
  DEF_ROMLOC(9174) : ext_reg_16(&D3);                      // EXT.W	D3
  DEF_ROMLOC(9176) : add_toreg_16(D3, &D2);                // ADD.W	D3,D2
  DEF_ROMLOC(9178)
      : move_toreg_16(read_16(A1 + 0xC), &D3);             // MOVE.W	12(A1),D3
  DEF_ROMLOC(917C) : sub_toreg_16(read_16(A0 + 0xC), &D3); // SUB.W
                                                           // 12(A0),D3
  DEF_ROMLOC(9180) : add_toreg_16(D2, &D3);                // ADD.W	D2,D3
  DEF_ROMLOC(9182) : if (CCR_MI) goto rom_91C6;            // BMI.B	$91C6
  DEF_ROMLOC(9184) : move_toreg_16(D2, &D4);               // MOVE.W	D2,D4
  DEF_ROMLOC(9186) : add_toreg_16(D4, &D4);                // ADD.W	D4,D4
  DEF_ROMLOC(9188) : cmp_toreg_16(D4, &D3);                // CMP.W	D4,D3
  DEF_ROMLOC(918A) : if (CCR_CC) goto rom_91C6;            // BCC.B	$91C6
  DEF_ROMLOC(918C) : tst_mem_8(0xFFFFF7C8);                // TST.B	$F7C8
  DEF_ROMLOC(9190) : if (CCR_MI) goto rom_91C6;            // BMI.B	$91C6
  DEF_ROMLOC(9192) : cmp_tomem_8(0x6, 0xFFFFD024);         // CMPI.B	#$06,$D024
  DEF_ROMLOC(9198) : if (CCR_CC) goto rom_91C6;            // BCC.B	$91C6
  DEF_ROMLOC(919A) : tst_mem_16(0xFFFFFE08);               // TST.W	$FE08
  DEF_ROMLOC(919E) : if (!CCR_EQ) goto rom_91C6;           // BNE.B	$91C6
  DEF_ROMLOC(91A0) : move_toreg_16(D0, &D5);               // MOVE.W	D0,D5
  DEF_ROMLOC(91A2) : cmp_toreg_16(D0, &D1);                // CMP.W	D0,D1
  DEF_ROMLOC(91A4) : if (CCR_CC) goto rom_91AE;            // BCC.B	$91AE
  DEF_ROMLOC(91A6) : add_toreg_16(D1, &D1);                // ADD.W	D1,D1
  DEF_ROMLOC(91A8) : sub_toreg_16(D1, &D0);                // SUB.W	D1,D0
  DEF_ROMLOC(91AA) : move_toreg_16(D0, &D5);               // MOVE.W	D0,D5
  DEF_ROMLOC(91AC) : neg_reg_16(&D5);                      // NEG.W	D5
  DEF_ROMLOC(91AE) : move_toreg_16(D3, &D1);               // MOVE.W	D3,D1
  DEF_ROMLOC(91B0) : cmp_toreg_16(D3, &D2);                // CMP.W	D3,D2
  DEF_ROMLOC(91B2) : if (CCR_CC) goto rom_91BA;            // BCC.B	$91BA
  DEF_ROMLOC(91B4) : sub_toreg_16(D4, &D3);                // SUB.W	D4,D3
  DEF_ROMLOC(91B6) : move_toreg_16(D3, &D1);               // MOVE.W	D3,D1
  DEF_ROMLOC(91B8) : neg_reg_16(&D1);                      // NEG.W	D1
  DEF_ROMLOC(91BA) : cmp_toreg_16(D1, &D5);                // CMP.W	D1,D5
  DEF_ROMLOC(91BC) : if (CCR_HI) goto rom_91C2;            // BHI.B	$91C2
  DEF_ROMLOC(91BE) : move_toreg_32(0x1, &D4);              // MOVEQ.L	$01,D4
  DEF_ROMLOC(91C0) : return;                               // RTS
  DEF_ROMLOC(91C2) : move_toreg_32(0xFFFFFFFF, &D4);       // MOVEQ.L	$FF,D4
  DEF_ROMLOC(91C4) : return;                               // RTS
  DEF_ROMLOC(91C6) : move_toreg_32(0x0, &D4);              // MOVEQ.L	$00,D4
  DEF_ROMLOC(91C8) : return;                               // RTS
}
ROMFUNC(rom_40F2) {
  DEF_ROMLOC(40F2) : move_toreg_32(0x0, &D0);           // MOVEQ.L	$00,D0
  DEF_ROMLOC(40F4) : move_toreg_8(read_8(v_zone), &D0); // MOVE.B	$FE10,D0
  DEF_ROMLOC(40F8) : lsl_toreg_16(0x2, &D0);            // LSL.W	#$02,D0
  DEF_ROMLOC(40FA)
      : move_tomem_32(read_32(0x4102 + (s16)(D0 & 0xffff)),
                      0xFFFFF796); // MOVE.L	6(PC,D0),$F796
  DEF_ROMLOC(4100) : return;       // RTS
}
ROMFUNC(rom_10062) {
  DEF_ROMLOC(10062) : tst_mem_8(A0 + 0x25); // TST.B	37(A0)
  DEF_ROMLOC(10066) : if (CCR_EQ) {
    rom_10154();
    return;
  }                                                   // BEQ.W	$10154
  DEF_ROMLOC(1006A) : move_toreg_16(D1, &D2);         // MOVE.W	D1,D2
  DEF_ROMLOC(1006C) : add_toreg_16(D2, &D2);          // ADD.W	D2,D2
  DEF_ROMLOC(1006E) : move_toreg_32(0xFFFFD000, &A1); // LEA.L	$D000,A1
  DEF_ROMLOC(10072) : btst_tomem_8(0x1, A1 + 0x22);   // BTST.B	#$01,34(A1)
  DEF_ROMLOC(10078) : if (!CCR_EQ) goto rom_1008A;    // BNE.B	$1008A
  DEF_ROMLOC(1007A)
      : move_toreg_16(read_16(A1 + 0x8), &D0);              // MOVE.W	8(A1),D0
  DEF_ROMLOC(1007E) : sub_toreg_16(read_16(A0 + 0x8), &D0); // SUB.W	8(A0),D0
  DEF_ROMLOC(10082) : add_toreg_16(D1, &D0);                // ADD.W	D1,D0
  DEF_ROMLOC(10084) : if (CCR_MI) goto rom_1008A;           // BMI.B	$1008A
  DEF_ROMLOC(10086) : cmp_toreg_16(D2, &D0);                // CMP.W	D2,D0
  DEF_ROMLOC(10088) : if (CCR_CS) goto rom_1009E;           // BCS.B	$1009E
  DEF_ROMLOC(1008A) : bclr_tomem_8(0x3, A1 + 0x22); // BCLR.B	#$03,34(A1)
  DEF_ROMLOC(10090) : bclr_tomem_8(0x3, A0 + 0x22); // BCLR.B	#$03,34(A0)
  DEF_ROMLOC(10096) : clr_mem_8(A0 + 0x25);         // CLR.B	37(A0)
  DEF_ROMLOC(1009A) : move_toreg_32(0x0, &D4);      // MOVEQ.L	$00,D4
  DEF_ROMLOC(1009C) : return;                       // RTS
  DEF_ROMLOC(1009E) : move_toreg_16(D4, &D2);       // MOVE.W	D4,D2
  DEF_ROMLOC(100A0) : rom_81A0();                   // BSR.W	$81A0
  DEF_ROMLOC(100A4) : move_toreg_32(0x0, &D4);      // MOVEQ.L	$00,D4
  DEF_ROMLOC(100A6) : return;                       // RTS
}

ROMFUNC(rom_10154) {
  DEF_ROMLOC(10154) : tst_mem_8(A0 + 0x1); // TST.B	1(A0)
  DEF_ROMLOC(10158) : if (CCR_PL) {
    rom_1021E();
    return;
  }            // BPL.W	$1021E
  rom_1015C(); // Detected flow into next function
}
ROMFUNC(rom_1015C) {
  DEF_ROMLOC(1015C) : move_toreg_32(0xFFFFD000, &A1); // LEA.L	$D000,A1
  DEF_ROMLOC(10160)
      : move_toreg_16(read_16(A1 + 0x8), &D0);              // MOVE.W	8(A1),D0
  DEF_ROMLOC(10164) : sub_toreg_16(read_16(A0 + 0x8), &D0); // SUB.W	8(A0),D0
  DEF_ROMLOC(10168) : add_toreg_16(D1, &D0);                // ADD.W	D1,D0
  DEF_ROMLOC(1016A) : if (CCR_MI) {
    rom_1021E();
    return;
  }                                           // BMI.W	$1021E
  DEF_ROMLOC(1016E) : move_toreg_16(D1, &D3); // MOVE.W	D1,D3
  DEF_ROMLOC(10170) : add_toreg_16(D3, &D3);  // ADD.W	D3,D3
  DEF_ROMLOC(10172) : cmp_toreg_16(D3, &D0);  // CMP.W	D3,D0
  DEF_ROMLOC(10174) : if (CCR_HI) {
    rom_1021E();
    return;
  } // BHI.W	$1021E
  DEF_ROMLOC(10178)
      : move_toreg_8(read_8(A1 + 0x16), &D3); // MOVE.B
                                              // 22(A1),D3
  DEF_ROMLOC(1017C) : ext_reg_16(&D3);        // EXT.W	D3
  DEF_ROMLOC(1017E) : add_toreg_16(D3, &D2);  // ADD.W	D3,D2
  DEF_ROMLOC(10180)
      : move_toreg_16(read_16(A1 + 0xC), &D3); // MOVE.W	12(A1),D3
  DEF_ROMLOC(10184)
      : sub_toreg_16(read_16(A0 + 0xC), &D3); // SUB.W
                                              // 12(A0),D3
  DEF_ROMLOC(10188) : add_toreg_16(0x4, &D3); // ADDQ.W	#$04,D3
  DEF_ROMLOC(1018A) : add_toreg_16(D2, &D3);  // ADD.W	D2,D3
  DEF_ROMLOC(1018C) : if (CCR_MI) {
    rom_1021E();
    return;
  }                                           // BMI.W	$1021E
  DEF_ROMLOC(10190) : move_toreg_16(D2, &D4); // MOVE.W	D2,D4
  DEF_ROMLOC(10192) : add_toreg_16(D4, &D4);  // ADD.W	D4,D4
  DEF_ROMLOC(10194) : cmp_toreg_16(D4, &D3);  // CMP.W	D4,D3
  DEF_ROMLOC(10196) : if (CCR_CC) {
    rom_1021E();
    return;
  }            // BCC.W	$1021E
  rom_1019A(); // Detected flow into next function
}
ROMFUNC(rom_1019A) {
  DEF_ROMLOC(1019A) : tst_mem_8(0xFFFFF7C8); // TST.B	$F7C8
  DEF_ROMLOC(1019E) : if (CCR_MI) {
    rom_1021E();
    return;
  }                                                 // BMI.W	$1021E
  DEF_ROMLOC(101A2) : cmp_tomem_8(0x6, 0xFFFFD024); // CMPI.B	#$06,$D024
  DEF_ROMLOC(101A8) : if (CCR_CC) {
    rom_10238();
    return;
  }                                           // BCC.W	$10238
  DEF_ROMLOC(101AC) : tst_mem_16(0xFFFFFE08); // TST.W	$FE08
  DEF_ROMLOC(101B0) : if (!CCR_EQ) {
    rom_10238();
    return;
  }                                               // BNE.W	$10238
  DEF_ROMLOC(101B4) : move_toreg_16(D0, &D5);     // MOVE.W	D0,D5
  DEF_ROMLOC(101B6) : cmp_toreg_16(D0, &D1);      // CMP.W	D0,D1
  DEF_ROMLOC(101B8) : if (CCR_CC) goto rom_101C2; // BCC.B	$101C2
  DEF_ROMLOC(101BA) : add_toreg_16(D1, &D1);      // ADD.W	D1,D1
  DEF_ROMLOC(101BC) : sub_toreg_16(D1, &D0);      // SUB.W	D1,D0
  DEF_ROMLOC(101BE) : move_toreg_16(D0, &D5);     // MOVE.W	D0,D5
  DEF_ROMLOC(101C0) : neg_reg_16(&D5);            // NEG.W	D5
  DEF_ROMLOC(101C2) : move_toreg_16(D3, &D1);     // MOVE.W	D3,D1
  DEF_ROMLOC(101C4) : cmp_toreg_16(D3, &D2);      // CMP.W	D3,D2
  DEF_ROMLOC(101C6) : if (CCR_CC) goto rom_101D0; // BCC.B	$101D0
  DEF_ROMLOC(101C8) : sub_toreg_16(0x4, &D3);     // SUBQ.W	#$04,D3
  DEF_ROMLOC(101CA) : sub_toreg_16(D4, &D3);      // SUB.W	D4,D3
  DEF_ROMLOC(101CC) : move_toreg_16(D3, &D1);     // MOVE.W	D3,D1
  DEF_ROMLOC(101CE) : neg_reg_16(&D1);            // NEG.W	D1
  DEF_ROMLOC(101D0) : cmp_toreg_16(D1, &D5);      // CMP.W	D1,D5
  DEF_ROMLOC(101D2) : if (CCR_HI) {
    rom_1023C();
    return;
  }                                           // BHI.W	$1023C
  DEF_ROMLOC(101D6) : cmp_toreg_16(0x4, &D1); // CMPI.W	#$0004,D1
  DEF_ROMLOC(101DA) : if (CCR_LS) {
    rom_10218();
    return;
  }                                    // BLS.B	$10218
  DEF_ROMLOC(101DC) : tst_reg_16(&D0); // TST.W	D0
  DEF_ROMLOC(101DE) : if (CCR_EQ) {
    rom_101FC();
    return;
  } // BEQ.B	$101FC
  DEF_ROMLOC(101E0) : if (CCR_MI) {
    rom_101EA();
    return;
  }                                          // BMI.B	$101EA
  DEF_ROMLOC(101E2) : tst_mem_16(A1 + 0x10); // TST.W	16(A1)
  DEF_ROMLOC(101E6) : if (CCR_MI) {
    rom_101FC();
    return;
  }            // BMI.B	$101FC
  rom_101F0(); // BRA.B	$101F0
}
ROMFUNC(rom_101EA) {
  DEF_ROMLOC(101EA) : tst_mem_16(A1 + 0x10); // TST.W	16(A1)
  DEF_ROMLOC(101EE) : if (CCR_PL) {
    rom_101FC();
    return;
  }            // BPL.B	$101FC
  rom_101F0(); // Detected flow into next function
}
ROMFUNC(rom_101F0) {
  DEF_ROMLOC(101F0) : move_tomem_16(0x0, A1 + 0x14); // MOVE.W	#$0000,20(A1)
  DEF_ROMLOC(101F6) : move_tomem_16(0x0, A1 + 0x10); // MOVE.W	#$0000,16(A1)
  rom_101FC(); // Detected flow into next function
}
ROMFUNC(rom_101FC) {
  DEF_ROMLOC(101FC) : sub_tomem_16(D0, A1 + 0x8);   // SUB.W	D0,8(A1)
  DEF_ROMLOC(10200) : btst_tomem_8(0x1, A1 + 0x22); // BTST.B	#$01,34(A1)
  DEF_ROMLOC(10206) : if (!CCR_EQ) {
    rom_10218();
    return;
  }                                                 // BNE.B	$10218
  DEF_ROMLOC(10208) : bset_tomem_8(0x5, A1 + 0x22); // BSET.B	#$05,34(A1)
  DEF_ROMLOC(1020E) : bset_tomem_8(0x5, A0 + 0x22); // BSET.B	#$05,34(A0)
  DEF_ROMLOC(10214) : move_toreg_32(0x1, &D4);      // MOVEQ.L	$01,D4
  DEF_ROMLOC(10216) : return;                       // RTS
}
ROMFUNC(rom_10218) {
  DEF_ROMLOC(10218) : rom_1022C();             // BSR.B	$1022C
  DEF_ROMLOC(1021A) : move_toreg_32(0x1, &D4); // MOVEQ.L	$01,D4
  DEF_ROMLOC(1021C) : return;                  // RTS
}
ROMFUNC(rom_1021E) {
  DEF_ROMLOC(1021E) : btst_tomem_8(0x5, A0 + 0x22); // BTST.B	#$05,34(A0)
  DEF_ROMLOC(10224) : if (CCR_EQ) {
    rom_10238();
    return;
  }                                                  // BEQ.B	$10238
  DEF_ROMLOC(10226) : move_tomem_16(0x1, A1 + 0x1C); // MOVE.W	#$0001,28(A1)
  rom_1022C(); // Detected flow into next function
}
ROMFUNC(rom_1022C) {
  DEF_ROMLOC(1022C) : bclr_tomem_8(0x5, A0 + 0x22); // BCLR.B	#$05,34(A0)
  DEF_ROMLOC(10232) : bclr_tomem_8(0x5, A1 + 0x22); // BCLR.B	#$05,34(A1)
  rom_10238(); // Detected flow into next function
}
ROMFUNC(rom_10238) {
  DEF_ROMLOC(10238) : move_toreg_32(0x0, &D4); // MOVEQ.L	$00,D4
  DEF_ROMLOC(1023A) : return;                  // RTS
}
ROMFUNC(rom_1023C) {
  DEF_ROMLOC(1023C) : tst_reg_16(&D3); // TST.W	D3
  DEF_ROMLOC(1023E) : if (CCR_MI) {
    rom_10248();
    return;
  }                                            // BMI.B	$10248
  DEF_ROMLOC(10240) : cmp_toreg_16(0x10, &D3); // CMPI.W	#$0010,D3
  DEF_ROMLOC(10244) : if (CCR_CS) {
    rom_1027A();
    return;
  }            // BCS.B	$1027A
  rom_1021E(); // BRA.B	$1021E
}
ROMFUNC(rom_10248) {
  DEF_ROMLOC(10248) : tst_mem_16(A1 + 0x12); // TST.W	18(A1)
  DEF_ROMLOC(1024C) : if (CCR_EQ) {
    rom_10262();
    return;
  } // BEQ.B	$10262
  DEF_ROMLOC(1024E) : if (CCR_PL) {
    rom_1025E();
    return;
  }                                    // BPL.B	$1025E
  DEF_ROMLOC(10250) : tst_reg_16(&D3); // TST.W	D3
  DEF_ROMLOC(10252) : if (CCR_PL) {
    rom_1025E();
    return;
  }                                                  // BPL.B	$1025E
  DEF_ROMLOC(10254) : sub_tomem_16(D3, A1 + 0xC);    // SUB.W	D3,12(A1)
  DEF_ROMLOC(10258) : move_tomem_16(0x0, A1 + 0x12); // MOVE.W	#$0000,18(A1)
  rom_1025E(); // Detected flow into next function
}
ROMFUNC(rom_1025E) {
  DEF_ROMLOC(1025E) : move_toreg_32(0xFFFFFFFF, &D4); // MOVEQ.L	$FF,D4
  DEF_ROMLOC(10260) : return;                         // RTS
}
ROMFUNC(rom_10262) {
  DEF_ROMLOC(10262) : btst_tomem_8(0x1, A1 + 0x22); // BTST.B	#$01,34(A1)
  DEF_ROMLOC(10268) : if (!CCR_EQ) {
    rom_1025E();
    return;
  }                                               // BNE.B	$1025E
  DEF_ROMLOC(1026A) : move_tomem_32(A0, A7 -= 4); // MOVE.L	A0,-(A7)
  DEF_ROMLOC(1026C) : move_toreg_32(A1, &A0);     // MOVEA.L	A1,A0
  DEF_ROMLOC(1026E) : rom_1B84E();                // JSR	$0001B84E
  DEF_ROMLOC(10274)
      : move_toreg_32(read_32((A7 += 4, A7 - 4)), &A0); // MOVEA.L	(A7)+,A0
  DEF_ROMLOC(10276) : move_toreg_32(0xFFFFFFFF, &D4);   // MOVEQ.L	$FF,D4
  DEF_ROMLOC(10278) : return;                           // RTS
}
ROMFUNC(rom_1027A) {
  DEF_ROMLOC(1027A) : sub_toreg_16(0x4, &D3);  // SUBQ.W	#$04,D3
  DEF_ROMLOC(1027C) : move_toreg_32(0x0, &D1); // MOVEQ.L	$00,D1
  DEF_ROMLOC(1027E)
      : move_toreg_8(read_8(A0 + 0x19), &D1);               // MOVE.B
                                                            // 25(A0),D1
  DEF_ROMLOC(10282) : move_toreg_16(D1, &D2);               // MOVE.W	D1,D2
  DEF_ROMLOC(10284) : add_toreg_16(D2, &D2);                // ADD.W	D2,D2
  DEF_ROMLOC(10286) : add_toreg_16(read_16(A1 + 0x8), &D1); // ADD.W	8(A1),D1
  DEF_ROMLOC(1028A) : sub_toreg_16(read_16(A0 + 0x8), &D1); // SUB.W	8(A0),D1
  DEF_ROMLOC(1028E) : if (CCR_MI) {
    rom_102B4();
    return;
  }                                          // BMI.B	$102B4
  DEF_ROMLOC(10290) : cmp_toreg_16(D2, &D1); // CMP.W	D2,D1
  DEF_ROMLOC(10292) : if (CCR_CC) {
    rom_102B4();
    return;
  }                                          // BCC.B	$102B4
  DEF_ROMLOC(10294) : tst_mem_16(A1 + 0x12); // TST.W	18(A1)
  DEF_ROMLOC(10298) : if (CCR_MI) {
    rom_102B4();
    return;
  }                                                   // BMI.B	$102B4
  DEF_ROMLOC(1029A) : sub_tomem_16(D3, A1 + 0xC);     // SUB.W	D3,12(A1)
  DEF_ROMLOC(1029E) : sub_tomem_16(0x1, A1 + 0xC);    // SUBQ.W	#$01,12(A1)
  DEF_ROMLOC(102A2) : rom_102B8();                    // BSR.B	$102B8
  DEF_ROMLOC(102A4) : move_tomem_8(0x2, A0 + 0x25);   // MOVE.B	#$02,37(A0)
  DEF_ROMLOC(102AA) : bset_tomem_8(0x3, A0 + 0x22);   // BSET.B	#$03,34(A0)
  DEF_ROMLOC(102B0) : move_toreg_32(0xFFFFFFFF, &D4); // MOVEQ.L	$FF,D4
  DEF_ROMLOC(102B2) : return;                         // RTS
}
ROMFUNC(rom_102B4) {
  DEF_ROMLOC(102B4) : move_toreg_32(0x0, &D4); // MOVEQ.L	$00,D4
  DEF_ROMLOC(102B6) : return;                  // RTS
}
ROMFUNC(rom_102B8) {
  DEF_ROMLOC(102B8) : btst_tomem_8(0x3, A1 + 0x22); // BTST.B	#$03,34(A1)
  DEF_ROMLOC(102BE) : if (CCR_EQ) goto rom_102DA;   // BEQ.B	$102DA
  DEF_ROMLOC(102C0) : move_toreg_32(0x0, &D0);      // MOVEQ.L	$00,D0
  DEF_ROMLOC(102C2)
      : move_toreg_8(read_8(A1 + 0x3D), &D0);        // MOVE.B
                                                     // 61(A1),D0
  DEF_ROMLOC(102C6) : lsl_toreg_16(0x6, &D0);        // LSL.W	#$06,D0
  DEF_ROMLOC(102C8) : add_toreg_32(0xFFD000, &D0);   // ADDI.L	#$00FFD000,D0
  DEF_ROMLOC(102CE) : move_toreg_32(D0, &A2);        // MOVEA.L	D0,A2
  DEF_ROMLOC(102D0) : bclr_tomem_8(0x3, A2 + 0x22);  // BCLR.B	#$03,34(A2)
  DEF_ROMLOC(102D6) : clr_mem_8(A2 + 0x25);          // CLR.B	37(A2)
  DEF_ROMLOC(102DA) : move_toreg_16(A0, &D0);        // MOVE.W	A0,D0
  DEF_ROMLOC(102DC) : sub_toreg_16(0xFFFFD000, &D0); // SUBI.W	#$D000,D0
  DEF_ROMLOC(102E0) : lsr_toreg_16(0x6, &D0);        // LSR.W	#$06,D0
  DEF_ROMLOC(102E2) : and_toreg_16(0x7F, &D0);       // ANDI.W	#$007F,D0
  DEF_ROMLOC(102E6) : move_tomem_8(D0, A1 + 0x3D);   // MOVE.B	D0,61(A1)
  DEF_ROMLOC(102EA) : move_tomem_8(0x0, A1 + 0x26);  // MOVE.B	#$00,38(A1)
  DEF_ROMLOC(102F0) : move_tomem_16(0x0, A1 + 0x12); // MOVE.W	#$0000,18(A1)
  DEF_ROMLOC(102F6)
      : move_tomem_16(read_16(A1 + 0x10), A1 + 0x14); // MOVE.W	16(A1),20(A1)
  DEF_ROMLOC(102FC) : btst_tomem_8(0x1, A1 + 0x22);   // BTST.B	#$01,34(A1)
  DEF_ROMLOC(10302) : if (CCR_EQ) goto rom_10310;     // BEQ.B	$10310
  DEF_ROMLOC(10304) : move_tomem_32(A0, A7 -= 4);     // MOVE.L	A0,-(A7)
  DEF_ROMLOC(10306) : move_toreg_32(A1, &A0);         // MOVEA.L	A1,A0
  DEF_ROMLOC(10308) : rom_13E74();                    // JSR	$00013E74
  DEF_ROMLOC(1030E)
      : move_toreg_32(read_32((A7 += 4, A7 - 4)), &A0); // MOVEA.L	(A7)+,A0
  DEF_ROMLOC(10310) : bset_tomem_8(0x3, A1 + 0x22);     // BSET.B	#$03,34(A1)
  DEF_ROMLOC(10316) : bset_tomem_8(0x3, A0 + 0x22);     // BSET.B	#$03,34(A0)
  DEF_ROMLOC(1031C) : return;                           // RTS
}
ROMFUNC(rom_15642) {
  DEF_ROMLOC(15642) : add_toreg_16(read_16(A0 + 0x8), &D3);  // ADD.W	8(A0),D3
  DEF_ROMLOC(15646) : move_toreg_16(read_16(A0 + 0xC), &D2); // MOVE.W
                                                             // 12(A0),D2
  DEF_ROMLOC(1564A) : move_toreg_32(0xFFFFF768, &A4);        // LEA.L	$F768,A4
  DEF_ROMLOC(1564E) : move_tomem_8(0x0, A4);                 // MOVE.B	#$00,(A4)
  DEF_ROMLOC(15652) : move_toreg_16(0x10, &A3); // MOVEA.W	#$0010,A3
  DEF_ROMLOC(15656) : move_toreg_16(0x0, &D6);  // MOVE.W	#$0000,D6
  DEF_ROMLOC(1565A) : move_toreg_32(0xE, &D5);  // MOVEQ.L	$0E,D5
  DEF_ROMLOC(1565C) : rom_15274();              // BSR.W	$15274
  DEF_ROMLOC(15660) : move_toreg_8(read_8(0xFFFFF768), &D3); // MOVE.B	$F768,D3
  DEF_ROMLOC(15664) : btst_toreg_32(0x0, &D3);               // BTST.L	#$00,D3
  DEF_ROMLOC(15668) : if (CCR_EQ) goto rom_1566E;            // BEQ.B	$1566E
  DEF_ROMLOC(1566A) : move_toreg_8(0xFFFFFFC0, &D3);         // MOVE.B	#$C0,D3
  DEF_ROMLOC(1566E) : return;                                // RTS
}
ROMFUNC(rom_15706) {
  DEF_ROMLOC(15706)
      : move_toreg_16(read_16(A0 + 0xC), &D2); // MOVE.W	12(A0),D2
  DEF_ROMLOC(1570A)
      : move_toreg_16(read_16(A0 + 0x8), &D3);              // MOVE.W	8(A0),D3
  DEF_ROMLOC(1570E) : move_toreg_32(0x0, &D0);              // MOVEQ.L	$00,D0
  DEF_ROMLOC(15710) : move_toreg_8(read_8(A0 + 0x16), &D0); // MOVE.B
                                                            // 22(A0),D0
  DEF_ROMLOC(15714) : ext_reg_16(&D0);                      // EXT.W	D0
  DEF_ROMLOC(15716) : sub_toreg_16(D0, &D2);                // SUB.W	D0,D2
  DEF_ROMLOC(15718) : eor_toreg_16(0xF, &D2);               // EORI.W	#$000F,D2
  DEF_ROMLOC(1571C) : move_toreg_32(0xFFFFF768, &A4);       // LEA.L	$F768,A4
  DEF_ROMLOC(15720)
      : move_toreg_16(0xFFFFFFF0, &A3);                      // MOVEA.W
                                                             // #$FFF0,A3
  DEF_ROMLOC(15724) : move_toreg_16(0x1000, &D6);            // MOVE.W	#$1000,D6
  DEF_ROMLOC(15728) : move_toreg_32(0xE, &D5);               // MOVEQ.L	$0E,D5
  DEF_ROMLOC(1572A) : rom_15136();                           // BSR.W	$15136
  DEF_ROMLOC(1572E) : move_toreg_8(read_8(0xFFFFF768), &D3); // MOVE.B	$F768,D3
  DEF_ROMLOC(15732) : btst_toreg_32(0x0, &D3);               // BTST.L	#$00,D3
  DEF_ROMLOC(15736) : if (CCR_EQ) goto rom_1573C;            // BEQ.B	$1573C
  DEF_ROMLOC(15738) : move_toreg_8(0xFFFFFF80, &D3);         // MOVE.B	#$80,D3
  DEF_ROMLOC(1573C) : return;                                // RTS
}
ROMFUNC(rom_157D4) {
  DEF_ROMLOC(157D4) : add_toreg_16(read_16(A0 + 0x8), &D3);  // ADD.W	8(A0),D3
  DEF_ROMLOC(157D8) : move_toreg_16(read_16(A0 + 0xC), &D2); // MOVE.W
                                                             // 12(A0),D2
  DEF_ROMLOC(157DC) : move_toreg_32(0xFFFFF768, &A4);        // LEA.L	$F768,A4
  DEF_ROMLOC(157E0) : move_tomem_8(0x0, A4);                 // MOVE.B	#$00,(A4)
  DEF_ROMLOC(157E4)
      : move_toreg_16(0xFFFFFFF0, &A3);          // MOVEA.W
                                                 // #$FFF0,A3
  DEF_ROMLOC(157E8) : move_toreg_16(0x800, &D6); // MOVE.W	#$0800,D6
  DEF_ROMLOC(157EC) : move_toreg_32(0xE, &D5);   // MOVEQ.L	$0E,D5
  DEF_ROMLOC(157EE) : rom_15274();               // BSR.W	$15274
  DEF_ROMLOC(157F2)
      : move_toreg_8(read_8(0xFFFFF768), &D3);    // MOVE.B	$F768,D3
  DEF_ROMLOC(157F6) : btst_toreg_32(0x0, &D3);    // BTST.L	#$00,D3
  DEF_ROMLOC(157FA) : if (CCR_EQ) goto rom_15800; // BEQ.B	$15800
  DEF_ROMLOC(157FC) : move_toreg_8(0x40, &D3);    // MOVE.B	#$40,D3
  DEF_ROMLOC(15800) : return;                     // RTS
}
ROMFUNC(rom_151DC) {
  DEF_ROMLOC(151DC) : rom_150C4();                     // BSR.W	$150C4
  DEF_ROMLOC(151E0) : move_toreg_16(read_16(A1), &D0); // MOVE.W	(A1),D0
  DEF_ROMLOC(151E2) : move_toreg_16(D0, &D4);          // MOVE.W	D0,D4
  DEF_ROMLOC(151E4) : and_toreg_16(0x7FF, &D0);        // ANDI.W	#$07FF,D0
  DEF_ROMLOC(151E8) : if (CCR_EQ) goto rom_151EE;      // BEQ.B	$151EE
  DEF_ROMLOC(151EA) : btst_toreg_32(D5, &D4);          // BTST.L	D5,D4
  DEF_ROMLOC(151EC) : if (!CCR_EQ) goto rom_151FC;     // BNE.B	$151FC
  DEF_ROMLOC(151EE) : move_toreg_16(0xF, &D1);         // MOVE.W	#$000F,D1
  DEF_ROMLOC(151F2) : move_toreg_16(D2, &D0);          // MOVE.W	D2,D0
  DEF_ROMLOC(151F4) : and_toreg_16(0xF, &D0);          // ANDI.W	#$000F,D0
  DEF_ROMLOC(151F8) : sub_toreg_16(D0, &D1);           // SUB.W	D0,D1
  DEF_ROMLOC(151FA) : return;                          // RTS
  DEF_ROMLOC(151FC)
      : move_toreg_32(read_32(0xFFFFF796), &A2); // MOVEA.L	$F796,A2
  DEF_ROMLOC(15200)
      : move_toreg_8(read_8((s32)A2 + (s8)0x0 + (s16)D0),
                     &D0);                         // MOVE.B	0(A2,D0),D0
  DEF_ROMLOC(15204) : and_toreg_16(0xFF, &D0);     // ANDI.W	#$00FF,D0
  DEF_ROMLOC(15208) : if (CCR_EQ) goto rom_151EE;  // BEQ.B	$151EE
  DEF_ROMLOC(1520A) : move_toreg_32(0x62900, &A2); // LEA.L	$00062900,A2
  DEF_ROMLOC(15210)
      : move_tomem_8(read_8((s32)A2 + (s8)0x0 + (s16)D0),
                     A4);                          // MOVE.B	0(A2,D0),(A4)
  DEF_ROMLOC(15214) : lsl_toreg_16(0x4, &D0);      // LSL.W	#$04,D0
  DEF_ROMLOC(15216) : move_toreg_16(D3, &D1);      // MOVE.W	D3,D1
  DEF_ROMLOC(15218) : btst_toreg_32(0xB, &D4);     // BTST.L	#$0B,D4
  DEF_ROMLOC(1521C) : if (CCR_EQ) goto rom_15222;  // BEQ.B	$15222
  DEF_ROMLOC(1521E) : not_reg_16(&D1);             // NOT.W	D1
  DEF_ROMLOC(15220) : neg_mem_8(A4);               // NEG.B	(A4)
  DEF_ROMLOC(15222) : btst_toreg_32(0xC, &D4);     // BTST.L	#$0C,D4
  DEF_ROMLOC(15226) : if (CCR_EQ) goto rom_15232;  // BEQ.B	$15232
  DEF_ROMLOC(15228) : add_tomem_8(0x40, A4);       // ADDI.B	#$40,(A4)
  DEF_ROMLOC(1522C) : neg_mem_8(A4);               // NEG.B	(A4)
  DEF_ROMLOC(1522E) : sub_tomem_8(0x40, A4);       // SUBI.B	#$40,(A4)
  DEF_ROMLOC(15232) : and_toreg_16(0xF, &D1);      // ANDI.W	#$000F,D1
  DEF_ROMLOC(15236) : add_toreg_16(D0, &D1);       // ADD.W	D0,D1
  DEF_ROMLOC(15238) : move_toreg_32(0x62A00, &A2); // LEA.L	$00062A00,A2
  DEF_ROMLOC(1523E)
      : move_toreg_8(read_8((s32)A2 + (s8)0x0 + (s16)D1),
                     &D0);                        // MOVE.B	0(A2,D1),D0
  DEF_ROMLOC(15242) : ext_reg_16(&D0);            // EXT.W	D0
  DEF_ROMLOC(15244) : eor_toreg_16(D6, &D4);      // EOR.W	D6,D4
  DEF_ROMLOC(15246) : btst_toreg_32(0xC, &D4);    // BTST.L	#$0C,D4
  DEF_ROMLOC(1524A) : if (CCR_EQ) goto rom_1524E; // BEQ.B	$1524E
  DEF_ROMLOC(1524C) : neg_reg_16(&D0);            // NEG.W	D0
  DEF_ROMLOC(1524E) : tst_reg_16(&D0);            // TST.W	D0
  DEF_ROMLOC(15250) : if (CCR_EQ) goto rom_151EE; // BEQ.B	$151EE
  DEF_ROMLOC(15252) : if (CCR_MI) goto rom_15264; // BMI.B	$15264
  DEF_ROMLOC(15254) : move_toreg_16(D2, &D1);     // MOVE.W	D2,D1
  DEF_ROMLOC(15256) : and_toreg_16(0xF, &D1);     // ANDI.W	#$000F,D1
  DEF_ROMLOC(1525A) : add_toreg_16(D1, &D0);      // ADD.W	D1,D0
  DEF_ROMLOC(1525C) : move_toreg_16(0xF, &D1);    // MOVE.W	#$000F,D1
  DEF_ROMLOC(15260) : sub_toreg_16(D0, &D1);      // SUB.W	D0,D1
  DEF_ROMLOC(15262) : return;                     // RTS
  DEF_ROMLOC(15264) : move_toreg_16(D2, &D1);     // MOVE.W	D2,D1
  DEF_ROMLOC(15266) : and_toreg_16(0xF, &D1);     // ANDI.W	#$000F,D1
  DEF_ROMLOC(1526A) : add_toreg_16(D1, &D0);      // ADD.W	D1,D0
  DEF_ROMLOC(1526C) : if (CCR_PL) goto rom_151EE; // BPL.W	$151EE
  DEF_ROMLOC(15270) : not_reg_16(&D1);            // NOT.W	D1
  DEF_ROMLOC(15272) : return;                     // RTS
}
ROMFUNC(rom_15274) {
  DEF_ROMLOC(15274) : rom_150C4();                     // BSR.W	$150C4
  DEF_ROMLOC(15278) : move_toreg_16(read_16(A1), &D0); // MOVE.W	(A1),D0
  DEF_ROMLOC(1527A) : move_toreg_16(D0, &D4);          // MOVE.W	D0,D4
  DEF_ROMLOC(1527C) : and_toreg_16(0x7FF, &D0);        // ANDI.W	#$07FF,D0
  DEF_ROMLOC(15280) : if (CCR_EQ) goto rom_15286;      // BEQ.B	$15286
  DEF_ROMLOC(15282) : btst_toreg_32(D5, &D4);          // BTST.L	D5,D4
  DEF_ROMLOC(15284) : if (!CCR_EQ) goto rom_15294;     // BNE.B	$15294
  DEF_ROMLOC(15286) : add_toreg_16(A3, &D3);           // ADD.W	A3,D3
  DEF_ROMLOC(15288) : rom_1531C();                     // BSR.W	$1531C
  DEF_ROMLOC(1528C) : sub_toreg_16(A3, &D3);           // SUB.W	A3,D3
  DEF_ROMLOC(1528E) : add_toreg_16(0x10, &D1);         // ADDI.W	#$0010,D1
  DEF_ROMLOC(15292) : return;                          // RTS
  DEF_ROMLOC(15294)
      : move_toreg_32(read_32(0xFFFFF796), &A2); // MOVEA.L	$F796,A2
  DEF_ROMLOC(15298)
      : move_toreg_8(read_8((s32)A2 + (s8)0x0 + (s16)D0),
                     &D0);                         // MOVE.B	0(A2,D0),D0
  DEF_ROMLOC(1529C) : and_toreg_16(0xFF, &D0);     // ANDI.W	#$00FF,D0
  DEF_ROMLOC(152A0) : if (CCR_EQ) goto rom_15286;  // BEQ.B	$15286
  DEF_ROMLOC(152A2) : move_toreg_32(0x62900, &A2); // LEA.L	$00062900,A2
  DEF_ROMLOC(152A8)
      : move_tomem_8(read_8((s32)A2 + (s8)0x0 + (s16)D0),
                     A4);                          // MOVE.B	0(A2,D0),(A4)
  DEF_ROMLOC(152AC) : lsl_toreg_16(0x4, &D0);      // LSL.W	#$04,D0
  DEF_ROMLOC(152AE) : move_toreg_16(D2, &D1);      // MOVE.W	D2,D1
  DEF_ROMLOC(152B0) : btst_toreg_32(0xC, &D4);     // BTST.L	#$0C,D4
  DEF_ROMLOC(152B4) : if (CCR_EQ) goto rom_152C2;  // BEQ.B	$152C2
  DEF_ROMLOC(152B6) : not_reg_16(&D1);             // NOT.W	D1
  DEF_ROMLOC(152B8) : add_tomem_8(0x40, A4);       // ADDI.B	#$40,(A4)
  DEF_ROMLOC(152BC) : neg_mem_8(A4);               // NEG.B	(A4)
  DEF_ROMLOC(152BE) : sub_tomem_8(0x40, A4);       // SUBI.B	#$40,(A4)
  DEF_ROMLOC(152C2) : btst_toreg_32(0xB, &D4);     // BTST.L	#$0B,D4
  DEF_ROMLOC(152C6) : if (CCR_EQ) goto rom_152CA;  // BEQ.B	$152CA
  DEF_ROMLOC(152C8) : neg_mem_8(A4);               // NEG.B	(A4)
  DEF_ROMLOC(152CA) : and_toreg_16(0xF, &D1);      // ANDI.W	#$000F,D1
  DEF_ROMLOC(152CE) : add_toreg_16(D0, &D1);       // ADD.W	D0,D1
  DEF_ROMLOC(152D0) : move_toreg_32(0x63A00, &A2); // LEA.L	$00063A00,A2
  DEF_ROMLOC(152D6)
      : move_toreg_8(read_8((s32)A2 + (s8)0x0 + (s16)D1),
                     &D0);                        // MOVE.B	0(A2,D1),D0
  DEF_ROMLOC(152DA) : ext_reg_16(&D0);            // EXT.W	D0
  DEF_ROMLOC(152DC) : eor_toreg_16(D6, &D4);      // EOR.W	D6,D4
  DEF_ROMLOC(152DE) : btst_toreg_32(0xB, &D4);    // BTST.L	#$0B,D4
  DEF_ROMLOC(152E2) : if (CCR_EQ) goto rom_152E6; // BEQ.B	$152E6
  DEF_ROMLOC(152E4) : neg_reg_16(&D0);            // NEG.W	D0
  DEF_ROMLOC(152E6) : tst_reg_16(&D0);            // TST.W	D0
  DEF_ROMLOC(152E8) : if (CCR_EQ) goto rom_15286; // BEQ.B	$15286
  DEF_ROMLOC(152EA) : if (CCR_MI) goto rom_15302; // BMI.B	$15302
  DEF_ROMLOC(152EC) : cmp_toreg_8(0x10, &D0);     // CMPI.B	#$10,D0
  DEF_ROMLOC(152F0) : if (CCR_EQ) goto rom_1530E; // BEQ.B	$1530E
  DEF_ROMLOC(152F2) : move_toreg_16(D3, &D1);     // MOVE.W	D3,D1
  DEF_ROMLOC(152F4) : and_toreg_16(0xF, &D1);     // ANDI.W	#$000F,D1
  DEF_ROMLOC(152F8) : add_toreg_16(D1, &D0);      // ADD.W	D1,D0
  DEF_ROMLOC(152FA) : move_toreg_16(0xF, &D1);    // MOVE.W	#$000F,D1
  DEF_ROMLOC(152FE) : sub_toreg_16(D0, &D1);      // SUB.W	D0,D1
  DEF_ROMLOC(15300) : return;                     // RTS
  DEF_ROMLOC(15302) : move_toreg_16(D3, &D1);     // MOVE.W	D3,D1
  DEF_ROMLOC(15304) : and_toreg_16(0xF, &D1);     // ANDI.W	#$000F,D1
  DEF_ROMLOC(15308) : add_toreg_16(D1, &D0);      // ADD.W	D1,D0
  DEF_ROMLOC(1530A) : if (CCR_PL) goto rom_15286; // BPL.W	$15286
  DEF_ROMLOC(1530E) : sub_toreg_16(A3, &D3);      // SUB.W	A3,D3
  DEF_ROMLOC(15310) : rom_1531C();                // BSR.W	$1531C
  DEF_ROMLOC(15314) : add_toreg_16(A3, &D3);      // ADD.W	A3,D3
  DEF_ROMLOC(15316) : sub_toreg_16(0x10, &D1);    // SUBI.W	#$0010,D1
  DEF_ROMLOC(1531A) : return;                     // RTS
}
ROMFUNC(rom_1531C) {
  DEF_ROMLOC(1531C) : rom_150C4();                     // BSR.W	$150C4
  DEF_ROMLOC(15320) : move_toreg_16(read_16(A1), &D0); // MOVE.W	(A1),D0
  DEF_ROMLOC(15322) : move_toreg_16(D0, &D4);          // MOVE.W	D0,D4
  DEF_ROMLOC(15324) : and_toreg_16(0x7FF, &D0);        // ANDI.W	#$07FF,D0
  DEF_ROMLOC(15328) : if (CCR_EQ) goto rom_1532E;      // BEQ.B	$1532E
  DEF_ROMLOC(1532A) : btst_toreg_32(D5, &D4);          // BTST.L	D5,D4
  DEF_ROMLOC(1532C) : if (!CCR_EQ) goto rom_1533C;     // BNE.B	$1533C
  DEF_ROMLOC(1532E) : move_toreg_16(0xF, &D1);         // MOVE.W	#$000F,D1
  DEF_ROMLOC(15332) : move_toreg_16(D3, &D0);          // MOVE.W	D3,D0
  DEF_ROMLOC(15334) : and_toreg_16(0xF, &D0);          // ANDI.W	#$000F,D0
  DEF_ROMLOC(15338) : sub_toreg_16(D0, &D1);           // SUB.W	D0,D1
  DEF_ROMLOC(1533A) : return;                          // RTS
  DEF_ROMLOC(1533C)
      : move_toreg_32(read_32(0xFFFFF796), &A2); // MOVEA.L	$F796,A2
  DEF_ROMLOC(15340)
      : move_toreg_8(read_8((s32)A2 + (s8)0x0 + (s16)D0),
                     &D0);                         // MOVE.B	0(A2,D0),D0
  DEF_ROMLOC(15344) : and_toreg_16(0xFF, &D0);     // ANDI.W	#$00FF,D0
  DEF_ROMLOC(15348) : if (CCR_EQ) goto rom_1532E;  // BEQ.B	$1532E
  DEF_ROMLOC(1534A) : move_toreg_32(0x62900, &A2); // LEA.L	$00062900,A2
  DEF_ROMLOC(15350)
      : move_tomem_8(read_8((s32)A2 + (s8)0x0 + (s16)D0),
                     A4);                          // MOVE.B	0(A2,D0),(A4)
  DEF_ROMLOC(15354) : lsl_toreg_16(0x4, &D0);      // LSL.W	#$04,D0
  DEF_ROMLOC(15356) : move_toreg_16(D2, &D1);      // MOVE.W	D2,D1
  DEF_ROMLOC(15358) : btst_toreg_32(0xC, &D4);     // BTST.L	#$0C,D4
  DEF_ROMLOC(1535C) : if (CCR_EQ) goto rom_1536A;  // BEQ.B	$1536A
  DEF_ROMLOC(1535E) : not_reg_16(&D1);             // NOT.W	D1
  DEF_ROMLOC(15360) : add_tomem_8(0x40, A4);       // ADDI.B	#$40,(A4)
  DEF_ROMLOC(15364) : neg_mem_8(A4);               // NEG.B	(A4)
  DEF_ROMLOC(15366) : sub_tomem_8(0x40, A4);       // SUBI.B	#$40,(A4)
  DEF_ROMLOC(1536A) : btst_toreg_32(0xB, &D4);     // BTST.L	#$0B,D4
  DEF_ROMLOC(1536E) : if (CCR_EQ) goto rom_15372;  // BEQ.B	$15372
  DEF_ROMLOC(15370) : neg_mem_8(A4);               // NEG.B	(A4)
  DEF_ROMLOC(15372) : and_toreg_16(0xF, &D1);      // ANDI.W	#$000F,D1
  DEF_ROMLOC(15376) : add_toreg_16(D0, &D1);       // ADD.W	D0,D1
  DEF_ROMLOC(15378) : move_toreg_32(0x63A00, &A2); // LEA.L	$00063A00,A2
  DEF_ROMLOC(1537E)
      : move_toreg_8(read_8((s32)A2 + (s8)0x0 + (s16)D1),
                     &D0);                        // MOVE.B	0(A2,D1),D0
  DEF_ROMLOC(15382) : ext_reg_16(&D0);            // EXT.W	D0
  DEF_ROMLOC(15384) : eor_toreg_16(D6, &D4);      // EOR.W	D6,D4
  DEF_ROMLOC(15386) : btst_toreg_32(0xB, &D4);    // BTST.L	#$0B,D4
  DEF_ROMLOC(1538A) : if (CCR_EQ) goto rom_1538E; // BEQ.B	$1538E
  DEF_ROMLOC(1538C) : neg_reg_16(&D0);            // NEG.W	D0
  DEF_ROMLOC(1538E) : tst_reg_16(&D0);            // TST.W	D0
  DEF_ROMLOC(15390) : if (CCR_EQ) goto rom_1532E; // BEQ.B	$1532E
  DEF_ROMLOC(15392) : if (CCR_MI) goto rom_153A4; // BMI.B	$153A4
  DEF_ROMLOC(15394) : move_toreg_16(D3, &D1);     // MOVE.W	D3,D1
  DEF_ROMLOC(15396) : and_toreg_16(0xF, &D1);     // ANDI.W	#$000F,D1
  DEF_ROMLOC(1539A) : add_toreg_16(D1, &D0);      // ADD.W	D1,D0
  DEF_ROMLOC(1539C) : move_toreg_16(0xF, &D1);    // MOVE.W	#$000F,D1
  DEF_ROMLOC(153A0) : sub_toreg_16(D0, &D1);      // SUB.W	D0,D1
  DEF_ROMLOC(153A2) : return;                     // RTS
  DEF_ROMLOC(153A4) : move_toreg_16(D3, &D1);     // MOVE.W	D3,D1
  DEF_ROMLOC(153A6) : and_toreg_16(0xF, &D1);     // ANDI.W	#$000F,D1
  DEF_ROMLOC(153AA) : add_toreg_16(D1, &D0);      // ADD.W	D1,D0
  DEF_ROMLOC(153AC) : if (CCR_PL) goto rom_1532E; // BPL.W	$1532E
  DEF_ROMLOC(153B0) : not_reg_16(&D1);            // NOT.W	D1
  DEF_ROMLOC(153B2) : return;                     // RTS
}
ROMFUNC(rom_150C4) {
  DEF_ROMLOC(150C4) : move_toreg_16(D2, &D0);         // MOVE.W	D2,D0
  DEF_ROMLOC(150C6) : lsr_toreg_16(0x1, &D0);         // LSR.W	#$01,D0
  DEF_ROMLOC(150C8) : and_toreg_16(0x380, &D0);       // ANDI.W	#$0380,D0
  DEF_ROMLOC(150CC) : move_toreg_16(D3, &D1);         // MOVE.W	D3,D1
  DEF_ROMLOC(150CE) : lsr_toreg_16(0x8, &D1);         // LSR.W	#$08,D1
  DEF_ROMLOC(150D0) : and_toreg_16(0x7F, &D1);        // ANDI.W	#$007F,D1
  DEF_ROMLOC(150D4) : add_toreg_16(D1, &D0);          // ADD.W	D1,D0
  DEF_ROMLOC(150D6) : move_toreg_32(0xFFFFFFFF, &D1); // MOVEQ.L	$FF,D1
  DEF_ROMLOC(150D8) : move_toreg_32(0xFFFFA400, &A1); // LEA.L	$A400,A1
  DEF_ROMLOC(150DC)
      : move_toreg_8(read_8((s32)A1 + (s8)0x0 + (s16)D0),
                     &D1);                         // MOVE.B	0(A1,D0),D1
  DEF_ROMLOC(150E0) : if (CCR_EQ) goto rom_150FE;  // BEQ.B	$150FE
  DEF_ROMLOC(150E2) : if (CCR_MI) goto rom_15102;  // BMI.B	$15102
  DEF_ROMLOC(150E4) : sub_toreg_8(0x1, &D1);       // SUBQ.B	#$01,D1
  DEF_ROMLOC(150E6) : ext_reg_16(&D1);             // EXT.W	D1
  DEF_ROMLOC(150E8) : ror_toreg_16(0x7, &D1);      // ROR.W	#$07,D1
  DEF_ROMLOC(150EA) : move_toreg_16(D2, &D0);      // MOVE.W	D2,D0
  DEF_ROMLOC(150EC) : add_toreg_16(D0, &D0);       // ADD.W	D0,D0
  DEF_ROMLOC(150EE) : and_toreg_16(0x1E0, &D0);    // ANDI.W	#$01E0,D0
  DEF_ROMLOC(150F2) : add_toreg_16(D0, &D1);       // ADD.W	D0,D1
  DEF_ROMLOC(150F4) : move_toreg_16(D3, &D0);      // MOVE.W	D3,D0
  DEF_ROMLOC(150F6) : lsr_toreg_16(0x3, &D0);      // LSR.W	#$03,D0
  DEF_ROMLOC(150F8) : and_toreg_16(0x1E, &D0);     // ANDI.W	#$001E,D0
  DEF_ROMLOC(150FC) : add_toreg_16(D0, &D1);       // ADD.W	D0,D1
  DEF_ROMLOC(150FE) : move_toreg_32(D1, &A1);      // MOVEA.L	D1,A1
  DEF_ROMLOC(15100) : return;                      // RTS
  DEF_ROMLOC(15102) : and_toreg_16(0x7F, &D1);     // ANDI.W	#$007F,D1
  DEF_ROMLOC(15106) : btst_tomem_8(0x6, A0 + 0x1); // BTST.B	#$06,1(A0)
  DEF_ROMLOC(1510C) : if (CCR_EQ) goto rom_1511A;  // BEQ.B	$1511A
  DEF_ROMLOC(1510E) : add_toreg_16(0x1, &D1);      // ADDQ.W	#$01,D1
  DEF_ROMLOC(15110) : cmp_toreg_16(0x29, &D1);     // CMPI.W	#$0029,D1
  DEF_ROMLOC(15114) : if (!CCR_EQ) goto rom_1511A; // BNE.B	$1511A
  DEF_ROMLOC(15116) : move_toreg_16(0x51, &D1);    // MOVE.W	#$0051,D1
  DEF_ROMLOC(1511A) : sub_toreg_8(0x1, &D1);       // SUBQ.B	#$01,D1
  DEF_ROMLOC(1511C) : ror_toreg_16(0x7, &D1);      // ROR.W	#$07,D1
  DEF_ROMLOC(1511E) : move_toreg_16(D2, &D0);      // MOVE.W	D2,D0
  DEF_ROMLOC(15120) : add_toreg_16(D0, &D0);       // ADD.W	D0,D0
  DEF_ROMLOC(15122) : and_toreg_16(0x1E0, &D0);    // ANDI.W	#$01E0,D0
  DEF_ROMLOC(15126) : add_toreg_16(D0, &D1);       // ADD.W	D0,D1
  DEF_ROMLOC(15128) : move_toreg_16(D3, &D0);      // MOVE.W	D3,D0
  DEF_ROMLOC(1512A) : lsr_toreg_16(0x3, &D0);      // LSR.W	#$03,D0
  DEF_ROMLOC(1512C) : and_toreg_16(0x1E, &D0);     // ANDI.W	#$001E,D0
  DEF_ROMLOC(15130) : add_toreg_16(D0, &D1);       // ADD.W	D0,D1
  DEF_ROMLOC(15132) : move_toreg_32(D1, &A1);      // MOVEA.L	D1,A1
  DEF_ROMLOC(15134) : return;                      // RTS
}
ROMFUNC(rom_15136) {
  DEF_ROMLOC(15136) : rom_150C4();                     // BSR.B	$150C4
  DEF_ROMLOC(15138) : move_toreg_16(read_16(A1), &D0); // MOVE.W	(A1),D0
  DEF_ROMLOC(1513A) : move_toreg_16(D0, &D4);          // MOVE.W	D0,D4
  DEF_ROMLOC(1513C) : and_toreg_16(0x7FF, &D0);        // ANDI.W	#$07FF,D0
  DEF_ROMLOC(15140) : if (CCR_EQ) goto rom_15146;      // BEQ.B	$15146
  DEF_ROMLOC(15142) : btst_toreg_32(D5, &D4);          // BTST.L	D5,D4
  DEF_ROMLOC(15144) : if (!CCR_EQ) goto rom_15154;     // BNE.B	$15154
  DEF_ROMLOC(15146) : add_toreg_16(A3, &D2);           // ADD.W	A3,D2
  DEF_ROMLOC(15148) : rom_151DC();                     // BSR.W	$151DC
  DEF_ROMLOC(1514C) : sub_toreg_16(A3, &D2);           // SUB.W	A3,D2
  DEF_ROMLOC(1514E) : add_toreg_16(0x10, &D1);         // ADDI.W	#$0010,D1
  DEF_ROMLOC(15152) : return;                          // RTS
  DEF_ROMLOC(15154)
      : move_toreg_32(read_32(0xFFFFF796), &A2); // MOVEA.L	$F796,A2
  DEF_ROMLOC(15158)
      : move_toreg_8(read_8((s32)A2 + (s8)0x0 + (s16)D0),
                     &D0);                         // MOVE.B	0(A2,D0),D0
  DEF_ROMLOC(1515C) : and_toreg_16(0xFF, &D0);     // ANDI.W	#$00FF,D0
  DEF_ROMLOC(15160) : if (CCR_EQ) goto rom_15146;  // BEQ.B	$15146
  DEF_ROMLOC(15162) : move_toreg_32(0x62900, &A2); // LEA.L	$00062900,A2
  DEF_ROMLOC(15168)
      : move_tomem_8(read_8((s32)A2 + (s8)0x0 + (s16)D0),
                     A4);                          // MOVE.B	0(A2,D0),(A4)
  DEF_ROMLOC(1516C) : lsl_toreg_16(0x4, &D0);      // LSL.W	#$04,D0
  DEF_ROMLOC(1516E) : move_toreg_16(D3, &D1);      // MOVE.W	D3,D1
  DEF_ROMLOC(15170) : btst_toreg_32(0xB, &D4);     // BTST.L	#$0B,D4
  DEF_ROMLOC(15174) : if (CCR_EQ) goto rom_1517A;  // BEQ.B	$1517A
  DEF_ROMLOC(15176) : not_reg_16(&D1);             // NOT.W	D1
  DEF_ROMLOC(15178) : neg_mem_8(A4);               // NEG.B	(A4)
  DEF_ROMLOC(1517A) : btst_toreg_32(0xC, &D4);     // BTST.L	#$0C,D4
  DEF_ROMLOC(1517E) : if (CCR_EQ) goto rom_1518A;  // BEQ.B	$1518A
  DEF_ROMLOC(15180) : add_tomem_8(0x40, A4);       // ADDI.B	#$40,(A4)
  DEF_ROMLOC(15184) : neg_mem_8(A4);               // NEG.B	(A4)
  DEF_ROMLOC(15186) : sub_tomem_8(0x40, A4);       // SUBI.B	#$40,(A4)
  DEF_ROMLOC(1518A) : and_toreg_16(0xF, &D1);      // ANDI.W	#$000F,D1
  DEF_ROMLOC(1518E) : add_toreg_16(D0, &D1);       // ADD.W	D0,D1
  DEF_ROMLOC(15190) : move_toreg_32(0x62A00, &A2); // LEA.L	$00062A00,A2
  DEF_ROMLOC(15196)
      : move_toreg_8(read_8((s32)A2 + (s8)0x0 + (s16)D1),
                     &D0);                        // MOVE.B	0(A2,D1),D0
  DEF_ROMLOC(1519A) : ext_reg_16(&D0);            // EXT.W	D0
  DEF_ROMLOC(1519C) : eor_toreg_16(D6, &D4);      // EOR.W	D6,D4
  DEF_ROMLOC(1519E) : btst_toreg_32(0xC, &D4);    // BTST.L	#$0C,D4
  DEF_ROMLOC(151A2) : if (CCR_EQ) goto rom_151A6; // BEQ.B	$151A6
  DEF_ROMLOC(151A4) : neg_reg_16(&D0);            // NEG.W	D0
  DEF_ROMLOC(151A6) : tst_reg_16(&D0);            // TST.W	D0
  DEF_ROMLOC(151A8) : if (CCR_EQ) goto rom_15146; // BEQ.B	$15146
  DEF_ROMLOC(151AA) : if (CCR_MI) goto rom_151C2; // BMI.B	$151C2
  DEF_ROMLOC(151AC) : cmp_toreg_8(0x10, &D0);     // CMPI.B	#$10,D0
  DEF_ROMLOC(151B0) : if (CCR_EQ) goto rom_151CE; // BEQ.B	$151CE
  DEF_ROMLOC(151B2) : move_toreg_16(D2, &D1);     // MOVE.W	D2,D1
  DEF_ROMLOC(151B4) : and_toreg_16(0xF, &D1);     // ANDI.W	#$000F,D1
  DEF_ROMLOC(151B8) : add_toreg_16(D1, &D0);      // ADD.W	D1,D0
  DEF_ROMLOC(151BA) : move_toreg_16(0xF, &D1);    // MOVE.W	#$000F,D1
  DEF_ROMLOC(151BE) : sub_toreg_16(D0, &D1);      // SUB.W	D0,D1
  DEF_ROMLOC(151C0) : return;                     // RTS
  DEF_ROMLOC(151C2) : move_toreg_16(D2, &D1);     // MOVE.W	D2,D1
  DEF_ROMLOC(151C4) : and_toreg_16(0xF, &D1);     // ANDI.W	#$000F,D1
  DEF_ROMLOC(151C8) : add_toreg_16(D1, &D0);      // ADD.W	D1,D0
  DEF_ROMLOC(151CA) : if (CCR_PL) goto rom_15146; // BPL.W	$15146
  DEF_ROMLOC(151CE) : sub_toreg_16(A3, &D2);      // SUB.W	A3,D2
  DEF_ROMLOC(151D0) : rom_151DC();                // BSR.W	$151DC
  DEF_ROMLOC(151D4) : add_toreg_16(A3, &D2);      // ADD.W	A3,D2
  DEF_ROMLOC(151D6) : sub_toreg_16(0x10, &D1);    // SUBI.W	#$0010,D1
  DEF_ROMLOC(151DA) : return;                     // RTS
}
ROMFUNC(rom_153B4) { return; }
ROMFUNC(rom_1B59A) {
  DEF_ROMLOC(1B59C)
      : move_toreg_16(read_16(A0 + 0x8), &D2); // MOVE.W	8(A0),D2
  DEF_ROMLOC(1B5A0)
      : move_toreg_16(read_16(A0 + 0xC), &D3); // MOVE.W	12(A0),D3
  DEF_ROMLOC(1B5A4) : sub_toreg_16(0x8, &D2);  // SUBQ.W	#$08,D2
  DEF_ROMLOC(1B5A6) : move_toreg_32(0x0, &D5); // MOVEQ.L	$00,D5
  DEF_ROMLOC(1B5A8)
      : move_toreg_8(read_8(A0 + 0x16), &D5);         // MOVE.B
                                                      // 22(A0),D5
  DEF_ROMLOC(1B5AC) : sub_toreg_8(0x3, &D5);          // SUBQ.B	#$03,D5
  DEF_ROMLOC(1B5AE) : sub_toreg_16(D5, &D3);          // SUB.W	D5,D3
  DEF_ROMLOC(1B5B0) : cmp_tomem_8(0x39, A0 + 0x1A);   // CMPI.B	#$39,26(A0)
  DEF_ROMLOC(1B5B6) : if (!CCR_EQ) goto rom_1B5BE;    // BNE.B	$1B5BE
  DEF_ROMLOC(1B5B8) : add_toreg_16(0xC, &D3);         // ADDI.W	#$000C,D3
  DEF_ROMLOC(1B5BC) : move_toreg_32(0xA, &D5);        // MOVEQ.L	$0A,D5
  DEF_ROMLOC(1B5BE) : move_toreg_16(0x10, &D4);       // MOVE.W	#$0010,D4
  DEF_ROMLOC(1B5C2) : add_toreg_16(D5, &D5);          // ADD.W	D5,D5
  DEF_ROMLOC(1B5C4) : move_toreg_32(0xFFFFD800, &A1); // LEA.L	$D800,A1
  DEF_ROMLOC(1B5C8) : move_toreg_16(0x5F, &D6);       // MOVE.W	#$005F,D6
  DEF_ROMLOC(1B5CC) : tst_mem_8(A1 + 0x1);            // TST.B	1(A1)
  DEF_ROMLOC(1B5D0) : if (CCR_PL) goto rom_1B5D8;     // BPL.B	$1B5D8
  DEF_ROMLOC(1B5D2)
      : move_toreg_8(read_8(A1 + 0x20), &D0);        // MOVE.B
                                                     // 32(A1),D0
  DEF_ROMLOC(1B5D6) : if (!CCR_EQ) goto rom_1B62C;   // BNE.B	$1B62C
  DEF_ROMLOC(1B5D8) : move_toreg_32(A1 + 0x40, &A1); // LEA.L	64(A1),A1
  DEF_ROMLOC(1B5DC) : dec_reg_16(&D6);
  if ((D6 & 0xffff) != 0xffff)
    goto rom_1B5CC;                            // DBF.W	D6,$1B5CC
  DEF_ROMLOC(1B5E0) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(1B5E2) : return;                  // RTS
  DEF_ROMLOC(1B62C) : and_toreg_16(0x3F, &D0); // ANDI.W	#$003F,D0
  DEF_ROMLOC(1B630) : add_toreg_16(D0, &D0);   // ADD.W	D0,D0
  DEF_ROMLOC(1B632)
      : move_toreg_32(0x1B5E2 + (s16)(D0 & 0xffff),
                      &A2);                            // LEA.L	-82(PC,D0),A2
  DEF_ROMLOC(1B636) : move_toreg_32(0x0, &D1);         // MOVEQ.L	$00,D1
  DEF_ROMLOC(1B638) : move_toreg_8(read_8(A2++), &D1); // MOVE.B	(A2)+,D1
  DEF_ROMLOC(1B63A)
      : move_toreg_16(read_16(A1 + 0x8), &D0);         // MOVE.W	8(A1),D0
  DEF_ROMLOC(1B63E) : sub_toreg_16(D1, &D0);           // SUB.W	D1,D0
  DEF_ROMLOC(1B640) : sub_toreg_16(D2, &D0);           // SUB.W	D2,D0
  DEF_ROMLOC(1B642) : if (CCR_CC) goto rom_1B64E;      // BCC.B	$1B64E
  DEF_ROMLOC(1B644) : add_toreg_16(D1, &D1);           // ADD.W	D1,D1
  DEF_ROMLOC(1B646) : add_toreg_16(D1, &D0);           // ADD.W	D1,D0
  DEF_ROMLOC(1B648) : if (CCR_CS) goto rom_1B654;      // BCS.B	$1B654
  DEF_ROMLOC(1B64A) : goto rom_1B5D8;                  // BRA.W	$1B5D8
  DEF_ROMLOC(1B64E) : cmp_toreg_16(D4, &D0);           // CMP.W	D4,D0
  DEF_ROMLOC(1B650) : if (CCR_HI) goto rom_1B5D8;      // BHI.W	$1B5D8
  DEF_ROMLOC(1B654) : move_toreg_32(0x0, &D1);         // MOVEQ.L	$00,D1
  DEF_ROMLOC(1B656) : move_toreg_8(read_8(A2++), &D1); // MOVE.B	(A2)+,D1
  DEF_ROMLOC(1B658)
      : move_toreg_16(read_16(A1 + 0xC), &D0);    // MOVE.W	12(A1),D0
  DEF_ROMLOC(1B65C) : sub_toreg_16(D1, &D0);      // SUB.W	D1,D0
  DEF_ROMLOC(1B65E) : sub_toreg_16(D3, &D0);      // SUB.W	D3,D0
  DEF_ROMLOC(1B660) : if (CCR_CC) goto rom_1B66C; // BCC.B	$1B66C
  DEF_ROMLOC(1B662) : add_toreg_16(D1, &D1);      // ADD.W	D1,D1
  DEF_ROMLOC(1B664) : add_toreg_16(D0, &D1);      // ADD.W	D0,D1
  DEF_ROMLOC(1B666) : if (CCR_CS) goto rom_1B672; // BCS.B	$1B672
  DEF_ROMLOC(1B668) : goto rom_1B5D8;             // BRA.W	$1B5D8
  DEF_ROMLOC(1B66C) : cmp_toreg_16(D5, &D0);      // CMP.W	D5,D0
  DEF_ROMLOC(1B66E) : if (CCR_HI) goto rom_1B5D8; // BHI.W	$1B5D8
  DEF_ROMLOC(1B672)
      : move_toreg_8(read_8(A1 + 0x20), &D1);       // MOVE.B	32(A1),D1
  DEF_ROMLOC(1B676) : and_toreg_8(0xFFFFFFC0, &D1); // ANDI.B	#$C0,D1
  DEF_ROMLOC(1B67A) : if (CCR_EQ) {
    rom_1B6E6();
    return;
  }                                                 // BEQ.W	$1B6E6
  DEF_ROMLOC(1B67E) : cmp_toreg_8(0xFFFFFFC0, &D1); // CMPI.B	#$C0,D1
  DEF_ROMLOC(1B682) : if (CCR_EQ) {
    rom_1B8A6();
    return;
  }                                   // BEQ.W	$1B8A6
  DEF_ROMLOC(1B686) : tst_reg_8(&D1); // TST.B	D1
  DEF_ROMLOC(1B688) : if (CCR_MI) {
    rom_1B796();
    return;
  } // BMI.W	$1B796
  DEF_ROMLOC(1B68C)
      : move_toreg_8(read_8(A1 + 0x20), &D0);        // MOVE.B
                                                     // 32(A1),D0
  DEF_ROMLOC(1B690) : and_toreg_8(0x3F, &D0);        // ANDI.B	#$3F,D0
  DEF_ROMLOC(1B694) : cmp_toreg_8(0x6, &D0);         // CMPI.B	#$06,D0
  DEF_ROMLOC(1B698) : if (CCR_EQ) goto rom_1B6AA;    // BEQ.B	$1B6AA
  DEF_ROMLOC(1B69A) : cmp_tomem_16(0x5A, A0 + 0x30); // CMPI.W	#$005A,48(A0)
  DEF_ROMLOC(1B6A0) : if (CCR_CC) goto rom_1B6A8;    // BCC.W	$1B6A8
  DEF_ROMLOC(1B6A4) : add_tomem_8(0x2, A1 + 0x24);   // ADDQ.B	#$02,36(A1)
  DEF_ROMLOC(1B6A8) : return;                        // RTS
  DEF_ROMLOC(1B6AA) : tst_mem_16(A0 + 0x12);         // TST.W	18(A0)
  DEF_ROMLOC(1B6AE) : if (CCR_PL) goto rom_1B6D4;    // BPL.B	$1B6D4
  DEF_ROMLOC(1B6B0)
      : move_toreg_16(read_16(A0 + 0xC), &D0); // MOVE.W	12(A0),D0
  DEF_ROMLOC(1B6B4) : sub_toreg_16(0x10, &D0); // SUBI.W	#$0010,D0
  DEF_ROMLOC(1B6B8)
      : cmp_toreg_16(read_16(A1 + 0xC), &D0);     // CMP.W	12(A1),D0
  DEF_ROMLOC(1B6BC) : if (CCR_CS) goto rom_1B6E4; // BCS.B	$1B6E4
  DEF_ROMLOC(1B6BE) : neg_mem_16(A0 + 0x12);      // NEG.W	18(A0)
  DEF_ROMLOC(1B6C2)
      : move_tomem_16(0xFFFFFE80, A1 + 0x12);      // MOVE.W	#$FE80,18(A1)
  DEF_ROMLOC(1B6C8) : tst_mem_8(A1 + 0x25);        // TST.B	37(A1)
  DEF_ROMLOC(1B6CC) : if (!CCR_EQ) goto rom_1B6E4; // BNE.B	$1B6E4
  DEF_ROMLOC(1B6CE) : add_tomem_8(0x4, A1 + 0x25); // ADDQ.B	#$04,37(A1)
  DEF_ROMLOC(1B6D2) : return;                      // RTS
  DEF_ROMLOC(1B6D4) : cmp_tomem_8(0x2, A0 + 0x1C); // CMPI.B	#$02,28(A0)
  DEF_ROMLOC(1B6DA) : if (!CCR_EQ) goto rom_1B6E4; // BNE.B	$1B6E4
  DEF_ROMLOC(1B6DC) : neg_mem_16(A0 + 0x12);       // NEG.W	18(A0)
  DEF_ROMLOC(1B6E0) : add_tomem_8(0x2, A1 + 0x24); // ADDQ.B	#$02,36(A1)
  DEF_ROMLOC(1B6E4) : return;                      // RTS
}
ROMFUNC(rom_1B6E6) {
  DEF_ROMLOC(1B6E6) : tst_mem_8(0xFFFFFE2D);       // TST.B	$FE2D
  DEF_ROMLOC(1B6EA) : if (!CCR_EQ) goto rom_1B6F6; // BNE.B	$1B6F6
  DEF_ROMLOC(1B6EC) : cmp_tomem_8(0x2, A0 + 0x1C); // CMPI.B	#$02,28(A0)
  DEF_ROMLOC(1B6F2) : if (!CCR_EQ) {
    rom_1B796();
    return;
  }                                                 // BNE.W	$1B796
  DEF_ROMLOC(1B6F6) : tst_mem_8(A1 + 0x21);         // TST.B	33(A1)
  DEF_ROMLOC(1B6FA) : if (CCR_EQ) goto rom_1B720;   // BEQ.B	$1B720
  DEF_ROMLOC(1B6FC) : neg_mem_16(A0 + 0x10);        // NEG.W	16(A0)
  DEF_ROMLOC(1B700) : neg_mem_16(A0 + 0x12);        // NEG.W	18(A0)
  DEF_ROMLOC(1B704) : asr_mem_16(A0 + 0x10);        // ASR.W	16(A0)
  DEF_ROMLOC(1B708) : asr_mem_16(A0 + 0x12);        // ASR.W	18(A0)
  DEF_ROMLOC(1B70C) : move_tomem_8(0x0, A1 + 0x20); // MOVE.B	#$00,32(A1)
  DEF_ROMLOC(1B712) : sub_tomem_8(0x1, A1 + 0x21);  // SUBQ.B	#$01,33(A1)
  DEF_ROMLOC(1B716) : if (!CCR_EQ) goto rom_1B71E;  // BNE.B	$1B71E
  DEF_ROMLOC(1B718) : bset_tomem_8(0x7, A1 + 0x22); // BSET.B	#$07,34(A1)
  DEF_ROMLOC(1B71E) : return;                       // RTS
  DEF_ROMLOC(1B720) : bset_tomem_8(0x7, A1 + 0x22); // BSET.B	#$07,34(A1)
  DEF_ROMLOC(1B726) : move_toreg_32(0x0, &D0);      // MOVEQ.L	$00,D0
  DEF_ROMLOC(1B728)
      : move_toreg_16(read_16(0xFFFFF7D0), &D0);     // MOVE.W	$F7D0,D0
  DEF_ROMLOC(1B72C) : add_tomem_16(0x2, 0xFFFFF7D0); // ADDQ.W	#$02,$F7D0
  DEF_ROMLOC(1B730) : cmp_toreg_16(0x6, &D0);        // CMPI.W	#$0006,D0
  DEF_ROMLOC(1B734) : if (CCR_CS) goto rom_1B738;    // BCS.B	$1B738
  DEF_ROMLOC(1B736) : move_toreg_32(0x6, &D0);       // MOVEQ.L	$06,D0
  DEF_ROMLOC(1B738) : move_tomem_16(D0, A1 + 0x3E);  // MOVE.W	D0,62(A1)
  DEF_ROMLOC(1B73C)
      : move_toreg_16(read_16(0x1B788 + (s16)(D0 & 0xffff)),
                      &D0);                           // MOVE.W	74(PC,D0),D0
  DEF_ROMLOC(1B740) : cmp_tomem_16(0x20, 0xFFFFF7D0); // CMPI.W	#$0020,$F7D0
  DEF_ROMLOC(1B746) : if (CCR_CS) goto rom_1B752;     // BCS.B	$1B752
  DEF_ROMLOC(1B748) : move_toreg_16(0x3E8, &D0);      // MOVE.W	#$03E8,D0
  DEF_ROMLOC(1B74C) : move_tomem_16(0xA, A1 + 0x3E);  // MOVE.W	#$000A,62(A1)
  DEF_ROMLOC(1B752) : rom_1CE42();                    // BSR.W	$1CE42
  DEF_ROMLOC(1B756)
      : move_tomem_8(OBJ_EXPLOSIONITEM,
                     A1 + offsetof(object, id));    // MOVE.B	#$27,0(A1)
  DEF_ROMLOC(1B75C) : move_tomem_8(0x0, A1 + 0x24); // MOVE.B	#$00,36(A1)
  DEF_ROMLOC(1B762) : tst_mem_16(A0 + 0x12);        // TST.W	18(A0)
  DEF_ROMLOC(1B766) : if (CCR_MI) goto rom_1B778;   // BMI.B	$1B778
  DEF_ROMLOC(1B768)
      : move_toreg_16(read_16(A0 + 0xC), &D0); // MOVE.W	12(A0),D0
  DEF_ROMLOC(1B76C)
      : cmp_toreg_16(read_16(A1 + 0xC), &D0);         // CMP.W
                                                      // 12(A1),D0
  DEF_ROMLOC(1B770) : if (CCR_CC) goto rom_1B780;     // BCC.B	$1B780
  DEF_ROMLOC(1B772) : neg_mem_16(A0 + 0x12);          // NEG.W	18(A0)
  DEF_ROMLOC(1B776) : return;                         // RTS
  DEF_ROMLOC(1B778) : add_tomem_16(0x100, A0 + 0x12); // ADDI.W	#$0100,18(A0)
  DEF_ROMLOC(1B77E) : return;                         // RTS
  DEF_ROMLOC(1B780) : sub_tomem_16(0x100, A0 + 0x12); // SUBI.W	#$0100,18(A0)
  DEF_ROMLOC(1B786) : return;                         // RTS
}
ROMFUNC(rom_1B790) {
  DEF_ROMLOC(1B790) : bset_tomem_8(0x7, A1 + 0x22); // BSET.B	#$07,34(A1)
  rom_1B796();
}
ROMFUNC(rom_1B796) {
  DEF_ROMLOC(1B796) : tst_mem_8(0xFFFFFE2D);          // TST.B	$FE2D
  DEF_ROMLOC(1B79A) : if (CCR_EQ) goto rom_1B7A0;     // BEQ.B	$1B7A0
  DEF_ROMLOC(1B79C) : move_toreg_32(0xFFFFFFFF, &D0); // MOVEQ.L	$FF,D0
  DEF_ROMLOC(1B79E) : return;                         // RTS
  DEF_ROMLOC(1B7A0)
      : DEF_ROMLOC(1B7A2) : tst_mem_16(A0 + 0x30); // TST.W	48(A0)
  DEF_ROMLOC(1B7A6) : if (!CCR_EQ) goto rom_1B79C; // BNE.B	$1B79C
  DEF_ROMLOC(1B7A8) : move_toreg_32(A1, &A2);      // MOVEA.L	A1,A2
  rom_1B7AA();
}