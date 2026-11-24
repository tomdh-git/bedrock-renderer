import sys
path = sys.argv[1]
with open(path, encoding="utf8") as f:
    lines = f.readlines()
for i in (27, 28, 29):
    print(i, repr(lines[i - 1]))
