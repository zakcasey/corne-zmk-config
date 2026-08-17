# My Corne setup

Personal notes for my Corne keyboard, built on the Miryoku layout.

## Hardware

| Item         | Value                                 |
| ------------ | ------------------------------------- |
| Keyboard     | Typeractive Corne, split              |
| Controller   | nice!nano v2 (`nice_nano@2.0.0//zmk`) |
| Display      | nice!view, `nice_view_gem` screen     |
| Alpha layout | Colemak-DH                            |
| Host         | macOS, US English input source        |
| Debounce     | 3 ms press and release                |

## Where to make changes

| Purpose                                             | File                                                                   |
| --------------------------------------------------- | ---------------------------------------------------------------------- |
| All layer contents and layer list                   | `miryoku/custom_config.h`                                              |
| Home-row mods, combos, debounce, keymap entry point | `config/corne.keymap`                                                  |
| Thumb layer-tap timing                              | `miryoku/miryoku_behaviors.dtsi`                                       |
| Kconfig, for example sleep and the screens          | `config/corne.conf`                                                    |
| Physical key mapping for the Corne                  | `miryoku/mapping/42/corne.h`                                           |
| Build job                                           | `.github/workflows/build-typeractive-corne-nice_nano_v2-nice_view.yml` |

Make personal changes in `custom_config.h` only. The files in `miryoku/miryoku_babel/`
are generated. `custom_config.h` now overrides every layer, so
edits in `miryoku_babel/miryoku_layer_alternatives.h` have no effect.

After a layout change, update `SETUP.md` and the Corne canvas, then run:

```bash
python3 scripts/check-layer-docs.py
```

See `AGENTS.md` for the full sync checklist.

## Build

A push does not start the build. The workflow trigger is `workflow_dispatch`,
so you must start the build by hand:

1. Open the Actions tab on GitHub.
2. Select "Build Typeractive corne nice_nano_v2 nice_view".
3. Click "Run workflow".

The job attaches the `.uf2` files as artifacts. Copy each file to the matching
half in bootloader mode.

To build on each push, add a `push` trigger to the workflow file.

Put all Kconfig settings in `config/corne.conf`. ZMK reads that one file for both
halves. Do not put a `kconfig:` value in the workflow file: the workflow writes it
to `config/corne_left.conf`, and ZMK ignores that file while `corne.conf` exists.

## Screens

The two nice!view screens use the [nice-view-gem](https://github.com/M165437/nice-view-gem)
module in place of the stock `nice_view` shield. Three things make this work:

| Item                                        | Where               |
| ------------------------------------------- | ------------------- |
| `CONFIG_ZMK_DISPLAY=y`                      | `config/corne.conf` |
| `nice_view_gem` in both shield names        | the build workflow  |
| `modules: '["M165437/nice-view-gem/main"]'` | the build workflow  |

No shield turns the display on by itself. Without `CONFIG_ZMK_DISPLAY=y`, both
screens stay blank.

The left half is the central half, so it shows the battery, the connection, the
active layer, and a words-per-minute gauge. The right half is a peripheral, so it
shows the battery and an animation.

The layer names come from `MIRYOKU_LAYER_LIST` in `custom_config.h`. Miryoku
writes each name into the keymap as a `display-name`, so the left screen shows
`Base`, `Nav`, `Raycast`, `Mac`, `Num`, `Sym`, and `Fun`.

The module revision must match the ZMK revision. `main.yml` clones ZMK `main`, so
the module uses its `main` branch. If you ever pin ZMK to a release, pin the
module to the matching release.

Options you can add to `config/corne.conf`:

| Option                                     | Effect                                    |
| ------------------------------------------ | ----------------------------------------- |
| `CONFIG_NICE_VIEW_WIDGET_INVERTED=y`       | White on black                            |
| `CONFIG_NICE_VIEW_GEM_ANIMATION=n`         | Stop the animation, to save battery       |
| `CONFIG_NICE_VIEW_GEM_ANIMATION_MS=96000`  | Make the animation much slower            |
| `CONFIG_NICE_VIEW_GEM_WPM_FIXED_RANGE_MAX` | Set the top of the words-per-minute gauge |
| `CONFIG_ZMK_DISPLAY_BLANK_ON_IDLE=y`       | Clear the screen when the board is idle   |

The module sets `CONFIG_ZMK_DISPLAY_BLANK_ON_IDLE=n`, so the last image stays on
the screen until deep sleep. ZMK still calls displays a proof of concept. A known
problem can leave a screen blank after a power cutoff
([zmk#674](https://github.com/zmkfirmware/zmk/issues/674)), so watch the screens
after the first flash. Deep sleep is on with a 15 minute timeout.

## Layers

Seven layers. Each thumb key gives one letter on tap and one layer on hold.

| Index | Name    | Hold key  | Purpose                                   |
| ----- | ------- | --------- | ----------------------------------------- |
| 0     | Base    | —         | Letters with home-row mods                |
| 1     | Nav     | Space     | Inverted-T arrows and caps word           |
| 2     | Raycast | Tab       | Hyper shortcuts for Raycast               |
| 3     | Mac     | Esc       | macOS utilities and media                 |
| 4     | Num     | Backspace | Numbers and brackets                      |
| 5     | Sym     | Return    | Symbols, each on the letter that names it |
| 6     | Fun     | Delete    | Function keys                             |

The stock Miryoku layers Extra, Tap, and Button are removed. No key can reach them.

`->Base` = double tap to go to the Base layer. `Boot` = double tap to enter the
bootloader.

**No layer can lock.** Stock Miryoku puts a `Lock` key and a layer jump key on
the bottom row of each hold layer. Both use `&to`, so the layer stays on after
you release the thumb key. They sit under the alphas you type most, and a double
tap there locked a layer by accident. All of them are removed. `->Base` is the
only `&to` key left. Every layer is now momentary: it is on only while you hold
its thumb key.

The outer pinky columns of the Corne are not used. They are `&none` on all layers.
This board has five columns per half. Left home row: A R S T G. Left bottom row:
Z X C D V. For Figma, hold **Z** (under A), then scroll.

### Base

```
 Q     W     F     P     B   |   J     L     U     Y     '
 A     R     S     T     G   |   M     N     E     I     O
 Z     X     C     D     V   |   K     H     ,     .     /
          Esc  Spc  Tab      |  Ret  Bspc  Del
```

Home-row mods, from pinky to index:

| Hand  | Key | Mod     |
| ----- | --- | ------- |
| Left  | A   | Control |
| Left  | R   | Option  |
| Left  | S   | Command |
| Left  | T   | Shift   |
| Right | N   | Shift   |
| Right | E   | Command |
| Right | I   | Option  |
| Right | O   | Control |

`X` and `.` give Right Option on hold. `Z` gives Shift on hold. Tap `Z` for the
letter. Hold `Z` for Figma: it sits under `A`, the same seat as Shift on a
normal keyboard.

Shift on `T`, `N` and `Z` is a simple hold-tap: Shift goes down on press. The
tapping term is 100 ms, so a hold still becomes Shift even if the press-time
path fails. `Z` is not in a combo.

Ctrl, Opt and Cmd still need the other hand. `Cmd+C` uses Cmd on `E`, because
`C` is on the left hand.

If you hold two mods on the same hand, both stay available. `Cmd+Shift+T` works
with Cmd on `S` and Shift on `T`. This is the effect of `hold-trigger-on-release`. All of these keys obey the other-hand
rule. See "Home-row mods and timing".

Thumb keys, tap and hold:

| Key     | Tap       | Hold          |
| ------- | --------- | ------------- |
| Left 1  | Esc       | Mac layer     |
| Left 2  | Space     | Nav layer     |
| Left 3  | Tab       | Raycast layer |
| Right 1 | Return    | Sym layer     |
| Right 2 | Backspace | Num layer     |
| Right 3 | Delete    | Fun layer     |

### Nav — hold Space

```
 --    --    --    --     --   |   --    --     Up     --    --
Ctrl   Opt   Cmd   Shift  --   |  Caps  Left   Down   Right  --
 --    AltGr --    --     --   |   --    --     --     --    --
           --   --   --        |   --    --     --
```

The arrows make an **inverted T**. `Up` sits directly above `Down`, so the middle
finger works both. `Left` is on the index finger and `Right` is on the ring finger.

`Caps` gives Caps Word. Shift+`Caps` gives Caps Lock. The `G` + `M` combo gives
Caps Word with no layer hold. See "Combos".

**Keep the left-hand mod row.** Base-layer home-row mods do not work on this
layer, because Nav replaces those keys. The mod row is the only way to send
Shift+Arrow to select text, Opt+Arrow to move by word, or Cmd+Arrow to go to the
start or the end of a line.

This layer was trimmed. The clipboard row (Undo, Cut, Copy, Paste, Redo), `Ins`,
`Home`, `End`, `PgUp`, `PgDn`, `Repeat` and the right thumb keys are now free.
Cmd+Z, Cmd+X, Cmd+C and Cmd+V still work on the Base layer.

`Boot` was also removed from this layer. A stray press of the left top pinky
while you hold Space put the board into the bootloader. `Boot` is still on the
Mac, Num, Sym, and Fun layers.

### Raycast — hold Tab

Every letter sends **Hyper** (Command + Control + Option + Shift) plus that letter.
Letter positions are the same as the Base layer.

```
Hyper+ Q   W   F   P   B   |   J   L   U   Y   '
Hyper+ A   R   S   T   G   |   M   N   E   I   O
Hyper+ Z   X   C   D   V   |   K   H   ,   .   /
```

Set each shortcut in Raycast: Settings > Extensions or Applications > Hotkey.

| Shortcut | Opens |
| -------- | ----- |
| Hyper+Q  |       |
| Hyper+W  |       |
| Hyper+F  |       |
| Hyper+P  |       |
| Hyper+B  |       |
| Hyper+J  |       |
| Hyper+L  |       |
| Hyper+U  |       |
| Hyper+Y  |       |
| Hyper+'  |       |
| Hyper+A  |       |
| Hyper+R  |       |
| Hyper+S  |       |
| Hyper+T  |       |
| Hyper+G  |       |
| Hyper+M  |       |
| Hyper+N  |       |
| Hyper+E  |       |
| Hyper+I  |       |
| Hyper+O  |       |
| Hyper+Z  |       |
| Hyper+X  |       |
| Hyper+C  |       |
| Hyper+D  |       |
| Hyper+V  |       |
| Hyper+K  |       |
| Hyper+H  |       |
| Hyper+,  |       |
| Hyper+.  |       |
| Hyper+/  |       |

Fill in this table when you add a Raycast hotkey.

### Mac — hold Esc

```
Boot   --    --   ->Base  --   |  --     --       VolUp  --     --
Ctrl   Opt   Cmd   Shift  --   |  --     PrevSpc  VolDn  NextSpc --
 --    AltGr Shot  Dict   --   |  Out    BT0      BT1    BT2    BT3
           --   --   --        |  Stop   Play     Mute
```

| Key | Function |
|-----|----------|
| `Shot` | Screenshot of a selected area (Cmd+Shift+4). This sits on the Base `C` key. |
| `Dict` | Dictation. Sends F13. |
| `VolDn` / `VolUp` | Volume down on `E`, volume up on `U` (directly above `E`) |
| `PrevSpc` / `NextSpc` | Previous Space on `N`, next Space on `I` |
| `BT0` to `BT3` | Select Bluetooth profile 0 to 3 |
| `Out` | Change the output between USB and Bluetooth |

For `Dict` to work, open System Settings > Keyboard > Dictation > Shortcut >
Customize, and press the Mac layer `D` key.

These Bluetooth keys are the only keys that can reach the radio. Without them you
cannot pair a second computer, and you cannot clear a bad pairing. Keep them bound.

To pair a new computer, hold Esc, then tap a free profile. To clear a profile,
hold Esc and Shift together, then tap that profile. `Out` sends the keystrokes
over USB instead of Bluetooth. Shift plus `Out` forces USB.

### Num — hold Backspace

```
 [     7     8     9     ]     |   --   ->Base  --    --    Boot
 ;     4     5     6     =     |   --   Shift   Cmd   Opt   Ctrl
 `     1     2     3     \     |   --   --      --    AltGr  --
             .     0     -     |   --    --     --
```

### Sym — hold Return

```
 {     &     +     %     }     |   --   Pipe    ^   ->Base  Boot
 @     :     *     ~     £     |   -     <      =     >      --
 --    !     --    $     --    |   --    #      --   AltGr   --
             (     )     _     |        --     --     --
```

The diagram writes the `|` key as `Pipe`, because `|` separates the two halves.

Most symbols sit on the letter that names them. Two go by shape:

```
A -> @  At               P -> %  Percent
D -> $  Dollar           S -> *  Star
E -> =  Equals           T -> ~  Tilde
G -> £  GBP              X -> !  eXclamation
H -> #  Hash
M -> -  Minus            L -> |  the letter looks like a pipe
                         U -> ^  the caret points up
```

`{`, `}`, `&`, `+` and the three thumb keys keep their stock positions, because
those symbols have no letter of their own.

`<`, `=` and `>` sit side by side on `N`, `E` and `I`, in reading order. This
makes `<=` and `>=` an inward roll on the index, middle and ring fingers.

Free on this layer: `Z`, `C`, `V`, `J`, `O`, `K`, `,` and `/`.

**This layer no longer mirrors Num.** Before this change, every left-hand Sym key
was the Shift twin of the Num key in the same position: `[`/`{`, `;`/`:`, `` ` ``/`~`
and so on. Six keys now break that rule. The mnemonic wins instead.

**The mirror mods are gone from the right hand**, because symbols use those keys.
So you cannot hold Command or Shift on this layer. Num keeps its own mod row, so
press Command with `E` on the Num layer for zoom, where `-` and `=` also live.

The right-hand symbols are on the same hand as the Return thumb key. This works,
because `u_lt` has no `hold-trigger-key-positions` list. Only the home-row mods
limit which hand may follow.

`->Base` sits on `Y` here, not on `L`, because `|` took `L`. Num and Fun still put
it on `L`.

The `£` key sends Option+3. This is correct for the macOS **US English** input
source. If you change to the British input source, change `LA(N3)` to `LS(N3)`
in `custom_config.h`.

### Fun — hold Delete

```
F12   F7    F8    F9    PrtSc  |   --   ->Base  --     --    Boot
F11   F4    F5    F6    ScrLk  |   --   Shift   Cmd    Opt    Ctrl
F10   F1    F2    F3    Pause  |   --   --      --     AltGr  --
            Menu  Spc   Tab    |   --    --     --
```

## Combos

A combo sends one behavior when you press two keys at the same time. Combos are
in `config/corne.keymap`, because they use raw Corne key positions.

| Press together | Result    | Layer |
| -------------- | --------- | ----- |
| `G` + `M`      | Caps Word | Base  |

`G` and `M` are the inner index keys, one on each hand. Press them together to
start Caps Word, and again to stop it. Caps Word also stops at a space or at any
key that is not a letter. This is a shortcut for the Nav layer `Caps` key, which
stays available.

This combo used to sit on `T` + `N`. Those keys are home-row Shift. A combo on a
hold-tap waits for the combo timeout before the mod can start. A mouse cannot
end that wait, so Shift+scroll never saw Shift. `G` and `M` are plain letters.

These settings stop a false trigger:

| Setting                 | Value | Effect                                           |
| ----------------------- | ----- | ------------------------------------------------ |
| `timeout-ms`            | 35    | Both keys must go down within 35 ms              |
| `require-prior-idle-ms` | 150   | No combo if you pressed a key in the last 150 ms |
| `layers`                | Base  | The combo is off on all other layers             |

The idle rule stops the combo in the middle of a word. It also means that you
must pause before you use the combo.

How to tune:

- The combo fires when you do not want it: increase `require-prior-idle-ms`, or
  decrease `timeout-ms` to 30.
- The combo is hard to get: increase `timeout-ms` to 45.

This is a personal combo. It is not one of the Miryoku key emulation combos,
which stay off. See "Notes and open items".

## Home-row mods and timing

There are four home-row mod behaviors in `config/corne.keymap`. `u_hml` and
`u_hmr` are Ctrl, Opt and Cmd. `u_hmls` and `u_hmrs` are Shift. The key position
lists apply to the Corne only.

`u_hml` and `u_hmr` have a `hold-trigger-key-positions` list. Ctrl, Opt and Cmd
trigger **only** if the next key you press is on the other hand or on a thumb.
A roll between two keys on the same hand can never make those mods.

A mouse is not a keyboard key, so it cannot trigger that list. Shift on `T`,
`N` and `Z` uses `u_hmls` / `u_hmrs` with no positional list. The flavor is
`hold-preferred`, the tapping term is 100 ms, and `hold-while-undecided` sends
Shift on press. For Figma, hold `Z` (under `A`), then scroll.

Ctrl, Opt and Cmd stay on `u_hml` / `u_hmr`. A short Cmd or Opt tap can open a
macOS menu. Do not add `hold-while-undecided` to those keys.

`hold-trigger-on-release` keeps same-hand mod combinations available on Ctrl,
Opt and Cmd. To get Cmd+Shift, hold `S` and `T` together, then press the other
key.

| Setting                  | Value        | Effect                                               |
| ------------------------ | ------------ | ---------------------------------------------------- |
| `flavor` (Ctrl/Opt/Cmd)  | balanced     | Send the mod as soon as an other-hand key is pressed |
| `tapping-term-ms` (same) | 280          | Hold time to get those mods with no other key        |
| `flavor` (Shift)         | hold-preferred | Send Shift if you hold, or if another key is pressed |
| `tapping-term-ms` (Shift)| 100          | Hold time for Shift with no other key                |
| `quick-tap-ms`           | 175, not Shift | Tap again in this time to repeat the letter        |
| `require-prior-idle-ms`  | 150, not Shift | No mod if you typed in the last 150 ms             |
| `hold-while-undecided`   | Shift        | Send Shift on press, so a mouse can see it           |

Thumb layer taps use `u_lt` in `miryoku/miryoku_behaviors.dtsi`.

| Setting                 | Value    | Effect                                                          |
| ----------------------- | -------- | --------------------------------------------------------------- |
| `flavor`                | balanced | Start the layer as soon as an other key is pressed and released |
| `tapping-term-ms`       | 200      | Hold time to get the layer with no other key                    |
| `quick-tap-ms`          | 175      | Tap again in this time to repeat the letter                     |
| `require-prior-idle-ms` | 100      | No layer if you typed in the last 100 ms                        |

The flavor was `tap-preferred`. That made every layer need a full 200 ms hold
before the layer became available. `balanced` removes that delay.

How to tune:

- Mods still fire when you do not want them: increase `require-prior-idle-ms`.
- Mods are slow or hard to get: decrease `require-prior-idle-ms` first, then
  decrease `tapping-term-ms`.
- Fast double letters fail: increase `quick-tap-ms`.
- A fast word plus Space opens the Nav layer: increase `require-prior-idle-ms`
  on `u_lt`, or set its flavor back to `tap-preferred`.

Change one value at a time. Use it for a few days before you change it again.

## Notes and open items

- The modifier order is now Ctrl-Opt-Cmd-Shift on every layer. This agrees with
  the Base layer home-row mods.
- `u_mt` and `u_lt_fast` are removed. `u_hml` and `u_hmr` replaced `u_mt`, and
  no key ever used `u_lt_fast`. The `U_MT` macro is removed too. If you delete a
  layer override in `custom_config.h`, a stock alternative layer will expand and
  the build will fail because `U_MT` is gone. Define it again if that happens.
- The Raycast layer sends 29 Hyper combinations. The hotkey table above is empty,
  so most of those keys probably do nothing. Fill in the table, or replace the
  keys you do not use.
- Free positions (`U_NU`): nineteen on Nav after the trim, nine on Mac, four each
  on Num and Fun, and five on Sym.
- Key emulation combos are **not** enabled. The Corne has all 36 keys that
  the layout needs, so the combos are not necessary. They exist only for
  keyboards with a missing key.
