// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_13172) {
  u8 switchindex = 0;
  DEF_ROMLOC(13172) : move_toreg_32(0x0, &D0); // MOVEQ.L	$00,D0
  DEF_ROMLOC(13174) : move_toreg_8(read_8(A0 + 0x24), &D0);
  switchindex = D0 / 2; // MOVE.B	36(A0),D0
  DEF_ROMLOC(13178)
      : move_toreg_16(read_16(0x13180 + (s16)(D0 & 0xffff)),
                      &D1); // MOVE.W	6(PC,D0),D1
  // DEF_ROMLOC(1317C): goto rom_13180 + (s16)(D1 & 0xffff); // JMP	2(PC,D1)
  DEF_ROMLOC(1317C) : switch (switchindex) {
  case 0:
    rom_1318A();
    break;
  case 1:
    rom_131EC();
    break;
  case 2:
    rom_131F8();
    break;
  case 3:
    rom_131FC();
    break;
  case 4:
    rom_1320A();
    break;
  }
}
ROMFUNC(rom_1318A) {
  DEF_ROMLOC(1318A) : add_tomem_8(0x4, A0 + 0x24); // ADDQ.B	#$04,36(A0)
  DEF_ROMLOC(1318E)
      : move_tomem_32(0x13228, A0 + 0x4); // MOVE.L	#$00013228,4(A0)
  DEF_ROMLOC(13196) : move_tomem_16(0x4259, A0 + 0x2); // MOVE.W
                                                       // #$4259,2(A0)
  DEF_ROMLOC(1319C) : or_tomem_8(0x4, A0 + 0x1);       // ORI.B	#$04,1(A0)
  DEF_ROMLOC(131A2) : move_tomem_8(0x18, A0 + 0x19);   // MOVE.B	#$18,25(A0)
  DEF_ROMLOC(131A8) : move_tomem_8(0x1, A0 + 0x18);    // MOVE.B	#$01,24(A0)
  DEF_ROMLOC(131AE)
      : move_toreg_8(read_8(A0 + 0x28), &D0);      // MOVE.B	40(A0),D0
  DEF_ROMLOC(131B2) : if (CCR_PL) goto rom_131BA;  // BPL.B	$131BA
  DEF_ROMLOC(131B4) : bset_tomem_8(0x7, A0 + 0x2); // BSET.B	#$07,2(A0)
  DEF_ROMLOC(131BA) : and_toreg_8(0xF, &D0);       // ANDI.B	#$0F,D0
  DEF_ROMLOC(131BE) : move_tomem_8(D0, A0 + 0x1A); // MOVE.B	D0,26(A0)
  DEF_ROMLOC(131C2) : cmp_toreg_8(0x9, &D0);       // CMPI.B	#$09,D0
  DEF_ROMLOC(131C6) : if (!CCR_EQ) {
    rom_131F8();
    return;
  }                                                 // BNE.B	$131F8
  DEF_ROMLOC(131C8) : clr_mem_8(A0 + 0x18);         // CLR.B	24(A0)
  DEF_ROMLOC(131CC) : sub_tomem_8(0x2, A0 + 0x24);  // SUBQ.B	#$02,36(A0)
  DEF_ROMLOC(131D0) : btst_tomem_8(0x6, A0 + 0x28); // BTST.B	#$06,40(A0)
  DEF_ROMLOC(131D6) : if (CCR_EQ) goto rom_131DE;   // BEQ.B	$131DE
  DEF_ROMLOC(131D8) : move_tomem_8(0x6, A0 + 0x24); // MOVE.B	#$06,36(A0)
  DEF_ROMLOC(131DE) : btst_tomem_8(0x5, A0 + 0x28); // BTST.B	#$05,40(A0)
  DEF_ROMLOC(131E4) : if (CCR_EQ) {
    rom_131EC();
    return;
  }                                                 // BEQ.B	$131EC
  DEF_ROMLOC(131E6) : move_tomem_8(0x8, A0 + 0x24); // MOVE.B	#$08,36(A0)
  rom_131EC(); // Detected flow into next function
}
ROMFUNC(rom_131EC) {
  DEF_ROMLOC(131EC) : move_toreg_32(0x13220, &A1); // LEA.L	$00013220,A1
  DEF_ROMLOC(131F2) : animate_sprite();                  // JSR	$0000ADA2
  rom_131F8(); // Detected flow into next function
}
ROMFUNC(rom_131F8) {
  rom_FD38(); // BRA.W	$FD38
}
ROMFUNC(rom_131FC) {
  DEF_ROMLOC(131FC)
      : move_toreg_16(read_16(0xFFFFF646), &D0);   // MOVE.W	$F646,D0
  DEF_ROMLOC(13200) : sub_toreg_16(0x10, &D0);     // SUBI.W	#$0010,D0
  DEF_ROMLOC(13204) : move_tomem_16(D0, A0 + 0xC); // MOVE.W	D0,12(A0)
  rom_131EC();                                     // BRA.B	$131EC
}
ROMFUNC(rom_1320A) {
  DEF_ROMLOC(1320A) : bclr_tomem_8(0x7, A0 + 0x2);  // BCLR.B	#$07,2(A0)
  DEF_ROMLOC(13210) : cmp_tomem_8(0x7, 0xFFFFA506); // CMPI.B	#$07,$A506
  DEF_ROMLOC(13216) : if (!CCR_EQ) goto rom_1321E;  // BNE.B	$1321E
  DEF_ROMLOC(13218) : bset_tomem_8(0x7, A0 + 0x2);  // BSET.B	#$07,2(A0)
  DEF_ROMLOC(1321E) : {
    rom_131EC();
    return;
  }                                         // BRA.B	$131EC
  DEF_ROMLOC(13220) : or_toreg_8(0x9, &D2); // ORI.B	#$09,D2
  rom_132AC();                              // Detected flow into next function
}