/*ROMFUNC(rom_128BC) {
	DEF_ROMLOC(128BC): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(128BE): move_toreg_8(read_8(A0 + 0x24), &D0); // MOVE.B	36(A0),D0
	DEF_ROMLOC(128C2): move_toreg_16(read_16(0x128CE + (s16)(D0 & 0xffff)), &D1); // MOVE.W	10(PC,D0),D1
	DEF_ROMLOC(128C6): rom_128CE + (s16)(D1 & 0xffff)(); // JSR	6(PC,D1)
	DEF_ROMLOC(128CA): goto rom_FD38; // BRA.W	$FD38
	DEF_ROMLOC(128CE): or_tomem_8(0x4E, A0); // ORI.B	#$4E,(A0)
	rom_128D6(); // Detected flow into next function
}*/
/*ROMFUNC(rom_128D6) {
	DEF_ROMLOC(128D6): move_toreg_8(0x78, &D7); // MOVE.B	#$78,D7
	DEF_ROMLOC(128DA): sub_toreg_32(read_32((s32)A4 + (s8)0xF0 + (s16)D13), &D3); // SUB.L	-16(A4,A5),D3
	rom_128DE(); // Detected flow into next function
}*/
/*ROMFUNC(rom_128DE) {
	DEF_ROMLOC(128DE): add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
	DEF_ROMLOC(128E2): move_tomem_32(0x129EC, A0 + 0x4); // MOVE.L	#$000129EC,4(A0)
	DEF_ROMLOC(128EA): move_tomem_16(0x42E9, A0 + 0x2); // MOVE.W	#$42E9,2(A0)
	DEF_ROMLOC(128F0): or_tomem_8(0x4, A0 + 0x1); // ORI.B	#$04,1(A0)
	DEF_ROMLOC(128F6): move_tomem_8(0x3, A0 + 0x18); // MOVE.B	#$03,24(A0)
	DEF_ROMLOC(128FC): move_tomem_8(0x10, A0 + 0x19); // MOVE.B	#$10,25(A0)
	DEF_ROMLOC(12902): move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B	40(A0),D0
	DEF_ROMLOC(12906): and_toreg_16(0xF, &D0); // ANDI.W	#$000F,D0
	DEF_ROMLOC(1290A): move_tomem_8(read_8(0x128D6 + (s16)(D0 & 0xffff)), A0 + 0x1F); // MOVE.B	-54(PC,D0),31(A0)
	DEF_ROMLOC(12910): move_tomem_8(read_8(A0 + 0x1F), A0 + 0x1E); // MOVE.B	31(A0),30(A0)
	DEF_ROMLOC(12916): and_tomem_8(0xF, A0 + 0x28); // ANDI.B	#$0F,40(A0)
	rom_1291C(); // Detected flow into next function
}*/
/*ROMFUNC(rom_1291C) {
	DEF_ROMLOC(1291C): sub_tomem_8(0x1, A0 + 0x1E); // SUBQ.B	#$01,30(A0)
	DEF_ROMLOC(12920): if (!CCR_EQ) goto rom_12956; // BNE.B	$12956
	DEF_ROMLOC(12922): move_tomem_8(read_8(A0 + 0x1F), A0 + 0x1E); // MOVE.B	31(A0),30(A0)
	DEF_ROMLOC(12928): rom_DF0C(); // BSR.W	$DF0C
	DEF_ROMLOC(1292C): if (!CCR_EQ) goto rom_12956; // BNE.B	$12956
	DEF_ROMLOC(1292E): rom_E11A(); // BSR.W	$E11A
	DEF_ROMLOC(12932): if (!CCR_EQ) goto rom_12956; // BNE.B	$12956
	DEF_ROMLOC(12934): move_tomem_8(0x62, A1 + 0x0); // MOVE.B	#$62,0(A1)
	DEF_ROMLOC(1293A): add_tomem_8(0x4, A1 + 0x24); // ADDQ.B	#$04,36(A1)
	DEF_ROMLOC(1293E): move_tomem_16(read_16(A0 + 0x8), A1 + 0x8); // MOVE.W	8(A0),8(A1)
	DEF_ROMLOC(12944): move_tomem_16(read_16(A0 + 0xC), A1 + 0xC); // MOVE.W	12(A0),12(A1)
	DEF_ROMLOC(1294A): move_tomem_8(read_8(A0 + 0x1), A1 + 0x1); // MOVE.B	1(A0),1(A1)
	DEF_ROMLOC(12950): move_tomem_8(read_8(A0 + 0x22), A1 + 0x22); // MOVE.B	34(A0),34(A1)
	DEF_ROMLOC(12956): return; // RTS
}*/
/*ROMFUNC(rom_12958) {
	DEF_ROMLOC(12958): add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
	DEF_ROMLOC(1295C): move_tomem_8(0x8, A0 + 0x16); // MOVE.B	#$08,22(A0)
	DEF_ROMLOC(12962): move_tomem_8(0x8, A0 + 0x17); // MOVE.B	#$08,23(A0)
	DEF_ROMLOC(12968): move_tomem_32(0x129EC, A0 + 0x4); // MOVE.L	#$000129EC,4(A0)
	DEF_ROMLOC(12970): move_tomem_16(0x2E9, A0 + 0x2); // MOVE.W	#$02E9,2(A0)
	DEF_ROMLOC(12976): or_tomem_8(0x4, A0 + 0x1); // ORI.B	#$04,1(A0)
	DEF_ROMLOC(1297C): move_tomem_8(0x4, A0 + 0x18); // MOVE.B	#$04,24(A0)
	DEF_ROMLOC(12982): move_tomem_8(0xFFFFFF98, A0 + 0x20); // MOVE.B	#$98,32(A0)
	DEF_ROMLOC(12988): move_tomem_8(0x8, A0 + 0x19); // MOVE.B	#$08,25(A0)
	DEF_ROMLOC(1298E): move_tomem_8(0x2, A0 + 0x1A); // MOVE.B	#$02,26(A0)
	DEF_ROMLOC(12994): add_tomem_16(0x8, A0 + 0xC); // ADDQ.W	#$08,12(A0)
	DEF_ROMLOC(12998): move_tomem_16(0x200, A0 + 0x10); // MOVE.W	#$0200,16(A0)
	DEF_ROMLOC(1299E): btst_tomem_8(0x0, A0 + 0x22); // BTST.B	#$00,34(A0)
	DEF_ROMLOC(129A4): if (!CCR_EQ) goto rom_129AA; // BNE.B	$129AA
	DEF_ROMLOC(129A6): neg_mem_16(A0 + 0x10); // NEG.W	16(A0)
	DEF_ROMLOC(129AA): move_toreg_16(0xAE, &D0); // MOVE.W	#$00AE,D0
	DEF_ROMLOC(129AE): rom_1394(); // JSR	$00001394
	rom_129B4(); // Detected flow into next function
}*/
/*ROMFUNC(rom_129B4) {
	DEF_ROMLOC(129B4): move_toreg_8(read_8(0xFFFFFE05), &D0); // MOVE.B	$FE05,D0
	DEF_ROMLOC(129B8): and_toreg_8(0x7, &D0); // ANDI.B	#$07,D0
	DEF_ROMLOC(129BC): if (!CCR_EQ) goto rom_129C4; // BNE.B	$129C4
	DEF_ROMLOC(129BE): bchg_tomem_8(0x0, A0 + 0x1A); // BCHG.B	#$00,26(A0)
	DEF_ROMLOC(129C4): rom_DC6C(); // BSR.W	$DC6C
	DEF_ROMLOC(129C8): btst_tomem_8(0x0, A0 + 0x22); // BTST.B	#$00,34(A0)
	DEF_ROMLOC(129CE): if (!CCR_EQ) goto rom_129DE; // BNE.B	$129DE
	DEF_ROMLOC(129D0): move_toreg_32(0xFFFFFFF8, &D3); // MOVEQ.L	$F8,D3
	DEF_ROMLOC(129D2): rom_157D4(); // BSR.W	$157D4
	DEF_ROMLOC(129D6): tst_reg_16(&D1); // TST.W	D1
	DEF_ROMLOC(129D8): if (CCR_MI) goto rom_DCCE; // BMI.W	$DCCE
	DEF_ROMLOC(129DC): return; // RTS
	DEF_ROMLOC(129DE): move_toreg_32(0x8, &D3); // MOVEQ.L	$08,D3
	DEF_ROMLOC(129E0): rom_15642(); // BSR.W	$15642
	DEF_ROMLOC(129E4): tst_reg_16(&D1); // TST.W	D1
	DEF_ROMLOC(129E6): if (CCR_MI) goto rom_DCCE; // BMI.W	$DCCE
	DEF_ROMLOC(129EA): return; // RTS
}*/