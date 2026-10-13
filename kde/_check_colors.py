import configparser, re, sys

p = configparser.ConfigParser()
p.read('/home/benylin/felt-work/wt/S-kde/kde/EndfieldDark.colors')
want = ['Colors:View', 'Colors:Window', 'Colors:Button', 'Colors:Selection',
        'Colors:Tooltip', 'Colors:Complementary', 'Colors:Header', 'General', 'WM']
assert p.sections() == want, p.sections()
role_keys = {'BackgroundAlternate', 'BackgroundNormal', 'DecorationFocus', 'DecorationHover',
             'ForegroundActive', 'ForegroundInactive', 'ForegroundLink', 'ForegroundLinkVisited',
             'ForegroundNegative', 'ForegroundNeutral', 'ForegroundNormal', 'ForegroundPositive'}
ok = True
for s in want:
    keys = set(p[s].keys())
    if s in ('General', 'WM'):
        print(s, '->', sorted(keys))
        continue
    missing = role_keys - keys
    extra = keys - role_keys
    if missing or extra:
        ok = False
        print('BAD', s, 'missing', missing, 'extra', extra)
    else:
        print(s, '-> 12 role keys OK')
    for k in keys:
        v = p[s][k]
        if not re.fullmatch(r'\d{1,3},\d{1,3},\d{1,3}', v):
            ok = False
            print('BAD value', s, k, v)
        else:
            for n in v.split(','):
                if int(n) > 255:
                    ok = False
                    print('OUT OF RANGE', s, k, v)

checks = {
    ('Colors:View', 'BackgroundNormal'): '131417',
    ('Colors:View', 'BackgroundAlternate'): '15161a',
    ('Colors:Window', 'BackgroundNormal'): '15161a',
    ('Colors:Window', 'BackgroundAlternate'): '1a1b1f',
    ('Colors:Button', 'BackgroundNormal'): '26282d',
    ('Colors:Button', 'BackgroundAlternate'): '33363C',
    ('Colors:Button', 'ForegroundNormal'): 'c9ccd3',
    ('Colors:Selection', 'BackgroundNormal'): '242415',
    ('Colors:Selection', 'BackgroundAlternate'): '2b2b15',
    ('Colors:Selection', 'ForegroundNormal'): 'ffffff',
    ('Colors:Tooltip', 'BackgroundNormal'): '26282d',
    ('Colors:Complementary', 'BackgroundNormal'): '0e0f11',
    ('Colors:Complementary', 'BackgroundAlternate'): '101114',
    ('Colors:Header', 'BackgroundNormal'): 'f4f5f7',
    ('Colors:Header', 'BackgroundAlternate'): 'e6e7ea',
    ('Colors:Header', 'ForegroundNormal'): '111111',
    ('Colors:Header', 'ForegroundInactive'): '8a8d94',
    ('Colors:Header', 'ForegroundActive'): '33363C',
    ('Colors:View', 'ForegroundNormal'): 'f1f1f4',
    ('Colors:View', 'ForegroundInactive'): '7d8089',
    ('Colors:View', 'ForegroundActive'): 'FFFA00',
    ('Colors:View', 'ForegroundLink'): '5aa7ff',
    ('Colors:View', 'ForegroundLinkVisited'): 'cfc6f4',
    ('Colors:View', 'ForegroundNegative'): 'd91e36',
    ('Colors:View', 'ForegroundNeutral'): 'ff9e2c',
    ('Colors:View', 'ForegroundPositive'): '7ddb57',
    ('Colors:View', 'DecorationFocus'): 'FFFA00',
    ('WM', 'activeBackground'): '15161a',
    ('WM', 'activeForeground'): 'f1f1f4',
    ('WM', 'activeBlend'): '33363C',
    ('WM', 'inactiveBackground'): '101114',
    ('WM', 'inactiveForeground'): '7d8089',
    ('WM', 'inactiveBlend'): '26282d',
}
for (s, k), hexv in checks.items():
    r, g, b = [int(x) for x in p[s][k].split(',')]
    exp = int(hexv[0:2], 16), int(hexv[2:4], 16), int(hexv[4:6], 16)
    if (r, g, b) != exp:
        ok = False
        print('MISMATCH', s, k, (r, g, b), 'expected', exp)

def blend(a, f):
    return (round(a[0] * (1 - f) + 255 * f), round(a[1] * (1 - f) + 250 * f),
            round(a[2] * (1 - f) + 0 * f))

sel = tuple(int(x) for x in p['Colors:Selection']['BackgroundNormal'].split(','))
sela = tuple(int(x) for x in p['Colors:Selection']['BackgroundAlternate'].split(','))
print('7% blend over 131417 =', blend((19, 20, 23), 0.07), 'file has', sel)
print('10% blend over 131417 =', blend((19, 20, 23), 0.10), 'file has', sela)
if sel != blend((19, 20, 23), 0.07) or sela != blend((19, 20, 23), 0.10):
    ok = False
    print('SELECTION BLEND MISMATCH')
print('ALL OK' if ok else 'FAILURES ABOVE')
sys.exit(0 if ok else 1)
