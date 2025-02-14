// #define CHECK_STUFF 1
#include "../system.h"
#include "../opcodes.h"

ROMFUNC(rom_B542) {
	u8 switchindex = 0;
	DEF_ROMLOC(B542): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(B544): move_toreg_8(read_8(A0 + 0x24), &D0); switchindex = D0 / 2; // MOVE.B	36(A0),D0
	DEF_ROMLOC(B548): move_toreg_16(read_16(0xB550 + (s16)(D0 & 0xffff)), &D1); // MOVE.W	6(PC,D0),D1
	// DEF_ROMLOC(B54C): goto rom_B550 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
	DEF_ROMLOC(B54C):
		switch (switchindex) {
			case 0: rom_B560(); break;
			case 1: rom_B5BE(); break;
		}
}
ROMFUNC(rom_B560) {
	DEF_ROMLOC(B560): add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
	DEF_ROMLOC(B564): move_tomem_32(0xB95E, A0 + 0x4); // MOVE.L	#$0000B95E,4(A0)
	DEF_ROMLOC(B56C): move_tomem_16(0xFFFFC000, A0 + 0x2); // MOVE.W	#$C000,2(A0)
	DEF_ROMLOC(B572): move_tomem_8(0x4, A0 + 0x1); // MOVE.B	#$04,1(A0)
	DEF_ROMLOC(B578): move_tomem_8(0x5, A0 + 0x18); // MOVE.B	#$05,24(A0)
	DEF_ROMLOC(B57E): move_tomem_16(read_16(A0 + 0xC), A0 + 0x2C); // MOVE.W	12(A0),44(A0)
	DEF_ROMLOC(B584): move_tomem_16(read_16(A0 + 0x8), A0 + 0x2A); // MOVE.W	8(A0),42(A0)
	DEF_ROMLOC(B58A): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(B58C): move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B	40(A0),D0
	DEF_ROMLOC(B590): lsr_toreg_16(0x2, &D0); // LSR.W	#$02,D0
	DEF_ROMLOC(B592): and_toreg_16(0x1C, &D0); // ANDI.W	#$001C,D0
	DEF_ROMLOC(B596): move_toreg_32(0xB554 + (s16)(D0 & 0xffff), &A1); // LEA.L	-68(PC,D0),A1
	DEF_ROMLOC(B59A): move_toreg_16(read_16((A1 += 2, A1 - 2)), &D0); // MOVE.W	(A1)+,D0
	DEF_ROMLOC(B59C): move_toreg_32(0xB554 + (s16)(D0 & 0xffff), &A2); // LEA.L	-74(PC,D0),A2
	DEF_ROMLOC(B5A0): move_tomem_32(A2, A0 + 0x30); // MOVE.L	A2,48(A0)
	DEF_ROMLOC(B5A4): move_tomem_8(read_8(A1++), A0 + 0x1A); // MOVE.B	(A1)+,26(A0)
	DEF_ROMLOC(B5A8): move_tomem_8(read_8(A1), A0 + 0x19); // MOVE.B	(A1),25(A0)
	DEF_ROMLOC(B5AC): and_tomem_8(0xF, A0 + 0x28); // ANDI.B	#$0F,40(A0)
	DEF_ROMLOC(B5B2): move_tomem_8(0x40, A0 + 0x16); // MOVE.B	#$40,22(A0)
	DEF_ROMLOC(B5B8): bset_tomem_8(0x4, A0 + 0x1); // BSET.B	#$04,1(A0)
	rom_B5BE(); // Detected flow into next function
}
ROMFUNC(rom_B5BE) {
	DEF_ROMLOC(B5BE): rom_B628(); // BSR.W	$B628
	DEF_ROMLOC(B5C2): tst_mem_8(A0 + 0x25); // TST.B	37(A0)
	DEF_ROMLOC(B5C6): if (CCR_EQ) goto rom_B5FE; // BEQ.B	$B5FE
	DEF_ROMLOC(B5C8): move_toreg_32(0x0, &D1); // MOVEQ.L	$00,D1
	DEF_ROMLOC(B5CA): move_toreg_8(read_8(A0 + 0x19), &D1); // MOVE.B	25(A0),D1
	DEF_ROMLOC(B5CE): add_toreg_16(0xB, &D1); // ADDI.W	#$000B,D1
	DEF_ROMLOC(B5D2): rom_7C3E(); // BSR.W	$7C3E
	DEF_ROMLOC(B5D6): btst_tomem_8(0x3, A1 + 0x22); // BTST.B	#$03,34(A1)
	DEF_ROMLOC(B5DC): if (!CCR_EQ) goto rom_B5E6; // BNE.W	$B5E6
	DEF_ROMLOC(B5E0): clr_mem_8(A0 + 0x25); // CLR.B	37(A0)
	goto rom_B620; // BRA.B	$B620
	DEF_ROMLOC(B5E6): move_toreg_32(0x0, &D1); // MOVEQ.L	$00,D1
	DEF_ROMLOC(B5E8): move_toreg_8(read_8(A0 + 0x19), &D1); // MOVE.B	25(A0),D1
	DEF_ROMLOC(B5EC): add_toreg_16(0xB, &D1); // ADDI.W	#$000B,D1
	DEF_ROMLOC(B5F0): move_toreg_32(read_32(A0 + 0x30), &A2); // MOVEA.L	48(A0),A2
	DEF_ROMLOC(B5F4): move_toreg_16(read_16(A0 + 0x8), &D2); // MOVE.W	8(A0),D2
	DEF_ROMLOC(B5F8): rom_8BA8(); // BSR.W	$8BA8
	goto rom_B620; // BRA.B	$B620
	DEF_ROMLOC(B5FE): move_toreg_32(0x0, &D1); // MOVEQ.L	$00,D1
	DEF_ROMLOC(B600): move_toreg_8(read_8(A0 + 0x19), &D1); // MOVE.B	25(A0),D1
	DEF_ROMLOC(B604): add_toreg_16(0xB, &D1); // ADDI.W	#$000B,D1
	DEF_ROMLOC(B608): move_toreg_16(0x20, &D2); // MOVE.W	#$0020,D2
	DEF_ROMLOC(B60C): cmp_tomem_8(0x2, A0 + 0x1A); // CMPI.B	#$02,26(A0)
	DEF_ROMLOC(B612): if (!CCR_EQ) goto rom_B618; // BNE.B	$B618
	DEF_ROMLOC(B614): move_toreg_16(0x30, &D2); // MOVE.W	#$0030,D2
	DEF_ROMLOC(B618): move_toreg_32(read_32(A0 + 0x30), &A2); // MOVEA.L	48(A0),A2
	DEF_ROMLOC(B61C): rom_100EE(); // BSR.W	$100EE
	DEF_ROMLOC(B620): rom_DC92(); // BSR.W	$DC92
	rom_B744(); // BRA.W	$B744
}
ROMFUNC(rom_B628) {
	u8 switchindex = 0;
	DEF_ROMLOC(B628): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(B62A): move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B	40(A0),D0
	DEF_ROMLOC(B62E): and_toreg_16(0x7, &D0); switchindex = D0; // ANDI.W	#$0007,D0
	DEF_ROMLOC(B632): add_toreg_16(D0, &D0); // ADD.W	D0,D0
	DEF_ROMLOC(B634): move_toreg_16(read_16(0xB63C + (s16)(D0 & 0xffff)), &D1); // MOVE.W	6(PC,D0),D1
	// DEF_ROMLOC(B638): goto rom_B63C + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
	DEF_ROMLOC(B638):
		switch (switchindex) {
			case 0: rom_B648(); break;
			case 1: rom_B64A(); break;
			case 2: rom_B654(); break;
			case 3: rom_B65E(); break;
			case 4: rom_B668(); break;
			case 5: rom_B688(); break;
		}
}
ROMFUNC(rom_B648) {
	DEF_ROMLOC(B648): return; // RTS
}
ROMFUNC(rom_B64A) {
	DEF_ROMLOC(B64A): move_toreg_8(read_8(0xFFFFFE60), &D0); // MOVE.B	$FE60,D0
	DEF_ROMLOC(B64E): move_toreg_16(0x20, &D1); // MOVE.W	#$0020,D1
	rom_B670(); // BRA.B	$B670
}
ROMFUNC(rom_B654) {
	DEF_ROMLOC(B654): move_toreg_8(read_8(0xFFFFFE64), &D0); // MOVE.B	$FE64,D0
	DEF_ROMLOC(B658): move_toreg_16(0x30, &D1); // MOVE.W	#$0030,D1
	rom_B670(); // BRA.B	$B670
}
ROMFUNC(rom_B65E) {
	DEF_ROMLOC(B65E): move_toreg_8(read_8(0xFFFFFE68), &D0); // MOVE.B	$FE68,D0
	DEF_ROMLOC(B662): move_toreg_16(0x40, &D1); // MOVE.W	#$0040,D1
	rom_B670(); // BRA.B	$B670
}
ROMFUNC(rom_B668) {
	DEF_ROMLOC(B668): move_toreg_8(read_8(0xFFFFFE6C), &D0); // MOVE.B	$FE6C,D0
	DEF_ROMLOC(B66C): move_toreg_16(0x60, &D1); // MOVE.W	#$0060,D1
	rom_B670(); // Detected flow into next function
}
ROMFUNC(rom_B670) {
	DEF_ROMLOC(B670): btst_tomem_8(0x3, A0 + 0x28); // BTST.B	#$03,40(A0)
	DEF_ROMLOC(B676): if (CCR_EQ) goto rom_B67C; // BEQ.B	$B67C
	DEF_ROMLOC(B678): neg_reg_16(&D0); // NEG.W	D0
	DEF_ROMLOC(B67A): add_toreg_16(D1, &D0); // ADD.W	D1,D0
	DEF_ROMLOC(B67C): move_toreg_16(read_16(A0 + 0x2C), &D1); // MOVE.W	44(A0),D1
	DEF_ROMLOC(B680): sub_toreg_16(D0, &D1); // SUB.W	D0,D1
	DEF_ROMLOC(B682): move_tomem_16(D1, A0 + 0xC); // MOVE.W	D1,12(A0)
	DEF_ROMLOC(B686): return; // RTS
}
ROMFUNC(rom_B688) {
	DEF_ROMLOC(B688): move_toreg_8(read_8(A0 + 0x34), &D0); // MOVE.B	52(A0),D0
	DEF_ROMLOC(B68C): tst_mem_8(A0 + 0x25); // TST.B	37(A0)
	DEF_ROMLOC(B690): if (!CCR_EQ) goto rom_B69A; // BNE.B	$B69A
	DEF_ROMLOC(B692): sub_toreg_8(0x2, &D0); // SUBQ.B	#$02,D0
	DEF_ROMLOC(B694): if (CCR_CC) goto rom_B6A6; // BCC.B	$B6A6
	DEF_ROMLOC(B696): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	goto rom_B6A6; // BRA.B	$B6A6
	DEF_ROMLOC(B69A): add_toreg_8(0x4, &D0); // ADDQ.B	#$04,D0
	DEF_ROMLOC(B69C): cmp_toreg_8(0x40, &D0); // CMPI.B	#$40,D0
	DEF_ROMLOC(B6A0): if (CCR_CS) goto rom_B6A6; // BCS.B	$B6A6
	DEF_ROMLOC(B6A2): move_toreg_8(0x40, &D0); // MOVE.B	#$40,D0
	DEF_ROMLOC(B6A6): move_tomem_8(D0, A0 + 0x34); // MOVE.B	D0,52(A0)
	DEF_ROMLOC(B6AA): rom_29D2(); // JSR	$000029D2
	DEF_ROMLOC(B6B0): lsr_toreg_16(0x4, &D0); // LSR.W	#$04,D0
	DEF_ROMLOC(B6B2): move_toreg_16(D0, &D1); // MOVE.W	D0,D1
	DEF_ROMLOC(B6B4): add_toreg_16(read_16(A0 + 0x2C), &D0); // ADD.W	44(A0),D0
	DEF_ROMLOC(B6B8): move_tomem_16(D0, A0 + 0xC); // MOVE.W	D0,12(A0)
	DEF_ROMLOC(B6BC): cmp_tomem_8(0x20, A0 + 0x34); // CMPI.B	#$20,52(A0)
	DEF_ROMLOC(B6C2): if (!CCR_EQ) goto rom_B704; // BNE.B	$B704
	DEF_ROMLOC(B6C4): tst_mem_8(A0 + 0x35); // TST.B	53(A0)
	DEF_ROMLOC(B6C8): if (!CCR_EQ) goto rom_B704; // BNE.B	$B704
	DEF_ROMLOC(B6CA): move_tomem_8(0x1, A0 + 0x35); // MOVE.B	#$01,53(A0)
	DEF_ROMLOC(B6D0): rom_E130(); // BSR.W	$E130
	DEF_ROMLOC(B6D4): if (!CCR_EQ) goto rom_B704; // BNE.B	$B704
	DEF_ROMLOC(B6D6): move_tomem_8(OBJ_GRASSFIRE, A1 + offsetof(object, id)); // MOVE.B	#$35,0(A1)
	DEF_ROMLOC(B6DC): move_tomem_16(read_16(A0 + 0x8), A1 + 0x8); // MOVE.W	8(A0),8(A1)
	DEF_ROMLOC(B6E2): move_tomem_16(read_16(A0 + 0x2C), A1 + 0x2C); // MOVE.W	44(A0),44(A1)
	DEF_ROMLOC(B6E8): add_tomem_16(0x8, A1 + 0x2C); // ADDQ.W	#$08,44(A1)
	DEF_ROMLOC(B6EC): sub_tomem_16(0x3, A1 + 0x2C); // SUBQ.W	#$03,44(A1)
	DEF_ROMLOC(B6F0): sub_tomem_16(0x40, A1 + 0x8); // SUBI.W	#$0040,8(A1)
	DEF_ROMLOC(B6F6): move_tomem_32(read_32(A0 + 0x30), A1 + 0x30); // MOVE.L	48(A0),48(A1)
	DEF_ROMLOC(B6FC): move_tomem_32(A0, A1 + 0x38); // MOVE.L	A0,56(A1)
	DEF_ROMLOC(B700): move_toreg_32(A0, &A2); // MOVEA.L	A0,A2
	DEF_ROMLOC(B702): rom_B726(); // BSR.B	$B726
	DEF_ROMLOC(B704): move_toreg_32(0x0, &D2); // MOVEQ.L	$00,D2
	DEF_ROMLOC(B706): move_toreg_32(A0 + 0x36, &A2); // LEA.L	54(A0),A2
	DEF_ROMLOC(B70A): move_toreg_8(read_8(A2++), &D2); // MOVE.B	(A2)+,D2
	DEF_ROMLOC(B70C): sub_toreg_8(0x1, &D2); // SUBQ.B	#$01,D2
	DEF_ROMLOC(B70E): if (CCR_CS) goto rom_B724; // BCS.B	$B724
	DEF_ROMLOC(B710): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(B712): move_toreg_8(read_8(A2++), &D0); // MOVE.B	(A2)+,D0
	DEF_ROMLOC(B714): lsl_toreg_16(0x6, &D0); // LSL.W	#$06,D0
	DEF_ROMLOC(B716): add_toreg_16(0xFFFFD000, &D0); // ADDI.W	#$D000,D0
	DEF_ROMLOC(B71A): move_toreg_16(D0, &A1); // MOVEA.W	D0,A1
	DEF_ROMLOC(B71C): move_tomem_16(D1, A1 + 0x3C); // MOVE.W	D1,60(A1)
	DEF_ROMLOC(B720): dec_reg_16(&D2); if ((D2 & 0xffff) != 0xffff) goto rom_B710; // DBF.W	D2,$B710
	DEF_ROMLOC(B724): return; // RTS
}
ROMFUNC(rom_B726) {
	DEF_ROMLOC(B726): move_toreg_32(A2 + 0x36, &A2); // LEA.L	54(A2),A2
	DEF_ROMLOC(B72A): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(B72C): move_toreg_8(read_8(A2), &D0); // MOVE.B	(A2),D0
	DEF_ROMLOC(B72E): add_tomem_8(0x1, A2); // ADDQ.B	#$01,(A2)
	DEF_ROMLOC(B730): move_toreg_32((s32)A2 + (s8)0x1 + (s16)D0, &A2); // LEA.L	1(A2,D0),A2
	DEF_ROMLOC(B734): move_toreg_16(A1, &D0); // MOVE.W	A1,D0
	DEF_ROMLOC(B736): sub_toreg_16(0xFFFFD000, &D0); // SUBI.W	#$D000,D0
	DEF_ROMLOC(B73A): lsr_toreg_16(0x6, &D0); // LSR.W	#$06,D0
	DEF_ROMLOC(B73C): and_toreg_16(0x7F, &D0); // ANDI.W	#$007F,D0
	DEF_ROMLOC(B740): move_tomem_8(D0, A2); // MOVE.B	D0,(A2)
	DEF_ROMLOC(B742): return; // RTS
}
ROMFUNC(rom_B744) {
	DEF_ROMLOC(B744): tst_mem_8(A0 + 0x35); // TST.B	53(A0)
	DEF_ROMLOC(B748): if (CCR_EQ) goto rom_B750; // BEQ.B	$B750
	DEF_ROMLOC(B74A): tst_mem_8(A0 + 0x1); // TST.B	1(A0)
	DEF_ROMLOC(B74E): if (CCR_PL) goto rom_B770; // BPL.B	$B770
	DEF_ROMLOC(B750): move_toreg_16(read_16(A0 + 0x2A), &D0); // MOVE.W	42(A0),D0
	DEF_ROMLOC(B754): and_toreg_16(0xFFFFFF80, &D0); // ANDI.W	#$FF80,D0
	DEF_ROMLOC(B758): move_toreg_16(read_16(0xFFFFF700), &D1); // MOVE.W	$F700,D1
	DEF_ROMLOC(B75C): sub_toreg_16(0x80, &D1); // SUBI.W	#$0080,D1
	DEF_ROMLOC(B760): and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
	DEF_ROMLOC(B764): sub_toreg_16(D1, &D0); // SUB.W	D1,D0
	DEF_ROMLOC(B766): cmp_toreg_16(0x280, &D0); // CMPI.W	#$0280,D0
	DEF_ROMLOC(B76A): if (CCR_HI) {rom_DCCE();return;} // BHI.W	$DCCE
	DEF_ROMLOC(B76E): return; // RTS
	DEF_ROMLOC(B770): move_toreg_32(0x0, &D2); // MOVEQ.L	$00,D2
	rom_B772(); // Detected flow into next function
}
ROMFUNC(rom_B772) {
	DEF_ROMLOC(B772): move_toreg_32(A0 + 0x36, &A2); // LEA.L	54(A0),A2
	DEF_ROMLOC(B776): move_toreg_8(read_8(A2), &D2); // MOVE.B	(A2),D2
	DEF_ROMLOC(B778): clr_mem_8(A2++); // CLR.B	(A2)+
	DEF_ROMLOC(B77A): sub_toreg_8(0x1, &D2); // SUBQ.B	#$01,D2
	DEF_ROMLOC(B77C): if (CCR_CS) goto rom_B7A0; // BCS.B	$B7A0
	DEF_ROMLOC(B77E): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(B780): move_toreg_8(read_8(A2), &D0); // MOVE.B	(A2),D0
	DEF_ROMLOC(B782): clr_mem_8(A2++); // CLR.B	(A2)+
	DEF_ROMLOC(B784): lsl_toreg_16(0x6, &D0); // LSL.W	#$06,D0
	DEF_ROMLOC(B786): add_toreg_16(0xFFFFD000, &D0); // ADDI.W	#$D000,D0
	DEF_ROMLOC(B78A): move_toreg_16(D0, &A1); // MOVEA.W	D0,A1
	DEF_ROMLOC(B78C): rom_DCD0(); // BSR.W	$DCD0
	DEF_ROMLOC(B790): dec_reg_16(&D2); if ((D2 & 0xffff) != 0xffff) goto rom_B77E; // DBF.W	D2,$B77E
	DEF_ROMLOC(B794): move_tomem_8(0x0, A0 + 0x35); // MOVE.B	#$00,53(A0)
	DEF_ROMLOC(B79A): move_tomem_8(0x0, A0 + 0x34); // MOVE.B	#$00,52(A0)
	DEF_ROMLOC(B7A0): return; // RTS
}