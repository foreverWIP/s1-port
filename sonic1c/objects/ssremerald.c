// #define CHECK_STUFF(loc) 1
#include "../system.h"
#include "../opcodes.h"

/*ROMFUNC(rom_CFE4) {
	DEF_ROMLOC(CFE4): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(CFE6): move_toreg_8(read_8(A0 + 0x24), &D0); // MOVE.B	36(A0),D0
	DEF_ROMLOC(CFEA): move_toreg_16(read_16(0xCFF2 + (s16)(D0 & 0xffff)), &D1); // MOVE.W	6(PC,D0),D1
	DEF_ROMLOC(CFEE): goto rom_CFF2 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
	DEF_ROMLOC(CFF2): or_tomem_8(0x68, A0); // ORI.B	#$68,(A0)
	rom_CFF6(); // Detected flow into next function
}*/
/*ROMFUNC(rom_CFF6) {
	DEF_ROMLOC(CFF6): btst_tomem_8(D0, A0); // BTST.B	D0,(A0)
	DEF_ROMLOC(CFF8): btst_tomem_8(D0, A0 + 0xF8); // BTST.B	D0,248(A0)
	DEF_ROMLOC(CFFC): bchg_toreg_32(D0, &D0); // BCHG.L	D0,D0
	rom_D002(); // Detected flow into next function
}*/
/*ROMFUNC(rom_D002) {
	DEF_ROMLOC(D002): move_toreg_32(A0, &A1); // MOVEA.L	A0,A1
	DEF_ROMLOC(D004): move_toreg_32(0xCFF6, &A2); // LEA.L	$0000CFF6,A2
	DEF_ROMLOC(D00A): move_toreg_32(0x0, &D2); // MOVEQ.L	$00,D2
	DEF_ROMLOC(D00C): move_toreg_32(0x0, &D1); // MOVEQ.L	$00,D1
	DEF_ROMLOC(D00E): move_toreg_8(read_8(0xFFFFFE57), &D1); // MOVE.B	$FE57,D1
	DEF_ROMLOC(D012): sub_toreg_8(0x1, &D1); // SUBQ.B	#$01,D1
	DEF_ROMLOC(D014): if (CCR_CS) goto rom_DCCE; // BCS.W	$DCCE
	rom_D018(); // Detected flow into next function
}*/
/*ROMFUNC(rom_D018) {
	DEF_ROMLOC(D018): move_tomem_8(0x7F, A1 + 0x0); // MOVE.B	#$7F,0(A1)
	DEF_ROMLOC(D01E): move_tomem_16(read_16((A2 += 2, A2 - 2)), A1 + 0x8); // MOVE.W	(A2)+,8(A1)
	DEF_ROMLOC(D022): move_tomem_16(0xF0, A1 + 0xA); // MOVE.W	#$00F0,10(A1)
	DEF_ROMLOC(D028): move_toreg_32(0xFFFFFE58, &A3); // LEA.L	$FE58,A3
	DEF_ROMLOC(D02C): move_toreg_8(read_8((s32)A3 + (s8)0x0 + (s16)D2), &D3); // MOVE.B	0(A3,D2),D3
	DEF_ROMLOC(D030): move_tomem_8(D3, A1 + 0x1A); // MOVE.B	D3,26(A1)
	DEF_ROMLOC(D034): move_tomem_8(D3, A1 + 0x1C); // MOVE.B	D3,28(A1)
	DEF_ROMLOC(D038): add_toreg_8(0x1, &D2); // ADDQ.B	#$01,D2
	DEF_ROMLOC(D03A): add_tomem_8(0x2, A1 + 0x24); // ADDQ.B	#$02,36(A1)
	DEF_ROMLOC(D03E): move_tomem_32(0xD482, A1 + 0x4); // MOVE.L	#$0000D482,4(A1)
	DEF_ROMLOC(D046): move_tomem_16(0xFFFF8541, A1 + 0x2); // MOVE.W	#$8541,2(A1)
	DEF_ROMLOC(D04C): move_tomem_8(0x0, A1 + 0x1); // MOVE.B	#$00,1(A1)
	DEF_ROMLOC(D052): move_toreg_32(A1 + 0x40, &A1); // LEA.L	64(A1),A1
	DEF_ROMLOC(D056): dec_reg_16(&D1); if ((D1 & 0xffff) != 0xffff) goto rom_D018; // DBF.W	D1,$D018
	rom_D05A(); // Detected flow into next function
}*/
/*ROMFUNC(rom_D05A) {
	DEF_ROMLOC(D05A): move_toreg_8(read_8(A0 + 0x1A), &D0); // MOVE.B	26(A0),D0
	DEF_ROMLOC(D05E): move_tomem_8(0x6, A0 + 0x1A); // MOVE.B	#$06,26(A0)
	DEF_ROMLOC(D064): cmp_toreg_8(0x6, &D0); // CMPI.B	#$06,D0
	DEF_ROMLOC(D068): if (!CCR_EQ) goto rom_D070; // BNE.B	$D070
	DEF_ROMLOC(D06A): move_tomem_8(read_8(A0 + 0x1C), A0 + 0x1A); // MOVE.B	28(A0),26(A0)
	rom_D070(); // Detected flow into next function
}*/
/*ROMFUNC(rom_D070) {
	DEF_ROMLOC(D070): goto rom_DC92; // BRA.W	$DC92
	DEF_ROMLOC(D074): or_tomem_8(0x46, A0++); // ORI.B	#$46,(A0)+
	DEF_ROMLOC(D078): or_tomem_16(0x94, (s32)A4 + (s8)0xC2 + (s16)D0); // ORI.W	#$0094,-62(A4,D0)
	rom_D4B6(); // Detected flow into next function
}*/