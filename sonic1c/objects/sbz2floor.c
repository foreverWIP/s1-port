// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"


ROMFUNC(rom_19FDC) {
  DEF_ROMLOC(19FDC) : {
    rom_DCCE();
    return;
  } // JMP	$0000DCCE
}
ROMFUNC(rom_1A310) {
  u8 switchindex = 0;
  DEF_ROMLOC(1A310) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(1A312) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(1A316)
      : move_toreg_16(read_16(0x1A31E + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(1A31A): goto rom_1A31E + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(1A31A) : switch (switchindex) {
  case 0:
    rom_1A32A();
    break;
  case 1:
    rom_1A3AC();
    break;
  case 2:
    rom_1A3E6();
    break;
  case 3:
    rom_1A412();
    break;
  case 4:
    rom_1A422();
    break;
  case 5:
    rom_1A430();
    break;
  }
}
ROMFUNC(rom_1A32A) {
  DEF_ROMLOC(1A32A) : move_tomem_16(0x2080, A0 + 0x8); // MOVE.W
                                                       // #$2080,8(A0)
  DEF_ROMLOC(1A330) : move_tomem_16(0x5D0, A0 + 0xC);  // MOVE.W	#$05D0,12(A0)
  DEF_ROMLOC(1A336)
      : move_tomem_8(0xFFFFFF80, A0 + 0x19);         // MOVE.B	#$80,25(A0)
  DEF_ROMLOC(1A33C) : move_tomem_8(0x10, A0 + 0x16); // MOVE.B	#$10,22(A0)
  DEF_ROMLOC(1A342) : move_tomem_8(0x4, A0 + 0x1);   // MOVE.B	#$04,1(A0)
  DEF_ROMLOC(1A348) : bset_tomem_8(0x7, A0 + 0x1);   // BSET.B	#$07,1(A0)
  DEF_ROMLOC(1A34E) : move_toreg_32(0x0, &D4);       // MOVEQ.L	$00,D4
  DEF_ROMLOC(1A350) : move_toreg_16(0x2010, &D5);    // MOVE.W	#$2010,D5
  DEF_ROMLOC(1A354) : move_toreg_32(0x7, &D6);       // MOVEQ.L	$07,D6
  DEF_ROMLOC(1A356) : move_toreg_32(A0 + 0x30, &A2); // LEA.L	48(A0),A2
  rom_1A35A(); // Detected flow into next function
}
ROMFUNC(rom_1A35A) {
  DEF_ROMLOC(1A35A) : rom_E11A();                  // JSR	$0000E11A
  DEF_ROMLOC(1A360) : if (!CCR_EQ) goto rom_1A3A6; // BNE.B	$1A3A6
  DEF_ROMLOC(1A362)
      : move_tomem_16(A1, (A2 += 2, A2 - 2));       // MOVE.W	A1,(A2)+
  DEF_ROMLOC(1A364) : move_tomem_8(0xFFFFFF83, A1); // MOVE.B	#$83,(A1)
  DEF_ROMLOC(1A368)
      : move_tomem_32(0x1A4C2, A1 + 0x4); // MOVE.L	#$0001A4C2,4(A1)
  DEF_ROMLOC(1A370) : move_tomem_16(0x4518, A1 + 0x2); // MOVE.W
                                                       // #$4518,2(A1)
  DEF_ROMLOC(1A376) : move_tomem_8(0x4, A1 + 0x1);     // MOVE.B	#$04,1(A1)
  DEF_ROMLOC(1A37C) : move_tomem_8(0x10, A1 + 0x19);   // MOVE.B	#$10,25(A1)
  DEF_ROMLOC(1A382) : move_tomem_8(0x10, A1 + 0x16);   // MOVE.B	#$10,22(A1)
  DEF_ROMLOC(1A388) : move_tomem_8(0x3, A1 + 0x18);    // MOVE.B	#$03,24(A1)
  DEF_ROMLOC(1A38E) : move_tomem_16(D5, A1 + 0x8);     // MOVE.W	D5,8(A1)
  DEF_ROMLOC(1A392) : move_tomem_16(0x5D0, A1 + 0xC);  // MOVE.W	#$05D0,12(A1)
  DEF_ROMLOC(1A398) : add_toreg_16(0x20, &D5);         // ADDI.W	#$0020,D5
  DEF_ROMLOC(1A39C) : move_tomem_8(0x8, A1 + 0x24);    // MOVE.B	#$08,36(A1)
  DEF_ROMLOC(1A3A2) : dec_reg_16(&D6);
  if ((D6 & 0xffff) != 0xffff)
    goto rom_1A35A;                                // DBF.W	D6,$1A35A
  DEF_ROMLOC(1A3A6) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(1A3AA) : return;                      // RTS
}
ROMFUNC(rom_1A3BC) {
  DEF_ROMLOC(1A3BC) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(1A3BE)
      : move_toreg_8(read_8(A0 + 0x1A), &D0);      // MOVE.B	26(A0),D0
  DEF_ROMLOC(1A3C2) : neg_reg_8(&D0);              // NEG.B	D0
  DEF_ROMLOC(1A3C4) : ext_reg_16(&D0);             // EXT.W	D0
  DEF_ROMLOC(1A3C6) : add_toreg_16(0x8, &D0);      // ADDQ.W	#$08,D0
  DEF_ROMLOC(1A3C8) : asl_toreg_16(0x4, &D0);      // ASL.W	#$04,D0
  DEF_ROMLOC(1A3CA) : move_toreg_16(0x2100, &D4);  // MOVE.W	#$2100,D4
  DEF_ROMLOC(1A3CE) : sub_toreg_16(D0, &D4);       // SUB.W	D0,D4
  DEF_ROMLOC(1A3D0) : move_tomem_8(D0, A0 + 0x19); // MOVE.B	D0,25(A0)
  DEF_ROMLOC(1A3D4) : move_tomem_16(D4, A0 + 0x8); // MOVE.W	D4,8(A0)
  DEF_ROMLOC(1A3D8) : move_toreg_32(0xB, &D1);     // MOVEQ.L	$0B,D1
  DEF_ROMLOC(1A3DA) : add_toreg_16(D0, &D1);       // ADD.W	D0,D1
  DEF_ROMLOC(1A3DC) : move_toreg_32(0x10, &D2);    // MOVEQ.L	$10,D2
  DEF_ROMLOC(1A3DE) : move_toreg_32(0x11, &D3);    // MOVEQ.L	$11,D3
  DEF_ROMLOC(1A3E0) : rom_10062();
  return; // JMP	$00010062
}
ROMFUNC(rom_1A3AC) {
  DEF_ROMLOC(1A3AC) : cmp_tomem_16(0x474F, A0 + 0x28); // CMPI.W
                                                       // #$474F,40(A0)
  DEF_ROMLOC(1A3B2) : if (!CCR_EQ) {
    rom_1A3BC();
    return;
  }                                                // BNE.B	$1A3BC
  DEF_ROMLOC(1A3B4) : clr_mem_8(A0 + 0x1A);        // CLR.B	26(A0)
  DEF_ROMLOC(1A3B8) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  rom_1A3BC();
}
ROMFUNC(rom_1A3E6) {
  DEF_ROMLOC(1A3E6) : sub_tomem_8(0xE, A0 + 0x1E);    // SUBI.B	#$0E,30(A0)
  DEF_ROMLOC(1A3EC) : if (CCR_CC) goto rom_1A410;     // BCC.B	$1A410
  DEF_ROMLOC(1A3EE) : move_toreg_32(0xFFFFFFFF, &D0); // MOVEQ.L	$FF,D0
  DEF_ROMLOC(1A3F0)
      : move_toreg_8(read_8(A0 + 0x1A), &D0); // MOVE.B	26(A0),D0
  DEF_ROMLOC(1A3F4) : ext_reg_16(&D0);        // EXT.W	D0
  DEF_ROMLOC(1A3F6) : add_toreg_16(D0, &D0);  // ADD.W	D0,D0
  DEF_ROMLOC(1A3F8)
      : move_toreg_16(read_16((s32)A0 + (s8)0x30 + (s16)D0),
                      &D0);                             // MOVE.W	48(A0,D0),D0
  DEF_ROMLOC(1A3FC) : move_toreg_32(D0, &A1);           // MOVEA.L	D0,A1
  DEF_ROMLOC(1A3FE) : move_tomem_16(0x474F, A1 + 0x28); // MOVE.W
                                                        // #$474F,40(A1)
  DEF_ROMLOC(1A404) : add_tomem_8(0x1, A0 + 0x1A);      // ADDQ.B	#$01,26(A0)
  DEF_ROMLOC(1A408) : cmp_tomem_8(0x8, A0 + 0x1A);      // CMPI.B	#$08,26(A0)
  DEF_ROMLOC(1A40E) : if (CCR_EQ) {
    rom_1A412();
    return;
  } // BEQ.B	$1A412
  DEF_ROMLOC(1A410) : rom_1A3BC();
  return; // BRA.B	$1A3BC
}
ROMFUNC(rom_1A412) {
  DEF_ROMLOC(1A412) : bclr_tomem_8(0x3, A0 + 0x22);  // BCLR.B	#$03,34(A0)
  DEF_ROMLOC(1A418) : bclr_tomem_8(0x3, 0xFFFFD022); // BCLR.B	#$03,$D022
  rom_19FDC();                                       // BRA.W	$19FDC
}
ROMFUNC(rom_1A422) {
  DEF_ROMLOC(1A422) : cmp_tomem_16(0x474F, A0 + 0x28); // CMPI.W
                                                       // #$474F,40(A0)
  DEF_ROMLOC(1A428) : if (CCR_EQ) {
    rom_1A444();
    return;
  } // BEQ.B	$1A444
  DEF_ROMLOC(1A42A) : rom_DC92();
  return; // JMP	$0000DC92
}
ROMFUNC(rom_1A430) {
  DEF_ROMLOC(1A430) : tst_mem_8(A0 + 0x1); // TST.B	1(A0)
  DEF_ROMLOC(1A434) : if (CCR_PL) {
    rom_19FDC();
    return;
  }                               // BPL.W	$19FDC
  DEF_ROMLOC(1A438) : rom_DC40(); // JSR	$0000DC40
  DEF_ROMLOC(1A43E) : rom_DC92();
  return; // JMP	$0000DC92
}
ROMFUNC(rom_1A444) {
  DEF_ROMLOC(1A444) : move_toreg_32(0x1A4AA, &A4);  // LEA.L	100(PC),A4
  DEF_ROMLOC(1A448) : move_toreg_32(0x1A4B2, &A5);  // LEA.L	104(PC),A5
  DEF_ROMLOC(1A44C) : move_toreg_32(0x1, &D4);      // MOVEQ.L	$01,D4
  DEF_ROMLOC(1A44E) : move_toreg_32(0x3, &D1);      // MOVEQ.L	$03,D1
  DEF_ROMLOC(1A450) : move_toreg_32(0x38, &D2);     // MOVEQ.L	$38,D2
  DEF_ROMLOC(1A452) : add_tomem_8(0x2, A0 + 0x24);  // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(1A456) : move_tomem_8(0x8, A0 + 0x19); // MOVE.B	#$08,25(A0)
  DEF_ROMLOC(1A45C) : move_tomem_8(0x8, A0 + 0x16); // MOVE.B	#$08,22(A0)
  DEF_ROMLOC(1A462) : move_toreg_32(A0, &A1);       // LEA.L	(A0),A1
  goto rom_1A46E;                                   // BRA.B	$1A46E
  DEF_ROMLOC(1A466) : rom_E130();                   // JSR	$0000E130
  DEF_ROMLOC(1A46C) : if (!CCR_EQ) goto rom_1A49A;  // BNE.B	$1A49A
  DEF_ROMLOC(1A46E) : move_toreg_32(A0, &A2);       // LEA.L	(A0),A2
  DEF_ROMLOC(1A470) : move_toreg_32(A1, &A3);       // LEA.L	(A1),A3
  DEF_ROMLOC(1A472) : move_toreg_32(0x3, &D3);      // MOVEQ.L	$03,D3
  DEF_ROMLOC(1A474)
      : move_tomem_32(read_32((A2 += 4, A2 - 4)),
                      (A3 += 4, A3 - 4)); // MOVE.L	(A2)+,(A3)+
  DEF_ROMLOC(1A476)
      : move_tomem_32(read_32((A2 += 4, A2 - 4)),
                      (A3 += 4, A3 - 4)); // MOVE.L	(A2)+,(A3)+
  DEF_ROMLOC(1A478)
      : move_tomem_32(read_32((A2 += 4, A2 - 4)),
                      (A3 += 4, A3 - 4)); // MOVE.L	(A2)+,(A3)+
  DEF_ROMLOC(1A47A)
      : move_tomem_32(read_32((A2 += 4, A2 - 4)),
                      (A3 += 4, A3 - 4)); // MOVE.L	(A2)+,(A3)+
  DEF_ROMLOC(1A47C) : dec_reg_16(&D3);
  if ((D3 & 0xffff) != 0xffff)
    goto rom_1A474; // DBF.W	D3,$1A474
  DEF_ROMLOC(1A480)
      : move_tomem_16(read_16((A4 += 2, A4 - 2)),
                      A1 + 0x12); // MOVE.W	(A4)+,18(A1)
  DEF_ROMLOC(1A484)
      : move_toreg_16(read_16((A5 += 2, A5 - 2)), &D3); // MOVE.W	(A5)+,D3
  DEF_ROMLOC(1A486) : add_tomem_16(D3, A1 + 0x8);       // ADD.W	D3,8(A1)
  DEF_ROMLOC(1A48A)
      : move_toreg_16(read_16((A5 += 2, A5 - 2)), &D3); // MOVE.W	(A5)+,D3
  DEF_ROMLOC(1A48C) : add_tomem_16(D3, A1 + 0xC);       // ADD.W	D3,12(A1)
  DEF_ROMLOC(1A490) : move_tomem_8(D4, A1 + 0x1A);      // MOVE.B	D4,26(A1)
  DEF_ROMLOC(1A494) : add_toreg_16(0x1, &D4);           // ADDQ.W	#$01,D4
  DEF_ROMLOC(1A496) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_1A466;                             // DBF.W	D1,$1A466
  DEF_ROMLOC(1A49A) : move_toreg_16(0xCB, &D0); // MOVE.W	#$00CB,D0
  DEF_ROMLOC(1A49E) : play_sound_special();     // JSR	$00001394
  DEF_ROMLOC(1A4A4) : rom_DC92();
  return; // JMP	$0000DC92
}