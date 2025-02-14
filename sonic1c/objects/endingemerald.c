// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

static bool return_early = false;

ROMFUNC(rom_5548) {
  u8 switchindex = 0;
  return_early = false;
  DEF_ROMLOC(5548) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(554A) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(554E)
      : move_toreg_16(read_16(0x555C + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	12(PC,D0),D1
  // DEF_ROMLOC(5552): rom_555C + (s16)(D1 & 0xffff)(); // JSR	8(PC,D1)
  DEF_ROMLOC(5552) : switch (switchindex) {
  case 0:
    rom_5560();
    break;
  case 1:
    rom_55C8();
    break;
  }
  if (return_early)
    return;
  DEF_ROMLOC(5556) : rom_DC92(); // JMP	$0000DC92
}
ROMFUNC(rom_5560) {
  DEF_ROMLOC(5560) : cmp_tomem_8(0x2, 0xFFFFD01A); // CMPI.B	#$02,$D01A
  DEF_ROMLOC(5566) : if (CCR_EQ) goto rom_556C;    // BEQ.B	$556C
  DEF_ROMLOC(5568) : return_early = true;          // TODO; // ADDQ.L	#$04,A7
  DEF_ROMLOC(556A) : return;                       // RTS
  DEF_ROMLOC(556C)
      : move_tomem_16(read_16(0xFFFFD008), A0 + 0x8); // MOVE.W	$D008,8(A0)
  DEF_ROMLOC(5572)
      : move_tomem_16(read_16(0xFFFFD00C), A0 + 0xC); // MOVE.W	$D00C,12(A0)
  DEF_ROMLOC(5578) : move_toreg_32(A0, &A1);          // MOVEA.L	A0,A1
  DEF_ROMLOC(557A) : move_toreg_32(0x0, &D3);         // MOVEQ.L	$00,D3
  DEF_ROMLOC(557C) : move_toreg_32(0x1, &D2);         // MOVEQ.L	$01,D2
  DEF_ROMLOC(557E) : move_toreg_32(0x5, &D1);         // MOVEQ.L	$05,D1
  rom_5580(); // Detected flow into next function
}
ROMFUNC(rom_5580) {
  DEF_ROMLOC(5580) : move_tomem_8(OBJ_ENDCHAOS, A1 + offsetof(object, id)); // MOVE.B	#$88,(A1)
  DEF_ROMLOC(5584) : add_tomem_8(0x2, A1 + 0x24);  // ADDQ.B	#$02,36(A1)
  DEF_ROMLOC(5588)
      : move_tomem_32(0x5788, A1 + 0x4);             // MOVE.L	#$00005788,4(A1)
  DEF_ROMLOC(5590) : move_tomem_16(0x3C5, A1 + 0x2); // MOVE.W	#$03C5,2(A1)
  DEF_ROMLOC(5596) : move_tomem_8(0x4, A1 + 0x1);    // MOVE.B	#$04,1(A1)
  DEF_ROMLOC(559C) : move_tomem_8(0x1, A1 + 0x18);   // MOVE.B	#$01,24(A1)
  DEF_ROMLOC(55A2)
      : move_tomem_16(read_16(A0 + 0x8), A1 + 0x38); // MOVE.W	8(A0),56(A1)
  DEF_ROMLOC(55A8)
      : move_tomem_16(read_16(A0 + 0xC), A1 + 0x3A); // MOVE.W	12(A0),58(A1)
  DEF_ROMLOC(55AE) : move_tomem_8(D2, A1 + 0x1C);    // MOVE.B	D2,28(A1)
  DEF_ROMLOC(55B2) : move_tomem_8(D2, A1 + 0x1A);    // MOVE.B	D2,26(A1)
  DEF_ROMLOC(55B6) : add_toreg_8(0x1, &D2);          // ADDQ.B	#$01,D2
  DEF_ROMLOC(55B8) : move_tomem_8(D3, A1 + 0x26);    // MOVE.B	D3,38(A1)
  DEF_ROMLOC(55BC) : add_toreg_8(0x2A, &D3);         // ADDI.B	#$2A,D3
  DEF_ROMLOC(55C0) : move_toreg_32(A1 + 0x40, &A1);  // LEA.L	64(A1),A1
  DEF_ROMLOC(55C4) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_5580; // DBF.W	D1,$5580
  rom_55C8();      // Detected flow into next function
}
ROMFUNC(rom_55C8) {
  DEF_ROMLOC(55C8)
      : move_toreg_16(read_16(A0 + 0x3E), &D0);   // MOVE.W	62(A0),D0
  DEF_ROMLOC(55CC) : add_tomem_16(D0, A0 + 0x26); // ADD.W	D0,38(A0)
  DEF_ROMLOC(55D0)
      : move_toreg_8(read_8(A0 + 0x26), &D0); // MOVE.B	38(A0),D0
  DEF_ROMLOC(55D4) : rom_29D2();              // JSR	$000029D2
  DEF_ROMLOC(55DA) : move_toreg_32(0x0, &D4); // MOVEQ.L	$00,D4
  DEF_ROMLOC(55DC)
      : move_toreg_8(read_8(A0 + 0x3C), &D4); // MOVE.B	60(A0),D4
  DEF_ROMLOC(55E0) : muls_toreg_16(D4, &D1);  // MULS.W	D4,D1
  DEF_ROMLOC(55E2) : asr_toreg_32(0x8, &D1);  // ASR.L	#$08,D1
  DEF_ROMLOC(55E4) : muls_toreg_16(D4, &D0);  // MULS.W	D4,D0
  DEF_ROMLOC(55E6) : asr_toreg_32(0x8, &D0);  // ASR.L	#$08,D0
  DEF_ROMLOC(55E8)
      : add_toreg_16(read_16(A0 + 0x38), &D1); // ADD.W	56(A0),D1
  DEF_ROMLOC(55EC)
      : add_toreg_16(read_16(A0 + 0x3A), &D0);    // ADD.W	58(A0),D0
  DEF_ROMLOC(55F0) : move_tomem_16(D1, A0 + 0x8); // MOVE.W	D1,8(A0)
  DEF_ROMLOC(55F4) : move_tomem_16(D0, A0 + 0xC); // MOVE.W	D0,12(A0)
  rom_55F8(); // Detected flow into next function
}
ROMFUNC(rom_55F8) {
  DEF_ROMLOC(55F8) : cmp_tomem_16(0x2000, A0 + 0x3C); // CMPI.W	#$2000,60(A0)
  DEF_ROMLOC(55FE) : if (CCR_EQ) goto rom_5606;       // BEQ.B	$5606
  DEF_ROMLOC(5600) : add_tomem_16(0x20, A0 + 0x3C);   // ADDI.W	#$0020,60(A0)
  DEF_ROMLOC(5606) : cmp_tomem_16(0x2000, A0 + 0x3E); // CMPI.W	#$2000,62(A0)
  DEF_ROMLOC(560C) : if (CCR_EQ) goto rom_5614;       // BEQ.B	$5614
  DEF_ROMLOC(560E) : add_tomem_16(0x20, A0 + 0x3E);   // ADDI.W	#$0020,62(A0)
  DEF_ROMLOC(5614) : cmp_tomem_16(0x140, A0 + 0x3A);  // CMPI.W	#$0140,58(A0)
  DEF_ROMLOC(561A) : if (CCR_EQ) goto rom_5620;       // BEQ.B	$5620
  DEF_ROMLOC(561C) : sub_tomem_16(0x1, A0 + 0x3A);    // SUBQ.W	#$01,58(A0)
  DEF_ROMLOC(5620) : return;                          // RTS
}