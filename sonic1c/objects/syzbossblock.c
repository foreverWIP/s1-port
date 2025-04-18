// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_19E42) {
  u8 switchindex = 0;
  DEF_ROMLOC(19E42) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(19E44) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(19E48)
      : move_toreg_16(read_16(0x19E50 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(19E4C): goto rom_19E50 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(19E4C) : switch (switchindex) {
  case 0:
    rom_19E56();
    break;
  case 1:
    rom_19EB4();
    break;
  case 2:
    rom_19F12();
    break;
  }
}
ROMFUNC(rom_19E56) {
  DEF_ROMLOC(19E56) : move_toreg_32(0x0, &D4);     // MOVEQ.L	$00,D4
  DEF_ROMLOC(19E58) : move_toreg_16(0x2C10, &D5);  // MOVE.W	#$2C10,D5
  DEF_ROMLOC(19E5C) : move_toreg_32(0x9, &D6);     // MOVEQ.L	$09,D6
  DEF_ROMLOC(19E5E) : move_toreg_32(A0, &A1);      // LEA.L	(A0),A1
  goto rom_19E6A;                                  // BRA.B	$19E6A
  DEF_ROMLOC(19E62) : rom_E11A();                  // JSR	$0000E11A
  DEF_ROMLOC(19E68) : if (!CCR_EQ) goto rom_19EB2; // BNE.B	$19EB2
  DEF_ROMLOC(19E6A)
      : move_tomem_8(OBJ_BOSSBLOCK,
                     A1 + offsetof(object, id)); // MOVE.B	#$76,(A1)
  DEF_ROMLOC(19E6E)
      : move_tomem_32(0x19FAE, A1 + 0x4); // MOVE.L	#$00019FAE,4(A1)
  DEF_ROMLOC(19E76)
      : move_tomem_16(0x4000, A1 + 0x2);           // MOVE.W
                                                   // #$4000,2(A1)
  DEF_ROMLOC(19E7C) : move_tomem_8(0x4, A1 + 0x1); // MOVE.B	#$04,1(A1)
  DEF_ROMLOC(19E82)
      : move_tomem_8(0x10, A1 + 0x19);                // MOVE.B	#$10,25(A1)
  DEF_ROMLOC(19E88) : move_tomem_8(0x10, A1 + 0x16);  // MOVE.B	#$10,22(A1)
  DEF_ROMLOC(19E8E) : move_tomem_8(0x3, A1 + 0x18);   // MOVE.B	#$03,24(A1)
  DEF_ROMLOC(19E94) : move_tomem_16(D5, A1 + 0x8);    // MOVE.W	D5,8(A1)
  DEF_ROMLOC(19E98) : move_tomem_16(0x582, A1 + 0xC); // MOVE.W	#$0582,12(A1)
  DEF_ROMLOC(19E9E) : move_tomem_16(D4, A1 + 0x28);   // MOVE.W	D4,40(A1)
  DEF_ROMLOC(19EA2) : add_toreg_16(0x101, &D4);       // ADDI.W	#$0101,D4
  DEF_ROMLOC(19EA6) : add_toreg_16(0x20, &D5);        // ADDI.W	#$0020,D5
  DEF_ROMLOC(19EAA) : add_tomem_8(0x2, A1 + 0x24);    // ADDQ.B	#$02,36(A1)
  DEF_ROMLOC(19EAE) : dec_reg_16(&D6);
  if ((D6 & 0xffff) != 0xffff)
    goto rom_19E62;           // DBF.W	D6,$19E62
  DEF_ROMLOC(19EB2) : return; // RTS
}
ROMFUNC(rom_19EB4) {
  DEF_ROMLOC(19EB4)
      : move_toreg_8(read_8(A0 + 0x29), &D0); // MOVE.B
                                              // 41(A0),D0
  DEF_ROMLOC(19EB8)
      : cmp_toreg_8(read_8(A0 + 0x28), &D0);      // CMP.B	40(A0),D0
  DEF_ROMLOC(19EBC) : if (CCR_EQ) goto rom_19EF6; // BEQ.B	$19EF6
  DEF_ROMLOC(19EBE) : tst_reg_8(&D0);             // TST.B	D0
  DEF_ROMLOC(19EC0) : if (CCR_MI) goto rom_19EC8; // BMI.B	$19EC8
  DEF_ROMLOC(19EC2) : rom_19F2A();                // BSR.W	$19F2A
  goto rom_19F0C;                                 // BRA.B	$19F0C
  DEF_ROMLOC(19EC8)
      : move_toreg_32(read_32(A0 + 0x34), &A1);   // MOVEA.L	52(A0),A1
  DEF_ROMLOC(19ECC) : tst_mem_8(A1 + 0x21);       // TST.B	33(A1)
  DEF_ROMLOC(19ED0) : if (CCR_EQ) goto rom_19EC2; // BEQ.B	$19EC2
  DEF_ROMLOC(19ED2)
      : move_tomem_16(read_16(A1 + 0x8), A0 + 0x8); // MOVE.W	8(A1),8(A0)
  DEF_ROMLOC(19ED8)
      : move_tomem_16(read_16(A1 + 0xC), A0 + 0xC); // MOVE.W	12(A1),12(A0)
  DEF_ROMLOC(19EDE) : add_tomem_16(0x2C, A0 + 0xC); // ADDI.W	#$002C,12(A0)
  DEF_ROMLOC(19EE4) : cmp_toreg_16(A0, &A1);        // CMPA.W	A0,A1
  DEF_ROMLOC(19EE6) : if (CCR_CS) goto rom_19F0C;   // BCS.B	$19F0C
  DEF_ROMLOC(19EE8)
      : move_toreg_16(read_16(A1 + 0x12), &D0);   // MOVE.W	18(A1),D0
  DEF_ROMLOC(19EEC) : ext_reg_32(&D0);            // EXT.L	D0
  DEF_ROMLOC(19EEE) : asr_toreg_32(0x8, &D0);     // ASR.L	#$08,D0
  DEF_ROMLOC(19EF0) : add_tomem_16(D0, A0 + 0xC); // ADD.W	D0,12(A0)
  goto rom_19F0C;                                 // BRA.B	$19F0C
  DEF_ROMLOC(19EF6) : move_toreg_16(0x1B, &D1);   // MOVE.W	#$001B,D1
  DEF_ROMLOC(19EFA) : move_toreg_16(0x10, &D2);   // MOVE.W	#$0010,D2
  DEF_ROMLOC(19EFE) : move_toreg_16(0x11, &D3);   // MOVE.W	#$0011,D3
  DEF_ROMLOC(19F02)
      : move_toreg_16(read_16(A0 + 0x8), &D4); // MOVE.W	8(A0),D4
  DEF_ROMLOC(19F06) : rom_10062();             // JSR	$00010062
  DEF_ROMLOC(19F0C) : queue_sprite();
  return; // JMP	$0000DC92
}
ROMFUNC(rom_19F2A) {
  DEF_ROMLOC(19F2A) : move_toreg_32(0x19F8E, &A4);  // LEA.L	98(PC),A4
  DEF_ROMLOC(19F2E) : move_toreg_32(0x19F9E, &A5);  // LEA.L	110(PC),A5
  DEF_ROMLOC(19F32) : move_toreg_32(0x1, &D4);      // MOVEQ.L	$01,D4
  DEF_ROMLOC(19F34) : move_toreg_32(0x3, &D1);      // MOVEQ.L	$03,D1
  DEF_ROMLOC(19F36) : move_toreg_32(0x38, &D2);     // MOVEQ.L	$38,D2
  DEF_ROMLOC(19F38) : add_tomem_8(0x2, A0 + 0x24);  // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(19F3C) : move_tomem_8(0x8, A0 + 0x19); // MOVE.B	#$08,25(A0)
  DEF_ROMLOC(19F42) : move_tomem_8(0x8, A0 + 0x16); // MOVE.B	#$08,22(A0)
  DEF_ROMLOC(19F48) : move_toreg_32(A0, &A1);       // LEA.L	(A0),A1
  goto rom_19F54;                                   // BRA.B	$19F54
  DEF_ROMLOC(19F4C) : rom_E130();                   // JSR	$0000E130
  DEF_ROMLOC(19F52) : if (!CCR_EQ) goto rom_19F84;  // BNE.B	$19F84
  DEF_ROMLOC(19F54) : move_toreg_32(A0, &A2);       // LEA.L	(A0),A2
  DEF_ROMLOC(19F56) : move_toreg_32(A1, &A3);       // LEA.L	(A1),A3
  DEF_ROMLOC(19F58) : move_toreg_32(0x3, &D3);      // MOVEQ.L	$03,D3
  DEF_ROMLOC(19F5A)
      : move_tomem_32(read_32((A2 += 4, A2 - 4)),
                      (A3 += 4, A3 - 4)); // MOVE.L	(A2)+,(A3)+
  DEF_ROMLOC(19F5C)
      : move_tomem_32(read_32((A2 += 4, A2 - 4)),
                      (A3 += 4, A3 - 4)); // MOVE.L	(A2)+,(A3)+
  DEF_ROMLOC(19F5E)
      : move_tomem_32(read_32((A2 += 4, A2 - 4)),
                      (A3 += 4, A3 - 4)); // MOVE.L	(A2)+,(A3)+
  DEF_ROMLOC(19F60)
      : move_tomem_32(read_32((A2 += 4, A2 - 4)),
                      (A3 += 4, A3 - 4)); // MOVE.L	(A2)+,(A3)+
  DEF_ROMLOC(19F62) : dec_reg_16(&D3);
  if ((D3 & 0xffff) != 0xffff)
    goto rom_19F5A; // DBF.W	D3,$19F5A
  DEF_ROMLOC(19F66)
      : move_tomem_16(read_16((A4 += 2, A4 - 2)),
                      A1 + 0x10); // MOVE.W	(A4)+,16(A1)
  DEF_ROMLOC(19F6A)
      : move_tomem_16(read_16((A4 += 2, A4 - 2)),
                      A1 + 0x12); // MOVE.W	(A4)+,18(A1)
  DEF_ROMLOC(19F6E)
      : move_toreg_16(read_16((A5 += 2, A5 - 2)), &D3); // MOVE.W	(A5)+,D3
  DEF_ROMLOC(19F70) : add_tomem_16(D3, A1 + 0x8);       // ADD.W	D3,8(A1)
  DEF_ROMLOC(19F74)
      : move_toreg_16(read_16((A5 += 2, A5 - 2)), &D3); // MOVE.W	(A5)+,D3
  DEF_ROMLOC(19F76) : add_tomem_16(D3, A1 + 0xC);       // ADD.W	D3,12(A1)
  DEF_ROMLOC(19F7A) : move_tomem_8(D4, A1 + 0x1A);      // MOVE.B	D4,26(A1)
  DEF_ROMLOC(19F7E) : add_toreg_16(0x1, &D4);           // ADDQ.W	#$01,D4
  DEF_ROMLOC(19F80) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_19F4C; // DBF.W	D1,$19F4C
  DEF_ROMLOC(19F84)
      : move_toreg_16(SFX_WALLSMASH, &D0); // MOVE.W	#$00CB,D0
  DEF_ROMLOC(19F88) : play_sound_special();
  return; // JMP	$00001394
}
ROMFUNC(rom_19F12) {
  DEF_ROMLOC(19F12) : tst_mem_8(A0 + 0x1);        // TST.B	1(A0)
  DEF_ROMLOC(19F16) : if (CCR_PL) goto rom_19F24; // BPL.B	$19F24
  DEF_ROMLOC(19F18) : rom_DC40();                 // JSR	$0000DC40
  DEF_ROMLOC(19F1E) : queue_sprite();
  return; // JMP	$0000DC92
  DEF_ROMLOC(19F24) : rom_DCCE();
  return; // JMP	$0000DCCE
  rom_19F2A();
}