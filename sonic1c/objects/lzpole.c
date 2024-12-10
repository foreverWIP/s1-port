/*ROMFUNC(rom_118DA) {
	DEF_ROMLOC(118DA): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(118DC): move_toreg_8(read_8(A0 + 0x24), &D0); // MOVE.B	36(A0),D0
	DEF_ROMLOC(118E0): move_toreg_16(read_16(0x118E8 + (s16)(D0 & 0xffff)), &D1); // MOVE.W	6(PC,D0),D1
	DEF_ROMLOC(118E4): goto rom_118E8 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
}*/
/*ROMFUNC(rom_118EE) {
	DEF_ROMLOC(118EE): add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
	DEF_ROMLOC(118F2): move_tomem_32(0x119F6, A0 + 0x4); // MOVE.L	#$000119F6,4(A0)
	DEF_ROMLOC(118FA): move_tomem_16(0x43DE, A0 + 0x2); // MOVE.W	#$43DE,2(A0)
	DEF_ROMLOC(11900): move_tomem_8(0x4, A0 + 0x1); // MOVE.B	#$04,1(A0)
	DEF_ROMLOC(11906): move_tomem_8(0x8, A0 + 0x19); // MOVE.B	#$08,25(A0)
	DEF_ROMLOC(1190C): move_tomem_8(0x4, A0 + 0x18); // MOVE.B	#$04,24(A0)
	DEF_ROMLOC(11912): move_tomem_8(0xFFFFFFE1, A0 + 0x20); // MOVE.B	#$E1,32(A0)
	DEF_ROMLOC(11918): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(1191A): move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B	40(A0),D0
	DEF_ROMLOC(1191E): mulu_toreg_16(0x3C, &D0); // MULU.W	#$003C,D0
	DEF_ROMLOC(11922): move_tomem_16(D0, A0 + 0x30); // MOVE.W	D0,48(A0)
	rom_11926(); // Detected flow into next function
}*/
/*ROMFUNC(rom_11926) {
	DEF_ROMLOC(11926): tst_mem_8(A0 + 0x32); // TST.B	50(A0)
	DEF_ROMLOC(1192A): if (CCR_EQ) goto rom_1199C; // BEQ.B	$1199C
	DEF_ROMLOC(1192C): tst_mem_16(A0 + 0x30); // TST.W	48(A0)
	DEF_ROMLOC(11930): if (CCR_EQ) goto rom_11940; // BEQ.B	$11940
	DEF_ROMLOC(11932): sub_tomem_16(0x1, A0 + 0x30); // SUBQ.W	#$01,48(A0)
	DEF_ROMLOC(11936): if (!CCR_EQ) goto rom_11940; // BNE.B	$11940
	DEF_ROMLOC(11938): move_tomem_8(0x1, A0 + 0x1A); // MOVE.B	#$01,26(A0)
	DEF_ROMLOC(1193E): goto rom_11986; // BRA.B	$11986
	DEF_ROMLOC(11940): move_toreg_32(0xFFFFD000, &A1); // LEA.L	$D000,A1
	DEF_ROMLOC(11944): move_toreg_16(read_16(A0 + 0xC), &D0); // MOVE.W	12(A0),D0
	DEF_ROMLOC(11948): sub_toreg_16(0x18, &D0); // SUBI.W	#$0018,D0
	DEF_ROMLOC(1194C): btst_tomem_8(0x0, 0xFFFFF604); // BTST.B	#$00,$F604
	DEF_ROMLOC(11952): if (CCR_EQ) goto rom_11962; // BEQ.B	$11962
	DEF_ROMLOC(11954): sub_tomem_16(0x1, A1 + 0xC); // SUBQ.W	#$01,12(A1)
	DEF_ROMLOC(11958): cmp_toreg_16(read_16(A1 + 0xC), &D0); // CMP.W	12(A1),D0
	DEF_ROMLOC(1195C): if (CCR_CS) goto rom_11962; // BCS.B	$11962
	DEF_ROMLOC(1195E): move_tomem_16(D0, A1 + 0xC); // MOVE.W	D0,12(A1)
	DEF_ROMLOC(11962): add_toreg_16(0x24, &D0); // ADDI.W	#$0024,D0
	DEF_ROMLOC(11966): btst_tomem_8(0x1, 0xFFFFF604); // BTST.B	#$01,$F604
	DEF_ROMLOC(1196C): if (CCR_EQ) goto rom_1197C; // BEQ.B	$1197C
	DEF_ROMLOC(1196E): add_tomem_16(0x1, A1 + 0xC); // ADDQ.W	#$01,12(A1)
	DEF_ROMLOC(11972): cmp_toreg_16(read_16(A1 + 0xC), &D0); // CMP.W	12(A1),D0
	DEF_ROMLOC(11976): if (CCR_CC) goto rom_1197C; // BCC.B	$1197C
	DEF_ROMLOC(11978): move_tomem_16(D0, A1 + 0xC); // MOVE.W	D0,12(A1)
	DEF_ROMLOC(1197C): move_toreg_8(read_8(0xFFFFF603), &D0); // MOVE.B	$F603,D0
	DEF_ROMLOC(11980): and_toreg_16(0x70, &D0); // ANDI.W	#$0070,D0
	DEF_ROMLOC(11984): if (CCR_EQ) goto rom_119F2; // BEQ.B	$119F2
	DEF_ROMLOC(11986): clr_mem_8(A0 + 0x20); // CLR.B	32(A0)
	DEF_ROMLOC(1198A): add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
	DEF_ROMLOC(1198E): clr_mem_8(0xFFFFF7C8); // CLR.B	$F7C8
	DEF_ROMLOC(11992): clr_mem_8(0xFFFFF7C9); // CLR.B	$F7C9
	DEF_ROMLOC(11996): clr_mem_8(A0 + 0x32); // CLR.B	50(A0)
	DEF_ROMLOC(1199A): goto rom_119F2; // BRA.B	$119F2
	DEF_ROMLOC(1199C): tst_mem_8(A0 + 0x21); // TST.B	33(A0)
	DEF_ROMLOC(119A0): if (CCR_EQ) goto rom_119F2; // BEQ.B	$119F2
	DEF_ROMLOC(119A2): move_toreg_32(0xFFFFD000, &A1); // LEA.L	$D000,A1
	DEF_ROMLOC(119A6): move_toreg_16(read_16(A0 + 0x8), &D0); // MOVE.W	8(A0),D0
	DEF_ROMLOC(119AA): add_toreg_16(0x14, &D0); // ADDI.W	#$0014,D0
	DEF_ROMLOC(119AE): cmp_toreg_16(read_16(A1 + 0x8), &D0); // CMP.W	8(A1),D0
	DEF_ROMLOC(119B2): if (CCR_CC) goto rom_119F2; // BCC.B	$119F2
	DEF_ROMLOC(119B4): clr_mem_8(A0 + 0x21); // CLR.B	33(A0)
	DEF_ROMLOC(119B8): cmp_tomem_8(0x4, A1 + 0x24); // CMPI.B	#$04,36(A1)
	DEF_ROMLOC(119BE): if (CCR_CC) goto rom_119F2; // BCC.B	$119F2
	DEF_ROMLOC(119C0): clr_mem_16(A1 + 0x10); // CLR.W	16(A1)
	DEF_ROMLOC(119C4): clr_mem_16(A1 + 0x12); // CLR.W	18(A1)
	DEF_ROMLOC(119C8): move_toreg_16(read_16(A0 + 0x8), &D0); // MOVE.W	8(A0),D0
	DEF_ROMLOC(119CC): add_toreg_16(0x14, &D0); // ADDI.W	#$0014,D0
	DEF_ROMLOC(119D0): move_tomem_16(D0, A1 + 0x8); // MOVE.W	D0,8(A1)
	DEF_ROMLOC(119D4): bclr_tomem_8(0x0, A1 + 0x22); // BCLR.B	#$00,34(A1)
	DEF_ROMLOC(119DA): move_tomem_8(0x11, A1 + 0x1C); // MOVE.B	#$11,28(A1)
	DEF_ROMLOC(119E0): move_tomem_8(0x1, 0xFFFFF7C8); // MOVE.B	#$01,$F7C8
	DEF_ROMLOC(119E6): move_tomem_8(0x1, 0xFFFFF7C9); // MOVE.B	#$01,$F7C9
	DEF_ROMLOC(119EC): move_tomem_8(0x1, A0 + 0x32); // MOVE.B	#$01,50(A0)
	rom_119F2(); // Detected flow into next function
}*/
/*ROMFUNC(rom_119F2) {
	DEF_ROMLOC(119F2): goto rom_FD38; // BRA.W	$FD38
	DEF_ROMLOC(119F6): or_toreg_8(0xF, &D4); // ORI.B	#$0F,D4
	rom_11A1A(); // Detected flow into next function
}*/