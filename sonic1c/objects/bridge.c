// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"


ROMFUNC(rom_79A6) {
  u8 switchindex = 0;
  DEF_ROMLOC(79A6) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(79A8) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(79AC)
      : move_toreg_16(read_16(0x79B4 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(79B0): goto rom_79B4 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(79B0) : switch (switchindex) {
  case 0:
    rom_79C0();
    break;
  case 1:
    rom_7A82();
    break;
  case 2:
    rom_7C06();
    break;
  case 3:
    rom_7FA6();
    break;
  case 4:
    rom_7FA6();
    break;
  case 5:
    rom_7FAC();
    break;
  }
}
ROMFUNC(rom_79C0) {
  DEF_ROMLOC(79C0) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(79C4)
      : move_tomem_32(0x7FB2, A0 + 0x4);              // MOVE.L	#$00007FB2,4(A0)
  DEF_ROMLOC(79CC) : move_tomem_16(0x438E, A0 + 0x2); // MOVE.W	#$438E,2(A0)
  DEF_ROMLOC(79D2) : move_tomem_8(0x4, A0 + 0x1);     // MOVE.B	#$04,1(A0)
  DEF_ROMLOC(79D8) : move_tomem_8(0x3, A0 + 0x18);    // MOVE.B	#$03,24(A0)
  DEF_ROMLOC(79DE)
      : move_tomem_8(0xFFFFFF80, A0 + 0x19); // MOVE.B	#$80,25(A0)
  DEF_ROMLOC(79E4)
      : move_toreg_16(read_16(A0 + 0xC), &D2); // MOVE.W	12(A0),D2
  DEF_ROMLOC(79E8)
      : move_toreg_16(read_16(A0 + 0x8), &D3); // MOVE.W	8(A0),D3
  DEF_ROMLOC(79EC)
      : move_toreg_8(read_8(A0 + 0x0), &D4);        // MOVE.B	0(A0),D4
  DEF_ROMLOC(79F0) : move_toreg_32(A0 + 0x28, &A2); // LEA.L	40(A0),A2
  DEF_ROMLOC(79F4) : move_toreg_32(0x0, &D1);       // MOVEQ.L	$00,D1
  DEF_ROMLOC(79F6) : move_toreg_8(read_8(A2), &D1); // MOVE.B	(A2),D1
  DEF_ROMLOC(79F8) : move_tomem_8(0x0, A2++);       // MOVE.B	#$00,(A2)+
  DEF_ROMLOC(79FC) : move_toreg_16(D1, &D0);        // MOVE.W	D1,D0
  DEF_ROMLOC(79FE) : lsr_toreg_16(0x1, &D0);        // LSR.W	#$01,D0
  DEF_ROMLOC(7A00) : lsl_toreg_16(0x4, &D0);        // LSL.W	#$04,D0
  DEF_ROMLOC(7A02) : sub_toreg_16(D0, &D3);         // SUB.W	D0,D3
  DEF_ROMLOC(7A04) : sub_toreg_8(0x2, &D1);         // SUBQ.B	#$02,D1
  DEF_ROMLOC(7A06) : if (CCR_CS) {
    rom_7A82();
    return;
  }                              // BCS.B	$7A82
  DEF_ROMLOC(7A08) : rom_E11A(); // BSR.W	$E11A
  DEF_ROMLOC(7A0C) : if (!CCR_EQ) {
    rom_7A82();
    return;
  }                                               // BNE.B	$7A82
  DEF_ROMLOC(7A0E) : add_tomem_8(0x1, A0 + 0x28); // ADDQ.B	#$01,40(A0)
  DEF_ROMLOC(7A12)
      : cmp_toreg_16(read_16(A0 + 0x8), &D3);       // CMP.W	8(A0),D3
  DEF_ROMLOC(7A16) : if (!CCR_EQ) goto rom_7A36;    // BNE.B	$7A36
  DEF_ROMLOC(7A18) : add_toreg_16(0x10, &D3);       // ADDI.W	#$0010,D3
  DEF_ROMLOC(7A1C) : move_tomem_16(D2, A0 + 0xC);   // MOVE.W	D2,12(A0)
  DEF_ROMLOC(7A20) : move_tomem_16(D2, A0 + 0x3C);  // MOVE.W	D2,60(A0)
  DEF_ROMLOC(7A24) : move_toreg_16(A0, &D5);        // MOVE.W	A0,D5
  DEF_ROMLOC(7A26) : sub_toreg_16(0xFFFFD000, &D5); // SUBI.W	#$D000,D5
  DEF_ROMLOC(7A2A) : lsr_toreg_16(0x6, &D5);        // LSR.W	#$06,D5
  DEF_ROMLOC(7A2C) : and_toreg_16(0x7F, &D5);       // ANDI.W	#$007F,D5
  DEF_ROMLOC(7A30) : move_tomem_8(D5, A2++);        // MOVE.B	D5,(A2)+
  DEF_ROMLOC(7A32) : add_tomem_8(0x1, A0 + 0x28);   // ADDQ.B	#$01,40(A0)
  DEF_ROMLOC(7A36) : move_toreg_16(A1, &D5);        // MOVE.W	A1,D5
  DEF_ROMLOC(7A38) : sub_toreg_16(0xFFFFD000, &D5); // SUBI.W	#$D000,D5
  DEF_ROMLOC(7A3C) : lsr_toreg_16(0x6, &D5);        // LSR.W	#$06,D5
  DEF_ROMLOC(7A3E) : and_toreg_16(0x7F, &D5);       // ANDI.W	#$007F,D5
  DEF_ROMLOC(7A42) : move_tomem_8(D5, A2++);        // MOVE.B	D5,(A2)+
  DEF_ROMLOC(7A44) : move_tomem_8(0xA, A1 + 0x24);  // MOVE.B	#$0A,36(A1)
  DEF_ROMLOC(7A4A) : move_tomem_8(D4, A1 + 0x0);    // MOVE.B	D4,0(A1)
  DEF_ROMLOC(7A4E) : move_tomem_16(D2, A1 + 0xC);   // MOVE.W	D2,12(A1)
  DEF_ROMLOC(7A52) : move_tomem_16(D2, A1 + 0x3C);  // MOVE.W	D2,60(A1)
  DEF_ROMLOC(7A56) : move_tomem_16(D3, A1 + 0x8);   // MOVE.W	D3,8(A1)
  DEF_ROMLOC(7A5A)
      : move_tomem_32(0x7FB2, A1 + 0x4);              // MOVE.L	#$00007FB2,4(A1)
  DEF_ROMLOC(7A62) : move_tomem_16(0x438E, A1 + 0x2); // MOVE.W	#$438E,2(A1)
  DEF_ROMLOC(7A68) : move_tomem_8(0x4, A1 + 0x1);     // MOVE.B	#$04,1(A1)
  DEF_ROMLOC(7A6E) : move_tomem_8(0x3, A1 + 0x18);    // MOVE.B	#$03,24(A1)
  DEF_ROMLOC(7A74) : move_tomem_8(0x8, A1 + 0x19);    // MOVE.B	#$08,25(A1)
  DEF_ROMLOC(7A7A) : add_toreg_16(0x10, &D3);         // ADDI.W	#$0010,D3
  DEF_ROMLOC(7A7E) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_7A08; // DBF.W	D1,$7A08
  rom_7A82();      // Detected flow into next function
}
ROMFUNC(rom_7A82) {
  DEF_ROMLOC(7A82) : rom_7A9A();                  // BSR.B	$7A9A
  DEF_ROMLOC(7A84) : tst_mem_8(A0 + 0x3E);        // TST.B	62(A0)
  DEF_ROMLOC(7A88) : if (CCR_EQ) goto rom_7A92;   // BEQ.B	$7A92
  DEF_ROMLOC(7A8A) : sub_tomem_8(0x4, A0 + 0x3E); // SUBQ.B	#$04,62(A0)
  DEF_ROMLOC(7A8E) : rom_7C9E();                  // BSR.W	$7C9E
  DEF_ROMLOC(7A92) : rom_DC92();                  // BSR.W	$DC92
  rom_7F5A();                                     // BRA.W	$7F5A
}
ROMFUNC(rom_7A9A) {
  DEF_ROMLOC(7A9A) : move_toreg_32(0x0, &D1); // MOVEQ.L	$00,D1
  DEF_ROMLOC(7A9C)
      : move_toreg_8(read_8(A0 + 0x28), &D1);        // MOVE.B	40(A0),D1
  DEF_ROMLOC(7AA0) : lsl_toreg_16(0x3, &D1);         // LSL.W	#$03,D1
  DEF_ROMLOC(7AA2) : move_toreg_16(D1, &D2);         // MOVE.W	D1,D2
  DEF_ROMLOC(7AA4) : add_toreg_16(0x8, &D1);         // ADDQ.W	#$08,D1
  DEF_ROMLOC(7AA6) : add_toreg_16(D2, &D2);          // ADD.W	D2,D2
  DEF_ROMLOC(7AA8) : move_toreg_32(0xFFFFD000, &A1); // LEA.L	$D000,A1
  DEF_ROMLOC(7AAC) : tst_mem_16(A1 + 0x12);          // TST.W	18(A1)
  DEF_ROMLOC(7AB0) : if (CCR_MI) return;             // BMI.W	$7B9C
  DEF_ROMLOC(7AB4)
      : move_toreg_16(read_16(A1 + 0x8), &D0); // MOVE.W	8(A1),D0
  DEF_ROMLOC(7AB8)
      : sub_toreg_16(read_16(A0 + 0x8), &D0); // SUB.W	8(A0),D0
  DEF_ROMLOC(7ABC) : add_toreg_16(D1, &D0);   // ADD.W	D1,D0
  DEF_ROMLOC(7ABE) : if (CCR_MI) return;      // BMI.W	$7B9C
  DEF_ROMLOC(7AC2) : cmp_toreg_16(D2, &D0);   // CMP.W	D2,D0
  DEF_ROMLOC(7AC4) : if (CCR_CC) return;      // BCC.W	$7B9C
  rom_7AEC();                                 // BRA.B	$7AEC
}
ROMFUNC(rom_7C06) {
  DEF_ROMLOC(7C06) : rom_7C10(); // BSR.B	$7C10
  DEF_ROMLOC(7C08) : rom_DC92(); // BSR.W	$DC92
  rom_7F5A();                    // BRA.W	$7F5A
}
ROMFUNC(rom_7F5A) {
  DEF_ROMLOC(7F5A)
      : move_toreg_16(read_16(A0 + 0x8), &D0);      // MOVE.W	8(A0),D0
  DEF_ROMLOC(7F5E) : and_toreg_16(0xFFFFFF80, &D0); // ANDI.W	#$FF80,D0
  DEF_ROMLOC(7F62)
      : move_toreg_16(read_16(0xFFFFF700), &D1);      // MOVE.W	$F700,D1
  DEF_ROMLOC(7F66) : sub_toreg_16(0x80, &D1);         // SUBI.W	#$0080,D1
  DEF_ROMLOC(7F6A) : and_toreg_16(0xFFFFFF80, &D1);   // ANDI.W	#$FF80,D1
  DEF_ROMLOC(7F6E) : sub_toreg_16(D1, &D0);           // SUB.W	D1,D0
  DEF_ROMLOC(7F70) : cmp_toreg_16(0x280, &D0);        // CMPI.W	#$0280,D0
  DEF_ROMLOC(7F74) : if (CCR_HI) goto rom_7F7A;       // BHI.W	$7F7A
  DEF_ROMLOC(7F78) : return;                          // RTS
  DEF_ROMLOC(7F7A) : move_toreg_32(0x0, &D2);         // MOVEQ.L	$00,D2
  DEF_ROMLOC(7F7C) : move_toreg_32(A0 + 0x28, &A2);   // LEA.L	40(A0),A2
  DEF_ROMLOC(7F80) : move_toreg_8(read_8(A2++), &D2); // MOVE.B	(A2)+,D2
  DEF_ROMLOC(7F82) : sub_toreg_8(0x1, &D2);           // SUBQ.B	#$01,D2
  DEF_ROMLOC(7F84) : if (CCR_CS) goto rom_7FA0;       // BCS.B	$7FA0
  DEF_ROMLOC(7F86) : move_toreg_32(0x0, &D0);         // MOVEQ.L	$00,D0
  DEF_ROMLOC(7F88) : move_toreg_8(read_8(A2++), &D0); // MOVE.B	(A2)+,D0
  DEF_ROMLOC(7F8A) : lsl_toreg_16(0x6, &D0);          // LSL.W	#$06,D0
  DEF_ROMLOC(7F8C) : add_toreg_32(0xFFD000, &D0);     // ADDI.L	#$00FFD000,D0
  DEF_ROMLOC(7F92) : move_toreg_32(D0, &A1);          // MOVEA.L	D0,A1
  DEF_ROMLOC(7F94) : cmp_toreg_16(A0, &D0);           // CMP.W	A0,D0
  DEF_ROMLOC(7F96) : if (CCR_EQ) goto rom_7F9C;       // BEQ.B	$7F9C
  DEF_ROMLOC(7F98) : rom_DCD0();                      // BSR.W	$DCD0
  DEF_ROMLOC(7F9C) : dec_reg_16(&D2);
  if ((D2 & 0xffff) != 0xffff)
    goto rom_7F86;               // DBF.W	D2,$7F86
  DEF_ROMLOC(7FA0) : rom_DCCE(); // BSR.W	$DCCE
  DEF_ROMLOC(7FA4) : return;     // RTS
}
ROMFUNC(rom_7FA6) {
  DEF_ROMLOC(7FA6) : rom_DCCE(); // BSR.W	$DCCE
  DEF_ROMLOC(7FAA) : return;     // RTS
}
ROMFUNC(rom_7FAC) {
  DEF_ROMLOC(7FAC) : rom_DC92();                 // BSR.W	$DC92
  DEF_ROMLOC(7FB0) : return;                     // RTS
  DEF_ROMLOC(7FB2) : or_toreg_8(0xC, &D6);       // ORI.B	#$0C,D6
  DEF_ROMLOC(7FB6) : or_tomem_8(0xFFFFFFF8, A7); // ORI.B	#$F8,(A7)
  DEF_ROMLOC(7FBA) : btst_toreg_32(D2, &D0);     // BTST.L	D2,D0
  rom_7FD0(); // Detected flow into next function
}