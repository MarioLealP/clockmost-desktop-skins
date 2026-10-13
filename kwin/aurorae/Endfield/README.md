# Endfield - Aurorae window decoration theme

Slim 34px title strip for every app window: mono uppercase title, a small yellow tick when
focused, bare 40x34 button cells, crimson close on hover, 1px frame, square corners.
Translated 1:1 from the approved mockup `ref/mocks/components/ds-window-v2.html` (house
style `ref/mocks/components/ds-shell.css`). Target: KDE Plasma 6.8 / KWin, Wayland (CachyOS).

## Files

| File | What it is |
|---|---|
| `metadata.json` | KPlugin metadata (theme name "Endfield") |
| `decoration.svg` | the Aurorae artwork: frame pieces + button states, named elements |
| `EndfieldDecorationrc` | theme sizing (34px title, padding, button cells) - **rename on install** (below) |
| `minimize.svg` `maximize.svg` `close.svg` | the mockup's exact glyphs, standalone. Aurorae does not load these files - the same glyphs are embedded in `decoration.svg` with their state colours. Kept as the order asked, and as a clean source of truth for the paths. |

## Install

```sh
mkdir -p ~/.local/share/aurorae/themes
cp -r kwin/aurorae/Endfield ~/.local/share/aurorae/themes/
mv ~/.local/share/aurorae/themes/Endfield/EndfieldDecorationrc \
   ~/.local/share/aurorae/themes/Endfield/Endfieldrc
```

Two notes on the last step - both are honest uncertainty, see "Needs live check":

1. **rc file name.** The order named the settings file `EndfieldDecorationrc`. Aurorae's
   loader looks for the theme sizing file named after the theme directory, i.e.
   `Endfieldrc` inside `Endfield/`. The install step renames it. If your KWin ignores
   the values, try `themerc` as the name (the other one seen in the wild); the values
   stay the same.
2. **rc group name.** The keys sit in `[General]` (the kwin3-decoration-rc convention
   these key names come from). If the sizes don't take effect, move the same keys under
   `[Decoration]` or `[Layout]` - one of the three is what the loader reads.

## Select it

System Settings -> **Window Decorations** (Plasma 6 puts it under *Colors & Themes*;
if you can't find the page, run `systemsettings kcm_kwindecoration`) -> pick **Endfield**.

Button order (min / max / close on the right, nothing on the left) - in the same page's
"Titlebar Buttons" tab, or in `~/.config/kwinrc`:

```ini
[org.kde.kdecoration2]
ButtonsOnLeft=
ButtonsOnRight=IAX
```

Reload KWin if a manual edit doesn't show (Plasma 6 Wayland):

```sh
qdbus6 org.kde.KWin /KWin reconfigure    # or: qdbus org.kde.KWin /KWin reconfigure
```

## Fonts needed (the theme itself cannot set fonts)

- Mono (titles, buttons-adjacent small print): **JetBrains Mono** (Consolas-like).
- Sans (anything readable): **Inter** (Segoe-like).

The Aurorae/KWin engine draws the title text with a system font - there is no verified
font key in the theme rc (see ../README.md "Could not match"). Install the two fonts and
set the fixed-width font to JetBrains Mono in System Settings -> Fonts.

## Needs live check (first things to verify on a real Plasma 6.8 box)

1. `decoration.svg` **element ids** - this theme uses `top-left-active` ... `bottom-right-inactive`
   for the frame and `minimize-active` ... `close-pressed` for the buttons (state as suffix).
   That naming is my best reconstruction of the Aurorae SVG spec; if KWin draws an empty
   frame, the ids are the first thing to rename against a known-good theme.
2. Whether the KCM reads `metadata.json` for Aurorae themes (Plasma 6 wants JSON; older
   scanners read `metadata.desktop`). If "Endfield" doesn't appear, a one-file
   `metadata.desktop` with `Name=Endfield` is the fix - not shipped here because the order
   asked for `metadata.json` only.
3. rc file name + group name (both above).
4. That the 40x35 `top-left` slice is where the yellow tick lands next to the title text
   (slice sizes come from the art's bounding boxes in most SVG-9-slice loaders).
