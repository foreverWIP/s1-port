/*ROMFUNC(rom_11718) {
	DEF_ROMLOC(11718): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(1171A): move_toreg_8(read_8(A0 + 0x24), &D0); // MOVE.B	36(A0),D0
	DEF_ROMLOC(1171E): move_toreg_16(read_16(0x11726 + (s16)(D0 & 0xffff)), &D1); // MOVE.W	6(PC,D0),D1
	DEF_ROMLOC(11722): goto rom_11726 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
	DEF_ROMLOC(11726): or_toreg_8(0x1C, &D4); // ORI.B	#$1C,D4
	rom_1172A(); // Detected flow into next function
}*/
/*ROMFUNC(rom_1172A) {
	DEF_ROMLOC(1172A): add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
	DEF_ROMLOC(1172E): move_tomem_32(0x1176A, A0 + 0x4); // MOVE.L	#$0001176A,4(A0)
	DEF_ROMLOC(11736): move_tomem_16(0xFFFF83CC, A0 + 0x2); // MOVE.W	#$83CC,2(A0)
	DEF_ROMLOC(1173C): move_tomem_8(0x10, A0 + 0x19); // MOVE.B	#$10,25(A0)
	rom_11742(); // Detected flow into next function
}*/
/*ROMFUNC(rom_11742) {
	DEF_ROMLOC(11742): move_toreg_32(read_32(0xFFFFF700), &D1); // MOVE.L	$F700,D1
	DEF_ROMLOC(11746): add_toreg_32(D1, &D1); // ADD.L	D1,D1
	DEF_ROMLOC(11748): swap_reg_16(&D1); // SWAP.W	D1
	DEF_ROMLOC(1174A): neg_reg_16(&D1); // NEG.W	D1
	DEF_ROMLOC(1174C): move_tomem_16(D1, A0 + 0x8); // MOVE.W	D1,8(A0)
	DEF_ROMLOC(11750): move_toreg_32(read_32(0xFFFFF704), &D1); // MOVE.L	$F704,D1
	DEF_ROMLOC(11754): add_toreg_32(D1, &D1); // ADD.L	D1,D1
	DEF_ROMLOC(11756): swap_reg_16(&D1); // SWAP.W	D1
	DEF_ROMLOC(11758): and_toreg_16(0x3F, &D1); // ANDI.W	#$003F,D1
	DEF_ROMLOC(1175C): neg_reg_16(&D1); // NEG.W	D1
	DEF_ROMLOC(1175E): add_toreg_16(0x100, &D1); // ADDI.W	#$0100,D1
	DEF_ROMLOC(11762): move_tomem_16(D1, A0 + 0xA); // MOVE.W	D1,10(A0)
	DEF_ROMLOC(11766): goto rom_DC92; // BRA.W	$DC92
	DEF_ROMLOC(1176A): or_toreg_8(0xFFFFFF80, &D2); // ORI.B	#$80,D2
	DEF_ROMLOC(1176E): btst_toreg_32(D7, &D0); // BTST.L	D7,D0
	rom_1179A(); // Detected flow into next function
}*/