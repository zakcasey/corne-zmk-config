# Agent notes for this Miryoku fork

This repo is a Corne-only fork of Miryoku ZMK. Personal layout lives in
`miryoku/custom_config.h`. That file is the source of truth.

## Keep the docs in sync

When you change any layer binding, layer list, thumb hold, home-row mod, or
timing, update **both** references in the same turn:

| Reference | Path |
|-----------|------|
| Markdown reference | `SETUP.md` |
| Interactive canvas | `~/.cursor/projects/Users-zakcasey-Documents-projects-keyboard-miryoku-zmk/canvases/corne-layer-reference.canvas.tsx` |

The canvas is outside the git repo. Cursor stores it next to this workspace.
Edit that file directly. Do not recreate it elsewhere.

### Required checklist after a layout edit

1. Edit `miryoku/custom_config.h` (or `config/corne.keymap` / behaviours).
2. Update matching layer diagrams and notes in `SETUP.md`.
3. Update the matching `LAYERS` entry in the canvas.
4. Run the drift check:

```bash
python3 scripts/check-layer-docs.py
```

5. Do not stop while the check reports drift.

### What the check covers

`scripts/check-layer-docs.py` compares each usable Miryoku position on every
layer in `custom_config.h` against the canvas. It fails when:

- a bound key is shown as empty (`—`) on the canvas, or
- an empty key (`U_NA` / `U_NU`) still has a label on the canvas, or
- a layer is missing, or a layer has the wrong key count.

It does not judge whether a label string is perfect (`Cmd` vs `Command`).
Still update labels so humans can find the key.

## Do not re-enable these without asking

- Key emulation combos (`MIRYOKU_KLUDGE_*COMBOS`) — wrong for a full Corne.
- Layer lock / remote layer-jump keys (`&u_to_U_*` except `&u_to_U_BASE`).
- Dead Extra / Tap / Button layers.

## Build

The firmware workflow is `workflow_dispatch` only. Push does not build. Start
the job by hand from the GitHub Actions tab, or tell the user to do that.
