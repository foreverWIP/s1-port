#pragma once

#include "game.h"

enum {
  ZONE_GHZ,
  ZONE_LZ,
  ZONE_MZ,
  ZONE_SLZ,
  ZONE_SYZ,
  ZONE_SBZ,
  ZONE_END,
  ZONE_SS,
};

enum {
  ZONE16_GHZ = ZONE_GHZ << 8,
  ZONE16_LZ = ZONE_LZ << 8,
  ZONE16_MZ = ZONE_MZ << 8,
  ZONE16_SLZ = ZONE_SLZ << 8,
  ZONE16_SYZ = ZONE_SYZ << 8,
  ZONE16_SBZ = ZONE_SBZ << 8,
  ZONE16_END = ZONE_END << 8,
  ZONE16_SS = ZONE_SS << 8,
};

#define MAX_AIR_SECONDS 30
#define AIR_COUNTDOWN_THRESHOLD 12