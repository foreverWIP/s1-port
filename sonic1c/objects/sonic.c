// #define CHECK_STUFF 1
#include "../game.h"
#include "../opcodes.h"
#include "../system.h"

static bool skiprestfromjump;

ROMFUNC(rom_3FD2) {
  DEF_ROMLOC(3FD2) : tst_mem_16(0xFFFFFFF0); // TST.W	$FFF0
  DEF_ROMLOC(3FD6) : if (!CCR_EQ) {
    rom_4012();
    return;
  }                          // BNE.B	$4012
  DEF_ROMLOC(3FD8) : return; // RTS
}
ROMFUNC(rom_4012) {
  DEF_ROMLOC(4012) : tst_mem_8(0xFFFFF604);     // TST.B	$F604
  DEF_ROMLOC(4016) : if (CCR_PL) goto rom_4024; // BPL.B	$4024
  DEF_ROMLOC(4018) : tst_mem_16(0xFFFFFFF0);    // TST.W	$FFF0
  DEF_ROMLOC(401C) : if (CCR_MI) goto rom_4024; // BMI.B	$4024
  DEF_ROMLOC(401E) : move_tomem_8(GM_TITLE, v_gamemode);
  DEF_ROMLOC(4024) : move_toreg_32(0x4082, &A1);        // LEA.L	$00004082,A1
  DEF_ROMLOC(402A) : move_toreg_32(0x0, &D0);           // MOVEQ.L	$00,D0
  DEF_ROMLOC(402C) : move_toreg_8(read_8(v_zone), &D0); // MOVE.B	$FE10,D0
  DEF_ROMLOC(4030)
      : cmp_tomem_8(GM_SPECIAL, v_gamemode);     // CMPI.B
                                                 // #$10,$F600
  DEF_ROMLOC(4036) : if (!CCR_EQ) goto rom_403A; // BNE.B	$403A
  DEF_ROMLOC(4038) : move_toreg_32(0x6, &D0);    // MOVEQ.L	$06,D0
  DEF_ROMLOC(403A) : lsl_toreg_16(0x2, &D0);     // LSL.W	#$02,D0
  DEF_ROMLOC(403C)
      : move_toreg_32(read_32((s32)A1 + (s8)0x0 + (s16)D0),
                      &A1);                      // MOVEA.L	0(A1,D0),A1
  DEF_ROMLOC(4040) : tst_mem_16(0xFFFFFFF0);     // TST.W	$FFF0
  DEF_ROMLOC(4044) : if (CCR_PL) goto rom_4058;  // BPL.B	$4058
  DEF_ROMLOC(4046) : move_toreg_32(0x40A2, &A1); // LEA.L	$000040A2,A1
  DEF_ROMLOC(404C)
      : move_toreg_16(read_16(0xFFFFFFF4), &D0); // MOVE.W	$FFF4,D0
  DEF_ROMLOC(4050) : sub_toreg_16(0x1, &D0);     // SUBQ.W	#$01,D0
  DEF_ROMLOC(4052) : lsl_toreg_16(0x2, &D0);     // LSL.W	#$02,D0
  DEF_ROMLOC(4054)
      : move_toreg_32(read_32((s32)A1 + (s8)0x0 + (s16)D0),
                      &A1); // MOVEA.L	0(A1,D0),A1
  DEF_ROMLOC(4058)
      : move_toreg_16(read_16(0xFFFFF790), &D0);     // MOVE.W	$F790,D0
  DEF_ROMLOC(405C) : add_toreg_16(D0, &A1);          // ADDA.W	D0,A1
  DEF_ROMLOC(405E) : move_toreg_8(read_8(A1), &D0);  // MOVE.B	(A1),D0
  DEF_ROMLOC(4060) : move_toreg_32(0xFFFFF604, &A0); // LEA.L	$F604,A0
  DEF_ROMLOC(4064) : move_toreg_8(D0, &D1);          // MOVE.B	D0,D1
  DEF_ROMLOC(4066) : move_toreg_32(0x0, &D2);        // MOVEQ.L	$00,D2
  DEF_ROMLOC(4068) : eor_toreg_8(D2, &D0);           // EOR.B	D2,D0
  DEF_ROMLOC(406A) : move_tomem_8(D1, A0++);         // MOVE.B	D1,(A0)+
  DEF_ROMLOC(406C) : and_toreg_8(D1, &D0);           // AND.B	D1,D0
  DEF_ROMLOC(406E) : move_tomem_8(D0, A0++);         // MOVE.B	D0,(A0)+
  DEF_ROMLOC(4070) : sub_tomem_8(0x1, 0xFFFFF792);   // SUBQ.B	#$01,$F792
  DEF_ROMLOC(4074) : if (CCR_CC) goto rom_4080;      // BCC.B	$4080
  DEF_ROMLOC(4076)
      : move_tomem_8(read_8(A1 + 0x3), 0xFFFFF792); // MOVE.B	3(A1),$F792
  DEF_ROMLOC(407C) : add_tomem_16(0x2, 0xFFFFF790); // ADDQ.W	#$02,$F790
  DEF_ROMLOC(4080) : return;                        // RTS
}
ROMFUNC(rom_81A0) {
  DEF_ROMLOC(81A0) : move_toreg_32(0xFFFFD000, &A1); // LEA.L	$D000,A1
  DEF_ROMLOC(81A4)
      : move_toreg_16(read_16(A0 + 0xC), &D0); // MOVE.W	12(A0),D0
  DEF_ROMLOC(81A8) : sub_toreg_16(D3, &D0);    // SUB.W	D3,D0
  rom_81B8();                                  // BRA.B	$81B8
}
ROMFUNC(rom_81AC) {
  DEF_ROMLOC(81AC) : move_toreg_32(0xFFFFD000, &A1); // LEA.L	$D000,A1
  DEF_ROMLOC(81B0)
      : move_toreg_16(read_16(A0 + 0xC), &D0); // MOVE.W	12(A0),D0
  DEF_ROMLOC(81B4) : sub_toreg_16(0x9, &D0);   // SUBI.W	#$0009,D0
  rom_81B8(); // Detected flow into next function
}
ROMFUNC(rom_81B8) {
  DEF_ROMLOC(81B8) : tst_mem_8(0xFFFFF7C8);        // TST.B	$F7C8
  DEF_ROMLOC(81BC) : if (CCR_MI) goto rom_81E0;    // BMI.B	$81E0
  DEF_ROMLOC(81BE) : cmp_tomem_8(0x6, 0xFFFFD024); // CMPI.B	#$06,$D024
  DEF_ROMLOC(81C4) : if (CCR_CC) goto rom_81E0;    // BCC.B	$81E0
  DEF_ROMLOC(81C6) : tst_mem_16(0xFFFFFE08);       // TST.W	$FE08
  DEF_ROMLOC(81CA) : if (!CCR_EQ) goto rom_81E0;   // BNE.B	$81E0
  DEF_ROMLOC(81CC) : move_toreg_32(0x0, &D1);      // MOVEQ.L	$00,D1
  DEF_ROMLOC(81CE)
      : move_toreg_8(read_8(A1 + 0x16), &D1);     // MOVE.B	22(A1),D1
  DEF_ROMLOC(81D2) : sub_toreg_16(D1, &D0);       // SUB.W	D1,D0
  DEF_ROMLOC(81D4) : move_tomem_16(D0, A1 + 0xC); // MOVE.W	D0,12(A1)
  DEF_ROMLOC(81D8)
      : sub_toreg_16(read_16(A0 + 0x8), &D2);    // SUB.W	8(A0),D2
  DEF_ROMLOC(81DC) : sub_tomem_16(D2, A1 + 0x8); // SUB.W	D2,8(A1)
  DEF_ROMLOC(81E0) : return;                     // RTS
}
ROMFUNC(rom_138FA) {
  DEF_ROMLOC(138FA)
      : move_toreg_16(read_16(A0 + 0x14), &D0);     // MOVE.W	20(A0),D0
  DEF_ROMLOC(138FE) : if (CCR_MI) goto rom_1390E;   // BMI.B	$1390E
  DEF_ROMLOC(13900) : bclr_tomem_8(0x0, A0 + 0x22); // BCLR.B	#$00,34(A0)
  DEF_ROMLOC(13906) : move_tomem_8(0x2, A0 + 0x1C); // MOVE.B	#$02,28(A0)
  DEF_ROMLOC(1390C) : return;                       // RTS
  DEF_ROMLOC(1390E) : add_toreg_16(D4, &D0);        // ADD.W	D4,D0
  DEF_ROMLOC(13910) : if (CCR_CC) goto rom_13916;   // BCC.B	$13916
  DEF_ROMLOC(13912) : move_toreg_16(0x80, &D0);     // MOVE.W	#$0080,D0
  DEF_ROMLOC(13916) : move_tomem_16(D0, A0 + 0x14); // MOVE.W	D0,20(A0)
  DEF_ROMLOC(1391A) : return;                       // RTS
}
ROMFUNC(rom_1391C) {
  DEF_ROMLOC(1391C)
      : move_toreg_16(read_16(0xFFFFF760), &D6); // MOVE.W	$F760,D6
  DEF_ROMLOC(13920)
      : move_toreg_16(read_16(0xFFFFF762), &D5);    // MOVE.W	$F762,D5
  DEF_ROMLOC(13924) : asl_toreg_16(0x1, &D5);       // ASL.W	#$01,D5
  DEF_ROMLOC(13926) : btst_tomem_8(0x4, A0 + 0x22); // BTST.B	#$04,34(A0)
  DEF_ROMLOC(1392C) : if (!CCR_EQ) goto rom_13966;  // BNE.B	$13966
  DEF_ROMLOC(1392E)
      : move_toreg_16(read_16(A0 + 0x10), &D0);       // MOVE.W	16(A0),D0
  DEF_ROMLOC(13932) : btst_tomem_8(0x2, 0xFFFFF602);  // BTST.B	#$02,$F602
  DEF_ROMLOC(13938) : if (CCR_EQ) goto rom_1394C;     // BEQ.B	$1394C
  DEF_ROMLOC(1393A) : bset_tomem_8(0x0, A0 + 0x22);   // BSET.B	#$00,34(A0)
  DEF_ROMLOC(13940) : sub_toreg_16(D5, &D0);          // SUB.W	D5,D0
  DEF_ROMLOC(13942) : move_toreg_16(D6, &D1);         // MOVE.W	D6,D1
  DEF_ROMLOC(13944) : neg_reg_16(&D1);                // NEG.W	D1
  DEF_ROMLOC(13946) : cmp_toreg_16(D1, &D0);          // CMP.W	D1,D0
  DEF_ROMLOC(13948) : if (CCR_GT) goto rom_1394C;     // BGT.B	$1394C
  DEF_ROMLOC(1394A) : move_toreg_16(D1, &D0);         // MOVE.W	D1,D0
  DEF_ROMLOC(1394C) : btst_tomem_8(0x3, 0xFFFFF602);  // BTST.B	#$03,$F602
  DEF_ROMLOC(13952) : if (CCR_EQ) goto rom_13962;     // BEQ.B	$13962
  DEF_ROMLOC(13954) : bclr_tomem_8(0x0, A0 + 0x22);   // BCLR.B	#$00,34(A0)
  DEF_ROMLOC(1395A) : add_toreg_16(D5, &D0);          // ADD.W	D5,D0
  DEF_ROMLOC(1395C) : cmp_toreg_16(D6, &D0);          // CMP.W	D6,D0
  DEF_ROMLOC(1395E) : if (CCR_LT) goto rom_13962;     // BLT.B	$13962
  DEF_ROMLOC(13960) : move_toreg_16(D6, &D0);         // MOVE.W	D6,D0
  DEF_ROMLOC(13962) : move_tomem_16(D0, A0 + 0x10);   // MOVE.W	D0,16(A0)
  DEF_ROMLOC(13966) : cmp_tomem_16(0x60, 0xFFFFF73E); // CMPI.W	#$0060,$F73E
  DEF_ROMLOC(1396C) : if (CCR_EQ) goto rom_13978;     // BEQ.B	$13978
  DEF_ROMLOC(1396E) : if (CCR_CC) goto rom_13974;     // BCC.B	$13974
  DEF_ROMLOC(13970) : add_tomem_16(0x4, 0xFFFFF73E);  // ADDQ.W	#$04,$F73E
  DEF_ROMLOC(13974) : sub_tomem_16(0x2, 0xFFFFF73E);  // SUBQ.W	#$02,$F73E
  DEF_ROMLOC(13978)
      : cmp_tomem_16(0xFFFFFC00, A0 + 0x12);      // CMPI.W	#$FC00,18(A0)
  DEF_ROMLOC(1397E) : if (CCR_CS) goto rom_139A6; // BCS.B	$139A6
  DEF_ROMLOC(13980)
      : move_toreg_16(read_16(A0 + 0x10), &D0);     // MOVE.W	16(A0),D0
  DEF_ROMLOC(13984) : move_toreg_16(D0, &D1);       // MOVE.W	D0,D1
  DEF_ROMLOC(13986) : asr_toreg_16(0x5, &D1);       // ASR.W	#$05,D1
  DEF_ROMLOC(13988) : if (CCR_EQ) goto rom_139A6;   // BEQ.B	$139A6
  DEF_ROMLOC(1398A) : if (CCR_MI) goto rom_1399A;   // BMI.B	$1399A
  DEF_ROMLOC(1398C) : sub_toreg_16(D1, &D0);        // SUB.W	D1,D0
  DEF_ROMLOC(1398E) : if (CCR_CC) goto rom_13994;   // BCC.B	$13994
  DEF_ROMLOC(13990) : move_toreg_16(0x0, &D0);      // MOVE.W	#$0000,D0
  DEF_ROMLOC(13994) : move_tomem_16(D0, A0 + 0x10); // MOVE.W	D0,16(A0)
  DEF_ROMLOC(13998) : return;                       // RTS
  DEF_ROMLOC(1399A) : sub_toreg_16(D1, &D0);        // SUB.W	D1,D0
  DEF_ROMLOC(1399C) : if (CCR_CS) goto rom_139A2;   // BCS.B	$139A2
  DEF_ROMLOC(1399E) : move_toreg_16(0x0, &D0);      // MOVE.W	#$0000,D0
  DEF_ROMLOC(139A2) : move_tomem_16(D0, A0 + 0x10); // MOVE.W	D0,16(A0)
  DEF_ROMLOC(139A6) : return;                       // RTS
}
ROMFUNC(rom_139D8) {
  DEF_ROMLOC(139D8)
      : move_toreg_32(read_32(A0 + 0x8), &D1); // MOVE.L	8(A0),D1
  DEF_ROMLOC(139DC)
      : move_toreg_16(read_16(A0 + 0x10), &D0); // MOVE.W	16(A0),D0
  DEF_ROMLOC(139E0) : ext_reg_32(&D0);          // EXT.L	D0
  DEF_ROMLOC(139E2) : asl_toreg_32(0x8, &D0);   // ASL.L	#$08,D0
  DEF_ROMLOC(139E4) : add_toreg_32(D0, &D1);    // ADD.L	D0,D1
  DEF_ROMLOC(139E6) : SWAPWORDS(D1);            // SWAP.W	D1
  DEF_ROMLOC(139E8)
      : move_toreg_16(read_16(0xFFFFF728), &D0);  // MOVE.W	$F728,D0
  DEF_ROMLOC(139EC) : add_toreg_16(0x10, &D0);    // ADDI.W	#$0010,D0
  DEF_ROMLOC(139F0) : cmp_toreg_16(D1, &D0);      // CMP.W	D1,D0
  DEF_ROMLOC(139F2) : if (CCR_HI) goto rom_13A40; // BHI.B	$13A40
  DEF_ROMLOC(139F4)
      : move_toreg_16(read_16(0xFFFFF72A), &D0);   // MOVE.W	$F72A,D0
  DEF_ROMLOC(139F8) : add_toreg_16(0x128, &D0);    // ADDI.W	#$0128,D0
  DEF_ROMLOC(139FC) : tst_mem_8(f_lockscreen);     // TST.B	$F7AA
  DEF_ROMLOC(13A00) : if (!CCR_EQ) goto rom_13A06; // BNE.B	$13A06
  DEF_ROMLOC(13A02) : add_toreg_16(0x40, &D0);     // ADDI.W	#$0040,D0
  DEF_ROMLOC(13A06) : cmp_toreg_16(D1, &D0);       // CMP.W	D1,D0
  DEF_ROMLOC(13A08) : if (CCR_LS) goto rom_13A40;  // BLS.B	$13A40
  DEF_ROMLOC(13A0A)
      : move_toreg_16(read_16(0xFFFFF72E), &D0); // MOVE.W	$F72E,D0
  DEF_ROMLOC(13A0E) : add_toreg_16(0xE0, &D0);   // ADDI.W	#$00E0,D0
  DEF_ROMLOC(13A12)
      : cmp_toreg_16(read_16(A0 + 0xC), &D0);     // CMP.W
                                                  // 12(A0),D0
  DEF_ROMLOC(13A16) : if (CCR_LT) goto rom_13A1A; // BLT.B	$13A1A
  DEF_ROMLOC(13A18) : return;                     // RTS
  DEF_ROMLOC(13A1A)
      : cmp_tomem_16(ZONE16_SBZ | 1, v_zone); // CMPI.W
                                              // #$0501,$FE10
  DEF_ROMLOC(13A20) : if (!CCR_EQ) {
    rom_1B84E();
    return;
  } // BNE.W	$1B84E
  DEF_ROMLOC(13A24)
      : cmp_tomem_16(0x2000, 0xFFFFD008); // CMPI.W
                                          // #$2000,$D008
  DEF_ROMLOC(13A2A) : if (CCR_CS) {
    rom_1B84E();
    return;
  }                                          // BCS.W	$1B84E
  DEF_ROMLOC(13A2E) : clr_mem_8(0xFFFFFE30); // CLR.B	$FE30
  DEF_ROMLOC(13A32)
      : move_tomem_16(0x1, 0xFFFFFE02); // MOVE.W	#$0001,$FE02
  DEF_ROMLOC(13A38)
      : move_tomem_16(ZONE16_LZ | 3, v_zone);       // MOVE.W
                                                    // #$0103,$FE10
  DEF_ROMLOC(13A3E) : return;                       // RTS
  DEF_ROMLOC(13A40) : move_tomem_16(D0, A0 + 0x8);  // MOVE.W	D0,8(A0)
  DEF_ROMLOC(13A44) : move_tomem_16(0x0, A0 + 0xA); // MOVE.W	#$0000,10(A0)
  DEF_ROMLOC(13A4A)
      : move_tomem_16(0x0, A0 + 0x10); // MOVE.W	#$0000,16(A0)
  DEF_ROMLOC(13A50)
      : move_tomem_16(0x0, A0 + 0x14); // MOVE.W	#$0000,20(A0)
  goto rom_13A0A;                      // BRA.B	$13A0A
}
ROMFUNC(rom_13A58) {
  DEF_ROMLOC(13A58) : tst_mem_8(0xFFFFF7CA);       // TST.B	$F7CA
  DEF_ROMLOC(13A5C) : if (!CCR_EQ) goto rom_13A7E; // BNE.B	$13A7E
  DEF_ROMLOC(13A5E)
      : move_toreg_16(read_16(A0 + 0x14), &D0);              // MOVE.W	20(A0),D0
  DEF_ROMLOC(13A62) : if (CCR_PL) goto rom_13A66;            // BPL.B	$13A66
  DEF_ROMLOC(13A64) : neg_reg_16(&D0);                       // NEG.W	D0
  DEF_ROMLOC(13A66) : cmp_toreg_16(0x80, &D0);               // CMPI.W	#$0080,D0
  DEF_ROMLOC(13A6A) : if (CCR_CS) goto rom_13A7E;            // BCS.B	$13A7E
  DEF_ROMLOC(13A6C) : move_toreg_8(read_8(0xFFFFF602), &D0); // MOVE.B	$F602,D0
  DEF_ROMLOC(13A70) : and_toreg_8(0xC, &D0);                 // ANDI.B	#$0C,D0
  DEF_ROMLOC(13A74) : if (!CCR_EQ) goto rom_13A7E;           // BNE.B	$13A7E
  DEF_ROMLOC(13A76) : btst_tomem_8(0x1, 0xFFFFF602); // BTST.B	#$01,$F602
  DEF_ROMLOC(13A7C) : if (!CCR_EQ) {
    rom_13A80();
    return;
  }                           // BNE.B	$13A80
  DEF_ROMLOC(13A7E) : return; // RTS
}
ROMFUNC(rom_13A80) {
  DEF_ROMLOC(13A80) : btst_tomem_8(0x2, A0 + 0x22); // BTST.B	#$02,34(A0)
  DEF_ROMLOC(13A86) : if (CCR_EQ) goto rom_13A8A;   // BEQ.B	$13A8A
  DEF_ROMLOC(13A88) : return;                       // RTS
  DEF_ROMLOC(13A8A) : bset_tomem_8(0x2, A0 + 0x22); // BSET.B	#$02,34(A0)
  DEF_ROMLOC(13A90) : move_tomem_8(0xE, A0 + 0x16); // MOVE.B	#$0E,22(A0)
  DEF_ROMLOC(13A96) : move_tomem_8(0x7, A0 + 0x17); // MOVE.B	#$07,23(A0)
  DEF_ROMLOC(13A9C) : move_tomem_8(0x2, A0 + 0x1C); // MOVE.B	#$02,28(A0)
  DEF_ROMLOC(13AA2) : add_tomem_16(0x5, A0 + 0xC);  // ADDQ.W	#$05,12(A0)
  DEF_ROMLOC(13AA6) : move_toreg_16(SFX_ROLL, &D0); // MOVE.W	#$00BE,D0
  DEF_ROMLOC(13AAA) : play_sound_special();         // JSR	$00001394
  DEF_ROMLOC(13AB0) : tst_mem_16(A0 + 0x14);        // TST.W	20(A0)
  DEF_ROMLOC(13AB4) : if (!CCR_EQ) goto rom_13ABC;  // BNE.B	$13ABC
  DEF_ROMLOC(13AB6)
      : move_tomem_16(0x200, A0 + 0x14); // MOVE.W
                                         // #$0200,20(A0)
  DEF_ROMLOC(13ABC) : return;            // RTS
}

// animate sonic sprite

ROMFUNC(rom_140E0) {
  DEF_ROMLOC(140E0) : move_toreg_32(0x0, &D1); // MOVEQ.L	$00,D1
  DEF_ROMLOC(140E2)
      : move_toreg_8(read_8(A0 + 0x1B), &D1); // MOVE.B
                                              // 27(A0),D1
  DEF_ROMLOC(140E6)
      : move_toreg_8(read_8((s32)A1 + (s8)0x1 + (s16)D1),
                     &D0);                                 // MOVE.B	1(A1,D1),D0
  DEF_ROMLOC(140EA) : if (CCR_MI) goto rom_140F6;          // BMI.B	$140F6
  DEF_ROMLOC(140EC) : move_tomem_8(D0, A0 + 0x1A);         // MOVE.B	D0,26(A0)
  DEF_ROMLOC(140F0) : add_tomem_8(0x1, A0 + 0x1B);         // ADDQ.B	#$01,27(A0)
  DEF_ROMLOC(140F4) : return;                              // RTS
  DEF_ROMLOC(140F6) : add_toreg_8(0x1, &D0);               // ADDQ.B	#$01,D0
  DEF_ROMLOC(140F8) : if (!CCR_EQ) goto rom_14106;         // BNE.B	$14106
  DEF_ROMLOC(140FA) : move_tomem_8(0x0, A0 + 0x1B);        // MOVE.B	#$00,27(A0)
  DEF_ROMLOC(14100) : move_toreg_8(read_8(A1 + 0x1), &D0); // MOVE.B	1(A1),D0
  DEF_ROMLOC(14104) : goto rom_140EC;                      // BRA.B	$140EC
  DEF_ROMLOC(14106) : add_toreg_8(0x1, &D0);               // ADDQ.B	#$01,D0
  DEF_ROMLOC(14108) : if (!CCR_EQ) goto rom_1411A;         // BNE.B	$1411A
  DEF_ROMLOC(1410A)
      : move_toreg_8(read_8((s32)A1 + (s8)0x2 + (s16)D1),
                     &D0);                        // MOVE.B	2(A1,D1),D0
  DEF_ROMLOC(1410E) : sub_tomem_8(D0, A0 + 0x1B); // SUB.B	D0,27(A0)
  DEF_ROMLOC(14112) : sub_toreg_8(D0, &D1);       // SUB.B	D0,D1
  DEF_ROMLOC(14114)
      : move_toreg_8(read_8((s32)A1 + (s8)0x1 + (s16)D1),
                     &D0);                         // MOVE.B	1(A1,D1),D0
  DEF_ROMLOC(14118) : goto rom_140EC;              // BRA.B	$140EC
  DEF_ROMLOC(1411A) : add_toreg_8(0x1, &D0);       // ADDQ.B	#$01,D0
  DEF_ROMLOC(1411C) : if (!CCR_EQ) goto rom_14124; // BNE.B	$14124
  DEF_ROMLOC(1411E)
      : move_tomem_8(read_8((s32)A1 + (s8)0x2 + (s16)D1),
                     A0 + 0x1C); // MOVE.B	2(A1,D1),28(A0)
  DEF_ROMLOC(14124) : return;    // RTS
}

ROMFUNC(rom_14098) {
  DEF_ROMLOC(14098) : move_toreg_32(0x1421C, &A1); // LEA.L	$0001421C,A1
  DEF_ROMLOC(1409E) : move_toreg_32(0x0, &D0);     // MOVEQ.L	$00,D0
  DEF_ROMLOC(140A0)
      : move_toreg_8(read_8(A0 + 0x1C), &D0); // MOVE.B
                                              // 28(A0),D0
  DEF_ROMLOC(140A4)
      : cmp_toreg_8(read_8(A0 + 0x1D), &D0);        // CMP.B
                                                    // 29(A0),D0
  DEF_ROMLOC(140A8) : if (CCR_EQ) goto rom_140BA;   // BEQ.B	$140BA
  DEF_ROMLOC(140AA) : move_tomem_8(D0, A0 + 0x1D);  // MOVE.B	D0,29(A0)
  DEF_ROMLOC(140AE) : move_tomem_8(0x0, A0 + 0x1B); // MOVE.B	#$00,27(A0)
  DEF_ROMLOC(140B4) : move_tomem_8(0x0, A0 + 0x1E); // MOVE.B	#$00,30(A0)
  DEF_ROMLOC(140BA) : add_toreg_16(D0, &D0);        // ADD.W	D0,D0
  DEF_ROMLOC(140BC)
      : add_toreg_16(read_16((s32)A1 + (s8)0x0 + (s16)D0),
                     &A1);                           // ADDA.W	0(A1,D0),A1
  DEF_ROMLOC(140C0) : move_toreg_8(read_8(A1), &D0); // MOVE.B	(A1),D0
  DEF_ROMLOC(140C2) : if (CCR_MI) goto rom_14126;    // BMI.B	$14126
  DEF_ROMLOC(140C4)
      : move_toreg_8(read_8(A0 + 0x22), &D1); // MOVE.B
                                              // 34(A0),D1
  DEF_ROMLOC(140C8) : and_toreg_8(0x1, &D1);  // ANDI.B	#$01,D1
  DEF_ROMLOC(140CC)
      : and_tomem_8(0xFFFFFFFC, A0 + 0x1);         // ANDI.B
                                                   // #$FC,1(A0)
  DEF_ROMLOC(140D2) : or_tomem_8(D1, A0 + 0x1);    // OR.B	D1,1(A0)
  DEF_ROMLOC(140D6) : sub_tomem_8(0x1, A0 + 0x1E); // SUBQ.B	#$01,30(A0)
  DEF_ROMLOC(140DA) : if (CCR_PL) goto rom_140F4;  // BPL.B	$140F4
  DEF_ROMLOC(140DC) : move_tomem_8(D0, A0 + 0x1E); // MOVE.B	D0,30(A0)
  DEF_ROMLOC(140E0) : move_toreg_32(0x0, &D1);     // MOVEQ.L	$00,D1
  DEF_ROMLOC(140E2)
      : move_toreg_8(read_8(A0 + 0x1B), &D1); // MOVE.B
                                              // 27(A0),D1
  DEF_ROMLOC(140E6)
      : move_toreg_8(read_8((s32)A1 + (s8)0x1 + (s16)D1),
                     &D0);                                 // MOVE.B	1(A1,D1),D0
  DEF_ROMLOC(140EA) : if (CCR_MI) goto rom_140F6;          // BMI.B	$140F6
  DEF_ROMLOC(140EC) : move_tomem_8(D0, A0 + 0x1A);         // MOVE.B	D0,26(A0)
  DEF_ROMLOC(140F0) : add_tomem_8(0x1, A0 + 0x1B);         // ADDQ.B	#$01,27(A0)
  DEF_ROMLOC(140F4) : return;                              // RTS
  DEF_ROMLOC(140F6) : add_toreg_8(0x1, &D0);               // ADDQ.B	#$01,D0
  DEF_ROMLOC(140F8) : if (!CCR_EQ) goto rom_14106;         // BNE.B	$14106
  DEF_ROMLOC(140FA) : move_tomem_8(0x0, A0 + 0x1B);        // MOVE.B	#$00,27(A0)
  DEF_ROMLOC(14100) : move_toreg_8(read_8(A1 + 0x1), &D0); // MOVE.B	1(A1),D0
  DEF_ROMLOC(14104) : goto rom_140EC;                      // BRA.B	$140EC
  DEF_ROMLOC(14106) : add_toreg_8(0x1, &D0);               // ADDQ.B	#$01,D0
  DEF_ROMLOC(14108) : if (!CCR_EQ) goto rom_1411A;         // BNE.B	$1411A
  DEF_ROMLOC(1410A)
      : move_toreg_8(read_8((s32)A1 + (s8)0x2 + (s16)D1),
                     &D0);                        // MOVE.B	2(A1,D1),D0
  DEF_ROMLOC(1410E) : sub_tomem_8(D0, A0 + 0x1B); // SUB.B	D0,27(A0)
  DEF_ROMLOC(14112) : sub_toreg_8(D0, &D1);       // SUB.B	D0,D1
  DEF_ROMLOC(14114)
      : move_toreg_8(read_8((s32)A1 + (s8)0x1 + (s16)D1),
                     &D0);                         // MOVE.B	1(A1,D1),D0
  DEF_ROMLOC(14118) : goto rom_140EC;              // BRA.B	$140EC
  DEF_ROMLOC(1411A) : add_toreg_8(0x1, &D0);       // ADDQ.B	#$01,D0
  DEF_ROMLOC(1411C) : if (!CCR_EQ) goto rom_14124; // BNE.B	$14124
  DEF_ROMLOC(1411E)
      : move_tomem_8(read_8((s32)A1 + (s8)0x2 + (s16)D1),
                     A0 + 0x1C);                   // MOVE.B	2(A1,D1),28(A0)
  DEF_ROMLOC(14124) : return;                      // RTS
  DEF_ROMLOC(14126) : sub_tomem_8(0x1, A0 + 0x1E); // SUBQ.B	#$01,30(A0)
  DEF_ROMLOC(1412A) : if (CCR_PL) goto rom_140F4;  // BPL.B	$140F4
  DEF_ROMLOC(1412C) : add_toreg_8(0x1, &D0);       // ADDQ.B	#$01,D0
  DEF_ROMLOC(1412E) : if (!CCR_EQ) goto rom_141A6; // BNE.W	$141A6
  DEF_ROMLOC(14132) : move_toreg_32(0x0, &D1);     // MOVEQ.L	$00,D1
  DEF_ROMLOC(14134)
      : move_toreg_8(read_8(A0 + 0x26), &D0); // MOVE.B
                                              // 38(A0),D0
  DEF_ROMLOC(14138)
      : move_toreg_8(read_8(A0 + 0x22), &D2);      // MOVE.B	34(A0),D2
  DEF_ROMLOC(1413C) : and_toreg_8(0x1, &D2);       // ANDI.B	#$01,D2
  DEF_ROMLOC(14140) : if (!CCR_EQ) goto rom_14144; // BNE.B	$14144
  DEF_ROMLOC(14142) : not_reg_8(&D0);              // NOT.B	D0
  DEF_ROMLOC(14144) : add_toreg_8(0x10, &D0);      // ADDI.B	#$10,D0
  DEF_ROMLOC(14148) : if (CCR_PL) goto rom_1414C;  // BPL.B	$1414C
  DEF_ROMLOC(1414A) : move_toreg_32(0x3, &D1);     // MOVEQ.L	$03,D1
  DEF_ROMLOC(1414C)
      : and_tomem_8(0xFFFFFFFC, A0 + 0x1);          // ANDI.B
                                                    // #$FC,1(A0)
  DEF_ROMLOC(14152) : eor_toreg_8(D1, &D2);         // EOR.B	D1,D2
  DEF_ROMLOC(14154) : or_tomem_8(D2, A0 + 0x1);     // OR.B	D2,1(A0)
  DEF_ROMLOC(14158) : btst_tomem_8(0x5, A0 + 0x22); // BTST.B	#$05,34(A0)
  DEF_ROMLOC(1415E) : if (!CCR_EQ) goto rom_141EA;  // BNE.W	$141EA
  DEF_ROMLOC(14162) : lsr_toreg_8(0x4, &D0);        // LSR.B	#$04,D0
  DEF_ROMLOC(14164) : and_toreg_8(0x6, &D0);        // ANDI.B	#$06,D0
  DEF_ROMLOC(14168)
      : move_toreg_16(read_16(A0 + 0x14), &D2);    // MOVE.W	20(A0),D2
  DEF_ROMLOC(1416C) : if (CCR_PL) goto rom_14170;  // BPL.B	$14170
  DEF_ROMLOC(1416E) : neg_reg_16(&D2);             // NEG.W	D2
  DEF_ROMLOC(14170) : move_toreg_32(0x14262, &A1); // LEA.L	$00014262,A1
  DEF_ROMLOC(14176) : cmp_toreg_16(0x600, &D2);    // CMPI.W	#$0600,D2
  DEF_ROMLOC(1417A) : if (CCR_CC) goto rom_14188;  // BCC.B	$14188
  DEF_ROMLOC(1417C) : move_toreg_32(0x1425A, &A1); // LEA.L	$0001425A,A1
  DEF_ROMLOC(14182) : move_toreg_8(D0, &D1);       // MOVE.B	D0,D1
  DEF_ROMLOC(14184) : lsr_toreg_8(0x1, &D1);       // LSR.B	#$01,D1
  DEF_ROMLOC(14186) : add_toreg_8(D1, &D0);        // ADD.B	D1,D0
  DEF_ROMLOC(14188) : add_toreg_8(D0, &D0);        // ADD.B	D0,D0
  DEF_ROMLOC(1418A) : move_toreg_8(D0, &D3);       // MOVE.B	D0,D3
  DEF_ROMLOC(1418C) : neg_reg_16(&D2);             // NEG.W	D2
  DEF_ROMLOC(1418E) : add_toreg_16(0x800, &D2);    // ADDI.W	#$0800,D2
  DEF_ROMLOC(14192) : if (CCR_PL) goto rom_14196;  // BPL.B	$14196
  DEF_ROMLOC(14194) : move_toreg_32(0x0, &D2);     // MOVEQ.L	$00,D2
  DEF_ROMLOC(14196) : lsr_toreg_16(0x8, &D2);      // LSR.W	#$08,D2
  DEF_ROMLOC(14198) : move_tomem_8(D2, A0 + 0x1E); // MOVE.B	D2,30(A0)
  DEF_ROMLOC(1419C) : rom_140E0();                 // BSR.W	$140E0
  DEF_ROMLOC(141A0) : add_tomem_8(D3, A0 + 0x1A);  // ADD.B	D3,26(A0)
  DEF_ROMLOC(141A4) : return;                      // RTS
  DEF_ROMLOC(141A6) : add_toreg_8(0x1, &D0);       // ADDQ.B	#$01,D0
  DEF_ROMLOC(141A8) : if (!CCR_EQ) goto rom_141EA; // BNE.B	$141EA
  DEF_ROMLOC(141AA)
      : move_toreg_16(read_16(A0 + 0x14), &D2);    // MOVE.W	20(A0),D2
  DEF_ROMLOC(141AE) : if (CCR_PL) goto rom_141B2;  // BPL.B	$141B2
  DEF_ROMLOC(141B0) : neg_reg_16(&D2);             // NEG.W	D2
  DEF_ROMLOC(141B2) : move_toreg_32(0x14272, &A1); // LEA.L	$00014272,A1
  DEF_ROMLOC(141B8) : cmp_toreg_16(0x600, &D2);    // CMPI.W	#$0600,D2
  DEF_ROMLOC(141BC) : if (CCR_CC) goto rom_141C4;  // BCC.B	$141C4
  DEF_ROMLOC(141BE) : move_toreg_32(0x1426A, &A1); // LEA.L	$0001426A,A1
  DEF_ROMLOC(141C4) : neg_reg_16(&D2);             // NEG.W	D2
  DEF_ROMLOC(141C6) : add_toreg_16(0x400, &D2);    // ADDI.W	#$0400,D2
  DEF_ROMLOC(141CA) : if (CCR_PL) goto rom_141CE;  // BPL.B	$141CE
  DEF_ROMLOC(141CC) : move_toreg_32(0x0, &D2);     // MOVEQ.L	$00,D2
  DEF_ROMLOC(141CE) : lsr_toreg_16(0x8, &D2);      // LSR.W	#$08,D2
  DEF_ROMLOC(141D0) : move_tomem_8(D2, A0 + 0x1E); // MOVE.B	D2,30(A0)
  DEF_ROMLOC(141D4)
      : move_toreg_8(read_8(A0 + 0x22), &D1); // MOVE.B
                                              // 34(A0),D1
  DEF_ROMLOC(141D8) : and_toreg_8(0x1, &D1);  // ANDI.B	#$01,D1
  DEF_ROMLOC(141DC)
      : and_tomem_8(0xFFFFFFFC, A0 + 0x1);      // ANDI.B
                                                // #$FC,1(A0)
  DEF_ROMLOC(141E2) : or_tomem_8(D1, A0 + 0x1); // OR.B	D1,1(A0)
  DEF_ROMLOC(141E6) : goto rom_140E0;           // BRA.W	$140E0
  DEF_ROMLOC(141EA)
      : move_toreg_16(read_16(A0 + 0x14), &D2);    // MOVE.W	20(A0),D2
  DEF_ROMLOC(141EE) : if (CCR_MI) goto rom_141F2;  // BMI.B	$141F2
  DEF_ROMLOC(141F0) : neg_reg_16(&D2);             // NEG.W	D2
  DEF_ROMLOC(141F2) : add_toreg_16(0x800, &D2);    // ADDI.W	#$0800,D2
  DEF_ROMLOC(141F6) : if (CCR_PL) goto rom_141FA;  // BPL.B	$141FA
  DEF_ROMLOC(141F8) : move_toreg_32(0x0, &D2);     // MOVEQ.L	$00,D2
  DEF_ROMLOC(141FA) : lsr_toreg_16(0x6, &D2);      // LSR.W	#$06,D2
  DEF_ROMLOC(141FC) : move_tomem_8(D2, A0 + 0x1E); // MOVE.B	D2,30(A0)
  DEF_ROMLOC(14200) : move_toreg_32(0x1427A, &A1); // LEA.L	$0001427A,A1
  DEF_ROMLOC(14206)
      : move_toreg_8(read_8(A0 + 0x22), &D1); // MOVE.B
                                              // 34(A0),D1
  DEF_ROMLOC(1420A) : and_toreg_8(0x1, &D1);  // ANDI.B	#$01,D1
  DEF_ROMLOC(1420E)
      : and_tomem_8(0xFFFFFFFC, A0 + 0x1);      // ANDI.B
                                                // #$FC,1(A0)
  DEF_ROMLOC(14214) : or_tomem_8(D1, A0 + 0x1); // OR.B	D1,1(A0)
  goto rom_140E0;                               // BRA.W	$140E0
}

// dynamically load sonic sprites into vram

ROMFUNC(rom_14312) {
  DEF_ROMLOC(14312) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(14314)
      : move_toreg_8(read_8(A0 + 0x1A), &D0);               // MOVE.B
                                                            // 26(A0),D0
  DEF_ROMLOC(14318) : cmp_toreg_8(read_8(0xFFFFF766), &D0); // CMP.B	$F766,D0
  DEF_ROMLOC(1431C) : if (CCR_EQ) goto rom_1436A;           // BEQ.B	$1436A
  DEF_ROMLOC(1431E) : move_tomem_8(D0, 0xFFFFF766);         // MOVE.B	D0,$F766
  DEF_ROMLOC(14322) : move_toreg_32(0x22310, &A2); // LEA.L	$00022310,A2
  DEF_ROMLOC(14328) : add_toreg_16(D0, &D0);       // ADD.W	D0,D0
  DEF_ROMLOC(1432A)
      : add_toreg_16(read_16((s32)A2 + (s8)0x0 + (s16)D0),
                     &A2);                             // ADDA.W	0(A2,D0),A2
  DEF_ROMLOC(1432E) : move_toreg_32(0x0, &D1);         // MOVEQ.L	$00,D1
  DEF_ROMLOC(14330) : move_toreg_8(read_8(A2++), &D1); // MOVE.B	(A2)+,D1
  DEF_ROMLOC(14332) : sub_toreg_8(0x1, &D1);           // SUBQ.B	#$01,D1
  DEF_ROMLOC(14334) : if (CCR_MI) goto rom_1436A;      // BMI.B	$1436A
  DEF_ROMLOC(14336) : move_toreg_32(0xFFFFC800, &A3);  // LEA.L	$C800,A3
  DEF_ROMLOC(1433A) : move_tomem_8(0x1, 0xFFFFF767);   // MOVE.B	#$01,$F767
  DEF_ROMLOC(14340) : move_toreg_32(0x0, &D2);         // MOVEQ.L	$00,D2
  DEF_ROMLOC(14342) : move_toreg_8(read_8(A2++), &D2); // MOVE.B	(A2)+,D2
  DEF_ROMLOC(14344) : move_toreg_16(D2, &D0);          // MOVE.W	D2,D0
  DEF_ROMLOC(14346) : lsr_toreg_8(0x4, &D0);           // LSR.B	#$04,D0
  DEF_ROMLOC(14348) : lsl_toreg_16(0x8, &D2);          // LSL.W	#$08,D2
  DEF_ROMLOC(1434A) : move_toreg_8(read_8(A2++), &D2); // MOVE.B	(A2)+,D2
  DEF_ROMLOC(1434C) : lsl_toreg_16(0x5, &D2);          // LSL.W	#$05,D2
  DEF_ROMLOC(1434E) : move_toreg_32(0x22610, &A1);     // LEA.L	$00022610,A1
  DEF_ROMLOC(14354) : add_toreg_32(D2, &A1);           // ADDA.L	D2,A1
  DEF_ROMLOC(14356) : D2 = read_32(A1);
  A1 += 4;
  D3 = read_32(A1);
  A1 += 4;
  D4 = read_32(A1);
  A1 += 4;
  D5 = read_32(A1);
  A1 += 4;
  D6 = read_32(A1);
  A1 += 4;
  A4 = read_32(A1);
  A1 += 4;
  A5 = read_32(A1);
  A1 += 4;
  A6 = read_32(A1);
  A1 += 4;
  // TODO; // MOVEM.L	(A1)+,D2-D6/A4-A6
  DEF_ROMLOC(1435A) : write_32(A3 + 0x00, D2);
  write_32(A3 + 0x04, D3);
  write_32(A3 + 0x08, D4);
  write_32(A3 + 0x0C, D5);
  write_32(A3 + 0x10, D6);
  write_32(A3 + 0x14, A4);
  write_32(A3 + 0x18, A5);
  write_32(A3 + 0x1C, A6);
  // TODO; // MOVEM.L	D2-D6/A4-A6,(A3)
  DEF_ROMLOC(1435E) : move_toreg_32(A3 + 0x20, &A3); // LEA.L	32(A3),A3
  DEF_ROMLOC(14362) : dec_reg_16(&D0);
  if ((D0 & 0xffff) != 0xffff)
    goto rom_14356; // DBF.W	D0,$14356
  DEF_ROMLOC(14366) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_14340;           // DBF.W	D1,$14340
  DEF_ROMLOC(1436A) : return; // RTS
}
ROMFUNC(rom_14D56) {
  DEF_ROMLOC(14D56) : btst_tomem_8(0x3, A0 + 0x22); // BTST.B	#$03,34(A0)
  DEF_ROMLOC(14D5C) : if (CCR_EQ) goto rom_14D6A;   // BEQ.B	$14D6A
  DEF_ROMLOC(14D5E) : move_toreg_32(0x0, &D0);      // MOVEQ.L	$00,D0
  DEF_ROMLOC(14D60) : move_tomem_8(D0, 0xFFFFF768); // MOVE.B	D0,$F768
  DEF_ROMLOC(14D64) : move_tomem_8(D0, 0xFFFFF76A); // MOVE.B	D0,$F76A
  DEF_ROMLOC(14D68) : return;                       // RTS
  DEF_ROMLOC(14D6A) : move_toreg_32(0x3, &D0);      // MOVEQ.L	$03,D0
  DEF_ROMLOC(14D6C) : move_tomem_8(D0, 0xFFFFF768); // MOVE.B	D0,$F768
  DEF_ROMLOC(14D70) : move_tomem_8(D0, 0xFFFFF76A); // MOVE.B	D0,$F76A
  DEF_ROMLOC(14D74)
      : move_toreg_8(read_8(A0 + 0x26), &D0);     // MOVE.B	38(A0),D0
  DEF_ROMLOC(14D78) : add_toreg_8(0x20, &D0);     // ADDI.B	#$20,D0
  DEF_ROMLOC(14D7C) : if (CCR_PL) goto rom_14D8C; // BPL.B	$14D8C
  DEF_ROMLOC(14D7E)
      : move_toreg_8(read_8(A0 + 0x26), &D0);     // MOVE.B	38(A0),D0
  DEF_ROMLOC(14D82) : if (CCR_PL) goto rom_14D86; // BPL.B	$14D86
  DEF_ROMLOC(14D84) : sub_toreg_8(0x1, &D0);      // SUBQ.B	#$01,D0
  DEF_ROMLOC(14D86) : add_toreg_8(0x20, &D0);     // ADDI.B	#$20,D0
  goto rom_14D98;                                 // BRA.B	$14D98
  DEF_ROMLOC(14D8C)
      : move_toreg_8(read_8(A0 + 0x26), &D0);       // MOVE.B	38(A0),D0
  DEF_ROMLOC(14D90) : if (CCR_PL) goto rom_14D94;   // BPL.B	$14D94
  DEF_ROMLOC(14D92) : add_toreg_8(0x1, &D0);        // ADDQ.B	#$01,D0
  DEF_ROMLOC(14D94) : add_toreg_8(0x1F, &D0);       // ADDI.B	#$1F,D0
  DEF_ROMLOC(14D98) : and_toreg_8(0xFFFFFFC0, &D0); // ANDI.B	#$C0,D0
  DEF_ROMLOC(14D9C) : cmp_toreg_8(0x40, &D0);       // CMPI.B	#$40,D0
  DEF_ROMLOC(14DA0) : if (CCR_EQ) {
    rom_15022();
    return;
  }                                                 // BEQ.W	$15022
  DEF_ROMLOC(14DA4) : cmp_toreg_8(0xFFFFFF80, &D0); // CMPI.B	#$80,D0
  DEF_ROMLOC(14DA8) : if (CCR_EQ) {
    rom_14F80();
    return;
  }                                                 // BEQ.W	$14F80
  DEF_ROMLOC(14DAC) : cmp_toreg_8(0xFFFFFFC0, &D0); // CMPI.B	#$C0,D0
  DEF_ROMLOC(14DB0) : if (CCR_EQ) {
    rom_14EE4();
    return;
  } // BEQ.W	$14EE4
  DEF_ROMLOC(14DB4)
      : move_toreg_16(read_16(A0 + 0xC), &D2); // MOVE.W	12(A0),D2
  DEF_ROMLOC(14DB8)
      : move_toreg_16(read_16(A0 + 0x8), &D3); // MOVE.W	8(A0),D3
  DEF_ROMLOC(14DBC) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(14DBE)
      : move_toreg_8(read_8(A0 + 0x16), &D0); // MOVE.B
                                              // 22(A0),D0
  DEF_ROMLOC(14DC2) : ext_reg_16(&D0);        // EXT.W	D0
  DEF_ROMLOC(14DC4) : add_toreg_16(D0, &D2);  // ADD.W	D0,D2
  DEF_ROMLOC(14DC6)
      : move_toreg_8(read_8(A0 + 0x17), &D0);         // MOVE.B
                                                      // 23(A0),D0
  DEF_ROMLOC(14DCA) : ext_reg_16(&D0);                // EXT.W	D0
  DEF_ROMLOC(14DCC) : add_toreg_16(D0, &D3);          // ADD.W	D0,D3
  DEF_ROMLOC(14DCE) : move_toreg_32(0xFFFFF768, &A4); // LEA.L	$F768,A4
  DEF_ROMLOC(14DD2) : move_toreg_16(0x10, &A3);       // MOVEA.W	#$0010,A3
  DEF_ROMLOC(14DD6) : move_toreg_16(0x0, &D6);        // MOVE.W	#$0000,D6
  DEF_ROMLOC(14DDA) : move_toreg_32(0xD, &D5);        // MOVEQ.L	$0D,D5
  DEF_ROMLOC(14DDC) : rom_15136();                    // BSR.W	$15136
  DEF_ROMLOC(14DE0) : move_tomem_16(D1, A7 -= 2);     // MOVE.W	D1,-(A7)
  DEF_ROMLOC(14DE2)
      : move_toreg_16(read_16(A0 + 0xC), &D2); // MOVE.W	12(A0),D2
  DEF_ROMLOC(14DE6)
      : move_toreg_16(read_16(A0 + 0x8), &D3); // MOVE.W	8(A0),D3
  DEF_ROMLOC(14DEA) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(14DEC)
      : move_toreg_8(read_8(A0 + 0x16), &D0); // MOVE.B
                                              // 22(A0),D0
  DEF_ROMLOC(14DF0) : ext_reg_16(&D0);        // EXT.W	D0
  DEF_ROMLOC(14DF2) : add_toreg_16(D0, &D2);  // ADD.W	D0,D2
  DEF_ROMLOC(14DF4)
      : move_toreg_8(read_8(A0 + 0x17), &D0);         // MOVE.B
                                                      // 23(A0),D0
  DEF_ROMLOC(14DF8) : ext_reg_16(&D0);                // EXT.W	D0
  DEF_ROMLOC(14DFA) : neg_reg_16(&D0);                // NEG.W	D0
  DEF_ROMLOC(14DFC) : add_toreg_16(D0, &D3);          // ADD.W	D0,D3
  DEF_ROMLOC(14DFE) : move_toreg_32(0xFFFFF76A, &A4); // LEA.L	$F76A,A4
  DEF_ROMLOC(14E02) : move_toreg_16(0x10, &A3);       // MOVEA.W	#$0010,A3
  DEF_ROMLOC(14E06) : move_toreg_16(0x0, &D6);        // MOVE.W	#$0000,D6
  DEF_ROMLOC(14E0A) : move_toreg_32(0xD, &D5);        // MOVEQ.L	$0D,D5
  DEF_ROMLOC(14E0C) : rom_15136();                    // BSR.W	$15136
  DEF_ROMLOC(14E10)
      : move_toreg_16(read_16((A7 += 2, A7 - 2)), &D0); // MOVE.W	(A7)+,D0
  DEF_ROMLOC(14E12) : rom_14EB8();                      // BSR.W	$14EB8
  DEF_ROMLOC(14E16) : tst_reg_16(&D1);                  // TST.W	D1
  DEF_ROMLOC(14E18) : if (CCR_EQ) goto rom_14E26;       // BEQ.B	$14E26
  DEF_ROMLOC(14E1A) : if (CCR_PL) goto rom_14E28;       // BPL.B	$14E28
  DEF_ROMLOC(14E1C) : cmp_toreg_16(0xFFFFFFF2, &D1);    // CMPI.W	#$FFF2,D1
  DEF_ROMLOC(14E20) : if (CCR_LT) return;               // BLT.B	$14E4E
  DEF_ROMLOC(14E22) : add_tomem_16(D1, A0 + 0xC);       // ADD.W	D1,12(A0)
  DEF_ROMLOC(14E26) : return;                           // RTS
  DEF_ROMLOC(14E28) : cmp_toreg_16(0xE, &D1);           // CMPI.W	#$000E,D1
  DEF_ROMLOC(14E2C) : if (CCR_GT) goto rom_14E34;       // BGT.B	$14E34
  DEF_ROMLOC(14E2E) : add_tomem_16(D1, A0 + 0xC);       // ADD.W	D1,12(A0)
  DEF_ROMLOC(14E32) : return;                           // RTS
  DEF_ROMLOC(14E34) : tst_mem_8(A0 + 0x38);             // TST.B	56(A0)
  DEF_ROMLOC(14E38) : if (!CCR_EQ) goto rom_14E2E;      // BNE.B	$14E2E
  DEF_ROMLOC(14E3A) : bset_tomem_8(0x1, A0 + 0x22);     // BSET.B	#$01,34(A0)
  DEF_ROMLOC(14E40) : bclr_tomem_8(0x5, A0 + 0x22);     // BCLR.B	#$05,34(A0)
  DEF_ROMLOC(14E46) : move_tomem_8(0x1, A0 + 0x1D);     // MOVE.B	#$01,29(A0)
  DEF_ROMLOC(14E4C) : return;                           // RTS
  DEF_ROMLOC(14E4E) : return;                           // RTS
  DEF_ROMLOC(14E72) : return;                           // RTS
  DEF_ROMLOC(14E74)
      : move_toreg_32(read_32(A0 + 0xC), &D3); // MOVE.L	12(A0),D3
  DEF_ROMLOC(14E78)
      : move_toreg_16(read_16(A0 + 0x12), &D0);     // MOVE.W	18(A0),D0
  DEF_ROMLOC(14E7C) : sub_toreg_16(0x38, &D0);      // SUBI.W	#$0038,D0
  DEF_ROMLOC(14E80) : move_tomem_16(D0, A0 + 0x12); // MOVE.W	D0,18(A0)
  DEF_ROMLOC(14E84) : ext_reg_32(&D0);              // EXT.L	D0
  DEF_ROMLOC(14E86) : asl_toreg_32(0x8, &D0);       // ASL.L	#$08,D0
  DEF_ROMLOC(14E88) : sub_toreg_32(D0, &D3);        // SUB.L	D0,D3
  DEF_ROMLOC(14E8A) : move_tomem_32(D3, A0 + 0xC);  // MOVE.L	D3,12(A0)
  DEF_ROMLOC(14E8E) : return;                       // RTS
  DEF_ROMLOC(14E90) : return;                       // RTS
  DEF_ROMLOC(14E92)
      : move_toreg_32(read_32(A0 + 0x8), &D2); // MOVE.L	8(A0),D2
  DEF_ROMLOC(14E96)
      : move_toreg_32(read_32(A0 + 0xC), &D3); // MOVE.L	12(A0),D3
  DEF_ROMLOC(14E9A)
      : move_toreg_16(read_16(A0 + 0x10), &D0); // MOVE.W	16(A0),D0
  DEF_ROMLOC(14E9E) : ext_reg_32(&D0);          // EXT.L	D0
  DEF_ROMLOC(14EA0) : asl_toreg_32(0x8, &D0);   // ASL.L	#$08,D0
  DEF_ROMLOC(14EA2) : sub_toreg_32(D0, &D2);    // SUB.L	D0,D2
  DEF_ROMLOC(14EA4)
      : move_toreg_16(read_16(A0 + 0x12), &D0);    // MOVE.W	18(A0),D0
  DEF_ROMLOC(14EA8) : ext_reg_32(&D0);             // EXT.L	D0
  DEF_ROMLOC(14EAA) : asl_toreg_32(0x8, &D0);      // ASL.L	#$08,D0
  DEF_ROMLOC(14EAC) : sub_toreg_32(D0, &D3);       // SUB.L	D0,D3
  DEF_ROMLOC(14EAE) : move_tomem_32(D2, A0 + 0x8); // MOVE.L	D2,8(A0)
  DEF_ROMLOC(14EB2) : move_tomem_32(D3, A0 + 0xC); // MOVE.L	D3,12(A0)
  DEF_ROMLOC(14EB6) : return;                      // RTS
}
ROMFUNC(rom_14EB8) {
  DEF_ROMLOC(14EB8)
      : move_toreg_8(read_8(0xFFFFF76A), &D2);    // MOVE.B	$F76A,D2
  DEF_ROMLOC(14EBC) : cmp_toreg_16(D0, &D1);      // CMP.W	D0,D1
  DEF_ROMLOC(14EBE) : if (CCR_LE) goto rom_14EC6; // BLE.B	$14EC6
  DEF_ROMLOC(14EC0)
      : move_toreg_8(read_8(0xFFFFF768), &D2);     // MOVE.B	$F768,D2
  DEF_ROMLOC(14EC4) : move_toreg_16(D0, &D1);      // MOVE.W	D0,D1
  DEF_ROMLOC(14EC6) : btst_toreg_32(0x0, &D2);     // BTST.L	#$00,D2
  DEF_ROMLOC(14ECA) : if (!CCR_EQ) goto rom_14ED2; // BNE.B	$14ED2
  DEF_ROMLOC(14ECC) : move_tomem_8(D2, A0 + 0x26); // MOVE.B	D2,38(A0)
  DEF_ROMLOC(14ED0) : return;                      // RTS
  DEF_ROMLOC(14ED2)
      : move_toreg_8(read_8(A0 + 0x26), &D2);       // MOVE.B	38(A0),D2
  DEF_ROMLOC(14ED6) : add_toreg_8(0x20, &D2);       // ADDI.B	#$20,D2
  DEF_ROMLOC(14EDA) : and_toreg_8(0xFFFFFFC0, &D2); // ANDI.B	#$C0,D2
  DEF_ROMLOC(14EDE) : move_tomem_8(D2, A0 + 0x26);  // MOVE.B	D2,38(A0)
  DEF_ROMLOC(14EE2) : return;                       // RTS
}
ROMFUNC(rom_14EE4) {
  DEF_ROMLOC(14EE4)
      : move_toreg_16(read_16(A0 + 0xC), &D2); // MOVE.W	12(A0),D2
  DEF_ROMLOC(14EE8)
      : move_toreg_16(read_16(A0 + 0x8), &D3); // MOVE.W	8(A0),D3
  DEF_ROMLOC(14EEC) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(14EEE)
      : move_toreg_8(read_8(A0 + 0x17), &D0); // MOVE.B
                                              // 23(A0),D0
  DEF_ROMLOC(14EF2) : ext_reg_16(&D0);        // EXT.W	D0
  DEF_ROMLOC(14EF4) : neg_reg_16(&D0);        // NEG.W	D0
  DEF_ROMLOC(14EF6) : add_toreg_16(D0, &D2);  // ADD.W	D0,D2
  DEF_ROMLOC(14EF8)
      : move_toreg_8(read_8(A0 + 0x16), &D0);         // MOVE.B
                                                      // 22(A0),D0
  DEF_ROMLOC(14EFC) : ext_reg_16(&D0);                // EXT.W	D0
  DEF_ROMLOC(14EFE) : add_toreg_16(D0, &D3);          // ADD.W	D0,D3
  DEF_ROMLOC(14F00) : move_toreg_32(0xFFFFF768, &A4); // LEA.L	$F768,A4
  DEF_ROMLOC(14F04) : move_toreg_16(0x10, &A3);       // MOVEA.W	#$0010,A3
  DEF_ROMLOC(14F08) : move_toreg_16(0x0, &D6);        // MOVE.W	#$0000,D6
  DEF_ROMLOC(14F0C) : move_toreg_32(0xD, &D5);        // MOVEQ.L	$0D,D5
  DEF_ROMLOC(14F0E) : rom_15274();                    // BSR.W	$15274
  DEF_ROMLOC(14F12) : move_tomem_16(D1, A7 -= 2);     // MOVE.W	D1,-(A7)
  DEF_ROMLOC(14F14)
      : move_toreg_16(read_16(A0 + 0xC), &D2); // MOVE.W	12(A0),D2
  DEF_ROMLOC(14F18)
      : move_toreg_16(read_16(A0 + 0x8), &D3); // MOVE.W	8(A0),D3
  DEF_ROMLOC(14F1C) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(14F1E)
      : move_toreg_8(read_8(A0 + 0x17), &D0); // MOVE.B
                                              // 23(A0),D0
  DEF_ROMLOC(14F22) : ext_reg_16(&D0);        // EXT.W	D0
  DEF_ROMLOC(14F24) : add_toreg_16(D0, &D2);  // ADD.W	D0,D2
  DEF_ROMLOC(14F26)
      : move_toreg_8(read_8(A0 + 0x16), &D0);         // MOVE.B
                                                      // 22(A0),D0
  DEF_ROMLOC(14F2A) : ext_reg_16(&D0);                // EXT.W	D0
  DEF_ROMLOC(14F2C) : add_toreg_16(D0, &D3);          // ADD.W	D0,D3
  DEF_ROMLOC(14F2E) : move_toreg_32(0xFFFFF76A, &A4); // LEA.L	$F76A,A4
  DEF_ROMLOC(14F32) : move_toreg_16(0x10, &A3);       // MOVEA.W	#$0010,A3
  DEF_ROMLOC(14F36) : move_toreg_16(0x0, &D6);        // MOVE.W	#$0000,D6
  DEF_ROMLOC(14F3A) : move_toreg_32(0xD, &D5);        // MOVEQ.L	$0D,D5
  DEF_ROMLOC(14F3C) : rom_15274();                    // BSR.W	$15274
  DEF_ROMLOC(14F40)
      : move_toreg_16(read_16((A7 += 2, A7 - 2)), &D0); // MOVE.W	(A7)+,D0
  DEF_ROMLOC(14F42) : rom_14EB8();                      // BSR.W	$14EB8
  DEF_ROMLOC(14F46) : tst_reg_16(&D1);                  // TST.W	D1
  DEF_ROMLOC(14F48) : if (CCR_EQ) goto rom_14F58;       // BEQ.B	$14F58
  DEF_ROMLOC(14F4A) : if (CCR_PL) goto rom_14F5A;       // BPL.B	$14F5A
  DEF_ROMLOC(14F4C) : cmp_toreg_16(0xFFFFFFF2, &D1);    // CMPI.W	#$FFF2,D1
  DEF_ROMLOC(14F50) : if (CCR_LT) return;               // BLT.W	$14E72
  DEF_ROMLOC(14F54) : add_tomem_16(D1, A0 + 0x8);       // ADD.W	D1,8(A0)
  DEF_ROMLOC(14F58) : return;                           // RTS
  DEF_ROMLOC(14F5A) : cmp_toreg_16(0xE, &D1);           // CMPI.W	#$000E,D1
  DEF_ROMLOC(14F5E) : if (CCR_GT) goto rom_14F66;       // BGT.B	$14F66
  DEF_ROMLOC(14F60) : add_tomem_16(D1, A0 + 0x8);       // ADD.W	D1,8(A0)
  DEF_ROMLOC(14F64) : return;                           // RTS
  DEF_ROMLOC(14F66) : tst_mem_8(A0 + 0x38);             // TST.B	56(A0)
  DEF_ROMLOC(14F6A) : if (!CCR_EQ) goto rom_14F60;      // BNE.B	$14F60
  DEF_ROMLOC(14F6C) : bset_tomem_8(0x1, A0 + 0x22);     // BSET.B	#$01,34(A0)
  DEF_ROMLOC(14F72) : bclr_tomem_8(0x5, A0 + 0x22);     // BCLR.B	#$05,34(A0)
  DEF_ROMLOC(14F78) : move_tomem_8(0x1, A0 + 0x1D);     // MOVE.B	#$01,29(A0)
  DEF_ROMLOC(14F7E) : return;                           // RTS
}
ROMFUNC(rom_14F80) {
  DEF_ROMLOC(14F80)
      : move_toreg_16(read_16(A0 + 0xC), &D2); // MOVE.W	12(A0),D2
  DEF_ROMLOC(14F84)
      : move_toreg_16(read_16(A0 + 0x8), &D3); // MOVE.W	8(A0),D3
  DEF_ROMLOC(14F88) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(14F8A)
      : move_toreg_8(read_8(A0 + 0x16), &D0); // MOVE.B
                                              // 22(A0),D0
  DEF_ROMLOC(14F8E) : ext_reg_16(&D0);        // EXT.W	D0
  DEF_ROMLOC(14F90) : sub_toreg_16(D0, &D2);  // SUB.W	D0,D2
  DEF_ROMLOC(14F92) : eor_toreg_16(0xF, &D2); // EORI.W	#$000F,D2
  DEF_ROMLOC(14F96)
      : move_toreg_8(read_8(A0 + 0x17), &D0);         // MOVE.B
                                                      // 23(A0),D0
  DEF_ROMLOC(14F9A) : ext_reg_16(&D0);                // EXT.W	D0
  DEF_ROMLOC(14F9C) : add_toreg_16(D0, &D3);          // ADD.W	D0,D3
  DEF_ROMLOC(14F9E) : move_toreg_32(0xFFFFF768, &A4); // LEA.L	$F768,A4
  DEF_ROMLOC(14FA2)
      : move_toreg_16(0xFFFFFFF0, &A3);           // MOVEA.W
                                                  // #$FFF0,A3
  DEF_ROMLOC(14FA6) : move_toreg_16(0x1000, &D6); // MOVE.W	#$1000,D6
  DEF_ROMLOC(14FAA) : move_toreg_32(0xD, &D5);    // MOVEQ.L	$0D,D5
  DEF_ROMLOC(14FAC) : rom_15136();                // BSR.W	$15136
  DEF_ROMLOC(14FB0) : move_tomem_16(D1, A7 -= 2); // MOVE.W	D1,-(A7)
  DEF_ROMLOC(14FB2)
      : move_toreg_16(read_16(A0 + 0xC), &D2); // MOVE.W	12(A0),D2
  DEF_ROMLOC(14FB6)
      : move_toreg_16(read_16(A0 + 0x8), &D3); // MOVE.W	8(A0),D3
  DEF_ROMLOC(14FBA) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(14FBC)
      : move_toreg_8(read_8(A0 + 0x16), &D0); // MOVE.B
                                              // 22(A0),D0
  DEF_ROMLOC(14FC0) : ext_reg_16(&D0);        // EXT.W	D0
  DEF_ROMLOC(14FC2) : sub_toreg_16(D0, &D2);  // SUB.W	D0,D2
  DEF_ROMLOC(14FC4) : eor_toreg_16(0xF, &D2); // EORI.W	#$000F,D2
  DEF_ROMLOC(14FC8)
      : move_toreg_8(read_8(A0 + 0x17), &D0);         // MOVE.B
                                                      // 23(A0),D0
  DEF_ROMLOC(14FCC) : ext_reg_16(&D0);                // EXT.W	D0
  DEF_ROMLOC(14FCE) : sub_toreg_16(D0, &D3);          // SUB.W	D0,D3
  DEF_ROMLOC(14FD0) : move_toreg_32(0xFFFFF76A, &A4); // LEA.L	$F76A,A4
  DEF_ROMLOC(14FD4)
      : move_toreg_16(0xFFFFFFF0, &A3);           // MOVEA.W
                                                  // #$FFF0,A3
  DEF_ROMLOC(14FD8) : move_toreg_16(0x1000, &D6); // MOVE.W	#$1000,D6
  DEF_ROMLOC(14FDC) : move_toreg_32(0xD, &D5);    // MOVEQ.L	$0D,D5
  DEF_ROMLOC(14FDE) : rom_15136();                // BSR.W	$15136
  DEF_ROMLOC(14FE2)
      : move_toreg_16(read_16((A7 += 2, A7 - 2)), &D0); // MOVE.W	(A7)+,D0
  DEF_ROMLOC(14FE4) : rom_14EB8();                      // BSR.W	$14EB8
  DEF_ROMLOC(14FE8) : tst_reg_16(&D1);                  // TST.W	D1
  DEF_ROMLOC(14FEA) : if (CCR_EQ) goto rom_14FFA;       // BEQ.B	$14FFA
  DEF_ROMLOC(14FEC) : if (CCR_PL) goto rom_14FFC;       // BPL.B	$14FFC
  DEF_ROMLOC(14FEE) : cmp_toreg_16(0xFFFFFFF2, &D1);    // CMPI.W	#$FFF2,D1
  DEF_ROMLOC(14FF2) : if (CCR_LT) return;               // BLT.W	$14E4E
  DEF_ROMLOC(14FF6) : sub_tomem_16(D1, A0 + 0xC);       // SUB.W	D1,12(A0)
  DEF_ROMLOC(14FFA) : return;                           // RTS
  DEF_ROMLOC(14FFC) : cmp_toreg_16(0xE, &D1);           // CMPI.W	#$000E,D1
  DEF_ROMLOC(15000) : if (CCR_GT) goto rom_15008;       // BGT.B	$15008
  DEF_ROMLOC(15002) : sub_tomem_16(D1, A0 + 0xC);       // SUB.W	D1,12(A0)
  DEF_ROMLOC(15006) : return;                           // RTS
  DEF_ROMLOC(15008) : tst_mem_8(A0 + 0x38);             // TST.B	56(A0)
  DEF_ROMLOC(1500C) : if (!CCR_EQ) goto rom_15002;      // BNE.B	$15002
  DEF_ROMLOC(1500E) : bset_tomem_8(0x1, A0 + 0x22);     // BSET.B	#$01,34(A0)
  DEF_ROMLOC(15014) : bclr_tomem_8(0x5, A0 + 0x22);     // BCLR.B	#$05,34(A0)
  DEF_ROMLOC(1501A) : move_tomem_8(0x1, A0 + 0x1D);     // MOVE.B	#$01,29(A0)
  DEF_ROMLOC(15020) : return;                           // RTS
}
ROMFUNC(rom_15022) {
  DEF_ROMLOC(15022)
      : move_toreg_16(read_16(A0 + 0xC), &D2); // MOVE.W	12(A0),D2
  DEF_ROMLOC(15026)
      : move_toreg_16(read_16(A0 + 0x8), &D3); // MOVE.W	8(A0),D3
  DEF_ROMLOC(1502A) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(1502C)
      : move_toreg_8(read_8(A0 + 0x17), &D0); // MOVE.B
                                              // 23(A0),D0
  DEF_ROMLOC(15030) : ext_reg_16(&D0);        // EXT.W	D0
  DEF_ROMLOC(15032) : sub_toreg_16(D0, &D2);  // SUB.W	D0,D2
  DEF_ROMLOC(15034)
      : move_toreg_8(read_8(A0 + 0x16), &D0);         // MOVE.B
                                                      // 22(A0),D0
  DEF_ROMLOC(15038) : ext_reg_16(&D0);                // EXT.W	D0
  DEF_ROMLOC(1503A) : sub_toreg_16(D0, &D3);          // SUB.W	D0,D3
  DEF_ROMLOC(1503C) : eor_toreg_16(0xF, &D3);         // EORI.W	#$000F,D3
  DEF_ROMLOC(15040) : move_toreg_32(0xFFFFF768, &A4); // LEA.L	$F768,A4
  DEF_ROMLOC(15044)
      : move_toreg_16(0xFFFFFFF0, &A3);           // MOVEA.W
                                                  // #$FFF0,A3
  DEF_ROMLOC(15048) : move_toreg_16(0x800, &D6);  // MOVE.W	#$0800,D6
  DEF_ROMLOC(1504C) : move_toreg_32(0xD, &D5);    // MOVEQ.L	$0D,D5
  DEF_ROMLOC(1504E) : rom_15274();                // BSR.W	$15274
  DEF_ROMLOC(15052) : move_tomem_16(D1, A7 -= 2); // MOVE.W	D1,-(A7)
  DEF_ROMLOC(15054)
      : move_toreg_16(read_16(A0 + 0xC), &D2); // MOVE.W	12(A0),D2
  DEF_ROMLOC(15058)
      : move_toreg_16(read_16(A0 + 0x8), &D3); // MOVE.W	8(A0),D3
  DEF_ROMLOC(1505C) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(1505E)
      : move_toreg_8(read_8(A0 + 0x17), &D0); // MOVE.B
                                              // 23(A0),D0
  DEF_ROMLOC(15062) : ext_reg_16(&D0);        // EXT.W	D0
  DEF_ROMLOC(15064) : add_toreg_16(D0, &D2);  // ADD.W	D0,D2
  DEF_ROMLOC(15066)
      : move_toreg_8(read_8(A0 + 0x16), &D0);         // MOVE.B
                                                      // 22(A0),D0
  DEF_ROMLOC(1506A) : ext_reg_16(&D0);                // EXT.W	D0
  DEF_ROMLOC(1506C) : sub_toreg_16(D0, &D3);          // SUB.W	D0,D3
  DEF_ROMLOC(1506E) : eor_toreg_16(0xF, &D3);         // EORI.W	#$000F,D3
  DEF_ROMLOC(15072) : move_toreg_32(0xFFFFF76A, &A4); // LEA.L	$F76A,A4
  DEF_ROMLOC(15076)
      : move_toreg_16(0xFFFFFFF0, &A3);          // MOVEA.W
                                                 // #$FFF0,A3
  DEF_ROMLOC(1507A) : move_toreg_16(0x800, &D6); // MOVE.W	#$0800,D6
  DEF_ROMLOC(1507E) : move_toreg_32(0xD, &D5);   // MOVEQ.L	$0D,D5
  DEF_ROMLOC(15080) : rom_15274();               // BSR.W	$15274
  DEF_ROMLOC(15084)
      : move_toreg_16(read_16((A7 += 2, A7 - 2)), &D0); // MOVE.W	(A7)+,D0
  DEF_ROMLOC(15086) : rom_14EB8();                      // BSR.W	$14EB8
  DEF_ROMLOC(1508A) : tst_reg_16(&D1);                  // TST.W	D1
  DEF_ROMLOC(1508C) : if (CCR_EQ) goto rom_1509C;       // BEQ.B	$1509C
  DEF_ROMLOC(1508E) : if (CCR_PL) goto rom_1509E;       // BPL.B	$1509E
  DEF_ROMLOC(15090) : cmp_toreg_16(0xFFFFFFF2, &D1);    // CMPI.W	#$FFF2,D1
  DEF_ROMLOC(15094) : if (CCR_LT) return;               // BLT.W	$14E72
  DEF_ROMLOC(15098) : sub_tomem_16(D1, A0 + 0x8);       // SUB.W	D1,8(A0)
  DEF_ROMLOC(1509C) : return;                           // RTS
  DEF_ROMLOC(1509E) : cmp_toreg_16(0xE, &D1);           // CMPI.W	#$000E,D1
  DEF_ROMLOC(150A2) : if (CCR_GT) goto rom_150AA;       // BGT.B	$150AA
  DEF_ROMLOC(150A4) : sub_tomem_16(D1, A0 + 0x8);       // SUB.W	D1,8(A0)
  DEF_ROMLOC(150A8) : return;                           // RTS
  DEF_ROMLOC(150AA) : tst_mem_8(A0 + 0x38);             // TST.B	56(A0)
  DEF_ROMLOC(150AE) : if (!CCR_EQ) goto rom_150A4;      // BNE.B	$150A4
  DEF_ROMLOC(150B0) : bset_tomem_8(0x1, A0 + 0x22);     // BSET.B	#$01,34(A0)
  DEF_ROMLOC(150B6) : bclr_tomem_8(0x5, A0 + 0x22);     // BCLR.B	#$05,34(A0)
  DEF_ROMLOC(150BC) : move_tomem_8(0x1, A0 + 0x1D);     // MOVE.B	#$01,29(A0)
  DEF_ROMLOC(150C2) : return;                           // RTS
}
ROMFUNC(rom_15670) {
  DEF_ROMLOC(15670)
      : move_toreg_16(read_16(A0 + 0xC), &D2); // MOVE.W	12(A0),D2
  DEF_ROMLOC(15674)
      : move_toreg_16(read_16(A0 + 0x8), &D3); // MOVE.W	8(A0),D3
  DEF_ROMLOC(15678) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(1567A)
      : move_toreg_8(read_8(A0 + 0x16), &D0); // MOVE.B
                                              // 22(A0),D0
  DEF_ROMLOC(1567E) : ext_reg_16(&D0);        // EXT.W	D0
  DEF_ROMLOC(15680) : sub_toreg_16(D0, &D2);  // SUB.W	D0,D2
  DEF_ROMLOC(15682) : eor_toreg_16(0xF, &D2); // EORI.W	#$000F,D2
  DEF_ROMLOC(15686)
      : move_toreg_8(read_8(A0 + 0x17), &D0);         // MOVE.B
                                                      // 23(A0),D0
  DEF_ROMLOC(1568A) : ext_reg_16(&D0);                // EXT.W	D0
  DEF_ROMLOC(1568C) : add_toreg_16(D0, &D3);          // ADD.W	D0,D3
  DEF_ROMLOC(1568E) : move_toreg_32(0xFFFFF768, &A4); // LEA.L	$F768,A4
  DEF_ROMLOC(15692)
      : move_toreg_16(0xFFFFFFF0, &A3);           // MOVEA.W
                                                  // #$FFF0,A3
  DEF_ROMLOC(15696) : move_toreg_16(0x1000, &D6); // MOVE.W	#$1000,D6
  DEF_ROMLOC(1569A) : move_toreg_32(0xE, &D5);    // MOVEQ.L	$0E,D5
  DEF_ROMLOC(1569C) : rom_15136();                // BSR.W	$15136
  DEF_ROMLOC(156A0) : move_tomem_16(D1, A7 -= 2); // MOVE.W	D1,-(A7)
  DEF_ROMLOC(156A2)
      : move_toreg_16(read_16(A0 + 0xC), &D2); // MOVE.W	12(A0),D2
  DEF_ROMLOC(156A6)
      : move_toreg_16(read_16(A0 + 0x8), &D3); // MOVE.W	8(A0),D3
  DEF_ROMLOC(156AA) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(156AC)
      : move_toreg_8(read_8(A0 + 0x16), &D0); // MOVE.B
                                              // 22(A0),D0
  DEF_ROMLOC(156B0) : ext_reg_16(&D0);        // EXT.W	D0
  DEF_ROMLOC(156B2) : sub_toreg_16(D0, &D2);  // SUB.W	D0,D2
  DEF_ROMLOC(156B4) : eor_toreg_16(0xF, &D2); // EORI.W	#$000F,D2
  DEF_ROMLOC(156B8)
      : move_toreg_8(read_8(A0 + 0x17), &D0);         // MOVE.B
                                                      // 23(A0),D0
  DEF_ROMLOC(156BC) : ext_reg_16(&D0);                // EXT.W	D0
  DEF_ROMLOC(156BE) : sub_toreg_16(D0, &D3);          // SUB.W	D0,D3
  DEF_ROMLOC(156C0) : move_toreg_32(0xFFFFF76A, &A4); // LEA.L	$F76A,A4
  DEF_ROMLOC(156C4)
      : move_toreg_16(0xFFFFFFF0, &A3);           // MOVEA.W
                                                  // #$FFF0,A3
  DEF_ROMLOC(156C8) : move_toreg_16(0x1000, &D6); // MOVE.W	#$1000,D6
  DEF_ROMLOC(156CC) : move_toreg_32(0xE, &D5);    // MOVEQ.L	$0E,D5
  DEF_ROMLOC(156CE) : rom_15136();                // BSR.W	$15136
  DEF_ROMLOC(156D2)
      : move_toreg_16(read_16((A7 += 2, A7 - 2)), &D0); // MOVE.W	(A7)+,D0
  DEF_ROMLOC(156D4) : move_toreg_8(0xFFFFFF80, &D2);    // MOVE.B	#$80,D2
  DEF_ROMLOC(156D8) : {
    rom_15538();
    return;
  } // BRA.W	$15538
  DEF_ROMLOC(156DC)
      : move_toreg_16(read_16(A0 + 0xC), &D2); // MOVE.W	12(A0),D2
  DEF_ROMLOC(156E0)
      : move_toreg_16(read_16(A0 + 0x8), &D3); // MOVE.W	8(A0),D3
  rom_156E4(); // Detected flow into next function
}
ROMFUNC(rom_156E4) {
  DEF_ROMLOC(156E4) : sub_toreg_16(0xA, &D2);         // SUBI.W	#$000A,D2
  DEF_ROMLOC(156E8) : eor_toreg_16(0xF, &D2);         // EORI.W	#$000F,D2
  DEF_ROMLOC(156EC) : move_toreg_32(0xFFFFF768, &A4); // LEA.L	$F768,A4
  DEF_ROMLOC(156F0)
      : move_toreg_16(0xFFFFFFF0, &A3);              // MOVEA.W
                                                     // #$FFF0,A3
  DEF_ROMLOC(156F4) : move_toreg_16(0x1000, &D6);    // MOVE.W	#$1000,D6
  DEF_ROMLOC(156F8) : move_toreg_32(0xE, &D5);       // MOVEQ.L	$0E,D5
  DEF_ROMLOC(156FA) : rom_15136();                   // BSR.W	$15136
  DEF_ROMLOC(156FE) : move_toreg_8(0xFFFFFF80, &D2); // MOVE.B	#$80,D2
  rom_15572();                                       // BRA.W	$15572
}
ROMFUNC(rom_157AA) {
  DEF_ROMLOC(157AA)
      : move_toreg_16(read_16(A0 + 0xC), &D2); // MOVE.W	12(A0),D2
  DEF_ROMLOC(157AE)
      : move_toreg_16(read_16(A0 + 0x8), &D3); // MOVE.W	8(A0),D3
  rom_157B2(); // Detected flow into next function
}
ROMFUNC(rom_157B2) {
  DEF_ROMLOC(157B2) : sub_toreg_16(0xA, &D3);         // SUBI.W	#$000A,D3
  DEF_ROMLOC(157B6) : eor_toreg_16(0xF, &D3);         // EORI.W	#$000F,D3
  DEF_ROMLOC(157BA) : move_toreg_32(0xFFFFF768, &A4); // LEA.L	$F768,A4
  DEF_ROMLOC(157BE)
      : move_toreg_16(0xFFFFFFF0, &A3);          // MOVEA.W
                                                 // #$FFF0,A3
  DEF_ROMLOC(157C2) : move_toreg_16(0x800, &D6); // MOVE.W	#$0800,D6
  DEF_ROMLOC(157C6) : move_toreg_32(0xE, &D5);   // MOVEQ.L	$0E,D5
  DEF_ROMLOC(157C8) : rom_15274();               // BSR.W	$15274
  DEF_ROMLOC(157CC) : move_toreg_8(0x40, &D2);   // MOVE.B	#$40,D2
  rom_15572();                                   // BRA.W	$15572
}
ROMFUNC(rom_132AC) {
  DEF_ROMLOC(132AC) : tst_mem_16(0xFFFFFE08); // TST.W	$FE08
  DEF_ROMLOC(132B0) : if (CCR_EQ) {
    rom_132B8();
    return;
  }                                // BEQ.B	$132B8
  DEF_ROMLOC(132B2) : rom_1D6E6(); // JMP	$0001D6E6
}
ROMFUNC(rom_132B8) {
  u8 switchindex = 0;
  DEF_ROMLOC(132B8) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(132BA) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(132BE)
      : move_toreg_16(read_16(0x132C6 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(132C2): goto rom_132C6 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(132C2) : switch (switchindex) {
  case 0:
    rom_132D0();
    break;
  case 1:
    rom_13312();
    break;
  case 2:
    rom_13EC6();
    break;
  case 3:
    rom_13F36();
    break;
  case 4:
    rom_13FD6();
    break;
  }
}
ROMFUNC(rom_132D0) {
  DEF_ROMLOC(132D0) : add_tomem_8(0x2, A0 + 0x24);   // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(132D4) : move_tomem_8(0x13, A0 + 0x16); // MOVE.B	#$13,22(A0)
  DEF_ROMLOC(132DA) : move_tomem_8(0x9, A0 + 0x17);  // MOVE.B	#$09,23(A0)
  DEF_ROMLOC(132E0)
      : move_tomem_32(0x21CF4, A0 + 0x4);             // MOVE.L	#$00021CF4,4(A0)
  DEF_ROMLOC(132E8) : move_tomem_16(0x780, A0 + 0x2); // MOVE.W	#$0780,2(A0)
  DEF_ROMLOC(132EE) : move_tomem_8(0x2, A0 + 0x18);   // MOVE.B	#$02,24(A0)
  DEF_ROMLOC(132F4) : move_tomem_8(0x18, A0 + 0x19);  // MOVE.B	#$18,25(A0)
  DEF_ROMLOC(132FA) : move_tomem_8(0x4, A0 + 0x1);    // MOVE.B	#$04,1(A0)
  DEF_ROMLOC(13300)
      : move_tomem_16(0x600, 0xFFFFF760); // MOVE.W
                                          // #$0600,$F760
  DEF_ROMLOC(13306)
      : move_tomem_16(0xC, 0xFFFFF762); // MOVE.W	#$000C,$F762
  DEF_ROMLOC(1330C)
      : move_tomem_16(0x80, 0xFFFFF764); // MOVE.W
                                         // #$0080,$F764
  rom_13312();                           // Detected flow into next function
}
ROMFUNC(rom_13312) {
  u8 switchindex = 0;
  DEF_ROMLOC(13312) : tst_mem_16(0xFFFFFFFA);         // TST.W	$FFFA
  DEF_ROMLOC(13316) : if (CCR_EQ) goto rom_1332C;     // BEQ.B	$1332C
  DEF_ROMLOC(13318) : btst_tomem_8(0x4, 0xFFFFF605);  // BTST.B	#$04,$F605
  DEF_ROMLOC(1331E) : if (CCR_EQ) goto rom_1332C;     // BEQ.B	$1332C
  DEF_ROMLOC(13320) : move_tomem_16(0x1, 0xFFFFFE08); // MOVE.W	#$0001,$FE08
  DEF_ROMLOC(13326) : clr_mem_8(0xFFFFF7CC);          // CLR.B	$F7CC
  DEF_ROMLOC(1332A) : return;                         // RTS
  DEF_ROMLOC(1332C) : tst_mem_8(0xFFFFF7CC);          // TST.B	$F7CC
  DEF_ROMLOC(13330) : if (!CCR_EQ) goto rom_13338;    // BNE.B	$13338
  DEF_ROMLOC(13332)
      : move_tomem_16(read_16(0xFFFFF604),
                      0xFFFFF602);                   // MOVE.W	$F604,$F602
  DEF_ROMLOC(13338) : btst_tomem_8(0x0, 0xFFFFF7C8); // BTST.B	#$00,$F7C8
  DEF_ROMLOC(1333E) : if (!CCR_EQ) goto rom_13352;   // BNE.B	$13352
  DEF_ROMLOC(13340) : move_toreg_32(0x0, &D0);       // MOVEQ.L	$00,D0
  DEF_ROMLOC(13342)
      : move_toreg_8(read_8(A0 + 0x22), &D0); // MOVE.B
                                              // 34(A0),D0
  DEF_ROMLOC(13346) : and_toreg_16(0x6, &D0);
  switchindex = D0 / 2; // ANDI.W	#$0006,D0
  DEF_ROMLOC(1334A)
      : move_toreg_16(read_16(0x13394 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	72(PC,D0),D1
  // DEF_ROMLOC(1334E): rom_13394 + (s16)(D1 & 0xffff)(); // JSR
  // 68(PC,D1)
  DEF_ROMLOC(1334E) : switch (switchindex) {
  case 0:
    rom_134EC();
    break;
  case 1:
    rom_13510();
    break;
  case 2:
    rom_1353A();
    break;
  case 3:
    rom_1355A();
    break;
  }
  DEF_ROMLOC(13352) : rom_133A2(); // BSR.B	$133A2
  DEF_ROMLOC(13354) : rom_13432(); // BSR.W	$13432
  DEF_ROMLOC(13358) : rom_1344C(); // BSR.W	$1344C
  DEF_ROMLOC(1335C)
      : move_tomem_8(read_8(0xFFFFF768), A0 + 0x36); // MOVE.B	$F768,54(A0)
  DEF_ROMLOC(13362)
      : move_tomem_8(read_8(0xFFFFF76A), A0 + 0x37); // MOVE.B	$F76A,55(A0)
  DEF_ROMLOC(13368) : tst_mem_8(0xFFFFF7C7);         // TST.B	$F7C7
  DEF_ROMLOC(1336C) : if (CCR_EQ) goto rom_1337A;    // BEQ.B	$1337A
  DEF_ROMLOC(1336E) : tst_mem_8(A0 + 0x1C);          // TST.B	28(A0)
  DEF_ROMLOC(13372) : if (!CCR_EQ) goto rom_1337A;   // BNE.B	$1337A
  DEF_ROMLOC(13374)
      : move_tomem_8(read_8(A0 + 0x1D), A0 + 0x1C); // MOVE.B	29(A0),28(A0)
  DEF_ROMLOC(1337A) : rom_14098();                  // BSR.W	$14098
  DEF_ROMLOC(1337E) : tst_mem_8(0xFFFFF7C8);        // TST.B	$F7C8
  DEF_ROMLOC(13382) : if (CCR_MI) goto rom_1338A;   // BMI.B	$1338A
  DEF_ROMLOC(13384) : rom_1B59A();                  // JSR	$0001B59A
  DEF_ROMLOC(1338A) : rom_13FEA();                  // BSR.W	$13FEA
  DEF_ROMLOC(1338E) : rom_14312();                  // BSR.W	$14312
  DEF_ROMLOC(13392) : return;                       // RTS
}
ROMFUNC(rom_133A2) {
  DEF_ROMLOC(133A2)
      : move_toreg_16(read_16(A0 + 0x30), &D0);     // MOVE.W	48(A0),D0
  DEF_ROMLOC(133A6) : if (CCR_EQ) goto rom_133B0;   // BEQ.B	$133B0
  DEF_ROMLOC(133A8) : sub_tomem_16(0x1, A0 + 0x30); // SUBQ.W	#$01,48(A0)
  DEF_ROMLOC(133AC) : lsr_toreg_16(0x3, &D0);       // LSR.W	#$03,D0
  DEF_ROMLOC(133AE) : if (CCR_CC) goto rom_133B6;   // BCC.B	$133B6
  DEF_ROMLOC(133B0) : rom_DC92();                   // JSR	$0000DC92
  DEF_ROMLOC(133B6) : tst_mem_8(0xFFFFFE2D);        // TST.B	$FE2D
  DEF_ROMLOC(133BA) : if (CCR_EQ) goto rom_133FC;   // BEQ.B	$133FC
  DEF_ROMLOC(133BC) : tst_mem_16(A0 + 0x32);        // TST.W	50(A0)
  DEF_ROMLOC(133C0) : if (CCR_EQ) goto rom_133FC;   // BEQ.B	$133FC
  DEF_ROMLOC(133C2) : sub_tomem_16(0x1, A0 + 0x32); // SUBQ.W	#$01,50(A0)
  DEF_ROMLOC(133C6) : if (!CCR_EQ) goto rom_133FC;  // BNE.B	$133FC
  DEF_ROMLOC(133C8) : tst_mem_8(f_lockscreen);      // TST.B	$F7AA
  DEF_ROMLOC(133CC) : if (!CCR_EQ) goto rom_133F6;  // BNE.B	$133F6
  DEF_ROMLOC(133CE)
      : cmp_tomem_16(AIR_COUNTDOWN_THRESHOLD, v_air);    // CMPI.W	#$000C,$FE14
  DEF_ROMLOC(133D4) : if (CCR_CS) goto rom_133F6;        // BCS.B	$133F6
  DEF_ROMLOC(133D6) : move_toreg_32(0x0, &D0);           // MOVEQ.L	$00,D0
  DEF_ROMLOC(133D8) : move_toreg_8(read_8(v_zone), &D0); // MOVE.B	$FE10,D0
  DEF_ROMLOC(133DC)
      : cmp_tomem_16(ZONE16_LZ | 3, v_zone);       // CMPI.W
                                                   // #$0103,$FE10
  DEF_ROMLOC(133E2) : if (!CCR_EQ) goto rom_133E6; // BNE.B	$133E6
  DEF_ROMLOC(133E4) : move_toreg_32(0x5, &D0);     // MOVEQ.L	$05,D0
  DEF_ROMLOC(133E6) : move_toreg_32(0x1339C, &A1); // LEA.L	$0001339C,A1
  DEF_ROMLOC(133EC)
      : move_toreg_8(read_8((s32)A1 + (s8)0x0 + (s16)D0),
                     &D0);                           // MOVE.B	0(A1,D0),D0
  DEF_ROMLOC(133F0) : play_sound();                  // JSR	$0000138E
  DEF_ROMLOC(133F6) : move_tomem_8(0x0, 0xFFFFFE2D); // MOVE.B	#$00,$FE2D
  DEF_ROMLOC(133FC) : tst_mem_8(0xFFFFFE2E);         // TST.B	$FE2E
  DEF_ROMLOC(13400) : if (CCR_EQ) goto rom_13430;    // BEQ.B	$13430
  DEF_ROMLOC(13402) : tst_mem_16(A0 + 0x34);         // TST.W	52(A0)
  DEF_ROMLOC(13406) : if (CCR_EQ) goto rom_13430;    // BEQ.B	$13430
  DEF_ROMLOC(13408) : sub_tomem_16(0x1, A0 + 0x34);  // SUBQ.W	#$01,52(A0)
  DEF_ROMLOC(1340C) : if (!CCR_EQ) goto rom_13430;   // BNE.B	$13430
  DEF_ROMLOC(1340E)
      : move_tomem_16(0x600, 0xFFFFF760); // MOVE.W
                                          // #$0600,$F760
  DEF_ROMLOC(13414)
      : move_tomem_16(0xC, 0xFFFFF762); // MOVE.W	#$000C,$F762
  DEF_ROMLOC(1341A)
      : move_tomem_16(0x80, 0xFFFFF764);             // MOVE.W
                                                     // #$0080,$F764
  DEF_ROMLOC(13420) : move_tomem_8(0x0, 0xFFFFFE2E); // MOVE.B	#$00,$FE2E
  DEF_ROMLOC(13426)
      : move_toreg_16(COMSFX_SLOWDOWN, &D0); // MOVE.W
                                             // #$00E3,D0
  DEF_ROMLOC(1342A) : {
    play_sound();
    return;
  }                           // JMP	$0000138E
  DEF_ROMLOC(13430) : return; // RTS
}
ROMFUNC(rom_13432) {
  DEF_ROMLOC(13432)
      : move_toreg_16(read_16(0xFFFFF7A8), &D0);      // MOVE.W	$F7A8,D0
  DEF_ROMLOC(13436) : move_toreg_32(0xFFFFCB00, &A1); // LEA.L	$CB00,A1
  DEF_ROMLOC(1343A)
      : move_toreg_32((s32)A1 + (s8)0x0 + (s16)D0,
                      &A1); // LEA.L	0(A1,D0),A1
  DEF_ROMLOC(1343E)
      : move_tomem_16(read_16(A0 + 0x8),
                      (A1 += 2, A1 - 2)); // MOVE.W	8(A0),(A1)+
  DEF_ROMLOC(13442)
      : move_tomem_16(read_16(A0 + 0xC),
                      (A1 += 2, A1 - 2));           // MOVE.W	12(A0),(A1)+
  DEF_ROMLOC(13446) : add_tomem_8(0x4, 0xFFFFF7A9); // ADDQ.B	#$04,$F7A9
  DEF_ROMLOC(1344A) : return;                       // RTS
}
ROMFUNC(rom_1344C) {
  DEF_ROMLOC(1344C) : cmp_tomem_8(ZONE_LZ, v_zone); // CMPI.B	#$01,$FE10
  DEF_ROMLOC(13452) : if (CCR_EQ) goto rom_13456;   // BEQ.B	$13456
  DEF_ROMLOC(13454) : return;                       // RTS
  DEF_ROMLOC(13456)
      : move_toreg_16(read_16(0xFFFFF646), &D0); // MOVE.W	$F646,D0
  DEF_ROMLOC(1345A)
      : cmp_toreg_16(read_16(A0 + 0xC), &D0);        // CMP.W
                                                     // 12(A0),D0
  DEF_ROMLOC(1345E) : if (CCR_GE) goto rom_134A8;    // BGE.B	$134A8
  DEF_ROMLOC(13460) : bset_tomem_8(0x6, A0 + 0x22);  // BSET.B	#$06,34(A0)
  DEF_ROMLOC(13466) : if (!CCR_EQ) goto rom_13454;   // BNE.B	$13454
  DEF_ROMLOC(13468) : resume_music();                // BSR.W	$147E2
  DEF_ROMLOC(1346C) : move_tomem_8(0xA, 0xFFFFD340); // MOVE.B	#$0A,$D340
  DEF_ROMLOC(13472)
      : move_tomem_8(0xFFFFFF81, 0xFFFFD368); // MOVE.B
                                              // #$81,$D368
  DEF_ROMLOC(13478)
      : move_tomem_16(0x300, 0xFFFFF760); // MOVE.W
                                          // #$0300,$F760
  DEF_ROMLOC(1347E)
      : move_tomem_16(0x6, 0xFFFFF762); // MOVE.W	#$0006,$F762
  DEF_ROMLOC(13484)
      : move_tomem_16(0x40, 0xFFFFF764);              // MOVE.W
                                                      // #$0040,$F764
  DEF_ROMLOC(1348A) : asr_mem_16(A0 + 0x10);          // ASR.W	16(A0)
  DEF_ROMLOC(1348E) : asr_mem_16(A0 + 0x12);          // ASR.W	18(A0)
  DEF_ROMLOC(13492) : asr_mem_16(A0 + 0x12);          // ASR.W	18(A0)
  DEF_ROMLOC(13496) : if (CCR_EQ) goto rom_13454;     // BEQ.B	$13454
  DEF_ROMLOC(13498) : move_tomem_8(0x8, 0xFFFFD300);  // MOVE.B	#$08,$D300
  DEF_ROMLOC(1349E) : move_toreg_16(SFX_SPLASH, &D0); // MOVE.W	#$00AA,D0
  DEF_ROMLOC(134A2) : {
    play_sound_special();
    return;
  }                                                 // JMP	$00001394
  DEF_ROMLOC(134A8) : bclr_tomem_8(0x6, A0 + 0x22); // BCLR.B	#$06,34(A0)
  DEF_ROMLOC(134AE) : if (CCR_EQ) goto rom_13454;   // BEQ.B	$13454
  DEF_ROMLOC(134B0) : resume_music();               // BSR.W	$147E2
  DEF_ROMLOC(134B4)
      : move_tomem_16(0x600, 0xFFFFF760); // MOVE.W
                                          // #$0600,$F760
  DEF_ROMLOC(134BA)
      : move_tomem_16(0xC, 0xFFFFF762); // MOVE.W	#$000C,$F762
  DEF_ROMLOC(134C0)
      : move_tomem_16(0x80, 0xFFFFF764);             // MOVE.W
                                                     // #$0080,$F764
  DEF_ROMLOC(134C6) : asl_mem_16(A0 + 0x12);         // ASL.W	18(A0)
  DEF_ROMLOC(134CA) : if (CCR_EQ) goto rom_13454;    // BEQ.W	$13454
  DEF_ROMLOC(134CE) : move_tomem_8(0x8, 0xFFFFD300); // MOVE.B	#$08,$D300
  DEF_ROMLOC(134D4)
      : cmp_tomem_16(0xFFFFF000, A0 + 0x12);      // CMPI.W	#$F000,18(A0)
  DEF_ROMLOC(134DA) : if (CCR_GT) goto rom_134E2; // BGT.B	$134E2
  DEF_ROMLOC(134DC)
      : move_tomem_16(0xFFFFF000, A0 + 0x12);         // MOVE.W	#$F000,18(A0)
  DEF_ROMLOC(134E2) : move_toreg_16(SFX_SPLASH, &D0); // MOVE.W	#$00AA,D0
  DEF_ROMLOC(134E6) : {
    play_sound_special();
    return;
  } // JMP	$00001394
}
ROMFUNC(rom_134EC) {
  DEF_ROMLOC(134EC) : rom_13ABE(); // BSR.W	$13ABE
  if (skiprestfromjump) {
    return;
  }
  DEF_ROMLOC(134F0) : rom_13BA8(); // BSR.W	$13BA8
  DEF_ROMLOC(134F4) : rom_13584(); // BSR.W	$13584
  DEF_ROMLOC(134F8) : rom_13A58(); // BSR.W	$13A58
  DEF_ROMLOC(134FC) : rom_139D8(); // BSR.W	$139D8
  DEF_ROMLOC(13500) : rom_DC6C();  // JSR	$0000DC6C
  DEF_ROMLOC(13506) : rom_14D56(); // BSR.W	$14D56
  DEF_ROMLOC(1350A) : rom_13C1A(); // BSR.W	$13C1A
  DEF_ROMLOC(1350E) : return;      // RTS
}
ROMFUNC(rom_13510) {
  DEF_ROMLOC(13510) : rom_13B6C();                   // BSR.W	$13B6C
  DEF_ROMLOC(13514) : rom_1391C();                   // BSR.W	$1391C
  DEF_ROMLOC(13518) : rom_139D8();                   // BSR.W	$139D8
  DEF_ROMLOC(1351C) : rom_DC40();                    // JSR	$0000DC40
  DEF_ROMLOC(13522) : btst_tomem_8(0x6, A0 + 0x22);  // BTST.B	#$06,34(A0)
  DEF_ROMLOC(13528) : if (CCR_EQ) goto rom_13530;    // BEQ.B	$13530
  DEF_ROMLOC(1352A) : sub_tomem_16(0x28, A0 + 0x12); // SUBI.W	#$0028,18(A0)
  DEF_ROMLOC(13530) : rom_13C5C();                   // BSR.W	$13C5C
  DEF_ROMLOC(13534) : rom_13C78();                   // BSR.W	$13C78
  DEF_ROMLOC(13538) : return;                        // RTS
}
ROMFUNC(rom_1353A) {
  DEF_ROMLOC(1353A) : rom_13ABE(); // BSR.W	$13ABE
  if (skiprestfromjump) {
    return;
  }
  DEF_ROMLOC(1353E) : rom_13BDE(); // BSR.W	$13BDE
  DEF_ROMLOC(13542) : rom_13824(); // BSR.W	$13824
  DEF_ROMLOC(13546) : rom_139D8(); // BSR.W	$139D8
  DEF_ROMLOC(1354A) : rom_DC6C();  // JSR	$0000DC6C
  DEF_ROMLOC(13550) : rom_14D56(); // BSR.W	$14D56
  DEF_ROMLOC(13554) : rom_13C1A(); // BSR.W	$13C1A
  DEF_ROMLOC(13558) : return;      // RTS
}
ROMFUNC(rom_1355A) {
  DEF_ROMLOC(1355A) : rom_13B6C();                   // BSR.W	$13B6C
  DEF_ROMLOC(1355E) : rom_1391C();                   // BSR.W	$1391C
  DEF_ROMLOC(13562) : rom_139D8();                   // BSR.W	$139D8
  DEF_ROMLOC(13566) : rom_DC40();                    // JSR	$0000DC40
  DEF_ROMLOC(1356C) : btst_tomem_8(0x6, A0 + 0x22);  // BTST.B	#$06,34(A0)
  DEF_ROMLOC(13572) : if (CCR_EQ) goto rom_1357A;    // BEQ.B	$1357A
  DEF_ROMLOC(13574) : sub_tomem_16(0x28, A0 + 0x12); // SUBI.W	#$0028,18(A0)
  DEF_ROMLOC(1357A) : rom_13C5C();                   // BSR.W	$13C5C
  DEF_ROMLOC(1357E) : rom_13C78();                   // BSR.W	$13C78
  DEF_ROMLOC(13582) : return;                        // RTS
}
ROMFUNC(rom_13584) {
  DEF_ROMLOC(13584)
      : move_toreg_16(read_16(0xFFFFF760), &D6); // MOVE.W	$F760,D6
  DEF_ROMLOC(13588)
      : move_toreg_16(read_16(0xFFFFF762), &D5); // MOVE.W	$F762,D5
  DEF_ROMLOC(1358C)
      : move_toreg_16(read_16(0xFFFFF764), &D4);     // MOVE.W	$F764,D4
  DEF_ROMLOC(13590) : tst_mem_8(0xFFFFF7CA);         // TST.B	$F7CA
  DEF_ROMLOC(13594) : if (!CCR_EQ) goto rom_136C2;   // BNE.W	$136C2
  DEF_ROMLOC(13598) : tst_mem_16(A0 + 0x3E);         // TST.W	62(A0)
  DEF_ROMLOC(1359C) : if (!CCR_EQ) goto rom_13684;   // BNE.W	$13684
  DEF_ROMLOC(135A0) : btst_tomem_8(0x2, 0xFFFFF602); // BTST.B	#$02,$F602
  DEF_ROMLOC(135A6) : if (CCR_EQ) goto rom_135AC;    // BEQ.B	$135AC
  DEF_ROMLOC(135A8) : rom_13752();                   // BSR.W	$13752
  DEF_ROMLOC(135AC) : btst_tomem_8(0x3, 0xFFFFF602); // BTST.B	#$03,$F602
  DEF_ROMLOC(135B2) : if (CCR_EQ) goto rom_135B8;    // BEQ.B	$135B8
  DEF_ROMLOC(135B4) : rom_137BE();                   // BSR.W	$137BE
  DEF_ROMLOC(135B8)
      : move_toreg_8(read_8(A0 + 0x26), &D0);       // MOVE.B	38(A0),D0
  DEF_ROMLOC(135BC) : add_toreg_8(0x20, &D0);       // ADDI.B	#$20,D0
  DEF_ROMLOC(135C0) : and_toreg_8(0xFFFFFFC0, &D0); // ANDI.B	#$C0,D0
  DEF_ROMLOC(135C4) : if (!CCR_EQ) goto rom_13684;  // BNE.W	$13684
  DEF_ROMLOC(135C8) : tst_mem_16(A0 + 0x14);        // TST.W	20(A0)
  DEF_ROMLOC(135CC) : if (!CCR_EQ) goto rom_13684;  // BNE.W	$13684
  DEF_ROMLOC(135D0) : bclr_tomem_8(0x5, A0 + 0x22); // BCLR.B	#$05,34(A0)
  DEF_ROMLOC(135D6) : move_tomem_8(0x5, A0 + 0x1C); // MOVE.B	#$05,28(A0)
  DEF_ROMLOC(135DC) : btst_tomem_8(0x3, A0 + 0x22); // BTST.B	#$03,34(A0)
  DEF_ROMLOC(135E2) : if (CCR_EQ) goto rom_1361A;   // BEQ.B	$1361A
  DEF_ROMLOC(135E4) : move_toreg_32(0x0, &D0);      // MOVEQ.L	$00,D0
  DEF_ROMLOC(135E6)
      : move_toreg_8(read_8(A0 + 0x3D), &D0);         // MOVE.B
                                                      // 61(A0),D0
  DEF_ROMLOC(135EA) : lsl_toreg_16(0x6, &D0);         // LSL.W	#$06,D0
  DEF_ROMLOC(135EC) : move_toreg_32(0xFFFFD000, &A1); // LEA.L	$D000,A1
  DEF_ROMLOC(135F0)
      : move_toreg_32((s32)A1 + (s8)0x0 + (s16)D0,
                      &A1);                       // LEA.L	0(A1,D0),A1
  DEF_ROMLOC(135F4) : tst_mem_8(A1 + 0x22);       // TST.B	34(A1)
  DEF_ROMLOC(135F8) : if (CCR_MI) goto rom_1364C; // BMI.B	$1364C
  DEF_ROMLOC(135FA) : move_toreg_32(0x0, &D1);    // MOVEQ.L	$00,D1
  DEF_ROMLOC(135FC)
      : move_toreg_8(read_8(A1 + 0x19), &D1);               // MOVE.B
                                                            // 25(A1),D1
  DEF_ROMLOC(13600) : move_toreg_16(D1, &D2);               // MOVE.W	D1,D2
  DEF_ROMLOC(13602) : add_toreg_16(D2, &D2);                // ADD.W	D2,D2
  DEF_ROMLOC(13604) : sub_toreg_16(0x4, &D2);               // SUBQ.W	#$04,D2
  DEF_ROMLOC(13606) : add_toreg_16(read_16(A0 + 0x8), &D1); // ADD.W	8(A0),D1
  DEF_ROMLOC(1360A) : sub_toreg_16(read_16(A1 + 0x8), &D1); // SUB.W	8(A1),D1
  DEF_ROMLOC(1360E) : cmp_toreg_16(0x4, &D1);               // CMPI.W	#$0004,D1
  DEF_ROMLOC(13612) : if (CCR_LT) goto rom_1363E;           // BLT.B	$1363E
  DEF_ROMLOC(13614) : cmp_toreg_16(D2, &D1);                // CMP.W	D2,D1
  DEF_ROMLOC(13616) : if (CCR_GE) goto rom_1362E;           // BGE.B	$1362E
  goto rom_1364C;                                           // BRA.B	$1364C
  DEF_ROMLOC(1361A) : rom_15580();                          // JSR	$00015580
  DEF_ROMLOC(13620) : cmp_toreg_16(0xC, &D1);               // CMPI.W	#$000C,D1
  DEF_ROMLOC(13624) : if (CCR_LT) goto rom_1364C;           // BLT.B	$1364C
  DEF_ROMLOC(13626) : cmp_tomem_8(0x3, A0 + 0x36);    // CMPI.B	#$03,54(A0)
  DEF_ROMLOC(1362C) : if (!CCR_EQ) goto rom_13636;    // BNE.B	$13636
  DEF_ROMLOC(1362E) : bclr_tomem_8(0x0, A0 + 0x22);   // BCLR.B	#$00,34(A0)
  goto rom_13644;                                     // BRA.B	$13644
  DEF_ROMLOC(13636) : cmp_tomem_8(0x3, A0 + 0x37);    // CMPI.B	#$03,55(A0)
  DEF_ROMLOC(1363C) : if (!CCR_EQ) goto rom_1364C;    // BNE.B	$1364C
  DEF_ROMLOC(1363E) : bset_tomem_8(0x0, A0 + 0x22);   // BSET.B	#$00,34(A0)
  DEF_ROMLOC(13644) : move_tomem_8(0x6, A0 + 0x1C);   // MOVE.B	#$06,28(A0)
  goto rom_13684;                                     // BRA.B	$13684
  DEF_ROMLOC(1364C) : btst_tomem_8(0x0, 0xFFFFF602);  // BTST.B	#$00,$F602
  DEF_ROMLOC(13652) : if (CCR_EQ) goto rom_13668;     // BEQ.B	$13668
  DEF_ROMLOC(13654) : move_tomem_8(0x7, A0 + 0x1C);   // MOVE.B	#$07,28(A0)
  DEF_ROMLOC(1365A) : cmp_tomem_16(0xC8, 0xFFFFF73E); // CMPI.W	#$00C8,$F73E
  DEF_ROMLOC(13660) : if (CCR_EQ) goto rom_13696;     // BEQ.B	$13696
  DEF_ROMLOC(13662) : add_tomem_16(0x2, 0xFFFFF73E);  // ADDQ.W	#$02,$F73E
  goto rom_13696;                                     // BRA.B	$13696
  DEF_ROMLOC(13668) : btst_tomem_8(0x1, 0xFFFFF602);  // BTST.B	#$01,$F602
  DEF_ROMLOC(1366E) : if (CCR_EQ) goto rom_13684;     // BEQ.B	$13684
  DEF_ROMLOC(13670) : move_tomem_8(0x8, A0 + 0x1C);   // MOVE.B	#$08,28(A0)
  DEF_ROMLOC(13676) : cmp_tomem_16(0x8, 0xFFFFF73E);  // CMPI.W	#$0008,$F73E
  DEF_ROMLOC(1367C) : if (CCR_EQ) goto rom_13696;     // BEQ.B	$13696
  DEF_ROMLOC(1367E) : sub_tomem_16(0x2, 0xFFFFF73E);  // SUBQ.W	#$02,$F73E
  goto rom_13696;                                     // BRA.B	$13696
  DEF_ROMLOC(13684) : cmp_tomem_16(0x60, 0xFFFFF73E); // CMPI.W	#$0060,$F73E
  DEF_ROMLOC(1368A) : if (CCR_EQ) goto rom_13696;     // BEQ.B	$13696
  DEF_ROMLOC(1368C) : if (CCR_CC) goto rom_13692;     // BCC.B	$13692
  DEF_ROMLOC(1368E) : add_tomem_16(0x4, 0xFFFFF73E);  // ADDQ.W	#$04,$F73E
  DEF_ROMLOC(13692) : sub_tomem_16(0x2, 0xFFFFF73E);  // SUBQ.W	#$02,$F73E
  DEF_ROMLOC(13696)
      : move_toreg_8(read_8(0xFFFFF602), &D0);     // MOVE.B	$F602,D0
  DEF_ROMLOC(1369A) : and_toreg_8(0xC, &D0);       // ANDI.B	#$0C,D0
  DEF_ROMLOC(1369E) : if (!CCR_EQ) goto rom_136C2; // BNE.B	$136C2
  DEF_ROMLOC(136A0)
      : move_toreg_16(read_16(A0 + 0x14), &D0);     // MOVE.W	20(A0),D0
  DEF_ROMLOC(136A4) : if (CCR_EQ) goto rom_136C2;   // BEQ.B	$136C2
  DEF_ROMLOC(136A6) : if (CCR_MI) goto rom_136B6;   // BMI.B	$136B6
  DEF_ROMLOC(136A8) : sub_toreg_16(D5, &D0);        // SUB.W	D5,D0
  DEF_ROMLOC(136AA) : if (CCR_CC) goto rom_136B0;   // BCC.B	$136B0
  DEF_ROMLOC(136AC) : move_toreg_16(0x0, &D0);      // MOVE.W	#$0000,D0
  DEF_ROMLOC(136B0) : move_tomem_16(D0, A0 + 0x14); // MOVE.W	D0,20(A0)
  goto rom_136C2;                                   // BRA.B	$136C2
  DEF_ROMLOC(136B6) : add_toreg_16(D5, &D0);        // ADD.W	D5,D0
  DEF_ROMLOC(136B8) : if (CCR_CC) goto rom_136BE;   // BCC.B	$136BE
  DEF_ROMLOC(136BA) : move_toreg_16(0x0, &D0);      // MOVE.W	#$0000,D0
  DEF_ROMLOC(136BE) : move_tomem_16(D0, A0 + 0x14); // MOVE.W	D0,20(A0)
  DEF_ROMLOC(136C2)
      : move_toreg_8(read_8(A0 + 0x26), &D0); // MOVE.B
                                              // 38(A0),D0
  DEF_ROMLOC(136C6) : rom_29D2();             // JSR	$000029D2
  DEF_ROMLOC(136CC)
      : muls_toreg_16(read_16(A0 + 0x14), &D1);     // MULS.W	20(A0),D1
  DEF_ROMLOC(136D0) : asr_toreg_32(0x8, &D1);       // ASR.L	#$08,D1
  DEF_ROMLOC(136D2) : move_tomem_16(D1, A0 + 0x10); // MOVE.W	D1,16(A0)
  DEF_ROMLOC(136D6)
      : muls_toreg_16(read_16(A0 + 0x14), &D0);     // MULS.W	20(A0),D0
  DEF_ROMLOC(136DA) : asr_toreg_32(0x8, &D0);       // ASR.L	#$08,D0
  DEF_ROMLOC(136DC) : move_tomem_16(D0, A0 + 0x12); // MOVE.W	D0,18(A0)
  rom_136E0(); // Detected flow into next function
}
ROMFUNC(rom_136E0) {
  DEF_ROMLOC(136E0)
      : move_toreg_8(read_8(A0 + 0x26), &D0);     // MOVE.B	38(A0),D0
  DEF_ROMLOC(136E4) : add_toreg_8(0x40, &D0);     // ADDI.B	#$40,D0
  DEF_ROMLOC(136E8) : if (CCR_MI) goto rom_13750; // BMI.B	$13750
  DEF_ROMLOC(136EA) : move_toreg_8(0x40, &D1);    // MOVE.B	#$40,D1
  DEF_ROMLOC(136EE) : tst_mem_16(A0 + 0x14);      // TST.W	20(A0)
  DEF_ROMLOC(136F2) : if (CCR_EQ) goto rom_13750; // BEQ.B	$13750
  DEF_ROMLOC(136F4) : if (CCR_MI) goto rom_136F8; // BMI.B	$136F8
  DEF_ROMLOC(136F6) : neg_reg_16(&D1);            // NEG.W	D1
  DEF_ROMLOC(136F8)
      : move_toreg_8(read_8(A0 + 0x26), &D0);     // MOVE.B	38(A0),D0
  DEF_ROMLOC(136FC) : add_toreg_8(D1, &D0);       // ADD.B	D1,D0
  DEF_ROMLOC(136FE) : move_tomem_16(D0, A7 -= 2); // MOVE.W	D0,-(A7)
  DEF_ROMLOC(13700) : rom_15446();                // BSR.W	$15446
  DEF_ROMLOC(13704)
      : move_toreg_16(read_16((A7 += 2, A7 - 2)), &D0); // MOVE.W	(A7)+,D0
  DEF_ROMLOC(13706) : tst_reg_16(&D1);                  // TST.W	D1
  DEF_ROMLOC(13708) : if (CCR_PL) goto rom_13750;       // BPL.B	$13750
  DEF_ROMLOC(1370A) : asl_toreg_16(0x8, &D1);           // ASL.W	#$08,D1
  DEF_ROMLOC(1370C) : add_toreg_8(0x20, &D0);           // ADDI.B	#$20,D0
  DEF_ROMLOC(13710) : and_toreg_8(0xFFFFFFC0, &D0);     // ANDI.B	#$C0,D0
  DEF_ROMLOC(13714) : if (CCR_EQ) goto rom_1374C;       // BEQ.B	$1374C
  DEF_ROMLOC(13716) : cmp_toreg_8(0x40, &D0);           // CMPI.B	#$40,D0
  DEF_ROMLOC(1371A) : if (CCR_EQ) goto rom_1373A;       // BEQ.B	$1373A
  DEF_ROMLOC(1371C) : cmp_toreg_8(0xFFFFFF80, &D0);     // CMPI.B	#$80,D0
  DEF_ROMLOC(13720) : if (CCR_EQ) goto rom_13734;       // BEQ.B	$13734
  DEF_ROMLOC(13722) : add_tomem_16(D1, A0 + 0x10);      // ADD.W	D1,16(A0)
  DEF_ROMLOC(13726) : bset_tomem_8(0x5, A0 + 0x22);     // BSET.B	#$05,34(A0)
  DEF_ROMLOC(1372C)
      : move_tomem_16(0x0, A0 + 0x14);              // MOVE.W	#$0000,20(A0)
  DEF_ROMLOC(13732) : return;                       // RTS
  DEF_ROMLOC(13734) : sub_tomem_16(D1, A0 + 0x12);  // SUB.W	D1,18(A0)
  DEF_ROMLOC(13738) : return;                       // RTS
  DEF_ROMLOC(1373A) : sub_tomem_16(D1, A0 + 0x10);  // SUB.W	D1,16(A0)
  DEF_ROMLOC(1373E) : bset_tomem_8(0x5, A0 + 0x22); // BSET.B	#$05,34(A0)
  DEF_ROMLOC(13744)
      : move_tomem_16(0x0, A0 + 0x14);             // MOVE.W	#$0000,20(A0)
  DEF_ROMLOC(1374A) : return;                      // RTS
  DEF_ROMLOC(1374C) : add_tomem_16(D1, A0 + 0x12); // ADD.W	D1,18(A0)
  DEF_ROMLOC(13750) : return;                      // RTS
}
ROMFUNC(rom_13752) {
  DEF_ROMLOC(13752)
      : move_toreg_16(read_16(A0 + 0x14), &D0);       // MOVE.W	20(A0),D0
  DEF_ROMLOC(13756) : if (CCR_EQ) goto rom_1375A;     // BEQ.B	$1375A
  DEF_ROMLOC(13758) : if (CCR_PL) goto rom_13786;     // BPL.B	$13786
  DEF_ROMLOC(1375A) : bset_tomem_8(0x0, A0 + 0x22);   // BSET.B	#$00,34(A0)
  DEF_ROMLOC(13760) : if (!CCR_EQ) goto rom_1376E;    // BNE.B	$1376E
  DEF_ROMLOC(13762) : bclr_tomem_8(0x5, A0 + 0x22);   // BCLR.B	#$05,34(A0)
  DEF_ROMLOC(13768) : move_tomem_8(0x1, A0 + 0x1D);   // MOVE.B	#$01,29(A0)
  DEF_ROMLOC(1376E) : sub_toreg_16(D5, &D0);          // SUB.W	D5,D0
  DEF_ROMLOC(13770) : move_toreg_16(D6, &D1);         // MOVE.W	D6,D1
  DEF_ROMLOC(13772) : neg_reg_16(&D1);                // NEG.W	D1
  DEF_ROMLOC(13774) : cmp_toreg_16(D1, &D0);          // CMP.W	D1,D0
  DEF_ROMLOC(13776) : if (CCR_GT) goto rom_1377A;     // BGT.B	$1377A
  DEF_ROMLOC(13778) : move_toreg_16(D1, &D0);         // MOVE.W	D1,D0
  DEF_ROMLOC(1377A) : move_tomem_16(D0, A0 + 0x14);   // MOVE.W	D0,20(A0)
  DEF_ROMLOC(1377E) : move_tomem_8(0x0, A0 + 0x1C);   // MOVE.B	#$00,28(A0)
  DEF_ROMLOC(13784) : return;                         // RTS
  DEF_ROMLOC(13786) : sub_toreg_16(D4, &D0);          // SUB.W	D4,D0
  DEF_ROMLOC(13788) : if (CCR_CC) goto rom_1378E;     // BCC.B	$1378E
  DEF_ROMLOC(1378A) : move_toreg_16(0xFFFFFF80, &D0); // MOVE.W	#$FF80,D0
  DEF_ROMLOC(1378E) : move_tomem_16(D0, A0 + 0x14);   // MOVE.W	D0,20(A0)
  DEF_ROMLOC(13792)
      : move_toreg_8(read_8(A0 + 0x26), &D0);       // MOVE.B	38(A0),D0
  DEF_ROMLOC(13796) : add_toreg_8(0x20, &D0);       // ADDI.B	#$20,D0
  DEF_ROMLOC(1379A) : and_toreg_8(0xFFFFFFC0, &D0); // ANDI.B	#$C0,D0
  DEF_ROMLOC(1379E) : if (!CCR_EQ) goto rom_137BC;  // BNE.B	$137BC
  DEF_ROMLOC(137A0) : cmp_toreg_16(0x400, &D0);     // CMPI.W	#$0400,D0
  DEF_ROMLOC(137A4) : if (CCR_LT) goto rom_137BC;   // BLT.B	$137BC
  DEF_ROMLOC(137A6) : move_tomem_8(0xD, A0 + 0x1C); // MOVE.B	#$0D,28(A0)
  DEF_ROMLOC(137AC) : bclr_tomem_8(0x0, A0 + 0x22); // BCLR.B	#$00,34(A0)
  DEF_ROMLOC(137B2) : move_toreg_16(SFX_SKID, &D0); // MOVE.W	#$00A4,D0
  DEF_ROMLOC(137B6) : play_sound_special();         // JSR	$00001394
  DEF_ROMLOC(137BC) : return;                       // RTS
}
ROMFUNC(rom_137BE) {
  DEF_ROMLOC(137BE)
      : move_toreg_16(read_16(A0 + 0x14), &D0);     // MOVE.W	20(A0),D0
  DEF_ROMLOC(137C2) : if (CCR_MI) goto rom_137EC;   // BMI.B	$137EC
  DEF_ROMLOC(137C4) : bclr_tomem_8(0x0, A0 + 0x22); // BCLR.B	#$00,34(A0)
  DEF_ROMLOC(137CA) : if (CCR_EQ) goto rom_137D8;   // BEQ.B	$137D8
  DEF_ROMLOC(137CC) : bclr_tomem_8(0x5, A0 + 0x22); // BCLR.B	#$05,34(A0)
  DEF_ROMLOC(137D2) : move_tomem_8(0x1, A0 + 0x1D); // MOVE.B	#$01,29(A0)
  DEF_ROMLOC(137D8) : add_toreg_16(D5, &D0);        // ADD.W	D5,D0
  DEF_ROMLOC(137DA) : cmp_toreg_16(D6, &D0);        // CMP.W	D6,D0
  DEF_ROMLOC(137DC) : if (CCR_LT) goto rom_137E0;   // BLT.B	$137E0
  DEF_ROMLOC(137DE) : move_toreg_16(D6, &D0);       // MOVE.W	D6,D0
  DEF_ROMLOC(137E0) : move_tomem_16(D0, A0 + 0x14); // MOVE.W	D0,20(A0)
  DEF_ROMLOC(137E4) : move_tomem_8(0x0, A0 + 0x1C); // MOVE.B	#$00,28(A0)
  DEF_ROMLOC(137EA) : return;                       // RTS
  DEF_ROMLOC(137EC) : add_toreg_16(D4, &D0);        // ADD.W	D4,D0
  DEF_ROMLOC(137EE) : if (CCR_CC) goto rom_137F4;   // BCC.B	$137F4
  DEF_ROMLOC(137F0) : move_toreg_16(0x80, &D0);     // MOVE.W	#$0080,D0
  DEF_ROMLOC(137F4) : move_tomem_16(D0, A0 + 0x14); // MOVE.W	D0,20(A0)
  DEF_ROMLOC(137F8)
      : move_toreg_8(read_8(A0 + 0x26), &D0);        // MOVE.B
                                                     // 38(A0),D0
  DEF_ROMLOC(137FC) : add_toreg_8(0x20, &D0);        // ADDI.B	#$20,D0
  DEF_ROMLOC(13800) : and_toreg_8(0xFFFFFFC0, &D0);  // ANDI.B	#$C0,D0
  DEF_ROMLOC(13804) : if (!CCR_EQ) goto rom_13822;   // BNE.B	$13822
  DEF_ROMLOC(13806) : cmp_toreg_16(0xFFFFFC00, &D0); // CMPI.W	#$FC00,D0
  DEF_ROMLOC(1380A) : if (CCR_GT) goto rom_13822;    // BGT.B	$13822
  DEF_ROMLOC(1380C) : move_tomem_8(0xD, A0 + 0x1C);  // MOVE.B	#$0D,28(A0)
  DEF_ROMLOC(13812) : bset_tomem_8(0x0, A0 + 0x22);  // BSET.B	#$00,34(A0)
  DEF_ROMLOC(13818) : move_toreg_16(SFX_SKID, &D0);  // MOVE.W	#$00A4,D0
  DEF_ROMLOC(1381C) : play_sound_special();          // JSR	$00001394
  DEF_ROMLOC(13822) : return;                        // RTS
}
ROMFUNC(rom_13824) {
  DEF_ROMLOC(13824)
      : move_toreg_16(read_16(0xFFFFF760), &D6); // MOVE.W	$F760,D6
  DEF_ROMLOC(13828) : asl_toreg_16(0x1, &D6);    // ASL.W	#$01,D6
  DEF_ROMLOC(1382A)
      : move_toreg_16(read_16(0xFFFFF762), &D5); // MOVE.W	$F762,D5
  DEF_ROMLOC(1382E) : asr_toreg_16(0x1, &D5);    // ASR.W	#$01,D5
  DEF_ROMLOC(13830)
      : move_toreg_16(read_16(0xFFFFF764), &D4);     // MOVE.W	$F764,D4
  DEF_ROMLOC(13834) : asr_toreg_16(0x2, &D4);        // ASR.W	#$02,D4
  DEF_ROMLOC(13836) : tst_mem_8(0xFFFFF7CA);         // TST.B	$F7CA
  DEF_ROMLOC(1383A) : if (!CCR_EQ) goto rom_138A0;   // BNE.W	$138A0
  DEF_ROMLOC(1383E) : tst_mem_16(A0 + 0x3E);         // TST.W	62(A0)
  DEF_ROMLOC(13842) : if (!CCR_EQ) goto rom_1385C;   // BNE.B	$1385C
  DEF_ROMLOC(13844) : btst_tomem_8(0x2, 0xFFFFF602); // BTST.B	#$02,$F602
  DEF_ROMLOC(1384A) : if (CCR_EQ) goto rom_13850;    // BEQ.B	$13850
  DEF_ROMLOC(1384C) : rom_138D6();                   // BSR.W	$138D6
  DEF_ROMLOC(13850) : btst_tomem_8(0x3, 0xFFFFF602); // BTST.B	#$03,$F602
  DEF_ROMLOC(13856) : if (CCR_EQ) goto rom_1385C;    // BEQ.B	$1385C
  DEF_ROMLOC(13858) : rom_138FA();                   // BSR.W	$138FA
  DEF_ROMLOC(1385C)
      : move_toreg_16(read_16(A0 + 0x14), &D0);      // MOVE.W	20(A0),D0
  DEF_ROMLOC(13860) : if (CCR_EQ) goto rom_1387E;    // BEQ.B	$1387E
  DEF_ROMLOC(13862) : if (CCR_MI) goto rom_13872;    // BMI.B	$13872
  DEF_ROMLOC(13864) : sub_toreg_16(D5, &D0);         // SUB.W	D5,D0
  DEF_ROMLOC(13866) : if (CCR_CC) goto rom_1386C;    // BCC.B	$1386C
  DEF_ROMLOC(13868) : move_toreg_16(0x0, &D0);       // MOVE.W	#$0000,D0
  DEF_ROMLOC(1386C) : move_tomem_16(D0, A0 + 0x14);  // MOVE.W	D0,20(A0)
  goto rom_1387E;                                    // BRA.B	$1387E
  DEF_ROMLOC(13872) : add_toreg_16(D5, &D0);         // ADD.W	D5,D0
  DEF_ROMLOC(13874) : if (CCR_CC) goto rom_1387A;    // BCC.B	$1387A
  DEF_ROMLOC(13876) : move_toreg_16(0x0, &D0);       // MOVE.W	#$0000,D0
  DEF_ROMLOC(1387A) : move_tomem_16(D0, A0 + 0x14);  // MOVE.W	D0,20(A0)
  DEF_ROMLOC(1387E) : tst_mem_16(A0 + 0x14);         // TST.W	20(A0)
  DEF_ROMLOC(13882) : if (!CCR_EQ) goto rom_138A0;   // BNE.B	$138A0
  DEF_ROMLOC(13884) : bclr_tomem_8(0x2, A0 + 0x22);  // BCLR.B	#$02,34(A0)
  DEF_ROMLOC(1388A) : move_tomem_8(0x13, A0 + 0x16); // MOVE.B	#$13,22(A0)
  DEF_ROMLOC(13890) : move_tomem_8(0x9, A0 + 0x17);  // MOVE.B	#$09,23(A0)
  DEF_ROMLOC(13896) : move_tomem_8(0x5, A0 + 0x1C);  // MOVE.B	#$05,28(A0)
  DEF_ROMLOC(1389C) : sub_tomem_16(0x5, A0 + 0xC);   // SUBQ.W	#$05,12(A0)
  DEF_ROMLOC(138A0)
      : move_toreg_8(read_8(A0 + 0x26), &D0); // MOVE.B
                                              // 38(A0),D0
  DEF_ROMLOC(138A4) : rom_29D2();             // JSR	$000029D2
  DEF_ROMLOC(138AA)
      : muls_toreg_16(read_16(A0 + 0x14), &D0);     // MULS.W	20(A0),D0
  DEF_ROMLOC(138AE) : asr_toreg_32(0x8, &D0);       // ASR.L	#$08,D0
  DEF_ROMLOC(138B0) : move_tomem_16(D0, A0 + 0x12); // MOVE.W	D0,18(A0)
  DEF_ROMLOC(138B4)
      : muls_toreg_16(read_16(A0 + 0x14), &D1);       // MULS.W	20(A0),D1
  DEF_ROMLOC(138B8) : asr_toreg_32(0x8, &D1);         // ASR.L	#$08,D1
  DEF_ROMLOC(138BA) : cmp_toreg_16(0x1000, &D1);      // CMPI.W	#$1000,D1
  DEF_ROMLOC(138BE) : if (CCR_LE) goto rom_138C4;     // BLE.B	$138C4
  DEF_ROMLOC(138C0) : move_toreg_16(0x1000, &D1);     // MOVE.W	#$1000,D1
  DEF_ROMLOC(138C4) : cmp_toreg_16(0xFFFFF000, &D1);  // CMPI.W	#$F000,D1
  DEF_ROMLOC(138C8) : if (CCR_GE) goto rom_138CE;     // BGE.B	$138CE
  DEF_ROMLOC(138CA) : move_toreg_16(0xFFFFF000, &D1); // MOVE.W	#$F000,D1
  DEF_ROMLOC(138CE) : move_tomem_16(D1, A0 + 0x10);   // MOVE.W	D1,16(A0)
  rom_136E0();                                        // BRA.W	$136E0
}
ROMFUNC(rom_138D6) {
  DEF_ROMLOC(138D6)
      : move_toreg_16(read_16(A0 + 0x14), &D0);       // MOVE.W	20(A0),D0
  DEF_ROMLOC(138DA) : if (CCR_EQ) goto rom_138DE;     // BEQ.B	$138DE
  DEF_ROMLOC(138DC) : if (CCR_PL) goto rom_138EC;     // BPL.B	$138EC
  DEF_ROMLOC(138DE) : bset_tomem_8(0x0, A0 + 0x22);   // BSET.B	#$00,34(A0)
  DEF_ROMLOC(138E4) : move_tomem_8(0x2, A0 + 0x1C);   // MOVE.B	#$02,28(A0)
  DEF_ROMLOC(138EA) : return;                         // RTS
  DEF_ROMLOC(138EC) : sub_toreg_16(D4, &D0);          // SUB.W	D4,D0
  DEF_ROMLOC(138EE) : if (CCR_CC) goto rom_138F4;     // BCC.B	$138F4
  DEF_ROMLOC(138F0) : move_toreg_16(0xFFFFFF80, &D0); // MOVE.W	#$FF80,D0
  DEF_ROMLOC(138F4) : move_tomem_16(D0, A0 + 0x14);   // MOVE.W	D0,20(A0)
  DEF_ROMLOC(138F8) : return;                         // RTS
}
ROMFUNC(rom_13ABE) {
  skiprestfromjump = false;
  DEF_ROMLOC(13ABE)
      : move_toreg_8(read_8(0xFFFFF603), &D0);    // MOVE.B	$F603,D0
  DEF_ROMLOC(13AC2) : and_toreg_8(0x70, &D0);     // ANDI.B	#$70,D0
  DEF_ROMLOC(13AC6) : if (CCR_EQ) goto rom_13B62; // BEQ.W	$13B62
  DEF_ROMLOC(13ACA) : move_toreg_32(0x0, &D0);    // MOVEQ.L	$00,D0
  DEF_ROMLOC(13ACC)
      : move_toreg_8(read_8(A0 + 0x26), &D0);       // MOVE.B	38(A0),D0
  DEF_ROMLOC(13AD0) : add_toreg_8(0xFFFFFF80, &D0); // ADDI.B	#$80,D0
  DEF_ROMLOC(13AD4) : rom_154B0();                  // BSR.W	$154B0
  DEF_ROMLOC(13AD8) : cmp_toreg_16(0x6, &D1);       // CMPI.W	#$0006,D1
  DEF_ROMLOC(13ADC) : if (CCR_LT) goto rom_13B62;   // BLT.W	$13B62
  DEF_ROMLOC(13AE0) : move_toreg_16(0x680, &D2);    // MOVE.W	#$0680,D2
  DEF_ROMLOC(13AE4) : btst_tomem_8(0x6, A0 + 0x22); // BTST.B	#$06,34(A0)
  DEF_ROMLOC(13AEA) : if (CCR_EQ) goto rom_13AF0;   // BEQ.B	$13AF0
  DEF_ROMLOC(13AEC) : move_toreg_16(0x380, &D2);    // MOVE.W	#$0380,D2
  DEF_ROMLOC(13AF0) : move_toreg_32(0x0, &D0);      // MOVEQ.L	$00,D0
  DEF_ROMLOC(13AF2)
      : move_toreg_8(read_8(A0 + 0x26), &D0);        // MOVE.B
                                                     // 38(A0),D0
  DEF_ROMLOC(13AF6) : sub_toreg_8(0x40, &D0);        // SUBI.B	#$40,D0
  DEF_ROMLOC(13AFA) : rom_29D2();                    // JSR	$000029D2
  DEF_ROMLOC(13B00) : muls_toreg_16(D2, &D1);        // MULS.W	D2,D1
  DEF_ROMLOC(13B02) : asr_toreg_32(0x8, &D1);        // ASR.L	#$08,D1
  DEF_ROMLOC(13B04) : add_tomem_16(D1, A0 + 0x10);   // ADD.W	D1,16(A0)
  DEF_ROMLOC(13B08) : muls_toreg_16(D2, &D0);        // MULS.W	D2,D0
  DEF_ROMLOC(13B0A) : asr_toreg_32(0x8, &D0);        // ASR.L	#$08,D0
  DEF_ROMLOC(13B0C) : add_tomem_16(D0, A0 + 0x12);   // ADD.W	D0,18(A0)
  DEF_ROMLOC(13B10) : bset_tomem_8(0x1, A0 + 0x22);  // BSET.B	#$01,34(A0)
  DEF_ROMLOC(13B16) : bclr_tomem_8(0x5, A0 + 0x22);  // BCLR.B	#$05,34(A0)
  DEF_ROMLOC(13B1C) : skiprestfromjump = true;       // TODO; // ADDQ.L	#$04,A7
  DEF_ROMLOC(13B1E) : move_tomem_8(0x1, A0 + 0x3C);  // MOVE.B	#$01,60(A0)
  DEF_ROMLOC(13B24) : clr_mem_8(A0 + 0x38);          // CLR.B	56(A0)
  DEF_ROMLOC(13B28) : move_toreg_16(SFX_JUMP, &D0);  // MOVE.W	#$00A0,D0
  DEF_ROMLOC(13B2C) : play_sound_special();          // JSR	$00001394
  DEF_ROMLOC(13B32) : move_tomem_8(0x13, A0 + 0x16); // MOVE.B	#$13,22(A0)
  DEF_ROMLOC(13B38) : move_tomem_8(0x9, A0 + 0x17);  // MOVE.B	#$09,23(A0)
  DEF_ROMLOC(13B3E) : btst_tomem_8(0x2, A0 + 0x22);  // BTST.B	#$02,34(A0)
  DEF_ROMLOC(13B44) : if (!CCR_EQ) goto rom_13B64;   // BNE.B	$13B64
  DEF_ROMLOC(13B46) : move_tomem_8(0xE, A0 + 0x16);  // MOVE.B	#$0E,22(A0)
  DEF_ROMLOC(13B4C) : move_tomem_8(0x7, A0 + 0x17);  // MOVE.B	#$07,23(A0)
  DEF_ROMLOC(13B52) : move_tomem_8(0x2, A0 + 0x1C);  // MOVE.B	#$02,28(A0)
  DEF_ROMLOC(13B58) : bset_tomem_8(0x2, A0 + 0x22);  // BSET.B	#$02,34(A0)
  DEF_ROMLOC(13B5E) : add_tomem_16(0x5, A0 + 0xC);   // ADDQ.W	#$05,12(A0)
  DEF_ROMLOC(13B62) : return;                        // RTS
  DEF_ROMLOC(13B64) : bset_tomem_8(0x4, A0 + 0x22);  // BSET.B	#$04,34(A0)
  DEF_ROMLOC(13B6A) : return;                        // RTS
}
ROMFUNC(rom_13B6C) {
  DEF_ROMLOC(13B6C) : tst_mem_8(A0 + 0x3C);           // TST.B	60(A0)
  DEF_ROMLOC(13B70) : if (CCR_EQ) goto rom_13B98;     // BEQ.B	$13B98
  DEF_ROMLOC(13B72) : move_toreg_16(0xFFFFFC00, &D1); // MOVE.W	#$FC00,D1
  DEF_ROMLOC(13B76) : btst_tomem_8(0x6, A0 + 0x22);   // BTST.B	#$06,34(A0)
  DEF_ROMLOC(13B7C) : if (CCR_EQ) goto rom_13B82;     // BEQ.B	$13B82
  DEF_ROMLOC(13B7E) : move_toreg_16(0xFFFFFE00, &D1); // MOVE.W	#$FE00,D1
  DEF_ROMLOC(13B82)
      : cmp_toreg_16(read_16(A0 + 0x12), &D1);    // CMP.W	18(A0),D1
  DEF_ROMLOC(13B86) : if (CCR_LE) goto rom_13B96; // BLE.B	$13B96
  DEF_ROMLOC(13B88)
      : move_toreg_8(read_8(0xFFFFF602), &D0);      // MOVE.B	$F602,D0
  DEF_ROMLOC(13B8C) : and_toreg_8(0x70, &D0);       // ANDI.B	#$70,D0
  DEF_ROMLOC(13B90) : if (!CCR_EQ) goto rom_13B96;  // BNE.B	$13B96
  DEF_ROMLOC(13B92) : move_tomem_16(D1, A0 + 0x12); // MOVE.W	D1,18(A0)
  DEF_ROMLOC(13B96) : return;                       // RTS
  DEF_ROMLOC(13B98)
      : cmp_tomem_16(0xFFFFF040, A0 + 0x12);      // CMPI.W	#$F040,18(A0)
  DEF_ROMLOC(13B9E) : if (CCR_GE) goto rom_13BA6; // BGE.B	$13BA6
  DEF_ROMLOC(13BA0)
      : move_tomem_16(0xFFFFF040, A0 + 0x12); // MOVE.W	#$F040,18(A0)
  DEF_ROMLOC(13BA6) : return;                 // RTS
}
ROMFUNC(rom_13BA8) {
  DEF_ROMLOC(13BA8)
      : move_toreg_8(read_8(A0 + 0x26), &D0);       // MOVE.B	38(A0),D0
  DEF_ROMLOC(13BAC) : add_toreg_8(0x60, &D0);       // ADDI.B	#$60,D0
  DEF_ROMLOC(13BB0) : cmp_toreg_8(0xFFFFFFC0, &D0); // CMPI.B	#$C0,D0
  DEF_ROMLOC(13BB4) : if (CCR_CC) goto rom_13BDC;   // BCC.B	$13BDC
  DEF_ROMLOC(13BB6)
      : move_toreg_8(read_8(A0 + 0x26), &D0);      // MOVE.B	38(A0),D0
  DEF_ROMLOC(13BBA) : rom_29D2();                  // JSR	$000029D2
  DEF_ROMLOC(13BC0) : muls_toreg_16(0x20, &D0);    // MULS.W	#$0020,D0
  DEF_ROMLOC(13BC4) : asr_toreg_32(0x8, &D0);      // ASR.L	#$08,D0
  DEF_ROMLOC(13BC6) : tst_mem_16(A0 + 0x14);       // TST.W	20(A0)
  DEF_ROMLOC(13BCA) : if (CCR_EQ) goto rom_13BDC;  // BEQ.B	$13BDC
  DEF_ROMLOC(13BCC) : if (CCR_MI) goto rom_13BD8;  // BMI.B	$13BD8
  DEF_ROMLOC(13BCE) : tst_reg_16(&D0);             // TST.W	D0
  DEF_ROMLOC(13BD0) : if (CCR_EQ) goto rom_13BD6;  // BEQ.B	$13BD6
  DEF_ROMLOC(13BD2) : add_tomem_16(D0, A0 + 0x14); // ADD.W	D0,20(A0)
  DEF_ROMLOC(13BD6) : return;                      // RTS
  DEF_ROMLOC(13BD8) : add_tomem_16(D0, A0 + 0x14); // ADD.W	D0,20(A0)
  DEF_ROMLOC(13BDC) : return;                      // RTS
}
ROMFUNC(rom_13BDE) {
  DEF_ROMLOC(13BDE)
      : move_toreg_8(read_8(A0 + 0x26), &D0);       // MOVE.B	38(A0),D0
  DEF_ROMLOC(13BE2) : add_toreg_8(0x60, &D0);       // ADDI.B	#$60,D0
  DEF_ROMLOC(13BE6) : cmp_toreg_8(0xFFFFFFC0, &D0); // CMPI.B	#$C0,D0
  DEF_ROMLOC(13BEA) : if (CCR_CC) goto rom_13C18;   // BCC.B	$13C18
  DEF_ROMLOC(13BEC)
      : move_toreg_8(read_8(A0 + 0x26), &D0);      // MOVE.B	38(A0),D0
  DEF_ROMLOC(13BF0) : rom_29D2();                  // JSR	$000029D2
  DEF_ROMLOC(13BF6) : muls_toreg_16(0x50, &D0);    // MULS.W	#$0050,D0
  DEF_ROMLOC(13BFA) : asr_toreg_32(0x8, &D0);      // ASR.L	#$08,D0
  DEF_ROMLOC(13BFC) : tst_mem_16(A0 + 0x14);       // TST.W	20(A0)
  DEF_ROMLOC(13C00) : if (CCR_MI) goto rom_13C0E;  // BMI.B	$13C0E
  DEF_ROMLOC(13C02) : tst_reg_16(&D0);             // TST.W	D0
  DEF_ROMLOC(13C04) : if (CCR_PL) goto rom_13C08;  // BPL.B	$13C08
  DEF_ROMLOC(13C06) : asr_toreg_32(0x2, &D0);      // ASR.L	#$02,D0
  DEF_ROMLOC(13C08) : add_tomem_16(D0, A0 + 0x14); // ADD.W	D0,20(A0)
  DEF_ROMLOC(13C0C) : return;                      // RTS
  DEF_ROMLOC(13C0E) : tst_reg_16(&D0);             // TST.W	D0
  DEF_ROMLOC(13C10) : if (CCR_MI) goto rom_13C14;  // BMI.B	$13C14
  DEF_ROMLOC(13C12) : asr_toreg_32(0x2, &D0);      // ASR.L	#$02,D0
  DEF_ROMLOC(13C14) : add_tomem_16(D0, A0 + 0x14); // ADD.W	D0,20(A0)
  DEF_ROMLOC(13C18) : return;                      // RTS
}
ROMFUNC(rom_13C1A) {
  DEF_ROMLOC(13C1C) : tst_mem_8(A0 + 0x38);        // TST.B	56(A0)
  DEF_ROMLOC(13C20) : if (!CCR_EQ) goto rom_13C54; // BNE.B	$13C54
  DEF_ROMLOC(13C22) : tst_mem_16(A0 + 0x3E);       // TST.W	62(A0)
  DEF_ROMLOC(13C26) : if (!CCR_EQ) goto rom_13C56; // BNE.B	$13C56
  DEF_ROMLOC(13C28)
      : move_toreg_8(read_8(A0 + 0x26), &D0);       // MOVE.B	38(A0),D0
  DEF_ROMLOC(13C2C) : add_toreg_8(0x20, &D0);       // ADDI.B	#$20,D0
  DEF_ROMLOC(13C30) : and_toreg_8(0xFFFFFFC0, &D0); // ANDI.B	#$C0,D0
  DEF_ROMLOC(13C34) : if (CCR_EQ) goto rom_13C54;   // BEQ.B	$13C54
  DEF_ROMLOC(13C36)
      : move_toreg_16(read_16(A0 + 0x14), &D0);       // MOVE.W	20(A0),D0
  DEF_ROMLOC(13C3A) : if (CCR_PL) goto rom_13C3E;     // BPL.B	$13C3E
  DEF_ROMLOC(13C3C) : neg_reg_16(&D0);                // NEG.W	D0
  DEF_ROMLOC(13C3E) : cmp_toreg_16(0x280, &D0);       // CMPI.W	#$0280,D0
  DEF_ROMLOC(13C42) : if (CCR_CC) goto rom_13C54;     // BCC.B	$13C54
  DEF_ROMLOC(13C44) : clr_mem_16(A0 + 0x14);          // CLR.W	20(A0)
  DEF_ROMLOC(13C48) : bset_tomem_8(0x1, A0 + 0x22);   // BSET.B	#$01,34(A0)
  DEF_ROMLOC(13C4E) : move_tomem_16(0x1E, A0 + 0x3E); // MOVE.W	#$001E,62(A0)
  DEF_ROMLOC(13C54) : return;                         // RTS
  DEF_ROMLOC(13C56) : sub_tomem_16(0x1, A0 + 0x3E);   // SUBQ.W	#$01,62(A0)
  DEF_ROMLOC(13C5A) : return;                         // RTS
}
ROMFUNC(rom_13C5C) {
  DEF_ROMLOC(13C5C)
      : move_toreg_8(read_8(A0 + 0x26), &D0);      // MOVE.B	38(A0),D0
  DEF_ROMLOC(13C60) : if (CCR_EQ) goto rom_13C76;  // BEQ.B	$13C76
  DEF_ROMLOC(13C62) : if (CCR_PL) goto rom_13C6C;  // BPL.B	$13C6C
  DEF_ROMLOC(13C64) : add_toreg_8(0x2, &D0);       // ADDQ.B	#$02,D0
  DEF_ROMLOC(13C66) : if (CCR_CC) goto rom_13C6A;  // BCC.B	$13C6A
  DEF_ROMLOC(13C68) : move_toreg_32(0x0, &D0);     // MOVEQ.L	$00,D0
  DEF_ROMLOC(13C6A) : goto rom_13C72;              // BRA.B	$13C72
  DEF_ROMLOC(13C6C) : sub_toreg_8(0x2, &D0);       // SUBQ.B	#$02,D0
  DEF_ROMLOC(13C6E) : if (CCR_CC) goto rom_13C72;  // BCC.B	$13C72
  DEF_ROMLOC(13C70) : move_toreg_32(0x0, &D0);     // MOVEQ.L	$00,D0
  DEF_ROMLOC(13C72) : move_tomem_8(D0, A0 + 0x26); // MOVE.B	D0,38(A0)
  DEF_ROMLOC(13C76) : return;                      // RTS
}
ROMFUNC(rom_13C78) {
  DEF_ROMLOC(13C78)
      : move_toreg_16(read_16(A0 + 0x10), &D1); // MOVE.W	16(A0),D1
  DEF_ROMLOC(13C7C)
      : move_toreg_16(read_16(A0 + 0x12), &D2);      // MOVE.W	18(A0),D2
  DEF_ROMLOC(13C80) : rom_2C6A();                    // JSR	$00002C6A
  DEF_ROMLOC(13C86) : move_tomem_8(D0, 0xFFFFFFEC);  // MOVE.B	D0,$FFEC
  DEF_ROMLOC(13C8A) : sub_toreg_8(0x20, &D0);        // SUBI.B	#$20,D0
  DEF_ROMLOC(13C8E) : move_tomem_8(D0, 0xFFFFFFED);  // MOVE.B	D0,$FFED
  DEF_ROMLOC(13C92) : and_toreg_8(0xFFFFFFC0, &D0);  // ANDI.B	#$C0,D0
  DEF_ROMLOC(13C96) : move_tomem_8(D0, 0xFFFFFFEE);  // MOVE.B	D0,$FFEE
  DEF_ROMLOC(13C9A) : cmp_toreg_8(0x40, &D0);        // CMPI.B	#$40,D0
  DEF_ROMLOC(13C9E) : if (CCR_EQ) goto rom_13D54;    // BEQ.W	$13D54
  DEF_ROMLOC(13CA2) : cmp_toreg_8(0xFFFFFF80, &D0);  // CMPI.B	#$80,D0
  DEF_ROMLOC(13CA6) : if (CCR_EQ) goto rom_13DB6;    // BEQ.W	$13DB6
  DEF_ROMLOC(13CAA) : cmp_toreg_8(0xFFFFFFC0, &D0);  // CMPI.B	#$C0,D0
  DEF_ROMLOC(13CAE) : if (CCR_EQ) goto rom_13E12;    // BEQ.W	$13E12
  DEF_ROMLOC(13CB2) : rom_157AA();                   // BSR.W	$157AA
  DEF_ROMLOC(13CB6) : tst_reg_16(&D1);               // TST.W	D1
  DEF_ROMLOC(13CB8) : if (CCR_PL) goto rom_13CC4;    // BPL.B	$13CC4
  DEF_ROMLOC(13CBA) : sub_tomem_16(D1, A0 + 0x8);    // SUB.W	D1,8(A0)
  DEF_ROMLOC(13CBE) : move_tomem_16(0x0, A0 + 0x10); // MOVE.W	#$0000,16(A0)
  DEF_ROMLOC(13CC4) : rom_1561C();                   // BSR.W	$1561C
  DEF_ROMLOC(13CC8) : tst_reg_16(&D1);               // TST.W	D1
  DEF_ROMLOC(13CCA) : if (CCR_PL) goto rom_13CD6;    // BPL.B	$13CD6
  DEF_ROMLOC(13CCC) : add_tomem_16(D1, A0 + 0x8);    // ADD.W	D1,8(A0)
  DEF_ROMLOC(13CD0) : move_tomem_16(0x0, A0 + 0x10); // MOVE.W	#$0000,16(A0)
  DEF_ROMLOC(13CD6) : rom_154D8();                   // BSR.W	$154D8
  DEF_ROMLOC(13CDA) : move_tomem_8(D1, 0xFFFFFFEF);  // MOVE.B	D1,$FFEF
  DEF_ROMLOC(13CDE) : tst_reg_16(&D1);               // TST.W	D1
  DEF_ROMLOC(13CE0) : if (CCR_PL) goto rom_13D52;    // BPL.B	$13D52
  DEF_ROMLOC(13CE2)
      : move_toreg_8(read_8(A0 + 0x12), &D2);        // MOVE.B
                                                     // 18(A0),D2
  DEF_ROMLOC(13CE6) : add_toreg_8(0x8, &D2);         // ADDQ.B	#$08,D2
  DEF_ROMLOC(13CE8) : neg_reg_8(&D2);                // NEG.B	D2
  DEF_ROMLOC(13CEA) : cmp_toreg_8(D2, &D1);          // CMP.B	D2,D1
  DEF_ROMLOC(13CEC) : if (CCR_GE) goto rom_13CF2;    // BGE.B	$13CF2
  DEF_ROMLOC(13CEE) : cmp_toreg_8(D2, &D0);          // CMP.B	D2,D0
  DEF_ROMLOC(13CF0) : if (CCR_LT) goto rom_13D52;    // BLT.B	$13D52
  DEF_ROMLOC(13CF2) : add_tomem_16(D1, A0 + 0xC);    // ADD.W	D1,12(A0)
  DEF_ROMLOC(13CF6) : move_tomem_8(D3, A0 + 0x26);   // MOVE.B	D3,38(A0)
  DEF_ROMLOC(13CFA) : rom_13E74();                   // BSR.W	$13E74
  DEF_ROMLOC(13CFE) : move_tomem_8(0x0, A0 + 0x1C);  // MOVE.B	#$00,28(A0)
  DEF_ROMLOC(13D04) : move_toreg_8(D3, &D0);         // MOVE.B	D3,D0
  DEF_ROMLOC(13D06) : add_toreg_8(0x20, &D0);        // ADDI.B	#$20,D0
  DEF_ROMLOC(13D0A) : and_toreg_8(0x40, &D0);        // ANDI.B	#$40,D0
  DEF_ROMLOC(13D0E) : if (!CCR_EQ) goto rom_13D30;   // BNE.B	$13D30
  DEF_ROMLOC(13D10) : move_toreg_8(D3, &D0);         // MOVE.B	D3,D0
  DEF_ROMLOC(13D12) : add_toreg_8(0x10, &D0);        // ADDI.B	#$10,D0
  DEF_ROMLOC(13D16) : and_toreg_8(0x20, &D0);        // ANDI.B	#$20,D0
  DEF_ROMLOC(13D1A) : if (CCR_EQ) goto rom_13D22;    // BEQ.B	$13D22
  DEF_ROMLOC(13D1C) : asr_mem_16(A0 + 0x12);         // ASR.W	18(A0)
  goto rom_13D44;                                    // BRA.B	$13D44
  DEF_ROMLOC(13D22) : move_tomem_16(0x0, A0 + 0x12); // MOVE.W	#$0000,18(A0)
  DEF_ROMLOC(13D28)
      : move_tomem_16(read_16(A0 + 0x10), A0 + 0x14); // MOVE.W	16(A0),20(A0)
  DEF_ROMLOC(13D2E) : return;                         // RTS
  DEF_ROMLOC(13D30)
      : move_tomem_16(0x0, A0 + 0x10); // MOVE.W	#$0000,16(A0)
  DEF_ROMLOC(13D36)
      : cmp_tomem_16(0xFC0, A0 + 0x12);           // CMPI.W	#$0FC0,18(A0)
  DEF_ROMLOC(13D3C) : if (CCR_LE) goto rom_13D44; // BLE.B	$13D44
  DEF_ROMLOC(13D3E)
      : move_tomem_16(0xFC0, A0 + 0x12); // MOVE.W
                                         // #$0FC0,18(A0)
  DEF_ROMLOC(13D44)
      : move_tomem_16(read_16(A0 + 0x12), A0 + 0x14); // MOVE.W	18(A0),20(A0)
  DEF_ROMLOC(13D4A) : tst_reg_8(&D3);                 // TST.B	D3
  DEF_ROMLOC(13D4C) : if (CCR_PL) goto rom_13D52;     // BPL.B	$13D52
  DEF_ROMLOC(13D4E) : neg_mem_16(A0 + 0x14);          // NEG.W	20(A0)
  DEF_ROMLOC(13D52) : return;                         // RTS
  DEF_ROMLOC(13D54) : rom_157AA();                    // BSR.W	$157AA
  DEF_ROMLOC(13D58) : tst_reg_16(&D1);                // TST.W	D1
  DEF_ROMLOC(13D5A) : if (CCR_PL) goto rom_13D6E;     // BPL.B	$13D6E
  DEF_ROMLOC(13D5C) : sub_tomem_16(D1, A0 + 0x8);     // SUB.W	D1,8(A0)
  DEF_ROMLOC(13D60) : move_tomem_16(0x0, A0 + 0x10);  // MOVE.W	#$0000,16(A0)
  DEF_ROMLOC(13D66)
      : move_tomem_16(read_16(A0 + 0x12), A0 + 0x14); // MOVE.W	18(A0),20(A0)
  DEF_ROMLOC(13D6C) : return;                         // RTS
  DEF_ROMLOC(13D6E) : rom_15670();                    // BSR.W	$15670
  DEF_ROMLOC(13D72) : tst_reg_16(&D1);                // TST.W	D1
  DEF_ROMLOC(13D74) : if (CCR_PL) goto rom_13D88;     // BPL.B	$13D88
  DEF_ROMLOC(13D76) : sub_tomem_16(D1, A0 + 0xC);     // SUB.W	D1,12(A0)
  DEF_ROMLOC(13D7A) : tst_mem_16(A0 + 0x12);          // TST.W	18(A0)
  DEF_ROMLOC(13D7E) : if (CCR_PL) goto rom_13D86;     // BPL.B	$13D86
  DEF_ROMLOC(13D80) : move_tomem_16(0x0, A0 + 0x12);  // MOVE.W	#$0000,18(A0)
  DEF_ROMLOC(13D86) : return;                         // RTS
  DEF_ROMLOC(13D88) : tst_mem_16(A0 + 0x12);          // TST.W	18(A0)
  DEF_ROMLOC(13D8C) : if (CCR_MI) goto rom_13DB4;     // BMI.B	$13DB4
  DEF_ROMLOC(13D8E) : rom_154D8();                    // BSR.W	$154D8
  DEF_ROMLOC(13D92) : tst_reg_16(&D1);                // TST.W	D1
  DEF_ROMLOC(13D94) : if (CCR_PL) goto rom_13DB4;     // BPL.B	$13DB4
  DEF_ROMLOC(13D96) : add_tomem_16(D1, A0 + 0xC);     // ADD.W	D1,12(A0)
  DEF_ROMLOC(13D9A) : move_tomem_8(D3, A0 + 0x26);    // MOVE.B	D3,38(A0)
  DEF_ROMLOC(13D9E) : rom_13E74();                    // BSR.W	$13E74
  DEF_ROMLOC(13DA2) : move_tomem_8(0x0, A0 + 0x1C);   // MOVE.B	#$00,28(A0)
  DEF_ROMLOC(13DA8) : move_tomem_16(0x0, A0 + 0x12);  // MOVE.W	#$0000,18(A0)
  DEF_ROMLOC(13DAE)
      : move_tomem_16(read_16(A0 + 0x10), A0 + 0x14); // MOVE.W	16(A0),20(A0)
  DEF_ROMLOC(13DB4) : return;                         // RTS
  DEF_ROMLOC(13DB6) : rom_157AA();                    // BSR.W	$157AA
  DEF_ROMLOC(13DBA) : tst_reg_16(&D1);                // TST.W	D1
  DEF_ROMLOC(13DBC) : if (CCR_PL) goto rom_13DC8;     // BPL.B	$13DC8
  DEF_ROMLOC(13DBE) : sub_tomem_16(D1, A0 + 0x8);     // SUB.W	D1,8(A0)
  DEF_ROMLOC(13DC2) : move_tomem_16(0x0, A0 + 0x10);  // MOVE.W	#$0000,16(A0)
  DEF_ROMLOC(13DC8) : rom_1561C();                    // BSR.W	$1561C
  DEF_ROMLOC(13DCC) : tst_reg_16(&D1);                // TST.W	D1
  DEF_ROMLOC(13DCE) : if (CCR_PL) goto rom_13DDA;     // BPL.B	$13DDA
  DEF_ROMLOC(13DD0) : add_tomem_16(D1, A0 + 0x8);     // ADD.W	D1,8(A0)
  DEF_ROMLOC(13DD4) : move_tomem_16(0x0, A0 + 0x10);  // MOVE.W	#$0000,16(A0)
  DEF_ROMLOC(13DDA) : rom_15670();                    // BSR.W	$15670
  DEF_ROMLOC(13DDE) : tst_reg_16(&D1);                // TST.W	D1
  DEF_ROMLOC(13DE0) : if (CCR_PL) goto rom_13E10;     // BPL.B	$13E10
  DEF_ROMLOC(13DE2) : sub_tomem_16(D1, A0 + 0xC);     // SUB.W	D1,12(A0)
  DEF_ROMLOC(13DE6) : move_toreg_8(D3, &D0);          // MOVE.B	D3,D0
  DEF_ROMLOC(13DE8) : add_toreg_8(0x20, &D0);         // ADDI.B	#$20,D0
  DEF_ROMLOC(13DEC) : and_toreg_8(0x40, &D0);         // ANDI.B	#$40,D0
  DEF_ROMLOC(13DF0) : if (!CCR_EQ) goto rom_13DFA;    // BNE.B	$13DFA
  DEF_ROMLOC(13DF2) : move_tomem_16(0x0, A0 + 0x12);  // MOVE.W	#$0000,18(A0)
  DEF_ROMLOC(13DF8) : return;                         // RTS
  DEF_ROMLOC(13DFA) : move_tomem_8(D3, A0 + 0x26);    // MOVE.B	D3,38(A0)
  DEF_ROMLOC(13DFE) : rom_13E74();                    // BSR.W	$13E74
  DEF_ROMLOC(13E02)
      : move_tomem_16(read_16(A0 + 0x12), A0 + 0x14); // MOVE.W	18(A0),20(A0)
  DEF_ROMLOC(13E08) : tst_reg_8(&D3);                 // TST.B	D3
  DEF_ROMLOC(13E0A) : if (CCR_PL) goto rom_13E10;     // BPL.B	$13E10
  DEF_ROMLOC(13E0C) : neg_mem_16(A0 + 0x14);          // NEG.W	20(A0)
  DEF_ROMLOC(13E10) : return;                         // RTS
  DEF_ROMLOC(13E12) : rom_1561C();                    // BSR.W	$1561C
  DEF_ROMLOC(13E16) : tst_reg_16(&D1);                // TST.W	D1
  DEF_ROMLOC(13E18) : if (CCR_PL) goto rom_13E2C;     // BPL.B	$13E2C
  DEF_ROMLOC(13E1A) : add_tomem_16(D1, A0 + 0x8);     // ADD.W	D1,8(A0)
  DEF_ROMLOC(13E1E) : move_tomem_16(0x0, A0 + 0x10);  // MOVE.W	#$0000,16(A0)
  DEF_ROMLOC(13E24)
      : move_tomem_16(read_16(A0 + 0x12), A0 + 0x14); // MOVE.W	18(A0),20(A0)
  DEF_ROMLOC(13E2A) : return;                         // RTS
  DEF_ROMLOC(13E2C) : rom_15670();                    // BSR.W	$15670
  DEF_ROMLOC(13E30) : tst_reg_16(&D1);                // TST.W	D1
  DEF_ROMLOC(13E32) : if (CCR_PL) goto rom_13E46;     // BPL.B	$13E46
  DEF_ROMLOC(13E34) : sub_tomem_16(D1, A0 + 0xC);     // SUB.W	D1,12(A0)
  DEF_ROMLOC(13E38) : tst_mem_16(A0 + 0x12);          // TST.W	18(A0)
  DEF_ROMLOC(13E3C) : if (CCR_PL) goto rom_13E44;     // BPL.B	$13E44
  DEF_ROMLOC(13E3E) : move_tomem_16(0x0, A0 + 0x12);  // MOVE.W	#$0000,18(A0)
  DEF_ROMLOC(13E44) : return;                         // RTS
  DEF_ROMLOC(13E46) : tst_mem_16(A0 + 0x12);          // TST.W	18(A0)
  DEF_ROMLOC(13E4A) : if (CCR_MI) goto rom_13E72;     // BMI.B	$13E72
  DEF_ROMLOC(13E4C) : rom_154D8();                    // BSR.W	$154D8
  DEF_ROMLOC(13E50) : tst_reg_16(&D1);                // TST.W	D1
  DEF_ROMLOC(13E52) : if (CCR_PL) goto rom_13E72;     // BPL.B	$13E72
  DEF_ROMLOC(13E54) : add_tomem_16(D1, A0 + 0xC);     // ADD.W	D1,12(A0)
  DEF_ROMLOC(13E58) : move_tomem_8(D3, A0 + 0x26);    // MOVE.B	D3,38(A0)
  DEF_ROMLOC(13E5C) : rom_13E74();                    // BSR.W	$13E74
  DEF_ROMLOC(13E60) : move_tomem_8(0x0, A0 + 0x1C);   // MOVE.B	#$00,28(A0)
  DEF_ROMLOC(13E66) : move_tomem_16(0x0, A0 + 0x12);  // MOVE.W	#$0000,18(A0)
  DEF_ROMLOC(13E6C)
      : move_tomem_16(read_16(A0 + 0x10), A0 + 0x14); // MOVE.W	16(A0),20(A0)
  DEF_ROMLOC(13E72) : return;                         // RTS
}
ROMFUNC(rom_13E74) {
  DEF_ROMLOC(13E74) : btst_tomem_8(0x4, A0 + 0x22);   // BTST.B	#$04,34(A0)
  DEF_ROMLOC(13E7A) : if (CCR_EQ) goto rom_13E82;     // BEQ.B	$13E82
  DEF_ROMLOC(13E82) : bclr_tomem_8(0x5, A0 + 0x22);   // BCLR.B	#$05,34(A0)
  DEF_ROMLOC(13E88) : bclr_tomem_8(0x1, A0 + 0x22);   // BCLR.B	#$01,34(A0)
  DEF_ROMLOC(13E8E) : bclr_tomem_8(0x4, A0 + 0x22);   // BCLR.B	#$04,34(A0)
  DEF_ROMLOC(13E94) : btst_tomem_8(0x2, A0 + 0x22);   // BTST.B	#$02,34(A0)
  DEF_ROMLOC(13E9A) : if (CCR_EQ) goto rom_13EB8;     // BEQ.B	$13EB8
  DEF_ROMLOC(13E9C) : bclr_tomem_8(0x2, A0 + 0x22);   // BCLR.B	#$02,34(A0)
  DEF_ROMLOC(13EA2) : move_tomem_8(0x13, A0 + 0x16);  // MOVE.B	#$13,22(A0)
  DEF_ROMLOC(13EA8) : move_tomem_8(0x9, A0 + 0x17);   // MOVE.B	#$09,23(A0)
  DEF_ROMLOC(13EAE) : move_tomem_8(0x0, A0 + 0x1C);   // MOVE.B	#$00,28(A0)
  DEF_ROMLOC(13EB4) : sub_tomem_16(0x5, A0 + 0xC);    // SUBQ.W	#$05,12(A0)
  DEF_ROMLOC(13EB8) : move_tomem_8(0x0, A0 + 0x3C);   // MOVE.B	#$00,60(A0)
  DEF_ROMLOC(13EBE) : move_tomem_16(0x0, 0xFFFFF7D0); // MOVE.W	#$0000,$F7D0
  DEF_ROMLOC(13EC4) : return;                         // RTS
}
ROMFUNC(rom_13EC6) {
  DEF_ROMLOC(13EC6) : rom_DC6C();                    // JSR	$0000DC6C
  DEF_ROMLOC(13ECC) : add_tomem_16(0x30, A0 + 0x12); // ADDI.W	#$0030,18(A0)
  DEF_ROMLOC(13ED2) : btst_tomem_8(0x6, A0 + 0x22);  // BTST.B	#$06,34(A0)
  DEF_ROMLOC(13ED8) : if (CCR_EQ) goto rom_13EE0;    // BEQ.B	$13EE0
  DEF_ROMLOC(13EDA) : sub_tomem_16(0x20, A0 + 0x12); // SUBI.W	#$0020,18(A0)
  DEF_ROMLOC(13EE0) : rom_13EFA();                   // BSR.W	$13EFA
  DEF_ROMLOC(13EE4) : rom_139D8();                   // BSR.W	$139D8
  DEF_ROMLOC(13EE8) : rom_13432();                   // BSR.W	$13432
  DEF_ROMLOC(13EEC) : rom_14098();                   // BSR.W	$14098
  DEF_ROMLOC(13EF0) : rom_14312();                   // BSR.W	$14312
  DEF_ROMLOC(13EF4) : rom_DC92();                    // JMP	$0000DC92
}
ROMFUNC(rom_13EFA) {
  DEF_ROMLOC(13EFA)
      : move_toreg_16(read_16(0xFFFFF72E), &D0); // MOVE.W	$F72E,D0
  DEF_ROMLOC(13EFE) : add_toreg_16(0xE0, &D0);   // ADDI.W	#$00E0,D0
  DEF_ROMLOC(13F02)
      : cmp_toreg_16(read_16(A0 + 0xC), &D0); // CMP.W
                                              // 12(A0),D0
  DEF_ROMLOC(13F06) : if (CCR_CS) {
    rom_1B84E();
    return;
  }                                                   // BCS.W	$1B84E
  DEF_ROMLOC(13F0A) : rom_13C78();                    // BSR.W	$13C78
  DEF_ROMLOC(13F0E) : btst_tomem_8(0x1, A0 + 0x22);   // BTST.B	#$01,34(A0)
  DEF_ROMLOC(13F14) : if (!CCR_EQ) goto rom_13F34;    // BNE.B	$13F34
  DEF_ROMLOC(13F16) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(13F18) : move_tomem_16(D0, A0 + 0x12);   // MOVE.W	D0,18(A0)
  DEF_ROMLOC(13F1C) : move_tomem_16(D0, A0 + 0x10);   // MOVE.W	D0,16(A0)
  DEF_ROMLOC(13F20) : move_tomem_16(D0, A0 + 0x14);   // MOVE.W	D0,20(A0)
  DEF_ROMLOC(13F24) : move_tomem_8(0x0, A0 + 0x1C);   // MOVE.B	#$00,28(A0)
  DEF_ROMLOC(13F2A) : sub_tomem_8(0x2, A0 + 0x24);    // SUBQ.B	#$02,36(A0)
  DEF_ROMLOC(13F2E) : move_tomem_16(0x78, A0 + 0x30); // MOVE.W	#$0078,48(A0)
  DEF_ROMLOC(13F34) : return;                         // RTS
}
ROMFUNC(rom_13F36) {
  DEF_ROMLOC(13F36) : rom_13F52(); // BSR.W	$13F52
  DEF_ROMLOC(13F3A) : rom_DC40();  // JSR	$0000DC40
  DEF_ROMLOC(13F40) : rom_13432(); // BSR.W	$13432
  DEF_ROMLOC(13F44) : rom_14098(); // BSR.W	$14098
  DEF_ROMLOC(13F48) : rom_14312(); // BSR.W	$14312
  DEF_ROMLOC(13F4C) : rom_DC92();  // JMP	$0000DC92
}
ROMFUNC(rom_1B7AA) {
  DEF_ROMLOC(1B7AA) : tst_mem_8(0xFFFFFE2C);       // TST.B	$FE2C
  DEF_ROMLOC(1B7AE) : if (!CCR_EQ) goto rom_1B7D2; // BNE.B	$1B7D2
  DEF_ROMLOC(1B7B0) : tst_mem_16(0xFFFFFE20);      // TST.W	$FE20
  DEF_ROMLOC(1B7B4) : if (CCR_EQ) goto rom_1B846;  // BEQ.W	$1B846
  DEF_ROMLOC(1B7B8) : rom_E11A();                  // JSR	$0000E11A
  DEF_ROMLOC(1B7BE) : if (!CCR_EQ) goto rom_1B7D2; // BNE.B	$1B7D2
  DEF_ROMLOC(1B7C0)
      : move_tomem_8(OBJ_RINGLOSS,
                     A1 + offsetof(object, id)); // MOVE.B	#$37,0(A1)
  DEF_ROMLOC(1B7C6)
      : move_tomem_16(read_16(A0 + 0x8), A1 + 0x8); // MOVE.W	8(A0),8(A1)
  DEF_ROMLOC(1B7CC)
      : move_tomem_16(read_16(A0 + 0xC), A1 + 0xC);  // MOVE.W	12(A0),12(A1)
  DEF_ROMLOC(1B7D2) : move_tomem_8(0x0, 0xFFFFFE2C); // MOVE.B	#$00,$FE2C
  DEF_ROMLOC(1B7D8) : move_tomem_8(0x4, A0 + 0x24);  // MOVE.B	#$04,36(A0)
  DEF_ROMLOC(1B7DE) : rom_13E74();                   // BSR.W	$13E74
  DEF_ROMLOC(1B7E2) : bset_tomem_8(0x1, A0 + 0x22);  // BSET.B	#$01,34(A0)
  DEF_ROMLOC(1B7E8)
      : move_tomem_16(0xFFFFFC00, A0 + 0x12); // MOVE.W	#$FC00,18(A0)
  DEF_ROMLOC(1B7EE)
      : move_tomem_16(0xFFFFFE00, A0 + 0x10);       // MOVE.W	#$FE00,16(A0)
  DEF_ROMLOC(1B7F4) : btst_tomem_8(0x6, A0 + 0x22); // BTST.B	#$06,34(A0)
  DEF_ROMLOC(1B7FA) : if (CCR_EQ) goto rom_1B808;   // BEQ.B	$1B808
  DEF_ROMLOC(1B7FC)
      : move_tomem_16(0xFFFFFE00, A0 + 0x12); // MOVE.W	#$FE00,18(A0)
  DEF_ROMLOC(1B802)
      : move_tomem_16(0xFFFFFF00, A0 + 0x10); // MOVE.W	#$FF00,16(A0)
  DEF_ROMLOC(1B808)
      : move_toreg_16(read_16(A0 + 0x8), &D0);              // MOVE.W	8(A0),D0
  DEF_ROMLOC(1B80C) : cmp_toreg_16(read_16(A2 + 0x8), &D0); // CMP.W	8(A2),D0
  DEF_ROMLOC(1B810) : if (CCR_CS) goto rom_1B816;           // BCS.B	$1B816
  DEF_ROMLOC(1B812) : neg_mem_16(A0 + 0x10);                // NEG.W	16(A0)
  DEF_ROMLOC(1B816) : move_tomem_16(0x0, A0 + 0x14);  // MOVE.W	#$0000,20(A0)
  DEF_ROMLOC(1B81C) : move_tomem_8(0x1A, A0 + 0x1C);  // MOVE.B	#$1A,28(A0)
  DEF_ROMLOC(1B822) : move_tomem_16(0x78, A0 + 0x30); // MOVE.W	#$0078,48(A0)
  DEF_ROMLOC(1B828) : move_toreg_16(SFX_DEATH, &D0);  // MOVE.W	#$00A3,D0
  DEF_ROMLOC(1B82C)
      : cmp_tomem_8(OBJ_SPIKES,
                    A2 + offsetof(object, id));    // CMPI.B	#$36,(A2)
  DEF_ROMLOC(1B830) : if (!CCR_EQ) goto rom_1B83C; // BNE.B	$1B83C
  DEF_ROMLOC(1B832)
      : cmp_tomem_8(OBJ_HARPOON,
                    A2 + offsetof(object, id));    // CMPI.B	#$16,(A2)
  DEF_ROMLOC(1B836) : if (!CCR_EQ) goto rom_1B83C; // BNE.B	$1B83C
  DEF_ROMLOC(1B838)
      : move_toreg_16(SFX_HITSPIKES, &D0);            // MOVE.W
                                                      // #$00A6,D0
  DEF_ROMLOC(1B83C) : play_sound_special();           // JSR	$00001394
  DEF_ROMLOC(1B842) : move_toreg_32(0xFFFFFFFF, &D0); // MOVEQ.L	$FF,D0
  DEF_ROMLOC(1B844) : return;                         // RTS
  DEF_ROMLOC(1B846) : tst_mem_16(0xFFFFFFFA);         // TST.W	$FFFA
  DEF_ROMLOC(1B84A) : if (!CCR_EQ) goto rom_1B7D2;    // BNE.W	$1B7D2
  rom_1B84E();
}
ROMFUNC(rom_1B84E) {
  DEF_ROMLOC(1B84E) : tst_mem_16(0xFFFFFE08);        // TST.W	$FE08
  DEF_ROMLOC(1B852) : if (!CCR_EQ) goto rom_1B8A2;   // BNE.B	$1B8A2
  DEF_ROMLOC(1B854) : move_tomem_8(0x0, 0xFFFFFE2D); // MOVE.B	#$00,$FE2D
  DEF_ROMLOC(1B85A) : move_tomem_8(0x6, A0 + 0x24);  // MOVE.B	#$06,36(A0)
  DEF_ROMLOC(1B860) : rom_13E74();                   // BSR.W	$13E74
  DEF_ROMLOC(1B864) : bset_tomem_8(0x1, A0 + 0x22);  // BSET.B	#$01,34(A0)
  DEF_ROMLOC(1B86A)
      : move_tomem_16(0xFFFFF900, A0 + 0x12);        // MOVE.W	#$F900,18(A0)
  DEF_ROMLOC(1B870) : move_tomem_16(0x0, A0 + 0x10); // MOVE.W	#$0000,16(A0)
  DEF_ROMLOC(1B876) : move_tomem_16(0x0, A0 + 0x14); // MOVE.W	#$0000,20(A0)
  DEF_ROMLOC(1B87C)
      : move_tomem_16(read_16(A0 + 0xC), A0 + 0x38); // MOVE.W	12(A0),56(A0)
  DEF_ROMLOC(1B882) : move_tomem_8(0x18, A0 + 0x1C); // MOVE.B	#$18,28(A0)
  DEF_ROMLOC(1B888) : bset_tomem_8(0x7, A0 + 0x2);   // BSET.B	#$07,2(A0)
  DEF_ROMLOC(1B88E) : move_toreg_16(SFX_DEATH, &D0); // MOVE.W	#$00A3,D0
  DEF_ROMLOC(1B892)
      : cmp_tomem_8(OBJ_SPIKES,
                    A2 + offsetof(object, id));    // CMPI.B	#$36,(A2)
  DEF_ROMLOC(1B896) : if (!CCR_EQ) goto rom_1B89C; // BNE.B	$1B89C
  DEF_ROMLOC(1B898)
      : move_toreg_16(SFX_HITSPIKES, &D0);            // MOVE.W
                                                      // #$00A6,D0
  DEF_ROMLOC(1B89C) : play_sound_special();           // JSR	$00001394
  DEF_ROMLOC(1B8A2) : move_toreg_32(0xFFFFFFFF, &D0); // MOVEQ.L	$FF,D0
  DEF_ROMLOC(1B8A4) : return;                         // RTS
}
ROMFUNC(rom_13FD6) {
  DEF_ROMLOC(13FD6) : tst_mem_16(A0 + 0x3A);          // TST.W	58(A0)
  DEF_ROMLOC(13FDA) : if (CCR_EQ) goto rom_13FE8;     // BEQ.B	$13FE8
  DEF_ROMLOC(13FDC) : sub_tomem_16(0x1, A0 + 0x3A);   // SUBQ.W	#$01,58(A0)
  DEF_ROMLOC(13FE0) : if (!CCR_EQ) goto rom_13FE8;    // BNE.B	$13FE8
  DEF_ROMLOC(13FE2) : move_tomem_16(0x1, 0xFFFFFE02); // MOVE.W	#$0001,$FE02
  DEF_ROMLOC(13FE8) : return;                         // RTS
}
ROMFUNC(rom_13FEA) {
  DEF_ROMLOC(13FEA) : cmp_tomem_8(ZONE_SLZ, v_zone); // CMPI.B	#$03,$FE10
  DEF_ROMLOC(13FF0) : if (CCR_EQ) goto rom_13FFA;    // BEQ.B	$13FFA
  DEF_ROMLOC(13FF2) : tst_mem_8(v_zone);             // TST.B	$FE10
  DEF_ROMLOC(13FF6) : if (!CCR_EQ) goto rom_14096;   // BNE.W	$14096
  DEF_ROMLOC(13FFA)
      : move_toreg_16(read_16(A0 + 0xC), &D0);             // MOVE.W	12(A0),D0
  DEF_ROMLOC(13FFE) : lsr_toreg_16(0x1, &D0);              // LSR.W	#$01,D0
  DEF_ROMLOC(14000) : and_toreg_16(0x380, &D0);            // ANDI.W	#$0380,D0
  DEF_ROMLOC(14004) : move_toreg_8(read_8(A0 + 0x8), &D1); // MOVE.B	8(A0),D1
  DEF_ROMLOC(14008) : and_toreg_16(0x7F, &D1);             // ANDI.W	#$007F,D1
  DEF_ROMLOC(1400C) : add_toreg_16(D1, &D0);               // ADD.W	D1,D0
  DEF_ROMLOC(1400E) : move_toreg_32(0xFFFFA400, &A1);      // LEA.L	$A400,A1
  DEF_ROMLOC(14012)
      : move_toreg_8(read_8((s32)A1 + (s8)0x0 + (s16)D0),
                     &D1); // MOVE.B	0(A1,D0),D1
  DEF_ROMLOC(14016) : cmp_toreg_8(read_8(0xFFFFF7AE), &D1); // CMP.B	$F7AE,D1
  DEF_ROMLOC(1401A) : if (CCR_EQ) {
    rom_13A80();
    return;
  }                                                         // BEQ.W	$13A80
  DEF_ROMLOC(1401E) : cmp_toreg_8(read_8(0xFFFFF7AF), &D1); // CMP.B	$F7AF,D1
  DEF_ROMLOC(14022) : if (CCR_EQ) {
    rom_13A80();
    return;
  }                                                         // BEQ.W	$13A80
  DEF_ROMLOC(14026) : cmp_toreg_8(read_8(0xFFFFF7AC), &D1); // CMP.B	$F7AC,D1
  DEF_ROMLOC(1402A) : if (CCR_EQ) goto rom_1404A;           // BEQ.B	$1404A
  DEF_ROMLOC(1402C) : cmp_toreg_8(read_8(0xFFFFF7AD), &D1); // CMP.B	$F7AD,D1
  DEF_ROMLOC(14030) : if (CCR_EQ) goto rom_1403A;           // BEQ.B	$1403A
  DEF_ROMLOC(14032) : bclr_tomem_8(0x6, A0 + 0x1);          // BCLR.B	#$06,1(A0)
  DEF_ROMLOC(14038) : return;                               // RTS
  DEF_ROMLOC(1403A) : btst_tomem_8(0x1, A0 + 0x22); // BTST.B	#$01,34(A0)
  DEF_ROMLOC(14040) : if (CCR_EQ) goto rom_1404A;   // BEQ.B	$1404A
  DEF_ROMLOC(14042) : bclr_tomem_8(0x6, A0 + 0x1);  // BCLR.B	#$06,1(A0)
  DEF_ROMLOC(14048) : return;                       // RTS
  DEF_ROMLOC(1404A)
      : move_toreg_16(read_16(A0 + 0x8), &D2);      // MOVE.W	8(A0),D2
  DEF_ROMLOC(1404E) : cmp_toreg_8(0x2C, &D2);       // CMPI.B	#$2C,D2
  DEF_ROMLOC(14052) : if (CCR_CC) goto rom_1405C;   // BCC.B	$1405C
  DEF_ROMLOC(14054) : bclr_tomem_8(0x6, A0 + 0x1);  // BCLR.B	#$06,1(A0)
  DEF_ROMLOC(1405A) : return;                       // RTS
  DEF_ROMLOC(1405C) : cmp_toreg_8(0xFFFFFFE0, &D2); // CMPI.B	#$E0,D2
  DEF_ROMLOC(14060) : if (CCR_CS) goto rom_1406A;   // BCS.B	$1406A
  DEF_ROMLOC(14062) : bset_tomem_8(0x6, A0 + 0x1);  // BSET.B	#$06,1(A0)
  DEF_ROMLOC(14068) : return;                       // RTS
  DEF_ROMLOC(1406A) : btst_tomem_8(0x6, A0 + 0x1);  // BTST.B	#$06,1(A0)
  DEF_ROMLOC(14070) : if (!CCR_EQ) goto rom_14086;  // BNE.B	$14086
  DEF_ROMLOC(14072)
      : move_toreg_8(read_8(A0 + 0x26), &D1);       // MOVE.B	38(A0),D1
  DEF_ROMLOC(14076) : if (CCR_EQ) goto rom_14096;   // BEQ.B	$14096
  DEF_ROMLOC(14078) : cmp_toreg_8(0xFFFFFF80, &D1); // CMPI.B	#$80,D1
  DEF_ROMLOC(1407C) : if (CCR_HI) goto rom_14096;   // BHI.B	$14096
  DEF_ROMLOC(1407E) : bset_tomem_8(0x6, A0 + 0x1);  // BSET.B	#$06,1(A0)
  DEF_ROMLOC(14084) : return;                       // RTS
  DEF_ROMLOC(14086)
      : move_toreg_8(read_8(A0 + 0x26), &D1);       // MOVE.B	38(A0),D1
  DEF_ROMLOC(1408A) : cmp_toreg_8(0xFFFFFF80, &D1); // CMPI.B	#$80,D1
  DEF_ROMLOC(1408E) : if (CCR_LS) goto rom_14096;   // BLS.B	$14096
  DEF_ROMLOC(14090) : bclr_tomem_8(0x6, A0 + 0x1);  // BCLR.B	#$06,1(A0)
  DEF_ROMLOC(14096) : return;                       // RTS
}
ROMFUNC(rom_15538) {
  DEF_ROMLOC(15538)
      : move_toreg_8(read_8(0xFFFFF76A), &D3);    // MOVE.B	$F76A,D3
  DEF_ROMLOC(1553C) : cmp_toreg_16(D0, &D1);      // CMP.W	D0,D1
  DEF_ROMLOC(1553E) : if (CCR_LE) goto rom_15546; // BLE.B	$15546
  DEF_ROMLOC(15540)
      : move_toreg_8(read_8(0xFFFFF768), &D3);    // MOVE.B	$F768,D3
  DEF_ROMLOC(15544) : exg_toreg_32(&D0, &D1);     // EXG.L	D0,D1
  DEF_ROMLOC(15546) : btst_toreg_32(0x0, &D3);    // BTST.L	#$00,D3
  DEF_ROMLOC(1554A) : if (CCR_EQ) goto rom_1554E; // BEQ.B	$1554E
  DEF_ROMLOC(1554C) : move_toreg_8(D2, &D3);      // MOVE.B	D2,D3
  DEF_ROMLOC(1554E) : return;                     // RTS
  DEF_ROMLOC(15550)
      : move_toreg_16(read_16(A0 + 0xC), &D2); // MOVE.W	12(A0),D2
  DEF_ROMLOC(15554)
      : move_toreg_16(read_16(A0 + 0x8), &D3); // MOVE.W	8(A0),D3
  rom_15558(); // Detected flow into next function
}
ROMFUNC(rom_15558) {
  DEF_ROMLOC(15558) : add_toreg_16(0xA, &D2);         // ADDI.W	#$000A,D2
  DEF_ROMLOC(1555C) : move_toreg_32(0xFFFFF768, &A4); // LEA.L	$F768,A4
  DEF_ROMLOC(15560) : move_toreg_16(0x10, &A3);       // MOVEA.W	#$0010,A3
  DEF_ROMLOC(15564) : move_toreg_16(0x0, &D6);        // MOVE.W	#$0000,D6
  DEF_ROMLOC(15568) : move_toreg_32(0xE, &D5);        // MOVEQ.L	$0E,D5
  DEF_ROMLOC(1556A) : rom_15136();                    // BSR.W	$15136
  DEF_ROMLOC(1556E) : move_toreg_8(0x0, &D2);         // MOVE.B	#$00,D2
  rom_15572(); // Detected flow into next function
}
ROMFUNC(rom_15572) {
  DEF_ROMLOC(15572)
      : move_toreg_8(read_8(0xFFFFF768), &D3);    // MOVE.B	$F768,D3
  DEF_ROMLOC(15576) : btst_toreg_32(0x0, &D3);    // BTST.L	#$00,D3
  DEF_ROMLOC(1557A) : if (CCR_EQ) goto rom_1557E; // BEQ.B	$1557E
  DEF_ROMLOC(1557C) : move_toreg_8(D2, &D3);      // MOVE.B	D2,D3
  DEF_ROMLOC(1557E) : return;                     // RTS
}
ROMFUNC(rom_15446) {
  DEF_ROMLOC(15446)
      : move_toreg_32(read_32(A0 + 0x8), &D3); // MOVE.L	8(A0),D3
  DEF_ROMLOC(1544A)
      : move_toreg_32(read_32(A0 + 0xC), &D2); // MOVE.L	12(A0),D2
  DEF_ROMLOC(1544E)
      : move_toreg_16(read_16(A0 + 0x10), &D1); // MOVE.W	16(A0),D1
  DEF_ROMLOC(15452) : ext_reg_32(&D1);          // EXT.L	D1
  DEF_ROMLOC(15454) : asl_toreg_32(0x8, &D1);   // ASL.L	#$08,D1
  DEF_ROMLOC(15456) : add_toreg_32(D1, &D3);    // ADD.L	D1,D3
  DEF_ROMLOC(15458)
      : move_toreg_16(read_16(A0 + 0x12), &D1);     // MOVE.W	18(A0),D1
  DEF_ROMLOC(1545C) : ext_reg_32(&D1);              // EXT.L	D1
  DEF_ROMLOC(1545E) : SWAPWORDS(0x8, &D1);          // ASL.L	#$08,D1
  DEF_ROMLOC(15460) : add_toreg_32(D1, &D2);        // ADD.L	D1,D2
  DEF_ROMLOC(15462) : SWAPWORDS(D2);                // SWAP.W	D2
  DEF_ROMLOC(15464) : SWAPWORDS(D3);                // SWAP.W	D3
  DEF_ROMLOC(15466) : move_tomem_8(D0, 0xFFFFF768); // MOVE.B	D0,$F768
  DEF_ROMLOC(1546A) : move_tomem_8(D0, 0xFFFFF76A); // MOVE.B	D0,$F76A
  DEF_ROMLOC(1546E) : move_toreg_8(D0, &D1);        // MOVE.B	D0,D1
  DEF_ROMLOC(15470) : add_toreg_8(0x20, &D0);       // ADDI.B	#$20,D0
  DEF_ROMLOC(15474) : if (CCR_PL) goto rom_15482;   // BPL.B	$15482
  DEF_ROMLOC(15476) : move_toreg_8(D1, &D0);        // MOVE.B	D1,D0
  DEF_ROMLOC(15478) : if (CCR_PL) goto rom_1547C;   // BPL.B	$1547C
  DEF_ROMLOC(1547A) : sub_toreg_8(0x1, &D0);        // SUBQ.B	#$01,D0
  DEF_ROMLOC(1547C) : add_toreg_8(0x20, &D0);       // ADDI.B	#$20,D0
  goto rom_1548C;                                   // BRA.B	$1548C
  DEF_ROMLOC(15482) : move_toreg_8(D1, &D0);        // MOVE.B	D1,D0
  DEF_ROMLOC(15484) : if (CCR_PL) goto rom_15488;   // BPL.B	$15488
  DEF_ROMLOC(15486) : add_toreg_8(0x1, &D0);        // ADDQ.B	#$01,D0
  DEF_ROMLOC(15488) : add_toreg_8(0x1F, &D0);       // ADDI.B	#$1F,D0
  DEF_ROMLOC(1548C) : and_toreg_8(0xFFFFFFC0, &D0); // ANDI.B	#$C0,D0
  DEF_ROMLOC(15490) : if (CCR_EQ) {
    rom_15558();
    return;
  }                                                 // BEQ.W	$15558
  DEF_ROMLOC(15494) : cmp_toreg_8(0xFFFFFF80, &D0); // CMPI.B	#$80,D0
  DEF_ROMLOC(15498) : if (CCR_EQ) {
    rom_156E4();
    return;
  }                                                // BEQ.W	$156E4
  DEF_ROMLOC(1549C) : and_toreg_8(0x38, &D1);      // ANDI.B	#$38,D1
  DEF_ROMLOC(154A0) : if (!CCR_EQ) goto rom_154A4; // BNE.B	$154A4
  DEF_ROMLOC(154A2) : add_toreg_16(0x8, &D2);      // ADDQ.W	#$08,D2
  DEF_ROMLOC(154A4) : cmp_toreg_8(0x40, &D0);      // CMPI.B	#$40,D0
  DEF_ROMLOC(154A8) : if (CCR_EQ) {
    rom_157B2();
    return;
  }            // BEQ.W	$157B2
  rom_15624(); // BRA.W	$15624
}
ROMFUNC(rom_154B0) {
  DEF_ROMLOC(154B0) : move_tomem_8(D0, 0xFFFFF768); // MOVE.B	D0,$F768
  DEF_ROMLOC(154B4) : move_tomem_8(D0, 0xFFFFF76A); // MOVE.B	D0,$F76A
  DEF_ROMLOC(154B8) : add_toreg_8(0x20, &D0);       // ADDI.B	#$20,D0
  DEF_ROMLOC(154BC) : and_toreg_8(0xFFFFFFC0, &D0); // ANDI.B	#$C0,D0
  DEF_ROMLOC(154C0) : cmp_toreg_8(0x40, &D0);       // CMPI.B	#$40,D0
  DEF_ROMLOC(154C4) : if (CCR_EQ) {
    rom_1573E();
    return;
  }                                                 // BEQ.W	$1573E
  DEF_ROMLOC(154C8) : cmp_toreg_8(0xFFFFFF80, &D0); // CMPI.B	#$80,D0
  DEF_ROMLOC(154CC) : if (CCR_EQ) {
    rom_15670();
    return;
  }                                                 // BEQ.W	$15670
  DEF_ROMLOC(154D0) : cmp_toreg_8(0xFFFFFFC0, &D0); // CMPI.B	#$C0,D0
  DEF_ROMLOC(154D4) : if (CCR_EQ) {
    rom_155B8();
    return;
  }            // BEQ.W	$155B8
  rom_154D8(); // Detected flow into next function
}
ROMFUNC(rom_154D8) {
  DEF_ROMLOC(154D8)
      : move_toreg_16(read_16(A0 + 0xC), &D2); // MOVE.W	12(A0),D2
  DEF_ROMLOC(154DC)
      : move_toreg_16(read_16(A0 + 0x8), &D3); // MOVE.W	8(A0),D3
  DEF_ROMLOC(154E0) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(154E2)
      : move_toreg_8(read_8(A0 + 0x16), &D0); // MOVE.B
                                              // 22(A0),D0
  DEF_ROMLOC(154E6) : ext_reg_16(&D0);        // EXT.W	D0
  DEF_ROMLOC(154E8) : add_toreg_16(D0, &D2);  // ADD.W	D0,D2
  DEF_ROMLOC(154EA)
      : move_toreg_8(read_8(A0 + 0x17), &D0);         // MOVE.B
                                                      // 23(A0),D0
  DEF_ROMLOC(154EE) : ext_reg_16(&D0);                // EXT.W	D0
  DEF_ROMLOC(154F0) : add_toreg_16(D0, &D3);          // ADD.W	D0,D3
  DEF_ROMLOC(154F2) : move_toreg_32(0xFFFFF768, &A4); // LEA.L	$F768,A4
  DEF_ROMLOC(154F6) : move_toreg_16(0x10, &A3);       // MOVEA.W	#$0010,A3
  DEF_ROMLOC(154FA) : move_toreg_16(0x0, &D6);        // MOVE.W	#$0000,D6
  DEF_ROMLOC(154FE) : move_toreg_32(0xD, &D5);        // MOVEQ.L	$0D,D5
  DEF_ROMLOC(15500) : rom_15136();                    // BSR.W	$15136
  DEF_ROMLOC(15504) : move_tomem_16(D1, A7 -= 2);     // MOVE.W	D1,-(A7)
  DEF_ROMLOC(15506)
      : move_toreg_16(read_16(A0 + 0xC), &D2); // MOVE.W	12(A0),D2
  DEF_ROMLOC(1550A)
      : move_toreg_16(read_16(A0 + 0x8), &D3); // MOVE.W	8(A0),D3
  DEF_ROMLOC(1550E) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(15510)
      : move_toreg_8(read_8(A0 + 0x16), &D0); // MOVE.B
                                              // 22(A0),D0
  DEF_ROMLOC(15514) : ext_reg_16(&D0);        // EXT.W	D0
  DEF_ROMLOC(15516) : add_toreg_16(D0, &D2);  // ADD.W	D0,D2
  DEF_ROMLOC(15518)
      : move_toreg_8(read_8(A0 + 0x17), &D0);         // MOVE.B
                                                      // 23(A0),D0
  DEF_ROMLOC(1551C) : ext_reg_16(&D0);                // EXT.W	D0
  DEF_ROMLOC(1551E) : sub_toreg_16(D0, &D3);          // SUB.W	D0,D3
  DEF_ROMLOC(15520) : move_toreg_32(0xFFFFF76A, &A4); // LEA.L	$F76A,A4
  DEF_ROMLOC(15524) : move_toreg_16(0x10, &A3);       // MOVEA.W	#$0010,A3
  DEF_ROMLOC(15528) : move_toreg_16(0x0, &D6);        // MOVE.W	#$0000,D6
  DEF_ROMLOC(1552C) : move_toreg_32(0xD, &D5);        // MOVEQ.L	$0D,D5
  DEF_ROMLOC(1552E) : rom_15136();                    // BSR.W	$15136
  DEF_ROMLOC(15532)
      : move_toreg_16(read_16((A7 += 2, A7 - 2)), &D0); // MOVE.W	(A7)+,D0
  DEF_ROMLOC(15534) : move_toreg_8(0x0, &D2);           // MOVE.B	#$00,D2
  rom_15538(); // Detected flow into next function
}