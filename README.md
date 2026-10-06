# NXP EdgeAI Demos

This repository collects EdgeAI and embedded-intelligence demonstrations organized by project. Each child directory contains its own README and status record; those files are the source of truth for hardware, implementation state, and validation.

| Demo | Purpose | Status |
| --- | --- | --- |
| [3D printer spool size ToF](./3d-printer-spool-size-tof) | ToF-based spool-size demonstration | See project `STATUS.md` |
| [CGM insulin pump](./cgm-insulin-pump) | Research/demo scope documented in project files | See project `STATUS.md`; not clinical approval |
| [EV charger anomaly](./ev-charger-anomaly) | Anomaly-detection demonstration | See project `STATUS.md` |
| [Package transport adaptive reasoning](./package-transport-adaptive-reasoning) | Package-transport intelligence demonstration | See project `STATUS.md` |
| [Smart Pong](./smart-pong) | Interactive EdgeAI demonstration | See project `STATUS.md` |
| [Sphere](./sphere) | Demonstration project | See project `STATUS.md` |

Choose a child project, read its status and prerequisites, and follow its project-specific instructions. This catalog does not add hardware, toolchain, measurement, or readiness claims that are not present in the child project.

See [LICENSE](./LICENSE) for license terms.

## How the examples relate

The child projects show different EdgeAI integration patterns on FRDM-MCXN947: the ToF demo turns an 8x8 distance sensor into spool-state classifications; EV charger and package-transport projects document anomaly and warning paths; Smart Pong explores adaptive control beside a fixed baseline; and Sphere combines display rendering with accelerometer input. The CGM project is a research/demo platform and is not clinical software. See the [MRD specification](https://github.com/telespial/Machine-Readable-Datasheets-Specs) for structured hardware facts and the [EIL specification](https://github.com/telespial/Embedded-Intelligence-Layer-Specs) for bounded runtime integration.
