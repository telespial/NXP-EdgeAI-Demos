# Smart Pong Demo (FRDM-MCXN947)

Smart Pong is a 3D-look Pong implementation for FRDM-MCXN947 with LCD-PAR-S035.

![NXP_Smart_Pong](https://github.com/user-attachments/assets/4fef2026-4e27-438b-8b81-2ac7305def1e)

## Real World AI Learning Demonstration
1. Compare three control behaviors in the same system:
   - `HUMAN`: touch-driven paddle control
   - `ALGO`: fixed classic CPU predictor (non-learning baseline)
   - `EdgeAI`: NPU-assisted predictor with adaptive runtime tuning
2. Observe online learning in live play:
   - The adaptive controller updates from rally outcomes (hits/misses), then changes paddle speed, anticipation, and tracking noise.
   - `SKILL` modes allow direct side comparison:
     - `AI/ALGO`: left uses adaptive EdgeAI, right uses fixed ALGO.
     - `ALGO/AI`: left uses fixed ALGO, right uses adaptive EdgeAI.
     - `2AI`: both sides use adaptive EdgeAI.
3. Validate session learning vs persistent learning:
   - `PERSIST ON`: left/right learned profiles carry across new matches and are restored independently from onboard flash after reboot/power cycle.
   - `PERSIST OFF`: learned profile is cleared, forcing a cold-start behavior.
4. Demonstrate deployment-style tradeoffs:
   - NPU path is used when enabled and available, with CPU fallback always present for robustness.
   - Bottom telemetry helps correlate behavior with NPU/fallback timing and latency trends.

## Hardware Components
1. Manufacturer: NXP Semiconductors
   - Name: FRDM-MCXN947 development board
   - Part number: FRDM-MCXN947
2. Manufacturer: NXP Semiconductors
   - Name: 3.5" Parallel TFT LCD shield (ST7796S + GT911)
   - Part number: LCD-PAR-S035
3. Manufacturer: MikroElektronika (sensor IC by NXP)
   - Name: Accel 4 Click (3-axis accelerometer module, FXLS8974CF)
   - Part number: MIKROE-4630

## Gameplay Rules
- Objective: first side to the selected `MATCH` target (`11`, `100`, or `1K`) wins the match.
- Scoring: when a side misses and the ball exits that side, the opponent gains 1 point.
- Ball motion: ball reflects from top and bottom arena walls.
- Paddle collision: ball reflects from paddles with hit-position-based angle shaping ("english").
- Serve behavior: each serve starts from center and is directed toward the side that conceded the previous point.
  - Serve variation: serve launch now uses adaptive AI-style selection that mixes straight, single-axis angle, and diagonal angle patterns with directional bias away from the receiver paddle position.
- Match flow:
  - `P0` (AI vs AI): at the selected `MATCH` target, winner styling + confetti are shown, then the game auto-resets.
  - `P1` and `P2`: at the selected `MATCH` target, winner styling + confetti are shown, then `NEW GAME? YES/NO` is displayed.
  - Absolute cap: at `999` points on either side, confetti/winner styling are shown and the game auto-resets to `0-0` after `30s`.
  - Persistence on reset at the `999` cap follows the `PERSIST` setting:
    - `PERSIST OFF`: reset continues without persisted carry-over.
    - `PERSIST ON`: persisted profile remains active and is restored on reset.
  - Bottom HUD now shows per-side match wins (`WINS`) centered on each side of the net line.

## Controls
- Touch control strips at left/right edges:
  - Left strip controls player 1 paddle.
  - Right strip controls player 2 paddle.
  - Touch `Y` controls paddle height.
  - Touch `X` within the strip controls paddle depth.
- UI top bar is reserved for settings.
- Alternate control sources (for example knob mappings) can be routed through `src/platform/input_hal.c`.

## Settings
- `Players`: `0`, `1`, `2`
- `Difficulty`: `1`, `2`, `3`
- `NPU`: `ON`, `OFF`
- `SKILL`: `2AI`, `AI/ALGO`, `ALGO/AI`
  - `2AI`: both sides adaptive EdgeAI.
  - `AI/ALGO`: left adaptive EdgeAI, right fixed ALGO baseline.
  - `ALGO/AI`: left fixed ALGO baseline, right adaptive EdgeAI.
- `PERSIST`: `ON`, `OFF`
  - `ON`: keep and restore learned AI profiles from flash independently per side.
  - `OFF`: clear learned profiles (including flash snapshot) for true cold-start behavior.
  - Startup default after flash/reboot: `OFF` (persistence is enabled only when user selects `ON`).
- `MATCH`: `11`, `100`, `1K` (`1K` uses a `999` target to match score-display and cap behavior)
  - Startup default after flash/reboot: `100`.
- `TARGET`: `ON`, `OFF`
- `SPEED++`: `ON`, `OFF`
- `New Game`: immediate score reset
  - Also clears `WINS` totals on both sides to `000`.

## AI and NPU Implementation
- This firmware uses an embedded TensorFlow Lite Micro model run via the eIQ Neutron NPU backend.
- Runtime has two AI paths:
  - CPU analytic intercept predictor (deterministic fallback)
  - NPU-assisted predictor path
- NPU path is enabled by `CONFIG_EDGEAI_USE_NPU=y`.
- Inference stack:
  - TensorFlow Lite Micro runtime
  - eIQ Neutron delegate/backend for NPU execution
- AI behavior:
  - Predicts paddle intercept targets (`y_hit`, `z_hit`, `t_hit`) for tracking.
  - Difficulty presets apply reaction-time limits, speed limits, and tracking noise.
  - `AI ON/OFF` controls whether the NPU-assisted path is used; CPU fallback remains available.
- Runtime telemetry:
  - On-screen telemetry shows NPU invoke rate, fallback rate, last inference latency, and moving-average latency.
  - Telemetry is displayed in AI-controlled modes (`P0`, `P1`) when AI is enabled.
- Current embedded NPU model artifact is integrated in `src/npu/` and linked into flash (`.model` section).

## AI Design (ALGO vs EdgeAI)
- Goal in mixed `SKILL` modes: compare a fixed analytic baseline (`ALGO`) against adaptive NPU-assisted control (`EdgeAI`) without hidden cadence bias.
- Side assignment:
  - `AI/ALGO`: left = EdgeAI, right = ALGO
  - `ALGO/AI`: left = ALGO, right = EdgeAI
  - `2AI`: both = EdgeAI
- Control-path design:
  - `ALGO` side uses CPU analytic intercept only.
  - `EdgeAI` side uses TFLM+Neutron predictions with CPU analytic fallback.
  - Mixed modes run EdgeAI target refresh at ALGO-like cadence for fairer side-to-side timing.
  - A disagreement gate compares NPU output to analytic physics and reduces NPU weight when divergence is high.
- Learning scope:
  - Runtime adapts per-side control parameters (`speed_scale`, `noise_scale`, `lead_scale`).
  - Model weights are fixed at runtime (no on-device retraining).
  - With `PERSIST ON`, learned side profiles are restored independently from flash.

## How It Works In This Project
1. Build a 16-value feature vector from current game state (ball, paddles, score, recent hit info) in `ai.c`.
2. Run an embedded TFLM model (`model_ds_cnn_s_npu_data.h`) through the eIQ Neutron backend in `npu_hal_tflm_neutron.cpp`.
3. Decode model output into (`y_hit`, `z_hit`, `t_hit`) signals (via sigmoid), then blend with an analytic physics intercept predictor.
4. Apply a confidence gate: if model output disagrees too much with physics, trust the analytic path more.
5. If NPU is off or inference fails, it falls back fully to CPU analytic prediction.
6. Important: runtime learning here does not retrain model weights; it adapts control parameters (speed/noise/lead) per side over time.

## Detailed AI Runtime Flow
- Per side, the controller computes a paddle target (`target_y`, `target_z`) at a bounded update cadence, then moves with speed limits each frame.
- In `AI/ALGO` and `ALGO/AI`:
  - `ALGO` side uses CPU analytic intercept only.
  - `EdgeAI` side uses NPU prediction plus analytic blend/fallback.
- NPU confidence gating:
  - NPU output is compared to analytic intercept (`y`, `z`, `t` disagreement metric).
  - If disagreement is high, NPU weight is reduced to zero and control follows analytic prediction.
  - This prevents unstable misses from outlier inferences.
- Online tactical learning (per side):
  - Maintains adaptive profile fields: `speed_scale`, `noise_scale`, `lead_scale`.
  - Maintains tactical style state (`center/corner` bias, style trials, style value estimate, last style).
  - Style selection is low-epsilon and reward-updated from hit/miss outcomes.
  - Style influence is maturity-gated so early rallies stay stable and stronger effects appear after enough history.
- Persistence behavior:
  - Startup default is `PERSIST OFF`; flash snapshot is not loaded unless persistence is explicitly turned on in settings.
  - With `PERSIST ON`, left/right profiles are stored independently in flash and restored on startup.
  - Runtime safeguards in both modes: match-level decay toward defaults and auto-rollback to last-good profile after sustained regression.
  - Additional safeguard with `PERSIST ON`: quality-gated flash writes so only stable profiles are persisted.
  - With `PERSIST OFF`, persisted profile snapshot is cleared for cold-start operation.

## Features
- 3D-look arena with depth cues, wall shading, and segmented score digits
- 0P / 1P / 2P modes
- Ball-speed-linked color gradient (red to green)
- 0P accelerometer perturbation of ball trajectory (`vy`, `vz`) for live outcome nudging
- New-game countdown (`3`, `2`, `1`; red/yellow/green) on game start only
- Fixed-timestep simulation
- Real-time NPU telemetry overlay for performance tuning
- `SKILL` setting for side-selectable adaptive AI vs baseline ALGO (`2AI`, `AI/ALGO`, `ALGO/AI`)
- Optional `SPEED++` progression: whenever either side reaches `11, 22, 33, ...`, serve speed target increases by `5%` (compounding) and is capped by runtime speed limits
- Base pacing update: startup serve speed is increased and once either side reaches `6+` points, serve pace ramps progressively (clamped) to keep late-game rallies energetic
- Settings `NEW GAME` now clears both score and `WINS` counters so bottom win values restart from `000`
- AI-driven serve variation: each new serve can be straight or angled (single-axis/diagonal) with dynamic bias based on receiver paddle position

## Build and Flash
1. Bootstrap tools:
```bash
./tools/bootstrap_ubuntu_user.sh
```
2. Prepare MCUX workspace:
```bash
./tools/setup_mcuxsdk_ws.sh
```
3. Build:
```bash
./tools/build_frdmmcxn947.sh debug
```
4. Flash:
```bash
./tools/flash_frdmmcxn947.sh
```

## Project Layout
- `src/`: game logic, rendering, platform HAL, AI/NPU integration
- `docs/`: hardware, build/flash, restore-point, and project description docs
- `tools/`: bootstrap, build, flash, lint, and helper scripts
- `failsafe/`: pinned restore binaries

## Restore Points
- Active golden/failsafe pointer: `docs/failsafe.md`
- Current active artifact: `failsafe/edgeai_smart_pong_demo_cm33_core0_20260324_065426_style_edgeai_fairness_speedup_golden.elf`
- Failsafe flash command:
```bash
FAILSAFE_CONFIRM="$(sed -n '1p' docs/failsafe.md)" ./tools/flash_failsafe.sh
```

## License

See [LICENSE](./LICENSE).
