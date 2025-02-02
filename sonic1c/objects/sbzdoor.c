// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_8FB2) {
  u8 switchindex = 0;
  DEF_ROMLOC(8FB2) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(8FB4) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(8FB8)
      : move_toreg_16(read_16(0x8FC0 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(8FBC): goto rom_8FC0 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(8FBC) : switch (switchindex) {
  case 0:
    rom_8FC4();
    break;
  case 1:
    rom_8FE8();
    break;
  }
}
ROMFUNC(rom_8FC4) {
  DEF_ROMLOC(8FC4) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(8FC8)
      : move_tomem_32(0x906A, A0 + 0x4);              // MOVE.L	#$0000906A,4(A0)
  DEF_ROMLOC(8FD0) : move_tomem_16(0x42E8, A0 + 0x2); // MOVE.W	#$42E8,2(A0)
  DEF_ROMLOC(8FD6) : or_tomem_8(0x4, A0 + 0x1);       // ORI.B	#$04,1(A0)
  DEF_ROMLOC(8FDC) : move_tomem_8(0x8, A0 + 0x19);    // MOVE.B	#$08,25(A0)
  DEF_ROMLOC(8FE2) : move_tomem_8(0x4, A0 + 0x18);    // MOVE.B	#$04,24(A0)
  rom_8FE8(); // Detected flow into next function
}
ROMFUNC(rom_8FE8) {
  DEF_ROMLOC(8FE8) : move_toreg_16(0x40, &D1); // MOVE.W	#$0040,D1
  DEF_ROMLOC(8FEC) : clr_mem_8(A0 + 0x1C);     // CLR.B	28(A0)
  DEF_ROMLOC(8FF0)
      : move_toreg_16(read_16(0xFFFFD008), &D0); // MOVE.W	$D008,D0
  DEF_ROMLOC(8FF4) : add_toreg_16(D1, &D0);      // ADD.W	D1,D0
  DEF_ROMLOC(8FF6)
      : cmp_toreg_16(read_16(A0 + 0x8), &D0);   // CMP.W	8(A0),D0
  DEF_ROMLOC(8FFA) : if (CCR_CS) goto rom_9026; // BCS.B	$9026
  DEF_ROMLOC(8FFC) : sub_toreg_16(D1, &D0);     // SUB.W	D1,D0
  DEF_ROMLOC(8FFE) : sub_toreg_16(D1, &D0);     // SUB.W	D1,D0
  DEF_ROMLOC(9000)
      : cmp_toreg_16(read_16(A0 + 0x8), &D0);   // CMP.W	8(A0),D0
  DEF_ROMLOC(9004) : if (CCR_CC) goto rom_9026; // BCC.B	$9026
  DEF_ROMLOC(9006) : add_toreg_16(D1, &D0);     // ADD.W	D1,D0
  DEF_ROMLOC(9008)
      : cmp_toreg_16(read_16(A0 + 0x8), &D0);      // CMP.W	8(A0),D0
  DEF_ROMLOC(900C) : if (CCR_CC) goto rom_9018;    // BCC.B	$9018
  DEF_ROMLOC(900E) : btst_tomem_8(0x0, A0 + 0x22); // BTST.B	#$00,34(A0)
  DEF_ROMLOC(9014) : if (!CCR_EQ) goto rom_9026;   // BNE.B	$9026
  goto rom_9020;                                   // BRA.B	$9020
  DEF_ROMLOC(9018) : btst_tomem_8(0x0, A0 + 0x22); // BTST.B	#$00,34(A0)
  DEF_ROMLOC(901E) : if (CCR_EQ) goto rom_9026;    // BEQ.B	$9026
  DEF_ROMLOC(9020) : move_tomem_8(0x1, A0 + 0x1C); // MOVE.B	#$01,28(A0)
  DEF_ROMLOC(9026) : move_toreg_32(0x904E, &A1);   // LEA.L	$0000904E,A1
  DEF_ROMLOC(902C) : animate_sprite();                   // BSR.W	$ADA2
  DEF_ROMLOC(9030) : tst_mem_8(A0 + 0x1A);         // TST.B	26(A0)
  DEF_ROMLOC(9034) : if (!CCR_EQ) goto rom_904A;   // BNE.B	$904A
  DEF_ROMLOC(9036) : move_toreg_16(0x11, &D1);     // MOVE.W	#$0011,D1
  DEF_ROMLOC(903A) : move_toreg_16(0x20, &D2);     // MOVE.W	#$0020,D2
  DEF_ROMLOC(903E) : move_toreg_16(D2, &D3);       // MOVE.W	D2,D3
  DEF_ROMLOC(9040) : add_toreg_16(0x1, &D3);       // ADDQ.W	#$01,D3
  DEF_ROMLOC(9042)
      : move_toreg_16(read_16(A0 + 0x8), &D4); // MOVE.W	8(A0),D4
  DEF_ROMLOC(9046) : rom_10062();              // BSR.W	$10062
  DEF_ROMLOC(904A) : rom_FD38();
  return; // BRA.W	$FD38
}