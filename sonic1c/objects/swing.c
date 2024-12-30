// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_7FD0) {
  u8 switchindex = 0;
  DEF_ROMLOC(7FD0) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(7FD2) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(7FD6)
      : move_toreg_16(read_16(0x7FDE + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(7FDA): goto rom_7FDE + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(7FDA) : switch (switchindex) {
  case 0:
    rom_7FEC();
    break;
  case 1:
    rom_815A();
    break;
  case 2:
    rom_8176();
    break;
  case 3:
    rom_82BC();
    break;
  case 4:
    rom_82BC();
    break;
  case 5:
    rom_82C2();
    break;
  case 6:
    rom_816A();
    break;
  }
}
ROMFUNC(rom_7FEC) {
  DEF_ROMLOC(7FEC) : add_tomem_8(0x2, A0 + 0x24);     // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(7FF0) : move_tomem_32(0x82C6, A0 + 0x4); // MOVE.L	#$000082C6,4(A0)
  DEF_ROMLOC(7FF8) : move_tomem_16(0x4380, A0 + 0x2); // MOVE.W	#$4380,2(A0)
  DEF_ROMLOC(7FFE) : move_tomem_8(0x4, A0 + 0x1);     // MOVE.B	#$04,1(A0)
  DEF_ROMLOC(8004) : move_tomem_8(0x3, A0 + 0x18);    // MOVE.B	#$03,24(A0)
  DEF_ROMLOC(800A) : move_tomem_8(0x18, A0 + 0x19);   // MOVE.B	#$18,25(A0)
  DEF_ROMLOC(8010) : move_tomem_8(0x8, A0 + 0x16);    // MOVE.B	#$08,22(A0)
  DEF_ROMLOC(8016)
      : move_tomem_16(read_16(A0 + 0xC), A0 + 0x38); // MOVE.W	12(A0),56(A0)
  DEF_ROMLOC(801C)
      : move_tomem_16(read_16(A0 + 0x8), A0 + 0x3A);  // MOVE.W	8(A0),58(A0)
  DEF_ROMLOC(8022) : cmp_tomem_8(0x3, 0xFFFFFE10);    // CMPI.B	#$03,$FE10
  DEF_ROMLOC(8028) : if (!CCR_EQ) goto rom_804A;      // BNE.B	$804A
  DEF_ROMLOC(802A) : move_tomem_32(0x82E4, A0 + 0x4); // MOVE.L	#$000082E4,4(A0)
  DEF_ROMLOC(8032) : move_tomem_16(0x43DC, A0 + 0x2); // MOVE.W	#$43DC,2(A0)
  DEF_ROMLOC(8038) : move_tomem_8(0x20, A0 + 0x19);   // MOVE.B	#$20,25(A0)
  DEF_ROMLOC(803E) : move_tomem_8(0x10, A0 + 0x16);   // MOVE.B	#$10,22(A0)
  DEF_ROMLOC(8044)
      : move_tomem_8(0xFFFFFF99, A0 + 0x20);       // MOVE.B	#$99,32(A0)
  DEF_ROMLOC(804A) : cmp_tomem_8(0x5, 0xFFFFFE10); // CMPI.B	#$05,$FE10
  DEF_ROMLOC(8050) : if (!CCR_EQ) goto rom_8078;   // BNE.B	$8078
  DEF_ROMLOC(8052)
      : move_tomem_32(0x11174, A0 + 0x4);            // MOVE.L	#$00011174,4(A0)
  DEF_ROMLOC(805A) : move_tomem_16(0x391, A0 + 0x2); // MOVE.W	#$0391,2(A0)
  DEF_ROMLOC(8060) : move_tomem_8(0x18, A0 + 0x19);  // MOVE.B	#$18,25(A0)
  DEF_ROMLOC(8066) : move_tomem_8(0x18, A0 + 0x16);  // MOVE.B	#$18,22(A0)
  DEF_ROMLOC(806C)
      : move_tomem_8(0xFFFFFF86, A0 + 0x20);              // MOVE.B	#$86,32(A0)
  DEF_ROMLOC(8072) : move_tomem_8(0xC, A0 + 0x24);        // MOVE.B	#$0C,36(A0)
  DEF_ROMLOC(8078) : move_toreg_8(read_8(A0 + 0x0), &D4); // MOVE.B	0(A0),D4
  DEF_ROMLOC(807C) : move_toreg_32(0x0, &D1);             // MOVEQ.L	$00,D1
  DEF_ROMLOC(807E) : move_toreg_32(A0 + 0x28, &A2);       // LEA.L	40(A0),A2
  DEF_ROMLOC(8082) : move_toreg_8(read_8(A2), &D1);       // MOVE.B	(A2),D1
  DEF_ROMLOC(8084) : move_tomem_16(D1, A7 -= 2);          // MOVE.W	D1,-(A7)
  DEF_ROMLOC(8086) : and_toreg_16(0xF, &D1);              // ANDI.W	#$000F,D1
  DEF_ROMLOC(808A) : move_tomem_8(0x0, A2++);             // MOVE.B	#$00,(A2)+
  DEF_ROMLOC(808E) : move_toreg_16(D1, &D3);              // MOVE.W	D1,D3
  DEF_ROMLOC(8090) : lsl_toreg_16(0x4, &D3);              // LSL.W	#$04,D3
  DEF_ROMLOC(8092) : add_toreg_8(0x8, &D3);               // ADDQ.B	#$08,D3
  DEF_ROMLOC(8094) : move_tomem_8(D3, A0 + 0x3C);         // MOVE.B	D3,60(A0)
  DEF_ROMLOC(8098) : sub_toreg_8(0x8, &D3);               // SUBQ.B	#$08,D3
  DEF_ROMLOC(809A) : tst_mem_8(A0 + 0x1A);                // TST.B	26(A0)
  DEF_ROMLOC(809E) : if (CCR_EQ) goto rom_80A4;           // BEQ.B	$80A4
  DEF_ROMLOC(80A0) : add_toreg_8(0x8, &D3);               // ADDQ.B	#$08,D3
  DEF_ROMLOC(80A2) : sub_toreg_16(0x1, &D1);              // SUBQ.W	#$01,D1
  DEF_ROMLOC(80A4) : rom_E11A();                          // BSR.W	$E11A
  DEF_ROMLOC(80A8) : if (!CCR_EQ) goto rom_8110;          // BNE.B	$8110
  DEF_ROMLOC(80AA) : add_tomem_8(0x1, A0 + 0x28);         // ADDQ.B	#$01,40(A0)
  DEF_ROMLOC(80AE) : move_toreg_16(A1, &D5);              // MOVE.W	A1,D5
  DEF_ROMLOC(80B0) : sub_toreg_16(0xFFFFD000, &D5);       // SUBI.W	#$D000,D5
  DEF_ROMLOC(80B4) : lsr_toreg_16(0x6, &D5);              // LSR.W	#$06,D5
  DEF_ROMLOC(80B6) : and_toreg_16(0x7F, &D5);             // ANDI.W	#$007F,D5
  DEF_ROMLOC(80BA) : move_tomem_8(D5, A2++);              // MOVE.B	D5,(A2)+
  DEF_ROMLOC(80BC) : move_tomem_8(0xA, A1 + 0x24);        // MOVE.B	#$0A,36(A1)
  DEF_ROMLOC(80C2) : move_tomem_8(D4, A1 + 0x0);          // MOVE.B	D4,0(A1)
  DEF_ROMLOC(80C6)
      : move_tomem_32(read_32(A0 + 0x4), A1 + 0x4); // MOVE.L	4(A0),4(A1)
  DEF_ROMLOC(80CC)
      : move_tomem_16(read_16(A0 + 0x2), A1 + 0x2); // MOVE.W	2(A0),2(A1)
  DEF_ROMLOC(80D2) : bclr_tomem_8(0x6, A1 + 0x2);   // BCLR.B	#$06,2(A1)
  DEF_ROMLOC(80D8) : move_tomem_8(0x4, A1 + 0x1);   // MOVE.B	#$04,1(A1)
  DEF_ROMLOC(80DE) : move_tomem_8(0x4, A1 + 0x18);  // MOVE.B	#$04,24(A1)
  DEF_ROMLOC(80E4) : move_tomem_8(0x8, A1 + 0x19);  // MOVE.B	#$08,25(A1)
  DEF_ROMLOC(80EA) : move_tomem_8(0x1, A1 + 0x1A);  // MOVE.B	#$01,26(A1)
  DEF_ROMLOC(80F0) : move_tomem_8(D3, A1 + 0x3C);   // MOVE.B	D3,60(A1)
  DEF_ROMLOC(80F4) : sub_toreg_8(0x10, &D3);        // SUBI.B	#$10,D3
  DEF_ROMLOC(80F8) : if (CCR_CC) goto rom_810C;     // BCC.B	$810C
  DEF_ROMLOC(80FA) : move_tomem_8(0x2, A1 + 0x1A);  // MOVE.B	#$02,26(A1)
  DEF_ROMLOC(8100) : move_tomem_8(0x3, A1 + 0x18);  // MOVE.B	#$03,24(A1)
  DEF_ROMLOC(8106) : bset_tomem_8(0x6, A1 + 0x2);   // BSET.B	#$06,2(A1)
  DEF_ROMLOC(810C) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_80A4;                                  // DBF.W	D1,$80A4
  DEF_ROMLOC(8110) : move_toreg_16(A0, &D5);        // MOVE.W	A0,D5
  DEF_ROMLOC(8112) : sub_toreg_16(0xFFFFD000, &D5); // SUBI.W	#$D000,D5
  DEF_ROMLOC(8116) : lsr_toreg_16(0x6, &D5);        // LSR.W	#$06,D5
  DEF_ROMLOC(8118) : and_toreg_16(0x7F, &D5);       // ANDI.W	#$007F,D5
  DEF_ROMLOC(811C) : move_tomem_8(D5, A2++);        // MOVE.B	D5,(A2)+
  DEF_ROMLOC(811E)
      : move_tomem_16(0x4080, A0 + 0x26); // MOVE.W
                                          // #$4080,38(A0)
  DEF_ROMLOC(8124)
      : move_tomem_16(0xFFFFFE00, A0 + 0x3E); // MOVE.W	#$FE00,62(A0)
  DEF_ROMLOC(812A)
      : move_toreg_16(read_16((A7 += 2, A7 - 2)), &D1); // MOVE.W	(A7)+,D1
  DEF_ROMLOC(812C) : btst_toreg_32(0x4, &D1);           // BTST.L	#$04,D1
  DEF_ROMLOC(8130) : if (CCR_EQ) goto rom_8152;         // BEQ.B	$8152
  DEF_ROMLOC(8132) : move_tomem_32(0x8828, A0 + 0x4); // MOVE.L	#$00008828,4(A0)
  DEF_ROMLOC(813A) : move_tomem_16(0x43AA, A0 + 0x2); // MOVE.W	#$43AA,2(A0)
  DEF_ROMLOC(8140) : move_tomem_8(0x1, A0 + 0x1A);    // MOVE.B	#$01,26(A0)
  DEF_ROMLOC(8146) : move_tomem_8(0x2, A0 + 0x18);    // MOVE.B	#$02,24(A0)
  DEF_ROMLOC(814C)
      : move_tomem_8(0xFFFFFF81, A0 + 0x20);       // MOVE.B	#$81,32(A0)
  DEF_ROMLOC(8152) : cmp_tomem_8(0x5, 0xFFFFFE10); // CMPI.B	#$05,$FE10
  DEF_ROMLOC(8158) : if (CCR_EQ) {
    rom_816A();
    return;
  }           // BEQ.B	$816A
  rom_815A(); // Detected flow into next function
}
ROMFUNC(rom_815A) {
  DEF_ROMLOC(815A) : move_toreg_32(0x0, &D1);              // MOVEQ.L	$00,D1
  DEF_ROMLOC(815C) : move_toreg_8(read_8(A0 + 0x19), &D1); // MOVE.B
                                                           // 25(A0),D1
  DEF_ROMLOC(8160) : move_toreg_32(0x0, &D3);              // MOVEQ.L	$00,D3
  DEF_ROMLOC(8162) : move_toreg_8(read_8(A0 + 0x16), &D3); // MOVE.B
                                                           // 22(A0),D3
  DEF_ROMLOC(8166) : rom_7BDA();                           // BSR.W	$7BDA
  rom_816A(); // Detected flow into next function
}
ROMFUNC(rom_816A) {
  DEF_ROMLOC(816A) : rom_81E2(); // BSR.W	$81E2
  DEF_ROMLOC(816E) : rom_DC92(); // BSR.W	$DC92
  rom_827C();                    // BRA.W	$827C
}
ROMFUNC(rom_8176) {
  DEF_ROMLOC(8176) : move_toreg_32(0x0, &D1);              // MOVEQ.L	$00,D1
  DEF_ROMLOC(8178) : move_toreg_8(read_8(A0 + 0x19), &D1); // MOVE.B
                                                           // 25(A0),D1
  DEF_ROMLOC(817C) : rom_7C3E();                           // BSR.W	$7C3E
  DEF_ROMLOC(8180)
      : move_tomem_16(read_16(A0 + 0x8), A7 -= 2); // MOVE.W	8(A0),-(A7)
  DEF_ROMLOC(8184) : rom_81E2();                   // BSR.W	$81E2
  DEF_ROMLOC(8188)
      : move_toreg_16(read_16((A7 += 2, A7 - 2)), &D2);    // MOVE.W	(A7)+,D2
  DEF_ROMLOC(818A) : move_toreg_32(0x0, &D3);              // MOVEQ.L	$00,D3
  DEF_ROMLOC(818C) : move_toreg_8(read_8(A0 + 0x16), &D3); // MOVE.B
                                                           // 22(A0),D3
  DEF_ROMLOC(8190) : add_toreg_8(0x1, &D3);                // ADDQ.B	#$01,D3
  DEF_ROMLOC(8192) : rom_81A0();                           // BSR.W	$81A0
  DEF_ROMLOC(8196) : rom_DC92();                           // BSR.W	$DC92
  DEF_ROMLOC(819A) : {
    rom_827C();
    return;
  }                          // BRA.W	$827C
  DEF_ROMLOC(819E) : return; // RTS
}
ROMFUNC(rom_81E2) {
  DEF_ROMLOC(81E2)
      : move_toreg_8(read_8(0xFFFFFE78), &D0);     // MOVE.B	$FE78,D0
  DEF_ROMLOC(81E6) : move_toreg_16(0x80, &D1);     // MOVE.W	#$0080,D1
  DEF_ROMLOC(81EA) : btst_tomem_8(0x0, A0 + 0x22); // BTST.B	#$00,34(A0)
  DEF_ROMLOC(81F0) : if (CCR_EQ) goto rom_81F6;    // BEQ.B	$81F6
  DEF_ROMLOC(81F2) : neg_reg_16(&D0);              // NEG.W	D0
  DEF_ROMLOC(81F4) : add_toreg_16(D1, &D0);        // ADD.W	D1,D0
  DEF_ROMLOC(81F6) : rom_8238();                   // BRA.B	$8238
}
ROMFUNC(rom_81F8) {
  DEF_ROMLOC(81F8) : tst_mem_8(A0 + 0x3D);                   // TST.B	61(A0)
  DEF_ROMLOC(81FC) : if (!CCR_EQ) goto rom_821A;             // BNE.B	$821A
  DEF_ROMLOC(81FE) : move_toreg_16(read_16(A0 + 0x3E), &D0); // MOVE.W
                                                             // 62(A0),D0
  DEF_ROMLOC(8202) : add_toreg_16(0x8, &D0);                 // ADDQ.W	#$08,D0
  DEF_ROMLOC(8204) : move_tomem_16(D0, A0 + 0x3E);           // MOVE.W	D0,62(A0)
  DEF_ROMLOC(8208) : add_tomem_16(D0, A0 + 0x26);            // ADD.W	D0,38(A0)
  DEF_ROMLOC(820C) : cmp_toreg_16(0x200, &D0);               // CMPI.W	#$0200,D0
  DEF_ROMLOC(8210) : if (!CCR_EQ) goto rom_8234;             // BNE.B	$8234
  DEF_ROMLOC(8212) : move_tomem_8(0x1, A0 + 0x3D); // MOVE.B	#$01,61(A0)
  goto rom_8234;                                   // BRA.B	$8234
  DEF_ROMLOC(821A) : move_toreg_16(read_16(A0 + 0x3E), &D0); // MOVE.W
                                                             // 62(A0),D0
  DEF_ROMLOC(821E) : sub_toreg_16(0x8, &D0);                 // SUBQ.W	#$08,D0
  DEF_ROMLOC(8220) : move_tomem_16(D0, A0 + 0x3E);           // MOVE.W	D0,62(A0)
  DEF_ROMLOC(8224) : add_tomem_16(D0, A0 + 0x26);            // ADD.W	D0,38(A0)
  DEF_ROMLOC(8228) : cmp_toreg_16(0xFFFFFE00, &D0);          // CMPI.W	#$FE00,D0
  DEF_ROMLOC(822C) : if (!CCR_EQ) goto rom_8234;             // BNE.B	$8234
  DEF_ROMLOC(822E) : move_tomem_8(0x0, A0 + 0x3D);         // MOVE.B	#$00,61(A0)
  DEF_ROMLOC(8234) : move_toreg_8(read_8(A0 + 0x26), &D0); // MOVE.B
                                                           // 38(A0),D0
  rom_8238(); // Detected flow into next function
}
ROMFUNC(rom_8238) {
  DEF_ROMLOC(8238) : rom_29D2(); // BSR.W	$29D2
  DEF_ROMLOC(823C)
      : move_toreg_16(read_16(A0 + 0x38), &D2);              // MOVE.W	56(A0),D2
  DEF_ROMLOC(8240) : move_toreg_16(read_16(A0 + 0x3A), &D3); // MOVE.W
                                                             // 58(A0),D3
  DEF_ROMLOC(8244) : move_toreg_32(A0 + 0x28, &A2);          // LEA.L	40(A0),A2
  DEF_ROMLOC(8248) : move_toreg_32(0x0, &D6);                // MOVEQ.L	$00,D6
  DEF_ROMLOC(824A) : move_toreg_8(read_8(A2++), &D6);        // MOVE.B	(A2)+,D6
  rom_824C(); // Detected flow into next function
}
ROMFUNC(rom_824C) {
  DEF_ROMLOC(824C) : move_toreg_32(0x0, &D4);         // MOVEQ.L	$00,D4
  DEF_ROMLOC(824E) : move_toreg_8(read_8(A2++), &D4); // MOVE.B	(A2)+,D4
  DEF_ROMLOC(8250) : lsl_toreg_16(0x6, &D4);          // LSL.W	#$06,D4
  DEF_ROMLOC(8252) : add_toreg_32(0xFFD000, &D4);     // ADDI.L	#$00FFD000,D4
  DEF_ROMLOC(8258) : move_toreg_32(D4, &A1);          // MOVEA.L	D4,A1
  DEF_ROMLOC(825A) : move_toreg_32(0x0, &D4);         // MOVEQ.L	$00,D4
  DEF_ROMLOC(825C)
      : move_toreg_8(read_8(A1 + 0x3C), &D4);     // MOVE.B	60(A1),D4
  DEF_ROMLOC(8260) : move_toreg_32(D4, &D5);      // MOVE.L	D4,D5
  DEF_ROMLOC(8262) : muls_toreg_16(D0, &D4);      // MULS.W	D0,D4
  DEF_ROMLOC(8264) : asr_toreg_32(0x8, &D4);      // ASR.L	#$08,D4
  DEF_ROMLOC(8266) : muls_toreg_16(D1, &D5);      // MULS.W	D1,D5
  DEF_ROMLOC(8268) : asr_toreg_32(0x8, &D5);      // ASR.L	#$08,D5
  DEF_ROMLOC(826A) : add_toreg_16(D2, &D4);       // ADD.W	D2,D4
  DEF_ROMLOC(826C) : add_toreg_16(D3, &D5);       // ADD.W	D3,D5
  DEF_ROMLOC(826E) : move_tomem_16(D4, A1 + 0xC); // MOVE.W	D4,12(A1)
  DEF_ROMLOC(8272) : move_tomem_16(D5, A1 + 0x8); // MOVE.W	D5,8(A1)
  DEF_ROMLOC(8276) : dec_reg_16(&D6);
  if ((D6 & 0xffff) != 0xffff)
    goto rom_824C;           // DBF.W	D6,$824C
  DEF_ROMLOC(827A) : return; // RTS
}
ROMFUNC(rom_827C) {
  DEF_ROMLOC(827C)
      : move_toreg_16(read_16(A0 + 0x3A), &D0);     // MOVE.W	58(A0),D0
  DEF_ROMLOC(8280) : and_toreg_16(0xFFFFFF80, &D0); // ANDI.W	#$FF80,D0
  DEF_ROMLOC(8284)
      : move_toreg_16(read_16(0xFFFFF700), &D1);    // MOVE.W	$F700,D1
  DEF_ROMLOC(8288) : sub_toreg_16(0x80, &D1);       // SUBI.W	#$0080,D1
  DEF_ROMLOC(828C) : and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
  DEF_ROMLOC(8290) : sub_toreg_16(D1, &D0);         // SUB.W	D1,D0
  DEF_ROMLOC(8292) : cmp_toreg_16(0x280, &D0);      // CMPI.W	#$0280,D0
  DEF_ROMLOC(8296) : if (CCR_HI) {
    rom_829C();
    return;
  }                          // BHI.W	$829C
  DEF_ROMLOC(829A) : return; // RTS
}
ROMFUNC(rom_829C) {
  DEF_ROMLOC(829C) : move_toreg_32(0x0, &D2);         // MOVEQ.L	$00,D2
  DEF_ROMLOC(829E) : move_toreg_32(A0 + 0x28, &A2);   // LEA.L	40(A0),A2
  DEF_ROMLOC(82A2) : move_toreg_8(read_8(A2++), &D2); // MOVE.B	(A2)+,D2
  rom_82A4(); // Detected flow into next function
}
ROMFUNC(rom_82A4) {
  DEF_ROMLOC(82A4) : move_toreg_32(0x0, &D0);         // MOVEQ.L	$00,D0
  DEF_ROMLOC(82A6) : move_toreg_8(read_8(A2++), &D0); // MOVE.B	(A2)+,D0
  DEF_ROMLOC(82A8) : lsl_toreg_16(0x6, &D0);          // LSL.W	#$06,D0
  DEF_ROMLOC(82AA) : add_toreg_32(0xFFD000, &D0);     // ADDI.L	#$00FFD000,D0
  DEF_ROMLOC(82B0) : move_toreg_32(D0, &A1);          // MOVEA.L	D0,A1
  DEF_ROMLOC(82B2) : rom_DCD0();                      // BSR.W	$DCD0
  DEF_ROMLOC(82B6) : dec_reg_16(&D2);
  if ((D2 & 0xffff) != 0xffff)
    goto rom_82A4;           // DBF.W	D2,$82A4
  DEF_ROMLOC(82BA) : return; // RTS
}
ROMFUNC(rom_82BC) {
  DEF_ROMLOC(82BC) : rom_DCCE(); // BSR.W	$DCCE
  DEF_ROMLOC(82C0) : return;     // RTS
}
ROMFUNC(rom_82C2) {
  DEF_ROMLOC(82C2) : rom_DC92(); // BRA.W	$DC92
}