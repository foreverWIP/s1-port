// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_15C4A) {
  u8 switchindex = 0;
  DEF_ROMLOC(15C4A) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(15C4C) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(15C50)
      : move_toreg_16(read_16(0x15C58 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(15C54): goto rom_15C58 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(15C54) : switch (switchindex) {
  case 0:
    rom_15C5C();
    break;
  case 1:
    rom_15CCC();
    break;
  }
}
ROMFUNC(rom_15C5C) {
  DEF_ROMLOC(15C5C) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(15C60)
      : move_tomem_32(0x15DEE, A0 + 0x4); // MOVE.L	#$00015DEE,4(A0)
  DEF_ROMLOC(15C68)
      : move_tomem_16(0xFFFFC344, A0 + 0x2);        // MOVE.W	#$C344,2(A0)
  DEF_ROMLOC(15C6E) : move_tomem_8(0x4, A0 + 0x1);  // MOVE.B	#$04,1(A0)
  DEF_ROMLOC(15C74) : move_tomem_8(0x4, A0 + 0x18); // MOVE.B	#$04,24(A0)
  DEF_ROMLOC(15C7A) : move_tomem_8(0x8, A0 + 0x19); // MOVE.B	#$08,25(A0)
  DEF_ROMLOC(15C80)
      : move_tomem_16(read_16(A0 + 0x8), A0 + 0x32); // MOVE.W	8(A0),50(A0)
  DEF_ROMLOC(15C86)
      : move_tomem_16(read_16(A0 + 0xC), A0 + 0x30); // MOVE.W	12(A0),48(A0)
  DEF_ROMLOC(15C8C) : move_tomem_8(0x18, A0 + 0x34); // MOVE.B	#$18,52(A0)
  DEF_ROMLOC(15C92) : move_tomem_8(0x48, A0 + 0x38); // MOVE.B	#$48,56(A0)
  DEF_ROMLOC(15C98)
      : move_toreg_8(read_8(A0 + 0x28), &D1);        // MOVE.B
                                                     // 40(A0),D1
  DEF_ROMLOC(15C9C) : and_toreg_8(0xF, &D1);         // ANDI.B	#$0F,D1
  DEF_ROMLOC(15CA0) : if (CCR_EQ) goto rom_15CAE;    // BEQ.B	$15CAE
  DEF_ROMLOC(15CA2) : move_tomem_8(0x10, A0 + 0x34); // MOVE.B	#$10,52(A0)
  DEF_ROMLOC(15CA8) : move_tomem_8(0x38, A0 + 0x38); // MOVE.B	#$38,56(A0)
  DEF_ROMLOC(15CAE)
      : move_toreg_8(read_8(A0 + 0x28), &D1);       // MOVE.B	40(A0),D1
  DEF_ROMLOC(15CB2) : and_toreg_8(0xFFFFFFF0, &D1); // ANDI.B	#$F0,D1
  DEF_ROMLOC(15CB6) : ext_reg_16(&D1);              // EXT.W	D1
  DEF_ROMLOC(15CB8) : asl_toreg_16(0x3, &D1);       // ASL.W	#$03,D1
  DEF_ROMLOC(15CBA) : move_tomem_16(D1, A0 + 0x36); // MOVE.W	D1,54(A0)
  DEF_ROMLOC(15CBE)
      : move_toreg_8(read_8(A0 + 0x22), &D0);       // MOVE.B	34(A0),D0
  DEF_ROMLOC(15CC2) : ror_toreg_8(0x2, &D0);        // ROR.B	#$02,D0
  DEF_ROMLOC(15CC4) : and_toreg_8(0xFFFFFFC0, &D0); // ANDI.B	#$C0,D0
  DEF_ROMLOC(15CC8) : move_tomem_8(D0, A0 + 0x26);  // MOVE.B	D0,38(A0)
  rom_15CCC(); // Detected flow into next function
}
ROMFUNC(rom_15CCC) {
  DEF_ROMLOC(15CCC) : rom_15CD8(); // BSR.W	$15CD8
  DEF_ROMLOC(15CD0) : rom_15D8C(); // BSR.W	$15D8C
  rom_15DC6();                     // BRA.W	$15DC6
}
ROMFUNC(rom_15CD8) {
  DEF_ROMLOC(15CD8) : move_toreg_32(0x0, &D2); // MOVEQ.L	$00,D2
  DEF_ROMLOC(15CDA)
      : move_toreg_8(read_8(A0 + 0x38), &D2);         // MOVE.B
                                                      // 56(A0),D2
  DEF_ROMLOC(15CDE) : move_toreg_16(D2, &D3);         // MOVE.W	D2,D3
  DEF_ROMLOC(15CE0) : add_toreg_16(D3, &D3);          // ADD.W	D3,D3
  DEF_ROMLOC(15CE2) : move_toreg_32(0xFFFFD000, &A1); // LEA.L	$D000,A1
  DEF_ROMLOC(15CE6)
      : move_toreg_16(read_16(A1 + 0x8), &D0); // MOVE.W	8(A1),D0
  DEF_ROMLOC(15CEA)
      : sub_toreg_16(read_16(A0 + 0x32), &D0);    // SUB.W	50(A0),D0
  DEF_ROMLOC(15CEE) : add_toreg_16(D2, &D0);      // ADD.W	D2,D0
  DEF_ROMLOC(15CF0) : cmp_toreg_16(D3, &D0);      // CMP.W	D3,D0
  DEF_ROMLOC(15CF2) : if (CCR_CC) goto rom_15D10; // BCC.B	$15D10
  DEF_ROMLOC(15CF4)
      : move_toreg_16(read_16(A1 + 0xC), &D1); // MOVE.W	12(A1),D1
  DEF_ROMLOC(15CF8)
      : sub_toreg_16(read_16(A0 + 0x30), &D1);      // SUB.W	48(A0),D1
  DEF_ROMLOC(15CFC) : add_toreg_16(D2, &D1);        // ADD.W	D2,D1
  DEF_ROMLOC(15CFE) : cmp_toreg_16(D3, &D1);        // CMP.W	D3,D1
  DEF_ROMLOC(15D00) : if (CCR_CC) goto rom_15D10;   // BCC.B	$15D10
  DEF_ROMLOC(15D02) : btst_tomem_8(0x1, A1 + 0x22); // BTST.B	#$01,34(A1)
  DEF_ROMLOC(15D08) : if (CCR_EQ) goto rom_15D20;   // BEQ.B	$15D20
  DEF_ROMLOC(15D0A) : clr_mem_8(A0 + 0x3A);         // CLR.B	58(A0)
  DEF_ROMLOC(15D0E) : return;                       // RTS
  DEF_ROMLOC(15D10) : tst_mem_8(A0 + 0x3A);         // TST.B	58(A0)
  DEF_ROMLOC(15D14) : if (CCR_EQ) goto rom_15D1E;   // BEQ.B	$15D1E
  DEF_ROMLOC(15D16) : clr_mem_8(A1 + 0x38);         // CLR.B	56(A1)
  DEF_ROMLOC(15D1A) : clr_mem_8(A0 + 0x3A);         // CLR.B	58(A0)
  DEF_ROMLOC(15D1E) : return;                       // RTS
  DEF_ROMLOC(15D20) : tst_mem_8(A0 + 0x3A);         // TST.B	58(A0)
  DEF_ROMLOC(15D24) : if (!CCR_EQ) goto rom_15D4A;  // BNE.B	$15D4A
  DEF_ROMLOC(15D26) : move_tomem_8(0x1, A0 + 0x3A); // MOVE.B	#$01,58(A0)
  DEF_ROMLOC(15D2C) : btst_tomem_8(0x2, A1 + 0x22); // BTST.B	#$02,34(A1)
  DEF_ROMLOC(15D32) : if (!CCR_EQ) goto rom_15D38;  // BNE.B	$15D38
  DEF_ROMLOC(15D34) : clr_mem_8(A1 + 0x1C);         // CLR.B	28(A1)
  DEF_ROMLOC(15D38) : bclr_tomem_8(0x5, A1 + 0x22); // BCLR.B	#$05,34(A1)
  DEF_ROMLOC(15D3E) : move_tomem_8(0x1, A1 + 0x1D); // MOVE.B	#$01,29(A1)
  DEF_ROMLOC(15D44) : move_tomem_8(0x1, A1 + 0x38); // MOVE.B	#$01,56(A1)
  DEF_ROMLOC(15D4A)
      : move_toreg_16(read_16(A1 + 0x14), &D0);      // MOVE.W	20(A1),D0
  DEF_ROMLOC(15D4E) : tst_mem_16(A0 + 0x36);         // TST.W	54(A0)
  DEF_ROMLOC(15D52) : if (CCR_PL) goto rom_15D70;    // BPL.B	$15D70
  DEF_ROMLOC(15D54) : cmp_toreg_16(0xFFFFFC00, &D0); // CMPI.W	#$FC00,D0
  DEF_ROMLOC(15D58) : if (CCR_LE) goto rom_15D62;    // BLE.B	$15D62
  DEF_ROMLOC(15D5A)
      : move_tomem_16(0xFFFFFC00, A1 + 0x14);        // MOVE.W	#$FC00,20(A1)
  DEF_ROMLOC(15D60) : return;                        // RTS
  DEF_ROMLOC(15D62) : cmp_toreg_16(0xFFFFF100, &D0); // CMPI.W	#$F100,D0
  DEF_ROMLOC(15D66) : if (CCR_GE) goto rom_15D6E;    // BGE.B	$15D6E
  DEF_ROMLOC(15D68)
      : move_tomem_16(0xFFFFF100, A1 + 0x14);     // MOVE.W	#$F100,20(A1)
  DEF_ROMLOC(15D6E) : return;                     // RTS
  DEF_ROMLOC(15D70) : cmp_toreg_16(0x400, &D0);   // CMPI.W	#$0400,D0
  DEF_ROMLOC(15D74) : if (CCR_GE) goto rom_15D7E; // BGE.B	$15D7E
  DEF_ROMLOC(15D76)
      : move_tomem_16(0x400, A1 + 0x14);          // MOVE.W
                                                  // #$0400,20(A1)
  DEF_ROMLOC(15D7C) : return;                     // RTS
  DEF_ROMLOC(15D7E) : cmp_toreg_16(0xF00, &D0);   // CMPI.W	#$0F00,D0
  DEF_ROMLOC(15D82) : if (CCR_LE) goto rom_15D8A; // BLE.B	$15D8A
  DEF_ROMLOC(15D84)
      : move_tomem_16(0xF00, A1 + 0x14); // MOVE.W
                                         // #$0F00,20(A1)
  DEF_ROMLOC(15D8A) : return;            // RTS
}
ROMFUNC(rom_15D8C) {
  DEF_ROMLOC(15D8C)
      : move_toreg_16(read_16(A0 + 0x36), &D0);    // MOVE.W	54(A0),D0
  DEF_ROMLOC(15D90) : add_tomem_16(D0, A0 + 0x26); // ADD.W	D0,38(A0)
  DEF_ROMLOC(15D94)
      : move_toreg_8(read_8(A0 + 0x26), &D0); // MOVE.B
                                              // 38(A0),D0
  DEF_ROMLOC(15D98) : rom_29D2();             // JSR	$000029D2
  DEF_ROMLOC(15D9E)
      : move_toreg_16(read_16(A0 + 0x30), &D2); // MOVE.W	48(A0),D2
  DEF_ROMLOC(15DA2)
      : move_toreg_16(read_16(A0 + 0x32), &D3); // MOVE.W	50(A0),D3
  DEF_ROMLOC(15DA6) : move_toreg_32(0x0, &D4);  // MOVEQ.L	$00,D4
  DEF_ROMLOC(15DA8)
      : move_toreg_8(read_8(A0 + 0x34), &D4);      // MOVE.B	52(A0),D4
  DEF_ROMLOC(15DAC) : lsl_toreg_16(0x8, &D4);      // LSL.W	#$08,D4
  DEF_ROMLOC(15DAE) : move_toreg_32(D4, &D5);      // MOVE.L	D4,D5
  DEF_ROMLOC(15DB0) : muls_toreg_16(D0, &D4);      // MULS.W	D0,D4
  DEF_ROMLOC(15DB2) : SWAPWORDS(D4);               // SWAP.W	D4
  DEF_ROMLOC(15DB4) : muls_toreg_16(D1, &D5);      // MULS.W	D1,D5
  DEF_ROMLOC(15DB6) : SWAPWORDS(D5);               // SWAP.W	D5
  DEF_ROMLOC(15DB8) : add_toreg_16(D2, &D4);       // ADD.W	D2,D4
  DEF_ROMLOC(15DBA) : add_toreg_16(D3, &D5);       // ADD.W	D3,D5
  DEF_ROMLOC(15DBC) : move_tomem_16(D4, A0 + 0xC); // MOVE.W	D4,12(A0)
  DEF_ROMLOC(15DC0) : move_tomem_16(D5, A0 + 0x8); // MOVE.W	D5,8(A0)
  DEF_ROMLOC(15DC4) : return;                      // RTS
}
ROMFUNC(rom_15DC6) {
  DEF_ROMLOC(15DC6)
      : move_toreg_16(read_16(A0 + 0x32), &D0);      // MOVE.W	50(A0),D0
  DEF_ROMLOC(15DCA) : and_toreg_16(0xFFFFFF80, &D0); // ANDI.W	#$FF80,D0
  DEF_ROMLOC(15DCE)
      : move_toreg_16(read_16(v_screenposx), &D1);   // MOVE.W	$F700,D1
  DEF_ROMLOC(15DD2) : sub_toreg_16(0x80, &D1);       // SUBI.W	#$0080,D1
  DEF_ROMLOC(15DD6) : and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
  DEF_ROMLOC(15DDA) : sub_toreg_16(D1, &D0);         // SUB.W	D1,D0
  DEF_ROMLOC(15DDC)
      : cmp_toreg_16(128 + GAME_WIDTH + 192, &D0); // CMPI.W	#$0280,D0
  DEF_ROMLOC(15DE0) : if (CCR_HI) goto rom_15DE8;  // BHI.B	$15DE8
  DEF_ROMLOC(15DE2) : {
    queue_sprite();
    return;
  } // JMP	$0000DC92
  DEF_ROMLOC(15DE8) : {
    rom_DCCE();
    return;
  } // JMP	$0000DCCE
}