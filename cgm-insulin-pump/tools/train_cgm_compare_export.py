#!/usr/bin/env python3
import json
import math
from pathlib import Path

import numpy as np
import pandas as pd
from sklearn.ensemble import GradientBoostingRegressor, RandomForestRegressor
from sklearn.linear_model import ElasticNet, HuberRegressor, Ridge
from sklearn.metrics import mean_absolute_error, mean_squared_error, r2_score


FEATURES = [
    "glucose_mgdl",
    "glucose_lag1",
    "glucose_lag2",
    "glucose_lag3",
    "glucose_lag6",
    "glucose_lag9",
    "glucose_lag12",
    "delta1",
    "delta3",
    "delta6",
    "accel13",
    "roll3",
    "roll6",
    "roll12",
    "tod_sin",
    "tod_cos",
]


def make_features(df: pd.DataFrame) -> pd.DataFrame:
    out = df.copy()
    out["glucose_lag1"] = out["glucose_mgdl"].shift(1)
    out["glucose_lag2"] = out["glucose_mgdl"].shift(2)
    out["glucose_lag3"] = out["glucose_mgdl"].shift(3)
    out["glucose_lag6"] = out["glucose_mgdl"].shift(6)
    out["glucose_lag9"] = out["glucose_mgdl"].shift(9)
    out["glucose_lag12"] = out["glucose_mgdl"].shift(12)
    out["delta1"] = out["glucose_mgdl"] - out["glucose_lag1"]
    out["delta3"] = out["glucose_mgdl"] - out["glucose_lag3"]
    out["delta6"] = out["glucose_mgdl"] - out["glucose_lag6"]
    out["accel13"] = out["delta1"] - out["delta3"]
    out["roll3"] = out["glucose_mgdl"].rolling(3).mean()
    out["roll6"] = out["glucose_mgdl"].rolling(6).mean()
    out["roll12"] = out["glucose_mgdl"].rolling(12).mean()

    sec_day = out["epoch_s"] % 86400
    ang = 2.0 * math.pi * sec_day / 86400.0
    out["tod_sin"] = np.sin(ang)
    out["tod_cos"] = np.cos(ang)

    out["delta15"] = out["glucose_mgdl"].shift(-3) - out["glucose_mgdl"]
    out["target15"] = out["glucose_mgdl"].shift(-3)
    out = out.dropna().reset_index(drop=True)
    return out


def tol_hit_rate(y_true_abs: np.ndarray, y_pred_abs: np.ndarray, tol_pct: float) -> float:
    tol = np.maximum(1.0, np.abs(y_pred_abs) * tol_pct)
    hit = np.abs(y_true_abs - y_pred_abs) <= tol
    return float(np.mean(hit))


def fit_compare(train_df: pd.DataFrame, test_df: pd.DataFrame):
    X_train = train_df[FEATURES].to_numpy(dtype=np.float64)
    X_test = test_df[FEATURES].to_numpy(dtype=np.float64)
    y_train_delta = train_df["delta15"].to_numpy(dtype=np.float64)
    y_test_delta = test_df["delta15"].to_numpy(dtype=np.float64)
    y_test_abs = test_df["target15"].to_numpy(dtype=np.float64)
    g_test = test_df["glucose_mgdl"].to_numpy(dtype=np.float64)

    models = {
        "ridge": Ridge(alpha=1.0, random_state=947),
        "elastic_net": ElasticNet(alpha=0.001, l1_ratio=0.15, random_state=947, max_iter=10000),
        "huber": HuberRegressor(alpha=0.0005, epsilon=1.35, max_iter=1000),
        "random_forest": RandomForestRegressor(
            n_estimators=160, max_depth=10, min_samples_leaf=3, random_state=947, n_jobs=-1
        ),
        "gradient_boosting": GradientBoostingRegressor(
            n_estimators=260, learning_rate=0.04, max_depth=3, random_state=947
        ),
    }

    rows = []
    fitted = {}
    for name, model in models.items():
        model.fit(X_train, y_train_delta)
        pred_delta = model.predict(X_test)
        pred_abs = g_test + pred_delta
        pred_abs = np.clip(pred_abs, 40.0, 400.0)
        mae = mean_absolute_error(y_test_abs, pred_abs)
        rmse = math.sqrt(mean_squared_error(y_test_abs, pred_abs))
        r2 = r2_score(y_test_abs, pred_abs)
        h05 = tol_hit_rate(y_test_abs, pred_abs, 0.05)
        h08 = tol_hit_rate(y_test_abs, pred_abs, 0.08)
        h10 = tol_hit_rate(y_test_abs, pred_abs, 0.10)
        rows.append(
            {
                "name": name,
                "mae": float(mae),
                "rmse": float(rmse),
                "r2": float(r2),
                "hit_05": float(h05),
                "hit_08": float(h08),
                "hit_10": float(h10),
                "composite": float((1.0 - h10) * 0.55 + (mae / 25.0) * 0.45),
            }
        )
        fitted[name] = model

    rows = sorted(rows, key=lambda x: (x["composite"], x["mae"]))
    best_name = rows[0]["name"]

    embeddable = {"ridge", "elastic_net", "huber"}
    emb_rows = [r for r in rows if r["name"] in embeddable]
    best_embed_name = emb_rows[0]["name"] if emb_rows else best_name

    return rows, best_name, best_embed_name, fitted[best_embed_name]


def export_linear_header(model, train_df: pd.DataFrame, out_h: Path):
    X = train_df[FEATURES].to_numpy(dtype=np.float64)
    med = np.nanmedian(X, axis=0)
    mean = np.nanmean(X, axis=0)
    std = np.nanstd(X, axis=0)
    std = np.where(std < 1e-9, 1.0, std)

    if hasattr(model, "coef_"):
        coef = np.asarray(model.coef_, dtype=np.float64).reshape(-1)
        intercept = float(model.intercept_)
    else:
        raise RuntimeError("Selected export model is not linear")

    lines = []
    lines.append("#ifndef CGM_MODEL_GENERATED_H")
    lines.append("#define CGM_MODEL_GENERATED_H")
    lines.append("")
    lines.append("#include <stdint.h>")
    lines.append("")
    lines.append(f"#define CGM_MODEL_GENERATED_FEATURE_COUNT {len(FEATURES)}u")
    lines.append("")
    lines.append("/* Auto-generated by tools/train_cgm_compare_export.py */")
    lines.append("/* Predicts +15m delta (mg/dL); runtime converts to absolute. */")
    lines.append("")

    def arr(name, vals):
        lines.append(f"static const float {name}[CGM_MODEL_GENERATED_FEATURE_COUNT] = {{")
        chunk = []

        def cfloat(x: float) -> str:
            s = f"{float(x):.9g}"
            if ("." not in s) and ("e" not in s) and ("E" not in s):
                s += ".0"
            return s + "f"

        for i, v in enumerate(vals):
            chunk.append(cfloat(v))
            if len(chunk) == 6 or i == len(vals) - 1:
                lines.append("    " + ", ".join(chunk) + ",")
                chunk = []
        lines.append("};")
        lines.append("")

    arr("kCgmModelGenMedian", med)
    arr("kCgmModelGenMean", mean)
    arr("kCgmModelGenScale", std)
    arr("kCgmModelGenCoeff", coef)
    lines.append(f"static const float kCgmModelGenIntercept = {intercept:.9g}f;")
    lines.append("")
    lines.append("#endif")
    out_h.write_text("\n".join(lines) + "\n", encoding="utf-8")


def main():
    root = Path(__file__).resolve().parents[1]
    train_csv = root / "data" / "d1namo_train_excl001.csv"
    test_csv = root / "data" / "d1namo_test_subject001.csv"
    out_metrics = root / "model" / "cgm_compare_metrics.json"
    out_header = root / "src" / "cgm_model_generated.h"

    train_df = make_features(pd.read_csv(train_csv))
    test_df = make_features(pd.read_csv(test_csv))
    rows, best_name, best_embed_name, best_embed_model = fit_compare(train_df, test_df)
    export_linear_header(best_embed_model, train_df, out_header)

    payload = {
        "train_csv": str(train_csv.relative_to(root)),
        "test_csv": str(test_csv.relative_to(root)),
        "features": FEATURES,
        "rows_train": int(len(train_df)),
        "rows_test": int(len(test_df)),
        "ranked_models": rows,
        "best_model": best_name,
        "best_embeddable_model": best_embed_name,
        "exported_header": str(out_header.relative_to(root)),
    }
    out_metrics.write_text(json.dumps(payload, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({"best": best_name, "best_embeddable": best_embed_name, "rows": len(rows)}, indent=2))


if __name__ == "__main__":
    main()
