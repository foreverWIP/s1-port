// #define CHECK_STUFF(loc) 1
#include "system.h"
#include "opcodes.h"

ROMFUNC(rom_1D91E);
ROMFUNC(rom_1D6E6) {
	u8 switchindex = 0;
	DEF_ROMLOC(1D6E6): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(1D6E8): move_toreg_8(read_8(0xFFFFFE08), &D0); switchindex = D0 / 2; // MOVE.B	$FE08,D0
	DEF_ROMLOC(1D6EC): move_toreg_16(read_16(0x1D6F4 + (s16)(D0 & 0xffff)), &D1); // MOVE.W	6(PC,D0),D1
	// DEF_ROMLOC(1D6F0): goto rom_1D6F4 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
	DEF_ROMLOC(1D6F0):
		switch (switchindex) {
			case 0: rom_1D6F8(); break;
			case 1: rom_1D77A(); break;
		}
}
ROMFUNC(rom_1D6F8) {
	DEF_ROMLOC(1D6F8): add_tomem_8(0x2, 0xFFFFFE08); // ADDQ.B	#$02,$FE08
	DEF_ROMLOC(1D6FC): move_tomem_16(read_16(0xFFFFF72C), 0xFFFFFEF0); // MOVE.W	$F72C,$FEF0
	DEF_ROMLOC(1D702): move_tomem_16(read_16(0xFFFFF726), 0xFFFFFEF2); // MOVE.W	$F726,$FEF2
	DEF_ROMLOC(1D708): move_tomem_16(0x0, 0xFFFFF72C); // MOVE.W	#$0000,$F72C
	DEF_ROMLOC(1D70E): move_tomem_16(0x720, 0xFFFFF726); // MOVE.W	#$0720,$F726
	DEF_ROMLOC(1D714): and_tomem_16(0x7FF, 0xFFFFD00C); // ANDI.W	#$07FF,$D00C
	DEF_ROMLOC(1D71A): and_tomem_16(0x7FF, 0xFFFFF704); // ANDI.W	#$07FF,$F704
	DEF_ROMLOC(1D720): and_tomem_16(0x3FF, 0xFFFFF70C); // ANDI.W	#$03FF,$F70C
	DEF_ROMLOC(1D726): move_tomem_8(0x0, A0 + 0x1A); // MOVE.B	#$00,26(A0)
	DEF_ROMLOC(1D72C): move_tomem_8(0x0, A0 + 0x1C); // MOVE.B	#$00,28(A0)
	DEF_ROMLOC(1D732): cmp_tomem_8(0x10, 0xFFFFF600); // CMPI.B	#$10,$F600
	DEF_ROMLOC(1D738): if (!CCR_EQ) goto rom_1D74A; // BNE.B	$1D74A
	DEF_ROMLOC(1D73A): move_tomem_16(0x0, 0xFFFFF782); // MOVE.W	#$0000,$F782
	DEF_ROMLOC(1D740): move_tomem_16(0x0, 0xFFFFF780); // MOVE.W	#$0000,$F780
	DEF_ROMLOC(1D746): move_toreg_32(0x6, &D0); // MOVEQ.L	$06,D0
	goto rom_1D750; // BRA.B	$1D750
	DEF_ROMLOC(1D74A): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(1D74C): move_toreg_8(read_8(0xFFFFFE10), &D0); // MOVE.B	$FE10,D0
	DEF_ROMLOC(1D750): move_toreg_32(0x1D93A, &A2); // LEA.L	$0001D93A,A2
	DEF_ROMLOC(1D756): add_toreg_16(D0, &D0); // ADD.W	D0,D0
	DEF_ROMLOC(1D758): add_toreg_16(read_16((s32)A2 + (s8)0x0 + (s16)D0), &A2); // ADDA.W	0(A2,D0),A2
	DEF_ROMLOC(1D75C): move_toreg_16(read_16((A2 += 2, A2 - 2)), &D6); // MOVE.W	(A2)+,D6
	DEF_ROMLOC(1D75E): cmp_toreg_8(read_8(0xFFFFFE06), &D6); // CMP.B	$FE06,D6
	DEF_ROMLOC(1D762): if (CCR_HI) goto rom_1D76A; // BHI.B	$1D76A
	DEF_ROMLOC(1D764): move_tomem_8(0x0, 0xFFFFFE06); // MOVE.B	#$00,$FE06
	DEF_ROMLOC(1D76A): rom_1D91E(); // BSR.W	$1D91E
	DEF_ROMLOC(1D76E): move_tomem_8(0xC, 0xFFFFFE0A); // MOVE.B	#$0C,$FE0A
	DEF_ROMLOC(1D774): move_tomem_8(0x1, 0xFFFFFE0B); // MOVE.B	#$01,$FE0B
	rom_1D77A();
}
ROMFUNC(rom_1D77A) {
	DEF_ROMLOC(1D77A): move_toreg_32(0x6, &D0); // MOVEQ.L	$06,D0
	DEF_ROMLOC(1D77C): cmp_tomem_8(0x10, 0xFFFFF600); // CMPI.B	#$10,$F600
	DEF_ROMLOC(1D782): if (CCR_EQ) goto rom_1D78A; // BEQ.B	$1D78A
	DEF_ROMLOC(1D784): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(1D786): move_toreg_8(read_8(0xFFFFFE10), &D0); // MOVE.B	$FE10,D0
	DEF_ROMLOC(1D78A): move_toreg_32(0x1D93A, &A2); // LEA.L	$0001D93A,A2
	DEF_ROMLOC(1D790): add_toreg_16(D0, &D0); // ADD.W	D0,D0
	DEF_ROMLOC(1D792): add_toreg_16(read_16((s32)A2 + (s8)0x0 + (s16)D0), &A2); // ADDA.W	0(A2,D0),A2
	DEF_ROMLOC(1D796): move_toreg_16(read_16((A2 += 2, A2 - 2)), &D6); // MOVE.W	(A2)+,D6
	DEF_ROMLOC(1D798): rom_1D7A2(); // BSR.W	$1D7A2
	DEF_ROMLOC(1D79C): rom_DC92(); // JMP	$0000DC92
}
ROMFUNC(rom_1D7A2) {
	DEF_ROMLOC(1D7A2): move_toreg_32(0x0, &D4); // MOVEQ.L	$00,D4
	DEF_ROMLOC(1D7A4): move_toreg_16(0x1, &D1); // MOVE.W	#$0001,D1
	DEF_ROMLOC(1D7A8): move_toreg_8(read_8(0xFFFFF605), &D4); // MOVE.B	$F605,D4
	DEF_ROMLOC(1D7AC): and_toreg_16(0xF, &D4); // ANDI.W	#$000F,D4
	DEF_ROMLOC(1D7B0): if (!CCR_EQ) goto rom_1D7E4; // BNE.B	$1D7E4
	DEF_ROMLOC(1D7B2): move_toreg_8(read_8(0xFFFFF604), &D0); // MOVE.B	$F604,D0
	DEF_ROMLOC(1D7B6): and_toreg_16(0xF, &D0); // ANDI.W	#$000F,D0
	DEF_ROMLOC(1D7BA): if (!CCR_EQ) goto rom_1D7CC; // BNE.B	$1D7CC
	DEF_ROMLOC(1D7BC): move_tomem_8(0xC, 0xFFFFFE0A); // MOVE.B	#$0C,$FE0A
	DEF_ROMLOC(1D7C2): move_tomem_8(0xF, 0xFFFFFE0B); // MOVE.B	#$0F,$FE0B
	goto rom_1D83A; // BRA.W	$1D83A
	DEF_ROMLOC(1D7CC): sub_tomem_8(0x1, 0xFFFFFE0A); // SUBQ.B	#$01,$FE0A
	DEF_ROMLOC(1D7D0): if (!CCR_EQ) goto rom_1D7E8; // BNE.B	$1D7E8
	DEF_ROMLOC(1D7D2): move_tomem_8(0x1, 0xFFFFFE0A); // MOVE.B	#$01,$FE0A
	DEF_ROMLOC(1D7D8): add_tomem_8(0x1, 0xFFFFFE0B); // ADDQ.B	#$01,$FE0B
	DEF_ROMLOC(1D7DC): if (!CCR_EQ) goto rom_1D7E4; // BNE.B	$1D7E4
	DEF_ROMLOC(1D7DE): move_tomem_8(0xFFFFFFFF, 0xFFFFFE0B); // MOVE.B	#$FF,$FE0B
	DEF_ROMLOC(1D7E4): move_toreg_8(read_8(0xFFFFF604), &D4); // MOVE.B	$F604,D4
	DEF_ROMLOC(1D7E8): move_toreg_32(0x0, &D1); // MOVEQ.L	$00,D1
	DEF_ROMLOC(1D7EA): move_toreg_8(read_8(0xFFFFFE0B), &D1); // MOVE.B	$FE0B,D1
	DEF_ROMLOC(1D7EE): add_toreg_16(0x1, &D1); // ADDQ.W	#$01,D1
	DEF_ROMLOC(1D7F0): swap_reg_16(&D1); // SWAP.W	D1
	DEF_ROMLOC(1D7F2): asr_toreg_32(0x4, &D1); // ASR.L	#$04,D1
	DEF_ROMLOC(1D7F4): move_toreg_32(read_32(A0 + 0xC), &D2); // MOVE.L	12(A0),D2
	DEF_ROMLOC(1D7F8): move_toreg_32(read_32(A0 + 0x8), &D3); // MOVE.L	8(A0),D3
	DEF_ROMLOC(1D7FC): btst_toreg_32(0x0, &D4); // BTST.L	#$00,D4
	DEF_ROMLOC(1D800): if (CCR_EQ) goto rom_1D808; // BEQ.B	$1D808
	DEF_ROMLOC(1D802): sub_toreg_32(D1, &D2); // SUB.L	D1,D2
	DEF_ROMLOC(1D804): if (CCR_CC) goto rom_1D808; // BCC.B	$1D808
	DEF_ROMLOC(1D806): move_toreg_32(0x0, &D2); // MOVEQ.L	$00,D2
	DEF_ROMLOC(1D808): btst_toreg_32(0x1, &D4); // BTST.L	#$01,D4
	DEF_ROMLOC(1D80C): if (CCR_EQ) goto rom_1D81E; // BEQ.B	$1D81E
	DEF_ROMLOC(1D80E): add_toreg_32(D1, &D2); // ADD.L	D1,D2
	DEF_ROMLOC(1D810): cmp_toreg_32(0x7FF0000, &D2); // CMPI.L	#$07FF0000,D2
	DEF_ROMLOC(1D816): if (CCR_CS) goto rom_1D81E; // BCS.B	$1D81E
	DEF_ROMLOC(1D818): move_toreg_32(0x7FF0000, &D2); // MOVE.L	#$07FF0000,D2
	DEF_ROMLOC(1D81E): btst_toreg_32(0x2, &D4); // BTST.L	#$02,D4
	DEF_ROMLOC(1D822): if (CCR_EQ) goto rom_1D82A; // BEQ.B	$1D82A
	DEF_ROMLOC(1D824): sub_toreg_32(D1, &D3); // SUB.L	D1,D3
	DEF_ROMLOC(1D826): if (CCR_CC) goto rom_1D82A; // BCC.B	$1D82A
	DEF_ROMLOC(1D828): move_toreg_32(0x0, &D3); // MOVEQ.L	$00,D3
	DEF_ROMLOC(1D82A): btst_toreg_32(0x3, &D4); // BTST.L	#$03,D4
	DEF_ROMLOC(1D82E): if (CCR_EQ) goto rom_1D832; // BEQ.B	$1D832
	DEF_ROMLOC(1D830): add_toreg_32(D1, &D3); // ADD.L	D1,D3
	DEF_ROMLOC(1D832): move_tomem_32(D2, A0 + 0xC); // MOVE.L	D2,12(A0)
	DEF_ROMLOC(1D836): move_tomem_32(D3, A0 + 0x8); // MOVE.L	D3,8(A0)
	DEF_ROMLOC(1D83A): btst_tomem_8(0x6, 0xFFFFF604); // BTST.B	#$06,$F604
	DEF_ROMLOC(1D840): if (CCR_EQ) goto rom_1D872; // BEQ.B	$1D872
	DEF_ROMLOC(1D842): btst_tomem_8(0x5, 0xFFFFF605); // BTST.B	#$05,$F605
	DEF_ROMLOC(1D848): if (CCR_EQ) goto rom_1D856; // BEQ.B	$1D856
	DEF_ROMLOC(1D84A): sub_tomem_8(0x1, 0xFFFFFE06); // SUBQ.B	#$01,$FE06
	DEF_ROMLOC(1D84E): if (CCR_CC) goto rom_1D86E; // BCC.B	$1D86E
	DEF_ROMLOC(1D850): add_tomem_8(D6, 0xFFFFFE06); // ADD.B	D6,$FE06
	goto rom_1D86E; // BRA.B	$1D86E
	DEF_ROMLOC(1D856): btst_tomem_8(0x6, 0xFFFFF605); // BTST.B	#$06,$F605
	DEF_ROMLOC(1D85C): if (CCR_EQ) goto rom_1D872; // BEQ.B	$1D872
	DEF_ROMLOC(1D85E): add_tomem_8(0x1, 0xFFFFFE06); // ADDQ.B	#$01,$FE06
	DEF_ROMLOC(1D862): cmp_toreg_8(read_8(0xFFFFFE06), &D6); // CMP.B	$FE06,D6
	DEF_ROMLOC(1D866): if (CCR_HI) goto rom_1D86E; // BHI.B	$1D86E
	DEF_ROMLOC(1D868): move_tomem_8(0x0, 0xFFFFFE06); // MOVE.B	#$00,$FE06
	DEF_ROMLOC(1D86E): {rom_1D91E();return;} // BRA.W	$1D91E
	DEF_ROMLOC(1D872): btst_tomem_8(0x5, 0xFFFFF605); // BTST.B	#$05,$F605
	DEF_ROMLOC(1D878): if (CCR_EQ) goto rom_1D8B6; // BEQ.B	$1D8B6
	DEF_ROMLOC(1D87A): rom_E11A(); // JSR	$0000E11A
	DEF_ROMLOC(1D880): if (!CCR_EQ) goto rom_1D8B6; // BNE.B	$1D8B6
	DEF_ROMLOC(1D882): move_tomem_16(read_16(A0 + 0x8), A1 + 0x8); // MOVE.W	8(A0),8(A1)
	DEF_ROMLOC(1D888): move_tomem_16(read_16(A0 + 0xC), A1 + 0xC); // MOVE.W	12(A0),12(A1)
	DEF_ROMLOC(1D88E): move_tomem_8(read_8(A0 + 0x4), A1 + 0x0); // MOVE.B	4(A0),0(A1)
	DEF_ROMLOC(1D894): move_tomem_8(read_8(A0 + 0x1), A1 + 0x1); // MOVE.B	1(A0),1(A1)
	DEF_ROMLOC(1D89A): move_tomem_8(read_8(A0 + 0x1), A1 + 0x22); // MOVE.B	1(A0),34(A1)
	DEF_ROMLOC(1D8A0): and_tomem_8(0x7F, A1 + 0x22); // ANDI.B	#$7F,34(A1)
	DEF_ROMLOC(1D8A6): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(1D8A8): move_toreg_8(read_8(0xFFFFFE06), &D0); // MOVE.B	$FE06,D0
	DEF_ROMLOC(1D8AC): lsl_toreg_16(0x3, &D0); // LSL.W	#$03,D0
	DEF_ROMLOC(1D8AE): move_tomem_8(read_8((s32)A2 + (s8)0x4 + (s16)D0), A1 + 0x28); // MOVE.B	4(A2,D0),40(A1)
	DEF_ROMLOC(1D8B4): return; // RTS
	DEF_ROMLOC(1D8B6): btst_tomem_8(0x4, 0xFFFFF605); // BTST.B	#$04,$F605
	DEF_ROMLOC(1D8BC): if (CCR_EQ) goto rom_1D91C; // BEQ.B	$1D91C
	DEF_ROMLOC(1D8BE): move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
	DEF_ROMLOC(1D8C0): move_tomem_16(D0, 0xFFFFFE08); // MOVE.W	D0,$FE08
	DEF_ROMLOC(1D8C4): move_tomem_32(0x21CF4, 0xFFFFD004); // MOVE.L	#$00021CF4,$D004
	DEF_ROMLOC(1D8CC): move_tomem_16(0x780, 0xFFFFD002); // MOVE.W	#$0780,$D002
	DEF_ROMLOC(1D8D2): move_tomem_8(D0, 0xFFFFD01C); // MOVE.B	D0,$D01C
	DEF_ROMLOC(1D8D6): move_tomem_16(D0, A0 + 0xA); // MOVE.W	D0,10(A0)
	DEF_ROMLOC(1D8DA): move_tomem_16(D0, A0 + 0xE); // MOVE.W	D0,14(A0)
	DEF_ROMLOC(1D8DE): move_tomem_16(read_16(0xFFFFFEF0), 0xFFFFF72C); // MOVE.W	$FEF0,$F72C
	DEF_ROMLOC(1D8E4): move_tomem_16(read_16(0xFFFFFEF2), 0xFFFFF726); // MOVE.W	$FEF2,$F726
	DEF_ROMLOC(1D8EA): cmp_tomem_8(0x10, 0xFFFFF600); // CMPI.B	#$10,$F600
	DEF_ROMLOC(1D8F0): if (!CCR_EQ) goto rom_1D91C; // BNE.B	$1D91C
	DEF_ROMLOC(1D8F2): clr_mem_16(0xFFFFF780); // CLR.W	$F780
	DEF_ROMLOC(1D8F6): move_tomem_16(0x40, 0xFFFFF782); // MOVE.W	#$0040,$F782
	DEF_ROMLOC(1D8FC): move_tomem_32(0x21CF4, 0xFFFFD004); // MOVE.L	#$00021CF4,$D004
	DEF_ROMLOC(1D904): move_tomem_16(0x780, 0xFFFFD002); // MOVE.W	#$0780,$D002
	DEF_ROMLOC(1D90A): move_tomem_8(0x2, 0xFFFFD01C); // MOVE.B	#$02,$D01C
	DEF_ROMLOC(1D910): bset_tomem_8(0x2, 0xFFFFD022); // BSET.B	#$02,$D022
	DEF_ROMLOC(1D916): bset_tomem_8(0x1, 0xFFFFD022); // BSET.B	#$01,$D022
	DEF_ROMLOC(1D91C): return; // RTS
}
ROMFUNC(rom_1D91E) {
	DEF_ROMLOC(1D91E): move_toreg_32(0, &D0);
	DEF_ROMLOC(1D920): move_toreg_8(read_8(0xFFFE06), &D0);
	DEF_ROMLOC(1D924): lsl_toreg_16(3, &D0);
	DEF_ROMLOC(1D926): move_tomem_32(read_32(A2 + (D0 & 0xFFFF)), A0 + 4);
	DEF_ROMLOC(1D92C): move_tomem_16(read_16(A2 + (D0 & 0xFFFF) + 6), A0 + 2);
	DEF_ROMLOC(1D932): move_tomem_8(read_8(A2 + (D0 & 0xFFFF) + 5), A0 + 0x1A);
	DEF_ROMLOC(1D938): return;
}