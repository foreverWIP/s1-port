// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_1C7DA) {
  u8 switchindex = 0;
  DEF_ROMLOC(1C7DA) : tst_mem_16(0xFFFFF63A);      // TST.W	$F63A
  DEF_ROMLOC(1C7DE) : if (!CCR_EQ) goto rom_1C7FA; // BNE.B	$1C7FA
  DEF_ROMLOC(1C7E0)
      : move_toreg_32(VDP_DATA_PORT, &A6);     // LEA.L
                                               // $00C00000,A6
  DEF_ROMLOC(1C7E6) : rom_1CCC6();             // BSR.W	$1CCC6
  DEF_ROMLOC(1C7EA) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(1C7EC) : move_toreg_8(read_8(v_zone), &D0);
  switchindex = (D0 & 0xff);                 // MOVE.B	$FE10,D0
  DEF_ROMLOC(1C7F0) : add_toreg_16(D0, &D0); // ADD.W	D0,D0
  DEF_ROMLOC(1C7F2)
      : move_toreg_16(read_16(0x1C7FC + (s16)(D0 & 0xffff)),
                      &D0); // MOVE.W	8(PC,D0),D0
  // DEF_ROMLOC(1C7F6): goto rom_1C7FC + (s16)(D0 & 0xffff); // JMP	4(PC,D0)
  DEF_ROMLOC(1C7F6) : switch (switchindex) {
  case 0:
    rom_1C80A();
    return;
  case 1:
    rom_1CB6C();
    return;
  case 2:
    rom_1C8C8();
    return;
  case 3:
    rom_1CB6C();
    return;
  case 4:
    rom_1CB6C();
    return;
  case 5:
    rom_1C9A2();
    return;
  case 6:
    rom_1CA58();
    return;
  }
  DEF_ROMLOC(1C7FA) : return; // RTS
}
ROMFUNC(rom_1C80A) {
  DEF_ROMLOC(1C80A) : sub_tomem_8(0x1, 0xFFFFF7B1);  // SUBQ.B	#$01,$F7B1
  DEF_ROMLOC(1C80E) : if (CCR_PL) goto rom_1C840;    // BPL.B	$1C840
  DEF_ROMLOC(1C810) : move_tomem_8(0x5, 0xFFFFF7B1); // MOVE.B	#$05,$F7B1
  DEF_ROMLOC(1C816) : move_toreg_32(0x66A96, &A1);   // LEA.L	$00066A96,A1
  DEF_ROMLOC(1C81C) : move_toreg_8(read_8(0xFFFFF7B0), &D0); // MOVE.B	$F7B0,D0
  DEF_ROMLOC(1C820) : add_tomem_8(0x1, 0xFFFFF7B0);   // ADDQ.B	#$01,$F7B0
  DEF_ROMLOC(1C824) : and_toreg_16(0x1, &D0);         // ANDI.W	#$0001,D0
  DEF_ROMLOC(1C828) : if (CCR_EQ) goto rom_1C82E;     // BEQ.B	$1C82E
  DEF_ROMLOC(1C82A) : move_toreg_32(A1 + 0x100, &A1); // LEA.L	256(A1),A1
  DEF_ROMLOC(1C82E)
      : write_vdp_control_32(0x6F000001);
  DEF_ROMLOC(1C838) : move_toreg_16(0x7, &D1); // MOVE.W	#$0007,D1
  rom_1CB6E();
  return;                                            // BRA.W	$1CB6E
  DEF_ROMLOC(1C840) : sub_tomem_8(0x1, 0xFFFFF7B3);  // SUBQ.B	#$01,$F7B3
  DEF_ROMLOC(1C844) : if (CCR_PL) goto rom_1C876;    // BPL.B	$1C876
  DEF_ROMLOC(1C846) : move_tomem_8(0xF, 0xFFFFF7B3); // MOVE.B	#$0F,$F7B3
  DEF_ROMLOC(1C84C) : move_toreg_32(0x66C96, &A1);   // LEA.L	$00066C96,A1
  DEF_ROMLOC(1C852) : move_toreg_8(read_8(0xFFFFF7B2), &D0); // MOVE.B	$F7B2,D0
  DEF_ROMLOC(1C856) : add_tomem_8(0x1, 0xFFFFF7B2);   // ADDQ.B	#$01,$F7B2
  DEF_ROMLOC(1C85A) : and_toreg_16(0x1, &D0);         // ANDI.W	#$0001,D0
  DEF_ROMLOC(1C85E) : if (CCR_EQ) goto rom_1C864;     // BEQ.B	$1C864
  DEF_ROMLOC(1C860) : move_toreg_32(A1 + 0x200, &A1); // LEA.L	512(A1),A1
  DEF_ROMLOC(1C864)
      : write_vdp_control_32(0x6B800001);
  DEF_ROMLOC(1C86E) : move_toreg_16(0xF, &D1); // MOVE.W	#$000F,D1
  rom_1CB6E();
  return;                                            // BRA.W	$1CB6E
  DEF_ROMLOC(1C876) : sub_tomem_8(0x1, 0xFFFFF7B5);  // SUBQ.B	#$01,$F7B5
  DEF_ROMLOC(1C87A) : if (CCR_PL) return;    // BPL.B	$1C8C2
  DEF_ROMLOC(1C87C) : move_tomem_8(0x7, 0xFFFFF7B5); // MOVE.B	#$07,$F7B5
  DEF_ROMLOC(1C882)
      : move_toreg_8(read_8(0xFFFFF7B4), &D0);      // MOVE.B	$F7B4,D0
  DEF_ROMLOC(1C886) : add_tomem_8(0x1, 0xFFFFF7B4); // ADDQ.B	#$01,$F7B4
  DEF_ROMLOC(1C88A) : and_toreg_16(0x3, &D0);       // ANDI.W	#$0003,D0
  DEF_ROMLOC(1C88E)
      : move_toreg_8(read_8(0x1C8C4 + (s16)(D0 & 0xffff)),
                     &D0);                            // MOVE.B	52(PC,D0),D0
  DEF_ROMLOC(1C892) : btst_toreg_32(0x0, &D0);        // BTST.L	#$00,D0
  DEF_ROMLOC(1C896) : if (!CCR_EQ) goto rom_1C89E;    // BNE.B	$1C89E
  DEF_ROMLOC(1C898) : move_tomem_8(0x7F, 0xFFFFF7B5); // MOVE.B	#$7F,$F7B5
  DEF_ROMLOC(1C89E) : lsl_toreg_16(0x7, &D0);         // LSL.W	#$07,D0
  DEF_ROMLOC(1C8A0) : move_toreg_16(D0, &D1);         // MOVE.W	D0,D1
  DEF_ROMLOC(1C8A2) : add_toreg_16(D0, &D0);          // ADD.W	D0,D0
  DEF_ROMLOC(1C8A4) : add_toreg_16(D1, &D0);          // ADD.W	D1,D0
  DEF_ROMLOC(1C8A6)
      : write_vdp_control_32(0x6D800001);
  DEF_ROMLOC(1C8B0) : move_toreg_32(0x67096, &A1); // LEA.L	$00067096,A1
  DEF_ROMLOC(1C8B6)
      : move_toreg_32((s32)A1 + (s8)0x0 + (s16)D0,
                      &A1);                    // LEA.L	0(A1,D0),A1
  DEF_ROMLOC(1C8BA) : move_toreg_16(0xB, &D1); // MOVE.W	#$000B,D1
  DEF_ROMLOC(1C8BE) : rom_1CB6E();             // BSR.W	$1CB6E
}
ROMFUNC(rom_1C8C8) {
  u8 switchindex = 0;
  DEF_ROMLOC(1C8C8) : sub_tomem_8(0x1, 0xFFFFF7B1);   // SUBQ.B	#$01,$F7B1
  DEF_ROMLOC(1C8CC) : if (CCR_PL) goto rom_1C906;     // BPL.B	$1C906
  DEF_ROMLOC(1C8CE) : move_tomem_8(0x13, 0xFFFFF7B1); // MOVE.B	#$13,$F7B1
  DEF_ROMLOC(1C8D4) : move_toreg_32(0x67516, &A1);    // LEA.L	$00067516,A1
  DEF_ROMLOC(1C8DA) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(1C8DC)
      : move_toreg_8(read_8(0xFFFFF7B0), &D0);      // MOVE.B	$F7B0,D0
  DEF_ROMLOC(1C8E0) : add_toreg_8(0x1, &D0);        // ADDQ.B	#$01,D0
  DEF_ROMLOC(1C8E2) : cmp_toreg_8(0x3, &D0);        // CMPI.B	#$03,D0
  DEF_ROMLOC(1C8E6) : if (!CCR_EQ) goto rom_1C8EA;  // BNE.B	$1C8EA
  DEF_ROMLOC(1C8E8) : move_toreg_32(0x0, &D0);      // MOVEQ.L	$00,D0
  DEF_ROMLOC(1C8EA) : move_tomem_8(D0, 0xFFFFF7B0); // MOVE.B	D0,$F7B0
  DEF_ROMLOC(1C8EE) : mulu_toreg_16(0x100, &D0);    // MULU.W	#$0100,D0
  DEF_ROMLOC(1C8F2) : add_toreg_16(D0, &A1);        // ADDA.W	D0,A1
  DEF_ROMLOC(1C8F4)
      : write_vdp_control_32(0x5C400001);
  DEF_ROMLOC(1C8FE) : move_toreg_16(0x7, &D1); // MOVE.W	#$0007,D1
  DEF_ROMLOC(1C902) : rom_1CB6E();             // BSR.W	$1CB6E
  DEF_ROMLOC(1C906) : sub_tomem_8(0x1, 0xFFFFF7B3);  // SUBQ.B	#$01,$F7B3
  DEF_ROMLOC(1C90A) : if (CCR_PL) goto rom_1C964;    // BPL.B	$1C964
  DEF_ROMLOC(1C90C) : move_tomem_8(0x1, 0xFFFFF7B3); // MOVE.B	#$01,$F7B3
  DEF_ROMLOC(1C912) : move_toreg_32(0x0, &D0);       // MOVEQ.L	$00,D0
  DEF_ROMLOC(1C914)
      : move_toreg_8(read_8(0xFFFFF7B0), &D0);     // MOVE.B	$F7B0,D0
  DEF_ROMLOC(1C918) : move_toreg_32(0x67816, &A4); // LEA.L	$00067816,A4
  DEF_ROMLOC(1C91E) : ror_toreg_16(0x7, &D0);      // ROR.W	#$07,D0
  DEF_ROMLOC(1C920) : add_toreg_16(D0, &A4);       // ADDA.W	D0,A4
  DEF_ROMLOC(1C922)
      : write_vdp_control_32(0x5A400001);
  DEF_ROMLOC(1C92C) : move_toreg_32(0x0, &D3); // MOVEQ.L	$00,D3
  DEF_ROMLOC(1C92E)
      : move_toreg_8(read_8(0xFFFFF7B2), &D3);      // MOVE.B	$F7B2,D3
  DEF_ROMLOC(1C932) : add_tomem_8(0x1, 0xFFFFF7B2); // ADDQ.B	#$01,$F7B2
  DEF_ROMLOC(1C936)
      : move_toreg_8(read_8(0xFFFFFE68), &D3); // MOVE.B	$FE68,D3
  DEF_ROMLOC(1C93A) : move_toreg_16(0x3, &D2); // MOVE.W	#$0003,D2
  DEF_ROMLOC(1C93E) : move_toreg_16(D3, &D0);  // MOVE.W	D3,D0
  DEF_ROMLOC(1C940) : add_toreg_16(D0, &D0);   // ADD.W	D0,D0
  DEF_ROMLOC(1C942) : and_toreg_16(0x1E, &D0);
  switchindex = D0 / 2;                            // ANDI.W	#$001E,D0
  DEF_ROMLOC(1C946) : move_toreg_32(0x1CB84, &A3); // LEA.L	$0001CB84,A3
  DEF_ROMLOC(1C94C)
      : move_toreg_16(read_16((s32)A3 + (s8)0x0 + (s16)D0),
                      &D0); // MOVE.W	0(A3,D0),D0
  DEF_ROMLOC(1C950)
      : move_toreg_32((s32)A3 + (s8)0x0 + (s16)D0,
                      &A3);                     // LEA.L	0(A3,D0),A3
  DEF_ROMLOC(1C954) : move_toreg_32(A4, &A1);   // MOVEA.L	A4,A1
  DEF_ROMLOC(1C956) : move_toreg_16(0x1F, &D1); // MOVE.W	#$001F,D1
  // DEF_ROMLOC(1C95A): rom_A3(); // JSR	(A3)
  DEF_ROMLOC(1C95A) : switch (switchindex) {
  case 0:
    rom_1CBA4();
    break;
  case 1:
    rom_1CBB0();
    break;
  case 2:
    rom_1CBC6();
    break;
  case 3:
    rom_1CBD4();
    break;
  case 4:
    rom_1CBEA();
    break;
  case 5:
    rom_1CBF8();
    break;
  case 6:
    rom_1CC0E();
    break;
  case 7:
    rom_1CC1C();
    break;
  case 8:
    rom_1CC32();
    break;
  case 9:
    rom_1CC40();
    break;
  case 10:
    rom_1CC56();
    break;
  case 11:
    rom_1CC64();
    break;
  case 12:
    rom_1CC7A();
    break;
  case 13:
    rom_1CC88();
    break;
  case 14:
    rom_1CC9E();
    break;
  case 15:
    rom_1CCB0();
    break;
  }
  DEF_ROMLOC(1C95C) : add_toreg_16(0x4, &D3); // ADDQ.W	#$04,D3
  DEF_ROMLOC(1C95E) : dec_reg_16(&D2);
  if ((D2 & 0xffff) != 0xffff)
    goto rom_1C93E;                                  // DBF.W	D2,$1C93E
  DEF_ROMLOC(1C962) : return;                        // RTS
  DEF_ROMLOC(1C964) : sub_tomem_8(0x1, 0xFFFFF7B5);  // SUBQ.B	#$01,$F7B5
  DEF_ROMLOC(1C968) : if (CCR_PL) goto rom_1C9A0;    // BPL.W	$1C9A0
  DEF_ROMLOC(1C96C) : move_tomem_8(0x7, 0xFFFFF7B5); // MOVE.B	#$07,$F7B5
  DEF_ROMLOC(1C972) : move_toreg_32(0x67E16, &A1);   // LEA.L	$00067E16,A1
  DEF_ROMLOC(1C978) : move_toreg_32(0x0, &D0);       // MOVEQ.L	$00,D0
  DEF_ROMLOC(1C97A)
      : move_toreg_8(read_8(0xFFFFF7B6), &D0);      // MOVE.B	$F7B6,D0
  DEF_ROMLOC(1C97E) : add_tomem_8(0x1, 0xFFFFF7B6); // ADDQ.B	#$01,$F7B6
  DEF_ROMLOC(1C982) : and_tomem_8(0x3, 0xFFFFF7B6); // ANDI.B	#$03,$F7B6
  DEF_ROMLOC(1C988) : mulu_toreg_16(0xC0, &D0);     // MULU.W	#$00C0,D0
  DEF_ROMLOC(1C98C) : add_toreg_16(D0, &A1);        // ADDA.W	D0,A1
  DEF_ROMLOC(1C98E)
      : write_vdp_control_32(0x5E400001);
  DEF_ROMLOC(1C998) : move_toreg_16(0x5, &D1); // MOVE.W	#$0005,D1
  DEF_ROMLOC(1C99C) : rom_1CB6E();
  return;                     // BRA.W	$1CB6E
  DEF_ROMLOC(1C9A0) : return; // RTS
}
ROMFUNC(rom_1C9A2) {
  DEF_ROMLOC(1C9A2) : tst_mem_8(0xFFFFF7B4);         // TST.B	$F7B4
  DEF_ROMLOC(1C9A6) : if (CCR_EQ) goto rom_1C9AE;    // BEQ.B	$1C9AE
  DEF_ROMLOC(1C9A8) : sub_tomem_8(0x1, 0xFFFFF7B4);  // SUBQ.B	#$01,$F7B4
  DEF_ROMLOC(1C9AC) : goto rom_1CA06;                // BRA.B	$1CA06
  DEF_ROMLOC(1C9AE) : sub_tomem_8(0x1, 0xFFFFF7B1);  // SUBQ.B	#$01,$F7B1
  DEF_ROMLOC(1C9B2) : if (CCR_PL) goto rom_1CA06;    // BPL.B	$1CA06
  DEF_ROMLOC(1C9B4) : move_tomem_8(0x7, 0xFFFFF7B1); // MOVE.B	#$07,$F7B1
  DEF_ROMLOC(1C9BA) : move_toreg_32(0x68116, &A1);   // LEA.L	$00068116,A1
  DEF_ROMLOC(1C9C0)
      : write_vdp_control_32(0x49000002);
  DEF_ROMLOC(1C9CA)
      : move_toreg_8(read_8(0xFFFFF7B0), &D0);      // MOVE.B	$F7B0,D0
  DEF_ROMLOC(1C9CE) : add_tomem_8(0x1, 0xFFFFF7B0); // ADDQ.B	#$01,$F7B0
  DEF_ROMLOC(1C9D2) : and_toreg_16(0x7, &D0);       // ANDI.W	#$0007,D0
  DEF_ROMLOC(1C9D6) : if (CCR_EQ) goto rom_1C9EA;   // BEQ.B	$1C9EA
  DEF_ROMLOC(1C9D8) : sub_toreg_16(0x1, &D0);       // SUBQ.W	#$01,D0
  DEF_ROMLOC(1C9DA) : mulu_toreg_16(0x180, &D0);    // MULU.W	#$0180,D0
  DEF_ROMLOC(1C9DE)
      : move_toreg_32((s32)A1 + (s8)0x0 + (s16)D0,
                      &A1);                    // LEA.L	0(A1,D0),A1
  DEF_ROMLOC(1C9E2) : move_toreg_16(0xB, &D1); // MOVE.W	#$000B,D1
  DEF_ROMLOC(1C9E6) : rom_1CB6E();
  return; // BRA.W	$1CB6E
  DEF_ROMLOC(1C9EA)
      : move_tomem_8(0xFFFFFFB4, 0xFFFFF7B4);      // MOVE.B	#$B4,$F7B4
  DEF_ROMLOC(1C9F0) : move_toreg_16(0x5, &D1);     // MOVE.W	#$0005,D1
  DEF_ROMLOC(1C9F4) : rom_1CB6E();                 // BSR.W	$1CB6E
  DEF_ROMLOC(1C9F8) : move_toreg_32(0x68116, &A1); // LEA.L	$00068116,A1
  DEF_ROMLOC(1C9FE) : move_toreg_16(0x5, &D1);     // MOVE.W	#$0005,D1
  DEF_ROMLOC(1CA02) : rom_1CB6E();
  return;                                            // BRA.W	$1CB6E
  DEF_ROMLOC(1CA06) : tst_mem_8(0xFFFFF7B5);         // TST.B	$F7B5
  DEF_ROMLOC(1CA0A) : if (CCR_EQ) goto rom_1CA12;    // BEQ.B	$1CA12
  DEF_ROMLOC(1CA0C) : sub_tomem_8(0x1, 0xFFFFF7B5);  // SUBQ.B	#$01,$F7B5
  DEF_ROMLOC(1CA10) : goto rom_1CA56;                // BRA.B	$1CA56
  DEF_ROMLOC(1CA12) : sub_tomem_8(0x1, 0xFFFFF7B3);  // SUBQ.B	#$01,$F7B3
  DEF_ROMLOC(1CA16) : if (CCR_PL) goto rom_1CA56;    // BPL.B	$1CA56
  DEF_ROMLOC(1CA18) : move_tomem_8(0x7, 0xFFFFF7B3); // MOVE.B	#$07,$F7B3
  DEF_ROMLOC(1CA1E) : move_toreg_32(0x68116, &A1);   // LEA.L	$00068116,A1
  DEF_ROMLOC(1CA24)
      : write_vdp_control_32(0x4A800002);
  DEF_ROMLOC(1CA2E)
      : move_toreg_8(read_8(0xFFFFF7B2), &D0);      // MOVE.B	$F7B2,D0
  DEF_ROMLOC(1CA32) : add_tomem_8(0x1, 0xFFFFF7B2); // ADDQ.B	#$01,$F7B2
  DEF_ROMLOC(1CA36) : and_toreg_16(0x7, &D0);       // ANDI.W	#$0007,D0
  DEF_ROMLOC(1CA3A) : if (CCR_EQ) goto rom_1CA4E;   // BEQ.B	$1CA4E
  DEF_ROMLOC(1CA3C) : sub_toreg_16(0x1, &D0);       // SUBQ.W	#$01,D0
  DEF_ROMLOC(1CA3E) : mulu_toreg_16(0x180, &D0);    // MULU.W	#$0180,D0
  DEF_ROMLOC(1CA42)
      : move_toreg_32((s32)A1 + (s8)0x0 + (s16)D0,
                      &A1);                    // LEA.L	0(A1,D0),A1
  DEF_ROMLOC(1CA46) : move_toreg_16(0xB, &D1); // MOVE.W	#$000B,D1
  DEF_ROMLOC(1CA4A) : rom_1CB6E();
  return;                                             // BRA.W	$1CB6E
  DEF_ROMLOC(1CA4E) : move_tomem_8(0x78, 0xFFFFF7B5); // MOVE.B	#$78,$F7B5
  DEF_ROMLOC(1CA54) : goto rom_1C9F0;                 // BRA.B	$1C9F0
  DEF_ROMLOC(1CA56) : return;                         // RTS
}
ROMFUNC(rom_1CA58) {
  DEF_ROMLOC(1CA58) : sub_tomem_8(0x1, 0xFFFFF7B3); // SUBQ.B	#$01,$F7B3
  DEF_ROMLOC(1CA5C) : if (CCR_PL) {
    rom_1CAAA();
    return;
  } // BPL.B	$1CAAA
  DEF_ROMLOC(1CA5E) : move_tomem_8(0x7, 0xFFFFF7B3); // MOVE.B	#$07,$F7B3
  DEF_ROMLOC(1CA64) : move_toreg_32(0x66C96, &A1);   // LEA.L	$00066C96,A1
  DEF_ROMLOC(1CA6A)
      : move_toreg_32(v_256x256 + 0xA400 - 0x1000, &A2);     // LEA.L	$9400,A2
  DEF_ROMLOC(1CA6E) : move_toreg_8(read_8(0xFFFFF7B2), &D0); // MOVE.B	$F7B2,D0
  DEF_ROMLOC(1CA72) : add_tomem_8(0x1, 0xFFFFF7B2);   // ADDQ.B	#$01,$F7B2
  DEF_ROMLOC(1CA76) : and_toreg_16(0x1, &D0);         // ANDI.W	#$0001,D0
  DEF_ROMLOC(1CA7A) : if (CCR_EQ) goto rom_1CA84;     // BEQ.B	$1CA84
  DEF_ROMLOC(1CA7C) : move_toreg_32(A1 + 0x200, &A1); // LEA.L	512(A1),A1
  DEF_ROMLOC(1CA80) : move_toreg_32(A2 + 0x200, &A2); // LEA.L	512(A2),A2
  DEF_ROMLOC(1CA84)
      : write_vdp_control_32(0x6B800001);
  DEF_ROMLOC(1CA8E) : move_toreg_16(0xF, &D1); // MOVE.W	#$000F,D1
  DEF_ROMLOC(1CA92) : rom_1CB6E();             // BSR.W	$1CB6E
  DEF_ROMLOC(1CA96) : move_toreg_32(A2, &A1);  // MOVEA.L	A2,A1
  DEF_ROMLOC(1CA98)
      : write_vdp_control_32(0x72000001);
  DEF_ROMLOC(1CAA2) : move_toreg_16(0xF, &D1); // MOVE.W	#$000F,D1
  rom_1CB6E();
  return; // BRA.W	$1CB6E
}
ROMFUNC(rom_1CAAA) {
  DEF_ROMLOC(1CAAA) : sub_tomem_8(0x1, 0xFFFFF7B5);  // SUBQ.B	#$01,$F7B5
  DEF_ROMLOC(1CAAE) : if (CCR_PL) goto rom_1CAF2;    // BPL.B	$1CAF2
  DEF_ROMLOC(1CAB0) : move_tomem_8(0x7, 0xFFFFF7B5); // MOVE.B	#$07,$F7B5
  DEF_ROMLOC(1CAB6)
      : move_toreg_8(read_8(0xFFFFF7B4), &D0);      // MOVE.B	$F7B4,D0
  DEF_ROMLOC(1CABA) : add_tomem_8(0x1, 0xFFFFF7B4); // ADDQ.B	#$01,$F7B4
  DEF_ROMLOC(1CABE) : and_toreg_16(0x7, &D0);       // ANDI.W	#$0007,D0
  DEF_ROMLOC(1CAC2)
      : move_toreg_8(read_8(0x1CAEA + (s16)(D0 & 0xffff)),
                     &D0);                    // MOVE.B	38(PC,D0),D0
  DEF_ROMLOC(1CAC6) : lsl_toreg_16(0x7, &D0); // LSL.W	#$07,D0
  DEF_ROMLOC(1CAC8) : move_toreg_16(D0, &D1); // MOVE.W	D0,D1
  DEF_ROMLOC(1CACA) : add_toreg_16(D0, &D0);  // ADD.W	D0,D0
  DEF_ROMLOC(1CACC) : add_toreg_16(D1, &D0);  // ADD.W	D1,D0
  DEF_ROMLOC(1CACE)
      : write_vdp_control_32(0x6D800001);
  DEF_ROMLOC(1CAD8) : move_toreg_32(0x67096, &A1); // LEA.L	$00067096,A1
  DEF_ROMLOC(1CADE)
      : move_toreg_32((s32)A1 + (s8)0x0 + (s16)D0,
                      &A1);                    // LEA.L	0(A1,D0),A1
  DEF_ROMLOC(1CAE2) : move_toreg_16(0xB, &D1); // MOVE.W	#$000B,D1
  DEF_ROMLOC(1CAE6) : rom_1CB6E();
  return;                                           // BRA.W	$1CB6E
  DEF_ROMLOC(1CAEA) : or_toreg_8(0x1, &D0);         // ORI.B	#$01,D0
  DEF_ROMLOC(1CAEE) : and_toreg_8(0x1, &D2);        // ANDI.B	#$01,D2
  DEF_ROMLOC(1CAF2) : sub_tomem_8(0x1, 0xFFFFF7B9); // SUBQ.B	#$01,$F7B9
  DEF_ROMLOC(1CAF6) : if (CCR_PL) {
    rom_1CB30();
    return;
  } // BPL.B	$1CB30
  DEF_ROMLOC(1CAF8) : move_tomem_8(0xE, 0xFFFFF7B9); // MOVE.B	#$0E,$F7B9
  DEF_ROMLOC(1CAFE)
      : move_toreg_8(read_8(0xFFFFF7B8), &D0);      // MOVE.B	$F7B8,D0
  DEF_ROMLOC(1CB02) : add_tomem_8(0x1, 0xFFFFF7B8); // ADDQ.B	#$01,$F7B8
  DEF_ROMLOC(1CB06) : and_toreg_16(0x3, &D0);       // ANDI.W	#$0003,D0
  DEF_ROMLOC(1CB0A)
      : move_toreg_8(read_8(0x1CB2C + (s16)(D0 & 0xffff)),
                     &D0);                    // MOVE.B	32(PC,D0),D0
  DEF_ROMLOC(1CB0E) : lsl_toreg_16(0x8, &D0); // LSL.W	#$08,D0
  DEF_ROMLOC(1CB10) : add_toreg_16(D0, &D0);  // ADD.W	D0,D0
  DEF_ROMLOC(1CB12)
      : write_vdp_control_32(0x70000001);
  DEF_ROMLOC(1CB1C)
      : move_toreg_32((v_256x256 + 0xA400) - 0x1000 + 0x400, &A1); // LEA.L	$9800,A1
  DEF_ROMLOC(1CB20)
      : move_toreg_32((s32)A1 + (s8)0x0 + (s16)D0,
                      &A1);                    // LEA.L	0(A1,D0),A1
  DEF_ROMLOC(1CB24) : move_toreg_16(0xF, &D1); // MOVE.W	#$000F,D1
  DEF_ROMLOC(1CB28) : rom_1CB6E();
  return;                                   // BRA.W	$1CB6E
  DEF_ROMLOC(1CB2C) : or_toreg_8(0x1, &D1); // ORI.B	#$01,D1
  rom_1CB30();                              // Detected flow into next function
}
ROMFUNC(rom_1CB30) {
  DEF_ROMLOC(1CB30) : sub_tomem_8(0x1, 0xFFFFF7BB);  // SUBQ.B	#$01,$F7BB
  DEF_ROMLOC(1CB34) : if (CCR_PL) goto rom_1CB6A;    // BPL.B	$1CB6A
  DEF_ROMLOC(1CB36) : move_tomem_8(0xB, 0xFFFFF7BB); // MOVE.B	#$0B,$F7BB
  DEF_ROMLOC(1CB3C)
      : move_toreg_8(read_8(0xFFFFF7BA), &D0);      // MOVE.B	$F7BA,D0
  DEF_ROMLOC(1CB40) : add_tomem_8(0x1, 0xFFFFF7BA); // ADDQ.B	#$01,$F7BA
  DEF_ROMLOC(1CB44) : and_toreg_16(0x3, &D0);       // ANDI.W	#$0003,D0
  DEF_ROMLOC(1CB48)
      : move_toreg_8(read_8(0x1CB2C + (s16)(D0 & 0xffff)),
                     &D0);                    // MOVE.B	-30(PC,D0),D0
  DEF_ROMLOC(1CB4C) : lsl_toreg_16(0x8, &D0); // LSL.W	#$08,D0
  DEF_ROMLOC(1CB4E) : add_toreg_16(D0, &D0);  // ADD.W	D0,D0
  DEF_ROMLOC(1CB50)
      : write_vdp_control_32(0x68000001);
  DEF_ROMLOC(1CB5A)
      : move_toreg_32(v_256x256 + 0xA400 - 0x600, &A1); // LEA.L	$9E00,A1
  DEF_ROMLOC(1CB5E)
      : move_toreg_32((s32)A1 + (s8)0x0 + (s16)D0,
                      &A1);                    // LEA.L	0(A1,D0),A1
  DEF_ROMLOC(1CB62) : move_toreg_16(0xF, &D1); // MOVE.W	#$000F,D1
  DEF_ROMLOC(1CB66) : rom_1CB6E();
  return;                     // BRA.W	$1CB6E
  DEF_ROMLOC(1CB6A) : return; // RTS
}
ROMFUNC(rom_1CB6C) {
  DEF_ROMLOC(1CB6C) : return; // RTS
}
ROMFUNC(rom_1CB6E) {
  DEF_ROMLOC(1CB6E) : write_vdp_data_32(read_32((A1 += 4, A1 - 4)));
  DEF_ROMLOC(1CB70) : write_vdp_data_32(read_32((A1 += 4, A1 - 4)));
  DEF_ROMLOC(1CB72) : write_vdp_data_32(read_32((A1 += 4, A1 - 4)));
  DEF_ROMLOC(1CB74) : write_vdp_data_32(read_32((A1 += 4, A1 - 4)));
  DEF_ROMLOC(1CB76) : write_vdp_data_32(read_32((A1 += 4, A1 - 4)));
  DEF_ROMLOC(1CB78) : write_vdp_data_32(read_32((A1 += 4, A1 - 4)));
  DEF_ROMLOC(1CB7A) : write_vdp_data_32(read_32((A1 += 4, A1 - 4)));
  DEF_ROMLOC(1CB7C) : write_vdp_data_32(read_32((A1 += 4, A1 - 4)));
  DEF_ROMLOC(1CB7E) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_1CB6E;           // DBF.W	D1,$1CB6E
  DEF_ROMLOC(1CB82) : return; // RTS
}
ROMFUNC(rom_1CBA4) {
  DEF_ROMLOC(1CBA4) : write_vdp_data_32(read_32(A1));
  DEF_ROMLOC(1CBA6) : move_toreg_32(A1 + 0x10, &A1);  // LEA.L	16(A1),A1
  DEF_ROMLOC(1CBAA) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_1CBA4;           // DBF.W	D1,$1CBA4
  DEF_ROMLOC(1CBAE) : return; // RTS
}
ROMFUNC(rom_1CBB0) {
  DEF_ROMLOC(1CBB0)
      : move_toreg_32(read_32(A1 + 0x2), &D0);             // MOVE.L	2(A1),D0
  DEF_ROMLOC(1CBB4) : move_toreg_8(read_8(A1 + 0x1), &D0); // MOVE.B	1(A1),D0
  DEF_ROMLOC(1CBB8) : ror_toreg_32(0x8, &D0);              // ROR.L	#$08,D0
  DEF_ROMLOC(1CBBA) : write_vdp_data_32(D0);
  DEF_ROMLOC(1CBBC) : move_toreg_32(A1 + 0x10, &A1);       // LEA.L	16(A1),A1
  DEF_ROMLOC(1CBC0) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_1CBB0;           // DBF.W	D1,$1CBB0
  DEF_ROMLOC(1CBC4) : return; // RTS
}
ROMFUNC(rom_1CBC6) {
  DEF_ROMLOC(1CBC6)
      : write_vdp_data_32(read_32(A1 + 0x2));
  DEF_ROMLOC(1CBCA) : move_toreg_32(A1 + 0x10, &A1); // LEA.L	16(A1),A1
  DEF_ROMLOC(1CBCE) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_1CBC6;           // DBF.W	D1,$1CBC6
  DEF_ROMLOC(1CBD2) : return; // RTS
}
ROMFUNC(rom_1CBD4) {
  DEF_ROMLOC(1CBD4)
      : move_toreg_32(read_32(A1 + 0x4), &D0);             // MOVE.L	4(A1),D0
  DEF_ROMLOC(1CBD8) : move_toreg_8(read_8(A1 + 0x3), &D0); // MOVE.B	3(A1),D0
  DEF_ROMLOC(1CBDC) : ror_toreg_32(0x8, &D0);              // ROR.L	#$08,D0
  DEF_ROMLOC(1CBDE) : write_vdp_data_32(D0);
  DEF_ROMLOC(1CBE0) : move_toreg_32(A1 + 0x10, &A1);       // LEA.L	16(A1),A1
  DEF_ROMLOC(1CBE4) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_1CBD4;           // DBF.W	D1,$1CBD4
  DEF_ROMLOC(1CBE8) : return; // RTS
}
ROMFUNC(rom_1CBEA) {
  DEF_ROMLOC(1CBEA)
      : write_vdp_data_32(read_32(A1 + 0x4));
  DEF_ROMLOC(1CBEE) : move_toreg_32(A1 + 0x10, &A1); // LEA.L	16(A1),A1
  DEF_ROMLOC(1CBF2) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_1CBEA;           // DBF.W	D1,$1CBEA
  DEF_ROMLOC(1CBF6) : return; // RTS
}
ROMFUNC(rom_1CBF8) {
  DEF_ROMLOC(1CBF8)
      : move_toreg_32(read_32(A1 + 0x6), &D0);             // MOVE.L	6(A1),D0
  DEF_ROMLOC(1CBFC) : move_toreg_8(read_8(A1 + 0x5), &D0); // MOVE.B	5(A1),D0
  DEF_ROMLOC(1CC00) : ror_toreg_32(0x8, &D0);              // ROR.L	#$08,D0
  DEF_ROMLOC(1CC02) : write_vdp_data_32(D0);
  DEF_ROMLOC(1CC04) : move_toreg_32(A1 + 0x10, &A1);       // LEA.L	16(A1),A1
  DEF_ROMLOC(1CC08) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_1CBF8;           // DBF.W	D1,$1CBF8
  DEF_ROMLOC(1CC0C) : return; // RTS
}
ROMFUNC(rom_1CC0E) {
  DEF_ROMLOC(1CC0E)
      : write_vdp_data_32(read_32(A1 + 0x6));
  DEF_ROMLOC(1CC12) : move_toreg_32(A1 + 0x10, &A1); // LEA.L	16(A1),A1
  DEF_ROMLOC(1CC16) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_1CC0E;           // DBF.W	D1,$1CC0E
  DEF_ROMLOC(1CC1A) : return; // RTS
}
ROMFUNC(rom_1CC1C) {
  DEF_ROMLOC(1CC1C)
      : move_toreg_32(read_32(A1 + 0x8), &D0);             // MOVE.L	8(A1),D0
  DEF_ROMLOC(1CC20) : move_toreg_8(read_8(A1 + 0x7), &D0); // MOVE.B	7(A1),D0
  DEF_ROMLOC(1CC24) : ror_toreg_32(0x8, &D0);              // ROR.L	#$08,D0
  DEF_ROMLOC(1CC26) : write_vdp_data_32(D0);
  DEF_ROMLOC(1CC28) : move_toreg_32(A1 + 0x10, &A1);       // LEA.L	16(A1),A1
  DEF_ROMLOC(1CC2C) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_1CC1C;           // DBF.W	D1,$1CC1C
  DEF_ROMLOC(1CC30) : return; // RTS
}
ROMFUNC(rom_1CC32) {
  DEF_ROMLOC(1CC32)
      : write_vdp_data_32(read_32(A1 + 0x8));
  DEF_ROMLOC(1CC36) : move_toreg_32(A1 + 0x10, &A1); // LEA.L	16(A1),A1
  DEF_ROMLOC(1CC3A) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_1CC32;           // DBF.W	D1,$1CC32
  DEF_ROMLOC(1CC3E) : return; // RTS
}
ROMFUNC(rom_1CC40) {
  DEF_ROMLOC(1CC40)
      : move_toreg_32(read_32(A1 + 0xA), &D0);             // MOVE.L	10(A1),D0
  DEF_ROMLOC(1CC44) : move_toreg_8(read_8(A1 + 0x9), &D0); // MOVE.B	9(A1),D0
  DEF_ROMLOC(1CC48) : ror_toreg_32(0x8, &D0);              // ROR.L	#$08,D0
  DEF_ROMLOC(1CC4A) : write_vdp_data_32(D0);
  DEF_ROMLOC(1CC4C) : move_toreg_32(A1 + 0x10, &A1);       // LEA.L	16(A1),A1
  DEF_ROMLOC(1CC50) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_1CC40;           // DBF.W	D1,$1CC40
  DEF_ROMLOC(1CC54) : return; // RTS
}
ROMFUNC(rom_1CC56) {
  DEF_ROMLOC(1CC56)
      : write_vdp_data_32(read_32(A1 + 0xA));
  DEF_ROMLOC(1CC5A) : move_toreg_32(A1 + 0x10, &A1); // LEA.L	16(A1),A1
  DEF_ROMLOC(1CC5E) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_1CC56;           // DBF.W	D1,$1CC56
  DEF_ROMLOC(1CC62) : return; // RTS
}
ROMFUNC(rom_1CC64) {
  DEF_ROMLOC(1CC64)
      : move_toreg_32(read_32(A1 + 0xC), &D0); // MOVE.L	12(A1),D0
  DEF_ROMLOC(1CC68)
      : move_toreg_8(read_8(A1 + 0xB), &D0);         // MOVE.B
                                                     // 11(A1),D0
  DEF_ROMLOC(1CC6C) : ror_toreg_32(0x8, &D0);        // ROR.L	#$08,D0
  DEF_ROMLOC(1CC6E) : write_vdp_data_32(D0);
  DEF_ROMLOC(1CC70) : move_toreg_32(A1 + 0x10, &A1); // LEA.L	16(A1),A1
  DEF_ROMLOC(1CC74) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_1CC64;           // DBF.W	D1,$1CC64
  DEF_ROMLOC(1CC78) : return; // RTS
}
ROMFUNC(rom_1CC7A) {
  DEF_ROMLOC(1CC7A)
      : write_vdp_data_32(read_32(A1 + 0xC));
  DEF_ROMLOC(1CC7E) : move_toreg_32(A1 + 0x10, &A1); // LEA.L	16(A1),A1
  DEF_ROMLOC(1CC82) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_1CC7A;           // DBF.W	D1,$1CC7A
  DEF_ROMLOC(1CC86) : return; // RTS
}
ROMFUNC(rom_1CC88) {
  DEF_ROMLOC(1CC88)
      : move_toreg_32(read_32(A1 + 0xC), &D0);             // MOVE.L	12(A1),D0
  DEF_ROMLOC(1CC8C) : rol_toreg_32(0x8, &D0);              // ROL.L	#$08,D0
  DEF_ROMLOC(1CC8E) : move_toreg_8(read_8(A1 + 0x0), &D0); // MOVE.B	0(A1),D0
  DEF_ROMLOC(1CC92) : write_vdp_data_32(D0);
  DEF_ROMLOC(1CC94) : move_toreg_32(A1 + 0x10, &A1);       // LEA.L	16(A1),A1
  DEF_ROMLOC(1CC98) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_1CC88;           // DBF.W	D1,$1CC88
  DEF_ROMLOC(1CC9C) : return; // RTS
}
ROMFUNC(rom_1CC9E) {
  DEF_ROMLOC(1CC9E)
      : write_vdp_data_16(read_16(A1 + 0xE));
  DEF_ROMLOC(1CCA2)
      : write_vdp_data_16(read_16(A1 + 0x0));
  DEF_ROMLOC(1CCA6) : move_toreg_32(A1 + 0x10, &A1); // LEA.L	16(A1),A1
  DEF_ROMLOC(1CCAA) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_1CC9E;           // DBF.W	D1,$1CC9E
  DEF_ROMLOC(1CCAE) : return; // RTS
}
ROMFUNC(rom_1CCB0) {
  DEF_ROMLOC(1CCB0)
      : move_toreg_32(read_32(A1 + 0x0), &D0); // MOVE.L	0(A1),D0
  DEF_ROMLOC(1CCB4)
      : move_toreg_8(read_8(A1 + 0xF), &D0);         // MOVE.B
                                                     // 15(A1),D0
  DEF_ROMLOC(1CCB8) : ror_toreg_32(0x8, &D0);        // ROR.L	#$08,D0
  DEF_ROMLOC(1CCBA) : write_vdp_data_32(D0);
  DEF_ROMLOC(1CCBC) : move_toreg_32(A1 + 0x10, &A1); // LEA.L	16(A1),A1
  DEF_ROMLOC(1CCC0) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_1CCB0;           // DBF.W	D1,$1CCB0
  DEF_ROMLOC(1CCC4) : return; // RTS
}
ROMFUNC(rom_1CCC6) {
  DEF_ROMLOC(1CCC6) : tst_mem_16(0xFFFFF7BE);      // TST.W	$F7BE
  DEF_ROMLOC(1CCCA) : if (!CCR_EQ) goto rom_1CCCE; // BNE.B	$1CCCE
  DEF_ROMLOC(1CCCC) : return;                      // RTS
  DEF_ROMLOC(1CCCE)
      : sub_tomem_16(0x1C0, 0xFFFFF7BE);           // SUBI.W
                                                   // #$01C0,$F7BE
  DEF_ROMLOC(1CCD4) : move_toreg_32(0x6A2E4, &A1); // LEA.L	$0006A2E4,A1
  DEF_ROMLOC(1CCDA) : move_toreg_32(0x0, &D0);     // MOVEQ.L	$00,D0
  DEF_ROMLOC(1CCDC)
      : move_toreg_16(read_16(0xFFFFF7BE), &D0); // MOVE.W	$F7BE,D0
  DEF_ROMLOC(1CCE0)
      : move_toreg_32((s32)A1 + (s8)0x0 + (s16)D0,
                      &A1);                          // LEA.L	0(A1,D0),A1
  DEF_ROMLOC(1CCE4) : add_toreg_16(0xFFFF8000, &D0); // ADDI.W	#$8000,D0
  DEF_ROMLOC(1CCE8) : lsl_toreg_32(0x2, &D0);        // LSL.L	#$02,D0
  DEF_ROMLOC(1CCEA) : lsr_toreg_16(0x2, &D0);        // LSR.W	#$02,D0
  DEF_ROMLOC(1CCEC) : or_toreg_16(0x4000, &D0);      // ORI.W	#$4000,D0
  DEF_ROMLOC(1CCF0) : SWAPWORDS(D0);                 // SWAP.W	D0
  DEF_ROMLOC(1CCF2) : write_vdp_control_32(D0);
  DEF_ROMLOC(1CCF6) : move_toreg_16(0xD, &D1);       // MOVE.W	#$000D,D1
  rom_1CB6E();
  return; // BRA.W	$1CB6E
}