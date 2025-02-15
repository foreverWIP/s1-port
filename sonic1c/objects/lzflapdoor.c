// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_11A1A) {
  u8 switchindex = 0;
  DEF_ROMLOC(11A1A) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(11A1C) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(11A20)
      : move_toreg_16(read_16(0x11A28 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(11A24): goto rom_11A28 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(11A24) : switch (switchindex) {
  case 0:
    rom_11A2C();
    break;
  case 1:
    rom_11A58();
    break;
  }
}
ROMFUNC(rom_11A2C) {
  DEF_ROMLOC(11A2C) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(11A30)
      : move_tomem_32(0x11AC6, A0 + 0x4); // MOVE.L	#$00011AC6,4(A0)
  DEF_ROMLOC(11A38)
      : move_tomem_16(0x4328, A0 + 0x2);         // MOVE.W
                                                 // #$4328,2(A0)
  DEF_ROMLOC(11A3E) : or_tomem_8(0x4, A0 + 0x1); // ORI.B	#$04,1(A0)
  DEF_ROMLOC(11A44)
      : move_tomem_8(0x28, A0 + 0x19);         // MOVE.B	#$28,25(A0)
  DEF_ROMLOC(11A4A) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(11A4C)
      : move_toreg_8(read_8(A0 + 0x28), &D0);       // MOVE.B	40(A0),D0
  DEF_ROMLOC(11A50) : mulu_toreg_16(0x3C, &D0);     // MULU.W	#$003C,D0
  DEF_ROMLOC(11A54) : move_tomem_16(D0, A0 + 0x32); // MOVE.W	D0,50(A0)
  rom_11A58(); // Detected flow into next function
}
ROMFUNC(rom_11A58) {
  DEF_ROMLOC(11A58) : sub_tomem_16(0x1, A0 + 0x30); // SUBQ.W	#$01,48(A0)
  DEF_ROMLOC(11A5C) : if (CCR_PL) goto rom_11A7A;   // BPL.B	$11A7A
  DEF_ROMLOC(11A5E)
      : move_tomem_16(read_16(A0 + 0x32), A0 + 0x30); // MOVE.W	50(A0),48(A0)
  DEF_ROMLOC(11A64) : bchg_tomem_8(0x0, A0 + 0x1C);   // BCHG.B	#$00,28(A0)
  DEF_ROMLOC(11A6A) : tst_mem_8(A0 + 0x1);            // TST.B	1(A0)
  DEF_ROMLOC(11A6E) : if (CCR_PL) goto rom_11A7A;     // BPL.B	$11A7A
  DEF_ROMLOC(11A70) : move_toreg_16(SFX_DOOR, &D0);       // MOVE.W	#$00BB,D0
  DEF_ROMLOC(11A74) : play_sound_special();           // JSR	$00001394
  DEF_ROMLOC(11A7A) : move_toreg_32(0x11AB6, &A1);    // LEA.L	$00011AB6,A1
  DEF_ROMLOC(11A80) : animate_sprite();                     // BSR.W	$ADA2
  DEF_ROMLOC(11A84) : clr_mem_8(0xFFFFF7C9);          // CLR.B	$F7C9
  DEF_ROMLOC(11A88) : tst_mem_8(A0 + 0x1A);           // TST.B	26(A0)
  DEF_ROMLOC(11A8C) : if (!CCR_EQ) goto rom_11AB2;    // BNE.B	$11AB2
  DEF_ROMLOC(11A8E)
      : move_toreg_16(read_16(0xFFFFD008), &D0);            // MOVE.W	$D008,D0
  DEF_ROMLOC(11A92) : cmp_toreg_16(read_16(A0 + 0x8), &D0); // CMP.W	8(A0),D0
  DEF_ROMLOC(11A96) : if (CCR_CC) goto rom_11AB2;           // BCC.B	$11AB2
  DEF_ROMLOC(11A98) : move_tomem_8(0x1, 0xFFFFF7C9);        // MOVE.B	#$01,$F7C9
  DEF_ROMLOC(11A9E) : move_toreg_16(0x13, &D1);             // MOVE.W	#$0013,D1
  DEF_ROMLOC(11AA2) : move_toreg_16(0x20, &D2);             // MOVE.W	#$0020,D2
  DEF_ROMLOC(11AA6) : move_toreg_16(D2, &D3);               // MOVE.W	D2,D3
  DEF_ROMLOC(11AA8) : add_toreg_16(0x1, &D3);               // ADDQ.W	#$01,D3
  DEF_ROMLOC(11AAA)
      : move_toreg_16(read_16(A0 + 0x8), &D4); // MOVE.W	8(A0),D4
  DEF_ROMLOC(11AAE) : rom_10062();             // BSR.W	$10062
  DEF_ROMLOC(11AB2) : {
    rom_FD38();
    return;
  } // BRA.W	$FD38
}