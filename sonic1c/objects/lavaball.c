// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_E992) {
  u8 switchindex = 0;
  DEF_ROMLOC(E992) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(E994) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(E998)
      : move_toreg_16(read_16(0xE9A4 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	10(PC,D0),D1
  // DEF_ROMLOC(E99C): rom_E9A4 + (s16)(D1 & 0xffff)(); // JSR	6(PC,D1)
  DEF_ROMLOC(E99C) : switch (switchindex) {
  case 0:
    rom_E9BC();
    break;
  case 1:
    rom_EA48();
    break;
  case 2:
    rom_EB4E();
    break;
  }
  DEF_ROMLOC(E9A0) : rom_DC92(); // BRA.W	$DC92
}
ROMFUNC(rom_E9BC) {
  DEF_ROMLOC(E9BC) : add_tomem_8(0x2, A0 + 0x24);  // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(E9C0) : move_tomem_8(0x8, A0 + 0x16); // MOVE.B	#$08,22(A0)
  DEF_ROMLOC(E9C6) : move_tomem_8(0x8, A0 + 0x17); // MOVE.B	#$08,23(A0)
  DEF_ROMLOC(E9CC)
      : move_tomem_32(0xB9F8, A0 + 0x4);             // MOVE.L	#$0000B9F8,4(A0)
  DEF_ROMLOC(E9D4) : move_tomem_16(0x345, A0 + 0x2); // MOVE.W	#$0345,2(A0)
  DEF_ROMLOC(E9DA) : cmp_tomem_8(0x3, 0xFFFFFE10);   // CMPI.B	#$03,$FE10
  DEF_ROMLOC(E9E0) : if (!CCR_EQ) goto rom_E9E8;     // BNE.B	$E9E8
  DEF_ROMLOC(E9E2) : move_tomem_16(0x480, A0 + 0x2); // MOVE.W	#$0480,2(A0)
  DEF_ROMLOC(E9E8) : move_tomem_8(0x4, A0 + 0x1);    // MOVE.B	#$04,1(A0)
  DEF_ROMLOC(E9EE) : move_tomem_8(0x3, A0 + 0x18);   // MOVE.B	#$03,24(A0)
  DEF_ROMLOC(E9F4)
      : move_tomem_8(0xFFFFFF8B, A0 + 0x20); // MOVE.B	#$8B,32(A0)
  DEF_ROMLOC(E9FA)
      : move_tomem_16(read_16(A0 + 0xC), A0 + 0x30); // MOVE.W	12(A0),48(A0)
  DEF_ROMLOC(EA00) : tst_mem_8(A0 + 0x29);           // TST.B	41(A0)
  DEF_ROMLOC(EA04) : if (CCR_EQ) goto rom_EA0A;      // BEQ.B	$EA0A
  DEF_ROMLOC(EA06) : add_tomem_8(0x2, A0 + 0x18);    // ADDQ.B	#$02,24(A0)
  DEF_ROMLOC(EA0A) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(EA0C)
      : move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B	40(A0),D0
  DEF_ROMLOC(EA10) : add_toreg_16(D0, &D0);   // ADD.W	D0,D0
  DEF_ROMLOC(EA12)
      : move_tomem_16(read_16(0xE9AA + (s16)(D0 & 0xffff)),
                      A0 + 0x12);                   // MOVE.W	-106(PC,D0),18(A0)
  DEF_ROMLOC(EA18) : move_tomem_8(0x8, A0 + 0x19);  // MOVE.B	#$08,25(A0)
  DEF_ROMLOC(EA1E) : cmp_tomem_8(0x6, A0 + 0x28);   // CMPI.B	#$06,40(A0)
  DEF_ROMLOC(EA24) : if (CCR_CS) goto rom_EA3E;     // BCS.B	$EA3E
  DEF_ROMLOC(EA26) : move_tomem_8(0x10, A0 + 0x19); // MOVE.B	#$10,25(A0)
  DEF_ROMLOC(EA2C) : move_tomem_8(0x2, A0 + 0x1C);  // MOVE.B	#$02,28(A0)
  DEF_ROMLOC(EA32)
      : move_tomem_16(read_16(A0 + 0x12), A0 + 0x10); // MOVE.W	18(A0),16(A0)
  DEF_ROMLOC(EA38) : move_tomem_16(0x0, A0 + 0x12);   // MOVE.W	#$0000,18(A0)
  DEF_ROMLOC(EA3E) : move_toreg_16(0xAE, &D0);        // MOVE.W	#$00AE,D0
  DEF_ROMLOC(EA42) : rom_1394();                      // JSR	$00001394
  rom_EA48(); // Detected flow into next function
}
ROMFUNC(rom_EA48) {
  u8 switchindex = 0;
  DEF_ROMLOC(EA48) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(EA4A) : move_toreg_8(read_8(A0 + 0x28), &D0);
  switchindex = D0;                         // MOVE.B	40(A0),D0
  DEF_ROMLOC(EA4E) : add_toreg_16(D0, &D0); // ADD.W	D0,D0
  DEF_ROMLOC(EA50)
      : move_toreg_16(read_16(0xEA86 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	52(PC,D0),D1
  // DEF_ROMLOC(EA54): rom_EA86 + (s16)(D1 & 0xffff)(); // JSR	48(PC,D1)
  DEF_ROMLOC(EA54) : switch (switchindex) {
  case 0:
    rom_EA98();
    break;
  case 1:
    rom_EA98();
    break;
  case 2:
    rom_EA98();
    break;
  case 3:
    rom_EA98();
    break;
  case 4:
    rom_EAC0();
    break;
  case 5:
    rom_EAE2();
    break;
  case 6:
    rom_EB04();
    break;
  case 7:
    rom_EB28();
    break;
  case 8:
    rom_EB4C();
    break;
  }
  DEF_ROMLOC(EA58) : rom_DC6C();                 // BSR.W	$DC6C
  DEF_ROMLOC(EA5C) : move_toreg_32(0xEB52, &A1); // LEA.L	$0000EB52,A1
  DEF_ROMLOC(EA62) : rom_ADA2();                 // BSR.W	$ADA2
  rom_EA66(); // Detected flow into next function
}
ROMFUNC(rom_EA66) {
  DEF_ROMLOC(EA66)
      : move_toreg_16(read_16(A0 + 0x8), &D0);      // MOVE.W	8(A0),D0
  DEF_ROMLOC(EA6A) : and_toreg_16(0xFFFFFF80, &D0); // ANDI.W	#$FF80,D0
  DEF_ROMLOC(EA6E)
      : move_toreg_16(read_16(0xFFFFF700), &D1);    // MOVE.W	$F700,D1
  DEF_ROMLOC(EA72) : sub_toreg_16(0x80, &D1);       // SUBI.W	#$0080,D1
  DEF_ROMLOC(EA76) : and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
  DEF_ROMLOC(EA7A) : sub_toreg_16(D1, &D0);         // SUB.W	D1,D0
  DEF_ROMLOC(EA7C) : cmp_toreg_16(0x280, &D0);      // CMPI.W	#$0280,D0
  DEF_ROMLOC(EA80) : if (CCR_HI) {
    rom_DCCE();
    return;
  }                          // BHI.W	$DCCE
  DEF_ROMLOC(EA84) : return; // RTS
}
ROMFUNC(rom_EA86) {
  DEF_ROMLOC(EA86) : or_tomem_8(0x12, A2); // ORI.B	#$12,(A2)
  DEF_ROMLOC(EA8A) : or_tomem_8(0x12, A2); // ORI.B	#$12,(A2)
  rom_EA98();                              // Detected flow into next function
}
ROMFUNC(rom_EA98) {
  DEF_ROMLOC(EA98) : add_tomem_16(0x18, A0 + 0x12); // ADDI.W	#$0018,18(A0)
  DEF_ROMLOC(EA9E)
      : move_toreg_16(read_16(A0 + 0x30), &D0); // MOVE.W	48(A0),D0
  DEF_ROMLOC(EAA2)
      : cmp_toreg_16(read_16(A0 + 0xC), &D0);      // CMP.W	12(A0),D0
  DEF_ROMLOC(EAA6) : if (CCR_CC) goto rom_EAAC;    // BCC.B	$EAAC
  DEF_ROMLOC(EAA8) : add_tomem_8(0x2, A0 + 0x24);  // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(EAAC) : bclr_tomem_8(0x1, A0 + 0x22); // BCLR.B	#$01,34(A0)
  DEF_ROMLOC(EAB2) : tst_mem_16(A0 + 0x12);        // TST.W	18(A0)
  DEF_ROMLOC(EAB6) : if (CCR_PL) goto rom_EABE;    // BPL.B	$EABE
  DEF_ROMLOC(EAB8) : bset_tomem_8(0x1, A0 + 0x22); // BSET.B	#$01,34(A0)
  DEF_ROMLOC(EABE) : return;                       // RTS
}
ROMFUNC(rom_EAC0) {
  DEF_ROMLOC(EAC0) : bset_tomem_8(0x1, A0 + 0x22);  // BSET.B	#$01,34(A0)
  DEF_ROMLOC(EAC6) : rom_15706();                   // BSR.W	$15706
  DEF_ROMLOC(EACA) : tst_reg_16(&D1);               // TST.W	D1
  DEF_ROMLOC(EACC) : if (CCR_PL) goto rom_EAE0;     // BPL.B	$EAE0
  DEF_ROMLOC(EACE) : move_tomem_8(0x8, A0 + 0x28);  // MOVE.B	#$08,40(A0)
  DEF_ROMLOC(EAD4) : move_tomem_8(0x1, A0 + 0x1C);  // MOVE.B	#$01,28(A0)
  DEF_ROMLOC(EADA) : move_tomem_16(0x0, A0 + 0x12); // MOVE.W	#$0000,18(A0)
  DEF_ROMLOC(EAE0) : return;                        // RTS
}
ROMFUNC(rom_EAE2) {
  DEF_ROMLOC(EAE2) : bclr_tomem_8(0x1, A0 + 0x22);  // BCLR.B	#$01,34(A0)
  DEF_ROMLOC(EAE8) : rom_15580();                   // BSR.W	$15580
  DEF_ROMLOC(EAEC) : tst_reg_16(&D1);               // TST.W	D1
  DEF_ROMLOC(EAEE) : if (CCR_PL) goto rom_EB02;     // BPL.B	$EB02
  DEF_ROMLOC(EAF0) : move_tomem_8(0x8, A0 + 0x28);  // MOVE.B	#$08,40(A0)
  DEF_ROMLOC(EAF6) : move_tomem_8(0x1, A0 + 0x1C);  // MOVE.B	#$01,28(A0)
  DEF_ROMLOC(EAFC) : move_tomem_16(0x0, A0 + 0x12); // MOVE.W	#$0000,18(A0)
  DEF_ROMLOC(EB02) : return;                        // RTS
}
ROMFUNC(rom_EB04) {
  DEF_ROMLOC(EB04) : bset_tomem_8(0x0, A0 + 0x22);   // BSET.B	#$00,34(A0)
  DEF_ROMLOC(EB0A) : move_toreg_32(0xFFFFFFF8, &D3); // MOVEQ.L	$F8,D3
  DEF_ROMLOC(EB0C) : rom_157D4();                    // BSR.W	$157D4
  DEF_ROMLOC(EB10) : tst_reg_16(&D1);                // TST.W	D1
  DEF_ROMLOC(EB12) : if (CCR_PL) goto rom_EB26;      // BPL.B	$EB26
  DEF_ROMLOC(EB14) : move_tomem_8(0x8, A0 + 0x28);   // MOVE.B	#$08,40(A0)
  DEF_ROMLOC(EB1A) : move_tomem_8(0x3, A0 + 0x1C);   // MOVE.B	#$03,28(A0)
  DEF_ROMLOC(EB20) : move_tomem_16(0x0, A0 + 0x10);  // MOVE.W	#$0000,16(A0)
  DEF_ROMLOC(EB26) : return;                         // RTS
}
ROMFUNC(rom_EB28) {
  DEF_ROMLOC(EB28) : bclr_tomem_8(0x0, A0 + 0x22);  // BCLR.B	#$00,34(A0)
  DEF_ROMLOC(EB2E) : move_toreg_32(0x8, &D3);       // MOVEQ.L	$08,D3
  DEF_ROMLOC(EB30) : rom_15642();                   // BSR.W	$15642
  DEF_ROMLOC(EB34) : tst_reg_16(&D1);               // TST.W	D1
  DEF_ROMLOC(EB36) : if (CCR_PL) goto rom_EB4A;     // BPL.B	$EB4A
  DEF_ROMLOC(EB38) : move_tomem_8(0x8, A0 + 0x28);  // MOVE.B	#$08,40(A0)
  DEF_ROMLOC(EB3E) : move_tomem_8(0x3, A0 + 0x1C);  // MOVE.B	#$03,28(A0)
  DEF_ROMLOC(EB44) : move_tomem_16(0x0, A0 + 0x10); // MOVE.W	#$0000,16(A0)
  DEF_ROMLOC(EB4A) : return;                        // RTS
}
ROMFUNC(rom_EB4C) {
  DEF_ROMLOC(EB4C) : return; // RTS
}
ROMFUNC(rom_EB4E) {
  rom_DCCE(); // BRA.W	$DCCE
}