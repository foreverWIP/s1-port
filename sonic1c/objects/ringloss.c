// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_A334) {
  u8 switchindex = 0;
  DEF_ROMLOC(A334) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(A336) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(A33A)
      : move_toreg_16(read_16(0xA342 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(A33E): goto rom_A342 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(A33E) : switch (switchindex) {
  case 0:
    rom_A34C();
    break;
  case 1:
    rom_A40C();
    break;
  case 2:
    rom_A45E();
    break;
  case 3:
    rom_A472();
    break;
  case 4:
    rom_A480();
    break;
  }
}
ROMFUNC(rom_A34C) {
  DEF_ROMLOC(A34C) : move_toreg_32(A0, &A1);  // MOVEA.L	A0,A1
  DEF_ROMLOC(A34E) : move_toreg_32(0x0, &D5); // MOVEQ.L	$00,D5
  DEF_ROMLOC(A350)
      : move_toreg_16(read_16(0xFFFFFE20), &D5);   // MOVE.W	$FE20,D5
  DEF_ROMLOC(A354) : move_toreg_32(0x20, &D0);     // MOVEQ.L	$20,D0
  DEF_ROMLOC(A356) : cmp_toreg_16(D0, &D5);        // CMP.W	D0,D5
  DEF_ROMLOC(A358) : if (CCR_CS) goto rom_A35C;    // BCS.B	$A35C
  DEF_ROMLOC(A35A) : move_toreg_16(D0, &D5);       // MOVE.W	D0,D5
  DEF_ROMLOC(A35C) : sub_toreg_16(0x1, &D5);       // SUBQ.W	#$01,D5
  DEF_ROMLOC(A35E) : move_toreg_16(0x288, &D4);    // MOVE.W	#$0288,D4
  DEF_ROMLOC(A362) : goto rom_A36C;                // BRA.B	$A36C
  DEF_ROMLOC(A364) : rom_E11A();                   // BSR.W	$E11A
  DEF_ROMLOC(A368) : if (!CCR_EQ) goto rom_A3F0;   // BNE.W	$A3F0
  DEF_ROMLOC(A36C) : move_tomem_8(0x37, A1 + 0x0); // MOVE.B	#$37,0(A1)
  DEF_ROMLOC(A372) : add_tomem_8(0x2, A1 + 0x24);  // ADDQ.B	#$02,36(A1)
  DEF_ROMLOC(A376) : move_tomem_8(0x8, A1 + 0x16); // MOVE.B	#$08,22(A1)
  DEF_ROMLOC(A37C) : move_tomem_8(0x8, A1 + 0x17); // MOVE.B	#$08,23(A1)
  DEF_ROMLOC(A382)
      : move_tomem_16(read_16(A0 + 0x8), A1 + 0x8); // MOVE.W	8(A0),8(A1)
  DEF_ROMLOC(A388)
      : move_tomem_16(read_16(A0 + 0xC), A1 + 0xC);   // MOVE.W	12(A0),12(A1)
  DEF_ROMLOC(A38E) : move_tomem_32(0xA610, A1 + 0x4); // MOVE.L	#$0000A610,4(A1)
  DEF_ROMLOC(A396) : move_tomem_16(0x27B2, A1 + 0x2); // MOVE.W	#$27B2,2(A1)
  DEF_ROMLOC(A39C) : move_tomem_8(0x4, A1 + 0x1);     // MOVE.B	#$04,1(A1)
  DEF_ROMLOC(A3A2) : move_tomem_8(0x3, A1 + 0x18);    // MOVE.B	#$03,24(A1)
  DEF_ROMLOC(A3A8) : move_tomem_8(0x47, A1 + 0x20);   // MOVE.B	#$47,32(A1)
  DEF_ROMLOC(A3AE) : move_tomem_8(0x8, A1 + 0x19);    // MOVE.B	#$08,25(A1)
  DEF_ROMLOC(A3B4)
      : move_tomem_8(0xFFFFFFFF, 0xFFFFFEC6);      // MOVE.B	#$FF,$FEC6
  DEF_ROMLOC(A3BA) : tst_reg_16(&D4);              // TST.W	D4
  DEF_ROMLOC(A3BC) : if (CCR_MI) goto rom_A3E0;    // BMI.B	$A3E0
  DEF_ROMLOC(A3BE) : move_toreg_16(D4, &D0);       // MOVE.W	D4,D0
  DEF_ROMLOC(A3C0) : rom_29D2();                   // BSR.W	$29D2
  DEF_ROMLOC(A3C4) : move_toreg_16(D4, &D2);       // MOVE.W	D4,D2
  DEF_ROMLOC(A3C6) : lsr_toreg_16(0x8, &D2);       // LSR.W	#$08,D2
  DEF_ROMLOC(A3C8) : asl_toreg_16(D2, &D0);        // ASL.W	D2,D0
  DEF_ROMLOC(A3CA) : asl_toreg_16(D2, &D1);        // ASL.W	D2,D1
  DEF_ROMLOC(A3CC) : move_toreg_16(D0, &D2);       // MOVE.W	D0,D2
  DEF_ROMLOC(A3CE) : move_toreg_16(D1, &D3);       // MOVE.W	D1,D3
  DEF_ROMLOC(A3D0) : add_toreg_8(0x10, &D4);       // ADDI.B	#$10,D4
  DEF_ROMLOC(A3D4) : if (CCR_CC) goto rom_A3E0;    // BCC.B	$A3E0
  DEF_ROMLOC(A3D6) : sub_toreg_16(0x80, &D4);      // SUBI.W	#$0080,D4
  DEF_ROMLOC(A3DA) : if (CCR_CC) goto rom_A3E0;    // BCC.B	$A3E0
  DEF_ROMLOC(A3DC) : move_toreg_16(0x288, &D4);    // MOVE.W	#$0288,D4
  DEF_ROMLOC(A3E0) : move_tomem_16(D2, A1 + 0x10); // MOVE.W	D2,16(A1)
  DEF_ROMLOC(A3E4) : move_tomem_16(D3, A1 + 0x12); // MOVE.W	D3,18(A1)
  DEF_ROMLOC(A3E8) : neg_reg_16(&D2);              // NEG.W	D2
  DEF_ROMLOC(A3EA) : neg_reg_16(&D4);              // NEG.W	D4
  DEF_ROMLOC(A3EC) : dec_reg_16(&D5);
  if ((D5 & 0xffff) != 0xffff)
    goto rom_A364;                                   // DBF.W	D5,$A364
  DEF_ROMLOC(A3F0) : move_tomem_16(0x0, 0xFFFFFE20); // MOVE.W	#$0000,$FE20
  DEF_ROMLOC(A3F6)
      : move_tomem_8(0xFFFFFF80, 0xFFFFFE1D);       // MOVE.B	#$80,$FE1D
  DEF_ROMLOC(A3FC) : move_tomem_8(0x0, 0xFFFFFE1B); // MOVE.B	#$00,$FE1B
  DEF_ROMLOC(A402) : move_toreg_16(0xC6, &D0);      // MOVE.W	#$00C6,D0
  DEF_ROMLOC(A406) : play_sound_special();          // JSR	$00001394
  rom_A40C(); // Detected flow into next function
}
ROMFUNC(rom_A40C) {
  DEF_ROMLOC(A40C)
      : move_tomem_8(read_8(0xFFFFFEC7), A0 + 0x1A); // MOVE.B	$FEC7,26(A0)
  DEF_ROMLOC(A412) : rom_DC6C();                     // BSR.W	$DC6C
  DEF_ROMLOC(A416) : add_tomem_16(0x18, A0 + 0x12);  // ADDI.W	#$0018,18(A0)
  DEF_ROMLOC(A41C) : if (CCR_MI) goto rom_A446;      // BMI.B	$A446
  DEF_ROMLOC(A41E)
      : move_toreg_8(read_8(0xFFFFFE0F), &D0);   // MOVE.B	$FE0F,D0
  DEF_ROMLOC(A422) : add_toreg_8(D7, &D0);       // ADD.B	D7,D0
  DEF_ROMLOC(A424) : and_toreg_8(0x3, &D0);      // ANDI.B	#$03,D0
  DEF_ROMLOC(A428) : if (!CCR_EQ) goto rom_A446; // BNE.B	$A446
  DEF_ROMLOC(A42A) : rom_15580();                // JSR	$00015580
  DEF_ROMLOC(A430) : tst_reg_16(&D1);            // TST.W	D1
  DEF_ROMLOC(A432) : if (CCR_PL) goto rom_A446;  // BPL.B	$A446
  DEF_ROMLOC(A434) : add_tomem_16(D1, A0 + 0xC); // ADD.W	D1,12(A0)
  DEF_ROMLOC(A438)
      : move_toreg_16(read_16(A0 + 0x12), &D0);   // MOVE.W	18(A0),D0
  DEF_ROMLOC(A43C) : asr_toreg_16(0x2, &D0);      // ASR.W	#$02,D0
  DEF_ROMLOC(A43E) : sub_tomem_16(D0, A0 + 0x12); // SUB.W	D0,18(A0)
  DEF_ROMLOC(A442) : neg_mem_16(A0 + 0x12);       // NEG.W	18(A0)
  DEF_ROMLOC(A446) : tst_mem_8(0xFFFFFEC6);       // TST.B	$FEC6
  DEF_ROMLOC(A44A) : if (CCR_EQ) {
    rom_A480();
    return;
  } // BEQ.B	$A480
  DEF_ROMLOC(A44C)
      : move_toreg_16(read_16(0xFFFFF72E), &D0);           // MOVE.W	$F72E,D0
  DEF_ROMLOC(A450) : add_toreg_16(0xE0, &D0);              // ADDI.W	#$00E0,D0
  DEF_ROMLOC(A454) : cmp_toreg_16(read_16(A0 + 0xC), &D0); // CMP.W
                                                           // 12(A0),D0
  DEF_ROMLOC(A458) : if (CCR_CS) {
    rom_A480();
    return;
  }           // BCS.B	$A480
  rom_DC92(); // BRA.W	$DC92
}
ROMFUNC(rom_A45E) {
  DEF_ROMLOC(A45E) : add_tomem_8(0x2, A0 + 0x24);  // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(A462) : move_tomem_8(0x0, A0 + 0x20); // MOVE.B	#$00,32(A0)
  DEF_ROMLOC(A468) : move_tomem_8(0x1, A0 + 0x18); // MOVE.B	#$01,24(A0)
  DEF_ROMLOC(A46E) : rom_A2F4();                   // BSR.W	$A2F4
  rom_A472(); // Detected flow into next function
}
ROMFUNC(rom_A472) {
  DEF_ROMLOC(A472) : move_toreg_32(0xA608, &A1); // LEA.L	$0000A608,A1
  DEF_ROMLOC(A478) : animate_sprite();                 // BSR.W	$ADA2
  rom_DC92();                                    // BRA.W	$DC92
}
ROMFUNC(rom_A480) {
  rom_DCCE(); // BRA.W	$DCCE
}