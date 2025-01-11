#include "opcodes.h"
#include "system.h"

ROMFUNC(rom_3168);
ROMFUNC(rom_327C);
ROMFUNC(rom_33B4);
ROMFUNC(rom_2F04);
ROMFUNC(rom_2FC2);
ROMFUNC(rom_3076);

ROMFUNC(rom_2EF4) {
  SR = 0x2700;
  DEF_ROMLOC(2EF4) : move_toreg_8(0xFFFFFFE4, &D0); // MOVE.B	#$E4,D0
  DEF_ROMLOC(2EF8) : play_sound_special();          // BSR.W	$1394
  DEF_ROMLOC(2EFC) : clear_plc();                    // BSR.W	$15D6
  DEF_ROMLOC(2F00) : game_state = rom_2F04;
  palette_fade_out(); // BSR.W	$1E4A
}
ROMFUNC(rom_2F04) {
  DEF_ROMLOC(2F04) : move_tosr_16(0x2700, &SR);            // MOVE.W	#$2700,SR
  DEF_ROMLOC(2F0C) : move_toreg_32(0xC00004, &A6);         // LEA.L	$00C00004,A6
  DEF_ROMLOC(2F12) : move_tomem_16(0xFFFF8004, A6);        // MOVE.W	#$8004,(A6)
  DEF_ROMLOC(2F16) : move_tomem_16(0xFFFF8230, A6);        // MOVE.W	#$8230,(A6)
  DEF_ROMLOC(2F1A) : move_tomem_16(0xFFFF8407, A6);        // MOVE.W	#$8407,(A6)
  DEF_ROMLOC(2F1E) : move_tomem_16(0xFFFF9001, A6);        // MOVE.W	#$9001,(A6)
  DEF_ROMLOC(2F22) : move_tomem_16(0xFFFF9200, A6);        // MOVE.W	#$9200,(A6)
  DEF_ROMLOC(2F26) : move_tomem_16(0xFFFF8B03, A6);        // MOVE.W	#$8B03,(A6)
  DEF_ROMLOC(2F2A) : move_tomem_16(0xFFFF8720, A6);        // MOVE.W	#$8720,(A6)
  DEF_ROMLOC(2F2E) : clr_mem_8(0xFFFFF64E);                // CLR.B	$F64E
  DEF_ROMLOC(2F32) : clear_screen();                           // BSR.W	$12C4
  DEF_ROMLOC(2F36) : move_toreg_32(0xFFFFD000, &A1);       // LEA.L	$D000,A1
  DEF_ROMLOC(2F3A) : move_toreg_32(0x0, &D0);              // MOVEQ.L	$00,D0
  DEF_ROMLOC(2F3C) : move_toreg_16(0x7FF, &D1);            // MOVE.W	#$07FF,D1
  DEF_ROMLOC(2F40) : move_tomem_32(D0, (A1 += 4, A1 - 4)); // MOVE.L	D0,(A1)+
  DEF_ROMLOC(2F42) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_2F40; // DBF.W	D1,$2F40
  DEF_ROMLOC(2F46)
      : move_tomem_32(0x40000000, 0xC00004);      // MOVE.L	#$40000000,$00C00004
  DEF_ROMLOC(2F50) : move_toreg_32(0x2184C, &A0); // LEA.L	$0002184C,A0
  DEF_ROMLOC(2F56) : decompress_nemesis();                  // BSR.W	$1438
  DEF_ROMLOC(2F5A)
      : move_tomem_32(0x54C00000, 0xC00004);      // MOVE.L	#$54C00000,$00C00004
  DEF_ROMLOC(2F64) : move_toreg_32(0x6203A, &A0); // LEA.L	$0006203A,A0
  DEF_ROMLOC(2F6A) : decompress_nemesis();                  // BSR.W	$1438
  DEF_ROMLOC(2F6E) : move_toreg_32(v_256x256, &A1);  // LEA.L	$00FF0000,A1
  DEF_ROMLOC(2F74) : move_toreg_32(0x2178E, &A0);    // LEA.L	$0002178E,A0
  DEF_ROMLOC(2F7A) : move_toreg_16(0x0, &D0);        // MOVE.W	#$0000,D0
  DEF_ROMLOC(2F7E) : decompress_enigma();                     // BSR.W	$1716
  DEF_ROMLOC(2F82) : move_toreg_32(v_256x256, &A1);  // LEA.L	$00FF0000,A1
  DEF_ROMLOC(2F88) : move_toreg_32(0x40000003, &D0); // MOVE.L	#$40000003,D0
  DEF_ROMLOC(2F8E) : move_toreg_32(0x27, &D1);       // MOVEQ.L	$27,D1
  DEF_ROMLOC(2F90) : move_toreg_32(0x1B, &D2);       // MOVEQ.L	$1B,D2
  DEF_ROMLOC(2F92) : copy_tilemap_to_vram();         // BSR.W	$1418
  DEF_ROMLOC(2F96) : move_toreg_32(0xFFFFFB80, &A1); // LEA.L	$FB80,A1
  DEF_ROMLOC(2F9A) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(2F9C) : move_toreg_16(0x1F, &D1);       // MOVE.W	#$001F,D1
  DEF_ROMLOC(2FA0) : move_tomem_32(D0, (A1 += 4, A1 - 4)); // MOVE.L	D0,(A1)+
  DEF_ROMLOC(2FA2) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_2FA0;                                         // DBF.W	D1,$2FA0
  DEF_ROMLOC(2FA6) : move_toreg_32(0x3, &D0);              // MOVEQ.L	$03,D0
  DEF_ROMLOC(2FA8) : load_palette_fading();                // BSR.W	$20F4
  DEF_ROMLOC(2FAC) : move_tomem_8(0xFFFFFF8A, 0xFFFFD080); // MOVE.B
                                                           // #$8A,$D080
  DEF_ROMLOC(2FB2) : rom_D9C6();                           // JSR	$0000D9C6
  DEF_ROMLOC(2FB8) : rom_DCEC();                           // JSR	$0000DCEC
  DEF_ROMLOC(2FBE) : game_state = rom_2FC2;
  palette_fade_in(true); // BSR.W	$1DA4
}
ROMFUNC(rom_2FC2) {
  DEF_ROMLOC(2FC2) : move_tosr_16(0x2700, &SR); // MOVE.W	#$2700,SR
  DEF_ROMLOC(2FC6)
      : move_tomem_32(0x40000001, 0xC00004);      // MOVE.L	#$40000001,$00C00004
  DEF_ROMLOC(2FD0) : move_toreg_32(0x1ED80, &A0); // LEA.L	$0001ED80,A0
  DEF_ROMLOC(2FD6) : decompress_nemesis();                  // BSR.W	$1438
  DEF_ROMLOC(2FDA)
      : move_tomem_32(0x60000001, 0xC00004);      // MOVE.L	#$60000001,$00C00004
  DEF_ROMLOC(2FE4) : move_toreg_32(0x1FD8C, &A0); // LEA.L	$0001FD8C,A0
  DEF_ROMLOC(2FEA) : decompress_nemesis();                  // BSR.W	$1438
  DEF_ROMLOC(2FEE)
      : move_tomem_32(0x62000002, 0xC00004);      // MOVE.L	#$62000002,$00C00004
  DEF_ROMLOC(2FF8) : move_toreg_32(0x2175A, &A0); // LEA.L	$0002175A,A0
  DEF_ROMLOC(2FFE) : decompress_nemesis();                  // BSR.W	$1438
  DEF_ROMLOC(3002) : move_toreg_32(0xC00000, &A6); // LEA.L	$00C00000,A6
  DEF_ROMLOC(3008)
      : move_tomem_32(0x50000003, A6 + 0x4);    // MOVE.L	#$50000003,4(A6)
  DEF_ROMLOC(3010) : move_toreg_32(0x5F0, &A5); // LEA.L	$000005F0,A5
  DEF_ROMLOC(3016) : move_toreg_16(0x28F, &D1); // MOVE.W	#$028F,D1
  rom_301A(); // Detected flow into next function
}
ROMFUNC(rom_301A) {
  DEF_ROMLOC(301A)
      : move_tomem_16(read_16((A5 += 2, A5 - 2)),
                      A6); // MOVE.W	(A5)+,(A6)
  DEF_ROMLOC(301C) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_301A;                                   // DBF.W	D1,$301A
  DEF_ROMLOC(3020) : move_tomem_8(0x0, 0xFFFFFE30);  // MOVE.B	#$00,$FE30
  DEF_ROMLOC(3026) : move_tomem_16(0x0, 0xFFFFFE08); // MOVE.W	#$0000,$FE08
  DEF_ROMLOC(302C) : move_tomem_16(0x0, 0xFFFFFFF0); // MOVE.W	#$0000,$FFF0
  DEF_ROMLOC(3032) : move_tomem_16(0x0, 0xFFFFFFEA); // MOVE.W	#$0000,$FFEA
  DEF_ROMLOC(3038) : move_tomem_16(0x0, 0xFFFFFE10); // MOVE.W	#$0000,$FE10
  DEF_ROMLOC(303E) : move_tomem_16(0x0, 0xFFFFF634); // MOVE.W	#$0000,$F634
  DEF_ROMLOC(3044) : rom_5ECC();                     // BSR.W	$5ECC
  DEF_ROMLOC(3048) : rom_626E();                     // BSR.W	$626E
  DEF_ROMLOC(304C) : move_toreg_32(v_16x16, &A1);    // LEA.L	$B000,A1
  DEF_ROMLOC(3050) : move_toreg_32(0x3C19C, &A0);    // LEA.L	$0003C19C,A0
  DEF_ROMLOC(3056) : move_toreg_16(0x0, &D0);        // MOVE.W	#$0000,D0
  DEF_ROMLOC(305A) : decompress_enigma();                     // BSR.W	$1716
  DEF_ROMLOC(305E) : move_toreg_32(0x3F544, &A0);    // LEA.L	$0003F544,A0
  DEF_ROMLOC(3064) : move_toreg_32(v_256x256, &A1);  // LEA.L	$00FF0000,A1
  DEF_ROMLOC(306A) : rom_1894();                     // BSR.W	$1894
  DEF_ROMLOC(306E) : rom_735C();                     // BSR.W	$735C
  DEF_ROMLOC(3072) : game_state = rom_3076;
  palette_fade_out(); // BSR.W	$1E4A
}
ROMFUNC(rom_3076) {
  DEF_ROMLOC(3076) : move_tosr_16(0x2700, &SR);      // MOVE.W	#$2700,SR
  DEF_ROMLOC(307A) : clear_screen();                     // BSR.W	$12C4
  DEF_ROMLOC(307E) : move_toreg_32(0xC00004, &A5);   // LEA.L	$00C00004,A5
  DEF_ROMLOC(3084) : move_toreg_32(0xC00000, &A6);   // LEA.L	$00C00000,A6
  DEF_ROMLOC(308A) : move_toreg_32(0xFFFFF708, &A3); // LEA.L	$F708,A3
  DEF_ROMLOC(308E) : move_toreg_32(0xFFFFA440, &A4); // LEA.L	$A440,A4
  DEF_ROMLOC(3092) : move_toreg_16(0x6000, &D2);     // MOVE.W	#$6000,D2
  DEF_ROMLOC(3096) : rom_71F8();                     // BSR.W	$71F8
  DEF_ROMLOC(309A) : move_toreg_32(v_256x256, &A1);  // LEA.L	$00FF0000,A1
  DEF_ROMLOC(30A0) : move_toreg_32(0x1EC6C, &A0);    // LEA.L	$0001EC6C,A0
  DEF_ROMLOC(30A6) : move_toreg_16(0x0, &D0);        // MOVE.W	#$0000,D0
  DEF_ROMLOC(30AA) : decompress_enigma();                     // BSR.W	$1716
  DEF_ROMLOC(30AE) : move_toreg_32(v_256x256, &A1);  // LEA.L	$00FF0000,A1
  DEF_ROMLOC(30B4) : move_toreg_32(0x42060003, &D0); // MOVE.L	#$42060003,D0
  DEF_ROMLOC(30BA) : move_toreg_32(0x21, &D1);       // MOVEQ.L	$21,D1
  DEF_ROMLOC(30BC) : move_toreg_32(0x15, &D2);       // MOVEQ.L	$15,D2
  DEF_ROMLOC(30BE) : copy_tilemap_to_vram();         // BSR.W	$1418
  DEF_ROMLOC(30C2)
      : move_tomem_32(0x40000000, 0xC00004);      // MOVE.L	#$40000000,$00C00004
  DEF_ROMLOC(30CC) : move_toreg_32(0x3CB3C, &A0); // LEA.L	$0003CB3C,A0
  DEF_ROMLOC(30D2) : decompress_nemesis();                  // BSR.W	$1438
  DEF_ROMLOC(30D6) : move_toreg_32(0x1, &D0);     // MOVEQ.L	$01,D0
  DEF_ROMLOC(30D8) : load_palette_fading();       // BSR.W	$20F4
  DEF_ROMLOC(30DC) : move_toreg_8(0xFFFFFF8A, &D0); // MOVE.B	#$8A,D0
  DEF_ROMLOC(30E0) : play_sound_special();          // BSR.W	$1394
  DEF_ROMLOC(30E4) : move_tomem_8(0x0, 0xFFFFFFFA); // MOVE.B	#$00,$FFFA
  DEF_ROMLOC(30EA)
      : move_tomem_16(0x178, 0xFFFFF614);                  // MOVE.W
                                                           // #$0178,$F614
  DEF_ROMLOC(30F0) : move_toreg_32(0xFFFFD080, &A1);       // LEA.L	$D080,A1
  DEF_ROMLOC(30F4) : move_toreg_32(0x0, &D0);              // MOVEQ.L	$00,D0
  DEF_ROMLOC(30F6) : move_toreg_16(0x7, &D1);              // MOVE.W	#$0007,D1
  DEF_ROMLOC(30FA) : move_tomem_32(D0, (A1 += 4, A1 - 4)); // MOVE.L	D0,(A1)+
  DEF_ROMLOC(30FC) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_30FA;                                   // DBF.W	D1,$30FA
  DEF_ROMLOC(3100) : move_tomem_8(0xE, 0xFFFFD040);  // MOVE.B	#$0E,$D040
  DEF_ROMLOC(3106) : move_tomem_8(0xF, 0xFFFFD080);  // MOVE.B	#$0F,$D080
  DEF_ROMLOC(310C) : tst_mem_8(0xFFFFFFF8);          // TST.B	$FFF8
  DEF_ROMLOC(3110) : if (CCR_PL) goto rom_311E;      // BPL.B	$311E
  DEF_ROMLOC(3112) : move_tomem_8(0xF, 0xFFFFD0C0);  // MOVE.B	#$0F,$D0C0
  DEF_ROMLOC(3118) : move_tomem_8(0x3, 0xFFFFD0DA);  // MOVE.B	#$03,$D0DA
  DEF_ROMLOC(311E) : move_tomem_8(0xF, 0xFFFFD100);  // MOVE.B	#$0F,$D100
  DEF_ROMLOC(3124) : move_tomem_8(0x2, 0xFFFFD11A);  // MOVE.B	#$02,$D11A
  DEF_ROMLOC(312A) : rom_D9C6();                     // JSR	$0000D9C6
  DEF_ROMLOC(3130) : rom_626E();                     // BSR.W	$626E
  DEF_ROMLOC(3134) : rom_DCEC();                     // JSR	$0000DCEC
  DEF_ROMLOC(313A) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(313C) : rom_15AA();                     // BSR.W	$15AA
  DEF_ROMLOC(3140) : move_tomem_16(0x0, 0xFFFFFFE4); // MOVE.W	#$0000,$FFE4
  DEF_ROMLOC(3146) : move_tomem_16(0x0, 0xFFFFFFE6); // MOVE.W	#$0000,$FFE6
  DEF_ROMLOC(314C)
      : move_toreg_16(read_16(0xFFFFF60C), &D0);  // MOVE.W	$F60C,D0
  DEF_ROMLOC(3150) : or_toreg_8(0x40, &D0);       // ORI.B	#$40,D0
  DEF_ROMLOC(3154) : move_tomem_16(D0, 0xC00004); // MOVE.W	D0,$00C00004
  DEF_ROMLOC(315A) : game_state = rom_315E;
  palette_fade_in(true); // BSR.W	$1DA4
}
ROMFUNC(rom_315E) {
  end_frame(0x4);
  game_state = rom_3168;
}
void level_palette_cycle_ghz(bool title_screen);
ROMFUNC(rom_3168) {
  DEF_ROMLOC(3168) : rom_D9C6();                    // JSR	$0000D9C6
  DEF_ROMLOC(316E) : rom_626E();                    // BSR.W	$626E
  DEF_ROMLOC(3172) : rom_DCEC();                    // JSR	$0000DCEC
  DEF_ROMLOC(3178) : level_palette_cycle_ghz(true); // BSR.W	$1954
  DEF_ROMLOC(317C) : rom_15E4();                    // BSR.W	$15E4
  DEF_ROMLOC(3180)
      : move_toreg_16(read_16(0xFFFFD008), &D0);    // MOVE.W	$D008,D0
  DEF_ROMLOC(3184) : add_toreg_16(0x2, &D0);        // ADDQ.W	#$02,D0
  DEF_ROMLOC(3186) : move_tomem_16(D0, 0xFFFFD008); // MOVE.W	D0,$D008
  DEF_ROMLOC(318A) : cmp_toreg_16(0x1C00, &D0);     // CMPI.W	#$1C00,D0
  DEF_ROMLOC(318E) : if (CCR_CS) goto rom_3198;     // BCS.B	$3198
  DEF_ROMLOC(3190) : SET_GM_SEGA();
  DEF_ROMLOC(3196) : return;                     // RTS
  DEF_ROMLOC(3198) : tst_mem_8(0xFFFFFFF8);      // TST.B	$FFF8
  DEF_ROMLOC(319C) : if (CCR_PL) goto rom_31A6;  // BPL.B	$31A6
  DEF_ROMLOC(319E) : move_toreg_32(0x339E, &A0); // LEA.L	$0000339E,A0
  goto rom_31AC;                                 // BRA.B	$31AC
  DEF_ROMLOC(31A6) : move_toreg_32(0x3396, &A0); // LEA.L	$00003396,A0
  DEF_ROMLOC(31AC)
      : move_toreg_16(read_16(0xFFFFFFE4), &D0);            // MOVE.W	$FFE4,D0
  DEF_ROMLOC(31B0) : add_toreg_16(D0, &A0);                 // ADDA.W	D0,A0
  DEF_ROMLOC(31B2) : move_toreg_8(read_8(0xFFFFF605), &D0); // MOVE.B	$F605,D0
  DEF_ROMLOC(31B6) : and_toreg_8(0xF, &D0);                 // ANDI.B	#$0F,D0
  DEF_ROMLOC(31BA) : cmp_toreg_8(read_8(A0), &D0);          // CMP.B	(A0),D0
  DEF_ROMLOC(31BC) : if (!CCR_EQ) goto rom_31F2;            // BNE.B	$31F2
  DEF_ROMLOC(31BE) : add_tomem_16(0x1, 0xFFFFFFE4);         // ADDQ.W	#$01,$FFE4
  DEF_ROMLOC(31C2) : tst_reg_8(&D0);                        // TST.B	D0
  DEF_ROMLOC(31C4) : if (!CCR_EQ) goto rom_3204;            // BNE.B	$3204
  DEF_ROMLOC(31C6) : move_toreg_32(0xFFFFFFE0, &A0);        // LEA.L	$FFE0,A0
  DEF_ROMLOC(31CA)
      : move_toreg_16(read_16(0xFFFFFFE6), &D1); // MOVE.W	$FFE6,D1
  DEF_ROMLOC(31CE) : lsr_toreg_16(0x1, &D1);     // LSR.W	#$01,D1
  DEF_ROMLOC(31D0) : and_toreg_16(0x3, &D1);     // ANDI.W	#$0003,D1
  DEF_ROMLOC(31D4) : if (CCR_EQ) goto rom_31E2;  // BEQ.B	$31E2
  DEF_ROMLOC(31D6) : tst_mem_8(0xFFFFFFF8);      // TST.B	$FFF8
  DEF_ROMLOC(31DA) : if (CCR_PL) goto rom_31E2;  // BPL.B	$31E2
  DEF_ROMLOC(31DC) : move_toreg_32(0x1, &D1);    // MOVEQ.L	$01,D1
  DEF_ROMLOC(31DE)
      : move_tomem_8(D1,
                     (s32)A0 + (s8)0x1 + (s16)D1); // MOVE.B	D1,1(A0,D1)
  DEF_ROMLOC(31E2)
      : move_tomem_8(0x1,
                     (s32)A0 + (s8)0x0 + (s16)D1);   // MOVE.B	#$01,0(A0,D1)
  DEF_ROMLOC(31E8) : move_toreg_8(0xFFFFFFB5, &D0);  // MOVE.B	#$B5,D0
  DEF_ROMLOC(31EC) : play_sound_special();           // BSR.W	$1394
  goto rom_3204;                                     // BRA.B	$3204
  DEF_ROMLOC(31F2) : tst_reg_8(&D0);                 // TST.B	D0
  DEF_ROMLOC(31F4) : if (CCR_EQ) goto rom_3204;      // BEQ.B	$3204
  DEF_ROMLOC(31F6) : cmp_tomem_16(0x9, 0xFFFFFFE4);  // CMPI.W	#$0009,$FFE4
  DEF_ROMLOC(31FC) : if (CCR_EQ) goto rom_3204;      // BEQ.B	$3204
  DEF_ROMLOC(31FE) : move_tomem_16(0x0, 0xFFFFFFE4); // MOVE.W	#$0000,$FFE4
  DEF_ROMLOC(3204) : move_toreg_8(read_8(0xFFFFF605), &D0); // MOVE.B	$F605,D0
  DEF_ROMLOC(3208) : and_toreg_8(0x20, &D0);                // ANDI.B	#$20,D0
  DEF_ROMLOC(320C) : if (CCR_EQ) goto rom_3212;             // BEQ.B	$3212
  DEF_ROMLOC(320E) : add_tomem_16(0x1, 0xFFFFFFE6);         // ADDQ.W	#$01,$FFE6
  DEF_ROMLOC(3212) : tst_mem_16(0xFFFFF614);                // TST.W	$F614
  DEF_ROMLOC(3216) : if (CCR_EQ) {
    rom_33A4();
    return;
  }                                                       // BEQ.W	$33A4
  DEF_ROMLOC(321A) : and_tomem_8(0xFFFFFF80, 0xFFFFF605); // ANDI.B
                                                          // #$80,$F605
  DEF_ROMLOC(3220) : if (CCR_EQ) {
    rom_315E();
    return;
  } // BEQ.W	$315E
  rom_3224();
}
ROMFUNC(rom_3224) {
  DEF_ROMLOC(3224) : tst_mem_8(0xFFFFFFE0); // TST.B	$FFE0
  DEF_ROMLOC(3228) : if (CCR_EQ) {
    rom_332C();
    return;
  }                                                 // BEQ.W	$332C
  DEF_ROMLOC(322C) : btst_tomem_8(0x6, 0xFFFFF604); // BTST.B	#$06,$F604
  DEF_ROMLOC(3232) : if (CCR_EQ) {
    rom_332C();
    return;
  }                                                        // BEQ.W	$332C
  DEF_ROMLOC(3236) : move_toreg_32(0x2, &D0);              // MOVEQ.L	$02,D0
  DEF_ROMLOC(3238) : load_palette();                       // BSR.W	$2110
  DEF_ROMLOC(323C) : move_toreg_32(0xFFFFCC00, &A1);       // LEA.L	$CC00,A1
  DEF_ROMLOC(3240) : move_toreg_32(0x0, &D0);              // MOVEQ.L	$00,D0
  DEF_ROMLOC(3242) : move_toreg_16(0xDF, &D1);             // MOVE.W	#$00DF,D1
  DEF_ROMLOC(3246) : move_tomem_32(D0, (A1 += 4, A1 - 4)); // MOVE.L	D0,(A1)+
  DEF_ROMLOC(3248) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_3246;                                  // DBF.W	D1,$3246
  DEF_ROMLOC(324C) : move_tomem_32(D0, 0xFFFFF616); // MOVE.L	D0,$F616
  DEF_ROMLOC(3250) : move_tosr_16(0x2700, &SR);     // MOVE.W	#$2700,SR
  DEF_ROMLOC(3254) : move_toreg_32(0xC00000, &A6);  // LEA.L	$00C00000,A6
  DEF_ROMLOC(325A)
      : move_tomem_32(0x60000003, 0xC00004);    // MOVE.L	#$60000003,$00C00004
  DEF_ROMLOC(3264) : move_toreg_16(0x3FF, &D1); // MOVE.W	#$03FF,D1
  DEF_ROMLOC(3268) : move_tomem_32(D0, A6);     // MOVE.L	D0,(A6)
  DEF_ROMLOC(326A) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_3268;               // DBF.W	D1,$3268
  DEF_ROMLOC(326E) : rom_34E2(); // BSR.W	$34E2
  rom_3272();
}
ROMFUNC(rom_3272) {
  end_frame(0x4);
  game_state = rom_327C;
}
ROMFUNC(rom_327C) {
  DEF_ROMLOC(327C) : rom_345C();               // BSR.W	$345C
  DEF_ROMLOC(3280) : rom_15E4();               // BSR.W	$15E4
  DEF_ROMLOC(3284) : tst_mem_32(v_plc_buffer); // TST.L	$F680
  DEF_ROMLOC(3288) : if (!CCR_EQ) {
    rom_3272();
    return;
  }                                                       // BNE.B	$3272
  DEF_ROMLOC(328A) : and_tomem_8(0xFFFFFFF0, 0xFFFFF605); // ANDI.B
                                                          // #$F0,$F605
  DEF_ROMLOC(3290) : if (CCR_EQ) {
    rom_3272();
    return;
  } // BEQ.B	$3272
  DEF_ROMLOC(3292)
      : move_toreg_16(read_16(0xFFFFFF82), &D0); // MOVE.W	$FF82,D0
  DEF_ROMLOC(3296) : cmp_toreg_16(0x14, &D0);    // CMPI.W	#$0014,D0
  DEF_ROMLOC(329A) : if (!CCR_EQ) goto rom_32EC; // BNE.B	$32EC
  DEF_ROMLOC(329C)
      : move_toreg_16(read_16(0xFFFFFF84), &D0); // MOVE.W	$FF84,D0
  DEF_ROMLOC(32A0) : add_toreg_16(0x80, &D0);    // ADDI.W	#$0080,D0
  DEF_ROMLOC(32A4) : tst_mem_8(0xFFFFFFE3);      // TST.B	$FFE3
  DEF_ROMLOC(32A8) : if (CCR_EQ) goto rom_32B6;  // BEQ.B	$32B6
  DEF_ROMLOC(32AA) : cmp_toreg_16(0x9F, &D0);    // CMPI.W	#$009F,D0
  DEF_ROMLOC(32AE) : if (CCR_EQ) goto rom_32C8;  // BEQ.B	$32C8
  DEF_ROMLOC(32B0) : cmp_toreg_16(0x9E, &D0);    // CMPI.W	#$009E,D0
  DEF_ROMLOC(32B4) : if (CCR_EQ) goto rom_32D6;  // BEQ.B	$32D6
  DEF_ROMLOC(32B6) : cmp_toreg_16(0x94, &D0);    // CMPI.W	#$0094,D0
  DEF_ROMLOC(32BA) : if (CCR_CS) goto rom_32C2;  // BCS.B	$32C2
  DEF_ROMLOC(32BC) : cmp_toreg_16(0xA0, &D0);    // CMPI.W	#$00A0,D0
  DEF_ROMLOC(32C0) : if (CCR_CS) {
    rom_3272();
    return;
  }                                        // BCS.B	$3272
  DEF_ROMLOC(32C2) : play_sound_special(); // BSR.W	$1394
  {
    rom_3272();
    return;
  } // BRA.B	$3272
  DEF_ROMLOC(32C8) : SET_GM_ENDING();
  DEF_ROMLOC(32CE)
      : move_tomem_16(0x600, 0xFFFFFE10); // MOVE.W
                                          // #$0600,$FE10
  DEF_ROMLOC(32D4) : return;              // RTS
  DEF_ROMLOC(32D6) : SET_GM_CREDITS();
  DEF_ROMLOC(32DC) : move_toreg_8(0xFFFFFF91, &D0);  // MOVE.B	#$91,D0
  DEF_ROMLOC(32E0) : play_sound_special();           // BSR.W	$1394
  DEF_ROMLOC(32E4) : move_tomem_16(0x0, 0xFFFFFFF4); // MOVE.W	#$0000,$FFF4
  DEF_ROMLOC(32EA) : return;                         // RTS
  DEF_ROMLOC(32EC) : add_toreg_16(D0, &D0);          // ADD.W	D0,D0
  DEF_ROMLOC(32EE)
      : move_toreg_16(read_16(0x336C + (s16)(D0 & 0xffff)),
                      &D0); // MOVE.W	124(PC,D0),D0
  DEF_ROMLOC(32F2) : if (CCR_MI) {
    rom_3272();
    return;
  }                                              // BMI.W	$3272
  DEF_ROMLOC(32F6) : cmp_toreg_16(0x700, &D0);   // CMPI.W	#$0700,D0
  DEF_ROMLOC(32FA) : if (!CCR_EQ) goto rom_3324; // BNE.B	$3324
  DEF_ROMLOC(32FC) : SET_GM_SPECIAL();
  DEF_ROMLOC(3302) : clr_mem_16(0xFFFFFE10);        // CLR.W	$FE10
  DEF_ROMLOC(3306) : move_tomem_8(0x3, 0xFFFFFE12); // MOVE.B	#$03,$FE12
  DEF_ROMLOC(330C) : move_toreg_32(0x0, &D0);       // MOVEQ.L	$00,D0
  DEF_ROMLOC(330E) : move_tomem_16(D0, 0xFFFFFE20); // MOVE.W	D0,$FE20
  DEF_ROMLOC(3312) : move_tomem_32(D0, 0xFFFFFE22); // MOVE.L	D0,$FE22
  DEF_ROMLOC(3316) : move_tomem_32(D0, 0xFFFFFE26); // MOVE.L	D0,$FE26
  DEF_ROMLOC(331A)
      : move_tomem_32(0x1388, 0xFFFFFFC0);          // MOVE.L	#$00001388,$FFC0
  DEF_ROMLOC(3322) : return;                        // RTS
  DEF_ROMLOC(3324) : and_toreg_16(0x3FFF, &D0);     // ANDI.W	#$3FFF,D0
  DEF_ROMLOC(3328) : move_tomem_16(D0, 0xFFFFFE10); // MOVE.W	D0,$FE10
  rom_332C();
}
ROMFUNC(rom_332C) {
  DEF_ROMLOC(332C) : SET_GM_LEVEL();
  DEF_ROMLOC(3332) : move_tomem_8(0x3, 0xFFFFFE12); // MOVE.B	#$03,$FE12
  DEF_ROMLOC(3338) : move_toreg_32(0x0, &D0);       // MOVEQ.L	$00,D0
  DEF_ROMLOC(333A) : move_tomem_16(D0, 0xFFFFFE20); // MOVE.W	D0,$FE20
  DEF_ROMLOC(333E) : move_tomem_32(D0, 0xFFFFFE22); // MOVE.L	D0,$FE22
  DEF_ROMLOC(3342) : move_tomem_32(D0, 0xFFFFFE26); // MOVE.L	D0,$FE26
  DEF_ROMLOC(3346) : move_tomem_8(D0, 0xFFFFFE16);  // MOVE.B	D0,$FE16
  DEF_ROMLOC(334A) : move_tomem_8(D0, 0xFFFFFE57);  // MOVE.B	D0,$FE57
  DEF_ROMLOC(334E) : move_tomem_32(D0, 0xFFFFFE58); // MOVE.L	D0,$FE58
  DEF_ROMLOC(3352) : move_tomem_32(D0, 0xFFFFFE5C); // MOVE.L	D0,$FE5C
  DEF_ROMLOC(3356) : move_tomem_8(D0, 0xFFFFFE18);  // MOVE.B	D0,$FE18
  DEF_ROMLOC(335A)
      : move_tomem_32(0x1388, 0xFFFFFFC0);          // MOVE.L	#$00001388,$FFC0
  DEF_ROMLOC(3362) : move_toreg_8(0xFFFFFFE0, &D0); // MOVE.B	#$E0,D0
  DEF_ROMLOC(3366) : play_sound_special();          // BSR.W	$1394
  DEF_ROMLOC(336A) : return;                        // RTS
}
ROMFUNC(rom_33A4) {
  DEF_ROMLOC(33A4) : move_tomem_16(0x1E, 0xFFFFF614); // MOVE.W	#$001E,$F614
  rom_33AA();
}
ROMFUNC(rom_33AA) {
  end_frame(0x4);
  game_state = rom_33B4;
}
void level_palette_cycle(void);
ROMFUNC(rom_33B4) {
  DEF_ROMLOC(33B4) : rom_626E();            // BSR.W	$626E
  DEF_ROMLOC(33B8) : level_palette_cycle(); // BSR.W	$1934
  DEF_ROMLOC(33BC) : rom_15E4();            // BSR.W	$15E4
  DEF_ROMLOC(33C0)
      : move_toreg_16(read_16(0xFFFFD008), &D0);    // MOVE.W	$D008,D0
  DEF_ROMLOC(33C4) : add_toreg_16(0x2, &D0);        // ADDQ.W	#$02,D0
  DEF_ROMLOC(33C6) : move_tomem_16(D0, 0xFFFFD008); // MOVE.W	D0,$D008
  DEF_ROMLOC(33CA) : cmp_toreg_16(0x1C00, &D0);     // CMPI.W	#$1C00,D0
  DEF_ROMLOC(33CE) : if (CCR_CS) goto rom_33D8;     // BCS.B	$33D8
  DEF_ROMLOC(33D0) : SET_GM_SEGA();
  DEF_ROMLOC(33D6) : return;                              // RTS
  DEF_ROMLOC(33D8) : and_tomem_8(0xFFFFFF80, 0xFFFFF605); // ANDI.B
                                                          // #$80,$F605
  DEF_ROMLOC(33DE) : if (!CCR_EQ) {
    rom_3224();
    return;
  }                                          // BNE.W	$3224
  DEF_ROMLOC(33E2) : tst_mem_16(0xFFFFF614); // TST.W	$F614
  DEF_ROMLOC(33E6) : if (!CCR_EQ) {
    rom_33AA();
    return;
  }                                                 // BNE.W	$33AA
  DEF_ROMLOC(33EA) : move_toreg_8(0xFFFFFFE0, &D0); // MOVE.B	#$E0,D0
  DEF_ROMLOC(33EE) : play_sound_special();          // BSR.W	$1394
  DEF_ROMLOC(33F2)
      : move_toreg_16(read_16(0xFFFFFFF2), &D0); // MOVE.W	$FFF2,D0
  DEF_ROMLOC(33F6) : and_toreg_16(0x7, &D0);     // ANDI.W	#$0007,D0
  DEF_ROMLOC(33FA) : add_toreg_16(D0, &D0);      // ADD.W	D0,D0
  DEF_ROMLOC(33FC)
      : move_toreg_16(read_16(0x3454 + (s16)(D0 & 0xffff)),
                      &D0);                          // MOVE.W	86(PC,D0),D0
  DEF_ROMLOC(3400) : move_tomem_16(D0, 0xFFFFFE10);  // MOVE.W	D0,$FE10
  DEF_ROMLOC(3404) : add_tomem_16(0x1, 0xFFFFFFF2);  // ADDQ.W	#$01,$FFF2
  DEF_ROMLOC(3408) : cmp_tomem_16(0x4, 0xFFFFFFF2);  // CMPI.W	#$0004,$FFF2
  DEF_ROMLOC(340E) : if (CCR_CS) goto rom_3416;      // BCS.B	$3416
  DEF_ROMLOC(3410) : move_tomem_16(0x0, 0xFFFFFFF2); // MOVE.W	#$0000,$FFF2
  DEF_ROMLOC(3416) : move_tomem_16(0x1, 0xFFFFFFF0); // MOVE.W	#$0001,$FFF0
  DEF_ROMLOC(341C) : SET_GM_DEMO();
  DEF_ROMLOC(3422) : cmp_toreg_16(0x600, &D0);   // CMPI.W	#$0600,D0
  DEF_ROMLOC(3426) : if (!CCR_EQ) goto rom_3436; // BNE.B	$3436
  DEF_ROMLOC(3428) : SET_GM_SPECIAL();
  DEF_ROMLOC(342E) : clr_mem_16(0xFFFFFE10);        // CLR.W	$FE10
  DEF_ROMLOC(3432) : clr_mem_8(0xFFFFFE16);         // CLR.B	$FE16
  DEF_ROMLOC(3436) : move_tomem_8(0x3, 0xFFFFFE12); // MOVE.B	#$03,$FE12
  DEF_ROMLOC(343C) : move_toreg_32(0x0, &D0);       // MOVEQ.L	$00,D0
  DEF_ROMLOC(343E) : move_tomem_16(D0, 0xFFFFFE20); // MOVE.W	D0,$FE20
  DEF_ROMLOC(3442) : move_tomem_32(D0, 0xFFFFFE22); // MOVE.L	D0,$FE22
  DEF_ROMLOC(3446) : move_tomem_32(D0, 0xFFFFFE26); // MOVE.L	D0,$FE26
  DEF_ROMLOC(344A)
      : move_tomem_32(0x1388, 0xFFFFFFC0); // MOVE.L	#$00001388,$FFC0
  DEF_ROMLOC(3452) : return;               // RTS
}
ROMFUNC(rom_345C) {
  DEF_ROMLOC(345C) : move_toreg_8(read_8(0xFFFFF605), &D1); // MOVE.B	$F605,D1
  DEF_ROMLOC(3460) : and_toreg_8(0x3, &D1);                 // ANDI.B	#$03,D1
  DEF_ROMLOC(3464) : if (!CCR_EQ) goto rom_346C;            // BNE.B	$346C
  DEF_ROMLOC(3466) : sub_tomem_16(0x1, 0xFFFFFF80);         // SUBQ.W	#$01,$FF80
  DEF_ROMLOC(346A) : if (CCR_PL) goto rom_34A6;             // BPL.B	$34A6
  DEF_ROMLOC(346C) : move_tomem_16(0xB, 0xFFFFFF80); // MOVE.W	#$000B,$FF80
  DEF_ROMLOC(3472)
      : move_toreg_8(read_8(0xFFFFF604), &D1);  // MOVE.B	$F604,D1
  DEF_ROMLOC(3476) : and_toreg_8(0x3, &D1);     // ANDI.B	#$03,D1
  DEF_ROMLOC(347A) : if (CCR_EQ) goto rom_34A6; // BEQ.B	$34A6
  DEF_ROMLOC(347C)
      : move_toreg_16(read_16(0xFFFFFF82), &D0);     // MOVE.W	$FF82,D0
  DEF_ROMLOC(3480) : btst_toreg_32(0x0, &D1);        // BTST.L	#$00,D1
  DEF_ROMLOC(3484) : if (CCR_EQ) goto rom_348C;      // BEQ.B	$348C
  DEF_ROMLOC(3486) : sub_toreg_16(0x1, &D0);         // SUBQ.W	#$01,D0
  DEF_ROMLOC(3488) : if (CCR_CC) goto rom_348C;      // BCC.B	$348C
  DEF_ROMLOC(348A) : move_toreg_32(0x14, &D0);       // MOVEQ.L	$14,D0
  DEF_ROMLOC(348C) : btst_toreg_32(0x1, &D1);        // BTST.L	#$01,D1
  DEF_ROMLOC(3490) : if (CCR_EQ) goto rom_349C;      // BEQ.B	$349C
  DEF_ROMLOC(3492) : add_toreg_16(0x1, &D0);         // ADDQ.W	#$01,D0
  DEF_ROMLOC(3494) : cmp_toreg_16(0x15, &D0);        // CMPI.W	#$0015,D0
  DEF_ROMLOC(3498) : if (CCR_CS) goto rom_349C;      // BCS.B	$349C
  DEF_ROMLOC(349A) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(349C) : move_tomem_16(D0, 0xFFFFFF82);  // MOVE.W	D0,$FF82
  DEF_ROMLOC(34A0) : rom_34E2();                     // BSR.W	$34E2
  DEF_ROMLOC(34A4) : return;                         // RTS
  DEF_ROMLOC(34A6) : cmp_tomem_16(0x14, 0xFFFFFF82); // CMPI.W	#$0014,$FF82
  DEF_ROMLOC(34AC) : if (!CCR_EQ) goto rom_34E0;     // BNE.B	$34E0
  DEF_ROMLOC(34AE)
      : move_toreg_8(read_8(0xFFFFF605), &D1);  // MOVE.B	$F605,D1
  DEF_ROMLOC(34B2) : and_toreg_8(0xC, &D1);     // ANDI.B	#$0C,D1
  DEF_ROMLOC(34B6) : if (CCR_EQ) goto rom_34E0; // BEQ.B	$34E0
  DEF_ROMLOC(34B8)
      : move_toreg_16(read_16(0xFFFFFF84), &D0);    // MOVE.W	$FF84,D0
  DEF_ROMLOC(34BC) : btst_toreg_32(0x2, &D1);       // BTST.L	#$02,D1
  DEF_ROMLOC(34C0) : if (CCR_EQ) goto rom_34C8;     // BEQ.B	$34C8
  DEF_ROMLOC(34C2) : sub_toreg_16(0x1, &D0);        // SUBQ.W	#$01,D0
  DEF_ROMLOC(34C4) : if (CCR_CC) goto rom_34C8;     // BCC.B	$34C8
  DEF_ROMLOC(34C6) : move_toreg_32(0x4F, &D0);      // MOVEQ.L	$4F,D0
  DEF_ROMLOC(34C8) : btst_toreg_32(0x3, &D1);       // BTST.L	#$03,D1
  DEF_ROMLOC(34CC) : if (CCR_EQ) goto rom_34D8;     // BEQ.B	$34D8
  DEF_ROMLOC(34CE) : add_toreg_16(0x1, &D0);        // ADDQ.W	#$01,D0
  DEF_ROMLOC(34D0) : cmp_toreg_16(0x50, &D0);       // CMPI.W	#$0050,D0
  DEF_ROMLOC(34D4) : if (CCR_CS) goto rom_34D8;     // BCS.B	$34D8
  DEF_ROMLOC(34D6) : move_toreg_32(0x0, &D0);       // MOVEQ.L	$00,D0
  DEF_ROMLOC(34D8) : move_tomem_16(D0, 0xFFFFFF84); // MOVE.W	D0,$FF84
  DEF_ROMLOC(34DC) : rom_34E2();                    // BSR.W	$34E2
  DEF_ROMLOC(34E0) : return;                        // RTS
}
ROMFUNC(rom_34E2) {
  DEF_ROMLOC(34E2) : move_toreg_32(0x359E, &A1);     // LEA.L	$0000359E,A1
  DEF_ROMLOC(34E8) : move_toreg_32(0xC00000, &A6);   // LEA.L	$00C00000,A6
  DEF_ROMLOC(34EE) : move_toreg_32(0x62100003, &D4); // MOVE.L	#$62100003,D4
  DEF_ROMLOC(34F4) : move_toreg_16(0xFFFFE680, &D3); // MOVE.W	#$E680,D3
  DEF_ROMLOC(34F8) : move_toreg_32(0x14, &D1);       // MOVEQ.L	$14,D1
  rom_34FA(); // Detected flow into next function
}
ROMFUNC(rom_34FA) {
  DEF_ROMLOC(34FA) : move_tomem_32(D4, A6 + 0x4); // MOVE.L	D4,4(A6)
  DEF_ROMLOC(34FE) : rom_3582();                  // BSR.W	$3582
  DEF_ROMLOC(3502) : add_toreg_32(0x800000, &D4); // ADDI.L	#$00800000,D4
  DEF_ROMLOC(3508) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_34FA;                            // DBF.W	D1,$34FA
  DEF_ROMLOC(350C) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(350E)
      : move_toreg_16(read_16(0xFFFFFF82), &D0);     // MOVE.W	$FF82,D0
  DEF_ROMLOC(3512) : move_toreg_16(D0, &D1);         // MOVE.W	D0,D1
  DEF_ROMLOC(3514) : move_toreg_32(0x62100003, &D4); // MOVE.L	#$62100003,D4
  DEF_ROMLOC(351A) : lsl_toreg_16(0x7, &D0);         // LSL.W	#$07,D0
  DEF_ROMLOC(351C) : swap_reg_16(&D0);               // SWAP.W	D0
  DEF_ROMLOC(351E) : add_toreg_32(D0, &D4);          // ADD.L	D0,D4
  DEF_ROMLOC(3520) : move_toreg_32(0x359E, &A1);     // LEA.L	$0000359E,A1
  DEF_ROMLOC(3526) : lsl_toreg_16(0x3, &D1);         // LSL.W	#$03,D1
  DEF_ROMLOC(3528) : move_toreg_16(D1, &D0);         // MOVE.W	D1,D0
  DEF_ROMLOC(352A) : add_toreg_16(D1, &D1);          // ADD.W	D1,D1
  DEF_ROMLOC(352C) : add_toreg_16(D0, &D1);          // ADD.W	D0,D1
  DEF_ROMLOC(352E) : add_toreg_16(D1, &A1);          // ADDA.W	D1,A1
  DEF_ROMLOC(3530) : move_toreg_16(0xFFFFC680, &D3); // MOVE.W	#$C680,D3
  DEF_ROMLOC(3534) : move_tomem_32(D4, A6 + 0x4);    // MOVE.L	D4,4(A6)
  DEF_ROMLOC(3538) : rom_3582();                     // BSR.W	$3582
  DEF_ROMLOC(353C) : move_toreg_16(0xFFFFE680, &D3); // MOVE.W	#$E680,D3
  DEF_ROMLOC(3540) : cmp_tomem_16(0x14, 0xFFFFFF82); // CMPI.W	#$0014,$FF82
  DEF_ROMLOC(3546) : if (!CCR_EQ) goto rom_354C;     // BNE.B	$354C
  DEF_ROMLOC(3548) : move_toreg_16(0xFFFFC680, &D3); // MOVE.W	#$C680,D3
  DEF_ROMLOC(354C)
      : move_tomem_32(0x6C300003, 0xC00004); // MOVE.L	#$6C300003,$00C00004
  DEF_ROMLOC(3556)
      : move_toreg_16(read_16(0xFFFFFF84), &D0); // MOVE.W	$FF84,D0
  DEF_ROMLOC(355A) : add_toreg_16(0x80, &D0);    // ADDI.W	#$0080,D0
  DEF_ROMLOC(355E) : move_toreg_8(D0, &D2);      // MOVE.B	D0,D2
  DEF_ROMLOC(3560) : lsr_toreg_8(0x4, &D0);      // LSR.B	#$04,D0
  DEF_ROMLOC(3562) : rom_356E();                 // BSR.W	$356E
  DEF_ROMLOC(3566) : move_toreg_8(D2, &D0);      // MOVE.B	D2,D0
  DEF_ROMLOC(3568) : rom_356E();                 // BSR.W	$356E
  DEF_ROMLOC(356C) : return;                     // RTS
}
ROMFUNC(rom_356E) {
  DEF_ROMLOC(356E) : and_toreg_16(0xF, &D0);    // ANDI.W	#$000F,D0
  DEF_ROMLOC(3572) : cmp_toreg_8(0xA, &D0);     // CMPI.B	#$0A,D0
  DEF_ROMLOC(3576) : if (CCR_CS) goto rom_357C; // BCS.B	$357C
  DEF_ROMLOC(3578) : add_toreg_8(0x7, &D0);     // ADDI.B	#$07,D0
  DEF_ROMLOC(357C) : add_toreg_16(D3, &D0);     // ADD.W	D3,D0
  DEF_ROMLOC(357E) : move_tomem_16(D0, A6);     // MOVE.W	D0,(A6)
  DEF_ROMLOC(3580) : return;                    // RTS
}
ROMFUNC(rom_3582) {
  DEF_ROMLOC(3582) : move_toreg_32(0x17, &D2);        // MOVEQ.L	$17,D2
  DEF_ROMLOC(3584) : move_toreg_32(0x0, &D0);         // MOVEQ.L	$00,D0
  DEF_ROMLOC(3586) : move_toreg_8(read_8(A1++), &D0); // MOVE.B	(A1)+,D0
  DEF_ROMLOC(3588) : if (CCR_PL) goto rom_3594;       // BPL.B	$3594
  DEF_ROMLOC(358A) : move_tomem_16(0x0, A6);          // MOVE.W	#$0000,(A6)
  DEF_ROMLOC(358E) : dec_reg_16(&D2);
  if ((D2 & 0xffff) != 0xffff)
    goto rom_3584;                          // DBF.W	D2,$3584
  DEF_ROMLOC(3592) : return;                // RTS
  DEF_ROMLOC(3594) : add_toreg_16(D3, &D0); // ADD.W	D3,D0
  DEF_ROMLOC(3596) : move_tomem_16(D0, A6); // MOVE.W	D0,(A6)
  DEF_ROMLOC(3598) : dec_reg_16(&D2);
  if ((D2 & 0xffff) != 0xffff)
    goto rom_3584;           // DBF.W	D2,$3584
  DEF_ROMLOC(359C) : return; // RTS
}