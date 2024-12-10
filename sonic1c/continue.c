/*ROMFUNC(rom_4CEC) {
	DEF_ROMLOC(4CEC): rom_1E4A(); // BSR.W	$1E4A
	DEF_ROMLOC(4CF0): move_tosr_16(0x2700, &SR); // MOVE.W	#$2700,SR
	DEF_ROMLOC(4CF4): move_toreg_16(read_16(0xFFFFF60C), &D0); // MOVE.W	$F60C,D0
	DEF_ROMLOC(4CF8): and_toreg_8(0xFFFFFFBF, &D0); // ANDI.B	#$BF,D0
	DEF_ROMLOC(4CFC): move_tomem_16(D0, 0xC00004); // MOVE.W	D0,$00C00004
	DEF_ROMLOC(4D02): move_toreg_32(0xC00004, &A6); // LEA.L	$00C00004,A6
	DEF_ROMLOC(4D08): move_tomem_16(0xFFFF8004, A6); // MOVE.W	#$8004,(A6)
	DEF_ROMLOC(4D0C): move_tomem_16(0xFFFF8700, A6); // MOVE.W	#$8700,(A6)
	DEF_ROMLOC(4D10): rom_12C4(); // BSR.W	$12C4
	DEF_ROMLOC(4D14): move_toreg_32(0xFFFFD000, &A1); // LEA.L	$D000,A1
	DEF_ROMLOC(4D18): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(4D1A): move_toreg_16(0x7FF, &D1); // MOVE.W	#$07FF,D1
	DEF_ROMLOC(4D1E): move_tomem_32(D0, (A1 += 4, A1 - 4)); // MOVE.L	D0,(A1)+
	DEF_ROMLOC(4D20): dec_reg_16(&D1); if ((D1 & 0xffff) != 0xffff) goto rom_4D1E; // DBF.W	D1,$4D1E
	DEF_ROMLOC(4D24): move_tomem_32(0x70000002, 0xC00004); // MOVE.L	#$70000002,$00C00004
	DEF_ROMLOC(4D2E): move_toreg_32(0x39204, &A0); // LEA.L	$00039204,A0
	DEF_ROMLOC(4D34): rom_1438(); // BSR.W	$1438
	DEF_ROMLOC(4D38): move_tomem_32(0x60000002, 0xC00004); // MOVE.L	#$60000002,$00C00004
	DEF_ROMLOC(4D42): move_toreg_32(0x3B39A, &A0); // LEA.L	$0003B39A,A0
	DEF_ROMLOC(4D48): rom_1438(); // BSR.W	$1438
	DEF_ROMLOC(4D4C): move_tomem_32(0x6A200002, 0xC00004); // MOVE.L	#$6A200002,$00C00004
	DEF_ROMLOC(4D56): move_toreg_32(0x3B64A, &A0); // LEA.L	$0003B64A,A0
	DEF_ROMLOC(4D5C): rom_1438(); // BSR.W	$1438
	DEF_ROMLOC(4D60): move_toreg_32(0xA, &D1); // MOVEQ.L	$0A,D1
	DEF_ROMLOC(4D62): rom_1D104(); // JSR	$0001D104
	DEF_ROMLOC(4D68): move_toreg_32(0x12, &D0); // MOVEQ.L	$12,D0
	DEF_ROMLOC(4D6A): rom_20F4(); // BSR.W	$20F4
	DEF_ROMLOC(4D6E): move_toreg_8(0xFFFFFF90, &D0); // MOVE.B	#$90,D0
	DEF_ROMLOC(4D72): rom_138E(); // BSR.W	$138E
	DEF_ROMLOC(4D76): move_tomem_16(0x293, 0xFFFFF614); // MOVE.W	#$0293,$F614
	DEF_ROMLOC(4D7C): clr_mem_32(0xFFFFF700); // CLR.L	$F700
	DEF_ROMLOC(4D80): move_tomem_32(0x1000000, 0xFFFFF704); // MOVE.L	#$01000000,$F704
	DEF_ROMLOC(4D88): move_tomem_8(0xFFFFFF81, 0xFFFFD000); // MOVE.B	#$81,$D000
	DEF_ROMLOC(4D8E): move_tomem_8(0xFFFFFF80, 0xFFFFD040); // MOVE.B	#$80,$D040
	DEF_ROMLOC(4D94): move_tomem_8(0xFFFFFF80, 0xFFFFD080); // MOVE.B	#$80,$D080
	DEF_ROMLOC(4D9A): move_tomem_8(0x3, 0xFFFFD098); // MOVE.B	#$03,$D098
	DEF_ROMLOC(4DA0): move_tomem_8(0x4, 0xFFFFD09A); // MOVE.B	#$04,$D09A
	DEF_ROMLOC(4DA6): move_tomem_8(0xFFFFFF80, 0xFFFFD0C0); // MOVE.B	#$80,$D0C0
	DEF_ROMLOC(4DAC): move_tomem_8(0x4, 0xFFFFD0E4); // MOVE.B	#$04,$D0E4
	DEF_ROMLOC(4DB2): rom_D9C6(); // JSR	$0000D9C6
	DEF_ROMLOC(4DB8): rom_DCEC(); // JSR	$0000DCEC
	DEF_ROMLOC(4DBE): move_toreg_16(read_16(0xFFFFF60C), &D0); // MOVE.W	$F60C,D0
	DEF_ROMLOC(4DC2): or_toreg_8(0x40, &D0); // ORI.B	#$40,D0
	DEF_ROMLOC(4DC6): move_tomem_16(D0, 0xC00004); // MOVE.W	D0,$00C00004
	DEF_ROMLOC(4DCC): rom_1DA4(); // BSR.W	$1DA4
	rom_4DD0(); // Detected flow into next function
}*/
/*ROMFUNC(rom_4DD0) {
	DEF_ROMLOC(4DD0): move_tomem_8(0x16, 0xFFFFF62A); // MOVE.B	#$16,$F62A
	DEF_ROMLOC(4DD6): rom_29A0(); // BSR.W	$29A0
	DEF_ROMLOC(4DDA): cmp_tomem_8(0x6, 0xFFFFD024); // CMPI.B	#$06,$D024
	DEF_ROMLOC(4DE0): if (CCR_CC) goto rom_4DFE; // BCC.B	$4DFE
	DEF_ROMLOC(4DE2): move_tosr_16(0x2700, &SR); // MOVE.W	#$2700,SR
	DEF_ROMLOC(4DE6): move_toreg_16(read_16(0xFFFFF614), &D1); // MOVE.W	$F614,D1
	DEF_ROMLOC(4DEA): divu_toreg_16(0x3C, &D1); // DIVU.W	#$003C,D1
	DEF_ROMLOC(4DEE): and_toreg_32(0xF, &D1); // ANDI.L	#$0000000F,D1
	DEF_ROMLOC(4DF4): rom_1D104(); // JSR	$0001D104
	DEF_ROMLOC(4DFA): move_tosr_16(0x2300, &SR); // MOVE.W	#$2300,SR
	rom_4DFE(); // Detected flow into next function
}*/
/*ROMFUNC(rom_4DFE) {
	DEF_ROMLOC(4DFE): rom_D9C6(); // JSR	$0000D9C6
	DEF_ROMLOC(4E04): rom_DCEC(); // JSR	$0000DCEC
	DEF_ROMLOC(4E0A): cmp_tomem_16(0x180, 0xFFFFD008); // CMPI.W	#$0180,$D008
	DEF_ROMLOC(4E10): if (CCR_CC) goto rom_4E2A; // BCC.B	$4E2A
	DEF_ROMLOC(4E12): cmp_tomem_8(0x6, 0xFFFFD024); // CMPI.B	#$06,$D024
	DEF_ROMLOC(4E18): if (CCR_CC) goto rom_4DD0; // BCC.B	$4DD0
	DEF_ROMLOC(4E1A): tst_mem_16(0xFFFFF614); // TST.W	$F614
	DEF_ROMLOC(4E1E): if (!CCR_EQ) goto rom_4DD0; // BNE.W	$4DD0
	DEF_ROMLOC(4E22): move_tomem_8(0x0, 0xFFFFF600); // MOVE.B	#$00,$F600
	DEF_ROMLOC(4E28): return; // RTS
}*/
/*ROMFUNC(rom_4E2A) {
	DEF_ROMLOC(4E2A): move_tomem_8(0xC, 0xFFFFF600); // MOVE.B	#$0C,$F600
	DEF_ROMLOC(4E30): move_tomem_8(0x3, 0xFFFFFE12); // MOVE.B	#$03,$FE12
	DEF_ROMLOC(4E36): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(4E38): move_tomem_16(D0, 0xFFFFFE20); // MOVE.W	D0,$FE20
	DEF_ROMLOC(4E3C): move_tomem_32(D0, 0xFFFFFE22); // MOVE.L	D0,$FE22
	DEF_ROMLOC(4E40): move_tomem_32(D0, 0xFFFFFE26); // MOVE.L	D0,$FE26
	DEF_ROMLOC(4E44): move_tomem_8(D0, 0xFFFFFE30); // MOVE.B	D0,$FE30
	DEF_ROMLOC(4E48): sub_tomem_8(0x1, 0xFFFFFE18); // SUBQ.B	#$01,$FE18
	DEF_ROMLOC(4E4C): return; // RTS
}*/
/*ROMFUNC(rom_4E4E) {
	DEF_ROMLOC(4E4E): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(4E50): move_toreg_8(read_8(A0 + 0x24), &D0); // MOVE.B	36(A0),D0
	DEF_ROMLOC(4E54): move_toreg_16(read_16(0x4E5C + (s16)(D0 & 0xffff)), &D1); // MOVE.W	6(PC,D0),D1
	DEF_ROMLOC(4E58): goto rom_4E5C + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
}*/
/*ROMFUNC(rom_4E64) {
	DEF_ROMLOC(4E64): add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
	DEF_ROMLOC(4E68): move_tomem_32(0x5062, A0 + 0x4); // MOVE.L	#$00005062,4(A0)
	DEF_ROMLOC(4E70): move_tomem_16(0xFFFF8500, A0 + 0x2); // MOVE.W	#$8500,2(A0)
	DEF_ROMLOC(4E76): move_tomem_8(0x0, A0 + 0x1); // MOVE.B	#$00,1(A0)
	DEF_ROMLOC(4E7C): move_tomem_8(0x3C, A0 + 0x19); // MOVE.B	#$3C,25(A0)
	DEF_ROMLOC(4E82): move_tomem_16(0x120, A0 + 0x8); // MOVE.W	#$0120,8(A0)
	DEF_ROMLOC(4E88): move_tomem_16(0xC0, A0 + 0xA); // MOVE.W	#$00C0,10(A0)
	DEF_ROMLOC(4E8E): move_tomem_16(0x0, 0xFFFFFE20); // MOVE.W	#$0000,$FE20
	rom_4E94(); // Detected flow into next function
}*/
/*ROMFUNC(rom_4E94) {
	DEF_ROMLOC(4E94): goto rom_DC92; // JMP	$0000DC92
}*/
/*ROMFUNC(rom_4E9A) {
	DEF_ROMLOC(4E9A): btst_tomem_8(D0, A6); // BTST.B	D0,(A6)
	DEF_ROMLOC(4E9C): btst_tomem_8(D0, A2 + 0x102); // BTST.B	D0,258(A2)
	rom_4EB8(); // Detected flow into next function
}*/
/*ROMFUNC(rom_4EB8) {
	DEF_ROMLOC(4EB8): move_toreg_32(A0, &A1); // MOVEA.L	A0,A1
	DEF_ROMLOC(4EBA): move_toreg_32(0x4E9A, &A2); // LEA.L	$00004E9A,A2
	DEF_ROMLOC(4EC0): move_toreg_32(0x0, &D1); // MOVEQ.L	$00,D1
	DEF_ROMLOC(4EC2): move_toreg_8(read_8(0xFFFFFE18), &D1); // MOVE.B	$FE18,D1
	DEF_ROMLOC(4EC6): sub_toreg_8(0x2, &D1); // SUBQ.B	#$02,D1
	DEF_ROMLOC(4EC8): if (CCR_CC) goto rom_4ED0; // BCC.B	$4ED0
	DEF_ROMLOC(4ECA): goto rom_DCCE; // JMP	$0000DCCE
}*/
/*ROMFUNC(rom_4ED0) {
	DEF_ROMLOC(4ED0): move_toreg_32(0x1, &D3); // MOVEQ.L	$01,D3
	DEF_ROMLOC(4ED2): cmp_toreg_8(0xE, &D1); // CMPI.B	#$0E,D1
	DEF_ROMLOC(4ED6): if (CCR_CS) goto rom_4EDC; // BCS.B	$4EDC
	DEF_ROMLOC(4ED8): move_toreg_32(0x0, &D3); // MOVEQ.L	$00,D3
	DEF_ROMLOC(4EDA): move_toreg_32(0xE, &D1); // MOVEQ.L	$0E,D1
	rom_4EDC(); // Detected flow into next function
}*/
/*ROMFUNC(rom_4EDC) {
	DEF_ROMLOC(4EDC): move_toreg_8(D1, &D2); // MOVE.B	D1,D2
	DEF_ROMLOC(4EDE): and_toreg_8(0x1, &D2); // ANDI.B	#$01,D2
	rom_4EE2(); // Detected flow into next function
}*/
/*ROMFUNC(rom_4EE2) {
	DEF_ROMLOC(4EE2): move_tomem_8(0xFFFFFF80, A1 + 0x0); // MOVE.B	#$80,0(A1)
	DEF_ROMLOC(4EE8): move_tomem_16(read_16((A2 += 2, A2 - 2)), A1 + 0x8); // MOVE.W	(A2)+,8(A1)
	DEF_ROMLOC(4EEC): tst_reg_8(&D2); // TST.B	D2
	DEF_ROMLOC(4EEE): if (CCR_EQ) goto rom_4EF6; // BEQ.B	$4EF6
	DEF_ROMLOC(4EF0): sub_tomem_16(0xA, A1 + 0x8); // SUBI.W	#$000A,8(A1)
	rom_4EF6(); // Detected flow into next function
}*/
/*ROMFUNC(rom_4EF6) {
	DEF_ROMLOC(4EF6): move_tomem_16(0xD0, A1 + 0xA); // MOVE.W	#$00D0,10(A1)
	DEF_ROMLOC(4EFC): move_tomem_8(0x6, A1 + 0x1A); // MOVE.B	#$06,26(A1)
	DEF_ROMLOC(4F02): move_tomem_8(0x6, A1 + 0x24); // MOVE.B	#$06,36(A1)
	DEF_ROMLOC(4F08): move_tomem_32(0x5062, A1 + 0x4); // MOVE.L	#$00005062,4(A1)
	DEF_ROMLOC(4F10): move_tomem_16(0xFFFF8551, A1 + 0x2); // MOVE.W	#$8551,2(A1)
	DEF_ROMLOC(4F16): move_tomem_8(0x0, A1 + 0x1); // MOVE.B	#$00,1(A1)
	DEF_ROMLOC(4F1C): move_toreg_32(A1 + 0x40, &A1); // LEA.L	64(A1),A1
	DEF_ROMLOC(4F20): dec_reg_16(&D1); if ((D1 & 0xffff) != 0xffff) goto rom_4EE2; // DBF.W	D1,$4EE2
	DEF_ROMLOC(4F24): move_toreg_32(A1 - 0x40, &A1); // LEA.L	-64(A1),A1
	DEF_ROMLOC(4F28): move_tomem_8(D3, A1 + 0x28); // MOVE.B	D3,40(A1)
	rom_4F2C(); // Detected flow into next function
}*/
/*ROMFUNC(rom_4F2C) {
	DEF_ROMLOC(4F2C): tst_mem_8(A0 + 0x28); // TST.B	40(A0)
	DEF_ROMLOC(4F30): if (CCR_EQ) goto rom_4F4C; // BEQ.B	$4F4C
	DEF_ROMLOC(4F32): cmp_tomem_8(0x6, 0xFFFFD024); // CMPI.B	#$06,$D024
	DEF_ROMLOC(4F38): if (CCR_CS) goto rom_4F4C; // BCS.B	$4F4C
	DEF_ROMLOC(4F3A): move_toreg_8(read_8(0xFFFFFE0F), &D0); // MOVE.B	$FE0F,D0
	DEF_ROMLOC(4F3E): and_toreg_8(0x1, &D0); // ANDI.B	#$01,D0
	DEF_ROMLOC(4F42): if (!CCR_EQ) goto rom_4F4C; // BNE.B	$4F4C
	DEF_ROMLOC(4F44): tst_mem_16(0xFFFFD010); // TST.W	$D010
	DEF_ROMLOC(4F48): if (!CCR_EQ) goto rom_4F62; // BNE.B	$4F62
	DEF_ROMLOC(4F4A): return; // RTS
}*/
/*ROMFUNC(rom_4F4C) {
	DEF_ROMLOC(4F4C): move_toreg_8(read_8(0xFFFFFE0F), &D0); // MOVE.B	$FE0F,D0
	DEF_ROMLOC(4F50): and_toreg_8(0xF, &D0); // ANDI.B	#$0F,D0
	DEF_ROMLOC(4F54): if (!CCR_EQ) goto rom_4F5C; // BNE.B	$4F5C
	DEF_ROMLOC(4F56): bchg_tomem_8(0x0, A0 + 0x1A); // BCHG.B	#$00,26(A0)
	rom_4F5C(); // Detected flow into next function
}*/
/*ROMFUNC(rom_4F5C) {
	DEF_ROMLOC(4F5C): goto rom_DC92; // JMP	$0000DC92
}*/
/*ROMFUNC(rom_4F62) {
	DEF_ROMLOC(4F62): goto rom_DCCE; // JMP	$0000DCCE
}*/
/*ROMFUNC(rom_4F68) {
	DEF_ROMLOC(4F68): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(4F6A): move_toreg_8(read_8(A0 + 0x24), &D0); // MOVE.B	36(A0),D0
	DEF_ROMLOC(4F6E): move_toreg_16(read_16(0x4F7C + (s16)(D0 & 0xffff)), &D1); // MOVE.W	12(PC,D0),D1
	DEF_ROMLOC(4F72): rom_4F7C + (s16)(D1 & 0xffff)(); // JSR	8(PC,D1)
	DEF_ROMLOC(4F76): goto rom_DC92; // JMP	$0000DC92
}*/
/*ROMFUNC(rom_4F84) {
	DEF_ROMLOC(4F84): add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
	DEF_ROMLOC(4F88): move_tomem_16(0xA0, A0 + 0x8); // MOVE.W	#$00A0,8(A0)
	DEF_ROMLOC(4F8E): move_tomem_16(0xC0, A0 + 0xC); // MOVE.W	#$00C0,12(A0)
	DEF_ROMLOC(4F94): move_tomem_32(0x21CF4, A0 + 0x4); // MOVE.L	#$00021CF4,4(A0)
	DEF_ROMLOC(4F9C): move_tomem_16(0x780, A0 + 0x2); // MOVE.W	#$0780,2(A0)
	DEF_ROMLOC(4FA2): move_tomem_8(0x4, A0 + 0x1); // MOVE.B	#$04,1(A0)
	DEF_ROMLOC(4FA8): move_tomem_8(0x2, A0 + 0x18); // MOVE.B	#$02,24(A0)
	DEF_ROMLOC(4FAE): move_tomem_8(0x1D, A0 + 0x1C); // MOVE.B	#$1D,28(A0)
	DEF_ROMLOC(4FB4): move_tomem_16(0x400, A0 + 0x12); // MOVE.W	#$0400,18(A0)
	rom_4FBA(); // Detected flow into next function
}*/
/*ROMFUNC(rom_4FBA) {
	DEF_ROMLOC(4FBA): cmp_tomem_16(0x1A0, A0 + 0xC); // CMPI.W	#$01A0,12(A0)
	DEF_ROMLOC(4FC0): if (!CCR_EQ) goto rom_4FE0; // BNE.B	$4FE0
	DEF_ROMLOC(4FC2): add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
	DEF_ROMLOC(4FC6): clr_mem_16(A0 + 0x12); // CLR.W	18(A0)
	DEF_ROMLOC(4FCA): move_tomem_32(0x5062, A0 + 0x4); // MOVE.L	#$00005062,4(A0)
	DEF_ROMLOC(4FD2): move_tomem_16(0xFFFF8500, A0 + 0x2); // MOVE.W	#$8500,2(A0)
	DEF_ROMLOC(4FD8): move_tomem_8(0x0, A0 + 0x1C); // MOVE.B	#$00,28(A0)
	rom_4FF2(); // BRA.B	$4FF2
}*/
/*ROMFUNC(rom_4FE0) {
	DEF_ROMLOC(4FE0): rom_DC6C(); // JSR	$0000DC6C
	DEF_ROMLOC(4FE6): rom_14098(); // JSR	$00014098
	DEF_ROMLOC(4FEC): goto rom_14312; // JMP	$00014312
}*/
/*ROMFUNC(rom_4FF2) {
	DEF_ROMLOC(4FF2): tst_mem_8(0xFFFFF605); // TST.B	$F605
	DEF_ROMLOC(4FF6): if (CCR_MI) goto rom_5004; // BMI.B	$5004
	DEF_ROMLOC(4FF8): move_toreg_32(0x5054, &A1); // LEA.L	$00005054,A1
	DEF_ROMLOC(4FFE): goto rom_ADA2; // JMP	$0000ADA2
}*/
/*ROMFUNC(rom_5004) {
	DEF_ROMLOC(5004): add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
	DEF_ROMLOC(5008): move_tomem_32(0x21CF4, A0 + 0x4); // MOVE.L	#$00021CF4,4(A0)
	DEF_ROMLOC(5010): move_tomem_16(0x780, A0 + 0x2); // MOVE.W	#$0780,2(A0)
	DEF_ROMLOC(5016): move_tomem_8(0x1E, A0 + 0x1C); // MOVE.B	#$1E,28(A0)
	DEF_ROMLOC(501C): clr_mem_16(A0 + 0x14); // CLR.W	20(A0)
	DEF_ROMLOC(5020): sub_tomem_16(0x8, A0 + 0xC); // SUBQ.W	#$08,12(A0)
	DEF_ROMLOC(5024): move_toreg_8(0xFFFFFFE0, &D0); // MOVE.B	#$E0,D0
	DEF_ROMLOC(5028): rom_1394(); // BSR.W	$1394
	rom_502C(); // Detected flow into next function
}*/
/*ROMFUNC(rom_502C) {
	DEF_ROMLOC(502C): cmp_tomem_16(0x800, A0 + 0x14); // CMPI.W	#$0800,20(A0)
	DEF_ROMLOC(5032): if (!CCR_EQ) goto rom_503C; // BNE.B	$503C
	DEF_ROMLOC(5034): move_tomem_16(0x1000, A0 + 0x10); // MOVE.W	#$1000,16(A0)
	rom_5042(); // BRA.B	$5042
}*/
/*ROMFUNC(rom_503C) {
	DEF_ROMLOC(503C): add_tomem_16(0x20, A0 + 0x14); // ADDI.W	#$0020,20(A0)
	rom_5042(); // Detected flow into next function
}*/
/*ROMFUNC(rom_5042) {
	DEF_ROMLOC(5042): rom_DC6C(); // JSR	$0000DC6C
	DEF_ROMLOC(5048): rom_14098(); // JSR	$00014098
	DEF_ROMLOC(504E): goto rom_14312; // JMP	$00014312
}*/
/*ROMFUNC(rom_5054) {
	DEF_ROMLOC(5054): or_toreg_8(0x1, &D2); // ORI.B	#$01,D2
	DEF_ROMLOC(5058): btst_toreg_32(D0, &D1); // BTST.L	D0,D1
	DEF_ROMLOC(505A): btst_toreg_32(D0, &D2); // BTST.L	D0,D2
	DEF_ROMLOC(505C): and_toreg_8(0x3, &D2); // ANDI.B	#$03,D2
	rom_50F2(); // Detected flow into next function
}*/
/*ROMFUNC(rom_1D104) {
	DEF_ROMLOC(1D104): move_tomem_32(0x5F800003, 0xC00004); // MOVE.L	#$5F800003,$00C00004
	DEF_ROMLOC(1D10E): move_toreg_32(0xC00000, &A6); // LEA.L	$00C00000,A6
	DEF_ROMLOC(1D114): move_toreg_32(0x1D16C, &A2); // LEA.L	$0001D16C,A2
	DEF_ROMLOC(1D11A): move_toreg_32(0x1, &D6); // MOVEQ.L	$01,D6
	DEF_ROMLOC(1D11C): move_toreg_32(0x0, &D4); // MOVEQ.L	$00,D4
	DEF_ROMLOC(1D11E): move_toreg_32(0x1D2A6, &A1); // LEA.L	390(PC),A1
	rom_1D122(); // Detected flow into next function
}*/
/*ROMFUNC(rom_1D122) {
	DEF_ROMLOC(1D122): move_toreg_32(0x0, &D2); // MOVEQ.L	$00,D2
	DEF_ROMLOC(1D124): move_toreg_32(read_32((A2 += 4, A2 - 4)), &D3); // MOVE.L	(A2)+,D3
	rom_1D126(); // Detected flow into next function
}*/
/*ROMFUNC(rom_1D126) {
	DEF_ROMLOC(1D126): sub_toreg_32(D3, &D1); // SUB.L	D3,D1
	DEF_ROMLOC(1D128): if (CCR_CS) goto rom_1D12E; // BCS.B	$1D12E
	DEF_ROMLOC(1D12A): add_toreg_16(0x1, &D2); // ADDQ.W	#$01,D2
	rom_1D126(); // BRA.B	$1D126
}*/
/*ROMFUNC(rom_1D12E) {
	DEF_ROMLOC(1D12E): add_toreg_32(D3, &D1); // ADD.L	D3,D1
	DEF_ROMLOC(1D130): lsl_toreg_16(0x6, &D2); // LSL.W	#$06,D2
	DEF_ROMLOC(1D132): move_toreg_32((s32)A1 + (s8)0x0 + (s16)D2, &A3); // LEA.L	0(A1,D2),A3
	DEF_ROMLOC(1D136): move_tomem_32(read_32((A3 += 4, A3 - 4)), A6); // MOVE.L	(A3)+,(A6)
	DEF_ROMLOC(1D138): move_tomem_32(read_32((A3 += 4, A3 - 4)), A6); // MOVE.L	(A3)+,(A6)
	DEF_ROMLOC(1D13A): move_tomem_32(read_32((A3 += 4, A3 - 4)), A6); // MOVE.L	(A3)+,(A6)
	DEF_ROMLOC(1D13C): move_tomem_32(read_32((A3 += 4, A3 - 4)), A6); // MOVE.L	(A3)+,(A6)
	DEF_ROMLOC(1D13E): move_tomem_32(read_32((A3 += 4, A3 - 4)), A6); // MOVE.L	(A3)+,(A6)
	DEF_ROMLOC(1D140): move_tomem_32(read_32((A3 += 4, A3 - 4)), A6); // MOVE.L	(A3)+,(A6)
	DEF_ROMLOC(1D142): move_tomem_32(read_32((A3 += 4, A3 - 4)), A6); // MOVE.L	(A3)+,(A6)
	DEF_ROMLOC(1D144): move_tomem_32(read_32((A3 += 4, A3 - 4)), A6); // MOVE.L	(A3)+,(A6)
	DEF_ROMLOC(1D146): move_tomem_32(read_32((A3 += 4, A3 - 4)), A6); // MOVE.L	(A3)+,(A6)
	DEF_ROMLOC(1D148): move_tomem_32(read_32((A3 += 4, A3 - 4)), A6); // MOVE.L	(A3)+,(A6)
	DEF_ROMLOC(1D14A): move_tomem_32(read_32((A3 += 4, A3 - 4)), A6); // MOVE.L	(A3)+,(A6)
	DEF_ROMLOC(1D14C): move_tomem_32(read_32((A3 += 4, A3 - 4)), A6); // MOVE.L	(A3)+,(A6)
	DEF_ROMLOC(1D14E): move_tomem_32(read_32((A3 += 4, A3 - 4)), A6); // MOVE.L	(A3)+,(A6)
	DEF_ROMLOC(1D150): move_tomem_32(read_32((A3 += 4, A3 - 4)), A6); // MOVE.L	(A3)+,(A6)
	DEF_ROMLOC(1D152): move_tomem_32(read_32((A3 += 4, A3 - 4)), A6); // MOVE.L	(A3)+,(A6)
	DEF_ROMLOC(1D154): move_tomem_32(read_32((A3 += 4, A3 - 4)), A6); // MOVE.L	(A3)+,(A6)
	DEF_ROMLOC(1D156): dec_reg_16(&D6); if ((D6 & 0xffff) != 0xffff) goto rom_1D122; // DBF.W	D6,$1D122
	DEF_ROMLOC(1D15A): return; // RTS
	DEF_ROMLOC(1D15C): or_toreg_8(0xFFFFFFA0, &D1); // ORI.B	#$A0,D1
	DEF_ROMLOC(1D160): or_toreg_8(0x10, &D0); // ORI.B	#$10,D0
	DEF_ROMLOC(1D164): or_toreg_8(0xFFFFFFE8, &D0); // ORI.B	#$E8,D0
	DEF_ROMLOC(1D168): or_toreg_8(0x64, &D0); // ORI.B	#$64,D0
	DEF_ROMLOC(1D16C): or_toreg_8(0xA, &D0); // ORI.B	#$0A,D0
	DEF_ROMLOC(1D170): or_toreg_8(0x1, &D0); // ORI.B	#$01,D0
	rom_1D174(); // Detected flow into next function
}*/