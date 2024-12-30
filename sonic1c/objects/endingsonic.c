// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_53EE) {
  u8 switchindex = 0;
  DEF_ROMLOC(53EE) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(53F0) : move_toreg_8(read_8(A0 + 0x25), &D0);
  switchindex = D0 / 2; // MOVE.B	37(A0),D0
  DEF_ROMLOC(53F4)
      : move_toreg_16(read_16(0x5402 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	12(PC,D0),D1
  // DEF_ROMLOC(53F8): rom_5402 + (s16)(D1 & 0xffff)(); // JSR	8(PC,D1)
  DEF_ROMLOC(53F8) : switch (switchindex) {
  case 0:
    rom_5416();
    break;
  case 1:
    rom_545A();
    break;
  case 2:
    rom_54D8();
    break;
  case 3:
    rom_5472();
    break;
  case 4:
    rom_548E();
    break;
  case 5:
    rom_54D8();
    break;
  case 6:
    rom_54BA();
    break;
  case 7:
    rom_54D8();
    break;
  case 8:
    rom_54E4();
    break;
  case 9:
    rom_54D8();
    break;
  }
  DEF_ROMLOC(53FC) : rom_DC92();
  return; // JMP	$0000DC92
}
ROMFUNC(rom_5416) {
  DEF_ROMLOC(5416) : cmp_tomem_8(0x6, 0xFFFFFE57);   // CMPI.B	#$06,$FE57
  DEF_ROMLOC(541C) : if (CCR_EQ) goto rom_542C;      // BEQ.B	$542C
  DEF_ROMLOC(541E) : add_tomem_8(0x10, A0 + 0x25);   // ADDI.B	#$10,37(A0)
  DEF_ROMLOC(5424) : move_tomem_16(0xD8, A0 + 0x30); // MOVE.W	#$00D8,48(A0)
  DEF_ROMLOC(542A) : return;                         // RTS
  DEF_ROMLOC(542C) : add_tomem_8(0x2, A0 + 0x25);    // ADDQ.B	#$02,37(A0)
  DEF_ROMLOC(5430)
      : move_tomem_32(0x568E, A0 + 0x4);             // MOVE.L	#$0000568E,4(A0)
  DEF_ROMLOC(5438) : move_tomem_16(0x3E1, A0 + 0x2); // MOVE.W	#$03E1,2(A0)
  DEF_ROMLOC(543E) : move_tomem_8(0x4, A0 + 0x1);    // MOVE.B	#$04,1(A0)
  DEF_ROMLOC(5444) : clr_mem_8(A0 + 0x22);           // CLR.B	34(A0)
  DEF_ROMLOC(5448) : move_tomem_8(0x2, A0 + 0x18);   // MOVE.B	#$02,24(A0)
  DEF_ROMLOC(544E) : move_tomem_8(0x0, A0 + 0x1A);   // MOVE.B	#$00,26(A0)
  DEF_ROMLOC(5454) : move_tomem_16(0x50, A0 + 0x30); // MOVE.W	#$0050,48(A0)
  rom_545A(); // Detected flow into next function
}
ROMFUNC(rom_545A) {
  DEF_ROMLOC(545A) : sub_tomem_16(0x1, A0 + 0x30);  // SUBQ.W	#$01,48(A0)
  DEF_ROMLOC(545E) : if (!CCR_EQ) goto rom_5470;    // BNE.B	$5470
  DEF_ROMLOC(5460) : add_tomem_8(0x2, A0 + 0x25);   // ADDQ.B	#$02,37(A0)
  DEF_ROMLOC(5464) : move_tomem_16(0x1, A0 + 0x1C); // MOVE.W	#$0001,28(A0)
  DEF_ROMLOC(546A)
      : move_tomem_8(0xFFFFFF88, 0xFFFFD400); // MOVE.B	#$88,$D400
  DEF_ROMLOC(5470) : return;                  // RTS
}
ROMFUNC(rom_5472) {
  DEF_ROMLOC(5472)
      : cmp_tomem_16(0x2000, 0xFFD43C);              // CMPI.W	#$2000,$00FFD43C
  DEF_ROMLOC(547A) : if (!CCR_EQ) goto rom_548C;     // BNE.B	$548C
  DEF_ROMLOC(547C) : move_tomem_16(0x1, 0xFFFFFE02); // MOVE.W	#$0001,$FE02
  DEF_ROMLOC(5482) : move_tomem_16(0x5A, A0 + 0x30); // MOVE.W	#$005A,48(A0)
  DEF_ROMLOC(5488) : add_tomem_8(0x2, A0 + 0x25);    // ADDQ.B	#$02,37(A0)
  DEF_ROMLOC(548C) : return;                         // RTS
}
ROMFUNC(rom_548E) {
  DEF_ROMLOC(548E) : sub_tomem_16(0x1, A0 + 0x30);   // SUBQ.W	#$01,48(A0)
  DEF_ROMLOC(5492) : if (!CCR_EQ) goto rom_54B8;     // BNE.B	$54B8
  DEF_ROMLOC(5494) : move_toreg_32(0xFFFFD400, &A1); // LEA.L	$D400,A1
  DEF_ROMLOC(5498) : move_toreg_16(0xFF, &D1);       // MOVE.W	#$00FF,D1
  DEF_ROMLOC(549C) : clr_mem_32((A1 += 4, A1 - 4));  // CLR.L	(A1)+
  DEF_ROMLOC(549E) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_549C;                                   // DBF.W	D1,$549C
  DEF_ROMLOC(54A2) : move_tomem_16(0x1, 0xFFFFFE02); // MOVE.W	#$0001,$FE02
  DEF_ROMLOC(54A8) : add_tomem_8(0x2, A0 + 0x25);    // ADDQ.B	#$02,37(A0)
  DEF_ROMLOC(54AC) : move_tomem_8(0x1, A0 + 0x1C);   // MOVE.B	#$01,28(A0)
  DEF_ROMLOC(54B2) : move_tomem_16(0x3C, A0 + 0x30); // MOVE.W	#$003C,48(A0)
  DEF_ROMLOC(54B8) : return;                         // RTS
}
ROMFUNC(rom_54BA) {
  DEF_ROMLOC(54BA) : sub_tomem_16(0x1, A0 + 0x30);   // SUBQ.W	#$01,48(A0)
  DEF_ROMLOC(54BE) : if (!CCR_EQ) goto rom_54D6;     // BNE.B	$54D6
  DEF_ROMLOC(54C0) : add_tomem_8(0x2, A0 + 0x25);    // ADDQ.B	#$02,37(A0)
  DEF_ROMLOC(54C4) : move_tomem_16(0xB4, A0 + 0x30); // MOVE.W	#$00B4,48(A0)
  DEF_ROMLOC(54CA) : move_tomem_8(0x2, A0 + 0x1C);   // MOVE.B	#$02,28(A0)
  DEF_ROMLOC(54D0)
      : move_tomem_8(0xFFFFFF89, 0xFFFFD400); // MOVE.B	#$89,$D400
  DEF_ROMLOC(54D6) : return;                  // RTS
}
ROMFUNC(rom_54D8) {
  DEF_ROMLOC(54D8) : move_toreg_32(0x5522, &A1); // LEA.L	$00005522,A1
  DEF_ROMLOC(54DE) : rom_ADA2();
  return; // JMP	$0000ADA2
}
ROMFUNC(rom_54E4) {
  DEF_ROMLOC(54E4) : sub_tomem_16(0x1, A0 + 0x30); // SUBQ.W	#$01,48(A0)
  DEF_ROMLOC(54E8) : if (!CCR_EQ) goto rom_5520;   // BNE.B	$5520
  DEF_ROMLOC(54EA) : add_tomem_8(0x2, A0 + 0x25);  // ADDQ.B	#$02,37(A0)
  DEF_ROMLOC(54EE)
      : move_tomem_32(0x568E, A0 + 0x4);             // MOVE.L	#$0000568E,4(A0)
  DEF_ROMLOC(54F6) : move_tomem_16(0x3E1, A0 + 0x2); // MOVE.W	#$03E1,2(A0)
  DEF_ROMLOC(54FC) : move_tomem_8(0x4, A0 + 0x1);    // MOVE.B	#$04,1(A0)
  DEF_ROMLOC(5502) : clr_mem_8(A0 + 0x22);           // CLR.B	34(A0)
  DEF_ROMLOC(5506) : move_tomem_8(0x2, A0 + 0x18);   // MOVE.B	#$02,24(A0)
  DEF_ROMLOC(550C) : move_tomem_8(0x5, A0 + 0x1A);   // MOVE.B	#$05,26(A0)
  DEF_ROMLOC(5512) : move_tomem_8(0x2, A0 + 0x1C);   // MOVE.B	#$02,28(A0)
  DEF_ROMLOC(5518)
      : move_tomem_8(0xFFFFFF89, 0xFFFFD400); // MOVE.B	#$89,$D400
  rom_54D8();
  return;                    // BRA.B	$54D8
  DEF_ROMLOC(5520) : return; // RTS
}