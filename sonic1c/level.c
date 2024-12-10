/*ROMFUNC(rom_359E) {
	DEF_ROMLOC(359E): move_tomem_8(read_8(--A2), --A3); // MOVE.B	-(A2),-(A3)
	DEF_ROMLOC(35A0): move_tomem_8(read_8(A5), --A2); // MOVE.B	(A5),-(A2)
	rom_3796(); // Detected flow into next function
}*/
/*ROMFUNC(rom_379E) {
	DEF_ROMLOC(379E): bset_tomem_8(0x7, 0xFFFFF600); // BSET.B	#$07,$F600
	DEF_ROMLOC(37A4): tst_mem_16(0xFFFFFFF0); // TST.W	$FFF0
	DEF_ROMLOC(37A8): if (CCR_MI) goto rom_37B2; // BMI.B	$37B2
	DEF_ROMLOC(37AA): move_toreg_8(0xFFFFFFE0, &D0); // MOVE.B	#$E0,D0
	DEF_ROMLOC(37AE): rom_1394(); // BSR.W	$1394
	rom_37B2(); // Detected flow into next function
}*/
/*ROMFUNC(rom_37B2) {
	DEF_ROMLOC(37B2): rom_15D6(); // BSR.W	$15D6
	DEF_ROMLOC(37B6): rom_1E4A(); // BSR.W	$1E4A
	DEF_ROMLOC(37BA): tst_mem_16(0xFFFFFFF0); // TST.W	$FFF0
	DEF_ROMLOC(37BE): if (CCR_MI) goto rom_37FE; // BMI.B	$37FE
	DEF_ROMLOC(37C0): move_tosr_16(0x2700, &SR); // MOVE.W	#$2700,SR
	DEF_ROMLOC(37C4): move_tomem_32(0x70000002, 0xC00004); // MOVE.L	#$70000002,$00C00004
	DEF_ROMLOC(37CE): move_toreg_32(0x39204, &A0); // LEA.L	$00039204,A0
	DEF_ROMLOC(37D4): rom_1438(); // BSR.W	$1438
	DEF_ROMLOC(37D8): move_tosr_16(0x2300, &SR); // MOVE.W	#$2300,SR
	DEF_ROMLOC(37DC): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(37DE): move_toreg_8(read_8(0xFFFFFE10), &D0); // MOVE.B	$FE10,D0
	DEF_ROMLOC(37E2): lsl_toreg_16(0x4, &D0); // LSL.W	#$04,D0
	DEF_ROMLOC(37E4): move_toreg_32(0x1DD16, &A2); // LEA.L	$0001DD16,A2
	DEF_ROMLOC(37EA): move_toreg_32((s32)A2 + (s8)0x0 + (s16)D0, &A2); // LEA.L	0(A2,D0),A2
	DEF_ROMLOC(37EE): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(37F0): move_toreg_8(read_8(A2), &D0); // MOVE.B	(A2),D0
	DEF_ROMLOC(37F2): if (CCR_EQ) goto rom_37F8; // BEQ.B	$37F8
	DEF_ROMLOC(37F4): rom_1578(); // BSR.W	$1578
	rom_37F8(); // Detected flow into next function
}*/
/*ROMFUNC(rom_37F8) {
	DEF_ROMLOC(37F8): move_toreg_32(0x1, &D0); // MOVEQ.L	$01,D0
	DEF_ROMLOC(37FA): rom_1578(); // BSR.W	$1578
	rom_37FE(); // Detected flow into next function
}*/
/*ROMFUNC(rom_37FE) {
	DEF_ROMLOC(37FE): move_toreg_32(0xFFFFD000, &A1); // LEA.L	$D000,A1
	DEF_ROMLOC(3802): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(3804): move_toreg_16(0x7FF, &D1); // MOVE.W	#$07FF,D1
	DEF_ROMLOC(3808): move_tomem_32(D0, (A1 += 4, A1 - 4)); // MOVE.L	D0,(A1)+
	DEF_ROMLOC(380A): dec_reg_16(&D1); if ((D1 & 0xffff) != 0xffff) goto rom_3808; // DBF.W	D1,$3808
	DEF_ROMLOC(380E): move_toreg_32(0xFFFFF628, &A1); // LEA.L	$F628,A1
	DEF_ROMLOC(3812): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(3814): move_toreg_16(0x15, &D1); // MOVE.W	#$0015,D1
	DEF_ROMLOC(3818): move_tomem_32(D0, (A1 += 4, A1 - 4)); // MOVE.L	D0,(A1)+
	DEF_ROMLOC(381A): dec_reg_16(&D1); if ((D1 & 0xffff) != 0xffff) goto rom_3818; // DBF.W	D1,$3818
	DEF_ROMLOC(381E): move_toreg_32(0xFFFFF700, &A1); // LEA.L	$F700,A1
	DEF_ROMLOC(3822): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(3824): move_toreg_16(0x3F, &D1); // MOVE.W	#$003F,D1
	DEF_ROMLOC(3828): move_tomem_32(D0, (A1 += 4, A1 - 4)); // MOVE.L	D0,(A1)+
	DEF_ROMLOC(382A): dec_reg_16(&D1); if ((D1 & 0xffff) != 0xffff) goto rom_3828; // DBF.W	D1,$3828
	DEF_ROMLOC(382E): move_toreg_32(0xFFFFFE60, &A1); // LEA.L	$FE60,A1
	DEF_ROMLOC(3832): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(3834): move_toreg_16(0x47, &D1); // MOVE.W	#$0047,D1
	DEF_ROMLOC(3838): move_tomem_32(D0, (A1 += 4, A1 - 4)); // MOVE.L	D0,(A1)+
	DEF_ROMLOC(383A): dec_reg_16(&D1); if ((D1 & 0xffff) != 0xffff) goto rom_3838; // DBF.W	D1,$3838
	DEF_ROMLOC(383E): move_tosr_16(0x2700, &SR); // MOVE.W	#$2700,SR
	DEF_ROMLOC(3842): rom_12C4(); // BSR.W	$12C4
	DEF_ROMLOC(3846): move_toreg_32(0xC00004, &A6); // LEA.L	$00C00004,A6
	DEF_ROMLOC(384C): move_tomem_16(0xFFFF8B03, A6); // MOVE.W	#$8B03,(A6)
	DEF_ROMLOC(3850): move_tomem_16(0xFFFF8230, A6); // MOVE.W	#$8230,(A6)
	DEF_ROMLOC(3854): move_tomem_16(0xFFFF8407, A6); // MOVE.W	#$8407,(A6)
	DEF_ROMLOC(3858): move_tomem_16(0xFFFF857C, A6); // MOVE.W	#$857C,(A6)
	DEF_ROMLOC(385C): move_tomem_16(0xFFFF9001, A6); // MOVE.W	#$9001,(A6)
	DEF_ROMLOC(3860): move_tomem_16(0xFFFF8004, A6); // MOVE.W	#$8004,(A6)
	DEF_ROMLOC(3864): move_tomem_16(0xFFFF8720, A6); // MOVE.W	#$8720,(A6)
	DEF_ROMLOC(3868): move_tomem_16(0xFFFF8ADF, 0xFFFFF624); // MOVE.W	#$8ADF,$F624
	DEF_ROMLOC(386E): move_tomem_16(read_16(0xFFFFF624), A6); // MOVE.W	$F624,(A6)
	DEF_ROMLOC(3872): cmp_tomem_8(0x1, 0xFFFFFE10); // CMPI.B	#$01,$FE10
	DEF_ROMLOC(3878): if (!CCR_EQ) goto rom_38AA; // BNE.B	$38AA
	DEF_ROMLOC(387A): move_tomem_16(0xFFFF8014, A6); // MOVE.W	#$8014,(A6)
	DEF_ROMLOC(387E): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(3880): move_toreg_8(read_8(0xFFFFFE11), &D0); // MOVE.B	$FE11,D0
	DEF_ROMLOC(3884): add_toreg_16(D0, &D0); // ADD.W	D0,D0
	DEF_ROMLOC(3886): move_toreg_32(0x3C2C, &A1); // LEA.L	$00003C2C,A1
	DEF_ROMLOC(388C): move_toreg_16(read_16((s32)A1 + (s8)0x0 + (s16)D0), &D0); // MOVE.W	0(A1,D0),D0
	DEF_ROMLOC(3890): move_tomem_16(D0, 0xFFFFF646); // MOVE.W	D0,$F646
	DEF_ROMLOC(3894): move_tomem_16(D0, 0xFFFFF648); // MOVE.W	D0,$F648
	DEF_ROMLOC(3898): move_tomem_16(D0, 0xFFFFF64A); // MOVE.W	D0,$F64A
	DEF_ROMLOC(389C): clr_mem_8(0xFFFFF64D); // CLR.B	$F64D
	DEF_ROMLOC(38A0): clr_mem_8(0xFFFFF64E); // CLR.B	$F64E
	DEF_ROMLOC(38A4): move_tomem_8(0x1, 0xFFFFF64C); // MOVE.B	#$01,$F64C
	rom_38AA(); // Detected flow into next function
}*/
/*ROMFUNC(rom_38AA) {
	DEF_ROMLOC(38AA): move_tomem_16(0x1E, 0xFFFFFE14); // MOVE.W	#$001E,$FE14
	DEF_ROMLOC(38B0): move_tosr_16(0x2300, &SR); // MOVE.W	#$2300,SR
	DEF_ROMLOC(38B4): move_toreg_32(0x3, &D0); // MOVEQ.L	$03,D0
	DEF_ROMLOC(38B6): rom_2110(); // BSR.W	$2110
	DEF_ROMLOC(38BA): cmp_tomem_8(0x1, 0xFFFFFE10); // CMPI.B	#$01,$FE10
	DEF_ROMLOC(38C0): if (!CCR_EQ) goto rom_38DE; // BNE.B	$38DE
	DEF_ROMLOC(38C2): move_toreg_32(0xF, &D0); // MOVEQ.L	$0F,D0
	DEF_ROMLOC(38C4): cmp_tomem_8(0x3, 0xFFFFFE11); // CMPI.B	#$03,$FE11
	DEF_ROMLOC(38CA): if (!CCR_EQ) goto rom_38CE; // BNE.B	$38CE
	DEF_ROMLOC(38CC): move_toreg_32(0x10, &D0); // MOVEQ.L	$10,D0
	rom_38CE(); // Detected flow into next function
}*/
/*ROMFUNC(rom_38CE) {
	DEF_ROMLOC(38CE): rom_2128(); // BSR.W	$2128
	DEF_ROMLOC(38D2): tst_mem_8(0xFFFFFE30); // TST.B	$FE30
	DEF_ROMLOC(38D6): if (CCR_EQ) goto rom_38DE; // BEQ.B	$38DE
	DEF_ROMLOC(38D8): move_tomem_8(read_8(0xFFFFFE53), 0xFFFFF64E); // MOVE.B	$FE53,$F64E
	rom_38DE(); // Detected flow into next function
}*/
/*ROMFUNC(rom_38DE) {
	DEF_ROMLOC(38DE): tst_mem_16(0xFFFFFFF0); // TST.W	$FFF0
	DEF_ROMLOC(38E2): if (CCR_MI) goto rom_3942; // BMI.B	$3942
	DEF_ROMLOC(38E4): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(38E6): move_toreg_8(read_8(0xFFFFFE10), &D0); // MOVE.B	$FE10,D0
	DEF_ROMLOC(38EA): cmp_tomem_16(0x103, 0xFFFFFE10); // CMPI.W	#$0103,$FE10
	DEF_ROMLOC(38F0): if (!CCR_EQ) goto rom_38F4; // BNE.B	$38F4
	DEF_ROMLOC(38F2): move_toreg_32(0x5, &D0); // MOVEQ.L	$05,D0
	rom_38F4(); // Detected flow into next function
}*/
/*ROMFUNC(rom_38F4) {
	DEF_ROMLOC(38F4): cmp_tomem_16(0x502, 0xFFFFFE10); // CMPI.W	#$0502,$FE10
	DEF_ROMLOC(38FA): if (!CCR_EQ) goto rom_38FE; // BNE.B	$38FE
	DEF_ROMLOC(38FC): move_toreg_32(0x6, &D0); // MOVEQ.L	$06,D0
	rom_38FE(); // Detected flow into next function
}*/
/*ROMFUNC(rom_38FE) {
	DEF_ROMLOC(38FE): move_toreg_32(0x3796, &A1); // LEA.L	$00003796,A1
	DEF_ROMLOC(3904): move_toreg_8(read_8((s32)A1 + (s8)0x0 + (s16)D0), &D0); // MOVE.B	0(A1,D0),D0
	DEF_ROMLOC(3908): rom_138E(); // BSR.W	$138E
	DEF_ROMLOC(390C): move_tomem_8(0x34, 0xFFFFD080); // MOVE.B	#$34,$D080
	rom_3912(); // Detected flow into next function
}*/
/*ROMFUNC(rom_3912) {
	DEF_ROMLOC(3912): move_tomem_8(0xC, 0xFFFFF62A); // MOVE.B	#$0C,$F62A
	DEF_ROMLOC(3918): rom_29A0(); // BSR.W	$29A0
	DEF_ROMLOC(391C): rom_D9C6(); // JSR	$0000D9C6
	DEF_ROMLOC(3922): rom_DCEC(); // JSR	$0000DCEC
	DEF_ROMLOC(3928): rom_15E4(); // BSR.W	$15E4
	DEF_ROMLOC(392C): move_toreg_16(read_16(0xFFFFD108), &D0); // MOVE.W	$D108,D0
	DEF_ROMLOC(3930): cmp_toreg_16(read_16(0xFFFFD130), &D0); // CMP.W	$D130,D0
	DEF_ROMLOC(3934): if (!CCR_EQ) goto rom_3912; // BNE.B	$3912
	DEF_ROMLOC(3936): tst_mem_32(0xFFFFF680); // TST.L	$F680
	DEF_ROMLOC(393A): if (!CCR_EQ) goto rom_3912; // BNE.B	$3912
	DEF_ROMLOC(393C): rom_1CFEE(); // JSR	$0001CFEE
	rom_3942(); // Detected flow into next function
}*/
/*ROMFUNC(rom_3942) {
	DEF_ROMLOC(3942): move_toreg_32(0x3, &D0); // MOVEQ.L	$03,D0
	DEF_ROMLOC(3944): rom_20F4(); // BSR.W	$20F4
	DEF_ROMLOC(3948): rom_5ECC(); // BSR.W	$5ECC
	DEF_ROMLOC(394C): rom_626E(); // BSR.W	$626E
	DEF_ROMLOC(3950): bset_tomem_8(0x2, 0xFFFFF754); // BSET.B	#$02,$F754
	DEF_ROMLOC(3956): rom_72F0(); // BSR.W	$72F0
	DEF_ROMLOC(395A): rom_71AC(); // BSR.W	$71AC
	DEF_ROMLOC(395E): rom_153B4(); // JSR	$000153B4
	DEF_ROMLOC(3964): rom_40F2(); // BSR.W	$40F2
	DEF_ROMLOC(3968): rom_3BCC(); // BSR.W	$3BCC
	DEF_ROMLOC(396C): move_tomem_8(0x1, 0xFFFFD000); // MOVE.B	#$01,$D000
	DEF_ROMLOC(3972): tst_mem_16(0xFFFFFFF0); // TST.W	$FFF0
	DEF_ROMLOC(3976): if (CCR_MI) goto rom_397E; // BMI.B	$397E
	DEF_ROMLOC(3978): move_tomem_8(0x21, 0xFFFFD040); // MOVE.B	#$21,$D040
	rom_397E(); // Detected flow into next function
}*/
/*ROMFUNC(rom_397E) {
	DEF_ROMLOC(397E): tst_mem_8(0xFFFFFFE2); // TST.B	$FFE2
	DEF_ROMLOC(3982): if (CCR_EQ) goto rom_3992; // BEQ.B	$3992
	DEF_ROMLOC(3984): btst_tomem_8(0x6, 0xFFFFF604); // BTST.B	#$06,$F604
	DEF_ROMLOC(398A): if (CCR_EQ) goto rom_3992; // BEQ.B	$3992
	DEF_ROMLOC(398C): move_tomem_8(0x1, 0xFFFFFFFA); // MOVE.B	#$01,$FFFA
	rom_3992(); // Detected flow into next function
}*/
/*ROMFUNC(rom_3992) {
	DEF_ROMLOC(3992): move_tomem_16(0x0, 0xFFFFF602); // MOVE.W	#$0000,$F602
	DEF_ROMLOC(3998): move_tomem_16(0x0, 0xFFFFF604); // MOVE.W	#$0000,$F604
	DEF_ROMLOC(399E): cmp_tomem_8(0x1, 0xFFFFFE10); // CMPI.B	#$01,$FE10
	DEF_ROMLOC(39A4): if (!CCR_EQ) goto rom_39BE; // BNE.B	$39BE
	DEF_ROMLOC(39A6): move_tomem_8(0x1B, 0xFFFFD780); // MOVE.B	#$1B,$D780
	DEF_ROMLOC(39AC): move_tomem_16(0x60, 0xFFFFD788); // MOVE.W	#$0060,$D788
	DEF_ROMLOC(39B2): move_tomem_8(0x1B, 0xFFFFD7C0); // MOVE.B	#$1B,$D7C0
	DEF_ROMLOC(39B8): move_tomem_16(0x120, 0xFFFFD7C8); // MOVE.W	#$0120,$D7C8
	rom_39BE(); // Detected flow into next function
}*/
/*ROMFUNC(rom_39BE) {
	DEF_ROMLOC(39BE): rom_DF68(); // JSR	$0000DF68
	DEF_ROMLOC(39C4): rom_D9C6(); // JSR	$0000D9C6
	DEF_ROMLOC(39CA): rom_DCEC(); // JSR	$0000DCEC
	DEF_ROMLOC(39D0): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(39D2): tst_mem_8(0xFFFFFE30); // TST.B	$FE30
	DEF_ROMLOC(39D6): if (!CCR_EQ) goto rom_39E4; // BNE.B	$39E4
	DEF_ROMLOC(39D8): move_tomem_16(D0, 0xFFFFFE20); // MOVE.W	D0,$FE20
	DEF_ROMLOC(39DC): move_tomem_32(D0, 0xFFFFFE22); // MOVE.L	D0,$FE22
	DEF_ROMLOC(39E0): move_tomem_8(D0, 0xFFFFFE1B); // MOVE.B	D0,$FE1B
	rom_39E4(); // Detected flow into next function
}*/
/*ROMFUNC(rom_39E4) {
	DEF_ROMLOC(39E4): move_tomem_8(D0, 0xFFFFFE1A); // MOVE.B	D0,$FE1A
	DEF_ROMLOC(39E8): move_tomem_8(D0, 0xFFFFFE2C); // MOVE.B	D0,$FE2C
	DEF_ROMLOC(39EC): move_tomem_8(D0, 0xFFFFFE2D); // MOVE.B	D0,$FE2D
	DEF_ROMLOC(39F0): move_tomem_8(D0, 0xFFFFFE2E); // MOVE.B	D0,$FE2E
	DEF_ROMLOC(39F4): move_tomem_8(D0, 0xFFFFFE2F); // MOVE.B	D0,$FE2F
	DEF_ROMLOC(39F8): move_tomem_16(D0, 0xFFFFFE08); // MOVE.W	D0,$FE08
	DEF_ROMLOC(39FC): move_tomem_16(D0, 0xFFFFFE02); // MOVE.W	D0,$FE02
	DEF_ROMLOC(3A00): move_tomem_16(D0, 0xFFFFFE04); // MOVE.W	D0,$FE04
	DEF_ROMLOC(3A04): rom_411A(); // BSR.W	$411A
	DEF_ROMLOC(3A08): move_tomem_8(0x1, 0xFFFFFE1F); // MOVE.B	#$01,$FE1F
	DEF_ROMLOC(3A0E): move_tomem_8(0x1, 0xFFFFFE1D); // MOVE.B	#$01,$FE1D
	DEF_ROMLOC(3A14): move_tomem_8(0x1, 0xFFFFFE1E); // MOVE.B	#$01,$FE1E
	DEF_ROMLOC(3A1A): move_tomem_16(0x0, 0xFFFFF790); // MOVE.W	#$0000,$F790
	DEF_ROMLOC(3A20): move_toreg_32(0x4082, &A1); // LEA.L	$00004082,A1
	DEF_ROMLOC(3A26): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(3A28): move_toreg_8(read_8(0xFFFFFE10), &D0); // MOVE.B	$FE10,D0
	DEF_ROMLOC(3A2C): lsl_toreg_16(0x2, &D0); // LSL.W	#$02,D0
	DEF_ROMLOC(3A2E): move_toreg_32(read_32((s32)A1 + (s8)0x0 + (s16)D0), &A1); // MOVEA.L	0(A1,D0),A1
	DEF_ROMLOC(3A32): tst_mem_16(0xFFFFFFF0); // TST.W	$FFF0
	DEF_ROMLOC(3A36): if (CCR_PL) goto rom_3A4A; // BPL.B	$3A4A
	DEF_ROMLOC(3A38): move_toreg_32(0x40A2, &A1); // LEA.L	$000040A2,A1
	DEF_ROMLOC(3A3E): move_toreg_16(read_16(0xFFFFFFF4), &D0); // MOVE.W	$FFF4,D0
	DEF_ROMLOC(3A42): sub_toreg_16(0x1, &D0); // SUBQ.W	#$01,D0
	DEF_ROMLOC(3A44): lsl_toreg_16(0x2, &D0); // LSL.W	#$02,D0
	DEF_ROMLOC(3A46): move_toreg_32(read_32((s32)A1 + (s8)0x0 + (s16)D0), &A1); // MOVEA.L	0(A1,D0),A1
	rom_3A4A(); // Detected flow into next function
}*/
/*ROMFUNC(rom_3A4A) {
	DEF_ROMLOC(3A4A): move_tomem_8(read_8(A1 + 0x1), 0xFFFFF792); // MOVE.B	1(A1),$F792
	DEF_ROMLOC(3A50): sub_tomem_8(0x1, 0xFFFFF792); // SUBQ.B	#$01,$F792
	DEF_ROMLOC(3A54): move_tomem_16(0x708, 0xFFFFF614); // MOVE.W	#$0708,$F614
	DEF_ROMLOC(3A5A): tst_mem_16(0xFFFFFFF0); // TST.W	$FFF0
	DEF_ROMLOC(3A5E): if (CCR_PL) goto rom_3A74; // BPL.B	$3A74
	DEF_ROMLOC(3A60): move_tomem_16(0x21C, 0xFFFFF614); // MOVE.W	#$021C,$F614
	DEF_ROMLOC(3A66): cmp_tomem_16(0x4, 0xFFFFFFF4); // CMPI.W	#$0004,$FFF4
	DEF_ROMLOC(3A6C): if (!CCR_EQ) goto rom_3A74; // BNE.B	$3A74
	DEF_ROMLOC(3A6E): move_tomem_16(0x1FE, 0xFFFFF614); // MOVE.W	#$01FE,$F614
	rom_3A74(); // Detected flow into next function
}*/
/*ROMFUNC(rom_3A74) {
	DEF_ROMLOC(3A74): cmp_tomem_8(0x1, 0xFFFFFE10); // CMPI.B	#$01,$FE10
	DEF_ROMLOC(3A7A): if (!CCR_EQ) goto rom_3A8C; // BNE.B	$3A8C
	DEF_ROMLOC(3A7C): move_toreg_32(0xB, &D0); // MOVEQ.L	$0B,D0
	DEF_ROMLOC(3A7E): cmp_tomem_8(0x3, 0xFFFFFE11); // CMPI.B	#$03,$FE11
	DEF_ROMLOC(3A84): if (!CCR_EQ) goto rom_3A88; // BNE.B	$3A88
	DEF_ROMLOC(3A86): move_toreg_32(0xD, &D0); // MOVEQ.L	$0D,D0
	rom_3A88(); // Detected flow into next function
}*/
/*ROMFUNC(rom_3A88) {
	DEF_ROMLOC(3A88): rom_2144(); // BSR.W	$2144
	rom_3A8C(); // Detected flow into next function
}*/
/*ROMFUNC(rom_3A8C) {
	DEF_ROMLOC(3A8C): move_toreg_16(0x3, &D1); // MOVE.W	#$0003,D1
	rom_3A90(); // Detected flow into next function
}*/
/*ROMFUNC(rom_3A90) {
	DEF_ROMLOC(3A90): move_tomem_8(0x8, 0xFFFFF62A); // MOVE.B	#$08,$F62A
	DEF_ROMLOC(3A96): rom_29A0(); // BSR.W	$29A0
	DEF_ROMLOC(3A9A): dec_reg_16(&D1); if ((D1 & 0xffff) != 0xffff) goto rom_3A90; // DBF.W	D1,$3A90
	DEF_ROMLOC(3A9E): move_tomem_16(0x202F, 0xFFFFF626); // MOVE.W	#$202F,$F626
	DEF_ROMLOC(3AA4): rom_1DAA(); // BSR.W	$1DAA
	DEF_ROMLOC(3AA8): tst_mem_16(0xFFFFFFF0); // TST.W	$FFF0
	DEF_ROMLOC(3AAC): if (CCR_MI) goto rom_3AC0; // BMI.B	$3AC0
	DEF_ROMLOC(3AAE): add_tomem_8(0x2, 0xFFFFD0A4); // ADDQ.B	#$02,$D0A4
	DEF_ROMLOC(3AB2): add_tomem_8(0x4, 0xFFFFD0E4); // ADDQ.B	#$04,$D0E4
	DEF_ROMLOC(3AB6): add_tomem_8(0x4, 0xFFFFD124); // ADDQ.B	#$04,$D124
	DEF_ROMLOC(3ABA): add_tomem_8(0x4, 0xFFFFD164); // ADDQ.B	#$04,$D164
	rom_3AD8(); // BRA.B	$3AD8
}*/
/*ROMFUNC(rom_3AC0) {
	DEF_ROMLOC(3AC0): move_toreg_32(0x2, &D0); // MOVEQ.L	$02,D0
	DEF_ROMLOC(3AC2): rom_1578(); // JSR	$00001578
	DEF_ROMLOC(3AC8): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(3ACA): move_toreg_8(read_8(0xFFFFFE10), &D0); // MOVE.B	$FE10,D0
	DEF_ROMLOC(3ACE): add_toreg_16(0x15, &D0); // ADDI.W	#$0015,D0
	DEF_ROMLOC(3AD2): rom_1578(); // JSR	$00001578
	rom_3AD8(); // Detected flow into next function
}*/
/*ROMFUNC(rom_3AD8) {
	DEF_ROMLOC(3AD8): bclr_tomem_8(0x7, 0xFFFFF600); // BCLR.B	#$07,$F600
	rom_3ADE(); // Detected flow into next function
}*/
/*ROMFUNC(rom_3ADE) {
	DEF_ROMLOC(3ADE): rom_13A0(); // BSR.W	$13A0
	DEF_ROMLOC(3AE2): move_tomem_8(0x8, 0xFFFFF62A); // MOVE.B	#$08,$F62A
	DEF_ROMLOC(3AE8): rom_29A0(); // BSR.W	$29A0
	DEF_ROMLOC(3AEC): add_tomem_16(0x1, 0xFFFFFE04); // ADDQ.W	#$01,$FE04
	DEF_ROMLOC(3AF0): rom_3FD2(); // BSR.W	$3FD2
	DEF_ROMLOC(3AF4): rom_3BCC(); // BSR.W	$3BCC
	DEF_ROMLOC(3AF8): rom_D9C6(); // JSR	$0000D9C6
	DEF_ROMLOC(3AFE): tst_mem_16(0xFFFFFE02); // TST.W	$FE02
	DEF_ROMLOC(3B02): if (!CCR_EQ) goto rom_379E; // BNE.W	$379E
	DEF_ROMLOC(3B06): tst_mem_16(0xFFFFFE08); // TST.W	$FE08
	DEF_ROMLOC(3B0A): if (!CCR_EQ) goto rom_3B14; // BNE.B	$3B14
	DEF_ROMLOC(3B0C): cmp_tomem_8(0x6, 0xFFFFD024); // CMPI.B	#$06,$D024
	DEF_ROMLOC(3B12): if (CCR_CC) goto rom_3B18; // BCC.B	$3B18
	rom_3B14(); // Detected flow into next function
}*/
/*ROMFUNC(rom_3B14) {
	DEF_ROMLOC(3B14): rom_626E(); // BSR.W	$626E
	rom_3B18(); // Detected flow into next function
}*/
/*ROMFUNC(rom_3B18) {
	DEF_ROMLOC(3B18): rom_DCEC(); // JSR	$0000DCEC
	DEF_ROMLOC(3B1E): rom_DF68(); // JSR	$0000DF68
	DEF_ROMLOC(3B24): rom_1934(); // BSR.W	$1934
	DEF_ROMLOC(3B28): rom_15E4(); // BSR.W	$15E4
	DEF_ROMLOC(3B2C): rom_4170(); // BSR.W	$4170
	DEF_ROMLOC(3B30): rom_4208(); // BSR.W	$4208
	DEF_ROMLOC(3B34): rom_4276(); // BSR.W	$4276
	DEF_ROMLOC(3B38): cmp_tomem_8(0x8, 0xFFFFF600); // CMPI.B	#$08,$F600
	DEF_ROMLOC(3B3E): if (CCR_EQ) goto rom_3B4C; // BEQ.B	$3B4C
	DEF_ROMLOC(3B40): cmp_tomem_8(0xC, 0xFFFFF600); // CMPI.B	#$0C,$F600
	DEF_ROMLOC(3B46): if (CCR_EQ) goto rom_3ADE; // BEQ.W	$3ADE
	DEF_ROMLOC(3B4A): return; // RTS
}*/
/*ROMFUNC(rom_3B4C) {
	DEF_ROMLOC(3B4C): tst_mem_16(0xFFFFFE02); // TST.W	$FE02
	DEF_ROMLOC(3B50): if (!CCR_EQ) goto rom_3B6A; // BNE.B	$3B6A
	DEF_ROMLOC(3B52): tst_mem_16(0xFFFFF614); // TST.W	$F614
	DEF_ROMLOC(3B56): if (CCR_EQ) goto rom_3B6A; // BEQ.B	$3B6A
	DEF_ROMLOC(3B58): cmp_tomem_8(0x8, 0xFFFFF600); // CMPI.B	#$08,$F600
	DEF_ROMLOC(3B5E): if (CCR_EQ) goto rom_3ADE; // BEQ.W	$3ADE
	DEF_ROMLOC(3B62): move_tomem_8(0x0, 0xFFFFF600); // MOVE.B	#$00,$F600
	DEF_ROMLOC(3B68): return; // RTS
}*/
/*ROMFUNC(rom_3B6A) {
	DEF_ROMLOC(3B6A): cmp_tomem_8(0x8, 0xFFFFF600); // CMPI.B	#$08,$F600
	DEF_ROMLOC(3B70): if (!CCR_EQ) goto rom_3B84; // BNE.B	$3B84
	DEF_ROMLOC(3B72): move_tomem_8(0x0, 0xFFFFF600); // MOVE.B	#$00,$F600
	DEF_ROMLOC(3B78): tst_mem_16(0xFFFFFFF0); // TST.W	$FFF0
	DEF_ROMLOC(3B7C): if (CCR_PL) goto rom_3B84; // BPL.B	$3B84
	DEF_ROMLOC(3B7E): move_tomem_8(0x1C, 0xFFFFF600); // MOVE.B	#$1C,$F600
	rom_3B84(); // Detected flow into next function
}*/
/*ROMFUNC(rom_3B84) {
	DEF_ROMLOC(3B84): move_tomem_16(0x3C, 0xFFFFF614); // MOVE.W	#$003C,$F614
	DEF_ROMLOC(3B8A): move_tomem_16(0x3F, 0xFFFFF626); // MOVE.W	#$003F,$F626
	DEF_ROMLOC(3B90): clr_mem_16(0xFFFFF794); // CLR.W	$F794
	rom_3B94(); // Detected flow into next function
}*/
/*ROMFUNC(rom_3B94) {
	DEF_ROMLOC(3B94): move_tomem_8(0x8, 0xFFFFF62A); // MOVE.B	#$08,$F62A
	DEF_ROMLOC(3B9A): rom_29A0(); // BSR.W	$29A0
	DEF_ROMLOC(3B9E): rom_3FD2(); // BSR.W	$3FD2
	DEF_ROMLOC(3BA2): rom_D9C6(); // JSR	$0000D9C6
	DEF_ROMLOC(3BA8): rom_DCEC(); // JSR	$0000DCEC
	DEF_ROMLOC(3BAE): rom_DF68(); // JSR	$0000DF68
	DEF_ROMLOC(3BB4): sub_tomem_16(0x1, 0xFFFFF794); // SUBQ.W	#$01,$F794
	DEF_ROMLOC(3BB8): if (CCR_PL) goto rom_3BC4; // BPL.B	$3BC4
	DEF_ROMLOC(3BBA): move_tomem_16(0x2, 0xFFFFF794); // MOVE.W	#$0002,$F794
	DEF_ROMLOC(3BC0): rom_1E6A(); // BSR.W	$1E6A
	rom_3BC4(); // Detected flow into next function
}*/
/*ROMFUNC(rom_3BC4) {
	DEF_ROMLOC(3BC4): tst_mem_16(0xFFFFF614); // TST.W	$F614
	DEF_ROMLOC(3BC8): if (!CCR_EQ) goto rom_3B94; // BNE.B	$3B94
	DEF_ROMLOC(3BCA): return; // RTS
}*/
/*ROMFUNC(rom_3FCA) {
	DEF_ROMLOC(3FCA): and_toreg_8(0x4C, &D7); // ANDI.B	#$4C,D7
	rom_3FD2(); // Detected flow into next function
}*/