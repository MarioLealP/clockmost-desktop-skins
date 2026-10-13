# discord — Endfield skin for Discord (from `ds-discord-v2`)

Real-build decision (WORKLOG 2026-10-12, Mario: *"just use default discord and retheme like this"*):
**default Discord layout (Equibop) + a CSS theme only.** No layout changes, so it survives Discord updates.
Everything here is colour, type and marker styling only.

## Files and where they install

| File | Installs to |
|---|---|
| `endfield.theme.css` | The themes folder of your Vencord/Equicord/Equibop install. Open it via **Settings → Vencord (or Equicord/Equibop) → Themes → "Open Theme Folder"** — that button is authoritative. Typical Linux paths: `~/.config/Vencord/themes/`, `~/.config/Equicord/themes/`, `~/.config/Equibop/themes/`. Keep the `.theme.css` suffix — the theme loader only lists `*.theme.css`. |
| `README.md` | Docs only. Lives next to the theme in this repo; install nothing. |

The theme carries the standard Vencord META block (`@name Endfield` + `@author` / `@version` / `@description`)
so it appears in the Themes list as **Endfield**.

## How to apply / reload

1. Copy `endfield.theme.css` into the themes folder (above).
2. Settings → Themes → toggle **Endfield** on. Everything else in that page can stay off.
3. `Ctrl+R` reloads the client and re-reads the CSS. After editing the file, save + `Ctrl+R`.
   If the theme list does not refresh, close and reopen the settings page first.

## Fonts needed

- **Mono** (labels, categories, timestamps, badges): **JetBrains Mono** 400/700 — a Consolas-like mono.
- **Body** (messages, names, UI text): **Inter** 400/500/600/700 — a Segoe-like sans.

The theme `@import`s both from Google Fonts (needs network on first load). For a fully offline install,
put them on the system instead, e.g. on CachyOS/Arch: `sudo pacman -S ttf-jetbrains-mono inter-font`
(package names may differ on your mirror; otherwise install from the fonts' upstream releases).
Fallback stacks in the CSS are `Consolas, "Cascadia Mono", ui-monospace` and `"Segoe UI", system-ui`.

## Colours (exact mockup / house-style hexes)

| Token | Hex | Used for |
|---|---|---|
| s0 | `#0e0f11` | server rail, user panel, search field |
| s1 | `#131417` | channel + member sidebars |
| s2 | `#17181c` | chat column |
| s3 | `#1c1d22` | composer, reaction pills, popouts |
| ink | `#f1f1f4` | main text |
| ink2 | `#c9ccd3` | secondary text, icons |
| dim | `#7d8089` | labels |
| faint | `#55575e` | micro print |
| yellow | `#FFFA00` | active / selected / where you are |
| crimson | `#d91e36` | mention badges, urgent |
| green | `#7ddb57` | online |
| orange | `#ff9e2c` | idle |
| blue | `#5aa7ff` | links / info |
| offline | `#6b6e76` | offline status |
| mention wash | `rgba(255,250,0,.05)` / `rgba(255,250,0,.12)` | mention row / `@` chip |
| row wash | `rgba(255,255,255,.06)` | selected channel |

## Mapping table (mockup element → real setting)

The theme prefers Discord's own CSS variables; class rules use `[class*=...]` only where no variable exists.
Sizes/letter-spacings below are taken from `ds-discord-v2.html` literally.

| Mockup (`ds-discord-v2.html`) | Real Discord setting / rule in `endfield.theme.css` |
|---|---|
| `--s0` rail + user panel + search | `--background-tertiary`, `--background-secondary-alt` (+ `nav[class*="guilds"]`, `div[class*="panels"]`, `div[class*="searchBar"]`) |
| `--s1` channel + member sidebars | `--background-secondary` |
| `--s2` chat column | `--background-primary` |
| `--s3` composer / reactions / popouts | `--channeltextarea-background`, `--background-floating`, reaction rule |
| `--hl` selected row wash `rgba(255,255,255,.06)` | `--background-modifier-selected` + `div[class*="modeSelected"]` |
| `.cat` / `.mem .rl` — mono 700 10px, `.2em`, uppercase, dim | `div[class*="sidebar"] h3` and `[class*="membersGroup"]` |
| `.day` — mono 700 10px, `.2em`, uppercase, faint | `div[class*="messagesWrapper"] div[class*="divider"] span` (line treatment stays Discord's) |
| `.m .nm small` timestamps — mono 10px, `.1em`, faint | `time[class*="timestamp"]` / `[class*="timestamp"]` |
| `.shd b` server header — mono 700 13px, `.2em`, uppercase | `div[class*="sidebar"] div[class*="header"]` name rules |
| `.shd .topo` topo motif (200×120 at right −40 / top −30, opacity .12) | `::after` on the sidebar header with an inlined data-URI contour motif, same box/opacity |
| `.shd` / `.chd` hairline `rgba(0,0,0,.4)` | `border-bottom` + `box-shadow: none` on sidebar header / `div[class*="title"]` |
| `.sv .ind` active indicator 4×36 yellow | guild pill rule (`nav[class*="guilds"] [class*="pill"] span` + active state) and `--background-accent: #FFFA00` |
| `.sv .ind` unread tick 4×8 ink | guild pill base rule |
| `.sv .mb` rail mention badges — crimson pill, mono 10px 700 | `--status-danger: #d91e36` + `nav[class*="guilds"] [class*="numberBadge"]` |
| `.sv.add` green `+`, dashed ring | `nav[class*="guilds"] [class*="circleIconButton"]` |
| `.ch.on` active channel bg + ink text | `div[class*="modeSelected"]` (bg wash, `[class*="name"]` colour) |
| `.ch.on::before` yellow active-channel tick 3px (top/bottom 6px, at sidebar edge) | `div[class*="modeSelected"]::before` |
| `.ch.unread` ink 600 + 4×8 ink tick | `div[class*="modeUnread"]` / `modeUnreadImportant` text + `::before` tick |
| `.ch .mb` sidebar mention badges — crimson, mono 10px, square | `div[class*="sidebar"] [class*="numberBadge"]` |
| `.m p` message text — body 15px/1.375, ink2 | `[class*="markup"]` |
| `.m .nm b` names — body 600 15px, role colour | `[class*="username"]`; role colours are Discord's own |
| `.m.mention` soft yellow row + 2px yellow inset bar | `--background-message-highlight: rgba(255,250,0,.05)` + `li/div[class*="mentioned"]` `box-shadow: inset 2px 0 0 #FFFA00` |
| `.at` `@mention` chip — yellow on `rgba(255,250,0,.12)` | `--mention-foreground` / `--mention-background` + `a[class*="mention"]` |
| `.rx` reactions — s3, 8px, mono 11px; `.me` blue tint | `div[class*="reaction"]` / `div[class*="reactionMe"]` rules |
| `.emb` embed — s1, 4px, 4px left bar; small mono provider; blue title | `div[class*="embedFull"]` + `embedProvider` / `embedTitle` / `embedDescription` rules (left-bar colour is per-embed) |
| `.comp` composer — s3, 8px, `rgba(255,255,255,.06)` border | `--channeltextarea-background` + `div[class*="channelTextArea"]` |
| `.comp > span` placeholder faint | placeholder rule in the composer block |
| `.comp .pl` square ink2 attach tile | `div[class*="channelTextArea"] div[class*="attachButton"]` |
| `.chd b` channel title — body 600 16px | `div[class*="title"] h1` |
| `.chd .tp` topic 13px dim | `[class*="topic"]` |
| `.chd .srch` search — s0, mono 11px, `.12em`, faint | `div[class*="searchBar"]` rules |
| `.up` user panel s0; name body 13px 600 | `--background-secondary-alt` + `div[class*="panels"]` name rules |
| `.up small` mono 9px `.14em` green "ONLINE" | `div[class*="panels"] [class*="subtext"]` |
| `.mm` member rows 4px radius, names body 14px 500 | `div[class*="membersWrap"] [class*="name"]` + member row radius rule |
| `.role` mono 8px chip | approximated on `span[class*="botTag"]` (see below) |
| `.typing` 12px dim | `div[class*="typing"]` |
| circle people avatars, circle status dots, server circles with active rounded square | **unchanged** — Discord's own defaults already do this |
| ink / ink2 / dim / faint / green / orange / blue / crimson | `--header-primary`, `--text-normal`, `--header-secondary`, `--text-muted`, `--status-*`, `--text-link`, `--status-danger` |
| `.ttl` window title strip + rule-18 window buttons | **not Discord** — that is the KWin decoration (order S-kwin's slim strip). On Plasma Wayland the frame is drawn by KWin. |

## Could not match (what the real app cannot do that the mockup shows)

1. **Window title strip (`.ttl`) and the rule-18 min/max/close buttons.** Not part of Discord — the frame is
   KWin's (order S-kwin). The theme targets the Discord UI only.
2. **Rule-18 open-centre X as the composer's `+` glyph.** Icons are Discord's own SVGs; CSS cannot replace
   icon paths. The attach button is restyled to the mockup's square ink2 tile, the glyph itself stays Discord's.
   Same for the `#` glyphs, category carets, header icons.
3. **Letter server tiles (CM / FL / …) and the yellow fill of the active tile.** Real servers show uploaded
   icons; a theme cannot generate monogram tiles or recolour the active icon. The active *indicator* (yellow
   pill) and badges are themed.
4. **The orange notification diamond (`.notif pin` on FL).** That is the shared house marker for the shell.
   Discord's own unread semantics (pill / dot / badges) are kept on purpose — the worklog decision explicitly
   kept them.
5. **Per-message "ADMIN" role chip (`.role`).** Discord only ships a BOT chip; roles appear as name colours.
   The BOT chip is restyled to the mockup's mono 8px chip look as an approximation, but it cannot say "ADMIN".
6. **Voice column letter tiles and the green speaking ring (`.vc i.spk`).** Sidebar voice users show real
   avatars, and Discord's channel user list has no speaking indicator to theme.
7. **Reply elbow line (`.rp::before`)** — Discord draws its own reply spine. Only the reply text size/colour
   is themed.
8. **Embed's green left bar** is that one embed's colour in the mockup. Real embeds colour the bar per link
   (kept — that is correct behaviour). The `.emb .shot` thumbnail is mockup filler.
9. **Search wording "SEARCH"** — Discord's placeholder text is its own ("Search"); only the mono/`.12em`/faint
   styling is themed. Same for "Message #felt-dev" (Discord renders its own placeholder).
10. **Topo motif is approximate.** The mockup uses the shared `ds-topo-card.svg`; the theme embeds a small
    hand-drawn contour motif instead (same stroke colour `rgba(205,209,220,.18)`, same box/opacity/position).
    The full 44 KB SVG could not be URL-encoded into the CSS because this worker sandbox blocks the
    interpreters (python3 / node) needed to splice it in.
11. **"ONLINE" small print in the user panel** — Discord shows "Online" or a custom status there. The mono,
    uppercase, green treatment is applied to whatever text Discord puts in that slot; wording is Discord's.
12. **Heights, paddings, column widths** are kept at Discord defaults on purpose (the mockup's own spacing
    block says to match Discord's rhythm; the build decision is "no layout changes"). The mock's 52px headers
    and 44px composer are close to Discord's real values already.
13. **Unread channel tick.** The mockup gives unread channels a 4×8 ink tick at the sidebar edge. Current
    Discord bolds the name but draws no tick there, so the theme draws it itself (`::before`). If your build
    also draws its own unread dot, you may briefly see both.

## Needs a live check (written blind — no screen here)

The variable half of the theme is durable. These class hooks were written against Discord's stable
`[class*=...]` export names and should be verified once in a running client
(`Ctrl+Shift+I` → inspect the element → adjust the selector if the prefix changed):

- **Active-server pill**: rules key on `[aria-selected="true"]` / `[class*="selected"]` inside
  `nav[class*="guilds"]`. If the active pill is not yellow and 36px tall, inspect the active server tile and
  tell me its state class — it is a one-line fix.
- **Active-channel tick position** (`left: -8px` on `div[class*="modeSelected"]::before`): if the channel
  scroller clips it, change `left` to `0`.
- Category labels: `div[class*="sidebar"] h3` (the only `h3` in that column).
- Member role headers: `[class*="membersGroup"]`.
- Date divider: `div[class*="messagesWrapper"] div[class*="divider"] span`.
- Mentioned-message bar: `li/div[class*="mentioned"]`. Discord also tints these rows via
  `--background-message-highlight`; if your build adds its own left bar you may see a doubled edge.
- `div[class*="searchBar"]`, `div[class*="attachButton"]`, `span[class*="botTag"]`,
  `div[class*="panels"] [class*="subtext"]`, `div[class*="typing"]` — the usual small hooks.
- Header hairlines: the theme forces `border-bottom: 1px solid rgba(0,0,0,.4); box-shadow: none` on the two
  top bars; check no doubled line appears.
- Discord updates can rename hashed classes. When something breaks after an update, the `:root` variables
  still hold the palette; only the class rules need re-pointing.

## Syntax check

`python3` / `node` are blocked in the worker sandbox, so no programmatic CSS parse was run. The file was
hand-checked: brace / paren / comment-marker balance verified with `grep` + `wc` (52 `{` = 52 `}`, 90 `(` =
90 `)`, 57 `/*` = 57 `*/`, data-URI placeholder fully replaced). The CSS is standard CSS2/3 + one `@import`
and one `data:image/svg+xml` background — valid for the Vencord/Equicord theme loader.
