// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_F1B4) {
  u8 switchindex = 0;
  DEF_ROMLOC(F1B4) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(F1B6) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(F1BA)
      : move_toreg_16(read_16(0xF1F0 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	52(PC,D0),D1
  // DEF_ROMLOC(F1BE): rom_F1F0 + (s16)(D1 & 0xffff)(); // JSR	48(PC,D1)
  DEF_ROMLOC(F1BE) : switch (switchindex) {
  case 0:
    rom_F1FA();
    break;
  case 1:
    rom_F21E();
    break;
  case 2:
    rom_F248();
    break;
  case 3:
    rom_F2E0();
    break;
  case 4:
    rom_F3A6();
    break;
  }
  DEF_ROMLOC(F1C2) : move_toreg_32(0xF3A8, &A1); // LEA.L	$0000F3A8,A1
  DEF_ROMLOC(F1C8) : rom_ADA2();                 // BSR.W	$ADA2
  DEF_ROMLOC(F1CC) : rom_DC92();                 // BSR.W	$DC92
  DEF_ROMLOC(F1D0) : move_toreg_16(read_16(A0 + 0x8), &D0); // MOVE.W	8(A0),D0
  DEF_ROMLOC(F1D4) : and_toreg_16(0xFFFFFF80, &D0);         // ANDI.W	#$FF80,D0
  DEF_ROMLOC(F1D8)
      : move_toreg_16(read_16(0xFFFFF700), &D1);    // MOVE.W	$F700,D1
  DEF_ROMLOC(F1DC) : sub_toreg_16(0x80, &D1);       // SUBI.W	#$0080,D1
  DEF_ROMLOC(F1E0) : and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
  DEF_ROMLOC(F1E4) : sub_toreg_16(D1, &D0);         // SUB.W	D1,D0
  DEF_ROMLOC(F1E6) : cmp_toreg_16(0x280, &D0);      // CMPI.W	#$0280,D0
  DEF_ROMLOC(F1EA) : if (CCR_HI) {
    rom_DCCE();
    return;
  }                          // BHI.W	$DCCE
  DEF_ROMLOC(F1EE) : return; // RTS
}
ROMFUNC(rom_F1FA) {
  DEF_ROMLOC(F1FA) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(F1FE)
      : move_tomem_32(0xF3C4, A0 + 0x4);             // MOVE.L	#$0000F3C4,4(A0)
  DEF_ROMLOC(F206) : move_tomem_16(0x680, A0 + 0x2); // MOVE.W	#$0680,2(A0)
  DEF_ROMLOC(F20C) : move_tomem_8(0x4, A0 + 0x1);    // MOVE.B	#$04,1(A0)
  DEF_ROMLOC(F212) : move_tomem_8(0x18, A0 + 0x19);  // MOVE.B	#$18,25(A0)
  DEF_ROMLOC(F218) : move_tomem_8(0x4, A0 + 0x18);   // MOVE.B	#$04,24(A0)
  rom_F21E(); // Detected flow into next function
}
ROMFUNC(rom_F21E) {
  DEF_ROMLOC(F21E)
      : move_toreg_16(read_16(0xFFFFD008), &D0); // MOVE.W	$D008,D0
  DEF_ROMLOC(F222)
      : sub_toreg_16(read_16(A0 + 0x8), &D0);   // SUB.W	8(A0),D0
  DEF_ROMLOC(F226) : if (CCR_CS) goto rom_F246; // BCS.B	$F246
  DEF_ROMLOC(F228) : cmp_toreg_16(0x20, &D0);   // CMPI.W	#$0020,D0
  DEF_ROMLOC(F22C) : if (CCR_CC) goto rom_F246; // BCC.B	$F246
  DEF_ROMLOC(F22E) : move_toreg_16(0xCF, &D0);  // MOVE.W	#$00CF,D0
  DEF_ROMLOC(F232) : play_sound();              // JSR	$0000138E
  DEF_ROMLOC(F238) : clr_mem_8(0xFFFFFE1E);     // CLR.B	$FE1E
  DEF_ROMLOC(F23C)
      : move_tomem_16(read_16(0xFFFFF72A),
                      0xFFFFF728);                // MOVE.W	$F72A,$F728
  DEF_ROMLOC(F242) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(F246) : return;                      // RTS
}
ROMFUNC(rom_F248) {
  DEF_ROMLOC(F248) : sub_tomem_16(0x1, A0 + 0x30);   // SUBQ.W	#$01,48(A0)
  DEF_ROMLOC(F24C) : if (CCR_PL) goto rom_F264;      // BPL.B	$F264
  DEF_ROMLOC(F24E) : move_tomem_16(0x3C, A0 + 0x30); // MOVE.W	#$003C,48(A0)
  DEF_ROMLOC(F254) : add_tomem_8(0x1, A0 + 0x1C);    // ADDQ.B	#$01,28(A0)
  DEF_ROMLOC(F258) : cmp_tomem_8(0x3, A0 + 0x1C);    // CMPI.B	#$03,28(A0)
  DEF_ROMLOC(F25E) : if (!CCR_EQ) goto rom_F264;     // BNE.B	$F264
  DEF_ROMLOC(F260) : add_tomem_8(0x2, A0 + 0x24);    // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(F264) : sub_tomem_16(0x1, A0 + 0x32);   // SUBQ.W	#$01,50(A0)
  DEF_ROMLOC(F268) : if (CCR_PL) goto rom_F2CE;      // BPL.B	$F2CE
  DEF_ROMLOC(F26A) : move_tomem_16(0xB, A0 + 0x32);  // MOVE.W	#$000B,50(A0)
  DEF_ROMLOC(F270) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(F272)
      : move_toreg_8(read_8(A0 + 0x34), &D0);     // MOVE.B	52(A0),D0
  DEF_ROMLOC(F276) : add_tomem_8(0x2, A0 + 0x34); // ADDQ.B	#$02,52(A0)
  DEF_ROMLOC(F27A) : and_tomem_8(0xE, A0 + 0x34); // ANDI.B	#$0E,52(A0)
  DEF_ROMLOC(F280)
      : move_toreg_32(0xF2D0 + (s16)(D0 & 0xffff),
                      &A2);                                // LEA.L	78(PC,D0),A2
  DEF_ROMLOC(F284) : rom_E11A();                           // BSR.W	$E11A
  DEF_ROMLOC(F288) : if (!CCR_EQ) goto rom_F2CE;           // BNE.B	$F2CE
  DEF_ROMLOC(F28A) : move_tomem_8(0x25, A1 + 0x0);         // MOVE.B	#$25,0(A1)
  DEF_ROMLOC(F290) : move_tomem_8(0x6, A1 + 0x24);         // MOVE.B	#$06,36(A1)
  DEF_ROMLOC(F296) : move_toreg_8(read_8(A2++), &D0);      // MOVE.B	(A2)+,D0
  DEF_ROMLOC(F298) : ext_reg_16(&D0);                      // EXT.W	D0
  DEF_ROMLOC(F29A) : add_toreg_16(read_16(A0 + 0x8), &D0); // ADD.W	8(A0),D0
  DEF_ROMLOC(F29E) : move_tomem_16(D0, A1 + 0x8);          // MOVE.W	D0,8(A1)
  DEF_ROMLOC(F2A2) : move_toreg_8(read_8(A2++), &D0);      // MOVE.B	(A2)+,D0
  DEF_ROMLOC(F2A4) : ext_reg_16(&D0);                      // EXT.W	D0
  DEF_ROMLOC(F2A6) : add_toreg_16(read_16(A0 + 0xC), &D0); // ADD.W
                                                           // 12(A0),D0
  DEF_ROMLOC(F2AA) : move_tomem_16(D0, A1 + 0xC);          // MOVE.W	D0,12(A1)
  DEF_ROMLOC(F2AE) : move_tomem_32(0xA610, A1 + 0x4); // MOVE.L	#$0000A610,4(A1)
  DEF_ROMLOC(F2B6) : move_tomem_16(0x27B2, A1 + 0x2); // MOVE.W	#$27B2,2(A1)
  DEF_ROMLOC(F2BC) : move_tomem_8(0x4, A1 + 0x1);     // MOVE.B	#$04,1(A1)
  DEF_ROMLOC(F2C2) : move_tomem_8(0x2, A1 + 0x18);    // MOVE.B	#$02,24(A1)
  DEF_ROMLOC(F2C8) : move_tomem_8(0x8, A1 + 0x19);    // MOVE.B	#$08,25(A1)
  DEF_ROMLOC(F2CE) : return;                          // RTS
}
ROMFUNC(rom_F2E0) {
  DEF_ROMLOC(F2E0) : tst_mem_16(0xFFFFFE08);        // TST.W	$FE08
  DEF_ROMLOC(F2E4) : if (!CCR_EQ) return;           // BNE.W	$F37A
  DEF_ROMLOC(F2E8) : btst_tomem_8(0x1, 0xFFFFD022); // BTST.B	#$01,$D022
  DEF_ROMLOC(F2EE) : if (!CCR_EQ) goto rom_F2FC;    // BNE.B	$F2FC
  DEF_ROMLOC(F2F0) : move_tomem_8(0x1, 0xFFFFF7CC); // MOVE.B	#$01,$F7CC
  DEF_ROMLOC(F2F6)
      : move_tomem_16(0x800, 0xFFFFF602);       // MOVE.W
                                                // #$0800,$F602
  DEF_ROMLOC(F2FC) : tst_mem_8(0xFFFFD000);     // TST.B	$D000
  DEF_ROMLOC(F300) : if (CCR_EQ) goto rom_F312; // BEQ.B	$F312
  DEF_ROMLOC(F302)
      : move_toreg_16(read_16(0xFFFFD008), &D0); // MOVE.W	$D008,D0
  DEF_ROMLOC(F306)
      : move_toreg_16(read_16(0xFFFFF72A), &D1);  // MOVE.W	$F72A,D1
  DEF_ROMLOC(F30A) : add_toreg_16(0x128, &D1);    // ADDI.W	#$0128,D1
  DEF_ROMLOC(F30E) : cmp_toreg_16(D1, &D0);       // CMP.W	D1,D0
  DEF_ROMLOC(F310) : if (CCR_CS) return;          // BCS.B	$F37A
  DEF_ROMLOC(F312) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  rom_F316(); // Detected flow into next function
}
ROMFUNC(rom_F316) {
  DEF_ROMLOC(F316) : tst_mem_8(0xFFFFD5C0);      // TST.B	$D5C0
  DEF_ROMLOC(F31A) : if (!CCR_EQ) goto rom_F37A; // BNE.B	$F37A
  DEF_ROMLOC(F31C)
      : move_tomem_16(read_16(0xFFFFF72A),
                      0xFFFFF728);                   // MOVE.W	$F72A,$F728
  DEF_ROMLOC(F322) : clr_mem_8(0xFFFFFE2D);          // CLR.B	$FE2D
  DEF_ROMLOC(F326) : clr_mem_8(0xFFFFFE1E);          // CLR.B	$FE1E
  DEF_ROMLOC(F32A) : move_tomem_8(0x3A, 0xFFFFD5C0); // MOVE.B	#$3A,$D5C0
  DEF_ROMLOC(F330) : move_toreg_32(0x10, &D0);       // MOVEQ.L	$10,D0
  DEF_ROMLOC(F332) : rom_15AA();                     // JSR	$000015AA
  DEF_ROMLOC(F338) : move_tomem_8(0x1, 0xFFFFF7D6);  // MOVE.B	#$01,$F7D6
  DEF_ROMLOC(F33E) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(F340)
      : move_toreg_8(read_8(0xFFFFFE23), &D0); // MOVE.B	$FE23,D0
  DEF_ROMLOC(F344) : mulu_toreg_16(0x3C, &D0); // MULU.W	#$003C,D0
  DEF_ROMLOC(F348) : move_toreg_32(0x0, &D1);  // MOVEQ.L	$00,D1
  DEF_ROMLOC(F34A)
      : move_toreg_8(read_8(0xFFFFFE24), &D1);  // MOVE.B	$FE24,D1
  DEF_ROMLOC(F34E) : add_toreg_16(D1, &D0);     // ADD.W	D1,D0
  DEF_ROMLOC(F350) : divu_toreg_16(0xF, &D0);   // DIVU.W	#$000F,D0
  DEF_ROMLOC(F354) : move_toreg_32(0x14, &D1);  // MOVEQ.L	$14,D1
  DEF_ROMLOC(F356) : cmp_toreg_16(D1, &D0);     // CMP.W	D1,D0
  DEF_ROMLOC(F358) : if (CCR_CS) goto rom_F35C; // BCS.B	$F35C
  DEF_ROMLOC(F35A) : move_toreg_16(D1, &D0);    // MOVE.W	D1,D0
  DEF_ROMLOC(F35C) : add_toreg_16(D0, &D0);     // ADD.W	D0,D0
  DEF_ROMLOC(F35E)
      : move_tomem_16(read_16(0xF37C + (s16)(D0 & 0xffff)),
                      0xFFFFF7D2); // MOVE.W	28(PC,D0),$F7D2
  DEF_ROMLOC(F364)
      : move_toreg_16(read_16(0xFFFFFE20), &D0);    // MOVE.W	$FE20,D0
  DEF_ROMLOC(F368) : mulu_toreg_16(0xA, &D0);       // MULU.W	#$000A,D0
  DEF_ROMLOC(F36C) : move_tomem_16(D0, 0xFFFFF7D4); // MOVE.W	D0,$F7D4
  DEF_ROMLOC(F370) : move_toreg_16(0x8E, &D0);      // MOVE.W	#$008E,D0
  DEF_ROMLOC(F374) : play_sound_special();          // JSR	$00001394
  DEF_ROMLOC(F37A) : return;                        // RTS
}
ROMFUNC(rom_F3A6) {
  DEF_ROMLOC(F3A6) : return; // RTS
}