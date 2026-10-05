#pragma once

#include <stdint.h>

/* Display geometry. */
#define EDGEAI_LCD_W 480
#define EDGEAI_LCD_H 320

/* Accelerometer normalization.
 * FXLS8974 configuration yields roughly ~512 counts per 1g in the current mode.
 */
#define EDGEAI_ACCEL_MAP_DENOM 512

/* Impact ("bang") detection tuning.
 * Uses a high-pass term: hp = raw - low-pass(raw), in raw sensor counts.
 */
#ifndef EDGEAI_BANG_THRESHOLD
#define EDGEAI_BANG_THRESHOLD 220
#endif

/* Render tile limits (single-blit path). */
#define EDGEAI_TILE_MAX_W 160
#define EDGEAI_TILE_MAX_H 320

/* Fixed-timestep target. */
#ifndef EDGEAI_FIXED_FPS
#define EDGEAI_FIXED_FPS 60
#endif

/* UI: reserve a top bar region for the settings pill. */
#ifndef EDGEAI_UI_BAR_H
#define EDGEAI_UI_BAR_H 32
#endif

/* Touch control strips at the left/right screen edges (normalized width). */
#ifndef EDGEAI_TOUCH_STRIP_W_NORM
#define EDGEAI_TOUCH_STRIP_W_NORM 0.18f
#endif
