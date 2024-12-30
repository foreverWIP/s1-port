// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"


ROMFUNC(rom_929A) {
  u8 switchindex = 0;
  DEF_ROMLOC(929A) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(929C) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(92A0)
      : move_toreg_16(read_16(0x92A8 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(92A4): goto rom_92A8 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(92A4) : switch (switchindex) {
  case 0:
    rom_92AC();
    break;
  case 1:
    rom_92F0();
    break;
  }
}
ROMFUNC(rom_92AC) {
  DEF_ROMLOC(92AC) : add_tomem_8(0x2, A0 + 0x24);  // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(92B0) : move_tomem_8(0x7, A0 + 0x16); // MOVE.B	#$07,22(A0)
  DEF_ROMLOC(92B6)
      : move_tomem_32(0x94E0, A0 + 0x4);              // MOVE.L	#$000094E0,4(A0)
  DEF_ROMLOC(92BE) : move_tomem_16(0x2302, A0 + 0x2); // MOVE.W	#$2302,2(A0)
  DEF_ROMLOC(92C4) : move_tomem_8(0x4, A0 + 0x1);     // MOVE.B	#$04,1(A0)
  DEF_ROMLOC(92CA) : move_tomem_8(0x3, A0 + 0x18);    // MOVE.B	#$03,24(A0)
  DEF_ROMLOC(92D0)
      : move_tomem_8(0xFFFFFF87, A0 + 0x20);       // MOVE.B	#$87,32(A0)
  DEF_ROMLOC(92D6) : move_tomem_8(0x8, A0 + 0x19); // MOVE.B	#$08,25(A0)
  DEF_ROMLOC(92DC) : move_toreg_32(0x0, &D0);      // MOVEQ.L	$00,D0
  DEF_ROMLOC(92DE)
      : move_toreg_8(read_8(A0 + 0x28), &D0);      // MOVE.B	40(A0),D0
  DEF_ROMLOC(92E2) : mulu_toreg_16(0x3C, &D0);     // MULU.W	#$003C,D0
  DEF_ROMLOC(92E6) : move_tomem_16(D0, A0 + 0x30); // MOVE.W	D0,48(A0)
  DEF_ROMLOC(92EA) : move_tomem_8(0x4, A0 + 0x1A); // MOVE.B	#$04,26(A0)
  rom_92F0(); // Detected flow into next function
}
ROMFUNC(rom_92F0) {
  DEF_ROMLOC(92F0) : rom_DC40();                 // JSR	$0000DC40
  DEF_ROMLOC(92F6) : tst_mem_16(A0 + 0x12);      // TST.W	18(A0)
  DEF_ROMLOC(92FA) : if (CCR_MI) goto rom_932C;  // BMI.B	$932C
  DEF_ROMLOC(92FC) : rom_15580();                // JSR	$00015580
  DEF_ROMLOC(9302) : tst_reg_16(&D1);            // TST.W	D1
  DEF_ROMLOC(9304) : if (CCR_PL) goto rom_932C;  // BPL.B	$932C
  DEF_ROMLOC(9306) : add_tomem_16(D1, A0 + 0xC); // ADD.W	D1,12(A0)
  DEF_ROMLOC(930A)
      : move_tomem_16(0xFFFFFD00, A0 + 0x12);      // MOVE.W	#$FD00,18(A0)
  DEF_ROMLOC(9310) : tst_reg_8(&D3);               // TST.B	D3
  DEF_ROMLOC(9312) : if (CCR_EQ) goto rom_932C;    // BEQ.B	$932C
  DEF_ROMLOC(9314) : if (CCR_MI) goto rom_9322;    // BMI.B	$9322
  DEF_ROMLOC(9316) : tst_mem_16(A0 + 0x10);        // TST.W	16(A0)
  DEF_ROMLOC(931A) : if (CCR_PL) goto rom_932C;    // BPL.B	$932C
  DEF_ROMLOC(931C) : neg_mem_16(A0 + 0x10);        // NEG.W	16(A0)
  goto rom_932C;                                   // BRA.B	$932C
  DEF_ROMLOC(9322) : tst_mem_16(A0 + 0x10);        // TST.W	16(A0)
  DEF_ROMLOC(9326) : if (CCR_MI) goto rom_932C;    // BMI.B	$932C
  DEF_ROMLOC(9328) : neg_mem_16(A0 + 0x10);        // NEG.W	16(A0)
  DEF_ROMLOC(932C) : sub_tomem_16(0x1, A0 + 0x30); // SUBQ.W	#$01,48(A0)
  DEF_ROMLOC(9330) : if (CCR_PL) goto rom_9348;    // BPL.B	$9348
  DEF_ROMLOC(9332) : move_tomem_8(0x24, A0 + 0x0); // MOVE.B	#$24,0(A0)
  DEF_ROMLOC(9338) : move_tomem_8(0x3F, A0 + 0x0); // MOVE.B	#$3F,0(A0)
  DEF_ROMLOC(933E) : move_tomem_8(0x0, A0 + 0x24); // MOVE.B	#$00,36(A0)
  rom_9474();
  return;                                          // BRA.W	$9474
  DEF_ROMLOC(9348) : sub_tomem_8(0x1, A0 + 0x1E);  // SUBQ.B	#$01,30(A0)
  DEF_ROMLOC(934C) : if (CCR_PL) goto rom_935A;    // BPL.B	$935A
  DEF_ROMLOC(934E) : move_tomem_8(0x5, A0 + 0x1E); // MOVE.B	#$05,30(A0)
  DEF_ROMLOC(9354) : bchg_tomem_8(0x0, A0 + 0x1A); // BCHG.B	#$00,26(A0)
  DEF_ROMLOC(935A) : rom_DC92();                   // BSR.W	$DC92
  DEF_ROMLOC(935E)
      : move_toreg_16(read_16(0xFFFFF72E), &D0); // MOVE.W	$F72E,D0
  DEF_ROMLOC(9362) : add_toreg_16(0xE0, &D0);    // ADDI.W	#$00E0,D0
  DEF_ROMLOC(9366)
      : cmp_toreg_16(read_16(A0 + 0xC), &D0); // CMP.W	12(A0),D0
  DEF_ROMLOC(936A) : if (CCR_CS) {
    rom_DCCE();
    return;
  }                          // BCS.W	$DCCE
  DEF_ROMLOC(936E) : return; // RTS
}