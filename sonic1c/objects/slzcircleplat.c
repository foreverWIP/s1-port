// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_1142E) {
  u8 switchindex = 0;
  DEF_ROMLOC(1142E) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(11430) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(11434)
      : move_toreg_16(read_16(0x1145E + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	40(PC,D0),D1
  // DEF_ROMLOC(11438): rom_1145E + (s16)(D1 & 0xffff)(); // JSR
  // 36(PC,D1)
  DEF_ROMLOC(11438) : switch (switchindex) {
  case 0:
    rom_11464();
    break;
  case 1:
    rom_11494();
    break;
  case 2:
    rom_114A4();
    break;
  }
  DEF_ROMLOC(1143C)
      : move_toreg_16(read_16(A0 + 0x32), &D0);      // MOVE.W	50(A0),D0
  DEF_ROMLOC(11440) : and_toreg_16(0xFFFFFF80, &D0); // ANDI.W	#$FF80,D0
  DEF_ROMLOC(11444)
      : move_toreg_16(read_16(v_screenposx), &D1);   // MOVE.W	$F700,D1
  DEF_ROMLOC(11448) : sub_toreg_16(0x80, &D1);       // SUBI.W	#$0080,D1
  DEF_ROMLOC(1144C) : and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
  DEF_ROMLOC(11450) : sub_toreg_16(D1, &D0);         // SUB.W	D1,D0
  DEF_ROMLOC(11452) : cmp_toreg_16(0x280, &D0);      // CMPI.W	#$0280,D0
  DEF_ROMLOC(11456) : if (CCR_HI) {
    rom_DCCE();
    return;
  } // BHI.W	$DCCE
  DEF_ROMLOC(1145A) : rom_DC92(); // BRA.W	$DC92
}
ROMFUNC(rom_11464) {
  DEF_ROMLOC(11464) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(11468)
      : move_tomem_32(0x11556, A0 + 0x4); // MOVE.L	#$00011556,4(A0)
  DEF_ROMLOC(11470)
      : move_tomem_16(0x4000, A0 + 0x2);            // MOVE.W
                                                    // #$4000,2(A0)
  DEF_ROMLOC(11476) : move_tomem_8(0x4, A0 + 0x1);  // MOVE.B	#$04,1(A0)
  DEF_ROMLOC(1147C) : move_tomem_8(0x4, A0 + 0x18); // MOVE.B	#$04,24(A0)
  DEF_ROMLOC(11482)
      : move_tomem_8(0x18, A0 + 0x19); // MOVE.B	#$18,25(A0)
  DEF_ROMLOC(11488)
      : move_tomem_16(read_16(A0 + 0x8), A0 + 0x32); // MOVE.W	8(A0),50(A0)
  DEF_ROMLOC(1148E)
      : move_tomem_16(read_16(A0 + 0xC), A0 + 0x30); // MOVE.W	12(A0),48(A0)
  rom_11494(); // Detected flow into next function
}
ROMFUNC(rom_11494) {
  DEF_ROMLOC(11494) : move_toreg_32(0x0, &D1);              // MOVEQ.L	$00,D1
  DEF_ROMLOC(11496) : move_toreg_8(read_8(A0 + 0x19), &D1); // MOVE.B
                                                            // 25(A0),D1
  DEF_ROMLOC(1149A) : rom_7ACA();                           // JSR	$00007ACA
  rom_114C0();                                              // BRA.W	$114C0
}
ROMFUNC(rom_114A4) {
  DEF_ROMLOC(114A4) : move_toreg_32(0x0, &D1);              // MOVEQ.L	$00,D1
  DEF_ROMLOC(114A6) : move_toreg_8(read_8(A0 + 0x19), &D1); // MOVE.B
                                                            // 25(A0),D1
  DEF_ROMLOC(114AA) : rom_7C3E();                           // JSR	$00007C3E
  DEF_ROMLOC(114B0)
      : move_tomem_16(read_16(A0 + 0x8), A7 -= 2); // MOVE.W	8(A0),-(A7)
  DEF_ROMLOC(114B4) : rom_114C0();                 // BSR.W	$114C0
  DEF_ROMLOC(114B8)
      : move_toreg_16(read_16((A7 += 2, A7 - 2)), &D2); // MOVE.W	(A7)+,D2
  DEF_ROMLOC(114BA) : rom_81AC();
  return; // JMP	$000081AC
}
ROMFUNC(rom_114D8);
ROMFUNC(rom_11516);
ROMFUNC(rom_114C0) {
  u8 switchindex = 0;
  DEF_ROMLOC(114C0) : move_toreg_32(0x0, &D0);              // MOVEQ.L	$00,D0
  DEF_ROMLOC(114C2) : move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B
                                                            // 40(A0),D0
  DEF_ROMLOC(114C6) : and_toreg_16(0xC, &D0);
  switchindex = D0 / 4;                       // ANDI.W	#$000C,D0
  DEF_ROMLOC(114CA) : lsr_toreg_16(0x1, &D0); // LSR.W	#$01,D0
  DEF_ROMLOC(114CC)
      : move_toreg_16(read_16(0x114D4 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(114D0): goto rom_114D4 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(114D0) : switch (switchindex) {
  case 0:
    rom_114D8();
    break;
  case 1:
    rom_11516();
    break;
  }
}
ROMFUNC(rom_114D8) {
  DEF_ROMLOC(114D8)
      : move_toreg_8(read_8(0xFFFFFE80), &D1); // MOVE.B	$FE80,D1
  DEF_ROMLOC(114DC) : sub_toreg_8(0x50, &D1);  // SUBI.B	#$50,D1
  DEF_ROMLOC(114E0) : ext_reg_16(&D1);         // EXT.W	D1
  DEF_ROMLOC(114E2)
      : move_toreg_8(read_8(0xFFFFFE84), &D2);      // MOVE.B	$FE84,D2
  DEF_ROMLOC(114E6) : sub_toreg_8(0x50, &D2);       // SUBI.B	#$50,D2
  DEF_ROMLOC(114EA) : ext_reg_16(&D2);              // EXT.W	D2
  DEF_ROMLOC(114EC) : btst_tomem_8(0x0, A0 + 0x28); // BTST.B	#$00,40(A0)
  DEF_ROMLOC(114F2) : if (CCR_EQ) goto rom_114F8;   // BEQ.B	$114F8
  DEF_ROMLOC(114F4) : neg_reg_16(&D1);              // NEG.W	D1
  DEF_ROMLOC(114F6) : neg_reg_16(&D2);              // NEG.W	D2
  DEF_ROMLOC(114F8) : btst_tomem_8(0x1, A0 + 0x28); // BTST.B	#$01,40(A0)
  DEF_ROMLOC(114FE) : if (CCR_EQ) goto rom_11504;   // BEQ.B	$11504
  DEF_ROMLOC(11500) : neg_reg_16(&D1);              // NEG.W	D1
  DEF_ROMLOC(11502) : exg_toreg_32(&D1, &D2);       // EXG.L	D1,D2
  DEF_ROMLOC(11504)
      : add_toreg_16(read_16(A0 + 0x32), &D1);     // ADD.W	50(A0),D1
  DEF_ROMLOC(11508) : move_tomem_16(D1, A0 + 0x8); // MOVE.W	D1,8(A0)
  DEF_ROMLOC(1150C)
      : add_toreg_16(read_16(A0 + 0x30), &D2);     // ADD.W	48(A0),D2
  DEF_ROMLOC(11510) : move_tomem_16(D2, A0 + 0xC); // MOVE.W	D2,12(A0)
  DEF_ROMLOC(11514) : return;                      // RTS
}
ROMFUNC(rom_11516) {
  DEF_ROMLOC(11516)
      : move_toreg_8(read_8(0xFFFFFE80), &D1); // MOVE.B	$FE80,D1
  DEF_ROMLOC(1151A) : sub_toreg_8(0x50, &D1);  // SUBI.B	#$50,D1
  DEF_ROMLOC(1151E) : ext_reg_16(&D1);         // EXT.W	D1
  DEF_ROMLOC(11520)
      : move_toreg_8(read_8(0xFFFFFE84), &D2);      // MOVE.B	$FE84,D2
  DEF_ROMLOC(11524) : sub_toreg_8(0x50, &D2);       // SUBI.B	#$50,D2
  DEF_ROMLOC(11528) : ext_reg_16(&D2);              // EXT.W	D2
  DEF_ROMLOC(1152A) : btst_tomem_8(0x0, A0 + 0x28); // BTST.B	#$00,40(A0)
  DEF_ROMLOC(11530) : if (CCR_EQ) goto rom_11536;   // BEQ.B	$11536
  DEF_ROMLOC(11532) : neg_reg_16(&D1);              // NEG.W	D1
  DEF_ROMLOC(11534) : neg_reg_16(&D2);              // NEG.W	D2
  DEF_ROMLOC(11536) : btst_tomem_8(0x1, A0 + 0x28); // BTST.B	#$01,40(A0)
  DEF_ROMLOC(1153C) : if (CCR_EQ) goto rom_11542;   // BEQ.B	$11542
  DEF_ROMLOC(1153E) : neg_reg_16(&D1);              // NEG.W	D1
  DEF_ROMLOC(11540) : exg_toreg_32(&D1, &D2);       // EXG.L	D1,D2
  DEF_ROMLOC(11542) : neg_reg_16(&D1);              // NEG.W	D1
  DEF_ROMLOC(11544)
      : add_toreg_16(read_16(A0 + 0x32), &D1);     // ADD.W	50(A0),D1
  DEF_ROMLOC(11548) : move_tomem_16(D1, A0 + 0x8); // MOVE.W	D1,8(A0)
  DEF_ROMLOC(1154C)
      : add_toreg_16(read_16(A0 + 0x30), &D2);     // ADD.W	48(A0),D2
  DEF_ROMLOC(11550) : move_tomem_16(D2, A0 + 0xC); // MOVE.W	D2,12(A0)
  DEF_ROMLOC(11554) : return;                      // RTS
}