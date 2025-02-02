#pragma once
#include "system.h"

typedef struct {
	u32 gfx_src;
	u16 vram_dst;
} plc;

void add_plc(void);
void new_plc(void);
void clear_plc(void);
void run_plc(void);
void dplc_process_2(void);
void quick_plc(void);
void plc_refresh_frame(void);