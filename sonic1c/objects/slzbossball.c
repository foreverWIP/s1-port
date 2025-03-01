// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_1947E) {
  u8 switchindex = 0;
  DEF_ROMLOC(1947E) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(19480) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(19484)
      : move_toreg_16(read_16(0x194B4 + (s16)(D0 & 0xffff)),
                      &D0); // MOVE.W	46(PC,D0),D0
  // DEF_ROMLOC(19488): rom_194B4 + (s16)(D0 & 0xffff)(); // JSR
  // 42(PC,D0)
  DEF_ROMLOC(19488) : switch (switchindex) {
  case 0:
    rom_194C0();
    break;
  case 1:
    rom_1951C();
    break;
  case 2:
    rom_19576();
    break;
  case 3:
    rom_1965A();
    break;
  case 4:
    rom_197DA();
    break;
  case 5:
    rom_19860();
    break;
  }
  DEF_ROMLOC(1948C)
      : move_toreg_16(read_16(A0 + 0x30), &D0);      // MOVE.W	48(A0),D0
  DEF_ROMLOC(19490) : and_toreg_16(0xFFFFFF80, &D0); // ANDI.W	#$FF80,D0
  DEF_ROMLOC(19494)
      : move_toreg_16(read_16(v_screenposx), &D1);   // MOVE.W	$F700,D1
  DEF_ROMLOC(19498) : sub_toreg_16(0x80, &D1);       // SUBI.W	#$0080,D1
  DEF_ROMLOC(1949C) : and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
  DEF_ROMLOC(194A0) : sub_toreg_16(D1, &D0);         // SUB.W	D1,D0
  DEF_ROMLOC(194A2) : if (CCR_MI) {
    rom_19062();
    return;
  } // BMI.W	$19062
  DEF_ROMLOC(194A6)
      : cmp_toreg_16(128 + GAME_WIDTH + 192, &D0); // CMPI.W	#$0280,D0
  DEF_ROMLOC(194AA) : if (CCR_HI) {
    rom_19062();
    return;
  } // BHI.W	$19062
  DEF_ROMLOC(194AE) : rom_DC92();
  return; // JMP	$0000DC92
}
ROMFUNC(rom_194C0) {
  DEF_ROMLOC(194C0)
      : move_tomem_32(0x120BA, A0 + 0x4);             // MOVE.L	#$000120BA,4(A0)
  DEF_ROMLOC(194C8) : move_tomem_16(0x518, A0 + 0x2); // MOVE.W	#$0518,2(A0)
  DEF_ROMLOC(194CE) : move_tomem_8(0x1, A0 + 0x1A);   // MOVE.B	#$01,26(A0)
  DEF_ROMLOC(194D4) : or_tomem_8(0x4, A0 + 0x1);      // ORI.B	#$04,1(A0)
  DEF_ROMLOC(194DA) : move_tomem_8(0x4, A0 + 0x18);   // MOVE.B	#$04,24(A0)
  DEF_ROMLOC(194E0)
      : move_tomem_8(0xFFFFFF8B, A0 + 0x20);        // MOVE.B	#$8B,32(A0)
  DEF_ROMLOC(194E6) : move_tomem_8(0xC, A0 + 0x19); // MOVE.B	#$0C,25(A0)
  DEF_ROMLOC(194EC)
      : move_toreg_32(read_32(A0 + 0x3C), &A1); // MOVEA.L	60(A0),A1
  DEF_ROMLOC(194F0)
      : move_tomem_16(read_16(A1 + 0x8), A0 + 0x30); // MOVE.W	8(A1),48(A0)
  DEF_ROMLOC(194F6)
      : move_tomem_16(read_16(A1 + 0xC), A0 + 0x34); // MOVE.W	12(A1),52(A0)
  DEF_ROMLOC(194FC) : bset_tomem_8(0x0, A0 + 0x22);  // BSET.B	#$00,34(A0)
  DEF_ROMLOC(19502)
      : move_toreg_16(read_16(A0 + 0x8), &D0);              // MOVE.W	8(A0),D0
  DEF_ROMLOC(19506) : cmp_toreg_16(read_16(A1 + 0x8), &D0); // CMP.W	8(A1),D0
  DEF_ROMLOC(1950A) : if (CCR_GT) goto rom_19518;           // BGT.B	$19518
  DEF_ROMLOC(1950C) : bclr_tomem_8(0x0, A0 + 0x22); // BCLR.B	#$00,34(A0)
  DEF_ROMLOC(19512) : move_tomem_8(0x2, A0 + 0x3A); // MOVE.B	#$02,58(A0)
  DEF_ROMLOC(19518) : add_tomem_8(0x2, A0 + 0x24);  // ADDQ.B	#$02,36(A0)
  rom_1951C(); // Detected flow into next function
}
ROMFUNC(rom_1951C) {
  DEF_ROMLOC(1951C) : rom_DC40(); // JSR	$0000DC40
  DEF_ROMLOC(19522)
      : move_toreg_32(read_32(A0 + 0x3C), &A1);    // MOVEA.L	60(A0),A1
  DEF_ROMLOC(19526) : move_toreg_32(0x197C8, &A2); // LEA.L	$000197C8,A2
  DEF_ROMLOC(1952C) : move_toreg_32(0x0, &D0);     // MOVEQ.L	$00,D0
  DEF_ROMLOC(1952E)
      : move_toreg_8(read_8(A1 + 0x1A), &D0); // MOVE.B
                                              // 26(A1),D0
  DEF_ROMLOC(19532)
      : move_toreg_16(read_16(A0 + 0x8), &D1); // MOVE.W	8(A0),D1
  DEF_ROMLOC(19536)
      : sub_toreg_16(read_16(A0 + 0x30), &D1);    // SUB.W	48(A0),D1
  DEF_ROMLOC(1953A) : if (CCR_CC) goto rom_1953E; // BCC.B	$1953E
  DEF_ROMLOC(1953C) : add_toreg_16(0x2, &D0);     // ADDQ.W	#$02,D0
  DEF_ROMLOC(1953E) : add_toreg_16(D0, &D0);      // ADD.W	D0,D0
  DEF_ROMLOC(19540)
      : move_toreg_16(read_16(A0 + 0x34), &D1); // MOVE.W	52(A0),D1
  DEF_ROMLOC(19544)
      : add_toreg_16(read_16((s32)A2 + (s8)0x0 + (s16)D0),
                     &D1); // ADD.W	0(A2,D0),D1
  DEF_ROMLOC(19548)
      : cmp_toreg_16(read_16(A0 + 0xC), &D1);     // CMP.W	12(A0),D1
  DEF_ROMLOC(1954C) : if (CCR_GT) goto rom_19574; // BGT.B	$19574
  DEF_ROMLOC(1954E)
      : move_toreg_32(read_32(A0 + 0x3C), &A1);       // MOVEA.L	60(A0),A1
  DEF_ROMLOC(19552) : move_toreg_32(0x2, &D1);        // MOVEQ.L	$02,D1
  DEF_ROMLOC(19554) : btst_tomem_8(0x0, A0 + 0x22);   // BTST.B	#$00,34(A0)
  DEF_ROMLOC(1955A) : if (CCR_EQ) goto rom_1955E;     // BEQ.B	$1955E
  DEF_ROMLOC(1955C) : move_toreg_32(0x0, &D1);        // MOVEQ.L	$00,D1
  DEF_ROMLOC(1955E) : move_tomem_16(0xF0, A0 + 0x28); // MOVE.W	#$00F0,40(A0)
  DEF_ROMLOC(19564) : move_tomem_8(0xA, A0 + 0x1F);   // MOVE.B	#$0A,31(A0)
  DEF_ROMLOC(1956A)
      : move_tomem_8(read_8(A0 + 0x1F), A0 + 0x1E); // MOVE.B	31(A0),30(A0)
  rom_19752();
  return;                     // BRA.W	$19752
  DEF_ROMLOC(19574) : return; // RTS
}
ROMFUNC(rom_19576) {
  DEF_ROMLOC(19576)
      : move_toreg_32(read_32(A0 + 0x3C), &A1); // MOVEA.L	60(A0),A1
  DEF_ROMLOC(1957A) : move_toreg_32(0x0, &D0);  // MOVEQ.L	$00,D0
  DEF_ROMLOC(1957C)
      : move_toreg_8(read_8(A0 + 0x3A), &D0); // MOVE.B
                                              // 58(A0),D0
  DEF_ROMLOC(19580)
      : sub_toreg_8(read_8(A1 + 0x3A), &D0);          // SUB.B
                                                      // 58(A1),D0
  DEF_ROMLOC(19584) : if (CCR_EQ) goto rom_195DA;     // BEQ.B	$195DA
  DEF_ROMLOC(19586) : if (CCR_CC) goto rom_1958A;     // BCC.B	$1958A
  DEF_ROMLOC(19588) : neg_reg_8(&D0);                 // NEG.B	D0
  DEF_ROMLOC(1958A) : move_toreg_16(0xFFFFF7E8, &D1); // MOVE.W	#$F7E8,D1
  DEF_ROMLOC(1958E) : move_toreg_16(0xFFFFFEEC, &D2); // MOVE.W	#$FEEC,D2
  DEF_ROMLOC(19592) : cmp_toreg_8(0x1, &D0);          // CMPI.B	#$01,D0
  DEF_ROMLOC(19596) : if (CCR_EQ) goto rom_195B0;     // BEQ.B	$195B0
  DEF_ROMLOC(19598) : move_toreg_16(0xFFFFF6A0, &D1); // MOVE.W	#$F6A0,D1
  DEF_ROMLOC(1959C) : move_toreg_16(0xFFFFFF0C, &D2); // MOVE.W	#$FF0C,D2
  DEF_ROMLOC(195A0) : cmp_tomem_16(0x9C0, A1 + 0x38); // CMPI.W	#$09C0,56(A1)
  DEF_ROMLOC(195A6) : if (CCR_LT) goto rom_195B0;     // BLT.B	$195B0
  DEF_ROMLOC(195A8) : move_toreg_16(0xFFFFF5E0, &D1); // MOVE.W	#$F5E0,D1
  DEF_ROMLOC(195AC) : move_toreg_16(0xFFFFFF80, &D2); // MOVE.W	#$FF80,D2
  DEF_ROMLOC(195B0) : move_tomem_16(D1, A0 + 0x12);   // MOVE.W	D1,18(A0)
  DEF_ROMLOC(195B4) : move_tomem_16(D2, A0 + 0x10);   // MOVE.W	D2,16(A0)
  DEF_ROMLOC(195B8) : move_toreg_16(read_16(A0 + 0x8), &D0); // MOVE.W	8(A0),D0
  DEF_ROMLOC(195BC)
      : sub_toreg_16(read_16(A0 + 0x30), &D0);        // SUB.W
                                                      // 48(A0),D0
  DEF_ROMLOC(195C0) : if (CCR_CC) goto rom_195C6;     // BCC.B	$195C6
  DEF_ROMLOC(195C2) : neg_mem_16(A0 + 0x10);          // NEG.W	16(A0)
  DEF_ROMLOC(195C6) : move_tomem_8(0x1, A0 + 0x1A);   // MOVE.B	#$01,26(A0)
  DEF_ROMLOC(195CC) : move_tomem_16(0x20, A0 + 0x28); // MOVE.W	#$0020,40(A0)
  DEF_ROMLOC(195D2) : add_tomem_8(0x2, A0 + 0x24);    // ADDQ.B	#$02,36(A0)
  rom_1965A();
  return;                                          // BRA.W	$1965A
  DEF_ROMLOC(195DA) : move_toreg_32(0x197C8, &A2); // LEA.L	$000197C8,A2
  DEF_ROMLOC(195E0) : move_toreg_32(0x0, &D0);     // MOVEQ.L	$00,D0
  DEF_ROMLOC(195E2)
      : move_toreg_8(read_8(A1 + 0x1A), &D0);   // MOVE.B	26(A1),D0
  DEF_ROMLOC(195E6) : move_toreg_16(0x28, &D2); // MOVE.W	#$0028,D2
  DEF_ROMLOC(195EA)
      : move_toreg_16(read_16(A0 + 0x8), &D1); // MOVE.W	8(A0),D1
  DEF_ROMLOC(195EE)
      : sub_toreg_16(read_16(A0 + 0x30), &D1);    // SUB.W	48(A0),D1
  DEF_ROMLOC(195F2) : if (CCR_CC) goto rom_195F8; // BCC.B	$195F8
  DEF_ROMLOC(195F4) : neg_reg_16(&D2);            // NEG.W	D2
  DEF_ROMLOC(195F6) : add_toreg_16(0x2, &D0);     // ADDQ.W	#$02,D0
  DEF_ROMLOC(195F8) : add_toreg_16(D0, &D0);      // ADD.W	D0,D0
  DEF_ROMLOC(195FA)
      : move_toreg_16(read_16(A0 + 0x34), &D1); // MOVE.W	52(A0),D1
  DEF_ROMLOC(195FE)
      : add_toreg_16(read_16((s32)A2 + (s8)0x0 + (s16)D0),
                     &D1);                         // ADD.W	0(A2,D0),D1
  DEF_ROMLOC(19602) : move_tomem_16(D1, A0 + 0xC); // MOVE.W	D1,12(A0)
  DEF_ROMLOC(19606)
      : add_toreg_16(read_16(A0 + 0x30), &D2);      // ADD.W	48(A0),D2
  DEF_ROMLOC(1960A) : move_tomem_16(D2, A0 + 0x8);  // MOVE.W	D2,8(A0)
  DEF_ROMLOC(1960E) : clr_mem_16(A0 + 0xE);         // CLR.W	14(A0)
  DEF_ROMLOC(19612) : clr_mem_16(A0 + 0xA);         // CLR.W	10(A0)
  DEF_ROMLOC(19616) : sub_tomem_16(0x1, A0 + 0x28); // SUBQ.W	#$01,40(A0)
  DEF_ROMLOC(1961A) : if (!CCR_EQ) {
    rom_1962A();
    return;
  } // BNE.B	$1962A
  DEF_ROMLOC(1961C) : move_tomem_16(0x20, A0 + 0x28); // MOVE.W	#$0020,40(A0)
  DEF_ROMLOC(19622) : move_tomem_8(0x8, A0 + 0x24);   // MOVE.B	#$08,36(A0)
  DEF_ROMLOC(19628) : return;                         // RTS
}
ROMFUNC(rom_1962A) {
  DEF_ROMLOC(1962A) : cmp_tomem_16(0x78, A0 + 0x28); // CMPI.W	#$0078,40(A0)
  DEF_ROMLOC(19630) : if (!CCR_EQ) goto rom_19638;   // BNE.B	$19638
  DEF_ROMLOC(19632) : move_tomem_8(0x5, A0 + 0x1F);  // MOVE.B	#$05,31(A0)
  DEF_ROMLOC(19638) : cmp_tomem_16(0x3C, A0 + 0x28); // CMPI.W	#$003C,40(A0)
  DEF_ROMLOC(1963E) : if (!CCR_EQ) goto rom_19646;   // BNE.B	$19646
  DEF_ROMLOC(19640) : move_tomem_8(0x2, A0 + 0x1F);  // MOVE.B	#$02,31(A0)
  DEF_ROMLOC(19646) : sub_tomem_8(0x1, A0 + 0x1E);   // SUBQ.B	#$01,30(A0)
  DEF_ROMLOC(1964A) : if (CCR_GT) goto rom_19658;    // BGT.B	$19658
  DEF_ROMLOC(1964C) : bchg_tomem_8(0x0, A0 + 0x1A);  // BCHG.B	#$00,26(A0)
  DEF_ROMLOC(19652)
      : move_tomem_8(read_8(A0 + 0x1F), A0 + 0x1E); // MOVE.B	31(A0),30(A0)
  DEF_ROMLOC(19658) : return;                       // RTS
}
ROMFUNC(rom_1965A) {
  DEF_ROMLOC(1965A) : move_toreg_32(0xFFFFD040, &A1); // LEA.L	$D040,A1
  DEF_ROMLOC(1965E) : move_toreg_32(0x7A, &D0);       // MOVEQ.L	$7A,D0
  DEF_ROMLOC(19660) : move_toreg_32(0x40, &D1);       // MOVEQ.L	$40,D1
  DEF_ROMLOC(19662) : move_toreg_32(0x3E, &D2);       // MOVEQ.L	$3E,D2
  DEF_ROMLOC(19664) : cmp_toreg_8(read_8(A1), &D0);   // CMP.B	(A1),D0
  DEF_ROMLOC(19666) : if (CCR_EQ) goto rom_19670;     // BEQ.B	$19670
  DEF_ROMLOC(19668) : add_toreg_16(D1, &A1);          // ADDA.W	D1,A1
  DEF_ROMLOC(1966A) : dec_reg_16(&D2);
  if ((D2 & 0xffff) != 0xffff)
    goto rom_19664; // DBF.W	D2,$19664
  goto rom_196E8;   // BRA.B	$196E8
  DEF_ROMLOC(19670)
      : move_toreg_16(read_16(A1 + 0x8), &D0); // MOVE.W	8(A1),D0
  DEF_ROMLOC(19674)
      : move_toreg_16(read_16(A1 + 0xC), &D1); // MOVE.W	12(A1),D1
  DEF_ROMLOC(19678)
      : move_toreg_16(read_16(A0 + 0x8), &D2); // MOVE.W	8(A0),D2
  DEF_ROMLOC(1967C)
      : move_toreg_16(read_16(A0 + 0xC), &D3);         // MOVE.W	12(A0),D3
  DEF_ROMLOC(19680) : move_toreg_32(0x197D2, &A2);     // LEA.L	336(PC),A2
  DEF_ROMLOC(19684) : move_toreg_32(0x197D6, &A3);     // LEA.L	336(PC),A3
  DEF_ROMLOC(19688) : move_toreg_8(read_8(A2++), &D4); // MOVE.B	(A2)+,D4
  DEF_ROMLOC(1968A) : ext_reg_16(&D4);                 // EXT.W	D4
  DEF_ROMLOC(1968C) : add_toreg_16(D4, &D0);           // ADD.W	D4,D0
  DEF_ROMLOC(1968E) : move_toreg_8(read_8(A3++), &D4); // MOVE.B	(A3)+,D4
  DEF_ROMLOC(19690) : ext_reg_16(&D4);                 // EXT.W	D4
  DEF_ROMLOC(19692) : add_toreg_16(D4, &D2);           // ADD.W	D4,D2
  DEF_ROMLOC(19694) : cmp_toreg_16(D0, &D2);           // CMP.W	D0,D2
  DEF_ROMLOC(19696) : if (CCR_CS) goto rom_196E8;      // BCS.B	$196E8
  DEF_ROMLOC(19698) : move_toreg_8(read_8(A2++), &D4); // MOVE.B	(A2)+,D4
  DEF_ROMLOC(1969A) : ext_reg_16(&D4);                 // EXT.W	D4
  DEF_ROMLOC(1969C) : add_toreg_16(D4, &D0);           // ADD.W	D4,D0
  DEF_ROMLOC(1969E) : move_toreg_8(read_8(A3++), &D4); // MOVE.B	(A3)+,D4
  DEF_ROMLOC(196A0) : ext_reg_16(&D4);                 // EXT.W	D4
  DEF_ROMLOC(196A2) : add_toreg_16(D4, &D2);           // ADD.W	D4,D2
  DEF_ROMLOC(196A4) : cmp_toreg_16(D2, &D0);           // CMP.W	D2,D0
  DEF_ROMLOC(196A6) : if (CCR_CS) goto rom_196E8;      // BCS.B	$196E8
  DEF_ROMLOC(196A8) : move_toreg_8(read_8(A2++), &D4); // MOVE.B	(A2)+,D4
  DEF_ROMLOC(196AA) : ext_reg_16(&D4);                 // EXT.W	D4
  DEF_ROMLOC(196AC) : add_toreg_16(D4, &D1);           // ADD.W	D4,D1
  DEF_ROMLOC(196AE) : move_toreg_8(read_8(A3++), &D4); // MOVE.B	(A3)+,D4
  DEF_ROMLOC(196B0) : ext_reg_16(&D4);                 // EXT.W	D4
  DEF_ROMLOC(196B2) : add_toreg_16(D4, &D3);           // ADD.W	D4,D3
  DEF_ROMLOC(196B4) : cmp_toreg_16(D1, &D3);           // CMP.W	D1,D3
  DEF_ROMLOC(196B6) : if (CCR_CS) goto rom_196E8;      // BCS.B	$196E8
  DEF_ROMLOC(196B8) : move_toreg_8(read_8(A2++), &D4); // MOVE.B	(A2)+,D4
  DEF_ROMLOC(196BA) : ext_reg_16(&D4);                 // EXT.W	D4
  DEF_ROMLOC(196BC) : add_toreg_16(D4, &D1);           // ADD.W	D4,D1
  DEF_ROMLOC(196BE) : move_toreg_8(read_8(A3++), &D4); // MOVE.B	(A3)+,D4
  DEF_ROMLOC(196C0) : ext_reg_16(&D4);                 // EXT.W	D4
  DEF_ROMLOC(196C2) : add_toreg_16(D4, &D3);           // ADD.W	D4,D3
  DEF_ROMLOC(196C4) : cmp_toreg_16(D3, &D1);           // CMP.W	D3,D1
  DEF_ROMLOC(196C6) : if (CCR_CS) goto rom_196E8;      // BCS.B	$196E8
  DEF_ROMLOC(196C8) : add_tomem_8(0x2, A0 + 0x24);     // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(196CC) : clr_mem_16(A0 + 0x28);           // CLR.W	40(A0)
  DEF_ROMLOC(196D0) : clr_mem_8(A1 + 0x20);            // CLR.B	32(A1)
  DEF_ROMLOC(196D4) : sub_tomem_8(0x1, A1 + 0x21);     // SUBQ.B	#$01,33(A1)
  DEF_ROMLOC(196D8) : if (!CCR_EQ) goto rom_196E8;     // BNE.B	$196E8
  DEF_ROMLOC(196DA) : bset_tomem_8(0x7, A1 + 0x22);    // BSET.B	#$07,34(A1)
  DEF_ROMLOC(196E0) : clr_mem_16(A0 + 0x10);           // CLR.W	16(A0)
  DEF_ROMLOC(196E4) : clr_mem_16(A0 + 0x12);           // CLR.W	18(A0)
  DEF_ROMLOC(196E8) : tst_mem_16(A0 + 0x12);           // TST.W	18(A0)
  DEF_ROMLOC(196EC) : if (CCR_PL) goto rom_1970C;      // BPL.B	$1970C
  DEF_ROMLOC(196EE) : rom_DC40();                      // JSR	$0000DC40
  DEF_ROMLOC(196F4)
      : move_toreg_16(read_16(A0 + 0x34), &D0); // MOVE.W	52(A0),D0
  DEF_ROMLOC(196F8) : sub_toreg_16(0x2F, &D0);  // SUBI.W	#$002F,D0
  DEF_ROMLOC(196FC)
      : cmp_toreg_16(read_16(A0 + 0xC), &D0);     // CMP.W	12(A0),D0
  DEF_ROMLOC(19700) : if (CCR_GT) goto rom_19708; // BGT.B	$19708
  DEF_ROMLOC(19702) : rom_DC40();                 // JSR	$0000DC40
  DEF_ROMLOC(19708) : rom_1962A();
  return;                         // BRA.W	$1962A
  DEF_ROMLOC(1970C) : rom_DC40(); // JSR	$0000DC40
  DEF_ROMLOC(19712)
      : move_toreg_32(read_32(A0 + 0x3C), &A1);    // MOVEA.L	60(A0),A1
  DEF_ROMLOC(19716) : move_toreg_32(0x197C8, &A2); // LEA.L	$000197C8,A2
  DEF_ROMLOC(1971C) : move_toreg_32(0x0, &D0);     // MOVEQ.L	$00,D0
  DEF_ROMLOC(1971E)
      : move_toreg_8(read_8(A1 + 0x1A), &D0); // MOVE.B
                                              // 26(A1),D0
  DEF_ROMLOC(19722)
      : move_toreg_16(read_16(A0 + 0x8), &D1); // MOVE.W	8(A0),D1
  DEF_ROMLOC(19726)
      : sub_toreg_16(read_16(A0 + 0x30), &D1);    // SUB.W	48(A0),D1
  DEF_ROMLOC(1972A) : if (CCR_CC) goto rom_1972E; // BCC.B	$1972E
  DEF_ROMLOC(1972C) : add_toreg_16(0x2, &D0);     // ADDQ.W	#$02,D0
  DEF_ROMLOC(1972E) : add_toreg_16(D0, &D0);      // ADD.W	D0,D0
  DEF_ROMLOC(19730)
      : move_toreg_16(read_16(A0 + 0x34), &D1); // MOVE.W	52(A0),D1
  DEF_ROMLOC(19734)
      : add_toreg_16(read_16((s32)A2 + (s8)0x0 + (s16)D0),
                     &D1); // ADD.W	0(A2,D0),D1
  DEF_ROMLOC(19738)
      : cmp_toreg_16(read_16(A0 + 0xC), &D1);     // CMP.W	12(A0),D1
  DEF_ROMLOC(1973C) : if (CCR_GT) goto rom_19708; // BGT.B	$19708
  DEF_ROMLOC(1973E)
      : move_toreg_32(read_32(A0 + 0x3C), &A1);      // MOVEA.L	60(A0),A1
  DEF_ROMLOC(19742) : move_toreg_32(0x2, &D1);       // MOVEQ.L	$02,D1
  DEF_ROMLOC(19744) : tst_mem_16(A0 + 0x10);         // TST.W	16(A0)
  DEF_ROMLOC(19748) : if (CCR_MI) goto rom_1974C;    // BMI.B	$1974C
  DEF_ROMLOC(1974A) : move_toreg_32(0x0, &D1);       // MOVEQ.L	$00,D1
  DEF_ROMLOC(1974C) : move_tomem_16(0x0, A0 + 0x28); // MOVE.W	#$0000,40(A0)
  rom_19752(); // Detected flow into next function
}
ROMFUNC(rom_19752) {
  DEF_ROMLOC(19752) : move_tomem_8(D1, A1 + 0x3A); // MOVE.B	D1,58(A1)
  DEF_ROMLOC(19756) : move_tomem_8(D1, A0 + 0x3A); // MOVE.B	D1,58(A0)
  DEF_ROMLOC(1975A)
      : cmp_toreg_8(read_8(A1 + 0x1A), &D1);          // CMP.B
                                                      // 26(A1),D1
  DEF_ROMLOC(1975E) : if (CCR_EQ) goto rom_197B8;     // BEQ.B	$197B8
  DEF_ROMLOC(19760) : bclr_tomem_8(0x3, A1 + 0x22);   // BCLR.B	#$03,34(A1)
  DEF_ROMLOC(19766) : if (CCR_EQ) goto rom_197B8;     // BEQ.B	$197B8
  DEF_ROMLOC(19768) : clr_mem_8(A1 + 0x25);           // CLR.B	37(A1)
  DEF_ROMLOC(1976C) : move_tomem_8(0x2, A1 + 0x24);   // MOVE.B	#$02,36(A1)
  DEF_ROMLOC(19772) : move_toreg_32(0xFFFFD000, &A2); // LEA.L	$D000,A2
  DEF_ROMLOC(19776)
      : move_tomem_16(read_16(A0 + 0x12), A2 + 0x12); // MOVE.W	18(A0),18(A2)
  DEF_ROMLOC(1977C) : neg_mem_16(A2 + 0x12);          // NEG.W	18(A2)
  DEF_ROMLOC(19780) : cmp_tomem_8(0x1, A1 + 0x1A);    // CMPI.B	#$01,26(A1)
  DEF_ROMLOC(19786) : if (!CCR_EQ) goto rom_1978C;    // BNE.B	$1978C
  DEF_ROMLOC(19788) : asr_mem_16(A2 + 0x12);          // ASR.W	18(A2)
  DEF_ROMLOC(1978C) : bset_tomem_8(0x1, A2 + 0x22);   // BSET.B	#$01,34(A2)
  DEF_ROMLOC(19792) : bclr_tomem_8(0x3, A2 + 0x22);   // BCLR.B	#$03,34(A2)
  DEF_ROMLOC(19798) : clr_mem_8(A2 + 0x3C);           // CLR.B	60(A2)
  DEF_ROMLOC(1979C) : move_tomem_32(A0, A7 -= 4);     // MOVE.L	A0,-(A7)
  DEF_ROMLOC(1979E) : move_toreg_32(A2, &A0);         // LEA.L	(A2),A0
  DEF_ROMLOC(197A0) : rom_13A80();                    // JSR	$00013A80
  DEF_ROMLOC(197A6)
      : move_toreg_32(read_32((A7 += 4, A7 - 4)), &A0); // MOVEA.L	(A7)+,A0
  DEF_ROMLOC(197A8) : move_tomem_8(0x2, A2 + 0x24);     // MOVE.B	#$02,36(A2)
  DEF_ROMLOC(197AE) : move_toreg_16(SFX_SPRING, &D0);   // MOVE.W	#$00CC,D0
  DEF_ROMLOC(197B2) : play_sound_special();             // JSR	$00001394
  DEF_ROMLOC(197B8) : clr_mem_16(A0 + 0x10);            // CLR.W	16(A0)
  DEF_ROMLOC(197BC) : clr_mem_16(A0 + 0x12);            // CLR.W	18(A0)
  DEF_ROMLOC(197C0) : add_tomem_8(0x2, A0 + 0x24);      // ADDQ.B	#$02,36(A0)
  rom_1962A();                                          // BRA.W	$1962A
}
ROMFUNC(rom_197DA) {
  DEF_ROMLOC(197DA)
      : move_tomem_8(OBJ_EXPLOSIONBOMB,
                     A0 + offsetof(object, id));     // MOVE.B	#$3F,(A0)
  DEF_ROMLOC(197DE) : clr_mem_8(A0 + 0x24);          // CLR.B	36(A0)
  DEF_ROMLOC(197E2) : cmp_tomem_16(0x20, A0 + 0x28); // CMPI.W	#$0020,40(A0)
  DEF_ROMLOC(197E8) : if (CCR_EQ) goto rom_197EC;    // BEQ.B	$197EC
  DEF_ROMLOC(197EA) : return;                        // RTS
  DEF_ROMLOC(197EC)
      : move_tomem_16(read_16(A0 + 0x34), A0 + 0xC); // MOVE.W	52(A0),12(A0)
  DEF_ROMLOC(197F2) : move_toreg_32(0x3, &D1);       // MOVEQ.L	$03,D1
  DEF_ROMLOC(197F4) : move_toreg_32(0x19850, &A2);   // LEA.L	90(PC),A2
  rom_197F8(); // Detected flow into next function
}
ROMFUNC(rom_197F8) {
  DEF_ROMLOC(197F8) : rom_E11A();                  // JSR	$0000E11A
  DEF_ROMLOC(197FE) : if (!CCR_EQ) goto rom_1984A; // BNE.B	$1984A
  DEF_ROMLOC(19800)
      : move_tomem_8(OBJ_BOSSSPIKEBALL,
                     A1 + offsetof(object, id));    // MOVE.B	#$7B,(A1)
  DEF_ROMLOC(19804) : move_tomem_8(0xA, A1 + 0x24); // MOVE.B	#$0A,36(A1)
  DEF_ROMLOC(1980A)
      : move_tomem_32(0x1988E, A1 + 0x4);             // MOVE.L	#$0001988E,4(A1)
  DEF_ROMLOC(19812) : move_tomem_8(0x3, A1 + 0x18);   // MOVE.B	#$03,24(A1)
  DEF_ROMLOC(19818) : move_tomem_16(0x518, A1 + 0x2); // MOVE.W	#$0518,2(A1)
  DEF_ROMLOC(1981E)
      : move_tomem_16(read_16(A0 + 0x8), A1 + 0x8); // MOVE.W	8(A0),8(A1)
  DEF_ROMLOC(19824)
      : move_tomem_16(read_16(A0 + 0xC), A1 + 0xC); // MOVE.W	12(A0),12(A1)
  DEF_ROMLOC(1982A)
      : move_tomem_16(read_16((A2 += 2, A2 - 2)),
                      A1 + 0x10); // MOVE.W	(A2)+,16(A1)
  DEF_ROMLOC(1982E)
      : move_tomem_16(read_16((A2 += 2, A2 - 2)),
                      A1 + 0x12); // MOVE.W	(A2)+,18(A1)
  DEF_ROMLOC(19832)
      : move_tomem_8(0xFFFFFF98, A1 + 0x20);        // MOVE.B	#$98,32(A1)
  DEF_ROMLOC(19838) : or_tomem_8(0x4, A1 + 0x1);    // ORI.B	#$04,1(A1)
  DEF_ROMLOC(1983E) : bset_tomem_8(0x7, A1 + 0x1);  // BSET.B	#$07,1(A1)
  DEF_ROMLOC(19844) : move_tomem_8(0xC, A1 + 0x19); // MOVE.B	#$0C,25(A1)
  DEF_ROMLOC(1984A) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_197F8;           // DBF.W	D1,$197F8
  DEF_ROMLOC(1984E) : return; // RTS
}
ROMFUNC(rom_19860) {
  DEF_ROMLOC(19860) : rom_DC6C(); // JSR	$0000DC6C
  DEF_ROMLOC(19866)
      : move_tomem_16(read_16(A0 + 0x8), A0 + 0x30); // MOVE.W	8(A0),48(A0)
  DEF_ROMLOC(1986C)
      : move_tomem_16(read_16(A0 + 0xC), A0 + 0x34); // MOVE.W	12(A0),52(A0)
  DEF_ROMLOC(19872) : add_tomem_16(0x18, A0 + 0x12); // ADDI.W	#$0018,18(A0)
  DEF_ROMLOC(19878) : move_toreg_32(0x4, &D0);       // MOVEQ.L	$04,D0
  DEF_ROMLOC(1987A)
      : and_toreg_16(read_16(0xFFFFFE0E), &D0);    // AND.W	$FE0E,D0
  DEF_ROMLOC(1987E) : lsr_toreg_16(0x2, &D0);      // LSR.W	#$02,D0
  DEF_ROMLOC(19880) : move_tomem_8(D0, A0 + 0x1A); // MOVE.B	D0,26(A0)
  DEF_ROMLOC(19884) : tst_mem_8(A0 + 0x1);         // TST.B	1(A0)
  DEF_ROMLOC(19888) : if (CCR_PL) {
    rom_19062();
    return;
  } // BPL.W	$19062
  DEF_ROMLOC(1988C) : return; // RTS
}