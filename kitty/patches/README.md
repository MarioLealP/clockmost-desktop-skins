# kitty patches (clockmost build)

kitty draws its tab bar on the terminal grid with the terminal font, so the mock's small tracked tab
labels (700 10px, .2em) can't be done from `tab_bar.py` alone.

- `0001-screen-draw_multicell-for-tab_bar.patch` (16 lines, kitty 0.49.2): adds
  `Screen.draw_multicell(text, width, scale, subscale_n, subscale_d, vertical_align, horizontal_align)`,
  a Python binding to kitty's existing `screen_handle_multicell_command` - the same cells the text-sizing
  protocol (OSC 66) makes. No renderer change. `tab_bar.py` draws each label letter at 2/3 size in its
  own cell (= small type + letter-spacing) and falls back to plain labels on stock kitty.

Package: the Arch PKGBUILD (gitlab.archlinux.org/archlinux/packaging/packages/kitty) with
`pkgrel=1.9`, the patch added to `source=` (b2sum SKIP) and

    prepare() {
      cd "${pkgbase}-${pkgver}"
      patch -Np1 -i ../0001-screen-draw_multicell-for-tab_bar.patch
    }

Built + installed in the VM 2026-10-13 (`kitty 0.49.2-1.9`). To do: move into the clockmost pkgs
pipeline so upgrades keep the patch.

Findings while getting there: `Screen.test_parse_written_data` does nothing on a tab-bar Screen (no
parser), so OSC 66 can't be fed in from Python; a sized plain space renders as a blank block (spaces go in
as U+00A0); underline thickness/position come from `modify_font` (global).
