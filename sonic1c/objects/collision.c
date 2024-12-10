// #define CHECK_STUFF(loc) 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_90E0) {
	DEF_ROMLOC(90E0): rom_9158(); // BSR.W	$9158
	DEF_ROMLOC(90E4): if (CCR_EQ) goto rom_9126; // BEQ.B	$9126
	DEF_ROMLOC(90E6): if (CCR_MI) goto rom_9142; // BMI.W	$9142
	DEF_ROMLOC(90EA): tst_reg_16(&D0); // TST.W	D0
	DEF_ROMLOC(90EC): if (CCR_EQ) goto rom_9110; // BEQ.W	$9110
	DEF_ROMLOC(90F0): if (CCR_MI) goto rom_90FA; // BMI.B	$90FA
	DEF_ROMLOC(90F2): tst_mem_16(A1 + 0x10); // TST.W	16(A1)
	DEF_ROMLOC(90F6): if (CCR_MI) goto rom_9110; // BMI.B	$9110
	goto rom_9100; // BRA.B	$9100
	DEF_ROMLOC(90FA): tst_mem_16(A1 + 0x10); // TST.W	16(A1)
	DEF_ROMLOC(90FE): if (CCR_PL) goto rom_9110; // BPL.B	$9110
	DEF_ROMLOC(9100): sub_tomem_16(D0, A1 + 0x8); // SUB.W	D0,8(A1)
	DEF_ROMLOC(9104): move_tomem_16(0x0, A1 + 0x14); // MOVE.W	#$0000,20(A1)
	DEF_ROMLOC(910A): move_tomem_16(0x0, A1 + 0x10); // MOVE.W	#$0000,16(A1)
	DEF_ROMLOC(9110): btst_tomem_8(0x1, A1 + 0x22); // BTST.B	#$01,34(A1)
	DEF_ROMLOC(9116): if (!CCR_EQ) goto rom_9134; // BNE.B	$9134
	DEF_ROMLOC(9118): bset_tomem_8(0x5, A1 + 0x22); // BSET.B	#$05,34(A1)
	DEF_ROMLOC(911E): bset_tomem_8(0x5, A0 + 0x22); // BSET.B	#$05,34(A0)
	DEF_ROMLOC(9124): return; // RTS
	DEF_ROMLOC(9126): btst_tomem_8(0x5, A0 + 0x22); // BTST.B	#$05,34(A0)
	DEF_ROMLOC(912C): if (CCR_EQ) goto rom_9140; // BEQ.B	$9140
	DEF_ROMLOC(912E): move_tomem_16(0x1, A1 + 0x1C); // MOVE.W	#$0001,28(A1)
	DEF_ROMLOC(9134): bclr_tomem_8(0x5, A0 + 0x22); // BCLR.B	#$05,34(A0)
	DEF_ROMLOC(913A): bclr_tomem_8(0x5, A1 + 0x22); // BCLR.B	#$05,34(A1)
	DEF_ROMLOC(9140): return; // RTS
	DEF_ROMLOC(9142): tst_mem_16(A1 + 0x12); // TST.W	18(A1)
	DEF_ROMLOC(9146): if (CCR_PL) goto rom_9156; // BPL.B	$9156
	DEF_ROMLOC(9148): tst_reg_16(&D3); // TST.W	D3
	DEF_ROMLOC(914A): if (CCR_PL) goto rom_9156; // BPL.B	$9156
	DEF_ROMLOC(914C): sub_tomem_16(D3, A1 + 0xC); // SUB.W	D3,12(A1)
	DEF_ROMLOC(9150): move_tomem_16(0x0, A1 + 0x12); // MOVE.W	#$0000,18(A1)
	DEF_ROMLOC(9156): return; // RTS
}
ROMFUNC(rom_9158) {
	DEF_ROMLOC(9158): move_toreg_32(0xFFFFD000, &A1); // LEA.L	$D000,A1
	DEF_ROMLOC(915C): move_toreg_16(read_16(A1 + 0x8), &D0); // MOVE.W	8(A1),D0
	DEF_ROMLOC(9160): sub_toreg_16(read_16(A0 + 0x8), &D0); // SUB.W	8(A0),D0
	DEF_ROMLOC(9164): add_toreg_16(D1, &D0); // ADD.W	D1,D0
	DEF_ROMLOC(9166): if (CCR_MI) goto rom_91C6; // BMI.B	$91C6
	DEF_ROMLOC(9168): move_toreg_16(D1, &D3); // MOVE.W	D1,D3
	DEF_ROMLOC(916A): add_toreg_16(D3, &D3); // ADD.W	D3,D3
	DEF_ROMLOC(916C): cmp_toreg_16(D3, &D0); // CMP.W	D3,D0
	DEF_ROMLOC(916E): if (CCR_HI) goto rom_91C6; // BHI.B	$91C6
	DEF_ROMLOC(9170): move_toreg_8(read_8(A1 + 0x16), &D3); // MOVE.B	22(A1),D3
	DEF_ROMLOC(9174): ext_reg_16(&D3); // EXT.W	D3
	DEF_ROMLOC(9176): add_toreg_16(D3, &D2); // ADD.W	D3,D2
	DEF_ROMLOC(9178): move_toreg_16(read_16(A1 + 0xC), &D3); // MOVE.W	12(A1),D3
	DEF_ROMLOC(917C): sub_toreg_16(read_16(A0 + 0xC), &D3); // SUB.W	12(A0),D3
	DEF_ROMLOC(9180): add_toreg_16(D2, &D3); // ADD.W	D2,D3
	DEF_ROMLOC(9182): if (CCR_MI) goto rom_91C6; // BMI.B	$91C6
	DEF_ROMLOC(9184): move_toreg_16(D2, &D4); // MOVE.W	D2,D4
	DEF_ROMLOC(9186): add_toreg_16(D4, &D4); // ADD.W	D4,D4
	DEF_ROMLOC(9188): cmp_toreg_16(D4, &D3); // CMP.W	D4,D3
	DEF_ROMLOC(918A): if (CCR_CC) goto rom_91C6; // BCC.B	$91C6
	DEF_ROMLOC(918C): tst_mem_8(0xFFFFF7C8); // TST.B	$F7C8
	DEF_ROMLOC(9190): if (CCR_MI) goto rom_91C6; // BMI.B	$91C6
	DEF_ROMLOC(9192): cmp_tomem_8(0x6, 0xFFFFD024); // CMPI.B	#$06,$D024
	DEF_ROMLOC(9198): if (CCR_CC) goto rom_91C6; // BCC.B	$91C6
	DEF_ROMLOC(919A): tst_mem_16(0xFFFFFE08); // TST.W	$FE08
	DEF_ROMLOC(919E): if (!CCR_EQ) goto rom_91C6; // BNE.B	$91C6
	DEF_ROMLOC(91A0): move_toreg_16(D0, &D5); // MOVE.W	D0,D5
	DEF_ROMLOC(91A2): cmp_toreg_16(D0, &D1); // CMP.W	D0,D1
	DEF_ROMLOC(91A4): if (CCR_CC) goto rom_91AE; // BCC.B	$91AE
	DEF_ROMLOC(91A6): add_toreg_16(D1, &D1); // ADD.W	D1,D1
	DEF_ROMLOC(91A8): sub_toreg_16(D1, &D0); // SUB.W	D1,D0
	DEF_ROMLOC(91AA): move_toreg_16(D0, &D5); // MOVE.W	D0,D5
	DEF_ROMLOC(91AC): neg_reg_16(&D5); // NEG.W	D5
	DEF_ROMLOC(91AE): move_toreg_16(D3, &D1); // MOVE.W	D3,D1
	DEF_ROMLOC(91B0): cmp_toreg_16(D3, &D2); // CMP.W	D3,D2
	DEF_ROMLOC(91B2): if (CCR_CC) goto rom_91BA; // BCC.B	$91BA
	DEF_ROMLOC(91B4): sub_toreg_16(D4, &D3); // SUB.W	D4,D3
	DEF_ROMLOC(91B6): move_toreg_16(D3, &D1); // MOVE.W	D3,D1
	DEF_ROMLOC(91B8): neg_reg_16(&D1); // NEG.W	D1
	DEF_ROMLOC(91BA): cmp_toreg_16(D1, &D5); // CMP.W	D1,D5
	DEF_ROMLOC(91BC): if (CCR_HI) goto rom_91C2; // BHI.B	$91C2
	DEF_ROMLOC(91BE): move_toreg_32(0x1, &D4); // MOVEQ.L	$01,D4
	DEF_ROMLOC(91C0): return; // RTS
	DEF_ROMLOC(91C2): move_toreg_32(0xFFFFFFFF, &D4); // MOVEQ.L	$FF,D4
	DEF_ROMLOC(91C4): return; // RTS
	DEF_ROMLOC(91C6): move_toreg_32(0x0, &D4); // MOVEQ.L	$00,D4
	DEF_ROMLOC(91C8): return; // RTS
}
ROMFUNC(rom_40F2) {
  DEF_ROMLOC(40F2) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(40F4)
      : move_toreg_8(read_8(0xFFFFFE10), &D0); // MOVE.B	$FE10,D0
  DEF_ROMLOC(40F8) : lsl_toreg_16(0x2, &D0);   // LSL.W	#$02,D0
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
      : move_toreg_16(read_16(A1 + 0x8), &D0); // MOVE.W	8(A1),D0
  DEF_ROMLOC(1007E)
      : sub_toreg_16(read_16(A0 + 0x8), &D0);       // SUB.W	8(A0),D0
  DEF_ROMLOC(10082) : add_toreg_16(D1, &D0);        // ADD.W	D1,D0
  DEF_ROMLOC(10084) : if (CCR_MI) goto rom_1008A;   // BMI.B	$1008A
  DEF_ROMLOC(10086) : cmp_toreg_16(D2, &D0);        // CMP.W	D2,D0
  DEF_ROMLOC(10088) : if (CCR_CS) goto rom_1009E;   // BCS.B	$1009E
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
      : move_toreg_16(read_16(A1 + 0x8), &D0); // MOVE.W	8(A1),D0
  DEF_ROMLOC(10164)
      : sub_toreg_16(read_16(A0 + 0x8), &D0); // SUB.W	8(A0),D0
  DEF_ROMLOC(10168) : add_toreg_16(D1, &D0);  // ADD.W	D1,D0
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
      : move_toreg_8(read_8(A1 + 0x16), &D3); // MOVE.B	22(A1),D3
  DEF_ROMLOC(1017C) : ext_reg_16(&D3);        // EXT.W	D3
  DEF_ROMLOC(1017E) : add_toreg_16(D3, &D2);  // ADD.W	D3,D2
  DEF_ROMLOC(10180)
      : move_toreg_16(read_16(A1 + 0xC), &D3); // MOVE.W	12(A1),D3
  DEF_ROMLOC(10184)
      : sub_toreg_16(read_16(A0 + 0xC), &D3); // SUB.W	12(A0),D3
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
      : move_toreg_8(read_8(A0 + 0x19), &D1); // MOVE.B	25(A0),D1
  DEF_ROMLOC(10282) : move_toreg_16(D1, &D2); // MOVE.W	D1,D2
  DEF_ROMLOC(10284) : add_toreg_16(D2, &D2);  // ADD.W	D2,D2
  DEF_ROMLOC(10286)
      : add_toreg_16(read_16(A1 + 0x8), &D1); // ADD.W	8(A1),D1
  DEF_ROMLOC(1028A)
      : sub_toreg_16(read_16(A0 + 0x8), &D1); // SUB.W	8(A0),D1
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
      : move_toreg_8(read_8(A1 + 0x3D), &D0);        // MOVE.B	61(A1),D0
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
/*ROMFUNC(rom_15642) {
	DEF_ROMLOC(15642): add_toreg_16(read_16(A0 + 0x8), &D3); // ADD.W	8(A0),D3
	DEF_ROMLOC(15646): move_toreg_16(read_16(A0 + 0xC), &D2); // MOVE.W	12(A0),D2
	DEF_ROMLOC(1564A): move_toreg_32(0xFFFFF768, &A4); // LEA.L	$F768,A4
	DEF_ROMLOC(1564E): move_tomem_8(0x0, A4); // MOVE.B	#$00,(A4)
	DEF_ROMLOC(15652): move_toreg_16(0x10, &A3); // MOVEA.W	#$0010,A3
	DEF_ROMLOC(15656): move_toreg_16(0x0, &D6); // MOVE.W	#$0000,D6
	DEF_ROMLOC(1565A): move_toreg_32(0xE, &D5); // MOVEQ.L	$0E,D5
	DEF_ROMLOC(1565C): rom_15274(); // BSR.W	$15274
	DEF_ROMLOC(15660): move_toreg_8(read_8(0xFFFFF768), &D3); // MOVE.B	$F768,D3
	DEF_ROMLOC(15664): btst_toreg_32(0x0, &D3); // BTST.L	#$00,D3
	DEF_ROMLOC(15668): if (CCR_EQ) goto rom_1566E; // BEQ.B	$1566E
	DEF_ROMLOC(1566A): move_toreg_8(0xFFFFFFC0, &D3); // MOVE.B	#$C0,D3
	rom_1566E(); // Detected flow into next function
}*/
/*ROMFUNC(rom_1566E) {
	DEF_ROMLOC(1566E): return; // RTS
}*/
/*ROMFUNC(rom_15706) {
	DEF_ROMLOC(15706): move_toreg_16(read_16(A0 + 0xC), &D2); // MOVE.W	12(A0),D2
	DEF_ROMLOC(1570A): move_toreg_16(read_16(A0 + 0x8), &D3); // MOVE.W	8(A0),D3
	DEF_ROMLOC(1570E): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(15710): move_toreg_8(read_8(A0 + 0x16), &D0); // MOVE.B	22(A0),D0
	DEF_ROMLOC(15714): ext_reg_16(&D0); // EXT.W	D0
	DEF_ROMLOC(15716): sub_toreg_16(D0, &D2); // SUB.W	D0,D2
	DEF_ROMLOC(15718): eor_toreg_16(0xF, &D2); // EORI.W	#$000F,D2
	DEF_ROMLOC(1571C): move_toreg_32(0xFFFFF768, &A4); // LEA.L	$F768,A4
	DEF_ROMLOC(15720): move_toreg_16(0xFFFFFFF0, &A3); // MOVEA.W	#$FFF0,A3
	DEF_ROMLOC(15724): move_toreg_16(0x1000, &D6); // MOVE.W	#$1000,D6
	DEF_ROMLOC(15728): move_toreg_32(0xE, &D5); // MOVEQ.L	$0E,D5
	DEF_ROMLOC(1572A): rom_15136(); // BSR.W	$15136
	DEF_ROMLOC(1572E): move_toreg_8(read_8(0xFFFFF768), &D3); // MOVE.B	$F768,D3
	DEF_ROMLOC(15732): btst_toreg_32(0x0, &D3); // BTST.L	#$00,D3
	DEF_ROMLOC(15736): if (CCR_EQ) goto rom_1573C; // BEQ.B	$1573C
	DEF_ROMLOC(15738): move_toreg_8(0xFFFFFF80, &D3); // MOVE.B	#$80,D3
	rom_1573C(); // Detected flow into next function
}*/
/*ROMFUNC(rom_1573C) {
	DEF_ROMLOC(1573C): return; // RTS
}*/
/*ROMFUNC(rom_157D4) {
	DEF_ROMLOC(157D4): add_toreg_16(read_16(A0 + 0x8), &D3); // ADD.W	8(A0),D3
	DEF_ROMLOC(157D8): move_toreg_16(read_16(A0 + 0xC), &D2); // MOVE.W	12(A0),D2
	DEF_ROMLOC(157DC): move_toreg_32(0xFFFFF768, &A4); // LEA.L	$F768,A4
	DEF_ROMLOC(157E0): move_tomem_8(0x0, A4); // MOVE.B	#$00,(A4)
	DEF_ROMLOC(157E4): move_toreg_16(0xFFFFFFF0, &A3); // MOVEA.W	#$FFF0,A3
	DEF_ROMLOC(157E8): move_toreg_16(0x800, &D6); // MOVE.W	#$0800,D6
	DEF_ROMLOC(157EC): move_toreg_32(0xE, &D5); // MOVEQ.L	$0E,D5
	DEF_ROMLOC(157EE): rom_15274(); // BSR.W	$15274
	DEF_ROMLOC(157F2): move_toreg_8(read_8(0xFFFFF768), &D3); // MOVE.B	$F768,D3
	DEF_ROMLOC(157F6): btst_toreg_32(0x0, &D3); // BTST.L	#$00,D3
	DEF_ROMLOC(157FA): if (CCR_EQ) goto rom_15800; // BEQ.B	$15800
	DEF_ROMLOC(157FC): move_toreg_8(0x40, &D3); // MOVE.B	#$40,D3
	rom_15800(); // Detected flow into next function
}*/
/*ROMFUNC(rom_15800) {
	DEF_ROMLOC(15800): return; // RTS
}*/