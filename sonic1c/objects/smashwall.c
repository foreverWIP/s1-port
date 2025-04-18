// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_D7AA) {
  u8 switchindex = 0;
  DEF_ROMLOC(D7AA) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(D7AC) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(D7B0)
      : move_toreg_16(read_16(0xD7BC + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	10(PC,D0),D1
  // DEF_ROMLOC(D7B4): rom_D7BC + (s16)(D1 & 0xffff)(); // JSR	6(PC,D1)
  DEF_ROMLOC(D7B4) : switch (switchindex) {
  case 0:
    rom_D7C2();
    break;
  case 1:
    rom_D7EC();
    break;
  case 2:
    rom_D864();
    break;
  }
  DEF_ROMLOC(D7B8) : {
    rom_FD38();
    return;
  } // BRA.W	$FD38
}
ROMFUNC(rom_D7C2) {
  DEF_ROMLOC(D7C2) : add_tomem_8(0x2, A0 + 0x24);     // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(D7C6) : move_tomem_32(0xD944, A0 + 0x4); // MOVE.L	#$0000D944,4(A0)
  DEF_ROMLOC(D7CE) : move_tomem_16(0x450F, A0 + 0x2); // MOVE.W	#$450F,2(A0)
  DEF_ROMLOC(D7D4) : move_tomem_8(0x4, A0 + 0x1);     // MOVE.B	#$04,1(A0)
  DEF_ROMLOC(D7DA) : move_tomem_8(0x10, A0 + 0x19);   // MOVE.B	#$10,25(A0)
  DEF_ROMLOC(D7E0) : move_tomem_8(0x4, A0 + 0x18);    // MOVE.B	#$04,24(A0)
  DEF_ROMLOC(D7E6)
      : move_tomem_8(read_8(A0 + 0x28), A0 + 0x1A); // MOVE.B	40(A0),26(A0)
  rom_D7EC(); // Detected flow into next function
}
ROMFUNC(rom_D7EC) {
  DEF_ROMLOC(D7EC)
      : move_tomem_16(read_16(0xFFFFD010),
                      A0 + 0x30);              // MOVE.W	$D010,48(A0)
  DEF_ROMLOC(D7F2) : move_toreg_16(0x1B, &D1); // MOVE.W	#$001B,D1
  DEF_ROMLOC(D7F6) : move_toreg_16(0x20, &D2); // MOVE.W	#$0020,D2
  DEF_ROMLOC(D7FA) : move_toreg_16(0x20, &D3); // MOVE.W	#$0020,D3
  DEF_ROMLOC(D7FE)
      : move_toreg_16(read_16(A0 + 0x8), &D4);     // MOVE.W	8(A0),D4
  DEF_ROMLOC(D802) : rom_10062();                  // BSR.W	$10062
  DEF_ROMLOC(D806) : btst_tomem_8(0x5, A0 + 0x22); // BTST.B	#$05,34(A0)
  DEF_ROMLOC(D80C) : if (!CCR_EQ) goto rom_D810;   // BNE.B	$D810
  DEF_ROMLOC(D80E) : return;                       // RTS
  DEF_ROMLOC(D810) : cmp_tomem_8(0x2, A1 + 0x1C);  // CMPI.B	#$02,28(A1)
  DEF_ROMLOC(D816) : if (!CCR_EQ) goto rom_D80E;   // BNE.B	$D80E
  DEF_ROMLOC(D818)
      : move_toreg_16(read_16(A0 + 0x30), &D0); // MOVE.W	48(A0),D0
  DEF_ROMLOC(D81C) : if (CCR_PL) goto rom_D820; // BPL.B	$D820
  DEF_ROMLOC(D81E) : neg_reg_16(&D0);           // NEG.W	D0
  DEF_ROMLOC(D820) : cmp_toreg_16(0x480, &D0);  // CMPI.W	#$0480,D0
  DEF_ROMLOC(D824) : if (CCR_CS) goto rom_D80E; // BCS.B	$D80E
  DEF_ROMLOC(D826)
      : move_tomem_16(read_16(A0 + 0x30), A1 + 0x10); // MOVE.W	48(A0),16(A1)
  DEF_ROMLOC(D82C) : add_tomem_16(0x4, A1 + 0x8);     // ADDQ.W	#$04,8(A1)
  DEF_ROMLOC(D830) : move_toreg_32(0xD904, &A4);      // LEA.L	$0000D904,A4
  DEF_ROMLOC(D836)
      : move_toreg_16(read_16(A0 + 0x8), &D0); // MOVE.W	8(A0),D0
  DEF_ROMLOC(D83A)
      : cmp_toreg_16(read_16(A1 + 0x8), &D0);     // CMP.W	8(A1),D0
  DEF_ROMLOC(D83E) : if (CCR_CS) goto rom_D84A;   // BCS.B	$D84A
  DEF_ROMLOC(D840) : sub_tomem_16(0x8, A1 + 0x8); // SUBQ.W	#$08,8(A1)
  DEF_ROMLOC(D844) : move_toreg_32(0xD924, &A4);  // LEA.L	$0000D924,A4
  DEF_ROMLOC(D84A)
      : move_tomem_16(read_16(A1 + 0x10), A1 + 0x14); // MOVE.W	16(A1),20(A1)
  DEF_ROMLOC(D850) : bclr_tomem_8(0x5, A0 + 0x22);    // BCLR.B	#$05,34(A0)
  DEF_ROMLOC(D856) : bclr_tomem_8(0x5, A1 + 0x22);    // BCLR.B	#$05,34(A1)
  DEF_ROMLOC(D85C) : move_toreg_32(0x7, &D1);         // MOVEQ.L	$07,D1
  DEF_ROMLOC(D85E) : move_toreg_16(0x70, &D2);        // MOVE.W	#$0070,D2
  DEF_ROMLOC(D862) : rom_D87C();                      // BSR.B	$D87C
  rom_D864(); // Detected flow into next function
}
ROMFUNC(rom_D864) {
  DEF_ROMLOC(D864) : rom_DC6C();                    // BSR.W	$DC6C
  DEF_ROMLOC(D868) : add_tomem_16(0x70, A0 + 0x12); // ADDI.W	#$0070,18(A0)
  DEF_ROMLOC(D86E) : queue_sprite();                // BSR.W	$DC92
  DEF_ROMLOC(D872) : tst_mem_8(A0 + 0x1);           // TST.B	1(A0)
  DEF_ROMLOC(D876) : if (CCR_PL) {
    rom_DCCE();
    return;
  } // BPL.W	$DCCE
  DEF_ROMLOC(D87A) : return; // RTS
}