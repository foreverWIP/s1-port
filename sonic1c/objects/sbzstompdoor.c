/*ROMFUNC(rom_1637A) {
	DEF_ROMLOC(1637A): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(1637C): move_toreg_8(read_8(A0 + 0x24), &D0); // MOVE.B	36(A0),D0
	DEF_ROMLOC(16380): move_toreg_16(read_16(0x16388 + (s16)(D0 & 0xffff)), &D1); // MOVE.W	6(PC,D0),D1
	DEF_ROMLOC(16384): goto rom_16388 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
	DEF_ROMLOC(16388): or_tomem_8(0xFFFFFFEA, A0++); // ORI.B	#$EA,(A0)+
	rom_1638C(); // Detected flow into next function
}*/
/*ROMFUNC(rom_163A0) {
	DEF_ROMLOC(163A0): add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
	DEF_ROMLOC(163A4): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(163A6): move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B	40(A0),D0
	DEF_ROMLOC(163AA): lsr_toreg_16(0x2, &D0); // LSR.W	#$02,D0
	DEF_ROMLOC(163AC): and_toreg_16(0x1C, &D0); // ANDI.W	#$001C,D0
	DEF_ROMLOC(163B0): move_toreg_32(0x1638C + (s16)(D0 & 0xffff), &A3); // LEA.L	-38(PC,D0),A3
	DEF_ROMLOC(163B4): move_tomem_8(read_8(A3++), A0 + 0x19); // MOVE.B	(A3)+,25(A0)
	DEF_ROMLOC(163B8): move_tomem_8(read_8(A3++), A0 + 0x16); // MOVE.B	(A3)+,22(A0)
	DEF_ROMLOC(163BC): lsr_toreg_16(0x2, &D0); // LSR.W	#$02,D0
	DEF_ROMLOC(163BE): move_tomem_8(D0, A0 + 0x1A); // MOVE.B	D0,26(A0)
	DEF_ROMLOC(163C2): move_tomem_32(0x166D0, A0 + 0x4); // MOVE.L	#$000166D0,4(A0)
	DEF_ROMLOC(163CA): move_tomem_16(0x22C0, A0 + 0x2); // MOVE.W	#$22C0,2(A0)
	DEF_ROMLOC(163D0): cmp_tomem_8(0x1, 0xFFFFFE10); // CMPI.B	#$01,$FE10
	DEF_ROMLOC(163D6): if (!CCR_EQ) goto rom_16420; // BNE.B	$16420
	DEF_ROMLOC(163D8): bset_tomem_8(0x0, 0xFFFFF7CB); // BSET.B	#$00,$F7CB
	DEF_ROMLOC(163DE): if (CCR_EQ) goto rom_163F8; // BEQ.B	$163F8
	DEF_ROMLOC(163E0): move_toreg_32(0xFFFFFC00, &A2); // LEA.L	$FC00,A2
	DEF_ROMLOC(163E4): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(163E6): move_toreg_8(read_8(A0 + 0x23), &D0); // MOVE.B	35(A0),D0
	DEF_ROMLOC(163EA): if (CCR_EQ) goto rom_163F2; // BEQ.B	$163F2
	DEF_ROMLOC(163EC): bclr_tomem_8(0x7, (s32)A2 + (s8)0x2 + (s16)D0); // BCLR.B	#$07,2(A2,D0)
	DEF_ROMLOC(163F2): goto rom_DCCE; // JMP	$0000DCCE
	DEF_ROMLOC(163F8): move_tomem_16(0x41F0, A0 + 0x2); // MOVE.W	#$41F0,2(A0)
	DEF_ROMLOC(163FE): cmp_tomem_16(0xA80, A0 + 0x8); // CMPI.W	#$0A80,8(A0)
	DEF_ROMLOC(16404): if (!CCR_EQ) goto rom_16420; // BNE.B	$16420
	DEF_ROMLOC(16406): move_toreg_32(0xFFFFFC00, &A2); // LEA.L	$FC00,A2
	DEF_ROMLOC(1640A): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(1640C): move_toreg_8(read_8(A0 + 0x23), &D0); // MOVE.B	35(A0),D0
	DEF_ROMLOC(16410): if (CCR_EQ) goto rom_16420; // BEQ.B	$16420
	DEF_ROMLOC(16412): btst_tomem_8(0x0, (s32)A2 + (s8)0x2 + (s16)D0); // BTST.B	#$00,2(A2,D0)
	DEF_ROMLOC(16418): if (CCR_EQ) goto rom_16420; // BEQ.B	$16420
	DEF_ROMLOC(1641A): clr_mem_8(0xFFFFF7CB); // CLR.B	$F7CB
	DEF_ROMLOC(1641E): goto rom_163E0; // BRA.B	$163E0
	DEF_ROMLOC(16420): or_tomem_8(0x4, A0 + 0x1); // ORI.B	#$04,1(A0)
	DEF_ROMLOC(16426): move_tomem_8(0x4, A0 + 0x18); // MOVE.B	#$04,24(A0)
	DEF_ROMLOC(1642C): move_tomem_16(read_16(A0 + 0x8), A0 + 0x34); // MOVE.W	8(A0),52(A0)
	DEF_ROMLOC(16432): move_tomem_16(read_16(A0 + 0xC), A0 + 0x30); // MOVE.W	12(A0),48(A0)
	DEF_ROMLOC(16438): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(1643A): move_toreg_8(read_8(A3++), &D0); // MOVE.B	(A3)+,D0
	DEF_ROMLOC(1643C): move_tomem_16(D0, A0 + 0x3C); // MOVE.W	D0,60(A0)
	DEF_ROMLOC(16440): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(16442): move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B	40(A0),D0
	DEF_ROMLOC(16446): if (CCR_PL) goto rom_16472; // BPL.B	$16472
	DEF_ROMLOC(16448): and_toreg_8(0xF, &D0); // ANDI.B	#$0F,D0
	DEF_ROMLOC(1644C): move_tomem_8(D0, A0 + 0x3E); // MOVE.B	D0,62(A0)
	DEF_ROMLOC(16450): move_tomem_8(read_8(A3), A0 + 0x28); // MOVE.B	(A3),40(A0)
	DEF_ROMLOC(16454): cmp_tomem_8(0x5, A3); // CMPI.B	#$05,(A3)
	DEF_ROMLOC(16458): if (!CCR_EQ) goto rom_16460; // BNE.B	$16460
	DEF_ROMLOC(1645A): bset_tomem_8(0x4, A0 + 0x1); // BSET.B	#$04,1(A0)
	DEF_ROMLOC(16460): move_toreg_32(0xFFFFFC00, &A2); // LEA.L	$FC00,A2
	DEF_ROMLOC(16464): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(16466): move_toreg_8(read_8(A0 + 0x23), &D0); // MOVE.B	35(A0),D0
	DEF_ROMLOC(1646A): if (CCR_EQ) goto rom_16472; // BEQ.B	$16472
	DEF_ROMLOC(1646C): bclr_tomem_8(0x7, (s32)A2 + (s8)0x2 + (s16)D0); // BCLR.B	#$07,2(A2,D0)
	rom_16472(); // Detected flow into next function
}*/
/*ROMFUNC(rom_16472) {
	DEF_ROMLOC(16472): move_tomem_16(read_16(A0 + 0x8), A7 -= 2); // MOVE.W	8(A0),-(A7)
	DEF_ROMLOC(16476): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(16478): move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B	40(A0),D0
	DEF_ROMLOC(1647C): and_toreg_16(0xF, &D0); // ANDI.W	#$000F,D0
	DEF_ROMLOC(16480): add_toreg_16(D0, &D0); // ADD.W	D0,D0
	DEF_ROMLOC(16482): move_toreg_16(read_16(0x164F0 + (s16)(D0 & 0xffff)), &D1); // MOVE.W	108(PC,D0),D1
	DEF_ROMLOC(16486): rom_164F0 + (s16)(D1 & 0xffff)(); // JSR	104(PC,D1)
	DEF_ROMLOC(1648A): move_toreg_16(read_16((A7 += 2, A7 - 2)), &D4); // MOVE.W	(A7)+,D4
	DEF_ROMLOC(1648C): tst_mem_8(A0 + 0x1); // TST.B	1(A0)
	DEF_ROMLOC(16490): if (CCR_PL) goto rom_164AA; // BPL.B	$164AA
	DEF_ROMLOC(16492): move_toreg_32(0x0, &D1); // MOVEQ.L	$00,D1
	DEF_ROMLOC(16494): move_toreg_8(read_8(A0 + 0x19), &D1); // MOVE.B	25(A0),D1
	DEF_ROMLOC(16498): add_toreg_16(0xB, &D1); // ADDI.W	#$000B,D1
	DEF_ROMLOC(1649C): move_toreg_32(0x0, &D2); // MOVEQ.L	$00,D2
	DEF_ROMLOC(1649E): move_toreg_8(read_8(A0 + 0x16), &D2); // MOVE.B	22(A0),D2
	DEF_ROMLOC(164A2): move_toreg_16(D2, &D3); // MOVE.W	D2,D3
	DEF_ROMLOC(164A4): add_toreg_16(0x1, &D3); // ADDQ.W	#$01,D3
	DEF_ROMLOC(164A6): rom_10062(); // BSR.W	$10062
	DEF_ROMLOC(164AA): move_toreg_16(read_16(A0 + 0x34), &D0); // MOVE.W	52(A0),D0
	DEF_ROMLOC(164AE): and_toreg_16(0xFFFFFF80, &D0); // ANDI.W	#$FF80,D0
	DEF_ROMLOC(164B2): move_toreg_16(read_16(0xFFFFF700), &D1); // MOVE.W	$F700,D1
	DEF_ROMLOC(164B6): sub_toreg_16(0x80, &D1); // SUBI.W	#$0080,D1
	DEF_ROMLOC(164BA): and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
	DEF_ROMLOC(164BE): sub_toreg_16(D1, &D0); // SUB.W	D1,D0
	DEF_ROMLOC(164C0): cmp_toreg_16(0x280, &D0); // CMPI.W	#$0280,D0
	DEF_ROMLOC(164C4): if (CCR_HI) goto rom_164CC; // BHI.B	$164CC
	DEF_ROMLOC(164C6): goto rom_DC92; // JMP	$0000DC92
	DEF_ROMLOC(164CC): cmp_tomem_8(0x1, 0xFFFFFE10); // CMPI.B	#$01,$FE10
	DEF_ROMLOC(164D2): if (!CCR_EQ) goto rom_164EA; // BNE.B	$164EA
	DEF_ROMLOC(164D4): clr_mem_8(0xFFFFF7CB); // CLR.B	$F7CB
	DEF_ROMLOC(164D8): move_toreg_32(0xFFFFFC00, &A2); // LEA.L	$FC00,A2
	DEF_ROMLOC(164DC): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(164DE): move_toreg_8(read_8(A0 + 0x23), &D0); // MOVE.B	35(A0),D0
	DEF_ROMLOC(164E2): if (CCR_EQ) goto rom_164EA; // BEQ.B	$164EA
	DEF_ROMLOC(164E4): bclr_tomem_8(0x7, (s32)A2 + (s8)0x2 + (s16)D0); // BCLR.B	#$07,2(A2,D0)
	DEF_ROMLOC(164EA): goto rom_DCCE; // JMP	$0000DCCE
}*/