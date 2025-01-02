// #define CHECK_STUFF 1
#include "opcodes.h"
#include "system.h"

ROMFUNC(rom_13CC);

ROMFUNC(rom_13A0) {
  DEF_ROMLOC(13A0) : {};                    // NOP
  DEF_ROMLOC(13A2) : tst_mem_8(0xFFFFFE12); // TST.B	$FE12
  DEF_ROMLOC(13A6) : if (CCR_EQ) {
    rom_1402();
    return;
  }                                                  // BEQ.B	$1402
  DEF_ROMLOC(13A8) : tst_mem_16(0xFFFFF63A);         // TST.W	$F63A
  DEF_ROMLOC(13AC) : if (!CCR_EQ) goto rom_13B6;     // BNE.B	$13B6
  DEF_ROMLOC(13AE) : btst_tomem_8(0x7, 0xFFFFF605);  // BTST.B	#$07,$F605
  DEF_ROMLOC(13B4) : if (CCR_EQ) {rom_1408();return;}             // BEQ.B	$1408
  DEF_ROMLOC(13B6) : move_tomem_16(0x1, 0xFFFFF63A); // MOVE.W	#$0001,$F63A
  game_state_pause = game_state;
  DEF_ROMLOC(13BC) : move_tomem_8(0x1, 0xFFFFF003); // MOVE.B	#$01,$F003
  rom_13C2();
}
ROMFUNC(rom_13C2) {
  DEF_ROMLOC(13C2) : move_tomem_8(0x10, 0xFFFFF62A); // MOVE.B	#$10,$F62A
  DEF_ROMLOC(13C8) : rom_29A0(); // rom_29A0(); // BSR.W	$29A0
  game_state = rom_13CC;
}
ROMFUNC(rom_13CC) {
  DEF_ROMLOC(13CC) : tst_mem_8(0xFFFFFFE1);         // TST.B	$FFE1
  DEF_ROMLOC(13D0) : if (CCR_EQ) goto rom_13F4;     // BEQ.B	$13F4
  DEF_ROMLOC(13D2) : btst_tomem_8(0x6, 0xFFFFF605); // BTST.B	#$06,$F605
  DEF_ROMLOC(13D8) : if (CCR_EQ) goto rom_13E4;     // BEQ.B	$13E4
  DEF_ROMLOC(13DA) : SET_GM_TITLE();
  DEF_ROMLOC(13E0) : {};                            // NOP
  goto rom_13FC;                                    // BRA.B	$13FC
  DEF_ROMLOC(13E4) : btst_tomem_8(0x4, 0xFFFFF604); // BTST.B	#$04,$F604
  DEF_ROMLOC(13EA) : if (!CCR_EQ) {
    rom_140A();
    return;
  }                                                 // BNE.B	$140A
  DEF_ROMLOC(13EC) : btst_tomem_8(0x5, 0xFFFFF605); // BTST.B	#$05,$F605
  DEF_ROMLOC(13F2) : if (!CCR_EQ) {
    rom_140A();
    return;
  }                                                 // BNE.B	$140A
  DEF_ROMLOC(13F4) : btst_tomem_8(0x7, 0xFFFFF605); // BTST.B	#$07,$F605
  DEF_ROMLOC(13FA) : if (CCR_EQ) {
    rom_13C2();
    return;
  } // BEQ.B	$13C2
  DEF_ROMLOC(13FC)
      : move_tomem_8(0xFFFFFF80, 0xFFFFF003); // MOVE.B	#$80,$F003
  rom_1402();
}
ROMFUNC(rom_1402) {
  DEF_ROMLOC(1402) : move_tomem_16(0x0, 0xFFFFF63A); // MOVE.W	#$0000,$F63A
  game_state = game_state_pause;
  game_state_pause = NULL;
  rom_1408();
}
ROMFUNC(rom_1408) {
  DEF_ROMLOC(1408) : if (game_state) game_state(); return; // RTS
}
ROMFUNC(rom_140A) {
  DEF_ROMLOC(140A) : move_tomem_16(0x1, 0xFFFFF63A); // MOVE.W	#$0001,$F63A
  DEF_ROMLOC(1410)
      : move_tomem_8(0xFFFFFF80, 0xFFFFF003); // MOVE.B	#$80,$F003
  DEF_ROMLOC(1416) : return;                  // RTS
}