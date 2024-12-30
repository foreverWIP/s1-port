// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_8EDC) {
  u8 switchindex = 0;
  DEF_ROMLOC(8EDC) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(8EDE) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(8EE2)
      : move_toreg_16(read_16(0x8EEA + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(8EE6): goto rom_8EEA + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(8EE6) : switch (switchindex) {
  case 0:
    rom_8EF0();
    break;
  case 1:
    rom_8F1A();
    break;
  case 2:
    rom_8F58();
    break;
  }
}
ROMFUNC(rom_8EF0) {
  DEF_ROMLOC(8EF0) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(8EF4)
      : move_tomem_32(0x8F9A, A0 + 0x4);              // MOVE.L	#$00008F9A,4(A0)
  DEF_ROMLOC(8EFC) : move_tomem_16(0x4000, A0 + 0x2); // MOVE.W	#$4000,2(A0)
  DEF_ROMLOC(8F02) : move_tomem_8(0x4, A0 + 0x1);     // MOVE.B	#$04,1(A0)
  DEF_ROMLOC(8F08)
      : move_tomem_16(read_16(A0 + 0xC), A0 + 0x30); // MOVE.W	12(A0),48(A0)
  DEF_ROMLOC(8F0E) : move_tomem_8(0x10, A0 + 0x19);  // MOVE.B	#$10,25(A0)
  DEF_ROMLOC(8F14) : move_tomem_8(0x5, A0 + 0x18);   // MOVE.B	#$05,24(A0)
  rom_8F1A(); // Detected flow into next function
}
ROMFUNC(rom_8F1A) {
  DEF_ROMLOC(8F1A)
      : move_tomem_16(read_16(A0 + 0x30), A0 + 0xC); // MOVE.W	48(A0),12(A0)
  DEF_ROMLOC(8F20) : move_toreg_16(0x10, &D1);       // MOVE.W	#$0010,D1
  DEF_ROMLOC(8F24) : rom_8F5E();                     // BSR.W	$8F5E
  DEF_ROMLOC(8F28) : if (CCR_EQ) goto rom_8F34;      // BEQ.B	$8F34
  DEF_ROMLOC(8F2A) : add_tomem_16(0x2, A0 + 0xC);    // ADDQ.W	#$02,12(A0)
  DEF_ROMLOC(8F2E) : move_toreg_32(0x1, &D0);        // MOVEQ.L	$01,D0
  DEF_ROMLOC(8F30) : move_tomem_16(D0, 0xFFFFF7E0);  // MOVE.W	D0,$F7E0
  DEF_ROMLOC(8F34) : rom_DC92();                     // BSR.W	$DC92
  DEF_ROMLOC(8F38)
      : move_toreg_16(read_16(A0 + 0x8), &D0);      // MOVE.W	8(A0),D0
  DEF_ROMLOC(8F3C) : and_toreg_16(0xFFFFFF80, &D0); // ANDI.W	#$FF80,D0
  DEF_ROMLOC(8F40)
      : move_toreg_16(read_16(0xFFFFF700), &D1);    // MOVE.W	$F700,D1
  DEF_ROMLOC(8F44) : sub_toreg_16(0x80, &D1);       // SUBI.W	#$0080,D1
  DEF_ROMLOC(8F48) : and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
  DEF_ROMLOC(8F4C) : sub_toreg_16(D1, &D0);         // SUB.W	D1,D0
  DEF_ROMLOC(8F4E) : cmp_toreg_16(0x280, &D0);      // CMPI.W	#$0280,D0
  DEF_ROMLOC(8F52) : if (CCR_HI) {
    rom_8F58();
    return;
  }                          // BHI.W	$8F58
  DEF_ROMLOC(8F56) : return; // RTS
}
ROMFUNC(rom_8F58) {
  DEF_ROMLOC(8F58) : rom_DCCE(); // BSR.W	$DCCE
  DEF_ROMLOC(8F5C) : return;     // RTS
}
ROMFUNC(rom_8F5E) {
  DEF_ROMLOC(8F5E) : move_toreg_32(0xFFFFD000, &A1); // LEA.L	$D000,A1
  DEF_ROMLOC(8F62)
      : move_toreg_16(read_16(A1 + 0x8), &D0); // MOVE.W	8(A1),D0
  DEF_ROMLOC(8F66)
      : sub_toreg_16(read_16(A0 + 0x8), &D0);   // SUB.W	8(A0),D0
  DEF_ROMLOC(8F6A) : add_toreg_16(D1, &D0);     // ADD.W	D1,D0
  DEF_ROMLOC(8F6C) : if (CCR_MI) goto rom_8F96; // BMI.B	$8F96
  DEF_ROMLOC(8F6E) : add_toreg_16(D1, &D1);     // ADD.W	D1,D1
  DEF_ROMLOC(8F70) : cmp_toreg_16(D1, &D0);     // CMP.W	D1,D0
  DEF_ROMLOC(8F72) : if (CCR_CC) goto rom_8F96; // BCC.B	$8F96
  DEF_ROMLOC(8F74)
      : move_toreg_16(read_16(A1 + 0xC), &D2); // MOVE.W	12(A1),D2
  DEF_ROMLOC(8F78)
      : move_toreg_8(read_8(A1 + 0x16), &D1); // MOVE.B	22(A1),D1
  DEF_ROMLOC(8F7C) : ext_reg_16(&D1);         // EXT.W	D1
  DEF_ROMLOC(8F7E) : add_toreg_16(D2, &D1);   // ADD.W	D2,D1
  DEF_ROMLOC(8F80)
      : move_toreg_16(read_16(A0 + 0xC), &D0);       // MOVE.W	12(A0),D0
  DEF_ROMLOC(8F84) : sub_toreg_16(0x10, &D0);        // SUBI.W	#$0010,D0
  DEF_ROMLOC(8F88) : sub_toreg_16(D1, &D0);          // SUB.W	D1,D0
  DEF_ROMLOC(8F8A) : if (CCR_HI) goto rom_8F96;      // BHI.B	$8F96
  DEF_ROMLOC(8F8C) : cmp_toreg_16(0xFFFFFFF0, &D0);  // CMPI.W	#$FFF0,D0
  DEF_ROMLOC(8F90) : if (CCR_CS) goto rom_8F96;      // BCS.B	$8F96
  DEF_ROMLOC(8F92) : move_toreg_32(0xFFFFFFFF, &D0); // MOVEQ.L	$FF,D0
  DEF_ROMLOC(8F94) : return;                         // RTS
  DEF_ROMLOC(8F96) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(8F98) : return;                         // RTS
}