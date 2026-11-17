import re, io, sys
# one-off helper: pull verbatim lines for listed RVAs from the _eg4a_*.txt rdis dumps
ADDRS = """
e814a8c e814ac3 e814aab e814ae7 e814a9d e814ab5 e814abe
e8143e3 e8143e7 e8143ef e814403 e814410 e81452c e814532 e814536 e81453d e814541 e814548 e81455b
e81458e e8145b9 e8145be e8145cc e8145d3 e8145db e8145e8 e814601 e814605 e81460e e814612 e81464d
e814652 e814659 e814664
e814bd8 e814bdb e814be1 e814cfe e814ea9 e814bac e814d34 e814d10 e814d05 e814d1f e814d24 e814d27
e814d9d e814da4 e814dab e814dae e814e0f e814e17 e814e1b e814e23 e814e2c e814e38 e814e48 e814e4f e814e64 e814e7a
e815242 e815245 e81524b e815250 e815260 e81530c e815314 e81532c e81534e e815453 e81545c e81545f
e81546e e815476 e81547e e815487 e81548b e8154b1 e8154b4 e8154c7 e8154e6 e8154eb e8154f7 e8154ff
e815430 e81543f e815447 e81544c e81553e e815541 e815545 e815548
e815866 e815869 e81586f e8159b4 e8159bf e8159cd e8159eb e8159f6 e815a01 e815a17 e815a65 e815a83
e815a3d e815ac9 e815ace e815b0d e815b2a e815b6d e815b72 e815b75 e815b86
e815d5f e815d58 e815c39 e815c3f e815d7a e815e90 e815fb0 e815fba
e80f2be e80f2d3 e80f2e4 e80f2ef e80f2f6 e80f34e e80f351 e80f387 e80f38f e80f3a0 e80f3d1
e818be9 e818bf0 e818bf7 e818bfa e818c00 e818c29 e818c47 e818c4f e818cb4 e818cb9 e818cbd e818cc1
e818cc4 e818cd2 e818cd6 e818cda e818d1e e818d2d e818dab e818e6d e818e73 e818e7e e818e8e e818e9e e818ea7
e819763 e819766 e81976e e819771 e8197a0 e8197ae e819822 e819825 e8197b4 e8197bb e8197ca e8197fb
e8197d5 e8197d9 e8197dd e819806 e81980d e81981a e81982a e81982e e819838 e81983c e819846
e8198af e8198b6 e8198b9 e81990a e819911 e819922 e81992c
e8143c0 e814544 e814a70 e8150f0 e815840 e815a34 e815c30 e815d70 e815d9c e815ea0 e818bc0 e819750
e80f385 e80f388 e819803
""".split()
want = {int(a, 16) for a in ADDRS}
files = ["_eg4a_create.txt", "_eg4a_resize2.txt", "_eg4a_blitsetup.txt", "_eg4a_dtor.txt",
         "_eg4a_update.txt", "_eg4a_tail.txt", "_eg4a_ovr.txt", "_eg4a_blit.txt"]
pat = re.compile(r"^\s*(?:0x)?([0-9a-fA-F]{6,8})\s\s(\S.*)$")
found = {}
for f in files:
    try:
        for ln in io.open("docs/progress/" + f, encoding="utf-8-sig", errors="replace"):
            m = pat.match(ln)
            if m:
                a = int(m.group(1), 16)
                if a in want and a not in found:
                    found[a] = (f, m.group(2).rstrip())
    except FileNotFoundError:
        print("MISSING FILE", f)
out = io.open("docs/progress/_eg4a_proofs.txt", "w", encoding="utf8")
missing = sorted(want - set(found))
for a in sorted(set(found) & want):
    f, t = found[a]
    out.write("0x%x  %s   ; from %s\n" % (a, t, f))
out.close()
print("found=%d missing=%d" % (len(found), len(missing)))
for a in missing:
    print("  no line for 0x%x" % a)
