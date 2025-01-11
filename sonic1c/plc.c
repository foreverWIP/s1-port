#include "opcodes.h"
#include "system.h"


ROMFUNC(rom_1578) {
  u32 a1backup = 0;
  u32 a2backup = 0;
  DEF_ROMLOC(1578) : a1backup = A1;
  a2backup = A2; // TODO; // MOVEM.L	A1-A2,-(A7)
  DEF_ROMLOC(157C) : move_toreg_32(0x1DD86, &A1); // LEA.L	$0001DD86,A1
  DEF_ROMLOC(1582) : add_toreg_16(D0, &D0);       // ADD.W	D0,D0
  DEF_ROMLOC(1584)
      : move_toreg_16(read_16((s32)A1 + (s8)0x0 + (s16)D0),
                      &D0); // MOVE.W	0(A1,D0),D0
  DEF_ROMLOC(1588)
      : move_toreg_32((s32)A1 + (s8)0x0 + (s16)D0,
                      &A1);                          // LEA.L	0(A1,D0),A1
  DEF_ROMLOC(158C) : move_toreg_32(v_plc_buffer, &A2); // LEA.L	$F680,A2
  DEF_ROMLOC(1590) : tst_mem_32(A2);                 // TST.L	(A2)
  DEF_ROMLOC(1592) : if (CCR_EQ) goto rom_1598;      // BEQ.B	$1598
  DEF_ROMLOC(1594) : add_toreg_16(0x6, &A2);         // ADDQ.W	#$06,A2
  DEF_ROMLOC(1596) : goto rom_1590;                  // BRA.B	$1590
  DEF_ROMLOC(1598)
      : move_toreg_16(read_16((A1 += 2, A1 - 2)), &D0); // MOVE.W	(A1)+,D0
  DEF_ROMLOC(159A) : if (CCR_MI) goto rom_15A4;         // BMI.B	$15A4
  DEF_ROMLOC(159C)
      : move_tomem_32(read_32((A1 += 4, A1 - 4)),
                      (A2 += 4, A2 - 4)); // MOVE.L	(A1)+,(A2)+
  DEF_ROMLOC(159E)
      : move_tomem_16(read_16((A1 += 2, A1 - 2)),
                      (A2 += 2, A2 - 2)); // MOVE.W	(A1)+,(A2)+
  DEF_ROMLOC(15A0) : dec_reg_16(&D0);
  if ((D0 & 0xffff) != 0xffff)
    goto rom_159C; // DBF.W	D0,$159C
  DEF_ROMLOC(15A4) : A1 = a1backup;
  A2 = a2backup;             // TODO; // MOVEM.L	(A7)+,A1-A2
  DEF_ROMLOC(15A8) : return; // RTS
}
ROMFUNC(rom_15AA) {
  u32 a1backup = 0;
  u32 a2backup = 0;
  DEF_ROMLOC(15AA) : a1backup = A1;
  a2backup = A2; // TODO; // MOVEM.L	A1-A2,-(A7)
  DEF_ROMLOC(15AE) : move_toreg_32(0x1DD86, &A1); // LEA.L	$0001DD86,A1
  DEF_ROMLOC(15B4) : add_toreg_16(D0, &D0);       // ADD.W	D0,D0
  DEF_ROMLOC(15B6)
      : move_toreg_16(read_16((s32)A1 + (s8)0x0 + (s16)D0),
                      &D0); // MOVE.W	0(A1,D0),D0
  DEF_ROMLOC(15BA)
      : move_toreg_32((s32)A1 + (s8)0x0 + (s16)D0,
                      &A1);                          // LEA.L	0(A1,D0),A1
  DEF_ROMLOC(15BE) : clear_plc();                     // BSR.B	$15D6
  DEF_ROMLOC(15C0) : move_toreg_32(v_plc_buffer, &A2); // LEA.L	$F680,A2
  DEF_ROMLOC(15C4)
      : move_toreg_16(read_16((A1 += 2, A1 - 2)), &D0); // MOVE.W	(A1)+,D0
  DEF_ROMLOC(15C6) : if (CCR_MI) goto rom_15D0;         // BMI.B	$15D0
  DEF_ROMLOC(15C8)
      : move_tomem_32(read_32((A1 += 4, A1 - 4)),
                      (A2 += 4, A2 - 4)); // MOVE.L	(A1)+,(A2)+
  DEF_ROMLOC(15CA)
      : move_tomem_16(read_16((A1 += 2, A1 - 2)),
                      (A2 += 2, A2 - 2)); // MOVE.W	(A1)+,(A2)+
  DEF_ROMLOC(15CC) : dec_reg_16(&D0);
  if ((D0 & 0xffff) != 0xffff)
    goto rom_15C8; // DBF.W	D0,$15C8
  DEF_ROMLOC(15D0) : A1 = a1backup;
  A2 = a2backup;             // TODO; // MOVEM.L	(A7)+,A1-A2
  DEF_ROMLOC(15D4) : return; // RTS
}
void clear_plc(void) {
  DEF_ROMLOC(15D6) : move_toreg_32(v_plc_buffer, &A2); // LEA.L	$F680,A2
  DEF_ROMLOC(15DA) : move_toreg_32(0x1F, &D0);       // MOVEQ.L	$1F,D0
  DEF_ROMLOC(15DC) : clr_mem_32((A2 += 4, A2 - 4));  // CLR.L	(A2)+
  DEF_ROMLOC(15DE) : dec_reg_16(&D0);
  if ((D0 & 0xffff) != 0xffff)
    goto rom_15DC;           // DBF.W	D0,$15DC
  DEF_ROMLOC(15E2) : return; // RTS
}
ROMFUNC(rom_15E4) {
  DEF_ROMLOC(15E4) : tst_mem_32(v_plc_buffer);     // TST.L	$F680
  DEF_ROMLOC(15E8) : if (CCR_EQ) goto rom_1638;  // BEQ.B	$1638
  DEF_ROMLOC(15EA) : tst_mem_16(0xFFFFF6F8);     // TST.W	$F6F8
  DEF_ROMLOC(15EE) : if (!CCR_EQ) goto rom_1638; // BNE.B	$1638
  DEF_ROMLOC(15F0)
      : move_toreg_32(read_32(v_plc_buffer), &A0);     // MOVEA.L	$F680,A0
  DEF_ROMLOC(15F4) : move_toreg_32(0x14FA, &A3);     // LEA.L	$000014FA,A3
  DEF_ROMLOC(15FA) : move_toreg_32(0xFFFFAA00, &A1); // LEA.L	$AA00,A1
  DEF_ROMLOC(15FE)
      : move_toreg_16(read_16((A0 += 2, A0 - 2)), &D2); // MOVE.W	(A0)+,D2
  DEF_ROMLOC(1600) : if (CCR_PL) goto rom_1606;         // BPL.B	$1606
  DEF_ROMLOC(1602) : add_toreg_16(0xA, &A3);            // ADDA.W	#$000A,A3
  DEF_ROMLOC(1606) : and_toreg_16(0x7FFF, &D2);         // ANDI.W	#$7FFF,D2
  DEF_ROMLOC(160A) : move_tomem_16(D2, 0xFFFFF6F8);     // MOVE.W	D2,$F6F8
  DEF_ROMLOC(160E) : rom_1526();                        // BSR.W	$1526
  DEF_ROMLOC(1612) : move_toreg_8(read_8(A0++), &D5);   // MOVE.B	(A0)+,D5
  DEF_ROMLOC(1614) : asl_toreg_16(0x8, &D5);            // ASL.W	#$08,D5
  DEF_ROMLOC(1616) : move_toreg_8(read_8(A0++), &D5);   // MOVE.B	(A0)+,D5
  DEF_ROMLOC(1618) : move_toreg_32(0x10, &D6);          // MOVEQ.L	$10,D6
  DEF_ROMLOC(161A) : move_toreg_32(0x0, &D0);           // MOVEQ.L	$00,D0
  DEF_ROMLOC(161C) : move_tomem_32(A0, v_plc_buffer);     // MOVE.L	A0,$F680
  DEF_ROMLOC(1620) : move_tomem_32(A3, 0xFFFFF6E0);     // MOVE.L	A3,$F6E0
  DEF_ROMLOC(1624) : move_tomem_32(D0, 0xFFFFF6E4);     // MOVE.L	D0,$F6E4
  DEF_ROMLOC(1628) : move_tomem_32(D0, 0xFFFFF6E8);     // MOVE.L	D0,$F6E8
  DEF_ROMLOC(162C) : move_tomem_32(D0, 0xFFFFF6EC);     // MOVE.L	D0,$F6EC
  DEF_ROMLOC(1630) : move_tomem_32(D5, 0xFFFFF6F0);     // MOVE.L	D5,$F6F0
  DEF_ROMLOC(1634) : move_tomem_32(D6, 0xFFFFF6F4);     // MOVE.L	D6,$F6F4
  DEF_ROMLOC(1638) : return;                            // RTS
}
ROMFUNC(rom_16D4) {
  DEF_ROMLOC(16D4) : move_toreg_32(v_plc_buffer, &A0); // LEA.L	$F680,A0
  DEF_ROMLOC(16D8) : move_toreg_32(0x15, &D0);       // MOVEQ.L	$15,D0
  rom_16DA(); // Detected flow into next function
}
ROMFUNC(rom_16DA) {
  DEF_ROMLOC(16DA)
      : move_tomem_32(read_32(A0 + 0x6),
                      (A0 += 4, A0 - 4)); // MOVE.L	6(A0),(A0)+
  DEF_ROMLOC(16DE) : dec_reg_16(&D0);
  if ((D0 & 0xffff) != 0xffff)
    goto rom_16DA;           // DBF.W	D0,$16DA
  DEF_ROMLOC(16E2) : return; // RTS
}
ROMFUNC(rom_163A) {
  DEF_ROMLOC(163A) : tst_mem_16(0xFFFFF6F8); // TST.W	$F6F8
  DEF_ROMLOC(163E) : if (CCR_EQ) {
    rom_16D2();
    return;
  }                                                  // BEQ.W	$16D2
  DEF_ROMLOC(1642) : move_tomem_16(0x9, 0xFFFFF6FA); // MOVE.W	#$0009,$F6FA
  DEF_ROMLOC(1648) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(164A)
      : move_toreg_16(read_16(0xFFFFF684), &D0);      // MOVE.W	$F684,D0
  DEF_ROMLOC(164E) : add_tomem_16(0x120, 0xFFFFF684); // ADDI.W	#$0120,$F684
  rom_166E();                                         // BRA.B	$166E
}
ROMFUNC(rom_1656) {
  DEF_ROMLOC(1656) : tst_mem_16(0xFFFFF6F8); // TST.W	$F6F8
  DEF_ROMLOC(165A) : if (CCR_EQ) {
    rom_16D2();
    return;
  }                                                  // BEQ.B	$16D2
  DEF_ROMLOC(165C) : move_tomem_16(0x3, 0xFFFFF6FA); // MOVE.W	#$0003,$F6FA
  DEF_ROMLOC(1662) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(1664)
      : move_toreg_16(read_16(0xFFFFF684), &D0);     // MOVE.W	$F684,D0
  DEF_ROMLOC(1668) : add_tomem_16(0x60, 0xFFFFF684); // ADDI.W	#$0060,$F684
  rom_166E(); // Detected flow into next function
}
ROMFUNC(rom_166E) {
  DEF_ROMLOC(166E) : move_toreg_32(0xC00004, &A4); // LEA.L	$00C00004,A4
  DEF_ROMLOC(1674) : lsl_toreg_32(0x2, &D0);       // LSL.L	#$02,D0
  DEF_ROMLOC(1676) : lsr_toreg_16(0x2, &D0);       // LSR.W	#$02,D0
  DEF_ROMLOC(1678) : or_toreg_16(0x4000, &D0);     // ORI.W	#$4000,D0
  DEF_ROMLOC(167C) : swap_reg_16(&D0);             // SWAP.W	D0
  DEF_ROMLOC(167E) : move_tomem_32(D0, A4);        // MOVE.L	D0,(A4)
  DEF_ROMLOC(1680) : sub_toreg_16(0x4, &A4);       // SUBQ.W	#$04,A4
  DEF_ROMLOC(1682)
      : move_toreg_32(read_32(v_plc_buffer), &A0); // MOVEA.L	$F680,A0
  DEF_ROMLOC(1686)
      : move_toreg_32(read_32(0xFFFFF6E0), &A3); // MOVEA.L	$F6E0,A3
  DEF_ROMLOC(168A)
      : move_toreg_32(read_32(0xFFFFF6E4), &D0); // MOVE.L	$F6E4,D0
  DEF_ROMLOC(168E)
      : move_toreg_32(read_32(0xFFFFF6E8), &D1); // MOVE.L	$F6E8,D1
  DEF_ROMLOC(1692)
      : move_toreg_32(read_32(0xFFFFF6EC), &D2); // MOVE.L	$F6EC,D2
  DEF_ROMLOC(1696)
      : move_toreg_32(read_32(0xFFFFF6F0), &D5); // MOVE.L	$F6F0,D5
  DEF_ROMLOC(169A)
      : move_toreg_32(read_32(0xFFFFF6F4), &D6);     // MOVE.L	$F6F4,D6
  DEF_ROMLOC(169E) : move_toreg_32(0xFFFFAA00, &A1); // LEA.L	$AA00,A1
  rom_16A2(); // Detected flow into next function
}
ROMFUNC(rom_16A2) {
  DEF_ROMLOC(16A2) : move_toreg_16(0x8, &A5);       // MOVEA.W	#$0008,A5
  DEF_ROMLOC(16A6) : rom_14C4();                    // BSR.W	$14C4
  DEF_ROMLOC(16AA) : sub_tomem_16(0x1, 0xFFFFF6F8); // SUBQ.W	#$01,$F6F8
  DEF_ROMLOC(16AE) : if (CCR_EQ) {
    rom_16D4();
    return;
  }                                                 // BEQ.B	$16D4
  DEF_ROMLOC(16B0) : sub_tomem_16(0x1, 0xFFFFF6FA); // SUBQ.W	#$01,$F6FA
  DEF_ROMLOC(16B4) : if (!CCR_EQ) goto rom_16A2;    // BNE.B	$16A2
  DEF_ROMLOC(16B6) : move_tomem_32(A0, v_plc_buffer); // MOVE.L	A0,$F680
  DEF_ROMLOC(16BA) : move_tomem_32(A3, 0xFFFFF6E0); // MOVE.L	A3,$F6E0
  DEF_ROMLOC(16BE) : move_tomem_32(D0, 0xFFFFF6E4); // MOVE.L	D0,$F6E4
  DEF_ROMLOC(16C2) : move_tomem_32(D1, 0xFFFFF6E8); // MOVE.L	D1,$F6E8
  DEF_ROMLOC(16C6) : move_tomem_32(D2, 0xFFFFF6EC); // MOVE.L	D2,$F6EC
  DEF_ROMLOC(16CA) : move_tomem_32(D5, 0xFFFFF6F0); // MOVE.L	D5,$F6F0
  DEF_ROMLOC(16CE) : move_tomem_32(D6, 0xFFFFF6F4); // MOVE.L	D6,$F6F4
  rom_16D2(); // Detected flow into next function
}
ROMFUNC(rom_16D2) {
  DEF_ROMLOC(16D2) : return; // RTS
}
ROMFUNC(rom_16E4) {
  DEF_ROMLOC(16E4) : move_toreg_32(0x1DD86, &A1); // LEA.L	$0001DD86,A1
  DEF_ROMLOC(16EA) : add_toreg_16(D0, &D0);       // ADD.W	D0,D0
  DEF_ROMLOC(16EC)
      : move_toreg_16(read_16((s32)A1 + (s8)0x0 + (s16)D0),
                      &D0); // MOVE.W	0(A1,D0),D0
  DEF_ROMLOC(16F0)
      : move_toreg_32((s32)A1 + (s8)0x0 + (s16)D0,
                      &A1); // LEA.L	0(A1,D0),A1
  DEF_ROMLOC(16F4)
      : move_toreg_16(read_16((A1 += 2, A1 - 2)), &D1); // MOVE.W	(A1)+,D1
  DEF_ROMLOC(16F6)
      : move_toreg_32(read_32((A1 += 4, A1 - 4)), &A0); // MOVEA.L	(A1)+,A0
  DEF_ROMLOC(16F8) : move_toreg_32(0x0, &D0);           // MOVEQ.L	$00,D0
  DEF_ROMLOC(16FA)
      : move_toreg_16(read_16((A1 += 2, A1 - 2)), &D0); // MOVE.W	(A1)+,D0
  DEF_ROMLOC(16FC) : lsl_toreg_32(0x2, &D0);            // LSL.L	#$02,D0
  DEF_ROMLOC(16FE) : lsr_toreg_16(0x2, &D0);            // LSR.W	#$02,D0
  DEF_ROMLOC(1700) : or_toreg_16(0x4000, &D0);          // ORI.W	#$4000,D0
  DEF_ROMLOC(1704) : swap_reg_16(&D0);                  // SWAP.W	D0
  DEF_ROMLOC(1706) : move_tomem_32(D0, 0xC00004);       // MOVE.L	D0,$00C00004
  DEF_ROMLOC(170C) : decompress_nemesis();                        // BSR.W	$1438
  DEF_ROMLOC(1710) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_16F6;           // DBF.W	D1,$16F6
  DEF_ROMLOC(1714) : return; // RTS
}