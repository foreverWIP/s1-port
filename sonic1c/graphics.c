// #define CHECK_STUFF 1
#include "opcodes.h"
#include "system.h"
#include "graphics.h"

void move_screen_horiz(void);
void draw_bg_layer_2(void);
void draw_bg_layer_3(void);
void draw_blocks_scroll_vert(void);
void draw_blocks_scroll_horiz_full(void);
void draw_blocks_scroll_horiz(void);
void get_block_data_relative(void);
void get_block_data(void);
void draw_chunks(void);
void draw_bg_ghz(void);
void draw_bg_mz(void);
void draw_bg_sbz(void);
void draw_bg_end(void);

void vdp_setup(void) {
  DEF_ROMLOC(1222)
      : move_toreg_32(VDP_CONTROL_PORT, &A0); // LEA.L	$00C00004,A0
  DEF_ROMLOC(1228)
      : move_toreg_32(VDP_DATA_PORT, &A1);       // LEA.L	$00C00000,A1
  DEF_ROMLOC(122E) : move_toreg_32(0x129E, &A2); // LEA.L	$0000129E,A2
  DEF_ROMLOC(1234) : move_toreg_32(0x12, &D7);   // MOVEQ.L	$12,D7
  DEF_ROMLOC(1236)
      : write_vdp_control_16(read_16((A2 += 2, A2 - 2)));
  DEF_ROMLOC(1238) : dec_reg_16(&D7);
  if ((D7 & 0xffff) != 0xffff)
    goto rom_1236; // DBF.W	D7,$1236
  DEF_ROMLOC(123C)
      : move_toreg_16(read_16(0x12A0), &D0);        // MOVE.W	$000012A0,D0
  DEF_ROMLOC(1242) : move_tomem_16(D0, 0xFFFFF60C); // MOVE.W	D0,$F60C
  DEF_ROMLOC(1246)
      : move_tomem_16(0xFFFF8ADF, 0xFFFFF624); // MOVE.W	#$8ADF,$F624
  DEF_ROMLOC(124C) : move_toreg_32(0x0, &D0);  // MOVEQ.L	$00,D0
  DEF_ROMLOC(124E)
      : set_cram_ptr_direct(0x00);
  DEF_ROMLOC(1258) : move_toreg_16(0x3F, &D7); // MOVE.W	#$003F,D7
  DEF_ROMLOC(125C) : write_vdp_data_16(D0);
  DEF_ROMLOC(125E) : dec_reg_16(&D7);
  if ((D7 & 0xffff) != 0xffff)
    goto rom_125C;                               // DBF.W	D7,$125C
  DEF_ROMLOC(1262) : clr_mem_32(0xFFFFF616);     // CLR.L	$F616
  DEF_ROMLOC(1266) : clr_mem_32(0xFFFFF61A);     // CLR.L	$F61A
  DEF_ROMLOC(126A) : 
  DEF_ROMLOC(126C) : fill_vram(0, 0, 0);
  DEF_ROMLOC(129C) : return;                            // RTS
}

void clear_screen(void) {
  DEF_ROMLOC(12C4) : fill_vram(0, VRAM_FG, VRAM_FG + PLANE_SIZE_64X32);
  DEF_ROMLOC(12F2) : fill_vram(0, VRAM_BG, VRAM_BG + PLANE_SIZE_64X32);
  DEF_ROMLOC(1320) : clr_mem_32(0xFFFFF616);          // CLR.L	$F616
  DEF_ROMLOC(1324) : clr_mem_32(0xFFFFF61A);          // CLR.L	$F61A
  DEF_ROMLOC(1328) : move_toreg_32(0xFFFFF800, &A1);  // LEA.L	$F800,A1
  DEF_ROMLOC(132C) : move_toreg_32(0x0, &D0);         // MOVEQ.L	$00,D0
  DEF_ROMLOC(132E) : move_toreg_16(0xA0, &D1);        // MOVE.W	#$00A0,D1
  DEF_ROMLOC(1332) : move_tomem_32(D0, (A1 += 4, A1 - 4)); // MOVE.L	D0,(A1)+
  DEF_ROMLOC(1334) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_1332;                                         // DBF.W	D1,$1332
  DEF_ROMLOC(1338) : move_toreg_32(0xFFFFCC00, &A1);       // LEA.L	$CC00,A1
  DEF_ROMLOC(133C) : move_toreg_32(0x0, &D0);              // MOVEQ.L	$00,D0
  DEF_ROMLOC(133E) : move_toreg_16(0x100, &D1);            // MOVE.W	#$0100,D1
  DEF_ROMLOC(1342) : move_tomem_32(D0, (A1 += 4, A1 - 4)); // MOVE.L	D0,(A1)+
  DEF_ROMLOC(1344) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_1342;           // DBF.W	D1,$1342
  DEF_ROMLOC(1348) : return; // RTS
}
void copy_tilemap_to_vram(u32 src_addr, u32 dst_command, u8 width, u8 height) {
  A1 = src_addr;
  D0 = dst_command;
  D1 = width;
  D2 = height;
  A6 = VDP_DATA_PORT; // LEA.L	$00C00000,A6
  D4 = 0x800000;      // MOVE.L	#$00800000,D4
  do {
	write_vdp_control_32(D0);
    move_toreg_16(D1, &D3);              // MOVE.W	D1,D3
    do {
      write_vdp_data_16(read_16(A1));
      A1 += 2;
      dec_reg_16(&D3);
    } while ((D3 & 0xffff) != 0xffff);
    D0 += 0x800000;
    dec_reg_16(&D2);
  } while ((D2 & 0xffff) != 0xffff);
}
void handle_scroll_horiz(void) {
  DEF_ROMLOC(68DA)
      : move_toreg_16(read_16(v_screenposx), &D4); // MOVE.W	$F700,D4
  DEF_ROMLOC(68DE) : move_screen_horiz();          // BSR.B	$690E
  DEF_ROMLOC(68E0)
      : move_toreg_16(read_16(v_screenposx), &D0);          // MOVE.W	$F700,D0
  DEF_ROMLOC(68E4) : and_toreg_16(0x10, &D0);               // ANDI.W	#$0010,D0
  DEF_ROMLOC(68E8) : move_toreg_8(read_8(0xFFFFF74A), &D1); // MOVE.B	$F74A,D1
  DEF_ROMLOC(68EC) : eor_toreg_8(D1, &D0);                  // EOR.B	D1,D0
  DEF_ROMLOC(68EE) : if (!CCR_EQ) goto rom_690C;            // BNE.B	$690C
  DEF_ROMLOC(68F0) : eor_tomem_8(0x10, 0xFFFFF74A);         // EORI.B	#$10,$F74A
  DEF_ROMLOC(68F6)
      : move_toreg_16(read_16(v_screenposx), &D0);  // MOVE.W	$F700,D0
  DEF_ROMLOC(68FA) : sub_toreg_16(D4, &D0);         // SUB.W	D4,D0
  DEF_ROMLOC(68FC) : if (CCR_PL) goto rom_6906;     // BPL.B	$6906
  DEF_ROMLOC(68FE) : bset_tomem_8(0x2, 0xFFFFF754); // BSET.B	#$02,$F754
  DEF_ROMLOC(6904) : return;                        // RTS
  DEF_ROMLOC(6906) : bset_tomem_8(0x3, 0xFFFFF754); // BSET.B	#$03,$F754
  DEF_ROMLOC(690C) : return;                        // RTS
}
void move_screen_horiz(void) {
  DEF_ROMLOC(690E)
      : move_toreg_16(read_16(0xFFFFD008), &D0); // MOVE.W	$D008,D0
  DEF_ROMLOC(6912)
      : sub_toreg_16(read_16(v_screenposx), &D0); // SUB.W	$F700,D0
  DEF_ROMLOC(6916) : sub_toreg_16((GAME_WIDTH / 2) - 16, &D0);     // SUBI.W	#$0090,D0
  DEF_ROMLOC(691A) : if (CCR_CS) goto rom_6952;   // BCS.B	$6952
  DEF_ROMLOC(691C) : sub_toreg_16(0x10, &D0);     // SUBI.W	#$0010,D0
  DEF_ROMLOC(6920) : if (CCR_CC) goto rom_6928;   // BCC.B	$6928
  DEF_ROMLOC(6922) : clr_mem_16(0xFFFFF73A);      // CLR.W	$F73A
  DEF_ROMLOC(6926) : return;                      // RTS
  DEF_ROMLOC(6928) : cmp_toreg_16(0x10, &D0);     // CMPI.W	#$0010,D0
  DEF_ROMLOC(692C) : if (CCR_CS) goto rom_6932;   // BCS.B	$6932
  DEF_ROMLOC(692E) : move_toreg_16(0x10, &D0);    // MOVE.W	#$0010,D0
  DEF_ROMLOC(6932)
      : add_toreg_16(read_16(v_screenposx), &D0); // ADD.W	$F700,D0
  DEF_ROMLOC(6936)
      : cmp_toreg_16(read_16(v_limitright2), &D0); // CMP.W	$F72A,D0
  DEF_ROMLOC(693A) : if (CCR_LT) goto rom_6940;    // BLT.B	$6940
  DEF_ROMLOC(693C)
      : move_toreg_16(read_16(v_limitright2), &D0); // MOVE.W	$F72A,D0
  DEF_ROMLOC(6940) : move_toreg_16(D0, &D1);        // MOVE.W	D0,D1
  DEF_ROMLOC(6942)
      : sub_toreg_16(read_16(v_screenposx), &D1);     // SUB.W	$F700,D1
  DEF_ROMLOC(6946) : asl_toreg_16(0x8, &D1);          // ASL.W	#$08,D1
  DEF_ROMLOC(6948) : move_tomem_16(D0, v_screenposx); // MOVE.W	D0,$F700
  DEF_ROMLOC(694C) : move_tomem_16(D1, 0xFFFFF73A);   // MOVE.W	D1,$F73A
  DEF_ROMLOC(6950) : return;                          // RTS
  DEF_ROMLOC(6952)
      : add_toreg_16(read_16(v_screenposx), &D0); // ADD.W	$F700,D0
  DEF_ROMLOC(6956)
      : cmp_toreg_16(read_16(v_limitleft2), &D0); // CMP.W	$F728,D0
  DEF_ROMLOC(695A) : if (CCR_GT) goto rom_6940;   // BGT.B	$6940
  DEF_ROMLOC(695C)
      : move_toreg_16(read_16(v_limitleft2), &D0);   // MOVE.W	$F728,D0
  DEF_ROMLOC(6960) : goto rom_6940;                  // BRA.B	$6940
  DEF_ROMLOC(6962) : tst_reg_16(&D0);                // TST.W	D0
  DEF_ROMLOC(6964) : if (CCR_PL) goto rom_696C;      // BPL.B	$696C
  DEF_ROMLOC(6966) : move_toreg_16(0xFFFFFFFE, &D0); // MOVE.W	#$FFFE,D0
  goto rom_6952;                                     // BRA.B	$6952
  DEF_ROMLOC(696C) : move_toreg_16(0x2, &D0);        // MOVE.W	#$0002,D0
  goto rom_6928;                                     // BRA.B	$6928
}
void handle_scroll_vert(void) {
  DEF_ROMLOC(6972) : move_toreg_32(0x0, &D1); // MOVEQ.L	$00,D1
  DEF_ROMLOC(6974)
      : move_toreg_16(read_16(0xFFFFD00C), &D0); // MOVE.W	$D00C,D0
  DEF_ROMLOC(6978)
      : sub_toreg_16(read_16(0xFFFFF704), &D0);     // SUB.W	$F704,D0
  DEF_ROMLOC(697C) : btst_tomem_8(0x2, 0xFFFFD022); // BTST.B	#$02,$D022
  DEF_ROMLOC(6982) : if (CCR_EQ) goto rom_6986;     // BEQ.B	$6986
  DEF_ROMLOC(6984) : sub_toreg_16(0x5, &D0);        // SUBQ.W	#$05,D0
  DEF_ROMLOC(6986) : btst_tomem_8(0x1, 0xFFFFD022); // BTST.B	#$01,$D022
  DEF_ROMLOC(698C) : if (CCR_EQ) goto rom_69A6;     // BEQ.B	$69A6
  DEF_ROMLOC(698E) : add_toreg_16(0x20, &D0);       // ADDI.W	#$0020,D0
  DEF_ROMLOC(6992) : sub_toreg_16(read_16(0xFFFFF73E), &D0); // SUB.W	$F73E,D0
  DEF_ROMLOC(6996) : if (CCR_CS) goto rom_69F2;              // BCS.B	$69F2
  DEF_ROMLOC(6998) : sub_toreg_16(0x40, &D0);                // SUBI.W	#$0040,D0
  DEF_ROMLOC(699C) : if (CCR_CC) goto rom_69F2;              // BCC.B	$69F2
  DEF_ROMLOC(699E) : tst_mem_8(0xFFFFF75C);                  // TST.B	$F75C
  DEF_ROMLOC(69A2) : if (!CCR_EQ) goto rom_6A04;             // BNE.B	$6A04
  goto rom_69B2;                                             // BRA.B	$69B2
  DEF_ROMLOC(69A6) : sub_toreg_16(read_16(0xFFFFF73E), &D0); // SUB.W	$F73E,D0
  DEF_ROMLOC(69AA) : if (!CCR_EQ) goto rom_69B8;             // BNE.B	$69B8
  DEF_ROMLOC(69AC) : tst_mem_8(0xFFFFF75C);                  // TST.B	$F75C
  DEF_ROMLOC(69B0) : if (!CCR_EQ) goto rom_6A04;             // BNE.B	$6A04
  DEF_ROMLOC(69B2) : clr_mem_16(0xFFFFF73C);                 // CLR.W	$F73C
  DEF_ROMLOC(69B6) : return;                                 // RTS
  DEF_ROMLOC(69B8) : cmp_tomem_16(0x60, 0xFFFFF73E); // CMPI.W	#$0060,$F73E
  DEF_ROMLOC(69BE) : if (!CCR_EQ) goto rom_69E0;     // BNE.B	$69E0
  DEF_ROMLOC(69C0)
      : move_toreg_16(read_16(0xFFFFD014), &D1);             // MOVE.W	$D014,D1
  DEF_ROMLOC(69C4) : if (CCR_PL) goto rom_69C8;              // BPL.B	$69C8
  DEF_ROMLOC(69C6) : neg_reg_16(&D1);                        // NEG.W	D1
  DEF_ROMLOC(69C8) : cmp_toreg_16(0x800, &D1);               // CMPI.W	#$0800,D1
  DEF_ROMLOC(69CC) : if (CCR_CC) goto rom_69F2;              // BCC.B	$69F2
  DEF_ROMLOC(69CE) : move_toreg_16(0x600, &D1);              // MOVE.W	#$0600,D1
  DEF_ROMLOC(69D2) : cmp_toreg_16(0x6, &D0);                 // CMPI.W	#$0006,D0
  DEF_ROMLOC(69D6) : if (CCR_GT) goto rom_6A52;              // BGT.B	$6A52
  DEF_ROMLOC(69D8) : cmp_toreg_16(0xFFFFFFFA, &D0);          // CMPI.W	#$FFFA,D0
  DEF_ROMLOC(69DC) : if (CCR_LT) goto rom_6A1C;              // BLT.B	$6A1C
  goto rom_6A0A;                                             // BRA.B	$6A0A
  DEF_ROMLOC(69E0) : move_toreg_16(0x200, &D1);              // MOVE.W	#$0200,D1
  DEF_ROMLOC(69E4) : cmp_toreg_16(0x2, &D0);                 // CMPI.W	#$0002,D0
  DEF_ROMLOC(69E8) : if (CCR_GT) goto rom_6A52;              // BGT.B	$6A52
  DEF_ROMLOC(69EA) : cmp_toreg_16(0xFFFFFFFE, &D0);          // CMPI.W	#$FFFE,D0
  DEF_ROMLOC(69EE) : if (CCR_LT) goto rom_6A1C;              // BLT.B	$6A1C
  goto rom_6A0A;                                             // BRA.B	$6A0A
  DEF_ROMLOC(69F2) : move_toreg_16(0x1000, &D1);             // MOVE.W	#$1000,D1
  DEF_ROMLOC(69F6) : cmp_toreg_16(0x10, &D0);                // CMPI.W	#$0010,D0
  DEF_ROMLOC(69FA) : if (CCR_GT) goto rom_6A52;              // BGT.B	$6A52
  DEF_ROMLOC(69FC) : cmp_toreg_16(0xFFFFFFF0, &D0);          // CMPI.W	#$FFF0,D0
  DEF_ROMLOC(6A00) : if (CCR_LT) goto rom_6A1C;              // BLT.B	$6A1C
  goto rom_6A0A;                                             // BRA.B	$6A0A
  DEF_ROMLOC(6A04) : move_toreg_32(0x0, &D0);                // MOVEQ.L	$00,D0
  DEF_ROMLOC(6A06) : move_tomem_8(D0, 0xFFFFF75C);           // MOVE.B	D0,$F75C
  DEF_ROMLOC(6A0A) : move_toreg_32(0x0, &D1);                // MOVEQ.L	$00,D1
  DEF_ROMLOC(6A0C) : move_toreg_16(D0, &D1);                 // MOVE.W	D0,D1
  DEF_ROMLOC(6A0E) : add_toreg_16(read_16(0xFFFFF704), &D1); // ADD.W	$F704,D1
  DEF_ROMLOC(6A12) : tst_reg_16(&D0);                        // TST.W	D0
  DEF_ROMLOC(6A14) : if (CCR_PL) goto rom_6A5C;              // BPL.W	$6A5C
  goto rom_6A28;                                             // BRA.W	$6A28
  DEF_ROMLOC(6A1C) : neg_reg_16(&D1);                        // NEG.W	D1
  DEF_ROMLOC(6A1E) : ext_reg_32(&D1);                        // EXT.L	D1
  DEF_ROMLOC(6A20) : asl_toreg_32(0x8, &D1);                 // ASL.L	#$08,D1
  DEF_ROMLOC(6A22) : add_toreg_32(read_32(0xFFFFF704), &D1); // ADD.L	$F704,D1
  DEF_ROMLOC(6A26) : SWAPWORDS(D1);                          // SWAP.W	D1
  DEF_ROMLOC(6A28) : cmp_toreg_16(read_16(0xFFFFF72C), &D1); // CMP.W	$F72C,D1
  DEF_ROMLOC(6A2C) : if (CCR_GT) goto rom_6A80;              // BGT.B	$6A80
  DEF_ROMLOC(6A2E) : cmp_toreg_16(0xFFFFFF00, &D1);          // CMPI.W	#$FF00,D1
  DEF_ROMLOC(6A32) : if (CCR_GT) goto rom_6A4C;              // BGT.B	$6A4C
  DEF_ROMLOC(6A34) : and_toreg_16(0x7FF, &D1);               // ANDI.W	#$07FF,D1
  DEF_ROMLOC(6A38) : and_tomem_16(0x7FF, 0xFFFFD00C); // ANDI.W	#$07FF,$D00C
  DEF_ROMLOC(6A3E) : and_tomem_16(0x7FF, 0xFFFFF704); // ANDI.W	#$07FF,$F704
  DEF_ROMLOC(6A44) : and_tomem_16(0x3FF, 0xFFFFF70C); // ANDI.W	#$03FF,$F70C
  goto rom_6A80;                                      // BRA.B	$6A80
  DEF_ROMLOC(6A4C)
      : move_toreg_16(read_16(0xFFFFF72C), &D1);             // MOVE.W	$F72C,D1
  goto rom_6A80;                                             // BRA.B	$6A80
  DEF_ROMLOC(6A52) : ext_reg_32(&D1);                        // EXT.L	D1
  DEF_ROMLOC(6A54) : asl_toreg_32(0x8, &D1);                 // ASL.L	#$08,D1
  DEF_ROMLOC(6A56) : add_toreg_32(read_32(0xFFFFF704), &D1); // ADD.L	$F704,D1
  DEF_ROMLOC(6A5A) : SWAPWORDS(D1);                          // SWAP.W	D1
  DEF_ROMLOC(6A5C) : cmp_toreg_16(read_16(0xFFFFF72E), &D1); // CMP.W	$F72E,D1
  DEF_ROMLOC(6A60) : if (CCR_LT) goto rom_6A80;              // BLT.B	$6A80
  DEF_ROMLOC(6A62) : sub_toreg_16(0x800, &D1);               // SUBI.W	#$0800,D1
  DEF_ROMLOC(6A66) : if (CCR_CS) goto rom_6A7C;              // BCS.B	$6A7C
  DEF_ROMLOC(6A68) : and_tomem_16(0x7FF, 0xFFFFD00C); // ANDI.W	#$07FF,$D00C
  DEF_ROMLOC(6A6E) : sub_tomem_16(0x800, 0xFFFFF704); // SUBI.W	#$0800,$F704
  DEF_ROMLOC(6A74) : and_tomem_16(0x3FF, 0xFFFFF70C); // ANDI.W	#$03FF,$F70C
  goto rom_6A80;                                      // BRA.B	$6A80
  DEF_ROMLOC(6A7C)
      : move_toreg_16(read_16(0xFFFFF72E), &D1); // MOVE.W	$F72E,D1
  DEF_ROMLOC(6A80)
      : move_toreg_16(read_16(0xFFFFF704), &D4); // MOVE.W	$F704,D4
  DEF_ROMLOC(6A84) : SWAPWORDS(D1);              // SWAP.W	D1
  DEF_ROMLOC(6A86) : move_toreg_32(D1, &D3);     // MOVE.L	D1,D3
  DEF_ROMLOC(6A88)
      : sub_toreg_32(read_32(0xFFFFF704), &D3);     // SUB.L	$F704,D3
  DEF_ROMLOC(6A8C) : ror_toreg_32(0x8, &D3);        // ROR.L	#$08,D3
  DEF_ROMLOC(6A8E) : move_tomem_16(D3, 0xFFFFF73C); // MOVE.W	D3,$F73C
  DEF_ROMLOC(6A92) : move_tomem_32(D1, 0xFFFFF704); // MOVE.L	D1,$F704
  DEF_ROMLOC(6A96)
      : move_toreg_16(read_16(0xFFFFF704), &D0);            // MOVE.W	$F704,D0
  DEF_ROMLOC(6A9A) : and_toreg_16(0x10, &D0);               // ANDI.W	#$0010,D0
  DEF_ROMLOC(6A9E) : move_toreg_8(read_8(0xFFFFF74B), &D1); // MOVE.B	$F74B,D1
  DEF_ROMLOC(6AA2) : eor_toreg_8(D1, &D0);                  // EOR.B	D1,D0
  DEF_ROMLOC(6AA4) : if (!CCR_EQ) goto rom_6AC2;            // BNE.B	$6AC2
  DEF_ROMLOC(6AA6) : eor_tomem_8(0x10, 0xFFFFF74B);         // EORI.B	#$10,$F74B
  DEF_ROMLOC(6AAC)
      : move_toreg_16(read_16(0xFFFFF704), &D0);    // MOVE.W	$F704,D0
  DEF_ROMLOC(6AB0) : sub_toreg_16(D4, &D0);         // SUB.W	D4,D0
  DEF_ROMLOC(6AB2) : if (CCR_PL) goto rom_6ABC;     // BPL.B	$6ABC
  DEF_ROMLOC(6AB4) : bset_tomem_8(0x0, 0xFFFFF754); // BSET.B	#$00,$F754
  DEF_ROMLOC(6ABA) : return;                        // RTS
  DEF_ROMLOC(6ABC) : bset_tomem_8(0x1, 0xFFFFF754); // BSET.B	#$01,$F754
  DEF_ROMLOC(6AC2) : return;                        // RTS
}
void scroll_bg_full(void) {
  DEF_ROMLOC(6AC4)
      : move_toreg_32(read_32(0xFFFFF708), &D2);    // MOVE.L	$F708,D2
  DEF_ROMLOC(6AC8) : move_toreg_32(D2, &D0);        // MOVE.L	D2,D0
  DEF_ROMLOC(6ACA) : add_toreg_32(D4, &D0);         // ADD.L	D4,D0
  DEF_ROMLOC(6ACC) : move_tomem_32(D0, 0xFFFFF708); // MOVE.L	D0,$F708
  DEF_ROMLOC(6AD0) : move_toreg_32(D0, &D1);        // MOVE.L	D0,D1
  DEF_ROMLOC(6AD2) : SWAPWORDS(D1);                 // SWAP.W	D1
  DEF_ROMLOC(6AD4) : and_toreg_16(0x10, &D1);       // ANDI.W	#$0010,D1
  DEF_ROMLOC(6AD8)
      : move_toreg_8(read_8(0xFFFFF74C), &D3); // MOVE.B	$F74C,D3
  DEF_ROMLOC(6ADC) : eor_toreg_8(D3, &D1);     // EOR.B	D3,D1
  DEF_ROMLOC(6ADE) : if (!CCR_EQ) {
    scroll_bg_y_relative();
    return;
  } // BNE.B	$6AF8
  DEF_ROMLOC(6AE0) : eor_tomem_8(0x10, 0xFFFFF74C); // EORI.B	#$10,$F74C
  DEF_ROMLOC(6AE6) : sub_toreg_32(D2, &D0);         // SUB.L	D2,D0
  DEF_ROMLOC(6AE8) : if (CCR_PL) goto rom_6AF2;     // BPL.B	$6AF2
  DEF_ROMLOC(6AEA) : bset_tomem_8(0x2, 0xFFFFF756); // BSET.B	#$02,$F756
  DEF_ROMLOC(6AF0) : scroll_bg_y_relative();
  return;                                           // BRA.B	$6AF8
  DEF_ROMLOC(6AF2) : bset_tomem_8(0x3, 0xFFFFF756); // BSET.B	#$03,$F756
  scroll_bg_y_relative();
}
void scroll_bg_y_relative(void) {
  DEF_ROMLOC(6AF8)
      : move_toreg_32(read_32(0xFFFFF70C), &D3);            // MOVE.L	$F70C,D3
  DEF_ROMLOC(6AFC) : move_toreg_32(D3, &D0);                // MOVE.L	D3,D0
  DEF_ROMLOC(6AFE) : add_toreg_32(D5, &D0);                 // ADD.L	D5,D0
  DEF_ROMLOC(6B00) : move_tomem_32(D0, 0xFFFFF70C);         // MOVE.L	D0,$F70C
  DEF_ROMLOC(6B04) : move_toreg_32(D0, &D1);                // MOVE.L	D0,D1
  DEF_ROMLOC(6B06) : SWAPWORDS(D1);                         // SWAP.W	D1
  DEF_ROMLOC(6B08) : and_toreg_16(0x10, &D1);               // ANDI.W	#$0010,D1
  DEF_ROMLOC(6B0C) : move_toreg_8(read_8(0xFFFFF74D), &D2); // MOVE.B	$F74D,D2
  DEF_ROMLOC(6B10) : eor_toreg_8(D2, &D1);                  // EOR.B	D2,D1
  DEF_ROMLOC(6B12) : if (!CCR_EQ) goto rom_6B2C;            // BNE.B	$6B2C
  DEF_ROMLOC(6B14) : eor_tomem_8(0x10, 0xFFFFF74D);         // EORI.B	#$10,$F74D
  DEF_ROMLOC(6B1A) : sub_toreg_32(D3, &D0);                 // SUB.L	D3,D0
  DEF_ROMLOC(6B1C) : if (CCR_PL) goto rom_6B26;             // BPL.B	$6B26
  DEF_ROMLOC(6B1E) : bset_tomem_8(0x0, 0xFFFFF756);         // BSET.B	#$00,$F756
  DEF_ROMLOC(6B24) : return;                                // RTS
  DEF_ROMLOC(6B26) : bset_tomem_8(0x1, 0xFFFFF756);         // BSET.B	#$01,$F756
  DEF_ROMLOC(6B2C) : return;                                // RTS
}
void scroll_bg_y(void) {
  DEF_ROMLOC(6B2E)
      : move_toreg_32(read_32(0xFFFFF70C), &D3);            // MOVE.L	$F70C,D3
  DEF_ROMLOC(6B32) : move_toreg_32(D3, &D0);                // MOVE.L	D3,D0
  DEF_ROMLOC(6B34) : add_toreg_32(D5, &D0);                 // ADD.L	D5,D0
  DEF_ROMLOC(6B36) : move_tomem_32(D0, 0xFFFFF70C);         // MOVE.L	D0,$F70C
  DEF_ROMLOC(6B3A) : move_toreg_32(D0, &D1);                // MOVE.L	D0,D1
  DEF_ROMLOC(6B3C) : SWAPWORDS(D1);                         // SWAP.W	D1
  DEF_ROMLOC(6B3E) : and_toreg_16(0x10, &D1);               // ANDI.W	#$0010,D1
  DEF_ROMLOC(6B42) : move_toreg_8(read_8(0xFFFFF74D), &D2); // MOVE.B	$F74D,D2
  DEF_ROMLOC(6B46) : eor_toreg_8(D2, &D1);                  // EOR.B	D2,D1
  DEF_ROMLOC(6B48) : if (!CCR_EQ) goto rom_6B62;            // BNE.B	$6B62
  DEF_ROMLOC(6B4A) : eor_tomem_8(0x10, 0xFFFFF74D);         // EORI.B	#$10,$F74D
  DEF_ROMLOC(6B50) : sub_toreg_32(D3, &D0);                 // SUB.L	D3,D0
  DEF_ROMLOC(6B52) : if (CCR_PL) goto rom_6B5C;             // BPL.B	$6B5C
  DEF_ROMLOC(6B54) : bset_tomem_8(0x4, 0xFFFFF756);         // BSET.B	#$04,$F756
  DEF_ROMLOC(6B5A) : return;                                // RTS
  DEF_ROMLOC(6B5C) : bset_tomem_8(0x5, 0xFFFFF756);         // BSET.B	#$05,$F756
  DEF_ROMLOC(6B62) : return;                                // RTS
}
void scroll_bg_y_absolute(void) {
  DEF_ROMLOC(6B64)
      : move_toreg_16(read_16(0xFFFFF70C), &D3);            // MOVE.W	$F70C,D3
  DEF_ROMLOC(6B68) : move_tomem_16(D0, 0xFFFFF70C);         // MOVE.W	D0,$F70C
  DEF_ROMLOC(6B6C) : move_toreg_16(D0, &D1);                // MOVE.W	D0,D1
  DEF_ROMLOC(6B6E) : and_toreg_16(0x10, &D1);               // ANDI.W	#$0010,D1
  DEF_ROMLOC(6B72) : move_toreg_8(read_8(0xFFFFF74D), &D2); // MOVE.B	$F74D,D2
  DEF_ROMLOC(6B76) : eor_toreg_8(D2, &D1);                  // EOR.B	D2,D1
  DEF_ROMLOC(6B78) : if (!CCR_EQ) goto rom_6B92;            // BNE.B	$6B92
  DEF_ROMLOC(6B7A) : eor_tomem_8(0x10, 0xFFFFF74D);         // EORI.B	#$10,$F74D
  DEF_ROMLOC(6B80) : sub_toreg_16(D3, &D0);                 // SUB.W	D3,D0
  DEF_ROMLOC(6B82) : if (CCR_PL) goto rom_6B8C;             // BPL.B	$6B8C
  DEF_ROMLOC(6B84) : bset_tomem_8(0x0, 0xFFFFF756);         // BSET.B	#$00,$F756
  DEF_ROMLOC(6B8A) : return;                                // RTS
  DEF_ROMLOC(6B8C) : bset_tomem_8(0x1, 0xFFFFF756);         // BSET.B	#$01,$F756
  DEF_ROMLOC(6B92) : return;                                // RTS
}
void scroll_bg_layer_1(void) {
  DEF_ROMLOC(6B94)
      : move_toreg_32(read_32(0xFFFFF708), &D2);            // MOVE.L	$F708,D2
  DEF_ROMLOC(6B98) : move_toreg_32(D2, &D0);                // MOVE.L	D2,D0
  DEF_ROMLOC(6B9A) : add_toreg_32(D4, &D0);                 // ADD.L	D4,D0
  DEF_ROMLOC(6B9C) : move_tomem_32(D0, 0xFFFFF708);         // MOVE.L	D0,$F708
  DEF_ROMLOC(6BA0) : move_toreg_32(D0, &D1);                // MOVE.L	D0,D1
  DEF_ROMLOC(6BA2) : SWAPWORDS(D1);                         // SWAP.W	D1
  DEF_ROMLOC(6BA4) : and_toreg_16(0x10, &D1);               // ANDI.W	#$0010,D1
  DEF_ROMLOC(6BA8) : move_toreg_8(read_8(0xFFFFF74C), &D3); // MOVE.B	$F74C,D3
  DEF_ROMLOC(6BAC) : eor_toreg_8(D3, &D1);                  // EOR.B	D3,D1
  DEF_ROMLOC(6BAE) : if (!CCR_EQ) goto rom_6BC6;            // BNE.B	$6BC6
  DEF_ROMLOC(6BB0) : eor_tomem_8(0x10, 0xFFFFF74C);         // EORI.B	#$10,$F74C
  DEF_ROMLOC(6BB6) : sub_toreg_32(D2, &D0);                 // SUB.L	D2,D0
  DEF_ROMLOC(6BB8) : if (CCR_PL) goto rom_6BC0;             // BPL.B	$6BC0
  DEF_ROMLOC(6BBA) : bset_tomem_8(D6, 0xFFFFF756);          // BSET.B	D6,$F756
  DEF_ROMLOC(6BBE) : goto rom_6BC6;                         // BRA.B	$6BC6
  DEF_ROMLOC(6BC0) : add_toreg_8(0x1, &D6);                 // ADDQ.B	#$01,D6
  DEF_ROMLOC(6BC2) : bset_tomem_8(D6, 0xFFFFF756);          // BSET.B	D6,$F756
  DEF_ROMLOC(6BC6) : return;                                // RTS
}
void scroll_bg_layer_2(void) {
  DEF_ROMLOC(6BC8)
      : move_toreg_32(read_32(0xFFFFF710), &D2);            // MOVE.L	$F710,D2
  DEF_ROMLOC(6BCC) : move_toreg_32(D2, &D0);                // MOVE.L	D2,D0
  DEF_ROMLOC(6BCE) : add_toreg_32(D4, &D0);                 // ADD.L	D4,D0
  DEF_ROMLOC(6BD0) : move_tomem_32(D0, 0xFFFFF710);         // MOVE.L	D0,$F710
  DEF_ROMLOC(6BD4) : move_toreg_32(D0, &D1);                // MOVE.L	D0,D1
  DEF_ROMLOC(6BD6) : SWAPWORDS(D1);                         // SWAP.W	D1
  DEF_ROMLOC(6BD8) : and_toreg_16(0x10, &D1);               // ANDI.W	#$0010,D1
  DEF_ROMLOC(6BDC) : move_toreg_8(read_8(0xFFFFF74E), &D3); // MOVE.B	$F74E,D3
  DEF_ROMLOC(6BE0) : eor_toreg_8(D3, &D1);                  // EOR.B	D3,D1
  DEF_ROMLOC(6BE2) : if (!CCR_EQ) goto rom_6BFA;            // BNE.B	$6BFA
  DEF_ROMLOC(6BE4) : eor_tomem_8(0x10, 0xFFFFF74E);         // EORI.B	#$10,$F74E
  DEF_ROMLOC(6BEA) : sub_toreg_32(D2, &D0);                 // SUB.L	D2,D0
  DEF_ROMLOC(6BEC) : if (CCR_PL) goto rom_6BF4;             // BPL.B	$6BF4
  DEF_ROMLOC(6BEE) : bset_tomem_8(D6, 0xFFFFF758);          // BSET.B	D6,$F758
  DEF_ROMLOC(6BF2) : goto rom_6BFA;                         // BRA.B	$6BFA
  DEF_ROMLOC(6BF4) : add_toreg_8(0x1, &D6);                 // ADDQ.B	#$01,D6
  DEF_ROMLOC(6BF6) : bset_tomem_8(D6, 0xFFFFF758);          // BSET.B	D6,$F758
  DEF_ROMLOC(6BFA) : return;                                // RTS
}
void scroll_bg_layer_3(void) {
  DEF_ROMLOC(6BFC)
      : move_toreg_32(read_32(0xFFFFF718), &D2);            // MOVE.L	$F718,D2
  DEF_ROMLOC(6C00) : move_toreg_32(D2, &D0);                // MOVE.L	D2,D0
  DEF_ROMLOC(6C02) : add_toreg_32(D4, &D0);                 // ADD.L	D4,D0
  DEF_ROMLOC(6C04) : move_tomem_32(D0, 0xFFFFF718);         // MOVE.L	D0,$F718
  DEF_ROMLOC(6C08) : move_toreg_32(D0, &D1);                // MOVE.L	D0,D1
  DEF_ROMLOC(6C0A) : SWAPWORDS(D1);                         // SWAP.W	D1
  DEF_ROMLOC(6C0C) : and_toreg_16(0x10, &D1);               // ANDI.W	#$0010,D1
  DEF_ROMLOC(6C10) : move_toreg_8(read_8(0xFFFFF750), &D3); // MOVE.B	$F750,D3
  DEF_ROMLOC(6C14) : eor_toreg_8(D3, &D1);                  // EOR.B	D3,D1
  DEF_ROMLOC(6C16) : if (!CCR_EQ) goto rom_6C2E;            // BNE.B	$6C2E
  DEF_ROMLOC(6C18) : eor_tomem_8(0x10, 0xFFFFF750);         // EORI.B	#$10,$F750
  DEF_ROMLOC(6C1E) : sub_toreg_32(D2, &D0);                 // SUB.L	D2,D0
  DEF_ROMLOC(6C20) : if (CCR_PL) goto rom_6C28;             // BPL.B	$6C28
  DEF_ROMLOC(6C22) : bset_tomem_8(D6, 0xFFFFF75A);          // BSET.B	D6,$F75A
  DEF_ROMLOC(6C26) : goto rom_6C2E;                         // BRA.B	$6C2E
  DEF_ROMLOC(6C28) : add_toreg_8(0x1, &D6);                 // ADDQ.B	#$01,D6
  DEF_ROMLOC(6C2A) : bset_tomem_8(D6, 0xFFFFF75A);          // BSET.B	D6,$F75A
  DEF_ROMLOC(6C2E) : return;                                // RTS
}
void scroll_update_tiles_bg(void) {
  DEF_ROMLOC(6C30)
      : move_toreg_32(VDP_CONTROL_PORT, &A5); // LEA.L	$00C00004,A5
  DEF_ROMLOC(6C36)
      : move_toreg_32(VDP_DATA_PORT, &A6);           // LEA.L
                                                     // $00C00000,A6
  DEF_ROMLOC(6C3C) : move_toreg_32(0xFFFFF756, &A2); // LEA.L	$F756,A2
  DEF_ROMLOC(6C40) : move_toreg_32(0xFFFFF708, &A3); // LEA.L	$F708,A3
  DEF_ROMLOC(6C44) : move_toreg_32(0xFFFFA440, &A4); // LEA.L	$A440,A4
  DEF_ROMLOC(6C48) : move_toreg_16(0x6000, &D2);     // MOVE.W	#$6000,D2
  DEF_ROMLOC(6C4C) : draw_bg_layer_1();              // BSR.W	$6D0A
  DEF_ROMLOC(6C50) : move_toreg_32(0xFFFFF758, &A2); // LEA.L	$F758,A2
  DEF_ROMLOC(6C54) : move_toreg_32(0xFFFFF710, &A3); // LEA.L	$F710,A3
  draw_bg_layer_2();                                 // BRA.W	$6DA6
}
void scroll_update_tiles(void) {
  DEF_ROMLOC(6C5C)
      : move_toreg_32(VDP_CONTROL_PORT, &A5); // LEA.L	$00C00004,A5
  DEF_ROMLOC(6C62)
      : move_toreg_32(VDP_DATA_PORT, &A6);            // LEA.L
                                                      // $00C00000,A6
  DEF_ROMLOC(6C68) : move_toreg_32(0xFFFFFF32, &A2);  // LEA.L	$FF32,A2
  DEF_ROMLOC(6C6C) : move_toreg_32(0xFFFFFF18, &A3);  // LEA.L	$FF18,A3
  DEF_ROMLOC(6C70) : move_toreg_32(0xFFFFA440, &A4);  // LEA.L	$A440,A4
  DEF_ROMLOC(6C74) : move_toreg_16(0x6000, &D2);      // MOVE.W	#$6000,D2
  DEF_ROMLOC(6C78) : draw_bg_layer_1();               // BSR.W	$6D0A
  DEF_ROMLOC(6C7C) : move_toreg_32(0xFFFFFF34, &A2);  // LEA.L	$FF34,A2
  DEF_ROMLOC(6C80) : move_toreg_32(0xFFFFFF20, &A3);  // LEA.L	$FF20,A3
  DEF_ROMLOC(6C84) : draw_bg_layer_2();               // BSR.W	$6DA6
  DEF_ROMLOC(6C88) : move_toreg_32(0xFFFFFF36, &A2);  // LEA.L	$FF36,A2
  DEF_ROMLOC(6C8C) : move_toreg_32(0xFFFFFF28, &A3);  // LEA.L	$FF28,A3
  DEF_ROMLOC(6C90) : draw_bg_layer_3();               // BSR.W	$6EA4
  DEF_ROMLOC(6C94) : move_toreg_32(0xFFFFFF30, &A2);  // LEA.L	$FF30,A2
  DEF_ROMLOC(6C98) : move_toreg_32(0xFFFFFF10, &A3);  // LEA.L	$FF10,A3
  DEF_ROMLOC(6C9C) : move_toreg_32(0xFFFFA400, &A4);  // LEA.L	$A400,A4
  DEF_ROMLOC(6CA0) : move_toreg_16(0x4000, &D2);      // MOVE.W	#$4000,D2
  DEF_ROMLOC(6CA4) : tst_mem_8(A2);                   // TST.B	(A2)
  DEF_ROMLOC(6CA6) : if (CCR_EQ) goto rom_6D08;       // BEQ.B	$6D08
  DEF_ROMLOC(6CA8) : bclr_tomem_8(0x0, A2);           // BCLR.B	#$00,(A2)
  DEF_ROMLOC(6CAC) : if (CCR_EQ) goto rom_6CBE;       // BEQ.B	$6CBE
  DEF_ROMLOC(6CAE) : move_toreg_32(0xFFFFFFF0, &D4);  // MOVEQ.L	$F0,D4
  DEF_ROMLOC(6CB0) : move_toreg_32(0xFFFFFFF0, &D5);  // MOVEQ.L	$F0,D5
  DEF_ROMLOC(6CB2) : calc_vram_pos_relative();        // BSR.W	$7174
  DEF_ROMLOC(6CB6) : move_toreg_32(0xFFFFFFF0, &D4);  // MOVEQ.L	$F0,D4
  DEF_ROMLOC(6CB8) : move_toreg_32(0xFFFFFFF0, &D5);  // MOVEQ.L	$F0,D5
  DEF_ROMLOC(6CBA) : draw_blocks_scroll_vert_full();  // BSR.W	$7028
  DEF_ROMLOC(6CBE) : bclr_tomem_8(0x1, A2);           // BCLR.B	#$01,(A2)
  DEF_ROMLOC(6CC2) : if (CCR_EQ) goto rom_6CD8;       // BEQ.B	$6CD8
  DEF_ROMLOC(6CC4) : move_toreg_16(0xE0, &D4);        // MOVE.W	#$00E0,D4
  DEF_ROMLOC(6CC8) : move_toreg_32(0xFFFFFFF0, &D5);  // MOVEQ.L	$F0,D5
  DEF_ROMLOC(6CCA) : calc_vram_pos_relative();        // BSR.W	$7174
  DEF_ROMLOC(6CCE) : move_toreg_16(0xE0, &D4);        // MOVE.W	#$00E0,D4
  DEF_ROMLOC(6CD2) : move_toreg_32(0xFFFFFFF0, &D5);  // MOVEQ.L	$F0,D5
  DEF_ROMLOC(6CD4) : draw_blocks_scroll_vert_full();  // BSR.W	$7028
  DEF_ROMLOC(6CD8) : bclr_tomem_8(0x2, A2);           // BCLR.B	#$02,(A2)
  DEF_ROMLOC(6CDC) : if (CCR_EQ) goto rom_6CEE;       // BEQ.B	$6CEE
  DEF_ROMLOC(6CDE) : move_toreg_32(0xFFFFFFF0, &D4);  // MOVEQ.L	$F0,D4
  DEF_ROMLOC(6CE0) : move_toreg_32(0xFFFFFFF0, &D5);  // MOVEQ.L	$F0,D5
  DEF_ROMLOC(6CE2) : calc_vram_pos_relative();        // BSR.W	$7174
  DEF_ROMLOC(6CE6) : move_toreg_32(0xFFFFFFF0, &D4);  // MOVEQ.L	$F0,D4
  DEF_ROMLOC(6CE8) : move_toreg_32(0xFFFFFFF0, &D5);  // MOVEQ.L	$F0,D5
  DEF_ROMLOC(6CEA) : draw_blocks_scroll_horiz_full(); // BSR.W	$707E
  DEF_ROMLOC(6CEE) : bclr_tomem_8(0x3, A2);           // BCLR.B	#$03,(A2)
  DEF_ROMLOC(6CF2) : if (CCR_EQ) goto rom_6D08;       // BEQ.B	$6D08
  DEF_ROMLOC(6CF4) : move_toreg_32(0xFFFFFFF0, &D4);  // MOVEQ.L	$F0,D4
  DEF_ROMLOC(6CF6) : move_toreg_16(GAME_WIDTH, &D5);       // MOVE.W	#$0140,D5
  DEF_ROMLOC(6CFA) : calc_vram_pos_relative();        // BSR.W	$7174
  DEF_ROMLOC(6CFE) : move_toreg_32(0xFFFFFFF0, &D4);  // MOVEQ.L	$F0,D4
  DEF_ROMLOC(6D00) : move_toreg_16(GAME_WIDTH, &D5);       // MOVE.W	#$0140,D5
  DEF_ROMLOC(6D04) : draw_blocks_scroll_horiz_full(); // BSR.W	$707E
  DEF_ROMLOC(6D08) : return;                          // RTS
}
void draw_bg_layer_1(void) {
  DEF_ROMLOC(6D0A) : tst_mem_8(A2);                   // TST.B	(A2)
  DEF_ROMLOC(6D0C) : if (CCR_EQ) goto rom_6DA4;       // BEQ.W	$6DA4
  DEF_ROMLOC(6D10) : bclr_tomem_8(0x0, A2);           // BCLR.B	#$00,(A2)
  DEF_ROMLOC(6D14) : if (CCR_EQ) goto rom_6D26;       // BEQ.B	$6D26
  DEF_ROMLOC(6D16) : move_toreg_32(0xFFFFFFF0, &D4);  // MOVEQ.L	$F0,D4
  DEF_ROMLOC(6D18) : move_toreg_32(0xFFFFFFF0, &D5);  // MOVEQ.L	$F0,D5
  DEF_ROMLOC(6D1A) : calc_vram_pos_relative();        // BSR.W	$7174
  DEF_ROMLOC(6D1E) : move_toreg_32(0xFFFFFFF0, &D4);  // MOVEQ.L	$F0,D4
  DEF_ROMLOC(6D20) : move_toreg_32(0xFFFFFFF0, &D5);  // MOVEQ.L	$F0,D5
  DEF_ROMLOC(6D22) : draw_blocks_scroll_vert_full();  // BSR.W	$7028
  DEF_ROMLOC(6D26) : bclr_tomem_8(0x1, A2);           // BCLR.B	#$01,(A2)
  DEF_ROMLOC(6D2A) : if (CCR_EQ) goto rom_6D40;       // BEQ.B	$6D40
  DEF_ROMLOC(6D2C) : move_toreg_16(0xE0, &D4);        // MOVE.W	#$00E0,D4
  DEF_ROMLOC(6D30) : move_toreg_32(0xFFFFFFF0, &D5);  // MOVEQ.L	$F0,D5
  DEF_ROMLOC(6D32) : calc_vram_pos_relative();        // BSR.W	$7174
  DEF_ROMLOC(6D36) : move_toreg_16(0xE0, &D4);        // MOVE.W	#$00E0,D4
  DEF_ROMLOC(6D3A) : move_toreg_32(0xFFFFFFF0, &D5);  // MOVEQ.L	$F0,D5
  DEF_ROMLOC(6D3C) : draw_blocks_scroll_vert_full();  // BSR.W	$7028
  DEF_ROMLOC(6D40) : bclr_tomem_8(0x2, A2);           // BCLR.B	#$02,(A2)
  DEF_ROMLOC(6D44) : if (CCR_EQ) goto rom_6D56;       // BEQ.B	$6D56
  DEF_ROMLOC(6D46) : move_toreg_32(0xFFFFFFF0, &D4);  // MOVEQ.L	$F0,D4
  DEF_ROMLOC(6D48) : move_toreg_32(0xFFFFFFF0, &D5);  // MOVEQ.L	$F0,D5
  DEF_ROMLOC(6D4A) : calc_vram_pos_relative();        // BSR.W	$7174
  DEF_ROMLOC(6D4E) : move_toreg_32(0xFFFFFFF0, &D4);  // MOVEQ.L	$F0,D4
  DEF_ROMLOC(6D50) : move_toreg_32(0xFFFFFFF0, &D5);  // MOVEQ.L	$F0,D5
  DEF_ROMLOC(6D52) : draw_blocks_scroll_horiz_full(); // BSR.W	$707E
  DEF_ROMLOC(6D56) : bclr_tomem_8(0x3, A2);           // BCLR.B	#$03,(A2)
  DEF_ROMLOC(6D5A) : if (CCR_EQ) goto rom_6D70;       // BEQ.B	$6D70
  DEF_ROMLOC(6D5C) : move_toreg_32(0xFFFFFFF0, &D4);  // MOVEQ.L	$F0,D4
  DEF_ROMLOC(6D5E) : move_toreg_16(GAME_WIDTH, &D5);       // MOVE.W	#$0140,D5
  DEF_ROMLOC(6D62) : calc_vram_pos_relative();        // BSR.W	$7174
  DEF_ROMLOC(6D66) : move_toreg_32(0xFFFFFFF0, &D4);  // MOVEQ.L	$F0,D4
  DEF_ROMLOC(6D68) : move_toreg_16(GAME_WIDTH, &D5);       // MOVE.W	#$0140,D5
  DEF_ROMLOC(6D6C) : draw_blocks_scroll_horiz_full(); // BSR.W	$707E
  DEF_ROMLOC(6D70) : bclr_tomem_8(0x4, A2);           // BCLR.B	#$04,(A2)
  DEF_ROMLOC(6D74) : if (CCR_EQ) goto rom_6D88;       // BEQ.B	$6D88
  DEF_ROMLOC(6D76) : move_toreg_32(0xFFFFFFF0, &D4);  // MOVEQ.L	$F0,D4
  DEF_ROMLOC(6D78) : move_toreg_32(0x0, &D5);         // MOVEQ.L	$00,D5
  DEF_ROMLOC(6D7A) : calc_vram_pos();                 // BSR.W	$7176
  DEF_ROMLOC(6D7E) : move_toreg_32(0xFFFFFFF0, &D4);  // MOVEQ.L	$F0,D4
  DEF_ROMLOC(6D80) : move_toreg_32(0x0, &D5);         // MOVEQ.L	$00,D5
  DEF_ROMLOC(6D82) : move_toreg_32(0x1F, &D6);        // MOVEQ.L	$1F,D6
  DEF_ROMLOC(6D84) : draw_blocks_scroll_vert_alt();   // BSR.W	$7054
  DEF_ROMLOC(6D88) : bclr_tomem_8(0x5, A2);           // BCLR.B	#$05,(A2)
  DEF_ROMLOC(6D8C) : if (CCR_EQ) goto rom_6DA4;       // BEQ.B	$6DA4
  DEF_ROMLOC(6D8E) : move_toreg_16(0xE0, &D4);        // MOVE.W	#$00E0,D4
  DEF_ROMLOC(6D92) : move_toreg_32(0x0, &D5);         // MOVEQ.L	$00,D5
  DEF_ROMLOC(6D94) : calc_vram_pos();                 // BSR.W	$7176
  DEF_ROMLOC(6D98) : move_toreg_16(0xE0, &D4);        // MOVE.W	#$00E0,D4
  DEF_ROMLOC(6D9C) : move_toreg_32(0x0, &D5);         // MOVEQ.L	$00,D5
  DEF_ROMLOC(6D9E) : move_toreg_32(0x1F, &D6);        // MOVEQ.L	$1F,D6
  DEF_ROMLOC(6DA0) : draw_blocks_scroll_vert_alt();   // BSR.W	$7054
  DEF_ROMLOC(6DA4) : return;                          // RTS
}
void draw_bg_layer_2(void) {
  DEF_ROMLOC(6DA6) : tst_mem_8(A2);                 // TST.B	(A2)
  DEF_ROMLOC(6DA8) : if (CCR_EQ) goto rom_6DF2;     // BEQ.W	$6DF2
  DEF_ROMLOC(6DAC) : cmp_tomem_8(ZONE_SBZ, v_zone); // CMPI.B	#$05,$FE10
  DEF_ROMLOC(6DB2) : if (CCR_EQ) {
    rom_6E16();
    return;
  } // BEQ.W	$6E16
  DEF_ROMLOC(6DB6) : bclr_tomem_8(0x0, A2);          // BCLR.B	#$00,(A2)
  DEF_ROMLOC(6DBA) : if (CCR_EQ) goto rom_6DD2;      // BEQ.B	$6DD2
  DEF_ROMLOC(6DBC) : move_toreg_16(0x70, &D4);       // MOVE.W	#$0070,D4
  DEF_ROMLOC(6DC0) : move_toreg_32(0xFFFFFFF0, &D5); // MOVEQ.L	$F0,D5
  DEF_ROMLOC(6DC2) : calc_vram_pos_relative();       // BSR.W	$7174
  DEF_ROMLOC(6DC6) : move_toreg_16(0x70, &D4);       // MOVE.W	#$0070,D4
  DEF_ROMLOC(6DCA) : move_toreg_32(0xFFFFFFF0, &D5); // MOVEQ.L	$F0,D5
  DEF_ROMLOC(6DCC) : move_toreg_32(0x2, &D6);        // MOVEQ.L	$02,D6
  DEF_ROMLOC(6DCE) : draw_blocks_scroll_horiz();     // BSR.W	$7080
  DEF_ROMLOC(6DD2) : bclr_tomem_8(0x1, A2);          // BCLR.B	#$01,(A2)
  DEF_ROMLOC(6DD6) : if (CCR_EQ) goto rom_6DF2;      // BEQ.B	$6DF2
  DEF_ROMLOC(6DD8) : move_toreg_16(0x70, &D4);       // MOVE.W	#$0070,D4
  DEF_ROMLOC(6DDC) : move_toreg_16(GAME_WIDTH, &D5);      // MOVE.W	#$0140,D5
  DEF_ROMLOC(6DE0) : calc_vram_pos_relative();       // BSR.W	$7174
  DEF_ROMLOC(6DE4) : move_toreg_16(0x70, &D4);       // MOVE.W	#$0070,D4
  DEF_ROMLOC(6DE8) : move_toreg_16(GAME_WIDTH, &D5);      // MOVE.W	#$0140,D5
  DEF_ROMLOC(6DEC) : move_toreg_32(0x2, &D6);        // MOVEQ.L	$02,D6
  DEF_ROMLOC(6DEE) : draw_blocks_scroll_horiz();     // BSR.W	$7080
  DEF_ROMLOC(6DF2) : return;                         // RTS
}
void draw_bg_layer_3(void) {
  u32 d4backup = 0;
  u32 d5backup = 0;
  DEF_ROMLOC(6EA4) : tst_mem_8(A2);                  // TST.B	(A2)
  DEF_ROMLOC(6EA6) : if (CCR_EQ) goto rom_6EF0;      // BEQ.W	$6EF0
  DEF_ROMLOC(6EAA) : cmp_tomem_8(ZONE_MZ, v_zone);   // CMPI.B	#$02,$FE10
  DEF_ROMLOC(6EB0) : if (CCR_EQ) goto rom_6F54;      // BEQ.W	$6F54
  DEF_ROMLOC(6EB4) : bclr_tomem_8(0x0, A2);          // BCLR.B	#$00,(A2)
  DEF_ROMLOC(6EB8) : if (CCR_EQ) goto rom_6ED0;      // BEQ.B	$6ED0
  DEF_ROMLOC(6EBA) : move_toreg_16(0x40, &D4);       // MOVE.W	#$0040,D4
  DEF_ROMLOC(6EBE) : move_toreg_32(0xFFFFFFF0, &D5); // MOVEQ.L	$F0,D5
  DEF_ROMLOC(6EC0) : calc_vram_pos_relative();       // BSR.W	$7174
  DEF_ROMLOC(6EC4) : move_toreg_16(0x40, &D4);       // MOVE.W	#$0040,D4
  DEF_ROMLOC(6EC8) : move_toreg_32(0xFFFFFFF0, &D5); // MOVEQ.L	$F0,D5
  DEF_ROMLOC(6ECA) : move_toreg_32(0x2, &D6);        // MOVEQ.L	$02,D6
  DEF_ROMLOC(6ECC) : draw_blocks_scroll_horiz();     // BSR.W	$7080
  DEF_ROMLOC(6ED0) : bclr_tomem_8(0x1, A2);          // BCLR.B	#$01,(A2)
  DEF_ROMLOC(6ED4) : if (CCR_EQ) goto rom_6EF0;      // BEQ.B	$6EF0
  DEF_ROMLOC(6ED6) : move_toreg_16(0x40, &D4);       // MOVE.W	#$0040,D4
  DEF_ROMLOC(6EDA) : move_toreg_16(GAME_WIDTH, &D5);      // MOVE.W	#$0140,D5
  DEF_ROMLOC(6EDE) : calc_vram_pos_relative();       // BSR.W	$7174
  DEF_ROMLOC(6EE2) : move_toreg_16(0x40, &D4);       // MOVE.W	#$0040,D4
  DEF_ROMLOC(6EE6) : move_toreg_16(GAME_WIDTH, &D5);      // MOVE.W	#$0140,D5
  DEF_ROMLOC(6EEA) : move_toreg_32(0x2, &D6);        // MOVEQ.L	$02,D6
  DEF_ROMLOC(6EEC) : draw_blocks_scroll_horiz();     // BSR.W	$7080
  DEF_ROMLOC(6EF0) : return;                         // RTS
  DEF_ROMLOC(6F54) : move_toreg_32(0xFFFFFFF0, &D4); // MOVEQ.L	$F0,D4
  DEF_ROMLOC(6F56) : bclr_tomem_8(0x0, A2);          // BCLR.B	#$00,(A2)
  DEF_ROMLOC(6F5A) : if (!CCR_EQ) goto rom_6F66;     // BNE.B	$6F66
  DEF_ROMLOC(6F5C) : bclr_tomem_8(0x1, A2);          // BCLR.B	#$01,(A2)
  DEF_ROMLOC(6F60) : if (CCR_EQ) goto rom_6FAE;      // BEQ.B	$6FAE
  DEF_ROMLOC(6F62) : move_toreg_16(0xE0, &D4);       // MOVE.W	#$00E0,D4
  DEF_ROMLOC(6F66) : move_toreg_32(0x6EF3, &A0);     // LEA.L	$00006EF3,A0
  DEF_ROMLOC(6F6C)
      : move_toreg_16(read_16(0xFFFFF70C), &D0); // MOVE.W	$F70C,D0
  DEF_ROMLOC(6F70) : sub_toreg_16(0x200, &D0);   // SUBI.W	#$0200,D0
  DEF_ROMLOC(6F74) : add_toreg_16(D4, &D0);      // ADD.W	D4,D0
  DEF_ROMLOC(6F76) : and_toreg_16(0x7F0, &D0);   // ANDI.W	#$07F0,D0
  DEF_ROMLOC(6F7A) : lsr_toreg_16(0x4, &D0);     // LSR.W	#$04,D0
  DEF_ROMLOC(6F7C)
      : move_toreg_8(read_8((s32)A0 + (s8)0x0 + (s16)D0),
                     &D0); // MOVE.B	0(A0,D0),D0
  DEF_ROMLOC(6F80)
      : move_toreg_16(read_16(0x6FE4 + (s16)(D0 & 0xffff)),
                      &A3);                          // MOVEA.W	98(PC,D0),A3
  DEF_ROMLOC(6F84) : if (CCR_EQ) goto rom_6F9A;      // BEQ.B	$6F9A
  DEF_ROMLOC(6F86) : move_toreg_32(0xFFFFFFF0, &D5); // MOVEQ.L	$F0,D5
  DEF_ROMLOC(6F88) : d4backup = D4;
  d5backup = D5;                               // TODO; // MOVEM.L	D4-D5,-(A7)
  DEF_ROMLOC(6F8C) : calc_vram_pos_relative(); // BSR.W	$7174
  DEF_ROMLOC(6F90) : D4 = d4backup;
  D5 = d5backup; // TODO; // MOVEM.L	(A7)+,D4-D5
  DEF_ROMLOC(6F94) : draw_blocks_scroll_vert_full(); // BSR.W	$7028
  goto rom_6FAE;                                     // BRA.B	$6FAE
  DEF_ROMLOC(6F9A) : move_toreg_32(0x0, &D5);        // MOVEQ.L	$00,D5
  DEF_ROMLOC(6F9C) : d4backup = D4;
  d5backup = D5;                      // TODO; // MOVEM.L	D4-D5,-(A7)
  DEF_ROMLOC(6FA0) : calc_vram_pos(); // BSR.W	$7176
  DEF_ROMLOC(6FA4) : D4 = d4backup;
  D5 = d5backup;                               // TODO; // MOVEM.L	(A7)+,D4-D5
  DEF_ROMLOC(6FA8) : move_toreg_32(0x1F, &D6); // MOVEQ.L	$1F,D6
  DEF_ROMLOC(6FAA) : draw_blocks_scroll_vert_alt();  // BSR.W	$7054
  DEF_ROMLOC(6FAE) : tst_mem_8(A2);                  // TST.B	(A2)
  DEF_ROMLOC(6FB0) : if (!CCR_EQ) goto rom_6FB4;     // BNE.B	$6FB4
  DEF_ROMLOC(6FB2) : return;                         // RTS
  DEF_ROMLOC(6FB4) : move_toreg_32(0xFFFFFFF0, &D4); // MOVEQ.L	$F0,D4
  DEF_ROMLOC(6FB6) : move_toreg_32(0xFFFFFFF0, &D5); // MOVEQ.L	$F0,D5
  DEF_ROMLOC(6FB8) : move_toreg_8(read_8(A2), &D0);  // MOVE.B	(A2),D0
  DEF_ROMLOC(6FBA) : and_toreg_8(0xFFFFFFA8, &D0);   // ANDI.B	#$A8,D0
  DEF_ROMLOC(6FBE) : if (CCR_EQ) goto rom_6FC8;      // BEQ.B	$6FC8
  DEF_ROMLOC(6FC0) : lsr_toreg_8(0x1, &D0);          // LSR.B	#$01,D0
  DEF_ROMLOC(6FC2) : move_tomem_8(D0, A2);           // MOVE.B	D0,(A2)
  DEF_ROMLOC(6FC4) : move_toreg_16(GAME_WIDTH, &D5);      // MOVE.W	#$0140,D5
  DEF_ROMLOC(6FC8) : move_toreg_32(0x6EF2, &A0);     // LEA.L	$00006EF2,A0
  DEF_ROMLOC(6FCE)
      : move_toreg_16(read_16(0xFFFFF70C), &D0); // MOVE.W	$F70C,D0
  DEF_ROMLOC(6FD2) : sub_toreg_16(0x200, &D0);   // SUBI.W	#$0200,D0
  DEF_ROMLOC(6FD6) : and_toreg_16(0x7F0, &D0);   // ANDI.W	#$07F0,D0
  DEF_ROMLOC(6FDA) : lsr_toreg_16(0x4, &D0);     // LSR.W	#$04,D0
  DEF_ROMLOC(6FDC)
      : move_toreg_32((s32)A0 + (s8)0x0 + (s16)D0,
                      &A0); // LEA.L	0(A0,D0),A0
  draw_bg_layer_3_alt();
}
void draw_bg_layer_3_alt(void) {
  DEF_ROMLOC(6FEC) : move_toreg_32(0xF, &D6);      // MOVEQ.L	$0F,D6
  DEF_ROMLOC(6FEE) : move_toreg_32(0x800000, &D7); // MOVE.L	#$00800000,D7
  u32 d4backupouter = 0;
  u32 d5backupouter = 0;
  u32 a0backupouter = 0;
  u32 d4backupinner = 0;
  u32 d5backupinner = 0;
  DEF_ROMLOC(6FF4) : move_toreg_32(0x0, &D0);         // MOVEQ.L	$00,D0
  DEF_ROMLOC(6FF6) : move_toreg_8(read_8(A0++), &D0); // MOVE.B	(A0)+,D0
  DEF_ROMLOC(6FF8) : btst_tomem_8(D0, A2);            // BTST.B	D0,(A2)
  DEF_ROMLOC(6FFA) : if (CCR_EQ) goto rom_701C;       // BEQ.B	$701C
  DEF_ROMLOC(6FFC)
      : move_toreg_16(read_16(0x6FE4 + (s16)(D0 & 0xffff)),
                      &A3); // MOVEA.W	-26(PC,D0),A3
  DEF_ROMLOC(7000) : d4backupouter = D4;
  d5backupouter = D5;
  a0backupouter = A0; // TODO; // MOVEM.L	D4-D5/A0,-(A7)
  DEF_ROMLOC(7004) : d4backupinner = D4;
  d5backupinner = D5;                           // TODO; // MOVEM.L	D4-D5,-(A7)
  DEF_ROMLOC(7008) : get_block_data_relative(); // BSR.W	$712A
  DEF_ROMLOC(700C) : D4 = d4backupinner;
  D5 = d5backupinner;                          // TODO; // MOVEM.L	(A7)+,D4-D5
  DEF_ROMLOC(7010) : calc_vram_pos_relative(); // BSR.W	$7174
  DEF_ROMLOC(7014) : draw_block(A0, A1, D0, D2, D7);             // BSR.W	$70AC
  DEF_ROMLOC(7018) : D4 = d4backupouter;
  D5 = d5backupouter;
  A0 = a0backupouter;                         // TODO; // MOVEM.L	(A7)+,D4-D5/A0
  DEF_ROMLOC(701C) : add_toreg_16(0x10, &D4); // ADDI.W	#$0010,D4
  DEF_ROMLOC(7020) : dec_reg_16(&D6);
  if ((D6 & 0xffff) != 0xffff)
    goto rom_6FF4;                  // DBF.W	D6,$6FF4
  DEF_ROMLOC(7024) : clr_mem_8(A2); // CLR.B	(A2)
  DEF_ROMLOC(7026) : return;        // RTS
}
void draw_blocks_scroll_vert_full(void) {
  DEF_ROMLOC(7028) : move_toreg_32(((16 + GAME_WIDTH + 16) / 16) - 1, &D6); // MOVEQ.L	$15,D6
  draw_blocks_scroll_vert(); // Detected flow into next function
}
void draw_blocks_scroll_vert(void) {
  u32 d4backup = 0;
  u32 d5backup = 0;
  DEF_ROMLOC(702A) : move_toreg_32(0x800000, &D7); // MOVE.L	#$00800000,D7
  DEF_ROMLOC(7030) : move_toreg_32(D0, &D1);       // MOVE.L	D0,D1
  DEF_ROMLOC(7032) : d4backup = D4;
  d5backup = D5;                                // TODO; // MOVEM.L	D4-D5,-(A7)
  DEF_ROMLOC(7036) : get_block_data_relative(); // BSR.W	$712A
  DEF_ROMLOC(703A) : move_toreg_32(D1, &D0);    // MOVE.L	D1,D0
  DEF_ROMLOC(703C) : draw_block(A0, A1, D0, D2, D7);              // BSR.W	$70AC
  DEF_ROMLOC(7040) : add_toreg_8(0x4, &D1);     // ADDQ.B	#$04,D1
  DEF_ROMLOC(7042) : and_toreg_8(0x7F, &D1);    // ANDI.B	#$7F,D1
  DEF_ROMLOC(7046) : D4 = d4backup;
  D5 = d5backup;                              // TODO; // MOVEM.L	(A7)+,D4-D5
  DEF_ROMLOC(704A) : add_toreg_16(0x10, &D5); // ADDI.W	#$0010,D5
  DEF_ROMLOC(704E) : dec_reg_16(&D6);
  if ((D6 & 0xffff) != 0xffff)
    goto rom_7032;           // DBF.W	D6,$7032
  DEF_ROMLOC(7052) : return; // RTS
}
void draw_blocks_scroll_vert_alt(void) {
  u32 d4backup = 0;
  u32 d5backup = 0;
  DEF_ROMLOC(7054) : move_toreg_32(0x800000, &D7); // MOVE.L	#$00800000,D7
  DEF_ROMLOC(705A) : move_toreg_32(D0, &D1);       // MOVE.L	D0,D1
  DEF_ROMLOC(705C) : d4backup = D4;
  d5backup = D5;                             // TODO; // MOVEM.L	D4-D5,-(A7)
  DEF_ROMLOC(7060) : get_block_data();       // BSR.W	$712C
  DEF_ROMLOC(7064) : move_toreg_32(D1, &D0); // MOVE.L	D1,D0
  DEF_ROMLOC(7066) : draw_block(A0, A1, D0, D2, D7);           // BSR.W	$70AC
  DEF_ROMLOC(706A) : add_toreg_8(0x4, &D1);  // ADDQ.B	#$04,D1
  DEF_ROMLOC(706C) : and_toreg_8(0x7F, &D1); // ANDI.B	#$7F,D1
  DEF_ROMLOC(7070) : D4 = d4backup;
  D5 = d5backup;                              // TODO; // MOVEM.L	(A7)+,D4-D5
  DEF_ROMLOC(7074) : add_toreg_16(0x10, &D5); // ADDI.W	#$0010,D5
  DEF_ROMLOC(7078) : dec_reg_16(&D6);
  if ((D6 & 0xffff) != 0xffff)
    goto rom_705C;           // DBF.W	D6,$705C
  DEF_ROMLOC(707C) : return; // RTS
}
void draw_blocks_scroll_horiz_full(void) {
  DEF_ROMLOC(707E) : move_toreg_32(0xF, &D6); // MOVEQ.L	$0F,D6
  draw_blocks_scroll_horiz(); // Detected flow into next function
}
void draw_blocks_scroll_horiz(void) {
  u32 d4backup = 0;
  u32 d5backup = 0;
  DEF_ROMLOC(7080) : move_toreg_32(0x800000, &D7); // MOVE.L	#$00800000,D7
  DEF_ROMLOC(7086) : move_toreg_32(D0, &D1);       // MOVE.L	D0,D1
  DEF_ROMLOC(7088) : d4backup = D4;
  d5backup = D5;                                // TODO; // MOVEM.L	D4-D5,-(A7)
  DEF_ROMLOC(708C) : get_block_data_relative(); // BSR.W	$712A
  DEF_ROMLOC(7090) : move_toreg_32(D1, &D0);    // MOVE.L	D1,D0
  DEF_ROMLOC(7092) : draw_block(A0, A1, D0, D2, D7);              // BSR.W	$70AC
  DEF_ROMLOC(7096) : add_toreg_16(0x100, &D1);  // ADDI.W	#$0100,D1
  DEF_ROMLOC(709A) : and_toreg_16(0xFFF, &D1);  // ANDI.W	#$0FFF,D1
  DEF_ROMLOC(709E) : D4 = d4backup;
  D5 = d5backup;                              // TODO; // MOVEM.L	(A7)+,D4-D5
  DEF_ROMLOC(70A2) : add_toreg_16(0x10, &D4); // ADDI.W	#$0010,D4
  DEF_ROMLOC(70A6) : dec_reg_16(&D6);
  if ((D6 & 0xffff) != 0xffff)
    goto rom_7088;           // DBF.W	D6,$7088
  DEF_ROMLOC(70AA) : return; // RTS
}
void draw_block(u32 block_metadata_ptr, u32 block_ptr, u32 vram_command, u32 vram_plane, u32 plane_stride) {
  DEF_ROMLOC(70AC) : or_toreg_16(D2, &D0);       // OR.W	D2,D0
  DEF_ROMLOC(70AE) : SWAPWORDS(D0);              // SWAP.W	D0
  DEF_ROMLOC(70B0) : btst_tomem_8(0x4, A0);      // BTST.B	#$04,(A0)
  DEF_ROMLOC(70B4) : if (CCR_EQ) {
  	DEF_ROMLOC(70B6) : btst_tomem_8(0x3, A0);      // BTST.B	#$03,(A0)
  	DEF_ROMLOC(70BA) : if (CCR_EQ) {
  		DEF_ROMLOC(70BC) : write_vdp_control_32(D0);
  		DEF_ROMLOC(70BE) : write_vdp_data_32(read_32((A1 += 4, A1 - 4)));
  		DEF_ROMLOC(70C0) : add_toreg_32(D7, &D0); // ADD.L	D7,D0
  		DEF_ROMLOC(70C2) : write_vdp_control_32(D0);
  		DEF_ROMLOC(70C4) : write_vdp_data_32(read_32((A1 += 4, A1 - 4)));
  		DEF_ROMLOC(70C6) : return;                // RTS
  	}
  	DEF_ROMLOC(70C8) : write_vdp_control_32(D0);
  	DEF_ROMLOC(70CA) : move_toreg_32(read_32((A1 += 4, A1 - 4)), &D4); // MOVE.L	(A1)+,D4
  	DEF_ROMLOC(70CC) : eor_toreg_32(0x8000800, &D4);      // EORI.L	#$08000800,D4
  	DEF_ROMLOC(70D2) : SWAPWORDS(D4);                     // SWAP.W	D4
  	DEF_ROMLOC(70D4) : write_vdp_data_32(D4);
  	DEF_ROMLOC(70D6) : add_toreg_32(D7, &D0);             // ADD.L	D7,D0
  	DEF_ROMLOC(70D8) : write_vdp_control_32(D0);
  	DEF_ROMLOC(70DA) : move_toreg_32(read_32((A1 += 4, A1 - 4)), &D4); // MOVE.L	(A1)+,D4
  	DEF_ROMLOC(70DC) : eor_toreg_32(0x8000800, &D4);      // EORI.L	#$08000800,D4
  	DEF_ROMLOC(70E2) : SWAPWORDS(D4);                     // SWAP.W	D4
  	DEF_ROMLOC(70E4) : write_vdp_data_32(D4);
  	DEF_ROMLOC(70E6) : return;                            // RTS
  }
  DEF_ROMLOC(70E8) : btst_tomem_8(0x3, A0);             // BTST.B	#$03,(A0)
  DEF_ROMLOC(70EC) : if (CCR_EQ) {
  	DEF_ROMLOC(70EE) : write_vdp_control_32(D0);
  	DEF_ROMLOC(70F0) : move_toreg_32(read_32((A1 += 4, A1 - 4)), &D5); // MOVE.L	(A1)+,D5
  	DEF_ROMLOC(70F2) : move_toreg_32(read_32((A1 += 4, A1 - 4)), &D4); // MOVE.L	(A1)+,D4
  	DEF_ROMLOC(70F4) : eor_toreg_32(0x10001000, &D4);      // EORI.L	#$10001000,D4
  	DEF_ROMLOC(70FA) : write_vdp_data_32(D4);
  	DEF_ROMLOC(70FC) : add_toreg_32(D7, &D0); // ADD.L	D7,D0
  	DEF_ROMLOC(70FE) : write_vdp_control_32(D0);
  	DEF_ROMLOC(7100) : eor_toreg_32(0x10001000, &D5);      // EORI.L	#$10001000,D5
  	DEF_ROMLOC(7106) : write_vdp_data_32(D5);
  	DEF_ROMLOC(7108) : return;                // RTS
  }
  DEF_ROMLOC(710A) : write_vdp_control_32(D0);
  DEF_ROMLOC(710C) : move_toreg_32(read_32((A1 += 4, A1 - 4)), &D5); // MOVE.L	(A1)+,D5
  DEF_ROMLOC(710E) : move_toreg_32(read_32((A1 += 4, A1 - 4)), &D4); // MOVE.L	(A1)+,D4
  DEF_ROMLOC(7110) : eor_toreg_32(0x18001800, &D4);      // EORI.L	#$18001800,D4
  DEF_ROMLOC(7116) : SWAPWORDS(D4);         // SWAP.W	D4
  DEF_ROMLOC(7118) : write_vdp_data_32(D4);
  DEF_ROMLOC(711A) : add_toreg_32(D7, &D0); // ADD.L	D7,D0
  DEF_ROMLOC(711C) : write_vdp_control_32(D0);
  DEF_ROMLOC(711E) : eor_toreg_32(0x18001800, &D5);      // EORI.L	#$18001800,D5
  DEF_ROMLOC(7124) : SWAPWORDS(D5);         // SWAP.W	D5
  DEF_ROMLOC(7126) : write_vdp_data_32(D5);
}
void get_block_data_relative(void) {
  DEF_ROMLOC(712A) : add_toreg_16(read_16(A3), &D5); // ADD.W	(A3),D5
  get_block_data();
}
void get_block_data(void) {
  DEF_ROMLOC(712C) : add_toreg_16(read_16(A3 + 0x4), &D4); // ADD.W	4(A3),D4
  DEF_ROMLOC(7130) : move_toreg_32(v_16x16, &A1);          // LEA.L	$B000,A1
  DEF_ROMLOC(7134) : move_toreg_16(D4, &D3);               // MOVE.W	D4,D3
  DEF_ROMLOC(7136) : lsr_toreg_16(0x1, &D3);               // LSR.W	#$01,D3
  DEF_ROMLOC(7138) : and_toreg_16(0x380, &D3);             // ANDI.W	#$0380,D3
  DEF_ROMLOC(713C) : lsr_toreg_16(0x3, &D5);               // LSR.W	#$03,D5
  DEF_ROMLOC(713E) : move_toreg_16(D5, &D0);               // MOVE.W	D5,D0
  DEF_ROMLOC(7140) : lsr_toreg_16(0x5, &D0);               // LSR.W	#$05,D0
  DEF_ROMLOC(7142) : and_toreg_16(0x7F, &D0);              // ANDI.W	#$007F,D0
  DEF_ROMLOC(7146) : add_toreg_16(D3, &D0);                // ADD.W	D3,D0
  DEF_ROMLOC(7148) : move_toreg_32(0xFFFFFFFF, &D3);       // MOVEQ.L	$FF,D3
  DEF_ROMLOC(714A)
      : move_toreg_8(read_8((s32)A4 + (s8)0x0 + (s16)D0),
                     &D3);                            // MOVE.B	0(A4,D0),D3
  DEF_ROMLOC(714E) : if (CCR_EQ) goto rom_7172;       // BEQ.B	$7172
  DEF_ROMLOC(7150) : sub_toreg_8(0x1, &D3);           // SUBQ.B	#$01,D3
  DEF_ROMLOC(7152) : and_toreg_16(0x7F, &D3);         // ANDI.W	#$007F,D3
  DEF_ROMLOC(7156) : ror_toreg_16(0x7, &D3);          // ROR.W	#$07,D3
  DEF_ROMLOC(7158) : add_toreg_16(D4, &D4);           // ADD.W	D4,D4
  DEF_ROMLOC(715A) : and_toreg_16(0x1E0, &D4);        // ANDI.W	#$01E0,D4
  DEF_ROMLOC(715E) : and_toreg_16(0x1E, &D5);         // ANDI.W	#$001E,D5
  DEF_ROMLOC(7162) : add_toreg_16(D4, &D3);           // ADD.W	D4,D3
  DEF_ROMLOC(7164) : add_toreg_16(D5, &D3);           // ADD.W	D5,D3
  DEF_ROMLOC(7166) : move_toreg_32(D3, &A0);          // MOVEA.L	D3,A0
  DEF_ROMLOC(7168) : move_toreg_16(read_16(A0), &D3); // MOVE.W	(A0),D3
  DEF_ROMLOC(716A) : and_toreg_16(0x3FF, &D3);        // ANDI.W	#$03FF,D3
  DEF_ROMLOC(716E) : lsl_toreg_16(0x3, &D3);          // LSL.W	#$03,D3
  DEF_ROMLOC(7170) : add_toreg_16(D3, &A1);           // ADDA.W	D3,A1
  DEF_ROMLOC(7172) : return;                          // RTS
}
void calc_vram_pos_relative(void) {
  DEF_ROMLOC(7174) : add_toreg_16(read_16(A3), &D5); // ADD.W	(A3),D5
  calc_vram_pos();
}
void calc_vram_pos(void) {
  DEF_ROMLOC(7176) : add_toreg_16(read_16(A3 + 0x4), &D4); // ADD.W	4(A3),D4
  DEF_ROMLOC(717A) : and_toreg_16(0xF0, &D4);              // ANDI.W	#$00F0,D4
  DEF_ROMLOC(717E) : and_toreg_16(0x1F0, &D5);             // ANDI.W	#$01F0,D5
  DEF_ROMLOC(7182) : lsl_toreg_16(0x4, &D4);               // LSL.W	#$04,D4
  DEF_ROMLOC(7184) : lsr_toreg_16(0x2, &D5);               // LSR.W	#$02,D5
  DEF_ROMLOC(7186) : add_toreg_16(D5, &D4);                // ADD.W	D5,D4
  DEF_ROMLOC(7188) : move_toreg_32(0x3, &D0);              // MOVEQ.L	$03,D0
  DEF_ROMLOC(718A) : SWAPWORDS(D0);                        // SWAP.W	D0
  DEF_ROMLOC(718C) : move_toreg_16(D4, &D0);               // MOVE.W	D4,D0
  DEF_ROMLOC(718E) : return;                               // RTS
}
void update_tiles_on_start(void) {
  DEF_ROMLOC(71AC)
      : move_toreg_32(VDP_CONTROL_PORT, &A5); // LEA.L
                                              // $00C00004,A5
  DEF_ROMLOC(71B2)
      : move_toreg_32(VDP_DATA_PORT, &A6);             // LEA.L
                                                       // $00C00000,A6
  DEF_ROMLOC(71B8) : move_toreg_32(v_screenposx, &A3); // LEA.L	$F700,A3
  DEF_ROMLOC(71BC) : move_toreg_32(0xFFFFA400, &A4);   // LEA.L	$A400,A4
  DEF_ROMLOC(71C0) : move_toreg_16(0x4000, &D2);       // MOVE.W	#$4000,D2
  DEF_ROMLOC(71C4) : draw_chunks();                    // BSR.B	$71F8
  DEF_ROMLOC(71C6) : move_toreg_32(0xFFFFF708, &A3);   // LEA.L	$F708,A3
  DEF_ROMLOC(71CA) : move_toreg_32(0xFFFFA440, &A4);   // LEA.L	$A440,A4
  DEF_ROMLOC(71CE) : move_toreg_16(0x6000, &D2);       // MOVE.W	#$6000,D2
  DEF_ROMLOC(71D2) : tst_mem_8(v_zone);                // TST.B	$FE10
  DEF_ROMLOC(71D6) : if (CCR_EQ) {
    draw_bg_ghz();
    return;
  } // BEQ.W	$7220
  DEF_ROMLOC(71DA) : cmp_tomem_8(ZONE_MZ, v_zone); // CMPI.B	#$02,$FE10
  DEF_ROMLOC(71E0) : if (CCR_EQ) {
    draw_bg_mz();
    return;
  } // BEQ.W	$725A
  DEF_ROMLOC(71E4)
      : cmp_tomem_16(ZONE16_SBZ, v_zone); // CMPI.W	#$0500,$FE10
  DEF_ROMLOC(71EA) : if (CCR_EQ) {
    draw_bg_sbz();
    return;
  } // BEQ.W	$7288
  DEF_ROMLOC(71EE) : cmp_tomem_8(ZONE_END, v_zone); // CMPI.B	#$06,$FE10
  DEF_ROMLOC(71F4) : if (CCR_EQ) {
    draw_bg_ghz();
    return;
  } // BEQ.W	$7220
  draw_chunks(); // Detected flow into next function
}
void draw_chunks(void) {
  u32 d4backup = D4;
  u32 d5backup = D5;
  u32 d6backup = D6;
  DEF_ROMLOC(71F8) : move_toreg_32(0xFFFFFFF0, &D4); // MOVEQ.L	$F0,D4
  DEF_ROMLOC(71FA) : move_toreg_32(0xF, &D6);        // MOVEQ.L	$0F,D6
  DEF_ROMLOC(71FC) : d4backup = D4;
  d5backup = D5;
  d6backup = D6;                                // TODO; // MOVEM.L	D4-D6,-(A7)
  DEF_ROMLOC(7200) : move_toreg_32(0x0, &D5);   // MOVEQ.L	$00,D5
  DEF_ROMLOC(7202) : move_toreg_16(D4, &D1);    // MOVE.W	D4,D1
  DEF_ROMLOC(7204) : calc_vram_pos_relative();  // BSR.W	$7174
  DEF_ROMLOC(7208) : move_toreg_16(D1, &D4);    // MOVE.W	D1,D4
  DEF_ROMLOC(720A) : move_toreg_32(0x0, &D5);   // MOVEQ.L	$00,D5
  DEF_ROMLOC(720C) : move_toreg_32(0x1F, &D6);  // MOVEQ.L	$1F,D6
  DEF_ROMLOC(720E) : draw_blocks_scroll_vert(); // BSR.W	$702A
  DEF_ROMLOC(7212) : D4 = d4backup;
  D5 = d5backup;
  D6 = d6backup;                              // TODO; // MOVEM.L	(A7)+,D4-D6
  DEF_ROMLOC(7216) : add_toreg_16(0x10, &D4); // ADDI.W	#$0010,D4
  DEF_ROMLOC(721A) : dec_reg_16(&D6);
  if ((D6 & 0xffff) != 0xffff)
    goto rom_71FC;           // DBF.W	D6,$71FC
  DEF_ROMLOC(721E) : return; // RTS
}
void draw_bg_ghz(void) {
  DEF_ROMLOC(7220) : move_toreg_32(0x0, &D4); // MOVEQ.L	$00,D4
  DEF_ROMLOC(7222) : move_toreg_32(0xF, &D6); // MOVEQ.L	$0F,D6
  u32 d4backup = 0;
  u32 d5backup = 0;
  u32 d6backup = 0;
  DEF_ROMLOC(7224) : d4backup = D4;
  d5backup = D5;
  d6backup = D6;                                 // TODO; // MOVEM.L	D4-D6,-(A7)
  DEF_ROMLOC(7228) : move_toreg_32(0x724A, &A0); // LEA.L	$0000724A,A0
  DEF_ROMLOC(722E)
      : move_toreg_16(read_16(0xFFFFF70C), &D0); // MOVE.W	$F70C,D0
  DEF_ROMLOC(7232) : add_toreg_16(D4, &D0);      // ADD.W	D4,D0
  DEF_ROMLOC(7234) : and_toreg_16(0xF0, &D0);    // ANDI.W	#$00F0,D0
  DEF_ROMLOC(7238) : draw_bg_end();              // BSR.W	$72BA
  DEF_ROMLOC(723C) : D4 = d4backup;
  D5 = d5backup;
  D6 = d6backup;                              // TODO; // MOVEM.L	(A7)+,D4-D6
  DEF_ROMLOC(7240) : add_toreg_16(0x10, &D4); // ADDI.W	#$0010,D4
  DEF_ROMLOC(7244) : dec_reg_16(&D6);
  if ((D6 & 0xffff) != 0xffff)
    goto rom_7224;           // DBF.W	D6,$7224
  DEF_ROMLOC(7248) : return; // RTS
}
void draw_bg_mz(void) {
  DEF_ROMLOC(725A) : move_toreg_32(0xFFFFFFF0, &D4); // MOVEQ.L	$F0,D4
  DEF_ROMLOC(725C) : move_toreg_32(0xF, &D6);        // MOVEQ.L	$0F,D6
  u32 d4backup = 0;
  u32 d5backup = 0;
  u32 d6backup = 0;
  DEF_ROMLOC(725E) : d4backup = D4;
  d5backup = D5;
  d6backup = D6;
  // TODO; // MOVEM.L	D4-D6,-(A7)
  DEF_ROMLOC(7262) : move_toreg_32(0x6EF3, &A0); // LEA.L	$00006EF3,A0
  DEF_ROMLOC(7268)
      : move_toreg_16(read_16(0xFFFFF70C), &D0); // MOVE.W	$F70C,D0
  DEF_ROMLOC(726C) : sub_toreg_16(0x200, &D0);   // SUBI.W	#$0200,D0
  DEF_ROMLOC(7270) : add_toreg_16(D4, &D0);      // ADD.W	D4,D0
  DEF_ROMLOC(7272) : and_toreg_16(0x7F0, &D0);   // ANDI.W	#$07F0,D0
  DEF_ROMLOC(7276) : draw_bg_end();              // BSR.W	$72BA
  DEF_ROMLOC(727A) : D4 = d4backup;
  D5 = d5backup;
  D6 = d6backup;
  // TODO; // MOVEM.L	(A7)+,D4-D6
  DEF_ROMLOC(727E) : add_toreg_16(0x10, &D4); // ADDI.W	#$0010,D4
  DEF_ROMLOC(7282) : dec_reg_16(&D6);
  if ((D6 & 0xffff) != 0xffff)
    goto rom_725E;           // DBF.W	D6,$725E
  DEF_ROMLOC(7286) : return; // RTS
}
void draw_bg_sbz(void) {
  DEF_ROMLOC(7288) : move_toreg_32(0xFFFFFFF0, &D4); // MOVEQ.L	$F0,D4
  DEF_ROMLOC(728A) : move_toreg_32(0xF, &D6);        // MOVEQ.L	$0F,D6
  u32 d4backup = 0;
  u32 d5backup = 0;
  u32 d6backup = 0;
  DEF_ROMLOC(728C) : d4backup = D4;
  d5backup = D5;
  d6backup = D6;
  // TODO; // MOVEM.L	D4-D6,-(A7)
  DEF_ROMLOC(7290) : move_toreg_32(0x6DF5, &A0); // LEA.L	$00006DF5,A0
  DEF_ROMLOC(7296)
      : move_toreg_16(read_16(0xFFFFF70C), &D0); // MOVE.W	$F70C,D0
  DEF_ROMLOC(729A) : add_toreg_16(D4, &D0);      // ADD.W	D4,D0
  DEF_ROMLOC(729C) : and_toreg_16(0x1F0, &D0);   // ANDI.W	#$01F0,D0
  DEF_ROMLOC(72A0) : draw_bg_end();              // BSR.W	$72BA
  DEF_ROMLOC(72A4) : D4 = d4backup;
  D5 = d5backup;
  D6 = d6backup;
  // TODO; // MOVEM.L	(A7)+,D4-D6
  DEF_ROMLOC(72A8) : add_toreg_16(0x10, &D4); // ADDI.W	#$0010,D4
  DEF_ROMLOC(72AC) : dec_reg_16(&D6);
  if ((D6 & 0xffff) != 0xffff)
    goto rom_728C;           // DBF.W	D6,$728C
  DEF_ROMLOC(72B0) : return; // RTS
}
void draw_bg_end(void) {
  u32 d4backup = 0;
  u32 d5backup = 0;
  DEF_ROMLOC(72BA) : lsr_toreg_16(0x4, &D0); // LSR.W	#$04,D0
  DEF_ROMLOC(72BC)
      : move_toreg_8(read_8((s32)A0 + (s8)0x0 + (s16)D0),
                     &D0); // MOVE.B	0(A0,D0),D0
  DEF_ROMLOC(72C0)
      : move_toreg_16(read_16(0x72B2 + (s16)(D0 & 0xffff)),
                      &A3);                          // MOVEA.W	-16(PC,D0),A3
  DEF_ROMLOC(72C4) : if (CCR_EQ) goto rom_72DA;      // BEQ.B	$72DA
  DEF_ROMLOC(72C6) : move_toreg_32(0xFFFFFFF0, &D5); // MOVEQ.L	$F0,D5
  DEF_ROMLOC(72C8) : d4backup = D4;
  d5backup = D5;                               // TODO; // MOVEM.L	D4-D5,-(A7)
  DEF_ROMLOC(72CC) : calc_vram_pos_relative(); // BSR.W	$7174
  DEF_ROMLOC(72D0) : D4 = d4backup;
  D5 = d5backup; // TODO; // MOVEM.L	(A7)+,D4-D5
  DEF_ROMLOC(72D4) : draw_blocks_scroll_vert_full(); // BSR.W	$7028
  goto rom_72EE;                                     // BRA.B	$72EE
  DEF_ROMLOC(72DA) : move_toreg_32(0x0, &D5);        // MOVEQ.L	$00,D5
  DEF_ROMLOC(72DC) : d4backup = D4;
  d5backup = D5;                      // TODO; // MOVEM.L	D4-D5,-(A7)
  DEF_ROMLOC(72E0) : calc_vram_pos(); // BSR.W	$7176
  DEF_ROMLOC(72E4) : D4 = d4backup;
  D5 = d5backup;                               // TODO; // MOVEM.L	(A7)+,D4-D5
  DEF_ROMLOC(72E8) : move_toreg_32(0x1F, &D6); // MOVEQ.L	$1F,D6
  DEF_ROMLOC(72EA) : draw_blocks_scroll_vert_alt(); // BSR.W	$7054
  DEF_ROMLOC(72EE) : return;                        // RTS
}