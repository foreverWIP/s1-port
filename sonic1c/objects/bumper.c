// #define CHECK_STUFF(loc) 1
#include "../system.h"
#include "../opcodes.h"

ROMFUNC(rom_F05C) {
	u8 switchindex = 0;
	DEF_ROMLOC(F05C): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(F05E): move_toreg_8(read_8(A0 + 0x24), &D0); switchindex = D0 / 2; // MOVE.B	36(A0),D0
	DEF_ROMLOC(F062): move_toreg_16(read_16(0xF06A + (s16)(D0 & 0xffff)), &D1); // MOVE.W	6(PC,D0),D1
	// DEF_ROMLOC(F066): goto rom_F06A + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
	DEF_ROMLOC(F066):
		switch (switchindex) {
			case 0: rom_F06E(); break;
			case 1: rom_F098(); break;
		}
}
ROMFUNC(rom_F06E) {
	DEF_ROMLOC(F06E): add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
	DEF_ROMLOC(F072): move_tomem_32(0xF18C, A0 + 0x4); // MOVE.L	#$0000F18C,4(A0)
	DEF_ROMLOC(F07A): move_tomem_16(0x380, A0 + 0x2); // MOVE.W	#$0380,2(A0)
	DEF_ROMLOC(F080): move_tomem_8(0x4, A0 + 0x1); // MOVE.B	#$04,1(A0)
	DEF_ROMLOC(F086): move_tomem_8(0x10, A0 + 0x19); // MOVE.B	#$10,25(A0)
	DEF_ROMLOC(F08C): move_tomem_8(0x1, A0 + 0x18); // MOVE.B	#$01,24(A0)
	DEF_ROMLOC(F092): move_tomem_8(0xFFFFFFD7, A0 + 0x20); // MOVE.B	#$D7,32(A0)
	rom_F098(); // Detected flow into next function
}
ROMFUNC(rom_F098) {
	DEF_ROMLOC(F098): tst_mem_8(A0 + 0x21); // TST.B	33(A0)
	DEF_ROMLOC(F09C): if (CCR_EQ) goto rom_F13C; // BEQ.W	$F13C
	DEF_ROMLOC(F0A0): clr_mem_8(A0 + 0x21); // CLR.B	33(A0)
	DEF_ROMLOC(F0A4): move_toreg_32(0xFFFFD000, &A1); // LEA.L	$D000,A1
	DEF_ROMLOC(F0A8): move_toreg_16(read_16(A0 + 0x8), &D1); // MOVE.W	8(A0),D1
	DEF_ROMLOC(F0AC): move_toreg_16(read_16(A0 + 0xC), &D2); // MOVE.W	12(A0),D2
	DEF_ROMLOC(F0B0): sub_toreg_16(read_16(A1 + 0x8), &D1); // SUB.W	8(A1),D1
	DEF_ROMLOC(F0B4): sub_toreg_16(read_16(A1 + 0xC), &D2); // SUB.W	12(A1),D2
	DEF_ROMLOC(F0B8): rom_2C6A(); // JSR	$00002C6A
	DEF_ROMLOC(F0BE): rom_29D2(); // JSR	$000029D2
	DEF_ROMLOC(F0C4): muls_toreg_16(0xFFFFF900, &D1); // MULS.W	#$F900,D1
	DEF_ROMLOC(F0C8): asr_toreg_32(0x8, &D1); // ASR.L	#$08,D1
	DEF_ROMLOC(F0CA): move_tomem_16(D1, A1 + 0x10); // MOVE.W	D1,16(A1)
	DEF_ROMLOC(F0CE): muls_toreg_16(0xFFFFF900, &D0); // MULS.W	#$F900,D0
	DEF_ROMLOC(F0D2): asr_toreg_32(0x8, &D0); // ASR.L	#$08,D0
	DEF_ROMLOC(F0D4): move_tomem_16(D0, A1 + 0x12); // MOVE.W	D0,18(A1)
	DEF_ROMLOC(F0D8): bset_tomem_8(0x1, A1 + 0x22); // BSET.B	#$01,34(A1)
	DEF_ROMLOC(F0DE): bclr_tomem_8(0x4, A1 + 0x22); // BCLR.B	#$04,34(A1)
	DEF_ROMLOC(F0E4): bclr_tomem_8(0x5, A1 + 0x22); // BCLR.B	#$05,34(A1)
	DEF_ROMLOC(F0EA): clr_mem_8(A1 + 0x3C); // CLR.B	60(A1)
	DEF_ROMLOC(F0EE): move_tomem_8(0x1, A0 + 0x1C); // MOVE.B	#$01,28(A0)
	DEF_ROMLOC(F0F4): move_toreg_16(0xB4, &D0); // MOVE.W	#$00B4,D0
	DEF_ROMLOC(F0F8): rom_1394(); // JSR	$00001394
	DEF_ROMLOC(F0FE): move_toreg_32(0xFFFFFC00, &A2); // LEA.L	$FC00,A2
	DEF_ROMLOC(F102): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(F104): move_toreg_8(read_8(A0 + 0x23), &D0); // MOVE.B	35(A0),D0
	DEF_ROMLOC(F108): if (CCR_EQ) goto rom_F116; // BEQ.B	$F116
	DEF_ROMLOC(F10A): cmp_tomem_8(0xFFFFFF8A, (s32)A2 + (s8)0x2 + (s16)D0); // CMPI.B	#$8A,2(A2,D0)
	DEF_ROMLOC(F110): if (CCR_CC) goto rom_F13C; // BCC.B	$F13C
	DEF_ROMLOC(F112): add_tomem_8(0x1, (s32)A2 + (s8)0x2 + (s16)D0); // ADDQ.B	#$01,2(A2,D0)
	DEF_ROMLOC(F116): move_toreg_32(0x1, &D0); // MOVEQ.L	$01,D0
	DEF_ROMLOC(F118): rom_1CE42(); // JSR	$0001CE42
	DEF_ROMLOC(F11E): rom_E11A(); // BSR.W	$E11A
	DEF_ROMLOC(F122): if (!CCR_EQ) goto rom_F13C; // BNE.B	$F13C
	DEF_ROMLOC(F124): move_tomem_8(0x29, A1 + 0x0); // MOVE.B	#$29,0(A1)
	DEF_ROMLOC(F12A): move_tomem_16(read_16(A0 + 0x8), A1 + 0x8); // MOVE.W	8(A0),8(A1)
	DEF_ROMLOC(F130): move_tomem_16(read_16(A0 + 0xC), A1 + 0xC); // MOVE.W	12(A0),12(A1)
	DEF_ROMLOC(F136): move_tomem_8(0x4, A1 + 0x1A); // MOVE.B	#$04,26(A1)
	DEF_ROMLOC(F13C): move_toreg_32(0xF17C, &A1); // LEA.L	$0000F17C,A1
	DEF_ROMLOC(F142): rom_ADA2(); // BSR.W	$ADA2
	DEF_ROMLOC(F146): move_toreg_16(read_16(A0 + 0x8), &D0); // MOVE.W	8(A0),D0
	DEF_ROMLOC(F14A): and_toreg_16(0xFFFFFF80, &D0); // ANDI.W	#$FF80,D0
	DEF_ROMLOC(F14E): move_toreg_16(read_16(0xFFFFF700), &D1); // MOVE.W	$F700,D1
	DEF_ROMLOC(F152): sub_toreg_16(0x80, &D1); // SUBI.W	#$0080,D1
	DEF_ROMLOC(F156): and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
	DEF_ROMLOC(F15A): sub_toreg_16(D1, &D0); // SUB.W	D1,D0
	DEF_ROMLOC(F15C): cmp_toreg_16(0x280, &D0); // CMPI.W	#$0280,D0
	DEF_ROMLOC(F160): if (CCR_HI) goto rom_F166; // BHI.B	$F166
	DEF_ROMLOC(F162): {rom_DC92();return;} // BRA.W	$DC92
	DEF_ROMLOC(F166): move_toreg_32(0xFFFFFC00, &A2); // LEA.L	$FC00,A2
	DEF_ROMLOC(F16A): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(F16C): move_toreg_8(read_8(A0 + 0x23), &D0); // MOVE.B	35(A0),D0
	DEF_ROMLOC(F170): if (CCR_EQ) goto rom_F178; // BEQ.B	$F178
	DEF_ROMLOC(F172): bclr_tomem_8(0x7, (s32)A2 + (s8)0x2 + (s16)D0); // BCLR.B	#$07,2(A2,D0)
	DEF_ROMLOC(F178): {rom_DCCE();return;} // BRA.W	$DCCE
}