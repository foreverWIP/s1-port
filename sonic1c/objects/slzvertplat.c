/*ROMFUNC(rom_111A6) {
	DEF_ROMLOC(111A6): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(111A8): move_toreg_8(read_8(A0 + 0x24), &D0); // MOVE.B	36(A0),D0
	DEF_ROMLOC(111AC): move_toreg_16(read_16(0x111D6 + (s16)(D0 & 0xffff)), &D1); // MOVE.W	40(PC,D0),D1
	DEF_ROMLOC(111B0): rom_111D6 + (s16)(D1 & 0xffff)(); // JSR	36(PC,D1)
	DEF_ROMLOC(111B4): move_toreg_16(read_16(A0 + 0x32), &D0); // MOVE.W	50(A0),D0
	DEF_ROMLOC(111B8): and_toreg_16(0xFFFFFF80, &D0); // ANDI.W	#$FF80,D0
	DEF_ROMLOC(111BC): move_toreg_16(read_16(0xFFFFF700), &D1); // MOVE.W	$F700,D1
	DEF_ROMLOC(111C0): sub_toreg_16(0x80, &D1); // SUBI.W	#$0080,D1
	DEF_ROMLOC(111C4): and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
	DEF_ROMLOC(111C8): sub_toreg_16(D1, &D0); // SUB.W	D1,D0
	DEF_ROMLOC(111CA): cmp_toreg_16(0x280, &D0); // CMPI.W	#$0280,D0
	DEF_ROMLOC(111CE): if (CCR_HI) goto rom_DCCE; // BHI.W	$DCCE
	DEF_ROMLOC(111D2): goto rom_DC92; // BRA.W	$DC92
	DEF_ROMLOC(111D6): or_tomem_8(0xFFFFFFA0, A0 + 0xB0); // ORI.B	#$A0,176(A0)
	rom_111DE(); // Detected flow into next function
}*/
/*ROMFUNC(rom_111DE) {
	DEF_ROMLOC(111DE): move_toreg_32(D0, &D4); // MOVE.L	D0,D4
	rom_111E0(); // Detected flow into next function
}*/
/*ROMFUNC(rom_111E0) {
	DEF_ROMLOC(111E0): move_toreg_8(D1, &D0); // MOVE.B	D1,D0
	DEF_ROMLOC(111E2): move_toreg_32(D1, &D0); // MOVE.L	D1,D0
	DEF_ROMLOC(111E4): move_toreg_16(D1, &D2); // MOVE.W	D1,D2
	DEF_ROMLOC(111E6): move_toreg_8(D3, &D0); // MOVE.B	D3,D0
	DEF_ROMLOC(111E8): move_toreg_32(D3, &D0); // MOVE.L	D3,D0
	DEF_ROMLOC(111EA): move_toreg_16(D3, &D2); // MOVE.W	D3,D2
	DEF_ROMLOC(111EC): move_toreg_8(D1, &D2); // MOVE.B	D1,D2
	DEF_ROMLOC(111EE): move_toreg_32(D1, &D2); // MOVE.L	D1,D2
	DEF_ROMLOC(111F0): move_toreg_32(D1, &D6); // MOVE.L	D1,D6
	DEF_ROMLOC(111F2): move_toreg_8(D3, &D2); // MOVE.B	D3,D2
	DEF_ROMLOC(111F4): move_toreg_32(D3, &D2); // MOVE.L	D3,D2
	DEF_ROMLOC(111F6): move_toreg_32(D3, &D6); // MOVE.L	D3,D6
	DEF_ROMLOC(111F8): move_toreg_32(D5, &D0); // MOVE.L	D5,D0
	DEF_ROMLOC(111FA): move_toreg_32(D7, &D0); // MOVE.L	D7,D0
	DEF_ROMLOC(111FC): move_toreg_16(A1, &D0); // MOVE.W	A1,D0
	rom_111FE(); // Detected flow into next function
}*/
/*ROMFUNC(rom_111FE) {
	DEF_ROMLOC(111FE): add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
	DEF_ROMLOC(11202): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(11204): move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B	40(A0),D0
	DEF_ROMLOC(11208): if (CCR_PL) goto rom_11222; // BPL.B	$11222
	DEF_ROMLOC(1120A): add_tomem_8(0x4, A0 + 0x24); // ADDQ.B	#$04,36(A0)
	DEF_ROMLOC(1120E): and_toreg_16(0x7F, &D0); // ANDI.W	#$007F,D0
	DEF_ROMLOC(11212): mulu_toreg_16(0x6, &D0); // MULU.W	#$0006,D0
	DEF_ROMLOC(11216): move_tomem_16(D0, A0 + 0x3C); // MOVE.W	D0,60(A0)
	DEF_ROMLOC(1121A): move_tomem_16(D0, A0 + 0x3E); // MOVE.W	D0,62(A0)
	DEF_ROMLOC(1121E): // TODO; // ADDQ.L	#$04,A7
	DEF_ROMLOC(11220): return; // RTS
	DEF_ROMLOC(11222): lsr_toreg_16(0x3, &D0); // LSR.W	#$03,D0
	DEF_ROMLOC(11224): and_toreg_16(0x1E, &D0); // ANDI.W	#$001E,D0
	DEF_ROMLOC(11228): move_toreg_32(0x111DE + (s16)(D0 & 0xffff), &A2); // LEA.L	-76(PC,D0),A2
	DEF_ROMLOC(1122C): move_tomem_8(read_8(A2++), A0 + 0x19); // MOVE.B	(A2)+,25(A0)
	DEF_ROMLOC(11230): move_tomem_8(read_8(A2++), A0 + 0x1A); // MOVE.B	(A2)+,26(A0)
	DEF_ROMLOC(11234): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(11236): move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B	40(A0),D0
	DEF_ROMLOC(1123A): add_toreg_16(D0, &D0); // ADD.W	D0,D0
	DEF_ROMLOC(1123C): and_toreg_16(0x1E, &D0); // ANDI.W	#$001E,D0
	DEF_ROMLOC(11240): move_toreg_32(0x111E0 + (s16)(D0 & 0xffff), &A2); // LEA.L	-98(PC,D0),A2
	DEF_ROMLOC(11244): move_toreg_8(read_8(A2++), &D0); // MOVE.B	(A2)+,D0
	DEF_ROMLOC(11246): lsl_toreg_16(0x2, &D0); // LSL.W	#$02,D0
	DEF_ROMLOC(11248): move_tomem_16(D0, A0 + 0x3C); // MOVE.W	D0,60(A0)
	DEF_ROMLOC(1124C): move_tomem_8(read_8(A2++), A0 + 0x28); // MOVE.B	(A2)+,40(A0)
	DEF_ROMLOC(11250): move_tomem_32(0x1141C, A0 + 0x4); // MOVE.L	#$0001141C,4(A0)
	DEF_ROMLOC(11258): move_tomem_16(0x4000, A0 + 0x2); // MOVE.W	#$4000,2(A0)
	DEF_ROMLOC(1125E): move_tomem_8(0x4, A0 + 0x1); // MOVE.B	#$04,1(A0)
	DEF_ROMLOC(11264): move_tomem_8(0x4, A0 + 0x18); // MOVE.B	#$04,24(A0)
	DEF_ROMLOC(1126A): move_tomem_16(read_16(A0 + 0x8), A0 + 0x32); // MOVE.W	8(A0),50(A0)
	DEF_ROMLOC(11270): move_tomem_16(read_16(A0 + 0xC), A0 + 0x30); // MOVE.W	12(A0),48(A0)
	rom_11276(); // Detected flow into next function
}*/
/*ROMFUNC(rom_11276) {
	DEF_ROMLOC(11276): move_toreg_32(0x0, &D1); // MOVEQ.L	$00,D1
	DEF_ROMLOC(11278): move_toreg_8(read_8(A0 + 0x19), &D1); // MOVE.B	25(A0),D1
	DEF_ROMLOC(1127C): rom_7ACA(); // JSR	$00007ACA
	rom_112AA(); // BRA.W	$112AA
}*/
/*ROMFUNC(rom_11286) {
	DEF_ROMLOC(11286): move_toreg_32(0x0, &D1); // MOVEQ.L	$00,D1
	DEF_ROMLOC(11288): move_toreg_8(read_8(A0 + 0x19), &D1); // MOVE.B	25(A0),D1
	DEF_ROMLOC(1128C): rom_7C3E(); // JSR	$00007C3E
	DEF_ROMLOC(11292): move_tomem_16(read_16(A0 + 0x8), A7 -= 2); // MOVE.W	8(A0),-(A7)
	DEF_ROMLOC(11296): rom_112AA(); // BSR.W	$112AA
	DEF_ROMLOC(1129A): move_toreg_16(read_16((A7 += 2, A7 - 2)), &D2); // MOVE.W	(A7)+,D2
	DEF_ROMLOC(1129C): tst_mem_8(A0 + 0x0); // TST.B	0(A0)
	DEF_ROMLOC(112A0): if (CCR_EQ) goto rom_112A8; // BEQ.B	$112A8
	DEF_ROMLOC(112A2): goto rom_81AC; // JMP	$000081AC
	DEF_ROMLOC(112A8): return; // RTS
}*/
/*ROMFUNC(rom_112AA) {
	DEF_ROMLOC(112AA): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(112AC): move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B	40(A0),D0
	DEF_ROMLOC(112B0): and_toreg_16(0xF, &D0); // ANDI.W	#$000F,D0
	DEF_ROMLOC(112B4): add_toreg_16(D0, &D0); // ADD.W	D0,D0
	DEF_ROMLOC(112B6): move_toreg_16(read_16(0x112BE + (s16)(D0 & 0xffff)), &D1); // MOVE.W	6(PC,D0),D1
	DEF_ROMLOC(112BA): goto rom_112BE + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
	DEF_ROMLOC(112BE): or_tomem_8(0x16, A4); // ORI.B	#$16,(A4)
	DEF_ROMLOC(112C2): or_tomem_8(0x16, --A4); // ORI.B	#$16,-(A4)
	DEF_ROMLOC(112C6): or_tomem_8(0x16, 0x4A); // ORI.B	#$16,$004A
	DEF_ROMLOC(112CC): or_tomem_8(0x6C, A6); // ORI.B	#$6C,(A6)
	rom_11386(); // Detected flow into next function
}*/
/*ROMFUNC(rom_11386) {
	DEF_ROMLOC(11386): move_toreg_16(read_16(A0 + 0x38), &D0); // MOVE.W	56(A0),D0
	DEF_ROMLOC(1138A): tst_mem_8(A0 + 0x3A); // TST.B	58(A0)
	DEF_ROMLOC(1138E): if (!CCR_EQ) goto rom_1139C; // BNE.B	$1139C
	DEF_ROMLOC(11390): cmp_toreg_16(0x800, &D0); // CMPI.W	#$0800,D0
	DEF_ROMLOC(11394): if (CCR_CC) goto rom_113A4; // BCC.B	$113A4
	DEF_ROMLOC(11396): add_toreg_16(0x10, &D0); // ADDI.W	#$0010,D0
	rom_113A4(); // BRA.B	$113A4
}*/
/*ROMFUNC(rom_1139C) {
	DEF_ROMLOC(1139C): tst_reg_16(&D0); // TST.W	D0
	DEF_ROMLOC(1139E): if (CCR_EQ) goto rom_113A4; // BEQ.B	$113A4
	DEF_ROMLOC(113A0): sub_toreg_16(0x10, &D0); // SUBI.W	#$0010,D0
	rom_113A4(); // Detected flow into next function
}*/
/*ROMFUNC(rom_113A4) {
	DEF_ROMLOC(113A4): move_tomem_16(D0, A0 + 0x38); // MOVE.W	D0,56(A0)
	DEF_ROMLOC(113A8): ext_reg_32(&D0); // EXT.L	D0
	DEF_ROMLOC(113AA): asl_toreg_32(0x8, &D0); // ASL.L	#$08,D0
	DEF_ROMLOC(113AC): add_toreg_32(read_32(A0 + 0x34), &D0); // ADD.L	52(A0),D0
	DEF_ROMLOC(113B0): move_tomem_32(D0, A0 + 0x34); // MOVE.L	D0,52(A0)
	DEF_ROMLOC(113B4): swap_reg_16(&D0); // SWAP.W	D0
	DEF_ROMLOC(113B6): move_toreg_16(read_16(A0 + 0x3C), &D2); // MOVE.W	60(A0),D2
	DEF_ROMLOC(113BA): cmp_toreg_16(D2, &D0); // CMP.W	D2,D0
	DEF_ROMLOC(113BC): if (CCR_LS) goto rom_113C4; // BLS.B	$113C4
	DEF_ROMLOC(113BE): move_tomem_8(0x1, A0 + 0x3A); // MOVE.B	#$01,58(A0)
	rom_113C4(); // Detected flow into next function
}*/
/*ROMFUNC(rom_113C4) {
	DEF_ROMLOC(113C4): add_toreg_16(D2, &D2); // ADD.W	D2,D2
	DEF_ROMLOC(113C6): cmp_toreg_16(D2, &D0); // CMP.W	D2,D0
	DEF_ROMLOC(113C8): if (!CCR_EQ) goto rom_113CE; // BNE.B	$113CE
	DEF_ROMLOC(113CA): clr_mem_8(A0 + 0x28); // CLR.B	40(A0)
	rom_113CE(); // Detected flow into next function
}*/
/*ROMFUNC(rom_113CE) {
	DEF_ROMLOC(113CE): return; // RTS
}*/
/*ROMFUNC(rom_113D0) {
	DEF_ROMLOC(113D0): sub_tomem_16(0x1, A0 + 0x3C); // SUBQ.W	#$01,60(A0)
	DEF_ROMLOC(113D4): if (!CCR_EQ) goto rom_113FA; // BNE.B	$113FA
	DEF_ROMLOC(113D6): move_tomem_16(read_16(A0 + 0x3E), A0 + 0x3C); // MOVE.W	62(A0),60(A0)
	DEF_ROMLOC(113DC): rom_E11A(); // BSR.W	$E11A
	DEF_ROMLOC(113E0): if (!CCR_EQ) goto rom_113FA; // BNE.B	$113FA
	DEF_ROMLOC(113E2): move_tomem_8(0x59, A1 + 0x0); // MOVE.B	#$59,0(A1)
	DEF_ROMLOC(113E8): move_tomem_16(read_16(A0 + 0x8), A1 + 0x8); // MOVE.W	8(A0),8(A1)
	DEF_ROMLOC(113EE): move_tomem_16(read_16(A0 + 0xC), A1 + 0xC); // MOVE.W	12(A0),12(A1)
	DEF_ROMLOC(113F4): move_tomem_8(0xE, A1 + 0x28); // MOVE.B	#$0E,40(A1)
	DEF_ROMLOC(113FA): // TODO; // ADDQ.L	#$04,A7
	DEF_ROMLOC(113FC): move_toreg_16(read_16(A0 + 0x8), &D0); // MOVE.W	8(A0),D0
	DEF_ROMLOC(11400): and_toreg_16(0xFFFFFF80, &D0); // ANDI.W	#$FF80,D0
	DEF_ROMLOC(11404): move_toreg_16(read_16(0xFFFFF700), &D1); // MOVE.W	$F700,D1
	DEF_ROMLOC(11408): sub_toreg_16(0x80, &D1); // SUBI.W	#$0080,D1
	DEF_ROMLOC(1140C): and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
	DEF_ROMLOC(11410): sub_toreg_16(D1, &D0); // SUB.W	D1,D0
	DEF_ROMLOC(11412): cmp_toreg_16(0x280, &D0); // CMPI.W	#$0280,D0
	DEF_ROMLOC(11416): if (CCR_HI) goto rom_DCCE; // BHI.W	$DCCE
	DEF_ROMLOC(1141A): return; // RTS
	DEF_ROMLOC(1141C): or_toreg_8(0xFFFFFFF8, &D2); // ORI.B	#$F8,D2
	DEF_ROMLOC(11420): btst_toreg_32(D7, &D0); // BTST.L	D7,D0
	rom_1142E(); // Detected flow into next function
}*/