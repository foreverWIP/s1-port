// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"


ROMFUNC(rom_4E4E) {
  u8 switchindex = 0;
  DEF_ROMLOC(4E4E) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(4E50) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(4E54)
      : move_toreg_16(read_16(0x4E5C + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(4E58): goto rom_4E5C + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(4E58) : switch (switchindex) {
  case 0:
    rom_4E64();
    break;
  case 1:
    rom_4E94();
    break;
  case 2:
    rom_4EB8();
    break;
  case 3:
    rom_4F2C();
    break;
  }
}
ROMFUNC(rom_4E64) {
  DEF_ROMLOC(4E64) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(4E68)
      : move_tomem_32(0x5062, A0 + 0x4); // MOVE.L	#$00005062,4(A0)
  DEF_ROMLOC(4E70)
      : move_tomem_16(0xFFFF8500, A0 + 0x2);         // MOVE.W	#$8500,2(A0)
  DEF_ROMLOC(4E76) : move_tomem_8(0x0, A0 + 0x1);    // MOVE.B	#$00,1(A0)
  DEF_ROMLOC(4E7C) : move_tomem_8(0x3C, A0 + 0x19);  // MOVE.B	#$3C,25(A0)
  DEF_ROMLOC(4E82) : move_tomem_16(0x120, A0 + 0x8); // MOVE.W	#$0120,8(A0)
  DEF_ROMLOC(4E88) : move_tomem_16(0xC0, A0 + 0xA);  // MOVE.W	#$00C0,10(A0)
  DEF_ROMLOC(4E8E) : move_tomem_16(0x0, 0xFFFFFE20); // MOVE.W	#$0000,$FE20
  rom_4E94(); // Detected flow into next function
}
ROMFUNC(rom_4E94) {
  DEF_ROMLOC(4E94) : rom_DC92();
  return; // JMP	$0000DC92
}
ROMFUNC(rom_4E9A) {
  DEF_ROMLOC(4E9A) : btst_tomem_8(D0, A6);         // BTST.B	D0,(A6)
  DEF_ROMLOC(4E9C) : btst_tomem_8(D0, A2 + 0x102); // BTST.B	D0,258(A2)
  rom_4EB8(); // Detected flow into next function
}
ROMFUNC(rom_4EB8) {
  DEF_ROMLOC(4EB8) : move_toreg_32(A0, &A1);     // MOVEA.L	A0,A1
  DEF_ROMLOC(4EBA) : move_toreg_32(0x4E9A, &A2); // LEA.L	$00004E9A,A2
  DEF_ROMLOC(4EC0) : move_toreg_32(0x0, &D1);    // MOVEQ.L	$00,D1
  DEF_ROMLOC(4EC2)
      : move_toreg_8(read_8(0xFFFFFE18), &D1);  // MOVE.B	$FE18,D1
  DEF_ROMLOC(4EC6) : sub_toreg_8(0x2, &D1);     // SUBQ.B	#$02,D1
  DEF_ROMLOC(4EC8) : if (CCR_CC) goto rom_4ED0; // BCC.B	$4ED0
  DEF_ROMLOC(4ECA) : rom_DCCE();
  return;                                       // JMP	$0000DCCE
  DEF_ROMLOC(4ED0) : move_toreg_32(0x1, &D3);   // MOVEQ.L	$01,D3
  DEF_ROMLOC(4ED2) : cmp_toreg_8(0xE, &D1);     // CMPI.B	#$0E,D1
  DEF_ROMLOC(4ED6) : if (CCR_CS) goto rom_4EDC; // BCS.B	$4EDC
  DEF_ROMLOC(4ED8) : move_toreg_32(0x0, &D3);   // MOVEQ.L	$00,D3
  DEF_ROMLOC(4EDA) : move_toreg_32(0xE, &D1);   // MOVEQ.L	$0E,D1
  DEF_ROMLOC(4EDC) : move_toreg_8(D1, &D2);     // MOVE.B	D1,D2
  DEF_ROMLOC(4EDE) : and_toreg_8(0x1, &D2);     // ANDI.B	#$01,D2
  rom_4EE2(); // Detected flow into next function
}
ROMFUNC(rom_4EE2) {
  DEF_ROMLOC(4EE2) : move_tomem_8(OBJ_CONTSCRITEM, A1 + offsetof(object, id)); // MOVE.B
                                                         // #$80,0(A1)
  DEF_ROMLOC(4EE8)
      : move_tomem_16(read_16((A2 += 2, A2 - 2)),
                      A1 + 0x8);                    // MOVE.W	(A2)+,8(A1)
  DEF_ROMLOC(4EEC) : tst_reg_8(&D2);                // TST.B	D2
  DEF_ROMLOC(4EEE) : if (CCR_EQ) goto rom_4EF6;     // BEQ.B	$4EF6
  DEF_ROMLOC(4EF0) : sub_tomem_16(0xA, A1 + 0x8);   // SUBI.W	#$000A,8(A1)
  DEF_ROMLOC(4EF6) : move_tomem_16(0xD0, A1 + 0xA); // MOVE.W	#$00D0,10(A1)
  DEF_ROMLOC(4EFC) : move_tomem_8(0x6, A1 + 0x1A);  // MOVE.B	#$06,26(A1)
  DEF_ROMLOC(4F02) : move_tomem_8(0x6, A1 + 0x24);  // MOVE.B	#$06,36(A1)
  DEF_ROMLOC(4F08)
      : move_tomem_32(0x5062, A1 + 0x4); // MOVE.L	#$00005062,4(A1)
  DEF_ROMLOC(4F10)
      : move_tomem_16(0xFFFF8551, A1 + 0x2);        // MOVE.W	#$8551,2(A1)
  DEF_ROMLOC(4F16) : move_tomem_8(0x0, A1 + 0x1);   // MOVE.B	#$00,1(A1)
  DEF_ROMLOC(4F1C) : move_toreg_32(A1 + 0x40, &A1); // LEA.L	64(A1),A1
  DEF_ROMLOC(4F20) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_4EE2;                                  // DBF.W	D1,$4EE2
  DEF_ROMLOC(4F24) : move_toreg_32(A1 - 0x40, &A1); // LEA.L	-64(A1),A1
  DEF_ROMLOC(4F28) : move_tomem_8(D3, A1 + 0x28);   // MOVE.B	D3,40(A1)
  rom_4F2C(); // Detected flow into next function
}
ROMFUNC(rom_4F2C) {
  DEF_ROMLOC(4F2C) : tst_mem_8(A0 + 0x28);         // TST.B	40(A0)
  DEF_ROMLOC(4F30) : if (CCR_EQ) goto rom_4F4C;    // BEQ.B	$4F4C
  DEF_ROMLOC(4F32) : cmp_tomem_8(0x6, 0xFFFFD024); // CMPI.B	#$06,$D024
  DEF_ROMLOC(4F38) : if (CCR_CS) goto rom_4F4C;    // BCS.B	$4F4C
  DEF_ROMLOC(4F3A)
      : move_toreg_8(read_8(0xFFFFFE0F), &D0);   // MOVE.B	$FE0F,D0
  DEF_ROMLOC(4F3E) : and_toreg_8(0x1, &D0);      // ANDI.B	#$01,D0
  DEF_ROMLOC(4F42) : if (!CCR_EQ) goto rom_4F4C; // BNE.B	$4F4C
  DEF_ROMLOC(4F44) : tst_mem_16(0xFFFFD010);     // TST.W	$D010
  DEF_ROMLOC(4F48) : if (!CCR_EQ) goto rom_4F62; // BNE.B	$4F62
  DEF_ROMLOC(4F4A) : return;                     // RTS
  DEF_ROMLOC(4F4C)
      : move_toreg_8(read_8(0xFFFFFE0F), &D0);     // MOVE.B	$FE0F,D0
  DEF_ROMLOC(4F50) : and_toreg_8(0xF, &D0);        // ANDI.B	#$0F,D0
  DEF_ROMLOC(4F54) : if (!CCR_EQ) goto rom_4F5C;   // BNE.B	$4F5C
  DEF_ROMLOC(4F56) : bchg_tomem_8(0x0, A0 + 0x1A); // BCHG.B	#$00,26(A0)
  DEF_ROMLOC(4F5C) : rom_DC92();
  return; // JMP	$0000DC92
  DEF_ROMLOC(4F62) : rom_DCCE();
  return; // JMP	$0000DCCE
}