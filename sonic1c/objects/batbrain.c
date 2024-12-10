/*ROMFUNC(rom_10734) {
	DEF_ROMLOC(10734): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(10736): move_toreg_8(read_8(A0 + 0x24), &D0); // MOVE.B	36(A0),D0
	DEF_ROMLOC(1073A): move_toreg_16(read_16(0x10742 + (s16)(D0 & 0xffff)), &D1); // MOVE.W	6(PC,D0),D1
	DEF_ROMLOC(1073E): goto rom_10742 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
	DEF_ROMLOC(10742): or_toreg_8(0x34, &D4); // ORI.B	#$34,D4
	rom_10746(); // Detected flow into next function
}*/
/*ROMFUNC(rom_10746) {
	DEF_ROMLOC(10746): add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
	DEF_ROMLOC(1074A): move_tomem_32(0x108CA, A0 + 0x4); // MOVE.L	#$000108CA,4(A0)
	DEF_ROMLOC(10752): move_tomem_16(0xFFFF84B8, A0 + 0x2); // MOVE.W	#$84B8,2(A0)
	DEF_ROMLOC(10758): move_tomem_8(0x4, A0 + 0x1); // MOVE.B	#$04,1(A0)
	DEF_ROMLOC(1075E): move_tomem_8(0xC, A0 + 0x16); // MOVE.B	#$0C,22(A0)
	DEF_ROMLOC(10764): move_tomem_8(0x2, A0 + 0x18); // MOVE.B	#$02,24(A0)
	DEF_ROMLOC(1076A): move_tomem_8(0xB, A0 + 0x20); // MOVE.B	#$0B,32(A0)
	DEF_ROMLOC(10770): move_tomem_8(0x10, A0 + 0x19); // MOVE.B	#$10,25(A0)
	rom_10776(); // Detected flow into next function
}*/
/*ROMFUNC(rom_10776) {
	DEF_ROMLOC(10776): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(10778): move_toreg_8(read_8(A0 + 0x25), &D0); // MOVE.B	37(A0),D0
	DEF_ROMLOC(1077C): move_toreg_16(read_16(0x10792 + (s16)(D0 & 0xffff)), &D1); // MOVE.W	20(PC,D0),D1
	DEF_ROMLOC(10780): rom_10792 + (s16)(D1 & 0xffff)(); // JSR	16(PC,D1)
	DEF_ROMLOC(10784): move_toreg_32(0x108B6, &A1); // LEA.L	$000108B6,A1
	DEF_ROMLOC(1078A): rom_ADA2(); // BSR.W	$ADA2
	rom_FD38(); // BRA.W	$FD38
}*/