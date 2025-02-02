#pragma once

#define RAMLOC32(word) (0xff0000 | (word))

#define v_256x256 RAMLOC32(0x0000)
#define v_ngfx_buffer RAMLOC32(0xaa00)
#define v_16x16 RAMLOC32(0xb000)
#define v_plc_buffer RAMLOC32(0xf680)
#define v_plc_patternsleft RAMLOC32(0xf6f8)
#define v_plc_framepatternsleft RAMLOC32(0xf6fa)
#define v_plc_buffer_end RAMLOC32(0xf700)
#define v_random RAMLOC32(0xf636)
#define v_plc_ptrnemcode RAMLOC32(0xf6e0)
#define v_plc_repeatcount RAMLOC32(0xf6e4)
#define v_plc_paletteindex RAMLOC32(0xf6e8)
#define v_plc_previousrow RAMLOC32(0xf6ec)
#define v_plc_dataword RAMLOC32(0xf6f0)
#define v_plc_shiftvalue RAMLOC32(0xf6f4)