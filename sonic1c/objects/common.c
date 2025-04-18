// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_7ACA) {
  DEF_ROMLOC(7ACA) : move_toreg_32(0xFFFFD000, &A1); // LEA.L	$D000,A1
  DEF_ROMLOC(7ACE) : tst_mem_16(A1 + 0x12);          // TST.W	18(A1)
  DEF_ROMLOC(7AD2) : if (CCR_MI) return;             // BMI.W	$7B9C
  DEF_ROMLOC(7AD6)
      : move_toreg_16(read_16(A1 + 0x8), &D0);             // MOVE.W	8(A1),D0
  DEF_ROMLOC(7ADA) : sub_toreg_16(read_16(A0 + 0x8), &D0); // SUB.W	8(A0),D0
  DEF_ROMLOC(7ADE) : add_toreg_16(D1, &D0);                // ADD.W	D1,D0
  DEF_ROMLOC(7AE0) : if (CCR_MI) return;                   // BMI.W	$7B9C
  DEF_ROMLOC(7AE4) : add_toreg_16(D1, &D1);                // ADD.W	D1,D1
  DEF_ROMLOC(7AE6) : cmp_toreg_16(D1, &D0);                // CMP.W	D1,D0
  DEF_ROMLOC(7AE8) : if (CCR_CC) return;                   // BCC.W	$7B9C
  rom_7AEC();
}
ROMFUNC(rom_7AEC) {
  DEF_ROMLOC(7AEC)
      : move_toreg_16(read_16(A0 + 0xC), &D0); // MOVE.W	12(A0),D0
  DEF_ROMLOC(7AF0) : sub_toreg_16(0x8, &D0);   // SUBQ.W	#$08,D0
  rom_7AF2();
}
ROMFUNC(rom_7AF2) {
  DEF_ROMLOC(7AF2)
      : move_toreg_16(read_16(A1 + 0xC), &D2); // MOVE.W	12(A1),D2
  DEF_ROMLOC(7AF6)
      : move_toreg_8(read_8(A1 + 0x16), &D1);       // MOVE.B
                                                    // 22(A1),D1
  DEF_ROMLOC(7AFA) : ext_reg_16(&D1);               // EXT.W	D1
  DEF_ROMLOC(7AFC) : add_toreg_16(D2, &D1);         // ADD.W	D2,D1
  DEF_ROMLOC(7AFE) : add_toreg_16(0x4, &D1);        // ADDQ.W	#$04,D1
  DEF_ROMLOC(7B00) : sub_toreg_16(D1, &D0);         // SUB.W	D1,D0
  DEF_ROMLOC(7B02) : if (CCR_HI) return;            // BHI.W	$7B9C
  DEF_ROMLOC(7B06) : cmp_toreg_16(0xFFFFFFF0, &D0); // CMPI.W	#$FFF0,D0
  DEF_ROMLOC(7B0A) : if (CCR_CS) return;            // BCS.W	$7B9C
  DEF_ROMLOC(7B0E) : tst_mem_8(0xFFFFF7C8);         // TST.B	$F7C8
  DEF_ROMLOC(7B12) : if (CCR_MI) return;            // BMI.W	$7B9C
  DEF_ROMLOC(7B16) : cmp_tomem_8(0x6, A1 + 0x24);   // CMPI.B	#$06,36(A1)
  DEF_ROMLOC(7B1C) : if (CCR_CC) return;            // BCC.W	$7B9C
  DEF_ROMLOC(7B20) : add_toreg_16(D0, &D2);         // ADD.W	D0,D2
  DEF_ROMLOC(7B22) : add_toreg_16(0x3, &D2);        // ADDQ.W	#$03,D2
  DEF_ROMLOC(7B24) : move_tomem_16(D2, A1 + 0xC);   // MOVE.W	D2,12(A1)
  DEF_ROMLOC(7B28) : add_tomem_8(0x2, A0 + 0x24);   // ADDQ.B	#$02,36(A0)
  rom_7B2C();
}
ROMFUNC(rom_7B2C) {
  DEF_ROMLOC(7B2C) : btst_tomem_8(0x3, A1 + 0x22); // BTST.B	#$03,34(A1)
  DEF_ROMLOC(7B32) : if (CCR_EQ) goto rom_7B5A;    // BEQ.B	$7B5A
  DEF_ROMLOC(7B34) : move_toreg_32(0x0, &D0);      // MOVEQ.L	$00,D0
  DEF_ROMLOC(7B36)
      : move_toreg_8(read_8(A1 + 0x3D), &D0);       // MOVE.B
                                                    // 61(A1),D0
  DEF_ROMLOC(7B3A) : lsl_toreg_16(0x6, &D0);        // LSL.W	#$06,D0
  DEF_ROMLOC(7B3C) : add_toreg_32(0xFFD000, &D0);   // ADDI.L	#$00FFD000,D0
  DEF_ROMLOC(7B42) : move_toreg_32(D0, &A2);        // MOVEA.L	D0,A2
  DEF_ROMLOC(7B44) : bclr_tomem_8(0x3, A2 + 0x22);  // BCLR.B	#$03,34(A2)
  DEF_ROMLOC(7B4A) : clr_mem_8(A2 + 0x25);          // CLR.B	37(A2)
  DEF_ROMLOC(7B4E) : cmp_tomem_8(0x4, A2 + 0x24);   // CMPI.B	#$04,36(A2)
  DEF_ROMLOC(7B54) : if (!CCR_EQ) goto rom_7B5A;    // BNE.B	$7B5A
  DEF_ROMLOC(7B56) : sub_tomem_8(0x2, A2 + 0x24);   // SUBQ.B	#$02,36(A2)
  DEF_ROMLOC(7B5A) : move_toreg_16(A0, &D0);        // MOVE.W	A0,D0
  DEF_ROMLOC(7B5C) : sub_toreg_16(0xFFFFD000, &D0); // SUBI.W	#$D000,D0
  DEF_ROMLOC(7B60) : lsr_toreg_16(0x6, &D0);        // LSR.W	#$06,D0
  DEF_ROMLOC(7B62) : and_toreg_16(0x7F, &D0);       // ANDI.W	#$007F,D0
  DEF_ROMLOC(7B66) : move_tomem_8(D0, A1 + 0x3D);   // MOVE.B	D0,61(A1)
  DEF_ROMLOC(7B6A) : move_tomem_8(0x0, A1 + 0x26);  // MOVE.B	#$00,38(A1)
  DEF_ROMLOC(7B70) : move_tomem_16(0x0, A1 + 0x12); // MOVE.W	#$0000,18(A1)
  DEF_ROMLOC(7B76)
      : move_tomem_16(read_16(A1 + 0x10), A1 + 0x14); // MOVE.W	16(A1),20(A1)
  DEF_ROMLOC(7B7C) : btst_tomem_8(0x1, A1 + 0x22);    // BTST.B	#$01,34(A1)
  DEF_ROMLOC(7B82) : if (CCR_EQ) goto rom_7B90;       // BEQ.B	$7B90
  DEF_ROMLOC(7B84) : move_tomem_32(A0, A7 -= 4);      // MOVE.L	A0,-(A7)
  DEF_ROMLOC(7B86) : move_toreg_32(A1, &A0);          // MOVEA.L	A1,A0
  DEF_ROMLOC(7B88) : rom_13E74();                     // JSR	$00013E74
  DEF_ROMLOC(7B8E)
      : move_toreg_32(read_32((A7 += 4, A7 - 4)), &A0); // MOVEA.L	(A7)+,A0
  DEF_ROMLOC(7B90) : bset_tomem_8(0x3, A1 + 0x22);      // BSET.B	#$03,34(A1)
  DEF_ROMLOC(7B96) : bset_tomem_8(0x3, A0 + 0x22);      // BSET.B	#$03,34(A0)
  DEF_ROMLOC(7B9C) : return;                            // RTS
}
ROMFUNC(rom_7B9E) {
  DEF_ROMLOC(7B9E) : move_toreg_32(0xFFFFD000, &A1); // LEA.L	$D000,A1
  DEF_ROMLOC(7BA2) : tst_mem_16(A1 + 0x12);          // TST.W	18(A1)
  DEF_ROMLOC(7BA6) : if (CCR_MI) return;             // BMI.W	$7B9C
  DEF_ROMLOC(7BAA)
      : move_toreg_16(read_16(A1 + 0x8), &D0); // MOVE.W	8(A1),D0
  DEF_ROMLOC(7BAE)
      : sub_toreg_16(read_16(A0 + 0x8), &D0);     // SUB.W	8(A0),D0
  DEF_ROMLOC(7BB2) : add_toreg_16(D1, &D0);       // ADD.W	D1,D0
  DEF_ROMLOC(7BB4) : if (CCR_MI) return;          // BMI.B	$7B9C
  DEF_ROMLOC(7BB6) : add_toreg_16(D1, &D1);       // ADD.W	D1,D1
  DEF_ROMLOC(7BB8) : cmp_toreg_16(D1, &D0);       // CMP.W	D1,D0
  DEF_ROMLOC(7BBA) : if (CCR_CC) return;          // BCC.B	$7B9C
  DEF_ROMLOC(7BBC) : btst_tomem_8(0x0, A0 + 0x1); // BTST.B	#$00,1(A0)
  DEF_ROMLOC(7BC2) : if (CCR_EQ) goto rom_7BC8;   // BEQ.B	$7BC8
  DEF_ROMLOC(7BC4) : not_reg_16(&D0);             // NOT.W	D0
  DEF_ROMLOC(7BC6) : add_toreg_16(D1, &D0);       // ADD.W	D1,D0
  DEF_ROMLOC(7BC8) : lsr_toreg_16(0x1, &D0);      // LSR.W	#$01,D0
  DEF_ROMLOC(7BCA) : move_toreg_32(0x0, &D3);     // MOVEQ.L	$00,D3
  DEF_ROMLOC(7BCC)
      : move_toreg_8(read_8((s32)A2 + (s8)0x0 + (s16)D0),
                     &D3); // MOVE.B	0(A2,D0),D3
  DEF_ROMLOC(7BD0)
      : move_toreg_16(read_16(A0 + 0xC), &D0); // MOVE.W	12(A0),D0
  DEF_ROMLOC(7BD4) : sub_toreg_16(D3, &D0);    // SUB.W	D3,D0
  rom_7AF2();                                  // BRA.W	$7AF2
}
ROMFUNC(rom_7C10) {
  DEF_ROMLOC(7C10) : move_toreg_32(0x0, &D1); // MOVEQ.L	$00,D1
  DEF_ROMLOC(7C12)
      : move_toreg_8(read_8(A0 + 0x28), &D1);     // MOVE.B	40(A0),D1
  DEF_ROMLOC(7C16) : lsl_toreg_16(0x3, &D1);      // LSL.W	#$03,D1
  DEF_ROMLOC(7C18) : move_toreg_16(D1, &D2);      // MOVE.W	D1,D2
  DEF_ROMLOC(7C1A) : add_toreg_16(0x8, &D1);      // ADDQ.W	#$08,D1
  DEF_ROMLOC(7C1C) : rom_7C40();                  // BSR.B	$7C40
  DEF_ROMLOC(7C1E) : if (CCR_CC) goto rom_7C3C;   // BCC.B	$7C3C
  DEF_ROMLOC(7C20) : lsr_toreg_16(0x4, &D0);      // LSR.W	#$04,D0
  DEF_ROMLOC(7C22) : move_tomem_8(D0, A0 + 0x3F); // MOVE.B	D0,63(A0)
  DEF_ROMLOC(7C26)
      : move_toreg_8(read_8(A0 + 0x3E), &D0);     // MOVE.B	62(A0),D0
  DEF_ROMLOC(7C2A) : cmp_toreg_8(0x40, &D0);      // CMPI.B	#$40,D0
  DEF_ROMLOC(7C2E) : if (CCR_EQ) goto rom_7C34;   // BEQ.B	$7C34
  DEF_ROMLOC(7C30) : add_tomem_8(0x4, A0 + 0x3E); // ADDQ.B	#$04,62(A0)
  DEF_ROMLOC(7C34) : rom_7C9E();                  // BSR.W	$7C9E
  DEF_ROMLOC(7C38) : rom_7C72();                  // BSR.W	$7C72
  DEF_ROMLOC(7C3C) : return;                      // RTS
}
ROMFUNC(rom_7C3E) {
  DEF_ROMLOC(7C3E) : move_toreg_16(D1, &D2); // MOVE.W	D1,D2
  rom_7C40();                                // Detected flow into next function
}
ROMFUNC(rom_7C40) {
  DEF_ROMLOC(7C40) : add_toreg_16(D2, &D2);          // ADD.W	D2,D2
  DEF_ROMLOC(7C42) : move_toreg_32(0xFFFFD000, &A1); // LEA.L	$D000,A1
  DEF_ROMLOC(7C46) : btst_tomem_8(0x1, A1 + 0x22);   // BTST.B	#$01,34(A1)
  DEF_ROMLOC(7C4C) : if (!CCR_EQ) goto rom_7C5E;     // BNE.B	$7C5E
  DEF_ROMLOC(7C4E)
      : move_toreg_16(read_16(A1 + 0x8), &D0);             // MOVE.W	8(A1),D0
  DEF_ROMLOC(7C52) : sub_toreg_16(read_16(A0 + 0x8), &D0); // SUB.W	8(A0),D0
  DEF_ROMLOC(7C56) : add_toreg_16(D1, &D0);                // ADD.W	D1,D0
  DEF_ROMLOC(7C58) : if (CCR_MI) goto rom_7C5E;            // BMI.B	$7C5E
  DEF_ROMLOC(7C5A) : cmp_toreg_16(D2, &D0);                // CMP.W	D2,D0
  DEF_ROMLOC(7C5C) : if (CCR_CS) goto rom_7C70;            // BCS.B	$7C70
  DEF_ROMLOC(7C5E) : bclr_tomem_8(0x3, A1 + 0x22);         // BCLR.B	#$03,34(A1)
  DEF_ROMLOC(7C64) : move_tomem_8(0x2, A0 + 0x24);         // MOVE.B	#$02,36(A0)
  DEF_ROMLOC(7C6A) : bclr_tomem_8(0x3, A0 + 0x22);         // BCLR.B	#$03,34(A0)
  DEF_ROMLOC(7C70) : return;                               // RTS
}
ROMFUNC(rom_7C72) {
  DEF_ROMLOC(7C72) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(7C74)
      : move_toreg_8(read_8(A0 + 0x3F), &D0); // MOVE.B
                                              // 63(A0),D0
  DEF_ROMLOC(7C78)
      : move_toreg_8(read_8((s32)A0 + (s8)0x29 + (s16)D0),
                     &D0);                           // MOVE.B	41(A0,D0),D0
  DEF_ROMLOC(7C7C) : lsl_toreg_16(0x6, &D0);         // LSL.W	#$06,D0
  DEF_ROMLOC(7C7E) : add_toreg_32(0xFFD000, &D0);    // ADDI.L	#$00FFD000,D0
  DEF_ROMLOC(7C84) : move_toreg_32(D0, &A2);         // MOVEA.L	D0,A2
  DEF_ROMLOC(7C86) : move_toreg_32(0xFFFFD000, &A1); // LEA.L	$D000,A1
  DEF_ROMLOC(7C8A)
      : move_toreg_16(read_16(A2 + 0xC), &D0); // MOVE.W	12(A2),D0
  DEF_ROMLOC(7C8E) : sub_toreg_16(0x8, &D0);   // SUBQ.W	#$08,D0
  DEF_ROMLOC(7C90) : move_toreg_32(0x0, &D1);  // MOVEQ.L	$00,D1
  DEF_ROMLOC(7C92)
      : move_toreg_8(read_8(A1 + 0x16), &D1);     // MOVE.B	22(A1),D1
  DEF_ROMLOC(7C96) : sub_toreg_16(D1, &D0);       // SUB.W	D1,D0
  DEF_ROMLOC(7C98) : move_tomem_16(D0, A1 + 0xC); // MOVE.W	D0,12(A1)
  DEF_ROMLOC(7C9C) : return;                      // RTS
}
ROMFUNC(rom_7C9E) {
  DEF_ROMLOC(7C9E)
      : move_toreg_8(read_8(A0 + 0x3E), &D0);    // MOVE.B	62(A0),D0
  DEF_ROMLOC(7CA2) : rom_29D2();                 // BSR.W	$29D2
  DEF_ROMLOC(7CA6) : move_toreg_16(D0, &D4);     // MOVE.W	D0,D4
  DEF_ROMLOC(7CA8) : move_toreg_32(0x7E5A, &A4); // LEA.L	$00007E5A,A4
  DEF_ROMLOC(7CAE) : move_toreg_32(0x0, &D0);    // MOVEQ.L	$00,D0
  DEF_ROMLOC(7CB0)
      : move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B
                                              // 40(A0),D0
  DEF_ROMLOC(7CB4) : lsl_toreg_16(0x4, &D0);  // LSL.W	#$04,D0
  DEF_ROMLOC(7CB6) : move_toreg_32(0x0, &D3); // MOVEQ.L	$00,D3
  DEF_ROMLOC(7CB8)
      : move_toreg_8(read_8(A0 + 0x3F), &D3);    // MOVE.B	63(A0),D3
  DEF_ROMLOC(7CBC) : move_toreg_16(D3, &D2);     // MOVE.W	D3,D2
  DEF_ROMLOC(7CBE) : add_toreg_16(D0, &D3);      // ADD.W	D0,D3
  DEF_ROMLOC(7CC0) : move_toreg_32(0x0, &D5);    // MOVEQ.L	$00,D5
  DEF_ROMLOC(7CC2) : move_toreg_32(0x7D4A, &A5); // LEA.L	$00007D4A,A5
  DEF_ROMLOC(7CC8)
      : move_toreg_8(read_8((s32)A5 + (s8)0x0 + (s16)D3),
                     &D5);                   // MOVE.B	0(A5,D3),D5
  DEF_ROMLOC(7CCC) : and_toreg_16(0xF, &D3); // ANDI.W	#$000F,D3
  DEF_ROMLOC(7CD0) : lsl_toreg_16(0x4, &D3); // LSL.W	#$04,D3
  DEF_ROMLOC(7CD2)
      : move_toreg_32((s32)A4 + (s8)0x0 + (s16)D3,
                      &A3);                         // LEA.L	0(A4,D3),A3
  DEF_ROMLOC(7CD6) : move_toreg_32(A0 + 0x29, &A2); // LEA.L	41(A0),A2
  rom_7CDA(); // Detected flow into next function
}
ROMFUNC(rom_7CDA) {
  DEF_ROMLOC(7CDA) : move_toreg_32(0x0, &D0);         // MOVEQ.L	$00,D0
  DEF_ROMLOC(7CDC) : move_toreg_8(read_8(A2++), &D0); // MOVE.B	(A2)+,D0
  DEF_ROMLOC(7CDE) : lsl_toreg_16(0x6, &D0);          // LSL.W	#$06,D0
  DEF_ROMLOC(7CE0) : add_toreg_32(0xFFD000, &D0);     // ADDI.L	#$00FFD000,D0
  DEF_ROMLOC(7CE6) : move_toreg_32(D0, &A1);          // MOVEA.L	D0,A1
  DEF_ROMLOC(7CE8) : move_toreg_32(0x0, &D0);         // MOVEQ.L	$00,D0
  DEF_ROMLOC(7CEA) : move_toreg_8(read_8(A3++), &D0); // MOVE.B	(A3)+,D0
  DEF_ROMLOC(7CEC) : add_toreg_16(0x1, &D0);          // ADDQ.W	#$01,D0
  DEF_ROMLOC(7CEE) : mulu_toreg_16(D5, &D0);          // MULU.W	D5,D0
  DEF_ROMLOC(7CF0) : mulu_toreg_16(D4, &D0);          // MULU.W	D4,D0
  DEF_ROMLOC(7CF2) : SWAPWORDS(D0);                   // SWAP.W	D0
  DEF_ROMLOC(7CF4)
      : add_toreg_16(read_16(A1 + 0x3C), &D0);    // ADD.W	60(A1),D0
  DEF_ROMLOC(7CF8) : move_tomem_16(D0, A1 + 0xC); // MOVE.W	D0,12(A1)
  DEF_ROMLOC(7CFC) : dec_reg_16(&D2);
  if ((D2 & 0xffff) != 0xffff)
    goto rom_7CDA;                            // DBF.W	D2,$7CDA
  DEF_ROMLOC(7D00) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(7D02)
      : move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B
                                              // 40(A0),D0
  DEF_ROMLOC(7D06) : move_toreg_32(0x0, &D3); // MOVEQ.L	$00,D3
  DEF_ROMLOC(7D08)
      : move_toreg_8(read_8(A0 + 0x3F), &D3);   // MOVE.B	63(A0),D3
  DEF_ROMLOC(7D0C) : add_toreg_8(0x1, &D3);     // ADDQ.B	#$01,D3
  DEF_ROMLOC(7D0E) : sub_toreg_8(D0, &D3);      // SUB.B	D0,D3
  DEF_ROMLOC(7D10) : neg_reg_8(&D3);            // NEG.B	D3
  DEF_ROMLOC(7D12) : if (CCR_MI) goto rom_7D48; // BMI.B	$7D48
  DEF_ROMLOC(7D14) : move_toreg_16(D3, &D2);    // MOVE.W	D3,D2
  DEF_ROMLOC(7D16) : lsl_toreg_16(0x4, &D3);    // LSL.W	#$04,D3
  DEF_ROMLOC(7D18)
      : move_toreg_32((s32)A4 + (s8)0x0 + (s16)D3,
                      &A3);                           // LEA.L	0(A4,D3),A3
  DEF_ROMLOC(7D1C) : add_toreg_16(D2, &A3);           // ADDA.W	D2,A3
  DEF_ROMLOC(7D1E) : sub_toreg_16(0x1, &D2);          // SUBQ.W	#$01,D2
  DEF_ROMLOC(7D20) : if (CCR_CS) goto rom_7D48;       // BCS.B	$7D48
  DEF_ROMLOC(7D22) : move_toreg_32(0x0, &D0);         // MOVEQ.L	$00,D0
  DEF_ROMLOC(7D24) : move_toreg_8(read_8(A2++), &D0); // MOVE.B	(A2)+,D0
  DEF_ROMLOC(7D26) : lsl_toreg_16(0x6, &D0);          // LSL.W	#$06,D0
  DEF_ROMLOC(7D28) : add_toreg_32(0xFFD000, &D0);     // ADDI.L	#$00FFD000,D0
  DEF_ROMLOC(7D2E) : move_toreg_32(D0, &A1);          // MOVEA.L	D0,A1
  DEF_ROMLOC(7D30) : move_toreg_32(0x0, &D0);         // MOVEQ.L	$00,D0
  DEF_ROMLOC(7D32) : move_toreg_8(read_8(--A3), &D0); // MOVE.B	-(A3),D0
  DEF_ROMLOC(7D34) : add_toreg_16(0x1, &D0);          // ADDQ.W	#$01,D0
  DEF_ROMLOC(7D36) : mulu_toreg_16(D5, &D0);          // MULU.W	D5,D0
  DEF_ROMLOC(7D38) : mulu_toreg_16(D4, &D0);          // MULU.W	D4,D0
  DEF_ROMLOC(7D3A) : SWAPWORDS(D0);                   // SWAP.W	D0
  DEF_ROMLOC(7D3C)
      : add_toreg_16(read_16(A1 + 0x3C), &D0);    // ADD.W	60(A1),D0
  DEF_ROMLOC(7D40) : move_tomem_16(D0, A1 + 0xC); // MOVE.W	D0,12(A1)
  DEF_ROMLOC(7D44) : dec_reg_16(&D2);
  if ((D2 & 0xffff) != 0xffff)
    goto rom_7D22;           // DBF.W	D2,$7D22
  DEF_ROMLOC(7D48) : return; // RTS
}
ROMFUNC(rom_7BDA) {
  DEF_ROMLOC(7BDA) : move_toreg_32(0xFFFFD000, &A1); // LEA.L	$D000,A1
  DEF_ROMLOC(7BDE) : tst_mem_16(A1 + 0x12);          // TST.W	18(A1)
  DEF_ROMLOC(7BE2) : if (CCR_MI) return;             // BMI.W	$7B9C
  DEF_ROMLOC(7BE6)
      : move_toreg_16(read_16(A1 + 0x8), &D0);             // MOVE.W	8(A1),D0
  DEF_ROMLOC(7BEA) : sub_toreg_16(read_16(A0 + 0x8), &D0); // SUB.W	8(A0),D0
  DEF_ROMLOC(7BEE) : add_toreg_16(D1, &D0);                // ADD.W	D1,D0
  DEF_ROMLOC(7BF0) : if (CCR_MI) return;                   // BMI.W	$7B9C
  DEF_ROMLOC(7BF4) : add_toreg_16(D1, &D1);                // ADD.W	D1,D1
  DEF_ROMLOC(7BF6) : cmp_toreg_16(D1, &D0);                // CMP.W	D1,D0
  DEF_ROMLOC(7BF8) : if (CCR_CC) return;                   // BCC.W	$7B9C
  DEF_ROMLOC(7BFC)
      : move_toreg_16(read_16(A0 + 0xC), &D0); // MOVE.W	12(A0),D0
  DEF_ROMLOC(7C00) : sub_toreg_16(D3, &D0);    // SUB.W	D3,D0
  rom_7AF2();                                  // BRA.W	$7AF2
}
ROMFUNC(rom_DC40) {
  DEF_ROMLOC(DC40)
      : move_toreg_32(read_32(A0 + 0x8), &D2); // MOVE.L	8(A0),D2
  DEF_ROMLOC(DC44)
      : move_toreg_32(read_32(A0 + 0xC), &D3); // MOVE.L	12(A0),D3
  DEF_ROMLOC(DC48)
      : move_toreg_16(read_16(A0 + 0x10), &D0); // MOVE.W	16(A0),D0
  DEF_ROMLOC(DC4C) : ext_reg_32(&D0);           // EXT.L	D0
  DEF_ROMLOC(DC4E) : asl_toreg_32(0x8, &D0);    // ASL.L	#$08,D0
  DEF_ROMLOC(DC50) : add_toreg_32(D0, &D2);     // ADD.L	D0,D2
  DEF_ROMLOC(DC52)
      : move_toreg_16(read_16(A0 + 0x12), &D0);     // MOVE.W	18(A0),D0
  DEF_ROMLOC(DC56) : add_tomem_16(0x38, A0 + 0x12); // ADDI.W	#$0038,18(A0)
  DEF_ROMLOC(DC5C) : ext_reg_32(&D0);               // EXT.L	D0
  DEF_ROMLOC(DC5E) : asl_toreg_32(0x8, &D0);        // ASL.L	#$08,D0
  DEF_ROMLOC(DC60) : add_toreg_32(D0, &D3);         // ADD.L	D0,D3
  DEF_ROMLOC(DC62) : move_tomem_32(D2, A0 + 0x8);   // MOVE.L	D2,8(A0)
  DEF_ROMLOC(DC66) : move_tomem_32(D3, A0 + 0xC);   // MOVE.L	D3,12(A0)
  DEF_ROMLOC(DC6A) : return;                        // RTS
}
ROMFUNC(rom_DC6C) {
  DEF_ROMLOC(DC6C)
      : move_toreg_32(read_32(A0 + 0x8), &D2); // MOVE.L	8(A0),D2
  DEF_ROMLOC(DC70)
      : move_toreg_32(read_32(A0 + 0xC), &D3); // MOVE.L	12(A0),D3
  DEF_ROMLOC(DC74)
      : move_toreg_16(read_16(A0 + 0x10), &D0); // MOVE.W	16(A0),D0
  DEF_ROMLOC(DC78) : ext_reg_32(&D0);           // EXT.L	D0
  DEF_ROMLOC(DC7A) : asl_toreg_32(0x8, &D0);    // ASL.L	#$08,D0
  DEF_ROMLOC(DC7C) : add_toreg_32(D0, &D2);     // ADD.L	D0,D2
  DEF_ROMLOC(DC7E)
      : move_toreg_16(read_16(A0 + 0x12), &D0);   // MOVE.W
                                                  // 18(A0),D0
  DEF_ROMLOC(DC82) : ext_reg_32(&D0);             // EXT.L	D0
  DEF_ROMLOC(DC84) : asl_toreg_32(0x8, &D0);      // ASL.L	#$08,D0
  DEF_ROMLOC(DC86) : add_toreg_32(D0, &D3);       // ADD.L	D0,D3
  DEF_ROMLOC(DC88) : move_tomem_32(D2, A0 + 0x8); // MOVE.L	D2,8(A0)
  DEF_ROMLOC(DC8C) : move_tomem_32(D3, A0 + 0xC); // MOVE.L	D3,12(A0)
  DEF_ROMLOC(DC90) : return;                      // RTS
}
ROMFUNC(rom_DCCE) {
  DEF_ROMLOC(DCCE) : move_toreg_32(A0, &A1); // MOVEA.L	A0,A1
  rom_DCD0();                                // Detected flow into next function
}
ROMFUNC(rom_DCD0) {
  DEF_ROMLOC(DCD0) : move_toreg_32(0x0, &D1); // MOVEQ.L	$00,D1
  DEF_ROMLOC(DCD2) : move_toreg_32(0xF, &D0); // MOVEQ.L	$0F,D0
  rom_DCD4(); // Detected flow into next function
}
ROMFUNC(rom_DCD4) {
  DEF_ROMLOC(DCD4) : move_tomem_32(D1, (A1 += 4, A1 - 4)); // MOVE.L	D1,(A1)+
  DEF_ROMLOC(DCD6) : dec_reg_16(&D0);
  if ((D0 & 0xffff) != 0xffff)
    goto rom_DCD4;           // DBF.W	D0,$DCD4
  DEF_ROMLOC(DCDA) : return; // RTS
}
ROMFUNC(rom_DF0C) {
  DEF_ROMLOC(DF0C)
      : move_toreg_16(read_16(A0 + 0x8), &D0); // MOVE.W	8(A0),D0
  DEF_ROMLOC(DF10)
      : sub_toreg_16(read_16(v_screenposx), &D0);   // SUB.W	$F700,D0
  DEF_ROMLOC(DF14) : if (CCR_MI) goto rom_DF30;     // BMI.B	$DF30
  DEF_ROMLOC(DF16) : cmp_toreg_16(GAME_WIDTH, &D0); // CMPI.W	#$0140,D0
  DEF_ROMLOC(DF1A) : if (CCR_GE) goto rom_DF30;     // BGE.B	$DF30
  DEF_ROMLOC(DF1C)
      : move_toreg_16(read_16(A0 + 0xC), &D1); // MOVE.W	12(A0),D1
  DEF_ROMLOC(DF20)
      : sub_toreg_16(read_16(0xFFFFF704), &D1); // SUB.W	$F704,D1
  DEF_ROMLOC(DF24) : if (CCR_MI) goto rom_DF30; // BMI.B	$DF30
  DEF_ROMLOC(DF26) : cmp_toreg_16(0xE0, &D1);   // CMPI.W	#$00E0,D1
  DEF_ROMLOC(DF2A) : if (CCR_GE) goto rom_DF30; // BGE.B	$DF30
  DEF_ROMLOC(DF2C) : move_toreg_32(0x0, &D0);   // MOVEQ.L	$00,D0
  DEF_ROMLOC(DF2E) : return;                    // RTS
  DEF_ROMLOC(DF30) : move_toreg_32(0x1, &D0);   // MOVEQ.L	$01,D0
  DEF_ROMLOC(DF32) : return;                    // RTS
}
ROMFUNC(rom_DF34) {
  DEF_ROMLOC(DF34) : move_toreg_32(0x0, &D1); // MOVEQ.L	$00,D1
  DEF_ROMLOC(DF36)
      : move_toreg_8(read_8(A0 + 0x19), &D1); // MOVE.B
                                              // 25(A0),D1
  DEF_ROMLOC(DF3A)
      : move_toreg_16(read_16(A0 + 0x8), &D0); // MOVE.W	8(A0),D0
  DEF_ROMLOC(DF3E)
      : sub_toreg_16(read_16(v_screenposx), &D0);   // SUB.W	$F700,D0
  DEF_ROMLOC(DF42) : add_toreg_16(D1, &D0);         // ADD.W	D1,D0
  DEF_ROMLOC(DF44) : if (CCR_MI) goto rom_DF64;     // BMI.B	$DF64
  DEF_ROMLOC(DF46) : add_toreg_16(D1, &D1);         // ADD.W	D1,D1
  DEF_ROMLOC(DF48) : sub_toreg_16(D1, &D0);         // SUB.W	D1,D0
  DEF_ROMLOC(DF4A) : cmp_toreg_16(GAME_WIDTH, &D0); // CMPI.W	#$0140,D0
  DEF_ROMLOC(DF4E) : if (CCR_GE) goto rom_DF64;     // BGE.B	$DF64
  DEF_ROMLOC(DF50)
      : move_toreg_16(read_16(A0 + 0xC), &D1); // MOVE.W	12(A0),D1
  DEF_ROMLOC(DF54)
      : sub_toreg_16(read_16(0xFFFFF704), &D1); // SUB.W	$F704,D1
  DEF_ROMLOC(DF58) : if (CCR_MI) goto rom_DF64; // BMI.B	$DF64
  DEF_ROMLOC(DF5A) : cmp_toreg_16(0xE0, &D1);   // CMPI.W	#$00E0,D1
  DEF_ROMLOC(DF5E) : if (CCR_GE) goto rom_DF64; // BGE.B	$DF64
  DEF_ROMLOC(DF60) : move_toreg_32(0x0, &D0);   // MOVEQ.L	$00,D0
  DEF_ROMLOC(DF62) : return;                    // RTS
  DEF_ROMLOC(DF64) : move_toreg_32(0x1, &D0);   // MOVEQ.L	$01,D0
  DEF_ROMLOC(DF66) : return;                    // RTS
}
ROMFUNC(rom_DF68) {
  u8 switchindex = 0;
  DEF_ROMLOC(DF68) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(DF6A) : move_toreg_8(read_8(0xFFFFF76C), &D0);
  switchindex = D0 / 2; // MOVE.B	$F76C,D0
  DEF_ROMLOC(DF6E)
      : move_toreg_16(read_16(0xDF76 + (s16)(D0 & 0xffff)),
                      &D0); // MOVE.W	6(PC,D0),D0
  // DEF_ROMLOC(DF72): goto rom_DF76 + (s16)(D0 & 0xffff); // JMP	2(PC,D0)
  DEF_ROMLOC(DF72) : switch (switchindex) {
  case 0:
    rom_DF7A();
    break;
  case 1:
    rom_E00E();
    break;
  }
}
ROMFUNC(rom_DF7A) {
  DEF_ROMLOC(DF7A) : add_tomem_8(0x2, 0xFFFFF76C);        // ADDQ.B	#$02,$F76C
  DEF_ROMLOC(DF7E) : move_toreg_16(read_16(v_zone), &D0); // MOVE.W	$FE10,D0
  DEF_ROMLOC(DF82) : lsl_toreg_8(0x6, &D0);               // LSL.B	#$06,D0
  DEF_ROMLOC(DF84) : lsr_toreg_16(0x4, &D0);              // LSR.W	#$04,D0
  DEF_ROMLOC(DF86) : move_toreg_32(0x6B000, &A0);         // LEA.L	$0006B000,A0
  DEF_ROMLOC(DF8C) : move_toreg_32(A0, &A1);              // MOVEA.L	A0,A1
  DEF_ROMLOC(DF8E)
      : add_toreg_16(read_16((s32)A0 + (s8)0x0 + (s16)D0),
                     &A0);                          // ADDA.W	0(A0,D0),A0
  DEF_ROMLOC(DF92) : move_tomem_32(A0, 0xFFFFF770); // MOVE.L	A0,$F770
  DEF_ROMLOC(DF96) : move_tomem_32(A0, 0xFFFFF774); // MOVE.L	A0,$F774
  DEF_ROMLOC(DF9A)
      : add_toreg_16(read_16((s32)A1 + (s8)0x2 + (s16)D0),
                     &A1);                           // ADDA.W	2(A1,D0),A1
  DEF_ROMLOC(DF9E) : move_tomem_32(A1, 0xFFFFF778);  // MOVE.L	A1,$F778
  DEF_ROMLOC(DFA2) : move_tomem_32(A1, 0xFFFFF77C);  // MOVE.L	A1,$F77C
  DEF_ROMLOC(DFA6) : move_toreg_32(0xFFFFFC00, &A2); // LEA.L	$FC00,A2
  DEF_ROMLOC(DFAA)
      : move_tomem_16(0x101, (A2 += 2, A2 - 2)); // MOVE.W	#$0101,(A2)+
  DEF_ROMLOC(DFAE) : move_toreg_16(0x5E, &D0);   // MOVE.W	#$005E,D0
  rom_DFB2(); // Detected flow into next function
}
ROMFUNC(rom_DFB2) {
  DEF_ROMLOC(DFB2) : clr_mem_32((A2 += 4, A2 - 4)); // CLR.L	(A2)+
  DEF_ROMLOC(DFB4) : dec_reg_16(&D0);
  if ((D0 & 0xffff) != 0xffff)
    goto rom_DFB2;                                   // DBF.W	D0,$DFB2
  DEF_ROMLOC(DFB8) : move_toreg_32(0xFFFFFC00, &A2); // LEA.L	$FC00,A2
  DEF_ROMLOC(DFBC) : move_toreg_32(0x0, &D2);        // MOVEQ.L	$00,D2
  DEF_ROMLOC(DFBE)
      : move_toreg_16(read_16(v_screenposx), &D6);  // MOVE.W	$F700,D6
  DEF_ROMLOC(DFC2) : sub_toreg_16(0x80, &D6);       // SUBI.W	#$0080,D6
  DEF_ROMLOC(DFC6) : if (CCR_CC) goto rom_DFCA;     // BCC.B	$DFCA
  DEF_ROMLOC(DFC8) : move_toreg_32(0x0, &D6);       // MOVEQ.L	$00,D6
  DEF_ROMLOC(DFCA) : and_toreg_16(0xFFFFFF80, &D6); // ANDI.W	#$FF80,D6
  DEF_ROMLOC(DFCE)
      : move_toreg_32(read_32(0xFFFFF770), &A0); // MOVEA.L	$F770,A0
  rom_DFD2(); // Detected flow into next function
}
ROMFUNC(rom_DFD2) {
  DEF_ROMLOC(DFD2) : cmp_toreg_16(read_16(A0), &D6); // CMP.W	(A0),D6
  DEF_ROMLOC(DFD4) : if (CCR_LS) goto rom_DFE4;      // BLS.B	$DFE4
  DEF_ROMLOC(DFD6) : tst_mem_8(A0 + 0x4);            // TST.B	4(A0)
  DEF_ROMLOC(DFDA) : if (CCR_PL) goto rom_DFE0;      // BPL.B	$DFE0
  DEF_ROMLOC(DFDC) : move_toreg_8(read_8(A2), &D2);  // MOVE.B	(A2),D2
  DEF_ROMLOC(DFDE) : add_tomem_8(0x1, A2);           // ADDQ.B	#$01,(A2)
  DEF_ROMLOC(DFE0) : add_toreg_16(0x6, &A0);         // ADDQ.W	#$06,A0
  rom_DFD2();
  return;                                           // BRA.B	$DFD2
  DEF_ROMLOC(DFE4) : move_tomem_32(A0, 0xFFFFF770); // MOVE.L	A0,$F770
  DEF_ROMLOC(DFE8)
      : move_toreg_32(read_32(0xFFFFF774), &A0);     // MOVEA.L	$F774,A0
  DEF_ROMLOC(DFEC) : sub_toreg_16(0x80, &D6);        // SUBI.W	#$0080,D6
  DEF_ROMLOC(DFF0) : if (CCR_CS) goto rom_E004;      // BCS.B	$E004
  DEF_ROMLOC(DFF2) : cmp_toreg_16(read_16(A0), &D6); // CMP.W	(A0),D6
  DEF_ROMLOC(DFF4) : if (CCR_LS) goto rom_E004;      // BLS.B	$E004
  DEF_ROMLOC(DFF6) : tst_mem_8(A0 + 0x4);            // TST.B	4(A0)
  DEF_ROMLOC(DFFA) : if (CCR_PL) goto rom_E000;      // BPL.B	$E000
  DEF_ROMLOC(DFFC) : add_tomem_8(0x1, A2 + 0x1);     // ADDQ.B	#$01,1(A2)
  DEF_ROMLOC(E000) : add_toreg_16(0x6, &A0);         // ADDQ.W	#$06,A0
  goto rom_DFF2;                                     // BRA.B	$DFF2
  DEF_ROMLOC(E004) : move_tomem_32(A0, 0xFFFFF774);  // MOVE.L	A0,$F774
  DEF_ROMLOC(E008)
      : move_tomem_16(0xFFFFFFFF, 0xFFFFF76E); // MOVE.W	#$FFFF,$F76E
  rom_E00E(); // Detected flow into next function
}
ROMFUNC(rom_E00E) {
  DEF_ROMLOC(E00E) : move_toreg_32(0xFFFFFC00, &A2); // LEA.L	$FC00,A2
  DEF_ROMLOC(E012) : move_toreg_32(0x0, &D2);        // MOVEQ.L	$00,D2
  DEF_ROMLOC(E014)
      : move_toreg_16(read_16(v_screenposx), &D6);  // MOVE.W	$F700,D6
  DEF_ROMLOC(E018) : and_toreg_16(0xFFFFFF80, &D6); // ANDI.W	#$FF80,D6
  DEF_ROMLOC(E01C)
      : cmp_toreg_16(read_16(0xFFFFF76E), &D6);     // CMP.W	$F76E,D6
  DEF_ROMLOC(E020) : if (CCR_EQ) goto rom_E0C8;     // BEQ.W	$E0C8
  DEF_ROMLOC(E024) : if (CCR_GE) goto rom_E084;     // BGE.B	$E084
  DEF_ROMLOC(E026) : move_tomem_16(D6, 0xFFFFF76E); // MOVE.W	D6,$F76E
  DEF_ROMLOC(E02A)
      : move_toreg_32(read_32(0xFFFFF774), &A0); // MOVEA.L	$F774,A0
  DEF_ROMLOC(E02E) : sub_toreg_16(0x80, &D6);    // SUBI.W	#$0080,D6
  DEF_ROMLOC(E032) : if (CCR_CS) goto rom_E060;  // BCS.B	$E060
  DEF_ROMLOC(E034)
      : cmp_toreg_16(read_16(A0 - 0x6), &D6);             // CMP.W	-6(A0),D6
  DEF_ROMLOC(E038) : if (CCR_GE) goto rom_E060;           // BGE.B	$E060
  DEF_ROMLOC(E03A) : sub_toreg_16(0x6, &A0);              // SUBQ.W	#$06,A0
  DEF_ROMLOC(E03C) : tst_mem_8(A0 + 0x4);                 // TST.B	4(A0)
  DEF_ROMLOC(E040) : if (CCR_PL) goto rom_E04A;           // BPL.B	$E04A
  DEF_ROMLOC(E042) : sub_tomem_8(0x1, A2 + 0x1);          // SUBQ.B	#$01,1(A2)
  DEF_ROMLOC(E046) : move_toreg_8(read_8(A2 + 0x1), &D2); // MOVE.B	1(A2),D2
  DEF_ROMLOC(E04A) : rom_E0CA();                          // BSR.W	$E0CA
  DEF_ROMLOC(E04E) : if (!CCR_EQ) goto rom_E054;          // BNE.B	$E054
  DEF_ROMLOC(E050) : sub_toreg_16(0x6, &A0);              // SUBQ.W	#$06,A0
  goto rom_E034;                                          // BRA.B	$E034
  DEF_ROMLOC(E054) : tst_mem_8(A0 + 0x4);                 // TST.B	4(A0)
  DEF_ROMLOC(E058) : if (CCR_PL) goto rom_E05E;           // BPL.B	$E05E
  DEF_ROMLOC(E05A) : add_tomem_8(0x1, A2 + 0x1);          // ADDQ.B	#$01,1(A2)
  DEF_ROMLOC(E05E) : add_toreg_16(0x6, &A0);              // ADDQ.W	#$06,A0
  DEF_ROMLOC(E060) : move_tomem_32(A0, 0xFFFFF774);       // MOVE.L	A0,$F774
  DEF_ROMLOC(E064)
      : move_toreg_32(read_32(0xFFFFF770), &A0); // MOVEA.L	$F770,A0
  DEF_ROMLOC(E068) : add_toreg_16(0x300, &D6);   // ADDI.W	#$0300,D6
  DEF_ROMLOC(E06C)
      : cmp_toreg_16(read_16(A0 - 0x6), &D6);       // CMP.W
                                                    // -6(A0),D6
  DEF_ROMLOC(E070) : if (CCR_GT) goto rom_E07E;     // BGT.B	$E07E
  DEF_ROMLOC(E072) : tst_mem_8(A0 - 0x2);           // TST.B	-2(A0)
  DEF_ROMLOC(E076) : if (CCR_PL) goto rom_E07A;     // BPL.B	$E07A
  DEF_ROMLOC(E078) : sub_tomem_8(0x1, A2);          // SUBQ.B	#$01,(A2)
  DEF_ROMLOC(E07A) : sub_toreg_16(0x6, &A0);        // SUBQ.W	#$06,A0
  goto rom_E06C;                                    // BRA.B	$E06C
  DEF_ROMLOC(E07E) : move_tomem_32(A0, 0xFFFFF770); // MOVE.L	A0,$F770
  DEF_ROMLOC(E082) : return;                        // RTS
  DEF_ROMLOC(E084) : move_tomem_16(D6, 0xFFFFF76E); // MOVE.W	D6,$F76E
  DEF_ROMLOC(E088)
      : move_toreg_32(read_32(0xFFFFF770), &A0);     // MOVEA.L	$F770,A0
  DEF_ROMLOC(E08C) : add_toreg_16(0x280, &D6);       // ADDI.W	#$0280,D6
  DEF_ROMLOC(E090) : cmp_toreg_16(read_16(A0), &D6); // CMP.W	(A0),D6
  DEF_ROMLOC(E092) : if (CCR_LS) goto rom_E0A4;      // BLS.B	$E0A4
  DEF_ROMLOC(E094) : tst_mem_8(A0 + 0x4);            // TST.B	4(A0)
  DEF_ROMLOC(E098) : if (CCR_PL) goto rom_E09E;      // BPL.B	$E09E
  DEF_ROMLOC(E09A) : move_toreg_8(read_8(A2), &D2);  // MOVE.B	(A2),D2
  DEF_ROMLOC(E09C) : add_tomem_8(0x1, A2);           // ADDQ.B	#$01,(A2)
  DEF_ROMLOC(E09E) : rom_E0CA();                     // BSR.W	$E0CA
  DEF_ROMLOC(E0A2) : if (CCR_EQ) goto rom_E090;      // BEQ.B	$E090
  DEF_ROMLOC(E0A4) : move_tomem_32(A0, 0xFFFFF770);  // MOVE.L	A0,$F770
  DEF_ROMLOC(E0A8)
      : move_toreg_32(read_32(0xFFFFF774), &A0);     // MOVEA.L	$F774,A0
  DEF_ROMLOC(E0AC) : sub_toreg_16(0x300, &D6);       // SUBI.W	#$0300,D6
  DEF_ROMLOC(E0B0) : if (CCR_CS) goto rom_E0C4;      // BCS.B	$E0C4
  DEF_ROMLOC(E0B2) : cmp_toreg_16(read_16(A0), &D6); // CMP.W	(A0),D6
  DEF_ROMLOC(E0B4) : if (CCR_LS) goto rom_E0C4;      // BLS.B	$E0C4
  DEF_ROMLOC(E0B6) : tst_mem_8(A0 + 0x4);            // TST.B	4(A0)
  DEF_ROMLOC(E0BA) : if (CCR_PL) goto rom_E0C0;      // BPL.B	$E0C0
  DEF_ROMLOC(E0BC) : add_tomem_8(0x1, A2 + 0x1);     // ADDQ.B	#$01,1(A2)
  DEF_ROMLOC(E0C0) : add_toreg_16(0x6, &A0);         // ADDQ.W	#$06,A0
  goto rom_E0B2;                                     // BRA.B	$E0B2
  DEF_ROMLOC(E0C4) : move_tomem_32(A0, 0xFFFFF774);  // MOVE.L	A0,$F774
  DEF_ROMLOC(E0C8) : return;                         // RTS
}
ROMFUNC(rom_E0CA) {
  DEF_ROMLOC(E0CA) : tst_mem_8(A0 + 0x4);       // TST.B	4(A0)
  DEF_ROMLOC(E0CE) : if (CCR_PL) goto rom_E0DE; // BPL.B	$E0DE
  DEF_ROMLOC(E0D0)
      : bset_tomem_8(0x7,
                     (s32)A2 + (s8)0x2 + (s16)D2); // BSET.B	#$07,2(A2,D2)
  DEF_ROMLOC(E0D6) : if (CCR_EQ) goto rom_E0DE;    // BEQ.B	$E0DE
  DEF_ROMLOC(E0D8) : add_toreg_16(0x6, &A0);       // ADDQ.W	#$06,A0
  DEF_ROMLOC(E0DA) : move_toreg_32(0x0, &D0);      // MOVEQ.L	$00,D0
  DEF_ROMLOC(E0DC) : return;                       // RTS
  DEF_ROMLOC(E0DE) : rom_E11A();                   // BSR.W	$E11A
  DEF_ROMLOC(E0E2) : if (!CCR_EQ) goto rom_E118;   // BNE.B	$E118
  DEF_ROMLOC(E0E4)
      : move_tomem_16(read_16((A0 += 2, A0 - 2)),
                      A1 + 0x8); // MOVE.W	(A0)+,8(A1)
  DEF_ROMLOC(E0E8)
      : move_toreg_16(read_16((A0 += 2, A0 - 2)), &D0); // MOVE.W	(A0)+,D0
  DEF_ROMLOC(E0EA) : move_toreg_16(D0, &D1);            // MOVE.W	D0,D1
  DEF_ROMLOC(E0EC) : and_toreg_16(0xFFF, &D0);          // ANDI.W	#$0FFF,D0
  DEF_ROMLOC(E0F0) : move_tomem_16(D0, A1 + 0xC);       // MOVE.W	D0,12(A1)
  DEF_ROMLOC(E0F4) : rol_toreg_16(0x2, &D1);            // ROL.W	#$02,D1
  DEF_ROMLOC(E0F6) : and_toreg_8(0x3, &D1);             // ANDI.B	#$03,D1
  DEF_ROMLOC(E0FA) : move_tomem_8(D1, A1 + 0x1);        // MOVE.B	D1,1(A1)
  DEF_ROMLOC(E0FE) : move_tomem_8(D1, A1 + 0x22);       // MOVE.B	D1,34(A1)
  DEF_ROMLOC(E102) : move_toreg_8(read_8(A0++), &D0);   // MOVE.B	(A0)+,D0
  DEF_ROMLOC(E104) : if (CCR_PL) goto rom_E10E;         // BPL.B	$E10E
  DEF_ROMLOC(E106) : and_toreg_8(0x7F, &D0);            // ANDI.B	#$7F,D0
  DEF_ROMLOC(E10A) : move_tomem_8(D2, A1 + 0x23);       // MOVE.B	D2,35(A1)
  DEF_ROMLOC(E10E) : move_tomem_8(D0, A1 + 0x0);        // MOVE.B	D0,0(A1)
  DEF_ROMLOC(E112)
      : move_tomem_8(read_8(A0++), A1 + 0x28); // MOVE.B	(A0)+,40(A1)
  DEF_ROMLOC(E116) : move_toreg_32(0x0, &D0);  // MOVEQ.L	$00,D0
  DEF_ROMLOC(E118) : return;                   // RTS
}
ROMFUNC(rom_E11A) {
  DEF_ROMLOC(E11A) : move_toreg_32(0xFFFFD800, &A1); // LEA.L	$D800,A1
  DEF_ROMLOC(E11E) : move_toreg_16(0x5F, &D0);       // MOVE.W	#$005F,D0
  DEF_ROMLOC(E122) : tst_mem_8(A1);                  // TST.B	(A1)
  DEF_ROMLOC(E124) : if (CCR_EQ) goto rom_E12E;      // BEQ.B	$E12E
  DEF_ROMLOC(E126) : move_toreg_32(A1 + 0x40, &A1);  // LEA.L	64(A1),A1
  DEF_ROMLOC(E12A) : dec_reg_16(&D0);
  if ((D0 & 0xffff) != 0xffff)
    goto rom_E122;           // DBF.W	D0,$E122
  DEF_ROMLOC(E12E) : return; // RTS
}
ROMFUNC(rom_E130) {
  DEF_ROMLOC(E130) : move_toreg_32(A0, &A1);         // MOVEA.L	A0,A1
  DEF_ROMLOC(E132) : move_toreg_16(0xFFFFF000, &D0); // MOVE.W	#$F000,D0
  DEF_ROMLOC(E136) : sub_toreg_16(A0, &D0);          // SUB.W	A0,D0
  DEF_ROMLOC(E138) : lsr_toreg_16(0x6, &D0);         // LSR.W	#$06,D0
  DEF_ROMLOC(E13A) : sub_toreg_16(0x1, &D0);         // SUBQ.W	#$01,D0
  DEF_ROMLOC(E13C) : if (CCR_CS) goto rom_E14A;      // BCS.B	$E14A
  DEF_ROMLOC(E13E) : tst_mem_8(A1);                  // TST.B	(A1)
  DEF_ROMLOC(E140) : if (CCR_EQ) goto rom_E14A;      // BEQ.B	$E14A
  DEF_ROMLOC(E142) : move_toreg_32(A1 + 0x40, &A1);  // LEA.L	64(A1),A1
  DEF_ROMLOC(E146) : dec_reg_16(&D0);
  if ((D0 & 0xffff) != 0xffff)
    goto rom_E13E;           // DBF.W	D0,$E13E
  DEF_ROMLOC(E14A) : return; // RTS
}
ROMFUNC(rom_FD38) {
  DEF_ROMLOC(FD38) : move_toreg_16(read_16(A0 + 0x8), &D0); // MOVE.W	8(A0),D0
  DEF_ROMLOC(FD3C) : and_toreg_16(0xFFFFFF80, &D0);         // ANDI.W	#$FF80,D0
  DEF_ROMLOC(FD40)
      : move_toreg_16(read_16(v_screenposx), &D1);  // MOVE.W	$F700,D1
  DEF_ROMLOC(FD44) : sub_toreg_16(0x80, &D1);       // SUBI.W	#$0080,D1
  DEF_ROMLOC(FD48) : and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
  DEF_ROMLOC(FD4C) : sub_toreg_16(D1, &D0);         // SUB.W	D1,D0
  DEF_ROMLOC(FD4E)
      : cmp_toreg_16(128 + GAME_WIDTH + 192, &D0); // CMPI.W	#$0280,D0
  DEF_ROMLOC(FD52) : if (CCR_HI) goto rom_FD5A;    // BHI.W	$FD5A
  DEF_ROMLOC(FD56) : {
    queue_sprite();
    return;
  } // BRA.W	$DC92
  DEF_ROMLOC(FD5A) : move_toreg_32(0xFFFFFC00, &A2); // LEA.L	$FC00,A2
  DEF_ROMLOC(FD5E) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(FD60)
      : move_toreg_8(read_8(A0 + 0x23), &D0);   // MOVE.B	35(A0),D0
  DEF_ROMLOC(FD64) : if (CCR_EQ) goto rom_FD6C; // BEQ.B	$FD6C
  DEF_ROMLOC(FD66)
      : bclr_tomem_8(0x7,
                     (s32)A2 + (s8)0x2 + (s16)D0); // BCLR.B	#$07,2(A2,D0)
  DEF_ROMLOC(FD6C) : rom_DCCE();                   // BRA.W	$DCCE
}
ROMFUNC(rom_15580) {
  DEF_ROMLOC(15580)
      : move_toreg_16(read_16(A0 + 0x8), &D3); // MOVE.W	8(A0),D3
  rom_15584(); // Detected flow into next function
}
ROMFUNC(rom_15584) {
  DEF_ROMLOC(15584)
      : move_toreg_16(read_16(A0 + 0xC), &D2); // MOVE.W	12(A0),D2
  DEF_ROMLOC(15588) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(1558A)
      : move_toreg_8(read_8(A0 + 0x16), &D0);         // MOVE.B
                                                      // 22(A0),D0
  DEF_ROMLOC(1558E) : ext_reg_16(&D0);                // EXT.W	D0
  DEF_ROMLOC(15590) : add_toreg_16(D0, &D2);          // ADD.W	D0,D2
  DEF_ROMLOC(15592) : move_toreg_32(0xFFFFF768, &A4); // LEA.L	$F768,A4
  DEF_ROMLOC(15596) : move_tomem_8(0x0, A4);          // MOVE.B	#$00,(A4)
  DEF_ROMLOC(1559A) : move_toreg_16(0x10, &A3);       // MOVEA.W	#$0010,A3
  DEF_ROMLOC(1559E) : move_toreg_16(0x0, &D6);        // MOVE.W	#$0000,D6
  DEF_ROMLOC(155A2) : move_toreg_32(0xD, &D5);        // MOVEQ.L	$0D,D5
  DEF_ROMLOC(155A4) : rom_15136();                    // BSR.W	$15136
  DEF_ROMLOC(155A8)
      : move_toreg_8(read_8(0xFFFFF768), &D3);    // MOVE.B	$F768,D3
  DEF_ROMLOC(155AC) : btst_toreg_32(0x0, &D3);    // BTST.L	#$00,D3
  DEF_ROMLOC(155B0) : if (CCR_EQ) goto rom_155B6; // BEQ.B	$155B6
  DEF_ROMLOC(155B2) : move_toreg_8(0x0, &D3);     // MOVE.B	#$00,D3
  DEF_ROMLOC(155B6) : return;                     // RTS
}
ROMFUNC(rom_155B8) {
  DEF_ROMLOC(155B8)
      : move_toreg_16(read_16(A0 + 0xC), &D2); // MOVE.W	12(A0),D2
  DEF_ROMLOC(155BC)
      : move_toreg_16(read_16(A0 + 0x8), &D3); // MOVE.W	8(A0),D3
  DEF_ROMLOC(155C0) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(155C2)
      : move_toreg_8(read_8(A0 + 0x17), &D0); // MOVE.B
                                              // 23(A0),D0
  DEF_ROMLOC(155C6) : ext_reg_16(&D0);        // EXT.W	D0
  DEF_ROMLOC(155C8) : sub_toreg_16(D0, &D2);  // SUB.W	D0,D2
  DEF_ROMLOC(155CA)
      : move_toreg_8(read_8(A0 + 0x16), &D0);         // MOVE.B
                                                      // 22(A0),D0
  DEF_ROMLOC(155CE) : ext_reg_16(&D0);                // EXT.W	D0
  DEF_ROMLOC(155D0) : add_toreg_16(D0, &D3);          // ADD.W	D0,D3
  DEF_ROMLOC(155D2) : move_toreg_32(0xFFFFF768, &A4); // LEA.L	$F768,A4
  DEF_ROMLOC(155D6) : move_toreg_16(0x10, &A3);       // MOVEA.W	#$0010,A3
  DEF_ROMLOC(155DA) : move_toreg_16(0x0, &D6);        // MOVE.W	#$0000,D6
  DEF_ROMLOC(155DE) : move_toreg_32(0xE, &D5);        // MOVEQ.L	$0E,D5
  DEF_ROMLOC(155E0) : rom_15274();                    // BSR.W	$15274
  DEF_ROMLOC(155E4) : move_tomem_16(D1, A7 -= 2);     // MOVE.W	D1,-(A7)
  DEF_ROMLOC(155E6)
      : move_toreg_16(read_16(A0 + 0xC), &D2); // MOVE.W	12(A0),D2
  DEF_ROMLOC(155EA)
      : move_toreg_16(read_16(A0 + 0x8), &D3); // MOVE.W	8(A0),D3
  DEF_ROMLOC(155EE) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(155F0)
      : move_toreg_8(read_8(A0 + 0x17), &D0); // MOVE.B
                                              // 23(A0),D0
  DEF_ROMLOC(155F4) : ext_reg_16(&D0);        // EXT.W	D0
  DEF_ROMLOC(155F6) : add_toreg_16(D0, &D2);  // ADD.W	D0,D2
  DEF_ROMLOC(155F8)
      : move_toreg_8(read_8(A0 + 0x16), &D0);         // MOVE.B
                                                      // 22(A0),D0
  DEF_ROMLOC(155FC) : ext_reg_16(&D0);                // EXT.W	D0
  DEF_ROMLOC(155FE) : add_toreg_16(D0, &D3);          // ADD.W	D0,D3
  DEF_ROMLOC(15600) : move_toreg_32(0xFFFFF76A, &A4); // LEA.L	$F76A,A4
  DEF_ROMLOC(15604) : move_toreg_16(0x10, &A3);       // MOVEA.W	#$0010,A3
  DEF_ROMLOC(15608) : move_toreg_16(0x0, &D6);        // MOVE.W	#$0000,D6
  DEF_ROMLOC(1560C) : move_toreg_32(0xE, &D5);        // MOVEQ.L	$0E,D5
  DEF_ROMLOC(1560E) : rom_15274();                    // BSR.W	$15274
  DEF_ROMLOC(15612)
      : move_toreg_16(read_16((A7 += 2, A7 - 2)), &D0); // MOVE.W	(A7)+,D0
  DEF_ROMLOC(15614) : move_toreg_8(0xFFFFFFC0, &D2);    // MOVE.B	#$C0,D2
  rom_15538();                                          // BRA.W	$15538
}
ROMFUNC(rom_1561C) {
  DEF_ROMLOC(1561C)
      : move_toreg_16(read_16(A0 + 0xC), &D2); // MOVE.W	12(A0),D2
  DEF_ROMLOC(15620)
      : move_toreg_16(read_16(A0 + 0x8), &D3); // MOVE.W	8(A0),D3
  rom_15624(); // Detected flow into next function
}
ROMFUNC(rom_15624) {
  DEF_ROMLOC(15624) : add_toreg_16(0xA, &D3);         // ADDI.W	#$000A,D3
  DEF_ROMLOC(15628) : move_toreg_32(0xFFFFF768, &A4); // LEA.L	$F768,A4
  DEF_ROMLOC(1562C) : move_toreg_16(0x10, &A3);       // MOVEA.W	#$0010,A3
  DEF_ROMLOC(15630) : move_toreg_16(0x0, &D6);        // MOVE.W	#$0000,D6
  DEF_ROMLOC(15634) : move_toreg_32(0xE, &D5);        // MOVEQ.L	$0E,D5
  DEF_ROMLOC(15636) : rom_15274();                    // BSR.W	$15274
  DEF_ROMLOC(1563A) : move_toreg_8(0xFFFFFFC0, &D2);  // MOVE.B	#$C0,D2
  rom_15572();                                        // BRA.W	$15572
}
ROMFUNC(rom_1573E) {
  DEF_ROMLOC(1573E)
      : move_toreg_16(read_16(A0 + 0xC), &D2); // MOVE.W	12(A0),D2
  DEF_ROMLOC(15742)
      : move_toreg_16(read_16(A0 + 0x8), &D3); // MOVE.W	8(A0),D3
  DEF_ROMLOC(15746) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(15748)
      : move_toreg_8(read_8(A0 + 0x17), &D0); // MOVE.B
                                              // 23(A0),D0
  DEF_ROMLOC(1574C) : ext_reg_16(&D0);        // EXT.W	D0
  DEF_ROMLOC(1574E) : sub_toreg_16(D0, &D2);  // SUB.W	D0,D2
  DEF_ROMLOC(15750)
      : move_toreg_8(read_8(A0 + 0x16), &D0);         // MOVE.B
                                                      // 22(A0),D0
  DEF_ROMLOC(15754) : ext_reg_16(&D0);                // EXT.W	D0
  DEF_ROMLOC(15756) : sub_toreg_16(D0, &D3);          // SUB.W	D0,D3
  DEF_ROMLOC(15758) : eor_toreg_16(0xF, &D3);         // EORI.W	#$000F,D3
  DEF_ROMLOC(1575C) : move_toreg_32(0xFFFFF768, &A4); // LEA.L	$F768,A4
  DEF_ROMLOC(15760)
      : move_toreg_16(0xFFFFFFF0, &A3);           // MOVEA.W
                                                  // #$FFF0,A3
  DEF_ROMLOC(15764) : move_toreg_16(0x800, &D6);  // MOVE.W	#$0800,D6
  DEF_ROMLOC(15768) : move_toreg_32(0xE, &D5);    // MOVEQ.L	$0E,D5
  DEF_ROMLOC(1576A) : rom_15274();                // BSR.W	$15274
  DEF_ROMLOC(1576E) : move_tomem_16(D1, A7 -= 2); // MOVE.W	D1,-(A7)
  DEF_ROMLOC(15770)
      : move_toreg_16(read_16(A0 + 0xC), &D2); // MOVE.W	12(A0),D2
  DEF_ROMLOC(15774)
      : move_toreg_16(read_16(A0 + 0x8), &D3); // MOVE.W	8(A0),D3
  DEF_ROMLOC(15778) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(1577A)
      : move_toreg_8(read_8(A0 + 0x17), &D0); // MOVE.B
                                              // 23(A0),D0
  DEF_ROMLOC(1577E) : ext_reg_16(&D0);        // EXT.W	D0
  DEF_ROMLOC(15780) : add_toreg_16(D0, &D2);  // ADD.W	D0,D2
  DEF_ROMLOC(15782)
      : move_toreg_8(read_8(A0 + 0x16), &D0);         // MOVE.B
                                                      // 22(A0),D0
  DEF_ROMLOC(15786) : ext_reg_16(&D0);                // EXT.W	D0
  DEF_ROMLOC(15788) : sub_toreg_16(D0, &D3);          // SUB.W	D0,D3
  DEF_ROMLOC(1578A) : eor_toreg_16(0xF, &D3);         // EORI.W	#$000F,D3
  DEF_ROMLOC(1578E) : move_toreg_32(0xFFFFF76A, &A4); // LEA.L	$F76A,A4
  DEF_ROMLOC(15792)
      : move_toreg_16(0xFFFFFFF0, &A3);          // MOVEA.W
                                                 // #$FFF0,A3
  DEF_ROMLOC(15796) : move_toreg_16(0x800, &D6); // MOVE.W	#$0800,D6
  DEF_ROMLOC(1579A) : move_toreg_32(0xE, &D5);   // MOVEQ.L	$0E,D5
  DEF_ROMLOC(1579C) : rom_15274();               // BSR.W	$15274
  DEF_ROMLOC(157A0)
      : move_toreg_16(read_16((A7 += 2, A7 - 2)), &D0); // MOVE.W	(A7)+,D0
  DEF_ROMLOC(157A2) : move_toreg_8(0x40, &D2);          // MOVE.B	#$40,D2
  rom_15538();                                          // BRA.W	$15538
}
ROMFUNC(rom_1B8A6) {
  DEF_ROMLOC(1B8A6)
      : move_toreg_8(read_8(A1 + 0x20), &D1);     // MOVE.B	32(A1),D1
  DEF_ROMLOC(1B8AA) : and_toreg_8(0x3F, &D1);     // ANDI.B	#$3F,D1
  DEF_ROMLOC(1B8AE) : cmp_toreg_8(0xB, &D1);      // CMPI.B	#$0B,D1
  DEF_ROMLOC(1B8B2) : if (CCR_EQ) goto rom_1B8C8; // BEQ.B	$1B8C8
  DEF_ROMLOC(1B8B4) : cmp_toreg_8(0xC, &D1);      // CMPI.B	#$0C,D1
  DEF_ROMLOC(1B8B8) : if (CCR_EQ) goto rom_1B8CC; // BEQ.B	$1B8CC
  DEF_ROMLOC(1B8BA) : cmp_toreg_8(0x17, &D1);     // CMPI.B	#$17,D1
  DEF_ROMLOC(1B8BE) : if (CCR_EQ) goto rom_1B8FE; // BEQ.B	$1B8FE
  DEF_ROMLOC(1B8C0) : cmp_toreg_8(0x21, &D1);     // CMPI.B	#$21,D1
  DEF_ROMLOC(1B8C4) : if (CCR_EQ) goto rom_1B8FE; // BEQ.B	$1B8FE
  DEF_ROMLOC(1B8C6) : return;                     // RTS
  DEF_ROMLOC(1B8C8) : {
    rom_1B790();
    return;
  } // BRA.W	$1B790
  DEF_ROMLOC(1B8CC) : sub_toreg_16(D0, &D5);      // SUB.W	D0,D5
  DEF_ROMLOC(1B8CE) : cmp_toreg_16(0x8, &D5);     // CMPI.W	#$0008,D5
  DEF_ROMLOC(1B8D2) : if (CCR_CC) goto rom_1B8FA; // BCC.B	$1B8FA
  DEF_ROMLOC(1B8D4)
      : move_toreg_16(read_16(A1 + 0x8), &D0);      // MOVE.W	8(A1),D0
  DEF_ROMLOC(1B8D8) : sub_toreg_16(0x4, &D0);       // SUBQ.W	#$04,D0
  DEF_ROMLOC(1B8DA) : btst_tomem_8(0x0, A1 + 0x22); // BTST.B	#$00,34(A1)
  DEF_ROMLOC(1B8E0) : if (CCR_EQ) goto rom_1B8E6;   // BEQ.B	$1B8E6
  DEF_ROMLOC(1B8E2) : sub_toreg_16(0x10, &D0);      // SUBI.W	#$0010,D0
  DEF_ROMLOC(1B8E6) : sub_toreg_16(D2, &D0);        // SUB.W	D2,D0
  DEF_ROMLOC(1B8E8) : if (CCR_CC) goto rom_1B8F2;   // BCC.B	$1B8F2
  DEF_ROMLOC(1B8EA) : add_toreg_16(0x18, &D0);      // ADDI.W	#$0018,D0
  DEF_ROMLOC(1B8EE) : if (CCR_CS) goto rom_1B8F6;   // BCS.B	$1B8F6
  DEF_ROMLOC(1B8F0) : goto rom_1B8FA;               // BRA.B	$1B8FA
  DEF_ROMLOC(1B8F2) : cmp_toreg_16(D4, &D0);        // CMP.W	D4,D0
  DEF_ROMLOC(1B8F4) : if (CCR_HI) goto rom_1B8FA;   // BHI.B	$1B8FA
  DEF_ROMLOC(1B8F6) : {
    rom_1B796();
    return;
  } // BRA.W	$1B796
  DEF_ROMLOC(1B8FA) : {
    rom_1B6E6();
    return;
  } // BRA.W	$1B6E6
  DEF_ROMLOC(1B8FE) : add_tomem_8(0x1, A1 + 0x21); // ADDQ.B	#$01,33(A1)
  DEF_ROMLOC(1B902) : return;                      // RTS
}
ROMFUNC(rom_8BA8) {
  DEF_ROMLOC(8BA8) : move_toreg_32(0xFFFFD000, &A1); // LEA.L	$D000,A1
  DEF_ROMLOC(8BAC) : btst_tomem_8(0x3, A1 + 0x22);   // BTST.B	#$03,34(A1)
  DEF_ROMLOC(8BB2) : if (CCR_EQ) goto rom_8BEC;      // BEQ.B	$8BEC
  DEF_ROMLOC(8BB4)
      : move_toreg_16(read_16(A1 + 0x8), &D0); // MOVE.W	8(A1),D0
  DEF_ROMLOC(8BB8)
      : sub_toreg_16(read_16(A0 + 0x8), &D0);     // SUB.W	8(A0),D0
  DEF_ROMLOC(8BBC) : add_toreg_16(D1, &D0);       // ADD.W	D1,D0
  DEF_ROMLOC(8BBE) : lsr_toreg_16(0x1, &D0);      // LSR.W	#$01,D0
  DEF_ROMLOC(8BC0) : btst_tomem_8(0x0, A0 + 0x1); // BTST.B	#$00,1(A0)
  DEF_ROMLOC(8BC6) : if (CCR_EQ) goto rom_8BCC;   // BEQ.B	$8BCC
  DEF_ROMLOC(8BC8) : not_reg_16(&D0);             // NOT.W	D0
  DEF_ROMLOC(8BCA) : add_toreg_16(D1, &D0);       // ADD.W	D1,D0
  DEF_ROMLOC(8BCC) : move_toreg_32(0x0, &D1);     // MOVEQ.L	$00,D1
  DEF_ROMLOC(8BCE)
      : move_toreg_8(read_8((s32)A2 + (s8)0x0 + (s16)D0),
                     &D1); // MOVE.B	0(A2,D0),D1
  DEF_ROMLOC(8BD2)
      : move_toreg_16(read_16(A0 + 0xC), &D0); // MOVE.W	12(A0),D0
  DEF_ROMLOC(8BD6) : sub_toreg_16(D1, &D0);    // SUB.W	D1,D0
  DEF_ROMLOC(8BD8) : move_toreg_32(0x0, &D1);  // MOVEQ.L	$00,D1
  DEF_ROMLOC(8BDA)
      : move_toreg_8(read_8(A1 + 0x16), &D1);     // MOVE.B	22(A1),D1
  DEF_ROMLOC(8BDE) : sub_toreg_16(D1, &D0);       // SUB.W	D1,D0
  DEF_ROMLOC(8BE0) : move_tomem_16(D0, A1 + 0xC); // MOVE.W	D0,12(A1)
  DEF_ROMLOC(8BE4)
      : sub_toreg_16(read_16(A0 + 0x8), &D2);    // SUB.W	8(A0),D2
  DEF_ROMLOC(8BE8) : sub_tomem_16(D2, A1 + 0x8); // SUB.W	D2,8(A1)
  DEF_ROMLOC(8BEC) : return;                     // RTS
}
ROMFUNC(rom_13F52) {
  DEF_ROMLOC(13F52)
      : move_toreg_16(read_16(0xFFFFF72E), &D0); // MOVE.W	$F72E,D0
  DEF_ROMLOC(13F56) : add_toreg_16(0x100, &D0);  // ADDI.W	#$0100,D0
  DEF_ROMLOC(13F5A)
      : cmp_toreg_16(read_16(A0 + 0xC), &D0);     // CMP.W	12(A0),D0
  DEF_ROMLOC(13F5E) : if (CCR_CC) goto rom_13FD4; // BCC.W	$13FD4
  DEF_ROMLOC(13F62)
      : move_tomem_16(0xFFFFFFC8, A0 + 0x12);         // MOVE.W	#$FFC8,18(A0)
  DEF_ROMLOC(13F68) : add_tomem_8(0x2, A0 + 0x24);    // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(13F6C) : clr_mem_8(f_timecount);         // CLR.B	$FE1E
  DEF_ROMLOC(13F70) : add_tomem_8(0x1, 0xFFFFFE1C);   // ADDQ.B	#$01,$FE1C
  DEF_ROMLOC(13F74) : sub_tomem_8(0x1, v_lives);      // SUBQ.B	#$01,$FE12
  DEF_ROMLOC(13F78) : if (!CCR_EQ) goto rom_13FA8;    // BNE.B	$13FA8
  DEF_ROMLOC(13F7A) : move_tomem_16(0x0, A0 + 0x3A);  // MOVE.W	#$0000,58(A0)
  DEF_ROMLOC(13F80) : move_tomem_8(0x39, 0xFFFFD080); // MOVE.B	#$39,$D080
  DEF_ROMLOC(13F86) : move_tomem_8(0x39, 0xFFFFD0C0); // MOVE.B	#$39,$D0C0
  DEF_ROMLOC(13F8C) : move_tomem_8(0x1, 0xFFFFD0DA);  // MOVE.B	#$01,$D0DA
  DEF_ROMLOC(13F92) : clr_mem_8(0xFFFFFE1A);          // CLR.B	$FE1A
  DEF_ROMLOC(13F96)
      : move_toreg_16(BGM_GAMEOVER, &D0);      // MOVE.W
                                               // #$008F,D0
  DEF_ROMLOC(13F9A) : play_sound();            // JSR	$0000138E
  DEF_ROMLOC(13FA0) : move_toreg_32(0x3, &D0); // MOVEQ.L	$03,D0
  DEF_ROMLOC(13FA2) : {
    add_plc();
    return;
  } // JMP	$00001578
  DEF_ROMLOC(13FA8) : move_tomem_16(0x3C, A0 + 0x3A); // MOVE.W	#$003C,58(A0)
  DEF_ROMLOC(13FAE) : tst_mem_8(0xFFFFFE1A);          // TST.B	$FE1A
  DEF_ROMLOC(13FB2) : if (CCR_EQ) goto rom_13FD4;     // BEQ.B	$13FD4
  DEF_ROMLOC(13FB4) : move_tomem_16(0x0, A0 + 0x3A);  // MOVE.W	#$0000,58(A0)
  DEF_ROMLOC(13FBA) : move_tomem_8(0x39, 0xFFFFD080); // MOVE.B	#$39,$D080
  DEF_ROMLOC(13FC0) : move_tomem_8(0x39, 0xFFFFD0C0); // MOVE.B	#$39,$D0C0
  DEF_ROMLOC(13FC6) : move_tomem_8(0x2, 0xFFFFD09A);  // MOVE.B	#$02,$D09A
  DEF_ROMLOC(13FCC) : move_tomem_8(0x3, 0xFFFFD0DA);  // MOVE.B	#$03,$D0DA
  goto rom_13F96;                                     // BRA.B	$13F96
  DEF_ROMLOC(13FD4) : return;                         // RTS
}
ROMFUNC(rom_100A8) {
  DEF_ROMLOC(100A8) : tst_mem_8(A0 + 0x25); // TST.B	37(A0)
  DEF_ROMLOC(100AC) : if (CCR_EQ) {
    rom_1015C();
    return;
  } // BEQ.W	$1015C
  DEF_ROMLOC(100B0) : move_toreg_16(D1, &D2);         // MOVE.W	D1,D2
  DEF_ROMLOC(100B2) : add_toreg_16(D2, &D2);          // ADD.W	D2,D2
  DEF_ROMLOC(100B4) : move_toreg_32(0xFFFFD000, &A1); // LEA.L	$D000,A1
  DEF_ROMLOC(100B8) : btst_tomem_8(0x1, A1 + 0x22);   // BTST.B	#$01,34(A1)
  DEF_ROMLOC(100BE) : if (!CCR_EQ) goto rom_100D0;    // BNE.B	$100D0
  DEF_ROMLOC(100C0)
      : move_toreg_16(read_16(A1 + 0x8), &D0);              // MOVE.W	8(A1),D0
  DEF_ROMLOC(100C4) : sub_toreg_16(read_16(A0 + 0x8), &D0); // SUB.W	8(A0),D0
  DEF_ROMLOC(100C8) : add_toreg_16(D1, &D0);                // ADD.W	D1,D0
  DEF_ROMLOC(100CA) : if (CCR_MI) goto rom_100D0;           // BMI.B	$100D0
  DEF_ROMLOC(100CC) : cmp_toreg_16(D2, &D0);                // CMP.W	D2,D0
  DEF_ROMLOC(100CE) : if (CCR_CS) goto rom_100E4;           // BCS.B	$100E4
  DEF_ROMLOC(100D0) : bclr_tomem_8(0x3, A1 + 0x22); // BCLR.B	#$03,34(A1)
  DEF_ROMLOC(100D6) : bclr_tomem_8(0x3, A0 + 0x22); // BCLR.B	#$03,34(A0)
  DEF_ROMLOC(100DC) : clr_mem_8(A0 + 0x25);         // CLR.B	37(A0)
  DEF_ROMLOC(100E0) : move_toreg_32(0x0, &D4);      // MOVEQ.L	$00,D4
  DEF_ROMLOC(100E2) : return;                       // RTS
  DEF_ROMLOC(100E4) : move_toreg_16(D4, &D2);       // MOVE.W	D4,D2
  DEF_ROMLOC(100E6) : rom_81A0();                   // BSR.W	$81A0
  DEF_ROMLOC(100EA) : move_toreg_32(0x0, &D4);      // MOVEQ.L	$00,D4
  DEF_ROMLOC(100EC) : return;                       // RTS
}
ROMFUNC(rom_100EE) {
  DEF_ROMLOC(100EE) : move_toreg_32(0xFFFFD000, &A1); // LEA.L	$D000,A1
  DEF_ROMLOC(100F2) : tst_mem_8(A0 + 0x1);            // TST.B	1(A0)
  DEF_ROMLOC(100F6) : if (CCR_PL) {
    rom_1021E();
    return;
  } // BPL.W	$1021E
  DEF_ROMLOC(100FA)
      : move_toreg_16(read_16(A1 + 0x8), &D0);              // MOVE.W	8(A1),D0
  DEF_ROMLOC(100FE) : sub_toreg_16(read_16(A0 + 0x8), &D0); // SUB.W	8(A0),D0
  DEF_ROMLOC(10102) : add_toreg_16(D1, &D0);                // ADD.W	D1,D0
  DEF_ROMLOC(10104) : if (CCR_MI) {
    rom_1021E();
    return;
  } // BMI.W	$1021E
  DEF_ROMLOC(10108) : move_toreg_16(D1, &D3); // MOVE.W	D1,D3
  DEF_ROMLOC(1010A) : add_toreg_16(D3, &D3);  // ADD.W	D3,D3
  DEF_ROMLOC(1010C) : cmp_toreg_16(D3, &D0);  // CMP.W	D3,D0
  DEF_ROMLOC(1010E) : if (CCR_HI) {
    rom_1021E();
    return;
  } // BHI.W	$1021E
  DEF_ROMLOC(10112) : move_toreg_16(D0, &D5);      // MOVE.W	D0,D5
  DEF_ROMLOC(10114) : btst_tomem_8(0x0, A0 + 0x1); // BTST.B	#$00,1(A0)
  DEF_ROMLOC(1011A) : if (CCR_EQ) goto rom_10120;  // BEQ.B	$10120
  DEF_ROMLOC(1011C) : not_reg_16(&D5);             // NOT.W	D5
  DEF_ROMLOC(1011E) : add_toreg_16(D3, &D5);       // ADD.W	D3,D5
  DEF_ROMLOC(10120) : lsr_toreg_16(0x1, &D5);      // LSR.W	#$01,D5
  DEF_ROMLOC(10122) : move_toreg_32(0x0, &D3);     // MOVEQ.L	$00,D3
  DEF_ROMLOC(10124)
      : move_toreg_8(read_8((s32)A2 + (s8)0x0 + (s16)D5),
                     &D3);                          // MOVE.B	0(A2,D5),D3
  DEF_ROMLOC(10128) : sub_toreg_8(read_8(A2), &D3); // SUB.B	(A2),D3
  DEF_ROMLOC(1012A)
      : move_toreg_16(read_16(A0 + 0xC), &D5); // MOVE.W	12(A0),D5
  DEF_ROMLOC(1012E) : sub_toreg_16(D3, &D5);   // SUB.W	D3,D5
  DEF_ROMLOC(10130)
      : move_toreg_8(read_8(A1 + 0x16), &D3); // MOVE.B
                                              // 22(A1),D3
  DEF_ROMLOC(10134) : ext_reg_16(&D3);        // EXT.W	D3
  DEF_ROMLOC(10136) : add_toreg_16(D3, &D2);  // ADD.W	D3,D2
  DEF_ROMLOC(10138)
      : move_toreg_16(read_16(A1 + 0xC), &D3); // MOVE.W	12(A1),D3
  DEF_ROMLOC(1013C) : sub_toreg_16(D5, &D3);   // SUB.W	D5,D3
  DEF_ROMLOC(1013E) : add_toreg_16(0x4, &D3);  // ADDQ.W	#$04,D3
  DEF_ROMLOC(10140) : add_toreg_16(D2, &D3);   // ADD.W	D2,D3
  DEF_ROMLOC(10142) : if (CCR_MI) {
    rom_1021E();
    return;
  } // BMI.W	$1021E
  DEF_ROMLOC(10146) : move_toreg_16(D2, &D4); // MOVE.W	D2,D4
  DEF_ROMLOC(10148) : add_toreg_16(D4, &D4);  // ADD.W	D4,D4
  DEF_ROMLOC(1014A) : cmp_toreg_16(D4, &D3);  // CMP.W	D4,D3
  DEF_ROMLOC(1014C) : if (CCR_CC) {
    rom_1021E();
    return;
  } // BCC.W	$1021E
  rom_1019A(); // BRA.W	$1019A
}
ROMFUNC(rom_D9D6) {
  u8 switchindex = 0;
  DEF_ROMLOC(D9D6) : move_toreg_8(read_8(A0), &D0); // MOVE.B	(A0),D0
  DEF_ROMLOC(D9D8) : if (CCR_EQ) goto rom_D9E6;     // BEQ.B	$D9E6
  DEF_ROMLOC(D9DA) : switchindex = D0 - 1;
  add_toreg_16(D0, &D0);                    // ADD.W	D0,D0
  DEF_ROMLOC(D9DC) : add_toreg_16(D0, &D0); // ADD.W	D0,D0
  DEF_ROMLOC(D9DE)
      : move_toreg_32(read_32(0xDA0C + (s16)(D0 & 0xffff)),
                      &A1); // MOVEA.L	44(PC,D0),A1
  // DEF_ROMLOC(D9E2): CALLEMU(A1); // rom_A1(); // JSR	(A1)
  // print("executing object %02x", switchindex);
  DEF_ROMLOC(D9E2) : switch (switchindex) {
  case 0x00:
    rom_132AC();
    break;
  case 0x01:
    rom_DC40();
    break;
  case 0x02:
    rom_DC40();
    break;
  case 0x03:
    rom_DC40();
    break;
  case 0x04:
    rom_DC40();
    break;
  case 0x05:
    rom_DC40();
    break;
  case 0x06:
    rom_DC40();
    break;
  case 0x07:
    rom_14A58();
    break;
  case 0x08:
    rom_1C13A();
    break;
  case 0x09:
    rom_1436C();
    break;
  case 0x0A:
    rom_118DA();
    break;
  case 0x0B:
    rom_11A1A();
    break;
  case 0x0C:
    rom_F1B4();
    break;
  case 0x0D:
    rom_ACA6();
    break;
  case 0x0E:
    rom_AD26();
    break;
  case 0x0F:
    rom_1C7D8();
    break;
  case 0x10:
    rom_79A6();
    break;
  case 0x11:
    rom_EF98();
    break;
  case 0x12:
    rom_E924();
    break;
  case 0x13:
    rom_E992();
    break;
  case 0x14:
    rom_7FD0();
    break;
  case 0x15:
    rom_125D8();
    break;
  case 0x16:
    rom_8320();
    break;
  case 0x17:
    rom_84B0();
    break;
  case 0x18:
    rom_8826();
    break;
  case 0x19:
    rom_888E();
    break;
  case 0x1A:
    rom_1179A();
    break;
  case 0x1B:
    rom_8E48();
    break;
  case 0x1C:
    rom_8EDC();
    break;
  case 0x1D:
    rom_91CA();
    break;
  case 0x1E:
    rom_9B6E();
    break;
  case 0x1F:
    rom_929A();
    break;
  case 0x20:
    rom_1CCFE();
    break;
  case 0x21:
    rom_9E5C();
    break;
  case 0x22:
    rom_9FB0();
    break;
  case 0x23:
    rom_9370();
    break;
  case 0x24:
    rom_A1A4();
    break;
  case 0x25:
    rom_A79A();
    break;
  case 0x26:
    rom_93E0();
    break;
  case 0x27:
    rom_95A0();
    break;
  case 0x28:
    rom_9A90();
    break;
  case 0x29:
    rom_8FB2();
    break;
  case 0x2A:
    rom_B1AA();
    break;
  case 0x2B:
    rom_B264();
    break;
  case 0x2C:
    rom_B32E();
    break;
  case 0x2D:
    rom_A984();
    break;
  case 0x2E:
    rom_B542();
    break;
  case 0x2F:
    rom_BA28();
    break;
  case 0x30:
    rom_BD06();
    break;
  case 0x31:
    rom_C3B8();
    break;
  case 0x32:
    rom_C55C();
    break;
  case 0x33:
    rom_C990();
    break;
  case 0x34:
    rom_B866();
    break;
  case 0x35:
    rom_D4B6();
    break;
  case 0x36:
    rom_A334();
    break;
  case 0x37:
    rom_148C0();
    break;
  case 0x38:
    rom_CB42();
    break;
  case 0x39:
    rom_CC00();
    break;
  case 0x3A:
    rom_D6DE();
    break;
  case 0x3B:
    rom_D7AA();
    break;
  case 0x3C:
    rom_17EAC();
    break;
  case 0x3D:
    rom_1B2D8();
    break;
  case 0x3E:
    rom_9474();
    break;
  case 0x3F:
    rom_FCA6();
    break;
  case 0x40:
    rom_E14C();
    break;
  case 0x41:
    rom_E3F6();
    break;
  case 0x42:
    rom_E688();
    break;
  case 0x43:
    rom_E862();
    break;
  case 0x44:
    rom_C024();
    break;
  case 0x45:
    rom_EE5E();
    break;
  case 0x46:
    rom_F05C();
    break;
  case 0x47:
    rom_18290();
    break;
  case 0x48:
    rom_D74C();
    break;
  case 0x49:
    rom_149BC();
    break;
  case 0x4A:
    rom_A484();
    break;
  case 0x4B:
    rom_F410();
    break;
  case 0x4C:
    rom_F4FC();
    break;
  case 0x4D:
    rom_F6EA();
    break;
  case 0x4E:
    rom_FE92();
    break;
  case 0x4F:
    rom_FEC6();
    break;
  case 0x50:
    rom_1031E();
    break;
  case 0x51:
    rom_10484();
    break;
  case 0x52:
    rom_899E();
    break;
  case 0x53:
    rom_F844();
    break;
  case 0x54:
    rom_10734();
    break;
  case 0x55:
    rom_10912();
    break;
  case 0x56:
    rom_10E56();
    break;
  case 0x57:
    rom_1104A();
    break;
  case 0x58:
    rom_111A6();
    break;
  case 0x59:
    rom_1142E();
    break;
  case 0x5A:
    rom_11564();
    break;
  case 0x5B:
    rom_11718();
    break;
  case 0x5C:
    rom_11BD0();
    break;
  case 0x5D:
    rom_11D10();
    break;
  case 0x5E:
    rom_120CA();
    break;
  case 0x5F:
    rom_123A2();
    break;
  case 0x60:
    rom_126A8();
    break;
  case 0x61:
    rom_128BC();
    break;
  case 0x62:
    rom_12A10();
    break;
  case 0x63:
    rom_12D78();
    break;
  case 0x64:
    rom_13172();
    break;
  case 0x65:
    rom_15802();
    break;
  case 0x66:
    rom_15C4A();
    break;
  case 0x67:
    rom_15DF6();
    break;
  case 0x68:
    rom_15E98();
    break;
  case 0x69:
    rom_160E4();
    break;
  case 0x6A:
    rom_1637A();
    break;
  case 0x6B:
    rom_16760();
    break;
  case 0x6C:
    rom_EB6E();
    break;
  case 0x6D:
    rom_168AE();
    break;
  case 0x6E:
    rom_169D2();
    break;
  case 0x6F:
    rom_16C92();
    break;
  case 0x70:
    rom_11AEE();
    break;
  case 0x71:
    rom_16DD0();
    break;
  case 0x72:
    rom_189E0();
    break;
  case 0x73:
    rom_18E54();
    break;
  case 0x74:
    rom_1989E();
    break;
  case 0x75:
    rom_19E42();
    break;
  case 0x76:
    rom_185E2();
    break;
  case 0x77:
    rom_1709C();
    break;
  case 0x78:
    rom_175DA();
    break;
  case 0x79:
    rom_19068();
    break;
  case 0x7A:
    rom_1947E();
    break;
  case 0x7B:
    rom_A554();
    break;
  case 0x7C:
    rom_1790A();
    break;
  case 0x7D:
    rom_CE3C();
    break;
  case 0x7E:
    rom_CFE4();
    break;
  case 0x7F:
    rom_4E4E();
    break;
  case 0x80:
    rom_4F68();
    break;
  case 0x81:
    rom_19FE2();
    break;
  case 0x82:
    rom_1A310();
    break;
  case 0x83:
    rom_1AC04();
    break;
  case 0x84:
    rom_1A508();
    break;
  case 0x85:
    rom_1AF90();
    break;
  case 0x86:
    rom_53EE();
    break;
  case 0x87:
    rom_5548();
    break;
  case 0x88:
    rom_5622();
    break;
  case 0x89:
    rom_17A10();
    break;
  case 0x8A:
    rom_59F0();
    break;
  case 0x8B:
    rom_5AD0();
    break;
  }
  DEF_ROMLOC(D9E4) : move_toreg_32(0x0, &D0);       // MOVEQ.L	$00,D0
  DEF_ROMLOC(D9E6) : move_toreg_32(A0 + 0x40, &A0); // LEA.L	64(A0),A0
  DEF_ROMLOC(D9EA) : dec_reg_16(&D7);
  if ((D7 & 0xffff) != 0xffff)
    goto rom_D9D6;           // DBF.W	D7,$D9D6
  DEF_ROMLOC(D9EE) : return; // RTS
}
ROMFUNC(rom_D9C6) {
  DEF_ROMLOC(D9C6) : move_toreg_32(0xFFFFD000, &A0); // LEA.L	$D000,A0
  DEF_ROMLOC(D9CA) : move_toreg_32(0x7F, &D7);       // MOVEQ.L	$7F,D7
  DEF_ROMLOC(D9CC) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(D9CE) : cmp_tomem_8(0x6, 0xFFFFD024);   // CMPI.B	#$06,$D024
  DEF_ROMLOC(D9D4) : if (CCR_CC) goto rom_D9F0;      // BCC.B	$D9F0
  rom_D9D6();
  return;
  DEF_ROMLOC(D9F0) : move_toreg_32(0x1F, &D7);      // MOVEQ.L	$1F,D7
  DEF_ROMLOC(D9F2) : rom_D9D6();                    // BSR.B	$D9D6
  DEF_ROMLOC(D9F4) : move_toreg_32(0x5F, &D7);      // MOVEQ.L	$5F,D7
  DEF_ROMLOC(D9F6) : move_toreg_32(0x0, &D0);       // MOVEQ.L	$00,D0
  DEF_ROMLOC(D9F8) : move_toreg_8(read_8(A0), &D0); // MOVE.B	(A0),D0
  DEF_ROMLOC(D9FA) : if (CCR_EQ) goto rom_DA06;     // BEQ.B	$DA06
  DEF_ROMLOC(D9FC) : tst_mem_8(A0 + 0x1);           // TST.B	1(A0)
  DEF_ROMLOC(DA00) : if (CCR_PL) goto rom_DA06;     // BPL.B	$DA06
  DEF_ROMLOC(DA02) : queue_sprite();                // BSR.W	$DC92
  DEF_ROMLOC(DA06) : move_toreg_32(A0 + 0x40, &A0); // LEA.L	64(A0),A0
  DEF_ROMLOC(DA0A) : dec_reg_16(&D7);
  if ((D7 & 0xffff) != 0xffff)
    goto rom_D9F6;           // DBF.W	D7,$D9F6
  DEF_ROMLOC(DA0E) : return; // RTS
}
ROMFUNC(rom_D87C) {
  DEF_ROMLOC(D87C) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(D87E)
      : move_toreg_8(read_8(A0 + 0x1A), &D0); // MOVE.B
                                              // 26(A0),D0
  DEF_ROMLOC(D882) : add_toreg_16(D0, &D0);   // ADD.W	D0,D0
  DEF_ROMLOC(D884)
      : move_toreg_32(read_32(A0 + 0x4), &A3); // MOVEA.L	4(A0),A3
  DEF_ROMLOC(D888)
      : add_toreg_16(read_16((s32)A3 + (s8)0x0 + (s16)D0),
                     &A3);                                // ADDA.W	0(A3,D0),A3
  DEF_ROMLOC(D88C) : add_toreg_16(0x1, &A3);              // ADDQ.W	#$01,A3
  DEF_ROMLOC(D88E) : bset_tomem_8(0x5, A0 + 0x1);         // BSET.B	#$05,1(A0)
  DEF_ROMLOC(D894) : move_toreg_8(read_8(A0 + 0x0), &D4); // MOVE.B	0(A0),D4
  DEF_ROMLOC(D898) : move_toreg_8(read_8(A0 + 0x1), &D5); // MOVE.B	1(A0),D5
  DEF_ROMLOC(D89C) : move_toreg_32(A0, &A1);              // MOVEA.L	A0,A1
  DEF_ROMLOC(D89E) : goto rom_D8A8;                       // BRA.B	$D8A8
  DEF_ROMLOC(D8A0) : rom_E11A();                          // BSR.W	$E11A
  DEF_ROMLOC(D8A4) : if (!CCR_EQ) goto rom_D8FA;          // BNE.B	$D8FA
  DEF_ROMLOC(D8A6) : add_toreg_16(0x5, &A3);              // ADDQ.W	#$05,A3
  DEF_ROMLOC(D8A8) : move_tomem_8(0x4, A1 + 0x24);        // MOVE.B	#$04,36(A1)
  DEF_ROMLOC(D8AE) : move_tomem_8(D4, A1 + 0x0);          // MOVE.B	D4,0(A1)
  DEF_ROMLOC(D8B2) : move_tomem_32(A3, A1 + 0x4);         // MOVE.L	A3,4(A1)
  DEF_ROMLOC(D8B6) : move_tomem_8(D5, A1 + 0x1);          // MOVE.B	D5,1(A1)
  DEF_ROMLOC(D8BA)
      : move_tomem_16(read_16(A0 + 0x8), A1 + 0x8); // MOVE.W	8(A0),8(A1)
  DEF_ROMLOC(D8C0)
      : move_tomem_16(read_16(A0 + 0xC), A1 + 0xC); // MOVE.W	12(A0),12(A1)
  DEF_ROMLOC(D8C6)
      : move_tomem_16(read_16(A0 + 0x2), A1 + 0x2); // MOVE.W	2(A0),2(A1)
  DEF_ROMLOC(D8CC)
      : move_tomem_8(read_8(A0 + 0x18), A1 + 0x18); // MOVE.B	24(A0),24(A1)
  DEF_ROMLOC(D8D2)
      : move_tomem_8(read_8(A0 + 0x19), A1 + 0x19); // MOVE.B	25(A0),25(A1)
  DEF_ROMLOC(D8D8)
      : move_tomem_16(read_16((A4 += 2, A4 - 2)),
                      A1 + 0x10); // MOVE.W	(A4)+,16(A1)
  DEF_ROMLOC(D8DC)
      : move_tomem_16(read_16((A4 += 2, A4 - 2)),
                      A1 + 0x12);                 // MOVE.W	(A4)+,18(A1)
  DEF_ROMLOC(D8E0) : cmp_toreg_32(A0, &A1);       // CMPA.L	A0,A1
  DEF_ROMLOC(D8E2) : if (CCR_CC) goto rom_D8F6;   // BCC.B	$D8F6
  DEF_ROMLOC(D8E4) : move_tomem_32(A0, A7 -= 4);  // MOVE.L	A0,-(A7)
  DEF_ROMLOC(D8E6) : move_toreg_32(A1, &A0);      // MOVEA.L	A1,A0
  DEF_ROMLOC(D8E8) : rom_DC6C();                  // BSR.W	$DC6C
  DEF_ROMLOC(D8EC) : add_tomem_16(D2, A0 + 0x12); // ADD.W	D2,18(A0)
  DEF_ROMLOC(D8F0)
      : move_toreg_32(read_32((A7 += 4, A7 - 4)), &A0); // MOVEA.L	(A7)+,A0
  DEF_ROMLOC(D8F2) : queue_sprite_a1();                        // BSR.W	$DCB0
  DEF_ROMLOC(D8F6) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_D8A0; // DBF.W	D1,$D8A0
  DEF_ROMLOC(D8FA)
      : move_toreg_16(SFX_WALLSMASH, &D0); // MOVE.W
                                           // #$00CB,D0
  DEF_ROMLOC(D8FE) : {
    play_sound_special();
    return;
  } // JMP	$00001394
}