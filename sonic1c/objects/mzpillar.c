// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_BA28) {
  u8 switchindex = 0;
  DEF_ROMLOC(BA28) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(BA2A) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(BA2E)
      : move_toreg_16(read_16(0xBA5C + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	44(PC,D0),D1
  // DEF_ROMLOC(BA32): rom_BA5C + (s16)(D1 & 0xffff)(); // JSR	40(PC,D1)
  DEF_ROMLOC(BA32) : switch (switchindex) {
  case 0:
    rom_BA72();
    break;
  case 1:
    rom_BB16();
    break;
  case 2:
    rom_BB2E();
    break;
  case 3:
    rom_BB3C();
    break;
  case 4:
    rom_BB54();
    break;
  }
  DEF_ROMLOC(BA36) : move_toreg_16(read_16(A0 + 0x8), &D0); // MOVE.W	8(A0),D0
  DEF_ROMLOC(BA3A) : and_toreg_16(0xFFFFFF80, &D0);         // ANDI.W	#$FF80,D0
  DEF_ROMLOC(BA3E)
      : move_toreg_16(read_16(v_screenposx), &D1);  // MOVE.W	$F700,D1
  DEF_ROMLOC(BA42) : sub_toreg_16(0x80, &D1);       // SUBI.W	#$0080,D1
  DEF_ROMLOC(BA46) : and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
  DEF_ROMLOC(BA4A) : sub_toreg_16(D1, &D0);         // SUB.W	D1,D0
  DEF_ROMLOC(BA4C) : cmp_toreg_16(0x280, &D0);      // CMPI.W	#$0280,D0
  DEF_ROMLOC(BA50) : if (CCR_HI) {
    rom_BA58();
    return;
  } // BHI.W	$BA58
  rom_DC92(); // BRA.W	$DC92
}
ROMFUNC(rom_BA58) {
  DEF_ROMLOC(BA58) : {
    rom_DCCE();
    return;
  } // BRA.W	$DCCE
}
ROMFUNC(rom_BA66) {
  DEF_ROMLOC(BA66) : and_toreg_8(0x4, &D0); // ANDI.B	#$04,D0
  DEF_ROMLOC(BA6A) : or_toreg_8(0x0, &D1);  // ORI.B	#$00,D1
  rom_BA6C();                               // Detected flow into next function
}
ROMFUNC(rom_BA6C) {
  u8 switchindex = 0;
  DEF_ROMLOC(BA6C) : add_toreg_8(0x8, &D0);         // ADDI.B	#$08,D0
  DEF_ROMLOC(BA70) : or_toreg_8(0xFFFFFFF9, &D1);   // ORI.B	#$F9,D1
  DEF_ROMLOC(BA74) : or_toreg_8(0x66, &D0);         // ORI.B	#$66,D0
  DEF_ROMLOC(BA78) : move_toreg_32(0x1, &D1);       // MOVEQ.L	$01,D1
  DEF_ROMLOC(BA7A) : move_tomem_8(0x48, A0 + 0x16); // MOVE.B	#$48,22(A0)
  DEF_ROMLOC(BA80) : cmp_tomem_8(0x3, A0 + 0x28);   // CMPI.B	#$03,40(A0)
  DEF_ROMLOC(BA86) : if (CCR_CS) goto rom_BA96;     // BCS.B	$BA96
  DEF_ROMLOC(BA88) : move_toreg_32(0xBA6C, &A2);    // LEA.L	$0000BA6C,A2
  DEF_ROMLOC(BA8E) : move_toreg_32(0x1, &D1);       // MOVEQ.L	$01,D1
  DEF_ROMLOC(BA90) : move_tomem_8(0x38, A0 + 0x16); // MOVE.B	#$38,22(A0)
  DEF_ROMLOC(BA96) : move_toreg_32(A0, &A1);        // MOVEA.L	A0,A1
  DEF_ROMLOC(BA98) : goto rom_BAA0;                 // BRA.B	$BAA0
  DEF_ROMLOC(BA9A) : rom_E130();                    // BSR.W	$E130
  DEF_ROMLOC(BA9E) : if (!CCR_EQ) goto rom_BB0A;    // BNE.B	$BB0A
  DEF_ROMLOC(BAA0)
      : move_tomem_8(read_8(A2++), A1 + 0x24); // MOVE.B	(A2)+,36(A1)
  DEF_ROMLOC(BAA4)
      : move_tomem_8(OBJ_GLASSBLOCK,
                     A1 + offsetof(object, id)); // MOVE.B	#$30,0(A1)
  DEF_ROMLOC(BAAA)
      : move_tomem_16(read_16(A0 + 0x8), A1 + 0x8);   // MOVE.W	8(A0),8(A1)
  DEF_ROMLOC(BAB0) : move_toreg_8(read_8(A2++), &D0); // MOVE.B	(A2)+,D0
  DEF_ROMLOC(BAB2) : ext_reg_16(&D0);                 // EXT.W	D0
  DEF_ROMLOC(BAB4)
      : add_toreg_16(read_16(A0 + 0xC), &D0);     // ADD.W	12(A0),D0
  DEF_ROMLOC(BAB8) : move_tomem_16(D0, A1 + 0xC); // MOVE.W	D0,12(A1)
  DEF_ROMLOC(BABC)
      : move_tomem_32(0xBC84, A1 + 0x4); // MOVE.L	#$0000BC84,4(A1)
  DEF_ROMLOC(BAC4)
      : move_tomem_16(0xFFFFC38E, A1 + 0x2);      // MOVE.W	#$C38E,2(A1)
  DEF_ROMLOC(BACA) : move_tomem_8(0x4, A1 + 0x1); // MOVE.B	#$04,1(A1)
  DEF_ROMLOC(BAD0)
      : move_tomem_16(read_16(A1 + 0xC), A1 + 0x30); // MOVE.W	12(A1),48(A1)
  DEF_ROMLOC(BAD6)
      : move_tomem_8(read_8(A0 + 0x28), A1 + 0x28); // MOVE.B	40(A0),40(A1)
  DEF_ROMLOC(BADC) : move_tomem_8(0x20, A1 + 0x19); // MOVE.B	#$20,25(A1)
  DEF_ROMLOC(BAE2) : move_tomem_8(0x4, A1 + 0x18);  // MOVE.B	#$04,24(A1)
  DEF_ROMLOC(BAE8)
      : move_tomem_8(read_8(A2++), A1 + 0x1A);     // MOVE.B	(A2)+,26(A1)
  DEF_ROMLOC(BAEC) : move_tomem_32(A0, A1 + 0x3C); // MOVE.L	A0,60(A1)
  DEF_ROMLOC(BAF0) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_BA9A;                                   // DBF.W	D1,$BA9A
  DEF_ROMLOC(BAF4) : move_tomem_8(0x10, A1 + 0x19);  // MOVE.B	#$10,25(A1)
  DEF_ROMLOC(BAFA) : move_tomem_8(0x3, A1 + 0x18);   // MOVE.B	#$03,24(A1)
  DEF_ROMLOC(BB00) : add_tomem_8(0x8, A1 + 0x28);    // ADDQ.B	#$08,40(A1)
  DEF_ROMLOC(BB04) : and_tomem_8(0xF, A1 + 0x28);    // ANDI.B	#$0F,40(A1)
  DEF_ROMLOC(BB0A) : move_tomem_16(0x90, A0 + 0x32); // MOVE.W	#$0090,50(A0)
  DEF_ROMLOC(BB10) : bset_tomem_8(0x4, A0 + 0x1);    // BSET.B	#$04,1(A0)
  DEF_ROMLOC(BB16) : rom_BB68();                     // BSR.W	$BB68
  DEF_ROMLOC(BB1A) : move_toreg_16(0x2B, &D1);       // MOVE.W	#$002B,D1
  DEF_ROMLOC(BB1E) : move_toreg_16(0x48, &D2);       // MOVE.W	#$0048,D2
  DEF_ROMLOC(BB22) : move_toreg_16(0x49, &D3);       // MOVE.W	#$0049,D3
  DEF_ROMLOC(BB26)
      : move_toreg_16(read_16(A0 + 0x8), &D4); // MOVE.W	8(A0),D4
  DEF_ROMLOC(BB2A) : {
    rom_10062();
    return;
  } // BRA.W	$10062
  DEF_ROMLOC(BB2E)
      : move_toreg_32(read_32(A0 + 0x3C), &A1); // MOVEA.L	60(A0),A1
  DEF_ROMLOC(BB32)
      : move_tomem_16(read_16(A1 + 0x32), A0 + 0x32); // MOVE.W	50(A1),50(A0)
  DEF_ROMLOC(BB38) : goto rom_BB68;                   // BRA.W	$BB68
  DEF_ROMLOC(BB3C) : rom_BB68();                      // BSR.W	$BB68
  DEF_ROMLOC(BB40) : move_toreg_16(0x2B, &D1);        // MOVE.W	#$002B,D1
  DEF_ROMLOC(BB44) : move_toreg_16(0x38, &D2);        // MOVE.W	#$0038,D2
  DEF_ROMLOC(BB48) : move_toreg_16(0x39, &D3);        // MOVE.W	#$0039,D3
  DEF_ROMLOC(BB4C)
      : move_toreg_16(read_16(A0 + 0x8), &D4); // MOVE.W	8(A0),D4
  DEF_ROMLOC(BB50) : {
    rom_10062();
    return;
  } // BRA.W	$10062
  DEF_ROMLOC(BB54)
      : move_toreg_32(read_32(A0 + 0x3C), &A1); // MOVEA.L	60(A0),A1
  DEF_ROMLOC(BB58)
      : move_tomem_16(read_16(A1 + 0x32), A0 + 0x32); // MOVE.W	50(A1),50(A0)
  DEF_ROMLOC(BB5E)
      : move_tomem_16(read_16(A1 + 0xC), A0 + 0x30); // MOVE.W	12(A1),48(A0)
  DEF_ROMLOC(BB64) : goto rom_BB68;                  // BRA.W	$BB68
  DEF_ROMLOC(BB68) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(BB6A) : move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B
                                                           // 40(A0),D0
  DEF_ROMLOC(BB6E) : and_toreg_16(0x7, &D0);
  switchindex = D0;                         // ANDI.W	#$0007,D0
  DEF_ROMLOC(BB72) : add_toreg_16(D0, &D0); // ADD.W	D0,D0
  DEF_ROMLOC(BB74)
      : move_toreg_16(read_16(0xBB7C + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(BB78): goto rom_BB7C + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(BB78) : switch (switchindex) {
  case 0:
    rom_BB86();
    break;
  case 1:
    rom_BB88();
    break;
  case 2:
    rom_BB92();
    break;
  case 3:
    rom_BBB4();
    break;
  case 4:
    rom_BC3A();
    break;
  }
}
ROMFUNC(rom_BA72) {
  DEF_ROMLOC(BA72) : move_toreg_32(0xBA66, &A2);    // LEA.L	$0000BA66,A2
  DEF_ROMLOC(BA78) : move_toreg_32(0x1, &D1);       // MOVEQ.L	$01,D1
  DEF_ROMLOC(BA7A) : move_tomem_8(0x48, A0 + 0x16); // MOVE.B	#$48,22(A0)
  DEF_ROMLOC(BA80) : cmp_tomem_8(0x3, A0 + 0x28);   // CMPI.B	#$03,40(A0)
  DEF_ROMLOC(BA86) : if (CCR_CS) goto rom_BA96;     // BCS.B	$BA96
  DEF_ROMLOC(BA88) : move_toreg_32(0xBA6C, &A2);    // LEA.L	$0000BA6C,A2
  DEF_ROMLOC(BA8E) : move_toreg_32(0x1, &D1);       // MOVEQ.L	$01,D1
  DEF_ROMLOC(BA90) : move_tomem_8(0x38, A0 + 0x16); // MOVE.B	#$38,22(A0)
  DEF_ROMLOC(BA96) : move_toreg_32(A0, &A1);        // MOVEA.L	A0,A1
  DEF_ROMLOC(BA98) : goto rom_BAA0;                 // BRA.B	$BAA0
  DEF_ROMLOC(BA9A) : rom_E130();                    // BSR.W	$E130
  DEF_ROMLOC(BA9E) : if (!CCR_EQ) goto rom_BB0A;    // BNE.B	$BB0A
  DEF_ROMLOC(BAA0)
      : move_tomem_8(read_8(A2++), A1 + 0x24); // MOVE.B	(A2)+,36(A1)
  DEF_ROMLOC(BAA4)
      : move_tomem_8(OBJ_GLASSBLOCK,
                     A1 + offsetof(object, id)); // MOVE.B	#$30,0(A1)
  DEF_ROMLOC(BAAA)
      : move_tomem_16(read_16(A0 + 0x8), A1 + 0x8);   // MOVE.W	8(A0),8(A1)
  DEF_ROMLOC(BAB0) : move_toreg_8(read_8(A2++), &D0); // MOVE.B	(A2)+,D0
  DEF_ROMLOC(BAB2) : ext_reg_16(&D0);                 // EXT.W	D0
  DEF_ROMLOC(BAB4)
      : add_toreg_16(read_16(A0 + 0xC), &D0);     // ADD.W	12(A0),D0
  DEF_ROMLOC(BAB8) : move_tomem_16(D0, A1 + 0xC); // MOVE.W	D0,12(A1)
  DEF_ROMLOC(BABC)
      : move_tomem_32(0xBC84, A1 + 0x4); // MOVE.L	#$0000BC84,4(A1)
  DEF_ROMLOC(BAC4)
      : move_tomem_16(0xFFFFC38E, A1 + 0x2);      // MOVE.W	#$C38E,2(A1)
  DEF_ROMLOC(BACA) : move_tomem_8(0x4, A1 + 0x1); // MOVE.B	#$04,1(A1)
  DEF_ROMLOC(BAD0)
      : move_tomem_16(read_16(A1 + 0xC), A1 + 0x30); // MOVE.W	12(A1),48(A1)
  DEF_ROMLOC(BAD6)
      : move_tomem_8(read_8(A0 + 0x28), A1 + 0x28); // MOVE.B	40(A0),40(A1)
  DEF_ROMLOC(BADC) : move_tomem_8(0x20, A1 + 0x19); // MOVE.B	#$20,25(A1)
  DEF_ROMLOC(BAE2) : move_tomem_8(0x4, A1 + 0x18);  // MOVE.B	#$04,24(A1)
  DEF_ROMLOC(BAE8)
      : move_tomem_8(read_8(A2++), A1 + 0x1A);     // MOVE.B	(A2)+,26(A1)
  DEF_ROMLOC(BAEC) : move_tomem_32(A0, A1 + 0x3C); // MOVE.L	A0,60(A1)
  DEF_ROMLOC(BAF0) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_BA9A;                                   // DBF.W	D1,$BA9A
  DEF_ROMLOC(BAF4) : move_tomem_8(0x10, A1 + 0x19);  // MOVE.B	#$10,25(A1)
  DEF_ROMLOC(BAFA) : move_tomem_8(0x3, A1 + 0x18);   // MOVE.B	#$03,24(A1)
  DEF_ROMLOC(BB00) : add_tomem_8(0x8, A1 + 0x28);    // ADDQ.B	#$08,40(A1)
  DEF_ROMLOC(BB04) : and_tomem_8(0xF, A1 + 0x28);    // ANDI.B	#$0F,40(A1)
  DEF_ROMLOC(BB0A) : move_tomem_16(0x90, A0 + 0x32); // MOVE.W	#$0090,50(A0)
  DEF_ROMLOC(BB10) : bset_tomem_8(0x4, A0 + 0x1);    // BSET.B	#$04,1(A0)
  rom_BB16(); // Detected flow into next function
}
ROMFUNC(rom_BB16) {
  DEF_ROMLOC(BB16) : rom_BB68();               // BSR.W	$BB68
  DEF_ROMLOC(BB1A) : move_toreg_16(0x2B, &D1); // MOVE.W	#$002B,D1
  DEF_ROMLOC(BB1E) : move_toreg_16(0x48, &D2); // MOVE.W	#$0048,D2
  DEF_ROMLOC(BB22) : move_toreg_16(0x49, &D3); // MOVE.W	#$0049,D3
  DEF_ROMLOC(BB26)
      : move_toreg_16(read_16(A0 + 0x8), &D4); // MOVE.W	8(A0),D4
  rom_10062();                                 // BRA.W	$10062
}
ROMFUNC(rom_BB2E) {
  DEF_ROMLOC(BB2E)
      : move_toreg_32(read_32(A0 + 0x3C), &A1); // MOVEA.L	60(A0),A1
  DEF_ROMLOC(BB32)
      : move_tomem_16(read_16(A1 + 0x32), A0 + 0x32); // MOVE.W	50(A1),50(A0)
  rom_BB68();                                         // BRA.W	$BB68
}
ROMFUNC(rom_BB3C) {
  DEF_ROMLOC(BB3C) : rom_BB68();               // BSR.W	$BB68
  DEF_ROMLOC(BB40) : move_toreg_16(0x2B, &D1); // MOVE.W	#$002B,D1
  DEF_ROMLOC(BB44) : move_toreg_16(0x38, &D2); // MOVE.W	#$0038,D2
  DEF_ROMLOC(BB48) : move_toreg_16(0x39, &D3); // MOVE.W	#$0039,D3
  DEF_ROMLOC(BB4C)
      : move_toreg_16(read_16(A0 + 0x8), &D4); // MOVE.W	8(A0),D4
  rom_10062();                                 // BRA.W	$10062
}
ROMFUNC(rom_BB54) {
  DEF_ROMLOC(BB54)
      : move_toreg_32(read_32(A0 + 0x3C), &A1); // MOVEA.L	60(A0),A1
  DEF_ROMLOC(BB58)
      : move_tomem_16(read_16(A1 + 0x32), A0 + 0x32); // MOVE.W	50(A1),50(A0)
  DEF_ROMLOC(BB5E)
      : move_tomem_16(read_16(A1 + 0xC), A0 + 0x30); // MOVE.W	12(A1),48(A0)
  rom_BB68();                                        // BRA.W	$BB68
}
ROMFUNC(rom_BB68) {
  u8 switchindex = 0;
  DEF_ROMLOC(BB68) : move_toreg_32(0x0, &D0);              // MOVEQ.L	$00,D0
  DEF_ROMLOC(BB6A) : move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B
                                                           // 40(A0),D0
  DEF_ROMLOC(BB6E) : and_toreg_16(0x7, &D0);
  switchindex = D0;                         // ANDI.W	#$0007,D0
  DEF_ROMLOC(BB72) : add_toreg_16(D0, &D0); // ADD.W	D0,D0
  DEF_ROMLOC(BB74)
      : move_toreg_16(read_16(0xBB7C + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(BB78): goto rom_BB7C + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(BB78) : switch (switchindex) {
  case 0:
    rom_BB86();
    break;
  case 1:
    rom_BB88();
    break;
  case 2:
    rom_BB92();
    break;
  case 3:
    rom_BBB4();
    break;
  case 4:
    rom_BC3A();
    break;
  }
}
ROMFUNC(rom_BB86) {
  DEF_ROMLOC(BB86) : return; // RTS
}
ROMFUNC(rom_BB88) {
  DEF_ROMLOC(BB88)
      : move_toreg_8(read_8(0xFFFFFE70), &D0); // MOVE.B	$FE70,D0
  DEF_ROMLOC(BB8C) : move_toreg_16(0x40, &D1); // MOVE.W	#$0040,D1
  rom_BB9E();                                  // BRA.B	$BB9E
}
ROMFUNC(rom_BB92) {
  DEF_ROMLOC(BB92)
      : move_toreg_8(read_8(0xFFFFFE70), &D0); // MOVE.B	$FE70,D0
  DEF_ROMLOC(BB96) : move_toreg_16(0x40, &D1); // MOVE.W	#$0040,D1
  DEF_ROMLOC(BB9A) : neg_reg_16(&D0);          // NEG.W	D0
  DEF_ROMLOC(BB9C) : add_toreg_16(D1, &D0);    // ADD.W	D1,D0
  rom_BB9E(); // Detected flow into next function
}
ROMFUNC(rom_BB9E) {
  DEF_ROMLOC(BB9E) : btst_tomem_8(0x3, A0 + 0x28); // BTST.B	#$03,40(A0)
  DEF_ROMLOC(BBA4) : if (CCR_EQ) goto rom_BBB0;    // BEQ.B	$BBB0
  DEF_ROMLOC(BBA6) : neg_reg_16(&D0);              // NEG.W	D0
  DEF_ROMLOC(BBA8) : add_toreg_16(D1, &D0);        // ADD.W	D1,D0
  DEF_ROMLOC(BBAA) : lsr_toreg_8(0x1, &D0);        // LSR.B	#$01,D0
  DEF_ROMLOC(BBAC) : add_toreg_16(0x20, &D0);      // ADDI.W	#$0020,D0
  DEF_ROMLOC(BBB0) : rom_BC78();                   // BRA.W	$BC78
}
ROMFUNC(rom_BBB4) {
  DEF_ROMLOC(BBB4) : btst_tomem_8(0x3, A0 + 0x28); // BTST.B	#$03,40(A0)
  DEF_ROMLOC(BBBA) : if (CCR_EQ) goto rom_BBC8;    // BEQ.B	$BBC8
  DEF_ROMLOC(BBBC)
      : move_toreg_8(read_8(0xFFFFFE70), &D0); // MOVE.B	$FE70,D0
  DEF_ROMLOC(BBC0) : sub_toreg_16(0x10, &D0);  // SUBI.W	#$0010,D0
  rom_BC78();
  return;                                            // BRA.W	$BC78
  DEF_ROMLOC(BBC8) : btst_tomem_8(0x3, A0 + 0x22);   // BTST.B	#$03,34(A0)
  DEF_ROMLOC(BBCE) : if (!CCR_EQ) goto rom_BBD8;     // BNE.B	$BBD8
  DEF_ROMLOC(BBD0) : bclr_tomem_8(0x0, A0 + 0x34);   // BCLR.B	#$00,52(A0)
  goto rom_BC0C;                                     // BRA.B	$BC0C
  DEF_ROMLOC(BBD8) : tst_mem_8(A0 + 0x34);           // TST.B	52(A0)
  DEF_ROMLOC(BBDC) : if (!CCR_EQ) goto rom_BC0C;     // BNE.B	$BC0C
  DEF_ROMLOC(BBDE) : move_tomem_8(0x1, A0 + 0x34);   // MOVE.B	#$01,52(A0)
  DEF_ROMLOC(BBE4) : bset_tomem_8(0x0, A0 + 0x35);   // BSET.B	#$00,53(A0)
  DEF_ROMLOC(BBEA) : if (CCR_EQ) goto rom_BC0C;      // BEQ.B	$BC0C
  DEF_ROMLOC(BBEC) : bset_tomem_8(0x7, A0 + 0x34);   // BSET.B	#$07,52(A0)
  DEF_ROMLOC(BBF2) : move_tomem_16(0x10, A0 + 0x36); // MOVE.W	#$0010,54(A0)
  DEF_ROMLOC(BBF8) : move_tomem_8(0xA, A0 + 0x38);   // MOVE.B	#$0A,56(A0)
  DEF_ROMLOC(BBFE) : cmp_tomem_16(0x40, A0 + 0x32);  // CMPI.W	#$0040,50(A0)
  DEF_ROMLOC(BC04) : if (!CCR_EQ) goto rom_BC0C;     // BNE.B	$BC0C
  DEF_ROMLOC(BC06) : move_tomem_16(0x40, A0 + 0x36); // MOVE.W	#$0040,54(A0)
  DEF_ROMLOC(BC0C) : tst_mem_8(A0 + 0x34);           // TST.B	52(A0)
  DEF_ROMLOC(BC10) : if (CCR_PL) goto rom_BC34;      // BPL.B	$BC34
  DEF_ROMLOC(BC12) : tst_mem_8(A0 + 0x38);           // TST.B	56(A0)
  DEF_ROMLOC(BC16) : if (CCR_EQ) goto rom_BC1E;      // BEQ.B	$BC1E
  DEF_ROMLOC(BC18) : sub_tomem_8(0x1, A0 + 0x38);    // SUBQ.B	#$01,56(A0)
  DEF_ROMLOC(BC1C) : if (!CCR_EQ) goto rom_BC34;     // BNE.B	$BC34
  DEF_ROMLOC(BC1E) : tst_mem_16(A0 + 0x32);          // TST.W	50(A0)
  DEF_ROMLOC(BC22) : if (CCR_EQ) goto rom_BC2E;      // BEQ.B	$BC2E
  DEF_ROMLOC(BC24) : sub_tomem_16(0x1, A0 + 0x32);   // SUBQ.W	#$01,50(A0)
  DEF_ROMLOC(BC28) : sub_tomem_16(0x1, A0 + 0x36);   // SUBQ.W	#$01,54(A0)
  DEF_ROMLOC(BC2C) : if (!CCR_EQ) goto rom_BC34;     // BNE.B	$BC34
  DEF_ROMLOC(BC2E) : bclr_tomem_8(0x7, A0 + 0x34);   // BCLR.B	#$07,52(A0)
  DEF_ROMLOC(BC34)
      : move_toreg_16(read_16(A0 + 0x32), &D0); // MOVE.W	50(A0),D0
  rom_BC78();                                   // BRA.B	$BC78
}
ROMFUNC(rom_BC3A) {
  DEF_ROMLOC(BC3A) : btst_tomem_8(0x3, A0 + 0x28); // BTST.B	#$03,40(A0)
  DEF_ROMLOC(BC40) : if (CCR_EQ) goto rom_BC4C;    // BEQ.B	$BC4C
  DEF_ROMLOC(BC42)
      : move_toreg_8(read_8(0xFFFFFE70), &D0); // MOVE.B	$FE70,D0
  DEF_ROMLOC(BC46) : sub_toreg_16(0x10, &D0);  // SUBI.W	#$0010,D0
  rom_BC78();
  return;                                                  // BRA.B	$BC78
  DEF_ROMLOC(BC4C) : tst_mem_8(A0 + 0x34);                 // TST.B	52(A0)
  DEF_ROMLOC(BC50) : if (!CCR_EQ) goto rom_BC6A;           // BNE.B	$BC6A
  DEF_ROMLOC(BC52) : move_toreg_32(0xFFFFF7E0, &A2);       // LEA.L	$F7E0,A2
  DEF_ROMLOC(BC56) : move_toreg_32(0x0, &D0);              // MOVEQ.L	$00,D0
  DEF_ROMLOC(BC58) : move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B
                                                           // 40(A0),D0
  DEF_ROMLOC(BC5C) : lsr_toreg_16(0x4, &D0);               // LSR.W	#$04,D0
  DEF_ROMLOC(BC5E)
      : tst_mem_8((s32)A2 + (s8)0x0 + (s16)D0);    // TST.B	0(A2,D0)
  DEF_ROMLOC(BC62) : if (CCR_EQ) goto rom_BC74;    // BEQ.B	$BC74
  DEF_ROMLOC(BC64) : move_tomem_8(0x1, A0 + 0x34); // MOVE.B	#$01,52(A0)
  DEF_ROMLOC(BC6A) : tst_mem_16(A0 + 0x32);        // TST.W	50(A0)
  DEF_ROMLOC(BC6E) : if (CCR_EQ) goto rom_BC74;    // BEQ.B	$BC74
  DEF_ROMLOC(BC70) : sub_tomem_16(0x2, A0 + 0x32); // SUBQ.W	#$02,50(A0)
  DEF_ROMLOC(BC74)
      : move_toreg_16(read_16(A0 + 0x32), &D0); // MOVE.W	50(A0),D0
  rom_BC78();
}
ROMFUNC(rom_BC78) {
  DEF_ROMLOC(BC78)
      : move_toreg_16(read_16(A0 + 0x30), &D1);   // MOVE.W	48(A0),D1
  DEF_ROMLOC(BC7C) : sub_toreg_16(D0, &D1);       // SUB.W	D0,D1
  DEF_ROMLOC(BC7E) : move_tomem_16(D1, A0 + 0xC); // MOVE.W	D1,12(A0)
  DEF_ROMLOC(BC82) : return;                      // RTS
}