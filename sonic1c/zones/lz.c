// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"


ROMFUNC(rom_3BCC) {
  DEF_ROMLOC(3BCC) : cmp_tomem_8(0x1, 0xFFFFFE10); // CMPI.B	#$01,$FE10
  DEF_ROMLOC(3BD2) : if (!CCR_EQ) goto rom_3C2A;   // BNE.B	$3C2A
  DEF_ROMLOC(3BD4) : tst_mem_8(0xFFFFF744);        // TST.B	$F744
  DEF_ROMLOC(3BD8) : if (!CCR_EQ) goto rom_3BEE;   // BNE.B	$3BEE
  DEF_ROMLOC(3BDA) : cmp_tomem_8(0x6, 0xFFFFD024); // CMPI.B	#$06,$D024
  DEF_ROMLOC(3BE0) : if (CCR_CC) goto rom_3BEE;    // BCC.B	$3BEE
  DEF_ROMLOC(3BE2) : rom_3E34();                   // BSR.W	$3E34
  DEF_ROMLOC(3BE6) : rom_3F36();                   // BSR.W	$3F36
  DEF_ROMLOC(3BEA) : rom_3C34();                   // BSR.W	$3C34
  DEF_ROMLOC(3BEE) : clr_mem_8(0xFFFFF64E);        // CLR.B	$F64E
  DEF_ROMLOC(3BF2) : move_toreg_32(0x0, &D0);      // MOVEQ.L	$00,D0
  DEF_ROMLOC(3BF4)
      : move_toreg_8(read_8(0xFFFFFE60), &D0); // MOVE.B	$FE60,D0
  DEF_ROMLOC(3BF8) : lsr_toreg_16(0x1, &D0);   // LSR.W	#$01,D0
  DEF_ROMLOC(3BFA)
      : add_toreg_16(read_16(0xFFFFF648), &D0);     // ADD.W	$F648,D0
  DEF_ROMLOC(3BFE) : move_tomem_16(D0, 0xFFFFF646); // MOVE.W	D0,$F646
  DEF_ROMLOC(3C02)
      : move_toreg_16(read_16(0xFFFFF646), &D0); // MOVE.W	$F646,D0
  DEF_ROMLOC(3C06)
      : sub_toreg_16(read_16(0xFFFFF704), &D0); // SUB.W	$F704,D0
  DEF_ROMLOC(3C0A) : if (CCR_CC) goto rom_3C1C; // BCC.B	$3C1C
  DEF_ROMLOC(3C0C) : tst_reg_16(&D0);           // TST.W	D0
  DEF_ROMLOC(3C0E) : if (CCR_PL) goto rom_3C1C; // BPL.B	$3C1C
  DEF_ROMLOC(3C10)
      : move_tomem_8(0xFFFFFFDF, 0xFFFFF625);       // MOVE.B	#$DF,$F625
  DEF_ROMLOC(3C16) : move_tomem_8(0x1, 0xFFFFF64E); // MOVE.B	#$01,$F64E
  DEF_ROMLOC(3C1C) : cmp_toreg_16(0xDF, &D0);       // CMPI.W	#$00DF,D0
  DEF_ROMLOC(3C20) : if (CCR_CS) goto rom_3C26;     // BCS.B	$3C26
  DEF_ROMLOC(3C22) : move_toreg_16(0xDF, &D0);      // MOVE.W	#$00DF,D0
  DEF_ROMLOC(3C26) : move_tomem_8(D0, 0xFFFFF625);  // MOVE.B	D0,$F625
  DEF_ROMLOC(3C2A) : return;                        // RTS
}
ROMFUNC(rom_3C34) {
  u8 switchindex = 0;
  DEF_ROMLOC(3C34) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(3C36) : move_toreg_8(read_8(0xFFFFFE11), &D0);
  switchindex = D0;                         // MOVE.B	$FE11,D0
  DEF_ROMLOC(3C3A) : add_toreg_16(D0, &D0); // ADD.W	D0,D0
  DEF_ROMLOC(3C3C)
      : move_toreg_16(read_16(0x3C5E + (s16)(D0 & 0xffff)),
                      &D0); // MOVE.W	32(PC,D0),D0
  // DEF_ROMLOC(3C40): rom_3C5E + (s16)(D0 & 0xffff)(); // JSR	28(PC,D0)
  DEF_ROMLOC(3C40) : switch (switchindex) {
  case 0:
    rom_3C66();
    break;
  case 1:
    rom_3CF8();
    break;
  case 2:
    rom_3D1A();
    break;
  case 3:
    rom_3E1E();
    break;
  }
  DEF_ROMLOC(3C44) : move_toreg_32(0x0, &D1); // MOVEQ.L	$00,D1
  DEF_ROMLOC(3C46)
      : move_toreg_8(read_8(0xFFFFF64C), &D1); // MOVE.B	$F64C,D1
  DEF_ROMLOC(3C4A)
      : move_toreg_16(read_16(0xFFFFF64A), &D0); // MOVE.W	$F64A,D0
  DEF_ROMLOC(3C4E)
      : sub_toreg_16(read_16(0xFFFFF648), &D0);    // SUB.W	$F648,D0
  DEF_ROMLOC(3C52) : if (CCR_EQ) goto rom_3C5C;    // BEQ.B	$3C5C
  DEF_ROMLOC(3C54) : if (CCR_CC) goto rom_3C58;    // BCC.B	$3C58
  DEF_ROMLOC(3C56) : neg_reg_16(&D1);              // NEG.W	D1
  DEF_ROMLOC(3C58) : add_tomem_16(D1, 0xFFFFF648); // ADD.W	D1,$F648
  DEF_ROMLOC(3C5C) : return;                       // RTS
}
ROMFUNC(rom_3C66) {
  DEF_ROMLOC(3C66)
      : move_toreg_16(read_16(0xFFFFF700), &D0); // MOVE.W	$F700,D0
  DEF_ROMLOC(3C6A)
      : move_toreg_8(read_8(0xFFFFF64D), &D2);        // MOVE.B	$F64D,D2
  DEF_ROMLOC(3C6E) : if (!CCR_EQ) goto rom_3CD2;      // BNE.B	$3CD2
  DEF_ROMLOC(3C70) : move_toreg_16(0xB8, &D1);        // MOVE.W	#$00B8,D1
  DEF_ROMLOC(3C74) : cmp_toreg_16(0x600, &D0);        // CMPI.W	#$0600,D0
  DEF_ROMLOC(3C78) : if (CCR_CS) goto rom_3CB6;       // BCS.B	$3CB6
  DEF_ROMLOC(3C7A) : move_toreg_16(0x108, &D1);       // MOVE.W	#$0108,D1
  DEF_ROMLOC(3C7E) : cmp_tomem_16(0x200, 0xFFFFD00C); // CMPI.W	#$0200,$D00C
  DEF_ROMLOC(3C84) : if (CCR_CS) goto rom_3CBC;       // BCS.B	$3CBC
  DEF_ROMLOC(3C86) : cmp_toreg_16(0xC00, &D0);        // CMPI.W	#$0C00,D0
  DEF_ROMLOC(3C8A) : if (CCR_CS) goto rom_3CB6;       // BCS.B	$3CB6
  DEF_ROMLOC(3C8C) : move_toreg_16(0x318, &D1);       // MOVE.W	#$0318,D1
  DEF_ROMLOC(3C90) : cmp_toreg_16(0x1080, &D0);       // CMPI.W	#$1080,D0
  DEF_ROMLOC(3C94) : if (CCR_CS) goto rom_3CB6;       // BCS.B	$3CB6
  DEF_ROMLOC(3C96)
      : move_tomem_8(0xFFFFFF80, 0xFFFFF7E5);   // MOVE.B	#$80,$F7E5
  DEF_ROMLOC(3C9C) : move_toreg_16(0x5C8, &D1); // MOVE.W	#$05C8,D1
  DEF_ROMLOC(3CA0) : cmp_toreg_16(0x1380, &D0); // CMPI.W	#$1380,D0
  DEF_ROMLOC(3CA4) : if (CCR_CS) goto rom_3CB6; // BCS.B	$3CB6
  DEF_ROMLOC(3CA6) : move_toreg_16(0x3A8, &D1); // MOVE.W	#$03A8,D1
  DEF_ROMLOC(3CAA)
      : cmp_toreg_16(read_16(0xFFFFF648), &D1);       // CMP.W	$F648,D1
  DEF_ROMLOC(3CAE) : if (!CCR_EQ) goto rom_3CB6;      // BNE.B	$3CB6
  DEF_ROMLOC(3CB0) : move_tomem_8(0x1, 0xFFFFF64D);   // MOVE.B	#$01,$F64D
  DEF_ROMLOC(3CB6) : move_tomem_16(D1, 0xFFFFF64A);   // MOVE.W	D1,$F64A
  DEF_ROMLOC(3CBA) : return;                          // RTS
  DEF_ROMLOC(3CBC) : cmp_toreg_16(0xC80, &D0);        // CMPI.W	#$0C80,D0
  DEF_ROMLOC(3CC0) : if (CCR_CS) goto rom_3CB6;       // BCS.B	$3CB6
  DEF_ROMLOC(3CC2) : move_toreg_16(0xE8, &D1);        // MOVE.W	#$00E8,D1
  DEF_ROMLOC(3CC6) : cmp_toreg_16(0x1500, &D0);       // CMPI.W	#$1500,D0
  DEF_ROMLOC(3CCA) : if (CCR_CS) goto rom_3CB6;       // BCS.B	$3CB6
  DEF_ROMLOC(3CCC) : move_toreg_16(0x108, &D1);       // MOVE.W	#$0108,D1
  DEF_ROMLOC(3CD0) : goto rom_3CB6;                   // BRA.B	$3CB6
  DEF_ROMLOC(3CD2) : sub_toreg_8(0x1, &D2);           // SUBQ.B	#$01,D2
  DEF_ROMLOC(3CD4) : if (!CCR_EQ) goto rom_3CF6;      // BNE.B	$3CF6
  DEF_ROMLOC(3CD6) : cmp_tomem_16(0x2E0, 0xFFFFD00C); // CMPI.W	#$02E0,$D00C
  DEF_ROMLOC(3CDC) : if (CCR_CC) goto rom_3CF6;       // BCC.B	$3CF6
  DEF_ROMLOC(3CDE) : move_toreg_16(0x3A8, &D1);       // MOVE.W	#$03A8,D1
  DEF_ROMLOC(3CE2) : cmp_toreg_16(0x1300, &D0);       // CMPI.W	#$1300,D0
  DEF_ROMLOC(3CE6) : if (CCR_CS) goto rom_3CF2;       // BCS.B	$3CF2
  DEF_ROMLOC(3CE8) : move_toreg_16(0x108, &D1);       // MOVE.W	#$0108,D1
  DEF_ROMLOC(3CEC) : move_tomem_8(0x2, 0xFFFFF64D);   // MOVE.B	#$02,$F64D
  DEF_ROMLOC(3CF2) : move_tomem_16(D1, 0xFFFFF64A);   // MOVE.W	D1,$F64A
  DEF_ROMLOC(3CF6) : return;                          // RTS
}
ROMFUNC(rom_3CF8) {
  DEF_ROMLOC(3CF8)
      : move_toreg_16(read_16(0xFFFFF700), &D0);    // MOVE.W	$F700,D0
  DEF_ROMLOC(3CFC) : move_toreg_16(0x328, &D1);     // MOVE.W	#$0328,D1
  DEF_ROMLOC(3D00) : cmp_toreg_16(0x500, &D0);      // CMPI.W	#$0500,D0
  DEF_ROMLOC(3D04) : if (CCR_CS) goto rom_3D14;     // BCS.B	$3D14
  DEF_ROMLOC(3D06) : move_toreg_16(0x3C8, &D1);     // MOVE.W	#$03C8,D1
  DEF_ROMLOC(3D0A) : cmp_toreg_16(0xB00, &D0);      // CMPI.W	#$0B00,D0
  DEF_ROMLOC(3D0E) : if (CCR_CS) goto rom_3D14;     // BCS.B	$3D14
  DEF_ROMLOC(3D10) : move_toreg_16(0x428, &D1);     // MOVE.W	#$0428,D1
  DEF_ROMLOC(3D14) : move_tomem_16(D1, 0xFFFFF64A); // MOVE.W	D1,$F64A
  DEF_ROMLOC(3D18) : return;                        // RTS
}
ROMFUNC(rom_3D1A) {
  DEF_ROMLOC(3D1A)
      : move_toreg_16(read_16(0xFFFFF700), &D0); // MOVE.W	$F700,D0
  DEF_ROMLOC(3D1E)
      : move_toreg_8(read_8(0xFFFFF64D), &D2);        // MOVE.B	$F64D,D2
  DEF_ROMLOC(3D22) : if (!CCR_EQ) goto rom_3D60;      // BNE.B	$3D60
  DEF_ROMLOC(3D24) : move_toreg_16(0x900, &D1);       // MOVE.W	#$0900,D1
  DEF_ROMLOC(3D28) : cmp_toreg_16(0x600, &D0);        // CMPI.W	#$0600,D0
  DEF_ROMLOC(3D2C) : if (CCR_CS) goto rom_3D56;       // BCS.B	$3D56
  DEF_ROMLOC(3D2E) : cmp_tomem_16(0x3C0, 0xFFFFD00C); // CMPI.W	#$03C0,$D00C
  DEF_ROMLOC(3D34) : if (CCR_CS) goto rom_3D56;       // BCS.B	$3D56
  DEF_ROMLOC(3D36) : cmp_tomem_16(0x600, 0xFFFFD00C); // CMPI.W	#$0600,$D00C
  DEF_ROMLOC(3D3C) : if (CCR_CC) goto rom_3D56;       // BCC.B	$3D56
  DEF_ROMLOC(3D3E) : move_toreg_16(0x4C8, &D1);       // MOVE.W	#$04C8,D1
  DEF_ROMLOC(3D42) : move_tomem_8(0x4B, 0xFFFFA506);  // MOVE.B	#$4B,$A506
  DEF_ROMLOC(3D48) : move_tomem_8(0x1, 0xFFFFF64D);   // MOVE.B	#$01,$F64D
  DEF_ROMLOC(3D4E) : move_toreg_16(0xB7, &D0);        // MOVE.W	#$00B7,D0
  DEF_ROMLOC(3D52) : rom_1394();                      // BSR.W	$1394
  DEF_ROMLOC(3D56) : move_tomem_16(D1, 0xFFFFF64A);   // MOVE.W	D1,$F64A
  DEF_ROMLOC(3D5A) : move_tomem_16(D1, 0xFFFFF648);   // MOVE.W	D1,$F648
  DEF_ROMLOC(3D5E) : return;                          // RTS
  DEF_ROMLOC(3D60) : sub_toreg_8(0x1, &D2);           // SUBQ.B	#$01,D2
  DEF_ROMLOC(3D62) : if (!CCR_EQ) goto rom_3DAA;      // BNE.B	$3DAA
  DEF_ROMLOC(3D64) : move_toreg_16(0x4C8, &D1);       // MOVE.W	#$04C8,D1
  DEF_ROMLOC(3D68) : cmp_toreg_16(0x770, &D0);        // CMPI.W	#$0770,D0
  DEF_ROMLOC(3D6C) : if (CCR_CS) goto rom_3DA4;       // BCS.B	$3DA4
  DEF_ROMLOC(3D6E) : move_toreg_16(0x308, &D1);       // MOVE.W	#$0308,D1
  DEF_ROMLOC(3D72) : cmp_toreg_16(0x1400, &D0);       // CMPI.W	#$1400,D0
  DEF_ROMLOC(3D76) : if (CCR_CS) goto rom_3DA4;       // BCS.B	$3DA4
  DEF_ROMLOC(3D78) : cmp_tomem_16(0x508, 0xFFFFF64A); // CMPI.W	#$0508,$F64A
  DEF_ROMLOC(3D7E) : if (CCR_EQ) goto rom_3D90;       // BEQ.B	$3D90
  DEF_ROMLOC(3D80) : cmp_tomem_16(0x600, 0xFFFFD00C); // CMPI.W	#$0600,$D00C
  DEF_ROMLOC(3D86) : if (CCR_CC) goto rom_3D90;       // BCC.B	$3D90
  DEF_ROMLOC(3D88) : cmp_tomem_16(0x280, 0xFFFFD00C); // CMPI.W	#$0280,$D00C
  DEF_ROMLOC(3D8E) : if (CCR_CC) goto rom_3DA4;       // BCC.B	$3DA4
  DEF_ROMLOC(3D90) : move_toreg_16(0x508, &D1);       // MOVE.W	#$0508,D1
  DEF_ROMLOC(3D94) : move_tomem_16(D1, 0xFFFFF648);   // MOVE.W	D1,$F648
  DEF_ROMLOC(3D98) : cmp_toreg_16(0x1770, &D0);       // CMPI.W	#$1770,D0
  DEF_ROMLOC(3D9C) : if (CCR_CS) goto rom_3DA4;       // BCS.B	$3DA4
  DEF_ROMLOC(3D9E) : move_tomem_8(0x2, 0xFFFFF64D);   // MOVE.B	#$02,$F64D
  DEF_ROMLOC(3DA4) : move_tomem_16(D1, 0xFFFFF64A);   // MOVE.W	D1,$F64A
  DEF_ROMLOC(3DA8) : return;                          // RTS
  DEF_ROMLOC(3DAA) : sub_toreg_8(0x1, &D2);           // SUBQ.B	#$01,D2
  DEF_ROMLOC(3DAC) : if (!CCR_EQ) goto rom_3DD4;      // BNE.B	$3DD4
  DEF_ROMLOC(3DAE) : move_toreg_16(0x508, &D1);       // MOVE.W	#$0508,D1
  DEF_ROMLOC(3DB2) : cmp_toreg_16(0x1860, &D0);       // CMPI.W	#$1860,D0
  DEF_ROMLOC(3DB6) : if (CCR_CS) goto rom_3DCE;       // BCS.B	$3DCE
  DEF_ROMLOC(3DB8) : move_toreg_16(0x188, &D1);       // MOVE.W	#$0188,D1
  DEF_ROMLOC(3DBC) : cmp_toreg_16(0x1AF0, &D0);       // CMPI.W	#$1AF0,D0
  DEF_ROMLOC(3DC0) : if (CCR_CC) goto rom_3DC8;       // BCC.B	$3DC8
  DEF_ROMLOC(3DC2)
      : cmp_toreg_16(read_16(0xFFFFF648), &D1);        // CMP.W	$F648,D1
  DEF_ROMLOC(3DC6) : if (!CCR_EQ) goto rom_3DCE;       // BNE.B	$3DCE
  DEF_ROMLOC(3DC8) : move_tomem_8(0x3, 0xFFFFF64D);    // MOVE.B	#$03,$F64D
  DEF_ROMLOC(3DCE) : move_tomem_16(D1, 0xFFFFF64A);    // MOVE.W	D1,$F64A
  DEF_ROMLOC(3DD2) : return;                           // RTS
  DEF_ROMLOC(3DD4) : sub_toreg_8(0x1, &D2);            // SUBQ.B	#$01,D2
  DEF_ROMLOC(3DD6) : if (!CCR_EQ) goto rom_3E10;       // BNE.B	$3E10
  DEF_ROMLOC(3DD8) : move_toreg_16(0x188, &D1);        // MOVE.W	#$0188,D1
  DEF_ROMLOC(3DDC) : cmp_toreg_16(0x1AF0, &D0);        // CMPI.W	#$1AF0,D0
  DEF_ROMLOC(3DE0) : if (CCR_CS) goto rom_3E06;        // BCS.B	$3E06
  DEF_ROMLOC(3DE2) : move_toreg_16(0x900, &D1);        // MOVE.W	#$0900,D1
  DEF_ROMLOC(3DE6) : cmp_toreg_16(0x1BC0, &D0);        // CMPI.W	#$1BC0,D0
  DEF_ROMLOC(3DEA) : if (CCR_CS) goto rom_3E06;        // BCS.B	$3E06
  DEF_ROMLOC(3DEC) : move_tomem_8(0x4, 0xFFFFF64D);    // MOVE.B	#$04,$F64D
  DEF_ROMLOC(3DF2) : move_tomem_16(0x608, 0xFFFFF64A); // MOVE.W
                                                       // #$0608,$F64A
  DEF_ROMLOC(3DF8) : move_tomem_16(0x7C0, 0xFFFFF648); // MOVE.W
                                                       // #$07C0,$F648
  DEF_ROMLOC(3DFE) : move_tomem_8(0x1, 0xFFFFF7E8);    // MOVE.B	#$01,$F7E8
  DEF_ROMLOC(3E04) : return;                           // RTS
  DEF_ROMLOC(3E06) : move_tomem_16(D1, 0xFFFFF64A);    // MOVE.W	D1,$F64A
  DEF_ROMLOC(3E0A) : move_tomem_16(D1, 0xFFFFF648);    // MOVE.W	D1,$F648
  DEF_ROMLOC(3E0E) : return;                           // RTS
  DEF_ROMLOC(3E10) : cmp_toreg_16(0x1E00, &D0);        // CMPI.W	#$1E00,D0
  DEF_ROMLOC(3E14) : if (CCR_CS) goto rom_3E1C;        // BCS.B	$3E1C
  DEF_ROMLOC(3E16) : move_tomem_16(0x128, 0xFFFFF64A); // MOVE.W
                                                       // #$0128,$F64A
  DEF_ROMLOC(3E1C) : return;                           // RTS
}
ROMFUNC(rom_3E1E) {
  DEF_ROMLOC(3E1E) : move_toreg_16(0x228, &D1);       // MOVE.W	#$0228,D1
  DEF_ROMLOC(3E22) : cmp_tomem_16(0xF00, 0xFFFFF700); // CMPI.W	#$0F00,$F700
  DEF_ROMLOC(3E28) : if (CCR_CS) goto rom_3E2E;       // BCS.B	$3E2E
  DEF_ROMLOC(3E2A) : move_toreg_16(0x4C8, &D1);       // MOVE.W	#$04C8,D1
  DEF_ROMLOC(3E2E) : move_tomem_16(D1, 0xFFFFF64A);   // MOVE.W	D1,$F64A
  DEF_ROMLOC(3E32) : return;                          // RTS
}
ROMFUNC(rom_3E34) {
  DEF_ROMLOC(3E34) : tst_mem_16(0xFFFFFE08);     // TST.W	$FE08
  DEF_ROMLOC(3E38) : if (!CCR_EQ) goto rom_3F0C; // BNE.W	$3F0C
  DEF_ROMLOC(3E3C) : move_toreg_32(0x3F16, &A2); // LEA.L	$00003F16,A2
  DEF_ROMLOC(3E42) : move_toreg_32(0x0, &D0);    // MOVEQ.L	$00,D0
  DEF_ROMLOC(3E44)
      : move_toreg_8(read_8(0xFFFFFE11), &D0);       // MOVE.B	$FE11,D0
  DEF_ROMLOC(3E48) : lsl_toreg_16(0x3, &D0);         // LSL.W	#$03,D0
  DEF_ROMLOC(3E4A) : add_toreg_16(D0, &A2);          // ADDA.W	D0,A2
  DEF_ROMLOC(3E4C) : move_toreg_32(0x0, &D1);        // MOVEQ.L	$00,D1
  DEF_ROMLOC(3E4E) : tst_mem_8(0xFFFFFE11);          // TST.B	$FE11
  DEF_ROMLOC(3E52) : if (!CCR_EQ) goto rom_3E58;     // BNE.B	$3E58
  DEF_ROMLOC(3E54) : move_toreg_32(0x1, &D1);        // MOVEQ.L	$01,D1
  DEF_ROMLOC(3E56) : sub_toreg_16(0x8, &A2);         // SUBQ.W	#$08,A2
  DEF_ROMLOC(3E58) : move_toreg_32(0xFFFFD000, &A1); // LEA.L	$D000,A1
  DEF_ROMLOC(3E5C)
      : move_toreg_16(read_16(A1 + 0x8), &D0);       // MOVE.W	8(A1),D0
  DEF_ROMLOC(3E60) : cmp_toreg_16(read_16(A2), &D0); // CMP.W	(A2),D0
  DEF_ROMLOC(3E62) : if (CCR_CS) goto rom_3EF6;      // BCS.W	$3EF6
  DEF_ROMLOC(3E66)
      : cmp_toreg_16(read_16(A2 + 0x4), &D0);   // CMP.W	4(A2),D0
  DEF_ROMLOC(3E6A) : if (CCR_CC) goto rom_3EF6; // BCC.W	$3EF6
  DEF_ROMLOC(3E6E)
      : move_toreg_16(read_16(A1 + 0xC), &D2); // MOVE.W	12(A1),D2
  DEF_ROMLOC(3E72)
      : cmp_toreg_16(read_16(A2 + 0x2), &D2);   // CMP.W	2(A2),D2
  DEF_ROMLOC(3E76) : if (CCR_CS) goto rom_3EF6; // BCS.B	$3EF6
  DEF_ROMLOC(3E78)
      : cmp_toreg_16(read_16(A2 + 0x6), &D2);   // CMP.W	6(A2),D2
  DEF_ROMLOC(3E7C) : if (CCR_CC) goto rom_3EF6; // BCC.B	$3EF6
  DEF_ROMLOC(3E7E)
      : move_toreg_8(read_8(0xFFFFFE0F), &D0);        // MOVE.B	$FE0F,D0
  DEF_ROMLOC(3E82) : and_toreg_8(0x3F, &D0);          // ANDI.B	#$3F,D0
  DEF_ROMLOC(3E86) : if (!CCR_EQ) goto rom_3E92;      // BNE.B	$3E92
  DEF_ROMLOC(3E88) : move_toreg_16(0xD0, &D0);        // MOVE.W	#$00D0,D0
  DEF_ROMLOC(3E8C) : rom_1394();                      // JSR	$00001394
  DEF_ROMLOC(3E92) : tst_mem_8(0xFFFFF7C9);           // TST.B	$F7C9
  DEF_ROMLOC(3E96) : if (!CCR_EQ) goto rom_3F0C;      // BNE.W	$3F0C
  DEF_ROMLOC(3E9A) : cmp_tomem_8(0x4, A1 + 0x24);     // CMPI.B	#$04,36(A1)
  DEF_ROMLOC(3EA0) : if (CCR_CC) goto rom_3F08;       // BCC.B	$3F08
  DEF_ROMLOC(3EA2) : move_tomem_8(0x1, 0xFFFFF7C7);   // MOVE.B	#$01,$F7C7
  DEF_ROMLOC(3EA8) : sub_toreg_16(0x80, &D0);         // SUBI.W	#$0080,D0
  DEF_ROMLOC(3EAC) : cmp_toreg_16(read_16(A2), &D0);  // CMP.W	(A2),D0
  DEF_ROMLOC(3EAE) : if (CCR_CC) goto rom_3EC0;       // BCC.B	$3EC0
  DEF_ROMLOC(3EB0) : move_toreg_32(0x2, &D0);         // MOVEQ.L	$02,D0
  DEF_ROMLOC(3EB2) : cmp_tomem_8(0x1, 0xFFFFFE11);    // CMPI.B	#$01,$FE11
  DEF_ROMLOC(3EB8) : if (!CCR_EQ) goto rom_3EBC;      // BNE.B	$3EBC
  DEF_ROMLOC(3EBA) : neg_reg_16(&D0);                 // NEG.W	D0
  DEF_ROMLOC(3EBC) : add_tomem_16(D0, A1 + 0xC);      // ADD.W	D0,12(A1)
  DEF_ROMLOC(3EC0) : add_tomem_16(0x4, A1 + 0x8);     // ADDQ.W	#$04,8(A1)
  DEF_ROMLOC(3EC4) : move_tomem_16(0x400, A1 + 0x10); // MOVE.W	#$0400,16(A1)
  DEF_ROMLOC(3ECA) : move_tomem_16(0x0, A1 + 0x12);   // MOVE.W	#$0000,18(A1)
  DEF_ROMLOC(3ED0) : move_tomem_8(0xF, A1 + 0x1C);    // MOVE.B	#$0F,28(A1)
  DEF_ROMLOC(3ED6) : bset_tomem_8(0x1, A1 + 0x22);    // BSET.B	#$01,34(A1)
  DEF_ROMLOC(3EDC) : btst_tomem_8(0x0, 0xFFFFF602);   // BTST.B	#$00,$F602
  DEF_ROMLOC(3EE2) : if (CCR_EQ) goto rom_3EE8;       // BEQ.B	$3EE8
  DEF_ROMLOC(3EE4) : sub_tomem_16(0x1, A1 + 0xC);     // SUBQ.W	#$01,12(A1)
  DEF_ROMLOC(3EE8) : btst_tomem_8(0x1, 0xFFFFF602);   // BTST.B	#$01,$F602
  DEF_ROMLOC(3EEE) : if (CCR_EQ) goto rom_3EF4;       // BEQ.B	$3EF4
  DEF_ROMLOC(3EF0) : add_tomem_16(0x1, A1 + 0xC);     // ADDQ.W	#$01,12(A1)
  DEF_ROMLOC(3EF4) : return;                          // RTS
  DEF_ROMLOC(3EF6) : add_toreg_16(0x8, &A2);          // ADDQ.W	#$08,A2
  DEF_ROMLOC(3EF8) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_3E5C;                                 // DBF.W	D1,$3E5C
  DEF_ROMLOC(3EFC) : tst_mem_8(0xFFFFF7C7);        // TST.B	$F7C7
  DEF_ROMLOC(3F00) : if (CCR_EQ) goto rom_3F0C;    // BEQ.B	$3F0C
  DEF_ROMLOC(3F02) : move_tomem_8(0x0, A1 + 0x1C); // MOVE.B	#$00,28(A1)
  DEF_ROMLOC(3F08) : clr_mem_8(0xFFFFF7C7);        // CLR.B	$F7C7
  DEF_ROMLOC(3F0C) : return;                       // RTS
}
ROMFUNC(rom_3F36) {
  DEF_ROMLOC(3F36) : move_toreg_32(0xFFFFD000, &A1); // LEA.L	$D000,A1
  DEF_ROMLOC(3F3A) : btst_tomem_8(0x1, A1 + 0x22);   // BTST.B	#$01,34(A1)
  DEF_ROMLOC(3F40) : if (!CCR_EQ) goto rom_3F6C;     // BNE.B	$3F6C
  DEF_ROMLOC(3F42)
      : move_toreg_16(read_16(A1 + 0xC), &D0); // MOVE.W	12(A1),D0
  DEF_ROMLOC(3F46) : lsr_toreg_16(0x1, &D0);   // LSR.W	#$01,D0
  DEF_ROMLOC(3F48) : and_toreg_16(0x380, &D0); // ANDI.W	#$0380,D0
  DEF_ROMLOC(3F4C)
      : move_toreg_8(read_8(A1 + 0x8), &D1);         // MOVE.B	8(A1),D1
  DEF_ROMLOC(3F50) : and_toreg_16(0x7F, &D1);        // ANDI.W	#$007F,D1
  DEF_ROMLOC(3F54) : add_toreg_16(D1, &D0);          // ADD.W	D1,D0
  DEF_ROMLOC(3F56) : move_toreg_32(0xFFFFA400, &A2); // LEA.L	$A400,A2
  DEF_ROMLOC(3F5A)
      : move_toreg_8(read_8((s32)A2 + (s8)0x0 + (s16)D0),
                     &D0);                           // MOVE.B	0(A2,D0),D0
  DEF_ROMLOC(3F5E) : move_toreg_32(0x3FD1, &A2);     // LEA.L	113(PC),A2
  DEF_ROMLOC(3F62) : move_toreg_32(0x6, &D1);        // MOVEQ.L	$06,D1
  DEF_ROMLOC(3F64) : cmp_toreg_8(read_8(--A2), &D0); // CMP.B	-(A2),D0
  DEF_ROMLOC(3F66) : if (!CCR_EQ) {
    dec_reg_16(&D1);
    if ((D1 & 0xffff) != 0xffff)
      goto rom_3F64;
  };                                                // DBEQ.W	D1,$3F64
  DEF_ROMLOC(3F6A) : if (CCR_EQ) goto rom_3F7E;     // BEQ.B	$3F7E
  DEF_ROMLOC(3F6C) : tst_mem_8(0xFFFFF7CA);         // TST.B	$F7CA
  DEF_ROMLOC(3F70) : if (CCR_EQ) goto rom_3F7C;     // BEQ.B	$3F7C
  DEF_ROMLOC(3F72) : move_tomem_16(0x5, A1 + 0x3E); // MOVE.W	#$0005,62(A1)
  DEF_ROMLOC(3F78) : clr_mem_8(0xFFFFF7CA);         // CLR.B	$F7CA
  DEF_ROMLOC(3F7C) : return;                        // RTS
  DEF_ROMLOC(3F7E) : cmp_toreg_16(0x3, &D1);        // CMPI.W	#$0003,D1
  DEF_ROMLOC(3F82) : if (CCR_CC) goto rom_3F86;     // BCC.B	$3F86
  DEF_ROMLOC(3F84) : {};                            // NOP
  DEF_ROMLOC(3F86) : bclr_tomem_8(0x0, A1 + 0x22);  // BCLR.B	#$00,34(A1)
  DEF_ROMLOC(3F8C)
      : move_toreg_8(read_8(0x3FC2 + (s16)(D1 & 0xffff)),
                     &D0);                          // MOVE.B	52(PC,D1),D0
  DEF_ROMLOC(3F90) : move_tomem_8(D0, A1 + 0x14);   // MOVE.B	D0,20(A1)
  DEF_ROMLOC(3F94) : if (CCR_PL) goto rom_3F9C;     // BPL.B	$3F9C
  DEF_ROMLOC(3F96) : bset_tomem_8(0x0, A1 + 0x22);  // BSET.B	#$00,34(A1)
  DEF_ROMLOC(3F9C) : clr_mem_8(A1 + 0x15);          // CLR.B	21(A1)
  DEF_ROMLOC(3FA0) : move_tomem_8(0x1B, A1 + 0x1C); // MOVE.B	#$1B,28(A1)
  DEF_ROMLOC(3FA6) : move_tomem_8(0x1, 0xFFFFF7CA); // MOVE.B	#$01,$F7CA
  DEF_ROMLOC(3FAC)
      : move_toreg_8(read_8(0xFFFFFE0F), &D0);   // MOVE.B	$FE0F,D0
  DEF_ROMLOC(3FB0) : and_toreg_8(0x1F, &D0);     // ANDI.B	#$1F,D0
  DEF_ROMLOC(3FB4) : if (!CCR_EQ) goto rom_3FC0; // BNE.B	$3FC0
  DEF_ROMLOC(3FB6) : move_toreg_16(0xD0, &D0);   // MOVE.W	#$00D0,D0
  DEF_ROMLOC(3FBA) : rom_1394();                 // JSR	$00001394
  DEF_ROMLOC(3FC0) : return;                     // RTS
}