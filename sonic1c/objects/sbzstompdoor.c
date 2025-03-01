// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_1637A) {
  u8 switchindex = 0;
  DEF_ROMLOC(1637A) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(1637C) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(16380)
      : move_toreg_16(read_16(0x16388 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(16384): goto rom_16388 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(16384) : switch (switchindex) {
  case 0:
    rom_163A0();
    break;
  case 1:
    rom_16472();
    break;
  }
}
ROMFUNC(rom_163A0) {
  DEF_ROMLOC(163A0) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(163A4) : move_toreg_32(0x0, &D0);     // MOVEQ.L	$00,D0
  DEF_ROMLOC(163A6)
      : move_toreg_8(read_8(A0 + 0x28), &D0);  // MOVE.B	40(A0),D0
  DEF_ROMLOC(163AA) : lsr_toreg_16(0x2, &D0);  // LSR.W	#$02,D0
  DEF_ROMLOC(163AC) : and_toreg_16(0x1C, &D0); // ANDI.W	#$001C,D0
  DEF_ROMLOC(163B0)
      : move_toreg_32(0x1638C + (s16)(D0 & 0xffff),
                      &A3); // LEA.L	-38(PC,D0),A3
  DEF_ROMLOC(163B4)
      : move_tomem_8(read_8(A3++), A0 + 0x19); // MOVE.B	(A3)+,25(A0)
  DEF_ROMLOC(163B8)
      : move_tomem_8(read_8(A3++), A0 + 0x16);     // MOVE.B	(A3)+,22(A0)
  DEF_ROMLOC(163BC) : lsr_toreg_16(0x2, &D0);      // LSR.W	#$02,D0
  DEF_ROMLOC(163BE) : move_tomem_8(D0, A0 + 0x1A); // MOVE.B	D0,26(A0)
  DEF_ROMLOC(163C2)
      : move_tomem_32(0x166D0, A0 + 0x4); // MOVE.L	#$000166D0,4(A0)
  DEF_ROMLOC(163CA)
      : move_tomem_16(0x22C0, A0 + 0x2);              // MOVE.W
                                                      // #$22C0,2(A0)
  DEF_ROMLOC(163D0) : cmp_tomem_8(ZONE_LZ, v_zone);   // CMPI.B	#$01,$FE10
  DEF_ROMLOC(163D6) : if (!CCR_EQ) goto rom_16420;    // BNE.B	$16420
  DEF_ROMLOC(163D8) : bset_tomem_8(0x0, 0xFFFFF7CB);  // BSET.B	#$00,$F7CB
  DEF_ROMLOC(163DE) : if (CCR_EQ) goto rom_163F8;     // BEQ.B	$163F8
  DEF_ROMLOC(163E0) : move_toreg_32(0xFFFFFC00, &A2); // LEA.L	$FC00,A2
  DEF_ROMLOC(163E4) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(163E6)
      : move_toreg_8(read_8(A0 + 0x23), &D0);     // MOVE.B	35(A0),D0
  DEF_ROMLOC(163EA) : if (CCR_EQ) goto rom_163F2; // BEQ.B	$163F2
  DEF_ROMLOC(163EC)
      : bclr_tomem_8(0x7,
                     (s32)A2 + (s8)0x2 + (s16)D0); // BCLR.B	#$07,2(A2,D0)
  DEF_ROMLOC(163F2) : rom_DCCE();
  return; // JMP	$0000DCCE
  DEF_ROMLOC(163F8)
      : move_tomem_16(0x41F0, A0 + 0x2);              // MOVE.W
                                                      // #$41F0,2(A0)
  DEF_ROMLOC(163FE) : cmp_tomem_16(0xA80, A0 + 0x8);  // CMPI.W	#$0A80,8(A0)
  DEF_ROMLOC(16404) : if (!CCR_EQ) goto rom_16420;    // BNE.B	$16420
  DEF_ROMLOC(16406) : move_toreg_32(0xFFFFFC00, &A2); // LEA.L	$FC00,A2
  DEF_ROMLOC(1640A) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(1640C)
      : move_toreg_8(read_8(A0 + 0x23), &D0);     // MOVE.B	35(A0),D0
  DEF_ROMLOC(16410) : if (CCR_EQ) goto rom_16420; // BEQ.B	$16420
  DEF_ROMLOC(16412)
      : btst_tomem_8(0x0,
                     (s32)A2 + (s8)0x2 + (s16)D0);  // BTST.B	#$00,2(A2,D0)
  DEF_ROMLOC(16418) : if (CCR_EQ) goto rom_16420;   // BEQ.B	$16420
  DEF_ROMLOC(1641A) : clr_mem_8(0xFFFFF7CB);        // CLR.B	$F7CB
  DEF_ROMLOC(1641E) : goto rom_163E0;               // BRA.B	$163E0
  DEF_ROMLOC(16420) : or_tomem_8(0x4, A0 + 0x1);    // ORI.B	#$04,1(A0)
  DEF_ROMLOC(16426) : move_tomem_8(0x4, A0 + 0x18); // MOVE.B	#$04,24(A0)
  DEF_ROMLOC(1642C)
      : move_tomem_16(read_16(A0 + 0x8), A0 + 0x34); // MOVE.W	8(A0),52(A0)
  DEF_ROMLOC(16432)
      : move_tomem_16(read_16(A0 + 0xC), A0 + 0x30);   // MOVE.W	12(A0),48(A0)
  DEF_ROMLOC(16438) : move_toreg_32(0x0, &D0);         // MOVEQ.L	$00,D0
  DEF_ROMLOC(1643A) : move_toreg_8(read_8(A3++), &D0); // MOVE.B	(A3)+,D0
  DEF_ROMLOC(1643C) : move_tomem_16(D0, A0 + 0x3C);    // MOVE.W	D0,60(A0)
  DEF_ROMLOC(16440) : move_toreg_32(0x0, &D0);         // MOVEQ.L	$00,D0
  DEF_ROMLOC(16442)
      : move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B
                                              // 40(A0),D0
  DEF_ROMLOC(16446) : if (CCR_PL) {
    rom_16472();
    return;
  } // BPL.B	$16472
  DEF_ROMLOC(16448) : and_toreg_8(0xF, &D0);       // ANDI.B	#$0F,D0
  DEF_ROMLOC(1644C) : move_tomem_8(D0, A0 + 0x3E); // MOVE.B	D0,62(A0)
  DEF_ROMLOC(16450)
      : move_tomem_8(read_8(A3), A0 + 0x28);          // MOVE.B
                                                      // (A3),40(A0)
  DEF_ROMLOC(16454) : cmp_tomem_8(0x5, A3);           // CMPI.B	#$05,(A3)
  DEF_ROMLOC(16458) : if (!CCR_EQ) goto rom_16460;    // BNE.B	$16460
  DEF_ROMLOC(1645A) : bset_tomem_8(0x4, A0 + 0x1);    // BSET.B	#$04,1(A0)
  DEF_ROMLOC(16460) : move_toreg_32(0xFFFFFC00, &A2); // LEA.L	$FC00,A2
  DEF_ROMLOC(16464) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(16466)
      : move_toreg_8(read_8(A0 + 0x23), &D0); // MOVE.B
                                              // 35(A0),D0
  DEF_ROMLOC(1646A) : if (CCR_EQ) {
    rom_16472();
    return;
  } // BEQ.B	$16472
  DEF_ROMLOC(1646C)
      : bclr_tomem_8(0x7,
                     (s32)A2 + (s8)0x2 + (s16)D0); // BCLR.B	#$07,2(A2,D0)
  rom_16472(); // Detected flow into next function
}
ROMFUNC(rom_164FC);
ROMFUNC(rom_164FE);
ROMFUNC(rom_1656A);
ROMFUNC(rom_165C0);
ROMFUNC(rom_16614);
ROMFUNC(rom_16676);
ROMFUNC(rom_16472) {
  u8 switchindex = 0;
  DEF_ROMLOC(16472)
      : move_tomem_16(read_16(A0 + 0x8), A7 -= 2); // MOVE.W	8(A0),-(A7)
  DEF_ROMLOC(16476) : move_toreg_32(0x0, &D0);     // MOVEQ.L	$00,D0
  DEF_ROMLOC(16478)
      : move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B
                                              // 40(A0),D0
  DEF_ROMLOC(1647C) : and_toreg_16(0xF, &D0);
  switchindex = D0;                          // ANDI.W	#$000F,D0
  DEF_ROMLOC(16480) : add_toreg_16(D0, &D0); // ADD.W	D0,D0
  DEF_ROMLOC(16482)
      : move_toreg_16(read_16(0x164F0 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	108(PC,D0),D1
  // DEF_ROMLOC(16486): rom_164F0 + (s16)(D1 & 0xffff)(); // JSR
  // 104(PC,D1)
  DEF_ROMLOC(16486) : switch (switchindex) {
  case 0:
    rom_164FC();
    break;
  case 1:
    rom_164FE();
    break;
  case 2:
    rom_1656A();
    break;
  case 3:
    rom_165C0();
    break;
  case 4:
    rom_16614();
    break;
  case 5:
    rom_16676();
    break;
  }
  DEF_ROMLOC(1648A)
      : move_toreg_16(read_16((A7 += 2, A7 - 2)), &D4); // MOVE.W	(A7)+,D4
  DEF_ROMLOC(1648C) : tst_mem_8(A0 + 0x1);              // TST.B	1(A0)
  DEF_ROMLOC(16490) : if (CCR_PL) goto rom_164AA;       // BPL.B	$164AA
  DEF_ROMLOC(16492) : move_toreg_32(0x0, &D1);          // MOVEQ.L	$00,D1
  DEF_ROMLOC(16494)
      : move_toreg_8(read_8(A0 + 0x19), &D1);  // MOVE.B	25(A0),D1
  DEF_ROMLOC(16498) : add_toreg_16(0xB, &D1);  // ADDI.W	#$000B,D1
  DEF_ROMLOC(1649C) : move_toreg_32(0x0, &D2); // MOVEQ.L	$00,D2
  DEF_ROMLOC(1649E)
      : move_toreg_8(read_8(A0 + 0x16), &D2); // MOVE.B
                                              // 22(A0),D2
  DEF_ROMLOC(164A2) : move_toreg_16(D2, &D3); // MOVE.W	D2,D3
  DEF_ROMLOC(164A4) : add_toreg_16(0x1, &D3); // ADDQ.W	#$01,D3
  DEF_ROMLOC(164A6) : rom_10062();            // BSR.W	$10062
  DEF_ROMLOC(164AA)
      : move_toreg_16(read_16(A0 + 0x34), &D0);      // MOVE.W	52(A0),D0
  DEF_ROMLOC(164AE) : and_toreg_16(0xFFFFFF80, &D0); // ANDI.W	#$FF80,D0
  DEF_ROMLOC(164B2)
      : move_toreg_16(read_16(v_screenposx), &D1);   // MOVE.W	$F700,D1
  DEF_ROMLOC(164B6) : sub_toreg_16(0x80, &D1);       // SUBI.W	#$0080,D1
  DEF_ROMLOC(164BA) : and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
  DEF_ROMLOC(164BE) : sub_toreg_16(D1, &D0);         // SUB.W	D1,D0
  DEF_ROMLOC(164C0)
      : cmp_toreg_16(128 + GAME_WIDTH + 192, &D0); // CMPI.W	#$0280,D0
  DEF_ROMLOC(164C4) : if (CCR_HI) goto rom_164CC;  // BHI.B	$164CC
  DEF_ROMLOC(164C6) : rom_DC92();
  return;                                             // JMP	$0000DC92
  DEF_ROMLOC(164CC) : cmp_tomem_8(ZONE_LZ, v_zone);   // CMPI.B	#$01,$FE10
  DEF_ROMLOC(164D2) : if (!CCR_EQ) goto rom_164EA;    // BNE.B	$164EA
  DEF_ROMLOC(164D4) : clr_mem_8(0xFFFFF7CB);          // CLR.B	$F7CB
  DEF_ROMLOC(164D8) : move_toreg_32(0xFFFFFC00, &A2); // LEA.L	$FC00,A2
  DEF_ROMLOC(164DC) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(164DE)
      : move_toreg_8(read_8(A0 + 0x23), &D0);     // MOVE.B	35(A0),D0
  DEF_ROMLOC(164E2) : if (CCR_EQ) goto rom_164EA; // BEQ.B	$164EA
  DEF_ROMLOC(164E4)
      : bclr_tomem_8(0x7,
                     (s32)A2 + (s8)0x2 + (s16)D0); // BCLR.B	#$07,2(A2,D0)
  DEF_ROMLOC(164EA) : rom_DCCE();                  // JMP	$0000DCCE
}
ROMFUNC(rom_164FC) {
  DEF_ROMLOC(164FC) : return; // RTS
}
ROMFUNC(rom_164FE) {
  DEF_ROMLOC(164FE) : tst_mem_8(A0 + 0x38);           // TST.B	56(A0)
  DEF_ROMLOC(16502) : if (!CCR_EQ) goto rom_1651C;    // BNE.B	$1651C
  DEF_ROMLOC(16504) : move_toreg_32(0xFFFFF7E0, &A2); // LEA.L	$F7E0,A2
  DEF_ROMLOC(16508) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(1650A)
      : move_toreg_8(read_8(A0 + 0x3E), &D0); // MOVE.B
                                              // 62(A0),D0
  DEF_ROMLOC(1650E)
      : btst_tomem_8(0x0,
                     (s32)A2 + (s8)0x0 + (s16)D0);  // BTST.B	#$00,0(A2,D0)
  DEF_ROMLOC(16514) : if (CCR_EQ) goto rom_1652A;   // BEQ.B	$1652A
  DEF_ROMLOC(16516) : move_tomem_8(0x1, A0 + 0x38); // MOVE.B	#$01,56(A0)
  DEF_ROMLOC(1651C)
      : move_toreg_16(read_16(A0 + 0x3C), &D0); // MOVE.W	60(A0),D0
  DEF_ROMLOC(16520)
      : cmp_toreg_16(read_16(A0 + 0x3A), &D0);      // CMP.W	58(A0),D0
  DEF_ROMLOC(16524) : if (CCR_EQ) goto rom_16548;   // BEQ.B	$16548
  DEF_ROMLOC(16526) : add_tomem_16(0x2, A0 + 0x3A); // ADDQ.W	#$02,58(A0)
  DEF_ROMLOC(1652A)
      : move_toreg_16(read_16(A0 + 0x3A), &D0);     // MOVE.W	58(A0),D0
  DEF_ROMLOC(1652E) : btst_tomem_8(0x0, A0 + 0x22); // BTST.B	#$00,34(A0)
  DEF_ROMLOC(16534) : if (CCR_EQ) goto rom_1653C;   // BEQ.B	$1653C
  DEF_ROMLOC(16536) : neg_reg_16(&D0);              // NEG.W	D0
  DEF_ROMLOC(16538) : add_toreg_16(0x80, &D0);      // ADDI.W	#$0080,D0
  DEF_ROMLOC(1653C)
      : move_toreg_16(read_16(A0 + 0x34), &D1);       // MOVE.W	52(A0),D1
  DEF_ROMLOC(16540) : sub_toreg_16(D0, &D1);          // SUB.W	D0,D1
  DEF_ROMLOC(16542) : move_tomem_16(D1, A0 + 0x8);    // MOVE.W	D1,8(A0)
  DEF_ROMLOC(16546) : return;                         // RTS
  DEF_ROMLOC(16548) : add_tomem_8(0x1, A0 + 0x28);    // ADDQ.B	#$01,40(A0)
  DEF_ROMLOC(1654C) : move_tomem_16(0xB4, A0 + 0x36); // MOVE.W	#$00B4,54(A0)
  DEF_ROMLOC(16552) : clr_mem_8(A0 + 0x38);           // CLR.B	56(A0)
  DEF_ROMLOC(16556) : move_toreg_32(0xFFFFFC00, &A2); // LEA.L	$FC00,A2
  DEF_ROMLOC(1655A) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(1655C)
      : move_toreg_8(read_8(A0 + 0x23), &D0);     // MOVE.B	35(A0),D0
  DEF_ROMLOC(16560) : if (CCR_EQ) goto rom_1652A; // BEQ.B	$1652A
  DEF_ROMLOC(16562)
      : bset_tomem_8(0x0,
                     (s32)A2 + (s8)0x2 + (s16)D0); // BSET.B	#$00,2(A2,D0)
  goto rom_1652A;                                  // BRA.B	$1652A
}
ROMFUNC(rom_1656A) {
  DEF_ROMLOC(1656A) : tst_mem_8(A0 + 0x38);         // TST.B	56(A0)
  DEF_ROMLOC(1656E) : if (!CCR_EQ) goto rom_1657C;  // BNE.B	$1657C
  DEF_ROMLOC(16570) : sub_tomem_16(0x1, A0 + 0x36); // SUBQ.W	#$01,54(A0)
  DEF_ROMLOC(16574) : if (!CCR_EQ) goto rom_16586;  // BNE.B	$16586
  DEF_ROMLOC(16576) : move_tomem_8(0x1, A0 + 0x38); // MOVE.B	#$01,56(A0)
  DEF_ROMLOC(1657C) : tst_mem_16(A0 + 0x3A);        // TST.W	58(A0)
  DEF_ROMLOC(16580) : if (CCR_EQ) goto rom_165A4;   // BEQ.B	$165A4
  DEF_ROMLOC(16582) : sub_tomem_16(0x2, A0 + 0x3A); // SUBQ.W	#$02,58(A0)
  DEF_ROMLOC(16586)
      : move_toreg_16(read_16(A0 + 0x3A), &D0);     // MOVE.W	58(A0),D0
  DEF_ROMLOC(1658A) : btst_tomem_8(0x0, A0 + 0x22); // BTST.B	#$00,34(A0)
  DEF_ROMLOC(16590) : if (CCR_EQ) goto rom_16598;   // BEQ.B	$16598
  DEF_ROMLOC(16592) : neg_reg_16(&D0);              // NEG.W	D0
  DEF_ROMLOC(16594) : add_toreg_16(0x80, &D0);      // ADDI.W	#$0080,D0
  DEF_ROMLOC(16598)
      : move_toreg_16(read_16(A0 + 0x34), &D1);       // MOVE.W	52(A0),D1
  DEF_ROMLOC(1659C) : sub_toreg_16(D0, &D1);          // SUB.W	D0,D1
  DEF_ROMLOC(1659E) : move_tomem_16(D1, A0 + 0x8);    // MOVE.W	D1,8(A0)
  DEF_ROMLOC(165A2) : return;                         // RTS
  DEF_ROMLOC(165A4) : sub_tomem_8(0x1, A0 + 0x28);    // SUBQ.B	#$01,40(A0)
  DEF_ROMLOC(165A8) : clr_mem_8(A0 + 0x38);           // CLR.B	56(A0)
  DEF_ROMLOC(165AC) : move_toreg_32(0xFFFFFC00, &A2); // LEA.L	$FC00,A2
  DEF_ROMLOC(165B0) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(165B2)
      : move_toreg_8(read_8(A0 + 0x23), &D0);     // MOVE.B	35(A0),D0
  DEF_ROMLOC(165B6) : if (CCR_EQ) goto rom_16586; // BEQ.B	$16586
  DEF_ROMLOC(165B8)
      : bclr_tomem_8(0x0,
                     (s32)A2 + (s8)0x2 + (s16)D0); // BCLR.B	#$00,2(A2,D0)
  goto rom_16586;                                  // BRA.B	$16586
}
ROMFUNC(rom_165C0) {
  DEF_ROMLOC(165C0) : tst_mem_8(A0 + 0x38);           // TST.B	56(A0)
  DEF_ROMLOC(165C4) : if (!CCR_EQ) goto rom_165E4;    // BNE.B	$165E4
  DEF_ROMLOC(165C6) : tst_mem_16(A0 + 0x3A);          // TST.W	58(A0)
  DEF_ROMLOC(165CA) : if (CCR_EQ) goto rom_165D2;     // BEQ.B	$165D2
  DEF_ROMLOC(165CC) : sub_tomem_16(0x1, A0 + 0x3A);   // SUBQ.W	#$01,58(A0)
  goto rom_165F6;                                     // BRA.B	$165F6
  DEF_ROMLOC(165D2) : sub_tomem_16(0x1, A0 + 0x36);   // SUBQ.W	#$01,54(A0)
  DEF_ROMLOC(165D6) : if (CCR_PL) goto rom_165F6;     // BPL.B	$165F6
  DEF_ROMLOC(165D8) : move_tomem_16(0x3C, A0 + 0x36); // MOVE.W	#$003C,54(A0)
  DEF_ROMLOC(165DE) : move_tomem_8(0x1, A0 + 0x38);   // MOVE.B	#$01,56(A0)
  DEF_ROMLOC(165E4) : add_tomem_16(0x8, A0 + 0x3A);   // ADDQ.W	#$08,58(A0)
  DEF_ROMLOC(165E8)
      : move_toreg_16(read_16(A0 + 0x3A), &D0); // MOVE.W	58(A0),D0
  DEF_ROMLOC(165EC)
      : cmp_toreg_16(read_16(A0 + 0x3C), &D0);     // CMP.W	60(A0),D0
  DEF_ROMLOC(165F0) : if (!CCR_EQ) goto rom_165F6; // BNE.B	$165F6
  DEF_ROMLOC(165F2) : clr_mem_8(A0 + 0x38);        // CLR.B	56(A0)
  DEF_ROMLOC(165F6)
      : move_toreg_16(read_16(A0 + 0x3A), &D0);     // MOVE.W	58(A0),D0
  DEF_ROMLOC(165FA) : btst_tomem_8(0x0, A0 + 0x22); // BTST.B	#$00,34(A0)
  DEF_ROMLOC(16600) : if (CCR_EQ) goto rom_16608;   // BEQ.B	$16608
  DEF_ROMLOC(16602) : neg_reg_16(&D0);              // NEG.W	D0
  DEF_ROMLOC(16604) : add_toreg_16(0x38, &D0);      // ADDI.W	#$0038,D0
  DEF_ROMLOC(16608)
      : move_toreg_16(read_16(A0 + 0x30), &D1);    // MOVE.W	48(A0),D1
  DEF_ROMLOC(1660C) : add_toreg_16(D0, &D1);       // ADD.W	D0,D1
  DEF_ROMLOC(1660E) : move_tomem_16(D1, A0 + 0xC); // MOVE.W	D1,12(A0)
  DEF_ROMLOC(16612) : return;                      // RTS
}
ROMFUNC(rom_16614) {
  DEF_ROMLOC(16614) : tst_mem_8(A0 + 0x38);           // TST.B	56(A0)
  DEF_ROMLOC(16618) : if (!CCR_EQ) goto rom_16638;    // BNE.B	$16638
  DEF_ROMLOC(1661A) : tst_mem_16(A0 + 0x3A);          // TST.W	58(A0)
  DEF_ROMLOC(1661E) : if (CCR_EQ) goto rom_16626;     // BEQ.B	$16626
  DEF_ROMLOC(16620) : sub_tomem_16(0x8, A0 + 0x3A);   // SUBQ.W	#$08,58(A0)
  goto rom_16658;                                     // BRA.B	$16658
  DEF_ROMLOC(16626) : sub_tomem_16(0x1, A0 + 0x36);   // SUBQ.W	#$01,54(A0)
  DEF_ROMLOC(1662A) : if (CCR_PL) goto rom_16658;     // BPL.B	$16658
  DEF_ROMLOC(1662C) : move_tomem_16(0x3C, A0 + 0x36); // MOVE.W	#$003C,54(A0)
  DEF_ROMLOC(16632) : move_tomem_8(0x1, A0 + 0x38);   // MOVE.B	#$01,56(A0)
  DEF_ROMLOC(16638)
      : move_toreg_16(read_16(A0 + 0x3A), &D0); // MOVE.W	58(A0),D0
  DEF_ROMLOC(1663C)
      : cmp_toreg_16(read_16(A0 + 0x3C), &D0);        // CMP.W
                                                      // 60(A0),D0
  DEF_ROMLOC(16640) : if (CCR_EQ) goto rom_16648;     // BEQ.B	$16648
  DEF_ROMLOC(16642) : add_tomem_16(0x8, A0 + 0x3A);   // ADDQ.W	#$08,58(A0)
  goto rom_16658;                                     // BRA.B	$16658
  DEF_ROMLOC(16648) : sub_tomem_16(0x1, A0 + 0x36);   // SUBQ.W	#$01,54(A0)
  DEF_ROMLOC(1664C) : if (CCR_PL) goto rom_16658;     // BPL.B	$16658
  DEF_ROMLOC(1664E) : move_tomem_16(0x3C, A0 + 0x36); // MOVE.W	#$003C,54(A0)
  DEF_ROMLOC(16654) : clr_mem_8(A0 + 0x38);           // CLR.B	56(A0)
  DEF_ROMLOC(16658)
      : move_toreg_16(read_16(A0 + 0x3A), &D0);     // MOVE.W	58(A0),D0
  DEF_ROMLOC(1665C) : btst_tomem_8(0x0, A0 + 0x22); // BTST.B	#$00,34(A0)
  DEF_ROMLOC(16662) : if (CCR_EQ) goto rom_1666A;   // BEQ.B	$1666A
  DEF_ROMLOC(16664) : neg_reg_16(&D0);              // NEG.W	D0
  DEF_ROMLOC(16666) : add_toreg_16(0x38, &D0);      // ADDI.W	#$0038,D0
  DEF_ROMLOC(1666A)
      : move_toreg_16(read_16(A0 + 0x30), &D1);    // MOVE.W	48(A0),D1
  DEF_ROMLOC(1666E) : add_toreg_16(D0, &D1);       // ADD.W	D0,D1
  DEF_ROMLOC(16670) : move_tomem_16(D1, A0 + 0xC); // MOVE.W	D1,12(A0)
  DEF_ROMLOC(16674) : return;                      // RTS
}
ROMFUNC(rom_16676) {
  DEF_ROMLOC(16676) : tst_mem_8(A0 + 0x38);           // TST.B	56(A0)
  DEF_ROMLOC(1667A) : if (!CCR_EQ) goto rom_166A6;    // BNE.B	$166A6
  DEF_ROMLOC(1667C) : move_toreg_32(0xFFFFF7E0, &A2); // LEA.L	$F7E0,A2
  DEF_ROMLOC(16680) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(16682)
      : move_toreg_8(read_8(A0 + 0x3E), &D0); // MOVE.B
                                              // 62(A0),D0
  DEF_ROMLOC(16686)
      : btst_tomem_8(0x0,
                     (s32)A2 + (s8)0x0 + (s16)D0);    // BTST.B	#$00,0(A2,D0)
  DEF_ROMLOC(1668C) : if (CCR_EQ) goto rom_166C4;     // BEQ.B	$166C4
  DEF_ROMLOC(1668E) : move_tomem_8(0x1, A0 + 0x38);   // MOVE.B	#$01,56(A0)
  DEF_ROMLOC(16694) : move_toreg_32(0xFFFFFC00, &A2); // LEA.L	$FC00,A2
  DEF_ROMLOC(16698) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(1669A)
      : move_toreg_8(read_8(A0 + 0x23), &D0);     // MOVE.B	35(A0),D0
  DEF_ROMLOC(1669E) : if (CCR_EQ) goto rom_166A6; // BEQ.B	$166A6
  DEF_ROMLOC(166A0)
      : bset_tomem_8(0x0,
                     (s32)A2 + (s8)0x2 + (s16)D0); // BSET.B	#$00,2(A2,D0)
  DEF_ROMLOC(166A6)
      : sub_tomem_32(0x10000, A0 + 0x8); // SUBI.L	#$00010000,8(A0)
  DEF_ROMLOC(166AE)
      : add_tomem_32(0x8000, A0 + 0xC); // ADDI.L	#$00008000,12(A0)
  DEF_ROMLOC(166B6)
      : move_tomem_16(read_16(A0 + 0x8), A0 + 0x34); // MOVE.W	8(A0),52(A0)
  DEF_ROMLOC(166BC) : cmp_tomem_16(0x980, A0 + 0x8); // CMPI.W	#$0980,8(A0)
  DEF_ROMLOC(166C2) : if (CCR_EQ) goto rom_166C6;    // BEQ.B	$166C6
  DEF_ROMLOC(166C4) : return;                        // RTS
  DEF_ROMLOC(166C6) : clr_mem_8(A0 + 0x28);          // CLR.B	40(A0)
  DEF_ROMLOC(166CA) : clr_mem_8(A0 + 0x38);          // CLR.B	56(A0)
  DEF_ROMLOC(166CE) : return;                        // RTS
}