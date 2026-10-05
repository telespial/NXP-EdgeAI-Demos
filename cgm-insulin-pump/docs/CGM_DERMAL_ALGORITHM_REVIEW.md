# Dermal CGM Signal Processing And Algorithm Stack (Review Draft)

Last updated: 2026-02-23

## Purpose
This document organizes a practical algorithm stack for a dermal, faster-kinetics CGM architecture for later technical and design review.

Core premise:
- Faster dermal kinetics typically favor less phase-smearing smoothing.
- Robust artifact rejection and signal-quality scoring become more important.
- Lag compensation can usually be reduced versus many subcutaneous CGM pipelines.

## 1) Raw Electrochemical Signal To Stable Engineering Units
Goal: Convert AFE samples into a stable, trustworthy sensor-current stream.

Recommended modules:
- ADC conversion and linearization
- Offset removal, gain correction, and reference tracking
- Anti-alias and decimation
  - CIC/boxcar + compensator FIR, or FIR decimator
- Periodic interference rejection
  - 50/60 Hz notch (typically biquad) where applicable
- Impulse noise handling
  - median filter (3-5 samples) or Hampel filter

## 2) Filtering Tuned For Fast Dynamics
Goal: Reduce noise while preserving true rapid rises/falls.

Recommended modules:
- Low-pass IIR (biquad) or EMA
  - tune with shorter time constants than conventional subcutaneous settings
- Savitzky-Golay smoothing
  - useful for smoothing plus derivative estimation with limited lag
- Adaptive filter gating
  - increase smoothing only when signal quality degrades (motion/contact noise)

## 3) Calibration And Compensation (Core CGM Estimation)
Goal: Convert sensor signal into clinically meaningful glucose estimates with compensation for environmental and sensor effects.

Recommended modules:
- Factory calibration mapping
  - per-lot and per-sensor coefficients
  - piecewise linear, polynomial, or log-domain mappings
- Temperature compensation
  - account for enzyme sensitivity and diffusion dependence
- Aging and drift compensation
  - random-walk, exponential, or piecewise baseline models
  - Kalman/state-space models are common for drift vs. noise separation
- Sensitivity-change detection
  - detect gradual degradation and adjust uncertainty, confidence, or end-of-life logic

## 4) Lag And Kinetics Handling
Goal: Compensate kinetics only as needed without introducing unstable look-forward behavior.

Recommended approach for faster dermal kinetics:
- Reduce or eliminate aggressive look-forward compensation
- Keep optional lag/phase correction for site-dependent conditions
  - perfusion shifts, compression effects, placement variability

Common math patterns:
- First-order kinetic models (time constant tau) with deconvolution-style correction
- Kalman filters with explicit delay/lag states

## 5) Signal Quality Index (SQI) And Fault Detection
Goal: Quantify trustworthiness continuously and prevent bad data from driving alarms or decisions.

Recommended checks:
- Saturation/clipping detection
- Open/short and impedance-change heuristics
- Rate-of-change plausibility checks
- Dropout detection with hold-last-value or guarded fallback behavior

SQI feature examples:
- noise power
- derivative stability
- range headroom/margin
- temperature sanity
- continuity/dropout behavior

Typical output tuple:
- glucose estimate
- trend (mg/dL/min)
- SQI/confidence score
- sensor status flags

## 6) Trend, Prediction, And Alert Logic
Goal: Support trend arrows and robust predictive alerts while minimizing chatter.

Recommended modules:
- Derivative estimation
  - finite difference on smoothed data, or Savitzky-Golay derivative
- Short-horizon prediction
  - constrained linear extrapolation or Kalman prediction
- Predictive hypo/hyper alerts
  - gated by confidence/SQI
- Debounce and hysteresis
  - reduce alarm oscillation/chatter

## 7) Performance And Validation Metrics
Goal: Quantify accuracy, lag, stability, and safety behavior for internal and regulatory-style evaluation.

Core analyses:
- MARD
- Clarke and Parkes error grid
- Bland-Altman bias and limits of agreement
- RMSE/MAE by glucose range and ROC bins
- Lag estimation
  - cross-correlation peak shift or fitted kinetic tau
- Time-in-range impact modeling
  - often in-silico for reduced-lag benefit assessment

## 8) Advanced/Optional Transforms
Use selectively due to compute/power budget.

- FFT/spectral diagnostics
  - periodic interference and motion artifact identification
- Wavelet transient detection
  - useful in R&D; often heavy for low-power MCU production paths

## Key Dermal-CGM Design Guidance
If physiologic lag is genuinely shorter, the strongest default stack is:
- lighter smoothing
- stronger artifact handling and SQI gating
- conservative prediction that avoids inventing dynamics

Rationale:
- a faster biological signal path should not be re-slowed by software over-smoothing.

## Suggested Next Review Artifact
For implementation planning, prepare a 30-second cadence reference pipeline with:
- block diagram
- equations-level pseudocode
- candidate filter constants
- SQI feature definitions/threshold strategy
- Kalman-style drift model structure
