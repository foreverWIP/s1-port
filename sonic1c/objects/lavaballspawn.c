// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_E924) {
  u8 switchindex = 0;
  DEF_ROMLOC(E924) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(E926) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(E92A)
      : move_toreg_16(read_16(0xE936 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	10(PC,D0),D1
  // DEF_ROMLOC(E92E): rom_E936 + (s16)(D1 & 0xffff)(); // JSR	6(PC,D1)
  DEF_ROMLOC(E92E) : switch (switchindex) {
  case 0:
    rom_E940();
    break;
  case 1:
    rom_E960();
    break;
  }
  rom_EA66(); // BRA.W	$EA66
}
ROMFUNC(rom_E940) {
  DEF_ROMLOC(E940) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(E944)
      : move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B	40(A0),D0
  DEF_ROMLOC(E948) : lsr_toreg_16(0x4, &D0);  // LSR.W	#$04,D0
  DEF_ROMLOC(E94A) : and_toreg_16(0xF, &D0);  // ANDI.W	#$000F,D0
  DEF_ROMLOC(E94E)
      : move_tomem_8(read_8(0xE93A + (s16)(D0 & 0xffff)),
                     A0 + 0x1F); // MOVE.B	-22(PC,D0),31(A0)
  DEF_ROMLOC(E954)
      : move_tomem_8(read_8(A0 + 0x1F), A0 + 0x1E); // MOVE.B	31(A0),30(A0)
  DEF_ROMLOC(E95A) : and_tomem_8(0xF, A0 + 0x28);   // ANDI.B	#$0F,40(A0)
  rom_E960(); // Detected flow into next function
}
ROMFUNC(rom_E960) {
  DEF_ROMLOC(E960) : sub_tomem_8(0x1, A0 + 0x1E); // SUBQ.B	#$01,30(A0)
  DEF_ROMLOC(E964) : if (!CCR_EQ) goto rom_E990;  // BNE.B	$E990
  DEF_ROMLOC(E966)
      : move_tomem_8(read_8(A0 + 0x1F), A0 + 0x1E); // MOVE.B	31(A0),30(A0)
  DEF_ROMLOC(E96C) : rom_DF0C();                    // BSR.W	$DF0C
  DEF_ROMLOC(E970) : if (!CCR_EQ) goto rom_E990;    // BNE.B	$E990
  DEF_ROMLOC(E972) : rom_E11A();                    // BSR.W	$E11A
  DEF_ROMLOC(E976) : if (!CCR_EQ) goto rom_E990;    // BNE.B	$E990
  DEF_ROMLOC(E978) : move_tomem_8(OBJ_LAVABALL, A1 + offsetof(object, id));  // MOVE.B	#$14,0(A1)
  DEF_ROMLOC(E97E)
      : move_tomem_16(read_16(A0 + 0x8), A1 + 0x8); // MOVE.W	8(A0),8(A1)
  DEF_ROMLOC(E984)
      : move_tomem_16(read_16(A0 + 0xC), A1 + 0xC); // MOVE.W	12(A0),12(A1)
  DEF_ROMLOC(E98A)
      : move_tomem_8(read_8(A0 + 0x28), A1 + 0x28); // MOVE.B	40(A0),40(A1)
  DEF_ROMLOC(E990) : return;                        // RTS
}