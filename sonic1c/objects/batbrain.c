// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_10882);
ROMFUNC(rom_10734) {
  u8 switchindex = 0;
  DEF_ROMLOC(10734) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(10736) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(1073A)
      : move_toreg_16(read_16(0x10742 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(1073E): goto rom_10742 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(1073E) : switch (switchindex) {
  case 0:
    rom_10746();
    break;
  case 1:
    rom_10776();
    break;
  }
}
ROMFUNC(rom_10746) {
  DEF_ROMLOC(10746) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(1074A)
      : move_tomem_32(0x108CA, A0 + 0x4); // MOVE.L	#$000108CA,4(A0)
  DEF_ROMLOC(10752)
      : move_tomem_16(0xFFFF84B8, A0 + 0x2);         // MOVE.W	#$84B8,2(A0)
  DEF_ROMLOC(10758) : move_tomem_8(0x4, A0 + 0x1);   // MOVE.B	#$04,1(A0)
  DEF_ROMLOC(1075E) : move_tomem_8(0xC, A0 + 0x16);  // MOVE.B	#$0C,22(A0)
  DEF_ROMLOC(10764) : move_tomem_8(0x2, A0 + 0x18);  // MOVE.B	#$02,24(A0)
  DEF_ROMLOC(1076A) : move_tomem_8(0xB, A0 + 0x20);  // MOVE.B	#$0B,32(A0)
  DEF_ROMLOC(10770) : move_tomem_8(0x10, A0 + 0x19); // MOVE.B	#$10,25(A0)
  rom_10776(); // Detected flow into next function
}
ROMFUNC(rom_1079A);
ROMFUNC(rom_107D6);
ROMFUNC(rom_10818);
ROMFUNC(rom_10854);
ROMFUNC(rom_10776) {
  u8 switchindex = 0;
  DEF_ROMLOC(10776) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(10778) : move_toreg_8(read_8(A0 + 0x25), &D0);
  switchindex = D0 / 2; // MOVE.B	37(A0),D0
  DEF_ROMLOC(1077C)
      : move_toreg_16(read_16(0x10792 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	20(PC,D0),D1
  // DEF_ROMLOC(10780): rom_10792 + (s16)(D1 & 0xffff)(); // JSR
  // 16(PC,D1)
  DEF_ROMLOC(10780) : switch (switchindex) {
  case 0:
    rom_1079A();
    break;
  case 1:
    rom_107D6();
    break;
  case 2:
    rom_10818();
    break;
  case 3:
    rom_10854();
    break;
  }
  DEF_ROMLOC(10784) : move_toreg_32(0x108B6, &A1); // LEA.L	$000108B6,A1
  DEF_ROMLOC(1078A) : animate_sprite();                  // BSR.W	$ADA2
  DEF_ROMLOC(1078E) : rom_FD38();
  return; // BRA.W	$FD38
}
ROMFUNC(rom_1079A) {
  DEF_ROMLOC(1079A) : move_toreg_16(0x80, &D2);   // MOVE.W	#$0080,D2
  DEF_ROMLOC(1079E) : rom_10882();                // BSR.W	$10882
  DEF_ROMLOC(107A2) : if (CCR_CC) goto rom_107D4; // BCC.B	$107D4
  DEF_ROMLOC(107A4)
      : move_toreg_16(read_16(0xFFFFD00C), &D0);    // MOVE.W	$D00C,D0
  DEF_ROMLOC(107A8) : move_tomem_16(D0, A0 + 0x36); // MOVE.W	D0,54(A0)
  DEF_ROMLOC(107AC)
      : sub_toreg_16(read_16(A0 + 0xC), &D0);      // SUB.W	12(A0),D0
  DEF_ROMLOC(107B0) : if (CCR_CS) goto rom_107D4;  // BCS.B	$107D4
  DEF_ROMLOC(107B2) : cmp_toreg_16(0x80, &D0);     // CMPI.W	#$0080,D0
  DEF_ROMLOC(107B6) : if (CCR_CC) goto rom_107D4;  // BCC.B	$107D4
  DEF_ROMLOC(107B8) : tst_mem_16(0xFFFFFE08);      // TST.W	$FE08
  DEF_ROMLOC(107BC) : if (!CCR_EQ) goto rom_107D4; // BNE.B	$107D4
  DEF_ROMLOC(107BE)
      : move_toreg_8(read_8(0xFFFFFE0F), &D0);      // MOVE.B	$FE0F,D0
  DEF_ROMLOC(107C2) : add_toreg_8(D7, &D0);         // ADD.B	D7,D0
  DEF_ROMLOC(107C4) : and_toreg_8(0x7, &D0);        // ANDI.B	#$07,D0
  DEF_ROMLOC(107C8) : if (!CCR_EQ) goto rom_107D4;  // BNE.B	$107D4
  DEF_ROMLOC(107CA) : move_tomem_8(0x1, A0 + 0x1C); // MOVE.B	#$01,28(A0)
  DEF_ROMLOC(107D0) : add_tomem_8(0x2, A0 + 0x25);  // ADDQ.B	#$02,37(A0)
  DEF_ROMLOC(107D4) : return;                       // RTS
}
ROMFUNC(rom_107D6) {
  DEF_ROMLOC(107D6) : rom_DC6C();                    // BSR.W	$DC6C
  DEF_ROMLOC(107DA) : add_tomem_16(0x18, A0 + 0x12); // ADDI.W	#$0018,18(A0)
  DEF_ROMLOC(107E0) : move_toreg_16(0x80, &D2);      // MOVE.W	#$0080,D2
  DEF_ROMLOC(107E4) : rom_10882();                   // BSR.W	$10882
  DEF_ROMLOC(107E8)
      : move_toreg_16(read_16(A0 + 0x36), &D0);             // MOVE.W	54(A0),D0
  DEF_ROMLOC(107EC) : sub_toreg_16(read_16(A0 + 0xC), &D0); // SUB.W
                                                            // 12(A0),D0
  DEF_ROMLOC(107F0) : if (CCR_CS) goto rom_1080E;           // BCS.B	$1080E
  DEF_ROMLOC(107F2) : cmp_toreg_16(0x10, &D0);              // CMPI.W	#$0010,D0
  DEF_ROMLOC(107F6) : if (CCR_CC) goto rom_1080C;           // BCC.B	$1080C
  DEF_ROMLOC(107F8) : move_tomem_16(D1, A0 + 0x10);         // MOVE.W	D1,16(A0)
  DEF_ROMLOC(107FC) : move_tomem_16(0x0, A0 + 0x12); // MOVE.W	#$0000,18(A0)
  DEF_ROMLOC(10802) : move_tomem_8(0x2, A0 + 0x1C);  // MOVE.B	#$02,28(A0)
  DEF_ROMLOC(10808) : add_tomem_8(0x2, A0 + 0x25);   // ADDQ.B	#$02,37(A0)
  DEF_ROMLOC(1080C) : return;                        // RTS
  DEF_ROMLOC(1080E) : tst_mem_8(A0 + 0x1);           // TST.B	1(A0)
  DEF_ROMLOC(10812) : if (CCR_PL) {
    rom_DCCE();
    return;
  }                           // BPL.W	$DCCE
  DEF_ROMLOC(10816) : return; // RTS
}
ROMFUNC(rom_10818) {
  DEF_ROMLOC(10818)
      : move_toreg_8(read_8(0xFFFFFE0F), &D0);     // MOVE.B	$FE0F,D0
  DEF_ROMLOC(1081C) : and_toreg_8(0xF, &D0);       // ANDI.B	#$0F,D0
  DEF_ROMLOC(10820) : if (!CCR_EQ) goto rom_1082C; // BNE.B	$1082C
  DEF_ROMLOC(10822) : move_toreg_16(0xC0, &D0);    // MOVE.W	#$00C0,D0
  DEF_ROMLOC(10826) : play_sound_special();        // JSR	$00001394
  DEF_ROMLOC(1082C) : rom_DC6C();                  // BSR.W	$DC6C
  DEF_ROMLOC(10830)
      : move_toreg_16(read_16(0xFFFFD008), &D0); // MOVE.W	$D008,D0
  DEF_ROMLOC(10834)
      : sub_toreg_16(read_16(A0 + 0x8), &D0);     // SUB.W	8(A0),D0
  DEF_ROMLOC(10838) : if (CCR_CC) goto rom_1083C; // BCC.B	$1083C
  DEF_ROMLOC(1083A) : neg_reg_16(&D0);            // NEG.W	D0
  DEF_ROMLOC(1083C) : cmp_toreg_16(0x80, &D0);    // CMPI.W	#$0080,D0
  DEF_ROMLOC(10840) : if (CCR_CS) goto rom_10852; // BCS.B	$10852
  DEF_ROMLOC(10842)
      : move_toreg_8(read_8(0xFFFFFE0F), &D0);     // MOVE.B	$FE0F,D0
  DEF_ROMLOC(10846) : add_toreg_8(D7, &D0);        // ADD.B	D7,D0
  DEF_ROMLOC(10848) : and_toreg_8(0x7, &D0);       // ANDI.B	#$07,D0
  DEF_ROMLOC(1084C) : if (!CCR_EQ) goto rom_10852; // BNE.B	$10852
  DEF_ROMLOC(1084E) : add_tomem_8(0x2, A0 + 0x25); // ADDQ.B	#$02,37(A0)
  DEF_ROMLOC(10852) : return;                      // RTS
}
ROMFUNC(rom_10854) {
  DEF_ROMLOC(10854) : rom_DC6C();                    // BSR.W	$DC6C
  DEF_ROMLOC(10858) : sub_tomem_16(0x18, A0 + 0x12); // SUBI.W	#$0018,18(A0)
  DEF_ROMLOC(1085E) : rom_15706();                   // BSR.W	$15706
  DEF_ROMLOC(10862) : tst_reg_16(&D1);               // TST.W	D1
  DEF_ROMLOC(10864) : if (CCR_PL) goto rom_10880;    // BPL.B	$10880
  DEF_ROMLOC(10866) : sub_tomem_16(D1, A0 + 0xC);    // SUB.W	D1,12(A0)
  DEF_ROMLOC(1086A)
      : and_tomem_16(0xFFFFFFF8, A0 + 0x8);  // ANDI.W	#$FFF8,8(A0)
  DEF_ROMLOC(10870) : clr_mem_16(A0 + 0x10); // CLR.W	16(A0)
  DEF_ROMLOC(10874) : clr_mem_16(A0 + 0x12); // CLR.W	18(A0)
  DEF_ROMLOC(10878) : clr_mem_8(A0 + 0x1C);  // CLR.B	28(A0)
  DEF_ROMLOC(1087C) : clr_mem_8(A0 + 0x25);  // CLR.B	37(A0)
  DEF_ROMLOC(10880) : return;                // RTS
}
ROMFUNC(rom_10882) {
  DEF_ROMLOC(10882) : move_toreg_16(0x100, &D1);    // MOVE.W	#$0100,D1
  DEF_ROMLOC(10886) : bset_tomem_8(0x0, A0 + 0x22); // BSET.B	#$00,34(A0)
  DEF_ROMLOC(1088C)
      : move_toreg_16(read_16(0xFFFFD008), &D0);            // MOVE.W	$D008,D0
  DEF_ROMLOC(10890) : sub_toreg_16(read_16(A0 + 0x8), &D0); // SUB.W	8(A0),D0
  DEF_ROMLOC(10894) : if (CCR_CC) goto rom_108A0;           // BCC.B	$108A0
  DEF_ROMLOC(10896) : neg_reg_16(&D0);                      // NEG.W	D0
  DEF_ROMLOC(10898) : neg_reg_16(&D1);                      // NEG.W	D1
  DEF_ROMLOC(1089A) : bclr_tomem_8(0x0, A0 + 0x22); // BCLR.B	#$00,34(A0)
  DEF_ROMLOC(108A0) : cmp_toreg_16(D2, &D0);        // CMP.W	D2,D0
  DEF_ROMLOC(108A2) : return;                       // RTS
}