# Restore Points

Last updated: 2026-02-24
Project: `EdgeAI_Package_Transport_Anomaly_demo_NXP_FRDM-MCXN947`

## Active Golden
- Golden tag: `GOLDEN-20260224-024123`
- Lock tag: `FAILSAFE-ACTIVE`
- Binary: `failsafe/edgeai_package_transport_anomaly_demo_cm33_core0_golden_20260224T024123Z.bin`
- Checksum (sha256): `0006e750231b6645e62ce770a21b8e965d80f7f68bedc7a584d5e27e0da3d9ce`

## Failsafe Active
- Binary: `failsafe/edgeai_package_transport_anomaly_demo_cm33_core0_failsafe_active.bin`
- Checksum (sha256): `0006e750231b6645e62ce770a21b8e965d80f7f68bedc7a584d5e27e0da3d9ce`

## Notes
- This golden captures the current validated UI/data stack plus buffered LCD fill optimization:
  - shield-IMU-driven sphere gauge (LSM6DSO16IS)
  - live/record modes with PLAY/RECORD controls
  - shield sensor-hub integration for LIS2MDL/LPS22DF/STTS22H plus SHT40
  - shield temperature source priority for terminal TEMP and left temp bargraph
  - AX/AY/AZ/TEMP scope plotting with FIFO persistence
  - chunk-buffered LCD fill rectangle path in `src/par_lcd_s035.c`
- Restore by flashing `failsafe/edgeai_package_transport_anomaly_demo_cm33_core0_failsafe_active.bin`.
