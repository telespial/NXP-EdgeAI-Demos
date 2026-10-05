# Hardware Setup

Last updated: 2026-02-25

## Board
- FRDM-MCXN947

## Recommended Connections
- MCU-Link USB connected
- Board power via USB
- Debug console via J17

## Probe Selection
- Prefer probe index `#1`.

## Verified Probe
- Last validated LinkServer probe: `#1` (`UYLKOJI11H2B3`)

## Recovery Flash
- Preferred recovery artifact:
  - `failsafe/edgeai_medical_device_demo_cm33_core0_failsafe_2026-02-25-R11.bin`
- Recovery command:
  - `./tools/flash_failsafe.sh failsafe/edgeai_medical_device_demo_cm33_core0_failsafe_2026-02-25-R11.bin`
