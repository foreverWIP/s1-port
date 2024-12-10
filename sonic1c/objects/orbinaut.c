/*ROMFUNC(rom_123A2) {
	DEF_ROMLOC(123A2): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(123A4): move_toreg_8(read_8(A0 + 0x24), &D0); // MOVE.B	36(A0),D0
	DEF_ROMLOC(123A8): move_toreg_16(read_16(0x123B0 + (s16)(D0 & 0xffff)), &D1); // MOVE.W	6(PC,D0),D1
	DEF_ROMLOC(123AC): goto rom_123B0 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
}*/
/*ROMFUNC(rom_123BA) {
	DEF_ROMLOC(123BA): move_tomem_32(0x125B8, A0 + 0x4); // MOVE.L	#$000125B8,4(A0)
	DEF_ROMLOC(123C2): move_tomem_16(0x429, A0 + 0x2); // MOVE.W	#$0429,2(A0)
	DEF_ROMLOC(123C8): cmp_tomem_8(0x5, 0xFFFFFE10); // CMPI.B	#$05,$FE10
	DEF_ROMLOC(123CE): if (CCR_EQ) goto rom_123D6; // BEQ.B	$123D6
	DEF_ROMLOC(123D0): move_tomem_16(0x2429, A0 + 0x2); // MOVE.W	#$2429,2(A0)
	DEF_ROMLOC(123D6): cmp_tomem_8(0x1, 0xFFFFFE10); // CMPI.B	#$01,$FE10
	DEF_ROMLOC(123DC): if (!CCR_EQ) goto rom_123E4; // BNE.B	$123E4
	DEF_ROMLOC(123DE): move_tomem_16(0x467, A0 + 0x2); // MOVE.W	#$0467,2(A0)
	DEF_ROMLOC(123E4): or_tomem_8(0x4, A0 + 0x1); // ORI.B	#$04,1(A0)
	DEF_ROMLOC(123EA): move_tomem_8(0x4, A0 + 0x18); // MOVE.B	#$04,24(A0)
	DEF_ROMLOC(123F0): move_tomem_8(0xB, A0 + 0x20); // MOVE.B	#$0B,32(A0)
	DEF_ROMLOC(123F6): move_tomem_8(0xC, A0 + 0x19); // MOVE.B	#$0C,25(A0)
	DEF_ROMLOC(123FC): move_toreg_32(0x0, &D2); // MOVEQ.L	$00,D2
	DEF_ROMLOC(123FE): move_toreg_32(A0 + 0x37, &A2); // LEA.L	55(A0),A2
	DEF_ROMLOC(12402): move_toreg_32(A2, &A3); // MOVEA.L	A2,A3
	DEF_ROMLOC(12404): add_toreg_16(0x1, &A2); // ADDQ.W	#$01,A2
	DEF_ROMLOC(12406): move_toreg_32(0x3, &D1); // MOVEQ.L	$03,D1
	DEF_ROMLOC(12408): rom_E130(); // BSR.W	$E130
	DEF_ROMLOC(1240C): if (!CCR_EQ) goto rom_12464; // BNE.B	$12464
	DEF_ROMLOC(1240E): add_tomem_8(0x1, A3); // ADDQ.B	#$01,(A3)
	DEF_ROMLOC(12410): move_toreg_16(A1, &D5); // MOVE.W	A1,D5
	DEF_ROMLOC(12412): sub_toreg_16(0xFFFFD000, &D5); // SUBI.W	#$D000,D5
	DEF_ROMLOC(12416): lsr_toreg_16(0x6, &D5); // LSR.W	#$06,D5
	DEF_ROMLOC(12418): and_toreg_16(0x7F, &D5); // ANDI.W	#$007F,D5
	DEF_ROMLOC(1241C): move_tomem_8(D5, A2++); // MOVE.B	D5,(A2)+
	DEF_ROMLOC(1241E): move_tomem_8(read_8(A0 + 0x0), A1 + 0x0); // MOVE.B	0(A0),0(A1)
	DEF_ROMLOC(12424): move_tomem_8(0x6, A1 + 0x24); // MOVE.B	#$06,36(A1)
	DEF_ROMLOC(1242A): move_tomem_32(read_32(A0 + 0x4), A1 + 0x4); // MOVE.L	4(A0),4(A1)
	DEF_ROMLOC(12430): move_tomem_16(read_16(A0 + 0x2), A1 + 0x2); // MOVE.W	2(A0),2(A1)
	DEF_ROMLOC(12436): or_tomem_8(0x4, A1 + 0x1); // ORI.B	#$04,1(A1)
	DEF_ROMLOC(1243C): move_tomem_8(0x4, A1 + 0x18); // MOVE.B	#$04,24(A1)
	DEF_ROMLOC(12442): move_tomem_8(0x8, A1 + 0x19); // MOVE.B	#$08,25(A1)
	DEF_ROMLOC(12448): move_tomem_8(0x3, A1 + 0x1A); // MOVE.B	#$03,26(A1)
	DEF_ROMLOC(1244E): move_tomem_8(0xFFFFFF98, A1 + 0x20); // MOVE.B	#$98,32(A1)
	DEF_ROMLOC(12454): move_tomem_8(D2, A1 + 0x26); // MOVE.B	D2,38(A1)
	DEF_ROMLOC(12458): add_toreg_8(0x40, &D2); // ADDI.B	#$40,D2
	DEF_ROMLOC(1245C): move_tomem_32(A0, A1 + 0x3C); // MOVE.L	A0,60(A1)
	DEF_ROMLOC(12460): dec_reg_16(&D1); if ((D1 & 0xffff) != 0xffff) goto rom_12408; // DBF.W	D1,$12408
	DEF_ROMLOC(12464): move_toreg_32(0x1, &D0); // MOVEQ.L	$01,D0
	DEF_ROMLOC(12466): btst_tomem_8(0x0, A0 + 0x22); // BTST.B	#$00,34(A0)
	DEF_ROMLOC(1246C): if (CCR_EQ) goto rom_12470; // BEQ.B	$12470
	DEF_ROMLOC(1246E): neg_reg_16(&D0); // NEG.W	D0
	DEF_ROMLOC(12470): move_tomem_8(D0, A0 + 0x36); // MOVE.B	D0,54(A0)
	DEF_ROMLOC(12474): move_tomem_8(read_8(A0 + 0x28), A0 + 0x24); // MOVE.B	40(A0),36(A0)
	DEF_ROMLOC(1247A): add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
	DEF_ROMLOC(1247E): move_tomem_16(0xFFFFFFC0, A0 + 0x10); // MOVE.W	#$FFC0,16(A0)
	DEF_ROMLOC(12484): btst_tomem_8(0x0, A0 + 0x22); // BTST.B	#$00,34(A0)
	DEF_ROMLOC(1248A): if (CCR_EQ) goto rom_12490; // BEQ.B	$12490
	DEF_ROMLOC(1248C): neg_mem_16(A0 + 0x10); // NEG.W	16(A0)
	DEF_ROMLOC(12490): return; // RTS
}*/
/*ROMFUNC(rom_12492) {
	DEF_ROMLOC(12492): move_toreg_16(read_16(0xFFFFD008), &D0); // MOVE.W	$D008,D0
	DEF_ROMLOC(12496): sub_toreg_16(read_16(A0 + 0x8), &D0); // SUB.W	8(A0),D0
	DEF_ROMLOC(1249A): if (CCR_CC) goto rom_1249E; // BCC.B	$1249E
	DEF_ROMLOC(1249C): neg_reg_16(&D0); // NEG.W	D0
	DEF_ROMLOC(1249E): cmp_toreg_16(0xA0, &D0); // CMPI.W	#$00A0,D0
	DEF_ROMLOC(124A2): if (CCR_CC) goto rom_124C2; // BCC.B	$124C2
	DEF_ROMLOC(124A4): move_toreg_16(read_16(0xFFFFD00C), &D0); // MOVE.W	$D00C,D0
	DEF_ROMLOC(124A8): sub_toreg_16(read_16(A0 + 0xC), &D0); // SUB.W	12(A0),D0
	DEF_ROMLOC(124AC): if (CCR_CC) goto rom_124B0; // BCC.B	$124B0
	DEF_ROMLOC(124AE): neg_reg_16(&D0); // NEG.W	D0
	DEF_ROMLOC(124B0): cmp_toreg_16(0x50, &D0); // CMPI.W	#$0050,D0
	DEF_ROMLOC(124B4): if (CCR_CC) goto rom_124C2; // BCC.B	$124C2
	DEF_ROMLOC(124B6): tst_mem_16(0xFFFFFE08); // TST.W	$FE08
	DEF_ROMLOC(124BA): if (!CCR_EQ) goto rom_124C2; // BNE.B	$124C2
	DEF_ROMLOC(124BC): move_tomem_8(0x1, A0 + 0x1C); // MOVE.B	#$01,28(A0)
	DEF_ROMLOC(124C2): move_toreg_32(0x125AA, &A1); // LEA.L	$000125AA,A1
	DEF_ROMLOC(124C8): rom_ADA2(); // BSR.W	$ADA2
	rom_124D4(); // BRA.W	$124D4
}*/
/*ROMFUNC(rom_124D0) {
	DEF_ROMLOC(124D0): rom_DC6C(); // BSR.W	$DC6C
	rom_124D4(); // Detected flow into next function
}*/
/*ROMFUNC(rom_124D4) {
	DEF_ROMLOC(124D4): move_toreg_16(read_16(A0 + 0x8), &D0); // MOVE.W	8(A0),D0
	DEF_ROMLOC(124D8): and_toreg_16(0xFFFFFF80, &D0); // ANDI.W	#$FF80,D0
	DEF_ROMLOC(124DC): move_toreg_16(read_16(0xFFFFF700), &D1); // MOVE.W	$F700,D1
	DEF_ROMLOC(124E0): sub_toreg_16(0x80, &D1); // SUBI.W	#$0080,D1
	DEF_ROMLOC(124E4): and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
	DEF_ROMLOC(124E8): sub_toreg_16(D1, &D0); // SUB.W	D1,D0
	DEF_ROMLOC(124EA): cmp_toreg_16(0x280, &D0); // CMPI.W	#$0280,D0
	DEF_ROMLOC(124EE): if (CCR_HI) goto rom_124F6; // BHI.W	$124F6
	DEF_ROMLOC(124F2): goto rom_DC92; // BRA.W	$DC92
	DEF_ROMLOC(124F6): move_toreg_32(0xFFFFFC00, &A2); // LEA.L	$FC00,A2
	DEF_ROMLOC(124FA): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(124FC): move_toreg_8(read_8(A0 + 0x23), &D0); // MOVE.B	35(A0),D0
	DEF_ROMLOC(12500): if (CCR_EQ) goto rom_12508; // BEQ.B	$12508
	DEF_ROMLOC(12502): bclr_tomem_8(0x7, (s32)A2 + (s8)0x2 + (s16)D0); // BCLR.B	#$07,2(A2,D0)
	rom_12508(); // Detected flow into next function
}*/
/*ROMFUNC(rom_12508) {
	DEF_ROMLOC(12508): move_toreg_32(A0 + 0x37, &A2); // LEA.L	55(A0),A2
	DEF_ROMLOC(1250C): move_toreg_32(0x0, &D2); // MOVEQ.L	$00,D2
	DEF_ROMLOC(1250E): move_toreg_8(read_8(A2++), &D2); // MOVE.B	(A2)+,D2
	DEF_ROMLOC(12510): sub_toreg_16(0x1, &D2); // SUBQ.W	#$01,D2
	DEF_ROMLOC(12512): if (CCR_CS) goto rom_1252A; // BCS.B	$1252A
	rom_12514(); // Detected flow into next function
}*/
/*ROMFUNC(rom_12514) {
	DEF_ROMLOC(12514): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(12516): move_toreg_8(read_8(A2++), &D0); // MOVE.B	(A2)+,D0
	DEF_ROMLOC(12518): lsl_toreg_16(0x6, &D0); // LSL.W	#$06,D0
	DEF_ROMLOC(1251A): add_toreg_32(0xFFD000, &D0); // ADDI.L	#$00FFD000,D0
	DEF_ROMLOC(12520): move_toreg_32(D0, &A1); // MOVEA.L	D0,A1
	DEF_ROMLOC(12522): rom_DCD0(); // BSR.W	$DCD0
	DEF_ROMLOC(12526): dec_reg_16(&D2); if ((D2 & 0xffff) != 0xffff) goto rom_12514; // DBF.W	D2,$12514
	rom_1252A(); // Detected flow into next function
}*/
/*ROMFUNC(rom_1252A) {
	rom_DCCE(); // BRA.W	$DCCE
}*/
/*ROMFUNC(rom_1252E) {
	DEF_ROMLOC(1252E): move_toreg_32(read_32(A0 + 0x3C), &A1); // MOVEA.L	60(A0),A1
	DEF_ROMLOC(12532): cmp_tomem_8(0x60, A1 + 0x0); // CMPI.B	#$60,0(A1)
	DEF_ROMLOC(12538): if (!CCR_EQ) goto rom_DCCE; // BNE.W	$DCCE
	DEF_ROMLOC(1253C): cmp_tomem_8(0x2, A1 + 0x1A); // CMPI.B	#$02,26(A1)
	DEF_ROMLOC(12542): if (!CCR_EQ) goto rom_12570; // BNE.B	$12570
	DEF_ROMLOC(12544): cmp_tomem_8(0x40, A0 + 0x26); // CMPI.B	#$40,38(A0)
	DEF_ROMLOC(1254A): if (!CCR_EQ) goto rom_12570; // BNE.B	$12570
	DEF_ROMLOC(1254C): add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
	DEF_ROMLOC(12550): sub_tomem_8(0x1, A1 + 0x37); // SUBQ.B	#$01,55(A1)
	DEF_ROMLOC(12554): if (!CCR_EQ) goto rom_1255A; // BNE.B	$1255A
	DEF_ROMLOC(12556): add_tomem_8(0x2, A1 + 0x24); // ADDQ.B	#$02,36(A1)
	DEF_ROMLOC(1255A): move_tomem_16(0xFFFFFE00, A0 + 0x10); // MOVE.W	#$FE00,16(A0)
	DEF_ROMLOC(12560): btst_tomem_8(0x0, A1 + 0x22); // BTST.B	#$00,34(A1)
	DEF_ROMLOC(12566): if (CCR_EQ) goto rom_1256C; // BEQ.B	$1256C
	DEF_ROMLOC(12568): neg_mem_16(A0 + 0x10); // NEG.W	16(A0)
	DEF_ROMLOC(1256C): goto rom_DC92; // BRA.W	$DC92
	DEF_ROMLOC(12570): move_toreg_8(read_8(A0 + 0x26), &D0); // MOVE.B	38(A0),D0
	DEF_ROMLOC(12574): rom_29D2(); // JSR	$000029D2
	DEF_ROMLOC(1257A): asr_toreg_16(0x4, &D1); // ASR.W	#$04,D1
	DEF_ROMLOC(1257C): add_toreg_16(read_16(A1 + 0x8), &D1); // ADD.W	8(A1),D1
	DEF_ROMLOC(12580): move_tomem_16(D1, A0 + 0x8); // MOVE.W	D1,8(A0)
	DEF_ROMLOC(12584): asr_toreg_16(0x4, &D0); // ASR.W	#$04,D0
	DEF_ROMLOC(12586): add_toreg_16(read_16(A1 + 0xC), &D0); // ADD.W	12(A1),D0
	DEF_ROMLOC(1258A): move_tomem_16(D0, A0 + 0xC); // MOVE.W	D0,12(A0)
	DEF_ROMLOC(1258E): move_toreg_8(read_8(A1 + 0x36), &D0); // MOVE.B	54(A1),D0
	DEF_ROMLOC(12592): add_tomem_8(D0, A0 + 0x26); // ADD.B	D0,38(A0)
	rom_DC92(); // BRA.W	$DC92
}*/
/*ROMFUNC(rom_1259A) {
	DEF_ROMLOC(1259A): rom_DC6C(); // BSR.W	$DC6C
	DEF_ROMLOC(1259E): tst_mem_8(A0 + 0x1); // TST.B	1(A0)
	DEF_ROMLOC(125A2): if (CCR_PL) goto rom_DCCE; // BPL.W	$DCCE
	DEF_ROMLOC(125A6): goto rom_DC92; // BRA.W	$DC92
	DEF_ROMLOC(125AA): or_toreg_8(0x8, &D4); // ORI.B	#$08,D4
	DEF_ROMLOC(125AE): btst_toreg_32(D7, &D0); // BTST.L	D7,D0
	rom_125D8(); // Detected flow into next function
}*/