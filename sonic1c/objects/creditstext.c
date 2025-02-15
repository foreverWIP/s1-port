// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_17A10) {
  u8 switchindex = 0;
  DEF_ROMLOC(17A10) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(17A12) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(17A16)
      : move_toreg_16(read_16(0x17A1E + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(17A1A): goto rom_17A1E + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(17A1A) : switch (switchindex) {
  case 0:
    goto rom_17A22;
    break;
  case 1:
    goto rom_17A88;
    break;
  }
  DEF_ROMLOC(17A22) : add_tomem_8(0x2, A0 + 0x24);    // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(17A26) : move_tomem_16(0x120, A0 + 0x8); // MOVE.W	#$0120,8(A0)
  DEF_ROMLOC(17A2C) : move_tomem_16(0xF0, A0 + 0xA);  // MOVE.W	#$00F0,10(A0)
  DEF_ROMLOC(17A32)
      : move_tomem_32(0x17A8E, A0 + 0x4);             // MOVE.L	#$00017A8E,4(A0)
  DEF_ROMLOC(17A3A) : move_tomem_16(0x5A0, A0 + 0x2); // MOVE.W	#$05A0,2(A0)
  DEF_ROMLOC(17A40)
      : move_toreg_16(read_16(0xFFFFFFF4), &D0);         // MOVE.W	$FFF4,D0
  DEF_ROMLOC(17A44) : move_tomem_8(D0, A0 + 0x1A);       // MOVE.B	D0,26(A0)
  DEF_ROMLOC(17A48) : move_tomem_8(0x0, A0 + 0x1);       // MOVE.B	#$00,1(A0)
  DEF_ROMLOC(17A4E) : move_tomem_8(0x0, A0 + 0x18);      // MOVE.B	#$00,24(A0)
  DEF_ROMLOC(17A54) : cmp_tomem_8(GM_TITLE, v_gamemode); // CMPI.B
                                                         // #$04,$F600
  DEF_ROMLOC(17A5A) : if (!CCR_EQ) goto rom_17A88;       // BNE.B	$17A88
  DEF_ROMLOC(17A5C)
      : move_tomem_16(0xA6, A0 + 0x2);               // MOVE.W	#$00A6,2(A0)
  DEF_ROMLOC(17A62) : move_tomem_8(0xA, A0 + 0x1A);  // MOVE.B	#$0A,26(A0)
  DEF_ROMLOC(17A68) : tst_mem_8(0xFFFFFFE3);         // TST.B	$FFE3
  DEF_ROMLOC(17A6C) : if (CCR_EQ) goto rom_17A88;    // BEQ.B	$17A88
  DEF_ROMLOC(17A6E) : cmp_tomem_8(0x72, 0xFFFFF604); // CMPI.B	#$72,$F604
  DEF_ROMLOC(17A74) : if (!CCR_EQ) goto rom_17A88;   // BNE.B	$17A88
  DEF_ROMLOC(17A76)
      : move_tomem_16(0xEEE, 0xFFFFFBC0); // MOVE.W
                                          // #$0EEE,$FBC0
  DEF_ROMLOC(17A7C)
      : move_tomem_16(0x880, 0xFFFFFBC2); // MOVE.W
                                          // #$0880,$FBC2
  DEF_ROMLOC(17A82) : rom_DCCE();
  return; // JMP	$0000DCCE
  DEF_ROMLOC(17A88) : rom_DC92();
  return; // JMP	$0000DC92
}