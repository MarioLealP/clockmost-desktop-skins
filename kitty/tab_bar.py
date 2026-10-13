# tab_bar.py - the slim tab line from ds-kitty-v3.html, for kitty.
# Install next to kitty.conf: ~/.config/kitty/tab_bar.py (kitty loads it when
# endfield.conf sets "tab_bar_style custom"). python3 syntax: ast.parse-clean.
#
# The kitty tab bar is ONE row of cells, so a tab is drawn as a plain label:
#   inactive: dim (inactive_tab_foreground), active: bright (active_tab_foreground)
#   + a short yellow underline under the active label.
# The underline uses the cell underline attribute; its colour comes from the
# decoration colour if this kitty build exposes one on the cursor object
# (decoration_color / underline_color), otherwise the underline matches the text
# colour. Live-check on the real machine - see README "Could not match".

from kitty.fast_data_types import Screen
from kitty.tab_bar import DrawData, ExtraData, TabBarData

# mockup: gap 26px between labels, 16px at the left; JetBrains Mono at 15px is
# ~9px wide, so 2-3 spaces. Letter-spacing (.16em) is not available in kitty.
GAP = '   '


def draw_tab(draw_data, screen, tab, before, max_title_length, index, is_last, extra_data=None):
    cur = screen.cursor
    screen.draw(GAP)

    # mockup labels: "1 · CLAUDE" - index, middot, uppercase title
    label = f'{index + 1} · {tab.title.upper()}'
    if 0 < max_title_length < len(label):
        label = label[: max_title_length - 1] + '~'

    active = getattr(tab, 'is_active', False)
    if active:
        cur.fg = getattr(draw_data, 'active_fg', 15)
    else:
        cur.fg = getattr(draw_data, 'inactive_fg', 8)

    can_underline = hasattr(cur, 'underline')
    if active and can_underline:
        cur.underline = True
        # yellow of the underline: draw_data.active_bg == active_tab_background
        yellow = getattr(draw_data, 'active_bg', 0xFFFA00)
        for attr in ('decoration_color', 'underline_color'):
            if hasattr(cur, attr):
                setattr(cur, attr, yellow)
                break

    screen.draw(label)

    if can_underline:
        cur.underline = False

    return cur.x
