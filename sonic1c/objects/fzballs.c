// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_1AF90) {
  u8 switchindex = 0;
  DEF_ROMLOC(1AF90) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(1AF92) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(1AF96)
      : move_toreg_16(read_16(0x1AF9E + (s16)(D0 & 0xffff)),
                      &D0); // MOVE.W	6(PC,D0),D0
  // DEF_ROMLOC(1AF9A): goto rom_1AF9E + (s16)(D0 & 0xffff); // JMP	2(PC,D0)
  DEF_ROMLOC(1AF9A) : switch (switchindex) {
  case 0:
    rom_1AFA8();
    break;
  case 1:
    rom_1AFEA();
    break;
  case 2:
    rom_1B060();
    break;
  case 3:
    rom_1B118();
    break;
  case 4:
    rom_1B138();
    break;
  }
}
ROMFUNC(rom_1AFA8) {
  DEF_ROMLOC(1AFA8) : move_tomem_16(0x2588, A0 + 0x8); // MOVE.W
                                                       // #$2588,8(A0)
  DEF_ROMLOC(1AFAE) : move_tomem_16(0x53C, A0 + 0xC);  // MOVE.W	#$053C,12(A0)
  DEF_ROMLOC(1AFB4) : move_tomem_16(0x300, A0 + 0x2);  // MOVE.W	#$0300,2(A0)
  DEF_ROMLOC(1AFBA)
      : move_tomem_32(0x1B20C, A0 + 0x4);           // MOVE.L	#$0001B20C,4(A0)
  DEF_ROMLOC(1AFC2) : move_tomem_8(0x0, A0 + 0x1C); // MOVE.B	#$00,28(A0)
  DEF_ROMLOC(1AFC8) : move_tomem_8(0x3, A0 + 0x18); // MOVE.B	#$03,24(A0)
  DEF_ROMLOC(1AFCE) : move_tomem_8(0x8, A0 + 0x17); // MOVE.B	#$08,23(A0)
  DEF_ROMLOC(1AFD4) : move_tomem_8(0x8, A0 + 0x16); // MOVE.B	#$08,22(A0)
  DEF_ROMLOC(1AFDA) : move_tomem_8(0x4, A0 + 0x1);  // MOVE.B	#$04,1(A0)
  DEF_ROMLOC(1AFE0) : bset_tomem_8(0x7, A0 + 0x1);  // BSET.B	#$07,1(A0)
  DEF_ROMLOC(1AFE6) : add_tomem_8(0x2, A0 + 0x24);  // ADDQ.B	#$02,36(A0)
  rom_1AFEA(); // Detected flow into next function
}
ROMFUNC(rom_1B022) {
  DEF_ROMLOC(1B022) : move_toreg_16(0x13, &D1); // MOVE.W	#$0013,D1
  DEF_ROMLOC(1B026) : move_toreg_16(0x8, &D2);  // MOVE.W	#$0008,D2
  DEF_ROMLOC(1B02A) : move_toreg_16(0x11, &D3); // MOVE.W	#$0011,D3
  DEF_ROMLOC(1B02E)
      : move_toreg_16(read_16(A0 + 0x8), &D4); // MOVE.W	8(A0),D4
  DEF_ROMLOC(1B032) : rom_10062();             // JSR	$00010062
  DEF_ROMLOC(1B038)
      : move_toreg_16(read_16(0xFFFFD008), &D0); // MOVE.W	$D008,D0
  DEF_ROMLOC(1B03C)
      : sub_toreg_16(read_16(A0 + 0x8), &D0);     // SUB.W	8(A0),D0
  DEF_ROMLOC(1B040) : if (CCR_MI) goto rom_1B050; // BMI.B	$1B050
  DEF_ROMLOC(1B042) : sub_toreg_16(GAME_WIDTH, &D0);   // SUBI.W	#$0140,D0
  DEF_ROMLOC(1B046) : if (CCR_MI) goto rom_1B050; // BMI.B	$1B050
  DEF_ROMLOC(1B048) : tst_mem_8(A0 + 0x1);        // TST.B	1(A0)
  DEF_ROMLOC(1B04C) : if (CCR_PL) {
    rom_1ABFE();
    return;
  }                                                // BPL.W	$1ABFE
  DEF_ROMLOC(1B050) : move_toreg_32(0x1B1F6, &A1); // LEA.L	420(PC),A1
  DEF_ROMLOC(1B054) : animate_sprite();                  // JSR	$0000ADA2
  DEF_ROMLOC(1B05A) : rom_DC92();
  return; // JMP	$0000DC92
}
ROMFUNC(rom_1AFEA) {
  DEF_ROMLOC(1AFEA)
      : move_toreg_32(read_32(A0 + 0x34), &A1);     // MOVEA.L	52(A0),A1
  DEF_ROMLOC(1AFEE) : cmp_tomem_8(0x6, A1 + 0x34);  // CMPI.B	#$06,52(A1)
  DEF_ROMLOC(1AFF4) : if (!CCR_EQ) goto rom_1B006;  // BNE.B	$1B006
  DEF_ROMLOC(1AFF6) : move_tomem_8(OBJ_EXPLOSIONBOMB, A0 + offsetof(object, id));       // MOVE.B	#$3F,(A0)
  DEF_ROMLOC(1AFFA) : move_tomem_8(0x0, A0 + 0x24); // MOVE.B	#$00,36(A0)
  DEF_ROMLOC(1B000) : rom_DC92();
  return;                                           // JMP	$0000DC92
  DEF_ROMLOC(1B006) : move_tomem_8(0x0, A0 + 0x1C); // MOVE.B	#$00,28(A0)
  DEF_ROMLOC(1B00C) : tst_mem_8(A0 + 0x29);         // TST.B	41(A0)
  DEF_ROMLOC(1B010) : if (CCR_EQ) {
    rom_1B022();
    return;
  }                                                  // BEQ.B	$1B022
  DEF_ROMLOC(1B012) : add_tomem_8(0x2, A0 + 0x24);   // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(1B016) : move_tomem_8(0x1, A0 + 0x1C);  // MOVE.B	#$01,28(A0)
  DEF_ROMLOC(1B01C) : move_tomem_8(0x3E, A0 + 0x28); // MOVE.B	#$3E,40(A0)
  rom_1B022();
}
ROMFUNC(rom_1B060) {
  DEF_ROMLOC(1B060) : tst_mem_8(A0 + 0x29);       // TST.B	41(A0)
  DEF_ROMLOC(1B064) : if (CCR_EQ) goto rom_1B10A; // BEQ.W	$1B10A
  DEF_ROMLOC(1B068) : clr_mem_8(A0 + 0x29);       // CLR.B	41(A0)
  DEF_ROMLOC(1B06C)
      : add_toreg_16(read_16(A0 + 0x30), &D0);      // ADD.W	48(A0),D0
  DEF_ROMLOC(1B070) : and_toreg_16(0x1E, &D0);      // ANDI.W	#$001E,D0
  DEF_ROMLOC(1B074) : add_toreg_16(D0, &A2);        // ADDA.W	D0,A2
  DEF_ROMLOC(1B076) : add_tomem_16(0x4, A0 + 0x30); // ADDQ.W	#$04,48(A0)
  DEF_ROMLOC(1B07A) : clr_mem_16(A0 + 0x32);        // CLR.W	50(A0)
  DEF_ROMLOC(1B07E) : move_toreg_32(0x3, &D2);      // MOVEQ.L	$03,D2
  DEF_ROMLOC(1B080) : rom_E130();                   // JSR	$0000E130
  DEF_ROMLOC(1B086) : if (!CCR_EQ) goto rom_1B10A;  // BNE.W	$1B10A
  DEF_ROMLOC(1B08A) : move_tomem_8(OBJ_BOSSPLASMA, A1 + offsetof(object, id)); // MOVE.B	#$86,(A1)
  DEF_ROMLOC(1B08E)
      : move_tomem_16(read_16(A0 + 0x8), A1 + 0x8);    // MOVE.W	8(A0),8(A1)
  DEF_ROMLOC(1B094) : move_tomem_16(0x53C, A1 + 0xC);  // MOVE.W	#$053C,12(A1)
  DEF_ROMLOC(1B09A) : move_tomem_8(0x8, A1 + 0x24);    // MOVE.B	#$08,36(A1)
  DEF_ROMLOC(1B0A0) : move_tomem_16(0x2300, A1 + 0x2); // MOVE.W
                                                       // #$2300,2(A1)
  DEF_ROMLOC(1B0A6)
      : move_tomem_32(0x1B25C, A1 + 0x4);             // MOVE.L	#$0001B25C,4(A1)
  DEF_ROMLOC(1B0AE) : move_tomem_8(0xC, A1 + 0x16);   // MOVE.B	#$0C,22(A1)
  DEF_ROMLOC(1B0B4) : move_tomem_8(0xC, A1 + 0x17);   // MOVE.B	#$0C,23(A1)
  DEF_ROMLOC(1B0BA) : move_tomem_8(0x0, A1 + 0x20);   // MOVE.B	#$00,32(A1)
  DEF_ROMLOC(1B0C0) : move_tomem_8(0x3, A1 + 0x18);   // MOVE.B	#$03,24(A1)
  DEF_ROMLOC(1B0C6) : move_tomem_16(0x3E, A1 + 0x28); // MOVE.W	#$003E,40(A1)
  DEF_ROMLOC(1B0CC) : move_tomem_8(0x4, A1 + 0x1);    // MOVE.B	#$04,1(A1)
  DEF_ROMLOC(1B0D2) : bset_tomem_8(0x7, A1 + 0x1);    // BSET.B	#$07,1(A1)
  DEF_ROMLOC(1B0D8) : move_tomem_32(A0, A1 + 0x34);   // MOVE.L	A0,52(A1)
  DEF_ROMLOC(1B0DC) : rom_29AC();                     // JSR	$000029AC
  DEF_ROMLOC(1B0E2)
      : move_toreg_16(read_16(A0 + 0x32), &D1);       // MOVE.W	50(A0),D1
  DEF_ROMLOC(1B0E6) : muls_toreg_16(0xFFFFFFB1, &D1); // MULS.W	#$FFB1,D1
  DEF_ROMLOC(1B0EA) : add_toreg_16(0x2578, &D1);      // ADDI.W	#$2578,D1
  DEF_ROMLOC(1B0EE) : and_toreg_16(0x1F, &D0);        // ANDI.W	#$001F,D0
  DEF_ROMLOC(1B0F2) : sub_toreg_16(0x10, &D0);        // SUBI.W	#$0010,D0
  DEF_ROMLOC(1B0F6) : add_toreg_16(D1, &D0);          // ADD.W	D1,D0
  DEF_ROMLOC(1B0F8) : move_tomem_16(D0, A1 + 0x30);   // MOVE.W	D0,48(A1)
  DEF_ROMLOC(1B0FC) : add_tomem_16(0x1, A0 + 0x32);   // ADDQ.W	#$01,50(A0)
  DEF_ROMLOC(1B100)
      : move_tomem_16(read_16(A0 + 0x32), A0 + 0x38); // MOVE.W	50(A0),56(A0)
  DEF_ROMLOC(1B106) : dec_reg_16(&D2);
  if ((D2 & 0xffff) != 0xffff)
    goto rom_1B080;                                // DBF.W	D2,$1B080
  DEF_ROMLOC(1B10A) : tst_mem_16(A0 + 0x32);       // TST.W	50(A0)
  DEF_ROMLOC(1B10E) : if (!CCR_EQ) goto rom_1B114; // BNE.B	$1B114
  DEF_ROMLOC(1B110) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(1B114) : rom_1B022();                 // BRA.W	$1B022
}
ROMFUNC(rom_1B118) {
  DEF_ROMLOC(1B118) : move_tomem_8(0x2, A0 + 0x1C); // MOVE.B	#$02,28(A0)
  DEF_ROMLOC(1B11E) : tst_mem_16(A0 + 0x38);        // TST.W	56(A0)
  DEF_ROMLOC(1B122) : if (!CCR_EQ) goto rom_1B134;  // BNE.B	$1B134
  DEF_ROMLOC(1B124) : move_tomem_8(0x2, A0 + 0x24); // MOVE.B	#$02,36(A0)
  DEF_ROMLOC(1B12A)
      : move_toreg_32(read_32(A0 + 0x34), &A1); // MOVEA.L	52(A0),A1
  DEF_ROMLOC(1B12E)
      : move_tomem_16(0xFFFFFFFF, A1 + 0x32); // MOVE.W	#$FFFF,50(A1)
  DEF_ROMLOC(1B134) : rom_1B022();            // BRA.W	$1B022
}
ROMFUNC(rom_1B138) {
  u8 switchindex = 0;
  DEF_ROMLOC(1B138) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(1B13A) : move_toreg_8(read_8(A0 + 0x25), &D0);
  switchindex = D0 / 2; // MOVE.B	37(A0),D0
  DEF_ROMLOC(1B13E)
      : move_toreg_16(read_16(0x1B156 + (s16)(D0 & 0xffff)),
                      &D0); // MOVE.W	22(PC,D0),D0
  // DEF_ROMLOC(1B142): rom_1B156 + (s16)(D0 & 0xffff)(); // JSR
  // 18(PC,D0)
  DEF_ROMLOC(1B142) : switch (switchindex) {
  case 0:
    rom_1B15C();
    break;
  case 1:
    rom_1B176();
    break;
  case 2:
    rom_1B1D4();
    break;
  }
  DEF_ROMLOC(1B146) : move_toreg_32(0x1B22C, &A1); // LEA.L	228(PC),A1
  DEF_ROMLOC(1B14A) : animate_sprite();                  // JSR	$0000ADA2
  DEF_ROMLOC(1B150) : rom_DC92();
  return; // JMP	$0000DC92
}
ROMFUNC(rom_1B156) {
  DEF_ROMLOC(1B156) : or_toreg_8(0x20, &D6); // ORI.B	#$20,D6
  rom_1B15C();                               // Detected flow into next function
}
ROMFUNC(rom_1B15C) {
  DEF_ROMLOC(1B15C)
      : move_toreg_16(read_16(A0 + 0x30), &D0); // MOVE.W	48(A0),D0
  DEF_ROMLOC(1B160)
      : sub_toreg_16(read_16(A0 + 0x8), &D0);         // SUB.W	8(A0),D0
  DEF_ROMLOC(1B164) : asl_toreg_16(0x4, &D0);         // ASL.W	#$04,D0
  DEF_ROMLOC(1B166) : move_tomem_16(D0, A0 + 0x10);   // MOVE.W	D0,16(A0)
  DEF_ROMLOC(1B16A) : move_tomem_16(0xB4, A0 + 0x28); // MOVE.W	#$00B4,40(A0)
  DEF_ROMLOC(1B170) : add_tomem_8(0x2, A0 + 0x25);    // ADDQ.B	#$02,37(A0)
  DEF_ROMLOC(1B174) : return;                         // RTS
}
ROMFUNC(rom_1B176) {
  DEF_ROMLOC(1B176) : tst_mem_16(A0 + 0x10);      // TST.W	16(A0)
  DEF_ROMLOC(1B17A) : if (CCR_EQ) goto rom_1B19C; // BEQ.B	$1B19C
  DEF_ROMLOC(1B17C) : rom_DC6C();                 // JSR	$0000DC6C
  DEF_ROMLOC(1B182)
      : move_toreg_16(read_16(A0 + 0x8), &D0); // MOVE.W	8(A0),D0
  DEF_ROMLOC(1B186)
      : sub_toreg_16(read_16(A0 + 0x30), &D0);    // SUB.W	48(A0),D0
  DEF_ROMLOC(1B18A) : if (CCR_CC) goto rom_1B19C; // BCC.B	$1B19C
  DEF_ROMLOC(1B18C) : clr_mem_16(A0 + 0x10);      // CLR.W	16(A0)
  DEF_ROMLOC(1B190) : add_tomem_16(D0, A0 + 0x8); // ADD.W	D0,8(A0)
  DEF_ROMLOC(1B194)
      : move_toreg_32(read_32(A0 + 0x34), &A1);     // MOVEA.L	52(A0),A1
  DEF_ROMLOC(1B198) : sub_tomem_16(0x1, A1 + 0x32); // SUBQ.W	#$01,50(A1)
  DEF_ROMLOC(1B19C) : move_tomem_8(0x0, A0 + 0x1C); // MOVE.B	#$00,28(A0)
  DEF_ROMLOC(1B1A2) : sub_tomem_16(0x1, A0 + 0x28); // SUBQ.W	#$01,40(A0)
  DEF_ROMLOC(1B1A6) : if (!CCR_EQ) goto rom_1B1D2;  // BNE.B	$1B1D2
  DEF_ROMLOC(1B1A8) : add_tomem_8(0x2, A0 + 0x25);  // ADDQ.B	#$02,37(A0)
  DEF_ROMLOC(1B1AC) : move_tomem_8(0x1, A0 + 0x1C); // MOVE.B	#$01,28(A0)
  DEF_ROMLOC(1B1B2)
      : move_tomem_8(0xFFFFFF9A, A0 + 0x20);          // MOVE.B	#$9A,32(A0)
  DEF_ROMLOC(1B1B8) : move_tomem_16(0xB4, A0 + 0x28); // MOVE.W	#$00B4,40(A0)
  DEF_ROMLOC(1B1BE) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(1B1C0)
      : move_toreg_16(read_16(0xFFFFD008), &D0); // MOVE.W	$D008,D0
  DEF_ROMLOC(1B1C4)
      : sub_toreg_16(read_16(A0 + 0x8), &D0);          // SUB.W	8(A0),D0
  DEF_ROMLOC(1B1C8) : move_tomem_16(D0, A0 + 0x10);    // MOVE.W	D0,16(A0)
  DEF_ROMLOC(1B1CC) : move_tomem_16(0x140, A0 + 0x12); // MOVE.W
                                                       // #$0140,18(A0)
  DEF_ROMLOC(1B1D2) : return;                          // RTS
}
ROMFUNC(rom_1B1D4) {
  DEF_ROMLOC(1B1D4) : rom_DC6C();                    // JSR	$0000DC6C
  DEF_ROMLOC(1B1DA) : cmp_tomem_16(0x5E0, A0 + 0xC); // CMPI.W	#$05E0,12(A0)
  DEF_ROMLOC(1B1E0) : if (CCR_CC) goto rom_1B1EA;    // BCC.B	$1B1EA
  DEF_ROMLOC(1B1E2) : sub_tomem_16(0x1, A0 + 0x28);  // SUBQ.W	#$01,40(A0)
  DEF_ROMLOC(1B1E6) : if (CCR_EQ) goto rom_1B1EA;    // BEQ.B	$1B1EA
  DEF_ROMLOC(1B1E8) : return;                        // RTS
  DEF_ROMLOC(1B1EA)
      : move_toreg_32(read_32(A0 + 0x34), &A1);     // MOVEA.L	52(A0),A1
  DEF_ROMLOC(1B1EE) : sub_tomem_16(0x1, A1 + 0x38); // SUBQ.W	#$01,56(A1)
  DEF_ROMLOC(1B1F2) : rom_1ABFE();
  return; // BRA.W	$1ABFE
}