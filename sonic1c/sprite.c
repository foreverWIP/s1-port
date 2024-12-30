// #define CHECK_STUFF 1
#include "opcodes.h"
#include "system.h"

ROMFUNC(rom_DCEC) {
  DEF_ROMLOC(DCEC) : move_toreg_32(0xFFFFF800, &A2); // LEA.L	$F800,A2
  DEF_ROMLOC(DCF0) : move_toreg_32(0x0, &D5);        // MOVEQ.L	$00,D5
  DEF_ROMLOC(DCF2) : move_toreg_32(0xFFFFAC00, &A4); // LEA.L	$AC00,A4
  DEF_ROMLOC(DCF6) : move_toreg_32(0x7, &D7);        // MOVEQ.L	$07,D7
  DEF_ROMLOC(DCF8) : tst_mem_16(A4);                 // TST.W	(A4)
  DEF_ROMLOC(DCFA) : if (CCR_EQ) goto rom_DDBC;      // BEQ.W	$DDBC
  DEF_ROMLOC(DCFE) : move_toreg_32(0x2, &D6);        // MOVEQ.L	$02,D6
  DEF_ROMLOC(DD00)
      : move_toreg_16(read_16((s32)A4 + (s8)0x0 + (s16)D6),
                      &A0);                       // MOVEA.W	0(A4,D6),A0
  DEF_ROMLOC(DD04) : tst_mem_8(A0);               // TST.B	(A0)
  DEF_ROMLOC(DD06) : if (CCR_EQ) goto rom_DDB4;   // BEQ.W	$DDB4
  DEF_ROMLOC(DD0A) : bclr_tomem_8(0x7, A0 + 0x1); // BCLR.B	#$07,1(A0)
  DEF_ROMLOC(DD10)
      : move_toreg_8(read_8(A0 + 0x1), &D0);    // MOVE.B	1(A0),D0
  DEF_ROMLOC(DD14) : move_toreg_8(D0, &D4);     // MOVE.B	D0,D4
  DEF_ROMLOC(DD16) : and_toreg_16(0xC, &D0);    // ANDI.W	#$000C,D0
  DEF_ROMLOC(DD1A) : if (CCR_EQ) goto rom_DD6C; // BEQ.B	$DD6C
  DEF_ROMLOC(DD1C)
      : move_toreg_32(read_32(0xDCDC + (s16)(D0 & 0xffff)),
                      &A1);                   // MOVEA.L	-66(PC,D0),A1
  DEF_ROMLOC(DD20) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(DD22) : move_toreg_8(read_8(A0 + 0x19), &D0);  // MOVE.B
                                                            // 25(A0),D0
  DEF_ROMLOC(DD26) : move_toreg_16(read_16(A0 + 0x8), &D3); // MOVE.W	8(A0),D3
  DEF_ROMLOC(DD2A) : sub_toreg_16(read_16(A1), &D3);        // SUB.W	(A1),D3
  DEF_ROMLOC(DD2C) : move_toreg_16(D3, &D1);                // MOVE.W	D3,D1
  DEF_ROMLOC(DD2E) : add_toreg_16(D0, &D1);                 // ADD.W	D0,D1
  DEF_ROMLOC(DD30) : if (CCR_MI) goto rom_DDB4;             // BMI.W	$DDB4
  DEF_ROMLOC(DD34) : move_toreg_16(D3, &D1);                // MOVE.W	D3,D1
  DEF_ROMLOC(DD36) : sub_toreg_16(D0, &D1);                 // SUB.W	D0,D1
  DEF_ROMLOC(DD38) : cmp_toreg_16(0x140, &D1);              // CMPI.W	#$0140,D1
  DEF_ROMLOC(DD3C) : if (CCR_GE) goto rom_DDB4;             // BGE.B	$DDB4
  DEF_ROMLOC(DD3E) : add_toreg_16(0x80, &D3);               // ADDI.W	#$0080,D3
  DEF_ROMLOC(DD42) : btst_toreg_32(0x4, &D4);               // BTST.L	#$04,D4
  DEF_ROMLOC(DD46) : if (CCR_EQ) goto rom_DD76;             // BEQ.B	$DD76
  DEF_ROMLOC(DD48) : move_toreg_32(0x0, &D0);               // MOVEQ.L	$00,D0
  DEF_ROMLOC(DD4A) : move_toreg_8(read_8(A0 + 0x16), &D0);  // MOVE.B
                                                            // 22(A0),D0
  DEF_ROMLOC(DD4E)
      : move_toreg_16(read_16(A0 + 0xC), &D2); // MOVE.W	12(A0),D2
  DEF_ROMLOC(DD52)
      : sub_toreg_16(read_16(A1 + 0x4), &D2);   // SUB.W	4(A1),D2
  DEF_ROMLOC(DD56) : move_toreg_16(D2, &D1);    // MOVE.W	D2,D1
  DEF_ROMLOC(DD58) : add_toreg_16(D0, &D1);     // ADD.W	D0,D1
  DEF_ROMLOC(DD5A) : if (CCR_MI) goto rom_DDB4; // BMI.B	$DDB4
  DEF_ROMLOC(DD5C) : move_toreg_16(D2, &D1);    // MOVE.W	D2,D1
  DEF_ROMLOC(DD5E) : sub_toreg_16(D0, &D1);     // SUB.W	D0,D1
  DEF_ROMLOC(DD60) : cmp_toreg_16(0xE0, &D1);   // CMPI.W	#$00E0,D1
  DEF_ROMLOC(DD64) : if (CCR_GE) goto rom_DDB4; // BGE.B	$DDB4
  DEF_ROMLOC(DD66) : add_toreg_16(0x80, &D2);   // ADDI.W	#$0080,D2
  DEF_ROMLOC(DD6A) : goto rom_DD8E;             // BRA.B	$DD8E
  DEF_ROMLOC(DD6C)
      : move_toreg_16(read_16(A0 + 0xA), &D2); // MOVE.W	10(A0),D2
  DEF_ROMLOC(DD70)
      : move_toreg_16(read_16(A0 + 0x8), &D3); // MOVE.W	8(A0),D3
  DEF_ROMLOC(DD74) : goto rom_DD8E;            // BRA.B	$DD8E
  DEF_ROMLOC(DD76)
      : move_toreg_16(read_16(A0 + 0xC), &D2); // MOVE.W	12(A0),D2
  DEF_ROMLOC(DD7A)
      : sub_toreg_16(read_16(A1 + 0x4), &D2);   // SUB.W	4(A1),D2
  DEF_ROMLOC(DD7E) : add_toreg_16(0x80, &D2);   // ADDI.W	#$0080,D2
  DEF_ROMLOC(DD82) : cmp_toreg_16(0x60, &D2);   // CMPI.W	#$0060,D2
  DEF_ROMLOC(DD86) : if (CCR_CS) goto rom_DDB4; // BCS.B	$DDB4
  DEF_ROMLOC(DD88) : cmp_toreg_16(0x180, &D2);  // CMPI.W	#$0180,D2
  DEF_ROMLOC(DD8C) : if (CCR_CC) goto rom_DDB4; // BCC.B	$DDB4
  DEF_ROMLOC(DD8E)
      : move_toreg_32(read_32(A0 + 0x4), &A1);             // MOVEA.L	4(A0),A1
  DEF_ROMLOC(DD92) : move_toreg_32(0x0, &D1);              // MOVEQ.L	$00,D1
  DEF_ROMLOC(DD94) : btst_toreg_32(0x5, &D4);              // BTST.L	#$05,D4
  DEF_ROMLOC(DD98) : if (!CCR_EQ) goto rom_DDAA;           // BNE.B	$DDAA
  DEF_ROMLOC(DD9A) : move_toreg_8(read_8(A0 + 0x1A), &D1); // MOVE.B
                                                           // 26(A0),D1
  DEF_ROMLOC(DD9E) : add_toreg_8(D1, &D1);                 // ADD.B	D1,D1
  DEF_ROMLOC(DDA0)
      : add_toreg_16(read_16((s32)A1 + (s8)0x0 + (s16)D1),
                     &A1);                            // ADDA.W	0(A1,D1),A1
  DEF_ROMLOC(DDA4) : move_toreg_8(read_8(A1++), &D1); // MOVE.B	(A1)+,D1
  DEF_ROMLOC(DDA6) : sub_toreg_8(0x1, &D1);           // SUBQ.B	#$01,D1
  DEF_ROMLOC(DDA8) : if (CCR_MI) goto rom_DDAE;       // BMI.B	$DDAE
  DEF_ROMLOC(DDAA) : rom_DDDE();                      // BSR.W	$DDDE
  DEF_ROMLOC(DDAE) : bset_tomem_8(0x7, A0 + 0x1);     // BSET.B	#$07,1(A0)
  DEF_ROMLOC(DDB4) : add_toreg_16(0x2, &D6);          // ADDQ.W	#$02,D6
  DEF_ROMLOC(DDB6) : sub_tomem_16(0x2, A4);           // SUBQ.W	#$02,(A4)
  DEF_ROMLOC(DDB8) : if (!CCR_EQ) goto rom_DD00;      // BNE.W	$DD00
  DEF_ROMLOC(DDBC) : move_toreg_32(A4 + 0x80, &A4);   // LEA.L	128(A4),A4
  DEF_ROMLOC(DDC0) : dec_reg_16(&D7);
  if ((D7 & 0xffff) != 0xffff)
    goto rom_DCF8;                                 // DBF.W	D7,$DCF8
  DEF_ROMLOC(DDC4) : move_tomem_8(D5, 0xFFFFF62C); // MOVE.B	D5,$F62C
  DEF_ROMLOC(DDC8) : cmp_toreg_8(0x50, &D5);       // CMPI.B	#$50,D5
  DEF_ROMLOC(DDCC) : if (CCR_EQ) goto rom_DDD6;    // BEQ.B	$DDD6
  DEF_ROMLOC(DDCE) : move_tomem_32(0x0, A2);       // MOVE.L	#$00000000,(A2)
  DEF_ROMLOC(DDD4) : return;                       // RTS
  DEF_ROMLOC(DDD6) : move_tomem_8(0x0, A2 - 0x5);  // MOVE.B	#$00,-5(A2)
  DEF_ROMLOC(DDDC) : return;                       // RTS
}
ROMFUNC(rom_DDF0) {
  DEF_ROMLOC(DDF0) : cmp_toreg_8(0x50, &D5);          // CMPI.B	#$50,D5
  DEF_ROMLOC(DDF4) : if (CCR_EQ) goto rom_DE22;       // BEQ.B	$DE22
  DEF_ROMLOC(DDF6) : move_toreg_8(read_8(A1++), &D0); // MOVE.B	(A1)+,D0
  DEF_ROMLOC(DDF8) : ext_reg_16(&D0);                 // EXT.W	D0
  DEF_ROMLOC(DDFA) : add_toreg_16(D2, &D0);           // ADD.W	D2,D0
  DEF_ROMLOC(DDFC)
      : move_tomem_16(D0, (A2 += 2, A2 - 2)); // MOVE.W	D0,(A2)+
  DEF_ROMLOC(DDFE)
      : move_tomem_8(read_8(A1++), A2++);                  // MOVE.B
                                                           // (A1)+,(A2)+
  DEF_ROMLOC(DE00) : add_toreg_8(0x1, &D5);                // ADDQ.B	#$01,D5
  DEF_ROMLOC(DE02) : move_tomem_8(D5, A2++);               // MOVE.B	D5,(A2)+
  DEF_ROMLOC(DE04) : move_toreg_8(read_8(A1++), &D0);      // MOVE.B	(A1)+,D0
  DEF_ROMLOC(DE06) : lsl_toreg_16(0x8, &D0);               // LSL.W	#$08,D0
  DEF_ROMLOC(DE08) : move_toreg_8(read_8(A1++), &D0);      // MOVE.B	(A1)+,D0
  DEF_ROMLOC(DE0A) : add_toreg_16(A3, &D0);                // ADD.W	A3,D0
  DEF_ROMLOC(DE0C) : move_tomem_16(D0, (A2 += 2, A2 - 2)); // MOVE.W	D0,(A2)+
  DEF_ROMLOC(DE0E) : move_toreg_8(read_8(A1++), &D0);      // MOVE.B	(A1)+,D0
  DEF_ROMLOC(DE10) : ext_reg_16(&D0);                      // EXT.W	D0
  DEF_ROMLOC(DE12) : add_toreg_16(D3, &D0);                // ADD.W	D3,D0
  DEF_ROMLOC(DE14) : and_toreg_16(0x1FF, &D0);             // ANDI.W	#$01FF,D0
  DEF_ROMLOC(DE18) : if (!CCR_EQ) goto rom_DE1C;           // BNE.B	$DE1C
  DEF_ROMLOC(DE1A) : add_toreg_16(0x1, &D0);               // ADDQ.W	#$01,D0
  DEF_ROMLOC(DE1C) : move_tomem_16(D0, (A2 += 2, A2 - 2)); // MOVE.W	D0,(A2)+
  DEF_ROMLOC(DE1E) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_DDF0;           // DBF.W	D1,$DDF0
  DEF_ROMLOC(DE22) : return; // RTS
}
ROMFUNC(rom_DDDE) {
  DEF_ROMLOC(DDDE)
      : move_toreg_16(read_16(A0 + 0x2), &A3);   // MOVEA.W	2(A0),A3
  DEF_ROMLOC(DDE2) : btst_toreg_32(0x0, &D4);    // BTST.L	#$00,D4
  DEF_ROMLOC(DDE6) : if (!CCR_EQ) goto rom_DE24; // BNE.B	$DE24
  DEF_ROMLOC(DDE8) : btst_toreg_32(0x1, &D4);    // BTST.L	#$01,D4
  DEF_ROMLOC(DDEC) : if (!CCR_EQ) goto rom_DE72; // BNE.W	$DE72

  DEF_ROMLOC(DDF0) : cmp_toreg_8(0x50, &D5);          // CMPI.B	#$50,D5
  DEF_ROMLOC(DDF4) : if (CCR_EQ) goto rom_DE22;       // BEQ.B	$DE22
  DEF_ROMLOC(DDF6) : move_toreg_8(read_8(A1++), &D0); // MOVE.B	(A1)+,D0
  DEF_ROMLOC(DDF8) : ext_reg_16(&D0);                 // EXT.W	D0
  DEF_ROMLOC(DDFA) : add_toreg_16(D2, &D0);           // ADD.W	D2,D0
  DEF_ROMLOC(DDFC)
      : move_tomem_16(D0, (A2 += 2, A2 - 2)); // MOVE.W	D0,(A2)+
  DEF_ROMLOC(DDFE)
      : move_tomem_8(read_8(A1++), A2++);                  // MOVE.B
                                                           // (A1)+,(A2)+
  DEF_ROMLOC(DE00) : add_toreg_8(0x1, &D5);                // ADDQ.B	#$01,D5
  DEF_ROMLOC(DE02) : move_tomem_8(D5, A2++);               // MOVE.B	D5,(A2)+
  DEF_ROMLOC(DE04) : move_toreg_8(read_8(A1++), &D0);      // MOVE.B	(A1)+,D0
  DEF_ROMLOC(DE06) : lsl_toreg_16(0x8, &D0);               // LSL.W	#$08,D0
  DEF_ROMLOC(DE08) : move_toreg_8(read_8(A1++), &D0);      // MOVE.B	(A1)+,D0
  DEF_ROMLOC(DE0A) : add_toreg_16(A3, &D0);                // ADD.W	A3,D0
  DEF_ROMLOC(DE0C) : move_tomem_16(D0, (A2 += 2, A2 - 2)); // MOVE.W	D0,(A2)+
  DEF_ROMLOC(DE0E) : move_toreg_8(read_8(A1++), &D0);      // MOVE.B	(A1)+,D0
  DEF_ROMLOC(DE10) : ext_reg_16(&D0);                      // EXT.W	D0
  DEF_ROMLOC(DE12) : add_toreg_16(D3, &D0);                // ADD.W	D3,D0
  DEF_ROMLOC(DE14) : and_toreg_16(0x1FF, &D0);             // ANDI.W	#$01FF,D0
  DEF_ROMLOC(DE18) : if (!CCR_EQ) goto rom_DE1C;           // BNE.B	$DE1C
  DEF_ROMLOC(DE1A) : add_toreg_16(0x1, &D0);               // ADDQ.W	#$01,D0
  DEF_ROMLOC(DE1C) : move_tomem_16(D0, (A2 += 2, A2 - 2)); // MOVE.W	D0,(A2)+
  DEF_ROMLOC(DE1E) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_DDF0;           // DBF.W	D1,$DDF0
  DEF_ROMLOC(DE22) : return; // RTS

  DEF_ROMLOC(DE24) : btst_toreg_32(0x1, &D4);              // BTST.L	#$01,D4
  DEF_ROMLOC(DE28) : if (!CCR_EQ) goto rom_DEB8;           // BNE.W	$DEB8
  DEF_ROMLOC(DE2C) : cmp_toreg_8(0x50, &D5);               // CMPI.B	#$50,D5
  DEF_ROMLOC(DE30) : if (CCR_EQ) goto rom_DE70;            // BEQ.B	$DE70
  DEF_ROMLOC(DE32) : move_toreg_8(read_8(A1++), &D0);      // MOVE.B	(A1)+,D0
  DEF_ROMLOC(DE34) : ext_reg_16(&D0);                      // EXT.W	D0
  DEF_ROMLOC(DE36) : add_toreg_16(D2, &D0);                // ADD.W	D2,D0
  DEF_ROMLOC(DE38) : move_tomem_16(D0, (A2 += 2, A2 - 2)); // MOVE.W	D0,(A2)+
  DEF_ROMLOC(DE3A) : move_toreg_8(read_8(A1++), &D4);      // MOVE.B	(A1)+,D4
  DEF_ROMLOC(DE3C) : move_tomem_8(D4, A2++);               // MOVE.B	D4,(A2)+
  DEF_ROMLOC(DE3E) : add_toreg_8(0x1, &D5);                // ADDQ.B	#$01,D5
  DEF_ROMLOC(DE40) : move_tomem_8(D5, A2++);               // MOVE.B	D5,(A2)+
  DEF_ROMLOC(DE42) : move_toreg_8(read_8(A1++), &D0);      // MOVE.B	(A1)+,D0
  DEF_ROMLOC(DE44) : lsl_toreg_16(0x8, &D0);               // LSL.W	#$08,D0
  DEF_ROMLOC(DE46) : move_toreg_8(read_8(A1++), &D0);      // MOVE.B	(A1)+,D0
  DEF_ROMLOC(DE48) : add_toreg_16(A3, &D0);                // ADD.W	A3,D0
  DEF_ROMLOC(DE4A) : eor_toreg_16(0x800, &D0);             // EORI.W	#$0800,D0
  DEF_ROMLOC(DE4E) : move_tomem_16(D0, (A2 += 2, A2 - 2)); // MOVE.W	D0,(A2)+
  DEF_ROMLOC(DE50) : move_toreg_8(read_8(A1++), &D0);      // MOVE.B	(A1)+,D0
  DEF_ROMLOC(DE52) : ext_reg_16(&D0);                      // EXT.W	D0
  DEF_ROMLOC(DE54) : neg_reg_16(&D0);                      // NEG.W	D0
  DEF_ROMLOC(DE56) : add_toreg_8(D4, &D4);                 // ADD.B	D4,D4
  DEF_ROMLOC(DE58) : and_toreg_16(0x18, &D4);              // ANDI.W	#$0018,D4
  DEF_ROMLOC(DE5C) : add_toreg_16(0x8, &D4);               // ADDQ.W	#$08,D4
  DEF_ROMLOC(DE5E) : sub_toreg_16(D4, &D0);                // SUB.W	D4,D0
  DEF_ROMLOC(DE60) : add_toreg_16(D3, &D0);                // ADD.W	D3,D0
  DEF_ROMLOC(DE62) : and_toreg_16(0x1FF, &D0);             // ANDI.W	#$01FF,D0
  DEF_ROMLOC(DE66) : if (!CCR_EQ) goto rom_DE6A;           // BNE.B	$DE6A
  DEF_ROMLOC(DE68) : add_toreg_16(0x1, &D0);               // ADDQ.W	#$01,D0
  DEF_ROMLOC(DE6A) : move_tomem_16(D0, (A2 += 2, A2 - 2)); // MOVE.W	D0,(A2)+
  DEF_ROMLOC(DE6C) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_DE2C;           // DBF.W	D1,$DE2C
  DEF_ROMLOC(DE70) : return; // RTS

  DEF_ROMLOC(DE72) : cmp_toreg_8(0x50, &D5);          // CMPI.B	#$50,D5
  DEF_ROMLOC(DE76) : if (CCR_EQ) goto rom_DEB6;       // BEQ.B	$DEB6
  DEF_ROMLOC(DE78) : move_toreg_8(read_8(A1++), &D0); // MOVE.B	(A1)+,D0
  DEF_ROMLOC(DE7A) : move_toreg_8(read_8(A1), &D4);   // MOVE.B	(A1),D4
  DEF_ROMLOC(DE7C) : ext_reg_16(&D0);                 // EXT.W	D0
  DEF_ROMLOC(DE7E) : neg_reg_16(&D0);                 // NEG.W	D0
  DEF_ROMLOC(DE80) : lsl_toreg_8(0x3, &D4);           // LSL.B	#$03,D4
  DEF_ROMLOC(DE82) : and_toreg_16(0x18, &D4);         // ANDI.W	#$0018,D4
  DEF_ROMLOC(DE86) : add_toreg_16(0x8, &D4);          // ADDQ.W	#$08,D4
  DEF_ROMLOC(DE88) : sub_toreg_16(D4, &D0);           // SUB.W	D4,D0
  DEF_ROMLOC(DE8A) : add_toreg_16(D2, &D0);           // ADD.W	D2,D0
  DEF_ROMLOC(DE8C)
      : move_tomem_16(D0, (A2 += 2, A2 - 2)); // MOVE.W	D0,(A2)+
  DEF_ROMLOC(DE8E)
      : move_tomem_8(read_8(A1++), A2++);                  // MOVE.B
                                                           // (A1)+,(A2)+
  DEF_ROMLOC(DE90) : add_toreg_8(0x1, &D5);                // ADDQ.B	#$01,D5
  DEF_ROMLOC(DE92) : move_tomem_8(D5, A2++);               // MOVE.B	D5,(A2)+
  DEF_ROMLOC(DE94) : move_toreg_8(read_8(A1++), &D0);      // MOVE.B	(A1)+,D0
  DEF_ROMLOC(DE96) : lsl_toreg_16(0x8, &D0);               // LSL.W	#$08,D0
  DEF_ROMLOC(DE98) : move_toreg_8(read_8(A1++), &D0);      // MOVE.B	(A1)+,D0
  DEF_ROMLOC(DE9A) : add_toreg_16(A3, &D0);                // ADD.W	A3,D0
  DEF_ROMLOC(DE9C) : eor_toreg_16(0x1000, &D0);            // EORI.W	#$1000,D0
  DEF_ROMLOC(DEA0) : move_tomem_16(D0, (A2 += 2, A2 - 2)); // MOVE.W	D0,(A2)+
  DEF_ROMLOC(DEA2) : move_toreg_8(read_8(A1++), &D0);      // MOVE.B	(A1)+,D0
  DEF_ROMLOC(DEA4) : ext_reg_16(&D0);                      // EXT.W	D0
  DEF_ROMLOC(DEA6) : add_toreg_16(D3, &D0);                // ADD.W	D3,D0
  DEF_ROMLOC(DEA8) : and_toreg_16(0x1FF, &D0);             // ANDI.W	#$01FF,D0
  DEF_ROMLOC(DEAC) : if (!CCR_EQ) goto rom_DEB0;           // BNE.B	$DEB0
  DEF_ROMLOC(DEAE) : add_toreg_16(0x1, &D0);               // ADDQ.W	#$01,D0
  DEF_ROMLOC(DEB0) : move_tomem_16(D0, (A2 += 2, A2 - 2)); // MOVE.W	D0,(A2)+
  DEF_ROMLOC(DEB2) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_DE72;           // DBF.W	D1,$DE72
  DEF_ROMLOC(DEB6) : return; // RTS

  DEF_ROMLOC(DEB8) : cmp_toreg_8(0x50, &D5);               // CMPI.B	#$50,D5
  DEF_ROMLOC(DEBC) : if (CCR_EQ) goto rom_DF0A;            // BEQ.B	$DF0A
  DEF_ROMLOC(DEBE) : move_toreg_8(read_8(A1++), &D0);      // MOVE.B	(A1)+,D0
  DEF_ROMLOC(DEC0) : move_toreg_8(read_8(A1), &D4);        // MOVE.B	(A1),D4
  DEF_ROMLOC(DEC2) : ext_reg_16(&D0);                      // EXT.W	D0
  DEF_ROMLOC(DEC4) : neg_reg_16(&D0);                      // NEG.W	D0
  DEF_ROMLOC(DEC6) : lsl_toreg_8(0x3, &D4);                // LSL.B	#$03,D4
  DEF_ROMLOC(DEC8) : and_toreg_16(0x18, &D4);              // ANDI.W	#$0018,D4
  DEF_ROMLOC(DECC) : add_toreg_16(0x8, &D4);               // ADDQ.W	#$08,D4
  DEF_ROMLOC(DECE) : sub_toreg_16(D4, &D0);                // SUB.W	D4,D0
  DEF_ROMLOC(DED0) : add_toreg_16(D2, &D0);                // ADD.W	D2,D0
  DEF_ROMLOC(DED2) : move_tomem_16(D0, (A2 += 2, A2 - 2)); // MOVE.W	D0,(A2)+
  DEF_ROMLOC(DED4) : move_toreg_8(read_8(A1++), &D4);      // MOVE.B	(A1)+,D4
  DEF_ROMLOC(DED6) : move_tomem_8(D4, A2++);               // MOVE.B	D4,(A2)+
  DEF_ROMLOC(DED8) : add_toreg_8(0x1, &D5);                // ADDQ.B	#$01,D5
  DEF_ROMLOC(DEDA) : move_tomem_8(D5, A2++);               // MOVE.B	D5,(A2)+
  DEF_ROMLOC(DEDC) : move_toreg_8(read_8(A1++), &D0);      // MOVE.B	(A1)+,D0
  DEF_ROMLOC(DEDE) : lsl_toreg_16(0x8, &D0);               // LSL.W	#$08,D0
  DEF_ROMLOC(DEE0) : move_toreg_8(read_8(A1++), &D0);      // MOVE.B	(A1)+,D0
  DEF_ROMLOC(DEE2) : add_toreg_16(A3, &D0);                // ADD.W	A3,D0
  DEF_ROMLOC(DEE4) : eor_toreg_16(0x1800, &D0);            // EORI.W	#$1800,D0
  DEF_ROMLOC(DEE8) : move_tomem_16(D0, (A2 += 2, A2 - 2)); // MOVE.W	D0,(A2)+
  DEF_ROMLOC(DEEA) : move_toreg_8(read_8(A1++), &D0);      // MOVE.B	(A1)+,D0
  DEF_ROMLOC(DEEC) : ext_reg_16(&D0);                      // EXT.W	D0
  DEF_ROMLOC(DEEE) : neg_reg_16(&D0);                      // NEG.W	D0
  DEF_ROMLOC(DEF0) : add_toreg_8(D4, &D4);                 // ADD.B	D4,D4
  DEF_ROMLOC(DEF2) : and_toreg_16(0x18, &D4);              // ANDI.W	#$0018,D4
  DEF_ROMLOC(DEF6) : add_toreg_16(0x8, &D4);               // ADDQ.W	#$08,D4
  DEF_ROMLOC(DEF8) : sub_toreg_16(D4, &D0);                // SUB.W	D4,D0
  DEF_ROMLOC(DEFA) : add_toreg_16(D3, &D0);                // ADD.W	D3,D0
  DEF_ROMLOC(DEFC) : and_toreg_16(0x1FF, &D0);             // ANDI.W	#$01FF,D0
  DEF_ROMLOC(DF00) : if (!CCR_EQ) goto rom_DF04;           // BNE.B	$DF04
  DEF_ROMLOC(DF02) : add_toreg_16(0x1, &D0);               // ADDQ.W	#$01,D0
  DEF_ROMLOC(DF04) : move_tomem_16(D0, (A2 += 2, A2 - 2)); // MOVE.W	D0,(A2)+
  DEF_ROMLOC(DF06) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_DEB8;           // DBF.W	D1,$DEB8
  DEF_ROMLOC(DF0A) : return; // RTS
}
ROMFUNC(rom_DC92) {
  DEF_ROMLOC(DC92) : move_toreg_32(0xFFFFAC00, &A1); // LEA.L	$AC00,A1
  DEF_ROMLOC(DC96)
      : move_toreg_16(read_16(A0 + 0x18), &D0);      // MOVE.W	24(A0),D0
  DEF_ROMLOC(DC9A) : lsr_toreg_16(0x1, &D0);         // LSR.W	#$01,D0
  DEF_ROMLOC(DC9C) : and_toreg_16(0x380, &D0);       // ANDI.W	#$0380,D0
  DEF_ROMLOC(DCA0) : add_toreg_16(D0, &A1);          // ADDA.W	D0,A1
  DEF_ROMLOC(DCA2) : cmp_tomem_16(0x7E, A1);         // CMPI.W	#$007E,(A1)
  DEF_ROMLOC(DCA6) : if (CCR_CC) goto rom_DCAE;      // BCC.B	$DCAE
  DEF_ROMLOC(DCA8) : add_tomem_16(0x2, A1);          // ADDQ.W	#$02,(A1)
  DEF_ROMLOC(DCAA) : add_toreg_16(read_16(A1), &A1); // ADDA.W	(A1),A1
  DEF_ROMLOC(DCAC) : move_tomem_16(A0, A1);          // MOVE.W	A0,(A1)
  DEF_ROMLOC(DCAE) : return;                         // RTS
}
ROMFUNC(rom_DCB0) {
  DEF_ROMLOC(DCB0) : move_toreg_32(0xFFFFAC00, &A2); // LEA.L	$AC00,A2
  DEF_ROMLOC(DCB4)
      : move_toreg_16(read_16(A1 + 0x18), &D0);      // MOVE.W	24(A1),D0
  DEF_ROMLOC(DCB8) : lsr_toreg_16(0x1, &D0);         // LSR.W	#$01,D0
  DEF_ROMLOC(DCBA) : and_toreg_16(0x380, &D0);       // ANDI.W	#$0380,D0
  DEF_ROMLOC(DCBE) : add_toreg_16(D0, &A2);          // ADDA.W	D0,A2
  DEF_ROMLOC(DCC0) : cmp_tomem_16(0x7E, A2);         // CMPI.W	#$007E,(A2)
  DEF_ROMLOC(DCC4) : if (CCR_CC) goto rom_DCCC;      // BCC.B	$DCCC
  DEF_ROMLOC(DCC6) : add_tomem_16(0x2, A2);          // ADDQ.W	#$02,(A2)
  DEF_ROMLOC(DCC8) : add_toreg_16(read_16(A2), &A2); // ADDA.W	(A2),A2
  DEF_ROMLOC(DCCA) : move_tomem_16(A1, A2);          // MOVE.W	A1,(A2)
  DEF_ROMLOC(DCCC) : return;                         // RTS
}