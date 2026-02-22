# Temporary Combined State

Last updated: 2026-02-22
Scope: consolidated transition brief for evolving the package-transport runtime into an infusion-pump derivative while retaining validated platform infrastructure.

## Executive Snapshot
- Current build/flash baseline: PASS (`frdmmcxn947/cm33_core0`, app `edgeai_package_transport_anomaly_demo`)
- Golden baseline: `GOLDEN-20260222-152829`
- Active failsafe: `failsafe/edgeai_package_transport_anomaly_demo_cm33_core0_failsafe_active.bin`
- Transition direction: reuse core runtime and replace domain profile + decision semantics for medical infusion safety supervision.

## Reuse-First Architecture Decision
The following firmware blocks remain foundational and should not be rewritten for the derivative:
- elapsed-time scheduler and cooperative tick cadence
- sensor data ingestion and streaming framework
- external flash record/playback pipeline and timeline controls
- live/train/operator state machine and persistent settings model
- alert visibility hold and priority arbitration mechanics

This preserves verified timing and operational behavior while minimizing regression surface.

## Infusion-Pump Derivative Target (Planned)
Primary outcomes:
- motor status supervision with anomaly scoring and predicted wear/damage risk
- over/under temperature detection plus predictive trend warning
- wearable motion context (sleep/sit/stand/walk/run/stairs up/down using barometric trend)
- inversion detection from gyro/orientation channels
- drop/impact detection with possible-damage escalation path

## EIL Model Strategy (Planned)
Model authoring path:
- build model profile in `embedded-intelligence-layer`
- set infusion template as bundled default:
  - `EdgeAI_Medical_Infusion_Pump_Adaptive_Reasoning_demo_NXP_FRDM-MCXN947.config.json`
- export/import via existing profile flow:
  - extension export package -> `tools/import_eil_profile.py` -> `src/eil_profile_generated.h`

Integration contract:
- firmware continues deterministic authority for safety gating
- model contributes explainable predictive/watchover signals via `status + reason code + score`

## Planned Validation Evidence
- replay scenario matrix covering normal, wear drift, thermal drift, inversion, and drop events
- UART and flash evidence bundles with timestamped `AS/RC/SC` fields
- log-cadence checks at `1/10/50 Hz`
- release gates tied to failsafe boot verification and synchronized state docs
