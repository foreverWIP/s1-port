// #define CHECK_STUFF 1
#include "../game.h"
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_CC00) {
  u8 switchindex = 0;
  DEF_ROMLOC(CC00) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(CC02) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(CC06)
      : move_toreg_16(read_16(0xCC0E + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(CC0A): goto rom_CC0E + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(CC0A) : switch (switchindex) {
  case 0:
    rom_CC20();
    break;
  case 1:
    rom_CC78();
    break;
  case 2:
    rom_CCC2();
    break;
  case 3:
    rom_CCD0();
    break;
  case 4:
    rom_CCC2();
    break;
  case 5:
    rom_CD3C();
    break;
  case 6:
    rom_CCC2();
    break;
  case 7:
    rom_CDB2();
    break;
  case 8:
    rom_CDF4();
    break;
  }
}
ROMFUNC(rom_CC20) {
  DEF_ROMLOC(CC20) : tst_mem_32(v_plc_buffer);             // TST.L	$F680
  DEF_ROMLOC(CC24) : if (CCR_EQ) goto rom_CC28;            // BEQ.B	$CC28
  DEF_ROMLOC(CC26) : return;                               // RTS
  DEF_ROMLOC(CC28) : move_toreg_32(A0, &A1);               // MOVEA.L	A0,A1
  DEF_ROMLOC(CC2A) : move_toreg_32(0xCE04, &A2);           // LEA.L	$0000CE04,A2
  DEF_ROMLOC(CC30) : move_toreg_32(0x6, &D1);              // MOVEQ.L	$06,D1
  DEF_ROMLOC(CC32) : move_tomem_8(OBJ_GOTTHROUGHCARD, A1 + offsetof(object, id));         // MOVE.B	#$3A,0(A1)
  DEF_ROMLOC(CC38) : move_tomem_16(read_16(A2), A1 + 0x8); // MOVE.W
                                                           // (A2),8(A1)
  DEF_ROMLOC(CC3C)
      : move_tomem_16(read_16((A2 += 2, A2 - 2)),
                      A1 + 0x32); // MOVE.W	(A2)+,50(A1)
  DEF_ROMLOC(CC40)
      : move_tomem_16(read_16((A2 += 2, A2 - 2)),
                      A1 + 0x30); // MOVE.W	(A2)+,48(A1)
  DEF_ROMLOC(CC44)
      : move_tomem_16(read_16((A2 += 2, A2 - 2)),
                      A1 + 0xA); // MOVE.W	(A2)+,10(A1)
  DEF_ROMLOC(CC48)
      : move_tomem_8(read_8(A2++), A1 + 0x24);        // MOVE.B	(A2)+,36(A1)
  DEF_ROMLOC(CC4C) : move_toreg_8(read_8(A2++), &D0); // MOVE.B	(A2)+,D0
  DEF_ROMLOC(CC4E) : cmp_toreg_8(0x6, &D0);           // CMPI.B	#$06,D0
  DEF_ROMLOC(CC52) : if (!CCR_EQ) goto rom_CC58;      // BNE.B	$CC58
  DEF_ROMLOC(CC54)
      : add_toreg_8(read_8(0xFFFFFE11), &D0);     // ADD.B	$FE11,D0
  DEF_ROMLOC(CC58) : move_tomem_8(D0, A1 + 0x1A); // MOVE.B	D0,26(A1)
  DEF_ROMLOC(CC5C)
      : move_tomem_32(0xD266, A1 + 0x4); // MOVE.L	#$0000D266,4(A1)
  DEF_ROMLOC(CC64)
      : move_tomem_16(0xFFFF8580, A1 + 0x2);        // MOVE.W	#$8580,2(A1)
  DEF_ROMLOC(CC6A) : move_tomem_8(0x0, A1 + 0x1);   // MOVE.B	#$00,1(A1)
  DEF_ROMLOC(CC70) : move_toreg_32(A1 + 0x40, &A1); // LEA.L	64(A1),A1
  DEF_ROMLOC(CC74) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_CC32; // DBF.W	D1,$CC32
  rom_CC78();      // Detected flow into next function
}
ROMFUNC(rom_CC78) {
  DEF_ROMLOC(CC78) : move_toreg_32(0x10, &D1); // MOVEQ.L	$10,D1
  DEF_ROMLOC(CC7A)
      : move_toreg_16(read_16(A0 + 0x30), &D0); // MOVE.W	48(A0),D0
  DEF_ROMLOC(CC7E)
      : cmp_toreg_16(read_16(A0 + 0x8), &D0);    // CMP.W	8(A0),D0
  DEF_ROMLOC(CC82) : if (CCR_EQ) goto rom_CCA8;  // BEQ.B	$CCA8
  DEF_ROMLOC(CC84) : if (CCR_GE) goto rom_CC88;  // BGE.B	$CC88
  DEF_ROMLOC(CC86) : neg_reg_16(&D1);            // NEG.W	D1
  DEF_ROMLOC(CC88) : add_tomem_16(D1, A0 + 0x8); // ADD.W	D1,8(A0)
  DEF_ROMLOC(CC8C)
      : move_toreg_16(read_16(A0 + 0x8), &D0);  // MOVE.W	8(A0),D0
  DEF_ROMLOC(CC90) : if (CCR_MI) goto rom_CC9C; // BMI.B	$CC9C
  DEF_ROMLOC(CC92) : cmp_toreg_16(0x200, &D0);  // CMPI.W	#$0200,D0
  DEF_ROMLOC(CC96) : if (CCR_CC) goto rom_CC9C; // BCC.B	$CC9C
  rom_DC92();
  return;                                          // BRA.W	$DC92
  DEF_ROMLOC(CC9C) : return;                       // RTS
  DEF_ROMLOC(CC9E) : move_tomem_8(0xE, A0 + 0x24); // MOVE.B	#$0E,36(A0)
  rom_CDB2();
  return;                                            // BRA.W	$CDB2
  DEF_ROMLOC(CCA8) : cmp_tomem_8(0xE, 0xFFFFD724);   // CMPI.B	#$0E,$D724
  DEF_ROMLOC(CCAE) : if (CCR_EQ) goto rom_CC9E;      // BEQ.B	$CC9E
  DEF_ROMLOC(CCB0) : cmp_tomem_8(0x4, A0 + 0x1A);    // CMPI.B	#$04,26(A0)
  DEF_ROMLOC(CCB6) : if (!CCR_EQ) goto rom_CC8C;     // BNE.B	$CC8C
  DEF_ROMLOC(CCB8) : add_tomem_8(0x2, A0 + 0x24);    // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(CCBC) : move_tomem_16(0xB4, A0 + 0x1E); // MOVE.W	#$00B4,30(A0)
  rom_CCC2(); // Detected flow into next function
}
ROMFUNC(rom_CCC2) {
  DEF_ROMLOC(CCC2) : sub_tomem_16(0x1, A0 + 0x1E); // SUBQ.W	#$01,30(A0)
  DEF_ROMLOC(CCC6) : if (!CCR_EQ) goto rom_CCCC;   // BNE.B	$CCCC
  DEF_ROMLOC(CCC8) : add_tomem_8(0x2, A0 + 0x24);  // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(CCCC) : rom_DC92();                   // BRA.W	$DC92
}
ROMFUNC(rom_CCD0) {
  DEF_ROMLOC(CCD0) : rom_DC92();                      // BSR.W	$DC92
  DEF_ROMLOC(CCD4) : move_tomem_8(0x1, 0xFFFFF7D6);   // MOVE.B	#$01,$F7D6
  DEF_ROMLOC(CCDA) : move_toreg_32(0x0, &D0);         // MOVEQ.L	$00,D0
  DEF_ROMLOC(CCDC) : tst_mem_16(0xFFFFF7D2);          // TST.W	$F7D2
  DEF_ROMLOC(CCE0) : if (CCR_EQ) goto rom_CCEC;       // BEQ.B	$CCEC
  DEF_ROMLOC(CCE2) : add_toreg_16(0xA, &D0);          // ADDI.W	#$000A,D0
  DEF_ROMLOC(CCE6) : sub_tomem_16(0xA, 0xFFFFF7D2);   // SUBI.W	#$000A,$F7D2
  DEF_ROMLOC(CCEC) : tst_mem_16(0xFFFFF7D4);          // TST.W	$F7D4
  DEF_ROMLOC(CCF0) : if (CCR_EQ) goto rom_CCFC;       // BEQ.B	$CCFC
  DEF_ROMLOC(CCF2) : add_toreg_16(0xA, &D0);          // ADDI.W	#$000A,D0
  DEF_ROMLOC(CCF6) : sub_tomem_16(0xA, 0xFFFFF7D4);   // SUBI.W	#$000A,$F7D4
  DEF_ROMLOC(CCFC) : tst_reg_16(&D0);                 // TST.W	D0
  DEF_ROMLOC(CCFE) : if (!CCR_EQ) goto rom_CD22;      // BNE.B	$CD22
  DEF_ROMLOC(CD00) : move_toreg_16(0xC5, &D0);        // MOVE.W	#$00C5,D0
  DEF_ROMLOC(CD04) : play_sound_special();            // JSR	$00001394
  DEF_ROMLOC(CD0A) : add_tomem_8(0x2, A0 + 0x24);     // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(CD0E) : cmp_tomem_16(0x501, 0xFFFFFE10); // CMPI.W	#$0501,$FE10
  DEF_ROMLOC(CD14) : if (!CCR_EQ) goto rom_CD1A;      // BNE.B	$CD1A
  DEF_ROMLOC(CD16) : add_tomem_8(0x4, A0 + 0x24);     // ADDQ.B	#$04,36(A0)
  DEF_ROMLOC(CD1A) : move_tomem_16(0xB4, A0 + 0x1E);  // MOVE.W	#$00B4,30(A0)
  DEF_ROMLOC(CD20) : return;                          // RTS
  DEF_ROMLOC(CD22) : rom_1CE42();                     // JSR	$0001CE42
  DEF_ROMLOC(CD28)
      : move_toreg_8(read_8(0xFFFFFE0F), &D0);   // MOVE.B	$FE0F,D0
  DEF_ROMLOC(CD2C) : and_toreg_8(0x3, &D0);      // ANDI.B	#$03,D0
  DEF_ROMLOC(CD30) : if (!CCR_EQ) goto rom_CD20; // BNE.B	$CD20
  DEF_ROMLOC(CD32) : move_toreg_16(0xCD, &D0);   // MOVE.W	#$00CD,D0
  DEF_ROMLOC(CD36) : {
    play_sound_special();
    return;
  } // JMP	$00001394
}
ROMFUNC(rom_CD3C) {
  DEF_ROMLOC(CD3C)
      : move_toreg_8(read_8(0xFFFFFE10), &D0); // MOVE.B	$FE10,D0
  DEF_ROMLOC(CD40) : and_toreg_16(0x7, &D0);   // ANDI.W	#$0007,D0
  DEF_ROMLOC(CD44) : lsl_toreg_16(0x3, &D0);   // LSL.W	#$03,D0
  DEF_ROMLOC(CD46)
      : move_toreg_8(read_8(0xFFFFFE11), &D1); // MOVE.B	$FE11,D1
  DEF_ROMLOC(CD4A) : and_toreg_16(0x3, &D1);   // ANDI.W	#$0003,D1
  DEF_ROMLOC(CD4E) : add_toreg_16(D1, &D1);    // ADD.W	D1,D1
  DEF_ROMLOC(CD50) : add_toreg_16(D1, &D0);    // ADD.W	D1,D0
  DEF_ROMLOC(CD52)
      : move_toreg_16(read_16(0xCD82 + (s16)(D0 & 0xffff)),
                      &D0);                         // MOVE.W	46(PC,D0),D0
  DEF_ROMLOC(CD56) : move_tomem_16(D0, 0xFFFFFE10); // MOVE.W	D0,$FE10
  DEF_ROMLOC(CD5A) : tst_reg_16(&D0);               // TST.W	D0
  DEF_ROMLOC(CD5C) : if (!CCR_EQ) goto rom_CD66;    // BNE.B	$CD66
  DEF_ROMLOC(CD5E) : SET_GM_SEGA();
  goto rom_CD7E;                                // BRA.B	$CD7E
  DEF_ROMLOC(CD66) : clr_mem_8(0xFFFFFE30);     // CLR.B	$FE30
  DEF_ROMLOC(CD6A) : tst_mem_8(0xFFFFF7CD);     // TST.B	$F7CD
  DEF_ROMLOC(CD6E) : if (CCR_EQ) goto rom_CD78; // BEQ.B	$CD78
  DEF_ROMLOC(CD70) : SET_GM_SPECIAL();
  goto rom_CD7E;                                     // BRA.B	$CD7E
  DEF_ROMLOC(CD78) : move_tomem_16(0x1, 0xFFFFFE02); // MOVE.W	#$0001,$FE02
  DEF_ROMLOC(CD7E) : rom_DC92();                     // BRA.W	$DC92
}
ROMFUNC(rom_CDB2) {
  DEF_ROMLOC(CDB2) : move_toreg_32(0x20, &D1); // MOVEQ.L	$20,D1
  DEF_ROMLOC(CDB4)
      : move_toreg_16(read_16(A0 + 0x32), &D0);            // MOVE.W	50(A0),D0
  DEF_ROMLOC(CDB8) : cmp_toreg_16(read_16(A0 + 0x8), &D0); // CMP.W	8(A0),D0
  DEF_ROMLOC(CDBC) : if (CCR_EQ) {
    rom_CDD8();
    return;
  } // BEQ.B	$CDD8
  DEF_ROMLOC(CDBE) : if (CCR_GE) {
    rom_CDC2();
    return;
  }                                   // BGE.B	$CDC2
  DEF_ROMLOC(CDC0) : neg_reg_16(&D1); // NEG.W	D1
  rom_CDC2();                         // Detected flow into next function
}
ROMFUNC(rom_CDC2) {
  DEF_ROMLOC(CDC2) : add_tomem_16(D1, A0 + 0x8); // ADD.W	D1,8(A0)
  DEF_ROMLOC(CDC6)
      : move_toreg_16(read_16(A0 + 0x8), &D0);  // MOVE.W	8(A0),D0
  DEF_ROMLOC(CDCA) : if (CCR_MI) goto rom_CDD6; // BMI.B	$CDD6
  DEF_ROMLOC(CDCC) : cmp_toreg_16(0x200, &D0);  // CMPI.W	#$0200,D0
  DEF_ROMLOC(CDD0) : if (CCR_CC) goto rom_CDD6; // BCC.B	$CDD6
  rom_DC92();
  return;                    // BRA.W	$DC92
  DEF_ROMLOC(CDD6) : return; // RTS
}
ROMFUNC(rom_CDD8) {
  DEF_ROMLOC(CDD8) : cmp_tomem_8(0x4, A0 + 0x1A); // CMPI.B	#$04,26(A0)
  DEF_ROMLOC(CDDE) : if (!CCR_EQ) {
    rom_DCCE();
    return;
  }                                               // BNE.W	$DCCE
  DEF_ROMLOC(CDE2) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(CDE6) : clr_mem_8(0xFFFFF7CC);       // CLR.B	$F7CC
  DEF_ROMLOC(CDEA) : move_toreg_16(0x8D, &D0);    // MOVE.W	#$008D,D0
  DEF_ROMLOC(CDEE) : {
    play_sound();
    return;
  } // JMP	$0000138E
}
ROMFUNC(rom_CDF4) {
  DEF_ROMLOC(CDF4) : add_tomem_16(0x2, 0xFFFFF72A); // ADDQ.W	#$02,$F72A
  DEF_ROMLOC(CDF8)
      : cmp_tomem_16(0x2100, 0xFFFFF72A); // CMPI.W
                                          // #$2100,$F72A
  DEF_ROMLOC(CDFE) : if (CCR_EQ) {
    rom_DCCE();
    return;
  }                          // BEQ.W	$DCCE
  DEF_ROMLOC(CE02) : return; // RTS
}