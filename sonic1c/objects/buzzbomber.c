// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"


ROMFUNC(rom_9E5C) {
  u8 switchindex = 0;
  DEF_ROMLOC(9E5C) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(9E5E) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(9E62)
      : move_toreg_16(read_16(0x9E6A + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(9E66): goto rom_9E6A + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(9E66) : switch (switchindex) {
  case 0:
    rom_9E70();
    break;
  case 1:
    rom_9E9A();
    break;
  case 2:
    rom_9FAA();
    break;
  }
}
ROMFUNC(rom_9E70) {
  DEF_ROMLOC(9E70) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(9E74)
      : move_tomem_32(0xA0B4, A0 + 0x4);             // MOVE.L	#$0000A0B4,4(A0)
  DEF_ROMLOC(9E7C) : move_tomem_16(0x444, A0 + 0x2); // MOVE.W	#$0444,2(A0)
  DEF_ROMLOC(9E82) : move_tomem_8(0x4, A0 + 0x1);    // MOVE.B	#$04,1(A0)
  DEF_ROMLOC(9E88) : move_tomem_8(0x3, A0 + 0x18);   // MOVE.B	#$03,24(A0)
  DEF_ROMLOC(9E8E) : move_tomem_8(0x8, A0 + 0x20);   // MOVE.B	#$08,32(A0)
  DEF_ROMLOC(9E94) : move_tomem_8(0x18, A0 + 0x19);  // MOVE.B	#$18,25(A0)
  rom_9E9A(); // Detected flow into next function
}
ROMFUNC(rom_9EBA);
ROMFUNC(rom_9F50);
ROMFUNC(rom_9E9A) {
  u8 switchindex = 0;
  DEF_ROMLOC(9E9A) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(9E9C) : move_toreg_8(read_8(A0 + 0x25), &D0);
  switchindex = D0 / 2; // MOVE.B	37(A0),D0
  DEF_ROMLOC(9EA0)
      : move_toreg_16(read_16(0x9EB6 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	20(PC,D0),D1
  // DEF_ROMLOC(9EA4): rom_9EB6 + (s16)(D1 & 0xffff)(); // JSR	16(PC,D1)
  DEF_ROMLOC(9EA4) : switch (switchindex) {
  case 0:
    rom_9EBA();
    break;
  case 1:
    rom_9F50();
    break;
  }
  DEF_ROMLOC(9EA8) : move_toreg_32(0xA096, &A1); // LEA.L	$0000A096,A1
  DEF_ROMLOC(9EAE) : animate_sprite();                 // BSR.W	$ADA2
  DEF_ROMLOC(9EB2) : {
    rom_FD38();
    return;
  } // BRA.W	$FD38
}
ROMFUNC(rom_9EBA) {
  DEF_ROMLOC(9EBA) : sub_tomem_16(0x1, A0 + 0x32);    // SUBQ.W	#$01,50(A0)
  DEF_ROMLOC(9EBE) : if (CCR_PL) goto rom_9EEA;       // BPL.B	$9EEA
  DEF_ROMLOC(9EC0) : btst_tomem_8(0x1, A0 + 0x34);    // BTST.B	#$01,52(A0)
  DEF_ROMLOC(9EC6) : if (!CCR_EQ) goto rom_9EEC;      // BNE.B	$9EEC
  DEF_ROMLOC(9EC8) : add_tomem_8(0x2, A0 + 0x25);     // ADDQ.B	#$02,37(A0)
  DEF_ROMLOC(9ECC) : move_tomem_16(0x7F, A0 + 0x32);  // MOVE.W	#$007F,50(A0)
  DEF_ROMLOC(9ED2) : move_tomem_16(0x400, A0 + 0x10); // MOVE.W	#$0400,16(A0)
  DEF_ROMLOC(9ED8) : move_tomem_8(0x1, A0 + 0x1C);    // MOVE.B	#$01,28(A0)
  DEF_ROMLOC(9EDE) : btst_tomem_8(0x0, A0 + 0x22);    // BTST.B	#$00,34(A0)
  DEF_ROMLOC(9EE4) : if (!CCR_EQ) goto rom_9EEA;      // BNE.B	$9EEA
  DEF_ROMLOC(9EE6) : neg_mem_16(A0 + 0x10);           // NEG.W	16(A0)
  DEF_ROMLOC(9EEA) : return;                          // RTS
  DEF_ROMLOC(9EEC) : rom_E11A();                      // BSR.W	$E11A
  DEF_ROMLOC(9EF0) : if (!CCR_EQ) goto rom_9F4E;      // BNE.B	$9F4E
  DEF_ROMLOC(9EF2) : move_tomem_8(0x23, A1 + 0x0);    // MOVE.B	#$23,0(A1)
  DEF_ROMLOC(9EF8)
      : move_tomem_16(read_16(A0 + 0x8), A1 + 0x8); // MOVE.W	8(A0),8(A1)
  DEF_ROMLOC(9EFE)
      : move_tomem_16(read_16(A0 + 0xC), A1 + 0xC);   // MOVE.W	12(A0),12(A1)
  DEF_ROMLOC(9F04) : add_tomem_16(0x1C, A1 + 0xC);    // ADDI.W	#$001C,12(A1)
  DEF_ROMLOC(9F0A) : move_tomem_16(0x200, A1 + 0x12); // MOVE.W	#$0200,18(A1)
  DEF_ROMLOC(9F10) : move_tomem_16(0x200, A1 + 0x10); // MOVE.W	#$0200,16(A1)
  DEF_ROMLOC(9F16) : move_toreg_16(0x18, &D0);        // MOVE.W	#$0018,D0
  DEF_ROMLOC(9F1A) : btst_tomem_8(0x0, A0 + 0x22);    // BTST.B	#$00,34(A0)
  DEF_ROMLOC(9F20) : if (!CCR_EQ) goto rom_9F28;      // BNE.B	$9F28
  DEF_ROMLOC(9F22) : neg_reg_16(&D0);                 // NEG.W	D0
  DEF_ROMLOC(9F24) : neg_mem_16(A1 + 0x10);           // NEG.W	16(A1)
  DEF_ROMLOC(9F28) : add_tomem_16(D0, A1 + 0x8);      // ADD.W	D0,8(A1)
  DEF_ROMLOC(9F2C)
      : move_tomem_8(read_8(A0 + 0x22), A1 + 0x22);  // MOVE.B	34(A0),34(A1)
  DEF_ROMLOC(9F32) : move_tomem_16(0xE, A1 + 0x32);  // MOVE.W	#$000E,50(A1)
  DEF_ROMLOC(9F38) : move_tomem_32(A0, A1 + 0x3C);   // MOVE.L	A0,60(A1)
  DEF_ROMLOC(9F3C) : move_tomem_8(0x1, A0 + 0x34);   // MOVE.B	#$01,52(A0)
  DEF_ROMLOC(9F42) : move_tomem_16(0x3B, A0 + 0x32); // MOVE.W	#$003B,50(A0)
  DEF_ROMLOC(9F48) : move_tomem_8(0x2, A0 + 0x1C);   // MOVE.B	#$02,28(A0)
  DEF_ROMLOC(9F4E) : return;                         // RTS
}
ROMFUNC(rom_9F50) {
  DEF_ROMLOC(9F50) : sub_tomem_16(0x1, A0 + 0x32); // SUBQ.W	#$01,50(A0)
  DEF_ROMLOC(9F54) : if (CCR_MI) goto rom_9F86;    // BMI.B	$9F86
  DEF_ROMLOC(9F56) : rom_DC6C();                   // BSR.W	$DC6C
  DEF_ROMLOC(9F5A) : tst_mem_8(A0 + 0x34);         // TST.B	52(A0)
  DEF_ROMLOC(9F5E) : if (!CCR_EQ) goto rom_9FA8;   // BNE.B	$9FA8
  DEF_ROMLOC(9F60)
      : move_toreg_16(read_16(0xFFFFD008), &D0); // MOVE.W	$D008,D0
  DEF_ROMLOC(9F64)
      : sub_toreg_16(read_16(A0 + 0x8), &D0);        // SUB.W	8(A0),D0
  DEF_ROMLOC(9F68) : if (CCR_PL) goto rom_9F6C;      // BPL.B	$9F6C
  DEF_ROMLOC(9F6A) : neg_reg_16(&D0);                // NEG.W	D0
  DEF_ROMLOC(9F6C) : cmp_toreg_16(0x60, &D0);        // CMPI.W	#$0060,D0
  DEF_ROMLOC(9F70) : if (CCR_CC) goto rom_9FA8;      // BCC.B	$9FA8
  DEF_ROMLOC(9F72) : tst_mem_8(A0 + 0x1);            // TST.B	1(A0)
  DEF_ROMLOC(9F76) : if (CCR_PL) goto rom_9FA8;      // BPL.B	$9FA8
  DEF_ROMLOC(9F78) : move_tomem_8(0x2, A0 + 0x34);   // MOVE.B	#$02,52(A0)
  DEF_ROMLOC(9F7E) : move_tomem_16(0x1D, A0 + 0x32); // MOVE.W	#$001D,50(A0)
  DEF_ROMLOC(9F84) : goto rom_9F98;                  // BRA.B	$9F98
  DEF_ROMLOC(9F86) : move_tomem_8(0x0, A0 + 0x34);   // MOVE.B	#$00,52(A0)
  DEF_ROMLOC(9F8C) : bchg_tomem_8(0x0, A0 + 0x22);   // BCHG.B	#$00,34(A0)
  DEF_ROMLOC(9F92) : move_tomem_16(0x3B, A0 + 0x32); // MOVE.W	#$003B,50(A0)
  DEF_ROMLOC(9F98) : sub_tomem_8(0x2, A0 + 0x25);    // SUBQ.B	#$02,37(A0)
  DEF_ROMLOC(9F9C) : move_tomem_16(0x0, A0 + 0x10);  // MOVE.W	#$0000,16(A0)
  DEF_ROMLOC(9FA2) : move_tomem_8(0x0, A0 + 0x1C);   // MOVE.B	#$00,28(A0)
  DEF_ROMLOC(9FA8) : return;                         // RTS
}
ROMFUNC(rom_9FAA) {
  DEF_ROMLOC(9FAA) : rom_DCCE(); // BSR.W	$DCCE
  DEF_ROMLOC(9FAE) : return;     // RTS
}