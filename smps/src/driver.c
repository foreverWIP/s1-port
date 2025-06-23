#include "driver.h"
#include "system.h"

// #include "Game/SoundDriver/SoundTable.h"
// #include "Game/SoundDriver/SoundSfxTable.h"

// #include "Game/SoundDriver/SoundEnum.h"

// #include "YM2612/YM2612.h"
// #include "PSG/PSG.h"

#include <stddef.h>
#include <string.h>

#define SOUND_DRIVER_NUM_MUSIC_DAC_TRACKS                                      \
  (sizeof(v_snddriver_ram.state.v_music_dac_track) / sizeof(SoundDriverTrack))
#define SOUND_DRIVER_NUM_MUSIC_FM_TRACKS                                       \
  (sizeof(v_snddriver_ram.state.v_music_fm1_track) / sizeof(SoundDriverTrack))
#define SOUND_DRIVER_NUM_MUSIC_PSG_TRACKS                                      \
  (sizeof(v_snddriver_ram.state.v_music_psg1_track) / sizeof(SoundDriverTrack))

#define SOUND_DRIVER_NUM_SFX_FM_TRACKS                                         \
  (sizeof(v_snddriver_ram.v_sfx_fm3_track) / sizeof(SoundDriverTrack))
#define SOUND_DRIVER_NUM_SFX_PSG_TRACKS                                        \
  (sizeof(v_snddriver_ram.v_sfx_psg1_track) / sizeof(SoundDriverTrack))

#define SOUND_DRIVER_NUM_SPCSFX_FM_TRACKS                                      \
  (sizeof(v_snddriver_ram.v_spcsfx_fm4_track) / sizeof(SoundDriverTrack))
#define SOUND_DRIVER_NUM_SPCSFX_PSG_TRACKS                                     \
  (sizeof(v_snddriver_ram.v_spcsfx_psg3_track) / sizeof(SoundDriverTrack))

#define SOUND_DRIVER_NUM_MUSIC_TRACKS                                          \
  (SOUND_DRIVER_NUM_MUSIC_DAC_TRACKS + SOUND_DRIVER_NUM_MUSIC_FM_TRACKS +      \
   SOUND_DRIVER_NUM_MUSIC_PSG_TRACKS)
#define SOUND_DRIVER_NUM_SFX_TRACKS                                            \
  (SOUND_DRIVER_NUM_SFX_FM_TRACKS + SOUND_DRIVER_NUM_SFX_PSG_TRACKS)
#define SOUND_DRIVER_NUM_SPCSFX_TRACKS                                         \
  (SOUND_DRIVER_NUM_SPCSFX_FM_TRACKS + SOUND_DRIVER_NUM_SPCSFX_PSG_TRACKS)

#define SOUND_DRIVER_NUM_SOUND_QUEUES                                          \
  (sizeof(v_snddriver_ram.state.v_soundqueue) /                                \
   sizeof(v_snddriver_ram.state.v_soundqueue[0]))

#define Master_Clock 53693175
#define M68000_Clock (Master_Clock / 7)
#define Z80_Clock (Master_Clock / 15)
#define FM_Sample_Rate (M68000_Clock / (6 * 6 * 4))
#define PSG_Sample_Rate (Z80_Clock / 16)

#define pcmLoopCounterBase(sampleRate, baseCycles)                             \
  (int)(1 + (Z80_Clock / (sampleRate) - (baseCycles) + (13.0 / 2)) / 13)
/* 90 is the number of cycles zPlaySEGAPCMLoop takes to deliver one sample. */
#define pcmLoopCounter(sampleRate) (pcmLoopCounterBase(sampleRate, 90.0))
/* 301 is the number of cycles zPlayPCMLoop takes to deliver two samples. */
#define dpcmLoopCounter(sampleRate) (pcmLoopCounterBase(sampleRate, 301.0 / 2))

u8 *v_snddriver_ram_ptr;
SoundDriverRAM v_snddriver_ram;

void InitSoundDriver(void) { v_snddriver_ram_ptr = (u8 *)&v_snddriver_ram; }

static int DACUpdateTrack(SoundDriverTrack *track);
/*
static u8 DAC_sample_rate[6];
*/
static int FMUpdateTrack(SoundDriverTrack *track);
static int FMDoNext(SoundDriverTrack *track);
static void FMSetFreq(SoundDriverTrack *track, u8 *data_p, u8 freq);
static void SetDuration(SoundDriverTrack *track, u8 duration);
static void TrackSetRest(SoundDriverTrack *track, u8 *data_p);
static void FinishTrackUpdate(SoundDriverTrack *track, u8 *data_p);
static int NoteTimeoutUpdate(SoundDriverTrack *track);
static int DoModulation(SoundDriverTrack *track, s16 *freq);
static void FMPrepareNote(SoundDriverTrack *track);
static void FMUpdateFreq(SoundDriverTrack *track, s16 freq);
static void FMSetRest(SoundDriverTrack *track);
static void PauseMusic(void);
static void CycleSoundQueue(void);
static int PlaySoundID(void);
static int Sound_E0toE4(u8 sound_id);
static int PlaySegaSound(void);
static int Sound_PlayBGM(u8 sound_id);
static u8 FMDACInitBytes[SOUND_DRIVER_NUM_MUSIC_DAC_TRACKS +
                         SOUND_DRIVER_NUM_MUSIC_FM_TRACKS];
static u8 PSGInitBytes[SOUND_DRIVER_NUM_MUSIC_PSG_TRACKS];
static void Sound_PlaySFX(u8 sound_id);
static SoundDriverTrack *SFX_BGMChannelRAM[8];
static SoundDriverTrack *SFX_SFXChannelRAM[8];
static void Sound_PlaySpecial(u8 sound_id);
/*
static SoundDriverTrack *SpecSFX_BGMChannelRAM[2];
static SoundDriverTrack *SpecSFX_SFXChannelRAM[2];
static SoundDriverTrack *SpecSFX_SpecSFXChannelRAM[2];
*/
static void StopSFX(void);
static void StopSpecialSFX(void);
static int FadeOutMusic(void);
static void DoFadeOut(void);
static void FMSilenceAll(void);
static int StopAllSound(void);
static void InitMusicPlayback(void);
static void TempoWait(void);
static int SpeedUpMusic(void);
static int SlowDownMusic(void);
static void DoFadeIn(void);
static void FMNoteOn(SoundDriverTrack *track);
static void FMNoteOff(SoundDriverTrack *track);
static void SendFMNoteOff(SoundDriverTrack *track);
static void WriteFMIorIIMain(SoundDriverTrack *track, u8 addr, u8 data);
static void WriteFMIorII(SoundDriverTrack *track, u8 addr, u8 data);
static void WriteFMI(u8 addr, u8 data);
static void WriteFMIIPart(SoundDriverTrack *track, u8 addr, u8 data);
static void WriteFMII(u8 addr, u8 data);
static s16 FMFrequencies[8 * 12];
static int PSGUpdateTrack(SoundDriverTrack *track);
static int PSGDoNext(SoundDriverTrack *track);
static void PSGSetFreq(SoundDriverTrack *track, u8 *data_p, u8 note);
static void PSGDoNoteOn(SoundDriverTrack *track);
static void PSGUpdateFreq(SoundDriverTrack *track, s16 freq);
static void PSGSetRest(SoundDriverTrack *track);
static void PSGUpdateVolFX(SoundDriverTrack *track);
static void PSGDoVolFX(SoundDriverTrack *track);
static void SetPSGVolume(SoundDriverTrack *track, u8 volume);
static void PSGSendVolume(SoundDriverTrack *track, u8 volume);
static void PSGCheckNoteTimeout(SoundDriverTrack *track, u8 volume);
static void VolEnvHold(SoundDriverTrack *track);
static void PSGNoteOff(SoundDriverTrack *track);
static void SendPSGNoteOff(SoundDriverTrack *track);
static void PSGSilenceAll(void);
static s16 PSGFrequencies[12 * 5 + 10];
static int CoordFlag(SoundDriverTrack *track, u8 **data, u8 unit);
int (*coordflagLookup[0xFA - 0xE0])(SoundDriverTrack *track, u8 **data);
static int cfPanningAMSFMS(SoundDriverTrack *track, u8 **data);
static int cfDetune(SoundDriverTrack *track, u8 **data);
static int cfSetCommunication(SoundDriverTrack *track, u8 **data);
static int cfJumpReturn(SoundDriverTrack *track, u8 **data);
static int cfFadeInToPrevious(SoundDriverTrack *track, u8 **data);
static int cfSetTempoDivider(SoundDriverTrack *track, u8 **data);
static int cfChangeFMVolume(SoundDriverTrack *track, u8 **data);
static int cfHoldNote(SoundDriverTrack *track, u8 **data);
static int cfNoteTimeout(SoundDriverTrack *track, u8 **data);
static int cfChangeTransposition(SoundDriverTrack *track, u8 **data);
static int cfSetTempo(SoundDriverTrack *track, u8 **data);
static int cfSetTempoDividerAll(SoundDriverTrack *track, u8 **data);
static int cfChangePSGVolume(SoundDriverTrack *track, u8 **data);
static int cfClearPush(SoundDriverTrack *track, u8 **data);
static int cfStopSpecialFM4(SoundDriverTrack *track, u8 **data);
static int cfSetVoice(SoundDriverTrack *track, u8 **data);
static void SetVoice(SoundDriverTrack *track, u8 voice, u8 *voice_ptr);
extern u8 FMSlotMask[8];
static void SendVoiceTL(SoundDriverTrack *track);
extern u8 FMInstrumentOperatorTable[4 * 5];
extern u8 FMInstrumentTLTable[4];
static int cfModulation(SoundDriverTrack *track, u8 **data);
static int cfEnableModulation(SoundDriverTrack *track, u8 **data);
static int cfStopTrack(SoundDriverTrack *track, u8 **data);
static int cfSetPSGNoise(SoundDriverTrack *track, u8 **data);
static int cfDisableModulation(SoundDriverTrack *track, u8 **data);
static int cfSetPSGTone(SoundDriverTrack *track, u8 **data);
static int cfJumpTo(SoundDriverTrack *track, u8 **data);
static int cfRepeatAtPos(SoundDriverTrack *track, u8 **data);
static int cfJumpToGosub(SoundDriverTrack *track, u8 **data);
static int cfOpF9(SoundDriverTrack *track, u8 **data);

u8 SpeedUpIndex[8] = {
    0x07, /* GHZ */
    0x72, /* LZ */
    0x73, /* MZ */
    0x26, /* SLZ */
    0x15, /* SYZ */
    0x08, /* SBZ */
    0xFF, /* Invincibility */
    0x05  /* Extra Life */
};

u8 SoundPriorities[0xE5 - 0x81] = {
    0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
    0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
    0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x80, 0x70, 0x70, 0x70, 0x70,
    0x70, 0x70, 0x70, 0x70, 0x70, 0x68, 0x70, 0x70, 0x70, 0x60, 0x70, 0x70,
    0x60, 0x70, 0x60, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70,
    0x70, 0x70, 0x7F, 0x60, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70,
    0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x90,
    0x90, 0x90, 0x90, 0x90};

void smps_update(void) { UpdateMusic(); }

void smps_set_next_sound(u8 sound) {
  v_snddriver_ram.state.v_soundqueue[0] = sound;
}

void smps_set_next_sound_special(u8 sound) {
  v_snddriver_ram.state.v_soundqueue[1] = sound;
}

u8 smps_get_tempo(void) { return v_snddriver_ram.state.v_main_tempo; }
u8 smps_get_tempo_divisor(void) {
  return v_snddriver_ram.state.v_main_tempo_divisor;
}

void UpdateMusic(void) {
  SoundDriverTrack *track;
  size_t i = 0;

  v_snddriver_ram.state.f_voice_selector = 0;
  if (v_snddriver_ram.state.f_pausemusic) {
    PauseMusic();
    return;
  }

  if (--v_snddriver_ram.state.v_main_tempo_timeout == 0)
    TempoWait();

  /* Process fades */
  if (v_snddriver_ram.state.v_fadeout_counter)
    DoFadeOut();
  if (v_snddriver_ram.state.v_fadein_counter)
    DoFadeIn();

  /* Process queued sounds */
#ifdef SONIC1C_FIX_BUGS
  if (v_snddriver_ram.state.v_soundqueue[0] ||
      v_snddriver_ram.state.v_soundqueue[1] ||
      v_snddriver_ram.state.v_soundqueue[2])
#else
  if (v_snddriver_ram.state.v_soundqueue[0] ||
      v_snddriver_ram.state.v_soundqueue[1])
#endif
    CycleSoundQueue();

  /* Check for new sound plays */
  if (v_snddriver_ram.state.v_sound_id != 0x80) {
    if (PlaySoundID())
      return;
  }

  /* Update tracks */
  track = &v_snddriver_ram.state.v_music_dac_track[0];

  if (track->PlaybackControl & PLAYBACKCONTROL_PLAYING)
    if (DACUpdateTrack(track))
      return;
  v_snddriver_ram.state.f_updating_dac = 0;

  track = &v_snddriver_ram.state.v_music_fm1_track[0];
  for (i = 0; i < SOUND_DRIVER_NUM_MUSIC_FM_TRACKS; i++, track++) {
    if (track->PlaybackControl & PLAYBACKCONTROL_PLAYING)
      if (FMUpdateTrack(track))
        return;
  }

  track = &v_snddriver_ram.state.v_music_psg1_track[0];
  for (i = 0; i < SOUND_DRIVER_NUM_MUSIC_PSG_TRACKS; i++, track++) {
    if (track->PlaybackControl & PLAYBACKCONTROL_PLAYING)
      if (PSGUpdateTrack(track))
        return;
  }

  /* Update SFX tracks */
  v_snddriver_ram.state.f_voice_selector = 0x80;

  track = &v_snddriver_ram.v_sfx_fm3_track[0];
  for (i = 0; i < SOUND_DRIVER_NUM_SFX_FM_TRACKS; i++, track++) {
    if (track->PlaybackControl & PLAYBACKCONTROL_PLAYING)
      if (FMUpdateTrack(track))
        return;
  }

  track = &v_snddriver_ram.v_sfx_psg1_track[0];
  for (i = 0; i < SOUND_DRIVER_NUM_SFX_PSG_TRACKS; i++, track++) {
    if (track->PlaybackControl & PLAYBACKCONTROL_PLAYING)
      if (PSGUpdateTrack(track))
        return;
  }

  /* Update special SFX tracks */
  v_snddriver_ram.state.f_voice_selector = 0x40;

  track = &v_snddriver_ram.v_spcsfx_fm4_track[0];
  if (track->PlaybackControl & PLAYBACKCONTROL_PLAYING)
    if (FMUpdateTrack(track))
      return;

  track = &v_snddriver_ram.v_spcsfx_psg3_track[0];
  if (track->PlaybackControl & PLAYBACKCONTROL_PLAYING)
    if (PSGUpdateTrack(track))
      return;
}

static int DACUpdateTrack(SoundDriverTrack *track) {
  u8 *data_p;

  u8 unit;

  if (--track->u.dac.DurationTimeout)
    return 0;

  v_snddriver_ram.state.f_updating_dac = 0x80;

  data_p = track->DataPointer;

  /* Read next SMPS unit */
  while (1) {
    unit = *data_p++;
    if (unit < 0xE0)
      break;
    if (CoordFlag(track, &data_p, unit))
      return 1;
  }

  /* If the unit is a note */
  if (unit & 0x80) {
    track->u.dac.SavedDAC = unit;
    unit = *data_p++;

    if (unit & 0x80) {
      data_p--;
      track->u.dac.DurationTimeout = track->u.dac.SavedDuration;
    } else {
      SetDuration(track, unit);
    }
  } else {
    SetDuration(track, unit);
  }

  track->DataPointer = data_p;

  if (!(track->PlaybackControl & PLAYBACKCONTROL_SFX_OVERRIDE)) {
    u8 sample = track->u.dac.SavedDAC;
    if (sample != 0x80) {
      if (!(sample & (1 << 3))) {
        set_dac_sample(sample);
      } else {
        sample -= 0x88;
        set_dac_sample(0x83 + sample);
      }
    }
  }

  return 0;
}

/*
static u8 DAC_sample_rate[6] = {
        dpcmLoopCounter(9750),
        dpcmLoopCounter(8750),
        dpcmLoopCounter(7150),
        dpcmLoopCounter(7000),
        0xFF, 0xFF
};
*/

static int FMUpdateTrack(SoundDriverTrack *track) {
  if (!--track->u.fm.DurationTimeout) {
    track->PlaybackControl &= ~PLAYBACKCONTROL_DO_NOT_ATTACK_NEXT;
    if (FMDoNext(track))
      return 1;
    FMPrepareNote(track);
    FMNoteOn(track);
  } else {
    s16 freq;

    if (NoteTimeoutUpdate(track))
      return 0;
    if (DoModulation(track, &freq))
      return 0;
    FMUpdateFreq(track, freq);
  }

  return 0;
}

static int FMDoNext(SoundDriverTrack *track) {
  u8 *data_p;
  u8 unit;

  data_p = track->DataPointer;

  track->PlaybackControl &= ~PLAYBACKCONTROL_AT_REST;

  while (1) {
    unit = *data_p++;
    if (unit < 0xE0)
      break;
    if (CoordFlag(track, &data_p, unit))
      return 1;
  }

  FMNoteOff(track);

  /* If the unit is a note */
  if (unit & 0x80) {
    FMSetFreq(track, data_p, unit);

    unit = *data_p++;
    if (unit & 0x80) {
      data_p--;
      FinishTrackUpdate(track, data_p);
      return 0;
    }
  }

  SetDuration(track, unit);
  FinishTrackUpdate(track, data_p);
  return 0;
}

static void FMSetFreq(SoundDriverTrack *track, u8 *data_p, u8 freq) {
  freq -= 0x80;

  if (!freq) {
    TrackSetRest(track, data_p);
    return;
  }

  freq = (freq + track->u.fm.Transpose) & 0x7F;

  track->u.fm.Freq = FMFrequencies[freq];
}

static void SetDuration(SoundDriverTrack *track, u8 duration) {
  u8 counter;
  u8 final_duration;

  final_duration = duration;

  counter = track->TempoDivider;
  while (--counter)
    final_duration += duration;

  track->u.dac.SavedDuration = final_duration;
  track->u.dac.DurationTimeout = final_duration;
}

static void TrackSetRest(SoundDriverTrack *track, u8 *data_p) {
  track->PlaybackControl |= PLAYBACKCONTROL_AT_REST;
  track->u.fm.Freq = 0;
  FinishTrackUpdate(track, data_p);
}

static void FinishTrackUpdate(SoundDriverTrack *track, u8 *data_p) {
  track->DataPointer = data_p;

  track->u.fm.DurationTimeout = track->u.fm.SavedDuration;

  if (track->PlaybackControl & PLAYBACKCONTROL_DO_NOT_ATTACK_NEXT)
    return;

  track->u.fm.NoteTimeout = track->u.fm.NoteTimeoutMaster;

  track->u.psg.VolEnvIndex = 0;

  if (track->PlaybackControl & PLAYBACKCONTROL_MODULATION) {
    track->u.fm.ModulationWait = track->u.fm.ModulationPtr[0];
    track->u.fm.ModulationSpeed = track->u.fm.ModulationPtr[1];
    track->u.fm.ModulationDelta = track->u.fm.ModulationPtr[2];
    track->u.fm.ModulationSteps = track->u.fm.ModulationPtr[3] >> 1;
    track->u.fm.ModulationVal = 0;
  }
}

static int NoteTimeoutUpdate(SoundDriverTrack *track) {
  if (!track->u.fm.NoteTimeout || --track->u.fm.NoteTimeout)
    return 0;

  track->PlaybackControl |= PLAYBACKCONTROL_AT_REST;

  if (!(track->VoiceControl & VOICECONTROL_IS_PSG))
    FMNoteOff(track);
  else
    PSGNoteOff(track);

  return 1;
}

static int DoModulation(SoundDriverTrack *track, s16 *freq) {
  s16 delta;

  if (!(track->PlaybackControl & PLAYBACKCONTROL_MODULATION))
    return 1;

  if (track->u.fm.ModulationWait) {
    track->u.fm.ModulationWait--;
    return 1;
  }

  if (--track->u.fm.ModulationSpeed)
    return 1;

  track->u.fm.ModulationSpeed = track->u.fm.ModulationPtr[1];

  if (!track->u.fm.ModulationSteps) {
    track->u.fm.ModulationSteps = track->u.fm.ModulationPtr[3];
    track->u.fm.ModulationDelta = -track->u.fm.ModulationDelta;
    return 1;
  }

  track->u.fm.ModulationSteps--;

  delta = (s8)track->u.fm.ModulationDelta;
  delta += track->u.fm.ModulationVal;
  track->u.fm.ModulationVal = delta;

  delta += track->u.fm.Freq;

  *freq = delta;
  return 0;
}

static void FMPrepareNote(SoundDriverTrack *track) {
  if (track->PlaybackControl & PLAYBACKCONTROL_AT_REST)
    return;

  if (track->u.fm.Freq == 0) {
    FMSetRest(track);
    return;
  }

  FMUpdateFreq(track, track->u.fm.Freq);
}

static void FMUpdateFreq(SoundDriverTrack *track, s16 freq) {
  freq += (s8)track->u.fm.Detune;

  if (track->PlaybackControl & PLAYBACKCONTROL_SFX_OVERRIDE)
    return;

  /* Register for upper 6 bits of frequency */
  WriteFMIorII(track, 0xA4, freq >> 8);
  /* Register for lower 8 bits of frequency */
  WriteFMIorII(track, 0xA0, freq & 0xFF);
}

static void FMSetRest(SoundDriverTrack *track) {
  track->PlaybackControl |= PLAYBACKCONTROL_AT_REST;
}

static void PauseMusic(void) {
  /* If music is not being unpaused */
  if (v_snddriver_ram.state.f_pausemusic & 0x80) {
    int i;

    u8 fm_addr, fm_data;

    /* Check if music has already been paused */
    if (v_snddriver_ram.state.f_pausemusic == 2)
      return;
    v_snddriver_ram.state.f_pausemusic = 2;

    /* Pause FM tracks */
    fm_addr = 0xB4; /* Command to set AMS/FMS/panning */
    fm_data = 0x00; /* No panning, AMS or FMS */

    for (i = 0; i < 3; i++) {
      WriteFMI(fm_addr, fm_data);
      WriteFMII(fm_addr, fm_data);
      fm_addr++;
    }

    fm_addr = 0x28; /* Key on/off register */

    for (i = 3 - 1; i >= 0; i--) {
      WriteFMI(fm_addr, (u8)i);
      WriteFMI(fm_addr, (u8)i + 4);
      fm_addr++;
    }

    /* Pause PSG tracks */
    PSGSilenceAll();
  } else {
    size_t i;
    SoundDriverTrack *track;

    u8 fm_addr, fm_data;

    v_snddriver_ram.state.f_pausemusic = 0;

    /* Restore music FM tracks */
    track = &v_snddriver_ram.state.v_music_dac_track[0];
    for (i = 0; i < SOUND_DRIVER_NUM_MUSIC_DAC_TRACKS +
                        SOUND_DRIVER_NUM_MUSIC_FM_TRACKS;
         i++, track++) {
      if (!(track->PlaybackControl & PLAYBACKCONTROL_PLAYING))
        continue;
      if (track->PlaybackControl & PLAYBACKCONTROL_SFX_OVERRIDE)
        continue;

      fm_addr = 0xB4; /* Command to set AMS/FMS/panning */
      fm_data = track->u.fm.AMSFMSPan;

      WriteFMIorII(track, fm_addr, fm_data);
    }

    /* Restore sfx FM tracks */
    track = &v_snddriver_ram.v_sfx_fm3_track[0];
    for (i = 0; i < SOUND_DRIVER_NUM_SFX_FM_TRACKS; i++, track++) {
      if (!(track->PlaybackControl & PLAYBACKCONTROL_PLAYING))
        continue;
      if (track->PlaybackControl & PLAYBACKCONTROL_SFX_OVERRIDE)
        continue;

      fm_addr = 0xB4; /* Command to set AMS/FMS/panning */
      fm_data = track->u.fm.AMSFMSPan;

      WriteFMIorII(track, fm_addr, fm_data);
    }

    /* Restore special sfx track */
    track = &v_snddriver_ram.v_spcsfx_fm4_track[0];
    for (i = 0; i < SOUND_DRIVER_NUM_SPCSFX_FM_TRACKS; i++, track++) {
      if (!(track->PlaybackControl & PLAYBACKCONTROL_PLAYING))
        continue;
      if (track->PlaybackControl & PLAYBACKCONTROL_SFX_OVERRIDE)
        continue;

      fm_addr = 0xB4; /* Command to set AMS/FMS/panning */
      fm_data = track->u.fm.AMSFMSPan;
      WriteFMIorII(track, fm_addr, fm_data);
    }
  }
}

static void CycleSoundQueue(void) {
  size_t i;

  u8 *soundqueue;
  u8 sndprio;

  soundqueue = &v_snddriver_ram.state.v_soundqueue[0];

  sndprio = v_snddriver_ram.state.v_sndprio;

  for (i = 0; i < SOUND_DRIVER_NUM_SOUND_QUEUES; i++) {
    u8 sfx_idx, sfx;
    u8 sfx_pri;

    sfx_idx = *soundqueue;
    sfx = sfx_idx;
    *soundqueue++ = 0;

    /* Check if SFX is a valid index (not $80 or lower) */
    if (sfx_idx < bgm__First)
      continue;
    sfx_idx -= bgm__First;

    /* Is sound a $80 (silence/empty)? */
    if (v_snddriver_ram.state.v_sound_id != 0x80) {
      v_snddriver_ram.state.v_soundqueue[0] = sfx;
      continue;
    }

    sfx_pri = SoundPriorities[sfx_idx & 0x7F];

    if (sfx_pri < sndprio)
      continue;

    sndprio = sfx_pri;
    v_snddriver_ram.state.v_sound_id = sfx;
  }

  /* We don't want to change sound priority if it is negative */
  if (!(sndprio & 0x80))
    v_snddriver_ram.state.v_sndprio = sndprio;
}

static int PlaySoundID(void) {
  u8 sound_id;

  sound_id = v_snddriver_ram.state.v_sound_id;
  if (sound_id == 0)
    return StopAllSound();
  else if (!(sound_id & 0x80))
    return 0;

  v_snddriver_ram.state.v_sound_id = 0x80;

  /* Check if this is a music track */
  if (sound_id < sfx__First)
    return Sound_PlayBGM(sound_id);
  /* Check if this is a sound effect */
  else if (sound_id < spec__First)
    Sound_PlaySFX(sound_id);
  /* Check if this is a special sound effect */
  else if (sound_id < flg__First)
    Sound_PlaySpecial(sound_id);
  /* Check if this is an EX sound effect */
  else if (sound_id < 0xF0)
    return Sound_E0toE4(sound_id);

  return 0;
}

static int (*Sound_ExIndex[])(void) = {
    FadeOutMusic, PlaySegaSound, SpeedUpMusic, SlowDownMusic, StopAllSound,
};

static int Sound_E0toE4(u8 sound_id) {
  return Sound_ExIndex[sound_id - flg__First]();
}

static int PlaySegaSound(void) {
  set_dac_sample(0x88);
  return 1;
}

static int Sound_PlayBGM(u8 sound_id) {
  u8 *sound_base, *sound_p;

  u8 *voice_ptr;

  u8 tempo;

  u8 number_of_tracks;
  u8 dividing_timing;

  u8 duration;

  size_t i;
  SoundDriverTrack *sfx_track;

  if (sound_id == bgm_ExtraLife) {
    SoundDriverTrack *track;

    if (v_snddriver_ram.state.f_1up_playing)
      return 1;
    v_snddriver_ram.state.f_1up_playing = 0x80;

    /* Clear sfx is overriding bit */
    track = &v_snddriver_ram.state.v_music_dac_track[0];
    for (i = 0; i < SOUND_DRIVER_NUM_MUSIC_TRACKS; i++, track++)
      track->PlaybackControl &= ~PLAYBACKCONTROL_SFX_OVERRIDE;

    /* Stop sfx */
    track = &v_snddriver_ram.v_sfx_fm3_track[0];
    for (i = 0; i < SOUND_DRIVER_NUM_SFX_TRACKS; i++, track++)
      track->PlaybackControl &= ~PLAYBACKCONTROL_PLAYING;

    v_snddriver_ram.state.v_sndprio = 0;

    /* Store driver state for later */
    memcpy(&v_snddriver_ram.state_1up, &v_snddriver_ram.state,
           sizeof(SoundDriverState));

    v_snddriver_ram.state.f_1up_playing = 0x80;
    v_snddriver_ram.state.v_sndprio = 0;
  } else {
    /* Interrupt 1up */
    v_snddriver_ram.state.f_1up_playing = 0;
    v_snddriver_ram.state.v_fadein_counter = 0;
  }

  InitMusicPlayback();

  v_snddriver_ram.state.v_speeduptempo = SpeedUpIndex[sound_id - bgm__First];

  // sound_p = (u8*)MusicIndex[sound_id - bgm__First];
  sound_p =
      (u8 *)(&smps_rom_ptr[read_32(0x71A9C + (sound_id - bgm__First) * 4)]);

  voice_ptr = sound_p + (((u16)sound_p[0] << 8) | sound_p[1]);
  v_snddriver_ram.state.v_voice_ptr = voice_ptr;

  tempo = sound_p[5];
  v_snddriver_ram.state.v_tempo_mod = tempo;
  v_snddriver_ram.state.v_main_tempo_divisor = sound_p[4];

  if (v_snddriver_ram.state.f_speedup)
    tempo = v_snddriver_ram.state.v_speeduptempo;

  v_snddriver_ram.state.v_main_tempo = tempo;
  v_snddriver_ram.state.v_main_tempo_timeout = tempo;

  sound_base = sound_p;
  sound_p += 6; /* Skip past header */

#ifdef SONIC1C_FIX_MAJOR_UB
  /* Otherwise psg might have these uninitialized */
  dividing_timing = sound_base[4];

  duration = 1;
#endif

  /* Load FM tracks */
  number_of_tracks = sound_base[2];
  if (number_of_tracks != 0) {
    u8 amsfms;

    SoundDriverTrack *track;

    u8 *init_p;

    number_of_tracks--;

    amsfms = 0xC0;

    dividing_timing = sound_base[4];

    duration = 1;

    track = &v_snddriver_ram.state.v_music_dac_track[0];
    init_p = FMDACInitBytes;

    do {
      track->PlaybackControl |= PLAYBACKCONTROL_PLAYING;
      track->VoiceControl = *init_p++;

      track->TempoDivider = dividing_timing;
      track->u.fm.StackPointer = sizeof(SoundDriverTrack);
      track->u.fm.AMSFMSPan = amsfms;
      track->u.fm.DurationTimeout = duration;

      track->DataPointer = sound_base + (((u16)sound_p[0] << 8) | sound_p[1]);
      sound_p += 2;

      track->u.fm.Transpose = *sound_p++;
      track->u.fm.Volume = *sound_p++;

      track++;
    } while (number_of_tracks-- > 0);

    /* Are 7 fm tracks defined? */
    if (sound_base[2] == 7) {
      /* Disable DAC */
      WriteFMI(0x2B, 0);
    } else {
      /* Key on/off register */
      /* Note off on all operators of channel 6 */
      WriteFMI(0x28, 6);
      /* TL for operator 1 of FM6 to total silence */
      WriteFMI(0x42, 0x7F);
      /* TL for operator 3 of FM6 to total silence */
      WriteFMI(0x4A, 0x7F);
      /* TL for operator 2 of FM6 to total silence */
      WriteFMI(0x46, 0x7F);
      /* TL for operator 4 of FM6 to total silence */
      WriteFMI(0x4E, 0x7F);
      /* AMS/FMS/panning of FM6 */
      /* Stereo */
      WriteFMI(0xB6, 0xC0);
    }
  }

  /* Load PSG tracks */
  number_of_tracks = sound_base[3];
  if (number_of_tracks != 0) {
    SoundDriverTrack *track;

    u8 *init_p;

    number_of_tracks--;

    track = &v_snddriver_ram.state.v_music_psg1_track[0];
    init_p = PSGInitBytes;

    do {
      track->PlaybackControl |= PLAYBACKCONTROL_PLAYING;
      track->VoiceControl = *init_p++;

      track->TempoDivider = dividing_timing;
      track->u.psg.StackPointer = sizeof(SoundDriverTrack);
      track->u.psg.DurationTimeout = duration;

      track->DataPointer = sound_base + (((u16)sound_p[0] << 8) | sound_p[1]);
      sound_p += 2;

      track->u.psg.Transpose = *sound_p++;
      track->u.psg.Volume = *sound_p++;

      sound_p++;

      track->u.psg.VoiceIndex = *sound_p++;

      track++;
    } while (number_of_tracks-- > 0);
  }

  sfx_track = &v_snddriver_ram.v_sfx_fm3_track[0];
  for (i = 0; i < SOUND_DRIVER_NUM_SFX_TRACKS; i++, sfx_track++) {
    u8 index;

    SoundDriverTrack *bgm_track;

    /* Is track not playing? */
    if (!(sfx_track->PlaybackControl & PLAYBACKCONTROL_PLAYING))
      continue;

    index = sfx_track->VoiceControl;

    if (!(index & VOICECONTROL_IS_PSG))
      index -= 2;
    else
      index >>= (3 + 2);

    bgm_track = SFX_BGMChannelRAM[index];
    /* Set sfx is overriding bit */
    bgm_track->PlaybackControl |= PLAYBACKCONTROL_SFX_OVERRIDE;
  }

  /* Check special sfx overrides */
  if (v_snddriver_ram.v_spcsfx_fm4_track[0].PlaybackControl &
      PLAYBACKCONTROL_PLAYING)
    v_snddriver_ram.state.v_music_fm1_track[4 - 1].PlaybackControl |=
        PLAYBACKCONTROL_SFX_OVERRIDE;
  if (v_snddriver_ram.v_spcsfx_psg3_track[0].PlaybackControl &
      PLAYBACKCONTROL_PLAYING)
    v_snddriver_ram.state.v_music_psg1_track[3 - 1].PlaybackControl |=
        PLAYBACKCONTROL_SFX_OVERRIDE;

  /* Send note offs */
  {
    SoundDriverTrack *track;

    track = &v_snddriver_ram.state.v_music_fm1_track[0];
    for (i = 0; i < SOUND_DRIVER_NUM_MUSIC_FM_TRACKS; i++, track++)
      FMNoteOff(track);

    track = &v_snddriver_ram.state.v_music_psg1_track[0];
    for (i = 0; i < SOUND_DRIVER_NUM_MUSIC_PSG_TRACKS; i++, track++)
      PSGNoteOff(track);
  }

  return 1;
}

static u8 FMDACInitBytes[SOUND_DRIVER_NUM_MUSIC_DAC_TRACKS +
                         SOUND_DRIVER_NUM_MUSIC_FM_TRACKS] = {
    /* first byte is for DAC; then notice the 0, 1, 2 then 4, 5, 6; this is the
       gap between parts I and II for YM2612 port writes */
    6, 0, 1, 2, 4, 5, 6};

static u8 PSGInitBytes[SOUND_DRIVER_NUM_MUSIC_PSG_TRACKS] = {
    /* Specifically, these configure writes to the PSG port for each channel */
    0x80, 0xA0, 0xC0};

static void Sound_PlaySFX(u8 sound_id) {
  u8 *sound_base, *sound_p;

  u8 *voice_ptr;

  u8 dividing_timing;
  u8 number_of_tracks;

  u8 voice_control;

  if (v_snddriver_ram.state.f_1up_playing)
    return;
  if (v_snddriver_ram.state.v_fadeout_counter)
    return;
  if (v_snddriver_ram.state.f_fadein_flag)
    return;

  if (sound_id == sfx_Ring) {
    if (v_snddriver_ram.state.v_ring_speaker)
      sound_id = sfx_RingLeft;
    v_snddriver_ram.state.v_ring_speaker ^= 1;
  }

  if (sound_id == sfx_Push) {
    if (v_snddriver_ram.state.f_push_playing)
      return;
    v_snddriver_ram.state.f_push_playing = 0x80;
  }

  // sound_p = (u8*)SoundIndex[sound_id - sfx__First];
  sound_p =
      (u8 *)(&smps_rom_ptr[read_32(0x78B44 + (sound_id - sfx__First) * 4)]);
  sound_base = sound_p;

  voice_ptr = sound_base + (((u16)sound_p[0] << 8) | sound_p[1]);
  sound_p += 2;

  dividing_timing = *sound_p++;

  number_of_tracks = *sound_p++ - 1;

  do {
    SoundDriverTrack *track;
    u16 index;

    voice_control = sound_p[1];

    /* Is voice not PSG? */
    if (!(voice_control & VOICECONTROL_IS_PSG)) {
      /* - 2 because SFX can only have FM3 or up */
      index = voice_control - 2;
      track = SFX_BGMChannelRAM[index];
      track->PlaybackControl |= PLAYBACKCONTROL_SFX_OVERRIDE;
    } else {
      index = voice_control >> (3 + 2);
      track = SFX_BGMChannelRAM[index];
      track->PlaybackControl |= PLAYBACKCONTROL_SFX_OVERRIDE;

      /* Is this PSG 3? */
      if (voice_control == 0xC0) {
        /* Silence PSG 3 and noise */
        write_psg(voice_control | 0x1F);
        write_psg((voice_control | 0x1F) ^ (1 << 5));
      }
    }

    track = SFX_SFXChannelRAM[index];

    memset(track, 0, sizeof(SoundDriverTrack));

    track->PlaybackControl = *sound_p++;
    track->VoiceControl = *sound_p++;

    track->TempoDivider = dividing_timing;

    track->DataPointer = sound_base + (((u16)sound_p[0] << 8) | sound_p[1]);
    sound_p += 2;

    track->u.fm.Transpose = *sound_p++;
    track->u.fm.Volume = *sound_p++;

    track->u.fm.DurationTimeout = 1;

    track->u.fm.StackPointer = sizeof(SoundDriverTrack);

    if (!(voice_control & VOICECONTROL_IS_PSG)) {
      track->u.fm.AMSFMSPan = 0xC0;
      track->u.fm.VoicePtr = voice_ptr;
    }
  } while (number_of_tracks-- > 0);

  /* Check special sfx override */
  if (v_snddriver_ram.v_sfx_fm3_track[4 - 3].PlaybackControl &
      PLAYBACKCONTROL_PLAYING)
    v_snddriver_ram.v_spcsfx_fm4_track[4 - 4].PlaybackControl |=
        PLAYBACKCONTROL_SFX_OVERRIDE;

  if (v_snddriver_ram.v_sfx_psg1_track[3 - 1].PlaybackControl &
      PLAYBACKCONTROL_PLAYING)
    v_snddriver_ram.v_spcsfx_psg3_track[3 - 3].PlaybackControl |=
        PLAYBACKCONTROL_SFX_OVERRIDE;
}

static SoundDriverTrack *SFX_BGMChannelRAM[8] = {
    &v_snddriver_ram.state.v_music_fm1_track[3 - 1],
    NULL,
    &v_snddriver_ram.state.v_music_fm1_track[4 - 1],
    &v_snddriver_ram.state.v_music_fm1_track[5 - 1],

    &v_snddriver_ram.state.v_music_psg1_track[1 - 1],
    &v_snddriver_ram.state.v_music_psg1_track[2 - 1],
    &v_snddriver_ram.state.v_music_psg1_track[3 - 1],
    &v_snddriver_ram.state.v_music_psg1_track[3 - 1]};

static SoundDriverTrack *SFX_SFXChannelRAM[8] = {
    &v_snddriver_ram.v_sfx_fm3_track[3 - 3],
    NULL,
    &v_snddriver_ram.v_sfx_fm3_track[4 - 3],
    &v_snddriver_ram.v_sfx_fm3_track[5 - 3],

    &v_snddriver_ram.v_sfx_psg1_track[1 - 1],
    &v_snddriver_ram.v_sfx_psg1_track[2 - 1],
    &v_snddriver_ram.v_sfx_psg1_track[3 - 1],
    &v_snddriver_ram.v_sfx_psg1_track[3 - 1]};

static void Sound_PlaySpecial(u8 sound_id) {
  u8 *sound_base, *sound_p;

  u8 dividing_timing;
  u8 number_of_tracks;

  u8 voice_control;

  if (v_snddriver_ram.state.f_1up_playing)
    return;
  if (v_snddriver_ram.state.v_fadeout_counter)
    return;
  if (v_snddriver_ram.state.f_fadein_flag)
    return;

  // sound_p = (u8*)SpecSoundIndex[sound_id - 0xD0];
  sound_p = (u8 *)(&smps_rom_ptr[read_32(0x78C04 + (sound_id - 0xd0) * 4)]);
  sound_base = sound_p;

  v_snddriver_ram.state.v_special_voice_ptr =
      sound_base + (((u16)sound_p[0] << 8) | sound_p[1]);
  sound_p += 2;

  dividing_timing = *sound_p++;

  number_of_tracks = *sound_p++ - 1;

  do {
    SoundDriverTrack *track;

    voice_control = sound_p[1];

    if (!(voice_control & VOICECONTROL_IS_PSG)) {
      v_snddriver_ram.state.v_music_fm1_track[4 - 1].PlaybackControl |=
          PLAYBACKCONTROL_SFX_OVERRIDE;
      track = &v_snddriver_ram.v_spcsfx_fm4_track[4 - 4];
    } else {
      /* Set SFX is overriding bit */
      v_snddriver_ram.state.v_music_psg1_track[3 - 1].PlaybackControl |=
          PLAYBACKCONTROL_SFX_OVERRIDE;
      track = &v_snddriver_ram.v_spcsfx_psg3_track[3 - 3];
    }

    memset(track, 0, sizeof(SoundDriverTrack));

    track->PlaybackControl = *sound_p++;
    track->VoiceControl = *sound_p++;

    track->TempoDivider = dividing_timing;

    track->DataPointer = sound_base + (((u16)sound_p[0] << 8) | sound_p[1]);
    sound_p += 2;

    track->u.fm.Transpose = *sound_p++;
    track->u.fm.Volume = *sound_p++;

    track->u.fm.DurationTimeout = 1;

    track->u.fm.StackPointer = sizeof(SoundDriverTrack);

    if (!(voice_control & (1 << 7)))
      track->u.fm.AMSFMSPan = 0xC0;
  } while (number_of_tracks-- > 0);

  if (v_snddriver_ram.v_sfx_fm3_track[4 - 3].PlaybackControl &
      PLAYBACKCONTROL_PLAYING)
    v_snddriver_ram.v_spcsfx_fm4_track[4 - 4].PlaybackControl |=
        PLAYBACKCONTROL_SFX_OVERRIDE;

  if (v_snddriver_ram.v_sfx_psg1_track[3 - 1].PlaybackControl &
      PLAYBACKCONTROL_PLAYING) {
    v_snddriver_ram.v_spcsfx_psg3_track[3 - 3].PlaybackControl |=
        PLAYBACKCONTROL_SFX_OVERRIDE;

    /* Silence PSG 3 and noise */
    write_psg(voice_control | 0x1F);
    write_psg((voice_control | 0x1F) ^ (1 << 5));
  }
}

/*
static SoundDriverTrack *SpecSFX_BGMChannelRAM[2] = {
        &v_snddriver_ram.state.v_music_fm1_track[4 - 1],
        &v_snddriver_ram.state.v_music_psg1_track[3 - 1]
};

static SoundDriverTrack *SpecSFX_SFXChannelRAM[2] = {
        &v_snddriver_ram.v_sfx_fm3_track[4 - 3],
        &v_snddriver_ram.v_sfx_psg1_track[3 - 1]
};

static SoundDriverTrack *SpecSFX_SpecSFXChannelRAM[2] = {
        &v_snddriver_ram.v_spcsfx_fm4_track[4 - 4],
        &v_snddriver_ram.v_spcsfx_psg3_track[3 - 3]
};
*/

static void StopSFX(void) {
  size_t i;

  SoundDriverTrack *track;

  track = &v_snddriver_ram.v_sfx_fm3_track[0];
  for (i = 0; i < SOUND_DRIVER_NUM_SFX_TRACKS; i++, track++) {
    u8 voice;
    u8 *voice_ptr;

    /* Is track not playing? */
    if (!(track->PlaybackControl & PLAYBACKCONTROL_PLAYING))
      continue;

    track->PlaybackControl &= ~PLAYBACKCONTROL_PLAYING;

    /* Is track not PSG? */
    voice = track->VoiceControl;

    if (!(voice & VOICECONTROL_IS_PSG)) {
      SoundDriverTrack *old_track;

      FMNoteOff(track);

      /* Is this the special sfx FM4 track? */
      if (voice == 4 && (v_snddriver_ram.v_spcsfx_fm4_track[0].PlaybackControl &
                         PLAYBACKCONTROL_PLAYING)) {
#ifdef SONIC1C_FIX_MAJOR_UB
        /* Original code doesn't do this, causing an uninitialized variable use
         */
        old_track = track;
#endif
        voice_ptr = v_snddriver_ram.v_spcsfx_fm4_track[0].u.fm.VoicePtr;
      } else {
        /* - 2 because SFX only has FM3 and up */
        old_track = track;
        track = SFX_BGMChannelRAM[voice - 2];
        voice_ptr = v_snddriver_ram.state.v_voice_ptr;
      }

      /* Clear sfx override flag */
      track->PlaybackControl &= ~PLAYBACKCONTROL_SFX_OVERRIDE;
      /* Set track at rest bit */
      track->PlaybackControl |= PLAYBACKCONTROL_AT_REST;

      SetVoice(track, track->u.fm.VoiceIndex, voice_ptr);
      track = old_track;
    } else {
      SoundDriverTrack *voice_track;

      PSGNoteOff(track);

#ifdef SONIC1C_FIX_BUGS
      if ((v_snddriver_ram.v_spcsfx_psg3_track[0].PlaybackControl &
           PLAYBACKCONTROL_PLAYING) &&
          (voice == 0xE0 || voice == 0xC0))
#else
      if (voice == 0xE0 || voice == 0xC0)
#endif
      {
        voice_track = &v_snddriver_ram.v_spcsfx_psg3_track[0];
      } else {
        voice_track = SFX_BGMChannelRAM[voice >> (3 + 2)];
      }

      voice_track->PlaybackControl &= ~PLAYBACKCONTROL_SFX_OVERRIDE;
      voice_track->PlaybackControl |= PLAYBACKCONTROL_AT_REST;

      if (voice_track->VoiceControl == 0xE0)
        write_psg(voice_track->u.psg.PSGNoise);
    }
  }
}

static void StopSpecialSFX(void) {
  SoundDriverTrack *track;

  /* Is FM4 track playing? */
  track = &v_snddriver_ram.v_spcsfx_fm4_track[0];

  if (track->PlaybackControl & PLAYBACKCONTROL_PLAYING) {
    track->PlaybackControl &= ~PLAYBACKCONTROL_PLAYING;

    /* Is SFX not overriding? */
    if (!(track->PlaybackControl & PLAYBACKCONTROL_SFX_OVERRIDE)) {
      SendFMNoteOff(track);

      /* Release music track */
      track = &v_snddriver_ram.state.v_music_fm1_track[4 - 1];

      track->PlaybackControl &= ~PLAYBACKCONTROL_SFX_OVERRIDE;
      track->PlaybackControl |= PLAYBACKCONTROL_AT_REST;

      /* Is track playing? */
      if (track->PlaybackControl & PLAYBACKCONTROL_PLAYING)
        SetVoice(track, track->u.fm.VoiceIndex,
                 v_snddriver_ram.state.v_voice_ptr);
    }
  }

  /* Is PSG3 track playing? */
  track = &v_snddriver_ram.v_spcsfx_psg3_track[0];

  if (track->PlaybackControl & PLAYBACKCONTROL_PLAYING) {
    track->PlaybackControl &= ~PLAYBACKCONTROL_PLAYING;

    /* Is SFX not overriding? */
    if (!(track->PlaybackControl & PLAYBACKCONTROL_SFX_OVERRIDE)) {
      SendPSGNoteOff(track);

      /* Release music track */
      track = &v_snddriver_ram.state.v_music_psg1_track[3 - 1];

      track->PlaybackControl &= ~PLAYBACKCONTROL_SFX_OVERRIDE;
      track->PlaybackControl |= PLAYBACKCONTROL_AT_REST;

      /* Is track playing? */
      if ((track->PlaybackControl & PLAYBACKCONTROL_PLAYING) &&
          track->VoiceControl == 0xE0)
        write_psg(track->u.psg.PSGNoise);
    }
  }
}

static int FadeOutMusic(void) {
  StopSFX();
  StopSpecialSFX();

  v_snddriver_ram.state.v_fadeout_delay = 3;
  v_snddriver_ram.state.v_fadeout_counter = 0x28;
  v_snddriver_ram.state.v_music_dac_track[0].PlaybackControl = 0;
  v_snddriver_ram.state.f_speedup = 0;

  return 0;
}

static void DoFadeOut(void) {
  size_t i;

  SoundDriverTrack *track;

  if (v_snddriver_ram.state.v_fadeout_delay) {
    v_snddriver_ram.state.v_fadeout_delay--;
    return;
  }

  if (--v_snddriver_ram.state.v_fadeout_counter == 0) {
    StopAllSound();
    return;
  }

  v_snddriver_ram.state.v_fadeout_delay = 3;

  track = &v_snddriver_ram.state.v_music_fm1_track[0];
  for (i = 0; i < SOUND_DRIVER_NUM_MUSIC_FM_TRACKS; i++, track++) {
    /* Is track not playing */
    if (!(track->PlaybackControl & PLAYBACKCONTROL_PLAYING))
      continue;

    if (++track->u.fm.Volume >= 0x80) {
      track->PlaybackControl &= ~PLAYBACKCONTROL_PLAYING;
      continue;
    }

    SendVoiceTL(track);
  }

  track = &v_snddriver_ram.state.v_music_psg1_track[0];
  for (i = 0; i < SOUND_DRIVER_NUM_MUSIC_PSG_TRACKS; i++, track++) {
    /* Is track not playing */
    if (!(track->PlaybackControl & PLAYBACKCONTROL_PLAYING))
      continue;

    if (++track->u.psg.Volume >= 0x10) {
      track->PlaybackControl &= ~PLAYBACKCONTROL_PLAYING;
      continue;
    }

    SetPSGVolume(track, track->u.psg.Volume);
  }
}

static void FMSilenceAll(void) {
  int i;

  u8 fm_addr;

  for (i = 3 - 1; i >= 0; i--) {
    /* FM key on/off register */
    WriteFMI(0x28, (u8)i);
    WriteFMI(0x28, (u8)i + 4);
  }

  fm_addr = 0x40; /* Set TL on FM channels... */

  for (i = 0; i < 3; i++) {
    int j;
    for (j = 0; j < 4; j++) {
      WriteFMI(fm_addr, 0x7F);
      WriteFMII(fm_addr, 0x7F);
      fm_addr += 4; /* Next TL operator */
    }
    fm_addr -= 16 - 1; /* Move to TL operator 1 of next channel*/
  }
}

static int StopAllSound(void) {
  /* Set Enable/disable DAC */
  /* Enable DAC */
  WriteFMI(0x2B, 0x80);

  /* Set Timers, FM3/FM6 mode */
  /* FM3/FM6 normal mode, disable timers */
  WriteFMI(0x27, 0x00);

#ifdef SONIC1C_FIX_BUGS
  memset(&v_snddriver_ram, 0, offsetof(SoundDriverRAM, state_1up));
#else
  /* DANGER! This should be clearing all variables and track data, but misses
   * the last $10 bytes of v_spcsfx_psg3_track. */
  memset(&v_snddriver_ram, 0, offsetof(SoundDriverRAM, state_1up) - 0x10);
#endif

  v_snddriver_ram.state.v_sound_id = 0x80; /* Silence */
  FMSilenceAll();
  PSGSilenceAll();

  return 0;
}

static void InitMusicPlayback(void) {
  u8 save_sndprio;
  u8 save_1up_playing;
  u8 save_speedup;
  u8 save_fadein_counter;
  u8 save_soundqueue[SOUND_DRIVER_NUM_SOUND_QUEUES];

  save_sndprio = v_snddriver_ram.state.v_sndprio;
  save_1up_playing = v_snddriver_ram.state.f_1up_playing;
  save_speedup = v_snddriver_ram.state.f_speedup;
  save_fadein_counter = v_snddriver_ram.state.v_fadein_counter;
  save_soundqueue[0] = v_snddriver_ram.state.v_soundqueue[0];
  save_soundqueue[1] = v_snddriver_ram.state.v_soundqueue[1];
#ifdef SONIC1C_FIX_BUGS
  save_soundqueue[2] = v_snddriver_ram.state.v_soundqueue[2];
#endif

  memset(&v_snddriver_ram.state, 0, sizeof(v_snddriver_ram.state));

  v_snddriver_ram.state.v_sndprio = save_sndprio;
  v_snddriver_ram.state.f_1up_playing = save_1up_playing;
  v_snddriver_ram.state.f_speedup = save_speedup;
  v_snddriver_ram.state.v_fadein_counter = save_fadein_counter;
  v_snddriver_ram.state.v_soundqueue[0] = save_soundqueue[0];
  v_snddriver_ram.state.v_soundqueue[1] = save_soundqueue[1];
#ifdef SONIC1C_FIX_BUGS
  v_snddriver_ram.state.v_soundqueue[2] = save_soundqueue[2];
#endif

  v_snddriver_ram.state.v_sound_id = 0x80; /* Silence */

#ifdef SONIC1C_FIX_BUGS
  {
    int i;

    SoundDriverTrack *track;
    u8 *init_bytes;

    track = &v_snddriver_ram.state.v_music_dac_track[0];
    init_bytes = &FMDACInitBytes[0];

    for (i = 0; i < SOUND_DRIVER_NUM_MUSIC_DAC_TRACKS +
                        SOUND_DRIVER_NUM_MUSIC_FM_TRACKS;
         i++, track++)
      track->VoiceControl = *init_bytes++;

    init_bytes = &PSGInitBytes[0];

    for (i = 0; i < SOUND_DRIVER_NUM_MUSIC_PSG_TRACKS; i++, track++)
      track->VoiceControl = *init_bytes++;
  }
#else
  /*
  ; DANGER! This silences ALL channels, even the ones being used
  ; by SFX, and not music! .sendfmnoteoff does this already, and
  ; doesn't affect SFX channels, either.
  ; DANGER! InitMusicPlayback, and Sound_PlayBGM for that matter,
  ; don't do a very good job of setting up the music tracks.
  ; Tracks that aren't defined in a music file's header don't have
  ; their channels defined, meaning .sendfmnoteoff won't silence
  ; hardware properly. In combination with removing the above
  ; calls to FMSilenceAll/PSGSilenceAll, this will cause hanging
  ; notes.
  */
  FMSilenceAll();
  PSGSilenceAll();
#endif
}

static void TempoWait(void) {
  size_t i;
  SoundDriverTrack *track;

  /* Reset main tempo timeout */
  v_snddriver_ram.state.v_main_tempo_timeout =
      v_snddriver_ram.state.v_main_tempo;

  track = &v_snddriver_ram.state.v_music_dac_track[0];
  for (i = 0; i < SOUND_DRIVER_NUM_MUSIC_TRACKS; i++, track++) {
    /* Delay note by 1 frame */
    track->u.fm.DurationTimeout++;
  }
}

static int SpeedUpMusic(void) {
  if (!v_snddriver_ram.state.f_1up_playing) {
    v_snddriver_ram.state.v_main_tempo = v_snddriver_ram.state.v_speeduptempo;
    v_snddriver_ram.state.v_main_tempo_timeout =
        v_snddriver_ram.state.v_speeduptempo;
    v_snddriver_ram.state.f_speedup = 0x80;
  } else {
    v_snddriver_ram.state_1up.v_main_tempo =
        v_snddriver_ram.state_1up.v_speeduptempo;
    v_snddriver_ram.state_1up.v_main_tempo_timeout =
        v_snddriver_ram.state_1up.v_speeduptempo;
    v_snddriver_ram.state_1up.f_speedup = 0x80;
  }

  return 0;
}

static int SlowDownMusic(void) {
  if (!v_snddriver_ram.state.f_1up_playing) {
    v_snddriver_ram.state.v_main_tempo = v_snddriver_ram.state.v_tempo_mod;
    v_snddriver_ram.state.v_main_tempo_timeout =
        v_snddriver_ram.state.v_tempo_mod;
    v_snddriver_ram.state.f_speedup = 0x00;
  } else {
    v_snddriver_ram.state_1up.v_main_tempo =
        v_snddriver_ram.state_1up.v_tempo_mod;
    v_snddriver_ram.state_1up.v_main_tempo_timeout =
        v_snddriver_ram.state_1up.v_tempo_mod;
    v_snddriver_ram.state_1up.f_speedup = 0x00;
  }

  return 0;
}

static void DoFadeIn(void) {
  /* Has fadein delay expired? */
  if (v_snddriver_ram.state.v_fadein_delay) {
    v_snddriver_ram.state.v_fadein_delay--;
    return;
  }

  /* Is fade not done? */
  if (v_snddriver_ram.state.v_fadein_counter) {
    size_t i;

    SoundDriverTrack *track;

    v_snddriver_ram.state.v_fadein_counter--;
    v_snddriver_ram.state.v_fadein_delay = 2;

    track = &v_snddriver_ram.state.v_music_fm1_track[0];
    for (i = 0; i < SOUND_DRIVER_NUM_MUSIC_FM_TRACKS; i++, track++) {
      /* Is track not playing? */
      if (!(track->PlaybackControl & PLAYBACKCONTROL_PLAYING))
        continue;

      /* Reduce volume attenuation */
      track->u.fm.Volume--;
      SendVoiceTL(track);
    }

    track = &v_snddriver_ram.state.v_music_psg1_track[0];
    for (i = 0; i < SOUND_DRIVER_NUM_MUSIC_PSG_TRACKS; i++, track++) {
      u8 volume;

      /* Is track not playing? */
      if (!(track->PlaybackControl & PLAYBACKCONTROL_PLAYING))
        continue;

      /* Reduce volume attenuation */
      track->u.psg.Volume--;

      volume = track->u.psg.Volume;
      if (volume >= 0x10)
        volume = 0xF;

      SetPSGVolume(track, volume);
    }
  } else {
    v_snddriver_ram.state.v_music_dac_track[0].PlaybackControl &=
        ~PLAYBACKCONTROL_SFX_OVERRIDE;

    v_snddriver_ram.state.f_fadein_flag = 0;
  }
}

static void FMNoteOn(SoundDriverTrack *track) {
  if (track->PlaybackControl & PLAYBACKCONTROL_AT_REST)
    return;
  if (track->PlaybackControl & PLAYBACKCONTROL_SFX_OVERRIDE)
    return;

  /* Note on/off register */
  WriteFMI(0x28, track->VoiceControl | 0xF0);
}

static void FMNoteOff(SoundDriverTrack *track) {
  if (track->PlaybackControl & PLAYBACKCONTROL_DO_NOT_ATTACK_NEXT)
    return;
  if (track->PlaybackControl & PLAYBACKCONTROL_SFX_OVERRIDE)
    return;

  SendFMNoteOff(track);
}

static void SendFMNoteOff(SoundDriverTrack *track) {
  /* Note on/off register */
  WriteFMI(0x28, track->VoiceControl);
}

/* YM2612 register writes */
static void WriteFMIorIIMain(SoundDriverTrack *track, u8 addr, u8 data) {
  if (track->PlaybackControl & PLAYBACKCONTROL_SFX_OVERRIDE)
    return;
  WriteFMIorII(track, addr, data);
}

static void WriteFMIorII(SoundDriverTrack *track, u8 addr, u8 data) {
  if ((track->VoiceControl & VOICECONTROL_IS_FM2)) {
    WriteFMIIPart(track, addr, data);
  } else {
    addr += track->VoiceControl;
    WriteFMI(addr, data);
  }
}

static void WriteFMI(u8 addr, u8 data) { write_fm_i(addr, data); }

static void WriteFMIIPart(SoundDriverTrack *track, u8 addr, u8 data) {
  u8 voice;
  voice = track->VoiceControl;
  voice &= ~VOICECONTROL_IS_FM2;

  WriteFMII(addr + voice, data);
}

static void WriteFMII(u8 addr, u8 data) { write_fm_ii(addr, data); }

#define MakeFMFrequency(frequency)                                             \
  ((s16)((double)frequency * 1024 * 1024 * 2 / FM_Sample_Rate))
#define MakeFMFrequenciesOctave(octave)                                        \
  MakeFMFrequency(15.39) + octave * 0x800,                                     \
      MakeFMFrequency(16.35) + octave * 0x800,                                 \
      MakeFMFrequency(17.34) + octave * 0x800,                                 \
      MakeFMFrequency(18.36) + octave * 0x800,                                 \
      MakeFMFrequency(19.45) + octave * 0x800,                                 \
      MakeFMFrequency(20.64) + octave * 0x800,                                 \
      MakeFMFrequency(21.84) + octave * 0x800,                                 \
      MakeFMFrequency(23.13) + octave * 0x800,                                 \
      MakeFMFrequency(24.51) + octave * 0x800,                                 \
      MakeFMFrequency(25.98) + octave * 0x800,                                 \
      MakeFMFrequency(27.53) + octave * 0x800,                                 \
      MakeFMFrequency(29.15) + octave * 0x800

static s16 FMFrequencies[8 * 12] = {
    MakeFMFrequenciesOctave(0), MakeFMFrequenciesOctave(1),
    MakeFMFrequenciesOctave(2), MakeFMFrequenciesOctave(3),
    MakeFMFrequenciesOctave(4), MakeFMFrequenciesOctave(5),
    MakeFMFrequenciesOctave(6), MakeFMFrequenciesOctave(7)};

#undef MakeFMFrequency
#undef MakeFMFrequenciesOctave

static int PSGUpdateTrack(SoundDriverTrack *track) {
  if (!--track->u.psg.DurationTimeout) {
    track->PlaybackControl &= ~PLAYBACKCONTROL_DO_NOT_ATTACK_NEXT;
    if (PSGDoNext(track))
      return 1;
    PSGDoNoteOn(track);
    PSGDoVolFX(track);
  } else {
    s16 freq;

    if (NoteTimeoutUpdate(track))
      return 0;
    PSGUpdateVolFX(track);
    if (DoModulation(track, &freq))
      return 0;
    PSGUpdateFreq(track, freq);
  }
  return 0;
}

static int PSGDoNext(SoundDriverTrack *track) {
  u8 *data_p;

  u8 unit;

  track->PlaybackControl &= ~PLAYBACKCONTROL_AT_REST;

  data_p = track->DataPointer;

  /* Read next SMPS unit */
  while (1) {
    unit = *data_p++;
    if (unit < 0xE0)
      break;
    if (CoordFlag(track, &data_p, unit))
      return 1;
  }

  /* If the unit is a note */
  if (unit & 0x80) {
    PSGSetFreq(track, data_p, unit);

    unit = *data_p++;

    if (unit & 0x80) {
      data_p--;
      FinishTrackUpdate(track, data_p);
      return 0;
    }
  }

  SetDuration(track, unit);
  FinishTrackUpdate(track, data_p);
  return 0;
}

static void PSGSetFreq(SoundDriverTrack *track, u8 *data_p, u8 note) {
  if (note >= 0x81) {
    note -= 0x81;

    note = (note + track->u.psg.Transpose) & 0x7F;

    track->u.psg.Freq = PSGFrequencies[note];
    FinishTrackUpdate(track, data_p);
  } else {
    track->PlaybackControl |= PLAYBACKCONTROL_AT_REST;
    track->u.psg.Freq = -1;
    FinishTrackUpdate(track, data_p);
    PSGNoteOff(track);
  }
}

static void PSGDoNoteOn(SoundDriverTrack *track) {
  s16 freq;

  freq = track->u.psg.Freq;
  if (freq < 0) {
    PSGSetRest(track);
    return;
  }

  PSGUpdateFreq(track, freq);
}

static void PSGUpdateFreq(SoundDriverTrack *track, s16 freq) {
  u8 voice;

  freq += (s8)track->u.psg.Detune;

  if (track->PlaybackControl & PLAYBACKCONTROL_SFX_OVERRIDE)
    return;
  if (track->PlaybackControl & PLAYBACKCONTROL_AT_REST)
    return;

  voice = track->VoiceControl;

  if (voice == 0xE0)
    voice = 0xC0;

  write_psg(voice | (freq & 0xF));
  write_psg((freq >> 4) & 0x3F);
}

static void PSGSetRest(SoundDriverTrack *track) {
  track->PlaybackControl |= PLAYBACKCONTROL_AT_REST;
}

static void PSGUpdateVolFX(SoundDriverTrack *track) {
  if (!track->u.psg.VoiceIndex)
    return;
  PSGDoVolFX(track);
}

static void PSGDoVolFX(SoundDriverTrack *track) {
  u8 volume;
  u8 voice_index;

  s8 *psg_p;
  s8 psg_v;

  volume = track->u.psg.Volume;
  voice_index = track->u.psg.VoiceIndex;

  if (voice_index == 0) {
    SetPSGVolume(track, volume);
    return;
  }

  // psg_p = (s8*)PSG_Index[voice_index - 1];
  psg_p = (s8 *)(&smps_rom_ptr[read_32(0x719A8 + (voice_index - 1) * 4)]);
  psg_v = psg_p[track->u.psg.VolEnvIndex++];

  if (psg_v < 0) {
    if (psg_v == -0x80) {
      VolEnvHold(track);
      return;
    }
  }

  volume += psg_v;
  if (volume >= 0x10)
    volume = 0xF;

  SetPSGVolume(track, volume);
}

static void SetPSGVolume(SoundDriverTrack *track, u8 volume) {
  if (track->PlaybackControl & PLAYBACKCONTROL_AT_REST)
    return;
  if (track->PlaybackControl & PLAYBACKCONTROL_SFX_OVERRIDE)
    return;
  if (track->PlaybackControl & PLAYBACKCONTROL_DO_NOT_ATTACK_NEXT) {
    PSGCheckNoteTimeout(track, volume);
    return;
  }

  PSGSendVolume(track, volume);
}

static void PSGSendVolume(SoundDriverTrack *track, u8 volume) {
  write_psg((track->VoiceControl | volume) + 0x10);
}

static void PSGCheckNoteTimeout(SoundDriverTrack *track, u8 volume) {
  if (track->u.psg.NoteTimeoutMaster == 0 || track->u.psg.NoteTimeout != 0)
    PSGSendVolume(track, volume);
}

static void VolEnvHold(SoundDriverTrack *track) { track->u.psg.VolEnvIndex--; }

static void PSGNoteOff(SoundDriverTrack *track) {
  /* Is sfx overriding? */
  if (track->PlaybackControl & PLAYBACKCONTROL_SFX_OVERRIDE)
    return;

  SendPSGNoteOff(track);
}

static void SendPSGNoteOff(SoundDriverTrack *track) {
  /* Maximum volume attenuation */
  write_psg(track->VoiceControl | 0x1F);

#ifdef SONIC1C_FIX_BUGS
  /* This is the same fix that S&K's driver uses: */
  if (track->VoiceControl == 0xDF)
    write_psg(0xFF);
#else
  /*
  ; DANGER! If InitMusicPlayback doesn't silence all channels, there's the
  ; risk of music accidentally playing noise because it can't detect if
  ; the PSG4/noise channel needs muting on track initialisation.
  */
#endif
}

static void PSGSilenceAll(void) {
  write_psg(0x9F); /* Silence PSG 1 */
  write_psg(0xBF); /* Silence PSG 2 */
  write_psg(0xDF); /* Silence PSG 3 */
  write_psg(0xFF); /* Silence noise channel */
}

#define Fmin(a, b) ((a) < (b) ? (a) : (b))
#define F(frequency)                                                           \
  (Fmin(0x3FF, (s16)((double)PSG_Sample_Rate / ((frequency) * 2))))

static s16 PSGFrequencies[12 * 5 + 10] = {
    F(130.98),  F(138.78),  F(146.99),  F(155.79),   F(165.22),  F(174.78),
    F(185.19),  F(196.24),  F(207.91),  F(220.63),   F(233.52),  F(247.47),
    F(261.96),  F(277.56),  F(293.59),  F(311.58),   F(329.97),  F(349.56),
    F(370.39),  F(392.49),  F(415.83),  F(440.39),   F(468.03),  F(494.95),
    F(522.71),  F(556.51),  F(588.73),  F(621.44),   F(661.89),  F(699.12),
    F(740.79),  F(782.24),  F(828.59),  F(880.79),   F(932.17),  F(989.91),
    F(1045.42), F(1107.52), F(1177.47), F(1242.89),  F(1316.00), F(1398.25),
    F(1491.47), F(1575.50), F(1669.55), F(1747.82),  F(1864.34), F(1962.46),
    F(2071.49), F(2193.34), F(2330.42), F(2485.78),  F(2601.40), F(2796.51),
    F(2943.69), F(3107.23), F(3290.01), F(3495.64),  F(3608.40), F(3857.25),
    F(4142.98), F(4302.32), F(4660.85), F(4863.50),  F(5084.56), F(5326.69),
    F(5887.39), F(6214.47), F(6580.02), F(223721.56)};

#undef F
#undef Fmin

static int CoordFlag(SoundDriverTrack *track, u8 **data, u8 unit) {
  return coordflagLookup[unit - 0xE0](track, data);
}

int (*coordflagLookup[0xFA - 0xE0])(SoundDriverTrack *track,
                                    u8 **data) = {cfPanningAMSFMS,
                                                  cfDetune,
                                                  cfSetCommunication,
                                                  cfJumpReturn,
                                                  cfFadeInToPrevious,
                                                  cfSetTempoDivider,
                                                  cfChangeFMVolume,
                                                  cfHoldNote,
                                                  cfNoteTimeout,
                                                  cfChangeTransposition,
                                                  cfSetTempo,
                                                  cfSetTempoDividerAll,
                                                  cfChangePSGVolume,
                                                  cfClearPush,
                                                  cfStopSpecialFM4,
                                                  cfSetVoice,
                                                  cfModulation,
                                                  cfEnableModulation,
                                                  cfStopTrack,
                                                  cfSetPSGNoise,
                                                  cfDisableModulation,
                                                  cfSetPSGTone,
                                                  cfJumpTo,
                                                  cfRepeatAtPos,
                                                  cfJumpToGosub,
                                                  cfOpF9};

static int cfPanningAMSFMS(SoundDriverTrack *track, u8 **data) {
  u8 new_amsfms;

  new_amsfms = *(*data)++;

  /* Is this a PSG track? */
  if ((track->VoiceControl & VOICECONTROL_IS_PSG))
    return 0;

  new_amsfms |= (track->u.fm.AMSFMSPan & 0x37);

  track->u.fm.AMSFMSPan = new_amsfms;

  WriteFMIorIIMain(track, 0xB4, new_amsfms);

  return 0;
}

static int cfDetune(SoundDriverTrack *track, u8 **data) {
  track->u.fm.Detune = *(*data)++;
  return 0;
}

static int cfSetCommunication(SoundDriverTrack *track, u8 **data) {
  (void)track;

  v_snddriver_ram.state.v_communication_byte = *(*data)++;
  return 0;
}

static int cfJumpReturn(SoundDriverTrack *track, u8 **data) {
  u8 sp;

  (void)track;
  (void)data;

  sp = track->u.fm.StackPointer;

  /* Pop address off the stack*/
  *data = *(u8 **)((u8 *)track + sp);
  *(u8 **)((u8 *)track + sp) = 0;

  *data += 2; /* Skip the command itself */

  track->u.fm.StackPointer = sp + sizeof(u8 *);

  return 0;
}

static int cfFadeInToPrevious(SoundDriverTrack *track, u8 **data) {
  size_t i;

  SoundDriverTrack *music_track;

  u8 volume;

  (void)track;
  (void)data;

  /* Copy 1up state back to main state */
  memcpy(&v_snddriver_ram.state, &v_snddriver_ram.state_1up,
         sizeof(v_snddriver_ram.state));

  /* Setup DAC track */
  v_snddriver_ram.state.v_music_dac_track[0].PlaybackControl |=
      PLAYBACKCONTROL_SFX_OVERRIDE;

  /* Setup FM tracks */
  volume = 0x28;

  music_track = &v_snddriver_ram.state.v_music_fm1_track[0];
  for (i = 0; i < SOUND_DRIVER_NUM_MUSIC_FM_TRACKS; i++, music_track++) {
    /* Is track not playing? */
    if (!(music_track->PlaybackControl & PLAYBACKCONTROL_PLAYING))
      continue;

    music_track->PlaybackControl |=
        PLAYBACKCONTROL_AT_REST; /* Set 'track at rest' bit */
    music_track->u.fm.Volume += volume;

    /* Is SFX overriding? */
    if ((music_track->PlaybackControl & PLAYBACKCONTROL_SFX_OVERRIDE))
      continue;

    SetVoice(music_track, music_track->u.fm.VoiceIndex,
             v_snddriver_ram.state.v_voice_ptr);
  }

  /* Setup PSG tracks */
  music_track = &v_snddriver_ram.state.v_music_psg1_track[0];
  for (i = 0; i < SOUND_DRIVER_NUM_MUSIC_PSG_TRACKS; i++, music_track++) {
    /* Is track not playing? */
    if (!(music_track->PlaybackControl & PLAYBACKCONTROL_PLAYING))
      continue;

    music_track->PlaybackControl |=
        PLAYBACKCONTROL_AT_REST; /* Set 'track at rest' bit */
    PSGNoteOff(music_track);
    music_track->u.psg.Volume += volume;
  }

  v_snddriver_ram.state.f_fadein_flag = 0x80;
  v_snddriver_ram.state.v_fadein_counter = 0x28;
  v_snddriver_ram.state.f_1up_playing = 0;

  return 1;
}

static int cfSetTempoDivider(SoundDriverTrack *track, u8 **data) {
  track->TempoDivider = *(*data)++;
  return 0;
}

static int cfChangeFMVolume(SoundDriverTrack *track, u8 **data) {
  track->u.fm.Volume += *(*data)++;
  SendVoiceTL(track);
  return 0;
}

static int cfHoldNote(SoundDriverTrack *track, u8 **data) {
  (void)data;

  track->PlaybackControl |= PLAYBACKCONTROL_DO_NOT_ATTACK_NEXT;
  return 0;
}

static int cfNoteTimeout(SoundDriverTrack *track, u8 **data) {
  track->u.fm.NoteTimeout = *(*data);
  track->u.fm.NoteTimeoutMaster = *(*data)++;
  return 0;
}

static int cfChangeTransposition(SoundDriverTrack *track, u8 **data) {
  track->u.fm.Transpose += *(*data)++;
  return 0;
}

static int cfSetTempo(SoundDriverTrack *track, u8 **data) {
  (void)track;

  v_snddriver_ram.state.v_main_tempo = *(*data);
  v_snddriver_ram.state.v_main_tempo_timeout = *(*data)++;
  return 0;
}

static int cfSetTempoDividerAll(SoundDriverTrack *track, u8 **data) {
  size_t i;

  SoundDriverTrack *music_track;

  u8 new_value;

  (void)track;

  new_value = *(*data)++;

  music_track = &v_snddriver_ram.state.v_music_dac_track[0];
  for (i = 0; i < SOUND_DRIVER_NUM_MUSIC_TRACKS; i++, music_track++)
    music_track->TempoDivider = new_value;

  return 0;
}

static int cfChangePSGVolume(SoundDriverTrack *track, u8 **data) {
  track->u.psg.Volume += *(*data)++;
  return 0;
}

static int cfClearPush(SoundDriverTrack *track, u8 **data) {
  (void)track;
  (void)data;

  v_snddriver_ram.state.f_push_playing = 0;
  return 0;
}

static int cfStopSpecialFM4(SoundDriverTrack *track, u8 **data) {
  SoundDriverTrack *music_track;

  (void)data;

  track->PlaybackControl &= ~PLAYBACKCONTROL_PLAYING;
  track->PlaybackControl &= ~PLAYBACKCONTROL_DO_NOT_ATTACK_NEXT;
  FMNoteOff(track);

  /* Is SFX using FM4? */
  if (v_snddriver_ram.v_sfx_fm3_track[0].PlaybackControl &
      PLAYBACKCONTROL_PLAYING)
    return 1;

  /* Reset music FM4 */
  music_track = &v_snddriver_ram.state.v_music_fm1_track[4 - 1];

  music_track->PlaybackControl &= ~PLAYBACKCONTROL_SFX_OVERRIDE;
  music_track->PlaybackControl |= PLAYBACKCONTROL_AT_REST;

  SetVoice(music_track, music_track->u.fm.VoiceIndex,
           v_snddriver_ram.state.v_voice_ptr);

  return 1;
}

static int cfSetVoice(SoundDriverTrack *track, u8 **data) {
  u8 voice;

  voice = *(*data)++;
  track->u.fm.VoiceIndex = voice;

  /* Is SFX overriding this track? */
  if (track->PlaybackControl & PLAYBACKCONTROL_SFX_OVERRIDE)
    return 0;

  if (!v_snddriver_ram.state.f_voice_selector)
    SetVoice(track, voice, v_snddriver_ram.state.v_voice_ptr);
  else if (v_snddriver_ram.state.f_voice_selector & 0x80)
    SetVoice(track, voice, track->u.fm.VoicePtr);
  else
    SetVoice(track, voice, v_snddriver_ram.state.v_special_voice_ptr);

  return 0;
}

static void SetVoice(SoundDriverTrack *track, u8 voice, u8 *voice_ptr) {
  size_t i;

  u8 feedback_algo;
  u8 slot_mask, volume;

  voice_ptr += voice * 25;

  /* Send feedback algo */
  feedback_algo = *voice_ptr++;
  track->u.fm.FeedbackAlgo = feedback_algo;
  WriteFMIorII(track, 0xB0, feedback_algo);

  /* Send instrument operators */
  for (i = 0; i < sizeof(FMInstrumentOperatorTable) /
                      sizeof(FMInstrumentOperatorTable[0]);
       i++)
    WriteFMIorII(track, FMInstrumentOperatorTable[i], *voice_ptr++);

  /* Send TL operators */
  slot_mask = FMSlotMask[feedback_algo & 7];
  volume = track->u.fm.Volume;

  for (i = 0; i < sizeof(FMInstrumentTLTable) / sizeof(FMInstrumentTLTable[0]);
       i++) {
    u8 fm_addr, fm_data;

    fm_addr = FMInstrumentTLTable[i];
    fm_data = *voice_ptr++;

    if (slot_mask & 1)
      fm_data += volume;
    slot_mask >>= 1;

    WriteFMIorII(track, fm_addr, fm_data);
  }

  /* Register for AMS/FMS/Panning */
  WriteFMIorII(track, 0xB4, track->u.fm.AMSFMSPan);
}

u8 FMSlotMask[8] = {0x08, 0x08, 0x08, 0x08, 0x0A, 0x0E, 0x0E, 0x0F};

static void SendVoiceTL(SoundDriverTrack *track) {
  size_t i;

  u8 voice;
  u8 *voice_ptr;

  u8 slot_mask, volume;

  /* Is SFX overriding? */
  if (track->PlaybackControl & PLAYBACKCONTROL_SFX_OVERRIDE)
    return;

  voice = track->u.fm.VoiceIndex;
  voice_ptr = v_snddriver_ram.state.v_voice_ptr;

  if (v_snddriver_ram.state.f_voice_selector) {
#ifdef SONIC1C_FIX_MAJOR_UB
    voice_ptr = track->u.fm.VoicePtr;
#else
    /*
    ; DANGER! This uploads the wrong voice! It should have been a5 instead of
    a6! ; In Sonic 1's prototype, TrackVoicePtr was a global variable instead of
    a ; per-track variable, explaining why this uses a6 instead of a5.
    */
    voice_ptr = ((SoundDriverTrack *)&v_snddriver_ram)->u.fm.VoicePtr;
#endif

    if (!(v_snddriver_ram.state.f_voice_selector & 0x80))
      voice_ptr = v_snddriver_ram.state.v_special_voice_ptr;
  }
  if (!voice_ptr)
    return;

  /* Attenuate voice operator volumes */
  voice_ptr += (voice * 25) + 21;

  slot_mask = FMSlotMask[track->u.fm.FeedbackAlgo & 7];

  volume = track->u.fm.Volume;
  if (volume & 0x80)
    return;

  for (i = 0; i < sizeof(FMInstrumentTLTable) / sizeof(FMInstrumentTLTable[0]);
       i++) {
    u8 fm_addr, fm_data;

    fm_addr = FMInstrumentTLTable[i];
    fm_data = *voice_ptr++;

    if (slot_mask & 1) {
      if (((u16)fm_data + volume) <= 0xFF)
        WriteFMIorII(track, fm_addr, fm_data + volume);
    }

    slot_mask >>= 1;
  }
}

u8 FMInstrumentOperatorTable[4 * 5] = {
    0x30, /* Detune / multiple operator 1 */
    0x38, /* Detune / multiple operator 3 */
    0x34, /* Detune / multiple operator 2 */
    0x3C, /* Detune / multiple operator 4 */
    0x50, /* Rate scalling / attack rate operator 1 */
    0x58, /* Rate scalling / attack rate operator 3 */
    0x54, /* Rate scalling / attack rate operator 2 */
    0x5C, /* Rate scalling / attack rate operator 4 */
    0x60, /* Amplitude modulation / first decay rate operator 1 */
    0x68, /* Amplitude modulation / first decay rate operator 3 */
    0x64, /* Amplitude modulation / first decay rate operator 2 */
    0x6C, /* Amplitude modulation / first decay rate operator 4 */
    0x70, /* Secondary decay rate operator 1 */
    0x78, /* Secondary decay rate operator 3 */
    0x74, /* Secondary decay rate operator 2 */
    0x7C, /* Secondary decay rate operator 4 */
    0x80, /* Secondary amplitude / release rate operator 1 */
    0x88, /* Secondary amplitude / release rate operator 3 */
    0x84, /* Secondary amplitude / release rate operator 2 */
    0x8C  /* Secondary amplitude / release rate operator 4 */
};

u8 FMInstrumentTLTable[4] = {
    0x40, /* Total level operator 1 */
    0x48, /* Total level operator 2 */
    0x44, /* Total level operator 3 */
    0x4C, /* Total level operator 4 */
};

static int cfModulation(SoundDriverTrack *track, u8 **data) {
  track->PlaybackControl |= PLAYBACKCONTROL_MODULATION;

  track->u.fm.ModulationPtr = *data;
  track->u.fm.ModulationWait = *(*data)++;
  track->u.fm.ModulationSpeed = *(*data)++;
  track->u.fm.ModulationDelta = *(*data)++;
  track->u.fm.ModulationSteps = *(*data)++ >> 1;
  track->u.fm.ModulationVal = 0;

  return 0;
}

static int cfEnableModulation(SoundDriverTrack *track, u8 **data) {
  (void)data;

  track->PlaybackControl |= PLAYBACKCONTROL_MODULATION;
  return 0;
}

static int cfStopTrack(SoundDriverTrack *track, u8 **data) {
  u8 voice;

  (void)data;

  track->PlaybackControl &= ~PLAYBACKCONTROL_PLAYING;
  track->PlaybackControl &= ~PLAYBACKCONTROL_DO_NOT_ATTACK_NEXT;

  if (!(track->VoiceControl & VOICECONTROL_IS_PSG)) {
    /* Is this the DAC we are updating? */
    if (v_snddriver_ram.state.f_updating_dac)
      return 1;

    FMNoteOff(track);
  } else {
    PSGNoteOff(track);
  }

  /* Are we updating SFX? */
  if (!(v_snddriver_ram.state.f_voice_selector & (1 << 7)))
    return 1;

  v_snddriver_ram.state.v_sndprio = 0;

  voice = track->VoiceControl;

  /* Is this not a PSG track? */
  if (!(track->VoiceControl & VOICECONTROL_IS_PSG)) {
    SoundDriverTrack *old_track;

    u8 *voice_ptr;

    old_track = track;

    /* Is this special FM4? */
    if (voice == 4 && (v_snddriver_ram.v_spcsfx_fm4_track[0].PlaybackControl &
                       PLAYBACKCONTROL_PLAYING)) {
      track = &v_snddriver_ram.v_spcsfx_fm4_track[0];
      voice_ptr = v_snddriver_ram.state.v_special_voice_ptr;
    } else {
      /* - 2 because SFX can only use FM3 and up */
      track = SFX_BGMChannelRAM[voice - 2];

      /* Is track not playing? */
      if (!(track->PlaybackControl & PLAYBACKCONTROL_PLAYING))
        return 1;

      voice_ptr = v_snddriver_ram.state.v_voice_ptr;
    }
    if (!voice_ptr)
      return 1;

    track->PlaybackControl &= ~PLAYBACKCONTROL_SFX_OVERRIDE;
    track->PlaybackControl |= PLAYBACKCONTROL_AT_REST;

    SetVoice(track, track->u.fm.VoiceIndex, voice_ptr);
    track = old_track;
  } else {
    SoundDriverTrack *voice_track;

    /* Is this special PSG3? */
    if ((v_snddriver_ram.v_spcsfx_psg3_track[0].PlaybackControl &
         PLAYBACKCONTROL_PLAYING) &&
        (voice == 0xE0 || voice == 0xC0)) {
      voice_track = &v_snddriver_ram.v_spcsfx_psg3_track[0];
    } else {
      voice_track = SFX_BGMChannelRAM[voice >> (3 + 2)];
    }

    voice_track->PlaybackControl &= ~PLAYBACKCONTROL_SFX_OVERRIDE;
    voice_track->PlaybackControl |= PLAYBACKCONTROL_AT_REST;

    if (voice_track->VoiceControl == 0xE0)
      write_psg(voice_track->u.psg.PSGNoise);
  }

  return 1;
}

static int cfSetPSGNoise(SoundDriverTrack *track, u8 **data) {
  track->VoiceControl = 0xE0;
  track->u.psg.PSGNoise = *(*data)++;

  if (track->PlaybackControl & PLAYBACKCONTROL_SFX_OVERRIDE)
    return 0;

  write_psg((*data)[-1]);
  return 0;
}

static int cfDisableModulation(SoundDriverTrack *track, u8 **data) {
  (void)data;

  track->PlaybackControl &= ~PLAYBACKCONTROL_MODULATION;
  return 0;
}

static int cfSetPSGTone(SoundDriverTrack *track, u8 **data) {
  track->u.psg.VoiceIndex = *(*data)++;
  return 0;
}

static int cfJumpTo(SoundDriverTrack *track, u8 **data) {
  s32 offset;

  (void)track;

  offset = ((u16)(*data)[0] << 8) | (*data)[1];
  *data += 2;

  if (offset & 0x8000)
    offset -= 0x10000;

  *data = *data + offset - 1;

  return 0;
}

static int cfRepeatAtPos(SoundDriverTrack *track, u8 **data) {
  u8 repeat_index, repeat_count;

  repeat_index = *(*data)++;
  repeat_count = *(*data)++;

  /* Has this loop not already started? */
  if (track->top.LoopCounters[repeat_index] == 0)
    track->top.LoopCounters[repeat_index] = repeat_count;

  if (--track->top.LoopCounters[repeat_index] != 0)
    return cfJumpTo(track, data);

  *data += 2; /* Skip target address */

  return 0;
}

static int cfJumpToGosub(SoundDriverTrack *track, u8 **data) {
  u8 sp;
  (void)track;

  /* Push current data pointer to stack */
  sp = track->u.fm.StackPointer - sizeof(u8 *);

  *(u8 **)((u8 *)track + sp) = *data;

  track->u.fm.StackPointer = sp;

  return cfJumpTo(track, data);
}

static int cfOpF9(SoundDriverTrack *track, u8 **data) {
  (void)track;
  (void)data;

  /* D1L/RR of Operator 3 */
  /* Loaded with fixed value (max RR, 1TL) */
  WriteFMI(0x88, 0xF);
  /* D1L/RR of Operator 4 */
  /* Loaded with fixed value (max RR, 1TL) */
  WriteFMI(0x8C, 0xF);

  return 0;
}
