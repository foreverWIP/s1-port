// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_E862) {
  u8 switchindex = 0;
  DEF_ROMLOC(E862) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(E864) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(E868)
      : move_toreg_16(read_16(0xE870 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(E86C): goto rom_E870 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(E86C) : switch (switchindex) {
  case 0:
    rom_E876();
    break;
  case 1:
    rom_E8AE();
    break;
  case 2:
    rom_E8BA();
    break;
  }
}
ROMFUNC(rom_E876) {
  DEF_ROMLOC(E876) : add_tomem_8(0x2, A0 + 0x24);     // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(E87A) : move_tomem_32(0xE8DE, A0 + 0x4); // MOVE.L	#$0000E8DE,4(A0)
  DEF_ROMLOC(E882) : move_tomem_16(0x434C, A0 + 0x2); // MOVE.W	#$434C,2(A0)
  DEF_ROMLOC(E888) : or_tomem_8(0x4, A0 + 0x1);       // ORI.B	#$04,1(A0)
  DEF_ROMLOC(E88E) : move_tomem_8(0x8, A0 + 0x19);    // MOVE.B	#$08,25(A0)
  DEF_ROMLOC(E894) : move_tomem_8(0x6, A0 + 0x18);    // MOVE.B	#$06,24(A0)
  DEF_ROMLOC(E89A)
      : move_tomem_8(read_8(A0 + 0x28), A0 + 0x1A); // MOVE.B	40(A0),26(A0)
  DEF_ROMLOC(E8A0) : bclr_tomem_8(0x4, A0 + 0x1A);  // BCLR.B	#$04,26(A0)
  DEF_ROMLOC(E8A6) : if (CCR_EQ) {
    rom_E8AE();
    return;
  } // BEQ.B	$E8AE
  DEF_ROMLOC(E8A8) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  rom_E8BA();                                     // BRA.B	$E8BA
}
ROMFUNC(rom_E8AE) {
  DEF_ROMLOC(E8AE) : move_toreg_16(0x13, &D1); // MOVE.W	#$0013,D1
  DEF_ROMLOC(E8B2) : move_toreg_16(0x28, &D2); // MOVE.W	#$0028,D2
  DEF_ROMLOC(E8B6) : rom_90E0();               // BSR.W	$90E0
  rom_E8BA(); // Detected flow into next function
}
ROMFUNC(rom_E8BA) {
  DEF_ROMLOC(E8BA) : rom_DC92();                            // BSR.W	$DC92
  DEF_ROMLOC(E8BE) : move_toreg_16(read_16(A0 + 0x8), &D0); // MOVE.W	8(A0),D0
  DEF_ROMLOC(E8C2) : and_toreg_16(0xFFFFFF80, &D0);         // ANDI.W	#$FF80,D0
  DEF_ROMLOC(E8C6)
      : move_toreg_16(read_16(v_screenposx), &D1);  // MOVE.W	$F700,D1
  DEF_ROMLOC(E8CA) : sub_toreg_16(0x80, &D1);       // SUBI.W	#$0080,D1
  DEF_ROMLOC(E8CE) : and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
  DEF_ROMLOC(E8D2) : sub_toreg_16(D1, &D0);         // SUB.W	D1,D0
  DEF_ROMLOC(E8D4)
      : cmp_toreg_16(128 + GAME_WIDTH + 192, &D0); // CMPI.W	#$0280,D0
  DEF_ROMLOC(E8D8) : if (CCR_HI) {
    rom_DCCE();
    return;
  } // BHI.W	$DCCE
  DEF_ROMLOC(E8DC) : return; // RTS
}