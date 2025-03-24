#include <math.h>
#include "system.h"
#include "opcodes.h"

ROMFUNC(dac_update_track);
ROMFUNC(fm_update_track);
ROMFUNC(fm_do_next);
void fm_set_freq(u8 freqindex);
ROMFUNC(set_duration);
ROMFUNC(track_set_rest);
ROMFUNC(finish_track_update);
ROMFUNC(rom_71D9E);
ROMFUNC(rom_71DC6);
ROMFUNC(rom_71E18);
ROMFUNC(fm_update_freq);
ROMFUNC(rom_71E4A);
ROMFUNC(rom_71E50);
ROMFUNC(rom_71F02);
ROMFUNC(play_sound_id);
ROMFUNC(rom_71F8E);
ROMFUNC(rom_71FAC);
ROMFUNC(sound_play_bgm);
ROMFUNC(rom_721C6);
ROMFUNC(rom_7230C);
ROMFUNC(stop_sfx);
ROMFUNC(rom_7247C);
ROMFUNC(rom_724E6);
ROMFUNC(rom_72504);
ROMFUNC(rom_7256A);
ROMFUNC(rom_7259E);
ROMFUNC(rom_725CA);
ROMFUNC(tempo_wait);
ROMFUNC(rom_72624);
ROMFUNC(rom_72652);
ROMFUNC(rom_7267C);
ROMFUNC(rom_726E2);
ROMFUNC(rom_726FE);
ROMFUNC(send_fm_note_off);
ROMFUNC(rom_72716);
ROMFUNC(rom_72722);
ROMFUNC(rom_7275A);
ROMFUNC(rom_72850);
ROMFUNC(rom_72878);
void psg_set_freq(u8 freqindex);
ROMFUNC(rom_728DC);
ROMFUNC(psg_update_freq);
ROMFUNC(rom_72920);
ROMFUNC(rom_72926);
ROMFUNC(psg_do_vol_fx);
void set_psg_volume(u8 vol);
void rom_7297C(u8 vol);
void psg_check_note_timeout(u8 vol);
ROMFUNC(rom_7299A);
ROMFUNC(rom_729A0);
ROMFUNC(send_psg_note_off);
ROMFUNC(psg_silence_all);
ROMFUNC(coord_flag);
ROMFUNC(cf_panning_ams_fms);
ROMFUNC(rom_72AEC);
ROMFUNC(rom_72AF2);
ROMFUNC(rom_72AF8);
ROMFUNC(rom_72B14);
ROMFUNC(rom_72B9E);
ROMFUNC(rom_72BA4);
ROMFUNC(rom_72BAE);
ROMFUNC(rom_72BB4);
ROMFUNC(rom_72BBE);
ROMFUNC(rom_72BC6);
ROMFUNC(cf_set_tempo_divider_all);
ROMFUNC(cf_change_psg_volume);
ROMFUNC(cf_clear_push);
ROMFUNC(cf_stop_special_fm4);
ROMFUNC(cf_set_voice);
ROMFUNC(set_voice);
ROMFUNC(send_voice_tl);
ROMFUNC(cf_modulation);
ROMFUNC(cf_enable_modulation);
ROMFUNC(cf_stop);
ROMFUNC(cf_set_psg_noise);
ROMFUNC(cf_disable_modulation);
ROMFUNC(cf_set_psg_tone);
ROMFUNC(cf_jump);
ROMFUNC(cf_repeat_at_pos);
ROMFUNC(cf_jumpto_gosub);
ROMFUNC(cf_opF9);

typedef struct {
	u8 PlaybackControl;
	u8 VoiceControl;
	u8 TempoDivider;
	u8 _;
	u32 DataPointer;
	u8 Transpose;
	u8 Volume;
	u8 AMSFMSPan;
	u8 VoiceIndex;
	u8 VolEnvIndex;
	u8 StackPointer;
	u8 DurationTimeout;
	u8 SavedDuration;
	union {
		struct {
			u8 SavedDat;
			u8 __;
		};
		u16 Freq;
	};
	u8 NoteTimeout;
	u8 NoteTimeoutMaster;
	u32 ModulationPtr;
	u8 ModulationWait;
	u8 ModulationSpeed;
	u8 ModulationDelta;
	u8 ModulationSteps;
	u16 ModulationVal;
	u8 Detune;
	union {
		u8 PSGNoise;
		u8 FeedbackAlgo;
	};
	u32 VoicePtr;
	u32 LoopCounters[3];
} SMPS_Track;

typedef struct {
	union {
		u8 v_1up_ram[544];
		struct {
			u8 v_sndprio;
			u8 v_main_tempo_timeout;
			u8 v_main_tempo;
			u8 f_pausemusic;
			u8 v_fadeout_counter;
			u8 _;
			u8 v_fadeout_delay;
			u8 v_communication_byte;
			u8 f_updating_dac;
			u8 v_sound_id;
			union {
				u8 v_soundqueue[3];
				struct {
					u8 v_soundqueue0;
					u8 v_soundqueue1;
					u8 v_soundqueue2;
				};
			};
			u8 __;
			u8 f_voice_selector;
			u8 ___[9];
			u32 v_voice_ptr;
			u32 ____;
			u32 v_special_voice_ptr;
			u8 f_fadein_flag;
			u8 v_fadein_delay;
			u8 v_fadein_counter;
			u8 f_1up_playing;
			u8 v_tempo_mod;
			u8 v_speeduptempo;
			u8 f_speedup;
			u8 v_ring_speaker;
			u8 f_push_playing;
			u8 _____[0x13];
			union {
				SMPS_Track v_music_tracks[10];
				struct {
					union {
						SMPS_Track v_fmdac_tracks[7];
						struct {
							SMPS_Track v_music_dac_track;
							union {
								SMPS_Track v_music_fm_tracks[6];
								struct {
									SMPS_Track v_music_fm1_track;
									SMPS_Track v_music_fm2_track;
									SMPS_Track v_music_fm3_track;
									SMPS_Track v_music_fm4_track;
									SMPS_Track v_music_fm5_track;
									SMPS_Track v_music_fm6_track;
								};
							};
						};
					};
					union {
						SMPS_Track v_music_psg_tracks[3];
						struct {
							SMPS_Track v_music_psg1_track;
							SMPS_Track v_music_psg2_track;
							SMPS_Track v_music_psg3_track;
						};
					};
				};
			};
		};
	};
	union {
		SMPS_Track v_sfx_tracks[6];
		struct {
			union {
				SMPS_Track v_sfx_fm_tracks[3];
				struct {
					SMPS_Track v_sfx_fm3_track;
					SMPS_Track v_sfx_fm4_track;
					SMPS_Track v_sfx_fm5_track;
				};
			};
			union {
				SMPS_Track v_sfx_psg_tracks[3];
				struct {
					SMPS_Track v_sfx_psg1_track;
					SMPS_Track v_sfx_psg2_track;
					SMPS_Track v_sfx_psg3_track;
				};
			};
		};
	};
	union {
		SMPS_Track v_spcsfx_tracks[2];
		struct {
			union {
				SMPS_Track v_spsfx_fm_tracks[1];
				struct {
					SMPS_Track v_spcsfx_fm4_track;
				};
			};
			union {
				SMPS_Track v_spsfx_psg_tracks[1];
				struct {
					SMPS_Track v_spcsfx_psg3_track;
				};
			};
		};
	};
	u8 v_1up_ram_copy[544];
} SMPS_RAM;

#define MASTER_CLOCK 53693175.0
#define M68K_CLOCK (MASTER_CLOCK / 7.0)
#define Z80_CLOCK (MASTER_CLOCK / 15.0)
#define FM_SAMPLE_RATE (M68K_CLOCK / 144.0)
#define PSG_SAMPLE_RATE (Z80_CLOCK / 16.0)

#define FM_FREQ(hz) ((u16)(((hz) * 1024.0 * 1024.0 * 2.0) / ((double)FM_SAMPLE_RATE)))
#define FM_FREQ_OCTAVE_NOTE(hz, octave) (FM_FREQ(hz) + ((octave) * 0x800))
#define FM_FREQ_OCTAVE(octave) \
	FM_FREQ_OCTAVE_NOTE(15.433853, octave), \
	FM_FREQ_OCTAVE_NOTE(16.351598, octave), \
	FM_FREQ_OCTAVE_NOTE(17.323914, octave), \
	FM_FREQ_OCTAVE_NOTE(18.354048, octave), \
	FM_FREQ_OCTAVE_NOTE(19.445436, octave), \
	FM_FREQ_OCTAVE_NOTE(20.601722, octave), \
	FM_FREQ_OCTAVE_NOTE(21.826764, octave), \
	FM_FREQ_OCTAVE_NOTE(23.124651, octave), \
	FM_FREQ_OCTAVE_NOTE(24.499715, octave), \
	FM_FREQ_OCTAVE_NOTE(25.956544, octave), \
	FM_FREQ_OCTAVE_NOTE(27.500000, octave), \
	FM_FREQ_OCTAVE_NOTE(29.135235, octave)
static u16 FM_FREQS[] = {
	FM_FREQ_OCTAVE(0),
	FM_FREQ_OCTAVE(1),
	FM_FREQ_OCTAVE(2),
	FM_FREQ_OCTAVE(3),
	FM_FREQ_OCTAVE(4),
	FM_FREQ_OCTAVE(5),
	FM_FREQ_OCTAVE(6),
	FM_FREQ_OCTAVE(7),
};

#define min(a, b) (((b) < (a)) ? (b) : (a))
#define PSG_FREQ(hz) min((u16)0x3ff, (u16)(PSG_SAMPLE_RATE / (hz * 2.0)))
static u16 PSG_FREQS[] = {
	PSG_FREQ(130.98),
	PSG_FREQ(138.78),
	PSG_FREQ(146.99),
	PSG_FREQ(155.79),
	PSG_FREQ(165.22),
	PSG_FREQ(174.78),
	PSG_FREQ(185.19),
	PSG_FREQ(196.24),
	PSG_FREQ(207.91),
	PSG_FREQ(220.63),
	PSG_FREQ(233.52),
	PSG_FREQ(247.47),
	PSG_FREQ(261.96),
	PSG_FREQ(277.56),
	PSG_FREQ(293.59),
	PSG_FREQ(311.58),
	PSG_FREQ(329.97),
	PSG_FREQ(349.56),
	PSG_FREQ(370.39),
	PSG_FREQ(392.49),
	PSG_FREQ(415.83),
	PSG_FREQ(440.39),
	PSG_FREQ(468.03),
	PSG_FREQ(494.95),
	PSG_FREQ(522.71),
	PSG_FREQ(556.51),
	PSG_FREQ(588.73),
	PSG_FREQ(621.44),
	PSG_FREQ(661.89),
	PSG_FREQ(699.12),
	PSG_FREQ(740.79),
	PSG_FREQ(782.24),
	PSG_FREQ(828.59),
	PSG_FREQ(880.79),
	PSG_FREQ(932.17),
	PSG_FREQ(989.91),
	PSG_FREQ(1045.42),
	PSG_FREQ(1107.52),
	PSG_FREQ(1177.47),
	PSG_FREQ(1242.89),
	PSG_FREQ(1316.00),
	PSG_FREQ(1398.25),
	PSG_FREQ(1491.47),
	PSG_FREQ(1575.50),
	PSG_FREQ(1669.55),
	PSG_FREQ(1747.82),
	PSG_FREQ(1864.34),
	PSG_FREQ(1962.46),
	PSG_FREQ(2071.49),
	PSG_FREQ(2193.34),
	PSG_FREQ(2330.42),
	PSG_FREQ(2485.78),
	PSG_FREQ(2601.40),
	PSG_FREQ(2796.51),
	PSG_FREQ(2943.69),
	PSG_FREQ(3107.23),
	PSG_FREQ(3290.01),
	PSG_FREQ(3495.64),
	PSG_FREQ(3608.40),
	PSG_FREQ(3857.25),
	PSG_FREQ(4142.98),
	PSG_FREQ(4302.32),
	PSG_FREQ(4660.85),
	PSG_FREQ(4863.50),
	PSG_FREQ(5084.56),
	PSG_FREQ(5326.69),
	PSG_FREQ(5887.39),
	PSG_FREQ(6214.47),
	PSG_FREQ(6580.02),
	PSG_FREQ(223721.56),
};

static u8 YM_INIT_DATA[] = { 6, 0, 1, 2, 4, 5, 6 };

static u8 FM_SLOT_MASK[] = { 8, 8, 8, 8, 0xa, 0xe, 0xe, 0xf };

static u8 sp_skip_level = 0;

#define CALL(func) func(); if (sp_skip_level > 0) { sp_skip_level -= 1; return; }

void smps_update(void) {
	sp_skip_level = 0;
	DEF_ROMLOC(71B82): A6 = 0xFFF000; // LEA.L	$00FFF000,A6
	DEF_ROMLOC(71B88): clr_mem_8(A6 + offsetof(SMPS_RAM, f_voice_selector)); // CLR.B	14(A6)
	DEF_ROMLOC(71B8C): tst_mem_8(A6 + offsetof(SMPS_RAM, f_pausemusic)); // TST.B	3(A6)
	DEF_ROMLOC(71B90): if (!CCR_EQ) {rom_71E50();return;} // BNE.W	$71E50
	DEF_ROMLOC(71B94): sub_tomem_8(0x1, A6 + offsetof(SMPS_RAM, v_main_tempo_timeout)); // SUBQ.B	#$01,1(A6)
	DEF_ROMLOC(71B98): if (!CCR_EQ) goto rom_71B9E; // BNE.B	$71B9E
	DEF_ROMLOC(71B9A): CALL(tempo_wait); // JSR	2672(PC)
	DEF_ROMLOC(71B9E): move_toreg_8(read_8(A6 + offsetof(SMPS_RAM, v_fadeout_counter)), &D0); // MOVE.B	4(A6),D0
	DEF_ROMLOC(71BA2): if (CCR_EQ) goto rom_71BA8; // BEQ.B	$71BA8
	DEF_ROMLOC(71BA4): CALL(rom_72504); // JSR	2398(PC)
	DEF_ROMLOC(71BA8): tst_mem_8(A6 + offsetof(SMPS_RAM, f_fadein_flag)); // TST.B	36(A6)
	DEF_ROMLOC(71BAC): if (CCR_EQ) goto rom_71BB2; // BEQ.B	$71BB2
	DEF_ROMLOC(71BAE): CALL(rom_7267C); // JSR	2764(PC)
	DEF_ROMLOC(71BB2): tst_mem_16(A6 + offsetof(SMPS_RAM, v_soundqueue0)); // TST.W	10(A6)
	DEF_ROMLOC(71BB6): if (CCR_EQ) goto rom_71BBC; // BEQ.B	$71BBC
	DEF_ROMLOC(71BB8): CALL(rom_71F02); // JSR	840(PC)
	DEF_ROMLOC(71BBC): cmp_tomem_8(0x80, A6 + offsetof(SMPS_RAM, v_sound_id)); // CMPI.B	#$80,9(A6)
	DEF_ROMLOC(71BC2): if (CCR_EQ) goto rom_71BC8; // BEQ.B	$71BC8
	DEF_ROMLOC(71BC4): CALL(play_sound_id); // JSR	902(PC)
	DEF_ROMLOC(71BC8): A5 = A6 + 0x40; // LEA.L	64(A6),A5
	DEF_ROMLOC(71BCC): tst_mem_8(A5); // TST.B	(A5)
	DEF_ROMLOC(71BCE): if (CCR_PL) goto rom_71BD4; // BPL.B	$71BD4
	DEF_ROMLOC(71BD0): CALL(dac_update_track); // JSR	124(PC)
	DEF_ROMLOC(71BD4): clr_mem_8(A6 + offsetof(SMPS_RAM, f_updating_dac)); // CLR.B	8(A6)
	DEF_ROMLOC(71BD8): D7 = 0x5; // MOVEQ.L	$05,D7
	DEF_ROMLOC(71BDA): add_toreg_16(0x30, &A5); // ADDA.W	#$0030,A5
	DEF_ROMLOC(71BDE): tst_mem_8(A5); // TST.B	(A5)
	DEF_ROMLOC(71BE0): if (CCR_PL) goto rom_71BE6; // BPL.B	$71BE6
	DEF_ROMLOC(71BE2): CALL(fm_update_track); // JSR	230(PC)
	DEF_ROMLOC(71BE6): dec_reg_16(&D7); if ((D7 & 0xffff) != 0xffff) goto rom_71BDA; // DBF.W	D7,$71BDA
	DEF_ROMLOC(71BEA): D7 = 0x2; // MOVEQ.L	$02,D7
	DEF_ROMLOC(71BEC): add_toreg_16(0x30, &A5); // ADDA.W	#$0030,A5
	DEF_ROMLOC(71BF0): tst_mem_8(A5); // TST.B	(A5)
	DEF_ROMLOC(71BF2): if (CCR_PL) goto rom_71BF8; // BPL.B	$71BF8
	DEF_ROMLOC(71BF4): CALL(rom_72850); // JSR	3162(PC)
	DEF_ROMLOC(71BF8): dec_reg_16(&D7); if ((D7 & 0xffff) != 0xffff) goto rom_71BEC; // DBF.W	D7,$71BEC
	DEF_ROMLOC(71BFC): move_tomem_8(0xFFFFFF80, A6 + offsetof(SMPS_RAM, f_voice_selector)); // MOVE.B	#$80,14(A6)
	DEF_ROMLOC(71C02): D7 = 0x2; // MOVEQ.L	$02,D7
	DEF_ROMLOC(71C04): add_toreg_16(0x30, &A5); // ADDA.W	#$0030,A5
	DEF_ROMLOC(71C08): tst_mem_8(A5); // TST.B	(A5)
	DEF_ROMLOC(71C0A): if (CCR_PL) goto rom_71C10; // BPL.B	$71C10
	DEF_ROMLOC(71C0C): CALL(fm_update_track); // JSR	188(PC)
	DEF_ROMLOC(71C10): dec_reg_16(&D7); if ((D7 & 0xffff) != 0xffff) goto rom_71C04; // DBF.W	D7,$71C04
	DEF_ROMLOC(71C14): D7 = 0x2; // MOVEQ.L	$02,D7
	DEF_ROMLOC(71C16): add_toreg_16(0x30, &A5); // ADDA.W	#$0030,A5
	DEF_ROMLOC(71C1A): tst_mem_8(A5); // TST.B	(A5)
	DEF_ROMLOC(71C1C): if (CCR_PL) goto rom_71C22; // BPL.B	$71C22
	DEF_ROMLOC(71C1E): CALL(rom_72850); // JSR	3120(PC)
	DEF_ROMLOC(71C22): dec_reg_16(&D7); if ((D7 & 0xffff) != 0xffff) goto rom_71C16; // DBF.W	D7,$71C16
	DEF_ROMLOC(71C26): move_tomem_8(0x40, A6 + offsetof(SMPS_RAM, f_voice_selector)); // MOVE.B	#$40,14(A6)
	DEF_ROMLOC(71C2C): add_toreg_16(0x30, &A5); // ADDA.W	#$0030,A5
	DEF_ROMLOC(71C30): tst_mem_8(A5); // TST.B	(A5)
	DEF_ROMLOC(71C32): if (CCR_PL) goto rom_71C38; // BPL.B	$71C38
	DEF_ROMLOC(71C34): CALL(fm_update_track); // JSR	148(PC)
	DEF_ROMLOC(71C38): add_toreg_16(0x30, &A5); // ADDA.W	#$0030,A5
	DEF_ROMLOC(71C3C): tst_mem_8(A5); // TST.B	(A5)
	DEF_ROMLOC(71C3E): if (CCR_PL) {return;} // BPL.B	$71C44
	DEF_ROMLOC(71C40): CALL(rom_72850); // JSR	3086(PC)
}
ROMFUNC(dac_update_track) {
	DEF_ROMLOC(71C4E): sub_tomem_8(0x1, A5 + 0xE); // SUBQ.B	#$01,14(A5)
	DEF_ROMLOC(71C52): if (!CCR_EQ) goto rom_71CAA; // BNE.B	$71CAA
	DEF_ROMLOC(71C54): move_tomem_8(0xFFFFFF80, A6 + offsetof(SMPS_RAM, f_updating_dac)); // MOVE.B	#$80,8(A6)
	DEF_ROMLOC(71C5A): A4 = read_32(A5 + 0x4); // MOVEA.L	4(A5),A4
	DEF_ROMLOC(71C5E): D5 = 0; // MOVEQ.L	$00,D5
	DEF_ROMLOC(71C60): move_toreg_8(read_8(A4++), &D5); // MOVE.B	(A4)+,D5
	DEF_ROMLOC(71C62): cmp_toreg_8(0xFFFFFFE0, &D5); // CMPI.B	#$E0,D5
	DEF_ROMLOC(71C66): if (CCR_CS) goto rom_71C6E; // BCS.B	$71C6E
	DEF_ROMLOC(71C68): CALL(coord_flag); // JSR	3568(PC)
	DEF_ROMLOC(71C6C): goto rom_71C5E; // BRA.B	$71C5E
	DEF_ROMLOC(71C6E): tst_reg_8(&D5); // TST.B	D5
	DEF_ROMLOC(71C70): if (CCR_PL) goto rom_71C84; // BPL.B	$71C84
	DEF_ROMLOC(71C72): move_tomem_8(D5, A5 + 0x10); // MOVE.B	D5,16(A5)
	DEF_ROMLOC(71C76): move_toreg_8(read_8(A4++), &D5); // MOVE.B	(A4)+,D5
	DEF_ROMLOC(71C78): if (CCR_PL) goto rom_71C84; // BPL.B	$71C84
	DEF_ROMLOC(71C7A): sub_toreg_16(0x1, &A4); // SUBQ.W	#$01,A4
	DEF_ROMLOC(71C7C): move_tomem_8(read_8(A5 + 0xF), A5 + 0xE); // MOVE.B	15(A5),14(A5)
	DEF_ROMLOC(71C82): goto rom_71C88; // BRA.B	$71C88
	DEF_ROMLOC(71C84): CALL(set_duration); // JSR	186(PC)
	DEF_ROMLOC(71C88): move_tomem_32(A4, A5 + 0x4); // MOVE.L	A4,4(A5)
	DEF_ROMLOC(71C8C): btst_tomem_8(0x2, A5); // BTST.B	#$02,(A5)
	DEF_ROMLOC(71C90): if (!CCR_EQ) goto rom_71CAA; // BNE.B	$71CAA
	DEF_ROMLOC(71C92): D0 = 0; // MOVEQ.L	$00,D0
	DEF_ROMLOC(71C94): move_toreg_8(read_8(A5 + 0x10), &D0); // MOVE.B	16(A5),D0
	DEF_ROMLOC(71C98): cmp_toreg_8(0xFFFFFF80, &D0); // CMPI.B	#$80,D0
	DEF_ROMLOC(71C9C): if (CCR_EQ) goto rom_71CAA; // BEQ.B	$71CAA
	DEF_ROMLOC(71C9E): btst_toreg_32(0x3, &D0); // BTST.L	#$03,D0
	DEF_ROMLOC(71CA2): if (!CCR_EQ) goto rom_71CAC; // BNE.B	$71CAC
	DEF_ROMLOC(71CA4): set_dac_sample(D0);
	DEF_ROMLOC(71CAA): return; // RTS
	DEF_ROMLOC(71CAC): sub_toreg_8(0x88, &D0); // SUBI.B	#$88,D0
	DEF_ROMLOC(71CBA): set_dac_sample(0x83 + GETWORD(D0));
}
ROMFUNC(fm_update_track) {
	DEF_ROMLOC(71CCA): sub_tomem_8(0x1, A5 + 0xE); // SUBQ.B	#$01,14(A5)
	DEF_ROMLOC(71CCE): if (!CCR_EQ) goto rom_71CE0; // BNE.B	$71CE0
	DEF_ROMLOC(71CD0): bclr_tomem_8(0x4, A5); // BCLR.B	#$04,(A5)
	DEF_ROMLOC(71CD4): CALL(fm_do_next); // JSR	22(PC)
	DEF_ROMLOC(71CD8): CALL(rom_71E18); // JSR	318(PC)
	DEF_ROMLOC(71CDC): {rom_726E2();return;} // BRA.W	$726E2
	DEF_ROMLOC(71CE0): CALL(rom_71D9E); // JSR	188(PC)
	DEF_ROMLOC(71CE4): CALL(rom_71DC6); // JSR	224(PC)
	fm_update_freq(); // BRA.W	$71E24
}
ROMFUNC(fm_do_next) {
	DEF_ROMLOC(71CEC): A4 = read_32(A5 + 0x4); // MOVEA.L	4(A5),A4
	DEF_ROMLOC(71CF0): bclr_tomem_8(0x1, A5); // BCLR.B	#$01,(A5)
	DEF_ROMLOC(71CF4): D5 = 0; // MOVEQ.L	$00,D5
	DEF_ROMLOC(71CF6): move_toreg_8(read_8(A4++), &D5); // MOVE.B	(A4)+,D5
	DEF_ROMLOC(71CF8): cmp_toreg_8(0xFFFFFFE0, &D5); // CMPI.B	#$E0,D5
	DEF_ROMLOC(71CFC): if (CCR_CS) goto rom_71D04; // BCS.B	$71D04
	DEF_ROMLOC(71CFE): CALL(coord_flag); // JSR	3418(PC)
	DEF_ROMLOC(71D02): goto rom_71CF4; // BRA.B	$71CF4
	DEF_ROMLOC(71D04): CALL(rom_726FE); // JSR	2552(PC)
	DEF_ROMLOC(71D08): tst_reg_8(&D5); // TST.B	D5
	DEF_ROMLOC(71D0A): if (CCR_PL) goto rom_71D1A; // BPL.B	$71D1A
	DEF_ROMLOC(71D0C): fm_set_freq(D5); // JSR	20(PC)
	DEF_ROMLOC(71D10): move_toreg_8(read_8(A4++), &D5); // MOVE.B	(A4)+,D5
	DEF_ROMLOC(71D12): if (CCR_PL) goto rom_71D1A; // BPL.B	$71D1A
	DEF_ROMLOC(71D14): sub_toreg_16(0x1, &A4); // SUBQ.W	#$01,A4
	DEF_ROMLOC(71D16): {finish_track_update();return;} // BRA.W	$71D60
	DEF_ROMLOC(71D1A): CALL(set_duration); // JSR	36(PC)
	finish_track_update(); // BRA.W	$71D60
}
void fm_set_freq(u8 freqindex) {
	freqindex -= 0x80;
	if (freqindex == 0) {
		track_set_rest();
		return;
	}
	freqindex += read_8(A5 + offsetof(SMPS_Track, Transpose));
	write_16(A5 + offsetof(SMPS_Track, Freq), FM_FREQS[freqindex & 0x7f]);
}
ROMFUNC(set_duration) {
	DEF_ROMLOC(71D40): move_toreg_8(D5, &D0); // MOVE.B	D5,D0
	DEF_ROMLOC(71D42): move_toreg_8(read_8(A5 + 0x2), &D1); // MOVE.B	2(A5),D1
	DEF_ROMLOC(71D46): sub_toreg_8(0x1, &D1); // SUBQ.B	#$01,D1
	DEF_ROMLOC(71D48): if (CCR_EQ) goto rom_71D4E; // BEQ.B	$71D4E
	DEF_ROMLOC(71D4A): add_toreg_8(D5, &D0); // ADD.B	D5,D0
	DEF_ROMLOC(71D4C): goto rom_71D46; // BRA.B	$71D46
	DEF_ROMLOC(71D4E): move_tomem_8(D0, A5 + 0xF); // MOVE.B	D0,15(A5)
	DEF_ROMLOC(71D52): move_tomem_8(D0, A5 + 0xE); // MOVE.B	D0,14(A5)
}
ROMFUNC(track_set_rest) {
	DEF_ROMLOC(71D58): bset_tomem_8(0x1, A5); // BSET.B	#$01,(A5)
	DEF_ROMLOC(71D5C): clr_mem_16(A5 + 0x10); // CLR.W	16(A5)
	finish_track_update();
}
ROMFUNC(finish_track_update) {
	DEF_ROMLOC(71D60): move_tomem_32(A4, A5 + 0x4); // MOVE.L	A4,4(A5)
	DEF_ROMLOC(71D64): move_tomem_8(read_8(A5 + 0xF), A5 + 0xE); // MOVE.B	15(A5),14(A5)
	DEF_ROMLOC(71D6A): btst_tomem_8(0x4, A5); // BTST.B	#$04,(A5)
	DEF_ROMLOC(71D6E): if (!CCR_EQ) return; // BNE.B	$71D9C
	DEF_ROMLOC(71D70): move_tomem_8(read_8(A5 + 0x13), A5 + 0x12); // MOVE.B	19(A5),18(A5)
	DEF_ROMLOC(71D76): clr_mem_8(A5 + 0xC); // CLR.B	12(A5)
	DEF_ROMLOC(71D7A): btst_tomem_8(0x3, A5); // BTST.B	#$03,(A5)
	DEF_ROMLOC(71D7E): if (CCR_EQ) return; // BEQ.B	$71D9C
	DEF_ROMLOC(71D80): A0 = read_32(A5 + 0x14); // MOVEA.L	20(A5),A0
	DEF_ROMLOC(71D84): move_tomem_8(read_8(A0++), A5 + 0x18); // MOVE.B	(A0)+,24(A5)
	DEF_ROMLOC(71D88): move_tomem_8(read_8(A0++), A5 + 0x19); // MOVE.B	(A0)+,25(A5)
	DEF_ROMLOC(71D8C): move_tomem_8(read_8(A0++), A5 + 0x1A); // MOVE.B	(A0)+,26(A5)
	DEF_ROMLOC(71D90): move_toreg_8(read_8(A0++), &D0); // MOVE.B	(A0)+,D0
	DEF_ROMLOC(71D92): lsr_toreg_8(0x1, &D0); // LSR.B	#$01,D0
	DEF_ROMLOC(71D94): move_tomem_8(D0, A5 + 0x1B); // MOVE.B	D0,27(A5)
	DEF_ROMLOC(71D98): clr_mem_16(A5 + 0x1C); // CLR.W	28(A5)
}
ROMFUNC(rom_71D9E) {
	DEF_ROMLOC(71D9E): tst_mem_8(A5 + 0x12); // TST.B	18(A5)
	DEF_ROMLOC(71DA2): if (CCR_EQ) return; // BEQ.B	$71DC4
	DEF_ROMLOC(71DA4): sub_tomem_8(0x1, A5 + 0x12); // SUBQ.B	#$01,18(A5)
	DEF_ROMLOC(71DA8): if (!CCR_EQ) return; // BNE.B	$71DC4
	DEF_ROMLOC(71DAA): bset_tomem_8(0x1, A5); // BSET.B	#$01,(A5)
	DEF_ROMLOC(71DAE): tst_mem_8(A5 + 0x1); // TST.B	1(A5)
	DEF_ROMLOC(71DB2): if (CCR_MI) goto rom_71DBE; // BMI.W	$71DBE
	DEF_ROMLOC(71DB6): CALL(rom_726FE); // JSR	2374(PC)
	DEF_ROMLOC(71DBA): sp_skip_level += 1; add_toreg_16(0x4, &A7); // ADDQ.W	#$04,A7
	DEF_ROMLOC(71DBC): return; // RTS
	DEF_ROMLOC(71DBE): CALL(rom_729A0); // JSR	3040(PC)
	DEF_ROMLOC(71DC2): sp_skip_level += 1; add_toreg_16(0x4, &A7); // ADDQ.W	#$04,A7
}
ROMFUNC(rom_71DC6) {
	DEF_ROMLOC(71DC6): sp_skip_level += 1; add_toreg_16(0x4, &A7); // ADDQ.W	#$04,A7
	DEF_ROMLOC(71DC8): btst_tomem_8(0x3, A5); // BTST.B	#$03,(A5)
	DEF_ROMLOC(71DCC): if (CCR_EQ) return; // BEQ.B	$71E16
	DEF_ROMLOC(71DCE): tst_mem_8(A5 + 0x18); // TST.B	24(A5)
	DEF_ROMLOC(71DD2): if (CCR_EQ) goto rom_71DDA; // BEQ.B	$71DDA
	DEF_ROMLOC(71DD4): sub_tomem_8(0x1, A5 + 0x18); // SUBQ.B	#$01,24(A5)
	DEF_ROMLOC(71DD8): return; // RTS
	DEF_ROMLOC(71DDA): sub_tomem_8(0x1, A5 + 0x19); // SUBQ.B	#$01,25(A5)
	DEF_ROMLOC(71DDE): if (CCR_EQ) goto rom_71DE2; // BEQ.B	$71DE2
	DEF_ROMLOC(71DE0): return; // RTS
	DEF_ROMLOC(71DE2): A0 = read_32(A5 + 0x14); // MOVEA.L	20(A5),A0
	DEF_ROMLOC(71DE6): move_tomem_8(read_8(A0 + 0x1), A5 + 0x19); // MOVE.B	1(A0),25(A5)
	DEF_ROMLOC(71DEC): tst_mem_8(A5 + 0x1B); // TST.B	27(A5)
	DEF_ROMLOC(71DF0): if (!CCR_EQ) goto rom_71DFE; // BNE.B	$71DFE
	DEF_ROMLOC(71DF2): move_tomem_8(read_8(A0 + 0x3), A5 + 0x1B); // MOVE.B	3(A0),27(A5)
	DEF_ROMLOC(71DF8): neg_mem_8(A5 + 0x1A); // NEG.B	26(A5)
	DEF_ROMLOC(71DFC): return; // RTS
	DEF_ROMLOC(71DFE): sub_tomem_8(0x1, A5 + 0x1B); // SUBQ.B	#$01,27(A5)
	DEF_ROMLOC(71E02): move_toreg_8(read_8(A5 + 0x1A), &D6); // MOVE.B	26(A5),D6
	DEF_ROMLOC(71E06): ext_reg_16(&D6); // EXT.W	D6
	DEF_ROMLOC(71E08): add_toreg_16(read_16(A5 + 0x1C), &D6); // ADD.W	28(A5),D6
	DEF_ROMLOC(71E0C): move_tomem_16(D6, A5 + 0x1C); // MOVE.W	D6,28(A5)
	DEF_ROMLOC(71E10): add_toreg_16(read_16(A5 + 0x10), &D6); // ADD.W	16(A5),D6
	DEF_ROMLOC(71E14): sp_skip_level -= 1; sub_toreg_16(0x4, &A7); // SUBQ.W	#$04,A7
}
ROMFUNC(rom_71E18) {
	DEF_ROMLOC(71E18): btst_tomem_8(0x1, A5); // BTST.B	#$01,(A5)
	DEF_ROMLOC(71E1C): if (!CCR_EQ) {return;} // BNE.B	$71E48
	DEF_ROMLOC(71E1E): move_toreg_16(read_16(A5 + 0x10), &D6); // MOVE.W	16(A5),D6
	DEF_ROMLOC(71E22): if (CCR_EQ) {rom_71E4A();return;} // BEQ.B	$71E4A
	fm_update_freq();
}
ROMFUNC(fm_update_freq) {
	DEF_ROMLOC(71E24): move_toreg_8(read_8(A5 + 0x1E), &D0); // MOVE.B	30(A5),D0
	DEF_ROMLOC(71E28): ext_reg_16(&D0); // EXT.W	D0
	DEF_ROMLOC(71E2A): add_toreg_16(D0, &D6); // ADD.W	D0,D6
	DEF_ROMLOC(71E2C): btst_tomem_8(0x2, A5); // BTST.B	#$02,(A5)
	DEF_ROMLOC(71E30): if (!CCR_EQ) {return;} // BNE.B	$71E48
	DEF_ROMLOC(71E32): move_toreg_16(D6, &D1); // MOVE.W	D6,D1
	DEF_ROMLOC(71E34): lsr_toreg_16(0x8, &D1); // LSR.W	#$08,D1
	DEF_ROMLOC(71E36): move_toreg_8(0xFFFFFFA4, &D0); // MOVE.B	#$A4,D0
	DEF_ROMLOC(71E3A): CALL(rom_72722); // JSR	2278(PC)
	DEF_ROMLOC(71E3E): move_toreg_8(D6, &D1); // MOVE.B	D6,D1
	DEF_ROMLOC(71E40): move_toreg_8(0xFFFFFFA0, &D0); // MOVE.B	#$A0,D0
	DEF_ROMLOC(71E44): CALL(rom_72722); // JSR	2268(PC)
}
ROMFUNC(rom_71E4A) {
	DEF_ROMLOC(71E4A): bset_tomem_8(0x1, A5); // BSET.B	#$01,(A5)
}
ROMFUNC(rom_71E50) {
	DEF_ROMLOC(71E50): if (CCR_MI) goto rom_71E94; // BMI.B	$71E94
	DEF_ROMLOC(71E52): cmp_tomem_8(0x2, A6 + offsetof(SMPS_RAM, f_pausemusic)); // CMPI.B	#$02,3(A6)
	DEF_ROMLOC(71E58): if (CCR_EQ) return; // BEQ.W	$71EFE
	DEF_ROMLOC(71E5C): move_tomem_8(0x2, A6 + offsetof(SMPS_RAM, f_pausemusic)); // MOVE.B	#$02,3(A6)
	DEF_ROMLOC(71E62): D3 = 0x2; // MOVEQ.L	$02,D3
	DEF_ROMLOC(71E64): move_toreg_8(0xFFFFFFB4, &D0); // MOVE.B	#$B4,D0
	DEF_ROMLOC(71E68): D1 = 0; // MOVEQ.L	$00,D1
	DEF_ROMLOC(71E6A): write_fm_i(D0, D1); // JSR	2242(PC)
	DEF_ROMLOC(71E6E): write_fm_ii(D0, D1); // JSR	2292(PC)
	DEF_ROMLOC(71E72): add_toreg_8(0x1, &D0); // ADDQ.B	#$01,D0
	DEF_ROMLOC(71E74): dec_reg_16(&D3); if ((D3 & 0xffff) != 0xffff) goto rom_71E6A; // DBF.W	D3,$71E6A
	DEF_ROMLOC(71E78): D3 = 0x2; // MOVEQ.L	$02,D3
	DEF_ROMLOC(71E7A): D0 = 0x28; // MOVEQ.L	$28,D0
	DEF_ROMLOC(71E7C): move_toreg_8(D3, &D1); // MOVE.B	D3,D1
	DEF_ROMLOC(71E7E): write_fm_i(D0, D1); // JSR	2222(PC)
	DEF_ROMLOC(71E82): add_toreg_8(0x4, &D1); // ADDQ.B	#$04,D1
	DEF_ROMLOC(71E84): write_fm_i(D0, D1); // JSR	2216(PC)
	DEF_ROMLOC(71E88): dec_reg_16(&D3); if ((D3 & 0xffff) != 0xffff) goto rom_71E7C; // DBF.W	D3,$71E7C
	DEF_ROMLOC(71E8C): CALL(psg_silence_all); // JSR	2856(PC)
	DEF_ROMLOC(71E90): return; // BRA.W	$71C44
	DEF_ROMLOC(71E94): clr_mem_8(A6 + offsetof(SMPS_RAM, f_pausemusic)); // CLR.B	3(A6)
	DEF_ROMLOC(71E98): D3 = 0x30; // MOVEQ.L	$30,D3
	DEF_ROMLOC(71E9A): A5 = A6 + 0x40; // LEA.L	64(A6),A5
	DEF_ROMLOC(71E9E): D4 = 0x6; // MOVEQ.L	$06,D4
	DEF_ROMLOC(71EA0): btst_tomem_8(0x7, A5); // BTST.B	#$07,(A5)
	DEF_ROMLOC(71EA4): if (CCR_EQ) goto rom_71EB8; // BEQ.B	$71EB8
	DEF_ROMLOC(71EA6): btst_tomem_8(0x2, A5); // BTST.B	#$02,(A5)
	DEF_ROMLOC(71EAA): if (!CCR_EQ) goto rom_71EB8; // BNE.B	$71EB8
	DEF_ROMLOC(71EAC): move_toreg_8(0xFFFFFFB4, &D0); // MOVE.B	#$B4,D0
	DEF_ROMLOC(71EB0): move_toreg_8(read_8(A5 + 0xA), &D1); // MOVE.B	10(A5),D1
	DEF_ROMLOC(71EB4): CALL(rom_72722); // JSR	2156(PC)
	DEF_ROMLOC(71EB8): add_toreg_16(D3, &A5); // ADDA.W	D3,A5
	DEF_ROMLOC(71EBA): dec_reg_16(&D4); if ((D4 & 0xffff) != 0xffff) goto rom_71EA0; // DBF.W	D4,$71EA0
	DEF_ROMLOC(71EBE): A5 = A6 + 0x220; // LEA.L	544(A6),A5
	DEF_ROMLOC(71EC2): D4 = 0x2; // MOVEQ.L	$02,D4
	DEF_ROMLOC(71EC4): btst_tomem_8(0x7, A5); // BTST.B	#$07,(A5)
	DEF_ROMLOC(71EC8): if (CCR_EQ) goto rom_71EDC; // BEQ.B	$71EDC
	DEF_ROMLOC(71ECA): btst_tomem_8(0x2, A5); // BTST.B	#$02,(A5)
	DEF_ROMLOC(71ECE): if (!CCR_EQ) goto rom_71EDC; // BNE.B	$71EDC
	DEF_ROMLOC(71ED0): move_toreg_8(0xFFFFFFB4, &D0); // MOVE.B	#$B4,D0
	DEF_ROMLOC(71ED4): move_toreg_8(read_8(A5 + 0xA), &D1); // MOVE.B	10(A5),D1
	DEF_ROMLOC(71ED8): CALL(rom_72722); // JSR	2120(PC)
	DEF_ROMLOC(71EDC): add_toreg_16(D3, &A5); // ADDA.W	D3,A5
	DEF_ROMLOC(71EDE): dec_reg_16(&D4); if ((D4 & 0xffff) != 0xffff) goto rom_71EC4; // DBF.W	D4,$71EC4
	DEF_ROMLOC(71EE2): A5 = A6 + 0x340; // LEA.L	832(A6),A5
	DEF_ROMLOC(71EE6): btst_tomem_8(0x7, A5); // BTST.B	#$07,(A5)
	DEF_ROMLOC(71EEA): if (CCR_EQ) return; // BEQ.B	$71EFE
	DEF_ROMLOC(71EEC): btst_tomem_8(0x2, A5); // BTST.B	#$02,(A5)
	DEF_ROMLOC(71EF0): if (!CCR_EQ) return; // BNE.B	$71EFE
	DEF_ROMLOC(71EF2): move_toreg_8(0xFFFFFFB4, &D0); // MOVE.B	#$B4,D0
	DEF_ROMLOC(71EF6): move_toreg_8(read_8(A5 + 0xA), &D1); // MOVE.B	10(A5),D1
	DEF_ROMLOC(71EFA): CALL(rom_72722); // JSR	2086(PC)
}
ROMFUNC(rom_71F02) {
	DEF_ROMLOC(71F02): A0 = read_32(0x71990); // MOVEA.L	$00071990,A0
	DEF_ROMLOC(71F08): A1 = A6 + 0xA; // LEA.L	10(A6),A1
	DEF_ROMLOC(71F0C): move_toreg_8(read_8(A6 + 0x0), &D3); // MOVE.B	0(A6),D3
	DEF_ROMLOC(71F10): D4 = 0x2; // MOVEQ.L	$02,D4
	DEF_ROMLOC(71F12): move_toreg_8(read_8(A1), &D0); // MOVE.B	(A1),D0
	DEF_ROMLOC(71F14): move_toreg_8(D0, &D1); // MOVE.B	D0,D1
	DEF_ROMLOC(71F16): clr_mem_8(A1++); // CLR.B	(A1)+
	DEF_ROMLOC(71F18): sub_toreg_8(0xFFFFFF81, &D0); // SUBI.B	#$81,D0
	DEF_ROMLOC(71F1C): if (CCR_CS) goto rom_71F3E; // BCS.B	$71F3E
	DEF_ROMLOC(71F1E): cmp_tomem_8(0xFFFFFF80, A6 + offsetof(SMPS_RAM, v_sound_id)); // CMPI.B	#$80,9(A6)
	DEF_ROMLOC(71F24): if (CCR_EQ) goto rom_71F2C; // BEQ.B	$71F2C
	DEF_ROMLOC(71F26): move_tomem_8(D1, A6 + 0xA); // MOVE.B	D1,10(A6)
	DEF_ROMLOC(71F2A): goto rom_71F3E; // BRA.B	$71F3E
	DEF_ROMLOC(71F2C): and_toreg_16(0x7F, &D0); // ANDI.W	#$007F,D0
	DEF_ROMLOC(71F30): move_toreg_8(read_8((s32)A0 + (s8)0x0 + (s16)D0), &D2); // MOVE.B	0(A0,D0),D2
	DEF_ROMLOC(71F34): cmp_toreg_8(D3, &D2); // CMP.B	D3,D2
	DEF_ROMLOC(71F36): if (CCR_CS) goto rom_71F3E; // BCS.B	$71F3E
	DEF_ROMLOC(71F38): move_toreg_8(D2, &D3); // MOVE.B	D2,D3
	DEF_ROMLOC(71F3A): move_tomem_8(D1, A6 + offsetof(SMPS_RAM, v_sound_id)); // MOVE.B	D1,9(A6)
	DEF_ROMLOC(71F3E): dec_reg_16(&D4); if ((D4 & 0xffff) != 0xffff) goto rom_71F12; // DBF.W	D4,$71F12
	DEF_ROMLOC(71F42): tst_reg_8(&D3); // TST.B	D3
	DEF_ROMLOC(71F44): if (CCR_MI) return; // BMI.B	$71F4A
	DEF_ROMLOC(71F46): move_tomem_8(D3, A6 + 0x0); // MOVE.B	D3,0(A6)
}
ROMFUNC(play_sound_id) {
	DEF_ROMLOC(71F4C): D7 = 0; // MOVEQ.L	$00,D7
	DEF_ROMLOC(71F4E): move_toreg_8(read_8(A6 + offsetof(SMPS_RAM, v_sound_id)), &D7); // MOVE.B	9(A6),D7
	DEF_ROMLOC(71F52): if (CCR_EQ) {rom_7259E();return;} // BEQ.W	$7259E
	DEF_ROMLOC(71F56): if (CCR_PL) return; // BPL.B	$71F8C
	DEF_ROMLOC(71F58): move_tomem_8(0x80, A6 + offsetof(SMPS_RAM, v_sound_id)); // MOVE.B	#$80,9(A6)
	DEF_ROMLOC(71F5E): cmp_toreg_8(0x9F, &D7); // CMPI.B	#$9F,D7
	DEF_ROMLOC(71F62): if (CCR_LS) {sound_play_bgm();return;} // BLS.W	$71FD2
	DEF_ROMLOC(71F66): cmp_toreg_8(0xA0, &D7); // CMPI.B	#$A0,D7
	DEF_ROMLOC(71F6A): if (CCR_CS) return; // BCS.W	$71F8C
	DEF_ROMLOC(71F6E): cmp_toreg_8(0xCF, &D7); // CMPI.B	#$CF,D7
	DEF_ROMLOC(71F72): if (CCR_LS) {rom_721C6();return;} // BLS.W	$721C6
	DEF_ROMLOC(71F76): cmp_toreg_8(0xD0, &D7); // CMPI.B	#$D0,D7
	DEF_ROMLOC(71F7A): if (CCR_CS) return; // BCS.W	$71F8C
	DEF_ROMLOC(71F7E): cmp_toreg_8(0xE0, &D7); // CMPI.B	#$E0,D7
	DEF_ROMLOC(71F82): if (CCR_CS) {rom_7230C();return;} // BCS.W	$7230C
	DEF_ROMLOC(71F86): cmp_toreg_8(0xE4, &D7); // CMPI.B	#$E4,D7
	DEF_ROMLOC(71F8A): if (CCR_LS) {rom_71F8E();return;} // BLS.B	$71F8E
}
ROMFUNC(rom_71F8E) {
	DEF_ROMLOC(71F8E): sub_toreg_8(0xE0, &D7); // SUBI.B	#$E0,D7
	switch (D7 & 0xffff) {
	case 0x00: rom_724E6(); break; // BRA.W	$724E6
	case 0x01: rom_71FAC(); break; // BRA.W	$71FAC
	case 0x02: rom_72624(); break; // BRA.W	$72624
	case 0x03: rom_72652(); break; // BRA.W	$72652
	case 0x04: rom_7259E(); break; // BRA.W	$7259E
	}
}
ROMFUNC(rom_71FAC) {
	set_dac_sample(0x88);
	sp_skip_level += 1; add_toreg_16(0x4, &A7); // ADDQ.W	#$04,A7
}
ROMFUNC(sound_play_bgm) {
	DEF_ROMLOC(71FD2): cmp_toreg_8(0xFFFFFF88, &D7); // CMPI.B	#$88,D7
	DEF_ROMLOC(71FD6): if (!CCR_EQ) goto rom_72024; // BNE.B	$72024
	DEF_ROMLOC(71FD8): tst_mem_8(A6 + offsetof(SMPS_RAM, f_1up_playing)); // TST.B	39(A6)
	DEF_ROMLOC(71FDC): if (!CCR_EQ) goto rom_721B6; // BNE.W	$721B6
	DEF_ROMLOC(71FE0): A5 = A6 + 0x40; // LEA.L	64(A6),A5
	DEF_ROMLOC(71FE4): D0 = 0x9; // MOVEQ.L	$09,D0
	DEF_ROMLOC(71FE6): bclr_tomem_8(0x2, A5); // BCLR.B	#$02,(A5)
	DEF_ROMLOC(71FEA): add_toreg_16(0x30, &A5); // ADDA.W	#$0030,A5
	DEF_ROMLOC(71FEE): dec_reg_16(&D0); if ((D0 & 0xffff) != 0xffff) goto rom_71FE6; // DBF.W	D0,$71FE6
	DEF_ROMLOC(71FF2): A5 = A6 + 0x220; // LEA.L	544(A6),A5
	DEF_ROMLOC(71FF6): D0 = 0x5; // MOVEQ.L	$05,D0
	DEF_ROMLOC(71FF8): bclr_tomem_8(0x7, A5); // BCLR.B	#$07,(A5)
	DEF_ROMLOC(71FFC): add_toreg_16(0x30, &A5); // ADDA.W	#$0030,A5
	DEF_ROMLOC(72000): dec_reg_16(&D0); if ((D0 & 0xffff) != 0xffff) goto rom_71FF8; // DBF.W	D0,$71FF8
	DEF_ROMLOC(72004): clr_mem_8(A6 + 0x0); // CLR.B	0(A6)
	DEF_ROMLOC(72008): A0 = A6; // MOVEA.L	A6,A0
	DEF_ROMLOC(7200A): A1 = A6 + 0x3A0; // LEA.L	928(A6),A1
	DEF_ROMLOC(7200E): move_toreg_16(0x87, &D0); // MOVE.W	#$0087,D0
	DEF_ROMLOC(72012): move_tomem_32(read_32((A0 += 4, A0 - 4)), (A1 += 4, A1 - 4)); // MOVE.L	(A0)+,(A1)+
	DEF_ROMLOC(72014): dec_reg_16(&D0); if ((D0 & 0xffff) != 0xffff) goto rom_72012; // DBF.W	D0,$72012
	DEF_ROMLOC(72018): move_tomem_8(0xFFFFFF80, A6 + offsetof(SMPS_RAM, f_1up_playing)); // MOVE.B	#$80,39(A6)
	DEF_ROMLOC(7201E): clr_mem_8(A6 + 0x0); // CLR.B	0(A6)
	DEF_ROMLOC(72022): goto rom_7202C; // BRA.B	$7202C
	DEF_ROMLOC(72024): clr_mem_8(A6 + offsetof(SMPS_RAM, f_1up_playing)); // CLR.B	39(A6)
	DEF_ROMLOC(72028): clr_mem_8(A6 + offsetof(SMPS_RAM, v_fadein_counter)); // CLR.B	38(A6)
	DEF_ROMLOC(7202C): CALL(rom_725CA); // JSR	1436(PC)
	DEF_ROMLOC(72030): A4 = read_32(0x719A0); // MOVEA.L	$000719A0,A4
	DEF_ROMLOC(72036): sub_toreg_8(0xFFFFFF81, &D7); // SUBI.B	#$81,D7
	DEF_ROMLOC(7203A): move_tomem_8(read_8((s32)A4 + (s8)0x0 + (s16)D7), A6 + offsetof(SMPS_RAM, v_speeduptempo)); // MOVE.B	0(A4,D7),41(A6)
	DEF_ROMLOC(72040): A4 = read_32(0x71998); // MOVEA.L	$00071998,A4
	DEF_ROMLOC(72046): lsl_toreg_16(0x2, &D7); // LSL.W	#$02,D7
	DEF_ROMLOC(72048): A4 = read_32((s32)A4 + (s8)0x0 + (s16)D7); // MOVEA.L	0(A4,D7),A4
	DEF_ROMLOC(7204C): D0 = 0; // MOVEQ.L	$00,D0
	DEF_ROMLOC(7204E): move_toreg_16(read_16(A4), &D0); // MOVE.W	(A4),D0
	DEF_ROMLOC(72050): D0 += A4;
	DEF_ROMLOC(72052): move_tomem_32(D0, A6 + offsetof(SMPS_RAM, v_voice_ptr)); // MOVE.L	D0,24(A6)
	DEF_ROMLOC(72056): move_toreg_8(read_8(A4 + 0x5), &D0); // MOVE.B	5(A4),D0
	DEF_ROMLOC(7205A): move_tomem_8(D0, A6 + offsetof(SMPS_RAM, v_tempo_mod)); // MOVE.B	D0,40(A6)
	DEF_ROMLOC(7205E): tst_mem_8(A6 + offsetof(SMPS_RAM, f_speedup)); // TST.B	42(A6)
	DEF_ROMLOC(72062): if (CCR_EQ) goto rom_72068; // BEQ.B	$72068
	DEF_ROMLOC(72064): move_toreg_8(read_8(A6 + offsetof(SMPS_RAM, v_speeduptempo)), &D0); // MOVE.B	41(A6),D0
	DEF_ROMLOC(72068): move_tomem_8(D0, A6 + offsetof(SMPS_RAM, v_main_tempo)); // MOVE.B	D0,2(A6)
	DEF_ROMLOC(7206C): move_tomem_8(D0, A6 + offsetof(SMPS_RAM, v_main_tempo_timeout)); // MOVE.B	D0,1(A6)
	DEF_ROMLOC(72070): D1 = 0; // MOVEQ.L	$00,D1
	DEF_ROMLOC(72072): A3 = A4; // MOVEA.L	A4,A3
	DEF_ROMLOC(72074): add_toreg_16(0x6, &A4); // ADDQ.W	#$06,A4
	DEF_ROMLOC(72076): D7 = 0; // MOVEQ.L	$00,D7
	DEF_ROMLOC(72078): move_toreg_8(read_8(A3 + 0x2), &D7); // MOVE.B	2(A3),D7
	DEF_ROMLOC(7207C): if (CCR_EQ) goto rom_72114; // BEQ.W	$72114
	DEF_ROMLOC(72080): sub_toreg_8(0x1, &D7); // SUBQ.B	#$01,D7
	DEF_ROMLOC(72082): move_toreg_8(0xFFFFFFC0, &D1); // MOVE.B	#$C0,D1
	DEF_ROMLOC(72086): move_toreg_8(read_8(A3 + 0x4), &D4); // MOVE.B	4(A3),D4
	DEF_ROMLOC(7208A): D6 = 0x30; // MOVEQ.L	$30,D6
	DEF_ROMLOC(7208C): move_toreg_8(0x1, &D5); // MOVE.B	#$01,D5
	DEF_ROMLOC(72090): A1 = A6 + 0x40; // LEA.L	64(A6),A1
	DEF_ROMLOC(72094): A2 = 0x721BA; // LEA.L	292(PC),A2
	DEF_ROMLOC(72098): bset_tomem_8(0x7, A1); // BSET.B	#$07,(A1)
	DEF_ROMLOC(7209C): move_tomem_8(read_8(A2++), A1 + 0x1); // MOVE.B	(A2)+,1(A1)
	DEF_ROMLOC(720A0): move_tomem_8(D4, A1 + 0x2); // MOVE.B	D4,2(A1)
	DEF_ROMLOC(720A4): move_tomem_8(D6, A1 + 0xD); // MOVE.B	D6,13(A1)
	DEF_ROMLOC(720A8): move_tomem_8(D1, A1 + 0xA); // MOVE.B	D1,10(A1)
	DEF_ROMLOC(720AC): move_tomem_8(D5, A1 + 0xE); // MOVE.B	D5,14(A1)
	DEF_ROMLOC(720B0): D0 = 0; // MOVEQ.L	$00,D0
	DEF_ROMLOC(720B2): move_toreg_16(read_16((A4 += 2, A4 - 2)), &D0); // MOVE.W	(A4)+,D0
	DEF_ROMLOC(720B4): D0 += A3;
	DEF_ROMLOC(720B6): move_tomem_32(D0, A1 + 0x4); // MOVE.L	D0,4(A1)
	DEF_ROMLOC(720BA): move_tomem_16(read_16((A4 += 2, A4 - 2)), A1 + 0x8); // MOVE.W	(A4)+,8(A1)
	DEF_ROMLOC(720BE): add_toreg_16(D6, &A1); // ADDA.W	D6,A1
	DEF_ROMLOC(720C0): dec_reg_16(&D7); if ((D7 & 0xffff) != 0xffff) goto rom_72098; // DBF.W	D7,$72098
	DEF_ROMLOC(720C4): cmp_tomem_8(0x7, A3 + 0x2); // CMPI.B	#$07,2(A3)
	DEF_ROMLOC(720CA): if (!CCR_EQ) goto rom_720D8; // BNE.B	$720D8
	DEF_ROMLOC(720CC): D0 = 0x2B; // MOVEQ.L	$2B,D0
	DEF_ROMLOC(720CE): D1 = 0; // MOVEQ.L	$00,D1
	DEF_ROMLOC(720D0): write_fm_i(D0, D1); // JSR	1628(PC)
	DEF_ROMLOC(720D4): goto rom_72114; // BRA.W	$72114
	DEF_ROMLOC(720D8): D0 = 0x28; // MOVEQ.L	$28,D0
	DEF_ROMLOC(720DA): D1 = 0x6; // MOVEQ.L	$06,D1
	DEF_ROMLOC(720DC): write_fm_i(D0, D1); // JSR	1616(PC)
	DEF_ROMLOC(720E0): move_toreg_8(0x42, &D0); // MOVE.B	#$42,D0
	DEF_ROMLOC(720E4): D1 = 0x7F; // MOVEQ.L	$7F,D1
	DEF_ROMLOC(720E6): write_fm_ii(D0, D1); // JSR	1660(PC)
	DEF_ROMLOC(720EA): move_toreg_8(0x4A, &D0); // MOVE.B	#$4A,D0
	DEF_ROMLOC(720EE): D1 = 0x7F; // MOVEQ.L	$7F,D1
	DEF_ROMLOC(720F0): write_fm_ii(D0, D1); // JSR	1650(PC)
	DEF_ROMLOC(720F4): move_toreg_8(0x46, &D0); // MOVE.B	#$46,D0
	DEF_ROMLOC(720F8): D1 = 0x7F; // MOVEQ.L	$7F,D1
	DEF_ROMLOC(720FA): write_fm_ii(D0, D1); // JSR	1640(PC)
	DEF_ROMLOC(720FE): move_toreg_8(0x4E, &D0); // MOVE.B	#$4E,D0
	DEF_ROMLOC(72102): D1 = 0x7F; // MOVEQ.L	$7F,D1
	DEF_ROMLOC(72104): write_fm_ii(D0, D1); // JSR	1630(PC)
	DEF_ROMLOC(72108): move_toreg_8(0xFFFFFFB6, &D0); // MOVE.B	#$B6,D0
	DEF_ROMLOC(7210C): move_toreg_8(0xFFFFFFC0, &D1); // MOVE.B	#$C0,D1
	DEF_ROMLOC(72110): write_fm_ii(D0, D1); // JSR	1618(PC)
	DEF_ROMLOC(72114): D7 = 0; // MOVEQ.L	$00,D7
	DEF_ROMLOC(72116): move_toreg_8(read_8(A3 + 0x3), &D7); // MOVE.B	3(A3),D7
	DEF_ROMLOC(7211A): if (CCR_EQ) goto rom_72154; // BEQ.B	$72154
	DEF_ROMLOC(7211C): sub_toreg_8(0x1, &D7); // SUBQ.B	#$01,D7
	DEF_ROMLOC(7211E): A1 = A6 + 0x190; // LEA.L	400(A6),A1
	DEF_ROMLOC(72122): A2 = 0x721C2; // LEA.L	158(PC),A2
	DEF_ROMLOC(72126): bset_tomem_8(0x7, A1); // BSET.B	#$07,(A1)
	DEF_ROMLOC(7212A): move_tomem_8(read_8(A2++), A1 + 0x1); // MOVE.B	(A2)+,1(A1)
	DEF_ROMLOC(7212E): move_tomem_8(D4, A1 + 0x2); // MOVE.B	D4,2(A1)
	DEF_ROMLOC(72132): move_tomem_8(D6, A1 + 0xD); // MOVE.B	D6,13(A1)
	DEF_ROMLOC(72136): move_tomem_8(D5, A1 + 0xE); // MOVE.B	D5,14(A1)
	DEF_ROMLOC(7213A): D0 = 0; // MOVEQ.L	$00,D0
	DEF_ROMLOC(7213C): move_toreg_16(read_16((A4 += 2, A4 - 2)), &D0); // MOVE.W	(A4)+,D0
	DEF_ROMLOC(7213E): D0 += A3;
	DEF_ROMLOC(72140): move_tomem_32(D0, A1 + 0x4); // MOVE.L	D0,4(A1)
	DEF_ROMLOC(72144): move_tomem_16(read_16((A4 += 2, A4 - 2)), A1 + 0x8); // MOVE.W	(A4)+,8(A1)
	DEF_ROMLOC(72148): move_toreg_8(read_8(A4++), &D0); // MOVE.B	(A4)+,D0
	DEF_ROMLOC(7214A): move_tomem_8(read_8(A4++), A1 + 0xB); // MOVE.B	(A4)+,11(A1)
	DEF_ROMLOC(7214E): add_toreg_16(D6, &A1); // ADDA.W	D6,A1
	DEF_ROMLOC(72150): dec_reg_16(&D7); if ((D7 & 0xffff) != 0xffff) goto rom_72126; // DBF.W	D7,$72126
	DEF_ROMLOC(72154): A1 = A6 + 0x220; // LEA.L	544(A6),A1
	DEF_ROMLOC(72158): D7 = 0x5; // MOVEQ.L	$05,D7
	DEF_ROMLOC(7215A): tst_mem_8(A1); // TST.B	(A1)
	DEF_ROMLOC(7215C): if (CCR_PL) goto rom_7217C; // BPL.W	$7217C
	DEF_ROMLOC(72160): D0 = 0; // MOVEQ.L	$00,D0
	DEF_ROMLOC(72162): move_toreg_8(read_8(A1 + 0x1), &D0); // MOVE.B	1(A1),D0
	DEF_ROMLOC(72166): if (CCR_MI) goto rom_7216E; // BMI.B	$7216E
	DEF_ROMLOC(72168): sub_toreg_8(0x2, &D0); // SUBQ.B	#$02,D0
	DEF_ROMLOC(7216A): lsl_toreg_8(0x2, &D0); // LSL.B	#$02,D0
	DEF_ROMLOC(7216C): goto rom_72170; // BRA.B	$72170
	DEF_ROMLOC(7216E): lsr_toreg_8(0x3, &D0); // LSR.B	#$03,D0
	DEF_ROMLOC(72170): A0 = 0x722CC; // LEA.L	346(PC),A0
	DEF_ROMLOC(72174): A0 = read_32((s32)A0 + (s8)0x0 + (s16)D0); // MOVEA.L	0(A0,D0),A0
	DEF_ROMLOC(72178): bset_tomem_8(0x2, A0); // BSET.B	#$02,(A0)
	DEF_ROMLOC(7217C): add_toreg_16(D6, &A1); // ADDA.W	D6,A1
	DEF_ROMLOC(7217E): dec_reg_16(&D7); if ((D7 & 0xffff) != 0xffff) goto rom_7215A; // DBF.W	D7,$7215A
	DEF_ROMLOC(72182): tst_mem_16(A6 + 0x340); // TST.W	832(A6)
	DEF_ROMLOC(72186): if (CCR_PL) goto rom_7218E; // BPL.B	$7218E
	DEF_ROMLOC(72188): bset_tomem_8(0x2, A6 + 0x100); // BSET.B	#$02,256(A6)
	DEF_ROMLOC(7218E): tst_mem_16(A6 + 0x370); // TST.W	880(A6)
	DEF_ROMLOC(72192): if (CCR_PL) goto rom_7219A; // BPL.B	$7219A
	DEF_ROMLOC(72194): bset_tomem_8(0x2, A6 + 0x1F0); // BSET.B	#$02,496(A6)
	DEF_ROMLOC(7219A): A5 = A6 + 0x70; // LEA.L	112(A6),A5
	DEF_ROMLOC(7219E): D4 = 0x5; // MOVEQ.L	$05,D4
	DEF_ROMLOC(721A0): CALL(rom_726FE); // JSR	1372(PC)
	DEF_ROMLOC(721A4): add_toreg_16(D6, &A5); // ADDA.W	D6,A5
	DEF_ROMLOC(721A6): dec_reg_16(&D4); if ((D4 & 0xffff) != 0xffff) goto rom_721A0; // DBF.W	D4,$721A0
	DEF_ROMLOC(721AA): D4 = 0x2; // MOVEQ.L	$02,D4
	DEF_ROMLOC(721AC): CALL(rom_729A0); // JSR	2034(PC)
	DEF_ROMLOC(721B0): add_toreg_16(D6, &A5); // ADDA.W	D6,A5
	DEF_ROMLOC(721B2): dec_reg_16(&D4); if ((D4 & 0xffff) != 0xffff) goto rom_721AC; // DBF.W	D4,$721AC
	DEF_ROMLOC(721B6): sp_skip_level += 1; add_toreg_16(0x4, &A7); // ADDQ.W	#$04,A7
}
ROMFUNC(rom_721C6) {
	DEF_ROMLOC(721C6): tst_mem_8(A6 + offsetof(SMPS_RAM, f_1up_playing)); // TST.B	39(A6)
	DEF_ROMLOC(721CA): if (!CCR_EQ) goto rom_722C6; // BNE.W	$722C6
	DEF_ROMLOC(721CE): tst_mem_8(A6 + offsetof(SMPS_RAM, v_fadeout_counter)); // TST.B	4(A6)
	DEF_ROMLOC(721D2): if (!CCR_EQ) goto rom_722C6; // BNE.W	$722C6
	DEF_ROMLOC(721D6): tst_mem_8(A6 + offsetof(SMPS_RAM, f_fadein_flag)); // TST.B	36(A6)
	DEF_ROMLOC(721DA): if (!CCR_EQ) goto rom_722C6; // BNE.W	$722C6
	DEF_ROMLOC(721DE): cmp_toreg_8(0xFFFFFFB5, &D7); // CMPI.B	#$B5,D7
	DEF_ROMLOC(721E2): if (!CCR_EQ) goto rom_721F4; // BNE.B	$721F4
	DEF_ROMLOC(721E4): tst_mem_8(A6 + offsetof(SMPS_RAM, v_ring_speaker)); // TST.B	43(A6)
	DEF_ROMLOC(721E8): if (!CCR_EQ) goto rom_721EE; // BNE.B	$721EE
	DEF_ROMLOC(721EA): move_toreg_8(0xFFFFFFCE, &D7); // MOVE.B	#$CE,D7
	DEF_ROMLOC(721EE): bchg_tomem_8(0x0, A6 + offsetof(SMPS_RAM, v_ring_speaker)); // BCHG.B	#$00,43(A6)
	DEF_ROMLOC(721F4): cmp_toreg_8(0xFFFFFFA7, &D7); // CMPI.B	#$A7,D7
	DEF_ROMLOC(721F8): if (!CCR_EQ) goto rom_72208; // BNE.B	$72208
	DEF_ROMLOC(721FA): tst_mem_8(A6 + offsetof(SMPS_RAM, f_push_playing)); // TST.B	44(A6)
	DEF_ROMLOC(721FE): if (!CCR_EQ) goto rom_722C4; // BNE.W	$722C4
	DEF_ROMLOC(72202): move_tomem_8(0xFFFFFF80, A6 + offsetof(SMPS_RAM, f_push_playing)); // MOVE.B	#$80,44(A6)
	DEF_ROMLOC(72208): A0 = read_32(0x7199C); // MOVEA.L	$0007199C,A0
	DEF_ROMLOC(7220E): sub_toreg_8(0xFFFFFFA0, &D7); // SUBI.B	#$A0,D7
	DEF_ROMLOC(72212): lsl_toreg_16(0x2, &D7); // LSL.W	#$02,D7
	DEF_ROMLOC(72214): A3 = read_32((s32)A0 + (s8)0x0 + (s16)D7); // MOVEA.L	0(A0,D7),A3
	DEF_ROMLOC(72218): A1 = A3; // MOVEA.L	A3,A1
	DEF_ROMLOC(7221A): D1 = 0; // MOVEQ.L	$00,D1
	DEF_ROMLOC(7221C): move_toreg_16(read_16((A1 += 2, A1 - 2)), &D1); // MOVE.W	(A1)+,D1
	DEF_ROMLOC(7221E): D1 += A3;
	DEF_ROMLOC(72220): move_toreg_8(read_8(A1++), &D5); // MOVE.B	(A1)+,D5
	DEF_ROMLOC(72222): move_toreg_8(read_8(A1++), &D7); // MOVE.B	(A1)+,D7
	DEF_ROMLOC(72224): sub_toreg_8(0x1, &D7); // SUBQ.B	#$01,D7
	DEF_ROMLOC(72226): D6 = 0x30; // MOVEQ.L	$30,D6
	DEF_ROMLOC(72228): D3 = 0; // MOVEQ.L	$00,D3
	DEF_ROMLOC(7222A): move_toreg_8(read_8(A1 + 0x1), &D3); // MOVE.B	1(A1),D3
	DEF_ROMLOC(7222E): move_toreg_8(D3, &D4); // MOVE.B	D3,D4
	DEF_ROMLOC(72230): if (CCR_MI) goto rom_72244; // BMI.B	$72244
	DEF_ROMLOC(72232): sub_toreg_16(0x2, &D3); // SUBQ.W	#$02,D3
	DEF_ROMLOC(72234): lsl_toreg_16(0x2, &D3); // LSL.W	#$02,D3
	DEF_ROMLOC(72236): A5 = 0x722CC; // LEA.L	148(PC),A5
	DEF_ROMLOC(7223A): A5 = read_32((s32)A5 + (s8)0x0 + (s16)D3); // MOVEA.L	0(A5,D3),A5
	DEF_ROMLOC(7223E): bset_tomem_8(0x2, A5); // BSET.B	#$02,(A5)
	DEF_ROMLOC(72242): goto rom_7226E; // BRA.B	$7226E
	DEF_ROMLOC(72244): lsr_toreg_16(0x3, &D3); // LSR.W	#$03,D3
	DEF_ROMLOC(72246): A5 = 0x722CC; // LEA.L	132(PC),A5
	DEF_ROMLOC(7224A): A5 = read_32((s32)A5 + (s8)0x0 + (s16)D3); // MOVEA.L	0(A5,D3),A5
	DEF_ROMLOC(7224E): bset_tomem_8(0x2, A5); // BSET.B	#$02,(A5)
	DEF_ROMLOC(72252): cmp_toreg_8(0xFFFFFFC0, &D4); // CMPI.B	#$C0,D4
	DEF_ROMLOC(72256): if (!CCR_EQ) goto rom_7226E; // BNE.B	$7226E
	DEF_ROMLOC(72258): move_toreg_8(D4, &D0); // MOVE.B	D4,D0
	DEF_ROMLOC(7225A): or_toreg_8(0x1F, &D0); // ORI.B	#$1F,D0
	DEF_ROMLOC(7225E): write_psg(D0);
	DEF_ROMLOC(72264): bchg_toreg_32(0x5, &D0); // BCHG.L	#$05,D0
	DEF_ROMLOC(72268): write_psg(D0);
	DEF_ROMLOC(7226E): A5 = read_32(0x722EC + (s16)(D3 & 0xffff)); // MOVEA.L	124(PC,D3),A5
	DEF_ROMLOC(72272): A2 = A5; // MOVEA.L	A5,A2
	DEF_ROMLOC(72274): D0 = 0xB; // MOVEQ.L	$0B,D0
	DEF_ROMLOC(72276): clr_mem_32((A2 += 4, A2 - 4)); // CLR.L	(A2)+
	DEF_ROMLOC(72278): dec_reg_16(&D0); if ((D0 & 0xffff) != 0xffff) goto rom_72276; // DBF.W	D0,$72276
	DEF_ROMLOC(7227C): move_tomem_16(read_16((A1 += 2, A1 - 2)), A5); // MOVE.W	(A1)+,(A5)
	DEF_ROMLOC(7227E): move_tomem_8(D5, A5 + 0x2); // MOVE.B	D5,2(A5)
	DEF_ROMLOC(72282): D0 = 0; // MOVEQ.L	$00,D0
	DEF_ROMLOC(72284): move_toreg_16(read_16((A1 += 2, A1 - 2)), &D0); // MOVE.W	(A1)+,D0
	DEF_ROMLOC(72286): D0 += A3;
	DEF_ROMLOC(72288): move_tomem_32(D0, A5 + 0x4); // MOVE.L	D0,4(A5)
	DEF_ROMLOC(7228C): move_tomem_16(read_16((A1 += 2, A1 - 2)), A5 + 0x8); // MOVE.W	(A1)+,8(A5)
	DEF_ROMLOC(72290): move_tomem_8(0x1, A5 + 0xE); // MOVE.B	#$01,14(A5)
	DEF_ROMLOC(72296): move_tomem_8(D6, A5 + 0xD); // MOVE.B	D6,13(A5)
	DEF_ROMLOC(7229A): tst_reg_8(&D4); // TST.B	D4
	DEF_ROMLOC(7229C): if (CCR_MI) goto rom_722A8; // BMI.B	$722A8
	DEF_ROMLOC(7229E): move_tomem_8(0xFFFFFFC0, A5 + 0xA); // MOVE.B	#$C0,10(A5)
	DEF_ROMLOC(722A4): move_tomem_32(D1, A5 + 0x20); // MOVE.L	D1,32(A5)
	DEF_ROMLOC(722A8): dec_reg_16(&D7); if ((D7 & 0xffff) != 0xffff) goto rom_72228; // DBF.W	D7,$72228
	DEF_ROMLOC(722AC): tst_mem_8(A6 + 0x250); // TST.B	592(A6)
	DEF_ROMLOC(722B0): if (CCR_PL) goto rom_722B8; // BPL.B	$722B8
	DEF_ROMLOC(722B2): bset_tomem_8(0x2, A6 + 0x340); // BSET.B	#$02,832(A6)
	DEF_ROMLOC(722B8): tst_mem_8(A6 + 0x310); // TST.B	784(A6)
	DEF_ROMLOC(722BC): if (CCR_PL) goto rom_722C4; // BPL.B	$722C4
	DEF_ROMLOC(722BE): bset_tomem_8(0x2, A6 + 0x370); // BSET.B	#$02,880(A6)
	DEF_ROMLOC(722C4): return; // RTS
	DEF_ROMLOC(722C6): clr_mem_8(A6 + 0x0); // CLR.B	0(A6)
}
ROMFUNC(rom_7230C) {
	DEF_ROMLOC(7230C): tst_mem_8(A6 + offsetof(SMPS_RAM, f_1up_playing)); // TST.B	39(A6)
	DEF_ROMLOC(72310): if (!CCR_EQ) return; // BNE.W	$723C6
	DEF_ROMLOC(72314): tst_mem_8(A6 + offsetof(SMPS_RAM, v_fadeout_counter)); // TST.B	4(A6)
	DEF_ROMLOC(72318): if (!CCR_EQ) return; // BNE.W	$723C6
	DEF_ROMLOC(7231C): tst_mem_8(A6 + offsetof(SMPS_RAM, f_fadein_flag)); // TST.B	36(A6)
	DEF_ROMLOC(72320): if (!CCR_EQ) return; // BNE.W	$723C6
	DEF_ROMLOC(72324): A0 = read_32(0x71994); // MOVEA.L	$00071994,A0
	DEF_ROMLOC(7232A): sub_toreg_8(0xFFFFFFD0, &D7); // SUBI.B	#$D0,D7
	DEF_ROMLOC(7232E): lsl_toreg_16(0x2, &D7); // LSL.W	#$02,D7
	DEF_ROMLOC(72330): A3 = read_32((s32)A0 + (s8)0x0 + (s16)D7); // MOVEA.L	0(A0,D7),A3
	DEF_ROMLOC(72334): A1 = A3; // MOVEA.L	A3,A1
	DEF_ROMLOC(72336): D0 = 0; // MOVEQ.L	$00,D0
	DEF_ROMLOC(72338): move_toreg_16(read_16((A1 += 2, A1 - 2)), &D0); // MOVE.W	(A1)+,D0
	DEF_ROMLOC(7233A): D0 += A3;
	DEF_ROMLOC(7233C): move_tomem_32(D0, A6 + offsetof(SMPS_RAM, v_special_voice_ptr)); // MOVE.L	D0,32(A6)
	DEF_ROMLOC(72340): move_toreg_8(read_8(A1++), &D5); // MOVE.B	(A1)+,D5
	DEF_ROMLOC(72342): move_toreg_8(read_8(A1++), &D7); // MOVE.B	(A1)+,D7
	DEF_ROMLOC(72344): sub_toreg_8(0x1, &D7); // SUBQ.B	#$01,D7
	DEF_ROMLOC(72346): D6 = 0x30; // MOVEQ.L	$30,D6
	DEF_ROMLOC(72348): move_toreg_8(read_8(A1 + 0x1), &D4); // MOVE.B	1(A1),D4
	DEF_ROMLOC(7234C): if (CCR_MI) goto rom_7235A; // BMI.B	$7235A
	DEF_ROMLOC(7234E): bset_tomem_8(0x2, A6 + 0x100); // BSET.B	#$02,256(A6)
	DEF_ROMLOC(72354): A5 = A6 + 0x340; // LEA.L	832(A6),A5
	DEF_ROMLOC(72358): goto rom_72364; // BRA.B	$72364
	DEF_ROMLOC(7235A): bset_tomem_8(0x2, A6 + 0x1F0); // BSET.B	#$02,496(A6)
	DEF_ROMLOC(72360): A5 = A6 + 0x370; // LEA.L	880(A6),A5
	DEF_ROMLOC(72364): A2 = A5; // MOVEA.L	A5,A2
	DEF_ROMLOC(72366): D0 = 0xB; // MOVEQ.L	$0B,D0
	DEF_ROMLOC(72368): clr_mem_32((A2 += 4, A2 - 4)); // CLR.L	(A2)+
	DEF_ROMLOC(7236A): dec_reg_16(&D0); if ((D0 & 0xffff) != 0xffff) goto rom_72368; // DBF.W	D0,$72368
	DEF_ROMLOC(7236E): move_tomem_16(read_16((A1 += 2, A1 - 2)), A5); // MOVE.W	(A1)+,(A5)
	DEF_ROMLOC(72370): move_tomem_8(D5, A5 + 0x2); // MOVE.B	D5,2(A5)
	DEF_ROMLOC(72374): D0 = 0; // MOVEQ.L	$00,D0
	DEF_ROMLOC(72376): move_toreg_16(read_16((A1 += 2, A1 - 2)), &D0); // MOVE.W	(A1)+,D0
	DEF_ROMLOC(72378): D0 += A3;
	DEF_ROMLOC(7237A): move_tomem_32(D0, A5 + 0x4); // MOVE.L	D0,4(A5)
	DEF_ROMLOC(7237E): move_tomem_16(read_16((A1 += 2, A1 - 2)), A5 + 0x8); // MOVE.W	(A1)+,8(A5)
	DEF_ROMLOC(72382): move_tomem_8(0x1, A5 + 0xE); // MOVE.B	#$01,14(A5)
	DEF_ROMLOC(72388): move_tomem_8(D6, A5 + 0xD); // MOVE.B	D6,13(A5)
	DEF_ROMLOC(7238C): tst_reg_8(&D4); // TST.B	D4
	DEF_ROMLOC(7238E): if (CCR_MI) goto rom_72396; // BMI.B	$72396
	DEF_ROMLOC(72390): move_tomem_8(0xFFFFFFC0, A5 + 0xA); // MOVE.B	#$C0,10(A5)
	DEF_ROMLOC(72396): dec_reg_16(&D7); if ((D7 & 0xffff) != 0xffff) goto rom_72348; // DBF.W	D7,$72348
	DEF_ROMLOC(7239A): tst_mem_8(A6 + 0x250); // TST.B	592(A6)
	DEF_ROMLOC(7239E): if (CCR_PL) goto rom_723A6; // BPL.B	$723A6
	DEF_ROMLOC(723A0): bset_tomem_8(0x2, A6 + 0x340); // BSET.B	#$02,832(A6)
	DEF_ROMLOC(723A6): tst_mem_8(A6 + 0x310); // TST.B	784(A6)
	DEF_ROMLOC(723AA): if (CCR_PL) return; // BPL.B	$723C6
	DEF_ROMLOC(723AC): bset_tomem_8(0x2, A6 + 0x370); // BSET.B	#$02,880(A6)
	DEF_ROMLOC(723B2): or_toreg_8(0x1F, &D4); // ORI.B	#$1F,D4
	DEF_ROMLOC(723B6): write_psg(D4);
	DEF_ROMLOC(723BC): bchg_toreg_32(0x5, &D4); // BCHG.L	#$05,D4
	DEF_ROMLOC(723C0): write_psg(D4);
}
ROMFUNC(stop_sfx) {
	DEF_ROMLOC(723E0): clr_mem_8(A6 + 0x0); // CLR.B	0(A6)
	DEF_ROMLOC(723E4): A5 = A6 + 0x220; // LEA.L	544(A6),A5
	DEF_ROMLOC(723E8): D7 = 0x5; // MOVEQ.L	$05,D7
	DEF_ROMLOC(723EA): tst_mem_8(A5); // TST.B	(A5)
	DEF_ROMLOC(723EC): if (CCR_PL) goto rom_72472; // BPL.W	$72472
	DEF_ROMLOC(723F0): bclr_tomem_8(0x7, A5); // BCLR.B	#$07,(A5)
	DEF_ROMLOC(723F4): D3 = 0; // MOVEQ.L	$00,D3
	DEF_ROMLOC(723F6): move_toreg_8(read_8(A5 + 0x1), &D3); // MOVE.B	1(A5),D3
	DEF_ROMLOC(723FA): if (CCR_MI) goto rom_7243C; // BMI.B	$7243C
	DEF_ROMLOC(723FC): CALL(rom_726FE); // JSR	768(PC)
	DEF_ROMLOC(72400): cmp_toreg_8(0x4, &D3); // CMPI.B	#$04,D3
	DEF_ROMLOC(72404): if (!CCR_EQ) goto rom_72416; // BNE.B	$72416
	DEF_ROMLOC(72406): tst_mem_8(A6 + 0x340); // TST.B	832(A6)
	DEF_ROMLOC(7240A): if (CCR_PL) goto rom_72416; // BPL.B	$72416
	DEF_ROMLOC(7240C): A5 = A6 + 0x340; // LEA.L	832(A6),A5
	DEF_ROMLOC(72410): A1 = read_32(A6 + offsetof(SMPS_RAM, v_special_voice_ptr)); // MOVEA.L	32(A6),A1
	DEF_ROMLOC(72414): goto rom_72428; // BRA.B	$72428
	DEF_ROMLOC(72416): sub_toreg_8(0x2, &D3); // SUBQ.B	#$02,D3
	DEF_ROMLOC(72418): lsl_toreg_8(0x2, &D3); // LSL.B	#$02,D3
	DEF_ROMLOC(7241A): A0 = 0x722CC; // LEA.L	-336(PC),A0
	DEF_ROMLOC(7241E): A3 = A5; // MOVEA.L	A5,A3
	DEF_ROMLOC(72420): A5 = read_32((s32)A0 + (s8)0x0 + (s16)D3); // MOVEA.L	0(A0,D3),A5
	DEF_ROMLOC(72424): A1 = read_32(A6 + offsetof(SMPS_RAM, v_voice_ptr)); // MOVEA.L	24(A6),A1
	DEF_ROMLOC(72428): bclr_tomem_8(0x2, A5); // BCLR.B	#$02,(A5)
	DEF_ROMLOC(7242C): bset_tomem_8(0x1, A5); // BSET.B	#$01,(A5)
	DEF_ROMLOC(72430): move_toreg_8(read_8(A5 + 0xB), &D0); // MOVE.B	11(A5),D0
	DEF_ROMLOC(72434): CALL(set_voice); // JSR	2072(PC)
	DEF_ROMLOC(72438): A5 = A3; // MOVEA.L	A3,A5
	DEF_ROMLOC(7243A): goto rom_72472; // BRA.B	$72472
	DEF_ROMLOC(7243C): CALL(rom_729A0); // JSR	1378(PC)
	DEF_ROMLOC(72440): A0 = A6 + 0x370; // LEA.L	880(A6),A0
	DEF_ROMLOC(72444): cmp_toreg_8(0xFFFFFFE0, &D3); // CMPI.B	#$E0,D3
	DEF_ROMLOC(72448): if (CCR_EQ) goto rom_7245A; // BEQ.B	$7245A
	DEF_ROMLOC(7244A): cmp_toreg_8(0xFFFFFFC0, &D3); // CMPI.B	#$C0,D3
	DEF_ROMLOC(7244E): if (CCR_EQ) goto rom_7245A; // BEQ.B	$7245A
	DEF_ROMLOC(72450): lsr_toreg_8(0x3, &D3); // LSR.B	#$03,D3
	DEF_ROMLOC(72452): A0 = 0x722CC; // LEA.L	-392(PC),A0
	DEF_ROMLOC(72456): A0 = read_32((s32)A0 + (s8)0x0 + (s16)D3); // MOVEA.L	0(A0,D3),A0
	DEF_ROMLOC(7245A): bclr_tomem_8(0x2, A0); // BCLR.B	#$02,(A0)
	DEF_ROMLOC(7245E): bset_tomem_8(0x1, A0); // BSET.B	#$01,(A0)
	DEF_ROMLOC(72462): cmp_tomem_8(0xFFFFFFE0, A0 + 0x1); // CMPI.B	#$E0,1(A0)
	DEF_ROMLOC(72468): if (!CCR_EQ) goto rom_72472; // BNE.B	$72472
	DEF_ROMLOC(7246A): write_psg(read_8(A0 + 0x1F));
	DEF_ROMLOC(72472): add_toreg_16(0x30, &A5); // ADDA.W	#$0030,A5
	DEF_ROMLOC(72476): dec_reg_16(&D7); if ((D7 & 0xffff) != 0xffff) goto rom_723EA; // DBF.W	D7,$723EA
}
ROMFUNC(rom_7247C) {
	DEF_ROMLOC(7247C): A5 = A6 + 0x340; // LEA.L	832(A6),A5
	DEF_ROMLOC(72480): tst_mem_8(A5); // TST.B	(A5)
	DEF_ROMLOC(72482): if (CCR_PL) goto rom_724AE; // BPL.B	$724AE
	DEF_ROMLOC(72484): bclr_tomem_8(0x7, A5); // BCLR.B	#$07,(A5)
	DEF_ROMLOC(72488): btst_tomem_8(0x2, A5); // BTST.B	#$02,(A5)
	DEF_ROMLOC(7248C): if (!CCR_EQ) goto rom_724AE; // BNE.B	$724AE
	DEF_ROMLOC(7248E): CALL(send_fm_note_off); // JSR	634(PC)
	DEF_ROMLOC(72492): A5 = A6 + 0x100; // LEA.L	256(A6),A5
	DEF_ROMLOC(72496): bclr_tomem_8(0x2, A5); // BCLR.B	#$02,(A5)
	DEF_ROMLOC(7249A): bset_tomem_8(0x1, A5); // BSET.B	#$01,(A5)
	DEF_ROMLOC(7249E): tst_mem_8(A5); // TST.B	(A5)
	DEF_ROMLOC(724A0): if (CCR_PL) goto rom_724AE; // BPL.B	$724AE
	DEF_ROMLOC(724A2): A1 = read_32(A6 + offsetof(SMPS_RAM, v_voice_ptr)); // MOVEA.L	24(A6),A1
	DEF_ROMLOC(724A6): move_toreg_8(read_8(A5 + 0xB), &D0); // MOVE.B	11(A5),D0
	DEF_ROMLOC(724AA): CALL(set_voice); // JSR	1954(PC)
	DEF_ROMLOC(724AE): A5 = A6 + 0x370; // LEA.L	880(A6),A5
	DEF_ROMLOC(724B2): tst_mem_8(A5); // TST.B	(A5)
	DEF_ROMLOC(724B4): if (CCR_PL) return; // BPL.B	$724E4
	DEF_ROMLOC(724B6): bclr_tomem_8(0x7, A5); // BCLR.B	#$07,(A5)
	DEF_ROMLOC(724BA): btst_tomem_8(0x2, A5); // BTST.B	#$02,(A5)
	DEF_ROMLOC(724BE): if (!CCR_EQ) return; // BNE.B	$724E4
	DEF_ROMLOC(724C0): CALL(send_psg_note_off); // JSR	1252(PC)
	DEF_ROMLOC(724C4): A5 = A6 + 0x1F0; // LEA.L	496(A6),A5
	DEF_ROMLOC(724C8): bclr_tomem_8(0x2, A5); // BCLR.B	#$02,(A5)
	DEF_ROMLOC(724CC): bset_tomem_8(0x1, A5); // BSET.B	#$01,(A5)
	DEF_ROMLOC(724D0): tst_mem_8(A5); // TST.B	(A5)
	DEF_ROMLOC(724D2): if (CCR_PL) return; // BPL.B	$724E4
	DEF_ROMLOC(724D4): cmp_tomem_8(0xFFFFFFE0, A5 + 0x1); // CMPI.B	#$E0,1(A5)
	DEF_ROMLOC(724DA): if (!CCR_EQ) return; // BNE.B	$724E4
	DEF_ROMLOC(724DC): write_psg(read_8(A5 + 0x1F));
}
ROMFUNC(rom_724E6) {
	DEF_ROMLOC(724E6): CALL(stop_sfx); // JSR	-264(PC)
	DEF_ROMLOC(724EA): CALL(rom_7247C); // JSR	-112(PC)
	DEF_ROMLOC(724EE): move_tomem_8(0x3, A6 + offsetof(SMPS_RAM, v_fadeout_delay)); // MOVE.B	#$03,6(A6)
	DEF_ROMLOC(724F4): move_tomem_8(0x28, A6 + offsetof(SMPS_RAM, v_fadeout_counter)); // MOVE.B	#$28,4(A6)
	DEF_ROMLOC(724FA): clr_mem_8(A6 + 0x40); // CLR.B	64(A6)
	DEF_ROMLOC(724FE): clr_mem_8(A6 + offsetof(SMPS_RAM, f_speedup)); // CLR.B	42(A6)
}
ROMFUNC(rom_72504) {
	DEF_ROMLOC(72504): move_toreg_8(read_8(A6 + offsetof(SMPS_RAM, v_fadeout_delay)), &D0); // MOVE.B	6(A6),D0
	DEF_ROMLOC(72508): if (CCR_EQ) goto rom_72510; // BEQ.B	$72510
	DEF_ROMLOC(7250A): sub_tomem_8(0x1, A6 + offsetof(SMPS_RAM, v_fadeout_delay)); // SUBQ.B	#$01,6(A6)
	DEF_ROMLOC(7250E): return; // RTS
	DEF_ROMLOC(72510): sub_tomem_8(0x1, A6 + offsetof(SMPS_RAM, v_fadeout_counter)); // SUBQ.B	#$01,4(A6)
	DEF_ROMLOC(72514): if (CCR_EQ) {rom_7259E();return;} // BEQ.W	$7259E
	DEF_ROMLOC(72518): move_tomem_8(0x3, A6 + offsetof(SMPS_RAM, v_fadeout_delay)); // MOVE.B	#$03,6(A6)
	DEF_ROMLOC(7251E): A5 = A6 + 0x70; // LEA.L	112(A6),A5
	DEF_ROMLOC(72522): D7 = 0x5; // MOVEQ.L	$05,D7
	DEF_ROMLOC(72524): tst_mem_8(A5); // TST.B	(A5)
	DEF_ROMLOC(72526): if (CCR_PL) goto rom_72538; // BPL.B	$72538
	DEF_ROMLOC(72528): add_tomem_8(0x1, A5 + 0x9); // ADDQ.B	#$01,9(A5)
	DEF_ROMLOC(7252C): if (CCR_PL) goto rom_72534; // BPL.B	$72534
	DEF_ROMLOC(7252E): bclr_tomem_8(0x7, A5); // BCLR.B	#$07,(A5)
	DEF_ROMLOC(72532): goto rom_72538; // BRA.B	$72538
	DEF_ROMLOC(72534): CALL(send_voice_tl); // JSR	1918(PC)
	DEF_ROMLOC(72538): add_toreg_16(0x30, &A5); // ADDA.W	#$0030,A5
	DEF_ROMLOC(7253C): dec_reg_16(&D7); if ((D7 & 0xffff) != 0xffff) goto rom_72524; // DBF.W	D7,$72524
	DEF_ROMLOC(72540): D7 = 0x2; // MOVEQ.L	$02,D7
	DEF_ROMLOC(72542): tst_mem_8(A5); // TST.B	(A5)
	DEF_ROMLOC(72544): if (CCR_PL) goto rom_72560; // BPL.B	$72560
	DEF_ROMLOC(72546): add_tomem_8(0x1, A5 + 0x9); // ADDQ.B	#$01,9(A5)
	DEF_ROMLOC(7254A): cmp_tomem_8(0x10, A5 + 0x9); // CMPI.B	#$10,9(A5)
	DEF_ROMLOC(72550): if (CCR_CS) goto rom_72558; // BCS.B	$72558
	DEF_ROMLOC(72552): bclr_tomem_8(0x7, A5); // BCLR.B	#$07,(A5)
	DEF_ROMLOC(72556): goto rom_72560; // BRA.B	$72560
	DEF_ROMLOC(72558): move_toreg_8(read_8(A5 + 0x9), &D6); // MOVE.B	9(A5),D6
	DEF_ROMLOC(7255C): set_psg_volume(D6); // JSR	1036(PC)
	DEF_ROMLOC(72560): add_toreg_16(0x30, &A5); // ADDA.W	#$0030,A5
	DEF_ROMLOC(72564): dec_reg_16(&D7); if ((D7 & 0xffff) != 0xffff) goto rom_72542; // DBF.W	D7,$72542
}
ROMFUNC(rom_7256A) {
	DEF_ROMLOC(7256A): D3 = 0x2; // MOVEQ.L	$02,D3
	DEF_ROMLOC(7256C): D0 = 0x28; // MOVEQ.L	$28,D0
	DEF_ROMLOC(7256E): move_toreg_8(D3, &D1); // MOVE.B	D3,D1
	DEF_ROMLOC(72570): write_fm_i(D0, D1); // JSR	444(PC)
	DEF_ROMLOC(72574): add_toreg_8(0x4, &D1); // ADDQ.B	#$04,D1
	DEF_ROMLOC(72576): write_fm_i(D0, D1); // JSR	438(PC)
	DEF_ROMLOC(7257A): dec_reg_16(&D3); if ((D3 & 0xffff) != 0xffff) goto rom_7256E; // DBF.W	D3,$7256E
	DEF_ROMLOC(7257E): D0 = 0x40; // MOVEQ.L	$40,D0
	DEF_ROMLOC(72580): D1 = 0x7F; // MOVEQ.L	$7F,D1
	DEF_ROMLOC(72582): D4 = 0x2; // MOVEQ.L	$02,D4
	DEF_ROMLOC(72584): D3 = 0x3; // MOVEQ.L	$03,D3
	DEF_ROMLOC(72586): write_fm_i(D0, D1); // JSR	422(PC)
	DEF_ROMLOC(7258A): write_fm_ii(D0, D1); // JSR	472(PC)
	DEF_ROMLOC(7258E): add_toreg_16(0x4, &D0); // ADDQ.W	#$04,D0
	DEF_ROMLOC(72590): dec_reg_16(&D3); if ((D3 & 0xffff) != 0xffff) goto rom_72586; // DBF.W	D3,$72586
	DEF_ROMLOC(72594): sub_toreg_8(0xF, &D0); // SUBI.B	#$0F,D0
	DEF_ROMLOC(72598): dec_reg_16(&D4); if ((D4 & 0xffff) != 0xffff) goto rom_72584; // DBF.W	D4,$72584
}
ROMFUNC(rom_7259E) {
	DEF_ROMLOC(7259E): D0 = 0x2B; // MOVEQ.L	$2B,D0
	DEF_ROMLOC(725A0): move_toreg_8(0xFFFFFF80, &D1); // MOVE.B	#$80,D1
	DEF_ROMLOC(725A4): write_fm_i(D0, D1); // JSR	392(PC)
	DEF_ROMLOC(725A8): D0 = 0x27; // MOVEQ.L	$27,D0
	DEF_ROMLOC(725AA): D1 = 0; // MOVEQ.L	$00,D1
	DEF_ROMLOC(725AC): write_fm_i(D0, D1); // JSR	384(PC)
	DEF_ROMLOC(725B0): A0 = A6; // MOVEA.L	A6,A0
	DEF_ROMLOC(725B2): move_toreg_16(0xE3, &D0); // MOVE.W	#$00E3,D0
	DEF_ROMLOC(725B6): clr_mem_32((A0 += 4, A0 - 4)); // CLR.L	(A0)+
	DEF_ROMLOC(725B8): dec_reg_16(&D0); if ((D0 & 0xffff) != 0xffff) goto rom_725B6; // DBF.W	D0,$725B6
	DEF_ROMLOC(725BC): move_tomem_8(0x80, A6 + offsetof(SMPS_RAM, v_sound_id)); // MOVE.B	#$80,9(A6)
	DEF_ROMLOC(725C2): CALL(rom_7256A); // JSR	-90(PC)
	psg_silence_all(); // BRA.W	$729B6
}
ROMFUNC(rom_725CA) {
	DEF_ROMLOC(725CA): A0 = A6; // MOVEA.L	A6,A0
	DEF_ROMLOC(725CC): move_toreg_8(read_8(A6 + 0x0), &D1); // MOVE.B	0(A6),D1
	DEF_ROMLOC(725D0): move_toreg_8(read_8(A6 + offsetof(SMPS_RAM, f_1up_playing)), &D2); // MOVE.B	39(A6),D2
	DEF_ROMLOC(725D4): move_toreg_8(read_8(A6 + offsetof(SMPS_RAM, f_speedup)), &D3); // MOVE.B	42(A6),D3
	DEF_ROMLOC(725D8): move_toreg_8(read_8(A6 + offsetof(SMPS_RAM, v_fadein_counter)), &D4); // MOVE.B	38(A6),D4
	DEF_ROMLOC(725DC): move_toreg_16(read_16(A6 + 0xA), &D5); // MOVE.W	10(A6),D5
	DEF_ROMLOC(725E0): move_toreg_16(0x87, &D0); // MOVE.W	#$0087,D0
	DEF_ROMLOC(725E4): clr_mem_32((A0 += 4, A0 - 4)); // CLR.L	(A0)+
	DEF_ROMLOC(725E6): dec_reg_16(&D0); if ((D0 & 0xffff) != 0xffff) goto rom_725E4; // DBF.W	D0,$725E4
	DEF_ROMLOC(725EA): move_tomem_8(D1, A6 + 0x0); // MOVE.B	D1,0(A6)
	DEF_ROMLOC(725EE): move_tomem_8(D2, A6 + offsetof(SMPS_RAM, f_1up_playing)); // MOVE.B	D2,39(A6)
	DEF_ROMLOC(725F2): move_tomem_8(D3, A6 + offsetof(SMPS_RAM, f_speedup)); // MOVE.B	D3,42(A6)
	DEF_ROMLOC(725F6): move_tomem_8(D4, A6 + offsetof(SMPS_RAM, v_fadein_counter)); // MOVE.B	D4,38(A6)
	DEF_ROMLOC(725FA): move_tomem_16(D5, A6 + 0xA); // MOVE.W	D5,10(A6)
	DEF_ROMLOC(725FE): move_tomem_8(0x80, A6 + offsetof(SMPS_RAM, v_sound_id)); // MOVE.B	#$80,9(A6)
	DEF_ROMLOC(72604): CALL(rom_7256A); // JSR	-156(PC)
	psg_silence_all(); // BRA.W	$729B6
}
ROMFUNC(tempo_wait) {
	DEF_ROMLOC(7260C): move_tomem_8(read_8(A6 + offsetof(SMPS_RAM, v_main_tempo)), A6 + offsetof(SMPS_RAM, v_main_tempo_timeout)); // MOVE.B	2(A6),1(A6)
	DEF_ROMLOC(72612): A0 = A6 + 0x4E; // LEA.L	78(A6),A0
	DEF_ROMLOC(72616): D0 = 0x30; // MOVEQ.L	$30,D0
	DEF_ROMLOC(72618): D1 = 0x9; // MOVEQ.L	$09,D1
	DEF_ROMLOC(7261A): add_tomem_8(0x1, A0); // ADDQ.B	#$01,(A0)
	DEF_ROMLOC(7261C): add_toreg_16(D0, &A0); // ADDA.W	D0,A0
	DEF_ROMLOC(7261E): dec_reg_16(&D1); if ((D1 & 0xffff) != 0xffff) goto rom_7261A; // DBF.W	D1,$7261A
}
ROMFUNC(rom_72624) {
	DEF_ROMLOC(72624): tst_mem_8(A6 + offsetof(SMPS_RAM, f_1up_playing)); // TST.B	39(A6)
	DEF_ROMLOC(72628): if (!CCR_EQ) goto rom_7263E; // BNE.B	$7263E
	DEF_ROMLOC(7262A): move_tomem_8(read_8(A6 + offsetof(SMPS_RAM, v_speeduptempo)), A6 + offsetof(SMPS_RAM, v_main_tempo)); // MOVE.B	41(A6),2(A6)
	DEF_ROMLOC(72630): move_tomem_8(read_8(A6 + offsetof(SMPS_RAM, v_speeduptempo)), A6 + offsetof(SMPS_RAM, v_main_tempo_timeout)); // MOVE.B	41(A6),1(A6)
	DEF_ROMLOC(72636): move_tomem_8(0xFFFFFF80, A6 + offsetof(SMPS_RAM, f_speedup)); // MOVE.B	#$80,42(A6)
	DEF_ROMLOC(7263C): return; // RTS
	DEF_ROMLOC(7263E): move_tomem_8(read_8(A6 + 0x3C9), A6 + 0x3A2); // MOVE.B	969(A6),930(A6)
	DEF_ROMLOC(72644): move_tomem_8(read_8(A6 + 0x3C9), A6 + 0x3A1); // MOVE.B	969(A6),929(A6)
	DEF_ROMLOC(7264A): move_tomem_8(0xFFFFFF80, A6 + 0x3CA); // MOVE.B	#$80,970(A6)
}
ROMFUNC(rom_72652) {
	DEF_ROMLOC(72652): tst_mem_8(A6 + offsetof(SMPS_RAM, f_1up_playing)); // TST.B	39(A6)
	DEF_ROMLOC(72656): if (!CCR_EQ) goto rom_7266A; // BNE.B	$7266A
	DEF_ROMLOC(72658): move_tomem_8(read_8(A6 + offsetof(SMPS_RAM, v_tempo_mod)), A6 + offsetof(SMPS_RAM, v_main_tempo)); // MOVE.B	40(A6),2(A6)
	DEF_ROMLOC(7265E): move_tomem_8(read_8(A6 + offsetof(SMPS_RAM, v_tempo_mod)), A6 + offsetof(SMPS_RAM, v_main_tempo_timeout)); // MOVE.B	40(A6),1(A6)
	DEF_ROMLOC(72664): clr_mem_8(A6 + offsetof(SMPS_RAM, f_speedup)); // CLR.B	42(A6)
	DEF_ROMLOC(72668): return; // RTS
	DEF_ROMLOC(7266A): move_tomem_8(read_8(A6 + 0x3C8), A6 + 0x3A2); // MOVE.B	968(A6),930(A6)
	DEF_ROMLOC(72670): move_tomem_8(read_8(A6 + 0x3C8), A6 + 0x3A1); // MOVE.B	968(A6),929(A6)
	DEF_ROMLOC(72676): clr_mem_8(A6 + 0x3CA); // CLR.B	970(A6)
}
ROMFUNC(rom_7267C) {
	DEF_ROMLOC(7267C): tst_mem_8(A6 + offsetof(SMPS_RAM, v_fadein_delay)); // TST.B	37(A6)
	DEF_ROMLOC(72680): if (CCR_EQ) goto rom_72688; // BEQ.B	$72688
	DEF_ROMLOC(72682): sub_tomem_8(0x1, A6 + offsetof(SMPS_RAM, v_fadein_delay)); // SUBQ.B	#$01,37(A6)
	DEF_ROMLOC(72686): return; // RTS
	DEF_ROMLOC(72688): tst_mem_8(A6 + offsetof(SMPS_RAM, v_fadein_counter)); // TST.B	38(A6)
	DEF_ROMLOC(7268C): if (CCR_EQ) goto rom_726D6; // BEQ.B	$726D6
	DEF_ROMLOC(7268E): sub_tomem_8(0x1, A6 + offsetof(SMPS_RAM, v_fadein_counter)); // SUBQ.B	#$01,38(A6)
	DEF_ROMLOC(72692): move_tomem_8(0x2, A6 + offsetof(SMPS_RAM, v_fadein_delay)); // MOVE.B	#$02,37(A6)
	DEF_ROMLOC(72698): A5 = A6 + 0x70; // LEA.L	112(A6),A5
	DEF_ROMLOC(7269C): D7 = 0x5; // MOVEQ.L	$05,D7
	DEF_ROMLOC(7269E): tst_mem_8(A5); // TST.B	(A5)
	DEF_ROMLOC(726A0): if (CCR_PL) goto rom_726AA; // BPL.B	$726AA
	DEF_ROMLOC(726A2): sub_tomem_8(0x1, A5 + 0x9); // SUBQ.B	#$01,9(A5)
	DEF_ROMLOC(726A6): CALL(send_voice_tl); // JSR	1548(PC)
	DEF_ROMLOC(726AA): add_toreg_16(0x30, &A5); // ADDA.W	#$0030,A5
	DEF_ROMLOC(726AE): dec_reg_16(&D7); if ((D7 & 0xffff) != 0xffff) goto rom_7269E; // DBF.W	D7,$7269E
	DEF_ROMLOC(726B2): D7 = 0x2; // MOVEQ.L	$02,D7
	DEF_ROMLOC(726B4): tst_mem_8(A5); // TST.B	(A5)
	DEF_ROMLOC(726B6): if (CCR_PL) goto rom_726CC; // BPL.B	$726CC
	DEF_ROMLOC(726B8): sub_tomem_8(0x1, A5 + 0x9); // SUBQ.B	#$01,9(A5)
	DEF_ROMLOC(726BC): move_toreg_8(read_8(A5 + 0x9), &D6); // MOVE.B	9(A5),D6
	DEF_ROMLOC(726C0): cmp_toreg_8(0x10, &D6); // CMPI.B	#$10,D6
	DEF_ROMLOC(726C4): if (CCR_CS) goto rom_726C8; // BCS.B	$726C8
	DEF_ROMLOC(726C6): D6 = 0xF; // MOVEQ.L	$0F,D6
	DEF_ROMLOC(726C8): set_psg_volume(D6); // JSR	672(PC)
	DEF_ROMLOC(726CC): add_toreg_16(0x30, &A5); // ADDA.W	#$0030,A5
	DEF_ROMLOC(726D0): dec_reg_16(&D7); if ((D7 & 0xffff) != 0xffff) goto rom_726B4; // DBF.W	D7,$726B4
	DEF_ROMLOC(726D4): return; // RTS
	DEF_ROMLOC(726D6): bclr_tomem_8(0x2, A6 + 0x40); // BCLR.B	#$02,64(A6)
	DEF_ROMLOC(726DC): clr_mem_8(A6 + offsetof(SMPS_RAM, f_fadein_flag)); // CLR.B	36(A6)
}
ROMFUNC(rom_726E2) {
	DEF_ROMLOC(726E2): btst_tomem_8(0x1, A5); // BTST.B	#$01,(A5)
	DEF_ROMLOC(726E6): if (!CCR_EQ) return; // BNE.B	$726FC
	DEF_ROMLOC(726E8): btst_tomem_8(0x2, A5); // BTST.B	#$02,(A5)
	DEF_ROMLOC(726EC): if (!CCR_EQ) return; // BNE.B	$726FC
	DEF_ROMLOC(726EE): D0 = 0x28; // MOVEQ.L	$28,D0
	DEF_ROMLOC(726F0): move_toreg_8(read_8(A5 + 0x1), &D1); // MOVE.B	1(A5),D1
	DEF_ROMLOC(726F4): or_toreg_8(0xFFFFFFF0, &D1); // ORI.B	#$F0,D1
	DEF_ROMLOC(726F8): {write_fm_i(D0, D1);return;} // BRA.W	$7272E
}
ROMFUNC(rom_726FE) {
	DEF_ROMLOC(726FE): btst_tomem_8(0x4, A5); // BTST.B	#$04,(A5)
	DEF_ROMLOC(72702): if (!CCR_EQ) {return;} // BNE.B	$72714
	DEF_ROMLOC(72704): btst_tomem_8(0x2, A5); // BTST.B	#$02,(A5)
	DEF_ROMLOC(72708): if (!CCR_EQ) {return;} // BNE.B	$72714
	send_fm_note_off();
}
ROMFUNC(send_fm_note_off) {
	DEF_ROMLOC(7270A): D0 = 0x28; // MOVEQ.L	$28,D0
	DEF_ROMLOC(7270C): move_toreg_8(read_8(A5 + 0x1), &D1); // MOVE.B	1(A5),D1
	write_fm_i(D0, D1); // BRA.W	$7272E
}
ROMFUNC(rom_72716) {
	DEF_ROMLOC(72716): btst_tomem_8(0x2, A5); // BTST.B	#$02,(A5)
	DEF_ROMLOC(7271A): if (!CCR_EQ) return; // BNE.B	$72720
	DEF_ROMLOC(7271C): {rom_72722();return;} // BRA.W	$72722
}
ROMFUNC(rom_72722) {
	DEF_ROMLOC(72722): btst_tomem_8(0x2, A5 + 0x1); // BTST.B	#$02,1(A5)
	DEF_ROMLOC(72728): if (!CCR_EQ) {rom_7275A();return;} // BNE.B	$7275A
	DEF_ROMLOC(7272A): add_toreg_8(read_8(A5 + 0x1), &D0); // ADD.B	1(A5),D0
	write_fm_i(D0, D1);
}
ROMFUNC(rom_7275A) {
	DEF_ROMLOC(7275A): move_toreg_8(read_8(A5 + 0x1), &D2); // MOVE.B	1(A5),D2
	DEF_ROMLOC(7275E): bclr_toreg_32(0x2, &D2); // BCLR.L	#$02,D2
	DEF_ROMLOC(72762): add_toreg_8(D2, &D0); // ADD.B	D2,D0
	write_fm_ii(D0, D1);
}
ROMFUNC(rom_72850) {
	DEF_ROMLOC(72850): sub_tomem_8(0x1, A5 + 0xE); // SUBQ.B	#$01,14(A5)
	DEF_ROMLOC(72854): if (!CCR_EQ) goto rom_72866; // BNE.B	$72866
	DEF_ROMLOC(72856): bclr_tomem_8(0x4, A5); // BCLR.B	#$04,(A5)
	DEF_ROMLOC(7285A): CALL(rom_72878); // JSR	28(PC)
	DEF_ROMLOC(7285E): CALL(rom_728DC); // JSR	124(PC)
	DEF_ROMLOC(72862): {psg_do_vol_fx();return;} // BRA.W	$7292E
	DEF_ROMLOC(72866): CALL(rom_71D9E); // JSR	-2762(PC)
	DEF_ROMLOC(7286A): CALL(rom_72926); // JSR	186(PC)
	DEF_ROMLOC(7286E): CALL(rom_71DC6); // JSR	-2730(PC)
	DEF_ROMLOC(72872): CALL(psg_update_freq); // JSR	110(PC)
}
ROMFUNC(rom_72878) {
	DEF_ROMLOC(72878): bclr_tomem_8(0x1, A5); // BCLR.B	#$01,(A5)
	DEF_ROMLOC(7287C): A4 = read_32(A5 + 0x4); // MOVEA.L	4(A5),A4
	DEF_ROMLOC(72880): D5 = 0; // MOVEQ.L	$00,D5
	DEF_ROMLOC(72882): move_toreg_8(read_8(A4++), &D5); // MOVE.B	(A4)+,D5
	DEF_ROMLOC(72884): cmp_toreg_8(0xFFFFFFE0, &D5); // CMPI.B	#$E0,D5
	DEF_ROMLOC(72888): if (CCR_CS) goto rom_72890; // BCS.B	$72890
	DEF_ROMLOC(7288A): CALL(coord_flag); // JSR	462(PC)
	DEF_ROMLOC(7288E): goto rom_72880; // BRA.B	$72880
	DEF_ROMLOC(72890): tst_reg_8(&D5); // TST.B	D5
	DEF_ROMLOC(72892): if (CCR_PL) goto rom_728A4; // BPL.B	$728A4
	DEF_ROMLOC(72894): psg_set_freq(D5); // JSR	22(PC)
	DEF_ROMLOC(72898): move_toreg_8(read_8(A4++), &D5); // MOVE.B	(A4)+,D5
	DEF_ROMLOC(7289A): tst_reg_8(&D5); // TST.B	D5
	DEF_ROMLOC(7289C): if (CCR_PL) goto rom_728A4; // BPL.B	$728A4
	DEF_ROMLOC(7289E): sub_toreg_16(0x1, &A4); // SUBQ.W	#$01,A4
	DEF_ROMLOC(728A0): {finish_track_update();return;} // BRA.W	$71D60
	DEF_ROMLOC(728A4): CALL(set_duration); // JSR	-2918(PC)
	finish_track_update(); // BRA.W	$71D60
}
void psg_set_freq(u8 freqindex) {
	if (freqindex != 0x80) {
		freqindex -= 0x81;
		freqindex += read_8(A5 + 0x8);
		write_16(A5 + offsetof(SMPS_Track, Freq), PSG_FREQS[freqindex & 0x7f]);
		finish_track_update();
	} else {
		bset_tomem_8(0x1, A5);
		move_tomem_16(0xFFFFFFFF, A5 + 0x10);
		CALL(finish_track_update);
		rom_729A0();
	}
}
ROMFUNC(rom_728DC) {
	DEF_ROMLOC(728DC): move_toreg_16(read_16(A5 + 0x10), &D6); // MOVE.W	16(A5),D6
	DEF_ROMLOC(728E0): if (CCR_MI) {rom_72920();return;} // BMI.B	$72920
	psg_update_freq();
}
ROMFUNC(psg_update_freq) {
	DEF_ROMLOC(728E2): move_toreg_8(read_8(A5 + 0x1E), &D0); // MOVE.B	30(A5),D0
	DEF_ROMLOC(728E6): ext_reg_16(&D0); // EXT.W	D0
	DEF_ROMLOC(728E8): add_toreg_16(D0, &D6); // ADD.W	D0,D6
	DEF_ROMLOC(728EA): btst_tomem_8(0x2, A5); // BTST.B	#$02,(A5)
	DEF_ROMLOC(728EE): if (!CCR_EQ) return; // BNE.B	$7291E
	DEF_ROMLOC(728F0): btst_tomem_8(0x1, A5); // BTST.B	#$01,(A5)
	DEF_ROMLOC(728F4): if (!CCR_EQ) return; // BNE.B	$7291E
	DEF_ROMLOC(728F6): move_toreg_8(read_8(A5 + 0x1), &D0); // MOVE.B	1(A5),D0
	DEF_ROMLOC(728FA): cmp_toreg_8(0xFFFFFFE0, &D0); // CMPI.B	#$E0,D0
	DEF_ROMLOC(728FE): if (!CCR_EQ) goto rom_72904; // BNE.B	$72904
	DEF_ROMLOC(72900): move_toreg_8(0xFFFFFFC0, &D0); // MOVE.B	#$C0,D0
	DEF_ROMLOC(72904): move_toreg_16(D6, &D1); // MOVE.W	D6,D1
	DEF_ROMLOC(72906): and_toreg_8(0xF, &D1); // ANDI.B	#$0F,D1
	DEF_ROMLOC(7290A): or_toreg_8(D1, &D0); // OR.B	D1,D0
	DEF_ROMLOC(7290C): lsr_toreg_16(0x4, &D6); // LSR.W	#$04,D6
	DEF_ROMLOC(7290E): and_toreg_8(0x3F, &D6); // ANDI.B	#$3F,D6
	DEF_ROMLOC(72912): write_psg(D0);
	DEF_ROMLOC(72918): write_psg(D6);
}
ROMFUNC(rom_72920) {
	DEF_ROMLOC(72920): bset_tomem_8(0x1, A5); // BSET.B	#$01,(A5)
}
ROMFUNC(rom_72926) {
	DEF_ROMLOC(72926): tst_mem_8(A5 + 0xB); // TST.B	11(A5)
	DEF_ROMLOC(7292A): if (CCR_EQ) {return;} // BEQ.W	$7298A
	psg_do_vol_fx();
}
ROMFUNC(psg_do_vol_fx) {
	DEF_ROMLOC(7292E): move_toreg_8(read_8(A5 + 0x9), &D6); // MOVE.B	9(A5),D6
	DEF_ROMLOC(72932): D0 = 0; // MOVEQ.L	$00,D0
	DEF_ROMLOC(72934): move_toreg_8(read_8(A5 + 0xB), &D0); // MOVE.B	11(A5),D0
	DEF_ROMLOC(72938): if (CCR_EQ) {set_psg_volume(D6);return;} // BEQ.B	$7296A
	DEF_ROMLOC(7293A): A0 = read_32(0x719A4); // MOVEA.L	$000719A4,A0
	DEF_ROMLOC(72940): sub_toreg_16(0x1, &D0); // SUBQ.W	#$01,D0
	DEF_ROMLOC(72942): lsl_toreg_16(0x2, &D0); // LSL.W	#$02,D0
	DEF_ROMLOC(72944): A0 = read_32((s32)A0 + (s8)0x0 + (s16)D0); // MOVEA.L	0(A0,D0),A0
	DEF_ROMLOC(72948): move_toreg_8(read_8(A5 + 0xC), &D0); // MOVE.B	12(A5),D0
	DEF_ROMLOC(7294C): move_toreg_8(read_8((s32)A0 + (s8)0x0 + (s16)D0), &D0); // MOVE.B	0(A0,D0),D0
	DEF_ROMLOC(72950): add_tomem_8(0x1, A5 + 0xC); // ADDQ.B	#$01,12(A5)
	DEF_ROMLOC(72954): btst_toreg_32(0x7, &D0); // BTST.L	#$07,D0
	DEF_ROMLOC(72958): if (CCR_EQ) goto rom_72960; // BEQ.B	$72960
	DEF_ROMLOC(7295A): cmp_toreg_8(0xFFFFFF80, &D0); // CMPI.B	#$80,D0
	DEF_ROMLOC(7295E): if (CCR_EQ) {rom_7299A();return;} // BEQ.B	$7299A
	DEF_ROMLOC(72960): add_toreg_16(D0, &D6); // ADD.W	D0,D6
	DEF_ROMLOC(72962): cmp_toreg_8(0x10, &D6); // CMPI.B	#$10,D6
	DEF_ROMLOC(72966): if (CCR_CS) {set_psg_volume(D6);return;} // BCS.B	$7296A
	DEF_ROMLOC(72968): D6 = 0xF; // MOVEQ.L	$0F,D6
	set_psg_volume(D6);
}
void set_psg_volume(u8 vol) {
	DEF_ROMLOC(7296A): btst_tomem_8(0x1, A5); // BTST.B	#$01,(A5)
	DEF_ROMLOC(7296E): if (!CCR_EQ) {return;} // BNE.B	$7298A
	DEF_ROMLOC(72970): btst_tomem_8(0x2, A5); // BTST.B	#$02,(A5)
	DEF_ROMLOC(72974): if (!CCR_EQ) {return;} // BNE.B	$7298A
	DEF_ROMLOC(72976): btst_tomem_8(0x4, A5); // BTST.B	#$04,(A5)
	DEF_ROMLOC(7297A): if (!CCR_EQ) {psg_check_note_timeout(vol);return;} // BNE.B	$7298C
	rom_7297C(vol);
}
void rom_7297C(u8 vol) {
	DEF_ROMLOC(7297C): or_toreg_8(read_8(A5 + 0x1), &D6); // OR.B	1(A5),D6
	DEF_ROMLOC(72980): add_toreg_8(0x10, &D6); // ADDI.B	#$10,D6
	DEF_ROMLOC(72984): write_psg(D6);
}
void psg_check_note_timeout(u8 vol) {
	DEF_ROMLOC(7298C): tst_mem_8(A5 + 0x13); // TST.B	19(A5)
	DEF_ROMLOC(72990): if (CCR_EQ) {rom_7297C(vol);return;} // BEQ.B	$7297C
	DEF_ROMLOC(72992): tst_mem_8(A5 + 0x12); // TST.B	18(A5)
	DEF_ROMLOC(72996): if (!CCR_EQ) {rom_7297C(vol);return;} // BNE.B	$7297C
}
ROMFUNC(rom_7299A) {
	DEF_ROMLOC(7299A): sub_tomem_8(0x1, A5 + 0xC); // SUBQ.B	#$01,12(A5)
}
ROMFUNC(rom_729A0) {
	DEF_ROMLOC(729A0): btst_tomem_8(0x2, A5); // BTST.B	#$02,(A5)
	DEF_ROMLOC(729A4): if (!CCR_EQ) {return;} // BNE.B	$729B4
	send_psg_note_off();
}
ROMFUNC(send_psg_note_off) {
	DEF_ROMLOC(729A6): move_toreg_8(read_8(A5 + 0x1), &D0); // MOVE.B	1(A5),D0
	DEF_ROMLOC(729AA): or_toreg_8(0x1F, &D0); // ORI.B	#$1F,D0
	DEF_ROMLOC(729AE): write_psg(D0);
}
ROMFUNC(psg_silence_all) {
	DEF_ROMLOC(729BC): write_psg(0x9F);
	DEF_ROMLOC(729C0): write_psg(0xBF);
	DEF_ROMLOC(729C4): write_psg(0xDF);
	DEF_ROMLOC(729C8): write_psg(0xFF);
}
ROMFUNC(coord_flag) {
	sub_toreg_16(0xE0, &D5);
	switch (D5 & 0xffff) {
	case 0x00: {
		move_toreg_8(read_8(A4++), &D1); // MOVE.B	(A4)+,D1
		if (read_8(A5 + offsetof(SMPS_Track, VoiceControl)) & 0x80) {return;} // BMI.B	$72AEA
		move_toreg_8(read_8(A5 + offsetof(SMPS_Track, AMSFMSPan)), &D0); // MOVE.B	10(A5),D0
		and_toreg_8(0x37, &D0); // ANDI.B	#$37,D0
		or_toreg_8(D0, &D1); // OR.B	D0,D1
		move_tomem_8(D1, A5 + offsetof(SMPS_Track, AMSFMSPan)); // MOVE.B	D1,10(A5)
		move_toreg_8(0xB4, &D0); // MOVE.B	#$B4,D0
		rom_72716(); // BRA.W	$72716
	} break; // BRA.W	$72ACC
	case 0x01: {
		move_tomem_8(read_8(A4++), A5 + 0x1E);
	} break; // BRA.W	$72AEC
	case 0x02: {
		move_tomem_8(read_8(A4++), A6 + offsetof(SMPS_RAM, v_communication_byte));
	} break; // BRA.W	$72AF2
	case 0x03: {
		D0 = 0; // MOVEQ.L	$00,D0
		move_toreg_8(read_8(A5 + 0xD), &D0); // MOVE.B	13(A5),D0
		A4 = read_32((s32)A5 + (s8)0x0 + (s16)D0); // MOVEA.L	0(A5,D0),A4
		move_tomem_32(0x0, (s32)A5 + (s8)0x0 + (s16)D0); // MOVE.L	#$00000000,0(A5,D0)
		add_toreg_16(0x2, &A4); // ADDQ.W	#$02,A4
		add_toreg_8(0x4, &D0); // ADDQ.B	#$04,D0
		move_tomem_8(D0, A5 + 0xD); // MOVE.B	D0,13(A5)
	} break; // BRA.W	$72AF8
	case 0x04: rom_72B14(); break; // BRA.W	$72B14
	case 0x05: rom_72B9E(); break; // BRA.W	$72B9E
	case 0x06: rom_72BA4(); break; // BRA.W	$72BA4
	case 0x07: rom_72BAE(); break; // BRA.W	$72BAE
	case 0x08: rom_72BB4(); break; // BRA.W	$72BB4
	case 0x09: rom_72BBE(); break; // BRA.W	$72BBE
	case 0x0a: rom_72BC6(); break; // BRA.W	$72BC6
	case 0x0b: cf_set_tempo_divider_all(); break; // BRA.W	$72BD0
	case 0x0c: cf_change_psg_volume(); break; // BRA.W	$72BE6
	case 0x0d: cf_clear_push(); break; // BRA.W	$72BEE
	case 0x0e: cf_stop_special_fm4(); break; // BRA.W	$72BF4
	case 0x0f: {
		D0 = 0; // MOVEQ.L	$00,D0
		move_toreg_8(read_8(A4++), &D0); // MOVE.B	(A4)+,D0
		move_tomem_8(D0, A5 + 0xB); // MOVE.B	D0,11(A5)
		btst_tomem_8(0x2, A5); // BTST.B	#$02,(A5)
		if (!CCR_EQ) {return;} // BNE.W	$72CAA
		A1 = read_32(A6 + offsetof(SMPS_RAM, v_voice_ptr)); // MOVEA.L	24(A6),A1
		tst_mem_8(A6 + offsetof(SMPS_RAM, f_voice_selector)); // TST.B	14(A6)
		if (CCR_EQ) {set_voice();return;} // BEQ.B	$72C4E
		A1 = read_32(A5 + 0x20); // MOVEA.L	32(A5),A1
		tst_mem_8(A6 + offsetof(SMPS_RAM, f_voice_selector)); // TST.B	14(A6)
		if (CCR_MI) {set_voice();return;} // BMI.B	$72C4E
		A1 = read_32(A6 + offsetof(SMPS_RAM, v_special_voice_ptr)); // MOVEA.L	32(A6),A1
		set_voice();
	} break; // BRA.W	$72C26
	case 0x10: {
		bset_tomem_8(0x3, A5); // BSET.B	#$03,(A5)
		move_tomem_32(A4, A5 + 0x14); // MOVE.L	A4,20(A5)
		move_tomem_8(read_8(A4++), A5 + 0x18); // MOVE.B	(A4)+,24(A5)
		move_tomem_8(read_8(A4++), A5 + 0x19); // MOVE.B	(A4)+,25(A5)
		move_tomem_8(read_8(A4++), A5 + 0x1A); // MOVE.B	(A4)+,26(A5)
		move_toreg_8(read_8(A4++), &D0); // MOVE.B	(A4)+,D0
		lsr_toreg_8(0x1, &D0); // LSR.B	#$01,D0
		move_tomem_8(D0, A5 + 0x1B); // MOVE.B	D0,27(A5)
		clr_mem_16(A5 + 0x1C); // CLR.W	28(A5)
	} break; // BRA.W	$72D30
	case 0x11: cf_enable_modulation(); break; // BRA.W	$72D52
	case 0x12: cf_stop(); break; // BRA.W	$72D58
	case 0x13: cf_set_psg_noise(); break; // BRA.W	$72E06
	case 0x14: cf_disable_modulation(); break; // BRA.W	$72E20
	case 0x15: cf_set_psg_tone(); break; // BRA.W	$72E26
	case 0x16: cf_jump(); break; // BRA.W	$72E2C
	case 0x17: cf_repeat_at_pos(); break; // BRA.W	$72E38
	case 0x18: cf_jumpto_gosub(); break; // BRA.W	$72E52
	case 0x19: cf_opF9(); break; // BRA.W	$72E64
	}
}
ROMFUNC(rom_72B14) {
	DEF_ROMLOC(72B14): A0 = A6; // MOVEA.L	A6,A0
	DEF_ROMLOC(72B16): A1 = A6 + 0x3A0; // LEA.L	928(A6),A1
	DEF_ROMLOC(72B1A): move_toreg_16(0x87, &D0); // MOVE.W	#$0087,D0
	DEF_ROMLOC(72B1E): move_tomem_32(read_32((A1 += 4, A1 - 4)), (A0 += 4, A0 - 4)); // MOVE.L	(A1)+,(A0)+
	DEF_ROMLOC(72B20): dec_reg_16(&D0); if ((D0 & 0xffff) != 0xffff) goto rom_72B1E; // DBF.W	D0,$72B1E
	DEF_ROMLOC(72B24): bset_tomem_8(0x2, A6 + 0x40); // BSET.B	#$02,64(A6)
	DEF_ROMLOC(72B2A): A3 = A5; // MOVEA.L	A5,A3
	DEF_ROMLOC(72B2C): move_toreg_8(0x28, &D6); // MOVE.B	#$28,D6
	DEF_ROMLOC(72B30): sub_toreg_8(read_8(A6 + offsetof(SMPS_RAM, v_fadein_counter)), &D6); // SUB.B	38(A6),D6
	DEF_ROMLOC(72B34): D7 = 0x5; // MOVEQ.L	$05,D7
	DEF_ROMLOC(72B36): A5 = A6 + 0x70; // LEA.L	112(A6),A5
	DEF_ROMLOC(72B3A): btst_tomem_8(0x7, A5); // BTST.B	#$07,(A5)
	DEF_ROMLOC(72B3E): if (CCR_EQ) goto rom_72B5C; // BEQ.B	$72B5C
	DEF_ROMLOC(72B40): bset_tomem_8(0x1, A5); // BSET.B	#$01,(A5)
	DEF_ROMLOC(72B44): add_tomem_8(D6, A5 + 0x9); // ADD.B	D6,9(A5)
	DEF_ROMLOC(72B48): btst_tomem_8(0x2, A5); // BTST.B	#$02,(A5)
	DEF_ROMLOC(72B4C): if (!CCR_EQ) goto rom_72B5C; // BNE.B	$72B5C
	DEF_ROMLOC(72B4E): D0 = 0; // MOVEQ.L	$00,D0
	DEF_ROMLOC(72B50): move_toreg_8(read_8(A5 + 0xB), &D0); // MOVE.B	11(A5),D0
	DEF_ROMLOC(72B54): A1 = read_32(A6 + offsetof(SMPS_RAM, v_voice_ptr)); // MOVEA.L	24(A6),A1
	DEF_ROMLOC(72B58): CALL(set_voice); // JSR	244(PC)
	DEF_ROMLOC(72B5C): add_toreg_16(0x30, &A5); // ADDA.W	#$0030,A5
	DEF_ROMLOC(72B60): dec_reg_16(&D7); if ((D7 & 0xffff) != 0xffff) goto rom_72B3A; // DBF.W	D7,$72B3A
	DEF_ROMLOC(72B64): D7 = 0x2; // MOVEQ.L	$02,D7
	DEF_ROMLOC(72B66): btst_tomem_8(0x7, A5); // BTST.B	#$07,(A5)
	DEF_ROMLOC(72B6A): if (CCR_EQ) goto rom_72B78; // BEQ.B	$72B78
	DEF_ROMLOC(72B6C): bset_tomem_8(0x1, A5); // BSET.B	#$01,(A5)
	DEF_ROMLOC(72B70): CALL(rom_729A0); // JSR	-466(PC)
	DEF_ROMLOC(72B74): add_tomem_8(D6, A5 + 0x9); // ADD.B	D6,9(A5)
	DEF_ROMLOC(72B78): add_toreg_16(0x30, &A5); // ADDA.W	#$0030,A5
	DEF_ROMLOC(72B7C): dec_reg_16(&D7); if ((D7 & 0xffff) != 0xffff) goto rom_72B66; // DBF.W	D7,$72B66
	DEF_ROMLOC(72B80): A5 = A3; // MOVEA.L	A3,A5
	DEF_ROMLOC(72B82): move_tomem_8(0xFFFFFF80, A6 + offsetof(SMPS_RAM, f_fadein_flag)); // MOVE.B	#$80,36(A6)
	DEF_ROMLOC(72B88): move_tomem_8(0x28, A6 + offsetof(SMPS_RAM, v_fadein_counter)); // MOVE.B	#$28,38(A6)
	DEF_ROMLOC(72B8E): clr_mem_8(A6 + offsetof(SMPS_RAM, f_1up_playing)); // CLR.B	39(A6)
	DEF_ROMLOC(72B92): move_tomem_16(0x0, 0xA11100); // MOVE.W	#$0000,$00A11100
	DEF_ROMLOC(72B9A): sp_skip_level += 2; add_toreg_16(0x8, &A7); // ADDQ.W	#$08,A7
}
ROMFUNC(rom_72B9E) {
	DEF_ROMLOC(72B9E): move_tomem_8(read_8(A4++), A5 + 0x2); // MOVE.B	(A4)+,2(A5)
}
ROMFUNC(rom_72BA4) {
	DEF_ROMLOC(72BA4): move_toreg_8(read_8(A4++), &D0); // MOVE.B	(A4)+,D0
	DEF_ROMLOC(72BA6): add_tomem_8(D0, A5 + 0x9); // ADD.B	D0,9(A5)
	send_voice_tl(); // BRA.W	$72CB4
}
ROMFUNC(rom_72BAE) {
	DEF_ROMLOC(72BAE): bset_tomem_8(0x4, A5); // BSET.B	#$04,(A5)
}
ROMFUNC(rom_72BB4) {
	DEF_ROMLOC(72BB4): move_tomem_8(read_8(A4), A5 + 0x12); // MOVE.B	(A4),18(A5)
	DEF_ROMLOC(72BB8): move_tomem_8(read_8(A4++), A5 + 0x13); // MOVE.B	(A4)+,19(A5)
}
ROMFUNC(rom_72BBE) {
	DEF_ROMLOC(72BBE): move_toreg_8(read_8(A4++), &D0); // MOVE.B	(A4)+,D0
	DEF_ROMLOC(72BC0): add_tomem_8(D0, A5 + 0x8); // ADD.B	D0,8(A5)
}
ROMFUNC(rom_72BC6) {
	DEF_ROMLOC(72BC6): move_tomem_8(read_8(A4), A6 + offsetof(SMPS_RAM, v_main_tempo)); // MOVE.B	(A4),2(A6)
	DEF_ROMLOC(72BCA): move_tomem_8(read_8(A4++), A6 + offsetof(SMPS_RAM, v_main_tempo_timeout)); // MOVE.B	(A4)+,1(A6)
}
ROMFUNC(cf_set_tempo_divider_all) {
	DEF_ROMLOC(72BD0): A0 = A6 + 0x40; // LEA.L	64(A6),A0
	DEF_ROMLOC(72BD4): move_toreg_8(read_8(A4++), &D0); // MOVE.B	(A4)+,D0
	DEF_ROMLOC(72BD6): D1 = 0x30; // MOVEQ.L	$30,D1
	DEF_ROMLOC(72BD8): D2 = 0x9; // MOVEQ.L	$09,D2
	DEF_ROMLOC(72BDA): move_tomem_8(D0, A0 + 0x2); // MOVE.B	D0,2(A0)
	DEF_ROMLOC(72BDE): add_toreg_16(D1, &A0); // ADDA.W	D1,A0
	DEF_ROMLOC(72BE0): dec_reg_16(&D2); if ((D2 & 0xffff) != 0xffff) goto rom_72BDA; // DBF.W	D2,$72BDA
}
ROMFUNC(cf_change_psg_volume) {
	DEF_ROMLOC(72BE6): move_toreg_8(read_8(A4++), &D0); // MOVE.B	(A4)+,D0
	DEF_ROMLOC(72BE8): add_tomem_8(D0, A5 + 0x9); // ADD.B	D0,9(A5)
}
ROMFUNC(cf_clear_push) {
	DEF_ROMLOC(72BEE): clr_mem_8(A6 + offsetof(SMPS_RAM, f_push_playing)); // CLR.B	44(A6)
}
ROMFUNC(cf_stop_special_fm4) {
	DEF_ROMLOC(72BF4): bclr_tomem_8(0x7, A5); // BCLR.B	#$07,(A5)
	DEF_ROMLOC(72BF8): bclr_tomem_8(0x4, A5); // BCLR.B	#$04,(A5)
	DEF_ROMLOC(72BFC): CALL(rom_726FE); // JSR	-1280(PC)
	DEF_ROMLOC(72C00): tst_mem_8(A6 + 0x250); // TST.B	592(A6)
	DEF_ROMLOC(72C04): if (CCR_MI) goto rom_72C22; // BMI.B	$72C22
	DEF_ROMLOC(72C06): A3 = A5; // MOVEA.L	A5,A3
	DEF_ROMLOC(72C08): A5 = A6 + 0x100; // LEA.L	256(A6),A5
	DEF_ROMLOC(72C0C): A1 = read_32(A6 + offsetof(SMPS_RAM, v_voice_ptr)); // MOVEA.L	24(A6),A1
	DEF_ROMLOC(72C10): bclr_tomem_8(0x2, A5); // BCLR.B	#$02,(A5)
	DEF_ROMLOC(72C14): bset_tomem_8(0x1, A5); // BSET.B	#$01,(A5)
	DEF_ROMLOC(72C18): move_toreg_8(read_8(A5 + 0xB), &D0); // MOVE.B	11(A5),D0
	DEF_ROMLOC(72C1C): CALL(set_voice); // JSR	48(PC)
	DEF_ROMLOC(72C20): A5 = A3; // MOVEA.L	A3,A5
	DEF_ROMLOC(72C22): sp_skip_level += 2; add_toreg_16(0x8, &A7); // ADDQ.W	#$08,A7
}
ROMFUNC(set_voice) {
	DEF_ROMLOC(72C4E): sub_toreg_16(0x1, &D0); // SUBQ.W	#$01,D0
	DEF_ROMLOC(72C50): if (CCR_MI) goto rom_72C5C; // BMI.B	$72C5C
	DEF_ROMLOC(72C52): move_toreg_16(0x19, &D1); // MOVE.W	#$0019,D1
	DEF_ROMLOC(72C56): add_toreg_16(D1, &A1); // ADDA.W	D1,A1
	DEF_ROMLOC(72C58): dec_reg_16(&D0); if ((D0 & 0xffff) != 0xffff) goto rom_72C56; // DBF.W	D0,$72C56
	DEF_ROMLOC(72C5C): move_toreg_8(read_8(A1++), &D1); // MOVE.B	(A1)+,D1
	DEF_ROMLOC(72C5E): move_tomem_8(D1, A5 + 0x1F); // MOVE.B	D1,31(A5)
	DEF_ROMLOC(72C62): move_toreg_8(D1, &D4); // MOVE.B	D1,D4
	DEF_ROMLOC(72C64): move_toreg_8(0xFFFFFFB0, &D0); // MOVE.B	#$B0,D0
	DEF_ROMLOC(72C68): CALL(rom_72722); // JSR	-1352(PC)
	DEF_ROMLOC(72C6C): A2 = 0x72D18; // LEA.L	170(PC),A2
	DEF_ROMLOC(72C70): D3 = 0x13; // MOVEQ.L	$13,D3
	DEF_ROMLOC(72C72): move_toreg_8(read_8(A2++), &D0); // MOVE.B	(A2)+,D0
	DEF_ROMLOC(72C74): move_toreg_8(read_8(A1++), &D1); // MOVE.B	(A1)+,D1
	DEF_ROMLOC(72C76): CALL(rom_72722); // JSR	-1366(PC)
	DEF_ROMLOC(72C7A): dec_reg_16(&D3); if ((D3 & 0xffff) != 0xffff) goto rom_72C72; // DBF.W	D3,$72C72
	DEF_ROMLOC(72C7E): D5 = 0x3; // MOVEQ.L	$03,D5
	DEF_ROMLOC(72C80): and_toreg_16(0x7, &D4); // ANDI.W	#$0007,D4
	DEF_ROMLOC(72C84): move_toreg_8(read_8(0x72CAC + (s16)(D4 & 0xffff)), &D4); // MOVE.B	38(PC,D4),D4
	DEF_ROMLOC(72C88): move_toreg_8(read_8(A5 + 0x9), &D3); // MOVE.B	9(A5),D3
	DEF_ROMLOC(72C8C): move_toreg_8(read_8(A2++), &D0); // MOVE.B	(A2)+,D0
	DEF_ROMLOC(72C8E): move_toreg_8(read_8(A1++), &D1); // MOVE.B	(A1)+,D1
	DEF_ROMLOC(72C90): lsr_toreg_8(0x1, &D4); // LSR.B	#$01,D4
	DEF_ROMLOC(72C92): if (CCR_CC) goto rom_72C96; // BCC.B	$72C96
	DEF_ROMLOC(72C94): add_toreg_8(D3, &D1); // ADD.B	D3,D1
	DEF_ROMLOC(72C96): CALL(rom_72722); // JSR	-1398(PC)
	DEF_ROMLOC(72C9A): dec_reg_16(&D5); if ((D5 & 0xffff) != 0xffff) goto rom_72C8C; // DBF.W	D5,$72C8C
	DEF_ROMLOC(72C9E): move_toreg_8(0xFFFFFFB4, &D0); // MOVE.B	#$B4,D0
	DEF_ROMLOC(72CA2): move_toreg_8(read_8(A5 + 0xA), &D1); // MOVE.B	10(A5),D1
	DEF_ROMLOC(72CA6): CALL(rom_72722); // JSR	-1414(PC)
}
ROMFUNC(send_voice_tl) {
	DEF_ROMLOC(72CB4): btst_tomem_8(0x2, A5); // BTST.B	#$02,(A5)
	DEF_ROMLOC(72CB8): if (!CCR_EQ) return; // BNE.B	$72D16
	DEF_ROMLOC(72CBA): D0 = 0; // MOVEQ.L	$00,D0
	DEF_ROMLOC(72CBC): move_toreg_8(read_8(A5 + 0xB), &D0); // MOVE.B	11(A5),D0
	DEF_ROMLOC(72CC0): A1 = read_32(A6 + offsetof(SMPS_RAM, v_voice_ptr)); // MOVEA.L	24(A6),A1
	DEF_ROMLOC(72CC4): tst_mem_8(A6 + offsetof(SMPS_RAM, f_voice_selector)); // TST.B	14(A6)
	DEF_ROMLOC(72CC8): if (CCR_EQ) goto rom_72CD8; // BEQ.B	$72CD8
	DEF_ROMLOC(72CCA): A1 = read_32(A6 + offsetof(SMPS_RAM, v_special_voice_ptr)); // MOVEA.L	32(A6),A1
	DEF_ROMLOC(72CCE): tst_mem_8(A6 + offsetof(SMPS_RAM, f_voice_selector)); // TST.B	14(A6)
	DEF_ROMLOC(72CD2): if (CCR_MI) goto rom_72CD8; // BMI.B	$72CD8
	DEF_ROMLOC(72CD4): A1 = read_32(A6 + offsetof(SMPS_RAM, v_special_voice_ptr)); // MOVEA.L	32(A6),A1
	DEF_ROMLOC(72CD8): sub_toreg_16(0x1, &D0); // SUBQ.W	#$01,D0
	DEF_ROMLOC(72CDA): if (CCR_MI) goto rom_72CE6; // BMI.B	$72CE6
	DEF_ROMLOC(72CDC): move_toreg_16(0x19, &D1); // MOVE.W	#$0019,D1
	DEF_ROMLOC(72CE0): add_toreg_16(D1, &A1); // ADDA.W	D1,A1
	DEF_ROMLOC(72CE2): dec_reg_16(&D0); if ((D0 & 0xffff) != 0xffff) goto rom_72CE0; // DBF.W	D0,$72CE0
	DEF_ROMLOC(72CE6): add_toreg_16(0x15, &A1); // ADDA.W	#$0015,A1
	DEF_ROMLOC(72CEA): A2 = 0x72D2C; // LEA.L	64(PC),A2
	DEF_ROMLOC(72CEE): move_toreg_8(read_8(A5 + 0x1F), &D0); // MOVE.B	31(A5),D0
	DEF_ROMLOC(72CF2): and_toreg_16(0x7, &D0); // ANDI.W	#$0007,D0
	DEF_ROMLOC(72CF6): move_toreg_8(read_8(0x72CAC + (s16)(D0 & 0xffff)), &D4); // MOVE.B	-76(PC,D0),D4
	DEF_ROMLOC(72CFA): move_toreg_8(read_8(A5 + 0x9), &D3); // MOVE.B	9(A5),D3
	DEF_ROMLOC(72CFE): if (CCR_MI) return; // BMI.B	$72D16
	DEF_ROMLOC(72D00): D5 = 0x3; // MOVEQ.L	$03,D5
	DEF_ROMLOC(72D02): move_toreg_8(read_8(A2++), &D0); // MOVE.B	(A2)+,D0
	DEF_ROMLOC(72D04): move_toreg_8(read_8(A1++), &D1); // MOVE.B	(A1)+,D1
	DEF_ROMLOC(72D06): lsr_toreg_8(0x1, &D4); // LSR.B	#$01,D4
	DEF_ROMLOC(72D08): if (CCR_CC) goto rom_72D12; // BCC.B	$72D12
	DEF_ROMLOC(72D0A): add_toreg_8(D3, &D1); // ADD.B	D3,D1
	DEF_ROMLOC(72D0C): if (CCR_CS) goto rom_72D12; // BCS.B	$72D12
	DEF_ROMLOC(72D0E): CALL(rom_72722); // JSR	-1518(PC)
	DEF_ROMLOC(72D12): dec_reg_16(&D5); if ((D5 & 0xffff) != 0xffff) goto rom_72D02; // DBF.W	D5,$72D02
}
ROMFUNC(cf_enable_modulation) {
	DEF_ROMLOC(72D52): bset_tomem_8(0x3, A5); // BSET.B	#$03,(A5)
}
ROMFUNC(cf_stop) {
	DEF_ROMLOC(72D58): bclr_tomem_8(0x7, A5); // BCLR.B	#$07,(A5)
	DEF_ROMLOC(72D5C): bclr_tomem_8(0x4, A5); // BCLR.B	#$04,(A5)
	DEF_ROMLOC(72D60): tst_mem_8(A5 + 0x1); // TST.B	1(A5)
	DEF_ROMLOC(72D64): if (CCR_MI) goto rom_72D74; // BMI.B	$72D74
	DEF_ROMLOC(72D66): tst_mem_8(A6 + offsetof(SMPS_RAM, f_updating_dac)); // TST.B	8(A6)
	DEF_ROMLOC(72D6A): if (CCR_MI) goto rom_72E02; // BMI.W	$72E02
	DEF_ROMLOC(72D6E): CALL(rom_726FE); // JSR	-1650(PC)
	DEF_ROMLOC(72D72): goto rom_72D78; // BRA.B	$72D78
	DEF_ROMLOC(72D74): CALL(rom_729A0); // JSR	-982(PC)
	DEF_ROMLOC(72D78): tst_mem_8(A6 + offsetof(SMPS_RAM, f_voice_selector)); // TST.B	14(A6)
	DEF_ROMLOC(72D7C): if (CCR_PL) goto rom_72E02; // BPL.W	$72E02
	DEF_ROMLOC(72D80): clr_mem_8(A6 + 0x0); // CLR.B	0(A6)
	DEF_ROMLOC(72D84): D0 = 0; // MOVEQ.L	$00,D0
	DEF_ROMLOC(72D86): move_toreg_8(read_8(A5 + 0x1), &D0); // MOVE.B	1(A5),D0
	DEF_ROMLOC(72D8A): if (CCR_MI) goto rom_72DCC; // BMI.B	$72DCC
	DEF_ROMLOC(72D8C): A0 = 0x722CC; // LEA.L	-2754(PC),A0
	DEF_ROMLOC(72D90): A3 = A5; // MOVEA.L	A5,A3
	DEF_ROMLOC(72D92): cmp_toreg_8(0x4, &D0); // CMPI.B	#$04,D0
	DEF_ROMLOC(72D96): if (!CCR_EQ) goto rom_72DA8; // BNE.B	$72DA8
	DEF_ROMLOC(72D98): tst_mem_8(A6 + 0x340); // TST.B	832(A6)
	DEF_ROMLOC(72D9C): if (CCR_PL) goto rom_72DA8; // BPL.B	$72DA8
	DEF_ROMLOC(72D9E): A5 = A6 + 0x340; // LEA.L	832(A6),A5
	DEF_ROMLOC(72DA2): A1 = read_32(A6 + offsetof(SMPS_RAM, v_special_voice_ptr)); // MOVEA.L	32(A6),A1
	DEF_ROMLOC(72DA6): goto rom_72DB8; // BRA.B	$72DB8
	DEF_ROMLOC(72DA8): sub_toreg_8(0x2, &D0); // SUBQ.B	#$02,D0
	DEF_ROMLOC(72DAA): lsl_toreg_8(0x2, &D0); // LSL.B	#$02,D0
	DEF_ROMLOC(72DAC): A5 = read_32((s32)A0 + (s8)0x0 + (s16)D0); // MOVEA.L	0(A0,D0),A5
	DEF_ROMLOC(72DB0): tst_mem_8(A5); // TST.B	(A5)
	DEF_ROMLOC(72DB2): if (CCR_PL) goto rom_72DC8; // BPL.B	$72DC8
	DEF_ROMLOC(72DB4): A1 = read_32(A6 + offsetof(SMPS_RAM, v_voice_ptr)); // MOVEA.L	24(A6),A1
	DEF_ROMLOC(72DB8): bclr_tomem_8(0x2, A5); // BCLR.B	#$02,(A5)
	DEF_ROMLOC(72DBC): bset_tomem_8(0x1, A5); // BSET.B	#$01,(A5)
	DEF_ROMLOC(72DC0): move_toreg_8(read_8(A5 + 0xB), &D0); // MOVE.B	11(A5),D0
	DEF_ROMLOC(72DC4): CALL(set_voice); // JSR	-376(PC)
	DEF_ROMLOC(72DC8): A5 = A3; // MOVEA.L	A3,A5
	DEF_ROMLOC(72DCA): goto rom_72E02; // BRA.B	$72E02
	DEF_ROMLOC(72DCC): A0 = A6 + 0x370; // LEA.L	880(A6),A0
	DEF_ROMLOC(72DD0): tst_mem_8(A0); // TST.B	(A0)
	DEF_ROMLOC(72DD2): if (CCR_PL) goto rom_72DE0; // BPL.B	$72DE0
	DEF_ROMLOC(72DD4): cmp_toreg_8(0xFFFFFFE0, &D0); // CMPI.B	#$E0,D0
	DEF_ROMLOC(72DD8): if (CCR_EQ) goto rom_72DEA; // BEQ.B	$72DEA
	DEF_ROMLOC(72DDA): cmp_toreg_8(0xFFFFFFC0, &D0); // CMPI.B	#$C0,D0
	DEF_ROMLOC(72DDE): if (CCR_EQ) goto rom_72DEA; // BEQ.B	$72DEA
	DEF_ROMLOC(72DE0): A0 = 0x722CC; // LEA.L	-2838(PC),A0
	DEF_ROMLOC(72DE4): lsr_toreg_8(0x3, &D0); // LSR.B	#$03,D0
	DEF_ROMLOC(72DE6): A0 = read_32((s32)A0 + (s8)0x0 + (s16)D0); // MOVEA.L	0(A0,D0),A0
	DEF_ROMLOC(72DEA): bclr_tomem_8(0x2, A0); // BCLR.B	#$02,(A0)
	DEF_ROMLOC(72DEE): bset_tomem_8(0x1, A0); // BSET.B	#$01,(A0)
	DEF_ROMLOC(72DF2): cmp_tomem_8(0xFFFFFFE0, A0 + 0x1); // CMPI.B	#$E0,1(A0)
	DEF_ROMLOC(72DF8): if (!CCR_EQ) goto rom_72E02; // BNE.B	$72E02
	DEF_ROMLOC(72DFA): write_psg(read_8(A0 + 0x1F));
	DEF_ROMLOC(72E02): sp_skip_level += 2; add_toreg_16(0x8, &A7); // ADDQ.W	#$08,A7
}
ROMFUNC(cf_set_psg_noise) {
	DEF_ROMLOC(72E06): move_tomem_8(0xFFFFFFE0, A5 + 0x1); // MOVE.B	#$E0,1(A5)
	DEF_ROMLOC(72E0C): move_tomem_8(read_8(A4++), A5 + 0x1F); // MOVE.B	(A4)+,31(A5)
	DEF_ROMLOC(72E10): btst_tomem_8(0x2, A5); // BTST.B	#$02,(A5)
	DEF_ROMLOC(72E14): if (!CCR_EQ) return; // BNE.B	$72E1E
	DEF_ROMLOC(72E16): write_psg(read_8(A4 - 0x1));
}
ROMFUNC(cf_disable_modulation) {
	DEF_ROMLOC(72E20): bclr_tomem_8(0x3, A5); // BCLR.B	#$03,(A5)
}
ROMFUNC(cf_set_psg_tone) {
	DEF_ROMLOC(72E26): move_tomem_8(read_8(A4++), A5 + 0xB); // MOVE.B	(A4)+,11(A5)
}
ROMFUNC(cf_jump) {
	DEF_ROMLOC(72E2C): move_toreg_8(read_8(A4++), &D0); // MOVE.B	(A4)+,D0
	DEF_ROMLOC(72E2E): lsl_toreg_16(0x8, &D0); // LSL.W	#$08,D0
	DEF_ROMLOC(72E30): move_toreg_8(read_8(A4++), &D0); // MOVE.B	(A4)+,D0
	DEF_ROMLOC(72E32): add_toreg_16(D0, &A4); // ADDA.W	D0,A4
	DEF_ROMLOC(72E34): sub_toreg_16(0x1, &A4); // SUBQ.W	#$01,A4
}
ROMFUNC(cf_repeat_at_pos) {
	DEF_ROMLOC(72E38): D0 = 0; // MOVEQ.L	$00,D0
	DEF_ROMLOC(72E3A): move_toreg_8(read_8(A4++), &D0); // MOVE.B	(A4)+,D0
	DEF_ROMLOC(72E3C): move_toreg_8(read_8(A4++), &D1); // MOVE.B	(A4)+,D1
	DEF_ROMLOC(72E3E): tst_mem_8((s32)A5 + (s8)0x24 + (s16)D0); // TST.B	36(A5,D0)
	DEF_ROMLOC(72E42): if (!CCR_EQ) goto rom_72E48; // BNE.B	$72E48
	DEF_ROMLOC(72E44): move_tomem_8(D1, (s32)A5 + (s8)0x24 + (s16)D0); // MOVE.B	D1,36(A5,D0)
	DEF_ROMLOC(72E48): sub_tomem_8(0x1, (s32)A5 + (s8)0x24 + (s16)D0); // SUBQ.B	#$01,36(A5,D0)
	DEF_ROMLOC(72E4C): if (!CCR_EQ) {cf_jump();return;} // BNE.B	$72E2C
	DEF_ROMLOC(72E4E): add_toreg_16(0x2, &A4); // ADDQ.W	#$02,A4
}
ROMFUNC(cf_jumpto_gosub) {
	DEF_ROMLOC(72E52): D0 = 0; // MOVEQ.L	$00,D0
	DEF_ROMLOC(72E54): move_toreg_8(read_8(A5 + 0xD), &D0); // MOVE.B	13(A5),D0
	DEF_ROMLOC(72E58): sub_toreg_8(0x4, &D0); // SUBQ.B	#$04,D0
	DEF_ROMLOC(72E5A): move_tomem_32(A4, (s32)A5 + (s8)0x0 + (s16)D0); // MOVE.L	A4,0(A5,D0)
	DEF_ROMLOC(72E5E): move_tomem_8(D0, A5 + 0xD); // MOVE.B	D0,13(A5)
	cf_jump(); // BRA.B	$72E2C
}
ROMFUNC(cf_opF9) {
	write_fm_i(0x88, 0xF);
	write_fm_i(0x8C, 0xF);
}