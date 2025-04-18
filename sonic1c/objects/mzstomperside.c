// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_C024) {
  u8 switchindex = 0;
  DEF_ROMLOC(C024) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(C026) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(C02A)
      : move_toreg_16(read_16(0xC032 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(C02E): goto rom_C032 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(C02E) : switch (switchindex) {
  case 0:
    rom_C04E();
    break;
  case 1:
    rom_C0E2();
    break;
  case 2:
    rom_C118();
    break;
  case 3:
    rom_C12C();
    break;
  case 4:
    rom_C104();
    break;
  }
}
ROMFUNC(rom_C03C) {
  DEF_ROMLOC(C03C) : and_toreg_8(0x4, &D4); // ANDI.B	#$04,D4
  DEF_ROMLOC(C040) : asr_toreg_8(0x2, &D1); // ASR.B	#$02,D1
  DEF_ROMLOC(C042)
      : btst_tomem_8(0x6,
                     (s32)A4 + (s8)0x2 + (s16)D2); // BTST.B	#$06,2(A4,D2)
  rom_C048(); // Detected flow into next function
}
ROMFUNC(rom_C048) {
  DEF_ROMLOC(C048) : move_toreg_16(D0, &D4); // MOVE.W	D0,D4
  rom_C04E();                                // Detected flow into next function
}
ROMFUNC(rom_C04E) {
  DEF_ROMLOC(C04E) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(C050)
      : move_toreg_8(read_8(A0 + 0x28), &D0); // MOVE.B
                                              // 40(A0),D0
  DEF_ROMLOC(C054) : add_toreg_16(D0, &D0);   // ADD.W	D0,D0
  DEF_ROMLOC(C056)
      : move_toreg_16(read_16(0xC048 + (s16)(D0 & 0xffff)),
                      &D2);                      // MOVE.W	-16(PC,D0),D2
  DEF_ROMLOC(C05A) : move_toreg_32(0xC03C, &A2); // LEA.L	$0000C03C,A2
  DEF_ROMLOC(C060) : move_toreg_32(A0, &A1);     // MOVEA.L	A0,A1
  DEF_ROMLOC(C062) : move_toreg_32(0x3, &D1);    // MOVEQ.L	$03,D1
  DEF_ROMLOC(C064) : goto rom_C06C;              // BRA.B	$C06C
  DEF_ROMLOC(C066) : rom_E130();                 // BSR.W	$E130
  DEF_ROMLOC(C06A) : if (!CCR_EQ) goto rom_C0DC; // BNE.B	$C0DC
  DEF_ROMLOC(C06C)
      : move_tomem_8(read_8(A2++), A1 + 0x24); // MOVE.B	(A2)+,36(A1)
  DEF_ROMLOC(C070)
      : move_tomem_8(OBJ_SIDESTOMP,
                     A1 + offsetof(object, id)); // MOVE.B	#$45,0(A1)
  DEF_ROMLOC(C076)
      : move_tomem_16(read_16(A0 + 0xC), A1 + 0xC);   // MOVE.W	12(A0),12(A1)
  DEF_ROMLOC(C07C) : move_toreg_8(read_8(A2++), &D0); // MOVE.B	(A2)+,D0
  DEF_ROMLOC(C07E) : ext_reg_16(&D0);                 // EXT.W	D0
  DEF_ROMLOC(C080)
      : add_toreg_16(read_16(A0 + 0x8), &D0);     // ADD.W	8(A0),D0
  DEF_ROMLOC(C084) : move_tomem_16(D0, A1 + 0x8); // MOVE.W	D0,8(A1)
  DEF_ROMLOC(C088)
      : move_tomem_32(0xC2E4, A1 + 0x4);             // MOVE.L	#$0000C2E4,4(A1)
  DEF_ROMLOC(C090) : move_tomem_16(0x300, A1 + 0x2); // MOVE.W	#$0300,2(A1)
  DEF_ROMLOC(C096) : move_tomem_8(0x4, A1 + 0x1);    // MOVE.B	#$04,1(A1)
  DEF_ROMLOC(C09C)
      : move_tomem_16(read_16(A1 + 0x8), A1 + 0x30); // MOVE.W	8(A1),48(A1)
  DEF_ROMLOC(C0A2)
      : move_tomem_16(read_16(A0 + 0x8), A1 + 0x3A); // MOVE.W	8(A0),58(A1)
  DEF_ROMLOC(C0A8)
      : move_tomem_8(read_8(A0 + 0x28), A1 + 0x28); // MOVE.B	40(A0),40(A1)
  DEF_ROMLOC(C0AE) : move_tomem_8(0x20, A1 + 0x19); // MOVE.B	#$20,25(A1)
  DEF_ROMLOC(C0B4) : move_tomem_16(D2, A1 + 0x34);  // MOVE.W	D2,52(A1)
  DEF_ROMLOC(C0B8) : move_tomem_8(0x4, A1 + 0x18);  // MOVE.B	#$04,24(A1)
  DEF_ROMLOC(C0BE) : cmp_tomem_8(0x1, A2);          // CMPI.B	#$01,(A2)
  DEF_ROMLOC(C0C2) : if (!CCR_EQ) goto rom_C0CA;    // BNE.B	$C0CA
  DEF_ROMLOC(C0C4)
      : move_tomem_8(0xFFFFFF91, A1 + 0x20); // MOVE.B
                                             // #$91,32(A1)
  DEF_ROMLOC(C0CA)
      : move_tomem_8(read_8(A2++), A1 + 0x1A);     // MOVE.B	(A2)+,26(A1)
  DEF_ROMLOC(C0CE) : move_tomem_32(A0, A1 + 0x3C); // MOVE.L	A0,60(A1)
  DEF_ROMLOC(C0D2) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_C066;                                  // DBF.W	D1,$C066
  DEF_ROMLOC(C0D6) : move_tomem_8(0x3, A1 + 0x18);  // MOVE.B	#$03,24(A1)
  DEF_ROMLOC(C0DC) : move_tomem_8(0x10, A0 + 0x19); // MOVE.B	#$10,25(A0)
  rom_C0E2(); // Detected flow into next function
}
ROMFUNC(rom_C0E2) {
  DEF_ROMLOC(C0E2)
      : move_tomem_16(read_16(A0 + 0x8), A7 -= 2); // MOVE.W	8(A0),-(A7)
  DEF_ROMLOC(C0E6) : rom_C150();                   // BSR.W	$C150
  DEF_ROMLOC(C0EA) : move_toreg_16(0x17, &D1);     // MOVE.W	#$0017,D1
  DEF_ROMLOC(C0EE) : move_toreg_16(0x20, &D2);     // MOVE.W	#$0020,D2
  DEF_ROMLOC(C0F2) : move_toreg_16(0x20, &D3);     // MOVE.W	#$0020,D3
  DEF_ROMLOC(C0F6)
      : move_toreg_16(read_16((A7 += 2, A7 - 2)), &D4); // MOVE.W	(A7)+,D4
  DEF_ROMLOC(C0F8) : rom_10062();                       // BSR.W	$10062
  DEF_ROMLOC(C0FC) : queue_sprite();                    // BSR.W	$DC92
  rom_C130();                                           // BRA.W	$C130
}
ROMFUNC(rom_C104) {
  DEF_ROMLOC(C104)
      : move_toreg_32(read_32(A0 + 0x3C), &A1); // MOVEA.L	60(A0),A1
  DEF_ROMLOC(C108)
      : move_toreg_8(read_8(A1 + 0x32), &D0);     // MOVE.B	50(A1),D0
  DEF_ROMLOC(C10C) : add_toreg_8(0x10, &D0);      // ADDI.B	#$10,D0
  DEF_ROMLOC(C110) : lsr_toreg_8(0x5, &D0);       // LSR.B	#$05,D0
  DEF_ROMLOC(C112) : add_toreg_8(0x3, &D0);       // ADDQ.B	#$03,D0
  DEF_ROMLOC(C114) : move_tomem_8(D0, A0 + 0x1A); // MOVE.B	D0,26(A0)
  rom_C118(); // Detected flow into next function
}
ROMFUNC(rom_C118) {
  DEF_ROMLOC(C118)
      : move_toreg_32(read_32(A0 + 0x3C), &A1); // MOVEA.L	60(A0),A1
  DEF_ROMLOC(C11C) : move_toreg_32(0x0, &D0);   // MOVEQ.L	$00,D0
  DEF_ROMLOC(C11E)
      : move_toreg_8(read_8(A1 + 0x32), &D0); // MOVE.B
                                              // 50(A1),D0
  DEF_ROMLOC(C122) : neg_reg_16(&D0);         // NEG.W	D0
  DEF_ROMLOC(C124)
      : add_toreg_16(read_16(A0 + 0x30), &D0);    // ADD.W	48(A0),D0
  DEF_ROMLOC(C128) : move_tomem_16(D0, A0 + 0x8); // MOVE.W	D0,8(A0)
  rom_C12C(); // Detected flow into next function
}
ROMFUNC(rom_C12C) {
  DEF_ROMLOC(C12C) : queue_sprite(); // BSR.W	$DC92
  rom_C130();                        // Detected flow into next function
}
ROMFUNC(rom_C130) {
  DEF_ROMLOC(C130)
      : move_toreg_16(read_16(A0 + 0x3A), &D0);     // MOVE.W	58(A0),D0
  DEF_ROMLOC(C134) : and_toreg_16(0xFFFFFF80, &D0); // ANDI.W	#$FF80,D0
  DEF_ROMLOC(C138)
      : move_toreg_16(read_16(v_screenposx), &D1);  // MOVE.W	$F700,D1
  DEF_ROMLOC(C13C) : sub_toreg_16(0x80, &D1);       // SUBI.W	#$0080,D1
  DEF_ROMLOC(C140) : and_toreg_16(0xFFFFFF80, &D1); // ANDI.W	#$FF80,D1
  DEF_ROMLOC(C144) : sub_toreg_16(D1, &D0);         // SUB.W	D1,D0
  DEF_ROMLOC(C146)
      : cmp_toreg_16(128 + GAME_WIDTH + 192, &D0); // CMPI.W	#$0280,D0
  DEF_ROMLOC(C14A) : if (CCR_HI) {
    rom_DCCE();
    return;
  } // BHI.W	$DCCE
  DEF_ROMLOC(C14E) : return; // RTS
}
ROMFUNC(rom_C150) {
  u8 switchindex = 0;
  DEF_ROMLOC(C150) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(C152) : move_toreg_8(read_8(A0 + 0x28), &D0);
  switchindex = D0 / 2;                     // MOVE.B	40(A0),D0
  DEF_ROMLOC(C156) : add_toreg_16(D0, &D0); // ADD.W	D0,D0
  DEF_ROMLOC(C158)
      : move_toreg_16(read_16(0xC160 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(C15C): goto rom_C160 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(C15C) : switch (switchindex) {
  case 0:
    rom_C164();
    break;
  case 1:
    rom_C164();
    break;
  }
}
ROMFUNC(rom_C164) {
  DEF_ROMLOC(C164) : tst_mem_16(A0 + 0x36);         // TST.W	54(A0)
  DEF_ROMLOC(C168) : if (CCR_EQ) goto rom_C192;     // BEQ.B	$C192
  DEF_ROMLOC(C16A) : tst_mem_16(A0 + 0x38);         // TST.W	56(A0)
  DEF_ROMLOC(C16E) : if (CCR_EQ) goto rom_C176;     // BEQ.B	$C176
  DEF_ROMLOC(C170) : sub_tomem_16(0x1, A0 + 0x38);  // SUBQ.W	#$01,56(A0)
  goto rom_C1C6;                                    // BRA.B	$C1C6
  DEF_ROMLOC(C176) : sub_tomem_16(0x80, A0 + 0x32); // SUBI.W	#$0080,50(A0)
  DEF_ROMLOC(C17C) : if (CCR_CC) goto rom_C1C6;     // BCC.B	$C1C6
  DEF_ROMLOC(C17E) : move_tomem_16(0x0, A0 + 0x32); // MOVE.W	#$0000,50(A0)
  DEF_ROMLOC(C184) : move_tomem_16(0x0, A0 + 0x10); // MOVE.W	#$0000,16(A0)
  DEF_ROMLOC(C18A) : move_tomem_16(0x0, A0 + 0x36); // MOVE.W	#$0000,54(A0)
  goto rom_C1C6;                                    // BRA.B	$C1C6
  DEF_ROMLOC(C192)
      : move_toreg_16(read_16(A0 + 0x34), &D1); // MOVE.W	52(A0),D1
  DEF_ROMLOC(C196)
      : cmp_toreg_16(read_16(A0 + 0x32), &D1);  // CMP.W	50(A0),D1
  DEF_ROMLOC(C19A) : if (CCR_EQ) goto rom_C1C6; // BEQ.B	$C1C6
  DEF_ROMLOC(C19C)
      : move_toreg_16(read_16(A0 + 0x10), &D0);     // MOVE.W	16(A0),D0
  DEF_ROMLOC(C1A0) : add_tomem_16(0x70, A0 + 0x10); // ADDI.W	#$0070,16(A0)
  DEF_ROMLOC(C1A6) : add_tomem_16(D0, A0 + 0x32);   // ADD.W	D0,50(A0)
  DEF_ROMLOC(C1AA)
      : cmp_toreg_16(read_16(A0 + 0x32), &D1);       // CMP.W
                                                     // 50(A0),D1
  DEF_ROMLOC(C1AE) : if (CCR_HI) goto rom_C1C6;      // BHI.B	$C1C6
  DEF_ROMLOC(C1B0) : move_tomem_16(D1, A0 + 0x32);   // MOVE.W	D1,50(A0)
  DEF_ROMLOC(C1B4) : move_tomem_16(0x0, A0 + 0x10);  // MOVE.W	#$0000,16(A0)
  DEF_ROMLOC(C1BA) : move_tomem_16(0x1, A0 + 0x36);  // MOVE.W	#$0001,54(A0)
  DEF_ROMLOC(C1C0) : move_tomem_16(0x3C, A0 + 0x38); // MOVE.W	#$003C,56(A0)
  DEF_ROMLOC(C1C6) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(C1C8)
      : move_toreg_8(read_8(A0 + 0x32), &D0); // MOVE.B
                                              // 50(A0),D0
  DEF_ROMLOC(C1CC) : neg_reg_16(&D0);         // NEG.W	D0
  DEF_ROMLOC(C1CE)
      : add_toreg_16(read_16(A0 + 0x30), &D0);    // ADD.W	48(A0),D0
  DEF_ROMLOC(C1D2) : move_tomem_16(D0, A0 + 0x8); // MOVE.W	D0,8(A0)
  DEF_ROMLOC(C1D6) : return;                      // RTS
  DEF_ROMLOC(C1D8) : or_tomem_8(0x30, A6);        // ORI.B	#$30,(A6)
  rom_C3B8(); // Detected flow into next function
}