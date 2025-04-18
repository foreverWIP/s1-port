// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_F410) {
  u8 switchindex = 0;
  DEF_ROMLOC(F410) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(F412) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(F416)
      : move_toreg_16(read_16(0xF422 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	10(PC,D0),D1
  // DEF_ROMLOC(F41A): rom_F422 + (s16)(D1 & 0xffff)(); // JSR	6(PC,D1)
  DEF_ROMLOC(F41A) : switch (switchindex) {
  case 0:
    rom_F42E();
    break;
  case 1:
    rom_F458();
    break;
  case 2:
    rom_F4CA();
    break;
  case 3:
    rom_F47E();
    break;
  case 4:
    rom_F4D6();
    break;
  case 5:
    rom_F4E6();
    break;
  }
  rom_F624(); // BRA.W	$F624
}
ROMFUNC(rom_F42E) {
  DEF_ROMLOC(F42E) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(F432)
      : move_tomem_32(0xF8D6, A0 + 0x4); // MOVE.L	#$0000F8D6,4(A0)
  DEF_ROMLOC(F43A)
      : move_tomem_16(0xFFFFE3A8, A0 + 0x2);         // MOVE.W	#$E3A8,2(A0)
  DEF_ROMLOC(F440) : move_tomem_8(0x4, A0 + 0x1);    // MOVE.B	#$04,1(A0)
  DEF_ROMLOC(F446) : move_tomem_8(0x1, A0 + 0x18);   // MOVE.B	#$01,24(A0)
  DEF_ROMLOC(F44C) : move_tomem_8(0x38, A0 + 0x19);  // MOVE.B	#$38,25(A0)
  DEF_ROMLOC(F452) : move_tomem_16(0x78, A0 + 0x34); // MOVE.W	#$0078,52(A0)
  rom_F458(); // Detected flow into next function
}
ROMFUNC(rom_F458) {
  DEF_ROMLOC(F458) : sub_tomem_16(0x1, A0 + 0x32); // SUBQ.W	#$01,50(A0)
  DEF_ROMLOC(F45C) : if (CCR_PL) goto rom_F47C;    // BPL.B	$F47C
  DEF_ROMLOC(F45E)
      : move_tomem_16(read_16(A0 + 0x34), A0 + 0x32); // MOVE.W	52(A0),50(A0)
  DEF_ROMLOC(F464)
      : move_toreg_16(read_16(0xFFFFD00C), &D0); // MOVE.W	$D00C,D0
  DEF_ROMLOC(F468)
      : move_toreg_16(read_16(A0 + 0xC), &D1);    // MOVE.W	12(A0),D1
  DEF_ROMLOC(F46C) : cmp_toreg_16(D1, &D0);       // CMP.W	D1,D0
  DEF_ROMLOC(F46E) : if (CCR_CC) goto rom_F47C;   // BCC.B	$F47C
  DEF_ROMLOC(F470) : sub_toreg_16(0x170, &D1);    // SUBI.W	#$0170,D1
  DEF_ROMLOC(F474) : cmp_toreg_16(D1, &D0);       // CMP.W	D1,D0
  DEF_ROMLOC(F476) : if (CCR_CS) goto rom_F47C;   // BCS.B	$F47C
  DEF_ROMLOC(F478) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(F47C) : return;                      // RTS
}
ROMFUNC(rom_F47E) {
  DEF_ROMLOC(F47E) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(F482) : rom_E130();                  // BSR.W	$E130
  DEF_ROMLOC(F486) : if (!CCR_EQ) goto rom_F4A4;  // BNE.B	$F4A4
  DEF_ROMLOC(F488)
      : move_tomem_8(OBJ_LAVAGEYSER,
                     A1 + offsetof(object, id)); // MOVE.B	#$4D,0(A1)
  DEF_ROMLOC(F48E)
      : move_tomem_16(read_16(A0 + 0x8), A1 + 0x8); // MOVE.W	8(A0),8(A1)
  DEF_ROMLOC(F494)
      : move_tomem_16(read_16(A0 + 0xC), A1 + 0xC); // MOVE.W	12(A0),12(A1)
  DEF_ROMLOC(F49A)
      : move_tomem_8(read_8(A0 + 0x28), A1 + 0x28); // MOVE.B	40(A0),40(A1)
  DEF_ROMLOC(F4A0) : move_tomem_32(A0, A1 + 0x3C);  // MOVE.L	A0,60(A1)
  DEF_ROMLOC(F4A4) : move_tomem_8(0x1, A0 + 0x1C);  // MOVE.B	#$01,28(A0)
  DEF_ROMLOC(F4AA) : tst_mem_8(A0 + 0x28);          // TST.B	40(A0)
  DEF_ROMLOC(F4AE) : if (CCR_EQ) goto rom_F4B8;     // BEQ.B	$F4B8
  DEF_ROMLOC(F4B0) : move_tomem_8(0x4, A0 + 0x1C);  // MOVE.B	#$04,28(A0)
  DEF_ROMLOC(F4B6) : {
    rom_F4D6();
    return;
  } // BRA.B	$F4D6
  DEF_ROMLOC(F4B8)
      : move_toreg_32(read_32(A0 + 0x3C), &A1);    // MOVEA.L	60(A0),A1
  DEF_ROMLOC(F4BC) : bset_tomem_8(0x1, A1 + 0x22); // BSET.B	#$01,34(A1)
  DEF_ROMLOC(F4C2)
      : move_tomem_16(0xFFFFFA80, A1 + 0x12); // MOVE.W	#$FA80,18(A1)
  rom_F4D6();                                 // BRA.B	$F4D6
}
ROMFUNC(rom_F4CA) {
  DEF_ROMLOC(F4CA) : tst_mem_8(A0 + 0x28); // TST.B	40(A0)
  DEF_ROMLOC(F4CE) : if (CCR_EQ) {
    rom_F4D6();
    return;
  } // BEQ.B	$F4D6
  DEF_ROMLOC(F4D0) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(F4D4) : return;                      // RTS
}
ROMFUNC(rom_F4D6) {
  DEF_ROMLOC(F4D6) : move_toreg_32(0xF8A0, &A1); // LEA.L	$0000F8A0,A1
  DEF_ROMLOC(F4DC) : animate_sprite();           // BSR.W	$ADA2
  DEF_ROMLOC(F4E0) : queue_sprite();             // BSR.W	$DC92
  DEF_ROMLOC(F4E4) : return;                     // RTS
}
ROMFUNC(rom_F4E6) {
  DEF_ROMLOC(F4E6) : move_tomem_8(0x0, A0 + 0x1C); // MOVE.B	#$00,28(A0)
  DEF_ROMLOC(F4EC) : move_tomem_8(0x2, A0 + 0x24); // MOVE.B	#$02,36(A0)
  DEF_ROMLOC(F4F2) : tst_mem_8(A0 + 0x28);         // TST.B	40(A0)
  DEF_ROMLOC(F4F6) : if (CCR_EQ) {
    rom_DCCE();
    return;
  } // BEQ.W	$DCCE
  DEF_ROMLOC(F4FA) : return; // RTS
}