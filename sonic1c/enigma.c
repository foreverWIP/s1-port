// #define CHECK_STUFF 1
#include "opcodes.h"
#include "system.h"


ROMFUNC(rom_1716) {
  u32 d0backup = 0;
  u32 d1backup = 0;
  u32 d2backup = 0;
  u32 d3backup = 0;
  u32 d4backup = 0;
  u32 d5backup = 0;
  u32 d6backup = 0;
  u32 d7backup = 0;
  u32 a1backup = 0;
  u32 a2backup = 0;
  u32 a3backup = 0;
  u32 a4backup = 0;
  u32 a5backup = 0;

  DEF_ROMLOC(1716) : d0backup = D0;
  d1backup = D1;
  d2backup = D2;
  d3backup = D3;
  d4backup = D4;
  d5backup = D5;
  d6backup = D6;
  d7backup = D7;
  a1backup = A1;
  a2backup = A2;
  a3backup = A3;
  a4backup = A4;
  a5backup = A5;
  // TODO; // MOVEM.L	D0-D7/A1-A5,-(A7)
  DEF_ROMLOC(171A) : move_toreg_16(D0, &A3);          // MOVEA.W	D0,A3
  DEF_ROMLOC(171C) : move_toreg_8(read_8(A0++), &D0); // MOVE.B	(A0)+,D0
  DEF_ROMLOC(171E) : ext_reg_16(&D0);                 // EXT.W	D0
  DEF_ROMLOC(1720) : move_toreg_16(D0, &A5);          // MOVEA.W	D0,A5
  DEF_ROMLOC(1722) : move_toreg_8(read_8(A0++), &D4); // MOVE.B	(A0)+,D4
  DEF_ROMLOC(1724) : lsl_toreg_8(0x3, &D4);           // LSL.B	#$03,D4
  DEF_ROMLOC(1726)
      : move_toreg_16(read_16((A0 += 2, A0 - 2)), &A2); // MOVEA.W	(A0)+,A2
  DEF_ROMLOC(1728) : add_toreg_16(A3, &A2);             // ADDA.W	A3,A2
  DEF_ROMLOC(172A)
      : move_toreg_16(read_16((A0 += 2, A0 - 2)), &A4); // MOVEA.W	(A0)+,A4
  DEF_ROMLOC(172C) : add_toreg_16(A3, &A4);             // ADDA.W	A3,A4
  DEF_ROMLOC(172E) : move_toreg_8(read_8(A0++), &D5);   // MOVE.B	(A0)+,D5
  DEF_ROMLOC(1730) : asl_toreg_16(0x8, &D5);            // ASL.W	#$08,D5
  DEF_ROMLOC(1732) : move_toreg_8(read_8(A0++), &D5);   // MOVE.B	(A0)+,D5
  DEF_ROMLOC(1734) : move_toreg_32(0x10, &D6);          // MOVEQ.L	$10,D6
  DEF_ROMLOC(1736) : move_toreg_32(0x7, &D0);           // MOVEQ.L	$07,D0
  DEF_ROMLOC(1738) : move_toreg_16(D6, &D7);            // MOVE.W	D6,D7
  DEF_ROMLOC(173A) : sub_toreg_16(D0, &D7);             // SUB.W	D0,D7
  DEF_ROMLOC(173C) : move_toreg_16(D5, &D1);            // MOVE.W	D5,D1
  DEF_ROMLOC(173E) : lsr_toreg_16(D7, &D1);             // LSR.W	D7,D1
  DEF_ROMLOC(1740) : and_toreg_16(0x7F, &D1);           // ANDI.W	#$007F,D1
  DEF_ROMLOC(1744) : move_toreg_16(D1, &D2);            // MOVE.W	D1,D2
  DEF_ROMLOC(1746) : cmp_toreg_16(0x40, &D1);           // CMPI.W	#$0040,D1
  DEF_ROMLOC(174A) : if (CCR_CC) goto rom_1750;         // BCC.B	$1750
  DEF_ROMLOC(174C) : move_toreg_32(0x6, &D0);           // MOVEQ.L	$06,D0
  DEF_ROMLOC(174E) : lsr_toreg_16(0x1, &D2);            // LSR.W	#$01,D2
  DEF_ROMLOC(1750) : rom_1884();                        // BSR.W	$1884
  DEF_ROMLOC(1754) : and_toreg_16(0xF, &D2);            // ANDI.W	#$000F,D2
  DEF_ROMLOC(1758) : lsr_toreg_16(0x4, &D1);            // LSR.W	#$04,D1
  DEF_ROMLOC(175A) : add_toreg_16(D1, &D1);             // ADD.W	D1,D1
  // DEF_ROMLOC(175C): goto rom_17AC + (s16)(D1 & 0xffff); // JMP
  // 78(PC,D1)
  DEF_ROMLOC(175C) : switch ((D1 & 0xffff) / 2) {
  case 0:
  case 1:
    goto rom_1760;
    break;
  case 2:
  case 3:
    goto rom_176A;
    break;
  case 4:
    goto rom_1772;
    break;
  case 5:
    goto rom_177E;
    break;
  case 6:
    goto rom_178C;
    break;
  case 7:
    goto rom_179A;
    break;
  }
  // }
  // ROMFUNC(rom_1760) {
  DEF_ROMLOC(1760)
      : move_tomem_16(A2, (A1 += 2, A1 - 2)); // MOVE.W	A2,(A1)+
  DEF_ROMLOC(1762) : add_toreg_16(0x1, &A2);  // ADDQ.W	#$01,A2
  DEF_ROMLOC(1764) : dec_reg_16(&D2);
  if ((D2 & 0xffff) != 0xffff)
    goto rom_1760; // DBF.W	D2,$1760
  goto rom_1736;   // BRA.B	$1736
                   // }
                   // ROMFUNC(rom_176A) {
  DEF_ROMLOC(176A)
      : move_tomem_16(A4, (A1 += 2, A1 - 2)); // MOVE.W	A4,(A1)+
  DEF_ROMLOC(176C) : dec_reg_16(&D2);
  if ((D2 & 0xffff) != 0xffff)
    goto rom_176A;               // DBF.W	D2,$176A
  goto rom_1736;                 // BRA.B	$1736
                                 // }
                                 // ROMFUNC(rom_1772) {
  DEF_ROMLOC(1772) : rom_17D4(); // BSR.W	$17D4
  DEF_ROMLOC(1776)
      : move_tomem_16(D1, (A1 += 2, A1 - 2)); // MOVE.W	D1,(A1)+
  DEF_ROMLOC(1778) : dec_reg_16(&D2);
  if ((D2 & 0xffff) != 0xffff)
    goto rom_1776;               // DBF.W	D2,$1776
  goto rom_1736;                 // BRA.B	$1736
                                 // }
                                 // ROMFUNC(rom_177E) {
  DEF_ROMLOC(177E) : rom_17D4(); // BSR.W	$17D4
  DEF_ROMLOC(1782)
      : move_tomem_16(D1, (A1 += 2, A1 - 2)); // MOVE.W	D1,(A1)+
  DEF_ROMLOC(1784) : add_toreg_16(0x1, &D1);  // ADDQ.W	#$01,D1
  DEF_ROMLOC(1786) : dec_reg_16(&D2);
  if ((D2 & 0xffff) != 0xffff)
    goto rom_1782;               // DBF.W	D2,$1782
  goto rom_1736;                 // BRA.B	$1736
                                 // }
                                 // ROMFUNC(rom_178C) {
  DEF_ROMLOC(178C) : rom_17D4(); // BSR.W	$17D4
  DEF_ROMLOC(1790)
      : move_tomem_16(D1, (A1 += 2, A1 - 2)); // MOVE.W	D1,(A1)+
  DEF_ROMLOC(1792) : sub_toreg_16(0x1, &D1);  // SUBQ.W	#$01,D1
  DEF_ROMLOC(1794) : dec_reg_16(&D2);
  if ((D2 & 0xffff) != 0xffff)
    goto rom_1790;                              // DBF.W	D2,$1790
  goto rom_1736;                                // BRA.B	$1736
                                                // }
                                                // ROMFUNC(rom_179A) {
  DEF_ROMLOC(179A) : cmp_toreg_16(0xF, &D2);    // CMPI.W	#$000F,D2
  DEF_ROMLOC(179E) : if (CCR_EQ) goto rom_17BC; // BEQ.B	$17BC
  DEF_ROMLOC(17A0) : rom_17D4();                // BSR.W	$17D4
  DEF_ROMLOC(17A4)
      : move_tomem_16(D1, (A1 += 2, A1 - 2)); // MOVE.W	D1,(A1)+
  DEF_ROMLOC(17A6) : dec_reg_16(&D2);
  if ((D2 & 0xffff) != 0xffff)
    goto rom_17A0;                  // DBF.W	D2,$17A0
  DEF_ROMLOC(17AA) : goto rom_1736; // BRA.B	$1736
  // DEF_ROMLOC(17AC): goto rom_1760; // BRA.B	$1760
  // DEF_ROMLOC(17AE): goto rom_1760; // BRA.B	$1760
  // DEF_ROMLOC(17B0): goto rom_176A; // BRA.B	$176A
  // DEF_ROMLOC(17B2): goto rom_176A; // BRA.B	$176A
  // DEF_ROMLOC(17B4): goto rom_1772; // BRA.B	$1772
  // DEF_ROMLOC(17B6): goto rom_177E; // BRA.B	$177E
  // DEF_ROMLOC(17B8): goto rom_178C; // BRA.B	$178C
  // rom_179A(); // BRA.B	$179A
  // }
  // ROMFUNC(rom_17BC) {
  DEF_ROMLOC(17BC) : sub_toreg_16(0x1, &A0);     // SUBQ.W	#$01,A0
  DEF_ROMLOC(17BE) : cmp_toreg_16(0x10, &D6);    // CMPI.W	#$0010,D6
  DEF_ROMLOC(17C2) : if (!CCR_EQ) goto rom_17C6; // BNE.B	$17C6
  DEF_ROMLOC(17C4) : sub_toreg_16(0x1, &A0);     // SUBQ.W	#$01,A0
  DEF_ROMLOC(17C6) : move_toreg_16(A0, &D0);     // MOVE.W	A0,D0
  DEF_ROMLOC(17C8) : lsr_toreg_16(0x1, &D0);     // LSR.W	#$01,D0
  DEF_ROMLOC(17CA) : if (CCR_CC) goto rom_17CE;  // BCC.B	$17CE
  DEF_ROMLOC(17CC) : add_toreg_16(0x1, &A0);     // ADDQ.W	#$01,A0
  DEF_ROMLOC(17CE) : D0 = d0backup;
  D1 = d1backup;
  D2 = d2backup;
  D3 = d3backup;
  D4 = d4backup;
  D5 = d5backup;
  D6 = d6backup;
  D7 = d7backup;
  A1 = a1backup;
  A2 = a2backup;
  A3 = a3backup;
  A4 = a4backup;
  A5 = a5backup;
  // TODO; // MOVEM.L	(A7)+,D0-D7/A1-A5
  DEF_ROMLOC(17D2) : return; // RTS
}
ROMFUNC(rom_17D4) {
  DEF_ROMLOC(17D4) : move_toreg_16(A3, &D3);        // MOVE.W	A3,D3
  DEF_ROMLOC(17D6) : move_toreg_8(D4, &D1);         // MOVE.B	D4,D1
  DEF_ROMLOC(17D8) : add_toreg_8(D1, &D1);          // ADD.B	D1,D1
  DEF_ROMLOC(17DA) : if (CCR_CC) goto rom_17E6;     // BCC.B	$17E6
  DEF_ROMLOC(17DC) : sub_toreg_16(0x1, &D6);        // SUBQ.W	#$01,D6
  DEF_ROMLOC(17DE) : btst_toreg_32(D6, &D5);        // BTST.L	D6,D5
  DEF_ROMLOC(17E0) : if (CCR_EQ) goto rom_17E6;     // BEQ.B	$17E6
  DEF_ROMLOC(17E2) : or_toreg_16(0xFFFF8000, &D3);  // ORI.W	#$8000,D3
  DEF_ROMLOC(17E6) : add_toreg_8(D1, &D1);          // ADD.B	D1,D1
  DEF_ROMLOC(17E8) : if (CCR_CC) goto rom_17F4;     // BCC.B	$17F4
  DEF_ROMLOC(17EA) : sub_toreg_16(0x1, &D6);        // SUBQ.W	#$01,D6
  DEF_ROMLOC(17EC) : btst_toreg_32(D6, &D5);        // BTST.L	D6,D5
  DEF_ROMLOC(17EE) : if (CCR_EQ) goto rom_17F4;     // BEQ.B	$17F4
  DEF_ROMLOC(17F0) : add_toreg_16(0x4000, &D3);     // ADDI.W	#$4000,D3
  DEF_ROMLOC(17F4) : add_toreg_8(D1, &D1);          // ADD.B	D1,D1
  DEF_ROMLOC(17F6) : if (CCR_CC) goto rom_1802;     // BCC.B	$1802
  DEF_ROMLOC(17F8) : sub_toreg_16(0x1, &D6);        // SUBQ.W	#$01,D6
  DEF_ROMLOC(17FA) : btst_toreg_32(D6, &D5);        // BTST.L	D6,D5
  DEF_ROMLOC(17FC) : if (CCR_EQ) goto rom_1802;     // BEQ.B	$1802
  DEF_ROMLOC(17FE) : add_toreg_16(0x2000, &D3);     // ADDI.W	#$2000,D3
  DEF_ROMLOC(1802) : add_toreg_8(D1, &D1);          // ADD.B	D1,D1
  DEF_ROMLOC(1804) : if (CCR_CC) goto rom_1810;     // BCC.B	$1810
  DEF_ROMLOC(1806) : sub_toreg_16(0x1, &D6);        // SUBQ.W	#$01,D6
  DEF_ROMLOC(1808) : btst_toreg_32(D6, &D5);        // BTST.L	D6,D5
  DEF_ROMLOC(180A) : if (CCR_EQ) goto rom_1810;     // BEQ.B	$1810
  DEF_ROMLOC(180C) : or_toreg_16(0x1000, &D3);      // ORI.W	#$1000,D3
  DEF_ROMLOC(1810) : add_toreg_8(D1, &D1);          // ADD.B	D1,D1
  DEF_ROMLOC(1812) : if (CCR_CC) goto rom_181E;     // BCC.B	$181E
  DEF_ROMLOC(1814) : sub_toreg_16(0x1, &D6);        // SUBQ.W	#$01,D6
  DEF_ROMLOC(1816) : btst_toreg_32(D6, &D5);        // BTST.L	D6,D5
  DEF_ROMLOC(1818) : if (CCR_EQ) goto rom_181E;     // BEQ.B	$181E
  DEF_ROMLOC(181A) : or_toreg_16(0x800, &D3);       // ORI.W	#$0800,D3
  DEF_ROMLOC(181E) : move_toreg_16(D5, &D1);        // MOVE.W	D5,D1
  DEF_ROMLOC(1820) : move_toreg_16(D6, &D7);        // MOVE.W	D6,D7
  DEF_ROMLOC(1822) : sub_toreg_16(A5, &D7);         // SUB.W	A5,D7
  DEF_ROMLOC(1824) : if (CCR_CC) goto rom_184E;     // BCC.B	$184E
  DEF_ROMLOC(1826) : move_toreg_16(D7, &D6);        // MOVE.W	D7,D6
  DEF_ROMLOC(1828) : add_toreg_16(0x10, &D6);       // ADDI.W	#$0010,D6
  DEF_ROMLOC(182C) : neg_reg_16(&D7);               // NEG.W	D7
  DEF_ROMLOC(182E) : lsl_toreg_16(D7, &D1);         // LSL.W	D7,D1
  DEF_ROMLOC(1830) : move_toreg_8(read_8(A0), &D5); // MOVE.B	(A0),D5
  DEF_ROMLOC(1832) : rol_toreg_8(D7, &D5);          // ROL.B	D7,D5
  DEF_ROMLOC(1834) : add_toreg_16(D7, &D7);         // ADD.W	D7,D7
  DEF_ROMLOC(1836)
      : and_toreg_16(read_16(0x1862 + (s16)(D7 & 0xffff)),
                     &D5);                   // AND.W	42(PC,D7),D5
  DEF_ROMLOC(183A) : add_toreg_16(D5, &D1);  // ADD.W	D5,D1
  DEF_ROMLOC(183C) : move_toreg_16(A5, &D0); // MOVE.W	A5,D0
  DEF_ROMLOC(183E) : add_toreg_16(D0, &D0);  // ADD.W	D0,D0
  DEF_ROMLOC(1840)
      : and_toreg_16(read_16(0x1862 + (s16)(D0 & 0xffff)),
                     &D1);                            // AND.W	32(PC,D0),D1
  DEF_ROMLOC(1844) : add_toreg_16(D3, &D1);           // ADD.W	D3,D1
  DEF_ROMLOC(1846) : move_toreg_8(read_8(A0++), &D5); // MOVE.B	(A0)+,D5
  DEF_ROMLOC(1848) : lsl_toreg_16(0x8, &D5);          // LSL.W	#$08,D5
  DEF_ROMLOC(184A) : move_toreg_8(read_8(A0++), &D5); // MOVE.B	(A0)+,D5
  DEF_ROMLOC(184C) : return;                          // RTS
  DEF_ROMLOC(184E) : if (CCR_EQ) goto rom_1860;       // BEQ.B	$1860
  DEF_ROMLOC(1850) : lsr_toreg_16(D7, &D1);           // LSR.W	D7,D1
  DEF_ROMLOC(1852) : move_toreg_16(A5, &D0);          // MOVE.W	A5,D0
  DEF_ROMLOC(1854) : add_toreg_16(D0, &D0);           // ADD.W	D0,D0
  DEF_ROMLOC(1856)
      : and_toreg_16(read_16(0x1862 + (s16)(D0 & 0xffff)),
                     &D1);                   // AND.W	10(PC,D0),D1
  DEF_ROMLOC(185A) : add_toreg_16(D3, &D1);  // ADD.W	D3,D1
  DEF_ROMLOC(185C) : move_toreg_16(A5, &D0); // MOVE.W	A5,D0
  DEF_ROMLOC(185E) : {
    rom_1884();
    return;
  }                                            // BRA.B	$1884
  DEF_ROMLOC(1860) : move_toreg_32(0x10, &D6); // MOVEQ.L	$10,D6
  goto rom_183C;                               // BRA.B	$183C
}
const u16 WORD_1864[] = {
    0x1,   0x3,   0x7,   0xf,   0x1f,   0x3f,   0x7f,   0xff,
    0x1ff, 0x3ff, 0x7ff, 0xfff, 0x1fff, 0x3fff, 0x7fff, 0xffff,
};
ROMFUNC(rom_1884) {
  DEF_ROMLOC(1884) : sub_toreg_16(D0, &D6);           // SUB.W	D0,D6
  DEF_ROMLOC(1886) : cmp_toreg_16(0x9, &D6);          // CMPI.W	#$0009,D6
  DEF_ROMLOC(188A) : if (CCR_CC) goto rom_1892;       // BCC.B	$1892
  DEF_ROMLOC(188C) : add_toreg_16(0x8, &D6);          // ADDQ.W	#$08,D6
  DEF_ROMLOC(188E) : asl_toreg_16(0x8, &D5);          // ASL.W	#$08,D5
  DEF_ROMLOC(1890) : move_toreg_8(read_8(A0++), &D5); // MOVE.B	(A0)+,D5
  DEF_ROMLOC(1892) : return;                          // RTS
}