# Hardware (FRDM-MCXN947)

## Required Components
1. Manufacturer: NXP Semiconductors
   - Name: FRDM-MCXN947 development board
   - Part number: FRDM-MCXN947
2. Manufacturer: NXP Semiconductors
   - Name: 3.5" Parallel TFT LCD shield (ST7796S controller, GT911 touch)
   - Part number: LCD-PAR-S035
3. Manufacturer: MikroElektronika (sensor IC by NXP)
   - Name: Accel 4 Click (3-axis accelerometer module, FXLS8974CF)
   - Part number: MIKROE-4630

## Board / Debug
- Probe: MCU-Link (CMSIS-DAP), probe index `#1` in LinkServer
- Debug USB connector: J17

## Input Paths (Platform HAL)
Touch panel (GT911):
- Bus: LPI2C2 / FLEXCOMM2
- INT pin: PIO4_6
- I2C pins: PIO4_0 (`FC2_P0`, SDA), PIO4_1 (`FC2_P1`, SCL)
- Reset pin shared with LCD reset line on the shield

Accelerometer (FXLS8974CF on Accel 4 Click):
- Bus: I2C via FLEXCOMM3
- Device address: `0x18` or `0x19` (ADDR SEL)
- `WHO_AM_I`: `0x86`
