#pragma once

#include "system.h"

typedef enum {
  OBJ_NULL,
  OBJ_SONIC,
} object_id;

typedef struct {
  object_id id;
  u8 subtype;
  bool flip_x;
  bool flip_y;
  bool screen_coords;
  u8 misc_render;
  u32 x;
  u32 y;
  s16 velx;
  s16 vely;
  s16 inertia;
  u8 width;
  u8 height;
  u8 draw_index;
  u8 action_width;
  u8 ani_frame;
  u8 ani;
  u8 prev_ani;
  u8 ani_time_left;
  u8 ani_time_delay;
  u8 state;
  u8 substate;
  u16 angle;
} object;