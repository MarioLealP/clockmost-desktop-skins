# Order S-kitty: real skin files for `kitty` from the approved mockup

Do NOT use the Skill tool (it only pulls in unrelated reference text). Write the files directly; keep thinking short.

Source of truth (read-only): `~/ref/mocks/components/ds-kitty-v3.html` (open it, read ALL its CSS/HTML), the house style
`~/ref/mocks/components/ds-shell.css` and rules `~/ref/mocks/orders/STYLE.md`, and the decisions in
`~/ref/mocks/WORKLOG.md` (search for the app name). Shared assets: `~/ref/mocks/src/assets/`.

Target system: CachyOS (Arch), KDE Plasma 6.8 on Wayland. You cannot see a screen here - so be exact with colours,
sizes and fonts taken from the mockup, and write down everything you could not match.

## Make (create files ONLY under `kitty/`)
- `kitty/endfield.conf`: kitty theme - the 16 ANSI colours exactly as the mockup's --an-* vars, foreground/background, cursor (yellow block), selection, background_opacity ~0.72 (+ note KWin blur needs a KWin blur rule/script), window padding, tab bar matching the slim tab line (active = bright text + short yellow underline; use tab_bar_style + tab_title_template, or a custom `tab_bar.py` if needed).
- `kitty/claude-statusline.sh`: Claude Code statusLine command (reads the JSON Claude Code passes on stdin; prints ONE line with ANSI colours only): yellow block '◆ MODEL', cwd in cyan, git branch yellow + changed count red, context bar (segments) + %, mode. Note in README how to set it in ~/.claude/settings.json and that Claude Code's theme must be 'dark-ansi' (/config).
- `kitty/README.md`: where each file installs, how to apply/reload, mapping table (mockup element -> real setting),
  and a "Could not match" list (be honest: what the real app cannot do that the mockup shows).

## Rules
- Real, valid syntax for the real app (no invented keys). If unsure a setting exists, say so in the README instead
  of inventing it. No network downloads; no files outside `kitty/`.
- Colours exactly as in the mockup/house style (hex). Fonts: mono = a Consolas-like mono (suggest JetBrains Mono),
  body = a Segoe-like sans (suggest Inter) - list fonts needed in the README.
- No glows. Square corners unless the mockup is rounded. People avatars = circles.

## Done when
All files exist, syntax checked where a checker exists locally (e.g. `python3 -c` for JSON/INI parsing, `bash -n`
for shell), README complete. Report: files made, what is approximate, what needs a live check.
