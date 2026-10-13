# Endfield window decoration (KWin, C++ / KDecoration3)

The mock's window frame (`ds-window-v2.html`): 34px near-black title bar, app name in 700 10px mono with .26em
tracking + uppercase, `·` + caption dimmed, 3x11 yellow tick on the focused window, hairline under the bar, 1px
frame (.10 / .22 focused), 40x34 buttons with the mock's glyphs (broken-X close, crimson on hover), deep shadow
(0 24px 60px .55). Every number is in `src/style.h` with the CSS it came from.

Why C++ and not Aurorae: the app name ("KITTY") is only exposed to C++ (`DecoratedWindow::windowClass()`), and
SVG themes can't letter-space or uppercase the title. Supersedes `../aurorae/` (kept as a fallback draft).

Motion: focus in/out 180ms OutCubic - the tick grows from its centre, the title slides right and brightens;
button hover fades in 120ms.

## Build / install (CachyOS)

    sudo pacman -S --needed base-devel cmake extra-cmake-modules
    cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr
    cmake --build build && sudo cmake --install build      # -> /usr/lib/qt6/plugins/org.kde.kdecoration3/
    kwriteconfig6 --file kwinrc --group org.kde.kdecoration2 --key library org.clockmost.endfield
    kwriteconfig6 --file kwinrc --group org.kde.kdecoration2 --key theme ""
    kwriteconfig6 --file kwinrc --group org.kde.kdecoration2 --key ButtonsOnLeft ""
    kwriteconfig6 --file kwinrc --group org.kde.kdecoration2 --key ButtonsOnRight "IAX"
    qdbus6 org.kde.KWin /KWin reconfigure

KWin keeps a loaded plugin in memory: after rebuilding, log out/in - or iterate in a nested compositor:
`kwin_wayland --wayland-display wayland-0 --no-lockscreen --width 1280 --height 720 --exit-with-session <cmd>`.

Not in the decoration (window content, not frame): the topo motif in the focused window's corner.
To do: package it in the clockmost pkgs pipeline.
