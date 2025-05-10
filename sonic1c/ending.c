// #define CHECK_STUFF 1
#include "opcodes.h"
#include "system.h"

ROMFUNC(rom_50FE);

ROMFUNC(rom_50F2) {
  DEF_ROMLOC(50F2) : move_toreg_8(COMSFX_STOP, &D0); // MOVE.B	#$E4,D0
  DEF_ROMLOC(50F6) : play_sound_special();           // BSR.W	$1394
  DEF_ROMLOC(50FA) : game_state = rom_50FE;
  palette_fade_out(); // BSR.W	$1E4A
}
ROMFUNC(rom_5278);
ROMFUNC(rom_50FE) {
  DEF_ROMLOC(50FE) : move_toreg_32(0xFFFFD000, &A1);       // LEA.L	$D000,A1
  DEF_ROMLOC(5102) : move_toreg_32(0x0, &D0);              // MOVEQ.L	$00,D0
  DEF_ROMLOC(5104) : move_toreg_16(0x7FF, &D1);            // MOVE.W	#$07FF,D1
  DEF_ROMLOC(5108) : move_tomem_32(D0, (A1 += 4, A1 - 4)); // MOVE.L	D0,(A1)+
  DEF_ROMLOC(510A) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_5108;                                         // DBF.W	D1,$5108
  DEF_ROMLOC(510E) : move_toreg_32(0xFFFFF628, &A1);       // LEA.L	$F628,A1
  DEF_ROMLOC(5112) : move_toreg_32(0x0, &D0);              // MOVEQ.L	$00,D0
  DEF_ROMLOC(5114) : move_toreg_16(0x15, &D1);             // MOVE.W	#$0015,D1
  DEF_ROMLOC(5118) : move_tomem_32(D0, (A1 += 4, A1 - 4)); // MOVE.L	D0,(A1)+
  DEF_ROMLOC(511A) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_5118;                                         // DBF.W	D1,$5118
  DEF_ROMLOC(511E) : move_toreg_32(v_levelvariables, &A1); // LEA.L	$F700,A1
  DEF_ROMLOC(5122) : move_toreg_32(0x0, &D0);              // MOVEQ.L	$00,D0
  DEF_ROMLOC(5124) : move_toreg_16(0x3F, &D1);             // MOVE.W	#$003F,D1
  DEF_ROMLOC(5128) : move_tomem_32(D0, (A1 += 4, A1 - 4)); // MOVE.L	D0,(A1)+
  DEF_ROMLOC(512A) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_5128;                                         // DBF.W	D1,$5128
  DEF_ROMLOC(512E) : move_toreg_32(0xFFFFFE60, &A1);       // LEA.L	$FE60,A1
  DEF_ROMLOC(5132) : move_toreg_32(0x0, &D0);              // MOVEQ.L	$00,D0
  DEF_ROMLOC(5134) : move_toreg_16(0x47, &D1);             // MOVE.W	#$0047,D1
  DEF_ROMLOC(5138) : move_tomem_32(D0, (A1 += 4, A1 - 4)); // MOVE.L	D0,(A1)+
  DEF_ROMLOC(513A) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_5138;                              // DBF.W	D1,$5138
  DEF_ROMLOC(513E) : move_tosr_16(0x2700, &SR); // MOVE.W	#$2700,SR
  DEF_ROMLOC(5142)
      : move_toreg_16(read_16(0xFFFFF60C), &D0);   // MOVE.W	$F60C,D0
  DEF_ROMLOC(5146) : and_toreg_8(0xFFFFFFBF, &D0); // ANDI.B	#$BF,D0
  DEF_ROMLOC(514A) : set_vdp_register(D0 >> 8, D0);
  DEF_ROMLOC(5150) : clear_screen(); // BSR.W	$12C4
  DEF_ROMLOC(5154)
      : move_toreg_32(VDP_CONTROL_PORT, &A6); // LEA.L	$00C00004,A6
  DEF_ROMLOC(515A) : set_vdp_register(0x8B, 0x03);
  DEF_ROMLOC(515E) : set_vdp_register(0x82, 0x30);
  DEF_ROMLOC(5162) : set_vdp_register(0x84, 0x07);
  DEF_ROMLOC(5166) : set_vdp_register(0x85, 0x7C);
  DEF_ROMLOC(516A) : set_vdp_register(0x90, 0x01);
  DEF_ROMLOC(516E) : set_vdp_register(0x80, 0x04);
  DEF_ROMLOC(5172) : set_vdp_register(0x87, 0x20);
  DEF_ROMLOC(5176)
      : move_tomem_16(0x8ADF, 0xFFFFF624); // MOVE.W	#$8ADF,$F624
  DEF_ROMLOC(517C) : set_vdp_register(read_8(v_hbla_hreg), read_8(v_hbla_hreg + 1));
  DEF_ROMLOC(5180)
      : move_tomem_16(MAX_AIR_SECONDS, v_air); // MOVE.W	#$001E,$FE14
  DEF_ROMLOC(5186)
      : move_tomem_16(ZONE16_END | 0, v_zone);     // MOVE.W
                                                   // #$0600,$FE10
  DEF_ROMLOC(518C) : cmp_tomem_8(0x6, 0xFFFFFE57); // CMPI.B	#$06,$FE57
  DEF_ROMLOC(5192) : if (CCR_EQ) goto rom_519A;    // BEQ.B	$519A
  DEF_ROMLOC(5194)
      : move_tomem_16(ZONE16_END | 1, v_zone);      // MOVE.W
                                                    // #$0601,$FE10
  DEF_ROMLOC(519A) : move_toreg_32(0x1C, &D0);      // MOVEQ.L	$1C,D0
  DEF_ROMLOC(519C) : quick_plc();                   // BSR.W	$16E4
  DEF_ROMLOC(51A0) : rom_1CFEE();                   // JSR	$0001CFEE
  DEF_ROMLOC(51A6) : rom_5ECC();                    // BSR.W	$5ECC
  DEF_ROMLOC(51AA) : rom_626E();                    // BSR.W	$626E
  DEF_ROMLOC(51AE) : bset_tomem_8(0x2, 0xFFFFF754); // BSET.B	#$02,$F754
  DEF_ROMLOC(51B4) : rom_72F0();                    // BSR.W	$72F0
  DEF_ROMLOC(51B8) : update_tiles_on_start();       // BSR.W	$71AC
  DEF_ROMLOC(51BC)
      : move_tomem_32(0x64A00, 0xFFFFF796);       // MOVE.L	#$00064A00,$F796
  DEF_ROMLOC(51C4) : move_tosr_16(0x2300, &SR);   // MOVE.W	#$2300,SR
  DEF_ROMLOC(51C8) : move_toreg_32(0x61822, &A0); // LEA.L	$00061822,A0
  DEF_ROMLOC(51CE)
      : move_toreg_32((v_256x256 + 0xA400) - 0x1000, &A1); // LEA.L	$9400,A1
  DEF_ROMLOC(51D2) : rom_1894();                           // BSR.W	$1894
  DEF_ROMLOC(51D6) : move_toreg_32(0x3, &D0);              // MOVEQ.L	$03,D0
  DEF_ROMLOC(51D8) : load_palette_fading();                // BSR.W	$20F4
  DEF_ROMLOC(51DC) : move_toreg_16(BGM_ENDING, &D0);       // MOVE.W	#$008B,D0
  DEF_ROMLOC(51E0) : play_sound();                         // BSR.W	$138E
  DEF_ROMLOC(51E4) : btst_tomem_8(0x6, 0xFFFFF604);        // BTST.B	#$06,$F604
  DEF_ROMLOC(51EA) : if (CCR_EQ) goto rom_51F2;            // BEQ.B	$51F2
  DEF_ROMLOC(51EC) : move_tomem_8(0x1, 0xFFFFFFFA);        // MOVE.B	#$01,$FFFA
  DEF_ROMLOC(51F2) : move_tomem_8(0x1, 0xFFFFD000);        // MOVE.B	#$01,$D000
  DEF_ROMLOC(51F8) : bset_tomem_8(0x0, 0xFFFFD022);        // BSET.B	#$00,$D022
  DEF_ROMLOC(51FE) : move_tomem_8(0x1, 0xFFFFF7CC);        // MOVE.B	#$01,$F7CC
  DEF_ROMLOC(5204)
      : move_tomem_16(0x400, 0xFFFFF602); // MOVE.W
                                          // #$0400,$F602
  DEF_ROMLOC(520A)
      : move_tomem_16(0xFFFFF800, 0xFFFFD014);       // MOVE.W	#$F800,$D014
  DEF_ROMLOC(5210) : move_tomem_8(0x21, 0xFFFFD040); // MOVE.B	#$21,$D040
  DEF_ROMLOC(5216) : rom_DF68();                     // JSR	$0000DF68
  DEF_ROMLOC(521C) : rom_D9C6();                     // JSR	$0000D9C6
  DEF_ROMLOC(5222) : build_sprites();                // JSR	$0000DCEC
  DEF_ROMLOC(5228) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(522A) : move_tomem_16(D0, 0xFFFFFE20);  // MOVE.W	D0,$FE20
  DEF_ROMLOC(522E) : move_tomem_32(D0, 0xFFFFFE22);  // MOVE.L	D0,$FE22
  DEF_ROMLOC(5232) : move_tomem_8(D0, 0xFFFFFE1B);   // MOVE.B	D0,$FE1B
  DEF_ROMLOC(5236) : move_tomem_8(D0, 0xFFFFFE2C);   // MOVE.B	D0,$FE2C
  DEF_ROMLOC(523A) : move_tomem_8(D0, 0xFFFFFE2D);   // MOVE.B	D0,$FE2D
  DEF_ROMLOC(523E) : move_tomem_8(D0, 0xFFFFFE2E);   // MOVE.B	D0,$FE2E
  DEF_ROMLOC(5242) : move_tomem_8(D0, 0xFFFFFE2F);   // MOVE.B	D0,$FE2F
  DEF_ROMLOC(5246) : move_tomem_16(D0, v_debuguse);  // MOVE.W	D0,$FE08
  DEF_ROMLOC(524A) : move_tomem_16(D0, 0xFFFFFE02);  // MOVE.W	D0,$FE02
  DEF_ROMLOC(524E) : move_tomem_16(D0, 0xFFFFFE04);  // MOVE.W	D0,$FE04
  DEF_ROMLOC(5252) : rom_411A();                     // BSR.W	$411A
  DEF_ROMLOC(5256) : move_tomem_8(0x1, 0xFFFFFE1F);  // MOVE.B	#$01,$FE1F
  DEF_ROMLOC(525C) : move_tomem_8(0x1, 0xFFFFFE1D);  // MOVE.B	#$01,$FE1D
  DEF_ROMLOC(5262) : move_tomem_8(0x0, f_timecount); // MOVE.B	#$00,$FE1E
  DEF_ROMLOC(5268)
      : move_tomem_16(0x708, 0xFFFFF614); // MOVE.W
                                          // #$0708,$F614
  end_frame(0x18);                        // BSR.W	$29A0
  game_state = rom_5278;
}
ROMFUNC(rom_5278) {
  DEF_ROMLOC(5278) : move_toreg_16(read_16(0xFFFFF60C), &D0); // MOVE.W	$F60C,D0
  DEF_ROMLOC(527C) : or_toreg_8(0x40, &D0);                   // ORI.B	#$40,D0
  DEF_ROMLOC(5280) : set_vdp_register(D0 >> 8, D0);
  // D0,$00C00004
  DEF_ROMLOC(5286) : move_tomem_16(0x3F, 0xFFFFF626); // MOVE.W	#$003F,$F626
  DEF_ROMLOC(528C) : game_state = rom_5290;
  palette_fade_in(true); // BSR.W	$1DA4
}
ROMFUNC(rom_529E);
ROMFUNC(rom_5294);
ROMFUNC(rom_5290) {
  DEF_ROMLOC(5290) : game_state = rom_5294;
  handle_pause_game(); // BSR.W	$13A0
}
ROMFUNC(rom_5294) {
  end_frame(0x18);
  game_state = rom_529E;
}
void level_palette_cycle(void);
ROMFUNC(rom_529E) {
  DEF_ROMLOC(529E) : add_tomem_16(0x1, 0xFFFFFE04); // ADDQ.W	#$01,$FE04
  DEF_ROMLOC(52A2) : rom_537C();                    // BSR.W	$537C
  DEF_ROMLOC(52A6) : rom_D9C6();                    // JSR	$0000D9C6
  DEF_ROMLOC(52AC) : rom_626E();                    // BSR.W	$626E
  DEF_ROMLOC(52B0) : build_sprites();               // JSR	$0000DCEC
  DEF_ROMLOC(52B6) : rom_DF68();                    // JSR	$0000DF68
  DEF_ROMLOC(52BC) : level_palette_cycle();         // BSR.W	$1934
  DEF_ROMLOC(52C0) : rom_4170();                    // BSR.W	$4170
  DEF_ROMLOC(52C4) : run_global_anims();            // BSR.W	$4208
  DEF_ROMLOC(52CE)
      : if (v_gamemode == GM_ENDING) goto rom_52E6; // BEQ.B	$52E6
  DEF_ROMLOC(52D0) : v_gamemode = GM_CREDITS;
  DEF_ROMLOC(52D6) : move_toreg_8(BGM_CREDITS, &D0); // MOVE.B	#$91,D0
  DEF_ROMLOC(52DA) : play_sound_special();           // BSR.W	$1394
  DEF_ROMLOC(52DE) : move_tomem_16(0x0, 0xFFFFFFF4); // MOVE.W	#$0000,$FFF4
  DEF_ROMLOC(52E4) : return;                         // RTS
  DEF_ROMLOC(52E6) : tst_mem_16(0xFFFFFE02);         // TST.W	$FE02
  DEF_ROMLOC(52EA) : if (CCR_EQ) {
    rom_5290();
    return;
  } // BEQ.W	$5290
  DEF_ROMLOC(52EE) : clr_mem_16(0xFFFFFE02);          // CLR.W	$FE02
  DEF_ROMLOC(52F2) : move_tomem_16(0x3F, 0xFFFFF626); // MOVE.W	#$003F,$F626
  DEF_ROMLOC(52F8) : clr_mem_16(0xFFFFF794);          // CLR.W	$F794
  rom_52FC(); // Detected flow into next function
}
ROMFUNC(rom_530A);
ROMFUNC(rom_5300);
ROMFUNC(rom_52FC) {
  DEF_ROMLOC(52FC) : game_state = rom_5300;
  handle_pause_game(); // BSR.W	$13A0
}
ROMFUNC(rom_5300) {
  end_frame(0x18);
  game_state = rom_530A;
}
ROMFUNC(rom_530A) {
  DEF_ROMLOC(530A) : add_tomem_16(0x1, 0xFFFFFE04);  // ADDQ.W	#$01,$FE04
  DEF_ROMLOC(530E) : rom_537C();                     // BSR.W	$537C
  DEF_ROMLOC(5312) : rom_D9C6();                     // JSR	$0000D9C6
  DEF_ROMLOC(5318) : rom_626E();                     // BSR.W	$626E
  DEF_ROMLOC(531C) : build_sprites();                // JSR	$0000DCEC
  DEF_ROMLOC(5322) : rom_DF68();                     // JSR	$0000DF68
  DEF_ROMLOC(5328) : rom_4170();                     // BSR.W	$4170
  DEF_ROMLOC(532C) : run_global_anims();             // BSR.W	$4208
  DEF_ROMLOC(5330) : sub_tomem_16(0x1, 0xFFFFF794);  // SUBQ.W	#$01,$F794
  DEF_ROMLOC(5334) : if (CCR_PL) goto rom_5340;      // BPL.B	$5340
  DEF_ROMLOC(5336) : move_tomem_16(0x2, 0xFFFFF794); // MOVE.W	#$0002,$F794
  DEF_ROMLOC(533C) : palette_move_towards_white();   // BSR.W	$1F94
  DEF_ROMLOC(5340) : tst_mem_16(0xFFFFFE02);         // TST.W	$FE02
  DEF_ROMLOC(5344) : if (CCR_EQ) {
    rom_52FC();
    return;
  } // BEQ.W	$52FC
  DEF_ROMLOC(5348) : clr_mem_16(0xFFFFFE02); // CLR.W	$FE02
  DEF_ROMLOC(534C)
      : move_tomem_16(0x2E2F, 0xFFFFA480); // MOVE.W
                                           // #$2E2F,$A480
  DEF_ROMLOC(5352)
      : move_toreg_32(VDP_CONTROL_PORT, &A5); // LEA.L
                                              // $00C00004,A5
  DEF_ROMLOC(5358)
      : move_toreg_32(VDP_DATA_PORT, &A6);             // LEA.L
                                                       // $00C00000,A6
  DEF_ROMLOC(535E) : move_toreg_32(v_screenposx, &A3); // LEA.L	$F700,A3
  DEF_ROMLOC(5362) : move_toreg_32(0xFFFFA400, &A4);   // LEA.L	$A400,A4
  DEF_ROMLOC(5366) : move_toreg_16(0x4000, &D2);       // MOVE.W	#$4000,D2
  DEF_ROMLOC(536A) : draw_chunks();                    // BSR.W	$71F8
  DEF_ROMLOC(536E) : move_toreg_32(0x13, &D0);         // MOVEQ.L	$13,D0
  DEF_ROMLOC(5370) : load_palette_fading();            // BSR.W	$20F4
  DEF_ROMLOC(5374) : game_state = rom_5290;
  palette_fade_from_white(); // BSR.W	$1EC8
}
ROMFUNC(rom_537C) {
  DEF_ROMLOC(537C) : move_toreg_8(read_8(0xFFFFF7D7), &D0); // MOVE.B	$F7D7,D0
  DEF_ROMLOC(5380) : if (!CCR_EQ) goto rom_539C;            // BNE.B	$539C
  DEF_ROMLOC(5382) : cmp_tomem_16(0x90, 0xFFFFD008); // CMPI.W	#$0090,$D008
  DEF_ROMLOC(5388) : if (CCR_CC) goto rom_53EC;      // BCC.B	$53EC
  DEF_ROMLOC(538A) : add_tomem_8(0x2, 0xFFFFF7D7);   // ADDQ.B	#$02,$F7D7
  DEF_ROMLOC(538E) : move_tomem_8(0x1, 0xFFFFF7CC);  // MOVE.B	#$01,$F7CC
  DEF_ROMLOC(5394)
      : move_tomem_16(0x800, 0xFFFFF602);        // MOVE.W
                                                 // #$0800,$F602
  DEF_ROMLOC(539A) : return;                     // RTS
  DEF_ROMLOC(539C) : sub_toreg_8(0x2, &D0);      // SUBQ.B	#$02,D0
  DEF_ROMLOC(539E) : if (!CCR_EQ) goto rom_53D4; // BNE.B	$53D4
  DEF_ROMLOC(53A0)
      : cmp_tomem_16(GAME_WIDTH / 2, 0xFFFFD008);   // CMPI.W	#$00A0,$D008
  DEF_ROMLOC(53A6) : if (CCR_CS) goto rom_53EC;     // BCS.B	$53EC
  DEF_ROMLOC(53A8) : add_tomem_8(0x2, 0xFFFFF7D7);  // ADDQ.B	#$02,$F7D7
  DEF_ROMLOC(53AC) : move_toreg_32(0x0, &D0);       // MOVEQ.L	$00,D0
  DEF_ROMLOC(53AE) : move_tomem_8(D0, 0xFFFFF7CC);  // MOVE.B	D0,$F7CC
  DEF_ROMLOC(53B2) : move_tomem_16(D0, 0xFFFFF602); // MOVE.W	D0,$F602
  DEF_ROMLOC(53B6) : move_tomem_16(D0, 0xFFFFD014); // MOVE.W	D0,$D014
  DEF_ROMLOC(53BA)
      : move_tomem_8(0xFFFFFF81, 0xFFFFF7C8);       // MOVE.B	#$81,$F7C8
  DEF_ROMLOC(53C0) : move_tomem_8(0x3, 0xFFFFD01A); // MOVE.B	#$03,$D01A
  DEF_ROMLOC(53C6)
      : move_tomem_16(0x505, 0xFFFFD01C);           // MOVE.W
                                                    // #$0505,$D01C
  DEF_ROMLOC(53CC) : move_tomem_8(0x3, 0xFFFFD01E); // MOVE.B	#$03,$D01E
  DEF_ROMLOC(53D2) : return;                        // RTS
  DEF_ROMLOC(53D4) : sub_toreg_8(0x2, &D0);         // SUBQ.B	#$02,D0
  DEF_ROMLOC(53D6) : if (!CCR_EQ) goto rom_53EC;    // BNE.B	$53EC
  DEF_ROMLOC(53D8) : add_tomem_8(0x2, 0xFFFFF7D7);  // ADDQ.B	#$02,$F7D7
  DEF_ROMLOC(53DC)
      : move_tomem_16(GAME_WIDTH / 2, 0xFFFFD008); // MOVE.W	#$00A0,$D008
  DEF_ROMLOC(53E2)
      : move_tomem_8(0xFFFFFF87, 0xFFFFD000); // MOVE.B
                                              // #$87,$D000
  DEF_ROMLOC(53E8) : clr_mem_16(0xFFFFD024);  // CLR.W	$D024
  DEF_ROMLOC(53EC) : return;                  // RTS
}
ROMFUNC(rom_5622) {
  u8 switchindex = 0;
  DEF_ROMLOC(5622) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(5624) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(5628)
      : move_toreg_16(read_16(0x5636 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	12(PC,D0),D1
  // DEF_ROMLOC(562C): rom_5636 + (s16)(D1 & 0xffff)(); // JSR	8(PC,D1)
  DEF_ROMLOC(562C) : switch (switchindex) {
  case 0:
    rom_563C();
    break;
  case 1:
    rom_5666();
    break;
  case 2:
    rom_5680();
    break;
  }
  DEF_ROMLOC(5630) : {
    queue_sprite();
    return;
  } // JMP	$0000DC92
}
ROMFUNC(rom_563C) {
  DEF_ROMLOC(563C) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(5640)
      : move_tomem_16(0xFFFFFFE0, A0 + 0x8);        // MOVE.W	#$FFE0,8(A0)
  DEF_ROMLOC(5646) : move_tomem_16(0xD8, A0 + 0xA); // MOVE.W	#$00D8,10(A0)
  DEF_ROMLOC(564C)
      : move_tomem_32(0x57C0, A0 + 0x4);             // MOVE.L	#$000057C0,4(A0)
  DEF_ROMLOC(5654) : move_tomem_16(0x5C5, A0 + 0x2); // MOVE.W	#$05C5,2(A0)
  DEF_ROMLOC(565A) : move_tomem_8(0x0, A0 + 0x1);    // MOVE.B	#$00,1(A0)
  DEF_ROMLOC(5660) : move_tomem_8(0x0, A0 + 0x18);   // MOVE.B	#$00,24(A0)
  rom_5666(); // Detected flow into next function
}
ROMFUNC(rom_5666) {
  DEF_ROMLOC(5666) : cmp_tomem_16(0xC0, A0 + 0x8);    // CMPI.W	#$00C0,8(A0)
  DEF_ROMLOC(566C) : if (CCR_EQ) goto rom_5676;       // BEQ.B	$5676
  DEF_ROMLOC(566E) : add_tomem_16(0x10, A0 + 0x8);    // ADDI.W	#$0010,8(A0)
  DEF_ROMLOC(5674) : return;                          // RTS
  DEF_ROMLOC(5676) : add_tomem_8(0x2, A0 + 0x24);     // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(567A) : move_tomem_16(0x12C, A0 + 0x30); // MOVE.W	#$012C,48(A0)
  rom_5680();
}
ROMFUNC(rom_5680) {
  DEF_ROMLOC(5680) : sub_tomem_16(0x1, A0 + 0x30); // SUBQ.W	#$01,48(A0)
  DEF_ROMLOC(5684) : if (CCR_PL) goto rom_568C;    // BPL.B	$568C
  DEF_ROMLOC(5686) : v_gamemode = GM_CREDITS;
  DEF_ROMLOC(568C) : return; // RTS
}