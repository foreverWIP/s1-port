// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_1104A) {
  u8 switchindex = 0;
  DEF_ROMLOC(1104A) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(1104C) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(11050)
      : move_toreg_16(read_16(0x11058 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(11054): goto rom_11058 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(11054) : switch (switchindex) {
  case 0:
    rom_1105C();
    break;
  case 1:
    rom_110B6();
    break;
  }
}
ROMFUNC(rom_1105C) {
  DEF_ROMLOC(1105C) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(11060)
      : move_tomem_32(0x11174, A0 + 0x4);             // MOVE.L	#$00011174,4(A0)
  DEF_ROMLOC(11068) : move_tomem_16(0x396, A0 + 0x2); // MOVE.W	#$0396,2(A0)
  DEF_ROMLOC(1106E) : move_tomem_8(0x4, A0 + 0x1);    // MOVE.B	#$04,1(A0)
  DEF_ROMLOC(11074) : move_tomem_8(0x4, A0 + 0x18);   // MOVE.B	#$04,24(A0)
  DEF_ROMLOC(1107A) : move_tomem_8(0x18, A0 + 0x19);  // MOVE.B	#$18,25(A0)
  DEF_ROMLOC(11080)
      : move_tomem_16(read_16(A0 + 0x8), A0 + 0x3A); // MOVE.W	8(A0),58(A0)
  DEF_ROMLOC(11086)
      : move_tomem_16(read_16(A0 + 0xC), A0 + 0x38); // MOVE.W	12(A0),56(A0)
  DEF_ROMLOC(1108C)
      : move_tomem_8(0xFFFFFF86, A0 + 0x20); // MOVE.B	#$86,32(A0)
  DEF_ROMLOC(11092)
      : move_toreg_8(read_8(A0 + 0x28), &D1);       // MOVE.B	40(A0),D1
  DEF_ROMLOC(11096) : and_toreg_8(0xFFFFFFF0, &D1); // ANDI.B	#$F0,D1
  DEF_ROMLOC(1109A) : ext_reg_16(&D1);              // EXT.W	D1
  DEF_ROMLOC(1109C) : asl_toreg_16(0x3, &D1);       // ASL.W	#$03,D1
  DEF_ROMLOC(1109E) : move_tomem_16(D1, A0 + 0x3E); // MOVE.W	D1,62(A0)
  DEF_ROMLOC(110A2)
      : move_toreg_8(read_8(A0 + 0x22), &D0);        // MOVE.B
                                                     // 34(A0),D0
  DEF_ROMLOC(110A6) : ror_toreg_8(0x2, &D0);         // ROR.B	#$02,D0
  DEF_ROMLOC(110A8) : and_toreg_8(0xFFFFFFC0, &D0);  // ANDI.B	#$C0,D0
  DEF_ROMLOC(110AC) : move_tomem_8(D0, A0 + 0x26);   // MOVE.B	D0,38(A0)
  DEF_ROMLOC(110B0) : move_tomem_8(0x50, A0 + 0x3C); // MOVE.B	#$50,60(A0)
  rom_110B6(); // Detected flow into next function
}
ROMFUNC(rom_110F4);
ROMFUNC(rom_110F6);
ROMFUNC(rom_11118);
ROMFUNC(rom_1113C);
ROMFUNC(rom_110B6) {
  u8 switchindex = 0;
  DEF_ROMLOC(110B6) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(110B8)
      : move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B
                                              // 40(A0),D0
  DEF_ROMLOC(110BC) : and_toreg_16(0x7, &D0);
  switchindex = D0;                          // ANDI.W	#$0007,D0
  DEF_ROMLOC(110C0) : add_toreg_16(D0, &D0); // ADD.W	D0,D0
  DEF_ROMLOC(110C2)
      : move_toreg_16(read_16(0x110EC + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	40(PC,D0),D1
  // DEF_ROMLOC(110C6): rom_110EC + (s16)(D1 & 0xffff)(); // JSR
  // 36(PC,D1)
  DEF_ROMLOC(110C6) : switch (switchindex) {
  case 0:
    rom_110F4();
    break;
  case 1:
    rom_110F6();
    break;
  case 2:
    rom_11118();
    break;
  case 3:
    rom_1113C();
    break;
  }
  DEF_ROMLOC(110CA)
      : move_toreg_16(read_16(A0 + 0x3A), &D0);      // MOVE.W	58(A0),D0
  DEF_ROMLOC(110CE) : and_toreg_16(0xFFFFFF80, &D0); // ANDI.W	#$FF80,D0
  DEF_ROMLOC(110D2)
      : move_toreg_16(read_16(v_screenposx), &D1);   // MOVE.W	$F700,D1
  DEF_ROMLOC(110D6) : sub_toreg_16(0x80, &D1);       // SUBI.W	#$0080,D1
  DEF_ROMLOC(110DA) : and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
  DEF_ROMLOC(110DE) : sub_toreg_16(D1, &D0);         // SUB.W	D1,D0
  DEF_ROMLOC(110E0)
      : cmp_toreg_16(128 + GAME_WIDTH + 192, &D0); // CMPI.W	#$0280,D0
  DEF_ROMLOC(110E4) : if (CCR_HI) {
    rom_DCCE();
    return;
  } // BHI.W	$DCCE
  rom_DC92(); // BRA.W	$DC92
}
ROMFUNC(rom_110F4) {
  DEF_ROMLOC(110F4) : return; // RTS
}
ROMFUNC(rom_110F6) {
  DEF_ROMLOC(110F6) : move_toreg_16(0x60, &D1); // MOVE.W	#$0060,D1
  DEF_ROMLOC(110FA) : move_toreg_32(0x0, &D0);  // MOVEQ.L	$00,D0
  DEF_ROMLOC(110FC)
      : move_toreg_8(read_8(0xFFFFFE6C), &D0);      // MOVE.B	$FE6C,D0
  DEF_ROMLOC(11100) : btst_tomem_8(0x0, A0 + 0x22); // BTST.B	#$00,34(A0)
  DEF_ROMLOC(11106) : if (CCR_EQ) goto rom_1110C;   // BEQ.B	$1110C
  DEF_ROMLOC(11108) : neg_reg_16(&D0);              // NEG.W	D0
  DEF_ROMLOC(1110A) : add_toreg_16(D1, &D0);        // ADD.W	D1,D0
  DEF_ROMLOC(1110C)
      : move_toreg_16(read_16(A0 + 0x3A), &D1);    // MOVE.W	58(A0),D1
  DEF_ROMLOC(11110) : sub_toreg_16(D0, &D1);       // SUB.W	D0,D1
  DEF_ROMLOC(11112) : move_tomem_16(D1, A0 + 0x8); // MOVE.W	D1,8(A0)
  DEF_ROMLOC(11116) : return;                      // RTS
}
ROMFUNC(rom_11118) {
  DEF_ROMLOC(11118) : move_toreg_16(0x60, &D1); // MOVE.W	#$0060,D1
  DEF_ROMLOC(1111C) : move_toreg_32(0x0, &D0);  // MOVEQ.L	$00,D0
  DEF_ROMLOC(1111E)
      : move_toreg_8(read_8(0xFFFFFE6C), &D0);      // MOVE.B	$FE6C,D0
  DEF_ROMLOC(11122) : btst_tomem_8(0x0, A0 + 0x22); // BTST.B	#$00,34(A0)
  DEF_ROMLOC(11128) : if (CCR_EQ) goto rom_11130;   // BEQ.B	$11130
  DEF_ROMLOC(1112A) : neg_reg_16(&D0);              // NEG.W	D0
  DEF_ROMLOC(1112C) : add_toreg_16(0x80, &D0);      // ADDI.W	#$0080,D0
  DEF_ROMLOC(11130)
      : move_toreg_16(read_16(A0 + 0x38), &D1);    // MOVE.W	56(A0),D1
  DEF_ROMLOC(11134) : sub_toreg_16(D0, &D1);       // SUB.W	D0,D1
  DEF_ROMLOC(11136) : move_tomem_16(D1, A0 + 0xC); // MOVE.W	D1,12(A0)
  DEF_ROMLOC(1113A) : return;                      // RTS
}
ROMFUNC(rom_1113C) {
  DEF_ROMLOC(1113C)
      : move_toreg_16(read_16(A0 + 0x3E), &D0);    // MOVE.W	62(A0),D0
  DEF_ROMLOC(11140) : add_tomem_16(D0, A0 + 0x26); // ADD.W	D0,38(A0)
  DEF_ROMLOC(11144)
      : move_toreg_8(read_8(A0 + 0x26), &D0); // MOVE.B
                                              // 38(A0),D0
  DEF_ROMLOC(11148) : rom_29D2();             // JSR	$000029D2
  DEF_ROMLOC(1114E)
      : move_toreg_16(read_16(A0 + 0x38), &D2); // MOVE.W	56(A0),D2
  DEF_ROMLOC(11152)
      : move_toreg_16(read_16(A0 + 0x3A), &D3); // MOVE.W	58(A0),D3
  DEF_ROMLOC(11156) : move_toreg_32(0x0, &D4);  // MOVEQ.L	$00,D4
  DEF_ROMLOC(11158)
      : move_toreg_8(read_8(A0 + 0x3C), &D4);      // MOVE.B	60(A0),D4
  DEF_ROMLOC(1115C) : move_toreg_32(D4, &D5);      // MOVE.L	D4,D5
  DEF_ROMLOC(1115E) : muls_toreg_16(D0, &D4);      // MULS.W	D0,D4
  DEF_ROMLOC(11160) : asr_toreg_32(0x8, &D4);      // ASR.L	#$08,D4
  DEF_ROMLOC(11162) : muls_toreg_16(D1, &D5);      // MULS.W	D1,D5
  DEF_ROMLOC(11164) : asr_toreg_32(0x8, &D5);      // ASR.L	#$08,D5
  DEF_ROMLOC(11166) : add_toreg_16(D2, &D4);       // ADD.W	D2,D4
  DEF_ROMLOC(11168) : add_toreg_16(D3, &D5);       // ADD.W	D3,D5
  DEF_ROMLOC(1116A) : move_tomem_16(D4, A0 + 0xC); // MOVE.W	D4,12(A0)
  DEF_ROMLOC(1116E) : move_tomem_16(D5, A0 + 0x8); // MOVE.W	D5,8(A0)
  DEF_ROMLOC(11172) : return;                      // RTS
}