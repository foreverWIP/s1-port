// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_A984) {
  u8 switchindex = 0;
  DEF_ROMLOC(A984) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(A986) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(A98A)
      : move_toreg_16(read_16(0xA996 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	10(PC,D0),D1
  // DEF_ROMLOC(A98E): rom_A996 + (s16)(D1 & 0xffff)(); // JSR	6(PC,D1)
  DEF_ROMLOC(A98E) : switch (switchindex) {
  case 0:
    rom_A99C();
    break;
  case 1:
    rom_A9DC();
    break;
  case 2:
    rom_AB0E();
    break;
  }
  DEF_ROMLOC(A992) : {
    rom_DC92();
    return;
  } // BRA.W	$DC92
}
ROMFUNC(rom_A99C) {
  DEF_ROMLOC(A99C) : add_tomem_8(0x2, A0 + 0x24);    // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(A9A0) : move_tomem_16(0x680, A0 + 0x2); // MOVE.W	#$0680,2(A0)
  DEF_ROMLOC(A9A6) : move_tomem_8(0x24, A0 + 0x1);   // MOVE.B	#$24,1(A0)
  DEF_ROMLOC(A9AC) : move_tomem_8(0x3, A0 + 0x18);   // MOVE.B	#$03,24(A0)
  DEF_ROMLOC(A9B2) : move_tomem_8(0x8, A0 + 0x19);   // MOVE.B	#$08,25(A0)
  DEF_ROMLOC(A9B8)
      : move_tomem_16(0xFFFFFD00, A0 + 0x12); // MOVE.W	#$FD00,18(A0)
  DEF_ROMLOC(A9BE) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(A9C0)
      : move_toreg_8(read_8(A0 + 0x1C), &D0);     // MOVE.B	28(A0),D0
  DEF_ROMLOC(A9C4) : add_toreg_8(0x2, &D0);       // ADDQ.B	#$02,D0
  DEF_ROMLOC(A9C6) : move_tomem_8(D0, A0 + 0x1A); // MOVE.B D0,26(A0)
  DEF_ROMLOC(A9CA) : move_toreg_32(0xAC14, &A1);  // MOVEA.L	#$0000AC14,A1
  DEF_ROMLOC(A9D0) : add_toreg_8(D0, &D0);        // ADD.B	D0,D0
  DEF_ROMLOC(A9D2)
      : add_toreg_16(read_16((s32)A1 + (s8)0x0 + (s16)D0),
                     &A1);                        // ADDA.W	0(A1,D0),A1
  DEF_ROMLOC(A9D6) : add_toreg_16(0x1, &A1);      // ADDQ.W	#$01,A1
  DEF_ROMLOC(A9D8) : move_tomem_32(A1, A0 + 0x4); // MOVE.L	A1,4(A0)
  rom_A9DC(); // Detected flow into next function
}
ROMFUNC(rom_A9DC) {
  DEF_ROMLOC(A9DC) : tst_mem_16(A0 + 0x12);          // TST.W	18(A0)
  DEF_ROMLOC(A9E0) : if (CCR_PL) goto rom_A9F0;      // BPL.W	$A9F0
  DEF_ROMLOC(A9E4) : rom_DC6C();                     // BSR.W	$DC6C
  DEF_ROMLOC(A9E8) : add_tomem_16(0x18, A0 + 0x12);  // ADDI.W	#$0018,18(A0)
  DEF_ROMLOC(A9EE) : return;                         // RTS
  DEF_ROMLOC(A9F0) : add_tomem_8(0x2, A0 + 0x24);    // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(A9F4) : move_tomem_16(0x1D, A0 + 0x1E); // MOVE.W	#$001D,30(A0)
  DEF_ROMLOC(A9FA)
      : move_toreg_8(read_8(A0 + 0x1C), &D0);      // MOVE.B	28(A0),D0
  DEF_ROMLOC(A9FE) : cmp_toreg_8(0x1, &D0);        // CMPI.B	#$01,D0
  DEF_ROMLOC(AA02) : if (!CCR_EQ) goto rom_AA06;   // BNE.B	$AA06
  DEF_ROMLOC(AA04) : return;                       // RTS
  DEF_ROMLOC(AA06) : cmp_toreg_8(0x2, &D0);        // CMPI.B	#$02,D0
  DEF_ROMLOC(AA0A) : if (!CCR_EQ) goto rom_AA1E;   // BNE.B	$AA1E
  DEF_ROMLOC(AA0C) : add_tomem_8(0x1, 0xFFFFFE12); // ADDQ.B	#$01,$FE12
  DEF_ROMLOC(AA10) : add_tomem_8(0x1, 0xFFFFFE1C); // ADDQ.B	#$01,$FE1C
  DEF_ROMLOC(AA14) : move_toreg_16(0x88, &D0);     // MOVE.W	#$0088,D0
  DEF_ROMLOC(AA18) : {
    rom_138E();
    return;
  }                                                    // JMP	$0000138E
  DEF_ROMLOC(AA1E) : cmp_toreg_8(0x3, &D0);            // CMPI.B	#$03,D0
  DEF_ROMLOC(AA22) : if (!CCR_EQ) goto rom_AA4C;       // BNE.B	$AA4C
  DEF_ROMLOC(AA24) : move_tomem_8(0x1, 0xFFFFFE2E);    // MOVE.B	#$01,$FE2E
  DEF_ROMLOC(AA2A) : move_tomem_16(0x4B0, 0xFFFFD034); // MOVE.W
                                                       // #$04B0,$D034
  DEF_ROMLOC(AA30) : move_tomem_16(0xC00, 0xFFFFF760); // MOVE.W
                                                       // #$0C00,$F760
  DEF_ROMLOC(AA36) : move_tomem_16(0x18, 0xFFFFF762);  // MOVE.W	#$0018,$F762
  DEF_ROMLOC(AA3C) : move_tomem_16(0x80, 0xFFFFF764);  // MOVE.W	#$0080,$F764
  DEF_ROMLOC(AA42) : move_toreg_16(0xE2, &D0);         // MOVE.W	#$00E2,D0
  DEF_ROMLOC(AA46) : {
    rom_138E();
    return;
  }                                                  // JMP	$0000138E
  DEF_ROMLOC(AA4C) : cmp_toreg_8(0x4, &D0);          // CMPI.B	#$04,D0
  DEF_ROMLOC(AA50) : if (!CCR_EQ) goto rom_AA68;     // BNE.B	$AA68
  DEF_ROMLOC(AA52) : move_tomem_8(0x1, 0xFFFFFE2C);  // MOVE.B	#$01,$FE2C
  DEF_ROMLOC(AA58) : move_tomem_8(0x38, 0xFFFFD180); // MOVE.B	#$38,$D180
  DEF_ROMLOC(AA5E) : move_toreg_16(0xAF, &D0);       // MOVE.W	#$00AF,D0
  DEF_ROMLOC(AA62) : {
    rom_138E();
    return;
  }                                                    // JMP	$0000138E
  DEF_ROMLOC(AA68) : cmp_toreg_8(0x5, &D0);            // CMPI.B	#$05,D0
  DEF_ROMLOC(AA6C) : if (!CCR_EQ) goto rom_AAC4;       // BNE.B	$AAC4
  DEF_ROMLOC(AA6E) : move_tomem_8(0x1, 0xFFFFFE2D);    // MOVE.B	#$01,$FE2D
  DEF_ROMLOC(AA74) : move_tomem_16(0x4B0, 0xFFFFD032); // MOVE.W
                                                       // #$04B0,$D032
  DEF_ROMLOC(AA7A) : move_tomem_8(0x38, 0xFFFFD200);   // MOVE.B	#$38,$D200
  DEF_ROMLOC(AA80) : move_tomem_8(0x1, 0xFFFFD21C);    // MOVE.B	#$01,$D21C
  DEF_ROMLOC(AA86) : move_tomem_8(0x38, 0xFFFFD240);   // MOVE.B	#$38,$D240
  DEF_ROMLOC(AA8C) : move_tomem_8(0x2, 0xFFFFD25C);    // MOVE.B	#$02,$D25C
  DEF_ROMLOC(AA92) : move_tomem_8(0x38, 0xFFFFD280);   // MOVE.B	#$38,$D280
  DEF_ROMLOC(AA98) : move_tomem_8(0x3, 0xFFFFD29C);    // MOVE.B	#$03,$D29C
  DEF_ROMLOC(AA9E) : move_tomem_8(0x38, 0xFFFFD2C0);   // MOVE.B	#$38,$D2C0
  DEF_ROMLOC(AAA4) : move_tomem_8(0x4, 0xFFFFD2DC);    // MOVE.B	#$04,$D2DC
  DEF_ROMLOC(AAAA) : tst_mem_8(0xFFFFF7AA);            // TST.B	$F7AA
  DEF_ROMLOC(AAAE) : if (!CCR_EQ) goto rom_AAC2;       // BNE.B	$AAC2
  DEF_ROMLOC(AAB0) : cmp_tomem_16(0xC, 0xFFFFFE14);    // CMPI.W	#$000C,$FE14
  DEF_ROMLOC(AAB6) : if (CCR_LS) goto rom_AAC2;        // BLS.B	$AAC2
  DEF_ROMLOC(AAB8) : move_toreg_16(0x87, &D0);         // MOVE.W	#$0087,D0
  DEF_ROMLOC(AABC) : {
    rom_138E();
    return;
  }                                                  // JMP	$0000138E
  DEF_ROMLOC(AAC2) : return;                         // RTS
  DEF_ROMLOC(AAC4) : cmp_toreg_8(0x6, &D0);          // CMPI.B	#$06,D0
  DEF_ROMLOC(AAC8) : if (!CCR_EQ) goto rom_AB04;     // BNE.B	$AB04
  DEF_ROMLOC(AACA) : add_tomem_16(0xA, 0xFFFFFE20);  // ADDI.W	#$000A,$FE20
  DEF_ROMLOC(AAD0) : or_tomem_8(0x1, 0xFFFFFE1D);    // ORI.B	#$01,$FE1D
  DEF_ROMLOC(AAD6) : cmp_tomem_16(0x64, 0xFFFFFE20); // CMPI.W	#$0064,$FE20
  DEF_ROMLOC(AADC) : if (CCR_CS) goto rom_AAFA;      // BCS.B	$AAFA
  DEF_ROMLOC(AADE) : bset_tomem_8(0x1, 0xFFFFFE1B);  // BSET.B	#$01,$FE1B
  DEF_ROMLOC(AAE4) : if (CCR_EQ) goto rom_AA0C;      // BEQ.W	$AA0C
  DEF_ROMLOC(AAE8) : cmp_tomem_16(0xC8, 0xFFFFFE20); // CMPI.W	#$00C8,$FE20
  DEF_ROMLOC(AAEE) : if (CCR_CS) goto rom_AAFA;      // BCS.B	$AAFA
  DEF_ROMLOC(AAF0) : bset_tomem_8(0x2, 0xFFFFFE1B);  // BSET.B	#$02,$FE1B
  DEF_ROMLOC(AAF6) : if (CCR_EQ) goto rom_AA0C;      // BEQ.W	$AA0C
  DEF_ROMLOC(AAFA) : move_toreg_16(0xB5, &D0);       // MOVE.W	#$00B5,D0
  DEF_ROMLOC(AAFE) : {
    rom_138E();
    return;
  }                                              // JMP	$0000138E
  DEF_ROMLOC(AB04) : cmp_toreg_8(0x7, &D0);      // CMPI.B	#$07,D0
  DEF_ROMLOC(AB08) : if (!CCR_EQ) goto rom_AB0C; // BNE.B	$AB0C
  DEF_ROMLOC(AB0A) : {};                         // NOP
  DEF_ROMLOC(AB0C) : return;                     // RTS
}
ROMFUNC(rom_AB0E) {
  DEF_ROMLOC(AB0E) : sub_tomem_16(0x1, A0 + 0x1E); // SUBQ.W	#$01,30(A0)
  DEF_ROMLOC(AB12) : if (CCR_MI) {
    rom_DCCE();
    return;
  }                          // BMI.W	$DCCE
  DEF_ROMLOC(AB16) : return; // RTS
}
ROMFUNC(rom_AB18) {
  DEF_ROMLOC(AB18) : move_toreg_32(0xFFFFD000, &A1); // LEA.L	$D000,A1
  DEF_ROMLOC(AB1C)
      : move_toreg_16(read_16(A1 + 0x8), &D0); // MOVE.W	8(A1),D0
  DEF_ROMLOC(AB20)
      : sub_toreg_16(read_16(A0 + 0x8), &D0);   // SUB.W	8(A0),D0
  DEF_ROMLOC(AB24) : add_toreg_16(D1, &D0);     // ADD.W	D1,D0
  DEF_ROMLOC(AB26) : if (CCR_MI) goto rom_AB70; // BMI.B	$AB70
  DEF_ROMLOC(AB28) : move_toreg_16(D1, &D3);    // MOVE.W	D1,D3
  DEF_ROMLOC(AB2A) : add_toreg_16(D3, &D3);     // ADD.W	D3,D3
  DEF_ROMLOC(AB2C) : cmp_toreg_16(D3, &D0);     // CMP.W	D3,D0
  DEF_ROMLOC(AB2E) : if (CCR_HI) goto rom_AB70; // BHI.B	$AB70
  DEF_ROMLOC(AB30)
      : move_toreg_8(read_8(A1 + 0x16), &D3); // MOVE.B	22(A1),D3
  DEF_ROMLOC(AB34) : ext_reg_16(&D3);         // EXT.W	D3
  DEF_ROMLOC(AB36) : add_toreg_16(D3, &D2);   // ADD.W	D3,D2
  DEF_ROMLOC(AB38)
      : move_toreg_16(read_16(A1 + 0xC), &D3); // MOVE.W	12(A1),D3
  DEF_ROMLOC(AB3C)
      : sub_toreg_16(read_16(A0 + 0xC), &D3);      // SUB.W	12(A0),D3
  DEF_ROMLOC(AB40) : add_toreg_16(D2, &D3);        // ADD.W	D2,D3
  DEF_ROMLOC(AB42) : if (CCR_MI) goto rom_AB70;    // BMI.B	$AB70
  DEF_ROMLOC(AB44) : add_toreg_16(D2, &D2);        // ADD.W	D2,D2
  DEF_ROMLOC(AB46) : cmp_toreg_16(D2, &D3);        // CMP.W	D2,D3
  DEF_ROMLOC(AB48) : if (CCR_CC) goto rom_AB70;    // BCC.B	$AB70
  DEF_ROMLOC(AB4A) : tst_mem_8(0xFFFFF7C8);        // TST.B	$F7C8
  DEF_ROMLOC(AB4E) : if (CCR_MI) goto rom_AB70;    // BMI.B	$AB70
  DEF_ROMLOC(AB50) : cmp_tomem_8(0x6, 0xFFFFD024); // CMPI.B	#$06,$D024
  DEF_ROMLOC(AB56) : if (CCR_CC) goto rom_AB70;    // BCC.B	$AB70
  DEF_ROMLOC(AB58) : tst_mem_16(0xFFFFFE08);       // TST.W	$FE08
  DEF_ROMLOC(AB5C) : if (!CCR_EQ) goto rom_AB70;   // BNE.B	$AB70
  DEF_ROMLOC(AB5E) : cmp_toreg_16(D0, &D1);        // CMP.W	D0,D1
  DEF_ROMLOC(AB60) : if (CCR_CC) goto rom_AB66;    // BCC.B	$AB66
  DEF_ROMLOC(AB62) : add_toreg_16(D1, &D1);        // ADD.W	D1,D1
  DEF_ROMLOC(AB64) : sub_toreg_16(D1, &D0);        // SUB.W	D1,D0
  DEF_ROMLOC(AB66) : cmp_toreg_16(0x10, &D3);      // CMPI.W	#$0010,D3
  DEF_ROMLOC(AB6A) : if (CCR_CS) goto rom_AB74;    // BCS.B	$AB74
  DEF_ROMLOC(AB6C) : move_toreg_32(0x1, &D1);      // MOVEQ.L	$01,D1
  DEF_ROMLOC(AB6E) : return;                       // RTS
  DEF_ROMLOC(AB70) : move_toreg_32(0x0, &D1);      // MOVEQ.L	$00,D1
  DEF_ROMLOC(AB72) : return;                       // RTS
  DEF_ROMLOC(AB74) : move_toreg_32(0x0, &D1);      // MOVEQ.L	$00,D1
  DEF_ROMLOC(AB76)
      : move_toreg_8(read_8(A0 + 0x19), &D1); // MOVE.B	25(A0),D1
  DEF_ROMLOC(AB7A) : add_toreg_16(0x4, &D1);  // ADDQ.W	#$04,D1
  DEF_ROMLOC(AB7C) : move_toreg_16(D1, &D2);  // MOVE.W	D1,D2
  DEF_ROMLOC(AB7E) : add_toreg_16(D2, &D2);   // ADD.W	D2,D2
  DEF_ROMLOC(AB80)
      : add_toreg_16(read_16(A1 + 0x8), &D1); // ADD.W	8(A1),D1
  DEF_ROMLOC(AB84)
      : sub_toreg_16(read_16(A0 + 0x8), &D1);        // SUB.W	8(A0),D1
  DEF_ROMLOC(AB88) : if (CCR_MI) goto rom_AB6C;      // BMI.B	$AB6C
  DEF_ROMLOC(AB8A) : cmp_toreg_16(D2, &D1);          // CMP.W	D2,D1
  DEF_ROMLOC(AB8C) : if (CCR_CC) goto rom_AB6C;      // BCC.B	$AB6C
  DEF_ROMLOC(AB8E) : move_toreg_32(0xFFFFFFFF, &D1); // MOVEQ.L	$FF,D1
  DEF_ROMLOC(AB90) : return;                         // RTS
  DEF_ROMLOC(AB92) : or_tomem_8(0x1A, A4);           // ORI.B	#$1A,(A4)
  DEF_ROMLOC(AB96) : or_tomem_8(0x32, --A6);         // ORI.B	#$32,-(A6)
  rom_ACA6(); // Detected flow into next function
}