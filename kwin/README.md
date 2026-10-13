# kwin - Endfield window decoration (skin order S-kwin)

Real KWin files translated from the approved mockup `ref/mocks/components/ds-window-v2.html`
(+ house style `ref/mocks/components/ds-shell.css`, rules `ref/mocks/orders/STYLE.md`,
decisions in `ref/mocks/WORKLOG.md` -> "Window frame = v2"). Target: CachyOS (Arch),
KDE Plasma 6.8, KWin on Wayland. Nothing here was seen on a screen - colours/sizes below
are the mockup's exact values; everything that could not be proven offline is listed under
"Could not match" and "Needs live check".

## What was made

| File in this repo | Installs to | What it is |
|---|---|---|
| `aurorae/Endfield/metadata.json` | `~/.local/share/aurorae/themes/Endfield/metadata.json` | theme metadata (name "Endfield") |
| `aurorae/Endfield/decoration.svg` | `~/.local/share/aurorae/themes/Endfield/decoration.svg` | frame + button artwork (Aurorae SVG) |
| `aurorae/Endfield/EndfieldDecorationrc` | `~/.local/share/aurorae/themes/Endfield/Endfieldrc` (**rename**, see theme README) | title height 34, title padding, 1px borders, 40x34 button cells |
| `aurorae/Endfield/minimize.svg` `maximize.svg` `close.svg` | (same folder, optional) | the mockup's exact glyphs standalone; Aurorae does not load them - the glyphs are embedded in `decoration.svg` |
| `aurorae/Endfield/README.md` | - | install + select for the theme itself |

That's the whole order's scope: KWin can only be skinned at the decoration level here.
The window body (frosted glass, top motif) is the app's own surface + the Blur effect,
not the decoration - see the mapping table.

## Install / apply / reload

```sh
mkdir -p ~/.local/share/aurorae/themes
cp -r aurorae/Endfield ~/.local/share/aurorae/themes/
mv ~/.local/share/aurorae/themes/Endfield/EndfieldDecorationrc \
   ~/.local/share/aurorae/themes/Endfield/Endfieldrc
```

Select: **System Settings -> Window Decorations** (Plasma 6: under *Colors & Themes*;
page also opens via `systemsettings kcm_kwindecoration`) -> **Endfield**.
Buttons min/max/close right, nothing left (Titlebar Buttons tab, or `~/.config/kwinrc`):

```ini
[org.kde.kdecoration2]
ButtonsOnLeft=
ButtonsOnRight=IAX
```

Reload after manual edits:

```sh
qdbus6 org.kde.KWin /KWin reconfigure    # or: qdbus org.kde.KWin /KWin reconfigure
```

## Mapping table (mockup element -> real setting)

| Mockup (ds-window-v2 / ds-shell.css) | Value | Real setting |
|---|---|---|
| `.wtop` title bar height | 34px | `Endfieldrc` `TitleHeight=34` |
| `.wtop` padding-left / gap | 14px / 10px | `TitleEdgeLeft=27` (14 + 3px tick + 10 gap), `TitleEdgeRight=10` |
| `.win` border, square corners | 1px `rgba(255,255,255,.10)` unfocused / `.22` focused | `Border*=1` + border art in `decoration.svg` (`*-active` = #fff @ .22, `*-inactive` = #fff @ .10) |
| `.wtop` fill | `rgba(10,11,13,.55)` | titlebar art in `decoration.svg` (#0a0b0d @ .55). The translucency shows the wallpaper only if the Blur effect covers the window - see "Could not match" |
| `.wtop::after` hairline under title | 1px `rgba(255,255,255,.07)`, full width | bottom edge of the titlebar art in `decoration.svg` |
| `.win.focus .wtitle::before` yellow tick | 3x11px `#FFFA00` at x=14 | baked into `top-left-active` art at x=15,y=12.5 (1px frame + 14px inset). Focused-only, as in the mockup |
| `.wtitle` text | 700 10px mono, UPPERCASE, letter-spacing .26em, `#c9ccd3` -> focused `#f1f1f4`, unfocused x.5 | **not settable from the theme** - KWin draws the title with a system font; see "Could not match". Font to install: **JetBrains Mono** |
| `.wb` button cells | 40x34px, no gap, transparent | `ButtonWidth=40` `ButtonHeight=34` `ButtonSpacing=0` |
| minimize glyph `M5 12h14` | 11px, stroke 3 | `minimize-*` elements in `decoration.svg` (and `minimize.svg`) |
| maximize glyph square `5,5 14x14` | 11px, stroke 3 | `maximize-*` elements (and `maximize.svg`) |
| close glyph rule-18 X (empty centre) | 11px, stroke 3 | `close-*` elements (and `close.svg`) |
| `.wb` icon colour focused / unfocused | `#c9ccd3` / `#7d8089` @ .5 | `*-active` / `*-inactive` button art |
| `.wb.x-hover` close hover | bg `#d91e36`, glyph `#fff` | `close-hover` / `close-pressed` art |
| `.wb.hover` other hover (house style) | bg `rgba(255,255,255,.07)`, glyph `#fff` | `minimize/maximize/restore-hover` art |
| `.win.blur .wtitle, .wb { opacity:.5 }` | dimmed when unfocused | inactive button art at .5; title dimming depends on KWin's inactive title colour - "Could not match" |
| min/max/close top-right order | I A X | kwinrc `ButtonsOnRight=IAX` |
| 8px tiled gaps / 8px from edges | 8px | **KWin tiling setting, not a decoration** - Plasma 6 tiling gap config (live check; not part of this theme) |
| `.win` drop shadow `0 24px 60px rgba(0,0,0,.55)` (focused) | soft, no glow | KWin supplies decoration shadows; exact blur/spread not tunable from what I could verify - live check |
| `.win.max` fullscreen app | no frame | KWin does this natively when maximized (border drops) |

Colours taken verbatim (house style hex): yellow `#FFFA00`, crimson `#d91e36`, ink `#f1f1f4`,
ink2 `#c9ccd3`, dim `#7d8089`, titlebar `#0a0b0d` @ 55%, hairline/border white @ 7% / 10% / 22%.

## Fonts needed

- **JetBrains Mono** (mono - titles, labels; Consolas-like).
- **Inter** (body - Segoe-like; used by apps, not by this decoration).

## Could not match (what KWin/the mockup cannot agree on)

1. **Title font/size/weight/letterspacing.** The mockup is 700 10px mono, uppercase,
   .26em tracking. Aurorae draws the title with a system font; I found no rc font keys I
   could trust and did not invent any. Set JetBrains Mono in System Settings -> Fonts;
   size/weight/tracking will not be exactly 10px/.26em. (If the rc really has font keys,
   the live check will show them; add them to `Endfieldrc`.)
2. **Title colour.** `#c9ccd3` / `#f1f1f4` are drawn by KWin, not the SVG. No verified rc
   keys for active/inactive title text colours - KWin's defaults (or the colour scheme's
   `InactiveForeground`/`ForegroundActive` in `kde/EndfieldDark.colors`) will be used.
3. **Tick only when focused, title reflow.** In the mockup the unfocused title sits at
   x=14 (no tick), focused at x=27 (tick + gap). Aurorae has one title inset for both
   states; chosen 27px so the tick never overlaps the text. Cost: unfocused titles are
   indented 13px more than the mockup.
4. **Frosted glass body** (`rgba(13,14,16,.86)` + `blur(28px)`) and the **faint topo motif**
   in the focused window's corner. Both live in the client area - the decoration cannot
   paint them. Body translucency = the app (e.g. Kitty's `background_opacity`); blur = the
   KWin Blur effect; the topo motif would need per-app support and is dropped here.
5. **Snap preview** (yellow `#FFFA00` half-screen zone) and **8px tiling gaps** - KWin
   window-management settings, not decoration; gaps in Plasma 6 come from the tiling
   configuration which I could not verify offline.
6. **Pressed button state.** The mockup (layout-only) has none; `*-pressed` art reuses the
   hover art.
7. **Restore glyph.** The mockup only draws a maximize square; `restore-*` reuses it
   (maximized windows will show the same square instead of a restore glyph).
8. **No menu button** in the mockup - fine in KWin (`ButtonsOnLeft=` empty), listed here
   because Aurorae themes often ship one.

## Needs live check (in order)

1. `decoration.svg` element ids (frame `top-left-active` ... scheme + button
   `close-active`-style ids). This is my best reconstruction of the Aurorae SVG spec; no
   KWin source was available in this environment to confirm. Empty frame = wrong ids.
2. `Endfieldrc` file name on install (`Endfieldrc` vs `themerc`) and `[General]` group.
3. Whether the Window Decorations page picks up `metadata.json` (vs wanting
   `metadata.desktop`).
4. Inactive title colour behaviour (point 2 above).
5. Shadow look and tiling gaps (points 5/8 above).
