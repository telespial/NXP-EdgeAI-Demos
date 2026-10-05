# Project Description: Smart Pong (FRDM-MCXN947)

Goal:
- Implement a 3D-look Pong game on FRDM-MCXN947 with LCD-PAR-S035.

Targets:
- 0P / 1P / 2P: AI vs AI, 1P vs AI, 2P local
- In-game settings UI (`PLAYERS`, `LEVEL`, `NPU`, `SKILL`, `PERSIST`, `MATCH`, `TARGET`, `SPEED++`, `NEW GAME`)
- Touch-first control (GT911 multi-touch) with alternate inputs supported via platform HAL
- Clean separation between platform bring-up, game logic, AI, and rendering

Visual target:
- Match `docs/pong_3D.png`: monochrome box arena, perspective depth cue, center dashed line, segmented digits, soft ball shadow.

Inspiration:
- Pong is a 1972 sports video game developed and published by Atari, Inc. for arcades.
- Original version: Allan Alcorn.
- Conceived by: Nolan Bushnell.

## 3D-Look Rendering Model (MCU-Friendly)
This demo uses:
- 3D game state (`x`, `y`, `z`)
- Lightweight perspective projection into 2D
- Flat-shaded walls/floor with depth cues
- Ball shadow on floor plane

## World Model (Normalized Coordinates)
- `x`: `0` (left paddle plane) to `1` (right paddle plane)
- `y`: `0` (top) to `1` (bottom)
- `z`: `0` (near) to `1` (far)

Ball:
- `pos = (x, y, z)`
- `vel = (vx, vy, vz)`
- `radius = r`

Paddles:
- Plane: `x = constant`
- Center: `(y, z)`
- Size: `(size_y, size_z)`

## Physics (Deterministic, Fixed Timestep)
Loop:
- Fixed timestep at 60 FPS.

Wall collisions:
- Ball reflects at `y` and `z` bounds with radius-aware clamping.

Paddle collisions:
- Collision checked at paddle planes while ball travels toward the relevant side.
- Hit acceptance uses overlap in `(y, z)` with radius padding.
- On hit:
  - Invert `vx`
  - Apply "english" from `y/z` impact offset
  - Apply paddle velocity influence to `vy/vz`

Scoring and match flow:
- Score when ball passes beyond x bounds.
- Match objective: first side to 11 points.
- Serve reset at center with randomized direction toward the side that conceded.
- New-game countdown: `3,2,1` (one second per number), new-game start only.
- `P0` behavior at 11:
  - Winner score styling + confetti
  - No yes/no popup
  - Automatic reset to new game for endless demo loop
- `P1/P2` behavior at 11:
  - Winner score styling + confetti
  - `NEW GAME? YES/NO` popup

## Projection
- `scale = 1 / (1 + z * persp)`
- `sx = cx + (x - 0.5) * world_scale_x * scale`
- `sy = cy + (y - 0.5) * world_scale_y * scale`

Depth cues:
- Ball/paddle size scales with depth.
- Ball color shifts from red toward green as speed rises.

## Input
Touch mapping:
- Left edge strip drives player 1 paddle.
- Right edge strip drives player 2 paddle.
- `touch y -> paddle y`
- `touch x (within strip) -> paddle z`
- UI top-bar region is excluded from paddle control.

Two-player:
- Independent simultaneous control via multi-touch strips.

Accelerometer:
- Accel 4 Click (FXLS8974CF) path available.
- In `P0`, tilt nudges ball `vy/vz` to perturb AI-vs-AI outcomes.

## AI / NPU
CPU baseline AI:
- Analytic intercept solver with bounded reaction behavior.
- Difficulty presets control tracking quality and response.

NPU-assisted path:
- Runtime uses TensorFlow Lite Micro + eIQ Neutron.
- Build-time enable: `CONFIG_EDGEAI_USE_NPU=y`.
- NPU prediction path is integrated with CPU fallback for robustness.
- `AI ON/OFF` in settings toggles NPU-assisted behavior.
- `SKILL` in settings controls side assignment:
  - `2AI`: both paddles use adaptive AI.
  - `AI/ALGO`: left adaptive AI, right fixed ALGO.
  - `ALGO/AI`: left fixed ALGO, right adaptive AI.
- Persistent learning stores left/right AI profiles independently in flash when `PERSIST` is enabled.
- Mixed-mode fairness tuning:
  - ALGO side remains CPU-only in `AI/ALGO` and `ALGO/AI`.
  - EdgeAI side uses ALGO-like target update cadence in mixed modes.
  - NPU output is confidence-gated against analytic prediction to reduce divergence-driven misses.
- Online tactical adaptation:
  - Per-side profile adapts `speed_scale`, `noise_scale`, and `lead_scale` from rally outcomes.
  - Per-side style learner tracks center/corner tactical tendencies (`style_trials`, `style_value_q8`, bias terms).
  - Style influence is maturity-gated to avoid unstable early-game behavior.
  - Current retune reduces exploration early and adds slight mixed-mode competitiveness bias (lower noise, modest speed increase) for fairer ALGO vs EdgeAI representation.

## Repo Architecture
- `src/platform/`: display, input, time, touch, accelerometer, NPU runtime hooks
- `src/game/`: loop, physics, input mapping, modes, AI, rendering
- `tools/`: bootstrap, setup, build, flash, guardrails
- `docs/`: hardware, build/flash, restore-point, and project docs
