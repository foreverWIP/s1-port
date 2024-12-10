// #define CHECK_STUFF(loc) 1
#include "../system.h"
#include "../opcodes.h"

ROMFUNC(rom_6E16) {
	u32 d4backup = 0;
	u32 d5backup = 0;
	DEF_ROMLOC(6E16): move_toreg_32(0xFFFFFFF0, &D4); // MOVEQ.L	$F0,D4
	DEF_ROMLOC(6E18): bclr_tomem_8(0x0, A2); // BCLR.B	#$00,(A2)
	DEF_ROMLOC(6E1C): if (!CCR_EQ) goto rom_6E28; // BNE.B	$6E28
	DEF_ROMLOC(6E1E): bclr_tomem_8(0x1, A2); // BCLR.B	#$01,(A2)
	DEF_ROMLOC(6E22): if (CCR_EQ) goto rom_6E72; // BEQ.B	$6E72
	DEF_ROMLOC(6E24): move_toreg_16(0xE0, &D4); // MOVE.W	#$00E0,D4
	DEF_ROMLOC(6E28): move_toreg_32(0x6DF5, &A0); // LEA.L	$00006DF5,A0
	DEF_ROMLOC(6E2E): move_toreg_16(read_16(0xFFFFF70C), &D0); // MOVE.W	$F70C,D0
	DEF_ROMLOC(6E32): add_toreg_16(D4, &D0); // ADD.W	D4,D0
	DEF_ROMLOC(6E34): and_toreg_16(0x1F0, &D0); // ANDI.W	#$01F0,D0
	DEF_ROMLOC(6E38): lsr_toreg_16(0x4, &D0); // LSR.W	#$04,D0
	DEF_ROMLOC(6E3A): move_toreg_8(read_8((s32)A0 + (s8)0x0 + (s16)D0), &D0); // MOVE.B	0(A0,D0),D0
	DEF_ROMLOC(6E3E): move_toreg_32(0x6FE4, &A3); // LEA.L	$00006FE4,A3
	DEF_ROMLOC(6E44): move_toreg_16(read_16((s32)A3 + (s8)0x0 + (s16)D0), &A3); // MOVEA.W	0(A3,D0),A3
	DEF_ROMLOC(6E48): if (CCR_EQ) goto rom_6E5E; // BEQ.B	$6E5E
	DEF_ROMLOC(6E4A): move_toreg_32(0xFFFFFFF0, &D5); // MOVEQ.L	$F0,D5
	DEF_ROMLOC(6E4C): d4backup = D4; d5backup = D5; // TODO; // MOVEM.L	D4-D5,-(A7)
	DEF_ROMLOC(6E50): rom_7174(); // BSR.W	$7174
	DEF_ROMLOC(6E54): D4 = d4backup; D5 = d5backup; // TODO; // MOVEM.L	(A7)+,D4-D5
	DEF_ROMLOC(6E58): rom_7028(); // BSR.W	$7028
	goto rom_6E72; // BRA.B	$6E72
	DEF_ROMLOC(6E5E): move_toreg_32(0x0, &D5); // MOVEQ.L	$00,D5
	DEF_ROMLOC(6E60): d4backup = D4; d5backup = D5; // TODO; // MOVEM.L	D4-D5,-(A7)
	DEF_ROMLOC(6E64): rom_7176(); // BSR.W	$7176
	DEF_ROMLOC(6E68): D4 = d4backup; D5 = d5backup; // TODO; // MOVEM.L	(A7)+,D4-D5
	DEF_ROMLOC(6E6C): move_toreg_32(0x1F, &D6); // MOVEQ.L	$1F,D6
	DEF_ROMLOC(6E6E): rom_7054(); // BSR.W	$7054
	DEF_ROMLOC(6E72): tst_mem_8(A2); // TST.B	(A2)
	DEF_ROMLOC(6E74): if (!CCR_EQ) goto rom_6E78; // BNE.B	$6E78
	DEF_ROMLOC(6E76): return; // RTS
	DEF_ROMLOC(6E78): move_toreg_32(0xFFFFFFF0, &D4); // MOVEQ.L	$F0,D4
	DEF_ROMLOC(6E7A): move_toreg_32(0xFFFFFFF0, &D5); // MOVEQ.L	$F0,D5
	DEF_ROMLOC(6E7C): move_toreg_8(read_8(A2), &D0); // MOVE.B	(A2),D0
	DEF_ROMLOC(6E7E): and_toreg_8(0xFFFFFFA8, &D0); // ANDI.B	#$A8,D0
	DEF_ROMLOC(6E82): if (CCR_EQ) goto rom_6E8C; // BEQ.B	$6E8C
	DEF_ROMLOC(6E84): lsr_toreg_8(0x1, &D0); // LSR.B	#$01,D0
	DEF_ROMLOC(6E86): move_tomem_8(D0, A2); // MOVE.B	D0,(A2)
	DEF_ROMLOC(6E88): move_toreg_16(0x140, &D5); // MOVE.W	#$0140,D5
	DEF_ROMLOC(6E8C): move_toreg_32(0x6DF4, &A0); // LEA.L	$00006DF4,A0
	DEF_ROMLOC(6E92): move_toreg_16(read_16(0xFFFFF70C), &D0); // MOVE.W	$F70C,D0
	DEF_ROMLOC(6E96): and_toreg_16(0x1F0, &D0); // ANDI.W	#$01F0,D0
	DEF_ROMLOC(6E9A): lsr_toreg_16(0x4, &D0); // LSR.W	#$04,D0
	DEF_ROMLOC(6E9C): move_toreg_32((s32)A0 + (s8)0x0 + (s16)D0, &A0); // LEA.L	0(A0,D0),A0
	rom_6FEC(); // BRA.W	$6FEC
}