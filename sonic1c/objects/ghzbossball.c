// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_18290) {
  u8 switchindex = 0;
  DEF_ROMLOC(18290) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(18292) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(18296)
      : move_toreg_16(read_16(0x1829E + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(1829A): goto rom_1829E + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(1829A) : switch (switchindex) {
  case 0:
    rom_182A8();
    break;
  case 1:
    rom_18364();
    break;
  case 2:
    rom_183C6();
    break;
  case 3:
    rom_18414();
    break;
  case 4:
    rom_18430();
    break;
  }
}
ROMFUNC(rom_182A8) {
  DEF_ROMLOC(182A8) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(182AC)
      : move_tomem_16(0x4080, A0 + 0x26); // MOVE.W
                                          // #$4080,38(A0)
  DEF_ROMLOC(182B2)
      : move_tomem_16(0xFFFFFE00, A0 + 0x3E); // MOVE.W	#$FE00,62(A0)
  DEF_ROMLOC(182B8)
      : move_tomem_32(0x18580, A0 + 0x4);             // MOVE.L	#$00018580,4(A0)
  DEF_ROMLOC(182C0) : move_tomem_16(0x46C, A0 + 0x2); // MOVE.W	#$046C,2(A0)
  DEF_ROMLOC(182C6) : move_toreg_32(A0 + 0x28, &A2);  // LEA.L	40(A0),A2
  DEF_ROMLOC(182CA) : move_tomem_8(0x0, A2++);        // MOVE.B	#$00,(A2)+
  DEF_ROMLOC(182CE) : move_toreg_32(0x5, &D1);        // MOVEQ.L	$05,D1
  DEF_ROMLOC(182D0) : move_toreg_32(A0, &A1);         // MOVEA.L	A0,A1
  goto rom_1830C;                                     // BRA.B	$1830C
  DEF_ROMLOC(182D4) : rom_E130();                     // JSR	$0000E130
  DEF_ROMLOC(182DA) : if (!CCR_EQ) goto rom_18336;    // BNE.B	$18336
  DEF_ROMLOC(182DC)
      : move_tomem_16(read_16(A0 + 0x8), A1 + 0x8); // MOVE.W	8(A0),8(A1)
  DEF_ROMLOC(182E2)
      : move_tomem_16(read_16(A0 + 0xC), A1 + 0xC); // MOVE.W	12(A0),12(A1)
  DEF_ROMLOC(182E8)
      : move_tomem_8(OBJ_BOSSBALL,
                     A1 + offsetof(object, id));    // MOVE.B	#$48,0(A1)
  DEF_ROMLOC(182EE) : move_tomem_8(0x6, A1 + 0x24); // MOVE.B	#$06,36(A1)
  DEF_ROMLOC(182F4)
      : move_tomem_32(0x82C6, A1 + 0x4);              // MOVE.L	#$000082C6,4(A1)
  DEF_ROMLOC(182FC) : move_tomem_16(0x380, A1 + 0x2); // MOVE.W	#$0380,2(A1)
  DEF_ROMLOC(18302) : move_tomem_8(0x1, A1 + 0x1A);   // MOVE.B	#$01,26(A1)
  DEF_ROMLOC(18308) : add_tomem_8(0x1, A0 + 0x28);    // ADDQ.B	#$01,40(A0)
  DEF_ROMLOC(1830C) : move_toreg_16(A1, &D5);         // MOVE.W	A1,D5
  DEF_ROMLOC(1830E) : sub_toreg_16(0xFFFFD000, &D5);  // SUBI.W	#$D000,D5
  DEF_ROMLOC(18312) : lsr_toreg_16(0x6, &D5);         // LSR.W	#$06,D5
  DEF_ROMLOC(18314) : and_toreg_16(0x7F, &D5);        // ANDI.W	#$007F,D5
  DEF_ROMLOC(18318) : move_tomem_8(D5, A2++);         // MOVE.B	D5,(A2)+
  DEF_ROMLOC(1831A) : move_tomem_8(0x4, A1 + 0x1);    // MOVE.B	#$04,1(A1)
  DEF_ROMLOC(18320) : move_tomem_8(0x8, A1 + 0x19);   // MOVE.B	#$08,25(A1)
  DEF_ROMLOC(18326) : move_tomem_8(0x6, A1 + 0x18);   // MOVE.B	#$06,24(A1)
  DEF_ROMLOC(1832C)
      : move_tomem_32(read_32(A0 + 0x34), A1 + 0x34); // MOVE.L	52(A0),52(A1)
  DEF_ROMLOC(18332) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_182D4;                                 // DBF.W	D1,$182D4
  DEF_ROMLOC(18336) : move_tomem_8(0x8, A1 + 0x24); // MOVE.B	#$08,36(A1)
  DEF_ROMLOC(1833C)
      : move_tomem_32(0x8828, A1 + 0x4); // MOVE.L	#$00008828,4(A1)
  DEF_ROMLOC(18344)
      : move_tomem_16(0x43AA, A1 + 0x2);            // MOVE.W
                                                    // #$43AA,2(A1)
  DEF_ROMLOC(1834A) : move_tomem_8(0x1, A1 + 0x1A); // MOVE.B	#$01,26(A1)
  DEF_ROMLOC(18350) : move_tomem_8(0x5, A1 + 0x18); // MOVE.B	#$05,24(A1)
  DEF_ROMLOC(18356)
      : move_tomem_8(0xFFFFFF81, A1 + 0x20); // MOVE.B	#$81,32(A1)
  DEF_ROMLOC(1835C) : return;                // RTS
}
ROMFUNC(rom_18364) {
  DEF_ROMLOC(18364) : move_toreg_32(0x1835E, &A3);     // LEA.L	$0001835E,A3
  DEF_ROMLOC(1836A) : move_toreg_32(A0 + 0x28, &A2);   // LEA.L	40(A0),A2
  DEF_ROMLOC(1836E) : move_toreg_32(0x0, &D6);         // MOVEQ.L	$00,D6
  DEF_ROMLOC(18370) : move_toreg_8(read_8(A2++), &D6); // MOVE.B	(A2)+,D6
  rom_18372(); // Detected flow into next function
}
ROMFUNC(rom_18372) {
  DEF_ROMLOC(18372) : move_toreg_32(0x0, &D4);         // MOVEQ.L	$00,D4
  DEF_ROMLOC(18374) : move_toreg_8(read_8(A2++), &D4); // MOVE.B	(A2)+,D4
  DEF_ROMLOC(18376) : lsl_toreg_16(0x6, &D4);          // LSL.W	#$06,D4
  DEF_ROMLOC(18378)
      : add_toreg_32(0xFFD000, &D4);                   // ADDI.L	#$00FFD000,D4
  DEF_ROMLOC(1837E) : move_toreg_32(D4, &A1);          // MOVEA.L	D4,A1
  DEF_ROMLOC(18380) : move_toreg_8(read_8(A3++), &D0); // MOVE.B	(A3)+,D0
  DEF_ROMLOC(18382)
      : cmp_toreg_8(read_8(A1 + 0x3C), &D0);       // CMP.B	60(A1),D0
  DEF_ROMLOC(18386) : if (CCR_EQ) goto rom_1838C;  // BEQ.B	$1838C
  DEF_ROMLOC(18388) : add_tomem_8(0x1, A1 + 0x3C); // ADDQ.B	#$01,60(A1)
  DEF_ROMLOC(1838C) : dec_reg_16(&D6);
  if ((D6 & 0xffff) != 0xffff)
    goto rom_18372; // DBF.W	D6,$18372
  DEF_ROMLOC(18390)
      : cmp_toreg_8(read_8(A1 + 0x3C), &D0);       // CMP.B	60(A1),D0
  DEF_ROMLOC(18394) : if (!CCR_EQ) goto rom_183A6; // BNE.B	$183A6
  DEF_ROMLOC(18396)
      : move_toreg_32(read_32(A0 + 0x34), &A1);      // MOVEA.L	52(A0),A1
  DEF_ROMLOC(1839A) : cmp_tomem_8(0x6, A1 + 0x25);   // CMPI.B	#$06,37(A1)
  DEF_ROMLOC(183A0) : if (!CCR_EQ) goto rom_183A6;   // BNE.B	$183A6
  DEF_ROMLOC(183A2) : add_tomem_8(0x2, A0 + 0x24);   // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(183A6) : cmp_tomem_16(0x20, A0 + 0x32); // CMPI.W	#$0020,50(A0)
  DEF_ROMLOC(183AC) : if (CCR_EQ) goto rom_183B2;    // BEQ.B	$183B2
  DEF_ROMLOC(183AE) : add_tomem_16(0x1, A0 + 0x32);  // ADDQ.W	#$01,50(A0)
  DEF_ROMLOC(183B2) : rom_183D6();                   // BSR.W	$183D6
  DEF_ROMLOC(183B6) : move_toreg_8(read_8(A0 + 0x26), &D0); // MOVE.B
                                                            // 38(A0),D0
  DEF_ROMLOC(183BA) : rom_8238();                           // JSR	$00008238
  DEF_ROMLOC(183C0) : queue_sprite();
  return; // JMP	$0000DC92
}
ROMFUNC(rom_183C6) {
  DEF_ROMLOC(183C6) : rom_183D6(); // BSR.W	$183D6
  DEF_ROMLOC(183CA) : rom_81F8();  // JSR	$000081F8
  DEF_ROMLOC(183D0) : queue_sprite();
  return; // JMP	$0000DC92
}
ROMFUNC(rom_183D6) {
  DEF_ROMLOC(183D6)
      : move_toreg_32(read_32(A0 + 0x34), &A1);     // MOVEA.L	52(A0),A1
  DEF_ROMLOC(183DA) : add_tomem_8(0x20, A0 + 0x1B); // ADDI.B	#$20,27(A0)
  DEF_ROMLOC(183E0) : if (CCR_CC) goto rom_183E8;   // BCC.B	$183E8
  DEF_ROMLOC(183E2) : bchg_tomem_8(0x0, A0 + 0x1A); // BCHG.B	#$00,26(A0)
  DEF_ROMLOC(183E8)
      : move_tomem_16(read_16(A1 + 0x8), A0 + 0x3A); // MOVE.W	8(A1),58(A0)
  DEF_ROMLOC(183EE)
      : move_toreg_16(read_16(A1 + 0xC), &D0); // MOVE.W	12(A1),D0
  DEF_ROMLOC(183F2)
      : add_toreg_16(read_16(A0 + 0x32), &D0);      // ADD.W	50(A0),D0
  DEF_ROMLOC(183F6) : move_tomem_16(D0, A0 + 0x38); // MOVE.W	D0,56(A0)
  DEF_ROMLOC(183FA)
      : move_tomem_8(read_8(A1 + 0x22), A0 + 0x22); // MOVE.B	34(A1),34(A0)
  DEF_ROMLOC(18400) : tst_mem_8(A1 + 0x22);         // TST.B	34(A1)
  DEF_ROMLOC(18404) : if (CCR_PL) goto rom_18412;   // BPL.B	$18412
  DEF_ROMLOC(18406)
      : move_tomem_8(OBJ_EXPLOSIONBOMB,
                     A0 + offsetof(object, id));    // MOVE.B	#$3F,0(A0)
  DEF_ROMLOC(1840C) : move_tomem_8(0x0, A0 + 0x24); // MOVE.B	#$00,36(A0)
  DEF_ROMLOC(18412) : return;                       // RTS
}
ROMFUNC(rom_18414) {
  DEF_ROMLOC(18414)
      : move_toreg_32(read_32(A0 + 0x34), &A1);   // MOVEA.L	52(A0),A1
  DEF_ROMLOC(18418) : tst_mem_8(A1 + 0x22);       // TST.B	34(A1)
  DEF_ROMLOC(1841C) : if (CCR_PL) goto rom_1842A; // BPL.B	$1842A
  DEF_ROMLOC(1841E)
      : move_tomem_8(OBJ_EXPLOSIONBOMB,
                     A0 + offsetof(object, id));    // MOVE.B	#$3F,0(A0)
  DEF_ROMLOC(18424) : move_tomem_8(0x0, A0 + 0x24); // MOVE.B	#$00,36(A0)
  DEF_ROMLOC(1842A) : queue_sprite();
  return; // JMP	$0000DC92
}
ROMFUNC(rom_18430) {
  DEF_ROMLOC(18430) : move_toreg_32(0x0, &D0);     // MOVEQ.L	$00,D0
  DEF_ROMLOC(18432) : tst_mem_8(A0 + 0x1A);        // TST.B	26(A0)
  DEF_ROMLOC(18436) : if (!CCR_EQ) goto rom_1843A; // BNE.B	$1843A
  DEF_ROMLOC(18438) : add_toreg_8(0x1, &D0);       // ADDQ.B	#$01,D0
  DEF_ROMLOC(1843A) : move_tomem_8(D0, A0 + 0x1A); // MOVE.B	D0,26(A0)
  DEF_ROMLOC(1843E)
      : move_toreg_32(read_32(A0 + 0x34), &A1);     // MOVEA.L	52(A0),A1
  DEF_ROMLOC(18442) : tst_mem_8(A1 + 0x22);         // TST.B	34(A1)
  DEF_ROMLOC(18446) : if (CCR_PL) goto rom_18462;   // BPL.B	$18462
  DEF_ROMLOC(18448) : move_tomem_8(0x0, A0 + 0x20); // MOVE.B	#$00,32(A0)
  DEF_ROMLOC(1844E) : rom_1800C();                  // BSR.W	$1800C
  DEF_ROMLOC(18452) : sub_tomem_8(0x1, A0 + 0x3C);  // SUBQ.B	#$01,60(A0)
  DEF_ROMLOC(18456) : if (CCR_PL) goto rom_18462;   // BPL.B	$18462
  DEF_ROMLOC(18458)
      : move_tomem_8(OBJ_EXPLOSIONBOMB,
                     A0 + offsetof(object, id));    // MOVE.B	#$3F,(A0)
  DEF_ROMLOC(1845C) : move_tomem_8(0x0, A0 + 0x24); // MOVE.B	#$00,36(A0)
  DEF_ROMLOC(18462) : queue_sprite();
  return; // JMP	$0000DC92
}