// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_175DA) {
  u8 switchindex = 0;
  DEF_ROMLOC(175DA) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(175DC) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(175E0)
      : move_toreg_16(read_16(0x175EE + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	12(PC,D0),D1
  // DEF_ROMLOC(175E4): rom_175EE + (s16)(D1 & 0xffff)(); // JSR	8(PC,D1)
  DEF_ROMLOC(175E4) : switch (switchindex) {
  case 0:
    rom_175F6();
    break;
  case 1:
    rom_1765A();
    break;
  case 2:
    rom_1773E();
    break;
  case 3:
    rom_17740();
    break;
  }
  DEF_ROMLOC(175E8) : rom_FD38(); // JMP	$0000FD38
}
ROMFUNC(rom_175F6) {
  DEF_ROMLOC(175F6) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(175FA)
      : move_tomem_32(0x178A4, A0 + 0x4);             // MOVE.L	#$000178A4,4(A0)
  DEF_ROMLOC(17602) : move_tomem_16(0x7A0, A0 + 0x2); // MOVE.W	#$07A0,2(A0)
  DEF_ROMLOC(17608) : move_tomem_8(0x4, A0 + 0x1);    // MOVE.B	#$04,1(A0)
  DEF_ROMLOC(1760E) : move_tomem_8(0x8, A0 + 0x19);   // MOVE.B	#$08,25(A0)
  DEF_ROMLOC(17614) : move_tomem_8(0x5, A0 + 0x18);   // MOVE.B	#$05,24(A0)
  DEF_ROMLOC(1761A) : move_toreg_32(0xFFFFFC00, &A2); // LEA.L	$FC00,A2
  DEF_ROMLOC(1761E) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(17620)
      : move_toreg_8(read_8(A0 + 0x23), &D0); // MOVE.B
                                              // 35(A0),D0
  DEF_ROMLOC(17624)
      : bclr_tomem_8(0x7,
                     (s32)A2 + (s8)0x2 + (s16)D0); // BCLR.B	#$07,2(A2,D0)
  DEF_ROMLOC(1762A)
      : btst_tomem_8(0x0,
                     (s32)A2 + (s8)0x2 + (s16)D0); // BTST.B	#$00,2(A2,D0)
  DEF_ROMLOC(17630) : if (!CCR_EQ) goto rom_17646; // BNE.B	$17646
  DEF_ROMLOC(17632)
      : move_toreg_8(read_8(0xFFFFFE30), &D1); // MOVE.B	$FE30,D1
  DEF_ROMLOC(17636) : and_toreg_8(0x7F, &D1);  // ANDI.B	#$7F,D1
  DEF_ROMLOC(1763A)
      : move_toreg_8(read_8(A0 + 0x28), &D2); // MOVE.B
                                              // 40(A0),D2
  DEF_ROMLOC(1763E) : and_toreg_8(0x7F, &D2); // ANDI.B	#$7F,D2
  DEF_ROMLOC(17642) : cmp_toreg_8(D2, &D1);   // CMP.B	D2,D1
  DEF_ROMLOC(17644) : if (CCR_CS) {
    rom_1765A();
    return;
  } // BCS.B	$1765A
  DEF_ROMLOC(17646)
      : bset_tomem_8(0x0,
                     (s32)A2 + (s8)0x2 + (s16)D0);  // BSET.B	#$00,2(A2,D0)
  DEF_ROMLOC(1764C) : move_tomem_8(0x4, A0 + 0x24); // MOVE.B	#$04,36(A0)
  DEF_ROMLOC(17652) : move_tomem_8(0x3, A0 + 0x1A); // MOVE.B	#$03,26(A0)
  DEF_ROMLOC(17658) : return;                       // RTS
}
ROMFUNC(rom_1765A) {
  DEF_ROMLOC(1765A) : tst_mem_16(0xFFFFFE08);      // TST.W	$FE08
  DEF_ROMLOC(1765E) : if (!CCR_EQ) goto rom_1773C; // BNE.W	$1773C
  DEF_ROMLOC(17662) : tst_mem_8(0xFFFFF7C8);       // TST.B	$F7C8
  DEF_ROMLOC(17666) : if (CCR_MI) goto rom_1773C;  // BMI.W	$1773C
  DEF_ROMLOC(1766A)
      : move_toreg_8(read_8(0xFFFFFE30), &D1); // MOVE.B	$FE30,D1
  DEF_ROMLOC(1766E) : and_toreg_8(0x7F, &D1);  // ANDI.B	#$7F,D1
  DEF_ROMLOC(17672)
      : move_toreg_8(read_8(A0 + 0x28), &D2);         // MOVE.B
                                                      // 40(A0),D2
  DEF_ROMLOC(17676) : and_toreg_8(0x7F, &D2);         // ANDI.B	#$7F,D2
  DEF_ROMLOC(1767A) : cmp_toreg_8(D2, &D1);           // CMP.B	D2,D1
  DEF_ROMLOC(1767C) : if (CCR_CS) goto rom_1769E;     // BCS.B	$1769E
  DEF_ROMLOC(1767E) : move_toreg_32(0xFFFFFC00, &A2); // LEA.L	$FC00,A2
  DEF_ROMLOC(17682) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(17684)
      : move_toreg_8(read_8(A0 + 0x23), &D0); // MOVE.B
                                              // 35(A0),D0
  DEF_ROMLOC(17688)
      : bset_tomem_8(0x0,
                     (s32)A2 + (s8)0x2 + (s16)D0);  // BSET.B	#$00,2(A2,D0)
  DEF_ROMLOC(1768E) : move_tomem_8(0x4, A0 + 0x24); // MOVE.B	#$04,36(A0)
  DEF_ROMLOC(17694) : move_tomem_8(0x3, A0 + 0x1A); // MOVE.B	#$03,26(A0)
  DEF_ROMLOC(1769A) : goto rom_1773C;               // BRA.W	$1773C
  DEF_ROMLOC(1769E)
      : move_toreg_16(read_16(0xFFFFD008), &D0); // MOVE.W	$D008,D0
  DEF_ROMLOC(176A2)
      : sub_toreg_16(read_16(A0 + 0x8), &D0);     // SUB.W	8(A0),D0
  DEF_ROMLOC(176A6) : add_toreg_16(0x8, &D0);     // ADDQ.W	#$08,D0
  DEF_ROMLOC(176A8) : cmp_toreg_16(0x10, &D0);    // CMPI.W	#$0010,D0
  DEF_ROMLOC(176AC) : if (CCR_CC) goto rom_1773C; // BCC.W	$1773C
  DEF_ROMLOC(176B0)
      : move_toreg_16(read_16(0xFFFFD00C), &D0); // MOVE.W	$D00C,D0
  DEF_ROMLOC(176B4)
      : sub_toreg_16(read_16(A0 + 0xC), &D0);     // SUB.W	12(A0),D0
  DEF_ROMLOC(176B8) : add_toreg_16(0x40, &D0);    // ADDI.W	#$0040,D0
  DEF_ROMLOC(176BC) : cmp_toreg_16(0x68, &D0);    // CMPI.W	#$0068,D0
  DEF_ROMLOC(176C0) : if (CCR_CC) goto rom_1773C; // BCC.B	$1773C
  DEF_ROMLOC(176C2)
      : move_toreg_16(SFX_LAMPPOST, &D0);          // MOVE.W
                                                   // #$00A1,D0
  DEF_ROMLOC(176C6) : play_sound_special();        // JSR	$00001394
  DEF_ROMLOC(176CC) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(176D0) : rom_E11A();                  // JSR	$0000E11A
  DEF_ROMLOC(176D6) : if (!CCR_EQ) goto rom_17722; // BNE.B	$17722
  DEF_ROMLOC(176D8)
      : move_tomem_8(OBJ_LAMPPOST,
                     A1 + offsetof(object, id));    // MOVE.B	#$79,0(A1)
  DEF_ROMLOC(176DE) : move_tomem_8(0x6, A1 + 0x24); // MOVE.B	#$06,36(A1)
  DEF_ROMLOC(176E4)
      : move_tomem_16(read_16(A0 + 0x8), A1 + 0x30); // MOVE.W	8(A0),48(A1)
  DEF_ROMLOC(176EA)
      : move_tomem_16(read_16(A0 + 0xC), A1 + 0x32); // MOVE.W	12(A0),50(A1)
  DEF_ROMLOC(176F0) : sub_tomem_16(0x18, A1 + 0x32); // SUBI.W	#$0018,50(A1)
  DEF_ROMLOC(176F6)
      : move_tomem_32(0x178A4, A1 + 0x4);             // MOVE.L	#$000178A4,4(A1)
  DEF_ROMLOC(176FE) : move_tomem_16(0x7A0, A1 + 0x2); // MOVE.W	#$07A0,2(A1)
  DEF_ROMLOC(17704) : move_tomem_8(0x4, A1 + 0x1);    // MOVE.B	#$04,1(A1)
  DEF_ROMLOC(1770A) : move_tomem_8(0x8, A1 + 0x19);   // MOVE.B	#$08,25(A1)
  DEF_ROMLOC(17710) : move_tomem_8(0x4, A1 + 0x18);   // MOVE.B	#$04,24(A1)
  DEF_ROMLOC(17716) : move_tomem_8(0x2, A1 + 0x1A);   // MOVE.B	#$02,26(A1)
  DEF_ROMLOC(1771C) : move_tomem_16(0x20, A1 + 0x36); // MOVE.W	#$0020,54(A1)
  DEF_ROMLOC(17722) : move_tomem_8(0x1, A0 + 0x1A);   // MOVE.B	#$01,26(A0)
  DEF_ROMLOC(17728) : rom_1777E();                    // BSR.W	$1777E
  DEF_ROMLOC(1772C) : move_toreg_32(0xFFFFFC00, &A2); // LEA.L	$FC00,A2
  DEF_ROMLOC(17730) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(17732)
      : move_toreg_8(read_8(A0 + 0x23), &D0); // MOVE.B
                                              // 35(A0),D0
  DEF_ROMLOC(17736)
      : bset_tomem_8(0x0,
                     (s32)A2 + (s8)0x2 + (s16)D0); // BSET.B	#$00,2(A2,D0)
  DEF_ROMLOC(1773C) : return;                      // RTS
}
ROMFUNC(rom_1773E) {
  DEF_ROMLOC(1773E) : return; // RTS
}
ROMFUNC(rom_17740) {
  DEF_ROMLOC(17740) : sub_tomem_16(0x1, A0 + 0x36); // SUBQ.W	#$01,54(A0)
  DEF_ROMLOC(17744) : if (CCR_PL) goto rom_1774C;   // BPL.B	$1774C
  DEF_ROMLOC(17746) : move_tomem_8(0x4, A0 + 0x24); // MOVE.B	#$04,36(A0)
  DEF_ROMLOC(1774C)
      : move_toreg_8(read_8(A0 + 0x26), &D0);       // MOVE.B	38(A0),D0
  DEF_ROMLOC(17750) : sub_tomem_8(0x10, A0 + 0x26); // SUBI.B	#$10,38(A0)
  DEF_ROMLOC(17756) : sub_toreg_8(0x40, &D0);       // SUBI.B	#$40,D0
  DEF_ROMLOC(1775A) : rom_29D2();                   // JSR	$000029D2
  DEF_ROMLOC(17760) : muls_toreg_16(0xC00, &D1);    // MULS.W	#$0C00,D1
  DEF_ROMLOC(17764) : SWAPWORDS(D1);                // SWAP.W	D1
  DEF_ROMLOC(17766)
      : add_toreg_16(read_16(A0 + 0x30), &D1);     // ADD.W	48(A0),D1
  DEF_ROMLOC(1776A) : move_tomem_16(D1, A0 + 0x8); // MOVE.W	D1,8(A0)
  DEF_ROMLOC(1776E) : muls_toreg_16(0xC00, &D0);   // MULS.W	#$0C00,D0
  DEF_ROMLOC(17772) : SWAPWORDS(D0);               // SWAP.W	D0
  DEF_ROMLOC(17774)
      : add_toreg_16(read_16(A0 + 0x32), &D0);     // ADD.W	50(A0),D0
  DEF_ROMLOC(17778) : move_tomem_16(D0, A0 + 0xC); // MOVE.W	D0,12(A0)
  DEF_ROMLOC(1777C) : return;                      // RTS
}
ROMFUNC(rom_1777E) {
  DEF_ROMLOC(1777E)
      : move_tomem_8(read_8(A0 + 0x28), 0xFFFFFE30); // MOVE.B	40(A0),$FE30
  DEF_ROMLOC(17784)
      : move_tomem_8(read_8(0xFFFFFE30), 0xFFFFFE31); // MOVE.B	$FE30,$FE31
  DEF_ROMLOC(1778A)
      : move_tomem_16(read_16(A0 + 0x8), 0xFFFFFE32); // MOVE.W	8(A0),$FE32
  DEF_ROMLOC(17790)
      : move_tomem_16(read_16(A0 + 0xC), 0xFFFFFE34); // MOVE.W	12(A0),$FE34
  DEF_ROMLOC(17796)
      : move_tomem_16(read_16(0xFFFFFE20),
                      0xFFFFFE36); // MOVE.W	$FE20,$FE36
  DEF_ROMLOC(1779C)
      : move_tomem_8(read_8(0xFFFFFE1B), 0xFFFFFE54); // MOVE.B	$FE1B,$FE54
  DEF_ROMLOC(177A2)
      : move_tomem_32(read_32(0xFFFFFE22),
                      0xFFFFFE38); // MOVE.L	$FE22,$FE38
  DEF_ROMLOC(177A8)
      : move_tomem_8(read_8(0xFFFFF742), 0xFFFFFE3C); // MOVE.B	$F742,$FE3C
  DEF_ROMLOC(177AE)
      : move_tomem_16(read_16(0xFFFFF72E),
                      0xFFFFFE3E); // MOVE.W	$F72E,$FE3E
  DEF_ROMLOC(177B4)
      : move_tomem_16(read_16(0xFFFFF700),
                      0xFFFFFE40); // MOVE.W	$F700,$FE40
  DEF_ROMLOC(177BA)
      : move_tomem_16(read_16(0xFFFFF704),
                      0xFFFFFE42); // MOVE.W	$F704,$FE42
  DEF_ROMLOC(177C0)
      : move_tomem_16(read_16(0xFFFFF708),
                      0xFFFFFE44); // MOVE.W	$F708,$FE44
  DEF_ROMLOC(177C6)
      : move_tomem_16(read_16(0xFFFFF70C),
                      0xFFFFFE46); // MOVE.W	$F70C,$FE46
  DEF_ROMLOC(177CC)
      : move_tomem_16(read_16(0xFFFFF710),
                      0xFFFFFE48); // MOVE.W	$F710,$FE48
  DEF_ROMLOC(177D2)
      : move_tomem_16(read_16(0xFFFFF714),
                      0xFFFFFE4A); // MOVE.W	$F714,$FE4A
  DEF_ROMLOC(177D8)
      : move_tomem_16(read_16(0xFFFFF718),
                      0xFFFFFE4C); // MOVE.W	$F718,$FE4C
  DEF_ROMLOC(177DE)
      : move_tomem_16(read_16(0xFFFFF71C),
                      0xFFFFFE4E); // MOVE.W	$F71C,$FE4E
  DEF_ROMLOC(177E4)
      : move_tomem_16(read_16(0xFFFFF648),
                      0xFFFFFE50); // MOVE.W	$F648,$FE50
  DEF_ROMLOC(177EA)
      : move_tomem_8(read_8(0xFFFFF64D), 0xFFFFFE52); // MOVE.B	$F64D,$FE52
  DEF_ROMLOC(177F0)
      : move_tomem_8(read_8(0xFFFFF64E), 0xFFFFFE53); // MOVE.B	$F64E,$FE53
  DEF_ROMLOC(177F6) : return;                         // RTS
}