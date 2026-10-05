#!/usr/bin/env python3
import argparse
import json
from pathlib import Path


DEFAULT_MODEL_NAME = "package_monitor_v1"
DEFAULT_MODEL_VERSION = "0.0.0"
DEFAULT_EXTENSION_VERSION = "0.1.0"
DEFAULT_WARN = 0.05
DEFAULT_FAIL = 0.15

CHANNEL_TO_DEFINE = {
    "accel_x_g": "EIL_WEIGHT_ACCEL_X",
    "accel_y_g": "EIL_WEIGHT_ACCEL_Y",
    "accel_z_g": "EIL_WEIGHT_ACCEL_Z",
    "temp_c": "EIL_WEIGHT_TEMP_C",
}


def format_f32(value: float) -> str:
    text = f"{value:.6f}".rstrip("0").rstrip(".")
    if "." not in text:
        text = text + ".0"
    return text + "f"


def load_model(path: Path) -> dict:
    with path.open("r", encoding="utf-8") as f:
        return json.load(f)


def extract_profile(model: dict) -> dict:
    name = model.get("name") or DEFAULT_MODEL_NAME
    version = model.get("version") or DEFAULT_MODEL_VERSION
    alerts = model.get("alertThresholds") or {}
    warn = float(alerts.get("warn", DEFAULT_WARN))
    fail = float(alerts.get("fail", DEFAULT_FAIL))

    weights = {
        "EIL_WEIGHT_ACCEL_X": 1.0,
        "EIL_WEIGHT_ACCEL_Y": 1.0,
        "EIL_WEIGHT_ACCEL_Z": 1.0,
        "EIL_WEIGHT_TEMP_C": 0.8,
    }
    for item in model.get("inputs", []):
        channel = item.get("channel")
        define_name = CHANNEL_TO_DEFINE.get(channel)
        if not define_name:
            continue
        weight = item.get("weight")
        if weight is None:
            continue
        weights[define_name] = float(weight)

    return {
        "name": name,
        "version": str(version),
        "extension_version": DEFAULT_EXTENSION_VERSION,
        "warn": warn,
        "fail": fail,
        "weights": weights,
    }


def render_header(profile: dict) -> str:
    return f"""#ifndef EDGEAI_EIL_PROFILE_GENERATED_H
#define EDGEAI_EIL_PROFILE_GENERATED_H

/*
 * Generated profile constants for EIL model integration.
 * Source model: {profile["name"]}
 */

#define EIL_MODEL_NAME "{profile["name"]}"
#define EIL_MODEL_VERSION "{profile["version"]}"
#define EIL_EXTENSION_VERSION "{profile["extension_version"]}"

#define EIL_ALERT_WARN {format_f32(profile["warn"])}
#define EIL_ALERT_FAIL {format_f32(profile["fail"])}

#define EIL_WEIGHT_ACCEL_X {format_f32(profile["weights"]["EIL_WEIGHT_ACCEL_X"])}
#define EIL_WEIGHT_ACCEL_Y {format_f32(profile["weights"]["EIL_WEIGHT_ACCEL_Y"])}
#define EIL_WEIGHT_ACCEL_Z {format_f32(profile["weights"]["EIL_WEIGHT_ACCEL_Z"])}
#define EIL_WEIGHT_TEMP_C {format_f32(profile["weights"]["EIL_WEIGHT_TEMP_C"])}

#endif /* EDGEAI_EIL_PROFILE_GENERATED_H */
"""


def main() -> int:
    parser = argparse.ArgumentParser(description="Import EIL model.config.json into firmware profile header.")
    parser.add_argument("--model", required=True, help="Path to model.config.json")
    parser.add_argument(
        "--out",
        default="src/eil_profile_generated.h",
        help="Output header path (default: src/eil_profile_generated.h)",
    )
    args = parser.parse_args()

    model_path = Path(args.model)
    out_path = Path(args.out)

    model = load_model(model_path)
    profile = extract_profile(model)
    out_path.write_text(render_header(profile), encoding="ascii")
    print(f"Wrote {out_path} from {model_path}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
