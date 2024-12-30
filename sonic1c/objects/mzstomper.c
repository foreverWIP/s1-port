// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"


ROMFUNC(rom_BD06) {
  u8 switchindex = 0;
  DEF_ROMLOC(BD06) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(BD08) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(BD0C)
      : move_toreg_16(read_16(0xBD14 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(BD10): goto rom_BD14 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(BD10) : switch (switchindex) {
  case 0:
    rom_BD3C();
    break;
  case 1:
    rom_BE22();
    break;
  case 2:
    rom_BE88();
    break;
  case 3:
    rom_BE9A();
    break;
  case 4:
    rom_BE6C();
    break;
  }
}
ROMFUNC(rom_BD1E) {
  DEF_ROMLOC(BD1E) : or_toreg_8(0x0, &D0); // ORI.B	#$00,D0
  rom_BD22();                              // Detected flow into next function
}
ROMFUNC(rom_BD22) {
  DEF_ROMLOC(BD22) : and_toreg_8(0x4, &D0); // ANDI.B	#$04,D0
  DEF_ROMLOC(BD26) : move_toreg_8(D1, &D6); // MOVE.B	D1,D6
  rom_BD3C();                               // Detected flow into next function
}
ROMFUNC(rom_BD3C) {
  DEF_ROMLOC(BD3C) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(BD3E)
      : move_toreg_8(read_8(A0 + 0x28), &D0);   // MOVE.B	40(A0),D0
  DEF_ROMLOC(BD42) : if (CCR_PL) goto rom_BD58; // BPL.B	$BD58
  DEF_ROMLOC(BD44) : and_toreg_16(0x7F, &D0);   // ANDI.W	#$007F,D0
  DEF_ROMLOC(BD48) : add_toreg_16(D0, &D0);     // ADD.W	D0,D0
  DEF_ROMLOC(BD4A)
      : move_toreg_32(0xBD1E + (s16)(D0 & 0xffff),
                      &A2); // LEA.L	-46(PC,D0),A2
  DEF_ROMLOC(BD4E)
      : move_tomem_8(read_8(A2++), A0 + 0x3A);        // MOVE.B	(A2)+,58(A0)
  DEF_ROMLOC(BD52) : move_toreg_8(read_8(A2++), &D0); // MOVE.B	(A2)+,D0
  DEF_ROMLOC(BD54) : move_tomem_8(D0, A0 + 0x28);     // MOVE.B	D0,40(A0)
  DEF_ROMLOC(BD58) : and_toreg_8(0xF, &D0);           // ANDI.B	#$0F,D0
  DEF_ROMLOC(BD5C) : add_toreg_16(D0, &D0);           // ADD.W	D0,D0
  DEF_ROMLOC(BD5E)
      : move_toreg_16(read_16(0xBD2E + (s16)(D0 & 0xffff)),
                      &D2);                        // MOVE.W	-50(PC,D0),D2
  DEF_ROMLOC(BD62) : tst_reg_16(&D0);              // TST.W	D0
  DEF_ROMLOC(BD64) : if (!CCR_EQ) goto rom_BD6A;   // BNE.B	$BD6A
  DEF_ROMLOC(BD66) : move_tomem_16(D2, A0 + 0x32); // MOVE.W	D2,50(A0)
  DEF_ROMLOC(BD6A) : move_toreg_32(0xBD22, &A2);   // LEA.L	$0000BD22,A2
  DEF_ROMLOC(BD70) : move_toreg_32(A0, &A1);       // MOVEA.L	A0,A1
  DEF_ROMLOC(BD72) : move_toreg_32(0x3, &D1);      // MOVEQ.L	$03,D1
  goto rom_BD7E;                                   // BRA.B	$BD7E
  DEF_ROMLOC(BD76) : rom_E130();                   // BSR.W	$E130
  DEF_ROMLOC(BD7A) : if (!CCR_EQ) goto rom_BE02;   // BNE.W	$BE02
  DEF_ROMLOC(BD7E)
      : move_tomem_8(read_8(A2++), A1 + 0x24);     // MOVE.B	(A2)+,36(A1)
  DEF_ROMLOC(BD82) : move_tomem_8(0x31, A1 + 0x0); // MOVE.B	#$31,0(A1)
  DEF_ROMLOC(BD88)
      : move_tomem_16(read_16(A0 + 0x8), A1 + 0x8);   // MOVE.W	8(A0),8(A1)
  DEF_ROMLOC(BD8E) : move_toreg_8(read_8(A2++), &D0); // MOVE.B	(A2)+,D0
  DEF_ROMLOC(BD90) : ext_reg_16(&D0);                 // EXT.W	D0
  DEF_ROMLOC(BD92)
      : add_toreg_16(read_16(A0 + 0xC), &D0);     // ADD.W	12(A0),D0
  DEF_ROMLOC(BD96) : move_tomem_16(D0, A1 + 0xC); // MOVE.W	D0,12(A1)
  DEF_ROMLOC(BD9A)
      : move_tomem_32(0xC1D8, A1 + 0x4);             // MOVE.L	#$0000C1D8,4(A1)
  DEF_ROMLOC(BDA2) : move_tomem_16(0x300, A1 + 0x2); // MOVE.W	#$0300,2(A1)
  DEF_ROMLOC(BDA8) : move_tomem_8(0x4, A1 + 0x1);    // MOVE.B	#$04,1(A1)
  DEF_ROMLOC(BDAE)
      : move_tomem_16(read_16(A1 + 0xC), A1 + 0x30); // MOVE.W	12(A1),48(A1)
  DEF_ROMLOC(BDB4)
      : move_tomem_8(read_8(A0 + 0x28), A1 + 0x28); // MOVE.B	40(A0),40(A1)
  DEF_ROMLOC(BDBA) : move_tomem_8(0x10, A1 + 0x19); // MOVE.B	#$10,25(A1)
  DEF_ROMLOC(BDC0) : move_tomem_16(D2, A1 + 0x34);  // MOVE.W	D2,52(A1)
  DEF_ROMLOC(BDC4) : move_tomem_8(0x4, A1 + 0x18);  // MOVE.B	#$04,24(A1)
  DEF_ROMLOC(BDCA)
      : move_tomem_8(read_8(A2++), A1 + 0x1A);    // MOVE.B	(A2)+,26(A1)
  DEF_ROMLOC(BDCE) : cmp_tomem_8(0x1, A1 + 0x1A); // CMPI.B	#$01,26(A1)
  DEF_ROMLOC(BDD4) : if (!CCR_EQ) goto rom_BDF4;  // BNE.B	$BDF4
  DEF_ROMLOC(BDD6) : sub_toreg_16(0x1, &D1);      // SUBQ.W	#$01,D1
  DEF_ROMLOC(BDD8)
      : move_toreg_8(read_8(A0 + 0x28), &D0);       // MOVE.B	40(A0),D0
  DEF_ROMLOC(BDDC) : and_toreg_16(0xF0, &D0);       // ANDI.W	#$00F0,D0
  DEF_ROMLOC(BDE0) : cmp_toreg_16(0x20, &D0);       // CMPI.W	#$0020,D0
  DEF_ROMLOC(BDE4) : if (CCR_EQ) goto rom_BD7E;     // BEQ.B	$BD7E
  DEF_ROMLOC(BDE6) : move_tomem_8(0x38, A1 + 0x19); // MOVE.B	#$38,25(A1)
  DEF_ROMLOC(BDEC)
      : move_tomem_8(0xFFFFFF90, A1 + 0x20);       // MOVE.B	#$90,32(A1)
  DEF_ROMLOC(BDF2) : add_toreg_16(0x1, &D1);       // ADDQ.W	#$01,D1
  DEF_ROMLOC(BDF4) : move_tomem_32(A0, A1 + 0x3C); // MOVE.L	A0,60(A1)
  DEF_ROMLOC(BDF8) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_BD76;                                 // DBF.W	D1,$BD76
  DEF_ROMLOC(BDFC) : move_tomem_8(0x3, A1 + 0x18); // MOVE.B	#$03,24(A1)
  DEF_ROMLOC(BE02) : move_toreg_32(0x0, &D0);      // MOVEQ.L	$00,D0
  DEF_ROMLOC(BE04)
      : move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B	40(A0),D0
  DEF_ROMLOC(BE08) : lsr_toreg_16(0x3, &D0);  // LSR.W	#$03,D0
  DEF_ROMLOC(BE0A) : and_toreg_8(0xE, &D0);   // ANDI.B	#$0E,D0
  DEF_ROMLOC(BE0E)
      : move_toreg_32(0xBE1C + (s16)(D0 & 0xffff),
                      &A2); // LEA.L	12(PC,D0),A2
  DEF_ROMLOC(BE12)
      : move_tomem_8(read_8(A2++), A0 + 0x19); // MOVE.B	(A2)+,25(A0)
  DEF_ROMLOC(BE16)
      : move_tomem_8(read_8(A2++), A0 + 0x1A); // MOVE.B	(A2)+,26(A0)
  rom_BE22();                                  // BRA.B	$BE22
}
ROMFUNC(rom_BE1C) {
  DEF_ROMLOC(BE1C) : move_toreg_16(D0, &D4); // MOVE.W	D0,D4
  DEF_ROMLOC(BE1E) : move_toreg_16(A1, &D0); // MOVE.W	A1,D0
  rom_BE22();                                // Detected flow into next function
}
ROMFUNC(rom_BE22) {
  DEF_ROMLOC(BE22) : rom_BEBE(); // BSR.W	$BEBE
  DEF_ROMLOC(BE26)
      : move_tomem_16(read_16(A0 + 0xC), 0xFFFFF7A4); // MOVE.W	12(A0),$F7A4
  DEF_ROMLOC(BE2C) : move_toreg_32(0x0, &D1);         // MOVEQ.L	$00,D1
  DEF_ROMLOC(BE2E)
      : move_toreg_8(read_8(A0 + 0x19), &D1); // MOVE.B	25(A0),D1
  DEF_ROMLOC(BE32) : add_toreg_16(0xB, &D1);  // ADDI.W	#$000B,D1
  DEF_ROMLOC(BE36) : move_toreg_16(0xC, &D2); // MOVE.W	#$000C,D2
  DEF_ROMLOC(BE3A) : move_toreg_16(0xD, &D3); // MOVE.W	#$000D,D3
  DEF_ROMLOC(BE3E)
      : move_toreg_16(read_16(A0 + 0x8), &D4);       // MOVE.W	8(A0),D4
  DEF_ROMLOC(BE42) : rom_10062();                    // BSR.W	$10062
  DEF_ROMLOC(BE46) : btst_tomem_8(0x3, A0 + 0x22);   // BTST.B	#$03,34(A0)
  DEF_ROMLOC(BE4C) : if (CCR_EQ) goto rom_BE64;      // BEQ.B	$BE64
  DEF_ROMLOC(BE4E) : cmp_tomem_8(0x10, A0 + 0x32);   // CMPI.B	#$10,50(A0)
  DEF_ROMLOC(BE54) : if (CCR_CC) goto rom_BE64;      // BCC.B	$BE64
  DEF_ROMLOC(BE56) : move_toreg_32(A0, &A2);         // MOVEA.L	A0,A2
  DEF_ROMLOC(BE58) : move_toreg_32(0xFFFFD000, &A0); // LEA.L	$D000,A0
  DEF_ROMLOC(BE5C) : rom_1B84E();                    // JSR	$0001B84E
  DEF_ROMLOC(BE62) : move_toreg_32(A2, &A0);         // MOVEA.L	A2,A0
  DEF_ROMLOC(BE64) : rom_DC92();                     // BSR.W	$DC92
  rom_BE9E();                                        // BRA.W	$BE9E
}
ROMFUNC(rom_BE6C) {
  DEF_ROMLOC(BE6C)
      : move_tomem_8(0xFFFFFF80, A0 + 0x16);      // MOVE.B	#$80,22(A0)
  DEF_ROMLOC(BE72) : bset_tomem_8(0x4, A0 + 0x1); // BSET.B	#$04,1(A0)
  DEF_ROMLOC(BE78)
      : move_toreg_32(read_32(A0 + 0x3C), &A1); // MOVEA.L	60(A0),A1
  DEF_ROMLOC(BE7C)
      : move_toreg_8(read_8(A1 + 0x32), &D0);     // MOVE.B	50(A1),D0
  DEF_ROMLOC(BE80) : lsr_toreg_8(0x5, &D0);       // LSR.B	#$05,D0
  DEF_ROMLOC(BE82) : add_toreg_8(0x3, &D0);       // ADDQ.B	#$03,D0
  DEF_ROMLOC(BE84) : move_tomem_8(D0, A0 + 0x1A); // MOVE.B	D0,26(A0)
  rom_BE88(); // Detected flow into next function
}
ROMFUNC(rom_BE88) {
  DEF_ROMLOC(BE88)
      : move_toreg_32(read_32(A0 + 0x3C), &A1); // MOVEA.L	60(A0),A1
  DEF_ROMLOC(BE8C) : move_toreg_32(0x0, &D0);   // MOVEQ.L	$00,D0
  DEF_ROMLOC(BE8E)
      : move_toreg_8(read_8(A1 + 0x32), &D0); // MOVE.B	50(A1),D0
  DEF_ROMLOC(BE92)
      : add_toreg_16(read_16(A0 + 0x30), &D0);    // ADD.W	48(A0),D0
  DEF_ROMLOC(BE96) : move_tomem_16(D0, A0 + 0xC); // MOVE.W	D0,12(A0)
  rom_BE9A(); // Detected flow into next function
}
ROMFUNC(rom_BE9A) {
  DEF_ROMLOC(BE9A) : rom_DC92(); // BSR.W	$DC92
  rom_BE9E();                    // Detected flow into next function
}
ROMFUNC(rom_BE9E) {
  DEF_ROMLOC(BE9E)
      : move_toreg_16(read_16(A0 + 0x8), &D0);      // MOVE.W	8(A0),D0
  DEF_ROMLOC(BEA2) : and_toreg_16(0xFFFFFF80, &D0); // ANDI.W	#$FF80,D0
  DEF_ROMLOC(BEA6)
      : move_toreg_16(read_16(0xFFFFF700), &D1);    // MOVE.W	$F700,D1
  DEF_ROMLOC(BEAA) : sub_toreg_16(0x80, &D1);       // SUBI.W	#$0080,D1
  DEF_ROMLOC(BEAE) : and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
  DEF_ROMLOC(BEB2) : sub_toreg_16(D1, &D0);         // SUB.W	D1,D0
  DEF_ROMLOC(BEB4) : cmp_toreg_16(0x280, &D0);      // CMPI.W	#$0280,D0
  DEF_ROMLOC(BEB8) : if (CCR_HI) {
    rom_DCCE();
    return;
  }                          // BHI.W	$DCCE
  DEF_ROMLOC(BEBC) : return; // RTS
}
ROMFUNC(rom_BEBE) {
  u8 switchindex = 0;
  DEF_ROMLOC(BEBE)
      : move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B	40(A0),D0
  DEF_ROMLOC(BEC2) : and_toreg_16(0xF, &D0);
  switchindex = D0;                         // ANDI.W	#$000F,D0
  DEF_ROMLOC(BEC6) : add_toreg_16(D0, &D0); // ADD.W	D0,D0
  DEF_ROMLOC(BEC8)
      : move_toreg_16(read_16(0xBED0 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(BECC): goto rom_BED0 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(BECC) : switch (switchindex) {
  case 0:
    rom_BEDE();
    break;
  case 1:
    rom_BF7A();
    break;
  case 2:
    rom_BF7A();
    break;
  case 3:
    rom_C00A();
    break;
  case 4:
    rom_BF7A();
    break;
  case 5:
    rom_C00A();
    break;
  case 6:
    rom_BF7A();
    break;
  }
}
ROMFUNC(rom_BF6A) {
  DEF_ROMLOC(BF6A) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(BF6C)
      : move_toreg_8(read_8(A0 + 0x32), &D0); // MOVE.B	50(A0),D0
  DEF_ROMLOC(BF70)
      : add_toreg_16(read_16(A0 + 0x30), &D0);    // ADD.W	48(A0),D0
  DEF_ROMLOC(BF74) : move_tomem_16(D0, A0 + 0xC); // MOVE.W	D0,12(A0)
  DEF_ROMLOC(BF78) : return;                      // RTS
}
ROMFUNC(rom_BEDE) {
  DEF_ROMLOC(BEDE) : move_toreg_32(0xFFFFF7E0, &A2); // LEA.L	$F7E0,A2
  DEF_ROMLOC(BEE2) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(BEE4)
      : move_toreg_8(read_8(A0 + 0x3A), &D0); // MOVE.B	58(A0),D0
  DEF_ROMLOC(BEE8)
      : tst_mem_8((s32)A2 + (s8)0x0 + (s16)D0);    // TST.B	0(A2,D0)
  DEF_ROMLOC(BEEC) : if (CCR_EQ) goto rom_BF32;    // BEQ.B	$BF32
  DEF_ROMLOC(BEEE) : tst_mem_16(0xFFFFF7A4);       // TST.W	$F7A4
  DEF_ROMLOC(BEF2) : if (CCR_PL) goto rom_BEFC;    // BPL.B	$BEFC
  DEF_ROMLOC(BEF4) : cmp_tomem_8(0x10, A0 + 0x32); // CMPI.B	#$10,50(A0)
  DEF_ROMLOC(BEFA) : if (CCR_EQ) goto rom_BF2A;    // BEQ.B	$BF2A
  DEF_ROMLOC(BEFC) : tst_mem_16(A0 + 0x32);        // TST.W	50(A0)
  DEF_ROMLOC(BF00) : if (CCR_EQ) goto rom_BF2A;    // BEQ.B	$BF2A
  DEF_ROMLOC(BF02)
      : move_toreg_8(read_8(0xFFFFFE0F), &D0);      // MOVE.B	$FE0F,D0
  DEF_ROMLOC(BF06) : and_toreg_8(0xF, &D0);         // ANDI.B	#$0F,D0
  DEF_ROMLOC(BF0A) : if (!CCR_EQ) goto rom_BF1C;    // BNE.B	$BF1C
  DEF_ROMLOC(BF0C) : tst_mem_8(A0 + 0x1);           // TST.B	1(A0)
  DEF_ROMLOC(BF10) : if (CCR_PL) goto rom_BF1C;     // BPL.B	$BF1C
  DEF_ROMLOC(BF12) : move_toreg_16(0xC7, &D0);      // MOVE.W	#$00C7,D0
  DEF_ROMLOC(BF16) : rom_1394();                    // JSR	$00001394
  DEF_ROMLOC(BF1C) : sub_tomem_16(0x80, A0 + 0x32); // SUBI.W	#$0080,50(A0)
  DEF_ROMLOC(BF22) : if (CCR_CC) {
    rom_BF6A();
    return;
  }                                                 // BCC.B	$BF6A
  DEF_ROMLOC(BF24) : move_tomem_16(0x0, A0 + 0x32); // MOVE.W	#$0000,50(A0)
  DEF_ROMLOC(BF2A) : move_tomem_16(0x0, A0 + 0x12); // MOVE.W	#$0000,18(A0)
  rom_BF6A();
  return; // BRA.B	$BF6A
  DEF_ROMLOC(BF32)
      : move_toreg_16(read_16(A0 + 0x34), &D1); // MOVE.W	52(A0),D1
  DEF_ROMLOC(BF36)
      : cmp_toreg_16(read_16(A0 + 0x32), &D1); // CMP.W	50(A0),D1
  DEF_ROMLOC(BF3A) : if (CCR_EQ) {
    rom_BF6A();
    return;
  } // BEQ.B	$BF6A
  DEF_ROMLOC(BF3C)
      : move_toreg_16(read_16(A0 + 0x12), &D0);     // MOVE.W	18(A0),D0
  DEF_ROMLOC(BF40) : add_tomem_16(0x70, A0 + 0x12); // ADDI.W	#$0070,18(A0)
  DEF_ROMLOC(BF46) : add_tomem_16(D0, A0 + 0x32);   // ADD.W	D0,50(A0)
  DEF_ROMLOC(BF4A)
      : cmp_toreg_16(read_16(A0 + 0x32), &D1); // CMP.W	50(A0),D1
  DEF_ROMLOC(BF4E) : if (CCR_HI) {
    rom_BF6A();
    return;
  }                                                 // BHI.B	$BF6A
  DEF_ROMLOC(BF50) : move_tomem_16(D1, A0 + 0x32);  // MOVE.W	D1,50(A0)
  DEF_ROMLOC(BF54) : move_tomem_16(0x0, A0 + 0x12); // MOVE.W	#$0000,18(A0)
  DEF_ROMLOC(BF5A) : tst_mem_8(A0 + 0x1);           // TST.B	1(A0)
  DEF_ROMLOC(BF5E) : if (CCR_PL) {
    rom_BF6A();
    return;
  }                                            // BPL.B	$BF6A
  DEF_ROMLOC(BF60) : move_toreg_16(0xBD, &D0); // MOVE.W	#$00BD,D0
  DEF_ROMLOC(BF64) : rom_1394();               // JSR	$00001394
  rom_BF6A();
}
ROMFUNC(rom_BF7A) {
  DEF_ROMLOC(BF7A) : tst_mem_16(A0 + 0x36);        // TST.W	54(A0)
  DEF_ROMLOC(BF7E) : if (CCR_EQ) goto rom_BFC2;    // BEQ.B	$BFC2
  DEF_ROMLOC(BF80) : tst_mem_16(A0 + 0x38);        // TST.W	56(A0)
  DEF_ROMLOC(BF84) : if (CCR_EQ) goto rom_BF8C;    // BEQ.B	$BF8C
  DEF_ROMLOC(BF86) : sub_tomem_16(0x1, A0 + 0x38); // SUBQ.W	#$01,56(A0)
  goto rom_C006;                                   // BRA.B	$C006
  DEF_ROMLOC(BF8C)
      : move_toreg_8(read_8(0xFFFFFE0F), &D0);      // MOVE.B	$FE0F,D0
  DEF_ROMLOC(BF90) : and_toreg_8(0xF, &D0);         // ANDI.B	#$0F,D0
  DEF_ROMLOC(BF94) : if (!CCR_EQ) goto rom_BFA6;    // BNE.B	$BFA6
  DEF_ROMLOC(BF96) : tst_mem_8(A0 + 0x1);           // TST.B	1(A0)
  DEF_ROMLOC(BF9A) : if (CCR_PL) goto rom_BFA6;     // BPL.B	$BFA6
  DEF_ROMLOC(BF9C) : move_toreg_16(0xC7, &D0);      // MOVE.W	#$00C7,D0
  DEF_ROMLOC(BFA0) : rom_1394();                    // JSR	$00001394
  DEF_ROMLOC(BFA6) : sub_tomem_16(0x80, A0 + 0x32); // SUBI.W	#$0080,50(A0)
  DEF_ROMLOC(BFAC) : if (CCR_CC) goto rom_C006;     // BCC.B	$C006
  DEF_ROMLOC(BFAE) : move_tomem_16(0x0, A0 + 0x32); // MOVE.W	#$0000,50(A0)
  DEF_ROMLOC(BFB4) : move_tomem_16(0x0, A0 + 0x12); // MOVE.W	#$0000,18(A0)
  DEF_ROMLOC(BFBA) : move_tomem_16(0x0, A0 + 0x36); // MOVE.W	#$0000,54(A0)
  goto rom_C006;                                    // BRA.B	$C006
  DEF_ROMLOC(BFC2)
      : move_toreg_16(read_16(A0 + 0x34), &D1); // MOVE.W	52(A0),D1
  DEF_ROMLOC(BFC6)
      : cmp_toreg_16(read_16(A0 + 0x32), &D1);  // CMP.W	50(A0),D1
  DEF_ROMLOC(BFCA) : if (CCR_EQ) goto rom_C006; // BEQ.B	$C006
  DEF_ROMLOC(BFCC)
      : move_toreg_16(read_16(A0 + 0x12), &D0);     // MOVE.W	18(A0),D0
  DEF_ROMLOC(BFD0) : add_tomem_16(0x70, A0 + 0x12); // ADDI.W	#$0070,18(A0)
  DEF_ROMLOC(BFD6) : add_tomem_16(D0, A0 + 0x32);   // ADD.W	D0,50(A0)
  DEF_ROMLOC(BFDA)
      : cmp_toreg_16(read_16(A0 + 0x32), &D1);       // CMP.W	50(A0),D1
  DEF_ROMLOC(BFDE) : if (CCR_HI) goto rom_C006;      // BHI.B	$C006
  DEF_ROMLOC(BFE0) : move_tomem_16(D1, A0 + 0x32);   // MOVE.W	D1,50(A0)
  DEF_ROMLOC(BFE4) : move_tomem_16(0x0, A0 + 0x12);  // MOVE.W	#$0000,18(A0)
  DEF_ROMLOC(BFEA) : move_tomem_16(0x1, A0 + 0x36);  // MOVE.W	#$0001,54(A0)
  DEF_ROMLOC(BFF0) : move_tomem_16(0x3C, A0 + 0x38); // MOVE.W	#$003C,56(A0)
  DEF_ROMLOC(BFF6) : tst_mem_8(A0 + 0x1);            // TST.B	1(A0)
  DEF_ROMLOC(BFFA) : if (CCR_PL) goto rom_C006;      // BPL.B	$C006
  DEF_ROMLOC(BFFC) : move_toreg_16(0xBD, &D0);       // MOVE.W	#$00BD,D0
  DEF_ROMLOC(C000) : rom_1394();                     // JSR	$00001394
  DEF_ROMLOC(C006) : rom_BF6A();                     // BRA.W	$BF6A
}
ROMFUNC(rom_C00A) {
  DEF_ROMLOC(C00A)
      : move_toreg_16(read_16(0xFFFFD008), &D0); // MOVE.W	$D008,D0
  DEF_ROMLOC(C00E)
      : sub_toreg_16(read_16(A0 + 0x8), &D0);     // SUB.W	8(A0),D0
  DEF_ROMLOC(C012) : if (CCR_CC) goto rom_C016;   // BCC.B	$C016
  DEF_ROMLOC(C014) : neg_reg_16(&D0);             // NEG.W	D0
  DEF_ROMLOC(C016) : cmp_toreg_16(0x90, &D0);     // CMPI.W	#$0090,D0
  DEF_ROMLOC(C01A) : if (CCR_CC) goto rom_C020;   // BCC.B	$C020
  DEF_ROMLOC(C01C) : add_tomem_8(0x1, A0 + 0x28); // ADDQ.B	#$01,40(A0)
  DEF_ROMLOC(C020) : rom_BF6A();                  // BRA.W	$BF6A
}