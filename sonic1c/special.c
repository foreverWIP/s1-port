// #define CHECK_STUFF(loc) 1
#include "system.h"
#include "opcodes.h"

/*ROMFUNC(rom_45DE) {
	DEF_ROMLOC(45DE): move_toreg_16(0xCA, &D0); // MOVE.W	#$00CA,D0
	DEF_ROMLOC(45E2): rom_1394(); // BSR.W	$1394
	DEF_ROMLOC(45E6): rom_1F74(); // BSR.W	$1F74
	DEF_ROMLOC(45EA): move_tosr_16(0x2700, &SR); // MOVE.W	#$2700,SR
	DEF_ROMLOC(45EE): move_toreg_32(0xC00004, &A6); // LEA.L	$00C00004,A6
	DEF_ROMLOC(45F4): move_tomem_16(0xFFFF8B03, A6); // MOVE.W	#$8B03,(A6)
	DEF_ROMLOC(45F8): move_tomem_16(0xFFFF8004, A6); // MOVE.W	#$8004,(A6)
	DEF_ROMLOC(45FC): move_tomem_16(0xFFFF8AAF, 0xFFFFF624); // MOVE.W	#$8AAF,$F624
	DEF_ROMLOC(4602): move_tomem_16(0xFFFF9011, A6); // MOVE.W	#$9011,(A6)
	DEF_ROMLOC(4606): move_toreg_16(read_16(0xFFFFF60C), &D0); // MOVE.W	$F60C,D0
	DEF_ROMLOC(460A): and_toreg_8(0xFFFFFFBF, &D0); // ANDI.B	#$BF,D0
	DEF_ROMLOC(460E): move_tomem_16(D0, 0xC00004); // MOVE.W	D0,$00C00004
	DEF_ROMLOC(4614): rom_12C4(); // BSR.W	$12C4
	DEF_ROMLOC(4618): move_tosr_16(0x2300, &SR); // MOVE.W	#$2300,SR
	DEF_ROMLOC(461C): move_toreg_32(0xC00004, &A5); // LEA.L	$00C00004,A5
	DEF_ROMLOC(4622): move_tomem_16(0xFFFF8F01, A5); // MOVE.W	#$8F01,(A5)
	DEF_ROMLOC(4626): move_tomem_32(0x946F93FF, A5); // MOVE.L	#$946F93FF,(A5)
	DEF_ROMLOC(462C): move_tomem_16(0xFFFF9780, A5); // MOVE.W	#$9780,(A5)
	DEF_ROMLOC(4630): move_tomem_32(0x50000081, A5); // MOVE.L	#$50000081,(A5)
	DEF_ROMLOC(4636): move_tomem_16(0x0, 0xC00000); // MOVE.W	#$0000,$00C00000
	DEF_ROMLOC(463E): move_toreg_16(read_16(A5), &D1); // MOVE.W	(A5),D1
	DEF_ROMLOC(4640): btst_toreg_32(0x1, &D1); // BTST.L	#$01,D1
	DEF_ROMLOC(4644): if (!CCR_EQ) goto rom_463E; // BNE.B	$463E
	DEF_ROMLOC(4646): move_tomem_16(0xFFFF8F02, A5); // MOVE.W	#$8F02,(A5)
	DEF_ROMLOC(464A): rom_48A8(); // BSR.W	$48A8
	DEF_ROMLOC(464E): move_toreg_32(0x14, &D0); // MOVEQ.L	$14,D0
	DEF_ROMLOC(4650): rom_16E4(); // BSR.W	$16E4
	DEF_ROMLOC(4654): move_toreg_32(0xFFFFD000, &A1); // LEA.L	$D000,A1
	DEF_ROMLOC(4658): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(465A): move_toreg_16(0x7FF, &D1); // MOVE.W	#$07FF,D1
	DEF_ROMLOC(465E): move_tomem_32(D0, (A1 += 4, A1 - 4)); // MOVE.L	D0,(A1)+
	DEF_ROMLOC(4660): dec_reg_16(&D1); if ((D1 & 0xffff) != 0xffff) goto rom_465E; // DBF.W	D1,$465E
	DEF_ROMLOC(4664): move_toreg_32(0xFFFFF700, &A1); // LEA.L	$F700,A1
	DEF_ROMLOC(4668): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(466A): move_toreg_16(0x3F, &D1); // MOVE.W	#$003F,D1
	DEF_ROMLOC(466E): move_tomem_32(D0, (A1 += 4, A1 - 4)); // MOVE.L	D0,(A1)+
	DEF_ROMLOC(4670): dec_reg_16(&D1); if ((D1 & 0xffff) != 0xffff) goto rom_466E; // DBF.W	D1,$466E
	DEF_ROMLOC(4674): move_toreg_32(0xFFFFFE60, &A1); // LEA.L	$FE60,A1
	DEF_ROMLOC(4678): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(467A): move_toreg_16(0x27, &D1); // MOVE.W	#$0027,D1
	DEF_ROMLOC(467E): move_tomem_32(D0, (A1 += 4, A1 - 4)); // MOVE.L	D0,(A1)+
	DEF_ROMLOC(4680): dec_reg_16(&D1); if ((D1 & 0xffff) != 0xffff) goto rom_467E; // DBF.W	D1,$467E
	DEF_ROMLOC(4684): move_toreg_32(0xFFFFAA00, &A1); // LEA.L	$AA00,A1
	DEF_ROMLOC(4688): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(468A): move_toreg_16(0x7F, &D1); // MOVE.W	#$007F,D1
	DEF_ROMLOC(468E): move_tomem_32(D0, (A1 += 4, A1 - 4)); // MOVE.L	D0,(A1)+
	DEF_ROMLOC(4690): dec_reg_16(&D1); if ((D1 & 0xffff) != 0xffff) goto rom_468E; // DBF.W	D1,$468E
	DEF_ROMLOC(4694): clr_mem_8(0xFFFFF64E); // CLR.B	$F64E
	DEF_ROMLOC(4698): clr_mem_16(0xFFFFFE02); // CLR.W	$FE02
	DEF_ROMLOC(469C): move_toreg_32(0xA, &D0); // MOVEQ.L	$0A,D0
	DEF_ROMLOC(469E): rom_20F4(); // BSR.W	$20F4
	DEF_ROMLOC(46A2): rom_1BE32(); // JSR	$0001BE32
	DEF_ROMLOC(46A8): move_tomem_32(0x0, 0xFFFFF700); // MOVE.L	#$00000000,$F700
	DEF_ROMLOC(46B0): move_tomem_32(0x0, 0xFFFFF704); // MOVE.L	#$00000000,$F704
	DEF_ROMLOC(46B8): move_tomem_8(0x9, 0xFFFFD000); // MOVE.B	#$09,$D000
	DEF_ROMLOC(46BE): rom_496E(); // BSR.W	$496E
	DEF_ROMLOC(46C2): clr_mem_16(0xFFFFF780); // CLR.W	$F780
	DEF_ROMLOC(46C6): move_tomem_16(0x40, 0xFFFFF782); // MOVE.W	#$0040,$F782
	DEF_ROMLOC(46CC): move_toreg_16(0x89, &D0); // MOVE.W	#$0089,D0
	DEF_ROMLOC(46D0): rom_138E(); // BSR.W	$138E
	DEF_ROMLOC(46D4): move_tomem_16(0x0, 0xFFFFF790); // MOVE.W	#$0000,$F790
	DEF_ROMLOC(46DA): move_toreg_32(0x4082, &A1); // LEA.L	$00004082,A1
	DEF_ROMLOC(46E0): move_toreg_32(0x6, &D0); // MOVEQ.L	$06,D0
	DEF_ROMLOC(46E2): lsl_toreg_16(0x2, &D0); // LSL.W	#$02,D0
	DEF_ROMLOC(46E4): move_toreg_32(read_32((s32)A1 + (s8)0x0 + (s16)D0), &A1); // MOVEA.L	0(A1,D0),A1
	DEF_ROMLOC(46E8): move_tomem_8(read_8(A1 + 0x1), 0xFFFFF792); // MOVE.B	1(A1),$F792
	DEF_ROMLOC(46EE): sub_tomem_8(0x1, 0xFFFFF792); // SUBQ.B	#$01,$F792
	DEF_ROMLOC(46F2): clr_mem_16(0xFFFFFE20); // CLR.W	$FE20
	DEF_ROMLOC(46F6): clr_mem_8(0xFFFFFE1B); // CLR.B	$FE1B
	DEF_ROMLOC(46FA): move_tomem_16(0x0, 0xFFFFFE08); // MOVE.W	#$0000,$FE08
	DEF_ROMLOC(4700): move_tomem_16(0x708, 0xFFFFF614); // MOVE.W	#$0708,$F614
	DEF_ROMLOC(4706): tst_mem_8(0xFFFFFFE2); // TST.B	$FFE2
	DEF_ROMLOC(470A): if (CCR_EQ) goto rom_471A; // BEQ.B	$471A
	DEF_ROMLOC(470C): btst_tomem_8(0x6, 0xFFFFF604); // BTST.B	#$06,$F604
	DEF_ROMLOC(4712): if (CCR_EQ) goto rom_471A; // BEQ.B	$471A
	DEF_ROMLOC(4714): move_tomem_8(0x1, 0xFFFFFFFA); // MOVE.B	#$01,$FFFA
	rom_471A(); // Detected flow into next function
}*/
/*ROMFUNC(rom_471A) {
	DEF_ROMLOC(471A): move_toreg_16(read_16(0xFFFFF60C), &D0); // MOVE.W	$F60C,D0
	DEF_ROMLOC(471E): or_toreg_8(0x40, &D0); // ORI.B	#$40,D0
	DEF_ROMLOC(4722): move_tomem_16(D0, 0xC00004); // MOVE.W	D0,$00C00004
	DEF_ROMLOC(4728): rom_1EC8(); // BSR.W	$1EC8
	rom_472C(); // Detected flow into next function
}*/
/*ROMFUNC(rom_472C) {
	DEF_ROMLOC(472C): rom_13A0(); // BSR.W	$13A0
	DEF_ROMLOC(4730): move_tomem_8(0xA, 0xFFFFF62A); // MOVE.B	#$0A,$F62A
	DEF_ROMLOC(4736): rom_29A0(); // BSR.W	$29A0
	DEF_ROMLOC(473A): rom_3FD2(); // BSR.W	$3FD2
	DEF_ROMLOC(473E): move_tomem_16(read_16(0xFFFFF604), 0xFFFFF602); // MOVE.W	$F604,$F602
	DEF_ROMLOC(4744): rom_D9C6(); // JSR	$0000D9C6
	DEF_ROMLOC(474A): rom_DCEC(); // JSR	$0000DCEC
	DEF_ROMLOC(4750): rom_1B904(); // JSR	$0001B904
	DEF_ROMLOC(4756): rom_4BF0(); // BSR.W	$4BF0
	DEF_ROMLOC(475A): tst_mem_16(0xFFFFFFF0); // TST.W	$FFF0
	DEF_ROMLOC(475E): if (CCR_EQ) goto rom_4768; // BEQ.B	$4768
	DEF_ROMLOC(4760): tst_mem_16(0xFFFFF614); // TST.W	$F614
	DEF_ROMLOC(4764): if (CCR_EQ) goto rom_4896; // BEQ.W	$4896
	rom_4768(); // Detected flow into next function
}*/
/*ROMFUNC(rom_4768) {
	DEF_ROMLOC(4768): cmp_tomem_8(0x10, 0xFFFFF600); // CMPI.B	#$10,$F600
	DEF_ROMLOC(476E): if (CCR_EQ) goto rom_472C; // BEQ.W	$472C
	DEF_ROMLOC(4772): tst_mem_16(0xFFFFFFF0); // TST.W	$FFF0
	DEF_ROMLOC(4776): if (!CCR_EQ) goto rom_489E; // BNE.W	$489E
	DEF_ROMLOC(477A): move_tomem_8(0xC, 0xFFFFF600); // MOVE.B	#$0C,$F600
	DEF_ROMLOC(4780): cmp_tomem_16(0x503, 0xFFFFFE10); // CMPI.W	#$0503,$FE10
	DEF_ROMLOC(4786): if (CCR_CS) goto rom_478C; // BCS.B	$478C
	DEF_ROMLOC(4788): clr_mem_16(0xFFFFFE10); // CLR.W	$FE10
	rom_478C(); // Detected flow into next function
}*/
/*ROMFUNC(rom_478C) {
	DEF_ROMLOC(478C): move_tomem_16(0x3C, 0xFFFFF614); // MOVE.W	#$003C,$F614
	DEF_ROMLOC(4792): move_tomem_16(0x3F, 0xFFFFF626); // MOVE.W	#$003F,$F626
	DEF_ROMLOC(4798): clr_mem_16(0xFFFFF794); // CLR.W	$F794
	rom_479C(); // Detected flow into next function
}*/
/*ROMFUNC(rom_479C) {
	DEF_ROMLOC(479C): move_tomem_8(0x16, 0xFFFFF62A); // MOVE.B	#$16,$F62A
	DEF_ROMLOC(47A2): rom_29A0(); // BSR.W	$29A0
	DEF_ROMLOC(47A6): rom_3FD2(); // BSR.W	$3FD2
	DEF_ROMLOC(47AA): move_tomem_16(read_16(0xFFFFF604), 0xFFFFF602); // MOVE.W	$F604,$F602
	DEF_ROMLOC(47B0): rom_D9C6(); // JSR	$0000D9C6
	DEF_ROMLOC(47B6): rom_DCEC(); // JSR	$0000DCEC
	DEF_ROMLOC(47BC): rom_1B904(); // JSR	$0001B904
	DEF_ROMLOC(47C2): rom_4BF0(); // BSR.W	$4BF0
	DEF_ROMLOC(47C6): sub_tomem_16(0x1, 0xFFFFF794); // SUBQ.W	#$01,$F794
	DEF_ROMLOC(47CA): if (CCR_PL) goto rom_47D6; // BPL.B	$47D6
	DEF_ROMLOC(47CC): move_tomem_16(0x2, 0xFFFFF794); // MOVE.W	#$0002,$F794
	DEF_ROMLOC(47D2): rom_1F94(); // BSR.W	$1F94
	rom_47D6(); // Detected flow into next function
}*/
/*ROMFUNC(rom_47D6) {
	DEF_ROMLOC(47D6): tst_mem_16(0xFFFFF614); // TST.W	$F614
	DEF_ROMLOC(47DA): if (!CCR_EQ) goto rom_479C; // BNE.B	$479C
	DEF_ROMLOC(47DC): move_tosr_16(0x2700, &SR); // MOVE.W	#$2700,SR
	DEF_ROMLOC(47E0): move_toreg_32(0xC00004, &A6); // LEA.L	$00C00004,A6
	DEF_ROMLOC(47E6): move_tomem_16(0xFFFF8230, A6); // MOVE.W	#$8230,(A6)
	DEF_ROMLOC(47EA): move_tomem_16(0xFFFF8407, A6); // MOVE.W	#$8407,(A6)
	DEF_ROMLOC(47EE): move_tomem_16(0xFFFF9001, A6); // MOVE.W	#$9001,(A6)
	DEF_ROMLOC(47F2): rom_12C4(); // BSR.W	$12C4
	DEF_ROMLOC(47F6): move_tomem_32(0x70000002, 0xC00004); // MOVE.L	#$70000002,$00C00004
	DEF_ROMLOC(4800): move_toreg_32(0x39204, &A0); // LEA.L	$00039204,A0
	DEF_ROMLOC(4806): rom_1438(); // BSR.W	$1438
	DEF_ROMLOC(480A): rom_1CFEE(); // JSR	$0001CFEE
	DEF_ROMLOC(4810): move_tosr_16(0x2300, &SR); // MOVE.W	#$2300,SR
	DEF_ROMLOC(4814): move_toreg_32(0x11, &D0); // MOVEQ.L	$11,D0
	DEF_ROMLOC(4816): rom_2110(); // BSR.W	$2110
	DEF_ROMLOC(481A): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(481C): rom_15AA(); // BSR.W	$15AA
	DEF_ROMLOC(4820): move_toreg_32(0x1B, &D0); // MOVEQ.L	$1B,D0
	DEF_ROMLOC(4822): rom_1578(); // BSR.W	$1578
	DEF_ROMLOC(4826): move_tomem_8(0x1, 0xFFFFFE1F); // MOVE.B	#$01,$FE1F
	DEF_ROMLOC(482C): move_tomem_8(0x1, 0xFFFFF7D6); // MOVE.B	#$01,$F7D6
	DEF_ROMLOC(4832): move_toreg_16(read_16(0xFFFFFE20), &D0); // MOVE.W	$FE20,D0
	DEF_ROMLOC(4836): mulu_toreg_16(0xA, &D0); // MULU.W	#$000A,D0
	DEF_ROMLOC(483A): move_tomem_16(D0, 0xFFFFF7D4); // MOVE.W	D0,$F7D4
	DEF_ROMLOC(483E): move_toreg_16(0x8E, &D0); // MOVE.W	#$008E,D0
	DEF_ROMLOC(4842): rom_1394(); // JSR	$00001394
	DEF_ROMLOC(4848): move_toreg_32(0xFFFFD000, &A1); // LEA.L	$D000,A1
	DEF_ROMLOC(484C): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(484E): move_toreg_16(0x7FF, &D1); // MOVE.W	#$07FF,D1
	DEF_ROMLOC(4852): move_tomem_32(D0, (A1 += 4, A1 - 4)); // MOVE.L	D0,(A1)+
	DEF_ROMLOC(4854): dec_reg_16(&D1); if ((D1 & 0xffff) != 0xffff) goto rom_4852; // DBF.W	D1,$4852
	DEF_ROMLOC(4858): move_tomem_8(0x7E, 0xFFFFD5C0); // MOVE.B	#$7E,$D5C0
	rom_485E(); // Detected flow into next function
}*/
/*ROMFUNC(rom_485E) {
	DEF_ROMLOC(485E): rom_13A0(); // BSR.W	$13A0
	DEF_ROMLOC(4862): move_tomem_8(0xC, 0xFFFFF62A); // MOVE.B	#$0C,$F62A
	DEF_ROMLOC(4868): rom_29A0(); // BSR.W	$29A0
	DEF_ROMLOC(486C): rom_D9C6(); // JSR	$0000D9C6
	DEF_ROMLOC(4872): rom_DCEC(); // JSR	$0000DCEC
	DEF_ROMLOC(4878): rom_15E4(); // BSR.W	$15E4
	DEF_ROMLOC(487C): tst_mem_16(0xFFFFFE02); // TST.W	$FE02
	DEF_ROMLOC(4880): if (CCR_EQ) goto rom_485E; // BEQ.B	$485E
	DEF_ROMLOC(4882): tst_mem_32(0xFFFFF680); // TST.L	$F680
	DEF_ROMLOC(4886): if (!CCR_EQ) goto rom_485E; // BNE.B	$485E
	DEF_ROMLOC(4888): move_toreg_16(0xCA, &D0); // MOVE.W	#$00CA,D0
	DEF_ROMLOC(488C): rom_1394(); // BSR.W	$1394
	DEF_ROMLOC(4890): rom_1F74(); // BSR.W	$1F74
	DEF_ROMLOC(4894): return; // RTS
}*/
ROMFUNC(rom_4896) {
	DEF_ROMLOC(4896): move_tomem_8(0x0, 0xFFFFF600); // MOVE.B	#$00,$F600
	DEF_ROMLOC(489C): return; // RTS
	DEF_ROMLOC(489E): cmp_tomem_8(0xC, 0xFFFFF600); // CMPI.B	#$0C,$F600
	DEF_ROMLOC(48A4): if (CCR_EQ) goto rom_4896; // BEQ.B	$4896
	DEF_ROMLOC(48A6): return; // RTS
}
ROMFUNC(rom_48A8) {
	u32 d0backup = 0;
	u32 d1backup = 0;
	u32 d2backup = 0;
	u32 d3backup = 0;
	u32 d4backup = 0;
	DEF_ROMLOC(48A8): move_toreg_32(0xFF0000, &A1); // LEA.L	$00FF0000,A1
	DEF_ROMLOC(48AE): move_toreg_32(0x2D3C6, &A0); // LEA.L	$0002D3C6,A0
	DEF_ROMLOC(48B4): move_toreg_16(0x4051, &D0); // MOVE.W	#$4051,D0
	DEF_ROMLOC(48B8): rom_1716(); // BSR.W	$1716
	DEF_ROMLOC(48BC): move_toreg_32(0x50000001, &D3); // MOVE.L	#$50000001,D3
	DEF_ROMLOC(48C2): move_toreg_32(0xFF0080, &A2); // LEA.L	$00FF0080,A2
	DEF_ROMLOC(48C8): move_toreg_32(0x6, &D7); // MOVEQ.L	$06,D7
	DEF_ROMLOC(48CA): move_toreg_32(D3, &D0); // MOVE.L	D3,D0
	DEF_ROMLOC(48CC): move_toreg_32(0x3, &D6); // MOVEQ.L	$03,D6
	DEF_ROMLOC(48CE): move_toreg_32(0x0, &D4); // MOVEQ.L	$00,D4
	DEF_ROMLOC(48D0): cmp_toreg_16(0x3, &D7); // CMPI.W	#$0003,D7
	DEF_ROMLOC(48D4): if (CCR_CC) goto rom_48D8; // BCC.B	$48D8
	DEF_ROMLOC(48D6): move_toreg_32(0x1, &D4); // MOVEQ.L	$01,D4
	DEF_ROMLOC(48D8): move_toreg_32(0x7, &D5); // MOVEQ.L	$07,D5
	DEF_ROMLOC(48DA): move_toreg_32(A2, &A1); // MOVEA.L	A2,A1
	DEF_ROMLOC(48DC): eor_toreg_8(0x1, &D4); // EORI.B	#$01,D4
	DEF_ROMLOC(48E0): if (!CCR_EQ) goto rom_48EE; // BNE.B	$48EE
	DEF_ROMLOC(48E2): cmp_toreg_16(0x6, &D7); // CMPI.W	#$0006,D7
	DEF_ROMLOC(48E6): if (!CCR_EQ) goto rom_48FE; // BNE.B	$48FE
	DEF_ROMLOC(48E8): move_toreg_32(0xFF0000, &A1); // LEA.L	$00FF0000,A1
	DEF_ROMLOC(48EE):
		d0backup = D0;
		d1backup = D1;
		d2backup = D2;
		d3backup = D3;
		d4backup = D4;
		// TODO; // MOVEM.L	D0-D4,-(A7)
	DEF_ROMLOC(48F2): move_toreg_32(0x7, &D1); // MOVEQ.L	$07,D1
	DEF_ROMLOC(48F4): move_toreg_32(0x7, &D2); // MOVEQ.L	$07,D2
	DEF_ROMLOC(48F6): rom_1418(); // BSR.W	$1418
	DEF_ROMLOC(48FA):
		D0 = d0backup;
		D1 = d1backup;
		D2 = d2backup;
		D3 = d3backup;
		D4 = d4backup;
		// TODO; // MOVEM.L	(A7)+,D0-D4
	DEF_ROMLOC(48FE): add_toreg_32(0x100000, &D0); // ADDI.L	#$00100000,D0
	DEF_ROMLOC(4904): dec_reg_16(&D5); if ((D5 & 0xffff) != 0xffff) goto rom_48DA; // DBF.W	D5,$48DA
	DEF_ROMLOC(4908): add_toreg_32(0x3800000, &D0); // ADDI.L	#$03800000,D0
	DEF_ROMLOC(490E): eor_toreg_8(0x1, &D4); // EORI.B	#$01,D4
	DEF_ROMLOC(4912): dec_reg_16(&D6); if ((D6 & 0xffff) != 0xffff) goto rom_48D8; // DBF.W	D6,$48D8
	DEF_ROMLOC(4916): add_toreg_32(0x10000000, &D3); // ADDI.L	#$10000000,D3
	DEF_ROMLOC(491C): if (CCR_PL) goto rom_4928; // BPL.B	$4928
	DEF_ROMLOC(491E): swap_reg_16(&D3); // SWAP.W	D3
	DEF_ROMLOC(4920): add_toreg_32(0xC000, &D3); // ADDI.L	#$0000C000,D3
	DEF_ROMLOC(4926): swap_reg_16(&D3); // SWAP.W	D3
	DEF_ROMLOC(4928): add_toreg_16(0x80, &A2); // ADDA.W	#$0080,A2
	DEF_ROMLOC(492C): dec_reg_16(&D7); if ((D7 & 0xffff) != 0xffff) goto rom_48CA; // DBF.W	D7,$48CA
	DEF_ROMLOC(4930): move_toreg_32(0xFF0000, &A1); // LEA.L	$00FF0000,A1
	DEF_ROMLOC(4936): move_toreg_32(0x2E18A, &A0); // LEA.L	$0002E18A,A0
	DEF_ROMLOC(493C): move_toreg_16(0x4000, &D0); // MOVE.W	#$4000,D0
	DEF_ROMLOC(4940): rom_1716(); // BSR.W	$1716
	DEF_ROMLOC(4944): move_toreg_32(0xFF0000, &A1); // LEA.L	$00FF0000,A1
	DEF_ROMLOC(494A): move_toreg_32(0x40000003, &D0); // MOVE.L	#$40000003,D0
	DEF_ROMLOC(4950): move_toreg_32(0x3F, &D1); // MOVEQ.L	$3F,D1
	DEF_ROMLOC(4952): move_toreg_32(0x1F, &D2); // MOVEQ.L	$1F,D2
	DEF_ROMLOC(4954): rom_1418(); // BSR.W	$1418
	DEF_ROMLOC(4958): move_toreg_32(0xFF0000, &A1); // LEA.L	$00FF0000,A1
	DEF_ROMLOC(495E): move_toreg_32(0x50000003, &D0); // MOVE.L	#$50000003,D0
	DEF_ROMLOC(4964): move_toreg_32(0x3F, &D1); // MOVEQ.L	$3F,D1
	DEF_ROMLOC(4966): move_toreg_32(0x3F, &D2); // MOVEQ.L	$3F,D2
	DEF_ROMLOC(4968): rom_1418(); // BSR.W	$1418
	DEF_ROMLOC(496C): return; // RTS
}
ROMFUNC(rom_496E) {
	DEF_ROMLOC(496E): tst_mem_16(0xFFFFF63A); // TST.W	$F63A
	DEF_ROMLOC(4972): if (!CCR_EQ) goto rom_49F2; // BNE.B	$49F2
	DEF_ROMLOC(4974): sub_tomem_16(0x1, 0xFFFFF79C); // SUBQ.W	#$01,$F79C
	DEF_ROMLOC(4978): if (CCR_PL) goto rom_49F2; // BPL.B	$49F2
	DEF_ROMLOC(497A): move_toreg_32(0xC00004, &A6); // LEA.L	$00C00004,A6
	DEF_ROMLOC(4980): move_toreg_16(read_16(0xFFFFF79A), &D0); // MOVE.W	$F79A,D0
	DEF_ROMLOC(4984): add_tomem_16(0x1, 0xFFFFF79A); // ADDQ.W	#$01,$F79A
	DEF_ROMLOC(4988): and_toreg_16(0x1F, &D0); // ANDI.W	#$001F,D0
	DEF_ROMLOC(498C): lsl_toreg_16(0x2, &D0); // LSL.W	#$02,D0
	DEF_ROMLOC(498E): move_toreg_32(0x4A48, &A0); // LEA.L	$00004A48,A0
	DEF_ROMLOC(4994): add_toreg_16(D0, &A0); // ADDA.W	D0,A0
	DEF_ROMLOC(4996): move_toreg_8(read_8(A0++), &D0); // MOVE.B	(A0)+,D0
	DEF_ROMLOC(4998): if (CCR_PL) goto rom_499E; // BPL.B	$499E
	DEF_ROMLOC(499A): move_toreg_16(0x1FF, &D0); // MOVE.W	#$01FF,D0
	DEF_ROMLOC(499E): move_tomem_16(D0, 0xFFFFF79C); // MOVE.W	D0,$F79C
	DEF_ROMLOC(49A2): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(49A4): move_toreg_8(read_8(A0++), &D0); // MOVE.B	(A0)+,D0
	DEF_ROMLOC(49A6): move_tomem_16(D0, 0xFFFFF7A0); // MOVE.W	D0,$F7A0
	DEF_ROMLOC(49AA): move_toreg_32(0x4AC8, &A1); // LEA.L	$00004AC8,A1
	DEF_ROMLOC(49B0): move_toreg_32((s32)A1 + (s8)0x0 + (s16)D0, &A1); // LEA.L	0(A1,D0),A1
	DEF_ROMLOC(49B4): move_toreg_16(0xFFFF8200, &D0); // MOVE.W	#$8200,D0
	DEF_ROMLOC(49B8): move_toreg_8(read_8(A1++), &D0); // MOVE.B	(A1)+,D0
	DEF_ROMLOC(49BA): move_tomem_16(D0, A6); // MOVE.W	D0,(A6)
	DEF_ROMLOC(49BC): move_tomem_8(read_8(A1), 0xFFFFF616); // MOVE.B	(A1),$F616
	DEF_ROMLOC(49C0): move_toreg_16(0xFFFF8400, &D0); // MOVE.W	#$8400,D0
	DEF_ROMLOC(49C4): move_toreg_8(read_8(A0++), &D0); // MOVE.B	(A0)+,D0
	DEF_ROMLOC(49C6): move_tomem_16(D0, A6); // MOVE.W	D0,(A6)
	DEF_ROMLOC(49C8): move_tomem_32(0x40000010, 0xC00004); // MOVE.L	#$40000010,$00C00004
	DEF_ROMLOC(49D2): move_tomem_32(read_32(0xFFFFF616), 0xC00000); // MOVE.L	$F616,$00C00000
	DEF_ROMLOC(49DA): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(49DC): move_toreg_8(read_8(A0++), &D0); // MOVE.B	(A0)+,D0
	DEF_ROMLOC(49DE): if (CCR_MI) goto rom_49F4; // BMI.B	$49F4
	DEF_ROMLOC(49E0): move_toreg_32(0x4AD6, &A1); // LEA.L	$00004AD6,A1
	DEF_ROMLOC(49E6): add_toreg_16(D0, &A1); // ADDA.W	D0,A1
	DEF_ROMLOC(49E8): move_toreg_32(0xFFFFFB4E, &A2); // LEA.L	$FB4E,A2
	DEF_ROMLOC(49EC): move_tomem_32(read_32((A1 += 4, A1 - 4)), (A2 += 4, A2 - 4)); // MOVE.L	(A1)+,(A2)+
	DEF_ROMLOC(49EE): move_tomem_32(read_32((A1 += 4, A1 - 4)), (A2 += 4, A2 - 4)); // MOVE.L	(A1)+,(A2)+
	DEF_ROMLOC(49F0): move_tomem_32(read_32((A1 += 4, A1 - 4)), (A2 += 4, A2 - 4)); // MOVE.L	(A1)+,(A2)+
	DEF_ROMLOC(49F2): return; // RTS
	DEF_ROMLOC(49F4): move_toreg_16(read_16(0xFFFFF79E), &D1); // MOVE.W	$F79E,D1
	DEF_ROMLOC(49F8): cmp_toreg_16(0x8A, &D0); // CMPI.W	#$008A,D0
	DEF_ROMLOC(49FC): if (CCR_CS) goto rom_4A00; // BCS.B	$4A00
	DEF_ROMLOC(49FE): add_toreg_16(0x1, &D1); // ADDQ.W	#$01,D1
	DEF_ROMLOC(4A00): mulu_toreg_16(0x2A, &D1); // MULU.W	#$002A,D1
	DEF_ROMLOC(4A04): move_toreg_32(0x4B1E, &A1); // LEA.L	$00004B1E,A1
	DEF_ROMLOC(4A0A): add_toreg_16(D1, &A1); // ADDA.W	D1,A1
	DEF_ROMLOC(4A0C): and_toreg_16(0x7F, &D0); // ANDI.W	#$007F,D0
	DEF_ROMLOC(4A10): bclr_toreg_32(0x0, &D0); // BCLR.L	#$00,D0
	DEF_ROMLOC(4A14): if (CCR_EQ) goto rom_4A24; // BEQ.B	$4A24
	DEF_ROMLOC(4A16): move_toreg_32(0xFFFFFB6E, &A2); // LEA.L	$FB6E,A2
	DEF_ROMLOC(4A1A): move_tomem_32(read_32(A1), (A2 += 4, A2 - 4)); // MOVE.L	(A1),(A2)+
	DEF_ROMLOC(4A1C): move_tomem_32(read_32(A1 + 0x4), (A2 += 4, A2 - 4)); // MOVE.L	4(A1),(A2)+
	DEF_ROMLOC(4A20): move_tomem_32(read_32(A1 + 0x8), (A2 += 4, A2 - 4)); // MOVE.L	8(A1),(A2)+
	DEF_ROMLOC(4A24): add_toreg_16(0xC, &A1); // ADDA.W	#$000C,A1
	DEF_ROMLOC(4A28): move_toreg_32(0xFFFFFB5A, &A2); // LEA.L	$FB5A,A2
	DEF_ROMLOC(4A2C): cmp_toreg_16(0xA, &D0); // CMPI.W	#$000A,D0
	DEF_ROMLOC(4A30): if (CCR_CS) goto rom_4A3A; // BCS.B	$4A3A
	DEF_ROMLOC(4A32): sub_toreg_16(0xA, &D0); // SUBI.W	#$000A,D0
	DEF_ROMLOC(4A36): move_toreg_32(0xFFFFFB7A, &A2); // LEA.L	$FB7A,A2
	DEF_ROMLOC(4A3A): move_toreg_16(D0, &D1); // MOVE.W	D0,D1
	DEF_ROMLOC(4A3C): add_toreg_16(D0, &D0); // ADD.W	D0,D0
	DEF_ROMLOC(4A3E): add_toreg_16(D1, &D0); // ADD.W	D1,D0
	DEF_ROMLOC(4A40): add_toreg_16(D0, &A1); // ADDA.W	D0,A1
	DEF_ROMLOC(4A42): move_tomem_32(read_32((A1 += 4, A1 - 4)), (A2 += 4, A2 - 4)); // MOVE.L	(A1)+,(A2)+
	DEF_ROMLOC(4A44): move_tomem_16(read_16((A1 += 2, A1 - 2)), (A2 += 2, A2 - 2)); // MOVE.W	(A1)+,(A2)+
	DEF_ROMLOC(4A46): return; // RTS
}
ROMFUNC(rom_4BF0) {
	DEF_ROMLOC(4BF0): move_toreg_16(read_16(0xFFFFF7A0), &D0); // MOVE.W	$F7A0,D0
	DEF_ROMLOC(4BF4): if (!CCR_EQ) goto rom_4C02; // BNE.B	$4C02
	DEF_ROMLOC(4BF6): move_tomem_16(0x0, 0xFFFFF70C); // MOVE.W	#$0000,$F70C
	DEF_ROMLOC(4BFC): move_tomem_16(read_16(0xFFFFF70C), 0xFFFFF618); // MOVE.W	$F70C,$F618
	DEF_ROMLOC(4C02): cmp_toreg_16(0x8, &D0); // CMPI.W	#$0008,D0
	DEF_ROMLOC(4C06): if (CCR_CC) goto rom_4C5A; // BCC.B	$4C5A
	DEF_ROMLOC(4C08): cmp_toreg_16(0x6, &D0); // CMPI.W	#$0006,D0
	DEF_ROMLOC(4C0C): if (!CCR_EQ) goto rom_4C1C; // BNE.B	$4C1C
	DEF_ROMLOC(4C0E): add_tomem_16(0x1, 0xFFFFF718); // ADDQ.W	#$01,$F718
	DEF_ROMLOC(4C12): add_tomem_16(0x1, 0xFFFFF70C); // ADDQ.W	#$01,$F70C
	DEF_ROMLOC(4C16): move_tomem_16(read_16(0xFFFFF70C), 0xFFFFF618); // MOVE.W	$F70C,$F618
	DEF_ROMLOC(4C1C): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(4C1E): move_toreg_16(read_16(0xFFFFF708), &D0); // MOVE.W	$F708,D0
	DEF_ROMLOC(4C22): neg_reg_16(&D0); // NEG.W	D0
	DEF_ROMLOC(4C24): swap_reg_16(&D0); // SWAP.W	D0
	DEF_ROMLOC(4C26): move_toreg_32(0x4CD8, &A1); // LEA.L	$00004CD8,A1
	DEF_ROMLOC(4C2C): move_toreg_32(0xFFFFAA00, &A3); // LEA.L	$AA00,A3
	DEF_ROMLOC(4C30): move_toreg_32(0x9, &D3); // MOVEQ.L	$09,D3
	DEF_ROMLOC(4C32): move_toreg_16(read_16(A3 + 0x2), &D0); // MOVE.W	2(A3),D0
	DEF_ROMLOC(4C36): rom_29D2(); // BSR.W	$29D2
	DEF_ROMLOC(4C3A): move_toreg_32(0x0, &D2); // MOVEQ.L	$00,D2
	DEF_ROMLOC(4C3C): move_toreg_8(read_8(A1++), &D2); // MOVE.B	(A1)+,D2
	DEF_ROMLOC(4C3E): muls_toreg_16(D2, &D0); // MULS.W	D2,D0
	DEF_ROMLOC(4C40): asr_toreg_32(0x8, &D0); // ASR.L	#$08,D0
	DEF_ROMLOC(4C42): move_tomem_16(D0, (A3 += 2, A3 - 2)); // MOVE.W	D0,(A3)+
	DEF_ROMLOC(4C44): move_toreg_8(read_8(A1++), &D2); // MOVE.B	(A1)+,D2
	DEF_ROMLOC(4C46): ext_reg_16(&D2); // EXT.W	D2
	DEF_ROMLOC(4C48): add_tomem_16(D2, (A3 += 2, A3 - 2)); // ADD.W	D2,(A3)+
	DEF_ROMLOC(4C4A): dec_reg_16(&D3); if ((D3 & 0xffff) != 0xffff) goto rom_4C32; // DBF.W	D3,$4C32
	DEF_ROMLOC(4C4E): move_toreg_32(0xFFFFAA00, &A3); // LEA.L	$AA00,A3
	DEF_ROMLOC(4C52): move_toreg_32(0x4CC4, &A2); // LEA.L	$00004CC4,A2
	goto rom_4C8A; // BRA.B	$4C8A
	DEF_ROMLOC(4C5A): cmp_toreg_16(0xC, &D0); // CMPI.W	#$000C,D0
	DEF_ROMLOC(4C5E): if (!CCR_EQ) goto rom_4C80; // BNE.B	$4C80
	DEF_ROMLOC(4C60): sub_tomem_16(0x1, 0xFFFFF718); // SUBQ.W	#$01,$F718
	DEF_ROMLOC(4C64): move_toreg_32(0xFFFFAB00, &A3); // LEA.L	$AB00,A3
	DEF_ROMLOC(4C68): move_toreg_32(0x18000, &D2); // MOVE.L	#$00018000,D2
	DEF_ROMLOC(4C6E): move_toreg_32(0x6, &D1); // MOVEQ.L	$06,D1
	DEF_ROMLOC(4C70): move_toreg_32(read_32(A3), &D0); // MOVE.L	(A3),D0
	DEF_ROMLOC(4C72): sub_toreg_32(D2, &D0); // SUB.L	D2,D0
	DEF_ROMLOC(4C74): move_tomem_32(D0, (A3 += 4, A3 - 4)); // MOVE.L	D0,(A3)+
	DEF_ROMLOC(4C76): sub_toreg_32(0x2000, &D2); // SUBI.L	#$00002000,D2
	DEF_ROMLOC(4C7C): dec_reg_16(&D1); if ((D1 & 0xffff) != 0xffff) goto rom_4C70; // DBF.W	D1,$4C70
	DEF_ROMLOC(4C80): move_toreg_32(0xFFFFAB00, &A3); // LEA.L	$AB00,A3
	DEF_ROMLOC(4C84): move_toreg_32(0x4CD0, &A2); // LEA.L	$00004CD0,A2
	DEF_ROMLOC(4C8A): move_toreg_32(0xFFFFCC00, &A1); // LEA.L	$CC00,A1
	DEF_ROMLOC(4C8E): move_toreg_16(read_16(0xFFFFF718), &D0); // MOVE.W	$F718,D0
	DEF_ROMLOC(4C92): neg_reg_16(&D0); // NEG.W	D0
	DEF_ROMLOC(4C94): swap_reg_16(&D0); // SWAP.W	D0
	DEF_ROMLOC(4C96): move_toreg_32(0x0, &D3); // MOVEQ.L	$00,D3
	DEF_ROMLOC(4C98): move_toreg_8(read_8(A2++), &D3); // MOVE.B	(A2)+,D3
	DEF_ROMLOC(4C9A): move_toreg_16(read_16(0xFFFFF70C), &D2); // MOVE.W	$F70C,D2
	DEF_ROMLOC(4C9E): neg_reg_16(&D2); // NEG.W	D2
	DEF_ROMLOC(4CA0): and_toreg_16(0xFF, &D2); // ANDI.W	#$00FF,D2
	DEF_ROMLOC(4CA4): lsl_toreg_16(0x2, &D2); // LSL.W	#$02,D2
	DEF_ROMLOC(4CA6): move_toreg_16(read_16((A3 += 2, A3 - 2)), &D0); // MOVE.W	(A3)+,D0
	DEF_ROMLOC(4CA8): add_toreg_16(0x2, &A3); // ADDQ.W	#$02,A3
	DEF_ROMLOC(4CAA): move_toreg_32(0x0, &D1); // MOVEQ.L	$00,D1
	DEF_ROMLOC(4CAC): move_toreg_8(read_8(A2++), &D1); // MOVE.B	(A2)+,D1
	DEF_ROMLOC(4CAE): sub_toreg_16(0x1, &D1); // SUBQ.W	#$01,D1
	DEF_ROMLOC(4CB0): move_tomem_32(D0, (s32)A1 + (s8)0x0 + (s16)D2); // MOVE.L	D0,0(A1,D2)
	DEF_ROMLOC(4CB4): add_toreg_16(0x4, &D2); // ADDQ.W	#$04,D2
	DEF_ROMLOC(4CB6): and_toreg_16(0x3FC, &D2); // ANDI.W	#$03FC,D2
	DEF_ROMLOC(4CBA): dec_reg_16(&D1); if ((D1 & 0xffff) != 0xffff) goto rom_4CB0; // DBF.W	D1,$4CB0
	DEF_ROMLOC(4CBE): dec_reg_16(&D3); if ((D3 & 0xffff) != 0xffff) goto rom_4CA6; // DBF.W	D3,$4CA6
	DEF_ROMLOC(4CC2): return; // RTS
}
ROMFUNC(rom_1BA46) {
	DEF_ROMLOC(1BA46): move_toreg_32(0xFF400C, &A1); // LEA.L	$00FF400C,A1
	DEF_ROMLOC(1BA4C): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(1BA4E): move_toreg_8(read_8(0xFFFFF780), &D0); // MOVE.B	$F780,D0
	DEF_ROMLOC(1BA52): lsr_toreg_8(0x2, &D0); // LSR.B	#$02,D0
	DEF_ROMLOC(1BA54): and_toreg_16(0xF, &D0); // ANDI.W	#$000F,D0
	DEF_ROMLOC(1BA58): move_toreg_32(0x23, &D1); // MOVEQ.L	$23,D1
	DEF_ROMLOC(1BA5A): move_tomem_16(D0, A1); // MOVE.W	D0,(A1)
	DEF_ROMLOC(1BA5C): add_toreg_16(0x8, &A1); // ADDQ.W	#$08,A1
	DEF_ROMLOC(1BA5E): dec_reg_16(&D1); if ((D1 & 0xffff) != 0xffff) goto rom_1BA5A; // DBF.W	D1,$1BA5A
	DEF_ROMLOC(1BA62): move_toreg_32(0xFF4005, &A1); // LEA.L	$00FF4005,A1
	DEF_ROMLOC(1BA68): sub_tomem_8(0x1, 0xFFFFFEC2); // SUBQ.B	#$01,$FEC2
	DEF_ROMLOC(1BA6C): if (CCR_PL) goto rom_1BA7E; // BPL.B	$1BA7E
	DEF_ROMLOC(1BA6E): move_tomem_8(0x7, 0xFFFFFEC2); // MOVE.B	#$07,$FEC2
	DEF_ROMLOC(1BA74): add_tomem_8(0x1, 0xFFFFFEC3); // ADDQ.B	#$01,$FEC3
	DEF_ROMLOC(1BA78): and_tomem_8(0x3, 0xFFFFFEC3); // ANDI.B	#$03,$FEC3
	DEF_ROMLOC(1BA7E): move_tomem_8(read_8(0xFFFFFEC3), A1 + 0x1D0); // MOVE.B	$FEC3,464(A1)
	DEF_ROMLOC(1BA84): sub_tomem_8(0x1, 0xFFFFFEC4); // SUBQ.B	#$01,$FEC4
	DEF_ROMLOC(1BA88): if (CCR_PL) goto rom_1BA9A; // BPL.B	$1BA9A
	DEF_ROMLOC(1BA8A): move_tomem_8(0x7, 0xFFFFFEC4); // MOVE.B	#$07,$FEC4
	DEF_ROMLOC(1BA90): add_tomem_8(0x1, 0xFFFFFEC5); // ADDQ.B	#$01,$FEC5
	DEF_ROMLOC(1BA94): and_tomem_8(0x1, 0xFFFFFEC5); // ANDI.B	#$01,$FEC5
	DEF_ROMLOC(1BA9A): move_toreg_8(read_8(0xFFFFFEC5), &D0); // MOVE.B	$FEC5,D0
	DEF_ROMLOC(1BA9E): move_tomem_8(D0, A1 + 0x138); // MOVE.B	D0,312(A1)
	DEF_ROMLOC(1BAA2): move_tomem_8(D0, A1 + 0x160); // MOVE.B	D0,352(A1)
	DEF_ROMLOC(1BAA6): move_tomem_8(D0, A1 + 0x148); // MOVE.B	D0,328(A1)
	DEF_ROMLOC(1BAAA): move_tomem_8(D0, A1 + 0x150); // MOVE.B	D0,336(A1)
	DEF_ROMLOC(1BAAE): move_tomem_8(D0, A1 + 0x1D8); // MOVE.B	D0,472(A1)
	DEF_ROMLOC(1BAB2): move_tomem_8(D0, A1 + 0x1E0); // MOVE.B	D0,480(A1)
	DEF_ROMLOC(1BAB6): move_tomem_8(D0, A1 + 0x1E8); // MOVE.B	D0,488(A1)
	DEF_ROMLOC(1BABA): move_tomem_8(D0, A1 + 0x1F0); // MOVE.B	D0,496(A1)
	DEF_ROMLOC(1BABE): move_tomem_8(D0, A1 + 0x1F8); // MOVE.B	D0,504(A1)
	DEF_ROMLOC(1BAC2): move_tomem_8(D0, A1 + 0x200); // MOVE.B	D0,512(A1)
	DEF_ROMLOC(1BAC6): sub_tomem_8(0x1, 0xFFFFFEC6); // SUBQ.B	#$01,$FEC6
	DEF_ROMLOC(1BACA): if (CCR_PL) goto rom_1BADC; // BPL.B	$1BADC
	DEF_ROMLOC(1BACC): move_tomem_8(0x4, 0xFFFFFEC6); // MOVE.B	#$04,$FEC6
	DEF_ROMLOC(1BAD2): add_tomem_8(0x1, 0xFFFFFEC7); // ADDQ.B	#$01,$FEC7
	DEF_ROMLOC(1BAD6): and_tomem_8(0x3, 0xFFFFFEC7); // ANDI.B	#$03,$FEC7
	DEF_ROMLOC(1BADC): move_toreg_8(read_8(0xFFFFFEC7), &D0); // MOVE.B	$FEC7,D0
	DEF_ROMLOC(1BAE0): move_tomem_8(D0, A1 + 0x168); // MOVE.B	D0,360(A1)
	DEF_ROMLOC(1BAE4): move_tomem_8(D0, A1 + 0x170); // MOVE.B	D0,368(A1)
	DEF_ROMLOC(1BAE8): move_tomem_8(D0, A1 + 0x178); // MOVE.B	D0,376(A1)
	DEF_ROMLOC(1BAEC): move_tomem_8(D0, A1 + 0x180); // MOVE.B	D0,384(A1)
	DEF_ROMLOC(1BAF0): sub_tomem_8(0x1, 0xFFFFFEC0); // SUBQ.B	#$01,$FEC0
	DEF_ROMLOC(1BAF4): if (CCR_PL) goto rom_1BB06; // BPL.B	$1BB06
	DEF_ROMLOC(1BAF6): move_tomem_8(0x7, 0xFFFFFEC0); // MOVE.B	#$07,$FEC0
	DEF_ROMLOC(1BAFC): sub_tomem_8(0x1, 0xFFFFFEC1); // SUBQ.B	#$01,$FEC1
	DEF_ROMLOC(1BB00): and_tomem_8(0x7, 0xFFFFFEC1); // ANDI.B	#$07,$FEC1
	DEF_ROMLOC(1BB06): move_toreg_32(0xFF4016, &A1); // LEA.L	$00FF4016,A1
	DEF_ROMLOC(1BB0C): move_toreg_32(0x1BBF0, &A0); // LEA.L	$0001BBF0,A0
	DEF_ROMLOC(1BB12): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(1BB14): move_toreg_8(read_8(0xFFFFFEC1), &D0); // MOVE.B	$FEC1,D0
	DEF_ROMLOC(1BB18): add_toreg_16(D0, &D0); // ADD.W	D0,D0
	DEF_ROMLOC(1BB1A): move_toreg_32((s32)A0 + (s8)0x0 + (s16)D0, &A0); // LEA.L	0(A0,D0),A0
	DEF_ROMLOC(1BB1E): move_tomem_16(read_16(A0), A1); // MOVE.W	(A0),(A1)
	DEF_ROMLOC(1BB20): move_tomem_16(read_16(A0 + 0x2), A1 + 0x8); // MOVE.W	2(A0),8(A1)
	DEF_ROMLOC(1BB26): move_tomem_16(read_16(A0 + 0x4), A1 + 0x10); // MOVE.W	4(A0),16(A1)
	DEF_ROMLOC(1BB2C): move_tomem_16(read_16(A0 + 0x6), A1 + 0x18); // MOVE.W	6(A0),24(A1)
	DEF_ROMLOC(1BB32): move_tomem_16(read_16(A0 + 0x8), A1 + 0x20); // MOVE.W	8(A0),32(A1)
	DEF_ROMLOC(1BB38): move_tomem_16(read_16(A0 + 0xA), A1 + 0x28); // MOVE.W	10(A0),40(A1)
	DEF_ROMLOC(1BB3E): move_tomem_16(read_16(A0 + 0xC), A1 + 0x30); // MOVE.W	12(A0),48(A1)
	DEF_ROMLOC(1BB44): move_tomem_16(read_16(A0 + 0xE), A1 + 0x38); // MOVE.W	14(A0),56(A1)
	DEF_ROMLOC(1BB4A): add_toreg_16(0x20, &A0); // ADDA.W	#$0020,A0
	DEF_ROMLOC(1BB4E): add_toreg_16(0x48, &A1); // ADDA.W	#$0048,A1
	DEF_ROMLOC(1BB52): move_tomem_16(read_16(A0), A1); // MOVE.W	(A0),(A1)
	DEF_ROMLOC(1BB54): move_tomem_16(read_16(A0 + 0x2), A1 + 0x8); // MOVE.W	2(A0),8(A1)
	DEF_ROMLOC(1BB5A): move_tomem_16(read_16(A0 + 0x4), A1 + 0x10); // MOVE.W	4(A0),16(A1)
	DEF_ROMLOC(1BB60): move_tomem_16(read_16(A0 + 0x6), A1 + 0x18); // MOVE.W	6(A0),24(A1)
	DEF_ROMLOC(1BB66): move_tomem_16(read_16(A0 + 0x8), A1 + 0x20); // MOVE.W	8(A0),32(A1)
	DEF_ROMLOC(1BB6C): move_tomem_16(read_16(A0 + 0xA), A1 + 0x28); // MOVE.W	10(A0),40(A1)
	DEF_ROMLOC(1BB72): move_tomem_16(read_16(A0 + 0xC), A1 + 0x30); // MOVE.W	12(A0),48(A1)
	DEF_ROMLOC(1BB78): move_tomem_16(read_16(A0 + 0xE), A1 + 0x38); // MOVE.W	14(A0),56(A1)
	DEF_ROMLOC(1BB7E): add_toreg_16(0x20, &A0); // ADDA.W	#$0020,A0
	DEF_ROMLOC(1BB82): add_toreg_16(0x48, &A1); // ADDA.W	#$0048,A1
	DEF_ROMLOC(1BB86): move_tomem_16(read_16(A0), A1); // MOVE.W	(A0),(A1)
	DEF_ROMLOC(1BB88): move_tomem_16(read_16(A0 + 0x2), A1 + 0x8); // MOVE.W	2(A0),8(A1)
	DEF_ROMLOC(1BB8E): move_tomem_16(read_16(A0 + 0x4), A1 + 0x10); // MOVE.W	4(A0),16(A1)
	DEF_ROMLOC(1BB94): move_tomem_16(read_16(A0 + 0x6), A1 + 0x18); // MOVE.W	6(A0),24(A1)
	DEF_ROMLOC(1BB9A): move_tomem_16(read_16(A0 + 0x8), A1 + 0x20); // MOVE.W	8(A0),32(A1)
	DEF_ROMLOC(1BBA0): move_tomem_16(read_16(A0 + 0xA), A1 + 0x28); // MOVE.W	10(A0),40(A1)
	DEF_ROMLOC(1BBA6): move_tomem_16(read_16(A0 + 0xC), A1 + 0x30); // MOVE.W	12(A0),48(A1)
	DEF_ROMLOC(1BBAC): move_tomem_16(read_16(A0 + 0xE), A1 + 0x38); // MOVE.W	14(A0),56(A1)
	DEF_ROMLOC(1BBB2): add_toreg_16(0x20, &A0); // ADDA.W	#$0020,A0
	DEF_ROMLOC(1BBB6): add_toreg_16(0x48, &A1); // ADDA.W	#$0048,A1
	DEF_ROMLOC(1BBBA): move_tomem_16(read_16(A0), A1); // MOVE.W	(A0),(A1)
	DEF_ROMLOC(1BBBC): move_tomem_16(read_16(A0 + 0x2), A1 + 0x8); // MOVE.W	2(A0),8(A1)
	DEF_ROMLOC(1BBC2): move_tomem_16(read_16(A0 + 0x4), A1 + 0x10); // MOVE.W	4(A0),16(A1)
	DEF_ROMLOC(1BBC8): move_tomem_16(read_16(A0 + 0x6), A1 + 0x18); // MOVE.W	6(A0),24(A1)
	DEF_ROMLOC(1BBCE): move_tomem_16(read_16(A0 + 0x8), A1 + 0x20); // MOVE.W	8(A0),32(A1)
	DEF_ROMLOC(1BBD4): move_tomem_16(read_16(A0 + 0xA), A1 + 0x28); // MOVE.W	10(A0),40(A1)
	DEF_ROMLOC(1BBDA): move_tomem_16(read_16(A0 + 0xC), A1 + 0x30); // MOVE.W	12(A0),48(A1)
	DEF_ROMLOC(1BBE0): move_tomem_16(read_16(A0 + 0xE), A1 + 0x38); // MOVE.W	14(A0),56(A1)
	DEF_ROMLOC(1BBE6): add_toreg_16(0x20, &A0); // ADDA.W	#$0020,A0
	DEF_ROMLOC(1BBEA): add_toreg_16(0x48, &A1); // ADDA.W	#$0048,A1
	DEF_ROMLOC(1BBEE): return; // RTS
}
ROMFUNC(rom_1BC70) {
	DEF_ROMLOC(1BC70): move_toreg_32(0xFF4400, &A2); // LEA.L	$00FF4400,A2
	DEF_ROMLOC(1BC76): move_toreg_16(0x1F, &D0); // MOVE.W	#$001F,D0
	DEF_ROMLOC(1BC7A): tst_mem_8(A2); // TST.B	(A2)
	DEF_ROMLOC(1BC7C): if (CCR_EQ) goto rom_1BC84; // BEQ.B	$1BC84
	DEF_ROMLOC(1BC7E): add_toreg_16(0x8, &A2); // ADDQ.W	#$08,A2
	DEF_ROMLOC(1BC80): dec_reg_16(&D0); if ((D0 & 0xffff) != 0xffff) goto rom_1BC7A; // DBF.W	D0,$1BC7A
	DEF_ROMLOC(1BC84): return; // RTS
}
ROMFUNC(rom_1B904) {
	DEF_ROMLOC(1B904): rom_1BA46(); // BSR.W	$1BA46
	DEF_ROMLOC(1B908): rom_1BC86(); // BSR.W	$1BC86
	DEF_ROMLOC(1B90C): move_tomem_16(D5, A7 -= 2); // MOVE.W	D5,-(A7)
	DEF_ROMLOC(1B90E): move_toreg_32(0xFFFF8000, &A1); // LEA.L	$8000,A1
	DEF_ROMLOC(1B912): move_toreg_8(read_8(0xFFFFF780), &D0); // MOVE.B	$F780,D0
	DEF_ROMLOC(1B916): and_toreg_8(0xFFFFFFFC, &D0); // ANDI.B	#$FC,D0
	DEF_ROMLOC(1B91A): rom_29D2(); // JSR	$000029D2
	DEF_ROMLOC(1B920): move_toreg_16(D0, &D4); // MOVE.W	D0,D4
	DEF_ROMLOC(1B922): move_toreg_16(D1, &D5); // MOVE.W	D1,D5
	DEF_ROMLOC(1B924): muls_toreg_16(0x18, &D4); // MULS.W	#$0018,D4
	DEF_ROMLOC(1B928): muls_toreg_16(0x18, &D5); // MULS.W	#$0018,D5
	DEF_ROMLOC(1B92C): move_toreg_32(0x0, &D2); // MOVEQ.L	$00,D2
	DEF_ROMLOC(1B92E): move_toreg_16(read_16(0xFFFFF700), &D2); // MOVE.W	$F700,D2
	DEF_ROMLOC(1B932): divu_toreg_16(0x18, &D2); // DIVU.W	#$0018,D2
	DEF_ROMLOC(1B936): swap_reg_16(&D2); // SWAP.W	D2
	DEF_ROMLOC(1B938): neg_reg_16(&D2); // NEG.W	D2
	DEF_ROMLOC(1B93A): add_toreg_16(0xFFFFFF4C, &D2); // ADDI.W	#$FF4C,D2
	DEF_ROMLOC(1B93E): move_toreg_32(0x0, &D3); // MOVEQ.L	$00,D3
	DEF_ROMLOC(1B940): move_toreg_16(read_16(0xFFFFF704), &D3); // MOVE.W	$F704,D3
	DEF_ROMLOC(1B944): divu_toreg_16(0x18, &D3); // DIVU.W	#$0018,D3
	DEF_ROMLOC(1B948): swap_reg_16(&D3); // SWAP.W	D3
	DEF_ROMLOC(1B94A): neg_reg_16(&D3); // NEG.W	D3
	DEF_ROMLOC(1B94C): add_toreg_16(0xFFFFFF4C, &D3); // ADDI.W	#$FF4C,D3
	DEF_ROMLOC(1B950): move_toreg_16(0xF, &D7); // MOVE.W	#$000F,D7
	rom_1B954(); // Detected flow into next function
}
ROMFUNC(rom_1B954) {
	u16 d0backupouter = 0;
	u16 d1backupouter = 0;
	u16 d0backupinner = 0;
	u16 d1backupinner = 0;
	u16 d2backup = 0;
	DEF_ROMLOC(1B954):
		d0backupouter = D0;
		d1backupouter = D1;
		d2backup = D2;
		// TODO; // MOVEM.W	D0-D2,-(A7)
	DEF_ROMLOC(1B958):
		d0backupinner = D0;
		d1backupinner = D1;
		// TODO; // MOVEM.W	D0-D1,-(A7)
	DEF_ROMLOC(1B95C): neg_reg_16(&D0); // NEG.W	D0
	DEF_ROMLOC(1B95E): muls_toreg_16(D2, &D1); // MULS.W	D2,D1
	DEF_ROMLOC(1B960): muls_toreg_16(D3, &D0); // MULS.W	D3,D0
	DEF_ROMLOC(1B962): move_toreg_32(D0, &D6); // MOVE.L	D0,D6
	DEF_ROMLOC(1B964): add_toreg_32(D1, &D6); // ADD.L	D1,D6
	DEF_ROMLOC(1B966):
		D0 = (s32)((s16)d0backupinner);
		D1 = (s32)((s16)d1backupinner);
		// TODO; // MOVEM.W	(A7)+,D0-D1
	DEF_ROMLOC(1B96A): muls_toreg_16(D2, &D0); // MULS.W	D2,D0
	DEF_ROMLOC(1B96C): muls_toreg_16(D3, &D1); // MULS.W	D3,D1
	DEF_ROMLOC(1B96E): add_toreg_32(D0, &D1); // ADD.L	D0,D1
	DEF_ROMLOC(1B970): move_toreg_32(D6, &D2); // MOVE.L	D6,D2
	DEF_ROMLOC(1B972): move_toreg_16(0xF, &D6); // MOVE.W	#$000F,D6
	DEF_ROMLOC(1B976): move_toreg_32(D2, &D0); // MOVE.L	D2,D0
	DEF_ROMLOC(1B978): asr_toreg_32(0x8, &D0); // ASR.L	#$08,D0
	DEF_ROMLOC(1B97A): move_tomem_16(D0, (A1 += 2, A1 - 2)); // MOVE.W	D0,(A1)+
	DEF_ROMLOC(1B97C): move_toreg_32(D1, &D0); // MOVE.L	D1,D0
	DEF_ROMLOC(1B97E): asr_toreg_32(0x8, &D0); // ASR.L	#$08,D0
	DEF_ROMLOC(1B980): move_tomem_16(D0, (A1 += 2, A1 - 2)); // MOVE.W	D0,(A1)+
	DEF_ROMLOC(1B982): add_toreg_32(D5, &D2); // ADD.L	D5,D2
	DEF_ROMLOC(1B984): add_toreg_32(D4, &D1); // ADD.L	D4,D1
	DEF_ROMLOC(1B986): dec_reg_16(&D6); if ((D6 & 0xffff) != 0xffff) goto rom_1B976; // DBF.W	D6,$1B976
	DEF_ROMLOC(1B98A):
		D0 = (s32)((s16)d0backupouter);
		D1 = (s32)((s16)d1backupouter);
		D2 = (s32)((s16)d2backup);
		// TODO; // MOVEM.W	(A7)+,D0-D2
	DEF_ROMLOC(1B98E): add_toreg_16(0x18, &D3); // ADDI.W	#$0018,D3
	DEF_ROMLOC(1B992): dec_reg_16(&D7); if ((D7 & 0xffff) != 0xffff) goto rom_1B954; // DBF.W	D7,$1B954
	DEF_ROMLOC(1B996): move_toreg_16(read_16((A7 += 2, A7 - 2)), &D5); // MOVE.W	(A7)+,D5
	DEF_ROMLOC(1B998): move_toreg_32(0xFF0000, &A0); // LEA.L	$00FF0000,A0
	DEF_ROMLOC(1B99E): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(1B9A0): move_toreg_16(read_16(0xFFFFF704), &D0); // MOVE.W	$F704,D0
	DEF_ROMLOC(1B9A4): divu_toreg_16(0x18, &D0); // DIVU.W	#$0018,D0
	DEF_ROMLOC(1B9A8): mulu_toreg_16(0x80, &D0); // MULU.W	#$0080,D0
	DEF_ROMLOC(1B9AC): add_toreg_32(D0, &A0); // ADDA.L	D0,A0
	DEF_ROMLOC(1B9AE): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(1B9B0): move_toreg_16(read_16(0xFFFFF700), &D0); // MOVE.W	$F700,D0
	DEF_ROMLOC(1B9B4): divu_toreg_16(0x18, &D0); // DIVU.W	#$0018,D0
	DEF_ROMLOC(1B9B8): add_toreg_16(D0, &A0); // ADDA.W	D0,A0
	DEF_ROMLOC(1B9BA): move_toreg_32(0xFFFF8000, &A4); // LEA.L	$8000,A4
	DEF_ROMLOC(1B9BE): move_toreg_16(0xF, &D7); // MOVE.W	#$000F,D7
	rom_1B9C2(); // Detected flow into next function
}
ROMFUNC(rom_1B9C2) {
	DEF_ROMLOC(1B9C2): move_toreg_16(0xF, &D6); // MOVE.W	#$000F,D6
	DEF_ROMLOC(1B9C6): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(1B9C8): move_toreg_8(read_8(A0++), &D0); // MOVE.B	(A0)+,D0
	DEF_ROMLOC(1B9CA): if (CCR_EQ) goto rom_1BA1E; // BEQ.B	$1BA1E
	DEF_ROMLOC(1B9CC): cmp_toreg_8(0x4E, &D0); // CMPI.B	#$4E,D0
	DEF_ROMLOC(1B9D0): if (CCR_HI) goto rom_1BA1E; // BHI.B	$1BA1E
	DEF_ROMLOC(1B9D2): move_toreg_16(read_16(A4), &D3); // MOVE.W	(A4),D3
	DEF_ROMLOC(1B9D4): add_toreg_16(0x120, &D3); // ADDI.W	#$0120,D3
	DEF_ROMLOC(1B9D8): cmp_toreg_16(0x70, &D3); // CMPI.W	#$0070,D3
	DEF_ROMLOC(1B9DC): if (CCR_CS) goto rom_1BA1E; // BCS.B	$1BA1E
	DEF_ROMLOC(1B9DE): cmp_toreg_16(0x1D0, &D3); // CMPI.W	#$01D0,D3
	DEF_ROMLOC(1B9E2): if (CCR_CC) goto rom_1BA1E; // BCC.B	$1BA1E
	DEF_ROMLOC(1B9E4): move_toreg_16(read_16(A4 + 0x2), &D2); // MOVE.W	2(A4),D2
	DEF_ROMLOC(1B9E8): add_toreg_16(0xF0, &D2); // ADDI.W	#$00F0,D2
	DEF_ROMLOC(1B9EC): cmp_toreg_16(0x70, &D2); // CMPI.W	#$0070,D2
	DEF_ROMLOC(1B9F0): if (CCR_CS) goto rom_1BA1E; // BCS.B	$1BA1E
	DEF_ROMLOC(1B9F2): cmp_toreg_16(0x170, &D2); // CMPI.W	#$0170,D2
	DEF_ROMLOC(1B9F6): if (CCR_CC) goto rom_1BA1E; // BCC.B	$1BA1E
	DEF_ROMLOC(1B9F8): move_toreg_32(0xFF4000, &A5); // LEA.L	$00FF4000,A5
	DEF_ROMLOC(1B9FE): lsl_toreg_16(0x3, &D0); // LSL.W	#$03,D0
	DEF_ROMLOC(1BA00): move_toreg_32((s32)A5 + (s8)0x0 + (s16)D0, &A5); // LEA.L	0(A5,D0),A5
	DEF_ROMLOC(1BA04): move_toreg_32(read_32((A5 += 4, A5 - 4)), &A1); // MOVEA.L	(A5)+,A1
	DEF_ROMLOC(1BA06): move_toreg_16(read_16((A5 += 2, A5 - 2)), &D1); // MOVE.W	(A5)+,D1
	DEF_ROMLOC(1BA08): add_toreg_16(D1, &D1); // ADD.W	D1,D1
	DEF_ROMLOC(1BA0A): add_toreg_16(read_16((s32)A1 + (s8)0x0 + (s16)D1), &A1); // ADDA.W	0(A1,D1),A1
	DEF_ROMLOC(1BA0E): move_toreg_16(read_16((A5 += 2, A5 - 2)), &A3); // MOVEA.W	(A5)+,A3
	DEF_ROMLOC(1BA10): move_toreg_32(0x0, &D1); // MOVEQ.L	$00,D1
	DEF_ROMLOC(1BA12): move_toreg_8(read_8(A1++), &D1); // MOVE.B	(A1)+,D1
	DEF_ROMLOC(1BA14): sub_toreg_8(0x1, &D1); // SUBQ.B	#$01,D1
	DEF_ROMLOC(1BA16): if (CCR_MI) goto rom_1BA1E; // BMI.B	$1BA1E
	DEF_ROMLOC(1BA18): rom_DDF0(); // JSR	$0000DDF0
	DEF_ROMLOC(1BA1E): add_toreg_16(0x4, &A4); // ADDQ.W	#$04,A4
	DEF_ROMLOC(1BA20): dec_reg_16(&D6); if ((D6 & 0xffff) != 0xffff) goto rom_1B9C6; // DBF.W	D6,$1B9C6
	DEF_ROMLOC(1BA24): move_toreg_32(A0 + 0x70, &A0); // LEA.L	112(A0),A0
	DEF_ROMLOC(1BA28): dec_reg_16(&D7); if ((D7 & 0xffff) != 0xffff) goto rom_1B9C2; // DBF.W	D7,$1B9C2
	DEF_ROMLOC(1BA2C): move_tomem_8(D5, 0xFFFFF62C); // MOVE.B	D5,$F62C
	DEF_ROMLOC(1BA30): cmp_toreg_8(0x50, &D5); // CMPI.B	#$50,D5
	DEF_ROMLOC(1BA34): if (CCR_EQ) goto rom_1BA3E; // BEQ.B	$1BA3E
	DEF_ROMLOC(1BA36): move_tomem_32(0x0, A2); // MOVE.L	#$00000000,(A2)
	DEF_ROMLOC(1BA3C): return; // RTS
	DEF_ROMLOC(1BA3E): move_tomem_8(0x0, A2 - 0x5); // MOVE.B	#$00,-5(A2)
	DEF_ROMLOC(1BA44): return; // RTS
}
ROMFUNC(rom_1BC86) {
	DEF_ROMLOC(1BC86): move_toreg_32(0xFF4400, &A0); // LEA.L	$00FF4400,A0
	DEF_ROMLOC(1BC8C): move_toreg_16(0x1F, &D7); // MOVE.W	#$001F,D7
	rom_1BC90(); // Detected flow into next function
}
ROMFUNC(rom_1BC90) {
	u8 switchindex = 0;
	DEF_ROMLOC(1BC90): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(1BC92): move_toreg_8(read_8(A0), &D0); // MOVE.B	(A0),D0
	DEF_ROMLOC(1BC94): if (CCR_EQ) goto rom_1BC9E; // BEQ.B	$1BC9E
	DEF_ROMLOC(1BC96): switchindex = D0 - 1; lsl_toreg_16(0x2, &D0); // LSL.W	#$02,D0
	DEF_ROMLOC(1BC98): move_toreg_32(read_32(0x1BCA2 + (s16)(D0 & 0xffff)), &A1); // MOVEA.L	8(PC,D0),A1
	// DEF_ROMLOC(1BC9C): rom_A1(); // JSR	(A1)
	DEF_ROMLOC(1BC9C):
		switch (switchindex) {
			case 0: rom_1BCBE(); break;
			case 1: rom_1BCEE(); break;
			case 2: rom_1BD24(); break;
			case 3: rom_1BD54(); break;
			case 4: rom_1BD8A(); break;
			case 5: rom_1BDCA(); break;
		}
	DEF_ROMLOC(1BC9E): add_toreg_16(0x8, &A0); // ADDQ.W	#$08,A0
	DEF_ROMLOC(1BCA0): dec_reg_16(&D7); if ((D7 & 0xffff) != 0xffff) goto rom_1BC90; // DBF.W	D7,$1BC90
	DEF_ROMLOC(1BCA4): return; // RTS
}
ROMFUNC(rom_1BCA6) {
	DEF_ROMLOC(1BCA6): or_toreg_8(0xFFFFFFBE, &D1); // ORI.B	#$BE,D1
	DEF_ROMLOC(1BCAA): or_toreg_8(0xFFFFFFEE, &D1); // ORI.B	#$EE,D1
	DEF_ROMLOC(1BCAE): or_toreg_8(0x24, &D1); // ORI.B	#$24,D1
	DEF_ROMLOC(1BCB2): or_toreg_8(0x54, &D1); // ORI.B	#$54,D1
	DEF_ROMLOC(1BCB6): or_toreg_8(0xFFFFFF8A, &D1); // ORI.B	#$8A,D1
	DEF_ROMLOC(1BCBA): or_toreg_8(0xFFFFFFCA, &D1); // ORI.B	#$CA,D1
	rom_1BCBE(); // Detected flow into next function
}
ROMFUNC(rom_1BCBE) {
	DEF_ROMLOC(1BCBE): sub_tomem_8(0x1, A0 + 0x2); // SUBQ.B	#$01,2(A0)
	DEF_ROMLOC(1BCC2): if (CCR_PL) goto rom_1BCE6; // BPL.B	$1BCE6
	DEF_ROMLOC(1BCC4): move_tomem_8(0x5, A0 + 0x2); // MOVE.B	#$05,2(A0)
	DEF_ROMLOC(1BCCA): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(1BCCC): move_toreg_8(read_8(A0 + 0x3), &D0); // MOVE.B	3(A0),D0
	DEF_ROMLOC(1BCD0): add_tomem_8(0x1, A0 + 0x3); // ADDQ.B	#$01,3(A0)
	DEF_ROMLOC(1BCD4): move_toreg_32(read_32(A0 + 0x4), &A1); // MOVEA.L	4(A0),A1
	DEF_ROMLOC(1BCD8): move_toreg_8(read_8(0x1BCE8 + (s16)(D0 & 0xffff)), &D0); // MOVE.B	14(PC,D0),D0
	DEF_ROMLOC(1BCDC): move_tomem_8(D0, A1); // MOVE.B	D0,(A1)
	DEF_ROMLOC(1BCDE): if (!CCR_EQ) goto rom_1BCE6; // BNE.B	$1BCE6
	DEF_ROMLOC(1BCE0): clr_mem_32(A0); // CLR.L	(A0)
	DEF_ROMLOC(1BCE2): clr_mem_32(A0 + 0x4); // CLR.L	4(A0)
	DEF_ROMLOC(1BCE6): return; // RTS
}
ROMFUNC(rom_1BCE8) {
	DEF_ROMLOC(1BCE8): clr_reg_16(&D3); // CLR.W	D3
	DEF_ROMLOC(1BCEA): neg_reg_16(&D5); // NEG.W	D5
	DEF_ROMLOC(1BCEC): or_toreg_8(0x28, &D0); // ORI.B	#$28,D0
	DEF_ROMLOC(1BCF0): or_toreg_8(0x28, &D2); // ORI.B	#$28,D2
	DEF_ROMLOC(1BCF4): move_tomem_8(0x7, A0 + 0x2); // MOVE.B	#$07,2(A0)
	DEF_ROMLOC(1BCFA): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(1BCFC): move_toreg_8(read_8(A0 + 0x3), &D0); // MOVE.B	3(A0),D0
	DEF_ROMLOC(1BD00): add_tomem_8(0x1, A0 + 0x3); // ADDQ.B	#$01,3(A0)
	DEF_ROMLOC(1BD04): move_toreg_32(read_32(A0 + 0x4), &A1); // MOVEA.L	4(A0),A1
	DEF_ROMLOC(1BD08): move_toreg_8(read_8(0x1BD1E + (s16)(D0 & 0xffff)), &D0); // MOVE.B	20(PC,D0),D0
	DEF_ROMLOC(1BD0C): if (!CCR_EQ) goto rom_1BD1A; // BNE.B	$1BD1A
	DEF_ROMLOC(1BD0E): clr_mem_32(A0); // CLR.L	(A0)
	DEF_ROMLOC(1BD10): clr_mem_32(A0 + 0x4); // CLR.L	4(A0)
	DEF_ROMLOC(1BD14): move_tomem_8(0x25, A1); // MOVE.B	#$25,(A1)
	DEF_ROMLOC(1BD18): return; // RTS
	DEF_ROMLOC(1BD1A): move_tomem_8(D0, A1); // MOVE.B	D0,(A1)
	DEF_ROMLOC(1BD1C): return; // RTS
	DEF_ROMLOC(1BD1E): move_toreg_16(read_16((s32)A3 + (s8)0x33 + (s16)D3), &D1); // MOVE.W	51(A3,D3),D1
	DEF_ROMLOC(1BD22): or_toreg_8(0x28, &D0); // ORI.B	#$28,D0
	DEF_ROMLOC(1BD26): or_toreg_8(0x22, &D2); // ORI.B	#$22,D2
	DEF_ROMLOC(1BD2A): move_tomem_8(0x5, A0 + 0x2); // MOVE.B	#$05,2(A0)
	DEF_ROMLOC(1BD30): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(1BD32): move_toreg_8(read_8(A0 + 0x3), &D0); // MOVE.B	3(A0),D0
	DEF_ROMLOC(1BD36): add_tomem_8(0x1, A0 + 0x3); // ADDQ.B	#$01,3(A0)
	DEF_ROMLOC(1BD3A): move_toreg_32(read_32(A0 + 0x4), &A1); // MOVEA.L	4(A0),A1
	DEF_ROMLOC(1BD3E): move_toreg_8(read_8(0x1BD4E + (s16)(D0 & 0xffff)), &D0); // MOVE.B	14(PC,D0),D0
	DEF_ROMLOC(1BD42): move_tomem_8(D0, A1); // MOVE.B	D0,(A1)
	DEF_ROMLOC(1BD44): if (!CCR_EQ) goto rom_1BD4C; // BNE.B	$1BD4C
	DEF_ROMLOC(1BD46): clr_mem_32(A0); // CLR.L	(A0)
	DEF_ROMLOC(1BD48): clr_mem_32(A0 + 0x4); // CLR.L	4(A0)
	DEF_ROMLOC(1BD4C): return; // RTS
	DEF_ROMLOC(1BD4E): not_reg_16(&D7); // NOT.W	D7
	rom_1BCEE(); // Detected flow into next function
}
ROMFUNC(rom_1BCEE) {
	DEF_ROMLOC(1BCEE): sub_tomem_8(0x1, A0 + 0x2); // SUBQ.B	#$01,2(A0)
	DEF_ROMLOC(1BCF2): if (CCR_PL) goto rom_1BD1C; // BPL.B	$1BD1C
	DEF_ROMLOC(1BCF4): move_tomem_8(0x7, A0 + 0x2); // MOVE.B	#$07,2(A0)
	DEF_ROMLOC(1BCFA): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(1BCFC): move_toreg_8(read_8(A0 + 0x3), &D0); // MOVE.B	3(A0),D0
	DEF_ROMLOC(1BD00): add_tomem_8(0x1, A0 + 0x3); // ADDQ.B	#$01,3(A0)
	DEF_ROMLOC(1BD04): move_toreg_32(read_32(A0 + 0x4), &A1); // MOVEA.L	4(A0),A1
	DEF_ROMLOC(1BD08): move_toreg_8(read_8(0x1BD1E + (s16)(D0 & 0xffff)), &D0); // MOVE.B	20(PC,D0),D0
	DEF_ROMLOC(1BD0C): if (!CCR_EQ) goto rom_1BD1A; // BNE.B	$1BD1A
	DEF_ROMLOC(1BD0E): clr_mem_32(A0); // CLR.L	(A0)
	DEF_ROMLOC(1BD10): clr_mem_32(A0 + 0x4); // CLR.L	4(A0)
	DEF_ROMLOC(1BD14): move_tomem_8(0x25, A1); // MOVE.B	#$25,(A1)
	DEF_ROMLOC(1BD18): return; // RTS
	DEF_ROMLOC(1BD1A): move_tomem_8(D0, A1); // MOVE.B	D0,(A1)
	DEF_ROMLOC(1BD1C): return; // RTS
}
ROMFUNC(rom_1BD1E) {
	DEF_ROMLOC(1BD1E): move_toreg_16(read_16((s32)A3 + (s8)0x33 + (s16)D3), &D1); // MOVE.W	51(A3,D3),D1
	DEF_ROMLOC(1BD22): or_toreg_8(0x28, &D0); // ORI.B	#$28,D0
	DEF_ROMLOC(1BD26): or_toreg_8(0x22, &D2); // ORI.B	#$22,D2
	DEF_ROMLOC(1BD2A): move_tomem_8(0x5, A0 + 0x2); // MOVE.B	#$05,2(A0)
	DEF_ROMLOC(1BD30): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(1BD32): move_toreg_8(read_8(A0 + 0x3), &D0); // MOVE.B	3(A0),D0
	DEF_ROMLOC(1BD36): add_tomem_8(0x1, A0 + 0x3); // ADDQ.B	#$01,3(A0)
	DEF_ROMLOC(1BD3A): move_toreg_32(read_32(A0 + 0x4), &A1); // MOVEA.L	4(A0),A1
	DEF_ROMLOC(1BD3E): move_toreg_8(read_8(0x1BD4E + (s16)(D0 & 0xffff)), &D0); // MOVE.B	14(PC,D0),D0
	DEF_ROMLOC(1BD42): move_tomem_8(D0, A1); // MOVE.B	D0,(A1)
	DEF_ROMLOC(1BD44): if (!CCR_EQ) goto rom_1BD4C; // BNE.B	$1BD4C
	DEF_ROMLOC(1BD46): clr_mem_32(A0); // CLR.L	(A0)
	DEF_ROMLOC(1BD48): clr_mem_32(A0 + 0x4); // CLR.L	4(A0)
	DEF_ROMLOC(1BD4C): return; // RTS
	DEF_ROMLOC(1BD4E): not_reg_16(&D7); // NOT.W	D7
	rom_1BD24(); // Detected flow into next function
}
ROMFUNC(rom_1BD24) {
	DEF_ROMLOC(1BD24): sub_tomem_8(0x1, A0 + 0x2); // SUBQ.B	#$01,2(A0)
	DEF_ROMLOC(1BD28): if (CCR_PL) goto rom_1BD4C; // BPL.B	$1BD4C
	DEF_ROMLOC(1BD2A): move_tomem_8(0x5, A0 + 0x2); // MOVE.B	#$05,2(A0)
	DEF_ROMLOC(1BD30): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(1BD32): move_toreg_8(read_8(A0 + 0x3), &D0); // MOVE.B	3(A0),D0
	DEF_ROMLOC(1BD36): add_tomem_8(0x1, A0 + 0x3); // ADDQ.B	#$01,3(A0)
	DEF_ROMLOC(1BD3A): move_toreg_32(read_32(A0 + 0x4), &A1); // MOVEA.L	4(A0),A1
	DEF_ROMLOC(1BD3E): move_toreg_8(read_8(0x1BD4E + (s16)(D0 & 0xffff)), &D0); // MOVE.B	14(PC,D0),D0
	DEF_ROMLOC(1BD42): move_tomem_8(D0, A1); // MOVE.B	D0,(A1)
	DEF_ROMLOC(1BD44): if (!CCR_EQ) goto rom_1BD4C; // BNE.B	$1BD4C
	DEF_ROMLOC(1BD46): clr_mem_32(A0); // CLR.L	(A0)
	DEF_ROMLOC(1BD48): clr_mem_32(A0 + 0x4); // CLR.L	4(A0)
	DEF_ROMLOC(1BD4C): return; // RTS
}
ROMFUNC(rom_1BD54) {
	DEF_ROMLOC(1BD54): sub_tomem_8(0x1, A0 + 0x2); // SUBQ.B	#$01,2(A0)
	DEF_ROMLOC(1BD58): if (CCR_PL) goto rom_1BD82; // BPL.B	$1BD82
	DEF_ROMLOC(1BD5A): move_tomem_8(0x7, A0 + 0x2); // MOVE.B	#$07,2(A0)
	DEF_ROMLOC(1BD60): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(1BD62): move_toreg_8(read_8(A0 + 0x3), &D0); // MOVE.B	3(A0),D0
	DEF_ROMLOC(1BD66): add_tomem_8(0x1, A0 + 0x3); // ADDQ.B	#$01,3(A0)
	DEF_ROMLOC(1BD6A): move_toreg_32(read_32(A0 + 0x4), &A1); // MOVEA.L	4(A0),A1
	DEF_ROMLOC(1BD6E): move_toreg_8(read_8(0x1BD84 + (s16)(D0 & 0xffff)), &D0); // MOVE.B	20(PC,D0),D0
	DEF_ROMLOC(1BD72): if (!CCR_EQ) goto rom_1BD80; // BNE.B	$1BD80
	DEF_ROMLOC(1BD74): clr_mem_32(A0); // CLR.L	(A0)
	DEF_ROMLOC(1BD76): clr_mem_32(A0 + 0x4); // CLR.L	4(A0)
	DEF_ROMLOC(1BD7A): move_tomem_8(0x2B, A1); // MOVE.B	#$2B,(A1)
	DEF_ROMLOC(1BD7E): return; // RTS
	DEF_ROMLOC(1BD80): move_tomem_8(D0, A1); // MOVE.B	D0,(A1)
	DEF_ROMLOC(1BD82): return; // RTS
}
ROMFUNC(rom_1BD84) {
	DEF_ROMLOC(1BD84): move_tomem_32(read_32((s32)A1 + (s8)0x31 + (s16)D2), A5 -= 4); // MOVE.L	49(A1,D2),-(A5)
	DEF_ROMLOC(1BD88): or_toreg_8(0x28, &D0); // ORI.B	#$28,D0
	DEF_ROMLOC(1BD8C): or_toreg_8(0x32, &D2); // ORI.B	#$32,D2
	DEF_ROMLOC(1BD90): move_tomem_8(0x5, A0 + 0x2); // MOVE.B	#$05,2(A0)
	DEF_ROMLOC(1BD96): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(1BD98): move_toreg_8(read_8(A0 + 0x3), &D0); // MOVE.B	3(A0),D0
	DEF_ROMLOC(1BD9C): add_tomem_8(0x1, A0 + 0x3); // ADDQ.B	#$01,3(A0)
	DEF_ROMLOC(1BDA0): move_toreg_32(read_32(A0 + 0x4), &A1); // MOVEA.L	4(A0),A1
	DEF_ROMLOC(1BDA4): move_toreg_8(read_8(0x1BDC4 + (s16)(D0 & 0xffff)), &D0); // MOVE.B	30(PC,D0),D0
	DEF_ROMLOC(1BDA8): move_tomem_8(D0, A1); // MOVE.B	D0,(A1)
	DEF_ROMLOC(1BDAA): if (!CCR_EQ) goto rom_1BDC2; // BNE.B	$1BDC2
	DEF_ROMLOC(1BDAC): clr_mem_32(A0); // CLR.L	(A0)
	DEF_ROMLOC(1BDAE): clr_mem_32(A0 + 0x4); // CLR.L	4(A0)
	DEF_ROMLOC(1BDB2): move_tomem_8(0x4, 0xFFFFD024); // MOVE.B	#$04,$D024
	DEF_ROMLOC(1BDB8): move_toreg_16(0xA8, &D0); // MOVE.W	#$00A8,D0
	DEF_ROMLOC(1BDBC): rom_1394(); // JSR	$00001394
	DEF_ROMLOC(1BDC2): return; // RTS
	DEF_ROMLOC(1BDC4): not_reg_16(&D7); // NOT.W	D7
	rom_1BD8A(); // Detected flow into next function
}
ROMFUNC(rom_1BD8A) {
	DEF_ROMLOC(1BD8A): sub_tomem_8(0x1, A0 + 0x2); // SUBQ.B	#$01,2(A0)
	DEF_ROMLOC(1BD8E): if (CCR_PL) goto rom_1BDC2; // BPL.B	$1BDC2
	DEF_ROMLOC(1BD90): move_tomem_8(0x5, A0 + 0x2); // MOVE.B	#$05,2(A0)
	DEF_ROMLOC(1BD96): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(1BD98): move_toreg_8(read_8(A0 + 0x3), &D0); // MOVE.B	3(A0),D0
	DEF_ROMLOC(1BD9C): add_tomem_8(0x1, A0 + 0x3); // ADDQ.B	#$01,3(A0)
	DEF_ROMLOC(1BDA0): move_toreg_32(read_32(A0 + 0x4), &A1); // MOVEA.L	4(A0),A1
	DEF_ROMLOC(1BDA4): move_toreg_8(read_8(0x1BDC4 + (s16)(D0 & 0xffff)), &D0); // MOVE.B	30(PC,D0),D0
	DEF_ROMLOC(1BDA8): move_tomem_8(D0, A1); // MOVE.B	D0,(A1)
	DEF_ROMLOC(1BDAA): if (!CCR_EQ) goto rom_1BDC2; // BNE.B	$1BDC2
	DEF_ROMLOC(1BDAC): clr_mem_32(A0); // CLR.L	(A0)
	DEF_ROMLOC(1BDAE): clr_mem_32(A0 + 0x4); // CLR.L	4(A0)
	DEF_ROMLOC(1BDB2): move_tomem_8(0x4, 0xFFFFD024); // MOVE.B	#$04,$D024
	DEF_ROMLOC(1BDB8): move_toreg_16(0xA8, &D0); // MOVE.W	#$00A8,D0
	DEF_ROMLOC(1BDBC): rom_1394(); // JSR	$00001394
	DEF_ROMLOC(1BDC2): return; // RTS
}
ROMFUNC(rom_1BDCA) {
	DEF_ROMLOC(1BDCA): sub_tomem_8(0x1, A0 + 0x2); // SUBQ.B	#$01,2(A0)
	DEF_ROMLOC(1BDCE): if (CCR_PL) goto rom_1BDF6; // BPL.B	$1BDF6
	DEF_ROMLOC(1BDD0): move_tomem_8(0x1, A0 + 0x2); // MOVE.B	#$01,2(A0)
	DEF_ROMLOC(1BDD6): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(1BDD8): move_toreg_8(read_8(A0 + 0x3), &D0); // MOVE.B	3(A0),D0
	DEF_ROMLOC(1BDDC): add_tomem_8(0x1, A0 + 0x3); // ADDQ.B	#$01,3(A0)
	DEF_ROMLOC(1BDE0): move_toreg_32(read_32(A0 + 0x4), &A1); // MOVEA.L	4(A0),A1
	DEF_ROMLOC(1BDE4): move_toreg_8(read_8(0x1BDF8 + (s16)(D0 & 0xffff)), &D0); // MOVE.B	18(PC,D0),D0
	DEF_ROMLOC(1BDE8): move_tomem_8(D0, A1); // MOVE.B	D0,(A1)
	DEF_ROMLOC(1BDEA): if (!CCR_EQ) goto rom_1BDF6; // BNE.B	$1BDF6
	DEF_ROMLOC(1BDEC): move_tomem_8(read_8(A0 + 0x4), A1); // MOVE.B	4(A0),(A1)
	DEF_ROMLOC(1BDF0): clr_mem_32(A0); // CLR.L	(A0)
	DEF_ROMLOC(1BDF2): clr_mem_32(A0 + 0x4); // CLR.L	4(A0)
	DEF_ROMLOC(1BDF6): return; // RTS
}
ROMFUNC(rom_1BE02) {
	DEF_ROMLOC(1BE02): or_toreg_8(0x32, &D6); // ORI.B	#$32,D6
	DEF_ROMLOC(1BE06): or_toreg_8(0xFFFFFFAC, &D6); // ORI.B	#$AC,D6
	DEF_ROMLOC(1BE0A): or_toreg_8(0xFFFFFFBE, &D6); // ORI.B	#$BE,D6
	DEF_ROMLOC(1BE0E): or_toreg_8(0x1A, &D6); // ORI.B	#$1A,D6
	DEF_ROMLOC(1BE12): or_toreg_8(0xFFFFFFF4, &D6); // ORI.B	#$F4,D6
	DEF_ROMLOC(1BE16): or_toreg_8(0xFFFFFFA4, &D6); // ORI.B	#$A4,D6
	rom_1BE1A(); // Detected flow into next function
}
ROMFUNC(rom_1BE1A) {
	DEF_ROMLOC(1BE1A): bset_tomem_8(D1, A0); // BSET.B	D1,(A0)
	rom_1BE32(); // Detected flow into next function
}
ROMFUNC(rom_1BE32) {
	DEF_ROMLOC(1BE32): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(1BE34): move_toreg_8(read_8(0xFFFFFE16), &D0); // MOVE.B	$FE16,D0
	DEF_ROMLOC(1BE38): add_tomem_8(0x1, 0xFFFFFE16); // ADDQ.B	#$01,$FE16
	DEF_ROMLOC(1BE3C): cmp_tomem_8(0x6, 0xFFFFFE16); // CMPI.B	#$06,$FE16
	DEF_ROMLOC(1BE42): if (CCR_CS) goto rom_1BE4A; // BCS.B	$1BE4A
	DEF_ROMLOC(1BE44): move_tomem_8(0x0, 0xFFFFFE16); // MOVE.B	#$00,$FE16
	DEF_ROMLOC(1BE4A): cmp_tomem_8(0x6, 0xFFFFFE57); // CMPI.B	#$06,$FE57
	DEF_ROMLOC(1BE50): if (CCR_EQ) goto rom_1BE6C; // BEQ.B	$1BE6C
	DEF_ROMLOC(1BE52): move_toreg_32(0x0, &D1); // MOVEQ.L	$00,D1
	DEF_ROMLOC(1BE54): move_toreg_8(read_8(0xFFFFFE57), &D1); // MOVE.B	$FE57,D1
	DEF_ROMLOC(1BE58): sub_toreg_8(0x1, &D1); // SUBQ.B	#$01,D1
	DEF_ROMLOC(1BE5A): if (CCR_CS) goto rom_1BE6C; // BCS.B	$1BE6C
	DEF_ROMLOC(1BE5C): move_toreg_32(0xFFFFFE58, &A3); // LEA.L	$FE58,A3
	DEF_ROMLOC(1BE60): cmp_toreg_8(read_8((s32)A3 + (s8)0x0 + (s16)D1), &D0); // CMP.B	0(A3,D1),D0
	DEF_ROMLOC(1BE64): if (!CCR_EQ) goto rom_1BE68; // BNE.B	$1BE68
	goto rom_1BE32; // BRA.B	$1BE32
	DEF_ROMLOC(1BE68): dec_reg_16(&D1); if ((D1 & 0xffff) != 0xffff) goto rom_1BE60; // DBF.W	D1,$1BE60
	DEF_ROMLOC(1BE6C): lsl_toreg_16(0x2, &D0); // LSL.W	#$02,D0
	DEF_ROMLOC(1BE6E): move_toreg_32(0x1BE1A + (s16)(D0 & 0xffff), &A1); // LEA.L	-86(PC,D0),A1
	DEF_ROMLOC(1BE72): move_tomem_16(read_16((A1 += 2, A1 - 2)), 0xFFFFD008); // MOVE.W	(A1)+,$D008
	DEF_ROMLOC(1BE76): move_tomem_16(read_16((A1 += 2, A1 - 2)), 0xFFFFD00C); // MOVE.W	(A1)+,$D00C
	DEF_ROMLOC(1BE7A): move_toreg_32(read_32(0x1BE02 + (s16)(D0 & 0xffff)), &A0); // MOVEA.L	-122(PC,D0),A0
	DEF_ROMLOC(1BE7E): move_toreg_32(0xFF4000, &A1); // LEA.L	$00FF4000,A1
	DEF_ROMLOC(1BE84): move_toreg_16(0x0, &D0); // MOVE.W	#$0000,D0
	DEF_ROMLOC(1BE88): rom_1716(); // JSR	$00001716
	DEF_ROMLOC(1BE8E): move_toreg_32(0xFF0000, &A1); // LEA.L	$00FF0000,A1
	DEF_ROMLOC(1BE94): move_toreg_16(0xFFF, &D0); // MOVE.W	#$0FFF,D0
	rom_1BE98(); // Detected flow into next function
}
ROMFUNC(rom_1BE98) {
	DEF_ROMLOC(1BE98): clr_mem_32((A1 += 4, A1 - 4)); // CLR.L	(A1)+
	DEF_ROMLOC(1BE9A): dec_reg_16(&D0); if ((D0 & 0xffff) != 0xffff) goto rom_1BE98; // DBF.W	D0,$1BE98
	DEF_ROMLOC(1BE9E): move_toreg_32(0xFF1020, &A1); // LEA.L	$00FF1020,A1
	DEF_ROMLOC(1BEA4): move_toreg_32(0xFF4000, &A0); // LEA.L	$00FF4000,A0
	DEF_ROMLOC(1BEAA): move_toreg_32(0x3F, &D1); // MOVEQ.L	$3F,D1
	rom_1BEAC(); // Detected flow into next function
}
ROMFUNC(rom_1BEAC) {
	DEF_ROMLOC(1BEAC): move_toreg_32(0x3F, &D2); // MOVEQ.L	$3F,D2
	DEF_ROMLOC(1BEAE): move_tomem_8(read_8(A0++), A1++); // MOVE.B	(A0)+,(A1)+
	DEF_ROMLOC(1BEB0): dec_reg_16(&D2); if ((D2 & 0xffff) != 0xffff) goto rom_1BEAE; // DBF.W	D2,$1BEAE
	DEF_ROMLOC(1BEB4): move_toreg_32(A1 + 0x40, &A1); // LEA.L	64(A1),A1
	DEF_ROMLOC(1BEB8): dec_reg_16(&D1); if ((D1 & 0xffff) != 0xffff) goto rom_1BEAC; // DBF.W	D1,$1BEAC
	DEF_ROMLOC(1BEBC): move_toreg_32(0xFF4008, &A1); // LEA.L	$00FF4008,A1
	DEF_ROMLOC(1BEC2): move_toreg_32(0x1BEEE, &A0); // LEA.L	$0001BEEE,A0
	DEF_ROMLOC(1BEC8): move_toreg_32(0x4D, &D1); // MOVEQ.L	$4D,D1
	DEF_ROMLOC(1BECA): move_tomem_32(read_32((A0 += 4, A0 - 4)), (A1 += 4, A1 - 4)); // MOVE.L	(A0)+,(A1)+
	DEF_ROMLOC(1BECC): move_tomem_16(0x0, (A1 += 2, A1 - 2)); // MOVE.W	#$0000,(A1)+
	DEF_ROMLOC(1BED0): move_tomem_8(read_8(A0 - 0x4), A1 - 0x1); // MOVE.B	-4(A0),-1(A1)
	DEF_ROMLOC(1BED6): move_tomem_16(read_16((A0 += 2, A0 - 2)), (A1 += 2, A1 - 2)); // MOVE.W	(A0)+,(A1)+
	DEF_ROMLOC(1BED8): dec_reg_16(&D1); if ((D1 & 0xffff) != 0xffff) goto rom_1BECA; // DBF.W	D1,$1BECA
	DEF_ROMLOC(1BEDC): move_toreg_32(0xFF4400, &A1); // LEA.L	$00FF4400,A1
	DEF_ROMLOC(1BEE2): move_toreg_16(0x3F, &D1); // MOVE.W	#$003F,D1
	rom_1BEE6(); // Detected flow into next function
}
ROMFUNC(rom_1BEE6) {
	DEF_ROMLOC(1BEE6): clr_mem_32((A1 += 4, A1 - 4)); // CLR.L	(A1)+
	DEF_ROMLOC(1BEE8): dec_reg_16(&D1); if ((D1 & 0xffff) != 0xffff) goto rom_1BEE6; // DBF.W	D1,$1BEE6
	DEF_ROMLOC(1BEEC): return; // RTS
}
ROMFUNC(rom_1C36C) {
	DEF_ROMLOC(1C36C): move_toreg_16(read_16(A0 + 0xC), &D2); // MOVE.W	12(A0),D2
	DEF_ROMLOC(1C370): move_toreg_16(read_16(A0 + 0x8), &D3); // MOVE.W	8(A0),D3
	DEF_ROMLOC(1C374): move_toreg_16(read_16(0xFFFFF700), &D0); // MOVE.W	$F700,D0
	DEF_ROMLOC(1C378): sub_toreg_16(0xA0, &D3); // SUBI.W	#$00A0,D3
	DEF_ROMLOC(1C37C): if (CCR_CS) goto rom_1C384; // BCS.B	$1C384
	DEF_ROMLOC(1C37E): sub_toreg_16(D3, &D0); // SUB.W	D3,D0
	DEF_ROMLOC(1C380): sub_tomem_16(D0, 0xFFFFF700); // SUB.W	D0,$F700
	DEF_ROMLOC(1C384): move_toreg_16(read_16(0xFFFFF704), &D0); // MOVE.W	$F704,D0
	DEF_ROMLOC(1C388): sub_toreg_16(0x70, &D2); // SUBI.W	#$0070,D2
	DEF_ROMLOC(1C38C): if (CCR_CS) goto rom_1C394; // BCS.B	$1C394
	DEF_ROMLOC(1C38E): sub_toreg_16(D2, &D0); // SUB.W	D2,D0
	DEF_ROMLOC(1C390): sub_tomem_16(D0, 0xFFFFF704); // SUB.W	D0,$F704
	DEF_ROMLOC(1C394): return; // RTS
}
ROMFUNC(rom_1C396) {
	DEF_ROMLOC(1C396): add_tomem_16(0x40, 0xFFFFF782); // ADDI.W	#$0040,$F782
	DEF_ROMLOC(1C39C): cmp_tomem_16(0x1800, 0xFFFFF782); // CMPI.W	#$1800,$F782
	DEF_ROMLOC(1C3A2): if (!CCR_EQ) goto rom_1C3AA; // BNE.B	$1C3AA
	DEF_ROMLOC(1C3A4): move_tomem_8(0xC, 0xFFFFF600); // MOVE.B	#$0C,$F600
	DEF_ROMLOC(1C3AA): cmp_tomem_16(0x3000, 0xFFFFF782); // CMPI.W	#$3000,$F782
	DEF_ROMLOC(1C3B0): if (CCR_LT) goto rom_1C3C8; // BLT.B	$1C3C8
	DEF_ROMLOC(1C3B2): move_tomem_16(0x0, 0xFFFFF782); // MOVE.W	#$0000,$F782
	DEF_ROMLOC(1C3B8): move_tomem_16(0x4000, 0xFFFFF780); // MOVE.W	#$4000,$F780
	DEF_ROMLOC(1C3BE): add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
	DEF_ROMLOC(1C3C2): move_tomem_16(0x3C, A0 + 0x38); // MOVE.W	#$003C,56(A0)
	DEF_ROMLOC(1C3C8): move_toreg_16(read_16(0xFFFFF780), &D0); // MOVE.W	$F780,D0
	DEF_ROMLOC(1C3CC): add_toreg_16(read_16(0xFFFFF782), &D0); // ADD.W	$F782,D0
	DEF_ROMLOC(1C3D0): move_tomem_16(D0, 0xFFFFF780); // MOVE.W	D0,$F780
	DEF_ROMLOC(1C3D4): rom_14098(); // JSR	$00014098
	DEF_ROMLOC(1C3DA): rom_14312(); // JSR	$00014312
	DEF_ROMLOC(1C3E0): rom_1C36C(); // BSR.W	$1C36C
	DEF_ROMLOC(1C3E4): {rom_DC92();return;} // JMP	$0000DC92
}
ROMFUNC(rom_1C3EA) {
	DEF_ROMLOC(1C3EA): sub_tomem_16(0x1, A0 + 0x38); // SUBQ.W	#$01,56(A0)
	DEF_ROMLOC(1C3EE): if (!CCR_EQ) goto rom_1C3F6; // BNE.B	$1C3F6
	DEF_ROMLOC(1C3F0): move_tomem_8(0xC, 0xFFFFF600); // MOVE.B	#$0C,$F600
	DEF_ROMLOC(1C3F6): rom_14098(); // JSR	$00014098
	DEF_ROMLOC(1C3FC): rom_14312(); // JSR	$00014312
	DEF_ROMLOC(1C402): rom_1C36C(); // BSR.W	$1C36C
	DEF_ROMLOC(1C406): {rom_DC92();return;} // JMP	$0000DC92
}
ROMFUNC(rom_1C40C) {
	DEF_ROMLOC(1C40C): move_toreg_32(read_32(A0 + 0xC), &D2); // MOVE.L	12(A0),D2
	DEF_ROMLOC(1C410): move_toreg_32(read_32(A0 + 0x8), &D3); // MOVE.L	8(A0),D3
	DEF_ROMLOC(1C414): move_toreg_8(read_8(0xFFFFF780), &D0); // MOVE.B	$F780,D0
	DEF_ROMLOC(1C418): and_toreg_8(0xFFFFFFFC, &D0); // ANDI.B	#$FC,D0
	DEF_ROMLOC(1C41C): rom_29D2(); // JSR	$000029D2
	DEF_ROMLOC(1C422): move_toreg_16(read_16(A0 + 0x10), &D4); // MOVE.W	16(A0),D4
	DEF_ROMLOC(1C426): ext_reg_32(&D4); // EXT.L	D4
	DEF_ROMLOC(1C428): asl_toreg_32(0x8, &D4); // ASL.L	#$08,D4
	DEF_ROMLOC(1C42A): muls_toreg_16(0x2A, &D0); // MULS.W	#$002A,D0
	DEF_ROMLOC(1C42E): add_toreg_32(D4, &D0); // ADD.L	D4,D0
	DEF_ROMLOC(1C430): move_toreg_16(read_16(A0 + 0x12), &D4); // MOVE.W	18(A0),D4
	DEF_ROMLOC(1C434): ext_reg_32(&D4); // EXT.L	D4
	DEF_ROMLOC(1C436): asl_toreg_32(0x8, &D4); // ASL.L	#$08,D4
	DEF_ROMLOC(1C438): muls_toreg_16(0x2A, &D1); // MULS.W	#$002A,D1
	DEF_ROMLOC(1C43C): add_toreg_32(D4, &D1); // ADD.L	D4,D1
	DEF_ROMLOC(1C43E): add_toreg_32(D0, &D3); // ADD.L	D0,D3
	DEF_ROMLOC(1C440): rom_1C49E(); // BSR.W	$1C49E
	DEF_ROMLOC(1C444): if (CCR_EQ) goto rom_1C466; // BEQ.B	$1C466
	DEF_ROMLOC(1C446): sub_toreg_32(D0, &D3); // SUB.L	D0,D3
	DEF_ROMLOC(1C448): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(1C44A): move_tomem_16(D0, A0 + 0x10); // MOVE.W	D0,16(A0)
	DEF_ROMLOC(1C44E): bclr_tomem_8(0x1, A0 + 0x22); // BCLR.B	#$01,34(A0)
	DEF_ROMLOC(1C454): add_toreg_32(D1, &D2); // ADD.L	D1,D2
	DEF_ROMLOC(1C456): rom_1C49E(); // BSR.W	$1C49E
	DEF_ROMLOC(1C45A): if (CCR_EQ) goto rom_1C47C; // BEQ.B	$1C47C
	DEF_ROMLOC(1C45C): sub_toreg_32(D1, &D2); // SUB.L	D1,D2
	DEF_ROMLOC(1C45E): move_toreg_32(0x0, &D1); // MOVEQ.L	$00,D1
	DEF_ROMLOC(1C460): move_tomem_16(D1, A0 + 0x12); // MOVE.W	D1,18(A0)
	DEF_ROMLOC(1C464): return; // RTS
	DEF_ROMLOC(1C466): add_toreg_32(D1, &D2); // ADD.L	D1,D2
	DEF_ROMLOC(1C468): rom_1C49E(); // BSR.W	$1C49E
	DEF_ROMLOC(1C46C): if (CCR_EQ) goto rom_1C48A; // BEQ.B	$1C48A
	DEF_ROMLOC(1C46E): sub_toreg_32(D1, &D2); // SUB.L	D1,D2
	DEF_ROMLOC(1C470): move_toreg_32(0x0, &D1); // MOVEQ.L	$00,D1
	DEF_ROMLOC(1C472): move_tomem_16(D1, A0 + 0x12); // MOVE.W	D1,18(A0)
	DEF_ROMLOC(1C476): bclr_tomem_8(0x1, A0 + 0x22); // BCLR.B	#$01,34(A0)
	DEF_ROMLOC(1C47C): asr_toreg_32(0x8, &D0); // ASR.L	#$08,D0
	DEF_ROMLOC(1C47E): asr_toreg_32(0x8, &D1); // ASR.L	#$08,D1
	DEF_ROMLOC(1C480): move_tomem_16(D0, A0 + 0x10); // MOVE.W	D0,16(A0)
	DEF_ROMLOC(1C484): move_tomem_16(D1, A0 + 0x12); // MOVE.W	D1,18(A0)
	DEF_ROMLOC(1C488): return; // RTS
	DEF_ROMLOC(1C48A): asr_toreg_32(0x8, &D0); // ASR.L	#$08,D0
	DEF_ROMLOC(1C48C): asr_toreg_32(0x8, &D1); // ASR.L	#$08,D1
	DEF_ROMLOC(1C48E): move_tomem_16(D0, A0 + 0x10); // MOVE.W	D0,16(A0)
	DEF_ROMLOC(1C492): move_tomem_16(D1, A0 + 0x12); // MOVE.W	D1,18(A0)
	DEF_ROMLOC(1C496): bset_tomem_8(0x1, A0 + 0x22); // BSET.B	#$01,34(A0)
	DEF_ROMLOC(1C49C): return; // RTS
}
ROMFUNC(rom_1C49E) {
	DEF_ROMLOC(1C49E): move_toreg_32(0xFF0000, &A1); // LEA.L	$00FF0000,A1
	DEF_ROMLOC(1C4A4): move_toreg_32(0x0, &D4); // MOVEQ.L	$00,D4
	DEF_ROMLOC(1C4A6): swap_reg_16(&D2); // SWAP.W	D2
	DEF_ROMLOC(1C4A8): move_toreg_16(D2, &D4); // MOVE.W	D2,D4
	DEF_ROMLOC(1C4AA): swap_reg_16(&D2); // SWAP.W	D2
	DEF_ROMLOC(1C4AC): add_toreg_16(0x44, &D4); // ADDI.W	#$0044,D4
	DEF_ROMLOC(1C4B0): divu_toreg_16(0x18, &D4); // DIVU.W	#$0018,D4
	DEF_ROMLOC(1C4B4): mulu_toreg_16(0x80, &D4); // MULU.W	#$0080,D4
	DEF_ROMLOC(1C4B8): add_toreg_32(D4, &A1); // ADDA.L	D4,A1
	DEF_ROMLOC(1C4BA): move_toreg_32(0x0, &D4); // MOVEQ.L	$00,D4
	DEF_ROMLOC(1C4BC): swap_reg_16(&D3); // SWAP.W	D3
	DEF_ROMLOC(1C4BE): move_toreg_16(D3, &D4); // MOVE.W	D3,D4
	DEF_ROMLOC(1C4C0): swap_reg_16(&D3); // SWAP.W	D3
	DEF_ROMLOC(1C4C2): add_toreg_16(0x14, &D4); // ADDI.W	#$0014,D4
	DEF_ROMLOC(1C4C6): divu_toreg_16(0x18, &D4); // DIVU.W	#$0018,D4
	DEF_ROMLOC(1C4CA): add_toreg_16(D4, &A1); // ADDA.W	D4,A1
	DEF_ROMLOC(1C4CC): move_toreg_32(0x0, &D5); // MOVEQ.L	$00,D5
	DEF_ROMLOC(1C4CE): move_toreg_8(read_8(A1++), &D4); // MOVE.B	(A1)+,D4
	DEF_ROMLOC(1C4D0): rom_1C4E6(); // BSR.B	$1C4E6
	DEF_ROMLOC(1C4D2): move_toreg_8(read_8(A1++), &D4); // MOVE.B	(A1)+,D4
	DEF_ROMLOC(1C4D4): rom_1C4E6(); // BSR.B	$1C4E6
	DEF_ROMLOC(1C4D6): add_toreg_16(0x7E, &A1); // ADDA.W	#$007E,A1
	DEF_ROMLOC(1C4DA): move_toreg_8(read_8(A1++), &D4); // MOVE.B	(A1)+,D4
	DEF_ROMLOC(1C4DC): rom_1C4E6(); // BSR.B	$1C4E6
	DEF_ROMLOC(1C4DE): move_toreg_8(read_8(A1++), &D4); // MOVE.B	(A1)+,D4
	DEF_ROMLOC(1C4E0): rom_1C4E6(); // BSR.B	$1C4E6
	DEF_ROMLOC(1C4E2): tst_reg_8(&D5); // TST.B	D5
	DEF_ROMLOC(1C4E4): return; // RTS
}
ROMFUNC(rom_1C4E6) {
	DEF_ROMLOC(1C4E6): if (CCR_EQ) goto rom_1C4FA; // BEQ.B	$1C4FA
	DEF_ROMLOC(1C4E8): cmp_toreg_8(0x28, &D4); // CMPI.B	#$28,D4
	DEF_ROMLOC(1C4EC): if (CCR_EQ) goto rom_1C4FA; // BEQ.B	$1C4FA
	DEF_ROMLOC(1C4EE): cmp_toreg_8(0x3A, &D4); // CMPI.B	#$3A,D4
	DEF_ROMLOC(1C4F2): if (CCR_CS) goto rom_1C4FC; // BCS.B	$1C4FC
	DEF_ROMLOC(1C4F4): cmp_toreg_8(0x4B, &D4); // CMPI.B	#$4B,D4
	DEF_ROMLOC(1C4F8): if (CCR_CC) goto rom_1C4FC; // BCC.B	$1C4FC
	DEF_ROMLOC(1C4FA): return; // RTS
	DEF_ROMLOC(1C4FC): move_tomem_8(D4, A0 + 0x30); // MOVE.B	D4,48(A0)
	DEF_ROMLOC(1C500): move_tomem_32(A1, A0 + 0x32); // MOVE.L	A1,50(A0)
	DEF_ROMLOC(1C504): move_toreg_32(0xFFFFFFFF, &D5); // MOVEQ.L	$FF,D5
	DEF_ROMLOC(1C506): return; // RTS
}
ROMFUNC(rom_1C508) {
	DEF_ROMLOC(1C508): move_toreg_32(0xFF0000, &A1); // LEA.L	$00FF0000,A1
	DEF_ROMLOC(1C50E): move_toreg_32(0x0, &D4); // MOVEQ.L	$00,D4
	DEF_ROMLOC(1C510): move_toreg_16(read_16(A0 + 0xC), &D4); // MOVE.W	12(A0),D4
	DEF_ROMLOC(1C514): add_toreg_16(0x50, &D4); // ADDI.W	#$0050,D4
	DEF_ROMLOC(1C518): divu_toreg_16(0x18, &D4); // DIVU.W	#$0018,D4
	DEF_ROMLOC(1C51C): mulu_toreg_16(0x80, &D4); // MULU.W	#$0080,D4
	DEF_ROMLOC(1C520): add_toreg_32(D4, &A1); // ADDA.L	D4,A1
	DEF_ROMLOC(1C522): move_toreg_32(0x0, &D4); // MOVEQ.L	$00,D4
	DEF_ROMLOC(1C524): move_toreg_16(read_16(A0 + 0x8), &D4); // MOVE.W	8(A0),D4
	DEF_ROMLOC(1C528): add_toreg_16(0x20, &D4); // ADDI.W	#$0020,D4
	DEF_ROMLOC(1C52C): divu_toreg_16(0x18, &D4); // DIVU.W	#$0018,D4
	DEF_ROMLOC(1C530): add_toreg_16(D4, &A1); // ADDA.W	D4,A1
	DEF_ROMLOC(1C532): move_toreg_8(read_8(A1), &D4); // MOVE.B	(A1),D4
	DEF_ROMLOC(1C534): if (!CCR_EQ) goto rom_1C542; // BNE.B	$1C542
	DEF_ROMLOC(1C536): tst_mem_8(A0 + 0x3A); // TST.B	58(A0)
	DEF_ROMLOC(1C53A): if (!CCR_EQ) goto rom_1C612; // BNE.W	$1C612
	DEF_ROMLOC(1C53E): move_toreg_32(0x0, &D4); // MOVEQ.L	$00,D4
	DEF_ROMLOC(1C540): return; // RTS
	DEF_ROMLOC(1C542): cmp_toreg_8(0x3A, &D4); // CMPI.B	#$3A,D4
	DEF_ROMLOC(1C546): if (!CCR_EQ) goto rom_1C57E; // BNE.B	$1C57E
	DEF_ROMLOC(1C548): rom_1BC70(); // BSR.W	$1BC70
	DEF_ROMLOC(1C54C): if (!CCR_EQ) goto rom_1C556; // BNE.B	$1C556
	DEF_ROMLOC(1C54E): move_tomem_8(0x1, A2); // MOVE.B	#$01,(A2)
	DEF_ROMLOC(1C552): move_tomem_32(A1, A2 + 0x4); // MOVE.L	A1,4(A2)
	DEF_ROMLOC(1C556): rom_A2F4(); // JSR	$0000A2F4
	DEF_ROMLOC(1C55C): cmp_tomem_16(0x32, 0xFFFFFE20); // CMPI.W	#$0032,$FE20
	DEF_ROMLOC(1C562): if (CCR_CS) goto rom_1C57A; // BCS.B	$1C57A
	DEF_ROMLOC(1C564): bset_tomem_8(0x0, 0xFFFFFE1B); // BSET.B	#$00,$FE1B
	DEF_ROMLOC(1C56A): if (!CCR_EQ) goto rom_1C57A; // BNE.B	$1C57A
	DEF_ROMLOC(1C56C): add_tomem_8(0x1, 0xFFFFFE18); // ADDQ.B	#$01,$FE18
	DEF_ROMLOC(1C570): move_toreg_16(0xBF, &D0); // MOVE.W	#$00BF,D0
	DEF_ROMLOC(1C574): rom_138E(); // JSR	$0000138E
	DEF_ROMLOC(1C57A): move_toreg_32(0x0, &D4); // MOVEQ.L	$00,D4
	DEF_ROMLOC(1C57C): return; // RTS
	DEF_ROMLOC(1C57E): cmp_toreg_8(0x28, &D4); // CMPI.B	#$28,D4
	DEF_ROMLOC(1C582): if (!CCR_EQ) goto rom_1C5A8; // BNE.B	$1C5A8
	DEF_ROMLOC(1C584): rom_1BC70(); // BSR.W	$1BC70
	DEF_ROMLOC(1C588): if (!CCR_EQ) goto rom_1C592; // BNE.B	$1C592
	DEF_ROMLOC(1C58A): move_tomem_8(0x3, A2); // MOVE.B	#$03,(A2)
	DEF_ROMLOC(1C58E): move_tomem_32(A1, A2 + 0x4); // MOVE.L	A1,4(A2)
	DEF_ROMLOC(1C592): add_tomem_8(0x1, 0xFFFFFE12); // ADDQ.B	#$01,$FE12
	DEF_ROMLOC(1C596): add_tomem_8(0x1, 0xFFFFFE1C); // ADDQ.B	#$01,$FE1C
	DEF_ROMLOC(1C59A): move_toreg_16(0x88, &D0); // MOVE.W	#$0088,D0
	DEF_ROMLOC(1C59E): rom_138E(); // JSR	$0000138E
	DEF_ROMLOC(1C5A4): move_toreg_32(0x0, &D4); // MOVEQ.L	$00,D4
	DEF_ROMLOC(1C5A6): return; // RTS
	DEF_ROMLOC(1C5A8): cmp_toreg_8(0x3B, &D4); // CMPI.B	#$3B,D4
	DEF_ROMLOC(1C5AC): if (CCR_CS) goto rom_1C5EE; // BCS.B	$1C5EE
	DEF_ROMLOC(1C5AE): cmp_toreg_8(0x40, &D4); // CMPI.B	#$40,D4
	DEF_ROMLOC(1C5B2): if (CCR_HI) goto rom_1C5EE; // BHI.B	$1C5EE
	DEF_ROMLOC(1C5B4): rom_1BC70(); // BSR.W	$1BC70
	DEF_ROMLOC(1C5B8): if (!CCR_EQ) goto rom_1C5C2; // BNE.B	$1C5C2
	DEF_ROMLOC(1C5BA): move_tomem_8(0x5, A2); // MOVE.B	#$05,(A2)
	DEF_ROMLOC(1C5BE): move_tomem_32(A1, A2 + 0x4); // MOVE.L	A1,4(A2)
	DEF_ROMLOC(1C5C2): cmp_tomem_8(0x6, 0xFFFFFE57); // CMPI.B	#$06,$FE57
	DEF_ROMLOC(1C5C8): if (CCR_EQ) goto rom_1C5E0; // BEQ.B	$1C5E0
	DEF_ROMLOC(1C5CA): sub_toreg_8(0x3B, &D4); // SUBI.B	#$3B,D4
	DEF_ROMLOC(1C5CE): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(1C5D0): move_toreg_8(read_8(0xFFFFFE57), &D0); // MOVE.B	$FE57,D0
	DEF_ROMLOC(1C5D4): move_toreg_32(0xFFFFFE58, &A2); // LEA.L	$FE58,A2
	DEF_ROMLOC(1C5D8): move_tomem_8(D4, (s32)A2 + (s8)0x0 + (s16)D0); // MOVE.B	D4,0(A2,D0)
	DEF_ROMLOC(1C5DC): add_tomem_8(0x1, 0xFFFFFE57); // ADDQ.B	#$01,$FE57
	DEF_ROMLOC(1C5E0): move_toreg_16(0x93, &D0); // MOVE.W	#$0093,D0
	DEF_ROMLOC(1C5E4): rom_1394(); // JSR	$00001394
	DEF_ROMLOC(1C5EA): move_toreg_32(0x0, &D4); // MOVEQ.L	$00,D4
	DEF_ROMLOC(1C5EC): return; // RTS
	DEF_ROMLOC(1C5EE): cmp_toreg_8(0x41, &D4); // CMPI.B	#$41,D4
	DEF_ROMLOC(1C5F2): if (!CCR_EQ) goto rom_1C5FA; // BNE.B	$1C5FA
	DEF_ROMLOC(1C5F4): move_tomem_8(0x1, A0 + 0x3A); // MOVE.B	#$01,58(A0)
	DEF_ROMLOC(1C5FA): cmp_toreg_8(0x4A, &D4); // CMPI.B	#$4A,D4
	DEF_ROMLOC(1C5FE): if (!CCR_EQ) goto rom_1C60E; // BNE.B	$1C60E
	DEF_ROMLOC(1C600): cmp_tomem_8(0x1, A0 + 0x3A); // CMPI.B	#$01,58(A0)
	DEF_ROMLOC(1C606): if (!CCR_EQ) goto rom_1C60E; // BNE.B	$1C60E
	DEF_ROMLOC(1C608): move_tomem_8(0x2, A0 + 0x3A); // MOVE.B	#$02,58(A0)
	DEF_ROMLOC(1C60E): move_toreg_32(0xFFFFFFFF, &D4); // MOVEQ.L	$FF,D4
	DEF_ROMLOC(1C610): return; // RTS
	DEF_ROMLOC(1C612): cmp_tomem_8(0x2, A0 + 0x3A); // CMPI.B	#$02,58(A0)
	DEF_ROMLOC(1C618): if (!CCR_EQ) goto rom_1C63C; // BNE.B	$1C63C
	DEF_ROMLOC(1C61A): move_toreg_32(0xFF1020, &A1); // LEA.L	$00FF1020,A1
	DEF_ROMLOC(1C620): move_toreg_32(0x3F, &D1); // MOVEQ.L	$3F,D1
	DEF_ROMLOC(1C622): move_toreg_32(0x3F, &D2); // MOVEQ.L	$3F,D2
	DEF_ROMLOC(1C624): cmp_tomem_8(0x41, A1); // CMPI.B	#$41,(A1)
	DEF_ROMLOC(1C628): if (!CCR_EQ) goto rom_1C62E; // BNE.B	$1C62E
	DEF_ROMLOC(1C62A): move_tomem_8(0x2C, A1); // MOVE.B	#$2C,(A1)
	DEF_ROMLOC(1C62E): add_toreg_16(0x1, &A1); // ADDQ.W	#$01,A1
	DEF_ROMLOC(1C630): dec_reg_16(&D2); if ((D2 & 0xffff) != 0xffff) goto rom_1C624; // DBF.W	D2,$1C624
	DEF_ROMLOC(1C634): move_toreg_32(A1 + 0x40, &A1); // LEA.L	64(A1),A1
	DEF_ROMLOC(1C638): dec_reg_16(&D1); if ((D1 & 0xffff) != 0xffff) goto rom_1C622; // DBF.W	D1,$1C622
	DEF_ROMLOC(1C63C): clr_mem_8(A0 + 0x3A); // CLR.B	58(A0)
	DEF_ROMLOC(1C640): move_toreg_32(0x0, &D4); // MOVEQ.L	$00,D4
	DEF_ROMLOC(1C642): return; // RTS
}
ROMFUNC(rom_1C644) {
	DEF_ROMLOC(1C644): move_toreg_8(read_8(A0 + 0x30), &D0); // MOVE.B	48(A0),D0
	DEF_ROMLOC(1C648): if (!CCR_EQ) goto rom_1C664; // BNE.B	$1C664
	DEF_ROMLOC(1C64A): sub_tomem_8(0x1, A0 + 0x36); // SUBQ.B	#$01,54(A0)
	DEF_ROMLOC(1C64E): if (CCR_PL) goto rom_1C656; // BPL.B	$1C656
	DEF_ROMLOC(1C650): move_tomem_8(0x0, A0 + 0x36); // MOVE.B	#$00,54(A0)
	DEF_ROMLOC(1C656): sub_tomem_8(0x1, A0 + 0x37); // SUBQ.B	#$01,55(A0)
	DEF_ROMLOC(1C65A): if (CCR_PL) goto rom_1C662; // BPL.B	$1C662
	DEF_ROMLOC(1C65C): move_tomem_8(0x0, A0 + 0x37); // MOVE.B	#$00,55(A0)
	DEF_ROMLOC(1C662): return; // RTS
	DEF_ROMLOC(1C664): cmp_toreg_8(0x25, &D0); // CMPI.B	#$25,D0
	DEF_ROMLOC(1C668): if (!CCR_EQ) goto rom_1C6DC; // BNE.B	$1C6DC
	DEF_ROMLOC(1C66A): move_toreg_32(read_32(A0 + 0x32), &D1); // MOVE.L	50(A0),D1
	DEF_ROMLOC(1C66E): sub_toreg_32(0xFF0001, &D1); // SUBI.L	#$00FF0001,D1
	DEF_ROMLOC(1C674): move_toreg_16(D1, &D2); // MOVE.W	D1,D2
	DEF_ROMLOC(1C676): and_toreg_16(0x7F, &D1); // ANDI.W	#$007F,D1
	DEF_ROMLOC(1C67A): mulu_toreg_16(0x18, &D1); // MULU.W	#$0018,D1
	DEF_ROMLOC(1C67E): sub_toreg_16(0x14, &D1); // SUBI.W	#$0014,D1
	DEF_ROMLOC(1C682): lsr_toreg_16(0x7, &D2); // LSR.W	#$07,D2
	DEF_ROMLOC(1C684): and_toreg_16(0x7F, &D2); // ANDI.W	#$007F,D2
	DEF_ROMLOC(1C688): mulu_toreg_16(0x18, &D2); // MULU.W	#$0018,D2
	DEF_ROMLOC(1C68C): sub_toreg_16(0x44, &D2); // SUBI.W	#$0044,D2
	DEF_ROMLOC(1C690): sub_toreg_16(read_16(A0 + 0x8), &D1); // SUB.W	8(A0),D1
	DEF_ROMLOC(1C694): sub_toreg_16(read_16(A0 + 0xC), &D2); // SUB.W	12(A0),D2
	DEF_ROMLOC(1C698): rom_2C6A(); // JSR	$00002C6A
	DEF_ROMLOC(1C69E): rom_29D2(); // JSR	$000029D2
	DEF_ROMLOC(1C6A4): muls_toreg_16(0xFFFFF900, &D1); // MULS.W	#$F900,D1
	DEF_ROMLOC(1C6A8): asr_toreg_32(0x8, &D1); // ASR.L	#$08,D1
	DEF_ROMLOC(1C6AA): move_tomem_16(D1, A0 + 0x10); // MOVE.W	D1,16(A0)
	DEF_ROMLOC(1C6AE): muls_toreg_16(0xFFFFF900, &D0); // MULS.W	#$F900,D0
	DEF_ROMLOC(1C6B2): asr_toreg_32(0x8, &D0); // ASR.L	#$08,D0
	DEF_ROMLOC(1C6B4): move_tomem_16(D0, A0 + 0x12); // MOVE.W	D0,18(A0)
	DEF_ROMLOC(1C6B8): bset_tomem_8(0x1, A0 + 0x22); // BSET.B	#$01,34(A0)
	DEF_ROMLOC(1C6BE): rom_1BC70(); // BSR.W	$1BC70
	DEF_ROMLOC(1C6C2): if (!CCR_EQ) goto rom_1C6D2; // BNE.B	$1C6D2
	DEF_ROMLOC(1C6C4): move_tomem_8(0x2, A2); // MOVE.B	#$02,(A2)
	DEF_ROMLOC(1C6C8): move_toreg_32(read_32(A0 + 0x32), &D0); // MOVE.L	50(A0),D0
	DEF_ROMLOC(1C6CC): sub_toreg_32(0x1, &D0); // SUBQ.L	#$01,D0
	DEF_ROMLOC(1C6CE): move_tomem_32(D0, A2 + 0x4); // MOVE.L	D0,4(A2)
	DEF_ROMLOC(1C6D2): move_toreg_16(0xB4, &D0); // MOVE.W	#$00B4,D0
	DEF_ROMLOC(1C6D6): rom_1394(); return; // JMP	$00001394
	DEF_ROMLOC(1C6DC): cmp_toreg_8(0x27, &D0); // CMPI.B	#$27,D0
	DEF_ROMLOC(1C6E0): if (!CCR_EQ) goto rom_1C6F2; // BNE.B	$1C6F2
	DEF_ROMLOC(1C6E2): add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
	DEF_ROMLOC(1C6E6): move_toreg_16(0xA8, &D0); // MOVE.W	#$00A8,D0
	DEF_ROMLOC(1C6EA): rom_1394(); // JSR	$00001394
	DEF_ROMLOC(1C6F0): return; // RTS
	DEF_ROMLOC(1C6F2): cmp_toreg_8(0x29, &D0); // CMPI.B	#$29,D0
	DEF_ROMLOC(1C6F6): if (!CCR_EQ) goto rom_1C726; // BNE.B	$1C726
	DEF_ROMLOC(1C6F8): tst_mem_8(A0 + 0x36); // TST.B	54(A0)
	DEF_ROMLOC(1C6FC): if (!CCR_EQ) goto rom_1C7D6; // BNE.W	$1C7D6
	DEF_ROMLOC(1C700): move_tomem_8(0x1E, A0 + 0x36); // MOVE.B	#$1E,54(A0)
	DEF_ROMLOC(1C706): btst_tomem_8(0x6, 0xFFFFF783); // BTST.B	#$06,$F783
	DEF_ROMLOC(1C70C): if (CCR_EQ) goto rom_1C71C; // BEQ.B	$1C71C
	DEF_ROMLOC(1C70E): asl_mem_16(0xFFFFF782); // ASL.W	$F782
	DEF_ROMLOC(1C712): move_toreg_32(read_32(A0 + 0x32), &A1); // MOVEA.L	50(A0),A1
	DEF_ROMLOC(1C716): sub_toreg_32(0x1, &A1); // SUBQ.L	#$01,A1
	DEF_ROMLOC(1C718): move_tomem_8(0x2A, A1); // MOVE.B	#$2A,(A1)
	DEF_ROMLOC(1C71C): move_toreg_16(0xA9, &D0); // MOVE.W	#$00A9,D0
	DEF_ROMLOC(1C720): rom_1394(); return; // JMP	$00001394
	DEF_ROMLOC(1C726): cmp_toreg_8(0x2A, &D0); // CMPI.B	#$2A,D0
	DEF_ROMLOC(1C72A): if (!CCR_EQ) goto rom_1C75A; // BNE.B	$1C75A
	DEF_ROMLOC(1C72C): tst_mem_8(A0 + 0x36); // TST.B	54(A0)
	DEF_ROMLOC(1C730): if (!CCR_EQ) goto rom_1C7D6; // BNE.W	$1C7D6
	DEF_ROMLOC(1C734): move_tomem_8(0x1E, A0 + 0x36); // MOVE.B	#$1E,54(A0)
	DEF_ROMLOC(1C73A): btst_tomem_8(0x6, 0xFFFFF783); // BTST.B	#$06,$F783
	DEF_ROMLOC(1C740): if (!CCR_EQ) goto rom_1C750; // BNE.B	$1C750
	DEF_ROMLOC(1C742): asr_mem_16(0xFFFFF782); // ASR.W	$F782
	DEF_ROMLOC(1C746): move_toreg_32(read_32(A0 + 0x32), &A1); // MOVEA.L	50(A0),A1
	DEF_ROMLOC(1C74A): sub_toreg_32(0x1, &A1); // SUBQ.L	#$01,A1
	DEF_ROMLOC(1C74C): move_tomem_8(0x29, A1); // MOVE.B	#$29,(A1)
	DEF_ROMLOC(1C750): move_toreg_16(0xA9, &D0); // MOVE.W	#$00A9,D0
	DEF_ROMLOC(1C754): rom_1394(); return; // JMP	$00001394
	DEF_ROMLOC(1C75A): cmp_toreg_8(0x2B, &D0); // CMPI.B	#$2B,D0
	DEF_ROMLOC(1C75E): if (!CCR_EQ) goto rom_1C790; // BNE.B	$1C790
	DEF_ROMLOC(1C760): tst_mem_8(A0 + 0x37); // TST.B	55(A0)
	DEF_ROMLOC(1C764): if (!CCR_EQ) goto rom_1C7D6; // BNE.W	$1C7D6
	DEF_ROMLOC(1C768): move_tomem_8(0x1E, A0 + 0x37); // MOVE.B	#$1E,55(A0)
	DEF_ROMLOC(1C76E): rom_1BC70(); // BSR.W	$1BC70
	DEF_ROMLOC(1C772): if (!CCR_EQ) goto rom_1C782; // BNE.B	$1C782
	DEF_ROMLOC(1C774): move_tomem_8(0x4, A2); // MOVE.B	#$04,(A2)
	DEF_ROMLOC(1C778): move_toreg_32(read_32(A0 + 0x32), &D0); // MOVE.L	50(A0),D0
	DEF_ROMLOC(1C77C): sub_toreg_32(0x1, &D0); // SUBQ.L	#$01,D0
	DEF_ROMLOC(1C77E): move_tomem_32(D0, A2 + 0x4); // MOVE.L	D0,4(A2)
	DEF_ROMLOC(1C782): neg_mem_16(0xFFFFF782); // NEG.W	$F782
	DEF_ROMLOC(1C786): move_toreg_16(0xA9, &D0); // MOVE.W	#$00A9,D0
	DEF_ROMLOC(1C78A): rom_1394(); return; // JMP	$00001394
	DEF_ROMLOC(1C790): cmp_toreg_8(0x2D, &D0); // CMPI.B	#$2D,D0
	DEF_ROMLOC(1C794): if (CCR_EQ) goto rom_1C7A8; // BEQ.B	$1C7A8
	DEF_ROMLOC(1C796): cmp_toreg_8(0x2E, &D0); // CMPI.B	#$2E,D0
	DEF_ROMLOC(1C79A): if (CCR_EQ) goto rom_1C7A8; // BEQ.B	$1C7A8
	DEF_ROMLOC(1C79C): cmp_toreg_8(0x2F, &D0); // CMPI.B	#$2F,D0
	DEF_ROMLOC(1C7A0): if (CCR_EQ) goto rom_1C7A8; // BEQ.B	$1C7A8
	DEF_ROMLOC(1C7A2): cmp_toreg_8(0x30, &D0); // CMPI.B	#$30,D0
	DEF_ROMLOC(1C7A6): if (!CCR_EQ) goto rom_1C7D6; // BNE.B	$1C7D6
	DEF_ROMLOC(1C7A8): rom_1BC70(); // BSR.W	$1BC70
	DEF_ROMLOC(1C7AC): if (!CCR_EQ) goto rom_1C7CC; // BNE.B	$1C7CC
	DEF_ROMLOC(1C7AE): move_tomem_8(0x6, A2); // MOVE.B	#$06,(A2)
	DEF_ROMLOC(1C7B2): move_toreg_32(read_32(A0 + 0x32), &A1); // MOVEA.L	50(A0),A1
	DEF_ROMLOC(1C7B6): sub_toreg_32(0x1, &A1); // SUBQ.L	#$01,A1
	DEF_ROMLOC(1C7B8): move_tomem_32(A1, A2 + 0x4); // MOVE.L	A1,4(A2)
	DEF_ROMLOC(1C7BC): move_toreg_8(read_8(A1), &D0); // MOVE.B	(A1),D0
	DEF_ROMLOC(1C7BE): add_toreg_8(0x1, &D0); // ADDQ.B	#$01,D0
	DEF_ROMLOC(1C7C0): cmp_toreg_8(0x30, &D0); // CMPI.B	#$30,D0
	DEF_ROMLOC(1C7C4): if (CCR_LS) goto rom_1C7C8; // BLS.B	$1C7C8
	DEF_ROMLOC(1C7C6): clr_reg_8(&D0); // CLR.B	D0
	DEF_ROMLOC(1C7C8): move_tomem_8(D0, A2 + 0x4); // MOVE.B	D0,4(A2)
	DEF_ROMLOC(1C7CC): move_toreg_16(0xBA, &D0); // MOVE.W	#$00BA,D0
	DEF_ROMLOC(1C7D0): rom_1394(); return; // JMP	$00001394
	DEF_ROMLOC(1C7D6): return; // RTS
}