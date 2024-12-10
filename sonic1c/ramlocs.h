#pragma once

#define RAMLOC32(word) (0xff0000 | (word))

#define v_16x16 RAMLOC32(0xb000)
#define v_plc_buffer RAMLOC32(0xf6e0)
#define v_plc_buffer_end RAMLOC32(0xf700)