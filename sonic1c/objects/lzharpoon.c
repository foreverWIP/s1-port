/*ROMFUNC(rom_125D8) {
	DEF_ROMLOC(125D8): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(125DA): move_toreg_8(read_8(A0 + 0x24), &D0); // MOVE.B	36(A0),D0
	DEF_ROMLOC(125DE): move_toreg_16(read_16(0x125E6 + (s16)(D0 & 0xffff)), &D1); // MOVE.W	6(PC,D0),D1
	DEF_ROMLOC(125E2): goto rom_125E6 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
}*/
/*ROMFUNC(rom_125EC) {
	DEF_ROMLOC(125EC): add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
	DEF_ROMLOC(125F0): move_tomem_32(0x1266E, A0 + 0x4); // MOVE.L	#$0001266E,4(A0)
	DEF_ROMLOC(125F8): move_tomem_16(0x3CC, A0 + 0x2); // MOVE.W	#$03CC,2(A0)
	DEF_ROMLOC(125FE): or_tomem_8(0x4, A0 + 0x1); // ORI.B	#$04,1(A0)
	DEF_ROMLOC(12604): move_tomem_8(0x4, A0 + 0x18); // MOVE.B	#$04,24(A0)
	DEF_ROMLOC(1260A): move_tomem_8(read_8(A0 + 0x28), A0 + 0x1C); // MOVE.B	40(A0),28(A0)
	DEF_ROMLOC(12610): move_tomem_8(0x14, A0 + 0x19); // MOVE.B	#$14,25(A0)
	DEF_ROMLOC(12616): move_tomem_16(0x3C, A0 + 0x30); // MOVE.W	#$003C,48(A0)
	rom_1261C(); // Detected flow into next function
}*/
/*ROMFUNC(rom_1261C) {
	DEF_ROMLOC(1261C): move_toreg_32(0x12656, &A1); // LEA.L	$00012656,A1
	DEF_ROMLOC(12622): rom_ADA2(); // BSR.W	$ADA2
	DEF_ROMLOC(12626): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(12628): move_toreg_8(read_8(A0 + 0x1A), &D0); // MOVE.B	26(A0),D0
	DEF_ROMLOC(1262C): move_tomem_8(read_8(0x12636 + (s16)(D0 & 0xffff)), A0 + 0x20); // MOVE.B	8(PC,D0),32(A0)
	DEF_ROMLOC(12632): goto rom_FD38; // BRA.W	$FD38
	DEF_ROMLOC(12636): sub_tomem_32(D5, (A4 += 4, A4 - 4)); // SUB.L	D5,(A4)+
	DEF_ROMLOC(12638): sub_tomem_32(D6, (A6 += 4, A6 - 4)); // SUB.L	D6,(A6)+
	DEF_ROMLOC(1263A): sub_tomem_32(D7, A0 -= 4); // SUB.L	D7,-(A0)
	rom_1263C(); // Detected flow into next function
}*/
/*ROMFUNC(rom_1263C) {
	DEF_ROMLOC(1263C): sub_tomem_16(0x1, A0 + 0x30); // SUBQ.W	#$01,48(A0)
	DEF_ROMLOC(12640): if (CCR_PL) goto rom_12652; // BPL.B	$12652
	DEF_ROMLOC(12642): move_tomem_16(0x3C, A0 + 0x30); // MOVE.W	#$003C,48(A0)
	DEF_ROMLOC(12648): sub_tomem_8(0x2, A0 + 0x24); // SUBQ.B	#$02,36(A0)
	DEF_ROMLOC(1264C): bchg_tomem_8(0x0, A0 + 0x1C); // BCHG.B	#$00,28(A0)
	rom_FD38(); // BRA.W	$FD38
}*/