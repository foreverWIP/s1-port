// #define CHECK_STUFF(loc) 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_7ACA) {
  DEF_ROMLOC(7ACA) : move_toreg_32(0xFFFFD000, &A1); // LEA.L	$D000,A1
  DEF_ROMLOC(7ACE) : tst_mem_16(A1 + 0x12);          // TST.W	18(A1)
  DEF_ROMLOC(7AD2) : if (CCR_MI) return;             // BMI.W	$7B9C
  DEF_ROMLOC(7AD6)
      : move_toreg_16(read_16(A1 + 0x8), &D0); // MOVE.W	8(A1),D0
  DEF_ROMLOC(7ADA)
      : sub_toreg_16(read_16(A0 + 0x8), &D0); // SUB.W	8(A0),D0
  DEF_ROMLOC(7ADE) : add_toreg_16(D1, &D0);   // ADD.W	D1,D0
  DEF_ROMLOC(7AE0) : if (CCR_MI) return;      // BMI.W	$7B9C
  DEF_ROMLOC(7AE4) : add_toreg_16(D1, &D1);   // ADD.W	D1,D1
  DEF_ROMLOC(7AE6) : cmp_toreg_16(D1, &D0);   // CMP.W	D1,D0
  DEF_ROMLOC(7AE8) : if (CCR_CC) return;      // BCC.W	$7B9C
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
      : move_toreg_8(read_8(A1 + 0x16), &D1);       // MOVE.B	22(A1),D1
  DEF_ROMLOC(7AFA) : ext_reg_16(&D1);               // EXT.W	D1
  DEF_ROMLOC(7AFC) : add_toreg_16(D2, &D1);         // ADD.W	D2,D1
  DEF_ROMLOC(7AFE) : add_toreg_16(0x4, &D1);        // ADDQ.W	#$04,D1
  DEF_ROMLOC(7B00) : sub_toreg_16(D1, &D0);         // SUB.W	D1,D0
  DEF_ROMLOC(7B02) : if (CCR_HI) return;     // BHI.W	$7B9C
  DEF_ROMLOC(7B06) : cmp_toreg_16(0xFFFFFFF0, &D0); // CMPI.W	#$FFF0,D0
  DEF_ROMLOC(7B0A) : if (CCR_CS) return;     // BCS.W	$7B9C
  DEF_ROMLOC(7B0E) : tst_mem_8(0xFFFFF7C8);         // TST.B	$F7C8
  DEF_ROMLOC(7B12) : if (CCR_MI) return;     // BMI.W	$7B9C
  DEF_ROMLOC(7B16) : cmp_tomem_8(0x6, A1 + 0x24);   // CMPI.B	#$06,36(A1)
  DEF_ROMLOC(7B1C) : if (CCR_CC) return;     // BCC.W	$7B9C
  DEF_ROMLOC(7B20) : add_toreg_16(D0, &D2);         // ADD.W	D0,D2
  DEF_ROMLOC(7B22) : add_toreg_16(0x3, &D2);        // ADDQ.W	#$03,D2
  DEF_ROMLOC(7B24) : move_tomem_16(D2, A1 + 0xC);   // MOVE.W	D2,12(A1)
  DEF_ROMLOC(7B28) : add_tomem_8(0x2, A0 + 0x24);   // ADDQ.B	#$02,36(A0)
  rom_7B2C();
}
ROMFUNC(rom_7B2C) {
  DEF_ROMLOC(7B2C) : btst_tomem_8(0x3, A1 + 0x22);  // BTST.B	#$03,34(A1)
  DEF_ROMLOC(7B32) : if (CCR_EQ) goto rom_7B5A;     // BEQ.B	$7B5A
  DEF_ROMLOC(7B34) : move_toreg_32(0x0, &D0);       // MOVEQ.L	$00,D0
  DEF_ROMLOC(7B36)
      : move_toreg_8(read_8(A1 + 0x3D), &D0);       // MOVE.B	61(A1),D0
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
      : move_toreg_16(read_16(A1 + 0x8), &D0); // MOVE.W	8(A1),D0
  DEF_ROMLOC(7C52)
      : sub_toreg_16(read_16(A0 + 0x8), &D0);      // SUB.W	8(A0),D0
  DEF_ROMLOC(7C56) : add_toreg_16(D1, &D0);        // ADD.W	D1,D0
  DEF_ROMLOC(7C58) : if (CCR_MI) goto rom_7C5E;    // BMI.B	$7C5E
  DEF_ROMLOC(7C5A) : cmp_toreg_16(D2, &D0);        // CMP.W	D2,D0
  DEF_ROMLOC(7C5C) : if (CCR_CS) goto rom_7C70;    // BCS.B	$7C70
  DEF_ROMLOC(7C5E) : bclr_tomem_8(0x3, A1 + 0x22); // BCLR.B	#$03,34(A1)
  DEF_ROMLOC(7C64) : move_tomem_8(0x2, A0 + 0x24); // MOVE.B	#$02,36(A0)
  DEF_ROMLOC(7C6A) : bclr_tomem_8(0x3, A0 + 0x22); // BCLR.B	#$03,34(A0)
  DEF_ROMLOC(7C70) : return;                       // RTS
}
ROMFUNC(rom_7C72) {
  DEF_ROMLOC(7C72) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(7C74)
      : move_toreg_8(read_8(A0 + 0x3F), &D0); // MOVE.B	63(A0),D0
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
      : move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B	40(A0),D0
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
  DEF_ROMLOC(7CF2) : swap_reg_16(&D0);                // SWAP.W	D0
  DEF_ROMLOC(7CF4)
      : add_toreg_16(read_16(A1 + 0x3C), &D0);    // ADD.W	60(A1),D0
  DEF_ROMLOC(7CF8) : move_tomem_16(D0, A1 + 0xC); // MOVE.W	D0,12(A1)
  DEF_ROMLOC(7CFC) : dec_reg_16(&D2);
  if ((D2 & 0xffff) != 0xffff)
    goto rom_7CDA;                            // DBF.W	D2,$7CDA
  DEF_ROMLOC(7D00) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(7D02)
      : move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B	40(A0),D0
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
  DEF_ROMLOC(7D3A) : swap_reg_16(&D0);                // SWAP.W	D0
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
      : move_toreg_16(read_16(A1 + 0x8), &D0); // MOVE.W	8(A1),D0
  DEF_ROMLOC(7BEA)
      : sub_toreg_16(read_16(A0 + 0x8), &D0); // SUB.W	8(A0),D0
  DEF_ROMLOC(7BEE) : add_toreg_16(D1, &D0);   // ADD.W	D1,D0
  DEF_ROMLOC(7BF0) : if (CCR_MI) return;      // BMI.W	$7B9C
  DEF_ROMLOC(7BF4) : add_toreg_16(D1, &D1);   // ADD.W	D1,D1
  DEF_ROMLOC(7BF6) : cmp_toreg_16(D1, &D0);   // CMP.W	D1,D0
  DEF_ROMLOC(7BF8) : if (CCR_CC) return;      // BCC.W	$7B9C
  DEF_ROMLOC(7BFC)
      : move_toreg_16(read_16(A0 + 0xC), &D0); // MOVE.W	12(A0),D0
  DEF_ROMLOC(7C00) : sub_toreg_16(D3, &D0);    // SUB.W	D3,D0
  rom_7AF2();                                  // BRA.W	$7AF2
}
ROMFUNC(rom_DC40) {
  DEF_ROMLOC(DC40): move_toreg_32(read_32(A0 + 0x8), &D2); // MOVE.L	8(A0),D2
  DEF_ROMLOC(DC44): move_toreg_32(read_32(A0 + 0xC), &D3); // MOVE.L	12(A0),D3
  DEF_ROMLOC(DC48): move_toreg_16(read_16(A0 + 0x10), &D0); // MOVE.W	16(A0),D0
  DEF_ROMLOC(DC4C): ext_reg_32(&D0);           // EXT.L	D0
  DEF_ROMLOC(DC4E): asl_toreg_32(0x8, &D0);    // ASL.L	#$08,D0
  DEF_ROMLOC(DC50): add_toreg_32(D0, &D2);     // ADD.L	D0,D2
  DEF_ROMLOC(DC52): move_toreg_16(read_16(A0 + 0x12), &D0);     // MOVE.W	18(A0),D0
  DEF_ROMLOC(DC56): add_tomem_16(0x38, A0 + 0x12); // ADDI.W	#$0038,18(A0)
  DEF_ROMLOC(DC5C): ext_reg_32(&D0);               // EXT.L	D0
  DEF_ROMLOC(DC5E): asl_toreg_32(0x8, &D0);        // ASL.L	#$08,D0
  DEF_ROMLOC(DC60): add_toreg_32(D0, &D3);         // ADD.L	D0,D3
  DEF_ROMLOC(DC62): move_tomem_32(D2, A0 + 0x8);   // MOVE.L	D2,8(A0)
  DEF_ROMLOC(DC66): move_tomem_32(D3, A0 + 0xC);   // MOVE.L	D3,12(A0)
  DEF_ROMLOC(DC6A): return;                        // RTS
}
ROMFUNC(rom_DC6C) {
  DEF_ROMLOC(DC6C): move_toreg_32(read_32(A0 + 0x8), &D2); // MOVE.L	8(A0),D2
  DEF_ROMLOC(DC70): move_toreg_32(read_32(A0 + 0xC), &D3); // MOVE.L	12(A0),D3
  DEF_ROMLOC(DC74): move_toreg_16(read_16(A0 + 0x10), &D0); // MOVE.W	16(A0),D0
  DEF_ROMLOC(DC78): ext_reg_32(&D0);           // EXT.L	D0
  DEF_ROMLOC(DC7A): asl_toreg_32(0x8, &D0);    // ASL.L	#$08,D0
  DEF_ROMLOC(DC7C): add_toreg_32(D0, &D2);     // ADD.L	D0,D2
  DEF_ROMLOC(DC7E): move_toreg_16(read_16(A0 + 0x12), &D0);   // MOVE.W	18(A0),D0
  DEF_ROMLOC(DC82): ext_reg_32(&D0);             // EXT.L	D0
  DEF_ROMLOC(DC84): asl_toreg_32(0x8, &D0);      // ASL.L	#$08,D0
  DEF_ROMLOC(DC86): add_toreg_32(D0, &D3);       // ADD.L	D0,D3
  DEF_ROMLOC(DC88): move_tomem_32(D2, A0 + 0x8); // MOVE.L	D2,8(A0)
  DEF_ROMLOC(DC8C): move_tomem_32(D3, A0 + 0xC); // MOVE.L	D3,12(A0)
  DEF_ROMLOC(DC90): return;                      // RTS
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
  DEF_ROMLOC(DCD4)
      : move_tomem_32(D1, (A1 += 4, A1 - 4)); // MOVE.L	D1,(A1)+
  DEF_ROMLOC(DCD6) : dec_reg_16(&D0);
  if ((D0 & 0xffff) != 0xffff)
    goto rom_DCD4;           // DBF.W	D0,$DCD4
  DEF_ROMLOC(DCDA) : return; // RTS
}
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
  DEF_ROMLOC(DD22)
      : move_toreg_8(read_8(A0 + 0x19), &D0); // MOVE.B	25(A0),D0
  DEF_ROMLOC(DD26)
      : move_toreg_16(read_16(A0 + 0x8), &D3);       // MOVE.W	8(A0),D3
  DEF_ROMLOC(DD2A) : sub_toreg_16(read_16(A1), &D3); // SUB.W	(A1),D3
  DEF_ROMLOC(DD2C) : move_toreg_16(D3, &D1);         // MOVE.W	D3,D1
  DEF_ROMLOC(DD2E) : add_toreg_16(D0, &D1);          // ADD.W	D0,D1
  DEF_ROMLOC(DD30) : if (CCR_MI) goto rom_DDB4;      // BMI.W	$DDB4
  DEF_ROMLOC(DD34) : move_toreg_16(D3, &D1);         // MOVE.W	D3,D1
  DEF_ROMLOC(DD36) : sub_toreg_16(D0, &D1);          // SUB.W	D0,D1
  DEF_ROMLOC(DD38) : cmp_toreg_16(0x140, &D1);       // CMPI.W	#$0140,D1
  DEF_ROMLOC(DD3C) : if (CCR_GE) goto rom_DDB4;      // BGE.B	$DDB4
  DEF_ROMLOC(DD3E) : add_toreg_16(0x80, &D3);        // ADDI.W	#$0080,D3
  DEF_ROMLOC(DD42) : btst_toreg_32(0x4, &D4);        // BTST.L	#$04,D4
  DEF_ROMLOC(DD46) : if (CCR_EQ) goto rom_DD76;      // BEQ.B	$DD76
  DEF_ROMLOC(DD48) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(DD4A)
      : move_toreg_8(read_8(A0 + 0x16), &D0); // MOVE.B	22(A0),D0
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
      : move_toreg_32(read_32(A0 + 0x4), &A1);   // MOVEA.L	4(A0),A1
  DEF_ROMLOC(DD92) : move_toreg_32(0x0, &D1);    // MOVEQ.L	$00,D1
  DEF_ROMLOC(DD94) : btst_toreg_32(0x5, &D4);    // BTST.L	#$05,D4
  DEF_ROMLOC(DD98) : if (!CCR_EQ) goto rom_DDAA; // BNE.B	$DDAA
  DEF_ROMLOC(DD9A)
      : move_toreg_8(read_8(A0 + 0x1A), &D1); // MOVE.B	26(A0),D1
  DEF_ROMLOC(DD9E) : add_toreg_8(D1, &D1);    // ADD.B	D1,D1
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
      : move_tomem_16(D0, (A2 += 2, A2 - 2));          // MOVE.W	D0,(A2)+
  DEF_ROMLOC(DDFE) : move_tomem_8(read_8(A1++), A2++); // MOVE.B
                                                       // (A1)+,(A2)+
  DEF_ROMLOC(DE00) : add_toreg_8(0x1, &D5);            // ADDQ.B	#$01,D5
  DEF_ROMLOC(DE02) : move_tomem_8(D5, A2++);           // MOVE.B	D5,(A2)+
  DEF_ROMLOC(DE04) : move_toreg_8(read_8(A1++), &D0);  // MOVE.B	(A1)+,D0
  DEF_ROMLOC(DE06) : lsl_toreg_16(0x8, &D0);           // LSL.W	#$08,D0
  DEF_ROMLOC(DE08) : move_toreg_8(read_8(A1++), &D0);  // MOVE.B	(A1)+,D0
  DEF_ROMLOC(DE0A) : add_toreg_16(A3, &D0);            // ADD.W	A3,D0
  DEF_ROMLOC(DE0C)
      : move_tomem_16(D0, (A2 += 2, A2 - 2));         // MOVE.W	D0,(A2)+
  DEF_ROMLOC(DE0E) : move_toreg_8(read_8(A1++), &D0); // MOVE.B	(A1)+,D0
  DEF_ROMLOC(DE10) : ext_reg_16(&D0);                 // EXT.W	D0
  DEF_ROMLOC(DE12) : add_toreg_16(D3, &D0);           // ADD.W	D3,D0
  DEF_ROMLOC(DE14) : and_toreg_16(0x1FF, &D0);        // ANDI.W	#$01FF,D0
  DEF_ROMLOC(DE18) : if (!CCR_EQ) goto rom_DE1C;      // BNE.B	$DE1C
  DEF_ROMLOC(DE1A) : add_toreg_16(0x1, &D0);          // ADDQ.W	#$01,D0
  DEF_ROMLOC(DE1C)
      : move_tomem_16(D0, (A2 += 2, A2 - 2)); // MOVE.W	D0,(A2)+
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
      : move_tomem_16(D0, (A2 += 2, A2 - 2));          // MOVE.W	D0,(A2)+
  DEF_ROMLOC(DDFE) : move_tomem_8(read_8(A1++), A2++); // MOVE.B
                                                       // (A1)+,(A2)+
  DEF_ROMLOC(DE00) : add_toreg_8(0x1, &D5);            // ADDQ.B	#$01,D5
  DEF_ROMLOC(DE02) : move_tomem_8(D5, A2++);           // MOVE.B	D5,(A2)+
  DEF_ROMLOC(DE04) : move_toreg_8(read_8(A1++), &D0);  // MOVE.B	(A1)+,D0
  DEF_ROMLOC(DE06) : lsl_toreg_16(0x8, &D0);           // LSL.W	#$08,D0
  DEF_ROMLOC(DE08) : move_toreg_8(read_8(A1++), &D0);  // MOVE.B	(A1)+,D0
  DEF_ROMLOC(DE0A) : add_toreg_16(A3, &D0);            // ADD.W	A3,D0
  DEF_ROMLOC(DE0C)
      : move_tomem_16(D0, (A2 += 2, A2 - 2));         // MOVE.W	D0,(A2)+
  DEF_ROMLOC(DE0E) : move_toreg_8(read_8(A1++), &D0); // MOVE.B	(A1)+,D0
  DEF_ROMLOC(DE10) : ext_reg_16(&D0);                 // EXT.W	D0
  DEF_ROMLOC(DE12) : add_toreg_16(D3, &D0);           // ADD.W	D3,D0
  DEF_ROMLOC(DE14) : and_toreg_16(0x1FF, &D0);        // ANDI.W	#$01FF,D0
  DEF_ROMLOC(DE18) : if (!CCR_EQ) goto rom_DE1C;      // BNE.B	$DE1C
  DEF_ROMLOC(DE1A) : add_toreg_16(0x1, &D0);          // ADDQ.W	#$01,D0
  DEF_ROMLOC(DE1C)
      : move_tomem_16(D0, (A2 += 2, A2 - 2)); // MOVE.W	D0,(A2)+
  DEF_ROMLOC(DE1E) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_DDF0;           // DBF.W	D1,$DDF0
  DEF_ROMLOC(DE22) : return; // RTS

  DEF_ROMLOC(DE24) : btst_toreg_32(0x1, &D4);         // BTST.L	#$01,D4
  DEF_ROMLOC(DE28) : if (!CCR_EQ) goto rom_DEB8;      // BNE.W	$DEB8
  DEF_ROMLOC(DE2C) : cmp_toreg_8(0x50, &D5);          // CMPI.B	#$50,D5
  DEF_ROMLOC(DE30) : if (CCR_EQ) goto rom_DE70;       // BEQ.B	$DE70
  DEF_ROMLOC(DE32) : move_toreg_8(read_8(A1++), &D0); // MOVE.B	(A1)+,D0
  DEF_ROMLOC(DE34) : ext_reg_16(&D0);                 // EXT.W	D0
  DEF_ROMLOC(DE36) : add_toreg_16(D2, &D0);           // ADD.W	D2,D0
  DEF_ROMLOC(DE38)
      : move_tomem_16(D0, (A2 += 2, A2 - 2));         // MOVE.W	D0,(A2)+
  DEF_ROMLOC(DE3A) : move_toreg_8(read_8(A1++), &D4); // MOVE.B	(A1)+,D4
  DEF_ROMLOC(DE3C) : move_tomem_8(D4, A2++);          // MOVE.B	D4,(A2)+
  DEF_ROMLOC(DE3E) : add_toreg_8(0x1, &D5);           // ADDQ.B	#$01,D5
  DEF_ROMLOC(DE40) : move_tomem_8(D5, A2++);          // MOVE.B	D5,(A2)+
  DEF_ROMLOC(DE42) : move_toreg_8(read_8(A1++), &D0); // MOVE.B	(A1)+,D0
  DEF_ROMLOC(DE44) : lsl_toreg_16(0x8, &D0);          // LSL.W	#$08,D0
  DEF_ROMLOC(DE46) : move_toreg_8(read_8(A1++), &D0); // MOVE.B	(A1)+,D0
  DEF_ROMLOC(DE48) : add_toreg_16(A3, &D0);           // ADD.W	A3,D0
  DEF_ROMLOC(DE4A) : eor_toreg_16(0x800, &D0);        // EORI.W	#$0800,D0
  DEF_ROMLOC(DE4E)
      : move_tomem_16(D0, (A2 += 2, A2 - 2));         // MOVE.W	D0,(A2)+
  DEF_ROMLOC(DE50) : move_toreg_8(read_8(A1++), &D0); // MOVE.B	(A1)+,D0
  DEF_ROMLOC(DE52) : ext_reg_16(&D0);                 // EXT.W	D0
  DEF_ROMLOC(DE54) : neg_reg_16(&D0);                 // NEG.W	D0
  DEF_ROMLOC(DE56) : add_toreg_8(D4, &D4);            // ADD.B	D4,D4
  DEF_ROMLOC(DE58) : and_toreg_16(0x18, &D4);         // ANDI.W	#$0018,D4
  DEF_ROMLOC(DE5C) : add_toreg_16(0x8, &D4);          // ADDQ.W	#$08,D4
  DEF_ROMLOC(DE5E) : sub_toreg_16(D4, &D0);           // SUB.W	D4,D0
  DEF_ROMLOC(DE60) : add_toreg_16(D3, &D0);           // ADD.W	D3,D0
  DEF_ROMLOC(DE62) : and_toreg_16(0x1FF, &D0);        // ANDI.W	#$01FF,D0
  DEF_ROMLOC(DE66) : if (!CCR_EQ) goto rom_DE6A;      // BNE.B	$DE6A
  DEF_ROMLOC(DE68) : add_toreg_16(0x1, &D0);          // ADDQ.W	#$01,D0
  DEF_ROMLOC(DE6A)
      : move_tomem_16(D0, (A2 += 2, A2 - 2)); // MOVE.W	D0,(A2)+
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
      : move_tomem_16(D0, (A2 += 2, A2 - 2));          // MOVE.W	D0,(A2)+
  DEF_ROMLOC(DE8E) : move_tomem_8(read_8(A1++), A2++); // MOVE.B
                                                       // (A1)+,(A2)+
  DEF_ROMLOC(DE90) : add_toreg_8(0x1, &D5);            // ADDQ.B	#$01,D5
  DEF_ROMLOC(DE92) : move_tomem_8(D5, A2++);           // MOVE.B	D5,(A2)+
  DEF_ROMLOC(DE94) : move_toreg_8(read_8(A1++), &D0);  // MOVE.B	(A1)+,D0
  DEF_ROMLOC(DE96) : lsl_toreg_16(0x8, &D0);           // LSL.W	#$08,D0
  DEF_ROMLOC(DE98) : move_toreg_8(read_8(A1++), &D0);  // MOVE.B	(A1)+,D0
  DEF_ROMLOC(DE9A) : add_toreg_16(A3, &D0);            // ADD.W	A3,D0
  DEF_ROMLOC(DE9C) : eor_toreg_16(0x1000, &D0);        // EORI.W	#$1000,D0
  DEF_ROMLOC(DEA0)
      : move_tomem_16(D0, (A2 += 2, A2 - 2));         // MOVE.W	D0,(A2)+
  DEF_ROMLOC(DEA2) : move_toreg_8(read_8(A1++), &D0); // MOVE.B	(A1)+,D0
  DEF_ROMLOC(DEA4) : ext_reg_16(&D0);                 // EXT.W	D0
  DEF_ROMLOC(DEA6) : add_toreg_16(D3, &D0);           // ADD.W	D3,D0
  DEF_ROMLOC(DEA8) : and_toreg_16(0x1FF, &D0);        // ANDI.W	#$01FF,D0
  DEF_ROMLOC(DEAC) : if (!CCR_EQ) goto rom_DEB0;      // BNE.B	$DEB0
  DEF_ROMLOC(DEAE) : add_toreg_16(0x1, &D0);          // ADDQ.W	#$01,D0
  DEF_ROMLOC(DEB0)
      : move_tomem_16(D0, (A2 += 2, A2 - 2)); // MOVE.W	D0,(A2)+
  DEF_ROMLOC(DEB2) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_DE72;           // DBF.W	D1,$DE72
  DEF_ROMLOC(DEB6) : return; // RTS

  DEF_ROMLOC(DEB8) : cmp_toreg_8(0x50, &D5);          // CMPI.B	#$50,D5
  DEF_ROMLOC(DEBC) : if (CCR_EQ) goto rom_DF0A;       // BEQ.B	$DF0A
  DEF_ROMLOC(DEBE) : move_toreg_8(read_8(A1++), &D0); // MOVE.B	(A1)+,D0
  DEF_ROMLOC(DEC0) : move_toreg_8(read_8(A1), &D4);   // MOVE.B	(A1),D4
  DEF_ROMLOC(DEC2) : ext_reg_16(&D0);                 // EXT.W	D0
  DEF_ROMLOC(DEC4) : neg_reg_16(&D0);                 // NEG.W	D0
  DEF_ROMLOC(DEC6) : lsl_toreg_8(0x3, &D4);           // LSL.B	#$03,D4
  DEF_ROMLOC(DEC8) : and_toreg_16(0x18, &D4);         // ANDI.W	#$0018,D4
  DEF_ROMLOC(DECC) : add_toreg_16(0x8, &D4);          // ADDQ.W	#$08,D4
  DEF_ROMLOC(DECE) : sub_toreg_16(D4, &D0);           // SUB.W	D4,D0
  DEF_ROMLOC(DED0) : add_toreg_16(D2, &D0);           // ADD.W	D2,D0
  DEF_ROMLOC(DED2)
      : move_tomem_16(D0, (A2 += 2, A2 - 2));         // MOVE.W	D0,(A2)+
  DEF_ROMLOC(DED4) : move_toreg_8(read_8(A1++), &D4); // MOVE.B	(A1)+,D4
  DEF_ROMLOC(DED6) : move_tomem_8(D4, A2++);          // MOVE.B	D4,(A2)+
  DEF_ROMLOC(DED8) : add_toreg_8(0x1, &D5);           // ADDQ.B	#$01,D5
  DEF_ROMLOC(DEDA) : move_tomem_8(D5, A2++);          // MOVE.B	D5,(A2)+
  DEF_ROMLOC(DEDC) : move_toreg_8(read_8(A1++), &D0); // MOVE.B	(A1)+,D0
  DEF_ROMLOC(DEDE) : lsl_toreg_16(0x8, &D0);          // LSL.W	#$08,D0
  DEF_ROMLOC(DEE0) : move_toreg_8(read_8(A1++), &D0); // MOVE.B	(A1)+,D0
  DEF_ROMLOC(DEE2) : add_toreg_16(A3, &D0);           // ADD.W	A3,D0
  DEF_ROMLOC(DEE4) : eor_toreg_16(0x1800, &D0);       // EORI.W	#$1800,D0
  DEF_ROMLOC(DEE8)
      : move_tomem_16(D0, (A2 += 2, A2 - 2));         // MOVE.W	D0,(A2)+
  DEF_ROMLOC(DEEA) : move_toreg_8(read_8(A1++), &D0); // MOVE.B	(A1)+,D0
  DEF_ROMLOC(DEEC) : ext_reg_16(&D0);                 // EXT.W	D0
  DEF_ROMLOC(DEEE) : neg_reg_16(&D0);                 // NEG.W	D0
  DEF_ROMLOC(DEF0) : add_toreg_8(D4, &D4);            // ADD.B	D4,D4
  DEF_ROMLOC(DEF2) : and_toreg_16(0x18, &D4);         // ANDI.W	#$0018,D4
  DEF_ROMLOC(DEF6) : add_toreg_16(0x8, &D4);          // ADDQ.W	#$08,D4
  DEF_ROMLOC(DEF8) : sub_toreg_16(D4, &D0);           // SUB.W	D4,D0
  DEF_ROMLOC(DEFA) : add_toreg_16(D3, &D0);           // ADD.W	D3,D0
  DEF_ROMLOC(DEFC) : and_toreg_16(0x1FF, &D0);        // ANDI.W	#$01FF,D0
  DEF_ROMLOC(DF00) : if (!CCR_EQ) goto rom_DF04;      // BNE.B	$DF04
  DEF_ROMLOC(DF02) : add_toreg_16(0x1, &D0);          // ADDQ.W	#$01,D0
  DEF_ROMLOC(DF04)
      : move_tomem_16(D0, (A2 += 2, A2 - 2)); // MOVE.W	D0,(A2)+
  DEF_ROMLOC(DF06) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_DEB8;           // DBF.W	D1,$DEB8
  DEF_ROMLOC(DF0A) : return; // RTS
}
ROMFUNC(rom_DF0C) {
  DEF_ROMLOC(DF0C)
      : move_toreg_16(read_16(A0 + 0x8), &D0); // MOVE.W	8(A0),D0
  DEF_ROMLOC(DF10)
      : sub_toreg_16(read_16(0xFFFFF700), &D0); // SUB.W	$F700,D0
  DEF_ROMLOC(DF14) : if (CCR_MI) goto rom_DF30; // BMI.B	$DF30
  DEF_ROMLOC(DF16) : cmp_toreg_16(0x140, &D0);  // CMPI.W	#$0140,D0
  DEF_ROMLOC(DF1A) : if (CCR_GE) goto rom_DF30; // BGE.B	$DF30
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
      : move_toreg_8(read_8(A0 + 0x19), &D1); // MOVE.B	25(A0),D1
  DEF_ROMLOC(DF3A)
      : move_toreg_16(read_16(A0 + 0x8), &D0); // MOVE.W	8(A0),D0
  DEF_ROMLOC(DF3E)
      : sub_toreg_16(read_16(0xFFFFF700), &D0); // SUB.W	$F700,D0
  DEF_ROMLOC(DF42) : add_toreg_16(D1, &D0);     // ADD.W	D1,D0
  DEF_ROMLOC(DF44) : if (CCR_MI) goto rom_DF64; // BMI.B	$DF64
  DEF_ROMLOC(DF46) : add_toreg_16(D1, &D1);     // ADD.W	D1,D1
  DEF_ROMLOC(DF48) : sub_toreg_16(D1, &D0);     // SUB.W	D1,D0
  DEF_ROMLOC(DF4A) : cmp_toreg_16(0x140, &D0);  // CMPI.W	#$0140,D0
  DEF_ROMLOC(DF4E) : if (CCR_GE) goto rom_DF64; // BGE.B	$DF64
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
  DEF_ROMLOC(DF7A) : add_tomem_8(0x2, 0xFFFFF76C); // ADDQ.B	#$02,$F76C
  DEF_ROMLOC(DF7E)
      : move_toreg_16(read_16(0xFFFFFE10), &D0);  // MOVE.W	$FE10,D0
  DEF_ROMLOC(DF82) : lsl_toreg_8(0x6, &D0);       // LSL.B	#$06,D0
  DEF_ROMLOC(DF84) : lsr_toreg_16(0x4, &D0);      // LSR.W	#$04,D0
  DEF_ROMLOC(DF86) : move_toreg_32(0x6B000, &A0); // LEA.L	$0006B000,A0
  DEF_ROMLOC(DF8C) : move_toreg_32(A0, &A1);      // MOVEA.L	A0,A1
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
      : move_toreg_16(read_16(0xFFFFF700), &D6);    // MOVE.W	$F700,D6
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
      : move_toreg_16(read_16(0xFFFFF700), &D6);    // MOVE.W	$F700,D6
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
      : cmp_toreg_16(read_16(A0 - 0x6), &D6);    // CMP.W	-6(A0),D6
  DEF_ROMLOC(E038) : if (CCR_GE) goto rom_E060;  // BGE.B	$E060
  DEF_ROMLOC(E03A) : sub_toreg_16(0x6, &A0);     // SUBQ.W	#$06,A0
  DEF_ROMLOC(E03C) : tst_mem_8(A0 + 0x4);        // TST.B	4(A0)
  DEF_ROMLOC(E040) : if (CCR_PL) goto rom_E04A;  // BPL.B	$E04A
  DEF_ROMLOC(E042) : sub_tomem_8(0x1, A2 + 0x1); // SUBQ.B	#$01,1(A2)
  DEF_ROMLOC(E046)
      : move_toreg_8(read_8(A2 + 0x1), &D2);        // MOVE.B	1(A2),D2
  DEF_ROMLOC(E04A) : rom_E0CA();                    // BSR.W	$E0CA
  DEF_ROMLOC(E04E) : if (!CCR_EQ) goto rom_E054;    // BNE.B	$E054
  DEF_ROMLOC(E050) : sub_toreg_16(0x6, &A0);        // SUBQ.W	#$06,A0
  goto rom_E034;                                    // BRA.B	$E034
  DEF_ROMLOC(E054) : tst_mem_8(A0 + 0x4);           // TST.B	4(A0)
  DEF_ROMLOC(E058) : if (CCR_PL) goto rom_E05E;     // BPL.B	$E05E
  DEF_ROMLOC(E05A) : add_tomem_8(0x1, A2 + 0x1);    // ADDQ.B	#$01,1(A2)
  DEF_ROMLOC(E05E) : add_toreg_16(0x6, &A0);        // ADDQ.W	#$06,A0
  DEF_ROMLOC(E060) : move_tomem_32(A0, 0xFFFFF774); // MOVE.L	A0,$F774
  DEF_ROMLOC(E064)
      : move_toreg_32(read_32(0xFFFFF770), &A0); // MOVEA.L	$F770,A0
  DEF_ROMLOC(E068) : add_toreg_16(0x300, &D6);   // ADDI.W	#$0300,D6
  DEF_ROMLOC(E06C)
      : cmp_toreg_16(read_16(A0 - 0x6), &D6);       // CMP.W	-6(A0),D6
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
  DEF_ROMLOC(FD38)
      : move_toreg_16(read_16(A0 + 0x8), &D0);      // MOVE.W	8(A0),D0
  DEF_ROMLOC(FD3C) : and_toreg_16(0xFFFFFF80, &D0); // ANDI.W	#$FF80,D0
  DEF_ROMLOC(FD40)
      : move_toreg_16(read_16(0xFFFFF700), &D1);    // MOVE.W	$F700,D1
  DEF_ROMLOC(FD44) : sub_toreg_16(0x80, &D1);       // SUBI.W	#$0080,D1
  DEF_ROMLOC(FD48) : and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
  DEF_ROMLOC(FD4C) : sub_toreg_16(D1, &D0);         // SUB.W	D1,D0
  DEF_ROMLOC(FD4E) : cmp_toreg_16(0x280, &D0);      // CMPI.W	#$0280,D0
  DEF_ROMLOC(FD52) : if (CCR_HI) goto rom_FD5A;     // BHI.W	$FD5A
  DEF_ROMLOC(FD56) : {
    rom_DC92();
    return;
  }                                                  // BRA.W	$DC92
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
ROMFUNC(rom_150C4) {
  DEF_ROMLOC(150C4) : move_toreg_16(D2, &D0);         // MOVE.W	D2,D0
  DEF_ROMLOC(150C6) : lsr_toreg_16(0x1, &D0);         // LSR.W	#$01,D0
  DEF_ROMLOC(150C8) : and_toreg_16(0x380, &D0);       // ANDI.W	#$0380,D0
  DEF_ROMLOC(150CC) : move_toreg_16(D3, &D1);         // MOVE.W	D3,D1
  DEF_ROMLOC(150CE) : lsr_toreg_16(0x8, &D1);         // LSR.W	#$08,D1
  DEF_ROMLOC(150D0) : and_toreg_16(0x7F, &D1);        // ANDI.W	#$007F,D1
  DEF_ROMLOC(150D4) : add_toreg_16(D1, &D0);          // ADD.W	D1,D0
  DEF_ROMLOC(150D6) : move_toreg_32(0xFFFFFFFF, &D1); // MOVEQ.L	$FF,D1
  DEF_ROMLOC(150D8) : move_toreg_32(0xFFFFA400, &A1); // LEA.L	$A400,A1
  DEF_ROMLOC(150DC)
      : move_toreg_8(read_8((s32)A1 + (s8)0x0 + (s16)D0),
                     &D1);                         // MOVE.B	0(A1,D0),D1
  DEF_ROMLOC(150E0) : if (CCR_EQ) goto rom_150FE;  // BEQ.B	$150FE
  DEF_ROMLOC(150E2) : if (CCR_MI) goto rom_15102;  // BMI.B	$15102
  DEF_ROMLOC(150E4) : sub_toreg_8(0x1, &D1);       // SUBQ.B	#$01,D1
  DEF_ROMLOC(150E6) : ext_reg_16(&D1);             // EXT.W	D1
  DEF_ROMLOC(150E8) : ror_toreg_16(0x7, &D1);      // ROR.W	#$07,D1
  DEF_ROMLOC(150EA) : move_toreg_16(D2, &D0);      // MOVE.W	D2,D0
  DEF_ROMLOC(150EC) : add_toreg_16(D0, &D0);       // ADD.W	D0,D0
  DEF_ROMLOC(150EE) : and_toreg_16(0x1E0, &D0);    // ANDI.W	#$01E0,D0
  DEF_ROMLOC(150F2) : add_toreg_16(D0, &D1);       // ADD.W	D0,D1
  DEF_ROMLOC(150F4) : move_toreg_16(D3, &D0);      // MOVE.W	D3,D0
  DEF_ROMLOC(150F6) : lsr_toreg_16(0x3, &D0);      // LSR.W	#$03,D0
  DEF_ROMLOC(150F8) : and_toreg_16(0x1E, &D0);     // ANDI.W	#$001E,D0
  DEF_ROMLOC(150FC) : add_toreg_16(D0, &D1);       // ADD.W	D0,D1
  DEF_ROMLOC(150FE) : move_toreg_32(D1, &A1);      // MOVEA.L	D1,A1
  DEF_ROMLOC(15100) : return;                      // RTS
  DEF_ROMLOC(15102) : and_toreg_16(0x7F, &D1);     // ANDI.W	#$007F,D1
  DEF_ROMLOC(15106) : btst_tomem_8(0x6, A0 + 0x1); // BTST.B	#$06,1(A0)
  DEF_ROMLOC(1510C) : if (CCR_EQ) goto rom_1511A;  // BEQ.B	$1511A
  DEF_ROMLOC(1510E) : add_toreg_16(0x1, &D1);      // ADDQ.W	#$01,D1
  DEF_ROMLOC(15110) : cmp_toreg_16(0x29, &D1);     // CMPI.W	#$0029,D1
  DEF_ROMLOC(15114) : if (!CCR_EQ) goto rom_1511A; // BNE.B	$1511A
  DEF_ROMLOC(15116) : move_toreg_16(0x51, &D1);    // MOVE.W	#$0051,D1
  DEF_ROMLOC(1511A) : sub_toreg_8(0x1, &D1);       // SUBQ.B	#$01,D1
  DEF_ROMLOC(1511C) : ror_toreg_16(0x7, &D1);      // ROR.W	#$07,D1
  DEF_ROMLOC(1511E) : move_toreg_16(D2, &D0);      // MOVE.W	D2,D0
  DEF_ROMLOC(15120) : add_toreg_16(D0, &D0);       // ADD.W	D0,D0
  DEF_ROMLOC(15122) : and_toreg_16(0x1E0, &D0);    // ANDI.W	#$01E0,D0
  DEF_ROMLOC(15126) : add_toreg_16(D0, &D1);       // ADD.W	D0,D1
  DEF_ROMLOC(15128) : move_toreg_16(D3, &D0);      // MOVE.W	D3,D0
  DEF_ROMLOC(1512A) : lsr_toreg_16(0x3, &D0);      // LSR.W	#$03,D0
  DEF_ROMLOC(1512C) : and_toreg_16(0x1E, &D0);     // ANDI.W	#$001E,D0
  DEF_ROMLOC(15130) : add_toreg_16(D0, &D1);       // ADD.W	D0,D1
  DEF_ROMLOC(15132) : move_toreg_32(D1, &A1);      // MOVEA.L	D1,A1
  DEF_ROMLOC(15134) : return;                      // RTS
}
ROMFUNC(rom_15136) {
  DEF_ROMLOC(15136) : rom_150C4();                     // BSR.B	$150C4
  DEF_ROMLOC(15138) : move_toreg_16(read_16(A1), &D0); // MOVE.W	(A1),D0
  DEF_ROMLOC(1513A) : move_toreg_16(D0, &D4);          // MOVE.W	D0,D4
  DEF_ROMLOC(1513C) : and_toreg_16(0x7FF, &D0);        // ANDI.W	#$07FF,D0
  DEF_ROMLOC(15140) : if (CCR_EQ) goto rom_15146;      // BEQ.B	$15146
  DEF_ROMLOC(15142) : btst_toreg_32(D5, &D4);          // BTST.L	D5,D4
  DEF_ROMLOC(15144) : if (!CCR_EQ) goto rom_15154;     // BNE.B	$15154
  DEF_ROMLOC(15146) : add_toreg_16(A3, &D2);           // ADD.W	A3,D2
  DEF_ROMLOC(15148) : rom_151DC();                     // BSR.W	$151DC
  DEF_ROMLOC(1514C) : sub_toreg_16(A3, &D2);           // SUB.W	A3,D2
  DEF_ROMLOC(1514E) : add_toreg_16(0x10, &D1);         // ADDI.W	#$0010,D1
  DEF_ROMLOC(15152) : return;                          // RTS
  DEF_ROMLOC(15154)
      : move_toreg_32(read_32(0xFFFFF796), &A2); // MOVEA.L	$F796,A2
  DEF_ROMLOC(15158)
      : move_toreg_8(read_8((s32)A2 + (s8)0x0 + (s16)D0),
                     &D0);                         // MOVE.B	0(A2,D0),D0
  DEF_ROMLOC(1515C) : and_toreg_16(0xFF, &D0);     // ANDI.W	#$00FF,D0
  DEF_ROMLOC(15160) : if (CCR_EQ) goto rom_15146;  // BEQ.B	$15146
  DEF_ROMLOC(15162) : move_toreg_32(0x62900, &A2); // LEA.L	$00062900,A2
  DEF_ROMLOC(15168)
      : move_tomem_8(read_8((s32)A2 + (s8)0x0 + (s16)D0),
                     A4);                          // MOVE.B	0(A2,D0),(A4)
  DEF_ROMLOC(1516C) : lsl_toreg_16(0x4, &D0);      // LSL.W	#$04,D0
  DEF_ROMLOC(1516E) : move_toreg_16(D3, &D1);      // MOVE.W	D3,D1
  DEF_ROMLOC(15170) : btst_toreg_32(0xB, &D4);     // BTST.L	#$0B,D4
  DEF_ROMLOC(15174) : if (CCR_EQ) goto rom_1517A;  // BEQ.B	$1517A
  DEF_ROMLOC(15176) : not_reg_16(&D1);             // NOT.W	D1
  DEF_ROMLOC(15178) : neg_mem_8(A4);               // NEG.B	(A4)
  DEF_ROMLOC(1517A) : btst_toreg_32(0xC, &D4);     // BTST.L	#$0C,D4
  DEF_ROMLOC(1517E) : if (CCR_EQ) goto rom_1518A;  // BEQ.B	$1518A
  DEF_ROMLOC(15180) : add_tomem_8(0x40, A4);       // ADDI.B	#$40,(A4)
  DEF_ROMLOC(15184) : neg_mem_8(A4);               // NEG.B	(A4)
  DEF_ROMLOC(15186) : sub_tomem_8(0x40, A4);       // SUBI.B	#$40,(A4)
  DEF_ROMLOC(1518A) : and_toreg_16(0xF, &D1);      // ANDI.W	#$000F,D1
  DEF_ROMLOC(1518E) : add_toreg_16(D0, &D1);       // ADD.W	D0,D1
  DEF_ROMLOC(15190) : move_toreg_32(0x62A00, &A2); // LEA.L	$00062A00,A2
  DEF_ROMLOC(15196)
      : move_toreg_8(read_8((s32)A2 + (s8)0x0 + (s16)D1),
                     &D0);                        // MOVE.B	0(A2,D1),D0
  DEF_ROMLOC(1519A) : ext_reg_16(&D0);            // EXT.W	D0
  DEF_ROMLOC(1519C) : eor_toreg_16(D6, &D4);      // EOR.W	D6,D4
  DEF_ROMLOC(1519E) : btst_toreg_32(0xC, &D4);    // BTST.L	#$0C,D4
  DEF_ROMLOC(151A2) : if (CCR_EQ) goto rom_151A6; // BEQ.B	$151A6
  DEF_ROMLOC(151A4) : neg_reg_16(&D0);            // NEG.W	D0
  DEF_ROMLOC(151A6) : tst_reg_16(&D0);            // TST.W	D0
  DEF_ROMLOC(151A8) : if (CCR_EQ) goto rom_15146; // BEQ.B	$15146
  DEF_ROMLOC(151AA) : if (CCR_MI) goto rom_151C2; // BMI.B	$151C2
  DEF_ROMLOC(151AC) : cmp_toreg_8(0x10, &D0);     // CMPI.B	#$10,D0
  DEF_ROMLOC(151B0) : if (CCR_EQ) goto rom_151CE; // BEQ.B	$151CE
  DEF_ROMLOC(151B2) : move_toreg_16(D2, &D1);     // MOVE.W	D2,D1
  DEF_ROMLOC(151B4) : and_toreg_16(0xF, &D1);     // ANDI.W	#$000F,D1
  DEF_ROMLOC(151B8) : add_toreg_16(D1, &D0);      // ADD.W	D1,D0
  DEF_ROMLOC(151BA) : move_toreg_16(0xF, &D1);    // MOVE.W	#$000F,D1
  DEF_ROMLOC(151BE) : sub_toreg_16(D0, &D1);      // SUB.W	D0,D1
  DEF_ROMLOC(151C0) : return;                     // RTS
  DEF_ROMLOC(151C2) : move_toreg_16(D2, &D1);     // MOVE.W	D2,D1
  DEF_ROMLOC(151C4) : and_toreg_16(0xF, &D1);     // ANDI.W	#$000F,D1
  DEF_ROMLOC(151C8) : add_toreg_16(D1, &D0);      // ADD.W	D1,D0
  DEF_ROMLOC(151CA) : if (CCR_PL) goto rom_15146; // BPL.W	$15146
  DEF_ROMLOC(151CE) : sub_toreg_16(A3, &D2);      // SUB.W	A3,D2
  DEF_ROMLOC(151D0) : rom_151DC();                // BSR.W	$151DC
  DEF_ROMLOC(151D4) : add_toreg_16(A3, &D2);      // ADD.W	A3,D2
  DEF_ROMLOC(151D6) : sub_toreg_16(0x10, &D1);    // SUBI.W	#$0010,D1
  DEF_ROMLOC(151DA) : return;                     // RTS
}
ROMFUNC(rom_151DC) {
  DEF_ROMLOC(151DC) : rom_150C4();                     // BSR.W	$150C4
  DEF_ROMLOC(151E0) : move_toreg_16(read_16(A1), &D0); // MOVE.W	(A1),D0
  DEF_ROMLOC(151E2) : move_toreg_16(D0, &D4);          // MOVE.W	D0,D4
  DEF_ROMLOC(151E4) : and_toreg_16(0x7FF, &D0);        // ANDI.W	#$07FF,D0
  DEF_ROMLOC(151E8) : if (CCR_EQ) goto rom_151EE;      // BEQ.B	$151EE
  DEF_ROMLOC(151EA) : btst_toreg_32(D5, &D4);          // BTST.L	D5,D4
  DEF_ROMLOC(151EC) : if (!CCR_EQ) goto rom_151FC;     // BNE.B	$151FC
  DEF_ROMLOC(151EE) : move_toreg_16(0xF, &D1);         // MOVE.W	#$000F,D1
  DEF_ROMLOC(151F2) : move_toreg_16(D2, &D0);          // MOVE.W	D2,D0
  DEF_ROMLOC(151F4) : and_toreg_16(0xF, &D0);          // ANDI.W	#$000F,D0
  DEF_ROMLOC(151F8) : sub_toreg_16(D0, &D1);           // SUB.W	D0,D1
  DEF_ROMLOC(151FA) : return;                          // RTS
  DEF_ROMLOC(151FC)
      : move_toreg_32(read_32(0xFFFFF796), &A2); // MOVEA.L	$F796,A2
  DEF_ROMLOC(15200)
      : move_toreg_8(read_8((s32)A2 + (s8)0x0 + (s16)D0),
                     &D0);                         // MOVE.B	0(A2,D0),D0
  DEF_ROMLOC(15204) : and_toreg_16(0xFF, &D0);     // ANDI.W	#$00FF,D0
  DEF_ROMLOC(15208) : if (CCR_EQ) goto rom_151EE;  // BEQ.B	$151EE
  DEF_ROMLOC(1520A) : move_toreg_32(0x62900, &A2); // LEA.L	$00062900,A2
  DEF_ROMLOC(15210)
      : move_tomem_8(read_8((s32)A2 + (s8)0x0 + (s16)D0),
                     A4);                          // MOVE.B	0(A2,D0),(A4)
  DEF_ROMLOC(15214) : lsl_toreg_16(0x4, &D0);      // LSL.W	#$04,D0
  DEF_ROMLOC(15216) : move_toreg_16(D3, &D1);      // MOVE.W	D3,D1
  DEF_ROMLOC(15218) : btst_toreg_32(0xB, &D4);     // BTST.L	#$0B,D4
  DEF_ROMLOC(1521C) : if (CCR_EQ) goto rom_15222;  // BEQ.B	$15222
  DEF_ROMLOC(1521E) : not_reg_16(&D1);             // NOT.W	D1
  DEF_ROMLOC(15220) : neg_mem_8(A4);               // NEG.B	(A4)
  DEF_ROMLOC(15222) : btst_toreg_32(0xC, &D4);     // BTST.L	#$0C,D4
  DEF_ROMLOC(15226) : if (CCR_EQ) goto rom_15232;  // BEQ.B	$15232
  DEF_ROMLOC(15228) : add_tomem_8(0x40, A4);       // ADDI.B	#$40,(A4)
  DEF_ROMLOC(1522C) : neg_mem_8(A4);               // NEG.B	(A4)
  DEF_ROMLOC(1522E) : sub_tomem_8(0x40, A4);       // SUBI.B	#$40,(A4)
  DEF_ROMLOC(15232) : and_toreg_16(0xF, &D1);      // ANDI.W	#$000F,D1
  DEF_ROMLOC(15236) : add_toreg_16(D0, &D1);       // ADD.W	D0,D1
  DEF_ROMLOC(15238) : move_toreg_32(0x62A00, &A2); // LEA.L	$00062A00,A2
  DEF_ROMLOC(1523E)
      : move_toreg_8(read_8((s32)A2 + (s8)0x0 + (s16)D1),
                     &D0);                        // MOVE.B	0(A2,D1),D0
  DEF_ROMLOC(15242) : ext_reg_16(&D0);            // EXT.W	D0
  DEF_ROMLOC(15244) : eor_toreg_16(D6, &D4);      // EOR.W	D6,D4
  DEF_ROMLOC(15246) : btst_toreg_32(0xC, &D4);    // BTST.L	#$0C,D4
  DEF_ROMLOC(1524A) : if (CCR_EQ) goto rom_1524E; // BEQ.B	$1524E
  DEF_ROMLOC(1524C) : neg_reg_16(&D0);            // NEG.W	D0
  DEF_ROMLOC(1524E) : tst_reg_16(&D0);            // TST.W	D0
  DEF_ROMLOC(15250) : if (CCR_EQ) goto rom_151EE; // BEQ.B	$151EE
  DEF_ROMLOC(15252) : if (CCR_MI) goto rom_15264; // BMI.B	$15264
  DEF_ROMLOC(15254) : move_toreg_16(D2, &D1);     // MOVE.W	D2,D1
  DEF_ROMLOC(15256) : and_toreg_16(0xF, &D1);     // ANDI.W	#$000F,D1
  DEF_ROMLOC(1525A) : add_toreg_16(D1, &D0);      // ADD.W	D1,D0
  DEF_ROMLOC(1525C) : move_toreg_16(0xF, &D1);    // MOVE.W	#$000F,D1
  DEF_ROMLOC(15260) : sub_toreg_16(D0, &D1);      // SUB.W	D0,D1
  DEF_ROMLOC(15262) : return;                     // RTS
  DEF_ROMLOC(15264) : move_toreg_16(D2, &D1);     // MOVE.W	D2,D1
  DEF_ROMLOC(15266) : and_toreg_16(0xF, &D1);     // ANDI.W	#$000F,D1
  DEF_ROMLOC(1526A) : add_toreg_16(D1, &D0);      // ADD.W	D1,D0
  DEF_ROMLOC(1526C) : if (CCR_PL) goto rom_151EE; // BPL.W	$151EE
  DEF_ROMLOC(15270) : not_reg_16(&D1);            // NOT.W	D1
  DEF_ROMLOC(15272) : return;                     // RTS
}
ROMFUNC(rom_15274) {
  DEF_ROMLOC(15274) : rom_150C4();                     // BSR.W	$150C4
  DEF_ROMLOC(15278) : move_toreg_16(read_16(A1), &D0); // MOVE.W	(A1),D0
  DEF_ROMLOC(1527A) : move_toreg_16(D0, &D4);          // MOVE.W	D0,D4
  DEF_ROMLOC(1527C) : and_toreg_16(0x7FF, &D0);        // ANDI.W	#$07FF,D0
  DEF_ROMLOC(15280) : if (CCR_EQ) goto rom_15286;      // BEQ.B	$15286
  DEF_ROMLOC(15282) : btst_toreg_32(D5, &D4);          // BTST.L	D5,D4
  DEF_ROMLOC(15284) : if (!CCR_EQ) goto rom_15294;     // BNE.B	$15294
  DEF_ROMLOC(15286) : add_toreg_16(A3, &D3);           // ADD.W	A3,D3
  DEF_ROMLOC(15288) : rom_1531C();                     // BSR.W	$1531C
  DEF_ROMLOC(1528C) : sub_toreg_16(A3, &D3);           // SUB.W	A3,D3
  DEF_ROMLOC(1528E) : add_toreg_16(0x10, &D1);         // ADDI.W	#$0010,D1
  DEF_ROMLOC(15292) : return;                          // RTS
  DEF_ROMLOC(15294)
      : move_toreg_32(read_32(0xFFFFF796), &A2); // MOVEA.L	$F796,A2
  DEF_ROMLOC(15298)
      : move_toreg_8(read_8((s32)A2 + (s8)0x0 + (s16)D0),
                     &D0);                         // MOVE.B	0(A2,D0),D0
  DEF_ROMLOC(1529C) : and_toreg_16(0xFF, &D0);     // ANDI.W	#$00FF,D0
  DEF_ROMLOC(152A0) : if (CCR_EQ) goto rom_15286;  // BEQ.B	$15286
  DEF_ROMLOC(152A2) : move_toreg_32(0x62900, &A2); // LEA.L	$00062900,A2
  DEF_ROMLOC(152A8)
      : move_tomem_8(read_8((s32)A2 + (s8)0x0 + (s16)D0),
                     A4);                          // MOVE.B	0(A2,D0),(A4)
  DEF_ROMLOC(152AC) : lsl_toreg_16(0x4, &D0);      // LSL.W	#$04,D0
  DEF_ROMLOC(152AE) : move_toreg_16(D2, &D1);      // MOVE.W	D2,D1
  DEF_ROMLOC(152B0) : btst_toreg_32(0xC, &D4);     // BTST.L	#$0C,D4
  DEF_ROMLOC(152B4) : if (CCR_EQ) goto rom_152C2;  // BEQ.B	$152C2
  DEF_ROMLOC(152B6) : not_reg_16(&D1);             // NOT.W	D1
  DEF_ROMLOC(152B8) : add_tomem_8(0x40, A4);       // ADDI.B	#$40,(A4)
  DEF_ROMLOC(152BC) : neg_mem_8(A4);               // NEG.B	(A4)
  DEF_ROMLOC(152BE) : sub_tomem_8(0x40, A4);       // SUBI.B	#$40,(A4)
  DEF_ROMLOC(152C2) : btst_toreg_32(0xB, &D4);     // BTST.L	#$0B,D4
  DEF_ROMLOC(152C6) : if (CCR_EQ) goto rom_152CA;  // BEQ.B	$152CA
  DEF_ROMLOC(152C8) : neg_mem_8(A4);               // NEG.B	(A4)
  DEF_ROMLOC(152CA) : and_toreg_16(0xF, &D1);      // ANDI.W	#$000F,D1
  DEF_ROMLOC(152CE) : add_toreg_16(D0, &D1);       // ADD.W	D0,D1
  DEF_ROMLOC(152D0) : move_toreg_32(0x63A00, &A2); // LEA.L	$00063A00,A2
  DEF_ROMLOC(152D6)
      : move_toreg_8(read_8((s32)A2 + (s8)0x0 + (s16)D1),
                     &D0);                        // MOVE.B	0(A2,D1),D0
  DEF_ROMLOC(152DA) : ext_reg_16(&D0);            // EXT.W	D0
  DEF_ROMLOC(152DC) : eor_toreg_16(D6, &D4);      // EOR.W	D6,D4
  DEF_ROMLOC(152DE) : btst_toreg_32(0xB, &D4);    // BTST.L	#$0B,D4
  DEF_ROMLOC(152E2) : if (CCR_EQ) goto rom_152E6; // BEQ.B	$152E6
  DEF_ROMLOC(152E4) : neg_reg_16(&D0);            // NEG.W	D0
  DEF_ROMLOC(152E6) : tst_reg_16(&D0);            // TST.W	D0
  DEF_ROMLOC(152E8) : if (CCR_EQ) goto rom_15286; // BEQ.B	$15286
  DEF_ROMLOC(152EA) : if (CCR_MI) goto rom_15302; // BMI.B	$15302
  DEF_ROMLOC(152EC) : cmp_toreg_8(0x10, &D0);     // CMPI.B	#$10,D0
  DEF_ROMLOC(152F0) : if (CCR_EQ) goto rom_1530E; // BEQ.B	$1530E
  DEF_ROMLOC(152F2) : move_toreg_16(D3, &D1);     // MOVE.W	D3,D1
  DEF_ROMLOC(152F4) : and_toreg_16(0xF, &D1);     // ANDI.W	#$000F,D1
  DEF_ROMLOC(152F8) : add_toreg_16(D1, &D0);      // ADD.W	D1,D0
  DEF_ROMLOC(152FA) : move_toreg_16(0xF, &D1);    // MOVE.W	#$000F,D1
  DEF_ROMLOC(152FE) : sub_toreg_16(D0, &D1);      // SUB.W	D0,D1
  DEF_ROMLOC(15300) : return;                     // RTS
  DEF_ROMLOC(15302) : move_toreg_16(D3, &D1);     // MOVE.W	D3,D1
  DEF_ROMLOC(15304) : and_toreg_16(0xF, &D1);     // ANDI.W	#$000F,D1
  DEF_ROMLOC(15308) : add_toreg_16(D1, &D0);      // ADD.W	D1,D0
  DEF_ROMLOC(1530A) : if (CCR_PL) goto rom_15286; // BPL.W	$15286
  DEF_ROMLOC(1530E) : sub_toreg_16(A3, &D3);      // SUB.W	A3,D3
  DEF_ROMLOC(15310) : rom_1531C();                // BSR.W	$1531C
  DEF_ROMLOC(15314) : add_toreg_16(A3, &D3);      // ADD.W	A3,D3
  DEF_ROMLOC(15316) : sub_toreg_16(0x10, &D1);    // SUBI.W	#$0010,D1
  DEF_ROMLOC(1531A) : return;                     // RTS
}
ROMFUNC(rom_1531C) {
  DEF_ROMLOC(1531C) : rom_150C4();                     // BSR.W	$150C4
  DEF_ROMLOC(15320) : move_toreg_16(read_16(A1), &D0); // MOVE.W	(A1),D0
  DEF_ROMLOC(15322) : move_toreg_16(D0, &D4);          // MOVE.W	D0,D4
  DEF_ROMLOC(15324) : and_toreg_16(0x7FF, &D0);        // ANDI.W	#$07FF,D0
  DEF_ROMLOC(15328) : if (CCR_EQ) goto rom_1532E;      // BEQ.B	$1532E
  DEF_ROMLOC(1532A) : btst_toreg_32(D5, &D4);          // BTST.L	D5,D4
  DEF_ROMLOC(1532C) : if (!CCR_EQ) goto rom_1533C;     // BNE.B	$1533C
  DEF_ROMLOC(1532E) : move_toreg_16(0xF, &D1);         // MOVE.W	#$000F,D1
  DEF_ROMLOC(15332) : move_toreg_16(D3, &D0);          // MOVE.W	D3,D0
  DEF_ROMLOC(15334) : and_toreg_16(0xF, &D0);          // ANDI.W	#$000F,D0
  DEF_ROMLOC(15338) : sub_toreg_16(D0, &D1);           // SUB.W	D0,D1
  DEF_ROMLOC(1533A) : return;                          // RTS
  DEF_ROMLOC(1533C)
      : move_toreg_32(read_32(0xFFFFF796), &A2); // MOVEA.L	$F796,A2
  DEF_ROMLOC(15340)
      : move_toreg_8(read_8((s32)A2 + (s8)0x0 + (s16)D0),
                     &D0);                         // MOVE.B	0(A2,D0),D0
  DEF_ROMLOC(15344) : and_toreg_16(0xFF, &D0);     // ANDI.W	#$00FF,D0
  DEF_ROMLOC(15348) : if (CCR_EQ) goto rom_1532E;  // BEQ.B	$1532E
  DEF_ROMLOC(1534A) : move_toreg_32(0x62900, &A2); // LEA.L	$00062900,A2
  DEF_ROMLOC(15350)
      : move_tomem_8(read_8((s32)A2 + (s8)0x0 + (s16)D0),
                     A4);                          // MOVE.B	0(A2,D0),(A4)
  DEF_ROMLOC(15354) : lsl_toreg_16(0x4, &D0);      // LSL.W	#$04,D0
  DEF_ROMLOC(15356) : move_toreg_16(D2, &D1);      // MOVE.W	D2,D1
  DEF_ROMLOC(15358) : btst_toreg_32(0xC, &D4);     // BTST.L	#$0C,D4
  DEF_ROMLOC(1535C) : if (CCR_EQ) goto rom_1536A;  // BEQ.B	$1536A
  DEF_ROMLOC(1535E) : not_reg_16(&D1);             // NOT.W	D1
  DEF_ROMLOC(15360) : add_tomem_8(0x40, A4);       // ADDI.B	#$40,(A4)
  DEF_ROMLOC(15364) : neg_mem_8(A4);               // NEG.B	(A4)
  DEF_ROMLOC(15366) : sub_tomem_8(0x40, A4);       // SUBI.B	#$40,(A4)
  DEF_ROMLOC(1536A) : btst_toreg_32(0xB, &D4);     // BTST.L	#$0B,D4
  DEF_ROMLOC(1536E) : if (CCR_EQ) goto rom_15372;  // BEQ.B	$15372
  DEF_ROMLOC(15370) : neg_mem_8(A4);               // NEG.B	(A4)
  DEF_ROMLOC(15372) : and_toreg_16(0xF, &D1);      // ANDI.W	#$000F,D1
  DEF_ROMLOC(15376) : add_toreg_16(D0, &D1);       // ADD.W	D0,D1
  DEF_ROMLOC(15378) : move_toreg_32(0x63A00, &A2); // LEA.L	$00063A00,A2
  DEF_ROMLOC(1537E)
      : move_toreg_8(read_8((s32)A2 + (s8)0x0 + (s16)D1),
                     &D0);                        // MOVE.B	0(A2,D1),D0
  DEF_ROMLOC(15382) : ext_reg_16(&D0);            // EXT.W	D0
  DEF_ROMLOC(15384) : eor_toreg_16(D6, &D4);      // EOR.W	D6,D4
  DEF_ROMLOC(15386) : btst_toreg_32(0xB, &D4);    // BTST.L	#$0B,D4
  DEF_ROMLOC(1538A) : if (CCR_EQ) goto rom_1538E; // BEQ.B	$1538E
  DEF_ROMLOC(1538C) : neg_reg_16(&D0);            // NEG.W	D0
  DEF_ROMLOC(1538E) : tst_reg_16(&D0);            // TST.W	D0
  DEF_ROMLOC(15390) : if (CCR_EQ) goto rom_1532E; // BEQ.B	$1532E
  DEF_ROMLOC(15392) : if (CCR_MI) goto rom_153A4; // BMI.B	$153A4
  DEF_ROMLOC(15394) : move_toreg_16(D3, &D1);     // MOVE.W	D3,D1
  DEF_ROMLOC(15396) : and_toreg_16(0xF, &D1);     // ANDI.W	#$000F,D1
  DEF_ROMLOC(1539A) : add_toreg_16(D1, &D0);      // ADD.W	D1,D0
  DEF_ROMLOC(1539C) : move_toreg_16(0xF, &D1);    // MOVE.W	#$000F,D1
  DEF_ROMLOC(153A0) : sub_toreg_16(D0, &D1);      // SUB.W	D0,D1
  DEF_ROMLOC(153A2) : return;                     // RTS
  DEF_ROMLOC(153A4) : move_toreg_16(D3, &D1);     // MOVE.W	D3,D1
  DEF_ROMLOC(153A6) : and_toreg_16(0xF, &D1);     // ANDI.W	#$000F,D1
  DEF_ROMLOC(153AA) : add_toreg_16(D1, &D0);      // ADD.W	D1,D0
  DEF_ROMLOC(153AC) : if (CCR_PL) goto rom_1532E; // BPL.W	$1532E
  DEF_ROMLOC(153B0) : not_reg_16(&D1);            // NOT.W	D1
  DEF_ROMLOC(153B2) : return;                     // RTS
}
ROMFUNC(rom_153B4) { return; }
ROMFUNC(rom_15446) {
  DEF_ROMLOC(15446)
      : move_toreg_32(read_32(A0 + 0x8), &D3); // MOVE.L	8(A0),D3
  DEF_ROMLOC(1544A)
      : move_toreg_32(read_32(A0 + 0xC), &D2); // MOVE.L	12(A0),D2
  DEF_ROMLOC(1544E)
      : move_toreg_16(read_16(A0 + 0x10), &D1); // MOVE.W	16(A0),D1
  DEF_ROMLOC(15452) : ext_reg_32(&D1);          // EXT.L	D1
  DEF_ROMLOC(15454) : asl_toreg_32(0x8, &D1);   // ASL.L	#$08,D1
  DEF_ROMLOC(15456) : add_toreg_32(D1, &D3);    // ADD.L	D1,D3
  DEF_ROMLOC(15458)
      : move_toreg_16(read_16(A0 + 0x12), &D1);     // MOVE.W	18(A0),D1
  DEF_ROMLOC(1545C) : ext_reg_32(&D1);              // EXT.L	D1
  DEF_ROMLOC(1545E) : asl_toreg_32(0x8, &D1);       // ASL.L	#$08,D1
  DEF_ROMLOC(15460) : add_toreg_32(D1, &D2);        // ADD.L	D1,D2
  DEF_ROMLOC(15462) : swap_reg_16(&D2);             // SWAP.W	D2
  DEF_ROMLOC(15464) : swap_reg_16(&D3);             // SWAP.W	D3
  DEF_ROMLOC(15466) : move_tomem_8(D0, 0xFFFFF768); // MOVE.B	D0,$F768
  DEF_ROMLOC(1546A) : move_tomem_8(D0, 0xFFFFF76A); // MOVE.B	D0,$F76A
  DEF_ROMLOC(1546E) : move_toreg_8(D0, &D1);        // MOVE.B	D0,D1
  DEF_ROMLOC(15470) : add_toreg_8(0x20, &D0);       // ADDI.B	#$20,D0
  DEF_ROMLOC(15474) : if (CCR_PL) goto rom_15482;   // BPL.B	$15482
  DEF_ROMLOC(15476) : move_toreg_8(D1, &D0);        // MOVE.B	D1,D0
  DEF_ROMLOC(15478) : if (CCR_PL) goto rom_1547C;   // BPL.B	$1547C
  DEF_ROMLOC(1547A) : sub_toreg_8(0x1, &D0);        // SUBQ.B	#$01,D0
  DEF_ROMLOC(1547C) : add_toreg_8(0x20, &D0);       // ADDI.B	#$20,D0
  goto rom_1548C;                                   // BRA.B	$1548C
  DEF_ROMLOC(15482) : move_toreg_8(D1, &D0);        // MOVE.B	D1,D0
  DEF_ROMLOC(15484) : if (CCR_PL) goto rom_15488;   // BPL.B	$15488
  DEF_ROMLOC(15486) : add_toreg_8(0x1, &D0);        // ADDQ.B	#$01,D0
  DEF_ROMLOC(15488) : add_toreg_8(0x1F, &D0);       // ADDI.B	#$1F,D0
  DEF_ROMLOC(1548C) : and_toreg_8(0xFFFFFFC0, &D0); // ANDI.B	#$C0,D0
  DEF_ROMLOC(15490) : if (CCR_EQ) {
    rom_15558();
    return;
  }                                                 // BEQ.W	$15558
  DEF_ROMLOC(15494) : cmp_toreg_8(0xFFFFFF80, &D0); // CMPI.B	#$80,D0
  DEF_ROMLOC(15498) : if (CCR_EQ) {
    rom_156E4();
    return;
  }                                                // BEQ.W	$156E4
  DEF_ROMLOC(1549C) : and_toreg_8(0x38, &D1);      // ANDI.B	#$38,D1
  DEF_ROMLOC(154A0) : if (!CCR_EQ) goto rom_154A4; // BNE.B	$154A4
  DEF_ROMLOC(154A2) : add_toreg_16(0x8, &D2);      // ADDQ.W	#$08,D2
  DEF_ROMLOC(154A4) : cmp_toreg_8(0x40, &D0);      // CMPI.B	#$40,D0
  DEF_ROMLOC(154A8) : if (CCR_EQ) {
    rom_157B2();
    return;
  }            // BEQ.W	$157B2
  rom_15624(); // BRA.W	$15624
}
ROMFUNC(rom_154B0) {
  DEF_ROMLOC(154B0) : move_tomem_8(D0, 0xFFFFF768); // MOVE.B	D0,$F768
  DEF_ROMLOC(154B4) : move_tomem_8(D0, 0xFFFFF76A); // MOVE.B	D0,$F76A
  DEF_ROMLOC(154B8) : add_toreg_8(0x20, &D0);       // ADDI.B	#$20,D0
  DEF_ROMLOC(154BC) : and_toreg_8(0xFFFFFFC0, &D0); // ANDI.B	#$C0,D0
  DEF_ROMLOC(154C0) : cmp_toreg_8(0x40, &D0);       // CMPI.B	#$40,D0
  DEF_ROMLOC(154C4) : if (CCR_EQ) {
    rom_1573E();
    return;
  }                                                 // BEQ.W	$1573E
  DEF_ROMLOC(154C8) : cmp_toreg_8(0xFFFFFF80, &D0); // CMPI.B	#$80,D0
  DEF_ROMLOC(154CC) : if (CCR_EQ) {
    rom_15670();
    return;
  }                                                 // BEQ.W	$15670
  DEF_ROMLOC(154D0) : cmp_toreg_8(0xFFFFFFC0, &D0); // CMPI.B	#$C0,D0
  DEF_ROMLOC(154D4) : if (CCR_EQ) {
    rom_155B8();
    return;
  }            // BEQ.W	$155B8
  rom_154D8(); // Detected flow into next function
}
ROMFUNC(rom_154D8) {
  DEF_ROMLOC(154D8)
      : move_toreg_16(read_16(A0 + 0xC), &D2); // MOVE.W	12(A0),D2
  DEF_ROMLOC(154DC)
      : move_toreg_16(read_16(A0 + 0x8), &D3); // MOVE.W	8(A0),D3
  DEF_ROMLOC(154E0) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(154E2)
      : move_toreg_8(read_8(A0 + 0x16), &D0); // MOVE.B	22(A0),D0
  DEF_ROMLOC(154E6) : ext_reg_16(&D0);        // EXT.W	D0
  DEF_ROMLOC(154E8) : add_toreg_16(D0, &D2);  // ADD.W	D0,D2
  DEF_ROMLOC(154EA)
      : move_toreg_8(read_8(A0 + 0x17), &D0);         // MOVE.B	23(A0),D0
  DEF_ROMLOC(154EE) : ext_reg_16(&D0);                // EXT.W	D0
  DEF_ROMLOC(154F0) : add_toreg_16(D0, &D3);          // ADD.W	D0,D3
  DEF_ROMLOC(154F2) : move_toreg_32(0xFFFFF768, &A4); // LEA.L	$F768,A4
  DEF_ROMLOC(154F6) : move_toreg_16(0x10, &A3);       // MOVEA.W	#$0010,A3
  DEF_ROMLOC(154FA) : move_toreg_16(0x0, &D6);        // MOVE.W	#$0000,D6
  DEF_ROMLOC(154FE) : move_toreg_32(0xD, &D5);        // MOVEQ.L	$0D,D5
  DEF_ROMLOC(15500) : rom_15136();                    // BSR.W	$15136
  DEF_ROMLOC(15504) : move_tomem_16(D1, A7 -= 2);     // MOVE.W	D1,-(A7)
  DEF_ROMLOC(15506)
      : move_toreg_16(read_16(A0 + 0xC), &D2); // MOVE.W	12(A0),D2
  DEF_ROMLOC(1550A)
      : move_toreg_16(read_16(A0 + 0x8), &D3); // MOVE.W	8(A0),D3
  DEF_ROMLOC(1550E) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(15510)
      : move_toreg_8(read_8(A0 + 0x16), &D0); // MOVE.B	22(A0),D0
  DEF_ROMLOC(15514) : ext_reg_16(&D0);        // EXT.W	D0
  DEF_ROMLOC(15516) : add_toreg_16(D0, &D2);  // ADD.W	D0,D2
  DEF_ROMLOC(15518)
      : move_toreg_8(read_8(A0 + 0x17), &D0);         // MOVE.B	23(A0),D0
  DEF_ROMLOC(1551C) : ext_reg_16(&D0);                // EXT.W	D0
  DEF_ROMLOC(1551E) : sub_toreg_16(D0, &D3);          // SUB.W	D0,D3
  DEF_ROMLOC(15520) : move_toreg_32(0xFFFFF76A, &A4); // LEA.L	$F76A,A4
  DEF_ROMLOC(15524) : move_toreg_16(0x10, &A3);       // MOVEA.W	#$0010,A3
  DEF_ROMLOC(15528) : move_toreg_16(0x0, &D6);        // MOVE.W	#$0000,D6
  DEF_ROMLOC(1552C) : move_toreg_32(0xD, &D5);        // MOVEQ.L	$0D,D5
  DEF_ROMLOC(1552E) : rom_15136();                    // BSR.W	$15136
  DEF_ROMLOC(15532)
      : move_toreg_16(read_16((A7 += 2, A7 - 2)), &D0); // MOVE.W	(A7)+,D0
  DEF_ROMLOC(15534) : move_toreg_8(0x0, &D2);           // MOVE.B	#$00,D2
  rom_15538(); // Detected flow into next function
}
ROMFUNC(rom_15538) {
  DEF_ROMLOC(15538)
      : move_toreg_8(read_8(0xFFFFF76A), &D3);    // MOVE.B	$F76A,D3
  DEF_ROMLOC(1553C) : cmp_toreg_16(D0, &D1);      // CMP.W	D0,D1
  DEF_ROMLOC(1553E) : if (CCR_LE) goto rom_15546; // BLE.B	$15546
  DEF_ROMLOC(15540)
      : move_toreg_8(read_8(0xFFFFF768), &D3);    // MOVE.B	$F768,D3
  DEF_ROMLOC(15544) : exg_toreg_32(&D0, &D1);     // EXG.L	D0,D1
  DEF_ROMLOC(15546) : btst_toreg_32(0x0, &D3);    // BTST.L	#$00,D3
  DEF_ROMLOC(1554A) : if (CCR_EQ) goto rom_1554E; // BEQ.B	$1554E
  DEF_ROMLOC(1554C) : move_toreg_8(D2, &D3);      // MOVE.B	D2,D3
  DEF_ROMLOC(1554E) : return;                     // RTS
  DEF_ROMLOC(15550)
      : move_toreg_16(read_16(A0 + 0xC), &D2); // MOVE.W	12(A0),D2
  DEF_ROMLOC(15554)
      : move_toreg_16(read_16(A0 + 0x8), &D3); // MOVE.W	8(A0),D3
  rom_15558(); // Detected flow into next function
}
ROMFUNC(rom_15558) {
  DEF_ROMLOC(15558) : add_toreg_16(0xA, &D2);         // ADDI.W	#$000A,D2
  DEF_ROMLOC(1555C) : move_toreg_32(0xFFFFF768, &A4); // LEA.L	$F768,A4
  DEF_ROMLOC(15560) : move_toreg_16(0x10, &A3);       // MOVEA.W	#$0010,A3
  DEF_ROMLOC(15564) : move_toreg_16(0x0, &D6);        // MOVE.W	#$0000,D6
  DEF_ROMLOC(15568) : move_toreg_32(0xE, &D5);        // MOVEQ.L	$0E,D5
  DEF_ROMLOC(1556A) : rom_15136();                    // BSR.W	$15136
  DEF_ROMLOC(1556E) : move_toreg_8(0x0, &D2);         // MOVE.B	#$00,D2
  rom_15572(); // Detected flow into next function
}
ROMFUNC(rom_15572) {
  DEF_ROMLOC(15572)
      : move_toreg_8(read_8(0xFFFFF768), &D3);    // MOVE.B	$F768,D3
  DEF_ROMLOC(15576) : btst_toreg_32(0x0, &D3);    // BTST.L	#$00,D3
  DEF_ROMLOC(1557A) : if (CCR_EQ) goto rom_1557E; // BEQ.B	$1557E
  DEF_ROMLOC(1557C) : move_toreg_8(D2, &D3);      // MOVE.B	D2,D3
  DEF_ROMLOC(1557E) : return;                     // RTS
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
      : move_toreg_8(read_8(A0 + 0x16), &D0);         // MOVE.B	22(A0),D0
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
      : move_toreg_8(read_8(A0 + 0x17), &D0); // MOVE.B	23(A0),D0
  DEF_ROMLOC(155C6) : ext_reg_16(&D0);        // EXT.W	D0
  DEF_ROMLOC(155C8) : sub_toreg_16(D0, &D2);  // SUB.W	D0,D2
  DEF_ROMLOC(155CA)
      : move_toreg_8(read_8(A0 + 0x16), &D0);         // MOVE.B	22(A0),D0
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
      : move_toreg_8(read_8(A0 + 0x17), &D0); // MOVE.B	23(A0),D0
  DEF_ROMLOC(155F4) : ext_reg_16(&D0);        // EXT.W	D0
  DEF_ROMLOC(155F6) : add_toreg_16(D0, &D2);  // ADD.W	D0,D2
  DEF_ROMLOC(155F8)
      : move_toreg_8(read_8(A0 + 0x16), &D0);         // MOVE.B	22(A0),D0
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
      : move_toreg_8(read_8(A0 + 0x17), &D0); // MOVE.B	23(A0),D0
  DEF_ROMLOC(1574C) : ext_reg_16(&D0);        // EXT.W	D0
  DEF_ROMLOC(1574E) : sub_toreg_16(D0, &D2);  // SUB.W	D0,D2
  DEF_ROMLOC(15750)
      : move_toreg_8(read_8(A0 + 0x16), &D0);         // MOVE.B	22(A0),D0
  DEF_ROMLOC(15754) : ext_reg_16(&D0);                // EXT.W	D0
  DEF_ROMLOC(15756) : sub_toreg_16(D0, &D3);          // SUB.W	D0,D3
  DEF_ROMLOC(15758) : eor_toreg_16(0xF, &D3);         // EORI.W	#$000F,D3
  DEF_ROMLOC(1575C) : move_toreg_32(0xFFFFF768, &A4); // LEA.L	$F768,A4
  DEF_ROMLOC(15760) : move_toreg_16(0xFFFFFFF0, &A3); // MOVEA.W
                                                      // #$FFF0,A3
  DEF_ROMLOC(15764) : move_toreg_16(0x800, &D6);      // MOVE.W	#$0800,D6
  DEF_ROMLOC(15768) : move_toreg_32(0xE, &D5);        // MOVEQ.L	$0E,D5
  DEF_ROMLOC(1576A) : rom_15274();                    // BSR.W	$15274
  DEF_ROMLOC(1576E) : move_tomem_16(D1, A7 -= 2);     // MOVE.W	D1,-(A7)
  DEF_ROMLOC(15770)
      : move_toreg_16(read_16(A0 + 0xC), &D2); // MOVE.W	12(A0),D2
  DEF_ROMLOC(15774)
      : move_toreg_16(read_16(A0 + 0x8), &D3); // MOVE.W	8(A0),D3
  DEF_ROMLOC(15778) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(1577A)
      : move_toreg_8(read_8(A0 + 0x17), &D0); // MOVE.B	23(A0),D0
  DEF_ROMLOC(1577E) : ext_reg_16(&D0);        // EXT.W	D0
  DEF_ROMLOC(15780) : add_toreg_16(D0, &D2);  // ADD.W	D0,D2
  DEF_ROMLOC(15782)
      : move_toreg_8(read_8(A0 + 0x16), &D0);         // MOVE.B	22(A0),D0
  DEF_ROMLOC(15786) : ext_reg_16(&D0);                // EXT.W	D0
  DEF_ROMLOC(15788) : sub_toreg_16(D0, &D3);          // SUB.W	D0,D3
  DEF_ROMLOC(1578A) : eor_toreg_16(0xF, &D3);         // EORI.W	#$000F,D3
  DEF_ROMLOC(1578E) : move_toreg_32(0xFFFFF76A, &A4); // LEA.L	$F76A,A4
  DEF_ROMLOC(15792) : move_toreg_16(0xFFFFFFF0, &A3); // MOVEA.W
                                                      // #$FFF0,A3
  DEF_ROMLOC(15796) : move_toreg_16(0x800, &D6);      // MOVE.W	#$0800,D6
  DEF_ROMLOC(1579A) : move_toreg_32(0xE, &D5);        // MOVEQ.L	$0E,D5
  DEF_ROMLOC(1579C) : rom_15274();                    // BSR.W	$15274
  DEF_ROMLOC(157A0)
      : move_toreg_16(read_16((A7 += 2, A7 - 2)), &D0); // MOVE.W	(A7)+,D0
  DEF_ROMLOC(157A2) : move_toreg_8(0x40, &D2);          // MOVE.B	#$40,D2
  rom_15538();                                          // BRA.W	$15538
}
ROMFUNC(rom_1B59A) {
  DEF_ROMLOC(1B59A) : {}; // NOP
  DEF_ROMLOC(1B59C)
      : move_toreg_16(read_16(A0 + 0x8), &D2); // MOVE.W	8(A0),D2
  DEF_ROMLOC(1B5A0)
      : move_toreg_16(read_16(A0 + 0xC), &D3); // MOVE.W	12(A0),D3
  DEF_ROMLOC(1B5A4) : sub_toreg_16(0x8, &D2);  // SUBQ.W	#$08,D2
  DEF_ROMLOC(1B5A6) : move_toreg_32(0x0, &D5); // MOVEQ.L	$00,D5
  DEF_ROMLOC(1B5A8)
      : move_toreg_8(read_8(A0 + 0x16), &D5);         // MOVE.B	22(A0),D5
  DEF_ROMLOC(1B5AC) : sub_toreg_8(0x3, &D5);          // SUBQ.B	#$03,D5
  DEF_ROMLOC(1B5AE) : sub_toreg_16(D5, &D3);          // SUB.W	D5,D3
  DEF_ROMLOC(1B5B0) : cmp_tomem_8(0x39, A0 + 0x1A);   // CMPI.B	#$39,26(A0)
  DEF_ROMLOC(1B5B6) : if (!CCR_EQ) goto rom_1B5BE;    // BNE.B	$1B5BE
  DEF_ROMLOC(1B5B8) : add_toreg_16(0xC, &D3);         // ADDI.W	#$000C,D3
  DEF_ROMLOC(1B5BC) : move_toreg_32(0xA, &D5);        // MOVEQ.L	$0A,D5
  DEF_ROMLOC(1B5BE) : move_toreg_16(0x10, &D4);       // MOVE.W	#$0010,D4
  DEF_ROMLOC(1B5C2) : add_toreg_16(D5, &D5);          // ADD.W	D5,D5
  DEF_ROMLOC(1B5C4) : move_toreg_32(0xFFFFD800, &A1); // LEA.L	$D800,A1
  DEF_ROMLOC(1B5C8) : move_toreg_16(0x5F, &D6);       // MOVE.W	#$005F,D6
  DEF_ROMLOC(1B5CC) : tst_mem_8(A1 + 0x1);            // TST.B	1(A1)
  DEF_ROMLOC(1B5D0) : if (CCR_PL) goto rom_1B5D8;     // BPL.B	$1B5D8
  DEF_ROMLOC(1B5D2)
      : move_toreg_8(read_8(A1 + 0x20), &D0);        // MOVE.B	32(A1),D0
  DEF_ROMLOC(1B5D6) : if (!CCR_EQ) goto rom_1B62C;   // BNE.B	$1B62C
  DEF_ROMLOC(1B5D8) : move_toreg_32(A1 + 0x40, &A1); // LEA.L	64(A1),A1
  DEF_ROMLOC(1B5DC) : dec_reg_16(&D6);
  if ((D6 & 0xffff) != 0xffff)
    goto rom_1B5CC;                            // DBF.W	D6,$1B5CC
  DEF_ROMLOC(1B5E0) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(1B5E2) : return;                  // RTS
  DEF_ROMLOC(1B62C) : and_toreg_16(0x3F, &D0); // ANDI.W	#$003F,D0
  DEF_ROMLOC(1B630) : add_toreg_16(D0, &D0);   // ADD.W	D0,D0
  DEF_ROMLOC(1B632)
      : move_toreg_32(0x1B5E2 + (s16)(D0 & 0xffff),
                      &A2);                            // LEA.L	-82(PC,D0),A2
  DEF_ROMLOC(1B636) : move_toreg_32(0x0, &D1);         // MOVEQ.L	$00,D1
  DEF_ROMLOC(1B638) : move_toreg_8(read_8(A2++), &D1); // MOVE.B	(A2)+,D1
  DEF_ROMLOC(1B63A)
      : move_toreg_16(read_16(A1 + 0x8), &D0);         // MOVE.W	8(A1),D0
  DEF_ROMLOC(1B63E) : sub_toreg_16(D1, &D0);           // SUB.W	D1,D0
  DEF_ROMLOC(1B640) : sub_toreg_16(D2, &D0);           // SUB.W	D2,D0
  DEF_ROMLOC(1B642) : if (CCR_CC) goto rom_1B64E;      // BCC.B	$1B64E
  DEF_ROMLOC(1B644) : add_toreg_16(D1, &D1);           // ADD.W	D1,D1
  DEF_ROMLOC(1B646) : add_toreg_16(D1, &D0);           // ADD.W	D1,D0
  DEF_ROMLOC(1B648) : if (CCR_CS) goto rom_1B654;      // BCS.B	$1B654
  DEF_ROMLOC(1B64A) : goto rom_1B5D8;                  // BRA.W	$1B5D8
  DEF_ROMLOC(1B64E) : cmp_toreg_16(D4, &D0);           // CMP.W	D4,D0
  DEF_ROMLOC(1B650) : if (CCR_HI) goto rom_1B5D8;      // BHI.W	$1B5D8
  DEF_ROMLOC(1B654) : move_toreg_32(0x0, &D1);         // MOVEQ.L	$00,D1
  DEF_ROMLOC(1B656) : move_toreg_8(read_8(A2++), &D1); // MOVE.B	(A2)+,D1
  DEF_ROMLOC(1B658)
      : move_toreg_16(read_16(A1 + 0xC), &D0);    // MOVE.W	12(A1),D0
  DEF_ROMLOC(1B65C) : sub_toreg_16(D1, &D0);      // SUB.W	D1,D0
  DEF_ROMLOC(1B65E) : sub_toreg_16(D3, &D0);      // SUB.W	D3,D0
  DEF_ROMLOC(1B660) : if (CCR_CC) goto rom_1B66C; // BCC.B	$1B66C
  DEF_ROMLOC(1B662) : add_toreg_16(D1, &D1);      // ADD.W	D1,D1
  DEF_ROMLOC(1B664) : add_toreg_16(D0, &D1);      // ADD.W	D0,D1
  DEF_ROMLOC(1B666) : if (CCR_CS) goto rom_1B672; // BCS.B	$1B672
  DEF_ROMLOC(1B668) : goto rom_1B5D8;             // BRA.W	$1B5D8
  DEF_ROMLOC(1B66C) : cmp_toreg_16(D5, &D0);      // CMP.W	D5,D0
  DEF_ROMLOC(1B66E) : if (CCR_HI) goto rom_1B5D8; // BHI.W	$1B5D8
  DEF_ROMLOC(1B672)
      : move_toreg_8(read_8(A1 + 0x20), &D1);       // MOVE.B	32(A1),D1
  DEF_ROMLOC(1B676) : and_toreg_8(0xFFFFFFC0, &D1); // ANDI.B	#$C0,D1
  DEF_ROMLOC(1B67A) : if (CCR_EQ) {
    rom_1B6E6();
    return;
  }                                                 // BEQ.W	$1B6E6
  DEF_ROMLOC(1B67E) : cmp_toreg_8(0xFFFFFFC0, &D1); // CMPI.B	#$C0,D1
  DEF_ROMLOC(1B682) : if (CCR_EQ) {
    rom_1B8A6();
    return;
  }                                   // BEQ.W	$1B8A6
  DEF_ROMLOC(1B686) : tst_reg_8(&D1); // TST.B	D1
  DEF_ROMLOC(1B688) : if (CCR_MI) {
    rom_1B796();
    return;
  } // BMI.W	$1B796
  DEF_ROMLOC(1B68C)
      : move_toreg_8(read_8(A1 + 0x20), &D0);        // MOVE.B	32(A1),D0
  DEF_ROMLOC(1B690) : and_toreg_8(0x3F, &D0);        // ANDI.B	#$3F,D0
  DEF_ROMLOC(1B694) : cmp_toreg_8(0x6, &D0);         // CMPI.B	#$06,D0
  DEF_ROMLOC(1B698) : if (CCR_EQ) goto rom_1B6AA;    // BEQ.B	$1B6AA
  DEF_ROMLOC(1B69A) : cmp_tomem_16(0x5A, A0 + 0x30); // CMPI.W	#$005A,48(A0)
  DEF_ROMLOC(1B6A0) : if (CCR_CC) goto rom_1B6A8;    // BCC.W	$1B6A8
  DEF_ROMLOC(1B6A4) : add_tomem_8(0x2, A1 + 0x24);   // ADDQ.B	#$02,36(A1)
  DEF_ROMLOC(1B6A8) : return;                        // RTS
  DEF_ROMLOC(1B6AA) : tst_mem_16(A0 + 0x12);         // TST.W	18(A0)
  DEF_ROMLOC(1B6AE) : if (CCR_PL) goto rom_1B6D4;    // BPL.B	$1B6D4
  DEF_ROMLOC(1B6B0)
      : move_toreg_16(read_16(A0 + 0xC), &D0); // MOVE.W	12(A0),D0
  DEF_ROMLOC(1B6B4) : sub_toreg_16(0x10, &D0); // SUBI.W	#$0010,D0
  DEF_ROMLOC(1B6B8)
      : cmp_toreg_16(read_16(A1 + 0xC), &D0);     // CMP.W	12(A1),D0
  DEF_ROMLOC(1B6BC) : if (CCR_CS) goto rom_1B6E4; // BCS.B	$1B6E4
  DEF_ROMLOC(1B6BE) : neg_mem_16(A0 + 0x12);      // NEG.W	18(A0)
  DEF_ROMLOC(1B6C2)
      : move_tomem_16(0xFFFFFE80, A1 + 0x12);      // MOVE.W	#$FE80,18(A1)
  DEF_ROMLOC(1B6C8) : tst_mem_8(A1 + 0x25);        // TST.B	37(A1)
  DEF_ROMLOC(1B6CC) : if (!CCR_EQ) goto rom_1B6E4; // BNE.B	$1B6E4
  DEF_ROMLOC(1B6CE) : add_tomem_8(0x4, A1 + 0x25); // ADDQ.B	#$04,37(A1)
  DEF_ROMLOC(1B6D2) : return;                      // RTS
  DEF_ROMLOC(1B6D4) : cmp_tomem_8(0x2, A0 + 0x1C); // CMPI.B	#$02,28(A0)
  DEF_ROMLOC(1B6DA) : if (!CCR_EQ) goto rom_1B6E4; // BNE.B	$1B6E4
  DEF_ROMLOC(1B6DC) : neg_mem_16(A0 + 0x12);       // NEG.W	18(A0)
  DEF_ROMLOC(1B6E0) : add_tomem_8(0x2, A1 + 0x24); // ADDQ.B	#$02,36(A1)
  DEF_ROMLOC(1B6E4) : return;                      // RTS
}
ROMFUNC(rom_1B6E6) {
  DEF_ROMLOC(1B6E6) : tst_mem_8(0xFFFFFE2D);       // TST.B	$FE2D
  DEF_ROMLOC(1B6EA) : if (!CCR_EQ) goto rom_1B6F6; // BNE.B	$1B6F6
  DEF_ROMLOC(1B6EC) : cmp_tomem_8(0x2, A0 + 0x1C); // CMPI.B	#$02,28(A0)
  DEF_ROMLOC(1B6F2) : if (!CCR_EQ) {
    rom_1B796();
    return;
  }                                                 // BNE.W	$1B796
  DEF_ROMLOC(1B6F6) : tst_mem_8(A1 + 0x21);         // TST.B	33(A1)
  DEF_ROMLOC(1B6FA) : if (CCR_EQ) goto rom_1B720;   // BEQ.B	$1B720
  DEF_ROMLOC(1B6FC) : neg_mem_16(A0 + 0x10);        // NEG.W	16(A0)
  DEF_ROMLOC(1B700) : neg_mem_16(A0 + 0x12);        // NEG.W	18(A0)
  DEF_ROMLOC(1B704) : asr_mem_16(A0 + 0x10);        // ASR.W	16(A0)
  DEF_ROMLOC(1B708) : asr_mem_16(A0 + 0x12);        // ASR.W	18(A0)
  DEF_ROMLOC(1B70C) : move_tomem_8(0x0, A1 + 0x20); // MOVE.B	#$00,32(A1)
  DEF_ROMLOC(1B712) : sub_tomem_8(0x1, A1 + 0x21);  // SUBQ.B	#$01,33(A1)
  DEF_ROMLOC(1B716) : if (!CCR_EQ) goto rom_1B71E;  // BNE.B	$1B71E
  DEF_ROMLOC(1B718) : bset_tomem_8(0x7, A1 + 0x22); // BSET.B	#$07,34(A1)
  DEF_ROMLOC(1B71E) : return;                       // RTS
  DEF_ROMLOC(1B720) : bset_tomem_8(0x7, A1 + 0x22); // BSET.B	#$07,34(A1)
  DEF_ROMLOC(1B726) : move_toreg_32(0x0, &D0);      // MOVEQ.L	$00,D0
  DEF_ROMLOC(1B728)
      : move_toreg_16(read_16(0xFFFFF7D0), &D0);     // MOVE.W	$F7D0,D0
  DEF_ROMLOC(1B72C) : add_tomem_16(0x2, 0xFFFFF7D0); // ADDQ.W	#$02,$F7D0
  DEF_ROMLOC(1B730) : cmp_toreg_16(0x6, &D0);        // CMPI.W	#$0006,D0
  DEF_ROMLOC(1B734) : if (CCR_CS) goto rom_1B738;    // BCS.B	$1B738
  DEF_ROMLOC(1B736) : move_toreg_32(0x6, &D0);       // MOVEQ.L	$06,D0
  DEF_ROMLOC(1B738) : move_tomem_16(D0, A1 + 0x3E);  // MOVE.W	D0,62(A1)
  DEF_ROMLOC(1B73C)
      : move_toreg_16(read_16(0x1B788 + (s16)(D0 & 0xffff)),
                      &D0);                           // MOVE.W	74(PC,D0),D0
  DEF_ROMLOC(1B740) : cmp_tomem_16(0x20, 0xFFFFF7D0); // CMPI.W	#$0020,$F7D0
  DEF_ROMLOC(1B746) : if (CCR_CS) goto rom_1B752;     // BCS.B	$1B752
  DEF_ROMLOC(1B748) : move_toreg_16(0x3E8, &D0);      // MOVE.W	#$03E8,D0
  DEF_ROMLOC(1B74C) : move_tomem_16(0xA, A1 + 0x3E);  // MOVE.W	#$000A,62(A1)
  DEF_ROMLOC(1B752) : rom_1CE42();                    // BSR.W	$1CE42
  DEF_ROMLOC(1B756) : move_tomem_8(0x27, A1 + 0x0);   // MOVE.B	#$27,0(A1)
  DEF_ROMLOC(1B75C) : move_tomem_8(0x0, A1 + 0x24);   // MOVE.B	#$00,36(A1)
  DEF_ROMLOC(1B762) : tst_mem_16(A0 + 0x12);          // TST.W	18(A0)
  DEF_ROMLOC(1B766) : if (CCR_MI) goto rom_1B778;     // BMI.B	$1B778
  DEF_ROMLOC(1B768)
      : move_toreg_16(read_16(A0 + 0xC), &D0); // MOVE.W	12(A0),D0
  DEF_ROMLOC(1B76C)
      : cmp_toreg_16(read_16(A1 + 0xC), &D0);         // CMP.W	12(A1),D0
  DEF_ROMLOC(1B770) : if (CCR_CC) goto rom_1B780;     // BCC.B	$1B780
  DEF_ROMLOC(1B772) : neg_mem_16(A0 + 0x12);          // NEG.W	18(A0)
  DEF_ROMLOC(1B776) : return;                         // RTS
  DEF_ROMLOC(1B778) : add_tomem_16(0x100, A0 + 0x12); // ADDI.W	#$0100,18(A0)
  DEF_ROMLOC(1B77E) : return;                         // RTS
  DEF_ROMLOC(1B780) : sub_tomem_16(0x100, A0 + 0x12); // SUBI.W	#$0100,18(A0)
  DEF_ROMLOC(1B786) : return;                         // RTS
}
ROMFUNC(rom_1B790) {
  DEF_ROMLOC(1B790) : bset_tomem_8(0x7, A1 + 0x22); // BSET.B	#$07,34(A1)
  rom_1B796();
}
ROMFUNC(rom_1B796) {
  DEF_ROMLOC(1B796) : tst_mem_8(0xFFFFFE2D);          // TST.B	$FE2D
  DEF_ROMLOC(1B79A) : if (CCR_EQ) goto rom_1B7A0;     // BEQ.B	$1B7A0
  DEF_ROMLOC(1B79C) : move_toreg_32(0xFFFFFFFF, &D0); // MOVEQ.L	$FF,D0
  DEF_ROMLOC(1B79E) : return;                         // RTS
  DEF_ROMLOC(1B7A0) : {};                             // NOP
  DEF_ROMLOC(1B7A2) : tst_mem_16(A0 + 0x30);          // TST.W	48(A0)
  DEF_ROMLOC(1B7A6) : if (!CCR_EQ) goto rom_1B79C;    // BNE.B	$1B79C
  DEF_ROMLOC(1B7A8) : move_toreg_32(A1, &A2);         // MOVEA.L	A1,A2
  rom_1B7AA();
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
  }                                               // BRA.W	$1B790
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
  }                                                // BRA.W	$1B6E6
  DEF_ROMLOC(1B8FE) : add_tomem_8(0x1, A1 + 0x21); // ADDQ.B	#$01,33(A1)
  DEF_ROMLOC(1B902) : return;                      // RTS
}
ROMFUNC(rom_8BA8) {
	DEF_ROMLOC(8BA8): move_toreg_32(0xFFFFD000, &A1); // LEA.L	$D000,A1
	DEF_ROMLOC(8BAC): btst_tomem_8(0x3, A1 + 0x22); // BTST.B	#$03,34(A1)
	DEF_ROMLOC(8BB2): if (CCR_EQ) goto rom_8BEC; // BEQ.B	$8BEC
	DEF_ROMLOC(8BB4): move_toreg_16(read_16(A1 + 0x8), &D0); // MOVE.W	8(A1),D0
	DEF_ROMLOC(8BB8): sub_toreg_16(read_16(A0 + 0x8), &D0); // SUB.W	8(A0),D0
	DEF_ROMLOC(8BBC): add_toreg_16(D1, &D0); // ADD.W	D1,D0
	DEF_ROMLOC(8BBE): lsr_toreg_16(0x1, &D0); // LSR.W	#$01,D0
	DEF_ROMLOC(8BC0): btst_tomem_8(0x0, A0 + 0x1); // BTST.B	#$00,1(A0)
	DEF_ROMLOC(8BC6): if (CCR_EQ) goto rom_8BCC; // BEQ.B	$8BCC
	DEF_ROMLOC(8BC8): not_reg_16(&D0); // NOT.W	D0
	DEF_ROMLOC(8BCA): add_toreg_16(D1, &D0); // ADD.W	D1,D0
	DEF_ROMLOC(8BCC): move_toreg_32(0x0, &D1); // MOVEQ.L	$00,D1
	DEF_ROMLOC(8BCE): move_toreg_8(read_8((s32)A2 + (s8)0x0 + (s16)D0), &D1); // MOVE.B	0(A2,D0),D1
	DEF_ROMLOC(8BD2): move_toreg_16(read_16(A0 + 0xC), &D0); // MOVE.W	12(A0),D0
	DEF_ROMLOC(8BD6): sub_toreg_16(D1, &D0); // SUB.W	D1,D0
	DEF_ROMLOC(8BD8): move_toreg_32(0x0, &D1); // MOVEQ.L	$00,D1
	DEF_ROMLOC(8BDA): move_toreg_8(read_8(A1 + 0x16), &D1); // MOVE.B	22(A1),D1
	DEF_ROMLOC(8BDE): sub_toreg_16(D1, &D0); // SUB.W	D1,D0
	DEF_ROMLOC(8BE0): move_tomem_16(D0, A1 + 0xC); // MOVE.W	D0,12(A1)
	DEF_ROMLOC(8BE4): sub_toreg_16(read_16(A0 + 0x8), &D2); // SUB.W	8(A0),D2
	DEF_ROMLOC(8BE8): sub_tomem_16(D2, A1 + 0x8); // SUB.W	D2,8(A1)
	DEF_ROMLOC(8BEC): return; // RTS
}
ROMFUNC(rom_13F52) {
	DEF_ROMLOC(13F52): move_toreg_16(read_16(0xFFFFF72E), &D0); // MOVE.W	$F72E,D0
	DEF_ROMLOC(13F56): add_toreg_16(0x100, &D0); // ADDI.W	#$0100,D0
	DEF_ROMLOC(13F5A): cmp_toreg_16(read_16(A0 + 0xC), &D0); // CMP.W	12(A0),D0
	DEF_ROMLOC(13F5E): if (CCR_CC) goto rom_13FD4; // BCC.W	$13FD4
	DEF_ROMLOC(13F62): move_tomem_16(0xFFFFFFC8, A0 + 0x12); // MOVE.W	#$FFC8,18(A0)
	DEF_ROMLOC(13F68): add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
	DEF_ROMLOC(13F6C): clr_mem_8(0xFFFFFE1E); // CLR.B	$FE1E
	DEF_ROMLOC(13F70): add_tomem_8(0x1, 0xFFFFFE1C); // ADDQ.B	#$01,$FE1C
	DEF_ROMLOC(13F74): sub_tomem_8(0x1, 0xFFFFFE12); // SUBQ.B	#$01,$FE12
	DEF_ROMLOC(13F78): if (!CCR_EQ) goto rom_13FA8; // BNE.B	$13FA8
	DEF_ROMLOC(13F7A): move_tomem_16(0x0, A0 + 0x3A); // MOVE.W	#$0000,58(A0)
	DEF_ROMLOC(13F80): move_tomem_8(0x39, 0xFFFFD080); // MOVE.B	#$39,$D080
	DEF_ROMLOC(13F86): move_tomem_8(0x39, 0xFFFFD0C0); // MOVE.B	#$39,$D0C0
	DEF_ROMLOC(13F8C): move_tomem_8(0x1, 0xFFFFD0DA); // MOVE.B	#$01,$D0DA
	DEF_ROMLOC(13F92): clr_mem_8(0xFFFFFE1A); // CLR.B	$FE1A
	DEF_ROMLOC(13F96): move_toreg_16(0x8F, &D0); // MOVE.W	#$008F,D0
	DEF_ROMLOC(13F9A): rom_138E(); // JSR	$0000138E
	DEF_ROMLOC(13FA0): move_toreg_32(0x3, &D0); // MOVEQ.L	$03,D0
	DEF_ROMLOC(13FA2): {rom_1578();return;} // JMP	$00001578
	DEF_ROMLOC(13FA8): move_tomem_16(0x3C, A0 + 0x3A); // MOVE.W	#$003C,58(A0)
	DEF_ROMLOC(13FAE): tst_mem_8(0xFFFFFE1A); // TST.B	$FE1A
	DEF_ROMLOC(13FB2): if (CCR_EQ) goto rom_13FD4; // BEQ.B	$13FD4
	DEF_ROMLOC(13FB4): move_tomem_16(0x0, A0 + 0x3A); // MOVE.W	#$0000,58(A0)
	DEF_ROMLOC(13FBA): move_tomem_8(0x39, 0xFFFFD080); // MOVE.B	#$39,$D080
	DEF_ROMLOC(13FC0): move_tomem_8(0x39, 0xFFFFD0C0); // MOVE.B	#$39,$D0C0
	DEF_ROMLOC(13FC6): move_tomem_8(0x2, 0xFFFFD09A); // MOVE.B	#$02,$D09A
	DEF_ROMLOC(13FCC): move_tomem_8(0x3, 0xFFFFD0DA); // MOVE.B	#$03,$D0DA
	goto rom_13F96; // BRA.B	$13F96
	DEF_ROMLOC(13FD4): return; // RTS
}
ROMFUNC(rom_100A8) {
	DEF_ROMLOC(100A8): tst_mem_8(A0 + 0x25); // TST.B	37(A0)
	DEF_ROMLOC(100AC): if (CCR_EQ) {rom_1015C();return;} // BEQ.W	$1015C
	DEF_ROMLOC(100B0): move_toreg_16(D1, &D2); // MOVE.W	D1,D2
	DEF_ROMLOC(100B2): add_toreg_16(D2, &D2); // ADD.W	D2,D2
	DEF_ROMLOC(100B4): move_toreg_32(0xFFFFD000, &A1); // LEA.L	$D000,A1
	DEF_ROMLOC(100B8): btst_tomem_8(0x1, A1 + 0x22); // BTST.B	#$01,34(A1)
	DEF_ROMLOC(100BE): if (!CCR_EQ) goto rom_100D0; // BNE.B	$100D0
	DEF_ROMLOC(100C0): move_toreg_16(read_16(A1 + 0x8), &D0); // MOVE.W	8(A1),D0
	DEF_ROMLOC(100C4): sub_toreg_16(read_16(A0 + 0x8), &D0); // SUB.W	8(A0),D0
	DEF_ROMLOC(100C8): add_toreg_16(D1, &D0); // ADD.W	D1,D0
	DEF_ROMLOC(100CA): if (CCR_MI) goto rom_100D0; // BMI.B	$100D0
	DEF_ROMLOC(100CC): cmp_toreg_16(D2, &D0); // CMP.W	D2,D0
	DEF_ROMLOC(100CE): if (CCR_CS) goto rom_100E4; // BCS.B	$100E4
	DEF_ROMLOC(100D0): bclr_tomem_8(0x3, A1 + 0x22); // BCLR.B	#$03,34(A1)
	DEF_ROMLOC(100D6): bclr_tomem_8(0x3, A0 + 0x22); // BCLR.B	#$03,34(A0)
	DEF_ROMLOC(100DC): clr_mem_8(A0 + 0x25); // CLR.B	37(A0)
	DEF_ROMLOC(100E0): move_toreg_32(0x0, &D4); // MOVEQ.L	$00,D4
	DEF_ROMLOC(100E2): return; // RTS
	DEF_ROMLOC(100E4): move_toreg_16(D4, &D2); // MOVE.W	D4,D2
	DEF_ROMLOC(100E6): rom_81A0(); // BSR.W	$81A0
	DEF_ROMLOC(100EA): move_toreg_32(0x0, &D4); // MOVEQ.L	$00,D4
	DEF_ROMLOC(100EC): return; // RTS
}
ROMFUNC(rom_100EE) {
	DEF_ROMLOC(100EE): move_toreg_32(0xFFFFD000, &A1); // LEA.L	$D000,A1
	DEF_ROMLOC(100F2): tst_mem_8(A0 + 0x1); // TST.B	1(A0)
	DEF_ROMLOC(100F6): if (CCR_PL) {rom_1021E();return;} // BPL.W	$1021E
	DEF_ROMLOC(100FA): move_toreg_16(read_16(A1 + 0x8), &D0); // MOVE.W	8(A1),D0
	DEF_ROMLOC(100FE): sub_toreg_16(read_16(A0 + 0x8), &D0); // SUB.W	8(A0),D0
	DEF_ROMLOC(10102): add_toreg_16(D1, &D0); // ADD.W	D1,D0
	DEF_ROMLOC(10104): if (CCR_MI) {rom_1021E();return;} // BMI.W	$1021E
	DEF_ROMLOC(10108): move_toreg_16(D1, &D3); // MOVE.W	D1,D3
	DEF_ROMLOC(1010A): add_toreg_16(D3, &D3); // ADD.W	D3,D3
	DEF_ROMLOC(1010C): cmp_toreg_16(D3, &D0); // CMP.W	D3,D0
	DEF_ROMLOC(1010E): if (CCR_HI) {rom_1021E();return;} // BHI.W	$1021E
	DEF_ROMLOC(10112): move_toreg_16(D0, &D5); // MOVE.W	D0,D5
	DEF_ROMLOC(10114): btst_tomem_8(0x0, A0 + 0x1); // BTST.B	#$00,1(A0)
	DEF_ROMLOC(1011A): if (CCR_EQ) goto rom_10120; // BEQ.B	$10120
	DEF_ROMLOC(1011C): not_reg_16(&D5); // NOT.W	D5
	DEF_ROMLOC(1011E): add_toreg_16(D3, &D5); // ADD.W	D3,D5
	DEF_ROMLOC(10120): lsr_toreg_16(0x1, &D5); // LSR.W	#$01,D5
	DEF_ROMLOC(10122): move_toreg_32(0x0, &D3); // MOVEQ.L	$00,D3
	DEF_ROMLOC(10124): move_toreg_8(read_8((s32)A2 + (s8)0x0 + (s16)D5), &D3); // MOVE.B	0(A2,D5),D3
	DEF_ROMLOC(10128): sub_toreg_8(read_8(A2), &D3); // SUB.B	(A2),D3
	DEF_ROMLOC(1012A): move_toreg_16(read_16(A0 + 0xC), &D5); // MOVE.W	12(A0),D5
	DEF_ROMLOC(1012E): sub_toreg_16(D3, &D5); // SUB.W	D3,D5
	DEF_ROMLOC(10130): move_toreg_8(read_8(A1 + 0x16), &D3); // MOVE.B	22(A1),D3
	DEF_ROMLOC(10134): ext_reg_16(&D3); // EXT.W	D3
	DEF_ROMLOC(10136): add_toreg_16(D3, &D2); // ADD.W	D3,D2
	DEF_ROMLOC(10138): move_toreg_16(read_16(A1 + 0xC), &D3); // MOVE.W	12(A1),D3
	DEF_ROMLOC(1013C): sub_toreg_16(D5, &D3); // SUB.W	D5,D3
	DEF_ROMLOC(1013E): add_toreg_16(0x4, &D3); // ADDQ.W	#$04,D3
	DEF_ROMLOC(10140): add_toreg_16(D2, &D3); // ADD.W	D2,D3
	DEF_ROMLOC(10142): if (CCR_MI) {rom_1021E();return;} // BMI.W	$1021E
	DEF_ROMLOC(10146): move_toreg_16(D2, &D4); // MOVE.W	D2,D4
	DEF_ROMLOC(10148): add_toreg_16(D4, &D4); // ADD.W	D4,D4
	DEF_ROMLOC(1014A): cmp_toreg_16(D4, &D3); // CMP.W	D4,D3
	DEF_ROMLOC(1014C): if (CCR_CC) {rom_1021E();return;} // BCC.W	$1021E
	rom_1019A(); // BRA.W	$1019A
}
/*ROMFUNC(rom_D9D6) {
	u8 switchindex = 0;
	DEF_ROMLOC(D9D6): move_toreg_8(read_8(A0), &D0); // MOVE.B	(A0),D0
	DEF_ROMLOC(D9D8): if (CCR_EQ) goto rom_D9E6; // BEQ.B	$D9E6
	DEF_ROMLOC(D9DA): switchindex = D0 - 1; add_toreg_16(D0, &D0); // ADD.W	D0,D0
	DEF_ROMLOC(D9DC): add_toreg_16(D0, &D0); // ADD.W	D0,D0
	DEF_ROMLOC(D9DE): move_toreg_32(read_32(0xDA0C + (s16)(D0 & 0xffff)), &A1); // MOVEA.L	44(PC,D0),A1
	// DEF_ROMLOC(D9E2): CALLEMU(A1); // rom_A1(); // JSR	(A1)
	DEF_ROMLOC(D9E2):
		switch (switchindex) {
			case 0x00: rom_132AC(); break;
			case 0x01: rom_DC40(); break;
			case 0x02: rom_DC40(); break;
			case 0x03: rom_DC40(); break;
			case 0x04: rom_DC40(); break;
			case 0x05: rom_DC40(); break;
			case 0x06: rom_DC40(); break;
			case 0x07: rom_14A58(); break;
			case 0x08: rom_1C13A(); break;
			case 0x09: rom_1436C(); break;
			case 0x0A: rom_118DA(); break;
			case 0x0B: rom_11A1A(); break;
			case 0x0C: rom_F1B4(); break;
			case 0x0D: rom_ACA6(); break;
			case 0x0E: rom_AD26(); break;
			case 0x0F: rom_1C7D8(); break;
			case 0x10: rom_79A6(); break;
			case 0x11: rom_EF98(); break;
			case 0x12: rom_E924(); break;
			case 0x13: rom_E992(); break;
			case 0x14: rom_7FD0(); break;
			case 0x15: rom_125D8(); break;
			case 0x16: rom_8320(); break;
			case 0x17: rom_84B0(); break;
			case 0x18: rom_8826(); break;
			case 0x19: rom_888E(); break;
			case 0x1A: rom_1179A(); break;
			case 0x1B: rom_8E48(); break;
			case 0x1C: rom_8EDC(); break;
			case 0x1D: rom_91CA(); break;
			case 0x1E: rom_9B6E(); break;
			case 0x1F: rom_929A(); break;
			case 0x20: rom_1CCFE(); break;
			case 0x21: rom_9E5C(); break;
			case 0x22: rom_9FB0(); break;
			case 0x23: rom_9370(); break;
			case 0x24: rom_A1A4(); break;
			case 0x25: rom_A79A(); break;
			case 0x26: rom_93E0(); break;
			case 0x27: rom_95A0(); break;
			case 0x28: rom_9A90(); break;
			case 0x29: rom_8FB2(); break;
			case 0x2A: rom_B1AA(); break;
			case 0x2B: rom_B264(); break;
			case 0x2C: rom_B32E(); break;
			case 0x2D: rom_A984(); break;
			case 0x2E: rom_B542(); break;
			case 0x2F: rom_BA28(); break;
			case 0x30: rom_BD06(); break;
			case 0x31: rom_C3B8(); break;
			case 0x32: rom_C55C(); break;
			case 0x33: rom_C990(); break;
			case 0x34: rom_B866(); break;
			case 0x35: rom_D4B6(); break;
			case 0x36: rom_A334(); break;
			case 0x37: rom_148C0(); break;
			case 0x38: rom_CB42(); break;
			case 0x39: rom_CC00(); break;
			case 0x3A: rom_D6DE(); break;
			case 0x3B: rom_D7AA(); break;
			case 0x3C: rom_17EAC(); break;
			case 0x3D: rom_1B2D8(); break;
			case 0x3E: rom_9474(); break;
			case 0x3F: rom_FCA6(); break;
			case 0x40: rom_E14C(); break;
			case 0x41: rom_E3F6(); break;
			case 0x42: rom_E688(); break;
			case 0x43: rom_E862(); break;
			case 0x44: rom_C024(); break;
			case 0x45: rom_EE5E(); break;
			case 0x46: rom_F05C(); break;
			case 0x47: rom_18290(); break;
			case 0x48: rom_D74C(); break;
			case 0x49: rom_149BC(); break;
			case 0x4A: rom_A484(); break;
			case 0x4B: rom_F410(); break;
			case 0x4C: rom_F4FC(); break;
			case 0x4D: rom_F6EA(); break;
			case 0x4E: rom_FE92(); break;
			case 0x4F: rom_FEC6(); break;
			case 0x50: rom_1031E(); break;
			case 0x51: rom_10484(); break;
			case 0x52: rom_899E(); break;
			case 0x53: rom_F844(); break;
			case 0x54: rom_10734(); break;
			case 0x55: rom_10912(); break;
			case 0x56: rom_10E56(); break;
			case 0x57: rom_1104A(); break;
			case 0x58: rom_111A6(); break;
			case 0x59: rom_1142E(); break;
			case 0x5A: rom_11564(); break;
			case 0x5B: rom_11718(); break;
			case 0x5C: rom_11BD0(); break;
			case 0x5D: rom_11D10(); break;
			case 0x5E: rom_120CA(); break;
			case 0x5F: rom_123A2(); break;
			case 0x60: rom_126A8(); break;
			case 0x61: rom_128BC(); break;
			case 0x62: rom_12A10(); break;
			case 0x63: rom_12D78(); break;
			case 0x64: rom_13172(); break;
			case 0x65: rom_15802(); break;
			case 0x66: rom_15C4A(); break;
			case 0x67: rom_15DF6(); break;
			case 0x68: rom_15E98(); break;
			case 0x69: rom_160E4(); break;
			case 0x6A: rom_1637A(); break;
			case 0x6B: rom_16760(); break;
			case 0x6C: rom_EB6E(); break;
			case 0x6D: rom_168AE(); break;
			case 0x6E: rom_169D2(); break;
			case 0x6F: rom_16C92(); break;
			case 0x70: rom_11AEE(); break;
			case 0x71: rom_16DD0(); break;
			case 0x72: rom_189E0(); break;
			case 0x73: rom_18E54(); break;
			case 0x74: rom_1989E(); break;
			case 0x75: rom_19E42(); break;
			case 0x76: rom_185E2(); break;
			case 0x77: rom_1709C(); break;
			case 0x78: rom_175DA(); break;
			case 0x79: rom_19068(); break;
			case 0x7A: rom_1947E(); break;
			case 0x7B: rom_A554(); break;
			case 0x7C: rom_1790A(); break;
			case 0x7D: rom_CE3C(); break;
			case 0x7E: rom_CFE4(); break;
			case 0x7F: rom_4E4E(); break;
			case 0x80: rom_4F68(); break;
			case 0x81: rom_19FE2(); break;
			case 0x82: rom_1A310(); break;
			case 0x83: rom_1AC04(); break;
			case 0x84: rom_1A508(); break;
			case 0x85: rom_1AF90(); break;
			case 0x86: rom_53EE(); break;
			case 0x87: rom_5548(); break;
			case 0x88: rom_5622(); break;
			case 0x89: rom_17A10(); break;
			case 0x8A: rom_59F0(); break;
			case 0x8B: rom_5AD0(); break;
		}
	DEF_ROMLOC(D9E4): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(D9E6): move_toreg_32(A0 + 0x40, &A0); // LEA.L	64(A0),A0
	DEF_ROMLOC(D9EA): dec_reg_16(&D7); if ((D7 & 0xffff) != 0xffff) goto rom_D9D6; // DBF.W	D7,$D9D6
	DEF_ROMLOC(D9EE): return; // RTS
}
ROMFUNC(rom_D9C6) {
	DEF_ROMLOC(D9C6): move_toreg_32(0xFFFFD000, &A0); // LEA.L	$D000,A0
	DEF_ROMLOC(D9CA): move_toreg_32(0x7F, &D7); // MOVEQ.L	$7F,D7
	DEF_ROMLOC(D9CC): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(D9CE): cmp_tomem_8(0x6, 0xFFFFD024); // CMPI.B	#$06,$D024
	DEF_ROMLOC(D9D4): if (CCR_CC) goto rom_D9F0; // BCC.B	$D9F0
	rom_D9D6(); return;
	DEF_ROMLOC(D9F0): move_toreg_32(0x1F, &D7); // MOVEQ.L	$1F,D7
	DEF_ROMLOC(D9F2): rom_D9D6(); // BSR.B	$D9D6
	DEF_ROMLOC(D9F4): move_toreg_32(0x5F, &D7); // MOVEQ.L	$5F,D7
	DEF_ROMLOC(D9F6): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(D9F8): move_toreg_8(read_8(A0), &D0); // MOVE.B	(A0),D0
	DEF_ROMLOC(D9FA): if (CCR_EQ) goto rom_DA06; // BEQ.B	$DA06
	DEF_ROMLOC(D9FC): tst_mem_8(A0 + 0x1); // TST.B	1(A0)
	DEF_ROMLOC(DA00): if (CCR_PL) goto rom_DA06; // BPL.B	$DA06
	DEF_ROMLOC(DA02): rom_DC92(); // BSR.W	$DC92
	DEF_ROMLOC(DA06): move_toreg_32(A0 + 0x40, &A0); // LEA.L	64(A0),A0
	DEF_ROMLOC(DA0A): dec_reg_16(&D7); if ((D7 & 0xffff) != 0xffff) goto rom_D9F6; // DBF.W	D7,$D9F6
	DEF_ROMLOC(DA0E): return; // RTS
}*/
ROMFUNC(rom_D87C) {
	DEF_ROMLOC(D87C): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(D87E): move_toreg_8(read_8(A0 + 0x1A), &D0); // MOVE.B	26(A0),D0
	DEF_ROMLOC(D882): add_toreg_16(D0, &D0); // ADD.W	D0,D0
	DEF_ROMLOC(D884): move_toreg_32(read_32(A0 + 0x4), &A3); // MOVEA.L	4(A0),A3
	DEF_ROMLOC(D888): add_toreg_16(read_16((s32)A3 + (s8)0x0 + (s16)D0), &A3); // ADDA.W	0(A3,D0),A3
	DEF_ROMLOC(D88C): add_toreg_16(0x1, &A3); // ADDQ.W	#$01,A3
	DEF_ROMLOC(D88E): bset_tomem_8(0x5, A0 + 0x1); // BSET.B	#$05,1(A0)
	DEF_ROMLOC(D894): move_toreg_8(read_8(A0 + 0x0), &D4); // MOVE.B	0(A0),D4
	DEF_ROMLOC(D898): move_toreg_8(read_8(A0 + 0x1), &D5); // MOVE.B	1(A0),D5
	DEF_ROMLOC(D89C): move_toreg_32(A0, &A1); // MOVEA.L	A0,A1
	DEF_ROMLOC(D89E): goto rom_D8A8; // BRA.B	$D8A8
	DEF_ROMLOC(D8A0): rom_E11A(); // BSR.W	$E11A
	DEF_ROMLOC(D8A4): if (!CCR_EQ) goto rom_D8FA; // BNE.B	$D8FA
	DEF_ROMLOC(D8A6): add_toreg_16(0x5, &A3); // ADDQ.W	#$05,A3
	DEF_ROMLOC(D8A8): move_tomem_8(0x4, A1 + 0x24); // MOVE.B	#$04,36(A1)
	DEF_ROMLOC(D8AE): move_tomem_8(D4, A1 + 0x0); // MOVE.B	D4,0(A1)
	DEF_ROMLOC(D8B2): move_tomem_32(A3, A1 + 0x4); // MOVE.L	A3,4(A1)
	DEF_ROMLOC(D8B6): move_tomem_8(D5, A1 + 0x1); // MOVE.B	D5,1(A1)
	DEF_ROMLOC(D8BA): move_tomem_16(read_16(A0 + 0x8), A1 + 0x8); // MOVE.W	8(A0),8(A1)
	DEF_ROMLOC(D8C0): move_tomem_16(read_16(A0 + 0xC), A1 + 0xC); // MOVE.W	12(A0),12(A1)
	DEF_ROMLOC(D8C6): move_tomem_16(read_16(A0 + 0x2), A1 + 0x2); // MOVE.W	2(A0),2(A1)
	DEF_ROMLOC(D8CC): move_tomem_8(read_8(A0 + 0x18), A1 + 0x18); // MOVE.B	24(A0),24(A1)
	DEF_ROMLOC(D8D2): move_tomem_8(read_8(A0 + 0x19), A1 + 0x19); // MOVE.B	25(A0),25(A1)
	DEF_ROMLOC(D8D8): move_tomem_16(read_16((A4 += 2, A4 - 2)), A1 + 0x10); // MOVE.W	(A4)+,16(A1)
	DEF_ROMLOC(D8DC): move_tomem_16(read_16((A4 += 2, A4 - 2)), A1 + 0x12); // MOVE.W	(A4)+,18(A1)
	DEF_ROMLOC(D8E0): cmp_toreg_32(A0, &A1); // CMPA.L	A0,A1
	DEF_ROMLOC(D8E2): if (CCR_CC) goto rom_D8F6; // BCC.B	$D8F6
	DEF_ROMLOC(D8E4): move_tomem_32(A0, A7 -= 4); // MOVE.L	A0,-(A7)
	DEF_ROMLOC(D8E6): move_toreg_32(A1, &A0); // MOVEA.L	A1,A0
	DEF_ROMLOC(D8E8): rom_DC6C(); // BSR.W	$DC6C
	DEF_ROMLOC(D8EC): add_tomem_16(D2, A0 + 0x12); // ADD.W	D2,18(A0)
	DEF_ROMLOC(D8F0): move_toreg_32(read_32((A7 += 4, A7 - 4)), &A0); // MOVEA.L	(A7)+,A0
	DEF_ROMLOC(D8F2): rom_DCB0(); // BSR.W	$DCB0
	DEF_ROMLOC(D8F6): dec_reg_16(&D1); if ((D1 & 0xffff) != 0xffff) goto rom_D8A0; // DBF.W	D1,$D8A0
	DEF_ROMLOC(D8FA): move_toreg_16(0xCB, &D0); // MOVE.W	#$00CB,D0
	DEF_ROMLOC(D8FE): {rom_1394();return;} // JMP	$00001394
}