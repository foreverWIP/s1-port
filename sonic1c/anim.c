// #define CHECK_STUFF 1
#include "opcodes.h"
#include "system.h"


void run_global_anims(void) {
  DEF_ROMLOC(4208) : sub_tomem_8(0x1, 0xFFFFFEC0);  // SUBQ.B	#$01,$FEC0
  DEF_ROMLOC(420C) : if (CCR_PL) goto rom_421E;     // BPL.B	$421E
  DEF_ROMLOC(420E) : move_tomem_8(0xB, 0xFFFFFEC0); // MOVE.B	#$0B,$FEC0
  DEF_ROMLOC(4214) : sub_tomem_8(0x1, 0xFFFFFEC1);  // SUBQ.B	#$01,$FEC1
  DEF_ROMLOC(4218) : and_tomem_8(0x7, 0xFFFFFEC1);  // ANDI.B	#$07,$FEC1
  DEF_ROMLOC(421E) : sub_tomem_8(0x1, 0xFFFFFEC2);  // SUBQ.B	#$01,$FEC2
  DEF_ROMLOC(4222) : if (CCR_PL) goto rom_4234;     // BPL.B	$4234
  DEF_ROMLOC(4224) : move_tomem_8(0x7, 0xFFFFFEC2); // MOVE.B	#$07,$FEC2
  DEF_ROMLOC(422A) : add_tomem_8(0x1, 0xFFFFFEC3);  // ADDQ.B	#$01,$FEC3
  DEF_ROMLOC(422E) : and_tomem_8(0x3, 0xFFFFFEC3);  // ANDI.B	#$03,$FEC3
  DEF_ROMLOC(4234) : sub_tomem_8(0x1, 0xFFFFFEC4);  // SUBQ.B	#$01,$FEC4
  DEF_ROMLOC(4238) : if (CCR_PL) goto rom_4252;     // BPL.B	$4252
  DEF_ROMLOC(423A) : move_tomem_8(0x7, 0xFFFFFEC4); // MOVE.B	#$07,$FEC4
  DEF_ROMLOC(4240) : add_tomem_8(0x1, 0xFFFFFEC5);  // ADDQ.B	#$01,$FEC5
  DEF_ROMLOC(4244) : cmp_tomem_8(0x6, 0xFFFFFEC5);  // CMPI.B	#$06,$FEC5
  DEF_ROMLOC(424A) : if (CCR_CS) goto rom_4252;     // BCS.B	$4252
  DEF_ROMLOC(424C) : move_tomem_8(0x0, 0xFFFFFEC5); // MOVE.B	#$00,$FEC5
  DEF_ROMLOC(4252) : tst_mem_8(0xFFFFFEC6);         // TST.B	$FEC6
  DEF_ROMLOC(4256) : if (CCR_EQ) goto rom_4274;     // BEQ.B	$4274
  DEF_ROMLOC(4258) : move_toreg_32(0x0, &D0);       // MOVEQ.L	$00,D0
  DEF_ROMLOC(425A)
      : move_toreg_8(read_8(0xFFFFFEC6), &D0); // MOVE.B	$FEC6,D0
  DEF_ROMLOC(425E)
      : add_toreg_16(read_16(0xFFFFFEC8), &D0);     // ADD.W	$FEC8,D0
  DEF_ROMLOC(4262) : move_tomem_16(D0, 0xFFFFFEC8); // MOVE.W	D0,$FEC8
  DEF_ROMLOC(4266) : rol_toreg_16(0x7, &D0);        // ROL.W	#$07,D0
  DEF_ROMLOC(4268) : and_toreg_16(0x3, &D0);        // ANDI.W	#$0003,D0
  DEF_ROMLOC(426C) : move_tomem_8(D0, 0xFFFFFEC7);  // MOVE.B	D0,$FEC7
  DEF_ROMLOC(4270) : sub_tomem_8(0x1, 0xFFFFFEC6);  // SUBQ.B	#$01,$FEC6
  DEF_ROMLOC(4274) : return;                        // RTS
}
void maybe_load_signpost_art(void) {
  DEF_ROMLOC(4276) : tst_mem_16(0xFFFFFE08);       // TST.W	$FE08
  DEF_ROMLOC(427A) : if (!CCR_EQ) goto rom_42AC;   // BNE.W	$42AC
  DEF_ROMLOC(427E) : cmp_tomem_8(0x2, v_act); // CMPI.B	#$02,$FE11
  DEF_ROMLOC(4284) : if (CCR_EQ) goto rom_42AC;    // BEQ.B	$42AC
  DEF_ROMLOC(4286)
      : move_toreg_16(read_16(0xFFFFF700), &D0); // MOVE.W	$F700,D0
  DEF_ROMLOC(428A)
      : move_toreg_16(read_16(0xFFFFF72A), &D1); // MOVE.W	$F72A,D1
  DEF_ROMLOC(428E) : sub_toreg_16(0x100, &D1);   // SUBI.W	#$0100,D1
  DEF_ROMLOC(4292) : cmp_toreg_16(D1, &D0);      // CMP.W	D1,D0
  DEF_ROMLOC(4294) : if (CCR_LT) goto rom_42AC;  // BLT.B	$42AC
  DEF_ROMLOC(4296) : tst_mem_8(0xFFFFFE1E);      // TST.B	$FE1E
  DEF_ROMLOC(429A) : if (CCR_EQ) goto rom_42AC;  // BEQ.B	$42AC
  DEF_ROMLOC(429C)
      : cmp_toreg_16(read_16(0xFFFFF728), &D1);     // CMP.W	$F728,D1
  DEF_ROMLOC(42A0) : if (CCR_EQ) goto rom_42AC;     // BEQ.B	$42AC
  DEF_ROMLOC(42A2) : move_tomem_16(D1, 0xFFFFF728); // MOVE.W	D1,$F728
  DEF_ROMLOC(42A6) : move_toreg_32(0x12, &D0);      // MOVEQ.L	$12,D0
  DEF_ROMLOC(42A8) : {
    new_plc();
    return;
  }                          // BRA.W	$15AA
  DEF_ROMLOC(42AC) : return; // RTS
}
void animate_sprite(void) {
  DEF_ROMLOC(ADA2) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(ADA4)
      : move_toreg_8(read_8(A0 + 0x1C), &D0);             // MOVE.B	28(A0),D0
  DEF_ROMLOC(ADA8) : cmp_toreg_8(read_8(A0 + 0x1D), &D0); // CMP.B
                                                          // 29(A0),D0
  DEF_ROMLOC(ADAC) : if (CCR_EQ) goto rom_ADBE;           // BEQ.B	$ADBE
  DEF_ROMLOC(ADAE) : move_tomem_8(D0, A0 + 0x1D);         // MOVE.B	D0,29(A0)
  DEF_ROMLOC(ADB2) : move_tomem_8(0x0, A0 + 0x1B);        // MOVE.B	#$00,27(A0)
  DEF_ROMLOC(ADB8) : move_tomem_8(0x0, A0 + 0x1E);        // MOVE.B	#$00,30(A0)
  DEF_ROMLOC(ADBE) : sub_tomem_8(0x1, A0 + 0x1E);         // SUBQ.B	#$01,30(A0)
  DEF_ROMLOC(ADC2) : if (CCR_PL) goto rom_ADFE;           // BPL.B	$ADFE
  DEF_ROMLOC(ADC4) : add_toreg_16(D0, &D0);               // ADD.W	D0,D0
  DEF_ROMLOC(ADC6)
      : add_toreg_16(read_16((s32)A1 + (s8)0x0 + (s16)D0),
                     &A1); // ADDA.W	0(A1,D0),A1
  DEF_ROMLOC(ADCA)
      : move_tomem_8(read_8(A1), A0 + 0x1E);  // MOVE.B	(A1),30(A0)
  DEF_ROMLOC(ADCE) : move_toreg_32(0x0, &D1); // MOVEQ.L	$00,D1
  DEF_ROMLOC(ADD0)
      : move_toreg_8(read_8(A0 + 0x1B), &D1); // MOVE.B	27(A0),D1
  DEF_ROMLOC(ADD4)
      : move_toreg_8(read_8((s32)A1 + (s8)0x1 + (s16)D1),
                     &D0);                        // MOVE.B	1(A1,D1),D0
  DEF_ROMLOC(ADD8) : if (CCR_MI) goto rom_AE00;   // BMI.B	$AE00
  DEF_ROMLOC(ADDA) : move_toreg_8(D0, &D1);       // MOVE.B	D0,D1
  DEF_ROMLOC(ADDC) : and_toreg_8(0x1F, &D0);      // ANDI.B	#$1F,D0
  DEF_ROMLOC(ADE0) : move_tomem_8(D0, A0 + 0x1A); // MOVE.B	D0,26(A0)
  DEF_ROMLOC(ADE4)
      : move_toreg_8(read_8(A0 + 0x22), &D0);           // MOVE.B	34(A0),D0
  DEF_ROMLOC(ADE8) : rol_toreg_8(0x3, &D1);             // ROL.B	#$03,D1
  DEF_ROMLOC(ADEA) : eor_toreg_8(D0, &D1);              // EOR.B	D0,D1
  DEF_ROMLOC(ADEC) : and_toreg_8(0x3, &D1);             // ANDI.B	#$03,D1
  DEF_ROMLOC(ADF0) : and_tomem_8(0xFFFFFFFC, A0 + 0x1); // ANDI.B
                                                        // #$FC,1(A0)
  DEF_ROMLOC(ADF6) : or_tomem_8(D1, A0 + 0x1);          // OR.B	D1,1(A0)
  DEF_ROMLOC(ADFA) : add_tomem_8(0x1, A0 + 0x1B);       // ADDQ.B	#$01,27(A0)
  DEF_ROMLOC(ADFE) : return;                            // RTS
  DEF_ROMLOC(AE00) : add_toreg_8(0x1, &D0);             // ADDQ.B	#$01,D0
  DEF_ROMLOC(AE02) : if (!CCR_EQ) goto rom_AE10;        // BNE.B	$AE10
  DEF_ROMLOC(AE04) : move_tomem_8(0x0, A0 + 0x1B);      // MOVE.B	#$00,27(A0)
  DEF_ROMLOC(AE0A)
      : move_toreg_8(read_8(A1 + 0x1), &D0);     // MOVE.B	1(A1),D0
  goto rom_ADDA;                                 // BRA.B	$ADDA
  DEF_ROMLOC(AE10) : add_toreg_8(0x1, &D0);      // ADDQ.B	#$01,D0
  DEF_ROMLOC(AE12) : if (!CCR_EQ) goto rom_AE24; // BNE.B	$AE24
  DEF_ROMLOC(AE14)
      : move_toreg_8(read_8((s32)A1 + (s8)0x2 + (s16)D1),
                     &D0);                       // MOVE.B	2(A1,D1),D0
  DEF_ROMLOC(AE18) : sub_tomem_8(D0, A0 + 0x1B); // SUB.B	D0,27(A0)
  DEF_ROMLOC(AE1C) : sub_toreg_8(D0, &D1);       // SUB.B	D0,D1
  DEF_ROMLOC(AE1E)
      : move_toreg_8(read_8((s32)A1 + (s8)0x1 + (s16)D1),
                     &D0);                       // MOVE.B	1(A1,D1),D0
  goto rom_ADDA;                                 // BRA.B	$ADDA
  DEF_ROMLOC(AE24) : add_toreg_8(0x1, &D0);      // ADDQ.B	#$01,D0
  DEF_ROMLOC(AE26) : if (!CCR_EQ) goto rom_AE2E; // BNE.B	$AE2E
  DEF_ROMLOC(AE28)
      : move_tomem_8(read_8((s32)A1 + (s8)0x2 + (s16)D1),
                     A0 + 0x1C);                   // MOVE.B	2(A1,D1),28(A0)
  DEF_ROMLOC(AE2E) : add_toreg_8(0x1, &D0);        // ADDQ.B	#$01,D0
  DEF_ROMLOC(AE30) : if (!CCR_EQ) goto rom_AE36;   // BNE.B	$AE36
  DEF_ROMLOC(AE32) : add_tomem_8(0x2, A0 + 0x24);  // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(AE36) : add_toreg_8(0x1, &D0);        // ADDQ.B	#$01,D0
  DEF_ROMLOC(AE38) : if (!CCR_EQ) goto rom_AE44;   // BNE.B	$AE44
  DEF_ROMLOC(AE3A) : move_tomem_8(0x0, A0 + 0x1B); // MOVE.B	#$00,27(A0)
  DEF_ROMLOC(AE40) : clr_mem_8(A0 + 0x25);         // CLR.B	37(A0)
  DEF_ROMLOC(AE44) : add_toreg_8(0x1, &D0);        // ADDQ.B	#$01,D0
  DEF_ROMLOC(AE46) : if (!CCR_EQ) goto rom_AE4C;   // BNE.B	$AE4C
  DEF_ROMLOC(AE48) : add_tomem_8(0x2, A0 + 0x25);  // ADDQ.B	#$02,37(A0)
  DEF_ROMLOC(AE4C) : return;                       // RTS
}