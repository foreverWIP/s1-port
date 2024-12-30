// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_91CA) {
  u8 switchindex = 0;
  DEF_ROMLOC(91CA) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(91CC) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(91D0)
      : move_toreg_16(read_16(0x91D8 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(91D4): goto rom_91D8 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(91D4) : switch (switchindex) {
  case 0:
    rom_91DC();
    break;
  case 1:
    rom_922C();
    break;
  }
}
ROMFUNC(rom_91DC) {
  DEF_ROMLOC(91DC) : move_tomem_8(0x13, A0 + 0x16); // MOVE.B	#$13,22(A0)
  DEF_ROMLOC(91E2) : move_tomem_8(0x8, A0 + 0x17);  // MOVE.B	#$08,23(A0)
  DEF_ROMLOC(91E8)
      : move_tomem_32(0x94E0, A0 + 0x4);              // MOVE.L	#$000094E0,4(A0)
  DEF_ROMLOC(91F0) : move_tomem_16(0x2302, A0 + 0x2); // MOVE.W	#$2302,2(A0)
  DEF_ROMLOC(91F6) : move_tomem_8(0x4, A0 + 0x1);     // MOVE.B	#$04,1(A0)
  DEF_ROMLOC(91FC) : move_tomem_8(0x4, A0 + 0x18);    // MOVE.B	#$04,24(A0)
  DEF_ROMLOC(9202) : move_tomem_8(0x5, A0 + 0x20);    // MOVE.B	#$05,32(A0)
  DEF_ROMLOC(9208) : move_tomem_8(0xC, A0 + 0x19);    // MOVE.B	#$0C,25(A0)
  DEF_ROMLOC(920E) : rom_DC40();                      // BSR.W	$DC40
  DEF_ROMLOC(9212) : rom_15580();                     // JSR	$00015580
  DEF_ROMLOC(9218) : tst_reg_16(&D1);                 // TST.W	D1
  DEF_ROMLOC(921A) : if (CCR_PL) goto rom_922A;       // BPL.B	$922A
  DEF_ROMLOC(921C) : add_tomem_16(D1, A0 + 0xC);      // ADD.W	D1,12(A0)
  DEF_ROMLOC(9220) : move_tomem_16(0x0, A0 + 0x12);   // MOVE.W	#$0000,18(A0)
  DEF_ROMLOC(9226) : add_tomem_8(0x2, A0 + 0x24);     // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(922A) : return;                          // RTS
}
ROMFUNC(rom_922C) {
  DEF_ROMLOC(922C) : move_toreg_32(0x94C6, &A1);  // LEA.L	$000094C6,A1
  DEF_ROMLOC(9232) : rom_ADA2();                  // BSR.W	$ADA2
  DEF_ROMLOC(9236) : cmp_tomem_8(0x1, A0 + 0x1A); // CMPI.B	#$01,26(A0)
  DEF_ROMLOC(923C) : if (!CCR_EQ) goto rom_9246;  // BNE.B	$9246
  DEF_ROMLOC(923E) : tst_mem_8(A0 + 0x32);        // TST.B	50(A0)
  DEF_ROMLOC(9242) : if (CCR_EQ) goto rom_924E;   // BEQ.B	$924E
  DEF_ROMLOC(9244) : goto rom_924A;               // BRA.B	$924A
  DEF_ROMLOC(9246) : clr_mem_8(A0 + 0x32);        // CLR.B	50(A0)
  DEF_ROMLOC(924A) : {
    rom_FD38();
    return;
  }                                                // BRA.W	$FD38
  DEF_ROMLOC(924E) : move_tomem_8(0x1, A0 + 0x32); // MOVE.B	#$01,50(A0)
  DEF_ROMLOC(9254) : rom_E11A();                   // BSR.W	$E11A
  DEF_ROMLOC(9258) : if (!CCR_EQ) goto rom_9298;   // BNE.B	$9298
  DEF_ROMLOC(925A) : move_tomem_8(0x20, A1 + 0x0); // MOVE.B	#$20,0(A1)
  DEF_ROMLOC(9260)
      : move_tomem_16(read_16(A0 + 0x8), A1 + 0x8); // MOVE.W	8(A0),8(A1)
  DEF_ROMLOC(9266)
      : move_tomem_16(read_16(A0 + 0xC), A1 + 0xC); // MOVE.W	12(A0),12(A1)
  DEF_ROMLOC(926C)
      : move_tomem_16(0xFFFFFF00, A1 + 0x10);        // MOVE.W	#$FF00,16(A1)
  DEF_ROMLOC(9272) : move_tomem_16(0x0, A1 + 0x12);  // MOVE.W	#$0000,18(A1)
  DEF_ROMLOC(9278) : move_toreg_32(0xFFFFFFFC, &D0); // MOVEQ.L	$FC,D0
  DEF_ROMLOC(927A) : btst_tomem_8(0x0, A0 + 0x22);   // BTST.B	#$00,34(A0)
  DEF_ROMLOC(9280) : if (CCR_EQ) goto rom_9288;      // BEQ.B	$9288
  DEF_ROMLOC(9282) : neg_reg_16(&D0);                // NEG.W	D0
  DEF_ROMLOC(9284) : neg_mem_16(A1 + 0x10);          // NEG.W	16(A1)
  DEF_ROMLOC(9288) : add_tomem_16(D0, A1 + 0x8);     // ADD.W	D0,8(A1)
  DEF_ROMLOC(928C) : add_tomem_16(0xC, A1 + 0xC);    // ADDI.W	#$000C,12(A1)
  DEF_ROMLOC(9292)
      : move_tomem_8(read_8(A0 + 0x28), A1 + 0x28); // MOVE.B	40(A0),40(A1)
  DEF_ROMLOC(9298) : goto rom_924A;                 // BRA.B	$924A
}