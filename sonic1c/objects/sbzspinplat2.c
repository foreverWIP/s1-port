/*ROMFUNC(rom_15E98) {
	DEF_ROMLOC(15E98): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(15E9A): move_toreg_8(read_8(A0 + 0x24), &D0); // MOVE.B	36(A0),D0
	DEF_ROMLOC(15E9E): move_toreg_16(read_16(0x15EA6 + (s16)(D0 & 0xffff)), &D1); // MOVE.W	6(PC,D0),D1
	DEF_ROMLOC(15EA2): goto rom_15EA6 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
	DEF_ROMLOC(15EA6): or_toreg_8(0xFFFFFF84, &D6); // ORI.B	#$84,D6
	rom_15EAC(); // Detected flow into next function
}*/
/*ROMFUNC(rom_15EAC) {
	DEF_ROMLOC(15EAC): add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
	DEF_ROMLOC(15EB0): move_tomem_32(0x16048, A0 + 0x4); // MOVE.L	#$00016048,4(A0)
	DEF_ROMLOC(15EB8): move_tomem_16(0x4492, A0 + 0x2); // MOVE.W	#$4492,2(A0)
	DEF_ROMLOC(15EBE): or_tomem_8(0x4, A0 + 0x1); // ORI.B	#$04,1(A0)
	DEF_ROMLOC(15EC4): move_tomem_8(0xFFFFFF80, A0 + 0x19); // MOVE.B	#$80,25(A0)
	DEF_ROMLOC(15ECA): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(15ECC): move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B	40(A0),D0
	DEF_ROMLOC(15ED0): and_toreg_16(0xF, &D0); // ANDI.W	#$000F,D0
	DEF_ROMLOC(15ED4): mulu_toreg_16(0x3C, &D0); // MULU.W	#$003C,D0
	DEF_ROMLOC(15ED8): move_tomem_16(D0, A0 + 0x32); // MOVE.W	D0,50(A0)
	DEF_ROMLOC(15EDC): tst_mem_8(A0 + 0x28); // TST.B	40(A0)
	DEF_ROMLOC(15EE0): if (CCR_PL) goto rom_15F2A; // BPL.B	$15F2A
	DEF_ROMLOC(15EE2): add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
	DEF_ROMLOC(15EE6): move_tomem_32(0x160A2, A0 + 0x4); // MOVE.L	#$000160A2,4(A0)
	DEF_ROMLOC(15EEE): move_tomem_16(0x4DF, A0 + 0x2); // MOVE.W	#$04DF,2(A0)
	DEF_ROMLOC(15EF4): move_tomem_8(0x10, A0 + 0x19); // MOVE.B	#$10,25(A0)
	DEF_ROMLOC(15EFA): move_tomem_8(0x2, A0 + 0x1C); // MOVE.B	#$02,28(A0)
	DEF_ROMLOC(15F00): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(15F02): move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B	40(A0),D0
	DEF_ROMLOC(15F06): move_toreg_16(D0, &D1); // MOVE.W	D0,D1
	DEF_ROMLOC(15F08): and_toreg_16(0xF, &D0); // ANDI.W	#$000F,D0
	DEF_ROMLOC(15F0C): mulu_toreg_16(0x6, &D0); // MULU.W	#$0006,D0
	DEF_ROMLOC(15F10): move_tomem_16(D0, A0 + 0x30); // MOVE.W	D0,48(A0)
	DEF_ROMLOC(15F14): move_tomem_16(D0, A0 + 0x32); // MOVE.W	D0,50(A0)
	DEF_ROMLOC(15F18): and_toreg_16(0x70, &D1); // ANDI.W	#$0070,D1
	DEF_ROMLOC(15F1C): add_toreg_16(0x10, &D1); // ADDI.W	#$0010,D1
	DEF_ROMLOC(15F20): lsl_toreg_16(0x2, &D1); // LSL.W	#$02,D1
	DEF_ROMLOC(15F22): sub_toreg_16(0x1, &D1); // SUBQ.W	#$01,D1
	DEF_ROMLOC(15F24): move_tomem_16(D1, A0 + 0x36); // MOVE.W	D1,54(A0)
	rom_15F96(); // BRA.B	$15F96
}*/
/*ROMFUNC(rom_15F2A) {
	DEF_ROMLOC(15F2A): sub_tomem_16(0x1, A0 + 0x30); // SUBQ.W	#$01,48(A0)
	DEF_ROMLOC(15F2E): if (CCR_PL) goto rom_15F4C; // BPL.B	$15F4C
	DEF_ROMLOC(15F30): move_tomem_16(read_16(A0 + 0x32), A0 + 0x30); // MOVE.W	50(A0),48(A0)
	DEF_ROMLOC(15F36): bchg_tomem_8(0x0, A0 + 0x1C); // BCHG.B	#$00,28(A0)
	DEF_ROMLOC(15F3C): tst_mem_8(A0 + 0x1); // TST.B	1(A0)
	DEF_ROMLOC(15F40): if (CCR_PL) goto rom_15F4C; // BPL.B	$15F4C
	DEF_ROMLOC(15F42): move_toreg_16(0xBB, &D0); // MOVE.W	#$00BB,D0
	DEF_ROMLOC(15F46): rom_1394(); // JSR	$00001394
	DEF_ROMLOC(15F4C): move_toreg_32(0x1600C, &A1); // LEA.L	$0001600C,A1
	DEF_ROMLOC(15F52): rom_ADA2(); // JSR	$0000ADA2
	DEF_ROMLOC(15F58): tst_mem_8(A0 + 0x1A); // TST.B	26(A0)
	DEF_ROMLOC(15F5C): if (!CCR_EQ) goto rom_15F76; // BNE.B	$15F76
	DEF_ROMLOC(15F5E): move_toreg_16(0x4B, &D1); // MOVE.W	#$004B,D1
	DEF_ROMLOC(15F62): move_toreg_16(0xC, &D2); // MOVE.W	#$000C,D2
	DEF_ROMLOC(15F66): move_toreg_16(D2, &D3); // MOVE.W	D2,D3
	DEF_ROMLOC(15F68): add_toreg_16(0x1, &D3); // ADDQ.W	#$01,D3
	DEF_ROMLOC(15F6A): move_toreg_16(read_16(A0 + 0x8), &D4); // MOVE.W	8(A0),D4
	DEF_ROMLOC(15F6E): rom_10062(); // BSR.W	$10062
	DEF_ROMLOC(15F72): goto rom_FD38; // BRA.W	$FD38
	DEF_ROMLOC(15F76): btst_tomem_8(0x3, A0 + 0x22); // BTST.B	#$03,34(A0)
	DEF_ROMLOC(15F7C): if (CCR_EQ) goto rom_15F92; // BEQ.B	$15F92
	DEF_ROMLOC(15F7E): move_toreg_32(0xFFFFD000, &A1); // LEA.L	$D000,A1
	DEF_ROMLOC(15F82): bclr_tomem_8(0x3, A1 + 0x22); // BCLR.B	#$03,34(A1)
	DEF_ROMLOC(15F88): bclr_tomem_8(0x3, A0 + 0x22); // BCLR.B	#$03,34(A0)
	DEF_ROMLOC(15F8E): clr_mem_8(A0 + 0x25); // CLR.B	37(A0)
	rom_FD38(); // BRA.W	$FD38
}*/
/*ROMFUNC(rom_15F96) {
	DEF_ROMLOC(15F96): move_toreg_16(read_16(0xFFFFFE04), &D0); // MOVE.W	$FE04,D0
	DEF_ROMLOC(15F9A): and_toreg_16(read_16(A0 + 0x36), &D0); // AND.W	54(A0),D0
	DEF_ROMLOC(15F9E): if (!CCR_EQ) goto rom_15FA6; // BNE.B	$15FA6
	DEF_ROMLOC(15FA0): move_tomem_8(0x1, A0 + 0x34); // MOVE.B	#$01,52(A0)
	DEF_ROMLOC(15FA6): tst_mem_8(A0 + 0x34); // TST.B	52(A0)
	DEF_ROMLOC(15FAA): if (CCR_EQ) goto rom_15FC2; // BEQ.B	$15FC2
	DEF_ROMLOC(15FAC): sub_tomem_16(0x1, A0 + 0x30); // SUBQ.W	#$01,48(A0)
	DEF_ROMLOC(15FB0): if (CCR_PL) goto rom_15FC2; // BPL.B	$15FC2
	DEF_ROMLOC(15FB2): move_tomem_16(read_16(A0 + 0x32), A0 + 0x30); // MOVE.W	50(A0),48(A0)
	DEF_ROMLOC(15FB8): clr_mem_8(A0 + 0x34); // CLR.B	52(A0)
	DEF_ROMLOC(15FBC): bchg_tomem_8(0x0, A0 + 0x1C); // BCHG.B	#$00,28(A0)
	DEF_ROMLOC(15FC2): move_toreg_32(0x1600C, &A1); // LEA.L	$0001600C,A1
	DEF_ROMLOC(15FC8): rom_ADA2(); // JSR	$0000ADA2
	DEF_ROMLOC(15FCE): tst_mem_8(A0 + 0x1A); // TST.B	26(A0)
	DEF_ROMLOC(15FD2): if (!CCR_EQ) goto rom_15FEC; // BNE.B	$15FEC
	DEF_ROMLOC(15FD4): move_toreg_16(0x1B, &D1); // MOVE.W	#$001B,D1
	DEF_ROMLOC(15FD8): move_toreg_16(0x7, &D2); // MOVE.W	#$0007,D2
	DEF_ROMLOC(15FDC): move_toreg_16(D2, &D3); // MOVE.W	D2,D3
	DEF_ROMLOC(15FDE): add_toreg_16(0x1, &D3); // ADDQ.W	#$01,D3
	DEF_ROMLOC(15FE0): move_toreg_16(read_16(A0 + 0x8), &D4); // MOVE.W	8(A0),D4
	DEF_ROMLOC(15FE4): rom_10062(); // BSR.W	$10062
	DEF_ROMLOC(15FE8): goto rom_FD38; // BRA.W	$FD38
	DEF_ROMLOC(15FEC): btst_tomem_8(0x3, A0 + 0x22); // BTST.B	#$03,34(A0)
	DEF_ROMLOC(15FF2): if (CCR_EQ) goto rom_16008; // BEQ.B	$16008
	DEF_ROMLOC(15FF4): move_toreg_32(0xFFFFD000, &A1); // LEA.L	$D000,A1
	DEF_ROMLOC(15FF8): bclr_tomem_8(0x3, A1 + 0x22); // BCLR.B	#$03,34(A1)
	DEF_ROMLOC(15FFE): bclr_tomem_8(0x3, A0 + 0x22); // BCLR.B	#$03,34(A0)
	DEF_ROMLOC(16004): clr_mem_8(A0 + 0x25); // CLR.B	37(A0)
	rom_FD38(); // BRA.W	$FD38
}*/