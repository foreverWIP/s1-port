// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_1790A) {
  u8 switchindex = 0;
  DEF_ROMLOC(1790A) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(1790C) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(17910)
      : move_toreg_16(read_16(0x17918 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(17914): goto rom_17918 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(17914) : switch (switchindex) {
  case 0:
    rom_1791C();
    break;
  case 1:
    rom_179C6();
    break;
  }
}
ROMFUNC(rom_1791C) {
  DEF_ROMLOC(1791C) : move_toreg_32(0x10, &D2);       // MOVEQ.L	$10,D2
  DEF_ROMLOC(1791E) : move_toreg_16(D2, &D3);         // MOVE.W	D2,D3
  DEF_ROMLOC(17920) : add_toreg_16(D3, &D3);          // ADD.W	D3,D3
  DEF_ROMLOC(17922) : move_toreg_32(0xFFFFD000, &A1); // LEA.L	$D000,A1
  DEF_ROMLOC(17926)
      : move_toreg_16(read_16(A1 + 0x8), &D0); // MOVE.W	8(A1),D0
  DEF_ROMLOC(1792A)
      : sub_toreg_16(read_16(A0 + 0x8), &D0);     // SUB.W	8(A0),D0
  DEF_ROMLOC(1792E) : add_toreg_16(D2, &D0);      // ADD.W	D2,D0
  DEF_ROMLOC(17930) : cmp_toreg_16(D3, &D0);      // CMP.W	D3,D0
  DEF_ROMLOC(17932) : if (CCR_CC) goto rom_1799A; // BCC.B	$1799A
  DEF_ROMLOC(17934)
      : move_toreg_16(read_16(A1 + 0xC), &D1); // MOVE.W	12(A1),D1
  DEF_ROMLOC(17938)
      : sub_toreg_16(read_16(A0 + 0xC), &D1);      // SUB.W	12(A0),D1
  DEF_ROMLOC(1793C) : add_toreg_16(D2, &D1);       // ADD.W	D2,D1
  DEF_ROMLOC(1793E) : cmp_toreg_16(D3, &D1);       // CMP.W	D3,D1
  DEF_ROMLOC(17940) : if (CCR_CC) goto rom_1799A;  // BCC.B	$1799A
  DEF_ROMLOC(17942) : tst_mem_16(0xFFFFFE08);      // TST.W	$FE08
  DEF_ROMLOC(17946) : if (!CCR_EQ) goto rom_1799A; // BNE.B	$1799A
  DEF_ROMLOC(17948) : tst_mem_8(0xFFFFF7CD);       // TST.B	$F7CD
  DEF_ROMLOC(1794C) : if (!CCR_EQ) goto rom_1799A; // BNE.B	$1799A
  DEF_ROMLOC(1794E) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(17952)
      : move_tomem_32(0x179F4, A0 + 0x4); // MOVE.L	#$000179F4,4(A0)
  DEF_ROMLOC(1795A)
      : move_tomem_16(0xFFFF84B6, A0 + 0x2);         // MOVE.W	#$84B6,2(A0)
  DEF_ROMLOC(17960) : or_tomem_8(0x4, A0 + 0x1);     // ORI.B	#$04,1(A0)
  DEF_ROMLOC(17966) : move_tomem_8(0x0, A0 + 0x18);  // MOVE.B	#$00,24(A0)
  DEF_ROMLOC(1796C) : move_tomem_8(0x10, A0 + 0x19); // MOVE.B	#$10,25(A0)
  DEF_ROMLOC(17972)
      : move_tomem_8(read_8(A0 + 0x28), A0 + 0x1A);   // MOVE.B	40(A0),26(A0)
  DEF_ROMLOC(17978) : move_tomem_16(0x77, A0 + 0x30); // MOVE.W	#$0077,48(A0)
  DEF_ROMLOC(1797E) : move_toreg_16(SFX_BONUS, &D0);       // MOVE.W	#$00C9,D0
  DEF_ROMLOC(17982) : play_sound_special();           // JSR	$00001394
  DEF_ROMLOC(17988) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(1798A) : move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B
                                                            // 40(A0),D0
  DEF_ROMLOC(1798E) : add_toreg_16(D0, &D0);                // ADD.W	D0,D0
  DEF_ROMLOC(17990)
      : move_toreg_16(read_16(0x179BE + (s16)(D0 & 0xffff)),
                      &D0);        // MOVE.W	44(PC,D0),D0
  DEF_ROMLOC(17994) : rom_1CE42(); // JSR	$0001CE42
  DEF_ROMLOC(1799A) : move_toreg_16(read_16(A0 + 0x8), &D0); // MOVE.W	8(A0),D0
  DEF_ROMLOC(1799E) : and_toreg_16(0xFFFFFF80, &D0);         // ANDI.W	#$FF80,D0
  DEF_ROMLOC(179A2)
      : move_toreg_16(read_16(0xFFFFF700), &D1);     // MOVE.W	$F700,D1
  DEF_ROMLOC(179A6) : sub_toreg_16(0x80, &D1);       // SUBI.W	#$0080,D1
  DEF_ROMLOC(179AA) : and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
  DEF_ROMLOC(179AE) : sub_toreg_16(D1, &D0);         // SUB.W	D1,D0
  DEF_ROMLOC(179B0) : cmp_toreg_16(0x280, &D0);      // CMPI.W	#$0280,D0
  DEF_ROMLOC(179B4) : if (CCR_HI) goto rom_179B8;    // BHI.B	$179B8
  DEF_ROMLOC(179B6) : return;                        // RTS
  DEF_ROMLOC(179B8) : rom_DCCE();                    // JMP	$0000DCCE
}
ROMFUNC(rom_179C6) {
  DEF_ROMLOC(179C6) : sub_tomem_16(0x1, A0 + 0x30); // SUBQ.W	#$01,48(A0)
  DEF_ROMLOC(179CA) : if (CCR_MI) goto rom_179EE;   // BMI.B	$179EE
  DEF_ROMLOC(179CC) : move_toreg_16(read_16(A0 + 0x8), &D0); // MOVE.W	8(A0),D0
  DEF_ROMLOC(179D0) : and_toreg_16(0xFFFFFF80, &D0);         // ANDI.W	#$FF80,D0
  DEF_ROMLOC(179D4)
      : move_toreg_16(read_16(0xFFFFF700), &D1);     // MOVE.W	$F700,D1
  DEF_ROMLOC(179D8) : sub_toreg_16(0x80, &D1);       // SUBI.W	#$0080,D1
  DEF_ROMLOC(179DC) : and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
  DEF_ROMLOC(179E0) : sub_toreg_16(D1, &D0);         // SUB.W	D1,D0
  DEF_ROMLOC(179E2) : cmp_toreg_16(0x280, &D0);      // CMPI.W	#$0280,D0
  DEF_ROMLOC(179E6) : if (CCR_HI) goto rom_179EE;    // BHI.B	$179EE
  DEF_ROMLOC(179E8) : rom_DC92();
  return;                         // JMP	$0000DC92
  DEF_ROMLOC(179EE) : rom_DCCE(); // JMP	$0000DCCE
}