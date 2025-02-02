#include "opcodes.h"
#include "system.h"

static u32 d0backup = 0;
static u32 d1backup = 0;
static u32 d2backup = 0;
static u32 d3backup = 0;
static u32 d4backup = 0;
static u32 d5backup = 0;
static u32 d6backup = 0;
static u32 d7backup = 0;
static u32 a0backup = 0;
static u32 a1backup = 0;
static u32 a2backup = 0;
static u32 a3backup = 0;
static u32 a4backup = 0;
static u32 a5backup = 0;
static u32 a6backup = 0;

ROMFUNC(rom_B10) {
  u8 switchindex = 0;
  DEF_ROMLOC(B10) : d0backup = D0;
  d1backup = D1;
  d2backup = D2;
  d3backup = D3;
  d4backup = D4;
  d5backup = D5;
  d6backup = D6;
  d7backup = D7;
  a0backup = A0;
  a1backup = A1;
  a2backup = A2;
  a3backup = A3;
  a4backup = A4;
  a5backup = A5;
  a6backup = A6;
  // TODO; // MOVEM.L	D0-A6,-(A7)
  DEF_ROMLOC(B14) : tst_mem_8(0xFFFFF62A); // TST.B	$F62A
  DEF_ROMLOC(B18) : if (CCR_EQ) {
    rom_B88();
    return;
  } // BEQ.B	$B88
  DEF_ROMLOC(B1A)
      : move_toreg_16(read_16(0xC00004), &D0); // MOVE.W	$00C00004,D0
  DEF_ROMLOC(B20)
      : move_tomem_32(0x40000010, 0xC00004); // MOVE.L	#$40000010,$00C00004
  DEF_ROMLOC(B2A)
      : move_tomem_32(read_32(0xFFFFF616), 0xC00000); // MOVE.L	$F616,$00C00000
  DEF_ROMLOC(B32) : btst_tomem_8(0x6, 0xFFFFFFF8);    // BTST.B	#$06,$FFF8
  DEF_ROMLOC(B38) : if (CCR_EQ) goto rom_B42;         // BEQ.B	$B42
  DEF_ROMLOC(B3A) : move_toreg_16(0x700, &D0);        // MOVE.W	#$0700,D0
  DEF_ROMLOC(B3E) : dec_reg_16(&D0);
  if ((D0 & 0xffff) != 0xffff)
    goto rom_B3E; // DBF.W	D0,$0B3E
  DEF_ROMLOC(B42)
      : move_toreg_8(read_8(0xFFFFF62A), &D0);      // MOVE.B	$F62A,D0
  DEF_ROMLOC(B46) : move_tomem_8(0x0, 0xFFFFF62A);  // MOVE.B	#$00,$F62A
  DEF_ROMLOC(B4C) : move_tomem_16(0x1, 0xFFFFF644); // MOVE.W	#$0001,$F644
  DEF_ROMLOC(B52) : and_toreg_16(0x3E, &D0);
  switchindex = D0 / 2; // ANDI.W	#$003E,D0
  DEF_ROMLOC(B56)
      : move_toreg_16(read_16(0xB6E + (s16)(D0 & 0xffff)),
                      &D0); // MOVE.W	22(PC,D0),D0
  // DEF_ROMLOC(B5A): rom_B6E + (s16)(D0 & 0xffff)(); // JSR	18(PC,D0)
  DEF_ROMLOC(B5A) : switch (switchindex) {
  case 0:
    rom_B88();
    break;
  case 1:
    rom_C32();
    break;
  case 2:
    rom_C44();
    break;
  case 3:
    rom_C5E();
    break;
  case 4:
    rom_C6E();
    break;
  case 5:
    rom_DA6();
    break;
  case 6:
    rom_E72();
    break;
  case 7:
    rom_F8A();
    break;
  case 8:
    rom_C64();
    break;
  case 9:
    rom_F9A();
    break;
  case 10:
    rom_C36();
    break;
  case 11:
    rom_FA6();
    break;
  case 12:
    rom_E72();
    break;
  }
  rom_B5E(); // Detected flow into next function
}
ROMFUNC(rom_B5E) {
  update_sound_driver();
  rom_B64(); // Detected flow into next function
}
ROMFUNC(rom_B64) {
  DEF_ROMLOC(B64) : add_tomem_32(0x1, 0xFFFFFE0C); // ADDQ.L	#$01,$FE0C
  DEF_ROMLOC(B68) : D0 = d0backup;
  D1 = d1backup;
  D2 = d2backup;
  D3 = d3backup;
  D4 = d4backup;
  D5 = d5backup;
  D6 = d6backup;
  D7 = d7backup;
  A0 = a0backup;
  A1 = a1backup;
  A2 = a2backup;
  A3 = a3backup;
  A4 = a4backup;
  A5 = a5backup;
  A6 = a6backup;
  // TODO; // MOVEM.L	(A7)+,D0-A6
  /*DEF_ROMLOC(B6C):*/ return; // RTE
}
ROMFUNC(rom_B88) {
  DEF_ROMLOC(B88) : cmp_tomem_8(0xFFFFFF8C, 0xFFFFF600); // CMPI.B
                                                         // #$8C,$F600
  DEF_ROMLOC(B8E) : if (CCR_EQ) goto rom_B9A;            // BEQ.B	$B9A
  DEF_ROMLOC(B90) : cmp_tomem_8(0xC, 0xFFFFF600);        // CMPI.B	#$0C,$F600
  DEF_ROMLOC(B96) : if (!CCR_EQ) {
    rom_B5E();
    return;
  }                                               // BNE.W	$0B5E
  DEF_ROMLOC(B9A) : cmp_tomem_8(0x1, 0xFFFFFE10); // CMPI.B	#$01,$FE10
  DEF_ROMLOC(BA0) : if (!CCR_EQ) {
    rom_B5E();
    return;
  } // BNE.W	$0B5E
  DEF_ROMLOC(BA4)
      : move_toreg_16(read_16(0xC00004), &D0);     // MOVE.W	$00C00004,D0
  DEF_ROMLOC(BAA) : btst_tomem_8(0x6, 0xFFFFFFF8); // BTST.B	#$06,$FFF8
  DEF_ROMLOC(BB0) : if (CCR_EQ) goto rom_BBA;      // BEQ.B	$BBA
  DEF_ROMLOC(BB2) : move_toreg_16(0x700, &D0);     // MOVE.W	#$0700,D0
  DEF_ROMLOC(BB6) : dec_reg_16(&D0);
  if ((D0 & 0xffff) != 0xffff)
    goto rom_BB6;                                   // DBF.W	D0,$0BB6
  DEF_ROMLOC(BBA) : move_tomem_16(0x1, 0xFFFFF644); // MOVE.W	#$0001,$F644
  DEF_ROMLOC(BC0)
      : move_tomem_16(0x100, 0xA11100);           // MOVE.W	#$0100,$00A11100
  DEF_ROMLOC(BC8) : btst_tomem_8(0x0, 0xA11100);  // BTST.B	#$00,$00A11100
  DEF_ROMLOC(BD0) : if (!CCR_EQ) goto rom_BC8;    // BNE.B	$BC8
  DEF_ROMLOC(BD2) : tst_mem_8(0xFFFFF64E);        // TST.B	$F64E
  DEF_ROMLOC(BD6) : if (!CCR_EQ) goto rom_BFE;    // BNE.B	$BFE
  DEF_ROMLOC(BD8) : move_toreg_32(0xC00004, &A5); // LEA.L	$00C00004,A5
  DEF_ROMLOC(BDE)
      : move_tomem_32(0x94009340, A5); // MOVE.L	#$94009340,(A5)
  DEF_ROMLOC(BE4)
      : move_tomem_32(0x96FD9580, A5);               // MOVE.L	#$96FD9580,(A5)
  DEF_ROMLOC(BEA) : move_tomem_16(0xFFFF977F, A5);   // MOVE.W	#$977F,(A5)
  DEF_ROMLOC(BEE) : move_tomem_16(0xFFFFC000, A5);   // MOVE.W	#$C000,(A5)
  DEF_ROMLOC(BF2) : move_tomem_16(0x80, 0xFFFFF640); // MOVE.W	#$0080,$F640
  DEF_ROMLOC(BF8)
      : move_tomem_16(read_16(0xFFFFF640), A5);   // MOVE.W	$F640,(A5)
  DEF_ROMLOC(BFC) : goto rom_C22;                 // BRA.B	$C22
  DEF_ROMLOC(BFE) : move_toreg_32(0xC00004, &A5); // LEA.L	$00C00004,A5
  DEF_ROMLOC(C04)
      : move_tomem_32(0x94009340, A5); // MOVE.L	#$94009340,(A5)
  DEF_ROMLOC(C0A)
      : move_tomem_32(0x96FD9540, A5);               // MOVE.L	#$96FD9540,(A5)
  DEF_ROMLOC(C10) : move_tomem_16(0xFFFF977F, A5);   // MOVE.W	#$977F,(A5)
  DEF_ROMLOC(C14) : move_tomem_16(0xFFFFC000, A5);   // MOVE.W	#$C000,(A5)
  DEF_ROMLOC(C18) : move_tomem_16(0x80, 0xFFFFF640); // MOVE.W	#$0080,$F640
  DEF_ROMLOC(C1E)
      : move_tomem_16(read_16(0xFFFFF640), A5); // MOVE.W	$F640,(A5)
  DEF_ROMLOC(C22)
      : move_tomem_16(read_16(0xFFFFF624), A5); // MOVE.W	$F624,(A5)
  DEF_ROMLOC(C26)
      : move_tomem_16(0x0, 0xA11100); // MOVE.W	#$0000,$00A11100
  rom_B5E();                          // BRA.W	$0B5E
}
ROMFUNC(rom_C32) {
  DEF_ROMLOC(C32) : rom_106E(); // BSR.W	$106E
  rom_C36();                    // Detected flow into next function
}
ROMFUNC(rom_C36) {
  DEF_ROMLOC(C36) : tst_mem_16(0xFFFFF614);        // TST.W	$F614
  DEF_ROMLOC(C3A) : if (CCR_EQ) goto rom_C42;      // BEQ.W	$0C42
  DEF_ROMLOC(C3E) : sub_tomem_16(0x1, 0xFFFFF614); // SUBQ.W	#$01,$F614
  DEF_ROMLOC(C42) : return;                        // RTS
}
ROMFUNC(rom_C44) {
  DEF_ROMLOC(C44) : rom_106E();                    // BSR.W	$106E
  DEF_ROMLOC(C48) : scroll_update_tiles_bg();                    // BSR.W	$6C30
  DEF_ROMLOC(C4C) : plc_refresh_frame();                    // BSR.W	$163A
  DEF_ROMLOC(C50) : tst_mem_16(0xFFFFF614);        // TST.W	$F614
  DEF_ROMLOC(C54) : if (CCR_EQ) goto rom_C5C;      // BEQ.W	$0C5C
  DEF_ROMLOC(C58) : sub_tomem_16(0x1, 0xFFFFF614); // SUBQ.W	#$01,$F614
  DEF_ROMLOC(C5C) : return;                        // RTS
}
ROMFUNC(rom_C5E) {
  DEF_ROMLOC(C5E) : rom_106E(); // BSR.W	$106E
  DEF_ROMLOC(C62) : return;     // RTS
}
ROMFUNC(rom_C64) {
  DEF_ROMLOC(C64) : cmp_tomem_8(0x10, 0xFFFFF600); // CMPI.B	#$10,$F600
  DEF_ROMLOC(C6A) : if (CCR_EQ) {
    rom_DA6();
    return;
  }          // BEQ.W	$0DA6
  rom_C6E(); // Detected flow into next function
}
ROMFUNC(rom_C6E) {
  DEF_ROMLOC(C6E)
      : move_tomem_16(0x100, 0xA11100);           // MOVE.W	#$0100,$00A11100
  DEF_ROMLOC(C76) : btst_tomem_8(0x0, 0xA11100);  // BTST.B	#$00,$00A11100
  DEF_ROMLOC(C7E) : if (!CCR_EQ) goto rom_C76;    // BNE.B	$C76
  DEF_ROMLOC(C80) : input_read_controllers();                   // BSR.W	$11E6
  DEF_ROMLOC(C84) : tst_mem_8(0xFFFFF64E);        // TST.B	$F64E
  DEF_ROMLOC(C88) : if (!CCR_EQ) goto rom_CB0;    // BNE.B	$CB0
  DEF_ROMLOC(C8A) : move_toreg_32(0xC00004, &A5); // LEA.L	$00C00004,A5
  DEF_ROMLOC(C90)
      : move_tomem_32(0x94009340, A5); // MOVE.L	#$94009340,(A5)
  DEF_ROMLOC(C96)
      : move_tomem_32(0x96FD9580, A5);               // MOVE.L	#$96FD9580,(A5)
  DEF_ROMLOC(C9C) : move_tomem_16(0xFFFF977F, A5);   // MOVE.W	#$977F,(A5)
  DEF_ROMLOC(CA0) : move_tomem_16(0xFFFFC000, A5);   // MOVE.W	#$C000,(A5)
  DEF_ROMLOC(CA4) : move_tomem_16(0x80, 0xFFFFF640); // MOVE.W	#$0080,$F640
  DEF_ROMLOC(CAA)
      : move_tomem_16(read_16(0xFFFFF640), A5);   // MOVE.W	$F640,(A5)
  DEF_ROMLOC(CAE) : goto rom_CD4;                 // BRA.B	$CD4
  DEF_ROMLOC(CB0) : move_toreg_32(0xC00004, &A5); // LEA.L	$00C00004,A5
  DEF_ROMLOC(CB6)
      : move_tomem_32(0x94009340, A5); // MOVE.L	#$94009340,(A5)
  DEF_ROMLOC(CBC)
      : move_tomem_32(0x96FD9540, A5);               // MOVE.L	#$96FD9540,(A5)
  DEF_ROMLOC(CC2) : move_tomem_16(0xFFFF977F, A5);   // MOVE.W	#$977F,(A5)
  DEF_ROMLOC(CC6) : move_tomem_16(0xFFFFC000, A5);   // MOVE.W	#$C000,(A5)
  DEF_ROMLOC(CCA) : move_tomem_16(0x80, 0xFFFFF640); // MOVE.W	#$0080,$F640
  DEF_ROMLOC(CD0)
      : move_tomem_16(read_16(0xFFFFF640), A5); // MOVE.W	$F640,(A5)
  DEF_ROMLOC(CD4)
      : move_tomem_16(read_16(0xFFFFF624), A5);   // MOVE.W	$F624,(A5)
  DEF_ROMLOC(CD8) : move_toreg_32(0xC00004, &A5); // LEA.L	$00C00004,A5
  DEF_ROMLOC(CDE)
      : move_tomem_32(0x940193C0, A5); // MOVE.L	#$940193C0,(A5)
  DEF_ROMLOC(CE4)
      : move_tomem_32(0x96E69500, A5);               // MOVE.L	#$96E69500,(A5)
  DEF_ROMLOC(CEA) : move_tomem_16(0xFFFF977F, A5);   // MOVE.W	#$977F,(A5)
  DEF_ROMLOC(CEE) : move_tomem_16(0x7C00, A5);       // MOVE.W	#$7C00,(A5)
  DEF_ROMLOC(CF2) : move_tomem_16(0x83, 0xFFFFF640); // MOVE.W	#$0083,$F640
  DEF_ROMLOC(CF8)
      : move_tomem_16(read_16(0xFFFFF640), A5);   // MOVE.W	$F640,(A5)
  DEF_ROMLOC(CFC) : move_toreg_32(0xC00004, &A5); // LEA.L	$00C00004,A5
  DEF_ROMLOC(D02)
      : move_tomem_32(0x94019340, A5); // MOVE.L	#$94019340,(A5)
  DEF_ROMLOC(D08)
      : move_tomem_32(0x96FC9500, A5);               // MOVE.L	#$96FC9500,(A5)
  DEF_ROMLOC(D0E) : move_tomem_16(0xFFFF977F, A5);   // MOVE.W	#$977F,(A5)
  DEF_ROMLOC(D12) : move_tomem_16(0x7800, A5);       // MOVE.W	#$7800,(A5)
  DEF_ROMLOC(D16) : move_tomem_16(0x83, 0xFFFFF640); // MOVE.W	#$0083,$F640
  DEF_ROMLOC(D1C)
      : move_tomem_16(read_16(0xFFFFF640), A5);   // MOVE.W	$F640,(A5)
  DEF_ROMLOC(D20) : tst_mem_8(0xFFFFF767);        // TST.B	$F767
  DEF_ROMLOC(D24) : if (CCR_EQ) goto rom_D50;     // BEQ.B	$D50
  DEF_ROMLOC(D26) : move_toreg_32(0xC00004, &A5); // LEA.L	$00C00004,A5
  DEF_ROMLOC(D2C)
      : move_tomem_32(0x94019370, A5); // MOVE.L	#$94019370,(A5)
  DEF_ROMLOC(D32)
      : move_tomem_32(0x96E49500, A5);               // MOVE.L	#$96E49500,(A5)
  DEF_ROMLOC(D38) : move_tomem_16(0xFFFF977F, A5);   // MOVE.W	#$977F,(A5)
  DEF_ROMLOC(D3C) : move_tomem_16(0x7000, A5);       // MOVE.W	#$7000,(A5)
  DEF_ROMLOC(D40) : move_tomem_16(0x83, 0xFFFFF640); // MOVE.W	#$0083,$F640
  DEF_ROMLOC(D46)
      : move_tomem_16(read_16(0xFFFFF640), A5);    // MOVE.W	$F640,(A5)
  DEF_ROMLOC(D4A) : move_tomem_8(0x0, 0xFFFFF767); // MOVE.B	#$00,$F767
  DEF_ROMLOC(D50)
      : move_tomem_16(0x0, 0xA11100); // MOVE.W	#$0000,$00A11100
  DEF_ROMLOC(D58) : D0 = read_32(0xFFF700);
  D1 = read_32(0xFFF704);
  D2 = read_32(0xFFF708);
  D3 = read_32(0xFFF70C);
  D4 = read_32(0xFFF710);
  D5 = read_32(0xFFF714);
  D6 = read_32(0xFFF718);
  D7 = read_32(0xFFF71C);
  // TODO; // MOVEM.L	$F700,D0-D7
  DEF_ROMLOC(D5E) : write_32(0xFFFF10, D0);
  write_32(0xFFFF14, D1);
  write_32(0xFFFF18, D2);
  write_32(0xFFFF1C, D3);
  write_32(0xFFFF20, D4);
  write_32(0xFFFF24, D5);
  write_32(0xFFFF28, D6);
  write_32(0xFFFF2C, D7);
  // TODO; // MOVEM.L	D0-D7,$FF10
  DEF_ROMLOC(D64) : D0 = read_32(0xFFF754);
  D1 = read_32(0xFFF758);
  // TODO; // MOVEM.L	$F754,D0-D1
  DEF_ROMLOC(D6A) : write_32(0xFFFF30, D0);
  write_32(0xFFFF34, D1);
  // TODO; // MOVEM.L	D0-D1,$FF30
  DEF_ROMLOC(D70) : cmp_tomem_8(0x60, 0xFFFFF625); // CMPI.B	#$60,$F625
  DEF_ROMLOC(D76) : if (CCR_CC) {
    rom_D84();
    return;
  }                                                // BCC.B	$D84
  DEF_ROMLOC(D78) : move_tomem_8(0x1, 0xFFFFF64F); // MOVE.B	#$01,$F64F
  // DEF_ROMLOC(D7E): // TODO; // ADDQ.L	#$04,A7
  // rom_B64(); // BRA.W	$0B64
}
ROMFUNC(rom_D84) {
  DEF_ROMLOC(D84) : scroll_update_tiles();                    // BSR.W	$6C5C
  DEF_ROMLOC(D88) : rom_1C7DA();                   // JSR	$0001C7DA
  DEF_ROMLOC(D8E) : rom_1CE84();                   // JSR	$0001CE84
  DEF_ROMLOC(D94) : dplc_process_2();                    // BSR.W	$1656
  DEF_ROMLOC(D98) : tst_mem_16(0xFFFFF614);        // TST.W	$F614
  DEF_ROMLOC(D9C) : if (CCR_EQ) goto rom_DA4;      // BEQ.W	$0DA4
  DEF_ROMLOC(DA0) : sub_tomem_16(0x1, 0xFFFFF614); // SUBQ.W	#$01,$F614
  DEF_ROMLOC(DA4) : return;                        // RTS
}
ROMFUNC(rom_DA6) {
  DEF_ROMLOC(DA6)
      : move_tomem_16(0x100, 0xA11100);           // MOVE.W	#$0100,$00A11100
  DEF_ROMLOC(DAE) : btst_tomem_8(0x0, 0xA11100);  // BTST.B	#$00,$00A11100
  DEF_ROMLOC(DB6) : if (!CCR_EQ) goto rom_DAE;    // BNE.B	$DAE
  DEF_ROMLOC(DB8) : input_read_controllers();                   // BSR.W	$11E6
  DEF_ROMLOC(DBC) : move_toreg_32(0xC00004, &A5); // LEA.L	$00C00004,A5
  DEF_ROMLOC(DC2)
      : move_tomem_32(0x94009340, A5); // MOVE.L	#$94009340,(A5)
  DEF_ROMLOC(DC8)
      : move_tomem_32(0x96FD9580, A5);               // MOVE.L	#$96FD9580,(A5)
  DEF_ROMLOC(DCE) : move_tomem_16(0xFFFF977F, A5);   // MOVE.W	#$977F,(A5)
  DEF_ROMLOC(DD2) : move_tomem_16(0xFFFFC000, A5);   // MOVE.W	#$C000,(A5)
  DEF_ROMLOC(DD6) : move_tomem_16(0x80, 0xFFFFF640); // MOVE.W	#$0080,$F640
  DEF_ROMLOC(DDC)
      : move_tomem_16(read_16(0xFFFFF640), A5);   // MOVE.W	$F640,(A5)
  DEF_ROMLOC(DE0) : move_toreg_32(0xC00004, &A5); // LEA.L	$00C00004,A5
  DEF_ROMLOC(DE6)
      : move_tomem_32(0x94019340, A5); // MOVE.L	#$94019340,(A5)
  DEF_ROMLOC(DEC)
      : move_tomem_32(0x96FC9500, A5);               // MOVE.L	#$96FC9500,(A5)
  DEF_ROMLOC(DF2) : move_tomem_16(0xFFFF977F, A5);   // MOVE.W	#$977F,(A5)
  DEF_ROMLOC(DF6) : move_tomem_16(0x7800, A5);       // MOVE.W	#$7800,(A5)
  DEF_ROMLOC(DFA) : move_tomem_16(0x83, 0xFFFFF640); // MOVE.W	#$0083,$F640
  DEF_ROMLOC(E00)
      : move_tomem_16(read_16(0xFFFFF640), A5);   // MOVE.W	$F640,(A5)
  DEF_ROMLOC(E04) : move_toreg_32(0xC00004, &A5); // LEA.L	$00C00004,A5
  DEF_ROMLOC(E0A)
      : move_tomem_32(0x940193C0, A5); // MOVE.L	#$940193C0,(A5)
  DEF_ROMLOC(E10)
      : move_tomem_32(0x96E69500, A5);               // MOVE.L	#$96E69500,(A5)
  DEF_ROMLOC(E16) : move_tomem_16(0xFFFF977F, A5);   // MOVE.W	#$977F,(A5)
  DEF_ROMLOC(E1A) : move_tomem_16(0x7C00, A5);       // MOVE.W	#$7C00,(A5)
  DEF_ROMLOC(E1E) : move_tomem_16(0x83, 0xFFFFF640); // MOVE.W	#$0083,$F640
  DEF_ROMLOC(E24)
      : move_tomem_16(read_16(0xFFFFF640), A5); // MOVE.W	$F640,(A5)
  DEF_ROMLOC(E28)
      : move_tomem_16(0x0, 0xA11100);             // MOVE.W	#$0000,$00A11100
  DEF_ROMLOC(E30) : rom_496E();                   // BSR.W	$496E
  DEF_ROMLOC(E34) : tst_mem_8(0xFFFFF767);        // TST.B	$F767
  DEF_ROMLOC(E38) : if (CCR_EQ) goto rom_E64;     // BEQ.B	$E64
  DEF_ROMLOC(E3A) : move_toreg_32(0xC00004, &A5); // LEA.L	$00C00004,A5
  DEF_ROMLOC(E40)
      : move_tomem_32(0x94019370, A5); // MOVE.L	#$94019370,(A5)
  DEF_ROMLOC(E46)
      : move_tomem_32(0x96E49500, A5);               // MOVE.L	#$96E49500,(A5)
  DEF_ROMLOC(E4C) : move_tomem_16(0xFFFF977F, A5);   // MOVE.W	#$977F,(A5)
  DEF_ROMLOC(E50) : move_tomem_16(0x7000, A5);       // MOVE.W	#$7000,(A5)
  DEF_ROMLOC(E54) : move_tomem_16(0x83, 0xFFFFF640); // MOVE.W	#$0083,$F640
  DEF_ROMLOC(E5A)
      : move_tomem_16(read_16(0xFFFFF640), A5);    // MOVE.W	$F640,(A5)
  DEF_ROMLOC(E5E) : move_tomem_8(0x0, 0xFFFFF767); // MOVE.B	#$00,$F767
  DEF_ROMLOC(E64) : tst_mem_16(0xFFFFF614);        // TST.W	$F614
  DEF_ROMLOC(E68) : if (CCR_EQ) goto rom_E70;      // BEQ.W	$0E70
  DEF_ROMLOC(E6C) : sub_tomem_16(0x1, 0xFFFFF614); // SUBQ.W	#$01,$F614
  DEF_ROMLOC(E70) : return;                        // RTS
}
ROMFUNC(rom_E72) {
  DEF_ROMLOC(E72)
      : move_tomem_16(0x100, 0xA11100);           // MOVE.W	#$0100,$00A11100
  DEF_ROMLOC(E7A) : btst_tomem_8(0x0, 0xA11100);  // BTST.B	#$00,$00A11100
  DEF_ROMLOC(E82) : if (!CCR_EQ) goto rom_E7A;    // BNE.B	$E7A
  DEF_ROMLOC(E84) : input_read_controllers();                   // BSR.W	$11E6
  DEF_ROMLOC(E88) : tst_mem_8(0xFFFFF64E);        // TST.B	$F64E
  DEF_ROMLOC(E8C) : if (!CCR_EQ) goto rom_EB4;    // BNE.B	$EB4
  DEF_ROMLOC(E8E) : move_toreg_32(0xC00004, &A5); // LEA.L	$00C00004,A5
  DEF_ROMLOC(E94)
      : move_tomem_32(0x94009340, A5); // MOVE.L	#$94009340,(A5)
  DEF_ROMLOC(E9A)
      : move_tomem_32(0x96FD9580, A5);               // MOVE.L	#$96FD9580,(A5)
  DEF_ROMLOC(EA0) : move_tomem_16(0xFFFF977F, A5);   // MOVE.W	#$977F,(A5)
  DEF_ROMLOC(EA4) : move_tomem_16(0xFFFFC000, A5);   // MOVE.W	#$C000,(A5)
  DEF_ROMLOC(EA8) : move_tomem_16(0x80, 0xFFFFF640); // MOVE.W	#$0080,$F640
  DEF_ROMLOC(EAE)
      : move_tomem_16(read_16(0xFFFFF640), A5);   // MOVE.W	$F640,(A5)
  DEF_ROMLOC(EB2) : goto rom_ED8;                 // BRA.B	$ED8
  DEF_ROMLOC(EB4) : move_toreg_32(0xC00004, &A5); // LEA.L	$00C00004,A5
  DEF_ROMLOC(EBA)
      : move_tomem_32(0x94009340, A5); // MOVE.L	#$94009340,(A5)
  DEF_ROMLOC(EC0)
      : move_tomem_32(0x96FD9540, A5);               // MOVE.L	#$96FD9540,(A5)
  DEF_ROMLOC(EC6) : move_tomem_16(0xFFFF977F, A5);   // MOVE.W	#$977F,(A5)
  DEF_ROMLOC(ECA) : move_tomem_16(0xFFFFC000, A5);   // MOVE.W	#$C000,(A5)
  DEF_ROMLOC(ECE) : move_tomem_16(0x80, 0xFFFFF640); // MOVE.W	#$0080,$F640
  DEF_ROMLOC(ED4)
      : move_tomem_16(read_16(0xFFFFF640), A5); // MOVE.W	$F640,(A5)
  DEF_ROMLOC(ED8)
      : move_tomem_16(read_16(0xFFFFF624), A5);   // MOVE.W	$F624,(A5)
  DEF_ROMLOC(EDC) : move_toreg_32(0xC00004, &A5); // LEA.L	$00C00004,A5
  DEF_ROMLOC(EE2)
      : move_tomem_32(0x940193C0, A5); // MOVE.L	#$940193C0,(A5)
  DEF_ROMLOC(EE8)
      : move_tomem_32(0x96E69500, A5);               // MOVE.L	#$96E69500,(A5)
  DEF_ROMLOC(EEE) : move_tomem_16(0xFFFF977F, A5);   // MOVE.W	#$977F,(A5)
  DEF_ROMLOC(EF2) : move_tomem_16(0x7C00, A5);       // MOVE.W	#$7C00,(A5)
  DEF_ROMLOC(EF6) : move_tomem_16(0x83, 0xFFFFF640); // MOVE.W	#$0083,$F640
  DEF_ROMLOC(EFC)
      : move_tomem_16(read_16(0xFFFFF640), A5);   // MOVE.W	$F640,(A5)
  DEF_ROMLOC(F00) : move_toreg_32(0xC00004, &A5); // LEA.L	$00C00004,A5
  DEF_ROMLOC(F06)
      : move_tomem_32(0x94019340, A5); // MOVE.L	#$94019340,(A5)
  DEF_ROMLOC(F0C)
      : move_tomem_32(0x96FC9500, A5);               // MOVE.L	#$96FC9500,(A5)
  DEF_ROMLOC(F12) : move_tomem_16(0xFFFF977F, A5);   // MOVE.W	#$977F,(A5)
  DEF_ROMLOC(F16) : move_tomem_16(0x7800, A5);       // MOVE.W	#$7800,(A5)
  DEF_ROMLOC(F1A) : move_tomem_16(0x83, 0xFFFFF640); // MOVE.W	#$0083,$F640
  DEF_ROMLOC(F20)
      : move_tomem_16(read_16(0xFFFFF640), A5);   // MOVE.W	$F640,(A5)
  DEF_ROMLOC(F24) : tst_mem_8(0xFFFFF767);        // TST.B	$F767
  DEF_ROMLOC(F28) : if (CCR_EQ) goto rom_F54;     // BEQ.B	$F54
  DEF_ROMLOC(F2A) : move_toreg_32(0xC00004, &A5); // LEA.L	$00C00004,A5
  DEF_ROMLOC(F30)
      : move_tomem_32(0x94019370, A5); // MOVE.L	#$94019370,(A5)
  DEF_ROMLOC(F36)
      : move_tomem_32(0x96E49500, A5);               // MOVE.L	#$96E49500,(A5)
  DEF_ROMLOC(F3C) : move_tomem_16(0xFFFF977F, A5);   // MOVE.W	#$977F,(A5)
  DEF_ROMLOC(F40) : move_tomem_16(0x7000, A5);       // MOVE.W	#$7000,(A5)
  DEF_ROMLOC(F44) : move_tomem_16(0x83, 0xFFFFF640); // MOVE.W	#$0083,$F640
  DEF_ROMLOC(F4A)
      : move_tomem_16(read_16(0xFFFFF640), A5);    // MOVE.W	$F640,(A5)
  DEF_ROMLOC(F4E) : move_tomem_8(0x0, 0xFFFFF767); // MOVE.B	#$00,$F767
  DEF_ROMLOC(F54)
      : move_tomem_16(0x0, 0xA11100); // MOVE.W	#$0000,$00A11100
  DEF_ROMLOC(F5C) : D0 = read_32(0xFFF700);
  D1 = read_32(0xFFF704);
  D2 = read_32(0xFFF708);
  D3 = read_32(0xFFF70C);
  D4 = read_32(0xFFF710);
  D5 = read_32(0xFFF714);
  D6 = read_32(0xFFF718);
  D7 = read_32(0xFFF71C);
  // TODO; // MOVEM.L	$F700,D0-D7
  DEF_ROMLOC(F62) : write_32(0xFFFF10, D0);
  write_32(0xFFFF14, D1);
  write_32(0xFFFF18, D2);
  write_32(0xFFFF1C, D3);
  write_32(0xFFFF20, D4);
  write_32(0xFFFF24, D5);
  write_32(0xFFFF28, D6);
  write_32(0xFFFF2C, D7);
  // TODO; // MOVEM.L	D0-D7,$FF10
  DEF_ROMLOC(F68) : D0 = read_32(0xFFF754);
  D1 = read_32(0xFFF758);
  // TODO; // MOVEM.L	$F754,D0-D1
  DEF_ROMLOC(F6E) : write_32(0xFFFF30, D0);
  write_32(0xFFFF34, D1);
  // TODO; // MOVEM.L	D0-D1,$FF30
  DEF_ROMLOC(F74) : scroll_update_tiles();  // BSR.W	$6C5C
  DEF_ROMLOC(F78) : rom_1C7DA(); // JSR	$0001C7DA
  DEF_ROMLOC(F7E) : rom_1CE84(); // JSR	$0001CE84
  DEF_ROMLOC(F84) : plc_refresh_frame();  // BSR.W	$163A
  DEF_ROMLOC(F88) : return;      // RTS
}
ROMFUNC(rom_F8A) {
  DEF_ROMLOC(F8A) : rom_106E();                    // BSR.W	$106E
  DEF_ROMLOC(F8E) : add_tomem_8(0x1, 0xFFFFF628);  // ADDQ.B	#$01,$F628
  DEF_ROMLOC(F92) : move_tomem_8(0xE, 0xFFFFF62A); // MOVE.B	#$0E,$F62A
  DEF_ROMLOC(F98) : return;                        // RTS
}
ROMFUNC(rom_F9A) {
  DEF_ROMLOC(F9A) : rom_106E(); // BSR.W	$106E
  DEF_ROMLOC(F9E)
      : move_tomem_16(read_16(0xFFFFF624), A5); // MOVE.W	$F624,(A5)
  plc_refresh_frame();                                   // BRA.W	$163A
}
ROMFUNC(rom_FA6) {
  DEF_ROMLOC(FA6)
      : move_tomem_16(0x100, 0xA11100);           // MOVE.W	#$0100,$00A11100
  DEF_ROMLOC(FAE) : btst_tomem_8(0x0, 0xA11100);  // BTST.B	#$00,$00A11100
  DEF_ROMLOC(FB6) : if (!CCR_EQ) goto rom_FAE;    // BNE.B	$FAE
  DEF_ROMLOC(FB8) : input_read_controllers();                   // BSR.W	$11E6
  DEF_ROMLOC(FBC) : move_toreg_32(0xC00004, &A5); // LEA.L	$00C00004,A5
  DEF_ROMLOC(FC2)
      : move_tomem_32(0x94009340, A5); // MOVE.L	#$94009340,(A5)
  DEF_ROMLOC(FC8)
      : move_tomem_32(0x96FD9580, A5);               // MOVE.L	#$96FD9580,(A5)
  DEF_ROMLOC(FCE) : move_tomem_16(0xFFFF977F, A5);   // MOVE.W	#$977F,(A5)
  DEF_ROMLOC(FD2) : move_tomem_16(0xFFFFC000, A5);   // MOVE.W	#$C000,(A5)
  DEF_ROMLOC(FD6) : move_tomem_16(0x80, 0xFFFFF640); // MOVE.W	#$0080,$F640
  DEF_ROMLOC(FDC)
      : move_tomem_16(read_16(0xFFFFF640), A5);   // MOVE.W	$F640,(A5)
  DEF_ROMLOC(FE0) : move_toreg_32(0xC00004, &A5); // LEA.L	$00C00004,A5
  DEF_ROMLOC(FE6)
      : move_tomem_32(0x94019340, A5); // MOVE.L	#$94019340,(A5)
  DEF_ROMLOC(FEC)
      : move_tomem_32(0x96FC9500, A5);               // MOVE.L	#$96FC9500,(A5)
  DEF_ROMLOC(FF2) : move_tomem_16(0xFFFF977F, A5);   // MOVE.W	#$977F,(A5)
  DEF_ROMLOC(FF6) : move_tomem_16(0x7800, A5);       // MOVE.W	#$7800,(A5)
  DEF_ROMLOC(FFA) : move_tomem_16(0x83, 0xFFFFF640); // MOVE.W	#$0083,$F640
  DEF_ROMLOC(1000)
      : move_tomem_16(read_16(0xFFFFF640), A5);    // MOVE.W	$F640,(A5)
  DEF_ROMLOC(1004) : move_toreg_32(0xC00004, &A5); // LEA.L	$00C00004,A5
  DEF_ROMLOC(100A)
      : move_tomem_32(0x940193C0, A5); // MOVE.L	#$940193C0,(A5)
  DEF_ROMLOC(1010)
      : move_tomem_32(0x96E69500, A5);                // MOVE.L	#$96E69500,(A5)
  DEF_ROMLOC(1016) : move_tomem_16(0xFFFF977F, A5);   // MOVE.W	#$977F,(A5)
  DEF_ROMLOC(101A) : move_tomem_16(0x7C00, A5);       // MOVE.W	#$7C00,(A5)
  DEF_ROMLOC(101E) : move_tomem_16(0x83, 0xFFFFF640); // MOVE.W	#$0083,$F640
  DEF_ROMLOC(1024)
      : move_tomem_16(read_16(0xFFFFF640), A5); // MOVE.W	$F640,(A5)
  DEF_ROMLOC(1028)
      : move_tomem_16(0x0, 0xA11100);              // MOVE.W	#$0000,$00A11100
  DEF_ROMLOC(1030) : tst_mem_8(0xFFFFF767);        // TST.B	$F767
  DEF_ROMLOC(1034) : if (CCR_EQ) goto rom_1060;    // BEQ.B	$1060
  DEF_ROMLOC(1036) : move_toreg_32(0xC00004, &A5); // LEA.L	$00C00004,A5
  DEF_ROMLOC(103C)
      : move_tomem_32(0x94019370, A5); // MOVE.L	#$94019370,(A5)
  DEF_ROMLOC(1042)
      : move_tomem_32(0x96E49500, A5);                // MOVE.L	#$96E49500,(A5)
  DEF_ROMLOC(1048) : move_tomem_16(0xFFFF977F, A5);   // MOVE.W	#$977F,(A5)
  DEF_ROMLOC(104C) : move_tomem_16(0x7000, A5);       // MOVE.W	#$7000,(A5)
  DEF_ROMLOC(1050) : move_tomem_16(0x83, 0xFFFFF640); // MOVE.W	#$0083,$F640
  DEF_ROMLOC(1056)
      : move_tomem_16(read_16(0xFFFFF640), A5);     // MOVE.W	$F640,(A5)
  DEF_ROMLOC(105A) : move_tomem_8(0x0, 0xFFFFF767); // MOVE.B	#$00,$F767
  DEF_ROMLOC(1060) : tst_mem_16(0xFFFFF614);        // TST.W	$F614
  DEF_ROMLOC(1064) : if (CCR_EQ) goto rom_106C;     // BEQ.W	$106C
  DEF_ROMLOC(1068) : sub_tomem_16(0x1, 0xFFFFF614); // SUBQ.W	#$01,$F614
  DEF_ROMLOC(106C) : return;                        // RTS
}
ROMFUNC(rom_106E) {
  DEF_ROMLOC(106E)
      : move_tomem_16(0x100, 0xA11100); // MOVE.W	#$0100,$00A11100
  DEF_ROMLOC(1076)
      : btst_tomem_8(0x0, 0xA11100);               // BTST.B	#$00,$00A11100
  DEF_ROMLOC(107E) : if (!CCR_EQ) goto rom_1076;   // BNE.B	$1076
  DEF_ROMLOC(1080) : input_read_controllers();                   // BSR.W	$11E6
  DEF_ROMLOC(1084) : tst_mem_8(0xFFFFF64E);        // TST.B	$F64E
  DEF_ROMLOC(1088) : if (!CCR_EQ) goto rom_10B0;   // BNE.B	$10B0
  DEF_ROMLOC(108A) : move_toreg_32(0xC00004, &A5); // LEA.L	$00C00004,A5
  DEF_ROMLOC(1090)
      : move_tomem_32(0x94009340, A5); // MOVE.L	#$94009340,(A5)
  DEF_ROMLOC(1096)
      : move_tomem_32(0x96FD9580, A5);                // MOVE.L	#$96FD9580,(A5)
  DEF_ROMLOC(109C) : move_tomem_16(0xFFFF977F, A5);   // MOVE.W	#$977F,(A5)
  DEF_ROMLOC(10A0) : move_tomem_16(0xFFFFC000, A5);   // MOVE.W	#$C000,(A5)
  DEF_ROMLOC(10A4) : move_tomem_16(0x80, 0xFFFFF640); // MOVE.W	#$0080,$F640
  DEF_ROMLOC(10AA)
      : move_tomem_16(read_16(0xFFFFF640), A5);    // MOVE.W	$F640,(A5)
  DEF_ROMLOC(10AE) : goto rom_10D4;                // BRA.B	$10D4
  DEF_ROMLOC(10B0) : move_toreg_32(0xC00004, &A5); // LEA.L	$00C00004,A5
  DEF_ROMLOC(10B6)
      : move_tomem_32(0x94009340, A5); // MOVE.L	#$94009340,(A5)
  DEF_ROMLOC(10BC)
      : move_tomem_32(0x96FD9540, A5);                // MOVE.L	#$96FD9540,(A5)
  DEF_ROMLOC(10C2) : move_tomem_16(0xFFFF977F, A5);   // MOVE.W	#$977F,(A5)
  DEF_ROMLOC(10C6) : move_tomem_16(0xFFFFC000, A5);   // MOVE.W	#$C000,(A5)
  DEF_ROMLOC(10CA) : move_tomem_16(0x80, 0xFFFFF640); // MOVE.W	#$0080,$F640
  DEF_ROMLOC(10D0)
      : move_tomem_16(read_16(0xFFFFF640), A5);    // MOVE.W	$F640,(A5)
  DEF_ROMLOC(10D4) : move_toreg_32(0xC00004, &A5); // LEA.L	$00C00004,A5
  DEF_ROMLOC(10DA)
      : move_tomem_32(0x94019340, A5); // MOVE.L	#$94019340,(A5)
  DEF_ROMLOC(10E0)
      : move_tomem_32(0x96FC9500, A5);                // MOVE.L	#$96FC9500,(A5)
  DEF_ROMLOC(10E6) : move_tomem_16(0xFFFF977F, A5);   // MOVE.W	#$977F,(A5)
  DEF_ROMLOC(10EA) : move_tomem_16(0x7800, A5);       // MOVE.W	#$7800,(A5)
  DEF_ROMLOC(10EE) : move_tomem_16(0x83, 0xFFFFF640); // MOVE.W	#$0083,$F640
  DEF_ROMLOC(10F4)
      : move_tomem_16(read_16(0xFFFFF640), A5);    // MOVE.W	$F640,(A5)
  DEF_ROMLOC(10F8) : move_toreg_32(0xC00004, &A5); // LEA.L	$00C00004,A5
  DEF_ROMLOC(10FE)
      : move_tomem_32(0x940193C0, A5); // MOVE.L	#$940193C0,(A5)
  DEF_ROMLOC(1104)
      : move_tomem_32(0x96E69500, A5);                // MOVE.L	#$96E69500,(A5)
  DEF_ROMLOC(110A) : move_tomem_16(0xFFFF977F, A5);   // MOVE.W	#$977F,(A5)
  DEF_ROMLOC(110E) : move_tomem_16(0x7C00, A5);       // MOVE.W	#$7C00,(A5)
  DEF_ROMLOC(1112) : move_tomem_16(0x83, 0xFFFFF640); // MOVE.W	#$0083,$F640
  DEF_ROMLOC(1118)
      : move_tomem_16(read_16(0xFFFFF640), A5); // MOVE.W	$F640,(A5)
  DEF_ROMLOC(111C)
      : move_tomem_16(0x0, 0xA11100); // MOVE.W	#$0000,$00A11100
  DEF_ROMLOC(1124) : return;          // RTS
}
ROMFUNC(rom_1126) {
  DEF_ROMLOC(1126) : move_tosr_16(0x2700, &SR);      // MOVE.W	#$2700,SR
  DEF_ROMLOC(112A) : tst_mem_16(0xFFFFF644);         // TST.W	$F644
  DEF_ROMLOC(112E) : if (CCR_EQ) goto rom_119C;      // BEQ.B	$119C
  DEF_ROMLOC(1130) : move_tomem_16(0x0, 0xFFFFF644); // MOVE.W	#$0000,$F644
  DEF_ROMLOC(1136) : a0backup = A0;
  a1backup = A1; // TODO; // MOVEM.L	A0-A1,-(A7)
  DEF_ROMLOC(113A) : move_toreg_32(0xC00000, &A1);   // LEA.L	$00C00000,A1
  DEF_ROMLOC(1140) : move_toreg_32(0xFFFFFA80, &A0); // LEA.L	$FA80,A0
  DEF_ROMLOC(1144)
      : move_tomem_32(0xC0000000, A1 + 0x4); // MOVE.L	#$C0000000,4(A1)
  DEF_ROMLOC(114C)
      : move_tomem_32(read_32((A0 += 4, A0 - 4)),
                      A1); // MOVE.L	(A0)+,(A1)
  DEF_ROMLOC(114E)
      : move_tomem_32(read_32((A0 += 4, A0 - 4)),
                      A1); // MOVE.L	(A0)+,(A1)
  DEF_ROMLOC(1150)
      : move_tomem_32(read_32((A0 += 4, A0 - 4)),
                      A1); // MOVE.L	(A0)+,(A1)
  DEF_ROMLOC(1152)
      : move_tomem_32(read_32((A0 += 4, A0 - 4)),
                      A1); // MOVE.L	(A0)+,(A1)
  DEF_ROMLOC(1154)
      : move_tomem_32(read_32((A0 += 4, A0 - 4)),
                      A1); // MOVE.L	(A0)+,(A1)
  DEF_ROMLOC(1156)
      : move_tomem_32(read_32((A0 += 4, A0 - 4)),
                      A1); // MOVE.L	(A0)+,(A1)
  DEF_ROMLOC(1158)
      : move_tomem_32(read_32((A0 += 4, A0 - 4)),
                      A1); // MOVE.L	(A0)+,(A1)
  DEF_ROMLOC(115A)
      : move_tomem_32(read_32((A0 += 4, A0 - 4)),
                      A1); // MOVE.L	(A0)+,(A1)
  DEF_ROMLOC(115C)
      : move_tomem_32(read_32((A0 += 4, A0 - 4)),
                      A1); // MOVE.L	(A0)+,(A1)
  DEF_ROMLOC(115E)
      : move_tomem_32(read_32((A0 += 4, A0 - 4)),
                      A1); // MOVE.L	(A0)+,(A1)
  DEF_ROMLOC(1160)
      : move_tomem_32(read_32((A0 += 4, A0 - 4)),
                      A1); // MOVE.L	(A0)+,(A1)
  DEF_ROMLOC(1162)
      : move_tomem_32(read_32((A0 += 4, A0 - 4)),
                      A1); // MOVE.L	(A0)+,(A1)
  DEF_ROMLOC(1164)
      : move_tomem_32(read_32((A0 += 4, A0 - 4)),
                      A1); // MOVE.L	(A0)+,(A1)
  DEF_ROMLOC(1166)
      : move_tomem_32(read_32((A0 += 4, A0 - 4)),
                      A1); // MOVE.L	(A0)+,(A1)
  DEF_ROMLOC(1168)
      : move_tomem_32(read_32((A0 += 4, A0 - 4)),
                      A1); // MOVE.L	(A0)+,(A1)
  DEF_ROMLOC(116A)
      : move_tomem_32(read_32((A0 += 4, A0 - 4)),
                      A1); // MOVE.L	(A0)+,(A1)
  DEF_ROMLOC(116C)
      : move_tomem_32(read_32((A0 += 4, A0 - 4)),
                      A1); // MOVE.L	(A0)+,(A1)
  DEF_ROMLOC(116E)
      : move_tomem_32(read_32((A0 += 4, A0 - 4)),
                      A1); // MOVE.L	(A0)+,(A1)
  DEF_ROMLOC(1170)
      : move_tomem_32(read_32((A0 += 4, A0 - 4)),
                      A1); // MOVE.L	(A0)+,(A1)
  DEF_ROMLOC(1172)
      : move_tomem_32(read_32((A0 += 4, A0 - 4)),
                      A1); // MOVE.L	(A0)+,(A1)
  DEF_ROMLOC(1174)
      : move_tomem_32(read_32((A0 += 4, A0 - 4)),
                      A1); // MOVE.L	(A0)+,(A1)
  DEF_ROMLOC(1176)
      : move_tomem_32(read_32((A0 += 4, A0 - 4)),
                      A1); // MOVE.L	(A0)+,(A1)
  DEF_ROMLOC(1178)
      : move_tomem_32(read_32((A0 += 4, A0 - 4)),
                      A1); // MOVE.L	(A0)+,(A1)
  DEF_ROMLOC(117A)
      : move_tomem_32(read_32((A0 += 4, A0 - 4)),
                      A1); // MOVE.L	(A0)+,(A1)
  DEF_ROMLOC(117C)
      : move_tomem_32(read_32((A0 += 4, A0 - 4)),
                      A1); // MOVE.L	(A0)+,(A1)
  DEF_ROMLOC(117E)
      : move_tomem_32(read_32((A0 += 4, A0 - 4)),
                      A1); // MOVE.L	(A0)+,(A1)
  DEF_ROMLOC(1180)
      : move_tomem_32(read_32((A0 += 4, A0 - 4)),
                      A1); // MOVE.L	(A0)+,(A1)
  DEF_ROMLOC(1182)
      : move_tomem_32(read_32((A0 += 4, A0 - 4)),
                      A1); // MOVE.L	(A0)+,(A1)
  DEF_ROMLOC(1184)
      : move_tomem_32(read_32((A0 += 4, A0 - 4)),
                      A1); // MOVE.L	(A0)+,(A1)
  DEF_ROMLOC(1186)
      : move_tomem_32(read_32((A0 += 4, A0 - 4)),
                      A1); // MOVE.L	(A0)+,(A1)
  DEF_ROMLOC(1188)
      : move_tomem_32(read_32((A0 += 4, A0 - 4)),
                      A1); // MOVE.L	(A0)+,(A1)
  DEF_ROMLOC(118A)
      : move_tomem_32(read_32((A0 += 4, A0 - 4)),
                      A1); // MOVE.L	(A0)+,(A1)
  DEF_ROMLOC(118C)
      : move_tomem_16(0xFFFF8ADF, A1 + 0x4); // MOVE.W	#$8ADF,4(A1)
  DEF_ROMLOC(1192) : A0 = a0backup;
  A1 = a1backup;                                 // TODO; // MOVEM.L	(A7)+,A0-A1
  DEF_ROMLOC(1196) : tst_mem_8(0xFFFFF64F);      // TST.B	$F64F
  DEF_ROMLOC(119A) : if (!CCR_EQ) goto rom_119E; // BNE.B	$119E
  DEF_ROMLOC(119C) : return;                     // RTE
  DEF_ROMLOC(119E) : clr_mem_8(0xFFFFF64F);      // CLR.B	$F64F
  DEF_ROMLOC(11A2) : d0backup = D0;
  d1backup = D1;
  d2backup = D2;
  d3backup = D3;
  d4backup = D4;
  d5backup = D5;
  d6backup = D6;
  d7backup = D7;
  a0backup = A0;
  a1backup = A1;
  a2backup = A2;
  a3backup = A3;
  a4backup = A4;
  a5backup = A5;
  a6backup = A6;
  // TODO; // MOVEM.L	D0-A6,-(A7)
  DEF_ROMLOC(11A6) : rom_D84(); // BSR.W	$0D84
  update_sound_driver();
  DEF_ROMLOC(11B0) : D0 = d0backup;
  D1 = d1backup;
  D2 = d2backup;
  D3 = d3backup;
  D4 = d4backup;
  D5 = d5backup;
  D6 = d6backup;
  D7 = d7backup;
  A0 = a0backup;
  A1 = a1backup;
  A2 = a2backup;
  A3 = a3backup;
  A4 = a4backup;
  A5 = a5backup;
  A6 = a6backup;
  // TODO; // MOVEM.L	(A7)+,D0-A6
  DEF_ROMLOC(11B4) : return; // RTE
}
void end_frame(u8 routine) {
  move_tomem_8(routine, 0xFFFFF62A);
  exit_mainloop = true;                                                        
}