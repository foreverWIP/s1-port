// #define CHECK_STUFF(loc) 1
#include "system.h"
#include "opcodes.h"

static u32 d0backup;
static u32 d1backup;
static u32 d2backup;
static u32 d3backup;
static u32 d4backup;
static u32 d5backup;
static u32 d6backup;
static u32 d7backup;
static u32 a0backup;
static u32 a1backup;
static u32 a3backup;
static u32 a4backup;
static u32 a5backup;

ROMFUNC(rom_1438) {
	DEF_ROMLOC(1438):
		d0backup = D0;
		d1backup = D1;
		d2backup = D2;
		d3backup = D3;
		d4backup = D4;
		d5backup = D5;
		d6backup = D6;
		d7backup = D7;
		a0backup = A0;
		a1backup = A1;
		a3backup = A3;
		a4backup = A4;
		a5backup = A5;
		// TODO; // MOVEM.L	D0-A1/A3-A5,-(A7)
	DEF_ROMLOC(143C): move_toreg_32(0x14FA, &A3); // LEA.L	$000014FA,A3
	DEF_ROMLOC(1442): move_toreg_32(0xC00000, &A4); // LEA.L	$00C00000,A4
	rom_1454(); // BRA.B	$1454
}
ROMFUNC(rom_144A) {
	DEF_ROMLOC(144A):
		d0backup = D0;
		d1backup = D1;
		d2backup = D2;
		d3backup = D3;
		d4backup = D4;
		d5backup = D5;
		d6backup = D6;
		d7backup = D7;
		a0backup = A0;
		a1backup = A1;
		a3backup = A3;
		a4backup = A4;
		a5backup = A5;
		// TODO; // MOVEM.L	D0-A1/A3-A5,-(A7)
	DEF_ROMLOC(144E): move_toreg_32(0x1510, &A3); // LEA.L	$00001510,A3
	rom_1454(); // Detected flow into next function
}
ROMFUNC(rom_1454) {
	DEF_ROMLOC(1454): move_toreg_32(0xFFFFAA00, &A1); // LEA.L	$AA00,A1
	DEF_ROMLOC(1458): move_toreg_16(read_16((A0 += 2, A0 - 2)), &D2); // MOVE.W	(A0)+,D2
	DEF_ROMLOC(145A): lsl_toreg_16(0x1, &D2); // LSL.W	#$01,D2
	DEF_ROMLOC(145C): if (CCR_CC) goto rom_1462; // BCC.B	$1462
	DEF_ROMLOC(145E): add_toreg_16(0xA, &A3); // ADDA.W	#$000A,A3
	DEF_ROMLOC(1462): lsl_toreg_16(0x2, &D2); // LSL.W	#$02,D2
	DEF_ROMLOC(1464): move_toreg_16(D2, &A5); // MOVEA.W	D2,A5
	DEF_ROMLOC(1466): move_toreg_32(0x8, &D3); // MOVEQ.L	$08,D3
	DEF_ROMLOC(1468): move_toreg_32(0x0, &D2); // MOVEQ.L	$00,D2
	DEF_ROMLOC(146A): move_toreg_32(0x0, &D4); // MOVEQ.L	$00,D4
	DEF_ROMLOC(146C): rom_1526(); // BSR.W	$1526
	DEF_ROMLOC(1470): move_toreg_8(read_8(A0++), &D5); // MOVE.B	(A0)+,D5
	DEF_ROMLOC(1472): asl_toreg_16(0x8, &D5); // ASL.W	#$08,D5
	DEF_ROMLOC(1474): move_toreg_8(read_8(A0++), &D5); // MOVE.B	(A0)+,D5
	DEF_ROMLOC(1476): move_toreg_16(0x10, &D6); // MOVE.W	#$0010,D6
	DEF_ROMLOC(147A): rom_1482(); // BSR.B	$1482
	DEF_ROMLOC(147C):
		D0 = d0backup;
		D1 = d1backup;
		D2 = d2backup;
		D3 = d3backup;
		D4 = d4backup;
		D5 = d5backup;
		D6 = d6backup;
		D7 = d7backup;
		A0 = a0backup;
		A1 = a1backup;
		A3 = a3backup;
		A4 = a4backup;
		A5 = a5backup;
		// TODO; // MOVEM.L	(A7)+,D0-A1/A3-A5
	DEF_ROMLOC(1480): return; // RTS
}
static void NemDec_ProcessCompressedData(bool skiptonewrow) {
	if (skiptonewrow) goto rom_14C4;
	DEF_ROMLOC(1482): move_toreg_16(D6, &D7); // MOVE.W	D6,D7
	DEF_ROMLOC(1484): sub_toreg_16(0x8, &D7); // SUBQ.W	#$08,D7
	DEF_ROMLOC(1486): move_toreg_16(D5, &D1); // MOVE.W	D5,D1
	DEF_ROMLOC(1488): lsr_toreg_16(D7, &D1); // LSR.W	D7,D1
	DEF_ROMLOC(148A): cmp_toreg_8(0xFFFFFFFC, &D1); // CMPI.B	#$FC,D1
	DEF_ROMLOC(148E): if (CCR_CC) goto rom_14CE; // BCC.B	$14CE
	DEF_ROMLOC(1490): and_toreg_16(0xFF, &D1); // ANDI.W	#$00FF,D1
	DEF_ROMLOC(1494): add_toreg_16(D1, &D1); // ADD.W	D1,D1
	DEF_ROMLOC(1496): move_toreg_8(read_8((s32)A1 + (s8)0x0 + (s16)D1), &D0); // MOVE.B	0(A1,D1),D0
	DEF_ROMLOC(149A): ext_reg_16(&D0); // EXT.W	D0
	DEF_ROMLOC(149C): sub_toreg_16(D0, &D6); // SUB.W	D0,D6
	DEF_ROMLOC(149E): cmp_toreg_16(0x9, &D6); // CMPI.W	#$0009,D6
	DEF_ROMLOC(14A2): if (CCR_CC) goto rom_14AA; // BCC.B	$14AA
	DEF_ROMLOC(14A4): add_toreg_16(0x8, &D6); // ADDQ.W	#$08,D6
	DEF_ROMLOC(14A6): asl_toreg_16(0x8, &D5); // ASL.W	#$08,D5
	DEF_ROMLOC(14A8): move_toreg_8(read_8(A0++), &D5); // MOVE.B	(A0)+,D5
	DEF_ROMLOC(14AA): move_toreg_8(read_8((s32)A1 + (s8)0x1 + (s16)D1), &D1); // MOVE.B	1(A1,D1),D1
	DEF_ROMLOC(14AE): move_toreg_16(D1, &D0); // MOVE.W	D1,D0
	DEF_ROMLOC(14B0): and_toreg_16(0xF, &D1); // ANDI.W	#$000F,D1
	DEF_ROMLOC(14B4): and_toreg_16(0xF0, &D0); // ANDI.W	#$00F0,D0
	DEF_ROMLOC(14B8): lsr_toreg_16(0x4, &D0); // LSR.W	#$04,D0
	DEF_ROMLOC(14BA): lsl_toreg_32(0x4, &D4); // LSL.L	#$04,D4
	DEF_ROMLOC(14BC): or_toreg_8(D1, &D4); // OR.B	D1,D4
	DEF_ROMLOC(14BE): sub_toreg_16(0x1, &D3); // SUBQ.W	#$01,D3
	DEF_ROMLOC(14C0): if (!CCR_EQ) goto rom_14C8; // BNE.B	$14C8
	// DEF_ROMLOC(14C2): goto rom_A3; // JMP	(A3)
	DEF_ROMLOC(14C2):
		switch (A3) {
			case 0x14FA: goto rom_14FA; break;
			case 0x1504: goto rom_1504; break;
			case 0x1510: goto rom_1510; break;
			case 0x151A: goto rom_151A; break;
		}

	DEF_ROMLOC(14C4): move_toreg_32(0x0, &D4); // MOVEQ.L	$00,D4
	DEF_ROMLOC(14C6): move_toreg_32(0x8, &D3); // MOVEQ.L	$08,D3
	DEF_ROMLOC(14C8): dec_reg_16(&D0); if ((D0 & 0xffff) != 0xffff) goto rom_14BA; // DBF.W	D0,$14BA
	goto rom_1482; // BRA.B	$1482
	DEF_ROMLOC(14CE): sub_toreg_16(0x6, &D6); // SUBQ.W	#$06,D6
	DEF_ROMLOC(14D0): cmp_toreg_16(0x9, &D6); // CMPI.W	#$0009,D6
	DEF_ROMLOC(14D4): if (CCR_CC) goto rom_14DC; // BCC.B	$14DC
	DEF_ROMLOC(14D6): add_toreg_16(0x8, &D6); // ADDQ.W	#$08,D6
	DEF_ROMLOC(14D8): asl_toreg_16(0x8, &D5); // ASL.W	#$08,D5
	DEF_ROMLOC(14DA): move_toreg_8(read_8(A0++), &D5); // MOVE.B	(A0)+,D5
	DEF_ROMLOC(14DC): sub_toreg_16(0x7, &D6); // SUBQ.W	#$07,D6
	DEF_ROMLOC(14DE): move_toreg_16(D5, &D1); // MOVE.W	D5,D1
	DEF_ROMLOC(14E0): lsr_toreg_16(D6, &D1); // LSR.W	D6,D1
	DEF_ROMLOC(14E2): move_toreg_16(D1, &D0); // MOVE.W	D1,D0
	DEF_ROMLOC(14E4): and_toreg_16(0xF, &D1); // ANDI.W	#$000F,D1
	DEF_ROMLOC(14E8): and_toreg_16(0x70, &D0); // ANDI.W	#$0070,D0
	DEF_ROMLOC(14EC): cmp_toreg_16(0x9, &D6); // CMPI.W	#$0009,D6
	DEF_ROMLOC(14F0): if (CCR_CC) goto rom_14B8; // BCC.B	$14B8
	DEF_ROMLOC(14F2): add_toreg_16(0x8, &D6); // ADDQ.W	#$08,D6
	DEF_ROMLOC(14F4): asl_toreg_16(0x8, &D5); // ASL.W	#$08,D5
	DEF_ROMLOC(14F6): move_toreg_8(read_8(A0++), &D5); // MOVE.B	(A0)+,D5
	goto rom_14B8; // BRA.B	$14B8

	DEF_ROMLOC(14FA): move_tomem_32(D4, A4); // MOVE.L	D4,(A4)
	DEF_ROMLOC(14FC): sub_toreg_16(0x1, &A5); // SUBQ.W	#$01,A5
	DEF_ROMLOC(14FE): move_toreg_16(A5, &D4); // MOVE.W	A5,D4
	DEF_ROMLOC(1500): if (!CCR_EQ) goto rom_14C4; // BNE.B	$14C4
	DEF_ROMLOC(1502): return; // RTS

	DEF_ROMLOC(1504): eor_toreg_32(D4, &D2); // EOR.L	D4,D2
	DEF_ROMLOC(1506): move_tomem_32(D2, A4); // MOVE.L	D2,(A4)
	DEF_ROMLOC(1508): sub_toreg_16(0x1, &A5); // SUBQ.W	#$01,A5
	DEF_ROMLOC(150A): move_toreg_16(A5, &D4); // MOVE.W	A5,D4
	DEF_ROMLOC(150C): if (!CCR_EQ) goto rom_14C4; // BNE.B	$14C4
	DEF_ROMLOC(150E): return; // RTS

	DEF_ROMLOC(1510): move_tomem_32(D4, (A4 += 4, A4 - 4)); // MOVE.L	D4,(A4)+
	DEF_ROMLOC(1512): sub_toreg_16(0x1, &A5); // SUBQ.W	#$01,A5
	DEF_ROMLOC(1514): move_toreg_16(A5, &D4); // MOVE.W	A5,D4
	DEF_ROMLOC(1516): if (!CCR_EQ) goto rom_14C4; // BNE.B	$14C4
	DEF_ROMLOC(1518): return; // RTS

	DEF_ROMLOC(151A): eor_toreg_32(D4, &D2); // EOR.L	D4,D2
	DEF_ROMLOC(151C): move_tomem_32(D2, (A4 += 4, A4 - 4)); // MOVE.L	D2,(A4)+
	DEF_ROMLOC(151E): sub_toreg_16(0x1, &A5); // SUBQ.W	#$01,A5
	DEF_ROMLOC(1520): move_toreg_16(A5, &D4); // MOVE.W	A5,D4
	DEF_ROMLOC(1522): if (!CCR_EQ) goto rom_14C4; // BNE.B	$14C4
	DEF_ROMLOC(1524): return; // RTS
}
ROMFUNC(rom_14C4) {
	NemDec_ProcessCompressedData(true);
}
ROMFUNC(rom_1482) {
	NemDec_ProcessCompressedData(false);
}
ROMFUNC(rom_1526) {
	DEF_ROMLOC(1526): move_toreg_8(read_8(A0++), &D0); // MOVE.B	(A0)+,D0
	DEF_ROMLOC(1528): cmp_toreg_8(0xFFFFFFFF, &D0); // CMPI.B	#$FF,D0
	DEF_ROMLOC(152C): if (!CCR_EQ) goto rom_1530; // BNE.B	$1530
	DEF_ROMLOC(152E): return; // RTS
	DEF_ROMLOC(1530): move_toreg_16(D0, &D7); // MOVE.W	D0,D7
	DEF_ROMLOC(1532): move_toreg_8(read_8(A0++), &D0); // MOVE.B	(A0)+,D0
	DEF_ROMLOC(1534): cmp_toreg_8(0xFFFFFF80, &D0); // CMPI.B	#$80,D0
	DEF_ROMLOC(1538): if (CCR_CC) goto rom_1528; // BCC.B	$1528
	DEF_ROMLOC(153A): move_toreg_8(D0, &D1); // MOVE.B	D0,D1
	DEF_ROMLOC(153C): and_toreg_16(0xF, &D7); // ANDI.W	#$000F,D7
	DEF_ROMLOC(1540): and_toreg_16(0x70, &D1); // ANDI.W	#$0070,D1
	DEF_ROMLOC(1544): or_toreg_16(D1, &D7); // OR.W	D1,D7
	DEF_ROMLOC(1546): and_toreg_16(0xF, &D0); // ANDI.W	#$000F,D0
	DEF_ROMLOC(154A): move_toreg_8(D0, &D1); // MOVE.B	D0,D1
	DEF_ROMLOC(154C): lsl_toreg_16(0x8, &D1); // LSL.W	#$08,D1
	DEF_ROMLOC(154E): or_toreg_16(D1, &D7); // OR.W	D1,D7
	DEF_ROMLOC(1550): move_toreg_32(0x8, &D1); // MOVEQ.L	$08,D1
	DEF_ROMLOC(1552): sub_toreg_16(D0, &D1); // SUB.W	D0,D1
	DEF_ROMLOC(1554): if (!CCR_EQ) goto rom_1560; // BNE.B	$1560
	DEF_ROMLOC(1556): move_toreg_8(read_8(A0++), &D0); // MOVE.B	(A0)+,D0
	DEF_ROMLOC(1558): add_toreg_16(D0, &D0); // ADD.W	D0,D0
	DEF_ROMLOC(155A): move_tomem_16(D7, (s32)A1 + (s8)0x0 + (s16)D0); // MOVE.W	D7,0(A1,D0)
	goto rom_1532; // BRA.B	$1532
	DEF_ROMLOC(1560): move_toreg_8(read_8(A0++), &D0); // MOVE.B	(A0)+,D0
	DEF_ROMLOC(1562): lsl_toreg_16(D1, &D0); // LSL.W	D1,D0
	DEF_ROMLOC(1564): add_toreg_16(D0, &D0); // ADD.W	D0,D0
	DEF_ROMLOC(1566): move_toreg_32(0x1, &D5); // MOVEQ.L	$01,D5
	DEF_ROMLOC(1568): lsl_toreg_16(D1, &D5); // LSL.W	D1,D5
	DEF_ROMLOC(156A): sub_toreg_16(0x1, &D5); // SUBQ.W	#$01,D5
	DEF_ROMLOC(156C): move_tomem_16(D7, (s32)A1 + (s8)0x0 + (s16)D0); // MOVE.W	D7,0(A1,D0)
	DEF_ROMLOC(1570): add_toreg_16(0x2, &D0); // ADDQ.W	#$02,D0
	DEF_ROMLOC(1572): dec_reg_16(&D5); if ((D5 & 0xffff) != 0xffff) goto rom_156C; // DBF.W	D5,$156C
	goto rom_1532; // BRA.B	$1532
}