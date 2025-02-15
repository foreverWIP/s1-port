// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_189E0) {
  u8 switchindex = 0;
  DEF_ROMLOC(189E0) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(189E2) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(189E6)
      : move_toreg_16(read_16(0x189EE + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(189EA): goto rom_189EE + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(189EA) : switch (switchindex) {
  case 0:
    rom_18A04();
    break;
  case 1:
    rom_18A78();
    break;
  case 2:
    rom_18D60();
    break;
  case 3:
    rom_18DBA();
    break;
  case 4:
    rom_18E26();
    break;
  }
}
ROMFUNC(rom_18A04) {
  DEF_ROMLOC(18A04)
      : move_tomem_16(read_16(A0 + 0x8), A0 + 0x30); // MOVE.W	8(A0),48(A0)
  DEF_ROMLOC(18A0A)
      : move_tomem_16(read_16(A0 + 0xC), A0 + 0x38); // MOVE.W	12(A0),56(A0)
  DEF_ROMLOC(18A10) : move_tomem_8(0xF, A0 + 0x20);  // MOVE.B	#$0F,32(A0)
  DEF_ROMLOC(18A16) : move_tomem_8(0x8, A0 + 0x21);  // MOVE.B	#$08,33(A0)
  DEF_ROMLOC(18A1C) : move_toreg_32(0x189F8, &A2);   // LEA.L	-38(PC),A2
  DEF_ROMLOC(18A20) : move_toreg_32(A0, &A1);        // MOVEA.L	A0,A1
  DEF_ROMLOC(18A22) : move_toreg_32(0x3, &D1);       // MOVEQ.L	$03,D1
  goto rom_18A40;                                    // BRA.B	$18A40
  DEF_ROMLOC(18A26) : rom_E130();                    // JSR	$0000E130
  DEF_ROMLOC(18A2C) : if (!CCR_EQ) {
    rom_18A78();
    return;
  }                                                 // BNE.B	$18A78
  DEF_ROMLOC(18A2E) : move_tomem_8(OBJ_BOSSMARBLE, A1 + offsetof(object, id)); // MOVE.B	#$73,0(A1)
  DEF_ROMLOC(18A34)
      : move_tomem_16(read_16(A0 + 0x8), A1 + 0x8); // MOVE.W	8(A0),8(A1)
  DEF_ROMLOC(18A3A)
      : move_tomem_16(read_16(A0 + 0xC), A1 + 0xC); // MOVE.W	12(A0),12(A1)
  DEF_ROMLOC(18A40) : bclr_tomem_8(0x0, A0 + 0x22); // BCLR.B	#$00,34(A0)
  DEF_ROMLOC(18A46) : clr_mem_8(A1 + 0x25);         // CLR.B	37(A1)
  DEF_ROMLOC(18A4A)
      : move_tomem_8(read_8(A2++), A1 + 0x24); // MOVE.B	(A2)+,36(A1)
  DEF_ROMLOC(18A4E)
      : move_tomem_8(read_8(A2++), A1 + 0x1C); // MOVE.B	(A2)+,28(A1)
  DEF_ROMLOC(18A52)
      : move_tomem_8(read_8(A2++), A1 + 0x18); // MOVE.B	(A2)+,24(A1)
  DEF_ROMLOC(18A56)
      : move_tomem_32(0x184B8, A1 + 0x4);             // MOVE.L	#$000184B8,4(A1)
  DEF_ROMLOC(18A5E) : move_tomem_16(0x400, A1 + 0x2); // MOVE.W	#$0400,2(A1)
  DEF_ROMLOC(18A64) : move_tomem_8(0x4, A1 + 0x1);    // MOVE.B	#$04,1(A1)
  DEF_ROMLOC(18A6A) : move_tomem_8(0x20, A1 + 0x19);  // MOVE.B	#$20,25(A1)
  DEF_ROMLOC(18A70) : move_tomem_32(A0, A1 + 0x34);   // MOVE.L	A0,52(A1)
  DEF_ROMLOC(18A74) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_18A26; // DBF.W	D1,$18A26
  rom_18A78();      // Detected flow into next function
}
ROMFUNC(rom_18A78) {
  u8 switchindex = 0;
  DEF_ROMLOC(18A78) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(18A7A) : move_toreg_8(read_8(A0 + 0x25), &D0);
  switchindex = D0 / 2; // MOVE.B	37(A0),D0
  DEF_ROMLOC(18A7E)
      : move_toreg_16(read_16(0x18AA8 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	40(PC,D0),D1
  // DEF_ROMLOC(18A82): rom_18AA8 + (s16)(D1 & 0xffff)(); // JSR
  // 36(PC,D1)
  DEF_ROMLOC(18A82) : switch (switchindex) {
  case 0:
    rom_18AB2();
    break;
  case 1:
    rom_18B5A();
    break;
  case 2:
    rom_18CA6();
    break;
  case 3:
    rom_18CDC();
    break;
  case 4:
    rom_18D32();
    break;
  }
  DEF_ROMLOC(18A86) : move_toreg_32(0x18468, &A1);         // LEA.L	$00018468,A1
  DEF_ROMLOC(18A8C) : animate_sprite();                          // JSR	$0000ADA2
  DEF_ROMLOC(18A92) : move_toreg_32(0x3, &D0);             // MOVEQ.L	$03,D0
  DEF_ROMLOC(18A94) : and_toreg_8(read_8(A0 + 0x22), &D0); // AND.B
                                                           // 34(A0),D0
  DEF_ROMLOC(18A98)
      : and_tomem_8(0xFFFFFFFC, A0 + 0x1);      // ANDI.B
                                                // #$FC,1(A0)
  DEF_ROMLOC(18A9E) : or_tomem_8(D0, A0 + 0x1); // OR.B	D0,1(A0)
  DEF_ROMLOC(18AA2) : rom_DC92();
  return; // JMP	$0000DC92
}
ROMFUNC(rom_18AB2) {
  DEF_ROMLOC(18AB2)
      : move_toreg_8(read_8(A0 + 0x3F), &D0);       // MOVE.B	63(A0),D0
  DEF_ROMLOC(18AB6) : add_tomem_8(0x2, A0 + 0x3F);  // ADDQ.B	#$02,63(A0)
  DEF_ROMLOC(18ABA) : rom_29D2();                   // JSR	$000029D2
  DEF_ROMLOC(18AC0) : asr_toreg_16(0x2, &D0);       // ASR.W	#$02,D0
  DEF_ROMLOC(18AC2) : move_tomem_16(D0, A0 + 0x12); // MOVE.W	D0,18(A0)
  DEF_ROMLOC(18AC6)
      : move_tomem_16(0xFFFFFF00, A0 + 0x10); // MOVE.W	#$FF00,16(A0)
  DEF_ROMLOC(18ACC) : rom_18050();            // BSR.W	$18050
  DEF_ROMLOC(18AD0)
      : cmp_tomem_16(0x1910, A0 + 0x30);           // CMPI.W
                                                   // #$1910,48(A0)
  DEF_ROMLOC(18AD6) : if (!CCR_EQ) goto rom_18AE4; // BNE.B	$18AE4
  DEF_ROMLOC(18AD8) : add_tomem_8(0x2, A0 + 0x25); // ADDQ.B	#$02,37(A0)
  DEF_ROMLOC(18ADC) : clr_mem_8(A0 + 0x28);        // CLR.B	40(A0)
  DEF_ROMLOC(18AE0) : clr_mem_32(A0 + 0x10);       // CLR.L	16(A0)
  DEF_ROMLOC(18AE4) : rom_29AC();                  // JSR	$000029AC
  DEF_ROMLOC(18AEA) : move_tomem_8(D0, A0 + 0x34); // MOVE.B	D0,52(A0)
  rom_18AEE(); // Detected flow into next function
}
ROMFUNC(rom_18AEE) {
  DEF_ROMLOC(18AEE)
      : move_tomem_16(read_16(A0 + 0x38), A0 + 0xC); // MOVE.W	56(A0),12(A0)
  DEF_ROMLOC(18AF4)
      : move_tomem_16(read_16(A0 + 0x30), A0 + 0x8);  // MOVE.W	48(A0),8(A0)
  DEF_ROMLOC(18AFA) : cmp_tomem_8(0x4, A0 + 0x25);    // CMPI.B	#$04,37(A0)
  DEF_ROMLOC(18B00) : if (CCR_CC) goto rom_18B40;     // BCC.B	$18B40
  DEF_ROMLOC(18B02) : tst_mem_8(A0 + 0x22);           // TST.B	34(A0)
  DEF_ROMLOC(18B06) : if (CCR_MI) goto rom_18B42;     // BMI.B	$18B42
  DEF_ROMLOC(18B08) : tst_mem_8(A0 + 0x20);           // TST.B	32(A0)
  DEF_ROMLOC(18B0C) : if (!CCR_EQ) goto rom_18B40;    // BNE.B	$18B40
  DEF_ROMLOC(18B0E) : tst_mem_8(A0 + 0x3E);           // TST.B	62(A0)
  DEF_ROMLOC(18B12) : if (!CCR_EQ) goto rom_18B24;    // BNE.B	$18B24
  DEF_ROMLOC(18B14) : move_tomem_8(0x28, A0 + 0x3E);  // MOVE.B	#$28,62(A0)
  DEF_ROMLOC(18B1A) : move_toreg_16(SFX_HITBOSS, &D0);       // MOVE.W	#$00AC,D0
  DEF_ROMLOC(18B1E) : play_sound_special();           // JSR	$00001394
  DEF_ROMLOC(18B24) : move_toreg_32(0xFFFFFB22, &A1); // LEA.L	$FB22,A1
  DEF_ROMLOC(18B28) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(18B2A) : tst_mem_16(A1);                 // TST.W	(A1)
  DEF_ROMLOC(18B2C) : if (!CCR_EQ) goto rom_18B32;    // BNE.B	$18B32
  DEF_ROMLOC(18B2E) : move_toreg_16(0xEEE, &D0);      // MOVE.W	#$0EEE,D0
  DEF_ROMLOC(18B32) : move_tomem_16(D0, A1);          // MOVE.W	D0,(A1)
  DEF_ROMLOC(18B34) : sub_tomem_8(0x1, A0 + 0x3E);    // SUBQ.B	#$01,62(A0)
  DEF_ROMLOC(18B38) : if (!CCR_EQ) goto rom_18B40;    // BNE.B	$18B40
  DEF_ROMLOC(18B3A) : move_tomem_8(0xF, A0 + 0x20);   // MOVE.B	#$0F,32(A0)
  DEF_ROMLOC(18B40) : return;                         // RTS
  DEF_ROMLOC(18B42) : move_toreg_32(0x64, &D0);       // MOVEQ.L	$64,D0
  DEF_ROMLOC(18B44) : rom_1CE42();                    // BSR.W	$1CE42
  DEF_ROMLOC(18B48) : move_tomem_8(0x4, A0 + 0x25);   // MOVE.B	#$04,37(A0)
  DEF_ROMLOC(18B4E) : move_tomem_16(0xB4, A0 + 0x3C); // MOVE.W	#$00B4,60(A0)
  DEF_ROMLOC(18B54) : clr_mem_16(A0 + 0x10);          // CLR.W	16(A0)
  DEF_ROMLOC(18B58) : return;                         // RTS
}
ROMFUNC(rom_18B5A) {
  u8 switchindex = 0;
  DEF_ROMLOC(18B5A) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(18B5C) : move_toreg_8(read_8(A0 + 0x28), &D0);
  switchindex = D0 / 2; // MOVE.B	40(A0),D0
  DEF_ROMLOC(18B60)
      : move_toreg_16(read_16(0x18B72 + (s16)(D0 & 0xffff)),
                      &D0); // MOVE.W	16(PC,D0),D0
  // DEF_ROMLOC(18B64): rom_18B72 + (s16)(D0 & 0xffff)(); // JSR
  // 12(PC,D0)
  DEF_ROMLOC(18B64) : switch (switchindex) {
  case 0:
    rom_18B7A();
    break;
  case 1:
    rom_18C4E();
    break;
  case 2:
    rom_18B7A();
    break;
  case 3:
    rom_18C4E();
    break;
  }
  DEF_ROMLOC(18B68) : and_tomem_8(0x6, A0 + 0x28); // ANDI.B	#$06,40(A0)
  rom_18AEE();                                     // BRA.W	$18AEE
}
ROMFUNC(rom_18B7A) {
  DEF_ROMLOC(18B7A) : tst_mem_16(A0 + 0x10);          // TST.W	16(A0)
  DEF_ROMLOC(18B7E) : if (!CCR_EQ) goto rom_18BAE;    // BNE.B	$18BAE
  DEF_ROMLOC(18B80) : move_toreg_32(0x40, &D0);       // MOVEQ.L	$40,D0
  DEF_ROMLOC(18B82) : cmp_tomem_16(0x22C, A0 + 0x38); // CMPI.W	#$022C,56(A0)
  DEF_ROMLOC(18B88) : if (CCR_EQ) goto rom_18B96;     // BEQ.B	$18B96
  DEF_ROMLOC(18B8A) : if (CCR_CS) goto rom_18B8E;     // BCS.B	$18B8E
  DEF_ROMLOC(18B8C) : neg_reg_16(&D0);                // NEG.W	D0
  DEF_ROMLOC(18B8E) : move_tomem_16(D0, A0 + 0x12);   // MOVE.W	D0,18(A0)
  rom_18050();
  return; // BRA.W	$18050
  DEF_ROMLOC(18B96)
      : move_tomem_16(0x200, A0 + 0x10); // MOVE.W
                                         // #$0200,16(A0)
  DEF_ROMLOC(18B9C)
      : move_tomem_16(0x100, A0 + 0x12);              // MOVE.W
                                                      // #$0100,18(A0)
  DEF_ROMLOC(18BA2) : btst_tomem_8(0x0, A0 + 0x22);   // BTST.B	#$00,34(A0)
  DEF_ROMLOC(18BA8) : if (!CCR_EQ) goto rom_18BAE;    // BNE.B	$18BAE
  DEF_ROMLOC(18BAA) : neg_mem_16(A0 + 0x10);          // NEG.W	16(A0)
  DEF_ROMLOC(18BAE) : cmp_tomem_8(0x18, A0 + 0x3E);   // CMPI.B	#$18,62(A0)
  DEF_ROMLOC(18BB4) : if (CCR_CC) goto rom_18BBE;     // BCC.B	$18BBE
  DEF_ROMLOC(18BB6) : rom_18050();                    // BSR.W	$18050
  DEF_ROMLOC(18BBA) : sub_tomem_16(0x4, A0 + 0x12);   // SUBQ.W	#$04,18(A0)
  DEF_ROMLOC(18BBE) : sub_tomem_8(0x1, A0 + 0x34);    // SUBQ.B	#$01,52(A0)
  DEF_ROMLOC(18BC2) : if (CCR_CC) goto rom_18C0C;     // BCC.B	$18C0C
  DEF_ROMLOC(18BC4) : rom_E11A();                     // JSR	$0000E11A
  DEF_ROMLOC(18BCA) : if (!CCR_EQ) goto rom_18BFA;    // BNE.B	$18BFA
  DEF_ROMLOC(18BCC) : move_tomem_8(OBJ_LAVABALL, A1 + offsetof(object, id));   // MOVE.B	#$14,0(A1)
  DEF_ROMLOC(18BD2) : move_tomem_16(0x2E8, A1 + 0xC); // MOVE.W	#$02E8,12(A1)
  DEF_ROMLOC(18BD8) : rom_29AC();                     // JSR	$000029AC
  DEF_ROMLOC(18BDE) : and_toreg_32(0xFFFF, &D0);      // ANDI.L	#$0000FFFF,D0
  DEF_ROMLOC(18BE4) : divu_toreg_16(0x50, &D0);       // DIVU.W	#$0050,D0
  DEF_ROMLOC(18BE8) : swap_reg_16(&D0);               // SWAP.W	D0
  DEF_ROMLOC(18BEA) : add_toreg_16(0x1878, &D0);      // ADDI.W	#$1878,D0
  DEF_ROMLOC(18BEE) : move_tomem_16(D0, A1 + 0x8);    // MOVE.W	D0,8(A1)
  DEF_ROMLOC(18BF2) : lsr_toreg_8(0x7, &D1);          // LSR.B	#$07,D1
  DEF_ROMLOC(18BF4) : move_tomem_16(0xFF, A1 + 0x28); // MOVE.W	#$00FF,40(A1)
  DEF_ROMLOC(18BFA) : rom_29AC();                     // JSR	$000029AC
  DEF_ROMLOC(18C00) : and_toreg_8(0x1F, &D0);         // ANDI.B	#$1F,D0
  DEF_ROMLOC(18C04) : add_toreg_8(0x40, &D0);         // ADDI.B	#$40,D0
  DEF_ROMLOC(18C08) : move_tomem_8(D0, A0 + 0x34);    // MOVE.B	D0,52(A0)
  DEF_ROMLOC(18C0C) : btst_tomem_8(0x0, A0 + 0x22);   // BTST.B	#$00,34(A0)
  DEF_ROMLOC(18C12) : if (CCR_EQ) goto rom_18C24;     // BEQ.B	$18C24
  DEF_ROMLOC(18C14)
      : cmp_tomem_16(0x1910, A0 + 0x30);          // CMPI.W
                                                  // #$1910,48(A0)
  DEF_ROMLOC(18C1A) : if (CCR_LT) goto rom_18C4C; // BLT.B	$18C4C
  DEF_ROMLOC(18C1C)
      : move_tomem_16(0x1910, A0 + 0x30); // MOVE.W
                                          // #$1910,48(A0)
  goto rom_18C32;                         // BRA.B	$18C32
  DEF_ROMLOC(18C24)
      : cmp_tomem_16(0x1830, A0 + 0x30);          // CMPI.W
                                                  // #$1830,48(A0)
  DEF_ROMLOC(18C2A) : if (CCR_GT) goto rom_18C4C; // BGT.B	$18C4C
  DEF_ROMLOC(18C2C)
      : move_tomem_16(0x1830, A0 + 0x30);    // MOVE.W
                                             // #$1830,48(A0)
  DEF_ROMLOC(18C32) : clr_mem_16(A0 + 0x10); // CLR.W	16(A0)
  DEF_ROMLOC(18C36)
      : move_tomem_16(0xFFFFFE80, A0 + 0x12);         // MOVE.W	#$FE80,18(A0)
  DEF_ROMLOC(18C3C) : cmp_tomem_16(0x22C, A0 + 0x38); // CMPI.W	#$022C,56(A0)
  DEF_ROMLOC(18C42) : if (CCR_CC) goto rom_18C48;     // BCC.B	$18C48
  DEF_ROMLOC(18C44) : neg_mem_16(A0 + 0x12);          // NEG.W	18(A0)
  DEF_ROMLOC(18C48) : add_tomem_8(0x2, A0 + 0x28);    // ADDQ.B	#$02,40(A0)
  DEF_ROMLOC(18C4C) : return;                         // RTS
}
ROMFUNC(rom_18C4E) {
  DEF_ROMLOC(18C4E) : rom_18050(); // BSR.W	$18050
  DEF_ROMLOC(18C52)
      : move_toreg_16(read_16(A0 + 0x38), &D0);       // MOVE.W	56(A0),D0
  DEF_ROMLOC(18C56) : sub_toreg_16(0x22C, &D0);       // SUBI.W	#$022C,D0
  DEF_ROMLOC(18C5A) : if (CCR_GT) goto rom_18CA4;     // BGT.B	$18CA4
  DEF_ROMLOC(18C5C) : move_toreg_16(0x22C, &D0);      // MOVE.W	#$022C,D0
  DEF_ROMLOC(18C60) : tst_mem_16(A0 + 0x12);          // TST.W	18(A0)
  DEF_ROMLOC(18C64) : if (CCR_EQ) goto rom_18C9A;     // BEQ.B	$18C9A
  DEF_ROMLOC(18C66) : clr_mem_16(A0 + 0x12);          // CLR.W	18(A0)
  DEF_ROMLOC(18C6A) : move_tomem_16(0x50, A0 + 0x3C); // MOVE.W	#$0050,60(A0)
  DEF_ROMLOC(18C70) : bchg_tomem_8(0x0, A0 + 0x22);   // BCHG.B	#$00,34(A0)
  DEF_ROMLOC(18C76) : rom_E11A();                     // JSR	$0000E11A
  DEF_ROMLOC(18C7C) : if (!CCR_EQ) goto rom_18C9A;    // BNE.B	$18C9A
  DEF_ROMLOC(18C7E)
      : move_tomem_16(read_16(A0 + 0x30), A1 + 0x8); // MOVE.W	48(A0),8(A1)
  DEF_ROMLOC(18C84)
      : move_tomem_16(read_16(A0 + 0x38), A1 + 0xC); // MOVE.W	56(A0),12(A1)
  DEF_ROMLOC(18C8A) : add_tomem_16(0x18, A1 + 0xC);  // ADDI.W	#$0018,12(A1)
  DEF_ROMLOC(18C90) : move_tomem_8(OBJ_BOSSFIRE, A1 + offsetof(object, id));        // MOVE.B	#$74,(A1)
  DEF_ROMLOC(18C94) : move_tomem_8(0x1, A1 + 0x28);  // MOVE.B	#$01,40(A1)
  DEF_ROMLOC(18C9A) : sub_tomem_16(0x1, A0 + 0x3C);  // SUBQ.W	#$01,60(A0)
  DEF_ROMLOC(18C9E) : if (!CCR_EQ) goto rom_18CA4;   // BNE.B	$18CA4
  DEF_ROMLOC(18CA0) : add_tomem_8(0x2, A0 + 0x28);   // ADDQ.B	#$02,40(A0)
  DEF_ROMLOC(18CA4) : return;                        // RTS
}
ROMFUNC(rom_18CA6) {
  DEF_ROMLOC(18CA6) : sub_tomem_16(0x1, A0 + 0x3C); // SUBQ.W	#$01,60(A0)
  DEF_ROMLOC(18CAA) : if (CCR_MI) goto rom_18CB0;   // BMI.B	$18CB0
  rom_1800C();
  return;                                           // BRA.W	$1800C
  DEF_ROMLOC(18CB0) : bset_tomem_8(0x0, A0 + 0x22); // BSET.B	#$00,34(A0)
  DEF_ROMLOC(18CB6) : bclr_tomem_8(0x7, A0 + 0x22); // BCLR.B	#$07,34(A0)
  DEF_ROMLOC(18CBC) : clr_mem_16(A0 + 0x10);        // CLR.W	16(A0)
  DEF_ROMLOC(18CC0) : add_tomem_8(0x2, A0 + 0x25);  // ADDQ.B	#$02,37(A0)
  DEF_ROMLOC(18CC4)
      : move_tomem_16(0xFFFFFFDA, A0 + 0x3C);        // MOVE.W	#$FFDA,60(A0)
  DEF_ROMLOC(18CCA) : tst_mem_8(0xFFFFF7A7);         // TST.B	$F7A7
  DEF_ROMLOC(18CCE) : if (!CCR_EQ) goto rom_18CDA;   // BNE.B	$18CDA
  DEF_ROMLOC(18CD0) : move_tomem_8(0x1, 0xFFFFF7A7); // MOVE.B	#$01,$F7A7
  DEF_ROMLOC(18CD6) : clr_mem_16(A0 + 0x12);         // CLR.W	18(A0)
  DEF_ROMLOC(18CDA) : return;                        // RTS
}
ROMFUNC(rom_18CDC) {
  DEF_ROMLOC(18CDC) : add_tomem_16(0x1, A0 + 0x3C);   // ADDQ.W	#$01,60(A0)
  DEF_ROMLOC(18CE0) : if (CCR_EQ) goto rom_18CF4;     // BEQ.B	$18CF4
  DEF_ROMLOC(18CE2) : if (CCR_PL) goto rom_18CFE;     // BPL.B	$18CFE
  DEF_ROMLOC(18CE4) : cmp_tomem_16(0x270, A0 + 0x38); // CMPI.W	#$0270,56(A0)
  DEF_ROMLOC(18CEA) : if (CCR_CC) goto rom_18CF4;     // BCC.B	$18CF4
  DEF_ROMLOC(18CEC) : add_tomem_16(0x18, A0 + 0x12);  // ADDI.W	#$0018,18(A0)
  goto rom_18D2A;                                     // BRA.B	$18D2A
  DEF_ROMLOC(18CF4) : clr_mem_16(A0 + 0x12);          // CLR.W	18(A0)
  DEF_ROMLOC(18CF8) : clr_mem_16(A0 + 0x3C);          // CLR.W	60(A0)
  goto rom_18D2A;                                     // BRA.B	$18D2A
  DEF_ROMLOC(18CFE) : cmp_tomem_16(0x30, A0 + 0x3C);  // CMPI.W	#$0030,60(A0)
  DEF_ROMLOC(18D04) : if (CCR_CS) goto rom_18D16;     // BCS.B	$18D16
  DEF_ROMLOC(18D06) : if (CCR_EQ) goto rom_18D1C;     // BEQ.B	$18D1C
  DEF_ROMLOC(18D08) : cmp_tomem_16(0x38, A0 + 0x3C);  // CMPI.W	#$0038,60(A0)
  DEF_ROMLOC(18D0E) : if (CCR_CS) goto rom_18D2A;     // BCS.B	$18D2A
  DEF_ROMLOC(18D10) : add_tomem_8(0x2, A0 + 0x25);    // ADDQ.B	#$02,37(A0)
  goto rom_18D2A;                                     // BRA.B	$18D2A
  DEF_ROMLOC(18D16) : sub_tomem_16(0x8, A0 + 0x12);   // SUBQ.W	#$08,18(A0)
  goto rom_18D2A;                                     // BRA.B	$18D2A
  DEF_ROMLOC(18D1C) : clr_mem_16(A0 + 0x12);          // CLR.W	18(A0)
  DEF_ROMLOC(18D20) : move_toreg_16(BGM_MZ, &D0);       // MOVE.W	#$0083,D0
  DEF_ROMLOC(18D24) : play_sound();                   // JSR	$0000138E
  DEF_ROMLOC(18D2A) : rom_18050();                    // BSR.W	$18050
  rom_18AEE();                                        // BRA.W	$18AEE
}
ROMFUNC(rom_18D32) {
  DEF_ROMLOC(18D32)
      : move_tomem_16(0x500, A0 + 0x10); // MOVE.W
                                         // #$0500,16(A0)
  DEF_ROMLOC(18D38)
      : move_tomem_16(0xFFFFFFC0, A0 + 0x12); // MOVE.W	#$FFC0,18(A0)
  DEF_ROMLOC(18D3E)
      : cmp_tomem_16(0x1960, 0xFFFFF72A);            // CMPI.W
                                                     // #$1960,$F72A
  DEF_ROMLOC(18D44) : if (CCR_CC) goto rom_18D4C;    // BCC.B	$18D4C
  DEF_ROMLOC(18D46) : add_tomem_16(0x2, 0xFFFFF72A); // ADDQ.W	#$02,$F72A
  goto rom_18D52;                                    // BRA.B	$18D52
  DEF_ROMLOC(18D4C) : tst_mem_8(A0 + 0x1);           // TST.B	1(A0)
  DEF_ROMLOC(18D50) : if (CCR_PL) goto rom_18D5A;    // BPL.B	$18D5A
  DEF_ROMLOC(18D52) : rom_18050();                   // BSR.W	$18050
  rom_18AEE();
  return; // BRA.W	$18AEE
  DEF_ROMLOC(18D5A) : rom_DCCE();
  return; // JMP	$0000DCCE
}
ROMFUNC(rom_18D60) {
  DEF_ROMLOC(18D60) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(18D62) : move_toreg_32(0x1, &D1); // MOVEQ.L	$01,D1
  DEF_ROMLOC(18D64)
      : move_toreg_32(read_32(A0 + 0x34), &A1); // MOVEA.L	52(A0),A1
  DEF_ROMLOC(18D68)
      : move_toreg_8(read_8(A1 + 0x25), &D0);       // MOVE.B	37(A1),D0
  DEF_ROMLOC(18D6C) : sub_toreg_16(0x2, &D0);       // SUBQ.W	#$02,D0
  DEF_ROMLOC(18D6E) : if (!CCR_EQ) goto rom_18D82;  // BNE.B	$18D82
  DEF_ROMLOC(18D70) : btst_tomem_8(0x1, A1 + 0x28); // BTST.B	#$01,40(A1)
  DEF_ROMLOC(18D76) : if (CCR_EQ) goto rom_18D8A;   // BEQ.B	$18D8A
  DEF_ROMLOC(18D78) : tst_mem_16(A1 + 0x12);        // TST.W	18(A1)
  DEF_ROMLOC(18D7C) : if (!CCR_EQ) goto rom_18D8A;  // BNE.B	$18D8A
  DEF_ROMLOC(18D7E) : move_toreg_32(0x4, &D1);      // MOVEQ.L	$04,D1
  goto rom_18D9E;                                   // BRA.B	$18D9E
  DEF_ROMLOC(18D82) : sub_toreg_8(0x2, &D0);        // SUBQ.B	#$02,D0
  DEF_ROMLOC(18D84) : if (CCR_MI) goto rom_18D8A;   // BMI.B	$18D8A
  DEF_ROMLOC(18D86) : move_toreg_32(0xA, &D1);      // MOVEQ.L	$0A,D1
  goto rom_18D9E;                                   // BRA.B	$18D9E
  DEF_ROMLOC(18D8A) : tst_mem_8(A1 + 0x20);         // TST.B	32(A1)
  DEF_ROMLOC(18D8E) : if (!CCR_EQ) goto rom_18D94;  // BNE.B	$18D94
  DEF_ROMLOC(18D90) : move_toreg_32(0x5, &D1);      // MOVEQ.L	$05,D1
  goto rom_18D9E;                                   // BRA.B	$18D9E
  DEF_ROMLOC(18D94) : cmp_tomem_8(0x4, 0xFFFFD024); // CMPI.B	#$04,$D024
  DEF_ROMLOC(18D9A) : if (CCR_CS) goto rom_18D9E;   // BCS.B	$18D9E
  DEF_ROMLOC(18D9C) : move_toreg_32(0x4, &D1);      // MOVEQ.L	$04,D1
  DEF_ROMLOC(18D9E) : move_tomem_8(D1, A0 + 0x1C);  // MOVE.B	D1,28(A0)
  DEF_ROMLOC(18DA2) : sub_toreg_8(0x4, &D0);        // SUBQ.B	#$04,D0
  DEF_ROMLOC(18DA4) : if (!CCR_EQ) goto rom_18DB2;  // BNE.B	$18DB2
  DEF_ROMLOC(18DA6) : move_tomem_8(0x6, A0 + 0x1C); // MOVE.B	#$06,28(A0)
  DEF_ROMLOC(18DAC) : tst_mem_8(A0 + 0x1);          // TST.B	1(A0)
  DEF_ROMLOC(18DB0) : if (CCR_PL) goto rom_18DB4;   // BPL.B	$18DB4
  DEF_ROMLOC(18DB2) : rom_18DEE();
  return; // BRA.B	$18DEE
  DEF_ROMLOC(18DB4) : rom_DCCE();
  return; // JMP	$0000DCCE
}
ROMFUNC(rom_18DBA) {
  DEF_ROMLOC(18DBA) : move_tomem_8(0x7, A0 + 0x1C); // MOVE.B	#$07,28(A0)
  DEF_ROMLOC(18DC0)
      : move_toreg_32(read_32(A0 + 0x34), &A1);     // MOVEA.L	52(A0),A1
  DEF_ROMLOC(18DC4) : cmp_tomem_8(0x8, A1 + 0x25);  // CMPI.B	#$08,37(A1)
  DEF_ROMLOC(18DCA) : if (CCR_LT) goto rom_18DDA;   // BLT.B	$18DDA
  DEF_ROMLOC(18DCC) : move_tomem_8(0xB, A0 + 0x1C); // MOVE.B	#$0B,28(A0)
  DEF_ROMLOC(18DD2) : tst_mem_8(A0 + 0x1);          // TST.B	1(A0)
  DEF_ROMLOC(18DD6) : if (CCR_PL) goto rom_18DE8;   // BPL.B	$18DE8
  goto rom_18DE6;                                   // BRA.B	$18DE6
  DEF_ROMLOC(18DDA) : tst_mem_16(A1 + 0x10);        // TST.W	16(A1)
  DEF_ROMLOC(18DDE) : if (CCR_EQ) goto rom_18DE6;   // BEQ.B	$18DE6
  DEF_ROMLOC(18DE0) : move_tomem_8(0x8, A0 + 0x1C); // MOVE.B	#$08,28(A0)
  DEF_ROMLOC(18DE6) : rom_18DEE();
  return; // BRA.B	$18DEE
  DEF_ROMLOC(18DE8) : rom_DCCE();
  return; // JMP	$0000DCCE
}
ROMFUNC(rom_18DEE) {
  DEF_ROMLOC(18DEE) : move_toreg_32(0x18468, &A1); // LEA.L	$00018468,A1
  DEF_ROMLOC(18DF4) : animate_sprite();                  // JSR	$0000ADA2
  rom_18DFA(); // Detected flow into next function
}
ROMFUNC(rom_18DFA) {
  DEF_ROMLOC(18DFA)
      : move_toreg_32(read_32(A0 + 0x34), &A1); // MOVEA.L	52(A0),A1
  DEF_ROMLOC(18DFE)
      : move_tomem_16(read_16(A1 + 0x8), A0 + 0x8); // MOVE.W	8(A1),8(A0)
  DEF_ROMLOC(18E04)
      : move_tomem_16(read_16(A1 + 0xC), A0 + 0xC); // MOVE.W	12(A1),12(A0)
  DEF_ROMLOC(18E0A)
      : move_tomem_8(read_8(A1 + 0x22), A0 + 0x22); // MOVE.B	34(A1),34(A0)
  DEF_ROMLOC(18E10) : move_toreg_32(0x3, &D0);      // MOVEQ.L	$03,D0
  DEF_ROMLOC(18E12) : and_toreg_8(read_8(A0 + 0x22), &D0); // AND.B
                                                           // 34(A0),D0
  DEF_ROMLOC(18E16)
      : and_tomem_8(0xFFFFFFFC, A0 + 0x1);      // ANDI.B
                                                // #$FC,1(A0)
  DEF_ROMLOC(18E1C) : or_tomem_8(D0, A0 + 0x1); // OR.B	D0,1(A0)
  DEF_ROMLOC(18E20) : rom_DC92();
  return; // JMP	$0000DC92
}
ROMFUNC(rom_18E26) {
  DEF_ROMLOC(18E26)
      : move_toreg_32(read_32(A0 + 0x34), &A1);    // MOVEA.L	52(A0),A1
  DEF_ROMLOC(18E2A) : cmp_tomem_8(0x8, A1 + 0x25); // CMPI.B	#$08,37(A1)
  DEF_ROMLOC(18E30) : if (!CCR_EQ) goto rom_18E38; // BNE.B	$18E38
  DEF_ROMLOC(18E32) : tst_mem_8(A0 + 0x1);         // TST.B	1(A0)
  DEF_ROMLOC(18E36) : if (CCR_PL) goto rom_18E4E;  // BPL.B	$18E4E
  DEF_ROMLOC(18E38)
      : move_tomem_32(0x18580, A0 + 0x4); // MOVE.L	#$00018580,4(A0)
  DEF_ROMLOC(18E40)
      : move_tomem_16(0x246C, A0 + 0x2);            // MOVE.W
                                                    // #$246C,2(A0)
  DEF_ROMLOC(18E46) : move_tomem_8(0x4, A0 + 0x1A); // MOVE.B	#$04,26(A0)
  rom_18DFA();
  return; // BRA.B	$18DFA
  DEF_ROMLOC(18E4E) : rom_DCCE();
  return; // JMP	$0000DCCE
}