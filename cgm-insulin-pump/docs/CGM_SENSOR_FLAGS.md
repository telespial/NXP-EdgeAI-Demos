# CGM Sensor Flags Taxonomy And Trigger Logic

Last updated: 2026-02-23

## Scope
Defines sensor-status flag taxonomy and trigger logic for the CGM runtime tuple (`sensor_flags` in `docs/CGM_RUNTIME_CONTRACT.md`).

This document covers:
- clipping/saturation
- dropout
- implausible rate-of-change
- temperature out-of-range
- calibration stale
- drift warning

## Flag Bit Assignments

- `BIT0` (`1u << 0`): `CGM_FLAG_SATURATION`
- `BIT1` (`1u << 1`): `CGM_FLAG_DROPOUT`
- `BIT2` (`1u << 2`): `CGM_FLAG_IMPLAUSIBLE_ROC`
- `BIT3` (`1u << 3`): `CGM_FLAG_TEMP_OUT_OF_RANGE`
- `BIT4` (`1u << 4`): `CGM_FLAG_CAL_STALE`
- `BIT5` (`1u << 5`): `CGM_FLAG_DRIFT_WARN`

## Sampling Assumptions

- Producer cadence: one tuple every `30 s`.
- Set/clear debounce counts below are in samples and can be converted to wall time.

## Trigger Logic

### `CGM_FLAG_SATURATION` (`BIT0`)

Set when either condition holds for `>=2` consecutive samples:
- raw sensor current is within 2% of ADC top/bottom rail, or
- converted glucose estimate is clamped at contract limit (`<=40` or `>=400`) due to sensor-range limit.

Clear when condition absent for `>=4` consecutive samples.

### `CGM_FLAG_DROPOUT` (`BIT1`)

Set when either condition occurs:
- no fresh sensor update for `>90 s`, or
- sample timestamp jumps and at least `2` expected updates are missing.

Clear when fresh updates resume for `>=3` consecutive samples.

### `CGM_FLAG_IMPLAUSIBLE_ROC` (`BIT2`)

Compute `trend_mgdl_min_x100` from current pipeline output.

Set when:
- `abs(trend_mgdl_min_x100) > 350` (`3.50 mg/dL/min`) for `>=2` consecutive samples, and
- not currently in dropout state.

Clear when `abs(trend_mgdl_min_x100) < 250` (`2.50 mg/dL/min`) for `>=4` consecutive samples.

### `CGM_FLAG_TEMP_OUT_OF_RANGE` (`BIT3`)

Set when sensor/skin temperature is outside `[10.0 C, 45.0 C]` for `>=1` sample.

Clear when temperature returns inside `[11.0 C, 44.0 C]` for `>=2` consecutive samples.

Note: clear window includes hysteresis to reduce chatter around boundaries.

### `CGM_FLAG_CAL_STALE` (`BIT4`)

Set when time since last accepted calibration exceeds:
- `7 days` (primary threshold), or
- project-configured calibration TTL, whichever is stricter.

Clear when a valid calibration update is accepted and persisted.

### `CGM_FLAG_DRIFT_WARN` (`BIT5`)

Set when estimated calibration residual or baseline drift exceeds threshold:
- residual error `>15 mg/dL` equivalent for `>=6` consecutive samples, or
- drift slope magnitude exceeds project drift limit for `>=10 minutes`.

Clear when residual/drift remains below 70% of set threshold for `>=20 minutes`.

## Flag Precedence And Interaction

- `DROPOUT` has highest operational priority.
- If `DROPOUT` is active:
  - force predictions invalid (`prediction_15m_mgdl=0`, `prediction_30m_mgdl=0`)
  - freeze trend to last valid value or use sentinel based on runtime policy.
- `Saturation` and `Temp out-of-range` suppress prediction publishing while active.
- `Implausible ROC` alone does not force dropout, but de-rates confidence (`sqi_pct` cap).

## SQI Coupling Guidance

Recommended SQI caps while flags active:
- `DROPOUT`: cap `sqi_pct <= 20`
- `SATURATION`: cap `sqi_pct <= 30`
- `TEMP_OUT_OF_RANGE`: cap `sqi_pct <= 35`
- `IMPLAUSIBLE_ROC`: cap `sqi_pct <= 45`
- `CAL_STALE`: cap `sqi_pct <= 60`
- `DRIFT_WARN`: cap `sqi_pct <= 55`

If multiple flags are active, apply the lowest cap.

## Logging Requirements

At minimum, log on each flag transition:
- timestamp
- flag bitmask before/after
- triggering metric(s) and value(s)
- debounce counter state

This log data is required for later validation and false-positive/chatter analysis.
