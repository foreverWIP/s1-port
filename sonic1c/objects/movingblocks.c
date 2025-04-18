// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

static bool exit_early = false;

ROMFUNC(rom_10484) {
  u8 switchindex = 0;
  exit_early = false;
  DEF_ROMLOC(10484) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(10486) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(1048A)
      : move_toreg_16(read_16(0x10492 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(1048E): goto rom_10492 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(1048E) : switch (switchindex) {
  case 0:
    rom_104A2();
    break;
  case 1:
    rom_10522();
    break;
  case 2:
    rom_10534();
    break;
  }
}
ROMFUNC(rom_104A2) {
  DEF_ROMLOC(104A2) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(104A6)
      : move_tomem_32(0x106D6, A0 + 0x4); // MOVE.L	#$000106D6,4(A0)
  DEF_ROMLOC(104AE)
      : move_tomem_16(0x42B8, A0 + 0x2);            // MOVE.W
                                                    // #$42B8,2(A0)
  DEF_ROMLOC(104B4) : cmp_tomem_8(ZONE_LZ, v_zone); // CMPI.B	#$01,$FE10
  DEF_ROMLOC(104BA) : if (!CCR_EQ) goto rom_104D0;  // BNE.B	$104D0
  DEF_ROMLOC(104BC)
      : move_tomem_32(0x1072C, A0 + 0x4); // MOVE.L	#$0001072C,4(A0)
  DEF_ROMLOC(104C4)
      : move_tomem_16(0x43BC, A0 + 0x2);             // MOVE.W
                                                     // #$43BC,2(A0)
  DEF_ROMLOC(104CA) : move_tomem_8(0x7, A0 + 0x16);  // MOVE.B	#$07,22(A0)
  DEF_ROMLOC(104D0) : cmp_tomem_8(ZONE_SBZ, v_zone); // CMPI.B	#$05,$FE10
  DEF_ROMLOC(104D6) : if (!CCR_EQ) goto rom_104EC;   // BNE.B	$104EC
  DEF_ROMLOC(104D8)
      : move_tomem_16(0x22C0, A0 + 0x2);            // MOVE.W
                                                    // #$22C0,2(A0)
  DEF_ROMLOC(104DE) : cmp_tomem_8(0x28, A0 + 0x28); // CMPI.B	#$28,40(A0)
  DEF_ROMLOC(104E4) : if (CCR_EQ) goto rom_104EC;   // BEQ.B	$104EC
  DEF_ROMLOC(104E6)
      : move_tomem_16(0x4460, A0 + 0x2);           // MOVE.W
                                                   // #$4460,2(A0)
  DEF_ROMLOC(104EC) : move_tomem_8(0x4, A0 + 0x1); // MOVE.B	#$04,1(A0)
  DEF_ROMLOC(104F2) : move_toreg_32(0x0, &D0);     // MOVEQ.L	$00,D0
  DEF_ROMLOC(104F4)
      : move_toreg_8(read_8(A0 + 0x28), &D0);  // MOVE.B	40(A0),D0
  DEF_ROMLOC(104F8) : lsr_toreg_16(0x3, &D0);  // LSR.W	#$03,D0
  DEF_ROMLOC(104FA) : and_toreg_16(0x1E, &D0); // ANDI.W	#$001E,D0
  DEF_ROMLOC(104FE)
      : move_toreg_32(0x10498 + (s16)(D0 & 0xffff),
                      &A2); // LEA.L	-104(PC,D0),A2
  DEF_ROMLOC(10502)
      : move_tomem_8(read_8(A2++), A0 + 0x19); // MOVE.B	(A2)+,25(A0)
  DEF_ROMLOC(10506)
      : move_tomem_8(read_8(A2++), A0 + 0x1A);      // MOVE.B	(A2)+,26(A0)
  DEF_ROMLOC(1050A) : move_tomem_8(0x4, A0 + 0x18); // MOVE.B	#$04,24(A0)
  DEF_ROMLOC(10510)
      : move_tomem_16(read_16(A0 + 0x8), A0 + 0x30); // MOVE.W	8(A0),48(A0)
  DEF_ROMLOC(10516)
      : move_tomem_16(read_16(A0 + 0xC), A0 + 0x32); // MOVE.W	12(A0),50(A0)
  DEF_ROMLOC(1051C) : and_tomem_8(0xF, A0 + 0x28);   // ANDI.B	#$0F,40(A0)
  rom_10522(); // Detected flow into next function
}
ROMFUNC(rom_10522) {
  DEF_ROMLOC(10522) : rom_10572(); // BSR.W	$10572
  if (exit_early)
    return;
  DEF_ROMLOC(10526) : move_toreg_32(0x0, &D1); // MOVEQ.L	$00,D1
  DEF_ROMLOC(10528)
      : move_toreg_8(read_8(A0 + 0x19), &D1); // MOVE.B
                                              // 25(A0),D1
  DEF_ROMLOC(1052C) : rom_7ACA();             // JSR	$00007ACA
  rom_10550();                                // BRA.B	$10550
}
ROMFUNC(rom_10534) {
  DEF_ROMLOC(10534) : move_toreg_32(0x0, &D1); // MOVEQ.L	$00,D1
  DEF_ROMLOC(10536)
      : move_toreg_8(read_8(A0 + 0x19), &D1); // MOVE.B
                                              // 25(A0),D1
  DEF_ROMLOC(1053A) : rom_7C3E();             // JSR	$00007C3E
  DEF_ROMLOC(10540)
      : move_tomem_16(read_16(A0 + 0x8), A7 -= 2); // MOVE.W	8(A0),-(A7)
  DEF_ROMLOC(10544) : rom_10572();                 // BSR.W	$10572
  if (exit_early)
    return;
  DEF_ROMLOC(10548)
      : move_toreg_16(read_16((A7 += 2, A7 - 2)), &D2); // MOVE.W	(A7)+,D2
  DEF_ROMLOC(1054A) : rom_81AC();                       // JSR	$000081AC
  rom_10550(); // Detected flow into next function
}
ROMFUNC(rom_10550) {
  DEF_ROMLOC(10550)
      : move_toreg_16(read_16(A0 + 0x30), &D0);      // MOVE.W	48(A0),D0
  DEF_ROMLOC(10554) : and_toreg_16(0xFFFFFF80, &D0); // ANDI.W	#$FF80,D0
  DEF_ROMLOC(10558)
      : move_toreg_16(read_16(v_screenposx), &D1);   // MOVE.W	$F700,D1
  DEF_ROMLOC(1055C) : sub_toreg_16(0x80, &D1);       // SUBI.W	#$0080,D1
  DEF_ROMLOC(10560) : and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
  DEF_ROMLOC(10564) : sub_toreg_16(D1, &D0);         // SUB.W	D1,D0
  DEF_ROMLOC(10566)
      : cmp_toreg_16(128 + GAME_WIDTH + 192, &D0); // CMPI.W	#$0280,D0
  DEF_ROMLOC(1056A) : if (CCR_HI) {
    rom_DCCE();
    return;
  } // BHI.W	$DCCE
  queue_sprite(); // BRA.W	$DC92
}
ROMFUNC(rom_10572) {
  u8 switchindex = 0;
  DEF_ROMLOC(10572) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(10574)
      : move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B
                                              // 40(A0),D0
  DEF_ROMLOC(10578) : and_toreg_16(0xF, &D0);
  switchindex = D0;                          // ANDI.W	#$000F,D0
  DEF_ROMLOC(1057C) : add_toreg_16(D0, &D0); // ADD.W	D0,D0
  DEF_ROMLOC(1057E)
      : move_toreg_16(read_16(0x10586 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(10582): goto rom_10586 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(10582) : switch (switchindex) {
  case 0:
    rom_1059C();
    break;
  case 1:
    rom_1059E();
    break;
  case 2:
    rom_105BE();
    break;
  case 3:
    rom_105CC();
    break;
  case 4:
    rom_105BE();
    break;
  case 5:
    rom_105EC();
    break;
  case 6:
    rom_1060C();
    break;
  case 7:
    rom_1062E();
    break;
  case 8:
    rom_1065A();
    break;
  case 9:
    rom_105BE();
    break;
  case 10:
    rom_1067A();
    break;
  }
}
ROMFUNC(rom_1059C) {
  DEF_ROMLOC(1059C) : return; // RTS
}
ROMFUNC(rom_1059E) {
  DEF_ROMLOC(1059E)
      : move_toreg_8(read_8(0xFFFFFE6C), &D0);      // MOVE.B	$FE6C,D0
  DEF_ROMLOC(105A2) : move_toreg_16(0x60, &D1);     // MOVE.W	#$0060,D1
  DEF_ROMLOC(105A6) : btst_tomem_8(0x0, A0 + 0x22); // BTST.B	#$00,34(A0)
  DEF_ROMLOC(105AC) : if (CCR_EQ) goto rom_105B2;   // BEQ.B	$105B2
  DEF_ROMLOC(105AE) : neg_reg_16(&D0);              // NEG.W	D0
  DEF_ROMLOC(105B0) : add_toreg_16(D1, &D0);        // ADD.W	D1,D0
  DEF_ROMLOC(105B2)
      : move_toreg_16(read_16(A0 + 0x30), &D1);    // MOVE.W	48(A0),D1
  DEF_ROMLOC(105B6) : sub_toreg_16(D0, &D1);       // SUB.W	D0,D1
  DEF_ROMLOC(105B8) : move_tomem_16(D1, A0 + 0x8); // MOVE.W	D1,8(A0)
  DEF_ROMLOC(105BC) : return;                      // RTS
}
ROMFUNC(rom_105BE) {
  DEF_ROMLOC(105BE) : cmp_tomem_8(0x4, A0 + 0x24); // CMPI.B	#$04,36(A0)
  DEF_ROMLOC(105C4) : if (!CCR_EQ) goto rom_105CA; // BNE.B	$105CA
  DEF_ROMLOC(105C6) : add_tomem_8(0x1, A0 + 0x28); // ADDQ.B	#$01,40(A0)
  DEF_ROMLOC(105CA) : return;                      // RTS
}
ROMFUNC(rom_105CC) {
  DEF_ROMLOC(105CC) : move_toreg_32(0x0, &D3); // MOVEQ.L	$00,D3
  DEF_ROMLOC(105CE)
      : move_toreg_8(read_8(A0 + 0x19), &D3);      // MOVE.B	25(A0),D3
  DEF_ROMLOC(105D2) : rom_15642();                 // BSR.W	$15642
  DEF_ROMLOC(105D6) : tst_reg_16(&D1);             // TST.W	D1
  DEF_ROMLOC(105D8) : if (CCR_MI) goto rom_105E6;  // BMI.B	$105E6
  DEF_ROMLOC(105DA) : add_tomem_16(0x1, A0 + 0x8); // ADDQ.W	#$01,8(A0)
  DEF_ROMLOC(105DE)
      : move_tomem_16(read_16(A0 + 0x8), A0 + 0x30); // MOVE.W	8(A0),48(A0)
  DEF_ROMLOC(105E4) : return;                        // RTS
  DEF_ROMLOC(105E6) : clr_mem_8(A0 + 0x28);          // CLR.B	40(A0)
  DEF_ROMLOC(105EA) : return;                        // RTS
}
ROMFUNC(rom_105EC) {
  DEF_ROMLOC(105EC) : move_toreg_32(0x0, &D3); // MOVEQ.L	$00,D3
  DEF_ROMLOC(105EE)
      : move_toreg_8(read_8(A0 + 0x19), &D3);      // MOVE.B	25(A0),D3
  DEF_ROMLOC(105F2) : rom_15642();                 // BSR.W	$15642
  DEF_ROMLOC(105F6) : tst_reg_16(&D1);             // TST.W	D1
  DEF_ROMLOC(105F8) : if (CCR_MI) goto rom_10606;  // BMI.B	$10606
  DEF_ROMLOC(105FA) : add_tomem_16(0x1, A0 + 0x8); // ADDQ.W	#$01,8(A0)
  DEF_ROMLOC(105FE)
      : move_tomem_16(read_16(A0 + 0x8), A0 + 0x30); // MOVE.W	8(A0),48(A0)
  DEF_ROMLOC(10604) : return;                        // RTS
  DEF_ROMLOC(10606) : add_tomem_8(0x1, A0 + 0x28);   // ADDQ.B	#$01,40(A0)
  DEF_ROMLOC(1060A) : return;                        // RTS
}
ROMFUNC(rom_1060C) {
  DEF_ROMLOC(1060C) : rom_DC6C();                    // BSR.W	$DC6C
  DEF_ROMLOC(10610) : add_tomem_16(0x18, A0 + 0x12); // ADDI.W	#$0018,18(A0)
  DEF_ROMLOC(10616) : rom_15580();                   // BSR.W	$15580
  DEF_ROMLOC(1061A) : tst_reg_16(&D1);               // TST.W	D1
  DEF_ROMLOC(1061C) : if (CCR_PL) goto rom_1062C;    // BPL.W	$1062C
  DEF_ROMLOC(10620) : add_tomem_16(D1, A0 + 0xC);    // ADD.W	D1,12(A0)
  DEF_ROMLOC(10624) : clr_mem_16(A0 + 0x12);         // CLR.W	18(A0)
  DEF_ROMLOC(10628) : clr_mem_8(A0 + 0x28);          // CLR.B	40(A0)
  DEF_ROMLOC(1062C) : return;                        // RTS
}
ROMFUNC(rom_1062E) {
  DEF_ROMLOC(1062E) : tst_mem_8(0xFFFFF7E2);       // TST.B	$F7E2
  DEF_ROMLOC(10632) : if (CCR_EQ) goto rom_10638;  // BEQ.B	$10638
  DEF_ROMLOC(10634) : sub_tomem_8(0x3, A0 + 0x28); // SUBQ.B	#$03,40(A0)
  DEF_ROMLOC(10638) : exit_early = true;           // TODO; // ADDQ.L	#$04,A7
  DEF_ROMLOC(1063A)
      : move_toreg_16(read_16(A0 + 0x30), &D0);      // MOVE.W	48(A0),D0
  DEF_ROMLOC(1063E) : and_toreg_16(0xFFFFFF80, &D0); // ANDI.W	#$FF80,D0
  DEF_ROMLOC(10642)
      : move_toreg_16(read_16(v_screenposx), &D1);   // MOVE.W	$F700,D1
  DEF_ROMLOC(10646) : sub_toreg_16(0x80, &D1);       // SUBI.W	#$0080,D1
  DEF_ROMLOC(1064A) : and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
  DEF_ROMLOC(1064E) : sub_toreg_16(D1, &D0);         // SUB.W	D1,D0
  DEF_ROMLOC(10650)
      : cmp_toreg_16(128 + GAME_WIDTH + 192, &D0); // CMPI.W	#$0280,D0
  DEF_ROMLOC(10654) : if (CCR_HI) {
    rom_DCCE();
    return;
  } // BHI.W	$DCCE
  DEF_ROMLOC(10658) : return; // RTS
}
ROMFUNC(rom_1065A) {
  DEF_ROMLOC(1065A)
      : move_toreg_8(read_8(0xFFFFFE7C), &D0);      // MOVE.B	$FE7C,D0
  DEF_ROMLOC(1065E) : move_toreg_16(0x80, &D1);     // MOVE.W	#$0080,D1
  DEF_ROMLOC(10662) : btst_tomem_8(0x0, A0 + 0x22); // BTST.B	#$00,34(A0)
  DEF_ROMLOC(10668) : if (CCR_EQ) goto rom_1066E;   // BEQ.B	$1066E
  DEF_ROMLOC(1066A) : neg_reg_16(&D0);              // NEG.W	D0
  DEF_ROMLOC(1066C) : add_toreg_16(D1, &D0);        // ADD.W	D1,D0
  DEF_ROMLOC(1066E)
      : move_toreg_16(read_16(A0 + 0x32), &D1);    // MOVE.W	50(A0),D1
  DEF_ROMLOC(10672) : sub_toreg_16(D0, &D1);       // SUB.W	D0,D1
  DEF_ROMLOC(10674) : move_tomem_16(D1, A0 + 0xC); // MOVE.W	D1,12(A0)
  DEF_ROMLOC(10678) : return;                      // RTS
}
ROMFUNC(rom_1067A) {
  DEF_ROMLOC(1067A) : move_toreg_32(0x0, &D3); // MOVEQ.L	$00,D3
  DEF_ROMLOC(1067C)
      : move_toreg_8(read_8(A0 + 0x19), &D3);       // MOVE.B	25(A0),D3
  DEF_ROMLOC(10680) : add_toreg_16(D3, &D3);        // ADD.W	D3,D3
  DEF_ROMLOC(10682) : move_toreg_32(0x8, &D1);      // MOVEQ.L	$08,D1
  DEF_ROMLOC(10684) : btst_tomem_8(0x0, A0 + 0x22); // BTST.B	#$00,34(A0)
  DEF_ROMLOC(1068A) : if (CCR_EQ) goto rom_10690;   // BEQ.B	$10690
  DEF_ROMLOC(1068C) : neg_reg_16(&D1);              // NEG.W	D1
  DEF_ROMLOC(1068E) : neg_reg_16(&D3);              // NEG.W	D3
  DEF_ROMLOC(10690) : tst_mem_16(A0 + 0x36);        // TST.W	54(A0)
  DEF_ROMLOC(10694) : if (!CCR_EQ) goto rom_106BC;  // BNE.B	$106BC
  DEF_ROMLOC(10696) : move_toreg_16(read_16(A0 + 0x8), &D0); // MOVE.W	8(A0),D0
  DEF_ROMLOC(1069A)
      : sub_toreg_16(read_16(A0 + 0x30), &D0);    // SUB.W
                                                  // 48(A0),D0
  DEF_ROMLOC(1069E) : cmp_toreg_16(D3, &D0);      // CMP.W	D3,D0
  DEF_ROMLOC(106A0) : if (CCR_EQ) goto rom_106AE; // BEQ.B	$106AE
  DEF_ROMLOC(106A2) : add_tomem_16(D1, A0 + 0x8); // ADD.W	D1,8(A0)
  DEF_ROMLOC(106A6)
      : move_tomem_16(0x12C, A0 + 0x34);            // MOVE.W
                                                    // #$012C,52(A0)
  DEF_ROMLOC(106AC) : return;                       // RTS
  DEF_ROMLOC(106AE) : sub_tomem_16(0x1, A0 + 0x34); // SUBQ.W	#$01,52(A0)
  DEF_ROMLOC(106B2) : if (!CCR_EQ) goto rom_106BA;  // BNE.B	$106BA
  DEF_ROMLOC(106B4)
      : move_tomem_16(0x1, A0 + 0x36); // MOVE.W	#$0001,54(A0)
  DEF_ROMLOC(106BA) : return;          // RTS
  DEF_ROMLOC(106BC)
      : move_toreg_16(read_16(A0 + 0x8), &D0); // MOVE.W	8(A0),D0
  DEF_ROMLOC(106C0)
      : sub_toreg_16(read_16(A0 + 0x30), &D0);     // SUB.W	48(A0),D0
  DEF_ROMLOC(106C4) : if (CCR_EQ) goto rom_106CC;  // BEQ.B	$106CC
  DEF_ROMLOC(106C6) : sub_tomem_16(D1, A0 + 0x8);  // SUB.W	D1,8(A0)
  DEF_ROMLOC(106CA) : return;                      // RTS
  DEF_ROMLOC(106CC) : clr_mem_16(A0 + 0x36);       // CLR.W	54(A0)
  DEF_ROMLOC(106D0) : sub_tomem_8(0x1, A0 + 0x28); // SUBQ.B	#$01,40(A0)
  DEF_ROMLOC(106D4) : return;                      // RTS
}