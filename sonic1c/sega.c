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
    DEF_ROMLOC(2024) : and_toreg_16(0x1E, &D2); // ANDI.W	#$001E,D2
    if (CCR_EQ) {                               // BNE.B	$202C
      add_toreg_16(0x2, &D0);                   // ADDQ.W	#$02,D0
    }
    DEF_ROMLOC(202C) : cmp_toreg_16(0x60, &D0);   // CMPI.W	#$0060,D0
    DEF_ROMLOC(2030) : if (CCR_CC) goto rom_2036; // BCC.B	$2036
    DEF_ROMLOC(2032)
        : move_tomem_16(read_16((A0 += 2, A0 - 2)),
                        (s32)A1 + (s8)0x0 + (s16)D0); // MOVE.W	(A0)+,0(A1,D0)
    DEF_ROMLOC(2036) : add_toreg_16(0x2, &D0);        // ADDQ.W	#$02,D0
    DEF_ROMLOC(2038) : dec_reg_16(&D1);
    if ((D1 & 0xffff) != 0xffff)
      goto rom_2022; // DBF.W	D1,$2022
    DEF_ROMLOC(203C)
        : move_toreg_16(read_16(0xFFFFF632), &D0); // MOVE.W	$F632,D0
    DEF_ROMLOC(2040) : add_toreg_16(0x2, &D0);     // ADDQ.W	#$02,D0
    DEF_ROMLOC(2042) : move_toreg_16(D0, &D2);     // MOVE.W	D0,D2
    DEF_ROMLOC(2044) : and_toreg_16(0x1E, &D2);    // ANDI.W	#$001E,D2
    if (CCR_EQ) {                                  // BNE.B	$204C
      add_toreg_16(0x2, &D0);                      // ADDQ.W	#$02,D0
    }
    DEF_ROMLOC(204C) : cmp_toreg_16(0x64, &D0); // CMPI.W	#$0064,D0
    if (!CCR_LT) {                              // BLT.B	$205A
      move_tomem_16(0x401, 0xFFFFF634);
      D0 = 0xFFFFFFF4;
    }
    DEF_ROMLOC(205A) : move_tomem_16(D0, 0xFFFFF632); // MOVE.W	D0,$F632
    D0 = 1;
    DEF_ROMLOC(2060) : return true;
  }
  DEF_ROMLOC(2062) : sub_tomem_8(0x1, 0xFFFFF634);    // SUBQ.B	#$01,$F634
  if (!CCR_PL) {                                      // BPL.B	$20B4
    DEF_ROMLOC(2068) : move_tomem_8(0x4, 0xFFFFF634); // MOVE.B	#$04,$F634
    DEF_ROMLOC(206E)
        : move_toreg_16(read_16(0xFFFFF632), &D0); // MOVE.W	$F632,D0
    DEF_ROMLOC(2072) : add_toreg_16(0xC, &D0);     // ADDI.W	#$000C,D0
    DEF_ROMLOC(2076) : cmp_toreg_16(0x30, &D0);    // CMPI.W	#$0030,D0
    if (!CCR_CS) {                                 // BCS.B	$2080
      D0 = 0;
      return false;
    }
    DEF_ROMLOC(2080) : move_tomem_16(D0, 0xFFFFF632); // MOVE.W	D0,$F632
    A0 = 0x20C4;
    A0 += D0;
    A1 = 0xFFFFFB04;
    DEF_ROMLOC(2092)
        : move_tomem_32(read_32((A0 += 4, A0 - 4)),
                        (A1 += 4, A1 - 4)); // MOVE.L	(A0)+,(A1)+
    DEF_ROMLOC(2094)
        : move_tomem_32(read_32((A0 += 4, A0 - 4)),
                        (A1 += 4, A1 - 4)); // MOVE.L	(A0)+,(A1)+
    DEF_ROMLOC(2096)
        : move_tomem_16(read_16((A0 += 2, A0 - 2)),
                        A1); // MOVE.W	(A0)+,(A1)
    A1 = 0xFFFFFB20;
    D0 = 0x0;
    D1 = 0x2C;
    DEF_ROMLOC(20A0) : move_toreg_16(D0, &D2);  // MOVE.W	D0,D2
    DEF_ROMLOC(20A2) : and_toreg_16(0x1E, &D2); // ANDI.W	#$001E,D2
    if (GETWORD(D2) == 0) {                     // BNE.B	$20AA
      add_toreg_16(0x2, &D0);                   // ADDQ.W	#$02,D0
    }
    DEF_ROMLOC(20AA)
        : move_tomem_16(read_16(A0),
                        (s32)A1 + (s8)0x0 + (s16)D0); // MOVE.W	(A0),0(A1,D0)
    DEF_ROMLOC(20AE) : add_toreg_16(0x2, &D0);        // ADDQ.W	#$02,D0
    DEF_ROMLOC(20B0) : dec_reg_16(&D1);
    if ((D1 & 0xffff) != 0xffff)
      goto rom_20A0; // DBF.W	D1,$20A0
  }
  D0 = 1;
  return true;
}

void sega_init_part2(void);
void sega_init(void) {
  SETBYTE(SR, 0x04);
  DEF_ROMLOC(2DD2) : move_toreg_8(COMSFX_STOP, &D0); // MOVE.B	#$E4,D0
  DEF_ROMLOC(2DD6) : play_sound_special();           // BSR.W	$1394
  DEF_ROMLOC(2DDA) : clear_plc();                    // BSR.W	$15D6
  DEF_ROMLOC(2DDE) : game_state = sega_init_part2;
  palette_fade_out(); // BSR.W	$1E4A
}
void sega_init_part2(void) {
  A6 = 0xC00004;
  write_16(A6, 0x8004);
  write_16(A6, 0x8230);
  write_16(A6, 0x8407);
  write_16(A6, 0x8700);
  write_16(A6, 0x8B00);
  DEF_ROMLOC(2DFC) : clr_mem_8(0xFFFFF64E);     // CLR.B	$F64E
  DEF_ROMLOC(2E00) : move_tosr_16(0x2700, &SR); // MOVE.W	#$2700,SR
  DEF_ROMLOC(2E04)
      : move_toreg_16(read_16(0xFFFFF60C), &D0);   // MOVE.W	$F60C,D0
  DEF_ROMLOC(2E08) : and_toreg_8(0xFFFFFFBF, &D0); // ANDI.B	#$BF,D0
  DEF_ROMLOC(2E0C) : move_tomem_16(D0, 0xC00004);  // MOVE.W	D0,$00C00004
  DEF_ROMLOC(2E12) : clear_screen();               // BSR.W	$12C4
  write_32(0xC00004, 0x40000000);
  A0 = 0x1E700;
  DEF_ROMLOC(2E26) : decompress_nemesis(); // BSR.W	$1438
  A1 = v_256x256;
  A0 = 0x1EB70;
  DEF_ROMLOC(2E36) : move_toreg_16(0x0, &D0); // MOVE.W	#$0000,D0
  DEF_ROMLOC(2E3A) : decompress_enigma();     // BSR.W	$1716
  A1 = v_256x256;
  D0 = 0x65100003;
  D1 = 0x17;
  D2 = 0x7;
  DEF_ROMLOC(2E4E) : copy_tilemap_to_vram(); // BSR.W	$1418
  A1 = v_256x256 + 0x180;
  D0 = 0x40000003;
  D1 = 0x27;
  D2 = 0x1B;
  DEF_ROMLOC(2E62) : copy_tilemap_to_vram(); // BSR.W	$1418
  if ((read_8(0xFFFFFFF8) & 0x80) == 0) {    // BMI.B	$2E80
    A1 = v_256x256 + 0xA40;
    D0 = 0x453A0003;
    D1 = 2;
    D2 = 1;
    copy_tilemap_to_vram(); // BSR.W	$1418
  }
  D0 = 0;
  DEF_ROMLOC(2E82) : load_palette(); // BSR.W	$2110
  DEF_ROMLOC(2E86)
      : move_tomem_16(0xFFFFFFF6, 0xFFFFF632);       // MOVE.W	#$FFF6,$F632
  DEF_ROMLOC(2E8C) : move_tomem_16(0x0, 0xFFFFF634); // MOVE.W	#$0000,$F634
  DEF_ROMLOC(2E92) : move_tomem_16(0x0, 0xFFFFF662); // MOVE.W	#$0000,$F662
  DEF_ROMLOC(2E98) : move_tomem_16(0x0, 0xFFFFF660); // MOVE.W	#$0000,$F660
  DEF_ROMLOC(2E9E)
      : move_toreg_16(read_16(0xFFFFF60C), &D0);  // MOVE.W	$F60C,D0
  DEF_ROMLOC(2EA2) : or_toreg_8(0x40, &D0);       // ORI.B	#$40,D0
  DEF_ROMLOC(2EA6) : move_tomem_16(D0, 0xC00004); // MOVE.W	D0,$00C00004
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
  DEF_ROMLOC(2EBC) : move_toreg_8(COMSFX_SEGA, &D0); // MOVE.B	#$E1,D0
  DEF_ROMLOC(2EC0) : play_sound_special();           // BSR.W	$1394
  end_frame(0x14);
  game_state = sega_end_wait_start;
}
void sega_wait_end_loop(void);
void sega_end_wait_start(void) {
  DEF_ROMLOC(2ECE) : move_tomem_16(0x1E, 0xFFFFF614); // MOVE.W	#$001E,$F614
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