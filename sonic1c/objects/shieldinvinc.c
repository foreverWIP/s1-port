// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"


ROMFUNC(rom_148C0) {
  u8 switchindex = 0;
  DEF_ROMLOC(148C0) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(148C2) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(148C6)
      : move_toreg_16(read_16(0x148CE + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(148CA): goto rom_148CE + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(148CA) : switch (switchindex) {
  case 0:
    rom_148D4();
    break;
  case 1:
    rom_1490C();
    break;
  case 2:
    rom_14944();
    break;
  }
}
ROMFUNC(rom_148D4) {
  DEF_ROMLOC(148D4) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(148D8)
      : move_tomem_32(0x14B1A, A0 + 0x4);             // MOVE.L	#$00014B1A,4(A0)
  DEF_ROMLOC(148E0) : move_tomem_8(0x4, A0 + 0x1);    // MOVE.B	#$04,1(A0)
  DEF_ROMLOC(148E6) : move_tomem_8(0x1, A0 + 0x18);   // MOVE.B	#$01,24(A0)
  DEF_ROMLOC(148EC) : move_tomem_8(0x10, A0 + 0x19);  // MOVE.B	#$10,25(A0)
  DEF_ROMLOC(148F2) : tst_mem_8(A0 + 0x1C);           // TST.B	28(A0)
  DEF_ROMLOC(148F6) : if (!CCR_EQ) goto rom_14900;    // BNE.B	$14900
  DEF_ROMLOC(148F8) : move_tomem_16(0x541, A0 + 0x2); // MOVE.W	#$0541,2(A0)
  DEF_ROMLOC(148FE) : return;                         // RTS
  DEF_ROMLOC(14900) : add_tomem_8(0x2, A0 + 0x24);    // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(14904) : move_tomem_16(0x55C, A0 + 0x2); // MOVE.W	#$055C,2(A0)
  DEF_ROMLOC(1490A) : return;                         // RTS
}
ROMFUNC(rom_1490C) {
  DEF_ROMLOC(1490C) : tst_mem_8(0xFFFFFE2D);       // TST.B	$FE2D
  DEF_ROMLOC(14910) : if (!CCR_EQ) goto rom_1493C; // BNE.B	$1493C
  DEF_ROMLOC(14912) : tst_mem_8(0xFFFFFE2C);       // TST.B	$FE2C
  DEF_ROMLOC(14916) : if (CCR_EQ) goto rom_1493E;  // BEQ.B	$1493E
  DEF_ROMLOC(14918)
      : move_tomem_16(read_16(0xFFFFD008), A0 + 0x8); // MOVE.W	$D008,8(A0)
  DEF_ROMLOC(1491E)
      : move_tomem_16(read_16(0xFFFFD00C), A0 + 0xC); // MOVE.W	$D00C,12(A0)
  DEF_ROMLOC(14924)
      : move_tomem_8(read_8(0xFFFFD022), A0 + 0x22); // MOVE.B	$D022,34(A0)
  DEF_ROMLOC(1492A) : move_toreg_32(0x14AB4, &A1);   // LEA.L	$00014AB4,A1
  DEF_ROMLOC(14930) : rom_ADA2();                    // JSR	$0000ADA2
  DEF_ROMLOC(14936) : {
    rom_DC92();
    return;
  }                           // JMP	$0000DC92
  DEF_ROMLOC(1493C) : return; // RTS
  DEF_ROMLOC(1493E) : {
    rom_DCCE();
    return;
  } // JMP	$0000DCCE
}
ROMFUNC(rom_14944) {
  DEF_ROMLOC(14944) : tst_mem_8(0xFFFFFE2D);      // TST.B	$FE2D
  DEF_ROMLOC(14948) : if (CCR_EQ) goto rom_149B6; // BEQ.B	$149B6
  DEF_ROMLOC(1494A)
      : move_toreg_16(read_16(0xFFFFF7A8), &D0); // MOVE.W	$F7A8,D0
  DEF_ROMLOC(1494E)
      : move_toreg_8(read_8(A0 + 0x1C), &D1); // MOVE.B	28(A0),D1
  DEF_ROMLOC(14952) : sub_toreg_8(0x1, &D1);  // SUBQ.B	#$01,D1
  DEF_ROMLOC(14954) : goto rom_1496E;         // BRA.B	$1496E
  DEF_ROMLOC(14956) : lsl_toreg_8(0x4, &D1);  // LSL.B	#$04,D1
  DEF_ROMLOC(14958) : add_toreg_8(0x4, &D1);  // ADDQ.B	#$04,D1
  DEF_ROMLOC(1495A) : sub_toreg_8(D1, &D0);   // SUB.B	D1,D0
  DEF_ROMLOC(1495C)
      : move_toreg_8(read_8(A0 + 0x30), &D1);      // MOVE.B	48(A0),D1
  DEF_ROMLOC(14960) : sub_toreg_8(D1, &D0);        // SUB.B	D1,D0
  DEF_ROMLOC(14962) : add_toreg_8(0x4, &D1);       // ADDQ.B	#$04,D1
  DEF_ROMLOC(14964) : and_toreg_8(0xF, &D1);       // ANDI.B	#$0F,D1
  DEF_ROMLOC(14968) : move_tomem_8(D1, A0 + 0x30); // MOVE.B	D1,48(A0)
  DEF_ROMLOC(1496C) : goto rom_1498E;              // BRA.B	$1498E
  DEF_ROMLOC(1496E) : lsl_toreg_8(0x3, &D1);       // LSL.B	#$03,D1
  DEF_ROMLOC(14970) : move_toreg_8(D1, &D2);       // MOVE.B	D1,D2
  DEF_ROMLOC(14972) : add_toreg_8(D1, &D1);        // ADD.B	D1,D1
  DEF_ROMLOC(14974) : add_toreg_8(D2, &D1);        // ADD.B	D2,D1
  DEF_ROMLOC(14976) : add_toreg_8(0x4, &D1);       // ADDQ.B	#$04,D1
  DEF_ROMLOC(14978) : sub_toreg_8(D1, &D0);        // SUB.B	D1,D0
  DEF_ROMLOC(1497A)
      : move_toreg_8(read_8(A0 + 0x30), &D1);         // MOVE.B	48(A0),D1
  DEF_ROMLOC(1497E) : sub_toreg_8(D1, &D0);           // SUB.B	D1,D0
  DEF_ROMLOC(14980) : add_toreg_8(0x4, &D1);          // ADDQ.B	#$04,D1
  DEF_ROMLOC(14982) : cmp_toreg_8(0x18, &D1);         // CMPI.B	#$18,D1
  DEF_ROMLOC(14986) : if (CCR_CS) goto rom_1498A;     // BCS.B	$1498A
  DEF_ROMLOC(14988) : move_toreg_32(0x0, &D1);        // MOVEQ.L	$00,D1
  DEF_ROMLOC(1498A) : move_tomem_8(D1, A0 + 0x30);    // MOVE.B	D1,48(A0)
  DEF_ROMLOC(1498E) : move_toreg_32(0xFFFFCB00, &A1); // LEA.L	$CB00,A1
  DEF_ROMLOC(14992)
      : move_toreg_32((s32)A1 + (s8)0x0 + (s16)D0,
                      &A1); // LEA.L	0(A1,D0),A1
  DEF_ROMLOC(14996)
      : move_tomem_16(read_16((A1 += 2, A1 - 2)),
                      A0 + 0x8); // MOVE.W	(A1)+,8(A0)
  DEF_ROMLOC(1499A)
      : move_tomem_16(read_16((A1 += 2, A1 - 2)),
                      A0 + 0xC); // MOVE.W	(A1)+,12(A0)
  DEF_ROMLOC(1499E)
      : move_tomem_8(read_8(0xFFFFD022), A0 + 0x22); // MOVE.B	$D022,34(A0)
  DEF_ROMLOC(149A4) : move_toreg_32(0x14AB4, &A1);   // LEA.L	$00014AB4,A1
  DEF_ROMLOC(149AA) : rom_ADA2();                    // JSR	$0000ADA2
  DEF_ROMLOC(149B0) : {
    rom_DC92();
    return;
  } // JMP	$0000DC92
  DEF_ROMLOC(149B6) : {
    rom_DCCE();
    return;
  } // JMP	$0000DCCE
}