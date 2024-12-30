// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"


ROMFUNC(rom_8E48) {
  u8 switchindex = 0;
  DEF_ROMLOC(8E48) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(8E4A) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(8E4E)
      : move_toreg_16(read_16(0x8E56 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(8E52): goto rom_8E56 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(8E52) : switch (switchindex) {
  case 0:
    rom_8E5A();
    break;
  case 1:
    rom_8E8A();
    break;
  }
}
ROMFUNC(rom_8E5A) {
  DEF_ROMLOC(8E5A) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(8E5E) : move_toreg_32(0x0, &D0);     // MOVEQ.L	$00,D0
  DEF_ROMLOC(8E60)
      : move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B	40(A0),D0
  DEF_ROMLOC(8E64) : mulu_toreg_16(0xA, &D0); // MULU.W	#$000A,D0
  DEF_ROMLOC(8E68)
      : move_toreg_32(0x8EAC + (s16)(D0 & 0xffff),
                      &A1); // LEA.L	66(PC,D0),A1
  DEF_ROMLOC(8E6C)
      : move_tomem_32(read_32((A1 += 4, A1 - 4)),
                      A0 + 0x4); // MOVE.L	(A1)+,4(A0)
  DEF_ROMLOC(8E70)
      : move_tomem_16(read_16((A1 += 2, A1 - 2)),
                      A0 + 0x2);                // MOVE.W	(A1)+,2(A0)
  DEF_ROMLOC(8E74) : or_tomem_8(0x4, A0 + 0x1); // ORI.B	#$04,1(A0)
  DEF_ROMLOC(8E7A)
      : move_tomem_8(read_8(A1++), A0 + 0x1A); // MOVE.B	(A1)+,26(A0)
  DEF_ROMLOC(8E7E)
      : move_tomem_8(read_8(A1++), A0 + 0x19); // MOVE.B	(A1)+,25(A0)
  DEF_ROMLOC(8E82)
      : move_tomem_8(read_8(A1++), A0 + 0x18); // MOVE.B	(A1)+,24(A0)
  DEF_ROMLOC(8E86)
      : move_tomem_8(read_8(A1++), A0 + 0x20); // MOVE.B	(A1)+,32(A0)
  rom_8E8A(); // Detected flow into next function
}
ROMFUNC(rom_8E8A) {
  DEF_ROMLOC(8E8A)
      : move_toreg_16(read_16(A0 + 0x8), &D0);      // MOVE.W	8(A0),D0
  DEF_ROMLOC(8E8E) : and_toreg_16(0xFFFFFF80, &D0); // ANDI.W	#$FF80,D0
  DEF_ROMLOC(8E92)
      : move_toreg_16(read_16(0xFFFFF700), &D1);    // MOVE.W	$F700,D1
  DEF_ROMLOC(8E96) : sub_toreg_16(0x80, &D1);       // SUBI.W	#$0080,D1
  DEF_ROMLOC(8E9A) : and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
  DEF_ROMLOC(8E9E) : sub_toreg_16(D1, &D0);         // SUB.W	D1,D0
  DEF_ROMLOC(8EA0) : cmp_toreg_16(0x280, &D0);      // CMPI.W	#$0280,D0
  DEF_ROMLOC(8EA4) : if (CCR_HI) {
    rom_DCCE();
    return;
  }           // BHI.W	$DCCE
  rom_DC92(); // BRA.W	$DC92
}