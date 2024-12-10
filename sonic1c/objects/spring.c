// #define CHECK_STUFF(loc) 1
#include "../system.h"
#include "../opcodes.h"

ROMFUNC(rom_E14C) {
	u8 switchindex = 0;
	DEF_ROMLOC(E14C): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(E14E): move_toreg_8(read_8(A0 + 0x24), &D0); switchindex = D0 / 2; // MOVE.B	36(A0),D0
	DEF_ROMLOC(E152): move_toreg_16(read_16(0xE17E + (s16)(D0 & 0xffff)), &D1); // MOVE.W	42(PC,D0),D1
	// DEF_ROMLOC(E156): rom_E17E + (s16)(D1 & 0xffff)(); // JSR	38(PC,D1)
	DEF_ROMLOC(E156):
		switch (switchindex) {
			case 0: rom_E196(); break;
			case 1: rom_E20C(); break;
			case 2: rom_E262(); break;
			case 3: rom_E26C(); break;
			case 4: rom_E278(); break;
			case 5: rom_E2FA(); break;
			case 6: rom_E304(); break;
			case 7: rom_E310(); break;
			case 8: rom_E376(); break;
			case 9: rom_E380(); break;
		}
	DEF_ROMLOC(E15A): rom_DC92(); // BSR.W	$DC92
	DEF_ROMLOC(E15E): move_toreg_16(read_16(A0 + 0x8), &D0); // MOVE.W	8(A0),D0
	DEF_ROMLOC(E162): and_toreg_16(0xFFFFFF80, &D0); // ANDI.W	#$FF80,D0
	DEF_ROMLOC(E166): move_toreg_16(read_16(0xFFFFF700), &D1); // MOVE.W	$F700,D1
	DEF_ROMLOC(E16A): sub_toreg_16(0x80, &D1); // SUBI.W	#$0080,D1
	DEF_ROMLOC(E16E): and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
	DEF_ROMLOC(E172): sub_toreg_16(D1, &D0); // SUB.W	D1,D0
	DEF_ROMLOC(E174): cmp_toreg_16(0x280, &D0); // CMPI.W	#$0280,D0
	DEF_ROMLOC(E178): if (CCR_HI) {rom_DCCE();return;} // BHI.W	$DCCE
	DEF_ROMLOC(E17C): return; // RTS
}
ROMFUNC(rom_E196) {
	DEF_ROMLOC(E196): add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
	DEF_ROMLOC(E19A): move_tomem_32(0xE3A8, A0 + 0x4); // MOVE.L	#$0000E3A8,4(A0)
	DEF_ROMLOC(E1A2): move_tomem_16(0x523, A0 + 0x2); // MOVE.W	#$0523,2(A0)
	DEF_ROMLOC(E1A8): or_tomem_8(0x4, A0 + 0x1); // ORI.B	#$04,1(A0)
	DEF_ROMLOC(E1AE): move_tomem_8(0x10, A0 + 0x19); // MOVE.B	#$10,25(A0)
	DEF_ROMLOC(E1B4): move_tomem_8(0x4, A0 + 0x18); // MOVE.B	#$04,24(A0)
	DEF_ROMLOC(E1BA): move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B	40(A0),D0
	DEF_ROMLOC(E1BE): btst_toreg_32(0x4, &D0); // BTST.L	#$04,D0
	DEF_ROMLOC(E1C2): if (CCR_EQ) goto rom_E1E2; // BEQ.B	$E1E2
	DEF_ROMLOC(E1C4): move_tomem_8(0x8, A0 + 0x24); // MOVE.B	#$08,36(A0)
	DEF_ROMLOC(E1CA): move_tomem_8(0x1, A0 + 0x1C); // MOVE.B	#$01,28(A0)
	DEF_ROMLOC(E1D0): move_tomem_8(0x3, A0 + 0x1A); // MOVE.B	#$03,26(A0)
	DEF_ROMLOC(E1D6): move_tomem_16(0x533, A0 + 0x2); // MOVE.W	#$0533,2(A0)
	DEF_ROMLOC(E1DC): move_tomem_8(0x8, A0 + 0x19); // MOVE.B	#$08,25(A0)
	DEF_ROMLOC(E1E2): btst_toreg_32(0x5, &D0); // BTST.L	#$05,D0
	DEF_ROMLOC(E1E6): if (CCR_EQ) goto rom_E1F4; // BEQ.B	$E1F4
	DEF_ROMLOC(E1E8): move_tomem_8(0xE, A0 + 0x24); // MOVE.B	#$0E,36(A0)
	DEF_ROMLOC(E1EE): bset_tomem_8(0x1, A0 + 0x22); // BSET.B	#$01,34(A0)
	DEF_ROMLOC(E1F4): btst_toreg_32(0x1, &D0); // BTST.L	#$01,D0
	DEF_ROMLOC(E1F8): if (CCR_EQ) goto rom_E200; // BEQ.B	$E200
	DEF_ROMLOC(E1FA): bset_tomem_8(0x5, A0 + 0x2); // BSET.B	#$05,2(A0)
	DEF_ROMLOC(E200): and_toreg_16(0xF, &D0); // ANDI.W	#$000F,D0
	DEF_ROMLOC(E204): move_tomem_16(read_16(0xE192 + (s16)(D0 & 0xffff)), A0 + 0x30); // MOVE.W	-116(PC,D0),48(A0)
	DEF_ROMLOC(E20A): return; // RTS
}
ROMFUNC(rom_E20C) {
	DEF_ROMLOC(E20C): move_toreg_16(0x1B, &D1); // MOVE.W	#$001B,D1
	DEF_ROMLOC(E210): move_toreg_16(0x8, &D2); // MOVE.W	#$0008,D2
	DEF_ROMLOC(E214): move_toreg_16(0x10, &D3); // MOVE.W	#$0010,D3
	DEF_ROMLOC(E218): move_toreg_16(read_16(A0 + 0x8), &D4); // MOVE.W	8(A0),D4
	DEF_ROMLOC(E21C): rom_10062(); // BSR.W	$10062
	DEF_ROMLOC(E220): tst_mem_8(A0 + 0x25); // TST.B	37(A0)
	DEF_ROMLOC(E224): if (!CCR_EQ) goto rom_E228; // BNE.B	$E228
	DEF_ROMLOC(E226): return; // RTS
	DEF_ROMLOC(E228): add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
	DEF_ROMLOC(E22C): add_tomem_16(0x8, A1 + 0xC); // ADDQ.W	#$08,12(A1)
	DEF_ROMLOC(E230): move_tomem_16(read_16(A0 + 0x30), A1 + 0x12); // MOVE.W	48(A0),18(A1)
	DEF_ROMLOC(E236): bset_tomem_8(0x1, A1 + 0x22); // BSET.B	#$01,34(A1)
	DEF_ROMLOC(E23C): bclr_tomem_8(0x3, A1 + 0x22); // BCLR.B	#$03,34(A1)
	DEF_ROMLOC(E242): move_tomem_8(0x10, A1 + 0x1C); // MOVE.B	#$10,28(A1)
	DEF_ROMLOC(E248): move_tomem_8(0x2, A1 + 0x24); // MOVE.B	#$02,36(A1)
	DEF_ROMLOC(E24E): bclr_tomem_8(0x3, A0 + 0x22); // BCLR.B	#$03,34(A0)
	DEF_ROMLOC(E254): clr_mem_8(A0 + 0x25); // CLR.B	37(A0)
	DEF_ROMLOC(E258): move_toreg_16(0xCC, &D0); // MOVE.W	#$00CC,D0
	DEF_ROMLOC(E25C): rom_1394(); // JSR	$00001394
	rom_E262(); // Detected flow into next function
}
ROMFUNC(rom_E262) {
	DEF_ROMLOC(E262): move_toreg_32(0xE38C, &A1); // LEA.L	$0000E38C,A1
	rom_ADA2(); // BRA.W	$ADA2
}
ROMFUNC(rom_E26C) {
	DEF_ROMLOC(E26C): move_tomem_8(0x1, A0 + 0x1D); // MOVE.B	#$01,29(A0)
	DEF_ROMLOC(E272): sub_tomem_8(0x4, A0 + 0x24); // SUBQ.B	#$04,36(A0)
	DEF_ROMLOC(E276): return; // RTS
}
ROMFUNC(rom_E278) {
	DEF_ROMLOC(E278): move_toreg_16(0x13, &D1); // MOVE.W	#$0013,D1
	DEF_ROMLOC(E27C): move_toreg_16(0xE, &D2); // MOVE.W	#$000E,D2
	DEF_ROMLOC(E280): move_toreg_16(0xF, &D3); // MOVE.W	#$000F,D3
	DEF_ROMLOC(E284): move_toreg_16(read_16(A0 + 0x8), &D4); // MOVE.W	8(A0),D4
	DEF_ROMLOC(E288): rom_10062(); // BSR.W	$10062
	DEF_ROMLOC(E28C): cmp_tomem_8(0x2, A0 + 0x24); // CMPI.B	#$02,36(A0)
	DEF_ROMLOC(E292): if (!CCR_EQ) goto rom_E29A; // BNE.B	$E29A
	DEF_ROMLOC(E294): move_tomem_8(0x8, A0 + 0x24); // MOVE.B	#$08,36(A0)
	DEF_ROMLOC(E29A): btst_tomem_8(0x5, A0 + 0x22); // BTST.B	#$05,34(A0)
	DEF_ROMLOC(E2A0): if (!CCR_EQ) goto rom_E2A4; // BNE.B	$E2A4
	DEF_ROMLOC(E2A2): return; // RTS
	DEF_ROMLOC(E2A4): add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
	DEF_ROMLOC(E2A8): move_tomem_16(read_16(A0 + 0x30), A1 + 0x10); // MOVE.W	48(A0),16(A1)
	DEF_ROMLOC(E2AE): add_tomem_16(0x8, A1 + 0x8); // ADDQ.W	#$08,8(A1)
	DEF_ROMLOC(E2B2): btst_tomem_8(0x0, A0 + 0x22); // BTST.B	#$00,34(A0)
	DEF_ROMLOC(E2B8): if (!CCR_EQ) goto rom_E2C4; // BNE.B	$E2C4
	DEF_ROMLOC(E2BA): sub_tomem_16(0x10, A1 + 0x8); // SUBI.W	#$0010,8(A1)
	DEF_ROMLOC(E2C0): neg_mem_16(A1 + 0x10); // NEG.W	16(A1)
	DEF_ROMLOC(E2C4): move_tomem_16(0xF, A1 + 0x3E); // MOVE.W	#$000F,62(A1)
	DEF_ROMLOC(E2CA): move_tomem_16(read_16(A1 + 0x10), A1 + 0x14); // MOVE.W	16(A1),20(A1)
	DEF_ROMLOC(E2D0): bchg_tomem_8(0x0, A1 + 0x22); // BCHG.B	#$00,34(A1)
	DEF_ROMLOC(E2D6): btst_tomem_8(0x2, A1 + 0x22); // BTST.B	#$02,34(A1)
	DEF_ROMLOC(E2DC): if (!CCR_EQ) goto rom_E2E4; // BNE.B	$E2E4
	DEF_ROMLOC(E2DE): move_tomem_8(0x0, A1 + 0x1C); // MOVE.B	#$00,28(A1)
	DEF_ROMLOC(E2E4): bclr_tomem_8(0x5, A0 + 0x22); // BCLR.B	#$05,34(A0)
	DEF_ROMLOC(E2EA): bclr_tomem_8(0x5, A1 + 0x22); // BCLR.B	#$05,34(A1)
	DEF_ROMLOC(E2F0): move_toreg_16(0xCC, &D0); // MOVE.W	#$00CC,D0
	DEF_ROMLOC(E2F4): rom_1394(); // JSR	$00001394
	rom_E2FA(); // Detected flow into next function
}
ROMFUNC(rom_E2FA) {
	DEF_ROMLOC(E2FA): move_toreg_32(0xE38C, &A1); // LEA.L	$0000E38C,A1
	rom_ADA2(); // BRA.W	$ADA2
}
ROMFUNC(rom_E304) {
	DEF_ROMLOC(E304): move_tomem_8(0x2, A0 + 0x1D); // MOVE.B	#$02,29(A0)
	DEF_ROMLOC(E30A): sub_tomem_8(0x4, A0 + 0x24); // SUBQ.B	#$04,36(A0)
	DEF_ROMLOC(E30E): return; // RTS
}
ROMFUNC(rom_E310) {
	DEF_ROMLOC(E310): move_toreg_16(0x1B, &D1); // MOVE.W	#$001B,D1
	DEF_ROMLOC(E314): move_toreg_16(0x8, &D2); // MOVE.W	#$0008,D2
	DEF_ROMLOC(E318): move_toreg_16(0x10, &D3); // MOVE.W	#$0010,D3
	DEF_ROMLOC(E31C): move_toreg_16(read_16(A0 + 0x8), &D4); // MOVE.W	8(A0),D4
	DEF_ROMLOC(E320): rom_10062(); // BSR.W	$10062
	DEF_ROMLOC(E324): cmp_tomem_8(0x2, A0 + 0x24); // CMPI.B	#$02,36(A0)
	DEF_ROMLOC(E32A): if (!CCR_EQ) goto rom_E332; // BNE.B	$E332
	DEF_ROMLOC(E32C): move_tomem_8(0xE, A0 + 0x24); // MOVE.B	#$0E,36(A0)
	DEF_ROMLOC(E332): tst_mem_8(A0 + 0x25); // TST.B	37(A0)
	DEF_ROMLOC(E336): if (!CCR_EQ) goto rom_E33C; // BNE.B	$E33C
	DEF_ROMLOC(E338): tst_reg_16(&D4); // TST.W	D4
	DEF_ROMLOC(E33A): if (CCR_MI) goto rom_E33E; // BMI.B	$E33E
	DEF_ROMLOC(E33C): return; // RTS
	DEF_ROMLOC(E33E): add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
	DEF_ROMLOC(E342): sub_tomem_16(0x8, A1 + 0xC); // SUBQ.W	#$08,12(A1)
	DEF_ROMLOC(E346): move_tomem_16(read_16(A0 + 0x30), A1 + 0x12); // MOVE.W	48(A0),18(A1)
	DEF_ROMLOC(E34C): neg_mem_16(A1 + 0x12); // NEG.W	18(A1)
	DEF_ROMLOC(E350): bset_tomem_8(0x1, A1 + 0x22); // BSET.B	#$01,34(A1)
	DEF_ROMLOC(E356): bclr_tomem_8(0x3, A1 + 0x22); // BCLR.B	#$03,34(A1)
	DEF_ROMLOC(E35C): move_tomem_8(0x2, A1 + 0x24); // MOVE.B	#$02,36(A1)
	DEF_ROMLOC(E362): bclr_tomem_8(0x3, A0 + 0x22); // BCLR.B	#$03,34(A0)
	DEF_ROMLOC(E368): clr_mem_8(A0 + 0x25); // CLR.B	37(A0)
	DEF_ROMLOC(E36C): move_toreg_16(0xCC, &D0); // MOVE.W	#$00CC,D0
	DEF_ROMLOC(E370): rom_1394(); // JSR	$00001394
	rom_E376(); // Detected flow into next function
}
ROMFUNC(rom_E376) {
	DEF_ROMLOC(E376): move_toreg_32(0xE38C, &A1); // LEA.L	$0000E38C,A1
	rom_ADA2(); // BRA.W	$ADA2
}
ROMFUNC(rom_E380) {
	DEF_ROMLOC(E380): move_tomem_8(0x1, A0 + 0x1D); // MOVE.B	#$01,29(A0)
	DEF_ROMLOC(E386): sub_tomem_8(0x4, A0 + 0x24); // SUBQ.B	#$04,36(A0)
	DEF_ROMLOC(E38A): return; // RTS
}