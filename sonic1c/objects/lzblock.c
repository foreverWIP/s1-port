// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_126A8) {
  u8 switchindex = 0;
  DEF_ROMLOC(126A8) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(126AA) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(126AE)
      : move_toreg_16(read_16(0x126B6 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(126B2): goto rom_126B6 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(126B2) : switch (switchindex) {
  case 0:
    rom_126C2();
    break;
  case 1:
    rom_12720();
    break;
  }
}
ROMFUNC(rom_126BA) {
  DEF_ROMLOC(126BA) : move_toreg_8(read_8(A0), &D0); // MOVE.B	(A0),D0
  DEF_ROMLOC(126BC) : move_toreg_32(A4, &D0);        // MOVE.L	A4,D0
  DEF_ROMLOC(126BE) : move_toreg_8(read_8(A0), &D0); // MOVE.B	(A0),D0
  DEF_ROMLOC(126C0) : move_toreg_8(read_8(A0), &D0); // MOVE.B	(A0),D0
  rom_126C2(); // Detected flow into next function
}
ROMFUNC(rom_126C2) {
  DEF_ROMLOC(126C2) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(126C6)
      : move_tomem_32(0x12896, A0 + 0x4); // MOVE.L	#$00012896,4(A0)
  DEF_ROMLOC(126CE)
      : move_tomem_16(0x43E6, A0 + 0x2);            // MOVE.W
                                                    // #$43E6,2(A0)
  DEF_ROMLOC(126D4) : move_tomem_8(0x4, A0 + 0x1);  // MOVE.B	#$04,1(A0)
  DEF_ROMLOC(126DA) : move_tomem_8(0x3, A0 + 0x18); // MOVE.B	#$03,24(A0)
  DEF_ROMLOC(126E0) : move_toreg_32(0x0, &D0);      // MOVEQ.L	$00,D0
  DEF_ROMLOC(126E2)
      : move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B
                                              // 40(A0),D0
  DEF_ROMLOC(126E6) : lsr_toreg_16(0x3, &D0); // LSR.W	#$03,D0
  DEF_ROMLOC(126E8) : and_toreg_16(0xE, &D0); // ANDI.W	#$000E,D0
  DEF_ROMLOC(126EC)
      : move_toreg_32(0x126BA + (s16)(D0 & 0xffff),
                      &A2); // LEA.L	-52(PC,D0),A2
  DEF_ROMLOC(126F0)
      : move_tomem_8(read_8(A2++), A0 + 0x19); // MOVE.B	(A2)+,25(A0)
  DEF_ROMLOC(126F4)
      : move_tomem_8(read_8(A2), A0 + 0x16);       // MOVE.B	(A2),22(A0)
  DEF_ROMLOC(126F8) : lsr_toreg_16(0x1, &D0);      // LSR.W	#$01,D0
  DEF_ROMLOC(126FA) : move_tomem_8(D0, A0 + 0x1A); // MOVE.B	D0,26(A0)
  DEF_ROMLOC(126FE)
      : move_tomem_16(read_16(A0 + 0x8), A0 + 0x34); // MOVE.W	8(A0),52(A0)
  DEF_ROMLOC(12704)
      : move_tomem_16(read_16(A0 + 0xC), A0 + 0x30); // MOVE.W	12(A0),48(A0)
  DEF_ROMLOC(1270A)
      : move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B
                                              // 40(A0),D0
  DEF_ROMLOC(1270E) : and_toreg_8(0xF, &D0);  // ANDI.B	#$0F,D0
  DEF_ROMLOC(12712) : if (CCR_EQ) {
    rom_12720();
    return;
  } // BEQ.B	$12720
  DEF_ROMLOC(12714) : cmp_toreg_8(0x7, &D0); // CMPI.B	#$07,D0
  DEF_ROMLOC(12718) : if (CCR_EQ) {
    rom_12720();
    return;
  } // BEQ.B	$12720
  DEF_ROMLOC(1271A) : move_tomem_8(0x1, A0 + 0x38); // MOVE.B	#$01,56(A0)
  rom_12720(); // Detected flow into next function
}
ROMFUNC(rom_12792);
ROMFUNC(rom_12794);
ROMFUNC(rom_127BA);
ROMFUNC(rom_12794);
ROMFUNC(rom_127DC);
ROMFUNC(rom_127FC);
ROMFUNC(rom_127BA);
ROMFUNC(rom_12792);
ROMFUNC(rom_1280E);
ROMFUNC(rom_12720) {
  u8 switchindex = 0;
  DEF_ROMLOC(12720)
      : move_tomem_16(read_16(A0 + 0x8), A7 -= 2); // MOVE.W	8(A0),-(A7)
  DEF_ROMLOC(12724) : move_toreg_32(0x0, &D0);     // MOVEQ.L	$00,D0
  DEF_ROMLOC(12726)
      : move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B
                                              // 40(A0),D0
  DEF_ROMLOC(1272A) : and_toreg_16(0xF, &D0);
  switchindex = D0;                          // ANDI.W	#$000F,D0
  DEF_ROMLOC(1272E) : add_toreg_16(D0, &D0); // ADD.W	D0,D0
  DEF_ROMLOC(12730)
      : move_toreg_16(read_16(0x12782 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	80(PC,D0),D1
  // DEF_ROMLOC(12734): rom_12782 + (s16)(D1 & 0xffff)(); // JSR
  // 76(PC,D1)
  DEF_ROMLOC(12734) : switch (switchindex) {
  case 0:
    rom_12792();
    break;
  case 1:
    rom_12794();
    break;
  case 2:
    rom_127BA();
    break;
  case 3:
    rom_12794();
    break;
  case 4:
    rom_127DC();
    break;
  case 5:
    rom_127FC();
    break;
  case 6:
    rom_127BA();
    break;
  case 7:
    rom_1280E();
    break;
  }
  DEF_ROMLOC(12738)
      : move_toreg_16(read_16((A7 += 2, A7 - 2)), &D4); // MOVE.W	(A7)+,D4
  DEF_ROMLOC(1273A) : tst_mem_8(A0 + 0x1);              // TST.B	1(A0)
  DEF_ROMLOC(1273E) : if (CCR_PL) goto rom_12760;       // BPL.B	$12760
  DEF_ROMLOC(12740) : move_toreg_32(0x0, &D1);          // MOVEQ.L	$00,D1
  DEF_ROMLOC(12742)
      : move_toreg_8(read_8(A0 + 0x19), &D1);  // MOVE.B	25(A0),D1
  DEF_ROMLOC(12746) : add_toreg_16(0xB, &D1);  // ADDI.W	#$000B,D1
  DEF_ROMLOC(1274A) : move_toreg_32(0x0, &D2); // MOVEQ.L	$00,D2
  DEF_ROMLOC(1274C)
      : move_toreg_8(read_8(A0 + 0x16), &D2);      // MOVE.B	22(A0),D2
  DEF_ROMLOC(12750) : move_toreg_16(D2, &D3);      // MOVE.W	D2,D3
  DEF_ROMLOC(12752) : add_toreg_16(0x1, &D3);      // ADDQ.W	#$01,D3
  DEF_ROMLOC(12754) : rom_10062();                 // BSR.W	$10062
  DEF_ROMLOC(12758) : move_tomem_8(D4, A0 + 0x3F); // MOVE.B	D4,63(A0)
  DEF_ROMLOC(1275C) : rom_12854();                 // BSR.W	$12854
  DEF_ROMLOC(12760)
      : move_toreg_16(read_16(A0 + 0x34), &D0);      // MOVE.W	52(A0),D0
  DEF_ROMLOC(12764) : and_toreg_16(0xFFFFFF80, &D0); // ANDI.W	#$FF80,D0
  DEF_ROMLOC(12768)
      : move_toreg_16(read_16(v_screenposx), &D1);   // MOVE.W	$F700,D1
  DEF_ROMLOC(1276C) : sub_toreg_16(0x80, &D1);       // SUBI.W	#$0080,D1
  DEF_ROMLOC(12770) : and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
  DEF_ROMLOC(12774) : sub_toreg_16(D1, &D0);         // SUB.W	D1,D0
  DEF_ROMLOC(12776)
      : cmp_toreg_16(128 + GAME_WIDTH + 192, &D0); // CMPI.W	#$0280,D0
  DEF_ROMLOC(1277A) : if (CCR_HI) {
    rom_DCCE();
    return;
  } // BHI.W	$DCCE
  rom_DC92(); // BRA.W	$DC92
}
ROMFUNC(rom_12782) {
  DEF_ROMLOC(12782) : or_tomem_8(0x12, A0);   // ORI.B	#$12,(A0)
  DEF_ROMLOC(12786) : or_tomem_8(0x12, 0x5A); // ORI.B	#$12,$005A
  rom_12792(); // Detected flow into next function
}
ROMFUNC(rom_12792) {
  DEF_ROMLOC(12792) : return; // RTS
}
ROMFUNC(rom_12794) {
  DEF_ROMLOC(12794) : tst_mem_16(A0 + 0x36);          // TST.W	54(A0)
  DEF_ROMLOC(12798) : if (!CCR_EQ) goto rom_127AA;    // BNE.B	$127AA
  DEF_ROMLOC(1279A) : btst_tomem_8(0x3, A0 + 0x22);   // BTST.B	#$03,34(A0)
  DEF_ROMLOC(127A0) : if (CCR_EQ) goto rom_127A8;     // BEQ.B	$127A8
  DEF_ROMLOC(127A2) : move_tomem_16(0x1E, A0 + 0x36); // MOVE.W	#$001E,54(A0)
  DEF_ROMLOC(127A8) : return;                         // RTS
  DEF_ROMLOC(127AA) : sub_tomem_16(0x1, A0 + 0x36);   // SUBQ.W	#$01,54(A0)
  DEF_ROMLOC(127AE) : if (!CCR_EQ) goto rom_127A8;    // BNE.B	$127A8
  DEF_ROMLOC(127B0) : add_tomem_8(0x1, A0 + 0x28);    // ADDQ.B	#$01,40(A0)
  DEF_ROMLOC(127B4) : clr_mem_8(A0 + 0x38);           // CLR.B	56(A0)
  DEF_ROMLOC(127B8) : return;                         // RTS
}
ROMFUNC(rom_127BA) {
  DEF_ROMLOC(127BA) : rom_DC6C();                   // BSR.W	$DC6C
  DEF_ROMLOC(127BE) : add_tomem_16(0x8, A0 + 0x12); // ADDQ.W	#$08,18(A0)
  DEF_ROMLOC(127C2) : rom_15580();                  // BSR.W	$15580
  DEF_ROMLOC(127C6) : tst_reg_16(&D1);              // TST.W	D1
  DEF_ROMLOC(127C8) : if (CCR_PL) goto rom_127DA;   // BPL.W	$127DA
  DEF_ROMLOC(127CC) : add_toreg_16(0x1, &D1);       // ADDQ.W	#$01,D1
  DEF_ROMLOC(127CE) : add_tomem_16(D1, A0 + 0xC);   // ADD.W	D1,12(A0)
  DEF_ROMLOC(127D2) : clr_mem_16(A0 + 0x12);        // CLR.W	18(A0)
  DEF_ROMLOC(127D6) : clr_mem_8(A0 + 0x28);         // CLR.B	40(A0)
  DEF_ROMLOC(127DA) : return;                       // RTS
}
ROMFUNC(rom_127DC) {
  DEF_ROMLOC(127DC) : rom_DC6C();                   // BSR.W	$DC6C
  DEF_ROMLOC(127E0) : sub_tomem_16(0x8, A0 + 0x12); // SUBQ.W	#$08,18(A0)
  DEF_ROMLOC(127E4) : rom_15706();                  // BSR.W	$15706
  DEF_ROMLOC(127E8) : tst_reg_16(&D1);              // TST.W	D1
  DEF_ROMLOC(127EA) : if (CCR_PL) goto rom_127FA;   // BPL.W	$127FA
  DEF_ROMLOC(127EE) : sub_tomem_16(D1, A0 + 0xC);   // SUB.W	D1,12(A0)
  DEF_ROMLOC(127F2) : clr_mem_16(A0 + 0x12);        // CLR.W	18(A0)
  DEF_ROMLOC(127F6) : clr_mem_8(A0 + 0x28);         // CLR.B	40(A0)
  DEF_ROMLOC(127FA) : return;                       // RTS
}
ROMFUNC(rom_127FC) {
  DEF_ROMLOC(127FC) : cmp_tomem_8(0x1, A0 + 0x3F); // CMPI.B	#$01,63(A0)
  DEF_ROMLOC(12802) : if (!CCR_EQ) goto rom_1280C; // BNE.B	$1280C
  DEF_ROMLOC(12804) : add_tomem_8(0x1, A0 + 0x28); // ADDQ.B	#$01,40(A0)
  DEF_ROMLOC(12808) : clr_mem_8(A0 + 0x38);        // CLR.B	56(A0)
  DEF_ROMLOC(1280C) : return;                      // RTS
}
ROMFUNC(rom_1280E) {
  DEF_ROMLOC(1280E)
      : move_toreg_16(read_16(0xFFFFF646), &D0); // MOVE.W	$F646,D0
  DEF_ROMLOC(12812)
      : sub_toreg_16(read_16(A0 + 0xC), &D0);         // SUB.W
                                                      // 12(A0),D0
  DEF_ROMLOC(12816) : if (CCR_EQ) goto rom_12852;     // BEQ.B	$12852
  DEF_ROMLOC(12818) : if (CCR_CC) goto rom_12836;     // BCC.B	$12836
  DEF_ROMLOC(1281A) : cmp_toreg_16(0xFFFFFFFE, &D0);  // CMPI.W	#$FFFE,D0
  DEF_ROMLOC(1281E) : if (CCR_GE) goto rom_12822;     // BGE.B	$12822
  DEF_ROMLOC(12820) : move_toreg_32(0xFFFFFFFE, &D0); // MOVEQ.L	$FE,D0
  DEF_ROMLOC(12822) : add_tomem_16(D0, A0 + 0xC);     // ADD.W	D0,12(A0)
  DEF_ROMLOC(12826) : rom_15706();                    // BSR.W	$15706
  DEF_ROMLOC(1282A) : tst_reg_16(&D1);                // TST.W	D1
  DEF_ROMLOC(1282C) : if (CCR_PL) goto rom_12834;     // BPL.W	$12834
  DEF_ROMLOC(12830) : sub_tomem_16(D1, A0 + 0xC);     // SUB.W	D1,12(A0)
  DEF_ROMLOC(12834) : return;                         // RTS
  DEF_ROMLOC(12836) : cmp_toreg_16(0x2, &D0);         // CMPI.W	#$0002,D0
  DEF_ROMLOC(1283A) : if (CCR_LE) goto rom_1283E;     // BLE.B	$1283E
  DEF_ROMLOC(1283C) : move_toreg_32(0x2, &D0);        // MOVEQ.L	$02,D0
  DEF_ROMLOC(1283E) : add_tomem_16(D0, A0 + 0xC);     // ADD.W	D0,12(A0)
  DEF_ROMLOC(12842) : rom_15580();                    // BSR.W	$15580
  DEF_ROMLOC(12846) : tst_reg_16(&D1);                // TST.W	D1
  DEF_ROMLOC(12848) : if (CCR_PL) goto rom_12852;     // BPL.W	$12852
  DEF_ROMLOC(1284C) : add_toreg_16(0x1, &D1);         // ADDQ.W	#$01,D1
  DEF_ROMLOC(1284E) : add_tomem_16(D1, A0 + 0xC);     // ADD.W	D1,12(A0)
  DEF_ROMLOC(12852) : return;                         // RTS
}
ROMFUNC(rom_12854) {
  DEF_ROMLOC(12854) : tst_mem_8(A0 + 0x38);         // TST.B	56(A0)
  DEF_ROMLOC(12858) : if (CCR_EQ) goto rom_12894;   // BEQ.B	$12894
  DEF_ROMLOC(1285A) : btst_tomem_8(0x3, A0 + 0x22); // BTST.B	#$03,34(A0)
  DEF_ROMLOC(12860) : if (!CCR_EQ) goto rom_1286E;  // BNE.B	$1286E
  DEF_ROMLOC(12862) : tst_mem_8(A0 + 0x3E);         // TST.B	62(A0)
  DEF_ROMLOC(12866) : if (CCR_EQ) goto rom_12894;   // BEQ.B	$12894
  DEF_ROMLOC(12868) : sub_tomem_8(0x4, A0 + 0x3E);  // SUBQ.B	#$04,62(A0)
  goto rom_1287A;                                   // BRA.B	$1287A
  DEF_ROMLOC(1286E) : cmp_tomem_8(0x40, A0 + 0x3E); // CMPI.B	#$40,62(A0)
  DEF_ROMLOC(12874) : if (CCR_EQ) goto rom_12894;   // BEQ.B	$12894
  DEF_ROMLOC(12876) : add_tomem_8(0x4, A0 + 0x3E);  // ADDQ.B	#$04,62(A0)
  DEF_ROMLOC(1287A)
      : move_toreg_8(read_8(A0 + 0x3E), &D0);    // MOVE.B	62(A0),D0
  DEF_ROMLOC(1287E) : rom_29D2();                // JSR	$000029D2
  DEF_ROMLOC(12884) : move_toreg_16(0x400, &D1); // MOVE.W	#$0400,D1
  DEF_ROMLOC(12888) : muls_toreg_16(D1, &D0);    // MULS.W	D1,D0
  DEF_ROMLOC(1288A) : SWAPWORDS(D0);             // SWAP.W	D0
  DEF_ROMLOC(1288C)
      : add_toreg_16(read_16(A0 + 0x30), &D0);     // ADD.W	48(A0),D0
  DEF_ROMLOC(12890) : move_tomem_16(D0, A0 + 0xC); // MOVE.W	D0,12(A0)
  DEF_ROMLOC(12894) : return;                      // RTS
}