// #define CHECK_STUFF(loc) 1
#include "../system.h"
#include "../opcodes.h"

/*ROMFUNC(rom_F6EA) {
	DEF_ROMLOC(F6EA): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(F6EC): move_toreg_8(read_8(A0 + 0x24), &D0); // MOVE.B	36(A0),D0
	DEF_ROMLOC(F6F0): move_toreg_16(read_16(0xF6F8 + (s16)(D0 & 0xffff)), &D1); // MOVE.W	6(PC,D0),D1
	DEF_ROMLOC(F6F4): goto rom_F6F8 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
}*/
/*ROMFUNC(rom_F702) {
	DEF_ROMLOC(F702): add_tomem_8(0x4, A0 + 0x24); // ADDQ.B	#$04,36(A0)
	DEF_ROMLOC(F706): move_toreg_32(A0, &A1); // MOVEA.L	A0,A1
	DEF_ROMLOC(F708): move_toreg_32(0x1, &D1); // MOVEQ.L	$01,D1
	DEF_ROMLOC(F70A): goto rom_F712; // BRA.B	$F712
	DEF_ROMLOC(F70C): rom_E130(); // BSR.W	$E130
	DEF_ROMLOC(F710): if (!CCR_EQ) goto rom_F754; // BNE.B	$F754
	DEF_ROMLOC(F712): move_tomem_8(0x4E, A1 + 0x0); // MOVE.B	#$4E,0(A1)
	DEF_ROMLOC(F718): move_tomem_32(0xFBBA, A1 + 0x4); // MOVE.L	#$0000FBBA,4(A1)
	DEF_ROMLOC(F720): move_tomem_16(0x63A8, A1 + 0x2); // MOVE.W	#$63A8,2(A1)
	DEF_ROMLOC(F726): move_tomem_8(0x4, A1 + 0x1); // MOVE.B	#$04,1(A1)
	DEF_ROMLOC(F72C): move_tomem_8(0x50, A1 + 0x19); // MOVE.B	#$50,25(A1)
	DEF_ROMLOC(F732): move_tomem_16(read_16(A0 + 0x8), A1 + 0x8); // MOVE.W	8(A0),8(A1)
	DEF_ROMLOC(F738): move_tomem_16(read_16(A0 + 0xC), A1 + 0xC); // MOVE.W	12(A0),12(A1)
	DEF_ROMLOC(F73E): move_tomem_8(0x1, A1 + 0x18); // MOVE.B	#$01,24(A1)
	DEF_ROMLOC(F744): move_tomem_8(0x0, A1 + 0x1C); // MOVE.B	#$00,28(A1)
	DEF_ROMLOC(F74A): move_tomem_8(0xFFFFFF94, A1 + 0x20); // MOVE.B	#$94,32(A1)
	DEF_ROMLOC(F750): move_tomem_32(A0, A1 + 0x3C); // MOVE.L	A0,60(A1)
	DEF_ROMLOC(F754): dec_reg_16(&D1); if ((D1 & 0xffff) != 0xffff) goto rom_F70C; // DBF.W	D1,$F70C
	DEF_ROMLOC(F758): add_tomem_8(0x6, A1 + 0x24); // ADDQ.B	#$06,36(A1)
	DEF_ROMLOC(F75C): move_tomem_8(0x4, A1 + 0x1A); // MOVE.B	#$04,26(A1)
	rom_F762(); // Detected flow into next function
}*/
/*ROMFUNC(rom_F762) {
	DEF_ROMLOC(F762): move_toreg_16(read_16(0xFFFFD008), &D0); // MOVE.W	$D008,D0
	DEF_ROMLOC(F766): sub_toreg_16(read_16(A0 + 0x8), &D0); // SUB.W	8(A0),D0
	DEF_ROMLOC(F76A): if (CCR_CC) goto rom_F76E; // BCC.B	$F76E
	DEF_ROMLOC(F76C): neg_reg_16(&D0); // NEG.W	D0
	DEF_ROMLOC(F76E): cmp_toreg_16(0xC0, &D0); // CMPI.W	#$00C0,D0
	DEF_ROMLOC(F772): if (CCR_CC) goto rom_F78E; // BCC.B	$F78E
	DEF_ROMLOC(F774): move_toreg_16(read_16(0xFFFFD00C), &D0); // MOVE.W	$D00C,D0
	DEF_ROMLOC(F778): sub_toreg_16(read_16(A0 + 0xC), &D0); // SUB.W	12(A0),D0
	DEF_ROMLOC(F77C): if (CCR_CC) goto rom_F780; // BCC.B	$F780
	DEF_ROMLOC(F77E): neg_reg_16(&D0); // NEG.W	D0
	DEF_ROMLOC(F780): cmp_toreg_16(0x60, &D0); // CMPI.W	#$0060,D0
	DEF_ROMLOC(F784): if (CCR_CC) goto rom_F78E; // BCC.B	$F78E
	DEF_ROMLOC(F786): move_tomem_8(0x1, A0 + 0x36); // MOVE.B	#$01,54(A0)
	DEF_ROMLOC(F78C): goto rom_F79E; // BRA.B	$F79E
	DEF_ROMLOC(F78E): tst_mem_8(A0 + 0x36); // TST.B	54(A0)
	DEF_ROMLOC(F792): if (CCR_EQ) goto rom_F79E; // BEQ.B	$F79E
	DEF_ROMLOC(F794): move_tomem_16(0x180, A0 + 0x10); // MOVE.W	#$0180,16(A0)
	DEF_ROMLOC(F79A): sub_tomem_8(0x2, A0 + 0x24); // SUBQ.B	#$02,36(A0)
	rom_F79E(); // Detected flow into next function
}*/
/*ROMFUNC(rom_F79E) {
	DEF_ROMLOC(F79E): move_toreg_16(0x2B, &D1); // MOVE.W	#$002B,D1
	DEF_ROMLOC(F7A2): move_toreg_16(0x18, &D2); // MOVE.W	#$0018,D2
	DEF_ROMLOC(F7A6): move_toreg_16(D2, &D3); // MOVE.W	D2,D3
	DEF_ROMLOC(F7A8): add_toreg_16(0x1, &D3); // ADDQ.W	#$01,D3
	DEF_ROMLOC(F7AA): move_toreg_16(read_16(A0 + 0x8), &D4); // MOVE.W	8(A0),D4
	DEF_ROMLOC(F7AE): move_toreg_8(read_8(A0 + 0x24), &D0); // MOVE.B	36(A0),D0
	DEF_ROMLOC(F7B2): move_tomem_16(D0, A7 -= 2); // MOVE.W	D0,-(A7)
	DEF_ROMLOC(F7B4): rom_10062(); // BSR.W	$10062
	DEF_ROMLOC(F7B8): move_toreg_16(read_16((A7 += 2, A7 - 2)), &D0); // MOVE.W	(A7)+,D0
	DEF_ROMLOC(F7BA): move_tomem_8(D0, A0 + 0x24); // MOVE.B	D0,36(A0)
	DEF_ROMLOC(F7BE): cmp_tomem_16(0x6A0, A0 + 0x8); // CMPI.W	#$06A0,8(A0)
	DEF_ROMLOC(F7C4): if (!CCR_EQ) goto rom_F7CE; // BNE.B	$F7CE
	DEF_ROMLOC(F7C6): clr_mem_16(A0 + 0x10); // CLR.W	16(A0)
	DEF_ROMLOC(F7CA): clr_mem_8(A0 + 0x36); // CLR.B	54(A0)
	DEF_ROMLOC(F7CE): move_toreg_32(0xF8CE, &A1); // LEA.L	$0000F8CE,A1
	DEF_ROMLOC(F7D4): rom_ADA2(); // BSR.W	$ADA2
	DEF_ROMLOC(F7D8): cmp_tomem_8(0x4, 0xFFFFD024); // CMPI.B	#$04,$D024
	DEF_ROMLOC(F7DE): if (CCR_CC) goto rom_F7E4; // BCC.B	$F7E4
	DEF_ROMLOC(F7E0): rom_DC6C(); // BSR.W	$DC6C
	DEF_ROMLOC(F7E4): rom_DC92(); // BSR.W	$DC92
	DEF_ROMLOC(F7E8): tst_mem_8(A0 + 0x36); // TST.B	54(A0)
	DEF_ROMLOC(F7EC): if (!CCR_EQ) goto rom_F80A; // BNE.B	$F80A
	DEF_ROMLOC(F7EE): move_toreg_16(read_16(A0 + 0x8), &D0); // MOVE.W	8(A0),D0
	DEF_ROMLOC(F7F2): and_toreg_16(0xFFFFFF80, &D0); // ANDI.W	#$FF80,D0
	DEF_ROMLOC(F7F6): move_toreg_16(read_16(0xFFFFF700), &D1); // MOVE.W	$F700,D1
	DEF_ROMLOC(F7FA): sub_toreg_16(0x80, &D1); // SUBI.W	#$0080,D1
	DEF_ROMLOC(F7FE): and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
	DEF_ROMLOC(F802): sub_toreg_16(D1, &D0); // SUB.W	D1,D0
	DEF_ROMLOC(F804): cmp_toreg_16(0x280, &D0); // CMPI.W	#$0280,D0
	DEF_ROMLOC(F808): if (CCR_HI) goto rom_F80C; // BHI.B	$F80C
	DEF_ROMLOC(F80A): return; // RTS
	DEF_ROMLOC(F80C): move_toreg_32(0xFFFFFC00, &A2); // LEA.L	$FC00,A2
	DEF_ROMLOC(F810): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(F812): move_toreg_8(read_8(A0 + 0x23), &D0); // MOVE.B	35(A0),D0
	DEF_ROMLOC(F816): bclr_tomem_8(0x7, (s32)A2 + (s8)0x2 + (s16)D0); // BCLR.B	#$07,2(A2,D0)
	DEF_ROMLOC(F81C): move_tomem_8(0x8, A0 + 0x24); // MOVE.B	#$08,36(A0)
	DEF_ROMLOC(F822): return; // RTS
}*/
/*ROMFUNC(rom_F824) {
	DEF_ROMLOC(F824): move_toreg_32(read_32(A0 + 0x3C), &A1); // MOVEA.L	60(A0),A1
	DEF_ROMLOC(F828): cmp_tomem_8(0x8, A1 + 0x24); // CMPI.B	#$08,36(A1)
	DEF_ROMLOC(F82E): if (CCR_EQ) goto rom_F840; // BEQ.B	$F840
	DEF_ROMLOC(F830): move_tomem_16(read_16(A1 + 0x8), A0 + 0x8); // MOVE.W	8(A1),8(A0)
	DEF_ROMLOC(F836): sub_tomem_16(0x80, A0 + 0x8); // SUBI.W	#$0080,8(A0)
	rom_DC92(); // BRA.W	$DC92
}*/
/*ROMFUNC(rom_F840) {
	rom_DCCE(); // BRA.W	$DCCE
}*/
ROMFUNC(rom_F844) {
	u8 switchindex = 0;
	DEF_ROMLOC(F844): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(F846): move_toreg_8(read_8(A0 + 0x24), &D0); switchindex = D0 / 2; // MOVE.B	36(A0),D0
	DEF_ROMLOC(F84A): move_toreg_16(read_16(0xF852 + (s16)(D0 & 0xffff)), &D1); // MOVE.W	6(PC,D0),D1
	// DEF_ROMLOC(F84E): goto rom_F852 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
	DEF_ROMLOC(F84E):
		switch (switchindex) {
			case 0: rom_F85A(); break;
			case 1: rom_F878(); break;
		}
}
ROMFUNC(rom_F85A) {
	DEF_ROMLOC(F85A): add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
	DEF_ROMLOC(F85E): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(F860): move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B	40(A0),D0
	DEF_ROMLOC(F864): move_tomem_8(read_8(0xF856 + (s16)(D0 & 0xffff)), A0 + 0x20); // MOVE.B	-16(PC,D0),32(A0)
	DEF_ROMLOC(F86A): move_tomem_32(0xF89C, A0 + 0x4); // MOVE.L	#$0000F89C,4(A0)
	DEF_ROMLOC(F872): move_tomem_8(0xFFFFFF84, A0 + 0x1); // MOVE.B	#$84,1(A0)
	rom_F878(); // Detected flow into next function
}
ROMFUNC(rom_F878) {
	DEF_ROMLOC(F878): move_toreg_16(read_16(A0 + 0x8), &D0); // MOVE.W	8(A0),D0
	DEF_ROMLOC(F87C): and_toreg_16(0xFFFFFF80, &D0); // ANDI.W	#$FF80,D0
	DEF_ROMLOC(F880): move_toreg_16(read_16(0xFFFFF700), &D1); // MOVE.W	$F700,D1
	DEF_ROMLOC(F884): sub_toreg_16(0x80, &D1); // SUBI.W	#$0080,D1
	DEF_ROMLOC(F888): and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
	DEF_ROMLOC(F88C): sub_toreg_16(D1, &D0); // SUB.W	D1,D0
	DEF_ROMLOC(F88E): if (CCR_MI) {rom_DCCE();return;} // BMI.W	$DCCE
	DEF_ROMLOC(F892): cmp_toreg_16(0x280, &D0); // CMPI.W	#$0280,D0
	DEF_ROMLOC(F896): if (CCR_HI) {rom_DCCE();return;} // BHI.W	$DCCE
	DEF_ROMLOC(F89A): return; // RTS
}