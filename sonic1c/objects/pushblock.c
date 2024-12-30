// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"


ROMFUNC(rom_C55C) {
  u8 switchindex = 0;
  DEF_ROMLOC(C55C) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(C55E) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(C562)
      : move_toreg_16(read_16(0xC56A + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(C566): goto rom_C56A + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(C566) : switch (switchindex) {
  case 0:
    rom_C574();
    break;
  case 1:
    rom_C5F8();
    break;
  case 2:
    rom_C6B6();
    break;
  }
}
ROMFUNC(rom_C574) {
  DEF_ROMLOC(C574) : add_tomem_8(0x2, A0 + 0x24);  // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(C578) : move_tomem_8(0xF, A0 + 0x16); // MOVE.B	#$0F,22(A0)
  DEF_ROMLOC(C57E) : move_tomem_8(0xF, A0 + 0x17); // MOVE.B	#$0F,23(A0)
  DEF_ROMLOC(C584)
      : move_tomem_32(0xC970, A0 + 0x4);              // MOVE.L	#$0000C970,4(A0)
  DEF_ROMLOC(C58C) : move_tomem_16(0x42B8, A0 + 0x2); // MOVE.W	#$42B8,2(A0)
  DEF_ROMLOC(C592) : cmp_tomem_8(0x1, 0xFFFFFE10);    // CMPI.B	#$01,$FE10
  DEF_ROMLOC(C598) : if (!CCR_EQ) goto rom_C5A0;      // BNE.B	$C5A0
  DEF_ROMLOC(C59A) : move_tomem_16(0x43DE, A0 + 0x2); // MOVE.W	#$43DE,2(A0)
  DEF_ROMLOC(C5A0) : move_tomem_8(0x4, A0 + 0x1);     // MOVE.B	#$04,1(A0)
  DEF_ROMLOC(C5A6) : move_tomem_8(0x3, A0 + 0x18);    // MOVE.B	#$03,24(A0)
  DEF_ROMLOC(C5AC)
      : move_tomem_16(read_16(A0 + 0x8), A0 + 0x34); // MOVE.W	8(A0),52(A0)
  DEF_ROMLOC(C5B2)
      : move_tomem_16(read_16(A0 + 0xC), A0 + 0x36); // MOVE.W	12(A0),54(A0)
  DEF_ROMLOC(C5B8) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(C5BA)
      : move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B	40(A0),D0
  DEF_ROMLOC(C5BE) : add_toreg_16(D0, &D0);   // ADD.W	D0,D0
  DEF_ROMLOC(C5C0) : and_toreg_16(0xE, &D0);  // ANDI.W	#$000E,D0
  DEF_ROMLOC(C5C4)
      : move_toreg_32(0xC570 + (s16)(D0 & 0xffff),
                      &A2); // LEA.L	-86(PC,D0),A2
  DEF_ROMLOC(C5C8)
      : move_tomem_8(read_8(A2++), A0 + 0x19); // MOVE.B	(A2)+,25(A0)
  DEF_ROMLOC(C5CC)
      : move_tomem_8(read_8(A2++), A0 + 0x1A);  // MOVE.B	(A2)+,26(A0)
  DEF_ROMLOC(C5D0) : tst_mem_8(A0 + 0x28);      // TST.B	40(A0)
  DEF_ROMLOC(C5D4) : if (CCR_EQ) goto rom_C5DC; // BEQ.B	$C5DC
  DEF_ROMLOC(C5D6)
      : move_tomem_16(0xFFFFC2B8, A0 + 0x2);         // MOVE.W	#$C2B8,2(A0)
  DEF_ROMLOC(C5DC) : move_toreg_32(0xFFFFFC00, &A2); // LEA.L	$FC00,A2
  DEF_ROMLOC(C5E0) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(C5E2)
      : move_toreg_8(read_8(A0 + 0x23), &D0); // MOVE.B	35(A0),D0
  DEF_ROMLOC(C5E6) : if (CCR_EQ) {
    rom_C5F8();
    return;
  } // BEQ.B	$C5F8
  DEF_ROMLOC(C5E8)
      : bclr_tomem_8(0x7,
                     (s32)A2 + (s8)0x2 + (s16)D0); // BCLR.B	#$07,2(A2,D0)
  DEF_ROMLOC(C5EE)
      : bset_tomem_8(0x0,
                     (s32)A2 + (s8)0x2 + (s16)D0); // BSET.B	#$00,2(A2,D0)
  DEF_ROMLOC(C5F4) : if (!CCR_EQ) {
    rom_DCCE();
    return;
  }           // BNE.W	$DCCE
  rom_C5F8(); // Detected flow into next function
}
ROMFUNC(rom_C650) {
  DEF_ROMLOC(C650)
      : move_toreg_16(read_16(A0 + 0x8), &D0);      // MOVE.W	8(A0),D0
  DEF_ROMLOC(C654) : and_toreg_16(0xFFFFFF80, &D0); // ANDI.W	#$FF80,D0
  DEF_ROMLOC(C658)
      : move_toreg_16(read_16(0xFFFFF700), &D1);    // MOVE.W	$F700,D1
  DEF_ROMLOC(C65C) : sub_toreg_16(0x80, &D1);       // SUBI.W	#$0080,D1
  DEF_ROMLOC(C660) : and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
  DEF_ROMLOC(C664) : sub_toreg_16(D1, &D0);         // SUB.W	D1,D0
  DEF_ROMLOC(C666) : cmp_toreg_16(0x280, &D0);      // CMPI.W	#$0280,D0
  DEF_ROMLOC(C66A) : if (CCR_HI) {
    rom_C670();
    return;
  } // BHI.B	$C670
  rom_DC92();
  return; // BRA.W	$DC92
}
ROMFUNC(rom_C5F8) {
  DEF_ROMLOC(C5F8) : tst_mem_8(A0 + 0x32); // TST.B	50(A0)
  DEF_ROMLOC(C5FC) : if (!CCR_EQ) {
    rom_C6D0();
    return;
  }                                           // BNE.W	$C6D0
  DEF_ROMLOC(C600) : move_toreg_32(0x0, &D1); // MOVEQ.L	$00,D1
  DEF_ROMLOC(C602)
      : move_toreg_8(read_8(A0 + 0x19), &D1);  // MOVE.B	25(A0),D1
  DEF_ROMLOC(C606) : add_toreg_16(0xB, &D1);   // ADDI.W	#$000B,D1
  DEF_ROMLOC(C60A) : move_toreg_16(0x10, &D2); // MOVE.W	#$0010,D2
  DEF_ROMLOC(C60E) : move_toreg_16(0x11, &D3); // MOVE.W	#$0011,D3
  DEF_ROMLOC(C612)
      : move_toreg_16(read_16(A0 + 0x8), &D4);        // MOVE.W	8(A0),D4
  DEF_ROMLOC(C616) : rom_C810();                      // BSR.W	$C810
  DEF_ROMLOC(C61A) : cmp_tomem_16(0x200, 0xFFFFFE10); // CMPI.W	#$0200,$FE10
  DEF_ROMLOC(C620) : if (!CCR_EQ) {
    rom_C650();
    return;
  }                                                // BNE.B	$C650
  DEF_ROMLOC(C622) : bclr_tomem_8(0x7, A0 + 0x28); // BCLR.B	#$07,40(A0)
  DEF_ROMLOC(C628)
      : move_toreg_16(read_16(A0 + 0x8), &D0); // MOVE.W	8(A0),D0
  DEF_ROMLOC(C62C) : cmp_toreg_16(0xA20, &D0); // CMPI.W	#$0A20,D0
  DEF_ROMLOC(C630) : if (CCR_CS) {
    rom_C650();
    return;
  }                                            // BCS.B	$C650
  DEF_ROMLOC(C632) : cmp_toreg_16(0xAA1, &D0); // CMPI.W	#$0AA1,D0
  DEF_ROMLOC(C636) : if (CCR_CC) {
    rom_C650();
    return;
  } // BCC.B	$C650
  DEF_ROMLOC(C638)
      : move_toreg_16(read_16(0xFFFFF7A4), &D0);    // MOVE.W	$F7A4,D0
  DEF_ROMLOC(C63C) : sub_toreg_16(0x1C, &D0);       // SUBI.W	#$001C,D0
  DEF_ROMLOC(C640) : move_tomem_16(D0, A0 + 0xC);   // MOVE.W	D0,12(A0)
  DEF_ROMLOC(C644) : bset_tomem_8(0x7, 0xFFFFF7A4); // BSET.B	#$07,$F7A4
  DEF_ROMLOC(C64A) : bset_tomem_8(0x7, A0 + 0x28);  // BSET.B	#$07,40(A0)
  rom_C650();
}
ROMFUNC(rom_C670) {
  DEF_ROMLOC(C670)
      : move_toreg_16(read_16(A0 + 0x34), &D0);     // MOVE.W	52(A0),D0
  DEF_ROMLOC(C674) : and_toreg_16(0xFFFFFF80, &D0); // ANDI.W	#$FF80,D0
  DEF_ROMLOC(C678)
      : move_toreg_16(read_16(0xFFFFF700), &D1);    // MOVE.W	$F700,D1
  DEF_ROMLOC(C67C) : sub_toreg_16(0x80, &D1);       // SUBI.W	#$0080,D1
  DEF_ROMLOC(C680) : and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
  DEF_ROMLOC(C684) : sub_toreg_16(D1, &D0);         // SUB.W	D1,D0
  DEF_ROMLOC(C686) : cmp_toreg_16(0x280, &D0);      // CMPI.W	#$0280,D0
  DEF_ROMLOC(C68A) : if (CCR_HI) {
    rom_C6A0();
    return;
  } // BHI.B	$C6A0
  DEF_ROMLOC(C68C)
      : move_tomem_16(read_16(A0 + 0x34), A0 + 0x8); // MOVE.W	52(A0),8(A0)
  DEF_ROMLOC(C692)
      : move_tomem_16(read_16(A0 + 0x36), A0 + 0xC); // MOVE.W	54(A0),12(A0)
  DEF_ROMLOC(C698) : move_tomem_8(0x4, A0 + 0x24);   // MOVE.B	#$04,36(A0)
  rom_C6B6();                                        // BRA.B	$C6B6
}
ROMFUNC(rom_C6A0) {
  DEF_ROMLOC(C6A0) : move_toreg_32(0xFFFFFC00, &A2); // LEA.L	$FC00,A2
  DEF_ROMLOC(C6A4) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(C6A6)
      : move_toreg_8(read_8(A0 + 0x23), &D0);   // MOVE.B	35(A0),D0
  DEF_ROMLOC(C6AA) : if (CCR_EQ) goto rom_C6B2; // BEQ.B	$C6B2
  DEF_ROMLOC(C6AC)
      : bclr_tomem_8(0x0,
                     (s32)A2 + (s8)0x2 + (s16)D0); // BCLR.B	#$00,2(A2,D0)
  DEF_ROMLOC(C6B2) : rom_DCCE();                   // BRA.W	$DCCE
}
ROMFUNC(rom_C6B6) {
  DEF_ROMLOC(C6B6) : rom_DF34();                   // BSR.W	$DF34
  DEF_ROMLOC(C6BA) : if (CCR_EQ) goto rom_C6CE;    // BEQ.B	$C6CE
  DEF_ROMLOC(C6BC) : move_tomem_8(0x2, A0 + 0x24); // MOVE.B	#$02,36(A0)
  DEF_ROMLOC(C6C2) : clr_mem_8(A0 + 0x32);         // CLR.B	50(A0)
  DEF_ROMLOC(C6C6) : clr_mem_16(A0 + 0x10);        // CLR.W	16(A0)
  DEF_ROMLOC(C6CA) : clr_mem_16(A0 + 0x12);        // CLR.W	18(A0)
  DEF_ROMLOC(C6CE) : return;                       // RTS
}
ROMFUNC(rom_C7A4) {
  DEF_ROMLOC(C7A4) : cmp_tomem_16(0x201, 0xFFFFFE10); // CMPI.W	#$0201,$FE10
  DEF_ROMLOC(C7AA) : if (!CCR_EQ) goto rom_C7CA;      // BNE.B	$C7CA
  DEF_ROMLOC(C7AC) : move_toreg_16(0xFFFFFFE0, &D2);  // MOVE.W	#$FFE0,D2
  DEF_ROMLOC(C7B0) : cmp_tomem_16(0xDD0, A0 + 0x8);   // CMPI.W	#$0DD0,8(A0)
  DEF_ROMLOC(C7B6) : if (CCR_EQ) goto rom_C7E8;       // BEQ.B	$C7E8
  DEF_ROMLOC(C7B8) : cmp_tomem_16(0xCC0, A0 + 0x8);   // CMPI.W	#$0CC0,8(A0)
  DEF_ROMLOC(C7BE) : if (CCR_EQ) goto rom_C7E8;       // BEQ.B	$C7E8
  DEF_ROMLOC(C7C0) : cmp_tomem_16(0xBA0, A0 + 0x8);   // CMPI.W	#$0BA0,8(A0)
  DEF_ROMLOC(C7C6) : if (CCR_EQ) goto rom_C7E8;       // BEQ.B	$C7E8
  DEF_ROMLOC(C7C8) : return;                          // RTS
  DEF_ROMLOC(C7CA) : cmp_tomem_16(0x202, 0xFFFFFE10); // CMPI.W	#$0202,$FE10
  DEF_ROMLOC(C7D0) : if (!CCR_EQ) goto rom_C7E6;      // BNE.B	$C7E6
  DEF_ROMLOC(C7D2) : move_toreg_16(0x20, &D2);        // MOVE.W	#$0020,D2
  DEF_ROMLOC(C7D6) : cmp_tomem_16(0x560, A0 + 0x8);   // CMPI.W	#$0560,8(A0)
  DEF_ROMLOC(C7DC) : if (CCR_EQ) goto rom_C7E8;       // BEQ.B	$C7E8
  DEF_ROMLOC(C7DE) : cmp_tomem_16(0x5C0, A0 + 0x8);   // CMPI.W	#$05C0,8(A0)
  DEF_ROMLOC(C7E4) : if (CCR_EQ) goto rom_C7E8;       // BEQ.B	$C7E8
  DEF_ROMLOC(C7E6) : return;                          // RTS
  DEF_ROMLOC(C7E8) : rom_E11A();                      // BSR.W	$E11A
  DEF_ROMLOC(C7EC) : if (!CCR_EQ) goto rom_C80E;      // BNE.B	$C80E
  DEF_ROMLOC(C7EE) : move_tomem_8(0x4C, A1 + 0x0);    // MOVE.B	#$4C,0(A1)
  DEF_ROMLOC(C7F4)
      : move_tomem_16(read_16(A0 + 0x8), A1 + 0x8); // MOVE.W	8(A0),8(A1)
  DEF_ROMLOC(C7FA) : add_tomem_16(D2, A1 + 0x8);    // ADD.W	D2,8(A1)
  DEF_ROMLOC(C7FE)
      : move_tomem_16(read_16(A0 + 0xC), A1 + 0xC); // MOVE.W	12(A0),12(A1)
  DEF_ROMLOC(C804) : add_tomem_16(0x10, A1 + 0xC);  // ADDI.W	#$0010,12(A1)
  DEF_ROMLOC(C80A) : move_tomem_32(A0, A1 + 0x3C);  // MOVE.L	A0,60(A1)
  DEF_ROMLOC(C80E) : return;                        // RTS
}
ROMFUNC(rom_C6D0) {
  DEF_ROMLOC(C6D0)
      : move_tomem_16(read_16(A0 + 0x8), A7 -= 2);    // MOVE.W	8(A0),-(A7)
  DEF_ROMLOC(C6D4) : cmp_tomem_8(0x4, A0 + 0x25);     // CMPI.B	#$04,37(A0)
  DEF_ROMLOC(C6DA) : if (CCR_CC) goto rom_C6E0;       // BCC.B	$C6E0
  DEF_ROMLOC(C6DC) : rom_DC6C();                      // BSR.W	$DC6C
  DEF_ROMLOC(C6E0) : btst_tomem_8(0x1, A0 + 0x22);    // BTST.B	#$01,34(A0)
  DEF_ROMLOC(C6E6) : if (CCR_EQ) goto rom_C72A;       // BEQ.B	$C72A
  DEF_ROMLOC(C6E8) : add_tomem_16(0x18, A0 + 0x12);   // ADDI.W	#$0018,18(A0)
  DEF_ROMLOC(C6EE) : rom_15580();                     // JSR	$00015580
  DEF_ROMLOC(C6F4) : tst_reg_16(&D1);                 // TST.W	D1
  DEF_ROMLOC(C6F6) : if (CCR_PL) goto rom_C728;       // BPL.W	$C728
  DEF_ROMLOC(C6FA) : add_tomem_16(D1, A0 + 0xC);      // ADD.W	D1,12(A0)
  DEF_ROMLOC(C6FE) : clr_mem_16(A0 + 0x12);           // CLR.W	18(A0)
  DEF_ROMLOC(C702) : bclr_tomem_8(0x1, A0 + 0x22);    // BCLR.B	#$01,34(A0)
  DEF_ROMLOC(C708) : move_toreg_16(read_16(A1), &D0); // MOVE.W	(A1),D0
  DEF_ROMLOC(C70A) : and_toreg_16(0x3FF, &D0);        // ANDI.W	#$03FF,D0
  DEF_ROMLOC(C70E) : cmp_toreg_16(0x16A, &D0);        // CMPI.W	#$016A,D0
  DEF_ROMLOC(C712) : if (CCR_CS) goto rom_C728;       // BCS.B	$C728
  DEF_ROMLOC(C714)
      : move_toreg_16(read_16(A0 + 0x30), &D0);    // MOVE.W	48(A0),D0
  DEF_ROMLOC(C718) : asr_toreg_16(0x3, &D0);       // ASR.W	#$03,D0
  DEF_ROMLOC(C71A) : move_tomem_16(D0, A0 + 0x10); // MOVE.W	D0,16(A0)
  DEF_ROMLOC(C71E) : move_tomem_8(0x1, A0 + 0x32); // MOVE.B	#$01,50(A0)
  DEF_ROMLOC(C724) : clr_mem_16(A0 + 0xE);         // CLR.W	14(A0)
  DEF_ROMLOC(C728) : goto rom_C770;                // BRA.B	$C770
  DEF_ROMLOC(C72A) : tst_mem_16(A0 + 0x10);        // TST.W	16(A0)
  DEF_ROMLOC(C72E) : if (CCR_EQ) goto rom_C760;    // BEQ.W	$C760
  DEF_ROMLOC(C732) : if (CCR_MI) goto rom_C746;    // BMI.B	$C746
  DEF_ROMLOC(C734) : move_toreg_32(0x0, &D3);      // MOVEQ.L	$00,D3
  DEF_ROMLOC(C736)
      : move_toreg_8(read_8(A0 + 0x19), &D3);   // MOVE.B	25(A0),D3
  DEF_ROMLOC(C73A) : rom_15642();               // JSR	$00015642
  DEF_ROMLOC(C740) : tst_reg_16(&D1);           // TST.W	D1
  DEF_ROMLOC(C742) : if (CCR_MI) goto rom_C75A; // BMI.B	$C75A
  goto rom_C770;                                // BRA.B	$C770
  DEF_ROMLOC(C746) : move_toreg_32(0x0, &D3);   // MOVEQ.L	$00,D3
  DEF_ROMLOC(C748)
      : move_toreg_8(read_8(A0 + 0x19), &D3);   // MOVE.B	25(A0),D3
  DEF_ROMLOC(C74C) : not_reg_16(&D3);           // NOT.W	D3
  DEF_ROMLOC(C74E) : rom_157D4();               // JSR	$000157D4
  DEF_ROMLOC(C754) : tst_reg_16(&D1);           // TST.W	D1
  DEF_ROMLOC(C756) : if (CCR_MI) goto rom_C75A; // BMI.B	$C75A
  goto rom_C770;                                // BRA.B	$C770
  DEF_ROMLOC(C75A) : clr_mem_16(A0 + 0x10);     // CLR.W	16(A0)
  goto rom_C770;                                // BRA.B	$C770
  DEF_ROMLOC(C760)
      : add_tomem_32(0x2001, A0 + 0xC); // ADDI.L	#$00002001,12(A0)
  DEF_ROMLOC(C768) : cmp_tomem_8(0xFFFFFFA0, A0 + 0xF); // CMPI.B
                                                        // #$A0,15(A0)
  DEF_ROMLOC(C76E) : if (CCR_CC) goto rom_C78E;         // BCC.B	$C78E
  DEF_ROMLOC(C770) : move_toreg_32(0x0, &D1);           // MOVEQ.L	$00,D1
  DEF_ROMLOC(C772)
      : move_toreg_8(read_8(A0 + 0x19), &D1);  // MOVE.B	25(A0),D1
  DEF_ROMLOC(C776) : add_toreg_16(0xB, &D1);   // ADDI.W	#$000B,D1
  DEF_ROMLOC(C77A) : move_toreg_16(0x10, &D2); // MOVE.W	#$0010,D2
  DEF_ROMLOC(C77E) : move_toreg_16(0x11, &D3); // MOVE.W	#$0011,D3
  DEF_ROMLOC(C782)
      : move_toreg_16(read_16((A7 += 2, A7 - 2)), &D4); // MOVE.W	(A7)+,D4
  DEF_ROMLOC(C784) : rom_C810();                        // BSR.W	$C810
  DEF_ROMLOC(C788) : rom_C7A4();                        // BSR.B	$C7A4
  rom_C650();
  return; // BRA.W	$C650
  DEF_ROMLOC(C78E)
      : move_toreg_16(read_16((A7 += 2, A7 - 2)), &D4); // MOVE.W	(A7)+,D4
  DEF_ROMLOC(C790) : move_toreg_32(0xFFFFD000, &A1);    // LEA.L	$D000,A1
  DEF_ROMLOC(C794) : bclr_tomem_8(0x3, A1 + 0x22);      // BCLR.B	#$03,34(A1)
  DEF_ROMLOC(C79A) : bclr_tomem_8(0x3, A0 + 0x22);      // BCLR.B	#$03,34(A0)
  rom_C670();
  return; // BRA.W	$C670
}
ROMFUNC(rom_C810) {
  DEF_ROMLOC(C810)
      : move_toreg_8(read_8(A0 + 0x25), &D0);      // MOVE.B	37(A0),D0
  DEF_ROMLOC(C814) : if (CCR_EQ) goto rom_C8A2;    // BEQ.W	$C8A2
  DEF_ROMLOC(C818) : sub_toreg_8(0x2, &D0);        // SUBQ.B	#$02,D0
  DEF_ROMLOC(C81A) : if (!CCR_EQ) goto rom_C834;   // BNE.B	$C834
  DEF_ROMLOC(C81C) : rom_7C3E();                   // BSR.W	$7C3E
  DEF_ROMLOC(C820) : btst_tomem_8(0x3, A1 + 0x22); // BTST.B	#$03,34(A1)
  DEF_ROMLOC(C826) : if (!CCR_EQ) goto rom_C82E;   // BNE.B	$C82E
  DEF_ROMLOC(C828) : clr_mem_8(A0 + 0x25);         // CLR.B	37(A0)
  DEF_ROMLOC(C82C) : return;                       // RTS
  DEF_ROMLOC(C82E) : move_toreg_16(D4, &D2);       // MOVE.W	D4,D2
  rom_81A0();
  return;                                             // BRA.W	$81A0
  DEF_ROMLOC(C834) : sub_toreg_8(0x2, &D0);           // SUBQ.B	#$02,D0
  DEF_ROMLOC(C836) : if (!CCR_EQ) goto rom_C87C;      // BNE.B	$C87C
  DEF_ROMLOC(C838) : rom_DC6C();                      // BSR.W	$DC6C
  DEF_ROMLOC(C83C) : add_tomem_16(0x18, A0 + 0x12);   // ADDI.W	#$0018,18(A0)
  DEF_ROMLOC(C842) : rom_15580();                     // JSR	$00015580
  DEF_ROMLOC(C848) : tst_reg_16(&D1);                 // TST.W	D1
  DEF_ROMLOC(C84A) : if (CCR_PL) goto rom_C87A;       // BPL.W	$C87A
  DEF_ROMLOC(C84E) : add_tomem_16(D1, A0 + 0xC);      // ADD.W	D1,12(A0)
  DEF_ROMLOC(C852) : clr_mem_16(A0 + 0x12);           // CLR.W	18(A0)
  DEF_ROMLOC(C856) : clr_mem_8(A0 + 0x25);            // CLR.B	37(A0)
  DEF_ROMLOC(C85A) : move_toreg_16(read_16(A1), &D0); // MOVE.W	(A1),D0
  DEF_ROMLOC(C85C) : and_toreg_16(0x3FF, &D0);        // ANDI.W	#$03FF,D0
  DEF_ROMLOC(C860) : cmp_toreg_16(0x16A, &D0);        // CMPI.W	#$016A,D0
  DEF_ROMLOC(C864) : if (CCR_CS) goto rom_C87A;       // BCS.B	$C87A
  DEF_ROMLOC(C866)
      : move_toreg_16(read_16(A0 + 0x30), &D0);    // MOVE.W	48(A0),D0
  DEF_ROMLOC(C86A) : asr_toreg_16(0x3, &D0);       // ASR.W	#$03,D0
  DEF_ROMLOC(C86C) : move_tomem_16(D0, A0 + 0x10); // MOVE.W	D0,16(A0)
  DEF_ROMLOC(C870) : move_tomem_8(0x1, A0 + 0x32); // MOVE.B	#$01,50(A0)
  DEF_ROMLOC(C876) : clr_mem_16(A0 + 0xE);         // CLR.W	14(A0)
  DEF_ROMLOC(C87A) : return;                       // RTS
  DEF_ROMLOC(C87C) : rom_DC6C();                   // BSR.W	$DC6C
  DEF_ROMLOC(C880)
      : move_toreg_16(read_16(A0 + 0x8), &D0);           // MOVE.W	8(A0),D0
  DEF_ROMLOC(C884) : and_toreg_16(0xC, &D0);             // ANDI.W	#$000C,D0
  DEF_ROMLOC(C888) : if (!CCR_EQ) goto rom_C96E;         // BNE.W	$C96E
  DEF_ROMLOC(C88C) : and_tomem_16(0xFFFFFFF0, A0 + 0x8); // ANDI.W
                                                         // #$FFF0,8(A0)
  DEF_ROMLOC(C892)
      : move_tomem_16(read_16(A0 + 0x10), A0 + 0x30); // MOVE.W	16(A0),48(A0)
  DEF_ROMLOC(C898) : clr_mem_16(A0 + 0x10);           // CLR.W	16(A0)
  DEF_ROMLOC(C89C) : sub_tomem_8(0x2, A0 + 0x25);     // SUBQ.B	#$02,37(A0)
  DEF_ROMLOC(C8A0) : return;                          // RTS
  DEF_ROMLOC(C8A2) : rom_10154();                     // BSR.W	$10154
  DEF_ROMLOC(C8A6) : tst_reg_16(&D4);                 // TST.W	D4
  DEF_ROMLOC(C8A8) : if (CCR_EQ) goto rom_C96E;       // BEQ.W	$C96E
  DEF_ROMLOC(C8AC) : if (CCR_MI) goto rom_C96E;       // BMI.W	$C96E
  DEF_ROMLOC(C8B0) : tst_mem_8(A0 + 0x32);            // TST.B	50(A0)
  DEF_ROMLOC(C8B4) : if (CCR_EQ) goto rom_C8BA;       // BEQ.B	$C8BA
  goto rom_C96E;                                      // BRA.W	$C96E
  DEF_ROMLOC(C8BA) : tst_reg_16(&D0);                 // TST.W	D0
  DEF_ROMLOC(C8BC) : if (CCR_EQ) goto rom_C96E;       // BEQ.W	$C96E
  DEF_ROMLOC(C8C0) : if (CCR_MI) goto rom_C8F2;       // BMI.B	$C8F2
  DEF_ROMLOC(C8C2) : btst_tomem_8(0x0, A1 + 0x22);    // BTST.B	#$00,34(A1)
  DEF_ROMLOC(C8C8) : if (!CCR_EQ) goto rom_C96E;      // BNE.W	$C96E
  DEF_ROMLOC(C8CC) : move_tomem_16(D0, A7 -= 2);      // MOVE.W	D0,-(A7)
  DEF_ROMLOC(C8CE) : move_toreg_32(0x0, &D3);         // MOVEQ.L	$00,D3
  DEF_ROMLOC(C8D0)
      : move_toreg_8(read_8(A0 + 0x19), &D3); // MOVE.B	25(A0),D3
  DEF_ROMLOC(C8D4) : rom_15642();             // JSR	$00015642
  DEF_ROMLOC(C8DA)
      : move_toreg_16(read_16((A7 += 2, A7 - 2)), &D0); // MOVE.W	(A7)+,D0
  DEF_ROMLOC(C8DC) : tst_reg_16(&D1);                   // TST.W	D1
  DEF_ROMLOC(C8DE) : if (CCR_MI) goto rom_C96E;         // BMI.W	$C96E
  DEF_ROMLOC(C8E2)
      : add_tomem_32(0x10000, A0 + 0x8);           // ADDI.L	#$00010000,8(A0)
  DEF_ROMLOC(C8EA) : move_toreg_32(0x1, &D0);      // MOVEQ.L	$01,D0
  DEF_ROMLOC(C8EC) : move_toreg_16(0x40, &D1);     // MOVE.W	#$0040,D1
  goto rom_C91E;                                   // BRA.B	$C91E
  DEF_ROMLOC(C8F2) : btst_tomem_8(0x0, A1 + 0x22); // BTST.B	#$00,34(A1)
  DEF_ROMLOC(C8F8) : if (CCR_EQ) goto rom_C96E;    // BEQ.B	$C96E
  DEF_ROMLOC(C8FA) : move_tomem_16(D0, A7 -= 2);   // MOVE.W	D0,-(A7)
  DEF_ROMLOC(C8FC) : move_toreg_32(0x0, &D3);      // MOVEQ.L	$00,D3
  DEF_ROMLOC(C8FE)
      : move_toreg_8(read_8(A0 + 0x19), &D3); // MOVE.B	25(A0),D3
  DEF_ROMLOC(C902) : not_reg_16(&D3);         // NOT.W	D3
  DEF_ROMLOC(C904) : rom_157D4();             // JSR	$000157D4
  DEF_ROMLOC(C90A)
      : move_toreg_16(read_16((A7 += 2, A7 - 2)), &D0); // MOVE.W	(A7)+,D0
  DEF_ROMLOC(C90C) : tst_reg_16(&D1);                   // TST.W	D1
  DEF_ROMLOC(C90E) : if (CCR_MI) goto rom_C96E;         // BMI.B	$C96E
  DEF_ROMLOC(C910)
      : sub_tomem_32(0x10000, A0 + 0x8);             // SUBI.L	#$00010000,8(A0)
  DEF_ROMLOC(C918) : move_toreg_32(0xFFFFFFFF, &D0); // MOVEQ.L	$FF,D0
  DEF_ROMLOC(C91A) : move_toreg_16(0xFFFFFFC0, &D1); // MOVE.W	#$FFC0,D1
  DEF_ROMLOC(C91E) : move_toreg_32(0xFFFFD000, &A1); // LEA.L	$D000,A1
  DEF_ROMLOC(C922) : add_tomem_16(D0, A1 + 0x8);     // ADD.W	D0,8(A1)
  DEF_ROMLOC(C926) : move_tomem_16(D1, A1 + 0x14);   // MOVE.W	D1,20(A1)
  DEF_ROMLOC(C92A) : move_tomem_16(0x0, A1 + 0x10);  // MOVE.W	#$0000,16(A1)
  DEF_ROMLOC(C930) : move_tomem_16(D0, A7 -= 2);     // MOVE.W	D0,-(A7)
  DEF_ROMLOC(C932) : move_toreg_16(0xA7, &D0);       // MOVE.W	#$00A7,D0
  DEF_ROMLOC(C936) : rom_1394();                     // JSR	$00001394
  DEF_ROMLOC(C93C)
      : move_toreg_16(read_16((A7 += 2, A7 - 2)), &D0); // MOVE.W	(A7)+,D0
  DEF_ROMLOC(C93E) : tst_mem_8(A0 + 0x28);              // TST.B	40(A0)
  DEF_ROMLOC(C942) : if (CCR_MI) goto rom_C96E;         // BMI.B	$C96E
  DEF_ROMLOC(C944) : move_tomem_16(D0, A7 -= 2);        // MOVE.W	D0,-(A7)
  DEF_ROMLOC(C946) : rom_15580();                       // JSR	$00015580
  DEF_ROMLOC(C94C)
      : move_toreg_16(read_16((A7 += 2, A7 - 2)), &D0); // MOVE.W	(A7)+,D0
  DEF_ROMLOC(C94E) : cmp_toreg_16(0x4, &D1);            // CMPI.W	#$0004,D1
  DEF_ROMLOC(C952) : if (CCR_LE) goto rom_C96A;         // BLE.B	$C96A
  DEF_ROMLOC(C954) : move_tomem_16(0x400, A0 + 0x10);   // MOVE.W	#$0400,16(A0)
  DEF_ROMLOC(C95A) : tst_reg_16(&D0);                   // TST.W	D0
  DEF_ROMLOC(C95C) : if (CCR_PL) goto rom_C962;         // BPL.B	$C962
  DEF_ROMLOC(C95E) : neg_mem_16(A0 + 0x10);             // NEG.W	16(A0)
  DEF_ROMLOC(C962) : move_tomem_8(0x6, A0 + 0x25);      // MOVE.B	#$06,37(A0)
  goto rom_C96E;                                        // BRA.B	$C96E
  DEF_ROMLOC(C96A) : add_tomem_16(D1, A0 + 0xC);        // ADD.W	D1,12(A0)
  DEF_ROMLOC(C96E) : return;                            // RTS
  DEF_ROMLOC(C970) : or_toreg_8(0xA, &D4);              // ORI.B	#$0A,D4
  DEF_ROMLOC(C974)
      : bset_tomem_8(D0,
                     (s32)A0 + (s8)0x0 + (s16)D0); // BSET.B	D0,0(A0,D0)
  DEF_ROMLOC(C978)
      : bset_tomem_8(0xFFFFFFF0,
                     (s32)A0 + (s8)0x0 + (s16)D0); // BSET.B	#$F0,0(A0,D0)
  DEF_ROMLOC(C97E) : bset_toreg_32(0xF, &D0);      // BSET.L	#$0F,D0
  rom_C990(); // Detected flow into next function
}