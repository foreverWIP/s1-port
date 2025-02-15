// #define CHECK_STUFF 1
#include "opcodes.h"
#include "system.h"

void play_sound(void) { move_tomem_8(D0, 0xFFFFF00A); }
void play_sound_special(void) { move_tomem_8(D0, 0xFFFFF00B); }
void update_sound_driver(void) {}
void resume_music(void) {
  if (read_16(0xFFFFFE14) <= 12) {
    move_toreg_16(0x82, &D0);
    if (read_16(v_zone) == 0x103) {
      move_toreg_16(0x86, &D0);
    }
    if (read_8(0xFFFFFE2D) != 0) {
      move_toreg_16(0x87, &D0);
    }
    if (read_8(0xFFFFF7AA) != 0) {
      move_toreg_16(0x8C, &D0);
    }
    play_sound();
  }
  move_tomem_16(0x1E, 0xFFFFFE14);
  clr_mem_8(0xFFFFD372);
}