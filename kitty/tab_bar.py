# tab_bar.py - the slim tab line from ds-kitty-v3.html, for kitty (>= 0.36).
# Install next to kitty.conf: ~/.config/kitty/tab_bar.py (loaded by "tab_bar_style custom").
#
# A tab is a plain label "1 · CLAUDE": inactive = dim, active = bright with a short
# yellow underline (cell decoration, coloured via decoration_fg). Colours come from
# endfield.conf: active/inactive_tab_foreground, and active_tab_background = the yellow.
# Checked live in the VM against kitty 0.49.2 (2026-10-13).

from kitty.fast_data_types import Screen
from kitty.tab_bar import DrawData, ExtraData, TabBarData, as_rgb
from kitty.utils import color_as_int

# mockup: 16px before the first label, 26px between labels (~2-3 cells of JetBrains Mono)
LEAD = '  '
GAP = '   '
UNDERLINE_STRAIGHT = 1


def draw_tab(
    draw_data: DrawData,
    screen: Screen,
    tab: TabBarData,
    before: int,
    max_tab_length: int,
    index: int,
    is_last: bool,
    extra_data: ExtraData,
) -> int:
    cur = screen.cursor
    cur.bg = 0  # the tab line sits on the terminal's own (glass) background
    cur.bold = cur.italic = False
    screen.draw(LEAD if index == 1 else GAP)

    label = f'{index} · {tab.title.upper()}'  # kitty's index is already 1-based
    if 0 < max_tab_length < len(label):
        label = label[: max_tab_length - 1] + '…'

    cur.fg = as_rgb(draw_data.tab_fg(tab))
    if tab.is_active:
        cur.bold = True
        cur.decoration = UNDERLINE_STRAIGHT
        cur.decoration_fg = as_rgb(color_as_int(draw_data.active_bg))
    screen.draw(label)
    cur.decoration = 0
    cur.bold = False

    end = cur.x
    cur.fg = 0
    return end
