// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_EF98) {
  u8 switchindex = 0;
  DEF_ROMLOC(EF98) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(EF9A) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(EF9E)
      : move_toreg_16(read_16(0xEFA6 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(EFA2): goto rom_EFA6 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(EFA2) : switch (switchindex) {
  case 0:
    rom_EFAA();
    break;
  case 1:
    rom_EFCE();
    break;
  }
}
ROMFUNC(rom_EFAA) {
  DEF_ROMLOC(EFAA) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(EFAE)
      : move_tomem_32(0xF00E, A0 + 0x4);            // MOVE.L	#$0000F00E,4(A0)
  DEF_ROMLOC(EFB6) : move_tomem_16(0x0, A0 + 0x2);  // MOVE.W	#$0000,2(A0)
  DEF_ROMLOC(EFBC) : move_tomem_8(0x4, A0 + 0x1);   // MOVE.B	#$04,1(A0)
  DEF_ROMLOC(EFC2) : move_tomem_8(0x10, A0 + 0x19); // MOVE.B	#$10,25(A0)
  DEF_ROMLOC(EFC8) : move_tomem_8(0x6, A0 + 0x18);  // MOVE.B	#$06,24(A0)
  rom_EFCE(); // Detected flow into next function
}
ROMFUNC(rom_EFCE) {
  DEF_ROMLOC(EFCE) : sub_tomem_8(0x1, A0 + 0x1E);  // SUBQ.B	#$01,30(A0)
  DEF_ROMLOC(EFD2) : if (CCR_PL) goto rom_EFEC;    // BPL.B	$EFEC
  DEF_ROMLOC(EFD4) : move_tomem_8(0x7, A0 + 0x1E); // MOVE.B	#$07,30(A0)
  DEF_ROMLOC(EFDA) : add_tomem_8(0x1, A0 + 0x1A);  // ADDQ.B	#$01,26(A0)
  DEF_ROMLOC(EFDE) : cmp_tomem_8(0x6, A0 + 0x1A);  // CMPI.B	#$06,26(A0)
  DEF_ROMLOC(EFE4) : if (CCR_CS) goto rom_EFEC;    // BCS.B	$EFEC
  DEF_ROMLOC(EFE6) : move_tomem_8(0x0, A0 + 0x1A); // MOVE.B	#$00,26(A0)
  DEF_ROMLOC(EFEC) : move_toreg_16(read_16(A0 + 0x8), &D0); // MOVE.W	8(A0),D0
  DEF_ROMLOC(EFF0) : and_toreg_16(0xFFFFFF80, &D0);         // ANDI.W	#$FF80,D0
  DEF_ROMLOC(EFF4)
      : move_toreg_16(read_16(v_screenposx), &D1);  // MOVE.W	$F700,D1
  DEF_ROMLOC(EFF8) : sub_toreg_16(0x80, &D1);       // SUBI.W	#$0080,D1
  DEF_ROMLOC(EFFC) : and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
  DEF_ROMLOC(F000) : sub_toreg_16(D1, &D0);         // SUB.W	D1,D0
  DEF_ROMLOC(F002) : cmp_toreg_16(0x280, &D0);      // CMPI.W	#$0280,D0
  DEF_ROMLOC(F006) : if (CCR_HI) {
    rom_DCCE();
    return;
  } // BHI.W	$DCCE
  rom_DC92(); // BRA.W	$DC92
}