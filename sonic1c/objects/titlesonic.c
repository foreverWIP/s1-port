// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_ACA6) {
  u8 switchindex = 0;
  DEF_ROMLOC(ACA6) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(ACA8) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(ACAC)
      : move_toreg_16(read_16(0xACB4 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(ACB0): goto rom_ACB4 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(ACB0) : switch (switchindex) {
  case 0:
    rom_ACBC();
    break;
  case 1:
    rom_ACF0();
    break;
  case 2:
    rom_AD00();
    break;
  case 3:
    rom_AD16();
    break;
  }
}
ROMFUNC(rom_ACBC) {
  DEF_ROMLOC(ACBC) : add_tomem_8(0x2, A0 + 0x24);     // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(ACC0) : move_tomem_16(0xF0, A0 + 0x8);   // MOVE.W	#$00F0,8(A0)
  DEF_ROMLOC(ACC6) : move_tomem_16(0xDE, A0 + 0xA);   // MOVE.W	#$00DE,10(A0)
  DEF_ROMLOC(ACCC) : move_tomem_32(0xAF12, A0 + 0x4); // MOVE.L	#$0000AF12,4(A0)
  DEF_ROMLOC(ACD4) : move_tomem_16(0x2300, A0 + 0x2); // MOVE.W	#$2300,2(A0)
  DEF_ROMLOC(ACDA) : move_tomem_8(0x1, A0 + 0x18);    // MOVE.B	#$01,24(A0)
  DEF_ROMLOC(ACE0) : move_tomem_8(0x1D, A0 + 0x1F);   // MOVE.B	#$1D,31(A0)
  DEF_ROMLOC(ACE6) : move_toreg_32(0xAD8E, &A1);      // LEA.L	$0000AD8E,A1
  DEF_ROMLOC(ACEC) : animate_sprite();                // BSR.W	$ADA2
  rom_ACF0(); // Detected flow into next function
}
ROMFUNC(rom_ACF0) {
  DEF_ROMLOC(ACF0) : sub_tomem_8(0x1, A0 + 0x1F); // SUBQ.B	#$01,31(A0)
  DEF_ROMLOC(ACF4) : if (CCR_PL) goto rom_ACFE;   // BPL.B	$ACFE
  DEF_ROMLOC(ACF6) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(ACFA) : queue_sprite();
  return;                    // BRA.W	$DC92
  DEF_ROMLOC(ACFE) : return; // RTS
}
ROMFUNC(rom_AD00) {
  DEF_ROMLOC(AD00) : sub_tomem_16(0x8, A0 + 0xA);  // SUBQ.W	#$08,10(A0)
  DEF_ROMLOC(AD04) : cmp_tomem_16(0x96, A0 + 0xA); // CMPI.W	#$0096,10(A0)
  DEF_ROMLOC(AD0A) : if (!CCR_EQ) goto rom_AD10;   // BNE.B	$AD10
  DEF_ROMLOC(AD0C) : add_tomem_8(0x2, A0 + 0x24);  // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(AD10) : queue_sprite();
  return;                    // BRA.W	$DC92
  DEF_ROMLOC(AD14) : return; // RTS
}
ROMFUNC(rom_AD16) {
  DEF_ROMLOC(AD16) : move_toreg_32(0xAD8E, &A1); // LEA.L	$0000AD8E,A1
  DEF_ROMLOC(AD1C) : animate_sprite();           // BSR.W	$ADA2
  DEF_ROMLOC(AD20) : queue_sprite();
  return;                    // BRA.W	$DC92
  DEF_ROMLOC(AD24) : return; // RTS
}