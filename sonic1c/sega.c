// #define CHECK_STUFF 1
#include "opcodes.h"
#include "system.h"

ROMFUNC(rom_396) { rom_2DD2(); }

void sega_cycle_palette(void) {
  DEF_ROMLOC(2002) : tst_mem_8(0xFFFFF635);          // TST.B	$F635
  DEF_ROMLOC(2006) : if (!CCR_EQ) goto rom_2062;     // BNE.B	$2062
  DEF_ROMLOC(2008) : move_toreg_32(0xFFFFFB20, &A1); // LEA.L	$FB20,A1
  DEF_ROMLOC(200C) : move_toreg_32(0x20B8, &A0);     // LEA.L	$000020B8,A0
  DEF_ROMLOC(2012) : move_toreg_32(0x5, &D1);        // MOVEQ.L	$05,D1
  DEF_ROMLOC(2014)
      : move_toreg_16(read_16(0xFFFFF632), &D0); // MOVE.W	$F632,D0
  DEF_ROMLOC(2018) : if (CCR_PL) goto rom_2022;  // BPL.B	$2022
  DEF_ROMLOC(201A) : add_toreg_16(0x2, &A0);     // ADDQ.W	#$02,A0
  DEF_ROMLOC(201C) : sub_toreg_16(0x1, &D1);     // SUBQ.W	#$01,D1
  DEF_ROMLOC(201E) : add_toreg_16(0x2, &D0);     // ADDQ.W	#$02,D0
  goto rom_2018;                                 // BRA.B	$2018
  DEF_ROMLOC(2022) : move_toreg_16(D0, &D2);     // MOVE.W	D0,D2
  DEF_ROMLOC(2024) : and_toreg_16(0x1E, &D2);    // ANDI.W	#$001E,D2
  DEF_ROMLOC(2028) : if (!CCR_EQ) goto rom_202C; // BNE.B	$202C
  DEF_ROMLOC(202A) : add_toreg_16(0x2, &D0);     // ADDQ.W	#$02,D0
  DEF_ROMLOC(202C) : cmp_toreg_16(0x60, &D0);    // CMPI.W	#$0060,D0
  DEF_ROMLOC(2030) : if (CCR_CC) goto rom_2036;  // BCC.B	$2036
  DEF_ROMLOC(2032)
      : move_tomem_16(read_16((A0 += 2, A0 - 2)),
                      (s32)A1 + (s8)0x0 + (s16)D0); // MOVE.W	(A0)+,0(A1,D0)
  DEF_ROMLOC(2036) : add_toreg_16(0x2, &D0);        // ADDQ.W	#$02,D0
  DEF_ROMLOC(2038) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_2022; // DBF.W	D1,$2022
  DEF_ROMLOC(203C)
      : move_toreg_16(read_16(0xFFFFF632), &D0);       // MOVE.W	$F632,D0
  DEF_ROMLOC(2040) : add_toreg_16(0x2, &D0);           // ADDQ.W	#$02,D0
  DEF_ROMLOC(2042) : move_toreg_16(D0, &D2);           // MOVE.W	D0,D2
  DEF_ROMLOC(2044) : and_toreg_16(0x1E, &D2);          // ANDI.W	#$001E,D2
  DEF_ROMLOC(2048) : if (!CCR_EQ) goto rom_204C;       // BNE.B	$204C
  DEF_ROMLOC(204A) : add_toreg_16(0x2, &D0);           // ADDQ.W	#$02,D0
  DEF_ROMLOC(204C) : cmp_toreg_16(0x64, &D0);          // CMPI.W	#$0064,D0
  DEF_ROMLOC(2050) : if (CCR_LT) goto rom_205A;        // BLT.B	$205A
  DEF_ROMLOC(2052) : move_tomem_16(0x401, 0xFFFFF634); // MOVE.W
                                                       // #$0401,$F634
  DEF_ROMLOC(2058) : move_toreg_32(0xFFFFFFF4, &D0);   // MOVEQ.L	$F4,D0
  DEF_ROMLOC(205A) : move_tomem_16(D0, 0xFFFFF632);    // MOVE.W	D0,$F632
  DEF_ROMLOC(205E) : move_toreg_32(0x1, &D0);          // MOVEQ.L	$01,D0
  DEF_ROMLOC(2060) : return;                           // RTS
  DEF_ROMLOC(2062) : sub_tomem_8(0x1, 0xFFFFF634);     // SUBQ.B	#$01,$F634
  DEF_ROMLOC(2066) : if (CCR_PL) goto rom_20B4;        // BPL.B	$20B4
  DEF_ROMLOC(2068) : move_tomem_8(0x4, 0xFFFFF634);    // MOVE.B	#$04,$F634
  DEF_ROMLOC(206E)
      : move_toreg_16(read_16(0xFFFFF632), &D0);    // MOVE.W	$F632,D0
  DEF_ROMLOC(2072) : add_toreg_16(0xC, &D0);        // ADDI.W	#$000C,D0
  DEF_ROMLOC(2076) : cmp_toreg_16(0x30, &D0);       // CMPI.W	#$0030,D0
  DEF_ROMLOC(207A) : if (CCR_CS) goto rom_2080;     // BCS.B	$2080
  DEF_ROMLOC(207C) : move_toreg_32(0x0, &D0);       // MOVEQ.L	$00,D0
  DEF_ROMLOC(207E) : return;                        // RTS
  DEF_ROMLOC(2080) : move_tomem_16(D0, 0xFFFFF632); // MOVE.W	D0,$F632
  DEF_ROMLOC(2084) : move_toreg_32(0x20C4, &A0);    // LEA.L	$000020C4,A0
  DEF_ROMLOC(208A)
      : move_toreg_32((s32)A0 + (s8)0x0 + (s16)D0,
                      &A0);                          // LEA.L	0(A0,D0),A0
  DEF_ROMLOC(208E) : move_toreg_32(0xFFFFFB04, &A1); // LEA.L	$FB04,A1
  DEF_ROMLOC(2092)
      : move_tomem_32(read_32((A0 += 4, A0 - 4)),
                      (A1 += 4, A1 - 4)); // MOVE.L	(A0)+,(A1)+
  DEF_ROMLOC(2094)
      : move_tomem_32(read_32((A0 += 4, A0 - 4)),
                      (A1 += 4, A1 - 4)); // MOVE.L	(A0)+,(A1)+
  DEF_ROMLOC(2096)
      : move_tomem_16(read_16((A0 += 2, A0 - 2)),
                      A1);                           // MOVE.W	(A0)+,(A1)
  DEF_ROMLOC(2098) : move_toreg_32(0xFFFFFB20, &A1); // LEA.L	$FB20,A1
  DEF_ROMLOC(209C) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(209E) : move_toreg_32(0x2C, &D1);       // MOVEQ.L	$2C,D1
  DEF_ROMLOC(20A0) : move_toreg_16(D0, &D2);         // MOVE.W	D0,D2
  DEF_ROMLOC(20A2) : and_toreg_16(0x1E, &D2);        // ANDI.W	#$001E,D2
  DEF_ROMLOC(20A6) : if (!CCR_EQ) goto rom_20AA;     // BNE.B	$20AA
  DEF_ROMLOC(20A8) : add_toreg_16(0x2, &D0);         // ADDQ.W	#$02,D0
  DEF_ROMLOC(20AA)
      : move_tomem_16(read_16(A0),
                      (s32)A1 + (s8)0x0 + (s16)D0); // MOVE.W	(A0),0(A1,D0)
  DEF_ROMLOC(20AE) : add_toreg_16(0x2, &D0);        // ADDQ.W	#$02,D0
  DEF_ROMLOC(20B0) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_20A0;                            // DBF.W	D1,$20A0
  DEF_ROMLOC(20B4) : move_toreg_32(0x1, &D0); // MOVEQ.L	$01,D0
  DEF_ROMLOC(20B6) : return;                  // RTS
}

ROMFUNC(rom_2EAC);
ROMFUNC(rom_2EB6);
ROMFUNC(rom_2DE2);
ROMFUNC(rom_2DD2) {
  SETBYTE(SR, 0x04);
  DEF_ROMLOC(2DD2) : move_toreg_8(0xFFFFFFE4, &D0); // MOVE.B	#$E4,D0
  DEF_ROMLOC(2DD6) : rom_1394();                    // BSR.W	$1394
  DEF_ROMLOC(2DDA) : rom_15D6();                    // BSR.W	$15D6
  DEF_ROMLOC(2DDE) : game_state = rom_2DE2; palette_fade_out(); // BSR.W	$1E4A
}
ROMFUNC(rom_2DE2) {
  DEF_ROMLOC(2DE2) : move_toreg_32(0xC00004, &A6);  // LEA.L	$00C00004,A6
  DEF_ROMLOC(2DE8) : move_tomem_16(0xFFFF8004, A6); // MOVE.W	#$8004,(A6)
  DEF_ROMLOC(2DEC) : move_tomem_16(0xFFFF8230, A6); // MOVE.W	#$8230,(A6)
  DEF_ROMLOC(2DF0) : move_tomem_16(0xFFFF8407, A6); // MOVE.W	#$8407,(A6)
  DEF_ROMLOC(2DF4) : move_tomem_16(0xFFFF8700, A6); // MOVE.W	#$8700,(A6)
  DEF_ROMLOC(2DF8) : move_tomem_16(0xFFFF8B00, A6); // MOVE.W	#$8B00,(A6)
  DEF_ROMLOC(2DFC) : clr_mem_8(0xFFFFF64E);         // CLR.B	$F64E
  DEF_ROMLOC(2E00) : move_tosr_16(0x2700, &SR);     // MOVE.W	#$2700,SR
  DEF_ROMLOC(2E04)
      : move_toreg_16(read_16(0xFFFFF60C), &D0);   // MOVE.W	$F60C,D0
  DEF_ROMLOC(2E08) : and_toreg_8(0xFFFFFFBF, &D0); // ANDI.B	#$BF,D0
  DEF_ROMLOC(2E0C) : move_tomem_16(D0, 0xC00004);  // MOVE.W	D0,$00C00004
  DEF_ROMLOC(2E12) : rom_12C4();                   // BSR.W	$12C4
  DEF_ROMLOC(2E16)
      : move_tomem_32(0x40000000, 0xC00004);      // MOVE.L	#$40000000,$00C00004
  DEF_ROMLOC(2E20) : move_toreg_32(0x1E700, &A0); // LEA.L	$0001E700,A0
  DEF_ROMLOC(2E26) : rom_1438();                  // rom_1438(); // BSR.W	$1438
  DEF_ROMLOC(2E2A) : move_toreg_32(v_256x256, &A1);   // LEA.L	$00FF0000,A1
  DEF_ROMLOC(2E30) : move_toreg_32(0x1EB70, &A0);    // LEA.L	$0001EB70,A0
  DEF_ROMLOC(2E36) : move_toreg_16(0x0, &D0);        // MOVE.W	#$0000,D0
  DEF_ROMLOC(2E3A) : rom_1716();                     // BSR.W	$1716
  DEF_ROMLOC(2E3E) : move_toreg_32(v_256x256, &A1);   // LEA.L	$00FF0000,A1
  DEF_ROMLOC(2E44) : move_toreg_32(0x65100003, &D0); // MOVE.L	#$65100003,D0
  DEF_ROMLOC(2E4A) : move_toreg_32(0x17, &D1);       // MOVEQ.L	$17,D1
  DEF_ROMLOC(2E4C) : move_toreg_32(0x7, &D2);        // MOVEQ.L	$07,D2
  DEF_ROMLOC(2E4E) : rom_1418();                     // BSR.W	$1418
  DEF_ROMLOC(2E52) : move_toreg_32(v_256x256 + 0x180, &A1);   // LEA.L	$00FF0180,A1
  DEF_ROMLOC(2E58) : move_toreg_32(0x40000003, &D0); // MOVE.L	#$40000003,D0
  DEF_ROMLOC(2E5E) : move_toreg_32(0x27, &D1);       // MOVEQ.L	$27,D1
  DEF_ROMLOC(2E60) : move_toreg_32(0x1B, &D2);       // MOVEQ.L	$1B,D2
  DEF_ROMLOC(2E62) : rom_1418();                     // BSR.W	$1418
  DEF_ROMLOC(2E66) : tst_mem_8(0xFFFFFFF8);          // TST.B	$FFF8
  DEF_ROMLOC(2E6A) : if (CCR_MI) goto rom_2E80;      // BMI.B	$2E80
  DEF_ROMLOC(2E6C) : move_toreg_32(v_256x256 + 0xA40, &A1);   // LEA.L	$00FF0A40,A1
  DEF_ROMLOC(2E72) : move_toreg_32(0x453A0003, &D0); // MOVE.L	#$453A0003,D0
  DEF_ROMLOC(2E78) : move_toreg_32(0x2, &D1);        // MOVEQ.L	$02,D1
  DEF_ROMLOC(2E7A) : move_toreg_32(0x1, &D2);        // MOVEQ.L	$01,D2
  DEF_ROMLOC(2E7C) : rom_1418();                     // BSR.W	$1418
  DEF_ROMLOC(2E80) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(2E82) : load_palette();                     // BSR.W	$2110
  DEF_ROMLOC(2E86)
      : move_tomem_16(0xFFFFFFF6, 0xFFFFF632);       // MOVE.W	#$FFF6,$F632
  DEF_ROMLOC(2E8C) : move_tomem_16(0x0, 0xFFFFF634); // MOVE.W	#$0000,$F634
  DEF_ROMLOC(2E92) : move_tomem_16(0x0, 0xFFFFF662); // MOVE.W	#$0000,$F662
  DEF_ROMLOC(2E98) : move_tomem_16(0x0, 0xFFFFF660); // MOVE.W	#$0000,$F660
  DEF_ROMLOC(2E9E)
      : move_toreg_16(read_16(0xFFFFF60C), &D0);  // MOVE.W	$F60C,D0
  DEF_ROMLOC(2EA2) : or_toreg_8(0x40, &D0);       // ORI.B	#$40,D0
  DEF_ROMLOC(2EA6) : move_tomem_16(D0, 0xC00004); // MOVE.W	D0,$00C00004
  rom_2EAC();
  game_state = rom_2EB6;
}
ROMFUNC(rom_2EAC) {
  DEF_ROMLOC(2EAC) : move_tomem_8(0x2, 0xFFFFF62A); // MOVE.B	#$02,$F62A
  DEF_ROMLOC(2EB2) : rom_29A0(); // rom_29A0(); // BSR.W	$29A0
}
ROMFUNC(rom_2ECE);
ROMFUNC(rom_2EB6) {
  DEF_ROMLOC(2EB6) : sega_cycle_palette(); // BSR.W	$2002
  DEF_ROMLOC(2EBA) : if (!CCR_EQ) {
    rom_2EAC();
    return;
  }                                                  // BNE.B	$2EAC
  DEF_ROMLOC(2EBC) : move_toreg_8(0xFFFFFFE1, &D0);  // MOVE.B	#$E1,D0
  DEF_ROMLOC(2EC0) : rom_1394();                     // BSR.W	$1394
  DEF_ROMLOC(2EC4) : move_tomem_8(0x14, 0xFFFFF62A); // MOVE.B	#$14,$F62A
  DEF_ROMLOC(2ECA) : rom_29A0(); // rom_29A0(); // BSR.W	$29A0
  game_state = rom_2ECE;
}
ROMFUNC(rom_2EDE);
ROMFUNC(rom_2ECE) {
  DEF_ROMLOC(2ECE) : move_tomem_16(0x1E, 0xFFFFF614); // MOVE.W	#$001E,$F614
  rom_2ED4();
  game_state = rom_2EDE;
}
ROMFUNC(rom_2ED4) {
  DEF_ROMLOC(2ED4) : move_tomem_8(0x2, 0xFFFFF62A); // MOVE.B	#$02,$F62A
  DEF_ROMLOC(2EDA) : rom_29A0(); // rom_29A0(); // BSR.W	$29A0
}
ROMFUNC(rom_2EDE) {
  DEF_ROMLOC(2EDE) : tst_mem_16(0xFFFFF614);    // TST.W	$F614
  DEF_ROMLOC(2EE2) : if (CCR_EQ) goto rom_2EEC; // BEQ.B	$2EEC
  DEF_ROMLOC(2EE4)
      : and_tomem_8(0xFFFFFF80, 0xFFFFF605); // ANDI.B	#$80,$F605
  DEF_ROMLOC(2EEA) : if (CCR_EQ) {
    rom_2ED4();
    return;
  } // BEQ.B	$2ED4
  DEF_ROMLOC(2EEC) : SET_GM_TITLE();
  DEF_ROMLOC(2EF2): return; // RTS
}