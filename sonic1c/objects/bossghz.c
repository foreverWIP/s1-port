// #define CHECK_STUFF(loc) 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_17EAC) {
	u8 switchindex = 0;
	DEF_ROMLOC(17EAC): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(17EAE): move_toreg_8(read_8(A0 + 0x24), &D0); switchindex = D0 / 2; // MOVE.B	36(A0),D0
	DEF_ROMLOC(17EB2): move_toreg_16(read_16(0x17EBA + (s16)(D0 & 0xffff)), &D1); // MOVE.W	6(PC,D0),D1
	// DEF_ROMLOC(17EB6): goto rom_17EBA + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
	DEF_ROMLOC(17EB6):
		switch (switchindex) {
			case 0: rom_17EC8(); break;
			case 1: rom_17F36(); break;
			case 2: rom_181D0(); break;
			case 3: rom_181D0(); break;
		}
}
ROMFUNC(rom_17EC2) {
	u8 switchindex = 0;
	DEF_ROMLOC(17EC8): move_toreg_32(0x17EC2, &A2);
	DEF_ROMLOC(17ECA): or_toreg_8(0xFFFFFFC2, &D1); // ORI.B	#$C2,D1
	DEF_ROMLOC(17ECE): move_toreg_32(A0, &A1); // MOVEA.L	A0,A1
	DEF_ROMLOC(17ED0): move_toreg_32(0x2, &D1); // MOVEQ.L	$02,D1
	DEF_ROMLOC(17ED2): goto rom_17EDC; // BRA.B	$17EDC
	DEF_ROMLOC(17ED4): rom_E130(); // JSR	$0000E130
	DEF_ROMLOC(17EDA): if (!CCR_EQ) goto rom_17F1E; // BNE.B	$17F1E
	DEF_ROMLOC(17EDC): move_tomem_8(read_8(A2++), A1 + 0x24); // MOVE.B	(A2)+,36(A1)
	DEF_ROMLOC(17EE0): move_tomem_8(0x3D, A1 + 0x0); // MOVE.B	#$3D,0(A1)
	DEF_ROMLOC(17EE6): move_tomem_16(read_16(A0 + 0x8), A1 + 0x8); // MOVE.W	8(A0),8(A1)
	DEF_ROMLOC(17EEC): move_tomem_16(read_16(A0 + 0xC), A1 + 0xC); // MOVE.W	12(A0),12(A1)
	DEF_ROMLOC(17EF2): move_tomem_32(0x184B8, A1 + 0x4); // MOVE.L	#$000184B8,4(A1)
	DEF_ROMLOC(17EFA): move_tomem_16(0x400, A1 + 0x2); // MOVE.W	#$0400,2(A1)
	DEF_ROMLOC(17F00): move_tomem_8(0x4, A1 + 0x1); // MOVE.B	#$04,1(A1)
	DEF_ROMLOC(17F06): move_tomem_8(0x20, A1 + 0x19); // MOVE.B	#$20,25(A1)
	DEF_ROMLOC(17F0C): move_tomem_8(0x3, A1 + 0x18); // MOVE.B	#$03,24(A1)
	DEF_ROMLOC(17F12): move_tomem_8(read_8(A2++), A1 + 0x1C); // MOVE.B	(A2)+,28(A1)
	DEF_ROMLOC(17F16): move_tomem_32(A0, A1 + 0x34); // MOVE.L	A0,52(A1)
	DEF_ROMLOC(17F1A): dec_reg_16(&D1); if ((D1 & 0xffff) != 0xffff) goto rom_17ED4; // DBF.W	D1,$17ED4
	DEF_ROMLOC(17F1E): move_tomem_16(read_16(A0 + 0x8), A0 + 0x30); // MOVE.W	8(A0),48(A0)
	DEF_ROMLOC(17F24): move_tomem_16(read_16(A0 + 0xC), A0 + 0x38); // MOVE.W	12(A0),56(A0)
	DEF_ROMLOC(17F2A): move_tomem_8(0xF, A0 + 0x20); // MOVE.B	#$0F,32(A0)
	DEF_ROMLOC(17F30): move_tomem_8(0x8, A0 + 0x21); // MOVE.B	#$08,33(A0)
	DEF_ROMLOC(17F36): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(17F38): move_toreg_8(read_8(A0 + 0x25), &D0); switchindex = D0 / 2; // MOVE.B	37(A0),D0
	DEF_ROMLOC(17F3C): move_toreg_16(read_16(0x17F68 + (s16)(D0 & 0xffff)), &D1); // MOVE.W	42(PC,D0),D1
	// DEF_ROMLOC(17F40): rom_17F68 + (s16)(D1 & 0xffff)(); // JSR	38(PC,D1)
	DEF_ROMLOC(17F40):
		switch (switchindex) {
			case 0: rom_17F76(); break;
			case 1: rom_18076(); break;
			case 2: rom_180C6(); break;
			case 3: rom_18100(); break;
			case 4: rom_18126(); break;
			case 5: rom_18158(); break;
			case 6: rom_181A2(); break;
		}
	DEF_ROMLOC(17F44): move_toreg_32(0x18468, &A1); // LEA.L	$00018468,A1
	DEF_ROMLOC(17F4A): rom_ADA2(); // JSR	$0000ADA2
	DEF_ROMLOC(17F50): move_toreg_8(read_8(A0 + 0x22), &D0); // MOVE.B	34(A0),D0
	DEF_ROMLOC(17F54): and_toreg_8(0x3, &D0); // ANDI.B	#$03,D0
	DEF_ROMLOC(17F58): and_tomem_8(0xFFFFFFFC, A0 + 0x1); // ANDI.B	#$FC,1(A0)
	DEF_ROMLOC(17F5E): or_tomem_8(D0, A0 + 0x1); // OR.B	D0,1(A0)
	DEF_ROMLOC(17F62): {rom_DC92();return;} // JMP	$0000DC92
}
ROMFUNC(rom_17EC8) {
	DEF_ROMLOC(17EC8): move_toreg_32(0x17EC2, &A2); // LEA.L	$00017EC2,A2
	DEF_ROMLOC(17ECE): move_toreg_32(A0, &A1); // MOVEA.L	A0,A1
	DEF_ROMLOC(17ED0): move_toreg_32(0x2, &D1); // MOVEQ.L	$02,D1
	goto rom_17EDC; // BRA.B	$17EDC
	DEF_ROMLOC(17ED4): rom_E130(); // JSR	$0000E130
	DEF_ROMLOC(17EDA): if (!CCR_EQ) goto rom_17F1E; // BNE.B	$17F1E
	DEF_ROMLOC(17EDC): move_tomem_8(read_8(A2++), A1 + 0x24); // MOVE.B	(A2)+,36(A1)
	DEF_ROMLOC(17EE0): move_tomem_8(0x3D, A1 + 0x0); // MOVE.B	#$3D,0(A1)
	DEF_ROMLOC(17EE6): move_tomem_16(read_16(A0 + 0x8), A1 + 0x8); // MOVE.W	8(A0),8(A1)
	DEF_ROMLOC(17EEC): move_tomem_16(read_16(A0 + 0xC), A1 + 0xC); // MOVE.W	12(A0),12(A1)
	DEF_ROMLOC(17EF2): move_tomem_32(0x184B8, A1 + 0x4); // MOVE.L	#$000184B8,4(A1)
	DEF_ROMLOC(17EFA): move_tomem_16(0x400, A1 + 0x2); // MOVE.W	#$0400,2(A1)
	DEF_ROMLOC(17F00): move_tomem_8(0x4, A1 + 0x1); // MOVE.B	#$04,1(A1)
	DEF_ROMLOC(17F06): move_tomem_8(0x20, A1 + 0x19); // MOVE.B	#$20,25(A1)
	DEF_ROMLOC(17F0C): move_tomem_8(0x3, A1 + 0x18); // MOVE.B	#$03,24(A1)
	DEF_ROMLOC(17F12): move_tomem_8(read_8(A2++), A1 + 0x1C); // MOVE.B	(A2)+,28(A1)
	DEF_ROMLOC(17F16): move_tomem_32(A0, A1 + 0x34); // MOVE.L	A0,52(A1)
	DEF_ROMLOC(17F1A): dec_reg_16(&D1); if ((D1 & 0xffff) != 0xffff) goto rom_17ED4; // DBF.W	D1,$17ED4
	DEF_ROMLOC(17F1E): move_tomem_16(read_16(A0 + 0x8), A0 + 0x30); // MOVE.W	8(A0),48(A0)
	DEF_ROMLOC(17F24): move_tomem_16(read_16(A0 + 0xC), A0 + 0x38); // MOVE.W	12(A0),56(A0)
	DEF_ROMLOC(17F2A): move_tomem_8(0xF, A0 + 0x20); // MOVE.B	#$0F,32(A0)
	DEF_ROMLOC(17F30): move_tomem_8(0x8, A0 + 0x21); // MOVE.B	#$08,33(A0)
	rom_17F36(); // Detected flow into next function
}
ROMFUNC(rom_17F36) {
	u8 switchindex = 0;
	DEF_ROMLOC(17F36): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(17F38): move_toreg_8(read_8(A0 + 0x25), &D0); switchindex = D0 / 2; // MOVE.B	37(A0),D0
	DEF_ROMLOC(17F3C): move_toreg_16(read_16(0x17F68 + (s16)(D0 & 0xffff)), &D1); // MOVE.W	42(PC,D0),D1
	// DEF_ROMLOC(17F40): rom_17F68 + (s16)(D1 & 0xffff)(); // JSR	38(PC,D1)
	DEF_ROMLOC(17F40):
	switch (switchindex) {
			case 0: rom_17F76(); break;
			case 1: rom_18076(); break;
			case 2: rom_180C6(); break;
			case 3: rom_18100(); break;
			case 4: rom_18126(); break;
			case 5: rom_18158(); break;
			case 6: rom_181A2(); break;
		}
	DEF_ROMLOC(17F44): move_toreg_32(0x18468, &A1); // LEA.L	$00018468,A1
	DEF_ROMLOC(17F4A): rom_ADA2(); // JSR	$0000ADA2
	DEF_ROMLOC(17F50): move_toreg_8(read_8(A0 + 0x22), &D0); // MOVE.B	34(A0),D0
	DEF_ROMLOC(17F54): and_toreg_8(0x3, &D0); // ANDI.B	#$03,D0
	DEF_ROMLOC(17F58): and_tomem_8(0xFFFFFFFC, A0 + 0x1); // ANDI.B	#$FC,1(A0)
	DEF_ROMLOC(17F5E): or_tomem_8(D0, A0 + 0x1); // OR.B	D0,1(A0)
	DEF_ROMLOC(17F62): {rom_DC92();return;} // JMP	$0000DC92
}
ROMFUNC(rom_17F76) {
	DEF_ROMLOC(17F76): move_tomem_16(0x100, A0 + 0x12); // MOVE.W	#$0100,18(A0)
	DEF_ROMLOC(17F7C): rom_18050(); // BSR.W	$18050
	DEF_ROMLOC(17F80): cmp_tomem_16(0x338, A0 + 0x38); // CMPI.W	#$0338,56(A0)
	DEF_ROMLOC(17F86): if (!CCR_EQ) {rom_17F92();return;} // BNE.B	$17F92
	DEF_ROMLOC(17F88): move_tomem_16(0x0, A0 + 0x12); // MOVE.W	#$0000,18(A0)
	DEF_ROMLOC(17F8E): add_tomem_8(0x2, A0 + 0x25); // ADDQ.B	#$02,37(A0)
	rom_17F92();
}
ROMFUNC(rom_17F92) {
	DEF_ROMLOC(17F92): move_toreg_8(read_8(A0 + 0x3F), &D0); // MOVE.B	63(A0),D0
	DEF_ROMLOC(17F96): rom_29D2(); // JSR	$000029D2
	DEF_ROMLOC(17F9C): asr_toreg_16(0x6, &D0); // ASR.W	#$06,D0
	DEF_ROMLOC(17F9E): add_toreg_16(read_16(A0 + 0x38), &D0); // ADD.W	56(A0),D0
	DEF_ROMLOC(17FA2): move_tomem_16(D0, A0 + 0xC); // MOVE.W	D0,12(A0)
	DEF_ROMLOC(17FA6): move_tomem_16(read_16(A0 + 0x30), A0 + 0x8); // MOVE.W	48(A0),8(A0)
	DEF_ROMLOC(17FAC): add_tomem_8(0x2, A0 + 0x3F); // ADDQ.B	#$02,63(A0)
	DEF_ROMLOC(17FB0): cmp_tomem_8(0x8, A0 + 0x25); // CMPI.B	#$08,37(A0)
	DEF_ROMLOC(17FB6): if (CCR_CC) goto rom_17FF6; // BCC.B	$17FF6
	DEF_ROMLOC(17FB8): tst_mem_8(A0 + 0x22); // TST.B	34(A0)
	DEF_ROMLOC(17FBC): if (CCR_MI) goto rom_17FF8; // BMI.B	$17FF8
	DEF_ROMLOC(17FBE): tst_mem_8(A0 + 0x20); // TST.B	32(A0)
	DEF_ROMLOC(17FC2): if (!CCR_EQ) goto rom_17FF6; // BNE.B	$17FF6
	DEF_ROMLOC(17FC4): tst_mem_8(A0 + 0x3E); // TST.B	62(A0)
	DEF_ROMLOC(17FC8): if (!CCR_EQ) goto rom_17FDA; // BNE.B	$17FDA
	DEF_ROMLOC(17FCA): move_tomem_8(0x20, A0 + 0x3E); // MOVE.B	#$20,62(A0)
	DEF_ROMLOC(17FD0): move_toreg_16(0xAC, &D0); // MOVE.W	#$00AC,D0
	DEF_ROMLOC(17FD4): rom_1394(); // JSR	$00001394
	DEF_ROMLOC(17FDA): move_toreg_32(0xFFFFFB22, &A1); // LEA.L	$FB22,A1
	DEF_ROMLOC(17FDE): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(17FE0): tst_mem_16(A1); // TST.W	(A1)
	DEF_ROMLOC(17FE2): if (!CCR_EQ) goto rom_17FE8; // BNE.B	$17FE8
	DEF_ROMLOC(17FE4): move_toreg_16(0xEEE, &D0); // MOVE.W	#$0EEE,D0
	DEF_ROMLOC(17FE8): move_tomem_16(D0, A1); // MOVE.W	D0,(A1)
	DEF_ROMLOC(17FEA): sub_tomem_8(0x1, A0 + 0x3E); // SUBQ.B	#$01,62(A0)
	DEF_ROMLOC(17FEE): if (!CCR_EQ) goto rom_17FF6; // BNE.B	$17FF6
	DEF_ROMLOC(17FF0): move_tomem_8(0xF, A0 + 0x20); // MOVE.B	#$0F,32(A0)
	DEF_ROMLOC(17FF6): return; // RTS
	DEF_ROMLOC(17FF8): move_toreg_32(0x64, &D0); // MOVEQ.L	$64,D0
	DEF_ROMLOC(17FFA): rom_1CE42(); // BSR.W	$1CE42
	DEF_ROMLOC(17FFE): move_tomem_8(0x8, A0 + 0x25); // MOVE.B	#$08,37(A0)
	DEF_ROMLOC(18004): move_tomem_16(0xB3, A0 + 0x3C); // MOVE.W	#$00B3,60(A0)
	DEF_ROMLOC(1800A): return; // RTS
}
ROMFUNC(rom_1800C) {
	DEF_ROMLOC(1800C): move_toreg_8(read_8(0xFFFFFE0F), &D0); // MOVE.B	$FE0F,D0
	DEF_ROMLOC(18010): and_toreg_8(0x7, &D0); // ANDI.B	#$07,D0
	DEF_ROMLOC(18014): if (!CCR_EQ) goto rom_1804E; // BNE.B	$1804E
	DEF_ROMLOC(18016): rom_E11A(); // JSR	$0000E11A
	DEF_ROMLOC(1801C): if (!CCR_EQ) goto rom_1804E; // BNE.B	$1804E
	DEF_ROMLOC(1801E): move_tomem_8(0x3F, A1 + 0x0); // MOVE.B	#$3F,0(A1)
	DEF_ROMLOC(18024): move_tomem_16(read_16(A0 + 0x8), A1 + 0x8); // MOVE.W	8(A0),8(A1)
	DEF_ROMLOC(1802A): move_tomem_16(read_16(A0 + 0xC), A1 + 0xC); // MOVE.W	12(A0),12(A1)
	DEF_ROMLOC(18030): rom_29AC(); // JSR	$000029AC
	DEF_ROMLOC(18036): move_toreg_16(D0, &D1); // MOVE.W	D0,D1
	DEF_ROMLOC(18038): move_toreg_32(0x0, &D1); // MOVEQ.L	$00,D1
	DEF_ROMLOC(1803A): move_toreg_8(D0, &D1); // MOVE.B	D0,D1
	DEF_ROMLOC(1803C): lsr_toreg_8(0x2, &D1); // LSR.B	#$02,D1
	DEF_ROMLOC(1803E): sub_toreg_16(0x20, &D1); // SUBI.W	#$0020,D1
	DEF_ROMLOC(18042): add_tomem_16(D1, A1 + 0x8); // ADD.W	D1,8(A1)
	DEF_ROMLOC(18046): lsr_toreg_16(0x8, &D0); // LSR.W	#$08,D0
	DEF_ROMLOC(18048): lsr_toreg_8(0x3, &D0); // LSR.B	#$03,D0
	DEF_ROMLOC(1804A): add_tomem_16(D0, A1 + 0xC); // ADD.W	D0,12(A1)
	DEF_ROMLOC(1804E): return; // RTS
}
ROMFUNC(rom_18050) {
	DEF_ROMLOC(18050): move_toreg_32(read_32(A0 + 0x30), &D2); // MOVE.L	48(A0),D2
	DEF_ROMLOC(18054): move_toreg_32(read_32(A0 + 0x38), &D3); // MOVE.L	56(A0),D3
	DEF_ROMLOC(18058): move_toreg_16(read_16(A0 + 0x10), &D0); // MOVE.W	16(A0),D0
	DEF_ROMLOC(1805C): ext_reg_32(&D0); // EXT.L	D0
	DEF_ROMLOC(1805E): asl_toreg_32(0x8, &D0); // ASL.L	#$08,D0
	DEF_ROMLOC(18060): add_toreg_32(D0, &D2); // ADD.L	D0,D2
	DEF_ROMLOC(18062): move_toreg_16(read_16(A0 + 0x12), &D0); // MOVE.W	18(A0),D0
	DEF_ROMLOC(18066): ext_reg_32(&D0); // EXT.L	D0
	DEF_ROMLOC(18068): asl_toreg_32(0x8, &D0); // ASL.L	#$08,D0
	DEF_ROMLOC(1806A): add_toreg_32(D0, &D3); // ADD.L	D0,D3
	DEF_ROMLOC(1806C): move_tomem_32(D2, A0 + 0x30); // MOVE.L	D2,48(A0)
	DEF_ROMLOC(18070): move_tomem_32(D3, A0 + 0x38); // MOVE.L	D3,56(A0)
	DEF_ROMLOC(18074): return; // RTS
}
ROMFUNC(rom_18076) {
	DEF_ROMLOC(18076): move_tomem_16(0xFFFFFF00, A0 + 0x10); // MOVE.W	#$FF00,16(A0)
	DEF_ROMLOC(1807C): move_tomem_16(0xFFFFFFC0, A0 + 0x12); // MOVE.W	#$FFC0,18(A0)
	DEF_ROMLOC(18082): rom_18050(); // BSR.W	$18050
	DEF_ROMLOC(18086): cmp_tomem_16(0x2A00, A0 + 0x30); // CMPI.W	#$2A00,48(A0)
	DEF_ROMLOC(1808C): if (!CCR_EQ) goto rom_180C2; // BNE.B	$180C2
	DEF_ROMLOC(1808E): move_tomem_16(0x0, A0 + 0x10); // MOVE.W	#$0000,16(A0)
	DEF_ROMLOC(18094): move_tomem_16(0x0, A0 + 0x12); // MOVE.W	#$0000,18(A0)
	DEF_ROMLOC(1809A): add_tomem_8(0x2, A0 + 0x25); // ADDQ.B	#$02,37(A0)
	DEF_ROMLOC(1809E): rom_E130(); // JSR	$0000E130
	DEF_ROMLOC(180A4): if (!CCR_EQ) goto rom_180BC; // BNE.B	$180BC
	DEF_ROMLOC(180A6): move_tomem_8(0x48, A1 + 0x0); // MOVE.B	#$48,0(A1)
	DEF_ROMLOC(180AC): move_tomem_16(read_16(A0 + 0x30), A1 + 0x8); // MOVE.W	48(A0),8(A1)
	DEF_ROMLOC(180B2): move_tomem_16(read_16(A0 + 0x38), A1 + 0xC); // MOVE.W	56(A0),12(A1)
	DEF_ROMLOC(180B8): move_tomem_32(A0, A1 + 0x34); // MOVE.L	A0,52(A1)
	DEF_ROMLOC(180BC): move_tomem_16(0x77, A0 + 0x3C); // MOVE.W	#$0077,60(A0)
	DEF_ROMLOC(180C2): rom_17F92(); // BRA.W	$17F92
}
ROMFUNC(rom_180C6) {
	DEF_ROMLOC(180C6): sub_tomem_16(0x1, A0 + 0x3C); // SUBQ.W	#$01,60(A0)
	DEF_ROMLOC(180CA): if (CCR_PL) goto rom_180F0; // BPL.B	$180F0
	DEF_ROMLOC(180CC): add_tomem_8(0x2, A0 + 0x25); // ADDQ.B	#$02,37(A0)
	DEF_ROMLOC(180D0): move_tomem_16(0x3F, A0 + 0x3C); // MOVE.W	#$003F,60(A0)
	DEF_ROMLOC(180D6): move_tomem_16(0x100, A0 + 0x10); // MOVE.W	#$0100,16(A0)
	DEF_ROMLOC(180DC): cmp_tomem_16(0x2A00, A0 + 0x30); // CMPI.W	#$2A00,48(A0)
	DEF_ROMLOC(180E2): if (!CCR_EQ) goto rom_180F0; // BNE.B	$180F0
	DEF_ROMLOC(180E4): move_tomem_16(0x7F, A0 + 0x3C); // MOVE.W	#$007F,60(A0)
	DEF_ROMLOC(180EA): move_tomem_16(0x40, A0 + 0x10); // MOVE.W	#$0040,16(A0)
	DEF_ROMLOC(180F0): btst_tomem_8(0x0, A0 + 0x22); // BTST.B	#$00,34(A0)
	DEF_ROMLOC(180F6): if (!CCR_EQ) goto rom_180FC; // BNE.B	$180FC
	DEF_ROMLOC(180F8): neg_mem_16(A0 + 0x10); // NEG.W	16(A0)
	DEF_ROMLOC(180FC): rom_17F92(); // BRA.W	$17F92
}
ROMFUNC(rom_18100) {
	DEF_ROMLOC(18100): sub_tomem_16(0x1, A0 + 0x3C); // SUBQ.W	#$01,60(A0)
	DEF_ROMLOC(18104): if (CCR_MI) goto rom_1810C; // BMI.B	$1810C
	DEF_ROMLOC(18106): rom_18050(); // BSR.W	$18050
	rom_18122(); // BRA.B	$18122
	DEF_ROMLOC(1810C): bchg_tomem_8(0x0, A0 + 0x22); // BCHG.B	#$00,34(A0)
	DEF_ROMLOC(18112): move_tomem_16(0x3F, A0 + 0x3C); // MOVE.W	#$003F,60(A0)
	DEF_ROMLOC(18118): sub_tomem_8(0x2, A0 + 0x25); // SUBQ.B	#$02,37(A0)
	DEF_ROMLOC(1811C): move_tomem_16(0x0, A0 + 0x10); // MOVE.W	#$0000,16(A0)
	rom_18122(); // Detected flow into next function
}
ROMFUNC(rom_18122) {
	rom_17F92(); // BRA.W	$17F92
}
ROMFUNC(rom_18126) {
	DEF_ROMLOC(18126): sub_tomem_16(0x1, A0 + 0x3C); // SUBQ.W	#$01,60(A0)
	DEF_ROMLOC(1812A): if (CCR_MI) goto rom_18130; // BMI.B	$18130
	rom_1800C(); // BRA.W	$1800C
	DEF_ROMLOC(18130): bset_tomem_8(0x0, A0 + 0x22); // BSET.B	#$00,34(A0)
	DEF_ROMLOC(18136): bclr_tomem_8(0x7, A0 + 0x22); // BCLR.B	#$07,34(A0)
	DEF_ROMLOC(1813C): clr_mem_16(A0 + 0x10); // CLR.W	16(A0)
	DEF_ROMLOC(18140): add_tomem_8(0x2, A0 + 0x25); // ADDQ.B	#$02,37(A0)
	DEF_ROMLOC(18144): move_tomem_16(0xFFFFFFDA, A0 + 0x3C); // MOVE.W	#$FFDA,60(A0)
	DEF_ROMLOC(1814A): tst_mem_8(0xFFFFF7A7); // TST.B	$F7A7
	DEF_ROMLOC(1814E): if (!CCR_EQ) goto rom_18156; // BNE.B	$18156
	DEF_ROMLOC(18150): move_tomem_8(0x1, 0xFFFFF7A7); // MOVE.B	#$01,$F7A7
	DEF_ROMLOC(18156): return; // RTS
}
ROMFUNC(rom_18158) {
	DEF_ROMLOC(18158): add_tomem_16(0x1, A0 + 0x3C); // ADDQ.W	#$01,60(A0)
	DEF_ROMLOC(1815C): if (CCR_EQ) goto rom_18168; // BEQ.B	$18168
	DEF_ROMLOC(1815E): if (CCR_PL) goto rom_1816E; // BPL.B	$1816E
	DEF_ROMLOC(18160): add_tomem_16(0x18, A0 + 0x12); // ADDI.W	#$0018,18(A0)
	goto rom_1819A; // BRA.B	$1819A
	DEF_ROMLOC(18168): clr_mem_16(A0 + 0x12); // CLR.W	18(A0)
	goto rom_1819A; // BRA.B	$1819A
	DEF_ROMLOC(1816E): cmp_tomem_16(0x30, A0 + 0x3C); // CMPI.W	#$0030,60(A0)
	DEF_ROMLOC(18174): if (CCR_CS) goto rom_18186; // BCS.B	$18186
	DEF_ROMLOC(18176): if (CCR_EQ) goto rom_1818C; // BEQ.B	$1818C
	DEF_ROMLOC(18178): cmp_tomem_16(0x38, A0 + 0x3C); // CMPI.W	#$0038,60(A0)
	DEF_ROMLOC(1817E): if (CCR_CS) goto rom_1819A; // BCS.B	$1819A
	DEF_ROMLOC(18180): add_tomem_8(0x2, A0 + 0x25); // ADDQ.B	#$02,37(A0)
	goto rom_1819A; // BRA.B	$1819A
	DEF_ROMLOC(18186): sub_tomem_16(0x8, A0 + 0x12); // SUBQ.W	#$08,18(A0)
	goto rom_1819A; // BRA.B	$1819A
	DEF_ROMLOC(1818C): clr_mem_16(A0 + 0x12); // CLR.W	18(A0)
	DEF_ROMLOC(18190): move_toreg_16(0x81, &D0); // MOVE.W	#$0081,D0
	DEF_ROMLOC(18194): rom_138E(); // JSR	$0000138E
	DEF_ROMLOC(1819A): rom_18050(); // BSR.W	$18050
	rom_17F92(); // BRA.W	$17F92
}
ROMFUNC(rom_181A2) {
	DEF_ROMLOC(181A2): move_tomem_16(0x400, A0 + 0x10); // MOVE.W	#$0400,16(A0)
	DEF_ROMLOC(181A8): move_tomem_16(0xFFFFFFC0, A0 + 0x12); // MOVE.W	#$FFC0,18(A0)
	DEF_ROMLOC(181AE): cmp_tomem_16(0x2AC0, 0xFFFFF72A); // CMPI.W	#$2AC0,$F72A
	DEF_ROMLOC(181B4): if (CCR_EQ) goto rom_181BC; // BEQ.B	$181BC
	DEF_ROMLOC(181B6): add_tomem_16(0x2, 0xFFFFF72A); // ADDQ.W	#$02,$F72A
	goto rom_181C2; // BRA.B	$181C2
	DEF_ROMLOC(181BC): tst_mem_8(A0 + 0x1); // TST.B	1(A0)
	DEF_ROMLOC(181C0): if (CCR_PL) goto rom_181CA; // BPL.B	$181CA
	DEF_ROMLOC(181C2): rom_18050(); // BSR.W	$18050
	rom_17F92(); // BRA.W	$17F92
	DEF_ROMLOC(181CA): {rom_DCCE();return;} // JMP	$0000DCCE
}
ROMFUNC(rom_181D0) {
	DEF_ROMLOC(181D0): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(181D2): move_toreg_32(0x1, &D1); // MOVEQ.L	$01,D1
	DEF_ROMLOC(181D4): move_toreg_32(read_32(A0 + 0x34), &A1); // MOVEA.L	52(A0),A1
	DEF_ROMLOC(181D8): move_toreg_8(read_8(A1 + 0x25), &D0); // MOVE.B	37(A1),D0
	DEF_ROMLOC(181DC): sub_toreg_8(0x4, &D0); // SUBQ.B	#$04,D0
	DEF_ROMLOC(181DE): if (!CCR_EQ) goto rom_181EA; // BNE.B	$181EA
	DEF_ROMLOC(181E0): cmp_tomem_16(0x2A00, A1 + 0x30); // CMPI.W	#$2A00,48(A1)
	DEF_ROMLOC(181E6): if (!CCR_EQ) goto rom_181F2; // BNE.B	$181F2
	DEF_ROMLOC(181E8): move_toreg_32(0x4, &D1); // MOVEQ.L	$04,D1
	DEF_ROMLOC(181EA): sub_toreg_8(0x6, &D0); // SUBQ.B	#$06,D0
	DEF_ROMLOC(181EC): if (CCR_MI) goto rom_181F2; // BMI.B	$181F2
	DEF_ROMLOC(181EE): move_toreg_32(0xA, &D1); // MOVEQ.L	$0A,D1
	goto rom_18206; // BRA.B	$18206
	DEF_ROMLOC(181F2): tst_mem_8(A1 + 0x20); // TST.B	32(A1)
	DEF_ROMLOC(181F6): if (!CCR_EQ) goto rom_181FC; // BNE.B	$181FC
	DEF_ROMLOC(181F8): move_toreg_32(0x5, &D1); // MOVEQ.L	$05,D1
	goto rom_18206; // BRA.B	$18206
	DEF_ROMLOC(181FC): cmp_tomem_8(0x4, 0xFFFFD024); // CMPI.B	#$04,$D024
	DEF_ROMLOC(18202): if (CCR_CS) goto rom_18206; // BCS.B	$18206
	DEF_ROMLOC(18204): move_toreg_32(0x4, &D1); // MOVEQ.L	$04,D1
	DEF_ROMLOC(18206): move_tomem_8(D1, A0 + 0x1C); // MOVE.B	D1,28(A0)
	DEF_ROMLOC(1820A): sub_toreg_8(0x2, &D0); // SUBQ.B	#$02,D0
	DEF_ROMLOC(1820C): if (!CCR_EQ) goto rom_1821A; // BNE.B	$1821A
	DEF_ROMLOC(1820E): move_tomem_8(0x6, A0 + 0x1C); // MOVE.B	#$06,28(A0)
	DEF_ROMLOC(18214): tst_mem_8(A0 + 0x1); // TST.B	1(A0)
	DEF_ROMLOC(18218): if (CCR_PL) goto rom_1821C; // BPL.B	$1821C
	DEF_ROMLOC(1821A): rom_18256(); // BRA.B	$18256
	DEF_ROMLOC(1821C): {rom_DCCE();return;} // JMP	$0000DCCE
}
ROMFUNC(rom_18222) {
	DEF_ROMLOC(18222): move_tomem_8(0x7, A0 + 0x1C); // MOVE.B	#$07,28(A0)
	DEF_ROMLOC(18228): move_toreg_32(read_32(A0 + 0x34), &A1); // MOVEA.L	52(A0),A1
	DEF_ROMLOC(1822C): cmp_tomem_8(0xC, A1 + 0x25); // CMPI.B	#$0C,37(A1)
	DEF_ROMLOC(18232): if (!CCR_EQ) goto rom_18242; // BNE.B	$18242
	DEF_ROMLOC(18234): move_tomem_8(0xB, A0 + 0x1C); // MOVE.B	#$0B,28(A0)
	DEF_ROMLOC(1823A): tst_mem_8(A0 + 0x1); // TST.B	1(A0)
	DEF_ROMLOC(1823E): if (CCR_PL) goto rom_18250; // BPL.B	$18250
	goto rom_1824E; // BRA.B	$1824E
	DEF_ROMLOC(18242): move_toreg_16(read_16(A1 + 0x10), &D0); // MOVE.W	16(A1),D0
	DEF_ROMLOC(18246): if (CCR_EQ) goto rom_1824E; // BEQ.B	$1824E
	DEF_ROMLOC(18248): move_tomem_8(0x8, A0 + 0x1C); // MOVE.B	#$08,28(A0)
	DEF_ROMLOC(1824E): rom_18256(); // BRA.B	$18256
	DEF_ROMLOC(18250): {rom_DCCE();return;} // JMP	$0000DCCE
}
ROMFUNC(rom_18256) {
	DEF_ROMLOC(18256): move_toreg_32(read_32(A0 + 0x34), &A1); // MOVEA.L	52(A0),A1
	DEF_ROMLOC(1825A): move_tomem_16(read_16(A1 + 0x8), A0 + 0x8); // MOVE.W	8(A1),8(A0)
	DEF_ROMLOC(18260): move_tomem_16(read_16(A1 + 0xC), A0 + 0xC); // MOVE.W	12(A1),12(A0)
	DEF_ROMLOC(18266): move_tomem_8(read_8(A1 + 0x22), A0 + 0x22); // MOVE.B	34(A1),34(A0)
	DEF_ROMLOC(1826C): move_toreg_32(0x18468, &A1); // LEA.L	$00018468,A1
	DEF_ROMLOC(18272): rom_ADA2(); // JSR	$0000ADA2
	DEF_ROMLOC(18278): move_toreg_8(read_8(A0 + 0x22), &D0); // MOVE.B	34(A0),D0
	DEF_ROMLOC(1827C): and_toreg_8(0x3, &D0); // ANDI.B	#$03,D0
	DEF_ROMLOC(18280): and_tomem_8(0xFFFFFFFC, A0 + 0x1); // ANDI.B	#$FC,1(A0)
	DEF_ROMLOC(18286): or_tomem_8(D0, A0 + 0x1); // OR.B	D0,1(A0)
	DEF_ROMLOC(1828A): {rom_DC92();return;} // JMP	$0000DC92
}