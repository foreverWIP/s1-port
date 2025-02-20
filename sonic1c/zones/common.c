// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

void load_palette_fading(void);

ROMFUNC(rom_5ECC) {
  DEF_ROMLOC(5ECC) : move_toreg_32(0x0, &D0);             // MOVEQ.L	$00,D0
  DEF_ROMLOC(5ECE) : move_tomem_8(D0, 0xFFFFF740);        // MOVE.B	D0,$F740
  DEF_ROMLOC(5ED2) : move_tomem_8(D0, 0xFFFFF741);        // MOVE.B	D0,$F741
  DEF_ROMLOC(5ED6) : move_tomem_8(D0, 0xFFFFF746);        // MOVE.B	D0,$F746
  DEF_ROMLOC(5EDA) : move_tomem_8(D0, 0xFFFFF748);        // MOVE.B	D0,$F748
  DEF_ROMLOC(5EDE) : move_tomem_8(D0, 0xFFFFF742);        // MOVE.B	D0,$F742
  DEF_ROMLOC(5EE2) : move_toreg_16(read_16(v_zone), &D0); // MOVE.W	$FE10,D0
  DEF_ROMLOC(5EE6) : lsl_toreg_8(0x6, &D0);               // LSL.B	#$06,D0
  DEF_ROMLOC(5EE8) : lsr_toreg_16(0x4, &D0);              // LSR.W	#$04,D0
  DEF_ROMLOC(5EEA) : move_toreg_16(D0, &D1);              // MOVE.W	D0,D1
  DEF_ROMLOC(5EEC) : add_toreg_16(D0, &D0);               // ADD.W	D0,D0
  DEF_ROMLOC(5EEE) : add_toreg_16(D1, &D0);               // ADD.W	D1,D0
  DEF_ROMLOC(5EF0)
      : move_toreg_32(0x5F2A + (s16)(D0 & 0xffff),
                      &A0); // LEA.L	56(PC,D0),A0
  DEF_ROMLOC(5EF4)
      : move_toreg_16(read_16((A0 += 2, A0 - 2)), &D0); // MOVE.W	(A0)+,D0
  DEF_ROMLOC(5EF6) : move_tomem_16(D0, 0xFFFFF730);     // MOVE.W	D0,$F730
  DEF_ROMLOC(5EFA)
      : move_toreg_32(read_32((A0 += 4, A0 - 4)), &D0); // MOVE.L	(A0)+,D0
  DEF_ROMLOC(5EFC) : move_tomem_32(D0, v_limitleft2);   // MOVE.L	D0,$F728
  DEF_ROMLOC(5F00) : move_tomem_32(D0, 0xFFFFF720);     // MOVE.L	D0,$F720
  DEF_ROMLOC(5F04)
      : move_toreg_32(read_32((A0 += 4, A0 - 4)), &D0); // MOVE.L	(A0)+,D0
  DEF_ROMLOC(5F06) : move_tomem_32(D0, 0xFFFFF72C);     // MOVE.L	D0,$F72C
  DEF_ROMLOC(5F0A) : move_tomem_32(D0, 0xFFFFF724);     // MOVE.L	D0,$F724
  DEF_ROMLOC(5F0E)
      : move_toreg_16(read_16(v_limitleft2), &D0);  // MOVE.W	$F728,D0
  DEF_ROMLOC(5F12) : add_toreg_16(0x240, &D0);      // ADDI.W	#$0240,D0
  DEF_ROMLOC(5F16) : move_tomem_16(D0, 0xFFFFF732); // MOVE.W	D0,$F732
  DEF_ROMLOC(5F1A)
      : move_tomem_16(0x1010, 0xFFFFF74A); // MOVE.W
                                           // #$1010,$F74A
  DEF_ROMLOC(5F20)
      : move_toreg_16(read_16((A0 += 2, A0 - 2)), &D0); // MOVE.W	(A0)+,D0
  DEF_ROMLOC(5F22) : move_tomem_16(D0, 0xFFFFF73E);     // MOVE.W	D0,$F73E
  DEF_ROMLOC(609A) : tst_mem_8(0xFFFFFE30);             // TST.B	$FE30
  DEF_ROMLOC(609E) : if (CCR_EQ) goto rom_60B0;         // BEQ.B	$60B0
  DEF_ROMLOC(60A0) : rom_177F8();                       // JSR	$000177F8
  DEF_ROMLOC(60A6)
      : move_toreg_16(read_16(0xFFFFD008), &D1); // MOVE.W	$D008,D1
  DEF_ROMLOC(60AA)
      : move_toreg_16(read_16(0xFFFFD00C), &D0);          // MOVE.W	$D00C,D0
  goto rom_60DE;                                          // BRA.B	$60DE
  DEF_ROMLOC(60B0) : move_toreg_16(read_16(v_zone), &D0); // MOVE.W	$FE10,D0
  DEF_ROMLOC(60B4) : lsl_toreg_8(0x6, &D0);               // LSL.B	#$06,D0
  DEF_ROMLOC(60B6) : lsr_toreg_16(0x4, &D0);              // LSR.W	#$04,D0
  DEF_ROMLOC(60B8)
      : move_toreg_32(0x611E + (s16)(D0 & 0xffff),
                      &A1);                     // LEA.L	100(PC,D0),A1
  DEF_ROMLOC(60BC) : tst_mem_16(0xFFFFFFF0);    // TST.W	$FFF0
  DEF_ROMLOC(60C0) : if (CCR_PL) goto rom_60CE; // BPL.B	$60CE
  DEF_ROMLOC(60C2)
      : move_toreg_16(read_16(0xFFFFFFF4), &D0); // MOVE.W	$FFF4,D0
  DEF_ROMLOC(60C6) : sub_toreg_16(0x1, &D0);     // SUBQ.W	#$01,D0
  DEF_ROMLOC(60C8) : lsl_toreg_16(0x2, &D0);     // LSL.W	#$02,D0
  DEF_ROMLOC(60CA)
      : move_toreg_32(0x607A + (s16)(D0 & 0xffff),
                      &A1);                   // LEA.L	-82(PC,D0),A1
  DEF_ROMLOC(60CE) : move_toreg_32(0x0, &D1); // MOVEQ.L	$00,D1
  DEF_ROMLOC(60D0)
      : move_toreg_16(read_16((A1 += 2, A1 - 2)), &D1); // MOVE.W	(A1)+,D1
  DEF_ROMLOC(60D2) : move_tomem_16(D1, 0xFFFFD008);     // MOVE.W	D1,$D008
  DEF_ROMLOC(60D6) : move_toreg_32(0x0, &D0);           // MOVEQ.L	$00,D0
  DEF_ROMLOC(60D8) : move_toreg_16(read_16(A1), &D0);   // MOVE.W	(A1),D0
  DEF_ROMLOC(60DA) : move_tomem_16(D0, 0xFFFFD00C);     // MOVE.W	D0,$D00C
  DEF_ROMLOC(60DE) : sub_toreg_16(0xA0, &D1);           // SUBI.W	#$00A0,D1
  DEF_ROMLOC(60E2) : if (CCR_CC) goto rom_60E6;         // BCC.B	$60E6
  DEF_ROMLOC(60E4) : move_toreg_32(0x0, &D1);           // MOVEQ.L	$00,D1
  DEF_ROMLOC(60E6)
      : move_toreg_16(read_16(v_limitright2), &D2);   // MOVE.W	$F72A,D2
  DEF_ROMLOC(60EA) : cmp_toreg_16(D2, &D1);           // CMP.W	D2,D1
  DEF_ROMLOC(60EC) : if (CCR_CS) goto rom_60F0;       // BCS.B	$60F0
  DEF_ROMLOC(60EE) : move_toreg_16(D2, &D1);          // MOVE.W	D2,D1
  DEF_ROMLOC(60F0) : move_tomem_16(D1, v_screenposx); // MOVE.W	D1,$F700
  DEF_ROMLOC(60F4) : sub_toreg_16(0x60, &D0);         // SUBI.W	#$0060,D0
  DEF_ROMLOC(60F8) : if (CCR_CC) goto rom_60FC;       // BCC.B	$60FC
  DEF_ROMLOC(60FA) : move_toreg_32(0x0, &D0);         // MOVEQ.L	$00,D0
  DEF_ROMLOC(60FC)
      : cmp_toreg_16(read_16(0xFFFFF72E), &D0); // CMP.W	$F72E,D0
  DEF_ROMLOC(6100) : if (CCR_LT) goto rom_6106; // BLT.B	$6106
  DEF_ROMLOC(6102)
      : move_toreg_16(read_16(0xFFFFF72E), &D0);        // MOVE.W	$F72E,D0
  DEF_ROMLOC(6106) : move_tomem_16(D0, 0xFFFFF704);     // MOVE.W	D0,$F704
  DEF_ROMLOC(610A) : rom_61AA();                        // BSR.W	$61AA
  DEF_ROMLOC(610E) : move_toreg_32(0x0, &D0);           // MOVEQ.L	$00,D0
  DEF_ROMLOC(6110) : move_toreg_8(read_8(v_zone), &D0); // MOVE.B	$FE10,D0
  DEF_ROMLOC(6114) : lsl_toreg_8(0x2, &D0);             // LSL.B	#$02,D0
  DEF_ROMLOC(6116)
      : move_tomem_32(read_32(0x618E + (s16)(D0 & 0xffff)),
                      0xFFFFF7AC); // MOVE.L	118(PC,D0),$F7AC
  DEF_ROMLOC(611C) : return;       // RTS
}
ROMFUNC(rom_72F0) {
  DEF_ROMLOC(72F0) : move_toreg_32(0x0, &D0);           // MOVEQ.L	$00,D0
  DEF_ROMLOC(72F2) : move_toreg_8(read_8(v_zone), &D0); // MOVE.B	$FE10,D0
  DEF_ROMLOC(72F6) : lsl_toreg_16(0x4, &D0);            // LSL.W	#$04,D0
  DEF_ROMLOC(72F8) : move_toreg_32(0x1DD16, &A2);       // LEA.L	$0001DD16,A2
  DEF_ROMLOC(72FE)
      : move_toreg_32((s32)A2 + (s8)0x0 + (s16)D0,
                      &A2);                      // LEA.L	0(A2,D0),A2
  DEF_ROMLOC(7302) : move_tomem_32(A2, A7 -= 4); // MOVE.L	A2,-(A7)
  DEF_ROMLOC(7304) : add_toreg_32(0x4, &A2);     // ADDQ.L	#$04,A2
  DEF_ROMLOC(7306)
      : move_toreg_32(read_32((A2 += 4, A2 - 4)), &A0); // MOVEA.L	(A2)+,A0
  DEF_ROMLOC(7308) : move_toreg_32(v_16x16, &A1);       // LEA.L	$B000,A1
  DEF_ROMLOC(730C) : move_toreg_16(0x0, &D0);           // MOVE.W	#$0000,D0
  DEF_ROMLOC(7310) : decompress_enigma();               // BSR.W	$1716
  DEF_ROMLOC(7314)
      : move_toreg_32(read_32((A2 += 4, A2 - 4)), &A0); // MOVEA.L	(A2)+,A0
  DEF_ROMLOC(7316) : move_toreg_32(v_256x256, &A1);     // LEA.L	$00FF0000,A1
  DEF_ROMLOC(731C) : rom_1894();                        // BSR.W	$1894
  DEF_ROMLOC(7320) : rom_735C();                        // BSR.W	$735C
  DEF_ROMLOC(7324)
      : move_toreg_16(read_16((A2 += 2, A2 - 2)), &D0); // MOVE.W	(A2)+,D0
  DEF_ROMLOC(7326) : move_toreg_16(read_16(A2), &D0);   // MOVE.W	(A2),D0
  DEF_ROMLOC(7328) : and_toreg_16(0xFF, &D0);           // ANDI.W	#$00FF,D0
  DEF_ROMLOC(732C)
      : cmp_tomem_16(ZONE16_LZ | 3, v_zone);     // CMPI.W
                                                 // #$0103,$FE10
  DEF_ROMLOC(7332) : if (!CCR_EQ) goto rom_7336; // BNE.B	$7336
  DEF_ROMLOC(7334) : move_toreg_32(0xC, &D0);    // MOVEQ.L	$0C,D0
  DEF_ROMLOC(7336)
      : cmp_tomem_16(ZONE16_SBZ | 1, v_zone);   // CMPI.W	#$0501,$FE10
  DEF_ROMLOC(733C) : if (CCR_EQ) goto rom_7346; // BEQ.B	$7346
  DEF_ROMLOC(733E)
      : cmp_tomem_16(ZONE16_SBZ | 2, v_zone);    // CMPI.W	#$0502,$FE10
  DEF_ROMLOC(7344) : if (!CCR_EQ) goto rom_7348; // BNE.B	$7348
  DEF_ROMLOC(7346) : move_toreg_32(0xE, &D0);    // MOVEQ.L	$0E,D0
  DEF_ROMLOC(7348) : load_palette_fading();      // BSR.W	$20F4
  DEF_ROMLOC(734C)
      : move_toreg_32(read_32((A7 += 4, A7 - 4)), &A2); // MOVEA.L	(A7)+,A2
  DEF_ROMLOC(734E) : add_toreg_16(0x4, &A2);            // ADDQ.W	#$04,A2
  DEF_ROMLOC(7350) : move_toreg_32(0x0, &D0);           // MOVEQ.L	$00,D0
  DEF_ROMLOC(7352) : move_toreg_8(read_8(A2), &D0);     // MOVE.B	(A2),D0
  DEF_ROMLOC(7354) : if (CCR_EQ) goto rom_735A;         // BEQ.B	$735A
  DEF_ROMLOC(7356) : add_plc();                         // BSR.W	$1578
  DEF_ROMLOC(735A) : return;                            // RTS
}
ROMFUNC(rom_735C) {
  DEF_ROMLOC(735C) : move_toreg_32(0xFFFFA400, &A3);       // LEA.L	$A400,A3
  DEF_ROMLOC(7360) : move_toreg_16(0x1FF, &D1);            // MOVE.W	#$01FF,D1
  DEF_ROMLOC(7364) : move_toreg_32(0x0, &D0);              // MOVEQ.L	$00,D0
  DEF_ROMLOC(7366) : move_tomem_32(D0, (A3 += 4, A3 - 4)); // MOVE.L	D0,(A3)+
  DEF_ROMLOC(7368) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_7366;                                   // DBF.W	D1,$7366
  DEF_ROMLOC(736C) : move_toreg_32(0xFFFFA400, &A3); // LEA.L	$A400,A3
  DEF_ROMLOC(7370) : move_toreg_32(0x0, &D1);        // MOVEQ.L	$00,D1
  DEF_ROMLOC(7372) : rom_737C();                     // BSR.W	$737C
  DEF_ROMLOC(7376) : move_toreg_32(0xFFFFA440, &A3); // LEA.L	$A440,A3
  DEF_ROMLOC(737A) : move_toreg_32(0x2, &D1);        // MOVEQ.L	$02,D1
  rom_737C(); // Detected flow into next function
}

ROMFUNC(rom_737C) {
  DEF_ROMLOC(737C) : move_toreg_16(read_16(v_zone), &D0); // MOVE.W	$FE10,D0
  DEF_ROMLOC(7380) : lsl_toreg_8(0x6, &D0);               // LSL.B	#$06,D0
  DEF_ROMLOC(7382) : lsr_toreg_16(0x5, &D0);              // LSR.W	#$05,D0
  DEF_ROMLOC(7384) : move_toreg_16(D0, &D2);              // MOVE.W	D0,D2
  DEF_ROMLOC(7386) : add_toreg_16(D0, &D0);               // ADD.W	D0,D0
  DEF_ROMLOC(7388) : add_toreg_16(D2, &D0);               // ADD.W	D2,D0
  DEF_ROMLOC(738A) : add_toreg_16(D1, &D0);               // ADD.W	D1,D0
  DEF_ROMLOC(738C) : move_toreg_32(0x68B96, &A1);         // LEA.L	$00068B96,A1
  DEF_ROMLOC(7392)
      : move_toreg_16(read_16((s32)A1 + (s8)0x0 + (s16)D0),
                      &D0); // MOVE.W	0(A1,D0),D0
  DEF_ROMLOC(7396)
      : move_toreg_32((s32)A1 + (s8)0x0 + (s16)D0,
                      &A1);                           // LEA.L	0(A1,D0),A1
  DEF_ROMLOC(739A) : move_toreg_32(0x0, &D1);         // MOVEQ.L	$00,D1
  DEF_ROMLOC(739C) : move_toreg_16(D1, &D2);          // MOVE.W	D1,D2
  DEF_ROMLOC(739E) : move_toreg_8(read_8(A1++), &D1); // MOVE.B	(A1)+,D1
  DEF_ROMLOC(73A0) : move_toreg_8(read_8(A1++), &D2); // MOVE.B	(A1)+,D2
  DEF_ROMLOC(73A2) : move_toreg_16(D1, &D0);          // MOVE.W	D1,D0
  DEF_ROMLOC(73A4) : move_toreg_32(A3, &A0);          // MOVEA.L	A3,A0
  DEF_ROMLOC(73A6)
      : move_tomem_8(read_8(A1++), A0++); // MOVE.B
                                          // (A1)+,(A0)+
  DEF_ROMLOC(73A8) : dec_reg_16(&D0);
  if ((D0 & 0xffff) != 0xffff)
    goto rom_73A6;                                  // DBF.W	D0,$73A6
  DEF_ROMLOC(73AC) : move_toreg_32(A3 + 0x80, &A3); // LEA.L	128(A3),A3
  DEF_ROMLOC(73B0) : dec_reg_16(&D2);
  if ((D2 & 0xffff) != 0xffff)
    goto rom_73A2;           // DBF.W	D2,$73A2
  DEF_ROMLOC(73B4) : return; // RTS
}

ROMFUNC(rom_177F8) {
  DEF_ROMLOC(177F8)
      : move_tomem_8(read_8(0xFFFFFE31), 0xFFFFFE30); // MOVE.B	$FE31,$FE30
  DEF_ROMLOC(177FE)
      : move_tomem_16(read_16(0xFFFFFE32),
                      0xFFFFD008); // MOVE.W	$FE32,$D008
  DEF_ROMLOC(17804)
      : move_tomem_16(read_16(0xFFFFFE34),
                      0xFFFFD00C); // MOVE.W	$FE34,$D00C
  DEF_ROMLOC(1780A)
      : move_tomem_16(read_16(0xFFFFFE36),
                      0xFFFFFE20); // MOVE.W	$FE36,$FE20
  DEF_ROMLOC(17810)
      : move_tomem_8(read_8(0xFFFFFE54), 0xFFFFFE1B); // MOVE.B	$FE54,$FE1B
  DEF_ROMLOC(17816) : clr_mem_16(0xFFFFFE20);         // CLR.W	$FE20
  DEF_ROMLOC(1781A) : clr_mem_8(0xFFFFFE1B);          // CLR.B	$FE1B
  DEF_ROMLOC(1781E)
      : move_tomem_32(read_32(0xFFFFFE38),
                      0xFFFFFE22);                    // MOVE.L	$FE38,$FE22
  DEF_ROMLOC(17824) : move_tomem_8(0x3B, 0xFFFFFE25); // MOVE.B	#$3B,$FE25
  DEF_ROMLOC(1782A) : sub_tomem_8(0x1, 0xFFFFFE24);   // SUBQ.B	#$01,$FE24
  DEF_ROMLOC(1782E)
      : move_tomem_8(read_8(0xFFFFFE3C), 0xFFFFF742); // MOVE.B	$FE3C,$F742
  DEF_ROMLOC(17834)
      : move_tomem_8(read_8(0xFFFFFE52), 0xFFFFF64D); // MOVE.B	$FE52,$F64D
  DEF_ROMLOC(1783A)
      : move_tomem_16(read_16(0xFFFFFE3E),
                      0xFFFFF72E); // MOVE.W	$FE3E,$F72E
  DEF_ROMLOC(17840)
      : move_tomem_16(read_16(0xFFFFFE3E),
                      0xFFFFF726); // MOVE.W	$FE3E,$F726
  DEF_ROMLOC(17846)
      : move_tomem_16(read_16(0xFFFFFE40),
                      v_screenposx); // MOVE.W	$FE40,$F700
  DEF_ROMLOC(1784C)
      : move_tomem_16(read_16(0xFFFFFE42),
                      0xFFFFF704); // MOVE.W	$FE42,$F704
  DEF_ROMLOC(17852)
      : move_tomem_16(read_16(0xFFFFFE44),
                      0xFFFFF708); // MOVE.W	$FE44,$F708
  DEF_ROMLOC(17858)
      : move_tomem_16(read_16(0xFFFFFE46),
                      0xFFFFF70C); // MOVE.W	$FE46,$F70C
  DEF_ROMLOC(1785E)
      : move_tomem_16(read_16(0xFFFFFE48),
                      0xFFFFF710); // MOVE.W	$FE48,$F710
  DEF_ROMLOC(17864)
      : move_tomem_16(read_16(0xFFFFFE4A),
                      0xFFFFF714); // MOVE.W	$FE4A,$F714
  DEF_ROMLOC(1786A)
      : move_tomem_16(read_16(0xFFFFFE4C),
                      0xFFFFF718); // MOVE.W	$FE4C,$F718
  DEF_ROMLOC(17870)
      : move_tomem_16(read_16(0xFFFFFE4E),
                      0xFFFFF71C);                  // MOVE.W	$FE4E,$F71C
  DEF_ROMLOC(17876) : cmp_tomem_8(ZONE_LZ, v_zone); // CMPI.B	#$01,$FE10
  DEF_ROMLOC(1787C) : if (!CCR_EQ) goto rom_17890;  // BNE.B	$17890
  DEF_ROMLOC(1787E)
      : move_tomem_16(read_16(0xFFFFFE50),
                      0xFFFFF648); // MOVE.W	$FE50,$F648
  DEF_ROMLOC(17884)
      : move_tomem_8(read_8(0xFFFFFE52), 0xFFFFF64D); // MOVE.B	$FE52,$F64D
  DEF_ROMLOC(1788A)
      : move_tomem_8(read_8(0xFFFFFE53), 0xFFFFF64E); // MOVE.B	$FE53,$F64E
  DEF_ROMLOC(17890) : tst_mem_8(0xFFFFFE30);          // TST.B	$FE30
  DEF_ROMLOC(17894) : if (CCR_PL) goto rom_178A2;     // BPL.B	$178A2
  DEF_ROMLOC(17896)
      : move_toreg_16(read_16(0xFFFFFE32), &D0);       // MOVE.W	$FE32,D0
  DEF_ROMLOC(1789A) : sub_toreg_16(0xA0, &D0);         // SUBI.W	#$00A0,D0
  DEF_ROMLOC(1789E) : move_tomem_16(D0, v_limitleft2); // MOVE.W	D0,$F728
  DEF_ROMLOC(178A2) : return;                          // RTS
}