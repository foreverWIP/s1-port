// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"


ROMFUNC(rom_1031E) {
  u8 switchindex = 0;
  DEF_ROMLOC(1031E) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(10320) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(10324)
      : move_toreg_16(read_16(0x10330 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	10(PC,D0),D1
  // DEF_ROMLOC(10328): rom_10330 + (s16)(D1 & 0xffff)(); // JSR	6(PC,D1)
  DEF_ROMLOC(10328) : switch (switchindex) {
  case 0:
    rom_10336();
    break;
  case 1:
    rom_10360();
    break;
  case 2:
    rom_10430();
    break;
  }
  DEF_ROMLOC(1032C) : rom_FD38();
  return; // BRA.W	$FD38
}
ROMFUNC(rom_10336) {
  DEF_ROMLOC(10336) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(1033A)
      : move_tomem_32(0x10460, A0 + 0x4); // MOVE.L	#$00010460,4(A0)
  DEF_ROMLOC(10342) : move_tomem_16(0x42B8, A0 + 0x2); // MOVE.W
                                                       // #$42B8,2(A0)
  DEF_ROMLOC(10348) : move_tomem_8(0x4, A0 + 0x1);     // MOVE.B	#$04,1(A0)
  DEF_ROMLOC(1034E) : move_tomem_8(0x10, A0 + 0x19);   // MOVE.B	#$10,25(A0)
  DEF_ROMLOC(10354) : move_tomem_8(0x4, A0 + 0x18);    // MOVE.B	#$04,24(A0)
  DEF_ROMLOC(1035A)
      : move_tomem_8(read_8(A0 + 0x28), A0 + 0x1A); // MOVE.B	40(A0),26(A0)
  rom_10360(); // Detected flow into next function
}
ROMFUNC(rom_10360) {
  DEF_ROMLOC(10360)
      : move_tomem_16(read_16(0xFFFFF7D0),
                      A0 + 0x34); // MOVE.W	$F7D0,52(A0)
  DEF_ROMLOC(10366)
      : move_tomem_8(read_8(0xFFFFD01C), A0 + 0x32); // MOVE.B	$D01C,50(A0)
  DEF_ROMLOC(1036C) : move_toreg_16(0x1B, &D1);      // MOVE.W	#$001B,D1
  DEF_ROMLOC(10370) : move_toreg_16(0x10, &D2);      // MOVE.W	#$0010,D2
  DEF_ROMLOC(10374) : move_toreg_16(0x11, &D3);      // MOVE.W	#$0011,D3
  DEF_ROMLOC(10378)
      : move_toreg_16(read_16(A0 + 0x8), &D4);      // MOVE.W	8(A0),D4
  DEF_ROMLOC(1037C) : rom_10062();                  // BSR.W	$10062
  DEF_ROMLOC(10380) : btst_tomem_8(0x3, A0 + 0x22); // BTST.B	#$03,34(A0)
  DEF_ROMLOC(10386) : if (!CCR_EQ) goto rom_1038A;  // BNE.B	$1038A
  DEF_ROMLOC(10388) : return;                       // RTS
  DEF_ROMLOC(1038A) : cmp_tomem_8(0x2, A0 + 0x32);  // CMPI.B	#$02,50(A0)
  DEF_ROMLOC(10390) : if (!CCR_EQ) goto rom_10388;  // BNE.B	$10388
  DEF_ROMLOC(10392)
      : move_tomem_16(read_16(A0 + 0x34),
                      0xFFFFF7D0);                  // MOVE.W	52(A0),$F7D0
  DEF_ROMLOC(10398) : bset_tomem_8(0x2, A1 + 0x22); // BSET.B	#$02,34(A1)
  DEF_ROMLOC(1039E) : move_tomem_8(0xE, A1 + 0x16); // MOVE.B	#$0E,22(A1)
  DEF_ROMLOC(103A4) : move_tomem_8(0x7, A1 + 0x17); // MOVE.B	#$07,23(A1)
  DEF_ROMLOC(103AA) : move_tomem_8(0x2, A1 + 0x1C); // MOVE.B	#$02,28(A1)
  DEF_ROMLOC(103B0)
      : move_tomem_16(0xFFFFFD00, A1 + 0x12);       // MOVE.W	#$FD00,18(A1)
  DEF_ROMLOC(103B6) : bset_tomem_8(0x1, A1 + 0x22); // BSET.B	#$01,34(A1)
  DEF_ROMLOC(103BC) : bclr_tomem_8(0x3, A1 + 0x22); // BCLR.B	#$03,34(A1)
  DEF_ROMLOC(103C2) : move_tomem_8(0x2, A1 + 0x24); // MOVE.B	#$02,36(A1)
  DEF_ROMLOC(103C8) : bclr_tomem_8(0x3, A0 + 0x22); // BCLR.B	#$03,34(A0)
  DEF_ROMLOC(103CE) : clr_mem_8(A0 + 0x25);         // CLR.B	37(A0)
  DEF_ROMLOC(103D2) : move_tomem_8(0x1, A0 + 0x1A); // MOVE.B	#$01,26(A0)
  DEF_ROMLOC(103D8) : move_toreg_32(0x10448, &A4);  // LEA.L	$00010448,A4
  DEF_ROMLOC(103DE) : move_toreg_32(0x3, &D1);      // MOVEQ.L	$03,D1
  DEF_ROMLOC(103E0) : move_toreg_16(0x38, &D2);     // MOVE.W	#$0038,D2
  DEF_ROMLOC(103E4) : rom_D87C();                   // BSR.W	$D87C
  DEF_ROMLOC(103E8) : rom_E11A();                   // BSR.W	$E11A
  DEF_ROMLOC(103EC) : if (!CCR_EQ) {
    rom_10430();
    return;
  }                                                 // BNE.B	$10430
  DEF_ROMLOC(103EE) : move_tomem_8(0x29, A1 + 0x0); // MOVE.B	#$29,0(A1)
  DEF_ROMLOC(103F4)
      : move_tomem_16(read_16(A0 + 0x8), A1 + 0x8); // MOVE.W	8(A0),8(A1)
  DEF_ROMLOC(103FA)
      : move_tomem_16(read_16(A0 + 0xC), A1 + 0xC); // MOVE.W	12(A0),12(A1)
  DEF_ROMLOC(10400)
      : move_toreg_16(read_16(0xFFFFF7D0), &D2);     // MOVE.W	$F7D0,D2
  DEF_ROMLOC(10404) : add_tomem_16(0x2, 0xFFFFF7D0); // ADDQ.W	#$02,$F7D0
  DEF_ROMLOC(10408) : cmp_toreg_16(0x6, &D2);        // CMPI.W	#$0006,D2
  DEF_ROMLOC(1040C) : if (CCR_CS) goto rom_10410;    // BCS.B	$10410
  DEF_ROMLOC(1040E) : move_toreg_32(0x6, &D2);       // MOVEQ.L	$06,D2
  DEF_ROMLOC(10410) : move_toreg_32(0x0, &D0);       // MOVEQ.L	$00,D0
  DEF_ROMLOC(10412)
      : move_toreg_16(read_16(0x10458 + (s16)(D2 & 0xffff)),
                      &D0);                           // MOVE.W	68(PC,D2),D0
  DEF_ROMLOC(10416) : cmp_tomem_16(0x20, 0xFFFFF7D0); // CMPI.W	#$0020,$F7D0
  DEF_ROMLOC(1041C) : if (CCR_CS) goto rom_10424;     // BCS.B	$10424
  DEF_ROMLOC(1041E) : move_toreg_16(0x3E8, &D0);      // MOVE.W	#$03E8,D0
  DEF_ROMLOC(10422) : move_toreg_32(0xA, &D2);        // MOVEQ.L	$0A,D2
  DEF_ROMLOC(10424) : rom_1CE42();                    // JSR	$0001CE42
  DEF_ROMLOC(1042A) : lsr_toreg_16(0x1, &D2);         // LSR.W	#$01,D2
  DEF_ROMLOC(1042C) : move_tomem_8(D2, A1 + 0x1A);    // MOVE.B	D2,26(A1)
  rom_10430(); // Detected flow into next function
}
ROMFUNC(rom_10430) {
  DEF_ROMLOC(10430) : rom_DC6C();                    // BSR.W	$DC6C
  DEF_ROMLOC(10434) : add_tomem_16(0x38, A0 + 0x12); // ADDI.W	#$0038,18(A0)
  DEF_ROMLOC(1043A) : rom_DC92();                    // BSR.W	$DC92
  DEF_ROMLOC(1043E) : tst_mem_8(A0 + 0x1);           // TST.B	1(A0)
  DEF_ROMLOC(10442) : if (CCR_PL) {
    rom_DCCE();
    return;
  }                           // BPL.W	$DCCE
  DEF_ROMLOC(10446) : return; // RTS
}