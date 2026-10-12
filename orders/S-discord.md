# Order S-discord: real skin files for `discord` from the approved mockup

Source of truth (read-only): `~/ref/mocks/components/ds-discord-v2.html` (open it, read ALL its CSS/HTML), the house style
`~/ref/mocks/components/ds-shell.css` and rules `~/ref/mocks/orders/STYLE.md`, and the decisions in
`~/ref/mocks/WORKLOG.md` (search for the app name). Shared assets: `~/ref/mocks/src/assets/`.

Target system: CachyOS (Arch), KDE Plasma 6.8 on Wayland. You cannot see a screen here - so be exact with colours,
sizes and fonts taken from the mockup, and write down everything you could not match.

## Make (create files ONLY under `discord/`)
- `discord/endfield.theme.css`: a Vencord/Equicord theme (with the META header comment block) re-theming DEFAULT Discord to the mock: surface colours (s0-s3), mono small-caps category labels, yellow active-server indicator + yellow active-channel tick, crimson mention badges, soft yellow mention highlight, circle avatars stay. Prefer Discord's CSS variables (--background-primary etc.) over fragile class names; where classes are needed use [class*=...] selectors.
- `discord/README.md`: where each file installs, how to apply/reload, mapping table (mockup element -> real setting),
  and a "Could not match" list (be honest: what the real app cannot do that the mockup shows).

## Rules
- Real, valid syntax for the real app (no invented keys). If unsure a setting exists, say so in the README instead
  of inventing it. No network downloads; no files outside `discord/`.
- Colours exactly as in the mockup/house style (hex). Fonts: mono = a Consolas-like mono (suggest JetBrains Mono),
  body = a Segoe-like sans (suggest Inter) - list fonts needed in the README.
- No glows. Square corners unless the mockup is rounded. People avatars = circles.

## Done when
All files exist, syntax checked where a checker exists locally (e.g. `python3 -c` for JSON/INI parsing, `bash -n`
for shell), README complete. Report: files made, what is approximate, what needs a live check.
