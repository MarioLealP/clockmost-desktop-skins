# SDDM — Endfield skin (from ds-lock-v2)

Real SDDM theme (Qt6, SDDM >= 0.21) reproducing the approved mockup
`ref/mocks/components/ds-lock-v2.html` ("lock v2"). Colours, sizes and type are
taken from that file, `ds-shell.css` and the `.clock` plate in
`ds-topbar-v2.html`. WORKLOG decision honoured: **no floor print** (Mario
disliked it), the yellow clock plate is **identical to the top bar's**, minimal
centred plate (circle avatar, password).

Target: CachyOS (Arch), KDE Plasma 6.8, Wayland. This is a login-greeter skin —
see the "Could not match" list item 1 for the lock-screen caveat.

## Files and where they install

| File in this repo | Installs to | What it is |
|---|---|---|
| `endfield/metadata.desktop` | `/usr/share/sddm/themes/endfield/metadata.desktop` | SDDM theme metadata (MainScript/ConfigFile) |
| `endfield/theme.conf` | `/usr/share/sddm/themes/endfield/theme.conf` | theme settings read by Main.qml via SDDM's `config` object |
| `endfield/Main.qml` | `/usr/share/sddm/themes/endfield/Main.qml` | the whole greeter UI |
| `endfield/topo-floor.svg` | `/usr/share/sddm/themes/endfield/topo-floor.svg` | the mockup's topo floor artwork (copy of `ref/mocks/src/assets/topo-floor.svg`) — ground |
| `endfield/topo-floor-dark.svg` | `/usr/share/sddm/themes/endfield/topo-floor-dark.svg` | same artwork with the strokes forced to black — the yellow plate's topo texture (reproduces CSS `filter: brightness(0); mix-blend-mode: multiply`) |
| `endfield/README.md` | (docs only — optional to copy) | short install/activate/test instructions |

Install:

```sh
sudo cp -r sddm/endfield /usr/share/sddm/themes/endfield
```

## Apply / reload

Drop-in config (do not edit `/etc/sddm.conf` directly):

```ini
# /etc/sddm.conf.d/10-endfield.conf
[Theme]
Current=endfield
```

Reload = the greeter has to restart. `systemctl restart sddm` does it **but kills
the running session**, so apply it from a TTY or before logging in. Changes to
the theme files also only show up after the greeter restarts. Test without any of
that:

```sh
sddm-greeter-qt6 --test-mode --theme /usr/share/sddm/themes/endfield
# or, before installing:
sddm-greeter-qt6 --test-mode --theme /path/to/sddm/endfield
```

## Fonts needed

| Role | Mockup CSS | Theme default (`theme.conf`) | Get it |
|---|---|---|---|
| mono (titles, clock, small print) | `Consolas, "Cascadia Mono", ui-monospace` | `JetBrains Mono` | `pacman -S ttf-jetbrains-mono` |
| body (user name) | `"Segoe UI", system-ui` | `Inter` | Inter from `extra` (`pacman -Ss inter` — package name varies: `inter-font`/`inter`) |

Change `monoFont` / `bodyFont` / `hostName` in `theme.conf` without touching QML.

## Mapping table — mockup element → real setting

| Mockup (ds-lock-v2) | Real SDDM theme |
|---|---|
| `.cp` yellow clock plate 320x96, top-centre, same as top bar's | `Main.qml` `plate` Item: 320x96 anchored top-centre; live `Qt.formatDateTime` every second |
| `.cp .t` "20<s>:</s>41" | live HH + dim ":" + mm (colon opacity .55, like the mockup) |
| `.cp .sec` ":37" | live seconds |
| `.cp .d` "MON ▮ 12 OCT 2026" | live short weekday + date (uppercased), barcode rebuilt from the mockup's repeating-linear-gradient pattern |
| `.cp .id` "CLK-0912 · UTC+1" | `CLK-0912` kept as static print; `UTC±h` computed from the system timezone |
| `.cp .topo/.hatch/.dots2` plate textures | `topo-floor-dark.svg` at opacity .22; hatch + dots painted on a Canvas with the mockup's exact gradients |
| `.cptb` tri-band 320x5 | three Rectangles: `#FFFA00` / `#3FD0E8` / `#ff1aac` at 33.3/33.3/33.4% (the one tri-band of the screen) |
| `.stage` ground | `#0c0c0d` + `topo-floor.svg` bottom band (46% height, cover-crop like CSS `100% 46%`) + the stage's gradient veil |
| `.hud` centred plate at top 30% | `hud` Item, `y = root.height * 0.30`, width 440 |
| `.av` circle avatar "BE" | `Repeater` over `userModel`: face icon if the account has one (drawn clipped to a circle on a Canvas), else initials on `#FFFA00`; ring = 4px `#0b0b0c` + 1px `rgba(241,241,244,.3)` as in the mockup |
| `.nm` "benylin" | flat `ComboBox` over `userModel` (`textRole: "name"`) styled as the name line — the user picker lives in the mockup's name slot |
| `.st` "LOCKED 20:39 · 2 MIN AGO" | flat `ComboBox` over `sessionModel` — a greeter has no lock time, so this slot is the session picker (styled as the same micro line) |
| `.pw` password field (48px, square, `rgba(10,11,13,.7)` + 1px `rgba(255,255,255,.22)`) | `TextField` with `echoMode: Password`, `passwordCharacter: "•"`, same box; Enter or the arrow logs in via `sddm.login(user, password, sessionIndex)` |
| `.pw b` yellow `›››` | static `Text` in `#FFFA00`, 700 14px mono |
| `.pw .go` arrow button | 30x30 `#f1f1f4` square with the mockup's arrow path, same action as Enter |
| `.hint` `↵` + `UNLOCK` | square keycap + micro print; after a failed login the micro becomes `ACCESS DENIED` in `#d91e36` (mockup has no error state) |
| `.tl` `CLOCKMOST` + barcode + `DT-01 · CACHYOS · PLASMA 6.8` | static print; wordmark = `hostName` from `theme.conf` (default `CLOCKMOST`) |
| `.tr` `TANG OK · VAULT OK / ETH 1G · 42MS / LISBON · 18°C CLEAR` | static print (house style: small print is texture) |
| `.bl` `SDDM · TTY1 · LK-2039` | static print |
| `.br` `US` cell | keyboard-layout cell: shows the current layout from SDDM's `keyboard` proxy, click cycles it (guarded code — see live checks) |
| `.br` ethernet cell | decorative status cell only (the greeter cannot touch NetworkManager) |
| `.br` power cell | `sddm.powerOff()` gated on `sddm.canPowerOff` (dimmed when unavailable) |

## Could not match (be honest)

1. **It is a greeter, not the lock screen.** The mockup is a lock screen; SDDM is
   the login greeter. Plasma's Win+L locker is kscreenlocker (look-and-feel
   QML), a different app — this theme cannot style it. The greeter does appear on
   logout/switch-user and on boot, so the look lands on every "login" surface.
2. **"LOCKED 20:39 · 2 MIN AGO"** — a greeter knows no lock time. The slot is
   repurposed as the session picker (mapping table above).
3. **Now-playing block** (`.np`: "Glassy Sky / SAPPHIRE · PAUSED") — omitted. The
   SDDM greeter has no MPRIS/Spotify access, and the work order's element list
   does not include it. The bottom-left corner keeps the `.bl` small print.
4. **Backdrop blur** on the password field (`backdrop-filter: blur(12px)`) — not
   available in stock QtQuick; the field is flat `rgba(10,11,13,.7)` (visually
   close over the calm ground).
5. **Plate drop shadow** (`0 10px 30px rgba(0,0,0,.45)`) — dropped shadows would
   need `QtQuick.Effects` (MultiEffect); omitted rather than risk the import.
6. **The stage's two soft radial glows** — QtQuick has no radial gradient without
   Qt5Compat/Effects; the ground is `#0c0c0d` + topo + veil without the glows.
7. **CSS blend modes** — `mix-blend-mode: multiply` + `filter: brightness(0)` on
   the plate topo is reproduced with the recoloured `topo-floor-dark.svg` at
   opacity .22; the *result* matches, the technique is not CSS.
8. **Corner telemetry / weather / serials** (TANG, VAULT, ETH 1G · 42MS,
   LISBON · 18°C, CLK-0912, LK-2039, DT-01) are **static print**, as the house
   style intends ("small print is texture, not content"). A greeter cannot query
   weather, network latency or vault status. Only the UTC offset on the plate is
   live.
9. **Font metrics**: JetBrains Mono is not Consolas and Inter is not Segoe UI, so
   glyph widths differ slightly from the mockup screenshots. QML letter-spacing
   is in pixels, so every `.em` value is converted exactly (`em × font size`).
10. **Rounded glow-free dots**: the mockup's soft radial-gradient dot grids are
    redrawn as crisp 1.2px-radius circles (pitch 6px) — same pattern, slightly
    harder edges.
11. **Empty password field** shows only the `›››` prompt; the mockup shows filled
    dots as an example filled state.
12. **Uppercase day/month strings** follow the Qt locale of the greeter (e.g.
    "OCT" vs a localised month name).
13. **`↵` glyph** (U+21B5) needs a font that carries it (JetBrains Mono does; a
    fallback font may render a box).

## Needs a live check (written blind — no SDDM here)

- `sddm.login(user, password, sessionIndex)` signature (3rd arg as session index).
- `sddm.canPowerOff` / `sddm.powerOff()`.
- `loginFailed` signal on the `sddm` proxy (used for the error line). If the
  signal is named differently, only that one line misbehaves — everything else
  works.
- The `keyboard` proxy API (`layouts`, `currentLayout`, `switchToNextLayout`) —
  all access is guarded; if the shape differs the `US` cell simply shows `US`
  and does nothing.
- `theme.conf` keys via the `config` object — guarded with the same defaults in
  code.
- Which metadata group this SDDM build reads — `metadata.desktop` provides both
  `[SddmGreeterTheme]` and `[Desktop Entry]`.
- `sddm-greeter-qt6 --test-mode --theme ...` on CachyOS (binary name per the
  work order).
- Whether the greeter resizes the root object to the screen (design size is
  1920x1080; the layout is anchored/centred so it should adapt either way).
- SVG rendering size of `topo-floor.svg` (it declares `width/height="100%"`;
  Qt normally falls back to the 1340x200 viewBox and then cover-crops like CSS).

## Checks

Checked at review (2026-10-13): `theme.conf`/`metadata.desktop` parse as INI, both SVGs
are well-formed XML, the dark recolor touches all 12 strokes, and `Main.qml` brackets
balance. `Main.qml` itself is unverified until it runs in `sddm-greeter-qt6 --test-mode`.
