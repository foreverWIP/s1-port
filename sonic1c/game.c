// #define CHECK_STUFF 1
#include "opcodes.h"
#include "system.h"


void (*game_state)(void);
bool exit_mainloop = false;

void (*game_state_palette)(void);
void (*game_state_pause)(void);
jmp_buf speedshoes__desync_jumpbuf;

ROMFUNC(rom_388);
ROMFUNC(rom_300) {
  DEF_ROMLOC(34E) : move_toreg_8(read_8(0xA10001), &D0); // MOVE.B
                                                         // $00A10001,D0
  DEF_ROMLOC(354) : and_toreg_8(0xFFFFFFC0, &D0);        // ANDI.B	#$C0,D0
  DEF_ROMLOC(358) : move_tomem_8(D0, 0xFFFFFFF8);        // MOVE.B	D0,$FFF8
  DEF_ROMLOC(35C)
      : move_tomem_32(0x696E6974, 0xFFFFFFFC); // MOVE.L	#$696E6974,$FFFC
  DEF_ROMLOC(376) : rom_1222();                // BSR.W	$1222
  DEF_ROMLOC(37A) : rom_134A();                // BSR.W	$134A
  DEF_ROMLOC(37E) : rom_11B6();                // BSR.W	$11B6
  DEF_ROMLOC(382) : move_tomem_8(0x0, 0xFFFFF600);
  rom_388(); // Detected flow into next function
}
ROMFUNC(rom_388) {
  DEF_ROMLOC(388)
      : move_toreg_8(read_8(0xFFFFF600), &D0); // MOVE.B	$F600,D0
  DEF_ROMLOC(38C) : and_toreg_16(0x1C, &D0);   // ANDI.W	#$001C,D0
  rom_2DD2();
}

void rom_388_nosega(void) {
  DEF_ROMLOC(388): move_toreg_8(read_8(0xFFFFF600), &D0); // MOVE.B	$F600,D0
  DEF_ROMLOC(38C): and_toreg_16(0x1C, &D0);   // ANDI.W	#$001C,D0
	switch (D0 & 0x1C) {
		case 0: game_state = rom_2DD2; break;
		case 4: game_state = rom_2EF4; break;
		case 8: game_state = rom_379E; break;
		case 0xc: game_state = rom_379E; break;
		case 0x10: game_state = rom_45DE; break;
		case 0x14: game_state = rom_4CEC; break;
		case 0x18: game_state = rom_50F2; break;
		case 0x1C: game_state = rom_57D2; break;
	}
}

EXPORT TEST_FLAGS get_test_level(void) {
	return TEST_LEVEL;
}

ROMFUNC(rom_396);
EXPORT void reset_game(void) {
  // print("reseting game");
  for (u16 i = 0; i < 0x4000; i++) {
    write_32(0xFF0000 + (i * 4), 0);
  }
  game_state = rom_300;
  D0 = 0;
  D1 = 0;
  D2 = 0;
  D3 = 0;
  D4 = 0;
  D5 = 0;
  D6 = 0;
  D7 = 0;
  A0 = 0;
  A1 = 0;
  A2 = 0;
  A3 = 0;
  A4 = 0;
  A5 = 0;
  A6 = 0;
  A7 = 0xFFFE00;
  SR = 0x2700;
  // print("game_state = 300");
}
EXPORT void run_game_frame(void) {
  exit_mainloop = false;
  while (true) {
	if (game_state) {
		if (setjmp(speedshoes__desync_jumpbuf)) {
			break;
		} else {
			game_state();
		}
	}
	if (exit_mainloop) {
		break;
	} else {
		rom_388_nosega();
	}
  }
}