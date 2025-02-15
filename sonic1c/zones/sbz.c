// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_6E16) {
  u32 d4backup = 0;
  u32 d5backup = 0;
  DEF_ROMLOC(6E16) : move_toreg_32(0xFFFFFFF0, &D4); // MOVEQ.L	$F0,D4
  DEF_ROMLOC(6E18) : bclr_tomem_8(0x0, A2);          // BCLR.B	#$00,(A2)
  DEF_ROMLOC(6E1C) : if (!CCR_EQ) goto rom_6E28;     // BNE.B	$6E28
  DEF_ROMLOC(6E1E) : bclr_tomem_8(0x1, A2);          // BCLR.B	#$01,(A2)
  DEF_ROMLOC(6E22) : if (CCR_EQ) goto rom_6E72;      // BEQ.B	$6E72
  DEF_ROMLOC(6E24) : move_toreg_16(0xE0, &D4);       // MOVE.W	#$00E0,D4
  DEF_ROMLOC(6E28) : move_toreg_32(0x6DF5, &A0);     // LEA.L	$00006DF5,A0
  DEF_ROMLOC(6E2E)
      : move_toreg_16(read_16(0xFFFFF70C), &D0); // MOVE.W	$F70C,D0
  DEF_ROMLOC(6E32) : add_toreg_16(D4, &D0);      // ADD.W	D4,D0
  DEF_ROMLOC(6E34) : and_toreg_16(0x1F0, &D0);   // ANDI.W	#$01F0,D0
  DEF_ROMLOC(6E38) : lsr_toreg_16(0x4, &D0);     // LSR.W	#$04,D0
  DEF_ROMLOC(6E3A)
      : move_toreg_8(read_8((s32)A0 + (s8)0x0 + (s16)D0),
                     &D0);                       // MOVE.B	0(A0,D0),D0
  DEF_ROMLOC(6E3E) : move_toreg_32(0x6FE4, &A3); // LEA.L	$00006FE4,A3
  DEF_ROMLOC(6E44)
      : move_toreg_16(read_16((s32)A3 + (s8)0x0 + (s16)D0),
                      &A3);                          // MOVEA.W	0(A3,D0),A3
  DEF_ROMLOC(6E48) : if (CCR_EQ) goto rom_6E5E;      // BEQ.B	$6E5E
  DEF_ROMLOC(6E4A) : move_toreg_32(0xFFFFFFF0, &D5); // MOVEQ.L	$F0,D5
  DEF_ROMLOC(6E4C) : d4backup = D4;
  d5backup = D5;                               // TODO; // MOVEM.L	D4-D5,-(A7)
  DEF_ROMLOC(6E50) : calc_vram_pos_relative(); // BSR.W	$7174
  DEF_ROMLOC(6E54) : D4 = d4backup;
  D5 = d5backup; // TODO; // MOVEM.L	(A7)+,D4-D5
  DEF_ROMLOC(6E58) : draw_blocks_scroll_vert_full(); // BSR.W	$7028
  goto rom_6E72;                                     // BRA.B	$6E72
  DEF_ROMLOC(6E5E) : move_toreg_32(0x0, &D5);        // MOVEQ.L	$00,D5
  DEF_ROMLOC(6E60) : d4backup = D4;
  d5backup = D5;                      // TODO; // MOVEM.L	D4-D5,-(A7)
  DEF_ROMLOC(6E64) : calc_vram_pos(); // BSR.W	$7176
  DEF_ROMLOC(6E68) : D4 = d4backup;
  D5 = d5backup;                               // TODO; // MOVEM.L	(A7)+,D4-D5
  DEF_ROMLOC(6E6C) : move_toreg_32(0x1F, &D6); // MOVEQ.L	$1F,D6
  DEF_ROMLOC(6E6E) : draw_blocks_scroll_vert_alt();  // BSR.W	$7054
  DEF_ROMLOC(6E72) : tst_mem_8(A2);                  // TST.B	(A2)
  DEF_ROMLOC(6E74) : if (!CCR_EQ) goto rom_6E78;     // BNE.B	$6E78
  DEF_ROMLOC(6E76) : return;                         // RTS
  DEF_ROMLOC(6E78) : move_toreg_32(0xFFFFFFF0, &D4); // MOVEQ.L	$F0,D4
  DEF_ROMLOC(6E7A) : move_toreg_32(0xFFFFFFF0, &D5); // MOVEQ.L	$F0,D5
  DEF_ROMLOC(6E7C) : move_toreg_8(read_8(A2), &D0);  // MOVE.B	(A2),D0
  DEF_ROMLOC(6E7E) : and_toreg_8(0xFFFFFFA8, &D0);   // ANDI.B	#$A8,D0
  DEF_ROMLOC(6E82) : if (CCR_EQ) goto rom_6E8C;      // BEQ.B	$6E8C
  DEF_ROMLOC(6E84) : lsr_toreg_8(0x1, &D0);          // LSR.B	#$01,D0
  DEF_ROMLOC(6E86) : move_tomem_8(D0, A2);           // MOVE.B	D0,(A2)
  DEF_ROMLOC(6E88) : move_toreg_16(0x140, &D5);      // MOVE.W	#$0140,D5
  DEF_ROMLOC(6E8C) : move_toreg_32(0x6DF4, &A0);     // LEA.L	$00006DF4,A0
  DEF_ROMLOC(6E92)
      : move_toreg_16(read_16(0xFFFFF70C), &D0); // MOVE.W	$F70C,D0
  DEF_ROMLOC(6E96) : and_toreg_16(0x1F0, &D0);   // ANDI.W	#$01F0,D0
  DEF_ROMLOC(6E9A) : lsr_toreg_16(0x4, &D0);     // LSR.W	#$04,D0
  DEF_ROMLOC(6E9C)
      : move_toreg_32((s32)A0 + (s8)0x0 + (s16)D0,
                      &A0); // LEA.L	0(A0,D0),A0
  draw_bg_layer_3_alt();    // BRA.W	$6FEC
}
ROMFUNC(rom_67BC) {
  DEF_ROMLOC(67BC) : tst_mem_8(v_act); // TST.B	$FE11
  DEF_ROMLOC(67C0) : if (!CCR_EQ) {
    rom_68A2();
    return;
  } // BNE.W	$68A2
  DEF_ROMLOC(67C4)
      : move_toreg_16(read_16(0xFFFFF73A), &D4); // MOVE.W	$F73A,D4
  DEF_ROMLOC(67C8) : ext_reg_32(&D4);            // EXT.L	D4
  DEF_ROMLOC(67CA) : asl_toreg_32(0x7, &D4);     // ASL.L	#$07,D4
  DEF_ROMLOC(67CC) : move_toreg_32(0x2, &D6);    // MOVEQ.L	$02,D6
  DEF_ROMLOC(67CE) : scroll_bg_layer_1();        // BSR.W	$6B94
  DEF_ROMLOC(67D2)
      : move_toreg_16(read_16(0xFFFFF73A), &D4); // MOVE.W	$F73A,D4
  DEF_ROMLOC(67D6) : ext_reg_32(&D4);            // EXT.L	D4
  DEF_ROMLOC(67D8) : asl_toreg_32(0x6, &D4);     // ASL.L	#$06,D4
  DEF_ROMLOC(67DA) : move_toreg_32(0x6, &D6);    // MOVEQ.L	$06,D6
  DEF_ROMLOC(67DC) : scroll_bg_layer_3();        // BSR.W	$6BFC
  DEF_ROMLOC(67E0)
      : move_toreg_16(read_16(0xFFFFF73A), &D4); // MOVE.W	$F73A,D4
  DEF_ROMLOC(67E4) : ext_reg_32(&D4);            // EXT.L	D4
  DEF_ROMLOC(67E6) : asl_toreg_32(0x5, &D4);     // ASL.L	#$05,D4
  DEF_ROMLOC(67E8) : move_toreg_32(D4, &D1);     // MOVE.L	D4,D1
  DEF_ROMLOC(67EA) : asl_toreg_32(0x1, &D4);     // ASL.L	#$01,D4
  DEF_ROMLOC(67EC) : add_toreg_32(D1, &D4);      // ADD.L	D1,D4
  DEF_ROMLOC(67EE) : move_toreg_32(0x4, &D6);    // MOVEQ.L	$04,D6
  DEF_ROMLOC(67F0) : scroll_bg_layer_2();        // BSR.W	$6BC8
  DEF_ROMLOC(67F4) : move_toreg_32(0x0, &D4);    // MOVEQ.L	$00,D4
  DEF_ROMLOC(67F6)
      : move_toreg_16(read_16(0xFFFFF73C), &D5); // MOVE.W	$F73C,D5
  DEF_ROMLOC(67FA) : ext_reg_32(&D5);            // EXT.L	D5
  DEF_ROMLOC(67FC) : asl_toreg_32(0x5, &D5);     // ASL.L	#$05,D5
  DEF_ROMLOC(67FE) : scroll_bg_y_relative();     // BSR.W	$6AF8
  DEF_ROMLOC(6802)
      : move_toreg_16(read_16(0xFFFFF70C), &D0);    // MOVE.W	$F70C,D0
  DEF_ROMLOC(6806) : move_tomem_16(D0, 0xFFFFF714); // MOVE.W	D0,$F714
  DEF_ROMLOC(680A) : move_tomem_16(D0, 0xFFFFF71C); // MOVE.W	D0,$F71C
  DEF_ROMLOC(680E) : move_tomem_16(D0, 0xFFFFF618); // MOVE.W	D0,$F618
  DEF_ROMLOC(6812)
      : move_toreg_8(read_8(0xFFFFF756), &D0);            // MOVE.B	$F756,D0
  DEF_ROMLOC(6816) : or_toreg_8(read_8(0xFFFFF75A), &D0); // OR.B	$F75A,D0
  DEF_ROMLOC(681A) : or_tomem_8(D0, 0xFFFFF758);          // OR.B	D0,$F758
  DEF_ROMLOC(681E) : clr_mem_8(0xFFFFF756);               // CLR.B	$F756
  DEF_ROMLOC(6822) : clr_mem_8(0xFFFFF75A);               // CLR.B	$F75A
  DEF_ROMLOC(6826) : move_toreg_32(0xFFFFA800, &A1);      // LEA.L	$A800,A1
  DEF_ROMLOC(682A)
      : move_toreg_16(read_16(0xFFFFF700), &D2);           // MOVE.W	$F700,D2
  DEF_ROMLOC(682E) : neg_reg_16(&D2);                      // NEG.W	D2
  DEF_ROMLOC(6830) : asr_toreg_16(0x2, &D2);               // ASR.W	#$02,D2
  DEF_ROMLOC(6832) : move_toreg_16(D2, &D0);               // MOVE.W	D2,D0
  DEF_ROMLOC(6834) : asr_toreg_16(0x1, &D0);               // ASR.W	#$01,D0
  DEF_ROMLOC(6836) : sub_toreg_16(D2, &D0);                // SUB.W	D2,D0
  DEF_ROMLOC(6838) : ext_reg_32(&D0);                      // EXT.L	D0
  DEF_ROMLOC(683A) : asl_toreg_32(0x3, &D0);               // ASL.L	#$03,D0
  DEF_ROMLOC(683C) : divs_toreg_16(0x4, &D0);              // DIVS.W	#$0004,D0
  DEF_ROMLOC(6840) : ext_reg_32(&D0);                      // EXT.L	D0
  DEF_ROMLOC(6842) : asl_toreg_32(0x4, &D0);               // ASL.L	#$04,D0
  DEF_ROMLOC(6844) : asl_toreg_32(0x8, &D0);               // ASL.L	#$08,D0
  DEF_ROMLOC(6846) : move_toreg_32(0x0, &D3);              // MOVEQ.L	$00,D3
  DEF_ROMLOC(6848) : move_toreg_16(D2, &D3);               // MOVE.W	D2,D3
  DEF_ROMLOC(684A) : move_toreg_16(0x3, &D1);              // MOVE.W	#$0003,D1
  DEF_ROMLOC(684E) : move_tomem_16(D3, (A1 += 2, A1 - 2)); // MOVE.W	D3,(A1)+
  DEF_ROMLOC(6850) : SWAPWORDS(D3);                        // SWAP.W	D3
  DEF_ROMLOC(6852) : add_toreg_32(D0, &D3);                // ADD.L	D0,D3
  DEF_ROMLOC(6854) : SWAPWORDS(D3);                        // SWAP.W	D3
  DEF_ROMLOC(6856) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_684E; // DBF.W	D1,$684E
  DEF_ROMLOC(685A)
      : move_toreg_16(read_16(0xFFFFF718), &D0);           // MOVE.W	$F718,D0
  DEF_ROMLOC(685E) : neg_reg_16(&D0);                      // NEG.W	D0
  DEF_ROMLOC(6860) : move_toreg_16(0x9, &D1);              // MOVE.W	#$0009,D1
  DEF_ROMLOC(6864) : move_tomem_16(D0, (A1 += 2, A1 - 2)); // MOVE.W	D0,(A1)+
  DEF_ROMLOC(6866) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_6864; // DBF.W	D1,$6864
  DEF_ROMLOC(686A)
      : move_toreg_16(read_16(0xFFFFF710), &D0);           // MOVE.W	$F710,D0
  DEF_ROMLOC(686E) : neg_reg_16(&D0);                      // NEG.W	D0
  DEF_ROMLOC(6870) : move_toreg_16(0x6, &D1);              // MOVE.W	#$0006,D1
  DEF_ROMLOC(6874) : move_tomem_16(D0, (A1 += 2, A1 - 2)); // MOVE.W	D0,(A1)+
  DEF_ROMLOC(6876) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_6874; // DBF.W	D1,$6874
  DEF_ROMLOC(687A)
      : move_toreg_16(read_16(0xFFFFF708), &D0);           // MOVE.W	$F708,D0
  DEF_ROMLOC(687E) : neg_reg_16(&D0);                      // NEG.W	D0
  DEF_ROMLOC(6880) : move_toreg_16(0xA, &D1);              // MOVE.W	#$000A,D1
  DEF_ROMLOC(6884) : move_tomem_16(D0, (A1 += 2, A1 - 2)); // MOVE.W	D0,(A1)+
  DEF_ROMLOC(6886) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_6884;                                   // DBF.W	D1,$6884
  DEF_ROMLOC(688A) : move_toreg_32(0xFFFFA800, &A2); // LEA.L	$A800,A2
  DEF_ROMLOC(688E)
      : move_toreg_16(read_16(0xFFFFF70C), &D0); // MOVE.W	$F70C,D0
  DEF_ROMLOC(6892) : move_toreg_16(D0, &D2);     // MOVE.W	D0,D2
  DEF_ROMLOC(6894) : and_toreg_16(0x1F0, &D0);   // ANDI.W	#$01F0,D0
  DEF_ROMLOC(6898) : lsr_toreg_16(0x3, &D0);     // LSR.W	#$03,D0
  DEF_ROMLOC(689A)
      : move_toreg_32((s32)A2 + (s8)0x0 + (s16)D0,
                      &A2); // LEA.L	0(A2,D0),A2
  rom_66CC();               // BRA.W	$66CC
}
ROMFUNC(rom_68A2) {
  DEF_ROMLOC(68A2)
      : move_toreg_16(read_16(0xFFFFF73A), &D4); // MOVE.W	$F73A,D4
  DEF_ROMLOC(68A6) : ext_reg_32(&D4);            // EXT.L	D4
  DEF_ROMLOC(68A8) : asl_toreg_32(0x6, &D4);     // ASL.L	#$06,D4
  DEF_ROMLOC(68AA)
      : move_toreg_16(read_16(0xFFFFF73C), &D5); // MOVE.W	$F73C,D5
  DEF_ROMLOC(68AE) : ext_reg_32(&D5);            // EXT.L	D5
  DEF_ROMLOC(68B0) : asl_toreg_32(0x5, &D5);     // ASL.L	#$05,D5
  DEF_ROMLOC(68B2) : scroll_bg_full();           // BSR.W	$6AC4
  DEF_ROMLOC(68B6)
      : move_tomem_16(read_16(0xFFFFF70C),
                      0xFFFFF618);                   // MOVE.W	$F70C,$F618
  DEF_ROMLOC(68BC) : move_toreg_32(0xFFFFCC00, &A1); // LEA.L	$CC00,A1
  DEF_ROMLOC(68C0) : move_toreg_16(0xDF, &D1);       // MOVE.W	#$00DF,D1
  DEF_ROMLOC(68C4)
      : move_toreg_16(read_16(0xFFFFF700), &D0); // MOVE.W	$F700,D0
  DEF_ROMLOC(68C8) : neg_reg_16(&D0);            // NEG.W	D0
  DEF_ROMLOC(68CA) : SWAPWORDS(D0);              // SWAP.W	D0
  DEF_ROMLOC(68CC)
      : move_toreg_16(read_16(0xFFFFF708), &D0);           // MOVE.W	$F708,D0
  DEF_ROMLOC(68D0) : neg_reg_16(&D0);                      // NEG.W	D0
  DEF_ROMLOC(68D2) : move_tomem_32(D0, (A1 += 4, A1 - 4)); // MOVE.L	D0,(A1)+
  DEF_ROMLOC(68D4) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_68D2;           // DBF.W	D1,$68D2
  DEF_ROMLOC(68D8) : return; // RTS
}