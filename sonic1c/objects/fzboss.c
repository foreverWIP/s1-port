// #define CHECK_STUFF 1
#include "../game.h"
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_1A502) {
  DEF_ROMLOC(1A502) : rom_DCCE();
  return; // JMP	$0000DCCE
}
ROMFUNC(rom_1A508) {
  u8 switchindex = 0;
  DEF_ROMLOC(1A508) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(1A50A) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(1A50E)
      : move_toreg_16(read_16(0x1A516 + (s16)(D0 & 0xffff)),
                      &D0); // MOVE.W	6(PC,D0),D0
  // DEF_ROMLOC(1A512): goto rom_1A516 + (s16)(D0 & 0xffff); // JMP	2(PC,D0)
  DEF_ROMLOC(1A512) : switch (switchindex) {
  case 0:
    rom_1A57E();
    break;
  case 1:
    rom_1A61C();
    break;
  case 2:
    rom_1AB44();
    break;
  case 3:
    rom_1AAFC();
    break;
  case 4:
    rom_1AA7C();
    break;
  case 5:
    rom_1AB62();
    break;
  case 6:
    rom_1AA1A();
    break;
  }
}
ROMFUNC(rom_1A57E) {
  DEF_ROMLOC(1A57E) : move_toreg_32(0x1A524, &A2);  // LEA.L	-92(PC),A2
  DEF_ROMLOC(1A582) : move_toreg_32(0x1A560, &A3);  // LEA.L	-36(PC),A3
  DEF_ROMLOC(1A586) : move_toreg_32(A0, &A1);       // MOVEA.L	A0,A1
  DEF_ROMLOC(1A588) : move_toreg_32(0x5, &D1);      // MOVEQ.L	$05,D1
  goto rom_1A594;                                   // BRA.B	$1A594
  DEF_ROMLOC(1A58C) : rom_E130();                   // JSR	$0000E130
  DEF_ROMLOC(1A592) : if (!CCR_EQ) goto rom_1A5D0;  // BNE.B	$1A5D0
  DEF_ROMLOC(1A594) : move_tomem_8(0xFFFFFF85, A1); // MOVE.B	#$85,(A1)
  DEF_ROMLOC(1A598)
      : move_tomem_16(read_16((A2 += 2, A2 - 2)),
                      A1 + 0x8); // MOVE.W	(A2)+,8(A1)
  DEF_ROMLOC(1A59C)
      : move_tomem_16(read_16((A2 += 2, A2 - 2)),
                      A1 + 0xC); // MOVE.W	(A2)+,12(A1)
  DEF_ROMLOC(1A5A0)
      : move_tomem_16(read_16((A2 += 2, A2 - 2)),
                      A1 + 0x2); // MOVE.W	(A2)+,2(A1)
  DEF_ROMLOC(1A5A4)
      : move_tomem_32(read_32((A2 += 4, A2 - 4)),
                      A1 + 0x4); // MOVE.L	(A2)+,4(A1)
  DEF_ROMLOC(1A5A8)
      : move_tomem_8(read_8(A3++), A1 + 0x24); // MOVE.B	(A3)+,36(A1)
  DEF_ROMLOC(1A5AC)
      : move_tomem_8(read_8(A3++), A1 + 0x1C); // MOVE.B	(A3)+,28(A1)
  DEF_ROMLOC(1A5B0)
      : move_tomem_8(read_8(A3++), A1 + 0x18); // MOVE.B	(A3)+,24(A1)
  DEF_ROMLOC(1A5B4)
      : move_tomem_8(read_8(A3++), A1 + 0x19); // MOVE.B	(A3)+,25(A1)
  DEF_ROMLOC(1A5B8)
      : move_tomem_8(read_8(A3++), A1 + 0x16);      // MOVE.B	(A3)+,22(A1)
  DEF_ROMLOC(1A5BC) : move_tomem_8(0x4, A1 + 0x1);  // MOVE.B	#$04,1(A1)
  DEF_ROMLOC(1A5C2) : bset_tomem_8(0x7, A0 + 0x1);  // BSET.B	#$07,1(A0)
  DEF_ROMLOC(1A5C8) : move_tomem_32(A0, A1 + 0x34); // MOVE.L	A0,52(A1)
  DEF_ROMLOC(1A5CC) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_1A58C;                                         // DBF.W	D1,$1A58C
  DEF_ROMLOC(1A5D0) : move_toreg_32(A0 + 0x36, &A2);        // LEA.L	54(A0),A2
  DEF_ROMLOC(1A5D4) : rom_E11A();                           // JSR	$0000E11A
  DEF_ROMLOC(1A5DA) : if (!CCR_EQ) goto rom_1A60A;          // BNE.B	$1A60A
  DEF_ROMLOC(1A5DC) : move_tomem_8(0xFFFFFF86, A1);         // MOVE.B	#$86,(A1)
  DEF_ROMLOC(1A5E0) : move_tomem_16(A1, A2);                // MOVE.W	A1,(A2)
  DEF_ROMLOC(1A5E2) : move_tomem_32(A0, A1 + 0x34);         // MOVE.L	A0,52(A1)
  DEF_ROMLOC(1A5E6) : move_toreg_32(A0 + 0x38, &A2);        // LEA.L	56(A0),A2
  DEF_ROMLOC(1A5EA) : move_toreg_32(0x0, &D2);              // MOVEQ.L	$00,D2
  DEF_ROMLOC(1A5EC) : move_toreg_32(0x3, &D1);              // MOVEQ.L	$03,D1
  DEF_ROMLOC(1A5EE) : rom_E130();                           // JSR	$0000E130
  DEF_ROMLOC(1A5F4) : if (!CCR_EQ) goto rom_1A60A;          // BNE.B	$1A60A
  DEF_ROMLOC(1A5F6) : move_tomem_16(A1, (A2 += 2, A2 - 2)); // MOVE.W	A1,(A2)+
  DEF_ROMLOC(1A5F8) : move_tomem_8(0xFFFFFF84, A1);         // MOVE.B	#$84,(A1)
  DEF_ROMLOC(1A5FC) : move_tomem_32(A0, A1 + 0x34);         // MOVE.L	A0,52(A1)
  DEF_ROMLOC(1A600) : move_tomem_8(D2, A1 + 0x28);          // MOVE.B	D2,40(A1)
  DEF_ROMLOC(1A604) : add_toreg_16(0x2, &D2);               // ADDQ.W	#$02,D2
  DEF_ROMLOC(1A606) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_1A5EE;                                  // DBF.W	D1,$1A5EE
  DEF_ROMLOC(1A60A) : move_tomem_16(0x0, A0 + 0x34); // MOVE.W	#$0000,52(A0)
  DEF_ROMLOC(1A610) : move_tomem_8(0x8, A0 + 0x21);  // MOVE.B	#$08,33(A0)
  DEF_ROMLOC(1A616)
      : move_tomem_16(0xFFFFFFFF, A0 + 0x30); // MOVE.W	#$FFFF,48(A0)
  rom_1A61C(); // Detected flow into next function
}
ROMFUNC(rom_1A61C) {
  u8 switchindex = 0;
  DEF_ROMLOC(1A61C) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(1A61E) : move_toreg_8(read_8(A0 + 0x34), &D0);
  switchindex = D0 / 2; // MOVE.B	52(A0),D0
  DEF_ROMLOC(1A622)
      : move_toreg_16(read_16(0x1A630 + (s16)(D0 & 0xffff)),
                      &D0); // MOVE.W	12(PC,D0),D0
  // DEF_ROMLOC(1A626): rom_1A630 + (s16)(D0 & 0xffff)(); // JSR	8(PC,D0)
  DEF_ROMLOC(1A626) : switch (switchindex) {
  case 0:
    rom_1A640();
    break;
  case 1:
    rom_1A658();
    break;
  case 2:
    rom_1A79C();
    break;
  case 3:
    rom_1A7E0();
    break;
  case 4:
    rom_1A82A();
    break;
  case 5:
    rom_1A8C8();
    break;
  case 6:
    rom_1A948();
    break;
  case 7:
    rom_1A98A();
    break;
  }
  DEF_ROMLOC(1A62A) : rom_DC92();
  return; // JMP	$0000DC92
}
ROMFUNC(rom_1A630) {
  DEF_ROMLOC(1A630) : or_tomem_8(0x28, A0);         // ORI.B	#$28,(A0)
  DEF_ROMLOC(1A634) : bchg_tomem_8(D0, A4 + 0x1B0); // BCHG.B	D0,432(A4)
  rom_1A640(); // Detected flow into next function
}
ROMFUNC(rom_1A640) {
  DEF_ROMLOC(1A640) : tst_mem_32(v_plc_buffer);    // TST.L	$F680
  DEF_ROMLOC(1A644) : if (!CCR_EQ) goto rom_1A652; // BNE.B	$1A652
  DEF_ROMLOC(1A646)
      : cmp_tomem_16(0x2450, 0xFFFFF700);            // CMPI.W
                                                     // #$2450,$F700
  DEF_ROMLOC(1A64C) : if (CCR_CS) goto rom_1A652;    // BCS.B	$1A652
  DEF_ROMLOC(1A64E) : add_tomem_8(0x2, A0 + 0x34);   // ADDQ.B	#$02,52(A0)
  DEF_ROMLOC(1A652) : add_tomem_32(0x1, 0xFFFFF636); // ADDQ.L	#$01,$F636
  DEF_ROMLOC(1A656) : return;                        // RTS
}
ROMFUNC(rom_1A658) {
  DEF_ROMLOC(1A658) : tst_mem_16(A0 + 0x30);       // TST.W	48(A0)
  DEF_ROMLOC(1A65C) : if (CCR_PL) goto rom_1A6C0;  // BPL.B	$1A6C0
  DEF_ROMLOC(1A65E) : clr_mem_16(A0 + 0x30);       // CLR.W	48(A0)
  DEF_ROMLOC(1A662) : rom_29AC();                  // JSR	$000029AC
  DEF_ROMLOC(1A668) : and_toreg_16(0xC, &D0);      // ANDI.W	#$000C,D0
  DEF_ROMLOC(1A66C) : move_toreg_16(D0, &D1);      // MOVE.W	D0,D1
  DEF_ROMLOC(1A66E) : add_toreg_16(0x2, &D1);      // ADDQ.W	#$02,D1
  DEF_ROMLOC(1A670) : tst_reg_32(&D0);             // TST.L	D0
  DEF_ROMLOC(1A672) : if (CCR_PL) goto rom_1A676;  // BPL.B	$1A676
  DEF_ROMLOC(1A674) : exg_toreg_32(&D1, &D0);      // EXG.L	D1,D0
  DEF_ROMLOC(1A676) : move_toreg_32(0x1A78C, &A1); // LEA.L	276(PC),A1
  DEF_ROMLOC(1A67A)
      : move_toreg_16(read_16((s32)A1 + (s8)0x0 + (s16)D0),
                      &D0); // MOVE.W	0(A1,D0),D0
  DEF_ROMLOC(1A67E)
      : move_toreg_16(read_16((s32)A1 + (s8)0x0 + (s16)D1),
                      &D1);                           // MOVE.W	0(A1,D1),D1
  DEF_ROMLOC(1A682) : move_tomem_16(D0, A0 + 0x30);   // MOVE.W	D0,48(A0)
  DEF_ROMLOC(1A686) : move_toreg_32(0xFFFFFFFF, &D2); // MOVEQ.L	$FF,D2
  DEF_ROMLOC(1A688)
      : move_toreg_16(read_16((s32)A0 + (s8)0x38 + (s16)D0),
                      &D2);                   // MOVE.W	56(A0,D0),D2
  DEF_ROMLOC(1A68C) : move_toreg_32(D2, &A1); // MOVEA.L	D2,A1
  DEF_ROMLOC(1A68E)
      : move_tomem_8(0xFFFFFFFF, A1 + 0x29); // MOVE.B	#$FF,41(A1)
  DEF_ROMLOC(1A694)
      : move_tomem_16(0xFFFFFFFF, A1 + 0x30); // MOVE.W	#$FFFF,48(A1)
  DEF_ROMLOC(1A69A)
      : move_toreg_16(read_16((s32)A0 + (s8)0x38 + (s16)D1),
                      &D2);                          // MOVE.W	56(A0,D1),D2
  DEF_ROMLOC(1A69E) : move_toreg_32(D2, &A1);        // MOVEA.L	D2,A1
  DEF_ROMLOC(1A6A0) : move_tomem_8(0x1, A1 + 0x29);  // MOVE.B	#$01,41(A1)
  DEF_ROMLOC(1A6A6) : move_tomem_16(0x0, A1 + 0x30); // MOVE.W	#$0000,48(A1)
  DEF_ROMLOC(1A6AC) : move_tomem_16(0x1, A0 + 0x32); // MOVE.W	#$0001,50(A0)
  DEF_ROMLOC(1A6B2) : clr_mem_8(A0 + 0x35);          // CLR.B	53(A0)
  DEF_ROMLOC(1A6B6) : move_toreg_16(0xB7, &D0);      // MOVE.W	#$00B7,D0
  DEF_ROMLOC(1A6BA) : play_sound_special();          // JSR	$00001394
  DEF_ROMLOC(1A6C0) : tst_mem_16(A0 + 0x32);         // TST.W	50(A0)
  DEF_ROMLOC(1A6C4) : if (CCR_MI) goto rom_1A756;    // BMI.W	$1A756
  DEF_ROMLOC(1A6C8) : bclr_tomem_8(0x0, A0 + 0x22);  // BCLR.B	#$00,34(A0)
  DEF_ROMLOC(1A6CE)
      : move_toreg_16(read_16(0xFFFFD008), &D0);            // MOVE.W	$D008,D0
  DEF_ROMLOC(1A6D2) : sub_toreg_16(read_16(A0 + 0x8), &D0); // SUB.W	8(A0),D0
  DEF_ROMLOC(1A6D6) : if (CCR_CS) goto rom_1A6DE;           // BCS.B	$1A6DE
  DEF_ROMLOC(1A6D8) : bset_tomem_8(0x0, A0 + 0x22); // BSET.B	#$00,34(A0)
  DEF_ROMLOC(1A6DE) : move_toreg_16(0x2B, &D1);     // MOVE.W	#$002B,D1
  DEF_ROMLOC(1A6E2) : move_toreg_16(0x14, &D2);     // MOVE.W	#$0014,D2
  DEF_ROMLOC(1A6E6) : move_toreg_16(0x14, &D3);     // MOVE.W	#$0014,D3
  DEF_ROMLOC(1A6EA) : move_toreg_16(read_16(A0 + 0x8), &D4); // MOVE.W	8(A0),D4
  DEF_ROMLOC(1A6EE) : rom_10062();                           // JSR	$00010062
  DEF_ROMLOC(1A6F4) : tst_reg_16(&D4);                       // TST.W	D4
  DEF_ROMLOC(1A6F6) : if (CCR_GT) goto rom_1A700;            // BGT.B	$1A700
  DEF_ROMLOC(1A6F8) : tst_mem_8(A0 + 0x35);                  // TST.B	53(A0)
  DEF_ROMLOC(1A6FC) : if (!CCR_EQ) goto rom_1A738;           // BNE.B	$1A738
  goto rom_1A746;                                            // BRA.B	$1A746
  DEF_ROMLOC(1A700) : add_tomem_16(0x7, 0xFFFFF636); // ADDQ.W	#$07,$F636
  DEF_ROMLOC(1A704) : cmp_tomem_8(0x2, 0xFFFFD01C);  // CMPI.B	#$02,$D01C
  DEF_ROMLOC(1A70A) : if (!CCR_EQ) goto rom_1A6F8;   // BNE.B	$1A6F8
  DEF_ROMLOC(1A70C) : move_toreg_16(0x300, &D0);     // MOVE.W	#$0300,D0
  DEF_ROMLOC(1A710) : btst_tomem_8(0x0, A0 + 0x22);  // BTST.B	#$00,34(A0)
  DEF_ROMLOC(1A716) : if (!CCR_EQ) goto rom_1A71A;   // BNE.B	$1A71A
  DEF_ROMLOC(1A718) : neg_reg_16(&D0);               // NEG.W	D0
  DEF_ROMLOC(1A71A) : move_tomem_16(D0, 0xFFFFD010); // MOVE.W	D0,$D010
  DEF_ROMLOC(1A71E) : tst_mem_8(A0 + 0x35);          // TST.B	53(A0)
  DEF_ROMLOC(1A722) : if (!CCR_EQ) goto rom_1A738;   // BNE.B	$1A738
  DEF_ROMLOC(1A724) : sub_tomem_8(0x1, A0 + 0x21);   // SUBQ.B	#$01,33(A0)
  DEF_ROMLOC(1A728) : move_tomem_8(0x64, A0 + 0x35); // MOVE.B	#$64,53(A0)
  DEF_ROMLOC(1A72E) : move_toreg_16(0xAC, &D0);      // MOVE.W	#$00AC,D0
  DEF_ROMLOC(1A732) : play_sound_special();          // JSR	$00001394
  DEF_ROMLOC(1A738) : sub_tomem_8(0x1, A0 + 0x35);   // SUBQ.B	#$01,53(A0)
  DEF_ROMLOC(1A73C) : if (CCR_EQ) goto rom_1A746;    // BEQ.B	$1A746
  DEF_ROMLOC(1A73E) : move_tomem_8(0x3, A0 + 0x1C);  // MOVE.B	#$03,28(A0)
  goto rom_1A74C;                                    // BRA.B	$1A74C
  DEF_ROMLOC(1A746) : move_tomem_8(0x1, A0 + 0x1C);  // MOVE.B	#$01,28(A0)
  DEF_ROMLOC(1A74C) : move_toreg_32(0x1A1B2, &A1);   // LEA.L	-1436(PC),A1
  DEF_ROMLOC(1A750) : rom_ADA2();
  return;                                          // JMP	$0000ADA2
  DEF_ROMLOC(1A756) : tst_mem_8(A0 + 0x21);        // TST.B	33(A0)
  DEF_ROMLOC(1A75A) : if (CCR_EQ) goto rom_1A76C;  // BEQ.B	$1A76C
  DEF_ROMLOC(1A75C) : add_tomem_8(0x2, A0 + 0x34); // ADDQ.B	#$02,52(A0)
  DEF_ROMLOC(1A760)
      : move_tomem_16(0xFFFFFFFF, A0 + 0x30);       // MOVE.W	#$FFFF,48(A0)
  DEF_ROMLOC(1A766) : clr_mem_16(A0 + 0x32);        // CLR.W	50(A0)
  DEF_ROMLOC(1A76A) : return;                       // RTS
  DEF_ROMLOC(1A76C) : move_toreg_32(0x64, &D0);     // MOVEQ.L	$64,D0
  DEF_ROMLOC(1A76E) : rom_1CE42();                  // BSR.W	$1CE42
  DEF_ROMLOC(1A772) : move_tomem_8(0x6, A0 + 0x34); // MOVE.B	#$06,52(A0)
  DEF_ROMLOC(1A778)
      : move_tomem_16(0x25C0, A0 + 0x8); // MOVE.W
                                         // #$25C0,8(A0)
  DEF_ROMLOC(1A77E)
      : move_tomem_16(0x53C, A0 + 0xC); // MOVE.W	#$053C,12(A0)
  DEF_ROMLOC(1A784)
      : move_tomem_8(0x14, A0 + 0x16); // MOVE.B	#$14,22(A0)
  DEF_ROMLOC(1A78A) : return;          // RTS
}
ROMFUNC(rom_1A79C) {
  DEF_ROMLOC(1A79C) : move_toreg_32(0xFFFFFFFF, &D0); // MOVEQ.L	$FF,D0
  DEF_ROMLOC(1A79E)
      : move_toreg_16(read_16(A0 + 0x36), &D0);   // MOVE.W	54(A0),D0
  DEF_ROMLOC(1A7A2) : move_toreg_32(D0, &A1);     // MOVEA.L	D0,A1
  DEF_ROMLOC(1A7A4) : tst_mem_16(A0 + 0x30);      // TST.W	48(A0)
  DEF_ROMLOC(1A7A8) : if (CCR_PL) goto rom_1A7B6; // BPL.B	$1A7B6
  DEF_ROMLOC(1A7AA) : clr_mem_16(A0 + 0x30);      // CLR.W	48(A0)
  DEF_ROMLOC(1A7AE)
      : move_tomem_8(0xFFFFFFFF, A1 + 0x29);   // MOVE.B	#$FF,41(A1)
  DEF_ROMLOC(1A7B4) : rom_1A7D6();             // BSR.B	$1A7D6
  DEF_ROMLOC(1A7B6) : move_toreg_32(0xF, &D0); // MOVEQ.L	$0F,D0
  DEF_ROMLOC(1A7B8)
      : and_toreg_16(read_16(0xFFFFFE0E), &D0);    // AND.W	$FE0E,D0
  DEF_ROMLOC(1A7BC) : if (!CCR_EQ) goto rom_1A7C0; // BNE.B	$1A7C0
  DEF_ROMLOC(1A7BE) : rom_1A7D6();                 // BSR.B	$1A7D6
  DEF_ROMLOC(1A7C0) : tst_mem_16(A0 + 0x32);       // TST.W	50(A0)
  DEF_ROMLOC(1A7C4) : if (CCR_EQ) goto rom_1A7D4;  // BEQ.B	$1A7D4
  DEF_ROMLOC(1A7C6) : sub_tomem_8(0x2, A0 + 0x34); // SUBQ.B	#$02,52(A0)
  DEF_ROMLOC(1A7CA)
      : move_tomem_16(0xFFFFFFFF, A0 + 0x30); // MOVE.W	#$FFFF,48(A0)
  DEF_ROMLOC(1A7D0) : clr_mem_16(A0 + 0x32);  // CLR.W	50(A0)
  DEF_ROMLOC(1A7D4) : return;                 // RTS
}
ROMFUNC(rom_1A7D6) {
  DEF_ROMLOC(1A7D6) : move_toreg_16(0xB1, &D0); // MOVE.W	#$00B1,D0
  DEF_ROMLOC(1A7DA) : play_sound_special();
  return; // JMP	$00001394
}
ROMFUNC(rom_1A7E0) {
  DEF_ROMLOC(1A7E0)
      : move_tomem_8(0x30, A0 + 0x19);              // MOVE.B	#$30,25(A0)
  DEF_ROMLOC(1A7E6) : bset_tomem_8(0x0, A0 + 0x22); // BSET.B	#$00,34(A0)
  DEF_ROMLOC(1A7EC) : rom_DC6C();                   // JSR	$0000DC6C
  DEF_ROMLOC(1A7F2) : move_tomem_8(0x6, A0 + 0x1A); // MOVE.B	#$06,26(A0)
  DEF_ROMLOC(1A7F8)
      : add_tomem_16(0x10, A0 + 0x12); // ADDI.W	#$0010,18(A0)
  DEF_ROMLOC(1A7FE)
      : cmp_tomem_16(0x59C, A0 + 0xC);            // CMPI.W	#$059C,12(A0)
  DEF_ROMLOC(1A804) : if (CCR_CS) goto rom_1A826; // BCS.B	$1A826
  DEF_ROMLOC(1A806)
      : move_tomem_16(0x59C, A0 + 0xC);            // MOVE.W	#$059C,12(A0)
  DEF_ROMLOC(1A80C) : add_tomem_8(0x2, A0 + 0x34); // ADDQ.B	#$02,52(A0)
  DEF_ROMLOC(1A810)
      : move_tomem_8(0x20, A0 + 0x19); // MOVE.B	#$20,25(A0)
  DEF_ROMLOC(1A816)
      : move_tomem_16(0x100, A0 + 0x10); // MOVE.W
                                         // #$0100,16(A0)
  DEF_ROMLOC(1A81C)
      : move_tomem_16(0xFFFFFF00, A0 + 0x12);       // MOVE.W	#$FF00,18(A0)
  DEF_ROMLOC(1A822) : add_tomem_8(0x2, 0xFFFFF742); // ADDQ.B	#$02,$F742
  DEF_ROMLOC(1A826) : rom_1A91C();                  // BRA.W	$1A91C
}
ROMFUNC(rom_1A82A) {
  DEF_ROMLOC(1A82A) : bset_tomem_8(0x0, A0 + 0x22);  // BSET.B	#$00,34(A0)
  DEF_ROMLOC(1A830) : move_tomem_8(0x4, A0 + 0x1C);  // MOVE.B	#$04,28(A0)
  DEF_ROMLOC(1A836) : rom_DC6C();                    // JSR	$0000DC6C
  DEF_ROMLOC(1A83C) : add_tomem_16(0x10, A0 + 0x12); // ADDI.W	#$0010,18(A0)
  DEF_ROMLOC(1A842) : cmp_tomem_16(0x5A3, A0 + 0xC); // CMPI.W	#$05A3,12(A0)
  DEF_ROMLOC(1A848) : if (CCR_CS) goto rom_1A850;    // BCS.B	$1A850
  DEF_ROMLOC(1A84A)
      : move_tomem_16(0xFFFFFFC0, A0 + 0x12); // MOVE.W	#$FFC0,18(A0)
  DEF_ROMLOC(1A850)
      : move_tomem_16(0x400, A0 + 0x10); // MOVE.W
                                         // #$0400,16(A0)
  DEF_ROMLOC(1A856)
      : move_toreg_16(read_16(A0 + 0x8), &D0);                // MOVE.W	8(A0),D0
  DEF_ROMLOC(1A85A) : sub_toreg_16(read_16(0xFFFFD008), &D0); // SUB.W	$D008,D0
  DEF_ROMLOC(1A85E) : if (CCR_PL) goto rom_1A86A;             // BPL.B	$1A86A
  DEF_ROMLOC(1A860)
      : move_tomem_16(0x500, A0 + 0x10);          // MOVE.W
                                                  // #$0500,16(A0)
  goto rom_1A8A8;                                 // BRA.W	$1A8A8
  DEF_ROMLOC(1A86A) : sub_toreg_16(0x70, &D0);    // SUBI.W	#$0070,D0
  DEF_ROMLOC(1A86E) : if (CCR_CS) goto rom_1A8A8; // BCS.B	$1A8A8
  DEF_ROMLOC(1A870)
      : sub_tomem_16(0x100, A0 + 0x10);           // SUBI.W	#$0100,16(A0)
  DEF_ROMLOC(1A876) : sub_toreg_16(0x8, &D0);     // SUBQ.W	#$08,D0
  DEF_ROMLOC(1A878) : if (CCR_CS) goto rom_1A8A8; // BCS.B	$1A8A8
  DEF_ROMLOC(1A87A)
      : sub_tomem_16(0x100, A0 + 0x10);           // SUBI.W	#$0100,16(A0)
  DEF_ROMLOC(1A880) : sub_toreg_16(0x8, &D0);     // SUBQ.W	#$08,D0
  DEF_ROMLOC(1A882) : if (CCR_CS) goto rom_1A8A8; // BCS.B	$1A8A8
  DEF_ROMLOC(1A884)
      : sub_tomem_16(0x80, A0 + 0x10);            // SUBI.W	#$0080,16(A0)
  DEF_ROMLOC(1A88A) : sub_toreg_16(0x8, &D0);     // SUBQ.W	#$08,D0
  DEF_ROMLOC(1A88C) : if (CCR_CS) goto rom_1A8A8; // BCS.B	$1A8A8
  DEF_ROMLOC(1A88E)
      : sub_tomem_16(0x80, A0 + 0x10);            // SUBI.W	#$0080,16(A0)
  DEF_ROMLOC(1A894) : sub_toreg_16(0x8, &D0);     // SUBQ.W	#$08,D0
  DEF_ROMLOC(1A896) : if (CCR_CS) goto rom_1A8A8; // BCS.B	$1A8A8
  DEF_ROMLOC(1A898)
      : sub_tomem_16(0x80, A0 + 0x10);            // SUBI.W	#$0080,16(A0)
  DEF_ROMLOC(1A89E) : sub_toreg_16(0x38, &D0);    // SUBI.W	#$0038,D0
  DEF_ROMLOC(1A8A2) : if (CCR_CS) goto rom_1A8A8; // BCS.B	$1A8A8
  DEF_ROMLOC(1A8A4) : clr_mem_16(A0 + 0x10);      // CLR.W	16(A0)
  DEF_ROMLOC(1A8A8)
      : cmp_tomem_16(0x26A0, A0 + 0x8);           // CMPI.W	#$26A0,8(A0)
  DEF_ROMLOC(1A8AE) : if (CCR_CS) goto rom_1A8C6; // BCS.B	$1A8C6
  DEF_ROMLOC(1A8B0)
      : move_tomem_16(0x26A0, A0 + 0x8); // MOVE.W
                                         // #$26A0,8(A0)
  DEF_ROMLOC(1A8B6)
      : move_tomem_16(0x240, A0 + 0x10); // MOVE.W
                                         // #$0240,16(A0)
  DEF_ROMLOC(1A8BC)
      : move_tomem_16(0xFFFFFB40, A0 + 0x12);      // MOVE.W	#$FB40,18(A0)
  DEF_ROMLOC(1A8C2) : add_tomem_8(0x2, A0 + 0x34); // ADDQ.B	#$02,52(A0)
  DEF_ROMLOC(1A8C6) : rom_1A912();                 // BRA.B	$1A912
}
ROMFUNC(rom_1A8C8) {
  DEF_ROMLOC(1A8C8) : rom_DC6C();                     // JSR	$0000DC6C
  DEF_ROMLOC(1A8CE) : cmp_tomem_16(0x26E0, A0 + 0x8); // CMPI.W	#$26E0,8(A0)
  DEF_ROMLOC(1A8D4) : if (CCR_CS) goto rom_1A8DA;     // BCS.B	$1A8DA
  DEF_ROMLOC(1A8D6) : clr_mem_16(A0 + 0x10);          // CLR.W	16(A0)
  DEF_ROMLOC(1A8DA) : add_tomem_16(0x34, A0 + 0x12);  // ADDI.W	#$0034,18(A0)
  DEF_ROMLOC(1A8E0) : tst_mem_16(A0 + 0x12);          // TST.W	18(A0)
  DEF_ROMLOC(1A8E4) : if (CCR_MI) goto rom_1A8F8;     // BMI.B	$1A8F8
  DEF_ROMLOC(1A8E6) : cmp_tomem_16(0x592, A0 + 0xC);  // CMPI.W	#$0592,12(A0)
  DEF_ROMLOC(1A8EC) : if (CCR_CS) goto rom_1A8F8;     // BCS.B	$1A8F8
  DEF_ROMLOC(1A8EE) : move_tomem_16(0x592, A0 + 0xC); // MOVE.W	#$0592,12(A0)
  DEF_ROMLOC(1A8F4) : clr_mem_16(A0 + 0x12);          // CLR.W	18(A0)
  DEF_ROMLOC(1A8F8)
      : move_toreg_16(read_16(A0 + 0x10), &D0);             // MOVE.W	16(A0),D0
  DEF_ROMLOC(1A8FC) : or_toreg_16(read_16(A0 + 0x12), &D0); // OR.W
                                                            // 18(A0),D0
  DEF_ROMLOC(1A900) : if (!CCR_EQ) {
    rom_1A912();
    return;
  }                                                // BNE.B	$1A912
  DEF_ROMLOC(1A902) : add_tomem_8(0x2, A0 + 0x34); // ADDQ.B	#$02,52(A0)
  DEF_ROMLOC(1A906)
      : move_tomem_16(0xFFFFFE80, A0 + 0x12);       // MOVE.W	#$FE80,18(A0)
  DEF_ROMLOC(1A90C) : move_tomem_8(0x1, A0 + 0x21); // MOVE.B	#$01,33(A0)
  rom_1A912();
}
ROMFUNC(rom_1A912) {
  DEF_ROMLOC(1A912) : move_toreg_32(0x1A1B2, &A1); // LEA.L	-1890(PC),A1
  DEF_ROMLOC(1A916) : rom_ADA2();                  // JSR	$0000ADA2
  rom_1A91C();
}
ROMFUNC(rom_1A91C) {
  DEF_ROMLOC(1A91C)
      : cmp_tomem_16(0x2700, 0xFFFFF72A);            // CMPI.W
                                                     // #$2700,$F72A
  DEF_ROMLOC(1A922) : if (CCR_GE) goto rom_1A928;    // BGE.B	$1A928
  DEF_ROMLOC(1A924) : add_tomem_16(0x2, 0xFFFFF72A); // ADDQ.W	#$02,$F72A
  DEF_ROMLOC(1A928) : cmp_tomem_8(0xC, A0 + 0x34);   // CMPI.B	#$0C,52(A0)
  DEF_ROMLOC(1A92E) : if (CCR_GE) goto rom_1A946;    // BGE.B	$1A946
  DEF_ROMLOC(1A930) : move_toreg_16(0x1B, &D1);      // MOVE.W	#$001B,D1
  DEF_ROMLOC(1A934) : move_toreg_16(0x70, &D2);      // MOVE.W	#$0070,D2
  DEF_ROMLOC(1A938) : move_toreg_16(0x71, &D3);      // MOVE.W	#$0071,D3
  DEF_ROMLOC(1A93C)
      : move_toreg_16(read_16(A0 + 0x8), &D4); // MOVE.W	8(A0),D4
  DEF_ROMLOC(1A940) : rom_10062();
  return;                     // JMP	$00010062
  DEF_ROMLOC(1A946) : return; // RTS
}
ROMFUNC(rom_1A948) {
  DEF_ROMLOC(1A948)
      : move_tomem_32(0x184B8, A0 + 0x4);             // MOVE.L	#$000184B8,4(A0)
  DEF_ROMLOC(1A950) : move_tomem_16(0x400, A0 + 0x2); // MOVE.W	#$0400,2(A0)
  DEF_ROMLOC(1A956) : move_tomem_8(0x0, A0 + 0x1C);   // MOVE.B	#$00,28(A0)
  DEF_ROMLOC(1A95C) : bset_tomem_8(0x0, A0 + 0x22);   // BSET.B	#$00,34(A0)
  DEF_ROMLOC(1A962) : rom_DC6C();                     // JSR	$0000DC6C
  DEF_ROMLOC(1A968) : cmp_tomem_16(0x544, A0 + 0xC);  // CMPI.W	#$0544,12(A0)
  DEF_ROMLOC(1A96E) : if (CCR_CC) goto rom_1A986;     // BCC.B	$1A986
  DEF_ROMLOC(1A970)
      : move_tomem_16(0x180, A0 + 0x10); // MOVE.W
                                         // #$0180,16(A0)
  DEF_ROMLOC(1A976)
      : move_tomem_16(0xFFFFFFE8, A0 + 0x12);       // MOVE.W	#$FFE8,18(A0)
  DEF_ROMLOC(1A97C) : move_tomem_8(0xF, A0 + 0x20); // MOVE.B	#$0F,32(A0)
  DEF_ROMLOC(1A982) : add_tomem_8(0x2, A0 + 0x34);  // ADDQ.B	#$02,52(A0)
  DEF_ROMLOC(1A986) : rom_1A912();                  // BRA.W	$1A912
}
ROMFUNC(rom_1A98A) {
  DEF_ROMLOC(1A98A) : bset_tomem_8(0x0, A0 + 0x22);   // BSET.B	#$00,34(A0)
  DEF_ROMLOC(1A990) : rom_DC6C();                     // JSR	$0000DC6C
  DEF_ROMLOC(1A996) : tst_mem_16(A0 + 0x30);          // TST.W	48(A0)
  DEF_ROMLOC(1A99A) : if (!CCR_EQ) goto rom_1A9B2;    // BNE.B	$1A9B2
  DEF_ROMLOC(1A99C) : tst_mem_8(A0 + 0x20);           // TST.B	32(A0)
  DEF_ROMLOC(1A9A0) : if (!CCR_EQ) goto rom_1A9CC;    // BNE.B	$1A9CC
  DEF_ROMLOC(1A9A2) : move_tomem_16(0x1E, A0 + 0x30); // MOVE.W	#$001E,48(A0)
  DEF_ROMLOC(1A9A8) : move_toreg_16(0xAC, &D0);       // MOVE.W	#$00AC,D0
  DEF_ROMLOC(1A9AC) : play_sound_special();           // JSR	$00001394
  DEF_ROMLOC(1A9B2) : sub_tomem_16(0x1, A0 + 0x30);   // SUBQ.W	#$01,48(A0)
  DEF_ROMLOC(1A9B6) : if (!CCR_EQ) goto rom_1A9CC;    // BNE.B	$1A9CC
  DEF_ROMLOC(1A9B8) : tst_mem_8(A0 + 0x22);           // TST.B	34(A0)
  DEF_ROMLOC(1A9BC) : if (CCR_PL) goto rom_1A9C6;     // BPL.B	$1A9C6
  DEF_ROMLOC(1A9BE) : move_tomem_16(0x60, A0 + 0x12); // MOVE.W	#$0060,18(A0)
  goto rom_1A9CC;
  return;                                           // BRA.B	$1A9CC
  DEF_ROMLOC(1A9C6) : move_tomem_8(0xF, A0 + 0x20); // MOVE.B	#$0F,32(A0)
  DEF_ROMLOC(1A9CC)
      : cmp_tomem_16(0x2790, 0xFFFFD008);            // CMPI.W
                                                     // #$2790,$D008
  DEF_ROMLOC(1A9D2) : if (CCR_LT) goto rom_1A9F0;    // BLT.B	$1A9F0
  DEF_ROMLOC(1A9D4) : move_tomem_8(0x1, 0xFFFFF7CC); // MOVE.B	#$01,$F7CC
  DEF_ROMLOC(1A9DA)
      : move_tomem_16(0x0, 0xFFFFF602);           // MOVE.W	#$0000,$F602
  DEF_ROMLOC(1A9E0) : clr_mem_16(0xFFFFD014);     // CLR.W	$D014
  DEF_ROMLOC(1A9E4) : tst_mem_16(A0 + 0x12);      // TST.W	18(A0)
  DEF_ROMLOC(1A9E8) : if (CCR_PL) goto rom_1A9FE; // BPL.B	$1A9FE
  DEF_ROMLOC(1A9EA)
      : move_tomem_16(0x100, 0xFFFFF602); // MOVE.W
                                          // #$0100,$F602
  DEF_ROMLOC(1A9F0)
      : cmp_tomem_16(0x27E0, 0xFFFFD008);         // CMPI.W
                                                  // #$27E0,$D008
  DEF_ROMLOC(1A9F6) : if (CCR_LT) goto rom_1A9FE; // BLT.B	$1A9FE
  DEF_ROMLOC(1A9F8)
      : move_tomem_16(0x27E0, 0xFFFFD008); // MOVE.W
                                           // #$27E0,$D008
  DEF_ROMLOC(1A9FE)
      : cmp_tomem_16(0x2900, A0 + 0x8);           // CMPI.W	#$2900,8(A0)
  DEF_ROMLOC(1AA04) : if (CCR_CS) goto rom_1AA16; // BCS.B	$1AA16
  DEF_ROMLOC(1AA06) : tst_mem_8(A0 + 0x1);        // TST.B	1(A0)
  DEF_ROMLOC(1AA0A) : if (CCR_MI) goto rom_1AA16; // BMI.B	$1AA16
  DEF_ROMLOC(1AA0C) : SET_GM_ENDING();
  rom_1A502();
  return; // BRA.W	$1A502
  DEF_ROMLOC(1AA16) : rom_1A912();
  return; // BRA.W	$1A912
}
ROMFUNC(rom_1AA1A) {
  DEF_ROMLOC(1AA1A)
      : move_toreg_32(read_32(A0 + 0x34), &A1);      // MOVEA.L	52(A0),A1
  DEF_ROMLOC(1AA1E) : move_toreg_8(read_8(A1), &D0); // MOVE.B	(A1),D0
  DEF_ROMLOC(1AA20) : cmp_toreg_8(read_8(A0), &D0);  // CMP.B	(A0),D0
  DEF_ROMLOC(1AA22) : if (!CCR_EQ) {
    rom_1A502();
    return;
  }                                                 // BNE.W	$1A502
  DEF_ROMLOC(1AA26) : move_tomem_8(0x7, A0 + 0x1C); // MOVE.B	#$07,28(A0)
  DEF_ROMLOC(1AA2C) : cmp_tomem_8(0xC, A1 + 0x34);  // CMPI.B	#$0C,52(A1)
  DEF_ROMLOC(1AA32) : if (CCR_GE) goto rom_1AA36;   // BGE.B	$1AA36
  rom_1AA5C();
  return;                                           // BRA.B	$1AA5C
  DEF_ROMLOC(1AA36) : tst_mem_16(A1 + 0x10);        // TST.W	16(A1)
  DEF_ROMLOC(1AA3A) : if (CCR_EQ) goto rom_1AA42;   // BEQ.B	$1AA42
  DEF_ROMLOC(1AA3C) : move_tomem_8(0xB, A0 + 0x1C); // MOVE.B	#$0B,28(A0)
  DEF_ROMLOC(1AA42) : move_toreg_32(0x18468, &A1);  // LEA.L	-9692(PC),A1
  DEF_ROMLOC(1AA46) : rom_ADA2();                   // JSR	$0000ADA2
  rom_1AA4C(); // Detected flow into next function
}
ROMFUNC(rom_1AA4C) {
  DEF_ROMLOC(1AA4C)
      : move_toreg_32(read_32(A0 + 0x34), &A1); // MOVEA.L	52(A0),A1
  DEF_ROMLOC(1AA50)
      : move_tomem_16(read_16(A1 + 0x8), A0 + 0x8); // MOVE.W	8(A1),8(A0)
  DEF_ROMLOC(1AA56)
      : move_tomem_16(read_16(A1 + 0xC), A0 + 0xC); // MOVE.W	12(A1),12(A0)
  rom_1AA5C(); // Detected flow into next function
}
ROMFUNC(rom_1AA5C) {
  DEF_ROMLOC(1AA5C)
      : move_toreg_32(read_32(A0 + 0x34), &A1); // MOVEA.L	52(A0),A1
  DEF_ROMLOC(1AA60)
      : move_tomem_8(read_8(A1 + 0x22), A0 + 0x22); // MOVE.B	34(A1),34(A0)
  DEF_ROMLOC(1AA66) : move_toreg_32(0x3, &D0);      // MOVEQ.L	$03,D0
  DEF_ROMLOC(1AA68)
      : and_toreg_8(read_8(A0 + 0x22), &D0); // AND.B	34(A0),D0
  DEF_ROMLOC(1AA6C)
      : and_tomem_8(0xFFFFFFFC, A0 + 0x1);      // ANDI.B
                                                // #$FC,1(A0)
  DEF_ROMLOC(1AA72) : or_tomem_8(D0, A0 + 0x1); // OR.B	D0,1(A0)
  DEF_ROMLOC(1AA76) : rom_DC92();
  return; // JMP	$0000DC92
}
ROMFUNC(rom_1AA7C) {
  DEF_ROMLOC(1AA7C)
      : move_toreg_32(read_32(A0 + 0x34), &A1);      // MOVEA.L	52(A0),A1
  DEF_ROMLOC(1AA80) : move_toreg_8(read_8(A1), &D0); // MOVE.B	(A1),D0
  DEF_ROMLOC(1AA82) : cmp_toreg_8(read_8(A0), &D0);  // CMP.B	(A0),D0
  DEF_ROMLOC(1AA84) : if (!CCR_EQ) {
    rom_1A502();
    return;
  } // BNE.W	$1A502
  DEF_ROMLOC(1AA88)
      : cmp_tomem_32(0x184B8, A1 + 0x4);            // CMPI.L	#$000184B8,4(A1)
  DEF_ROMLOC(1AA90) : if (CCR_EQ) goto rom_1AA9A;   // BEQ.B	$1AA9A
  DEF_ROMLOC(1AA92) : move_tomem_8(0xA, A0 + 0x1A); // MOVE.B	#$0A,26(A0)
  rom_1AA5C();
  return;                                           // BRA.B	$1AA5C
  DEF_ROMLOC(1AA9A) : move_tomem_8(0x1, A0 + 0x1C); // MOVE.B	#$01,28(A0)
  DEF_ROMLOC(1AAA0) : tst_mem_8(A1 + 0x21);         // TST.B	33(A1)
  DEF_ROMLOC(1AAA4) : if (CCR_LE) goto rom_1AAC8;   // BLE.B	$1AAC8
  DEF_ROMLOC(1AAA6) : move_tomem_8(0x6, A0 + 0x1C); // MOVE.B	#$06,28(A0)
  DEF_ROMLOC(1AAAC)
      : move_tomem_32(0x184B8, A0 + 0x4);             // MOVE.L	#$000184B8,4(A0)
  DEF_ROMLOC(1AAB4) : move_tomem_16(0x400, A0 + 0x2); // MOVE.W	#$0400,2(A0)
  DEF_ROMLOC(1AABA) : move_toreg_32(0x18468, &A1);    // LEA.L	-9812(PC),A1
  DEF_ROMLOC(1AABE) : rom_ADA2();                     // JSR	$0000ADA2
  rom_1AA4C();
  return;                                  // BRA.W	$1AA4C
  DEF_ROMLOC(1AAC8) : tst_mem_8(A0 + 0x1); // TST.B	1(A0)
  DEF_ROMLOC(1AACC) : if (CCR_PL) {
    rom_1A502();
    return;
  }                                                 // BPL.W	$1A502
  DEF_ROMLOC(1AAD0) : rom_1800C();                  // BSR.W	$1800C
  DEF_ROMLOC(1AAD4) : move_tomem_8(0x2, A0 + 0x18); // MOVE.B	#$02,24(A0)
  DEF_ROMLOC(1AADA) : move_tomem_8(0x0, A0 + 0x1C); // MOVE.B	#$00,28(A0)
  DEF_ROMLOC(1AAE0)
      : move_tomem_32(0x1AB90, A0 + 0x4);             // MOVE.L	#$0001AB90,4(A0)
  DEF_ROMLOC(1AAE8) : move_tomem_16(0x3A0, A0 + 0x2); // MOVE.W	#$03A0,2(A0)
  DEF_ROMLOC(1AAEE) : move_toreg_32(0x1AB8A, &A1);    // LEA.L	154(PC),A1
  DEF_ROMLOC(1AAF2) : rom_ADA2();                     // JSR	$0000ADA2
  rom_1AA4C();                                        // BRA.W	$1AA4C
}
ROMFUNC(rom_1AAFC) {
  DEF_ROMLOC(1AAFC) : bset_tomem_8(0x0, A0 + 0x22); // BSET.B	#$00,34(A0)
  DEF_ROMLOC(1AB02)
      : move_toreg_32(read_32(A0 + 0x34), &A1); // MOVEA.L	52(A0),A1
  DEF_ROMLOC(1AB06)
      : cmp_tomem_32(0x184B8, A1 + 0x4);          // CMPI.L	#$000184B8,4(A1)
  DEF_ROMLOC(1AB0E) : if (CCR_EQ) goto rom_1AB14; // BEQ.B	$1AB14
  rom_1AA5C();
  return; // BRA.W	$1AA5C
  DEF_ROMLOC(1AB14)
      : move_tomem_16(read_16(A1 + 0x8), A0 + 0x8); // MOVE.W	8(A1),8(A0)
  DEF_ROMLOC(1AB1A)
      : move_tomem_16(read_16(A1 + 0xC), A0 + 0xC);  // MOVE.W	12(A1),12(A0)
  DEF_ROMLOC(1AB20) : tst_mem_8(A0 + 0x1E);          // TST.B	30(A0)
  DEF_ROMLOC(1AB24) : if (!CCR_EQ) goto rom_1AB2C;   // BNE.B	$1AB2C
  DEF_ROMLOC(1AB26) : move_tomem_8(0x14, A0 + 0x1E); // MOVE.B	#$14,30(A0)
  DEF_ROMLOC(1AB2C) : sub_tomem_8(0x1, A0 + 0x1E);   // SUBQ.B	#$01,30(A0)
  DEF_ROMLOC(1AB30) : if (CCR_GT) goto rom_1AB40;    // BGT.B	$1AB40
  DEF_ROMLOC(1AB32) : add_tomem_8(0x1, A0 + 0x1A);   // ADDQ.B	#$01,26(A0)
  DEF_ROMLOC(1AB36) : cmp_tomem_8(0x2, A0 + 0x1A);   // CMPI.B	#$02,26(A0)
  DEF_ROMLOC(1AB3C) : if (CCR_GT) {
    rom_1A502();
    return;
  }                                // BGT.W	$1A502
  DEF_ROMLOC(1AB40) : rom_1AA4C(); // BRA.W	$1AA4C
}
ROMFUNC(rom_1AB44) {
  DEF_ROMLOC(1AB44) : move_tomem_8(0xB, A0 + 0x1A); // MOVE.B	#$0B,26(A0)
  DEF_ROMLOC(1AB4A)
      : move_toreg_16(read_16(0xFFFFD008), &D0); // MOVE.W	$D008,D0
  DEF_ROMLOC(1AB4E)
      : sub_toreg_16(read_16(A0 + 0x8), &D0);     // SUB.W	8(A0),D0
  DEF_ROMLOC(1AB52) : if (CCR_CS) goto rom_1AB5C; // BCS.B	$1AB5C
  DEF_ROMLOC(1AB54) : tst_mem_8(A0 + 0x1);        // TST.B	1(A0)
  DEF_ROMLOC(1AB58) : if (CCR_PL) {
    rom_1A502();
    return;
  } // BPL.W	$1A502
  DEF_ROMLOC(1AB5C) : rom_DC92();
  return; // JMP	$0000DC92
}
ROMFUNC(rom_1AB62) {
  DEF_ROMLOC(1AB62) : move_tomem_8(0x0, A0 + 0x1A); // MOVE.B	#$00,26(A0)
  DEF_ROMLOC(1AB68) : bset_tomem_8(0x0, A0 + 0x22); // BSET.B	#$00,34(A0)
  DEF_ROMLOC(1AB6E)
      : move_toreg_32(read_32(A0 + 0x34), &A1);    // MOVEA.L	52(A0),A1
  DEF_ROMLOC(1AB72) : cmp_tomem_8(0xC, A1 + 0x34); // CMPI.B	#$0C,52(A1)
  DEF_ROMLOC(1AB78) : if (!CCR_EQ) goto rom_1AB86; // BNE.B	$1AB86
  DEF_ROMLOC(1AB7A)
      : cmp_tomem_32(0x184B8, A1 + 0x4); // CMPI.L	#$000184B8,4(A1)
  DEF_ROMLOC(1AB82) : if (CCR_EQ) {
    rom_1A502();
    return;
  } // BEQ.W	$1A502
  DEF_ROMLOC(1AB86) : rom_1AA5C();
  return;                                   // BRA.W	$1AA5C
  DEF_ROMLOC(1AB8A) : or_toreg_8(0x0, &D2); // ORI.B	#$00,D2
  rom_1ABFE();                              // Detected flow into next function
}