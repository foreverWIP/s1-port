// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_1436C) {
  u8 switchindex = 0;
  DEF_ROMLOC(1436C) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(1436E) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(14372)
      : move_toreg_16(read_16(0x1437A + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(14376): goto rom_1437A + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(14376) : switch (switchindex) {
  case 0:
    rom_1438C();
    break;
  case 1:
    rom_143E4();
    break;
  case 2:
    rom_143F0();
    break;
  case 3:
    rom_14452();
    break;
  case 4:
    rom_14466();
    break;
  case 5:
    rom_145F0();
    break;
  case 6:
    rom_1446C();
    break;
  case 7:
    rom_14452();
    break;
  case 8:
    rom_14466();
    break;
  }
}
ROMFUNC(rom_1438C) {
  DEF_ROMLOC(1438C) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(14390)
      : move_tomem_32(0x130A0, A0 + 0x4); // MOVE.L	#$000130A0,4(A0)
  DEF_ROMLOC(14398)
      : move_tomem_16(0xFFFF8348, A0 + 0x2); // MOVE.W	#$8348,2(A0)
  DEF_ROMLOC(1439E)
      : move_tomem_8(0xFFFFFF84, A0 + 0x1);          // MOVE.B
                                                     // #$84,1(A0)
  DEF_ROMLOC(143A4) : move_tomem_8(0x10, A0 + 0x19); // MOVE.B	#$10,25(A0)
  DEF_ROMLOC(143AA) : move_tomem_8(0x1, A0 + 0x18);  // MOVE.B	#$01,24(A0)
  DEF_ROMLOC(143B0)
      : move_toreg_8(read_8(A0 + 0x28), &D0);      // MOVE.B	40(A0),D0
  DEF_ROMLOC(143B4) : if (CCR_PL) goto rom_143D4;  // BPL.B	$143D4
  DEF_ROMLOC(143B6) : add_tomem_8(0x8, A0 + 0x24); // ADDQ.B	#$08,36(A0)
  DEF_ROMLOC(143BA)
      : move_tomem_32(0x148B8, A0 + 0x4);             // MOVE.L	#$000148B8,4(A0)
  DEF_ROMLOC(143C2) : move_tomem_16(0x440, A0 + 0x2); // MOVE.W	#$0440,2(A0)
  DEF_ROMLOC(143C8) : and_toreg_16(0x7F, &D0);        // ANDI.W	#$007F,D0
  DEF_ROMLOC(143CC) : move_tomem_8(D0, A0 + 0x33);    // MOVE.B	D0,51(A0)
  DEF_ROMLOC(143D0) : {
    rom_145F0();
    return;
  } // BRA.W	$145F0
  DEF_ROMLOC(143D4) : move_tomem_8(D0, A0 + 0x1C); // MOVE.B	D0,28(A0)
  DEF_ROMLOC(143D8)
      : move_tomem_16(read_16(A0 + 0x8), A0 + 0x30); // MOVE.W	8(A0),48(A0)
  DEF_ROMLOC(143DE)
      : move_tomem_16(0xFFFFFF78, A0 + 0x12); // MOVE.W	#$FF78,18(A0)
  rom_143E4(); // Detected flow into next function
}
ROMFUNC(rom_143E4) {
  DEF_ROMLOC(143E4) : move_toreg_32(0x14820, &A1); // LEA.L	$00014820,A1
  DEF_ROMLOC(143EA) : animate_sprite();            // JSR	$0000ADA2
  rom_143F0(); // Detected flow into next function
}
ROMFUNC(rom_143F0) {
  DEF_ROMLOC(143F0)
      : move_toreg_16(read_16(0xFFFFF646), &D0); // MOVE.W	$F646,D0
  DEF_ROMLOC(143F4)
      : cmp_toreg_16(read_16(A0 + 0xC), &D0);       // CMP.W	12(A0),D0
  DEF_ROMLOC(143F8) : if (CCR_CS) goto rom_1440E;   // BCS.B	$1440E
  DEF_ROMLOC(143FA) : move_tomem_8(0x6, A0 + 0x24); // MOVE.B	#$06,36(A0)
  DEF_ROMLOC(14400) : add_tomem_8(0x7, A0 + 0x1C);  // ADDQ.B	#$07,28(A0)
  DEF_ROMLOC(14404) : cmp_tomem_8(0xD, A0 + 0x1C);  // CMPI.B	#$0D,28(A0)
  DEF_ROMLOC(1440A) : if (CCR_EQ) {
    rom_14452();
    return;
  } // BEQ.B	$14452
  DEF_ROMLOC(1440C) : {
    rom_14452();
    return;
  } // BRA.B	$14452
  DEF_ROMLOC(1440E) : tst_mem_8(0xFFFFF7C7);        // TST.B	$F7C7
  DEF_ROMLOC(14412) : if (CCR_EQ) goto rom_14418;   // BEQ.B	$14418
  DEF_ROMLOC(14414) : add_tomem_16(0x4, A0 + 0x30); // ADDQ.W	#$04,48(A0)
  DEF_ROMLOC(14418)
      : move_toreg_8(read_8(A0 + 0x26), &D0);      // MOVE.B	38(A0),D0
  DEF_ROMLOC(1441C) : add_tomem_8(0x1, A0 + 0x26); // ADDQ.B	#$01,38(A0)
  DEF_ROMLOC(14420) : and_toreg_16(0x7F, &D0);     // ANDI.W	#$007F,D0
  DEF_ROMLOC(14424) : move_toreg_32(0x144F0, &A1); // LEA.L	$000144F0,A1
  DEF_ROMLOC(1442A)
      : move_toreg_8(read_8((s32)A1 + (s8)0x0 + (s16)D0),
                     &D0);             // MOVE.B	0(A1,D0),D0
  DEF_ROMLOC(1442E) : ext_reg_16(&D0); // EXT.W	D0
  DEF_ROMLOC(14430)
      : add_toreg_16(read_16(A0 + 0x30), &D0);     // ADD.W	48(A0),D0
  DEF_ROMLOC(14434) : move_tomem_16(D0, A0 + 0x8); // MOVE.W	D0,8(A0)
  DEF_ROMLOC(14438) : rom_144A4();                 // BSR.B	$144A4
  DEF_ROMLOC(1443A) : rom_DC6C();                  // JSR	$0000DC6C
  DEF_ROMLOC(14440) : tst_mem_8(A0 + 0x1);         // TST.B	1(A0)
  DEF_ROMLOC(14444) : if (CCR_PL) goto rom_1444C;  // BPL.B	$1444C
  DEF_ROMLOC(14446) : {
    queue_sprite();
    return;
  } // JMP	$0000DC92
  DEF_ROMLOC(1444C) : {
    rom_DCCE();
    return;
  } // JMP	$0000DCCE
}
ROMFUNC(rom_14452) {
  DEF_ROMLOC(14452) : rom_144A4();                 // BSR.B	$144A4
  DEF_ROMLOC(14454) : move_toreg_32(0x14820, &A1); // LEA.L	$00014820,A1
  DEF_ROMLOC(1445A) : animate_sprite();            // JSR	$0000ADA2
  DEF_ROMLOC(14460) : {
    queue_sprite();
    return;
  } // JMP	$0000DC92
}
ROMFUNC(rom_14466) {
  DEF_ROMLOC(14466) : {
    rom_DCCE();
    return;
  } // JMP	$0000DCCE
}
ROMFUNC(rom_1446C) {
  DEF_ROMLOC(1446C)
      : cmp_tomem_16(AIR_COUNTDOWN_THRESHOLD, v_air); // CMPI.W	#$000C,$FE14
  DEF_ROMLOC(14472) : if (CCR_HI) goto rom_1449E;     // BHI.B	$1449E
  DEF_ROMLOC(14474) : sub_tomem_16(0x1, A0 + 0x38);   // SUBQ.W	#$01,56(A0)
  DEF_ROMLOC(14478) : if (!CCR_EQ) goto rom_14486;    // BNE.B	$14486
  DEF_ROMLOC(1447A) : move_tomem_8(0xE, A0 + 0x24);   // MOVE.B	#$0E,36(A0)
  DEF_ROMLOC(14480) : add_tomem_8(0x7, A0 + 0x1C);    // ADDQ.B	#$07,28(A0)
  DEF_ROMLOC(14484) : {
    rom_14452();
    return;
  } // BRA.B	$14452
  DEF_ROMLOC(14486) : move_toreg_32(0x14820, &A1); // LEA.L	$00014820,A1
  DEF_ROMLOC(1448C) : animate_sprite();            // JSR	$0000ADA2
  DEF_ROMLOC(14492) : tst_mem_8(A0 + 0x1);         // TST.B	1(A0)
  DEF_ROMLOC(14496) : if (CCR_PL) goto rom_1449E;  // BPL.B	$1449E
  DEF_ROMLOC(14498) : {
    queue_sprite();
    return;
  } // JMP	$0000DC92
  DEF_ROMLOC(1449E) : {
    rom_DCCE();
    return;
  } // JMP	$0000DCCE
}
ROMFUNC(rom_144A4) {
  DEF_ROMLOC(144A4) : tst_mem_16(A0 + 0x38);         // TST.W	56(A0)
  DEF_ROMLOC(144A8) : if (CCR_EQ) goto rom_144EE;    // BEQ.B	$144EE
  DEF_ROMLOC(144AA) : sub_tomem_16(0x1, A0 + 0x38);  // SUBQ.W	#$01,56(A0)
  DEF_ROMLOC(144AE) : if (!CCR_EQ) goto rom_144EE;   // BNE.B	$144EE
  DEF_ROMLOC(144B0) : cmp_tomem_8(0x7, A0 + 0x1C);   // CMPI.B	#$07,28(A0)
  DEF_ROMLOC(144B6) : if (CCR_CC) goto rom_144EE;    // BCC.B	$144EE
  DEF_ROMLOC(144B8) : move_tomem_16(0xF, A0 + 0x38); // MOVE.W	#$000F,56(A0)
  DEF_ROMLOC(144BE) : clr_mem_16(A0 + 0x12);         // CLR.W	18(A0)
  DEF_ROMLOC(144C2)
      : move_tomem_8(0xFFFFFF80, A0 + 0x1); // MOVE.B
                                            // #$80,1(A0)
  DEF_ROMLOC(144C8)
      : move_toreg_16(read_16(A0 + 0x8), &D0); // MOVE.W	8(A0),D0
  DEF_ROMLOC(144CC)
      : sub_toreg_16(read_16(v_screenposx), &D0);  // SUB.W	$F700,D0
  DEF_ROMLOC(144D0) : add_toreg_16(0x80, &D0);     // ADDI.W	#$0080,D0
  DEF_ROMLOC(144D4) : move_tomem_16(D0, A0 + 0x8); // MOVE.W	D0,8(A0)
  DEF_ROMLOC(144D8)
      : move_toreg_16(read_16(A0 + 0xC), &D0); // MOVE.W	12(A0),D0
  DEF_ROMLOC(144DC)
      : sub_toreg_16(read_16(0xFFFFF704), &D0);     // SUB.W	$F704,D0
  DEF_ROMLOC(144E0) : add_toreg_16(0x80, &D0);      // ADDI.W	#$0080,D0
  DEF_ROMLOC(144E4) : move_tomem_16(D0, A0 + 0xA);  // MOVE.W	D0,10(A0)
  DEF_ROMLOC(144E8) : move_tomem_8(0xC, A0 + 0x24); // MOVE.B	#$0C,36(A0)
  DEF_ROMLOC(144EE) : return;                       // RTS
}
ROMFUNC(rom_145F0) {
  DEF_ROMLOC(145F0) : tst_mem_16(A0 + 0x2C);          // TST.W	44(A0)
  DEF_ROMLOC(145F4) : if (!CCR_EQ) goto rom_146DA;    // BNE.W	$146DA
  DEF_ROMLOC(145F8) : cmp_tomem_8(0x6, 0xFFFFD024);   // CMPI.B	#$06,$D024
  DEF_ROMLOC(145FE) : if (CCR_CC) goto rom_147E0;     // BCC.W	$147E0
  DEF_ROMLOC(14602) : btst_tomem_8(0x6, 0xFFFFD022);  // BTST.B	#$06,$D022
  DEF_ROMLOC(14608) : if (CCR_EQ) goto rom_147E0;     // BEQ.W	$147E0
  DEF_ROMLOC(1460C) : sub_tomem_16(0x1, A0 + 0x38);   // SUBQ.W	#$01,56(A0)
  DEF_ROMLOC(14610) : if (CCR_PL) goto rom_14700;     // BPL.W	$14700
  DEF_ROMLOC(14614) : move_tomem_16(0x3B, A0 + 0x38); // MOVE.W	#$003B,56(A0)
  DEF_ROMLOC(1461A) : move_tomem_16(0x1, A0 + 0x36);  // MOVE.W	#$0001,54(A0)
  DEF_ROMLOC(14620) : rom_29AC();                     // JSR	$000029AC
  DEF_ROMLOC(14626) : and_toreg_16(0x1, &D0);         // ANDI.W	#$0001,D0
  DEF_ROMLOC(1462A) : move_tomem_8(D0, A0 + 0x34);    // MOVE.B	D0,52(A0)
  DEF_ROMLOC(1462E) : move_toreg_16(read_16(v_air), &D0); // MOVE.W	$FE14,D0
  DEF_ROMLOC(14632) : cmp_toreg_16(0x19, &D0);            // CMPI.W	#$0019,D0
  DEF_ROMLOC(14636) : if (CCR_EQ) goto rom_1466A;         // BEQ.B	$1466A
  DEF_ROMLOC(14638) : cmp_toreg_16(0x14, &D0);            // CMPI.W	#$0014,D0
  DEF_ROMLOC(1463C) : if (CCR_EQ) goto rom_1466A;         // BEQ.B	$1466A
  DEF_ROMLOC(1463E) : cmp_toreg_16(0xF, &D0);             // CMPI.W	#$000F,D0
  DEF_ROMLOC(14642) : if (CCR_EQ) goto rom_1466A;         // BEQ.B	$1466A
  DEF_ROMLOC(14644) : cmp_toreg_16(0xC, &D0);             // CMPI.W	#$000C,D0
  DEF_ROMLOC(14648) : if (CCR_HI) goto rom_14674;         // BHI.B	$14674
  DEF_ROMLOC(1464A) : if (!CCR_EQ) goto rom_14656;        // BNE.B	$14656
  DEF_ROMLOC(1464C)
      : move_toreg_16(BGM_DROWNING, &D0);          // MOVE.W
                                                   // #$0092,D0
  DEF_ROMLOC(14650) : play_sound();                // JSR	$0000138E
  DEF_ROMLOC(14656) : sub_tomem_8(0x1, A0 + 0x32); // SUBQ.B	#$01,50(A0)
  DEF_ROMLOC(1465A) : if (CCR_PL) goto rom_14674;  // BPL.B	$14674
  DEF_ROMLOC(1465C)
      : move_tomem_8(read_8(A0 + 0x33), A0 + 0x32); // MOVE.B	51(A0),50(A0)
  DEF_ROMLOC(14662) : bset_tomem_8(0x7, A0 + 0x36); // BSET.B	#$07,54(A0)
  DEF_ROMLOC(14668) : goto rom_14674;               // BRA.B	$14674
  DEF_ROMLOC(1466A)
      : move_toreg_16(SFX_WARNING, &D0);          // MOVE.W
                                                  // #$00C2,D0
  DEF_ROMLOC(1466E) : play_sound_special();       // JSR	$00001394
  DEF_ROMLOC(14674) : sub_tomem_16(0x1, v_air);   // SUBQ.W	#$01,$FE14
  DEF_ROMLOC(14678) : if (CCR_CC) goto rom_146FE; // BCC.W	$146FE
  DEF_ROMLOC(1467C) : resume_music();             // BSR.W	$147E2
  DEF_ROMLOC(14680)
      : move_tomem_8(0xFFFFFF81, 0xFFFFF7C8);         // MOVE.B
                                                      // #$81,$F7C8
  DEF_ROMLOC(14686) : move_toreg_16(SFX_DROWN, &D0);  // MOVE.W	#$00B2,D0
  DEF_ROMLOC(1468A) : play_sound_special();           // JSR	$00001394
  DEF_ROMLOC(14690) : move_tomem_8(0xA, A0 + 0x34);   // MOVE.B	#$0A,52(A0)
  DEF_ROMLOC(14696) : move_tomem_16(0x1, A0 + 0x36);  // MOVE.W	#$0001,54(A0)
  DEF_ROMLOC(1469C) : move_tomem_16(0x78, A0 + 0x2C); // MOVE.W	#$0078,44(A0)
  DEF_ROMLOC(146A2) : move_tomem_32(A0, A7 -= 4);     // MOVE.L	A0,-(A7)
  DEF_ROMLOC(146A4) : move_toreg_32(0xFFFFD000, &A0); // LEA.L	$D000,A0
  DEF_ROMLOC(146A8) : rom_13E74();                    // BSR.W	$13E74
  DEF_ROMLOC(146AC) : move_tomem_8(0x17, A0 + 0x1C);  // MOVE.B	#$17,28(A0)
  DEF_ROMLOC(146B2) : bset_tomem_8(0x1, A0 + 0x22);   // BSET.B	#$01,34(A0)
  DEF_ROMLOC(146B8) : bset_tomem_8(0x7, A0 + 0x2);    // BSET.B	#$07,2(A0)
  DEF_ROMLOC(146BE) : move_tomem_16(0x0, A0 + 0x12);  // MOVE.W	#$0000,18(A0)
  DEF_ROMLOC(146C4) : move_tomem_16(0x0, A0 + 0x10);  // MOVE.W	#$0000,16(A0)
  DEF_ROMLOC(146CA) : move_tomem_16(0x0, A0 + 0x14);  // MOVE.W	#$0000,20(A0)
  DEF_ROMLOC(146D0) : move_tomem_8(0x1, 0xFFFFF744);  // MOVE.B	#$01,$F744
  DEF_ROMLOC(146D6)
      : move_toreg_32(read_32((A7 += 4, A7 - 4)), &A0); // MOVEA.L	(A7)+,A0
  DEF_ROMLOC(146D8) : return;                           // RTS
  DEF_ROMLOC(146DA) : sub_tomem_16(0x1, A0 + 0x2C);     // SUBQ.W	#$01,44(A0)
  DEF_ROMLOC(146DE) : if (!CCR_EQ) goto rom_146E8;      // BNE.B	$146E8
  DEF_ROMLOC(146E0) : move_tomem_8(0x6, 0xFFFFD024);    // MOVE.B	#$06,$D024
  DEF_ROMLOC(146E6) : return;                           // RTS
  DEF_ROMLOC(146E8) : move_tomem_32(A0, A7 -= 4);       // MOVE.L	A0,-(A7)
  DEF_ROMLOC(146EA) : move_toreg_32(0xFFFFD000, &A0);   // LEA.L	$D000,A0
  DEF_ROMLOC(146EE) : rom_DC6C();                       // JSR	$0000DC6C
  DEF_ROMLOC(146F4)
      : add_tomem_16(0x10, A0 + 0x12); // ADDI.W	#$0010,18(A0)
  DEF_ROMLOC(146FA)
      : move_toreg_32(read_32((A7 += 4, A7 - 4)), &A0); // MOVEA.L	(A7)+,A0
  DEF_ROMLOC(146FC) : goto rom_14700;                   // BRA.B	$14700
  DEF_ROMLOC(146FE) : goto rom_14710;                   // BRA.B	$14710
  DEF_ROMLOC(14700) : tst_mem_16(A0 + 0x36);            // TST.W	54(A0)
  DEF_ROMLOC(14704) : if (CCR_EQ) goto rom_147E0;       // BEQ.W	$147E0
  DEF_ROMLOC(14708) : sub_tomem_16(0x1, A0 + 0x3A);     // SUBQ.W	#$01,58(A0)
  DEF_ROMLOC(1470C) : if (CCR_PL) goto rom_147E0;       // BPL.W	$147E0
  DEF_ROMLOC(14710) : rom_29AC();                       // JSR	$000029AC
  DEF_ROMLOC(14716) : and_toreg_16(0xF, &D0);           // ANDI.W	#$000F,D0
  DEF_ROMLOC(1471A) : move_tomem_16(D0, A0 + 0x3A);     // MOVE.W	D0,58(A0)
  DEF_ROMLOC(1471E) : rom_E11A();                       // JSR	$0000E11A
  DEF_ROMLOC(14724) : if (!CCR_EQ) goto rom_147E0;      // BNE.W	$147E0
  DEF_ROMLOC(14728)
      : move_tomem_8(OBJ_DROWNCOUNT,
                     A1 + offsetof(object, id)); // MOVE.B	#$0A,0(A1)
  DEF_ROMLOC(1472E)
      : move_tomem_16(read_16(0xFFFFD008), A1 + 0x8); // MOVE.W	$D008,8(A1)
  DEF_ROMLOC(14734) : move_toreg_32(0x6, &D0);        // MOVEQ.L	$06,D0
  DEF_ROMLOC(14736) : btst_tomem_8(0x0, 0xFFFFD022);  // BTST.B	#$00,$D022
  DEF_ROMLOC(1473C) : if (CCR_EQ) goto rom_14746;     // BEQ.B	$14746
  DEF_ROMLOC(1473E) : neg_reg_16(&D0);                // NEG.W	D0
  DEF_ROMLOC(14740) : move_tomem_8(0x40, A1 + 0x26);  // MOVE.B	#$40,38(A1)
  DEF_ROMLOC(14746) : add_tomem_16(D0, A1 + 0x8);     // ADD.W	D0,8(A1)
  DEF_ROMLOC(1474A)
      : move_tomem_16(read_16(0xFFFFD00C), A1 + 0xC); // MOVE.W	$D00C,12(A1)
  DEF_ROMLOC(14750) : move_tomem_8(0x6, A1 + 0x28);   // MOVE.B	#$06,40(A1)
  DEF_ROMLOC(14756) : tst_mem_16(A0 + 0x2C);          // TST.W	44(A0)
  DEF_ROMLOC(1475A) : if (CCR_EQ) goto rom_14792;     // BEQ.W	$14792
  DEF_ROMLOC(1475E) : and_tomem_16(0x7, A0 + 0x3A);   // ANDI.W	#$0007,58(A0)
  DEF_ROMLOC(14764) : add_tomem_16(0x0, A0 + 0x3A);   // ADDI.W	#$0000,58(A0)
  DEF_ROMLOC(1476A)
      : move_toreg_16(read_16(0xFFFFD00C), &D0);   // MOVE.W	$D00C,D0
  DEF_ROMLOC(1476E) : sub_toreg_16(0xC, &D0);      // SUBI.W	#$000C,D0
  DEF_ROMLOC(14772) : move_tomem_16(D0, A1 + 0xC); // MOVE.W	D0,12(A1)
  DEF_ROMLOC(14776) : rom_29AC();                  // JSR	$000029AC
  DEF_ROMLOC(1477C) : move_tomem_8(D0, A1 + 0x26); // MOVE.B	D0,38(A1)
  DEF_ROMLOC(14780)
      : move_toreg_16(read_16(0xFFFFFE04), &D0);          // MOVE.W	$FE04,D0
  DEF_ROMLOC(14784) : and_toreg_8(0x3, &D0);              // ANDI.B	#$03,D0
  DEF_ROMLOC(14788) : if (!CCR_EQ) goto rom_147D6;        // BNE.B	$147D6
  DEF_ROMLOC(1478A) : move_tomem_8(0xE, A1 + 0x28);       // MOVE.B	#$0E,40(A1)
  DEF_ROMLOC(14790) : goto rom_147D6;                     // BRA.B	$147D6
  DEF_ROMLOC(14792) : btst_tomem_8(0x7, A0 + 0x36);       // BTST.B	#$07,54(A0)
  DEF_ROMLOC(14798) : if (CCR_EQ) goto rom_147D6;         // BEQ.B	$147D6
  DEF_ROMLOC(1479A) : move_toreg_16(read_16(v_air), &D2); // MOVE.W	$FE14,D2
  DEF_ROMLOC(1479E) : lsr_toreg_16(0x1, &D2);             // LSR.W	#$01,D2
  DEF_ROMLOC(147A0) : rom_29AC();                         // JSR	$000029AC
  DEF_ROMLOC(147A6) : and_toreg_16(0x3, &D0);             // ANDI.W	#$0003,D0
  DEF_ROMLOC(147AA) : if (!CCR_EQ) goto rom_147BE;        // BNE.B	$147BE
  DEF_ROMLOC(147AC) : bset_tomem_8(0x6, A0 + 0x36);       // BSET.B	#$06,54(A0)
  DEF_ROMLOC(147B2) : if (!CCR_EQ) goto rom_147D6;        // BNE.B	$147D6
  DEF_ROMLOC(147B4) : move_tomem_8(D2, A1 + 0x28);        // MOVE.B	D2,40(A1)
  DEF_ROMLOC(147B8) : move_tomem_16(0x1C, A1 + 0x38); // MOVE.W	#$001C,56(A1)
  DEF_ROMLOC(147BE) : tst_mem_8(A0 + 0x34);           // TST.B	52(A0)
  DEF_ROMLOC(147C2) : if (!CCR_EQ) goto rom_147D6;    // BNE.B	$147D6
  DEF_ROMLOC(147C4) : bset_tomem_8(0x6, A0 + 0x36);   // BSET.B	#$06,54(A0)
  DEF_ROMLOC(147CA) : if (!CCR_EQ) goto rom_147D6;    // BNE.B	$147D6
  DEF_ROMLOC(147CC) : move_tomem_8(D2, A1 + 0x28);    // MOVE.B	D2,40(A1)
  DEF_ROMLOC(147D0) : move_tomem_16(0x1C, A1 + 0x38); // MOVE.W	#$001C,56(A1)
  DEF_ROMLOC(147D6) : sub_tomem_8(0x1, A0 + 0x34);    // SUBQ.B	#$01,52(A0)
  DEF_ROMLOC(147DA) : if (CCR_PL) goto rom_147E0;     // BPL.B	$147E0
  DEF_ROMLOC(147DC) : clr_mem_16(A0 + 0x36);          // CLR.W	54(A0)
  DEF_ROMLOC(147E0) : return;                         // RTS
}