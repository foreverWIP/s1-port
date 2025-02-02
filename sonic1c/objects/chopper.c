// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"


ROMFUNC(rom_B1AA) {
  u8 switchindex = 0;
  DEF_ROMLOC(B1AA) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(B1AC) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(B1B0)
      : move_toreg_16(read_16(0xB1BC + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	10(PC,D0),D1
  // DEF_ROMLOC(B1B4): rom_B1BC + (s16)(D1 & 0xffff)(); // JSR	6(PC,D1)
  DEF_ROMLOC(B1B4) : switch (switchindex) {
  case 0:
    rom_B1C0();
    break;
  case 1:
    rom_B1F6();
    break;
  }
  DEF_ROMLOC(B1B8) : rom_FD38(); // BRA.W	$FD38
}
ROMFUNC(rom_B1C0) {
  DEF_ROMLOC(B1C0) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(B1C4)
      : move_tomem_32(0xB254, A0 + 0x4);             // MOVE.L	#$0000B254,4(A0)
  DEF_ROMLOC(B1CC) : move_tomem_16(0x47B, A0 + 0x2); // MOVE.W	#$047B,2(A0)
  DEF_ROMLOC(B1D2) : move_tomem_8(0x4, A0 + 0x1);    // MOVE.B	#$04,1(A0)
  DEF_ROMLOC(B1D8) : move_tomem_8(0x4, A0 + 0x18);   // MOVE.B	#$04,24(A0)
  DEF_ROMLOC(B1DE) : move_tomem_8(0x9, A0 + 0x20);   // MOVE.B	#$09,32(A0)
  DEF_ROMLOC(B1E4) : move_tomem_8(0x10, A0 + 0x19);  // MOVE.B	#$10,25(A0)
  DEF_ROMLOC(B1EA)
      : move_tomem_16(0xFFFFF900, A0 + 0x12); // MOVE.W	#$F900,18(A0)
  DEF_ROMLOC(B1F0)
      : move_tomem_16(read_16(A0 + 0xC), A0 + 0x30); // MOVE.W	12(A0),48(A0)
  rom_B1F6(); // Detected flow into next function
}
ROMFUNC(rom_B1F6) {
  DEF_ROMLOC(B1F6) : move_toreg_32(0xB242, &A1);    // LEA.L	$0000B242,A1
  DEF_ROMLOC(B1FC) : animate_sprite();                    // BSR.W	$ADA2
  DEF_ROMLOC(B200) : rom_DC6C();                    // BSR.W	$DC6C
  DEF_ROMLOC(B204) : add_tomem_16(0x18, A0 + 0x12); // ADDI.W	#$0018,18(A0)
  DEF_ROMLOC(B20A)
      : move_toreg_16(read_16(A0 + 0x30), &D0); // MOVE.W	48(A0),D0
  DEF_ROMLOC(B20E)
      : cmp_toreg_16(read_16(A0 + 0xC), &D0);     // CMP.W	12(A0),D0
  DEF_ROMLOC(B212) : if (CCR_CC) goto rom_B21E;   // BCC.B	$B21E
  DEF_ROMLOC(B214) : move_tomem_16(D0, A0 + 0xC); // MOVE.W	D0,12(A0)
  DEF_ROMLOC(B218)
      : move_tomem_16(0xFFFFF900, A0 + 0x12);      // MOVE.W	#$F900,18(A0)
  DEF_ROMLOC(B21E) : move_tomem_8(0x1, A0 + 0x1C); // MOVE.B	#$01,28(A0)
  DEF_ROMLOC(B224) : sub_toreg_16(0xC0, &D0);      // SUBI.W	#$00C0,D0
  DEF_ROMLOC(B228)
      : cmp_toreg_16(read_16(A0 + 0xC), &D0);      // CMP.W	12(A0),D0
  DEF_ROMLOC(B22C) : if (CCR_CC) goto rom_B240;    // BCC.B	$B240
  DEF_ROMLOC(B22E) : move_tomem_8(0x0, A0 + 0x1C); // MOVE.B	#$00,28(A0)
  DEF_ROMLOC(B234) : tst_mem_16(A0 + 0x12);        // TST.W	18(A0)
  DEF_ROMLOC(B238) : if (CCR_MI) goto rom_B240;    // BMI.B	$B240
  DEF_ROMLOC(B23A) : move_tomem_8(0x2, A0 + 0x1C); // MOVE.B	#$02,28(A0)
  DEF_ROMLOC(B240) : return;                       // RTS
}