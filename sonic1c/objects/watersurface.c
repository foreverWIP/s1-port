// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_1179A) {
  u8 switchindex = 0;
  DEF_ROMLOC(1179A) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(1179C) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(117A0)
      : move_toreg_16(read_16(0x117A8 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(117A4): goto rom_117A8 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(117A4) : switch (switchindex) {
  case 0:
    rom_117AC();
    break;
  case 1:
    rom_117D0();
    break;
  }
}
ROMFUNC(rom_117AC) {
  DEF_ROMLOC(117AC) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(117B0)
      : move_tomem_32(0x11840, A0 + 0x4); // MOVE.L	#$00011840,4(A0)
  DEF_ROMLOC(117B8)
      : move_tomem_16(0xFFFFC300, A0 + 0x2);       // MOVE.W	#$C300,2(A0)
  DEF_ROMLOC(117BE) : move_tomem_8(0x4, A0 + 0x1); // MOVE.B	#$04,1(A0)
  DEF_ROMLOC(117C4)
      : move_tomem_8(0xFFFFFF80, A0 + 0x19); // MOVE.B	#$80,25(A0)
  DEF_ROMLOC(117CA)
      : move_tomem_16(read_16(A0 + 0x8), A0 + 0x30); // MOVE.W	8(A0),48(A0)
  rom_117D0(); // Detected flow into next function
}
ROMFUNC(rom_117D0) {
  DEF_ROMLOC(117D0)
      : move_toreg_16(read_16(0xFFFFF700), &D1);     // MOVE.W	$F700,D1
  DEF_ROMLOC(117D4) : and_toreg_16(0xFFFFFFE0, &D1); // ANDI.W	#$FFE0,D1
  DEF_ROMLOC(117D8)
      : add_toreg_16(read_16(A0 + 0x30), &D1);       // ADD.W	48(A0),D1
  DEF_ROMLOC(117DC) : btst_tomem_8(0x0, 0xFFFFFE05); // BTST.B	#$00,$FE05
  DEF_ROMLOC(117E2) : if (CCR_EQ) goto rom_117E8;    // BEQ.B	$117E8
  DEF_ROMLOC(117E4) : add_toreg_16(0x20, &D1);       // ADDI.W	#$0020,D1
  DEF_ROMLOC(117E8) : move_tomem_16(D1, A0 + 0x8);   // MOVE.W	D1,8(A0)
  DEF_ROMLOC(117EC)
      : move_toreg_16(read_16(0xFFFFF646), &D1);     // MOVE.W	$F646,D1
  DEF_ROMLOC(117F0) : move_tomem_16(D1, A0 + 0xC);   // MOVE.W	D1,12(A0)
  DEF_ROMLOC(117F4) : tst_mem_8(A0 + 0x32);          // TST.B	50(A0)
  DEF_ROMLOC(117F8) : if (!CCR_EQ) goto rom_1180E;   // BNE.B	$1180E
  DEF_ROMLOC(117FA) : btst_tomem_8(0x7, 0xFFFFF605); // BTST.B	#$07,$F605
  DEF_ROMLOC(11800) : if (CCR_EQ) goto rom_1181E;    // BEQ.B	$1181E
  DEF_ROMLOC(11802) : add_tomem_8(0x3, A0 + 0x1A);   // ADDQ.B	#$03,26(A0)
  DEF_ROMLOC(11806) : move_tomem_8(0x1, A0 + 0x32);  // MOVE.B	#$01,50(A0)
  DEF_ROMLOC(1180C) : goto rom_1183C;                // BRA.B	$1183C
  DEF_ROMLOC(1180E) : tst_mem_16(0xFFFFF63A);        // TST.W	$F63A
  DEF_ROMLOC(11812) : if (!CCR_EQ) goto rom_1183C;   // BNE.B	$1183C
  DEF_ROMLOC(11814) : move_tomem_8(0x0, A0 + 0x32);  // MOVE.B	#$00,50(A0)
  DEF_ROMLOC(1181A) : sub_tomem_8(0x3, A0 + 0x1A);   // SUBQ.B	#$03,26(A0)
  DEF_ROMLOC(1181E) : sub_tomem_8(0x1, A0 + 0x1E);   // SUBQ.B	#$01,30(A0)
  DEF_ROMLOC(11822) : if (CCR_PL) goto rom_1183C;    // BPL.B	$1183C
  DEF_ROMLOC(11824) : move_tomem_8(0x7, A0 + 0x1E);  // MOVE.B	#$07,30(A0)
  DEF_ROMLOC(1182A) : add_tomem_8(0x1, A0 + 0x1A);   // ADDQ.B	#$01,26(A0)
  DEF_ROMLOC(1182E) : cmp_tomem_8(0x3, A0 + 0x1A);   // CMPI.B	#$03,26(A0)
  DEF_ROMLOC(11834) : if (CCR_CS) goto rom_1183C;    // BCS.B	$1183C
  DEF_ROMLOC(11836) : move_tomem_8(0x0, A0 + 0x1A);  // MOVE.B	#$00,26(A0)
  DEF_ROMLOC(1183C) : rom_DC92();                    // BRA.W	$DC92
}