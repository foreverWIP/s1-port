// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_149BC) {
  u8 switchindex = 0;
  DEF_ROMLOC(149BC) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(149BE) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(149C2)
      : move_toreg_16(read_16(0x149CA + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(149C6): goto rom_149CA + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(149C6) : switch (switchindex) {
  case 0:
    rom_149D0();
  case 1:
    rom_14A02();
  case 2:
    rom_14A44();
  }
}
ROMFUNC(rom_149D0) {
  DEF_ROMLOC(149D0) : tst_mem_32(v_plc_buffer);      // TST.L	$F680
  DEF_ROMLOC(149D4) : if (CCR_EQ) goto rom_149D8;  // BEQ.B	$149D8
  DEF_ROMLOC(149D6) : return;                      // RTS
  DEF_ROMLOC(149D8) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(149DC)
      : move_tomem_32(0x14BD4, A0 + 0x4);             // MOVE.L	#$00014BD4,4(A0)
  DEF_ROMLOC(149E4) : move_tomem_8(0x4, A0 + 0x1);    // MOVE.B	#$04,1(A0)
  DEF_ROMLOC(149EA) : move_tomem_8(0x1, A0 + 0x18);   // MOVE.B	#$01,24(A0)
  DEF_ROMLOC(149F0) : move_tomem_8(0x38, A0 + 0x19);  // MOVE.B	#$38,25(A0)
  DEF_ROMLOC(149F6) : move_tomem_16(0x541, A0 + 0x2); // MOVE.W	#$0541,2(A0)
  DEF_ROMLOC(149FC) : move_tomem_16(0x78, A0 + 0x30); // MOVE.W	#$0078,48(A0)
  rom_14A02(); // Detected flow into next function
}
ROMFUNC(rom_14A02) {
  DEF_ROMLOC(14A02)
      : move_tomem_16(read_16(0xFFFFD008), A0 + 0x8); // MOVE.W	$D008,8(A0)
  DEF_ROMLOC(14A08)
      : move_tomem_16(read_16(0xFFFFD00C), A0 + 0xC); // MOVE.W	$D00C,12(A0)
  DEF_ROMLOC(14A0E)
      : move_tomem_8(read_8(0xFFFFD022), A0 + 0x22); // MOVE.B	$D022,34(A0)
  DEF_ROMLOC(14A14) : move_toreg_32(0x14BBE, &A1);   // LEA.L	$00014BBE,A1
  DEF_ROMLOC(14A1A) : rom_ADA2();                    // JSR	$0000ADA2
  DEF_ROMLOC(14A20) : cmp_tomem_8(0x2, A0 + 0x1A);   // CMPI.B	#$02,26(A0)
  DEF_ROMLOC(14A26) : if (!CCR_EQ) goto rom_14A3E;   // BNE.B	$14A3E
  DEF_ROMLOC(14A28) : tst_mem_8(0xFFFFD000);         // TST.B	$D000
  DEF_ROMLOC(14A2C) : if (CCR_EQ) goto rom_14A3E;    // BEQ.B	$14A3E
  DEF_ROMLOC(14A2E) : move_tomem_8(0x0, 0xFFFFD000); // MOVE.B	#$00,$D000
  DEF_ROMLOC(14A34) : move_toreg_16(0xA8, &D0);      // MOVE.W	#$00A8,D0
  DEF_ROMLOC(14A38) : rom_1394();                    // JSR	$00001394
  DEF_ROMLOC(14A3E) : rom_DC92();
  return; // JMP	$0000DC92
}
ROMFUNC(rom_14A44) {
  DEF_ROMLOC(14A44) : sub_tomem_16(0x1, A0 + 0x30);  // SUBQ.W	#$01,48(A0)
  DEF_ROMLOC(14A48) : if (!CCR_EQ) goto rom_14A56;   // BNE.B	$14A56
  DEF_ROMLOC(14A4A) : move_tomem_8(0x1, 0xFFFFD000); // MOVE.B	#$01,$D000
  DEF_ROMLOC(14A50) : rom_DCCE();
  return;                     // JMP	$0000DCCE
  DEF_ROMLOC(14A56) : return; // RTS
}