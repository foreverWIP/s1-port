// #define CHECK_STUFF 1
#include "opcodes.h"
#include "system.h"


ROMFUNC(rom_134A) {
  DEF_ROMLOC(134A) : return; // RTS
  DEF_ROMLOC(134C)
      : move_tomem_16(0x100, 0xA11100); // MOVE.W	#$0100,$00A11100
  DEF_ROMLOC(1354)
      : move_tomem_16(0x100, 0xA11200);            // MOVE.W	#$0100,$00A11200
  DEF_ROMLOC(135C) : move_toreg_32(0x72E7C, &A0);  // LEA.L	$00072E7C,A0
  DEF_ROMLOC(1362) : move_toreg_32(0xA00000, &A1); // LEA.L	$00A00000,A1
  DEF_ROMLOC(1368) : rom_1894();                   // BSR.W	$1894
  DEF_ROMLOC(136C)
      : move_tomem_16(0x0, 0xA11200); // MOVE.W	#$0000,$00A11200
  DEF_ROMLOC(1374) : {};              // NOP
  DEF_ROMLOC(1376) : {};              // NOP
  DEF_ROMLOC(1378) : {};              // NOP
  DEF_ROMLOC(137A) : {};              // NOP
  DEF_ROMLOC(137C)
      : move_tomem_16(0x100, 0xA11200); // MOVE.W	#$0100,$00A11200
  DEF_ROMLOC(1384)
      : move_tomem_16(0x0, 0xA11100); // MOVE.W	#$0000,$00A11100
  DEF_ROMLOC(138C) : return;          // RTS
}
ROMFUNC(rom_138E) {
  DEF_ROMLOC(138E) : move_tomem_8(D0, 0xFFFFF00A); // MOVE.B	D0,$F00A
  DEF_ROMLOC(1392) : return;                       // RTS
}
ROMFUNC(rom_1394) {
  DEF_ROMLOC(1394) : move_tomem_8(D0, 0xFFFFF00B); // MOVE.B	D0,$F00B
  DEF_ROMLOC(1398) : return;                       // RTS
}
ROMFUNC(rom_139A) {
  DEF_ROMLOC(139A) : move_tomem_8(D0, 0xFFFFF00C); // MOVE.B	D0,$F00C
  DEF_ROMLOC(139E) : return;                       // RTS
}
ROMFUNC(rom_71B4C) { return; }
ROMFUNC(rom_147E2) {
  DEF_ROMLOC(147E2) : cmp_tomem_16(0xC, 0xFFFFFE14);   // CMPI.W	#$000C,$FE14
  DEF_ROMLOC(147E8) : if (CCR_HI) goto rom_14814;      // BHI.B	$14814
  DEF_ROMLOC(147EA) : move_toreg_16(0x82, &D0);        // MOVE.W	#$0082,D0
  DEF_ROMLOC(147EE) : cmp_tomem_16(0x103, 0xFFFFFE10); // CMPI.W
                                                       // #$0103,$FE10
  DEF_ROMLOC(147F4) : if (!CCR_EQ) goto rom_147FA;     // BNE.B	$147FA
  DEF_ROMLOC(147F6) : move_toreg_16(0x86, &D0);        // MOVE.W	#$0086,D0
  DEF_ROMLOC(147FA) : tst_mem_8(0xFFFFFE2D);           // TST.B	$FE2D
  DEF_ROMLOC(147FE) : if (CCR_EQ) goto rom_14804;      // BEQ.B	$14804
  DEF_ROMLOC(14800) : move_toreg_16(0x87, &D0);        // MOVE.W	#$0087,D0
  DEF_ROMLOC(14804) : tst_mem_8(0xFFFFF7AA);           // TST.B	$F7AA
  DEF_ROMLOC(14808) : if (CCR_EQ) goto rom_1480E;      // BEQ.B	$1480E
  DEF_ROMLOC(1480A) : move_toreg_16(0x8C, &D0);        // MOVE.W	#$008C,D0
  DEF_ROMLOC(1480E) : rom_138E();                      // JSR	$0000138E
  DEF_ROMLOC(14814) : move_tomem_16(0x1E, 0xFFFFFE14); // MOVE.W
                                                       // #$001E,$FE14
  DEF_ROMLOC(1481A) : clr_mem_8(0xFFFFD372);           // CLR.B	$D372
  DEF_ROMLOC(1481E) : return;                          // RTS
}