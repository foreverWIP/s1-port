// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_B32E) {
  u8 switchindex = 0;
  DEF_ROMLOC(B32E) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(B330) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(B334)
      : move_toreg_16(read_16(0xB33C + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(B338): goto rom_B33C + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(B338) : switch (switchindex) {
  case 0:
    rom_B340();
    break;
  case 1:
    rom_B380();
    break;
  }
}
ROMFUNC(rom_B340) {
  DEF_ROMLOC(B340) : add_tomem_8(0x2, A0 + 0x24);   // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(B344) : move_tomem_8(0x13, A0 + 0x16); // MOVE.B	#$13,22(A0)
  DEF_ROMLOC(B34A) : move_tomem_8(0x8, A0 + 0x17);  // MOVE.B	#$08,23(A0)
  DEF_ROMLOC(B350)
      : move_tomem_32(0xB4E6, A0 + 0x4);             // MOVE.L	#$0000B4E6,4(A0)
  DEF_ROMLOC(B358) : move_tomem_16(0x4A6, A0 + 0x2); // MOVE.W	#$04A6,2(A0)
  DEF_ROMLOC(B35E) : or_tomem_8(0x4, A0 + 0x1);      // ORI.B	#$04,1(A0)
  DEF_ROMLOC(B364) : move_tomem_8(0x4, A0 + 0x18);   // MOVE.B	#$04,24(A0)
  DEF_ROMLOC(B36A) : move_tomem_8(0x5, A0 + 0x20);   // MOVE.B	#$05,32(A0)
  DEF_ROMLOC(B370) : move_tomem_8(0xC, A0 + 0x19);   // MOVE.B	#$0C,25(A0)
  DEF_ROMLOC(B376) : add_tomem_8(0x6, A0 + 0x25);    // ADDQ.B	#$06,37(A0)
  DEF_ROMLOC(B37A) : move_tomem_8(0x2, A0 + 0x1C);   // MOVE.B	#$02,28(A0)
  rom_B380(); // Detected flow into next function
}
ROMFUNC(rom_B3A4);
ROMFUNC(rom_B380) {
  u8 switchindex = 0;
  DEF_ROMLOC(B380) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(B382) : move_toreg_8(read_8(A0 + 0x25), &D0);
  switchindex = D0 / 2; // MOVE.B	37(A0),D0
  DEF_ROMLOC(B386)
      : move_toreg_16(read_16(0xB39C + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	20(PC,D0),D1
  // DEF_ROMLOC(B38A): rom_B39C + (s16)(D1 & 0xffff)(); // JSR	16(PC,D1)
  DEF_ROMLOC(B38A) : switch (switchindex) {
  case 0:
    rom_B3A4();
    break;
  case 1:
    rom_B3CE();
    break;
  case 2:
    rom_B440();
    break;
  case 3:
    rom_B47C();
    break;
  }
  DEF_ROMLOC(B38E) : move_toreg_32(0xB4CE, &A1); // LEA.L	$0000B4CE,A1
  DEF_ROMLOC(B394) : animate_sprite();           // BSR.W	$ADA2
  rom_FD38();                                    // BRA.W	$FD38
}
ROMFUNC(rom_B3A4) {
  DEF_ROMLOC(B3A4) : sub_tomem_16(0x1, A0 + 0x30);   // SUBQ.W	#$01,48(A0)
  DEF_ROMLOC(B3A8) : if (CCR_PL) goto rom_B3CC;      // BPL.B	$B3CC
  DEF_ROMLOC(B3AA) : add_tomem_8(0x2, A0 + 0x25);    // ADDQ.B	#$02,37(A0)
  DEF_ROMLOC(B3AE) : move_tomem_16(0xFF, A0 + 0x30); // MOVE.W	#$00FF,48(A0)
  DEF_ROMLOC(B3B4) : move_tomem_16(0x80, A0 + 0x10); // MOVE.W	#$0080,16(A0)
  DEF_ROMLOC(B3BA) : move_tomem_8(0x1, A0 + 0x1C);   // MOVE.B	#$01,28(A0)
  DEF_ROMLOC(B3C0) : bchg_tomem_8(0x0, A0 + 0x22);   // BCHG.B	#$00,34(A0)
  DEF_ROMLOC(B3C6) : if (CCR_EQ) goto rom_B3CC;      // BEQ.B	$B3CC
  DEF_ROMLOC(B3C8) : neg_mem_16(A0 + 0x10);          // NEG.W	16(A0)
  DEF_ROMLOC(B3CC) : return;                         // RTS
}
ROMFUNC(rom_B3CE) {
  DEF_ROMLOC(B3CE) : sub_tomem_16(0x1, A0 + 0x30); // SUBQ.W	#$01,48(A0)
  DEF_ROMLOC(B3D2) : if (CCR_MI) goto rom_B40E;    // BMI.B	$B40E
  DEF_ROMLOC(B3D4) : rom_DC6C();                   // BSR.W	$DC6C
  DEF_ROMLOC(B3D8) : bchg_tomem_8(0x0, A0 + 0x32); // BCHG.B	#$00,50(A0)
  DEF_ROMLOC(B3DE) : if (!CCR_EQ) goto rom_B402;   // BNE.B	$B402
  DEF_ROMLOC(B3E0) : move_toreg_16(read_16(A0 + 0x8), &D3); // MOVE.W	8(A0),D3
  DEF_ROMLOC(B3E4) : add_toreg_16(0xC, &D3);                // ADDI.W	#$000C,D3
  DEF_ROMLOC(B3E8) : btst_tomem_8(0x0, A0 + 0x22);   // BTST.B	#$00,34(A0)
  DEF_ROMLOC(B3EE) : if (!CCR_EQ) goto rom_B3F4;     // BNE.B	$B3F4
  DEF_ROMLOC(B3F0) : sub_toreg_16(0x18, &D3);        // SUBI.W	#$0018,D3
  DEF_ROMLOC(B3F4) : rom_15584();                    // JSR	$00015584
  DEF_ROMLOC(B3FA) : cmp_toreg_16(0xC, &D1);         // CMPI.W	#$000C,D1
  DEF_ROMLOC(B3FE) : if (CCR_GE) goto rom_B40E;      // BGE.B	$B40E
  DEF_ROMLOC(B400) : return;                         // RTS
  DEF_ROMLOC(B402) : rom_15580();                    // JSR	$00015580
  DEF_ROMLOC(B408) : add_tomem_16(D1, A0 + 0xC);     // ADD.W	D1,12(A0)
  DEF_ROMLOC(B40C) : return;                         // RTS
  DEF_ROMLOC(B40E) : btst_tomem_8(0x2, 0xFFFFFE0F);  // BTST.B	#$02,$FE0F
  DEF_ROMLOC(B414) : if (CCR_EQ) goto rom_B42E;      // BEQ.B	$B42E
  DEF_ROMLOC(B416) : sub_tomem_8(0x2, A0 + 0x25);    // SUBQ.B	#$02,37(A0)
  DEF_ROMLOC(B41A) : move_tomem_16(0x3B, A0 + 0x30); // MOVE.W	#$003B,48(A0)
  DEF_ROMLOC(B420) : move_tomem_16(0x0, A0 + 0x10);  // MOVE.W	#$0000,16(A0)
  DEF_ROMLOC(B426) : move_tomem_8(0x0, A0 + 0x1C);   // MOVE.B	#$00,28(A0)
  DEF_ROMLOC(B42C) : return;                         // RTS
  DEF_ROMLOC(B42E) : add_tomem_8(0x2, A0 + 0x25);    // ADDQ.B	#$02,37(A0)
  DEF_ROMLOC(B432)
      : move_tomem_16(0xFFFFFC00, A0 + 0x12);      // MOVE.W	#$FC00,18(A0)
  DEF_ROMLOC(B438) : move_tomem_8(0x2, A0 + 0x1C); // MOVE.B	#$02,28(A0)
  DEF_ROMLOC(B43E) : return;                       // RTS
}
ROMFUNC(rom_B440) {
  DEF_ROMLOC(B440) : rom_DC6C();                     // BSR.W	$DC6C
  DEF_ROMLOC(B444) : add_tomem_16(0x18, A0 + 0x12);  // ADDI.W	#$0018,18(A0)
  DEF_ROMLOC(B44A) : if (CCR_MI) goto rom_B47A;      // BMI.B	$B47A
  DEF_ROMLOC(B44C) : move_tomem_8(0x3, A0 + 0x1C);   // MOVE.B	#$03,28(A0)
  DEF_ROMLOC(B452) : rom_15580();                    // JSR	$00015580
  DEF_ROMLOC(B458) : tst_reg_16(&D1);                // TST.W	D1
  DEF_ROMLOC(B45A) : if (CCR_PL) goto rom_B47A;      // BPL.B	$B47A
  DEF_ROMLOC(B45C) : add_tomem_16(D1, A0 + 0xC);     // ADD.W	D1,12(A0)
  DEF_ROMLOC(B460) : move_tomem_16(0x0, A0 + 0x12);  // MOVE.W	#$0000,18(A0)
  DEF_ROMLOC(B466) : move_tomem_8(0x1, A0 + 0x1C);   // MOVE.B	#$01,28(A0)
  DEF_ROMLOC(B46C) : move_tomem_16(0xFF, A0 + 0x30); // MOVE.W	#$00FF,48(A0)
  DEF_ROMLOC(B472) : sub_tomem_8(0x2, A0 + 0x25);    // SUBQ.B	#$02,37(A0)
  DEF_ROMLOC(B476) : rom_B4AC();                     // BSR.W	$B4AC
  DEF_ROMLOC(B47A) : return;                         // RTS
}
ROMFUNC(rom_B47C) {
  DEF_ROMLOC(B47C) : move_toreg_16(0x60, &D2);  // MOVE.W	#$0060,D2
  DEF_ROMLOC(B480) : rom_B4AC();                // BSR.W	$B4AC
  DEF_ROMLOC(B484) : if (CCR_CC) goto rom_B4AA; // BCC.B	$B4AA
  DEF_ROMLOC(B486)
      : move_toreg_16(read_16(0xFFFFD00C), &D0);           // MOVE.W	$D00C,D0
  DEF_ROMLOC(B48A) : sub_toreg_16(read_16(A0 + 0xC), &D0); // SUB.W
                                                           // 12(A0),D0
  DEF_ROMLOC(B48E) : if (CCR_CC) goto rom_B4AA;            // BCC.B	$B4AA
  DEF_ROMLOC(B490) : cmp_toreg_16(0xFFFFFF80, &D0);        // CMPI.W	#$FF80,D0
  DEF_ROMLOC(B494) : if (CCR_CS) goto rom_B4AA;            // BCS.B	$B4AA
  DEF_ROMLOC(B496) : tst_mem_16(v_debuguse);               // TST.W	$FE08
  DEF_ROMLOC(B49A) : if (!CCR_EQ) goto rom_B4AA;           // BNE.B	$B4AA
  DEF_ROMLOC(B49C) : sub_tomem_8(0x2, A0 + 0x25);          // SUBQ.B	#$02,37(A0)
  DEF_ROMLOC(B4A0) : move_tomem_16(D1, A0 + 0x10);         // MOVE.W	D1,16(A0)
  DEF_ROMLOC(B4A4)
      : move_tomem_16(0xFFFFFC00, A0 + 0x12); // MOVE.W	#$FC00,18(A0)
  DEF_ROMLOC(B4AA) : return;                  // RTS
}
ROMFUNC(rom_B4AC) {
  DEF_ROMLOC(B4AC) : move_toreg_16(0x80, &D1);     // MOVE.W	#$0080,D1
  DEF_ROMLOC(B4B0) : bset_tomem_8(0x0, A0 + 0x22); // BSET.B	#$00,34(A0)
  DEF_ROMLOC(B4B6)
      : move_toreg_16(read_16(0xFFFFD008), &D0);           // MOVE.W	$D008,D0
  DEF_ROMLOC(B4BA) : sub_toreg_16(read_16(A0 + 0x8), &D0); // SUB.W	8(A0),D0
  DEF_ROMLOC(B4BE) : if (CCR_CC) goto rom_B4CA;            // BCC.B	$B4CA
  DEF_ROMLOC(B4C0) : neg_reg_16(&D0);                      // NEG.W	D0
  DEF_ROMLOC(B4C2) : neg_reg_16(&D1);                      // NEG.W	D1
  DEF_ROMLOC(B4C4) : bclr_tomem_8(0x0, A0 + 0x22);         // BCLR.B	#$00,34(A0)
  DEF_ROMLOC(B4CA) : cmp_toreg_16(D2, &D0);                // CMP.W	D2,D0
  DEF_ROMLOC(B4CC) : return;                               // RTS
}