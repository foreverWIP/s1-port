// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_4F68) {
  u8 switchindex = 0;
  DEF_ROMLOC(4F68) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(4F6A) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(4F6E)
      : move_toreg_16(read_16(0x4F7C + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	12(PC,D0),D1
  // DEF_ROMLOC(4F72): rom_4F7C + (s16)(D1 & 0xffff)(); // JSR	8(PC,D1)
  DEF_ROMLOC(4F72) : switch (switchindex) {
  case 0:
    rom_4F84();
    break;
  case 1:
    rom_4FBA();
    break;
  case 2:
    rom_4FF2();
    break;
  case 3:
    rom_502C();
    break;
  }
  DEF_ROMLOC(4F76) : rom_DC92();
  return; // JMP	$0000DC92
}
ROMFUNC(rom_4F84) {
  DEF_ROMLOC(4F84) : add_tomem_8(0x2, A0 + 0x24);   // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(4F88) : move_tomem_16(0xA0, A0 + 0x8); // MOVE.W	#$00A0,8(A0)
  DEF_ROMLOC(4F8E) : move_tomem_16(0xC0, A0 + 0xC); // MOVE.W	#$00C0,12(A0)
  DEF_ROMLOC(4F94)
      : move_tomem_32(0x21CF4, A0 + 0x4);             // MOVE.L	#$00021CF4,4(A0)
  DEF_ROMLOC(4F9C) : move_tomem_16(0x780, A0 + 0x2);  // MOVE.W	#$0780,2(A0)
  DEF_ROMLOC(4FA2) : move_tomem_8(0x4, A0 + 0x1);     // MOVE.B	#$04,1(A0)
  DEF_ROMLOC(4FA8) : move_tomem_8(0x2, A0 + 0x18);    // MOVE.B	#$02,24(A0)
  DEF_ROMLOC(4FAE) : move_tomem_8(0x1D, A0 + 0x1C);   // MOVE.B	#$1D,28(A0)
  DEF_ROMLOC(4FB4) : move_tomem_16(0x400, A0 + 0x12); // MOVE.W	#$0400,18(A0)
  rom_4FBA(); // Detected flow into next function
}
ROMFUNC(rom_4FBA) {
  DEF_ROMLOC(4FBA) : cmp_tomem_16(0x1A0, A0 + 0xC); // CMPI.W	#$01A0,12(A0)
  DEF_ROMLOC(4FC0) : if (!CCR_EQ) goto rom_4FE0;    // BNE.B	$4FE0
  DEF_ROMLOC(4FC2) : add_tomem_8(0x2, A0 + 0x24);   // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(4FC6) : clr_mem_16(A0 + 0x12);         // CLR.W	18(A0)
  DEF_ROMLOC(4FCA)
      : move_tomem_32(0x5062, A0 + 0x4); // MOVE.L	#$00005062,4(A0)
  DEF_ROMLOC(4FD2)
      : move_tomem_16(0xFFFF8500, A0 + 0x2);       // MOVE.W	#$8500,2(A0)
  DEF_ROMLOC(4FD8) : move_tomem_8(0x0, A0 + 0x1C); // MOVE.B	#$00,28(A0)
  rom_4FF2();
  return;                         // BRA.B	$4FF2
  DEF_ROMLOC(4FE0) : rom_DC6C();  // JSR	$0000DC6C
  DEF_ROMLOC(4FE6) : rom_14098(); // JSR	$00014098
  DEF_ROMLOC(4FEC) : rom_14312();
  return; // JMP	$00014312
}
ROMFUNC(rom_4FF2) {
  DEF_ROMLOC(4FF2) : tst_mem_8(0xFFFFF605);      // TST.B	$F605
  DEF_ROMLOC(4FF6) : if (CCR_MI) goto rom_5004;  // BMI.B	$5004
  DEF_ROMLOC(4FF8) : move_toreg_32(0x5054, &A1); // LEA.L	$00005054,A1
  DEF_ROMLOC(4FFE) : rom_ADA2();
  return;                                         // JMP	$0000ADA2
  DEF_ROMLOC(5004) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(5008)
      : move_tomem_32(0x21CF4, A0 + 0x4);            // MOVE.L	#$00021CF4,4(A0)
  DEF_ROMLOC(5010) : move_tomem_16(0x780, A0 + 0x2); // MOVE.W	#$0780,2(A0)
  DEF_ROMLOC(5016) : move_tomem_8(0x1E, A0 + 0x1C);  // MOVE.B	#$1E,28(A0)
  DEF_ROMLOC(501C) : clr_mem_16(A0 + 0x14);          // CLR.W	20(A0)
  DEF_ROMLOC(5020) : sub_tomem_16(0x8, A0 + 0xC);    // SUBQ.W	#$08,12(A0)
  DEF_ROMLOC(5024) : move_toreg_8(0xFFFFFFE0, &D0);  // MOVE.B	#$E0,D0
  DEF_ROMLOC(5028) : play_sound_special();           // BSR.W	$1394
  rom_502C(); // Detected flow into next function
}
ROMFUNC(rom_502C) {
  DEF_ROMLOC(502C)
      : cmp_tomem_16(0x800, A0 + 0x14);          // CMPI.W	#$0800,20(A0)
  DEF_ROMLOC(5032) : if (!CCR_EQ) goto rom_503C; // BNE.B	$503C
  DEF_ROMLOC(5034)
      : move_tomem_16(0x1000, A0 + 0x10); // MOVE.W
                                          // #$1000,16(A0)
  goto rom_5042;                          // BRA.B	$5042
  DEF_ROMLOC(503C)
      : add_tomem_16(0x20, A0 + 0x14); // ADDI.W	#$0020,20(A0)
  DEF_ROMLOC(5042) : rom_DC6C();       // JSR	$0000DC6C
  DEF_ROMLOC(5048) : rom_14098();      // JSR	$00014098
  DEF_ROMLOC(504E) : rom_14312();
  return; // JMP	$00014312
}