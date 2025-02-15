// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_95A0) {
  u8 switchindex = 0;
  DEF_ROMLOC(95A0) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(95A2) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(95A6)
      : move_toreg_16(read_16(0x95AE + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(95AA): goto rom_95AE + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(95AA) : switch (switchindex) {
  case 0:
    rom_968A();
    break;
  case 1:
    rom_97A8();
    break;
  case 2:
    rom_9802();
    break;
  case 3:
    rom_983E();
    break;
  case 4:
    rom_9802();
    break;
  case 5:
    rom_9802();
    break;
  case 6:
    rom_9802();
    break;
  case 7:
    rom_983E();
    break;
  case 8:
    rom_9802();
    break;
  case 9:
    rom_98BE();
    break;
  case 10:
    rom_98DE();
    break;
  case 11:
    rom_98DE();
    break;
  case 12:
    rom_98FE();
    break;
  case 13:
    rom_9938();
    break;
  case 14:
    rom_9992();
    break;
  case 15:
    rom_99B0();
    break;
  case 16:
    rom_9992();
    break;
  case 17:
    rom_99B0();
    break;
  case 18:
    rom_9992();
    break;
  case 19:
    rom_99EE();
    break;
  case 20:
    rom_9954();
    break;
  }
}
ROMFUNC(rom_968A) {
  DEF_ROMLOC(968A) : tst_mem_8(A0 + 0x28);      // TST.B	40(A0)
  DEF_ROMLOC(968E) : if (CCR_EQ) goto rom_96F4; // BEQ.W	$96F4
  DEF_ROMLOC(9692) : move_toreg_32(0x0, &D0);   // MOVEQ.L	$00,D0
  DEF_ROMLOC(9694)
      : move_toreg_8(read_8(A0 + 0x28), &D0);     // MOVE.B	40(A0),D0
  DEF_ROMLOC(9698) : add_toreg_16(D0, &D0);       // ADD.W	D0,D0
  DEF_ROMLOC(969A) : move_tomem_8(D0, A0 + 0x24); // MOVE.B	D0,36(A0)
  DEF_ROMLOC(969E) : sub_toreg_16(0x14, &D0);     // SUBI.W	#$0014,D0
  DEF_ROMLOC(96A2)
      : move_tomem_16(read_16(0x9674 + (s16)(D0 & 0xffff)),
                      A0 + 0x2);            // MOVE.W	-48(PC,D0),2(A0)
  DEF_ROMLOC(96A8) : add_toreg_16(D0, &D0); // ADD.W	D0,D0
  DEF_ROMLOC(96AA)
      : move_tomem_32(read_32(0x9648 + (s16)(D0 & 0xffff)),
                      A0 + 0x4);                 // MOVE.L	-100(PC,D0),4(A0)
  DEF_ROMLOC(96B0) : move_toreg_32(0x961C, &A1); // LEA.L	-150(PC),A1
  DEF_ROMLOC(96B4)
      : move_tomem_16(read_16((s32)A1 + (s8)0x0 + (s16)D0),
                      A0 + 0x32); // MOVE.W	0(A1,D0),50(A0)
  DEF_ROMLOC(96BA)
      : move_tomem_16(read_16((s32)A1 + (s8)0x0 + (s16)D0),
                      A0 + 0x10); // MOVE.W	0(A1,D0),16(A0)
  DEF_ROMLOC(96C0)
      : move_tomem_16(read_16((s32)A1 + (s8)0x2 + (s16)D0),
                      A0 + 0x34); // MOVE.W	2(A1,D0),52(A0)
  DEF_ROMLOC(96C6)
      : move_tomem_16(read_16((s32)A1 + (s8)0x2 + (s16)D0),
                      A0 + 0x12);                  // MOVE.W	2(A1,D0),18(A0)
  DEF_ROMLOC(96CC) : move_tomem_8(0xC, A0 + 0x16); // MOVE.B	#$0C,22(A0)
  DEF_ROMLOC(96D2) : move_tomem_8(0x4, A0 + 0x1);  // MOVE.B	#$04,1(A0)
  DEF_ROMLOC(96D8) : bset_tomem_8(0x0, A0 + 0x1);  // BSET.B	#$00,1(A0)
  DEF_ROMLOC(96DE) : move_tomem_8(0x6, A0 + 0x18); // MOVE.B	#$06,24(A0)
  DEF_ROMLOC(96E4) : move_tomem_8(0x8, A0 + 0x19); // MOVE.B	#$08,25(A0)
  DEF_ROMLOC(96EA) : move_tomem_8(0x7, A0 + 0x1E); // MOVE.B	#$07,30(A0)
  rom_DC92();
  return;                                               // BRA.W	$DC92
  DEF_ROMLOC(96F4) : add_tomem_8(0x2, A0 + 0x24);       // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(96F8) : rom_29AC();                        // BSR.W	$29AC
  DEF_ROMLOC(96FC) : and_toreg_16(0x1, &D0);            // ANDI.W	#$0001,D0
  DEF_ROMLOC(9700) : move_toreg_32(0x0, &D1);           // MOVEQ.L	$00,D1
  DEF_ROMLOC(9702) : move_toreg_8(read_8(v_zone), &D1); // MOVE.B	$FE10,D1
  DEF_ROMLOC(9706) : add_toreg_16(D1, &D1);             // ADD.W	D1,D1
  DEF_ROMLOC(9708) : add_toreg_16(D0, &D1);             // ADD.W	D0,D1
  DEF_ROMLOC(970A) : move_toreg_32(0x95D8, &A1);        // LEA.L	-308(PC),A1
  DEF_ROMLOC(970E)
      : move_toreg_8(read_8((s32)A1 + (s8)0x0 + (s16)D1),
                     &D0);                        // MOVE.B	0(A1,D1),D0
  DEF_ROMLOC(9712) : move_tomem_8(D0, A0 + 0x30); // MOVE.B	D0,48(A0)
  DEF_ROMLOC(9716) : lsl_toreg_16(0x3, &D0);      // LSL.W	#$03,D0
  DEF_ROMLOC(9718) : move_toreg_32(0x95E4, &A1);  // LEA.L	-310(PC),A1
  DEF_ROMLOC(971C) : add_toreg_16(D0, &A1);       // ADDA.W	D0,A1
  DEF_ROMLOC(971E)
      : move_tomem_16(read_16((A1 += 2, A1 - 2)),
                      A0 + 0x32); // MOVE.W	(A1)+,50(A0)
  DEF_ROMLOC(9722)
      : move_tomem_16(read_16((A1 += 2, A1 - 2)),
                      A0 + 0x34); // MOVE.W	(A1)+,52(A0)
  DEF_ROMLOC(9726)
      : move_tomem_32(read_32((A1 += 4, A1 - 4)),
                      A0 + 0x4);                     // MOVE.L	(A1)+,4(A0)
  DEF_ROMLOC(972A) : move_tomem_16(0x580, A0 + 0x2); // MOVE.W	#$0580,2(A0)
  DEF_ROMLOC(9730) : btst_tomem_8(0x0, A0 + 0x30);   // BTST.B	#$00,48(A0)
  DEF_ROMLOC(9736) : if (CCR_EQ) goto rom_973E;      // BEQ.B	$973E
  DEF_ROMLOC(9738) : move_tomem_16(0x592, A0 + 0x2); // MOVE.W	#$0592,2(A0)
  DEF_ROMLOC(973E) : move_tomem_8(0xC, A0 + 0x16);   // MOVE.B	#$0C,22(A0)
  DEF_ROMLOC(9744) : move_tomem_8(0x4, A0 + 0x1);    // MOVE.B	#$04,1(A0)
  DEF_ROMLOC(974A) : bset_tomem_8(0x0, A0 + 0x1);    // BSET.B	#$00,1(A0)
  DEF_ROMLOC(9750) : move_tomem_8(0x6, A0 + 0x18);   // MOVE.B	#$06,24(A0)
  DEF_ROMLOC(9756) : move_tomem_8(0x8, A0 + 0x19);   // MOVE.B	#$08,25(A0)
  DEF_ROMLOC(975C) : move_tomem_8(0x7, A0 + 0x1E);   // MOVE.B	#$07,30(A0)
  DEF_ROMLOC(9762) : move_tomem_8(0x2, A0 + 0x1A);   // MOVE.B	#$02,26(A0)
  DEF_ROMLOC(9768)
      : move_tomem_16(0xFFFFFC00, A0 + 0x12);    // MOVE.W	#$FC00,18(A0)
  DEF_ROMLOC(976E) : tst_mem_8(0xFFFFF7A7);      // TST.B	$F7A7
  DEF_ROMLOC(9772) : if (!CCR_EQ) goto rom_979A; // BNE.B	$979A
  DEF_ROMLOC(9774) : rom_E11A();                 // BSR.W	$E11A
  DEF_ROMLOC(9778) : if (!CCR_EQ) goto rom_9796; // BNE.B	$9796
  DEF_ROMLOC(977A)
      : move_tomem_8(OBJ_POINTS,
                     A1 + offsetof(object, id)); // MOVE.B	#$29,0(A1)
  DEF_ROMLOC(9780)
      : move_tomem_16(read_16(A0 + 0x8), A1 + 0x8); // MOVE.W	8(A0),8(A1)
  DEF_ROMLOC(9786)
      : move_tomem_16(read_16(A0 + 0xC), A1 + 0xC); // MOVE.W	12(A0),12(A1)
  DEF_ROMLOC(978C)
      : move_toreg_16(read_16(A0 + 0x3E), &D0);   // MOVE.W	62(A0),D0
  DEF_ROMLOC(9790) : lsr_toreg_16(0x1, &D0);      // LSR.W	#$01,D0
  DEF_ROMLOC(9792) : move_tomem_8(D0, A1 + 0x1A); // MOVE.B	D0,26(A1)
  DEF_ROMLOC(9796) : rom_DC92();
  return;                                           // BRA.W	$DC92
  DEF_ROMLOC(979A) : move_tomem_8(0x12, A0 + 0x24); // MOVE.B	#$12,36(A0)
  DEF_ROMLOC(97A0) : clr_mem_16(A0 + 0x10);         // CLR.W	16(A0)
  rom_DC92();                                       // BRA.W	$DC92
}
ROMFUNC(rom_97A8) {
  DEF_ROMLOC(97A8) : tst_mem_8(A0 + 0x1); // TST.B	1(A0)
  DEF_ROMLOC(97AC) : if (CCR_PL) {
    rom_DCCE();
    return;
  }                                              // BPL.W	$DCCE
  DEF_ROMLOC(97B0) : rom_DC40();                 // BSR.W	$DC40
  DEF_ROMLOC(97B4) : tst_mem_16(A0 + 0x12);      // TST.W	18(A0)
  DEF_ROMLOC(97B8) : if (CCR_MI) goto rom_97FE;  // BMI.B	$97FE
  DEF_ROMLOC(97BA) : rom_15580();                // JSR	$00015580
  DEF_ROMLOC(97C0) : tst_reg_16(&D1);            // TST.W	D1
  DEF_ROMLOC(97C2) : if (CCR_PL) goto rom_97FE;  // BPL.B	$97FE
  DEF_ROMLOC(97C4) : add_tomem_16(D1, A0 + 0xC); // ADD.W	D1,12(A0)
  DEF_ROMLOC(97C8)
      : move_tomem_16(read_16(A0 + 0x32), A0 + 0x10); // MOVE.W	50(A0),16(A0)
  DEF_ROMLOC(97CE)
      : move_tomem_16(read_16(A0 + 0x34), A0 + 0x12); // MOVE.W	52(A0),18(A0)
  DEF_ROMLOC(97D4) : move_tomem_8(0x1, A0 + 0x1A);    // MOVE.B	#$01,26(A0)
  DEF_ROMLOC(97DA) : move_toreg_8(read_8(A0 + 0x30), &D0); // MOVE.B
                                                           // 48(A0),D0
  DEF_ROMLOC(97DE) : add_toreg_8(D0, &D0);                 // ADD.B	D0,D0
  DEF_ROMLOC(97E0) : add_toreg_8(0x4, &D0);                // ADDQ.B	#$04,D0
  DEF_ROMLOC(97E2) : move_tomem_8(D0, A0 + 0x24);          // MOVE.B	D0,36(A0)
  DEF_ROMLOC(97E6) : tst_mem_8(0xFFFFF7A7);                // TST.B	$F7A7
  DEF_ROMLOC(97EA) : if (CCR_EQ) goto rom_97FE;            // BEQ.B	$97FE
  DEF_ROMLOC(97EC) : btst_tomem_8(0x4, 0xFFFFFE0F);        // BTST.B	#$04,$FE0F
  DEF_ROMLOC(97F2) : if (CCR_EQ) goto rom_97FE;            // BEQ.B	$97FE
  DEF_ROMLOC(97F4) : neg_mem_16(A0 + 0x10);                // NEG.W	16(A0)
  DEF_ROMLOC(97F8) : bchg_tomem_8(0x0, A0 + 0x1);          // BCHG.B	#$00,1(A0)
  DEF_ROMLOC(97FE) : rom_DC92();                           // BRA.W	$DC92
}
ROMFUNC(rom_9802) {
  DEF_ROMLOC(9802) : rom_DC40();                   // BSR.W	$DC40
  DEF_ROMLOC(9806) : move_tomem_8(0x1, A0 + 0x1A); // MOVE.B	#$01,26(A0)
  DEF_ROMLOC(980C) : tst_mem_16(A0 + 0x12);        // TST.W	18(A0)
  DEF_ROMLOC(9810) : if (CCR_MI) goto rom_982C;    // BMI.B	$982C
  DEF_ROMLOC(9812) : move_tomem_8(0x0, A0 + 0x1A); // MOVE.B	#$00,26(A0)
  DEF_ROMLOC(9818) : rom_15580();                  // JSR	$00015580
  DEF_ROMLOC(981E) : tst_reg_16(&D1);              // TST.W	D1
  DEF_ROMLOC(9820) : if (CCR_PL) goto rom_982C;    // BPL.B	$982C
  DEF_ROMLOC(9822) : add_tomem_16(D1, A0 + 0xC);   // ADD.W	D1,12(A0)
  DEF_ROMLOC(9826)
      : move_tomem_16(read_16(A0 + 0x34), A0 + 0x12); // MOVE.W	52(A0),18(A0)
  DEF_ROMLOC(982C) : tst_mem_8(A0 + 0x28);            // TST.B	40(A0)
  DEF_ROMLOC(9830) : if (!CCR_EQ) {
    rom_98A2();
    return;
  }                                       // BNE.B	$98A2
  DEF_ROMLOC(9832) : tst_mem_8(A0 + 0x1); // TST.B	1(A0)
  DEF_ROMLOC(9836) : if (CCR_PL) {
    rom_DCCE();
    return;
  } // BPL.W	$DCCE
  rom_DC92();
  return; // BRA.W	$DC92
}
ROMFUNC(rom_983E) {
  DEF_ROMLOC(983E) : rom_DC6C();                    // BSR.W	$DC6C
  DEF_ROMLOC(9842) : add_tomem_16(0x18, A0 + 0x12); // ADDI.W	#$0018,18(A0)
  DEF_ROMLOC(9848) : tst_mem_16(A0 + 0x12);         // TST.W	18(A0)
  DEF_ROMLOC(984C) : if (CCR_MI) goto rom_987A;     // BMI.B	$987A
  DEF_ROMLOC(984E) : rom_15580();                   // JSR	$00015580
  DEF_ROMLOC(9854) : tst_reg_16(&D1);               // TST.W	D1
  DEF_ROMLOC(9856) : if (CCR_PL) goto rom_987A;     // BPL.B	$987A
  DEF_ROMLOC(9858) : add_tomem_16(D1, A0 + 0xC);    // ADD.W	D1,12(A0)
  DEF_ROMLOC(985C)
      : move_tomem_16(read_16(A0 + 0x34), A0 + 0x12); // MOVE.W	52(A0),18(A0)
  DEF_ROMLOC(9862) : tst_mem_8(A0 + 0x28);            // TST.B	40(A0)
  DEF_ROMLOC(9866) : if (CCR_EQ) goto rom_987A;       // BEQ.B	$987A
  DEF_ROMLOC(9868) : cmp_tomem_8(0xA, A0 + 0x28);     // CMPI.B	#$0A,40(A0)
  DEF_ROMLOC(986E) : if (CCR_EQ) goto rom_987A;       // BEQ.B	$987A
  DEF_ROMLOC(9870) : neg_mem_16(A0 + 0x10);           // NEG.W	16(A0)
  DEF_ROMLOC(9874) : bchg_tomem_8(0x0, A0 + 0x1);     // BCHG.B	#$00,1(A0)
  DEF_ROMLOC(987A) : sub_tomem_8(0x1, A0 + 0x1E);     // SUBQ.B	#$01,30(A0)
  DEF_ROMLOC(987E) : if (CCR_PL) goto rom_9890;       // BPL.B	$9890
  DEF_ROMLOC(9880) : move_tomem_8(0x1, A0 + 0x1E);    // MOVE.B	#$01,30(A0)
  DEF_ROMLOC(9886) : add_tomem_8(0x1, A0 + 0x1A);     // ADDQ.B	#$01,26(A0)
  DEF_ROMLOC(988A) : and_tomem_8(0x1, A0 + 0x1A);     // ANDI.B	#$01,26(A0)
  DEF_ROMLOC(9890) : tst_mem_8(A0 + 0x28);            // TST.B	40(A0)
  DEF_ROMLOC(9894) : if (!CCR_EQ) {
    rom_98A2();
    return;
  }                                       // BNE.B	$98A2
  DEF_ROMLOC(9896) : tst_mem_8(A0 + 0x1); // TST.B	1(A0)
  DEF_ROMLOC(989A) : if (CCR_PL) {
    rom_DCCE();
    return;
  } // BPL.W	$DCCE
  rom_DC92();
  return; // BRA.W	$DC92
}
ROMFUNC(rom_98A2) {
  DEF_ROMLOC(98A2)
      : move_toreg_16(read_16(A0 + 0x8), &D0); // MOVE.W	8(A0),D0
  DEF_ROMLOC(98A6)
      : sub_toreg_16(read_16(0xFFFFD008), &D0); // SUB.W	$D008,D0
  DEF_ROMLOC(98AA) : if (CCR_CS) goto rom_98BA; // BCS.B	$98BA
  DEF_ROMLOC(98AC) : sub_toreg_16(0x180, &D0);  // SUBI.W	#$0180,D0
  DEF_ROMLOC(98B0) : if (CCR_PL) goto rom_98BA; // BPL.B	$98BA
  DEF_ROMLOC(98B2) : tst_mem_8(A0 + 0x1);       // TST.B	1(A0)
  DEF_ROMLOC(98B6) : if (CCR_PL) {
    rom_DCCE();
    return;
  }                              // BPL.W	$DCCE
  DEF_ROMLOC(98BA) : rom_DC92(); // BRA.W	$DC92
}
ROMFUNC(rom_98BE) {
  DEF_ROMLOC(98BE) : tst_mem_8(A0 + 0x1); // TST.B	1(A0)
  DEF_ROMLOC(98C2) : if (CCR_PL) {
    rom_DCCE();
    return;
  }                                                // BPL.W	$DCCE
  DEF_ROMLOC(98C6) : sub_tomem_16(0x1, A0 + 0x36); // SUBQ.W	#$01,54(A0)
  DEF_ROMLOC(98CA) : if (!CCR_EQ) goto rom_98DA;   // BNE.W	$98DA
  DEF_ROMLOC(98CE) : move_tomem_8(0x2, A0 + 0x24); // MOVE.B	#$02,36(A0)
  DEF_ROMLOC(98D4) : move_tomem_8(0x3, A0 + 0x18); // MOVE.B	#$03,24(A0)
  DEF_ROMLOC(98DA) : rom_DC92();                   // BRA.W	$DC92
}
ROMFUNC(rom_98DE) {
  DEF_ROMLOC(98DE) : rom_9A82();                // BSR.W	$9A82
  DEF_ROMLOC(98E2) : if (CCR_CC) goto rom_98FA; // BCC.B	$98FA
  DEF_ROMLOC(98E4)
      : move_tomem_16(read_16(A0 + 0x32), A0 + 0x10); // MOVE.W	50(A0),16(A0)
  DEF_ROMLOC(98EA)
      : move_tomem_16(read_16(A0 + 0x34), A0 + 0x12); // MOVE.W	52(A0),18(A0)
  DEF_ROMLOC(98F0) : move_tomem_8(0xE, A0 + 0x24);    // MOVE.B	#$0E,36(A0)
  rom_983E();
  return;                        // BRA.W	$983E
  DEF_ROMLOC(98FA) : rom_98A2(); // BRA.W	$98A2
}
ROMFUNC(rom_98FE) {
  DEF_ROMLOC(98FE) : rom_9A82();                    // BSR.W	$9A82
  DEF_ROMLOC(9902) : if (CCR_PL) goto rom_9934;     // BPL.B	$9934
  DEF_ROMLOC(9904) : clr_mem_16(A0 + 0x10);         // CLR.W	16(A0)
  DEF_ROMLOC(9908) : clr_mem_16(A0 + 0x32);         // CLR.W	50(A0)
  DEF_ROMLOC(990C) : rom_DC6C();                    // BSR.W	$DC6C
  DEF_ROMLOC(9910) : add_tomem_16(0x18, A0 + 0x12); // ADDI.W	#$0018,18(A0)
  DEF_ROMLOC(9916) : rom_9A42();                    // BSR.W	$9A42
  DEF_ROMLOC(991A) : rom_9A6A();                    // BSR.W	$9A6A
  DEF_ROMLOC(991E) : sub_tomem_8(0x1, A0 + 0x1E);   // SUBQ.B	#$01,30(A0)
  DEF_ROMLOC(9922) : if (CCR_PL) goto rom_9934;     // BPL.B	$9934
  DEF_ROMLOC(9924) : move_tomem_8(0x1, A0 + 0x1E);  // MOVE.B	#$01,30(A0)
  DEF_ROMLOC(992A) : add_tomem_8(0x1, A0 + 0x1A);   // ADDQ.B	#$01,26(A0)
  DEF_ROMLOC(992E) : and_tomem_8(0x1, A0 + 0x1A);   // ANDI.B	#$01,26(A0)
  DEF_ROMLOC(9934) : rom_98A2();                    // BRA.W	$98A2
}
ROMFUNC(rom_9938) {
  DEF_ROMLOC(9938) : rom_9A82(); // BSR.W	$9A82
  DEF_ROMLOC(993C) : if (CCR_PL) {
    rom_998E();
    return;
  } // BPL.B	$998E
  DEF_ROMLOC(993E)
      : move_tomem_16(read_16(A0 + 0x32), A0 + 0x10); // MOVE.W	50(A0),16(A0)
  DEF_ROMLOC(9944)
      : move_tomem_16(read_16(A0 + 0x34), A0 + 0x12); // MOVE.W	52(A0),18(A0)
  DEF_ROMLOC(994A) : move_tomem_8(0x4, A0 + 0x24);    // MOVE.B	#$04,36(A0)
  rom_9802();
  return; // BRA.W	$9802
}
ROMFUNC(rom_9954) {
  DEF_ROMLOC(9954) : rom_DC40();                   // BSR.W	$DC40
  DEF_ROMLOC(9958) : move_tomem_8(0x1, A0 + 0x1A); // MOVE.B	#$01,26(A0)
  DEF_ROMLOC(995E) : tst_mem_16(A0 + 0x12);        // TST.W	18(A0)
  DEF_ROMLOC(9962) : if (CCR_MI) {
    rom_998E();
    return;
  }                                                // BMI.B	$998E
  DEF_ROMLOC(9964) : move_tomem_8(0x0, A0 + 0x1A); // MOVE.B	#$00,26(A0)
  DEF_ROMLOC(996A) : rom_15580();                  // JSR	$00015580
  DEF_ROMLOC(9970) : tst_reg_16(&D1);              // TST.W	D1
  DEF_ROMLOC(9972) : if (CCR_PL) {
    rom_998E();
    return;
  }                                               // BPL.B	$998E
  DEF_ROMLOC(9974) : not_mem_8(A0 + 0x29);        // NOT.B	41(A0)
  DEF_ROMLOC(9978) : if (!CCR_EQ) goto rom_9984;  // BNE.B	$9984
  DEF_ROMLOC(997A) : neg_mem_16(A0 + 0x10);       // NEG.W	16(A0)
  DEF_ROMLOC(997E) : bchg_tomem_8(0x0, A0 + 0x1); // BCHG.B	#$00,1(A0)
  DEF_ROMLOC(9984) : add_tomem_16(D1, A0 + 0xC);  // ADD.W	D1,12(A0)
  DEF_ROMLOC(9988)
      : move_tomem_16(read_16(A0 + 0x34), A0 + 0x12); // MOVE.W	52(A0),18(A0)
  rom_998E();
}
ROMFUNC(rom_998E) {
  DEF_ROMLOC(998E) : rom_98A2(); // BRA.W	$98A2
}
ROMFUNC(rom_9992) {
  DEF_ROMLOC(9992) : rom_9A82();                // BSR.W	$9A82
  DEF_ROMLOC(9996) : if (CCR_PL) goto rom_99AC; // BPL.B	$99AC
  DEF_ROMLOC(9998) : clr_mem_16(A0 + 0x10);     // CLR.W	16(A0)
  DEF_ROMLOC(999C) : clr_mem_16(A0 + 0x32);     // CLR.W	50(A0)
  DEF_ROMLOC(99A0) : rom_DC40();                // BSR.W	$DC40
  DEF_ROMLOC(99A4) : rom_9A42();                // BSR.W	$9A42
  DEF_ROMLOC(99A8) : rom_9A6A();                // BSR.W	$9A6A
  DEF_ROMLOC(99AC) : rom_98A2();                // BRA.W	$98A2
}
ROMFUNC(rom_99B0) {
  DEF_ROMLOC(99B0) : rom_9A82();                   // BSR.W	$9A82
  DEF_ROMLOC(99B4) : if (CCR_PL) goto rom_99EA;    // BPL.B	$99EA
  DEF_ROMLOC(99B6) : rom_DC40();                   // BSR.W	$DC40
  DEF_ROMLOC(99BA) : move_tomem_8(0x1, A0 + 0x1A); // MOVE.B	#$01,26(A0)
  DEF_ROMLOC(99C0) : tst_mem_16(A0 + 0x12);        // TST.W	18(A0)
  DEF_ROMLOC(99C4) : if (CCR_MI) goto rom_99EA;    // BMI.B	$99EA
  DEF_ROMLOC(99C6) : move_tomem_8(0x0, A0 + 0x1A); // MOVE.B	#$00,26(A0)
  DEF_ROMLOC(99CC) : rom_15580();                  // JSR	$00015580
  DEF_ROMLOC(99D2) : tst_reg_16(&D1);              // TST.W	D1
  DEF_ROMLOC(99D4) : if (CCR_PL) goto rom_99EA;    // BPL.B	$99EA
  DEF_ROMLOC(99D6) : neg_mem_16(A0 + 0x10);        // NEG.W	16(A0)
  DEF_ROMLOC(99DA) : bchg_tomem_8(0x0, A0 + 0x1);  // BCHG.B	#$00,1(A0)
  DEF_ROMLOC(99E0) : add_tomem_16(D1, A0 + 0xC);   // ADD.W	D1,12(A0)
  DEF_ROMLOC(99E4)
      : move_tomem_16(read_16(A0 + 0x34), A0 + 0x12); // MOVE.W	52(A0),18(A0)
  DEF_ROMLOC(99EA) : rom_98A2();                      // BRA.W	$98A2
}
ROMFUNC(rom_99EE) {
  DEF_ROMLOC(99EE) : rom_9A82();                    // BSR.W	$9A82
  DEF_ROMLOC(99F2) : if (CCR_PL) goto rom_9A3E;     // BPL.B	$9A3E
  DEF_ROMLOC(99F4) : rom_DC6C();                    // BSR.W	$DC6C
  DEF_ROMLOC(99F8) : add_tomem_16(0x18, A0 + 0x12); // ADDI.W	#$0018,18(A0)
  DEF_ROMLOC(99FE) : tst_mem_16(A0 + 0x12);         // TST.W	18(A0)
  DEF_ROMLOC(9A02) : if (CCR_MI) goto rom_9A28;     // BMI.B	$9A28
  DEF_ROMLOC(9A04) : rom_15580();                   // JSR	$00015580
  DEF_ROMLOC(9A0A) : tst_reg_16(&D1);               // TST.W	D1
  DEF_ROMLOC(9A0C) : if (CCR_PL) goto rom_9A28;     // BPL.B	$9A28
  DEF_ROMLOC(9A0E) : not_mem_8(A0 + 0x29);          // NOT.B	41(A0)
  DEF_ROMLOC(9A12) : if (!CCR_EQ) goto rom_9A1E;    // BNE.B	$9A1E
  DEF_ROMLOC(9A14) : neg_mem_16(A0 + 0x10);         // NEG.W	16(A0)
  DEF_ROMLOC(9A18) : bchg_tomem_8(0x0, A0 + 0x1);   // BCHG.B	#$00,1(A0)
  DEF_ROMLOC(9A1E) : add_tomem_16(D1, A0 + 0xC);    // ADD.W	D1,12(A0)
  DEF_ROMLOC(9A22)
      : move_tomem_16(read_16(A0 + 0x34), A0 + 0x12); // MOVE.W	52(A0),18(A0)
  DEF_ROMLOC(9A28) : sub_tomem_8(0x1, A0 + 0x1E);     // SUBQ.B	#$01,30(A0)
  DEF_ROMLOC(9A2C) : if (CCR_PL) goto rom_9A3E;       // BPL.B	$9A3E
  DEF_ROMLOC(9A2E) : move_tomem_8(0x1, A0 + 0x1E);    // MOVE.B	#$01,30(A0)
  DEF_ROMLOC(9A34) : add_tomem_8(0x1, A0 + 0x1A);     // ADDQ.B	#$01,26(A0)
  DEF_ROMLOC(9A38) : and_tomem_8(0x1, A0 + 0x1A);     // ANDI.B	#$01,26(A0)
  DEF_ROMLOC(9A3E) : rom_98A2();                      // BRA.W	$98A2
}
ROMFUNC(rom_9A42) {
  DEF_ROMLOC(9A42) : move_tomem_8(0x1, A0 + 0x1A); // MOVE.B	#$01,26(A0)
  DEF_ROMLOC(9A48) : tst_mem_16(A0 + 0x12);        // TST.W	18(A0)
  DEF_ROMLOC(9A4C) : if (CCR_MI) goto rom_9A68;    // BMI.B	$9A68
  DEF_ROMLOC(9A4E) : move_tomem_8(0x0, A0 + 0x1A); // MOVE.B	#$00,26(A0)
  DEF_ROMLOC(9A54) : rom_15580();                  // JSR	$00015580
  DEF_ROMLOC(9A5A) : tst_reg_16(&D1);              // TST.W	D1
  DEF_ROMLOC(9A5C) : if (CCR_PL) goto rom_9A68;    // BPL.B	$9A68
  DEF_ROMLOC(9A5E) : add_tomem_16(D1, A0 + 0xC);   // ADD.W	D1,12(A0)
  DEF_ROMLOC(9A62)
      : move_tomem_16(read_16(A0 + 0x34), A0 + 0x12); // MOVE.W	52(A0),18(A0)
  DEF_ROMLOC(9A68) : return;                          // RTS
}
ROMFUNC(rom_9A6A) {
  DEF_ROMLOC(9A6A) : bset_tomem_8(0x0, A0 + 0x1); // BSET.B	#$00,1(A0)
  DEF_ROMLOC(9A70)
      : move_toreg_16(read_16(A0 + 0x8), &D0); // MOVE.W	8(A0),D0
  DEF_ROMLOC(9A74)
      : sub_toreg_16(read_16(0xFFFFD008), &D0);   // SUB.W	$D008,D0
  DEF_ROMLOC(9A78) : if (CCR_CC) goto rom_9A80;   // BCC.B	$9A80
  DEF_ROMLOC(9A7A) : bclr_tomem_8(0x0, A0 + 0x1); // BCLR.B	#$00,1(A0)
  DEF_ROMLOC(9A80) : return;                      // RTS
}
ROMFUNC(rom_9A82) {
  DEF_ROMLOC(9A82)
      : move_toreg_16(read_16(0xFFFFD008), &D0);           // MOVE.W	$D008,D0
  DEF_ROMLOC(9A86) : sub_toreg_16(read_16(A0 + 0x8), &D0); // SUB.W	8(A0),D0
  DEF_ROMLOC(9A8A) : sub_toreg_16(0xB8, &D0);              // SUBI.W	#$00B8,D0
  DEF_ROMLOC(9A8E) : return;                               // RTS
}