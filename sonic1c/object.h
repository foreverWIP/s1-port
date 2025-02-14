#pragma once

#include "system.h"

typedef enum {
  OBJ_NULL,
  OBJ_SONIC,
  OBJ_SPLASH = 8,
  OBJ_SONIC_SPECIAL,
  OBJ_DROWNCOUNT,
  OBJ_POLE,
  OBJ_FLAPDOOR,
  OBJ_SIGNPOST,
  OBJ_TITLESONIC,
  OBJ_TITLEUI,
  OBJ_BRIDGE = 0x11,
  OBJ_SPINNINGLIGHT,
  OBJ_LAVAMAKER,
  OBJ_LAVABALL,
  OBJ_SWINGINGPLATFORM,
  OBJ_HARPOON,
  OBJ_HELIX,
  OBJ_BASICPLATFORM,
  OBJ_COLLAPSELEDGE = 0x1A,
  OBJ_WATERSURFACE,
  OBJ_SCENERY,
  OBJ_MAGICSWITCH,
  OBJ_BALLHOG,
  OBJ_CRABMEAT,
  OBJ_CANNONBALL,
  OBJ_HUD,
  OBJ_BUZZBOMBER,
  OBJ_MISSILE,
  OBJ_MISSILEDISSOLVE,
  OBJ_RINGS,
  OBJ_MONITOR,
  OBJ_EXPLOSIONITEM,
  OBJ_ANIMALS,
  OBJ_POINTS,
  OBJ_AUTODOOR,
  OBJ_CHOPPER,
  OBJ_JAWS,
  OBJ_BURROBOT,
  OBJ_POWERUP,
  OBJ_LARGEGRASS,
  OBJ_GLASSBLOCK,
  OBJ_CHAINSTOMP,
  OBJ_BUTTON,
  OBJ_PUSHBLOCK,
  OBJ_TITLECARD,
  OBJ_GRASSFIRE,
  OBJ_SPIKES,
  OBJ_RINGLOSS,
  OBJ_SHIELDITEM,
  OBJ_GAMEOVERCARD,
  OBJ_GOTTHROUGHCARD,
  OBJ_PURPLEROCK,
  OBJ_SMASHWALL,
  OBJ_BOSSGREENHILL,
  OBJ_PRISON,
  OBJ_EXPLOSIONBOMB,
  OBJ_MOTOBUG,
  OBJ_SPRINGS,
  OBJ_NEWTRON,
  OBJ_ROLLER,
  OBJ_EDGEWALLS,
  OBJ_SIDESTOMP,
  OBJ_MARBLEBRICK,
  OBJ_BUMPER,
  OBJ_BOSSBALL,
  OBJ_WATERSOUND,
  OBJ_VANISHSONIC,
  OBJ_GIANTRING,
  OBJ_GEYSERMAKER,
  OBJ_LAVAGEYSER,
  OBJ_LAVAWALL,
  OBJ_YADRIN = 0x50,
  OBJ_SMASHBLOCK,
  OBJ_MOVINGBLOCK,
  OBJ_COLLAPSEFLOOR,
  OBJ_LAVATAG,
  OBJ_BASARAN,
  OBJ_FLOATINGBLOCK,
  OBJ_SPIKEBALL,
  OBJ_BIGSPIKEBALL,
  OBJ_ELEVATOR,
  OBJ_CIRCLINGPLATFORM,
  OBJ_STAIRCASE,
  OBJ_PYLON,
  OBJ_FAN,
  OBJ_SEESAW,
  OBJ_BOMB,
  OBJ_ORBINAUT,
  OBJ_LABYRINTHBLOCK,
  OBJ_GARGOYLE,
  OBJ_LABYRINTHCONVEY,
  OBJ_BUBBLE,
  OBJ_WATERFALL,
  OBJ_JUNCTION,
  OBJ_RUNNINGDISC,
  OBJ_CONVEYOR,
  OBJ_SPINPLATFORM,
  OBJ_SAWS,
  OBJ_SCRAPSTOMP,
  OBJ_VANISHPLATFORM,
  OBJ_FLAMETHROWER,
  OBJ_ELECTRO,
  OBJ_SPINCONVEY,
  OBJ_GIRDER,
  OBJ_INVISIBARRIER,
  OBJ_TELEPORT,
  OBJ_BOSSMARBLE,
  OBJ_BOSSFIRE,
  OBJ_BOSSSPRINGYARD,
  OBJ_BOSSBLOCK,
  OBJ_BOSSLABYRINTH,
  OBJ_CATERKILLER,
  OBJ_LAMPPOST,
  OBJ_BOSSSTARLIGHT,
  OBJ_BOSSSPIKEBALL,
  OBJ_RINGFLASH,
  OBJ_HIDDENBONUS,
  OBJ_SSRESULT,
  OBJ_SSRCHAOS,
  OBJ_CONTSCRITEM,
  OBJ_CONTSONIC,
  OBJ_SCRAPEGGMAN,
  OBJ_FALSEFLOOR,
  OBJ_EGGMANCYLINDER,
  OBJ_BOSSFINAL,
  OBJ_BOSSPLASMA,
  OBJ_ENDSONIC,
  OBJ_ENDCHAOS,
  OBJ_ENDSTH,
  OBJ_CREDITSTEXT,
  OBJ_ENDEGGMAN,
  OBJ_TRYCHAOS,
};

#define OBJSTRUCTDEF                                                           \
  struct {                                                                     \
    u8 id;                                                                     \
    u8 render_flags;                                                           \
    u16 gfx_setting;                                                           \
    u32 map_addr;                                                              \
    union {                                                                    \
      u32 x;                                                                   \
      struct {                                                                 \
        u16 screen_x;                                                          \
        u16 screen_y;                                                          \
      };                                                                       \
    };                                                                         \
    u32 y;                                                                     \
    s16 velx;                                                                  \
    s16 vely;                                                                  \
    s16 inertia;                                                               \
    u8 height;                                                                 \
    u8 width;                                                                  \
    u8 priority;                                                               \
    u8 action_width;                                                           \
    u8 frame;                                                                  \
    u8 ani_frame;                                                              \
    u8 ani;                                                                    \
    u8 prev_ani;                                                               \
    u8 ani_time_left;                                                          \
    u8 ani_time_delay;                                                         \
    u8 collision_data;                                                         \
    u8 collision_status;                                                       \
    u8 status;                                                                 \
    u8 respawn_index;                                                          \
    u8 action;                                                                 \
    union {                                                                    \
      u8 subaction;                                                            \
      u8 solid_flags;                                                          \
    };                                                                         \
    u16 angle;                                                                 \
    u8 subtype;                                                                \
  }

typedef struct {
  OBJSTRUCTDEF;
  u8 padding[22];
} object;

typedef struct {
  OBJSTRUCTDEF;
  u8 padding[4];
  u16 flash_time;
  u16 invincibility_time;
  u16 speedshoes_time;
  u8 padding2[2];
  bool stick_to_convex;
  u8 padding3[4];
  u8 stand_on_object;
} obj_sonic;