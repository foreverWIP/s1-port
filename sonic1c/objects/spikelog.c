// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_8320) {
  u8 switchindex = 0;
  DEF_ROMLOC(8320) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(8322) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(8326)
      : move_toreg_16(read_16(0x832E + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(832A): goto rom_832E + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(832A) : switch (switchindex) {
  case 0:
    rom_8338();
    break;
  case 1:
    rom_83FA();
    break;
  case 2:
    rom_83FA();
    break;
  case 3:
    rom_8468();
    break;
  case 4:
    rom_846E();
    break;
  }
}
ROMFUNC(rom_8338) {
  DEF_ROMLOC(8338) : add_tomem_8(0x2, A0 + 0x24);     // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(833C) : move_tomem_32(0x8476, A0 + 0x4); // MOVE.L	#$00008476,4(A0)
  DEF_ROMLOC(8344) : move_tomem_16(0x4398, A0 + 0x2); // MOVE.W	#$4398,2(A0)
  DEF_ROMLOC(834A) : move_tomem_8(0x7, A0 + 0x22);    // MOVE.B	#$07,34(A0)
  DEF_ROMLOC(8350) : move_tomem_8(0x4, A0 + 0x1);     // MOVE.B	#$04,1(A0)
  DEF_ROMLOC(8356) : move_tomem_8(0x3, A0 + 0x18);    // MOVE.B	#$03,24(A0)
  DEF_ROMLOC(835C) : move_tomem_8(0x8, A0 + 0x19);    // MOVE.B	#$08,25(A0)
  DEF_ROMLOC(8362)
      : move_toreg_16(read_16(A0 + 0xC), &D2); // MOVE.W	12(A0),D2
  DEF_ROMLOC(8366)
      : move_toreg_16(read_16(A0 + 0x8), &D3);            // MOVE.W	8(A0),D3
  DEF_ROMLOC(836A) : move_toreg_8(read_8(A0 + 0x0), &D4); // MOVE.B	0(A0),D4
  DEF_ROMLOC(836E) : move_toreg_32(A0 + 0x28, &A2);       // LEA.L	40(A0),A2
  DEF_ROMLOC(8372) : move_toreg_32(0x0, &D1);             // MOVEQ.L	$00,D1
  DEF_ROMLOC(8374) : move_toreg_8(read_8(A2), &D1);       // MOVE.B	(A2),D1
  DEF_ROMLOC(8376) : move_tomem_8(0x0, A2++);             // MOVE.B	#$00,(A2)+
  DEF_ROMLOC(837A) : move_toreg_16(D1, &D0);              // MOVE.W	D1,D0
  DEF_ROMLOC(837C) : lsr_toreg_16(0x1, &D0);              // LSR.W	#$01,D0
  DEF_ROMLOC(837E) : lsl_toreg_16(0x4, &D0);              // LSL.W	#$04,D0
  DEF_ROMLOC(8380) : sub_toreg_16(D0, &D3);               // SUB.W	D0,D3
  DEF_ROMLOC(8382) : sub_toreg_8(0x2, &D1);               // SUBQ.B	#$02,D1
  DEF_ROMLOC(8384) : if (CCR_CS) {
    rom_83FA();
    return;
  } // BCS.B	$83FA
  DEF_ROMLOC(8386) : move_toreg_32(0x0, &D6); // MOVEQ.L	$00,D6
  DEF_ROMLOC(8388) : rom_E11A();              // BSR.W	$E11A
  DEF_ROMLOC(838C) : if (!CCR_EQ) {
    rom_83FA();
    return;
  } // BNE.B	$83FA
  DEF_ROMLOC(838E) : add_tomem_8(0x1, A0 + 0x28);   // ADDQ.B	#$01,40(A0)
  DEF_ROMLOC(8392) : move_toreg_16(A1, &D5);        // MOVE.W	A1,D5
  DEF_ROMLOC(8394) : sub_toreg_16(0xFFFFD000, &D5); // SUBI.W	#$D000,D5
  DEF_ROMLOC(8398) : lsr_toreg_16(0x6, &D5);        // LSR.W	#$06,D5
  DEF_ROMLOC(839A) : and_toreg_16(0x7F, &D5);       // ANDI.W	#$007F,D5
  DEF_ROMLOC(839E) : move_tomem_8(D5, A2++);        // MOVE.B	D5,(A2)+
  DEF_ROMLOC(83A0) : move_tomem_8(0x8, A1 + 0x24);  // MOVE.B	#$08,36(A1)
  DEF_ROMLOC(83A6) : move_tomem_8(D4, A1 + 0x0);    // MOVE.B	D4,0(A1)
  DEF_ROMLOC(83AA) : move_tomem_16(D2, A1 + 0xC);   // MOVE.W	D2,12(A1)
  DEF_ROMLOC(83AE) : move_tomem_16(D3, A1 + 0x8);   // MOVE.W	D3,8(A1)
  DEF_ROMLOC(83B2)
      : move_tomem_32(read_32(A0 + 0x4), A1 + 0x4);   // MOVE.L	4(A0),4(A1)
  DEF_ROMLOC(83B8) : move_tomem_16(0x4398, A1 + 0x2); // MOVE.W	#$4398,2(A1)
  DEF_ROMLOC(83BE) : move_tomem_8(0x4, A1 + 0x1);     // MOVE.B	#$04,1(A1)
  DEF_ROMLOC(83C4) : move_tomem_8(0x3, A1 + 0x18);    // MOVE.B	#$03,24(A1)
  DEF_ROMLOC(83CA) : move_tomem_8(0x8, A1 + 0x19);    // MOVE.B	#$08,25(A1)
  DEF_ROMLOC(83D0) : move_tomem_8(D6, A1 + 0x3E);     // MOVE.B	D6,62(A1)
  DEF_ROMLOC(83D4) : add_toreg_8(0x1, &D6);           // ADDQ.B	#$01,D6
  DEF_ROMLOC(83D6) : and_toreg_8(0x7, &D6);           // ANDI.B	#$07,D6
  DEF_ROMLOC(83DA) : add_toreg_16(0x10, &D3);         // ADDI.W	#$0010,D3
  DEF_ROMLOC(83DE)
      : cmp_toreg_16(read_16(A0 + 0x8), &D3);     // CMP.W	8(A0),D3
  DEF_ROMLOC(83E2) : if (!CCR_EQ) goto rom_83F6;  // BNE.B	$83F6
  DEF_ROMLOC(83E4) : move_tomem_8(D6, A0 + 0x3E); // MOVE.B	D6,62(A0)
  DEF_ROMLOC(83E8) : add_toreg_8(0x1, &D6);       // ADDQ.B	#$01,D6
  DEF_ROMLOC(83EA) : and_toreg_8(0x7, &D6);       // ANDI.B	#$07,D6
  DEF_ROMLOC(83EE) : add_toreg_16(0x10, &D3);     // ADDI.W	#$0010,D3
  DEF_ROMLOC(83F2) : add_tomem_8(0x1, A0 + 0x28); // ADDQ.B	#$01,40(A0)
  DEF_ROMLOC(83F6) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_8388; // DBF.W	D1,$8388
  rom_83FA();
}
ROMFUNC(rom_83FA) {
  DEF_ROMLOC(83FA) : rom_8406(); // BSR.W	$8406
  DEF_ROMLOC(83FE) : rom_DC92(); // BSR.W	$DC92
  rom_8426();                    // BRA.W	$8426
}
ROMFUNC(rom_8406) {
  DEF_ROMLOC(8406)
      : move_toreg_8(read_8(v_ani0_frame), &D0);   // MOVE.B	$FEC1,D0
  DEF_ROMLOC(840A) : move_tomem_8(0x0, A0 + 0x20); // MOVE.B	#$00,32(A0)
  DEF_ROMLOC(8410)
      : add_toreg_8(read_8(A0 + 0x3E), &D0);      // ADD.B
                                                  // 62(A0),D0
  DEF_ROMLOC(8414) : and_toreg_8(0x7, &D0);       // ANDI.B	#$07,D0
  DEF_ROMLOC(8418) : move_tomem_8(D0, A0 + 0x1A); // MOVE.B	D0,26(A0)
  DEF_ROMLOC(841C) : if (!CCR_EQ) goto rom_8424;  // BNE.B	$8424
  DEF_ROMLOC(841E)
      : move_tomem_8(0xFFFFFF84, A0 + 0x20); // MOVE.B
                                             // #$84,32(A0)
  DEF_ROMLOC(8424) : return;                 // RTS
}
ROMFUNC(rom_8426) {
  DEF_ROMLOC(8426) : move_toreg_16(read_16(A0 + 0x8), &D0); // MOVE.W	8(A0),D0
  DEF_ROMLOC(842A) : and_toreg_16(0xFFFFFF80, &D0);         // ANDI.W	#$FF80,D0
  DEF_ROMLOC(842E)
      : move_toreg_16(read_16(v_screenposx), &D1);    // MOVE.W	$F700,D1
  DEF_ROMLOC(8432) : sub_toreg_16(0x80, &D1);         // SUBI.W	#$0080,D1
  DEF_ROMLOC(8436) : and_toreg_16(0xFFFFFF80, &D1);   // ANDI.W	#$FF80,D1
  DEF_ROMLOC(843A) : sub_toreg_16(D1, &D0);           // SUB.W	D1,D0
  DEF_ROMLOC(843C) : cmp_toreg_16(0x280, &D0);        // CMPI.W	#$0280,D0
  DEF_ROMLOC(8440) : if (CCR_HI) goto rom_8446;       // BHI.W	$8446
  DEF_ROMLOC(8444) : return;                          // RTS
  DEF_ROMLOC(8446) : move_toreg_32(0x0, &D2);         // MOVEQ.L	$00,D2
  DEF_ROMLOC(8448) : move_toreg_32(A0 + 0x28, &A2);   // LEA.L	40(A0),A2
  DEF_ROMLOC(844C) : move_toreg_8(read_8(A2++), &D2); // MOVE.B	(A2)+,D2
  DEF_ROMLOC(844E) : sub_toreg_8(0x2, &D2);           // SUBQ.B	#$02,D2
  DEF_ROMLOC(8450) : if (CCR_CS) {
    rom_8468();
    return;
  } // BCS.B	$8468
  DEF_ROMLOC(8452) : move_toreg_32(0x0, &D0);         // MOVEQ.L	$00,D0
  DEF_ROMLOC(8454) : move_toreg_8(read_8(A2++), &D0); // MOVE.B	(A2)+,D0
  DEF_ROMLOC(8456) : lsl_toreg_16(0x6, &D0);          // LSL.W	#$06,D0
  DEF_ROMLOC(8458) : add_toreg_32(0xFFD000, &D0);     // ADDI.L	#$00FFD000,D0
  DEF_ROMLOC(845E) : move_toreg_32(D0, &A1);          // MOVEA.L	D0,A1
  DEF_ROMLOC(8460) : rom_DCD0();                      // BSR.W	$DCD0
  DEF_ROMLOC(8464) : dec_reg_16(&D2);
  if ((D2 & 0xffff) != 0xffff)
    goto rom_8452; // DBF.W	D2,$8452
  rom_8468();
}
ROMFUNC(rom_8468) {
  DEF_ROMLOC(8468) : rom_DCCE(); // BSR.W	$DCCE
  DEF_ROMLOC(846C) : return;     // RTS
}
ROMFUNC(rom_846E) {
  DEF_ROMLOC(846E) : rom_8406(); // BSR.W	$8406
  DEF_ROMLOC(8472) : {
    rom_DC92();
    return;
  } // BRA.W	$DC92
  DEF_ROMLOC(8476) : or_tomem_8(0x16, A0);        // ORI.B	#$16,(A0)
  DEF_ROMLOC(847A) : or_tomem_8(0x22, A4++);      // ORI.B	#$22,(A4)+
  DEF_ROMLOC(847E) : or_tomem_8(0x2E, A0 + 0x36); // ORI.B	#$2E,54(A0)
  DEF_ROMLOC(8484)
      : or_tomem_8(0xFFFFFFF0,
                   (s32)A4 + (s8)0x0 + (s16)D0); // ORI.B	#$F0,0(A4,D0)
  rom_84B0(); // Detected flow into next function
}