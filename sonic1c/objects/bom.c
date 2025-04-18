// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_120CA) {
  u8 switchindex = 0;
  DEF_ROMLOC(120CA) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(120CC) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(120D0)
      : move_toreg_16(read_16(0x120D8 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(120D4): goto rom_120D8 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(120D4) : switch (switchindex) {
  case 0:
    rom_120E0();
    break;
  case 1:
    rom_1211C();
    break;
  case 2:
    rom_12234();
    break;
  case 3:
    rom_122AC();
    break;
  }
}
ROMFUNC(rom_120E0) {
  DEF_ROMLOC(120E0) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(120E4)
      : move_tomem_32(0x122FC, A0 + 0x4);             // MOVE.L	#$000122FC,4(A0)
  DEF_ROMLOC(120EC) : move_tomem_16(0x400, A0 + 0x2); // MOVE.W	#$0400,2(A0)
  DEF_ROMLOC(120F2) : or_tomem_8(0x4, A0 + 0x1);      // ORI.B	#$04,1(A0)
  DEF_ROMLOC(120F8) : move_tomem_8(0x3, A0 + 0x18);   // MOVE.B	#$03,24(A0)
  DEF_ROMLOC(120FE) : move_tomem_8(0xC, A0 + 0x19);   // MOVE.B	#$0C,25(A0)
  DEF_ROMLOC(12104)
      : move_toreg_8(read_8(A0 + 0x28), &D0);      // MOVE.B	40(A0),D0
  DEF_ROMLOC(12108) : if (CCR_EQ) goto rom_12110;  // BEQ.B	$12110
  DEF_ROMLOC(1210A) : move_tomem_8(D0, A0 + 0x24); // MOVE.B	D0,36(A0)
  DEF_ROMLOC(1210E) : return;                      // RTS
  DEF_ROMLOC(12110)
      : move_tomem_8(0xFFFFFF9A, A0 + 0x20);        // MOVE.B	#$9A,32(A0)
  DEF_ROMLOC(12116) : bchg_tomem_8(0x0, A0 + 0x22); // BCHG.B	#$00,34(A0)
  rom_1211C(); // Detected flow into next function
}
ROMFUNC(rom_1213E);
ROMFUNC(rom_1216C);
ROMFUNC(rom_12192);
ROMFUNC(rom_1211C) {
  u8 switchindex = 0;
  DEF_ROMLOC(1211C) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(1211E) : move_toreg_8(read_8(A0 + 0x25), &D0);
  switchindex = D0 / 2; // MOVE.B	37(A0),D0
  DEF_ROMLOC(12122)
      : move_toreg_16(read_16(0x12138 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	20(PC,D0),D1
  // DEF_ROMLOC(12126): rom_12138 + (s16)(D1 & 0xffff)(); // JSR
  // 16(PC,D1)
  DEF_ROMLOC(12126) : switch (switchindex) {
  case 0:
    rom_1213E();
    break;
  case 1:
    rom_1216C();
    break;
  case 2:
    rom_12192();
    break;
  }
  DEF_ROMLOC(1212A) : move_toreg_32(0x122DC, &A1); // LEA.L	$000122DC,A1
  DEF_ROMLOC(12130) : animate_sprite();            // BSR.W	$ADA2
  DEF_ROMLOC(12134) : rom_FD38();
  return; // BRA.W	$FD38
}
ROMFUNC(rom_121A6);
ROMFUNC(rom_1213E) {
  DEF_ROMLOC(1213E) : rom_121A6();                  // BSR.W	$121A6
  DEF_ROMLOC(12142) : sub_tomem_16(0x1, A0 + 0x30); // SUBQ.W	#$01,48(A0)
  DEF_ROMLOC(12146) : if (CCR_PL) goto rom_1216A;   // BPL.B	$1216A
  DEF_ROMLOC(12148) : add_tomem_8(0x2, A0 + 0x25);  // ADDQ.B	#$02,37(A0)
  DEF_ROMLOC(1214C)
      : move_tomem_16(0x5FF, A0 + 0x30);              // MOVE.W
                                                      // #$05FF,48(A0)
  DEF_ROMLOC(12152) : move_tomem_16(0x10, A0 + 0x10); // MOVE.W	#$0010,16(A0)
  DEF_ROMLOC(12158) : move_tomem_8(0x1, A0 + 0x1C);   // MOVE.B	#$01,28(A0)
  DEF_ROMLOC(1215E) : bchg_tomem_8(0x0, A0 + 0x22);   // BCHG.B	#$00,34(A0)
  DEF_ROMLOC(12164) : if (CCR_EQ) goto rom_1216A;     // BEQ.B	$1216A
  DEF_ROMLOC(12166) : neg_mem_16(A0 + 0x10);          // NEG.W	16(A0)
  DEF_ROMLOC(1216A) : return;                         // RTS
}
ROMFUNC(rom_1216C) {
  DEF_ROMLOC(1216C) : rom_121A6();                    // BSR.W	$121A6
  DEF_ROMLOC(12170) : sub_tomem_16(0x1, A0 + 0x30);   // SUBQ.W	#$01,48(A0)
  DEF_ROMLOC(12174) : if (CCR_MI) goto rom_1217C;     // BMI.B	$1217C
  DEF_ROMLOC(12176) : rom_DC6C();                     // BSR.W	$DC6C
  DEF_ROMLOC(1217A) : return;                         // RTS
  DEF_ROMLOC(1217C) : sub_tomem_8(0x2, A0 + 0x25);    // SUBQ.B	#$02,37(A0)
  DEF_ROMLOC(12180) : move_tomem_16(0xB3, A0 + 0x30); // MOVE.W	#$00B3,48(A0)
  DEF_ROMLOC(12186) : clr_mem_16(A0 + 0x10);          // CLR.W	16(A0)
  DEF_ROMLOC(1218A) : move_tomem_8(0x0, A0 + 0x1C);   // MOVE.B	#$00,28(A0)
  DEF_ROMLOC(12190) : return;                         // RTS
}
ROMFUNC(rom_12192) {
  DEF_ROMLOC(12192) : sub_tomem_16(0x1, A0 + 0x30); // SUBQ.W	#$01,48(A0)
  DEF_ROMLOC(12196) : if (CCR_PL) goto rom_121A4;   // BPL.B	$121A4
  DEF_ROMLOC(12198)
      : move_tomem_8(OBJ_EXPLOSIONBOMB,
                     A0 + offsetof(object, id));    // MOVE.B	#$3F,0(A0)
  DEF_ROMLOC(1219E) : move_tomem_8(0x0, A0 + 0x24); // MOVE.B	#$00,36(A0)
  DEF_ROMLOC(121A4) : return;                       // RTS
}
ROMFUNC(rom_121A6) {
  DEF_ROMLOC(121A6)
      : move_toreg_16(read_16(0xFFFFD008), &D0); // MOVE.W	$D008,D0
  DEF_ROMLOC(121AA)
      : sub_toreg_16(read_16(A0 + 0x8), &D0);     // SUB.W	8(A0),D0
  DEF_ROMLOC(121AE) : if (CCR_CC) goto rom_121B2; // BCC.B	$121B2
  DEF_ROMLOC(121B0) : neg_reg_16(&D0);            // NEG.W	D0
  DEF_ROMLOC(121B2) : cmp_toreg_16(0x60, &D0);    // CMPI.W	#$0060,D0
  DEF_ROMLOC(121B6) : if (CCR_CC) goto rom_12232; // BCC.B	$12232
  DEF_ROMLOC(121B8)
      : move_toreg_16(read_16(0xFFFFD00C), &D0); // MOVE.W	$D00C,D0
  DEF_ROMLOC(121BC)
      : sub_toreg_16(read_16(A0 + 0xC), &D0);         // SUB.W
                                                      // 12(A0),D0
  DEF_ROMLOC(121C0) : if (CCR_CC) goto rom_121C4;     // BCC.B	$121C4
  DEF_ROMLOC(121C2) : neg_reg_16(&D0);                // NEG.W	D0
  DEF_ROMLOC(121C4) : cmp_toreg_16(0x60, &D0);        // CMPI.W	#$0060,D0
  DEF_ROMLOC(121C8) : if (CCR_CC) goto rom_12232;     // BCC.B	$12232
  DEF_ROMLOC(121CA) : tst_mem_16(v_debuguse);         // TST.W	$FE08
  DEF_ROMLOC(121CE) : if (!CCR_EQ) goto rom_12232;    // BNE.B	$12232
  DEF_ROMLOC(121D0) : move_tomem_8(0x4, A0 + 0x25);   // MOVE.B	#$04,37(A0)
  DEF_ROMLOC(121D6) : move_tomem_16(0x8F, A0 + 0x30); // MOVE.W	#$008F,48(A0)
  DEF_ROMLOC(121DC) : clr_mem_16(A0 + 0x10);          // CLR.W	16(A0)
  DEF_ROMLOC(121E0) : move_tomem_8(0x2, A0 + 0x1C);   // MOVE.B	#$02,28(A0)
  DEF_ROMLOC(121E6) : rom_E130();                     // BSR.W	$E130
  DEF_ROMLOC(121EA) : if (!CCR_EQ) goto rom_12232;    // BNE.B	$12232
  DEF_ROMLOC(121EC)
      : move_tomem_8(OBJ_BOMB,
                     A1 + offsetof(object, id)); // MOVE.B	#$5F,0(A1)
  DEF_ROMLOC(121F2)
      : move_tomem_16(read_16(A0 + 0x8), A1 + 0x8); // MOVE.W	8(A0),8(A1)
  DEF_ROMLOC(121F8)
      : move_tomem_16(read_16(A0 + 0xC), A1 + 0xC); // MOVE.W	12(A0),12(A1)
  DEF_ROMLOC(121FE)
      : move_tomem_16(read_16(A0 + 0xC), A1 + 0x34); // MOVE.W	12(A0),52(A1)
  DEF_ROMLOC(12204)
      : move_tomem_8(read_8(A0 + 0x22), A1 + 0x22);   // MOVE.B	34(A0),34(A1)
  DEF_ROMLOC(1220A) : move_tomem_8(0x4, A1 + 0x28);   // MOVE.B	#$04,40(A1)
  DEF_ROMLOC(12210) : move_tomem_8(0x3, A1 + 0x1C);   // MOVE.B	#$03,28(A1)
  DEF_ROMLOC(12216) : move_tomem_16(0x10, A1 + 0x12); // MOVE.W	#$0010,18(A1)
  DEF_ROMLOC(1221C) : btst_tomem_8(0x1, A0 + 0x22);   // BTST.B	#$01,34(A0)
  DEF_ROMLOC(12222) : if (CCR_EQ) goto rom_12228;     // BEQ.B	$12228
  DEF_ROMLOC(12224) : neg_mem_16(A1 + 0x12);          // NEG.W	18(A1)
  DEF_ROMLOC(12228) : move_tomem_16(0x8F, A1 + 0x30); // MOVE.W	#$008F,48(A1)
  DEF_ROMLOC(1222E) : move_tomem_32(A0, A1 + 0x3C);   // MOVE.L	A0,60(A1)
  DEF_ROMLOC(12232) : return;                         // RTS
}
ROMFUNC(rom_12234) {
  DEF_ROMLOC(12234) : rom_12244();                 // BSR.B	$12244
  DEF_ROMLOC(12236) : move_toreg_32(0x122DC, &A1); // LEA.L	$000122DC,A1
  DEF_ROMLOC(1223C) : animate_sprite();            // BSR.W	$ADA2
  rom_FD38();                                      // BRA.W	$FD38
}
ROMFUNC(rom_12244) {
  DEF_ROMLOC(12244) : sub_tomem_16(0x1, A0 + 0x30); // SUBQ.W	#$01,48(A0)
  DEF_ROMLOC(12248) : if (CCR_MI) goto rom_12250;   // BMI.B	$12250
  DEF_ROMLOC(1224A) : rom_DC6C();                   // BSR.W	$DC6C
  DEF_ROMLOC(1224E) : return;                       // RTS
  DEF_ROMLOC(12250) : clr_mem_16(A0 + 0x30);        // CLR.W	48(A0)
  DEF_ROMLOC(12254) : clr_mem_8(A0 + 0x24);         // CLR.B	36(A0)
  DEF_ROMLOC(12258)
      : move_tomem_16(read_16(A0 + 0x34), A0 + 0xC); // MOVE.W	52(A0),12(A0)
  DEF_ROMLOC(1225E) : move_toreg_32(0x3, &D1);       // MOVEQ.L	$03,D1
  DEF_ROMLOC(12260) : move_toreg_32(A0, &A1);        // MOVEA.L	A0,A1
  DEF_ROMLOC(12262) : move_toreg_32(0x122CC, &A2);   // LEA.L	$000122CC,A2
  DEF_ROMLOC(12268) : goto rom_12270;                // BRA.B	$12270
  DEF_ROMLOC(1226A) : rom_E130();                    // BSR.W	$E130
  DEF_ROMLOC(1226E) : if (!CCR_EQ) goto rom_122A2;   // BNE.B	$122A2
  DEF_ROMLOC(12270)
      : move_tomem_8(OBJ_BOMB,
                     A1 + offsetof(object, id)); // MOVE.B	#$5F,0(A1)
  DEF_ROMLOC(12276)
      : move_tomem_16(read_16(A0 + 0x8), A1 + 0x8); // MOVE.W	8(A0),8(A1)
  DEF_ROMLOC(1227C)
      : move_tomem_16(read_16(A0 + 0xC), A1 + 0xC); // MOVE.W	12(A0),12(A1)
  DEF_ROMLOC(12282) : move_tomem_8(0x6, A1 + 0x28); // MOVE.B	#$06,40(A1)
  DEF_ROMLOC(12288) : move_tomem_8(0x4, A1 + 0x1C); // MOVE.B	#$04,28(A1)
  DEF_ROMLOC(1228E)
      : move_tomem_16(read_16((A2 += 2, A2 - 2)),
                      A1 + 0x10); // MOVE.W	(A2)+,16(A1)
  DEF_ROMLOC(12292)
      : move_tomem_16(read_16((A2 += 2, A2 - 2)),
                      A1 + 0x12); // MOVE.W	(A2)+,18(A1)
  DEF_ROMLOC(12296)
      : move_tomem_8(0xFFFFFF98, A1 + 0x20);       // MOVE.B	#$98,32(A1)
  DEF_ROMLOC(1229C) : bset_tomem_8(0x7, A1 + 0x1); // BSET.B	#$07,1(A1)
  DEF_ROMLOC(122A2) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_1226A;                                 // DBF.W	D1,$1226A
  DEF_ROMLOC(122A6) : move_tomem_8(0x6, A0 + 0x24); // MOVE.B	#$06,36(A0)
  rom_122AC(); // Detected flow into next function
}
ROMFUNC(rom_122AC) {
  DEF_ROMLOC(122AC) : rom_DC6C();                    // BSR.W	$DC6C
  DEF_ROMLOC(122B0) : add_tomem_16(0x18, A0 + 0x12); // ADDI.W	#$0018,18(A0)
  DEF_ROMLOC(122B6) : move_toreg_32(0x122DC, &A1);   // LEA.L	$000122DC,A1
  DEF_ROMLOC(122BC) : animate_sprite();              // BSR.W	$ADA2
  DEF_ROMLOC(122C0) : tst_mem_8(A0 + 0x1);           // TST.B	1(A0)
  DEF_ROMLOC(122C4) : if (CCR_PL) {
    rom_DCCE();
    return;
  } // BPL.W	$DCCE
  queue_sprite(); // BRA.W	$DC92
}