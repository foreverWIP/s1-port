// #define CHECK_STUFF 1
#include "opcodes.h"
#include "system.h"

void update_sound_driver(void) {}
void resume_music(void) {
  if (read_16(v_air) <= AIR_COUNTDOWN_THRESHOLD) {
    move_toreg_16(BGM_LZ, &D0);
    if (read_16(v_zone) == (ZONE16_LZ | 3)) {
      move_toreg_16(BGM_SBZ, &D0);
    }
    if (read_8(v_invinc) != 0) {
      move_toreg_16(BGM_INVINCIBLE, &D0);
    }
    if (read_8(f_lockscreen) != 0) {
      move_toreg_16(BGM_BOSS, &D0);
    }
    play_sound();
  }
  move_tomem_16(MAX_AIR_SECONDS, v_air);
  clr_mem_8(0xFFFFD372);
}