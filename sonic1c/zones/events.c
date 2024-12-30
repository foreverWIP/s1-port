// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"


ROMFUNC(rom_73B6) {
  u8 switchindex = 0;
  DEF_ROMLOC(73B6) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(73B8) : move_toreg_8(read_8(0xFFFFFE10), &D0);
  switchindex = D0;                         // MOVE.B	$FE10,D0
  DEF_ROMLOC(73BC) : add_toreg_16(D0, &D0); // ADD.W	D0,D0
  DEF_ROMLOC(73BE)
      : move_toreg_16(read_16(0x741A + (s16)(D0 & 0xffff)),
                      &D0); // MOVE.W	90(PC,D0),D0
  // DEF_ROMLOC(73C2): rom_741A + (s16)(D0 & 0xffff)(); // JSR	86(PC,D0)
  DEF_ROMLOC(73C2) : switch (switchindex) {
  case 0:
    rom_7428();
    break;
  case 1:
    rom_753C();
    break;
  case 2:
    rom_75D8();
    break;
  case 3:
    rom_7770();
    break;
  case 4:
    rom_77E6();
    break;
  case 5:
    rom_7888();
    break;
  case 6:
    rom_79A4();
    break;
  }
  DEF_ROMLOC(73C6) : move_toreg_32(0x2, &D1); // MOVEQ.L	$02,D1
  DEF_ROMLOC(73C8)
      : move_toreg_16(read_16(0xFFFFF726), &D0); // MOVE.W	$F726,D0
  DEF_ROMLOC(73CC)
      : sub_toreg_16(read_16(0xFFFFF72E), &D0); // SUB.W	$F72E,D0
  DEF_ROMLOC(73D0) : if (CCR_EQ) goto rom_73F4; // BEQ.B	$73F4
  DEF_ROMLOC(73D2) : if (CCR_CC) goto rom_73F6; // BCC.B	$73F6
  DEF_ROMLOC(73D4) : neg_reg_16(&D1);           // NEG.W	D1
  DEF_ROMLOC(73D6)
      : move_toreg_16(read_16(0xFFFFF704), &D0); // MOVE.W	$F704,D0
  DEF_ROMLOC(73DA)
      : cmp_toreg_16(read_16(0xFFFFF726), &D0);     // CMP.W	$F726,D0
  DEF_ROMLOC(73DE) : if (CCR_LS) goto rom_73EA;     // BLS.B	$73EA
  DEF_ROMLOC(73E0) : move_tomem_16(D0, 0xFFFFF72E); // MOVE.W	D0,$F72E
  DEF_ROMLOC(73E4)
      : and_tomem_16(0xFFFFFFFE, 0xFFFFF72E);       // ANDI.W	#$FFFE,$F72E
  DEF_ROMLOC(73EA) : add_tomem_16(D1, 0xFFFFF72E);  // ADD.W	D1,$F72E
  DEF_ROMLOC(73EE) : move_tomem_8(0x1, 0xFFFFF75C); // MOVE.B	#$01,$F75C
  DEF_ROMLOC(73F4) : return;                        // RTS
  DEF_ROMLOC(73F6)
      : move_toreg_16(read_16(0xFFFFF704), &D0); // MOVE.W	$F704,D0
  DEF_ROMLOC(73FA) : add_toreg_16(0x8, &D0);     // ADDQ.W	#$08,D0
  DEF_ROMLOC(73FC)
      : cmp_toreg_16(read_16(0xFFFFF72E), &D0);     // CMP.W	$F72E,D0
  DEF_ROMLOC(7400) : if (CCR_CS) goto rom_740E;     // BCS.B	$740E
  DEF_ROMLOC(7402) : btst_tomem_8(0x1, 0xFFFFD022); // BTST.B	#$01,$D022
  DEF_ROMLOC(7408) : if (CCR_EQ) goto rom_740E;     // BEQ.B	$740E
  DEF_ROMLOC(740A) : add_toreg_16(D1, &D1);         // ADD.W	D1,D1
  DEF_ROMLOC(740C) : add_toreg_16(D1, &D1);         // ADD.W	D1,D1
  DEF_ROMLOC(740E) : add_tomem_16(D1, 0xFFFFF72E);  // ADD.W	D1,$F72E
  DEF_ROMLOC(7412) : move_tomem_8(0x1, 0xFFFFF75C); // MOVE.B	#$01,$F75C
  DEF_ROMLOC(7418) : return;                        // RTS
}
ROMFUNC(rom_7428) {
  u8 switchindex = 0;
  DEF_ROMLOC(7428) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(742A) : move_toreg_8(read_8(0xFFFFFE11), &D0);
  switchindex = D0;                         // MOVE.B	$FE11,D0
  DEF_ROMLOC(742E) : add_toreg_16(D0, &D0); // ADD.W	D0,D0
  DEF_ROMLOC(7430)
      : move_toreg_16(read_16(0x7438 + (s16)(D0 & 0xffff)),
                      &D0); // MOVE.W	6(PC,D0),D0
  // DEF_ROMLOC(7434): goto rom_7438 + (s16)(D0 & 0xffff); // JMP	2(PC,D0)
  DEF_ROMLOC(7434) : switch (switchindex) {
  case 0:
    rom_743E();
    break;
  case 1:
    rom_7454();
    break;
  case 2:
    rom_7486();
    break;
  }
}
ROMFUNC(rom_743E) {
  DEF_ROMLOC(743E) : move_tomem_16(0x300, 0xFFFFF726); // MOVE.W
                                                       // #$0300,$F726
  DEF_ROMLOC(7444) : cmp_tomem_16(0x1780, 0xFFFFF700); // CMPI.W
                                                       // #$1780,$F700
  DEF_ROMLOC(744A) : if (CCR_CS) goto rom_7452;        // BCS.B	$7452
  DEF_ROMLOC(744C) : move_tomem_16(0x400, 0xFFFFF726); // MOVE.W
                                                       // #$0400,$F726
  DEF_ROMLOC(7452) : return;                           // RTS
}
ROMFUNC(rom_7454) {
  DEF_ROMLOC(7454) : move_tomem_16(0x300, 0xFFFFF726); // MOVE.W
                                                       // #$0300,$F726
  DEF_ROMLOC(745A) : cmp_tomem_16(0xED0, 0xFFFFF700);  // CMPI.W	#$0ED0,$F700
  DEF_ROMLOC(7460) : if (CCR_CS) goto rom_7484;        // BCS.B	$7484
  DEF_ROMLOC(7462) : move_tomem_16(0x200, 0xFFFFF726); // MOVE.W
                                                       // #$0200,$F726
  DEF_ROMLOC(7468) : cmp_tomem_16(0x1600, 0xFFFFF700); // CMPI.W
                                                       // #$1600,$F700
  DEF_ROMLOC(746E) : if (CCR_CS) goto rom_7484;        // BCS.B	$7484
  DEF_ROMLOC(7470) : move_tomem_16(0x400, 0xFFFFF726); // MOVE.W
                                                       // #$0400,$F726
  DEF_ROMLOC(7476) : cmp_tomem_16(0x1D60, 0xFFFFF700); // CMPI.W
                                                       // #$1D60,$F700
  DEF_ROMLOC(747C) : if (CCR_CS) goto rom_7484;        // BCS.B	$7484
  DEF_ROMLOC(747E) : move_tomem_16(0x300, 0xFFFFF726); // MOVE.W
                                                       // #$0300,$F726
  DEF_ROMLOC(7484) : return;                           // RTS
}
ROMFUNC(rom_7486) {
  u8 switchindex = 0;
  DEF_ROMLOC(7486) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(7488) : move_toreg_8(read_8(0xFFFFF742), &D0);
  switchindex = D0 / 2; // MOVE.B	$F742,D0
  DEF_ROMLOC(748C)
      : move_toreg_16(read_16(0x7494 + (s16)(D0 & 0xffff)),
                      &D0); // MOVE.W	6(PC,D0),D0
  // DEF_ROMLOC(7490): goto rom_7494 + (s16)(D0 & 0xffff); // JMP	2(PC,D0)
  DEF_ROMLOC(7490) : switch (switchindex) {
  case 0:
    rom_749A();
    break;
  case 1:
    rom_74EE();
    break;
  case 2:
    rom_7534();
    break;
  }
}
ROMFUNC(rom_749A) {
  DEF_ROMLOC(749A) : move_tomem_16(0x300, 0xFFFFF726); // MOVE.W
                                                       // #$0300,$F726
  DEF_ROMLOC(74A0) : cmp_tomem_16(0x380, 0xFFFFF700);  // CMPI.W	#$0380,$F700
  DEF_ROMLOC(74A6) : if (CCR_CS) goto rom_74E0;        // BCS.B	$74E0
  DEF_ROMLOC(74A8) : move_tomem_16(0x310, 0xFFFFF726); // MOVE.W
                                                       // #$0310,$F726
  DEF_ROMLOC(74AE) : cmp_tomem_16(0x960, 0xFFFFF700);  // CMPI.W	#$0960,$F700
  DEF_ROMLOC(74B4) : if (CCR_CS) goto rom_74E0;        // BCS.B	$74E0
  DEF_ROMLOC(74B6) : cmp_tomem_16(0x280, 0xFFFFF704);  // CMPI.W	#$0280,$F704
  DEF_ROMLOC(74BC) : if (CCR_CS) goto rom_74E2;        // BCS.B	$74E2
  DEF_ROMLOC(74BE) : move_tomem_16(0x400, 0xFFFFF726); // MOVE.W
                                                       // #$0400,$F726
  DEF_ROMLOC(74C4) : cmp_tomem_16(0x1380, 0xFFFFF700); // CMPI.W
                                                       // #$1380,$F700
  DEF_ROMLOC(74CA) : if (CCR_CC) goto rom_74D8;        // BCC.B	$74D8
  DEF_ROMLOC(74CC) : move_tomem_16(0x4C0, 0xFFFFF726); // MOVE.W
                                                       // #$04C0,$F726
  DEF_ROMLOC(74D2) : move_tomem_16(0x4C0, 0xFFFFF72E); // MOVE.W
                                                       // #$04C0,$F72E
  DEF_ROMLOC(74D8) : cmp_tomem_16(0x1700, 0xFFFFF700); // CMPI.W
                                                       // #$1700,$F700
  DEF_ROMLOC(74DE) : if (CCR_CC) goto rom_74E2;        // BCC.B	$74E2
  DEF_ROMLOC(74E0) : return;                           // RTS
  DEF_ROMLOC(74E2) : move_tomem_16(0x300, 0xFFFFF726); // MOVE.W
                                                       // #$0300,$F726
  DEF_ROMLOC(74E8) : add_tomem_8(0x2, 0xFFFFF742);     // ADDQ.B	#$02,$F742
  DEF_ROMLOC(74EC) : return;                           // RTS
}
ROMFUNC(rom_74EE) {
  DEF_ROMLOC(74EE) : cmp_tomem_16(0x960, 0xFFFFF700);  // CMPI.W	#$0960,$F700
  DEF_ROMLOC(74F4) : if (CCR_CC) goto rom_74FA;        // BCC.B	$74FA
  DEF_ROMLOC(74F6) : sub_tomem_8(0x2, 0xFFFFF742);     // SUBQ.B	#$02,$F742
  DEF_ROMLOC(74FA) : cmp_tomem_16(0x2960, 0xFFFFF700); // CMPI.W
                                                       // #$2960,$F700
  DEF_ROMLOC(7500) : if (CCR_CS) goto rom_7532;        // BCS.B	$7532
  DEF_ROMLOC(7502) : rom_E11A();                       // BSR.W	$E11A
  DEF_ROMLOC(7506) : if (!CCR_EQ) goto rom_751A;       // BNE.B	$751A
  DEF_ROMLOC(7508) : move_tomem_8(0x3D, A1 + 0x0);     // MOVE.B	#$3D,0(A1)
  DEF_ROMLOC(750E) : move_tomem_16(0x2A60, A1 + 0x8);  // MOVE.W	#$2A60,8(A1)
  DEF_ROMLOC(7514) : move_tomem_16(0x280, A1 + 0xC);   // MOVE.W	#$0280,12(A1)
  DEF_ROMLOC(751A) : move_toreg_16(0x8C, &D0);         // MOVE.W	#$008C,D0
  DEF_ROMLOC(751E) : rom_138E();                       // BSR.W	$138E
  DEF_ROMLOC(7522) : move_tomem_8(0x1, 0xFFFFF7AA);    // MOVE.B	#$01,$F7AA
  DEF_ROMLOC(7528) : add_tomem_8(0x2, 0xFFFFF742);     // ADDQ.B	#$02,$F742
  DEF_ROMLOC(752C) : move_toreg_32(0x11, &D0);         // MOVEQ.L	$11,D0
  rom_1578();
  return;                    // BRA.W	$1578
  DEF_ROMLOC(7532) : return; // RTS
}
ROMFUNC(rom_7534) {
  DEF_ROMLOC(7534)
      : move_tomem_16(read_16(0xFFFFF700),
                      0xFFFFF728); // MOVE.W	$F700,$F728
  DEF_ROMLOC(753A) : return;       // RTS
}
ROMFUNC(rom_753C) {
  u8 switchindex = 0;
  DEF_ROMLOC(753C) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(753E) : move_toreg_8(read_8(0xFFFFFE11), &D0);
  switchindex = D0;                         // MOVE.B	$FE11,D0
  DEF_ROMLOC(7542) : add_toreg_16(D0, &D0); // ADD.W	D0,D0
  DEF_ROMLOC(7544)
      : move_toreg_16(read_16(0x754C + (s16)(D0 & 0xffff)),
                      &D0); // MOVE.W	6(PC,D0),D0
  // DEF_ROMLOC(7548): goto rom_754C + (s16)(D0 & 0xffff); // JMP	2(PC,D0)
  DEF_ROMLOC(7548) : switch (switchindex) {
  case 0:
    rom_7554();
    break;
  case 1:
    rom_7554();
    break;
  case 2:
    rom_7556();
    break;
  case 3:
    rom_75B0();
    break;
  }
}
ROMFUNC(rom_7554) {
  DEF_ROMLOC(7554) : return; // RTS
}
ROMFUNC(rom_7556) {
  DEF_ROMLOC(7556) : tst_mem_8(0xFFFFF7EF);            // TST.B	$F7EF
  DEF_ROMLOC(755A) : if (CCR_EQ) goto rom_7572;        // BEQ.B	$7572
  DEF_ROMLOC(755C) : move_toreg_32(0xFFFFA506, &A1);   // LEA.L	$A506,A1
  DEF_ROMLOC(7560) : cmp_tomem_8(0x7, A1);             // CMPI.B	#$07,(A1)
  DEF_ROMLOC(7564) : if (CCR_EQ) goto rom_7572;        // BEQ.B	$7572
  DEF_ROMLOC(7566) : move_tomem_8(0x7, A1);            // MOVE.B	#$07,(A1)
  DEF_ROMLOC(756A) : move_toreg_16(0xB7, &D0);         // MOVE.W	#$00B7,D0
  DEF_ROMLOC(756E) : rom_1394();                       // BSR.W	$1394
  DEF_ROMLOC(7572) : tst_mem_8(0xFFFFF742);            // TST.B	$F742
  DEF_ROMLOC(7576) : if (!CCR_EQ) goto rom_75AE;       // BNE.B	$75AE
  DEF_ROMLOC(7578) : cmp_tomem_16(0x1CA0, 0xFFFFF700); // CMPI.W
                                                       // #$1CA0,$F700
  DEF_ROMLOC(757E) : if (CCR_CS) goto rom_75AC;        // BCS.B	$75AC
  DEF_ROMLOC(7580) : cmp_tomem_16(0x600, 0xFFFFF704);  // CMPI.W	#$0600,$F704
  DEF_ROMLOC(7586) : if (CCR_CC) goto rom_75AC;        // BCC.B	$75AC
  DEF_ROMLOC(7588) : rom_E11A();                       // BSR.W	$E11A
  DEF_ROMLOC(758C) : if (!CCR_EQ) goto rom_7594;       // BNE.B	$7594
  DEF_ROMLOC(758E) : move_tomem_8(0x77, A1 + 0x0);     // MOVE.B	#$77,0(A1)
  DEF_ROMLOC(7594) : move_toreg_16(0x8C, &D0);         // MOVE.W	#$008C,D0
  DEF_ROMLOC(7598) : rom_138E();                       // BSR.W	$138E
  DEF_ROMLOC(759C) : move_tomem_8(0x1, 0xFFFFF7AA);    // MOVE.B	#$01,$F7AA
  DEF_ROMLOC(75A2) : add_tomem_8(0x2, 0xFFFFF742);     // ADDQ.B	#$02,$F742
  DEF_ROMLOC(75A6) : move_toreg_32(0x11, &D0);         // MOVEQ.L	$11,D0
  rom_1578();
  return;                    // BRA.W	$1578
  DEF_ROMLOC(75AC) : return; // RTS
  DEF_ROMLOC(75AE) : return; // RTS
}
ROMFUNC(rom_75B0) {
  DEF_ROMLOC(75B0) : cmp_tomem_16(0xD00, 0xFFFFF700);  // CMPI.W	#$0D00,$F700
  DEF_ROMLOC(75B6) : if (CCR_CS) goto rom_75D6;        // BCS.B	$75D6
  DEF_ROMLOC(75B8) : cmp_tomem_16(0x18, 0xFFFFD00C);   // CMPI.W	#$0018,$D00C
  DEF_ROMLOC(75BE) : if (CCR_CC) goto rom_75D6;        // BCC.B	$75D6
  DEF_ROMLOC(75C0) : clr_mem_8(0xFFFFFE30);            // CLR.B	$FE30
  DEF_ROMLOC(75C4) : move_tomem_16(0x1, 0xFFFFFE02);   // MOVE.W	#$0001,$FE02
  DEF_ROMLOC(75CA) : move_tomem_16(0x502, 0xFFFFFE10); // MOVE.W
                                                       // #$0502,$FE10
  DEF_ROMLOC(75D0) : move_tomem_8(0x1, 0xFFFFF7C8);    // MOVE.B	#$01,$F7C8
  DEF_ROMLOC(75D6) : return;                           // RTS
}
ROMFUNC(rom_75D8) {
  u8 switchindex = 0;
  DEF_ROMLOC(75D8) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(75DA) : move_toreg_8(read_8(0xFFFFFE11), &D0);
  switchindex = D0;                         // MOVE.B	$FE11,D0
  DEF_ROMLOC(75DE) : add_toreg_16(D0, &D0); // ADD.W	D0,D0
  DEF_ROMLOC(75E0)
      : move_toreg_16(read_16(0x75E8 + (s16)(D0 & 0xffff)),
                      &D0); // MOVE.W	6(PC,D0),D0
  // DEF_ROMLOC(75E4): goto rom_75E8 + (s16)(D0 & 0xffff); // JMP	2(PC,D0)
  DEF_ROMLOC(75E4) : switch (switchindex) {
  case 0:
    rom_75EE();
    break;
  case 1:
    rom_76F2();
    break;
  case 2:
    rom_7708();
    break;
  }
}
ROMFUNC(rom_75EE) {
  u8 switchindex = 0;
  DEF_ROMLOC(75EE) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(75F0) : move_toreg_8(read_8(0xFFFFF742), &D0);
  switchindex = D0 / 2; // MOVE.B	$F742,D0
  DEF_ROMLOC(75F4)
      : move_toreg_16(read_16(0x75FC + (s16)(D0 & 0xffff)),
                      &D0); // MOVE.W	6(PC,D0),D0
  // DEF_ROMLOC(75F8): goto rom_75FC + (s16)(D0 & 0xffff); // JMP	2(PC,D0)
  DEF_ROMLOC(75F8) : switch (switchindex) {
  case 0:
    rom_7604();
    break;
  case 1:
    rom_7634();
    break;
  case 2:
    rom_7678();
    break;
  case 3:
    rom_76A2();
    break;
  }
}
ROMFUNC(rom_7604) {
  DEF_ROMLOC(7604) : move_tomem_16(0x1D0, 0xFFFFF726); // MOVE.W
                                                       // #$01D0,$F726
  DEF_ROMLOC(760A) : cmp_tomem_16(0x700, 0xFFFFF700);  // CMPI.W	#$0700,$F700
  DEF_ROMLOC(7610) : if (CCR_CS) goto rom_7632;        // BCS.B	$7632
  DEF_ROMLOC(7612) : move_tomem_16(0x220, 0xFFFFF726); // MOVE.W
                                                       // #$0220,$F726
  DEF_ROMLOC(7618) : cmp_tomem_16(0xD00, 0xFFFFF700);  // CMPI.W	#$0D00,$F700
  DEF_ROMLOC(761E) : if (CCR_CS) goto rom_7632;        // BCS.B	$7632
  DEF_ROMLOC(7620) : move_tomem_16(0x340, 0xFFFFF726); // MOVE.W
                                                       // #$0340,$F726
  DEF_ROMLOC(7626) : cmp_tomem_16(0x340, 0xFFFFF704);  // CMPI.W	#$0340,$F704
  DEF_ROMLOC(762C) : if (CCR_CS) goto rom_7632;        // BCS.B	$7632
  DEF_ROMLOC(762E) : add_tomem_8(0x2, 0xFFFFF742);     // ADDQ.B	#$02,$F742
  DEF_ROMLOC(7632) : return;                           // RTS
}
ROMFUNC(rom_7634) {
  DEF_ROMLOC(7634) : cmp_tomem_16(0x340, 0xFFFFF704);  // CMPI.W	#$0340,$F704
  DEF_ROMLOC(763A) : if (CCR_CC) goto rom_7642;        // BCC.B	$7642
  DEF_ROMLOC(763C) : sub_tomem_8(0x2, 0xFFFFF742);     // SUBQ.B	#$02,$F742
  DEF_ROMLOC(7640) : return;                           // RTS
  DEF_ROMLOC(7642) : move_tomem_16(0x0, 0xFFFFF72C);   // MOVE.W	#$0000,$F72C
  DEF_ROMLOC(7648) : cmp_tomem_16(0xE00, 0xFFFFF700);  // CMPI.W	#$0E00,$F700
  DEF_ROMLOC(764E) : if (CCR_CC) goto rom_7676;        // BCC.B	$7676
  DEF_ROMLOC(7650) : move_tomem_16(0x340, 0xFFFFF72C); // MOVE.W
                                                       // #$0340,$F72C
  DEF_ROMLOC(7656) : move_tomem_16(0x340, 0xFFFFF726); // MOVE.W
                                                       // #$0340,$F726
  DEF_ROMLOC(765C) : cmp_tomem_16(0xA90, 0xFFFFF700);  // CMPI.W	#$0A90,$F700
  DEF_ROMLOC(7662) : if (CCR_CC) goto rom_7676;        // BCC.B	$7676
  DEF_ROMLOC(7664) : move_tomem_16(0x500, 0xFFFFF726); // MOVE.W
                                                       // #$0500,$F726
  DEF_ROMLOC(766A) : cmp_tomem_16(0x370, 0xFFFFF704);  // CMPI.W	#$0370,$F704
  DEF_ROMLOC(7670) : if (CCR_CS) goto rom_7676;        // BCS.B	$7676
  DEF_ROMLOC(7672) : add_tomem_8(0x2, 0xFFFFF742);     // ADDQ.B	#$02,$F742
  DEF_ROMLOC(7676) : return;                           // RTS
}
ROMFUNC(rom_7678) {
  DEF_ROMLOC(7678) : cmp_tomem_16(0x370, 0xFFFFF704);  // CMPI.W	#$0370,$F704
  DEF_ROMLOC(767E) : if (CCR_CC) goto rom_7686;        // BCC.B	$7686
  DEF_ROMLOC(7680) : sub_tomem_8(0x2, 0xFFFFF742);     // SUBQ.B	#$02,$F742
  DEF_ROMLOC(7684) : return;                           // RTS
  DEF_ROMLOC(7686) : cmp_tomem_16(0x500, 0xFFFFF704);  // CMPI.W	#$0500,$F704
  DEF_ROMLOC(768C) : if (CCR_CS) goto rom_76A0;        // BCS.B	$76A0
  DEF_ROMLOC(768E) : cmp_tomem_16(0xB80, 0xFFFFF700);  // CMPI.W	#$0B80,$F700
  DEF_ROMLOC(7694) : if (CCR_CS) goto rom_76A0;        // BCS.B	$76A0
  DEF_ROMLOC(7696) : move_tomem_16(0x500, 0xFFFFF72C); // MOVE.W
                                                       // #$0500,$F72C
  DEF_ROMLOC(769C) : add_tomem_8(0x2, 0xFFFFF742);     // ADDQ.B	#$02,$F742
  DEF_ROMLOC(76A0) : return;                           // RTS
}
ROMFUNC(rom_76A2) {
  DEF_ROMLOC(76A2) : cmp_tomem_16(0xB80, 0xFFFFF700);  // CMPI.W	#$0B80,$F700
  DEF_ROMLOC(76A8) : if (CCR_CC) goto rom_76B8;        // BCC.B	$76B8
  DEF_ROMLOC(76AA) : cmp_tomem_16(0x340, 0xFFFFF72C);  // CMPI.W	#$0340,$F72C
  DEF_ROMLOC(76B0) : if (CCR_EQ) goto rom_76F0;        // BEQ.B	$76F0
  DEF_ROMLOC(76B2) : sub_tomem_16(0x2, 0xFFFFF72C);    // SUBQ.W	#$02,$F72C
  DEF_ROMLOC(76B6) : return;                           // RTS
  DEF_ROMLOC(76B8) : cmp_tomem_16(0x500, 0xFFFFF72C);  // CMPI.W	#$0500,$F72C
  DEF_ROMLOC(76BE) : if (CCR_EQ) goto rom_76CE;        // BEQ.B	$76CE
  DEF_ROMLOC(76C0) : cmp_tomem_16(0x500, 0xFFFFF704);  // CMPI.W	#$0500,$F704
  DEF_ROMLOC(76C6) : if (CCR_CS) goto rom_76F0;        // BCS.B	$76F0
  DEF_ROMLOC(76C8) : move_tomem_16(0x500, 0xFFFFF72C); // MOVE.W
                                                       // #$0500,$F72C
  DEF_ROMLOC(76CE) : cmp_tomem_16(0xE70, 0xFFFFF700);  // CMPI.W	#$0E70,$F700
  DEF_ROMLOC(76D4) : if (CCR_CS) goto rom_76F0;        // BCS.B	$76F0
  DEF_ROMLOC(76D6) : move_tomem_16(0x0, 0xFFFFF72C);   // MOVE.W	#$0000,$F72C
  DEF_ROMLOC(76DC) : move_tomem_16(0x500, 0xFFFFF726); // MOVE.W
                                                       // #$0500,$F726
  DEF_ROMLOC(76E2) : cmp_tomem_16(0x1430, 0xFFFFF700); // CMPI.W
                                                       // #$1430,$F700
  DEF_ROMLOC(76E8) : if (CCR_CS) goto rom_76F0;        // BCS.B	$76F0
  DEF_ROMLOC(76EA) : move_tomem_16(0x210, 0xFFFFF726); // MOVE.W
                                                       // #$0210,$F726
  DEF_ROMLOC(76F0) : return;                           // RTS
}
ROMFUNC(rom_76F2) {
  DEF_ROMLOC(76F2) : move_tomem_16(0x520, 0xFFFFF726); // MOVE.W
                                                       // #$0520,$F726
  DEF_ROMLOC(76F8) : cmp_tomem_16(0x1700, 0xFFFFF700); // CMPI.W
                                                       // #$1700,$F700
  DEF_ROMLOC(76FE) : if (CCR_CS) goto rom_7706;        // BCS.B	$7706
  DEF_ROMLOC(7700) : move_tomem_16(0x200, 0xFFFFF726); // MOVE.W
                                                       // #$0200,$F726
  DEF_ROMLOC(7706) : return;                           // RTS
}
ROMFUNC(rom_7708) {
  u8 switchindex = 0;
  DEF_ROMLOC(7708) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(770A) : move_toreg_8(read_8(0xFFFFF742), &D0);
  switchindex = D0 / 2; // MOVE.B	$F742,D0
  DEF_ROMLOC(770E)
      : move_toreg_16(read_16(0x7716 + (s16)(D0 & 0xffff)),
                      &D0); // MOVE.W	6(PC,D0),D0
  // DEF_ROMLOC(7712): goto rom_7716 + (s16)(D0 & 0xffff); // JMP	2(PC,D0)
  DEF_ROMLOC(7712) : switch (switchindex) {
  case 0:
    rom_771A();
    break;
  case 1:
    rom_7768();
    break;
  }
}
ROMFUNC(rom_771A) {
  DEF_ROMLOC(771A) : move_tomem_16(0x720, 0xFFFFF726); // MOVE.W
                                                       // #$0720,$F726
  DEF_ROMLOC(7720) : cmp_tomem_16(0x1560, 0xFFFFF700); // CMPI.W
                                                       // #$1560,$F700
  DEF_ROMLOC(7726) : if (CCR_CS) goto rom_7766;        // BCS.B	$7766
  DEF_ROMLOC(7728) : move_tomem_16(0x210, 0xFFFFF726); // MOVE.W
                                                       // #$0210,$F726
  DEF_ROMLOC(772E) : cmp_tomem_16(0x17F0, 0xFFFFF700); // CMPI.W
                                                       // #$17F0,$F700
  DEF_ROMLOC(7734) : if (CCR_CS) goto rom_7766;        // BCS.B	$7766
  DEF_ROMLOC(7736) : rom_E11A();                       // BSR.W	$E11A
  DEF_ROMLOC(773A) : if (!CCR_EQ) goto rom_774E;       // BNE.B	$774E
  DEF_ROMLOC(773C) : move_tomem_8(0x73, A1 + 0x0);     // MOVE.B	#$73,0(A1)
  DEF_ROMLOC(7742) : move_tomem_16(0x19F0, A1 + 0x8);  // MOVE.W	#$19F0,8(A1)
  DEF_ROMLOC(7748) : move_tomem_16(0x22C, A1 + 0xC);   // MOVE.W	#$022C,12(A1)
  DEF_ROMLOC(774E) : move_toreg_16(0x8C, &D0);         // MOVE.W	#$008C,D0
  DEF_ROMLOC(7752) : rom_138E();                       // BSR.W	$138E
  DEF_ROMLOC(7756) : move_tomem_8(0x1, 0xFFFFF7AA);    // MOVE.B	#$01,$F7AA
  DEF_ROMLOC(775C) : add_tomem_8(0x2, 0xFFFFF742);     // ADDQ.B	#$02,$F742
  DEF_ROMLOC(7760) : move_toreg_32(0x11, &D0);         // MOVEQ.L	$11,D0
  rom_1578();
  return;                    // BRA.W	$1578
  DEF_ROMLOC(7766) : return; // RTS
}
ROMFUNC(rom_7768) {
  DEF_ROMLOC(7768)
      : move_tomem_16(read_16(0xFFFFF700),
                      0xFFFFF728); // MOVE.W	$F700,$F728
  DEF_ROMLOC(776E) : return;       // RTS
}
ROMFUNC(rom_7770) {
  u8 switchindex = 0;
  DEF_ROMLOC(7770) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(7772) : move_toreg_8(read_8(0xFFFFFE11), &D0);
  switchindex = D0;                         // MOVE.B	$FE11,D0
  DEF_ROMLOC(7776) : add_toreg_16(D0, &D0); // ADD.W	D0,D0
  DEF_ROMLOC(7778)
      : move_toreg_16(read_16(0x7780 + (s16)(D0 & 0xffff)),
                      &D0); // MOVE.W	6(PC,D0),D0
  // DEF_ROMLOC(777C): goto rom_7780 + (s16)(D0 & 0xffff); // JMP	2(PC,D0)
  DEF_ROMLOC(777C) : switch (switchindex) {
  case 0:
    rom_7786();
    break;
  case 1:
    rom_7786();
    break;
  case 2:
    rom_7788();
    break;
  }
}
ROMFUNC(rom_7786) {
  DEF_ROMLOC(7786) : return; // RTS
}
ROMFUNC(rom_7788) {
  u8 switchindex = 0;
  DEF_ROMLOC(7788) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(778A) : move_toreg_8(read_8(0xFFFFF742), &D0);
  switchindex = D0 / 2; // MOVE.B	$F742,D0
  DEF_ROMLOC(778E)
      : move_toreg_16(read_16(0x7796 + (s16)(D0 & 0xffff)),
                      &D0); // MOVE.W	6(PC,D0),D0
  // DEF_ROMLOC(7792): goto rom_7796 + (s16)(D0 & 0xffff); // JMP	2(PC,D0)
  DEF_ROMLOC(7792) : switch (switchindex) {
  case 0:
    rom_779C();
    break;
  case 1:
    rom_77B0();
    break;
  case 2:
    rom_77DC();
    break;
  }
}
ROMFUNC(rom_7796) {
  DEF_ROMLOC(7796) : or_toreg_8(0x1A, &D6);   // ORI.B	#$1A,D6
  DEF_ROMLOC(779A) : or_toreg_16(0xC78, &D6); // ORI.W	#$0C78,D6
  rom_779C(); // Detected flow into next function
}
ROMFUNC(rom_779C) {
  DEF_ROMLOC(779C) : cmp_tomem_16(0x1E70, 0xFFFFF700); // CMPI.W
                                                       // #$1E70,$F700
  DEF_ROMLOC(77A2) : if (CCR_CS) goto rom_77AE;        // BCS.B	$77AE
  DEF_ROMLOC(77A4) : move_tomem_16(0x210, 0xFFFFF726); // MOVE.W
                                                       // #$0210,$F726
  DEF_ROMLOC(77AA) : add_tomem_8(0x2, 0xFFFFF742);     // ADDQ.B	#$02,$F742
  DEF_ROMLOC(77AE) : return;                           // RTS
}
ROMFUNC(rom_77B0) {
  DEF_ROMLOC(77B0) : cmp_tomem_16(0x2000, 0xFFFFF700); // CMPI.W
                                                       // #$2000,$F700
  DEF_ROMLOC(77B6) : if (CCR_CS) goto rom_77DA;        // BCS.B	$77DA
  DEF_ROMLOC(77B8) : rom_E11A();                       // BSR.W	$E11A
  DEF_ROMLOC(77BC) : if (!CCR_EQ) goto rom_77C2;       // BNE.B	$77C2
  DEF_ROMLOC(77BE) : move_tomem_8(0x7A, A1);           // MOVE.B	#$7A,(A1)
  DEF_ROMLOC(77C2) : move_toreg_16(0x8C, &D0);         // MOVE.W	#$008C,D0
  DEF_ROMLOC(77C6) : rom_138E();                       // BSR.W	$138E
  DEF_ROMLOC(77CA) : move_tomem_8(0x1, 0xFFFFF7AA);    // MOVE.B	#$01,$F7AA
  DEF_ROMLOC(77D0) : add_tomem_8(0x2, 0xFFFFF742);     // ADDQ.B	#$02,$F742
  DEF_ROMLOC(77D4) : move_toreg_32(0x11, &D0);         // MOVEQ.L	$11,D0
  rom_1578();
  return;                    // BRA.W	$1578
  DEF_ROMLOC(77DA) : return; // RTS
}
ROMFUNC(rom_77DC) {
  DEF_ROMLOC(77DC)
      : move_tomem_16(read_16(0xFFFFF700),
                      0xFFFFF728); // MOVE.W	$F700,$F728
  DEF_ROMLOC(77E2) : return;       // RTS
  DEF_ROMLOC(77E4) : return;       // RTS
}
ROMFUNC(rom_77E6) {
  u8 switchindex = 0;
  DEF_ROMLOC(77E6) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(77E8) : move_toreg_8(read_8(0xFFFFFE11), &D0);
  switchindex = D0;                         // MOVE.B	$FE11,D0
  DEF_ROMLOC(77EC) : add_toreg_16(D0, &D0); // ADD.W	D0,D0
  DEF_ROMLOC(77EE)
      : move_toreg_16(read_16(0x77F6 + (s16)(D0 & 0xffff)),
                      &D0); // MOVE.W	6(PC,D0),D0
  // DEF_ROMLOC(77F2): goto rom_77F6 + (s16)(D0 & 0xffff); // JMP	2(PC,D0)
  DEF_ROMLOC(77F2) : switch (switchindex) {
  case 0:
    rom_77FC();
    break;
  case 1:
    rom_77FE();
    break;
  case 2:
    rom_7822();
    break;
  }
}
ROMFUNC(rom_77F6) {
  DEF_ROMLOC(77F6) : or_toreg_8(0x8, &D6); // ORI.B	#$08,D6
  DEF_ROMLOC(77FA)
      : or_tomem_8(0x75, A4 + 0x31FC);       // ORI.B	#$75,12796(A4)
  DEF_ROMLOC(7800) : btst_tomem_8(D2, --A0); // BTST.B	D2,-(A0)
  rom_77FC();                                // Detected flow into next function
}
ROMFUNC(rom_77FC) {
  DEF_ROMLOC(77FC) : return; // RTS
}
ROMFUNC(rom_77FE) {
  DEF_ROMLOC(77FE) : move_tomem_16(0x520, 0xFFFFF726); // MOVE.W
                                                       // #$0520,$F726
  DEF_ROMLOC(7804) : cmp_tomem_16(0x25A0, 0xFFFFF700); // CMPI.W
                                                       // #$25A0,$F700
  DEF_ROMLOC(780A) : if (CCR_CS) goto rom_7820;        // BCS.B	$7820
  DEF_ROMLOC(780C) : move_tomem_16(0x420, 0xFFFFF726); // MOVE.W
                                                       // #$0420,$F726
  DEF_ROMLOC(7812) : cmp_tomem_16(0x4D0, 0xFFFFD00C);  // CMPI.W	#$04D0,$D00C
  DEF_ROMLOC(7818) : if (CCR_CS) goto rom_7820;        // BCS.B	$7820
  DEF_ROMLOC(781A) : move_tomem_16(0x520, 0xFFFFF726); // MOVE.W
                                                       // #$0520,$F726
  DEF_ROMLOC(7820) : return;                           // RTS
}
ROMFUNC(rom_7822) {
  u8 switchindex = 0;
  DEF_ROMLOC(7822) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(7824) : move_toreg_8(read_8(0xFFFFF742), &D0);
  switchindex = D0;
  switchindex = D0 / 2; // MOVE.B	$F742,D0
  DEF_ROMLOC(7828)
      : move_toreg_16(read_16(0x7830 + (s16)(D0 & 0xffff)),
                      &D0); // MOVE.W	6(PC,D0),D0
  // DEF_ROMLOC(782C): goto rom_7830 + (s16)(D0 & 0xffff); // JMP	2(PC,D0)
  DEF_ROMLOC(782C) : switch (switchindex) {
  case 0:
    rom_7836();
    break;
  case 1:
    rom_784E();
    break;
  case 2:
    rom_7880();
    break;
  }
}
ROMFUNC(rom_7830) {
  DEF_ROMLOC(7830) : or_toreg_8(0x1E, &D6);  // ORI.B	#$1E,D6
  DEF_ROMLOC(7834) : or_tomem_16(0xC78, A0); // ORI.W	#$0C78,(A0)
  DEF_ROMLOC(7838)
      : move_tomem_32(D0, (A5 += 4, A5 - 4)); // MOVE.L	D0,(A5)+
  rom_7836(); // Detected flow into next function
}
ROMFUNC(rom_7836) {
  DEF_ROMLOC(7836) : cmp_tomem_16(0x2AC0, 0xFFFFF700); // CMPI.W
                                                       // #$2AC0,$F700
  DEF_ROMLOC(783C) : if (CCR_CS) goto rom_784C;        // BCS.B	$784C
  DEF_ROMLOC(783E) : rom_E11A();                       // BSR.W	$E11A
  DEF_ROMLOC(7842) : if (!CCR_EQ) goto rom_784C;       // BNE.B	$784C
  DEF_ROMLOC(7844) : move_tomem_8(0x76, A1);           // MOVE.B	#$76,(A1)
  DEF_ROMLOC(7848) : add_tomem_8(0x2, 0xFFFFF742);     // ADDQ.B	#$02,$F742
  DEF_ROMLOC(784C) : return;                           // RTS
}
ROMFUNC(rom_784E) {
  DEF_ROMLOC(784E) : cmp_tomem_16(0x2C00, 0xFFFFF700); // CMPI.W
                                                       // #$2C00,$F700
  DEF_ROMLOC(7854) : if (CCR_CS) goto rom_787E;        // BCS.B	$787E
  DEF_ROMLOC(7856) : move_tomem_16(0x4CC, 0xFFFFF726); // MOVE.W
                                                       // #$04CC,$F726
  DEF_ROMLOC(785C) : rom_E11A();                       // BSR.W	$E11A
  DEF_ROMLOC(7860) : if (!CCR_EQ) goto rom_786A;       // BNE.B	$786A
  DEF_ROMLOC(7862) : move_tomem_8(0x75, A1);           // MOVE.B	#$75,(A1)
  DEF_ROMLOC(7866) : add_tomem_8(0x2, 0xFFFFF742);     // ADDQ.B	#$02,$F742
  DEF_ROMLOC(786A) : move_toreg_16(0x8C, &D0);         // MOVE.W	#$008C,D0
  DEF_ROMLOC(786E) : rom_138E();                       // BSR.W	$138E
  DEF_ROMLOC(7872) : move_tomem_8(0x1, 0xFFFFF7AA);    // MOVE.B	#$01,$F7AA
  DEF_ROMLOC(7878) : move_toreg_32(0x11, &D0);         // MOVEQ.L	$11,D0
  rom_1578();
  return;                    // BRA.W	$1578
  DEF_ROMLOC(787E) : return; // RTS
}
ROMFUNC(rom_7880) {
  DEF_ROMLOC(7880)
      : move_tomem_16(read_16(0xFFFFF700),
                      0xFFFFF728); // MOVE.W	$F700,$F728
  DEF_ROMLOC(7886) : return;       // RTS
}
ROMFUNC(rom_7888) {
  u8 switchindex = 0;
  DEF_ROMLOC(7888) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(788A) : move_toreg_8(read_8(0xFFFFFE11), &D0);
  switchindex = D0;                         // MOVE.B	$FE11,D0
  DEF_ROMLOC(788E) : add_toreg_16(D0, &D0); // ADD.W	D0,D0
  DEF_ROMLOC(7890)
      : move_toreg_16(read_16(0x7898 + (s16)(D0 & 0xffff)),
                      &D0); // MOVE.W	6(PC,D0),D0
  // DEF_ROMLOC(7894): goto rom_7898 + (s16)(D0 & 0xffff); // JMP	2(PC,D0)
  DEF_ROMLOC(7894) : switch (switchindex) {
  case 0:
    rom_789E();
    break;
  case 1:
    rom_78C2();
    break;
  case 2:
    rom_7948();
    break;
  }
}
ROMFUNC(rom_789E) {
  DEF_ROMLOC(789E) : move_tomem_16(0x720, 0xFFFFF726); // MOVE.W
                                                       // #$0720,$F726
  DEF_ROMLOC(78A4) : cmp_tomem_16(0x1880, 0xFFFFF700); // CMPI.W
                                                       // #$1880,$F700
  DEF_ROMLOC(78AA) : if (CCR_CS) goto rom_78C0;        // BCS.B	$78C0
  DEF_ROMLOC(78AC) : move_tomem_16(0x620, 0xFFFFF726); // MOVE.W
                                                       // #$0620,$F726
  DEF_ROMLOC(78B2) : cmp_tomem_16(0x2000, 0xFFFFF700); // CMPI.W
                                                       // #$2000,$F700
  DEF_ROMLOC(78B8) : if (CCR_CS) goto rom_78C0;        // BCS.B	$78C0
  DEF_ROMLOC(78BA) : move_tomem_16(0x2A0, 0xFFFFF726); // MOVE.W
                                                       // #$02A0,$F726
  DEF_ROMLOC(78C0) : return;                           // RTS
}
ROMFUNC(rom_78C2) {
  u8 switchindex = 0;
  DEF_ROMLOC(78C2) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(78C4) : move_toreg_8(read_8(0xFFFFF742), &D0);
  switchindex = D0 / 2; // MOVE.B	$F742,D0
  DEF_ROMLOC(78C8)
      : move_toreg_16(read_16(0x78D0 + (s16)(D0 & 0xffff)),
                      &D0); // MOVE.W	6(PC,D0),D0
  // DEF_ROMLOC(78CC): goto rom_78D0 + (s16)(D0 & 0xffff); // JMP	2(PC,D0)
  DEF_ROMLOC(78CC) : switch (switchindex) {
  case 0:
    rom_78D8();
    break;
  case 1:
    rom_78FA();
    break;
  case 2:
    rom_7918();
    break;
  case 3:
    rom_7936();
    break;
  }
}
ROMFUNC(rom_78D8) {
  DEF_ROMLOC(78D8) : move_tomem_16(0x800, 0xFFFFF726); // MOVE.W
                                                       // #$0800,$F726
  DEF_ROMLOC(78DE) : cmp_tomem_16(0x1800, 0xFFFFF700); // CMPI.W
                                                       // #$1800,$F700
  DEF_ROMLOC(78E4) : if (CCR_CS) goto rom_78F8;        // BCS.B	$78F8
  DEF_ROMLOC(78E6) : move_tomem_16(0x510, 0xFFFFF726); // MOVE.W
                                                       // #$0510,$F726
  DEF_ROMLOC(78EC) : cmp_tomem_16(0x1E00, 0xFFFFF700); // CMPI.W
                                                       // #$1E00,$F700
  DEF_ROMLOC(78F2) : if (CCR_CS) goto rom_78F8;        // BCS.B	$78F8
  DEF_ROMLOC(78F4) : add_tomem_8(0x2, 0xFFFFF742);     // ADDQ.B	#$02,$F742
  DEF_ROMLOC(78F8) : return;                           // RTS
}
ROMFUNC(rom_78FA) {
  DEF_ROMLOC(78FA) : cmp_tomem_16(0x1EB0, 0xFFFFF700); // CMPI.W
                                                       // #$1EB0,$F700
  DEF_ROMLOC(7900) : if (CCR_CS) goto rom_7916;        // BCS.B	$7916
  DEF_ROMLOC(7902) : rom_E11A();                       // BSR.W	$E11A
  DEF_ROMLOC(7906) : if (!CCR_EQ) goto rom_7916;       // BNE.B	$7916
  DEF_ROMLOC(7908) : move_tomem_8(0xFFFFFF83, A1);     // MOVE.B	#$83,(A1)
  DEF_ROMLOC(790C) : add_tomem_8(0x2, 0xFFFFF742);     // ADDQ.B	#$02,$F742
  DEF_ROMLOC(7910) : move_toreg_32(0x1E, &D0);         // MOVEQ.L	$1E,D0
  rom_1578();
  return;                    // BRA.W	$1578
  DEF_ROMLOC(7916) : return; // RTS
}
ROMFUNC(rom_7918) {
  DEF_ROMLOC(7918) : cmp_tomem_16(0x1F60, 0xFFFFF700); // CMPI.W
                                                       // #$1F60,$F700
  DEF_ROMLOC(791E) : if (CCR_CS) goto rom_7934;        // BCS.B	$7934
  DEF_ROMLOC(7920) : rom_E11A();                       // BSR.W	$E11A
  DEF_ROMLOC(7924) : if (!CCR_EQ) goto rom_792E;       // BNE.B	$792E
  DEF_ROMLOC(7926) : move_tomem_8(0xFFFFFF82, A1);     // MOVE.B	#$82,(A1)
  DEF_ROMLOC(792A) : add_tomem_8(0x2, 0xFFFFF742);     // ADDQ.B	#$02,$F742
  DEF_ROMLOC(792E) : move_tomem_8(0x1, 0xFFFFF7AA);    // MOVE.B	#$01,$F7AA
  DEF_ROMLOC(7934) : rom_7940();                       // BRA.B	$7940
}
ROMFUNC(rom_7936) {
  DEF_ROMLOC(7936) : cmp_tomem_16(0x2050, 0xFFFFF700); // CMPI.W
                                                       // #$2050,$F700
  DEF_ROMLOC(793C) : if (CCR_CS) {
    rom_7940();
    return;
  }                          // BCS.B	$7940
  DEF_ROMLOC(793E) : return; // RTS
}
ROMFUNC(rom_7940) {
  DEF_ROMLOC(7940)
      : move_tomem_16(read_16(0xFFFFF700),
                      0xFFFFF728); // MOVE.W	$F700,$F728
  DEF_ROMLOC(7946) : return;       // RTS
}
ROMFUNC(rom_7948) {
  u8 switchindex = 0;
  DEF_ROMLOC(7948) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(794A) : move_toreg_8(read_8(0xFFFFF742), &D0);
  switchindex = D0 / 2; // MOVE.B	$F742,D0
  DEF_ROMLOC(794E)
      : move_toreg_16(read_16(0x7956 + (s16)(D0 & 0xffff)),
                      &D0); // MOVE.W	6(PC,D0),D0
  // DEF_ROMLOC(7952): goto rom_7956 + (s16)(D0 & 0xffff); // JMP	2(PC,D0)
  DEF_ROMLOC(7952) : switch (switchindex) {
  case 0:
    rom_7960();
    break;
  case 1:
    rom_7974();
    break;
  case 2:
    rom_7992();
    break;
  case 3:
    rom_79A0();
    break;
  case 4:
    rom_79A2();
    break;
  }
}
ROMFUNC(rom_7960) {
  DEF_ROMLOC(7960) : cmp_tomem_16(0x2148, 0xFFFFF700); // CMPI.W
                                                       // #$2148,$F700
  DEF_ROMLOC(7966) : if (CCR_CS) goto rom_7972;        // BCS.B	$7972
  DEF_ROMLOC(7968) : add_tomem_8(0x2, 0xFFFFF742);     // ADDQ.B	#$02,$F742
  DEF_ROMLOC(796C) : move_toreg_32(0x1F, &D0);         // MOVEQ.L	$1F,D0
  DEF_ROMLOC(796E) : rom_1578();                       // BSR.W	$1578
  DEF_ROMLOC(7972) : rom_7940();                       // BRA.B	$7940
}
ROMFUNC(rom_7974) {
  DEF_ROMLOC(7974) : cmp_tomem_16(0x2300, 0xFFFFF700); // CMPI.W
                                                       // #$2300,$F700
  DEF_ROMLOC(797A) : if (CCR_CS) goto rom_7990;        // BCS.B	$7990
  DEF_ROMLOC(797C) : rom_E11A();                       // BSR.W	$E11A
  DEF_ROMLOC(7980) : if (!CCR_EQ) goto rom_7990;       // BNE.B	$7990
  DEF_ROMLOC(7982) : move_tomem_8(0xFFFFFF85, A1);     // MOVE.B	#$85,(A1)
  DEF_ROMLOC(7986) : add_tomem_8(0x2, 0xFFFFF742);     // ADDQ.B	#$02,$F742
  DEF_ROMLOC(798A) : move_tomem_8(0x1, 0xFFFFF7AA);    // MOVE.B	#$01,$F7AA
  DEF_ROMLOC(7990) : rom_7940();                       // BRA.B	$7940
}
ROMFUNC(rom_7992) {
  DEF_ROMLOC(7992) : cmp_tomem_16(0x2450, 0xFFFFF700); // CMPI.W
                                                       // #$2450,$F700
  DEF_ROMLOC(7998) : if (CCR_CS) goto rom_799E;        // BCS.B	$799E
  DEF_ROMLOC(799A) : add_tomem_8(0x2, 0xFFFFF742);     // ADDQ.B	#$02,$F742
  DEF_ROMLOC(799E) : rom_7940();                       // BRA.B	$7940
}
ROMFUNC(rom_79A0) {
  DEF_ROMLOC(79A0) : return; // RTS
}
ROMFUNC(rom_79A2) {
  rom_7940(); // BRA.B	$7940
}
ROMFUNC(rom_79A4) {
  DEF_ROMLOC(79A4) : return; // RTS
}