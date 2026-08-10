#!/usr/bin/env python3
"""Fail if the Corne canvas drifts from miryoku/custom_config.h.

Compares empty vs bound positions on every layer. Exit 0 when in sync,
exit 1 when the canvas is stale or missing.

Usage:
  python3 scripts/check-layer-docs.py
  CANVAS_PATH=/path/to/corne-layer-reference.canvas.tsx python3 scripts/check-layer-docs.py
"""

from __future__ import annotations

import os
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
CONFIG = ROOT / "miryoku" / "custom_config.h"
DEFAULT_CANVAS = (
    Path.home()
    / ".cursor"
    / "projects"
    / "Users-zakcasey-Documents-projects-keyboard-miryoku-zmk"
    / "canvases"
    / "corne-layer-reference.canvas.tsx"
)
EMPTY = {"U_NA", "U_NU", "U_NP"}
LAYER_ORDER = ["BASE", "NAV", "MOUSE", "MEDIA", "NUM", "SYM", "FUN"]


def split_bindings(body: str) -> list[str]:
    out: list[str] = []
    depth = 0
    cur = ""
    for ch in body:
        if ch == "(":
            depth += 1
        elif ch == ")":
            depth -= 1
        if ch == "," and depth == 0:
            out.append(cur.strip())
            cur = ""
        else:
            cur += ch
    if cur.strip():
        out.append(cur.strip())
    return out


def parse_config_layers(text: str) -> dict[str, list[str]]:
    layers: dict[str, list[str]] = {}
    for name in LAYER_ORDER:
        match = re.search(
            rf"#define MIRYOKU_LAYER_{name} \\\n(.*?)(?:\n\n|\Z)",
            text,
            re.S,
        )
        if not match:
            raise SystemExit(f"missing MIRYOKU_LAYER_{name} in {CONFIG}")
        body = match.group(1).replace("\\\n", " ").replace("\n", " ")
        bindings = split_bindings(body)
        if len(bindings) != 40:
            raise SystemExit(
                f"{name}: expected 40 Miryoku slots, found {len(bindings)}"
            )
        # Drop the four U_NP corners. Keep 3x10 alpha grid + 6 thumbs.
        layers[name] = bindings[0:30] + bindings[32:38]
    return layers


def parse_canvas_layers(text: str) -> dict[str, list[str]]:
    blocks = re.findall(
        r'id: "([A-Z]+)",.*?rows: \[(.*?)\],\s*thumbs: \[(.*?)\],\s*\},',
        text,
        re.S,
    )
    layers: dict[str, list[str]] = {}
    for layer_id, rows_src, thumbs_src in blocks:
        labels: list[str] = []
        for src in (rows_src, thumbs_src):
            for match in re.finditer(
                r'\bNIL\b|k\(\s*("(?:[^"\\]|\\.)*")',
                src,
            ):
                if match.group(0) == "NIL":
                    labels.append("—")
                else:
                    labels.append(match.group(1)[1:-1].replace("\\\\", "\\"))
        layers[layer_id] = labels
    return layers


def slot_name(index: int) -> str:
    if index < 30:
        return f"r{index // 10}c{index % 10}"
    return f"thumb{index - 30}"


def main() -> int:
    canvas_path = Path(os.environ.get("CANVAS_PATH", DEFAULT_CANVAS))
    if not CONFIG.is_file():
        print(f"error: config not found: {CONFIG}", file=sys.stderr)
        return 1
    if not canvas_path.is_file():
        print(f"error: canvas not found: {canvas_path}", file=sys.stderr)
        print(
            "Set CANVAS_PATH if the canvas lives somewhere else.",
            file=sys.stderr,
        )
        return 1

    config_layers = parse_config_layers(CONFIG.read_text())
    canvas_layers = parse_canvas_layers(canvas_path.read_text())

    errors: list[str] = []
    for name in LAYER_ORDER:
        if name not in canvas_layers:
            errors.append(f"{name}: missing from canvas")
            continue
        cfg = config_layers[name]
        canv = canvas_layers[name]
        if len(canv) != 36:
            errors.append(f"{name}: canvas has {len(canv)} keys, expected 36")
            continue
        for i, (binding, label) in enumerate(zip(cfg, canv)):
            cfg_empty = binding in EMPTY
            canv_empty = label == "—"
            if cfg_empty != canv_empty:
                errors.append(
                    f"{name} {slot_name(i)}: "
                    f"config={binding!r} canvas={label!r}"
                )

    extra = sorted(set(canvas_layers) - set(LAYER_ORDER))
    for name in extra:
        errors.append(f"{name}: unexpected layer on canvas")

    if errors:
        print(f"canvas drift: {len(errors)} problem(s)")
        print(f"config: {CONFIG}")
        print(f"canvas: {canvas_path}")
        for err in errors:
            print(f"  - {err}")
        print(
            "\nUpdate SETUP.md and the canvas, then re-run "
            "python3 scripts/check-layer-docs.py"
        )
        return 1

    print("ok: canvas matches custom_config.h empty/bound layout")
    print(f"config: {CONFIG}")
    print(f"canvas: {canvas_path}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
