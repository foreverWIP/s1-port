// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_B866) {
  u8 switchindex = 0;
  DEF_ROMLOC(B866) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(B868) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(B86C)
      : move_toreg_16(read_16(0xB874 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(B870): goto rom_B874 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(B870) : switch (switchindex) {
  case 0:
    rom_B87A();
    break;
  case 1:
    rom_B8C2();
    break;
  case 2:
    rom_B93C();
    break;
  }
}
ROMFUNC(rom_B87A) {
  DEF_ROMLOC(B87A) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(B87E)
      : move_tomem_32(0xB9F8, A0 + 0x4);             // MOVE.L	#$0000B9F8,4(A0)
  DEF_ROMLOC(B886) : move_tomem_16(0x345, A0 + 0x2); // MOVE.W	#$0345,2(A0)
  DEF_ROMLOC(B88C)
      : move_tomem_16(read_16(A0 + 0x8), A0 + 0x2A); // MOVE.W	8(A0),42(A0)
  DEF_ROMLOC(B892) : move_tomem_8(0x4, A0 + 0x1);    // MOVE.B	#$04,1(A0)
  DEF_ROMLOC(B898) : move_tomem_8(0x1, A0 + 0x18);   // MOVE.B	#$01,24(A0)
  DEF_ROMLOC(B89E)
      : move_tomem_8(0xFFFFFF8B, A0 + 0x20);       // MOVE.B	#$8B,32(A0)
  DEF_ROMLOC(B8A4) : move_tomem_8(0x8, A0 + 0x19); // MOVE.B	#$08,25(A0)
  DEF_ROMLOC(B8AA) : move_toreg_16(SFX_BURNING, &D0);     // MOVE.W	#$00C8,D0
  DEF_ROMLOC(B8AE) : play_sound_special();         // JSR	$00001394
  DEF_ROMLOC(B8B4) : tst_mem_8(A0 + 0x28);         // TST.B	40(A0)
  DEF_ROMLOC(B8B8) : if (CCR_EQ) {
    rom_B8C2();
    return;
  }                                               // BEQ.B	$B8C2
  DEF_ROMLOC(B8BA) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  rom_B93C();                                     // BRA.W	$B93C
}
ROMFUNC(rom_B8C2) {
  DEF_ROMLOC(B8C2)
      : move_toreg_32(read_32(A0 + 0x30), &A1); // MOVEA.L	48(A0),A1
  DEF_ROMLOC(B8C6)
      : move_toreg_16(read_16(A0 + 0x8), &D1);              // MOVE.W	8(A0),D1
  DEF_ROMLOC(B8CA) : sub_toreg_16(read_16(A0 + 0x2A), &D1); // SUB.W
                                                            // 42(A0),D1
  DEF_ROMLOC(B8CE) : add_toreg_16(0xC, &D1);                // ADDI.W	#$000C,D1
  DEF_ROMLOC(B8D2) : move_toreg_16(D1, &D0);                // MOVE.W	D1,D0
  DEF_ROMLOC(B8D4) : lsr_toreg_16(0x1, &D0);                // LSR.W	#$01,D0
  DEF_ROMLOC(B8D6)
      : move_toreg_8(read_8((s32)A1 + (s8)0x0 + (s16)D0),
                     &D0);            // MOVE.B	0(A1,D0),D0
  DEF_ROMLOC(B8DA) : neg_reg_16(&D0); // NEG.W	D0
  DEF_ROMLOC(B8DC) : add_toreg_16(read_16(A0 + 0x2C), &D0); // ADD.W
                                                            // 44(A0),D0
  DEF_ROMLOC(B8E0) : move_toreg_16(D0, &D2);                // MOVE.W	D0,D2
  DEF_ROMLOC(B8E2)
      : add_toreg_16(read_16(A0 + 0x3C), &D0);    // ADD.W	60(A0),D0
  DEF_ROMLOC(B8E6) : move_tomem_16(D0, A0 + 0xC); // MOVE.W	D0,12(A0)
  DEF_ROMLOC(B8EA) : cmp_toreg_16(0x84, &D1);     // CMPI.W	#$0084,D1
  DEF_ROMLOC(B8EE) : if (CCR_CC) goto rom_B93A;   // BCC.B	$B93A
  DEF_ROMLOC(B8F0)
      : add_tomem_32(0x10000, A0 + 0x8);        // ADDI.L	#$00010000,8(A0)
  DEF_ROMLOC(B8F8) : cmp_toreg_16(0x80, &D1);   // CMPI.W	#$0080,D1
  DEF_ROMLOC(B8FC) : if (CCR_CC) goto rom_B93A; // BCC.B	$B93A
  DEF_ROMLOC(B8FE)
      : move_toreg_32(read_32(A0 + 0x8), &D0);     // MOVE.L	8(A0),D0
  DEF_ROMLOC(B902) : add_toreg_32(0x80000, &D0);   // ADDI.L	#$00080000,D0
  DEF_ROMLOC(B908) : and_toreg_32(0xFFFFF, &D0);   // ANDI.L	#$000FFFFF,D0
  DEF_ROMLOC(B90E) : if (!CCR_EQ) goto rom_B93A;   // BNE.B	$B93A
  DEF_ROMLOC(B910) : rom_E130();                   // BSR.W	$E130
  DEF_ROMLOC(B914) : if (!CCR_EQ) goto rom_B93A;   // BNE.B	$B93A
  DEF_ROMLOC(B916) : move_tomem_8(0x35, A1 + 0x0); // MOVE.B	#$35,0(A1)
  DEF_ROMLOC(B91C)
      : move_tomem_16(read_16(A0 + 0x8), A1 + 0x8); // MOVE.W	8(A0),8(A1)
  DEF_ROMLOC(B922) : move_tomem_16(D2, A1 + 0x2C);  // MOVE.W	D2,44(A1)
  DEF_ROMLOC(B926)
      : move_tomem_16(read_16(A0 + 0x3C), A1 + 0x3C); // MOVE.W	60(A0),60(A1)
  DEF_ROMLOC(B92C) : move_tomem_8(0x1, A1 + 0x28);    // MOVE.B	#$01,40(A1)
  DEF_ROMLOC(B932)
      : move_toreg_32(read_32(A0 + 0x38), &A2); // MOVEA.L	56(A0),A2
  DEF_ROMLOC(B936) : rom_B726();                // BSR.W	$B726
  DEF_ROMLOC(B93A) : rom_B948();                // BRA.B	$B948
}
ROMFUNC(rom_B93C) {
  DEF_ROMLOC(B93C)
      : move_toreg_16(read_16(A0 + 0x2C), &D0); // MOVE.W	44(A0),D0
  DEF_ROMLOC(B940)
      : add_toreg_16(read_16(A0 + 0x3C), &D0);    // ADD.W	60(A0),D0
  DEF_ROMLOC(B944) : move_tomem_16(D0, A0 + 0xC); // MOVE.W	D0,12(A0)
  rom_B948(); // Detected flow into next function
}
ROMFUNC(rom_B948) {
  DEF_ROMLOC(B948) : move_toreg_32(0xB956, &A1); // LEA.L	$0000B956,A1
  DEF_ROMLOC(B94E) : animate_sprite();                 // BSR.W	$ADA2
  DEF_ROMLOC(B952) : rom_DC92();
  return;                                    // BRA.W	$DC92
  DEF_ROMLOC(B956) : or_toreg_8(0x0, &D2);   // ORI.B	#$00,D2
  DEF_ROMLOC(B95A) : move_toreg_32(D1, &D0); // MOVE.L	D1,D0
  rom_BA28();                                // Detected flow into next function
}