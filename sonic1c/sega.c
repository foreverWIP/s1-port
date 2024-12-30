// #define CHECK_STUFF 1
#include "game.h"
#include "opcodes.h"
#include "system.h"


ROMFUNC(rom_396) { rom_2DD2(); }

ROMFUNC(rom_2EAC);
ROMFUNC(rom_2EB6);
ROMFUNC(rom_2DE2);
ROMFUNC(rom_2DD2) {
  SETBYTE(SR, 0x04);
  DEF_ROMLOC(2DD2) : move_toreg_8(0xFFFFFFE4, &D0); // MOVE.B	#$E4,D0
  DEF_ROMLOC(2DD6) : rom_1394();                    // BSR.W	$1394
  DEF_ROMLOC(2DDA) : rom_15D6();                    // BSR.W	$15D6
  DEF_ROMLOC(2DDE) : game_state = rom_2DE2; rom_1E4A(); // BSR.W	$1E4A
}
ROMFUNC(rom_2DE2) {
  DEF_ROMLOC(2DE2) : move_toreg_32(0xC00004, &A6);  // LEA.L	$00C00004,A6
  DEF_ROMLOC(2DE8) : move_tomem_16(0xFFFF8004, A6); // MOVE.W	#$8004,(A6)
  DEF_ROMLOC(2DEC) : move_tomem_16(0xFFFF8230, A6); // MOVE.W	#$8230,(A6)
  DEF_ROMLOC(2DF0) : move_tomem_16(0xFFFF8407, A6); // MOVE.W	#$8407,(A6)
  DEF_ROMLOC(2DF4) : move_tomem_16(0xFFFF8700, A6); // MOVE.W	#$8700,(A6)
  DEF_ROMLOC(2DF8) : move_tomem_16(0xFFFF8B00, A6); // MOVE.W	#$8B00,(A6)
  DEF_ROMLOC(2DFC) : clr_mem_8(0xFFFFF64E);         // CLR.B	$F64E
  DEF_ROMLOC(2E00) : move_tosr_16(0x2700, &SR);     // MOVE.W	#$2700,SR
  DEF_ROMLOC(2E04)
      : move_toreg_16(read_16(0xFFFFF60C), &D0);   // MOVE.W	$F60C,D0
  DEF_ROMLOC(2E08) : and_toreg_8(0xFFFFFFBF, &D0); // ANDI.B	#$BF,D0
  DEF_ROMLOC(2E0C) : move_tomem_16(D0, 0xC00004);  // MOVE.W	D0,$00C00004
  DEF_ROMLOC(2E12) : rom_12C4();                   // BSR.W	$12C4
  DEF_ROMLOC(2E16)
      : move_tomem_32(0x40000000, 0xC00004);      // MOVE.L	#$40000000,$00C00004
  DEF_ROMLOC(2E20) : move_toreg_32(0x1E700, &A0); // LEA.L	$0001E700,A0
  DEF_ROMLOC(2E26) : rom_1438();                  // rom_1438(); // BSR.W	$1438
  DEF_ROMLOC(2E2A) : move_toreg_32(0xFF0000, &A1);   // LEA.L	$00FF0000,A1
  DEF_ROMLOC(2E30) : move_toreg_32(0x1EB70, &A0);    // LEA.L	$0001EB70,A0
  DEF_ROMLOC(2E36) : move_toreg_16(0x0, &D0);        // MOVE.W	#$0000,D0
  DEF_ROMLOC(2E3A) : rom_1716();                     // BSR.W	$1716
  DEF_ROMLOC(2E3E) : move_toreg_32(0xFF0000, &A1);   // LEA.L	$00FF0000,A1
  DEF_ROMLOC(2E44) : move_toreg_32(0x65100003, &D0); // MOVE.L	#$65100003,D0
  DEF_ROMLOC(2E4A) : move_toreg_32(0x17, &D1);       // MOVEQ.L	$17,D1
  DEF_ROMLOC(2E4C) : move_toreg_32(0x7, &D2);        // MOVEQ.L	$07,D2
  DEF_ROMLOC(2E4E) : rom_1418();                     // BSR.W	$1418
  DEF_ROMLOC(2E52) : move_toreg_32(0xFF0180, &A1);   // LEA.L	$00FF0180,A1
  DEF_ROMLOC(2E58) : move_toreg_32(0x40000003, &D0); // MOVE.L	#$40000003,D0
  DEF_ROMLOC(2E5E) : move_toreg_32(0x27, &D1);       // MOVEQ.L	$27,D1
  DEF_ROMLOC(2E60) : move_toreg_32(0x1B, &D2);       // MOVEQ.L	$1B,D2
  DEF_ROMLOC(2E62) : rom_1418();                     // BSR.W	$1418
  DEF_ROMLOC(2E66) : tst_mem_8(0xFFFFFFF8);          // TST.B	$FFF8
  DEF_ROMLOC(2E6A) : if (CCR_MI) goto rom_2E80;      // BMI.B	$2E80
  DEF_ROMLOC(2E6C) : move_toreg_32(0xFF0A40, &A1);   // LEA.L	$00FF0A40,A1
  DEF_ROMLOC(2E72) : move_toreg_32(0x453A0003, &D0); // MOVE.L	#$453A0003,D0
  DEF_ROMLOC(2E78) : move_toreg_32(0x2, &D1);        // MOVEQ.L	$02,D1
  DEF_ROMLOC(2E7A) : move_toreg_32(0x1, &D2);        // MOVEQ.L	$01,D2
  DEF_ROMLOC(2E7C) : rom_1418();                     // BSR.W	$1418
  DEF_ROMLOC(2E80) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(2E82) : rom_2110();                     // BSR.W	$2110
  DEF_ROMLOC(2E86)
      : move_tomem_16(0xFFFFFFF6, 0xFFFFF632);       // MOVE.W	#$FFF6,$F632
  DEF_ROMLOC(2E8C) : move_tomem_16(0x0, 0xFFFFF634); // MOVE.W	#$0000,$F634
  DEF_ROMLOC(2E92) : move_tomem_16(0x0, 0xFFFFF662); // MOVE.W	#$0000,$F662
  DEF_ROMLOC(2E98) : move_tomem_16(0x0, 0xFFFFF660); // MOVE.W	#$0000,$F660
  DEF_ROMLOC(2E9E)
      : move_toreg_16(read_16(0xFFFFF60C), &D0);  // MOVE.W	$F60C,D0
  DEF_ROMLOC(2EA2) : or_toreg_8(0x40, &D0);       // ORI.B	#$40,D0
  DEF_ROMLOC(2EA6) : move_tomem_16(D0, 0xC00004); // MOVE.W	D0,$00C00004
  rom_2EAC();
  game_state = rom_2EB6;
}
ROMFUNC(rom_2EAC) {
  DEF_ROMLOC(2EAC) : move_tomem_8(0x2, 0xFFFFF62A); // MOVE.B	#$02,$F62A
  DEF_ROMLOC(2EB2) : rom_29A0(); // rom_29A0(); // BSR.W	$29A0
}
ROMFUNC(rom_2ECE);
ROMFUNC(rom_2EB6) {
  DEF_ROMLOC(2EB6) : rom_2002(); // BSR.W	$2002
  DEF_ROMLOC(2EBA) : if (!CCR_EQ) {
    rom_2EAC();
    return;
  }                                                  // BNE.B	$2EAC
  DEF_ROMLOC(2EBC) : move_toreg_8(0xFFFFFFE1, &D0);  // MOVE.B	#$E1,D0
  DEF_ROMLOC(2EC0) : rom_1394();                     // BSR.W	$1394
  DEF_ROMLOC(2EC4) : move_tomem_8(0x14, 0xFFFFF62A); // MOVE.B	#$14,$F62A
  DEF_ROMLOC(2ECA) : rom_29A0(); // rom_29A0(); // BSR.W	$29A0
  game_state = rom_2ECE;
}
ROMFUNC(rom_2EDE);
ROMFUNC(rom_2ECE) {
  DEF_ROMLOC(2ECE) : move_tomem_16(0x1E, 0xFFFFF614); // MOVE.W	#$001E,$F614
  rom_2ED4();
  game_state = rom_2EDE;
}
ROMFUNC(rom_2ED4) {
  DEF_ROMLOC(2ED4) : move_tomem_8(0x2, 0xFFFFF62A); // MOVE.B	#$02,$F62A
  DEF_ROMLOC(2EDA) : rom_29A0(); // rom_29A0(); // BSR.W	$29A0
}
ROMFUNC(rom_2EDE) {
  DEF_ROMLOC(2EDE) : tst_mem_16(0xFFFFF614);    // TST.W	$F614
  DEF_ROMLOC(2EE2) : if (CCR_EQ) goto rom_2EEC; // BEQ.B	$2EEC
  DEF_ROMLOC(2EE4)
      : and_tomem_8(0xFFFFFF80, 0xFFFFF605); // ANDI.B	#$80,$F605
  DEF_ROMLOC(2EEA) : if (CCR_EQ) {
    rom_2ED4();
    return;
  } // BEQ.B	$2ED4
  DEF_ROMLOC(2EEC) : SET_GM_TITLE();
  DEF_ROMLOC(2EF2): return; // RTS
}