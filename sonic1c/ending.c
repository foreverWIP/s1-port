// #define CHECK_STUFF(loc) 1
#include "opcodes.h"
#include "system.h"

/*ROMFUNC(rom_50F2) {
	DEF_ROMLOC(50F2): move_toreg_8(0xFFFFFFE4, &D0); // MOVE.B	#$E4,D0
	DEF_ROMLOC(50F6): rom_1394(); // BSR.W	$1394
	DEF_ROMLOC(50FA): rom_1E4A(); // BSR.W	$1E4A
	DEF_ROMLOC(50FE): move_toreg_32(0xFFFFD000, &A1); // LEA.L	$D000,A1
	DEF_ROMLOC(5102): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(5104): move_toreg_16(0x7FF, &D1); // MOVE.W	#$07FF,D1
	DEF_ROMLOC(5108): move_tomem_32(D0, (A1 += 4, A1 - 4)); // MOVE.L	D0,(A1)+
	DEF_ROMLOC(510A): dec_reg_16(&D1); if ((D1 & 0xffff) != 0xffff) goto rom_5108; // DBF.W	D1,$5108
	DEF_ROMLOC(510E): move_toreg_32(0xFFFFF628, &A1); // LEA.L	$F628,A1
	DEF_ROMLOC(5112): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(5114): move_toreg_16(0x15, &D1); // MOVE.W	#$0015,D1
	DEF_ROMLOC(5118): move_tomem_32(D0, (A1 += 4, A1 - 4)); // MOVE.L	D0,(A1)+
	DEF_ROMLOC(511A): dec_reg_16(&D1); if ((D1 & 0xffff) != 0xffff) goto rom_5118; // DBF.W	D1,$5118
	DEF_ROMLOC(511E): move_toreg_32(0xFFFFF700, &A1); // LEA.L	$F700,A1
	DEF_ROMLOC(5122): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(5124): move_toreg_16(0x3F, &D1); // MOVE.W	#$003F,D1
	DEF_ROMLOC(5128): move_tomem_32(D0, (A1 += 4, A1 - 4)); // MOVE.L	D0,(A1)+
	DEF_ROMLOC(512A): dec_reg_16(&D1); if ((D1 & 0xffff) != 0xffff) goto rom_5128; // DBF.W	D1,$5128
	DEF_ROMLOC(512E): move_toreg_32(0xFFFFFE60, &A1); // LEA.L	$FE60,A1
	DEF_ROMLOC(5132): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(5134): move_toreg_16(0x47, &D1); // MOVE.W	#$0047,D1
	DEF_ROMLOC(5138): move_tomem_32(D0, (A1 += 4, A1 - 4)); // MOVE.L	D0,(A1)+
	DEF_ROMLOC(513A): dec_reg_16(&D1); if ((D1 & 0xffff) != 0xffff) goto rom_5138; // DBF.W	D1,$5138
	DEF_ROMLOC(513E): move_tosr_16(0x2700, &SR); // MOVE.W	#$2700,SR
	DEF_ROMLOC(5142): move_toreg_16(read_16(0xFFFFF60C), &D0); // MOVE.W	$F60C,D0
	DEF_ROMLOC(5146): and_toreg_8(0xFFFFFFBF, &D0); // ANDI.B	#$BF,D0
	DEF_ROMLOC(514A): move_tomem_16(D0, 0xC00004); // MOVE.W	D0,$00C00004
	DEF_ROMLOC(5150): rom_12C4(); // BSR.W	$12C4
	DEF_ROMLOC(5154): move_toreg_32(0xC00004, &A6); // LEA.L	$00C00004,A6
	DEF_ROMLOC(515A): move_tomem_16(0xFFFF8B03, A6); // MOVE.W	#$8B03,(A6)
	DEF_ROMLOC(515E): move_tomem_16(0xFFFF8230, A6); // MOVE.W	#$8230,(A6)
	DEF_ROMLOC(5162): move_tomem_16(0xFFFF8407, A6); // MOVE.W	#$8407,(A6)
	DEF_ROMLOC(5166): move_tomem_16(0xFFFF857C, A6); // MOVE.W	#$857C,(A6)
	DEF_ROMLOC(516A): move_tomem_16(0xFFFF9001, A6); // MOVE.W	#$9001,(A6)
	DEF_ROMLOC(516E): move_tomem_16(0xFFFF8004, A6); // MOVE.W	#$8004,(A6)
	DEF_ROMLOC(5172): move_tomem_16(0xFFFF8720, A6); // MOVE.W	#$8720,(A6)
	DEF_ROMLOC(5176): move_tomem_16(0xFFFF8ADF, 0xFFFFF624); // MOVE.W	#$8ADF,$F624
	DEF_ROMLOC(517C): move_tomem_16(read_16(0xFFFFF624), A6); // MOVE.W	$F624,(A6)
	DEF_ROMLOC(5180): move_tomem_16(0x1E, 0xFFFFFE14); // MOVE.W	#$001E,$FE14
	DEF_ROMLOC(5186): move_tomem_16(0x600, 0xFFFFFE10); // MOVE.W	#$0600,$FE10
	DEF_ROMLOC(518C): cmp_tomem_8(0x6, 0xFFFFFE57); // CMPI.B	#$06,$FE57
	DEF_ROMLOC(5192): if (CCR_EQ) goto rom_519A; // BEQ.B	$519A
	DEF_ROMLOC(5194): move_tomem_16(0x601, 0xFFFFFE10); // MOVE.W	#$0601,$FE10
	rom_519A(); // Detected flow into next function
}*/
/*ROMFUNC(rom_519A) {
	DEF_ROMLOC(519A): move_toreg_32(0x1C, &D0); // MOVEQ.L	$1C,D0
	DEF_ROMLOC(519C): rom_16E4(); // BSR.W	$16E4
	DEF_ROMLOC(51A0): rom_1CFEE(); // JSR	$0001CFEE
	DEF_ROMLOC(51A6): rom_5ECC(); // BSR.W	$5ECC
	DEF_ROMLOC(51AA): rom_626E(); // BSR.W	$626E
	DEF_ROMLOC(51AE): bset_tomem_8(0x2, 0xFFFFF754); // BSET.B	#$02,$F754
	DEF_ROMLOC(51B4): rom_72F0(); // BSR.W	$72F0
	DEF_ROMLOC(51B8): rom_71AC(); // BSR.W	$71AC
	DEF_ROMLOC(51BC): move_tomem_32(0x64A00, 0xFFFFF796); // MOVE.L	#$00064A00,$F796
	DEF_ROMLOC(51C4): move_tosr_16(0x2300, &SR); // MOVE.W	#$2300,SR
	DEF_ROMLOC(51C8): move_toreg_32(0x61822, &A0); // LEA.L	$00061822,A0
	DEF_ROMLOC(51CE): move_toreg_32(0xFFFF9400, &A1); // LEA.L	$9400,A1
	DEF_ROMLOC(51D2): rom_1894(); // BSR.W	$1894
	DEF_ROMLOC(51D6): move_toreg_32(0x3, &D0); // MOVEQ.L	$03,D0
	DEF_ROMLOC(51D8): rom_20F4(); // BSR.W	$20F4
	DEF_ROMLOC(51DC): move_toreg_16(0x8B, &D0); // MOVE.W	#$008B,D0
	DEF_ROMLOC(51E0): rom_138E(); // BSR.W	$138E
	DEF_ROMLOC(51E4): btst_tomem_8(0x6, 0xFFFFF604); // BTST.B	#$06,$F604
	DEF_ROMLOC(51EA): if (CCR_EQ) goto rom_51F2; // BEQ.B	$51F2
	DEF_ROMLOC(51EC): move_tomem_8(0x1, 0xFFFFFFFA); // MOVE.B	#$01,$FFFA
	rom_51F2(); // Detected flow into next function
}*/
/*ROMFUNC(rom_51F2) {
	DEF_ROMLOC(51F2): move_tomem_8(0x1, 0xFFFFD000); // MOVE.B	#$01,$D000
	DEF_ROMLOC(51F8): bset_tomem_8(0x0, 0xFFFFD022); // BSET.B	#$00,$D022
	DEF_ROMLOC(51FE): move_tomem_8(0x1, 0xFFFFF7CC); // MOVE.B	#$01,$F7CC
	DEF_ROMLOC(5204): move_tomem_16(0x400, 0xFFFFF602); // MOVE.W	#$0400,$F602
	DEF_ROMLOC(520A): move_tomem_16(0xFFFFF800, 0xFFFFD014); // MOVE.W	#$F800,$D014
	DEF_ROMLOC(5210): move_tomem_8(0x21, 0xFFFFD040); // MOVE.B	#$21,$D040
	DEF_ROMLOC(5216): rom_DF68(); // JSR	$0000DF68
	DEF_ROMLOC(521C): rom_D9C6(); // JSR	$0000D9C6
	DEF_ROMLOC(5222): rom_DCEC(); // JSR	$0000DCEC
	DEF_ROMLOC(5228): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(522A): move_tomem_16(D0, 0xFFFFFE20); // MOVE.W	D0,$FE20
	DEF_ROMLOC(522E): move_tomem_32(D0, 0xFFFFFE22); // MOVE.L	D0,$FE22
	DEF_ROMLOC(5232): move_tomem_8(D0, 0xFFFFFE1B); // MOVE.B	D0,$FE1B
	DEF_ROMLOC(5236): move_tomem_8(D0, 0xFFFFFE2C); // MOVE.B	D0,$FE2C
	DEF_ROMLOC(523A): move_tomem_8(D0, 0xFFFFFE2D); // MOVE.B	D0,$FE2D
	DEF_ROMLOC(523E): move_tomem_8(D0, 0xFFFFFE2E); // MOVE.B	D0,$FE2E
	DEF_ROMLOC(5242): move_tomem_8(D0, 0xFFFFFE2F); // MOVE.B	D0,$FE2F
	DEF_ROMLOC(5246): move_tomem_16(D0, 0xFFFFFE08); // MOVE.W	D0,$FE08
	DEF_ROMLOC(524A): move_tomem_16(D0, 0xFFFFFE02); // MOVE.W	D0,$FE02
	DEF_ROMLOC(524E): move_tomem_16(D0, 0xFFFFFE04); // MOVE.W	D0,$FE04
	DEF_ROMLOC(5252): rom_411A(); // BSR.W	$411A
	DEF_ROMLOC(5256): move_tomem_8(0x1, 0xFFFFFE1F); // MOVE.B	#$01,$FE1F
	DEF_ROMLOC(525C): move_tomem_8(0x1, 0xFFFFFE1D); // MOVE.B	#$01,$FE1D
	DEF_ROMLOC(5262): move_tomem_8(0x0, 0xFFFFFE1E); // MOVE.B	#$00,$FE1E
	DEF_ROMLOC(5268): move_tomem_16(0x708, 0xFFFFF614); // MOVE.W	#$0708,$F614
	DEF_ROMLOC(526E): move_tomem_8(0x18, 0xFFFFF62A); // MOVE.B	#$18,$F62A
	DEF_ROMLOC(5274): rom_29A0(); // BSR.W	$29A0
	DEF_ROMLOC(5278): move_toreg_16(read_16(0xFFFFF60C), &D0); // MOVE.W	$F60C,D0
	DEF_ROMLOC(527C): or_toreg_8(0x40, &D0); // ORI.B	#$40,D0
	DEF_ROMLOC(5280): move_tomem_16(D0, 0xC00004); // MOVE.W	D0,$00C00004
	DEF_ROMLOC(5286): move_tomem_16(0x3F, 0xFFFFF626); // MOVE.W	#$003F,$F626
	DEF_ROMLOC(528C): rom_1DA4(); // BSR.W	$1DA4
	rom_5290(); // Detected flow into next function
}*/
/*ROMFUNC(rom_5290) {
	DEF_ROMLOC(5290): rom_13A0(); // BSR.W	$13A0
	DEF_ROMLOC(5294): move_tomem_8(0x18, 0xFFFFF62A); // MOVE.B	#$18,$F62A
	DEF_ROMLOC(529A): rom_29A0(); // BSR.W	$29A0
	DEF_ROMLOC(529E): add_tomem_16(0x1, 0xFFFFFE04); // ADDQ.W	#$01,$FE04
	DEF_ROMLOC(52A2): rom_537C(); // BSR.W	$537C
	DEF_ROMLOC(52A6): rom_D9C6(); // JSR	$0000D9C6
	DEF_ROMLOC(52AC): rom_626E(); // BSR.W	$626E
	DEF_ROMLOC(52B0): rom_DCEC(); // JSR	$0000DCEC
	DEF_ROMLOC(52B6): rom_DF68(); // JSR	$0000DF68
	DEF_ROMLOC(52BC): rom_1934(); // BSR.W	$1934
	DEF_ROMLOC(52C0): rom_4170(); // BSR.W	$4170
	DEF_ROMLOC(52C4): rom_4208(); // BSR.W	$4208
	DEF_ROMLOC(52C8): cmp_tomem_8(0x18, 0xFFFFF600); // CMPI.B	#$18,$F600
	DEF_ROMLOC(52CE): if (CCR_EQ) goto rom_52E6; // BEQ.B	$52E6
	DEF_ROMLOC(52D0): move_tomem_8(0x1C, 0xFFFFF600); // MOVE.B	#$1C,$F600
	DEF_ROMLOC(52D6): move_toreg_8(0xFFFFFF91, &D0); // MOVE.B	#$91,D0
	DEF_ROMLOC(52DA): rom_1394(); // BSR.W	$1394
	DEF_ROMLOC(52DE): move_tomem_16(0x0, 0xFFFFFFF4); // MOVE.W	#$0000,$FFF4
	DEF_ROMLOC(52E4): return; // RTS
}*/
/*ROMFUNC(rom_52E6) {
	DEF_ROMLOC(52E6): tst_mem_16(0xFFFFFE02); // TST.W	$FE02
	DEF_ROMLOC(52EA): if (CCR_EQ) goto rom_5290; // BEQ.W	$5290
	DEF_ROMLOC(52EE): clr_mem_16(0xFFFFFE02); // CLR.W	$FE02
	DEF_ROMLOC(52F2): move_tomem_16(0x3F, 0xFFFFF626); // MOVE.W	#$003F,$F626
	DEF_ROMLOC(52F8): clr_mem_16(0xFFFFF794); // CLR.W	$F794
	rom_52FC(); // Detected flow into next function
}*/
/*ROMFUNC(rom_52FC) {
	DEF_ROMLOC(52FC): rom_13A0(); // BSR.W	$13A0
	DEF_ROMLOC(5300): move_tomem_8(0x18, 0xFFFFF62A); // MOVE.B	#$18,$F62A
	DEF_ROMLOC(5306): rom_29A0(); // BSR.W	$29A0
	DEF_ROMLOC(530A): add_tomem_16(0x1, 0xFFFFFE04); // ADDQ.W	#$01,$FE04
	DEF_ROMLOC(530E): rom_537C(); // BSR.W	$537C
	DEF_ROMLOC(5312): rom_D9C6(); // JSR	$0000D9C6
	DEF_ROMLOC(5318): rom_626E(); // BSR.W	$626E
	DEF_ROMLOC(531C): rom_DCEC(); // JSR	$0000DCEC
	DEF_ROMLOC(5322): rom_DF68(); // JSR	$0000DF68
	DEF_ROMLOC(5328): rom_4170(); // BSR.W	$4170
	DEF_ROMLOC(532C): rom_4208(); // BSR.W	$4208
	DEF_ROMLOC(5330): sub_tomem_16(0x1, 0xFFFFF794); // SUBQ.W	#$01,$F794
	DEF_ROMLOC(5334): if (CCR_PL) goto rom_5340; // BPL.B	$5340
	DEF_ROMLOC(5336): move_tomem_16(0x2, 0xFFFFF794); // MOVE.W	#$0002,$F794
	DEF_ROMLOC(533C): rom_1F94(); // BSR.W	$1F94
	rom_5340(); // Detected flow into next function
}*/
/*ROMFUNC(rom_5340) {
	DEF_ROMLOC(5340): tst_mem_16(0xFFFFFE02); // TST.W	$FE02
	DEF_ROMLOC(5344): if (CCR_EQ) goto rom_52FC; // BEQ.W	$52FC
	DEF_ROMLOC(5348): clr_mem_16(0xFFFFFE02); // CLR.W	$FE02
	DEF_ROMLOC(534C): move_tomem_16(0x2E2F, 0xFFFFA480); // MOVE.W	#$2E2F,$A480
	DEF_ROMLOC(5352): move_toreg_32(0xC00004, &A5); // LEA.L	$00C00004,A5
	DEF_ROMLOC(5358): move_toreg_32(0xC00000, &A6); // LEA.L	$00C00000,A6
	DEF_ROMLOC(535E): move_toreg_32(0xFFFFF700, &A3); // LEA.L	$F700,A3
	DEF_ROMLOC(5362): move_toreg_32(0xFFFFA400, &A4); // LEA.L	$A400,A4
	DEF_ROMLOC(5366): move_toreg_16(0x4000, &D2); // MOVE.W	#$4000,D2
	DEF_ROMLOC(536A): rom_71F8(); // BSR.W	$71F8
	DEF_ROMLOC(536E): move_toreg_32(0x13, &D0); // MOVEQ.L	$13,D0
	DEF_ROMLOC(5370): rom_20F4(); // BSR.W	$20F4
	DEF_ROMLOC(5374): rom_1EC8(); // BSR.W	$1EC8
	rom_5290(); // BRA.W	$5290
}*/
/*ROMFUNC(rom_537C) {
	DEF_ROMLOC(537C): move_toreg_8(read_8(0xFFFFF7D7), &D0); // MOVE.B	$F7D7,D0
	DEF_ROMLOC(5380): if (!CCR_EQ) goto rom_539C; // BNE.B	$539C
	DEF_ROMLOC(5382): cmp_tomem_16(0x90, 0xFFFFD008); // CMPI.W	#$0090,$D008
	DEF_ROMLOC(5388): if (CCR_CC) goto rom_53EC; // BCC.B	$53EC
	DEF_ROMLOC(538A): add_tomem_8(0x2, 0xFFFFF7D7); // ADDQ.B	#$02,$F7D7
	DEF_ROMLOC(538E): move_tomem_8(0x1, 0xFFFFF7CC); // MOVE.B	#$01,$F7CC
	DEF_ROMLOC(5394): move_tomem_16(0x800, 0xFFFFF602); // MOVE.W	#$0800,$F602
	DEF_ROMLOC(539A): return; // RTS
}*/
/*ROMFUNC(rom_539C) {
	DEF_ROMLOC(539C): sub_toreg_8(0x2, &D0); // SUBQ.B	#$02,D0
	DEF_ROMLOC(539E): if (!CCR_EQ) goto rom_53D4; // BNE.B	$53D4
	DEF_ROMLOC(53A0): cmp_tomem_16(0xA0, 0xFFFFD008); // CMPI.W	#$00A0,$D008
	DEF_ROMLOC(53A6): if (CCR_CS) goto rom_53EC; // BCS.B	$53EC
	DEF_ROMLOC(53A8): add_tomem_8(0x2, 0xFFFFF7D7); // ADDQ.B	#$02,$F7D7
	DEF_ROMLOC(53AC): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(53AE): move_tomem_8(D0, 0xFFFFF7CC); // MOVE.B	D0,$F7CC
	DEF_ROMLOC(53B2): move_tomem_16(D0, 0xFFFFF602); // MOVE.W	D0,$F602
	DEF_ROMLOC(53B6): move_tomem_16(D0, 0xFFFFD014); // MOVE.W	D0,$D014
	DEF_ROMLOC(53BA): move_tomem_8(0xFFFFFF81, 0xFFFFF7C8); // MOVE.B	#$81,$F7C8
	DEF_ROMLOC(53C0): move_tomem_8(0x3, 0xFFFFD01A); // MOVE.B	#$03,$D01A
	DEF_ROMLOC(53C6): move_tomem_16(0x505, 0xFFFFD01C); // MOVE.W	#$0505,$D01C
	DEF_ROMLOC(53CC): move_tomem_8(0x3, 0xFFFFD01E); // MOVE.B	#$03,$D01E
	DEF_ROMLOC(53D2): return; // RTS
}*/
/*ROMFUNC(rom_53D4) {
	DEF_ROMLOC(53D4): sub_toreg_8(0x2, &D0); // SUBQ.B	#$02,D0
	DEF_ROMLOC(53D6): if (!CCR_EQ) goto rom_53EC; // BNE.B	$53EC
	DEF_ROMLOC(53D8): add_tomem_8(0x2, 0xFFFFF7D7); // ADDQ.B	#$02,$F7D7
	DEF_ROMLOC(53DC): move_tomem_16(0xA0, 0xFFFFD008); // MOVE.W	#$00A0,$D008
	DEF_ROMLOC(53E2): move_tomem_8(0xFFFFFF87, 0xFFFFD000); // MOVE.B	#$87,$D000
	DEF_ROMLOC(53E8): clr_mem_16(0xFFFFD024); // CLR.W	$D024
	rom_53EC(); // Detected flow into next function
}*/
/*ROMFUNC(rom_53EC) {
	DEF_ROMLOC(53EC): return; // RTS
}*/
/*ROMFUNC(rom_53EE) {
	DEF_ROMLOC(53EE): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(53F0): move_toreg_8(read_8(A0 + 0x25), &D0); // MOVE.B	37(A0),D0
	DEF_ROMLOC(53F4): move_toreg_16(read_16(0x5402 + (s16)(D0 & 0xffff)), &D1); // MOVE.W	12(PC,D0),D1
	DEF_ROMLOC(53F8): rom_5402 + (s16)(D1 & 0xffff)(); // JSR	8(PC,D1)
	DEF_ROMLOC(53FC): goto rom_DC92; // JMP	$0000DC92
	DEF_ROMLOC(5402): or_tomem_8(0x58, A4); // ORI.B	#$58,(A4)
	rom_5416(); // Detected flow into next function
}*/
/*ROMFUNC(rom_5416) {
	DEF_ROMLOC(5416): cmp_tomem_8(0x6, 0xFFFFFE57); // CMPI.B	#$06,$FE57
	DEF_ROMLOC(541C): if (CCR_EQ) goto rom_542C; // BEQ.B	$542C
	DEF_ROMLOC(541E): add_tomem_8(0x10, A0 + 0x25); // ADDI.B	#$10,37(A0)
	DEF_ROMLOC(5424): move_tomem_16(0xD8, A0 + 0x30); // MOVE.W	#$00D8,48(A0)
	DEF_ROMLOC(542A): return; // RTS
}*/
/*ROMFUNC(rom_542C) {
	DEF_ROMLOC(542C): add_tomem_8(0x2, A0 + 0x25); // ADDQ.B	#$02,37(A0)
	DEF_ROMLOC(5430): move_tomem_32(0x568E, A0 + 0x4); // MOVE.L	#$0000568E,4(A0)
	DEF_ROMLOC(5438): move_tomem_16(0x3E1, A0 + 0x2); // MOVE.W	#$03E1,2(A0)
	DEF_ROMLOC(543E): move_tomem_8(0x4, A0 + 0x1); // MOVE.B	#$04,1(A0)
	DEF_ROMLOC(5444): clr_mem_8(A0 + 0x22); // CLR.B	34(A0)
	DEF_ROMLOC(5448): move_tomem_8(0x2, A0 + 0x18); // MOVE.B	#$02,24(A0)
	DEF_ROMLOC(544E): move_tomem_8(0x0, A0 + 0x1A); // MOVE.B	#$00,26(A0)
	DEF_ROMLOC(5454): move_tomem_16(0x50, A0 + 0x30); // MOVE.W	#$0050,48(A0)
	rom_545A(); // Detected flow into next function
}*/
/*ROMFUNC(rom_545A) {
	DEF_ROMLOC(545A): sub_tomem_16(0x1, A0 + 0x30); // SUBQ.W	#$01,48(A0)
	DEF_ROMLOC(545E): if (!CCR_EQ) goto rom_5470; // BNE.B	$5470
	DEF_ROMLOC(5460): add_tomem_8(0x2, A0 + 0x25); // ADDQ.B	#$02,37(A0)
	DEF_ROMLOC(5464): move_tomem_16(0x1, A0 + 0x1C); // MOVE.W	#$0001,28(A0)
	DEF_ROMLOC(546A): move_tomem_8(0xFFFFFF88, 0xFFFFD400); // MOVE.B	#$88,$D400
	rom_5470(); // Detected flow into next function
}*/
/*ROMFUNC(rom_5470) {
	DEF_ROMLOC(5470): return; // RTS
}*/
/*ROMFUNC(rom_5472) {
	DEF_ROMLOC(5472): cmp_tomem_16(0x2000, 0xFFD43C); // CMPI.W	#$2000,$00FFD43C
	DEF_ROMLOC(547A): if (!CCR_EQ) goto rom_548C; // BNE.B	$548C
	DEF_ROMLOC(547C): move_tomem_16(0x1, 0xFFFFFE02); // MOVE.W	#$0001,$FE02
	DEF_ROMLOC(5482): move_tomem_16(0x5A, A0 + 0x30); // MOVE.W	#$005A,48(A0)
	DEF_ROMLOC(5488): add_tomem_8(0x2, A0 + 0x25); // ADDQ.B	#$02,37(A0)
	rom_548C(); // Detected flow into next function
}*/
/*ROMFUNC(rom_548C) {
	DEF_ROMLOC(548C): return; // RTS
}*/
/*ROMFUNC(rom_548E) {
	DEF_ROMLOC(548E): sub_tomem_16(0x1, A0 + 0x30); // SUBQ.W	#$01,48(A0)
	DEF_ROMLOC(5492): if (!CCR_EQ) goto rom_54B8; // BNE.B	$54B8
	DEF_ROMLOC(5494): move_toreg_32(0xFFFFD400, &A1); // LEA.L	$D400,A1
	DEF_ROMLOC(5498): move_toreg_16(0xFF, &D1); // MOVE.W	#$00FF,D1
	rom_549C(); // Detected flow into next function
}*/
/*ROMFUNC(rom_549C) {
	DEF_ROMLOC(549C): clr_mem_32((A1 += 4, A1 - 4)); // CLR.L	(A1)+
	DEF_ROMLOC(549E): dec_reg_16(&D1); if ((D1 & 0xffff) != 0xffff) goto rom_549C; // DBF.W	D1,$549C
	DEF_ROMLOC(54A2): move_tomem_16(0x1, 0xFFFFFE02); // MOVE.W	#$0001,$FE02
	DEF_ROMLOC(54A8): add_tomem_8(0x2, A0 + 0x25); // ADDQ.B	#$02,37(A0)
	DEF_ROMLOC(54AC): move_tomem_8(0x1, A0 + 0x1C); // MOVE.B	#$01,28(A0)
	DEF_ROMLOC(54B2): move_tomem_16(0x3C, A0 + 0x30); // MOVE.W	#$003C,48(A0)
	rom_54B8(); // Detected flow into next function
}*/
/*ROMFUNC(rom_54B8) {
	DEF_ROMLOC(54B8): return; // RTS
}*/
/*ROMFUNC(rom_54BA) {
	DEF_ROMLOC(54BA): sub_tomem_16(0x1, A0 + 0x30); // SUBQ.W	#$01,48(A0)
	DEF_ROMLOC(54BE): if (!CCR_EQ) goto rom_54D6; // BNE.B	$54D6
	DEF_ROMLOC(54C0): add_tomem_8(0x2, A0 + 0x25); // ADDQ.B	#$02,37(A0)
	DEF_ROMLOC(54C4): move_tomem_16(0xB4, A0 + 0x30); // MOVE.W	#$00B4,48(A0)
	DEF_ROMLOC(54CA): move_tomem_8(0x2, A0 + 0x1C); // MOVE.B	#$02,28(A0)
	DEF_ROMLOC(54D0): move_tomem_8(0xFFFFFF89, 0xFFFFD400); // MOVE.B	#$89,$D400
	rom_54D6(); // Detected flow into next function
}*/
/*ROMFUNC(rom_54D6) {
	DEF_ROMLOC(54D6): return; // RTS
}*/
/*ROMFUNC(rom_54D8) {
	DEF_ROMLOC(54D8): move_toreg_32(0x5522, &A1); // LEA.L	$00005522,A1
	DEF_ROMLOC(54DE): goto rom_ADA2; // JMP	$0000ADA2
}*/
/*ROMFUNC(rom_54E4) {
	DEF_ROMLOC(54E4): sub_tomem_16(0x1, A0 + 0x30); // SUBQ.W	#$01,48(A0)
	DEF_ROMLOC(54E8): if (!CCR_EQ) goto rom_5520; // BNE.B	$5520
	DEF_ROMLOC(54EA): add_tomem_8(0x2, A0 + 0x25); // ADDQ.B	#$02,37(A0)
	DEF_ROMLOC(54EE): move_tomem_32(0x568E, A0 + 0x4); // MOVE.L	#$0000568E,4(A0)
	DEF_ROMLOC(54F6): move_tomem_16(0x3E1, A0 + 0x2); // MOVE.W	#$03E1,2(A0)
	DEF_ROMLOC(54FC): move_tomem_8(0x4, A0 + 0x1); // MOVE.B	#$04,1(A0)
	DEF_ROMLOC(5502): clr_mem_8(A0 + 0x22); // CLR.B	34(A0)
	DEF_ROMLOC(5506): move_tomem_8(0x2, A0 + 0x18); // MOVE.B	#$02,24(A0)
	DEF_ROMLOC(550C): move_tomem_8(0x5, A0 + 0x1A); // MOVE.B	#$05,26(A0)
	DEF_ROMLOC(5512): move_tomem_8(0x2, A0 + 0x1C); // MOVE.B	#$02,28(A0)
	DEF_ROMLOC(5518): move_tomem_8(0xFFFFFF89, 0xFFFFD400); // MOVE.B	#$89,$D400
	rom_54D8(); // BRA.B	$54D8
}*/
/*ROMFUNC(rom_5520) {
	DEF_ROMLOC(5520): return; // RTS
}*/
/*ROMFUNC(rom_5522) {
	DEF_ROMLOC(5522): or_toreg_8(0x14, &D6); // ORI.B	#$14,D6
	DEF_ROMLOC(5526): or_tomem_8(0x1, A6++); // ORI.B	#$01,(A6)+
	DEF_ROMLOC(552A): or_toreg_8(0x1, &D1); // ORI.B	#$01,D1
	DEF_ROMLOC(552E): or_toreg_8(0x1, &D1); // ORI.B	#$01,D1
	DEF_ROMLOC(5532): or_toreg_8(0xFFFFFFFA, &D1); // ORI.B	#$FA,D1
	DEF_ROMLOC(5536): btst_toreg_32(D2, &D3); // BTST.L	D2,D3
	DEF_ROMLOC(5538): sub_toreg_8(0x3, &D3); // SUBI.B	#$03,D3
	DEF_ROMLOC(553C): sub_toreg_8(0x0, &D3); // SUBI.B	#$00,D3
	DEF_ROMLOC(5540): btst_toreg_32(D1, &D5); // BTST.L	D1,D5
	DEF_ROMLOC(5542): btst_toreg_32(D2, &D5); // BTST.L	D2,D5
	DEF_ROMLOC(5544): add_toreg_8(0x1, &D7); // ADDI.B	#$01,D7
	rom_5548(); // Detected flow into next function
}*/
/*ROMFUNC(rom_5548) {
	DEF_ROMLOC(5548): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(554A): move_toreg_8(read_8(A0 + 0x24), &D0); // MOVE.B	36(A0),D0
	DEF_ROMLOC(554E): move_toreg_16(read_16(0x555C + (s16)(D0 & 0xffff)), &D1); // MOVE.W	12(PC,D0),D1
	DEF_ROMLOC(5552): rom_555C + (s16)(D1 & 0xffff)(); // JSR	8(PC,D1)
	DEF_ROMLOC(5556): goto rom_DC92; // JMP	$0000DC92
	DEF_ROMLOC(555C): or_toreg_8(0x6C, &D4); // ORI.B	#$6C,D4
	rom_5560(); // Detected flow into next function
}*/
/*ROMFUNC(rom_5560) {
	DEF_ROMLOC(5560): cmp_tomem_8(0x2, 0xFFFFD01A); // CMPI.B	#$02,$D01A
	DEF_ROMLOC(5566): if (CCR_EQ) goto rom_556C; // BEQ.B	$556C
	DEF_ROMLOC(5568): // TODO; // ADDQ.L	#$04,A7
	DEF_ROMLOC(556A): return; // RTS
}*/
/*ROMFUNC(rom_556C) {
	DEF_ROMLOC(556C): move_tomem_16(read_16(0xFFFFD008), A0 + 0x8); // MOVE.W	$D008,8(A0)
	DEF_ROMLOC(5572): move_tomem_16(read_16(0xFFFFD00C), A0 + 0xC); // MOVE.W	$D00C,12(A0)
	DEF_ROMLOC(5578): move_toreg_32(A0, &A1); // MOVEA.L	A0,A1
	DEF_ROMLOC(557A): move_toreg_32(0x0, &D3); // MOVEQ.L	$00,D3
	DEF_ROMLOC(557C): move_toreg_32(0x1, &D2); // MOVEQ.L	$01,D2
	DEF_ROMLOC(557E): move_toreg_32(0x5, &D1); // MOVEQ.L	$05,D1
	rom_5580(); // Detected flow into next function
}*/
/*ROMFUNC(rom_5580) {
	DEF_ROMLOC(5580): move_tomem_8(0xFFFFFF88, A1); // MOVE.B	#$88,(A1)
	DEF_ROMLOC(5584): add_tomem_8(0x2, A1 + 0x24); // ADDQ.B	#$02,36(A1)
	DEF_ROMLOC(5588): move_tomem_32(0x5788, A1 + 0x4); // MOVE.L	#$00005788,4(A1)
	DEF_ROMLOC(5590): move_tomem_16(0x3C5, A1 + 0x2); // MOVE.W	#$03C5,2(A1)
	DEF_ROMLOC(5596): move_tomem_8(0x4, A1 + 0x1); // MOVE.B	#$04,1(A1)
	DEF_ROMLOC(559C): move_tomem_8(0x1, A1 + 0x18); // MOVE.B	#$01,24(A1)
	DEF_ROMLOC(55A2): move_tomem_16(read_16(A0 + 0x8), A1 + 0x38); // MOVE.W	8(A0),56(A1)
	DEF_ROMLOC(55A8): move_tomem_16(read_16(A0 + 0xC), A1 + 0x3A); // MOVE.W	12(A0),58(A1)
	DEF_ROMLOC(55AE): move_tomem_8(D2, A1 + 0x1C); // MOVE.B	D2,28(A1)
	DEF_ROMLOC(55B2): move_tomem_8(D2, A1 + 0x1A); // MOVE.B	D2,26(A1)
	DEF_ROMLOC(55B6): add_toreg_8(0x1, &D2); // ADDQ.B	#$01,D2
	DEF_ROMLOC(55B8): move_tomem_8(D3, A1 + 0x26); // MOVE.B	D3,38(A1)
	DEF_ROMLOC(55BC): add_toreg_8(0x2A, &D3); // ADDI.B	#$2A,D3
	DEF_ROMLOC(55C0): move_toreg_32(A1 + 0x40, &A1); // LEA.L	64(A1),A1
	DEF_ROMLOC(55C4): dec_reg_16(&D1); if ((D1 & 0xffff) != 0xffff) goto rom_5580; // DBF.W	D1,$5580
	rom_55C8(); // Detected flow into next function
}*/
/*ROMFUNC(rom_55C8) {
	DEF_ROMLOC(55C8): move_toreg_16(read_16(A0 + 0x3E), &D0); // MOVE.W	62(A0),D0
	DEF_ROMLOC(55CC): add_tomem_16(D0, A0 + 0x26); // ADD.W	D0,38(A0)
	DEF_ROMLOC(55D0): move_toreg_8(read_8(A0 + 0x26), &D0); // MOVE.B	38(A0),D0
	DEF_ROMLOC(55D4): rom_29D2(); // JSR	$000029D2
	DEF_ROMLOC(55DA): move_toreg_32(0x0, &D4); // MOVEQ.L	$00,D4
	DEF_ROMLOC(55DC): move_toreg_8(read_8(A0 + 0x3C), &D4); // MOVE.B	60(A0),D4
	DEF_ROMLOC(55E0): muls_toreg_16(D4, &D1); // MULS.W	D4,D1
	DEF_ROMLOC(55E2): asr_toreg_32(0x8, &D1); // ASR.L	#$08,D1
	DEF_ROMLOC(55E4): muls_toreg_16(D4, &D0); // MULS.W	D4,D0
	DEF_ROMLOC(55E6): asr_toreg_32(0x8, &D0); // ASR.L	#$08,D0
	DEF_ROMLOC(55E8): add_toreg_16(read_16(A0 + 0x38), &D1); // ADD.W	56(A0),D1
	DEF_ROMLOC(55EC): add_toreg_16(read_16(A0 + 0x3A), &D0); // ADD.W	58(A0),D0
	DEF_ROMLOC(55F0): move_tomem_16(D1, A0 + 0x8); // MOVE.W	D1,8(A0)
	DEF_ROMLOC(55F4): move_tomem_16(D0, A0 + 0xC); // MOVE.W	D0,12(A0)
	rom_55F8(); // Detected flow into next function
}*/
/*ROMFUNC(rom_55F8) {
	DEF_ROMLOC(55F8): cmp_tomem_16(0x2000, A0 + 0x3C); // CMPI.W	#$2000,60(A0)
	DEF_ROMLOC(55FE): if (CCR_EQ) goto rom_5606; // BEQ.B	$5606
	DEF_ROMLOC(5600): add_tomem_16(0x20, A0 + 0x3C); // ADDI.W	#$0020,60(A0)
	rom_5606(); // Detected flow into next function
}*/
/*ROMFUNC(rom_5606) {
	DEF_ROMLOC(5606): cmp_tomem_16(0x2000, A0 + 0x3E); // CMPI.W	#$2000,62(A0)
	DEF_ROMLOC(560C): if (CCR_EQ) goto rom_5614; // BEQ.B	$5614
	DEF_ROMLOC(560E): add_tomem_16(0x20, A0 + 0x3E); // ADDI.W	#$0020,62(A0)
	rom_5614(); // Detected flow into next function
}*/
/*ROMFUNC(rom_5614) {
	DEF_ROMLOC(5614): cmp_tomem_16(0x140, A0 + 0x3A); // CMPI.W	#$0140,58(A0)
	DEF_ROMLOC(561A): if (CCR_EQ) goto rom_5620; // BEQ.B	$5620
	DEF_ROMLOC(561C): sub_tomem_16(0x1, A0 + 0x3A); // SUBQ.W	#$01,58(A0)
	rom_5620(); // Detected flow into next function
}*/
/*ROMFUNC(rom_5620) {
	DEF_ROMLOC(5620): return; // RTS
}*/
ROMFUNC(rom_5622) {
	u8 switchindex = 0;
	DEF_ROMLOC(5622): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(5624): move_toreg_8(read_8(A0 + 0x24), &D0); switchindex = D0 / 2; // MOVE.B	36(A0),D0
	DEF_ROMLOC(5628): move_toreg_16(read_16(0x5636 + (s16)(D0 & 0xffff)), &D1); // MOVE.W	12(PC,D0),D1
	// DEF_ROMLOC(562C): rom_5636 + (s16)(D1 & 0xffff)(); // JSR	8(PC,D1)
	DEF_ROMLOC(562C):
		switch (switchindex) {
			case 0: rom_563C(); break;
			case 1: rom_5666(); break;
			case 2: rom_5680(); break;
		}
	DEF_ROMLOC(5630): {rom_DC92();return;} // JMP	$0000DC92
}
ROMFUNC(rom_563C) {
	DEF_ROMLOC(563C): add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
	DEF_ROMLOC(5640): move_tomem_16(0xFFFFFFE0, A0 + 0x8); // MOVE.W	#$FFE0,8(A0)
	DEF_ROMLOC(5646): move_tomem_16(0xD8, A0 + 0xA); // MOVE.W	#$00D8,10(A0)
	DEF_ROMLOC(564C): move_tomem_32(0x57C0, A0 + 0x4); // MOVE.L	#$000057C0,4(A0)
	DEF_ROMLOC(5654): move_tomem_16(0x5C5, A0 + 0x2); // MOVE.W	#$05C5,2(A0)
	DEF_ROMLOC(565A): move_tomem_8(0x0, A0 + 0x1); // MOVE.B	#$00,1(A0)
	DEF_ROMLOC(5660): move_tomem_8(0x0, A0 + 0x18); // MOVE.B	#$00,24(A0)
	rom_5666(); // Detected flow into next function
}
ROMFUNC(rom_5666) {
	DEF_ROMLOC(5666): cmp_tomem_16(0xC0, A0 + 0x8); // CMPI.W	#$00C0,8(A0)
	DEF_ROMLOC(566C): if (CCR_EQ) goto rom_5676; // BEQ.B	$5676
	DEF_ROMLOC(566E): add_tomem_16(0x10, A0 + 0x8); // ADDI.W	#$0010,8(A0)
	DEF_ROMLOC(5674): return; // RTS
	DEF_ROMLOC(5676): add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
	DEF_ROMLOC(567A): move_tomem_16(0x12C, A0 + 0x30); // MOVE.W	#$012C,48(A0)
	rom_5680();
}
ROMFUNC(rom_5680) {
	DEF_ROMLOC(5680): sub_tomem_16(0x1, A0 + 0x30); // SUBQ.W	#$01,48(A0)
	DEF_ROMLOC(5684): if (CCR_PL) goto rom_568C; // BPL.B	$568C
	DEF_ROMLOC(5686): move_tomem_8(0x1C, 0xFFFFF600); // MOVE.B	#$1C,$F600
	DEF_ROMLOC(568C): return; // RTS
}