// #define CHECK_STUFF 1
#include "opcodes.h"
#include "system.h"

void continue_screen_init_part2(void);
void continue_screen_load_numbers(void);
void continue_screen_loop(void);
void continue_screen_loop_part2(void);

void continue_screen_init(void) {
  DEF_ROMLOC(4CEC) : game_state = continue_screen_init_part2;
  palette_fade_out(); // BSR.W	$1E4A
}
void continue_screen_init_part2(void) {
  DEF_ROMLOC(4CF0) : move_tosr_16(0x2700, &SR); // MOVE.W	#$2700,SR
  DEF_ROMLOC(4CF4)
      : move_toreg_16(read_16(0xFFFFF60C), &D0);   // MOVE.W	$F60C,D0
  DEF_ROMLOC(4CF8) : and_toreg_8(0xFFFFFFBF, &D0); // ANDI.B	#$BF,D0
  DEF_ROMLOC(4CFC) : set_vdp_register(D0 >> 8, D0);
  DEF_ROMLOC(4D02)
      : move_toreg_32(VDP_CONTROL_PORT, &A6); // LEA.L	$00C00004,A6
  DEF_ROMLOC(4D08) : set_vdp_register(0x80, 0x04);
  DEF_ROMLOC(4D0C) : set_vdp_register(0x87, 0x00);
  DEF_ROMLOC(4D10) : clear_screen();                       // BSR.W	$12C4
  DEF_ROMLOC(4D14) : move_toreg_32(0xFFFFD000, &A1);       // LEA.L	$D000,A1
  DEF_ROMLOC(4D18) : move_toreg_32(0x0, &D0);              // MOVEQ.L	$00,D0
  DEF_ROMLOC(4D1A) : move_toreg_16(0x7FF, &D1);            // MOVE.W	#$07FF,D1
  DEF_ROMLOC(4D1E) : move_tomem_32(D0, (A1 += 4, A1 - 4)); // MOVE.L	D0,(A1)+
  DEF_ROMLOC(4D20) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_4D1E; // DBF.W	D1,$4D1E
  DEF_ROMLOC(4D24) : set_vram_ptr_direct(0x580 * 0x20);
  DEF_ROMLOC(4D2E) : move_toreg_32(0x39204, &A0); // LEA.L	$00039204,A0
  DEF_ROMLOC(4D34) : decompress_nemesis();        // BSR.W	$1438
  DEF_ROMLOC(4D38) : set_vram_ptr_direct(0x500 * 0x20);
  DEF_ROMLOC(4D42) : move_toreg_32(0x3B39A, &A0); // LEA.L	$0003B39A,A0
  DEF_ROMLOC(4D48) : decompress_nemesis();        // BSR.W	$1438
  DEF_ROMLOC(4D4C) : set_vram_ptr_direct(0x551 * 0x20);
  DEF_ROMLOC(4D56) : move_toreg_32(0x3B64A, &A0);     // LEA.L	$0003B64A,A0
  DEF_ROMLOC(4D5C) : decompress_nemesis();            // BSR.W	$1438
  DEF_ROMLOC(4D60) : move_toreg_32(0xA, &D1);         // MOVEQ.L	$0A,D1
  DEF_ROMLOC(4D62) : continue_screen_load_numbers();  // JSR	$0001D104
  DEF_ROMLOC(4D68) : move_toreg_32(0x12, &D0);        // MOVEQ.L	$12,D0
  DEF_ROMLOC(4D6A) : load_palette_fading();           // BSR.W	$20F4
  DEF_ROMLOC(4D6E) : move_toreg_8(BGM_CONTINUE, &D0); // MOVE.B	#$90,D0
  DEF_ROMLOC(4D72) : play_sound();                    // BSR.W	$138E
  DEF_ROMLOC(4D76)
      : move_tomem_16(0x293, 0xFFFFF614);      // MOVE.W
                                               // #$0293,$F614
  DEF_ROMLOC(4D7C) : clr_mem_32(v_screenposx); // CLR.L	$F700
  DEF_ROMLOC(4D80)
      : move_tomem_32(0x1000000, 0xFFFFF704); // MOVE.L	#$01000000,$F704
  DEF_ROMLOC(4D88)
      : move_tomem_8(0xFFFFFF81, 0xFFFFD000); // MOVE.B
                                              // #$81,$D000
  DEF_ROMLOC(4D8E)
      : move_tomem_8(0xFFFFFF80, 0xFFFFD040); // MOVE.B
                                              // #$80,$D040
  DEF_ROMLOC(4D94)
      : move_tomem_8(0xFFFFFF80, 0xFFFFD080);       // MOVE.B	#$80,$D080
  DEF_ROMLOC(4D9A) : move_tomem_8(0x3, 0xFFFFD098); // MOVE.B	#$03,$D098
  DEF_ROMLOC(4DA0) : move_tomem_8(0x4, 0xFFFFD09A); // MOVE.B	#$04,$D09A
  DEF_ROMLOC(4DA6)
      : move_tomem_8(0xFFFFFF80, 0xFFFFD0C0);       // MOVE.B	#$80,$D0C0
  DEF_ROMLOC(4DAC) : move_tomem_8(0x4, 0xFFFFD0E4); // MOVE.B	#$04,$D0E4
  DEF_ROMLOC(4DB2) : rom_D9C6();                    // JSR	$0000D9C6
  DEF_ROMLOC(4DB8) : build_sprites();               // JSR	$0000DCEC
  DEF_ROMLOC(4DBE)
      : move_toreg_16(read_16(0xFFFFF60C), &D0); // MOVE.W	$F60C,D0
  DEF_ROMLOC(4DC2) : or_toreg_8(0x40, &D0);      // ORI.B	#$40,D0
  DEF_ROMLOC(4DC6) : set_vdp_register(D0 >> 8, D0);
  DEF_ROMLOC(4DCC) : game_state = continue_screen_loop;
  palette_fade_in(true); // BSR.W	$1DA4
}
void continue_screen_loop(void) {
  end_frame(0x16);
  game_state = continue_screen_loop_part2;
}
void continue_screen_loop_part2(void) {
  DEF_ROMLOC(4DDA) : cmp_tomem_8(0x6, 0xFFFFD024); // CMPI.B	#$06,$D024
  DEF_ROMLOC(4DE0) : if (CCR_CC) goto rom_4DFE;    // BCC.B	$4DFE
  DEF_ROMLOC(4DE2) : move_tosr_16(0x2700, &SR);    // MOVE.W	#$2700,SR
  DEF_ROMLOC(4DE6) : move_toreg_16(read_16(0xFFFFF614), &D1); // MOVE.W	$F614,D1
  DEF_ROMLOC(4DEA) : divu_toreg_16(0x3C, &D1);        // DIVU.W	#$003C,D1
  DEF_ROMLOC(4DEE) : and_toreg_32(0xF, &D1);          // ANDI.L	#$0000000F,D1
  DEF_ROMLOC(4DF4) : continue_screen_load_numbers();  // JSR	$0001D104
  DEF_ROMLOC(4DFA) : move_tosr_16(0x2300, &SR);       // MOVE.W	#$2300,SR
  DEF_ROMLOC(4DFE) : rom_D9C6();                      // JSR	$0000D9C6
  DEF_ROMLOC(4E04) : build_sprites();                 // JSR	$0000DCEC
  DEF_ROMLOC(4E0A) : cmp_tomem_16(0x180, 0xFFFFD008); // CMPI.W	#$0180,$D008
  DEF_ROMLOC(4E10) : if (CCR_CC) goto rom_4E2A;       // BCC.B	$4E2A
  DEF_ROMLOC(4E12) : cmp_tomem_8(0x6, 0xFFFFD024);    // CMPI.B	#$06,$D024
  DEF_ROMLOC(4E18) : if (CCR_CC) {
    continue_screen_loop();
    return;
  } // BCC.B	$4DD0
  DEF_ROMLOC(4E1A) : tst_mem_16(0xFFFFF614); // TST.W	$F614
  DEF_ROMLOC(4E1E) : if (!CCR_EQ) {
    continue_screen_loop();
    return;
  } // BNE.W	$4DD0
  DEF_ROMLOC(4E22) : v_gamemode = GM_SEGA;
  DEF_ROMLOC(4E28) : return; // RTS
  DEF_ROMLOC(4E2A) : v_gamemode = GM_LEVEL;
  DEF_ROMLOC(4E30) : move_tomem_8(0x3, v_lives);    // MOVE.B	#$03,$FE12
  DEF_ROMLOC(4E36) : move_toreg_32(0x0, &D0);       // MOVEQ.L	$00,D0
  DEF_ROMLOC(4E38) : move_tomem_16(D0, 0xFFFFFE20); // MOVE.W	D0,$FE20
  DEF_ROMLOC(4E3C) : move_tomem_32(D0, 0xFFFFFE22); // MOVE.L	D0,$FE22
  DEF_ROMLOC(4E40) : move_tomem_32(D0, 0xFFFFFE26); // MOVE.L	D0,$FE26
  DEF_ROMLOC(4E44) : move_tomem_8(D0, 0xFFFFFE30);  // MOVE.B	D0,$FE30
  DEF_ROMLOC(4E48) : sub_tomem_8(0x1, 0xFFFFFE18);  // SUBQ.B	#$01,$FE18
  DEF_ROMLOC(4E4C) : return;                        // RTS
}
void continue_screen_load_numbers(void) {
  DEF_ROMLOC(1D104) : set_vram_ptr_direct(0x6fc * 0x20);
  DEF_ROMLOC(1D10E)
      : move_toreg_32(VDP_DATA_PORT, &A6);         // LEA.L	$00C00000,A6
  DEF_ROMLOC(1D114) : move_toreg_32(0x1D16C, &A2); // LEA.L	$0001D16C,A2
  DEF_ROMLOC(1D11A) : move_toreg_32(0x1, &D6);     // MOVEQ.L	$01,D6
  DEF_ROMLOC(1D11C) : move_toreg_32(0x0, &D4);     // MOVEQ.L	$00,D4
  DEF_ROMLOC(1D11E) : move_toreg_32(0x1D2A6, &A1); // LEA.L	390(PC),A1
  DEF_ROMLOC(1D122) : move_toreg_32(0x0, &D2);     // MOVEQ.L	$00,D2
  DEF_ROMLOC(1D124)
      : move_toreg_32(read_32((A2 += 4, A2 - 4)), &D3); // MOVE.L	(A2)+,D3
  DEF_ROMLOC(1D126) : sub_toreg_32(D3, &D1);            // SUB.L	D3,D1
  DEF_ROMLOC(1D128) : if (CCR_CS) goto rom_1D12E;       // BCS.B	$1D12E
  DEF_ROMLOC(1D12A) : add_toreg_16(0x1, &D2);           // ADDQ.W	#$01,D2
  goto rom_1D126;                                       // BRA.B	$1D126
  DEF_ROMLOC(1D12E) : add_toreg_32(D3, &D1);            // ADD.L	D3,D1
  DEF_ROMLOC(1D130) : lsl_toreg_16(0x6, &D2);           // LSL.W	#$06,D2
  DEF_ROMLOC(1D132)
      : move_toreg_32((s32)A1 + (s8)0x0 + (s16)D2,
                      &A3); // LEA.L	0(A1,D2),A3
  DEF_ROMLOC(1D136) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D138) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D13A) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D13C) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D13E) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D140) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D142) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D144) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D146) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D148) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D14A) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D14C) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D14E) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D150) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D152) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D154) : write_vdp_data_32(read_32((A3 += 4, A3 - 4)));
  DEF_ROMLOC(1D156) : dec_reg_16(&D6);
  if ((D6 & 0xffff) != 0xffff)
    goto rom_1D122;           // DBF.W	D6,$1D122
  DEF_ROMLOC(1D15A) : return; // RTS
}