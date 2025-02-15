// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_61AA) {
  u8 switchindex = 0;
  DEF_ROMLOC(61AA) : tst_mem_8(0xFFFFFE30);         // TST.B	$FE30
  DEF_ROMLOC(61AE) : if (!CCR_EQ) goto rom_61C4;    // BNE.B	$61C4
  DEF_ROMLOC(61B0) : move_tomem_16(D0, 0xFFFFF70C); // MOVE.W	D0,$F70C
  DEF_ROMLOC(61B4) : move_tomem_16(D0, 0xFFFFF714); // MOVE.W	D0,$F714
  DEF_ROMLOC(61B8) : move_tomem_16(D1, 0xFFFFF708); // MOVE.W	D1,$F708
  DEF_ROMLOC(61BC) : move_tomem_16(D1, 0xFFFFF710); // MOVE.W	D1,$F710
  DEF_ROMLOC(61C0) : move_tomem_16(D1, 0xFFFFF718); // MOVE.W	D1,$F718
  DEF_ROMLOC(61C4) : move_toreg_32(0x0, &D2);       // MOVEQ.L	$00,D2
  DEF_ROMLOC(61C6) : move_toreg_8(read_8(v_zone), &D2);
  switchindex = D2;                         // MOVE.B	$FE10,D2
  DEF_ROMLOC(61CA) : add_toreg_16(D2, &D2); // ADD.W	D2,D2
  DEF_ROMLOC(61CC)
      : move_toreg_16(read_16(0x61D4 + (s16)(D2 & 0xffff)),
                      &D2); // MOVE.W	6(PC,D2),D2
  // DEF_ROMLOC(61D0): goto rom_61D4 + (s16)(D2 & 0xffff); // JMP	2(PC,D2)
  DEF_ROMLOC(61D0) : switch (switchindex) {
  case 0:
    rom_61E2();
    break;
  case 1:
    rom_61FE();
    break;
  case 2:
    rom_6206();
    break;
  case 3:
    rom_6208();
    break;
  case 4:
    rom_6218();
    break;
  case 5:
    rom_622E();
    break;
  case 6:
    rom_623C();
    break;
  }
}
ROMFUNC(rom_61E2) {
  DEF_ROMLOC(61E2) : clr_mem_32(0xFFFFF708);         // CLR.L	$F708
  DEF_ROMLOC(61E6) : clr_mem_32(0xFFFFF70C);         // CLR.L	$F70C
  DEF_ROMLOC(61EA) : clr_mem_32(0xFFFFF714);         // CLR.L	$F714
  DEF_ROMLOC(61EE) : clr_mem_32(0xFFFFF71C);         // CLR.L	$F71C
  DEF_ROMLOC(61F2) : move_toreg_32(0xFFFFA800, &A2); // LEA.L	$A800,A2
  DEF_ROMLOC(61F6) : clr_mem_32((A2 += 4, A2 - 4));  // CLR.L	(A2)+
  DEF_ROMLOC(61F8) : clr_mem_32((A2 += 4, A2 - 4));  // CLR.L	(A2)+
  DEF_ROMLOC(61FA) : clr_mem_32((A2 += 4, A2 - 4));  // CLR.L	(A2)+
  DEF_ROMLOC(61FC) : return;                         // RTS
}
ROMFUNC(rom_61FE) {
  DEF_ROMLOC(61FE) : asr_toreg_32(0x1, &D0);        // ASR.L	#$01,D0
  DEF_ROMLOC(6200) : move_tomem_16(D0, 0xFFFFF70C); // MOVE.W	D0,$F70C
  DEF_ROMLOC(6204) : return;                        // RTS
}
ROMFUNC(rom_6206) {
  DEF_ROMLOC(6206) : return; // RTS
}
ROMFUNC(rom_6208) {
  DEF_ROMLOC(6208) : asr_toreg_32(0x1, &D0);        // ASR.L	#$01,D0
  DEF_ROMLOC(620A) : add_toreg_16(0xC0, &D0);       // ADDI.W	#$00C0,D0
  DEF_ROMLOC(620E) : move_tomem_16(D0, 0xFFFFF70C); // MOVE.W	D0,$F70C
  DEF_ROMLOC(6212) : clr_mem_32(0xFFFFF708);        // CLR.L	$F708
  DEF_ROMLOC(6216) : return;                        // RTS
}
ROMFUNC(rom_6218) {
  DEF_ROMLOC(6218) : asl_toreg_32(0x4, &D0);        // ASL.L	#$04,D0
  DEF_ROMLOC(621A) : move_toreg_32(D0, &D2);        // MOVE.L	D0,D2
  DEF_ROMLOC(621C) : asl_toreg_32(0x1, &D0);        // ASL.L	#$01,D0
  DEF_ROMLOC(621E) : add_toreg_32(D2, &D0);         // ADD.L	D2,D0
  DEF_ROMLOC(6220) : asr_toreg_32(0x8, &D0);        // ASR.L	#$08,D0
  DEF_ROMLOC(6222) : add_toreg_16(0x1, &D0);        // ADDQ.W	#$01,D0
  DEF_ROMLOC(6224) : move_tomem_16(D0, 0xFFFFF70C); // MOVE.W	D0,$F70C
  DEF_ROMLOC(6228) : clr_mem_32(0xFFFFF708);        // CLR.L	$F708
  DEF_ROMLOC(622C) : return;                        // RTS
}
ROMFUNC(rom_622E) {
  DEF_ROMLOC(622E) : and_toreg_16(0x7F8, &D0);      // ANDI.W	#$07F8,D0
  DEF_ROMLOC(6232) : asr_toreg_16(0x3, &D0);        // ASR.W	#$03,D0
  DEF_ROMLOC(6234) : add_toreg_16(0x1, &D0);        // ADDQ.W	#$01,D0
  DEF_ROMLOC(6236) : move_tomem_16(D0, 0xFFFFF70C); // MOVE.W	D0,$F70C
  DEF_ROMLOC(623A) : return;                        // RTS
}
ROMFUNC(rom_623C) {
  DEF_ROMLOC(623C)
      : move_toreg_16(read_16(0xFFFFF700), &D0);     // MOVE.W	$F700,D0
  DEF_ROMLOC(6240) : asr_toreg_16(0x1, &D0);         // ASR.W	#$01,D0
  DEF_ROMLOC(6242) : move_tomem_16(D0, 0xFFFFF708);  // MOVE.W	D0,$F708
  DEF_ROMLOC(6246) : move_tomem_16(D0, 0xFFFFF710);  // MOVE.W	D0,$F710
  DEF_ROMLOC(624A) : asr_toreg_16(0x2, &D0);         // ASR.W	#$02,D0
  DEF_ROMLOC(624C) : move_toreg_16(D0, &D1);         // MOVE.W	D0,D1
  DEF_ROMLOC(624E) : add_toreg_16(D0, &D0);          // ADD.W	D0,D0
  DEF_ROMLOC(6250) : add_toreg_16(D1, &D0);          // ADD.W	D1,D0
  DEF_ROMLOC(6252) : move_tomem_16(D0, 0xFFFFF718);  // MOVE.W	D0,$F718
  DEF_ROMLOC(6256) : clr_mem_32(0xFFFFF70C);         // CLR.L	$F70C
  DEF_ROMLOC(625A) : clr_mem_32(0xFFFFF714);         // CLR.L	$F714
  DEF_ROMLOC(625E) : clr_mem_32(0xFFFFF71C);         // CLR.L	$F71C
  DEF_ROMLOC(6262) : move_toreg_32(0xFFFFA800, &A2); // LEA.L	$A800,A2
  DEF_ROMLOC(6266) : clr_mem_32((A2 += 4, A2 - 4));  // CLR.L	(A2)+
  DEF_ROMLOC(6268) : clr_mem_32((A2 += 4, A2 - 4));  // CLR.L	(A2)+
  DEF_ROMLOC(626A) : clr_mem_32((A2 += 4, A2 - 4));  // CLR.L	(A2)+
  DEF_ROMLOC(626C) : return;                         // RTS
}

ROMFUNC(rom_626E) {
  u8 switchindex = 0;
  DEF_ROMLOC(626E) : tst_mem_8(0xFFFFF744);     // TST.B	$F744
  DEF_ROMLOC(6272) : if (CCR_EQ) goto rom_6276; // BEQ.B	$6276
  DEF_ROMLOC(6274) : return;                    // RTS
  DEF_ROMLOC(6276) : clr_mem_16(0xFFFFF754);    // CLR.W	$F754
  DEF_ROMLOC(627A) : clr_mem_16(0xFFFFF756);    // CLR.W	$F756
  DEF_ROMLOC(627E) : clr_mem_16(0xFFFFF758);    // CLR.W	$F758
  DEF_ROMLOC(6282) : clr_mem_16(0xFFFFF75A);    // CLR.W	$F75A
  DEF_ROMLOC(6286) : handle_scroll_horiz();     // BSR.W	$68DA
  DEF_ROMLOC(628A) : handle_scroll_vert();      // BSR.W	$6972
  DEF_ROMLOC(628E) : rom_73B6();                // BSR.W	$73B6
  DEF_ROMLOC(6292)
      : move_tomem_16(read_16(0xFFFFF704),
                      0xFFFFF616); // MOVE.W	$F704,$F616
  DEF_ROMLOC(6298)
      : move_tomem_16(read_16(0xFFFFF70C),
                      0xFFFFF618);            // MOVE.W	$F70C,$F618
  DEF_ROMLOC(629E) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(62A0) : move_toreg_8(read_8(v_zone), &D0);
  switchindex = D0;                         // MOVE.B	$FE10,D0
  DEF_ROMLOC(62A4) : add_toreg_16(D0, &D0); // ADD.W	D0,D0
  DEF_ROMLOC(62A6)
      : move_toreg_16(read_16(0x62AE + (s16)(D0 & 0xffff)),
                      &D0); // MOVE.W	6(PC,D0),D0
  // DEF_ROMLOC(62AA): goto rom_62AE + (s16)(D0 & 0xffff); // JMP	2(PC,D0)
  DEF_ROMLOC(62AA) : switch (switchindex) {
  case 0:
    rom_62BC();
    break;
  case 1:
    rom_63B6();
    break;
  case 2:
    rom_6548();
    break;
  case 3:
    rom_6640();
    break;
  case 4:
    rom_6710();
    break;
  case 5:
    rom_67BC();
    break;
  case 6:
    rom_62BC();
    break;
  }
}
ROMFUNC(rom_62BC) {
  DEF_ROMLOC(62BC)
      : move_toreg_16(read_16(0xFFFFF73A), &D4); // MOVE.W	$F73A,D4
  DEF_ROMLOC(62C0) : ext_reg_32(&D4);            // EXT.L	D4
  DEF_ROMLOC(62C2) : asl_toreg_32(0x5, &D4);     // ASL.L	#$05,D4
  DEF_ROMLOC(62C4) : move_toreg_32(D4, &D1);     // MOVE.L	D4,D1
  DEF_ROMLOC(62C6) : asl_toreg_32(0x1, &D4);     // ASL.L	#$01,D4
  DEF_ROMLOC(62C8) : add_toreg_32(D1, &D4);      // ADD.L	D1,D4
  DEF_ROMLOC(62CA) : move_toreg_32(0x0, &D6);    // MOVEQ.L	$00,D6
  DEF_ROMLOC(62CC) : scroll_bg_layer_3();        // BSR.W	$6BFC
  DEF_ROMLOC(62D0)
      : move_toreg_16(read_16(0xFFFFF73A), &D4);     // MOVE.W	$F73A,D4
  DEF_ROMLOC(62D4) : ext_reg_32(&D4);                // EXT.L	D4
  DEF_ROMLOC(62D6) : asl_toreg_32(0x7, &D4);         // ASL.L	#$07,D4
  DEF_ROMLOC(62D8) : move_toreg_32(0x0, &D6);        // MOVEQ.L	$00,D6
  DEF_ROMLOC(62DA) : scroll_bg_layer_2();            // BSR.W	$6BC8
  DEF_ROMLOC(62DE) : move_toreg_32(0xFFFFCC00, &A1); // LEA.L	$CC00,A1
  DEF_ROMLOC(62E2)
      : move_toreg_16(read_16(0xFFFFF704), &D0);    // MOVE.W	$F704,D0
  DEF_ROMLOC(62E6) : and_toreg_16(0x7FF, &D0);      // ANDI.W	#$07FF,D0
  DEF_ROMLOC(62EA) : lsr_toreg_16(0x5, &D0);        // LSR.W	#$05,D0
  DEF_ROMLOC(62EC) : neg_reg_16(&D0);               // NEG.W	D0
  DEF_ROMLOC(62EE) : add_toreg_16(0x20, &D0);       // ADDI.W	#$0020,D0
  DEF_ROMLOC(62F2) : if (CCR_PL) goto rom_62F6;     // BPL.B	$62F6
  DEF_ROMLOC(62F4) : move_toreg_32(0x0, &D0);       // MOVEQ.L	$00,D0
  DEF_ROMLOC(62F6) : move_toreg_16(D0, &D4);        // MOVE.W	D0,D4
  DEF_ROMLOC(62F8) : move_tomem_16(D0, 0xFFFFF618); // MOVE.W	D0,$F618
  DEF_ROMLOC(62FC)
      : move_toreg_16(read_16(0xFFFFF700), &D0);     // MOVE.W	$F700,D0
  DEF_ROMLOC(6300) : cmp_tomem_8(GM_TITLE, v_gamemode);   // CMPI.B	#$04,$F600
  DEF_ROMLOC(6306) : if (!CCR_EQ) goto rom_630A;     // BNE.B	$630A
  DEF_ROMLOC(6308) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(630A) : neg_reg_16(&D0);                // NEG.W	D0
  DEF_ROMLOC(630C) : swap_reg_16(&D0);               // SWAP.W	D0
  DEF_ROMLOC(630E) : move_toreg_32(0xFFFFA800, &A2); // LEA.L	$A800,A2
  DEF_ROMLOC(6312)
      : add_tomem_32(0x10000, (A2 += 4, A2 - 4)); // ADDI.L	#$00010000,(A2)+
  DEF_ROMLOC(6318)
      : add_tomem_32(0xC000, (A2 += 4, A2 - 4)); // ADDI.L	#$0000C000,(A2)+
  DEF_ROMLOC(631E)
      : add_tomem_32(0x8000, (A2 += 4, A2 - 4)); // ADDI.L	#$00008000,(A2)+
  DEF_ROMLOC(6324)
      : move_toreg_16(read_16(0xFFFFA800), &D0); // MOVE.W	$A800,D0
  DEF_ROMLOC(6328)
      : add_toreg_16(read_16(0xFFFFF718), &D0);            // ADD.W	$F718,D0
  DEF_ROMLOC(632C) : neg_reg_16(&D0);                      // NEG.W	D0
  DEF_ROMLOC(632E) : move_toreg_16(0x1F, &D1);             // MOVE.W	#$001F,D1
  DEF_ROMLOC(6332) : sub_toreg_16(D4, &D1);                // SUB.W	D4,D1
  DEF_ROMLOC(6334) : if (CCR_CS) goto rom_633C;            // BCS.B	$633C
  DEF_ROMLOC(6336) : move_tomem_32(D0, (A1 += 4, A1 - 4)); // MOVE.L	D0,(A1)+
  DEF_ROMLOC(6338) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_6336; // DBF.W	D1,$6336
  DEF_ROMLOC(633C)
      : move_toreg_16(read_16(0xFFFFA804), &D0); // MOVE.W	$A804,D0
  DEF_ROMLOC(6340)
      : add_toreg_16(read_16(0xFFFFF718), &D0);            // ADD.W	$F718,D0
  DEF_ROMLOC(6344) : neg_reg_16(&D0);                      // NEG.W	D0
  DEF_ROMLOC(6346) : move_toreg_16(0xF, &D1);              // MOVE.W	#$000F,D1
  DEF_ROMLOC(634A) : move_tomem_32(D0, (A1 += 4, A1 - 4)); // MOVE.L	D0,(A1)+
  DEF_ROMLOC(634C) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_634A; // DBF.W	D1,$634A
  DEF_ROMLOC(6350)
      : move_toreg_16(read_16(0xFFFFA808), &D0); // MOVE.W	$A808,D0
  DEF_ROMLOC(6354)
      : add_toreg_16(read_16(0xFFFFF718), &D0);            // ADD.W	$F718,D0
  DEF_ROMLOC(6358) : neg_reg_16(&D0);                      // NEG.W	D0
  DEF_ROMLOC(635A) : move_toreg_16(0xF, &D1);              // MOVE.W	#$000F,D1
  DEF_ROMLOC(635E) : move_tomem_32(D0, (A1 += 4, A1 - 4)); // MOVE.L	D0,(A1)+
  DEF_ROMLOC(6360) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_635E;                             // DBF.W	D1,$635E
  DEF_ROMLOC(6364) : move_toreg_16(0x2F, &D1); // MOVE.W	#$002F,D1
  DEF_ROMLOC(6368)
      : move_toreg_16(read_16(0xFFFFF718), &D0);           // MOVE.W	$F718,D0
  DEF_ROMLOC(636C) : neg_reg_16(&D0);                      // NEG.W	D0
  DEF_ROMLOC(636E) : move_tomem_32(D0, (A1 += 4, A1 - 4)); // MOVE.L	D0,(A1)+
  DEF_ROMLOC(6370) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_636E;                             // DBF.W	D1,$636E
  DEF_ROMLOC(6374) : move_toreg_16(0x27, &D1); // MOVE.W	#$0027,D1
  DEF_ROMLOC(6378)
      : move_toreg_16(read_16(0xFFFFF710), &D0);           // MOVE.W	$F710,D0
  DEF_ROMLOC(637C) : neg_reg_16(&D0);                      // NEG.W	D0
  DEF_ROMLOC(637E) : move_tomem_32(D0, (A1 += 4, A1 - 4)); // MOVE.L	D0,(A1)+
  DEF_ROMLOC(6380) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_637E; // DBF.W	D1,$637E
  DEF_ROMLOC(6384)
      : move_toreg_16(read_16(0xFFFFF710), &D0); // MOVE.W	$F710,D0
  DEF_ROMLOC(6388)
      : move_toreg_16(read_16(0xFFFFF700), &D2);           // MOVE.W	$F700,D2
  DEF_ROMLOC(638C) : sub_toreg_16(D0, &D2);                // SUB.W	D0,D2
  DEF_ROMLOC(638E) : ext_reg_32(&D2);                      // EXT.L	D2
  DEF_ROMLOC(6390) : asl_toreg_32(0x8, &D2);               // ASL.L	#$08,D2
  DEF_ROMLOC(6392) : divs_toreg_16(0x68, &D2);             // DIVS.W	#$0068,D2
  DEF_ROMLOC(6396) : ext_reg_32(&D2);                      // EXT.L	D2
  DEF_ROMLOC(6398) : asl_toreg_32(0x8, &D2);               // ASL.L	#$08,D2
  DEF_ROMLOC(639A) : move_toreg_32(0x0, &D3);              // MOVEQ.L	$00,D3
  DEF_ROMLOC(639C) : move_toreg_16(D0, &D3);               // MOVE.W	D0,D3
  DEF_ROMLOC(639E) : move_toreg_16(0x47, &D1);             // MOVE.W	#$0047,D1
  DEF_ROMLOC(63A2) : add_toreg_16(D4, &D1);                // ADD.W	D4,D1
  DEF_ROMLOC(63A4) : move_toreg_16(D3, &D0);               // MOVE.W	D3,D0
  DEF_ROMLOC(63A6) : neg_reg_16(&D0);                      // NEG.W	D0
  DEF_ROMLOC(63A8) : move_tomem_32(D0, (A1 += 4, A1 - 4)); // MOVE.L	D0,(A1)+
  DEF_ROMLOC(63AA) : swap_reg_16(&D3);                     // SWAP.W	D3
  DEF_ROMLOC(63AC) : add_toreg_32(D2, &D3);                // ADD.L	D2,D3
  DEF_ROMLOC(63AE) : swap_reg_16(&D3);                     // SWAP.W	D3
  DEF_ROMLOC(63B0) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_63A4;           // DBF.W	D1,$63A4
  DEF_ROMLOC(63B4) : return; // RTS
}
ROMFUNC(rom_63B6) {
  DEF_ROMLOC(63B6)
      : move_toreg_16(read_16(0xFFFFF73A), &D4); // MOVE.W	$F73A,D4
  DEF_ROMLOC(63BA) : ext_reg_32(&D4);            // EXT.L	D4
  DEF_ROMLOC(63BC) : asl_toreg_32(0x7, &D4);     // ASL.L	#$07,D4
  DEF_ROMLOC(63BE)
      : move_toreg_16(read_16(0xFFFFF73C), &D5); // MOVE.W	$F73C,D5
  DEF_ROMLOC(63C2) : ext_reg_32(&D5);            // EXT.L	D5
  DEF_ROMLOC(63C4) : asl_toreg_32(0x7, &D5);     // ASL.L	#$07,D5
  DEF_ROMLOC(63C6) : scroll_bg_full();           // BSR.W	$6AC4
  DEF_ROMLOC(63CA)
      : move_tomem_16(read_16(0xFFFFF70C),
                      0xFFFFF618);                // MOVE.W	$F70C,$F618
  DEF_ROMLOC(63D0) : move_toreg_32(0x6448, &A3);  // LEA.L	$00006448,A3
  DEF_ROMLOC(63D6) : move_toreg_32(0x144F0, &A2); // LEA.L	$000144F0,A2
  DEF_ROMLOC(63DC) : move_toreg_8(read_8(0xFFFFF7D8), &D2); // MOVE.B	$F7D8,D2
  DEF_ROMLOC(63E0) : move_toreg_8(D2, &D3);                 // MOVE.B	D2,D3
  DEF_ROMLOC(63E2) : add_tomem_16(0x80, 0xFFFFF7D8); // ADDI.W	#$0080,$F7D8
  DEF_ROMLOC(63E8) : add_toreg_16(read_16(0xFFFFF70C), &D2); // ADD.W	$F70C,D2
  DEF_ROMLOC(63EC) : and_toreg_16(0xFF, &D2);                // ANDI.W	#$00FF,D2
  DEF_ROMLOC(63F0) : add_toreg_16(read_16(0xFFFFF704), &D3); // ADD.W	$F704,D3
  DEF_ROMLOC(63F4) : and_toreg_16(0xFF, &D3);                // ANDI.W	#$00FF,D3
  DEF_ROMLOC(63F8) : move_toreg_32(0xFFFFCC00, &A1);         // LEA.L	$CC00,A1
  DEF_ROMLOC(63FC) : move_toreg_16(0xDF, &D1);               // MOVE.W	#$00DF,D1
  DEF_ROMLOC(6400)
      : move_toreg_16(read_16(0xFFFFF700), &D0); // MOVE.W	$F700,D0
  DEF_ROMLOC(6404) : neg_reg_16(&D0);            // NEG.W	D0
  DEF_ROMLOC(6406) : move_toreg_16(D0, &D6);     // MOVE.W	D0,D6
  DEF_ROMLOC(6408) : swap_reg_16(&D0);           // SWAP.W	D0
  DEF_ROMLOC(640A)
      : move_toreg_16(read_16(0xFFFFF708), &D0); // MOVE.W	$F708,D0
  DEF_ROMLOC(640E) : neg_reg_16(&D0);            // NEG.W	D0
  DEF_ROMLOC(6410)
      : move_toreg_16(read_16(0xFFFFF646), &D4); // MOVE.W	$F646,D4
  DEF_ROMLOC(6414)
      : move_toreg_16(read_16(0xFFFFF704), &D5);           // MOVE.W	$F704,D5
  DEF_ROMLOC(6418) : cmp_toreg_16(D4, &D5);                // CMP.W	D4,D5
  DEF_ROMLOC(641A) : if (CCR_GE) goto rom_642A;            // BGE.B	$642A
  DEF_ROMLOC(641C) : move_tomem_32(D0, (A1 += 4, A1 - 4)); // MOVE.L	D0,(A1)+
  DEF_ROMLOC(641E) : add_toreg_16(0x1, &D5);               // ADDQ.W	#$01,D5
  DEF_ROMLOC(6420) : add_toreg_8(0x1, &D2);                // ADDQ.B	#$01,D2
  DEF_ROMLOC(6422) : add_toreg_8(0x1, &D3);                // ADDQ.B	#$01,D3
  DEF_ROMLOC(6424) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_6418;           // DBF.W	D1,$6418
  DEF_ROMLOC(6428) : return; // RTS
  DEF_ROMLOC(642A)
      : move_toreg_8(read_8((s32)A3 + (s8)0x0 + (s16)D3),
                     &D4);                                 // MOVE.B	0(A3,D3),D4
  DEF_ROMLOC(642E) : ext_reg_16(&D4);                      // EXT.W	D4
  DEF_ROMLOC(6430) : add_toreg_16(D6, &D4);                // ADD.W	D6,D4
  DEF_ROMLOC(6432) : move_tomem_16(D4, (A1 += 2, A1 - 2)); // MOVE.W	D4,(A1)+
  DEF_ROMLOC(6434)
      : move_toreg_8(read_8((s32)A2 + (s8)0x0 + (s16)D2),
                     &D4);                                 // MOVE.B	0(A2,D2),D4
  DEF_ROMLOC(6438) : ext_reg_16(&D4);                      // EXT.W	D4
  DEF_ROMLOC(643A) : add_toreg_16(D0, &D4);                // ADD.W	D0,D4
  DEF_ROMLOC(643C) : move_tomem_16(D4, (A1 += 2, A1 - 2)); // MOVE.W	D4,(A1)+
  DEF_ROMLOC(643E) : add_toreg_8(0x1, &D2);                // ADDQ.B	#$01,D2
  DEF_ROMLOC(6440) : add_toreg_8(0x1, &D3);                // ADDQ.B	#$01,D3
  DEF_ROMLOC(6442) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_642A;           // DBF.W	D1,$642A
  DEF_ROMLOC(6446) : return; // RTS
}
ROMFUNC(rom_6548) {
  DEF_ROMLOC(6548)
      : move_toreg_16(read_16(0xFFFFF73A), &D4); // MOVE.W	$F73A,D4
  DEF_ROMLOC(654C) : ext_reg_32(&D4);            // EXT.L	D4
  DEF_ROMLOC(654E) : asl_toreg_32(0x6, &D4);     // ASL.L	#$06,D4
  DEF_ROMLOC(6550) : move_toreg_32(D4, &D1);     // MOVE.L	D4,D1
  DEF_ROMLOC(6552) : asl_toreg_32(0x1, &D4);     // ASL.L	#$01,D4
  DEF_ROMLOC(6554) : add_toreg_32(D1, &D4);      // ADD.L	D1,D4
  DEF_ROMLOC(6556) : move_toreg_32(0x2, &D6);    // MOVEQ.L	$02,D6
  DEF_ROMLOC(6558) : scroll_bg_layer_1();        // BSR.W	$6B94
  DEF_ROMLOC(655C)
      : move_toreg_16(read_16(0xFFFFF73A), &D4); // MOVE.W	$F73A,D4
  DEF_ROMLOC(6560) : ext_reg_32(&D4);            // EXT.L	D4
  DEF_ROMLOC(6562) : asl_toreg_32(0x6, &D4);     // ASL.L	#$06,D4
  DEF_ROMLOC(6564) : move_toreg_32(0x6, &D6);    // MOVEQ.L	$06,D6
  DEF_ROMLOC(6566) : scroll_bg_layer_3();        // BSR.W	$6BFC
  DEF_ROMLOC(656A)
      : move_toreg_16(read_16(0xFFFFF73A), &D4); // MOVE.W	$F73A,D4
  DEF_ROMLOC(656E) : ext_reg_32(&D4);            // EXT.L	D4
  DEF_ROMLOC(6570) : asl_toreg_32(0x7, &D4);     // ASL.L	#$07,D4
  DEF_ROMLOC(6572) : move_toreg_32(0x4, &D6);    // MOVEQ.L	$04,D6
  DEF_ROMLOC(6574) : scroll_bg_layer_2();        // BSR.W	$6BC8
  DEF_ROMLOC(6578) : move_toreg_16(0x200, &D0);  // MOVE.W	#$0200,D0
  DEF_ROMLOC(657C)
      : move_toreg_16(read_16(0xFFFFF704), &D1);    // MOVE.W	$F704,D1
  DEF_ROMLOC(6580) : sub_toreg_16(0x1C8, &D1);      // SUBI.W	#$01C8,D1
  DEF_ROMLOC(6584) : if (CCR_CS) goto rom_6590;     // BCS.B	$6590
  DEF_ROMLOC(6586) : move_toreg_16(D1, &D2);        // MOVE.W	D1,D2
  DEF_ROMLOC(6588) : add_toreg_16(D1, &D1);         // ADD.W	D1,D1
  DEF_ROMLOC(658A) : add_toreg_16(D2, &D1);         // ADD.W	D2,D1
  DEF_ROMLOC(658C) : asr_toreg_16(0x2, &D1);        // ASR.W	#$02,D1
  DEF_ROMLOC(658E) : add_toreg_16(D1, &D0);         // ADD.W	D1,D0
  DEF_ROMLOC(6590) : move_tomem_16(D0, 0xFFFFF714); // MOVE.W	D0,$F714
  DEF_ROMLOC(6594) : move_tomem_16(D0, 0xFFFFF71C); // MOVE.W	D0,$F71C
  DEF_ROMLOC(6598) : scroll_bg_y_absolute();        // BSR.W	$6B64
  DEF_ROMLOC(659C)
      : move_tomem_16(read_16(0xFFFFF70C),
                      0xFFFFF618); // MOVE.W	$F70C,$F618
  DEF_ROMLOC(65A2)
      : move_toreg_8(read_8(0xFFFFF756), &D0);            // MOVE.B	$F756,D0
  DEF_ROMLOC(65A6) : or_toreg_8(read_8(0xFFFFF758), &D0); // OR.B	$F758,D0
  DEF_ROMLOC(65AA) : or_tomem_8(D0, 0xFFFFF75A);          // OR.B	D0,$F75A
  DEF_ROMLOC(65AE) : clr_mem_8(0xFFFFF756);               // CLR.B	$F756
  DEF_ROMLOC(65B2) : clr_mem_8(0xFFFFF758);               // CLR.B	$F758
  DEF_ROMLOC(65B6) : move_toreg_32(0xFFFFA800, &A1);      // LEA.L	$A800,A1
  DEF_ROMLOC(65BA)
      : move_toreg_16(read_16(0xFFFFF700), &D2);           // MOVE.W	$F700,D2
  DEF_ROMLOC(65BE) : neg_reg_16(&D2);                      // NEG.W	D2
  DEF_ROMLOC(65C0) : move_toreg_16(D2, &D0);               // MOVE.W	D2,D0
  DEF_ROMLOC(65C2) : asr_toreg_16(0x2, &D0);               // ASR.W	#$02,D0
  DEF_ROMLOC(65C4) : sub_toreg_16(D2, &D0);                // SUB.W	D2,D0
  DEF_ROMLOC(65C6) : ext_reg_32(&D0);                      // EXT.L	D0
  DEF_ROMLOC(65C8) : asl_toreg_32(0x3, &D0);               // ASL.L	#$03,D0
  DEF_ROMLOC(65CA) : divs_toreg_16(0x5, &D0);              // DIVS.W	#$0005,D0
  DEF_ROMLOC(65CE) : ext_reg_32(&D0);                      // EXT.L	D0
  DEF_ROMLOC(65D0) : asl_toreg_32(0x4, &D0);               // ASL.L	#$04,D0
  DEF_ROMLOC(65D2) : asl_toreg_32(0x8, &D0);               // ASL.L	#$08,D0
  DEF_ROMLOC(65D4) : move_toreg_32(0x0, &D3);              // MOVEQ.L	$00,D3
  DEF_ROMLOC(65D6) : move_toreg_16(D2, &D3);               // MOVE.W	D2,D3
  DEF_ROMLOC(65D8) : asr_toreg_16(0x1, &D3);               // ASR.W	#$01,D3
  DEF_ROMLOC(65DA) : move_toreg_16(0x4, &D1);              // MOVE.W	#$0004,D1
  DEF_ROMLOC(65DE) : move_tomem_16(D3, (A1 += 2, A1 - 2)); // MOVE.W	D3,(A1)+
  DEF_ROMLOC(65E0) : swap_reg_16(&D3);                     // SWAP.W	D3
  DEF_ROMLOC(65E2) : add_toreg_32(D0, &D3);                // ADD.L	D0,D3
  DEF_ROMLOC(65E4) : swap_reg_16(&D3);                     // SWAP.W	D3
  DEF_ROMLOC(65E6) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_65DE; // DBF.W	D1,$65DE
  DEF_ROMLOC(65EA)
      : move_toreg_16(read_16(0xFFFFF718), &D0);           // MOVE.W	$F718,D0
  DEF_ROMLOC(65EE) : neg_reg_16(&D0);                      // NEG.W	D0
  DEF_ROMLOC(65F0) : move_toreg_16(0x1, &D1);              // MOVE.W	#$0001,D1
  DEF_ROMLOC(65F4) : move_tomem_16(D0, (A1 += 2, A1 - 2)); // MOVE.W	D0,(A1)+
  DEF_ROMLOC(65F6) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_65F4; // DBF.W	D1,$65F4
  DEF_ROMLOC(65FA)
      : move_toreg_16(read_16(0xFFFFF710), &D0);           // MOVE.W	$F710,D0
  DEF_ROMLOC(65FE) : neg_reg_16(&D0);                      // NEG.W	D0
  DEF_ROMLOC(6600) : move_toreg_16(0x8, &D1);              // MOVE.W	#$0008,D1
  DEF_ROMLOC(6604) : move_tomem_16(D0, (A1 += 2, A1 - 2)); // MOVE.W	D0,(A1)+
  DEF_ROMLOC(6606) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_6604; // DBF.W	D1,$6604
  DEF_ROMLOC(660A)
      : move_toreg_16(read_16(0xFFFFF708), &D0);           // MOVE.W	$F708,D0
  DEF_ROMLOC(660E) : neg_reg_16(&D0);                      // NEG.W	D0
  DEF_ROMLOC(6610) : move_toreg_16(0xF, &D1);              // MOVE.W	#$000F,D1
  DEF_ROMLOC(6614) : move_tomem_16(D0, (A1 += 2, A1 - 2)); // MOVE.W	D0,(A1)+
  DEF_ROMLOC(6616) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_6614;                                   // DBF.W	D1,$6614
  DEF_ROMLOC(661A) : move_toreg_32(0xFFFFA800, &A2); // LEA.L	$A800,A2
  DEF_ROMLOC(661E)
      : move_toreg_16(read_16(0xFFFFF70C), &D0); // MOVE.W	$F70C,D0
  DEF_ROMLOC(6622) : sub_toreg_16(0x200, &D0);   // SUBI.W	#$0200,D0
  DEF_ROMLOC(6626) : move_toreg_16(D0, &D2);     // MOVE.W	D0,D2
  DEF_ROMLOC(6628) : cmp_toreg_16(0x100, &D0);   // CMPI.W	#$0100,D0
  DEF_ROMLOC(662C) : if (CCR_CS) goto rom_6632;  // BCS.B	$6632
  DEF_ROMLOC(662E) : move_toreg_16(0x100, &D0);  // MOVE.W	#$0100,D0
  DEF_ROMLOC(6632) : and_toreg_16(0x1F0, &D0);   // ANDI.W	#$01F0,D0
  DEF_ROMLOC(6636) : lsr_toreg_16(0x3, &D0);     // LSR.W	#$03,D0
  DEF_ROMLOC(6638)
      : move_toreg_32((s32)A2 + (s8)0x0 + (s16)D0,
                      &A2); // LEA.L	0(A2,D0),A2
  rom_66CC();               // BRA.W	$66CC
}
ROMFUNC(rom_6640) {
  DEF_ROMLOC(6640)
      : move_toreg_16(read_16(0xFFFFF73C), &D5); // MOVE.W	$F73C,D5
  DEF_ROMLOC(6644) : ext_reg_32(&D5);            // EXT.L	D5
  DEF_ROMLOC(6646) : asl_toreg_32(0x7, &D5);     // ASL.L	#$07,D5
  DEF_ROMLOC(6648) : scroll_bg_y();              // BSR.W	$6B2E
  DEF_ROMLOC(664C)
      : move_tomem_16(read_16(0xFFFFF70C),
                      0xFFFFF618);                   // MOVE.W	$F70C,$F618
  DEF_ROMLOC(6652) : move_toreg_32(0xFFFFA800, &A1); // LEA.L	$A800,A1
  DEF_ROMLOC(6656)
      : move_toreg_16(read_16(0xFFFFF700), &D2);           // MOVE.W	$F700,D2
  DEF_ROMLOC(665A) : neg_reg_16(&D2);                      // NEG.W	D2
  DEF_ROMLOC(665C) : move_toreg_16(D2, &D0);               // MOVE.W	D2,D0
  DEF_ROMLOC(665E) : asr_toreg_16(0x3, &D0);               // ASR.W	#$03,D0
  DEF_ROMLOC(6660) : sub_toreg_16(D2, &D0);                // SUB.W	D2,D0
  DEF_ROMLOC(6662) : ext_reg_32(&D0);                      // EXT.L	D0
  DEF_ROMLOC(6664) : asl_toreg_32(0x4, &D0);               // ASL.L	#$04,D0
  DEF_ROMLOC(6666) : divs_toreg_16(0x1C, &D0);             // DIVS.W	#$001C,D0
  DEF_ROMLOC(666A) : ext_reg_32(&D0);                      // EXT.L	D0
  DEF_ROMLOC(666C) : asl_toreg_32(0x4, &D0);               // ASL.L	#$04,D0
  DEF_ROMLOC(666E) : asl_toreg_32(0x8, &D0);               // ASL.L	#$08,D0
  DEF_ROMLOC(6670) : move_toreg_32(0x0, &D3);              // MOVEQ.L	$00,D3
  DEF_ROMLOC(6672) : move_toreg_16(D2, &D3);               // MOVE.W	D2,D3
  DEF_ROMLOC(6674) : move_toreg_16(0x1B, &D1);             // MOVE.W	#$001B,D1
  DEF_ROMLOC(6678) : move_tomem_16(D3, (A1 += 2, A1 - 2)); // MOVE.W	D3,(A1)+
  DEF_ROMLOC(667A) : swap_reg_16(&D3);                     // SWAP.W	D3
  DEF_ROMLOC(667C) : add_toreg_32(D0, &D3);                // ADD.L	D0,D3
  DEF_ROMLOC(667E) : swap_reg_16(&D3);                     // SWAP.W	D3
  DEF_ROMLOC(6680) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_6678;                                         // DBF.W	D1,$6678
  DEF_ROMLOC(6684) : move_toreg_16(D2, &D0);               // MOVE.W	D2,D0
  DEF_ROMLOC(6686) : asr_toreg_16(0x3, &D0);               // ASR.W	#$03,D0
  DEF_ROMLOC(6688) : move_toreg_16(D0, &D1);               // MOVE.W	D0,D1
  DEF_ROMLOC(668A) : asr_toreg_16(0x1, &D1);               // ASR.W	#$01,D1
  DEF_ROMLOC(668C) : add_toreg_16(D1, &D0);                // ADD.W	D1,D0
  DEF_ROMLOC(668E) : move_toreg_16(0x4, &D1);              // MOVE.W	#$0004,D1
  DEF_ROMLOC(6692) : move_tomem_16(D0, (A1 += 2, A1 - 2)); // MOVE.W	D0,(A1)+
  DEF_ROMLOC(6694) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_6692;                                         // DBF.W	D1,$6692
  DEF_ROMLOC(6698) : move_toreg_16(D2, &D0);               // MOVE.W	D2,D0
  DEF_ROMLOC(669A) : asr_toreg_16(0x2, &D0);               // ASR.W	#$02,D0
  DEF_ROMLOC(669C) : move_toreg_16(0x4, &D1);              // MOVE.W	#$0004,D1
  DEF_ROMLOC(66A0) : move_tomem_16(D0, (A1 += 2, A1 - 2)); // MOVE.W	D0,(A1)+
  DEF_ROMLOC(66A2) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_66A0;                                         // DBF.W	D1,$66A0
  DEF_ROMLOC(66A6) : move_toreg_16(D2, &D0);               // MOVE.W	D2,D0
  DEF_ROMLOC(66A8) : asr_toreg_16(0x1, &D0);               // ASR.W	#$01,D0
  DEF_ROMLOC(66AA) : move_toreg_16(0x1D, &D1);             // MOVE.W	#$001D,D1
  DEF_ROMLOC(66AE) : move_tomem_16(D0, (A1 += 2, A1 - 2)); // MOVE.W	D0,(A1)+
  DEF_ROMLOC(66B0) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_66AE;                                   // DBF.W	D1,$66AE
  DEF_ROMLOC(66B4) : move_toreg_32(0xFFFFA800, &A2); // LEA.L	$A800,A2
  DEF_ROMLOC(66B8)
      : move_toreg_16(read_16(0xFFFFF70C), &D0); // MOVE.W	$F70C,D0
  DEF_ROMLOC(66BC) : move_toreg_16(D0, &D2);     // MOVE.W	D0,D2
  DEF_ROMLOC(66BE) : sub_toreg_16(0xC0, &D0);    // SUBI.W	#$00C0,D0
  DEF_ROMLOC(66C2) : and_toreg_16(0x3F0, &D0);   // ANDI.W	#$03F0,D0
  DEF_ROMLOC(66C6) : lsr_toreg_16(0x3, &D0);     // LSR.W	#$03,D0
  DEF_ROMLOC(66C8)
      : move_toreg_32((s32)A2 + (s8)0x0 + (s16)D0,
                      &A2); // LEA.L	0(A2,D0),A2
  rom_66CC();               // Detected flow into next function
}
ROMFUNC(rom_66CC) {
  u8 switchindex = 0;
  DEF_ROMLOC(66CC) : move_toreg_32(0xFFFFCC00, &A1); // LEA.L	$CC00,A1
  DEF_ROMLOC(66D0) : move_toreg_16(0xE, &D1);        // MOVE.W	#$000E,D1
  DEF_ROMLOC(66D4)
      : move_toreg_16(read_16(0xFFFFF700), &D0); // MOVE.W	$F700,D0
  DEF_ROMLOC(66D8) : neg_reg_16(&D0);            // NEG.W	D0
  DEF_ROMLOC(66DA) : swap_reg_16(&D0);           // SWAP.W	D0
  DEF_ROMLOC(66DC) : and_toreg_16(0xF, &D2);
  switchindex = D2;                         // ANDI.W	#$000F,D2
  DEF_ROMLOC(66E0) : add_toreg_16(D2, &D2); // ADD.W	D2,D2
  DEF_ROMLOC(66E2)
      : move_toreg_16(read_16((A2 += 2, A2 - 2)), &D0); // MOVE.W	(A2)+,D0
  // DEF_ROMLOC(66E4): goto rom_66EA + (s16)(D2 & 0xffff); // JMP	4(PC,D2)
  DEF_ROMLOC(66E4) : switch (switchindex) {
  case 0:
    goto rom_66EA;
    break;
  case 1:
    goto rom_66EC;
    break;
  case 2:
    goto rom_66EE;
    break;
  case 3:
    goto rom_66F0;
    break;
  case 4:
    goto rom_66F2;
    break;
  case 5:
    goto rom_66F4;
    break;
  case 6:
    goto rom_66F6;
    break;
  case 7:
    goto rom_66F8;
    break;
  case 8:
    goto rom_66FA;
    break;
  case 9:
    goto rom_66FC;
    break;
  case 10:
    goto rom_66FE;
    break;
  case 11:
    goto rom_6700;
    break;
  case 12:
    goto rom_6702;
    break;
  case 13:
    goto rom_6704;
    break;
  case 14:
    goto rom_6706;
    break;
  case 15:
    goto rom_6708;
    break;
  }
  DEF_ROMLOC(66E8)
      : move_toreg_16(read_16((A2 += 2, A2 - 2)), &D0);    // MOVE.W	(A2)+,D0
  DEF_ROMLOC(66EA) : move_tomem_32(D0, (A1 += 4, A1 - 4)); // MOVE.L	D0,(A1)+
  DEF_ROMLOC(66EC) : move_tomem_32(D0, (A1 += 4, A1 - 4)); // MOVE.L	D0,(A1)+
  DEF_ROMLOC(66EE) : move_tomem_32(D0, (A1 += 4, A1 - 4)); // MOVE.L	D0,(A1)+
  DEF_ROMLOC(66F0) : move_tomem_32(D0, (A1 += 4, A1 - 4)); // MOVE.L	D0,(A1)+
  DEF_ROMLOC(66F2) : move_tomem_32(D0, (A1 += 4, A1 - 4)); // MOVE.L	D0,(A1)+
  DEF_ROMLOC(66F4) : move_tomem_32(D0, (A1 += 4, A1 - 4)); // MOVE.L	D0,(A1)+
  DEF_ROMLOC(66F6) : move_tomem_32(D0, (A1 += 4, A1 - 4)); // MOVE.L	D0,(A1)+
  DEF_ROMLOC(66F8) : move_tomem_32(D0, (A1 += 4, A1 - 4)); // MOVE.L	D0,(A1)+
  DEF_ROMLOC(66FA) : move_tomem_32(D0, (A1 += 4, A1 - 4)); // MOVE.L	D0,(A1)+
  DEF_ROMLOC(66FC) : move_tomem_32(D0, (A1 += 4, A1 - 4)); // MOVE.L	D0,(A1)+
  DEF_ROMLOC(66FE) : move_tomem_32(D0, (A1 += 4, A1 - 4)); // MOVE.L	D0,(A1)+
  DEF_ROMLOC(6700) : move_tomem_32(D0, (A1 += 4, A1 - 4)); // MOVE.L	D0,(A1)+
  DEF_ROMLOC(6702) : move_tomem_32(D0, (A1 += 4, A1 - 4)); // MOVE.L	D0,(A1)+
  DEF_ROMLOC(6704) : move_tomem_32(D0, (A1 += 4, A1 - 4)); // MOVE.L	D0,(A1)+
  DEF_ROMLOC(6706) : move_tomem_32(D0, (A1 += 4, A1 - 4)); // MOVE.L	D0,(A1)+
  DEF_ROMLOC(6708) : move_tomem_32(D0, (A1 += 4, A1 - 4)); // MOVE.L	D0,(A1)+
  DEF_ROMLOC(670A) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_66E8;           // DBF.W	D1,$66E8
  DEF_ROMLOC(670E) : return; // RTS
}