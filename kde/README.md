# EndfieldDark — KDE Plasma 6 skin (order S-kde)

Real skin files for the approved mockup `ref/mocks/components/ds-dolphin-v2.html` (Dolphin "depot" v2) and the
house style (`ref/mocks/components/ds-shell.css`, `ref/mocks/orders/STYLE.md`).
Target: CachyOS (Arch), KDE Plasma 6.8 on Wayland. Everything here was written without seeing a screen — the
"Needs a live check" section at the end lists what to verify on the real machine.

## Files

| File | What it is |
|---|---|
| `EndfieldDark.colors` | Complete KDE colour scheme (KConfig/`.colors`, standard keys only) |

There is deliberately **no** Kvantum theme, icon theme or QML in this order — see "Beyond a colour scheme"
for what the depot look still needs and which of those cannot be done at all.

## Install

**Colour scheme** — copy to the user colour-scheme directory (Plasma 6):

```
cp EndfieldDark.colors ~/.local/share/color-schemes/
```

System-wide alternative (all users): `/usr/share/color-schemes/`.

**Apply** (either one):

- System Settings → **Colors** → *EndfieldDark* → Apply
- or CLI: `plasma-apply-colorscheme EndfieldDark`

**Reload notes:**

- `plasma-apply-colorscheme` re-themes running Qt/KDE apps on Wayland in most cases; if a specific app keeps
  its old colours, restart that app.
- GTK apps do not follow KDE colour schemes by default. On Plasma 6 the XDG desktop portal usually applies
  the scheme to GTK if "Global Theme → colours for applications" is set to *From the current colour scheme*;
  otherwise GTK apps need their own theme (out of scope of this order).
- If the scheme does not appear in the KCM list, the file has a parse error — re-copy and re-open the KCM.

## Format note (why the file has no hex values)

KDE `.colors` files store colours as decimal `R,G,B` triples (same as the official Breeze schemes). Every value
below is an exact conversion of the mockup hex; there is no approximation in the conversion itself.

## Palette taken from the house style (`ds-shell.css`)

| Token | Hex | RGB (used in `.colors`) |
|---|---|---|
| `--ink` | `#f1f1f4` | 241,241,244 |
| `--ink2` | `#c9ccd3` | 201,204,211 |
| `--dim` | `#7d8089` | 125,128,137 |
| `--faint` | `#55575e` | 85,87,94 |
| `--yellow` | `#FFFA00` | 255,250,0 |
| `--orange` | `#ff9e2c` | 255,158,44 |
| `--crimson` | `#d91e36` | 217,30,54 |
| `--green` | `#7ddb57` | 125,219,87 |
| `--blue` | `#5aa7ff` | 90,167,255 |
| `--violet` | `#cfc6f4` | 207,198,244 |
| list surface (mockup `.ls` / `.dp`) | `#131417` | 19,20,23 |
| side panels / sidebars (`.pl`, `.info`) | `#15161a` | 21,22,26 |
| content surface (`--chat`) | `#1a1b1f` | 26,27,31 |
| raised control (`--field`) | `#26282d` | 38,40,45 |
| lines / unselected blocks (`--steel`) | `#33363C` | 51,54,60 |
| darkest foot (mockup `.foot`) | `#0e0f11` | 14,15,17 |
| rail (`--rail`) | `#101114` | 16,17,20 |
| light head top (`.head` gradient) | `#f4f5f7` | 244,245,247 |
| light head bottom (gradient) | `#e6e7ea` | 230,231,234 |
| head text / barcode (`#111`) | `#111111` | 17,17,17 |
| head secondary (`#8a8d94`) | `#8a8d94` | 138,141,148 |

## The selection colour (important)

The mockup selects rows with `rgba(255,250,0,.07)` over `#131417` — a 7% yellow tint — plus a 3px yellow left
bar. A `.colors` file cannot store alpha; the role must be a solid. The nearest solid is that tint composited
over the list surface:

```
7% #FFFA00 over #131417  ->  R 19+0.07*(255-19)=35.5  G 20+0.07*(250-20)=36.1  B 23-0.07*23=21.4
                          ->  36,36,21  (#242415)
```

So `[Colors:Selection] BackgroundNormal=36,36,21` (`#242415`). `BackgroundAlternate=43,43,21` (`#2b2b15`) is the
same blend at 10% for alternating selected rows. Selected text is `#ffffff` (the mockup sets `.row.sel .n`
to `#fff`). If the live result looks too subtle, raise both values toward the 10–14% blend rather than
switching to full yellow — full `#FFFA00` would break the "yellow is structural, never decoration" rule by
painting entire rows yellow.

Focus decoration is `DecorationFocus=DecorationHover=255,250,0` (`#FFFA00`) in every colour group — the yellow
focus frame/tick, per the mockup's yellow focus marks. (The mockup's *3px left bar on the selected row* is a
widget-style detail, not a colour-scheme one — see mapping table.)

## Mapping table — mockup element → real setting

| Mockup element | Hex | Real setting |
|---|---|---|
| `.ls` file-list background `#131417` | `#131417` | `[Colors:View] BackgroundNormal` |
| `.row` alt / `.pl`+`.info` panels `#15161a` | `#15161a` | `[Colors:View] BackgroundAlternate` |
| row name text `--ink` | `#f1f1f4` | `[Colors:View] ForegroundNormal` |
| `.row .s/.d`, `.row.hid` text `--dim` | `#7d8089` | `[Colors:View] ForegroundInactive` (also dims hidden files, like `.row.hid`) |
| `.info .kv b` GIT `MODIFIED` yellow | `#FFFA00` | `[Colors:View] ForegroundActive` (active/visited-state text) |
| links / info | `#5aa7ff` | `[Colors:View] ForegroundLink` |
| `.t-doc` violet family | `#cfc6f4` | `[Colors:View] ForegroundLinkVisited` |
| crimson (urgent, `.bar s.hot`) | `#d91e36` | `[Colors:View] ForegroundNegative` |
| orange (notif diamond, `--t-arc`) | `#ff9e2c` | `[Colors:View] ForegroundNeutral` |
| green (`--t-code`, ok) | `#7ddb57` | `[Colors:View] ForegroundPositive` |
| `.row.sel` background (7% tint) | `#242415` | `[Colors:Selection] BackgroundNormal` |
| `.row.sel .n` text `#fff` | `#ffffff` | `[Colors:Selection] ForegroundNormal` |
| yellow focus marks (`.it.on::before`, `DecorationFocus`) | `#FFFA00` | `DecorationFocus`/`DecorationHover` in **all** groups |
| `.pl` / `.info` sidebar surfaces | `#15161a` | `[Colors:Window] BackgroundNormal` |
| `.flt` filter row / raised areas `#18191d`–`#1a1b1f` | `#1a1b1f` | `[Colors:Window] BackgroundAlternate` |
| window/dialog text hierarchy | ink/ink2/dim | `[Colors:Window] Foreground*` (same set as View) |
| `.field`/`.chip`/control fills `--field` | `#26282d` | `[Colors:Button] BackgroundNormal` |
| `.chip` hover-ish / steel blocks `--steel` | `#33363C` | `[Colors:Button] BackgroundAlternate` |
| button/control text `--ink2` | `#c9ccd3` | `[Colors:Button] ForegroundNormal` |
| `.head` light depot header (gradient top) | `#f4f5f7` | `[Colors:Header] BackgroundNormal` |
| `.head` gradient bottom | `#e6e7ea` | `[Colors:Header] BackgroundAlternate` |
| `.head` text `#111` | `#111111` | `[Colors:Header] ForegroundNormal` |
| `.head .cap` / `.head .tt b span` `#8a8d94` | `#8a8d94` | `[Colors:Header] ForegroundInactive` |
| `.head` dark steel text (`#33363C`) | `#33363C` | `[Colors:Header] ForegroundActive` (yellow would be unreadable on the light head) |
| `.foot` dark depot foot `#0e0f11` | `#0e0f11` | `[Colors:Complementary] BackgroundNormal` |
| `--rail` darkest strips | `#101114` | `[Colors:Complementary] BackgroundAlternate` |
| tooltips (mockup `.chip`/field material) | `#26282d` | `[Colors:Tooltip] BackgroundNormal` (+ `#33363C` alternate) |
| unfocused window chrome (dimmer) | `#101114` | `[WM] inactiveBackground` / `inactiveForeground` = `#7d8089` |
| focused window chrome | `#15161a` | `[WM] activeBackground` / `activeForeground` = `#f1f1f4` |
| window button cells (`.wb` fill/border family) | `#33363C` | `[WM] activeTitleBtnBg` / `activeTitleBtnFg` = `#f1f1f4` |
| sorted column shading (mockup shows none) | — | `[General] shadeSortColumn=true` (KDE default; harmless) |
| mono labels, body fonts | — | Not in `.colors` — see Fonts |
| pills, 2px plates, 3px selection tick, underbars | — | Widget style / icons — see "Beyond a colour scheme" |

## Fonts needed (not part of `.colors`)

The mockup uses `var(--mono) = Consolas, "Cascadia Mono", ui-monospace` for titles/labels/micro-print and
`var(--body) = "Segoe UI", system-ui` for readable content. Linux equivalents to install:

- **Mono (Consolas-like): JetBrains Mono** — terminal + all mono small-caps labels.
  Arch: `pacman -S ttf-jetbrains-mono` (or any JetBrains Mono from the AUR/fonts package you trust).
- **Body (Segoe-like): Inter** — file names, message text, headings.
  Arch: `pacman -S inter-font`.

Then System Settings → **Fonts**:

- General (body): **Inter**, 10pt
- Fixed width: **JetBrains Mono**, 10pt

(These are also writable as `kdeglobals [General] font=` / `fixed=` X11 font-description strings, but the exact
description string is best produced by the GUI/`kwriteconfig6` on the live machine rather than guessed here.)

Not matchable via fonts: the mockup's *wide letter-spacing and uppercase* small print (`.label`, `.micro`) —
Qt stylesheets can letter-space per-app only; KDE's global font setting has no tracking control. Apps whose
QML/stylesheet you control (Kitty, Discord, Firefox) get this in their own skin orders.

## Beyond a colour scheme — what Dolphin's depot look actually needs

Honest inventory. A `.colors` file only paints roles (backgrounds, text, focus). Everything structural below
needs more machinery, and some of it cannot be had at all without forking Dolphin.

### 1. Widget style (Kvantum or Klassy) — achievable, required

- **Rounded pills** (filter pills radius 17px, sort pill radius 19px, round filter button) and **2px plates /
  6px fields** — the house corner rules. Breeze does not round like this; **Kvantum** (with a custom Endfield
  kvantum theme) or **Klassy** (Breeze fork with per-element shape/colour options) is needed.
- **Light-on-top surfaces inside a dark app** (light header over dark body) — only a style can paint a
  differently-coloured toolbar/header band; `[Colors:Header]` supplies the colours but Breeze ignores it for
  most widgets.
- **3px yellow left tick on the selected/active row** (`.it.on::before`, `.row.sel` shadow) — Breeze draws a
  full-row highlight only; Kvantum can draw an edge indicator. The colour comes from the scheme; the geometry
  does not.
- Suggested direction: **Kvantum + one custom "Endfield" theme** (the mockup's flat washes and pill shapes map
  cleanly to Kvantum's per-widget painting). Klassy is the lower-effort fallback for rounding + colour tweaks.

### 2. Dolphin itself (its toolbar/status bar/panels are C++/QML, not skinable) — mostly NOT achievable

Dolphin has **no user theme/QML-override mechanism** (unlike Kirigami desktop themes or app styles). These
mockup parts have no supported settings path and would need a Dolphin patch/fork or a deliberate approximation:

| Depot element | Reality | Verdict |
|---|---|---|
| 72px light head: icon tile, barcode strip, `DOLPHIN 25.08 · BENYLIN@CLOCKMOST` micro line | Dolphin's header is a QToolBar of actions. No barcode, no version/host print, no gradient. | **Not possible** without patching Dolphin. Approximation: light `[Colors:Header]` + Kvantum header band; put the micro print nowhere or in a terminal prompt. |
| Capacity meter `1.2 / 1.8 TB` + 120px bar in the head | No such widget in Dolphin. | **Not possible** inside the window. Approximation: a Plasma panel widget / Conky-style bar near the window reading `df -h`. |
| Filter pills row (`All / Folders / Code / Docs / Images / Config / Archives` with colour swatches) | Dolphin's real Filter Bar (Ctrl+I) is one plain text field, no pills, no type categories. | **Not possible** as shown. Keep Dolphin's stock filter bar; the `›››` yellow prompt look can only be approximated in a Kvantum line-edit. |
| File-type colour underbars (2px, dir `#3FD0E8` / code `#7ddb57` / doc `#cfc6f4` / img `#ff1aac` / archive `#ff9e2c` / config `#5aa7ff` per icon) | Colour-by-type does not exist in Dolphin. | **Approximable** with a custom icon theme (`endfield-icons`): bake the coloured underbar into each mimetype SVG. Otherwise not possible. Separate order. |
| Sidebar labels `PINS` / `TREE` / `DEVICES` in mono caps | Places panel is a QTreeView; section headers are not configurable. | **Not possible** as shown (font/colour partially via style). |
| Pin glyphs on places | Dolphin does show a "pinned" concept only for the toolbar. | **Not possible** as shown. |
| Device capacity bars in sidebar (`Data 600/1800`, `Games 754/920` with crimson "hot" bar) | Places panel shows device free space as text at most. | **Not possible** without patching; the Devices:/ view gives free-space text. |
| Details columns `NAME / SIZE / MODIFIED ▾ / TYPE` | Columns exist (Name, Size, Modified, Type…). Mono caps + wide tracking headers are style/font territory. | **Partly possible**: enable columns in Details view; header font is style-limited. |
| Dark foot: light sort pill `Modified ▾ / DESC`, delete glyph, `5 FOLDERS · 11 FILES · 2 SELECTED`, ZOOM slider, `1.2 TB FREE` | Status bar exists with zoom slider and free-space/selection text; formatting is stock; no sort pill (sort via View menu / column headers). | **Partly possible**: turn on the status bar + zoom + free space; the pill and mono caps counts are **not**. |
| Info panel: 170px preview with type underbar + `FL-2410` code chip, `OWNER` row, `GIT: MODIFIED` in yellow, barcode, `2 SELECTED · 48.8 KB` | Information panel exists (preview + name/size/date/type/…). No code chip, no barcode, no GIT row. | **Partly possible**: preview + metadata yes; `GIT` needs a custom KFileMetaData/properties plugin — **not available**; chip/barcode are mock furniture (**not possible**). |
| Hidden rows dimmed (`.row.hid`) | Dolphin dims hidden files in the view. | **Possible** (scheme `ForegroundInactive` helps). |
| Window buttons: four-arm rule-18 X, crimson close on hover | KWin decoration territory (order **S-kwin**), not the colour scheme. | See `orders/S-kwin.md`. |

### 3. Things this order intentionally does not invent

- No Kvantum theme files here (would be guesswork geometry without a live iterate loop; and the order's file
  list is the `.colors` + README only).
- No icon theme here (needs its own order: `endfield-icons` with per-type underbar icons).
- No `[ColorEffects:Disabled]` / `[ColorEffects:Inactive]` sections — real KConfig sections used by Breeze for
  greying/disabling effects, but not requested and not needed for the mockup's flat look. Add later if disabled
  items look wrong live.

## Could not match (honest list)

1. **Selection tint** — mockup uses 7% alpha yellow; `.colors` has no alpha → solid `#242415` (see above).
2. **3px yellow left bar on selection** — colour scheme cannot draw it; widget-style work (Kvantum).
3. **All of "Beyond a colour scheme §2"** — light depot head with icon block/barcode/capacity meter, filter
   pills, per-type underbars (without a custom icon theme), mono-caps sidebar section labels, sidebar capacity
   bars, sort pill in the foot, mono-caps status counts, info-panel code chip / barcode / GIT row. The real
   Dolphin cannot do these without patches; the mockup is allowed to be ahead of the app.
4. **Letter-spacing / uppercase micro print** — no global font tracking in KDE; per-app only.
5. **Exact 38px row height and the 1fr/110/170/120 column grid** — row height follows icon size + font;
   Details columns are the stock set with user-dragged widths.
6. **`#e9e9ee` light pills on dark surfaces** (sort pill, filter-all pill, `.flb`) — that inversion is style
   painting (Kvantum), not a colour-scheme role.
7. **Flipped light `#f4f5f7` head inside a dark app** — `[Colors:Header]` carries the colours, but whether any
   live widget uses them depends on the style; stock Breeze will not show the depot head.

## Needs a live check

- Whether Plasma 6.8's Colors KCM lists *Header* and *Complementary* groups from this file (keys are standard;
  the KCM only shows some roles).
- Readability of `#5aa7ff` links and `#cfc6f4` link-visited on `#131417` (borrowed from the mockup as-is).
- That `#242415` selection reads as a *tint*, not as a mistake — if too faint, raise toward `#2b2b15`+.
- Whether `[Colors:Header]` affects anything in the chosen style (Kvantum/Klassy), or is only data.
- GTK apps picking up the scheme via the portal.
- Dolphin status-bar free-space text format vs the mockup's `1.2 TB FREE`.
- Interaction with the S-kwin decoration (slim strip, yellow focus tick) — `[WM]` is only the fallback colours
  Breeze/Aurorae read.
