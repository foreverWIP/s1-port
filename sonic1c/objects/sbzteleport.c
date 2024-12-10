/*ROMFUNC(rom_16DD0) {
	DEF_ROMLOC(16DD0): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(16DD2): move_toreg_8(read_8(A0 + 0x24), &D0); // MOVE.B	36(A0),D0
	DEF_ROMLOC(16DD6): move_toreg_16(read_16(0x16E02 + (s16)(D0 & 0xffff)), &D1); // MOVE.W	42(PC,D0),D1
	DEF_ROMLOC(16DDA): rom_16E02 + (s16)(D1 & 0xffff)(); // JSR	38(PC,D1)
	DEF_ROMLOC(16DDE): move_toreg_16(read_16(A0 + 0x8), &D0); // MOVE.W	8(A0),D0
	DEF_ROMLOC(16DE2): and_toreg_16(0xFFFFFF80, &D0); // ANDI.W	#$FF80,D0
	DEF_ROMLOC(16DE6): move_toreg_16(read_16(0xFFFFF700), &D1); // MOVE.W	$F700,D1
	DEF_ROMLOC(16DEA): sub_toreg_16(0x80, &D1); // SUBI.W	#$0080,D1
	DEF_ROMLOC(16DEE): and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
	DEF_ROMLOC(16DF2): sub_toreg_16(D1, &D0); // SUB.W	D1,D0
	DEF_ROMLOC(16DF4): cmp_toreg_16(0x280, &D0); // CMPI.W	#$0280,D0
	DEF_ROMLOC(16DF8): if (CCR_HI) goto rom_16DFC; // BHI.B	$16DFC
	DEF_ROMLOC(16DFA): return; // RTS
	DEF_ROMLOC(16DFC): goto rom_DCCE; // JMP	$0000DCCE
}*/
/*ROMFUNC(rom_16E0A) {
	DEF_ROMLOC(16E0A): add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
	DEF_ROMLOC(16E0E): move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B	40(A0),D0
	DEF_ROMLOC(16E12): add_toreg_16(D0, &D0); // ADD.W	D0,D0
	DEF_ROMLOC(16E14): and_toreg_16(0x1E, &D0); // ANDI.W	#$001E,D0
	DEF_ROMLOC(16E18): move_toreg_32(0x17014, &A2); // LEA.L	506(PC),A2
	DEF_ROMLOC(16E1C): add_toreg_16(read_16((s32)A2 + (s8)0x0 + (s16)D0), &A2); // ADDA.W	0(A2,D0),A2
	DEF_ROMLOC(16E20): move_tomem_16(read_16((A2 += 2, A2 - 2)), A0 + 0x3A); // MOVE.W	(A2)+,58(A0)
	DEF_ROMLOC(16E24): move_tomem_32(A2, A0 + 0x3C); // MOVE.L	A2,60(A0)
	DEF_ROMLOC(16E28): move_tomem_16(read_16((A2 += 2, A2 - 2)), A0 + 0x36); // MOVE.W	(A2)+,54(A0)
	DEF_ROMLOC(16E2C): move_tomem_16(read_16((A2 += 2, A2 - 2)), A0 + 0x38); // MOVE.W	(A2)+,56(A0)
	rom_16E30(); // Detected flow into next function
}*/
/*ROMFUNC(rom_16E30) {
	DEF_ROMLOC(16E30): move_toreg_32(0xFFFFD000, &A1); // LEA.L	$D000,A1
	DEF_ROMLOC(16E34): move_toreg_16(read_16(A1 + 0x8), &D0); // MOVE.W	8(A1),D0
	DEF_ROMLOC(16E38): sub_toreg_16(read_16(A0 + 0x8), &D0); // SUB.W	8(A0),D0
	DEF_ROMLOC(16E3C): btst_tomem_8(0x0, A0 + 0x22); // BTST.B	#$00,34(A0)
	DEF_ROMLOC(16E42): if (CCR_EQ) goto rom_16E48; // BEQ.B	$16E48
	DEF_ROMLOC(16E44): add_toreg_16(0xF, &D0); // ADDI.W	#$000F,D0
	rom_16E48(); // Detected flow into next function
}*/
/*ROMFUNC(rom_16E48) {
	DEF_ROMLOC(16E48): cmp_toreg_16(0x10, &D0); // CMPI.W	#$0010,D0
	DEF_ROMLOC(16E4C): if (CCR_CC) goto rom_16EC4; // BCC.B	$16EC4
	DEF_ROMLOC(16E4E): move_toreg_16(read_16(A1 + 0xC), &D1); // MOVE.W	12(A1),D1
	DEF_ROMLOC(16E52): sub_toreg_16(read_16(A0 + 0xC), &D1); // SUB.W	12(A0),D1
	DEF_ROMLOC(16E56): add_toreg_16(0x20, &D1); // ADDI.W	#$0020,D1
	DEF_ROMLOC(16E5A): cmp_toreg_16(0x40, &D1); // CMPI.W	#$0040,D1
	DEF_ROMLOC(16E5E): if (CCR_CC) goto rom_16EC4; // BCC.B	$16EC4
	DEF_ROMLOC(16E60): tst_mem_8(0xFFFFF7C8); // TST.B	$F7C8
	DEF_ROMLOC(16E64): if (!CCR_EQ) goto rom_16EC4; // BNE.B	$16EC4
	DEF_ROMLOC(16E66): cmp_tomem_8(0x7, A0 + 0x28); // CMPI.B	#$07,40(A0)
	DEF_ROMLOC(16E6C): if (!CCR_EQ) goto rom_16E76; // BNE.B	$16E76
	DEF_ROMLOC(16E6E): cmp_tomem_16(0x32, 0xFFFFFE20); // CMPI.W	#$0032,$FE20
	DEF_ROMLOC(16E74): if (CCR_CS) goto rom_16EC4; // BCS.B	$16EC4
	rom_16E76(); // Detected flow into next function
}*/
/*ROMFUNC(rom_16E76) {
	DEF_ROMLOC(16E76): add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
	DEF_ROMLOC(16E7A): move_tomem_8(0xFFFFFF81, 0xFFFFF7C8); // MOVE.B	#$81,$F7C8
	DEF_ROMLOC(16E80): move_tomem_8(0x2, A1 + 0x1C); // MOVE.B	#$02,28(A1)
	DEF_ROMLOC(16E86): move_tomem_16(0x800, A1 + 0x14); // MOVE.W	#$0800,20(A1)
	DEF_ROMLOC(16E8C): move_tomem_16(0x0, A1 + 0x10); // MOVE.W	#$0000,16(A1)
	DEF_ROMLOC(16E92): move_tomem_16(0x0, A1 + 0x12); // MOVE.W	#$0000,18(A1)
	DEF_ROMLOC(16E98): bclr_tomem_8(0x5, A0 + 0x22); // BCLR.B	#$05,34(A0)
	DEF_ROMLOC(16E9E): bclr_tomem_8(0x5, A1 + 0x22); // BCLR.B	#$05,34(A1)
	DEF_ROMLOC(16EA4): bset_tomem_8(0x1, A1 + 0x22); // BSET.B	#$01,34(A1)
	DEF_ROMLOC(16EAA): move_tomem_16(read_16(A0 + 0x8), A1 + 0x8); // MOVE.W	8(A0),8(A1)
	DEF_ROMLOC(16EB0): move_tomem_16(read_16(A0 + 0xC), A1 + 0xC); // MOVE.W	12(A0),12(A1)
	DEF_ROMLOC(16EB6): clr_mem_8(A0 + 0x32); // CLR.B	50(A0)
	DEF_ROMLOC(16EBA): move_toreg_16(0xBE, &D0); // MOVE.W	#$00BE,D0
	DEF_ROMLOC(16EBE): rom_1394(); // JSR	$00001394
	rom_16EC4(); // Detected flow into next function
}*/
/*ROMFUNC(rom_16EC4) {
	DEF_ROMLOC(16EC4): return; // RTS
}*/
/*ROMFUNC(rom_16EC6) {
	DEF_ROMLOC(16EC6): move_toreg_32(0xFFFFD000, &A1); // LEA.L	$D000,A1
	DEF_ROMLOC(16ECA): move_toreg_8(read_8(A0 + 0x32), &D0); // MOVE.B	50(A0),D0
	DEF_ROMLOC(16ECE): add_tomem_8(0x2, A0 + 0x32); // ADDQ.B	#$02,50(A0)
	DEF_ROMLOC(16ED2): rom_29D2(); // JSR	$000029D2
	DEF_ROMLOC(16ED8): asr_toreg_16(0x5, &D0); // ASR.W	#$05,D0
	DEF_ROMLOC(16EDA): move_toreg_16(read_16(A0 + 0xC), &D2); // MOVE.W	12(A0),D2
	DEF_ROMLOC(16EDE): sub_toreg_16(D0, &D2); // SUB.W	D0,D2
	DEF_ROMLOC(16EE0): move_tomem_16(D2, A1 + 0xC); // MOVE.W	D2,12(A1)
	DEF_ROMLOC(16EE4): cmp_tomem_8(0xFFFFFF80, A0 + 0x32); // CMPI.B	#$80,50(A0)
	DEF_ROMLOC(16EEA): if (!CCR_EQ) goto rom_16EFE; // BNE.B	$16EFE
	DEF_ROMLOC(16EEC): rom_16F84(); // BSR.W	$16F84
	DEF_ROMLOC(16EF0): add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
	DEF_ROMLOC(16EF4): move_toreg_16(0xBC, &D0); // MOVE.W	#$00BC,D0
	DEF_ROMLOC(16EF8): rom_1394(); // JSR	$00001394
	rom_16EFE(); // Detected flow into next function
}*/
/*ROMFUNC(rom_16EFE) {
	DEF_ROMLOC(16EFE): return; // RTS
}*/
/*ROMFUNC(rom_16F00) {
	DEF_ROMLOC(16F00): // TODO; // ADDQ.L	#$04,A7
	DEF_ROMLOC(16F02): move_toreg_32(0xFFFFD000, &A1); // LEA.L	$D000,A1
	DEF_ROMLOC(16F06): sub_tomem_8(0x1, A0 + 0x2E); // SUBQ.B	#$01,46(A0)
	DEF_ROMLOC(16F0A): if (CCR_PL) goto rom_16F42; // BPL.B	$16F42
	DEF_ROMLOC(16F0C): move_tomem_16(read_16(A0 + 0x36), A1 + 0x8); // MOVE.W	54(A0),8(A1)
	DEF_ROMLOC(16F12): move_tomem_16(read_16(A0 + 0x38), A1 + 0xC); // MOVE.W	56(A0),12(A1)
	DEF_ROMLOC(16F18): move_toreg_32(0x0, &D1); // MOVEQ.L	$00,D1
	DEF_ROMLOC(16F1A): move_toreg_8(read_8(A0 + 0x3A), &D1); // MOVE.B	58(A0),D1
	DEF_ROMLOC(16F1E): add_toreg_8(0x4, &D1); // ADDQ.B	#$04,D1
	DEF_ROMLOC(16F20): cmp_toreg_8(read_8(A0 + 0x3B), &D1); // CMP.B	59(A0),D1
	DEF_ROMLOC(16F24): if (CCR_CS) goto rom_16F2A; // BCS.B	$16F2A
	DEF_ROMLOC(16F26): move_toreg_32(0x0, &D1); // MOVEQ.L	$00,D1
	rom_16F68(); // BRA.B	$16F68
}*/
/*ROMFUNC(rom_16F2A) {
	DEF_ROMLOC(16F2A): move_tomem_8(D1, A0 + 0x3A); // MOVE.B	D1,58(A0)
	DEF_ROMLOC(16F2E): move_toreg_32(read_32(A0 + 0x3C), &A2); // MOVEA.L	60(A0),A2
	DEF_ROMLOC(16F32): move_tomem_16(read_16((s32)A2 + (s8)0x0 + (s16)D1), A0 + 0x36); // MOVE.W	0(A2,D1),54(A0)
	DEF_ROMLOC(16F38): move_tomem_16(read_16((s32)A2 + (s8)0x2 + (s16)D1), A0 + 0x38); // MOVE.W	2(A2,D1),56(A0)
	rom_16F84(); // BRA.W	$16F84
}*/
/*ROMFUNC(rom_16F42) {
	DEF_ROMLOC(16F42): move_toreg_32(read_32(A1 + 0x8), &D2); // MOVE.L	8(A1),D2
	DEF_ROMLOC(16F46): move_toreg_32(read_32(A1 + 0xC), &D3); // MOVE.L	12(A1),D3
	DEF_ROMLOC(16F4A): move_toreg_16(read_16(A1 + 0x10), &D0); // MOVE.W	16(A1),D0
	DEF_ROMLOC(16F4E): ext_reg_32(&D0); // EXT.L	D0
	DEF_ROMLOC(16F50): asl_toreg_32(0x8, &D0); // ASL.L	#$08,D0
	DEF_ROMLOC(16F52): add_toreg_32(D0, &D2); // ADD.L	D0,D2
	DEF_ROMLOC(16F54): move_toreg_16(read_16(A1 + 0x12), &D0); // MOVE.W	18(A1),D0
	DEF_ROMLOC(16F58): ext_reg_32(&D0); // EXT.L	D0
	DEF_ROMLOC(16F5A): asl_toreg_32(0x8, &D0); // ASL.L	#$08,D0
	DEF_ROMLOC(16F5C): add_toreg_32(D0, &D3); // ADD.L	D0,D3
	DEF_ROMLOC(16F5E): move_tomem_32(D2, A1 + 0x8); // MOVE.L	D2,8(A1)
	DEF_ROMLOC(16F62): move_tomem_32(D3, A1 + 0xC); // MOVE.L	D3,12(A1)
	DEF_ROMLOC(16F66): return; // RTS
}*/
/*ROMFUNC(rom_16F68) {
	DEF_ROMLOC(16F68): and_tomem_16(0x7FF, A1 + 0xC); // ANDI.W	#$07FF,12(A1)
	DEF_ROMLOC(16F6E): clr_mem_8(A0 + 0x24); // CLR.B	36(A0)
	DEF_ROMLOC(16F72): clr_mem_8(0xFFFFF7C8); // CLR.B	$F7C8
	DEF_ROMLOC(16F76): move_tomem_16(0x0, A1 + 0x10); // MOVE.W	#$0000,16(A1)
	DEF_ROMLOC(16F7C): move_tomem_16(0x200, A1 + 0x12); // MOVE.W	#$0200,18(A1)
	DEF_ROMLOC(16F82): return; // RTS
}*/
/*ROMFUNC(rom_16F84) {
	DEF_ROMLOC(16F84): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(16F86): move_toreg_16(0x1000, &D2); // MOVE.W	#$1000,D2
	DEF_ROMLOC(16F8A): move_toreg_16(read_16(A0 + 0x36), &D0); // MOVE.W	54(A0),D0
	DEF_ROMLOC(16F8E): sub_toreg_16(read_16(A1 + 0x8), &D0); // SUB.W	8(A1),D0
	DEF_ROMLOC(16F92): if (CCR_GE) goto rom_16F98; // BGE.B	$16F98
	DEF_ROMLOC(16F94): neg_reg_16(&D0); // NEG.W	D0
	DEF_ROMLOC(16F96): neg_reg_16(&D2); // NEG.W	D2
	rom_16F98(); // Detected flow into next function
}*/
/*ROMFUNC(rom_16F98) {
	DEF_ROMLOC(16F98): move_toreg_32(0x0, &D1); // MOVEQ.L	$00,D1
	DEF_ROMLOC(16F9A): move_toreg_16(0x1000, &D3); // MOVE.W	#$1000,D3
	DEF_ROMLOC(16F9E): move_toreg_16(read_16(A0 + 0x38), &D1); // MOVE.W	56(A0),D1
	DEF_ROMLOC(16FA2): sub_toreg_16(read_16(A1 + 0xC), &D1); // SUB.W	12(A1),D1
	DEF_ROMLOC(16FA6): if (CCR_GE) goto rom_16FAC; // BGE.B	$16FAC
	DEF_ROMLOC(16FA8): neg_reg_16(&D1); // NEG.W	D1
	DEF_ROMLOC(16FAA): neg_reg_16(&D3); // NEG.W	D3
	rom_16FAC(); // Detected flow into next function
}*/
/*ROMFUNC(rom_16FAC) {
	DEF_ROMLOC(16FAC): cmp_toreg_16(D0, &D1); // CMP.W	D0,D1
	DEF_ROMLOC(16FAE): if (CCR_CS) goto rom_16FE2; // BCS.B	$16FE2
	DEF_ROMLOC(16FB0): move_toreg_32(0x0, &D1); // MOVEQ.L	$00,D1
	DEF_ROMLOC(16FB2): move_toreg_16(read_16(A0 + 0x38), &D1); // MOVE.W	56(A0),D1
	DEF_ROMLOC(16FB6): sub_toreg_16(read_16(A1 + 0xC), &D1); // SUB.W	12(A1),D1
	DEF_ROMLOC(16FBA): swap_reg_16(&D1); // SWAP.W	D1
	DEF_ROMLOC(16FBC): divs_toreg_16(D3, &D1); // DIVS.W	D3,D1
	DEF_ROMLOC(16FBE): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(16FC0): move_toreg_16(read_16(A0 + 0x36), &D0); // MOVE.W	54(A0),D0
	DEF_ROMLOC(16FC4): sub_toreg_16(read_16(A1 + 0x8), &D0); // SUB.W	8(A1),D0
	DEF_ROMLOC(16FC8): if (CCR_EQ) goto rom_16FCE; // BEQ.B	$16FCE
	DEF_ROMLOC(16FCA): swap_reg_16(&D0); // SWAP.W	D0
	DEF_ROMLOC(16FCC): divs_toreg_16(D1, &D0); // DIVS.W	D1,D0
	rom_16FCE(); // Detected flow into next function
}*/
/*ROMFUNC(rom_16FCE) {
	DEF_ROMLOC(16FCE): move_tomem_16(D0, A1 + 0x10); // MOVE.W	D0,16(A1)
	DEF_ROMLOC(16FD2): move_tomem_16(D3, A1 + 0x12); // MOVE.W	D3,18(A1)
	DEF_ROMLOC(16FD6): tst_reg_16(&D1); // TST.W	D1
	DEF_ROMLOC(16FD8): if (CCR_PL) goto rom_16FDC; // BPL.B	$16FDC
	DEF_ROMLOC(16FDA): neg_reg_16(&D1); // NEG.W	D1
	rom_16FDC(); // Detected flow into next function
}*/
/*ROMFUNC(rom_16FDC) {
	DEF_ROMLOC(16FDC): move_tomem_16(D1, A0 + 0x2E); // MOVE.W	D1,46(A0)
	DEF_ROMLOC(16FE0): return; // RTS
}*/
/*ROMFUNC(rom_16FE2) {
	DEF_ROMLOC(16FE2): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(16FE4): move_toreg_16(read_16(A0 + 0x36), &D0); // MOVE.W	54(A0),D0
	DEF_ROMLOC(16FE8): sub_toreg_16(read_16(A1 + 0x8), &D0); // SUB.W	8(A1),D0
	DEF_ROMLOC(16FEC): swap_reg_16(&D0); // SWAP.W	D0
	DEF_ROMLOC(16FEE): divs_toreg_16(D2, &D0); // DIVS.W	D2,D0
	DEF_ROMLOC(16FF0): move_toreg_32(0x0, &D1); // MOVEQ.L	$00,D1
	DEF_ROMLOC(16FF2): move_toreg_16(read_16(A0 + 0x38), &D1); // MOVE.W	56(A0),D1
	DEF_ROMLOC(16FF6): sub_toreg_16(read_16(A1 + 0xC), &D1); // SUB.W	12(A1),D1
	DEF_ROMLOC(16FFA): if (CCR_EQ) goto rom_17000; // BEQ.B	$17000
	DEF_ROMLOC(16FFC): swap_reg_16(&D1); // SWAP.W	D1
	DEF_ROMLOC(16FFE): divs_toreg_16(D0, &D1); // DIVS.W	D0,D1
	rom_17000(); // Detected flow into next function
}*/
/*ROMFUNC(rom_17000) {
	DEF_ROMLOC(17000): move_tomem_16(D1, A1 + 0x12); // MOVE.W	D1,18(A1)
	DEF_ROMLOC(17004): move_tomem_16(D2, A1 + 0x10); // MOVE.W	D2,16(A1)
	DEF_ROMLOC(17008): tst_reg_16(&D0); // TST.W	D0
	DEF_ROMLOC(1700A): if (CCR_PL) goto rom_1700E; // BPL.B	$1700E
	DEF_ROMLOC(1700C): neg_reg_16(&D0); // NEG.W	D0
	rom_1700E(); // Detected flow into next function
}*/
/*ROMFUNC(rom_1700E) {
	DEF_ROMLOC(1700E): move_tomem_16(D0, A0 + 0x2E); // MOVE.W	D0,46(A0)
	DEF_ROMLOC(17012): return; // RTS
}*/