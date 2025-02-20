#include "opcodes.h"
#include "system.h"

static plc plc_main[] = {
    {.gfx_src = 0x3AE64, .vram_dst = 0xF400},
    {.gfx_src = 0x39812, .vram_dst = 0xD940},
    {.gfx_src = 0x39908, .vram_dst = 0xFA80},
    {.gfx_src = 0x39A0E, .vram_dst = 0xF640},
    {.gfx_src = 0x3A5C8, .vram_dst = 0xF2E0},
    {.gfx_src = 0x00000, .vram_dst = 0x0000},
};
static plc plc_main_2[] = {
    {.gfx_src = 0x39B02, .vram_dst = 0xD000},
    {.gfx_src = 0x2C730, .vram_dst = 0xA820},
    {.gfx_src = 0x2C8C6, .vram_dst = 0xAB80},
    {.gfx_src = 0x00000, .vram_dst = 0x0000},
};
static plc plc_explode[] = {
    {.gfx_src = 0x39F62, .vram_dst = 0xB400},
    {.gfx_src = 0x00000, .vram_dst = 0x0000},
};
static plc plc_gameover[] = {
    {.gfx_src = 0x3A678, .vram_dst = 0xABC0},
    {.gfx_src = 0x00000, .vram_dst = 0x0000},
};
static plc plc_ghz[] = {
    {.gfx_src = 0x3CB3C, .vram_dst = 0x0000},
    {.gfx_src = 0x3E19C, .vram_dst = 0x39A0},
    {.gfx_src = 0x2F8C8, .vram_dst = 0x6B00},
    {.gfx_src = 0x300BA, .vram_dst = 0x7A00},
    {.gfx_src = 0x35EB0, .vram_dst = 0x8000},
    {.gfx_src = 0x3639E, .vram_dst = 0x8880},
    {.gfx_src = 0x37016, .vram_dst = 0x8F60},
    {.gfx_src = 0x37CB6, .vram_dst = 0x9360},
    {.gfx_src = 0x37A2C, .vram_dst = 0x9E00},
    {.gfx_src = 0x2FCFE, .vram_dst = 0xA360},
    {.gfx_src = 0x3A80A, .vram_dst = 0xA460},
    {.gfx_src = 0x3A90C, .vram_dst = 0xA660},
    {.gfx_src = 0x00000, .vram_dst = 0x0000},
};
static plc plc_ghz_2[] = {
    {.gfx_src = 0x2F912, .vram_dst = 0x7000},
    {.gfx_src = 0x2FA2C, .vram_dst = 0x71C0},
    {.gfx_src = 0x2FF8E, .vram_dst = 0x7300},
    {.gfx_src = 0x2FB60, .vram_dst = 0x7540},
    {.gfx_src = 0x301E8, .vram_dst = 0xA1E0},
    {.gfx_src = 0x30286, .vram_dst = 0x6980},
    {.gfx_src = 0x00000, .vram_dst = 0x0000},
};
static plc plc_lz[] = {
    {.gfx_src = 0x4197E, .vram_dst = 0x0000},
    {.gfx_src = 0x32514, .vram_dst = 0x3C00},
    {.gfx_src = 0x31FFA, .vram_dst = 0x3E00},
    {.gfx_src = 0x3040A, .vram_dst = 0x4B20},
    {.gfx_src = 0x302E6, .vram_dst = 0x6000},
    {.gfx_src = 0x30BFE, .vram_dst = 0x6200},
    {.gfx_src = 0x30D7E, .vram_dst = 0x6500},
    {.gfx_src = 0x30EE8, .vram_dst = 0x6900},
    {.gfx_src = 0x3153E, .vram_dst = 0x7780},
    {.gfx_src = 0x315F4, .vram_dst = 0x7880},
    {.gfx_src = 0x31696, .vram_dst = 0x7980},
    {.gfx_src = 0x3692C, .vram_dst = 0x94C0},
    {.gfx_src = 0x00000, .vram_dst = 0x0000},
};
static plc plc_lz_2[] = {
    {.gfx_src = 0x317F2, .vram_dst = 0x7BC0},
    {.gfx_src = 0x31856, .vram_dst = 0x7CC0},
    {.gfx_src = 0x319A8, .vram_dst = 0x7EC0},
    {.gfx_src = 0x31E8A, .vram_dst = 0x5D20},
    {.gfx_src = 0x322B2, .vram_dst = 0x89E0},
    {.gfx_src = 0x38E98, .vram_dst = 0x8CE0},
    {.gfx_src = 0x3727E, .vram_dst = 0x90C0},
    {.gfx_src = 0x344C4, .vram_dst = 0xA1E0},
    {.gfx_src = 0x323EA, .vram_dst = 0xA000},
    {.gfx_src = 0x2FCFE, .vram_dst = 0xA360},
    {.gfx_src = 0x3A80A, .vram_dst = 0xA460},
    {.gfx_src = 0x3A90C, .vram_dst = 0xA660},
    {.gfx_src = 0x00000, .vram_dst = 0x0000},
};
static plc plc_mz[] = {
    {.gfx_src = 0x464C0, .vram_dst = 0x0000},
    {.gfx_src = 0x32624, .vram_dst = 0x6000},
    {.gfx_src = 0x32A7C, .vram_dst = 0x68A0},
    {.gfx_src = 0x2F912, .vram_dst = 0x7000},
    {.gfx_src = 0x32970, .vram_dst = 0x71C0},
    {.gfx_src = 0x32D5A, .vram_dst = 0x7500},
    {.gfx_src = 0x3639E, .vram_dst = 0x8880},
    {.gfx_src = 0x382D4, .vram_dst = 0x8F60},
    {.gfx_src = 0x386BC, .vram_dst = 0x9700},
    {.gfx_src = 0x39076, .vram_dst = 0x9FE0},
    {.gfx_src = 0x00000, .vram_dst = 0x0000},
};
static plc plc_mz_2[] = {
    {.gfx_src = 0x328B2, .vram_dst = 0xA260},
    {.gfx_src = 0x2FCFE, .vram_dst = 0xA360},
    {.gfx_src = 0x3A80A, .vram_dst = 0xA460},
    {.gfx_src = 0x3A90C, .vram_dst = 0xA660},
    {.gfx_src = 0x33670, .vram_dst = 0x5700},
    {.gfx_src = 0x00000, .vram_dst = 0x0000},
};
static plc plc_slz[] = {
    {.gfx_src = 0x4AC88, .vram_dst = 0x0000},
    {.gfx_src = 0x38C00, .vram_dst = 0x8000},
    {.gfx_src = 0x38E98, .vram_dst = 0x8520},
    {.gfx_src = 0x32A7C, .vram_dst = 0x9000},
    {.gfx_src = 0x34148, .vram_dst = 0x9C00},
    {.gfx_src = 0x33E22, .vram_dst = 0xA260},
    {.gfx_src = 0x2FCFE, .vram_dst = 0xA360},
    {.gfx_src = 0x3A80A, .vram_dst = 0xA460},
    {.gfx_src = 0x3A90C, .vram_dst = 0xA660},
    {.gfx_src = 0x00000, .vram_dst = 0x0000},
};
static plc plc_slz_2[] = {
    {.gfx_src = 0x3385C, .vram_dst = 0x6E80},
    {.gfx_src = 0x33BDE, .vram_dst = 0x7400},
    {.gfx_src = 0x33E84, .vram_dst = 0x7980},
    {.gfx_src = 0x33F66, .vram_dst = 0x7B80},
    {.gfx_src = 0x34254, .vram_dst = 0x9B00},
    {.gfx_src = 0x33A98, .vram_dst = 0x9E00},
    {.gfx_src = 0x00000, .vram_dst = 0x0000},
};
static plc plc_syz[] = {
    {.gfx_src = 0x5157A, .vram_dst = 0x0000},
    {.gfx_src = 0x35EB0, .vram_dst = 0x8000},
    {.gfx_src = 0x3639E, .vram_dst = 0x8880},
    {.gfx_src = 0x382D4, .vram_dst = 0x8F60},
    {.gfx_src = 0x37508, .vram_dst = 0x9700},
    {.gfx_src = 0x00000, .vram_dst = 0x0000},
};
static plc plz_syz_2[] = {
    {.gfx_src = 0x342F8, .vram_dst = 0x7000},
    {.gfx_src = 0x345A6, .vram_dst = 0x72C0},
    {.gfx_src = 0x34462, .vram_dst = 0x7740},
    {.gfx_src = 0x39076, .vram_dst = 0x9FE0},
    {.gfx_src = 0x344C4, .vram_dst = 0xA1E0},
    {.gfx_src = 0x2FCFE, .vram_dst = 0xA360},
    {.gfx_src = 0x3A80A, .vram_dst = 0xA460},
    {.gfx_src = 0x3A90C, .vram_dst = 0xA660},
    {.gfx_src = 0x00000, .vram_dst = 0x0000},
};
static plc plc_sbz[] = {
    {.gfx_src = 0x57EF0, .vram_dst = 0x0000},
    {.gfx_src = 0x34D28, .vram_dst = 0x5800},
    {.gfx_src = 0x35836, .vram_dst = 0x5D00},
    {.gfx_src = 0x359DA, .vram_dst = 0x5E00},
    {.gfx_src = 0x35AF0, .vram_dst = 0x6040},
    {.gfx_src = 0x34834, .vram_dst = 0x6880},
    {.gfx_src = 0x34888, .vram_dst = 0x6900},
    {.gfx_src = 0x345A6, .vram_dst = 0x7220},
    {.gfx_src = 0x34B24, .vram_dst = 0x76A0},
    {.gfx_src = 0x356AA, .vram_dst = 0x7B20},
    {.gfx_src = 0x353D4, .vram_dst = 0x7EA0},
    {.gfx_src = 0x355AC, .vram_dst = 0x9860},
    {.gfx_src = 0x00000, .vram_dst = 0x0000},
};
static plc plc_sbz_2[] = {
    {.gfx_src = 0x39076, .vram_dst = 0x5600},
    {.gfx_src = 0x38C00, .vram_dst = 0x8000},
    {.gfx_src = 0x38E98, .vram_dst = 0x8520},
    {.gfx_src = 0x35886, .vram_dst = 0x8C00},
    {.gfx_src = 0x358DE, .vram_dst = 0x8DE0},
    {.gfx_src = 0x3542C, .vram_dst = 0x8FC0},
    {.gfx_src = 0x351F6, .vram_dst = 0x9240},
    {.gfx_src = 0x353D4, .vram_dst = 0x7F20},
    {.gfx_src = 0x34EC6, .vram_dst = 0x9BE0},
    {.gfx_src = 0x344C4, .vram_dst = 0xA1E0},
    {.gfx_src = 0x2FCFE, .vram_dst = 0xA360},
    {.gfx_src = 0x3A80A, .vram_dst = 0xA460},
    {.gfx_src = 0x3A90C, .vram_dst = 0xA660},
    {.gfx_src = 0x00000, .vram_dst = 0x0000},
};
static plc plc_title_card[] = {
    {.gfx_src = 0x39204, .vram_dst = 0xB000},
    {.gfx_src = 0x00000, .vram_dst = 0x0000},
};
static plc plc_boss_common[] = {
    {.gfx_src = 0x5D0FC, .vram_dst = 0x8000},
    {.gfx_src = 0x5D960, .vram_dst = 0x8D80},
    {.gfx_src = 0x5DC4A, .vram_dst = 0x93A0},
    {.gfx_src = 0x38C00, .vram_dst = 0xA300},
    {.gfx_src = 0x33A98, .vram_dst = 0xA300},
    {.gfx_src = 0x5F9E2, .vram_dst = 0xA540},
    {.gfx_src = 0x00000, .vram_dst = 0x0000},
};
static plc plc_signpost[] = {
    {.gfx_src = 0x3A9E8, .vram_dst = 0xD000},
    {.gfx_src = 0x3B098, .vram_dst = 0x96C0},
    {.gfx_src = 0x3AF24, .vram_dst = 0x8C40},
    {.gfx_src = 0x00000, .vram_dst = 0x0000},
};
static plc plc_special[] = {
    {.gfx_src = 0x2E48A, .vram_dst = 0x0000},
    {.gfx_src = 0x2D4FA, .vram_dst = 0x0A20},
    {.gfx_src = 0x2CA8E, .vram_dst = 0x2840},
    {.gfx_src = 0x342F8, .vram_dst = 0x4760},
    {.gfx_src = 0x2E97E, .vram_dst = 0x4A20},
    {.gfx_src = 0x2F1E0, .vram_dst = 0x4C60},
    {.gfx_src = 0x2EA6C, .vram_dst = 0x5E00},
    {.gfx_src = 0x2EB3C, .vram_dst = 0x6E00},
    {.gfx_src = 0x2EC32, .vram_dst = 0x7E00},
    {.gfx_src = 0x2EC90, .vram_dst = 0x8E00},
    {.gfx_src = 0x2F53C, .vram_dst = 0x9E00},
    {.gfx_src = 0x2F5EC, .vram_dst = 0xAE00},
    {.gfx_src = 0x2F6C6, .vram_dst = 0xBE00},
    {.gfx_src = 0x2F3D4, .vram_dst = 0xEE00},
    {.gfx_src = 0x2ED22, .vram_dst = 0xF2E0},
    {.gfx_src = 0x2EDE4, .vram_dst = 0xF400},
    {.gfx_src = 0x2EEB2, .vram_dst = 0xF520},
    {.gfx_src = 0x2EF7E, .vram_dst = 0xF2E0},
    {.gfx_src = 0x2F046, .vram_dst = 0xF400},
    {.gfx_src = 0x2F110, .vram_dst = 0xF520},
    {.gfx_src = 0x00000, .vram_dst = 0x0000},
};
static plc plc_animals_ghz[] = {
    {.gfx_src = 0x3B884, .vram_dst = 0xB000},
    {.gfx_src = 0x3BF06, .vram_dst = 0xB240},
    {.gfx_src = 0x00000, .vram_dst = 0x0000},
};
static plc plc_animals_lz[] = {
    {.gfx_src = 0x3BB38, .vram_dst = 0xB000},
    {.gfx_src = 0x3BCB4, .vram_dst = 0xB240},
    {.gfx_src = 0x00000, .vram_dst = 0x0000},
};
static plc plc_animals_mz[] = {
    {.gfx_src = 0x3C040, .vram_dst = 0xB000},
    {.gfx_src = 0x3BCB4, .vram_dst = 0xB240},
    {.gfx_src = 0x00000, .vram_dst = 0x0000},
};
static plc plc_animals_slz[] = {
    {.gfx_src = 0x3BDD0, .vram_dst = 0xB000},
    {.gfx_src = 0x3BF06, .vram_dst = 0xB240},
    {.gfx_src = 0x00000, .vram_dst = 0x0000},
};
static plc plc_animals_syz[] = {
    {.gfx_src = 0x3BDD0, .vram_dst = 0xB000},
    {.gfx_src = 0x3B9DC, .vram_dst = 0xB240},
    {.gfx_src = 0x00000, .vram_dst = 0x0000},
};
static plc plc_animals_sbz[] = {
    {.gfx_src = 0x3B884, .vram_dst = 0xB000},
    {.gfx_src = 0x3B9DC, .vram_dst = 0xB240},
    {.gfx_src = 0x00000, .vram_dst = 0x0000},
};
static plc plc_ss_result[] = {
    {.gfx_src = 0x2F74A, .vram_dst = 0xA820},
    {.gfx_src = 0x3B64A, .vram_dst = 0xAA20},
    {.gfx_src = 0x00000, .vram_dst = 0x0000},
};
static plc plc_ending[] = {
    {.gfx_src = 0x3CB3C, .vram_dst = 0x0000},
    {.gfx_src = 0x3E19C, .vram_dst = 0x39A0},
    {.gfx_src = 0x2F8C8, .vram_dst = 0x6B00},
    {.gfx_src = 0x61DB2, .vram_dst = 0x7400},
    {.gfx_src = 0x5FB02, .vram_dst = 0x78A0},
    {.gfx_src = 0x5FD00, .vram_dst = 0x7C20},
    {.gfx_src = 0x3B884, .vram_dst = 0xAA60},
    {.gfx_src = 0x3B9DC, .vram_dst = 0xACA0},
    {.gfx_src = 0x3BB38, .vram_dst = 0xAE60},
    {.gfx_src = 0x3BCB4, .vram_dst = 0xB0A0},
    {.gfx_src = 0x3BDD0, .vram_dst = 0xB260},
    {.gfx_src = 0x3BF06, .vram_dst = 0xB4A0},
    {.gfx_src = 0x3C040, .vram_dst = 0xB660},
    {.gfx_src = 0x62638, .vram_dst = 0xB8A0},
    {.gfx_src = 0x00000, .vram_dst = 0x0000},
};
static plc plc_try_again[] = {
    {.gfx_src = 0x5FB02, .vram_dst = 0x78A0},
    {.gfx_src = 0x60EDE, .vram_dst = 0x7C20},
    {.gfx_src = 0x6203A, .vram_dst = 0xB400},
    {.gfx_src = 0x00000, .vram_dst = 0x0000},
};
static plc plc_eggman_sbz2[] = {
    {.gfx_src = 0x355AC, .vram_dst = 0xA300},
    {.gfx_src = 0x5E4CE, .vram_dst = 0x8000},
    {.gfx_src = 0x344C4, .vram_dst = 0x9400},
    {.gfx_src = 0x00000, .vram_dst = 0x0000},
};
static plc plc_boss_fz[] = {
    {.gfx_src = 0x5F462, .vram_dst = 0x7400},
    {.gfx_src = 0x5ECFA, .vram_dst = 0x6000},
    {.gfx_src = 0x5D0FC, .vram_dst = 0x8000},
    {.gfx_src = 0x5E4CE, .vram_dst = 0x8E00},
    {.gfx_src = 0x5F9E2, .vram_dst = 0xA540},
    {.gfx_src = 0x00000, .vram_dst = 0x0000},
};

static plc *plcs[] = {
    plc_main,        plc_main_2,      plc_explode,     plc_gameover,
    plc_ghz,         plc_ghz_2,       plc_lz,          plc_lz_2,
    plc_mz,          plc_mz_2,        plc_slz,         plc_slz_2,
    plc_syz,         plz_syz_2,       plc_sbz,         plc_sbz_2,
    plc_title_card,  plc_boss_common, plc_signpost,    plc_special,
    plc_special,     plc_animals_ghz, plc_animals_lz,  plc_animals_mz,
    plc_animals_slz, plc_animals_syz, plc_animals_sbz, plc_ss_result,
    plc_ending,      plc_try_again,   plc_eggman_sbz2, plc_boss_fz,
};

void plc_dplc_finish(void);

void create_plc_common(bool clear_buffer) {
  u32 a1backup = 0;
  u32 a2backup = 0;
  DEF_ROMLOC(15AA) : a1backup = A1;
  a2backup = A2;               // TODO; // MOVEM.L	A1-A2,-(A7)
  move_toreg_32(0x1DD86, &A1); // LEA.L	$0001DD86,A1
  add_toreg_16(D0, &D0);       // ADD.W	D0,D0
  move_toreg_16(read_16((s32)A1 + (s8)0x0 + (s16)D0),
                &D0); // MOVE.W	0(A1,D0),D0
  move_toreg_32((s32)A1 + (s8)0x0 + (s16)D0,
                &A1); // LEA.L	0(A1,D0),A1
  if (clear_buffer) {
    clear_plc(); // BSR.B	$15D6
  }
  move_toreg_32(v_plc_buffer, &A2); // LEA.L	$F680,A2
  if (!clear_buffer) {
  noclear_innerloop:
    tst_mem_32(A2); // TST.L	(A2)
    if (CCR_EQ)
      goto noclear_continue; // BEQ.B	$1598
    add_toreg_16(0x6, &A2);  // ADDQ.W	#$06,A2
    goto noclear_innerloop;
  }
noclear_continue:
  move_toreg_16(read_16((A1 += 2, A1 - 2)), &D0); // MOVE.W	(A1)+,D0
  if (CCR_MI)
    goto finish; // BMI.B	$15D0
loop:
  move_tomem_32(read_32((A1 += 4, A1 - 4)),
                (A2 += 4, A2 - 4)); // MOVE.L	(A1)+,(A2)+
  move_tomem_16(read_16((A1 += 2, A1 - 2)),
                (A2 += 2, A2 - 2)); // MOVE.W	(A1)+,(A2)+
  dec_reg_16(&D0);
  if ((D0 & 0xffff) != 0xffff)
    goto loop; // DBF.W	D0,$15C8
finish:
  A1 = a1backup;
  A2 = a2backup; // TODO; // MOVEM.L	(A7)+,A1-A2
}
void add_plc(void) { create_plc_common(false); }
void new_plc(void) { create_plc_common(true); }
void clear_plc(void) {
  for (u32 ptr = v_plc_buffer; ptr < v_plc_buffer_end; ptr += 4) {
    write_32(ptr, 0);
  }
  D0 = 0xffff;
  A2 = v_plc_buffer_end;
}
void run_plc(void) {
  DEF_ROMLOC(15E4) : tst_mem_32(v_plc_buffer);       // TST.L	$F680
  DEF_ROMLOC(15E8) : if (CCR_EQ) goto rom_1638;      // BEQ.B	$1638
  DEF_ROMLOC(15EA) : tst_mem_16(v_plc_patternsleft); // TST.W	$F6F8
  DEF_ROMLOC(15EE) : if (!CCR_EQ) goto rom_1638;     // BNE.B	$1638
  DEF_ROMLOC(15F0)
      : move_toreg_32(read_32(v_plc_buffer), &A0);   // MOVEA.L	$F680,A0
  DEF_ROMLOC(15F4) : move_toreg_32(0x14FA, &A3);     // LEA.L	$000014FA,A3
  DEF_ROMLOC(15FA) : move_toreg_32(0xFFFFAA00, &A1); // LEA.L	$AA00,A1
  DEF_ROMLOC(15FE)
      : move_toreg_16(read_16((A0 += 2, A0 - 2)), &D2); // MOVE.W	(A0)+,D2
  DEF_ROMLOC(1600) : if (CCR_PL) goto rom_1606;         // BPL.B	$1606
  DEF_ROMLOC(1602) : add_toreg_16(0xA, &A3);            // ADDA.W	#$000A,A3
  DEF_ROMLOC(1606) : and_toreg_16(0x7FFF, &D2);         // ANDI.W	#$7FFF,D2
  DEF_ROMLOC(160A)
      : move_tomem_16(D2, v_plc_patternsleft);        // MOVE.W	D2,$F6F8
  DEF_ROMLOC(160E) : rom_1526();                      // BSR.W	$1526
  DEF_ROMLOC(1612) : move_toreg_8(read_8(A0++), &D5); // MOVE.B	(A0)+,D5
  DEF_ROMLOC(1614) : asl_toreg_16(0x8, &D5);          // ASL.W	#$08,D5
  DEF_ROMLOC(1616) : move_toreg_8(read_8(A0++), &D5); // MOVE.B	(A0)+,D5
  DEF_ROMLOC(1618) : move_toreg_32(0x10, &D6);        // MOVEQ.L	$10,D6
  DEF_ROMLOC(161A) : move_toreg_32(0x0, &D0);         // MOVEQ.L	$00,D0
  DEF_ROMLOC(161C) : move_tomem_32(A0, v_plc_buffer); // MOVE.L	A0,$F680
  DEF_ROMLOC(1620) : move_tomem_32(A3, 0xFFFFF6E0);   // MOVE.L	A3,$F6E0
  DEF_ROMLOC(1624) : move_tomem_32(D0, 0xFFFFF6E4);   // MOVE.L	D0,$F6E4
  DEF_ROMLOC(1628) : move_tomem_32(D0, 0xFFFFF6E8);   // MOVE.L	D0,$F6E8
  DEF_ROMLOC(162C) : move_tomem_32(D0, 0xFFFFF6EC);   // MOVE.L	D0,$F6EC
  DEF_ROMLOC(1630) : move_tomem_32(D5, 0xFFFFF6F0);   // MOVE.L	D5,$F6F0
  DEF_ROMLOC(1634) : move_tomem_32(D6, 0xFFFFF6F4);   // MOVE.L	D6,$F6F4
  DEF_ROMLOC(1638) : return;                          // RTS
}
void plc_pop_front(void) {
  DEF_ROMLOC(16D4) : move_toreg_32(v_plc_buffer, &A0); // LEA.L	$F680,A0
  DEF_ROMLOC(16D8) : move_toreg_32(0x15, &D0);         // MOVEQ.L	$15,D0
  DEF_ROMLOC(16DA) : move_tomem_32(read_32(A0 + 0x6), A0);
  A0 += 4; // MOVE.L	6(A0),(A0)+
  DEF_ROMLOC(16DE) : dec_reg_16(&D0);
  if ((D0 & 0xffff) != 0xffff)
    goto rom_16DA; // DBF.W	D0,$16DA
}
void plc_refresh_frame(void) {
  DEF_ROMLOC(163A) : tst_mem_16(0xFFFFF6F8); // TST.W	$F6F8
  DEF_ROMLOC(163E) : if (CCR_EQ) { return; } // BEQ.W	$16D2
  DEF_ROMLOC(1642) : move_tomem_16(0x9, 0xFFFFF6FA); // MOVE.W	#$0009,$F6FA
  DEF_ROMLOC(1648) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(164A) : move_toreg_16(read_16(0xFFFFF684), &D0); // MOVE.W	$F684,D0
  DEF_ROMLOC(164E) : add_tomem_16(0x120, 0xFFFFF684); // ADDI.W	#$0120,$F684
  plc_dplc_finish();                                  // BRA.B	$166E
}
void dplc_process_2(void) {
  DEF_ROMLOC(1656) : tst_mem_16(0xFFFFF6F8); // TST.W	$F6F8
  DEF_ROMLOC(165A) : if (CCR_EQ) { return; } // BEQ.B	$16D2
  DEF_ROMLOC(165C) : move_tomem_16(0x3, 0xFFFFF6FA); // MOVE.W	#$0003,$F6FA
  DEF_ROMLOC(1662) : move_toreg_32(0x0, &D0);        // MOVEQ.L	$00,D0
  DEF_ROMLOC(1664)
      : move_toreg_16(read_16(0xFFFFF684), &D0);     // MOVE.W	$F684,D0
  DEF_ROMLOC(1668) : add_tomem_16(0x60, 0xFFFFF684); // ADDI.W	#$0060,$F684
  plc_dplc_finish(); // Detected flow into next function
}
void plc_dplc_finish(void) {
  move_toreg_32(VDP_CONTROL_PORT, &A4);
  set_vram_ptr(D0);
  sub_toreg_16(0x4, &A4);
  A0 = read_32(v_plc_buffer);
  A3 = read_32(v_plc_ptrnemcode);
  D0 = read_32(v_plc_repeatcount);
  D1 = read_32(v_plc_paletteindex);
  D2 = read_32(v_plc_previousrow);
  D5 = read_32(v_plc_dataword);
  D6 = read_32(v_plc_shiftvalue);
  A1 = v_ngfx_buffer;
  DEF_ROMLOC(16A2) : move_toreg_16(0x8, &A5);
  rom_14C4();
  sub_tomem_16(0x1, v_plc_patternsleft);
  if (CCR_EQ) {
    plc_pop_front();
    return;
  }
  sub_tomem_16(0x1, v_plc_framepatternsleft);
  if (!CCR_EQ)
    goto rom_16A2;
  write_32(v_plc_buffer, A0);
  write_32(v_plc_ptrnemcode, A3);
  write_32(v_plc_repeatcount, D0);
  write_32(v_plc_paletteindex, D1);
  write_32(v_plc_previousrow, D2);
  write_32(v_plc_dataword, D5);
  write_32(v_plc_shiftvalue, D6);
}
void quick_plc(void) {
  move_toreg_32(0x1DD86, &A1); // LEA.L	$0001DD86,A1
  add_toreg_16(D0, &D0);       // ADD.W	D0,D0
  move_toreg_16(read_16((s32)A1 + (s8)0x0 + (s16)D0),
                &D0);                              // MOVE.W	0(A1,D0),D0
  move_toreg_32((s32)A1 + (s8)0x0 + (s16)D0, &A1); // LEA.L	0(A1,D0),A1
  move_toreg_16(read_16((A1 += 2, A1 - 2)), &D1);  // MOVE.W	(A1)+,D1
  DEF_ROMLOC(16F6)
      : move_toreg_32(read_32((A1 += 4, A1 - 4)), &A0); // MOVEA.L	(A1)+,A0
  move_toreg_32(0x0, &D0);                              // MOVEQ.L	$00,D0
  move_toreg_16(read_16((A1 += 2, A1 - 2)), &D0);       // MOVE.W	(A1)+,D0
  set_vram_ptr(D0);
  decompress_nemesis(); // BSR.W	$1438
  dec_reg_16(&D1);
  if ((D1 & 0xffff) != 0xffff)
    goto rom_16F6; // DBF.W	D1,$16F6
}