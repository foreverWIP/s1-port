// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"


ROMFUNC(rom_9A90) {
  u8 switchindex = 0;
  DEF_ROMLOC(9A90) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(9A92) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(9A96)
      : move_toreg_16(read_16(0x9AA2 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	10(PC,D0),D1
  // DEF_ROMLOC(9A9A): rom_9AA2 + (s16)(D1 & 0xffff)(); // JSR	6(PC,D1)
  DEF_ROMLOC(9A9A) : switch (switchindex) {
  case 0:
    rom_9AA6();
    break;
  case 1:
    rom_9AD0();
    break;
  }
  DEF_ROMLOC(9A9E) : {
    rom_DC92();
    return;
  } // BRA.W	$DC92
}
ROMFUNC(rom_9AA6) {
  DEF_ROMLOC(9AA6) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(9AAA)
      : move_tomem_32(0x9B2C, A0 + 0x4);              // MOVE.L	#$00009B2C,4(A0)
  DEF_ROMLOC(9AB2) : move_tomem_16(0x2797, A0 + 0x2); // MOVE.W	#$2797,2(A0)
  DEF_ROMLOC(9AB8) : move_tomem_8(0x4, A0 + 0x1);     // MOVE.B	#$04,1(A0)
  DEF_ROMLOC(9ABE) : move_tomem_8(0x1, A0 + 0x18);    // MOVE.B	#$01,24(A0)
  DEF_ROMLOC(9AC4) : move_tomem_8(0x8, A0 + 0x19);    // MOVE.B	#$08,25(A0)
  DEF_ROMLOC(9ACA)
      : move_tomem_16(0xFFFFFD00, A0 + 0x12); // MOVE.W	#$FD00,18(A0)
  rom_9AD0(); // Detected flow into next function
}
ROMFUNC(rom_9AD0) {
  DEF_ROMLOC(9AD0) : tst_mem_16(A0 + 0x12); // TST.W	18(A0)
  DEF_ROMLOC(9AD4) : if (CCR_PL) {
    rom_DCCE();
    return;
  }                                                 // BPL.W	$DCCE
  DEF_ROMLOC(9AD8) : rom_DC6C();                    // BSR.W	$DC6C
  DEF_ROMLOC(9ADC) : add_tomem_16(0x18, A0 + 0x12); // ADDI.W	#$0018,18(A0)
  DEF_ROMLOC(9AE2) : return;                        // RTS
}