// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_9370) {
  u8 switchindex = 0;
  DEF_ROMLOC(9370) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(9372) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(9376)
      : move_toreg_16(read_16(0x937E + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(937A): goto rom_937E + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(937A) : switch (switchindex) {
  case 0:
    rom_9382();
    break;
  case 1:
    rom_93C2();
    break;
  }
}
ROMFUNC(rom_9382) {
  DEF_ROMLOC(9382) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(9386)
      : move_tomem_32(0x9524, A0 + 0x4);             // MOVE.L	#$00009524,4(A0)
  DEF_ROMLOC(938E) : move_tomem_16(0x41C, A0 + 0x2); // MOVE.W	#$041C,2(A0)
  DEF_ROMLOC(9394) : move_tomem_8(0x4, A0 + 0x1);    // MOVE.B	#$04,1(A0)
  DEF_ROMLOC(939A) : move_tomem_8(0x1, A0 + 0x18);   // MOVE.B	#$01,24(A0)
  DEF_ROMLOC(93A0) : move_tomem_8(0x0, A0 + 0x20);   // MOVE.B	#$00,32(A0)
  DEF_ROMLOC(93A6) : move_tomem_8(0xC, A0 + 0x19);   // MOVE.B	#$0C,25(A0)
  DEF_ROMLOC(93AC) : move_tomem_8(0x9, A0 + 0x1E);   // MOVE.B	#$09,30(A0)
  DEF_ROMLOC(93B2) : move_tomem_8(0x0, A0 + 0x1A);   // MOVE.B	#$00,26(A0)
  DEF_ROMLOC(93B8) : move_toreg_16(SFX_A5, &D0);       // MOVE.W	#$00A5,D0
  DEF_ROMLOC(93BC) : play_sound_special();           // JSR	$00001394
  rom_93C2(); // Detected flow into next function
}
ROMFUNC(rom_93C2) {
  DEF_ROMLOC(93C2) : sub_tomem_8(0x1, A0 + 0x1E);  // SUBQ.B	#$01,30(A0)
  DEF_ROMLOC(93C6) : if (CCR_PL) goto rom_93DC;    // BPL.B	$93DC
  DEF_ROMLOC(93C8) : move_tomem_8(0x9, A0 + 0x1E); // MOVE.B	#$09,30(A0)
  DEF_ROMLOC(93CE) : add_tomem_8(0x1, A0 + 0x1A);  // ADDQ.B	#$01,26(A0)
  DEF_ROMLOC(93D2) : cmp_tomem_8(0x4, A0 + 0x1A);  // CMPI.B	#$04,26(A0)
  DEF_ROMLOC(93D8) : if (CCR_EQ) {
    rom_DCCE();
    return;
  }                              // BEQ.W	$DCCE
  DEF_ROMLOC(93DC) : rom_DC92(); // BRA.W	$DC92
}