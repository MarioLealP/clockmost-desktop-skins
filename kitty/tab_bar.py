# tab_bar.py - the slim tab line from ds-kitty-v3.html, for kitty (>= 0.36).
# Install next to kitty.conf: ~/.config/kitty/tab_bar.py (loaded by "tab_bar_style custom").
#
# A tab is a label "1 · CLAUDE": inactive = dim, active = bright + yellow underline.
# Mock: 700 10px mono, .2em tracking. kitty draws its tab bar on the terminal grid, so with the
# clockmost kitty build (patches/0001: Screen.draw_multicell) each letter is drawn at 2/3 size in
# its own cell - small type, and the spare third of the cell becomes the letter-spacing.
# On stock kitty (no draw_multicell) it falls back to full-size labels.
# Colours: endfield.conf active/inactive_tab_foreground; active_tab_background = the yellow.

from kitty.fast_data_types import Screen
from kitty.tab_bar import DrawData, ExtraData, TabBarData, as_rgb
from kitty.utils import color_as_int

LEAD = '  '  # mock: 16px before the first label
GAP = '   '  # mock: 26px between labels
UNDERLINE_STRAIGHT = 1
SUBSCALE = (2, 3)  # 10px label on a ~15px terminal font
VALIGN_CENTER = 2


def _label(screen: Screen, text: str) -> None:
    draw_multicell = getattr(screen, 'draw_multicell', None)
    if draw_multicell is None:
        screen.draw(text)
        return
    n, d = SUBSCALE
    # every cell at the same scale so the underline is one straight line; kitty renders a sized
    # plain space as a blank block, so spaces go in as no-break spaces
    for ch in text:
        draw_multicell('\u00a0' if ch == ' ' else ch, width=1, subscale_n=n, subscale_d=d, vertical_align=VALIGN_CENTER)


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
    cur.bold = True  # mock labels are 700 in both states; colour carries active/inactive
    if tab.is_active:
        cur.decoration = UNDERLINE_STRAIGHT
        cur.decoration_fg = as_rgb(color_as_int(draw_data.active_bg))
    _label(screen, label)
    cur.decoration = 0
    cur.bold = False

    end = cur.x
    cur.fg = 0
    return end
