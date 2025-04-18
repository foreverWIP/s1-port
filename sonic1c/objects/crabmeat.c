// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_9B6E) {
  u8 switchindex = 0;
  DEF_ROMLOC(9B6E) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(9B70) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(9B74)
      : move_toreg_16(read_16(0x9B7C + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(9B78): goto rom_9B7C + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(9B78) : switch (switchindex) {
  case 0:
    rom_9B86();
    break;
  case 1:
    rom_9BDA();
    break;
  case 2:
    rom_9D36();
    break;
  case 3:
    rom_9D3C();
    break;
  case 4:
    rom_9D72();
    break;
  }
}
ROMFUNC(rom_9B86) {
  DEF_ROMLOC(9B86) : move_tomem_8(0x10, A0 + 0x16); // MOVE.B	#$10,22(A0)
  DEF_ROMLOC(9B8C) : move_tomem_8(0x8, A0 + 0x17);  // MOVE.B	#$08,23(A0)
  DEF_ROMLOC(9B92)
      : move_tomem_32(0x9DCE, A0 + 0x4);             // MOVE.L	#$00009DCE,4(A0)
  DEF_ROMLOC(9B9A) : move_tomem_16(0x400, A0 + 0x2); // MOVE.W	#$0400,2(A0)
  DEF_ROMLOC(9BA0) : move_tomem_8(0x4, A0 + 0x1);    // MOVE.B	#$04,1(A0)
  DEF_ROMLOC(9BA6) : move_tomem_8(0x3, A0 + 0x18);   // MOVE.B	#$03,24(A0)
  DEF_ROMLOC(9BAC) : move_tomem_8(0x6, A0 + 0x20);   // MOVE.B	#$06,32(A0)
  DEF_ROMLOC(9BB2) : move_tomem_8(0x15, A0 + 0x19);  // MOVE.B	#$15,25(A0)
  DEF_ROMLOC(9BB8) : rom_DC40();                     // BSR.W	$DC40
  DEF_ROMLOC(9BBC) : rom_15580();                    // JSR	$00015580
  DEF_ROMLOC(9BC2) : tst_reg_16(&D1);                // TST.W	D1
  DEF_ROMLOC(9BC4) : if (CCR_PL) goto rom_9BD8;      // BPL.B	$9BD8
  DEF_ROMLOC(9BC6) : add_tomem_16(D1, A0 + 0xC);     // ADD.W	D1,12(A0)
  DEF_ROMLOC(9BCA) : move_tomem_8(D3, A0 + 0x26);    // MOVE.B	D3,38(A0)
  DEF_ROMLOC(9BCE) : move_tomem_16(0x0, A0 + 0x12);  // MOVE.W	#$0000,18(A0)
  DEF_ROMLOC(9BD4) : add_tomem_8(0x2, A0 + 0x24);    // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(9BD8) : return;                         // RTS
}
ROMFUNC(rom_9BFA);
ROMFUNC(rom_9C98);
ROMFUNC(rom_9BDA) {
  u8 switchindex = 0;
  DEF_ROMLOC(9BDA) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(9BDC) : move_toreg_8(read_8(A0 + 0x25), &D0);
  switchindex = D0 / 2; // MOVE.B	37(A0),D0
  DEF_ROMLOC(9BE0)
      : move_toreg_16(read_16(0x9BF6 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	20(PC,D0),D1
  // DEF_ROMLOC(9BE4): rom_9BF6 + (s16)(D1 & 0xffff)(); // JSR	16(PC,D1)
  DEF_ROMLOC(9BE4) : switch (switchindex) {
  case 0:
    rom_9BFA();
    break;
  case 1:
    rom_9C98();
    break;
  }
  DEF_ROMLOC(9BE8) : move_toreg_32(0x9D98, &A1); // LEA.L	$00009D98,A1
  DEF_ROMLOC(9BEE) : animate_sprite();           // BSR.W	$ADA2
  DEF_ROMLOC(9BF2) : {
    rom_FD38();
    return;
  } // BRA.W	$FD38
}
ROMFUNC(rom_9BFA) {
  DEF_ROMLOC(9BFA) : sub_tomem_16(0x1, A0 + 0x30);   // SUBQ.W	#$01,48(A0)
  DEF_ROMLOC(9BFE) : if (CCR_PL) goto rom_9C34;      // BPL.B	$9C34
  DEF_ROMLOC(9C00) : tst_mem_8(A0 + 0x1);            // TST.B	1(A0)
  DEF_ROMLOC(9C04) : if (CCR_PL) goto rom_9C0E;      // BPL.B	$9C0E
  DEF_ROMLOC(9C06) : bchg_tomem_8(0x1, A0 + 0x32);   // BCHG.B	#$01,50(A0)
  DEF_ROMLOC(9C0C) : if (!CCR_EQ) goto rom_9C36;     // BNE.B	$9C36
  DEF_ROMLOC(9C0E) : add_tomem_8(0x2, A0 + 0x25);    // ADDQ.B	#$02,37(A0)
  DEF_ROMLOC(9C12) : move_tomem_16(0x7F, A0 + 0x30); // MOVE.W	#$007F,48(A0)
  DEF_ROMLOC(9C18) : move_tomem_16(0x80, A0 + 0x10); // MOVE.W	#$0080,16(A0)
  DEF_ROMLOC(9C1E) : rom_9D06();                     // BSR.W	$9D06
  DEF_ROMLOC(9C22) : add_toreg_8(0x3, &D0);          // ADDQ.B	#$03,D0
  DEF_ROMLOC(9C24) : move_tomem_8(D0, A0 + 0x1C);    // MOVE.B	D0,28(A0)
  DEF_ROMLOC(9C28) : bchg_tomem_8(0x0, A0 + 0x22);   // BCHG.B	#$00,34(A0)
  DEF_ROMLOC(9C2E) : if (!CCR_EQ) goto rom_9C34;     // BNE.B	$9C34
  DEF_ROMLOC(9C30) : neg_mem_16(A0 + 0x10);          // NEG.W	16(A0)
  DEF_ROMLOC(9C34) : return;                         // RTS
  DEF_ROMLOC(9C36) : move_tomem_16(0x3B, A0 + 0x30); // MOVE.W	#$003B,48(A0)
  DEF_ROMLOC(9C3C) : move_tomem_8(0x6, A0 + 0x1C);   // MOVE.B	#$06,28(A0)
  DEF_ROMLOC(9C42) : rom_E11A();                     // BSR.W	$E11A
  DEF_ROMLOC(9C46) : if (!CCR_EQ) goto rom_9C6C;     // BNE.B	$9C6C
  DEF_ROMLOC(9C48)
      : move_tomem_8(OBJ_CRABMEAT,
                     A1 + offsetof(object, id));   // MOVE.B	#$1F,0(A1)
  DEF_ROMLOC(9C4E) : move_tomem_8(0x6, A1 + 0x24); // MOVE.B	#$06,36(A1)
  DEF_ROMLOC(9C54)
      : move_tomem_16(read_16(A0 + 0x8), A1 + 0x8); // MOVE.W	8(A0),8(A1)
  DEF_ROMLOC(9C5A) : sub_tomem_16(0x10, A1 + 0x8);  // SUBI.W	#$0010,8(A1)
  DEF_ROMLOC(9C60)
      : move_tomem_16(read_16(A0 + 0xC), A1 + 0xC); // MOVE.W	12(A0),12(A1)
  DEF_ROMLOC(9C66)
      : move_tomem_16(0xFFFFFF00, A1 + 0x10);    // MOVE.W	#$FF00,16(A1)
  DEF_ROMLOC(9C6C) : rom_E11A();                 // BSR.W	$E11A
  DEF_ROMLOC(9C70) : if (!CCR_EQ) goto rom_9C96; // BNE.B	$9C96
  DEF_ROMLOC(9C72)
      : move_tomem_8(OBJ_CRABMEAT,
                     A1 + offsetof(object, id));   // MOVE.B	#$1F,0(A1)
  DEF_ROMLOC(9C78) : move_tomem_8(0x6, A1 + 0x24); // MOVE.B	#$06,36(A1)
  DEF_ROMLOC(9C7E)
      : move_tomem_16(read_16(A0 + 0x8), A1 + 0x8); // MOVE.W	8(A0),8(A1)
  DEF_ROMLOC(9C84) : add_tomem_16(0x10, A1 + 0x8);  // ADDI.W	#$0010,8(A1)
  DEF_ROMLOC(9C8A)
      : move_tomem_16(read_16(A0 + 0xC), A1 + 0xC);   // MOVE.W	12(A0),12(A1)
  DEF_ROMLOC(9C90) : move_tomem_16(0x100, A1 + 0x10); // MOVE.W	#$0100,16(A1)
  DEF_ROMLOC(9C96) : return;                          // RTS
}
ROMFUNC(rom_9C98) {
  DEF_ROMLOC(9C98) : sub_tomem_16(0x1, A0 + 0x30); // SUBQ.W	#$01,48(A0)
  DEF_ROMLOC(9C9C) : if (CCR_MI) goto rom_9CEC;    // BMI.B	$9CEC
  DEF_ROMLOC(9C9E) : rom_DC6C();                   // BSR.W	$DC6C
  DEF_ROMLOC(9CA2) : bchg_tomem_8(0x0, A0 + 0x32); // BCHG.B	#$00,50(A0)
  DEF_ROMLOC(9CA8) : if (!CCR_EQ) goto rom_9CD2;   // BNE.B	$9CD2
  DEF_ROMLOC(9CAA) : move_toreg_16(read_16(A0 + 0x8), &D3); // MOVE.W	8(A0),D3
  DEF_ROMLOC(9CAE) : add_toreg_16(0x10, &D3);               // ADDI.W	#$0010,D3
  DEF_ROMLOC(9CB2) : btst_tomem_8(0x0, A0 + 0x22);   // BTST.B	#$00,34(A0)
  DEF_ROMLOC(9CB8) : if (CCR_EQ) goto rom_9CBE;      // BEQ.B	$9CBE
  DEF_ROMLOC(9CBA) : sub_toreg_16(0x20, &D3);        // SUBI.W	#$0020,D3
  DEF_ROMLOC(9CBE) : rom_15584();                    // JSR	$00015584
  DEF_ROMLOC(9CC4) : cmp_toreg_16(0xFFFFFFF8, &D1);  // CMPI.W	#$FFF8,D1
  DEF_ROMLOC(9CC8) : if (CCR_LT) goto rom_9CEC;      // BLT.B	$9CEC
  DEF_ROMLOC(9CCA) : cmp_toreg_16(0xC, &D1);         // CMPI.W	#$000C,D1
  DEF_ROMLOC(9CCE) : if (CCR_GE) goto rom_9CEC;      // BGE.B	$9CEC
  DEF_ROMLOC(9CD0) : return;                         // RTS
  DEF_ROMLOC(9CD2) : rom_15580();                    // JSR	$00015580
  DEF_ROMLOC(9CD8) : add_tomem_16(D1, A0 + 0xC);     // ADD.W	D1,12(A0)
  DEF_ROMLOC(9CDC) : move_tomem_8(D3, A0 + 0x26);    // MOVE.B	D3,38(A0)
  DEF_ROMLOC(9CE0) : rom_9D06();                     // BSR.W	$9D06
  DEF_ROMLOC(9CE4) : add_toreg_8(0x3, &D0);          // ADDQ.B	#$03,D0
  DEF_ROMLOC(9CE6) : move_tomem_8(D0, A0 + 0x1C);    // MOVE.B	D0,28(A0)
  DEF_ROMLOC(9CEA) : return;                         // RTS
  DEF_ROMLOC(9CEC) : sub_tomem_8(0x2, A0 + 0x25);    // SUBQ.B	#$02,37(A0)
  DEF_ROMLOC(9CF0) : move_tomem_16(0x3B, A0 + 0x30); // MOVE.W	#$003B,48(A0)
  DEF_ROMLOC(9CF6) : move_tomem_16(0x0, A0 + 0x10);  // MOVE.W	#$0000,16(A0)
  DEF_ROMLOC(9CFC) : rom_9D06();                     // BSR.W	$9D06
  DEF_ROMLOC(9D00) : move_tomem_8(D0, A0 + 0x1C);    // MOVE.B	D0,28(A0)
  DEF_ROMLOC(9D04) : return;                         // RTS
}
ROMFUNC(rom_9D06) {
  DEF_ROMLOC(9D06) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(9D08)
      : move_toreg_8(read_8(A0 + 0x26), &D3);      // MOVE.B	38(A0),D3
  DEF_ROMLOC(9D0C) : if (CCR_MI) goto rom_9D22;    // BMI.B	$9D22
  DEF_ROMLOC(9D0E) : cmp_toreg_8(0x6, &D3);        // CMPI.B	#$06,D3
  DEF_ROMLOC(9D12) : if (CCR_CS) goto rom_9D20;    // BCS.B	$9D20
  DEF_ROMLOC(9D14) : move_toreg_32(0x1, &D0);      // MOVEQ.L	$01,D0
  DEF_ROMLOC(9D16) : btst_tomem_8(0x0, A0 + 0x22); // BTST.B	#$00,34(A0)
  DEF_ROMLOC(9D1C) : if (!CCR_EQ) goto rom_9D20;   // BNE.B	$9D20
  DEF_ROMLOC(9D1E) : move_toreg_32(0x2, &D0);      // MOVEQ.L	$02,D0
  DEF_ROMLOC(9D20) : return;                       // RTS
  DEF_ROMLOC(9D22) : cmp_toreg_8(0xFFFFFFFA, &D3); // CMPI.B	#$FA,D3
  DEF_ROMLOC(9D26) : if (CCR_HI) goto rom_9D34;    // BHI.B	$9D34
  DEF_ROMLOC(9D28) : move_toreg_32(0x2, &D0);      // MOVEQ.L	$02,D0
  DEF_ROMLOC(9D2A) : btst_tomem_8(0x0, A0 + 0x22); // BTST.B	#$00,34(A0)
  DEF_ROMLOC(9D30) : if (!CCR_EQ) goto rom_9D34;   // BNE.B	$9D34
  DEF_ROMLOC(9D32) : move_toreg_32(0x1, &D0);      // MOVEQ.L	$01,D0
  DEF_ROMLOC(9D34) : return;                       // RTS
}
ROMFUNC(rom_9D36) {
  DEF_ROMLOC(9D36) : rom_DCCE(); // BSR.W	$DCCE
  DEF_ROMLOC(9D3A) : return;     // RTS
}
ROMFUNC(rom_9D3C) {
  DEF_ROMLOC(9D3C) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(9D40)
      : move_tomem_32(0x9DCE, A0 + 0x4);             // MOVE.L	#$00009DCE,4(A0)
  DEF_ROMLOC(9D48) : move_tomem_16(0x400, A0 + 0x2); // MOVE.W	#$0400,2(A0)
  DEF_ROMLOC(9D4E) : move_tomem_8(0x4, A0 + 0x1);    // MOVE.B	#$04,1(A0)
  DEF_ROMLOC(9D54) : move_tomem_8(0x3, A0 + 0x18);   // MOVE.B	#$03,24(A0)
  DEF_ROMLOC(9D5A)
      : move_tomem_8(0xFFFFFF87, A0 + 0x20);       // MOVE.B	#$87,32(A0)
  DEF_ROMLOC(9D60) : move_tomem_8(0x8, A0 + 0x19); // MOVE.B	#$08,25(A0)
  DEF_ROMLOC(9D66)
      : move_tomem_16(0xFFFFFC00, A0 + 0x12);      // MOVE.W	#$FC00,18(A0)
  DEF_ROMLOC(9D6C) : move_tomem_8(0x7, A0 + 0x1C); // MOVE.B	#$07,28(A0)
  rom_9D72(); // Detected flow into next function
}
ROMFUNC(rom_9D72) {
  DEF_ROMLOC(9D72) : move_toreg_32(0x9D98, &A1); // LEA.L	$00009D98,A1
  DEF_ROMLOC(9D78) : animate_sprite();           // BSR.W	$ADA2
  DEF_ROMLOC(9D7C) : rom_DC40();                 // BSR.W	$DC40
  DEF_ROMLOC(9D80) : queue_sprite();             // BSR.W	$DC92
  DEF_ROMLOC(9D84)
      : move_toreg_16(read_16(0xFFFFF72E), &D0); // MOVE.W	$F72E,D0
  DEF_ROMLOC(9D88) : add_toreg_16(0xE0, &D0);    // ADDI.W	#$00E0,D0
  DEF_ROMLOC(9D8C)
      : cmp_toreg_16(read_16(A0 + 0xC), &D0);   // CMP.W	12(A0),D0
  DEF_ROMLOC(9D90) : if (CCR_CS) goto rom_9D94; // BCS.B	$9D94
  DEF_ROMLOC(9D92) : return;                    // RTS
  DEF_ROMLOC(9D94) : {
    rom_DCCE();
    return;
  }
}