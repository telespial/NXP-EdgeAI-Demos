# Restore Points

Last updated: 2026-02-23
Project: `EdgeAI_Package_Transport_Anomaly_demo_NXP_FRDM-MCXN947`

## Active Golden
- Golden tag: `GOLDEN-20260223-161638`
- Lock tag: `FAILSAFE-20260223-161638`
- Binary: `failsafe/edgeai_package_transport_anomaly_demo_cm33_core0_golden_20260223T161638Z.bin`
- Checksum (sha256): `2304af425c539cc63ddd56a6e0166c1697f43d1f1c0b744bf32be32ff8b78bd3`

## Failsafe Active
- Binary: `failsafe/edgeai_package_transport_anomaly_demo_cm33_core0_failsafe_active.bin`
- Checksum (sha256): `2304af425c539cc63ddd56a6e0166c1697f43d1f1c0b744bf32be32ff8b78bd3`

## Notes
- This golden captures the current validated UI/data stack plus buffered LCD fill optimization:
  - shield-IMU-driven sphere gauge (LSM6DSO16IS)
  - live/record modes with PLAY/RECORD controls
  - shield sensor-hub integration for LIS2MDL/LPS22DF/STTS22H plus SHT40
  - shield temperature source priority for terminal TEMP and left temp bargraph
  - AX/AY/AZ/TEMP scope plotting with FIFO persistence
  - chunk-buffered LCD fill rectangle path in `src/par_lcd_s035.c`
- Restore by flashing `failsafe/edgeai_package_transport_anomaly_demo_cm33_core0_failsafe_active.bin`.
