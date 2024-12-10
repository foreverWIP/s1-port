// #define CHECK_STUFF(loc) 1
#include "../system.h"
#include "../opcodes.h"

ROMFUNC(rom_11AEE) {
	u8 switchindex = 0;
	DEF_ROMLOC(11AEE): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(11AF0): move_toreg_8(read_8(A0 + 0x24), &D0); switchindex = D0 / 2; // MOVE.B	36(A0),D0
	DEF_ROMLOC(11AF4): move_toreg_16(read_16(0x11AFC + (s16)(D0 & 0xffff)), &D1); // MOVE.W	6(PC,D0),D1
	// DEF_ROMLOC(11AF8): goto rom_11AFC + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
	DEF_ROMLOC(11AF8):
		switch (switchindex) {
			case 0: rom_11B00(); break;
			case 1: rom_11B38(); break;
		}
}
ROMFUNC(rom_11B00) {
	DEF_ROMLOC(11B00): add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
	DEF_ROMLOC(11B04): move_tomem_32(0x11B8A, A0 + 0x4); // MOVE.L	#$00011B8A,4(A0)
	DEF_ROMLOC(11B0C): move_tomem_16(0xFFFF8680, A0 + 0x2); // MOVE.W	#$8680,2(A0)
	DEF_ROMLOC(11B12): or_tomem_8(0x4, A0 + 0x1); // ORI.B	#$04,1(A0)
	DEF_ROMLOC(11B18): move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B	40(A0),D0
	DEF_ROMLOC(11B1C): move_toreg_8(D0, &D1); // MOVE.B	D0,D1
	DEF_ROMLOC(11B1E): and_toreg_16(0xF0, &D0); // ANDI.W	#$00F0,D0
	DEF_ROMLOC(11B22): add_toreg_16(0x10, &D0); // ADDI.W	#$0010,D0
	DEF_ROMLOC(11B26): lsr_toreg_16(0x1, &D0); // LSR.W	#$01,D0
	DEF_ROMLOC(11B28): move_tomem_8(D0, A0 + 0x19); // MOVE.B	D0,25(A0)
	DEF_ROMLOC(11B2C): and_toreg_16(0xF, &D1); // ANDI.W	#$000F,D1
	DEF_ROMLOC(11B30): add_toreg_16(0x1, &D1); // ADDQ.W	#$01,D1
	DEF_ROMLOC(11B32): lsl_toreg_16(0x3, &D1); // LSL.W	#$03,D1
	DEF_ROMLOC(11B34): move_tomem_8(D1, A0 + 0x16); // MOVE.B	D1,22(A0)
	rom_11B38(); // Detected flow into next function
}
ROMFUNC(rom_11B38) {
	DEF_ROMLOC(11B38): rom_DF0C(); // BSR.W	$DF0C
	DEF_ROMLOC(11B3C): if (!CCR_EQ) goto rom_11B5A; // BNE.B	$11B5A
	DEF_ROMLOC(11B3E): move_toreg_32(0x0, &D1); // MOVEQ.L	$00,D1
	DEF_ROMLOC(11B40): move_toreg_8(read_8(A0 + 0x19), &D1); // MOVE.B	25(A0),D1
	DEF_ROMLOC(11B44): add_toreg_16(0xB, &D1); // ADDI.W	#$000B,D1
	DEF_ROMLOC(11B48): move_toreg_32(0x0, &D2); // MOVEQ.L	$00,D2
	DEF_ROMLOC(11B4A): move_toreg_8(read_8(A0 + 0x16), &D2); // MOVE.B	22(A0),D2
	DEF_ROMLOC(11B4E): move_toreg_16(D2, &D3); // MOVE.W	D2,D3
	DEF_ROMLOC(11B50): add_toreg_16(0x1, &D3); // ADDQ.W	#$01,D3
	DEF_ROMLOC(11B52): move_toreg_16(read_16(A0 + 0x8), &D4); // MOVE.W	8(A0),D4
	DEF_ROMLOC(11B56): rom_100A8(); // BSR.W	$100A8
	DEF_ROMLOC(11B5A): move_toreg_16(read_16(A0 + 0x8), &D0); // MOVE.W	8(A0),D0
	DEF_ROMLOC(11B5E): and_toreg_16(0xFFFFFF80, &D0); // ANDI.W	#$FF80,D0
	DEF_ROMLOC(11B62): move_toreg_16(read_16(0xFFFFF700), &D1); // MOVE.W	$F700,D1
	DEF_ROMLOC(11B66): sub_toreg_16(0x80, &D1); // SUBI.W	#$0080,D1
	DEF_ROMLOC(11B6A): and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
	DEF_ROMLOC(11B6E): sub_toreg_16(D1, &D0); // SUB.W	D1,D0
	DEF_ROMLOC(11B70): cmp_toreg_16(0x280, &D0); // CMPI.W	#$0280,D0
	DEF_ROMLOC(11B74): if (CCR_HI) goto rom_11B84; // BHI.B	$11B84
	DEF_ROMLOC(11B76): tst_mem_16(0xFFFFFE08); // TST.W	$FE08
	DEF_ROMLOC(11B7A): if (CCR_EQ) goto rom_11B82; // BEQ.B	$11B82
	DEF_ROMLOC(11B7C): {rom_DC92();return;} // JMP	$0000DC92
	DEF_ROMLOC(11B82): return; // RTS
	DEF_ROMLOC(11B84): {rom_DCCE();return;} // JMP	$0000DCCE
}