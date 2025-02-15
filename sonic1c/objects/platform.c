// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_84B0) {
  u8 switchindex = 0;
  DEF_ROMLOC(84B0) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(84B2) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(84B6)
      : move_toreg_16(read_16(0x84BE + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(84BA): goto rom_84BE + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(84BA) : switch (switchindex) {
  case 0:
    rom_84C8();
    break;
  case 1:
    rom_8554();
    break;
  case 2:
    rom_8578();
    break;
  case 3:
    rom_8774();
    break;
  case 4:
    rom_8568();
    break;
  }
}
ROMFUNC(rom_84C8) {
  DEF_ROMLOC(84C8) : add_tomem_8(0x2, A0 + 0x24);     // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(84CC) : move_tomem_16(0x4000, A0 + 0x2); // MOVE.W	#$4000,2(A0)
  DEF_ROMLOC(84D2) : move_tomem_32(0x87BA, A0 + 0x4); // MOVE.L	#$000087BA,4(A0)
  DEF_ROMLOC(84DA) : move_tomem_8(0x20, A0 + 0x19);   // MOVE.B	#$20,25(A0)
  DEF_ROMLOC(84E0) : cmp_tomem_8(ZONE_SYZ, v_zone);   // CMPI.B	#$04,$FE10
  DEF_ROMLOC(84E6) : if (!CCR_EQ) goto rom_84F6;      // BNE.B	$84F6
  DEF_ROMLOC(84E8) : move_tomem_32(0x8806, A0 + 0x4); // MOVE.L	#$00008806,4(A0)
  DEF_ROMLOC(84F0) : move_tomem_8(0x20, A0 + 0x19);   // MOVE.B	#$20,25(A0)
  DEF_ROMLOC(84F6) : cmp_tomem_8(ZONE_SLZ, v_zone);   // CMPI.B	#$03,$FE10
  DEF_ROMLOC(84FC) : if (!CCR_EQ) goto rom_8518;      // BNE.B	$8518
  DEF_ROMLOC(84FE) : move_tomem_32(0x8818, A0 + 0x4); // MOVE.L	#$00008818,4(A0)
  DEF_ROMLOC(8506) : move_tomem_8(0x20, A0 + 0x19);   // MOVE.B	#$20,25(A0)
  DEF_ROMLOC(850C) : move_tomem_16(0x4000, A0 + 0x2); // MOVE.W	#$4000,2(A0)
  DEF_ROMLOC(8512) : move_tomem_8(0x3, A0 + 0x28);    // MOVE.B	#$03,40(A0)
  DEF_ROMLOC(8518) : move_tomem_8(0x4, A0 + 0x1);     // MOVE.B	#$04,1(A0)
  DEF_ROMLOC(851E) : move_tomem_8(0x4, A0 + 0x18);    // MOVE.B	#$04,24(A0)
  DEF_ROMLOC(8524)
      : move_tomem_16(read_16(A0 + 0xC), A0 + 0x2C); // MOVE.W	12(A0),44(A0)
  DEF_ROMLOC(852A)
      : move_tomem_16(read_16(A0 + 0xC), A0 + 0x34); // MOVE.W	12(A0),52(A0)
  DEF_ROMLOC(8530)
      : move_tomem_16(read_16(A0 + 0x8), A0 + 0x32); // MOVE.W	8(A0),50(A0)
  DEF_ROMLOC(8536) : move_tomem_16(0x80, A0 + 0x26); // MOVE.W	#$0080,38(A0)
  DEF_ROMLOC(853C) : move_toreg_32(0x0, &D1);        // MOVEQ.L	$00,D1
  DEF_ROMLOC(853E)
      : move_toreg_8(read_8(A0 + 0x28), &D0);       // MOVE.B
                                                    // 40(A0),D0
  DEF_ROMLOC(8542) : cmp_toreg_8(0xA, &D0);         // CMPI.B	#$0A,D0
  DEF_ROMLOC(8546) : if (!CCR_EQ) goto rom_8550;    // BNE.B	$8550
  DEF_ROMLOC(8548) : add_toreg_8(0x1, &D1);         // ADDQ.B	#$01,D1
  DEF_ROMLOC(854A) : move_tomem_8(0x20, A0 + 0x19); // MOVE.B	#$20,25(A0)
  DEF_ROMLOC(8550) : move_tomem_8(D1, A0 + 0x1A);   // MOVE.B	D1,26(A0)
  rom_8554(); // Detected flow into next function
}
ROMFUNC(rom_8554) {
  DEF_ROMLOC(8554) : tst_mem_8(A0 + 0x38);        // TST.B	56(A0)
  DEF_ROMLOC(8558) : if (CCR_EQ) goto rom_855E;   // BEQ.B	$855E
  DEF_ROMLOC(855A) : sub_tomem_8(0x4, A0 + 0x38); // SUBQ.B	#$04,56(A0)
  DEF_ROMLOC(855E) : move_toreg_32(0x0, &D1);     // MOVEQ.L	$00,D1
  DEF_ROMLOC(8560)
      : move_toreg_8(read_8(A0 + 0x19), &D1); // MOVE.B
                                              // 25(A0),D1
  DEF_ROMLOC(8564) : rom_7ACA();              // BSR.W	$7ACA
  rom_8568(); // Detected flow into next function
}
ROMFUNC(rom_8568) {
  DEF_ROMLOC(8568) : rom_85C4(); // BSR.W	$85C4
  DEF_ROMLOC(856C) : rom_85AA(); // BSR.W	$85AA
  DEF_ROMLOC(8570) : rom_DC92(); // BSR.W	$DC92
  rom_8756();                    // BRA.W	$8756
}
ROMFUNC(rom_8578) {
  DEF_ROMLOC(8578) : cmp_tomem_8(0x40, A0 + 0x38); // CMPI.B	#$40,56(A0)
  DEF_ROMLOC(857E) : if (CCR_EQ) goto rom_8584;    // BEQ.B	$8584
  DEF_ROMLOC(8580) : add_tomem_8(0x4, A0 + 0x38);  // ADDQ.B	#$04,56(A0)
  DEF_ROMLOC(8584) : move_toreg_32(0x0, &D1);      // MOVEQ.L	$00,D1
  DEF_ROMLOC(8586)
      : move_toreg_8(read_8(A0 + 0x19), &D1); // MOVE.B
                                              // 25(A0),D1
  DEF_ROMLOC(858A) : rom_7C3E();              // BSR.W	$7C3E
  DEF_ROMLOC(858E)
      : move_tomem_16(read_16(A0 + 0x8), A7 -= 2); // MOVE.W	8(A0),-(A7)
  DEF_ROMLOC(8592) : rom_85C4();                   // BSR.W	$85C4
  DEF_ROMLOC(8596) : rom_85AA();                   // BSR.W	$85AA
  DEF_ROMLOC(859A)
      : move_toreg_16(read_16((A7 += 2, A7 - 2)), &D2); // MOVE.W	(A7)+,D2
  DEF_ROMLOC(859C) : rom_81AC();                        // BSR.W	$81AC
  DEF_ROMLOC(85A0) : rom_DC92();                        // BSR.W	$DC92
  DEF_ROMLOC(85A4) : {
    rom_8756();
    return;
  }                          // BRA.W	$8756
  DEF_ROMLOC(85A8) : return; // RTS
}
ROMFUNC(rom_85AA) {
  DEF_ROMLOC(85AA)
      : move_toreg_8(read_8(A0 + 0x38), &D0);   // MOVE.B	56(A0),D0
  DEF_ROMLOC(85AE) : rom_29D2();                // BSR.W	$29D2
  DEF_ROMLOC(85B2) : move_toreg_16(0x400, &D1); // MOVE.W	#$0400,D1
  DEF_ROMLOC(85B6) : muls_toreg_16(D1, &D0);    // MULS.W	D1,D0
  DEF_ROMLOC(85B8) : swap_reg_16(&D0);          // SWAP.W	D0
  DEF_ROMLOC(85BA)
      : add_toreg_16(read_16(A0 + 0x2C), &D0);    // ADD.W	44(A0),D0
  DEF_ROMLOC(85BE) : move_tomem_16(D0, A0 + 0xC); // MOVE.W	D0,12(A0)
  DEF_ROMLOC(85C2) : return;                      // RTS
}
ROMFUNC(rom_85C4) {
  u8 switchindex = 0;
  DEF_ROMLOC(85C4) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(85C6)
      : move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B
                                              // 40(A0),D0
  DEF_ROMLOC(85CA) : and_toreg_16(0xF, &D0);
  switchindex = D0;                         // ANDI.W	#$000F,D0
  DEF_ROMLOC(85CE) : add_toreg_16(D0, &D0); // ADD.W	D0,D0
  DEF_ROMLOC(85D0)
      : move_toreg_16(read_16(0x85D8 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(85D4): goto rom_85D8 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(85D4) : switch (switchindex) {
  case 0:
    rom_85F2();
    return;
  case 1:
    rom_8604();
    return;
  case 2:
    rom_864A();
    return;
  case 3:
    rom_8662();
    return;
  case 4:
    rom_868A();
    return;
  case 5:
    rom_85F4();
    return;
  case 6:
    rom_863A();
    return;
  case 7:
    rom_86F4();
    return;
  case 8:
    rom_8720();
    return;
  case 9:
    rom_85F2();
    return;
  case 10:
    rom_8738();
    return;
  case 11:
    rom_862C();
    return;
  case 12:
    rom_861C();
    return;
  }
}
ROMFUNC(rom_85F2) {
  DEF_ROMLOC(85F2) : return; // RTS
}
ROMFUNC(rom_85F4) {
  DEF_ROMLOC(85F4)
      : move_toreg_16(read_16(A0 + 0x32), &D0); // MOVE.W	50(A0),D0
  DEF_ROMLOC(85F8)
      : move_toreg_8(read_8(A0 + 0x26), &D1); // MOVE.B
                                              // 38(A0),D1
  DEF_ROMLOC(85FC) : neg_reg_8(&D1);          // NEG.B	D1
  DEF_ROMLOC(85FE) : add_toreg_8(0x40, &D1);  // ADDI.B	#$40,D1
  rom_8610();                                 // BRA.B	$8610
}
ROMFUNC(rom_8604) {
  DEF_ROMLOC(8604)
      : move_toreg_16(read_16(A0 + 0x32), &D0); // MOVE.W	50(A0),D0
  DEF_ROMLOC(8608)
      : move_toreg_8(read_8(A0 + 0x26), &D1); // MOVE.B
                                              // 38(A0),D1
  DEF_ROMLOC(860C) : sub_toreg_8(0x40, &D1);  // SUBI.B	#$40,D1
  rom_8610(); // Detected flow into next function
}
ROMFUNC(rom_8610) {
  DEF_ROMLOC(8610) : ext_reg_16(&D1);             // EXT.W	D1
  DEF_ROMLOC(8612) : add_toreg_16(D1, &D0);       // ADD.W	D1,D0
  DEF_ROMLOC(8614) : move_tomem_16(D0, A0 + 0x8); // MOVE.W	D0,8(A0)
  rom_874E();                                     // BRA.W	$874E
}
ROMFUNC(rom_861C) {
  DEF_ROMLOC(861C)
      : move_toreg_16(read_16(A0 + 0x34), &D0); // MOVE.W	52(A0),D0
  DEF_ROMLOC(8620)
      : move_toreg_8(read_8(0xFFFFFE6C), &D1); // MOVE.B	$FE6C,D1
  DEF_ROMLOC(8624) : neg_reg_8(&D1);           // NEG.B	D1
  DEF_ROMLOC(8626) : add_toreg_8(0x30, &D1);   // ADDI.B	#$30,D1
  rom_8656();                                  // BRA.B	$8656
}
ROMFUNC(rom_862C) {
  DEF_ROMLOC(862C)
      : move_toreg_16(read_16(A0 + 0x34), &D0); // MOVE.W	52(A0),D0
  DEF_ROMLOC(8630)
      : move_toreg_8(read_8(0xFFFFFE6C), &D1); // MOVE.B	$FE6C,D1
  DEF_ROMLOC(8634) : sub_toreg_8(0x30, &D1);   // SUBI.B	#$30,D1
  rom_8656();                                  // BRA.B	$8656
}
ROMFUNC(rom_863A) {
  DEF_ROMLOC(863A)
      : move_toreg_16(read_16(A0 + 0x34), &D0); // MOVE.W	52(A0),D0
  DEF_ROMLOC(863E)
      : move_toreg_8(read_8(A0 + 0x26), &D1); // MOVE.B
                                              // 38(A0),D1
  DEF_ROMLOC(8642) : neg_reg_8(&D1);          // NEG.B	D1
  DEF_ROMLOC(8644) : add_toreg_8(0x40, &D1);  // ADDI.B	#$40,D1
  rom_8656();                                 // BRA.B	$8656
}
ROMFUNC(rom_864A) {
  DEF_ROMLOC(864A)
      : move_toreg_16(read_16(A0 + 0x34), &D0); // MOVE.W	52(A0),D0
  DEF_ROMLOC(864E)
      : move_toreg_8(read_8(A0 + 0x26), &D1); // MOVE.B
                                              // 38(A0),D1
  DEF_ROMLOC(8652) : sub_toreg_8(0x40, &D1);  // SUBI.B	#$40,D1
  rom_8656(); // Detected flow into next function
}
ROMFUNC(rom_8656) {
  DEF_ROMLOC(8656) : ext_reg_16(&D1);              // EXT.W	D1
  DEF_ROMLOC(8658) : add_toreg_16(D1, &D0);        // ADD.W	D1,D0
  DEF_ROMLOC(865A) : move_tomem_16(D0, A0 + 0x2C); // MOVE.W	D0,44(A0)
  rom_874E();                                      // BRA.W	$874E
}
ROMFUNC(rom_8662) {
  DEF_ROMLOC(8662) : tst_mem_16(A0 + 0x3A); // TST.W	58(A0)
  DEF_ROMLOC(8666) : if (!CCR_EQ) {
    rom_8678();
    return;
  }                                                // BNE.B	$8678
  DEF_ROMLOC(8668) : btst_tomem_8(0x3, A0 + 0x22); // BTST.B	#$03,34(A0)
  DEF_ROMLOC(866E) : if (CCR_EQ) {
    rom_8676();
    return;
  }                                                  // BEQ.B	$8676
  DEF_ROMLOC(8670) : move_tomem_16(0x1E, A0 + 0x3A); // MOVE.W	#$001E,58(A0)
  rom_8676(); // Detected flow into next function
}
ROMFUNC(rom_8676) {
  DEF_ROMLOC(8676) : return; // RTS
}
ROMFUNC(rom_8678) {
  DEF_ROMLOC(8678) : sub_tomem_16(0x1, A0 + 0x3A); // SUBQ.W	#$01,58(A0)
  DEF_ROMLOC(867C) : if (!CCR_EQ) {
    rom_8676();
    return;
  }                                                  // BNE.B	$8676
  DEF_ROMLOC(867E) : move_tomem_16(0x20, A0 + 0x3A); // MOVE.W	#$0020,58(A0)
  DEF_ROMLOC(8684) : add_tomem_8(0x1, A0 + 0x28);    // ADDQ.B	#$01,40(A0)
  DEF_ROMLOC(8688) : return;                         // RTS
}
ROMFUNC(rom_868A) {
  DEF_ROMLOC(868A) : tst_mem_16(A0 + 0x3A); // TST.W	58(A0)
  DEF_ROMLOC(868E) : if (CCR_EQ) {
    rom_86C6();
    return;
  }                                                // BEQ.B	$86C6
  DEF_ROMLOC(8690) : sub_tomem_16(0x1, A0 + 0x3A); // SUBQ.W	#$01,58(A0)
  DEF_ROMLOC(8694) : if (!CCR_EQ) {
    rom_86C6();
    return;
  }                                                // BNE.B	$86C6
  DEF_ROMLOC(8696) : btst_tomem_8(0x3, A0 + 0x22); // BTST.B	#$03,34(A0)
  DEF_ROMLOC(869C) : if (CCR_EQ) {
    rom_86C0();
    return;
  }                                                // BEQ.B	$86C0
  DEF_ROMLOC(869E) : bset_tomem_8(0x1, A1 + 0x22); // BSET.B	#$01,34(A1)
  DEF_ROMLOC(86A4) : bclr_tomem_8(0x3, A1 + 0x22); // BCLR.B	#$03,34(A1)
  DEF_ROMLOC(86AA) : move_tomem_8(0x2, A1 + 0x24); // MOVE.B	#$02,36(A1)
  DEF_ROMLOC(86B0) : bclr_tomem_8(0x3, A0 + 0x22); // BCLR.B	#$03,34(A0)
  DEF_ROMLOC(86B6) : clr_mem_8(A0 + 0x25);         // CLR.B	37(A0)
  DEF_ROMLOC(86BA)
      : move_tomem_16(read_16(A0 + 0x12), A1 + 0x12); // MOVE.W	18(A0),18(A1)
  rom_86C0(); // Detected flow into next function
}
ROMFUNC(rom_86C0) {
  DEF_ROMLOC(86C0) : move_tomem_8(0x8, A0 + 0x24); // MOVE.B	#$08,36(A0)
  rom_86C6(); // Detected flow into next function
}
ROMFUNC(rom_86C6) {
  DEF_ROMLOC(86C6)
      : move_toreg_32(read_32(A0 + 0x2C), &D3); // MOVE.L	44(A0),D3
  DEF_ROMLOC(86CA)
      : move_toreg_16(read_16(A0 + 0x12), &D0);     // MOVE.W	18(A0),D0
  DEF_ROMLOC(86CE) : ext_reg_32(&D0);               // EXT.L	D0
  DEF_ROMLOC(86D0) : asl_toreg_32(0x8, &D0);        // ASL.L	#$08,D0
  DEF_ROMLOC(86D2) : add_toreg_32(D0, &D3);         // ADD.L	D0,D3
  DEF_ROMLOC(86D4) : move_tomem_32(D3, A0 + 0x2C);  // MOVE.L	D3,44(A0)
  DEF_ROMLOC(86D8) : add_tomem_16(0x38, A0 + 0x12); // ADDI.W	#$0038,18(A0)
  DEF_ROMLOC(86DE)
      : move_toreg_16(read_16(0xFFFFF72E), &D0); // MOVE.W	$F72E,D0
  DEF_ROMLOC(86E2) : add_toreg_16(0xE0, &D0);    // ADDI.W	#$00E0,D0
  DEF_ROMLOC(86E6)
      : cmp_toreg_16(read_16(A0 + 0x2C), &D0); // CMP.W
                                               // 44(A0),D0
  DEF_ROMLOC(86EA) : if (CCR_CC) {
    rom_86F2();
    return;
  }                                                // BCC.B	$86F2
  DEF_ROMLOC(86EC) : move_tomem_8(0x6, A0 + 0x24); // MOVE.B	#$06,36(A0)
  rom_86F2(); // Detected flow into next function
}
ROMFUNC(rom_86F2) {
  DEF_ROMLOC(86F2) : return; // RTS
}
ROMFUNC(rom_86F4) {
  DEF_ROMLOC(86F4) : tst_mem_16(A0 + 0x3A); // TST.W	58(A0)
  DEF_ROMLOC(86F8) : if (!CCR_EQ) {
    rom_8714();
    return;
  }                                                  // BNE.B	$8714
  DEF_ROMLOC(86FA) : move_toreg_32(0xFFFFF7E0, &A2); // LEA.L	$F7E0,A2
  DEF_ROMLOC(86FE) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(8700)
      : move_toreg_8(read_8(A0 + 0x28), &D0);                // MOVE.B
                                                             // 40(A0),D0
  DEF_ROMLOC(8704) : lsr_toreg_16(0x4, &D0);                 // LSR.W	#$04,D0
  DEF_ROMLOC(8706) : tst_mem_8((s32)A2 + (s8)0x0 + (s16)D0); // TST.B	0(A2,D0)
  DEF_ROMLOC(870A) : if (CCR_EQ) {
    rom_8712();
    return;
  }                                                  // BEQ.B	$8712
  DEF_ROMLOC(870C) : move_tomem_16(0x3C, A0 + 0x3A); // MOVE.W	#$003C,58(A0)
  rom_8712(); // Detected flow into next function
}
ROMFUNC(rom_8712) {
  DEF_ROMLOC(8712) : return; // RTS
}
ROMFUNC(rom_8714) {
  DEF_ROMLOC(8714) : sub_tomem_16(0x1, A0 + 0x3A); // SUBQ.W	#$01,58(A0)
  DEF_ROMLOC(8718) : if (!CCR_EQ) {
    rom_8712();
    return;
  }                                               // BNE.B	$8712
  DEF_ROMLOC(871A) : add_tomem_8(0x1, A0 + 0x28); // ADDQ.B	#$01,40(A0)
  DEF_ROMLOC(871E) : return;                      // RTS
}
ROMFUNC(rom_8720) {
  DEF_ROMLOC(8720) : sub_tomem_16(0x2, A0 + 0x2C); // SUBQ.W	#$02,44(A0)
  DEF_ROMLOC(8724)
      : move_toreg_16(read_16(A0 + 0x34), &D0); // MOVE.W	52(A0),D0
  DEF_ROMLOC(8728) : sub_toreg_16(0x200, &D0);  // SUBI.W	#$0200,D0
  DEF_ROMLOC(872C)
      : cmp_toreg_16(read_16(A0 + 0x2C), &D0); // CMP.W
                                               // 44(A0),D0
  DEF_ROMLOC(8730) : if (!CCR_EQ) {
    rom_8736();
    return;
  }                                        // BNE.B	$8736
  DEF_ROMLOC(8732) : clr_mem_8(A0 + 0x28); // CLR.B	40(A0)
  rom_8736();                              // Detected flow into next function
}
ROMFUNC(rom_8736) {
  DEF_ROMLOC(8736) : return; // RTS
}
ROMFUNC(rom_8738) {
  DEF_ROMLOC(8738)
      : move_toreg_16(read_16(A0 + 0x34), &D0); // MOVE.W	52(A0),D0
  DEF_ROMLOC(873C)
      : move_toreg_8(read_8(A0 + 0x26), &D1);      // MOVE.B	38(A0),D1
  DEF_ROMLOC(8740) : sub_toreg_8(0x40, &D1);       // SUBI.B	#$40,D1
  DEF_ROMLOC(8744) : ext_reg_16(&D1);              // EXT.W	D1
  DEF_ROMLOC(8746) : asr_toreg_16(0x1, &D1);       // ASR.W	#$01,D1
  DEF_ROMLOC(8748) : add_toreg_16(D1, &D0);        // ADD.W	D1,D0
  DEF_ROMLOC(874A) : move_tomem_16(D0, A0 + 0x2C); // MOVE.W	D0,44(A0)
  rom_874E(); // Detected flow into next function
}
ROMFUNC(rom_874E) {
  DEF_ROMLOC(874E)
      : move_tomem_8(read_8(0xFFFFFE78), A0 + 0x26); // MOVE.B	$FE78,38(A0)
  DEF_ROMLOC(8754) : return;                         // RTS
}
ROMFUNC(rom_8756) {
  DEF_ROMLOC(8756)
      : move_toreg_16(read_16(A0 + 0x32), &D0);     // MOVE.W	50(A0),D0
  DEF_ROMLOC(875A) : and_toreg_16(0xFFFFFF80, &D0); // ANDI.W	#$FF80,D0
  DEF_ROMLOC(875E)
      : move_toreg_16(read_16(0xFFFFF700), &D1);    // MOVE.W	$F700,D1
  DEF_ROMLOC(8762) : sub_toreg_16(0x80, &D1);       // SUBI.W	#$0080,D1
  DEF_ROMLOC(8766) : and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
  DEF_ROMLOC(876A) : sub_toreg_16(D1, &D0);         // SUB.W	D1,D0
  DEF_ROMLOC(876C) : cmp_toreg_16(0x280, &D0);      // CMPI.W	#$0280,D0
  DEF_ROMLOC(8770) : if (CCR_HI) {
    rom_8774();
    return;
  }                          // BHI.B	$8774
  DEF_ROMLOC(8772) : return; // RTS
}
ROMFUNC(rom_8774) {
  DEF_ROMLOC(8774) : rom_DCCE(); // BRA.W	$DCCE
}