// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"


ROMFUNC(rom_A79A) {
  u8 switchindex = 0;
  DEF_ROMLOC(A79A) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(A79C) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(A7A0)
      : move_toreg_16(read_16(0xA7A8 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(A7A4): goto rom_A7A8 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(A7A4) : switch (switchindex) {
  case 0:
    rom_A7B2();
    break;
  case 1:
    rom_A814();
    break;
  case 2:
    rom_A926();
    break;
  case 3:
    rom_A8F8();
    break;
  case 4:
    rom_A902();
    break;
  }
}
ROMFUNC(rom_A7B2) {
  DEF_ROMLOC(A7B2) : add_tomem_8(0x2, A0 + 0x24);  // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(A7B6) : move_tomem_8(0xE, A0 + 0x16); // MOVE.B	#$0E,22(A0)
  DEF_ROMLOC(A7BC) : move_tomem_8(0xE, A0 + 0x17); // MOVE.B	#$0E,23(A0)
  DEF_ROMLOC(A7C2)
      : move_tomem_32(0xAC14, A0 + 0x4);             // MOVE.L	#$0000AC14,4(A0)
  DEF_ROMLOC(A7CA) : move_tomem_16(0x680, A0 + 0x2); // MOVE.W	#$0680,2(A0)
  DEF_ROMLOC(A7D0) : move_tomem_8(0x4, A0 + 0x1);    // MOVE.B	#$04,1(A0)
  DEF_ROMLOC(A7D6) : move_tomem_8(0x3, A0 + 0x18);   // MOVE.B	#$03,24(A0)
  DEF_ROMLOC(A7DC) : move_tomem_8(0xF, A0 + 0x19);   // MOVE.B	#$0F,25(A0)
  DEF_ROMLOC(A7E2) : move_toreg_32(0xFFFFFC00, &A2); // LEA.L	$FC00,A2
  DEF_ROMLOC(A7E6) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(A7E8)
      : move_toreg_8(read_8(A0 + 0x23), &D0); // MOVE.B	35(A0),D0
  DEF_ROMLOC(A7EC)
      : bclr_tomem_8(0x7,
                     (s32)A2 + (s8)0x2 + (s16)D0); // BCLR.B	#$07,2(A2,D0)
  DEF_ROMLOC(A7F2)
      : btst_tomem_8(0x0,
                     (s32)A2 + (s8)0x2 + (s16)D0);  // BTST.B	#$00,2(A2,D0)
  DEF_ROMLOC(A7F8) : if (CCR_EQ) goto rom_A808;     // BEQ.B	$A808
  DEF_ROMLOC(A7FA) : move_tomem_8(0x8, A0 + 0x24);  // MOVE.B	#$08,36(A0)
  DEF_ROMLOC(A800) : move_tomem_8(0xB, A0 + 0x1A);  // MOVE.B	#$0B,26(A0)
  DEF_ROMLOC(A806) : return;                        // RTS
  DEF_ROMLOC(A808) : move_tomem_8(0x46, A0 + 0x20); // MOVE.B	#$46,32(A0)
  DEF_ROMLOC(A80E)
      : move_tomem_8(read_8(A0 + 0x28), A0 + 0x1C); // MOVE.B	40(A0),28(A0)
  rom_A814(); // Detected flow into next function
}
ROMFUNC(rom_A814) {
  DEF_ROMLOC(A814)
      : move_toreg_8(read_8(A0 + 0x25), &D0);    // MOVE.B	37(A0),D0
  DEF_ROMLOC(A818) : if (CCR_EQ) goto rom_A86E;  // BEQ.B	$A86E
  DEF_ROMLOC(A81A) : sub_toreg_8(0x2, &D0);      // SUBQ.B	#$02,D0
  DEF_ROMLOC(A81C) : if (!CCR_EQ) goto rom_A84E; // BNE.B	$A84E
  DEF_ROMLOC(A81E) : move_toreg_32(0x0, &D1);    // MOVEQ.L	$00,D1
  DEF_ROMLOC(A820)
      : move_toreg_8(read_8(A0 + 0x19), &D1);      // MOVE.B	25(A0),D1
  DEF_ROMLOC(A824) : add_toreg_16(0xB, &D1);       // ADDI.W	#$000B,D1
  DEF_ROMLOC(A828) : rom_7C3E();                   // BSR.W	$7C3E
  DEF_ROMLOC(A82C) : btst_tomem_8(0x3, A1 + 0x22); // BTST.B	#$03,34(A1)
  DEF_ROMLOC(A832) : if (!CCR_EQ) goto rom_A83E;   // BNE.W	$A83E
  DEF_ROMLOC(A836) : clr_mem_8(A0 + 0x25);         // CLR.B	37(A0)
  DEF_ROMLOC(A83A) : {
    rom_A8F8();
    return;
  }                                            // BRA.W	$A8F8
  DEF_ROMLOC(A83E) : move_toreg_16(0x10, &D3); // MOVE.W	#$0010,D3
  DEF_ROMLOC(A842)
      : move_toreg_16(read_16(A0 + 0x8), &D2); // MOVE.W	8(A0),D2
  DEF_ROMLOC(A846) : rom_81A0();               // BSR.W	$81A0
  DEF_ROMLOC(A84A) : {
    rom_A8F8();
    return;
  }                                   // BRA.W	$A8F8
  DEF_ROMLOC(A84E) : rom_DC40();      // BSR.W	$DC40
  DEF_ROMLOC(A852) : rom_15580();     // JSR	$00015580
  DEF_ROMLOC(A858) : tst_reg_16(&D1); // TST.W	D1
  DEF_ROMLOC(A85A) : if (CCR_PL) {
    rom_A8F8();
    return;
  }                                              // BPL.W	$A8F8
  DEF_ROMLOC(A85E) : add_tomem_16(D1, A0 + 0xC); // ADD.W	D1,12(A0)
  DEF_ROMLOC(A862) : clr_mem_16(A0 + 0x12);      // CLR.W	18(A0)
  DEF_ROMLOC(A866) : clr_mem_8(A0 + 0x25);       // CLR.B	37(A0)
  DEF_ROMLOC(A86A) : {
    rom_A8F8();
    return;
  }                                                // BRA.W	$A8F8
  DEF_ROMLOC(A86E) : move_toreg_16(0x1A, &D1);     // MOVE.W	#$001A,D1
  DEF_ROMLOC(A872) : move_toreg_16(0xF, &D2);      // MOVE.W	#$000F,D2
  DEF_ROMLOC(A876) : rom_AB18();                   // BSR.W	$AB18
  DEF_ROMLOC(A87A) : if (CCR_EQ) goto rom_A8DE;    // BEQ.W	$A8DE
  DEF_ROMLOC(A87E) : tst_mem_16(A1 + 0x12);        // TST.W	18(A1)
  DEF_ROMLOC(A882) : if (CCR_MI) goto rom_A88C;    // BMI.B	$A88C
  DEF_ROMLOC(A884) : cmp_tomem_8(0x2, A1 + 0x1C);  // CMPI.B	#$02,28(A1)
  DEF_ROMLOC(A88A) : if (CCR_EQ) goto rom_A8DE;    // BEQ.B	$A8DE
  DEF_ROMLOC(A88C) : tst_reg_16(&D1);              // TST.W	D1
  DEF_ROMLOC(A88E) : if (CCR_PL) goto rom_A8A2;    // BPL.B	$A8A2
  DEF_ROMLOC(A890) : sub_tomem_16(D3, A1 + 0xC);   // SUB.W	D3,12(A1)
  DEF_ROMLOC(A894) : rom_7B2C();                   // BSR.W	$7B2C
  DEF_ROMLOC(A898) : move_tomem_8(0x2, A0 + 0x25); // MOVE.B	#$02,37(A0)
  rom_A8F8();
  return;                                           // BRA.W	$A8F8
  DEF_ROMLOC(A8A2) : tst_reg_16(&D0);               // TST.W	D0
  DEF_ROMLOC(A8A4) : if (CCR_EQ) goto rom_A8C8;     // BEQ.W	$A8C8
  DEF_ROMLOC(A8A8) : if (CCR_MI) goto rom_A8B2;     // BMI.B	$A8B2
  DEF_ROMLOC(A8AA) : tst_mem_16(A1 + 0x10);         // TST.W	16(A1)
  DEF_ROMLOC(A8AE) : if (CCR_MI) goto rom_A8C8;     // BMI.B	$A8C8
  goto rom_A8B8;                                    // BRA.B	$A8B8
  DEF_ROMLOC(A8B2) : tst_mem_16(A1 + 0x10);         // TST.W	16(A1)
  DEF_ROMLOC(A8B6) : if (CCR_PL) goto rom_A8C8;     // BPL.B	$A8C8
  DEF_ROMLOC(A8B8) : sub_tomem_16(D0, A1 + 0x8);    // SUB.W	D0,8(A1)
  DEF_ROMLOC(A8BC) : move_tomem_16(0x0, A1 + 0x14); // MOVE.W	#$0000,20(A1)
  DEF_ROMLOC(A8C2) : move_tomem_16(0x0, A1 + 0x10); // MOVE.W	#$0000,16(A1)
  DEF_ROMLOC(A8C8) : btst_tomem_8(0x1, A1 + 0x22);  // BTST.B	#$01,34(A1)
  DEF_ROMLOC(A8CE) : if (!CCR_EQ) goto rom_A8EC;    // BNE.B	$A8EC
  DEF_ROMLOC(A8D0) : bset_tomem_8(0x5, A1 + 0x22);  // BSET.B	#$05,34(A1)
  DEF_ROMLOC(A8D6) : bset_tomem_8(0x5, A0 + 0x22);  // BSET.B	#$05,34(A0)
  rom_A8F8();
  return;                                          // BRA.B	$A8F8
  DEF_ROMLOC(A8DE) : btst_tomem_8(0x5, A0 + 0x22); // BTST.B	#$05,34(A0)
  DEF_ROMLOC(A8E4) : if (CCR_EQ) {
    rom_A8F8();
    return;
  }                                                 // BEQ.B	$A8F8
  DEF_ROMLOC(A8E6) : move_tomem_16(0x1, A1 + 0x1C); // MOVE.W	#$0001,28(A1)
  DEF_ROMLOC(A8EC) : bclr_tomem_8(0x5, A0 + 0x22);  // BCLR.B	#$05,34(A0)
  DEF_ROMLOC(A8F2) : bclr_tomem_8(0x5, A1 + 0x22);  // BCLR.B	#$05,34(A1)
  rom_A8F8(); // Detected flow into next function
}
ROMFUNC(rom_A8F8) {
  DEF_ROMLOC(A8F8) : move_toreg_32(0xAB92, &A1); // LEA.L	$0000AB92,A1
  DEF_ROMLOC(A8FE) : rom_ADA2();                 // BSR.W	$ADA2
  rom_A902(); // Detected flow into next function
}
ROMFUNC(rom_A902) {
  DEF_ROMLOC(A902) : rom_DC92(); // BSR.W	$DC92
  DEF_ROMLOC(A906)
      : move_toreg_16(read_16(A0 + 0x8), &D0);      // MOVE.W	8(A0),D0
  DEF_ROMLOC(A90A) : and_toreg_16(0xFFFFFF80, &D0); // ANDI.W	#$FF80,D0
  DEF_ROMLOC(A90E)
      : move_toreg_16(read_16(0xFFFFF700), &D1);    // MOVE.W	$F700,D1
  DEF_ROMLOC(A912) : sub_toreg_16(0x80, &D1);       // SUBI.W	#$0080,D1
  DEF_ROMLOC(A916) : and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
  DEF_ROMLOC(A91A) : sub_toreg_16(D1, &D0);         // SUB.W	D1,D0
  DEF_ROMLOC(A91C) : cmp_toreg_16(0x280, &D0);      // CMPI.W	#$0280,D0
  DEF_ROMLOC(A920) : if (CCR_HI) {
    rom_DCCE();
    return;
  }                          // BHI.W	$DCCE
  DEF_ROMLOC(A924) : return; // RTS
}
ROMFUNC(rom_A926) {
  DEF_ROMLOC(A926) : add_tomem_8(0x2, A0 + 0x24);  // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(A92A) : move_tomem_8(0x0, A0 + 0x20); // MOVE.B	#$00,32(A0)
  DEF_ROMLOC(A930) : rom_E11A();                   // BSR.W	$E11A
  DEF_ROMLOC(A934) : if (!CCR_EQ) goto rom_A94E;   // BNE.B	$A94E
  DEF_ROMLOC(A936) : move_tomem_8(0x2E, A1 + 0x0); // MOVE.B	#$2E,0(A1)
  DEF_ROMLOC(A93C)
      : move_tomem_16(read_16(A0 + 0x8), A1 + 0x8); // MOVE.W	8(A0),8(A1)
  DEF_ROMLOC(A942)
      : move_tomem_16(read_16(A0 + 0xC), A1 + 0xC); // MOVE.W	12(A0),12(A1)
  DEF_ROMLOC(A948)
      : move_tomem_8(read_8(A0 + 0x1C), A1 + 0x1C); // MOVE.B	28(A0),28(A1)
  DEF_ROMLOC(A94E) : rom_E11A();                    // BSR.W	$E11A
  DEF_ROMLOC(A952) : if (!CCR_EQ) goto rom_A96A;    // BNE.B	$A96A
  DEF_ROMLOC(A954) : move_tomem_8(0x27, A1 + 0x0);  // MOVE.B	#$27,0(A1)
  DEF_ROMLOC(A95A) : add_tomem_8(0x2, A1 + 0x24);   // ADDQ.B	#$02,36(A1)
  DEF_ROMLOC(A95E)
      : move_tomem_16(read_16(A0 + 0x8), A1 + 0x8); // MOVE.W	8(A0),8(A1)
  DEF_ROMLOC(A964)
      : move_tomem_16(read_16(A0 + 0xC), A1 + 0xC);  // MOVE.W	12(A0),12(A1)
  DEF_ROMLOC(A96A) : move_toreg_32(0xFFFFFC00, &A2); // LEA.L	$FC00,A2
  DEF_ROMLOC(A96E) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(A970)
      : move_toreg_8(read_8(A0 + 0x23), &D0); // MOVE.B	35(A0),D0
  DEF_ROMLOC(A974)
      : bset_tomem_8(0x0,
                     (s32)A2 + (s8)0x2 + (s16)D0); // BSET.B	#$00,2(A2,D0)
  DEF_ROMLOC(A97A) : move_tomem_8(0x9, A0 + 0x1C); // MOVE.B	#$09,28(A0)
  rom_DC92();                                      // BRA.W	$DC92
}