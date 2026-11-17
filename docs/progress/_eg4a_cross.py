import re, io
# cross-check: every 0xaddr cited in the note (in backticked proof positions) must exist in _eg4a_proofs.txt
note = io.open("docs/progress/oc_U-EG4a.md", encoding="utf-8").read()
proofs = {}
for ln in io.open("docs/progress/_eg4a_proofs.txt", encoding="utf-8"):
    m = re.match(r"0x([0-9a-f]+)  (.*)$", ln.rstrip("\n"))
    if m: proofs[int(m.group(1), 16)] = m.group(2)
# citations of the form `0xaddr  instr` (two spaces) inside backticks
cites = re.findall(r"`\s*(?:0x)?([0-9a-fA-F]{6,8})  ", note)
cites = [int(c, 16) for c in cites]
missing = sorted(set(cites) - set(proofs))
print("cited=%d unique=%d proofs=%d missing=%d" % (len(cites), len(set(cites)), len(proofs), len(missing)))
for a in missing: print("  MISSING 0x%x" % a)
# duplicate first cells across table rows
rows = [l for l in note.splitlines() if l.startswith("|") and not l.startswith("|--") and "offset" not in l.lower()]
offs = [re.split(r"\s*\|\s*", l.strip("| "))[0].lower() for l in rows]
dups = sorted({o for o in offs if offs.count(o) > 1 and o})
print("rows=%d dup-first-cells=%s" % (len(rows), dups))
# movups/movsd etc inside rows: size-cell contradiction pre-check
SIZE = {"movups":16,"movaps":16,"movdqu":16,"movdqa":16,"movss":4,"movsd":8}
for l in rows:
    mm = re.search(r"0x[0-9a-f]+\s{2}(movups|movaps|movdqu|movdqa|movss|movsd)\b", l, re.I)
    if mm:
        c = re.split(r"\s*\|\s*", l.strip("| "))
        sz = re.search(r"\b(\d+)\s*B?\b", c[1])
        print("  SIMD-ROW", mm.group(1), "size-cell=", c[1], "OK" if sz and int(sz.group(1)) == SIZE[mm.group(1).lower()] else "FAIL")
print("etc-present:", "etc." in note.lower())
