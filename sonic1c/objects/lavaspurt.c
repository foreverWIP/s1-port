// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_F4FC) {
  u8 switchindex = 0;
  DEF_ROMLOC(F4FC) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(F4FE) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(F502)
      : move_toreg_16(read_16(0xF50E + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	10(PC,D0),D1
  // DEF_ROMLOC(F506): rom_F50E + (s16)(D1 & 0xffff)(); // JSR	6(PC,D1)
  DEF_ROMLOC(F506) : switch (switchindex) {
  case 0:
    rom_F51A();
    break;
  case 1:
    rom_F606();
    break;
  case 2:
    rom_F688();
    break;
  case 3:
    rom_F6E6();
    break;
  }
  rom_DC92(); // BRA.W	$DC92
}
ROMFUNC(rom_F546) {
  DEF_ROMLOC(F546) : rom_E130();                      // BSR.W	$E130
  DEF_ROMLOC(F54A) : if (!CCR_EQ) goto rom_F596;      // BNE.B	$F596
  DEF_ROMLOC(F54C) : move_tomem_8(0x4D, A1 + 0x0);    // MOVE.B	#$4D,0(A1)
  DEF_ROMLOC(F552) : move_tomem_32(0xF8D6, A1 + 0x4); // MOVE.L	#$0000F8D6,4(A1)
  DEF_ROMLOC(F55A) : move_tomem_16(0x63A8, A1 + 0x2); // MOVE.W	#$63A8,2(A1)
  DEF_ROMLOC(F560) : move_tomem_8(0x4, A1 + 0x1);     // MOVE.B	#$04,1(A1)
  DEF_ROMLOC(F566) : move_tomem_8(0x20, A1 + 0x19);   // MOVE.B	#$20,25(A1)
  DEF_ROMLOC(F56C)
      : move_tomem_16(read_16(A0 + 0x8), A1 + 0x8); // MOVE.W	8(A0),8(A1)
  DEF_ROMLOC(F572)
      : move_tomem_16(read_16(A0 + 0xC), A1 + 0xC); // MOVE.W	12(A0),12(A1)
  DEF_ROMLOC(F578)
      : move_tomem_8(read_8(A0 + 0x28), A1 + 0x28); // MOVE.B	40(A0),40(A1)
  DEF_ROMLOC(F57E) : move_tomem_8(0x1, A1 + 0x18);  // MOVE.B	#$01,24(A1)
  DEF_ROMLOC(F584) : move_tomem_8(0x5, A1 + 0x1C);  // MOVE.B	#$05,28(A1)
  DEF_ROMLOC(F58A) : tst_mem_8(A0 + 0x28);          // TST.B	40(A0)
  DEF_ROMLOC(F58E) : if (CCR_EQ) goto rom_F596;     // BEQ.B	$F596
  DEF_ROMLOC(F590) : move_tomem_8(0x2, A1 + 0x1C);  // MOVE.B	#$02,28(A1)
  DEF_ROMLOC(F596) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_F546;           // DBF.W	D1,$F546
  DEF_ROMLOC(F59A) : return; // RTS
}
ROMFUNC(rom_F54C) {
  DEF_ROMLOC(F54C) : move_tomem_8(0x4D, A1 + 0x0);    // MOVE.B	#$4D,0(A1)
  DEF_ROMLOC(F552) : move_tomem_32(0xF8D6, A1 + 0x4); // MOVE.L	#$0000F8D6,4(A1)
  DEF_ROMLOC(F55A) : move_tomem_16(0x63A8, A1 + 0x2); // MOVE.W	#$63A8,2(A1)
  DEF_ROMLOC(F560) : move_tomem_8(0x4, A1 + 0x1);     // MOVE.B	#$04,1(A1)
  DEF_ROMLOC(F566) : move_tomem_8(0x20, A1 + 0x19);   // MOVE.B	#$20,25(A1)
  DEF_ROMLOC(F56C)
      : move_tomem_16(read_16(A0 + 0x8), A1 + 0x8); // MOVE.W	8(A0),8(A1)
  DEF_ROMLOC(F572)
      : move_tomem_16(read_16(A0 + 0xC), A1 + 0xC); // MOVE.W	12(A0),12(A1)
  DEF_ROMLOC(F578)
      : move_tomem_8(read_8(A0 + 0x28), A1 + 0x28); // MOVE.B	40(A0),40(A1)
  DEF_ROMLOC(F57E) : move_tomem_8(0x1, A1 + 0x18);  // MOVE.B	#$01,24(A1)
  DEF_ROMLOC(F584) : move_tomem_8(0x5, A1 + 0x1C);  // MOVE.B	#$05,28(A1)
  DEF_ROMLOC(F58A) : tst_mem_8(A0 + 0x28);          // TST.B	40(A0)
  DEF_ROMLOC(F58E) : if (CCR_EQ) goto rom_F596;     // BEQ.B	$F596
  DEF_ROMLOC(F590) : move_tomem_8(0x2, A1 + 0x1C);  // MOVE.B	#$02,28(A1)
  DEF_ROMLOC(F596) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff) {
    rom_F546();
    return;
  }                          // DBF.W	D1,$F546
  DEF_ROMLOC(F59A) : return; // RTS
}
ROMFUNC(rom_F51A) {
  DEF_ROMLOC(F51A) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(F51E)
      : move_tomem_16(read_16(A0 + 0xC), A0 + 0x30); // MOVE.W	12(A0),48(A0)
  DEF_ROMLOC(F524) : tst_mem_8(A0 + 0x28);           // TST.B	40(A0)
  DEF_ROMLOC(F528) : if (CCR_EQ) goto rom_F530;      // BEQ.B	$F530
  DEF_ROMLOC(F52A) : sub_tomem_16(0x250, A0 + 0xC);  // SUBI.W	#$0250,12(A0)
  DEF_ROMLOC(F530) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(F532) : move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B
                                                           // 40(A0),D0
  DEF_ROMLOC(F536) : add_toreg_16(D0, &D0);                // ADD.W	D0,D0
  DEF_ROMLOC(F538)
      : move_tomem_16(read_16(0xF516 + (s16)(D0 & 0xffff)),
                      A0 + 0x12);                  // MOVE.W	-36(PC,D0),18(A0)
  DEF_ROMLOC(F53E) : move_toreg_32(A0, &A1);       // MOVEA.L	A0,A1
  DEF_ROMLOC(F540) : move_toreg_32(0x1, &D1);      // MOVEQ.L	$01,D1
  DEF_ROMLOC(F542) : rom_F54C();                   // BSR.B	$F54C
  DEF_ROMLOC(F544) : goto rom_F59C;                // BRA.B	$F59C
  DEF_ROMLOC(F546) : rom_E130();                   // BSR.W	$E130
  DEF_ROMLOC(F54A) : if (!CCR_EQ) goto rom_F596;   // BNE.B	$F596
  DEF_ROMLOC(F54C) : move_tomem_8(0x4D, A1 + 0x0); // MOVE.B	#$4D,0(A1)
  DEF_ROMLOC(F552) : move_tomem_32(0xF8D6, A1 + 0x4); // MOVE.L	#$0000F8D6,4(A1)
  DEF_ROMLOC(F55A) : move_tomem_16(0x63A8, A1 + 0x2); // MOVE.W	#$63A8,2(A1)
  DEF_ROMLOC(F560) : move_tomem_8(0x4, A1 + 0x1);     // MOVE.B	#$04,1(A1)
  DEF_ROMLOC(F566) : move_tomem_8(0x20, A1 + 0x19);   // MOVE.B	#$20,25(A1)
  DEF_ROMLOC(F56C)
      : move_tomem_16(read_16(A0 + 0x8), A1 + 0x8); // MOVE.W	8(A0),8(A1)
  DEF_ROMLOC(F572)
      : move_tomem_16(read_16(A0 + 0xC), A1 + 0xC); // MOVE.W	12(A0),12(A1)
  DEF_ROMLOC(F578)
      : move_tomem_8(read_8(A0 + 0x28), A1 + 0x28); // MOVE.B	40(A0),40(A1)
  DEF_ROMLOC(F57E) : move_tomem_8(0x1, A1 + 0x18);  // MOVE.B	#$01,24(A1)
  DEF_ROMLOC(F584) : move_tomem_8(0x5, A1 + 0x1C);  // MOVE.B	#$05,28(A1)
  DEF_ROMLOC(F58A) : tst_mem_8(A0 + 0x28);          // TST.B	40(A0)
  DEF_ROMLOC(F58E) : if (CCR_EQ) goto rom_F596;     // BEQ.B	$F596
  DEF_ROMLOC(F590) : move_tomem_8(0x2, A1 + 0x1C);  // MOVE.B	#$02,28(A1)
  DEF_ROMLOC(F596) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_F546;                                 // DBF.W	D1,$F546
  DEF_ROMLOC(F59A) : return;                       // RTS
  DEF_ROMLOC(F59C) : add_tomem_16(0x60, A1 + 0xC); // ADDI.W	#$0060,12(A1)
  DEF_ROMLOC(F5A2)
      : move_tomem_16(read_16(A0 + 0x30), A1 + 0x30); // MOVE.W	48(A0),48(A1)
  DEF_ROMLOC(F5A8) : add_tomem_16(0x60, A1 + 0x30);   // ADDI.W	#$0060,48(A1)
  DEF_ROMLOC(F5AE) : move_tomem_8(0xFFFFFF93, A1 + 0x20); // MOVE.B
                                                          // #$93,32(A1)
  DEF_ROMLOC(F5B4)
      : move_tomem_8(0xFFFFFF80, A1 + 0x16);        // MOVE.B	#$80,22(A1)
  DEF_ROMLOC(F5BA) : bset_tomem_8(0x4, A1 + 0x1);   // BSET.B	#$04,1(A1)
  DEF_ROMLOC(F5C0) : add_tomem_8(0x4, A1 + 0x24);   // ADDQ.B	#$04,36(A1)
  DEF_ROMLOC(F5C4) : move_tomem_32(A0, A1 + 0x3C);  // MOVE.L	A0,60(A1)
  DEF_ROMLOC(F5C8) : tst_mem_8(A0 + 0x28);          // TST.B	40(A0)
  DEF_ROMLOC(F5CC) : if (CCR_EQ) goto rom_F5FC;     // BEQ.B	$F5FC
  DEF_ROMLOC(F5CE) : move_toreg_32(0x0, &D1);       // MOVEQ.L	$00,D1
  DEF_ROMLOC(F5D0) : rom_F546();                    // BSR.W	$F546
  DEF_ROMLOC(F5D4) : add_tomem_8(0x2, A1 + 0x24);   // ADDQ.B	#$02,36(A1)
  DEF_ROMLOC(F5D8) : bset_tomem_8(0x4, A1 + 0x2);   // BSET.B	#$04,2(A1)
  DEF_ROMLOC(F5DE) : add_tomem_16(0x100, A1 + 0xC); // ADDI.W	#$0100,12(A1)
  DEF_ROMLOC(F5E4) : move_tomem_8(0x0, A1 + 0x18);  // MOVE.B	#$00,24(A1)
  DEF_ROMLOC(F5EA)
      : move_tomem_16(read_16(A0 + 0x30), A1 + 0x30); // MOVE.W	48(A0),48(A1)
  DEF_ROMLOC(F5F0)
      : move_tomem_32(read_32(A0 + 0x3C), A1 + 0x3C); // MOVE.L	60(A0),60(A1)
  DEF_ROMLOC(F5F6) : move_tomem_8(0x0, A0 + 0x28);    // MOVE.B	#$00,40(A0)
  DEF_ROMLOC(F5FC) : move_toreg_16(0xC8, &D0);        // MOVE.W	#$00C8,D0
  DEF_ROMLOC(F600) : play_sound_special();            // JSR	$00001394
  rom_F606(); // Detected flow into next function
}
ROMFUNC(rom_F606) {
  u8 switchindex = 0;
  DEF_ROMLOC(F606) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(F608) : move_toreg_8(read_8(A0 + 0x28), &D0);
  switchindex = D0 / 2;                     // MOVE.B	40(A0),D0
  DEF_ROMLOC(F60C) : add_toreg_16(D0, &D0); // ADD.W	D0,D0
  DEF_ROMLOC(F60E)
      : move_toreg_16(read_16(0xF644 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	52(PC,D0),D1
  // DEF_ROMLOC(F612): rom_F644 + (s16)(D1 & 0xffff)(); // JSR	48(PC,D1)
  DEF_ROMLOC(F612) : switch (switchindex) {
  case 0:
    rom_F648();
    break;
  case 1:
    rom_F668();
    break;
  }
  DEF_ROMLOC(F616) : rom_DC6C();                 // BSR.W	$DC6C
  DEF_ROMLOC(F61A) : move_toreg_32(0xF8A0, &A1); // LEA.L	$0000F8A0,A1
  DEF_ROMLOC(F620) : rom_ADA2();                 // BSR.W	$ADA2
  rom_F624(); // Detected flow into next function
}
ROMFUNC(rom_F624) {
  DEF_ROMLOC(F624) : move_toreg_16(read_16(A0 + 0x8), &D0); // MOVE.W	8(A0),D0
  DEF_ROMLOC(F628) : and_toreg_16(0xFFFFFF80, &D0);         // ANDI.W	#$FF80,D0
  DEF_ROMLOC(F62C)
      : move_toreg_16(read_16(0xFFFFF700), &D1);    // MOVE.W	$F700,D1
  DEF_ROMLOC(F630) : sub_toreg_16(0x80, &D1);       // SUBI.W	#$0080,D1
  DEF_ROMLOC(F634) : and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
  DEF_ROMLOC(F638) : sub_toreg_16(D1, &D0);         // SUB.W	D1,D0
  DEF_ROMLOC(F63A) : cmp_toreg_16(0x280, &D0);      // CMPI.W	#$0280,D0
  DEF_ROMLOC(F63E) : if (CCR_HI) {
    rom_DCCE();
    return;
  }                                         // BHI.W	$DCCE
  DEF_ROMLOC(F642) : return;                // RTS
  DEF_ROMLOC(F644) : or_toreg_8(0x24, &D4); // ORI.B	#$24,D4
  rom_F648();                               // Detected flow into next function
}
ROMFUNC(rom_F648) {
  DEF_ROMLOC(F648) : add_tomem_16(0x18, A0 + 0x12); // ADDI.W	#$0018,18(A0)
  DEF_ROMLOC(F64E)
      : move_toreg_16(read_16(A0 + 0x30), &D0); // MOVE.W	48(A0),D0
  DEF_ROMLOC(F652)
      : cmp_toreg_16(read_16(A0 + 0xC), &D0);     // CMP.W	12(A0),D0
  DEF_ROMLOC(F656) : if (CCR_CC) goto rom_F666;   // BCC.B	$F666
  DEF_ROMLOC(F658) : add_tomem_8(0x4, A0 + 0x24); // ADDQ.B	#$04,36(A0)
  DEF_ROMLOC(F65C)
      : move_toreg_32(read_32(A0 + 0x3C), &A1);    // MOVEA.L	60(A0),A1
  DEF_ROMLOC(F660) : move_tomem_8(0x3, A1 + 0x1C); // MOVE.B	#$03,28(A1)
  DEF_ROMLOC(F666) : return;                       // RTS
}
ROMFUNC(rom_F668) {
  DEF_ROMLOC(F668) : add_tomem_16(0x18, A0 + 0x12); // ADDI.W	#$0018,18(A0)
  DEF_ROMLOC(F66E)
      : move_toreg_16(read_16(A0 + 0x30), &D0); // MOVE.W	48(A0),D0
  DEF_ROMLOC(F672)
      : cmp_toreg_16(read_16(A0 + 0xC), &D0);     // CMP.W	12(A0),D0
  DEF_ROMLOC(F676) : if (CCR_CC) goto rom_F686;   // BCC.B	$F686
  DEF_ROMLOC(F678) : add_tomem_8(0x4, A0 + 0x24); // ADDQ.B	#$04,36(A0)
  DEF_ROMLOC(F67C)
      : move_toreg_32(read_32(A0 + 0x3C), &A1);    // MOVEA.L	60(A0),A1
  DEF_ROMLOC(F680) : move_tomem_8(0x1, A1 + 0x1C); // MOVE.B	#$01,28(A1)
  DEF_ROMLOC(F686) : return;                       // RTS
}
ROMFUNC(rom_F688) {
  DEF_ROMLOC(F688)
      : move_toreg_32(read_32(A0 + 0x3C), &A1);   // MOVEA.L	60(A0),A1
  DEF_ROMLOC(F68C) : cmp_tomem_8(0x6, A1 + 0x24); // CMPI.B	#$06,36(A1)
  DEF_ROMLOC(F692) : if (CCR_EQ) {
    rom_F6E6();
    return;
  } // BEQ.W	$F6E6
  DEF_ROMLOC(F696)
      : move_toreg_16(read_16(A1 + 0xC), &D0);    // MOVE.W	12(A1),D0
  DEF_ROMLOC(F69A) : add_toreg_16(0x60, &D0);     // ADDI.W	#$0060,D0
  DEF_ROMLOC(F69E) : move_tomem_16(D0, A0 + 0xC); // MOVE.W	D0,12(A0)
  DEF_ROMLOC(F6A2)
      : sub_toreg_16(read_16(A0 + 0x30), &D0);     // SUB.W	48(A0),D0
  DEF_ROMLOC(F6A6) : neg_reg_16(&D0);              // NEG.W	D0
  DEF_ROMLOC(F6A8) : move_toreg_32(0x8, &D1);      // MOVEQ.L	$08,D1
  DEF_ROMLOC(F6AA) : cmp_toreg_16(0x40, &D0);      // CMPI.W	#$0040,D0
  DEF_ROMLOC(F6AE) : if (CCR_GE) goto rom_F6B2;    // BGE.B	$F6B2
  DEF_ROMLOC(F6B0) : move_toreg_32(0xB, &D1);      // MOVEQ.L	$0B,D1
  DEF_ROMLOC(F6B2) : cmp_toreg_16(0x80, &D0);      // CMPI.W	#$0080,D0
  DEF_ROMLOC(F6B6) : if (CCR_LE) goto rom_F6BA;    // BLE.B	$F6BA
  DEF_ROMLOC(F6B8) : move_toreg_32(0xE, &D1);      // MOVEQ.L	$0E,D1
  DEF_ROMLOC(F6BA) : sub_tomem_8(0x1, A0 + 0x1E);  // SUBQ.B	#$01,30(A0)
  DEF_ROMLOC(F6BE) : if (CCR_PL) goto rom_F6D8;    // BPL.B	$F6D8
  DEF_ROMLOC(F6C0) : move_tomem_8(0x7, A0 + 0x1E); // MOVE.B	#$07,30(A0)
  DEF_ROMLOC(F6C6) : add_tomem_8(0x1, A0 + 0x1B);  // ADDQ.B	#$01,27(A0)
  DEF_ROMLOC(F6CA) : cmp_tomem_8(0x2, A0 + 0x1B);  // CMPI.B	#$02,27(A0)
  DEF_ROMLOC(F6D0) : if (CCR_CS) goto rom_F6D8;    // BCS.B	$F6D8
  DEF_ROMLOC(F6D2) : move_tomem_8(0x0, A0 + 0x1B); // MOVE.B	#$00,27(A0)
  DEF_ROMLOC(F6D8)
      : move_toreg_8(read_8(A0 + 0x1B), &D0);     // MOVE.B	27(A0),D0
  DEF_ROMLOC(F6DC) : add_toreg_8(D1, &D0);        // ADD.B	D1,D0
  DEF_ROMLOC(F6DE) : move_tomem_8(D0, A0 + 0x1A); // MOVE.B	D0,26(A0)
  rom_F624();
  return; // BRA.W	$F624
}
ROMFUNC(rom_F6E6) {
  DEF_ROMLOC(F6E6) : rom_DCCE(); // BRA.W	$DCCE
}