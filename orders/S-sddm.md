# Order S-sddm: real skin files for `sddm` from the approved mockup

Source of truth (read-only): `~/ref/mocks/components/ds-lock-v2.html` (open it, read ALL its CSS/HTML), the house style
`~/ref/mocks/components/ds-shell.css` and rules `~/ref/mocks/orders/STYLE.md`, and the decisions in
`~/ref/mocks/WORKLOG.md` (search for the app name). Shared assets: `~/ref/mocks/src/assets/`.

Target system: CachyOS (Arch), KDE Plasma 6.8 on Wayland. You cannot see a screen here - so be exact with colours,
sizes and fonts taken from the mockup, and write down everything you could not match.

## Make (create files ONLY under `sddm/`)
- `sddm/endfield/`: an SDDM theme for Qt6 (SDDM >= 0.21): `metadata.desktop`, `theme.conf`, `Main.qml` reproducing lock v2: the yellow hanging clock plate (320x96, IDENTICAL to the top bar's - read ds-topbar-v2.html's .clock CSS), tri-band under it, centred circle avatar (userModel icon or initials), password field with yellow '›››', corner small print, power/keyboard buttons. Calm ground with the faint topo floor (use ~/ref/mocks/src/assets/topo-floor.svg, copy it into the theme folder - that copy is allowed).
- README: install path (/usr/share/sddm/themes/), sddm.conf [Theme] Current=endfield, test command (sddm-greeter-qt6 --test-mode --theme ...).
- `sddm/README.md`: where each file installs, how to apply/reload, mapping table (mockup element -> real setting),
  and a "Could not match" list (be honest: what the real app cannot do that the mockup shows).

## Rules
- Real, valid syntax for the real app (no invented keys). If unsure a setting exists, say so in the README instead
  of inventing it. No network downloads; no files outside `sddm/`.
- Colours exactly as in the mockup/house style (hex). Fonts: mono = a Consolas-like mono (suggest JetBrains Mono),
  body = a Segoe-like sans (suggest Inter) - list fonts needed in the README.
- No glows. Square corners unless the mockup is rounded. People avatars = circles.

## Done when
All files exist, syntax checked where a checker exists locally (e.g. `python3 -c` for JSON/INI parsing, `bash -n`
for shell), README complete. Report: files made, what is approximate, what needs a live check.
