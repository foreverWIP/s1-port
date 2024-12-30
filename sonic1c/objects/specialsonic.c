// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"


ROMFUNC(rom_1C13A) {
  u8 switchindex = 0;
  DEF_ROMLOC(1C13A) : tst_mem_16(0xFFFFFE08);     // TST.W	$FE08
  DEF_ROMLOC(1C13E) : if (CCR_EQ) goto rom_1C148; // BEQ.B	$1C148
  DEF_ROMLOC(1C140) : rom_1C36C();                // BSR.W	$1C36C
  rom_1D6E6();
  return;                                      // BRA.W	$1D6E6
  DEF_ROMLOC(1C148) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(1C14A) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(1C14E)
      : move_toreg_16(read_16(0x1C156 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(1C152): goto rom_1C156 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(1C152) : switch (switchindex) {
  case 0:
    rom_1C15E();
    break;
  case 1:
    rom_1C19A();
    break;
  case 2:
    rom_1C396();
    break;
  case 3:
    rom_1C3EA();
    break;
  }
}
ROMFUNC(rom_1C15E) {
  DEF_ROMLOC(1C15E) : add_tomem_8(0x2, A0 + 0x24);  // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(1C162) : move_tomem_8(0xE, A0 + 0x16); // MOVE.B	#$0E,22(A0)
  DEF_ROMLOC(1C168) : move_tomem_8(0x7, A0 + 0x17); // MOVE.B	#$07,23(A0)
  DEF_ROMLOC(1C16E)
      : move_tomem_32(0x21CF4, A0 + 0x4);             // MOVE.L	#$00021CF4,4(A0)
  DEF_ROMLOC(1C176) : move_tomem_16(0x780, A0 + 0x2); // MOVE.W	#$0780,2(A0)
  DEF_ROMLOC(1C17C) : move_tomem_8(0x4, A0 + 0x1);    // MOVE.B	#$04,1(A0)
  DEF_ROMLOC(1C182) : move_tomem_8(0x0, A0 + 0x18);   // MOVE.B	#$00,24(A0)
  DEF_ROMLOC(1C188) : move_tomem_8(0x2, A0 + 0x1C);   // MOVE.B	#$02,28(A0)
  DEF_ROMLOC(1C18E) : bset_tomem_8(0x2, A0 + 0x22);   // BSET.B	#$02,34(A0)
  DEF_ROMLOC(1C194) : bset_tomem_8(0x1, A0 + 0x22);   // BSET.B	#$01,34(A0)
  rom_1C19A(); // Detected flow into next function
}
ROMFUNC(rom_1C19A) {
  u8 switchindex = 0;
  DEF_ROMLOC(1C19A) : tst_mem_16(0xFFFFFFFA);         // TST.W	$FFFA
  DEF_ROMLOC(1C19E) : if (CCR_EQ) goto rom_1C1AE;     // BEQ.B	$1C1AE
  DEF_ROMLOC(1C1A0) : btst_tomem_8(0x4, 0xFFFFF605);  // BTST.B	#$04,$F605
  DEF_ROMLOC(1C1A6) : if (CCR_EQ) goto rom_1C1AE;     // BEQ.B	$1C1AE
  DEF_ROMLOC(1C1A8) : move_tomem_16(0x1, 0xFFFFFE08); // MOVE.W	#$0001,$FE08
  DEF_ROMLOC(1C1AE) : move_tomem_8(0x0, A0 + 0x30);   // MOVE.B	#$00,48(A0)
  DEF_ROMLOC(1C1B4) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(1C1B6)
      : move_toreg_8(read_8(A0 + 0x22), &D0); // MOVE.B	34(A0),D0
  DEF_ROMLOC(1C1BA) : and_toreg_16(0x2, &D0);
  switchindex = D0 / 2; // ANDI.W	#$0002,D0
  DEF_ROMLOC(1C1BE)
      : move_toreg_16(read_16(0x1C1D2 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	18(PC,D0),D1
  // DEF_ROMLOC(1C1C2): rom_1C1D2 + (s16)(D1 & 0xffff)(); // JSR
  // 14(PC,D1)
  DEF_ROMLOC(1C1C2) : switch (switchindex) {
  case 0:
    rom_1C1D6();
    break;
  case 1:
    rom_1C1E4();
    break;
  }
  DEF_ROMLOC(1C1C6) : rom_14312(); // JSR	$00014312
  DEF_ROMLOC(1C1CC) : {
    rom_DC92();
    return;
  } // JMP	$0000DC92
}
ROMFUNC(rom_1C1D6) {
  DEF_ROMLOC(1C1D6) : rom_1C30C(); // BSR.W	$1C30C
  DEF_ROMLOC(1C1DA) : rom_1C216(); // BSR.W	$1C216
  DEF_ROMLOC(1C1DE) : rom_1C40C(); // BSR.W	$1C40C
  rom_1C1F0();                     // BRA.B	$1C1F0
}
ROMFUNC(rom_1C1E4) {
  DEF_ROMLOC(1C1E4) : rom_1C350(); // BSR.W	$1C350
  DEF_ROMLOC(1C1E8) : rom_1C216(); // BSR.W	$1C216
  DEF_ROMLOC(1C1EC) : rom_1C40C(); // BSR.W	$1C40C
  rom_1C1F0();                     // Detected flow into next function
}
ROMFUNC(rom_1C1F0) {
  DEF_ROMLOC(1C1F0) : rom_1C508(); // BSR.W	$1C508
  DEF_ROMLOC(1C1F4) : rom_1C644(); // BSR.W	$1C644
  DEF_ROMLOC(1C1F8) : rom_DC6C();  // JSR	$0000DC6C
  DEF_ROMLOC(1C1FE) : rom_1C36C(); // BSR.W	$1C36C
  DEF_ROMLOC(1C202)
      : move_toreg_16(read_16(0xFFFFF780), &D0); // MOVE.W	$F780,D0
  DEF_ROMLOC(1C206)
      : add_toreg_16(read_16(0xFFFFF782), &D0);      // ADD.W	$F782,D0
  DEF_ROMLOC(1C20A) : move_tomem_16(D0, 0xFFFFF780); // MOVE.W	D0,$F780
  DEF_ROMLOC(1C20E) : rom_14098();                   // JSR	$00014098
  DEF_ROMLOC(1C214) : return;                        // RTS
}
ROMFUNC(rom_1C216) {
  u32 d0backup = 0;
  u32 d1backup = 0;
  DEF_ROMLOC(1C216) : btst_tomem_8(0x2, 0xFFFFF602); // BTST.B	#$02,$F602
  DEF_ROMLOC(1C21C) : if (CCR_EQ) goto rom_1C222;    // BEQ.B	$1C222
  DEF_ROMLOC(1C21E) : rom_1C2AE();                   // BSR.W	$1C2AE
  DEF_ROMLOC(1C222) : btst_tomem_8(0x3, 0xFFFFF602); // BTST.B	#$03,$F602
  DEF_ROMLOC(1C228) : if (CCR_EQ) goto rom_1C22E;    // BEQ.B	$1C22E
  DEF_ROMLOC(1C22A) : rom_1C2DE();                   // BSR.W	$1C2DE
  DEF_ROMLOC(1C22E)
      : move_toreg_8(read_8(0xFFFFF602), &D0);     // MOVE.B	$F602,D0
  DEF_ROMLOC(1C232) : and_toreg_8(0xC, &D0);       // ANDI.B	#$0C,D0
  DEF_ROMLOC(1C236) : if (!CCR_EQ) goto rom_1C25E; // BNE.B	$1C25E
  DEF_ROMLOC(1C238)
      : move_toreg_16(read_16(A0 + 0x14), &D0);     // MOVE.W	20(A0),D0
  DEF_ROMLOC(1C23C) : if (CCR_EQ) goto rom_1C25E;   // BEQ.B	$1C25E
  DEF_ROMLOC(1C23E) : if (CCR_MI) goto rom_1C250;   // BMI.B	$1C250
  DEF_ROMLOC(1C240) : sub_toreg_16(0xC, &D0);       // SUBI.W	#$000C,D0
  DEF_ROMLOC(1C244) : if (CCR_CC) goto rom_1C24A;   // BCC.B	$1C24A
  DEF_ROMLOC(1C246) : move_toreg_16(0x0, &D0);      // MOVE.W	#$0000,D0
  DEF_ROMLOC(1C24A) : move_tomem_16(D0, A0 + 0x14); // MOVE.W	D0,20(A0)
  goto rom_1C25E;                                   // BRA.B	$1C25E
  DEF_ROMLOC(1C250) : add_toreg_16(0xC, &D0);       // ADDI.W	#$000C,D0
  DEF_ROMLOC(1C254) : if (CCR_CC) goto rom_1C25A;   // BCC.B	$1C25A
  DEF_ROMLOC(1C256) : move_toreg_16(0x0, &D0);      // MOVE.W	#$0000,D0
  DEF_ROMLOC(1C25A) : move_tomem_16(D0, A0 + 0x14); // MOVE.W	D0,20(A0)
  DEF_ROMLOC(1C25E)
      : move_toreg_8(read_8(0xFFFFF780), &D0);      // MOVE.B	$F780,D0
  DEF_ROMLOC(1C262) : add_toreg_8(0x20, &D0);       // ADDI.B	#$20,D0
  DEF_ROMLOC(1C266) : and_toreg_8(0xFFFFFFC0, &D0); // ANDI.B	#$C0,D0
  DEF_ROMLOC(1C26A) : neg_reg_8(&D0);               // NEG.B	D0
  DEF_ROMLOC(1C26C) : rom_29D2();                   // JSR	$000029D2
  DEF_ROMLOC(1C272)
      : muls_toreg_16(read_16(A0 + 0x14), &D1);   // MULS.W	20(A0),D1
  DEF_ROMLOC(1C276) : add_tomem_32(D1, A0 + 0x8); // ADD.L	D1,8(A0)
  DEF_ROMLOC(1C27A)
      : muls_toreg_16(read_16(A0 + 0x14), &D0);   // MULS.W	20(A0),D0
  DEF_ROMLOC(1C27E) : add_tomem_32(D0, A0 + 0xC); // ADD.L	D0,12(A0)
  DEF_ROMLOC(1C282) : d0backup = D0;
  d1backup = D1;
  // TODO; // MOVEM.L	D0-D1,-(A7)
  DEF_ROMLOC(1C286)
      : move_toreg_32(read_32(A0 + 0xC), &D2); // MOVE.L	12(A0),D2
  DEF_ROMLOC(1C28A)
      : move_toreg_32(read_32(A0 + 0x8), &D3);    // MOVE.L	8(A0),D3
  DEF_ROMLOC(1C28E) : rom_1C49E();                // BSR.W	$1C49E
  DEF_ROMLOC(1C292) : if (CCR_EQ) goto rom_1C2A8; // BEQ.B	$1C2A8
  DEF_ROMLOC(1C294) : D0 = d0backup;
  D1 = d1backup;
  // TODO; // MOVEM.L	(A7)+,D0-D1
  DEF_ROMLOC(1C298) : sub_tomem_32(D1, A0 + 0x8);    // SUB.L	D1,8(A0)
  DEF_ROMLOC(1C29C) : sub_tomem_32(D0, A0 + 0xC);    // SUB.L	D0,12(A0)
  DEF_ROMLOC(1C2A0) : move_tomem_16(0x0, A0 + 0x14); // MOVE.W	#$0000,20(A0)
  DEF_ROMLOC(1C2A6) : return;                        // RTS
  DEF_ROMLOC(1C2A8) : D0 = d0backup;
  D1 = d1backup;
  // TODO; // MOVEM.L	(A7)+,D0-D1
  DEF_ROMLOC(1C2AC) : return; // RTS
}
ROMFUNC(rom_1C2AE) {
  DEF_ROMLOC(1C2AE) : bset_tomem_8(0x0, A0 + 0x22); // BSET.B	#$00,34(A0)
  DEF_ROMLOC(1C2B4)
      : move_toreg_16(read_16(A0 + 0x14), &D0);       // MOVE.W	20(A0),D0
  DEF_ROMLOC(1C2B8) : if (CCR_EQ) goto rom_1C2BC;     // BEQ.B	$1C2BC
  DEF_ROMLOC(1C2BA) : if (CCR_PL) goto rom_1C2D0;     // BPL.B	$1C2D0
  DEF_ROMLOC(1C2BC) : sub_toreg_16(0xC, &D0);         // SUBI.W	#$000C,D0
  DEF_ROMLOC(1C2C0) : cmp_toreg_16(0xFFFFF800, &D0);  // CMPI.W	#$F800,D0
  DEF_ROMLOC(1C2C4) : if (CCR_GT) goto rom_1C2CA;     // BGT.B	$1C2CA
  DEF_ROMLOC(1C2C6) : move_toreg_16(0xFFFFF800, &D0); // MOVE.W	#$F800,D0
  DEF_ROMLOC(1C2CA) : move_tomem_16(D0, A0 + 0x14);   // MOVE.W	D0,20(A0)
  DEF_ROMLOC(1C2CE) : return;                         // RTS
  DEF_ROMLOC(1C2D0) : sub_toreg_16(0x40, &D0);        // SUBI.W	#$0040,D0
  DEF_ROMLOC(1C2D4) : if (CCR_CC) goto rom_1C2D8;     // BCC.B	$1C2D8
  DEF_ROMLOC(1C2D6) : {};                             // NOP
  DEF_ROMLOC(1C2D8) : move_tomem_16(D0, A0 + 0x14);   // MOVE.W	D0,20(A0)
  DEF_ROMLOC(1C2DC) : return;                         // RTS
}
ROMFUNC(rom_1C2DE) {
  DEF_ROMLOC(1C2DE) : bclr_tomem_8(0x0, A0 + 0x22); // BCLR.B	#$00,34(A0)
  DEF_ROMLOC(1C2E4)
      : move_toreg_16(read_16(A0 + 0x14), &D0);     // MOVE.W	20(A0),D0
  DEF_ROMLOC(1C2E8) : if (CCR_MI) goto rom_1C2FE;   // BMI.B	$1C2FE
  DEF_ROMLOC(1C2EA) : add_toreg_16(0xC, &D0);       // ADDI.W	#$000C,D0
  DEF_ROMLOC(1C2EE) : cmp_toreg_16(0x800, &D0);     // CMPI.W	#$0800,D0
  DEF_ROMLOC(1C2F2) : if (CCR_LT) goto rom_1C2F8;   // BLT.B	$1C2F8
  DEF_ROMLOC(1C2F4) : move_toreg_16(0x800, &D0);    // MOVE.W	#$0800,D0
  DEF_ROMLOC(1C2F8) : move_tomem_16(D0, A0 + 0x14); // MOVE.W	D0,20(A0)
  goto rom_1C30A;                                   // BRA.B	$1C30A
  DEF_ROMLOC(1C2FE) : add_toreg_16(0x40, &D0);      // ADDI.W	#$0040,D0
  DEF_ROMLOC(1C302) : if (CCR_CC) goto rom_1C306;   // BCC.B	$1C306
  DEF_ROMLOC(1C304) : {};                           // NOP
  DEF_ROMLOC(1C306) : move_tomem_16(D0, A0 + 0x14); // MOVE.W	D0,20(A0)
  DEF_ROMLOC(1C30A) : return;                       // RTS
}
ROMFUNC(rom_1C30C) {
  DEF_ROMLOC(1C30C)
      : move_toreg_8(read_8(0xFFFFF603), &D0);    // MOVE.B	$F603,D0
  DEF_ROMLOC(1C310) : and_toreg_8(0x70, &D0);     // ANDI.B	#$70,D0
  DEF_ROMLOC(1C314) : if (CCR_EQ) goto rom_1C34E; // BEQ.B	$1C34E
  DEF_ROMLOC(1C316)
      : move_toreg_8(read_8(0xFFFFF780), &D0);      // MOVE.B	$F780,D0
  DEF_ROMLOC(1C31A) : and_toreg_8(0xFFFFFFFC, &D0); // ANDI.B	#$FC,D0
  DEF_ROMLOC(1C31E) : neg_reg_8(&D0);               // NEG.B	D0
  DEF_ROMLOC(1C320) : sub_toreg_8(0x40, &D0);       // SUBI.B	#$40,D0
  DEF_ROMLOC(1C324) : rom_29D2();                   // JSR	$000029D2
  DEF_ROMLOC(1C32A) : muls_toreg_16(0x680, &D1);    // MULS.W	#$0680,D1
  DEF_ROMLOC(1C32E) : asr_toreg_32(0x8, &D1);       // ASR.L	#$08,D1
  DEF_ROMLOC(1C330) : move_tomem_16(D1, A0 + 0x10); // MOVE.W	D1,16(A0)
  DEF_ROMLOC(1C334) : muls_toreg_16(0x680, &D0);    // MULS.W	#$0680,D0
  DEF_ROMLOC(1C338) : asr_toreg_32(0x8, &D0);       // ASR.L	#$08,D0
  DEF_ROMLOC(1C33A) : move_tomem_16(D0, A0 + 0x12); // MOVE.W	D0,18(A0)
  DEF_ROMLOC(1C33E) : bset_tomem_8(0x1, A0 + 0x22); // BSET.B	#$01,34(A0)
  DEF_ROMLOC(1C344) : move_toreg_16(0xA0, &D0);     // MOVE.W	#$00A0,D0
  DEF_ROMLOC(1C348) : rom_1394();                   // JSR	$00001394
  DEF_ROMLOC(1C34E) : return;                       // RTS
}
ROMFUNC(rom_1C350) {
  DEF_ROMLOC(1C350) : return; // RTS
}
ROMFUNC(rom_1C36A) {
  DEF_ROMLOC(1C36A) : return; // RTS
}