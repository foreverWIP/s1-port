/*ROMFUNC(rom_11BD0) {
	DEF_ROMLOC(11BD0): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(11BD2): move_toreg_8(read_8(A0 + 0x24), &D0); // MOVE.B	36(A0),D0
	DEF_ROMLOC(11BD6): move_toreg_16(read_16(0x11BDE + (s16)(D0 & 0xffff)), &D1); // MOVE.W	6(PC,D0),D1
	DEF_ROMLOC(11BDA): goto rom_11BDE + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
	DEF_ROMLOC(11BDE): or_toreg_8(0x28, &D4); // ORI.B	#$28,D4
	rom_11BE2(); // Detected flow into next function
}*/
/*ROMFUNC(rom_11BE2) {
	DEF_ROMLOC(11BE2): add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
	DEF_ROMLOC(11BE6): move_tomem_32(0x11CE4, A0 + 0x4); // MOVE.L	#$00011CE4,4(A0)
	DEF_ROMLOC(11BEE): move_tomem_16(0x43A0, A0 + 0x2); // MOVE.W	#$43A0,2(A0)
	DEF_ROMLOC(11BF4): or_tomem_8(0x4, A0 + 0x1); // ORI.B	#$04,1(A0)
	DEF_ROMLOC(11BFA): move_tomem_8(0x10, A0 + 0x19); // MOVE.B	#$10,25(A0)
	DEF_ROMLOC(11C00): move_tomem_8(0x4, A0 + 0x18); // MOVE.B	#$04,24(A0)
	rom_11C06(); // Detected flow into next function
}*/
/*ROMFUNC(rom_11C06) {
	DEF_ROMLOC(11C06): btst_tomem_8(0x1, A0 + 0x28); // BTST.B	#$01,40(A0)
	DEF_ROMLOC(11C0C): if (!CCR_EQ) goto rom_11C28; // BNE.B	$11C28
	DEF_ROMLOC(11C0E): sub_tomem_16(0x1, A0 + 0x30); // SUBQ.W	#$01,48(A0)
	DEF_ROMLOC(11C12): if (CCR_PL) goto rom_11C28; // BPL.B	$11C28
	DEF_ROMLOC(11C14): move_tomem_16(0x78, A0 + 0x30); // MOVE.W	#$0078,48(A0)
	DEF_ROMLOC(11C1A): bchg_tomem_8(0x0, A0 + 0x32); // BCHG.B	#$00,50(A0)
	DEF_ROMLOC(11C20): if (CCR_EQ) goto rom_11C28; // BEQ.B	$11C28
	DEF_ROMLOC(11C22): move_tomem_16(0xB4, A0 + 0x30); // MOVE.W	#$00B4,48(A0)
	DEF_ROMLOC(11C28): tst_mem_8(A0 + 0x32); // TST.B	50(A0)
	DEF_ROMLOC(11C2C): if (!CCR_EQ) goto rom_11CC0; // BNE.W	$11CC0
	DEF_ROMLOC(11C30): move_toreg_32(0xFFFFD000, &A1); // LEA.L	$D000,A1
	DEF_ROMLOC(11C34): move_toreg_16(read_16(A1 + 0x8), &D0); // MOVE.W	8(A1),D0
	DEF_ROMLOC(11C38): sub_toreg_16(read_16(A0 + 0x8), &D0); // SUB.W	8(A0),D0
	DEF_ROMLOC(11C3C): btst_tomem_8(0x0, A0 + 0x22); // BTST.B	#$00,34(A0)
	DEF_ROMLOC(11C42): if (!CCR_EQ) goto rom_11C46; // BNE.B	$11C46
	DEF_ROMLOC(11C44): neg_reg_16(&D0); // NEG.W	D0
	DEF_ROMLOC(11C46): add_toreg_16(0x50, &D0); // ADDI.W	#$0050,D0
	DEF_ROMLOC(11C4A): cmp_toreg_16(0xF0, &D0); // CMPI.W	#$00F0,D0
	DEF_ROMLOC(11C4E): if (CCR_CC) goto rom_11C8E; // BCC.B	$11C8E
	DEF_ROMLOC(11C50): move_toreg_16(read_16(A1 + 0xC), &D1); // MOVE.W	12(A1),D1
	DEF_ROMLOC(11C54): add_toreg_16(0x60, &D1); // ADDI.W	#$0060,D1
	DEF_ROMLOC(11C58): sub_toreg_16(read_16(A0 + 0xC), &D1); // SUB.W	12(A0),D1
	DEF_ROMLOC(11C5C): if (CCR_CS) goto rom_11C8E; // BCS.B	$11C8E
	DEF_ROMLOC(11C5E): cmp_toreg_16(0x70, &D1); // CMPI.W	#$0070,D1
	DEF_ROMLOC(11C62): if (CCR_CC) goto rom_11C8E; // BCC.B	$11C8E
	DEF_ROMLOC(11C64): sub_toreg_16(0x50, &D0); // SUBI.W	#$0050,D0
	DEF_ROMLOC(11C68): if (CCR_CC) goto rom_11C6E; // BCC.B	$11C6E
	DEF_ROMLOC(11C6A): not_reg_16(&D0); // NOT.W	D0
	DEF_ROMLOC(11C6C): add_toreg_16(D0, &D0); // ADD.W	D0,D0
	DEF_ROMLOC(11C6E): add_toreg_16(0x60, &D0); // ADDI.W	#$0060,D0
	DEF_ROMLOC(11C72): btst_tomem_8(0x0, A0 + 0x22); // BTST.B	#$00,34(A0)
	DEF_ROMLOC(11C78): if (!CCR_EQ) goto rom_11C7C; // BNE.B	$11C7C
	DEF_ROMLOC(11C7A): neg_reg_16(&D0); // NEG.W	D0
	DEF_ROMLOC(11C7C): neg_reg_8(&D0); // NEG.B	D0
	DEF_ROMLOC(11C7E): asr_toreg_16(0x4, &D0); // ASR.W	#$04,D0
	DEF_ROMLOC(11C80): btst_tomem_8(0x0, A0 + 0x28); // BTST.B	#$00,40(A0)
	DEF_ROMLOC(11C86): if (CCR_EQ) goto rom_11C8A; // BEQ.B	$11C8A
	DEF_ROMLOC(11C88): neg_reg_16(&D0); // NEG.W	D0
	DEF_ROMLOC(11C8A): add_tomem_16(D0, A1 + 0x8); // ADD.W	D0,8(A1)
	DEF_ROMLOC(11C8E): sub_tomem_8(0x1, A0 + 0x1E); // SUBQ.B	#$01,30(A0)
	DEF_ROMLOC(11C92): if (CCR_PL) goto rom_11CC0; // BPL.B	$11CC0
	DEF_ROMLOC(11C94): move_tomem_8(0x0, A0 + 0x1E); // MOVE.B	#$00,30(A0)
	DEF_ROMLOC(11C9A): add_tomem_8(0x1, A0 + 0x1B); // ADDQ.B	#$01,27(A0)
	DEF_ROMLOC(11C9E): cmp_tomem_8(0x3, A0 + 0x1B); // CMPI.B	#$03,27(A0)
	DEF_ROMLOC(11CA4): if (CCR_CS) goto rom_11CAC; // BCS.B	$11CAC
	DEF_ROMLOC(11CA6): move_tomem_8(0x0, A0 + 0x1B); // MOVE.B	#$00,27(A0)
	DEF_ROMLOC(11CAC): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(11CAE): btst_tomem_8(0x0, A0 + 0x28); // BTST.B	#$00,40(A0)
	DEF_ROMLOC(11CB4): if (CCR_EQ) goto rom_11CB8; // BEQ.B	$11CB8
	DEF_ROMLOC(11CB6): move_toreg_32(0x2, &D0); // MOVEQ.L	$02,D0
	DEF_ROMLOC(11CB8): add_toreg_8(read_8(A0 + 0x1B), &D0); // ADD.B	27(A0),D0
	DEF_ROMLOC(11CBC): move_tomem_8(D0, A0 + 0x1A); // MOVE.B	D0,26(A0)
	DEF_ROMLOC(11CC0): rom_DC92(); // BSR.W	$DC92
	DEF_ROMLOC(11CC4): move_toreg_16(read_16(A0 + 0x8), &D0); // MOVE.W	8(A0),D0
	DEF_ROMLOC(11CC8): and_toreg_16(0xFFFFFF80, &D0); // ANDI.W	#$FF80,D0
	DEF_ROMLOC(11CCC): move_toreg_16(read_16(0xFFFFF700), &D1); // MOVE.W	$F700,D1
	DEF_ROMLOC(11CD0): sub_toreg_16(0x80, &D1); // SUBI.W	#$0080,D1
	DEF_ROMLOC(11CD4): and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
	DEF_ROMLOC(11CD8): sub_toreg_16(D1, &D0); // SUB.W	D1,D0
	DEF_ROMLOC(11CDA): cmp_toreg_16(0x280, &D0); // CMPI.W	#$0280,D0
	DEF_ROMLOC(11CDE): if (CCR_HI) goto rom_DCCE; // BHI.W	$DCCE
	DEF_ROMLOC(11CE2): return; // RTS
}*/