// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"


ROMFUNC(rom_B264) {
  u8 switchindex = 0;
  DEF_ROMLOC(B264) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(B266) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(B26A)
      : move_toreg_16(read_16(0xB272 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(B26E): goto rom_B272 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(B26E) : switch (switchindex) {
  case 0:
    rom_B276();
    break;
  case 1:
    rom_B2C4();
    break;
  }
}
ROMFUNC(rom_B276) {
  DEF_ROMLOC(B276) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(B27A)
      : move_tomem_32(0xB2FA, A0 + 0x4);              // MOVE.L	#$0000B2FA,4(A0)
  DEF_ROMLOC(B282) : move_tomem_16(0x2486, A0 + 0x2); // MOVE.W	#$2486,2(A0)
  DEF_ROMLOC(B288) : or_tomem_8(0x4, A0 + 0x1);       // ORI.B	#$04,1(A0)
  DEF_ROMLOC(B28E) : move_tomem_8(0xA, A0 + 0x20);    // MOVE.B	#$0A,32(A0)
  DEF_ROMLOC(B294) : move_tomem_8(0x4, A0 + 0x18);    // MOVE.B	#$04,24(A0)
  DEF_ROMLOC(B29A) : move_tomem_8(0x10, A0 + 0x19);   // MOVE.B	#$10,25(A0)
  DEF_ROMLOC(B2A0) : move_toreg_32(0x0, &D0);         // MOVEQ.L	$00,D0
  DEF_ROMLOC(B2A2)
      : move_toreg_8(read_8(A0 + 0x28), &D0);      // MOVE.B	40(A0),D0
  DEF_ROMLOC(B2A6) : lsl_toreg_16(0x6, &D0);       // LSL.W	#$06,D0
  DEF_ROMLOC(B2A8) : sub_toreg_16(0x1, &D0);       // SUBQ.W	#$01,D0
  DEF_ROMLOC(B2AA) : move_tomem_16(D0, A0 + 0x30); // MOVE.W	D0,48(A0)
  DEF_ROMLOC(B2AE) : move_tomem_16(D0, A0 + 0x32); // MOVE.W	D0,50(A0)
  DEF_ROMLOC(B2B2)
      : move_tomem_16(0xFFFFFFC0, A0 + 0x10);      // MOVE.W	#$FFC0,16(A0)
  DEF_ROMLOC(B2B8) : btst_tomem_8(0x0, A0 + 0x22); // BTST.B	#$00,34(A0)
  DEF_ROMLOC(B2BE) : if (CCR_EQ) {
    rom_B2C4();
    return;
  }                                         // BEQ.B	$B2C4
  DEF_ROMLOC(B2C0) : neg_mem_16(A0 + 0x10); // NEG.W	16(A0)
  rom_B2C4();                               // Detected flow into next function
}
ROMFUNC(rom_B2C4) {
  DEF_ROMLOC(B2C4) : sub_tomem_16(0x1, A0 + 0x30); // SUBQ.W	#$01,48(A0)
  DEF_ROMLOC(B2C8) : if (CCR_PL) goto rom_B2E0;    // BPL.B	$B2E0
  DEF_ROMLOC(B2CA)
      : move_tomem_16(read_16(A0 + 0x32), A0 + 0x30); // MOVE.W	50(A0),48(A0)
  DEF_ROMLOC(B2D0) : neg_mem_16(A0 + 0x10);           // NEG.W	16(A0)
  DEF_ROMLOC(B2D4) : bchg_tomem_8(0x0, A0 + 0x22);    // BCHG.B	#$00,34(A0)
  DEF_ROMLOC(B2DA) : move_tomem_8(0x1, A0 + 0x1D);    // MOVE.B	#$01,29(A0)
  DEF_ROMLOC(B2E0) : move_toreg_32(0xB2F2, &A1);      // LEA.L	$0000B2F2,A1
  DEF_ROMLOC(B2E6) : rom_ADA2();                      // BSR.W	$ADA2
  DEF_ROMLOC(B2EA) : rom_DC6C();                      // BSR.W	$DC6C
  DEF_ROMLOC(B2EE) : {
    rom_FD38();
    return;
  } // BRA.W	$FD38
}