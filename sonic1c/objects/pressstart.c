// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_AD26) {
  u8 switchindex = 0;
  DEF_ROMLOC(AD26) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(AD28) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(AD2C)
      : move_toreg_16(read_16(0xAD38 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	10(PC,D0),D1
  // DEF_ROMLOC(AD30): rom_AD38 + (s16)(D1 & 0xffff)(); // JSR	6(PC,D1)
  DEF_ROMLOC(AD30) : switch (switchindex) {
  case 0:
    rom_AD3E();
    break;
  case 1:
    rom_AD84();
    break;
  case 2:
    rom_AD82();
    break;
  }
  DEF_ROMLOC(AD34) : rom_DC92(); // BRA.W	$DC92
}
ROMFUNC(rom_AD3E) {
  DEF_ROMLOC(AD3E) : add_tomem_8(0x2, A0 + 0x24);    // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(AD42) : move_tomem_16(0xD0, A0 + 0x8);  // MOVE.W	#$00D0,8(A0)
  DEF_ROMLOC(AD48) : move_tomem_16(0x130, A0 + 0xA); // MOVE.W	#$0130,10(A0)
  DEF_ROMLOC(AD4E)
      : move_tomem_32(0xAE4E, A0 + 0x4);             // MOVE.L	#$0000AE4E,4(A0)
  DEF_ROMLOC(AD56) : move_tomem_16(0x200, A0 + 0x2); // MOVE.W	#$0200,2(A0)
  DEF_ROMLOC(AD5C) : cmp_tomem_8(0x2, A0 + 0x1A);    // CMPI.B	#$02,26(A0)
  DEF_ROMLOC(AD62) : if (CCR_CS) {
    rom_AD84();
    return;
  }                                               // BCS.B	$AD84
  DEF_ROMLOC(AD64) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(AD68) : cmp_tomem_8(0x3, A0 + 0x1A); // CMPI.B	#$03,26(A0)
  DEF_ROMLOC(AD6E) : if (!CCR_EQ) {
    rom_AD82();
    return;
  }                                                   // BNE.B	$AD82
  DEF_ROMLOC(AD70) : move_tomem_16(0x2510, A0 + 0x2); // MOVE.W	#$2510,2(A0)
  DEF_ROMLOC(AD76) : move_tomem_16(0x170, A0 + 0x8);  // MOVE.W	#$0170,8(A0)
  DEF_ROMLOC(AD7C) : move_tomem_16(0xF8, A0 + 0xA);   // MOVE.W	#$00F8,10(A0)
  rom_AD82(); // Detected flow into next function
}
ROMFUNC(rom_AD82) {
  DEF_ROMLOC(AD82) : return; // RTS
}
ROMFUNC(rom_AD84) {
  DEF_ROMLOC(AD84) : move_toreg_32(0xAD9C, &A1); // LEA.L	$0000AD9C,A1
  DEF_ROMLOC(AD8A) : animate_sprite();                 // BRA.W	$ADA2
}