/*ROMFUNC(rom_10912) {
	DEF_ROMLOC(10912): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(10914): move_toreg_8(read_8(A0 + 0x24), &D0); // MOVE.B	36(A0),D0
	DEF_ROMLOC(10918): move_toreg_16(read_16(0x10920 + (s16)(D0 & 0xffff)), &D1); // MOVE.W	6(PC,D0),D1
	DEF_ROMLOC(1091C): goto rom_10920 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
}*/
/*ROMFUNC(rom_10934) {
	DEF_ROMLOC(10934): add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
	DEF_ROMLOC(10938): move_tomem_32(0x10DD4, A0 + 0x4); // MOVE.L	#$00010DD4,4(A0)
	DEF_ROMLOC(10940): move_tomem_16(0x4000, A0 + 0x2); // MOVE.W	#$4000,2(A0)
	DEF_ROMLOC(10946): cmp_tomem_8(0x1, 0xFFFFFE10); // CMPI.B	#$01,$FE10
	DEF_ROMLOC(1094C): if (!CCR_EQ) goto rom_10954; // BNE.B	$10954
	DEF_ROMLOC(1094E): move_tomem_16(0x43C4, A0 + 0x2); // MOVE.W	#$43C4,2(A0)
	DEF_ROMLOC(10954): move_tomem_8(0x4, A0 + 0x1); // MOVE.B	#$04,1(A0)
	DEF_ROMLOC(1095A): move_tomem_8(0x3, A0 + 0x18); // MOVE.B	#$03,24(A0)
	DEF_ROMLOC(10960): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(10962): move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B	40(A0),D0
	DEF_ROMLOC(10966): lsr_toreg_16(0x3, &D0); // LSR.W	#$03,D0
	DEF_ROMLOC(10968): and_toreg_16(0xE, &D0); // ANDI.W	#$000E,D0
	DEF_ROMLOC(1096C): move_toreg_32(0x10924 + (s16)(D0 & 0xffff), &A2); // LEA.L	-74(PC,D0),A2
	DEF_ROMLOC(10970): move_tomem_8(read_8(A2++), A0 + 0x19); // MOVE.B	(A2)+,25(A0)
	DEF_ROMLOC(10974): move_tomem_8(read_8(A2), A0 + 0x16); // MOVE.B	(A2),22(A0)
	DEF_ROMLOC(10978): lsr_toreg_16(0x1, &D0); // LSR.W	#$01,D0
	DEF_ROMLOC(1097A): move_tomem_8(D0, A0 + 0x1A); // MOVE.B	D0,26(A0)
	DEF_ROMLOC(1097E): move_tomem_16(read_16(A0 + 0x8), A0 + 0x34); // MOVE.W	8(A0),52(A0)
	DEF_ROMLOC(10984): move_tomem_16(read_16(A0 + 0xC), A0 + 0x30); // MOVE.W	12(A0),48(A0)
	DEF_ROMLOC(1098A): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(1098C): move_toreg_8(read_8(A2), &D0); // MOVE.B	(A2),D0
	DEF_ROMLOC(1098E): add_toreg_16(D0, &D0); // ADD.W	D0,D0
	DEF_ROMLOC(10990): move_tomem_16(D0, A0 + 0x3A); // MOVE.W	D0,58(A0)
	DEF_ROMLOC(10994): cmp_tomem_8(0x37, A0 + 0x28); // CMPI.B	#$37,40(A0)
	DEF_ROMLOC(1099A): if (!CCR_EQ) goto rom_109C0; // BNE.B	$109C0
	DEF_ROMLOC(1099C): cmp_tomem_16(0x1BB8, A0 + 0x8); // CMPI.W	#$1BB8,8(A0)
	DEF_ROMLOC(109A2): if (!CCR_EQ) goto rom_109B0; // BNE.B	$109B0
	DEF_ROMLOC(109A4): tst_mem_8(0xFFFFF7CE); // TST.B	$F7CE
	DEF_ROMLOC(109A8): if (CCR_EQ) goto rom_109C0; // BEQ.B	$109C0
	DEF_ROMLOC(109AA): goto rom_DCCE; // JMP	$0000DCCE
	DEF_ROMLOC(109B0): clr_mem_8(A0 + 0x28); // CLR.B	40(A0)
	DEF_ROMLOC(109B4): tst_mem_8(0xFFFFF7CE); // TST.B	$F7CE
	DEF_ROMLOC(109B8): if (!CCR_EQ) goto rom_109C0; // BNE.B	$109C0
	DEF_ROMLOC(109BA): goto rom_DCCE; // JMP	$0000DCCE
	DEF_ROMLOC(109C0): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(109C2): cmp_tomem_8(0x1, 0xFFFFFE10); // CMPI.B	#$01,$FE10
	DEF_ROMLOC(109C8): if (CCR_EQ) goto rom_109EA; // BEQ.B	$109EA
	DEF_ROMLOC(109CA): move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B	40(A0),D0
	DEF_ROMLOC(109CE): and_toreg_16(0xF, &D0); // ANDI.W	#$000F,D0
	DEF_ROMLOC(109D2): sub_toreg_16(0x8, &D0); // SUBQ.W	#$08,D0
	DEF_ROMLOC(109D4): if (CCR_CS) goto rom_109EA; // BCS.B	$109EA
	DEF_ROMLOC(109D6): lsl_toreg_16(0x2, &D0); // LSL.W	#$02,D0
	DEF_ROMLOC(109D8): move_toreg_32(0xFFFFFE8A, &A2); // LEA.L	$FE8A,A2
	DEF_ROMLOC(109DC): move_toreg_32((s32)A2 + (s8)0x0 + (s16)D0, &A2); // LEA.L	0(A2,D0),A2
	DEF_ROMLOC(109E0): tst_mem_16(A2); // TST.W	(A2)
	DEF_ROMLOC(109E2): if (CCR_PL) goto rom_109EA; // BPL.B	$109EA
	DEF_ROMLOC(109E4): bchg_tomem_8(0x0, A0 + 0x22); // BCHG.B	#$00,34(A0)
	DEF_ROMLOC(109EA): move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B	40(A0),D0
	DEF_ROMLOC(109EE): if (CCR_PL) goto rom_10A34; // BPL.B	$10A34
	DEF_ROMLOC(109F0): and_toreg_8(0xF, &D0); // ANDI.B	#$0F,D0
	DEF_ROMLOC(109F4): move_tomem_8(D0, A0 + 0x3C); // MOVE.B	D0,60(A0)
	DEF_ROMLOC(109F8): move_tomem_8(0x5, A0 + 0x28); // MOVE.B	#$05,40(A0)
	DEF_ROMLOC(109FE): cmp_tomem_8(0x7, A0 + 0x1A); // CMPI.B	#$07,26(A0)
	DEF_ROMLOC(10A04): if (!CCR_EQ) goto rom_10A12; // BNE.B	$10A12
	DEF_ROMLOC(10A06): move_tomem_8(0xC, A0 + 0x28); // MOVE.B	#$0C,40(A0)
	DEF_ROMLOC(10A0C): move_tomem_16(0x80, A0 + 0x3A); // MOVE.W	#$0080,58(A0)
	DEF_ROMLOC(10A12): move_toreg_32(0xFFFFFC00, &A2); // LEA.L	$FC00,A2
	DEF_ROMLOC(10A16): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(10A18): move_toreg_8(read_8(A0 + 0x23), &D0); // MOVE.B	35(A0),D0
	DEF_ROMLOC(10A1C): if (CCR_EQ) goto rom_10A34; // BEQ.B	$10A34
	DEF_ROMLOC(10A1E): bclr_tomem_8(0x7, (s32)A2 + (s8)0x2 + (s16)D0); // BCLR.B	#$07,2(A2,D0)
	DEF_ROMLOC(10A24): btst_tomem_8(0x0, (s32)A2 + (s8)0x2 + (s16)D0); // BTST.B	#$00,2(A2,D0)
	DEF_ROMLOC(10A2A): if (CCR_EQ) goto rom_10A34; // BEQ.B	$10A34
	DEF_ROMLOC(10A2C): add_tomem_8(0x1, A0 + 0x28); // ADDQ.B	#$01,40(A0)
	DEF_ROMLOC(10A30): clr_mem_16(A0 + 0x3A); // CLR.W	58(A0)
	rom_10A34(); // Detected flow into next function
}*/
/*ROMFUNC(rom_10A34) {
	DEF_ROMLOC(10A34): move_tomem_16(read_16(A0 + 0x8), A7 -= 2); // MOVE.W	8(A0),-(A7)
	DEF_ROMLOC(10A38): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(10A3A): move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B	40(A0),D0
	DEF_ROMLOC(10A3E): and_toreg_16(0xF, &D0); // ANDI.W	#$000F,D0
	DEF_ROMLOC(10A42): add_toreg_16(D0, &D0); // ADD.W	D0,D0
	DEF_ROMLOC(10A44): move_toreg_16(read_16(0x10AA0 + (s16)(D0 & 0xffff)), &D1); // MOVE.W	90(PC,D0),D1
	DEF_ROMLOC(10A48): rom_10AA0 + (s16)(D1 & 0xffff)(); // JSR	86(PC,D1)
	DEF_ROMLOC(10A4C): move_toreg_16(read_16((A7 += 2, A7 - 2)), &D4); // MOVE.W	(A7)+,D4
	DEF_ROMLOC(10A4E): tst_mem_8(A0 + 0x1); // TST.B	1(A0)
	DEF_ROMLOC(10A52): if (CCR_PL) goto rom_10A6C; // BPL.B	$10A6C
	DEF_ROMLOC(10A54): move_toreg_32(0x0, &D1); // MOVEQ.L	$00,D1
	DEF_ROMLOC(10A56): move_toreg_8(read_8(A0 + 0x19), &D1); // MOVE.B	25(A0),D1
	DEF_ROMLOC(10A5A): add_toreg_16(0xB, &D1); // ADDI.W	#$000B,D1
	DEF_ROMLOC(10A5E): move_toreg_32(0x0, &D2); // MOVEQ.L	$00,D2
	DEF_ROMLOC(10A60): move_toreg_8(read_8(A0 + 0x16), &D2); // MOVE.B	22(A0),D2
	DEF_ROMLOC(10A64): move_toreg_16(D2, &D3); // MOVE.W	D2,D3
	DEF_ROMLOC(10A66): add_toreg_16(0x1, &D3); // ADDQ.W	#$01,D3
	DEF_ROMLOC(10A68): rom_10062(); // BSR.W	$10062
	DEF_ROMLOC(10A6C): move_toreg_16(read_16(A0 + 0x34), &D0); // MOVE.W	52(A0),D0
	DEF_ROMLOC(10A70): and_toreg_16(0xFFFFFF80, &D0); // ANDI.W	#$FF80,D0
	DEF_ROMLOC(10A74): move_toreg_16(read_16(0xFFFFF700), &D1); // MOVE.W	$F700,D1
	DEF_ROMLOC(10A78): sub_toreg_16(0x80, &D1); // SUBI.W	#$0080,D1
	DEF_ROMLOC(10A7C): and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
	DEF_ROMLOC(10A80): sub_toreg_16(D1, &D0); // SUB.W	D1,D0
	DEF_ROMLOC(10A82): cmp_toreg_16(0x280, &D0); // CMPI.W	#$0280,D0
	DEF_ROMLOC(10A86): if (CCR_HI) goto rom_10A8C; // BHI.B	$10A8C
	DEF_ROMLOC(10A88): goto rom_DC92; // BRA.W	$DC92
	DEF_ROMLOC(10A8C): cmp_tomem_8(0x37, A0 + 0x28); // CMPI.B	#$37,40(A0)
	DEF_ROMLOC(10A92): if (!CCR_EQ) goto rom_10A9A; // BNE.B	$10A9A
	DEF_ROMLOC(10A94): tst_mem_8(A0 + 0x38); // TST.B	56(A0)
	DEF_ROMLOC(10A98): if (!CCR_EQ) goto rom_10A88; // BNE.B	$10A88
	DEF_ROMLOC(10A9A): goto rom_DCCE; // JMP	$0000DCCE
	DEF_ROMLOC(10AA0): or_tomem_8(0x1E, A4++); // ORI.B	#$1E,(A4)+
	DEF_ROMLOC(10AA4): or_tomem_8(0x4C, A2 + 0x58); // ORI.B	#$4C,88(A2)
	rom_10E56(); // Detected flow into next function
}*/