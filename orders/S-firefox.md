# Order S-firefox: real skin files for `firefox` from the approved mockup

Source of truth (read-only): `~/ref/mocks/components/ds-firefox-v3.html` (open it, read ALL its CSS/HTML), the house style
`~/ref/mocks/components/ds-shell.css` and rules `~/ref/mocks/orders/STYLE.md`, and the decisions in
`~/ref/mocks/WORKLOG.md` (search for the app name). Shared assets: `~/ref/mocks/src/assets/`.

Target system: CachyOS (Arch), KDE Plasma 6.8 on Wayland. You cannot see a screen here - so be exact with colours,
sizes and fonts taken from the mockup, and write down everything you could not match.

## Make (create files ONLY under `firefox/`)
- `firefox/chrome/userChrome.css` (+ `userContent.css` only if needed): the Intel Archive light chrome - pale paper toolbars with the faint dot grid, // BROWSER header feel, address bar as in the mock (black site-identity block, bold host / grey path), native vertical tabs (sidebar.verticalTabs) styled as the mission list (active tab = yellow block, others light rows), bookmarks toolbar with GREYSCALE favicons that turn colour on hover, 300px tab sidebar. Firefox 157.
- README: about:config prefs needed (toolkit.legacyUserProfileCustomizations.stylesheets etc.).
- `firefox/README.md`: where each file installs, how to apply/reload, mapping table (mockup element -> real setting),
  and a "Could not match" list (be honest: what the real app cannot do that the mockup shows).

## Rules
- Real, valid syntax for the real app (no invented keys). If unsure a setting exists, say so in the README instead
  of inventing it. No network downloads; no files outside `firefox/`.
- Colours exactly as in the mockup/house style (hex). Fonts: mono = a Consolas-like mono (suggest JetBrains Mono),
  body = a Segoe-like sans (suggest Inter) - list fonts needed in the README.
- No glows. Square corners unless the mockup is rounded. People avatars = circles.

## Done when
All files exist, syntax checked where a checker exists locally (e.g. `python3 -c` for JSON/INI parsing, `bash -n`
for shell), README complete. Report: files made, what is approximate, what needs a live check.
