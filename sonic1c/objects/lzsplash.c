// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"


ROMFUNC(rom_14A58) {
  u8 switchindex = 0;
  DEF_ROMLOC(14A58) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(14A5A) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(14A5E)
      : move_toreg_16(read_16(0x14A66 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(14A62): goto rom_14A66 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(14A62) : switch (switchindex) {
  case 0:
    rom_14A6C();
    break;
  case 1:
    rom_14A96();
    break;
  case 2:
    rom_14AAE();
    break;
  }
}
ROMFUNC(rom_14A6C) {
  DEF_ROMLOC(14A6C) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(14A70)
      : move_tomem_32(0x14D34, A0 + 0x4);            // MOVE.L	#$00014D34,4(A0)
  DEF_ROMLOC(14A78) : or_tomem_8(0x4, A0 + 0x1);     // ORI.B	#$04,1(A0)
  DEF_ROMLOC(14A7E) : move_tomem_8(0x1, A0 + 0x18);  // MOVE.B	#$01,24(A0)
  DEF_ROMLOC(14A84) : move_tomem_8(0x10, A0 + 0x19); // MOVE.B	#$10,25(A0)
  DEF_ROMLOC(14A8A) : move_tomem_16(0x4259, A0 + 0x2); // MOVE.W
                                                       // #$4259,2(A0)
  DEF_ROMLOC(14A90)
      : move_tomem_16(read_16(0xFFFFD008), A0 + 0x8); // MOVE.W	$D008,8(A0)
  rom_14A96(); // Detected flow into next function
}
ROMFUNC(rom_14A96) {
  DEF_ROMLOC(14A96)
      : move_tomem_16(read_16(0xFFFFF646), A0 + 0xC); // MOVE.W	$F646,12(A0)
  DEF_ROMLOC(14A9C) : move_toreg_32(0x14D2C, &A1);    // LEA.L	$00014D2C,A1
  DEF_ROMLOC(14AA2) : rom_ADA2();                     // JSR	$0000ADA2
  DEF_ROMLOC(14AA8) : {
    rom_DC92();
    return;
  } // JMP	$0000DC92
}
ROMFUNC(rom_14AAE) {
  DEF_ROMLOC(14AAE) : {
    rom_DCCE();
    return;
  } // JMP	$0000DCCE
}