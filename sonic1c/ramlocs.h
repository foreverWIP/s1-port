#pragma once

#define RAMLOC32(word) (0xff0000 | (word))

#define v_256x256 RAMLOC32(0x0000)
#define v_16x16 RAMLOC32(0xb000)
#define v_plc_buffer RAMLOC32(0xf680)
#define v_random RAMLOC32(0xf636)