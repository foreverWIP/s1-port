// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_A1A4) {
  u8 switchindex = 0;
  DEF_ROMLOC(A1A4) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(A1A6) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(A1AA)
      : move_toreg_16(read_16(0xA1B2 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(A1AE): goto rom_A1B2 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(A1AE) : switch (switchindex) {
  case 0:
    rom_A1DC();
    break;
  case 1:
    rom_A294();
    break;
  case 2:
    rom_A2BC();
    break;
  case 3:
    rom_A2E2();
    break;
  case 4:
    rom_A2F0();
    break;
  }
}
ROMFUNC(rom_A1DC) {
  DEF_ROMLOC(A1DC) : move_toreg_32(0xFFFFFC00, &A2); // LEA.L	$FC00,A2
  DEF_ROMLOC(A1E0) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(A1E2)
      : move_toreg_8(read_8(A0 + 0x23), &D0); // MOVE.B
                                              // 35(A0),D0
  DEF_ROMLOC(A1E6)
      : move_toreg_32((s32)A2 + (s8)0x2 + (s16)D0,
                      &A2);                         // LEA.L	2(A2,D0),A2
  DEF_ROMLOC(A1EA) : move_toreg_8(read_8(A2), &D4); // MOVE.B	(A2),D4
  DEF_ROMLOC(A1EC)
      : move_toreg_8(read_8(A0 + 0x28), &D1);    // MOVE.B	40(A0),D1
  DEF_ROMLOC(A1F0) : move_toreg_8(D1, &D0);      // MOVE.B	D1,D0
  DEF_ROMLOC(A1F2) : and_toreg_16(0x7, &D1);     // ANDI.W	#$0007,D1
  DEF_ROMLOC(A1F6) : cmp_toreg_16(0x7, &D1);     // CMPI.W	#$0007,D1
  DEF_ROMLOC(A1FA) : if (!CCR_EQ) goto rom_A1FE; // BNE.B	$A1FE
  DEF_ROMLOC(A1FC) : move_toreg_32(0x6, &D1);    // MOVEQ.L	$06,D1
  DEF_ROMLOC(A1FE) : SWAPWORDS(D1);              // SWAP.W	D1
  DEF_ROMLOC(A200) : move_toreg_16(0x0, &D1);    // MOVE.W	#$0000,D1
  DEF_ROMLOC(A204) : lsr_toreg_8(0x4, &D0);      // LSR.B	#$04,D0
  DEF_ROMLOC(A206) : add_toreg_16(D0, &D0);      // ADD.W	D0,D0
  DEF_ROMLOC(A208)
      : move_toreg_8(read_8(0xA1BC + (s16)(D0 & 0xffff)),
                     &D5);            // MOVE.B	-78(PC,D0),D5
  DEF_ROMLOC(A20C) : ext_reg_16(&D5); // EXT.W	D5
  DEF_ROMLOC(A20E)
      : move_toreg_8(read_8(0xA1BD + (s16)(D0 & 0xffff)),
                     &D6);                   // MOVE.B	-83(PC,D0),D6
  DEF_ROMLOC(A212) : ext_reg_16(&D6);        // EXT.W	D6
  DEF_ROMLOC(A214) : move_toreg_32(A0, &A1); // MOVEA.L	A0,A1
  DEF_ROMLOC(A216)
      : move_toreg_16(read_16(A0 + 0x8), &D2); // MOVE.W	8(A0),D2
  DEF_ROMLOC(A21A)
      : move_toreg_16(read_16(A0 + 0xC), &D3);   // MOVE.W	12(A0),D3
  DEF_ROMLOC(A21E) : lsr_toreg_8(0x1, &D4);      // LSR.B	#$01,D4
  DEF_ROMLOC(A220) : if (CCR_CS) goto rom_A280;  // BCS.B	$A280
  DEF_ROMLOC(A222) : bclr_tomem_8(0x7, A2);      // BCLR.B	#$07,(A2)
  goto rom_A238;                                 // BRA.B	$A238
  DEF_ROMLOC(A228) : SWAPWORDS(D1);              // SWAP.W	D1
  DEF_ROMLOC(A22A) : lsr_toreg_8(0x1, &D4);      // LSR.B	#$01,D4
  DEF_ROMLOC(A22C) : if (CCR_CS) goto rom_A280;  // BCS.B	$A280
  DEF_ROMLOC(A22E) : bclr_tomem_8(0x7, A2);      // BCLR.B	#$07,(A2)
  DEF_ROMLOC(A232) : rom_E11A();                 // BSR.W	$E11A
  DEF_ROMLOC(A236) : if (!CCR_EQ) goto rom_A28C; // BNE.B	$A28C
  DEF_ROMLOC(A238)
      : move_tomem_8(OBJ_RINGS,
                     A1 + offsetof(object, id));  // MOVE.B	#$25,0(A1)
  DEF_ROMLOC(A23E) : add_tomem_8(0x2, A1 + 0x24); // ADDQ.B	#$02,36(A1)
  DEF_ROMLOC(A242) : move_tomem_16(D2, A1 + 0x8); // MOVE.W	D2,8(A1)
  DEF_ROMLOC(A246)
      : move_tomem_16(read_16(A0 + 0x8), A1 + 0x32);  // MOVE.W	8(A0),50(A1)
  DEF_ROMLOC(A24C) : move_tomem_16(D3, A1 + 0xC);     // MOVE.W	D3,12(A1)
  DEF_ROMLOC(A250) : move_tomem_32(0xA610, A1 + 0x4); // MOVE.L	#$0000A610,4(A1)
  DEF_ROMLOC(A258) : move_tomem_16(0x27B2, A1 + 0x2); // MOVE.W	#$27B2,2(A1)
  DEF_ROMLOC(A25E) : move_tomem_8(0x4, A1 + 0x1);     // MOVE.B	#$04,1(A1)
  DEF_ROMLOC(A264) : move_tomem_8(0x2, A1 + 0x18);    // MOVE.B	#$02,24(A1)
  DEF_ROMLOC(A26A) : move_tomem_8(0x47, A1 + 0x20);   // MOVE.B	#$47,32(A1)
  DEF_ROMLOC(A270) : move_tomem_8(0x8, A1 + 0x19);    // MOVE.B	#$08,25(A1)
  DEF_ROMLOC(A276)
      : move_tomem_8(read_8(A0 + 0x23), A1 + 0x23); // MOVE.B	35(A0),35(A1)
  DEF_ROMLOC(A27C) : move_tomem_8(D1, A1 + 0x34);   // MOVE.B	D1,52(A1)
  DEF_ROMLOC(A280) : add_toreg_16(0x1, &D1);        // ADDQ.W	#$01,D1
  DEF_ROMLOC(A282) : add_toreg_16(D5, &D2);         // ADD.W	D5,D2
  DEF_ROMLOC(A284) : add_toreg_16(D6, &D3);         // ADD.W	D6,D3
  DEF_ROMLOC(A286) : SWAPWORDS(D1);                 // SWAP.W	D1
  DEF_ROMLOC(A288) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_A228;                          // DBF.W	D1,$A228
  DEF_ROMLOC(A28C) : btst_tomem_8(0x0, A2); // BTST.B	#$00,(A2)
  DEF_ROMLOC(A290) : if (!CCR_EQ) {
    rom_DCCE();
    return;
  } // BNE.W	$DCCE
  rom_A294(); // Detected flow into next function
}
ROMFUNC(rom_A294) {
  DEF_ROMLOC(A294)
      : move_tomem_8(read_8(v_ani1_frame),
                     A0 + 0x1A);     // MOVE.B	$FEC3,26(A0)
  DEF_ROMLOC(A29A) : queue_sprite(); // BSR.W	$DC92
  DEF_ROMLOC(A29E)
      : move_toreg_16(read_16(A0 + 0x32), &D0);     // MOVE.W	50(A0),D0
  DEF_ROMLOC(A2A2) : and_toreg_16(0xFFFFFF80, &D0); // ANDI.W	#$FF80,D0
  DEF_ROMLOC(A2A6)
      : move_toreg_16(read_16(v_screenposx), &D1);  // MOVE.W	$F700,D1
  DEF_ROMLOC(A2AA) : sub_toreg_16(0x80, &D1);       // SUBI.W	#$0080,D1
  DEF_ROMLOC(A2AE) : and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
  DEF_ROMLOC(A2B2) : sub_toreg_16(D1, &D0);         // SUB.W	D1,D0
  DEF_ROMLOC(A2B4)
      : cmp_toreg_16(128 + GAME_WIDTH + 192, &D0); // CMPI.W	#$0280,D0
  DEF_ROMLOC(A2B8) : if (CCR_HI) {
    rom_A2F0();
    return;
  } // BHI.B	$A2F0
  DEF_ROMLOC(A2BA) : return; // RTS
}
ROMFUNC(rom_A2BC) {
  DEF_ROMLOC(A2BC) : add_tomem_8(0x2, A0 + 0x24);    // ADDQ.B	#$02,36(A0)
  DEF_ROMLOC(A2C0) : move_tomem_8(0x0, A0 + 0x20);   // MOVE.B	#$00,32(A0)
  DEF_ROMLOC(A2C6) : move_tomem_8(0x1, A0 + 0x18);   // MOVE.B	#$01,24(A0)
  DEF_ROMLOC(A2CC) : rom_A2F4();                     // BSR.W	$A2F4
  DEF_ROMLOC(A2D0) : move_toreg_32(0xFFFFFC00, &A2); // LEA.L	$FC00,A2
  DEF_ROMLOC(A2D4) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(A2D6)
      : move_toreg_8(read_8(A0 + 0x23), &D0); // MOVE.B
                                              // 35(A0),D0
  DEF_ROMLOC(A2DA)
      : move_toreg_8(read_8(A0 + 0x34), &D1); // MOVE.B
                                              // 52(A0),D1
  DEF_ROMLOC(A2DE)
      : bset_tomem_8(D1,
                     (s32)A2 + (s8)0x2 + (s16)D0); // BSET.B	D1,2(A2,D0)
  rom_A2E2(); // Detected flow into next function
}
ROMFUNC(rom_A2E2) {
  DEF_ROMLOC(A2E2) : move_toreg_32(0xA608, &A1); // LEA.L	$0000A608,A1
  DEF_ROMLOC(A2E8) : animate_sprite();           // BSR.W	$ADA2
  queue_sprite();                                // BRA.W	$DC92
}
ROMFUNC(rom_A2F0) {
  rom_DCCE(); // BRA.W	$DCCE
}
ROMFUNC(rom_A2F4) {
  DEF_ROMLOC(A2F4) : add_tomem_16(0x1, 0xFFFFFE20);  // ADDQ.W	#$01,$FE20
  DEF_ROMLOC(A2F8) : or_tomem_8(0x1, 0xFFFFFE1D);    // ORI.B	#$01,$FE1D
  DEF_ROMLOC(A2FE) : move_toreg_16(SFX_RING, &D0);   // MOVE.W	#$00B5,D0
  DEF_ROMLOC(A302) : cmp_tomem_16(0x64, 0xFFFFFE20); // CMPI.W	#$0064,$FE20
  DEF_ROMLOC(A308) : if (CCR_CS) goto rom_A32E;      // BCS.B	$A32E
  DEF_ROMLOC(A30A) : bset_tomem_8(0x1, 0xFFFFFE1B);  // BSET.B	#$01,$FE1B
  DEF_ROMLOC(A310) : if (CCR_EQ) goto rom_A322;      // BEQ.B	$A322
  DEF_ROMLOC(A312) : cmp_tomem_16(0xC8, 0xFFFFFE20); // CMPI.W	#$00C8,$FE20
  DEF_ROMLOC(A318) : if (CCR_CS) goto rom_A32E;      // BCS.B	$A32E
  DEF_ROMLOC(A31A) : bset_tomem_8(0x2, 0xFFFFFE1B);  // BSET.B	#$02,$FE1B
  DEF_ROMLOC(A320) : if (!CCR_EQ) goto rom_A32E;     // BNE.B	$A32E
  DEF_ROMLOC(A322) : add_tomem_8(0x1, v_lives);      // ADDQ.B	#$01,$FE12
  DEF_ROMLOC(A326) : add_tomem_8(0x1, 0xFFFFFE1C);   // ADDQ.B	#$01,$FE1C
  DEF_ROMLOC(A32A)
      : move_toreg_16(BGM_EXTRALIFE, &D0); // MOVE.W
                                           // #$0088,D0
  DEF_ROMLOC(A32E) : play_sound_special(); // JMP	$00001394
}