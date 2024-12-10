/*ROMFUNC(rom_16760) {
	DEF_ROMLOC(16760): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(16762): move_toreg_8(read_8(A0 + 0x24), &D0); // MOVE.B	36(A0),D0
	DEF_ROMLOC(16766): move_toreg_16(read_16(0x1676E + (s16)(D0 & 0xffff)), &D1); // MOVE.W	6(PC,D0),D1
	DEF_ROMLOC(1676A): goto rom_1676E + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
}*/
/*ROMFUNC(rom_16776) {
	DEF_ROMLOC(16776): add_tomem_8(0x6, A0 + 0x24); // ADDQ.B	#$06,36(A0)
	DEF_ROMLOC(1677A): move_tomem_32(0x16892, A0 + 0x4); // MOVE.L	#$00016892,4(A0)
	DEF_ROMLOC(16782): move_tomem_16(0x44C3, A0 + 0x2); // MOVE.W	#$44C3,2(A0)
	DEF_ROMLOC(16788): or_tomem_8(0x4, A0 + 0x1); // ORI.B	#$04,1(A0)
	DEF_ROMLOC(1678E): move_tomem_8(0x10, A0 + 0x19); // MOVE.B	#$10,25(A0)
	DEF_ROMLOC(16794): move_tomem_8(0x4, A0 + 0x18); // MOVE.B	#$04,24(A0)
	DEF_ROMLOC(1679A): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(1679C): move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B	40(A0),D0
	DEF_ROMLOC(167A0): and_toreg_16(0xF, &D0); // ANDI.W	#$000F,D0
	DEF_ROMLOC(167A4): add_toreg_16(0x1, &D0); // ADDQ.W	#$01,D0
	DEF_ROMLOC(167A6): lsl_toreg_16(0x7, &D0); // LSL.W	#$07,D0
	DEF_ROMLOC(167A8): move_toreg_16(D0, &D1); // MOVE.W	D0,D1
	DEF_ROMLOC(167AA): sub_toreg_16(0x1, &D0); // SUBQ.W	#$01,D0
	DEF_ROMLOC(167AC): move_tomem_16(D0, A0 + 0x30); // MOVE.W	D0,48(A0)
	DEF_ROMLOC(167B0): move_tomem_16(D0, A0 + 0x32); // MOVE.W	D0,50(A0)
	DEF_ROMLOC(167B4): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(167B6): move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B	40(A0),D0
	DEF_ROMLOC(167BA): and_toreg_16(0xF0, &D0); // ANDI.W	#$00F0,D0
	DEF_ROMLOC(167BE): add_toreg_16(0x80, &D1); // ADDI.W	#$0080,D1
	DEF_ROMLOC(167C2): mulu_toreg_16(D1, &D0); // MULU.W	D1,D0
	DEF_ROMLOC(167C4): lsr_toreg_32(0x8, &D0); // LSR.L	#$08,D0
	DEF_ROMLOC(167C6): move_tomem_16(D0, A0 + 0x36); // MOVE.W	D0,54(A0)
	DEF_ROMLOC(167CA): sub_toreg_16(0x1, &D1); // SUBQ.W	#$01,D1
	DEF_ROMLOC(167CC): move_tomem_16(D1, A0 + 0x38); // MOVE.W	D1,56(A0)
	rom_167D0(); // Detected flow into next function
}*/
/*ROMFUNC(rom_167D0) {
	DEF_ROMLOC(167D0): move_toreg_16(read_16(0xFFFFFE04), &D0); // MOVE.W	$FE04,D0
	DEF_ROMLOC(167D4): sub_toreg_16(read_16(A0 + 0x36), &D0); // SUB.W	54(A0),D0
	DEF_ROMLOC(167D8): and_toreg_16(read_16(A0 + 0x38), &D0); // AND.W	56(A0),D0
	DEF_ROMLOC(167DC): if (!CCR_EQ) goto rom_167E4; // BNE.B	$167E4
	DEF_ROMLOC(167DE): sub_tomem_8(0x4, A0 + 0x24); // SUBQ.B	#$04,36(A0)
	DEF_ROMLOC(167E2): goto rom_167F4; // BRA.B	$167F4
	DEF_ROMLOC(167E4): move_toreg_32(0x1687E, &A1); // LEA.L	$0001687E,A1
	DEF_ROMLOC(167EA): rom_ADA2(); // JSR	$0000ADA2
	rom_FD38(); // BRA.W	$FD38
}*/
/*ROMFUNC(rom_167F4) {
	DEF_ROMLOC(167F4): sub_tomem_16(0x1, A0 + 0x30); // SUBQ.W	#$01,48(A0)
	DEF_ROMLOC(167F8): if (CCR_PL) goto rom_16812; // BPL.B	$16812
	DEF_ROMLOC(167FA): move_tomem_16(0x7F, A0 + 0x30); // MOVE.W	#$007F,48(A0)
	DEF_ROMLOC(16800): tst_mem_8(A0 + 0x1C); // TST.B	28(A0)
	DEF_ROMLOC(16804): if (CCR_EQ) goto rom_1680C; // BEQ.B	$1680C
	DEF_ROMLOC(16806): move_tomem_16(read_16(A0 + 0x32), A0 + 0x30); // MOVE.W	50(A0),48(A0)
	DEF_ROMLOC(1680C): bchg_tomem_8(0x0, A0 + 0x1C); // BCHG.B	#$00,28(A0)
	DEF_ROMLOC(16812): move_toreg_32(0x1687E, &A1); // LEA.L	$0001687E,A1
	DEF_ROMLOC(16818): rom_ADA2(); // JSR	$0000ADA2
	DEF_ROMLOC(1681E): btst_tomem_8(0x1, A0 + 0x1A); // BTST.B	#$01,26(A0)
	DEF_ROMLOC(16824): if (!CCR_EQ) goto rom_16858; // BNE.B	$16858
	DEF_ROMLOC(16826): cmp_tomem_8(0x2, A0 + 0x24); // CMPI.B	#$02,36(A0)
	DEF_ROMLOC(1682C): if (!CCR_EQ) goto rom_1683E; // BNE.B	$1683E
	DEF_ROMLOC(1682E): move_toreg_32(0x0, &D1); // MOVEQ.L	$00,D1
	DEF_ROMLOC(16830): move_toreg_8(read_8(A0 + 0x19), &D1); // MOVE.B	25(A0),D1
	DEF_ROMLOC(16834): rom_7ACA(); // JSR	$00007ACA
	DEF_ROMLOC(1683A): goto rom_FD38; // BRA.W	$FD38
	DEF_ROMLOC(1683E): move_toreg_32(0x0, &D1); // MOVEQ.L	$00,D1
	DEF_ROMLOC(16840): move_toreg_8(read_8(A0 + 0x19), &D1); // MOVE.B	25(A0),D1
	DEF_ROMLOC(16844): rom_7C3E(); // JSR	$00007C3E
	DEF_ROMLOC(1684A): move_toreg_16(read_16(A0 + 0x8), &D2); // MOVE.W	8(A0),D2
	DEF_ROMLOC(1684E): rom_81AC(); // JSR	$000081AC
	DEF_ROMLOC(16854): goto rom_FD38; // BRA.W	$FD38
	DEF_ROMLOC(16858): btst_tomem_8(0x3, A0 + 0x22); // BTST.B	#$03,34(A0)
	DEF_ROMLOC(1685E): if (CCR_EQ) goto rom_1687A; // BEQ.B	$1687A
	DEF_ROMLOC(16860): move_toreg_32(0xFFFFD000, &A1); // LEA.L	$D000,A1
	DEF_ROMLOC(16864): bclr_tomem_8(0x3, A1 + 0x22); // BCLR.B	#$03,34(A1)
	DEF_ROMLOC(1686A): bclr_tomem_8(0x3, A0 + 0x22); // BCLR.B	#$03,34(A0)
	DEF_ROMLOC(16870): move_tomem_8(0x2, A0 + 0x24); // MOVE.B	#$02,36(A0)
	DEF_ROMLOC(16876): clr_mem_8(A0 + 0x25); // CLR.B	37(A0)
	DEF_ROMLOC(1687A): goto rom_FD38; // BRA.W	$FD38
	DEF_ROMLOC(1687E): or_toreg_8(0xC, &D4); // ORI.B	#$0C,D4
	DEF_ROMLOC(16882): btst_toreg_32(D3, &D0); // BTST.L	D3,D0
	DEF_ROMLOC(16884): btst_toreg_32(D0, &D2); // BTST.L	D0,D2
	rom_168AE(); // Detected flow into next function
}*/