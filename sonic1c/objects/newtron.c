// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"


ROMFUNC(rom_E3F6) {
  u8 switchindex = 0;
  DEF_ROMLOC(E3F6) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(E3F8) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(E3FC)
      : move_toreg_16(read_16(0xE404 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(E400): goto rom_E404 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(E400) : switch (switchindex) {
  case 0:
    rom_E40A();
    break;
  case 1:
    rom_E43A();
    break;
  case 2:
    rom_E5A4();
    break;
  }
}
ROMFUNC(rom_E40A) {
  DEF_ROMLOC(E40A) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(E40E)
      : move_tomem_32(0xE5D0, A0 + 0x4);             // MOVE.L	#$0000E5D0,4(A0)
  DEF_ROMLOC(E416) : move_tomem_16(0x49B, A0 + 0x2); // MOVE.W	#$049B,2(A0)
  DEF_ROMLOC(E41C) : move_tomem_8(0x4, A0 + 0x1);    // MOVE.B	#$04,1(A0)
  DEF_ROMLOC(E422) : move_tomem_8(0x4, A0 + 0x18);   // MOVE.B	#$04,24(A0)
  DEF_ROMLOC(E428) : move_tomem_8(0x14, A0 + 0x19);  // MOVE.B	#$14,25(A0)
  DEF_ROMLOC(E42E) : move_tomem_8(0x10, A0 + 0x16);  // MOVE.B	#$10,22(A0)
  DEF_ROMLOC(E434) : move_tomem_8(0x8, A0 + 0x17);   // MOVE.B	#$08,23(A0)
  rom_E43A(); // Detected flow into next function
}
ROMFUNC(rom_E460);
ROMFUNC(rom_E4A2);
ROMFUNC(rom_E516);
ROMFUNC(rom_E536);
ROMFUNC(rom_E53C);
ROMFUNC(rom_E43A) {
  u8 switchindex = 0;
  DEF_ROMLOC(E43A) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(E43C) : move_toreg_8(read_8(A0 + 0x25), &D0);
  switchindex = D0 / 2; // MOVE.B	37(A0),D0
  DEF_ROMLOC(E440)
      : move_toreg_16(read_16(0xE456 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	20(PC,D0),D1
  // DEF_ROMLOC(E444): rom_E456 + (s16)(D1 & 0xffff)(); // JSR	16(PC,D1)
  DEF_ROMLOC(E444) : switch (switchindex) {
  case 0:
    rom_E460();
    break;
  case 1:
    rom_E4A2();
    break;
  case 2:
    rom_E516();
    break;
  case 3:
    rom_E536();
    break;
  case 4:
    rom_E53C();
    break;
  }
  DEF_ROMLOC(E448) : move_toreg_32(0xE5A8, &A1); // LEA.L	$0000E5A8,A1
  DEF_ROMLOC(E44E) : animate_sprite();                 // BSR.W	$ADA2
  rom_FD38();                                    // BRA.W	$FD38
}
ROMFUNC(rom_E460) {
  DEF_ROMLOC(E460) : bset_tomem_8(0x0, A0 + 0x22); // BSET.B	#$00,34(A0)
  DEF_ROMLOC(E466)
      : move_toreg_16(read_16(0xFFFFD008), &D0); // MOVE.W	$D008,D0
  DEF_ROMLOC(E46A)
      : sub_toreg_16(read_16(A0 + 0x8), &D0);         // SUB.W	8(A0),D0
  DEF_ROMLOC(E46E) : if (CCR_CC) goto rom_E478;       // BCC.B	$E478
  DEF_ROMLOC(E470) : neg_reg_16(&D0);                 // NEG.W	D0
  DEF_ROMLOC(E472) : bclr_tomem_8(0x0, A0 + 0x22);    // BCLR.B	#$00,34(A0)
  DEF_ROMLOC(E478) : cmp_toreg_16(0x80, &D0);         // CMPI.W	#$0080,D0
  DEF_ROMLOC(E47C) : if (CCR_CC) goto rom_E4A0;       // BCC.B	$E4A0
  DEF_ROMLOC(E47E) : add_tomem_8(0x2, A0 + 0x25);     // ADDQ.B	#$02,37(A0)
  DEF_ROMLOC(E482) : move_tomem_8(0x1, A0 + 0x1C);    // MOVE.B	#$01,28(A0)
  DEF_ROMLOC(E488) : tst_mem_8(A0 + 0x28);            // TST.B	40(A0)
  DEF_ROMLOC(E48C) : if (CCR_EQ) goto rom_E4A0;       // BEQ.B	$E4A0
  DEF_ROMLOC(E48E) : move_tomem_16(0x249B, A0 + 0x2); // MOVE.W	#$249B,2(A0)
  DEF_ROMLOC(E494) : move_tomem_8(0x8, A0 + 0x25);    // MOVE.B	#$08,37(A0)
  DEF_ROMLOC(E49A) : move_tomem_8(0x4, A0 + 0x1C);    // MOVE.B	#$04,28(A0)
  DEF_ROMLOC(E4A0) : return;                          // RTS
}
ROMFUNC(rom_E4A2) {
  DEF_ROMLOC(E4A2) : cmp_tomem_8(0x4, A0 + 0x1A);  // CMPI.B	#$04,26(A0)
  DEF_ROMLOC(E4A8) : if (CCR_CC) goto rom_E4C2;    // BCC.B	$E4C2
  DEF_ROMLOC(E4AA) : bset_tomem_8(0x0, A0 + 0x22); // BSET.B	#$00,34(A0)
  DEF_ROMLOC(E4B0)
      : move_toreg_16(read_16(0xFFFFD008), &D0); // MOVE.W	$D008,D0
  DEF_ROMLOC(E4B4)
      : sub_toreg_16(read_16(A0 + 0x8), &D0);         // SUB.W	8(A0),D0
  DEF_ROMLOC(E4B8) : if (CCR_CC) goto rom_E4C0;       // BCC.B	$E4C0
  DEF_ROMLOC(E4BA) : bclr_tomem_8(0x0, A0 + 0x22);    // BCLR.B	#$00,34(A0)
  DEF_ROMLOC(E4C0) : return;                          // RTS
  DEF_ROMLOC(E4C2) : cmp_tomem_8(0x1, A0 + 0x1A);     // CMPI.B	#$01,26(A0)
  DEF_ROMLOC(E4C8) : if (!CCR_EQ) goto rom_E4D0;      // BNE.B	$E4D0
  DEF_ROMLOC(E4CA) : move_tomem_8(0xC, A0 + 0x20);    // MOVE.B	#$0C,32(A0)
  DEF_ROMLOC(E4D0) : rom_DC40();                      // BSR.W	$DC40
  DEF_ROMLOC(E4D4) : rom_15580();                     // BSR.W	$15580
  DEF_ROMLOC(E4D8) : tst_reg_16(&D1);                 // TST.W	D1
  DEF_ROMLOC(E4DA) : if (CCR_PL) goto rom_E514;       // BPL.B	$E514
  DEF_ROMLOC(E4DC) : add_tomem_16(D1, A0 + 0xC);      // ADD.W	D1,12(A0)
  DEF_ROMLOC(E4E0) : move_tomem_16(0x0, A0 + 0x12);   // MOVE.W	#$0000,18(A0)
  DEF_ROMLOC(E4E6) : add_tomem_8(0x2, A0 + 0x25);     // ADDQ.B	#$02,37(A0)
  DEF_ROMLOC(E4EA) : move_tomem_8(0x2, A0 + 0x1C);    // MOVE.B	#$02,28(A0)
  DEF_ROMLOC(E4F0) : btst_tomem_8(0x5, A0 + 0x2);     // BTST.B	#$05,2(A0)
  DEF_ROMLOC(E4F6) : if (CCR_EQ) goto rom_E4FC;       // BEQ.B	$E4FC
  DEF_ROMLOC(E4F8) : add_tomem_8(0x1, A0 + 0x1C);     // ADDQ.B	#$01,28(A0)
  DEF_ROMLOC(E4FC) : move_tomem_8(0xD, A0 + 0x20);    // MOVE.B	#$0D,32(A0)
  DEF_ROMLOC(E502) : move_tomem_16(0x200, A0 + 0x10); // MOVE.W	#$0200,16(A0)
  DEF_ROMLOC(E508) : btst_tomem_8(0x0, A0 + 0x22);    // BTST.B	#$00,34(A0)
  DEF_ROMLOC(E50E) : if (!CCR_EQ) goto rom_E514;      // BNE.B	$E514
  DEF_ROMLOC(E510) : neg_mem_16(A0 + 0x10);           // NEG.W	16(A0)
  DEF_ROMLOC(E514) : return;                          // RTS
}
ROMFUNC(rom_E516) {
  DEF_ROMLOC(E516) : rom_DC6C();                    // BSR.W	$DC6C
  DEF_ROMLOC(E51A) : rom_15580();                   // BSR.W	$15580
  DEF_ROMLOC(E51E) : cmp_toreg_16(0xFFFFFFF8, &D1); // CMPI.W	#$FFF8,D1
  DEF_ROMLOC(E522) : if (CCR_LT) goto rom_E530;     // BLT.B	$E530
  DEF_ROMLOC(E524) : cmp_toreg_16(0xC, &D1);        // CMPI.W	#$000C,D1
  DEF_ROMLOC(E528) : if (CCR_GE) goto rom_E530;     // BGE.B	$E530
  DEF_ROMLOC(E52A) : add_tomem_16(D1, A0 + 0xC);    // ADD.W	D1,12(A0)
  DEF_ROMLOC(E52E) : return;                        // RTS
  DEF_ROMLOC(E530) : add_tomem_8(0x2, A0 + 0x25);   // ADDQ.B	#$02,37(A0)
  DEF_ROMLOC(E534) : return;                        // RTS
}
ROMFUNC(rom_E536) {
  DEF_ROMLOC(E536) : rom_DC6C(); // BSR.W	$DC6C
  DEF_ROMLOC(E53A) : return;     // RTS
}
ROMFUNC(rom_E53C) {
  DEF_ROMLOC(E53C) : cmp_tomem_8(0x1, A0 + 0x1A);  // CMPI.B	#$01,26(A0)
  DEF_ROMLOC(E542) : if (!CCR_EQ) goto rom_E54A;   // BNE.B	$E54A
  DEF_ROMLOC(E544) : move_tomem_8(0xC, A0 + 0x20); // MOVE.B	#$0C,32(A0)
  DEF_ROMLOC(E54A) : cmp_tomem_8(0x2, A0 + 0x1A);  // CMPI.B	#$02,26(A0)
  DEF_ROMLOC(E550) : if (!CCR_EQ) goto rom_E5A2;   // BNE.B	$E5A2
  DEF_ROMLOC(E552) : tst_mem_8(A0 + 0x32);         // TST.B	50(A0)
  DEF_ROMLOC(E556) : if (!CCR_EQ) goto rom_E5A2;   // BNE.B	$E5A2
  DEF_ROMLOC(E558) : move_tomem_8(0x1, A0 + 0x32); // MOVE.B	#$01,50(A0)
  DEF_ROMLOC(E55E) : rom_E11A();                   // BSR.W	$E11A
  DEF_ROMLOC(E562) : if (!CCR_EQ) goto rom_E5A2;   // BNE.B	$E5A2
  DEF_ROMLOC(E564) : move_tomem_8(OBJ_MISSILE, A1 + offsetof(object, id)); // MOVE.B	#$23,0(A1)
  DEF_ROMLOC(E56A)
      : move_tomem_16(read_16(A0 + 0x8), A1 + 0x8); // MOVE.W	8(A0),8(A1)
  DEF_ROMLOC(E570)
      : move_tomem_16(read_16(A0 + 0xC), A1 + 0xC);   // MOVE.W	12(A0),12(A1)
  DEF_ROMLOC(E576) : sub_tomem_16(0x8, A1 + 0xC);     // SUBQ.W	#$08,12(A1)
  DEF_ROMLOC(E57A) : move_tomem_16(0x200, A1 + 0x10); // MOVE.W	#$0200,16(A1)
  DEF_ROMLOC(E580) : move_toreg_16(0x14, &D0);        // MOVE.W	#$0014,D0
  DEF_ROMLOC(E584) : btst_tomem_8(0x0, A0 + 0x22);    // BTST.B	#$00,34(A0)
  DEF_ROMLOC(E58A) : if (!CCR_EQ) goto rom_E592;      // BNE.B	$E592
  DEF_ROMLOC(E58C) : neg_reg_16(&D0);                 // NEG.W	D0
  DEF_ROMLOC(E58E) : neg_mem_16(A1 + 0x10);           // NEG.W	16(A1)
  DEF_ROMLOC(E592) : add_tomem_16(D0, A1 + 0x8);      // ADD.W	D0,8(A1)
  DEF_ROMLOC(E596)
      : move_tomem_8(read_8(A0 + 0x22), A1 + 0x22); // MOVE.B	34(A0),34(A1)
  DEF_ROMLOC(E59C) : move_tomem_8(0x1, A1 + 0x28);  // MOVE.B	#$01,40(A1)
  DEF_ROMLOC(E5A2) : return;                        // RTS
}
ROMFUNC(rom_E5A4) {
  rom_DCCE(); // BRA.W	$DCCE
}