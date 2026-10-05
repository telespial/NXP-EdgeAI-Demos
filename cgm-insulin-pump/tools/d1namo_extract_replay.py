#!/usr/bin/env python3
import argparse
import csv
import io
import zipfile
from datetime import datetime, timezone
from pathlib import Path

MMOL_TO_MGDL = 18.0


def parse_args() -> argparse.Namespace:
    p = argparse.ArgumentParser(description="Extract D1NAMO subject data into replay-ready CSVs.")
    p.add_argument("--zip", required=True, dest="zip_path", help="Path to D1NAMO zip")
    p.add_argument("--subject", default="001", help="Subject folder ID, e.g. 001")
    p.add_argument("--out-cgm", required=True, help="Output normalized CGM+insulin replay CSV")
    p.add_argument(
        "--out-trace",
        required=True,
        help="Output firmware-compatible replay trace CSV (current_mA,power_mW,voltage_mV,soc_pct,temp_c)",
    )
    return p.parse_args()


def dt_from_row(date_s: str, time_s: str) -> datetime:
    return datetime.strptime(f"{date_s} {time_s}", "%Y-%m-%d %H:%M:%S").replace(tzinfo=timezone.utc)


def clamp(v: int, lo: int, hi: int) -> int:
    return max(lo, min(hi, v))


def main() -> int:
    args = parse_args()
    zip_path = Path(args.zip_path)
    out_cgm = Path(args.out_cgm)
    out_trace = Path(args.out_trace)

    base = f"diabetes_subset_pictures-glucose-food-insulin/{args.subject}/"
    glucose_name = base + "glucose.csv"
    insulin_name = base + "insulin.csv"

    insulin_events = {}

    with zipfile.ZipFile(zip_path, "r") as zf:
        with zf.open(insulin_name) as f:
            reader = csv.DictReader(io.TextIOWrapper(f, encoding="utf-8", newline=""))
            for row in reader:
                ts = dt_from_row(row["date"], row["time"])
                fast = float(row.get("fast_insulin") or 0.0)
                slow = float(row.get("slow_insulin") or 0.0)
                prev = insulin_events.get(ts, (0.0, 0.0))
                insulin_events[ts] = (prev[0] + fast, prev[1] + slow)

        cgm_rows = []
        with zf.open(glucose_name) as f:
            reader = csv.DictReader(io.TextIOWrapper(f, encoding="utf-8", newline=""))
            for row in reader:
                ts = dt_from_row(row["date"], row["time"])
                mmol = float(row["glucose"])
                mgdl = int(round(mmol * MMOL_TO_MGDL))
                gtype = (row.get("type") or "").strip().lower()
                fast, slow = insulin_events.get(ts, (0.0, 0.0))
                cgm_rows.append(
                    {
                        "ts_iso": ts.strftime("%Y-%m-%dT%H:%M:%SZ"),
                        "epoch_s": int(ts.timestamp()),
                        "glucose_mgdl": mgdl,
                        "glucose_mmol_l": f"{mmol:.3f}",
                        "glucose_type": gtype,
                        "insulin_fast_u": f"{fast:.3f}",
                        "insulin_slow_u": f"{slow:.3f}",
                        "insulin_total_u": f"{(fast + slow):.3f}",
                    }
                )

    if not cgm_rows:
        raise SystemExit("No rows extracted")

    out_cgm.parent.mkdir(parents=True, exist_ok=True)
    with out_cgm.open("w", newline="") as f:
        fieldnames = [
            "ts_iso",
            "epoch_s",
            "glucose_mgdl",
            "glucose_mmol_l",
            "glucose_type",
            "insulin_fast_u",
            "insulin_slow_u",
            "insulin_total_u",
        ]
        w = csv.DictWriter(f, fieldnames=fieldnames)
        w.writeheader()
        w.writerows(cgm_rows)

    # Compatibility trace for existing firmware replay path.
    # Mapping is deterministic for pipeline/testing only, not physiological.
    out_trace.parent.mkdir(parents=True, exist_ok=True)
    with out_trace.open("w", newline="") as f:
        fieldnames = ["current_mA", "power_mW", "voltage_mV", "soc_pct", "temp_c"]
        w = csv.DictWriter(f, fieldnames=fieldnames)
        w.writeheader()

        n = len(cgm_rows)
        for i, row in enumerate(cgm_rows):
            mgdl = int(row["glucose_mgdl"])
            insulin_total = float(row["insulin_total_u"])

            current_mA = clamp((mgdl - 60) * 220, 0, 62000)
            voltage_mV = 24000
            power_mW = clamp((current_mA * voltage_mV) // 100000, 0, 65000)
            soc_pct = clamp(int(round((i * 100.0) / max(1, n - 1))), 0, 100)
            temp_c = clamp(int(round(25 + insulin_total * 0.3)), 20, 60)

            w.writerow(
                {
                    "current_mA": current_mA,
                    "power_mW": power_mW,
                    "voltage_mV": voltage_mV,
                    "soc_pct": soc_pct,
                    "temp_c": temp_c,
                }
            )

    print(f"Wrote {out_cgm} ({len(cgm_rows)} rows)")
    print(f"Wrote {out_trace} ({len(cgm_rows)} rows)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
