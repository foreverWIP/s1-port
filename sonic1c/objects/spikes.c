// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_D4B6) {
  u8 switchindex = 0;
  DEF_ROMLOC(D4B6) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(D4B8) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(D4BC)
      : move_toreg_16(read_16(0xD4C4 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(D4C0): goto rom_D4C4 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(D4C0) : switch (switchindex) {
  case 0:
    rom_D4D4();
    break;
  case 1:
    rom_D51E();
    break;
  }
}
ROMFUNC(rom_D4D4) {
  DEF_ROMLOC(D4D4) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(D4D8)
      : move_tomem_32(0xD676, A0 + 0x4);             // MOVE.L	#$0000D676,4(A0)
  DEF_ROMLOC(D4E0) : move_tomem_16(0x51B, A0 + 0x2); // MOVE.W	#$051B,2(A0)
  DEF_ROMLOC(D4E6) : or_tomem_8(0x4, A0 + 0x1);      // ORI.B	#$04,1(A0)
  DEF_ROMLOC(D4EC) : move_tomem_8(0x4, A0 + 0x18);   // MOVE.B	#$04,24(A0)
  DEF_ROMLOC(D4F2)
      : move_toreg_8(read_8(A0 + 0x28), &D0);     // MOVE.B	40(A0),D0
  DEF_ROMLOC(D4F6) : and_tomem_8(0xF, A0 + 0x28); // ANDI.B	#$0F,40(A0)
  DEF_ROMLOC(D4FC) : and_toreg_16(0xF0, &D0);     // ANDI.W	#$00F0,D0
  DEF_ROMLOC(D500) : move_toreg_32(0xD4C8, &A1);  // LEA.L	$0000D4C8,A1
  DEF_ROMLOC(D506) : lsr_toreg_16(0x3, &D0);      // LSR.W	#$03,D0
  DEF_ROMLOC(D508) : add_toreg_16(D0, &A1);       // ADDA.W	D0,A1
  DEF_ROMLOC(D50A)
      : move_tomem_8(read_8(A1++), A0 + 0x1A); // MOVE.B	(A1)+,26(A0)
  DEF_ROMLOC(D50E)
      : move_tomem_8(read_8(A1++), A0 + 0x19); // MOVE.B	(A1)+,25(A0)
  DEF_ROMLOC(D512)
      : move_tomem_16(read_16(A0 + 0x8), A0 + 0x30); // MOVE.W	8(A0),48(A0)
  DEF_ROMLOC(D518)
      : move_tomem_16(read_16(A0 + 0xC), A0 + 0x32); // MOVE.W	12(A0),50(A0)
  rom_D51E(); // Detected flow into next function
}
ROMFUNC(rom_D51E) {
  DEF_ROMLOC(D51E) : rom_D5D4();                  // BSR.W	$D5D4
  DEF_ROMLOC(D522) : move_toreg_16(0x4, &D2);     // MOVE.W	#$0004,D2
  DEF_ROMLOC(D526) : cmp_tomem_8(0x5, A0 + 0x1A); // CMPI.B	#$05,26(A0)
  DEF_ROMLOC(D52C) : if (CCR_EQ) goto rom_D53A;   // BEQ.B	$D53A
  DEF_ROMLOC(D52E) : cmp_tomem_8(0x1, A0 + 0x1A); // CMPI.B	#$01,26(A0)
  DEF_ROMLOC(D534) : if (!CCR_EQ) goto rom_D55A;  // BNE.B	$D55A
  DEF_ROMLOC(D536) : move_toreg_16(0x14, &D2);    // MOVE.W	#$0014,D2
  DEF_ROMLOC(D53A) : move_toreg_16(0x1B, &D1);    // MOVE.W	#$001B,D1
  DEF_ROMLOC(D53E) : move_toreg_16(D2, &D3);      // MOVE.W	D2,D3
  DEF_ROMLOC(D540) : add_toreg_16(0x1, &D3);      // ADDQ.W	#$01,D3
  DEF_ROMLOC(D542)
      : move_toreg_16(read_16(A0 + 0x8), &D4);     // MOVE.W	8(A0),D4
  DEF_ROMLOC(D546) : rom_10062();                  // BSR.W	$10062
  DEF_ROMLOC(D54A) : btst_tomem_8(0x3, A0 + 0x22); // BTST.B	#$03,34(A0)
  DEF_ROMLOC(D550) : if (!CCR_EQ) goto rom_D5B0;   // BNE.B	$D5B0
  DEF_ROMLOC(D552) : cmp_toreg_16(0x1, &D4);       // CMPI.W	#$0001,D4
  DEF_ROMLOC(D556) : if (CCR_EQ) goto rom_D580;    // BEQ.B	$D580
  DEF_ROMLOC(D558) : goto rom_D5B0;
  DEF_ROMLOC(D55A) : move_toreg_32(0x0, &D1); // MOVEQ.L	$00,D1
  DEF_ROMLOC(D55C)
      : move_toreg_8(read_8(A0 + 0x19), &D1);               // MOVE.B
                                                            // 25(A0),D1
  DEF_ROMLOC(D560) : add_toreg_16(0xB, &D1);                // ADDI.W	#$000B,D1
  DEF_ROMLOC(D564) : move_toreg_16(0x10, &D2);              // MOVE.W	#$0010,D2
  DEF_ROMLOC(D568) : move_toreg_16(0x11, &D3);              // MOVE.W	#$0011,D3
  DEF_ROMLOC(D56C) : move_toreg_16(read_16(A0 + 0x8), &D4); // MOVE.W	8(A0),D4
  DEF_ROMLOC(D570) : rom_10062();                           // BSR.W	$10062
  DEF_ROMLOC(D574) : btst_tomem_8(0x3, A0 + 0x22);   // BTST.B	#$03,34(A0)
  DEF_ROMLOC(D57A) : if (!CCR_EQ) goto rom_D580;     // BNE.B	$D580
  DEF_ROMLOC(D57C) : tst_reg_16(&D4);                // TST.W	D4
  DEF_ROMLOC(D57E) : if (CCR_PL) goto rom_D5B0;      // BPL.B	$D5B0
  DEF_ROMLOC(D580) : tst_mem_8(0xFFFFFE2D);          // TST.B	$FE2D
  DEF_ROMLOC(D584) : if (!CCR_EQ) goto rom_D5B0;     // BNE.B	$D5B0
  DEF_ROMLOC(D586) : move_tomem_32(A0, A7 -= 4);     // MOVE.L	A0,-(A7)
  DEF_ROMLOC(D588) : move_toreg_32(A0, &A2);         // MOVEA.L	A0,A2
  DEF_ROMLOC(D58A) : move_toreg_32(0xFFFFD000, &A0); // LEA.L	$D000,A0
  DEF_ROMLOC(D58E) : cmp_tomem_8(0x4, A0 + 0x24);    // CMPI.B	#$04,36(A0)
  DEF_ROMLOC(D594) : if (CCR_CC) goto rom_D5AE;      // BCC.B	$D5AE
  DEF_ROMLOC(D596)
      : move_toreg_32(read_32(A0 + 0xC), &D3); // MOVE.L	12(A0),D3
  DEF_ROMLOC(D59A)
      : move_toreg_16(read_16(A0 + 0x12), &D0);   // MOVE.W	18(A0),D0
  DEF_ROMLOC(D59E) : ext_reg_32(&D0);             // EXT.L	D0
  DEF_ROMLOC(D5A0) : asl_toreg_32(0x8, &D0);      // ASL.L	#$08,D0
  DEF_ROMLOC(D5A2) : sub_toreg_32(D0, &D3);       // SUB.L	D0,D3
  DEF_ROMLOC(D5A4) : move_tomem_32(D3, A0 + 0xC); // MOVE.L	D3,12(A0)
  DEF_ROMLOC(D5A8) : rom_1B7AA();                 // JSR	$0001B7AA
  DEF_ROMLOC(D5AE)
      : move_toreg_32(read_32((A7 += 4, A7 - 4)), &A0); // MOVEA.L	(A7)+,A0
  DEF_ROMLOC(D5B0) : rom_DC92();                        // BSR.W	$DC92
  DEF_ROMLOC(D5B4)
      : move_toreg_16(read_16(A0 + 0x30), &D0);     // MOVE.W	48(A0),D0
  DEF_ROMLOC(D5B8) : and_toreg_16(0xFFFFFF80, &D0); // ANDI.W	#$FF80,D0
  DEF_ROMLOC(D5BC)
      : move_toreg_16(read_16(v_screenposx), &D1);  // MOVE.W	$F700,D1
  DEF_ROMLOC(D5C0) : sub_toreg_16(0x80, &D1);       // SUBI.W	#$0080,D1
  DEF_ROMLOC(D5C4) : and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
  DEF_ROMLOC(D5C8) : sub_toreg_16(D1, &D0);         // SUB.W	D1,D0
  DEF_ROMLOC(D5CA)
      : cmp_toreg_16(128 + GAME_WIDTH + 192, &D0); // CMPI.W	#$0280,D0
  DEF_ROMLOC(D5CE) : if (CCR_HI) {
    rom_DCCE();
    return;
  } // BHI.W	$DCCE
  DEF_ROMLOC(D5D2) : return; // RTS
}
ROMFUNC(rom_D5D4) {
  u8 switchindex = 0;
  DEF_ROMLOC(D5D4) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(D5D6) : move_toreg_8(read_8(A0 + 0x28), &D0);
  switchindex = D0;                         // MOVE.B	40(A0),D0
  DEF_ROMLOC(D5DA) : add_toreg_16(D0, &D0); // ADD.W	D0,D0
  DEF_ROMLOC(D5DC)
      : move_toreg_16(read_16(0xD5E4 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(D5E0): goto rom_D5E4 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(D5E0) : switch (switchindex) {
  case 0:
    rom_D5EA();
    break;
  case 1:
    rom_D5EC();
    break;
  case 2:
    rom_D600();
    break;
  }
}
ROMFUNC(rom_D5E4) {
  DEF_ROMLOC(D5E4) : or_toreg_8(0x8, &D6);    // ORI.B	#$08,D6
  DEF_ROMLOC(D5E8) : or_tomem_8(0x75, A4++);  // ORI.B	#$75,(A4)+
  DEF_ROMLOC(D5EC) : rom_D614();              // BSR.W	$D614
  DEF_ROMLOC(D5F0) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(D5F2)
      : move_toreg_8(read_8(A0 + 0x34), &D0); // MOVE.B
                                              // 52(A0),D0
  DEF_ROMLOC(D5F6)
      : add_toreg_16(read_16(A0 + 0x32), &D0);    // ADD.W	50(A0),D0
  DEF_ROMLOC(D5FA) : move_tomem_16(D0, A0 + 0xC); // MOVE.W	D0,12(A0)
  DEF_ROMLOC(D5FE) : return;                      // RTS
  DEF_ROMLOC(D600) : rom_D614();                  // BSR.W	$D614
  DEF_ROMLOC(D604) : move_toreg_32(0x0, &D0);     // MOVEQ.L	$00,D0
  DEF_ROMLOC(D606)
      : move_toreg_8(read_8(A0 + 0x34), &D0); // MOVE.B
                                              // 52(A0),D0
  DEF_ROMLOC(D60A)
      : add_toreg_16(read_16(A0 + 0x30), &D0);     // ADD.W
                                                   // 48(A0),D0
  DEF_ROMLOC(D60E) : move_tomem_16(D0, A0 + 0x8);  // MOVE.W	D0,8(A0)
  DEF_ROMLOC(D612) : return;                       // RTS
  DEF_ROMLOC(D614) : tst_mem_16(A0 + 0x38);        // TST.W	56(A0)
  DEF_ROMLOC(D618) : if (CCR_EQ) goto rom_D632;    // BEQ.B	$D632
  DEF_ROMLOC(D61A) : sub_tomem_16(0x1, A0 + 0x38); // SUBQ.W	#$01,56(A0)
  DEF_ROMLOC(D61E) : if (!CCR_EQ) goto rom_D674;   // BNE.B	$D674
  DEF_ROMLOC(D620) : tst_mem_8(A0 + 0x1);          // TST.B	1(A0)
  DEF_ROMLOC(D624) : if (CCR_PL) goto rom_D674;    // BPL.B	$D674
  DEF_ROMLOC(D626)
      : move_toreg_16(SFX_SPIKESMOVE, &D0);     // MOVE.W
                                                // #$00B6,D0
  DEF_ROMLOC(D62A) : play_sound_special();      // JSR	$00001394
  DEF_ROMLOC(D630) : goto rom_D674;             // BRA.B	$D674
  DEF_ROMLOC(D632) : tst_mem_16(A0 + 0x36);     // TST.W	54(A0)
  DEF_ROMLOC(D636) : if (CCR_EQ) goto rom_D654; // BEQ.B	$D654
  DEF_ROMLOC(D638)
      : sub_tomem_16(0x800, A0 + 0x34);         // SUBI.W	#$0800,52(A0)
  DEF_ROMLOC(D63E) : if (CCR_CC) goto rom_D674; // BCC.B	$D674
  DEF_ROMLOC(D640)
      : move_tomem_16(0x0, A0 + 0x34); // MOVE.W	#$0000,52(A0)
  DEF_ROMLOC(D646)
      : move_tomem_16(0x0, A0 + 0x36); // MOVE.W	#$0000,54(A0)
  DEF_ROMLOC(D64C)
      : move_tomem_16(0x3C, A0 + 0x38); // MOVE.W	#$003C,56(A0)
  DEF_ROMLOC(D652) : goto rom_D674;     // BRA.B	$D674
  DEF_ROMLOC(D654)
      : add_tomem_16(0x800, A0 + 0x34); // ADDI.W	#$0800,52(A0)
  DEF_ROMLOC(D65A)
      : cmp_tomem_16(0x2000, A0 + 0x34);        // CMPI.W	#$2000,52(A0)
  DEF_ROMLOC(D660) : if (CCR_CS) goto rom_D674; // BCS.B	$D674
  DEF_ROMLOC(D662)
      : move_tomem_16(0x2000, A0 + 0x34); // MOVE.W
                                          // #$2000,52(A0)
  DEF_ROMLOC(D668)
      : move_tomem_16(0x1, A0 + 0x36); // MOVE.W	#$0001,54(A0)
  DEF_ROMLOC(D66E)
      : move_tomem_16(0x3C, A0 + 0x38); // MOVE.W	#$003C,56(A0)
  DEF_ROMLOC(D674) : return;            // RTS
}
ROMFUNC(rom_D5EA) {
  DEF_ROMLOC(D5EA) : return; // RTS
}
ROMFUNC(rom_D5EC) {
  DEF_ROMLOC(D5EC) : rom_D614();              // BSR.W	$D614
  DEF_ROMLOC(D5F0) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(D5F2)
      : move_toreg_8(read_8(A0 + 0x34), &D0); // MOVE.B
                                              // 52(A0),D0
  DEF_ROMLOC(D5F6)
      : add_toreg_16(read_16(A0 + 0x32), &D0);    // ADD.W	50(A0),D0
  DEF_ROMLOC(D5FA) : move_tomem_16(D0, A0 + 0xC); // MOVE.W	D0,12(A0)
  DEF_ROMLOC(D5FE) : return;                      // RTS
}
ROMFUNC(rom_D600) {
  DEF_ROMLOC(D600) : rom_D614();              // BSR.W	$D614
  DEF_ROMLOC(D604) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(D606)
      : move_toreg_8(read_8(A0 + 0x34), &D0); // MOVE.B
                                              // 52(A0),D0
  DEF_ROMLOC(D60A)
      : add_toreg_16(read_16(A0 + 0x30), &D0);    // ADD.W	48(A0),D0
  DEF_ROMLOC(D60E) : move_tomem_16(D0, A0 + 0x8); // MOVE.W	D0,8(A0)
  DEF_ROMLOC(D612) : return;                      // RTS
}
ROMFUNC(rom_D614) {
  DEF_ROMLOC(D614) : tst_mem_16(A0 + 0x38);        // TST.W	56(A0)
  DEF_ROMLOC(D618) : if (CCR_EQ) goto rom_D632;    // BEQ.B	$D632
  DEF_ROMLOC(D61A) : sub_tomem_16(0x1, A0 + 0x38); // SUBQ.W	#$01,56(A0)
  DEF_ROMLOC(D61E) : if (!CCR_EQ) goto rom_D674;   // BNE.B	$D674
  DEF_ROMLOC(D620) : tst_mem_8(A0 + 0x1);          // TST.B	1(A0)
  DEF_ROMLOC(D624) : if (CCR_PL) goto rom_D674;    // BPL.B	$D674
  DEF_ROMLOC(D626)
      : move_toreg_16(SFX_SPIKESMOVE, &D0);     // MOVE.W
                                                // #$00B6,D0
  DEF_ROMLOC(D62A) : play_sound_special();      // JSR	$00001394
  goto rom_D674;                                // BRA.B	$D674
  DEF_ROMLOC(D632) : tst_mem_16(A0 + 0x36);     // TST.W	54(A0)
  DEF_ROMLOC(D636) : if (CCR_EQ) goto rom_D654; // BEQ.B	$D654
  DEF_ROMLOC(D638)
      : sub_tomem_16(0x800, A0 + 0x34);         // SUBI.W	#$0800,52(A0)
  DEF_ROMLOC(D63E) : if (CCR_CC) goto rom_D674; // BCC.B	$D674
  DEF_ROMLOC(D640)
      : move_tomem_16(0x0, A0 + 0x34); // MOVE.W	#$0000,52(A0)
  DEF_ROMLOC(D646)
      : move_tomem_16(0x0, A0 + 0x36); // MOVE.W	#$0000,54(A0)
  DEF_ROMLOC(D64C)
      : move_tomem_16(0x3C, A0 + 0x38); // MOVE.W	#$003C,56(A0)
  goto rom_D674;                        // BRA.B	$D674
  DEF_ROMLOC(D654)
      : add_tomem_16(0x800, A0 + 0x34); // ADDI.W	#$0800,52(A0)
  DEF_ROMLOC(D65A)
      : cmp_tomem_16(0x2000, A0 + 0x34);        // CMPI.W	#$2000,52(A0)
  DEF_ROMLOC(D660) : if (CCR_CS) goto rom_D674; // BCS.B	$D674
  DEF_ROMLOC(D662)
      : move_tomem_16(0x2000, A0 + 0x34); // MOVE.W
                                          // #$2000,52(A0)
  DEF_ROMLOC(D668)
      : move_tomem_16(0x1, A0 + 0x36); // MOVE.W	#$0001,54(A0)
  DEF_ROMLOC(D66E)
      : move_tomem_16(0x3C, A0 + 0x38); // MOVE.W	#$003C,56(A0)
  DEF_ROMLOC(D674) : return;            // RTS
}