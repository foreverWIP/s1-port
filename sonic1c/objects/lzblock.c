/*ROMFUNC(rom_126A8) {
	DEF_ROMLOC(126A8): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(126AA): move_toreg_8(read_8(A0 + 0x24), &D0); // MOVE.B	36(A0),D0
	DEF_ROMLOC(126AE): move_toreg_16(read_16(0x126B6 + (s16)(D0 & 0xffff)), &D1); // MOVE.W	6(PC,D0),D1
	DEF_ROMLOC(126B2): goto rom_126B6 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
}*/
/*ROMFUNC(rom_126BA) {
	DEF_ROMLOC(126BA): move_toreg_8(read_8(A0), &D0); // MOVE.B	(A0),D0
	DEF_ROMLOC(126BC): move_toreg_32(A4, &D0); // MOVE.L	A4,D0
	DEF_ROMLOC(126BE): move_toreg_8(read_8(A0), &D0); // MOVE.B	(A0),D0
	DEF_ROMLOC(126C0): move_toreg_8(read_8(A0), &D0); // MOVE.B	(A0),D0
	rom_126C2(); // Detected flow into next function
}*/
/*ROMFUNC(rom_126C2) {
	DEF_ROMLOC(126C2): add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
	DEF_ROMLOC(126C6): move_tomem_32(0x12896, A0 + 0x4); // MOVE.L	#$00012896,4(A0)
	DEF_ROMLOC(126CE): move_tomem_16(0x43E6, A0 + 0x2); // MOVE.W	#$43E6,2(A0)
	DEF_ROMLOC(126D4): move_tomem_8(0x4, A0 + 0x1); // MOVE.B	#$04,1(A0)
	DEF_ROMLOC(126DA): move_tomem_8(0x3, A0 + 0x18); // MOVE.B	#$03,24(A0)
	DEF_ROMLOC(126E0): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(126E2): move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B	40(A0),D0
	DEF_ROMLOC(126E6): lsr_toreg_16(0x3, &D0); // LSR.W	#$03,D0
	DEF_ROMLOC(126E8): and_toreg_16(0xE, &D0); // ANDI.W	#$000E,D0
	DEF_ROMLOC(126EC): move_toreg_32(0x126BA + (s16)(D0 & 0xffff), &A2); // LEA.L	-52(PC,D0),A2
	DEF_ROMLOC(126F0): move_tomem_8(read_8(A2++), A0 + 0x19); // MOVE.B	(A2)+,25(A0)
	DEF_ROMLOC(126F4): move_tomem_8(read_8(A2), A0 + 0x16); // MOVE.B	(A2),22(A0)
	DEF_ROMLOC(126F8): lsr_toreg_16(0x1, &D0); // LSR.W	#$01,D0
	DEF_ROMLOC(126FA): move_tomem_8(D0, A0 + 0x1A); // MOVE.B	D0,26(A0)
	DEF_ROMLOC(126FE): move_tomem_16(read_16(A0 + 0x8), A0 + 0x34); // MOVE.W	8(A0),52(A0)
	DEF_ROMLOC(12704): move_tomem_16(read_16(A0 + 0xC), A0 + 0x30); // MOVE.W	12(A0),48(A0)
	DEF_ROMLOC(1270A): move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B	40(A0),D0
	DEF_ROMLOC(1270E): and_toreg_8(0xF, &D0); // ANDI.B	#$0F,D0
	DEF_ROMLOC(12712): if (CCR_EQ) goto rom_12720; // BEQ.B	$12720
	DEF_ROMLOC(12714): cmp_toreg_8(0x7, &D0); // CMPI.B	#$07,D0
	DEF_ROMLOC(12718): if (CCR_EQ) goto rom_12720; // BEQ.B	$12720
	DEF_ROMLOC(1271A): move_tomem_8(0x1, A0 + 0x38); // MOVE.B	#$01,56(A0)
	rom_12720(); // Detected flow into next function
}*/
/*ROMFUNC(rom_12720) {
	DEF_ROMLOC(12720): move_tomem_16(read_16(A0 + 0x8), A7 -= 2); // MOVE.W	8(A0),-(A7)
	DEF_ROMLOC(12724): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(12726): move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B	40(A0),D0
	DEF_ROMLOC(1272A): and_toreg_16(0xF, &D0); // ANDI.W	#$000F,D0
	DEF_ROMLOC(1272E): add_toreg_16(D0, &D0); // ADD.W	D0,D0
	DEF_ROMLOC(12730): move_toreg_16(read_16(0x12782 + (s16)(D0 & 0xffff)), &D1); // MOVE.W	80(PC,D0),D1
	DEF_ROMLOC(12734): rom_12782 + (s16)(D1 & 0xffff)(); // JSR	76(PC,D1)
	DEF_ROMLOC(12738): move_toreg_16(read_16((A7 += 2, A7 - 2)), &D4); // MOVE.W	(A7)+,D4
	DEF_ROMLOC(1273A): tst_mem_8(A0 + 0x1); // TST.B	1(A0)
	DEF_ROMLOC(1273E): if (CCR_PL) goto rom_12760; // BPL.B	$12760
	DEF_ROMLOC(12740): move_toreg_32(0x0, &D1); // MOVEQ.L	$00,D1
	DEF_ROMLOC(12742): move_toreg_8(read_8(A0 + 0x19), &D1); // MOVE.B	25(A0),D1
	DEF_ROMLOC(12746): add_toreg_16(0xB, &D1); // ADDI.W	#$000B,D1
	DEF_ROMLOC(1274A): move_toreg_32(0x0, &D2); // MOVEQ.L	$00,D2
	DEF_ROMLOC(1274C): move_toreg_8(read_8(A0 + 0x16), &D2); // MOVE.B	22(A0),D2
	DEF_ROMLOC(12750): move_toreg_16(D2, &D3); // MOVE.W	D2,D3
	DEF_ROMLOC(12752): add_toreg_16(0x1, &D3); // ADDQ.W	#$01,D3
	DEF_ROMLOC(12754): rom_10062(); // BSR.W	$10062
	DEF_ROMLOC(12758): move_tomem_8(D4, A0 + 0x3F); // MOVE.B	D4,63(A0)
	DEF_ROMLOC(1275C): rom_12854(); // BSR.W	$12854
	DEF_ROMLOC(12760): move_toreg_16(read_16(A0 + 0x34), &D0); // MOVE.W	52(A0),D0
	DEF_ROMLOC(12764): and_toreg_16(0xFFFFFF80, &D0); // ANDI.W	#$FF80,D0
	DEF_ROMLOC(12768): move_toreg_16(read_16(0xFFFFF700), &D1); // MOVE.W	$F700,D1
	DEF_ROMLOC(1276C): sub_toreg_16(0x80, &D1); // SUBI.W	#$0080,D1
	DEF_ROMLOC(12770): and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
	DEF_ROMLOC(12774): sub_toreg_16(D1, &D0); // SUB.W	D1,D0
	DEF_ROMLOC(12776): cmp_toreg_16(0x280, &D0); // CMPI.W	#$0280,D0
	DEF_ROMLOC(1277A): if (CCR_HI) goto rom_DCCE; // BHI.W	$DCCE
	DEF_ROMLOC(1277E): goto rom_DC92; // BRA.W	$DC92
	DEF_ROMLOC(12782): or_tomem_8(0x12, A0); // ORI.B	#$12,(A0)
	DEF_ROMLOC(12786): or_tomem_8(0x12, 0x5A); // ORI.B	#$12,$005A
	rom_12854(); // Detected flow into next function
}*/
/*ROMFUNC(rom_12854) {
	DEF_ROMLOC(12854): tst_mem_8(A0 + 0x38); // TST.B	56(A0)
	DEF_ROMLOC(12858): if (CCR_EQ) goto rom_12894; // BEQ.B	$12894
	DEF_ROMLOC(1285A): btst_tomem_8(0x3, A0 + 0x22); // BTST.B	#$03,34(A0)
	DEF_ROMLOC(12860): if (!CCR_EQ) goto rom_1286E; // BNE.B	$1286E
	DEF_ROMLOC(12862): tst_mem_8(A0 + 0x3E); // TST.B	62(A0)
	DEF_ROMLOC(12866): if (CCR_EQ) goto rom_12894; // BEQ.B	$12894
	DEF_ROMLOC(12868): sub_tomem_8(0x4, A0 + 0x3E); // SUBQ.B	#$04,62(A0)
	rom_1287A(); // BRA.B	$1287A
}*/
/*ROMFUNC(rom_1286E) {
	DEF_ROMLOC(1286E): cmp_tomem_8(0x40, A0 + 0x3E); // CMPI.B	#$40,62(A0)
	DEF_ROMLOC(12874): if (CCR_EQ) goto rom_12894; // BEQ.B	$12894
	DEF_ROMLOC(12876): add_tomem_8(0x4, A0 + 0x3E); // ADDQ.B	#$04,62(A0)
	rom_1287A(); // Detected flow into next function
}*/
/*ROMFUNC(rom_1287A) {
	DEF_ROMLOC(1287A): move_toreg_8(read_8(A0 + 0x3E), &D0); // MOVE.B	62(A0),D0
	DEF_ROMLOC(1287E): rom_29D2(); // JSR	$000029D2
	DEF_ROMLOC(12884): move_toreg_16(0x400, &D1); // MOVE.W	#$0400,D1
	DEF_ROMLOC(12888): muls_toreg_16(D1, &D0); // MULS.W	D1,D0
	DEF_ROMLOC(1288A): swap_reg_16(&D0); // SWAP.W	D0
	DEF_ROMLOC(1288C): add_toreg_16(read_16(A0 + 0x30), &D0); // ADD.W	48(A0),D0
	DEF_ROMLOC(12890): move_tomem_16(D0, A0 + 0xC); // MOVE.W	D0,12(A0)
	rom_12894(); // Detected flow into next function
}*/
/*ROMFUNC(rom_12894) {
	DEF_ROMLOC(12894): return; // RTS
}*/