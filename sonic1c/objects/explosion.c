// #define CHECK_STUFF(loc) 1
#include "../system.h"
#include "../opcodes.h"

ROMFUNC(rom_93E0) {
	u8 switchindex = 0;
	DEF_ROMLOC(93E0): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(93E2): move_toreg_8(read_8(A0 + 0x24), &D0); switchindex = D0 / 2; // MOVE.B	36(A0),D0
	DEF_ROMLOC(93E6): move_toreg_16(read_16(0x93EE + (s16)(D0 & 0xffff)), &D1); // MOVE.W	6(PC,D0),D1
	// DEF_ROMLOC(93EA): goto rom_93EE + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
	DEF_ROMLOC(93EA):
		switch (switchindex) {
			case 0: rom_93F4(); break;
			case 1: rom_9416(); break;
			case 2: rom_9456(); break;
		}
}
ROMFUNC(rom_93F4) {
	DEF_ROMLOC(93F4): add_tomem_8(2, A0 + 0x24);
	DEF_ROMLOC(93F8): rom_E11A(); // BSR.W	$E11A
	DEF_ROMLOC(93FC): if (!CCR_EQ) {rom_9416();return;} // BNE.B	$9416
	DEF_ROMLOC(93FE): move_tomem_8(0x28, A1 + 0x0); // MOVE.B	#$28,0(A1)
	DEF_ROMLOC(9404): move_tomem_16(read_16(A0 + 0x8), A1 + 0x8); // MOVE.W	8(A0),8(A1)
	DEF_ROMLOC(940A): move_tomem_16(read_16(A0 + 0xC), A1 + 0xC); // MOVE.W	12(A0),12(A1)
	DEF_ROMLOC(9410): move_tomem_16(read_16(A0 + 0x3E), A1 + 0x3E); // MOVE.W	62(A0),62(A1)
	rom_9416();
}
ROMFUNC(rom_9416) {
	DEF_ROMLOC(9416): add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
	DEF_ROMLOC(941A): move_tomem_32(0x9544, A0 + 0x4); // MOVE.L	#$00009544,4(A0)
	DEF_ROMLOC(9422): move_tomem_16(0x5A0, A0 + 0x2); // MOVE.W	#$05A0,2(A0)
	DEF_ROMLOC(9428): move_tomem_8(0x4, A0 + 0x1); // MOVE.B	#$04,1(A0)
	DEF_ROMLOC(942E): move_tomem_8(0x1, A0 + 0x18); // MOVE.B	#$01,24(A0)
	DEF_ROMLOC(9434): move_tomem_8(0x0, A0 + 0x20); // MOVE.B	#$00,32(A0)
	DEF_ROMLOC(943A): move_tomem_8(0xC, A0 + 0x19); // MOVE.B	#$0C,25(A0)
	DEF_ROMLOC(9440): move_tomem_8(0x7, A0 + 0x1E); // MOVE.B	#$07,30(A0)
	DEF_ROMLOC(9446): move_tomem_8(0x0, A0 + 0x1A); // MOVE.B	#$00,26(A0)
	DEF_ROMLOC(944C): move_toreg_16(0xC1, &D0); // MOVE.W	#$00C1,D0
	DEF_ROMLOC(9450): rom_1394(); // JSR	$00001394
	rom_9456();
}
ROMFUNC(rom_9456) {
	DEF_ROMLOC(9456): sub_tomem_8(0x1, A0 + 0x1E); // SUBQ.B	#$01,30(A0)
	DEF_ROMLOC(945A): if (CCR_PL) goto rom_9470; // BPL.B	$9470
	DEF_ROMLOC(945C): move_tomem_8(0x7, A0 + 0x1E); // MOVE.B	#$07,30(A0)
	DEF_ROMLOC(9462): add_tomem_8(0x1, A0 + 0x1A); // ADDQ.B	#$01,26(A0)
	DEF_ROMLOC(9466): cmp_tomem_8(0x5, A0 + 0x1A); // CMPI.B	#$05,26(A0)
	DEF_ROMLOC(946C): if (CCR_EQ) {rom_DCCE();return;} // BEQ.W	$DCCE
	DEF_ROMLOC(9470): {rom_DC92();return;} // BRA.W	$DC92
}
ROMFUNC(rom_9474) {
	u8 switchindex = 0;
	DEF_ROMLOC(9474): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(9476): move_toreg_8(read_8(A0 + 0x24), &D0); switchindex = D0 / 2; // MOVE.B	36(A0),D0
	DEF_ROMLOC(947A): move_toreg_16(read_16(0x9482 + (s16)(D0 & 0xffff)), &D1); // MOVE.W	6(PC,D0),D1
	// DEF_ROMLOC(947E): goto rom_9482 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
	DEF_ROMLOC(947E):
		switch (switchindex) {
			case 0: rom_9486(); break;
			case 1: rom_9456(); break;
		}
}
ROMFUNC(rom_9486) {
	DEF_ROMLOC(9486): add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
	DEF_ROMLOC(948A): move_tomem_32(0x958A, A0 + 0x4); // MOVE.L	#$0000958A,4(A0)
	DEF_ROMLOC(9492): move_tomem_16(0x5A0, A0 + 0x2); // MOVE.W	#$05A0,2(A0)
	DEF_ROMLOC(9498): move_tomem_8(0x4, A0 + 0x1); // MOVE.B	#$04,1(A0)
	DEF_ROMLOC(949E): move_tomem_8(0x1, A0 + 0x18); // MOVE.B	#$01,24(A0)
	DEF_ROMLOC(94A4): move_tomem_8(0x0, A0 + 0x20); // MOVE.B	#$00,32(A0)
	DEF_ROMLOC(94AA): move_tomem_8(0xC, A0 + 0x19); // MOVE.B	#$0C,25(A0)
	DEF_ROMLOC(94B0): move_tomem_8(0x7, A0 + 0x1E); // MOVE.B	#$07,30(A0)
	DEF_ROMLOC(94B6): move_tomem_8(0x0, A0 + 0x1A); // MOVE.B	#$00,26(A0)
	DEF_ROMLOC(94BC): move_toreg_16(0xC4, &D0); // MOVE.W	#$00C4,D0
	DEF_ROMLOC(94C0): {rom_1394();return;} // JMP	$00001394
}