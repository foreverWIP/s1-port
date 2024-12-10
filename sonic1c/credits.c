// #define CHECK_STUFF(loc) 1
#include "opcodes.h"
#include "system.h"

/*ROMFUNC(rom_57D2) {
	DEF_ROMLOC(57D2): rom_15D6(); // BSR.W	$15D6
	DEF_ROMLOC(57D6): rom_1E4A(); // BSR.W	$1E4A
	DEF_ROMLOC(57DA): move_toreg_32(0xC00004, &A6); // LEA.L	$00C00004,A6
	DEF_ROMLOC(57E0): move_tomem_16(0xFFFF8004, A6); // MOVE.W	#$8004,(A6)
	DEF_ROMLOC(57E4): move_tomem_16(0xFFFF8230, A6); // MOVE.W	#$8230,(A6)
	DEF_ROMLOC(57E8): move_tomem_16(0xFFFF8407, A6); // MOVE.W	#$8407,(A6)
	DEF_ROMLOC(57EC): move_tomem_16(0xFFFF9001, A6); // MOVE.W	#$9001,(A6)
	DEF_ROMLOC(57F0): move_tomem_16(0xFFFF9200, A6); // MOVE.W	#$9200,(A6)
	DEF_ROMLOC(57F4): move_tomem_16(0xFFFF8B03, A6); // MOVE.W	#$8B03,(A6)
	DEF_ROMLOC(57F8): move_tomem_16(0xFFFF8720, A6); // MOVE.W	#$8720,(A6)
	DEF_ROMLOC(57FC): clr_mem_8(0xFFFFF64E); // CLR.B	$F64E
	DEF_ROMLOC(5800): rom_12C4(); // BSR.W	$12C4
	DEF_ROMLOC(5804): move_toreg_32(0xFFFFD000, &A1); // LEA.L	$D000,A1
	DEF_ROMLOC(5808): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(580A): move_toreg_16(0x7FF, &D1); // MOVE.W	#$07FF,D1
	DEF_ROMLOC(580E): move_tomem_32(D0, (A1 += 4, A1 - 4)); // MOVE.L	D0,(A1)+
	DEF_ROMLOC(5810): dec_reg_16(&D1); if ((D1 & 0xffff) != 0xffff) goto rom_580E; // DBF.W	D1,$580E
	DEF_ROMLOC(5814): move_tomem_32(0x74000002, 0xC00004); // MOVE.L	#$74000002,$00C00004
	DEF_ROMLOC(581E): move_toreg_32(0x6203A, &A0); // LEA.L	$0006203A,A0
	DEF_ROMLOC(5824): rom_1438(); // BSR.W	$1438
	DEF_ROMLOC(5828): move_toreg_32(0xFFFFFB80, &A1); // LEA.L	$FB80,A1
	DEF_ROMLOC(582C): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(582E): move_toreg_16(0x1F, &D1); // MOVE.W	#$001F,D1
	DEF_ROMLOC(5832): move_tomem_32(D0, (A1 += 4, A1 - 4)); // MOVE.L	D0,(A1)+
	DEF_ROMLOC(5834): dec_reg_16(&D1); if ((D1 & 0xffff) != 0xffff) goto rom_5832; // DBF.W	D1,$5832
	DEF_ROMLOC(5838): move_toreg_32(0x3, &D0); // MOVEQ.L	$03,D0
	DEF_ROMLOC(583A): rom_20F4(); // BSR.W	$20F4
	DEF_ROMLOC(583E): move_tomem_8(0xFFFFFF8A, 0xFFFFD080); // MOVE.B	#$8A,$D080
	DEF_ROMLOC(5844): rom_D9C6(); // JSR	$0000D9C6
	DEF_ROMLOC(584A): rom_DCEC(); // JSR	$0000DCEC
	DEF_ROMLOC(5850): rom_58A6(); // BSR.W	$58A6
	DEF_ROMLOC(5854): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(5856): move_toreg_8(read_8(0xFFFFFE10), &D0); // MOVE.B	$FE10,D0
	DEF_ROMLOC(585A): lsl_toreg_16(0x4, &D0); // LSL.W	#$04,D0
	DEF_ROMLOC(585C): move_toreg_32(0x1DD16, &A2); // LEA.L	$0001DD16,A2
	DEF_ROMLOC(5862): move_toreg_32((s32)A2 + (s8)0x0 + (s16)D0, &A2); // LEA.L	0(A2,D0),A2
	DEF_ROMLOC(5866): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(5868): move_toreg_8(read_8(A2), &D0); // MOVE.B	(A2),D0
	DEF_ROMLOC(586A): if (CCR_EQ) goto rom_5870; // BEQ.B	$5870
	DEF_ROMLOC(586C): rom_1578(); // BSR.W	$1578
	rom_5870(); // Detected flow into next function
}*/
/*ROMFUNC(rom_5870) {
	DEF_ROMLOC(5870): move_toreg_32(0x1, &D0); // MOVEQ.L	$01,D0
	DEF_ROMLOC(5872): rom_1578(); // BSR.W	$1578
	DEF_ROMLOC(5876): move_tomem_16(0x78, 0xFFFFF614); // MOVE.W	#$0078,$F614
	DEF_ROMLOC(587C): rom_1DA4(); // BSR.W	$1DA4
	rom_5880(); // Detected flow into next function
}*/
/*ROMFUNC(rom_5880) {
	DEF_ROMLOC(5880): move_tomem_8(0x4, 0xFFFFF62A); // MOVE.B	#$04,$F62A
	DEF_ROMLOC(5886): rom_29A0(); // BSR.W	$29A0
	DEF_ROMLOC(588A): rom_15E4(); // BSR.W	$15E4
	DEF_ROMLOC(588E): tst_mem_16(0xFFFFF614); // TST.W	$F614
	DEF_ROMLOC(5892): if (!CCR_EQ) goto rom_5880; // BNE.B	$5880
	DEF_ROMLOC(5894): tst_mem_32(0xFFFFF680); // TST.L	$F680
	DEF_ROMLOC(5898): if (!CCR_EQ) goto rom_5880; // BNE.B	$5880
	DEF_ROMLOC(589A): cmp_tomem_16(0x9, 0xFFFFFFF4); // CMPI.W	#$0009,$FFF4
	DEF_ROMLOC(58A0): if (CCR_EQ) goto rom_593A; // BEQ.W	$593A
	DEF_ROMLOC(58A4): return; // RTS
}*/
/*ROMFUNC(rom_58A6) {
	DEF_ROMLOC(58A6): move_toreg_16(read_16(0xFFFFFFF4), &D0); // MOVE.W	$FFF4,D0
	DEF_ROMLOC(58AA): and_toreg_16(0xF, &D0); // ANDI.W	#$000F,D0
	DEF_ROMLOC(58AE): add_toreg_16(D0, &D0); // ADD.W	D0,D0
	DEF_ROMLOC(58B0): move_toreg_16(read_16(0x5906 + (s16)(D0 & 0xffff)), &D0); // MOVE.W	84(PC,D0),D0
	DEF_ROMLOC(58B4): move_tomem_16(D0, 0xFFFFFE10); // MOVE.W	D0,$FE10
	DEF_ROMLOC(58B8): add_tomem_16(0x1, 0xFFFFFFF4); // ADDQ.W	#$01,$FFF4
	DEF_ROMLOC(58BC): cmp_tomem_16(0x9, 0xFFFFFFF4); // CMPI.W	#$0009,$FFF4
	DEF_ROMLOC(58C2): if (CCR_CC) goto rom_5904; // BCC.B	$5904
	DEF_ROMLOC(58C4): move_tomem_16(0xFFFF8001, 0xFFFFFFF0); // MOVE.W	#$8001,$FFF0
	DEF_ROMLOC(58CA): move_tomem_8(0x8, 0xFFFFF600); // MOVE.B	#$08,$F600
	DEF_ROMLOC(58D0): move_tomem_8(0x3, 0xFFFFFE12); // MOVE.B	#$03,$FE12
	DEF_ROMLOC(58D6): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(58D8): move_tomem_16(D0, 0xFFFFFE20); // MOVE.W	D0,$FE20
	DEF_ROMLOC(58DC): move_tomem_32(D0, 0xFFFFFE22); // MOVE.L	D0,$FE22
	DEF_ROMLOC(58E0): move_tomem_32(D0, 0xFFFFFE26); // MOVE.L	D0,$FE26
	DEF_ROMLOC(58E4): move_tomem_8(D0, 0xFFFFFE30); // MOVE.B	D0,$FE30
	DEF_ROMLOC(58E8): cmp_tomem_16(0x4, 0xFFFFFFF4); // CMPI.W	#$0004,$FFF4
	DEF_ROMLOC(58EE): if (!CCR_EQ) goto rom_5904; // BNE.B	$5904
	DEF_ROMLOC(58F0): move_toreg_32(0x5916, &A1); // LEA.L	$00005916,A1
	DEF_ROMLOC(58F6): move_toreg_32(0xFFFFFE30, &A2); // LEA.L	$FE30,A2
	DEF_ROMLOC(58FA): move_toreg_16(0x8, &D0); // MOVE.W	#$0008,D0
	rom_58FE(); // Detected flow into next function
}*/
/*ROMFUNC(rom_58FE) {
	DEF_ROMLOC(58FE): move_tomem_32(read_32((A1 += 4, A1 - 4)), (A2 += 4, A2 - 4)); // MOVE.L	(A1)+,(A2)+
	DEF_ROMLOC(5900): dec_reg_16(&D0); if ((D0 & 0xffff) != 0xffff) goto rom_58FE; // DBF.W	D0,$58FE
	rom_5904(); // Detected flow into next function
}*/
/*ROMFUNC(rom_5904) {
	DEF_ROMLOC(5904): return; // RTS
}*/
/*ROMFUNC(rom_5906) {
	DEF_ROMLOC(5906): or_toreg_8(0x1, &D0); // ORI.B	#$01,D0
	DEF_ROMLOC(590A): sub_toreg_8(0x2, &D2); // SUBI.B	#$02,D2
	DEF_ROMLOC(590E): btst_toreg_32(D1, &D2); // BTST.L	D1,D2
	DEF_ROMLOC(5910): btst_toreg_32(D2, &D0); // BTST.L	D2,D0
	DEF_ROMLOC(5912): btst_toreg_32(D2, &D1); // BTST.L	D2,D1
	DEF_ROMLOC(5914): or_toreg_8(0x1, &D0); // ORI.B	#$01,D0
	DEF_ROMLOC(5918): eor_toreg_8(0x2C, &D0); // EORI.B	#$2C,D0
	rom_5916(); // Detected flow into next function
}*/
/*ROMFUNC(rom_5916) {
	DEF_ROMLOC(5916): btst_toreg_32(D0, &D1); // BTST.L	D0,D1
	DEF_ROMLOC(5918): eor_toreg_8(0x2C, &D0); // EORI.B	#$2C,D0
	rom_593A(); // Detected flow into next function
}*/
/*ROMFUNC(rom_593A) {
	DEF_ROMLOC(593A): rom_15D6(); // BSR.W	$15D6
	DEF_ROMLOC(593E): rom_1E4A(); // BSR.W	$1E4A
	DEF_ROMLOC(5942): move_toreg_32(0xC00004, &A6); // LEA.L	$00C00004,A6
	DEF_ROMLOC(5948): move_tomem_16(0xFFFF8004, A6); // MOVE.W	#$8004,(A6)
	DEF_ROMLOC(594C): move_tomem_16(0xFFFF8230, A6); // MOVE.W	#$8230,(A6)
	DEF_ROMLOC(5950): move_tomem_16(0xFFFF8407, A6); // MOVE.W	#$8407,(A6)
	DEF_ROMLOC(5954): move_tomem_16(0xFFFF9001, A6); // MOVE.W	#$9001,(A6)
	DEF_ROMLOC(5958): move_tomem_16(0xFFFF9200, A6); // MOVE.W	#$9200,(A6)
	DEF_ROMLOC(595C): move_tomem_16(0xFFFF8B03, A6); // MOVE.W	#$8B03,(A6)
	DEF_ROMLOC(5960): move_tomem_16(0xFFFF8720, A6); // MOVE.W	#$8720,(A6)
	DEF_ROMLOC(5964): clr_mem_8(0xFFFFF64E); // CLR.B	$F64E
	DEF_ROMLOC(5968): rom_12C4(); // BSR.W	$12C4
	DEF_ROMLOC(596C): move_toreg_32(0xFFFFD000, &A1); // LEA.L	$D000,A1
	DEF_ROMLOC(5970): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(5972): move_toreg_16(0x7FF, &D1); // MOVE.W	#$07FF,D1
	DEF_ROMLOC(5976): move_tomem_32(D0, (A1 += 4, A1 - 4)); // MOVE.L	D0,(A1)+
	DEF_ROMLOC(5978): dec_reg_16(&D1); if ((D1 & 0xffff) != 0xffff) goto rom_5976; // DBF.W	D1,$5976
	DEF_ROMLOC(597C): move_toreg_32(0x1D, &D0); // MOVEQ.L	$1D,D0
	DEF_ROMLOC(597E): rom_16E4(); // BSR.W	$16E4
	DEF_ROMLOC(5982): move_toreg_32(0xFFFFFB80, &A1); // LEA.L	$FB80,A1
	DEF_ROMLOC(5986): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(5988): move_toreg_16(0x1F, &D1); // MOVE.W	#$001F,D1
	DEF_ROMLOC(598C): move_tomem_32(D0, (A1 += 4, A1 - 4)); // MOVE.L	D0,(A1)+
	DEF_ROMLOC(598E): dec_reg_16(&D1); if ((D1 & 0xffff) != 0xffff) goto rom_598C; // DBF.W	D1,$598C
	DEF_ROMLOC(5992): move_toreg_32(0x13, &D0); // MOVEQ.L	$13,D0
	DEF_ROMLOC(5994): rom_20F4(); // BSR.W	$20F4
	DEF_ROMLOC(5998): clr_mem_16(0xFFFFFBC0); // CLR.W	$FBC0
	DEF_ROMLOC(599C): move_tomem_8(0xFFFFFF8B, 0xFFFFD080); // MOVE.B	#$8B,$D080
	DEF_ROMLOC(59A2): rom_D9C6(); // JSR	$0000D9C6
	DEF_ROMLOC(59A8): rom_DCEC(); // JSR	$0000DCEC
	DEF_ROMLOC(59AE): move_tomem_16(0x708, 0xFFFFF614); // MOVE.W	#$0708,$F614
	DEF_ROMLOC(59B4): rom_1DA4(); // BSR.W	$1DA4
	rom_59B8(); // Detected flow into next function
}*/
/*ROMFUNC(rom_59B8) {
	DEF_ROMLOC(59B8): rom_13A0(); // BSR.W	$13A0
	DEF_ROMLOC(59BC): move_tomem_8(0x4, 0xFFFFF62A); // MOVE.B	#$04,$F62A
	DEF_ROMLOC(59C2): rom_29A0(); // BSR.W	$29A0
	DEF_ROMLOC(59C6): rom_D9C6(); // JSR	$0000D9C6
	DEF_ROMLOC(59CC): rom_DCEC(); // JSR	$0000DCEC
	DEF_ROMLOC(59D2): and_tomem_8(0xFFFFFF80, 0xFFFFF605); // ANDI.B	#$80,$F605
	DEF_ROMLOC(59D8): if (!CCR_EQ) goto rom_59E8; // BNE.B	$59E8
	DEF_ROMLOC(59DA): tst_mem_16(0xFFFFF614); // TST.W	$F614
	DEF_ROMLOC(59DE): if (CCR_EQ) goto rom_59E8; // BEQ.B	$59E8
	DEF_ROMLOC(59E0): cmp_tomem_8(0x1C, 0xFFFFF600); // CMPI.B	#$1C,$F600
	DEF_ROMLOC(59E6): if (CCR_EQ) goto rom_59B8; // BEQ.B	$59B8
	rom_59E8(); // Detected flow into next function
}*/
/*ROMFUNC(rom_59E8) {
	DEF_ROMLOC(59E8): move_tomem_8(0x0, 0xFFFFF600); // MOVE.B	#$00,$F600
	DEF_ROMLOC(59EE): return; // RTS
}*/
ROMFUNC(rom_59F0) {
	u8 switchindex = 0;
	DEF_ROMLOC(59F0): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(59F2): move_toreg_8(read_8(A0 + 0x24), &D0); switchindex = D0 / 2; // MOVE.B	36(A0),D0
	DEF_ROMLOC(59F6): move_toreg_16(read_16(0x5A04 + (s16)(D0 & 0xffff)), &D1); // MOVE.W	12(PC,D0),D1
	// DEF_ROMLOC(59FA): rom_5A04 + (s16)(D1 & 0xffff)(); // JSR	8(PC,D1)
	DEF_ROMLOC(59FA):
		switch (switchindex) {
			case 0: rom_5A0C(); break;
			case 1: rom_5A5C(); break;
			case 2: rom_5A68(); break;
			case 3: rom_5A9C(); break;
		}
	DEF_ROMLOC(59FE): {rom_DC92();return;} // JMP	$0000DC92
}
ROMFUNC(rom_5A0C) {
	DEF_ROMLOC(5A0C): add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
	DEF_ROMLOC(5A10): move_tomem_16(0x120, A0 + 0x8); // MOVE.W	#$0120,8(A0)
	DEF_ROMLOC(5A16): move_tomem_16(0xF4, A0 + 0xA); // MOVE.W	#$00F4,10(A0)
	DEF_ROMLOC(5A1C): move_tomem_32(0x5BCA, A0 + 0x4); // MOVE.L	#$00005BCA,4(A0)
	DEF_ROMLOC(5A24): move_tomem_16(0x3E1, A0 + 0x2); // MOVE.W	#$03E1,2(A0)
	DEF_ROMLOC(5A2A): move_tomem_8(0x0, A0 + 0x1); // MOVE.B	#$00,1(A0)
	DEF_ROMLOC(5A30): move_tomem_8(0x2, A0 + 0x18); // MOVE.B	#$02,24(A0)
	DEF_ROMLOC(5A36): move_tomem_8(0x2, A0 + 0x1C); // MOVE.B	#$02,28(A0)
	DEF_ROMLOC(5A3C): cmp_tomem_8(0x6, 0xFFFFFE57); // CMPI.B	#$06,$FE57
	DEF_ROMLOC(5A42): if (CCR_EQ) {rom_5A5C();return;} // BEQ.B	$5A5C
	DEF_ROMLOC(5A44): move_tomem_8(0xFFFFFF8A, 0xFFFFD0C0); // MOVE.B	#$8A,$D0C0
	DEF_ROMLOC(5A4A): move_tomem_16(0x9, 0xFFFFFFF4); // MOVE.W	#$0009,$FFF4
	DEF_ROMLOC(5A50): move_tomem_8(0xFFFFFF8C, 0xFFFFD800); // MOVE.B	#$8C,$D800
	DEF_ROMLOC(5A56): move_tomem_8(0x0, A0 + 0x1C); // MOVE.B	#$00,28(A0)
}
ROMFUNC(rom_5A5C) {
	DEF_ROMLOC(5A5C): move_toreg_32(0x5AB0, &A1); // LEA.L	$00005AB0,A1
	DEF_ROMLOC(5A62): {rom_ADA2();return;} // JMP	$0000ADA2
}
ROMFUNC(rom_5A68) {
	DEF_ROMLOC(5A68): add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
	DEF_ROMLOC(5A6C): move_toreg_32(0x2, &D0); // MOVEQ.L	$02,D0
	DEF_ROMLOC(5A6E): btst_tomem_8(0x0, A0 + 0x1C); // BTST.B	#$00,28(A0)
	DEF_ROMLOC(5A74): if (CCR_EQ) goto rom_5A78; // BEQ.B	$5A78
	DEF_ROMLOC(5A76): neg_reg_16(&D0); // NEG.W	D0
	DEF_ROMLOC(5A78): move_toreg_32(0xFFFFD800, &A1); // LEA.L	$D800,A1
	DEF_ROMLOC(5A7C): move_toreg_32(0x5, &D1); // MOVEQ.L	$05,D1
	DEF_ROMLOC(5A7E): move_tomem_8(D0, A1 + 0x3E); // MOVE.B	D0,62(A1)
	DEF_ROMLOC(5A82): move_toreg_16(D0, &D2); // MOVE.W	D0,D2
	DEF_ROMLOC(5A84): asl_toreg_16(0x3, &D2); // ASL.W	#$03,D2
	DEF_ROMLOC(5A86): add_tomem_8(D2, A1 + 0x26); // ADD.B	D2,38(A1)
	DEF_ROMLOC(5A8A): move_toreg_32(A1 + 0x40, &A1); // LEA.L	64(A1),A1
	DEF_ROMLOC(5A8E): dec_reg_16(&D1); if ((D1 & 0xffff) != 0xffff) goto rom_5A7E; // DBF.W	D1,$5A7E
	DEF_ROMLOC(5A92): add_tomem_8(0x1, A0 + 0x1A); // ADDQ.B	#$01,26(A0)
	DEF_ROMLOC(5A96): move_tomem_16(0x70, A0 + 0x30); // MOVE.W	#$0070,48(A0)
	rom_5A9C(); // Detected flow into next function
}
ROMFUNC(rom_5A9C) {
	DEF_ROMLOC(5A9C): sub_tomem_16(0x1, A0 + 0x30); // SUBQ.W	#$01,48(A0)
	DEF_ROMLOC(5AA0): if (CCR_PL) goto rom_5AAE; // BPL.B	$5AAE
	DEF_ROMLOC(5AA2): bchg_tomem_8(0x0, A0 + 0x1C); // BCHG.B	#$00,28(A0)
	DEF_ROMLOC(5AA8): move_tomem_8(0x2, A0 + 0x24); // MOVE.B	#$02,36(A0)
	DEF_ROMLOC(5AAE): return; // RTS
	DEF_ROMLOC(5AB0): or_toreg_8(0xA, &D6); // ORI.B	#$0A,D6
	rom_5AD0(); // Detected flow into next function
}
ROMFUNC(rom_5AD0) {
	u8 switchindex = 0;
	DEF_ROMLOC(5AD0): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(5AD2): move_toreg_8(read_8(A0 + 0x24), &D0); switchindex = D0 / 2; // MOVE.B	36(A0),D0
	DEF_ROMLOC(5AD6): move_toreg_16(read_16(0x5AE4 + (s16)(D0 & 0xffff)), &D1); // MOVE.W	12(PC,D0),D1
	// DEF_ROMLOC(5ADA): rom_5AE4 + (s16)(D1 & 0xffff)(); // JSR	8(PC,D1)
	DEF_ROMLOC(5ADA):
		switch (switchindex) {
			case 0: rom_5AE8(); break;
			case 1: rom_5B74(); break;
		}
	DEF_ROMLOC(5ADE): {rom_DC92();return;} // JMP	$0000DC92
}
ROMFUNC(rom_5AE8) {
	DEF_ROMLOC(5AE8): move_toreg_32(A0, &A1); // MOVEA.L	A0,A1
	DEF_ROMLOC(5AEA): move_toreg_32(0x0, &D2); // MOVEQ.L	$00,D2
	DEF_ROMLOC(5AEC): move_toreg_32(0x0, &D3); // MOVEQ.L	$00,D3
	DEF_ROMLOC(5AEE): move_toreg_32(0x5, &D1); // MOVEQ.L	$05,D1
	DEF_ROMLOC(5AF0): sub_toreg_8(read_8(0xFFFFFE57), &D1); // SUB.B	$FE57,D1
	DEF_ROMLOC(5AF4): move_tomem_8(0xFFFFFF8C, A1); // MOVE.B	#$8C,(A1)
	DEF_ROMLOC(5AF8): add_tomem_8(0x2, A1 + 0x24); // ADDQ.B	#$02,36(A1)
	DEF_ROMLOC(5AFC): move_tomem_32(0x5788, A1 + 0x4); // MOVE.L	#$00005788,4(A1)
	DEF_ROMLOC(5B04): move_tomem_16(0x3C5, A1 + 0x2); // MOVE.W	#$03C5,2(A1)
	DEF_ROMLOC(5B0A): move_tomem_8(0x0, A1 + 0x1); // MOVE.B	#$00,1(A1)
	DEF_ROMLOC(5B10): move_tomem_8(0x1, A1 + 0x18); // MOVE.B	#$01,24(A1)
	DEF_ROMLOC(5B16): move_tomem_16(0x104, A1 + 0x8); // MOVE.W	#$0104,8(A1)
	DEF_ROMLOC(5B1C): move_tomem_16(0x120, A1 + 0x38); // MOVE.W	#$0120,56(A1)
	DEF_ROMLOC(5B22): move_tomem_16(0xEC, A1 + 0xA); // MOVE.W	#$00EC,10(A1)
	DEF_ROMLOC(5B28): move_tomem_16(read_16(A1 + 0xA), A1 + 0x3A); // MOVE.W	10(A1),58(A1)
	DEF_ROMLOC(5B2E): move_tomem_8(0x1C, A1 + 0x3C); // MOVE.B	#$1C,60(A1)
	DEF_ROMLOC(5B34): move_toreg_32(0xFFFFFE58, &A3); // LEA.L	$FE58,A3
	DEF_ROMLOC(5B38): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(5B3A): move_toreg_8(read_8(0xFFFFFE57), &D0); // MOVE.B	$FE57,D0
	DEF_ROMLOC(5B3E): sub_toreg_16(0x1, &D0); // SUBQ.W	#$01,D0
	DEF_ROMLOC(5B40): if (CCR_CS) goto rom_5B50; // BCS.B	$5B50
	DEF_ROMLOC(5B42): cmp_toreg_8(read_8((s32)A3 + (s8)0x0 + (s16)D0), &D2); // CMP.B	0(A3,D0),D2
	DEF_ROMLOC(5B46): if (!CCR_EQ) goto rom_5B4C; // BNE.B	$5B4C
	DEF_ROMLOC(5B48): add_toreg_8(0x1, &D2); // ADDQ.B	#$01,D2
	DEF_ROMLOC(5B4A): goto rom_5B38; // BRA.B	$5B38
	DEF_ROMLOC(5B4C): dec_reg_16(&D0); if ((D0 & 0xffff) != 0xffff) goto rom_5B42; // DBF.W	D0,$5B42
	DEF_ROMLOC(5B50): move_tomem_8(D2, A1 + 0x1A); // MOVE.B	D2,26(A1)
	DEF_ROMLOC(5B54): add_tomem_8(0x1, A1 + 0x1A); // ADDQ.B	#$01,26(A1)
	DEF_ROMLOC(5B58): add_toreg_8(0x1, &D2); // ADDQ.B	#$01,D2
	DEF_ROMLOC(5B5A): move_tomem_8(0xFFFFFF80, A1 + 0x26); // MOVE.B	#$80,38(A1)
	DEF_ROMLOC(5B60): move_tomem_8(D3, A1 + 0x1E); // MOVE.B	D3,30(A1)
	DEF_ROMLOC(5B64): move_tomem_8(D3, A1 + 0x1F); // MOVE.B	D3,31(A1)
	DEF_ROMLOC(5B68): add_toreg_16(0xA, &D3); // ADDI.W	#$000A,D3
	DEF_ROMLOC(5B6C): move_toreg_32(A1 + 0x40, &A1); // LEA.L	64(A1),A1
	DEF_ROMLOC(5B70): dec_reg_16(&D1); if ((D1 & 0xffff) != 0xffff) goto rom_5AF4; // DBF.W	D1,$5AF4
	rom_5B74(); // Detected flow into next function
}
ROMFUNC(rom_5B74) {
	DEF_ROMLOC(5B74): tst_mem_16(A0 + 0x3E); // TST.W	62(A0)
	DEF_ROMLOC(5B78): if (CCR_EQ) goto rom_5BC8; // BEQ.B	$5BC8
	DEF_ROMLOC(5B7A): tst_mem_8(A0 + 0x1E); // TST.B	30(A0)
	DEF_ROMLOC(5B7E): if (CCR_EQ) goto rom_5B86; // BEQ.B	$5B86
	DEF_ROMLOC(5B80): sub_tomem_8(0x1, A0 + 0x1E); // SUBQ.B	#$01,30(A0)
	DEF_ROMLOC(5B84): if (!CCR_EQ) goto rom_5B8E; // BNE.B	$5B8E
	DEF_ROMLOC(5B86): move_toreg_16(read_16(A0 + 0x3E), &D0); // MOVE.W	62(A0),D0
	DEF_ROMLOC(5B8A): add_tomem_16(D0, A0 + 0x26); // ADD.W	D0,38(A0)
	DEF_ROMLOC(5B8E): move_toreg_8(read_8(A0 + 0x26), &D0); // MOVE.B	38(A0),D0
	DEF_ROMLOC(5B92): if (CCR_EQ) goto rom_5B9A; // BEQ.B	$5B9A
	DEF_ROMLOC(5B94): cmp_toreg_8(0xFFFFFF80, &D0); // CMPI.B	#$80,D0
	DEF_ROMLOC(5B98): if (!CCR_EQ) goto rom_5BA4; // BNE.B	$5BA4
	DEF_ROMLOC(5B9A): clr_mem_16(A0 + 0x3E); // CLR.W	62(A0)
	DEF_ROMLOC(5B9E): move_tomem_8(read_8(A0 + 0x1F), A0 + 0x1E); // MOVE.B	31(A0),30(A0)
	DEF_ROMLOC(5BA4): rom_29D2(); // JSR	$000029D2
	DEF_ROMLOC(5BAA): move_toreg_32(0x0, &D4); // MOVEQ.L	$00,D4
	DEF_ROMLOC(5BAC): move_toreg_8(read_8(A0 + 0x3C), &D4); // MOVE.B	60(A0),D4
	DEF_ROMLOC(5BB0): muls_toreg_16(D4, &D1); // MULS.W	D4,D1
	DEF_ROMLOC(5BB2): asr_toreg_32(0x8, &D1); // ASR.L	#$08,D1
	DEF_ROMLOC(5BB4): muls_toreg_16(D4, &D0); // MULS.W	D4,D0
	DEF_ROMLOC(5BB6): asr_toreg_32(0x8, &D0); // ASR.L	#$08,D0
	DEF_ROMLOC(5BB8): add_toreg_16(read_16(A0 + 0x38), &D1); // ADD.W	56(A0),D1
	DEF_ROMLOC(5BBC): add_toreg_16(read_16(A0 + 0x3A), &D0); // ADD.W	58(A0),D0
	DEF_ROMLOC(5BC0): move_tomem_16(D1, A0 + 0x8); // MOVE.W	D1,8(A0)
	DEF_ROMLOC(5BC4): move_tomem_16(D0, A0 + 0xA); // MOVE.W	D0,10(A0)
	DEF_ROMLOC(5BC8): return; // RTS
}
/*ROMFUNC(rom_5D5E) {
	DEF_ROMLOC(5D5E): bchg_tomem_8(0x9, --A4); // BCHG.B	#$09,-(A4)
	rom_5D8C(); // Detected flow into next function
}*/
/*ROMFUNC(rom_5DCC) {
	DEF_ROMLOC(5DCC): or_tomem_8(0x2F, A7); // ORI.B	#$2F,(A7)
	DEF_ROMLOC(5DD0): or_tomem_8(0x1C, A2++); // ORI.B	#$1C,(A2)+
	DEF_ROMLOC(5DD4): eor_toreg_8(0x9, &D2); // EORI.B	#$09,D2
	DEF_ROMLOC(5DD8): or_toreg_8(0x1B, &D7); // ORI.B	#$1B,D7
	DEF_ROMLOC(5DDC): or_tomem_8(0x4B, A1 + 0x62); // ORI.B	#$4B,98(A1)
	rom_5DFC(); // Detected flow into next function
}*/
/*ROMFUNC(rom_5DFC) {
	DEF_ROMLOC(5DFC): or_toreg_8(0xFFFFFF83, &D4); // ORI.B	#$83,D4
	DEF_ROMLOC(5E00): or_tomem_32(0x2090005, A2); // ORI.L	#$02090005,(A2)
	rom_5E2C(); // Detected flow into next function
}*/
/*ROMFUNC(rom_5E4C) {
	DEF_ROMLOC(5E4C): or_tomem_8(0x52, --A5); // ORI.B	#$52,-(A5)
	DEF_ROMLOC(5E50): or_tomem_8(0x23, --A5); // ORI.B	#$23,-(A5)
	rom_5E6C(); // Detected flow into next function
}*/
/*ROMFUNC(rom_5E6C) {
	DEF_ROMLOC(5E6C): or_toreg_8(0x10, &D6); // ORI.B	#$10,D6
	DEF_ROMLOC(5E70): or_tomem_16(0x82F, (s32)A4 + (s8)0x1B + (s16)D2); // ORI.W	#$082F,27(A4,D2)
	DEF_ROMLOC(5E76): bchg_tomem_8(0x6, A4); // BCHG.B	#$06,(A4)
	DEF_ROMLOC(5E7A): and_tomem_8(0x60, --A0); // ANDI.B	#$60,-(A0)
	DEF_ROMLOC(5E7E): move_toreg_32(read_32((A5 += 4, A5 - 4)), &D0); // MOVE.L	(A5)+,D0
	DEF_ROMLOC(5E80): move_toreg_32(read_32(A4), &D4); // MOVE.L	(A4),D4
	DEF_ROMLOC(5E82): btst_tomem_8(0x9, A1); // BTST.B	#$09,(A1)
	DEF_ROMLOC(5E86): btst_tomem_8(0x3, A7++); // BTST.B	#$03,(A7)+
	DEF_ROMLOC(5E8A): btst_toreg_32(0x7, &D6); // BTST.L	#$07,D6
	DEF_ROMLOC(5E8E): and_tomem_8(0x30, --A6); // ANDI.B	#$30,-(A6)
	DEF_ROMLOC(5E92): or_toreg_8(0x0, &D0); // ORI.B	#$00,D0
	DEF_ROMLOC(5E96): or_toreg_8(0x0, &D0); // ORI.B	#$00,D0
	DEF_ROMLOC(5E9A): or_toreg_8(0x7, &D0); // ORI.B	#$07,D0
	rom_5E9C(); // Detected flow into next function
}*/
/*ROMFUNC(rom_5E9C) {
	DEF_ROMLOC(5E9C): or_toreg_8(0xFFFFFFFF, &D7); // ORI.B	#$FF,D7
	DEF_ROMLOC(5EA0): bchg_toreg_32(0xFFFFFFC2, &D7); // BCHG.L	#$C2,D7
	rom_5ECC(); // Detected flow into next function
}*/