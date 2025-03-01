// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_1B2D8) {
  u8 switchindex = 0;
  DEF_ROMLOC(1B2D8) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(1B2DA) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(1B2DE)
      : move_toreg_16(read_16(0x1B30E + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	46(PC,D0),D1
  // DEF_ROMLOC(1B2E2): rom_1B30E + (s16)(D1 & 0xffff)(); // JSR
  // 42(PC,D1)
  DEF_ROMLOC(1B2E2) : switch (switchindex) {
  case 0:
    rom_1B32E();
    break;
  case 1:
    rom_1B378();
    break;
  case 2:
    rom_1B3B4();
    break;
  case 3:
    rom_1B418();
    break;
  case 4:
    rom_1B418();
    break;
  case 5:
    rom_1B418();
    break;
  case 6:
    rom_1B4B0();
    break;
  case 7:
    rom_1B500();
    break;
  }
  DEF_ROMLOC(1B2E6) : move_toreg_16(read_16(A0 + 0x8), &D0); // MOVE.W	8(A0),D0
  DEF_ROMLOC(1B2EA) : and_toreg_16(0xFFFFFF80, &D0);         // ANDI.W	#$FF80,D0
  DEF_ROMLOC(1B2EE)
      : move_toreg_16(read_16(v_screenposx), &D1);   // MOVE.W	$F700,D1
  DEF_ROMLOC(1B2F2) : sub_toreg_16(0x80, &D1);       // SUBI.W	#$0080,D1
  DEF_ROMLOC(1B2F6) : and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
  DEF_ROMLOC(1B2FA) : sub_toreg_16(D1, &D0);         // SUB.W	D1,D0
  DEF_ROMLOC(1B2FC)
      : cmp_toreg_16(128 + GAME_WIDTH + 192, &D0); // CMPI.W	#$0280,D0
  DEF_ROMLOC(1B300) : if (CCR_HI) goto rom_1B308;  // BHI.B	$1B308
  DEF_ROMLOC(1B302) : {
    rom_DC92();
    return;
  } // JMP	$0000DC92
  DEF_ROMLOC(1B308) : {
    rom_DCCE();
    return;
  } // JMP	$0000DCCE
}
ROMFUNC(rom_1B32E) {
  DEF_ROMLOC(1B32E)
      : move_tomem_32(0x1B52A, A0 + 0x4);             // MOVE.L	#$0001B52A,4(A0)
  DEF_ROMLOC(1B336) : move_tomem_16(0x49D, A0 + 0x2); // MOVE.W	#$049D,2(A0)
  DEF_ROMLOC(1B33C) : move_tomem_8(0x4, A0 + 0x1);    // MOVE.B	#$04,1(A0)
  DEF_ROMLOC(1B342)
      : move_tomem_16(read_16(A0 + 0xC), A0 + 0x30); // MOVE.W	12(A0),48(A0)
  DEF_ROMLOC(1B348) : move_toreg_32(0x0, &D0);       // MOVEQ.L	$00,D0
  DEF_ROMLOC(1B34A)
      : move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B
                                              // 40(A0),D0
  DEF_ROMLOC(1B34E) : lsl_toreg_16(0x2, &D0); // LSL.W	#$02,D0
  DEF_ROMLOC(1B350)
      : move_toreg_32(0x1B31E + (s16)(D0 & 0xffff),
                      &A1); // LEA.L	-52(PC,D0),A1
  DEF_ROMLOC(1B354)
      : move_tomem_8(read_8(A1++), A0 + 0x24); // MOVE.B	(A1)+,36(A0)
  DEF_ROMLOC(1B358)
      : move_tomem_8(read_8(A1++), A0 + 0x19); // MOVE.B	(A1)+,25(A0)
  DEF_ROMLOC(1B35C)
      : move_tomem_8(read_8(A1++), A0 + 0x18); // MOVE.B	(A1)+,24(A0)
  DEF_ROMLOC(1B360)
      : move_tomem_8(read_8(A1++), A0 + 0x1A);      // MOVE.B	(A1)+,26(A0)
  DEF_ROMLOC(1B364) : cmp_toreg_16(0x8, &D0);       // CMPI.W	#$0008,D0
  DEF_ROMLOC(1B368) : if (!CCR_EQ) goto rom_1B376;  // BNE.B	$1B376
  DEF_ROMLOC(1B36A) : move_tomem_8(0x6, A0 + 0x20); // MOVE.B	#$06,32(A0)
  DEF_ROMLOC(1B370) : move_tomem_8(0x8, A0 + 0x21); // MOVE.B	#$08,33(A0)
  DEF_ROMLOC(1B376) : return;                       // RTS
}
ROMFUNC(rom_1B378) {
  DEF_ROMLOC(1B378) : cmp_tomem_8(0x2, 0xFFFFF7A7); // CMPI.B	#$02,$F7A7
  DEF_ROMLOC(1B37E) : if (CCR_EQ) goto rom_1B396;   // BEQ.B	$1B396
  DEF_ROMLOC(1B380) : move_toreg_16(0x2B, &D1);     // MOVE.W	#$002B,D1
  DEF_ROMLOC(1B384) : move_toreg_16(0x18, &D2);     // MOVE.W	#$0018,D2
  DEF_ROMLOC(1B388) : move_toreg_16(0x18, &D3);     // MOVE.W	#$0018,D3
  DEF_ROMLOC(1B38C)
      : move_toreg_16(read_16(A0 + 0x8), &D4); // MOVE.W	8(A0),D4
  DEF_ROMLOC(1B390) : {
    rom_10062();
    return;
  } // JMP	$00010062
  DEF_ROMLOC(1B396) : tst_mem_8(A0 + 0x25);          // TST.B	37(A0)
  DEF_ROMLOC(1B39A) : if (CCR_EQ) goto rom_1B3AC;    // BEQ.B	$1B3AC
  DEF_ROMLOC(1B39C) : clr_mem_8(A0 + 0x25);          // CLR.B	37(A0)
  DEF_ROMLOC(1B3A0) : bclr_tomem_8(0x3, 0xFFFFD022); // BCLR.B	#$03,$D022
  DEF_ROMLOC(1B3A6) : bset_tomem_8(0x1, 0xFFFFD022); // BSET.B	#$01,$D022
  DEF_ROMLOC(1B3AC) : move_tomem_8(0x2, A0 + 0x1A);  // MOVE.B	#$02,26(A0)
  DEF_ROMLOC(1B3B2) : return;                        // RTS
}
ROMFUNC(rom_1B3B4) {
  DEF_ROMLOC(1B3B4) : move_toreg_16(0x17, &D1); // MOVE.W	#$0017,D1
  DEF_ROMLOC(1B3B8) : move_toreg_16(0x8, &D2);  // MOVE.W	#$0008,D2
  DEF_ROMLOC(1B3BC) : move_toreg_16(0x8, &D3);  // MOVE.W	#$0008,D3
  DEF_ROMLOC(1B3C0)
      : move_toreg_16(read_16(A0 + 0x8), &D4);     // MOVE.W	8(A0),D4
  DEF_ROMLOC(1B3C4) : rom_10062();                 // JSR	$00010062
  DEF_ROMLOC(1B3CA) : move_toreg_32(0x1B522, &A1); // LEA.L	$0001B522,A1
  DEF_ROMLOC(1B3D0) : animate_sprite();            // JSR	$0000ADA2
  DEF_ROMLOC(1B3D6)
      : move_tomem_16(read_16(A0 + 0x30), A0 + 0xC);  // MOVE.W	48(A0),12(A0)
  DEF_ROMLOC(1B3DC) : tst_mem_8(A0 + 0x25);           // TST.B	37(A0)
  DEF_ROMLOC(1B3E0) : if (CCR_EQ) goto rom_1B416;     // BEQ.B	$1B416
  DEF_ROMLOC(1B3E2) : add_tomem_16(0x8, A0 + 0xC);    // ADDQ.W	#$08,12(A0)
  DEF_ROMLOC(1B3E6) : move_tomem_8(0xA, A0 + 0x24);   // MOVE.B	#$0A,36(A0)
  DEF_ROMLOC(1B3EC) : move_tomem_16(0x3C, A0 + 0x1E); // MOVE.W	#$003C,30(A0)
  DEF_ROMLOC(1B3F2) : clr_mem_8(f_timecount);         // CLR.B	$FE1E
  DEF_ROMLOC(1B3F6) : clr_mem_8(f_lockscreen);        // CLR.B	$F7AA
  DEF_ROMLOC(1B3FA) : move_tomem_8(0x1, 0xFFFFF7CC);  // MOVE.B	#$01,$F7CC
  DEF_ROMLOC(1B400)
      : move_tomem_16(0x800, 0xFFFFF602);            // MOVE.W
                                                     // #$0800,$F602
  DEF_ROMLOC(1B406) : clr_mem_8(A0 + 0x25);          // CLR.B	37(A0)
  DEF_ROMLOC(1B40A) : bclr_tomem_8(0x3, 0xFFFFD022); // BCLR.B	#$03,$D022
  DEF_ROMLOC(1B410) : bset_tomem_8(0x1, 0xFFFFD022); // BSET.B	#$01,$D022
  DEF_ROMLOC(1B416) : return;                        // RTS
}
ROMFUNC(rom_1B418) {
  DEF_ROMLOC(1B418) : move_toreg_32(0x7, &D0);              // MOVEQ.L	$07,D0
  DEF_ROMLOC(1B41A) : and_toreg_8(read_8(0xFFFFFE0F), &D0); // AND.B	$FE0F,D0
  DEF_ROMLOC(1B41E) : if (!CCR_EQ) goto rom_1B456;          // BNE.B	$1B456
  DEF_ROMLOC(1B420) : rom_E11A();                           // JSR	$0000E11A
  DEF_ROMLOC(1B426) : if (!CCR_EQ) goto rom_1B456;          // BNE.B	$1B456
  DEF_ROMLOC(1B428)
      : move_tomem_8(OBJ_EXPLOSIONBOMB,
                     A1 + offsetof(object, id)); // MOVE.B	#$3F,0(A1)
  DEF_ROMLOC(1B42E)
      : move_tomem_16(read_16(A0 + 0x8), A1 + 0x8); // MOVE.W	8(A0),8(A1)
  DEF_ROMLOC(1B434)
      : move_tomem_16(read_16(A0 + 0xC), A1 + 0xC);   // MOVE.W	12(A0),12(A1)
  DEF_ROMLOC(1B43A) : rom_29AC();                     // JSR	$000029AC
  DEF_ROMLOC(1B440) : move_toreg_32(0x0, &D1);        // MOVEQ.L	$00,D1
  DEF_ROMLOC(1B442) : move_toreg_8(D0, &D1);          // MOVE.B	D0,D1
  DEF_ROMLOC(1B444) : lsr_toreg_8(0x2, &D1);          // LSR.B	#$02,D1
  DEF_ROMLOC(1B446) : sub_toreg_16(0x20, &D1);        // SUBI.W	#$0020,D1
  DEF_ROMLOC(1B44A) : add_tomem_16(D1, A1 + 0x8);     // ADD.W	D1,8(A1)
  DEF_ROMLOC(1B44E) : lsr_toreg_16(0x8, &D0);         // LSR.W	#$08,D0
  DEF_ROMLOC(1B450) : lsr_toreg_8(0x3, &D0);          // LSR.B	#$03,D0
  DEF_ROMLOC(1B452) : add_tomem_16(D0, A1 + 0xC);     // ADD.W	D0,12(A1)
  DEF_ROMLOC(1B456) : sub_tomem_16(0x1, A0 + 0x1E);   // SUBQ.W	#$01,30(A0)
  DEF_ROMLOC(1B45A) : if (CCR_EQ) goto rom_1B45E;     // BEQ.B	$1B45E
  DEF_ROMLOC(1B45C) : return;                         // RTS
  DEF_ROMLOC(1B45E) : move_tomem_8(0x2, 0xFFFFF7A7);  // MOVE.B	#$02,$F7A7
  DEF_ROMLOC(1B464) : move_tomem_8(0xC, A0 + 0x24);   // MOVE.B	#$0C,36(A0)
  DEF_ROMLOC(1B46A) : move_tomem_8(0x6, A0 + 0x1A);   // MOVE.B	#$06,26(A0)
  DEF_ROMLOC(1B470) : move_tomem_16(0x96, A0 + 0x1E); // MOVE.W	#$0096,30(A0)
  DEF_ROMLOC(1B476) : add_tomem_16(0x20, A0 + 0xC);   // ADDI.W	#$0020,12(A0)
  DEF_ROMLOC(1B47C) : move_toreg_32(0x7, &D6);        // MOVEQ.L	$07,D6
  DEF_ROMLOC(1B47E) : move_toreg_16(0x9A, &D5);       // MOVE.W	#$009A,D5
  DEF_ROMLOC(1B482) : move_toreg_32(0xFFFFFFE4, &D4); // MOVEQ.L	$E4,D4
  DEF_ROMLOC(1B484) : rom_E11A();                     // JSR	$0000E11A
  DEF_ROMLOC(1B48A) : if (!CCR_EQ) goto rom_1B4AE;    // BNE.B	$1B4AE
  DEF_ROMLOC(1B48C)
      : move_tomem_8(OBJ_ANIMALS,
                     A1 + offsetof(object, id)); // MOVE.B	#$28,0(A1)
  DEF_ROMLOC(1B492)
      : move_tomem_16(read_16(A0 + 0x8), A1 + 0x8); // MOVE.W	8(A0),8(A1)
  DEF_ROMLOC(1B498)
      : move_tomem_16(read_16(A0 + 0xC), A1 + 0xC); // MOVE.W	12(A0),12(A1)
  DEF_ROMLOC(1B49E) : add_tomem_16(D4, A1 + 0x8);   // ADD.W	D4,8(A1)
  DEF_ROMLOC(1B4A2) : add_toreg_16(0x7, &D4);       // ADDQ.W	#$07,D4
  DEF_ROMLOC(1B4A4) : move_tomem_16(D5, A1 + 0x36); // MOVE.W	D5,54(A1)
  DEF_ROMLOC(1B4A8) : sub_toreg_16(0x8, &D5);       // SUBQ.W	#$08,D5
  DEF_ROMLOC(1B4AA) : dec_reg_16(&D6);
  if ((D6 & 0xffff) != 0xffff)
    goto rom_1B484;           // DBF.W	D6,$1B484
  DEF_ROMLOC(1B4AE) : return; // RTS
}
ROMFUNC(rom_1B4B0) {
  DEF_ROMLOC(1B4B0) : move_toreg_32(0x7, &D0);              // MOVEQ.L	$07,D0
  DEF_ROMLOC(1B4B2) : and_toreg_8(read_8(0xFFFFFE0F), &D0); // AND.B	$FE0F,D0
  DEF_ROMLOC(1B4B6) : if (!CCR_EQ) goto rom_1B4EE;          // BNE.B	$1B4EE
  DEF_ROMLOC(1B4B8) : rom_E11A();                           // JSR	$0000E11A
  DEF_ROMLOC(1B4BE) : if (!CCR_EQ) goto rom_1B4EE;          // BNE.B	$1B4EE
  DEF_ROMLOC(1B4C0)
      : move_tomem_8(OBJ_ANIMALS,
                     A1 + offsetof(object, id)); // MOVE.B	#$28,0(A1)
  DEF_ROMLOC(1B4C6)
      : move_tomem_16(read_16(A0 + 0x8), A1 + 0x8); // MOVE.W	8(A0),8(A1)
  DEF_ROMLOC(1B4CC)
      : move_tomem_16(read_16(A0 + 0xC), A1 + 0xC);   // MOVE.W	12(A0),12(A1)
  DEF_ROMLOC(1B4D2) : rom_29AC();                     // JSR	$000029AC
  DEF_ROMLOC(1B4D8) : and_toreg_16(0x1F, &D0);        // ANDI.W	#$001F,D0
  DEF_ROMLOC(1B4DC) : sub_toreg_16(0x6, &D0);         // SUBQ.W	#$06,D0
  DEF_ROMLOC(1B4DE) : tst_reg_16(&D1);                // TST.W	D1
  DEF_ROMLOC(1B4E0) : if (CCR_PL) goto rom_1B4E4;     // BPL.B	$1B4E4
  DEF_ROMLOC(1B4E2) : neg_reg_16(&D0);                // NEG.W	D0
  DEF_ROMLOC(1B4E4) : add_tomem_16(D0, A1 + 0x8);     // ADD.W	D0,8(A1)
  DEF_ROMLOC(1B4E8) : move_tomem_16(0xC, A1 + 0x36);  // MOVE.W	#$000C,54(A1)
  DEF_ROMLOC(1B4EE) : sub_tomem_16(0x1, A0 + 0x1E);   // SUBQ.W	#$01,30(A0)
  DEF_ROMLOC(1B4F2) : if (!CCR_EQ) goto rom_1B4FE;    // BNE.B	$1B4FE
  DEF_ROMLOC(1B4F4) : add_tomem_8(0x2, A0 + 0x24);    // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(1B4F8) : move_tomem_16(0xB4, A0 + 0x1E); // MOVE.W	#$00B4,30(A0)
  DEF_ROMLOC(1B4FE) : return;                         // RTS
}
ROMFUNC(rom_1B500) {
  DEF_ROMLOC(1B500) : move_toreg_32(0x3E, &D0);       // MOVEQ.L	$3E,D0
  DEF_ROMLOC(1B502) : move_toreg_32(0x28, &D1);       // MOVEQ.L	$28,D1
  DEF_ROMLOC(1B504) : move_toreg_32(0x40, &D2);       // MOVEQ.L	$40,D2
  DEF_ROMLOC(1B506) : move_toreg_32(0xFFFFD040, &A1); // LEA.L	$D040,A1
  DEF_ROMLOC(1B50A) : cmp_toreg_8(read_8(A1), &D1);   // CMP.B	(A1),D1
  DEF_ROMLOC(1B50C) : if (CCR_EQ) goto rom_1B520;     // BEQ.B	$1B520
  DEF_ROMLOC(1B50E) : add_toreg_16(D2, &A1);          // ADDA.W	D2,A1
  DEF_ROMLOC(1B510) : dec_reg_16(&D0);
  if ((D0 & 0xffff) != 0xffff)
    goto rom_1B50A;               // DBF.W	D0,$1B50A
  DEF_ROMLOC(1B514) : rom_F316(); // JSR	$0000F316
  DEF_ROMLOC(1B51A) : {
    rom_DCCE();
    return;
  } // JMP	$0000DCCE
  DEF_ROMLOC(1B520) : return;                       // RTS
  DEF_ROMLOC(1B522) : or_toreg_8(0x4, &D4);         // ORI.B	#$04,D4
  DEF_ROMLOC(1B526) : and_toreg_8(0xFFFFFFFF, &D1); // ANDI.B	#$FF,D1
  rom_1B59A(); // Detected flow into next function
}