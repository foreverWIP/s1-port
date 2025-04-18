// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_9FB0) {
  u8 switchindex = 0;
  DEF_ROMLOC(9FB0) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(9FB2) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(9FB6)
      : move_toreg_16(read_16(0x9FBE + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(9FBA): goto rom_9FBE + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(9FBA) : switch (switchindex) {
  case 0:
    rom_9FC8();
    break;
  case 1:
    rom_A012();
    break;
  case 2:
    rom_A030();
    break;
  case 3:
    rom_A076();
    break;
  case 4:
    rom_A07C();
    break;
  }
}
ROMFUNC(rom_9FC8) {
  DEF_ROMLOC(9FC8) : sub_tomem_16(0x1, A0 + 0x32); // SUBQ.W	#$01,50(A0)
  DEF_ROMLOC(9FCC) : if (CCR_PL) {
    rom_A022();
    return;
  } // BPL.B	$A022
  DEF_ROMLOC(9FCE) : add_tomem_8(0x2, A0 + 0x24);     // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(9FD2) : move_tomem_32(0xA184, A0 + 0x4); // MOVE.L	#$0000A184,4(A0)
  DEF_ROMLOC(9FDA) : move_tomem_16(0x2444, A0 + 0x2); // MOVE.W	#$2444,2(A0)
  DEF_ROMLOC(9FE0) : move_tomem_8(0x4, A0 + 0x1);     // MOVE.B	#$04,1(A0)
  DEF_ROMLOC(9FE6) : move_tomem_8(0x3, A0 + 0x18);    // MOVE.B	#$03,24(A0)
  DEF_ROMLOC(9FEC) : move_tomem_8(0x8, A0 + 0x19);    // MOVE.B	#$08,25(A0)
  DEF_ROMLOC(9FF2) : and_tomem_8(0x3, A0 + 0x22);     // ANDI.B	#$03,34(A0)
  DEF_ROMLOC(9FF8) : tst_mem_8(A0 + 0x28);            // TST.B	40(A0)
  DEF_ROMLOC(9FFC) : if (CCR_EQ) {
    rom_A012();
    return;
  } // BEQ.B	$A012
  DEF_ROMLOC(9FFE) : move_tomem_8(0x8, A0 + 0x24); // MOVE.B	#$08,36(A0)
  DEF_ROMLOC(A004)
      : move_tomem_8(0xFFFFFF87, A0 + 0x20);       // MOVE.B	#$87,32(A0)
  DEF_ROMLOC(A00A) : move_tomem_8(0x1, A0 + 0x1C); // MOVE.B	#$01,28(A0)
  rom_A086();                                      // BRA.B	$A086
}
ROMFUNC(rom_A012) {
  DEF_ROMLOC(A012) : rom_A022();                 // BSR.B	$A022
  DEF_ROMLOC(A014) : move_toreg_32(0xA0A8, &A1); // LEA.L	$0000A0A8,A1
  DEF_ROMLOC(A01A) : animate_sprite();           // BSR.W	$ADA2
  queue_sprite();                                // BRA.W	$DC92
}
ROMFUNC(rom_A022) {
  DEF_ROMLOC(A022)
      : move_toreg_32(read_32(A0 + 0x3C), &A1); // MOVEA.L	60(A0),A1
  DEF_ROMLOC(A026)
      : cmp_tomem_8(OBJ_EXPLOSIONITEM,
                    A1 + offsetof(object, id)); // CMPI.B	#$27,0(A1)
  DEF_ROMLOC(A02C) : if (CCR_EQ) {
    rom_A076();
    return;
  } // BEQ.B	$A076
  DEF_ROMLOC(A02E) : return; // RTS
}
ROMFUNC(rom_A030) {
  DEF_ROMLOC(A030) : btst_tomem_8(0x7, A0 + 0x22); // BTST.B	#$07,34(A0)
  DEF_ROMLOC(A036) : if (!CCR_EQ) goto rom_A066;   // BNE.B	$A066
  DEF_ROMLOC(A038)
      : move_tomem_8(0xFFFFFF87, A0 + 0x20);       // MOVE.B	#$87,32(A0)
  DEF_ROMLOC(A03E) : move_tomem_8(0x1, A0 + 0x1C); // MOVE.B	#$01,28(A0)
  DEF_ROMLOC(A044) : rom_DC6C();                   // BSR.W	$DC6C
  DEF_ROMLOC(A048) : move_toreg_32(0xA0A8, &A1);   // LEA.L	$0000A0A8,A1
  DEF_ROMLOC(A04E) : animate_sprite();             // BSR.W	$ADA2
  DEF_ROMLOC(A052) : queue_sprite();               // BSR.W	$DC92
  DEF_ROMLOC(A056)
      : move_toreg_16(read_16(0xFFFFF72E), &D0);           // MOVE.W	$F72E,D0
  DEF_ROMLOC(A05A) : add_toreg_16(0xE0, &D0);              // ADDI.W	#$00E0,D0
  DEF_ROMLOC(A05E) : cmp_toreg_16(read_16(A0 + 0xC), &D0); // CMP.W
                                                           // 12(A0),D0
  DEF_ROMLOC(A062) : if (CCR_CS) {
    rom_A076();
    return;
  } // BCS.B	$A076
  DEF_ROMLOC(A064) : return; // RTS
  DEF_ROMLOC(A066)
      : move_tomem_8(OBJ_MISSILEDISSOLVE,
                     A0 + offsetof(object, id));   // MOVE.B	#$24,0(A0)
  DEF_ROMLOC(A06C) : move_tomem_8(0x0, A0 + 0x24); // MOVE.B	#$00,36(A0)
  rom_9370();
  return; // BRA.W	$9370
}
ROMFUNC(rom_A076) {
  DEF_ROMLOC(A076) : rom_DCCE(); // BSR.W	$DCCE
  DEF_ROMLOC(A07A) : return;     // RTS
}
ROMFUNC(rom_A07C) {
  DEF_ROMLOC(A07C) : tst_mem_8(A0 + 0x1); // TST.B	1(A0)
  DEF_ROMLOC(A080) : if (CCR_PL) {
    rom_A076();
    return;
  } // BPL.B	$A076
  DEF_ROMLOC(A082) : rom_DC6C(); // BSR.W	$DC6C
  rom_A086();
}
ROMFUNC(rom_A086) {
  DEF_ROMLOC(A086) : move_toreg_32(0xA0A8, &A1); // LEA.L	$0000A0A8,A1
  DEF_ROMLOC(A08C) : animate_sprite();           // BSR.W	$ADA2
  DEF_ROMLOC(A090) : queue_sprite();             // BSR.W	$DC92
  DEF_ROMLOC(A094) : return;                     // RTS
}