// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_11564) {
  u8 switchindex = 0;
  DEF_ROMLOC(11564) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(11566) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(1156A)
      : move_toreg_16(read_16(0x11594 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	40(PC,D0),D1
  // DEF_ROMLOC(1156E): rom_11594 + (s16)(D1 & 0xffff)(); // JSR
  // 36(PC,D1)
  DEF_ROMLOC(1156E) : switch (switchindex) {
  case 0:
    rom_1159A();
    break;
  case 1:
    rom_1161A();
    break;
  case 2:
    rom_1162E();
    break;
  }
  DEF_ROMLOC(11572)
      : move_toreg_16(read_16(A0 + 0x30), &D0);      // MOVE.W	48(A0),D0
  DEF_ROMLOC(11576) : and_toreg_16(0xFFFFFF80, &D0); // ANDI.W	#$FF80,D0
  DEF_ROMLOC(1157A)
      : move_toreg_16(read_16(v_screenposx), &D1);   // MOVE.W	$F700,D1
  DEF_ROMLOC(1157E) : sub_toreg_16(0x80, &D1);       // SUBI.W	#$0080,D1
  DEF_ROMLOC(11582) : and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
  DEF_ROMLOC(11586) : sub_toreg_16(D1, &D0);         // SUB.W	D1,D0
  DEF_ROMLOC(11588)
      : cmp_toreg_16(128 + GAME_WIDTH + 192, &D0); // CMPI.W	#$0280,D0
  DEF_ROMLOC(1158C) : if (CCR_HI) {
    rom_DCCE();
    return;
  } // BHI.W	$DCCE
  DEF_ROMLOC(11590) : rom_DC92();
  return; // BRA.W	$DC92
}
ROMFUNC(rom_1159A) {
  DEF_ROMLOC(1159A) : add_tomem_8(0x2, A0 + 0x24);    // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(1159E) : move_toreg_32(0x38, &D3);       // MOVEQ.L	$38,D3
  DEF_ROMLOC(115A0) : move_toreg_32(0x1, &D4);        // MOVEQ.L	$01,D4
  DEF_ROMLOC(115A2) : btst_tomem_8(0x0, A0 + 0x22);   // BTST.B	#$00,34(A0)
  DEF_ROMLOC(115A8) : if (CCR_EQ) goto rom_115AE;     // BEQ.B	$115AE
  DEF_ROMLOC(115AA) : move_toreg_32(0x3B, &D3);       // MOVEQ.L	$3B,D3
  DEF_ROMLOC(115AC) : move_toreg_32(0xFFFFFFFF, &D4); // MOVEQ.L	$FF,D4
  DEF_ROMLOC(115AE)
      : move_toreg_16(read_16(A0 + 0x8), &D2); // MOVE.W	8(A0),D2
  DEF_ROMLOC(115B2) : move_toreg_32(A0, &A1);  // MOVEA.L	A0,A1
  DEF_ROMLOC(115B4) : move_toreg_32(0x3, &D1); // MOVEQ.L	$03,D1
  DEF_ROMLOC(115B6) : goto rom_115C6;          // BRA.B	$115C6
  DEF_ROMLOC(115B8) : rom_E130();              // BSR.W	$E130
  DEF_ROMLOC(115BC) : if (!CCR_EQ) {
    rom_1161A();
    return;
  } // BNE.W	$1161A
  DEF_ROMLOC(115C0) : move_tomem_8(0x4, A1 + 0x24); // MOVE.B	#$04,36(A1)
  DEF_ROMLOC(115C6)
      : move_tomem_8(OBJ_STAIRCASE,
                     A1 + offsetof(object, id)); // MOVE.B	#$5B,0(A1)
  DEF_ROMLOC(115CC)
      : move_tomem_32(0x11710, A1 + 0x4); // MOVE.L	#$00011710,4(A1)
  DEF_ROMLOC(115D4)
      : move_tomem_16(0x4000, A1 + 0x2);            // MOVE.W
                                                    // #$4000,2(A1)
  DEF_ROMLOC(115DA) : move_tomem_8(0x4, A1 + 0x1);  // MOVE.B	#$04,1(A1)
  DEF_ROMLOC(115E0) : move_tomem_8(0x3, A1 + 0x18); // MOVE.B	#$03,24(A1)
  DEF_ROMLOC(115E6)
      : move_tomem_8(0x10, A1 + 0x19); // MOVE.B	#$10,25(A1)
  DEF_ROMLOC(115EC)
      : move_tomem_8(read_8(A0 + 0x28), A1 + 0x28); // MOVE.B	40(A0),40(A1)
  DEF_ROMLOC(115F2) : move_tomem_16(D2, A1 + 0x8);  // MOVE.W	D2,8(A1)
  DEF_ROMLOC(115F6)
      : move_tomem_16(read_16(A0 + 0xC), A1 + 0xC); // MOVE.W	12(A0),12(A1)
  DEF_ROMLOC(115FC)
      : move_tomem_16(read_16(A0 + 0x8), A1 + 0x30); // MOVE.W	8(A0),48(A1)
  DEF_ROMLOC(11602)
      : move_tomem_16(read_16(A1 + 0xC), A1 + 0x32); // MOVE.W	12(A1),50(A1)
  DEF_ROMLOC(11608) : add_toreg_16(0x20, &D2);       // ADDI.W	#$0020,D2
  DEF_ROMLOC(1160C) : move_tomem_8(D3, A1 + 0x37);   // MOVE.B	D3,55(A1)
  DEF_ROMLOC(11610) : move_tomem_32(A0, A1 + 0x3C);  // MOVE.L	A0,60(A1)
  DEF_ROMLOC(11614) : add_toreg_8(D4, &D3);          // ADD.B	D4,D3
  DEF_ROMLOC(11616) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_115B8; // DBF.W	D1,$115B8
  rom_1161A();      // Detected flow into next function
}
ROMFUNC(rom_1161A) {
  u8 switchindex = 0;
  DEF_ROMLOC(1161A) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(1161C)
      : move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B
                                              // 40(A0),D0
  DEF_ROMLOC(11620) : and_toreg_16(0x7, &D0);
  switchindex = D0;                          // ANDI.W	#$0007,D0
  DEF_ROMLOC(11624) : add_toreg_16(D0, &D0); // ADD.W	D0,D0
  DEF_ROMLOC(11626)
      : move_toreg_16(read_16(0x11676 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	78(PC,D0),D1
  // DEF_ROMLOC(1162A): rom_11676 + (s16)(D1 & 0xffff)(); // JSR
  // 74(PC,D1)
  DEF_ROMLOC(1162A) : switch (switchindex) {
  case 0:
    rom_1167E();
    break;
  case 1:
    rom_116E4();
    break;
  case 2:
    rom_116A0();
    break;
  case 3:
    rom_116E4();
    break;
  }
  rom_1162E(); // Detected flow into next function
}
ROMFUNC(rom_1162E) {
  DEF_ROMLOC(1162E)
      : move_toreg_32(read_32(A0 + 0x3C), &A2); // MOVEA.L	60(A0),A2
  DEF_ROMLOC(11632) : move_toreg_32(0x0, &D0);  // MOVEQ.L	$00,D0
  DEF_ROMLOC(11634)
      : move_toreg_8(read_8(A0 + 0x37), &D0); // MOVE.B
                                              // 55(A0),D0
  DEF_ROMLOC(11638)
      : move_toreg_8(read_8((s32)A2 + (s8)0x0 + (s16)D0),
                     &D0); // MOVE.B	0(A2,D0),D0
  DEF_ROMLOC(1163C)
      : add_toreg_16(read_16(A0 + 0x32), &D0);     // ADD.W	50(A0),D0
  DEF_ROMLOC(11640) : move_tomem_16(D0, A0 + 0xC); // MOVE.W	D0,12(A0)
  DEF_ROMLOC(11644) : move_toreg_32(0x0, &D1);     // MOVEQ.L	$00,D1
  DEF_ROMLOC(11646)
      : move_toreg_8(read_8(A0 + 0x19), &D1);   // MOVE.B	25(A0),D1
  DEF_ROMLOC(1164A) : add_toreg_16(0xB, &D1);   // ADDI.W	#$000B,D1
  DEF_ROMLOC(1164E) : move_toreg_16(0x10, &D2); // MOVE.W	#$0010,D2
  DEF_ROMLOC(11652) : move_toreg_16(0x11, &D3); // MOVE.W	#$0011,D3
  DEF_ROMLOC(11656)
      : move_toreg_16(read_16(A0 + 0x8), &D4);      // MOVE.W	8(A0),D4
  DEF_ROMLOC(1165A) : rom_10062();                  // BSR.W	$10062
  DEF_ROMLOC(1165E) : tst_reg_8(&D4);               // TST.B	D4
  DEF_ROMLOC(11660) : if (CCR_PL) goto rom_11666;   // BPL.B	$11666
  DEF_ROMLOC(11662) : move_tomem_8(D4, A2 + 0x36);  // MOVE.B	D4,54(A2)
  DEF_ROMLOC(11666) : btst_tomem_8(0x3, A0 + 0x22); // BTST.B	#$03,34(A0)
  DEF_ROMLOC(1166C) : if (CCR_EQ) goto rom_11674;   // BEQ.B	$11674
  DEF_ROMLOC(1166E) : move_tomem_8(0x1, A2 + 0x36); // MOVE.B	#$01,54(A2)
  DEF_ROMLOC(11674) : return;                       // RTS
}
ROMFUNC(rom_1167E) {
  DEF_ROMLOC(1167E) : tst_mem_16(A0 + 0x34);          // TST.W	52(A0)
  DEF_ROMLOC(11682) : if (!CCR_EQ) goto rom_11694;    // BNE.B	$11694
  DEF_ROMLOC(11684) : cmp_tomem_8(0x1, A0 + 0x36);    // CMPI.B	#$01,54(A0)
  DEF_ROMLOC(1168A) : if (!CCR_EQ) goto rom_11692;    // BNE.B	$11692
  DEF_ROMLOC(1168C) : move_tomem_16(0x1E, A0 + 0x34); // MOVE.W	#$001E,52(A0)
  DEF_ROMLOC(11692) : return;                         // RTS
  DEF_ROMLOC(11694) : sub_tomem_16(0x1, A0 + 0x34);   // SUBQ.W	#$01,52(A0)
  DEF_ROMLOC(11698) : if (!CCR_EQ) goto rom_11692;    // BNE.B	$11692
  DEF_ROMLOC(1169A) : add_tomem_8(0x1, A0 + 0x28);    // ADDQ.B	#$01,40(A0)
  DEF_ROMLOC(1169E) : return;                         // RTS
}
ROMFUNC(rom_116A0) {
  DEF_ROMLOC(116A0) : tst_mem_16(A0 + 0x34);          // TST.W	52(A0)
  DEF_ROMLOC(116A4) : if (!CCR_EQ) goto rom_116B4;    // BNE.B	$116B4
  DEF_ROMLOC(116A6) : tst_mem_8(A0 + 0x36);           // TST.B	54(A0)
  DEF_ROMLOC(116AA) : if (CCR_PL) goto rom_116B2;     // BPL.B	$116B2
  DEF_ROMLOC(116AC) : move_tomem_16(0x3C, A0 + 0x34); // MOVE.W	#$003C,52(A0)
  DEF_ROMLOC(116B2) : return;                         // RTS
  DEF_ROMLOC(116B4) : sub_tomem_16(0x1, A0 + 0x34);   // SUBQ.W	#$01,52(A0)
  DEF_ROMLOC(116B8) : if (!CCR_EQ) goto rom_116C0;    // BNE.B	$116C0
  DEF_ROMLOC(116BA) : add_tomem_8(0x1, A0 + 0x28);    // ADDQ.B	#$01,40(A0)
  DEF_ROMLOC(116BE) : return;                         // RTS
  DEF_ROMLOC(116C0) : move_toreg_32(A0 + 0x38, &A1);  // LEA.L	56(A0),A1
  DEF_ROMLOC(116C4)
      : move_toreg_16(read_16(A0 + 0x34), &D0); // MOVE.W	52(A0),D0
  DEF_ROMLOC(116C8) : lsr_toreg_8(0x2, &D0);    // LSR.B	#$02,D0
  DEF_ROMLOC(116CA) : and_toreg_8(0x1, &D0);    // ANDI.B	#$01,D0
  DEF_ROMLOC(116CE) : move_tomem_8(D0, A1++);   // MOVE.B	D0,(A1)+
  DEF_ROMLOC(116D0) : eor_toreg_8(0x1, &D0);    // EORI.B	#$01,D0
  DEF_ROMLOC(116D4) : move_tomem_8(D0, A1++);   // MOVE.B	D0,(A1)+
  DEF_ROMLOC(116D6) : eor_toreg_8(0x1, &D0);    // EORI.B	#$01,D0
  DEF_ROMLOC(116DA) : move_tomem_8(D0, A1++);   // MOVE.B	D0,(A1)+
  DEF_ROMLOC(116DC) : eor_toreg_8(0x1, &D0);    // EORI.B	#$01,D0
  DEF_ROMLOC(116E0) : move_tomem_8(D0, A1++);   // MOVE.B	D0,(A1)+
  DEF_ROMLOC(116E2) : return;                   // RTS
}
ROMFUNC(rom_116E4) {
  DEF_ROMLOC(116E4) : move_toreg_32(A0 + 0x38, &A1);   // LEA.L	56(A0),A1
  DEF_ROMLOC(116E8) : cmp_tomem_8(0xFFFFFF80, A1);     // CMPI.B	#$80,(A1)
  DEF_ROMLOC(116EC) : if (CCR_EQ) goto rom_1170C;      // BEQ.B	$1170C
  DEF_ROMLOC(116EE) : add_tomem_8(0x1, A1);            // ADDQ.B	#$01,(A1)
  DEF_ROMLOC(116F0) : move_toreg_32(0x0, &D1);         // MOVEQ.L	$00,D1
  DEF_ROMLOC(116F2) : move_toreg_8(read_8(A1++), &D1); // MOVE.B	(A1)+,D1
  DEF_ROMLOC(116F4) : SWAPWORDS(D1);                   // SWAP.W	D1
  DEF_ROMLOC(116F6) : lsr_toreg_32(0x1, &D1);          // LSR.L	#$01,D1
  DEF_ROMLOC(116F8) : move_toreg_32(D1, &D2);          // MOVE.L	D1,D2
  DEF_ROMLOC(116FA) : lsr_toreg_32(0x1, &D1);          // LSR.L	#$01,D1
  DEF_ROMLOC(116FC) : move_toreg_32(D1, &D3);          // MOVE.L	D1,D3
  DEF_ROMLOC(116FE) : add_toreg_32(D2, &D3);           // ADD.L	D2,D3
  DEF_ROMLOC(11700) : SWAPWORDS(D1);                   // SWAP.W	D1
  DEF_ROMLOC(11702) : SWAPWORDS(D2);                   // SWAP.W	D2
  DEF_ROMLOC(11704) : SWAPWORDS(D3);                   // SWAP.W	D3
  DEF_ROMLOC(11706) : move_tomem_8(D3, A1++);          // MOVE.B	D3,(A1)+
  DEF_ROMLOC(11708) : move_tomem_8(D2, A1++);          // MOVE.B	D2,(A1)+
  DEF_ROMLOC(1170A) : move_tomem_8(D1, A1++);          // MOVE.B	D1,(A1)+
  DEF_ROMLOC(1170C) : return;                          // RTS
  DEF_ROMLOC(1170E) : return;                          // RTS
  DEF_ROMLOC(11710) : or_toreg_8(0xFFFFFFF0, &D2);     // ORI.B	#$F0,D2
  DEF_ROMLOC(11714) : btst_toreg_32(D7, &D0);          // BTST.L	D7,D0
  DEF_ROMLOC(11716)
      : move_tomem_32(read_32((s32)A0 + (s8)0x0 + (s16)D7),
                      0x1028);                     // MOVE.L	0(A0,D7),$1028
  DEF_ROMLOC(1171C) : or_tomem_8(0x3B, --A4);      // ORI.B	#$3B,-(A4)
  DEF_ROMLOC(11720) : or_toreg_8(0xFFFFFFFB, &D6); // ORI.B	#$FB,D6
  DEF_ROMLOC(11724) : move_toreg_8(D2, &D0);       // MOVE.B	D2,D0
  DEF_ROMLOC(11726) : or_toreg_8(0x1C, &D4);       // ORI.B	#$1C,D4
  DEF_ROMLOC(1172A) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(1172E)
      : move_tomem_32(0x1176A, A0 + 0x4); // MOVE.L	#$0001176A,4(A0)
  DEF_ROMLOC(11736)
      : move_tomem_16(0xFFFF83CC, A0 + 0x2);         // MOVE.W	#$83CC,2(A0)
  DEF_ROMLOC(1173C) : move_tomem_8(0x10, A0 + 0x19); // MOVE.B	#$10,25(A0)
  DEF_ROMLOC(11742)
      : move_toreg_32(read_32(v_screenposx), &D1); // MOVE.L	$F700,D1
  DEF_ROMLOC(11746) : add_toreg_32(D1, &D1);       // ADD.L	D1,D1
  DEF_ROMLOC(11748) : SWAPWORDS(D1);               // SWAP.W	D1
  DEF_ROMLOC(1174A) : neg_reg_16(&D1);             // NEG.W	D1
  DEF_ROMLOC(1174C) : move_tomem_16(D1, A0 + 0x8); // MOVE.W	D1,8(A0)
  DEF_ROMLOC(11750)
      : move_toreg_32(read_32(0xFFFFF704), &D1);   // MOVE.L	$F704,D1
  DEF_ROMLOC(11754) : add_toreg_32(D1, &D1);       // ADD.L	D1,D1
  DEF_ROMLOC(11756) : SWAPWORDS(D1);               // SWAP.W	D1
  DEF_ROMLOC(11758) : and_toreg_16(0x3F, &D1);     // ANDI.W	#$003F,D1
  DEF_ROMLOC(1175C) : neg_reg_16(&D1);             // NEG.W	D1
  DEF_ROMLOC(1175E) : add_toreg_16(0x100, &D1);    // ADDI.W	#$0100,D1
  DEF_ROMLOC(11762) : move_tomem_16(D1, A0 + 0xA); // MOVE.W	D1,10(A0)
  DEF_ROMLOC(11766) : rom_DC92();
  return; // BRA.W	$DC92
}