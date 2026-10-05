# ToDo: Smart Pong (FRDM-MCXN947)

Reference material:
- `docs/project_description.md`
- `docs/pong_3D.png`

## Current Snapshot
- [x] Build/flash flow is reproducible in-project (`tools/setup_mcuxsdk_ws.sh`, `tools/build_frdmmcxn947.sh`, `tools/flash_frdmmcxn947.sh`).
- [x] Golden restore point and failsafe restore point are aligned via `docs/failsafe.md`.
- [x] Last known-good status is tracked in `STATUS.md`.
- [x] Current golden/failsafe release artifact: `failsafe/edgeai_smart_pong_demo_cm33_core0_20260225_0100_mixed_skill_balance_confidence_gate_golden.elf`.

## Gameplay + Rendering
- [x] 3D-look arena rendering aligned to style target (walls, floor, center dash, depth cues).
- [x] 0P / 1P / 2P play modes with in-game settings pill (`P`, `D`, `A`, `N`).
- [x] Touch controls use left/right edge strips for non-occluding paddle control.
- [x] Ball speed scaling distributed across all three difficulty levels.
- [x] Ball hue shifts from red toward green as speed increases.
- [x] Help overlay (`?`) shows rules, controls, inspiration credit, and version credit.
- [x] Win condition at 11 points with confetti and winner/loser score styling.
- [x] `P1/P2`: post-win `NEW GAME? YES/NO` dialog.
- [x] `P0`: no dialog; game auto-resets after the 11-point celebration for endless desk demo operation.
- [x] New-game countdown (`3,2,1`) is shown only at game start and skipped for `P0`.

## Physics + Control
- [x] Fixed timestep game loop.
- [x] Paddle-ball collision and depth handling tuned for left/right parity.
- [x] Single-player and two-player paddle behavior tuned to avoid forced recentering.
- [x] Serve direction targets the side that conceded the previous point.

## AI/NPU
- [x] CPU baseline predictor path implemented.
- [x] NPU runtime integration enabled (`CONFIG_EDGEAI_USE_NPU=y`).
- [x] TFLM + eIQ Neutron execution path verified.
- [x] NPU path has CPU fallback behavior.
- [x] In-game AI enable/disable setting integrated.
- [x] Mixed `SKILL` fairness tuning: ALGO side stays CPU-only; EdgeAI side uses confidence-gated NPU+analytic blending with ALGO-like update cadence.

## Optional Backlog
- [ ] Replace placeholder NeutronGraph model with a Pong-specific trained predictor model.
- [ ] Add runtime telemetry overlay toggle (AI invoke cadence, fallback count, frame budget).
- [ ] Add deterministic gameplay regression scenarios for collision edge cases.
