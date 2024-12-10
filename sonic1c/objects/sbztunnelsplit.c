/*ROMFUNC(rom_15802) {
	DEF_ROMLOC(15802): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(15804): move_toreg_8(read_8(A0 + 0x24), &D0); // MOVE.B	36(A0),D0
	DEF_ROMLOC(15808): move_toreg_16(read_16(0x15810 + (s16)(D0 & 0xffff)), &D1); // MOVE.W	6(PC,D0),D1
	DEF_ROMLOC(1580C): goto rom_15810 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
}*/
/*ROMFUNC(rom_15818) {
	DEF_ROMLOC(15818): add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
	DEF_ROMLOC(1581C): move_toreg_16(0x1, &D1); // MOVE.W	#$0001,D1
	DEF_ROMLOC(15820): move_toreg_32(A0, &A1); // MOVEA.L	A0,A1
	DEF_ROMLOC(15822): goto rom_1584C; // BRA.B	$1584C
	DEF_ROMLOC(15824): rom_E11A(); // BSR.W	$E11A
	DEF_ROMLOC(15828): if (!CCR_EQ) goto rom_15866; // BNE.B	$15866
	DEF_ROMLOC(1582A): move_tomem_8(0x66, A1 + 0x0); // MOVE.B	#$66,0(A1)
	DEF_ROMLOC(15830): add_tomem_8(0x4, A1 + 0x24); // ADDQ.B	#$04,36(A1)
	DEF_ROMLOC(15834): move_tomem_16(read_16(A0 + 0x8), A1 + 0x8); // MOVE.W	8(A0),8(A1)
	DEF_ROMLOC(1583A): move_tomem_16(read_16(A0 + 0xC), A1 + 0xC); // MOVE.W	12(A0),12(A1)
	DEF_ROMLOC(15840): move_tomem_8(0x3, A1 + 0x18); // MOVE.B	#$03,24(A1)
	DEF_ROMLOC(15846): move_tomem_8(0x10, A1 + 0x1A); // MOVE.B	#$10,26(A1)
	DEF_ROMLOC(1584C): move_tomem_32(0x159FA, A1 + 0x4); // MOVE.L	#$000159FA,4(A1)
	DEF_ROMLOC(15854): move_tomem_16(0x4348, A1 + 0x2); // MOVE.W	#$4348,2(A1)
	DEF_ROMLOC(1585A): or_tomem_8(0x4, A1 + 0x1); // ORI.B	#$04,1(A1)
	DEF_ROMLOC(15860): move_tomem_8(0x38, A1 + 0x19); // MOVE.B	#$38,25(A1)
	DEF_ROMLOC(15866): dec_reg_16(&D1); if ((D1 & 0xffff) != 0xffff) goto rom_15824; // DBF.W	D1,$15824
	DEF_ROMLOC(1586A): move_tomem_8(0x30, A0 + 0x19); // MOVE.B	#$30,25(A0)
	DEF_ROMLOC(15870): move_tomem_8(0x4, A0 + 0x18); // MOVE.B	#$04,24(A0)
	DEF_ROMLOC(15876): move_tomem_16(0x3C, A0 + 0x30); // MOVE.W	#$003C,48(A0)
	DEF_ROMLOC(1587C): move_tomem_8(0x1, A0 + 0x34); // MOVE.B	#$01,52(A0)
	DEF_ROMLOC(15882): move_tomem_8(read_8(A0 + 0x28), A0 + 0x38); // MOVE.B	40(A0),56(A0)
	rom_15888(); // Detected flow into next function
}*/
/*ROMFUNC(rom_15888) {
	DEF_ROMLOC(15888): rom_15968(); // BSR.W	$15968
	DEF_ROMLOC(1588C): tst_mem_8(A0 + 0x1); // TST.B	1(A0)
	DEF_ROMLOC(15890): if (CCR_PL) goto rom_1591C; // BPL.W	$1591C
	DEF_ROMLOC(15894): move_toreg_16(0x30, &D1); // MOVE.W	#$0030,D1
	DEF_ROMLOC(15898): move_toreg_16(D1, &D2); // MOVE.W	D1,D2
	DEF_ROMLOC(1589A): move_toreg_16(D2, &D3); // MOVE.W	D2,D3
	DEF_ROMLOC(1589C): add_toreg_16(0x1, &D3); // ADDQ.W	#$01,D3
	DEF_ROMLOC(1589E): move_toreg_16(read_16(A0 + 0x8), &D4); // MOVE.W	8(A0),D4
	DEF_ROMLOC(158A2): rom_10062(); // BSR.W	$10062
	DEF_ROMLOC(158A6): btst_tomem_8(0x5, A0 + 0x22); // BTST.B	#$05,34(A0)
	DEF_ROMLOC(158AC): if (CCR_EQ) goto rom_1591C; // BEQ.W	$1591C
	DEF_ROMLOC(158B0): move_toreg_32(0xFFFFD000, &A1); // LEA.L	$D000,A1
	DEF_ROMLOC(158B4): move_toreg_32(0xE, &D1); // MOVEQ.L	$0E,D1
	DEF_ROMLOC(158B6): move_toreg_16(read_16(A1 + 0x8), &D0); // MOVE.W	8(A1),D0
	DEF_ROMLOC(158BA): cmp_toreg_16(read_16(A0 + 0x8), &D0); // CMP.W	8(A0),D0
	DEF_ROMLOC(158BE): if (CCR_CS) goto rom_158C2; // BCS.B	$158C2
	DEF_ROMLOC(158C0): move_toreg_32(0x7, &D1); // MOVEQ.L	$07,D1
	DEF_ROMLOC(158C2): cmp_toreg_8(read_8(A0 + 0x1A), &D1); // CMP.B	26(A0),D1
	DEF_ROMLOC(158C6): if (!CCR_EQ) goto rom_1591C; // BNE.B	$1591C
	DEF_ROMLOC(158C8): move_tomem_8(D1, A0 + 0x32); // MOVE.B	D1,50(A0)
	DEF_ROMLOC(158CC): add_tomem_8(0x4, A0 + 0x24); // ADDQ.B	#$04,36(A0)
	DEF_ROMLOC(158D0): move_tomem_8(0x1, 0xFFFFF7C8); // MOVE.B	#$01,$F7C8
	DEF_ROMLOC(158D6): move_tomem_8(0x2, A1 + 0x1C); // MOVE.B	#$02,28(A1)
	DEF_ROMLOC(158DC): move_tomem_16(0x800, A1 + 0x14); // MOVE.W	#$0800,20(A1)
	DEF_ROMLOC(158E2): move_tomem_16(0x0, A1 + 0x10); // MOVE.W	#$0000,16(A1)
	DEF_ROMLOC(158E8): move_tomem_16(0x0, A1 + 0x12); // MOVE.W	#$0000,18(A1)
	DEF_ROMLOC(158EE): bclr_tomem_8(0x5, A0 + 0x22); // BCLR.B	#$05,34(A0)
	DEF_ROMLOC(158F4): bclr_tomem_8(0x5, A1 + 0x22); // BCLR.B	#$05,34(A1)
	DEF_ROMLOC(158FA): bset_tomem_8(0x1, A1 + 0x22); // BSET.B	#$01,34(A1)
	DEF_ROMLOC(15900): move_toreg_16(read_16(A1 + 0x8), &D2); // MOVE.W	8(A1),D2
	DEF_ROMLOC(15904): move_toreg_16(read_16(A1 + 0xC), &D3); // MOVE.W	12(A1),D3
	DEF_ROMLOC(15908): rom_159B0(); // BSR.W	$159B0
	DEF_ROMLOC(1590C): add_tomem_16(D2, A1 + 0x8); // ADD.W	D2,8(A1)
	DEF_ROMLOC(15910): add_tomem_16(D3, A1 + 0xC); // ADD.W	D3,12(A1)
	DEF_ROMLOC(15914): asr_mem_16(A1 + 0x8); // ASR.W	8(A1)
	DEF_ROMLOC(15918): asr_mem_16(A1 + 0xC); // ASR.W	12(A1)
	rom_1591C(); // Detected flow into next function
}*/
/*ROMFUNC(rom_1591C) {
	rom_FD38(); // BRA.W	$FD38
}*/
/*ROMFUNC(rom_15920) {
	DEF_ROMLOC(15920): move_toreg_8(read_8(A0 + 0x1A), &D0); // MOVE.B	26(A0),D0
	DEF_ROMLOC(15924): cmp_toreg_8(0x4, &D0); // CMPI.B	#$04,D0
	DEF_ROMLOC(15928): if (CCR_EQ) goto rom_15930; // BEQ.B	$15930
	DEF_ROMLOC(1592A): cmp_toreg_8(0x7, &D0); // CMPI.B	#$07,D0
	DEF_ROMLOC(1592E): if (!CCR_EQ) goto rom_15960; // BNE.B	$15960
	DEF_ROMLOC(15930): cmp_toreg_8(read_8(A0 + 0x32), &D0); // CMP.B	50(A0),D0
	DEF_ROMLOC(15934): if (CCR_EQ) goto rom_15960; // BEQ.B	$15960
	DEF_ROMLOC(15936): move_toreg_32(0xFFFFD000, &A1); // LEA.L	$D000,A1
	DEF_ROMLOC(1593A): move_tomem_16(0x0, A1 + 0x10); // MOVE.W	#$0000,16(A1)
	DEF_ROMLOC(15940): move_tomem_16(0x800, A1 + 0x12); // MOVE.W	#$0800,18(A1)
	DEF_ROMLOC(15946): cmp_toreg_8(0x4, &D0); // CMPI.B	#$04,D0
	DEF_ROMLOC(1594A): if (CCR_EQ) goto rom_15958; // BEQ.B	$15958
	DEF_ROMLOC(1594C): move_tomem_16(0x800, A1 + 0x10); // MOVE.W	#$0800,16(A1)
	DEF_ROMLOC(15952): move_tomem_16(0x800, A1 + 0x12); // MOVE.W	#$0800,18(A1)
	DEF_ROMLOC(15958): clr_mem_8(0xFFFFF7C8); // CLR.B	$F7C8
	DEF_ROMLOC(1595C): sub_tomem_8(0x4, A0 + 0x24); // SUBQ.B	#$04,36(A0)
	DEF_ROMLOC(15960): rom_15968(); // BSR.B	$15968
	DEF_ROMLOC(15962): rom_159B0(); // BSR.B	$159B0
	rom_FD38(); // BRA.W	$FD38
}*/
/*ROMFUNC(rom_15968) {
	DEF_ROMLOC(15968): move_toreg_32(0xFFFFF7E0, &A2); // LEA.L	$F7E0,A2
	DEF_ROMLOC(1596C): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(1596E): move_toreg_8(read_8(A0 + 0x38), &D0); // MOVE.B	56(A0),D0
	DEF_ROMLOC(15972): btst_tomem_8(0x0, (s32)A2 + (s8)0x0 + (s16)D0); // BTST.B	#$00,0(A2,D0)
	DEF_ROMLOC(15978): if (CCR_EQ) goto rom_1598C; // BEQ.B	$1598C
	DEF_ROMLOC(1597A): tst_mem_8(A0 + 0x36); // TST.B	54(A0)
	DEF_ROMLOC(1597E): if (!CCR_EQ) goto rom_15990; // BNE.B	$15990
	DEF_ROMLOC(15980): neg_mem_8(A0 + 0x34); // NEG.B	52(A0)
	DEF_ROMLOC(15984): move_tomem_8(0x1, A0 + 0x36); // MOVE.B	#$01,54(A0)
	DEF_ROMLOC(1598A): goto rom_15990; // BRA.B	$15990
	DEF_ROMLOC(1598C): clr_mem_8(A0 + 0x36); // CLR.B	54(A0)
	DEF_ROMLOC(15990): sub_tomem_8(0x1, A0 + 0x1E); // SUBQ.B	#$01,30(A0)
	DEF_ROMLOC(15994): if (CCR_PL) goto rom_159AE; // BPL.B	$159AE
	DEF_ROMLOC(15996): move_tomem_8(0x7, A0 + 0x1E); // MOVE.B	#$07,30(A0)
	DEF_ROMLOC(1599C): move_toreg_8(read_8(A0 + 0x34), &D1); // MOVE.B	52(A0),D1
	DEF_ROMLOC(159A0): move_toreg_8(read_8(A0 + 0x1A), &D0); // MOVE.B	26(A0),D0
	DEF_ROMLOC(159A4): add_toreg_8(D1, &D0); // ADD.B	D1,D0
	DEF_ROMLOC(159A6): and_toreg_8(0xF, &D0); // ANDI.B	#$0F,D0
	DEF_ROMLOC(159AA): move_tomem_8(D0, A0 + 0x1A); // MOVE.B	D0,26(A0)
	DEF_ROMLOC(159AE): return; // RTS
}*/
/*ROMFUNC(rom_159B0) {
	DEF_ROMLOC(159B0): move_toreg_32(0xFFFFD000, &A1); // LEA.L	$D000,A1
	DEF_ROMLOC(159B4): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(159B6): move_toreg_8(read_8(A0 + 0x1A), &D0); // MOVE.B	26(A0),D0
	DEF_ROMLOC(159BA): add_toreg_16(D0, &D0); // ADD.W	D0,D0
	DEF_ROMLOC(159BC): move_toreg_32(0x159DA + (s16)(D0 & 0xffff), &A2); // LEA.L	28(PC,D0),A2
	DEF_ROMLOC(159C0): move_toreg_8(read_8(A2++), &D0); // MOVE.B	(A2)+,D0
	DEF_ROMLOC(159C2): ext_reg_16(&D0); // EXT.W	D0
	DEF_ROMLOC(159C4): add_toreg_16(read_16(A0 + 0x8), &D0); // ADD.W	8(A0),D0
	DEF_ROMLOC(159C8): move_tomem_16(D0, A1 + 0x8); // MOVE.W	D0,8(A1)
	DEF_ROMLOC(159CC): move_toreg_8(read_8(A2++), &D0); // MOVE.B	(A2)+,D0
	DEF_ROMLOC(159CE): ext_reg_16(&D0); // EXT.W	D0
	DEF_ROMLOC(159D0): add_toreg_16(read_16(A0 + 0xC), &D0); // ADD.W	12(A0),D0
	DEF_ROMLOC(159D4): move_tomem_16(D0, A1 + 0xC); // MOVE.W	D0,12(A1)
	DEF_ROMLOC(159D8): return; // RTS
	DEF_ROMLOC(159DA): asr_toreg_8(0x8, &D0); // ASR.B	#$08,D0
	DEF_ROMLOC(159DC): lsr_toreg_8(0x1, &D6); // LSR.B	#$01,D6
	DEF_ROMLOC(159DE): ror_toreg_8(0x4, &D0); // ROR.B	#$04,D0
	rom_15C4A(); // Detected flow into next function
}*/