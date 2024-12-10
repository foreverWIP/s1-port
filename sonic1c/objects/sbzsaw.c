/*ROMFUNC(rom_160E4) {
	DEF_ROMLOC(160E4): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(160E6): move_toreg_8(read_8(A0 + 0x24), &D0); // MOVE.B	36(A0),D0
	DEF_ROMLOC(160EA): move_toreg_16(read_16(0x160F2 + (s16)(D0 & 0xffff)), &D1); // MOVE.W	6(PC,D0),D1
	DEF_ROMLOC(160EE): goto rom_160F2 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
	DEF_ROMLOC(160F2): or_toreg_8(0x42, &D4); // ORI.B	#$42,D4
	rom_160F6(); // Detected flow into next function
}*/
/*ROMFUNC(rom_160F6) {
	DEF_ROMLOC(160F6): add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
	DEF_ROMLOC(160FA): move_tomem_32(0x16300, A0 + 0x4); // MOVE.L	#$00016300,4(A0)
	DEF_ROMLOC(16102): move_tomem_16(0x43B5, A0 + 0x2); // MOVE.W	#$43B5,2(A0)
	DEF_ROMLOC(16108): move_tomem_8(0x4, A0 + 0x1); // MOVE.B	#$04,1(A0)
	DEF_ROMLOC(1610E): move_tomem_8(0x4, A0 + 0x18); // MOVE.B	#$04,24(A0)
	DEF_ROMLOC(16114): move_tomem_8(0x20, A0 + 0x19); // MOVE.B	#$20,25(A0)
	DEF_ROMLOC(1611A): move_tomem_16(read_16(A0 + 0x8), A0 + 0x3A); // MOVE.W	8(A0),58(A0)
	DEF_ROMLOC(16120): move_tomem_16(read_16(A0 + 0xC), A0 + 0x38); // MOVE.W	12(A0),56(A0)
	DEF_ROMLOC(16126): cmp_tomem_8(0x3, A0 + 0x28); // CMPI.B	#$03,40(A0)
	DEF_ROMLOC(1612C): if (CCR_CC) goto rom_16134; // BCC.B	$16134
	DEF_ROMLOC(1612E): move_tomem_8(0xFFFFFFA2, A0 + 0x20); // MOVE.B	#$A2,32(A0)
	rom_16134(); // Detected flow into next function
}*/
/*ROMFUNC(rom_16134) {
	DEF_ROMLOC(16134): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(16136): move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B	40(A0),D0
	DEF_ROMLOC(1613A): and_toreg_16(0x7, &D0); // ANDI.W	#$0007,D0
	DEF_ROMLOC(1613E): add_toreg_16(D0, &D0); // ADD.W	D0,D0
	DEF_ROMLOC(16140): move_toreg_16(read_16(0x16170 + (s16)(D0 & 0xffff)), &D1); // MOVE.W	46(PC,D0),D1
	DEF_ROMLOC(16144): rom_16170 + (s16)(D1 & 0xffff)(); // JSR	42(PC,D1)
	DEF_ROMLOC(16148): move_toreg_16(read_16(A0 + 0x3A), &D0); // MOVE.W	58(A0),D0
	DEF_ROMLOC(1614C): and_toreg_16(0xFFFFFF80, &D0); // ANDI.W	#$FF80,D0
	DEF_ROMLOC(16150): move_toreg_16(read_16(0xFFFFF700), &D1); // MOVE.W	$F700,D1
	DEF_ROMLOC(16154): sub_toreg_16(0x80, &D1); // SUBI.W	#$0080,D1
	DEF_ROMLOC(16158): and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
	DEF_ROMLOC(1615C): sub_toreg_16(D1, &D0); // SUB.W	D1,D0
	DEF_ROMLOC(1615E): cmp_toreg_16(0x280, &D0); // CMPI.W	#$0280,D0
	DEF_ROMLOC(16162): if (CCR_HI) goto rom_1616A; // BHI.B	$1616A
	DEF_ROMLOC(16164): goto rom_DC92; // JMP	$0000DC92
	DEF_ROMLOC(1616A): goto rom_DCCE; // JMP	$0000DCCE
}*/