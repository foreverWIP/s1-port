#include "sega.h"
#include "opcodes.h"
#include "system.h"


void sega_wait_palette(void);
void sega_wait_palette_loop(void);

bool sega_cycle_palette(void) {
  if (read_8(0xFFFFF635) == 0) {
    A1 = 0xFFFFFB20;
    A0 = 0x20B8;
    D1 = 5;
    SETWORD(D0, read_16(0xFFFFF632));
    while (true) {
      if (((s16)GETWORD(D0)) >= 0)
        break;
      A0 += 2;
      D1 -= 1;
      D0 += 2;
    }
    DEF_ROMLOC(2022) : move_toreg_16(D0, &D2);  // MOVE.W	D0,D2
    and_toreg_16(0x1E, &D2); // ANDI.W	#$001E,D2
    if (CCR_EQ) {                               // BNE.B	$202C
      add_toreg_16(0x2, &D0);                   // ADDQ.W	#$02,D0
    }
    cmp_toreg_16(0x60, &D0);   // CMPI.W	#$0060,D0
    if (CCR_CC) goto rom_2036; // BCC.B	$2036
    move_tomem_16(read_16((A0 += 2, A0 - 2)),
                        (s32)A1 + (s8)0x0 + (s16)D0); // MOVE.W	(A0)+,0(A1,D0)
    DEF_ROMLOC(2036) : add_toreg_16(0x2, &D0);        // ADDQ.W	#$02,D0
    dec_reg_16(&D1);
    if ((D1 & 0xffff) != 0xffff)
      goto rom_2022; // DBF.W	D1,$2022
    move_toreg_16(read_16(0xFFFFF632), &D0); // MOVE.W	$F632,D0
    add_toreg_16(0x2, &D0);     // ADDQ.W	#$02,D0
    move_toreg_16(D0, &D2);     // MOVE.W	D0,D2
    and_toreg_16(0x1E, &D2);    // ANDI.W	#$001E,D2
    if (CCR_EQ) {                                  // BNE.B	$204C
      add_toreg_16(0x2, &D0);                      // ADDQ.W	#$02,D0
    }
    cmp_toreg_16(0x64, &D0); // CMPI.W	#$0064,D0
    if (!CCR_LT) {                              // BLT.B	$205A
      move_tomem_16(0x401, 0xFFFFF634);
      D0 = 0xFFFFFFF4;
    }
    move_tomem_16(D0, 0xFFFFF632); // MOVE.W	D0,$F632
    D0 = 1;
    return true;
  }
  sub_tomem_8(0x1, 0xFFFFF634);    // SUBQ.B	#$01,$F634
  if (!CCR_PL) {                                      // BPL.B	$20B4
    move_tomem_8(0x4, 0xFFFFF634); // MOVE.B	#$04,$F634
    move_toreg_16(read_16(0xFFFFF632), &D0); // MOVE.W	$F632,D0
    add_toreg_16(0xC, &D0);     // ADDI.W	#$000C,D0
    cmp_toreg_16(0x30, &D0);    // CMPI.W	#$0030,D0
    if (!CCR_CS) {                                 // BCS.B	$2080
      D0 = 0;
      return false;
    }
    move_tomem_16(D0, 0xFFFFF632); // MOVE.W	D0,$F632
    A0 = 0x20C4;
    A0 += D0;
    A1 = 0xFFFFFB04;
    move_tomem_32(read_32((A0 += 4, A0 - 4)),
                        (A1 += 4, A1 - 4)); // MOVE.L	(A0)+,(A1)+
    move_tomem_32(read_32((A0 += 4, A0 - 4)),
                        (A1 += 4, A1 - 4)); // MOVE.L	(A0)+,(A1)+
    move_tomem_16(read_16((A0 += 2, A0 - 2)),
                        A1); // MOVE.W	(A0)+,(A1)
    A1 = 0xFFFFFB20;
    D0 = 0x0;
    D1 = 0x2C;
    DEF_ROMLOC(20A0) : move_toreg_16(D0, &D2);  // MOVE.W	D0,D2
    and_toreg_16(0x1E, &D2); // ANDI.W	#$001E,D2
    if (GETWORD(D2) == 0) {                     // BNE.B	$20AA
      add_toreg_16(0x2, &D0);                   // ADDQ.W	#$02,D0
    }
    move_tomem_16(read_16(A0),
                        (s32)A1 + (s8)0x0 + (s16)D0); // MOVE.W	(A0),0(A1,D0)
    add_toreg_16(0x2, &D0);        // ADDQ.W	#$02,D0
    dec_reg_16(&D1);
    if ((D1 & 0xffff) != 0xffff)
      goto rom_20A0; // DBF.W	D1,$20A0
  }
  D0 = 1;
  return true;
}

void sega_init_part2(void);
void sega_init(void) {
  SETBYTE(SR, 0x04);
  move_toreg_8(COMSFX_STOP, &D0); // MOVE.B	#$E4,D0
  play_sound_special();           // BSR.W	$1394
  clear_plc();                    // BSR.W	$15D6
  game_state = sega_init_part2;
  palette_fade_out(); // BSR.W	$1E4A
}
void sega_init_part2(void) {
  A6 = 0xC00004;
  write_16(A6, 0x8004);
  write_16(A6, 0x8230);
  write_16(A6, 0x8407);
  write_16(A6, 0x8700);
  write_16(A6, 0x8B00);
  clr_mem_8(0xFFFFF64E);     // CLR.B	$F64E
  move_tosr_16(0x2700, &SR); // MOVE.W	#$2700,SR
  move_toreg_16(read_16(0xFFFFF60C), &D0);   // MOVE.W	$F60C,D0
  and_toreg_8(0xFFFFFFBF, &D0); // ANDI.B	#$BF,D0
  move_tomem_16(D0, 0xC00004);  // MOVE.W	D0,$00C00004
  clear_screen();               // BSR.W	$12C4
  write_32(0xC00004, VRAM_PTR_TO_VDP_COMMAND(0x0000));
  A0 = 0x1E700;
  decompress_nemesis(); // BSR.W	$1438
  A1 = v_256x256;
  A0 = 0x1EB70;
  move_toreg_16(0x0, &D0); // MOVE.W	#$0000,D0
  decompress_enigma();     // BSR.W	$1716
  copy_tilemap(v_256x256, VRAM_BG, 8, 10, 24, 8);
  copy_tilemap(v_256x256 + (24 * 8 * 2), VRAM_FG, 0, 0, 40, 28);
  if ((read_8(0xFFFFFFF8) & 0x80) == 0) {    // BMI.B	$2E80
	copy_tilemap(v_256x256 + 0xa40, VRAM_FG, 29, 10, 3, 2);
  }
  D0 = 0;
  load_palette(); // BSR.W	$2110
  move_tomem_16(0xFFFFFFF6, 0xFFFFF632);       // MOVE.W	#$FFF6,$F632
  move_tomem_16(0x0, 0xFFFFF634); // MOVE.W	#$0000,$F634
  move_tomem_16(0x0, 0xFFFFF662); // MOVE.W	#$0000,$F662
  move_tomem_16(0x0, 0xFFFFF660); // MOVE.W	#$0000,$F660
  move_toreg_16(read_16(0xFFFFF60C), &D0);  // MOVE.W	$F60C,D0
  or_toreg_8(0x40, &D0);       // ORI.B	#$40,D0
  move_tomem_16(D0, 0xC00004); // MOVE.W	D0,$00C00004
  sega_wait_palette();
  game_state = sega_wait_palette_loop;
}
void sega_wait_palette(void) { end_frame(0x2); }
void sega_end_wait_start(void);
void sega_wait_palette_loop(void) {
  if (sega_cycle_palette()) {
    sega_wait_palette();
    return;
  }                                                  // BNE.B	$2EAC
  move_toreg_8(COMSFX_SEGA, &D0); // MOVE.B	#$E1,D0
  play_sound_special();           // BSR.W	$1394
  end_frame(0x14);
  game_state = sega_end_wait_start;
}
void sega_wait_end_loop(void);
void sega_end_wait_start(void) {
  move_tomem_16(0x1E, 0xFFFFF614); // MOVE.W	#$001E,$F614
  sega_wait_end();
  game_state = sega_wait_end_loop;
}
void sega_wait_end(void) { end_frame(0x2); }
void sega_wait_end_loop(void) {
  if (read_16(0xFFFFF614) != 0) {
    u8 start_pressed = read_8(0xFFFFF605) & 0xFFFFFF80;
    write_8(0xFFFFF605, start_pressed);
    if (start_pressed == 0) {
      sega_wait_end();
      return;
    }
  }
  move_tomem_8(GM_TITLE, v_gamemode);
}