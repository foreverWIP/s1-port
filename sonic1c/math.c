// #define CHECK_STUFF 1
#include "opcodes.h"
#include "system.h"


ROMFUNC(rom_29AC) {
  DEF_ROMLOC(29AC)
      : move_toreg_32(read_32(0xFFFFF636), &D1);     // MOVE.L	$F636,D1
  DEF_ROMLOC(29B0) : if (!CCR_EQ) goto rom_29B8;     // BNE.B	$29B8
  DEF_ROMLOC(29B2) : move_toreg_32(0x2A6D365A, &D1); // MOVE.L	#$2A6D365A,D1
  DEF_ROMLOC(29B8) : move_toreg_32(D1, &D0);         // MOVE.L	D1,D0
  DEF_ROMLOC(29BA) : asl_toreg_32(0x2, &D1);         // ASL.L	#$02,D1
  DEF_ROMLOC(29BC) : add_toreg_32(D0, &D1);          // ADD.L	D0,D1
  DEF_ROMLOC(29BE) : asl_toreg_32(0x3, &D1);         // ASL.L	#$03,D1
  DEF_ROMLOC(29C0) : add_toreg_32(D0, &D1);          // ADD.L	D0,D1
  DEF_ROMLOC(29C2) : move_toreg_16(D1, &D0);         // MOVE.W	D1,D0
  DEF_ROMLOC(29C4) : swap_reg_16(&D1);               // SWAP.W	D1
  DEF_ROMLOC(29C6) : add_toreg_16(D1, &D0);          // ADD.W	D1,D0
  DEF_ROMLOC(29C8) : move_toreg_16(D0, &D1);         // MOVE.W	D0,D1
  DEF_ROMLOC(29CA) : swap_reg_16(&D1);               // SWAP.W	D1
  DEF_ROMLOC(29CC) : move_tomem_32(D1, 0xFFFFF636);  // MOVE.L	D1,$F636
  DEF_ROMLOC(29D0) : return;                         // RTS
}
ROMFUNC(rom_29D2) {
  DEF_ROMLOC(29D2) : and_toreg_16(0xFF, &D0); // ANDI.W	#$00FF,D0
  DEF_ROMLOC(29D6) : add_toreg_16(D0, &D0);   // ADD.W	D0,D0
  DEF_ROMLOC(29D8) : add_toreg_16(0x80, &D0); // ADDI.W	#$0080,D0
  DEF_ROMLOC(29DC)
      : move_toreg_16(read_16(0x29EA + (s16)(D0 & 0xffff)),
                      &D1);                   // MOVE.W	12(PC,D0),D1
  DEF_ROMLOC(29E0) : sub_toreg_16(0x80, &D0); // SUBI.W	#$0080,D0
  DEF_ROMLOC(29E4)
      : move_toreg_16(read_16(0x29EA + (s16)(D0 & 0xffff)),
                      &D0);  // MOVE.W	4(PC,D0),D0
  DEF_ROMLOC(29E8) : return; // RTS
}
ROMFUNC(rom_2C6A) {
  u32 d3backup = 0;
  u32 d4backup = 0;
  DEF_ROMLOC(2C6A) : d3backup = D3;
  d4backup = D4;                                // TODO; // MOVEM.L	D3-D4,-(A7)
  DEF_ROMLOC(2C6E) : move_toreg_32(0x0, &D3);   // MOVEQ.L	$00,D3
  DEF_ROMLOC(2C70) : move_toreg_32(0x0, &D4);   // MOVEQ.L	$00,D4
  DEF_ROMLOC(2C72) : move_toreg_16(D1, &D3);    // MOVE.W	D1,D3
  DEF_ROMLOC(2C74) : move_toreg_16(D2, &D4);    // MOVE.W	D2,D4
  DEF_ROMLOC(2C76) : or_toreg_16(D3, &D4);      // OR.W	D3,D4
  DEF_ROMLOC(2C78) : if (CCR_EQ) goto rom_2CC6; // BEQ.B	$2CC6
  DEF_ROMLOC(2C7A) : move_toreg_16(D2, &D4);    // MOVE.W	D2,D4
  DEF_ROMLOC(2C7C) : tst_reg_16(&D3);           // TST.W	D3
  DEF_ROMLOC(2C7E) : if (CCR_PL) goto rom_2C84; // BPL.W	$2C84
  DEF_ROMLOC(2C82) : neg_reg_16(&D3);           // NEG.W	D3
  DEF_ROMLOC(2C84) : tst_reg_16(&D4);           // TST.W	D4
  DEF_ROMLOC(2C86) : if (CCR_PL) goto rom_2C8C; // BPL.W	$2C8C
  DEF_ROMLOC(2C8A) : neg_reg_16(&D4);           // NEG.W	D4
  DEF_ROMLOC(2C8C) : cmp_toreg_16(D3, &D4);     // CMP.W	D3,D4
  DEF_ROMLOC(2C8E) : if (CCR_CC) goto rom_2C9E; // BCC.W	$2C9E
  DEF_ROMLOC(2C92) : lsl_toreg_32(0x8, &D4);    // LSL.L	#$08,D4
  DEF_ROMLOC(2C94) : divu_toreg_16(D3, &D4);    // DIVU.W	D3,D4
  DEF_ROMLOC(2C96) : move_toreg_32(0x0, &D0);   // MOVEQ.L	$00,D0
  DEF_ROMLOC(2C98)
      : move_toreg_8(read_8(0x2CD0 + (s16)(D4 & 0xffff)),
                     &D0);                     // MOVE.B	54(PC,D4),D0
  goto rom_2CA8;                               // BRA.B	$2CA8
  DEF_ROMLOC(2C9E) : lsl_toreg_32(0x8, &D3);   // LSL.L	#$08,D3
  DEF_ROMLOC(2CA0) : divu_toreg_16(D4, &D3);   // DIVU.W	D4,D3
  DEF_ROMLOC(2CA2) : move_toreg_32(0x40, &D0); // MOVEQ.L	$40,D0
  DEF_ROMLOC(2CA4)
      : sub_toreg_8(read_8(0x2CD0 + (s16)(D3 & 0xffff)),
                    &D0);                       // SUB.B	42(PC,D3),D0
  DEF_ROMLOC(2CA8) : tst_reg_16(&D1);           // TST.W	D1
  DEF_ROMLOC(2CAA) : if (CCR_PL) goto rom_2CB4; // BPL.W	$2CB4
  DEF_ROMLOC(2CAE) : neg_reg_16(&D0);           // NEG.W	D0
  DEF_ROMLOC(2CB0) : add_toreg_16(0x80, &D0);   // ADDI.W	#$0080,D0
  DEF_ROMLOC(2CB4) : tst_reg_16(&D2);           // TST.W	D2
  DEF_ROMLOC(2CB6) : if (CCR_PL) goto rom_2CC0; // BPL.W	$2CC0
  DEF_ROMLOC(2CBA) : neg_reg_16(&D0);           // NEG.W	D0
  DEF_ROMLOC(2CBC) : add_toreg_16(0x100, &D0);  // ADDI.W	#$0100,D0
  DEF_ROMLOC(2CC0) : D3 = d3backup;
  D4 = d4backup;                               // TODO; // MOVEM.L	(A7)+,D3-D4
  DEF_ROMLOC(2CC4) : return;                   // RTS
  DEF_ROMLOC(2CC6) : move_toreg_16(0x40, &D0); // MOVE.W	#$0040,D0
  DEF_ROMLOC(2CCA) : D3 = d3backup;
  D4 = d4backup;             // TODO; // MOVEM.L	(A7)+,D3-D4
  DEF_ROMLOC(2CCE) : return; // RTS
}
ROMFUNC(rom_411A) {
  DEF_ROMLOC(411A) : move_toreg_32(0xFFFFFE5E, &A1); // LEA.L	$FE5E,A1
  DEF_ROMLOC(411E) : move_toreg_32(0x412E, &A2);     // LEA.L	$0000412E,A2
  DEF_ROMLOC(4124) : move_toreg_32(0x20, &D1);       // MOVEQ.L	$20,D1
  DEF_ROMLOC(4126)
      : move_tomem_16(read_16((A2 += 2, A2 - 2)),
                      (A1 += 2, A1 - 2)); // MOVE.W	(A2)+,(A1)+
  DEF_ROMLOC(4128) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_4126;           // DBF.W	D1,$4126
  DEF_ROMLOC(412C) : return; // RTS
}
ROMFUNC(rom_4170) {
  DEF_ROMLOC(4170) : cmp_tomem_8(0x6, 0xFFFFD024);   // CMPI.B	#$06,$D024
  DEF_ROMLOC(4176) : if (CCR_CC) goto rom_41C6;      // BCC.B	$41C6
  DEF_ROMLOC(4178) : move_toreg_32(0xFFFFFE5E, &A1); // LEA.L	$FE5E,A1
  DEF_ROMLOC(417C) : move_toreg_32(0x41C8, &A2);     // LEA.L	$000041C8,A2
  DEF_ROMLOC(4182)
      : move_toreg_16(read_16((A1 += 2, A1 - 2)), &D3); // MOVE.W	(A1)+,D3
  DEF_ROMLOC(4184) : move_toreg_32(0xF, &D1);           // MOVEQ.L	$0F,D1
  DEF_ROMLOC(4186)
      : move_toreg_16(read_16((A2 += 2, A2 - 2)), &D2); // MOVE.W	(A2)+,D2
  DEF_ROMLOC(4188)
      : move_toreg_16(read_16((A2 += 2, A2 - 2)), &D4); // MOVE.W	(A2)+,D4
  DEF_ROMLOC(418A) : btst_toreg_32(D1, &D3);            // BTST.L	D1,D3
  DEF_ROMLOC(418C) : if (!CCR_EQ) goto rom_41A6;        // BNE.B	$41A6
  DEF_ROMLOC(418E)
      : move_toreg_16(read_16(A1 + 0x2), &D0);           // MOVE.W	2(A1),D0
  DEF_ROMLOC(4192) : add_toreg_16(D2, &D0);              // ADD.W	D2,D0
  DEF_ROMLOC(4194) : move_tomem_16(D0, A1 + 0x2);        // MOVE.W	D0,2(A1)
  DEF_ROMLOC(4198) : add_tomem_16(D0, A1 + 0x0);         // ADD.W	D0,0(A1)
  DEF_ROMLOC(419C) : cmp_toreg_8(read_8(A1 + 0x0), &D4); // CMP.B	0(A1),D4
  DEF_ROMLOC(41A0) : if (CCR_HI) goto rom_41BC;          // BHI.B	$41BC
  DEF_ROMLOC(41A2) : bset_toreg_32(D1, &D3);             // BSET.L	D1,D3
  DEF_ROMLOC(41A4) : goto rom_41BC;                      // BRA.B	$41BC
  DEF_ROMLOC(41A6)
      : move_toreg_16(read_16(A1 + 0x2), &D0);           // MOVE.W	2(A1),D0
  DEF_ROMLOC(41AA) : sub_toreg_16(D2, &D0);              // SUB.W	D2,D0
  DEF_ROMLOC(41AC) : move_tomem_16(D0, A1 + 0x2);        // MOVE.W	D0,2(A1)
  DEF_ROMLOC(41B0) : add_tomem_16(D0, A1 + 0x0);         // ADD.W	D0,0(A1)
  DEF_ROMLOC(41B4) : cmp_toreg_8(read_8(A1 + 0x0), &D4); // CMP.B	0(A1),D4
  DEF_ROMLOC(41B8) : if (CCR_LS) goto rom_41BC;          // BLS.B	$41BC
  DEF_ROMLOC(41BA) : bclr_toreg_32(D1, &D3);             // BCLR.L	D1,D3
  DEF_ROMLOC(41BC) : add_toreg_16(0x4, &A1);             // ADDQ.W	#$04,A1
  DEF_ROMLOC(41BE) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_4186;                                  // DBF.W	D1,$4186
  DEF_ROMLOC(41C2) : move_tomem_16(D3, 0xFFFFFE5E); // MOVE.W	D3,$FE5E
  DEF_ROMLOC(41C6) : return;                        // RTS
}