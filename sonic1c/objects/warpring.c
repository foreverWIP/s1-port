// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_A484) {
  u8 switchindex = 0;
  DEF_ROMLOC(A484) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(A486) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(A48A)
      : move_toreg_16(read_16(0xA492 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(A48E): goto rom_A492 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(A48E) : switch (switchindex) {
  case 0:
    rom_A49A();
    break;
  case 1:
    rom_A4E4();
    break;
  case 2:
    rom_A50C();
    break;
  case 3:
    rom_A550();
    break;
  }
}
ROMFUNC(rom_A49A) {
  DEF_ROMLOC(A49A)
      : move_tomem_32(0xA654, A0 + 0x4);              // MOVE.L	#$0000A654,4(A0)
  DEF_ROMLOC(A4A2) : move_tomem_16(0x2400, A0 + 0x2); // MOVE.W	#$2400,2(A0)
  DEF_ROMLOC(A4A8) : or_tomem_8(0x4, A0 + 0x1);       // ORI.B	#$04,1(A0)
  DEF_ROMLOC(A4AE) : move_tomem_8(0x40, A0 + 0x19);   // MOVE.B	#$40,25(A0)
  DEF_ROMLOC(A4B4) : tst_mem_8(A0 + 0x1);             // TST.B	1(A0)
  DEF_ROMLOC(A4B8) : if (CCR_PL) {
    rom_A4E4();
    return;
  }                                                // BPL.B	$A4E4
  DEF_ROMLOC(A4BA) : cmp_tomem_8(0x6, 0xFFFFFE57); // CMPI.B	#$06,$FE57
  DEF_ROMLOC(A4C0) : if (CCR_EQ) {
    rom_A550();
    return;
  }                                                    // BEQ.W	$A550
  DEF_ROMLOC(A4C4) : cmp_tomem_16(0x32, 0xFFFFFE20);   // CMPI.W	#$0032,$FE20
  DEF_ROMLOC(A4CA) : if (CCR_CC) goto rom_A4CE;        // BCC.B	$A4CE
  DEF_ROMLOC(A4CC) : return;                           // RTS
  DEF_ROMLOC(A4CE) : add_tomem_8(0x2, A0 + 0x24);      // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(A4D2) : move_tomem_8(0x2, A0 + 0x18);     // MOVE.B	#$02,24(A0)
  DEF_ROMLOC(A4D8) : move_tomem_8(0x52, A0 + 0x20);    // MOVE.B	#$52,32(A0)
  DEF_ROMLOC(A4DE) : move_tomem_16(0xC40, 0xFFFFF7BE); // MOVE.W
                                                       // #$0C40,$F7BE
  rom_A4E4(); // Detected flow into next function
}
ROMFUNC(rom_A4E4) {
  DEF_ROMLOC(A4E4)
      : move_tomem_8(read_8(0xFFFFFEC3), A0 + 0x1A); // MOVE.B	$FEC3,26(A0)
  DEF_ROMLOC(A4EA)
      : move_toreg_16(read_16(A0 + 0x8), &D0);      // MOVE.W	8(A0),D0
  DEF_ROMLOC(A4EE) : and_toreg_16(0xFFFFFF80, &D0); // ANDI.W	#$FF80,D0
  DEF_ROMLOC(A4F2)
      : move_toreg_16(read_16(0xFFFFF700), &D1);    // MOVE.W	$F700,D1
  DEF_ROMLOC(A4F6) : sub_toreg_16(0x80, &D1);       // SUBI.W	#$0080,D1
  DEF_ROMLOC(A4FA) : and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
  DEF_ROMLOC(A4FE) : sub_toreg_16(D1, &D0);         // SUB.W	D1,D0
  DEF_ROMLOC(A500) : cmp_toreg_16(0x280, &D0);      // CMPI.W	#$0280,D0
  DEF_ROMLOC(A504) : if (CCR_HI) {
    rom_DCCE();
    return;
  }           // BHI.W	$DCCE
  rom_DC92(); // BRA.W	$DC92
}
ROMFUNC(rom_A50C) {
  DEF_ROMLOC(A50C) : sub_tomem_8(0x2, A0 + 0x24);  // SUBQ.B	#$02,36(A0)
  DEF_ROMLOC(A510) : move_tomem_8(0x0, A0 + 0x20); // MOVE.B	#$00,32(A0)
  DEF_ROMLOC(A516) : rom_E11A();                   // BSR.W	$E11A
  DEF_ROMLOC(A51A) : if (!CCR_EQ) goto rom_A544;   // BNE.W	$A544
  DEF_ROMLOC(A51E) : move_tomem_8(0x7C, A1 + 0x0); // MOVE.B	#$7C,0(A1)
  DEF_ROMLOC(A524)
      : move_tomem_16(read_16(A0 + 0x8), A1 + 0x8); // MOVE.W	8(A0),8(A1)
  DEF_ROMLOC(A52A)
      : move_tomem_16(read_16(A0 + 0xC), A1 + 0xC); // MOVE.W	12(A0),12(A1)
  DEF_ROMLOC(A530) : move_tomem_32(A0, A1 + 0x3C);  // MOVE.L	A0,60(A1)
  DEF_ROMLOC(A534)
      : move_toreg_16(read_16(0xFFFFD008), &D0); // MOVE.W	$D008,D0
  DEF_ROMLOC(A538)
      : cmp_toreg_16(read_16(A0 + 0x8), &D0);     // CMP.W	8(A0),D0
  DEF_ROMLOC(A53C) : if (CCR_CS) goto rom_A544;   // BCS.B	$A544
  DEF_ROMLOC(A53E) : bset_tomem_8(0x0, A1 + 0x1); // BSET.B	#$00,1(A1)
  DEF_ROMLOC(A544) : move_toreg_16(0xC3, &D0);    // MOVE.W	#$00C3,D0
  DEF_ROMLOC(A548) : rom_1394();                  // JSR	$00001394
  rom_A4E4();                                     // BRA.B	$A4E4
}
ROMFUNC(rom_A550) {
  rom_DCCE(); // BRA.W	$DCCE
}