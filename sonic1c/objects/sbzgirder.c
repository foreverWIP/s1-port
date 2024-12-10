/*ROMFUNC(rom_16C92) {
	DEF_ROMLOC(16C92): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(16C94): move_toreg_8(read_8(A0 + 0x24), &D0); // MOVE.B	36(A0),D0
	DEF_ROMLOC(16C98): move_toreg_16(read_16(0x16CA0 + (s16)(D0 & 0xffff)), &D1); // MOVE.W	6(PC,D0),D1
	DEF_ROMLOC(16C9C): goto rom_16CA0 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
	DEF_ROMLOC(16CA0): or_toreg_8(0x3E, &D4); // ORI.B	#$3E,D4
	rom_16CA4(); // Detected flow into next function
}*/
/*ROMFUNC(rom_16CA4) {
	DEF_ROMLOC(16CA4): add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
	DEF_ROMLOC(16CA8): move_tomem_32(0x16D90, A0 + 0x4); // MOVE.L	#$00016D90,4(A0)
	DEF_ROMLOC(16CB0): move_tomem_16(0x42F0, A0 + 0x2); // MOVE.W	#$42F0,2(A0)
	DEF_ROMLOC(16CB6): or_tomem_8(0x4, A0 + 0x1); // ORI.B	#$04,1(A0)
	DEF_ROMLOC(16CBC): move_tomem_8(0x4, A0 + 0x18); // MOVE.B	#$04,24(A0)
	DEF_ROMLOC(16CC2): move_tomem_8(0x60, A0 + 0x19); // MOVE.B	#$60,25(A0)
	DEF_ROMLOC(16CC8): move_tomem_8(0x18, A0 + 0x16); // MOVE.B	#$18,22(A0)
	DEF_ROMLOC(16CCE): move_tomem_16(read_16(A0 + 0x8), A0 + 0x32); // MOVE.W	8(A0),50(A0)
	DEF_ROMLOC(16CD4): move_tomem_16(read_16(A0 + 0xC), A0 + 0x30); // MOVE.W	12(A0),48(A0)
	DEF_ROMLOC(16CDA): rom_16D46(); // BSR.W	$16D46
	rom_16CDE(); // Detected flow into next function
}*/
/*ROMFUNC(rom_16CDE) {
	DEF_ROMLOC(16CDE): move_tomem_16(read_16(A0 + 0x8), A7 -= 2); // MOVE.W	8(A0),-(A7)
	DEF_ROMLOC(16CE2): tst_mem_16(A0 + 0x3A); // TST.W	58(A0)
	DEF_ROMLOC(16CE6): if (CCR_EQ) goto rom_16CEE; // BEQ.B	$16CEE
	DEF_ROMLOC(16CE8): sub_tomem_16(0x1, A0 + 0x3A); // SUBQ.W	#$01,58(A0)
	DEF_ROMLOC(16CEC): if (!CCR_EQ) goto rom_16CFE; // BNE.B	$16CFE
	DEF_ROMLOC(16CEE): rom_DC6C(); // JSR	$0000DC6C
	DEF_ROMLOC(16CF4): sub_tomem_16(0x1, A0 + 0x34); // SUBQ.W	#$01,52(A0)
	DEF_ROMLOC(16CF8): if (!CCR_EQ) goto rom_16CFE; // BNE.B	$16CFE
	DEF_ROMLOC(16CFA): rom_16D46(); // BSR.W	$16D46
	DEF_ROMLOC(16CFE): move_toreg_16(read_16((A7 += 2, A7 - 2)), &D4); // MOVE.W	(A7)+,D4
	DEF_ROMLOC(16D00): tst_mem_8(A0 + 0x1); // TST.B	1(A0)
	DEF_ROMLOC(16D04): if (CCR_PL) goto rom_16D1E; // BPL.B	$16D1E
	DEF_ROMLOC(16D06): move_toreg_32(0x0, &D1); // MOVEQ.L	$00,D1
	DEF_ROMLOC(16D08): move_toreg_8(read_8(A0 + 0x19), &D1); // MOVE.B	25(A0),D1
	DEF_ROMLOC(16D0C): add_toreg_16(0xB, &D1); // ADDI.W	#$000B,D1
	DEF_ROMLOC(16D10): move_toreg_32(0x0, &D2); // MOVEQ.L	$00,D2
	DEF_ROMLOC(16D12): move_toreg_8(read_8(A0 + 0x16), &D2); // MOVE.B	22(A0),D2
	DEF_ROMLOC(16D16): move_toreg_16(D2, &D3); // MOVE.W	D2,D3
	DEF_ROMLOC(16D18): add_toreg_16(0x1, &D3); // ADDQ.W	#$01,D3
	DEF_ROMLOC(16D1A): rom_10062(); // BSR.W	$10062
	DEF_ROMLOC(16D1E): move_toreg_16(read_16(A0 + 0x32), &D0); // MOVE.W	50(A0),D0
	DEF_ROMLOC(16D22): and_toreg_16(0xFFFFFF80, &D0); // ANDI.W	#$FF80,D0
	DEF_ROMLOC(16D26): move_toreg_16(read_16(0xFFFFF700), &D1); // MOVE.W	$F700,D1
	DEF_ROMLOC(16D2A): sub_toreg_16(0x80, &D1); // SUBI.W	#$0080,D1
	DEF_ROMLOC(16D2E): and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
	DEF_ROMLOC(16D32): sub_toreg_16(D1, &D0); // SUB.W	D1,D0
	DEF_ROMLOC(16D34): cmp_toreg_16(0x280, &D0); // CMPI.W	#$0280,D0
	DEF_ROMLOC(16D38): if (CCR_HI) goto rom_16D40; // BHI.B	$16D40
	DEF_ROMLOC(16D3A): goto rom_DC92; // JMP	$0000DC92
	DEF_ROMLOC(16D40): goto rom_DCCE; // JMP	$0000DCCE
}*/
/*ROMFUNC(rom_16D46) {
	DEF_ROMLOC(16D46): move_toreg_8(read_8(A0 + 0x38), &D0); // MOVE.B	56(A0),D0
	DEF_ROMLOC(16D4A): and_toreg_16(0x18, &D0); // ANDI.W	#$0018,D0
	DEF_ROMLOC(16D4E): move_toreg_32(0x16D70, &A1); // LEA.L	$00016D70,A1
	DEF_ROMLOC(16D54): move_toreg_32((s32)A1 + (s8)0x0 + (s16)D0, &A1); // LEA.L	0(A1,D0),A1
	DEF_ROMLOC(16D58): move_tomem_16(read_16((A1 += 2, A1 - 2)), A0 + 0x10); // MOVE.W	(A1)+,16(A0)
	DEF_ROMLOC(16D5C): move_tomem_16(read_16((A1 += 2, A1 - 2)), A0 + 0x12); // MOVE.W	(A1)+,18(A0)
	DEF_ROMLOC(16D60): move_tomem_16(read_16((A1 += 2, A1 - 2)), A0 + 0x34); // MOVE.W	(A1)+,52(A0)
	DEF_ROMLOC(16D64): add_tomem_8(0x8, A0 + 0x38); // ADDQ.B	#$08,56(A0)
	DEF_ROMLOC(16D68): move_tomem_16(0x7, A0 + 0x3A); // MOVE.W	#$0007,58(A0)
	DEF_ROMLOC(16D6E): return; // RTS
	DEF_ROMLOC(16D70): btst_toreg_32(D0, &D0); // BTST.L	D0,D0
	DEF_ROMLOC(16D72): or_toreg_8(0x60, &D0); // ORI.B	#$60,D0
	DEF_ROMLOC(16D76): or_toreg_8(0x0, &D0); // ORI.B	#$00,D0
	DEF_ROMLOC(16D7A): btst_toreg_32(D0, &D0); // BTST.L	D0,D0
	DEF_ROMLOC(16D7C): or_tomem_8(0x0, (s32)A0 + (s8)0x0 + (s16)D15); // ORI.B	#$00,0(A0,A7)
	rom_16DD0(); // Detected flow into next function
}*/