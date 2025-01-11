// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

static bool return_early = false;

ROMFUNC(rom_160E4) {
  u8 switchindex = 0;
  DEF_ROMLOC(160E4) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(160E6) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(160EA)
      : move_toreg_16(read_16(0x160F2 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(160EE): goto rom_160F2 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(160EE) : switch (switchindex) {
  case 0:
    rom_160F6();
    break;
  case 1:
    rom_16134();
    break;
  }
}
ROMFUNC(rom_160F6) {
  DEF_ROMLOC(160F6) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(160FA)
      : move_tomem_32(0x16300, A0 + 0x4); // MOVE.L	#$00016300,4(A0)
  DEF_ROMLOC(16102)
      : move_tomem_16(0x43B5, A0 + 0x2);            // MOVE.W
                                                    // #$43B5,2(A0)
  DEF_ROMLOC(16108) : move_tomem_8(0x4, A0 + 0x1);  // MOVE.B	#$04,1(A0)
  DEF_ROMLOC(1610E) : move_tomem_8(0x4, A0 + 0x18); // MOVE.B	#$04,24(A0)
  DEF_ROMLOC(16114)
      : move_tomem_8(0x20, A0 + 0x19); // MOVE.B	#$20,25(A0)
  DEF_ROMLOC(1611A)
      : move_tomem_16(read_16(A0 + 0x8), A0 + 0x3A); // MOVE.W	8(A0),58(A0)
  DEF_ROMLOC(16120)
      : move_tomem_16(read_16(A0 + 0xC), A0 + 0x38); // MOVE.W	12(A0),56(A0)
  DEF_ROMLOC(16126) : cmp_tomem_8(0x3, A0 + 0x28);   // CMPI.B	#$03,40(A0)
  DEF_ROMLOC(1612C) : if (CCR_CC) {
    rom_16134();
    return;
  } // BCC.B	$16134
  DEF_ROMLOC(1612E)
      : move_tomem_8(0xFFFFFFA2, A0 + 0x20); // MOVE.B	#$A2,32(A0)
  rom_16134();                               // Detected flow into next function
}
ROMFUNC(rom_1617A);
ROMFUNC(rom_1617C);
ROMFUNC(rom_161CA);
ROMFUNC(rom_1621A);
ROMFUNC(rom_1628E);
ROMFUNC(rom_16134) {
  u8 switchindex = 0;
  return_early = false;
  DEF_ROMLOC(16134) : move_toreg_32(0x0, &D0);              // MOVEQ.L	$00,D0
  DEF_ROMLOC(16136) : move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B
                                                            // 40(A0),D0
  DEF_ROMLOC(1613A) : and_toreg_16(0x7, &D0);
  switchindex = D0;                          // ANDI.W	#$0007,D0
  DEF_ROMLOC(1613E) : add_toreg_16(D0, &D0); // ADD.W	D0,D0
  DEF_ROMLOC(16140)
      : move_toreg_16(read_16(0x16170 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	46(PC,D0),D1
  // DEF_ROMLOC(16144): rom_16170 + (s16)(D1 & 0xffff)(); // JSR
  // 42(PC,D1)
  DEF_ROMLOC(16144) : switch (switchindex) {
  case 0:
    rom_1617A();
    break;
  case 1:
    rom_1617C();
    break;
  case 2:
    rom_161CA();
    break;
  case 3:
    rom_1621A();
    break;
  case 4:
    rom_1628E();
    break;
  }
  if (return_early)
    return;
  DEF_ROMLOC(16148)
      : move_toreg_16(read_16(A0 + 0x3A), &D0);      // MOVE.W	58(A0),D0
  DEF_ROMLOC(1614C) : and_toreg_16(0xFFFFFF80, &D0); // ANDI.W	#$FF80,D0
  DEF_ROMLOC(16150)
      : move_toreg_16(read_16(0xFFFFF700), &D1);     // MOVE.W	$F700,D1
  DEF_ROMLOC(16154) : sub_toreg_16(0x80, &D1);       // SUBI.W	#$0080,D1
  DEF_ROMLOC(16158) : and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
  DEF_ROMLOC(1615C) : sub_toreg_16(D1, &D0);         // SUB.W	D1,D0
  DEF_ROMLOC(1615E) : cmp_toreg_16(0x280, &D0);      // CMPI.W	#$0280,D0
  DEF_ROMLOC(16162) : if (CCR_HI) goto rom_1616A;    // BHI.B	$1616A
  DEF_ROMLOC(16164) : rom_DC92();
  return; // JMP	$0000DC92
  DEF_ROMLOC(1616A) : rom_DCCE();
  return; // JMP	$0000DCCE
}
ROMFUNC(rom_1617A) {
  DEF_ROMLOC(1617A) : return; // RTS
}
ROMFUNC(rom_1617C) {
  DEF_ROMLOC(1617C) : move_toreg_16(0x60, &D1); // MOVE.W	#$0060,D1
  DEF_ROMLOC(16180) : move_toreg_32(0x0, &D0);  // MOVEQ.L	$00,D0
  DEF_ROMLOC(16182)
      : move_toreg_8(read_8(0xFFFFFE6C), &D0);      // MOVE.B	$FE6C,D0
  DEF_ROMLOC(16186) : btst_tomem_8(0x0, A0 + 0x22); // BTST.B	#$00,34(A0)
  DEF_ROMLOC(1618C) : if (CCR_EQ) goto rom_16192;   // BEQ.B	$16192
  DEF_ROMLOC(1618E) : neg_reg_16(&D0);              // NEG.W	D0
  DEF_ROMLOC(16190) : add_toreg_16(D1, &D0);        // ADD.W	D1,D0
  DEF_ROMLOC(16192)
      : move_toreg_16(read_16(A0 + 0x3A), &D1);     // MOVE.W	58(A0),D1
  DEF_ROMLOC(16196) : sub_toreg_16(D0, &D1);        // SUB.W	D0,D1
  DEF_ROMLOC(16198) : move_tomem_16(D1, A0 + 0x8);  // MOVE.W	D1,8(A0)
  DEF_ROMLOC(1619C) : sub_tomem_8(0x1, A0 + 0x1E);  // SUBQ.B	#$01,30(A0)
  DEF_ROMLOC(161A0) : if (CCR_PL) goto rom_161AE;   // BPL.B	$161AE
  DEF_ROMLOC(161A2) : move_tomem_8(0x2, A0 + 0x1E); // MOVE.B	#$02,30(A0)
  DEF_ROMLOC(161A8) : bchg_tomem_8(0x0, A0 + 0x1A); // BCHG.B	#$00,26(A0)
  DEF_ROMLOC(161AE) : tst_mem_8(A0 + 0x1);          // TST.B	1(A0)
  DEF_ROMLOC(161B2) : if (CCR_PL) goto rom_161C8;   // BPL.B	$161C8
  DEF_ROMLOC(161B4)
      : move_toreg_16(read_16(0xFFFFFE04), &D0);   // MOVE.W	$FE04,D0
  DEF_ROMLOC(161B8) : and_toreg_16(0xF, &D0);      // ANDI.W	#$000F,D0
  DEF_ROMLOC(161BC) : if (!CCR_EQ) goto rom_161C8; // BNE.B	$161C8
  DEF_ROMLOC(161BE) : move_toreg_16(0xB0, &D0);    // MOVE.W	#$00B0,D0
  DEF_ROMLOC(161C2) : play_sound_special();        // JSR	$00001394
  DEF_ROMLOC(161C8) : return;                      // RTS
}
ROMFUNC(rom_161CA) {
  DEF_ROMLOC(161CA) : move_toreg_16(0x30, &D1); // MOVE.W	#$0030,D1
  DEF_ROMLOC(161CE) : move_toreg_32(0x0, &D0);  // MOVEQ.L	$00,D0
  DEF_ROMLOC(161D0)
      : move_toreg_8(read_8(0xFFFFFE64), &D0);      // MOVE.B	$FE64,D0
  DEF_ROMLOC(161D4) : btst_tomem_8(0x0, A0 + 0x22); // BTST.B	#$00,34(A0)
  DEF_ROMLOC(161DA) : if (CCR_EQ) goto rom_161E2;   // BEQ.B	$161E2
  DEF_ROMLOC(161DC) : neg_reg_16(&D0);              // NEG.W	D0
  DEF_ROMLOC(161DE) : add_toreg_16(0x80, &D0);      // ADDI.W	#$0080,D0
  DEF_ROMLOC(161E2)
      : move_toreg_16(read_16(A0 + 0x38), &D1);     // MOVE.W	56(A0),D1
  DEF_ROMLOC(161E6) : sub_toreg_16(D0, &D1);        // SUB.W	D0,D1
  DEF_ROMLOC(161E8) : move_tomem_16(D1, A0 + 0xC);  // MOVE.W	D1,12(A0)
  DEF_ROMLOC(161EC) : sub_tomem_8(0x1, A0 + 0x1E);  // SUBQ.B	#$01,30(A0)
  DEF_ROMLOC(161F0) : if (CCR_PL) goto rom_161FE;   // BPL.B	$161FE
  DEF_ROMLOC(161F2) : move_tomem_8(0x2, A0 + 0x1E); // MOVE.B	#$02,30(A0)
  DEF_ROMLOC(161F8) : bchg_tomem_8(0x0, A0 + 0x1A); // BCHG.B	#$00,26(A0)
  DEF_ROMLOC(161FE) : tst_mem_8(A0 + 0x1);          // TST.B	1(A0)
  DEF_ROMLOC(16202) : if (CCR_PL) goto rom_16218;   // BPL.B	$16218
  DEF_ROMLOC(16204)
      : move_toreg_8(read_8(0xFFFFFE64), &D0);     // MOVE.B	$FE64,D0
  DEF_ROMLOC(16208) : cmp_toreg_8(0x18, &D0);      // CMPI.B	#$18,D0
  DEF_ROMLOC(1620C) : if (!CCR_EQ) goto rom_16218; // BNE.B	$16218
  DEF_ROMLOC(1620E) : move_toreg_16(0xB0, &D0);    // MOVE.W	#$00B0,D0
  DEF_ROMLOC(16212) : play_sound_special();        // JSR	$00001394
  DEF_ROMLOC(16218) : return;                      // RTS
}
ROMFUNC(rom_1621A) {
  DEF_ROMLOC(1621A) : tst_mem_8(A0 + 0x3D);        // TST.B	61(A0)
  DEF_ROMLOC(1621E) : if (!CCR_EQ) goto rom_1626E; // BNE.B	$1626E
  DEF_ROMLOC(16220)
      : move_toreg_16(read_16(0xFFFFD008), &D0);  // MOVE.W	$D008,D0
  DEF_ROMLOC(16224) : sub_toreg_16(0xC0, &D0);    // SUBI.W	#$00C0,D0
  DEF_ROMLOC(16228) : if (CCR_CS) goto rom_1626A; // BCS.B	$1626A
  DEF_ROMLOC(1622A)
      : sub_toreg_16(read_16(A0 + 0x8), &D0);     // SUB.W	8(A0),D0
  DEF_ROMLOC(1622E) : if (CCR_CS) goto rom_1626A; // BCS.B	$1626A
  DEF_ROMLOC(16230)
      : move_toreg_16(read_16(0xFFFFD00C), &D0); // MOVE.W	$D00C,D0
  DEF_ROMLOC(16234) : sub_toreg_16(0x80, &D0);   // SUBI.W	#$0080,D0
  DEF_ROMLOC(16238)
      : cmp_toreg_16(read_16(A0 + 0xC), &D0);               // CMP.W	12(A0),D0
  DEF_ROMLOC(1623C) : if (CCR_CC) goto rom_1626C;           // BCC.B	$1626C
  DEF_ROMLOC(1623E) : add_toreg_16(0x100, &D0);             // ADDI.W	#$0100,D0
  DEF_ROMLOC(16242) : cmp_toreg_16(read_16(A0 + 0xC), &D0); // CMP.W
                                                            // 12(A0),D0
  DEF_ROMLOC(16246) : if (CCR_CS) goto rom_1626C;           // BCS.B	$1626C
  DEF_ROMLOC(16248) : move_tomem_8(0x1, A0 + 0x3D); // MOVE.B	#$01,61(A0)
  DEF_ROMLOC(1624E)
      : move_tomem_16(0x600, A0 + 0x10); // MOVE.W
                                         // #$0600,16(A0)
  DEF_ROMLOC(16254)
      : move_tomem_8(0xFFFFFFA2, A0 + 0x20);        // MOVE.B	#$A2,32(A0)
  DEF_ROMLOC(1625A) : move_tomem_8(0x2, A0 + 0x1A); // MOVE.B	#$02,26(A0)
  DEF_ROMLOC(16260) : move_toreg_16(0xB0, &D0);     // MOVE.W	#$00B0,D0
  DEF_ROMLOC(16264) : play_sound_special();         // JSR	$00001394
  DEF_ROMLOC(1626A) : return_early = true;          // TODO; // ADDQ.L	#$04,A7
  DEF_ROMLOC(1626C) : return;                       // RTS
  DEF_ROMLOC(1626E) : rom_DC6C();                   // JSR	$0000DC6C
  DEF_ROMLOC(16274)
      : move_tomem_16(read_16(A0 + 0x8), A0 + 0x3A); // MOVE.W	8(A0),58(A0)
  DEF_ROMLOC(1627A) : sub_tomem_8(0x1, A0 + 0x1E);   // SUBQ.B	#$01,30(A0)
  DEF_ROMLOC(1627E) : if (CCR_PL) goto rom_1628C;    // BPL.B	$1628C
  DEF_ROMLOC(16280) : move_tomem_8(0x2, A0 + 0x1E);  // MOVE.B	#$02,30(A0)
  DEF_ROMLOC(16286) : bchg_tomem_8(0x0, A0 + 0x1A);  // BCHG.B	#$00,26(A0)
  DEF_ROMLOC(1628C) : return;                        // RTS
}
ROMFUNC(rom_1628E) {
  DEF_ROMLOC(1628E) : tst_mem_8(A0 + 0x3D);        // TST.B	61(A0)
  DEF_ROMLOC(16292) : if (!CCR_EQ) goto rom_162E0; // BNE.B	$162E0
  DEF_ROMLOC(16294)
      : move_toreg_16(read_16(0xFFFFD008), &D0); // MOVE.W	$D008,D0
  DEF_ROMLOC(16298) : add_toreg_16(0xE0, &D0);   // ADDI.W	#$00E0,D0
  DEF_ROMLOC(1629C)
      : sub_toreg_16(read_16(A0 + 0x8), &D0);     // SUB.W	8(A0),D0
  DEF_ROMLOC(162A0) : if (CCR_CC) goto rom_162DC; // BCC.B	$162DC
  DEF_ROMLOC(162A2)
      : move_toreg_16(read_16(0xFFFFD00C), &D0); // MOVE.W	$D00C,D0
  DEF_ROMLOC(162A6) : sub_toreg_16(0x80, &D0);   // SUBI.W	#$0080,D0
  DEF_ROMLOC(162AA)
      : cmp_toreg_16(read_16(A0 + 0xC), &D0);     // CMP.W	12(A0),D0
  DEF_ROMLOC(162AE) : if (CCR_CC) goto rom_162DE; // BCC.B	$162DE
  DEF_ROMLOC(162B0) : add_toreg_16(0x100, &D0);   // ADDI.W	#$0100,D0
  DEF_ROMLOC(162B4)
      : cmp_toreg_16(read_16(A0 + 0xC), &D0);       // CMP.W	12(A0),D0
  DEF_ROMLOC(162B8) : if (CCR_CS) goto rom_162DE;   // BCS.B	$162DE
  DEF_ROMLOC(162BA) : move_tomem_8(0x1, A0 + 0x3D); // MOVE.B	#$01,61(A0)
  DEF_ROMLOC(162C0)
      : move_tomem_16(0xFFFFFA00, A0 + 0x10); // MOVE.W	#$FA00,16(A0)
  DEF_ROMLOC(162C6)
      : move_tomem_8(0xFFFFFFA2, A0 + 0x20);        // MOVE.B	#$A2,32(A0)
  DEF_ROMLOC(162CC) : move_tomem_8(0x2, A0 + 0x1A); // MOVE.B	#$02,26(A0)
  DEF_ROMLOC(162D2) : move_toreg_16(0xB0, &D0);     // MOVE.W	#$00B0,D0
  DEF_ROMLOC(162D6) : play_sound_special();         // JSR	$00001394
  DEF_ROMLOC(162DC) : return_early = true;          // TODO; // ADDQ.L	#$04,A7
  DEF_ROMLOC(162DE) : return;                       // RTS
  DEF_ROMLOC(162E0) : rom_DC6C();                   // JSR	$0000DC6C
  DEF_ROMLOC(162E6)
      : move_tomem_16(read_16(A0 + 0x8), A0 + 0x3A); // MOVE.W	8(A0),58(A0)
  DEF_ROMLOC(162EC) : sub_tomem_8(0x1, A0 + 0x1E);   // SUBQ.B	#$01,30(A0)
  DEF_ROMLOC(162F0) : if (CCR_PL) goto rom_162FE;    // BPL.B	$162FE
  DEF_ROMLOC(162F2) : move_tomem_8(0x2, A0 + 0x1E);  // MOVE.B	#$02,30(A0)
  DEF_ROMLOC(162F8) : bchg_tomem_8(0x0, A0 + 0x1A);  // BCHG.B	#$00,26(A0)
  DEF_ROMLOC(162FE) : return;                        // RTS
}