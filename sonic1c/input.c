// #define CHECK_STUFF 1
#include "opcodes.h"
#include "system.h"


void input_init(void) {
  return;
}
void input_read_controller(u8 controller_num);
void input_read_controllers(void) {
  u32 a1before = 0;
  DEF_ROMLOC(11E6) : move_toreg_32(0xFFFFF604, &A0); // LEA.L	$F604,A0
  DEF_ROMLOC(11EA) : move_toreg_32(0xA10003, &A1);   // LEA.L	$00A10003,A1
  DEF_ROMLOC(11F0) : input_read_controller(0);                     // BSR.B	$11F4
  DEF_ROMLOC(11F2) : add_toreg_16(0x2, &A1);         // ADDQ.W	#$02,A1
  input_read_controller(1);
}
void input_read_controller(u8 controller_num) {
  u8 (*joy_read_func)(void);
  void (*joy_write_func)(u8);
  if (controller_num == 0) {
	joy_read_func = read_joy1;
	joy_write_func = write_joy1;
  } else {
	joy_read_func = read_joy2;
	joy_write_func = write_joy2;
  }
  DEF_ROMLOC(11F4) : joy_write_func(0x0);
  DEF_ROMLOC(11FC) : move_toreg_8(joy_read_func(), &D0); // MOVE.B	(A1),D0
  DEF_ROMLOC(11FE) : lsl_toreg_8(0x2, &D0);         // LSL.B	#$02,D0
  DEF_ROMLOC(1200) : and_toreg_8(0xFFFFFFC0, &D0);  // ANDI.B	#$C0,D0
  DEF_ROMLOC(1204) : joy_write_func(0x40);        // MOVE.B	#$40,(A1)
  DEF_ROMLOC(120C) : move_toreg_8(joy_read_func(), &D1); // MOVE.B	(A1),D1
  DEF_ROMLOC(120E) : and_toreg_8(0x3F, &D1);        // ANDI.B	#$3F,D1
  DEF_ROMLOC(1212) : or_toreg_8(D1, &D0);           // OR.B	D1,D0
  DEF_ROMLOC(1214) : not_reg_8(&D0);                // NOT.B	D0
  DEF_ROMLOC(1216) : move_toreg_8(read_8(A0), &D1); // MOVE.B	(A0),D1
  DEF_ROMLOC(1218) : eor_toreg_8(D0, &D1);          // EOR.B	D0,D1
  DEF_ROMLOC(121A) : move_tomem_8(D0, A0++);        // MOVE.B	D0,(A0)+
  DEF_ROMLOC(121C) : and_toreg_8(D0, &D1);          // AND.B	D0,D1
  DEF_ROMLOC(121E) : move_tomem_8(D1, A0++);        // MOVE.B	D1,(A0)+
  DEF_ROMLOC(1220) : return;                        // RTS
}