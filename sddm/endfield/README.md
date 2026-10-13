# endfield — SDDM theme (Qt6, SDDM >= 0.21)

Endfield lock v2 skin (yellow clock plate, tri-band, centred user plate) for the
CachyOS / KDE Plasma 6.8 login greeter.

## Install

Copy this whole folder to the system theme path:

```
sudo cp -r endfield /usr/share/sddm/themes/endfield
```

## Activate

`/etc/sddm.conf.d/10-endfield.conf` (create the drop-in; don't edit sddm.conf):

```ini
[Theme]
Current=endfield
```

## Test (no install, no session restart)

```
sddm-greeter-qt6 --test-mode --theme /usr/share/sddm/themes/endfield
```

To test in place before copying, point `--theme` at this folder instead.

Fonts the skin expects (install or change in `theme.conf`): **JetBrains Mono**
(mono), **Inter** (body). Keys in `theme.conf`: `monoFont`, `bodyFont`, `hostName`.

Full file-by-file install map, mockup mapping and limitations: see `../README.md`.
