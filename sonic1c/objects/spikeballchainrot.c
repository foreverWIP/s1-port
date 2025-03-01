// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_10E56) {
  u8 switchindex = 0;
  DEF_ROMLOC(10E56) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(10E58) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(10E5C)
      : move_toreg_16(read_16(0x10E64 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(10E60): goto rom_10E64 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(10E60) : switch (switchindex) {
  case 0:
    rom_10E6A();
    break;
  case 1:
    rom_10F8A();
    break;
  case 2:
    rom_11026();
    break;
  }
}
ROMFUNC(rom_10E6A) {
  DEF_ROMLOC(10E6A) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(10E6E)
      : move_tomem_32(0x1102A, A0 + 0x4);             // MOVE.L	#$0001102A,4(A0)
  DEF_ROMLOC(10E76) : move_tomem_16(0x3BA, A0 + 0x2); // MOVE.W	#$03BA,2(A0)
  DEF_ROMLOC(10E7C) : move_tomem_8(0x4, A0 + 0x1);    // MOVE.B	#$04,1(A0)
  DEF_ROMLOC(10E82) : move_tomem_8(0x4, A0 + 0x18);   // MOVE.B	#$04,24(A0)
  DEF_ROMLOC(10E88) : move_tomem_8(0x8, A0 + 0x19);   // MOVE.B	#$08,25(A0)
  DEF_ROMLOC(10E8E)
      : move_tomem_16(read_16(A0 + 0x8), A0 + 0x3A); // MOVE.W	8(A0),58(A0)
  DEF_ROMLOC(10E94)
      : move_tomem_16(read_16(A0 + 0xC), A0 + 0x38); // MOVE.W	12(A0),56(A0)
  DEF_ROMLOC(10E9A)
      : move_tomem_8(0xFFFFFF98, A0 + 0x20);          // MOVE.B
                                                      // #$98,32(A0)
  DEF_ROMLOC(10EA0) : cmp_tomem_8(ZONE_LZ, v_zone);   // CMPI.B	#$01,$FE10
  DEF_ROMLOC(10EA6) : if (!CCR_EQ) goto rom_10EBC;    // BNE.B	$10EBC
  DEF_ROMLOC(10EA8) : move_tomem_8(0x0, A0 + 0x20);   // MOVE.B	#$00,32(A0)
  DEF_ROMLOC(10EAE) : move_tomem_16(0x310, A0 + 0x2); // MOVE.W	#$0310,2(A0)
  DEF_ROMLOC(10EB4)
      : move_tomem_32(0x11032, A0 + 0x4); // MOVE.L	#$00011032,4(A0)
  DEF_ROMLOC(10EBC)
      : move_toreg_8(read_8(A0 + 0x28), &D1);       // MOVE.B	40(A0),D1
  DEF_ROMLOC(10EC0) : and_toreg_8(0xFFFFFFF0, &D1); // ANDI.B	#$F0,D1
  DEF_ROMLOC(10EC4) : ext_reg_16(&D1);              // EXT.W	D1
  DEF_ROMLOC(10EC6) : asl_toreg_16(0x3, &D1);       // ASL.W	#$03,D1
  DEF_ROMLOC(10EC8) : move_tomem_16(D1, A0 + 0x3E); // MOVE.W	D1,62(A0)
  DEF_ROMLOC(10ECC)
      : move_toreg_8(read_8(A0 + 0x22), &D0);        // MOVE.B
                                                     // 34(A0),D0
  DEF_ROMLOC(10ED0) : ror_toreg_8(0x2, &D0);         // ROR.B	#$02,D0
  DEF_ROMLOC(10ED2) : and_toreg_8(0xFFFFFFC0, &D0);  // ANDI.B	#$C0,D0
  DEF_ROMLOC(10ED6) : move_tomem_8(D0, A0 + 0x26);   // MOVE.B	D0,38(A0)
  DEF_ROMLOC(10EDA) : move_toreg_32(A0 + 0x29, &A2); // LEA.L	41(A0),A2
  DEF_ROMLOC(10EDE)
      : move_toreg_8(read_8(A0 + 0x28), &D1);        // MOVE.B
                                                     // 40(A0),D1
  DEF_ROMLOC(10EE2) : and_toreg_16(0x7, &D1);        // ANDI.W	#$0007,D1
  DEF_ROMLOC(10EE6) : move_tomem_8(0x0, A2++);       // MOVE.B	#$00,(A2)+
  DEF_ROMLOC(10EEA) : move_toreg_16(D1, &D3);        // MOVE.W	D1,D3
  DEF_ROMLOC(10EEC) : lsl_toreg_16(0x4, &D3);        // LSL.W	#$04,D3
  DEF_ROMLOC(10EEE) : move_tomem_8(D3, A0 + 0x3C);   // MOVE.B	D3,60(A0)
  DEF_ROMLOC(10EF2) : sub_toreg_16(0x1, &D1);        // SUBQ.W	#$01,D1
  DEF_ROMLOC(10EF4) : if (CCR_CS) goto rom_10F68;    // BCS.B	$10F68
  DEF_ROMLOC(10EF6) : btst_tomem_8(0x3, A0 + 0x28);  // BTST.B	#$03,40(A0)
  DEF_ROMLOC(10EFC) : if (CCR_EQ) goto rom_10F02;    // BEQ.B	$10F02
  DEF_ROMLOC(10EFE) : sub_toreg_16(0x1, &D1);        // SUBQ.W	#$01,D1
  DEF_ROMLOC(10F00) : if (CCR_CS) goto rom_10F68;    // BCS.B	$10F68
  DEF_ROMLOC(10F02) : rom_E11A();                    // BSR.W	$E11A
  DEF_ROMLOC(10F06) : if (!CCR_EQ) goto rom_10F68;   // BNE.B	$10F68
  DEF_ROMLOC(10F08) : add_tomem_8(0x1, A0 + 0x29);   // ADDQ.B	#$01,41(A0)
  DEF_ROMLOC(10F0C) : move_toreg_16(A1, &D5);        // MOVE.W	A1,D5
  DEF_ROMLOC(10F0E) : sub_toreg_16(0xFFFFD000, &D5); // SUBI.W	#$D000,D5
  DEF_ROMLOC(10F12) : lsr_toreg_16(0x6, &D5);        // LSR.W	#$06,D5
  DEF_ROMLOC(10F14) : and_toreg_16(0x7F, &D5);       // ANDI.W	#$007F,D5
  DEF_ROMLOC(10F18) : move_tomem_8(D5, A2++);        // MOVE.B	D5,(A2)+
  DEF_ROMLOC(10F1A) : move_tomem_8(0x4, A1 + 0x24);  // MOVE.B	#$04,36(A1)
  DEF_ROMLOC(10F20)
      : move_tomem_8(read_8(A0 + 0x0), A1 + 0x0); // MOVE.B	0(A0),0(A1)
  DEF_ROMLOC(10F26)
      : move_tomem_32(read_32(A0 + 0x4), A1 + 0x4); // MOVE.L	4(A0),4(A1)
  DEF_ROMLOC(10F2C)
      : move_tomem_16(read_16(A0 + 0x2), A1 + 0x2); // MOVE.W	2(A0),2(A1)
  DEF_ROMLOC(10F32)
      : move_tomem_8(read_8(A0 + 0x1), A1 + 0x1); // MOVE.B	1(A0),1(A1)
  DEF_ROMLOC(10F38)
      : move_tomem_8(read_8(A0 + 0x18), A1 + 0x18); // MOVE.B	24(A0),24(A1)
  DEF_ROMLOC(10F3E)
      : move_tomem_8(read_8(A0 + 0x19), A1 + 0x19); // MOVE.B	25(A0),25(A1)
  DEF_ROMLOC(10F44)
      : move_tomem_8(read_8(A0 + 0x20), A1 + 0x20); // MOVE.B	32(A0),32(A1)
  DEF_ROMLOC(10F4A) : sub_toreg_8(0x10, &D3);       // SUBI.B	#$10,D3
  DEF_ROMLOC(10F4E) : move_tomem_8(D3, A1 + 0x3C);  // MOVE.B	D3,60(A1)
  DEF_ROMLOC(10F52) : cmp_tomem_8(ZONE_LZ, v_zone); // CMPI.B	#$01,$FE10
  DEF_ROMLOC(10F58) : if (!CCR_EQ) goto rom_10F64;  // BNE.B	$10F64
  DEF_ROMLOC(10F5A) : tst_reg_8(&D3);               // TST.B	D3
  DEF_ROMLOC(10F5C) : if (!CCR_EQ) goto rom_10F64;  // BNE.B	$10F64
  DEF_ROMLOC(10F5E) : move_tomem_8(0x2, A1 + 0x1A); // MOVE.B	#$02,26(A1)
  DEF_ROMLOC(10F64) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_10F02;                                  // DBF.W	D1,$10F02
  DEF_ROMLOC(10F68) : move_toreg_16(A0, &D5);        // MOVE.W	A0,D5
  DEF_ROMLOC(10F6A) : sub_toreg_16(0xFFFFD000, &D5); // SUBI.W	#$D000,D5
  DEF_ROMLOC(10F6E) : lsr_toreg_16(0x6, &D5);        // LSR.W	#$06,D5
  DEF_ROMLOC(10F70) : and_toreg_16(0x7F, &D5);       // ANDI.W	#$007F,D5
  DEF_ROMLOC(10F74) : move_tomem_8(D5, A2++);        // MOVE.B	D5,(A2)+
  DEF_ROMLOC(10F76) : cmp_tomem_8(ZONE_LZ, v_zone);  // CMPI.B	#$01,$FE10
  DEF_ROMLOC(10F7C) : if (!CCR_EQ) {
    rom_10F8A();
    return;
  } // BNE.B	$10F8A
  DEF_ROMLOC(10F7E)
      : move_tomem_8(0xFFFFFF8B, A0 + 0x20);        // MOVE.B	#$8B,32(A0)
  DEF_ROMLOC(10F84) : move_tomem_8(0x1, A0 + 0x1A); // MOVE.B	#$01,26(A0)
  rom_10F8A(); // Detected flow into next function
}
ROMFUNC(rom_10F92) {
  DEF_ROMLOC(10F92)
      : move_toreg_16(read_16(A0 + 0x3E), &D0);    // MOVE.W	62(A0),D0
  DEF_ROMLOC(10F96) : add_tomem_16(D0, A0 + 0x26); // ADD.W	D0,38(A0)
  DEF_ROMLOC(10F9A)
      : move_toreg_8(read_8(A0 + 0x26), &D0); // MOVE.B
                                              // 38(A0),D0
  DEF_ROMLOC(10F9E) : rom_29D2();             // JSR	$000029D2
  DEF_ROMLOC(10FA4)
      : move_toreg_16(read_16(A0 + 0x38), &D2); // MOVE.W	56(A0),D2
  DEF_ROMLOC(10FA8)
      : move_toreg_16(read_16(A0 + 0x3A), &D3);        // MOVE.W	58(A0),D3
  DEF_ROMLOC(10FAC) : move_toreg_32(A0 + 0x29, &A2);   // LEA.L	41(A0),A2
  DEF_ROMLOC(10FB0) : move_toreg_32(0x0, &D6);         // MOVEQ.L	$00,D6
  DEF_ROMLOC(10FB2) : move_toreg_8(read_8(A2++), &D6); // MOVE.B	(A2)+,D6
  DEF_ROMLOC(10FB4) : move_toreg_32(0x0, &D4);         // MOVEQ.L	$00,D4
  DEF_ROMLOC(10FB6) : move_toreg_8(read_8(A2++), &D4); // MOVE.B	(A2)+,D4
  DEF_ROMLOC(10FB8) : lsl_toreg_16(0x6, &D4);          // LSL.W	#$06,D4
  DEF_ROMLOC(10FBA)
      : add_toreg_32(0xFFD000, &D4);           // ADDI.L	#$00FFD000,D4
  DEF_ROMLOC(10FC0) : move_toreg_32(D4, &A1);  // MOVEA.L	D4,A1
  DEF_ROMLOC(10FC2) : move_toreg_32(0x0, &D4); // MOVEQ.L	$00,D4
  DEF_ROMLOC(10FC4)
      : move_toreg_8(read_8(A1 + 0x3C), &D4);      // MOVE.B	60(A1),D4
  DEF_ROMLOC(10FC8) : move_toreg_32(D4, &D5);      // MOVE.L	D4,D5
  DEF_ROMLOC(10FCA) : muls_toreg_16(D0, &D4);      // MULS.W	D0,D4
  DEF_ROMLOC(10FCC) : asr_toreg_32(0x8, &D4);      // ASR.L	#$08,D4
  DEF_ROMLOC(10FCE) : muls_toreg_16(D1, &D5);      // MULS.W	D1,D5
  DEF_ROMLOC(10FD0) : asr_toreg_32(0x8, &D5);      // ASR.L	#$08,D5
  DEF_ROMLOC(10FD2) : add_toreg_16(D2, &D4);       // ADD.W	D2,D4
  DEF_ROMLOC(10FD4) : add_toreg_16(D3, &D5);       // ADD.W	D3,D5
  DEF_ROMLOC(10FD6) : move_tomem_16(D4, A1 + 0xC); // MOVE.W	D4,12(A1)
  DEF_ROMLOC(10FDA) : move_tomem_16(D5, A1 + 0x8); // MOVE.W	D5,8(A1)
  DEF_ROMLOC(10FDE) : dec_reg_16(&D6);
  if ((D6 & 0xffff) != 0xffff)
    goto rom_10FB4;           // DBF.W	D6,$10FB4
  DEF_ROMLOC(10FE2) : return; // RTS
}
ROMFUNC(rom_10F8A) {
  DEF_ROMLOC(10F8A) : rom_10F92();    // BSR.W	$10F92
  DEF_ROMLOC(10F8E) : goto rom_10FE4; // BRA.W	$10FE4
  DEF_ROMLOC(10F92)
      : move_toreg_16(read_16(A0 + 0x3E), &D0);    // MOVE.W	62(A0),D0
  DEF_ROMLOC(10F96) : add_tomem_16(D0, A0 + 0x26); // ADD.W	D0,38(A0)
  DEF_ROMLOC(10F9A)
      : move_toreg_8(read_8(A0 + 0x26), &D0); // MOVE.B
                                              // 38(A0),D0
  DEF_ROMLOC(10F9E) : rom_29D2();             // JSR	$000029D2
  DEF_ROMLOC(10FA4)
      : move_toreg_16(read_16(A0 + 0x38), &D2); // MOVE.W	56(A0),D2
  DEF_ROMLOC(10FA8)
      : move_toreg_16(read_16(A0 + 0x3A), &D3);        // MOVE.W	58(A0),D3
  DEF_ROMLOC(10FAC) : move_toreg_32(A0 + 0x29, &A2);   // LEA.L	41(A0),A2
  DEF_ROMLOC(10FB0) : move_toreg_32(0x0, &D6);         // MOVEQ.L	$00,D6
  DEF_ROMLOC(10FB2) : move_toreg_8(read_8(A2++), &D6); // MOVE.B	(A2)+,D6
  DEF_ROMLOC(10FB4) : move_toreg_32(0x0, &D4);         // MOVEQ.L	$00,D4
  DEF_ROMLOC(10FB6) : move_toreg_8(read_8(A2++), &D4); // MOVE.B	(A2)+,D4
  DEF_ROMLOC(10FB8) : lsl_toreg_16(0x6, &D4);          // LSL.W	#$06,D4
  DEF_ROMLOC(10FBA)
      : add_toreg_32(0xFFD000, &D4);           // ADDI.L	#$00FFD000,D4
  DEF_ROMLOC(10FC0) : move_toreg_32(D4, &A1);  // MOVEA.L	D4,A1
  DEF_ROMLOC(10FC2) : move_toreg_32(0x0, &D4); // MOVEQ.L	$00,D4
  DEF_ROMLOC(10FC4)
      : move_toreg_8(read_8(A1 + 0x3C), &D4);      // MOVE.B	60(A1),D4
  DEF_ROMLOC(10FC8) : move_toreg_32(D4, &D5);      // MOVE.L	D4,D5
  DEF_ROMLOC(10FCA) : muls_toreg_16(D0, &D4);      // MULS.W	D0,D4
  DEF_ROMLOC(10FCC) : asr_toreg_32(0x8, &D4);      // ASR.L	#$08,D4
  DEF_ROMLOC(10FCE) : muls_toreg_16(D1, &D5);      // MULS.W	D1,D5
  DEF_ROMLOC(10FD0) : asr_toreg_32(0x8, &D5);      // ASR.L	#$08,D5
  DEF_ROMLOC(10FD2) : add_toreg_16(D2, &D4);       // ADD.W	D2,D4
  DEF_ROMLOC(10FD4) : add_toreg_16(D3, &D5);       // ADD.W	D3,D5
  DEF_ROMLOC(10FD6) : move_tomem_16(D4, A1 + 0xC); // MOVE.W	D4,12(A1)
  DEF_ROMLOC(10FDA) : move_tomem_16(D5, A1 + 0x8); // MOVE.W	D5,8(A1)
  DEF_ROMLOC(10FDE) : dec_reg_16(&D6);
  if ((D6 & 0xffff) != 0xffff)
    goto rom_10FB4;           // DBF.W	D6,$10FB4
  DEF_ROMLOC(10FE2) : return; // RTS
  DEF_ROMLOC(10FE4)
      : move_toreg_16(read_16(A0 + 0x3A), &D0);      // MOVE.W	58(A0),D0
  DEF_ROMLOC(10FE8) : and_toreg_16(0xFFFFFF80, &D0); // ANDI.W	#$FF80,D0
  DEF_ROMLOC(10FEC)
      : move_toreg_16(read_16(v_screenposx), &D1);   // MOVE.W	$F700,D1
  DEF_ROMLOC(10FF0) : sub_toreg_16(0x80, &D1);       // SUBI.W	#$0080,D1
  DEF_ROMLOC(10FF4) : and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
  DEF_ROMLOC(10FF8) : sub_toreg_16(D1, &D0);         // SUB.W	D1,D0
  DEF_ROMLOC(10FFA)
      : cmp_toreg_16(128 + GAME_WIDTH + 192, &D0); // CMPI.W	#$0280,D0
  DEF_ROMLOC(10FFE) : if (CCR_HI) goto rom_11006;  // BHI.W	$11006
  DEF_ROMLOC(11002) : rom_DC92();
  return;                                              // BRA.W	$DC92
  DEF_ROMLOC(11006) : move_toreg_32(0x0, &D2);         // MOVEQ.L	$00,D2
  DEF_ROMLOC(11008) : move_toreg_32(A0 + 0x29, &A2);   // LEA.L	41(A0),A2
  DEF_ROMLOC(1100C) : move_toreg_8(read_8(A2++), &D2); // MOVE.B	(A2)+,D2
  DEF_ROMLOC(1100E) : move_toreg_32(0x0, &D0);         // MOVEQ.L	$00,D0
  DEF_ROMLOC(11010) : move_toreg_8(read_8(A2++), &D0); // MOVE.B	(A2)+,D0
  DEF_ROMLOC(11012) : lsl_toreg_16(0x6, &D0);          // LSL.W	#$06,D0
  DEF_ROMLOC(11014) : add_toreg_32(0xFFD000, &D0);     // ADDI.L	#$00FFD000,D0
  DEF_ROMLOC(1101A) : move_toreg_32(D0, &A1);          // MOVEA.L	D0,A1
  DEF_ROMLOC(1101C) : rom_DCD0();                      // BSR.W	$DCD0
  DEF_ROMLOC(11020) : dec_reg_16(&D2);
  if ((D2 & 0xffff) != 0xffff)
    goto rom_1100E;           // DBF.W	D2,$1100E
  DEF_ROMLOC(11024) : return; // RTS
}
ROMFUNC(rom_11026) {
  DEF_ROMLOC(11026) : rom_DC92();
  return; // BRA.W	$DC92
}