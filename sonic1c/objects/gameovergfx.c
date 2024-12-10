// #define CHECK_STUFF(loc) 1
#include "../system.h"
#include "../opcodes.h"

/*ROMFUNC(rom_CB42) {
	DEF_ROMLOC(CB42): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(CB44): move_toreg_8(read_8(A0 + 0x24), &D0); // MOVE.B	36(A0),D0
	DEF_ROMLOC(CB48): move_toreg_16(read_16(0xCB50 + (s16)(D0 & 0xffff)), &D1); // MOVE.W	6(PC,D0),D1
	DEF_ROMLOC(CB4C): goto rom_CB50 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
	DEF_ROMLOC(CB50): or_toreg_8(0x46, &D6); // ORI.B	#$46,D6
	DEF_ROMLOC(CB54): or_tomem_16(0x4AB8, A0 - 0x980); // ORI.W	#$4AB8,-2432(A0)
	DEF_ROMLOC(CB5A): if (CCR_EQ) goto rom_CB5E; // BEQ.B	$CB5E
	DEF_ROMLOC(CB5C): return; // RTS
	DEF_ROMLOC(CB5E): add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
	DEF_ROMLOC(CB62): move_tomem_16(0x50, A0 + 0x8); // MOVE.W	#$0050,8(A0)
	DEF_ROMLOC(CB68): btst_tomem_8(0x0, A0 + 0x1A); // BTST.B	#$00,26(A0)
	DEF_ROMLOC(CB6E): if (CCR_EQ) goto rom_CB76; // BEQ.B	$CB76
	DEF_ROMLOC(CB70): move_tomem_16(0x1F0, A0 + 0x8); // MOVE.W	#$01F0,8(A0)
	DEF_ROMLOC(CB76): move_tomem_16(0xF0, A0 + 0xA); // MOVE.W	#$00F0,10(A0)
	DEF_ROMLOC(CB7C): move_tomem_32(0xD232, A0 + 0x4); // MOVE.L	#$0000D232,4(A0)
	DEF_ROMLOC(CB84): move_tomem_16(0xFFFF855E, A0 + 0x2); // MOVE.W	#$855E,2(A0)
	DEF_ROMLOC(CB8A): move_tomem_8(0x0, A0 + 0x1); // MOVE.B	#$00,1(A0)
	DEF_ROMLOC(CB90): move_tomem_8(0x0, A0 + 0x18); // MOVE.B	#$00,24(A0)
	DEF_ROMLOC(CB96): move_toreg_32(0x10, &D1); // MOVEQ.L	$10,D1
	DEF_ROMLOC(CB98): cmp_tomem_16(0x120, A0 + 0x8); // CMPI.W	#$0120,8(A0)
	DEF_ROMLOC(CB9E): if (CCR_EQ) goto rom_CBAC; // BEQ.B	$CBAC
	DEF_ROMLOC(CBA0): if (CCR_CS) goto rom_CBA4; // BCS.B	$CBA4
	DEF_ROMLOC(CBA2): neg_reg_16(&D1); // NEG.W	D1
	DEF_ROMLOC(CBA4): add_tomem_16(D1, A0 + 0x8); // ADD.W	D1,8(A0)
	DEF_ROMLOC(CBA8): goto rom_DC92; // BRA.W	$DC92
	DEF_ROMLOC(CBAC): move_tomem_16(0x2D0, A0 + 0x1E); // MOVE.W	#$02D0,30(A0)
	DEF_ROMLOC(CBB2): add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
	DEF_ROMLOC(CBB6): return; // RTS
	DEF_ROMLOC(CBB8): move_toreg_8(read_8(0xFFFFF605), &D0); // MOVE.B	$F605,D0
	DEF_ROMLOC(CBBC): and_toreg_8(0x70, &D0); // ANDI.B	#$70,D0
	DEF_ROMLOC(CBC0): if (!CCR_EQ) goto rom_CBD8; // BNE.B	$CBD8
	DEF_ROMLOC(CBC2): btst_tomem_8(0x0, A0 + 0x1A); // BTST.B	#$00,26(A0)
	DEF_ROMLOC(CBC8): if (!CCR_EQ) goto rom_CBFC; // BNE.B	$CBFC
	DEF_ROMLOC(CBCA): tst_mem_16(A0 + 0x1E); // TST.W	30(A0)
	DEF_ROMLOC(CBCE): if (CCR_EQ) goto rom_CBD8; // BEQ.B	$CBD8
	DEF_ROMLOC(CBD0): sub_tomem_16(0x1, A0 + 0x1E); // SUBQ.W	#$01,30(A0)
	DEF_ROMLOC(CBD4): goto rom_DC92; // BRA.W	$DC92
	DEF_ROMLOC(CBD8): tst_mem_8(0xFFFFFE1A); // TST.B	$FE1A
	DEF_ROMLOC(CBDC): if (!CCR_EQ) goto rom_CBF2; // BNE.B	$CBF2
	DEF_ROMLOC(CBDE): move_tomem_8(0x14, 0xFFFFF600); // MOVE.B	#$14,$F600
	DEF_ROMLOC(CBE4): tst_mem_8(0xFFFFFE18); // TST.B	$FE18
	DEF_ROMLOC(CBE8): if (!CCR_EQ) goto rom_CBFC; // BNE.B	$CBFC
	DEF_ROMLOC(CBEA): move_tomem_8(0x0, 0xFFFFF600); // MOVE.B	#$00,$F600
	DEF_ROMLOC(CBF0): goto rom_CBFC; // BRA.B	$CBFC
	DEF_ROMLOC(CBF2): clr_mem_32(0xFFFFFE38); // CLR.L	$FE38
	DEF_ROMLOC(CBF6): move_tomem_16(0x1, 0xFFFFFE02); // MOVE.W	#$0001,$FE02
	DEF_ROMLOC(CBFC): goto rom_DC92; // BRA.W	$DC92
	DEF_ROMLOC(CC00): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(CC02): move_toreg_8(read_8(A0 + 0x24), &D0); // MOVE.B	36(A0),D0
	DEF_ROMLOC(CC06): move_toreg_16(read_16(0xCC0E + (s16)(D0 & 0xffff)), &D1); // MOVE.W	6(PC,D0),D1
	DEF_ROMLOC(CC0A): goto rom_CC0E + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
	DEF_ROMLOC(CC0E): or_tomem_8(0x6A, A2); // ORI.B	#$6A,(A2)
	DEF_ROMLOC(CC12): or_tomem_32(0xC200B4, (s32)A4 + (s8)0x2E + (s16)D0); // ORI.L	#$00C200B4,46(A4,D0)
	DEF_ROMLOC(CC1A): or_tomem_32(0x1A401E6, (s32)A4 + (s8)0xB8 + (s16)D4); // ORI.L	#$01A401E6,-72(A4,D4)
	rom_CB56(); // Detected flow into next function
}*/
/*ROMFUNC(rom_CB56) {
	DEF_ROMLOC(CB56): tst_mem_32(0xFFFFF680); // TST.L	$F680
	DEF_ROMLOC(CB5A): if (CCR_EQ) goto rom_CB5E; // BEQ.B	$CB5E
	DEF_ROMLOC(CB5C): return; // RTS
}*/
/*ROMFUNC(rom_CB5E) {
	DEF_ROMLOC(CB5E): add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
	DEF_ROMLOC(CB62): move_tomem_16(0x50, A0 + 0x8); // MOVE.W	#$0050,8(A0)
	DEF_ROMLOC(CB68): btst_tomem_8(0x0, A0 + 0x1A); // BTST.B	#$00,26(A0)
	DEF_ROMLOC(CB6E): if (CCR_EQ) goto rom_CB76; // BEQ.B	$CB76
	DEF_ROMLOC(CB70): move_tomem_16(0x1F0, A0 + 0x8); // MOVE.W	#$01F0,8(A0)
	rom_CB76(); // Detected flow into next function
}*/
/*ROMFUNC(rom_CB76) {
	DEF_ROMLOC(CB76): move_tomem_16(0xF0, A0 + 0xA); // MOVE.W	#$00F0,10(A0)
	DEF_ROMLOC(CB7C): move_tomem_32(0xD232, A0 + 0x4); // MOVE.L	#$0000D232,4(A0)
	DEF_ROMLOC(CB84): move_tomem_16(0xFFFF855E, A0 + 0x2); // MOVE.W	#$855E,2(A0)
	DEF_ROMLOC(CB8A): move_tomem_8(0x0, A0 + 0x1); // MOVE.B	#$00,1(A0)
	DEF_ROMLOC(CB90): move_tomem_8(0x0, A0 + 0x18); // MOVE.B	#$00,24(A0)
	rom_CB96(); // Detected flow into next function
}*/
/*ROMFUNC(rom_CB96) {
	DEF_ROMLOC(CB96): move_toreg_32(0x10, &D1); // MOVEQ.L	$10,D1
	DEF_ROMLOC(CB98): cmp_tomem_16(0x120, A0 + 0x8); // CMPI.W	#$0120,8(A0)
	DEF_ROMLOC(CB9E): if (CCR_EQ) goto rom_CBAC; // BEQ.B	$CBAC
	DEF_ROMLOC(CBA0): if (CCR_CS) goto rom_CBA4; // BCS.B	$CBA4
	DEF_ROMLOC(CBA2): neg_reg_16(&D1); // NEG.W	D1
	rom_CBA4(); // Detected flow into next function
}*/
/*ROMFUNC(rom_CBA4) {
	DEF_ROMLOC(CBA4): add_tomem_16(D1, A0 + 0x8); // ADD.W	D1,8(A0)
	rom_DC92(); // BRA.W	$DC92
}*/
/*ROMFUNC(rom_CBAC) {
	DEF_ROMLOC(CBAC): move_tomem_16(0x2D0, A0 + 0x1E); // MOVE.W	#$02D0,30(A0)
	DEF_ROMLOC(CBB2): add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
	DEF_ROMLOC(CBB6): return; // RTS
}*/
/*ROMFUNC(rom_CBB8) {
	DEF_ROMLOC(CBB8): move_toreg_8(read_8(0xFFFFF605), &D0); // MOVE.B	$F605,D0
	DEF_ROMLOC(CBBC): and_toreg_8(0x70, &D0); // ANDI.B	#$70,D0
	DEF_ROMLOC(CBC0): if (!CCR_EQ) goto rom_CBD8; // BNE.B	$CBD8
	DEF_ROMLOC(CBC2): btst_tomem_8(0x0, A0 + 0x1A); // BTST.B	#$00,26(A0)
	DEF_ROMLOC(CBC8): if (!CCR_EQ) goto rom_CBFC; // BNE.B	$CBFC
	DEF_ROMLOC(CBCA): tst_mem_16(A0 + 0x1E); // TST.W	30(A0)
	DEF_ROMLOC(CBCE): if (CCR_EQ) goto rom_CBD8; // BEQ.B	$CBD8
	DEF_ROMLOC(CBD0): sub_tomem_16(0x1, A0 + 0x1E); // SUBQ.W	#$01,30(A0)
	rom_DC92(); // BRA.W	$DC92
}*/
/*ROMFUNC(rom_CBD8) {
	DEF_ROMLOC(CBD8): tst_mem_8(0xFFFFFE1A); // TST.B	$FE1A
	DEF_ROMLOC(CBDC): if (!CCR_EQ) goto rom_CBF2; // BNE.B	$CBF2
	DEF_ROMLOC(CBDE): move_tomem_8(0x14, 0xFFFFF600); // MOVE.B	#$14,$F600
	DEF_ROMLOC(CBE4): tst_mem_8(0xFFFFFE18); // TST.B	$FE18
	DEF_ROMLOC(CBE8): if (!CCR_EQ) goto rom_CBFC; // BNE.B	$CBFC
	DEF_ROMLOC(CBEA): move_tomem_8(0x0, 0xFFFFF600); // MOVE.B	#$00,$F600
	rom_CBFC(); // BRA.B	$CBFC
}*/
/*ROMFUNC(rom_CBF2) {
	DEF_ROMLOC(CBF2): clr_mem_32(0xFFFFFE38); // CLR.L	$FE38
	DEF_ROMLOC(CBF6): move_tomem_16(0x1, 0xFFFFFE02); // MOVE.W	#$0001,$FE02
	rom_CBFC(); // Detected flow into next function
}*/
/*ROMFUNC(rom_CBFC) {
	rom_DC92(); // BRA.W	$DC92
}*/