# CGM Runtime Tuple Contract

Last updated: 2026-02-24

## Purpose
Define the canonical CGM runtime tuple for this demo so UI, control logic, logging, and later sensor integration all use the same data contract.

## Tuple Definition

```c
typedef struct
{
    uint16_t glucose_mgdl;
    int16_t trend_mgdl_min_x100;
    uint8_t sqi_pct;
    uint16_t sensor_flags;
    uint16_t prediction_15m_mgdl;
    uint16_t prediction_30m_mgdl;
} cgm_tuple_t;
```

Note:
- `trend_mgdl_min_x100` stores `mg/dL/min` with fixed-point scale x100.
- Example: `+1.25 mg/dL/min` is stored as `125`.

## Field Contract

| Field | Type | Units | Valid range | Invalid/sentinel | Description |
|---|---|---|---|---|---|
| `glucose_mgdl` | `uint16_t` | mg/dL | 40..400 | `0` | Current glucose estimate. |
| `trend_mgdl_min_x100` | `int16_t` | mg/dL/min x100 | -500..500 (-5.00..+5.00) | `INT16_MIN` | Current glucose slope. |
| `sqi_pct` | `uint8_t` | % | 0..100 | `255` | Signal quality index; higher is better. |
| `sensor_flags` | `uint16_t` | bitmask | bitwise | `0` means no flags | Sensor/data quality state flags. |
| `prediction_15m_mgdl` | `uint16_t` | mg/dL | 40..400 | `0` | Predicted glucose at +15 minutes. |
| `prediction_30m_mgdl` | `uint16_t` | mg/dL | 40..400 | `0` | Predicted glucose at +30 minutes. |

## Sensor Flags (Initial Contract)

Bit assignments for `sensor_flags`:

- `BIT0` (`1u << 0`): `CGM_FLAG_SATURATION`
- `BIT1` (`1u << 1`): `CGM_FLAG_DROPOUT`
- `BIT2` (`1u << 2`): `CGM_FLAG_IMPLAUSIBLE_ROC`
- `BIT3` (`1u << 3`): `CGM_FLAG_TEMP_OUT_OF_RANGE`
- `BIT4` (`1u << 4`): `CGM_FLAG_CAL_STALE`
- `BIT5` (`1u << 5`): `CGM_FLAG_DRIFT_WARN`

Remaining bits are reserved for future use.

Detailed taxonomy and trigger logic:
- `docs/CGM_SENSOR_FLAGS.md`

## Update Cadence

- Producer update period target: every `30 s`.
- Consumer behavior:
  - accept tuple if all required fields are valid (non-sentinel)
  - treat tuple as stale if no update for `>90 s`
  - when stale/invalid, keep last valid glucose/trend and suppress prediction-driven alerts

## Runtime Semantics

- If `sqi_pct < 40` or `sensor_flags != 0`, prediction outputs are considered low-confidence.
- UI contract (for later step 11):
  - display glucose and trend always when valid
  - show SQI and active sensor flags
  - visually mark tuple as simulated until live CGM source is integrated

## Runtime Status (Current Firmware)

- Tuple fields above are actively produced/consumed in the runtime CGM path.
- Upstream signal source is still synthetic/demo preprocessing input, not a live dermal CGM sensor feed.
- Prediction quality diagnostics are now exposed in UI:
  - `PRED SCORE` (tolerance hit-rate based)
  - `E#` (matured prediction evaluations consumed)
  - `MAE x.y mg/dL` (blended 15m/30m absolute error magnitude)

## Integration Notes

- Contract wiring is implemented in firmware, but model quality remains under active tuning.
- This demo remains an advisory simulation and is not an autonomous therapy controller.
