// #define CHECK_STUFF 1
#include "game.h"
#include "opcodes.h"
#include "system.h"

void level_palette_cycle(void) {
  u8 switchindex = 0;
  DEF_ROMLOC(1934) : move_toreg_32(0x0, &D2); // MOVEQ.L	$00,D2
  DEF_ROMLOC(1936) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(1938) : move_toreg_8(read_8(0xFFFFFE10), &D0);
  switchindex = D0;                         // MOVE.B	$FE10,D0
  DEF_ROMLOC(193C) : add_toreg_16(D0, &D0); // ADD.W	D0,D0
  DEF_ROMLOC(193E)
      : move_toreg_16(read_16(0x1946 + (s16)(D0 & 0xffff)),
                      &D0); // MOVE.W	6(PC,D0),D0
  // DEF_ROMLOC(1942): goto rom_1946 + (s16)(D0 & 0xffff); // JMP	2(PC,D0)
  DEF_ROMLOC(1942) : switch (switchindex) {
  case 0:
    level_palette_cycle_ghz(false);
    break;
  case 1:
    level_palette_cycle_lz();
    break;
  case 2:
    level_palette_cycle_mz();
    break;
  case 3:
    level_palette_cycle_slz();
    break;
  case 4:
    level_palette_cycle_syz();
    break;
  case 5:
    level_palette_cycle_sbz();
    break;
  case 6:
    level_palette_cycle_ghz(false);
    break;
  }
}
void level_palette_cycle_ghz(bool title_screen) {
	if (title_screen) {
		A0 = 0x1B5E;
	} else {
		A0 = 0x1B7E;
	}
	DEF_ROMLOC(1962) : sub_tomem_16(0x1, 0xFFFFF634);  // SUBQ.W	#$01,$F634
	DEF_ROMLOC(1966) : if (CCR_PL) goto rom_1988;      // BPL.B	$1988
	DEF_ROMLOC(1968) : move_tomem_16(0x5, 0xFFFFF634); // MOVE.W	#$0005,$F634
	DEF_ROMLOC(196E)
		: move_toreg_16(read_16(0xFFFFF632), &D0);     // MOVE.W	$F632,D0
	DEF_ROMLOC(1972) : add_tomem_16(0x1, 0xFFFFF632);  // ADDQ.W	#$01,$F632
	DEF_ROMLOC(1976) : and_toreg_16(0x3, &D0);         // ANDI.W	#$0003,D0
	DEF_ROMLOC(197A) : lsl_toreg_16(0x3, &D0);         // LSL.W	#$03,D0
	DEF_ROMLOC(197C) : move_toreg_32(0xFFFFFB50, &A1); // LEA.L	$FB50,A1
	DEF_ROMLOC(1980)
		: move_tomem_32(read_32((s32)A0 + (s8)0x0 + (s16)D0),
						(A1 += 4, A1 - 4)); // MOVE.L	0(A0,D0),(A1)+
	DEF_ROMLOC(1984)
		: move_tomem_32(read_32((s32)A0 + (s8)0x4 + (s16)D0),
						A1);   // MOVE.L	4(A0,D0),(A1)
	DEF_ROMLOC(1988) : return; // RTS
}
void level_palette_cycle_lz(void) {
  DEF_ROMLOC(198A) : sub_tomem_16(0x1, 0xFFFFF634);  // SUBQ.W	#$01,$F634
  DEF_ROMLOC(198E) : if (CCR_PL) goto rom_19D0;      // BPL.B	$19D0
  DEF_ROMLOC(1990) : move_tomem_16(0x2, 0xFFFFF634); // MOVE.W	#$0002,$F634
  DEF_ROMLOC(1996)
      : move_toreg_16(read_16(0xFFFFF632), &D0);     // MOVE.W	$F632,D0
  DEF_ROMLOC(199A) : add_tomem_16(0x1, 0xFFFFF632);  // ADDQ.W	#$01,$F632
  DEF_ROMLOC(199E) : and_toreg_16(0x3, &D0);         // ANDI.W	#$0003,D0
  DEF_ROMLOC(19A2) : lsl_toreg_16(0x3, &D0);         // LSL.W	#$03,D0
  DEF_ROMLOC(19A4) : move_toreg_32(0x1B9E, &A0);     // LEA.L	$00001B9E,A0
  DEF_ROMLOC(19AA) : cmp_tomem_8(0x3, 0xFFFFFE11);   // CMPI.B	#$03,$FE11
  DEF_ROMLOC(19B0) : if (!CCR_EQ) goto rom_19B8;     // BNE.B	$19B8
  DEF_ROMLOC(19B2) : move_toreg_32(0x1BE2, &A0);     // LEA.L	$00001BE2,A0
  DEF_ROMLOC(19B8) : move_toreg_32(0xFFFFFB56, &A1); // LEA.L	$FB56,A1
  DEF_ROMLOC(19BC)
      : move_tomem_32(read_32((s32)A0 + (s8)0x0 + (s16)D0),
                      (A1 += 4, A1 - 4)); // MOVE.L	0(A0,D0),(A1)+
  DEF_ROMLOC(19C0)
      : move_tomem_32(read_32((s32)A0 + (s8)0x4 + (s16)D0),
                      A1);                           // MOVE.L	4(A0,D0),(A1)
  DEF_ROMLOC(19C4) : move_toreg_32(0xFFFFFAD6, &A1); // LEA.L	$FAD6,A1
  DEF_ROMLOC(19C8)
      : move_tomem_32(read_32((s32)A0 + (s8)0x0 + (s16)D0),
                      (A1 += 4, A1 - 4)); // MOVE.L	0(A0,D0),(A1)+
  DEF_ROMLOC(19CC)
      : move_tomem_32(read_32((s32)A0 + (s8)0x4 + (s16)D0),
                      A1); // MOVE.L	4(A0,D0),(A1)
  DEF_ROMLOC(19D0)
      : move_toreg_16(read_16(0xFFFFFE04), &D0); // MOVE.W	$FE04,D0
  DEF_ROMLOC(19D4) : and_toreg_16(0x7, &D0);     // ANDI.W	#$0007,D0
  DEF_ROMLOC(19D8)
      : move_toreg_8(read_8(0x1A34 + (s16)(D0 & 0xffff)),
                     &D0);                      // MOVE.B	90(PC,D0),D0
  DEF_ROMLOC(19DC) : if (CCR_EQ) goto rom_1A32; // BEQ.B	$1A32
  DEF_ROMLOC(19DE) : move_toreg_32(0x1, &D1);   // MOVEQ.L	$01,D1
  DEF_ROMLOC(19E0) : tst_mem_8(0xFFFFF7C0);     // TST.B	$F7C0
  DEF_ROMLOC(19E4) : if (CCR_EQ) goto rom_19E8; // BEQ.B	$19E8
  DEF_ROMLOC(19E6) : neg_reg_16(&D1);           // NEG.W	D1
  DEF_ROMLOC(19E8)
      : move_toreg_16(read_16(0xFFFFF650), &D0);     // MOVE.W	$F650,D0
  DEF_ROMLOC(19EC) : and_toreg_16(0x3, &D0);         // ANDI.W	#$0003,D0
  DEF_ROMLOC(19F0) : add_toreg_16(D1, &D0);          // ADD.W	D1,D0
  DEF_ROMLOC(19F2) : cmp_toreg_16(0x3, &D0);         // CMPI.W	#$0003,D0
  DEF_ROMLOC(19F6) : if (CCR_CS) goto rom_1A02;      // BCS.B	$1A02
  DEF_ROMLOC(19F8) : move_toreg_16(D0, &D1);         // MOVE.W	D0,D1
  DEF_ROMLOC(19FA) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(19FC) : tst_reg_16(&D1);                // TST.W	D1
  DEF_ROMLOC(19FE) : if (CCR_PL) goto rom_1A02;      // BPL.B	$1A02
  DEF_ROMLOC(1A00) : move_toreg_32(0x2, &D0);        // MOVEQ.L	$02,D0
  DEF_ROMLOC(1A02) : move_tomem_16(D0, 0xFFFFF650);  // MOVE.W	D0,$F650
  DEF_ROMLOC(1A06) : add_toreg_16(D0, &D0);          // ADD.W	D0,D0
  DEF_ROMLOC(1A08) : move_toreg_16(D0, &D1);         // MOVE.W	D0,D1
  DEF_ROMLOC(1A0A) : add_toreg_16(D0, &D0);          // ADD.W	D0,D0
  DEF_ROMLOC(1A0C) : add_toreg_16(D1, &D0);          // ADD.W	D1,D0
  DEF_ROMLOC(1A0E) : move_toreg_32(0x1BBE, &A0);     // LEA.L	$00001BBE,A0
  DEF_ROMLOC(1A14) : move_toreg_32(0xFFFFFB76, &A1); // LEA.L	$FB76,A1
  DEF_ROMLOC(1A18)
      : move_tomem_32(read_32((s32)A0 + (s8)0x0 + (s16)D0),
                      (A1 += 4, A1 - 4)); // MOVE.L	0(A0,D0),(A1)+
  DEF_ROMLOC(1A1C)
      : move_tomem_16(read_16((s32)A0 + (s8)0x4 + (s16)D0),
                      A1);                           // MOVE.W	4(A0,D0),(A1)
  DEF_ROMLOC(1A20) : move_toreg_32(0x1BD0, &A0);     // LEA.L	$00001BD0,A0
  DEF_ROMLOC(1A26) : move_toreg_32(0xFFFFFAF6, &A1); // LEA.L	$FAF6,A1
  DEF_ROMLOC(1A2A)
      : move_tomem_32(read_32((s32)A0 + (s8)0x0 + (s16)D0),
                      (A1 += 4, A1 - 4)); // MOVE.L	0(A0,D0),(A1)+
  DEF_ROMLOC(1A2E)
      : move_tomem_16(read_16((s32)A0 + (s8)0x4 + (s16)D0),
                      A1);   // MOVE.W	4(A0,D0),(A1)
  DEF_ROMLOC(1A32) : return; // RTS
}
void level_palette_cycle_mz(void) {
  DEF_ROMLOC(1A3C) : return; // RTS
}
void level_palette_cycle_slz(void) {
  DEF_ROMLOC(1A3E) : sub_tomem_16(0x1, 0xFFFFF634);  // SUBQ.W	#$01,$F634
  DEF_ROMLOC(1A42) : if (CCR_PL) goto rom_1A78;      // BPL.B	$1A78
  DEF_ROMLOC(1A44) : move_tomem_16(0x7, 0xFFFFF634); // MOVE.W	#$0007,$F634
  DEF_ROMLOC(1A4A)
      : move_toreg_16(read_16(0xFFFFF632), &D0);     // MOVE.W	$F632,D0
  DEF_ROMLOC(1A4E) : add_toreg_16(0x1, &D0);         // ADDQ.W	#$01,D0
  DEF_ROMLOC(1A50) : cmp_toreg_16(0x6, &D0);         // CMPI.W	#$0006,D0
  DEF_ROMLOC(1A54) : if (CCR_CS) goto rom_1A58;      // BCS.B	$1A58
  DEF_ROMLOC(1A56) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(1A58) : move_tomem_16(D0, 0xFFFFF632);  // MOVE.W	D0,$F632
  DEF_ROMLOC(1A5C) : move_toreg_16(D0, &D1);         // MOVE.W	D0,D1
  DEF_ROMLOC(1A5E) : add_toreg_16(D1, &D1);          // ADD.W	D1,D1
  DEF_ROMLOC(1A60) : add_toreg_16(D1, &D0);          // ADD.W	D1,D0
  DEF_ROMLOC(1A62) : add_toreg_16(D0, &D0);          // ADD.W	D0,D0
  DEF_ROMLOC(1A64) : move_toreg_32(0x1C4A, &A0);     // LEA.L	$00001C4A,A0
  DEF_ROMLOC(1A6A) : move_toreg_32(0xFFFFFB56, &A1); // LEA.L	$FB56,A1
  DEF_ROMLOC(1A6E)
      : move_tomem_16(read_16((s32)A0 + (s8)0x0 + (s16)D0),
                      A1); // MOVE.W	0(A0,D0),(A1)
  DEF_ROMLOC(1A72)
      : move_tomem_32(read_32((s32)A0 + (s8)0x2 + (s16)D0),
                      A1 + 0x4); // MOVE.L	2(A0,D0),4(A1)
  DEF_ROMLOC(1A78) : return;     // RTS
}
void level_palette_cycle_syz(void) {
  DEF_ROMLOC(1A7A) : sub_tomem_16(0x1, 0xFFFFF634);  // SUBQ.W	#$01,$F634
  DEF_ROMLOC(1A7E) : if (CCR_PL) goto rom_1ABE;      // BPL.B	$1ABE
  DEF_ROMLOC(1A80) : move_tomem_16(0x5, 0xFFFFF634); // MOVE.W	#$0005,$F634
  DEF_ROMLOC(1A86)
      : move_toreg_16(read_16(0xFFFFF632), &D0);     // MOVE.W	$F632,D0
  DEF_ROMLOC(1A8A) : add_tomem_16(0x1, 0xFFFFF632);  // ADDQ.W	#$01,$F632
  DEF_ROMLOC(1A8E) : and_toreg_16(0x3, &D0);         // ANDI.W	#$0003,D0
  DEF_ROMLOC(1A92) : lsl_toreg_16(0x2, &D0);         // LSL.W	#$02,D0
  DEF_ROMLOC(1A94) : move_toreg_16(D0, &D1);         // MOVE.W	D0,D1
  DEF_ROMLOC(1A96) : add_toreg_16(D0, &D0);          // ADD.W	D0,D0
  DEF_ROMLOC(1A98) : move_toreg_32(0x1C6E, &A0);     // LEA.L	$00001C6E,A0
  DEF_ROMLOC(1A9E) : move_toreg_32(0xFFFFFB6E, &A1); // LEA.L	$FB6E,A1
  DEF_ROMLOC(1AA2)
      : move_tomem_32(read_32((s32)A0 + (s8)0x0 + (s16)D0),
                      (A1 += 4, A1 - 4)); // MOVE.L	0(A0,D0),(A1)+
  DEF_ROMLOC(1AA6)
      : move_tomem_32(read_32((s32)A0 + (s8)0x4 + (s16)D0),
                      A1);                           // MOVE.L	4(A0,D0),(A1)
  DEF_ROMLOC(1AAA) : move_toreg_32(0x1C8E, &A0);     // LEA.L	$00001C8E,A0
  DEF_ROMLOC(1AB0) : move_toreg_32(0xFFFFFB76, &A1); // LEA.L	$FB76,A1
  DEF_ROMLOC(1AB4)
      : move_tomem_16(read_16((s32)A0 + (s8)0x0 + (s16)D1),
                      A1); // MOVE.W	0(A0,D1),(A1)
  DEF_ROMLOC(1AB8)
      : move_tomem_16(read_16((s32)A0 + (s8)0x2 + (s16)D1),
                      A1 + 0x4); // MOVE.W	2(A0,D1),4(A1)
  DEF_ROMLOC(1ABE) : return;     // RTS
}
void level_palette_cycle_sbz(void) {
  DEF_ROMLOC(1AC0) : move_toreg_32(0x1C9E, &A2);     // LEA.L	$00001C9E,A2
  DEF_ROMLOC(1AC6) : tst_mem_8(0xFFFFFE11);          // TST.B	$FE11
  DEF_ROMLOC(1ACA) : if (CCR_EQ) goto rom_1AD2;      // BEQ.B	$1AD2
  DEF_ROMLOC(1ACC) : move_toreg_32(0x1CD6, &A2);     // LEA.L	$00001CD6,A2
  DEF_ROMLOC(1AD2) : move_toreg_32(0xFFFFF650, &A1); // LEA.L	$F650,A1
  DEF_ROMLOC(1AD6)
      : move_toreg_16(read_16((A2 += 2, A2 - 2)), &D1); // MOVE.W	(A2)+,D1
  DEF_ROMLOC(1AD8) : sub_tomem_8(0x1, A1);              // SUBQ.B	#$01,(A1)
  DEF_ROMLOC(1ADA) : if (CCR_MI) goto rom_1AE2;         // BMI.B	$1AE2
  DEF_ROMLOC(1ADC) : add_toreg_32(0x2, &A1);            // ADDQ.L	#$02,A1
  DEF_ROMLOC(1ADE) : add_toreg_32(0x6, &A2);            // ADDQ.L	#$06,A2
  goto rom_1AFE;                                        // BRA.B	$1AFE
  DEF_ROMLOC(1AE2) : move_tomem_8(read_8(A2++), A1++);  // MOVE.B
                                                        // (A2)+,(A1)+
  DEF_ROMLOC(1AE4) : move_toreg_8(read_8(A1), &D0);     // MOVE.B	(A1),D0
  DEF_ROMLOC(1AE6) : add_toreg_8(0x1, &D0);             // ADDQ.B	#$01,D0
  DEF_ROMLOC(1AE8) : cmp_toreg_8(read_8(A2++), &D0);    // CMP.B	(A2)+,D0
  DEF_ROMLOC(1AEA) : if (CCR_CS) goto rom_1AEE;         // BCS.B	$1AEE
  DEF_ROMLOC(1AEC) : move_toreg_32(0x0, &D0);           // MOVEQ.L	$00,D0
  DEF_ROMLOC(1AEE) : move_tomem_8(D0, A1++);            // MOVE.B	D0,(A1)+
  DEF_ROMLOC(1AF0) : and_toreg_16(0xF, &D0);            // ANDI.W	#$000F,D0
  DEF_ROMLOC(1AF4) : add_toreg_16(D0, &D0);             // ADD.W	D0,D0
  DEF_ROMLOC(1AF6)
      : move_toreg_16(read_16((A2 += 2, A2 - 2)), &A0); // MOVEA.W	(A2)+,A0
  DEF_ROMLOC(1AF8)
      : move_toreg_16(read_16((A2 += 2, A2 - 2)), &A3); // MOVEA.W	(A2)+,A3
  DEF_ROMLOC(1AFA)
      : move_tomem_16(read_16((s32)A0 + (s8)0x0 + (s16)D0),
                      A3); // MOVE.W	0(A0,D0),(A3)
  DEF_ROMLOC(1AFE) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_1AD8;                                   // DBF.W	D1,$1AD8
  DEF_ROMLOC(1B02) : sub_tomem_16(0x1, 0xFFFFF634);  // SUBQ.W	#$01,$F634
  DEF_ROMLOC(1B06) : if (CCR_PL) goto rom_1B5C;      // BPL.B	$1B5C
  DEF_ROMLOC(1B08) : move_toreg_32(0x1D32, &A0);     // LEA.L	$00001D32,A0
  DEF_ROMLOC(1B0E) : move_tomem_16(0x1, 0xFFFFF634); // MOVE.W	#$0001,$F634
  DEF_ROMLOC(1B14) : tst_mem_8(0xFFFFFE11);          // TST.B	$FE11
  DEF_ROMLOC(1B18) : if (CCR_EQ) goto rom_1B26;      // BEQ.B	$1B26
  DEF_ROMLOC(1B1A) : move_toreg_32(0x1D98, &A0);     // LEA.L	$00001D98,A0
  DEF_ROMLOC(1B20) : move_tomem_16(0x0, 0xFFFFF634); // MOVE.W	#$0000,$F634
  DEF_ROMLOC(1B26) : move_toreg_32(0xFFFFFFFF, &D1); // MOVEQ.L	$FF,D1
  DEF_ROMLOC(1B28) : tst_mem_8(0xFFFFF7C0);          // TST.B	$F7C0
  DEF_ROMLOC(1B2C) : if (CCR_EQ) goto rom_1B30;      // BEQ.B	$1B30
  DEF_ROMLOC(1B2E) : neg_reg_16(&D1);                // NEG.W	D1
  DEF_ROMLOC(1B30)
      : move_toreg_16(read_16(0xFFFFF632), &D0);     // MOVE.W	$F632,D0
  DEF_ROMLOC(1B34) : and_toreg_16(0x3, &D0);         // ANDI.W	#$0003,D0
  DEF_ROMLOC(1B38) : add_toreg_16(D1, &D0);          // ADD.W	D1,D0
  DEF_ROMLOC(1B3A) : cmp_toreg_16(0x3, &D0);         // CMPI.W	#$0003,D0
  DEF_ROMLOC(1B3E) : if (CCR_CS) goto rom_1B4A;      // BCS.B	$1B4A
  DEF_ROMLOC(1B40) : move_toreg_16(D0, &D1);         // MOVE.W	D0,D1
  DEF_ROMLOC(1B42) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(1B44) : tst_reg_16(&D1);                // TST.W	D1
  DEF_ROMLOC(1B46) : if (CCR_PL) goto rom_1B4A;      // BPL.B	$1B4A
  DEF_ROMLOC(1B48) : move_toreg_32(0x2, &D0);        // MOVEQ.L	$02,D0
  DEF_ROMLOC(1B4A) : move_tomem_16(D0, 0xFFFFF632);  // MOVE.W	D0,$F632
  DEF_ROMLOC(1B4E) : add_toreg_16(D0, &D0);          // ADD.W	D0,D0
  DEF_ROMLOC(1B50) : move_toreg_32(0xFFFFFB58, &A1); // LEA.L	$FB58,A1
  DEF_ROMLOC(1B54)
      : move_tomem_32(read_32((s32)A0 + (s8)0x0 + (s16)D0),
                      (A1 += 4, A1 - 4)); // MOVE.L	0(A0,D0),(A1)+
  DEF_ROMLOC(1B58)
      : move_tomem_16(read_16((s32)A0 + (s8)0x4 + (s16)D0),
                      A1);   // MOVE.W	4(A0,D0),(A1)
  DEF_ROMLOC(1B5C) : return; // RTS
}
void palette_fade_in(bool full_palette) {
  if (full_palette) {
  	DEF_ROMLOC(1DA4) : move_tomem_16(0x3F, 0xFFFFF626); // MOVE.W	#$003F,$F626
  }
  game_state_palette = game_state;
  DEF_ROMLOC(1DAA) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(1DAC) : move_toreg_32(0xFFFFFB00, &A0); // LEA.L	$FB00,A0
  DEF_ROMLOC(1DB0)
      : move_toreg_8(read_8(0xFFFFF626), &D0); // MOVE.B	$F626,D0
  DEF_ROMLOC(1DB4) : add_toreg_16(D0, &A0);    // ADDA.W	D0,A0
  DEF_ROMLOC(1DB6) : move_toreg_32(0x0, &D1);  // MOVEQ.L	$00,D1
  DEF_ROMLOC(1DB8)
      : move_toreg_8(read_8(0xFFFFF627), &D0); // MOVE.B	$F627,D0
  DEF_ROMLOC(1DBC)
      : move_tomem_16(D1, (A0 += 2, A0 - 2)); // MOVE.W	D1,(A0)+
  DEF_ROMLOC(1DBE) : dec_reg_16(&D0);
  if ((D0 & 0xffff) != 0xffff)
    goto rom_1DBC;                             // DBF.W	D0,$1DBC
  DEF_ROMLOC(1DC2) : move_toreg_16(0x15, &D4); // MOVE.W	#$0015,D4
  palette_fade_in_runvblank();
}
void palette_fade_in_runvblank(void) {
  DEF_ROMLOC(1DC6) : move_tomem_8(0x12, 0xFFFFF62A); // MOVE.B	#$12,$F62A
  DEF_ROMLOC(1DCC) : rom_29A0();                     // BSR.W	$29A0
  game_state = palette_fade_in_loop;
}
void palette_fade_in_loop(void) {
  DEF_ROMLOC(1DD0) : palette_move_from_black(); // BSR.B	$1DDC
  DEF_ROMLOC(1DD2) : rom_15E4(); // BSR.W	$15E4
  DEF_ROMLOC(1DD6) : dec_reg_16(&D4);
  if ((D4 & 0xffff) != 0xffff) {
    palette_fade_in_runvblank();
    return;
  } // DBF.W	D4,$1DC6
  game_state = game_state_palette;
  game_state_palette = NULL;
  DEF_ROMLOC(1DDA) : if (game_state) {
	game_state();
  } return; // RTS
}
void palette_move_from_black(void) {
  DEF_ROMLOC(1DDC) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(1DDE) : move_toreg_32(0xFFFFFB00, &A0); // LEA.L	$FB00,A0
  DEF_ROMLOC(1DE2) : move_toreg_32(0xFFFFFB80, &A1); // LEA.L	$FB80,A1
  DEF_ROMLOC(1DE6)
      : move_toreg_8(read_8(0xFFFFF626), &D0); // MOVE.B	$F626,D0
  DEF_ROMLOC(1DEA) : add_toreg_16(D0, &A0);    // ADDA.W	D0,A0
  DEF_ROMLOC(1DEC) : add_toreg_16(D0, &A1);    // ADDA.W	D0,A1
  DEF_ROMLOC(1DEE)
      : move_toreg_8(read_8(0xFFFFF627), &D0); // MOVE.B	$F627,D0
  DEF_ROMLOC(1DF2) : color_move_from_black();               // BSR.B	$1E1E
  DEF_ROMLOC(1DF4) : dec_reg_16(&D0);
  if ((D0 & 0xffff) != 0xffff)
    goto rom_1DF2;                                   // DBF.W	D0,$1DF2
  DEF_ROMLOC(1DF8) : cmp_tomem_8(0x1, 0xFFFFFE10);   // CMPI.B	#$01,$FE10
  DEF_ROMLOC(1DFE) : if (!CCR_EQ) goto rom_1E1C;     // BNE.B	$1E1C
  DEF_ROMLOC(1E00) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(1E02) : move_toreg_32(0xFFFFFA80, &A0); // LEA.L	$FA80,A0
  DEF_ROMLOC(1E06) : move_toreg_32(0xFFFFFA00, &A1); // LEA.L	$FA00,A1
  DEF_ROMLOC(1E0A)
      : move_toreg_8(read_8(0xFFFFF626), &D0); // MOVE.B	$F626,D0
  DEF_ROMLOC(1E0E) : add_toreg_16(D0, &A0);    // ADDA.W	D0,A0
  DEF_ROMLOC(1E10) : add_toreg_16(D0, &A1);    // ADDA.W	D0,A1
  DEF_ROMLOC(1E12)
      : move_toreg_8(read_8(0xFFFFF627), &D0); // MOVE.B	$F627,D0
  DEF_ROMLOC(1E16) : color_move_from_black();               // BSR.B	$1E1E
  DEF_ROMLOC(1E18) : dec_reg_16(&D0);
  if ((D0 & 0xffff) != 0xffff)
    goto rom_1E16;           // DBF.W	D0,$1E16
  DEF_ROMLOC(1E1C) : return; // RTS
}
void color_move_from_black(void) {
  DEF_ROMLOC(1E1E)
      : move_toreg_16(read_16((A1 += 2, A1 - 2)), &D2); // MOVE.W	(A1)+,D2
  DEF_ROMLOC(1E20) : move_toreg_16(read_16(A0), &D3);   // MOVE.W	(A0),D3
  DEF_ROMLOC(1E22) : cmp_toreg_16(D2, &D3);             // CMP.W	D2,D3
  DEF_ROMLOC(1E24) : if (CCR_EQ) goto rom_1E46;         // BEQ.B	$1E46
  DEF_ROMLOC(1E26) : move_toreg_16(D3, &D1);            // MOVE.W	D3,D1
  DEF_ROMLOC(1E28) : add_toreg_16(0x200, &D1);          // ADDI.W	#$0200,D1
  DEF_ROMLOC(1E2C) : cmp_toreg_16(D2, &D1);             // CMP.W	D2,D1
  DEF_ROMLOC(1E2E) : if (CCR_HI) goto rom_1E34;         // BHI.B	$1E34
  DEF_ROMLOC(1E30)
      : move_tomem_16(D1, (A0 += 2, A0 - 2));   // MOVE.W	D1,(A0)+
  DEF_ROMLOC(1E32) : return;                    // RTS
  DEF_ROMLOC(1E34) : move_toreg_16(D3, &D1);    // MOVE.W	D3,D1
  DEF_ROMLOC(1E36) : add_toreg_16(0x20, &D1);   // ADDI.W	#$0020,D1
  DEF_ROMLOC(1E3A) : cmp_toreg_16(D2, &D1);     // CMP.W	D2,D1
  DEF_ROMLOC(1E3C) : if (CCR_HI) goto rom_1E42; // BHI.B	$1E42
  DEF_ROMLOC(1E3E)
      : move_tomem_16(D1, (A0 += 2, A0 - 2)); // MOVE.W	D1,(A0)+
  DEF_ROMLOC(1E40) : return;                  // RTS
  DEF_ROMLOC(1E42)
      : add_tomem_16(0x2, (A0 += 2, A0 - 2)); // ADDQ.W	#$02,(A0)+
  DEF_ROMLOC(1E44) : return;                  // RTS
  DEF_ROMLOC(1E46) : add_toreg_16(0x2, &A0);  // ADDQ.W	#$02,A0
  DEF_ROMLOC(1E48) : return;                  // RTS
}
void palette_fade_out(void) {
  game_state_palette = game_state;
  DEF_ROMLOC(1E4A) : move_tomem_16(0x3F, 0xFFFFF626); // MOVE.W	#$003F,$F626
  DEF_ROMLOC(1E50) : move_toreg_16(0x15, &D4);        // MOVE.W	#$0015,D4
  palette_fade_out_runvblank();
  game_state = palette_fade_out_loop;
}
void palette_fade_out_runvblank(void) {
  DEF_ROMLOC(1E54) : move_tomem_8(0x12, 0xFFFFF62A); // MOVE.B	#$12,$F62A
  DEF_ROMLOC(1E5A) : rom_29A0();                     // BSR.W	$29A0
}
void palette_fade_out_loop(void) {
  DEF_ROMLOC(1E5E) : palette_move_toward_black(); // BSR.B	$1E6A
  DEF_ROMLOC(1E60) : rom_15E4(); // BSR.W	$15E4
  DEF_ROMLOC(1E64) : dec_reg_16(&D4);
  if ((D4 & 0xffff) != 0xffff) {
    palette_fade_out_runvblank();
    return;
  } // DBF.W	D4,$1E54
  game_state = game_state_palette;
  game_state_palette = NULL;
  DEF_ROMLOC(1E68) : if (game_state) {
	game_state();
  } return; // RTS
}
void palette_move_toward_black(void) {
  DEF_ROMLOC(1E6A) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(1E6C) : move_toreg_32(0xFFFFFB00, &A0); // LEA.L	$FB00,A0
  DEF_ROMLOC(1E70)
      : move_toreg_8(read_8(0xFFFFF626), &D0); // MOVE.B	$F626,D0
  DEF_ROMLOC(1E74) : add_toreg_16(D0, &A0);    // ADDA.W	D0,A0
  DEF_ROMLOC(1E76)
      : move_toreg_8(read_8(0xFFFFF627), &D0); // MOVE.B	$F627,D0
  DEF_ROMLOC(1E7A) : color_move_toward_black();               // BSR.B	$1E98
  DEF_ROMLOC(1E7C) : dec_reg_16(&D0);
  if ((D0 & 0xffff) != 0xffff)
    goto rom_1E7A;                                   // DBF.W	D0,$1E7A
  DEF_ROMLOC(1E80) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(1E82) : move_toreg_32(0xFFFFFA80, &A0); // LEA.L	$FA80,A0
  DEF_ROMLOC(1E86)
      : move_toreg_8(read_8(0xFFFFF626), &D0); // MOVE.B	$F626,D0
  DEF_ROMLOC(1E8A) : add_toreg_16(D0, &A0);    // ADDA.W	D0,A0
  DEF_ROMLOC(1E8C)
      : move_toreg_8(read_8(0xFFFFF627), &D0); // MOVE.B	$F627,D0
  DEF_ROMLOC(1E90) : color_move_toward_black();               // BSR.B	$1E98
  DEF_ROMLOC(1E92) : dec_reg_16(&D0);
  if ((D0 & 0xffff) != 0xffff)
    goto rom_1E90;           // DBF.W	D0,$1E90
  DEF_ROMLOC(1E96) : return; // RTS
}
void color_move_toward_black(void) {
  DEF_ROMLOC(1E98) : move_toreg_16(read_16(A0), &D2); // MOVE.W	(A0),D2
  DEF_ROMLOC(1E9A) : if (CCR_EQ) goto rom_1EC4;       // BEQ.B	$1EC4
  DEF_ROMLOC(1E9C) : move_toreg_16(D2, &D1);          // MOVE.W	D2,D1
  DEF_ROMLOC(1E9E) : and_toreg_16(0xE, &D1);          // ANDI.W	#$000E,D1
  DEF_ROMLOC(1EA2) : if (CCR_EQ) goto rom_1EA8;       // BEQ.B	$1EA8
  DEF_ROMLOC(1EA4)
      : sub_tomem_16(0x2, (A0 += 2, A0 - 2));   // SUBQ.W	#$02,(A0)+
  DEF_ROMLOC(1EA6) : return;                    // RTS
  DEF_ROMLOC(1EA8) : move_toreg_16(D2, &D1);    // MOVE.W	D2,D1
  DEF_ROMLOC(1EAA) : and_toreg_16(0xE0, &D1);   // ANDI.W	#$00E0,D1
  DEF_ROMLOC(1EAE) : if (CCR_EQ) goto rom_1EB6; // BEQ.B	$1EB6
  DEF_ROMLOC(1EB0)
      : sub_tomem_16(0x20, (A0 += 2, A0 - 2));  // SUBI.W	#$0020,(A0)+
  DEF_ROMLOC(1EB4) : return;                    // RTS
  DEF_ROMLOC(1EB6) : move_toreg_16(D2, &D1);    // MOVE.W	D2,D1
  DEF_ROMLOC(1EB8) : and_toreg_16(0xE00, &D1);  // ANDI.W	#$0E00,D1
  DEF_ROMLOC(1EBC) : if (CCR_EQ) goto rom_1EC4; // BEQ.B	$1EC4
  DEF_ROMLOC(1EBE)
      : sub_tomem_16(0x200, (A0 += 2, A0 - 2)); // SUBI.W	#$0200,(A0)+
  DEF_ROMLOC(1EC2) : return;                    // RTS
  DEF_ROMLOC(1EC4) : add_toreg_16(0x2, &A0);    // ADDQ.W	#$02,A0
  DEF_ROMLOC(1EC6) : return;                    // RTS
}
void palette_fade_from_white(void) {
  game_state_palette = game_state;
  DEF_ROMLOC(1EC8) : move_tomem_16(0x3F, 0xFFFFF626); // MOVE.W	#$003F,$F626
  DEF_ROMLOC(1ECE) : move_toreg_32(0x0, &D0);         // MOVEQ.L	$00,D0
  DEF_ROMLOC(1ED0) : move_toreg_32(0xFFFFFB00, &A0);  // LEA.L	$FB00,A0
  DEF_ROMLOC(1ED4)
      : move_toreg_8(read_8(0xFFFFF626), &D0);  // MOVE.B	$F626,D0
  DEF_ROMLOC(1ED8) : add_toreg_16(D0, &A0);     // ADDA.W	D0,A0
  DEF_ROMLOC(1EDA) : move_toreg_16(0xEEE, &D1); // MOVE.W	#$0EEE,D1
  DEF_ROMLOC(1EDE)
      : move_toreg_8(read_8(0xFFFFF627), &D0); // MOVE.B	$F627,D0
  DEF_ROMLOC(1EE2)
      : move_tomem_16(D1, (A0 += 2, A0 - 2)); // MOVE.W	D1,(A0)+
  DEF_ROMLOC(1EE4) : dec_reg_16(&D0);
  if ((D0 & 0xffff) != 0xffff)
    goto rom_1EE2;                             // DBF.W	D0,$1EE2
  DEF_ROMLOC(1EE8) : move_toreg_16(0x15, &D4); // MOVE.W	#$0015,D4
  palette_fade_from_white_runvblank();
}
void palette_fade_from_white_runvblank(void) {
  DEF_ROMLOC(1EEC) : move_tomem_8(0x12, 0xFFFFF62A); // MOVE.B	#$12,$F62A
  DEF_ROMLOC(1EF2) : rom_29A0();                     // BSR.W	$29A0
  game_state = palette_fade_from_white_loop;
}
void palette_fade_from_white_loop(void) {
  DEF_ROMLOC(1EF6) : palette_move_from_white(); // BSR.B	$1F02
  DEF_ROMLOC(1EF8) : rom_15E4(); // BSR.W	$15E4
  DEF_ROMLOC(1EFC) : dec_reg_16(&D4);
  if ((D4 & 0xffff) != 0xffff) {
    palette_fade_from_white_runvblank();
    return;
  } // DBF.W	D4,$1EEC
  game_state = game_state_palette;
  game_state_palette = NULL;
  DEF_ROMLOC(1F00) : if (game_state) {
	game_state();
  } return; // RTS
}
void palette_move_from_white(void) {
  DEF_ROMLOC(1F02) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(1F04) : move_toreg_32(0xFFFFFB00, &A0); // LEA.L	$FB00,A0
  DEF_ROMLOC(1F08) : move_toreg_32(0xFFFFFB80, &A1); // LEA.L	$FB80,A1
  DEF_ROMLOC(1F0C)
      : move_toreg_8(read_8(0xFFFFF626), &D0); // MOVE.B	$F626,D0
  DEF_ROMLOC(1F10) : add_toreg_16(D0, &A0);    // ADDA.W	D0,A0
  DEF_ROMLOC(1F12) : add_toreg_16(D0, &A1);    // ADDA.W	D0,A1
  DEF_ROMLOC(1F14)
      : move_toreg_8(read_8(0xFFFFF627), &D0); // MOVE.B	$F627,D0
  DEF_ROMLOC(1F18) : color_move_from_white();               // BSR.B	$1F44
  DEF_ROMLOC(1F1A) : dec_reg_16(&D0);
  if ((D0 & 0xffff) != 0xffff)
    goto rom_1F18;                                   // DBF.W	D0,$1F18
  DEF_ROMLOC(1F1E) : cmp_tomem_8(0x1, 0xFFFFFE10);   // CMPI.B	#$01,$FE10
  DEF_ROMLOC(1F24) : if (!CCR_EQ) goto rom_1F42;     // BNE.B	$1F42
  DEF_ROMLOC(1F26) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(1F28) : move_toreg_32(0xFFFFFA80, &A0); // LEA.L	$FA80,A0
  DEF_ROMLOC(1F2C) : move_toreg_32(0xFFFFFA00, &A1); // LEA.L	$FA00,A1
  DEF_ROMLOC(1F30)
      : move_toreg_8(read_8(0xFFFFF626), &D0); // MOVE.B	$F626,D0
  DEF_ROMLOC(1F34) : add_toreg_16(D0, &A0);    // ADDA.W	D0,A0
  DEF_ROMLOC(1F36) : add_toreg_16(D0, &A1);    // ADDA.W	D0,A1
  DEF_ROMLOC(1F38)
      : move_toreg_8(read_8(0xFFFFF627), &D0); // MOVE.B	$F627,D0
  DEF_ROMLOC(1F3C) : color_move_from_white();               // BSR.B	$1F44
  DEF_ROMLOC(1F3E) : dec_reg_16(&D0);
  if ((D0 & 0xffff) != 0xffff)
    goto rom_1F3C;           // DBF.W	D0,$1F3C
  DEF_ROMLOC(1F42) : return; // RTS
}
void color_move_from_white(void) {
  DEF_ROMLOC(1F44)
      : move_toreg_16(read_16((A1 += 2, A1 - 2)), &D2); // MOVE.W	(A1)+,D2
  DEF_ROMLOC(1F46) : move_toreg_16(read_16(A0), &D3);   // MOVE.W	(A0),D3
  DEF_ROMLOC(1F48) : cmp_toreg_16(D2, &D3);             // CMP.W	D2,D3
  DEF_ROMLOC(1F4A) : if (CCR_EQ) goto rom_1F70;         // BEQ.B	$1F70
  DEF_ROMLOC(1F4C) : move_toreg_16(D3, &D1);            // MOVE.W	D3,D1
  DEF_ROMLOC(1F4E) : sub_toreg_16(0x200, &D1);          // SUBI.W	#$0200,D1
  DEF_ROMLOC(1F52) : if (CCR_CS) goto rom_1F5C;         // BCS.B	$1F5C
  DEF_ROMLOC(1F54) : cmp_toreg_16(D2, &D1);             // CMP.W	D2,D1
  DEF_ROMLOC(1F56) : if (CCR_CS) goto rom_1F5C;         // BCS.B	$1F5C
  DEF_ROMLOC(1F58)
      : move_tomem_16(D1, (A0 += 2, A0 - 2));   // MOVE.W	D1,(A0)+
  DEF_ROMLOC(1F5A) : return;                    // RTS
  DEF_ROMLOC(1F5C) : move_toreg_16(D3, &D1);    // MOVE.W	D3,D1
  DEF_ROMLOC(1F5E) : sub_toreg_16(0x20, &D1);   // SUBI.W	#$0020,D1
  DEF_ROMLOC(1F62) : if (CCR_CS) goto rom_1F6C; // BCS.B	$1F6C
  DEF_ROMLOC(1F64) : cmp_toreg_16(D2, &D1);     // CMP.W	D2,D1
  DEF_ROMLOC(1F66) : if (CCR_CS) goto rom_1F6C; // BCS.B	$1F6C
  DEF_ROMLOC(1F68)
      : move_tomem_16(D1, (A0 += 2, A0 - 2)); // MOVE.W	D1,(A0)+
  DEF_ROMLOC(1F6A) : return;                  // RTS
  DEF_ROMLOC(1F6C)
      : sub_tomem_16(0x2, (A0 += 2, A0 - 2)); // SUBQ.W	#$02,(A0)+
  DEF_ROMLOC(1F6E) : return;                  // RTS
  DEF_ROMLOC(1F70) : add_toreg_16(0x2, &A0);  // ADDQ.W	#$02,A0
  DEF_ROMLOC(1F72) : return;                  // RTS
}
void palette_fade_to_white(void) {
  game_state_palette = game_state;
  DEF_ROMLOC(1F74) : move_tomem_16(0x3F, 0xFFFFF626); // MOVE.W	#$003F,$F626
  DEF_ROMLOC(1F7A) : move_toreg_16(0x15, &D4);        // MOVE.W	#$0015,D4
  palette_fade_to_white_runvblank();
}
void palette_fade_to_white_runvblank(void) {
  DEF_ROMLOC(1F7E) : move_tomem_8(0x12, 0xFFFFF62A); // MOVE.B	#$12,$F62A
  DEF_ROMLOC(1F84) : rom_29A0();                     // BSR.W	$29A0
  game_state = palette_fade_to_white_loop;
}
void palette_fade_to_white_loop(void) {
  DEF_ROMLOC(1F88) : palette_move_towards_white(); // BSR.B	$1F94
  DEF_ROMLOC(1F8A) : rom_15E4(); // BSR.W	$15E4
  DEF_ROMLOC(1F8E) : dec_reg_16(&D4);
  if ((D4 & 0xffff) != 0xffff) {
    palette_fade_to_white_runvblank();
    return;
  } // DBF.W	D4,$1F7E
  game_state = game_state_palette;
  game_state_palette = NULL;
  DEF_ROMLOC(1F92) : if (game_state) {
	game_state();
  } return; // RTS
}
void palette_move_towards_white(void) {
  DEF_ROMLOC(1F94) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(1F96) : move_toreg_32(0xFFFFFB00, &A0); // LEA.L	$FB00,A0
  DEF_ROMLOC(1F9A)
      : move_toreg_8(read_8(0xFFFFF626), &D0); // MOVE.B	$F626,D0
  DEF_ROMLOC(1F9E) : add_toreg_16(D0, &A0);    // ADDA.W	D0,A0
  DEF_ROMLOC(1FA0)
      : move_toreg_8(read_8(0xFFFFF627), &D0); // MOVE.B	$F627,D0
  DEF_ROMLOC(1FA4) : color_move_towards_white();               // BSR.B	$1FC2
  DEF_ROMLOC(1FA6) : dec_reg_16(&D0);
  if ((D0 & 0xffff) != 0xffff)
    goto rom_1FA4;                                   // DBF.W	D0,$1FA4
  DEF_ROMLOC(1FAA) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(1FAC) : move_toreg_32(0xFFFFFA80, &A0); // LEA.L	$FA80,A0
  DEF_ROMLOC(1FB0)
      : move_toreg_8(read_8(0xFFFFF626), &D0); // MOVE.B	$F626,D0
  DEF_ROMLOC(1FB4) : add_toreg_16(D0, &A0);    // ADDA.W	D0,A0
  DEF_ROMLOC(1FB6)
      : move_toreg_8(read_8(0xFFFFF627), &D0); // MOVE.B	$F627,D0
  DEF_ROMLOC(1FBA) : color_move_towards_white();               // BSR.B	$1FC2
  DEF_ROMLOC(1FBC) : dec_reg_16(&D0);
  if ((D0 & 0xffff) != 0xffff)
    goto rom_1FBA;           // DBF.W	D0,$1FBA
  DEF_ROMLOC(1FC0) : return; // RTS
}
void color_move_towards_white(void) {
  DEF_ROMLOC(1FC2) : move_toreg_16(read_16(A0), &D2); // MOVE.W	(A0),D2
  DEF_ROMLOC(1FC4) : cmp_toreg_16(0xEEE, &D2);        // CMPI.W	#$0EEE,D2
  DEF_ROMLOC(1FC8) : if (CCR_EQ) goto rom_1FFE;       // BEQ.B	$1FFE
  DEF_ROMLOC(1FCA) : move_toreg_16(D2, &D1);          // MOVE.W	D2,D1
  DEF_ROMLOC(1FCC) : and_toreg_16(0xE, &D1);          // ANDI.W	#$000E,D1
  DEF_ROMLOC(1FD0) : cmp_toreg_16(0xE, &D1);          // CMPI.W	#$000E,D1
  DEF_ROMLOC(1FD4) : if (CCR_EQ) goto rom_1FDA;       // BEQ.B	$1FDA
  DEF_ROMLOC(1FD6)
      : add_tomem_16(0x2, (A0 += 2, A0 - 2));   // ADDQ.W	#$02,(A0)+
  DEF_ROMLOC(1FD8) : return;                    // RTS
  DEF_ROMLOC(1FDA) : move_toreg_16(D2, &D1);    // MOVE.W	D2,D1
  DEF_ROMLOC(1FDC) : and_toreg_16(0xE0, &D1);   // ANDI.W	#$00E0,D1
  DEF_ROMLOC(1FE0) : cmp_toreg_16(0xE0, &D1);   // CMPI.W	#$00E0,D1
  DEF_ROMLOC(1FE4) : if (CCR_EQ) goto rom_1FEC; // BEQ.B	$1FEC
  DEF_ROMLOC(1FE6)
      : add_tomem_16(0x20, (A0 += 2, A0 - 2));  // ADDI.W	#$0020,(A0)+
  DEF_ROMLOC(1FEA) : return;                    // RTS
  DEF_ROMLOC(1FEC) : move_toreg_16(D2, &D1);    // MOVE.W	D2,D1
  DEF_ROMLOC(1FEE) : and_toreg_16(0xE00, &D1);  // ANDI.W	#$0E00,D1
  DEF_ROMLOC(1FF2) : cmp_toreg_16(0xE00, &D1);  // CMPI.W	#$0E00,D1
  DEF_ROMLOC(1FF6) : if (CCR_EQ) goto rom_1FFE; // BEQ.B	$1FFE
  DEF_ROMLOC(1FF8)
      : add_tomem_16(0x200, (A0 += 2, A0 - 2)); // ADDI.W	#$0200,(A0)+
  DEF_ROMLOC(1FFC) : return;                    // RTS
  DEF_ROMLOC(1FFE) : add_toreg_16(0x2, &A0);    // ADDQ.W	#$02,A0
  DEF_ROMLOC(2000) : return;                    // RTS
}
void load_palette_fading(void) {
  DEF_ROMLOC(20F4) : move_toreg_32(0x2160, &A1); // LEA.L	$00002160,A1
  DEF_ROMLOC(20FA) : lsl_toreg_16(0x3, &D0);     // LSL.W	#$03,D0
  DEF_ROMLOC(20FC) : add_toreg_16(D0, &A1);      // ADDA.W	D0,A1
  DEF_ROMLOC(20FE)
      : move_toreg_32(read_32((A1 += 4, A1 - 4)), &A2); // MOVEA.L	(A1)+,A2
  DEF_ROMLOC(2100)
      : move_toreg_16(read_16((A1 += 2, A1 - 2)), &A3); // MOVEA.W	(A1)+,A3
  DEF_ROMLOC(2102) : add_toreg_16(0x80, &A3);           // ADDA.W	#$0080,A3
  DEF_ROMLOC(2106)
      : move_toreg_16(read_16((A1 += 2, A1 - 2)), &D7); // MOVE.W	(A1)+,D7
  DEF_ROMLOC(2108)
      : move_tomem_32(read_32((A2 += 4, A2 - 4)),
                      (A3 += 4, A3 - 4)); // MOVE.L	(A2)+,(A3)+
  DEF_ROMLOC(210A) : dec_reg_16(&D7);
  if ((D7 & 0xffff) != 0xffff)
    goto rom_2108;           // DBF.W	D7,$2108
  DEF_ROMLOC(210E) : return; // RTS
}
void load_palette(void) {
  DEF_ROMLOC(2110) : move_toreg_32(0x2160, &A1); // LEA.L	$00002160,A1
  DEF_ROMLOC(2116) : lsl_toreg_16(0x3, &D0);     // LSL.W	#$03,D0
  DEF_ROMLOC(2118) : add_toreg_16(D0, &A1);      // ADDA.W	D0,A1
  DEF_ROMLOC(211A)
      : move_toreg_32(read_32((A1 += 4, A1 - 4)), &A2); // MOVEA.L	(A1)+,A2
  DEF_ROMLOC(211C)
      : move_toreg_16(read_16((A1 += 2, A1 - 2)), &A3); // MOVEA.W	(A1)+,A3
  DEF_ROMLOC(211E)
      : move_toreg_16(read_16((A1 += 2, A1 - 2)), &D7); // MOVE.W	(A1)+,D7
  DEF_ROMLOC(2120)
      : move_tomem_32(read_32((A2 += 4, A2 - 4)),
                      (A3 += 4, A3 - 4)); // MOVE.L	(A2)+,(A3)+
  DEF_ROMLOC(2122) : dec_reg_16(&D7);
  if ((D7 & 0xffff) != 0xffff)
    goto rom_2120;           // DBF.W	D7,$2120
  DEF_ROMLOC(2126) : return; // RTS
}
void load_palette_water_fading(void) {
  DEF_ROMLOC(2128) : move_toreg_32(0x2160, &A1); // LEA.L	$00002160,A1
  DEF_ROMLOC(212E) : lsl_toreg_16(0x3, &D0);     // LSL.W	#$03,D0
  DEF_ROMLOC(2130) : add_toreg_16(D0, &A1);      // ADDA.W	D0,A1
  DEF_ROMLOC(2132)
      : move_toreg_32(read_32((A1 += 4, A1 - 4)), &A2); // MOVEA.L	(A1)+,A2
  DEF_ROMLOC(2134)
      : move_toreg_16(read_16((A1 += 2, A1 - 2)), &A3); // MOVEA.W	(A1)+,A3
  DEF_ROMLOC(2136) : sub_toreg_16(0x80, &A3);           // SUBA.W	#$0080,A3
  DEF_ROMLOC(213A)
      : move_toreg_16(read_16((A1 += 2, A1 - 2)), &D7); // MOVE.W	(A1)+,D7
  DEF_ROMLOC(213C)
      : move_tomem_32(read_32((A2 += 4, A2 - 4)),
                      (A3 += 4, A3 - 4)); // MOVE.L	(A2)+,(A3)+
  DEF_ROMLOC(213E) : dec_reg_16(&D7);
  if ((D7 & 0xffff) != 0xffff)
    goto rom_213C;           // DBF.W	D7,$213C
  DEF_ROMLOC(2142) : return; // RTS
}
void load_palette_water(void) {
  DEF_ROMLOC(2144) : move_toreg_32(0x2160, &A1); // LEA.L	$00002160,A1
  DEF_ROMLOC(214A) : lsl_toreg_16(0x3, &D0);     // LSL.W	#$03,D0
  DEF_ROMLOC(214C) : add_toreg_16(D0, &A1);      // ADDA.W	D0,A1
  DEF_ROMLOC(214E)
      : move_toreg_32(read_32((A1 += 4, A1 - 4)), &A2); // MOVEA.L	(A1)+,A2
  DEF_ROMLOC(2150)
      : move_toreg_16(read_16((A1 += 2, A1 - 2)), &A3); // MOVEA.W	(A1)+,A3
  DEF_ROMLOC(2152) : sub_toreg_16(0x100, &A3);          // SUBA.W	#$0100,A3
  DEF_ROMLOC(2156)
      : move_toreg_16(read_16((A1 += 2, A1 - 2)), &D7); // MOVE.W	(A1)+,D7
  DEF_ROMLOC(2158)
      : move_tomem_32(read_32((A2 += 4, A2 - 4)),
                      (A3 += 4, A3 - 4)); // MOVE.L	(A2)+,(A3)+
  DEF_ROMLOC(215A) : dec_reg_16(&D7);
  if ((D7 & 0xffff) != 0xffff)
    goto rom_2158;           // DBF.W	D7,$2158
  DEF_ROMLOC(215E) : return; // RTS
}