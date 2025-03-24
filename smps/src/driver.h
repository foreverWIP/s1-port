#pragma once

#include "system.h"

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

extern SMPS_RAM sound_driver_ram;