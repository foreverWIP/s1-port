// #define CHECK_STUFF 1
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
  DEF_ROMLOC(B20)
      : write_vdp_control_32(0x40000010);
  DEF_ROMLOC(B2A)
      : write_vdp_data_32(read_32(0xFFFFF616));
  DEF_ROMLOC(B42) : move_toreg_8(read_8(0xFFFFF62A), &D0); // MOVE.B	$F62A,D0
  DEF_ROMLOC(B46) : move_tomem_8(0x0, 0xFFFFF62A);         // MOVE.B	#$00,$F62A
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
  DEF_ROMLOC(B8E) : if (v_gamemode == (GM_TITLECARD_FLAG | GM_LEVEL)) goto rom_B9A;                  // BEQ.B	$B9A
  DEF_ROMLOC(B96) : if (v_gamemode != GM_LEVEL) {
    rom_B5E();
    return;
  } // BNE.W	$0B5E
  DEF_ROMLOC(B9A) : cmp_tomem_8(ZONE_LZ, v_zone); // CMPI.B	#$01,$FE10
  DEF_ROMLOC(BA0) : if (!CCR_EQ) {
    rom_B5E();
    return;
  } // BNE.W	$0B5E
  DEF_ROMLOC(BBA) : move_tomem_16(0x1, 0xFFFFF644); // MOVE.W	#$0001,$F644
  DEF_ROMLOC(BD2) : tst_mem_8(0xFFFFF64E);          // TST.B	$F64E
  DEF_ROMLOC(BD6) : if (!CCR_EQ) goto rom_BFE;      // BNE.B	$BFE
  DEF_ROMLOC(BD8)
      : move_toreg_32(VDP_CONTROL_PORT, &A5);        // LEA.L	$00C00004,A5
  DEF_ROMLOC(BDE) : set_vdp_register(0x94, 0x00);
  					set_vdp_register(0x93, 0x40);
  DEF_ROMLOC(BE4) : set_vdp_register(0x96, 0xFD);
  					set_vdp_register(0x95, 0x80);
  DEF_ROMLOC(BEA) : set_vdp_register(0x97, 0x7F);
  DEF_ROMLOC(BEE) : write_vdp_control_16(0xC000);
  DEF_ROMLOC(BF2) : move_tomem_16(0x80, 0xFFFFF640); // MOVE.W	#$0080,$F640
  DEF_ROMLOC(BF8)
      : write_vdp_control_16(read_16(0xFFFFF640));
  DEF_ROMLOC(BFC) : goto rom_C22;               // BRA.B	$C22
  DEF_ROMLOC(BFE)
      : move_toreg_32(VDP_CONTROL_PORT, &A5);        // LEA.L	$00C00004,A5
  DEF_ROMLOC(C04) : set_vdp_register(0x94, 0x00);
  					set_vdp_register(0x93, 0x40);
  DEF_ROMLOC(C0A) : set_vdp_register(0x96, 0xFD);
  					set_vdp_register(0x95, 0x40);
  DEF_ROMLOC(C10) : set_vdp_register(0x97, 0x7F);
  DEF_ROMLOC(C14) : write_vdp_control_16(0xC000);
  DEF_ROMLOC(C18) : move_tomem_16(0x80, 0xFFFFF640); // MOVE.W	#$0080,$F640
  DEF_ROMLOC(C1E)
      : write_vdp_control_16(read_16(0xFFFFF640));
  DEF_ROMLOC(C22)
      : write_vdp_control_16(read_16(0xFFFFF624));
  rom_B5E();                                      // BRA.W	$0B5E
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
  DEF_ROMLOC(C48) : scroll_update_tiles_bg();      // BSR.W	$6C30
  DEF_ROMLOC(C4C) : plc_refresh_frame();           // BSR.W	$163A
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
  DEF_ROMLOC(C6A) : if (v_gamemode == GM_SPECIAL) {
    rom_DA6();
    return;
  } // BEQ.W	$0DA6
  rom_C6E(); // Detected flow into next function
}
ROMFUNC(rom_C6E) {
  DEF_ROMLOC(C80) : input_read_controllers();       // BSR.W	$11E6
  DEF_ROMLOC(C84) : tst_mem_8(0xFFFFF64E);          // TST.B	$F64E
  DEF_ROMLOC(C88) : if (!CCR_EQ) goto rom_CB0;      // BNE.B	$CB0
  DEF_ROMLOC(C8A)
      : move_toreg_32(VDP_CONTROL_PORT, &A5);        // LEA.L	$00C00004,A5
  DEF_ROMLOC(C90) : set_vdp_register(0x94, 0x00);
  					set_vdp_register(0x93, 0x40);
  DEF_ROMLOC(C96) : set_vdp_register(0x96, 0xFD);
  					set_vdp_register(0x95, 0x80);
  DEF_ROMLOC(C9C) : set_vdp_register(0x97, 0x7F);
  DEF_ROMLOC(CA0) : write_vdp_control_16(0xC000);
  DEF_ROMLOC(CA4) : move_tomem_16(0x80, 0xFFFFF640); // MOVE.W	#$0080,$F640
  DEF_ROMLOC(CAA)
      : write_vdp_control_16(read_16(0xFFFFF640));
  DEF_ROMLOC(CAE) : goto rom_CD4;               // BRA.B	$CD4
  DEF_ROMLOC(CB0)
      : move_toreg_32(VDP_CONTROL_PORT, &A5);        // LEA.L	$00C00004,A5
  DEF_ROMLOC(CB6) : set_vdp_register(0x94, 0x00);
  					set_vdp_register(0x93, 0x40);
  DEF_ROMLOC(CBC) : set_vdp_register(0x96, 0xFD);
  					set_vdp_register(0x95, 0x40);
  DEF_ROMLOC(CC2) : set_vdp_register(0x97, 0x7F);
  DEF_ROMLOC(CC6) : write_vdp_control_16(0xC000);
  DEF_ROMLOC(CCA) : move_tomem_16(0x80, 0xFFFFF640); // MOVE.W	#$0080,$F640
  DEF_ROMLOC(CD0)
      : write_vdp_control_16(read_16(0xFFFFF640));
  DEF_ROMLOC(CD4)
      : write_vdp_control_16(read_16(0xFFFFF624));
  DEF_ROMLOC(CD8)
      : move_toreg_32(VDP_CONTROL_PORT, &A5);        // LEA.L	$00C00004,A5
  DEF_ROMLOC(CDE) : set_vdp_register(0x94, 0x01);
  					set_vdp_register(0x93, 0xC0);
  DEF_ROMLOC(CE4) : set_vdp_register(0x96, 0xE6);
  					set_vdp_register(0x95, 0x00);
  DEF_ROMLOC(CEA) : set_vdp_register(0x97, 0x7F);
  DEF_ROMLOC(CEE) : write_vdp_control_16(0x7C00);
  DEF_ROMLOC(CF2) : move_tomem_16(0x83, 0xFFFFF640); // MOVE.W	#$0083,$F640
  DEF_ROMLOC(CF8)
      : write_vdp_control_16(read_16(0xFFFFF640));
  DEF_ROMLOC(CFC)
      : move_toreg_32(VDP_CONTROL_PORT, &A5);        // LEA.L	$00C00004,A5
  DEF_ROMLOC(D02) : set_vdp_register(0x94, 0x01);
  					set_vdp_register(0x93, 0x40);
  DEF_ROMLOC(D08) : set_vdp_register(0x96, 0xFC);
  					set_vdp_register(0x95, 0x00);
  DEF_ROMLOC(D0E) : set_vdp_register(0x97, 0x7F);
  DEF_ROMLOC(D12) : write_vdp_control_16(0x7800);
  DEF_ROMLOC(D16) : move_tomem_16(0x83, 0xFFFFF640); // MOVE.W	#$0083,$F640
  DEF_ROMLOC(D1C)
      : write_vdp_control_16(read_16(0xFFFFF640));
  DEF_ROMLOC(D20) : tst_mem_8(0xFFFFF767);      // TST.B	$F767
  DEF_ROMLOC(D24) : if (CCR_EQ) goto rom_D50;   // BEQ.B	$D50
  DEF_ROMLOC(D26)
      : move_toreg_32(VDP_CONTROL_PORT, &A5);        // LEA.L	$00C00004,A5
  DEF_ROMLOC(D2C) : set_vdp_register(0x94, 0x01);
  					set_vdp_register(0x93, 0x70);
  DEF_ROMLOC(D32) : set_vdp_register(0x96, 0xE4);
  					set_vdp_register(0x95, 0x00);
  DEF_ROMLOC(D38) : set_vdp_register(0x97, 0x7F);
  DEF_ROMLOC(D3C) : write_vdp_control_16(0x7000);
  DEF_ROMLOC(D40) : move_tomem_16(0x83, 0xFFFFF640); // MOVE.W	#$0083,$F640
  DEF_ROMLOC(D46)
      : write_vdp_control_16(read_16(0xFFFFF640));
  DEF_ROMLOC(D50) :
  DEF_ROMLOC(D4A) : move_tomem_8(0x0, 0xFFFFF767); // MOVE.B	#$00,$F767
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
  } // BCC.B	$D84
  DEF_ROMLOC(D78) : move_tomem_8(0x1, 0xFFFFF64F); // MOVE.B	#$01,$F64F
  // DEF_ROMLOC(D7E): // TODO; // ADDQ.L	#$04,A7
  // rom_B64(); // BRA.W	$0B64
}
ROMFUNC(rom_D84) {
  DEF_ROMLOC(D84) : scroll_update_tiles();         // BSR.W	$6C5C
  DEF_ROMLOC(D88) : rom_1C7DA();                   // JSR	$0001C7DA
  DEF_ROMLOC(D8E) : rom_1CE84();                   // JSR	$0001CE84
  DEF_ROMLOC(D94) : dplc_process_2();              // BSR.W	$1656
  DEF_ROMLOC(D98) : tst_mem_16(0xFFFFF614);        // TST.W	$F614
  DEF_ROMLOC(D9C) : if (CCR_EQ) goto rom_DA4;      // BEQ.W	$0DA4
  DEF_ROMLOC(DA0) : sub_tomem_16(0x1, 0xFFFFF614); // SUBQ.W	#$01,$F614
  DEF_ROMLOC(DA4) : return;                        // RTS
}
ROMFUNC(rom_DA6) {
  DEF_ROMLOC(DB8) : input_read_controllers();       // BSR.W	$11E6
  DEF_ROMLOC(DBC)
      : move_toreg_32(VDP_CONTROL_PORT, &A5);        // LEA.L	$00C00004,A5
  DEF_ROMLOC(DC2) : set_vdp_register(0x94, 0x00);
  					set_vdp_register(0x93, 0x40);
  DEF_ROMLOC(DC8) : set_vdp_register(0x96, 0xFD);
  					set_vdp_register(0x95, 0x80);
  DEF_ROMLOC(DCE) : set_vdp_register(0x97, 0x7F);
  DEF_ROMLOC(DD2) : write_vdp_control_16(0xC000);
  DEF_ROMLOC(DD6) : move_tomem_16(0x80, 0xFFFFF640); // MOVE.W	#$0080,$F640
  DEF_ROMLOC(DDC)
      : write_vdp_control_16(read_16(0xFFFFF640));
  DEF_ROMLOC(DE0)
      : move_toreg_32(VDP_CONTROL_PORT, &A5);        // LEA.L	$00C00004,A5
  DEF_ROMLOC(DE6) : set_vdp_register(0x94, 0x01);
  					set_vdp_register(0x93, 0x40);
  DEF_ROMLOC(DEC) : set_vdp_register(0x96, 0xFC);
  					set_vdp_register(0x95, 0x00);
  DEF_ROMLOC(DF2) : set_vdp_register(0x97, 0x7F);
  DEF_ROMLOC(DF6) : write_vdp_control_16(0x7800);
  DEF_ROMLOC(DFA) : move_tomem_16(0x83, 0xFFFFF640); // MOVE.W	#$0083,$F640
  DEF_ROMLOC(E00)
      : write_vdp_control_16(read_16(0xFFFFF640));
  DEF_ROMLOC(E04)
      : move_toreg_32(VDP_CONTROL_PORT, &A5);        // LEA.L	$00C00004,A5
  DEF_ROMLOC(E0A) : set_vdp_register(0x94, 0x01);
  					set_vdp_register(0x93, 0xC0);
  DEF_ROMLOC(E10) : set_vdp_register(0x96, 0xE6);
  					set_vdp_register(0x95, 0x00);
  DEF_ROMLOC(E16) : set_vdp_register(0x97, 0x7F);
  DEF_ROMLOC(E1A) : write_vdp_control_16(0x7C00);
  DEF_ROMLOC(E1E) : move_tomem_16(0x83, 0xFFFFF640); // MOVE.W	#$0083,$F640
  DEF_ROMLOC(E24)
      : write_vdp_control_16(read_16(0xFFFFF640));
  DEF_ROMLOC(E30) : rom_496E();                   // BSR.W	$496E
  DEF_ROMLOC(E34) : tst_mem_8(0xFFFFF767);        // TST.B	$F767
  DEF_ROMLOC(E38) : if (CCR_EQ) goto rom_E64;     // BEQ.B	$E64
  DEF_ROMLOC(E3A)
      : move_toreg_32(VDP_CONTROL_PORT, &A5);        // LEA.L	$00C00004,A5
  DEF_ROMLOC(E40) : set_vdp_register(0x94, 0x01);
  					set_vdp_register(0x93, 0x70);
  DEF_ROMLOC(E46) : set_vdp_register(0x96, 0xE4);
  					set_vdp_register(0x95, 0x00);
  DEF_ROMLOC(E4C) : set_vdp_register(0x97, 0x7F);
  DEF_ROMLOC(E50) : write_vdp_control_16(0x7000);
  DEF_ROMLOC(E54) : move_tomem_16(0x83, 0xFFFFF640); // MOVE.W	#$0083,$F640
  DEF_ROMLOC(E5A)
      : write_vdp_control_16(read_16(0xFFFFF640));
  DEF_ROMLOC(E5E) : move_tomem_8(0x0, 0xFFFFF767); // MOVE.B	#$00,$F767
  DEF_ROMLOC(E64) : tst_mem_16(0xFFFFF614);        // TST.W	$F614
  DEF_ROMLOC(E68) : if (CCR_EQ) goto rom_E70;      // BEQ.W	$0E70
  DEF_ROMLOC(E6C) : sub_tomem_16(0x1, 0xFFFFF614); // SUBQ.W	#$01,$F614
  DEF_ROMLOC(E70) : return;                        // RTS
}
ROMFUNC(rom_E72) {
  DEF_ROMLOC(E84) : input_read_controllers();       // BSR.W	$11E6
  DEF_ROMLOC(E88) : tst_mem_8(0xFFFFF64E);          // TST.B	$F64E
  DEF_ROMLOC(E8C) : if (!CCR_EQ) goto rom_EB4;      // BNE.B	$EB4
  DEF_ROMLOC(E8E)
      : move_toreg_32(VDP_CONTROL_PORT, &A5);        // LEA.L	$00C00004,A5
  DEF_ROMLOC(E94) : set_vdp_register(0x94, 0x00);
  					set_vdp_register(0x93, 0x40);
  DEF_ROMLOC(E9A) : set_vdp_register(0x96, 0xFD);
  					set_vdp_register(0x95, 0x80);
  DEF_ROMLOC(EA0) : set_vdp_register(0x97, 0x7F);
  DEF_ROMLOC(EA4) : write_vdp_control_16(0xC000);
  DEF_ROMLOC(EA8) : move_tomem_16(0x80, 0xFFFFF640); // MOVE.W	#$0080,$F640
  DEF_ROMLOC(EAE)
      : write_vdp_control_16(read_16(0xFFFFF640));
  DEF_ROMLOC(EB2) : goto rom_ED8;               // BRA.B	$ED8
  DEF_ROMLOC(EB4)
      : move_toreg_32(VDP_CONTROL_PORT, &A5);        // LEA.L	$00C00004,A5
  DEF_ROMLOC(EBA) : set_vdp_register(0x94, 0x00);
  					set_vdp_register(0x93, 0x40);
  DEF_ROMLOC(EC0) : set_vdp_register(0x96, 0xFD);
  					set_vdp_register(0x95, 0x40);
  DEF_ROMLOC(EC6) : set_vdp_register(0x97, 0x7F);
  DEF_ROMLOC(ECA) : write_vdp_control_16(0xC000);
  DEF_ROMLOC(ECE) : move_tomem_16(0x80, 0xFFFFF640); // MOVE.W	#$0080,$F640
  DEF_ROMLOC(ED4)
      : write_vdp_control_16(read_16(0xFFFFF640));
  DEF_ROMLOC(ED8)
      : write_vdp_control_16(read_16(0xFFFFF624));
  DEF_ROMLOC(EDC)
      : move_toreg_32(VDP_CONTROL_PORT, &A5);        // LEA.L	$00C00004,A5
  DEF_ROMLOC(EE2) : set_vdp_register(0x94, 0x01);
  					set_vdp_register(0x93, 0xC0);
  DEF_ROMLOC(EE8) : set_vdp_register(0x96, 0xE6);
  					set_vdp_register(0x95, 0x00);
  DEF_ROMLOC(EEE) : set_vdp_register(0x97, 0x7F);
  DEF_ROMLOC(EF2) : write_vdp_control_16(0x7C00);
  DEF_ROMLOC(EF6) : move_tomem_16(0x83, 0xFFFFF640); // MOVE.W	#$0083,$F640
  DEF_ROMLOC(EFC)
      : write_vdp_control_16(read_16(0xFFFFF640));
  DEF_ROMLOC(F00)
      : move_toreg_32(VDP_CONTROL_PORT, &A5);        // LEA.L	$00C00004,A5
  DEF_ROMLOC(F06) : set_vdp_register(0x94, 0x01);
  					set_vdp_register(0x93, 0x40);
  DEF_ROMLOC(F0C) : set_vdp_register(0x96, 0xFC);
  					set_vdp_register(0x95, 0x00);
  DEF_ROMLOC(F12) : set_vdp_register(0x97, 0x7F);
  DEF_ROMLOC(F16) : write_vdp_control_16(0x7800);
  DEF_ROMLOC(F1A) : move_tomem_16(0x83, 0xFFFFF640); // MOVE.W	#$0083,$F640
  DEF_ROMLOC(F20)
      : write_vdp_control_16(read_16(0xFFFFF640));
  DEF_ROMLOC(F24) : tst_mem_8(0xFFFFF767);      // TST.B	$F767
  DEF_ROMLOC(F28) : if (CCR_EQ) goto rom_F54;   // BEQ.B	$F54
  DEF_ROMLOC(F2A)
      : move_toreg_32(VDP_CONTROL_PORT, &A5);        // LEA.L	$00C00004,A5
  DEF_ROMLOC(F30) : set_vdp_register(0x94, 0x01);
  					set_vdp_register(0x93, 0x70);
  DEF_ROMLOC(F36) : set_vdp_register(0x96, 0xE4);
  					set_vdp_register(0x95, 0x00);
  DEF_ROMLOC(F3C) : set_vdp_register(0x97, 0x7F);
  DEF_ROMLOC(F40) : write_vdp_control_16(0x7000);
  DEF_ROMLOC(F44) : move_tomem_16(0x83, 0xFFFFF640); // MOVE.W	#$0083,$F640
  DEF_ROMLOC(F4A)
      : write_vdp_control_16(read_16(0xFFFFF640));
  DEF_ROMLOC(F4E) : move_tomem_8(0x0, 0xFFFFF767); // MOVE.B	#$00,$F767
  DEF_ROMLOC(F54) :
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
  DEF_ROMLOC(F74) : scroll_update_tiles(); // BSR.W	$6C5C
  DEF_ROMLOC(F78) : rom_1C7DA();           // JSR	$0001C7DA
  DEF_ROMLOC(F7E) : rom_1CE84();           // JSR	$0001CE84
  DEF_ROMLOC(F84) : plc_refresh_frame();   // BSR.W	$163A
  DEF_ROMLOC(F88) : return;                // RTS
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
      : write_vdp_control_16(read_16(0xFFFFF624));
  plc_refresh_frame();                          // BRA.W	$163A
}
ROMFUNC(rom_FA6) {
  DEF_ROMLOC(FB8) : input_read_controllers();       // BSR.W	$11E6
  DEF_ROMLOC(FBC)
      : move_toreg_32(VDP_CONTROL_PORT, &A5);        // LEA.L	$00C00004,A5
  DEF_ROMLOC(FC2) : set_vdp_register(0x94, 0x00);
  					set_vdp_register(0x93, 0x40);
  DEF_ROMLOC(FC8) : set_vdp_register(0x96, 0xFD);
  					set_vdp_register(0x95, 0x80);
  DEF_ROMLOC(FCE) : set_vdp_register(0x97, 0x7F);
  DEF_ROMLOC(FD2) : write_vdp_control_16(0xC000);
  DEF_ROMLOC(FD6) : move_tomem_16(0x80, 0xFFFFF640); // MOVE.W	#$0080,$F640
  DEF_ROMLOC(FDC)
      : write_vdp_control_16(read_16(0xFFFFF640));
  DEF_ROMLOC(FE0)
      : move_toreg_32(VDP_CONTROL_PORT, &A5);        // LEA.L	$00C00004,A5
  DEF_ROMLOC(FE6) : set_vdp_register(0x94, 0x01);
  					set_vdp_register(0x93, 0x40);
  DEF_ROMLOC(FEC) : set_vdp_register(0x96, 0xFC);
  					set_vdp_register(0x95, 0x00);
  DEF_ROMLOC(FF2) : set_vdp_register(0x97, 0x7F);
  DEF_ROMLOC(FF6) : write_vdp_control_16(0x7800);
  DEF_ROMLOC(FFA) : move_tomem_16(0x83, 0xFFFFF640); // MOVE.W	#$0083,$F640
  DEF_ROMLOC(1000)
      : write_vdp_control_16(read_16(0xFFFFF640));
  DEF_ROMLOC(1004)
      : move_toreg_32(VDP_CONTROL_PORT, &A5);         // LEA.L	$00C00004,A5
  DEF_ROMLOC(100A) : set_vdp_register(0x94, 0x01);
  					 set_vdp_register(0x93, 0xC0);
  DEF_ROMLOC(1010) : set_vdp_register(0x96, 0xE6);
  					 set_vdp_register(0x95, 0x00);
  DEF_ROMLOC(1016) : set_vdp_register(0x97, 0x7F);
  DEF_ROMLOC(101A) : write_vdp_control_16(0x7C00);
  DEF_ROMLOC(101E) : move_tomem_16(0x83, 0xFFFFF640); // MOVE.W	#$0083,$F640
  DEF_ROMLOC(1024)
      : write_vdp_control_16(read_16(0xFFFFF640));
  DEF_ROMLOC(1030) : tst_mem_8(0xFFFFF767);        // TST.B	$F767
  DEF_ROMLOC(1034) : if (CCR_EQ) goto rom_1060;    // BEQ.B	$1060
  DEF_ROMLOC(1036)
      : move_toreg_32(VDP_CONTROL_PORT, &A5);         // LEA.L	$00C00004,A5
  DEF_ROMLOC(103C) : set_vdp_register(0x94, 0x01);
  					 set_vdp_register(0x93, 0x70);
  DEF_ROMLOC(1042) : set_vdp_register(0x96, 0xE4);
  					 set_vdp_register(0x95, 0x00);
  DEF_ROMLOC(1048) : set_vdp_register(0x97, 0x7F);
  DEF_ROMLOC(104C) : write_vdp_control_16(0x7000);
  DEF_ROMLOC(1050) : move_tomem_16(0x83, 0xFFFFF640); // MOVE.W	#$0083,$F640
  DEF_ROMLOC(1056)
      : write_vdp_control_16(read_16(0xFFFFF640));
  DEF_ROMLOC(105A) : move_tomem_8(0x0, 0xFFFFF767); // MOVE.B	#$00,$F767
  DEF_ROMLOC(1060) : tst_mem_16(0xFFFFF614);        // TST.W	$F614
  DEF_ROMLOC(1064) : if (CCR_EQ) goto rom_106C;     // BEQ.W	$106C
  DEF_ROMLOC(1068) : sub_tomem_16(0x1, 0xFFFFF614); // SUBQ.W	#$01,$F614
  DEF_ROMLOC(106C) : return;                        // RTS
}
ROMFUNC(rom_106E) {
  DEF_ROMLOC(1080) : input_read_controllers();       // BSR.W	$11E6
  DEF_ROMLOC(1084) : tst_mem_8(0xFFFFF64E);          // TST.B	$F64E
  DEF_ROMLOC(1088) : if (!CCR_EQ) goto rom_10B0;     // BNE.B	$10B0
  DEF_ROMLOC(108A)
      : move_toreg_32(VDP_CONTROL_PORT, &A5);         // LEA.L	$00C00004,A5
  DEF_ROMLOC(1090) : set_vdp_register(0x94, 0x00);
  					 set_vdp_register(0x93, 0x40);
  DEF_ROMLOC(1096) : set_vdp_register(0x96, 0xFD);
  					 set_vdp_register(0x95, 0x80);
  DEF_ROMLOC(109C) : set_vdp_register(0x97, 0x7F);
  DEF_ROMLOC(10A0) : write_vdp_control_16(0xC000);
  DEF_ROMLOC(10A4) : move_tomem_16(0x80, 0xFFFFF640); // MOVE.W	#$0080,$F640
  DEF_ROMLOC(10AA)
      : write_vdp_control_16(read_16(0xFFFFF640));
  DEF_ROMLOC(10AE) : goto rom_10D4;             // BRA.B	$10D4
  DEF_ROMLOC(10B0)
      : move_toreg_32(VDP_CONTROL_PORT, &A5);         // LEA.L	$00C00004,A5
  DEF_ROMLOC(10B6) : set_vdp_register(0x94, 0x00);
  					 set_vdp_register(0x93, 0x40);
  DEF_ROMLOC(10BC) : set_vdp_register(0x96, 0xFD);
  					 set_vdp_register(0x95, 0x40);
  DEF_ROMLOC(10C2) : set_vdp_register(0x97, 0x7F);
  DEF_ROMLOC(10C6) : write_vdp_control_16(0xC000);
  DEF_ROMLOC(10CA) : move_tomem_16(0x80, 0xFFFFF640); // MOVE.W	#$0080,$F640
  DEF_ROMLOC(10D0)
      : write_vdp_control_16(read_16(0xFFFFF640));
  DEF_ROMLOC(10D4)
      : move_toreg_32(VDP_CONTROL_PORT, &A5);         // LEA.L	$00C00004,A5
  DEF_ROMLOC(10DA) : set_vdp_register(0x94, 0x01);
  					 set_vdp_register(0x93, 0x40);
  DEF_ROMLOC(10E0) : set_vdp_register(0x96, 0xFC);
  					 set_vdp_register(0x95, 0x00);
  DEF_ROMLOC(10E6) : set_vdp_register(0x97, 0x7F);
  DEF_ROMLOC(10EA) : write_vdp_control_16(0x7800);
  DEF_ROMLOC(10EE) : move_tomem_16(0x83, 0xFFFFF640); // MOVE.W	#$0083,$F640
  DEF_ROMLOC(10F4)
      : write_vdp_control_16(read_16(0xFFFFF640));
  DEF_ROMLOC(10F8)
      : move_toreg_32(VDP_CONTROL_PORT, &A5);         // LEA.L	$00C00004,A5
  DEF_ROMLOC(10FE) : set_vdp_register(0x94, 0x01);
  					 set_vdp_register(0x93, 0xC0);
  DEF_ROMLOC(1104) : set_vdp_register(0x96, 0xE6);
  					 set_vdp_register(0x95, 0x00);
  DEF_ROMLOC(110A) : set_vdp_register(0x97, 0x7F);
  DEF_ROMLOC(110E) : write_vdp_control_16(0x7C00);
  DEF_ROMLOC(1112) : move_tomem_16(0x83, 0xFFFFF640); // MOVE.W	#$0083,$F640
  DEF_ROMLOC(1118)
      : write_vdp_control_16(read_16(0xFFFFF640));
  DEF_ROMLOC(1124) : return;                       // RTS
}
ROMFUNC(rom_1126) {
  DEF_ROMLOC(1126) : move_tosr_16(0x2700, &SR);      // MOVE.W	#$2700,SR
  DEF_ROMLOC(112A) : tst_mem_16(0xFFFFF644);         // TST.W	$F644
  DEF_ROMLOC(112E) : if (CCR_EQ) goto rom_119C;      // BEQ.B	$119C
  DEF_ROMLOC(1130) : move_tomem_16(0x0, 0xFFFFF644); // MOVE.W	#$0000,$F644
  DEF_ROMLOC(1136) : a0backup = A0;
  a1backup = A1; // TODO; // MOVEM.L	A0-A1,-(A7)
  DEF_ROMLOC(113A)
      : move_toreg_32(VDP_DATA_PORT, &A1);           // LEA.L
                                                     // $00C00000,A1
  DEF_ROMLOC(1140) : move_toreg_32(0xFFFFFA80, &A0); // LEA.L	$FA80,A0
  DEF_ROMLOC(1144)
      : write_vdp_control_32(0xC0000000);
  DEF_ROMLOC(114C) : write_vdp_data_32(read_32((A0 += 4, A0 - 4)));
  DEF_ROMLOC(114E) : write_vdp_data_32(read_32((A0 += 4, A0 - 4)));
  DEF_ROMLOC(1150) : write_vdp_data_32(read_32((A0 += 4, A0 - 4)));
  DEF_ROMLOC(1152) : write_vdp_data_32(read_32((A0 += 4, A0 - 4)));
  DEF_ROMLOC(1154) : write_vdp_data_32(read_32((A0 += 4, A0 - 4)));
  DEF_ROMLOC(1156) : write_vdp_data_32(read_32((A0 += 4, A0 - 4)));
  DEF_ROMLOC(1158) : write_vdp_data_32(read_32((A0 += 4, A0 - 4)));
  DEF_ROMLOC(115A) : write_vdp_data_32(read_32((A0 += 4, A0 - 4)));
  DEF_ROMLOC(115C) : write_vdp_data_32(read_32((A0 += 4, A0 - 4)));
  DEF_ROMLOC(115E) : write_vdp_data_32(read_32((A0 += 4, A0 - 4)));
  DEF_ROMLOC(1160) : write_vdp_data_32(read_32((A0 += 4, A0 - 4)));
  DEF_ROMLOC(1162) : write_vdp_data_32(read_32((A0 += 4, A0 - 4)));
  DEF_ROMLOC(1164) : write_vdp_data_32(read_32((A0 += 4, A0 - 4)));
  DEF_ROMLOC(1166) : write_vdp_data_32(read_32((A0 += 4, A0 - 4)));
  DEF_ROMLOC(1168) : write_vdp_data_32(read_32((A0 += 4, A0 - 4)));
  DEF_ROMLOC(116A) : write_vdp_data_32(read_32((A0 += 4, A0 - 4)));
  DEF_ROMLOC(116C) : write_vdp_data_32(read_32((A0 += 4, A0 - 4)));
  DEF_ROMLOC(116E) : write_vdp_data_32(read_32((A0 += 4, A0 - 4)));
  DEF_ROMLOC(1170) : write_vdp_data_32(read_32((A0 += 4, A0 - 4)));
  DEF_ROMLOC(1172) : write_vdp_data_32(read_32((A0 += 4, A0 - 4)));
  DEF_ROMLOC(1174) : write_vdp_data_32(read_32((A0 += 4, A0 - 4)));
  DEF_ROMLOC(1176) : write_vdp_data_32(read_32((A0 += 4, A0 - 4)));
  DEF_ROMLOC(1178) : write_vdp_data_32(read_32((A0 += 4, A0 - 4)));
  DEF_ROMLOC(117A) : write_vdp_data_32(read_32((A0 += 4, A0 - 4)));
  DEF_ROMLOC(117C) : write_vdp_data_32(read_32((A0 += 4, A0 - 4)));
  DEF_ROMLOC(117E) : write_vdp_data_32(read_32((A0 += 4, A0 - 4)));
  DEF_ROMLOC(1180) : write_vdp_data_32(read_32((A0 += 4, A0 - 4)));
  DEF_ROMLOC(1182) : write_vdp_data_32(read_32((A0 += 4, A0 - 4)));
  DEF_ROMLOC(1184) : write_vdp_data_32(read_32((A0 += 4, A0 - 4)));
  DEF_ROMLOC(1186) : write_vdp_data_32(read_32((A0 += 4, A0 - 4)));
  DEF_ROMLOC(1188) : write_vdp_data_32(read_32((A0 += 4, A0 - 4)));
  DEF_ROMLOC(118A) : write_vdp_data_32(read_32((A0 += 4, A0 - 4)));
  DEF_ROMLOC(118C)
      : set_vdp_register(0x8A,0xDF);
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