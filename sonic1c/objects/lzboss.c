// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

void lz_boss_main(bool skip_to_ship);
ROMFUNC(rom_185E2) {
  u8 switchindex = 0;
  DEF_ROMLOC(185E2) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(185E4) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(185E8)
      : move_toreg_16(read_16(0x185F0 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(185EC): goto rom_185F0 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(185EC) : switch (switchindex) {
  case 0:
    rom_185FE();
    break;
  case 1:
    lz_boss_main(true);
    break;
  case 2:
    rom_18920();
    break;
  case 3:
    rom_1896E();
    break;
  }
}
void lz_boss_main(bool skip_to_ship) {
  if (skip_to_ship) {
    goto rom_18686;
  }
  DEF_ROMLOC(185FE)
      : move_tomem_16(0x1E10, A0 + 0x8); // MOVE.W
                                         // #$1E10,8(A0)
  DEF_ROMLOC(18604)
      : move_tomem_16(0x5C0, A0 + 0xC); // MOVE.W	#$05C0,12(A0)
  DEF_ROMLOC(1860A)
      : move_tomem_16(read_16(A0 + 0x8), A0 + 0x30); // MOVE.W	8(A0),48(A0)
  DEF_ROMLOC(18610)
      : move_tomem_16(read_16(A0 + 0xC), A0 + 0x38);   // MOVE.W	12(A0),56(A0)
  DEF_ROMLOC(18616) : move_tomem_8(0xF, A0 + 0x20);    // MOVE.B	#$0F,32(A0)
  DEF_ROMLOC(1861C) : move_tomem_8(0x8, A0 + 0x21);    // MOVE.B	#$08,33(A0)
  DEF_ROMLOC(18622) : move_tomem_8(0x4, A0 + 0x18);    // MOVE.B	#$04,24(A0)
  DEF_ROMLOC(18628) : move_toreg_32(0x185F8, &A2);     // LEA.L	-50(PC),A2
  DEF_ROMLOC(1862C) : move_toreg_32(A0, &A1);          // MOVEA.L	A0,A1
  DEF_ROMLOC(1862E) : move_toreg_32(0x2, &D1);         // MOVEQ.L	$02,D1
  goto rom_1864C;                                      // BRA.B	$1864C
  DEF_ROMLOC(18632) : rom_E130();                      // JSR	$0000E130
  DEF_ROMLOC(18638) : if (!CCR_EQ) { goto rom_18686; } // BNE.B	$18686
  DEF_ROMLOC(1863A) : move_tomem_8(0x77, A1 + 0x0);    // MOVE.B	#$77,0(A1)
  DEF_ROMLOC(18640)
      : move_tomem_16(read_16(A0 + 0x8), A1 + 0x8); // MOVE.W	8(A0),8(A1)
  DEF_ROMLOC(18646)
      : move_tomem_16(read_16(A0 + 0xC), A1 + 0xC); // MOVE.W	12(A0),12(A1)
  DEF_ROMLOC(1864C) : bclr_tomem_8(0x0, A0 + 0x22); // BCLR.B	#$00,34(A0)
  DEF_ROMLOC(18652) : clr_mem_8(A1 + 0x25);         // CLR.B	37(A1)
  DEF_ROMLOC(18656)
      : move_tomem_8(read_8(A2++), A1 + 0x24); // MOVE.B	(A2)+,36(A1)
  DEF_ROMLOC(1865A)
      : move_tomem_8(read_8(A2++), A1 + 0x1C); // MOVE.B	(A2)+,28(A1)
  DEF_ROMLOC(1865E)
      : move_tomem_8(read_8(A0 + 0x18), A1 + 0x18); // MOVE.B	24(A0),24(A1)
  DEF_ROMLOC(18664)
      : move_tomem_32(0x184B8, A1 + 0x4);             // MOVE.L	#$000184B8,4(A1)
  DEF_ROMLOC(1866C) : move_tomem_16(0x400, A1 + 0x2); // MOVE.W	#$0400,2(A1)
  DEF_ROMLOC(18672) : move_tomem_8(0x4, A1 + 0x1);    // MOVE.B	#$04,1(A1)
  DEF_ROMLOC(18678) : move_tomem_8(0x20, A1 + 0x19);  // MOVE.B	#$20,25(A1)
  DEF_ROMLOC(1867E) : move_tomem_32(A0, A1 + 0x34);   // MOVE.L	A0,52(A1)
  DEF_ROMLOC(18682) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_18632; // DBF.W	D1,$18632
  u8 switchindex = 0;
  DEF_ROMLOC(18686) : move_toreg_32(0xFFFFD000, &A1); // LEA.L	$D000,A1
  DEF_ROMLOC(1868A) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(1868C) : move_toreg_8(read_8(A0 + 0x25), &D0);
  switchindex = D0 / 2; // MOVE.B	37(A0),D0
  DEF_ROMLOC(18690)
      : move_toreg_16(read_16(0x186BA + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	40(PC,D0),D1
  // DEF_ROMLOC(18694): rom_186BA + (s16)(D1 & 0xffff)(); // JSR
  // 36(PC,D1)
  DEF_ROMLOC(18694) : switch (switchindex) {
  case 0:
    rom_186CA();
    break;
  case 1:
    rom_1874C();
    break;
  case 2:
    rom_1878C();
    break;
  case 3:
    rom_187CA();
    break;
  case 4:
    rom_18868();
    break;
  case 5:
    rom_188A2();
    break;
  case 6:
    rom_188DA();
    break;
  case 7:
    rom_18902();
    break;
  }
  DEF_ROMLOC(18698) : move_toreg_32(0x18468, &A1);         // LEA.L	$00018468,A1
  DEF_ROMLOC(1869E) : animate_sprite();                          // JSR	$0000ADA2
  DEF_ROMLOC(186A4) : move_toreg_32(0x3, &D0);             // MOVEQ.L	$03,D0
  DEF_ROMLOC(186A6) : and_toreg_8(read_8(A0 + 0x22), &D0); // AND.B
                                                           // 34(A0),D0
  DEF_ROMLOC(186AA)
      : and_tomem_8(0xFFFFFFFC, A0 + 0x1);      // ANDI.B
                                                // #$FC,1(A0)
  DEF_ROMLOC(186B0) : or_tomem_8(D0, A0 + 0x1); // OR.B	D0,1(A0)
  DEF_ROMLOC(186B4) : rom_DC92();
  return; // JMP	$0000DC92
}
ROMFUNC(rom_185FE) { lz_boss_main(false); }
ROMFUNC(rom_186E4) {
  DEF_ROMLOC(186E4) : rom_18050(); // BSR.W	$18050
  DEF_ROMLOC(186E8)
      : move_tomem_16(read_16(A0 + 0x38), A0 + 0xC); // MOVE.W	56(A0),12(A0)
  DEF_ROMLOC(186EE)
      : move_tomem_16(read_16(A0 + 0x30), A0 + 0x8); // MOVE.W	48(A0),8(A0)
  rom_186F4(); // Detected flow into next function
}
ROMFUNC(rom_186CA) {
  DEF_ROMLOC(186CA)
      : move_toreg_16(read_16(A1 + 0x8), &D0);   // MOVE.W	8(A1),D0
  DEF_ROMLOC(186CE) : cmp_toreg_16(0x1DA0, &D0); // CMPI.W	#$1DA0,D0
  DEF_ROMLOC(186D2) : if (CCR_CS) {
    rom_186E4();
    return;
  } // BCS.B	$186E4
  DEF_ROMLOC(186D4)
      : move_tomem_16(0xFFFFFE80, A0 + 0x12);         // MOVE.W	#$FE80,18(A0)
  DEF_ROMLOC(186DA) : move_tomem_16(0x60, A0 + 0x10); // MOVE.W	#$0060,16(A0)
  DEF_ROMLOC(186E0) : add_tomem_8(0x2, A0 + 0x25);    // ADDQ.B	#$02,37(A0)
  rom_186E4();
}
ROMFUNC(rom_186F4) {
  DEF_ROMLOC(186F4) : tst_mem_8(A0 + 0x3D);           // TST.B	61(A0)
  DEF_ROMLOC(186F8) : if (!CCR_EQ) goto rom_1873A;    // BNE.B	$1873A
  DEF_ROMLOC(186FA) : tst_mem_8(A0 + 0x22);           // TST.B	34(A0)
  DEF_ROMLOC(186FE) : if (CCR_MI) goto rom_1873E;     // BMI.B	$1873E
  DEF_ROMLOC(18700) : tst_mem_8(A0 + 0x20);           // TST.B	32(A0)
  DEF_ROMLOC(18704) : if (!CCR_EQ) goto rom_18738;    // BNE.B	$18738
  DEF_ROMLOC(18706) : tst_mem_8(A0 + 0x3E);           // TST.B	62(A0)
  DEF_ROMLOC(1870A) : if (!CCR_EQ) goto rom_1871C;    // BNE.B	$1871C
  DEF_ROMLOC(1870C) : move_tomem_8(0x20, A0 + 0x3E);  // MOVE.B	#$20,62(A0)
  DEF_ROMLOC(18712) : move_toreg_16(0xAC, &D0);       // MOVE.W	#$00AC,D0
  DEF_ROMLOC(18716) : play_sound_special();           // JSR	$00001394
  DEF_ROMLOC(1871C) : move_toreg_32(0xFFFFFB22, &A1); // LEA.L	$FB22,A1
  DEF_ROMLOC(18720) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(18722) : tst_mem_16(A1);                 // TST.W	(A1)
  DEF_ROMLOC(18724) : if (!CCR_EQ) goto rom_1872A;    // BNE.B	$1872A
  DEF_ROMLOC(18726) : move_toreg_16(0xEEE, &D0);      // MOVE.W	#$0EEE,D0
  DEF_ROMLOC(1872A) : move_tomem_16(D0, A1);          // MOVE.W	D0,(A1)
  DEF_ROMLOC(1872C) : sub_tomem_8(0x1, A0 + 0x3E);    // SUBQ.B	#$01,62(A0)
  DEF_ROMLOC(18730) : if (!CCR_EQ) goto rom_18738;    // BNE.B	$18738
  DEF_ROMLOC(18732) : move_tomem_8(0xF, A0 + 0x20);   // MOVE.B	#$0F,32(A0)
  DEF_ROMLOC(18738) : return;                         // RTS
  DEF_ROMLOC(1873A) : rom_1800C();
  return;                                       // BRA.W	$1800C
  DEF_ROMLOC(1873E) : move_toreg_32(0x64, &D0); // MOVEQ.L	$64,D0
  DEF_ROMLOC(18740) : rom_1CE42();              // BSR.W	$1CE42
  DEF_ROMLOC(18744)
      : move_tomem_8(0xFFFFFFFF, A0 + 0x3D); // MOVE.B	#$FF,61(A0)
  DEF_ROMLOC(1874A) : return;                // RTS
}
ROMFUNC(rom_1874C) {
  DEF_ROMLOC(1874C) : move_toreg_32(0xFFFFFFFE, &D0); // MOVEQ.L	$FE,D0
  DEF_ROMLOC(1874E)
      : cmp_tomem_16(0x1E48, A0 + 0x30);          // CMPI.W
                                                  // #$1E48,48(A0)
  DEF_ROMLOC(18754) : if (CCR_CS) goto rom_18762; // BCS.B	$18762
  DEF_ROMLOC(18756)
      : move_tomem_16(0x1E48, A0 + 0x30);     // MOVE.W
                                              // #$1E48,48(A0)
  DEF_ROMLOC(1875C) : clr_mem_16(A0 + 0x10);  // CLR.W	16(A0)
  DEF_ROMLOC(18760) : add_toreg_16(0x1, &D0); // ADDQ.W	#$01,D0
  DEF_ROMLOC(18762)
      : cmp_tomem_16(0x500, A0 + 0x38);           // CMPI.W	#$0500,56(A0)
  DEF_ROMLOC(18768) : if (CCR_GT) goto rom_18776; // BGT.B	$18776
  DEF_ROMLOC(1876A)
      : move_tomem_16(0x500, A0 + 0x38);           // MOVE.W
                                                   // #$0500,56(A0)
  DEF_ROMLOC(18770) : clr_mem_16(A0 + 0x12);       // CLR.W	18(A0)
  DEF_ROMLOC(18774) : add_toreg_16(0x1, &D0);      // ADDQ.W	#$01,D0
  DEF_ROMLOC(18776) : if (!CCR_EQ) goto rom_18788; // BNE.B	$18788
  DEF_ROMLOC(18778)
      : move_tomem_16(0x140, A0 + 0x10); // MOVE.W
                                         // #$0140,16(A0)
  DEF_ROMLOC(1877E)
      : move_tomem_16(0xFFFFFE00, A0 + 0x12);      // MOVE.W	#$FE00,18(A0)
  DEF_ROMLOC(18784) : add_tomem_8(0x2, A0 + 0x25); // ADDQ.B	#$02,37(A0)
  DEF_ROMLOC(18788) : rom_186E4();
  return; // BRA.W	$186E4
}
ROMFUNC(rom_1878C) {
  DEF_ROMLOC(1878C) : move_toreg_32(0xFFFFFFFE, &D0); // MOVEQ.L	$FE,D0
  DEF_ROMLOC(1878E)
      : cmp_tomem_16(0x1E70, A0 + 0x30);          // CMPI.W
                                                  // #$1E70,48(A0)
  DEF_ROMLOC(18794) : if (CCR_CS) goto rom_187A2; // BCS.B	$187A2
  DEF_ROMLOC(18796)
      : move_tomem_16(0x1E70, A0 + 0x30);     // MOVE.W
                                              // #$1E70,48(A0)
  DEF_ROMLOC(1879C) : clr_mem_16(A0 + 0x10);  // CLR.W	16(A0)
  DEF_ROMLOC(187A0) : add_toreg_16(0x1, &D0); // ADDQ.W	#$01,D0
  DEF_ROMLOC(187A2)
      : cmp_tomem_16(0x4C0, A0 + 0x38);           // CMPI.W	#$04C0,56(A0)
  DEF_ROMLOC(187A8) : if (CCR_GT) goto rom_187B6; // BGT.B	$187B6
  DEF_ROMLOC(187AA)
      : move_tomem_16(0x4C0, A0 + 0x38);           // MOVE.W
                                                   // #$04C0,56(A0)
  DEF_ROMLOC(187B0) : clr_mem_16(A0 + 0x12);       // CLR.W	18(A0)
  DEF_ROMLOC(187B4) : add_toreg_16(0x1, &D0);      // ADDQ.W	#$01,D0
  DEF_ROMLOC(187B6) : if (!CCR_EQ) goto rom_187C6; // BNE.B	$187C6
  DEF_ROMLOC(187B8)
      : move_tomem_16(0xFFFFFE80, A0 + 0x12);      // MOVE.W	#$FE80,18(A0)
  DEF_ROMLOC(187BE) : add_tomem_8(0x2, A0 + 0x25); // ADDQ.B	#$02,37(A0)
  DEF_ROMLOC(187C2) : clr_mem_8(A0 + 0x3F);        // CLR.B	63(A0)
  DEF_ROMLOC(187C6) : rom_186E4();
  return; // BRA.W	$186E4
}
ROMFUNC(rom_187CA) {
  DEF_ROMLOC(187CA)
      : cmp_tomem_16(0x100, A0 + 0x38);           // CMPI.W	#$0100,56(A0)
  DEF_ROMLOC(187D0) : if (CCR_GT) goto rom_187FA; // BGT.B	$187FA
  DEF_ROMLOC(187D2)
      : move_tomem_16(0x100, A0 + 0x38); // MOVE.W
                                         // #$0100,56(A0)
  DEF_ROMLOC(187D8)
      : move_tomem_16(0x140, A0 + 0x10); // MOVE.W
                                         // #$0140,16(A0)
  DEF_ROMLOC(187DE)
      : move_tomem_16(0xFFFFFF80, A0 + 0x12);      // MOVE.W	#$FF80,18(A0)
  DEF_ROMLOC(187E4) : tst_mem_8(A0 + 0x3D);        // TST.B	61(A0)
  DEF_ROMLOC(187E8) : if (CCR_EQ) goto rom_187F2;  // BEQ.B	$187F2
  DEF_ROMLOC(187EA) : asl_mem_16(A0 + 0x10);       // ASL.W	16(A0)
  DEF_ROMLOC(187EE) : asl_mem_16(A0 + 0x12);       // ASL.W	18(A0)
  DEF_ROMLOC(187F2) : add_tomem_8(0x2, A0 + 0x25); // ADDQ.B	#$02,37(A0)
  rom_186E4();
  return;                                           // BRA.W	$186E4
  DEF_ROMLOC(187FA) : bset_tomem_8(0x0, A0 + 0x22); // BSET.B	#$00,34(A0)
  DEF_ROMLOC(18800) : add_tomem_8(0x2, A0 + 0x3F);  // ADDQ.B	#$02,63(A0)
  DEF_ROMLOC(18804)
      : move_toreg_8(read_8(A0 + 0x3F), &D0);       // MOVE.B	63(A0),D0
  DEF_ROMLOC(18808) : rom_29D2();                   // JSR	$000029D2
  DEF_ROMLOC(1880E) : tst_reg_16(&D1);              // TST.W	D1
  DEF_ROMLOC(18810) : if (CCR_PL) goto rom_18818;   // BPL.B	$18818
  DEF_ROMLOC(18812) : bclr_tomem_8(0x0, A0 + 0x22); // BCLR.B	#$00,34(A0)
  DEF_ROMLOC(18818) : asr_toreg_16(0x4, &D0);       // ASR.W	#$04,D0
  DEF_ROMLOC(1881A) : swap_reg_16(&D0);             // SWAP.W	D0
  DEF_ROMLOC(1881C) : clr_reg_16(&D0);              // CLR.W	D0
  DEF_ROMLOC(1881E)
      : add_toreg_32(read_32(A0 + 0x30), &D0);     // ADD.L	48(A0),D0
  DEF_ROMLOC(18822) : swap_reg_16(&D0);            // SWAP.W	D0
  DEF_ROMLOC(18824) : move_tomem_16(D0, A0 + 0x8); // MOVE.W	D0,8(A0)
  DEF_ROMLOC(18828)
      : move_toreg_16(read_16(A0 + 0x12), &D0); // MOVE.W	18(A0),D0
  DEF_ROMLOC(1882C)
      : move_toreg_16(read_16(0xFFFFD00C), &D1); // MOVE.W	$D00C,D1
  DEF_ROMLOC(18830)
      : sub_toreg_16(read_16(A0 + 0xC), &D1);      // SUB.W	12(A0),D1
  DEF_ROMLOC(18834) : if (CCR_CS) goto rom_1884E;  // BCS.B	$1884E
  DEF_ROMLOC(18836) : sub_toreg_16(0x48, &D1);     // SUBI.W	#$0048,D1
  DEF_ROMLOC(1883A) : if (CCR_CS) goto rom_1884E;  // BCS.B	$1884E
  DEF_ROMLOC(1883C) : asr_toreg_16(0x1, &D0);      // ASR.W	#$01,D0
  DEF_ROMLOC(1883E) : sub_toreg_16(0x28, &D1);     // SUBI.W	#$0028,D1
  DEF_ROMLOC(18842) : if (CCR_CS) goto rom_1884E;  // BCS.B	$1884E
  DEF_ROMLOC(18844) : asr_toreg_16(0x1, &D0);      // ASR.W	#$01,D0
  DEF_ROMLOC(18846) : sub_toreg_16(0x28, &D1);     // SUBI.W	#$0028,D1
  DEF_ROMLOC(1884A) : if (CCR_CS) goto rom_1884E;  // BCS.B	$1884E
  DEF_ROMLOC(1884C) : move_toreg_32(0x0, &D0);     // MOVEQ.L	$00,D0
  DEF_ROMLOC(1884E) : ext_reg_32(&D0);             // EXT.L	D0
  DEF_ROMLOC(18850) : asl_toreg_32(0x8, &D0);      // ASL.L	#$08,D0
  DEF_ROMLOC(18852) : tst_mem_8(A0 + 0x3D);        // TST.B	61(A0)
  DEF_ROMLOC(18856) : if (CCR_EQ) goto rom_1885A;  // BEQ.B	$1885A
  DEF_ROMLOC(18858) : add_toreg_32(D0, &D0);       // ADD.L	D0,D0
  DEF_ROMLOC(1885A) : add_tomem_32(D0, A0 + 0x38); // ADD.L	D0,56(A0)
  DEF_ROMLOC(1885E)
      : move_tomem_16(read_16(A0 + 0x38), A0 + 0xC); // MOVE.W	56(A0),12(A0)
  rom_186F4();                                       // BRA.W	$186F4
}
ROMFUNC(rom_18868) {
  DEF_ROMLOC(18868) : move_toreg_32(0xFFFFFFFE, &D0); // MOVEQ.L	$FE,D0
  DEF_ROMLOC(1886A)
      : cmp_tomem_16(0x1F4C, A0 + 0x30);          // CMPI.W
                                                  // #$1F4C,48(A0)
  DEF_ROMLOC(18870) : if (CCR_CS) goto rom_1887E; // BCS.B	$1887E
  DEF_ROMLOC(18872)
      : move_tomem_16(0x1F4C, A0 + 0x30);             // MOVE.W
                                                      // #$1F4C,48(A0)
  DEF_ROMLOC(18878) : clr_mem_16(A0 + 0x10);          // CLR.W	16(A0)
  DEF_ROMLOC(1887C) : add_toreg_16(0x1, &D0);         // ADDQ.W	#$01,D0
  DEF_ROMLOC(1887E) : cmp_tomem_16(0xC0, A0 + 0x38);  // CMPI.W	#$00C0,56(A0)
  DEF_ROMLOC(18884) : if (CCR_GT) goto rom_18892;     // BGT.B	$18892
  DEF_ROMLOC(18886) : move_tomem_16(0xC0, A0 + 0x38); // MOVE.W	#$00C0,56(A0)
  DEF_ROMLOC(1888C) : clr_mem_16(A0 + 0x12);          // CLR.W	18(A0)
  DEF_ROMLOC(18890) : add_toreg_16(0x1, &D0);         // ADDQ.W	#$01,D0
  DEF_ROMLOC(18892) : if (!CCR_EQ) goto rom_1889E;    // BNE.B	$1889E
  DEF_ROMLOC(18894) : add_tomem_8(0x2, A0 + 0x25);    // ADDQ.B	#$02,37(A0)
  DEF_ROMLOC(18898) : bclr_tomem_8(0x0, A0 + 0x22);   // BCLR.B	#$00,34(A0)
  DEF_ROMLOC(1889E) : rom_186E4();
  return; // BRA.W	$186E4
}
ROMFUNC(rom_188A2) {
  DEF_ROMLOC(188A2) : tst_mem_8(A0 + 0x3D);           // TST.B	61(A0)
  DEF_ROMLOC(188A6) : if (!CCR_EQ) goto rom_188BE;    // BNE.B	$188BE
  DEF_ROMLOC(188A8) : cmp_tomem_16(0x1EC8, A1 + 0x8); // CMPI.W	#$1EC8,8(A1)
  DEF_ROMLOC(188AE) : if (CCR_LT) goto rom_188D6;     // BLT.B	$188D6
  DEF_ROMLOC(188B0) : cmp_tomem_16(0xF0, A1 + 0xC);   // CMPI.W	#$00F0,12(A1)
  DEF_ROMLOC(188B6) : if (CCR_GT) goto rom_188D6;     // BGT.B	$188D6
  DEF_ROMLOC(188B8) : move_tomem_8(0x32, A0 + 0x3C);  // MOVE.B	#$32,60(A0)
  DEF_ROMLOC(188BE) : move_toreg_16(0x82, &D0);       // MOVE.W	#$0082,D0
  DEF_ROMLOC(188C2) : play_sound();                   // JSR	$0000138E
  DEF_ROMLOC(188C8) : clr_mem_8(0xFFFFF7AA);          // CLR.B	$F7AA
  DEF_ROMLOC(188CC) : bset_tomem_8(0x0, A0 + 0x22);   // BSET.B	#$00,34(A0)
  DEF_ROMLOC(188D2) : add_tomem_8(0x2, A0 + 0x25);    // ADDQ.B	#$02,37(A0)
  DEF_ROMLOC(188D6) : rom_186E4();
  return; // BRA.W	$186E4
}
ROMFUNC(rom_188DA) {
  DEF_ROMLOC(188DA) : tst_mem_8(A0 + 0x3D);        // TST.B	61(A0)
  DEF_ROMLOC(188DE) : if (!CCR_EQ) goto rom_188E6; // BNE.B	$188E6
  DEF_ROMLOC(188E0) : sub_tomem_8(0x1, A0 + 0x3C); // SUBQ.B	#$01,60(A0)
  DEF_ROMLOC(188E4) : if (!CCR_EQ) goto rom_188FE; // BNE.B	$188FE
  DEF_ROMLOC(188E6) : clr_mem_8(A0 + 0x3C);        // CLR.B	60(A0)
  DEF_ROMLOC(188EA)
      : move_tomem_16(0x400, A0 + 0x10); // MOVE.W
                                         // #$0400,16(A0)
  DEF_ROMLOC(188F0)
      : move_tomem_16(0xFFFFFFC0, A0 + 0x12);      // MOVE.W	#$FFC0,18(A0)
  DEF_ROMLOC(188F6) : clr_mem_8(A0 + 0x3D);        // CLR.B	61(A0)
  DEF_ROMLOC(188FA) : add_tomem_8(0x2, A0 + 0x25); // ADDQ.B	#$02,37(A0)
  DEF_ROMLOC(188FE) : rom_186E4();                 // BRA.W	$186E4
}
ROMFUNC(rom_18902) {
  DEF_ROMLOC(18902)
      : cmp_tomem_16(0x2030, 0xFFFFF72A);            // CMPI.W
                                                     // #$2030,$F72A
  DEF_ROMLOC(18908) : if (CCR_CC) goto rom_18910;    // BCC.B	$18910
  DEF_ROMLOC(1890A) : add_tomem_16(0x2, 0xFFFFF72A); // ADDQ.W	#$02,$F72A
  goto rom_18916;                                    // BRA.B	$18916
  DEF_ROMLOC(18910) : tst_mem_8(A0 + 0x1);           // TST.B	1(A0)
  DEF_ROMLOC(18914) : if (CCR_PL) goto rom_1891A;    // BPL.B	$1891A
  DEF_ROMLOC(18916) : rom_186E4();
  return; // BRA.W	$186E4
  DEF_ROMLOC(1891A) : rom_DCCE();
  return; // JMP	$0000DCCE
}
ROMFUNC(rom_18920) {
  DEF_ROMLOC(18920)
      : move_toreg_32(read_32(A0 + 0x34), &A1);      // MOVEA.L	52(A0),A1
  DEF_ROMLOC(18924) : move_toreg_8(read_8(A1), &D0); // MOVE.B	(A1),D0
  DEF_ROMLOC(18926) : cmp_toreg_8(read_8(A0), &D0);  // CMP.B	(A0),D0
  DEF_ROMLOC(18928) : if (!CCR_EQ) {
    rom_18968();
    return;
  }                                            // BNE.B	$18968
  DEF_ROMLOC(1892A) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(1892C)
      : move_toreg_8(read_8(A1 + 0x25), &D0);       // MOVE.B	37(A1),D0
  DEF_ROMLOC(18930) : move_toreg_32(0x1, &D1);      // MOVEQ.L	$01,D1
  DEF_ROMLOC(18932) : tst_mem_8(A0 + 0x3D);         // TST.B	61(A0)
  DEF_ROMLOC(18936) : if (CCR_EQ) goto rom_1893C;   // BEQ.B	$1893C
  DEF_ROMLOC(18938) : move_toreg_32(0xA, &D1);      // MOVEQ.L	$0A,D1
  goto rom_18950;                                   // BRA.B	$18950
  DEF_ROMLOC(1893C) : tst_mem_8(A1 + 0x20);         // TST.B	32(A1)
  DEF_ROMLOC(18940) : if (!CCR_EQ) goto rom_18946;  // BNE.B	$18946
  DEF_ROMLOC(18942) : move_toreg_32(0x5, &D1);      // MOVEQ.L	$05,D1
  goto rom_18950;                                   // BRA.B	$18950
  DEF_ROMLOC(18946) : cmp_tomem_8(0x4, 0xFFFFD024); // CMPI.B	#$04,$D024
  DEF_ROMLOC(1894C) : if (CCR_CS) goto rom_18950;   // BCS.B	$18950
  DEF_ROMLOC(1894E) : move_toreg_32(0x4, &D1);      // MOVEQ.L	$04,D1
  DEF_ROMLOC(18950) : move_tomem_8(D1, A0 + 0x1C);  // MOVE.B	D1,28(A0)
  DEF_ROMLOC(18954) : cmp_toreg_8(0xE, &D0);        // CMPI.B	#$0E,D0
  DEF_ROMLOC(18958) : if (!CCR_EQ) goto rom_18966;  // BNE.B	$18966
  DEF_ROMLOC(1895A) : move_tomem_8(0x6, A0 + 0x1C); // MOVE.B	#$06,28(A0)
  DEF_ROMLOC(18960) : tst_mem_8(A0 + 0x1);          // TST.B	1(A0)
  DEF_ROMLOC(18964) : if (CCR_PL) {
    rom_18968();
    return;
  } // BPL.B	$18968
  DEF_ROMLOC(18966) : rom_189A8();
  return; // BRA.B	$189A8
}
ROMFUNC(rom_18968) {
  DEF_ROMLOC(18968) : rom_DCCE();
  return; // JMP	$0000DCCE
}
ROMFUNC(rom_1896E) {
  DEF_ROMLOC(1896E) : move_tomem_8(0x7, A0 + 0x1C); // MOVE.B	#$07,28(A0)
  DEF_ROMLOC(18974)
      : move_toreg_32(read_32(A0 + 0x34), &A1);      // MOVEA.L	52(A0),A1
  DEF_ROMLOC(18978) : move_toreg_8(read_8(A1), &D0); // MOVE.B	(A1),D0
  DEF_ROMLOC(1897A) : cmp_toreg_8(read_8(A0), &D0);  // CMP.B	(A0),D0
  DEF_ROMLOC(1897C) : if (!CCR_EQ) goto rom_189A2;   // BNE.B	$189A2
  DEF_ROMLOC(1897E) : cmp_tomem_8(0xE, A1 + 0x25);   // CMPI.B	#$0E,37(A1)
  DEF_ROMLOC(18984) : if (!CCR_EQ) goto rom_189A0;   // BNE.B	$189A0
  DEF_ROMLOC(18986) : move_tomem_8(0xB, A0 + 0x1C);  // MOVE.B	#$0B,28(A0)
  DEF_ROMLOC(1898C) : tst_mem_8(A0 + 0x1);           // TST.B	1(A0)
  DEF_ROMLOC(18990) : if (CCR_PL) goto rom_189A2;    // BPL.B	$189A2
  DEF_ROMLOC(18992) : goto rom_189A0;                // BRA.B	$189A0
  DEF_ROMLOC(18994) : tst_mem_16(A1 + 0x10);         // TST.W	16(A1)
  DEF_ROMLOC(18998) : if (CCR_EQ) goto rom_189A0;    // BEQ.B	$189A0
  DEF_ROMLOC(1899A) : move_tomem_8(0x8, A0 + 0x1C);  // MOVE.B	#$08,28(A0)
  DEF_ROMLOC(189A0) : rom_189A8();
  return; // BRA.B	$189A8
  DEF_ROMLOC(189A2) : rom_DCCE();
  return; // JMP	$0000DCCE
}
ROMFUNC(rom_189A8) {
  DEF_ROMLOC(189A8) : move_toreg_32(0x18468, &A1); // LEA.L	$00018468,A1
  DEF_ROMLOC(189AE) : animate_sprite();                  // JSR	$0000ADA2
  DEF_ROMLOC(189B4)
      : move_toreg_32(read_32(A0 + 0x34), &A1); // MOVEA.L	52(A0),A1
  DEF_ROMLOC(189B8)
      : move_tomem_16(read_16(A1 + 0x8), A0 + 0x8); // MOVE.W	8(A1),8(A0)
  DEF_ROMLOC(189BE)
      : move_tomem_16(read_16(A1 + 0xC), A0 + 0xC); // MOVE.W	12(A1),12(A0)
  DEF_ROMLOC(189C4)
      : move_tomem_8(read_8(A1 + 0x22), A0 + 0x22); // MOVE.B	34(A1),34(A0)
  DEF_ROMLOC(189CA) : move_toreg_32(0x3, &D0);      // MOVEQ.L	$03,D0
  DEF_ROMLOC(189CC) : and_toreg_8(read_8(A0 + 0x22), &D0); // AND.B
                                                           // 34(A0),D0
  DEF_ROMLOC(189D0)
      : and_tomem_8(0xFFFFFFFC, A0 + 0x1);      // ANDI.B
                                                // #$FC,1(A0)
  DEF_ROMLOC(189D6) : or_tomem_8(D0, A0 + 0x1); // OR.B	D0,1(A0)
  DEF_ROMLOC(189DA) : rom_DC92();
  return; // JMP	$0000DC92
}