// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

static bool exit_early = false;

ROMFUNC(rom_E688) {
  u8 switchindex = 0;
  exit_early = false;
  DEF_ROMLOC(E688) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(E68A) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(E68E)
      : move_toreg_16(read_16(0xE696 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(E692): goto rom_E696 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(E692) : switch (switchindex) {
  case 0:
    rom_E69A();
    break;
  case 1:
    rom_E6E2();
    break;
  }
}
ROMFUNC(rom_E69A) {
  DEF_ROMLOC(E69A) : move_tomem_8(0xE, A0 + 0x16);  // MOVE.B	#$0E,22(A0)
  DEF_ROMLOC(E6A0) : move_tomem_8(0x8, A0 + 0x17);  // MOVE.B	#$08,23(A0)
  DEF_ROMLOC(E6A6) : rom_DC40();                    // BSR.W	$DC40
  DEF_ROMLOC(E6AA) : rom_15580();                   // BSR.W	$15580
  DEF_ROMLOC(E6AE) : tst_reg_16(&D1);               // TST.W	D1
  DEF_ROMLOC(E6B0) : if (CCR_PL) goto rom_E6E0;     // BPL.B	$E6E0
  DEF_ROMLOC(E6B2) : add_tomem_16(D1, A0 + 0xC);    // ADD.W	D1,12(A0)
  DEF_ROMLOC(E6B6) : move_tomem_16(0x0, A0 + 0x12); // MOVE.W	#$0000,18(A0)
  DEF_ROMLOC(E6BC) : add_tomem_8(0x2, A0 + 0x24);   // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(E6C0)
      : move_tomem_32(0xE830, A0 + 0x4);             // MOVE.L	#$0000E830,4(A0)
  DEF_ROMLOC(E6C8) : move_tomem_16(0x4B8, A0 + 0x2); // MOVE.W	#$04B8,2(A0)
  DEF_ROMLOC(E6CE) : move_tomem_8(0x4, A0 + 0x1);    // MOVE.B	#$04,1(A0)
  DEF_ROMLOC(E6D4) : move_tomem_8(0x4, A0 + 0x18);   // MOVE.B	#$04,24(A0)
  DEF_ROMLOC(E6DA) : move_tomem_8(0x10, A0 + 0x19);  // MOVE.B	#$10,25(A0)
  DEF_ROMLOC(E6E0) : return;                         // RTS
}
ROMFUNC(rom_E6E2) {
  u8 switchindex = 0;
  DEF_ROMLOC(E6E2) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(E6E4) : move_toreg_8(read_8(A0 + 0x25), &D0);
  switchindex = D0 / 2; // MOVE.B	37(A0),D0
  DEF_ROMLOC(E6E8)
      : move_toreg_16(read_16(0xE732 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	72(PC,D0),D1
  // DEF_ROMLOC(E6EC): rom_E732 + (s16)(D1 & 0xffff)(); // JSR	68(PC,D1)
  DEF_ROMLOC(E6EC) : switch (switchindex) {
  case 0:
    rom_E73A();
    break;
  case 1:
    rom_E764();
    break;
  case 2:
    rom_E78C();
    break;
  case 3:
    rom_E7BE();
    break;
  }
  if (exit_early)
    return;
  DEF_ROMLOC(E6F0) : move_toreg_32(0xE818, &A1); // LEA.L	$0000E818,A1
  DEF_ROMLOC(E6F6) : animate_sprite();           // BSR.W	$ADA2
  DEF_ROMLOC(E6FA) : move_toreg_16(read_16(A0 + 0x8), &D0); // MOVE.W	8(A0),D0
  DEF_ROMLOC(E6FE) : and_toreg_16(0xFFFFFF80, &D0);         // ANDI.W	#$FF80,D0
  DEF_ROMLOC(E702)
      : move_toreg_16(read_16(v_screenposx), &D1);  // MOVE.W	$F700,D1
  DEF_ROMLOC(E706) : sub_toreg_16(0x80, &D1);       // SUBI.W	#$0080,D1
  DEF_ROMLOC(E70A) : and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
  DEF_ROMLOC(E70E) : sub_toreg_16(D1, &D0);         // SUB.W	D1,D0
  DEF_ROMLOC(E710) : cmp_toreg_16(0x280, &D0);      // CMPI.W	#$0280,D0
  DEF_ROMLOC(E714) : if (CCR_GT) goto rom_E71C;     // BGT.W	$E71C
  rom_DC92();
  return;                                            // BRA.W	$DC92
  DEF_ROMLOC(E71C) : move_toreg_32(0xFFFFFC00, &A2); // LEA.L	$FC00,A2
  DEF_ROMLOC(E720) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(E722)
      : move_toreg_8(read_8(A0 + 0x23), &D0);   // MOVE.B	35(A0),D0
  DEF_ROMLOC(E726) : if (CCR_EQ) goto rom_E72E; // BEQ.B	$E72E
  DEF_ROMLOC(E728)
      : bclr_tomem_8(0x7,
                     (s32)A2 + (s8)0x2 + (s16)D0); // BCLR.B	#$07,2(A2,D0)
  DEF_ROMLOC(E72E) : rom_DCCE();                   // BRA.W	$DCCE
}
ROMFUNC(rom_E73A) {
  DEF_ROMLOC(E73A)
      : move_toreg_16(read_16(0xFFFFD008), &D0);           // MOVE.W	$D008,D0
  DEF_ROMLOC(E73E) : sub_toreg_16(0x100, &D0);             // SUBI.W	#$0100,D0
  DEF_ROMLOC(E742) : if (CCR_CS) goto rom_E760;            // BCS.B	$E760
  DEF_ROMLOC(E744) : sub_toreg_16(read_16(A0 + 0x8), &D0); // SUB.W	8(A0),D0
  DEF_ROMLOC(E748) : if (CCR_CS) goto rom_E760;            // BCS.B	$E760
  DEF_ROMLOC(E74A) : add_tomem_8(0x4, A0 + 0x25);          // ADDQ.B	#$04,37(A0)
  DEF_ROMLOC(E74E) : move_tomem_8(0x2, A0 + 0x1C);         // MOVE.B	#$02,28(A0)
  DEF_ROMLOC(E754) : move_tomem_16(0x700, A0 + 0x10); // MOVE.W	#$0700,16(A0)
  DEF_ROMLOC(E75A) : move_tomem_8(0xFFFFFF8E, A0 + 0x20); // MOVE.B
                                                          // #$8E,32(A0)
  DEF_ROMLOC(E760) : exit_early = true; // TODO; // ADDQ.L	#$04,A7
  DEF_ROMLOC(E762) : return;            // RTS
}
ROMFUNC(rom_E764) {
  DEF_ROMLOC(E764) : cmp_tomem_8(0x2, A0 + 0x1C);     // CMPI.B	#$02,28(A0)
  DEF_ROMLOC(E76A) : if (CCR_EQ) goto rom_E786;       // BEQ.B	$E786
  DEF_ROMLOC(E76C) : sub_tomem_16(0x1, A0 + 0x30);    // SUBQ.W	#$01,48(A0)
  DEF_ROMLOC(E770) : if (CCR_PL) goto rom_E784;       // BPL.B	$E784
  DEF_ROMLOC(E772) : move_tomem_8(0x1, A0 + 0x1C);    // MOVE.B	#$01,28(A0)
  DEF_ROMLOC(E778) : move_tomem_16(0x700, A0 + 0x10); // MOVE.W	#$0700,16(A0)
  DEF_ROMLOC(E77E)
      : move_tomem_8(0xFFFFFF8E, A0 + 0x20);      // MOVE.B	#$8E,32(A0)
  DEF_ROMLOC(E784) : return;                      // RTS
  DEF_ROMLOC(E786) : add_tomem_8(0x2, A0 + 0x25); // ADDQ.B	#$02,37(A0)
  DEF_ROMLOC(E78A) : return;                      // RTS
}
ROMFUNC(rom_E78C) {
  DEF_ROMLOC(E78C) : rom_E7E0();                    // BSR.W	$E7E0
  DEF_ROMLOC(E790) : rom_DC6C();                    // BSR.W	$DC6C
  DEF_ROMLOC(E794) : rom_15580();                   // BSR.W	$15580
  DEF_ROMLOC(E798) : cmp_toreg_16(0xFFFFFFF8, &D1); // CMPI.W	#$FFF8,D1
  DEF_ROMLOC(E79C) : if (CCR_LT) goto rom_E7AA;     // BLT.B	$E7AA
  DEF_ROMLOC(E79E) : cmp_toreg_16(0xC, &D1);        // CMPI.W	#$000C,D1
  DEF_ROMLOC(E7A2) : if (CCR_GE) goto rom_E7AA;     // BGE.B	$E7AA
  DEF_ROMLOC(E7A4) : add_tomem_16(D1, A0 + 0xC);    // ADD.W	D1,12(A0)
  DEF_ROMLOC(E7A8) : return;                        // RTS
  DEF_ROMLOC(E7AA) : add_tomem_8(0x2, A0 + 0x25);   // ADDQ.B	#$02,37(A0)
  DEF_ROMLOC(E7AE) : bset_tomem_8(0x0, A0 + 0x32);  // BSET.B	#$00,50(A0)
  DEF_ROMLOC(E7B4) : if (CCR_EQ) goto rom_E7BC;     // BEQ.B	$E7BC
  DEF_ROMLOC(E7B6)
      : move_tomem_16(0xFFFFFA00, A0 + 0x12); // MOVE.W	#$FA00,18(A0)
  DEF_ROMLOC(E7BC) : return;                  // RTS
}
ROMFUNC(rom_E7BE) {
  DEF_ROMLOC(E7BE) : rom_DC40();                    // BSR.W	$DC40
  DEF_ROMLOC(E7C2) : tst_mem_16(A0 + 0x12);         // TST.W	18(A0)
  DEF_ROMLOC(E7C6) : if (CCR_MI) goto rom_E7DE;     // BMI.B	$E7DE
  DEF_ROMLOC(E7C8) : rom_15580();                   // BSR.W	$15580
  DEF_ROMLOC(E7CC) : tst_reg_16(&D1);               // TST.W	D1
  DEF_ROMLOC(E7CE) : if (CCR_PL) goto rom_E7DE;     // BPL.B	$E7DE
  DEF_ROMLOC(E7D0) : add_tomem_16(D1, A0 + 0xC);    // ADD.W	D1,12(A0)
  DEF_ROMLOC(E7D4) : sub_tomem_8(0x2, A0 + 0x25);   // SUBQ.B	#$02,37(A0)
  DEF_ROMLOC(E7D8) : move_tomem_16(0x0, A0 + 0x12); // MOVE.W	#$0000,18(A0)
  DEF_ROMLOC(E7DE) : return;                        // RTS
}
ROMFUNC(rom_E7E0) {
  DEF_ROMLOC(E7E0) : tst_mem_8(A0 + 0x32);      // TST.B	50(A0)
  DEF_ROMLOC(E7E4) : if (CCR_MI) goto rom_E816; // BMI.B	$E816
  DEF_ROMLOC(E7E6)
      : move_toreg_16(read_16(0xFFFFD008), &D0);           // MOVE.W	$D008,D0
  DEF_ROMLOC(E7EA) : sub_toreg_16(0x30, &D0);              // SUBI.W	#$0030,D0
  DEF_ROMLOC(E7EE) : sub_toreg_16(read_16(A0 + 0x8), &D0); // SUB.W	8(A0),D0
  DEF_ROMLOC(E7F2) : if (CCR_CC) goto rom_E816;            // BCC.B	$E816
  DEF_ROMLOC(E7F4) : move_tomem_8(0x0, A0 + 0x1C);         // MOVE.B	#$00,28(A0)
  DEF_ROMLOC(E7FA) : move_tomem_8(0xE, A0 + 0x20);         // MOVE.B	#$0E,32(A0)
  DEF_ROMLOC(E800) : clr_mem_16(A0 + 0x10);                // CLR.W	16(A0)
  DEF_ROMLOC(E804) : move_tomem_16(0x78, A0 + 0x30); // MOVE.W	#$0078,48(A0)
  DEF_ROMLOC(E80A) : move_tomem_8(0x2, A0 + 0x25);   // MOVE.B	#$02,37(A0)
  DEF_ROMLOC(E810) : bset_tomem_8(0x7, A0 + 0x32);   // BSET.B	#$07,50(A0)
  DEF_ROMLOC(E816) : return;                         // RTS
}