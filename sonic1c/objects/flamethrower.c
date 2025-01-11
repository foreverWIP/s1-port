// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_EB6E) {
  u8 switchindex = 0;
  DEF_ROMLOC(EB6E) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(EB70) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(EB74)
      : move_toreg_16(read_16(0xEB7C + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(EB78): goto rom_EB7C + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(EB78) : switch (switchindex) {
  case 0:
    rom_EB80();
    break;
  case 1:
    rom_EBE4();
    break;
  }
}
ROMFUNC(rom_EB80) {
  DEF_ROMLOC(EB80) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(EB84)
      : move_tomem_32(0xEC82, A0 + 0x4); // MOVE.L	#$0000EC82,4(A0)
  DEF_ROMLOC(EB8C)
      : move_tomem_16(0xFFFF83D9, A0 + 0x2);       // MOVE.W	#$83D9,2(A0)
  DEF_ROMLOC(EB92) : or_tomem_8(0x4, A0 + 0x1);    // ORI.B	#$04,1(A0)
  DEF_ROMLOC(EB98) : move_tomem_8(0x1, A0 + 0x18); // MOVE.B	#$01,24(A0)
  DEF_ROMLOC(EB9E)
      : move_tomem_16(read_16(A0 + 0xC), A0 + 0x30); // MOVE.W	12(A0),48(A0)
  DEF_ROMLOC(EBA4) : move_tomem_8(0xC, A0 + 0x19);   // MOVE.B	#$0C,25(A0)
  DEF_ROMLOC(EBAA)
      : move_toreg_8(read_8(A0 + 0x28), &D0);      // MOVE.B	40(A0),D0
  DEF_ROMLOC(EBAE) : and_toreg_16(0xF0, &D0);      // ANDI.W	#$00F0,D0
  DEF_ROMLOC(EBB2) : add_toreg_16(D0, &D0);        // ADD.W	D0,D0
  DEF_ROMLOC(EBB4) : move_tomem_16(D0, A0 + 0x30); // MOVE.W	D0,48(A0)
  DEF_ROMLOC(EBB8) : move_tomem_16(D0, A0 + 0x32); // MOVE.W	D0,50(A0)
  DEF_ROMLOC(EBBC)
      : move_toreg_8(read_8(A0 + 0x28), &D0);      // MOVE.B	40(A0),D0
  DEF_ROMLOC(EBC0) : and_toreg_16(0xF, &D0);       // ANDI.W	#$000F,D0
  DEF_ROMLOC(EBC4) : lsl_toreg_16(0x5, &D0);       // LSL.W	#$05,D0
  DEF_ROMLOC(EBC6) : move_tomem_16(D0, A0 + 0x34); // MOVE.W	D0,52(A0)
  DEF_ROMLOC(EBCA) : move_tomem_8(0xA, A0 + 0x36); // MOVE.B	#$0A,54(A0)
  DEF_ROMLOC(EBD0) : btst_tomem_8(0x1, A0 + 0x22); // BTST.B	#$01,34(A0)
  DEF_ROMLOC(EBD6) : if (CCR_EQ) {
    rom_EBE4();
    return;
  }                                                 // BEQ.B	$EBE4
  DEF_ROMLOC(EBD8) : move_tomem_8(0x2, A0 + 0x1C);  // MOVE.B	#$02,28(A0)
  DEF_ROMLOC(EBDE) : move_tomem_8(0x15, A0 + 0x36); // MOVE.B	#$15,54(A0)
  rom_EBE4(); // Detected flow into next function
}
ROMFUNC(rom_EBE4) {
  DEF_ROMLOC(EBE4) : sub_tomem_16(0x1, A0 + 0x30); // SUBQ.W	#$01,48(A0)
  DEF_ROMLOC(EBE8) : if (CCR_PL) goto rom_EC08;    // BPL.B	$EC08
  DEF_ROMLOC(EBEA)
      : move_tomem_16(read_16(A0 + 0x34), A0 + 0x30); // MOVE.W	52(A0),48(A0)
  DEF_ROMLOC(EBF0) : bchg_tomem_8(0x0, A0 + 0x1C);    // BCHG.B	#$00,28(A0)
  DEF_ROMLOC(EBF6) : if (CCR_EQ) goto rom_EC08;       // BEQ.B	$EC08
  DEF_ROMLOC(EBF8)
      : move_tomem_16(read_16(A0 + 0x32), A0 + 0x30); // MOVE.W	50(A0),48(A0)
  DEF_ROMLOC(EBFE) : move_toreg_16(0xB3, &D0);        // MOVE.W	#$00B3,D0
  DEF_ROMLOC(EC02) : play_sound_special();            // JSR	$00001394
  DEF_ROMLOC(EC08) : move_toreg_32(0xEC4A, &A1);      // LEA.L	$0000EC4A,A1
  DEF_ROMLOC(EC0E) : rom_ADA2();                      // BSR.W	$ADA2
  DEF_ROMLOC(EC12) : move_tomem_8(0x0, A0 + 0x20);    // MOVE.B	#$00,32(A0)
  DEF_ROMLOC(EC18)
      : move_toreg_8(read_8(A0 + 0x36), &D0); // MOVE.B	54(A0),D0
  DEF_ROMLOC(EC1C)
      : cmp_toreg_8(read_8(A0 + 0x1A), &D0);                // CMP.B
                                                            // 26(A0),D0
  DEF_ROMLOC(EC20) : if (!CCR_EQ) goto rom_EC28;            // BNE.B	$EC28
  DEF_ROMLOC(EC22) : move_tomem_8(0xFFFFFFA3, A0 + 0x20);   // MOVE.B
                                                            // #$A3,32(A0)
  DEF_ROMLOC(EC28) : move_toreg_16(read_16(A0 + 0x8), &D0); // MOVE.W	8(A0),D0
  DEF_ROMLOC(EC2C) : and_toreg_16(0xFFFFFF80, &D0);         // ANDI.W	#$FF80,D0
  DEF_ROMLOC(EC30)
      : move_toreg_16(read_16(0xFFFFF700), &D1);    // MOVE.W	$F700,D1
  DEF_ROMLOC(EC34) : sub_toreg_16(0x80, &D1);       // SUBI.W	#$0080,D1
  DEF_ROMLOC(EC38) : and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
  DEF_ROMLOC(EC3C) : sub_toreg_16(D1, &D0);         // SUB.W	D1,D0
  DEF_ROMLOC(EC3E) : cmp_toreg_16(0x280, &D0);      // CMPI.W	#$0280,D0
  DEF_ROMLOC(EC42) : if (CCR_HI) {
    rom_DCCE();
    return;
  }           // BHI.W	$DCCE
  rom_DC92(); // BRA.W	$DC92
}