// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_FCA6) {
  u8 switchindex = 0;
  DEF_ROMLOC(FCA6) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(FCA8) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(FCAC)
      : move_toreg_16(read_16(0xFCB4 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(FCB0): goto rom_FCB4 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(FCB0) : switch (switchindex) {
  case 0:
    rom_FCBC();
    break;
  case 1:
    rom_FD20();
    break;
  case 2:
    rom_FDFC();
    break;
  case 3:
    rom_FE0A();
    break;
  }
}
ROMFUNC(rom_FCBC) {
  DEF_ROMLOC(FCBC)
      : move_tomem_32(0xFE2C, A0 + 0x4);             // MOVE.L	#$0000FE2C,4(A0)
  DEF_ROMLOC(FCC4) : move_tomem_16(0x4F0, A0 + 0x2); // MOVE.W	#$04F0,2(A0)
  DEF_ROMLOC(FCCA) : move_tomem_8(0x4, A0 + 0x1);    // MOVE.B	#$04,1(A0)
  DEF_ROMLOC(FCD0) : move_tomem_8(0x4, A0 + 0x18);   // MOVE.B	#$04,24(A0)
  DEF_ROMLOC(FCD6) : move_tomem_8(0x14, A0 + 0x19);  // MOVE.B	#$14,25(A0)
  DEF_ROMLOC(FCDC) : tst_mem_8(A0 + 0x1C);           // TST.B	28(A0)
  DEF_ROMLOC(FCE0) : if (!CCR_EQ) goto rom_FD18;     // BNE.B	$FD18
  DEF_ROMLOC(FCE2) : move_tomem_8(0xE, A0 + 0x16);   // MOVE.B	#$0E,22(A0)
  DEF_ROMLOC(FCE8) : move_tomem_8(0x8, A0 + 0x17);   // MOVE.B	#$08,23(A0)
  DEF_ROMLOC(FCEE) : move_tomem_8(0xC, A0 + 0x20);   // MOVE.B	#$0C,32(A0)
  DEF_ROMLOC(FCF4) : rom_DC40();                     // BSR.W	$DC40
  DEF_ROMLOC(FCF8) : rom_15580();                    // JSR	$00015580
  DEF_ROMLOC(FCFE) : tst_reg_16(&D1);                // TST.W	D1
  DEF_ROMLOC(FD00) : if (CCR_PL) goto rom_FD16;      // BPL.B	$FD16
  DEF_ROMLOC(FD02) : add_tomem_16(D1, A0 + 0xC);     // ADD.W	D1,12(A0)
  DEF_ROMLOC(FD06) : move_tomem_16(0x0, A0 + 0x12);  // MOVE.W	#$0000,18(A0)
  DEF_ROMLOC(FD0C) : add_tomem_8(0x2, A0 + 0x24);    // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(FD10) : bchg_tomem_8(0x0, A0 + 0x22);   // BCHG.B	#$00,34(A0)
  DEF_ROMLOC(FD16) : return;                         // RTS
  DEF_ROMLOC(FD18) : add_tomem_8(0x4, A0 + 0x24);    // ADDQ.B	#$04,36(A0)
  rom_FDFC();                                        // BRA.W	$FDFC
}
ROMFUNC(rom_FD74);
ROMFUNC(rom_FD98);
ROMFUNC(rom_FD20) {
  u8 switchindex = 0;
  DEF_ROMLOC(FD20) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(FD22) : move_toreg_8(read_8(A0 + 0x25), &D0);
  switchindex = D0 / 2; // MOVE.B	37(A0),D0
  DEF_ROMLOC(FD26)
      : move_toreg_16(read_16(0xFD70 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	72(PC,D0),D1
  // DEF_ROMLOC(FD2A): rom_FD70 + (s16)(D1 & 0xffff)(); // JSR	68(PC,D1)
  DEF_ROMLOC(FD2A) : switch (switchindex) {
  case 0:
    rom_FD74();
    break;
  case 1:
    rom_FD98();
    break;
  }
  DEF_ROMLOC(FD2E) : move_toreg_32(0xFE0E, &A1); // LEA.L	$0000FE0E,A1
  DEF_ROMLOC(FD34) : animate_sprite();                 // BSR.W	$ADA2
  rom_FD38(); // Detected flow into next function
}
ROMFUNC(rom_FD74) {
  DEF_ROMLOC(FD74) : sub_tomem_16(0x1, A0 + 0x30); // SUBQ.W	#$01,48(A0)
  DEF_ROMLOC(FD78) : if (CCR_PL) goto rom_FD96;    // BPL.B	$FD96
  DEF_ROMLOC(FD7A) : add_tomem_8(0x2, A0 + 0x25);  // ADDQ.B	#$02,37(A0)
  DEF_ROMLOC(FD7E)
      : move_tomem_16(0xFFFFFF00, A0 + 0x10);      // MOVE.W	#$FF00,16(A0)
  DEF_ROMLOC(FD84) : move_tomem_8(0x1, A0 + 0x1C); // MOVE.B	#$01,28(A0)
  DEF_ROMLOC(FD8A) : bchg_tomem_8(0x0, A0 + 0x22); // BCHG.B	#$00,34(A0)
  DEF_ROMLOC(FD90) : if (!CCR_EQ) goto rom_FD96;   // BNE.B	$FD96
  DEF_ROMLOC(FD92) : neg_mem_16(A0 + 0x10);        // NEG.W	16(A0)
  DEF_ROMLOC(FD96) : return;                       // RTS
}
ROMFUNC(rom_FD98) {
  DEF_ROMLOC(FD98) : rom_DC6C();                    // BSR.W	$DC6C
  DEF_ROMLOC(FD9C) : rom_15580();                   // JSR	$00015580
  DEF_ROMLOC(FDA2) : cmp_toreg_16(0xFFFFFFF8, &D1); // CMPI.W	#$FFF8,D1
  DEF_ROMLOC(FDA6) : if (CCR_LT) goto rom_FDE4;     // BLT.B	$FDE4
  DEF_ROMLOC(FDA8) : cmp_toreg_16(0xC, &D1);        // CMPI.W	#$000C,D1
  DEF_ROMLOC(FDAC) : if (CCR_GE) goto rom_FDE4;     // BGE.B	$FDE4
  DEF_ROMLOC(FDAE) : add_tomem_16(D1, A0 + 0xC);    // ADD.W	D1,12(A0)
  DEF_ROMLOC(FDB2) : sub_tomem_8(0x1, A0 + 0x33);   // SUBQ.B	#$01,51(A0)
  DEF_ROMLOC(FDB6) : if (CCR_PL) goto rom_FDE2;     // BPL.B	$FDE2
  DEF_ROMLOC(FDB8) : move_tomem_8(0xF, A0 + 0x33);  // MOVE.B	#$0F,51(A0)
  DEF_ROMLOC(FDBE) : rom_E11A();                    // BSR.W	$E11A
  DEF_ROMLOC(FDC2) : if (!CCR_EQ) goto rom_FDE2;    // BNE.B	$FDE2
  DEF_ROMLOC(FDC4) : move_tomem_8(0x40, A1 + 0x0);  // MOVE.B	#$40,0(A1)
  DEF_ROMLOC(FDCA)
      : move_tomem_16(read_16(A0 + 0x8), A1 + 0x8); // MOVE.W	8(A0),8(A1)
  DEF_ROMLOC(FDD0)
      : move_tomem_16(read_16(A0 + 0xC), A1 + 0xC); // MOVE.W	12(A0),12(A1)
  DEF_ROMLOC(FDD6)
      : move_tomem_8(read_8(A0 + 0x22), A1 + 0x22);  // MOVE.B	34(A0),34(A1)
  DEF_ROMLOC(FDDC) : move_tomem_8(0x2, A1 + 0x1C);   // MOVE.B	#$02,28(A1)
  DEF_ROMLOC(FDE2) : return;                         // RTS
  DEF_ROMLOC(FDE4) : sub_tomem_8(0x2, A0 + 0x25);    // SUBQ.B	#$02,37(A0)
  DEF_ROMLOC(FDE8) : move_tomem_16(0x3B, A0 + 0x30); // MOVE.W	#$003B,48(A0)
  DEF_ROMLOC(FDEE) : move_tomem_16(0x0, A0 + 0x10);  // MOVE.W	#$0000,16(A0)
  DEF_ROMLOC(FDF4) : move_tomem_8(0x0, A0 + 0x1C);   // MOVE.B	#$00,28(A0)
  DEF_ROMLOC(FDFA) : return;                         // RTS
}
ROMFUNC(rom_FDFC) {
  DEF_ROMLOC(FDFC) : move_toreg_32(0xFE0E, &A1); // LEA.L	$0000FE0E,A1
  DEF_ROMLOC(FE02) : animate_sprite();                 // BSR.W	$ADA2
  rom_DC92();                                    // BRA.W	$DC92
}
ROMFUNC(rom_FE0A) {
  DEF_ROMLOC(FE0A) : rom_DCCE(); // BRA.W	$DCCE
}