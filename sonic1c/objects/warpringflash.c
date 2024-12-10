#define CHECK_STUFF(loc) 1
#include "../opcodes.h"
#include "../system.h"

static bool returnearly = false;

ROMFUNC(rom_A554) {
	u8 switchindex = 0;
	DEF_ROMLOC(A554): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(A556): move_toreg_8(read_8(A0 + 0x24), &D0); switchindex = D0 / 2; // MOVE.B	36(A0),D0
	DEF_ROMLOC(A55A): move_toreg_16(read_16(0xA562 + (s16)(D0 & 0xffff)), &D1); // MOVE.W	6(PC,D0),D1
	// DEF_ROMLOC(A55E): goto rom_A562 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
	DEF_ROMLOC(A55E):
		switch (switchindex) {
			case 0: rom_A568(); break;
			case 1: rom_A592(); break;
			case 2: rom_A604(); break;
		}
}
ROMFUNC(rom_A568) {
	DEF_ROMLOC(A568): add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
	DEF_ROMLOC(A56C): move_tomem_32(0xA6F6, A0 + 0x4); // MOVE.L	#$0000A6F6,4(A0)
	DEF_ROMLOC(A574): move_tomem_16(0x2462, A0 + 0x2); // MOVE.W	#$2462,2(A0)
	DEF_ROMLOC(A57A): or_tomem_8(0x4, A0 + 0x1); // ORI.B	#$04,1(A0)
	DEF_ROMLOC(A580): move_tomem_8(0x0, A0 + 0x18); // MOVE.B	#$00,24(A0)
	DEF_ROMLOC(A586): move_tomem_8(0x20, A0 + 0x19); // MOVE.B	#$20,25(A0)
	DEF_ROMLOC(A58C): move_tomem_8(0xFFFFFFFF, A0 + 0x1A); // MOVE.B	#$FF,26(A0)
	rom_A592(); // Detected flow into next function
}
ROMFUNC(rom_A592) {
	DEF_ROMLOC(A592): rom_A5B6(); // BSR.B	$A5B6
	if (returnearly) {
		return;
	}
	DEF_ROMLOC(A594): move_toreg_16(read_16(A0 + 0x8), &D0); // MOVE.W	8(A0),D0
	DEF_ROMLOC(A598): and_toreg_16(0xFFFFFF80, &D0); // ANDI.W	#$FF80,D0
	DEF_ROMLOC(A59C): move_toreg_16(read_16(0xFFFFF700), &D1); // MOVE.W	$F700,D1
	DEF_ROMLOC(A5A0): sub_toreg_16(0x80, &D1); // SUBI.W	#$0080,D1
	DEF_ROMLOC(A5A4): and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
	DEF_ROMLOC(A5A8): sub_toreg_16(D1, &D0); // SUB.W	D1,D0
	DEF_ROMLOC(A5AA): cmp_toreg_16(0x280, &D0); // CMPI.W	#$0280,D0
	DEF_ROMLOC(A5AE): if (CCR_HI) {rom_DCCE();return;} // BHI.W	$DCCE
	rom_DC92(); // BRA.W	$DC92
}
ROMFUNC(rom_A5B6) {
	returnearly = false;
	DEF_ROMLOC(A5B6): sub_tomem_8(0x1, A0 + 0x1E); // SUBQ.B	#$01,30(A0)
	DEF_ROMLOC(A5BA): if (CCR_PL) goto rom_A5F4; // BPL.B	$A5F4
	DEF_ROMLOC(A5BC): move_tomem_8(0x1, A0 + 0x1E); // MOVE.B	#$01,30(A0)
	DEF_ROMLOC(A5C2): add_tomem_8(0x1, A0 + 0x1A); // ADDQ.B	#$01,26(A0)
	DEF_ROMLOC(A5C6): cmp_tomem_8(0x8, A0 + 0x1A); // CMPI.B	#$08,26(A0)
	DEF_ROMLOC(A5CC): if (CCR_CC) goto rom_A5F6; // BCC.B	$A5F6
	DEF_ROMLOC(A5CE): cmp_tomem_8(0x3, A0 + 0x1A); // CMPI.B	#$03,26(A0)
	DEF_ROMLOC(A5D4): if (!CCR_EQ) goto rom_A5F4; // BNE.B	$A5F4
	DEF_ROMLOC(A5D6): move_toreg_32(read_32(A0 + 0x3C), &A1); // MOVEA.L	60(A0),A1
	DEF_ROMLOC(A5DA): move_tomem_8(0x6, A1 + 0x24); // MOVE.B	#$06,36(A1)
	DEF_ROMLOC(A5E0): move_tomem_8(0x1C, 0xFFFFD01C); // MOVE.B	#$1C,$D01C
	DEF_ROMLOC(A5E6): move_tomem_8(0x1, 0xFFFFF7CD); // MOVE.B	#$01,$F7CD
	DEF_ROMLOC(A5EC): clr_mem_8(0xFFFFFE2D); // CLR.B	$FE2D
	DEF_ROMLOC(A5F0): clr_mem_8(0xFFFFFE2C); // CLR.B	$FE2C
	DEF_ROMLOC(A5F4): return; // RTS
	DEF_ROMLOC(A5F6): add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
	DEF_ROMLOC(A5FA): move_tomem_16(0x0, 0xFFFFD000); // MOVE.W	#$0000,$D000
	DEF_ROMLOC(A600): returnearly = true; // TODO; // ADDQ.L	#$04,A7
	DEF_ROMLOC(A602): return; // RTS
}
ROMFUNC(rom_A604) {
	DEF_ROMLOC(A604): {rom_DCCE();return;} // BRA.W	$DCCE
}