use std::{
    array,
    cell::{LazyCell, RefCell},
    ops::Deref,
    rc::Rc,
    sync::{Arc, LazyLock},
};

use crate::{
    FM_SAMPLE_RATE, M68K_CLOCK, MCYCLES_FRAME, PSG_SAMPLE_RATE, Z80_CLOCK,
    dacdriver::DacDriver,
    vgm_ffi::{
        DEV_DEF, DEV_GEN_CFG, DEV_INFO, DEVFUNC_UPDATE, DEVFUNC_WRITE_A8D8, DEVID_SN76496,
        DEVID_YM2612, DEVRI_SRMODE_CUSTOM, DEVRI_SRMODE_NATIVE, DEVRW_A8D8, EERR_NOT_FOUND,
        FCC_GPGX, FCC_MAME, FCC_MAXM, RESAMPLER_FUNC, RESMPL_STATE, RSMODE_LINEAR, RSMODE_NEAREST,
        RWF_REGISTER, RWF_WRITE, Resmpl_Deinit, Resmpl_DevConnect, Resmpl_Execute, Resmpl_Init,
        Resmpl_SetVals, SN76496_CFG, SndEmu_GetDevDefList, SndEmu_GetDeviceFunc, SndEmu_Start,
        SndEmu_Stop, WAVE_32BS,
    },
};
use bitfield::{Bit, BitMut};
use num::PrimInt;
use paste::paste;

pub struct SoundDriver {
    rom: Arc<Vec<u8>>,
    sample_rate: u16,
    fm_buf: Vec<i32>,
    psg_buf: Vec<i32>,
    pub safe_audio_buffer: Vec<i16>,
    ram: Vec<u8>,
    fm_resampler: RESMPL_STATE,
    psg_resampler: RESMPL_STATE,
    fm: DEV_INFO,
    psg: DEV_INFO,
    dac: DacDriver,
}
impl Drop for SoundDriver {
    fn drop(&mut self) {
        unsafe {
            Resmpl_Deinit(&mut self.fm_resampler);
            Resmpl_Deinit(&mut self.psg_resampler);
            SndEmu_Stop(&raw mut devinf_fm);
            SndEmu_Stop(&raw mut devinf_psg);
        }
    }
}
impl SoundDriver {
    pub fn new(rom: Arc<Vec<u8>>, sample_rate: u16) -> Self {
        unsafe {
            let mut fm = DEV_INFO {
                dataPtr: std::ptr::null_mut(),
                sampleRate: sample_rate as u32 / 60,
                devDef: std::ptr::null(),
                linkDevCount: 0,
                linkDevs: std::ptr::null_mut(),
            };
            let fm_cfg = DEV_GEN_CFG {
                emuCore: FCC_GPGX,
                srMode: DEVRI_SRMODE_NATIVE,
                flags: 0,
                clock: M68K_CLOCK as u32 / 60,
                smplRate: FM_SAMPLE_RATE as u32 / 60,
            };
            fm.devDef = *SndEmu_GetDevDefList(DEVID_YM2612);
            SndEmu_Start(DEVID_YM2612, &fm_cfg, &mut fm);
            ((*fm.devDef).Reset).unwrap()(fm.dataPtr as *mut u8);
            ((*fm.devDef).SetOptionBits).unwrap()(fm.dataPtr as *mut u8, 0b0000_0000);
            let mut fm_resampler = RESMPL_STATE::default();
            Resmpl_SetVals(
                &mut fm_resampler,
                RSMODE_LINEAR,
                0x1,
                sample_rate as u32 / 60,
            );
            Resmpl_DevConnect(&mut fm_resampler, &mut fm);
            Resmpl_Init(&mut fm_resampler);

            let mut psg = DEV_INFO {
                dataPtr: std::ptr::null_mut(),
                sampleRate: sample_rate as u32 / 60,
                devDef: std::ptr::null(),
                linkDevCount: 0,
                linkDevs: std::ptr::null_mut(),
            };
            let psg_cfg = SN76496_CFG {
                _genCfg: DEV_GEN_CFG {
                    emuCore: FCC_MAXM,
                    srMode: DEVRI_SRMODE_NATIVE,
                    flags: 0,
                    clock: Z80_CLOCK as u32 / 60,
                    smplRate: PSG_SAMPLE_RATE as u32 / 60,
                },
                noiseTaps: 9,
                shiftRegWidth: 16,
                negate: 1,
                clkDiv: 8,
                ncrPSG: 0,
                segaPSG: 1,
                stereo: 0,
                t6w28_tone: std::ptr::null_mut(),
            };
            psg.devDef = *(SndEmu_GetDevDefList(DEVID_SN76496).add(1));
            SndEmu_Start(DEVID_SN76496, &psg_cfg._genCfg, &mut psg);
            ((*psg.devDef).Reset).unwrap()(psg.dataPtr as *mut u8);
            let mut psg_resampler = RESMPL_STATE::default();
            Resmpl_SetVals(
                &mut psg_resampler,
                RSMODE_LINEAR,
                0x1,
                sample_rate as u32 / 60,
            );
            Resmpl_DevConnect(&mut psg_resampler, &mut psg);
            Resmpl_Init(&mut psg_resampler);

            let ret = Self {
                rom: rom.clone(),
                ram: vec![0; 0x1000],
                safe_audio_buffer: vec![0; (sample_rate as usize * 2) / 60],
                sample_rate,
                fm_resampler,
                psg_resampler,
                fm_buf: vec![0; 0x1_0000],
                psg_buf: vec![0; 0x1_0000],
                fm,
                psg,
                dac: DacDriver::new(&rom),
            };
            ret
        }
    }

    fn set_up_ffi(&mut self) {
        unsafe {
            smps_rom_ptr = self.rom.as_ptr();
            smps_ram_ptr = self.ram.as_mut_ptr();
            devinf_fm = self.fm.clone();
            devinf_psg = self.psg.clone();
        }
    }

    pub fn play_sound(&mut self, id: u8) {
        self.set_up_ffi();
        self.ram[0xa] = id;
    }

    pub fn play_sound_special(&mut self, id: u8) {
        self.set_up_ffi();
        self.ram[0xb] = id;
    }

    pub fn update(&mut self) {
        self.set_up_ffi();
        unsafe {
            smps_update();
            if cur_dac_sample != 0 {
                self.dac.play_sample(cur_dac_sample);
                cur_dac_sample = 0;
            }
        }
        self.fm_buf.fill(0);
        self.psg_buf.fill(0);
        self.safe_audio_buffer.fill(0);

        let samples = self.safe_audio_buffer.len() as u32 / 2;
        // let samples = MCYCLES_FRAME as u32;
        let sample_time_slice = 1.0 / (samples as f64);
        let fm_time_slice = 1.0 / FM_SAMPLE_RATE;
        let dac_time_slice = if self.dac.cur_sample_rate() != 0 {
            1.0 / (self.dac.cur_sample_rate() as f64 / 60.0)
        } else {
            1.0
        };
        let mut fm_cycles_accum = 0.0;
        let mut fm_i = 0;
        let mut dac_cycles_accum = 0.0;
        unsafe {
            for _ in 0..samples {
                fm_cycles_accum += sample_time_slice;
                if fm_cycles_accum >= fm_time_slice {
                    Resmpl_Execute(
                        &mut self.fm_resampler,
                        1,
                        (self.fm_buf.as_mut_ptr() as *mut WAVE_32BS).add(fm_i as usize),
                    );
                    fm_i += 1;
                    fm_cycles_accum -= fm_time_slice;
                }
                dac_cycles_accum += sample_time_slice;
                if dac_cycles_accum >= dac_time_slice {
                    self.dac.update(write_fm_i);
                    dac_cycles_accum -= dac_time_slice;
                }
            }
            Resmpl_Execute(
                &mut self.psg_resampler,
                self.safe_audio_buffer.len() as u32 / 2,
                self.psg_buf.as_mut_ptr() as *mut WAVE_32BS,
            );
        }
        unsafe {
            let dst_ptr = self.safe_audio_buffer.as_mut_ptr();
            let fm_ptr = self.fm_buf.as_mut_ptr() as *mut i16;
            let psg_ptr = self.psg_buf.as_mut_ptr() as *mut i16;
            for i in 0..self.safe_audio_buffer.len() {
                *dst_ptr.add(i) = (*psg_ptr.add(i * 2) / 2).saturating_add(*fm_ptr.add(i * 2));
            }
        }
    }
}

static mut cur_dac_sample: u8 = 0;
static mut devinf_fm: DEV_INFO = DEV_INFO::default();
static mut devinf_psg: DEV_INFO = DEV_INFO::default();

unsafe extern "C" {
    static mut smps_rom_ptr: *const u8;
    static mut smps_ram_ptr: *mut u8;

    fn smps_update() -> ();
}
fn get_write_func(devinf: *const DEV_INFO) -> Option<DEVFUNC_WRITE_A8D8> {
    unsafe {
        let write_func: *mut u8 = std::ptr::null_mut();
        let retVal = SndEmu_GetDeviceFunc(
            (*devinf).devDef,
            RWF_REGISTER | RWF_WRITE,
            DEVRW_A8D8,
            0,
            std::mem::transmute(&write_func),
        );
        if (retVal != EERR_NOT_FOUND && write_func != std::ptr::null_mut()) {
            Some(std::mem::transmute(write_func))
        } else {
            None
        }
    }
}

#[unsafe(no_mangle)]
extern "C" fn write_fm_i(a: u8, v: u8) {
    unsafe {
        if let Some(write_func) = get_write_func(&raw const devinf_fm) {
            write_func(devinf_fm.dataPtr as *mut u8, 0, a);
            write_func(devinf_fm.dataPtr as *mut u8, 1, v);
        }
    }
}
#[unsafe(no_mangle)]
extern "C" fn write_fm_ii(a: u8, v: u8) {
    unsafe {
        if let Some(write_func) = get_write_func(&raw const devinf_fm) {
            write_func(devinf_fm.dataPtr as *mut u8, 2, a);
            write_func(devinf_fm.dataPtr as *mut u8, 3, v);
        }
    }
}
#[unsafe(no_mangle)]
extern "C" fn write_psg(data: u8) {
    unsafe {
        if let Some(write_func) = get_write_func(&raw const devinf_psg) {
            write_func(devinf_psg.dataPtr as *mut u8, 0, data);
        }
    }
}

#[unsafe(no_mangle)]
extern "C" fn set_dac_sample(sample: u8) {
    unsafe {
        cur_dac_sample = sample;
    }
}
