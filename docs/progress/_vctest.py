import re, sys
path = sys.argv[1]
pat = re.compile(r"\s*(?:0x)?([0-9a-fA-F]{6,8})\s{2,}([a-zA-Z]\S*(?: .*)?)", re.M)
n = 0
with open(path, encoding="utf8") as f:
    for i, ln in enumerate(f, 1):
        if pat.match(ln):
            n += 1
            if n <= 5:
                print(i, repr(ln[:80]))
print("total matching lines:", n)
