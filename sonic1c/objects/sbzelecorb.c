// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_168AE) {
  u8 switchindex = 0;
  DEF_ROMLOC(168AE) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(168B0) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(168B4)
      : move_toreg_16(read_16(0x168BC + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(168B8): goto rom_168BC + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(168B8) : switch (switchindex) {
  case 0:
    rom_168C0();
    break;
  case 1:
    rom_168EC();
    break;
  }
}
ROMFUNC(rom_168C0) {
  DEF_ROMLOC(168C0) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(168C4)
      : move_tomem_32(0x16948, A0 + 0x4);             // MOVE.L	#$00016948,4(A0)
  DEF_ROMLOC(168CC) : move_tomem_16(0x47E, A0 + 0x2); // MOVE.W	#$047E,2(A0)
  DEF_ROMLOC(168D2) : or_tomem_8(0x4, A0 + 0x1);      // ORI.B	#$04,1(A0)
  DEF_ROMLOC(168D8) : move_tomem_8(0x28, A0 + 0x19);  // MOVE.B	#$28,25(A0)
  DEF_ROMLOC(168DE) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(168E0)
      : move_toreg_8(read_8(A0 + 0x28), &D0);       // MOVE.B	40(A0),D0
  DEF_ROMLOC(168E4) : lsl_toreg_16(0x4, &D0);       // LSL.W	#$04,D0
  DEF_ROMLOC(168E6) : sub_toreg_16(0x1, &D0);       // SUBQ.W	#$01,D0
  DEF_ROMLOC(168E8) : move_tomem_16(D0, A0 + 0x34); // MOVE.W	D0,52(A0)
  rom_168EC(); // Detected flow into next function
}
ROMFUNC(rom_168EC) {
  DEF_ROMLOC(168EC)
      : move_toreg_16(read_16(0xFFFFFE04), &D0); // MOVE.W	$FE04,D0
  DEF_ROMLOC(168F0)
      : and_toreg_16(read_16(A0 + 0x34), &D0);      // AND.W	52(A0),D0
  DEF_ROMLOC(168F4) : if (!CCR_EQ) goto rom_1690C;  // BNE.B	$1690C
  DEF_ROMLOC(168F6) : move_tomem_8(0x1, A0 + 0x1C); // MOVE.B	#$01,28(A0)
  DEF_ROMLOC(168FC) : tst_mem_8(A0 + 0x1);          // TST.B	1(A0)
  DEF_ROMLOC(16900) : if (CCR_PL) goto rom_1690C;   // BPL.B	$1690C
  DEF_ROMLOC(16902) : move_toreg_16(0xB1, &D0);     // MOVE.W	#$00B1,D0
  DEF_ROMLOC(16906) : play_sound_special();         // JSR	$00001394
  DEF_ROMLOC(1690C) : move_toreg_32(0x16930, &A1);  // LEA.L	$00016930,A1
  DEF_ROMLOC(16912) : animate_sprite();                   // JSR	$0000ADA2
  DEF_ROMLOC(16918) : move_tomem_8(0x0, A0 + 0x20); // MOVE.B	#$00,32(A0)
  DEF_ROMLOC(1691E) : cmp_tomem_8(0x4, A0 + 0x1A);  // CMPI.B	#$04,26(A0)
  DEF_ROMLOC(16924) : if (!CCR_EQ) goto rom_1692C;  // BNE.B	$1692C
  DEF_ROMLOC(16926)
      : move_tomem_8(0xFFFFFFA4, A0 + 0x20); // MOVE.B	#$A4,32(A0)
  DEF_ROMLOC(1692C) : rom_FD38();
  return; // BRA.W	$FD38
}