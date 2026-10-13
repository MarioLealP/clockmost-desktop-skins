# Kitty — Endfield skin (from `ds-kitty-v3.html`)

Real kitty config + Claude Code statusLine for the approved mockup
`ref/mocks/components/ds-kitty-v3.html` ("glass + Claude Code"), on CachyOS
(Arch) + KDE Plasma 6.8 Wayland. Colours are the mockup's `--an-*` values 1:1.

## Files and where they install

| File | Installs to | What it is |
|---|---|---|
| `endfield.conf` | `~/.config/kitty/endfield.conf`, included from `~/.config/kitty/kitty.conf` | theme (ANSI 16, fg/bg, cursor, selection), glass opacity, window padding, tab bar config |
| `tab_bar.py` | `~/.config/kitty/tab_bar.py` | the slim tab line (kitty loads it automatically when `tab_bar_style custom` is set) |
| `claude-statusline.sh` | `~/.config/kitty/claude-statusline.sh` (`chmod +x`) | Claude Code `statusLine` command — the mockup's `.sl` row |

## Fonts needed

- **Mono (kitty terminal + tab labels): JetBrains Mono** — the mockup uses Consolas
  (`--mono`); JetBrains Mono is the closest free match. `font_size 15` matches the
  mockup's 15px terminal type at 1920×1080; nudge for your DPI.
- **Body sans: Inter** — Segoe-like (`--body` in the house style). Kitty itself is
  monospace-only and does **not** use it; listed because the rest of the Endfield
  shell (KWin decoration, Dolphin, …) does.

## Apply / reload

1. `mkdir -p ~/.config/kitty && cp endfield.conf tab_bar.py claude-statusline.sh ~/.config/kitty/`
2. In `~/.config/kitty/kitty.conf` add: `include endfield.conf`
3. Restart kitty (or open a new window). To reload in place, either run
   `kitty @ load-config` (needs remote control enabled) or add a keybind to
   `endfield.conf`, e.g. `map ctrl+shift+f5 load_config_file` (real kitty action).
4. **KWin blur** (required for the frosted look — kitty only makes the window
   translucent): `background_opacity 0.72` needs KWin to blur what is behind the
   window. KWin only blurs surfaces that ask for it via `org_kde_kwin_blur`, which
   kitty does not send, so add a **KWin blur rule/script for the window class
   `kitty`** (e.g. the community "Force Blur" KWin script, or your shell's blur
   rule). Without it the window is see-through but not frosted.

## Claude Code status line

`claude-statusline.sh` reads the JSON Claude Code passes on stdin and prints one
ANSI line. Set it in `~/.claude/settings.json`:

```json
{
  "statusLine": {
    "type": "command",
    "command": "~/.config/kitty/claude-statusline.sh"
  }
}
```

(Use the absolute path if `~` does not expand in your setup.) Then in Claude Code
run `/config` and set the **theme to `dark (ANSI)`** — only then do the ANSI codes
resolve to the Endfield palette from `endfield.conf`. The script needs `python3`
(Arch base) and `git` (branch segment).

Line layout (mockup `.sl`): ` ◆ MODEL ` black-on-yellow bold · cwd cyan ·
`branch` yellow + `● N` red (0 = dim) · `ctx ▮…▯… NN%` · `⏵⏵ mode` magenta.
Context % is estimated from the last assistant `usage` in the transcript
(`input + cache_read + cache_creation` over 200k).

## Mapping table — mockup element → real setting

| Mockup (`ds-kitty-v3.html`) | Real setting |
|---|---|
| `--an-black`…`--an-brwhite` (the 16 swatches) | `color0`…`color15` in `endfield.conf` (exact hex) |
| `.term` text `--an-white` | `foreground #c9ccd3` |
| `.k` glass `rgba(13,14,16,.72)` | `background #0d0e10` + `background_opacity 0.72` + KWin blur rule |
| yellow block cursor (order) | `cursor #FFFA00`, `cursor_text_color #0d0d0e`, `cursor_shape block`, `cursor_blink_interval 0` |
| selection (not shown in mockup) | `selection_background #FFFA00`, `selection_foreground #0d0d0e` (house rule: yellow = selected) |
| `.term` padding `22px 28px 0` | `window_padding_width 22 28 0 28` (top right bottom left) |
| `.tl` slim tab line | `tab_bar_edge top`, `tab_bar_style custom` + `tab_bar.py` |
| `.tl span.on` (bright + short yellow underline) | `active_tab_foreground #f1f1f4` + yellow underline drawn in `tab_bar.py` |
| `.tl span` inactive `--an-brblack` | `inactive_tab_foreground #6b6e76` |
| tab labels `1 · CLAUDE` uppercase | `tab_bar.py` builds `N · TITLE` (`tab_title_template {title}` stays identity) |
| `.sl` Endfield status line | `claude-statusline.sh` via Claude Code `statusLine` |
| `.sl .blk` black-on-yellow bold block | SGR `1;30;43` in the script |
| `.sl` ctx bar `▮▮▮▮▯▯▯▯▯▯ 38%` | 10 segments in the script (`▮` green / `▯` bright-black / `%` bright-white) |
| `active_tab_background #FFFA00` (quirk) | not a plate: `tab_bar.py` reads it back as the underline yellow (type-safe colour round trip); also the active plate in the conf-only fallback below |

## Could not match (be honest)

1. **Letter-spacing** (`.16em`–`.26em` on tab labels and the title strip) — kitty
   has no letter-spacing; labels are plain glyphs.
2. **Title strip** (34px `KITTY` + yellow tick + min/max/close) — that is the
   **KWin window decoration** (WORKLOG: the slim 34px strip is the global
   decoration), not kitty config. Out of this skin's files.
3. **Hairline under the tab line** (`rgba(255,255,255,.08)`), the **1px window
   border** and the **drop shadow** — KWin borders/shadows. The kitty tab bar is
   one text row and cannot draw its own bottom border.
4. **Topo motif + dot field** (`.topo` / `.dots` window furniture) — kitty's
   `background_image` takes a raster image, has no corner mask or gradient, and
   ships nothing extra in this order. Could be approximated later with a
   pre-rendered PNG at low opacity (`background_image` / `background_image_opacity`
   exist but are **unverified** here — do not trust without a live check).
5. **Tab underline two-tone** (bright text + yellow underline) — the tab bar
   draws in one cell row; the yellow underline needs the cursor object to expose
   an underline attribute + decoration colour. `tab_bar.py` uses it when present
   (checks `decoration_color` / `underline_color`) and falls back to an underline
   in the text colour otherwise. **Needs a live check on the real machine.**
6. **Cursor colour** — the order says yellow block; the mockup's `.cur` is
   `--an-brwhite` (`#f1f1f4`). Shipped yellow per the order; change `cursor` to
   `#f1f1f4` in `endfield.conf` to match the mockup exactly.
7. **Selection** — the mockup never shows a selection state; chose the house
   rule (yellow). Softer alternative: `selection_background #33363C` +
   `selection_foreground #f1f1f4`.
8. **Mode `⏵⏵ auto`** — Claude Code's statusLine JSON has `output_style.name`,
   not the permission mode (auto-accept / plan). The script shows the output
   style; that segment cannot show "auto" for certain. If you want the real mode
   later, it has to come from hooks/transcript scraping.
9. **Tab gap / indent** (16px left, 26px between labels) — approximated with
   spaces (`GAP = '   '` in `tab_bar.py`); exact pixels depend on font metrics.

## Approximate / needs a live check

- `font_size 15` is the mockup's 15px at 1920×1080 — retune for your DPI.
- `tab_bar.py` uses the documented `draw_tab` hook; verify it loads on your kitty
  version and that the active/colours render. **Conf-only fallback** if it errors
  (no underline, active plate is a yellow block — house-legal "active = yellow"):
  in `endfield.conf` replace the tab-bar block with:
  `tab_bar_style separator`, `tab_separator "  "`,
  `tab_title_template {index} · {title}`, `active_tab_foreground #f1f1f4`,
  `active_tab_background #FFFA00`, `inactive_tab_foreground #6b6e76`,
  `inactive_tab_background #0d0d0e` — and delete `tab_bar.py`.
- KWin blur/translucency behaviour on Wayland (see above).
- `claude-statusline.sh`: the JSON field names (`model.display_name`,
  `workspace.current_dir`, `transcript_path`, `output_style.name`) follow Claude
  Code's documented statusLine payload — confirm on a live session (the script
  degrades gracefully if a field is missing).
- Segment widths: the status line is one line; on narrow windows it will wrap in
  the Claude Code UI — shorten the cwd or drop a segment if that bothers you.
