// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_19068) {
  u8 switchindex = 0;
  DEF_ROMLOC(19068) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(1906A) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(1906E)
      : move_toreg_16(read_16(0x19076 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(19072): goto rom_19076 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(19072) : switch (switchindex) {
  case 0:
    rom_1908C();
    break;
  case 1:
    rom_1912C();
    break;
  case 2:
    rom_193A0();
    break;
  case 3:
    rom_193E4();
    break;
  case 4:
    rom_19454();
    break;
  }
}
ROMFUNC(rom_1908C) {
  DEF_ROMLOC(1908C)
      : move_tomem_16(0x2188, A0 + 0x8); // MOVE.W
                                         // #$2188,8(A0)
  DEF_ROMLOC(19092)
      : move_tomem_16(0x228, A0 + 0xC); // MOVE.W	#$0228,12(A0)
  DEF_ROMLOC(19098)
      : move_tomem_16(read_16(A0 + 0x8), A0 + 0x30); // MOVE.W	8(A0),48(A0)
  DEF_ROMLOC(1909E)
      : move_tomem_16(read_16(A0 + 0xC), A0 + 0x38); // MOVE.W	12(A0),56(A0)
  DEF_ROMLOC(190A4) : move_tomem_8(0xF, A0 + 0x20);  // MOVE.B	#$0F,32(A0)
  DEF_ROMLOC(190AA) : move_tomem_8(0x8, A0 + 0x21);  // MOVE.B	#$08,33(A0)
  DEF_ROMLOC(190B0) : move_toreg_32(0x19080, &A2);   // LEA.L	-50(PC),A2
  DEF_ROMLOC(190B4) : move_toreg_32(A0, &A1);        // MOVEA.L	A0,A1
  DEF_ROMLOC(190B6) : move_toreg_32(0x3, &D1);       // MOVEQ.L	$03,D1
  goto rom_190D4;                                    // BRA.B	$190D4
  DEF_ROMLOC(190BA) : rom_E130();                    // JSR	$0000E130
  DEF_ROMLOC(190C0) : if (!CCR_EQ) goto rom_1910C;   // BNE.B	$1910C
  DEF_ROMLOC(190C2)
      : move_tomem_8(OBJ_BOSSSTARLIGHT,
                     A1 + offsetof(object, id)); // MOVE.B	#$7A,0(A1)
  DEF_ROMLOC(190C8)
      : move_tomem_16(read_16(A0 + 0x8), A1 + 0x8); // MOVE.W	8(A0),8(A1)
  DEF_ROMLOC(190CE)
      : move_tomem_16(read_16(A0 + 0xC), A1 + 0xC); // MOVE.W	12(A0),12(A1)
  DEF_ROMLOC(190D4) : bclr_tomem_8(0x0, A0 + 0x22); // BCLR.B	#$00,34(A0)
  DEF_ROMLOC(190DA) : clr_mem_8(A1 + 0x25);         // CLR.B	37(A1)
  DEF_ROMLOC(190DE)
      : move_tomem_8(read_8(A2++), A1 + 0x24); // MOVE.B	(A2)+,36(A1)
  DEF_ROMLOC(190E2)
      : move_tomem_8(read_8(A2++), A1 + 0x1C); // MOVE.B	(A2)+,28(A1)
  DEF_ROMLOC(190E6)
      : move_tomem_8(read_8(A2++), A1 + 0x18); // MOVE.B	(A2)+,24(A1)
  DEF_ROMLOC(190EA)
      : move_tomem_32(0x184B8, A1 + 0x4);             // MOVE.L	#$000184B8,4(A1)
  DEF_ROMLOC(190F2) : move_tomem_16(0x400, A1 + 0x2); // MOVE.W	#$0400,2(A1)
  DEF_ROMLOC(190F8) : move_tomem_8(0x4, A1 + 0x1);    // MOVE.B	#$04,1(A1)
  DEF_ROMLOC(190FE) : move_tomem_8(0x20, A1 + 0x19);  // MOVE.B	#$20,25(A1)
  DEF_ROMLOC(19104) : move_tomem_32(A0, A1 + 0x34);   // MOVE.L	A0,52(A1)
  DEF_ROMLOC(19108) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_190BA;                                   // DBF.W	D1,$190BA
  DEF_ROMLOC(1910C) : move_toreg_32(0xFFFFD040, &A1); // LEA.L	$D040,A1
  DEF_ROMLOC(19110) : move_toreg_32(A0 + 0x2A, &A2);  // LEA.L	42(A0),A2
  DEF_ROMLOC(19114) : move_toreg_32(0x5E, &D0);       // MOVEQ.L	$5E,D0
  DEF_ROMLOC(19116) : move_toreg_32(0x3E, &D1);       // MOVEQ.L	$3E,D1
  rom_19118(); // Detected flow into next function
}
ROMFUNC(rom_19118) {
  DEF_ROMLOC(19118) : cmp_toreg_8(read_8(A1), &D0); // CMP.B	(A1),D0
  DEF_ROMLOC(1911A) : if (!CCR_EQ) goto rom_19124;  // BNE.B	$19124
  DEF_ROMLOC(1911C) : tst_mem_8(A1 + 0x28);         // TST.B	40(A1)
  DEF_ROMLOC(19120) : if (CCR_EQ) goto rom_19124;   // BEQ.B	$19124
  DEF_ROMLOC(19122)
      : move_tomem_16(A1, (A2 += 2, A2 - 2));  // MOVE.W	A1,(A2)+
  DEF_ROMLOC(19124) : add_toreg_16(0x40, &A1); // ADDA.W	#$0040,A1
  DEF_ROMLOC(19128) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_19118; // DBF.W	D1,$19118
  rom_1912C();      // Detected flow into next function
}
ROMFUNC(rom_1912C) {
  u8 switchindex = 0;
  DEF_ROMLOC(1912C) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(1912E) : move_toreg_8(read_8(A0 + 0x25), &D0);
  switchindex = D0 / 2; // MOVE.B	37(A0),D0
  DEF_ROMLOC(19132)
      : move_toreg_16(read_16(0x1915C + (s16)(D0 & 0xffff)),
                      &D0); // MOVE.W	40(PC,D0),D0
  // DEF_ROMLOC(19136): rom_1915C + (s16)(D0 & 0xffff)(); // JSR
  // 36(PC,D0)
  DEF_ROMLOC(19136) : switch (switchindex) {
  case 0:
    rom_19168();
    break;
  case 1:
    rom_1920E();
    break;
  case 2:
    rom_19282();
    break;
  case 3:
    rom_192F8();
    break;
  case 4:
    rom_19330();
    break;
  case 5:
    rom_19376();
    break;
  }
  DEF_ROMLOC(1913A) : move_toreg_32(0x18468, &A1); // LEA.L	$00018468,A1
  DEF_ROMLOC(19140) : animate_sprite();            // JSR	$0000ADA2
  DEF_ROMLOC(19146) : move_toreg_32(0x3, &D0);     // MOVEQ.L	$03,D0
  DEF_ROMLOC(19148)
      : and_toreg_8(read_8(A0 + 0x22), &D0); // AND.B
                                             // 34(A0),D0
  DEF_ROMLOC(1914C)
      : and_tomem_8(0xFFFFFFFC, A0 + 0x1);      // ANDI.B
                                                // #$FC,1(A0)
  DEF_ROMLOC(19152) : or_tomem_8(D0, A0 + 0x1); // OR.B	D0,1(A0)
  DEF_ROMLOC(19156) : queue_sprite();
  return; // JMP	$0000DC92
}
ROMFUNC(rom_1917A) {
  DEF_ROMLOC(1917A) : rom_18050(); // BSR.W	$18050
  DEF_ROMLOC(1917E)
      : move_toreg_8(read_8(A0 + 0x3F), &D0);      // MOVE.B	63(A0),D0
  DEF_ROMLOC(19182) : add_tomem_8(0x2, A0 + 0x3F); // ADDQ.B	#$02,63(A0)
  DEF_ROMLOC(19186) : rom_29D2();                  // JSR	$000029D2
  DEF_ROMLOC(1918C) : asr_toreg_16(0x6, &D0);      // ASR.W	#$06,D0
  DEF_ROMLOC(1918E)
      : add_toreg_16(read_16(A0 + 0x38), &D0);     // ADD.W	56(A0),D0
  DEF_ROMLOC(19192) : move_tomem_16(D0, A0 + 0xC); // MOVE.W	D0,12(A0)
  DEF_ROMLOC(19196)
      : move_tomem_16(read_16(A0 + 0x30), A0 + 0x8); // MOVE.W	48(A0),8(A0)
  goto rom_191AE;                                    // BRA.B	$191AE
  DEF_ROMLOC(1919E) : rom_18050();                   // BSR.W	$18050
  DEF_ROMLOC(191A2)
      : move_tomem_16(read_16(A0 + 0x38), A0 + 0xC); // MOVE.W	56(A0),12(A0)
  DEF_ROMLOC(191A8)
      : move_tomem_16(read_16(A0 + 0x30), A0 + 0x8); // MOVE.W	48(A0),8(A0)
  DEF_ROMLOC(191AE) : cmp_tomem_8(0x6, A0 + 0x25);   // CMPI.B	#$06,37(A0)
  DEF_ROMLOC(191B4) : if (CCR_CC) goto rom_191F4;    // BCC.B	$191F4
  DEF_ROMLOC(191B6) : tst_mem_8(A0 + 0x22);          // TST.B	34(A0)
  DEF_ROMLOC(191BA) : if (CCR_MI) goto rom_191F6;    // BMI.B	$191F6
  DEF_ROMLOC(191BC) : tst_mem_8(A0 + 0x20);          // TST.B	32(A0)
  DEF_ROMLOC(191C0) : if (!CCR_EQ) goto rom_191F4;   // BNE.B	$191F4
  DEF_ROMLOC(191C2) : tst_mem_8(A0 + 0x3E);          // TST.B	62(A0)
  DEF_ROMLOC(191C6) : if (!CCR_EQ) goto rom_191D8;   // BNE.B	$191D8
  DEF_ROMLOC(191C8)
      : move_tomem_8(0x20, A0 + 0x3E); // MOVE.B	#$20,62(A0)
  DEF_ROMLOC(191CE)
      : move_toreg_16(SFX_HITBOSS, &D0);              // MOVE.W
                                                      // #$00AC,D0
  DEF_ROMLOC(191D2) : play_sound_special();           // JSR	$00001394
  DEF_ROMLOC(191D8) : move_toreg_32(0xFFFFFB22, &A1); // LEA.L	$FB22,A1
  DEF_ROMLOC(191DC) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(191DE) : tst_mem_16(A1);                 // TST.W	(A1)
  DEF_ROMLOC(191E0) : if (!CCR_EQ) goto rom_191E6;    // BNE.B	$191E6
  DEF_ROMLOC(191E2) : move_toreg_16(0xEEE, &D0);      // MOVE.W	#$0EEE,D0
  DEF_ROMLOC(191E6) : move_tomem_16(D0, A1);          // MOVE.W	D0,(A1)
  DEF_ROMLOC(191E8) : sub_tomem_8(0x1, A0 + 0x3E);    // SUBQ.B	#$01,62(A0)
  DEF_ROMLOC(191EC) : if (!CCR_EQ) goto rom_191F4;    // BNE.B	$191F4
  DEF_ROMLOC(191EE) : move_tomem_8(0xF, A0 + 0x20);   // MOVE.B	#$0F,32(A0)
  DEF_ROMLOC(191F4) : return;                         // RTS
  DEF_ROMLOC(191F6) : move_toreg_32(0x64, &D0);       // MOVEQ.L	$64,D0
  DEF_ROMLOC(191F8) : rom_1CE42();                    // BSR.W	$1CE42
  DEF_ROMLOC(191FC) : move_tomem_8(0x6, A0 + 0x25);   // MOVE.B	#$06,37(A0)
  DEF_ROMLOC(19202)
      : move_tomem_8(0x78, A0 + 0x3C);       // MOVE.B	#$78,60(A0)
  DEF_ROMLOC(19208) : clr_mem_16(A0 + 0x10); // CLR.W	16(A0)
  DEF_ROMLOC(1920C) : return;                // RTS
}
ROMFUNC(rom_191AE) {
  DEF_ROMLOC(191AE) : cmp_tomem_8(0x6, A0 + 0x25); // CMPI.B	#$06,37(A0)
  DEF_ROMLOC(191B4) : if (CCR_CC) goto rom_191F4;  // BCC.B	$191F4
  DEF_ROMLOC(191B6) : tst_mem_8(A0 + 0x22);        // TST.B	34(A0)
  DEF_ROMLOC(191BA) : if (CCR_MI) goto rom_191F6;  // BMI.B	$191F6
  DEF_ROMLOC(191BC) : tst_mem_8(A0 + 0x20);        // TST.B	32(A0)
  DEF_ROMLOC(191C0) : if (!CCR_EQ) goto rom_191F4; // BNE.B	$191F4
  DEF_ROMLOC(191C2) : tst_mem_8(A0 + 0x3E);        // TST.B	62(A0)
  DEF_ROMLOC(191C6) : if (!CCR_EQ) goto rom_191D8; // BNE.B	$191D8
  DEF_ROMLOC(191C8)
      : move_tomem_8(0x20, A0 + 0x3E); // MOVE.B	#$20,62(A0)
  DEF_ROMLOC(191CE)
      : move_toreg_16(SFX_HITBOSS, &D0);              // MOVE.W
                                                      // #$00AC,D0
  DEF_ROMLOC(191D2) : play_sound_special();           // JSR	$00001394
  DEF_ROMLOC(191D8) : move_toreg_32(0xFFFFFB22, &A1); // LEA.L	$FB22,A1
  DEF_ROMLOC(191DC) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(191DE) : tst_mem_16(A1);                 // TST.W	(A1)
  DEF_ROMLOC(191E0) : if (!CCR_EQ) goto rom_191E6;    // BNE.B	$191E6
  DEF_ROMLOC(191E2) : move_toreg_16(0xEEE, &D0);      // MOVE.W	#$0EEE,D0
  DEF_ROMLOC(191E6) : move_tomem_16(D0, A1);          // MOVE.W	D0,(A1)
  DEF_ROMLOC(191E8) : sub_tomem_8(0x1, A0 + 0x3E);    // SUBQ.B	#$01,62(A0)
  DEF_ROMLOC(191EC) : if (!CCR_EQ) goto rom_191F4;    // BNE.B	$191F4
  DEF_ROMLOC(191EE) : move_tomem_8(0xF, A0 + 0x20);   // MOVE.B	#$0F,32(A0)
  DEF_ROMLOC(191F4) : return;                         // RTS
  DEF_ROMLOC(191F6) : move_toreg_32(0x64, &D0);       // MOVEQ.L	$64,D0
  DEF_ROMLOC(191F8) : rom_1CE42();                    // BSR.W	$1CE42
  DEF_ROMLOC(191FC) : move_tomem_8(0x6, A0 + 0x25);   // MOVE.B	#$06,37(A0)
  DEF_ROMLOC(19202)
      : move_tomem_8(0x78, A0 + 0x3C);       // MOVE.B	#$78,60(A0)
  DEF_ROMLOC(19208) : clr_mem_16(A0 + 0x10); // CLR.W	16(A0)
  DEF_ROMLOC(1920C) : return;                // RTS
}
ROMFUNC(rom_1919E) {
  DEF_ROMLOC(1919E) : rom_18050(); // BSR.W	$18050
  DEF_ROMLOC(191A2)
      : move_tomem_16(read_16(A0 + 0x38), A0 + 0xC); // MOVE.W	56(A0),12(A0)
  DEF_ROMLOC(191A8)
      : move_tomem_16(read_16(A0 + 0x30), A0 + 0x8); // MOVE.W	48(A0),8(A0)
  DEF_ROMLOC(191AE) : cmp_tomem_8(0x6, A0 + 0x25);   // CMPI.B	#$06,37(A0)
  DEF_ROMLOC(191B4) : if (CCR_CC) goto rom_191F4;    // BCC.B	$191F4
  DEF_ROMLOC(191B6) : tst_mem_8(A0 + 0x22);          // TST.B	34(A0)
  DEF_ROMLOC(191BA) : if (CCR_MI) goto rom_191F6;    // BMI.B	$191F6
  DEF_ROMLOC(191BC) : tst_mem_8(A0 + 0x20);          // TST.B	32(A0)
  DEF_ROMLOC(191C0) : if (!CCR_EQ) goto rom_191F4;   // BNE.B	$191F4
  DEF_ROMLOC(191C2) : tst_mem_8(A0 + 0x3E);          // TST.B	62(A0)
  DEF_ROMLOC(191C6) : if (!CCR_EQ) goto rom_191D8;   // BNE.B	$191D8
  DEF_ROMLOC(191C8)
      : move_tomem_8(0x20, A0 + 0x3E); // MOVE.B	#$20,62(A0)
  DEF_ROMLOC(191CE)
      : move_toreg_16(SFX_HITBOSS, &D0);              // MOVE.W
                                                      // #$00AC,D0
  DEF_ROMLOC(191D2) : play_sound_special();           // JSR	$00001394
  DEF_ROMLOC(191D8) : move_toreg_32(0xFFFFFB22, &A1); // LEA.L	$FB22,A1
  DEF_ROMLOC(191DC) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(191DE) : tst_mem_16(A1);                 // TST.W	(A1)
  DEF_ROMLOC(191E0) : if (!CCR_EQ) goto rom_191E6;    // BNE.B	$191E6
  DEF_ROMLOC(191E2) : move_toreg_16(0xEEE, &D0);      // MOVE.W	#$0EEE,D0
  DEF_ROMLOC(191E6) : move_tomem_16(D0, A1);          // MOVE.W	D0,(A1)
  DEF_ROMLOC(191E8) : sub_tomem_8(0x1, A0 + 0x3E);    // SUBQ.B	#$01,62(A0)
  DEF_ROMLOC(191EC) : if (!CCR_EQ) goto rom_191F4;    // BNE.B	$191F4
  DEF_ROMLOC(191EE) : move_tomem_8(0xF, A0 + 0x20);   // MOVE.B	#$0F,32(A0)
  DEF_ROMLOC(191F4) : return;                         // RTS
  DEF_ROMLOC(191F6) : move_toreg_32(0x64, &D0);       // MOVEQ.L	$64,D0
  DEF_ROMLOC(191F8) : rom_1CE42();                    // BSR.W	$1CE42
  DEF_ROMLOC(191FC) : move_tomem_8(0x6, A0 + 0x25);   // MOVE.B	#$06,37(A0)
  DEF_ROMLOC(19202)
      : move_tomem_8(0x78, A0 + 0x3C);       // MOVE.B	#$78,60(A0)
  DEF_ROMLOC(19208) : clr_mem_16(A0 + 0x10); // CLR.W	16(A0)
  DEF_ROMLOC(1920C) : return;                // RTS
}
ROMFUNC(rom_19168) {
  DEF_ROMLOC(19168)
      : move_tomem_16(0xFFFFFF00, A0 + 0x10); // MOVE.W	#$FF00,16(A0)
  DEF_ROMLOC(1916E)
      : cmp_tomem_16(0x2120, A0 + 0x30);           // CMPI.W
                                                   // #$2120,48(A0)
  DEF_ROMLOC(19174) : if (CCR_CC) goto rom_1917A;  // BCC.B	$1917A
  DEF_ROMLOC(19176) : add_tomem_8(0x2, A0 + 0x25); // ADDQ.B	#$02,37(A0)
  DEF_ROMLOC(1917A) : rom_18050();                 // BSR.W	$18050
  DEF_ROMLOC(1917E)
      : move_toreg_8(read_8(A0 + 0x3F), &D0);      // MOVE.B	63(A0),D0
  DEF_ROMLOC(19182) : add_tomem_8(0x2, A0 + 0x3F); // ADDQ.B	#$02,63(A0)
  DEF_ROMLOC(19186) : rom_29D2();                  // JSR	$000029D2
  DEF_ROMLOC(1918C) : asr_toreg_16(0x6, &D0);      // ASR.W	#$06,D0
  DEF_ROMLOC(1918E)
      : add_toreg_16(read_16(A0 + 0x38), &D0);     // ADD.W	56(A0),D0
  DEF_ROMLOC(19192) : move_tomem_16(D0, A0 + 0xC); // MOVE.W	D0,12(A0)
  DEF_ROMLOC(19196)
      : move_tomem_16(read_16(A0 + 0x30), A0 + 0x8); // MOVE.W	48(A0),8(A0)
  goto rom_191AE;                                    // BRA.B	$191AE
  DEF_ROMLOC(1919E) : rom_18050();                   // BSR.W	$18050
  DEF_ROMLOC(191A2)
      : move_tomem_16(read_16(A0 + 0x38), A0 + 0xC); // MOVE.W	56(A0),12(A0)
  DEF_ROMLOC(191A8)
      : move_tomem_16(read_16(A0 + 0x30), A0 + 0x8); // MOVE.W	48(A0),8(A0)
  DEF_ROMLOC(191AE) : cmp_tomem_8(0x6, A0 + 0x25);   // CMPI.B	#$06,37(A0)
  DEF_ROMLOC(191B4) : if (CCR_CC) goto rom_191F4;    // BCC.B	$191F4
  DEF_ROMLOC(191B6) : tst_mem_8(A0 + 0x22);          // TST.B	34(A0)
  DEF_ROMLOC(191BA) : if (CCR_MI) goto rom_191F6;    // BMI.B	$191F6
  DEF_ROMLOC(191BC) : tst_mem_8(A0 + 0x20);          // TST.B	32(A0)
  DEF_ROMLOC(191C0) : if (!CCR_EQ) goto rom_191F4;   // BNE.B	$191F4
  DEF_ROMLOC(191C2) : tst_mem_8(A0 + 0x3E);          // TST.B	62(A0)
  DEF_ROMLOC(191C6) : if (!CCR_EQ) goto rom_191D8;   // BNE.B	$191D8
  DEF_ROMLOC(191C8)
      : move_tomem_8(0x20, A0 + 0x3E); // MOVE.B	#$20,62(A0)
  DEF_ROMLOC(191CE)
      : move_toreg_16(SFX_HITBOSS, &D0);              // MOVE.W
                                                      // #$00AC,D0
  DEF_ROMLOC(191D2) : play_sound_special();           // JSR	$00001394
  DEF_ROMLOC(191D8) : move_toreg_32(0xFFFFFB22, &A1); // LEA.L	$FB22,A1
  DEF_ROMLOC(191DC) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(191DE) : tst_mem_16(A1);                 // TST.W	(A1)
  DEF_ROMLOC(191E0) : if (!CCR_EQ) goto rom_191E6;    // BNE.B	$191E6
  DEF_ROMLOC(191E2) : move_toreg_16(0xEEE, &D0);      // MOVE.W	#$0EEE,D0
  DEF_ROMLOC(191E6) : move_tomem_16(D0, A1);          // MOVE.W	D0,(A1)
  DEF_ROMLOC(191E8) : sub_tomem_8(0x1, A0 + 0x3E);    // SUBQ.B	#$01,62(A0)
  DEF_ROMLOC(191EC) : if (!CCR_EQ) goto rom_191F4;    // BNE.B	$191F4
  DEF_ROMLOC(191EE) : move_tomem_8(0xF, A0 + 0x20);   // MOVE.B	#$0F,32(A0)
  DEF_ROMLOC(191F4) : return;                         // RTS
  DEF_ROMLOC(191F6) : move_toreg_32(0x64, &D0);       // MOVEQ.L	$64,D0
  DEF_ROMLOC(191F8) : rom_1CE42();                    // BSR.W	$1CE42
  DEF_ROMLOC(191FC) : move_tomem_8(0x6, A0 + 0x25);   // MOVE.B	#$06,37(A0)
  DEF_ROMLOC(19202)
      : move_tomem_8(0x78, A0 + 0x3C);       // MOVE.B	#$78,60(A0)
  DEF_ROMLOC(19208) : clr_mem_16(A0 + 0x10); // CLR.W	16(A0)
  DEF_ROMLOC(1920C) : return;                // RTS
}
ROMFUNC(rom_1920E) {
  DEF_ROMLOC(1920E)
      : move_toreg_16(read_16(A0 + 0x30), &D0); // MOVE.W	48(A0),D0
  DEF_ROMLOC(19212)
      : move_tomem_16(0x200, A0 + 0x10);            // MOVE.W
                                                    // #$0200,16(A0)
  DEF_ROMLOC(19218) : btst_tomem_8(0x0, A0 + 0x22); // BTST.B	#$00,34(A0)
  DEF_ROMLOC(1921E) : if (!CCR_EQ) goto rom_1922C;  // BNE.B	$1922C
  DEF_ROMLOC(19220) : neg_mem_16(A0 + 0x10);        // NEG.W	16(A0)
  DEF_ROMLOC(19224) : cmp_toreg_16(0x2008, &D0);    // CMPI.W	#$2008,D0
  DEF_ROMLOC(19228) : if (CCR_GT) goto rom_19238;   // BGT.B	$19238
  goto rom_19232;                                   // BRA.B	$19232
  DEF_ROMLOC(1922C) : cmp_toreg_16(0x2138, &D0);    // CMPI.W	#$2138,D0
  DEF_ROMLOC(19230) : if (CCR_LT) goto rom_19238;   // BLT.B	$19238
  DEF_ROMLOC(19232) : bchg_tomem_8(0x0, A0 + 0x22); // BCHG.B	#$00,34(A0)
  DEF_ROMLOC(19238) : move_toreg_16(read_16(A0 + 0x8), &D0); // MOVE.W	8(A0),D0
  DEF_ROMLOC(1923C) : move_toreg_32(0xFFFFFFFF, &D1);        // MOVEQ.L	$FF,D1
  DEF_ROMLOC(1923E) : move_toreg_32(0x2, &D2);               // MOVEQ.L	$02,D2
  DEF_ROMLOC(19240) : move_toreg_32(A0 + 0x2A, &A2);         // LEA.L	42(A0),A2
  DEF_ROMLOC(19244) : move_toreg_32(0x28, &D4);              // MOVEQ.L	$28,D4
  DEF_ROMLOC(19246) : tst_mem_16(A0 + 0x10);                 // TST.W	16(A0)
  DEF_ROMLOC(1924A) : if (CCR_PL) goto rom_1924E;            // BPL.B	$1924E
  DEF_ROMLOC(1924C) : neg_reg_16(&D4);                       // NEG.W	D4
  DEF_ROMLOC(1924E)
      : move_toreg_16(read_16((A2 += 2, A2 - 2)), &D1); // MOVE.W	(A2)+,D1
  DEF_ROMLOC(19250) : move_toreg_32(D1, &A3);           // MOVEA.L	D1,A3
  DEF_ROMLOC(19252) : btst_tomem_8(0x3, A3 + 0x22);     // BTST.B	#$03,34(A3)
  DEF_ROMLOC(19258) : if (!CCR_EQ) goto rom_19264;      // BNE.B	$19264
  DEF_ROMLOC(1925A)
      : move_toreg_16(read_16(A3 + 0x8), &D3);    // MOVE.W	8(A3),D3
  DEF_ROMLOC(1925E) : add_toreg_16(D4, &D3);      // ADD.W	D4,D3
  DEF_ROMLOC(19260) : sub_toreg_16(D0, &D3);      // SUB.W	D0,D3
  DEF_ROMLOC(19262) : if (CCR_EQ) goto rom_19270; // BEQ.B	$19270
  DEF_ROMLOC(19264) : dec_reg_16(&D2);
  if ((D2 & 0xffff) != 0xffff)
    goto rom_1924E;                                // DBF.W	D2,$1924E
  DEF_ROMLOC(19268) : move_tomem_8(D2, A0 + 0x28); // MOVE.B	D2,40(A0)
  rom_1917A();
  return;                                            // BRA.W	$1917A
  DEF_ROMLOC(19270) : move_tomem_8(D2, A0 + 0x28);   // MOVE.B	D2,40(A0)
  DEF_ROMLOC(19274) : add_tomem_8(0x2, A0 + 0x25);   // ADDQ.B	#$02,37(A0)
  DEF_ROMLOC(19278) : move_tomem_8(0x28, A0 + 0x3C); // MOVE.B	#$28,60(A0)
  rom_1917A();                                       // BRA.W	$1917A
}
ROMFUNC(rom_19282) {
  DEF_ROMLOC(19282) : cmp_tomem_8(0x28, A0 + 0x3C);   // CMPI.B	#$28,60(A0)
  DEF_ROMLOC(19288) : if (!CCR_EQ) goto rom_192E6;    // BNE.B	$192E6
  DEF_ROMLOC(1928A) : move_toreg_32(0xFFFFFFFF, &D0); // MOVEQ.L	$FF,D0
  DEF_ROMLOC(1928C)
      : move_toreg_8(read_8(A0 + 0x28), &D0);        // MOVE.B
                                                     // 40(A0),D0
  DEF_ROMLOC(19290) : ext_reg_16(&D0);               // EXT.W	D0
  DEF_ROMLOC(19292) : if (CCR_MI) goto rom_192F0;    // BMI.B	$192F0
  DEF_ROMLOC(19294) : sub_toreg_16(0x2, &D0);        // SUBQ.W	#$02,D0
  DEF_ROMLOC(19296) : neg_reg_16(&D0);               // NEG.W	D0
  DEF_ROMLOC(19298) : add_toreg_16(D0, &D0);         // ADD.W	D0,D0
  DEF_ROMLOC(1929A) : move_toreg_32(A0 + 0x2A, &A1); // LEA.L	42(A0),A1
  DEF_ROMLOC(1929E)
      : move_toreg_16(read_16((s32)A1 + (s8)0x0 + (s16)D0),
                      &D0);                           // MOVE.W	0(A1,D0),D0
  DEF_ROMLOC(192A2) : move_toreg_32(D0, &A2);         // MOVEA.L	D0,A2
  DEF_ROMLOC(192A4) : move_toreg_32(0xFFFFD040, &A1); // LEA.L	$D040,A1
  DEF_ROMLOC(192A8) : move_toreg_32(0x3E, &D1);       // MOVEQ.L	$3E,D1
  DEF_ROMLOC(192AA)
      : cmp_toreg_32(read_32(A1 + 0x3C), &D0);    // CMP.L	60(A1),D0
  DEF_ROMLOC(192AE) : if (CCR_EQ) goto rom_192F0; // BEQ.B	$192F0
  DEF_ROMLOC(192B0) : add_toreg_16(0x40, &A1);    // ADDA.W	#$0040,A1
  DEF_ROMLOC(192B4) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_192AA;                               // DBF.W	D1,$192AA
  DEF_ROMLOC(192B8) : move_tomem_32(A0, A7 -= 4); // MOVE.L	A0,-(A7)
  DEF_ROMLOC(192BA) : move_toreg_32(A2, &A0);     // LEA.L	(A2),A0
  DEF_ROMLOC(192BC) : rom_E130();                 // JSR	$0000E130
  DEF_ROMLOC(192C2)
      : move_toreg_32(read_32((A7 += 4, A7 - 4)), &A0); // MOVEA.L	(A7)+,A0
  DEF_ROMLOC(192C4) : if (!CCR_EQ) goto rom_192F0;      // BNE.B	$192F0
  DEF_ROMLOC(192C6)
      : move_tomem_8(OBJ_BOSSSPIKEBALL,
                     A1 + offsetof(object, id)); // MOVE.B	#$7B,(A1)
  DEF_ROMLOC(192CA)
      : move_tomem_16(read_16(A0 + 0x8), A1 + 0x8); // MOVE.W	8(A0),8(A1)
  DEF_ROMLOC(192D0)
      : move_tomem_16(read_16(A0 + 0xC), A1 + 0xC); // MOVE.W	12(A0),12(A1)
  DEF_ROMLOC(192D6) : add_tomem_16(0x20, A1 + 0xC); // ADDI.W	#$0020,12(A1)
  DEF_ROMLOC(192DC)
      : move_tomem_8(read_8(A2 + 0x22), A1 + 0x22); // MOVE.B	34(A2),34(A1)
  DEF_ROMLOC(192E2) : move_tomem_32(A2, A1 + 0x3C); // MOVE.L	A2,60(A1)
  DEF_ROMLOC(192E6) : sub_tomem_8(0x1, A0 + 0x3C);  // SUBQ.B	#$01,60(A0)
  DEF_ROMLOC(192EA) : if (CCR_EQ) goto rom_192F0;   // BEQ.B	$192F0
  rom_191AE();
  return;                                          // BRA.W	$191AE
  DEF_ROMLOC(192F0) : sub_tomem_8(0x2, A0 + 0x25); // SUBQ.B	#$02,37(A0)
  rom_1917A();                                     // BRA.W	$1917A
}
ROMFUNC(rom_192F8) {
  DEF_ROMLOC(192F8) : sub_tomem_8(0x1, A0 + 0x3C); // SUBQ.B	#$01,60(A0)
  DEF_ROMLOC(192FC) : if (CCR_MI) goto rom_19302;  // BMI.B	$19302
  rom_1800C();
  return;                                           // BRA.W	$1800C
  DEF_ROMLOC(19302) : add_tomem_8(0x2, A0 + 0x25);  // ADDQ.B	#$02,37(A0)
  DEF_ROMLOC(19306) : clr_mem_16(A0 + 0x12);        // CLR.W	18(A0)
  DEF_ROMLOC(1930A) : bset_tomem_8(0x0, A0 + 0x22); // BSET.B	#$00,34(A0)
  DEF_ROMLOC(19310) : bclr_tomem_8(0x7, A0 + 0x22); // BCLR.B	#$07,34(A0)
  DEF_ROMLOC(19316) : clr_mem_16(A0 + 0x10);        // CLR.W	16(A0)
  DEF_ROMLOC(1931A)
      : move_tomem_8(0xFFFFFFE8, A0 + 0x3C);         // MOVE.B	#$E8,60(A0)
  DEF_ROMLOC(19320) : tst_mem_8(0xFFFFF7A7);         // TST.B	$F7A7
  DEF_ROMLOC(19324) : if (!CCR_EQ) goto rom_1932C;   // BNE.B	$1932C
  DEF_ROMLOC(19326) : move_tomem_8(0x1, 0xFFFFF7A7); // MOVE.B	#$01,$F7A7
  DEF_ROMLOC(1932C) : rom_191AE();                   // BRA.W	$191AE
}
ROMFUNC(rom_19330) {
  DEF_ROMLOC(19330) : add_tomem_8(0x1, A0 + 0x3C);   // ADDQ.B	#$01,60(A0)
  DEF_ROMLOC(19334) : if (CCR_EQ) goto rom_19340;    // BEQ.B	$19340
  DEF_ROMLOC(19336) : if (CCR_PL) goto rom_19346;    // BPL.B	$19346
  DEF_ROMLOC(19338) : add_tomem_16(0x18, A0 + 0x12); // ADDI.W	#$0018,18(A0)
  goto rom_19372;                                    // BRA.B	$19372
  DEF_ROMLOC(19340) : clr_mem_16(A0 + 0x12);         // CLR.W	18(A0)
  goto rom_19372;                                    // BRA.B	$19372
  DEF_ROMLOC(19346) : cmp_tomem_8(0x20, A0 + 0x3C);  // CMPI.B	#$20,60(A0)
  DEF_ROMLOC(1934C) : if (CCR_CS) goto rom_1935E;    // BCS.B	$1935E
  DEF_ROMLOC(1934E) : if (CCR_EQ) goto rom_19364;    // BEQ.B	$19364
  DEF_ROMLOC(19350) : cmp_tomem_8(0x2A, A0 + 0x3C);  // CMPI.B	#$2A,60(A0)
  DEF_ROMLOC(19356) : if (CCR_CS) goto rom_19372;    // BCS.B	$19372
  DEF_ROMLOC(19358) : add_tomem_8(0x2, A0 + 0x25);   // ADDQ.B	#$02,37(A0)
  goto rom_19372;                                    // BRA.B	$19372
  DEF_ROMLOC(1935E) : sub_tomem_16(0x8, A0 + 0x12);  // SUBQ.W	#$08,18(A0)
  goto rom_19372;                                    // BRA.B	$19372
  DEF_ROMLOC(19364) : clr_mem_16(A0 + 0x12);         // CLR.W	18(A0)
  DEF_ROMLOC(19368) : move_toreg_16(BGM_SLZ, &D0);   // MOVE.W	#$0084,D0
  DEF_ROMLOC(1936C) : play_sound();                  // JSR	$0000138E
  DEF_ROMLOC(19372) : rom_1919E();                   // BRA.W	$1919E
}
ROMFUNC(rom_19376) {
  DEF_ROMLOC(19376)
      : move_tomem_16(0x400, A0 + 0x10); // MOVE.W
                                         // #$0400,16(A0)
  DEF_ROMLOC(1937C)
      : move_tomem_16(0xFFFFFFC0, A0 + 0x12); // MOVE.W	#$FFC0,18(A0)
  DEF_ROMLOC(19382)
      : cmp_tomem_16(0x2160, v_limitright2);            // CMPI.W
                                                        // #$2160,$F72A
  DEF_ROMLOC(19388) : if (CCR_CC) goto rom_19390;       // BCC.B	$19390
  DEF_ROMLOC(1938A) : add_tomem_16(0x2, v_limitright2); // ADDQ.W
                                                        // #$02,$F72A
  goto rom_19398;                                       // BRA.B	$19398
  DEF_ROMLOC(19390) : tst_mem_8(A0 + 0x1);              // TST.B	1(A0)
  DEF_ROMLOC(19394) : if (CCR_PL) {
    rom_19062();
    return;
  } // BPL.W	$19062
  DEF_ROMLOC(19398) : rom_18050(); // BSR.W	$18050
  rom_1917A();                     // BRA.W	$1917A
}
ROMFUNC(rom_1941C) {
  DEF_ROMLOC(1941C) : move_toreg_32(0x18468, &A1); // LEA.L	$00018468,A1
  DEF_ROMLOC(19422) : animate_sprite();            // JSR	$0000ADA2
  rom_19428(); // Detected flow into next function
}
ROMFUNC(rom_193A0) {
  DEF_ROMLOC(193A0) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(193A2) : move_toreg_32(0x1, &D1); // MOVEQ.L	$01,D1
  DEF_ROMLOC(193A4)
      : move_toreg_32(read_32(A0 + 0x34), &A1); // MOVEA.L	52(A0),A1
  DEF_ROMLOC(193A8)
      : move_toreg_8(read_8(A1 + 0x25), &D0);       // MOVE.B	37(A1),D0
  DEF_ROMLOC(193AC) : cmp_toreg_8(0x6, &D0);        // CMPI.B	#$06,D0
  DEF_ROMLOC(193B0) : if (CCR_MI) goto rom_193B6;   // BMI.B	$193B6
  DEF_ROMLOC(193B2) : move_toreg_32(0xA, &D1);      // MOVEQ.L	$0A,D1
  goto rom_193CA;                                   // BRA.B	$193CA
  DEF_ROMLOC(193B6) : tst_mem_8(A1 + 0x20);         // TST.B	32(A1)
  DEF_ROMLOC(193BA) : if (!CCR_EQ) goto rom_193C0;  // BNE.B	$193C0
  DEF_ROMLOC(193BC) : move_toreg_32(0x5, &D1);      // MOVEQ.L	$05,D1
  goto rom_193CA;                                   // BRA.B	$193CA
  DEF_ROMLOC(193C0) : cmp_tomem_8(0x4, 0xFFFFD024); // CMPI.B	#$04,$D024
  DEF_ROMLOC(193C6) : if (CCR_CS) goto rom_193CA;   // BCS.B	$193CA
  DEF_ROMLOC(193C8) : move_toreg_32(0x4, &D1);      // MOVEQ.L	$04,D1
  DEF_ROMLOC(193CA) : move_tomem_8(D1, A0 + 0x1C);  // MOVE.B	D1,28(A0)
  DEF_ROMLOC(193CE) : cmp_toreg_8(0xA, &D0);        // CMPI.B	#$0A,D0
  DEF_ROMLOC(193D2) : if (!CCR_EQ) goto rom_193E2;  // BNE.B	$193E2
  DEF_ROMLOC(193D4) : move_tomem_8(0x6, A0 + 0x1C); // MOVE.B	#$06,28(A0)
  DEF_ROMLOC(193DA) : tst_mem_8(A0 + 0x1);          // TST.B	1(A0)
  DEF_ROMLOC(193DE) : if (CCR_PL) {
    rom_19062();
    return;
  } // BPL.W	$19062
  DEF_ROMLOC(193E2) : rom_1941C(); // BRA.B	$1941C
}
ROMFUNC(rom_193E4) {
  DEF_ROMLOC(193E4) : move_tomem_8(0x8, A0 + 0x1C); // MOVE.B	#$08,28(A0)
  DEF_ROMLOC(193EA)
      : move_toreg_32(read_32(A0 + 0x34), &A1);    // MOVEA.L	52(A0),A1
  DEF_ROMLOC(193EE) : cmp_tomem_8(0xA, A1 + 0x25); // CMPI.B	#$0A,37(A1)
  DEF_ROMLOC(193F4) : if (!CCR_EQ) goto rom_19406; // BNE.B	$19406
  DEF_ROMLOC(193F6) : tst_mem_8(A0 + 0x1);         // TST.B	1(A0)
  DEF_ROMLOC(193FA) : if (CCR_PL) {
    rom_19062();
    return;
  } // BPL.W	$19062
  DEF_ROMLOC(193FE) : move_tomem_8(0xB, A0 + 0x1C); // MOVE.B	#$0B,28(A0)
  goto rom_1941C;                                   // BRA.B	$1941C
  DEF_ROMLOC(19406) : cmp_tomem_8(0x8, A1 + 0x25);  // CMPI.B	#$08,37(A1)
  DEF_ROMLOC(1940C) : if (CCR_GT) goto rom_1941C;   // BGT.B	$1941C
  DEF_ROMLOC(1940E) : cmp_tomem_8(0x4, A1 + 0x25);  // CMPI.B	#$04,37(A1)
  DEF_ROMLOC(19414) : if (CCR_LT) goto rom_1941C;   // BLT.B	$1941C
  DEF_ROMLOC(19416) : move_tomem_8(0x7, A0 + 0x1C); // MOVE.B	#$07,28(A0)
  DEF_ROMLOC(1941C) : move_toreg_32(0x18468, &A1);  // LEA.L	$00018468,A1
  DEF_ROMLOC(19422) : animate_sprite();             // JSR	$0000ADA2
  rom_19428(); // Detected flow into next function
}
ROMFUNC(rom_19428) {
  DEF_ROMLOC(19428)
      : move_toreg_32(read_32(A0 + 0x34), &A1); // MOVEA.L	52(A0),A1
  DEF_ROMLOC(1942C)
      : move_tomem_16(read_16(A1 + 0x8), A0 + 0x8); // MOVE.W	8(A1),8(A0)
  DEF_ROMLOC(19432)
      : move_tomem_16(read_16(A1 + 0xC), A0 + 0xC); // MOVE.W	12(A1),12(A0)
  DEF_ROMLOC(19438)
      : move_tomem_8(read_8(A1 + 0x22), A0 + 0x22); // MOVE.B	34(A1),34(A0)
  DEF_ROMLOC(1943E) : move_toreg_32(0x3, &D0);      // MOVEQ.L	$03,D0
  DEF_ROMLOC(19440)
      : and_toreg_8(read_8(A0 + 0x22), &D0); // AND.B
                                             // 34(A0),D0
  DEF_ROMLOC(19444)
      : and_tomem_8(0xFFFFFFFC, A0 + 0x1);      // ANDI.B
                                                // #$FC,1(A0)
  DEF_ROMLOC(1944A) : or_tomem_8(D0, A0 + 0x1); // OR.B	D0,1(A0)
  DEF_ROMLOC(1944E) : queue_sprite();
  return; // JMP	$0000DC92
}
ROMFUNC(rom_19454) {
  DEF_ROMLOC(19454)
      : move_toreg_32(read_32(A0 + 0x34), &A1);    // MOVEA.L	52(A0),A1
  DEF_ROMLOC(19458) : cmp_tomem_8(0xA, A1 + 0x25); // CMPI.B	#$0A,37(A1)
  DEF_ROMLOC(1945E) : if (!CCR_EQ) goto rom_19468; // BNE.B	$19468
  DEF_ROMLOC(19460) : tst_mem_8(A0 + 0x1);         // TST.B	1(A0)
  DEF_ROMLOC(19464) : if (CCR_PL) {
    rom_19062();
    return;
  } // BPL.W	$19062
  DEF_ROMLOC(19468)
      : move_tomem_32(0x18580, A0 + 0x4); // MOVE.L	#$00018580,4(A0)
  DEF_ROMLOC(19470)
      : move_tomem_16(0x246C, A0 + 0x2);            // MOVE.W
                                                    // #$246C,2(A0)
  DEF_ROMLOC(19476) : move_tomem_8(0x3, A0 + 0x1A); // MOVE.B	#$03,26(A0)
  rom_19428();                                      // BRA.B	$19428
}