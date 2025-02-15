// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

void syz_boss_loop(u8 skip_state);
ROMFUNC(rom_1989E) {
  u8 switchindex = 0;
  DEF_ROMLOC(1989E) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(198A0) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(198A4)
      : move_toreg_16(read_16(0x198AC + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(198A8): goto rom_198AC + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(198A8) : switch (switchindex) {
  case 0:
    rom_198C2();
    break;
  case 1:
    syz_boss_loop(2);
    break;
  case 2:
    rom_19CD0();
    break;
  case 3:
    rom_19D3A();
    break;
  case 4:
    rom_19DA6();
    break;
  }
}
ROMFUNC(rom_198B6) {
  DEF_ROMLOC(198B6) : and_toreg_8(0x4, &D0);  // ANDI.B	#$04,D0
  DEF_ROMLOC(198BA) : btst_toreg_32(D0, &D5); // BTST.L	D0,D5
  DEF_ROMLOC(198BC) : add_toreg_8(0x8, &D7);  // ADDI.B	#$08,D7
  DEF_ROMLOC(198C0) : or_toreg_8(0x7C, &D5);  // ORI.B	#$7C,D5
  DEF_ROMLOC(198C4)
      : move_tomem_32(read_32((s32)A0 + (s8)0x8 + (s16)D0),
                      (s32)A6 + (s8)0x7C +
                          (s16)D3); // MOVE.L	8(A0,D0),124(A6,D3)
  rom_198C2();                      // Detected flow into next function
}
void syz_boss_loop(u8 skip_state) {
  u8 switchindex = 0;
  if (skip_state == 1) {
    goto rom_19908;
  }
  if (skip_state == 2) {
    goto rom_19940;
  }
  DEF_ROMLOC(198F0) : rom_E130();                  // JSR	$0000E130
  DEF_ROMLOC(198F6) : if (!CCR_EQ) goto rom_19940; // BNE.B	$19940
  DEF_ROMLOC(198F8) : move_tomem_8(OBJ_BOSSSPRINGYARD, A1 + offsetof(object, id));      // MOVE.B	#$75,(A1)
  DEF_ROMLOC(198FC)
      : move_tomem_16(read_16(A0 + 0x8), A1 + 0x8); // MOVE.W	8(A0),8(A1)
  DEF_ROMLOC(19902)
      : move_tomem_16(read_16(A0 + 0xC), A1 + 0xC); // MOVE.W	12(A0),12(A1)
  DEF_ROMLOC(19908) : bclr_tomem_8(0x0, A0 + 0x22); // BCLR.B	#$00,34(A0)
  DEF_ROMLOC(1990E) : clr_mem_8(A1 + 0x25);         // CLR.B	37(A1)
  DEF_ROMLOC(19912)
      : move_tomem_8(read_8(A2++), A1 + 0x24); // MOVE.B	(A2)+,36(A1)
  DEF_ROMLOC(19916)
      : move_tomem_8(read_8(A2++), A1 + 0x1C); // MOVE.B	(A2)+,28(A1)
  DEF_ROMLOC(1991A)
      : move_tomem_8(read_8(A2++), A1 + 0x18); // MOVE.B	(A2)+,24(A1)
  DEF_ROMLOC(1991E)
      : move_tomem_32(0x184B8, A1 + 0x4);             // MOVE.L	#$000184B8,4(A1)
  DEF_ROMLOC(19926) : move_tomem_16(0x400, A1 + 0x2); // MOVE.W	#$0400,2(A1)
  DEF_ROMLOC(1992C) : move_tomem_8(0x4, A1 + 0x1);    // MOVE.B	#$04,1(A1)
  DEF_ROMLOC(19932) : move_tomem_8(0x20, A1 + 0x19);  // MOVE.B	#$20,25(A1)
  DEF_ROMLOC(19938) : move_tomem_32(A0, A1 + 0x34);   // MOVE.L	A0,52(A1)
  DEF_ROMLOC(1993C) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_198F0;                            // DBF.W	D1,$198F0
  DEF_ROMLOC(19940) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(19942) : move_toreg_8(read_8(A0 + 0x25), &D0);
  switchindex = D0 / 2; // MOVE.B	37(A0),D0
  DEF_ROMLOC(19946)
      : move_toreg_16(read_16(0x19970 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	40(PC,D0),D1
  // DEF_ROMLOC(1994A): rom_19970 + (s16)(D1 & 0xffff)(); // JSR
  // 36(PC,D1)
  DEF_ROMLOC(1994A) : switch (switchindex) {
  case 0:
    rom_1997C();
    break;
  case 1:
    rom_19A20();
    break;
  case 2:
    rom_19A9C();
    break;
  case 3:
    rom_19C24();
    break;
  case 4:
    rom_19C5C();
    break;
  case 5:
    rom_19CA2();
    break;
  }
  DEF_ROMLOC(1994E) : move_toreg_32(0x18468, &A1);         // LEA.L	$00018468,A1
  DEF_ROMLOC(19954) : animate_sprite();                          // JSR	$0000ADA2
  DEF_ROMLOC(1995A) : move_toreg_32(0x3, &D0);             // MOVEQ.L	$03,D0
  DEF_ROMLOC(1995C) : and_toreg_8(read_8(A0 + 0x22), &D0); // AND.B
                                                           // 34(A0),D0
  DEF_ROMLOC(19960)
      : and_tomem_8(0xFFFFFFFC, A0 + 0x1);      // ANDI.B
                                                // #$FC,1(A0)
  DEF_ROMLOC(19966) : or_tomem_8(D0, A0 + 0x1); // OR.B	D0,1(A0)
  DEF_ROMLOC(1996A) : rom_DC92();
  return; // JMP	$0000DC92
}
ROMFUNC(rom_198C2) {
  DEF_ROMLOC(198C2)
      : move_tomem_16(0x2DB0, A0 + 0x8); // MOVE.W
                                         // #$2DB0,8(A0)
  DEF_ROMLOC(198C8)
      : move_tomem_16(0x4DA, A0 + 0xC); // MOVE.W	#$04DA,12(A0)
  DEF_ROMLOC(198CE)
      : move_tomem_16(read_16(A0 + 0x8), A0 + 0x30); // MOVE.W	8(A0),48(A0)
  DEF_ROMLOC(198D4)
      : move_tomem_16(read_16(A0 + 0xC), A0 + 0x38); // MOVE.W	12(A0),56(A0)
  DEF_ROMLOC(198DA) : move_tomem_8(0xF, A0 + 0x20);  // MOVE.B	#$0F,32(A0)
  DEF_ROMLOC(198E0) : move_tomem_8(0x8, A0 + 0x21);  // MOVE.B	#$08,33(A0)
  DEF_ROMLOC(198E6) : move_toreg_32(0x198B6, &A2);   // LEA.L	-50(PC),A2
  DEF_ROMLOC(198EA) : move_toreg_32(A0, &A1);        // MOVEA.L	A0,A1
  DEF_ROMLOC(198EC) : move_toreg_32(0x3, &D1);       // MOVEQ.L	$03,D1
  syz_boss_loop(1);                                  // BRA.B	$19908
}
ROMFUNC(rom_198F0) { syz_boss_loop(0); }
ROMFUNC(rom_199B2) {
  DEF_ROMLOC(199B2) : move_toreg_16(read_16(A0 + 0x8), &D0); // MOVE.W	8(A0),D0
  DEF_ROMLOC(199B6) : sub_toreg_16(0x2C00, &D0);             // SUBI.W	#$2C00,D0
  DEF_ROMLOC(199BA) : lsr_toreg_16(0x5, &D0);                // LSR.W	#$05,D0
  DEF_ROMLOC(199BC) : move_tomem_8(D0, A0 + 0x34);           // MOVE.B	D0,52(A0)
  DEF_ROMLOC(199C0) : cmp_tomem_8(0x6, A0 + 0x25);    // CMPI.B	#$06,37(A0)
  DEF_ROMLOC(199C6) : if (CCR_CC) goto rom_19A06;     // BCC.B	$19A06
  DEF_ROMLOC(199C8) : tst_mem_8(A0 + 0x22);           // TST.B	34(A0)
  DEF_ROMLOC(199CC) : if (CCR_MI) goto rom_19A08;     // BMI.B	$19A08
  DEF_ROMLOC(199CE) : tst_mem_8(A0 + 0x20);           // TST.B	32(A0)
  DEF_ROMLOC(199D2) : if (!CCR_EQ) goto rom_19A06;    // BNE.B	$19A06
  DEF_ROMLOC(199D4) : tst_mem_8(A0 + 0x3E);           // TST.B	62(A0)
  DEF_ROMLOC(199D8) : if (!CCR_EQ) goto rom_199EA;    // BNE.B	$199EA
  DEF_ROMLOC(199DA) : move_tomem_8(0x20, A0 + 0x3E);  // MOVE.B	#$20,62(A0)
  DEF_ROMLOC(199E0) : move_toreg_16(SFX_HITBOSS, &D0);       // MOVE.W	#$00AC,D0
  DEF_ROMLOC(199E4) : play_sound_special();           // JSR	$00001394
  DEF_ROMLOC(199EA) : move_toreg_32(0xFFFFFB22, &A1); // LEA.L	$FB22,A1
  DEF_ROMLOC(199EE) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(199F0) : tst_mem_16(A1);                 // TST.W	(A1)
  DEF_ROMLOC(199F2) : if (!CCR_EQ) goto rom_199F8;    // BNE.B	$199F8
  DEF_ROMLOC(199F4) : move_toreg_16(0xEEE, &D0);      // MOVE.W	#$0EEE,D0
  DEF_ROMLOC(199F8) : move_tomem_16(D0, A1);          // MOVE.W	D0,(A1)
  DEF_ROMLOC(199FA) : sub_tomem_8(0x1, A0 + 0x3E);    // SUBQ.B	#$01,62(A0)
  DEF_ROMLOC(199FE) : if (!CCR_EQ) goto rom_19A06;    // BNE.B	$19A06
  DEF_ROMLOC(19A00) : move_tomem_8(0xF, A0 + 0x20);   // MOVE.B	#$0F,32(A0)
  DEF_ROMLOC(19A06) : return;                         // RTS
  DEF_ROMLOC(19A08) : move_toreg_32(0x64, &D0);       // MOVEQ.L	$64,D0
  DEF_ROMLOC(19A0A) : rom_1CE42();                    // BSR.W	$1CE42
  DEF_ROMLOC(19A0E) : move_tomem_8(0x6, A0 + 0x25);   // MOVE.B	#$06,37(A0)
  DEF_ROMLOC(19A14) : move_tomem_16(0xB4, A0 + 0x3C); // MOVE.W	#$00B4,60(A0)
  DEF_ROMLOC(19A1A) : clr_mem_16(A0 + 0x10);          // CLR.W	16(A0)
  DEF_ROMLOC(19A1E) : return;                         // RTS
}
ROMFUNC(rom_199A2) {
  DEF_ROMLOC(199A2) : rom_18050(); // BSR.W	$18050
  DEF_ROMLOC(199A6)
      : move_tomem_16(read_16(A0 + 0x38), A0 + 0xC); // MOVE.W	56(A0),12(A0)
  DEF_ROMLOC(199AC)
      : move_tomem_16(read_16(A0 + 0x30), A0 + 0x8); // MOVE.W	48(A0),8(A0)
  rom_199B2();
}
ROMFUNC(rom_1998E) {
  DEF_ROMLOC(1998E)
      : move_toreg_8(read_8(A0 + 0x3F), &D0);       // MOVE.B	63(A0),D0
  DEF_ROMLOC(19992) : add_tomem_8(0x2, A0 + 0x3F);  // ADDQ.B	#$02,63(A0)
  DEF_ROMLOC(19996) : rom_29D2();                   // JSR	$000029D2
  DEF_ROMLOC(1999C) : asr_toreg_16(0x2, &D0);       // ASR.W	#$02,D0
  DEF_ROMLOC(1999E) : move_tomem_16(D0, A0 + 0x12); // MOVE.W	D0,18(A0)
  rom_199A2();
}
ROMFUNC(rom_1997C) {
  DEF_ROMLOC(1997C)
      : move_tomem_16(0xFFFFFF00, A0 + 0x10); // MOVE.W	#$FF00,16(A0)
  DEF_ROMLOC(19982)
      : cmp_tomem_16(0x2D38, A0 + 0x30); // CMPI.W
                                         // #$2D38,48(A0)
  DEF_ROMLOC(19988) : if (CCR_CC) {
    rom_1998E();
    return;
  }                                                // BCC.B	$1998E
  DEF_ROMLOC(1998A) : add_tomem_8(0x2, A0 + 0x25); // ADDQ.B	#$02,37(A0)
  rom_1998E();
}
ROMFUNC(rom_19A20) {
  DEF_ROMLOC(19A20)
      : move_toreg_16(read_16(A0 + 0x30), &D0); // MOVE.W	48(A0),D0
  DEF_ROMLOC(19A24)
      : move_tomem_16(0x140, A0 + 0x10);            // MOVE.W
                                                    // #$0140,16(A0)
  DEF_ROMLOC(19A2A) : btst_tomem_8(0x0, A0 + 0x22); // BTST.B	#$00,34(A0)
  DEF_ROMLOC(19A30) : if (!CCR_EQ) goto rom_19A3E;  // BNE.B	$19A3E
  DEF_ROMLOC(19A32) : neg_mem_16(A0 + 0x10);        // NEG.W	16(A0)
  DEF_ROMLOC(19A36) : cmp_toreg_16(0x2C08, &D0);    // CMPI.W	#$2C08,D0
  DEF_ROMLOC(19A3A) : if (CCR_GT) goto rom_19A4E;   // BGT.B	$19A4E
  goto rom_19A44;                                   // BRA.B	$19A44
  DEF_ROMLOC(19A3E) : cmp_toreg_16(0x2D38, &D0);    // CMPI.W	#$2D38,D0
  DEF_ROMLOC(19A42) : if (CCR_LT) goto rom_19A4E;   // BLT.B	$19A4E
  DEF_ROMLOC(19A44) : bchg_tomem_8(0x0, A0 + 0x22); // BCHG.B	#$00,34(A0)
  DEF_ROMLOC(19A4A) : clr_mem_8(A0 + 0x3D);         // CLR.B	61(A0)
  DEF_ROMLOC(19A4E) : sub_toreg_16(0x2C10, &D0);    // SUBI.W	#$2C10,D0
  DEF_ROMLOC(19A52) : and_toreg_16(0x1F, &D0);      // ANDI.W	#$001F,D0
  DEF_ROMLOC(19A56) : sub_toreg_16(0x1F, &D0);      // SUBI.W	#$001F,D0
  DEF_ROMLOC(19A5A) : if (CCR_PL) goto rom_19A5E;   // BPL.B	$19A5E
  DEF_ROMLOC(19A5C) : neg_reg_16(&D0);              // NEG.W	D0
  DEF_ROMLOC(19A5E) : sub_toreg_16(0x1, &D0);       // SUBQ.W	#$01,D0
  DEF_ROMLOC(19A60) : if (CCR_GT) goto rom_19A98;   // BGT.B	$19A98
  DEF_ROMLOC(19A62) : tst_mem_8(A0 + 0x3D);         // TST.B	61(A0)
  DEF_ROMLOC(19A66) : if (!CCR_EQ) goto rom_19A98;  // BNE.B	$19A98
  DEF_ROMLOC(19A68)
      : move_toreg_16(read_16(0xFFFFD008), &D1); // MOVE.W	$D008,D1
  DEF_ROMLOC(19A6C) : sub_toreg_16(0x2C00, &D1); // SUBI.W	#$2C00,D1
  DEF_ROMLOC(19A70) : asr_toreg_16(0x5, &D1);    // ASR.W	#$05,D1
  DEF_ROMLOC(19A72)
      : cmp_toreg_8(read_8(A0 + 0x34), &D1);       // CMP.B	52(A0),D1
  DEF_ROMLOC(19A76) : if (!CCR_EQ) goto rom_19A98; // BNE.B	$19A98
  DEF_ROMLOC(19A78) : move_toreg_32(0x0, &D0);     // MOVEQ.L	$00,D0
  DEF_ROMLOC(19A7A)
      : move_toreg_8(read_8(A0 + 0x34), &D0);       // MOVE.B	52(A0),D0
  DEF_ROMLOC(19A7E) : asl_toreg_16(0x5, &D0);       // ASL.W	#$05,D0
  DEF_ROMLOC(19A80) : add_toreg_16(0x2C10, &D0);    // ADDI.W	#$2C10,D0
  DEF_ROMLOC(19A84) : move_tomem_16(D0, A0 + 0x30); // MOVE.W	D0,48(A0)
  DEF_ROMLOC(19A88) : rom_19BFA();                  // BSR.W	$19BFA
  DEF_ROMLOC(19A8C) : add_tomem_8(0x2, A0 + 0x25);  // ADDQ.B	#$02,37(A0)
  DEF_ROMLOC(19A90) : clr_mem_16(A0 + 0x28);        // CLR.W	40(A0)
  DEF_ROMLOC(19A94) : clr_mem_16(A0 + 0x10);        // CLR.W	16(A0)
  DEF_ROMLOC(19A98) : rom_1998E();                  // BRA.W	$1998E
}
ROMFUNC(rom_19A9C) {
  u8 switchindex = 0;
  DEF_ROMLOC(19A9C) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(19A9E) : move_toreg_8(read_8(A0 + 0x28), &D0);
  switchindex = D0 / 2; // MOVE.B	40(A0),D0
  DEF_ROMLOC(19AA2)
      : move_toreg_16(read_16(0x19AAA + (s16)(D0 & 0xffff)),
                      &D0); // MOVE.W	6(PC,D0),D0
  // DEF_ROMLOC(19AA6): goto rom_19AAA + (s16)(D0 & 0xffff); // JMP	2(PC,D0)
  DEF_ROMLOC(19AA6) : switch (switchindex) {
  case 0:
    rom_19AB2();
    break;
  case 1:
    rom_19AF8();
    break;
  case 2:
    rom_19B3E();
    break;
  case 3:
    rom_19B80();
    break;
  }
}
ROMFUNC(rom_19AB2) {
  DEF_ROMLOC(19AB2)
      : move_tomem_16(0x180, A0 + 0x12); // MOVE.W
                                         // #$0180,18(A0)
  DEF_ROMLOC(19AB8)
      : move_toreg_16(read_16(A0 + 0x38), &D0);   // MOVE.W	56(A0),D0
  DEF_ROMLOC(19ABC) : cmp_toreg_16(0x556, &D0);   // CMPI.W	#$0556,D0
  DEF_ROMLOC(19AC0) : if (CCR_CS) goto rom_19AF4; // BCS.B	$19AF4
  DEF_ROMLOC(19AC2)
      : move_tomem_16(0x556, A0 + 0x38);              // MOVE.W
                                                      // #$0556,56(A0)
  DEF_ROMLOC(19AC8) : clr_mem_16(A0 + 0x3C);          // CLR.W	60(A0)
  DEF_ROMLOC(19ACC) : move_toreg_32(0xFFFFFFFF, &D0); // MOVEQ.L	$FF,D0
  DEF_ROMLOC(19ACE)
      : move_toreg_16(read_16(A0 + 0x36), &D0);   // MOVE.W	54(A0),D0
  DEF_ROMLOC(19AD2) : if (CCR_EQ) goto rom_19AEC; // BEQ.B	$19AEC
  DEF_ROMLOC(19AD4) : move_toreg_32(D0, &A1);     // MOVEA.L	D0,A1
  DEF_ROMLOC(19AD6)
      : move_tomem_8(0xFFFFFFFF, A1 + 0x29); // MOVE.B	#$FF,41(A1)
  DEF_ROMLOC(19ADC)
      : move_tomem_8(0xFFFFFFFF, A0 + 0x29);          // MOVE.B
                                                      // #$FF,41(A0)
  DEF_ROMLOC(19AE2) : move_tomem_32(A0, A1 + 0x34);   // MOVE.L	A0,52(A1)
  DEF_ROMLOC(19AE6) : move_tomem_16(0x32, A0 + 0x3C); // MOVE.W	#$0032,60(A0)
  DEF_ROMLOC(19AEC) : clr_mem_16(A0 + 0x12);          // CLR.W	18(A0)
  DEF_ROMLOC(19AF0) : add_tomem_8(0x2, A0 + 0x28);    // ADDQ.B	#$02,40(A0)
  DEF_ROMLOC(19AF4) : rom_199A2();                    // BRA.W	$199A2
}
ROMFUNC(rom_19AF8) {
  DEF_ROMLOC(19AF8) : sub_tomem_16(0x1, A0 + 0x3C); // SUBQ.W	#$01,60(A0)
  DEF_ROMLOC(19AFC) : if (CCR_PL) goto rom_19B16;   // BPL.B	$19B16
  DEF_ROMLOC(19AFE) : add_tomem_8(0x2, A0 + 0x28);  // ADDQ.B	#$02,40(A0)
  DEF_ROMLOC(19B02)
      : move_tomem_16(0xFFFFF800, A0 + 0x12);        // MOVE.W	#$F800,18(A0)
  DEF_ROMLOC(19B08) : tst_mem_16(A0 + 0x36);         // TST.W	54(A0)
  DEF_ROMLOC(19B0C) : if (!CCR_EQ) goto rom_19B12;   // BNE.B	$19B12
  DEF_ROMLOC(19B0E) : asr_mem_16(A0 + 0x12);         // ASR.W	18(A0)
  DEF_ROMLOC(19B12) : move_toreg_32(0x0, &D0);       // MOVEQ.L	$00,D0
  goto rom_19B2C;                                    // BRA.B	$19B2C
  DEF_ROMLOC(19B16) : move_toreg_32(0x0, &D0);       // MOVEQ.L	$00,D0
  DEF_ROMLOC(19B18) : cmp_tomem_16(0x1E, A0 + 0x3C); // CMPI.W	#$001E,60(A0)
  DEF_ROMLOC(19B1E) : if (CCR_GT) goto rom_19B2C;    // BGT.B	$19B2C
  DEF_ROMLOC(19B20) : move_toreg_32(0x2, &D0);       // MOVEQ.L	$02,D0
  DEF_ROMLOC(19B22) : btst_tomem_8(0x1, A0 + 0x3D);  // BTST.B	#$01,61(A0)
  DEF_ROMLOC(19B28) : if (CCR_EQ) goto rom_19B2C;    // BEQ.B	$19B2C
  DEF_ROMLOC(19B2A) : neg_reg_16(&D0);               // NEG.W	D0
  DEF_ROMLOC(19B2C)
      : add_toreg_16(read_16(A0 + 0x38), &D0);     // ADD.W	56(A0),D0
  DEF_ROMLOC(19B30) : move_tomem_16(D0, A0 + 0xC); // MOVE.W	D0,12(A0)
  DEF_ROMLOC(19B34)
      : move_tomem_16(read_16(A0 + 0x30), A0 + 0x8); // MOVE.W	48(A0),8(A0)
  rom_199B2();                                       // BRA.W	$199B2
}
ROMFUNC(rom_19B3E) {
  DEF_ROMLOC(19B3E) : move_toreg_16(0x4DA, &D0);  // MOVE.W	#$04DA,D0
  DEF_ROMLOC(19B42) : tst_mem_16(A0 + 0x36);      // TST.W	54(A0)
  DEF_ROMLOC(19B46) : if (CCR_EQ) goto rom_19B4C; // BEQ.B	$19B4C
  DEF_ROMLOC(19B48) : sub_toreg_16(0x18, &D0);    // SUBI.W	#$0018,D0
  DEF_ROMLOC(19B4C)
      : cmp_toreg_16(read_16(A0 + 0x38), &D0);        // CMP.W
                                                      // 56(A0),D0
  DEF_ROMLOC(19B50) : if (CCR_LT) goto rom_19B6E;     // BLT.B	$19B6E
  DEF_ROMLOC(19B52) : move_tomem_16(0x8, A0 + 0x3C);  // MOVE.W	#$0008,60(A0)
  DEF_ROMLOC(19B58) : tst_mem_16(A0 + 0x36);          // TST.W	54(A0)
  DEF_ROMLOC(19B5C) : if (CCR_EQ) goto rom_19B64;     // BEQ.B	$19B64
  DEF_ROMLOC(19B5E) : move_tomem_16(0x2D, A0 + 0x3C); // MOVE.W	#$002D,60(A0)
  DEF_ROMLOC(19B64) : add_tomem_8(0x2, A0 + 0x28);    // ADDQ.B	#$02,40(A0)
  DEF_ROMLOC(19B68) : clr_mem_16(A0 + 0x12);          // CLR.W	18(A0)
  goto rom_19B7C;                                     // BRA.B	$19B7C
  DEF_ROMLOC(19B6E)
      : cmp_tomem_16(0xFFFFFFC0, A0 + 0x12);        // CMPI.W	#$FFC0,18(A0)
  DEF_ROMLOC(19B74) : if (CCR_GE) goto rom_19B7C;   // BGE.B	$19B7C
  DEF_ROMLOC(19B76) : add_tomem_16(0xC, A0 + 0x12); // ADDI.W	#$000C,18(A0)
  DEF_ROMLOC(19B7C) : rom_199A2();                  // BRA.W	$199A2
}
ROMFUNC(rom_19B80) {
  DEF_ROMLOC(19B80) : sub_tomem_16(0x1, A0 + 0x3C);   // SUBQ.W	#$01,60(A0)
  DEF_ROMLOC(19B84) : if (CCR_GT) goto rom_19BB6;     // BGT.B	$19BB6
  DEF_ROMLOC(19B86) : if (CCR_MI) goto rom_19B9E;     // BMI.B	$19B9E
  DEF_ROMLOC(19B88) : move_toreg_32(0xFFFFFFFF, &D0); // MOVEQ.L	$FF,D0
  DEF_ROMLOC(19B8A)
      : move_toreg_16(read_16(A0 + 0x36), &D0);     // MOVE.W	54(A0),D0
  DEF_ROMLOC(19B8E) : if (CCR_EQ) goto rom_19B98;   // BEQ.B	$19B98
  DEF_ROMLOC(19B90) : move_toreg_32(D0, &A1);       // MOVEA.L	D0,A1
  DEF_ROMLOC(19B92) : move_tomem_8(0xA, A1 + 0x29); // MOVE.B	#$0A,41(A1)
  DEF_ROMLOC(19B98) : clr_mem_16(A0 + 0x36);        // CLR.W	54(A0)
  goto rom_19BB6;                                   // BRA.B	$19BB6
  DEF_ROMLOC(19B9E)
      : cmp_tomem_16(0xFFFFFFE2, A0 + 0x3C);       // CMPI.W	#$FFE2,60(A0)
  DEF_ROMLOC(19BA4) : if (!CCR_EQ) goto rom_19BB6; // BNE.B	$19BB6
  DEF_ROMLOC(19BA6) : clr_mem_8(A0 + 0x29);        // CLR.B	41(A0)
  DEF_ROMLOC(19BAA) : sub_tomem_8(0x2, A0 + 0x25); // SUBQ.B	#$02,37(A0)
  DEF_ROMLOC(19BAE)
      : move_tomem_8(0xFFFFFFFF, A0 + 0x3D);          // MOVE.B
                                                      // #$FF,61(A0)
  goto rom_19BF6;                                     // BRA.B	$19BF6
  DEF_ROMLOC(19BB6) : move_toreg_32(0x1, &D0);        // MOVEQ.L	$01,D0
  DEF_ROMLOC(19BB8) : tst_mem_16(A0 + 0x36);          // TST.W	54(A0)
  DEF_ROMLOC(19BBC) : if (CCR_EQ) goto rom_19BC0;     // BEQ.B	$19BC0
  DEF_ROMLOC(19BBE) : move_toreg_32(0x2, &D0);        // MOVEQ.L	$02,D0
  DEF_ROMLOC(19BC0) : cmp_tomem_16(0x4DA, A0 + 0x38); // CMPI.W	#$04DA,56(A0)
  DEF_ROMLOC(19BC6) : if (CCR_EQ) goto rom_19BD4;     // BEQ.B	$19BD4
  DEF_ROMLOC(19BC8) : if (CCR_LT) goto rom_19BCC;     // BLT.B	$19BCC
  DEF_ROMLOC(19BCA) : neg_reg_16(&D0);                // NEG.W	D0
  DEF_ROMLOC(19BCC) : tst_mem_16(A0 + 0x36);          // TST.W	54(A0)
  DEF_ROMLOC(19BD0) : add_tomem_16(D0, A0 + 0x38);    // ADD.W	D0,56(A0)
  DEF_ROMLOC(19BD4) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(19BD6) : tst_mem_16(A0 + 0x36);          // TST.W	54(A0)
  DEF_ROMLOC(19BDA) : if (CCR_EQ) goto rom_19BE8;     // BEQ.B	$19BE8
  DEF_ROMLOC(19BDC) : move_toreg_32(0x2, &D0);        // MOVEQ.L	$02,D0
  DEF_ROMLOC(19BDE) : btst_tomem_8(0x0, A0 + 0x3D);   // BTST.B	#$00,61(A0)
  DEF_ROMLOC(19BE4) : if (CCR_EQ) goto rom_19BE8;     // BEQ.B	$19BE8
  DEF_ROMLOC(19BE6) : neg_reg_16(&D0);                // NEG.W	D0
  DEF_ROMLOC(19BE8)
      : add_toreg_16(read_16(A0 + 0x38), &D0);     // ADD.W	56(A0),D0
  DEF_ROMLOC(19BEC) : move_tomem_16(D0, A0 + 0xC); // MOVE.W	D0,12(A0)
  DEF_ROMLOC(19BF0)
      : move_tomem_16(read_16(A0 + 0x30), A0 + 0x8); // MOVE.W	48(A0),8(A0)
  DEF_ROMLOC(19BF6) : rom_199B2();                   // BRA.W	$199B2
}
ROMFUNC(rom_19BFA) {
  DEF_ROMLOC(19BFA) : clr_mem_16(A0 + 0x36);          // CLR.W	54(A0)
  DEF_ROMLOC(19BFE) : move_toreg_32(0xFFFFD040, &A1); // LEA.L	$D040,A1
  DEF_ROMLOC(19C02) : move_toreg_32(0x3E, &D0);       // MOVEQ.L	$3E,D0
  DEF_ROMLOC(19C04) : move_toreg_32(0x76, &D1);       // MOVEQ.L	$76,D1
  DEF_ROMLOC(19C06)
      : move_toreg_8(read_8(A0 + 0x34), &D2); // MOVE.B
                                              // 52(A0),D2
  rom_19C0A(); // Detected flow into next function
}
ROMFUNC(rom_19C0A) {
  DEF_ROMLOC(19C0A) : cmp_toreg_8(read_8(A1), &D1); // CMP.B	(A1),D1
  DEF_ROMLOC(19C0C) : if (!CCR_EQ) goto rom_19C1A;  // BNE.B	$19C1A
  DEF_ROMLOC(19C0E)
      : cmp_toreg_8(read_8(A1 + 0x28), &D2);         // CMP.B
                                                     // 40(A1),D2
  DEF_ROMLOC(19C12) : if (!CCR_EQ) goto rom_19C1A;   // BNE.B	$19C1A
  DEF_ROMLOC(19C14) : move_tomem_16(A1, A0 + 0x36);  // MOVE.W	A1,54(A0)
  goto rom_19C22;                                    // BRA.B	$19C22
  DEF_ROMLOC(19C1A) : move_toreg_32(A1 + 0x40, &A1); // LEA.L	64(A1),A1
  DEF_ROMLOC(19C1E) : dec_reg_16(&D0);
  if ((D0 & 0xffff) != 0xffff)
    goto rom_19C0A;           // DBF.W	D0,$19C0A
  DEF_ROMLOC(19C22) : return; // RTS
}
ROMFUNC(rom_19C24) {
  DEF_ROMLOC(19C24) : sub_tomem_16(0x1, A0 + 0x3C); // SUBQ.W	#$01,60(A0)
  DEF_ROMLOC(19C28) : if (CCR_MI) goto rom_19C2E;   // BMI.B	$19C2E
  rom_1800C();
  return;                                           // BRA.W	$1800C
  DEF_ROMLOC(19C2E) : add_tomem_8(0x2, A0 + 0x25);  // ADDQ.B	#$02,37(A0)
  DEF_ROMLOC(19C32) : clr_mem_16(A0 + 0x12);        // CLR.W	18(A0)
  DEF_ROMLOC(19C36) : bset_tomem_8(0x0, A0 + 0x22); // BSET.B	#$00,34(A0)
  DEF_ROMLOC(19C3C) : bclr_tomem_8(0x7, A0 + 0x22); // BCLR.B	#$07,34(A0)
  DEF_ROMLOC(19C42) : clr_mem_16(A0 + 0x10);        // CLR.W	16(A0)
  DEF_ROMLOC(19C46)
      : move_tomem_16(0xFFFFFFFF, A0 + 0x3C);        // MOVE.W	#$FFFF,60(A0)
  DEF_ROMLOC(19C4C) : tst_mem_8(0xFFFFF7A7);         // TST.B	$F7A7
  DEF_ROMLOC(19C50) : if (!CCR_EQ) goto rom_19C58;   // BNE.B	$19C58
  DEF_ROMLOC(19C52) : move_tomem_8(0x1, 0xFFFFF7A7); // MOVE.B	#$01,$F7A7
  DEF_ROMLOC(19C58) : rom_199B2();                   // BRA.W	$199B2
}
ROMFUNC(rom_19C5C) {
  DEF_ROMLOC(19C5C) : add_tomem_16(0x1, A0 + 0x3C);  // ADDQ.W	#$01,60(A0)
  DEF_ROMLOC(19C60) : if (CCR_EQ) goto rom_19C6C;    // BEQ.B	$19C6C
  DEF_ROMLOC(19C62) : if (CCR_PL) goto rom_19C72;    // BPL.B	$19C72
  DEF_ROMLOC(19C64) : add_tomem_16(0x18, A0 + 0x12); // ADDI.W	#$0018,18(A0)
  goto rom_19C9E;                                    // BRA.B	$19C9E
  DEF_ROMLOC(19C6C) : clr_mem_16(A0 + 0x12);         // CLR.W	18(A0)
  goto rom_19C9E;                                    // BRA.B	$19C9E
  DEF_ROMLOC(19C72) : cmp_tomem_16(0x20, A0 + 0x3C); // CMPI.W	#$0020,60(A0)
  DEF_ROMLOC(19C78) : if (CCR_CS) goto rom_19C8A;    // BCS.B	$19C8A
  DEF_ROMLOC(19C7A) : if (CCR_EQ) goto rom_19C90;    // BEQ.B	$19C90
  DEF_ROMLOC(19C7C) : cmp_tomem_16(0x2A, A0 + 0x3C); // CMPI.W	#$002A,60(A0)
  DEF_ROMLOC(19C82) : if (CCR_CS) goto rom_19C9E;    // BCS.B	$19C9E
  DEF_ROMLOC(19C84) : add_tomem_8(0x2, A0 + 0x25);   // ADDQ.B	#$02,37(A0)
  goto rom_19C9E;                                    // BRA.B	$19C9E
  DEF_ROMLOC(19C8A) : sub_tomem_16(0x8, A0 + 0x12);  // SUBQ.W	#$08,18(A0)
  goto rom_19C9E;                                    // BRA.B	$19C9E
  DEF_ROMLOC(19C90) : clr_mem_16(A0 + 0x12);         // CLR.W	18(A0)
  DEF_ROMLOC(19C94) : move_toreg_16(BGM_SYZ, &D0);      // MOVE.W	#$0085,D0
  DEF_ROMLOC(19C98) : play_sound();                  // JSR	$0000138E
  DEF_ROMLOC(19C9E) : rom_199A2();                   // BRA.W	$199A2
}
ROMFUNC(rom_19CA2) {
  DEF_ROMLOC(19CA2)
      : move_tomem_16(0x400, A0 + 0x10); // MOVE.W
                                         // #$0400,16(A0)
  DEF_ROMLOC(19CA8)
      : move_tomem_16(0xFFFFFFC0, A0 + 0x12); // MOVE.W	#$FFC0,18(A0)
  DEF_ROMLOC(19CAE)
      : cmp_tomem_16(0x2D40, 0xFFFFF72A);            // CMPI.W
                                                     // #$2D40,$F72A
  DEF_ROMLOC(19CB4) : if (CCR_CC) goto rom_19CBC;    // BCC.B	$19CBC
  DEF_ROMLOC(19CB6) : add_tomem_16(0x2, 0xFFFFF72A); // ADDQ.W	#$02,$F72A
  goto rom_19CC2;                                    // BRA.B	$19CC2
  DEF_ROMLOC(19CBC) : tst_mem_8(A0 + 0x1);           // TST.B	1(A0)
  DEF_ROMLOC(19CC0) : if (CCR_PL) goto rom_19CCA;    // BPL.B	$19CCA
  DEF_ROMLOC(19CC2) : rom_18050();                   // BSR.W	$18050
  rom_1998E();
  return; // BRA.W	$1998E
  DEF_ROMLOC(19CCA) : rom_DCCE();
  return; // JMP	$0000DCCE
}
ROMFUNC(rom_19CD0) {
  u8 switchindex = 0;
  DEF_ROMLOC(19CD0) : move_toreg_32(0x1, &D1); // MOVEQ.L	$01,D1
  DEF_ROMLOC(19CD2)
      : move_toreg_32(read_32(A0 + 0x34), &A1); // MOVEA.L	52(A0),A1
  DEF_ROMLOC(19CD6) : move_toreg_32(0x0, &D0);  // MOVEQ.L	$00,D0
  DEF_ROMLOC(19CD8) : move_toreg_8(read_8(A1 + 0x25), &D0);
  switchindex = D0 / 2; // MOVE.B	37(A1),D0
  DEF_ROMLOC(19CDC)
      : move_toreg_16(read_16(0x19CF6 + (s16)(D0 & 0xffff)),
                      &D0); // MOVE.W	24(PC,D0),D0
  // DEF_ROMLOC(19CE0): rom_19CF6 + (s16)(D0 & 0xffff)(); // JSR
  // 20(PC,D0)
  DEF_ROMLOC(19CE0) : switch (switchindex) {
  case 0:
    rom_19D24();
    break;
  case 1:
    rom_19D24();
    break;
  case 2:
    rom_19D0A();
    break;
  case 3:
    rom_19D02();
    break;
  case 4:
    rom_19D02();
    break;
  case 5:
    rom_19D06();
    break;
  }
  DEF_ROMLOC(19CE4) : move_tomem_8(D1, A0 + 0x1C);   // MOVE.B	D1,28(A0)
  DEF_ROMLOC(19CE8) : move_toreg_8(read_8(A0), &D0); // MOVE.B	(A0),D0
  DEF_ROMLOC(19CEA) : cmp_toreg_8(read_8(A1), &D0);  // CMP.B	(A1),D0
  DEF_ROMLOC(19CEC) : if (!CCR_EQ) goto rom_19CF0;   // BNE.B	$19CF0
  rom_19D6E();
  return; // BRA.B	$19D6E
  DEF_ROMLOC(19CF0) : rom_DCCE();
  return; // JMP	$0000DCCE
}
ROMFUNC(rom_19CF6) {
  DEF_ROMLOC(19CF6) : or_tomem_8(0x2E, A6 + 0x14); // ORI.B	#$2E,20(A6)
  rom_19D02(); // Detected flow into next function
}
ROMFUNC(rom_19D02) {
  DEF_ROMLOC(19D02) : move_toreg_32(0xA, &D1); // MOVEQ.L	$0A,D1
  DEF_ROMLOC(19D04) : return;                  // RTS
}
ROMFUNC(rom_19D06) {
  DEF_ROMLOC(19D06) : move_toreg_32(0x6, &D1); // MOVEQ.L	$06,D1
  DEF_ROMLOC(19D08) : return;                  // RTS
}
ROMFUNC(rom_19D0A) {
  u8 switchindex = 0;
  DEF_ROMLOC(19D0A) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(19D0C) : move_toreg_8(read_8(A1 + 0x28), &D0);
  switchindex = D0 / 2; // MOVE.B	40(A1),D0
  DEF_ROMLOC(19D10)
      : move_toreg_16(read_16(0x19D18 + (s16)(D0 & 0xffff)),
                      &D0); // MOVE.W	6(PC,D0),D0
  // DEF_ROMLOC(19D14): goto rom_19D18 + (s16)(D0 & 0xffff); // JMP	2(PC,D0)
  DEF_ROMLOC(19D14) : switch (switchindex) {
  case 0:
    rom_19D20();
    break;
  case 1:
    rom_19D22();
    break;
  case 2:
    rom_19D20();
    break;
  case 3:
    rom_19D20();
    break;
  }
}
ROMFUNC(rom_19D20) {
  rom_19D24(); // BRA.B	$19D24
}
ROMFUNC(rom_19D22) {
  DEF_ROMLOC(19D22) : move_toreg_32(0x6, &D1); // MOVEQ.L	$06,D1
  rom_19D24(); // Detected flow into next function
}
ROMFUNC(rom_19D24) {
  DEF_ROMLOC(19D24) : tst_mem_8(A1 + 0x20);         // TST.B	32(A1)
  DEF_ROMLOC(19D28) : if (!CCR_EQ) goto rom_19D2E;  // BNE.B	$19D2E
  DEF_ROMLOC(19D2A) : move_toreg_32(0x5, &D1);      // MOVEQ.L	$05,D1
  DEF_ROMLOC(19D2C) : return;                       // RTS
  DEF_ROMLOC(19D2E) : cmp_tomem_8(0x4, 0xFFFFD024); // CMPI.B	#$04,$D024
  DEF_ROMLOC(19D34) : if (CCR_CS) goto rom_19D38;   // BCS.B	$19D38
  DEF_ROMLOC(19D36) : move_toreg_32(0x4, &D1);      // MOVEQ.L	$04,D1
  DEF_ROMLOC(19D38) : return;                       // RTS
}
ROMFUNC(rom_19D3A) {
  DEF_ROMLOC(19D3A) : move_tomem_8(0x7, A0 + 0x1C); // MOVE.B	#$07,28(A0)
  DEF_ROMLOC(19D40)
      : move_toreg_32(read_32(A0 + 0x34), &A1);     // MOVEA.L	52(A0),A1
  DEF_ROMLOC(19D44) : cmp_tomem_8(0xA, A1 + 0x25);  // CMPI.B	#$0A,37(A1)
  DEF_ROMLOC(19D4A) : if (!CCR_EQ) goto rom_19D5A;  // BNE.B	$19D5A
  DEF_ROMLOC(19D4C) : move_tomem_8(0xB, A0 + 0x1C); // MOVE.B	#$0B,28(A0)
  DEF_ROMLOC(19D52) : tst_mem_8(A0 + 0x1);          // TST.B	1(A0)
  DEF_ROMLOC(19D56) : if (CCR_PL) goto rom_19D68;   // BPL.B	$19D68
  goto rom_19D66;                                   // BRA.B	$19D66
  DEF_ROMLOC(19D5A) : tst_mem_16(A1 + 0x10);        // TST.W	16(A1)
  DEF_ROMLOC(19D5E) : if (CCR_EQ) goto rom_19D66;   // BEQ.B	$19D66
  DEF_ROMLOC(19D60) : move_tomem_8(0x8, A0 + 0x1C); // MOVE.B	#$08,28(A0)
  DEF_ROMLOC(19D66) : rom_19D6E();
  return; // BRA.B	$19D6E
  DEF_ROMLOC(19D68) : rom_DCCE();
  return; // JMP	$0000DCCE
}
ROMFUNC(rom_19D6E) {
  DEF_ROMLOC(19D6E) : move_toreg_32(0x18468, &A1); // LEA.L	$00018468,A1
  DEF_ROMLOC(19D74) : animate_sprite();                  // JSR	$0000ADA2
  DEF_ROMLOC(19D7A)
      : move_toreg_32(read_32(A0 + 0x34), &A1); // MOVEA.L	52(A0),A1
  DEF_ROMLOC(19D7E)
      : move_tomem_16(read_16(A1 + 0x8), A0 + 0x8); // MOVE.W	8(A1),8(A0)
  DEF_ROMLOC(19D84)
      : move_tomem_16(read_16(A1 + 0xC), A0 + 0xC); // MOVE.W	12(A1),12(A0)
  rom_19D8A(); // Detected flow into next function
}
ROMFUNC(rom_19D8A) {
  DEF_ROMLOC(19D8A)
      : move_tomem_8(read_8(A1 + 0x22), A0 + 0x22); // MOVE.B	34(A1),34(A0)
  DEF_ROMLOC(19D90) : move_toreg_32(0x3, &D0);      // MOVEQ.L	$03,D0
  DEF_ROMLOC(19D92) : and_toreg_8(read_8(A0 + 0x22), &D0); // AND.B
                                                           // 34(A0),D0
  DEF_ROMLOC(19D96)
      : and_tomem_8(0xFFFFFFFC, A0 + 0x1);      // ANDI.B
                                                // #$FC,1(A0)
  DEF_ROMLOC(19D9C) : or_tomem_8(D0, A0 + 0x1); // OR.B	D0,1(A0)
  DEF_ROMLOC(19DA0) : rom_DC92();
  return; // JMP	$0000DC92
}
ROMFUNC(rom_19DA6) {
  DEF_ROMLOC(19DA6)
      : move_tomem_32(0x18580, A0 + 0x4); // MOVE.L	#$00018580,4(A0)
  DEF_ROMLOC(19DAE)
      : move_tomem_16(0x246C, A0 + 0x2);            // MOVE.W
                                                    // #$246C,2(A0)
  DEF_ROMLOC(19DB4) : move_tomem_8(0x5, A0 + 0x1A); // MOVE.B	#$05,26(A0)
  DEF_ROMLOC(19DBA)
      : move_toreg_32(read_32(A0 + 0x34), &A1);    // MOVEA.L	52(A0),A1
  DEF_ROMLOC(19DBE) : cmp_tomem_8(0xA, A1 + 0x25); // CMPI.B	#$0A,37(A1)
  DEF_ROMLOC(19DC4) : if (!CCR_EQ) goto rom_19DCC; // BNE.B	$19DCC
  DEF_ROMLOC(19DC6) : tst_mem_8(A0 + 0x1);         // TST.B	1(A0)
  DEF_ROMLOC(19DCA) : if (CCR_PL) goto rom_19E3C;  // BPL.B	$19E3C
  DEF_ROMLOC(19DCC)
      : move_tomem_16(read_16(A1 + 0x8), A0 + 0x8); // MOVE.W	8(A1),8(A0)
  DEF_ROMLOC(19DD2)
      : move_tomem_16(read_16(A1 + 0xC), A0 + 0xC); // MOVE.W	12(A1),12(A0)
  DEF_ROMLOC(19DD8)
      : move_toreg_16(read_16(A0 + 0x3C), &D0);     // MOVE.W	60(A0),D0
  DEF_ROMLOC(19DDC) : cmp_tomem_8(0x4, A1 + 0x25);  // CMPI.B	#$04,37(A1)
  DEF_ROMLOC(19DE2) : if (!CCR_EQ) goto rom_19E02;  // BNE.B	$19E02
  DEF_ROMLOC(19DE4) : cmp_tomem_8(0x6, A1 + 0x28);  // CMPI.B	#$06,40(A1)
  DEF_ROMLOC(19DEA) : if (CCR_EQ) goto rom_19DFC;   // BEQ.B	$19DFC
  DEF_ROMLOC(19DEC) : tst_mem_8(A1 + 0x28);         // TST.B	40(A1)
  DEF_ROMLOC(19DF0) : if (!CCR_EQ) goto rom_19E08;  // BNE.B	$19E08
  DEF_ROMLOC(19DF2) : cmp_toreg_16(0x94, &D0);      // CMPI.W	#$0094,D0
  DEF_ROMLOC(19DF6) : if (CCR_GE) goto rom_19E08;   // BGE.B	$19E08
  DEF_ROMLOC(19DF8) : add_toreg_16(0x7, &D0);       // ADDQ.W	#$07,D0
  goto rom_19E08;                                   // BRA.B	$19E08
  DEF_ROMLOC(19DFC) : tst_mem_16(A1 + 0x3C);        // TST.W	60(A1)
  DEF_ROMLOC(19E00) : if (CCR_PL) goto rom_19E08;   // BPL.B	$19E08
  DEF_ROMLOC(19E02) : tst_reg_16(&D0);              // TST.W	D0
  DEF_ROMLOC(19E04) : if (CCR_LE) goto rom_19E08;   // BLE.B	$19E08
  DEF_ROMLOC(19E06) : sub_toreg_16(0x5, &D0);       // SUBQ.W	#$05,D0
  DEF_ROMLOC(19E08) : move_tomem_16(D0, A0 + 0x3C); // MOVE.W	D0,60(A0)
  DEF_ROMLOC(19E0C) : asr_toreg_16(0x2, &D0);       // ASR.W	#$02,D0
  DEF_ROMLOC(19E0E) : add_tomem_16(D0, A0 + 0xC);   // ADD.W	D0,12(A0)
  DEF_ROMLOC(19E12) : move_tomem_8(0x8, A0 + 0x19); // MOVE.B	#$08,25(A0)
  DEF_ROMLOC(19E18) : move_tomem_8(0xC, A0 + 0x16); // MOVE.B	#$0C,22(A0)
  DEF_ROMLOC(19E1E) : clr_mem_8(A0 + 0x20);         // CLR.B	32(A0)
  DEF_ROMLOC(19E22)
      : move_toreg_32(read_32(A0 + 0x34), &A1);    // MOVEA.L	52(A0),A1
  DEF_ROMLOC(19E26) : tst_mem_8(A1 + 0x20);        // TST.B	32(A1)
  DEF_ROMLOC(19E2A) : if (CCR_EQ) goto rom_19E38;  // BEQ.B	$19E38
  DEF_ROMLOC(19E2C) : tst_mem_8(A1 + 0x29);        // TST.B	41(A1)
  DEF_ROMLOC(19E30) : if (!CCR_EQ) goto rom_19E38; // BNE.B	$19E38
  DEF_ROMLOC(19E32)
      : move_tomem_8(0xFFFFFF84, A0 + 0x20); // MOVE.B	#$84,32(A0)
  DEF_ROMLOC(19E38) : rom_19D8A();
  return; // BRA.W	$19D8A
  DEF_ROMLOC(19E3C) : rom_DCCE();
  return; // JMP	$0000DCCE
}