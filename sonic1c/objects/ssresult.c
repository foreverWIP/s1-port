// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_CE3C) {
  u8 switchindex = 0;
  DEF_ROMLOC(CE3C) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(CE3E) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(CE42)
      : move_toreg_16(read_16(0xCE4A + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(CE46): goto rom_CE4A + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(CE46) : switch (switchindex) {
  case 0:
    rom_CE60();
    break;
  case 1:
    rom_CED4();
    break;
  case 2:
    rom_CF12();
    break;
  case 3:
    rom_CF20();
    break;
  case 4:
    rom_CF12();
    break;
  case 5:
    rom_CF7A();
    break;
  case 6:
    rom_CF12();
    break;
  case 7:
    rom_CF84();
    break;
  case 8:
    rom_CF12();
    break;
  case 9:
    rom_CF7A();
    break;
  case 10:
    rom_CFA8();
    break;
  }
}
ROMFUNC(rom_CE60) {
  DEF_ROMLOC(CE60) : tst_mem_32(v_plc_buffer);       // TST.L	$F680
  DEF_ROMLOC(CE64) : if (CCR_EQ) goto rom_CE68;      // BEQ.B	$CE68
  DEF_ROMLOC(CE66) : return;                         // RTS
  DEF_ROMLOC(CE68) : move_toreg_32(A0, &A1);         // MOVEA.L	A0,A1
  DEF_ROMLOC(CE6A) : move_toreg_32(0xCFBC, &A2);     // LEA.L	$0000CFBC,A2
  DEF_ROMLOC(CE70) : move_toreg_32(0x3, &D1);        // MOVEQ.L	$03,D1
  DEF_ROMLOC(CE72) : cmp_tomem_16(0x32, 0xFFFFFE20); // CMPI.W	#$0032,$FE20
  DEF_ROMLOC(CE78) : if (CCR_CS) goto rom_CE7C;      // BCS.B	$CE7C
  DEF_ROMLOC(CE7A) : add_toreg_16(0x1, &D1);         // ADDQ.W	#$01,D1
  DEF_ROMLOC(CE7C) : move_tomem_8(OBJ_SSRESULT, A1 + offsetof(object, id));   // MOVE.B	#$7E,0(A1)
  DEF_ROMLOC(CE82)
      : move_tomem_16(read_16((A2 += 2, A2 - 2)),
                      A1 + 0x8); // MOVE.W	(A2)+,8(A1)
  DEF_ROMLOC(CE86)
      : move_tomem_16(read_16((A2 += 2, A2 - 2)),
                      A1 + 0x30); // MOVE.W	(A2)+,48(A1)
  DEF_ROMLOC(CE8A)
      : move_tomem_16(read_16((A2 += 2, A2 - 2)),
                      A1 + 0xA); // MOVE.W	(A2)+,10(A1)
  DEF_ROMLOC(CE8E)
      : move_tomem_8(read_8(A2++), A1 + 0x24); // MOVE.B	(A2)+,36(A1)
  DEF_ROMLOC(CE92)
      : move_tomem_8(read_8(A2++), A1 + 0x1A); // MOVE.B	(A2)+,26(A1)
  DEF_ROMLOC(CE96)
      : move_tomem_32(0xD328, A1 + 0x4); // MOVE.L	#$0000D328,4(A1)
  DEF_ROMLOC(CE9E)
      : move_tomem_16(0xFFFF8580, A1 + 0x2);        // MOVE.W	#$8580,2(A1)
  DEF_ROMLOC(CEA4) : move_tomem_8(0x0, A1 + 0x1);   // MOVE.B	#$00,1(A1)
  DEF_ROMLOC(CEAA) : move_toreg_32(A1 + 0x40, &A1); // LEA.L	64(A1),A1
  DEF_ROMLOC(CEAE) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_CE7C;                                          // DBF.W	D1,$CE7C
  DEF_ROMLOC(CEB2) : move_toreg_32(0x7, &D0);               // MOVEQ.L	$07,D0
  DEF_ROMLOC(CEB4) : move_toreg_8(read_8(0xFFFFFE57), &D1); // MOVE.B	$FE57,D1
  DEF_ROMLOC(CEB8) : if (CCR_EQ) goto rom_CED0;             // BEQ.B	$CED0
  DEF_ROMLOC(CEBA) : move_toreg_32(0x0, &D0);               // MOVEQ.L	$00,D0
  DEF_ROMLOC(CEBC) : cmp_toreg_8(0x6, &D1);                 // CMPI.B	#$06,D1
  DEF_ROMLOC(CEC0) : if (!CCR_EQ) goto rom_CED0;            // BNE.B	$CED0
  DEF_ROMLOC(CEC2) : move_toreg_32(0x8, &D0);               // MOVEQ.L	$08,D0
  DEF_ROMLOC(CEC4) : move_tomem_16(0x18, A0 + 0x8);   // MOVE.W	#$0018,8(A0)
  DEF_ROMLOC(CECA) : move_tomem_16(0x118, A0 + 0x30); // MOVE.W	#$0118,48(A0)
  DEF_ROMLOC(CED0) : move_tomem_8(D0, A0 + 0x1A);     // MOVE.B	D0,26(A0)
  rom_CED4(); // Detected flow into next function
}
ROMFUNC(rom_CED4) {
  DEF_ROMLOC(CED4) : move_toreg_32(0x10, &D1); // MOVEQ.L	$10,D1
  DEF_ROMLOC(CED6)
      : move_toreg_16(read_16(A0 + 0x30), &D0); // MOVE.W	48(A0),D0
  DEF_ROMLOC(CEDA)
      : cmp_toreg_16(read_16(A0 + 0x8), &D0);    // CMP.W	8(A0),D0
  DEF_ROMLOC(CEDE) : if (CCR_EQ) goto rom_CEFA;  // BEQ.B	$CEFA
  DEF_ROMLOC(CEE0) : if (CCR_GE) goto rom_CEE4;  // BGE.B	$CEE4
  DEF_ROMLOC(CEE2) : neg_reg_16(&D1);            // NEG.W	D1
  DEF_ROMLOC(CEE4) : add_tomem_16(D1, A0 + 0x8); // ADD.W	D1,8(A0)
  DEF_ROMLOC(CEE8)
      : move_toreg_16(read_16(A0 + 0x8), &D0);  // MOVE.W	8(A0),D0
  DEF_ROMLOC(CEEC) : if (CCR_MI) goto rom_CEF8; // BMI.B	$CEF8
  DEF_ROMLOC(CEEE) : cmp_toreg_16(0x200, &D0);  // CMPI.W	#$0200,D0
  DEF_ROMLOC(CEF2) : if (CCR_CC) goto rom_CEF8; // BCC.B	$CEF8
  rom_DC92();
  return;                                            // BRA.W	$DC92
  DEF_ROMLOC(CEF8) : return;                         // RTS
  DEF_ROMLOC(CEFA) : cmp_tomem_8(0x2, A0 + 0x1A);    // CMPI.B	#$02,26(A0)
  DEF_ROMLOC(CF00) : if (!CCR_EQ) goto rom_CEE8;     // BNE.B	$CEE8
  DEF_ROMLOC(CF02) : add_tomem_8(0x2, A0 + 0x24);    // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(CF06) : move_tomem_16(0xB4, A0 + 0x1E); // MOVE.W	#$00B4,30(A0)
  DEF_ROMLOC(CF0C) : move_tomem_8(0x7F, 0xFFFFD800); // MOVE.B	#$7F,$D800
  rom_CF12(); // Detected flow into next function
}
ROMFUNC(rom_CF12) {
  DEF_ROMLOC(CF12) : sub_tomem_16(0x1, A0 + 0x1E); // SUBQ.W	#$01,30(A0)
  DEF_ROMLOC(CF16) : if (!CCR_EQ) goto rom_CF1C;   // BNE.B	$CF1C
  DEF_ROMLOC(CF18) : add_tomem_8(0x2, A0 + 0x24);  // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(CF1C) : rom_DC92();                   // BRA.W	$DC92
}
ROMFUNC(rom_CF20) {
  DEF_ROMLOC(CF20) : rom_DC92();                    // BSR.W	$DC92
  DEF_ROMLOC(CF24) : move_tomem_8(0x1, 0xFFFFF7D6); // MOVE.B	#$01,$F7D6
  DEF_ROMLOC(CF2A) : tst_mem_16(0xFFFFF7D4);        // TST.W	$F7D4
  DEF_ROMLOC(CF2E) : if (CCR_EQ) goto rom_CF52;     // BEQ.B	$CF52
  DEF_ROMLOC(CF30) : sub_tomem_16(0xA, 0xFFFFF7D4); // SUBI.W	#$000A,$F7D4
  DEF_ROMLOC(CF36) : move_toreg_32(0xA, &D0);       // MOVEQ.L	$0A,D0
  DEF_ROMLOC(CF38) : rom_1CE42();                   // JSR	$0001CE42
  DEF_ROMLOC(CF3E)
      : move_toreg_8(read_8(0xFFFFFE0F), &D0);   // MOVE.B	$FE0F,D0
  DEF_ROMLOC(CF42) : and_toreg_8(0x3, &D0);      // ANDI.B	#$03,D0
  DEF_ROMLOC(CF46) : if (!CCR_EQ) goto rom_CF78; // BNE.B	$CF78
  DEF_ROMLOC(CF48) : move_toreg_16(SFX_SPRING, &D0);   // MOVE.W	#$00CD,D0
  DEF_ROMLOC(CF4C) : play_sound_special();
  return;                                            // JMP	$00001394
  DEF_ROMLOC(CF52) : move_toreg_16(SFX_CASH, &D0);       // MOVE.W	#$00C5,D0
  DEF_ROMLOC(CF56) : play_sound_special();           // JSR	$00001394
  DEF_ROMLOC(CF5C) : add_tomem_8(0x2, A0 + 0x24);    // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(CF60) : move_tomem_16(0xB4, A0 + 0x1E); // MOVE.W	#$00B4,30(A0)
  DEF_ROMLOC(CF66) : cmp_tomem_16(0x32, 0xFFFFFE20); // CMPI.W	#$0032,$FE20
  DEF_ROMLOC(CF6C) : if (CCR_CS) goto rom_CF78;      // BCS.B	$CF78
  DEF_ROMLOC(CF6E) : move_tomem_16(0x3C, A0 + 0x1E); // MOVE.W	#$003C,30(A0)
  DEF_ROMLOC(CF74) : add_tomem_8(0x4, A0 + 0x24);    // ADDQ.B	#$04,36(A0)
  DEF_ROMLOC(CF78) : return;                         // RTS
}
ROMFUNC(rom_CF7A) {
  DEF_ROMLOC(CF7A) : move_tomem_16(0x1, 0xFFFFFE02); // MOVE.W	#$0001,$FE02
  rom_DC92();                                        // BRA.W	$DC92
}
ROMFUNC(rom_CF84) {
  DEF_ROMLOC(CF84) : move_tomem_8(0x4, 0xFFFFD6DA);   // MOVE.B	#$04,$D6DA
  DEF_ROMLOC(CF8A) : move_tomem_8(0x14, 0xFFFFD6E4);  // MOVE.B	#$14,$D6E4
  DEF_ROMLOC(CF90) : move_toreg_16(SFX_CONTINUE, &D0);        // MOVE.W	#$00BF,D0
  DEF_ROMLOC(CF94) : play_sound_special();            // JSR	$00001394
  DEF_ROMLOC(CF9A) : add_tomem_8(0x2, A0 + 0x24);     // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(CF9E) : move_tomem_16(0x168, A0 + 0x1E); // MOVE.W	#$0168,30(A0)
  rom_DC92();                                         // BRA.W	$DC92
}
ROMFUNC(rom_CFA8) {
  DEF_ROMLOC(CFA8)
      : move_toreg_8(read_8(0xFFFFFE0F), &D0);     // MOVE.B	$FE0F,D0
  DEF_ROMLOC(CFAC) : and_toreg_8(0xF, &D0);        // ANDI.B	#$0F,D0
  DEF_ROMLOC(CFB0) : if (!CCR_EQ) goto rom_CFB8;   // BNE.B	$CFB8
  DEF_ROMLOC(CFB2) : bchg_tomem_8(0x0, A0 + 0x1A); // BCHG.B	#$00,26(A0)
  DEF_ROMLOC(CFB8) : rom_DC92();                   // BRA.W	$DC92
}
ROMFUNC(rom_CFBC) {
  DEF_ROMLOC(CFBC) : or_tomem_8(0x20, --A0); // ORI.B	#$20,-(A0)
  rom_CFE4();                                // Detected flow into next function
}