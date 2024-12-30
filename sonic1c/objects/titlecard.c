// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"


ROMFUNC(rom_C990) {
  u8 switchindex = 0;
  DEF_ROMLOC(C990) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(C992) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(C996)
      : move_toreg_16(read_16(0xC99E + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(C99A): goto rom_C99E + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(C99A) : switch (switchindex) {
  case 0:
    rom_C9A6();
    break;
  case 1:
    rom_CA3E();
    break;
  case 2:
    rom_CA64();
    break;
  case 3:
    rom_CA64();
    break;
  }
}
ROMFUNC(rom_C9A6) {
  DEF_ROMLOC(C9A6) : move_toreg_32(A0, &A1);  // MOVEA.L	A0,A1
  DEF_ROMLOC(C9A8) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(C9AA)
      : move_toreg_8(read_8(0xFFFFFE10), &D0);        // MOVE.B	$FE10,D0
  DEF_ROMLOC(C9AE) : cmp_tomem_16(0x103, 0xFFFFFE10); // CMPI.W	#$0103,$FE10
  DEF_ROMLOC(C9B4) : if (!CCR_EQ) goto rom_C9B8;      // BNE.B	$C9B8
  DEF_ROMLOC(C9B6) : move_toreg_32(0x5, &D0);         // MOVEQ.L	$05,D0
  DEF_ROMLOC(C9B8) : move_toreg_16(D0, &D2);          // MOVE.W	D0,D2
  DEF_ROMLOC(C9BA) : cmp_tomem_16(0x502, 0xFFFFFE10); // CMPI.W	#$0502,$FE10
  DEF_ROMLOC(C9C0) : if (!CCR_EQ) goto rom_C9C6;      // BNE.B	$C9C6
  DEF_ROMLOC(C9C2) : move_toreg_32(0x6, &D0);         // MOVEQ.L	$06,D0
  DEF_ROMLOC(C9C4) : move_toreg_32(0xB, &D2);         // MOVEQ.L	$0B,D2
  DEF_ROMLOC(C9C6) : move_toreg_32(0xCAD2, &A3);      // LEA.L	$0000CAD2,A3
  DEF_ROMLOC(C9CC) : lsl_toreg_16(0x4, &D0);          // LSL.W	#$04,D0
  DEF_ROMLOC(C9CE) : add_toreg_16(D0, &A3);           // ADDA.W	D0,A3
  DEF_ROMLOC(C9D0) : move_toreg_32(0xCAC2, &A2);      // LEA.L	$0000CAC2,A2
  DEF_ROMLOC(C9D6) : move_toreg_32(0x3, &D1);         // MOVEQ.L	$03,D1
  DEF_ROMLOC(C9D8) : move_tomem_8(0x34, A1 + 0x0);    // MOVE.B	#$34,0(A1)
  DEF_ROMLOC(C9DE)
      : move_tomem_16(read_16(A3), A1 + 0x8); // MOVE.W	(A3),8(A1)
  DEF_ROMLOC(C9E2)
      : move_tomem_16(read_16((A3 += 2, A3 - 2)),
                      A1 + 0x32); // MOVE.W	(A3)+,50(A1)
  DEF_ROMLOC(C9E6)
      : move_tomem_16(read_16((A3 += 2, A3 - 2)),
                      A1 + 0x30); // MOVE.W	(A3)+,48(A1)
  DEF_ROMLOC(C9EA)
      : move_tomem_16(read_16((A2 += 2, A2 - 2)),
                      A1 + 0xA); // MOVE.W	(A2)+,10(A1)
  DEF_ROMLOC(C9EE)
      : move_tomem_8(read_8(A2++), A1 + 0x24);        // MOVE.B	(A2)+,36(A1)
  DEF_ROMLOC(C9F2) : move_toreg_8(read_8(A2++), &D0); // MOVE.B	(A2)+,D0
  DEF_ROMLOC(C9F4) : if (!CCR_EQ) goto rom_C9F8;      // BNE.B	$C9F8
  DEF_ROMLOC(C9F6) : move_toreg_8(D2, &D0);           // MOVE.B	D2,D0
  DEF_ROMLOC(C9F8) : cmp_toreg_8(0x7, &D0);           // CMPI.B	#$07,D0
  DEF_ROMLOC(C9FC) : if (!CCR_EQ) goto rom_CA0C;      // BNE.B	$CA0C
  DEF_ROMLOC(C9FE)
      : add_toreg_8(read_8(0xFFFFFE11), &D0);      // ADD.B	$FE11,D0
  DEF_ROMLOC(CA02) : cmp_tomem_8(0x3, 0xFFFFFE11); // CMPI.B	#$03,$FE11
  DEF_ROMLOC(CA08) : if (!CCR_EQ) goto rom_CA0C;   // BNE.B	$CA0C
  DEF_ROMLOC(CA0A) : sub_toreg_8(0x1, &D0);        // SUBQ.B	#$01,D0
  DEF_ROMLOC(CA0C) : move_tomem_8(D0, A1 + 0x1A);  // MOVE.B	D0,26(A1)
  DEF_ROMLOC(CA10)
      : move_tomem_32(0xD074, A1 + 0x4); // MOVE.L	#$0000D074,4(A1)
  DEF_ROMLOC(CA18)
      : move_tomem_16(0xFFFF8580, A1 + 0x2);         // MOVE.W	#$8580,2(A1)
  DEF_ROMLOC(CA1E) : move_tomem_8(0x78, A1 + 0x19);  // MOVE.B	#$78,25(A1)
  DEF_ROMLOC(CA24) : move_tomem_8(0x0, A1 + 0x1);    // MOVE.B	#$00,1(A1)
  DEF_ROMLOC(CA2A) : move_tomem_8(0x0, A1 + 0x18);   // MOVE.B	#$00,24(A1)
  DEF_ROMLOC(CA30) : move_tomem_16(0x3C, A1 + 0x1E); // MOVE.W	#$003C,30(A1)
  DEF_ROMLOC(CA36) : move_toreg_32(A1 + 0x40, &A1);  // LEA.L	64(A1),A1
  DEF_ROMLOC(CA3A) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_C9D8; // DBF.W	D1,$C9D8
  rom_CA3E();      // Detected flow into next function
}
ROMFUNC(rom_CA3E) {
  DEF_ROMLOC(CA3E) : move_toreg_32(0x10, &D1); // MOVEQ.L	$10,D1
  DEF_ROMLOC(CA40)
      : move_toreg_16(read_16(A0 + 0x30), &D0); // MOVE.W	48(A0),D0
  DEF_ROMLOC(CA44)
      : cmp_toreg_16(read_16(A0 + 0x8), &D0);    // CMP.W	8(A0),D0
  DEF_ROMLOC(CA48) : if (CCR_EQ) goto rom_CA52;  // BEQ.B	$CA52
  DEF_ROMLOC(CA4A) : if (CCR_GE) goto rom_CA4E;  // BGE.B	$CA4E
  DEF_ROMLOC(CA4C) : neg_reg_16(&D1);            // NEG.W	D1
  DEF_ROMLOC(CA4E) : add_tomem_16(D1, A0 + 0x8); // ADD.W	D1,8(A0)
  DEF_ROMLOC(CA52)
      : move_toreg_16(read_16(A0 + 0x8), &D0);  // MOVE.W	8(A0),D0
  DEF_ROMLOC(CA56) : if (CCR_MI) goto rom_CA62; // BMI.B	$CA62
  DEF_ROMLOC(CA58) : cmp_toreg_16(0x200, &D0);  // CMPI.W	#$0200,D0
  DEF_ROMLOC(CA5C) : if (CCR_CC) goto rom_CA62; // BCC.B	$CA62
  rom_DC92();
  return;                    // BRA.W	$DC92
  DEF_ROMLOC(CA62) : return; // RTS
}
ROMFUNC(rom_CA64) {
  DEF_ROMLOC(CA64) : tst_mem_16(A0 + 0x1E);        // TST.W	30(A0)
  DEF_ROMLOC(CA68) : if (CCR_EQ) goto rom_CA72;    // BEQ.B	$CA72
  DEF_ROMLOC(CA6A) : sub_tomem_16(0x1, A0 + 0x1E); // SUBQ.W	#$01,30(A0)
  rom_DC92();
  return;                                       // BRA.W	$DC92
  DEF_ROMLOC(CA72) : tst_mem_8(A0 + 0x1);       // TST.B	1(A0)
  DEF_ROMLOC(CA76) : if (CCR_PL) goto rom_CA9E; // BPL.B	$CA9E
  DEF_ROMLOC(CA78) : move_toreg_32(0x20, &D1);  // MOVEQ.L	$20,D1
  DEF_ROMLOC(CA7A)
      : move_toreg_16(read_16(A0 + 0x32), &D0); // MOVE.W	50(A0),D0
  DEF_ROMLOC(CA7E)
      : cmp_toreg_16(read_16(A0 + 0x8), &D0);    // CMP.W	8(A0),D0
  DEF_ROMLOC(CA82) : if (CCR_EQ) goto rom_CA9E;  // BEQ.B	$CA9E
  DEF_ROMLOC(CA84) : if (CCR_GE) goto rom_CA88;  // BGE.B	$CA88
  DEF_ROMLOC(CA86) : neg_reg_16(&D1);            // NEG.W	D1
  DEF_ROMLOC(CA88) : add_tomem_16(D1, A0 + 0x8); // ADD.W	D1,8(A0)
  DEF_ROMLOC(CA8C)
      : move_toreg_16(read_16(A0 + 0x8), &D0);  // MOVE.W	8(A0),D0
  DEF_ROMLOC(CA90) : if (CCR_MI) goto rom_CA9C; // BMI.B	$CA9C
  DEF_ROMLOC(CA92) : cmp_toreg_16(0x200, &D0);  // CMPI.W	#$0200,D0
  DEF_ROMLOC(CA96) : if (CCR_CC) goto rom_CA9C; // BCC.B	$CA9C
  rom_DC92();
  return;                                         // BRA.W	$DC92
  DEF_ROMLOC(CA9C) : return;                      // RTS
  DEF_ROMLOC(CA9E) : cmp_tomem_8(0x4, A0 + 0x24); // CMPI.B	#$04,36(A0)
  DEF_ROMLOC(CAA4) : if (!CCR_EQ) goto rom_CABE;  // BNE.B	$CABE
  DEF_ROMLOC(CAA6) : move_toreg_32(0x2, &D0);     // MOVEQ.L	$02,D0
  DEF_ROMLOC(CAA8) : rom_1578();                  // JSR	$00001578
  DEF_ROMLOC(CAAE) : move_toreg_32(0x0, &D0);     // MOVEQ.L	$00,D0
  DEF_ROMLOC(CAB0)
      : move_toreg_8(read_8(0xFFFFFE10), &D0); // MOVE.B	$FE10,D0
  DEF_ROMLOC(CAB4) : add_toreg_16(0x15, &D0);  // ADDI.W	#$0015,D0
  DEF_ROMLOC(CAB8) : rom_1578();               // JSR	$00001578
  DEF_ROMLOC(CABE) : rom_DCCE();               // BRA.W	$DCCE
}