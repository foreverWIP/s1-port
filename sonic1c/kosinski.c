// #define CHECK_STUFF(loc) 1
#include "system.h"
#include "opcodes.h"

ROMFUNC(rom_1894) {
	DEF_ROMLOC(1894): sub_toreg_32(0x2, &A7); // SUBQ.L	#$02,A7
	DEF_ROMLOC(1896): move_tomem_8(read_8(A0++), A7 + 0x1); // MOVE.B	(A0)+,1(A7)
	DEF_ROMLOC(189A): move_tomem_8(read_8(A0++), A7); // MOVE.B	(A0)+,(A7)
	DEF_ROMLOC(189C): move_toreg_16(read_16(A7), &D5); // MOVE.W	(A7),D5
	DEF_ROMLOC(189E): move_toreg_32(0xF, &D4); // MOVEQ.L	$0F,D4
	DEF_ROMLOC(18A0): lsr_toreg_16(0x1, &D5); // LSR.W	#$01,D5
	DEF_ROMLOC(18A2): move_sr_toreg_16(SR, &D6); // MOVE.W	SR,D6
	DEF_ROMLOC(18A4): dec_reg_16(&D4); if ((D4 & 0xffff) != 0xffff) goto rom_18B2; // DBF.W	D4,$18B2
	DEF_ROMLOC(18A8): move_tomem_8(read_8(A0++), A7 + 0x1); // MOVE.B	(A0)+,1(A7)
	DEF_ROMLOC(18AC): move_tomem_8(read_8(A0++), A7); // MOVE.B	(A0)+,(A7)
	DEF_ROMLOC(18AE): move_toreg_16(read_16(A7), &D5); // MOVE.W	(A7),D5
	DEF_ROMLOC(18B0): move_toreg_32(0xF, &D4); // MOVEQ.L	$0F,D4
	DEF_ROMLOC(18B2): move_tosr_16(D6, &SR); // MOVE.W	D6,CCR
	DEF_ROMLOC(18B4): if (CCR_CC) goto rom_18BA; // BCC.B	$18BA
	DEF_ROMLOC(18B6): move_tomem_8(read_8(A0++), A1++); // MOVE.B	(A0)+,(A1)+
	DEF_ROMLOC(18B8): goto rom_18A0; // BRA.B	$18A0
	DEF_ROMLOC(18BA): move_toreg_32(0x0, &D3); // MOVEQ.L	$00,D3
	DEF_ROMLOC(18BC): lsr_toreg_16(0x1, &D5); // LSR.W	#$01,D5
	DEF_ROMLOC(18BE): move_sr_toreg_16(SR, &D6); // MOVE.W	SR,D6
	DEF_ROMLOC(18C0): dec_reg_16(&D4); if ((D4 & 0xffff) != 0xffff) goto rom_18CE; // DBF.W	D4,$18CE
	DEF_ROMLOC(18C4): move_tomem_8(read_8(A0++), A7 + 0x1); // MOVE.B	(A0)+,1(A7)
	DEF_ROMLOC(18C8): move_tomem_8(read_8(A0++), A7); // MOVE.B	(A0)+,(A7)
	DEF_ROMLOC(18CA): move_toreg_16(read_16(A7), &D5); // MOVE.W	(A7),D5
	DEF_ROMLOC(18CC): move_toreg_32(0xF, &D4); // MOVEQ.L	$0F,D4
	DEF_ROMLOC(18CE): move_tosr_16(D6, &SR); // MOVE.W	D6,CCR
	DEF_ROMLOC(18D0): if (CCR_CS) goto rom_18FE; // BCS.B	$18FE
	DEF_ROMLOC(18D2): lsr_toreg_16(0x1, &D5); // LSR.W	#$01,D5
	DEF_ROMLOC(18D4): dec_reg_16(&D4); if ((D4 & 0xffff) != 0xffff) goto rom_18E2; // DBF.W	D4,$18E2
	DEF_ROMLOC(18D8): move_tomem_8(read_8(A0++), A7 + 0x1); // MOVE.B	(A0)+,1(A7)
	DEF_ROMLOC(18DC): move_tomem_8(read_8(A0++), A7); // MOVE.B	(A0)+,(A7)
	DEF_ROMLOC(18DE): move_toreg_16(read_16(A7), &D5); // MOVE.W	(A7),D5
	DEF_ROMLOC(18E0): move_toreg_32(0xF, &D4); // MOVEQ.L	$0F,D4
	DEF_ROMLOC(18E2): roxl_toreg_16(0x1, &D3); // ROXL.W	#$01,D3
	DEF_ROMLOC(18E4): lsr_toreg_16(0x1, &D5); // LSR.W	#$01,D5
	DEF_ROMLOC(18E6): dec_reg_16(&D4); if ((D4 & 0xffff) != 0xffff) goto rom_18F4; // DBF.W	D4,$18F4
	DEF_ROMLOC(18EA): move_tomem_8(read_8(A0++), A7 + 0x1); // MOVE.B	(A0)+,1(A7)
	DEF_ROMLOC(18EE): move_tomem_8(read_8(A0++), A7); // MOVE.B	(A0)+,(A7)
	DEF_ROMLOC(18F0): move_toreg_16(read_16(A7), &D5); // MOVE.W	(A7),D5
	DEF_ROMLOC(18F2): move_toreg_32(0xF, &D4); // MOVEQ.L	$0F,D4
	DEF_ROMLOC(18F4): roxl_toreg_16(0x1, &D3); // ROXL.W	#$01,D3
	DEF_ROMLOC(18F6): add_toreg_16(0x1, &D3); // ADDQ.W	#$01,D3
	DEF_ROMLOC(18F8): move_toreg_32(0xFFFFFFFF, &D2); // MOVEQ.L	$FF,D2
	DEF_ROMLOC(18FA): move_toreg_8(read_8(A0++), &D2); // MOVE.B	(A0)+,D2
	DEF_ROMLOC(18FC): goto rom_1914; // BRA.B	$1914
	DEF_ROMLOC(18FE): move_toreg_8(read_8(A0++), &D0); // MOVE.B	(A0)+,D0
	DEF_ROMLOC(1900): move_toreg_8(read_8(A0++), &D1); // MOVE.B	(A0)+,D1
	DEF_ROMLOC(1902): move_toreg_32(0xFFFFFFFF, &D2); // MOVEQ.L	$FF,D2
	DEF_ROMLOC(1904): move_toreg_8(D1, &D2); // MOVE.B	D1,D2
	DEF_ROMLOC(1906): lsl_toreg_16(0x5, &D2); // LSL.W	#$05,D2
	DEF_ROMLOC(1908): move_toreg_8(D0, &D2); // MOVE.B	D0,D2
	DEF_ROMLOC(190A): and_toreg_16(0x7, &D1); // ANDI.W	#$0007,D1
	DEF_ROMLOC(190E): if (CCR_EQ) goto rom_1920; // BEQ.B	$1920
	DEF_ROMLOC(1910): move_toreg_8(D1, &D3); // MOVE.B	D1,D3
	DEF_ROMLOC(1912): add_toreg_16(0x1, &D3); // ADDQ.W	#$01,D3
	DEF_ROMLOC(1914): move_toreg_8(read_8((s32)A1 + (s8)0x0 + (s16)D2), &D0); // MOVE.B	0(A1,D2),D0
	DEF_ROMLOC(1918): move_tomem_8(D0, A1++); // MOVE.B	D0,(A1)+
	DEF_ROMLOC(191A): dec_reg_16(&D3); if ((D3 & 0xffff) != 0xffff) goto rom_1914; // DBF.W	D3,$1914
	DEF_ROMLOC(191E): goto rom_18A0; // BRA.B	$18A0
	DEF_ROMLOC(1920): move_toreg_8(read_8(A0++), &D1); // MOVE.B	(A0)+,D1
	DEF_ROMLOC(1922): if (CCR_EQ) goto rom_1930; // BEQ.B	$1930
	DEF_ROMLOC(1924): cmp_toreg_8(0x1, &D1); // CMPI.B	#$01,D1
	DEF_ROMLOC(1928): if (CCR_EQ) goto rom_18A0; // BEQ.W	$18A0
	DEF_ROMLOC(192C): move_toreg_8(D1, &D3); // MOVE.B	D1,D3
	DEF_ROMLOC(192E): goto rom_1914; // BRA.B	$1914
	DEF_ROMLOC(1930): add_toreg_32(0x2, &A7); // ADDQ.L	#$02,A7
	DEF_ROMLOC(1932): return; // RTS
}