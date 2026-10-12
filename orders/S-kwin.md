# Order S-kwin: real skin files for `kwin` from the approved mockup

Source of truth (read-only): `~/ref/mocks/components/ds-window-v2.html` (open it, read ALL its CSS/HTML), the house style
`~/ref/mocks/components/ds-shell.css` and rules `~/ref/mocks/orders/STYLE.md`, and the decisions in
`~/ref/mocks/WORKLOG.md` (search for the app name). Shared assets: `~/ref/mocks/src/assets/`.

Target system: CachyOS (Arch), KDE Plasma 6.8 on Wayland. You cannot see a screen here - so be exact with colours,
sizes and fonts taken from the mockup, and write down everything you could not match.

## Make (create files ONLY under `kwin/`)
- `kwin/aurorae/Endfield/`: an Aurorae (SVG) window decoration theme: `metadata.json`, `decoration.svg`, button SVGs (minimize/maximize/close: the mockup's exact glyphs; close = rule-18 X with empty centre), `EndfieldDecorationrc` (title height 34, fonts, padding). Focused: small yellow tick left of the title; inactive: dimmed. Square corners. Close hover = crimson.
- README: install path (~/.local/share/aurorae/themes/), how to select it.
- `kwin/README.md`: where each file installs, how to apply/reload, mapping table (mockup element -> real setting),
  and a "Could not match" list (be honest: what the real app cannot do that the mockup shows).

## Rules
- Real, valid syntax for the real app (no invented keys). If unsure a setting exists, say so in the README instead
  of inventing it. No network downloads; no files outside `kwin/`.
- Colours exactly as in the mockup/house style (hex). Fonts: mono = a Consolas-like mono (suggest JetBrains Mono),
  body = a Segoe-like sans (suggest Inter) - list fonts needed in the README.
- No glows. Square corners unless the mockup is rounded. People avatars = circles.

## Done when
All files exist, syntax checked where a checker exists locally (e.g. `python3 -c` for JSON/INI parsing, `bash -n`
for shell), README complete. Report: files made, what is approximate, what needs a live check.
