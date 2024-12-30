// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"


ROMFUNC(rom_888E) {
  u8 switchindex = 0;
  DEF_ROMLOC(888E) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(8890) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(8894)
      : move_toreg_16(read_16(0x889C + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(8898): goto rom_889C + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(8898) : switch (switchindex) {
  case 0:
    rom_88A8();
    break;
  case 1:
    rom_88E4();
    break;
  case 2:
    rom_8908();
    break;
  case 3:
    rom_8938();
    break;
  case 4:
    rom_8998();
    break;
  case 5:
    rom_891A();
    break;
  }
}
ROMFUNC(rom_88A8) {
  DEF_ROMLOC(88A8) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(88AC)
      : move_tomem_32(0x8C1E, A0 + 0x4);              // MOVE.L	#$00008C1E,4(A0)
  DEF_ROMLOC(88B4) : move_tomem_16(0x4000, A0 + 0x2); // MOVE.W	#$4000,2(A0)
  DEF_ROMLOC(88BA) : or_tomem_8(0x4, A0 + 0x1);       // ORI.B	#$04,1(A0)
  DEF_ROMLOC(88C0) : move_tomem_8(0x4, A0 + 0x18);    // MOVE.B	#$04,24(A0)
  DEF_ROMLOC(88C6) : move_tomem_8(0x7, A0 + 0x38);    // MOVE.B	#$07,56(A0)
  DEF_ROMLOC(88CC) : move_tomem_8(0x64, A0 + 0x19);   // MOVE.B	#$64,25(A0)
  DEF_ROMLOC(88D2)
      : move_tomem_8(read_8(A0 + 0x28), A0 + 0x1A); // MOVE.B	40(A0),26(A0)
  DEF_ROMLOC(88D8) : move_tomem_8(0x38, A0 + 0x16); // MOVE.B	#$38,22(A0)
  DEF_ROMLOC(88DE) : bset_tomem_8(0x4, A0 + 0x1);   // BSET.B	#$04,1(A0)
  rom_88E4(); // Detected flow into next function
}
ROMFUNC(rom_88E4) {
  DEF_ROMLOC(88E4) : tst_mem_8(A0 + 0x3A);      // TST.B	58(A0)
  DEF_ROMLOC(88E8) : if (CCR_EQ) goto rom_88F6; // BEQ.B	$88F6
  DEF_ROMLOC(88EA) : tst_mem_8(A0 + 0x38);      // TST.B	56(A0)
  DEF_ROMLOC(88EE) : if (CCR_EQ) {
    rom_8AF2();
    return;
  }                                               // BEQ.W	$8AF2
  DEF_ROMLOC(88F2) : sub_tomem_8(0x1, A0 + 0x38); // SUBQ.B	#$01,56(A0)
  DEF_ROMLOC(88F6) : move_toreg_16(0x30, &D1);    // MOVE.W	#$0030,D1
  DEF_ROMLOC(88FA) : move_toreg_32(0x8BEE, &A2);  // LEA.L	$00008BEE,A2
  DEF_ROMLOC(8900) : rom_7B9E();                  // BSR.W	$7B9E
  rom_FD38();                                     // BRA.W	$FD38
}
ROMFUNC(rom_8908) {
  DEF_ROMLOC(8908) : tst_mem_8(A0 + 0x38); // TST.B	56(A0)
  DEF_ROMLOC(890C) : if (CCR_EQ) {
    rom_8AF8();
    return;
  }                                                // BEQ.W	$8AF8
  DEF_ROMLOC(8910) : move_tomem_8(0x1, A0 + 0x3A); // MOVE.B	#$01,58(A0)
  DEF_ROMLOC(8916) : sub_tomem_8(0x1, A0 + 0x38);  // SUBQ.B	#$01,56(A0)
  rom_891A(); // Detected flow into next function
}
ROMFUNC(rom_891A) {
  DEF_ROMLOC(891A) : move_toreg_16(0x30, &D1);   // MOVE.W	#$0030,D1
  DEF_ROMLOC(891E) : rom_7C3E();                 // BSR.W	$7C3E
  DEF_ROMLOC(8922) : move_toreg_16(0x30, &D1);   // MOVE.W	#$0030,D1
  DEF_ROMLOC(8926) : move_toreg_32(0x8BEE, &A2); // LEA.L	$00008BEE,A2
  DEF_ROMLOC(892C)
      : move_toreg_16(read_16(A0 + 0x8), &D2); // MOVE.W	8(A0),D2
  DEF_ROMLOC(8930) : rom_8BA8();               // BSR.W	$8BA8
  rom_FD38();                                  // BRA.W	$FD38
}
ROMFUNC(rom_8938) {
  DEF_ROMLOC(8938) : tst_mem_8(A0 + 0x38); // TST.B	56(A0)
  DEF_ROMLOC(893C) : if (CCR_EQ) {
    rom_8988();
    return;
  }                                        // BEQ.B	$8988
  DEF_ROMLOC(893E) : tst_mem_8(A0 + 0x3A); // TST.B	58(A0)
  DEF_ROMLOC(8942) : if (!CCR_EQ) {
    rom_894E();
    return;
  }                                               // BNE.W	$894E
  DEF_ROMLOC(8946) : sub_tomem_8(0x1, A0 + 0x38); // SUBQ.B	#$01,56(A0)
  rom_DC92();                                     // BRA.W	$DC92
}
ROMFUNC(rom_894E) {
  DEF_ROMLOC(894E) : sub_tomem_8(0x1, A0 + 0x38);    // SUBQ.B	#$01,56(A0)
  DEF_ROMLOC(8952) : rom_891A();                     // BSR.W	$891A
  DEF_ROMLOC(8956) : move_toreg_32(0xFFFFD000, &A1); // LEA.L	$D000,A1
  DEF_ROMLOC(895A) : btst_tomem_8(0x3, A1 + 0x22);   // BTST.B	#$03,34(A1)
  DEF_ROMLOC(8960) : if (CCR_EQ) {
    rom_897A();
    return;
  }                                        // BEQ.B	$897A
  DEF_ROMLOC(8962) : tst_mem_8(A0 + 0x38); // TST.B	56(A0)
  DEF_ROMLOC(8966) : if (!CCR_EQ) {
    rom_8986();
    return;
  }                                                // BNE.B	$8986
  DEF_ROMLOC(8968) : bclr_tomem_8(0x3, A1 + 0x22); // BCLR.B	#$03,34(A1)
  DEF_ROMLOC(896E) : bclr_tomem_8(0x5, A1 + 0x22); // BCLR.B	#$05,34(A1)
  DEF_ROMLOC(8974) : move_tomem_8(0x1, A1 + 0x1D); // MOVE.B	#$01,29(A1)
  rom_897A(); // Detected flow into next function
}
ROMFUNC(rom_897A) {
  DEF_ROMLOC(897A) : move_tomem_8(0x0, A0 + 0x3A); // MOVE.B	#$00,58(A0)
  DEF_ROMLOC(8980) : move_tomem_8(0x6, A0 + 0x24); // MOVE.B	#$06,36(A0)
  rom_8986(); // Detected flow into next function
}
ROMFUNC(rom_8986) {
  DEF_ROMLOC(8986) : return; // RTS
}
ROMFUNC(rom_8988) {
  DEF_ROMLOC(8988) : rom_DC40();          // BSR.W	$DC40
  DEF_ROMLOC(898C) : rom_DC92();          // BSR.W	$DC92
  DEF_ROMLOC(8990) : tst_mem_8(A0 + 0x1); // TST.B	1(A0)
  DEF_ROMLOC(8994) : if (CCR_PL) {
    rom_8998();
    return;
  }                          // BPL.B	$8998
  DEF_ROMLOC(8996) : return; // RTS
}
ROMFUNC(rom_8998) {
  DEF_ROMLOC(8998) : rom_DCCE(); // BSR.W	$DCCE
  DEF_ROMLOC(899C) : return;     // RTS
}
ROMFUNC(rom_899E) {
  u8 switchindex = 0;
  DEF_ROMLOC(899E) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(89A0) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(89A4)
      : move_toreg_16(read_16(0x89AC + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(89A8): goto rom_89AC + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(89A8) : switch (switchindex) {
  case 0:
    rom_89B8();
    break;
  case 1:
    rom_8A02();
    break;
  case 2:
    rom_8A44();
    break;
  case 3:
    rom_8A6A();
    break;
  case 4:
    rom_8ACA();
    break;
  case 5:
    rom_8A56();
    break;
  }
}
ROMFUNC(rom_89B8) {
  DEF_ROMLOC(89B8) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(89BC)
      : move_tomem_32(0x8DC4, A0 + 0x4);              // MOVE.L	#$00008DC4,4(A0)
  DEF_ROMLOC(89C4) : move_tomem_16(0x42B8, A0 + 0x2); // MOVE.W	#$42B8,2(A0)
  DEF_ROMLOC(89CA) : cmp_tomem_8(0x3, 0xFFFFFE10);    // CMPI.B	#$03,$FE10
  DEF_ROMLOC(89D0) : if (!CCR_EQ) goto rom_89DC;      // BNE.B	$89DC
  DEF_ROMLOC(89D2) : move_tomem_16(0x44E0, A0 + 0x2); // MOVE.W	#$44E0,2(A0)
  DEF_ROMLOC(89D8) : add_tomem_8(0x2, A0 + 0x1A);     // ADDQ.B	#$02,26(A0)
  DEF_ROMLOC(89DC) : cmp_tomem_8(0x5, 0xFFFFFE10);    // CMPI.B	#$05,$FE10
  DEF_ROMLOC(89E2) : if (!CCR_EQ) goto rom_89EA;      // BNE.B	$89EA
  DEF_ROMLOC(89E4) : move_tomem_16(0x43F5, A0 + 0x2); // MOVE.W	#$43F5,2(A0)
  DEF_ROMLOC(89EA) : or_tomem_8(0x4, A0 + 0x1);       // ORI.B	#$04,1(A0)
  DEF_ROMLOC(89F0) : move_tomem_8(0x4, A0 + 0x18);    // MOVE.B	#$04,24(A0)
  DEF_ROMLOC(89F6) : move_tomem_8(0x7, A0 + 0x38);    // MOVE.B	#$07,56(A0)
  DEF_ROMLOC(89FC) : move_tomem_8(0x44, A0 + 0x19);   // MOVE.B	#$44,25(A0)
  rom_8A02();
}
ROMFUNC(rom_8A02) {
  DEF_ROMLOC(8A02) : tst_mem_8(A0 + 0x3A);      // TST.B	58(A0)
  DEF_ROMLOC(8A06) : if (CCR_EQ) goto rom_8A14; // BEQ.B	$8A14
  DEF_ROMLOC(8A08) : tst_mem_8(A0 + 0x38);      // TST.B	56(A0)
  DEF_ROMLOC(8A0C) : if (CCR_EQ) {
    rom_8AD0();
    return;
  }                                                // BEQ.W	$8AD0
  DEF_ROMLOC(8A10) : sub_tomem_8(0x1, A0 + 0x38);  // SUBQ.B	#$01,56(A0)
  DEF_ROMLOC(8A14) : move_toreg_16(0x20, &D1);     // MOVE.W	#$0020,D1
  DEF_ROMLOC(8A18) : rom_7ACA();                   // BSR.W	$7ACA
  DEF_ROMLOC(8A1C) : tst_mem_8(A0 + 0x28);         // TST.B	40(A0)
  DEF_ROMLOC(8A20) : if (CCR_PL) goto rom_8A40;    // BPL.B	$8A40
  DEF_ROMLOC(8A22) : btst_tomem_8(0x3, A1 + 0x22); // BTST.B	#$03,34(A1)
  DEF_ROMLOC(8A28) : if (CCR_EQ) goto rom_8A40;    // BEQ.B	$8A40
  DEF_ROMLOC(8A2A) : bclr_tomem_8(0x0, A0 + 0x1);  // BCLR.B	#$00,1(A0)
  DEF_ROMLOC(8A30)
      : move_toreg_16(read_16(A1 + 0x8), &D0); // MOVE.W	8(A1),D0
  DEF_ROMLOC(8A34)
      : sub_toreg_16(read_16(A0 + 0x8), &D0);     // SUB.W	8(A0),D0
  DEF_ROMLOC(8A38) : if (CCR_CC) goto rom_8A40;   // BCC.B	$8A40
  DEF_ROMLOC(8A3A) : bset_tomem_8(0x0, A0 + 0x1); // BSET.B	#$00,1(A0)
  DEF_ROMLOC(8A40) : rom_FD38();
  return; // BRA.W	$FD38
}
ROMFUNC(rom_8A56) {
  DEF_ROMLOC(8A56) : move_toreg_16(0x20, &D1); // MOVE.W	#$0020,D1
  DEF_ROMLOC(8A5A) : rom_7C3E();               // BSR.W	$7C3E
  DEF_ROMLOC(8A5E)
      : move_toreg_16(read_16(A0 + 0x8), &D2); // MOVE.W	8(A0),D2
  DEF_ROMLOC(8A62) : rom_81AC();               // BSR.W	$81AC
  rom_FD38();
  return; // BRA.W	$FD38
}
ROMFUNC(rom_8A44) {
  DEF_ROMLOC(8A44) : tst_mem_8(A0 + 0x38); // TST.B	56(A0)
  DEF_ROMLOC(8A48) : if (CCR_EQ) {
    rom_8AD6();
    return;
  }                                                // BEQ.W	$8AD6
  DEF_ROMLOC(8A4C) : move_tomem_8(0x1, A0 + 0x3A); // MOVE.B	#$01,58(A0)
  DEF_ROMLOC(8A52) : sub_tomem_8(0x1, A0 + 0x38);  // SUBQ.B	#$01,56(A0)
  // DEF_ROMLOC(8A56): move_toreg_16(0x20, &D1); // MOVE.W	#$0020,D1
  // DEF_ROMLOC(8A5A): rom_7C3E(); // BSR.W	$7C3E
  // DEF_ROMLOC(8A5E): move_toreg_16(read_16(A0 + 0x8), &D2); // MOVE.W	8(A0),D2
  // DEF_ROMLOC(8A62): rom_81AC(); // BSR.W	$81AC
  // rom_FD38(); return; // BRA.W	$FD38
  rom_8A56();
  return;
}
ROMFUNC(rom_8A6A) {
  DEF_ROMLOC(8A6A) : tst_mem_8(A0 + 0x38);        // TST.B	56(A0)
  DEF_ROMLOC(8A6E) : if (CCR_EQ) goto rom_8ABA;   // BEQ.B	$8ABA
  DEF_ROMLOC(8A70) : tst_mem_8(A0 + 0x3A);        // TST.B	58(A0)
  DEF_ROMLOC(8A74) : if (!CCR_EQ) goto rom_8A80;  // BNE.W	$8A80
  DEF_ROMLOC(8A78) : sub_tomem_8(0x1, A0 + 0x38); // SUBQ.B	#$01,56(A0)
  rom_DC92();
  return;                                            // BRA.W	$DC92
  DEF_ROMLOC(8A80) : sub_tomem_8(0x1, A0 + 0x38);    // SUBQ.B	#$01,56(A0)
  DEF_ROMLOC(8A84) : rom_8A56();                     // BSR.W	$8A56
  DEF_ROMLOC(8A88) : move_toreg_32(0xFFFFD000, &A1); // LEA.L	$D000,A1
  DEF_ROMLOC(8A8C) : btst_tomem_8(0x3, A1 + 0x22);   // BTST.B	#$03,34(A1)
  DEF_ROMLOC(8A92) : if (CCR_EQ) goto rom_8AAC;      // BEQ.B	$8AAC
  DEF_ROMLOC(8A94) : tst_mem_8(A0 + 0x38);           // TST.B	56(A0)
  DEF_ROMLOC(8A98) : if (!CCR_EQ) goto rom_8AB8;     // BNE.B	$8AB8
  DEF_ROMLOC(8A9A) : bclr_tomem_8(0x3, A1 + 0x22);   // BCLR.B	#$03,34(A1)
  DEF_ROMLOC(8AA0) : bclr_tomem_8(0x5, A1 + 0x22);   // BCLR.B	#$05,34(A1)
  DEF_ROMLOC(8AA6) : move_tomem_8(0x1, A1 + 0x1D);   // MOVE.B	#$01,29(A1)
  DEF_ROMLOC(8AAC) : move_tomem_8(0x0, A0 + 0x3A);   // MOVE.B	#$00,58(A0)
  DEF_ROMLOC(8AB2) : move_tomem_8(0x6, A0 + 0x24);   // MOVE.B	#$06,36(A0)
  DEF_ROMLOC(8AB8) : return;                         // RTS
  DEF_ROMLOC(8ABA) : rom_DC40();                     // BSR.W	$DC40
  DEF_ROMLOC(8ABE) : rom_DC92();                     // BSR.W	$DC92
  DEF_ROMLOC(8AC2) : tst_mem_8(A0 + 0x1);            // TST.B	1(A0)
  DEF_ROMLOC(8AC6) : if (CCR_PL) {
    rom_8ACA();
    return;
  }                          // BPL.B	$8ACA
  DEF_ROMLOC(8AC8) : return; // RTS
}
ROMFUNC(rom_8ACA) {
  DEF_ROMLOC(8ACA) : rom_DCCE(); // BSR.W	$DCCE
  DEF_ROMLOC(8ACE) : return;     // RTS
}
ROMFUNC(rom_8AD0) {
  DEF_ROMLOC(8AD0) : move_tomem_8(0x0, A0 + 0x3A); // MOVE.B	#$00,58(A0)
  rom_8AD6();
}
ROMFUNC(rom_8AD6) {
  DEF_ROMLOC(8AD6) : move_toreg_32(0x8B98, &A4);   // LEA.L	$00008B98,A4
  DEF_ROMLOC(8ADC) : btst_tomem_8(0x0, A0 + 0x28); // BTST.B	#$00,40(A0)
  DEF_ROMLOC(8AE2) : if (CCR_EQ) goto rom_8AEA;    // BEQ.B	$8AEA
  DEF_ROMLOC(8AE4) : move_toreg_32(0x8BA0, &A4);   // LEA.L	$00008BA0,A4
  DEF_ROMLOC(8AEA) : move_toreg_32(0x7, &D1);      // MOVEQ.L	$07,D1
  DEF_ROMLOC(8AEC) : add_tomem_8(0x1, A0 + 0x1A);  // ADDQ.B	#$01,26(A0)
  rom_8B04();                                      // BRA.B	$8B04
}
ROMFUNC(rom_8AF2) {
  DEF_ROMLOC(8AF2) : move_tomem_8(0x0, A0 + 0x3A); // MOVE.B	#$00,58(A0)
  rom_8AF8(); // Detected flow into next function
}
ROMFUNC(rom_8AF8) {
  DEF_ROMLOC(8AF8) : move_toreg_32(0x8B7E, &A4);  // LEA.L	$00008B7E,A4
  DEF_ROMLOC(8AFE) : move_toreg_32(0x18, &D1);    // MOVEQ.L	$18,D1
  DEF_ROMLOC(8B00) : add_tomem_8(0x2, A0 + 0x1A); // ADDQ.B	#$02,26(A0)
  rom_8B04(); // Detected flow into next function
}
ROMFUNC(rom_8B04) {
  DEF_ROMLOC(8B04) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(8B06)
      : move_toreg_8(read_8(A0 + 0x1A), &D0); // MOVE.B	26(A0),D0
  DEF_ROMLOC(8B0A) : add_toreg_16(D0, &D0);   // ADD.W	D0,D0
  DEF_ROMLOC(8B0C)
      : move_toreg_32(read_32(A0 + 0x4), &A3); // MOVEA.L	4(A0),A3
  DEF_ROMLOC(8B10)
      : add_toreg_16(read_16((s32)A3 + (s8)0x0 + (s16)D0),
                     &A3);                        // ADDA.W	0(A3,D0),A3
  DEF_ROMLOC(8B14) : add_toreg_16(0x1, &A3);      // ADDQ.W	#$01,A3
  DEF_ROMLOC(8B16) : bset_tomem_8(0x5, A0 + 0x1); // BSET.B	#$05,1(A0)
  DEF_ROMLOC(8B1C)
      : move_toreg_8(read_8(A0 + 0x0), &D4); // MOVE.B	0(A0),D4
  DEF_ROMLOC(8B20)
      : move_toreg_8(read_8(A0 + 0x1), &D5);       // MOVE.B	1(A0),D5
  DEF_ROMLOC(8B24) : move_toreg_32(A0, &A1);       // MOVEA.L	A0,A1
  goto rom_8B30;                                   // BRA.B	$8B30
  DEF_ROMLOC(8B28) : rom_E11A();                   // BSR.W	$E11A
  DEF_ROMLOC(8B2C) : if (!CCR_EQ) goto rom_8B70;   // BNE.B	$8B70
  DEF_ROMLOC(8B2E) : add_toreg_16(0x5, &A3);       // ADDQ.W	#$05,A3
  DEF_ROMLOC(8B30) : move_tomem_8(0x6, A1 + 0x24); // MOVE.B	#$06,36(A1)
  DEF_ROMLOC(8B36) : move_tomem_8(D4, A1 + 0x0);   // MOVE.B	D4,0(A1)
  DEF_ROMLOC(8B3A) : move_tomem_32(A3, A1 + 0x4);  // MOVE.L	A3,4(A1)
  DEF_ROMLOC(8B3E) : move_tomem_8(D5, A1 + 0x1);   // MOVE.B	D5,1(A1)
  DEF_ROMLOC(8B42)
      : move_tomem_16(read_16(A0 + 0x8), A1 + 0x8); // MOVE.W	8(A0),8(A1)
  DEF_ROMLOC(8B48)
      : move_tomem_16(read_16(A0 + 0xC), A1 + 0xC); // MOVE.W	12(A0),12(A1)
  DEF_ROMLOC(8B4E)
      : move_tomem_16(read_16(A0 + 0x2), A1 + 0x2); // MOVE.W	2(A0),2(A1)
  DEF_ROMLOC(8B54)
      : move_tomem_8(read_8(A0 + 0x18), A1 + 0x18); // MOVE.B	24(A0),24(A1)
  DEF_ROMLOC(8B5A)
      : move_tomem_8(read_8(A0 + 0x19), A1 + 0x19); // MOVE.B	25(A0),25(A1)
  DEF_ROMLOC(8B60)
      : move_tomem_8(read_8(A4++), A1 + 0x38);  // MOVE.B	(A4)+,56(A1)
  DEF_ROMLOC(8B64) : cmp_toreg_32(A0, &A1);     // CMPA.L	A0,A1
  DEF_ROMLOC(8B66) : if (CCR_CC) goto rom_8B6C; // BCC.B	$8B6C
  DEF_ROMLOC(8B68) : rom_DCB0();                // BSR.W	$DCB0
  DEF_ROMLOC(8B6C) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_8B28;                             // DBF.W	D1,$8B28
  DEF_ROMLOC(8B70) : rom_DC92();               // BSR.W	$DC92
  DEF_ROMLOC(8B74) : move_toreg_16(0xB9, &D0); // MOVE.W	#$00B9,D0
  DEF_ROMLOC(8B78) : rom_1394();               // JMP	$00001394
}