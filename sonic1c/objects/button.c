// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"


ROMFUNC(rom_C3B8) {
  u8 switchindex = 0;
  DEF_ROMLOC(C3B8) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(C3BA) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(C3BE)
      : move_toreg_16(read_16(0xC3C6 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(C3C2): goto rom_C3C6 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(C3C2) : switch (switchindex) {
  case 0:
    rom_C3CA();
    break;
  case 1:
    rom_C400();
    break;
  }
}
ROMFUNC(rom_C3CA) {
  DEF_ROMLOC(C3CA) : add_tomem_8(0x2, A0 + 0x24); // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(C3CE)
      : move_tomem_32(0xC52E, A0 + 0x4);              // MOVE.L	#$0000C52E,4(A0)
  DEF_ROMLOC(C3D6) : move_tomem_16(0x4513, A0 + 0x2); // MOVE.W	#$4513,2(A0)
  DEF_ROMLOC(C3DC) : cmp_tomem_8(0x2, 0xFFFFFE10);    // CMPI.B	#$02,$FE10
  DEF_ROMLOC(C3E2) : if (CCR_EQ) goto rom_C3EA;       // BEQ.B	$C3EA
  DEF_ROMLOC(C3E4) : move_tomem_16(0x513, A0 + 0x2);  // MOVE.W	#$0513,2(A0)
  DEF_ROMLOC(C3EA) : move_tomem_8(0x4, A0 + 0x1);     // MOVE.B	#$04,1(A0)
  DEF_ROMLOC(C3F0) : move_tomem_8(0x10, A0 + 0x19);   // MOVE.B	#$10,25(A0)
  DEF_ROMLOC(C3F6) : move_tomem_8(0x4, A0 + 0x18);    // MOVE.B	#$04,24(A0)
  DEF_ROMLOC(C3FC) : add_tomem_16(0x3, A0 + 0xC);     // ADDQ.W	#$03,12(A0)
  rom_C400(); // Detected flow into next function
}
ROMFUNC(rom_C400) {
  DEF_ROMLOC(C400) : tst_mem_8(A0 + 0x1);       // TST.B	1(A0)
  DEF_ROMLOC(C404) : if (CCR_PL) goto rom_C482; // BPL.B	$C482
  DEF_ROMLOC(C406) : move_toreg_16(0x1B, &D1);  // MOVE.W	#$001B,D1
  DEF_ROMLOC(C40A) : move_toreg_16(0x5, &D2);   // MOVE.W	#$0005,D2
  DEF_ROMLOC(C40E) : move_toreg_16(0x5, &D3);   // MOVE.W	#$0005,D3
  DEF_ROMLOC(C412)
      : move_toreg_16(read_16(A0 + 0x8), &D4);     // MOVE.W	8(A0),D4
  DEF_ROMLOC(C416) : rom_10062();                  // BSR.W	$10062
  DEF_ROMLOC(C41A) : bclr_tomem_8(0x0, A0 + 0x1A); // BCLR.B	#$00,26(A0)
  DEF_ROMLOC(C420)
      : move_toreg_8(read_8(A0 + 0x28), &D0);        // MOVE.B	40(A0),D0
  DEF_ROMLOC(C424) : and_toreg_16(0xF, &D0);         // ANDI.W	#$000F,D0
  DEF_ROMLOC(C428) : move_toreg_32(0xFFFFF7E0, &A3); // LEA.L	$F7E0,A3
  DEF_ROMLOC(C42C)
      : move_toreg_32((s32)A3 + (s8)0x0 + (s16)D0,
                      &A3);                        // LEA.L	0(A3,D0),A3
  DEF_ROMLOC(C430) : move_toreg_32(0x0, &D3);      // MOVEQ.L	$00,D3
  DEF_ROMLOC(C432) : btst_tomem_8(0x6, A0 + 0x28); // BTST.B	#$06,40(A0)
  DEF_ROMLOC(C438) : if (CCR_EQ) goto rom_C43C;    // BEQ.B	$C43C
  DEF_ROMLOC(C43A) : move_toreg_32(0x7, &D3);      // MOVEQ.L	$07,D3
  DEF_ROMLOC(C43C) : tst_mem_8(A0 + 0x28);         // TST.B	40(A0)
  DEF_ROMLOC(C440) : if (CCR_PL) goto rom_C448;    // BPL.B	$C448
  DEF_ROMLOC(C442) : rom_C4AC();                   // BSR.W	$C4AC
  DEF_ROMLOC(C446) : if (!CCR_EQ) goto rom_C452;   // BNE.B	$C452
  DEF_ROMLOC(C448) : tst_mem_8(A0 + 0x25);         // TST.B	37(A0)
  DEF_ROMLOC(C44C) : if (!CCR_EQ) goto rom_C452;   // BNE.B	$C452
  DEF_ROMLOC(C44E) : bclr_tomem_8(D3, A3);         // BCLR.B	D3,(A3)
  goto rom_C468;                                   // BRA.B	$C468
  DEF_ROMLOC(C452) : tst_mem_8(A3);                // TST.B	(A3)
  DEF_ROMLOC(C454) : if (!CCR_EQ) goto rom_C460;   // BNE.B	$C460
  DEF_ROMLOC(C456) : move_toreg_16(0xCD, &D0);     // MOVE.W	#$00CD,D0
  DEF_ROMLOC(C45A) : rom_1394();                   // JSR	$00001394
  DEF_ROMLOC(C460) : bset_tomem_8(D3, A3);         // BSET.B	D3,(A3)
  DEF_ROMLOC(C462) : bset_tomem_8(0x0, A0 + 0x1A); // BSET.B	#$00,26(A0)
  DEF_ROMLOC(C468) : btst_tomem_8(0x5, A0 + 0x28); // BTST.B	#$05,40(A0)
  DEF_ROMLOC(C46E) : if (CCR_EQ) goto rom_C482;    // BEQ.B	$C482
  DEF_ROMLOC(C470) : sub_tomem_8(0x1, A0 + 0x1E);  // SUBQ.B	#$01,30(A0)
  DEF_ROMLOC(C474) : if (CCR_PL) goto rom_C482;    // BPL.B	$C482
  DEF_ROMLOC(C476) : move_tomem_8(0x7, A0 + 0x1E); // MOVE.B	#$07,30(A0)
  DEF_ROMLOC(C47C) : bchg_tomem_8(0x1, A0 + 0x1A); // BCHG.B	#$01,26(A0)
  DEF_ROMLOC(C482) : rom_DC92();                   // BSR.W	$DC92
  DEF_ROMLOC(C486)
      : move_toreg_16(read_16(A0 + 0x8), &D0);      // MOVE.W	8(A0),D0
  DEF_ROMLOC(C48A) : and_toreg_16(0xFFFFFF80, &D0); // ANDI.W	#$FF80,D0
  DEF_ROMLOC(C48E)
      : move_toreg_16(read_16(0xFFFFF700), &D1);    // MOVE.W	$F700,D1
  DEF_ROMLOC(C492) : sub_toreg_16(0x80, &D1);       // SUBI.W	#$0080,D1
  DEF_ROMLOC(C496) : and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
  DEF_ROMLOC(C49A) : sub_toreg_16(D1, &D0);         // SUB.W	D1,D0
  DEF_ROMLOC(C49C) : cmp_toreg_16(0x280, &D0);      // CMPI.W	#$0280,D0
  DEF_ROMLOC(C4A0) : if (CCR_HI) goto rom_C4A6;     // BHI.W	$C4A6
  DEF_ROMLOC(C4A4) : return;                        // RTS
  DEF_ROMLOC(C4A6) : rom_DCCE();                    // BSR.W	$DCCE
  DEF_ROMLOC(C4AA) : return;                        // RTS
}
ROMFUNC(rom_C4AC) {
  DEF_ROMLOC(C4AC) : move_tomem_16(D3, A7 -= 2); // MOVE.W	D3,-(A7)
  DEF_ROMLOC(C4AE)
      : move_toreg_16(read_16(A0 + 0x8), &D2); // MOVE.W	8(A0),D2
  DEF_ROMLOC(C4B2)
      : move_toreg_16(read_16(A0 + 0xC), &D3);       // MOVE.W	12(A0),D3
  DEF_ROMLOC(C4B6) : sub_toreg_16(0x10, &D2);        // SUBI.W	#$0010,D2
  DEF_ROMLOC(C4BA) : sub_toreg_16(0x8, &D3);         // SUBQ.W	#$08,D3
  DEF_ROMLOC(C4BC) : move_toreg_16(0x20, &D4);       // MOVE.W	#$0020,D4
  DEF_ROMLOC(C4C0) : move_toreg_16(0x10, &D5);       // MOVE.W	#$0010,D5
  DEF_ROMLOC(C4C4) : move_toreg_32(0xFFFFD800, &A1); // LEA.L	$D800,A1
  DEF_ROMLOC(C4C8) : move_toreg_16(0x5F, &D6);       // MOVE.W	#$005F,D6
  rom_C4CC(); // Detected flow into next function
}
ROMFUNC(rom_C4CC) {
  DEF_ROMLOC(C4CC) : tst_mem_8(A1 + 0x1);           // TST.B	1(A1)
  DEF_ROMLOC(C4D0) : if (CCR_PL) goto rom_C4D8;     // BPL.B	$C4D8
  DEF_ROMLOC(C4D2) : cmp_tomem_8(0x33, A1);         // CMPI.B	#$33,(A1)
  DEF_ROMLOC(C4D6) : if (CCR_EQ) goto rom_C4E8;     // BEQ.B	$C4E8
  DEF_ROMLOC(C4D8) : move_toreg_32(A1 + 0x40, &A1); // LEA.L	64(A1),A1
  DEF_ROMLOC(C4DC) : dec_reg_16(&D6);
  if ((D6 & 0xffff) != 0xffff)
    goto rom_C4CC; // DBF.W	D6,$C4CC
  DEF_ROMLOC(C4E0)
      : move_toreg_16(read_16((A7 += 2, A7 - 2)), &D3); // MOVE.W	(A7)+,D3
  DEF_ROMLOC(C4E2) : move_toreg_32(0x0, &D0);           // MOVEQ.L	$00,D0
  DEF_ROMLOC(C4E4) : return;                            // RTS
  DEF_ROMLOC(C4E6) : move_toreg_8(read_8(A0), &D0);     // MOVE.B	(A0),D0
  DEF_ROMLOC(C4E8) : move_toreg_32(0x1, &D0);           // MOVEQ.L	$01,D0
  DEF_ROMLOC(C4EA) : and_toreg_16(0x3F, &D0);           // ANDI.W	#$003F,D0
  DEF_ROMLOC(C4EE) : add_toreg_16(D0, &D0);             // ADD.W	D0,D0
  DEF_ROMLOC(C4F0)
      : move_toreg_32(0xC4E4 + (s16)(D0 & 0xffff),
                      &A2);                           // LEA.L	-14(PC,D0),A2
  DEF_ROMLOC(C4F4) : move_toreg_8(read_8(A2++), &D1); // MOVE.B	(A2)+,D1
  DEF_ROMLOC(C4F6) : ext_reg_16(&D1);                 // EXT.W	D1
  DEF_ROMLOC(C4F8)
      : move_toreg_16(read_16(A1 + 0x8), &D0);        // MOVE.W	8(A1),D0
  DEF_ROMLOC(C4FC) : sub_toreg_16(D1, &D0);           // SUB.W	D1,D0
  DEF_ROMLOC(C4FE) : sub_toreg_16(D2, &D0);           // SUB.W	D2,D0
  DEF_ROMLOC(C500) : if (CCR_CC) goto rom_C50A;       // BCC.B	$C50A
  DEF_ROMLOC(C502) : add_toreg_16(D1, &D1);           // ADD.W	D1,D1
  DEF_ROMLOC(C504) : add_toreg_16(D1, &D0);           // ADD.W	D1,D0
  DEF_ROMLOC(C506) : if (CCR_CS) goto rom_C50E;       // BCS.B	$C50E
  goto rom_C4D8;                                      // BRA.B	$C4D8
  DEF_ROMLOC(C50A) : cmp_toreg_16(D4, &D0);           // CMP.W	D4,D0
  DEF_ROMLOC(C50C) : if (CCR_HI) goto rom_C4D8;       // BHI.B	$C4D8
  DEF_ROMLOC(C50E) : move_toreg_8(read_8(A2++), &D1); // MOVE.B	(A2)+,D1
  DEF_ROMLOC(C510) : ext_reg_16(&D1);                 // EXT.W	D1
  DEF_ROMLOC(C512)
      : move_toreg_16(read_16(A1 + 0xC), &D0);  // MOVE.W	12(A1),D0
  DEF_ROMLOC(C516) : sub_toreg_16(D1, &D0);     // SUB.W	D1,D0
  DEF_ROMLOC(C518) : sub_toreg_16(D3, &D0);     // SUB.W	D3,D0
  DEF_ROMLOC(C51A) : if (CCR_CC) goto rom_C524; // BCC.B	$C524
  DEF_ROMLOC(C51C) : add_toreg_16(D1, &D1);     // ADD.W	D1,D1
  DEF_ROMLOC(C51E) : add_toreg_16(D1, &D0);     // ADD.W	D1,D0
  DEF_ROMLOC(C520) : if (CCR_CS) goto rom_C528; // BCS.B	$C528
  goto rom_C4D8;                                // BRA.B	$C4D8
  DEF_ROMLOC(C524) : cmp_toreg_16(D5, &D0);     // CMP.W	D5,D0
  DEF_ROMLOC(C526) : if (CCR_HI) goto rom_C4D8; // BHI.B	$C4D8
  DEF_ROMLOC(C528)
      : move_toreg_16(read_16((A7 += 2, A7 - 2)), &D3); // MOVE.W	(A7)+,D3
  DEF_ROMLOC(C52A) : move_toreg_32(0x1, &D0);           // MOVEQ.L	$01,D0
  DEF_ROMLOC(C52C) : return;                            // RTS
}