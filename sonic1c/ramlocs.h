#pragma once
#include "system.h"

#define RAMLOC32(word) (0xff0000 | (word))

#define v_256x256 RAMLOC32(0x0000)
#define v_ssbuffer1 RAMLOC32(0x0000)
#define v_lvllayout RAMLOC32(0xa400)
#define v_ngfx_buffer RAMLOC32(0xaa00)
#define v_16x16 RAMLOC32(0xb000)
extern u8 v_gamemode;
#define v_sgfx_buffer RAMLOC32(0xc800)
#define v_sgfx_buffer_end RAMLOC32(0xcae0)
#define v_hscrolltablebuffer RAMLOC32(0xcc00)
#define v_hscrolltablebuffer_end RAMLOC32(0xcf80)
#define v_hscrolltablebuffer_end_padded RAMLOC32(0xd000)
#define v_vdp_buffer1 RAMLOC32(0xf60c)
#define v_hbla_hreg RAMLOC32(0xf624)
#define v_vdp_buffer2 RAMLOC32(0xf640)
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
#define v_levelvariables RAMLOC32(0xf700)
#define v_screenposx RAMLOC32(0xf700)
#define v_screenposy RAMLOC32(0xf704)
#define v_bgscreenposx RAMLOC32(0xf708)
#define v_bgscreenposy RAMLOC32(0xf70c)
#define v_bg2screenposx RAMLOC32(0xf710)
#define v_bg2screenposy RAMLOC32(0xf714)
#define v_bg3screenposx RAMLOC32(0xf718)
#define v_bg3screenposy RAMLOC32(0xf71c)
#define v_limitleft1 RAMLOC32(0xf720)
#define v_limitright1 RAMLOC32(0xf722)
#define v_limittop1 RAMLOC32(0xf724)
#define v_limitbtm1 RAMLOC32(0xf726)
#define v_limitleft2 RAMLOC32(0xf728)
#define v_limitright2 RAMLOC32(0xf72a)
#define v_limittop2 RAMLOC32(0xf72c)
#define v_limitbtm2 RAMLOC32(0xf72e)
#define v_limitleft3 RAMLOC32(0xf732)
#define v_scrshiftx RAMLOC32(0xf73a)
#define v_scrshifty RAMLOC32(0xf73c)
#define v_lookshift RAMLOC32(0xf73e)
#define v_dle_routine RAMLOC32(0xf742)
#define f_lockscreen RAMLOC32(0xf7aa)
#define v_spritetablebuffer RAMLOC32(0xf800)
#define v_spritetablebuffer_end RAMLOC32(0xfa80)
#define v_palette_water_fading RAMLOC32(0xfa80)
#define v_palette_water RAMLOC32(0xfa80)
#define v_palette_water_end RAMLOC32(0xfb00)
#define v_palette RAMLOC32(0xfb00)
#define v_palette_end RAMLOC32(0xfb80)
#define v_debuguse RAMLOC32(0xfe08)
#define v_debugspeedtimer RAMLOC32(0xfe0a)
#define v_debugspeed RAMLOC32(0xfe0b)
#define v_vbla_count RAMLOC32(0xfe0c)
#define v_vbla_word RAMLOC32(0xfe0e)
#define v_vbla_byte RAMLOC32(0xfe0f)
#define v_zone RAMLOC32(0xfe10)
#define v_act RAMLOC32(0xfe11)
#define v_lives RAMLOC32(0xfe12)
#define v_air RAMLOC32(0xfe14)
#define f_timecount RAMLOC32(0xfe1e)
#define v_invinc RAMLOC32(0xfe2d)
#define v_ani0_time RAMLOC32(0xfec0)
#define v_ani0_frame RAMLOC32(0xfec1)
#define v_ani1_time RAMLOC32(0xfec2)
#define v_ani1_frame RAMLOC32(0xfec3)
#define v_ani2_time RAMLOC32(0xfec4)
#define v_ani2_frame RAMLOC32(0xfec5)
#define v_ani3_time RAMLOC32(0xfec6)
#define v_ani3_frame RAMLOC32(0xfec7)
#define v_ani3_buf RAMLOC32(0xfec8)
#define v_screenposx_dup RAMLOC32(0xff10)
#define v_screenposy_dup RAMLOC32(0xff14)
#define v_bgscreenposx_dup RAMLOC32(0xff18)
#define v_bgscreenposy_dup RAMLOC32(0xff1c)
#define v_bg2screenposx_dup RAMLOC32(0xff20)
#define v_bg2screenposy_dup RAMLOC32(0xff24)
#define v_bg3screenposx_dup RAMLOC32(0xff28)
#define v_bg3screenposy_dup RAMLOC32(0xff2c)
#define v_bg1_scroll_flags_dup RAMLOC32(0xff32)
#define v_bg2_scroll_flags_dup RAMLOC32(0xff34)
#define v_bg3_scroll_flags_dup RAMLOC32(0xff36)
#define v_fg_scroll_flags_dup RAMLOC32(0xff30)
#define v_title_ccount RAMLOC32(0xffe6)
#define v_demo RAMLOC32(0xfff0)
#define v_demonum RAMLOC32(0xfff2)
#define v_creditsnum RAMLOC32(0xfff4)
#define v_megadrive = RAMLOC32(0xfff8)
#define f_debugmode RAMLOC32(0xfffa)
#define v_init RAMLOC32(0xfffc)

extern u8 ram[0x10000];
extern void serialize_ram(void);