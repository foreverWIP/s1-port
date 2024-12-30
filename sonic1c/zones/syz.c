// #define CHECK_STUFF 1
#include "../opcodes.h"
#include "../system.h"

ROMFUNC(rom_6710) {
  DEF_ROMLOC(6710)
      : move_toreg_16(read_16(0xFFFFF73C), &D5); // MOVE.W	$F73C,D5
  DEF_ROMLOC(6714) : ext_reg_32(&D5);            // EXT.L	D5
  DEF_ROMLOC(6716) : asl_toreg_32(0x4, &D5);     // ASL.L	#$04,D5
  DEF_ROMLOC(6718) : move_toreg_32(D5, &D1);     // MOVE.L	D5,D1
  DEF_ROMLOC(671A) : asl_toreg_32(0x1, &D5);     // ASL.L	#$01,D5
  DEF_ROMLOC(671C) : add_toreg_32(D1, &D5);      // ADD.L	D1,D5
  DEF_ROMLOC(671E) : rom_6B2E();                 // BSR.W	$6B2E
  DEF_ROMLOC(6722)
      : move_tomem_16(read_16(0xFFFFF70C),
                      0xFFFFF618);                   // MOVE.W	$F70C,$F618
  DEF_ROMLOC(6728) : move_toreg_32(0xFFFFA800, &A1); // LEA.L	$A800,A1
  DEF_ROMLOC(672C)
      : move_toreg_16(read_16(0xFFFFF700), &D2); // MOVE.W	$F700,D2
  DEF_ROMLOC(6730) : neg_reg_16(&D2);            // NEG.W	D2
  DEF_ROMLOC(6732) : move_toreg_16(D2, &D0);     // MOVE.W	D2,D0
  DEF_ROMLOC(6734) : asr_toreg_16(0x3, &D0);     // ASR.W	#$03,D0
  DEF_ROMLOC(6736) : sub_toreg_16(D2, &D0);      // SUB.W	D2,D0
  DEF_ROMLOC(6738) : ext_reg_32(&D0);            // EXT.L	D0
  DEF_ROMLOC(673A) : asl_toreg_32(0x3, &D0);     // ASL.L	#$03,D0
  DEF_ROMLOC(673C) : divs_toreg_16(0x8, &D0);    // DIVS.W	#$0008,D0
  DEF_ROMLOC(6740) : ext_reg_32(&D0);            // EXT.L	D0
  DEF_ROMLOC(6742) : asl_toreg_32(0x4, &D0);     // ASL.L	#$04,D0
  DEF_ROMLOC(6744) : asl_toreg_32(0x8, &D0);     // ASL.L	#$08,D0
  DEF_ROMLOC(6746) : move_toreg_32(0x0, &D3);    // MOVEQ.L	$00,D3
  DEF_ROMLOC(6748) : move_toreg_16(D2, &D3);     // MOVE.W	D2,D3
  DEF_ROMLOC(674A) : asr_toreg_16(0x1, &D3);     // ASR.W	#$01,D3
  DEF_ROMLOC(674C) : move_toreg_16(0x7, &D1);    // MOVE.W	#$0007,D1
  DEF_ROMLOC(6750)
      : move_tomem_16(D3, (A1 += 2, A1 - 2)); // MOVE.W	D3,(A1)+
  DEF_ROMLOC(6752) : swap_reg_16(&D3);        // SWAP.W	D3
  DEF_ROMLOC(6754) : add_toreg_32(D0, &D3);   // ADD.L	D0,D3
  DEF_ROMLOC(6756) : swap_reg_16(&D3);        // SWAP.W	D3
  DEF_ROMLOC(6758) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_6750;                            // DBF.W	D1,$6750
  DEF_ROMLOC(675C) : move_toreg_16(D2, &D0);  // MOVE.W	D2,D0
  DEF_ROMLOC(675E) : asr_toreg_16(0x3, &D0);  // ASR.W	#$03,D0
  DEF_ROMLOC(6760) : move_toreg_16(0x4, &D1); // MOVE.W	#$0004,D1
  DEF_ROMLOC(6764)
      : move_tomem_16(D0, (A1 += 2, A1 - 2)); // MOVE.W	D0,(A1)+
  DEF_ROMLOC(6766) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_6764;                            // DBF.W	D1,$6764
  DEF_ROMLOC(676A) : move_toreg_16(D2, &D0);  // MOVE.W	D2,D0
  DEF_ROMLOC(676C) : asr_toreg_16(0x2, &D0);  // ASR.W	#$02,D0
  DEF_ROMLOC(676E) : move_toreg_16(0x5, &D1); // MOVE.W	#$0005,D1
  DEF_ROMLOC(6772)
      : move_tomem_16(D0, (A1 += 2, A1 - 2)); // MOVE.W	D0,(A1)+
  DEF_ROMLOC(6774) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_6772;                            // DBF.W	D1,$6772
  DEF_ROMLOC(6778) : move_toreg_16(D2, &D0);  // MOVE.W	D2,D0
  DEF_ROMLOC(677A) : move_toreg_16(D2, &D1);  // MOVE.W	D2,D1
  DEF_ROMLOC(677C) : asr_toreg_16(0x1, &D1);  // ASR.W	#$01,D1
  DEF_ROMLOC(677E) : sub_toreg_16(D1, &D0);   // SUB.W	D1,D0
  DEF_ROMLOC(6780) : ext_reg_32(&D0);         // EXT.L	D0
  DEF_ROMLOC(6782) : asl_toreg_32(0x4, &D0);  // ASL.L	#$04,D0
  DEF_ROMLOC(6784) : divs_toreg_16(0xE, &D0); // DIVS.W	#$000E,D0
  DEF_ROMLOC(6788) : ext_reg_32(&D0);         // EXT.L	D0
  DEF_ROMLOC(678A) : asl_toreg_32(0x4, &D0);  // ASL.L	#$04,D0
  DEF_ROMLOC(678C) : asl_toreg_32(0x8, &D0);  // ASL.L	#$08,D0
  DEF_ROMLOC(678E) : move_toreg_32(0x0, &D3); // MOVEQ.L	$00,D3
  DEF_ROMLOC(6790) : move_toreg_16(D2, &D3);  // MOVE.W	D2,D3
  DEF_ROMLOC(6792) : asr_toreg_16(0x1, &D3);  // ASR.W	#$01,D3
  DEF_ROMLOC(6794) : move_toreg_16(0xD, &D1); // MOVE.W	#$000D,D1
  DEF_ROMLOC(6798)
      : move_tomem_16(D3, (A1 += 2, A1 - 2)); // MOVE.W	D3,(A1)+
  DEF_ROMLOC(679A) : swap_reg_16(&D3);        // SWAP.W	D3
  DEF_ROMLOC(679C) : add_toreg_32(D0, &D3);   // ADD.L	D0,D3
  DEF_ROMLOC(679E) : swap_reg_16(&D3);        // SWAP.W	D3
  DEF_ROMLOC(67A0) : dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_6798;                                   // DBF.W	D1,$6798
  DEF_ROMLOC(67A4) : move_toreg_32(0xFFFFA800, &A2); // LEA.L	$A800,A2
  DEF_ROMLOC(67A8)
      : move_toreg_16(read_16(0xFFFFF70C), &D0); // MOVE.W	$F70C,D0
  DEF_ROMLOC(67AC) : move_toreg_16(D0, &D2);     // MOVE.W	D0,D2
  DEF_ROMLOC(67AE) : and_toreg_16(0x1F0, &D0);   // ANDI.W	#$01F0,D0
  DEF_ROMLOC(67B2) : lsr_toreg_16(0x3, &D0);     // LSR.W	#$03,D0
  DEF_ROMLOC(67B4)
      : move_toreg_32((s32)A2 + (s8)0x0 + (s16)D0,
                      &A2); // LEA.L	0(A2,D0),A2
  rom_66CC();               // BRA.W	$66CC
}