// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_D6DE) {
  u8 switchindex = 0;
  DEF_ROMLOC(D6DE) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(D6E0) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(D6E4)
      : move_toreg_16(read_16(0xD6EC + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(D6E8): goto rom_D6EC + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(D6E8) : switch (switchindex) {
  case 0:
    rom_D6F0();
    break;
  case 1:
    rom_D714();
    break;
  }
}
ROMFUNC(rom_D6F0) {
  DEF_ROMLOC(D6F0) : add_tomem_8(0x2, A0 + 0x24);     // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(D6F4) : move_tomem_32(0xD79C, A0 + 0x4); // MOVE.L	#$0000D79C,4(A0)
  DEF_ROMLOC(D6FC) : move_tomem_16(0x63D0, A0 + 0x2); // MOVE.W	#$63D0,2(A0)
  DEF_ROMLOC(D702) : move_tomem_8(0x4, A0 + 0x1);     // MOVE.B	#$04,1(A0)
  DEF_ROMLOC(D708) : move_tomem_8(0x13, A0 + 0x19);   // MOVE.B	#$13,25(A0)
  DEF_ROMLOC(D70E) : move_tomem_8(0x4, A0 + 0x18);    // MOVE.B	#$04,24(A0)
  rom_D714(); // Detected flow into next function
}
ROMFUNC(rom_D714) {
  DEF_ROMLOC(D714) : move_toreg_16(0x1B, &D1);              // MOVE.W	#$001B,D1
  DEF_ROMLOC(D718) : move_toreg_16(0x10, &D2);              // MOVE.W	#$0010,D2
  DEF_ROMLOC(D71C) : move_toreg_16(0x10, &D3);              // MOVE.W	#$0010,D3
  DEF_ROMLOC(D720) : move_toreg_16(read_16(A0 + 0x8), &D4); // MOVE.W	8(A0),D4
  DEF_ROMLOC(D724) : rom_10062();                           // BSR.W	$10062
  DEF_ROMLOC(D728) : rom_DC92();                            // BSR.W	$DC92
  DEF_ROMLOC(D72C) : move_toreg_16(read_16(A0 + 0x8), &D0); // MOVE.W	8(A0),D0
  DEF_ROMLOC(D730) : and_toreg_16(0xFFFFFF80, &D0);         // ANDI.W	#$FF80,D0
  DEF_ROMLOC(D734)
      : move_toreg_16(read_16(v_screenposx), &D1);  // MOVE.W	$F700,D1
  DEF_ROMLOC(D738) : sub_toreg_16(0x80, &D1);       // SUBI.W	#$0080,D1
  DEF_ROMLOC(D73C) : and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
  DEF_ROMLOC(D740) : sub_toreg_16(D1, &D0);         // SUB.W	D1,D0
  DEF_ROMLOC(D742)
      : cmp_toreg_16(128 + GAME_WIDTH + 192, &D0); // CMPI.W	#$0280,D0
  DEF_ROMLOC(D746) : if (CCR_HI) {
    rom_DCCE();
    return;
  } // BHI.W	$DCCE
  DEF_ROMLOC(D74A) : return; // RTS
}