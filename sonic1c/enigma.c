// #define CHECK_STUFF 1
#include "opcodes.h"
#include "system.h"

const u16 enigma_masks[] = {
    0x1,   0x3,   0x7,   0xf,   0x1f,   0x3f,   0x7f,   0xff,
    0x1ff, 0x3ff, 0x7ff, 0xfff, 0x1fff, 0x3fff, 0x7fff, 0xffff,
};

void enigma_get_byte(void);

void decompress_enigma(void) {
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
  bool oddbyte;
  // print("enigma(A0 = %x, A1 = %x, D0 = %x)", A0, A1, D0);
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
  
  DEF_ROMLOC(171A) : SETWORD(A3, D0);
  DEF_ROMLOC(171C) : SETBYTE(D0, read_8(A0++));
  DEF_ROMLOC(171E) : ext_reg_16(&D0);                 // EXT.W	D0
  DEF_ROMLOC(1720) : SETWORD(A5, D0);
  DEF_ROMLOC(1722) : SETBYTE(D4, read_8(A0++));
  DEF_ROMLOC(1724) : SETBYTE(D4, D4 << 3);
  DEF_ROMLOC(1726) : move_toreg_16(read_16((A0 += 2, A0 - 2)), &A2); // MOVEA.W	(A0)+,A2
  DEF_ROMLOC(1728) : add_toreg_16(A3, &A2);             // ADDA.W	A3,A2
  DEF_ROMLOC(172A)
      : move_toreg_16(read_16((A0 += 2, A0 - 2)), &A4); // MOVEA.W	(A0)+,A4
  DEF_ROMLOC(172C) : add_toreg_16(A3, &A4);             // ADDA.W	A3,A4
  DEF_ROMLOC(172E) : move_toreg_8(read_8(A0++), &D5);   // MOVE.B	(A0)+,D5
  DEF_ROMLOC(1730) : SETWORD(D5, D5 << 8);
  DEF_ROMLOC(1732) : move_toreg_8(read_8(A0++), &D5);   // MOVE.B	(A0)+,D5
  DEF_ROMLOC(1734) : D6 = 0x10;
  DEF_ROMLOC(1736) : D0 = 7;
  DEF_ROMLOC(1738) : SETWORD(D7, D6);
  DEF_ROMLOC(173A) : sub_toreg_16(D0, &D7);             // SUB.W	D0,D7
  DEF_ROMLOC(173C) : SETWORD(D1, D5);
  DEF_ROMLOC(173E) : SETWORD(D1, ((D7 & 0x1f) > 16) ? 0 : (GETWORD(D1) >> (D7 & 0x1f)));
  DEF_ROMLOC(1740) : SETWORD(D1, D1 & 0x7f);
  DEF_ROMLOC(1744) : SETWORD(D2, D1);
  DEF_ROMLOC(1746) : cmp_toreg_16(0x40, &D1);           // CMPI.W	#$0040,D1
  DEF_ROMLOC(174A) : if (!CCR_CC) {
  	DEF_ROMLOC(174C) : D0 = 6;
  	DEF_ROMLOC(174E) : SETWORD(D2, GETWORD(D2) >> 1);
  }
  DEF_ROMLOC(1750) : enigma_get_byte();                        // BSR.W	$1884
  DEF_ROMLOC(1754) : and_toreg_16(0xF, &D2);            // ANDI.W	#$000F,D2
  DEF_ROMLOC(1758) : SETWORD(D1, GETWORD(D1) >> 4);
  DEF_ROMLOC(175A) : add_toreg_16(D1, &D1);             // ADD.W	D1,D1
  // DEF_ROMLOC(175C): goto rom_17AC + (s16)(D1 & 0xffff); // JMP
  // 78(PC,D1)
  DEF_ROMLOC(175C) : switch ((D1 & 0xffff) / 2) {
  case 0:
  case 1:
	while (true) {
    	DEF_ROMLOC(1760) : move_tomem_16(A2, (A1 += 2, A1 - 2)); // MOVE.W	A2,(A1)+
  		DEF_ROMLOC(1762) : add_toreg_16(0x1, &A2);  // ADDQ.W	#$01,A2
  		DEF_ROMLOC(1764) : dec_reg_16(&D2);
  		if ((D2 & 0xffff) == 0xffff) break;
	}
    break;
  case 2:
  case 3:
	while (true) {
  	  	DEF_ROMLOC(176A) : move_tomem_16(A4, (A1 += 2, A1 - 2)); // MOVE.W	A4,(A1)+
  		DEF_ROMLOC(176C) : dec_reg_16(&D2);
  		if ((D2 & 0xffff) == 0xffff) break;
  	}
    break;
  case 4:
    DEF_ROMLOC(1772) : rom_17D4(); // BSR.W	$17D4
	while (true) {
		DEF_ROMLOC(1776) : move_tomem_16(D1, (A1 += 2, A1 - 2)); // MOVE.W	D1,(A1)+
		DEF_ROMLOC(1778) : dec_reg_16(&D2);
		if ((D2 & 0xffff) == 0xffff) break;
	}
    break;
  case 5:
    DEF_ROMLOC(177E) : rom_17D4(); // BSR.W	$17D4
	while (true) {
  		DEF_ROMLOC(1782) : move_tomem_16(D1, (A1 += 2, A1 - 2)); // MOVE.W	D1,(A1)+
  		DEF_ROMLOC(1784) : add_toreg_16(0x1, &D1);  // ADDQ.W	#$01,D1
  		DEF_ROMLOC(1786) : dec_reg_16(&D2);
  		if ((D2 & 0xffff) == 0xffff) break;
	}
    break;
  case 6:
    DEF_ROMLOC(178C) : rom_17D4(); // BSR.W	$17D4
	while (true) {
  		DEF_ROMLOC(1790) : move_tomem_16(D1, (A1 += 2, A1 - 2)); // MOVE.W	D1,(A1)+
  		DEF_ROMLOC(1792) : sub_toreg_16(0x1, &D1);  // SUBQ.W	#$01,D1
  		DEF_ROMLOC(1794) : dec_reg_16(&D2);
  		if ((D2 & 0xffff) == 0xffff) break;
	}
    break;
  case 7:
    DEF_ROMLOC(179A) : cmp_toreg_16(0xF, &D2);    // CMPI.W	#$000F,D2
  	DEF_ROMLOC(179E) : if (CCR_EQ) goto rom_17BC; // BEQ.B	$17BC
  	DEF_ROMLOC(17A0) : rom_17D4();                // BSR.W	$17D4
  	DEF_ROMLOC(17A4) : move_tomem_16(D1, (A1 += 2, A1 - 2)); // MOVE.W	D1,(A1)+
  	DEF_ROMLOC(17A6) : dec_reg_16(&D2);
  	if ((D2 & 0xffff) != 0xffff) goto rom_17A0;                  // DBF.W	D2,$17A0
    break;
  }
  goto rom_1736;
 
  DEF_ROMLOC(17AA) : goto rom_1736; // BRA.B	$1736
  DEF_ROMLOC(17BC) : SETWORD(A0, A0 - 1);
  DEF_ROMLOC(17C2) : if (GETWORD(D6) == 0x10) {
  	DEF_ROMLOC(17C4) : SETWORD(A0, A0 - 1);
  }
  DEF_ROMLOC(17C6) : SETWORD(D0, A0);
  DEF_ROMLOC(17C8) : oddbyte = (D0 & 1); SETWORD(D0, GETWORD(D0) >> 1);
  DEF_ROMLOC(17CA) : if (!oddbyte) goto rom_17CE;  // BCC.B	$17CE
  DEF_ROMLOC(17CC) : SETWORD(A0, A0 + 1);
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
  DEF_ROMLOC(17D2) : return; // RTS
}
ROMFUNC(rom_17D4) {
  DEF_ROMLOC(17D4) : move_toreg_16(A3, &D3);        // MOVE.W	A3,D3
  DEF_ROMLOC(17D6) : move_toreg_8(D4, &D1);         // MOVE.B	D4,D1
  DEF_ROMLOC(17D8) : add_toreg_8(D1, &D1);          // ADD.B	D1,D1
  DEF_ROMLOC(17DA) : if (!CCR_CC) {
  	DEF_ROMLOC(17DC) : sub_toreg_16(0x1, &D6);        // SUBQ.W	#$01,D6
  	DEF_ROMLOC(17DE) : btst_toreg_32(D6, &D5);        // BTST.L	D6,D5
  	DEF_ROMLOC(17E0) : if (!CCR_EQ) {
  		DEF_ROMLOC(17E2) : or_toreg_16(0xFFFF8000, &D3);  // ORI.W	#$8000,D3
	}
  }
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
  DEF_ROMLOC(1824) : if (!CCR_CC) {
  	DEF_ROMLOC(1826) : move_toreg_16(D7, &D6);        // MOVE.W	D7,D6
  	DEF_ROMLOC(1828) : add_toreg_16(0x10, &D6);       // ADDI.W	#$0010,D6
  	DEF_ROMLOC(182C) : neg_reg_16(&D7);               // NEG.W	D7
  	DEF_ROMLOC(182E) : SETWORD(D1, (GETWORD(D7) >= 16) ? 0 : (GETWORD(D1) << (D7 & 0x1f)));
  	DEF_ROMLOC(1830) : move_toreg_8(read_8(A0), &D5); // MOVE.B	(A0),D5
  	DEF_ROMLOC(1832) : SETBYTE(D5, (D5 << GETBYTE(D7)) | (GETBYTE(D5) >> (8 - GETBYTE(D7)))); // rol_toreg_8(D7, &D5);          // ROL.B	D7,D5
  	DEF_ROMLOC(1834) : add_toreg_16(D7, &D7);         // ADD.W	D7,D7
  	DEF_ROMLOC(1836) : SETWORD(D5, D5 & enigma_masks[(GETWORD(D7) / 2) - 1]);
  	DEF_ROMLOC(183A) : add_toreg_16(D5, &D1);  // ADD.W	D5,D1
  	DEF_ROMLOC(183C) : move_toreg_16(A5, &D0); // MOVE.W	A5,D0
  	DEF_ROMLOC(183E) : add_toreg_16(D0, &D0);  // ADD.W	D0,D0
  	DEF_ROMLOC(1840) : SETWORD(D1, D1 & enigma_masks[(GETWORD(D0) / 2) - 1]);
  	DEF_ROMLOC(1844) : add_toreg_16(D3, &D1);           // ADD.W	D3,D1
  	DEF_ROMLOC(1846) : move_toreg_8(read_8(A0++), &D5); // MOVE.B	(A0)+,D5
  	DEF_ROMLOC(1848) : SETWORD(D5, D5 << 8);
  	DEF_ROMLOC(184A) : move_toreg_8(read_8(A0++), &D5); // MOVE.B	(A0)+,D5
  	DEF_ROMLOC(184C) : return;                          // RTS
  }
  DEF_ROMLOC(184E) : if (GETWORD(D7) != 0) {
  	DEF_ROMLOC(1850) : SETWORD(D1, (GETWORD(D7) >= 16) ? 0 : (GETWORD(D1) >> (D7 & 0x1f)));
  	DEF_ROMLOC(1852) : move_toreg_16(A5, &D0);          // MOVE.W	A5,D0
  	DEF_ROMLOC(1854) : add_toreg_16(D0, &D0);           // ADD.W	D0,D0
  	DEF_ROMLOC(1856) : SETWORD(D1, D1 & enigma_masks[(GETWORD(D0) / 2) - 1]);
  	DEF_ROMLOC(185A) : add_toreg_16(D3, &D1);  // ADD.W	D3,D1
  	DEF_ROMLOC(185C) : move_toreg_16(A5, &D0); // MOVE.W	A5,D0
  	DEF_ROMLOC(185E) : enigma_get_byte();
  	return;  
  }                                         // BRA.B	$1884
  DEF_ROMLOC(1860) : D6 = 0x10;
  goto rom_183C;                               // BRA.B	$183C
}
void enigma_get_byte(void) {
  DEF_ROMLOC(1884) : SETWORD(D6, D6 - D0);
  DEF_ROMLOC(188A) : if (GETWORD(D6) < 9) {
  	DEF_ROMLOC(188C) : SETWORD(D6, D6 + 8);
  	DEF_ROMLOC(188E) : SETWORD(D5, D5 << 8);
  	DEF_ROMLOC(1890) : SETBYTE(D5, read_8(A0++));
  }
}