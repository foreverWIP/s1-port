// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_D74C) {
  u8 switchindex = 0;
  DEF_ROMLOC(D74C) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(D74E) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(D752)
      : move_toreg_16(read_16(0xD75A + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(D756): goto rom_D75A + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(D756) : switch (switchindex) {
  case 0:
    rom_D75E();
    break;
  case 1:
    rom_D768();
    break;
  }
}
ROMFUNC(rom_D75E) {
  DEF_ROMLOC(D75E) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(D762) : move_tomem_8(0x4, A0 + 0x1); // MOVE.B	#$04,1(A0)
  rom_D768(); // Detected flow into next function
}
ROMFUNC(rom_D768) {
  DEF_ROMLOC(D768)
      : move_toreg_8(read_8(0xFFFFFE0F), &D0); // MOVE.B	$FE0F,D0
  DEF_ROMLOC(D76C) : and_toreg_8(0x3F, &D0);   // ANDI.B	#$3F,D0
  DEF_ROMLOC(D770) : if (!CCR_EQ) {
    rom_D77C();
    return;
  } // BNE.B	$D77C
  DEF_ROMLOC(D772)
      : move_toreg_16(SPECSFX_WATERFALL, &D0); // MOVE.W	#$00D0,D0
  DEF_ROMLOC(D776) : play_sound_special();     // JSR	$00001394
  rom_D77C(); // Detected flow into next function
}
ROMFUNC(rom_D77C) {
  DEF_ROMLOC(D77C) : move_toreg_16(read_16(A0 + 0x8), &D0); // MOVE.W	8(A0),D0
  DEF_ROMLOC(D780) : and_toreg_16(0xFFFFFF80, &D0);         // ANDI.W	#$FF80,D0
  DEF_ROMLOC(D784)
      : move_toreg_16(read_16(v_screenposx), &D1);  // MOVE.W	$F700,D1
  DEF_ROMLOC(D788) : sub_toreg_16(0x80, &D1);       // SUBI.W	#$0080,D1
  DEF_ROMLOC(D78C) : and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
  DEF_ROMLOC(D790) : sub_toreg_16(D1, &D0);         // SUB.W	D1,D0
  DEF_ROMLOC(D792)
      : cmp_toreg_16(128 + GAME_WIDTH + 192, &D0); // CMPI.W	#$0280,D0
  DEF_ROMLOC(D796) : if (CCR_HI) {
    rom_DCCE();
    return;
  } // BHI.W	$DCCE
  DEF_ROMLOC(D79A) : return; // RTS
}