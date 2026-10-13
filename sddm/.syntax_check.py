import configparser
import re
import xml.etree.ElementTree as ET

ok = True

def fail(msg):
    global ok
    ok = False
    print("FAIL:", msg)

for p in ["sddm/endfield/theme.conf", "sddm/endfield/metadata.desktop"]:
    c = configparser.ConfigParser()
    read = c.read(p)
    if not read:
        fail(p + " not parseable")
    else:
        print("INI OK:", p, "groups:", c.sections())
        for s in c.sections():
            print("   ", s, dict(c[s]))

for p in ["sddm/endfield/topo-floor.svg", "sddm/endfield/topo-floor-dark.svg"]:
    try:
        ET.parse(p)
        print("XML OK:", p)
    except Exception as e:
        fail(p + " XML: " + str(e))

dark = open("sddm/endfield/topo-floor-dark.svg").read()
orig = open("sddm/endfield/topo-floor.svg").read()
if "rgba(205,209,220," in dark:
    fail("light stroke left in dark variant")
elif dark.count("rgba(0,0,0,") != orig.count("rgba(205,209,220,"):
    fail("stroke count mismatch in dark variant")
else:
    print("recolor OK:", dark.count("rgba(0,0,0,"), "black strokes")

src = open("sddm/endfield/Main.qml").read()
s = re.sub(r"/\*.*?\*/", "", src, flags=re.S)
s = re.sub(r"//[^\n]*", "", s)
s = re.sub(r'"(\\.|[^"\\])*"', '""', s)
pairs = {"}": "{", ")": "(", "]": "["}
stack = []
for i, ch in enumerate(s):
    if ch in "{([":
        stack.append((ch, i))
    elif ch in pairs:
        if not stack or stack[-1][0] != pairs[ch]:
            fail("unbalanced %r at offset %d" % (ch, i))
            break
        stack.pop()
if stack:
    fail("leftover open brackets: %r" % (stack,))
else:
    print("Main.qml: brackets balanced")

for name in ["root", "plate", "passwordField", "userBox", "sessionBox", "goBtn",
             "avatarHost", "hud", "powerCell", "platePat", "avatarImg",
             "avatarCanvas", "dayShortText", "dateText"]:
    if not re.search(r"\bid:\s*" + name + r"\b", s):
        fail("missing id " + name)

print("Main.qml lines:", len(src.splitlines()))
print("ALL OK" if ok else "CHECKS FAILED")
raise SystemExit(0 if ok else 1)
