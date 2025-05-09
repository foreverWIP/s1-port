// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_1CCFE) {
  u8 switchindex = 0;
  DEF_ROMLOC(1CCFE) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(1CD00) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(1CD04)
      : move_toreg_16(read_16(0x1CD0C + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(1CD08): goto rom_1CD0C + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(1CD08) : switch (switchindex) {
  case 0:
    rom_1CD10();
    break;
  case 1:
    rom_1CD3A();
    break;
  }
}
ROMFUNC(rom_1CD10) {
  DEF_ROMLOC(1CD10) : add_tomem_8(0x2, A0 + 0x24);    // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(1CD14) : move_tomem_16(0x90, A0 + 0x8);  // MOVE.W	#$0090,8(A0)
  DEF_ROMLOC(1CD1A) : move_tomem_16(0x108, A0 + 0xA); // MOVE.W	#$0108,10(A0)
  DEF_ROMLOC(1CD20)
      : move_tomem_32(0x1CD6A, A0 + 0x4);             // MOVE.L	#$0001CD6A,4(A0)
  DEF_ROMLOC(1CD28) : move_tomem_16(0x6CA, A0 + 0x2); // MOVE.W	#$06CA,2(A0)
  DEF_ROMLOC(1CD2E) : move_tomem_8(0x0, A0 + 0x1);    // MOVE.B	#$00,1(A0)
  DEF_ROMLOC(1CD34) : move_tomem_8(0x0, A0 + 0x18);   // MOVE.B	#$00,24(A0)
  rom_1CD3A();
}
ROMFUNC(rom_1CD3A) {
  DEF_ROMLOC(1CD3A) : tst_mem_16(0xFFFFFE20);     // TST.W	$FE20
  DEF_ROMLOC(1CD3E) : if (CCR_EQ) goto rom_1CD4A; // BEQ.B	$1CD4A
  DEF_ROMLOC(1CD40) : clr_mem_8(A0 + 0x1A);       // CLR.B	26(A0)
  DEF_ROMLOC(1CD44) : {
    queue_sprite();
    return;
  } // JMP	$0000DC92
  DEF_ROMLOC(1CD4A) : move_toreg_32(0x0, &D0);       // MOVEQ.L	$00,D0
  DEF_ROMLOC(1CD4C) : btst_tomem_8(0x3, 0xFFFFFE05); // BTST.B	#$03,$FE05
  DEF_ROMLOC(1CD52) : if (!CCR_EQ) goto rom_1CD60;   // BNE.B	$1CD60
  DEF_ROMLOC(1CD54) : add_toreg_16(0x1, &D0);        // ADDQ.W	#$01,D0
  DEF_ROMLOC(1CD56) : cmp_tomem_8(0x9, 0xFFFFFE23);  // CMPI.B	#$09,$FE23
  DEF_ROMLOC(1CD5C) : if (!CCR_EQ) goto rom_1CD60;   // BNE.B	$1CD60
  DEF_ROMLOC(1CD5E) : add_toreg_16(0x2, &D0);        // ADDQ.W	#$02,D0
  DEF_ROMLOC(1CD60) : move_tomem_8(D0, A0 + 0x1A);   // MOVE.B	D0,26(A0)
  DEF_ROMLOC(1CD64) : {
    queue_sprite();
    return;
  } // JMP	$0000DC92
}
ROMFUNC(rom_1CE42) {
  DEF_ROMLOC(1CE42) : move_tomem_8(0x1, 0xFFFFFE1F);  // MOVE.B	#$01,$FE1F
  DEF_ROMLOC(1CE48) : move_toreg_32(0xFFFFFE26, &A3); // LEA.L	$FE26,A3
  DEF_ROMLOC(1CE4C) : add_tomem_32(D0, A3);           // ADD.L	D0,(A3)
  DEF_ROMLOC(1CE4E)
      : move_toreg_32(0xF423F, &D1);                   // MOVE.L	#$000F423F,D1
  DEF_ROMLOC(1CE54) : cmp_toreg_32(read_32(A3), &D1);  // CMP.L	(A3),D1
  DEF_ROMLOC(1CE56) : if (CCR_HI) goto rom_1CE5A;      // BHI.B	$1CE5A
  DEF_ROMLOC(1CE58) : move_tomem_32(D1, A3);           // MOVE.L	D1,(A3)
  DEF_ROMLOC(1CE5A) : move_toreg_32(read_32(A3), &D0); // MOVE.L	(A3),D0
  DEF_ROMLOC(1CE5C)
      : cmp_toreg_32(read_32(0xFFFFFFC0), &D0);   // CMP.L	$FFC0,D0
  DEF_ROMLOC(1CE60) : if (CCR_CS) goto rom_1CE82; // BCS.B	$1CE82
  DEF_ROMLOC(1CE62)
      : add_tomem_32(0x1388, 0xFFFFFFC0);           // ADDI.L	#$00001388,$FFC0
  DEF_ROMLOC(1CE6A) : tst_mem_8(0xFFFFFFF8);        // TST.B	$FFF8
  DEF_ROMLOC(1CE6E) : if (CCR_MI) goto rom_1CE82;   // BMI.B	$1CE82
  DEF_ROMLOC(1CE70) : add_tomem_8(0x1, v_lives);    // ADDQ.B	#$01,$FE12
  DEF_ROMLOC(1CE74) : add_tomem_8(0x1, 0xFFFFFE1C); // ADDQ.B	#$01,$FE1C
  DEF_ROMLOC(1CE78)
      : move_toreg_16(BGM_EXTRALIFE, &D0); // MOVE.W
                                           // #$0088,D0
  DEF_ROMLOC(1CE7C) : play_sound();        // JMP	$0000138E
  DEF_ROMLOC(1CE82) : return;              // RTS
}
ROMFUNC(rom_1CE84) {
  DEF_ROMLOC(1CE84) : tst_mem_16(0xFFFFFFFA);         // TST.W	$FFFA
  DEF_ROMLOC(1CE88) : if (!CCR_EQ) goto rom_1CF6E;    // BNE.W	$1CF6E
  DEF_ROMLOC(1CE8C) : tst_mem_8(0xFFFFFE1F);          // TST.B	$FE1F
  DEF_ROMLOC(1CE90) : if (CCR_EQ) goto rom_1CEA4;     // BEQ.B	$1CEA4
  DEF_ROMLOC(1CE92) : clr_mem_8(0xFFFFFE1F);          // CLR.B	$FE1F
  DEF_ROMLOC(1CE96) : move_toreg_32(0x5C800003, &D0); // MOVE.L	#$5C800003,D0
  DEF_ROMLOC(1CE9C)
      : move_toreg_32(read_32(0xFFFFFE26), &D1);      // MOVE.L	$FE26,D1
  DEF_ROMLOC(1CEA0) : rom_1D0A6();                    // BSR.W	$1D0A6
  DEF_ROMLOC(1CEA4) : tst_mem_8(0xFFFFFE1D);          // TST.B	$FE1D
  DEF_ROMLOC(1CEA8) : if (CCR_EQ) goto rom_1CEC4;     // BEQ.B	$1CEC4
  DEF_ROMLOC(1CEAA) : if (CCR_PL) goto rom_1CEB0;     // BPL.B	$1CEB0
  DEF_ROMLOC(1CEAC) : rom_1CFDA();                    // BSR.W	$1CFDA
  DEF_ROMLOC(1CEB0) : clr_mem_8(0xFFFFFE1D);          // CLR.B	$FE1D
  DEF_ROMLOC(1CEB4) : move_toreg_32(0x5F400003, &D0); // MOVE.L	#$5F400003,D0
  DEF_ROMLOC(1CEBA) : move_toreg_32(0x0, &D1);        // MOVEQ.L	$00,D1
  DEF_ROMLOC(1CEBC)
      : move_toreg_16(read_16(0xFFFFFE20), &D1);      // MOVE.W	$FE20,D1
  DEF_ROMLOC(1CEC0) : rom_1D09C();                    // BSR.W	$1D09C
  DEF_ROMLOC(1CEC4) : tst_mem_8(f_timecount);         // TST.B	$FE1E
  DEF_ROMLOC(1CEC8) : if (CCR_EQ) goto rom_1CF20;     // BEQ.B	$1CF20
  DEF_ROMLOC(1CECA) : tst_mem_16(0xFFFFF63A);         // TST.W	$F63A
  DEF_ROMLOC(1CECE) : if (!CCR_EQ) goto rom_1CF20;    // BNE.B	$1CF20
  DEF_ROMLOC(1CED0) : move_toreg_32(0xFFFFFE22, &A1); // LEA.L	$FE22,A1
  DEF_ROMLOC(1CED4)
      : cmp_tomem_32(0x93B3B, (A1 += 4, A1 - 4));     // CMPI.L	#$00093B3B,(A1)+
  DEF_ROMLOC(1CEDA) : if (CCR_EQ) goto rom_1CF58;     // BEQ.B	$1CF58
  DEF_ROMLOC(1CEDC) : add_tomem_8(0x1, --A1);         // ADDQ.B	#$01,-(A1)
  DEF_ROMLOC(1CEDE) : cmp_tomem_8(0x3C, A1);          // CMPI.B	#$3C,(A1)
  DEF_ROMLOC(1CEE2) : if (CCR_CS) goto rom_1CF20;     // BCS.B	$1CF20
  DEF_ROMLOC(1CEE4) : move_tomem_8(0x0, A1);          // MOVE.B	#$00,(A1)
  DEF_ROMLOC(1CEE8) : add_tomem_8(0x1, --A1);         // ADDQ.B	#$01,-(A1)
  DEF_ROMLOC(1CEEA) : cmp_tomem_8(0x3C, A1);          // CMPI.B	#$3C,(A1)
  DEF_ROMLOC(1CEEE) : if (CCR_CS) goto rom_1CF00;     // BCS.B	$1CF00
  DEF_ROMLOC(1CEF0) : move_tomem_8(0x0, A1);          // MOVE.B	#$00,(A1)
  DEF_ROMLOC(1CEF4) : add_tomem_8(0x1, --A1);         // ADDQ.B	#$01,-(A1)
  DEF_ROMLOC(1CEF6) : cmp_tomem_8(0x9, A1);           // CMPI.B	#$09,(A1)
  DEF_ROMLOC(1CEFA) : if (CCR_CS) goto rom_1CF00;     // BCS.B	$1CF00
  DEF_ROMLOC(1CEFC) : move_tomem_8(0x9, A1);          // MOVE.B	#$09,(A1)
  DEF_ROMLOC(1CF00) : move_toreg_32(0x5E400003, &D0); // MOVE.L	#$5E400003,D0
  DEF_ROMLOC(1CF06) : move_toreg_32(0x0, &D1);        // MOVEQ.L	$00,D1
  DEF_ROMLOC(1CF08) : move_toreg_8(read_8(0xFFFFFE23), &D1); // MOVE.B	$FE23,D1
  DEF_ROMLOC(1CF0C) : rom_1D174();                           // BSR.W	$1D174
  DEF_ROMLOC(1CF10) : move_toreg_32(0x5EC00003, &D0); // MOVE.L	#$5EC00003,D0
  DEF_ROMLOC(1CF16) : move_toreg_32(0x0, &D1);        // MOVEQ.L	$00,D1
  DEF_ROMLOC(1CF18)
      : move_toreg_8(read_8(0xFFFFFE24), &D1);    // MOVE.B	$FE24,D1
  DEF_ROMLOC(1CF1C) : rom_1D17E();                // BSR.W	$1D17E
  DEF_ROMLOC(1CF20) : tst_mem_8(0xFFFFFE1C);      // TST.B	$FE1C
  DEF_ROMLOC(1CF24) : if (CCR_EQ) goto rom_1CF2E; // BEQ.B	$1CF2E
  DEF_ROMLOC(1CF26) : clr_mem_8(0xFFFFFE1C);      // CLR.B	$FE1C
  DEF_ROMLOC(1CF2A) : rom_1D23A();                // BSR.W	$1D23A
  DEF_ROMLOC(1CF2E) : tst_mem_8(0xFFFFF7D6);      // TST.B	$F7D6
  DEF_ROMLOC(1CF32) : if (CCR_EQ) goto rom_1CF56; // BEQ.B	$1CF56
  DEF_ROMLOC(1CF34) : clr_mem_8(0xFFFFF7D6);      // CLR.B	$F7D6
  DEF_ROMLOC(1CF38) : set_vram_ptr_direct(ArtTile_Bonuses * TILE_SIZE_BYTES);
  DEF_ROMLOC(1CF42) : move_toreg_32(0x0, &D1); // MOVEQ.L	$00,D1
  DEF_ROMLOC(1CF44)
      : move_toreg_16(read_16(0xFFFFF7D2), &D1); // MOVE.W	$F7D2,D1
  DEF_ROMLOC(1CF48) : rom_1D1D8();               // BSR.W	$1D1D8
  DEF_ROMLOC(1CF4C) : move_toreg_32(0x0, &D1);   // MOVEQ.L	$00,D1
  DEF_ROMLOC(1CF4E)
      : move_toreg_16(read_16(0xFFFFF7D4), &D1);      // MOVE.W	$F7D4,D1
  DEF_ROMLOC(1CF52) : rom_1D1D8();                    // BSR.W	$1D1D8
  DEF_ROMLOC(1CF56) : return;                         // RTS
  DEF_ROMLOC(1CF58) : clr_mem_8(f_timecount);         // CLR.B	$FE1E
  DEF_ROMLOC(1CF5C) : move_toreg_32(0xFFFFD000, &A0); // LEA.L	$D000,A0
  DEF_ROMLOC(1CF60) : move_toreg_32(A0, &A2);         // MOVEA.L	A0,A2
  DEF_ROMLOC(1CF62) : rom_1B84E();                    // BSR.W	$1B84E
  DEF_ROMLOC(1CF66) : move_tomem_8(0x1, 0xFFFFFE1A);  // MOVE.B	#$01,$FE1A
  DEF_ROMLOC(1CF6C) : return;                         // RTS
  DEF_ROMLOC(1CF6E) : rom_1D046();                    // BSR.W	$1D046
  DEF_ROMLOC(1CF72) : tst_mem_8(0xFFFFFE1D);          // TST.B	$FE1D
  DEF_ROMLOC(1CF76) : if (CCR_EQ) goto rom_1CF92;     // BEQ.B	$1CF92
  DEF_ROMLOC(1CF78) : if (CCR_PL) goto rom_1CF7E;     // BPL.B	$1CF7E
  DEF_ROMLOC(1CF7A) : rom_1CFDA();                    // BSR.W	$1CFDA
  DEF_ROMLOC(1CF7E) : clr_mem_8(0xFFFFFE1D);          // CLR.B	$FE1D
  DEF_ROMLOC(1CF82) : move_toreg_32(0x5F400003, &D0); // MOVE.L	#$5F400003,D0
  DEF_ROMLOC(1CF88) : move_toreg_32(0x0, &D1);        // MOVEQ.L	$00,D1
  DEF_ROMLOC(1CF8A)
      : move_toreg_16(read_16(0xFFFFFE20), &D1);      // MOVE.W	$FE20,D1
  DEF_ROMLOC(1CF8E) : rom_1D09C();                    // BSR.W	$1D09C
  DEF_ROMLOC(1CF92) : move_toreg_32(0x5EC00003, &D0); // MOVE.L	#$5EC00003,D0
  DEF_ROMLOC(1CF98) : move_toreg_32(0x0, &D1);        // MOVEQ.L	$00,D1
  DEF_ROMLOC(1CF9A)
      : move_toreg_8(read_8(0xFFFFF62C), &D1);    // MOVE.B	$F62C,D1
  DEF_ROMLOC(1CF9E) : rom_1D17E();                // BSR.W	$1D17E
  DEF_ROMLOC(1CFA2) : tst_mem_8(0xFFFFFE1C);      // TST.B	$FE1C
  DEF_ROMLOC(1CFA6) : if (CCR_EQ) goto rom_1CFB0; // BEQ.B	$1CFB0
  DEF_ROMLOC(1CFA8) : clr_mem_8(0xFFFFFE1C);      // CLR.B	$FE1C
  DEF_ROMLOC(1CFAC) : rom_1D23A();                // BSR.W	$1D23A
  DEF_ROMLOC(1CFB0) : tst_mem_8(0xFFFFF7D6);      // TST.B	$F7D6
  DEF_ROMLOC(1CFB4) : if (CCR_EQ) goto rom_1CFD8; // BEQ.B	$1CFD8
  DEF_ROMLOC(1CFB6) : clr_mem_8(0xFFFFF7D6);      // CLR.B	$F7D6
  DEF_ROMLOC(1CFBA) : set_vram_ptr_direct(ArtTile_Bonuses * TILE_SIZE_BYTES);
  DEF_ROMLOC(1CFC4) : move_toreg_32(0x0, &D1); // MOVEQ.L	$00,D1
  DEF_ROMLOC(1CFC6)
      : move_toreg_16(read_16(0xFFFFF7D2), &D1); // MOVE.W	$F7D2,D1
  DEF_ROMLOC(1CFCA) : rom_1D1D8();               // BSR.W	$1D1D8
  DEF_ROMLOC(1CFCE) : move_toreg_32(0x0, &D1);   // MOVEQ.L	$00,D1
  DEF_ROMLOC(1CFD0)
      : move_toreg_16(read_16(0xFFFFF7D4), &D1); // MOVE.W	$F7D4,D1
  DEF_ROMLOC(1CFD4) : rom_1D1D8();               // BSR.W	$1D1D8
  DEF_ROMLOC(1CFD8) : return;                    // RTS
}
ROMFUNC(rom_1CFEE) {
  DEF_ROMLOC(1CFEE)
      : move_toreg_32(VDP_DATA_PORT, &A6); // LEA.L	$00C00000,A6
  DEF_ROMLOC(1CFF4) : rom_1D23A();         // BSR.W	$1D23A
  DEF_ROMLOC(1CFF8) : set_vram_ptr_direct((ArtTile_HUD + 0x18) * TILE_SIZE_BYTES);
  DEF_ROMLOC(1D002) : move_toreg_32(0x1D036, &A2);     // LEA.L	50(PC),A2
  DEF_ROMLOC(1D006) : move_toreg_16(0xE, &D2);         // MOVE.W	#$000E,D2
  DEF_ROMLOC(1D00A) : move_toreg_32(0x1D2A6, &A1);     // LEA.L	666(PC),A1
  DEF_ROMLOC(1D00E) : move_toreg_16(0xF, &D1);         // MOVE.W	#$000F,D1
  DEF_ROMLOC(1D012) : move_toreg_8(read_8(A2++), &D0); // MOVE.B	(A2)+,D0
  DEF_ROMLOC(1D014) : if (CCR_MI) goto rom_1D02A;      // BMI.B	$1D02A
  DEF_ROMLOC(1D016) : ext_reg_16(&D0);                 // EXT.W	D0
  DEF_ROMLOC(1D018) : lsl_toreg_16(0x5, &D0);          // LSL.W	#$05,D0
  DEF_ROMLOC(1D01A)
      : move_toreg_32((s32)A1 + (s8)0x0 + (s16)D0,
                      &A3); // LEA.L	0(A1,D0),A3
  DEF_ROMLOC(1D01E) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D020) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_1D01E; // DBF.W	D1,$1D01E
  DEF_ROMLOC(1D024) : dec_reg_16(&D2);
  if ((D2 & 0xffff) != 0xffff)
    goto rom_1D00E;           // DBF.W	D2,$1D00E
  DEF_ROMLOC(1D028) : return; // RTS
  DEF_ROMLOC(1D02A) : write_vdp_data_32(0x0);
  DEF_ROMLOC(1D030) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_1D02A; // DBF.W	D1,$1D02A
  goto rom_1D024;   // BRA.B	$1D024
}
ROMFUNC(rom_1CFDA) {
  DEF_ROMLOC(1CFDA) : set_vram_ptr_direct((ArtTile_HUD + 0x30) * TILE_SIZE_BYTES);
  DEF_ROMLOC(1CFE4) : move_toreg_32(0x1D042, &A2); // LEA.L	92(PC),A2
  DEF_ROMLOC(1CFE8) : move_toreg_16(0x2, &D2);     // MOVE.W	#$0002,D2
  goto rom_1D00A;                                  // BRA.B	$1D00A
  DEF_ROMLOC(1CFEE)
      : move_toreg_32(VDP_DATA_PORT, &A6); // LEA.L	$00C00000,A6
  DEF_ROMLOC(1CFF4) : rom_1D23A();         // BSR.W	$1D23A
  DEF_ROMLOC(1CFF8) : set_vram_ptr_direct((ArtTile_HUD + 0x18) * TILE_SIZE_BYTES);
  DEF_ROMLOC(1D002) : move_toreg_32(0x1D036, &A2);     // LEA.L	50(PC),A2
  DEF_ROMLOC(1D006) : move_toreg_16(0xE, &D2);         // MOVE.W	#$000E,D2
  DEF_ROMLOC(1D00A) : move_toreg_32(0x1D2A6, &A1);     // LEA.L	666(PC),A1
  DEF_ROMLOC(1D00E) : move_toreg_16(0xF, &D1);         // MOVE.W	#$000F,D1
  DEF_ROMLOC(1D012) : move_toreg_8(read_8(A2++), &D0); // MOVE.B	(A2)+,D0
  DEF_ROMLOC(1D014) : if (CCR_MI) goto rom_1D02A;      // BMI.B	$1D02A
  DEF_ROMLOC(1D016) : ext_reg_16(&D0);                 // EXT.W	D0
  DEF_ROMLOC(1D018) : lsl_toreg_16(0x5, &D0);          // LSL.W	#$05,D0
  DEF_ROMLOC(1D01A)
      : move_toreg_32((s32)A1 + (s8)0x0 + (s16)D0,
                      &A3); // LEA.L	0(A1,D0),A3
  DEF_ROMLOC(1D01E) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D020) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_1D01E; // DBF.W	D1,$1D01E
  DEF_ROMLOC(1D024) : dec_reg_16(&D2);
  if ((D2 & 0xffff) != 0xffff)
    goto rom_1D00E;           // DBF.W	D2,$1D00E
  DEF_ROMLOC(1D028) : return; // RTS
  DEF_ROMLOC(1D02A) : write_vdp_data_32(0x0);
  DEF_ROMLOC(1D030) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_1D02A; // DBF.W	D1,$1D02A
  goto rom_1D024;   // BRA.B	$1D024
}
ROMFUNC(rom_1D046) {
  DEF_ROMLOC(1D046) : set_vram_ptr_direct((ArtTile_HUD + 0x18) * TILE_SIZE_BYTES);
  DEF_ROMLOC(1D050)
      : move_toreg_16(read_16(v_screenposx), &D1); // MOVE.W	$F700,D1
  DEF_ROMLOC(1D054) : SWAPWORDS(D1);               // SWAP.W	D1
  DEF_ROMLOC(1D056)
      : move_toreg_16(read_16(0xFFFFD008), &D1); // MOVE.W	$D008,D1
  DEF_ROMLOC(1D05A) : rom_1D066();               // BSR.B	$1D066
  DEF_ROMLOC(1D05C)
      : move_toreg_16(read_16(0xFFFFF704), &D1); // MOVE.W	$F704,D1
  DEF_ROMLOC(1D060) : SWAPWORDS(D1);             // SWAP.W	D1
  DEF_ROMLOC(1D062)
      : move_toreg_16(read_16(0xFFFFD00C), &D1); // MOVE.W	$D00C,D1
  rom_1D066();
}
ROMFUNC(rom_1D066) {
  DEF_ROMLOC(1D066) : move_toreg_32(0x7, &D6);    // MOVEQ.L	$07,D6
  DEF_ROMLOC(1D068) : move_toreg_32(0x5F0, &A1);  // LEA.L	$000005F0,A1
  DEF_ROMLOC(1D06E) : rol_toreg_16(0x4, &D1);     // ROL.W	#$04,D1
  DEF_ROMLOC(1D070) : move_toreg_16(D1, &D2);     // MOVE.W	D1,D2
  DEF_ROMLOC(1D072) : and_toreg_16(0xF, &D2);     // ANDI.W	#$000F,D2
  DEF_ROMLOC(1D076) : cmp_toreg_16(0xA, &D2);     // CMPI.W	#$000A,D2
  DEF_ROMLOC(1D07A) : if (CCR_CS) goto rom_1D07E; // BCS.B	$1D07E
  DEF_ROMLOC(1D07C) : add_toreg_16(0x7, &D2);     // ADDQ.W	#$07,D2
  DEF_ROMLOC(1D07E) : lsl_toreg_16(0x5, &D2);     // LSL.W	#$05,D2
  DEF_ROMLOC(1D080)
      : move_toreg_32((s32)A1 + (s8)0x0 + (s16)D2,
                      &A3); // LEA.L	0(A1,D2),A3
  DEF_ROMLOC(1D084) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D086) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D088) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D08A) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D08C) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D08E) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D090) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D092) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D094) : SWAPWORDS(D1); // SWAP.W	D1
  DEF_ROMLOC(1D096) : dec_reg_16(&D6);
  if ((D6 & 0xffff) != 0xffff)
    goto rom_1D06E;           // DBF.W	D6,$1D06E
  DEF_ROMLOC(1D09A) : return; // RTS
}
ROMFUNC(rom_1D09C) {
  DEF_ROMLOC(1D09C) : move_toreg_32(0x1D168, &A2); // LEA.L	$0001D168,A2
  DEF_ROMLOC(1D0A2) : move_toreg_32(0x2, &D6);     // MOVEQ.L	$02,D6
  rom_1D0AE();                                     // BRA.B	$1D0AE
}
ROMFUNC(rom_1D0A6) {
  DEF_ROMLOC(1D0A6) : move_toreg_32(0x1D15C, &A2); // LEA.L	$0001D15C,A2
  DEF_ROMLOC(1D0AC) : move_toreg_32(0x5, &D6);     // MOVEQ.L	$05,D6
  rom_1D0AE(); // Detected flow into next function
}
ROMFUNC(rom_1D0AE) {
  DEF_ROMLOC(1D0AE) : move_toreg_32(0x0, &D4);     // MOVEQ.L	$00,D4
  DEF_ROMLOC(1D0B0) : move_toreg_32(0x1D2A6, &A1); // LEA.L	500(PC),A1
  rom_1D0B4(); // Detected flow into next function
}
ROMFUNC(rom_1D0B4) {
  DEF_ROMLOC(1D0B4) : move_toreg_32(0x0, &D2); // MOVEQ.L	$00,D2
  DEF_ROMLOC(1D0B6)
      : move_toreg_32(read_32((A2 += 4, A2 - 4)), &D3); // MOVE.L	(A2)+,D3
  DEF_ROMLOC(1D0B8) : sub_toreg_32(D3, &D1);            // SUB.L	D3,D1
  DEF_ROMLOC(1D0BA) : if (CCR_CS) goto rom_1D0C0;       // BCS.B	$1D0C0
  DEF_ROMLOC(1D0BC) : add_toreg_16(0x1, &D2);           // ADDQ.W	#$01,D2
  goto rom_1D0B8;                                       // BRA.B	$1D0B8
  DEF_ROMLOC(1D0C0) : add_toreg_32(D3, &D1);            // ADD.L	D3,D1
  DEF_ROMLOC(1D0C2) : tst_reg_16(&D2);                  // TST.W	D2
  DEF_ROMLOC(1D0C4) : if (CCR_EQ) goto rom_1D0CA;       // BEQ.B	$1D0CA
  DEF_ROMLOC(1D0C6) : move_toreg_16(0x1, &D4);          // MOVE.W	#$0001,D4
  DEF_ROMLOC(1D0CA) : tst_reg_16(&D4);                  // TST.W	D4
  DEF_ROMLOC(1D0CC) : if (CCR_EQ) goto rom_1D0F8;       // BEQ.B	$1D0F8
  DEF_ROMLOC(1D0CE) : lsl_toreg_16(0x6, &D2);           // LSL.W	#$06,D2
  DEF_ROMLOC(1D0D0) : write_vdp_control_32(D0);
  DEF_ROMLOC(1D0D4)
      : move_toreg_32((s32)A1 + (s8)0x0 + (s16)D2,
                      &A3); // LEA.L	0(A1,D2),A3
  DEF_ROMLOC(1D0D8) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D0DA) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D0DC) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D0DE) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D0E0) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D0E2) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D0E4) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D0E6) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D0E8) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D0EA) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D0EC) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D0EE) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D0F0) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D0F2) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D0F4) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D0F6)
      : write_vdp_data_32(
            read_32((A3 += 4, A3 - 4)));           // MOVE.L	(A3)+,(A6)
  DEF_ROMLOC(1D0F8) : add_toreg_32(0x400000, &D0); // ADDI.L	#$00400000,D0
  DEF_ROMLOC(1D0FE) : dec_reg_16(&D6);
  if ((D6 & 0xffff) != 0xffff)
    goto rom_1D0B4;           // DBF.W	D6,$1D0B4
  DEF_ROMLOC(1D102) : return; // RTS
}
ROMFUNC(rom_1D174) {
  DEF_ROMLOC(1D174) : move_toreg_32(0x1D170, &A2); // LEA.L	$0001D170,A2
  DEF_ROMLOC(1D17A) : move_toreg_32(0x0, &D6);     // MOVEQ.L	$00,D6
  rom_1D186();                                     // BRA.B	$1D186
}
ROMFUNC(rom_1D17E) {
  DEF_ROMLOC(1D17E) : move_toreg_32(0x1D16C, &A2); // LEA.L	$0001D16C,A2
  DEF_ROMLOC(1D184) : move_toreg_32(0x1, &D6);     // MOVEQ.L	$01,D6
  rom_1D186(); // Detected flow into next function
}
ROMFUNC(rom_1D186) {
  DEF_ROMLOC(1D186) : move_toreg_32(0x0, &D4);     // MOVEQ.L	$00,D4
  DEF_ROMLOC(1D188) : move_toreg_32(0x1D2A6, &A1); // LEA.L	284(PC),A1
  rom_1D18C(); // Detected flow into next function
}
ROMFUNC(rom_1D18C) {
  DEF_ROMLOC(1D18C) : move_toreg_32(0x0, &D2); // MOVEQ.L	$00,D2
  DEF_ROMLOC(1D18E)
      : move_toreg_32(read_32((A2 += 4, A2 - 4)), &D3); // MOVE.L	(A2)+,D3
  DEF_ROMLOC(1D190) : sub_toreg_32(D3, &D1);            // SUB.L	D3,D1
  DEF_ROMLOC(1D192) : if (CCR_CS) goto rom_1D198;       // BCS.B	$1D198
  DEF_ROMLOC(1D194) : add_toreg_16(0x1, &D2);           // ADDQ.W	#$01,D2
  goto rom_1D190;                                       // BRA.B	$1D190
  DEF_ROMLOC(1D198) : add_toreg_32(D3, &D1);            // ADD.L	D3,D1
  DEF_ROMLOC(1D19A) : tst_reg_16(&D2);                  // TST.W	D2
  DEF_ROMLOC(1D19C) : if (CCR_EQ) goto rom_1D1A2;       // BEQ.B	$1D1A2
  DEF_ROMLOC(1D19E) : move_toreg_16(0x1, &D4);          // MOVE.W	#$0001,D4
  DEF_ROMLOC(1D1A2) : lsl_toreg_16(0x6, &D2);           // LSL.W	#$06,D2
  DEF_ROMLOC(1D1A4) : write_vdp_control_32(D0);
  DEF_ROMLOC(1D1A8)
      : move_toreg_32((s32)A1 + (s8)0x0 + (s16)D2,
                      &A3); // LEA.L	0(A1,D2),A3
  DEF_ROMLOC(1D1AC) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D1AE) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D1B0) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D1B2) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D1B4) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D1B6) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D1B8) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D1BA) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D1BC) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D1BE) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D1C0) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D1C2) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D1C4) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D1C6) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D1C8) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D1CA)
      : write_vdp_data_32(
            read_32((A3 += 4, A3 - 4)));           // MOVE.L	(A3)+,(A6)
  DEF_ROMLOC(1D1CC) : add_toreg_32(0x400000, &D0); // ADDI.L	#$00400000,D0
  DEF_ROMLOC(1D1D2) : dec_reg_16(&D6);
  if ((D6 & 0xffff) != 0xffff)
    goto rom_1D18C;           // DBF.W	D6,$1D18C
  DEF_ROMLOC(1D1D6) : return; // RTS
}
ROMFUNC(rom_1D1D8) {
  DEF_ROMLOC(1D1D8) : move_toreg_32(0x1D164, &A2); // LEA.L	$0001D164,A2
  DEF_ROMLOC(1D1DE) : move_toreg_32(0x3, &D6);     // MOVEQ.L	$03,D6
  DEF_ROMLOC(1D1E0) : move_toreg_32(0x0, &D4);     // MOVEQ.L	$00,D4
  DEF_ROMLOC(1D1E2) : move_toreg_32(0x1D2A6, &A1); // LEA.L	194(PC),A1
  DEF_ROMLOC(1D1E6) : move_toreg_32(0x0, &D2);     // MOVEQ.L	$00,D2
  DEF_ROMLOC(1D1E8)
      : move_toreg_32(read_32((A2 += 4, A2 - 4)), &D3); // MOVE.L	(A2)+,D3
  DEF_ROMLOC(1D1EA) : sub_toreg_32(D3, &D1);            // SUB.L	D3,D1
  DEF_ROMLOC(1D1EC) : if (CCR_CS) goto rom_1D1F2;       // BCS.B	$1D1F2
  DEF_ROMLOC(1D1EE) : add_toreg_16(0x1, &D2);           // ADDQ.W	#$01,D2
  goto rom_1D1EA;                                       // BRA.B	$1D1EA
  DEF_ROMLOC(1D1F2) : add_toreg_32(D3, &D1);            // ADD.L	D3,D1
  DEF_ROMLOC(1D1F4) : tst_reg_16(&D2);                  // TST.W	D2
  DEF_ROMLOC(1D1F6) : if (CCR_EQ) goto rom_1D1FC;       // BEQ.B	$1D1FC
  DEF_ROMLOC(1D1F8) : move_toreg_16(0x1, &D4);          // MOVE.W	#$0001,D4
  DEF_ROMLOC(1D1FC) : tst_reg_16(&D4);                  // TST.W	D4
  DEF_ROMLOC(1D1FE) : if (CCR_EQ) goto rom_1D22C;       // BEQ.B	$1D22C
  DEF_ROMLOC(1D200) : lsl_toreg_16(0x6, &D2);           // LSL.W	#$06,D2
  DEF_ROMLOC(1D202)
      : move_toreg_32((s32)A1 + (s8)0x0 + (s16)D2,
                      &A3); // LEA.L	0(A1,D2),A3
  DEF_ROMLOC(1D206) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D208) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D20A) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D20C) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D20E) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D210) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D212) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D214) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D216) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D218) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D21A) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D21C) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D21E) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D220) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D222) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D224) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D226) : dec_reg_16(&D6);
  if ((D6 & 0xffff) != 0xffff)
    goto rom_1D1E6;                            // DBF.W	D6,$1D1E6
  DEF_ROMLOC(1D22A) : return;                  // RTS
  DEF_ROMLOC(1D22C) : move_toreg_32(0xF, &D5); // MOVEQ.L	$0F,D5
  DEF_ROMLOC(1D22E) : write_vdp_data_32(0x0);
  DEF_ROMLOC(1D234) : dec_reg_16(&D5);
  if ((D5 & 0xffff) != 0xffff)
    goto rom_1D22E; // DBF.W	D5,$1D22E
  goto rom_1D226;   // BRA.B	$1D226
}
ROMFUNC(rom_1D23A) {
  DEF_ROMLOC(1D23A) : move_toreg_32(0x7BA00003, &D0); // MOVE.L	#$7BA00003,D0
  DEF_ROMLOC(1D240) : move_toreg_32(0x0, &D1);        // MOVEQ.L	$00,D1
  DEF_ROMLOC(1D242) : move_toreg_8(read_8(v_lives), &D1); // MOVE.B	$FE12,D1
  DEF_ROMLOC(1D246) : move_toreg_32(0x1D16C, &A2);        // LEA.L	$0001D16C,A2
  DEF_ROMLOC(1D24C) : move_toreg_32(0x1, &D6);            // MOVEQ.L	$01,D6
  DEF_ROMLOC(1D24E) : move_toreg_32(0x0, &D4);            // MOVEQ.L	$00,D4
  DEF_ROMLOC(1D250) : move_toreg_32(0x1D5A6, &A1);        // LEA.L	852(PC),A1
  rom_1D254(); // Detected flow into next function
}
ROMFUNC(rom_1D254) {
  DEF_ROMLOC(1D254) : write_vdp_control_32(D0);
  DEF_ROMLOC(1D258) : move_toreg_32(0x0, &D2); // MOVEQ.L	$00,D2
  DEF_ROMLOC(1D25A)
      : move_toreg_32(read_32((A2 += 4, A2 - 4)), &D3); // MOVE.L	(A2)+,D3
  DEF_ROMLOC(1D25C) : sub_toreg_32(D3, &D1);            // SUB.L	D3,D1
  DEF_ROMLOC(1D25E) : if (CCR_CS) goto rom_1D264;       // BCS.B	$1D264
  DEF_ROMLOC(1D260) : add_toreg_16(0x1, &D2);           // ADDQ.W	#$01,D2
  goto rom_1D25C;                                       // BRA.B	$1D25C
  DEF_ROMLOC(1D264) : add_toreg_32(D3, &D1);            // ADD.L	D3,D1
  DEF_ROMLOC(1D266) : tst_reg_16(&D2);                  // TST.W	D2
  DEF_ROMLOC(1D268) : if (CCR_EQ) goto rom_1D26E;       // BEQ.B	$1D26E
  DEF_ROMLOC(1D26A) : move_toreg_16(0x1, &D4);          // MOVE.W	#$0001,D4
  DEF_ROMLOC(1D26E) : tst_reg_16(&D4);                  // TST.W	D4
  DEF_ROMLOC(1D270) : if (CCR_EQ) goto rom_1D294;       // BEQ.B	$1D294
  DEF_ROMLOC(1D272) : lsl_toreg_16(0x5, &D2);           // LSL.W	#$05,D2
  DEF_ROMLOC(1D274)
      : move_toreg_32((s32)A1 + (s8)0x0 + (s16)D2,
                      &A3); // LEA.L	0(A1,D2),A3
  DEF_ROMLOC(1D278) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D27A) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D27C) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D27E) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D280) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D282) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D284) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D286)
      : write_vdp_data_32(
            read_32((A3 += 4, A3 - 4)));           // MOVE.L	(A3)+,(A6)
  DEF_ROMLOC(1D288) : add_toreg_32(0x400000, &D0); // ADDI.L	#$00400000,D0
  DEF_ROMLOC(1D28E) : dec_reg_16(&D6);
  if ((D6 & 0xffff) != 0xffff)
    goto rom_1D254;                               // DBF.W	D6,$1D254
  DEF_ROMLOC(1D292) : return;                     // RTS
  DEF_ROMLOC(1D294) : tst_reg_16(&D6);            // TST.W	D6
  DEF_ROMLOC(1D296) : if (CCR_EQ) goto rom_1D272; // BEQ.B	$1D272
  DEF_ROMLOC(1D298) : move_toreg_32(0x7, &D5);    // MOVEQ.L	$07,D5
  DEF_ROMLOC(1D29A) : write_vdp_data_32(0x0);
  DEF_ROMLOC(1D2A0) : dec_reg_16(&D5);
  if ((D5 & 0xffff) != 0xffff)
    goto rom_1D29A; // DBF.W	D5,$1D29A
  goto rom_1D288;   // BRA.B	$1D288
}