/*ROMFUNC(rom_120CA) {
	DEF_ROMLOC(120CA): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(120CC): move_toreg_8(read_8(A0 + 0x24), &D0); // MOVE.B	36(A0),D0
	DEF_ROMLOC(120D0): move_toreg_16(read_16(0x120D8 + (s16)(D0 & 0xffff)), &D1); // MOVE.W	6(PC,D0),D1
	DEF_ROMLOC(120D4): goto rom_120D8 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
}*/
/*ROMFUNC(rom_120E0) {
	DEF_ROMLOC(120E0): add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
	DEF_ROMLOC(120E4): move_tomem_32(0x122FC, A0 + 0x4); // MOVE.L	#$000122FC,4(A0)
	DEF_ROMLOC(120EC): move_tomem_16(0x400, A0 + 0x2); // MOVE.W	#$0400,2(A0)
	DEF_ROMLOC(120F2): or_tomem_8(0x4, A0 + 0x1); // ORI.B	#$04,1(A0)
	DEF_ROMLOC(120F8): move_tomem_8(0x3, A0 + 0x18); // MOVE.B	#$03,24(A0)
	DEF_ROMLOC(120FE): move_tomem_8(0xC, A0 + 0x19); // MOVE.B	#$0C,25(A0)
	DEF_ROMLOC(12104): move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B	40(A0),D0
	DEF_ROMLOC(12108): if (CCR_EQ) goto rom_12110; // BEQ.B	$12110
	DEF_ROMLOC(1210A): move_tomem_8(D0, A0 + 0x24); // MOVE.B	D0,36(A0)
	DEF_ROMLOC(1210E): return; // RTS
}*/
/*ROMFUNC(rom_12110) {
	DEF_ROMLOC(12110): move_tomem_8(0xFFFFFF9A, A0 + 0x20); // MOVE.B	#$9A,32(A0)
	DEF_ROMLOC(12116): bchg_tomem_8(0x0, A0 + 0x22); // BCHG.B	#$00,34(A0)
	rom_1211C(); // Detected flow into next function
}*/
/*ROMFUNC(rom_1211C) {
	DEF_ROMLOC(1211C): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(1211E): move_toreg_8(read_8(A0 + 0x25), &D0); // MOVE.B	37(A0),D0
	DEF_ROMLOC(12122): move_toreg_16(read_16(0x12138 + (s16)(D0 & 0xffff)), &D1); // MOVE.W	20(PC,D0),D1
	DEF_ROMLOC(12126): rom_12138 + (s16)(D1 & 0xffff)(); // JSR	16(PC,D1)
	DEF_ROMLOC(1212A): move_toreg_32(0x122DC, &A1); // LEA.L	$000122DC,A1
	DEF_ROMLOC(12130): rom_ADA2(); // BSR.W	$ADA2
	DEF_ROMLOC(12134): goto rom_FD38; // BRA.W	$FD38
	DEF_ROMLOC(12138): or_toreg_8(0x34, &D6); // ORI.B	#$34,D6
	DEF_ROMLOC(1213C): or_tomem_16(0x6100, (A2 += 2, A2 - 2)); // ORI.W	#$6100,(A2)+
	DEF_ROMLOC(12140): or_tomem_16(0x5368, A6 -= 2); // ORI.W	#$5368,-(A6)
	DEF_ROMLOC(12144): or_tomem_8(0x22, (s32)A0 + (s8)0x28 + (s16)D5); // ORI.B	#$22,40(A0,D5)
	DEF_ROMLOC(1214A): or_tomem_8(0x7C, --A5); // ORI.B	#$7C,-(A5)
	rom_12234(); // Detected flow into next function
}*/
/*ROMFUNC(rom_12234) {
	DEF_ROMLOC(12234): rom_12244(); // BSR.B	$12244
	DEF_ROMLOC(12236): move_toreg_32(0x122DC, &A1); // LEA.L	$000122DC,A1
	DEF_ROMLOC(1223C): rom_ADA2(); // BSR.W	$ADA2
	rom_FD38(); // BRA.W	$FD38
}*/
/*ROMFUNC(rom_12244) {
	DEF_ROMLOC(12244): sub_tomem_16(0x1, A0 + 0x30); // SUBQ.W	#$01,48(A0)
	DEF_ROMLOC(12248): if (CCR_MI) goto rom_12250; // BMI.B	$12250
	DEF_ROMLOC(1224A): rom_DC6C(); // BSR.W	$DC6C
	DEF_ROMLOC(1224E): return; // RTS
}*/
/*ROMFUNC(rom_12250) {
	DEF_ROMLOC(12250): clr_mem_16(A0 + 0x30); // CLR.W	48(A0)
	DEF_ROMLOC(12254): clr_mem_8(A0 + 0x24); // CLR.B	36(A0)
	DEF_ROMLOC(12258): move_tomem_16(read_16(A0 + 0x34), A0 + 0xC); // MOVE.W	52(A0),12(A0)
	DEF_ROMLOC(1225E): move_toreg_32(0x3, &D1); // MOVEQ.L	$03,D1
	DEF_ROMLOC(12260): move_toreg_32(A0, &A1); // MOVEA.L	A0,A1
	DEF_ROMLOC(12262): move_toreg_32(0x122CC, &A2); // LEA.L	$000122CC,A2
	DEF_ROMLOC(12268): goto rom_12270; // BRA.B	$12270
	DEF_ROMLOC(1226A): rom_E130(); // BSR.W	$E130
	DEF_ROMLOC(1226E): if (!CCR_EQ) goto rom_122A2; // BNE.B	$122A2
	DEF_ROMLOC(12270): move_tomem_8(0x5F, A1 + 0x0); // MOVE.B	#$5F,0(A1)
	DEF_ROMLOC(12276): move_tomem_16(read_16(A0 + 0x8), A1 + 0x8); // MOVE.W	8(A0),8(A1)
	DEF_ROMLOC(1227C): move_tomem_16(read_16(A0 + 0xC), A1 + 0xC); // MOVE.W	12(A0),12(A1)
	DEF_ROMLOC(12282): move_tomem_8(0x6, A1 + 0x28); // MOVE.B	#$06,40(A1)
	DEF_ROMLOC(12288): move_tomem_8(0x4, A1 + 0x1C); // MOVE.B	#$04,28(A1)
	DEF_ROMLOC(1228E): move_tomem_16(read_16((A2 += 2, A2 - 2)), A1 + 0x10); // MOVE.W	(A2)+,16(A1)
	DEF_ROMLOC(12292): move_tomem_16(read_16((A2 += 2, A2 - 2)), A1 + 0x12); // MOVE.W	(A2)+,18(A1)
	DEF_ROMLOC(12296): move_tomem_8(0xFFFFFF98, A1 + 0x20); // MOVE.B	#$98,32(A1)
	DEF_ROMLOC(1229C): bset_tomem_8(0x7, A1 + 0x1); // BSET.B	#$07,1(A1)
	DEF_ROMLOC(122A2): dec_reg_16(&D1); if ((D1 & 0xffff) != 0xffff) goto rom_1226A; // DBF.W	D1,$1226A
	DEF_ROMLOC(122A6): move_tomem_8(0x6, A0 + 0x24); // MOVE.B	#$06,36(A0)
	rom_122AC(); // Detected flow into next function
}*/
/*ROMFUNC(rom_122AC) {
	DEF_ROMLOC(122AC): rom_DC6C(); // BSR.W	$DC6C
	DEF_ROMLOC(122B0): add_tomem_16(0x18, A0 + 0x12); // ADDI.W	#$0018,18(A0)
	DEF_ROMLOC(122B6): move_toreg_32(0x122DC, &A1); // LEA.L	$000122DC,A1
	DEF_ROMLOC(122BC): rom_ADA2(); // BSR.W	$ADA2
	DEF_ROMLOC(122C0): tst_mem_8(A0 + 0x1); // TST.B	1(A0)
	DEF_ROMLOC(122C4): if (CCR_PL) goto rom_DCCE; // BPL.W	$DCCE
	rom_DC92(); // BRA.W	$DC92
}*/