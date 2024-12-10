/*ROMFUNC(rom_18E54) {
	DEF_ROMLOC(18E54): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(18E56): move_toreg_8(read_8(A0 + 0x24), &D0); // MOVE.B	36(A0),D0
	DEF_ROMLOC(18E5A): move_toreg_16(read_16(0x18E68 + (s16)(D0 & 0xffff)), &D0); // MOVE.W	12(PC,D0),D0
	DEF_ROMLOC(18E5E): rom_18E68 + (s16)(D0 & 0xffff)(); // JSR	8(PC,D0)
	DEF_ROMLOC(18E62): goto rom_DC92; // JMP	$0000DC92
}*/
/*ROMFUNC(rom_18E70) {
	DEF_ROMLOC(18E70): move_tomem_8(0x8, A0 + 0x16); // MOVE.B	#$08,22(A0)
	DEF_ROMLOC(18E76): move_tomem_8(0x8, A0 + 0x17); // MOVE.B	#$08,23(A0)
	DEF_ROMLOC(18E7C): move_tomem_32(0xB9F8, A0 + 0x4); // MOVE.L	#$0000B9F8,4(A0)
	DEF_ROMLOC(18E84): move_tomem_16(0x345, A0 + 0x2); // MOVE.W	#$0345,2(A0)
	DEF_ROMLOC(18E8A): move_tomem_8(0x4, A0 + 0x1); // MOVE.B	#$04,1(A0)
	DEF_ROMLOC(18E90): move_tomem_8(0x5, A0 + 0x18); // MOVE.B	#$05,24(A0)
	DEF_ROMLOC(18E96): move_tomem_16(read_16(A0 + 0xC), A0 + 0x38); // MOVE.W	12(A0),56(A0)
	DEF_ROMLOC(18E9C): move_tomem_8(0x8, A0 + 0x19); // MOVE.B	#$08,25(A0)
	DEF_ROMLOC(18EA2): add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
	DEF_ROMLOC(18EA6): tst_mem_8(A0 + 0x28); // TST.B	40(A0)
	DEF_ROMLOC(18EAA): if (!CCR_EQ) goto rom_18EBA; // BNE.B	$18EBA
	DEF_ROMLOC(18EAC): move_tomem_8(0xFFFFFF8B, A0 + 0x20); // MOVE.B	#$8B,32(A0)
	DEF_ROMLOC(18EB2): add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
	rom_19036(); // BRA.W	$19036
}*/
/*ROMFUNC(rom_18EBA) {
	DEF_ROMLOC(18EBA): move_tomem_8(0x1E, A0 + 0x29); // MOVE.B	#$1E,41(A0)
	DEF_ROMLOC(18EC0): move_toreg_16(0xAE, &D0); // MOVE.W	#$00AE,D0
	DEF_ROMLOC(18EC4): rom_1394(); // JSR	$00001394
	rom_18ECA(); // Detected flow into next function
}*/
/*ROMFUNC(rom_18ECA) {
	DEF_ROMLOC(18ECA): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(18ECC): move_toreg_8(read_8(A0 + 0x25), &D0); // MOVE.B	37(A0),D0
	DEF_ROMLOC(18ED0): move_toreg_16(read_16(0x18EFA + (s16)(D0 & 0xffff)), &D0); // MOVE.W	40(PC,D0),D0
	DEF_ROMLOC(18ED4): rom_18EFA + (s16)(D0 & 0xffff)(); // JSR	36(PC,D0)
	DEF_ROMLOC(18ED8): rom_DC6C(); // JSR	$0000DC6C
	DEF_ROMLOC(18EDE): move_toreg_32(0xEB52, &A1); // LEA.L	$0000EB52,A1
	DEF_ROMLOC(18EE4): rom_ADA2(); // JSR	$0000ADA2
	DEF_ROMLOC(18EEA): cmp_tomem_16(0x2E8, A0 + 0xC); // CMPI.W	#$02E8,12(A0)
	DEF_ROMLOC(18EF0): if (CCR_HI) goto rom_18EF4; // BHI.B	$18EF4
	DEF_ROMLOC(18EF2): return; // RTS
}*/
/*ROMFUNC(rom_18EF4) {
	DEF_ROMLOC(18EF4): goto rom_DCCE; // JMP	$0000DCCE
}*/
/*ROMFUNC(rom_18F02) {
	DEF_ROMLOC(18F02): bset_tomem_8(0x1, A0 + 0x22); // BSET.B	#$01,34(A0)
	DEF_ROMLOC(18F08): sub_tomem_8(0x1, A0 + 0x29); // SUBQ.B	#$01,41(A0)
	DEF_ROMLOC(18F0C): if (CCR_PL) goto rom_18F30; // BPL.B	$18F30
	DEF_ROMLOC(18F0E): move_tomem_8(0xFFFFFF8B, A0 + 0x20); // MOVE.B	#$8B,32(A0)
	DEF_ROMLOC(18F14): clr_mem_8(A0 + 0x28); // CLR.B	40(A0)
	DEF_ROMLOC(18F18): add_tomem_16(0x18, A0 + 0x12); // ADDI.W	#$0018,18(A0)
	DEF_ROMLOC(18F1E): bclr_tomem_8(0x1, A0 + 0x22); // BCLR.B	#$01,34(A0)
	DEF_ROMLOC(18F24): rom_15580(); // BSR.W	$15580
	DEF_ROMLOC(18F28): tst_reg_16(&D1); // TST.W	D1
	DEF_ROMLOC(18F2A): if (CCR_PL) goto rom_18F30; // BPL.B	$18F30
	DEF_ROMLOC(18F2C): add_tomem_8(0x2, A0 + 0x25); // ADDQ.B	#$02,37(A0)
	rom_18F30(); // Detected flow into next function
}*/
/*ROMFUNC(rom_18F30) {
	DEF_ROMLOC(18F30): return; // RTS
}*/
/*ROMFUNC(rom_18F32) {
	DEF_ROMLOC(18F32): sub_tomem_16(0x2, A0 + 0xC); // SUBQ.W	#$02,12(A0)
	DEF_ROMLOC(18F36): bset_tomem_8(0x7, A0 + 0x2); // BSET.B	#$07,2(A0)
	DEF_ROMLOC(18F3C): move_tomem_16(0xA0, A0 + 0x10); // MOVE.W	#$00A0,16(A0)
	DEF_ROMLOC(18F42): clr_mem_16(A0 + 0x12); // CLR.W	18(A0)
	DEF_ROMLOC(18F46): move_tomem_16(read_16(A0 + 0x8), A0 + 0x30); // MOVE.W	8(A0),48(A0)
	DEF_ROMLOC(18F4C): move_tomem_16(read_16(A0 + 0xC), A0 + 0x38); // MOVE.W	12(A0),56(A0)
	DEF_ROMLOC(18F52): move_tomem_8(0x3, A0 + 0x29); // MOVE.B	#$03,41(A0)
	DEF_ROMLOC(18F58): rom_E130(); // JSR	$0000E130
	DEF_ROMLOC(18F5E): if (!CCR_EQ) goto rom_18F7A; // BNE.B	$18F7A
	DEF_ROMLOC(18F60): move_toreg_32(A1, &A3); // LEA.L	(A1),A3
	DEF_ROMLOC(18F62): move_toreg_32(A0, &A2); // LEA.L	(A0),A2
	DEF_ROMLOC(18F64): move_toreg_32(0x3, &D0); // MOVEQ.L	$03,D0
	rom_18F66(); // Detected flow into next function
}*/
/*ROMFUNC(rom_18F66) {
	DEF_ROMLOC(18F66): move_tomem_32(read_32((A2 += 4, A2 - 4)), (A3 += 4, A3 - 4)); // MOVE.L	(A2)+,(A3)+
	DEF_ROMLOC(18F68): move_tomem_32(read_32((A2 += 4, A2 - 4)), (A3 += 4, A3 - 4)); // MOVE.L	(A2)+,(A3)+
	DEF_ROMLOC(18F6A): move_tomem_32(read_32((A2 += 4, A2 - 4)), (A3 += 4, A3 - 4)); // MOVE.L	(A2)+,(A3)+
	DEF_ROMLOC(18F6C): move_tomem_32(read_32((A2 += 4, A2 - 4)), (A3 += 4, A3 - 4)); // MOVE.L	(A2)+,(A3)+
	DEF_ROMLOC(18F6E): dec_reg_16(&D0); if ((D0 & 0xffff) != 0xffff) goto rom_18F66; // DBF.W	D0,$18F66
	DEF_ROMLOC(18F72): neg_mem_16(A1 + 0x10); // NEG.W	16(A1)
	DEF_ROMLOC(18F76): add_tomem_8(0x2, A1 + 0x25); // ADDQ.B	#$02,37(A1)
	rom_18F7A(); // Detected flow into next function
}*/
/*ROMFUNC(rom_18F7A) {
	DEF_ROMLOC(18F7A): add_tomem_8(0x2, A0 + 0x25); // ADDQ.B	#$02,37(A0)
	DEF_ROMLOC(18F7E): return; // RTS
}*/
/*ROMFUNC(rom_18F80) {
	DEF_ROMLOC(18F80): rom_E130(); // JSR	$0000E130
	DEF_ROMLOC(18F86): if (!CCR_EQ) goto rom_18F9E; // BNE.B	$18F9E
	DEF_ROMLOC(18F88): move_tomem_16(read_16(A0 + 0x8), A1 + 0x8); // MOVE.W	8(A0),8(A1)
	DEF_ROMLOC(18F8E): move_tomem_16(read_16(A0 + 0xC), A1 + 0xC); // MOVE.W	12(A0),12(A1)
	DEF_ROMLOC(18F94): move_tomem_8(0x74, A1); // MOVE.B	#$74,(A1)
	DEF_ROMLOC(18F98): move_tomem_16(0x67, A1 + 0x28); // MOVE.W	#$0067,40(A1)
	rom_18F9E(); // Detected flow into next function
}*/
/*ROMFUNC(rom_18F9E) {
	DEF_ROMLOC(18F9E): return; // RTS
}*/
/*ROMFUNC(rom_18FA0) {
	DEF_ROMLOC(18FA0): rom_15580(); // BSR.W	$15580
	DEF_ROMLOC(18FA4): tst_reg_16(&D1); // TST.W	D1
	DEF_ROMLOC(18FA6): if (CCR_PL) goto rom_18FD6; // BPL.B	$18FD6
	DEF_ROMLOC(18FA8): move_toreg_16(read_16(A0 + 0x8), &D0); // MOVE.W	8(A0),D0
	DEF_ROMLOC(18FAC): cmp_toreg_16(0x1940, &D0); // CMPI.W	#$1940,D0
	DEF_ROMLOC(18FB0): if (CCR_GT) goto rom_18FDC; // BGT.B	$18FDC
	DEF_ROMLOC(18FB2): move_toreg_16(read_16(A0 + 0x30), &D1); // MOVE.W	48(A0),D1
	DEF_ROMLOC(18FB6): cmp_toreg_16(D0, &D1); // CMP.W	D0,D1
	DEF_ROMLOC(18FB8): if (CCR_EQ) goto rom_18FCE; // BEQ.B	$18FCE
	DEF_ROMLOC(18FBA): and_toreg_16(0x10, &D0); // ANDI.W	#$0010,D0
	DEF_ROMLOC(18FBE): and_toreg_16(0x10, &D1); // ANDI.W	#$0010,D1
	DEF_ROMLOC(18FC2): cmp_toreg_16(D0, &D1); // CMP.W	D0,D1
	DEF_ROMLOC(18FC4): if (CCR_EQ) goto rom_18FCE; // BEQ.B	$18FCE
	DEF_ROMLOC(18FC6): rom_18F80(); // BSR.B	$18F80
	DEF_ROMLOC(18FC8): move_tomem_16(read_16(A0 + 0x8), A0 + 0x32); // MOVE.W	8(A0),50(A0)
	rom_18FCE(); // Detected flow into next function
}*/
/*ROMFUNC(rom_18FCE) {
	DEF_ROMLOC(18FCE): move_tomem_16(read_16(A0 + 0x8), A0 + 0x30); // MOVE.W	8(A0),48(A0)
	DEF_ROMLOC(18FD4): return; // RTS
}*/
/*ROMFUNC(rom_18FD6) {
	DEF_ROMLOC(18FD6): add_tomem_8(0x2, A0 + 0x25); // ADDQ.B	#$02,37(A0)
	DEF_ROMLOC(18FDA): return; // RTS
}*/
/*ROMFUNC(rom_18FDC) {
	DEF_ROMLOC(18FDC): add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
	DEF_ROMLOC(18FE0): return; // RTS
}*/
/*ROMFUNC(rom_18FE2) {
	DEF_ROMLOC(18FE2): bclr_tomem_8(0x1, A0 + 0x22); // BCLR.B	#$01,34(A0)
	DEF_ROMLOC(18FE8): add_tomem_16(0x24, A0 + 0x12); // ADDI.W	#$0024,18(A0)
	DEF_ROMLOC(18FEE): move_toreg_16(read_16(A0 + 0x8), &D0); // MOVE.W	8(A0),D0
	DEF_ROMLOC(18FF2): sub_toreg_16(read_16(A0 + 0x32), &D0); // SUB.W	50(A0),D0
	DEF_ROMLOC(18FF6): if (CCR_PL) goto rom_18FFA; // BPL.B	$18FFA
	DEF_ROMLOC(18FF8): neg_reg_16(&D0); // NEG.W	D0
	rom_18FFA(); // Detected flow into next function
}*/
/*ROMFUNC(rom_18FFA) {
	DEF_ROMLOC(18FFA): cmp_toreg_16(0x12, &D0); // CMPI.W	#$0012,D0
	DEF_ROMLOC(18FFE): if (!CCR_EQ) goto rom_19006; // BNE.B	$19006
	DEF_ROMLOC(19000): bclr_tomem_8(0x7, A0 + 0x2); // BCLR.B	#$07,2(A0)
	rom_19006(); // Detected flow into next function
}*/
/*ROMFUNC(rom_19006) {
	DEF_ROMLOC(19006): rom_15580(); // BSR.W	$15580
	DEF_ROMLOC(1900A): tst_reg_16(&D1); // TST.W	D1
	DEF_ROMLOC(1900C): if (CCR_PL) goto rom_1902E; // BPL.B	$1902E
	DEF_ROMLOC(1900E): sub_tomem_8(0x1, A0 + 0x29); // SUBQ.B	#$01,41(A0)
	DEF_ROMLOC(19012): if (CCR_EQ) goto rom_19030; // BEQ.B	$19030
	DEF_ROMLOC(19014): clr_mem_16(A0 + 0x12); // CLR.W	18(A0)
	DEF_ROMLOC(19018): move_tomem_16(read_16(A0 + 0x32), A0 + 0x8); // MOVE.W	50(A0),8(A0)
	DEF_ROMLOC(1901E): move_tomem_16(read_16(A0 + 0x38), A0 + 0xC); // MOVE.W	56(A0),12(A0)
	DEF_ROMLOC(19024): bset_tomem_8(0x7, A0 + 0x2); // BSET.B	#$07,2(A0)
	DEF_ROMLOC(1902A): sub_tomem_8(0x2, A0 + 0x25); // SUBQ.B	#$02,37(A0)
	rom_1902E(); // Detected flow into next function
}*/
/*ROMFUNC(rom_1902E) {
	DEF_ROMLOC(1902E): return; // RTS
}*/
/*ROMFUNC(rom_19030) {
	DEF_ROMLOC(19030): goto rom_DCCE; // JMP	$0000DCCE
}*/
/*ROMFUNC(rom_19036) {
	DEF_ROMLOC(19036): bset_tomem_8(0x7, A0 + 0x2); // BSET.B	#$07,2(A0)
	DEF_ROMLOC(1903C): sub_tomem_8(0x1, A0 + 0x29); // SUBQ.B	#$01,41(A0)
	DEF_ROMLOC(19040): if (!CCR_EQ) goto rom_19050; // BNE.B	$19050
	DEF_ROMLOC(19042): move_tomem_8(0x1, A0 + 0x1C); // MOVE.B	#$01,28(A0)
	DEF_ROMLOC(19048): sub_tomem_16(0x4, A0 + 0xC); // SUBQ.W	#$04,12(A0)
	DEF_ROMLOC(1904C): clr_mem_8(A0 + 0x20); // CLR.B	32(A0)
	rom_19050(); // Detected flow into next function
}*/
/*ROMFUNC(rom_19050) {
	DEF_ROMLOC(19050): move_toreg_32(0xEB52, &A1); // LEA.L	$0000EB52,A1
	DEF_ROMLOC(19056): goto rom_ADA2; // JMP	$0000ADA2
}*/
/*ROMFUNC(rom_1905C) {
	DEF_ROMLOC(1905C): goto rom_DCCE; // JMP	$0000DCCE
}*/