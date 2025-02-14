// #define CHECK_STUFF 1
#include "../system.h"
#include "../opcodes.h"

ROMFUNC(rom_19FE2) {
	u8 switchindex = 0;
	DEF_ROMLOC(19FE2): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(19FE4): move_toreg_8(read_8(A0 + 0x24), &D0); switchindex = D0 / 2; // MOVE.B	36(A0),D0
	DEF_ROMLOC(19FE8): move_toreg_16(read_16(0x19FF0 + (s16)(D0 & 0xffff)), &D1); // MOVE.W	6(PC,D0),D1
	// DEF_ROMLOC(19FEC): goto rom_19FF0 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
	DEF_ROMLOC(19FEC):
		switch (switchindex) {
			case 0: rom_19FFC(); break;
			case 1: rom_1A0A0(); break;
			case 2: rom_1A184(); break;
		}
}
ROMFUNC(rom_19FF6) {
	DEF_ROMLOC(19FF6): and_toreg_8(0x4, &D0); // ANDI.B	#$04,D0
	DEF_ROMLOC(19FFA): or_toreg_8(0xFFFFFFFA, &D3); // ORI.B	#$FA,D3
	rom_19FFC(); // Detected flow into next function
}
ROMFUNC(rom_19FFC) {
	DEF_ROMLOC(19FFC): move_toreg_32(0x19FF6, &A2); // LEA.L	-8(PC),A2
	DEF_ROMLOC(1A000): move_tomem_16(0x2160, A0 + 0x8); // MOVE.W	#$2160,8(A0)
	DEF_ROMLOC(1A006): move_tomem_16(0x5A4, A0 + 0xC); // MOVE.W	#$05A4,12(A0)
	DEF_ROMLOC(1A00C): move_tomem_8(0xF, A0 + 0x20); // MOVE.B	#$0F,32(A0)
	DEF_ROMLOC(1A012): move_tomem_8(0x10, A0 + 0x21); // MOVE.B	#$10,33(A0)
	DEF_ROMLOC(1A018): bclr_tomem_8(0x0, A0 + 0x22); // BCLR.B	#$00,34(A0)
	DEF_ROMLOC(1A01E): clr_mem_8(A0 + 0x25); // CLR.B	37(A0)
	DEF_ROMLOC(1A022): move_tomem_8(read_8(A2++), A0 + 0x24); // MOVE.B	(A2)+,36(A0)
	DEF_ROMLOC(1A026): move_tomem_8(read_8(A2++), A0 + 0x1C); // MOVE.B	(A2)+,28(A0)
	DEF_ROMLOC(1A02A): move_tomem_8(read_8(A2++), A0 + 0x18); // MOVE.B	(A2)+,24(A0)
	DEF_ROMLOC(1A02E): move_tomem_32(0x1A1E4, A0 + 0x4); // MOVE.L	#$0001A1E4,4(A0)
	DEF_ROMLOC(1A036): move_tomem_16(0x400, A0 + 0x2); // MOVE.W	#$0400,2(A0)
	DEF_ROMLOC(1A03C): move_tomem_8(0x4, A0 + 0x1); // MOVE.B	#$04,1(A0)
	DEF_ROMLOC(1A042): bset_tomem_8(0x7, A0 + 0x1); // BSET.B	#$07,1(A0)
	DEF_ROMLOC(1A048): move_tomem_8(0x20, A0 + 0x19); // MOVE.B	#$20,25(A0)
	DEF_ROMLOC(1A04E): rom_E130(); // JSR	$0000E130
	DEF_ROMLOC(1A054): if (!CCR_EQ) {rom_1A0A0();return;} // BNE.B	$1A0A0
	DEF_ROMLOC(1A056): move_tomem_32(A0, A1 + 0x34); // MOVE.L	A0,52(A1)
	DEF_ROMLOC(1A05A): move_tomem_8(OBJ_SCRAPEGGMAN, A1 + offsetof(object, id)); // MOVE.B	#$82,(A1)
	DEF_ROMLOC(1A05E): move_tomem_16(0x2130, A1 + 0x8); // MOVE.W	#$2130,8(A1)
	DEF_ROMLOC(1A064): move_tomem_16(0x5BC, A1 + 0xC); // MOVE.W	#$05BC,12(A1)
	DEF_ROMLOC(1A06A): clr_mem_8(A0 + 0x25); // CLR.B	37(A0)
	DEF_ROMLOC(1A06E): move_tomem_8(read_8(A2++), A1 + 0x24); // MOVE.B	(A2)+,36(A1)
	DEF_ROMLOC(1A072): move_tomem_8(read_8(A2++), A1 + 0x1C); // MOVE.B	(A2)+,28(A1)
	DEF_ROMLOC(1A076): move_tomem_8(read_8(A2++), A1 + 0x18); // MOVE.B	(A2)+,24(A1)
	DEF_ROMLOC(1A07A): move_tomem_32(0xC52E, A1 + 0x4); // MOVE.L	#$0000C52E,4(A1)
	DEF_ROMLOC(1A082): move_tomem_16(0x4A4, A1 + 0x2); // MOVE.W	#$04A4,2(A1)
	DEF_ROMLOC(1A088): move_tomem_8(0x4, A1 + 0x1); // MOVE.B	#$04,1(A1)
	DEF_ROMLOC(1A08E): bset_tomem_8(0x7, A1 + 0x1); // BSET.B	#$07,1(A1)
	DEF_ROMLOC(1A094): move_tomem_8(0x10, A1 + 0x19); // MOVE.B	#$10,25(A1)
	DEF_ROMLOC(1A09A): move_tomem_8(0x0, A1 + 0x1A); // MOVE.B	#$00,26(A1)
	rom_1A0A0();
}
ROMFUNC(rom_1A0A0) {
	u8 switchindex = 0;
	DEF_ROMLOC(1A0A0): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(1A0A2): move_toreg_8(read_8(A0 + 0x25), &D0); switchindex = D0 / 2; // MOVE.B	37(A0),D0
	DEF_ROMLOC(1A0A6): move_toreg_16(read_16(0x1A0BE + (s16)(D0 & 0xffff)), &D1); // MOVE.W	22(PC,D0),D1
	// DEF_ROMLOC(1A0AA): rom_1A0BE + (s16)(D1 & 0xffff)(); // JSR	18(PC,D1)
	DEF_ROMLOC(1A0AA):
		switch (switchindex) {
			case 0: rom_1A0C6(); break;
			case 1: rom_1A0EA(); break;
			case 2: rom_1A106(); break;
			case 3: rom_1A0E4(); break;
		}
	DEF_ROMLOC(1A0AE): move_toreg_32(0x1A1B2, &A1); // LEA.L	258(PC),A1
	DEF_ROMLOC(1A0B2): animate_sprite(); // JSR	$0000ADA2
	DEF_ROMLOC(1A0B8): rom_DC92(); return; // JMP	$0000DC92
}
ROMFUNC(rom_1A0C6) {
	DEF_ROMLOC(1A0C6): move_toreg_16(read_16(A0 + 0x8), &D0); // MOVE.W	8(A0),D0
	DEF_ROMLOC(1A0CA): sub_toreg_16(read_16(0xFFFFD008), &D0); // SUB.W	$D008,D0
	DEF_ROMLOC(1A0CE): cmp_toreg_16(0x80, &D0); // CMPI.W	#$0080,D0
	DEF_ROMLOC(1A0D2): if (CCR_CC) {rom_1A0E4();return;} // BCC.B	$1A0E4
	DEF_ROMLOC(1A0D4): add_tomem_8(0x2, A0 + 0x25); // ADDQ.B	#$02,37(A0)
	DEF_ROMLOC(1A0D8): move_tomem_16(0xB4, A0 + 0x3C); // MOVE.W	#$00B4,60(A0)
	DEF_ROMLOC(1A0DE): move_tomem_8(0x1, A0 + 0x1C); // MOVE.B	#$01,28(A0)
	rom_1A0E4();
}
ROMFUNC(rom_1A0E4) {
	DEF_ROMLOC(1A0E4): rom_DC6C(); return; // JMP	$0000DC6C
}
ROMFUNC(rom_1A0EA) {
	DEF_ROMLOC(1A0EA): sub_tomem_16(0x1, A0 + 0x3C); // SUBQ.W	#$01,60(A0)
	DEF_ROMLOC(1A0EE): if (!CCR_EQ) goto rom_1A104; // BNE.B	$1A104
	DEF_ROMLOC(1A0F0): add_tomem_8(0x2, A0 + 0x25); // ADDQ.B	#$02,37(A0)
	DEF_ROMLOC(1A0F4): move_tomem_8(0x2, A0 + 0x1C); // MOVE.B	#$02,28(A0)
	DEF_ROMLOC(1A0FA): add_tomem_16(0x4, A0 + 0xC); // ADDQ.W	#$04,12(A0)
	DEF_ROMLOC(1A0FE): move_tomem_16(0xF, A0 + 0x3C); // MOVE.W	#$000F,60(A0)
	DEF_ROMLOC(1A104): rom_1A0E4(); // BRA.B	$1A0E4
}
ROMFUNC(rom_1A106) {
	DEF_ROMLOC(1A106): sub_tomem_16(0x1, A0 + 0x3C); // SUBQ.W	#$01,60(A0)
	DEF_ROMLOC(1A10A): if (CCR_GT) goto rom_1A180; // BGT.B	$1A180
	DEF_ROMLOC(1A10C): if (!CCR_EQ) goto rom_1A11A; // BNE.B	$1A11A
	DEF_ROMLOC(1A10E): move_tomem_16(0xFFFFFF04, A0 + 0x10); // MOVE.W	#$FF04,16(A0)
	DEF_ROMLOC(1A114): move_tomem_16(0xFFFFFC40, A0 + 0x12); // MOVE.W	#$FC40,18(A0)
	DEF_ROMLOC(1A11A): cmp_tomem_16(0x2132, A0 + 0x8); // CMPI.W	#$2132,8(A0)
	DEF_ROMLOC(1A120): if (CCR_GT) goto rom_1A126; // BGT.B	$1A126
	DEF_ROMLOC(1A122): clr_mem_16(A0 + 0x10); // CLR.W	16(A0)
	DEF_ROMLOC(1A126): add_tomem_16(0x24, A0 + 0x12); // ADDI.W	#$0024,18(A0)
	DEF_ROMLOC(1A12C): tst_mem_16(A0 + 0x12); // TST.W	18(A0)
	DEF_ROMLOC(1A130): if (CCR_MI) goto rom_1A152; // BMI.B	$1A152
	DEF_ROMLOC(1A132): cmp_tomem_16(0x595, A0 + 0xC); // CMPI.W	#$0595,12(A0)
	DEF_ROMLOC(1A138): if (CCR_CS) goto rom_1A152; // BCS.B	$1A152
	DEF_ROMLOC(1A13A): move_tomem_16(0x5357, A0 + 0x28); // MOVE.W	#$5357,40(A0)
	DEF_ROMLOC(1A140): cmp_tomem_16(0x59B, A0 + 0xC); // CMPI.W	#$059B,12(A0)
	DEF_ROMLOC(1A146): if (CCR_CS) goto rom_1A152; // BCS.B	$1A152
	DEF_ROMLOC(1A148): move_tomem_16(0x59B, A0 + 0xC); // MOVE.W	#$059B,12(A0)
	DEF_ROMLOC(1A14E): clr_mem_16(A0 + 0x12); // CLR.W	18(A0)
	DEF_ROMLOC(1A152): move_toreg_16(read_16(A0 + 0x10), &D0); // MOVE.W	16(A0),D0
	DEF_ROMLOC(1A156): or_toreg_16(read_16(A0 + 0x12), &D0); // OR.W	18(A0),D0
	DEF_ROMLOC(1A15A): if (!CCR_EQ) goto rom_1A180; // BNE.B	$1A180
	DEF_ROMLOC(1A15C): move_toreg_32(0xFFFFD000, &A1); // LEA.L	$D000,A1
	DEF_ROMLOC(1A160): move_toreg_32(0x3E, &D0); // MOVEQ.L	$3E,D0
	DEF_ROMLOC(1A162): move_toreg_32(0x40, &D1); // MOVEQ.L	$40,D1
	DEF_ROMLOC(1A164): add_toreg_16(D1, &A1); // ADDA.W	D1,A1
	DEF_ROMLOC(1A166): cmp_tomem_8(OBJ_FALSEFLOOR, A1 + offsetof(object, id)); // CMPI.B	#$83,(A1)
	DEF_ROMLOC(1A16A): if (!CCR_EQ) {dec_reg_16(&D0); if ((D0 & 0xffff) != 0xffff) goto rom_1A164;}; // DBEQ.W	D0,$1A164
	DEF_ROMLOC(1A16E): if (!CCR_EQ) goto rom_1A180; // BNE.B	$1A180
	DEF_ROMLOC(1A170): move_tomem_16(0x474F, A1 + 0x28); // MOVE.W	#$474F,40(A1)
	DEF_ROMLOC(1A176): add_tomem_8(0x2, A0 + 0x25); // ADDQ.B	#$02,37(A0)
	DEF_ROMLOC(1A17A): move_tomem_8(0x1, A0 + 0x1C); // MOVE.B	#$01,28(A0)
	DEF_ROMLOC(1A180): rom_1A0E4(); // BRA.W	$1A0E4
}
ROMFUNC(rom_1A184) {
	u8 switchindex = 0;
	DEF_ROMLOC(1A184): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(1A186): move_toreg_8(read_8(A0 + 0x25), &D0); switchindex = D0 / 2; // MOVE.B	37(A0),D0
	DEF_ROMLOC(1A18A): move_toreg_16(read_16(0x1A192 + (s16)(D0 & 0xffff)), &D0); // MOVE.W	6(PC,D0),D0
	// DEF_ROMLOC(1A18E): goto rom_1A192 + (s16)(D0 & 0xffff); // JMP	2(PC,D0)
	DEF_ROMLOC(1A18E):
		switch (switchindex) {
			case 0: rom_1A196(); break;
			case 1: rom_1A1AC(); break;
		}
}
ROMFUNC(rom_1A192) {
	DEF_ROMLOC(1A192): or_toreg_8(0x1A, &D4); // ORI.B	#$1A,D4
	rom_1A196(); // Detected flow into next function
}
ROMFUNC(rom_1A196) {
	DEF_ROMLOC(1A196): move_toreg_32(read_32(A0 + 0x34), &A1); // MOVEA.L	52(A0),A1
	DEF_ROMLOC(1A19A): cmp_tomem_16(0x5357, A1 + 0x28); // CMPI.W	#$5357,40(A1)
	DEF_ROMLOC(1A1A0): if (!CCR_EQ) {rom_1A1AC();return;} // BNE.B	$1A1AC
	DEF_ROMLOC(1A1A2): move_tomem_8(0x1, A0 + 0x1A); // MOVE.B	#$01,26(A0)
	DEF_ROMLOC(1A1A8): add_tomem_8(0x2, A0 + 0x25); // ADDQ.B	#$02,37(A0)
	rom_1A1AC(); // Detected flow into next function
}
ROMFUNC(rom_1A1AC) {
	DEF_ROMLOC(1A1AC): rom_DC92(); return; // JMP	$0000DC92
}