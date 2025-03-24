#![allow(unused)]
#![allow(non_snake_case)]
#![allow(non_camel_case_types)]

pub type UINT8 = u8;
pub type INT8 = i8;
pub type UINT16 = u16;
pub type INT16 = i16;
pub type UINT32 = u32;
pub type INT32 = i32;

pub type DEV_SMPL = i32;
pub type DEVLINK_INFO = u8;
pub type DEV_DATA = u8;

// typedef UINT8 (*DEVFUNC_START)(const DEV_GEN_CFG* cfg, DEV_INFO* retDevInf);
pub type DEVFUNC_START = extern "C" fn(cfg: *const DEV_GEN_CFG, retDevInf: *mut DEV_INFO) -> u8;
// typedef void (*DEVFUNC_CTRL)(void* info);
pub type DEVFUNC_CTRL = extern "C" fn(info: *mut u8) -> ();
// typedef void (*DEVFUNC_UPDATE)(void* info, UINT32 samples, DEV_SMPL** outputs);
pub type DEVFUNC_UPDATE =
    extern "C" fn(info: *mut u8, samples: u32, outputs: *mut *mut DEV_SMPL) -> ();
// typedef void (*DEVFUNC_OPTMASK)(void* info, UINT32 optionBits);
pub type DEVFUNC_OPTMASK = extern "C" fn(info: *mut u8, optionBits: u32) -> ();
// typedef void (*DEVFUNC_PANALL)(void* info, const INT16* channelPanVal);
pub type DEVFUNC_PANALL = extern "C" fn(info: *mut u8, channelPanVal: *const i16) -> ();
// typedef void (*DEVFUNC_SRCCB)(void* info, DEVCB_SRATE_CHG SmpRateChgCallback, void* paramPtr);
pub type DEVFUNC_SRCCB =
    extern "C" fn(info: *mut u8, SmpRateChgCallback: DEVCB_SRATE_CHG, paramPtr: *mut u8) -> ();
// typedef
pub type DEVFUNC_LINKDEV =
    extern "C" fn(info: *mut u8, devID: UINT8, devInfLink: *const DEV_INFO) -> UINT8;
// typedef void (*DEVFUNC_SETLOGCB)(void* info, DEVCB_LOG logFunc, void* userParam);
pub type DEVFUNC_SETLOGCB = extern "C" fn(info: *mut u8, logFunc: DEVCB_LOG, userParam: *mut u8);

// typedef void (*DEVCB_SRATE_CHG)(void* userParam, UINT32 newSRate);
pub type DEVCB_SRATE_CHG = extern "C" fn(userParam: *mut u8, newSRate: u32);
// typedef void (*DEVCB_LOG)(void* userParam, void* source, UINT8 level, const char* message);
pub type DEVCB_LOG =
    extern "C" fn(userParam: *mut u8, source: *mut u8, level: u8, message: *const i8);

// typedef void (*DEVFUNC_WRITE_A8D8)(void* info, UINT8 addr, UINT8 data);
pub type DEVFUNC_WRITE_A8D8 = extern "C" fn(info: *mut u8, addr: u8, data: u8);

#[repr(C)]
#[derive(Clone, Copy)]
pub struct DEV_DEF {
    pub name: *const i8,   // name of the device
    pub author: *const i8, // author/origin of emulation
    pub coreID: u32,       // 4-character identifier ID to distinguish between
    // multiple emulators of a device
    pub Start: Option<DEVFUNC_START>,
    pub Stop: Option<DEVFUNC_CTRL>,
    pub Reset: Option<DEVFUNC_CTRL>,
    pub Update: Option<DEVFUNC_UPDATE>,

    pub SetOptionBits: Option<DEVFUNC_OPTMASK>,
    pub SetMuteMask: Option<DEVFUNC_OPTMASK>,
    pub SetPanning: Option<DEVFUNC_PANALL>, // **NOTE: deprecated, moved to rwFuncs**
    pub SetSRateChgCB: Option<DEVFUNC_SRCCB>, // used to set callback function for realtime sample rate changes
    pub SetLogCB: Option<DEVFUNC_SETLOGCB>,   // set callback for logging
    pub LinkDevice: Option<DEVFUNC_LINKDEV>,  // used to link multiple devices together

    pub rwFuncs: *const DEVDEF_RWFUNC, // terminated by (funcPtr == NULL)
} // DEV_DEF

#[repr(C)]
#[derive(Clone, Debug)]
pub struct DEV_INFO {
    pub dataPtr: *mut DEV_DATA, // points to chip data structure
    pub sampleRate: u32,
    pub devDef: *const DEV_DEF,

    pub linkDevCount: u32,           // number of link-able devices
    pub linkDevs: *mut DEVLINK_INFO, // [freed by caller]
} // DEV_INFO
impl DEV_INFO {
    pub const fn default() -> Self {
        Self {
            dataPtr: std::ptr::null_mut(),
            sampleRate: 0,
            devDef: std::ptr::null(),
            linkDevCount: 0,
            linkDevs: std::ptr::null_mut(),
        }
    }
}

#[repr(C)]
pub struct DEVDEF_RWFUNC {
    pub funcType: u8, // function type, see RWF_ constants
    pub rwType: u8,   // read/write function type, see DEVRW_ constants
    pub user: u16,    // user-defined value
    pub funcPtr: *const u8,
}

#[link(name = "smps")]
unsafe extern "C" {
    /**
     * @brief Retrieve a list of all available sound cores for a device.
     *
     * @param deviceID ID of the sound device (see DEVID_ constants in SoundDevs.h)
     * @return an array of DEV_DEF* that is terminated by a NULL pointer
     */
    pub fn SndEmu_GetDevDefList(deviceID: UINT8) -> *const *const DEV_DEF;
    /**
     * @brief Initializes emulation for a sound device.
     *
     * @param deviceID ID of the sound device to be emulated (see DEVID constants in SoundDevs.h)
     * @param cfg chip-dependent configuration structure, contains various settings
     * @param retDevInf pointer to DEV_INFO structure that gets filled with device information,
     *        caller has to free information about linkable devices
     * @return error code. 0 = success, see EERR constants
     */
    pub fn SndEmu_Start(deviceID: UINT8, cfg: *const DEV_GEN_CFG, retDevInf: *mut DEV_INFO) -> u8;
    /**
     * @brief Deinitializes the sound core.
     *
     * @param devInf DEV_INFO structure of the device to be stopped
     * @return always returns 0 (success)
     */
    pub fn SndEmu_Stop(devInf: *mut DEV_INFO) -> u8;
    /**
     * @brief Frees memory that holds information about linkable devices.
     *        Should be called sometime after a successful SndEmu_Start() in order to prevent memory leaks.
     *
     * @param devInf DEV_INFO structure of the main device
     */
    pub fn SndEmu_FreeDevLinkData(devInf: *mut DEV_INFO) -> ();
    /**
     * @brief Retrieve a function of a sound core that fullfills certain conditions.
     *
     * @param devInf DEV_INFO structure of the device
     * @param funcType function type (write/read, register/memory, ...), see RWF_ constants in EmuStructs.h
     * @param rwType read/write data type, see DEVRW_ constants in EmuStructs.h
     * @param user user-defined value for distinguishing functions with the same funcType/rwType, 0 = default
     * @param retFuncPtr parameter the function pointer is stored in
     * @return error code. 0 = success, 1 - success, but more possible candidates found, see EERR constants
     */
    pub fn SndEmu_GetDeviceFunc(
        devInf: *const DEV_DEF,
        funcType: UINT8,
        rwType: UINT8,
        user: UINT16,
        retFuncPtr: *mut *mut u8,
    ) -> u8;
    /**
     * @brief Retrieve the name of a sound device.
     *        Device configuration parameters may be use to identify exact sound chip models.
     *
     * @param deviceID ID of the sound device to get the name of (see DEVID constants in SoundDevs.h)
     * @param opts bitfield of options
     *             Bit 0 (0x01): enable long names
     * @param cfg chip-dependent configuration structure, allows for correct names of device variations,
     *            ONLY used when long names are enabled
     * @return pointer to name of the device
     */
    pub fn SndEmu_GetDevName(deviceID: UINT8, opts: UINT8, devCfg: *const DEV_GEN_CFG)
    -> *const i8;
}

pub const EERR_OK: u8 = 0x00;
pub const EERR_MORE_FOUND: u8 = 0x01; // success, but more items were found
pub const EERR_UNK_DEVICE: u8 = 0xF0; // unknown/invalid device ID
pub const EERR_NOT_FOUND: u8 = 0xF8; // sound core or function not found
pub const EERR_INIT_ERR: u8 = 0xFF; // sound core initialization error (usually malloc error)

pub const DEVID_SN76496: u8 = 0x00; // variants: SN76489(A), SEGA PSG, T6W28
pub const DEVID_YM2413: u8 = 0x01; // variants: VRC7
pub const DEVID_YM2612: u8 = 0x02; // variants: YM3438
pub const DEVID_YM2151: u8 = 0x03;
pub const DEVID_SEGAPCM: u8 = 0x04;
pub const DEVID_RF5C68: u8 = 0x05; // variants: RF5C164, RF5C105
pub const DEVID_YM2203: u8 = 0x06;
pub const DEVID_YM2608: u8 = 0x07; // variants: YMF288
pub const DEVID_YM2610: u8 = 0x08; // variants: YM2610B
pub const DEVID_YM3812: u8 = 0x09; // also known as OPL2
pub const DEVID_YM3526: u8 = 0x0A;
pub const DEVID_Y8950: u8 = 0x0B;
pub const DEVID_YMF262: u8 = 0x0C; // also known as OPL3
pub const DEVID_YMF278B: u8 = 0x0D; // also known as OPL4
pub const DEVID_YMF271: u8 = 0x0E;
pub const DEVID_YMZ280B: u8 = 0x0F;
pub const DEVID_32X_PWM: u8 = 0x11;
pub const DEVID_AY8910: u8 = 0x12; // variants: AY-3-8912/8913/8930, YM2149, YM3439, YMZ284/294
pub const DEVID_GB_DMG: u8 = 0x13;
pub const DEVID_NES_APU: u8 = 0x14; // also known as RP2A03/RP2A07
pub const DEVID_YMW258: u8 = 0x15; // also known as MultiPCM
pub const DEVID_uPD7759: u8 = 0x16;
pub const DEVID_OKIM6258: u8 = 0x17; // also known as MSM6258
pub const DEVID_OKIM6295: u8 = 0x18; // also known as MSM6295
pub const DEVID_K051649: u8 = 0x19; // also known as SCC1, variants: K052539, also known as SCC+
pub const DEVID_K054539: u8 = 0x1A;
pub const DEVID_C6280: u8 = 0x1B;
pub const DEVID_C140: u8 = 0x1C;
pub const DEVID_C219: u8 = 0x80; // TODO: renumber devices
pub const DEVID_K053260: u8 = 0x1D;
pub const DEVID_POKEY: u8 = 0x1E;
pub const DEVID_QSOUND: u8 = 0x1F;
pub const DEVID_SCSP: u8 = 0x20; // also known as YMF292
pub const DEVID_WSWAN: u8 = 0x21;
pub const DEVID_VBOY_VSU: u8 = 0x22;
pub const DEVID_SAA1099: u8 = 0x23;
pub const DEVID_ES5503: u8 = 0x24;
pub const DEVID_ES5506: u8 = 0x25; // variants: ES5505
pub const DEVID_X1_010: u8 = 0x26;
pub const DEVID_C352: u8 = 0x27;
pub const DEVID_GA20: u8 = 0x28;
pub const DEVID_MIKEY: u8 = 0x29;

pub const FCC_MAME: u32 = 0x4D414D45; // MAME
pub const FCC_MAXM: u32 = 0x4D41584D; // SN76489 by Maxim
pub const FCC_EMU_: u32 = 0x454D5500; // EMU2413/EMU2149
pub const FCC_GPGX: u32 = 0x47504758; // Genesis Plus GX
pub const FCC_GENS: u32 = 0x47454E53; // Gens
pub const FCC_ADLE: u32 = 0x41444C45; // AdLibEmu
pub const FCC_OMSX: u32 = 0x4F4D5358; // openMSX
pub const FCC_NSFP: u32 = 0x4E534650; // NSFPlay
pub const FCC_OOTK: u32 = 0x4F4F544B; // Ootake
pub const FCC_MEDN: u32 = 0x4D45444E; // Mednafen
pub const FCC_NUKE: u32 = 0x4E554B45; // Nuked OPx
pub const FCC_NRS_: u32 = 0x4E525300; // NewRisingSun
pub const FCC_VBEL: u32 = 0x5642454C; // Valley Bell
pub const FCC_CTR_: u32 = 0x43545200; // superctr
pub const FCC_LAOO: u32 = 0x4c414f4f; // laoo

// device resampling info constants
pub const DEVRI_SRMODE_NATIVE: u8 = 0x00;
pub const DEVRI_SRMODE_CUSTOM: u8 = 0x01;
pub const DEVRI_SRMODE_HIGHEST: u8 = 0x02;
#[repr(C)]
#[derive(Default)]
pub struct DEV_GEN_CFG {
    pub emuCore: UINT32, // emulation core (4-character code, 0 = default)
    pub srMode: UINT8,   // sample rate mode

    pub flags: UINT8,  // chip flags
    pub clock: UINT32, // chip clock
    pub smplRate: UINT32, // sample rate for SRMODE_CUSTOM/DEVRI_SRMODE_HIGHEST
                       // Note: Some cores ignore the srMode setting and always use smplRate.
} // DEV_GEN_CFG

pub const RWF_WRITE: u8 = 0x00;
pub const RWF_READ: u8 = 0x01;
pub const RWF_QUICKWRITE: u8 = (0x02 | RWF_WRITE);
pub const RWF_QUICKREAD: u8 = (0x02 | RWF_READ);
pub const RWF_REGISTER: u8 = 0x00; // register r/w
pub const RWF_MEMORY: u8 = 0x10; // memory (RAM) r/w
// Note: These chip setting constants can be ORed with RWF_WRITE/RWF_READ.
pub const RWF_CLOCK: u8 = 0x80; // chip clock
pub const RWF_SRATE: u8 = 0x82; // sample rate
pub const RWF_VOLUME: u8 = 0x84; // volume (all speakers)
pub const RWF_VOLUME_LR: u8 = 0x86; // volume (left/right separately)
pub const RWF_CHN_MUTE: u8 = 0x90; // set channel muting (DEVRW_VALUE = single channel, DEVRW_ALL = mask)
pub const RWF_CHN_PAN: u8 = 0x92; // set channel panning (DEVRW_VALUE = single channel, DEVRW_ALL = array)

// register/memory DEVRW constants
pub const DEVRW_A8D8: u8 = 0x11; //  8-bit address,  8-bit data
pub const DEVRW_A8D16: u8 = 0x12; //  8-bit address, 16-bit data
pub const DEVRW_A16D8: u8 = 0x21; // 16-bit address,  8-bit data
pub const DEVRW_A16D16: u8 = 0x22; // 16-bit address, 16-bit data
pub const DEVRW_BLOCK: u8 = 0x80; // write sample ROM/RAM
pub const DEVRW_MEMSIZE: u8 = 0x81; // set ROM/RAM size
// chip setting DEVRW constants
pub const DEVRW_VALUE: u8 = 0x00;
pub const DEVRW_ALL: u8 = 0x01;

pub const DEVLOG_OFF: u8 = 0x00;
pub const DEVLOG_ERROR: u8 = 0x01;
pub const DEVLOG_WARN: u8 = 0x02;
pub const DEVLOG_INFO: u8 = 0x03;
pub const DEVLOG_DEBUG: u8 = 0x04;
pub const DEVLOG_TRACE: u8 = 0x05;

#[repr(C)]
pub struct WAVE_32BS {
    pub L: DEV_SMPL,
    pub R: DEV_SMPL,
}

// Resampler Modes
pub const RSMODE_LINEAR: u8 = 0x00; // linear interpolation (good quality)
pub const RSMODE_NEAREST: u8 = 0x01; // nearest-neighbour (low quality)
pub const RSMODE_LUP_NDWN: u8 = 0x02; // nearest-neighbour downsampling, interpolation upsampling

// typedef void (*RESAMPLER_FUNC)(RESMPL_STATE* CAA, UINT32 length, WAVE_32BS* retSample);
pub type RESAMPLER_FUNC =
    extern "C" fn(CAA: *mut RESMPL_STATE, length: UINT32, retSample: *mut WAVE_32BS);

#[repr(C)]
pub struct RESMPL_STATE {
    pub smpRateSrc: UINT32,
    pub smpRateDst: UINT32,
    pub volumeL: INT16,
    pub volumeR: INT16,
    pub resampleMode: UINT8, // see RSMODE_ constants
    pub resampler: Option<RESAMPLER_FUNC>,
    pub StreamUpdate: Option<DEVFUNC_UPDATE>,
    pub su_DataPtr: *mut u8,
    pub smpP: UINT32,     // Current Sample (Playback Rate)
    pub smpLast: UINT32,  // Sample Number Last
    pub smpNext: UINT32,  // Sample Number Next
    pub lSmpl: WAVE_32BS, // Last Sample
    pub nSmpl: WAVE_32BS, // Next Sample
    pub smplBufSize: UINT32,
    pub smplBufs: [*mut DEV_SMPL; 2],
}
impl Default for RESMPL_STATE {
    fn default() -> Self {
        unsafe {
            Self {
                smpRateSrc: 0,
                smpRateDst: 0,
                volumeL: 0,
                volumeR: 0,
                resampleMode: 0,
                resampler: None,
                StreamUpdate: None,
                su_DataPtr: std::ptr::null_mut(),
                smpP: 0,
                smpLast: 0,
                smpNext: 0,
                lSmpl: WAVE_32BS { L: 0, R: 0 },
                nSmpl: WAVE_32BS { L: 0, R: 0 },
                smplBufSize: 0,
                smplBufs: [std::ptr::null_mut(); 2],
            }
        }
    }
}

#[link(name = "smps")]
unsafe extern "C" {
    pub fn Resmpl_DevConnect(CAA: *mut RESMPL_STATE, devInf: *const DEV_INFO) -> ();
    pub fn Resmpl_SetVals(
        CAA: *mut RESMPL_STATE,
        resampleMode: UINT8,
        volume: UINT16,
        destSampleRate: UINT32,
    ) -> ();
    pub fn Resmpl_Init(CAA: *mut RESMPL_STATE) -> ();
    pub fn Resmpl_Deinit(CAA: *mut RESMPL_STATE) -> ();
    pub fn Resmpl_ChangeRate(DataPtr: *mut u8, newSmplRate: UINT32) -> ();
    pub fn Resmpl_Execute(
        CAA: *mut RESMPL_STATE,
        samples: UINT32,
        smplBuffer: *mut WAVE_32BS,
    ) -> ();
}

#[repr(C)]
pub struct SN76496_CFG {
    pub _genCfg: DEV_GEN_CFG,

    pub noiseTaps: UINT16,    // noise tap mask (usually 2 bits set)
    pub shiftRegWidth: UINT8, // noise shift register width
    pub negate: UINT8,        // invert output
    pub clkDiv: UINT8,        // clock divider (1 or 8)
    pub ncrPSG: UINT8,        // enable NCR noise algorithm
    pub segaPSG: UINT8,       // enable Sega PSG frequencies (frequency 0 is treated as 1)
    pub stereo: UINT8,        // enable Sega Game Gear stereo

    pub t6w28_tone: *mut u8, // SN-chip that emulates the "tone" part of a T6W28
}
impl SN76496_CFG {
    pub const fn default() -> Self {
        Self {
            _genCfg: DEV_GEN_CFG {
                emuCore: 0,
                srMode: 0,
                flags: 0,
                clock: 0,
                smplRate: 0,
            },
            noiseTaps: 0,
            shiftRegWidth: 0,
            negate: 0,
            clkDiv: 0,
            ncrPSG: 0,
            segaPSG: 0,
            stereo: 0,
            t6w28_tone: std::ptr::null_mut(),
        }
    }
}

#[repr(C)]
pub struct VGM_BASEDEV {
    pub defInf: DEV_INFO,
    pub resmpl: RESMPL_STATE,
    pub linkDev: *mut VGM_BASEDEV,
}
