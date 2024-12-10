/*ROMFUNC(rom_12D78) {
	DEF_ROMLOC(12D78): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(12D7A): move_toreg_8(read_8(A0 + 0x24), &D0); // MOVE.B	36(A0),D0
	DEF_ROMLOC(12D7E): move_toreg_16(read_16(0x12D86 + (s16)(D0 & 0xffff)), &D1); // MOVE.W	6(PC,D0),D1
	DEF_ROMLOC(12D82): goto rom_12D86 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
}*/
/*ROMFUNC(rom_12D92) {
	DEF_ROMLOC(12D92): add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
	DEF_ROMLOC(12D96): move_tomem_32(0x130A0, A0 + 0x4); // MOVE.L	#$000130A0,4(A0)
	DEF_ROMLOC(12D9E): move_tomem_16(0xFFFF8348, A0 + 0x2); // MOVE.W	#$8348,2(A0)
	DEF_ROMLOC(12DA4): move_tomem_8(0xFFFFFF84, A0 + 0x1); // MOVE.B	#$84,1(A0)
	DEF_ROMLOC(12DAA): move_tomem_8(0x10, A0 + 0x19); // MOVE.B	#$10,25(A0)
	DEF_ROMLOC(12DB0): move_tomem_8(0x1, A0 + 0x18); // MOVE.B	#$01,24(A0)
	DEF_ROMLOC(12DB6): move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B	40(A0),D0
	DEF_ROMLOC(12DBA): if (CCR_PL) goto rom_12DD6; // BPL.B	$12DD6
	DEF_ROMLOC(12DBC): add_tomem_8(0x8, A0 + 0x24); // ADDQ.B	#$08,36(A0)
	DEF_ROMLOC(12DC0): and_toreg_16(0x7F, &D0); // ANDI.W	#$007F,D0
	DEF_ROMLOC(12DC4): move_tomem_8(D0, A0 + 0x32); // MOVE.B	D0,50(A0)
	DEF_ROMLOC(12DC8): move_tomem_8(D0, A0 + 0x33); // MOVE.B	D0,51(A0)
	DEF_ROMLOC(12DCC): move_tomem_8(0x6, A0 + 0x1C); // MOVE.B	#$06,28(A0)
	DEF_ROMLOC(12DD2): goto rom_12EE6; // BRA.W	$12EE6
	DEF_ROMLOC(12DD6): move_tomem_8(D0, A0 + 0x1C); // MOVE.B	D0,28(A0)
	DEF_ROMLOC(12DDA): move_tomem_16(read_16(A0 + 0x8), A0 + 0x30); // MOVE.W	8(A0),48(A0)
	DEF_ROMLOC(12DE0): move_tomem_16(0xFFFFFF78, A0 + 0x12); // MOVE.W	#$FF78,18(A0)
	DEF_ROMLOC(12DE6): rom_29AC(); // JSR	$000029AC
	DEF_ROMLOC(12DEC): move_tomem_8(D0, A0 + 0x26); // MOVE.B	D0,38(A0)
	rom_12DF0(); // Detected flow into next function
}*/
/*ROMFUNC(rom_12DF0) {
	DEF_ROMLOC(12DF0): move_toreg_32(0x13070, &A1); // LEA.L	$00013070,A1
	DEF_ROMLOC(12DF6): rom_ADA2(); // JSR	$0000ADA2
	DEF_ROMLOC(12DFC): cmp_tomem_8(0x6, A0 + 0x1A); // CMPI.B	#$06,26(A0)
	DEF_ROMLOC(12E02): if (!CCR_EQ) goto rom_12E0A; // BNE.B	$12E0A
	DEF_ROMLOC(12E04): move_tomem_8(0x1, A0 + 0x2E); // MOVE.B	#$01,46(A0)
	rom_12E0A(); // Detected flow into next function
}*/
/*ROMFUNC(rom_12E0A) {
	DEF_ROMLOC(12E0A): move_toreg_16(read_16(0xFFFFF646), &D0); // MOVE.W	$F646,D0
	DEF_ROMLOC(12E0E): cmp_toreg_16(read_16(A0 + 0xC), &D0); // CMP.W	12(A0),D0
	DEF_ROMLOC(12E12): if (CCR_CS) goto rom_12E22; // BCS.B	$12E22
	DEF_ROMLOC(12E14): move_tomem_8(0x6, A0 + 0x24); // MOVE.B	#$06,36(A0)
	DEF_ROMLOC(12E1A): add_tomem_8(0x3, A0 + 0x1C); // ADDQ.B	#$03,28(A0)
	DEF_ROMLOC(12E1E): goto rom_12EC4; // BRA.W	$12EC4
	DEF_ROMLOC(12E22): move_toreg_8(read_8(A0 + 0x26), &D0); // MOVE.B	38(A0),D0
	DEF_ROMLOC(12E26): add_tomem_8(0x1, A0 + 0x26); // ADDQ.B	#$01,38(A0)
	DEF_ROMLOC(12E2A): and_toreg_16(0x7F, &D0); // ANDI.W	#$007F,D0
	DEF_ROMLOC(12E2E): move_toreg_32(0x144F0, &A1); // LEA.L	$000144F0,A1
	DEF_ROMLOC(12E34): move_toreg_8(read_8((s32)A1 + (s8)0x0 + (s16)D0), &D0); // MOVE.B	0(A1,D0),D0
	DEF_ROMLOC(12E38): ext_reg_16(&D0); // EXT.W	D0
	DEF_ROMLOC(12E3A): add_toreg_16(read_16(A0 + 0x30), &D0); // ADD.W	48(A0),D0
	DEF_ROMLOC(12E3E): move_tomem_16(D0, A0 + 0x8); // MOVE.W	D0,8(A0)
	DEF_ROMLOC(12E42): tst_mem_8(A0 + 0x2E); // TST.B	46(A0)
	DEF_ROMLOC(12E46): if (CCR_EQ) goto rom_12EAE; // BEQ.B	$12EAE
	DEF_ROMLOC(12E48): rom_13032(); // BSR.W	$13032
	DEF_ROMLOC(12E4C): if (CCR_EQ) goto rom_12EAE; // BEQ.B	$12EAE
	DEF_ROMLOC(12E4E): rom_147E2(); // BSR.W	$147E2
	DEF_ROMLOC(12E52): move_toreg_16(0xAD, &D0); // MOVE.W	#$00AD,D0
	DEF_ROMLOC(12E56): rom_1394(); // JSR	$00001394
	DEF_ROMLOC(12E5C): move_toreg_32(0xFFFFD000, &A1); // LEA.L	$D000,A1
	DEF_ROMLOC(12E60): clr_mem_16(A1 + 0x10); // CLR.W	16(A1)
	DEF_ROMLOC(12E64): clr_mem_16(A1 + 0x12); // CLR.W	18(A1)
	DEF_ROMLOC(12E68): clr_mem_16(A1 + 0x14); // CLR.W	20(A1)
	DEF_ROMLOC(12E6C): move_tomem_8(0x15, A1 + 0x1C); // MOVE.B	#$15,28(A1)
	DEF_ROMLOC(12E72): move_tomem_16(0x23, A1 + 0x3E); // MOVE.W	#$0023,62(A1)
	DEF_ROMLOC(12E78): move_tomem_8(0x0, A1 + 0x3C); // MOVE.B	#$00,60(A1)
	DEF_ROMLOC(12E7E): bclr_tomem_8(0x5, A1 + 0x22); // BCLR.B	#$05,34(A1)
	DEF_ROMLOC(12E84): bclr_tomem_8(0x4, A1 + 0x22); // BCLR.B	#$04,34(A1)
	DEF_ROMLOC(12E8A): btst_tomem_8(0x2, A1 + 0x22); // BTST.B	#$02,34(A1)
	DEF_ROMLOC(12E90): if (CCR_EQ) goto rom_12E14; // BEQ.W	$12E14
	DEF_ROMLOC(12E94): bclr_tomem_8(0x2, A1 + 0x22); // BCLR.B	#$02,34(A1)
	DEF_ROMLOC(12E9A): move_tomem_8(0x13, A1 + 0x16); // MOVE.B	#$13,22(A1)
	DEF_ROMLOC(12EA0): move_tomem_8(0x9, A1 + 0x17); // MOVE.B	#$09,23(A1)
	DEF_ROMLOC(12EA6): sub_tomem_16(0x5, A1 + 0xC); // SUBQ.W	#$05,12(A1)
	DEF_ROMLOC(12EAA): goto rom_12E14; // BRA.W	$12E14
	DEF_ROMLOC(12EAE): rom_DC6C(); // BSR.W	$DC6C
	DEF_ROMLOC(12EB2): tst_mem_8(A0 + 0x1); // TST.B	1(A0)
	DEF_ROMLOC(12EB6): if (CCR_PL) goto rom_12EBE; // BPL.B	$12EBE
	DEF_ROMLOC(12EB8): goto rom_DC92; // JMP	$0000DC92
	DEF_ROMLOC(12EBE): goto rom_DCCE; // JMP	$0000DCCE
}*/
/*ROMFUNC(rom_12EC4) {
	DEF_ROMLOC(12EC4): move_toreg_32(0x13070, &A1); // LEA.L	$00013070,A1
	DEF_ROMLOC(12ECA): rom_ADA2(); // JSR	$0000ADA2
	DEF_ROMLOC(12ED0): tst_mem_8(A0 + 0x1); // TST.B	1(A0)
	DEF_ROMLOC(12ED4): if (CCR_PL) goto rom_12EDC; // BPL.B	$12EDC
	DEF_ROMLOC(12ED6): goto rom_DC92; // JMP	$0000DC92
	DEF_ROMLOC(12EDC): goto rom_DCCE; // JMP	$0000DCCE
}*/
/*ROMFUNC(rom_12EE2) {
	rom_DCCE(); // BRA.W	$DCCE
}*/
/*ROMFUNC(rom_12EE6) {
	DEF_ROMLOC(12EE6): tst_mem_16(A0 + 0x36); // TST.W	54(A0)
	DEF_ROMLOC(12EEA): if (!CCR_EQ) goto rom_12F48; // BNE.B	$12F48
	DEF_ROMLOC(12EEC): move_toreg_16(read_16(0xFFFFF646), &D0); // MOVE.W	$F646,D0
	DEF_ROMLOC(12EF0): cmp_toreg_16(read_16(A0 + 0xC), &D0); // CMP.W	12(A0),D0
	DEF_ROMLOC(12EF4): if (CCR_CC) goto rom_12FF4; // BCC.W	$12FF4
	DEF_ROMLOC(12EF8): tst_mem_8(A0 + 0x1); // TST.B	1(A0)
	DEF_ROMLOC(12EFC): if (CCR_PL) goto rom_12FF4; // BPL.W	$12FF4
	DEF_ROMLOC(12F00): sub_tomem_16(0x1, A0 + 0x38); // SUBQ.W	#$01,56(A0)
	DEF_ROMLOC(12F04): if (CCR_PL) goto rom_12FE8; // BPL.W	$12FE8
	DEF_ROMLOC(12F08): move_tomem_16(0x1, A0 + 0x36); // MOVE.W	#$0001,54(A0)
	DEF_ROMLOC(12F0E): rom_29AC(); // JSR	$000029AC
	DEF_ROMLOC(12F14): move_toreg_16(D0, &D1); // MOVE.W	D0,D1
	DEF_ROMLOC(12F16): and_toreg_16(0x7, &D0); // ANDI.W	#$0007,D0
	DEF_ROMLOC(12F1A): cmp_toreg_16(0x6, &D0); // CMPI.W	#$0006,D0
	DEF_ROMLOC(12F1E): if (CCR_CC) goto rom_12F0E; // BCC.B	$12F0E
	DEF_ROMLOC(12F20): move_tomem_8(D0, A0 + 0x34); // MOVE.B	D0,52(A0)
	DEF_ROMLOC(12F24): and_toreg_16(0xC, &D1); // ANDI.W	#$000C,D1
	DEF_ROMLOC(12F28): move_toreg_32(0x13020, &A1); // LEA.L	$00013020,A1
	DEF_ROMLOC(12F2E): add_toreg_16(D1, &A1); // ADDA.W	D1,A1
	DEF_ROMLOC(12F30): move_tomem_32(A1, A0 + 0x3C); // MOVE.L	A1,60(A0)
	DEF_ROMLOC(12F34): sub_tomem_8(0x1, A0 + 0x32); // SUBQ.B	#$01,50(A0)
	DEF_ROMLOC(12F38): if (CCR_PL) goto rom_12F46; // BPL.B	$12F46
	DEF_ROMLOC(12F3A): move_tomem_8(read_8(A0 + 0x33), A0 + 0x32); // MOVE.B	51(A0),50(A0)
	DEF_ROMLOC(12F40): bset_tomem_8(0x7, A0 + 0x36); // BSET.B	#$07,54(A0)
	DEF_ROMLOC(12F46): goto rom_12F50; // BRA.B	$12F50
	DEF_ROMLOC(12F48): sub_tomem_16(0x1, A0 + 0x38); // SUBQ.W	#$01,56(A0)
	DEF_ROMLOC(12F4C): if (CCR_PL) goto rom_12FE8; // BPL.W	$12FE8
	DEF_ROMLOC(12F50): rom_29AC(); // JSR	$000029AC
	DEF_ROMLOC(12F56): and_toreg_16(0x1F, &D0); // ANDI.W	#$001F,D0
	DEF_ROMLOC(12F5A): move_tomem_16(D0, A0 + 0x38); // MOVE.W	D0,56(A0)
	DEF_ROMLOC(12F5E): rom_E11A(); // BSR.W	$E11A
	DEF_ROMLOC(12F62): if (!CCR_EQ) goto rom_12FCC; // BNE.B	$12FCC
	DEF_ROMLOC(12F64): move_tomem_8(0x64, A1 + 0x0); // MOVE.B	#$64,0(A1)
	DEF_ROMLOC(12F6A): move_tomem_16(read_16(A0 + 0x8), A1 + 0x8); // MOVE.W	8(A0),8(A1)
	DEF_ROMLOC(12F70): rom_29AC(); // JSR	$000029AC
	DEF_ROMLOC(12F76): and_toreg_16(0xF, &D0); // ANDI.W	#$000F,D0
	DEF_ROMLOC(12F7A): sub_toreg_16(0x8, &D0); // SUBQ.W	#$08,D0
	DEF_ROMLOC(12F7C): add_tomem_16(D0, A1 + 0x8); // ADD.W	D0,8(A1)
	DEF_ROMLOC(12F80): move_tomem_16(read_16(A0 + 0xC), A1 + 0xC); // MOVE.W	12(A0),12(A1)
	DEF_ROMLOC(12F86): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(12F88): move_toreg_8(read_8(A0 + 0x34), &D0); // MOVE.B	52(A0),D0
	DEF_ROMLOC(12F8C): move_toreg_32(read_32(A0 + 0x3C), &A2); // MOVEA.L	60(A0),A2
	DEF_ROMLOC(12F90): move_tomem_8(read_8((s32)A2 + (s8)0x0 + (s16)D0), A1 + 0x28); // MOVE.B	0(A2,D0),40(A1)
	DEF_ROMLOC(12F96): btst_tomem_8(0x7, A0 + 0x36); // BTST.B	#$07,54(A0)
	DEF_ROMLOC(12F9C): if (CCR_EQ) goto rom_12FCC; // BEQ.B	$12FCC
	DEF_ROMLOC(12F9E): rom_29AC(); // JSR	$000029AC
	DEF_ROMLOC(12FA4): and_toreg_16(0x3, &D0); // ANDI.W	#$0003,D0
	DEF_ROMLOC(12FA8): if (!CCR_EQ) goto rom_12FB8; // BNE.B	$12FB8
	DEF_ROMLOC(12FAA): bset_tomem_8(0x6, A0 + 0x36); // BSET.B	#$06,54(A0)
	DEF_ROMLOC(12FB0): if (!CCR_EQ) goto rom_12FCC; // BNE.B	$12FCC
	DEF_ROMLOC(12FB2): move_tomem_8(0x2, A1 + 0x28); // MOVE.B	#$02,40(A1)
	DEF_ROMLOC(12FB8): tst_mem_8(A0 + 0x34); // TST.B	52(A0)
	DEF_ROMLOC(12FBC): if (!CCR_EQ) goto rom_12FCC; // BNE.B	$12FCC
	DEF_ROMLOC(12FBE): bset_tomem_8(0x6, A0 + 0x36); // BSET.B	#$06,54(A0)
	DEF_ROMLOC(12FC4): if (!CCR_EQ) goto rom_12FCC; // BNE.B	$12FCC
	DEF_ROMLOC(12FC6): move_tomem_8(0x2, A1 + 0x28); // MOVE.B	#$02,40(A1)
	DEF_ROMLOC(12FCC): sub_tomem_8(0x1, A0 + 0x34); // SUBQ.B	#$01,52(A0)
	DEF_ROMLOC(12FD0): if (CCR_PL) goto rom_12FE8; // BPL.B	$12FE8
	DEF_ROMLOC(12FD2): rom_29AC(); // JSR	$000029AC
	DEF_ROMLOC(12FD8): and_toreg_16(0x7F, &D0); // ANDI.W	#$007F,D0
	DEF_ROMLOC(12FDC): add_toreg_16(0x80, &D0); // ADDI.W	#$0080,D0
	DEF_ROMLOC(12FE0): add_tomem_16(D0, A0 + 0x38); // ADD.W	D0,56(A0)
	DEF_ROMLOC(12FE4): clr_mem_16(A0 + 0x36); // CLR.W	54(A0)
	DEF_ROMLOC(12FE8): move_toreg_32(0x13070, &A1); // LEA.L	$00013070,A1
	DEF_ROMLOC(12FEE): rom_ADA2(); // JSR	$0000ADA2
	DEF_ROMLOC(12FF4): move_toreg_16(read_16(A0 + 0x8), &D0); // MOVE.W	8(A0),D0
	DEF_ROMLOC(12FF8): and_toreg_16(0xFFFFFF80, &D0); // ANDI.W	#$FF80,D0
	DEF_ROMLOC(12FFC): move_toreg_16(read_16(0xFFFFF700), &D1); // MOVE.W	$F700,D1
	DEF_ROMLOC(13000): sub_toreg_16(0x80, &D1); // SUBI.W	#$0080,D1
	DEF_ROMLOC(13004): and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
	DEF_ROMLOC(13008): sub_toreg_16(D1, &D0); // SUB.W	D1,D0
	DEF_ROMLOC(1300A): cmp_toreg_16(0x280, &D0); // CMPI.W	#$0280,D0
	DEF_ROMLOC(1300E): if (CCR_HI) goto rom_DCCE; // BHI.W	$DCCE
	DEF_ROMLOC(13012): move_toreg_16(read_16(0xFFFFF646), &D0); // MOVE.W	$F646,D0
	DEF_ROMLOC(13016): cmp_toreg_16(read_16(A0 + 0xC), &D0); // CMP.W	12(A0),D0
	DEF_ROMLOC(1301A): if (CCR_CS) goto rom_DC92; // BCS.W	$DC92
	DEF_ROMLOC(1301E): return; // RTS
}*/
/*ROMFUNC(rom_13020) {
	DEF_ROMLOC(13020): or_toreg_8(0x0, &D1); // ORI.B	#$00,D1
	DEF_ROMLOC(13024): or_toreg_8(0x0, &D0); // ORI.B	#$00,D0
	DEF_ROMLOC(13028): or_toreg_8(0x1, &D0); // ORI.B	#$01,D0
	DEF_ROMLOC(1302C): or_toreg_8(0x0, &D1); // ORI.B	#$00,D1
	DEF_ROMLOC(13030): btst_toreg_32(D0, &D0); // BTST.L	D0,D0
	rom_13032(); // Detected flow into next function
}*/
/*ROMFUNC(rom_13032) {
	DEF_ROMLOC(13032): tst_mem_8(0xFFFFF7C8); // TST.B	$F7C8
	DEF_ROMLOC(13036): if (CCR_MI) goto rom_1306C; // BMI.B	$1306C
	DEF_ROMLOC(13038): move_toreg_32(0xFFFFD000, &A1); // LEA.L	$D000,A1
	DEF_ROMLOC(1303C): move_toreg_16(read_16(A1 + 0x8), &D0); // MOVE.W	8(A1),D0
	DEF_ROMLOC(13040): move_toreg_16(read_16(A0 + 0x8), &D1); // MOVE.W	8(A0),D1
	DEF_ROMLOC(13044): sub_toreg_16(0x10, &D1); // SUBI.W	#$0010,D1
	DEF_ROMLOC(13048): cmp_toreg_16(D0, &D1); // CMP.W	D0,D1
	DEF_ROMLOC(1304A): if (CCR_CC) goto rom_1306C; // BCC.B	$1306C
	DEF_ROMLOC(1304C): add_toreg_16(0x20, &D1); // ADDI.W	#$0020,D1
	DEF_ROMLOC(13050): cmp_toreg_16(D0, &D1); // CMP.W	D0,D1
	DEF_ROMLOC(13052): if (CCR_CS) goto rom_1306C; // BCS.B	$1306C
	DEF_ROMLOC(13054): move_toreg_16(read_16(A1 + 0xC), &D0); // MOVE.W	12(A1),D0
	DEF_ROMLOC(13058): move_toreg_16(read_16(A0 + 0xC), &D1); // MOVE.W	12(A0),D1
	DEF_ROMLOC(1305C): cmp_toreg_16(D0, &D1); // CMP.W	D0,D1
	DEF_ROMLOC(1305E): if (CCR_CC) goto rom_1306C; // BCC.B	$1306C
	DEF_ROMLOC(13060): add_toreg_16(0x10, &D1); // ADDI.W	#$0010,D1
	DEF_ROMLOC(13064): cmp_toreg_16(D0, &D1); // CMP.W	D0,D1
	DEF_ROMLOC(13066): if (CCR_CS) goto rom_1306C; // BCS.B	$1306C
	DEF_ROMLOC(13068): move_toreg_32(0x1, &D0); // MOVEQ.L	$01,D0
	DEF_ROMLOC(1306A): return; // RTS
	DEF_ROMLOC(1306C): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(1306E): return; // RTS
}*/