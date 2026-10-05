# TODO

Last updated: 2026-02-22
Project: `EdgeAI_Package_Transport_Adaptive_Reasoning_demo_NXP_FRDM-MCXN947`

## Priority 0 (Release Hygiene)
- [ ] Keep `STATUS.md`, `docs/PROJECT_STATE.md`, and restore docs synchronized on every golden cut.
- [ ] Keep command trace complete in `docs/COMMAND_LOG.md` for every build/flash/release action.
- [ ] Verify `failsafe/edgeai_package_transport_anomaly_demo_cm33_core0_failsafe_active.bin` boots and reaches UI before tagging release.

## Priority 1 (Runtime Validation)
- [ ] Run end-to-end record/replay test at `1 Hz`, `10 Hz`, and `50 Hz` to verify flash cadence follows `LOG HZ`.
- [ ] Capture UART evidence showing persisted `AS/RC/SC` fields during short transient warnings.
- [ ] Validate help popup on hardware for full alphabet render (A-Z) across both pages.
- [ ] Confirm settings persistence after power cycle: mode, run, AI, limits, log rate.

## Priority 2 (Data/Forensics)
- [ ] Add explicit UART flash dump command output with signed fields and timestamp (`ts_ds`) for quick audit.
- [ ] Save one known-good capture bundle:
  - config/profile used
  - UART log
  - flash dump sample
  - expected warning sequence
- [ ] Document retention expectations by log rate using measured sample counts.

## Priority 3 (UX Polish)
- [ ] Keep settings/help text concise and font-safe for the 5x7 renderer.
- [ ] Re-check popup layouts after any text edits (no overlap, no clipping, no stale artifacts).
- [ ] Keep touch targets consistent for all up/down and confirm buttons.

## Deferred (Post v0.1)
- [ ] Additional demo profiles in extension and firmware import path.
- [ ] Deeper training workflow automation and packaged validation scripts.
