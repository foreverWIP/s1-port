/*ROMFUNC(rom_FE94) {
	DEF_ROMLOC(FE94): move_toreg_16(read_16(0xFFFFFE04), &D0); // MOVE.W	$FE04,D0
	DEF_ROMLOC(FE98): add_toreg_16(D7, &D0); // ADD.W	D7,D0
	DEF_ROMLOC(FE9A): and_toreg_16(0x3, &D0); // ANDI.W	#$0003,D0
	DEF_ROMLOC(FE9E): if (!CCR_EQ) goto rom_FEC2; // BNE.B	$FEC2
	DEF_ROMLOC(FEA0): move_toreg_32(0x0, &D3); // MOVEQ.L	$00,D3
	DEF_ROMLOC(FEA2): move_toreg_8(read_8(A0 + 0x19), &D3); // MOVE.B	25(A0),D3
	DEF_ROMLOC(FEA6): tst_mem_16(A0 + 0x10); // TST.W	16(A0)
	DEF_ROMLOC(FEAA): if (CCR_MI) goto rom_FEB8; // BMI.B	$FEB8
	DEF_ROMLOC(FEAC): rom_15642(); // BSR.W	$15642
	DEF_ROMLOC(FEB0): tst_reg_16(&D1); // TST.W	D1
	DEF_ROMLOC(FEB2): if (CCR_PL) goto rom_FEC2; // BPL.B	$FEC2
	rom_FEB4(); // Detected flow into next function
}*/
/*ROMFUNC(rom_FEB4) {
	DEF_ROMLOC(FEB4): move_toreg_32(0x1, &D0); // MOVEQ.L	$01,D0
	DEF_ROMLOC(FEB6): return; // RTS
}*/
/*ROMFUNC(rom_FEB8) {
	DEF_ROMLOC(FEB8): not_reg_16(&D3); // NOT.W	D3
	DEF_ROMLOC(FEBA): rom_157D4(); // BSR.W	$157D4
	DEF_ROMLOC(FEBE): tst_reg_16(&D1); // TST.W	D1
	DEF_ROMLOC(FEC0): if (CCR_MI) goto rom_FEB4; // BMI.B	$FEB4
	rom_FEC2(); // Detected flow into next function
}*/
/*ROMFUNC(rom_FEC2) {
	DEF_ROMLOC(FEC2): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(FEC4): return; // RTS
}*/
/*ROMFUNC(rom_FEC6) {
	DEF_ROMLOC(FEC6): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(FEC8): move_toreg_8(read_8(A0 + 0x24), &D0); // MOVE.B	36(A0),D0
	DEF_ROMLOC(FECC): move_toreg_16(read_16(0xFED4 + (s16)(D0 & 0xffff)), &D1); // MOVE.W	6(PC,D0),D1
	DEF_ROMLOC(FED0): goto rom_FED4 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
	DEF_ROMLOC(FED4): or_toreg_8(0x58, &D4); // ORI.B	#$58,D4
	rom_FED8(); // Detected flow into next function
}*/
/*ROMFUNC(rom_FED8) {
	DEF_ROMLOC(FED8): move_tomem_32(0xFFBA, A0 + 0x4); // MOVE.L	#$0000FFBA,4(A0)
	DEF_ROMLOC(FEE0): move_tomem_16(0x247B, A0 + 0x2); // MOVE.W	#$247B,2(A0)
	DEF_ROMLOC(FEE6): move_tomem_8(0x4, A0 + 0x1); // MOVE.B	#$04,1(A0)
	DEF_ROMLOC(FEEC): move_tomem_8(0x4, A0 + 0x18); // MOVE.B	#$04,24(A0)
	DEF_ROMLOC(FEF2): move_tomem_8(0x14, A0 + 0x19); // MOVE.B	#$14,25(A0)
	DEF_ROMLOC(FEF8): move_tomem_8(0x11, A0 + 0x16); // MOVE.B	#$11,22(A0)
	DEF_ROMLOC(FEFE): move_tomem_8(0x8, A0 + 0x17); // MOVE.B	#$08,23(A0)
	DEF_ROMLOC(FF04): move_tomem_8(0xFFFFFFCC, A0 + 0x20); // MOVE.B	#$CC,32(A0)
	DEF_ROMLOC(FF0A): rom_DC40(); // BSR.W	$DC40
	DEF_ROMLOC(FF0E): rom_15580(); // BSR.W	$15580
	DEF_ROMLOC(FF12): tst_reg_16(&D1); // TST.W	D1
	DEF_ROMLOC(FF14): if (CCR_PL) goto rom_FF2A; // BPL.B	$FF2A
	DEF_ROMLOC(FF16): add_tomem_16(D1, A0 + 0xC); // ADD.W	D1,12(A0)
	DEF_ROMLOC(FF1A): move_tomem_16(0x0, A0 + 0x12); // MOVE.W	#$0000,18(A0)
	DEF_ROMLOC(FF20): add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
	DEF_ROMLOC(FF24): bchg_tomem_8(0x0, A0 + 0x22); // BCHG.B	#$00,34(A0)
	rom_FF2A(); // Detected flow into next function
}*/
/*ROMFUNC(rom_FF2A) {
	DEF_ROMLOC(FF2A): return; // RTS
}*/
/*ROMFUNC(rom_FF2C) {
	DEF_ROMLOC(FF2C): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(FF2E): move_toreg_8(read_8(A0 + 0x25), &D0); // MOVE.B	37(A0),D0
	DEF_ROMLOC(FF32): move_toreg_16(read_16(0xFF48 + (s16)(D0 & 0xffff)), &D1); // MOVE.W	20(PC,D0),D1
	DEF_ROMLOC(FF36): rom_FF48 + (s16)(D1 & 0xffff)(); // JSR	16(PC,D1)
	DEF_ROMLOC(FF3A): move_toreg_32(0xFFA8, &A1); // LEA.L	$0000FFA8,A1
	DEF_ROMLOC(FF40): rom_ADA2(); // BSR.W	$ADA2
	rom_FD38(); // BRA.W	$FD38
}*/
/*ROMFUNC(rom_FF48) {
	DEF_ROMLOC(FF48): or_toreg_8(0x28, &D4); // ORI.B	#$28,D4
	rom_FF4C(); // Detected flow into next function
}*/
/*ROMFUNC(rom_FF4C) {
	DEF_ROMLOC(FF4C): sub_tomem_16(0x1, A0 + 0x30); // SUBQ.W	#$01,48(A0)
	DEF_ROMLOC(FF50): if (CCR_PL) goto rom_FF6E; // BPL.B	$FF6E
	DEF_ROMLOC(FF52): add_tomem_8(0x2, A0 + 0x25); // ADDQ.B	#$02,37(A0)
	DEF_ROMLOC(FF56): move_tomem_16(0xFFFFFF00, A0 + 0x10); // MOVE.W	#$FF00,16(A0)
	DEF_ROMLOC(FF5C): move_tomem_8(0x1, A0 + 0x1C); // MOVE.B	#$01,28(A0)
	DEF_ROMLOC(FF62): bchg_tomem_8(0x0, A0 + 0x22); // BCHG.B	#$00,34(A0)
	DEF_ROMLOC(FF68): if (!CCR_EQ) goto rom_FF6E; // BNE.B	$FF6E
	DEF_ROMLOC(FF6A): neg_mem_16(A0 + 0x10); // NEG.W	16(A0)
	rom_FF6E(); // Detected flow into next function
}*/
/*ROMFUNC(rom_FF6E) {
	DEF_ROMLOC(FF6E): return; // RTS
}*/
/*ROMFUNC(rom_FF70) {
	DEF_ROMLOC(FF70): rom_DC6C(); // BSR.W	$DC6C
	DEF_ROMLOC(FF74): rom_15580(); // BSR.W	$15580
	DEF_ROMLOC(FF78): cmp_toreg_16(0xFFFFFFF8, &D1); // CMPI.W	#$FFF8,D1
	DEF_ROMLOC(FF7C): if (CCR_LT) goto rom_FF90; // BLT.B	$FF90
	DEF_ROMLOC(FF7E): cmp_toreg_16(0xC, &D1); // CMPI.W	#$000C,D1
	DEF_ROMLOC(FF82): if (CCR_GE) goto rom_FF90; // BGE.B	$FF90
	DEF_ROMLOC(FF84): add_tomem_16(D1, A0 + 0xC); // ADD.W	D1,12(A0)
	DEF_ROMLOC(FF88): rom_FE94(); // BSR.W	$FE94
	DEF_ROMLOC(FF8C): if (!CCR_EQ) goto rom_FF90; // BNE.B	$FF90
	DEF_ROMLOC(FF8E): return; // RTS
}*/
/*ROMFUNC(rom_FF90) {
	DEF_ROMLOC(FF90): sub_tomem_8(0x2, A0 + 0x25); // SUBQ.B	#$02,37(A0)
	DEF_ROMLOC(FF94): move_tomem_16(0x3B, A0 + 0x30); // MOVE.W	#$003B,48(A0)
	DEF_ROMLOC(FF9A): move_tomem_16(0x0, A0 + 0x10); // MOVE.W	#$0000,16(A0)
	DEF_ROMLOC(FFA0): move_tomem_8(0x0, A0 + 0x1C); // MOVE.B	#$00,28(A0)
	DEF_ROMLOC(FFA6): return; // RTS
	DEF_ROMLOC(FFA8): or_toreg_8(0x8, &D4); // ORI.B	#$08,D4
	DEF_ROMLOC(FFAC): btst_toreg_32(D3, &D0); // BTST.L	D3,D0
	rom_10062(); // Detected flow into next function
}*/