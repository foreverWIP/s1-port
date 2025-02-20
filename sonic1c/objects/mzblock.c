// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_EE5E) {
  u8 switchindex = 0;
  DEF_ROMLOC(EE5E) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(EE60) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(EE64)
      : move_toreg_16(read_16(0xEE6C + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(EE68): goto rom_EE6C + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(EE68) : switch (switchindex) {
  case 0:
    rom_EE70();
    break;
  case 1:
    rom_EEAC();
    break;
  }
}
ROMFUNC(rom_EE70) {
  DEF_ROMLOC(EE70) : add_tomem_8(0x2, A0 + 0x24);     // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(EE74) : move_tomem_8(0xF, A0 + 0x16);    // MOVE.B	#$0F,22(A0)
  DEF_ROMLOC(EE7A) : move_tomem_8(0xF, A0 + 0x17);    // MOVE.B	#$0F,23(A0)
  DEF_ROMLOC(EE80) : move_tomem_32(0xEF90, A0 + 0x4); // MOVE.L	#$0000EF90,4(A0)
  DEF_ROMLOC(EE88) : move_tomem_16(0x4000, A0 + 0x2); // MOVE.W	#$4000,2(A0)
  DEF_ROMLOC(EE8E) : move_tomem_8(0x4, A0 + 0x1);     // MOVE.B	#$04,1(A0)
  DEF_ROMLOC(EE94) : move_tomem_8(0x3, A0 + 0x18);    // MOVE.B	#$03,24(A0)
  DEF_ROMLOC(EE9A) : move_tomem_8(0x10, A0 + 0x19);   // MOVE.B	#$10,25(A0)
  DEF_ROMLOC(EEA0)
      : move_tomem_16(read_16(A0 + 0xC), A0 + 0x30);  // MOVE.W	12(A0),48(A0)
  DEF_ROMLOC(EEA6) : move_tomem_16(0x5C0, A0 + 0x32); // MOVE.W	#$05C0,50(A0)
  rom_EEAC(); // Detected flow into next function
}
ROMFUNC(rom_EEAC) {
  u8 switchindex = 0;
  DEF_ROMLOC(EEAC) : tst_mem_8(A0 + 0x1);                  // TST.B	1(A0)
  DEF_ROMLOC(EEB0) : if (CCR_PL) goto rom_EEDA;            // BPL.B	$EEDA
  DEF_ROMLOC(EEB2) : move_toreg_32(0x0, &D0);              // MOVEQ.L	$00,D0
  DEF_ROMLOC(EEB4) : move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B
                                                           // 40(A0),D0
  DEF_ROMLOC(EEB8) : and_toreg_16(0x7, &D0);
  switchindex = D0;                         // ANDI.W	#$0007,D0
  DEF_ROMLOC(EEBC) : add_toreg_16(D0, &D0); // ADD.W	D0,D0
  DEF_ROMLOC(EEBE)
      : move_toreg_16(read_16(0xEEFC + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	60(PC,D0),D1
  // DEF_ROMLOC(EEC2): rom_EEFC + (s16)(D1 & 0xffff)(); // JSR	56(PC,D1)
  DEF_ROMLOC(EEC2) : switch (switchindex) {
  case 0:
    rom_EF06();
    break;
  case 1:
    rom_EF20();
    break;
  case 2:
    rom_EF08();
    break;
  case 3:
    rom_EF40();
    break;
  case 4:
    rom_EF7C();
    break;
  }
  DEF_ROMLOC(EEC6) : move_toreg_16(0x1B, &D1); // MOVE.W	#$001B,D1
  DEF_ROMLOC(EECA) : move_toreg_16(0x10, &D2); // MOVE.W	#$0010,D2
  DEF_ROMLOC(EECE) : move_toreg_16(0x11, &D3); // MOVE.W	#$0011,D3
  DEF_ROMLOC(EED2)
      : move_toreg_16(read_16(A0 + 0x8), &D4);              // MOVE.W	8(A0),D4
  DEF_ROMLOC(EED6) : rom_10062();                           // BSR.W	$10062
  DEF_ROMLOC(EEDA) : move_toreg_16(read_16(A0 + 0x8), &D0); // MOVE.W	8(A0),D0
  DEF_ROMLOC(EEDE) : and_toreg_16(0xFFFFFF80, &D0);         // ANDI.W	#$FF80,D0
  DEF_ROMLOC(EEE2)
      : move_toreg_16(read_16(v_screenposx), &D1);  // MOVE.W	$F700,D1
  DEF_ROMLOC(EEE6) : sub_toreg_16(0x80, &D1);       // SUBI.W	#$0080,D1
  DEF_ROMLOC(EEEA) : and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
  DEF_ROMLOC(EEEE) : sub_toreg_16(D1, &D0);         // SUB.W	D1,D0
  DEF_ROMLOC(EEF0) : cmp_toreg_16(0x280, &D0);      // CMPI.W	#$0280,D0
  DEF_ROMLOC(EEF4) : if (CCR_HI) {
    rom_DCCE();
    return;
  } // BHI.W	$DCCE
  rom_DC92(); // BRA.W	$DC92
}
ROMFUNC(rom_EF06) {
  DEF_ROMLOC(EF06) : return; // RTS
}
ROMFUNC(rom_EF08) {
  DEF_ROMLOC(EF08)
      : move_toreg_16(read_16(0xFFFFD008), &D0); // MOVE.W	$D008,D0
  DEF_ROMLOC(EF0C)
      : sub_toreg_16(read_16(A0 + 0x8), &D0);   // SUB.W	8(A0),D0
  DEF_ROMLOC(EF10) : if (CCR_CC) goto rom_EF14; // BCC.B	$EF14
  DEF_ROMLOC(EF12) : neg_reg_16(&D0);           // NEG.W	D0
  DEF_ROMLOC(EF14) : cmp_toreg_16(0x90, &D0);   // CMPI.W	#$0090,D0
  DEF_ROMLOC(EF18) : if (CCR_CC) {
    rom_EF20();
    return;
  } // BCC.B	$EF20
  DEF_ROMLOC(EF1A) : move_tomem_8(0x3, A0 + 0x28); // MOVE.B	#$03,40(A0)
  rom_EF20(); // Detected flow into next function
}
ROMFUNC(rom_EF20) {
  DEF_ROMLOC(EF20) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(EF22)
      : move_toreg_8(read_8(0xFFFFFE74), &D0);     // MOVE.B	$FE74,D0
  DEF_ROMLOC(EF26) : btst_tomem_8(0x3, A0 + 0x28); // BTST.B	#$03,40(A0)
  DEF_ROMLOC(EF2C) : if (CCR_EQ) goto rom_EF34;    // BEQ.B	$EF34
  DEF_ROMLOC(EF2E) : neg_reg_16(&D0);              // NEG.W	D0
  DEF_ROMLOC(EF30) : add_toreg_16(0x10, &D0);      // ADDI.W	#$0010,D0
  DEF_ROMLOC(EF34)
      : move_toreg_16(read_16(A0 + 0x30), &D1);   // MOVE.W	48(A0),D1
  DEF_ROMLOC(EF38) : sub_toreg_16(D0, &D1);       // SUB.W	D0,D1
  DEF_ROMLOC(EF3A) : move_tomem_16(D1, A0 + 0xC); // MOVE.W	D1,12(A0)
  DEF_ROMLOC(EF3E) : return;                      // RTS
}
ROMFUNC(rom_EF40) {
  DEF_ROMLOC(EF40) : rom_DC6C();                    // BSR.W	$DC6C
  DEF_ROMLOC(EF44) : add_tomem_16(0x18, A0 + 0x12); // ADDI.W	#$0018,18(A0)
  DEF_ROMLOC(EF4A) : rom_15580();                   // BSR.W	$15580
  DEF_ROMLOC(EF4E) : tst_reg_16(&D1);               // TST.W	D1
  DEF_ROMLOC(EF50) : if (CCR_PL) goto rom_EF7A;     // BPL.W	$EF7A
  DEF_ROMLOC(EF54) : add_tomem_16(D1, A0 + 0xC);    // ADD.W	D1,12(A0)
  DEF_ROMLOC(EF58) : clr_mem_16(A0 + 0x12);         // CLR.W	18(A0)
  DEF_ROMLOC(EF5C)
      : move_tomem_16(read_16(A0 + 0xC), A0 + 0x30);  // MOVE.W	12(A0),48(A0)
  DEF_ROMLOC(EF62) : move_tomem_8(0x4, A0 + 0x28);    // MOVE.B	#$04,40(A0)
  DEF_ROMLOC(EF68) : move_toreg_16(read_16(A1), &D0); // MOVE.W	(A1),D0
  DEF_ROMLOC(EF6A) : and_toreg_16(0x3FF, &D0);        // ANDI.W	#$03FF,D0
  DEF_ROMLOC(EF6E) : cmp_toreg_16(0x16A, &D0);        // CMPI.W	#$016A,D0
  DEF_ROMLOC(EF72) : if (CCR_CC) goto rom_EF7A;       // BCC.B	$EF7A
  DEF_ROMLOC(EF74) : move_tomem_8(0x0, A0 + 0x28);    // MOVE.B	#$00,40(A0)
  DEF_ROMLOC(EF7A) : return;                          // RTS
}
ROMFUNC(rom_EF7C) {
  DEF_ROMLOC(EF7C) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(EF7E)
      : move_toreg_8(read_8(0xFFFFFE70), &D0); // MOVE.B	$FE70,D0
  DEF_ROMLOC(EF82) : lsr_toreg_16(0x3, &D0);   // LSR.W	#$03,D0
  DEF_ROMLOC(EF84)
      : move_toreg_16(read_16(A0 + 0x30), &D1);   // MOVE.W	48(A0),D1
  DEF_ROMLOC(EF88) : sub_toreg_16(D0, &D1);       // SUB.W	D0,D1
  DEF_ROMLOC(EF8A) : move_tomem_16(D1, A0 + 0xC); // MOVE.W	D1,12(A0)
  DEF_ROMLOC(EF8E) : return;                      // RTS
}