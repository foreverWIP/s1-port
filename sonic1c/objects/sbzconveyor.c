// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_15DF6) {
  u8 switchindex = 0;
  DEF_ROMLOC(15DF6) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(15DF8) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(15DFC)
      : move_toreg_16(read_16(0x15E04 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(15E00): goto rom_15E04 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(15E00) : switch (switchindex) {
  case 0:
    rom_15E08();
    break;
  case 1:
    rom_15E32();
    break;
  }
}
ROMFUNC(rom_15E08) {
  DEF_ROMLOC(15E08) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(15E0C)
      : move_tomem_8(0xFFFFFF80, A0 + 0x38); // MOVE.B	#$80,56(A0)
  DEF_ROMLOC(15E12)
      : move_toreg_8(read_8(A0 + 0x28), &D1);        // MOVE.B
                                                     // 40(A0),D1
  DEF_ROMLOC(15E16) : and_toreg_8(0xF, &D1);         // ANDI.B	#$0F,D1
  DEF_ROMLOC(15E1A) : if (CCR_EQ) goto rom_15E22;    // BEQ.B	$15E22
  DEF_ROMLOC(15E1C) : move_tomem_8(0x38, A0 + 0x38); // MOVE.B	#$38,56(A0)
  DEF_ROMLOC(15E22)
      : move_toreg_8(read_8(A0 + 0x28), &D1);       // MOVE.B	40(A0),D1
  DEF_ROMLOC(15E26) : and_toreg_8(0xFFFFFFF0, &D1); // ANDI.B	#$F0,D1
  DEF_ROMLOC(15E2A) : ext_reg_16(&D1);              // EXT.W	D1
  DEF_ROMLOC(15E2C) : asr_toreg_16(0x4, &D1);       // ASR.W	#$04,D1
  DEF_ROMLOC(15E2E) : move_tomem_16(D1, A0 + 0x36); // MOVE.W	D1,54(A0)
  rom_15E32(); // Detected flow into next function
}
ROMFUNC(rom_15E58) {
  DEF_ROMLOC(15E58) : move_toreg_32(0x0, &D2); // MOVEQ.L	$00,D2
  DEF_ROMLOC(15E5A)
      : move_toreg_8(read_8(A0 + 0x38), &D2);         // MOVE.B
                                                      // 56(A0),D2
  DEF_ROMLOC(15E5E) : move_toreg_16(D2, &D3);         // MOVE.W	D2,D3
  DEF_ROMLOC(15E60) : add_toreg_16(D3, &D3);          // ADD.W	D3,D3
  DEF_ROMLOC(15E62) : move_toreg_32(0xFFFFD000, &A1); // LEA.L	$D000,A1
  DEF_ROMLOC(15E66)
      : move_toreg_16(read_16(A1 + 0x8), &D0); // MOVE.W	8(A1),D0
  DEF_ROMLOC(15E6A)
      : sub_toreg_16(read_16(A0 + 0x8), &D0);     // SUB.W	8(A0),D0
  DEF_ROMLOC(15E6E) : add_toreg_16(D2, &D0);      // ADD.W	D2,D0
  DEF_ROMLOC(15E70) : cmp_toreg_16(D3, &D0);      // CMP.W	D3,D0
  DEF_ROMLOC(15E72) : if (CCR_CC) goto rom_15E96; // BCC.B	$15E96
  DEF_ROMLOC(15E74)
      : move_toreg_16(read_16(A1 + 0xC), &D1); // MOVE.W	12(A1),D1
  DEF_ROMLOC(15E78)
      : sub_toreg_16(read_16(A0 + 0xC), &D1);       // SUB.W	12(A0),D1
  DEF_ROMLOC(15E7C) : add_toreg_16(0x30, &D1);      // ADDI.W	#$0030,D1
  DEF_ROMLOC(15E80) : cmp_toreg_16(0x30, &D1);      // CMPI.W	#$0030,D1
  DEF_ROMLOC(15E84) : if (CCR_CC) goto rom_15E96;   // BCC.B	$15E96
  DEF_ROMLOC(15E86) : btst_tomem_8(0x1, A1 + 0x22); // BTST.B	#$01,34(A1)
  DEF_ROMLOC(15E8C) : if (!CCR_EQ) goto rom_15E96;  // BNE.B	$15E96
  DEF_ROMLOC(15E8E)
      : move_toreg_16(read_16(A0 + 0x36), &D0);   // MOVE.W	54(A0),D0
  DEF_ROMLOC(15E92) : add_tomem_16(D0, A1 + 0x8); // ADD.W	D0,8(A1)
  DEF_ROMLOC(15E96) : return;                     // RTS
}
ROMFUNC(rom_15E32) {
  DEF_ROMLOC(15E32) : rom_15E58();                           // BSR.B	$15E58
  DEF_ROMLOC(15E34) : move_toreg_16(read_16(A0 + 0x8), &D0); // MOVE.W	8(A0),D0
  DEF_ROMLOC(15E38) : and_toreg_16(0xFFFFFF80, &D0);         // ANDI.W	#$FF80,D0
  DEF_ROMLOC(15E3C)
      : move_toreg_16(read_16(v_screenposx), &D1);   // MOVE.W	$F700,D1
  DEF_ROMLOC(15E40) : sub_toreg_16(0x80, &D1);       // SUBI.W	#$0080,D1
  DEF_ROMLOC(15E44) : and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
  DEF_ROMLOC(15E48) : sub_toreg_16(D1, &D0);         // SUB.W	D1,D0
  DEF_ROMLOC(15E4A)
      : cmp_toreg_16(128 + GAME_WIDTH + 192, &D0); // CMPI.W	#$0280,D0
  DEF_ROMLOC(15E4E) : if (CCR_HI) goto rom_15E52;  // BHI.B	$15E52
  DEF_ROMLOC(15E50) : return;                      // RTS
  DEF_ROMLOC(15E52) : rom_DCCE();
  return; // JMP	$0000DCCE
  rom_15E58();
}