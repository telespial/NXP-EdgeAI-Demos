# Smart Pong Demo (FRDM-MCXN947)

3D-look Pong demo with:
- `P0` / `P1` / `P2` modes
- Match target: 11 points
- `P0` endless demo loop (11-point celebration then automatic restart)
- Touch edge-strip paddle controls
- NPU-assisted AI path (TFLM + eIQ Neutron) with CPU fallback
- In-game settings: players, difficulty, AI on/off, new game

Hardware assumptions:
- FRDM-MCXN947
- LCD-PAR-S035 (ST7796S + GT911)
- Optional Accel 4 Click (MIKROE-4630, FXLS8974CF)

Source layout:
- `src/`
- `docs/`

This wrapper CMake references sources from this repository.
