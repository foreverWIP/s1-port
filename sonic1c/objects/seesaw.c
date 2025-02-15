// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_11D10) {
  u8 switchindex = 0;
  DEF_ROMLOC(11D10) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(11D12) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(11D16)
      : move_toreg_16(read_16(0x11D44 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	44(PC,D0),D1
  // DEF_ROMLOC(11D1A): rom_11D44 + (s16)(D1 & 0xffff)(); // JSR
  // 40(PC,D1)
  DEF_ROMLOC(11D1A) : switch (switchindex) {
  case 0:
    rom_11D50();
    break;
  case 1:
    rom_11DBA();
    break;
  case 2:
    rom_11DEC();
    break;
  case 3:
    rom_11E66();
    break;
  case 4:
    rom_11EBC();
    break;
  case 5:
    rom_11F50();
    break;
  }
  DEF_ROMLOC(11D1E)
      : move_toreg_16(read_16(A0 + 0x30), &D0);      // MOVE.W	48(A0),D0
  DEF_ROMLOC(11D22) : and_toreg_16(0xFFFFFF80, &D0); // ANDI.W	#$FF80,D0
  DEF_ROMLOC(11D26)
      : move_toreg_16(read_16(0xFFFFF700), &D1);     // MOVE.W	$F700,D1
  DEF_ROMLOC(11D2A) : sub_toreg_16(0x80, &D1);       // SUBI.W	#$0080,D1
  DEF_ROMLOC(11D2E) : and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
  DEF_ROMLOC(11D32) : sub_toreg_16(D1, &D0);         // SUB.W	D1,D0
  DEF_ROMLOC(11D34) : if (CCR_MI) {
    rom_DCCE();
    return;
  }                                             // BMI.W	$DCCE
  DEF_ROMLOC(11D38) : cmp_toreg_16(0x280, &D0); // CMPI.W	#$0280,D0
  DEF_ROMLOC(11D3C) : if (CCR_HI) {
    rom_DCCE();
    return;
  }           // BHI.W	$DCCE
  rom_DC92(); // BRA.W	$DC92
}
ROMFUNC(rom_11D50) {
  DEF_ROMLOC(11D50) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(11D54)
      : move_tomem_32(0x12078, A0 + 0x4);             // MOVE.L	#$00012078,4(A0)
  DEF_ROMLOC(11D5C) : move_tomem_16(0x374, A0 + 0x2); // MOVE.W	#$0374,2(A0)
  DEF_ROMLOC(11D62) : or_tomem_8(0x4, A0 + 0x1);      // ORI.B	#$04,1(A0)
  DEF_ROMLOC(11D68) : move_tomem_8(0x4, A0 + 0x18);   // MOVE.B	#$04,24(A0)
  DEF_ROMLOC(11D6E) : move_tomem_8(0x30, A0 + 0x19);  // MOVE.B	#$30,25(A0)
  DEF_ROMLOC(11D74)
      : move_tomem_16(read_16(A0 + 0x8), A0 + 0x30); // MOVE.W	8(A0),48(A0)
  DEF_ROMLOC(11D7A) : tst_mem_8(A0 + 0x28);          // TST.B	40(A0)
  DEF_ROMLOC(11D7E) : if (!CCR_EQ) goto rom_11DA6;   // BNE.B	$11DA6
  DEF_ROMLOC(11D80) : rom_E130();                    // BSR.W	$E130
  DEF_ROMLOC(11D84) : if (!CCR_EQ) goto rom_11DA6;   // BNE.B	$11DA6
  DEF_ROMLOC(11D86) : move_tomem_8(OBJ_SEESAW, A1 + offsetof(object, id));  // MOVE.B	#$5E,0(A1)
  DEF_ROMLOC(11D8C) : add_tomem_8(0x6, A1 + 0x24);   // ADDQ.B	#$06,36(A1)
  DEF_ROMLOC(11D90)
      : move_tomem_16(read_16(A0 + 0x8), A1 + 0x8); // MOVE.W	8(A0),8(A1)
  DEF_ROMLOC(11D96)
      : move_tomem_16(read_16(A0 + 0xC), A1 + 0xC); // MOVE.W	12(A0),12(A1)
  DEF_ROMLOC(11D9C)
      : move_tomem_8(read_8(A0 + 0x22), A1 + 0x22); // MOVE.B	34(A0),34(A1)
  DEF_ROMLOC(11DA2) : move_tomem_32(A0, A1 + 0x3C); // MOVE.L	A0,60(A1)
  DEF_ROMLOC(11DA6) : btst_tomem_8(0x0, A0 + 0x22); // BTST.B	#$00,34(A0)
  DEF_ROMLOC(11DAC) : if (CCR_EQ) goto rom_11DB4;   // BEQ.B	$11DB4
  DEF_ROMLOC(11DAE) : move_tomem_8(0x2, A0 + 0x1A); // MOVE.B	#$02,26(A0)
  DEF_ROMLOC(11DB4)
      : move_tomem_8(read_8(A0 + 0x1A), A0 + 0x3A); // MOVE.B	26(A0),58(A0)
  rom_11DBA(); // Detected flow into next function
}
ROMFUNC(rom_11DBA) {
  DEF_ROMLOC(11DBA) : move_toreg_8(read_8(A0 + 0x3A), &D1); // MOVE.B
                                                            // 58(A0),D1
  DEF_ROMLOC(11DBE) : rom_11E3A();                          // BSR.W	$11E3A
  DEF_ROMLOC(11DC2) : move_toreg_32(0x12018, &A2);    // LEA.L	$00012018,A2
  DEF_ROMLOC(11DC8) : btst_tomem_8(0x0, A0 + 0x1A);   // BTST.B	#$00,26(A0)
  DEF_ROMLOC(11DCE) : if (CCR_EQ) goto rom_11DD6;     // BEQ.B	$11DD6
  DEF_ROMLOC(11DD0) : move_toreg_32(0x12048, &A2);    // LEA.L	$00012048,A2
  DEF_ROMLOC(11DD6) : move_toreg_32(0xFFFFD000, &A1); // LEA.L	$D000,A1
  DEF_ROMLOC(11DDA)
      : move_tomem_16(read_16(A1 + 0x12), A0 + 0x38); // MOVE.W	18(A1),56(A0)
  DEF_ROMLOC(11DE0) : move_toreg_16(0x30, &D1);       // MOVE.W	#$0030,D1
  DEF_ROMLOC(11DE4) : rom_7B9E();                     // JSR	$00007B9E
  DEF_ROMLOC(11DEA) : return;                         // RTS
}
ROMFUNC(rom_11DEC) {
  DEF_ROMLOC(11DEC) : rom_11E1E();                  // BSR.W	$11E1E
  DEF_ROMLOC(11DF0) : move_toreg_32(0x12018, &A2);  // LEA.L	$00012018,A2
  DEF_ROMLOC(11DF6) : btst_tomem_8(0x0, A0 + 0x1A); // BTST.B	#$00,26(A0)
  DEF_ROMLOC(11DFC) : if (CCR_EQ) goto rom_11E04;   // BEQ.B	$11E04
  DEF_ROMLOC(11DFE) : move_toreg_32(0x12048, &A2);  // LEA.L	$00012048,A2
  DEF_ROMLOC(11E04) : move_toreg_16(0x30, &D1);     // MOVE.W	#$0030,D1
  DEF_ROMLOC(11E08) : rom_7C3E();                   // JSR	$00007C3E
  DEF_ROMLOC(11E0E) : move_toreg_16(0x30, &D1);     // MOVE.W	#$0030,D1
  DEF_ROMLOC(11E12)
      : move_toreg_16(read_16(A0 + 0x8), &D2); // MOVE.W	8(A0),D2
  DEF_ROMLOC(11E16) : rom_8BA8();              // JSR	$00008BA8
  DEF_ROMLOC(11E1C) : return;                  // RTS
}
ROMFUNC(rom_11E1E) {
  DEF_ROMLOC(11E1E) : move_toreg_32(0x2, &D1);        // MOVEQ.L	$02,D1
  DEF_ROMLOC(11E20) : move_toreg_32(0xFFFFD000, &A1); // LEA.L	$D000,A1
  DEF_ROMLOC(11E24)
      : move_toreg_16(read_16(A0 + 0x8), &D0); // MOVE.W	8(A0),D0
  DEF_ROMLOC(11E28)
      : sub_toreg_16(read_16(A1 + 0x8), &D0);     // SUB.W	8(A1),D0
  DEF_ROMLOC(11E2C) : if (CCR_CC) goto rom_11E32; // BCC.B	$11E32
  DEF_ROMLOC(11E2E) : neg_reg_16(&D0);            // NEG.W	D0
  DEF_ROMLOC(11E30) : move_toreg_32(0x0, &D1);    // MOVEQ.L	$00,D1
  DEF_ROMLOC(11E32) : cmp_toreg_16(0x8, &D0);     // CMPI.W	#$0008,D0
  DEF_ROMLOC(11E36) : if (CCR_CC) {
    rom_11E3A();
    return;
  }                                            // BCC.B	$11E3A
  DEF_ROMLOC(11E38) : move_toreg_32(0x1, &D1); // MOVEQ.L	$01,D1
  rom_11E3A(); // Detected flow into next function
}
ROMFUNC(rom_11E3A) {
  DEF_ROMLOC(11E3A)
      : move_toreg_8(read_8(A0 + 0x1A), &D0);       // MOVE.B	26(A0),D0
  DEF_ROMLOC(11E3E) : cmp_toreg_8(D1, &D0);         // CMP.B	D1,D0
  DEF_ROMLOC(11E40) : if (CCR_EQ) goto rom_11E64;   // BEQ.B	$11E64
  DEF_ROMLOC(11E42) : if (CCR_CC) goto rom_11E46;   // BCC.B	$11E46
  DEF_ROMLOC(11E44) : add_toreg_8(0x2, &D0);        // ADDQ.B	#$02,D0
  DEF_ROMLOC(11E46) : sub_toreg_8(0x1, &D0);        // SUBQ.B	#$01,D0
  DEF_ROMLOC(11E48) : move_tomem_8(D0, A0 + 0x1A);  // MOVE.B	D0,26(A0)
  DEF_ROMLOC(11E4C) : move_tomem_8(D1, A0 + 0x3A);  // MOVE.B	D1,58(A0)
  DEF_ROMLOC(11E50) : bclr_tomem_8(0x0, A0 + 0x1);  // BCLR.B	#$00,1(A0)
  DEF_ROMLOC(11E56) : btst_tomem_8(0x1, A0 + 0x1A); // BTST.B	#$01,26(A0)
  DEF_ROMLOC(11E5C) : if (CCR_EQ) goto rom_11E64;   // BEQ.B	$11E64
  DEF_ROMLOC(11E5E) : bset_tomem_8(0x0, A0 + 0x1);  // BSET.B	#$00,1(A0)
  DEF_ROMLOC(11E64) : return;                       // RTS
}
ROMFUNC(rom_11E66) {
  DEF_ROMLOC(11E66) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(11E6A)
      : move_tomem_32(0x120BA, A0 + 0x4);             // MOVE.L	#$000120BA,4(A0)
  DEF_ROMLOC(11E72) : move_tomem_16(0x4F0, A0 + 0x2); // MOVE.W	#$04F0,2(A0)
  DEF_ROMLOC(11E78) : or_tomem_8(0x4, A0 + 0x1);      // ORI.B	#$04,1(A0)
  DEF_ROMLOC(11E7E) : move_tomem_8(0x4, A0 + 0x18);   // MOVE.B	#$04,24(A0)
  DEF_ROMLOC(11E84)
      : move_tomem_8(0xFFFFFF8B, A0 + 0x20);        // MOVE.B	#$8B,32(A0)
  DEF_ROMLOC(11E8A) : move_tomem_8(0xC, A0 + 0x19); // MOVE.B	#$0C,25(A0)
  DEF_ROMLOC(11E90)
      : move_tomem_16(read_16(A0 + 0x8), A0 + 0x30); // MOVE.W	8(A0),48(A0)
  DEF_ROMLOC(11E96) : add_tomem_16(0x28, A0 + 0x8);  // ADDI.W	#$0028,8(A0)
  DEF_ROMLOC(11E9C)
      : move_tomem_16(read_16(A0 + 0xC), A0 + 0x34); // MOVE.W	12(A0),52(A0)
  DEF_ROMLOC(11EA2) : move_tomem_8(0x1, A0 + 0x1A);  // MOVE.B	#$01,26(A0)
  DEF_ROMLOC(11EA8) : btst_tomem_8(0x0, A0 + 0x22);  // BTST.B	#$00,34(A0)
  DEF_ROMLOC(11EAE) : if (CCR_EQ) {
    rom_11EBC();
    return;
  }                                                 // BEQ.B	$11EBC
  DEF_ROMLOC(11EB0) : sub_tomem_16(0x50, A0 + 0x8); // SUBI.W	#$0050,8(A0)
  DEF_ROMLOC(11EB6) : move_tomem_8(0x2, A0 + 0x3A); // MOVE.B	#$02,58(A0)
  rom_11EBC(); // Detected flow into next function
}
ROMFUNC(rom_11EBC) {
  DEF_ROMLOC(11EBC)
      : move_toreg_32(read_32(A0 + 0x3C), &A1);             // MOVEA.L	60(A0),A1
  DEF_ROMLOC(11EC0) : move_toreg_32(0x0, &D0);              // MOVEQ.L	$00,D0
  DEF_ROMLOC(11EC2) : move_toreg_8(read_8(A0 + 0x3A), &D0); // MOVE.B
                                                            // 58(A0),D0
  DEF_ROMLOC(11EC6) : sub_toreg_8(read_8(A1 + 0x3A), &D0);  // SUB.B
                                                            // 58(A1),D0
  DEF_ROMLOC(11ECA) : if (CCR_EQ) goto rom_11F12;           // BEQ.B	$11F12
  DEF_ROMLOC(11ECC) : if (CCR_CC) goto rom_11ED0;           // BCC.B	$11ED0
  DEF_ROMLOC(11ECE) : neg_reg_8(&D0);                       // NEG.B	D0
  DEF_ROMLOC(11ED0) : move_toreg_16(0xFFFFF7E8, &D1);       // MOVE.W	#$F7E8,D1
  DEF_ROMLOC(11ED4) : move_toreg_16(0xFFFFFEEC, &D2);       // MOVE.W	#$FEEC,D2
  DEF_ROMLOC(11ED8) : cmp_toreg_8(0x1, &D0);                // CMPI.B	#$01,D0
  DEF_ROMLOC(11EDC) : if (CCR_EQ) goto rom_11EF6;           // BEQ.B	$11EF6
  DEF_ROMLOC(11EDE) : move_toreg_16(0xFFFFF510, &D1);       // MOVE.W	#$F510,D1
  DEF_ROMLOC(11EE2) : move_toreg_16(0xFFFFFF34, &D2);       // MOVE.W	#$FF34,D2
  DEF_ROMLOC(11EE6) : cmp_tomem_16(0xA00, A1 + 0x38); // CMPI.W	#$0A00,56(A1)
  DEF_ROMLOC(11EEC) : if (CCR_LT) goto rom_11EF6;     // BLT.B	$11EF6
  DEF_ROMLOC(11EEE) : move_toreg_16(0xFFFFF200, &D1); // MOVE.W	#$F200,D1
  DEF_ROMLOC(11EF2) : move_toreg_16(0xFFFFFF60, &D2); // MOVE.W	#$FF60,D2
  DEF_ROMLOC(11EF6) : move_tomem_16(D1, A0 + 0x12);   // MOVE.W	D1,18(A0)
  DEF_ROMLOC(11EFA) : move_tomem_16(D2, A0 + 0x10);   // MOVE.W	D2,16(A0)
  DEF_ROMLOC(11EFE)
      : move_toreg_16(read_16(A0 + 0x8), &D0); // MOVE.W	8(A0),D0
  DEF_ROMLOC(11F02)
      : sub_toreg_16(read_16(A0 + 0x30), &D0);     // SUB.W	48(A0),D0
  DEF_ROMLOC(11F06) : if (CCR_CC) goto rom_11F0C;  // BCC.B	$11F0C
  DEF_ROMLOC(11F08) : neg_mem_16(A0 + 0x10);       // NEG.W	16(A0)
  DEF_ROMLOC(11F0C) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  rom_11F50();
  return;                                          // BRA.B	$11F50
  DEF_ROMLOC(11F12) : move_toreg_32(0x1200E, &A2); // LEA.L	$0001200E,A2
  DEF_ROMLOC(11F18) : move_toreg_32(0x0, &D0);     // MOVEQ.L	$00,D0
  DEF_ROMLOC(11F1A)
      : move_toreg_8(read_8(A1 + 0x1A), &D0);   // MOVE.B	26(A1),D0
  DEF_ROMLOC(11F1E) : move_toreg_16(0x28, &D2); // MOVE.W	#$0028,D2
  DEF_ROMLOC(11F22)
      : move_toreg_16(read_16(A0 + 0x8), &D1); // MOVE.W	8(A0),D1
  DEF_ROMLOC(11F26)
      : sub_toreg_16(read_16(A0 + 0x30), &D1);    // SUB.W	48(A0),D1
  DEF_ROMLOC(11F2A) : if (CCR_CC) goto rom_11F30; // BCC.B	$11F30
  DEF_ROMLOC(11F2C) : neg_reg_16(&D2);            // NEG.W	D2
  DEF_ROMLOC(11F2E) : add_toreg_16(0x2, &D0);     // ADDQ.W	#$02,D0
  DEF_ROMLOC(11F30) : add_toreg_16(D0, &D0);      // ADD.W	D0,D0
  DEF_ROMLOC(11F32)
      : move_toreg_16(read_16(A0 + 0x34), &D1); // MOVE.W	52(A0),D1
  DEF_ROMLOC(11F36)
      : add_toreg_16(read_16((s32)A2 + (s8)0x0 + (s16)D0),
                     &D1);                         // ADD.W	0(A2,D0),D1
  DEF_ROMLOC(11F3A) : move_tomem_16(D1, A0 + 0xC); // MOVE.W	D1,12(A0)
  DEF_ROMLOC(11F3E)
      : add_toreg_16(read_16(A0 + 0x30), &D2);     // ADD.W	48(A0),D2
  DEF_ROMLOC(11F42) : move_tomem_16(D2, A0 + 0x8); // MOVE.W	D2,8(A0)
  DEF_ROMLOC(11F46) : clr_mem_16(A0 + 0xE);        // CLR.W	14(A0)
  DEF_ROMLOC(11F4A) : clr_mem_16(A0 + 0xA);        // CLR.W	10(A0)
  DEF_ROMLOC(11F4E) : return;                      // RTS
}
ROMFUNC(rom_11F50) {
  DEF_ROMLOC(11F50) : tst_mem_16(A0 + 0x12);      // TST.W	18(A0)
  DEF_ROMLOC(11F54) : if (CCR_PL) goto rom_11F6E; // BPL.B	$11F6E
  DEF_ROMLOC(11F56) : rom_DC40();                 // BSR.W	$DC40
  DEF_ROMLOC(11F5A)
      : move_toreg_16(read_16(A0 + 0x34), &D0); // MOVE.W	52(A0),D0
  DEF_ROMLOC(11F5E) : sub_toreg_16(0x2F, &D0);  // SUBI.W	#$002F,D0
  DEF_ROMLOC(11F62)
      : cmp_toreg_16(read_16(A0 + 0xC), &D0);     // CMP.W	12(A0),D0
  DEF_ROMLOC(11F66) : if (CCR_GT) goto rom_11F6C; // BGT.B	$11F6C
  DEF_ROMLOC(11F68) : rom_DC40();                 // BSR.W	$DC40
  DEF_ROMLOC(11F6C) : return;                     // RTS
  DEF_ROMLOC(11F6E) : rom_DC40();                 // BSR.W	$DC40
  DEF_ROMLOC(11F72)
      : move_toreg_32(read_32(A0 + 0x3C), &A1);    // MOVEA.L	60(A0),A1
  DEF_ROMLOC(11F76) : move_toreg_32(0x1200E, &A2); // LEA.L	$0001200E,A2
  DEF_ROMLOC(11F7C) : move_toreg_32(0x0, &D0);     // MOVEQ.L	$00,D0
  DEF_ROMLOC(11F7E) : move_toreg_8(read_8(A1 + 0x1A), &D0); // MOVE.B
                                                            // 26(A1),D0
  DEF_ROMLOC(11F82)
      : move_toreg_16(read_16(A0 + 0x8), &D1); // MOVE.W	8(A0),D1
  DEF_ROMLOC(11F86)
      : sub_toreg_16(read_16(A0 + 0x30), &D1);    // SUB.W	48(A0),D1
  DEF_ROMLOC(11F8A) : if (CCR_CC) goto rom_11F8E; // BCC.B	$11F8E
  DEF_ROMLOC(11F8C) : add_toreg_16(0x2, &D0);     // ADDQ.W	#$02,D0
  DEF_ROMLOC(11F8E) : add_toreg_16(D0, &D0);      // ADD.W	D0,D0
  DEF_ROMLOC(11F90)
      : move_toreg_16(read_16(A0 + 0x34), &D1); // MOVE.W	52(A0),D1
  DEF_ROMLOC(11F94)
      : add_toreg_16(read_16((s32)A2 + (s8)0x0 + (s16)D0),
                     &D1); // ADD.W	0(A2,D0),D1
  DEF_ROMLOC(11F98)
      : cmp_toreg_16(read_16(A0 + 0xC), &D1);     // CMP.W	12(A0),D1
  DEF_ROMLOC(11F9C) : if (CCR_GT) goto rom_1200C; // BGT.B	$1200C
  DEF_ROMLOC(11F9E)
      : move_toreg_32(read_32(A0 + 0x3C), &A1);            // MOVEA.L	60(A0),A1
  DEF_ROMLOC(11FA2) : move_toreg_32(0x2, &D1);             // MOVEQ.L	$02,D1
  DEF_ROMLOC(11FA4) : tst_mem_16(A0 + 0x10);               // TST.W	16(A0)
  DEF_ROMLOC(11FA8) : if (CCR_MI) goto rom_11FAC;          // BMI.B	$11FAC
  DEF_ROMLOC(11FAA) : move_toreg_32(0x0, &D1);             // MOVEQ.L	$00,D1
  DEF_ROMLOC(11FAC) : move_tomem_8(D1, A1 + 0x3A);         // MOVE.B	D1,58(A1)
  DEF_ROMLOC(11FB0) : move_tomem_8(D1, A0 + 0x3A);         // MOVE.B	D1,58(A0)
  DEF_ROMLOC(11FB4) : cmp_toreg_8(read_8(A1 + 0x1A), &D1); // CMP.B
                                                           // 26(A1),D1
  DEF_ROMLOC(11FB8) : if (CCR_EQ) goto rom_12000;          // BEQ.B	$12000
  DEF_ROMLOC(11FBA) : bclr_tomem_8(0x3, A1 + 0x22);        // BCLR.B	#$03,34(A1)
  DEF_ROMLOC(11FC0) : if (CCR_EQ) goto rom_12000;          // BEQ.B	$12000
  DEF_ROMLOC(11FC2) : clr_mem_8(A1 + 0x25);                // CLR.B	37(A1)
  DEF_ROMLOC(11FC6) : move_tomem_8(0x2, A1 + 0x24);        // MOVE.B	#$02,36(A1)
  DEF_ROMLOC(11FCC) : move_toreg_32(0xFFFFD000, &A2);      // LEA.L	$D000,A2
  DEF_ROMLOC(11FD0)
      : move_tomem_16(read_16(A0 + 0x12), A2 + 0x12); // MOVE.W	18(A0),18(A2)
  DEF_ROMLOC(11FD6) : neg_mem_16(A2 + 0x12);          // NEG.W	18(A2)
  DEF_ROMLOC(11FDA) : bset_tomem_8(0x1, A2 + 0x22);   // BSET.B	#$01,34(A2)
  DEF_ROMLOC(11FE0) : bclr_tomem_8(0x3, A2 + 0x22);   // BCLR.B	#$03,34(A2)
  DEF_ROMLOC(11FE6) : clr_mem_8(A2 + 0x3C);           // CLR.B	60(A2)
  DEF_ROMLOC(11FEA) : move_tomem_8(0x10, A2 + 0x1C);  // MOVE.B	#$10,28(A2)
  DEF_ROMLOC(11FF0) : move_tomem_8(0x2, A2 + 0x24);   // MOVE.B	#$02,36(A2)
  DEF_ROMLOC(11FF6) : move_toreg_16(SFX_SPRING, &D0);       // MOVE.W	#$00CC,D0
  DEF_ROMLOC(11FFA) : play_sound_special();           // JSR	$00001394
  DEF_ROMLOC(12000) : clr_mem_16(A0 + 0x10);          // CLR.W	16(A0)
  DEF_ROMLOC(12004) : clr_mem_16(A0 + 0x12);          // CLR.W	18(A0)
  DEF_ROMLOC(12008) : sub_tomem_8(0x2, A0 + 0x24);    // SUBQ.B	#$02,36(A0)
  DEF_ROMLOC(1200C) : return;                         // RTS
}