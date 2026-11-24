#!/usr/bin/env python3
"""liftcheck.py - decides whether a function counts as lifted (L1, statically complete). Spec: docs/RENDER_NATIVE_SPEC.md section 2.

    python tools/sigs/liftcheck.py <rva> [<rva> ...]      e.g. 0xbc60740 or bc60740
    python tools/sigs/liftcheck.py --boundary             no raw function pointers out of lifted source (X6b; full call-target audit once native_boundary.tsv exists)

Prints one line per failed check and finally `LIFTCHECK OK <rva>` or `LIFTCHECK FAIL <rva>`; exit code 1 on any failure.
Checks:
  - dossier docs/functions/<rva>.md with a 'Reversed source' section free of [?]/[I]/TODO/UNVERIFIED;
  - source file under src/client/features/render/native/ whose first line is `// LIFT 0x<rva> size 0x<size> ...` with the right size, no stub/TODO text, a registry entry (LIFT_FN or NativeEntry), a static_assert;
  - instruction coverage: every instruction of [rva, rva+size) lies inside an address range cited in the source or dossier (`// 0xA..0xB`) or is quoted verbatim;
  - every `call` instruction is quoted verbatim (`0xRVA  call ...`, two spaces) in the source or dossier;
  - verify_oc mismatch=0 on all quoted instruction lines.
Chunked functions (size > 0x1800) are checked as a whole (the .asm item).
"""
import os, re, subprocess, sys, tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
os.chdir(ROOT)
NATIVE = "src/client/features/render/native"
PY = sys.executable
RDIS = os.path.abspath("tools/rdis/target/release/rdis.exe")
EXE = "C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe"
RANGE = re.compile(r"0x([0-9a-fA-F]{6,8})\s*\.\.\s*(?:0x)?([0-9a-fA-F]{6,8})")
QUOTE = re.compile(r"^\s*(?://\s*)?(?:0x)?([0-9a-fA-F]{7,8})  ([a-z]\S*)", re.M)
TRAIL = re.compile(r"//\s*(?:0x)?([0-9a-fA-F]{7,8})  ([a-z]\S*)")


def sizes():
    t = {}
    for l in open("docs/data/native_functions.tsv", encoding="utf-8"):
        if l.startswith("#") or not l.strip():
            continue
        f = l.split("\t")
        t[int(f[0], 16)] = int(f[1], 16)
    return t


def find_source(rva):
    pat = re.compile(r"^// LIFT 0x%x size 0x([0-9a-f]+)" % rva, re.I)
    for d, _, fs in os.walk(NATIVE):
        for n in fs:
            if n.endswith(".cpp"):
                p = os.path.join(d, n)
                try:
                    if pat.match(open(p, encoding="utf-8", errors="replace").readline()):
                        return p
                except OSError:
                    pass
    return None


def dossier(rva):
    for n in ("docs/functions/%x.md" % rva, "docs/functions/0x%x.md" % rva):
        if os.path.exists(n):
            return n
    return None


def instructions(rva, size):
    out = subprocess.run([RDIS, EXE, "dis", hex(rva), str(size)], capture_output=True, text=True).stdout.splitlines()
    r = []
    for l in out:
        m = re.match(r"\s+([0-9a-f]{7,8})\s+(.*)", l)
        if m and rva <= int(m.group(1), 16) < rva + size:
            r.append((int(m.group(1), 16), m.group(2).strip()))
    return r


def coverage(rva, size, text):
    ins = instructions(rva, size)
    if not ins:
        return ["rdis produced no instructions for %#x" % rva]
    rngs = [(int(a, 16), int(b, 16)) for a, b in RANGE.findall(text)]
    quoted = {int(a, 16) for a, _ in QUOTE.findall(text)} | {int(a, 16) for a, _ in TRAIL.findall(text)}
    unc = [a for a, _ in ins if a not in quoted and not any(lo <= a <= hi for lo, hi in rngs)]
    bad = []
    if unc:
        bad.append("instruction coverage incomplete: %d of %d instructions are in no cited range (first %s)" % (len(unc), len(ins), " ".join("%#x" % a for a in unc[:6])))
    calls = [a for a, t in ins if t.startswith("call")]
    nq = [a for a in calls if a not in quoted]
    if nq:
        bad.append("%d of %d call instructions not quoted verbatim (first %s)" % (len(nq), len(calls), " ".join("%#x" % a for a in nq[:6])))
    return bad


def check(rva, size):
    bad = []
    dn = dossier(rva)
    if not dn:
        return ["no dossier docs/functions/%x.md" % rva]
    txt = open(dn, encoding="utf-8").read()
    m = re.search(r"^#{2,4} Reversed source[^\n]*\n(.*?)(?=^#{2,4} (?!Reversed)|\Z)", txt, re.S | re.M)
    if not m:
        bad.append("dossier has no 'Reversed source' section")
    elif re.search(r"\[\?\]|\[I\]|TODO|UNVERIFIED", m.group(1)):
        bad.append("reversed-source block still has [?]/[I]/TODO/UNVERIFIED")
    sp = find_source(rva)
    if not sp:
        return bad + ["no source file under %s whose first line is '// LIFT 0x%x size 0x...'" % (NATIVE, rva)]
    src = open(sp, encoding="utf-8", errors="replace").read()
    ms = re.search(r"size 0x([0-9a-f]+)", src.split("\n", 1)[0])
    if ms and int(ms.group(1), 16) != size:
        bad.append("LIFT marker size 0x%s != function size 0x%x" % (ms.group(1), size))
    if re.search(r"\[\?\]|\[I\]|TODO|UNVERIFIED|not implemented|\bstub\b", src, re.I):
        bad.append("source has [?]/[I]/TODO/UNVERIFIED/stub")
    if not re.search(r"\bLIFT_FN\b|\bNativeEntry\b", src):
        bad.append("no registry entry (LIFT_FN / NativeEntry) in %s" % sp)
    if "static_assert" not in src and "static_assert" not in txt:
        bad.append("no layout assertion (static_assert) in source or dossier")
    both = src + "\n" + txt
    bad += coverage(rva, size, both)
    tf = tempfile.NamedTemporaryFile("w", suffix=".md", delete=False, encoding="utf-8")
    tf.write(both)
    tf.close()
    v = subprocess.run([PY, "tools/sigs/verify_oc.py", tf.name], capture_output=True, text=True).stdout
    os.unlink(tf.name)
    mv = re.search(r"mismatch=(\d+) no-such-instr=(\d+)", v)
    if not mv:
        bad.append("verify_oc found no quoted instruction lines")
    elif mv.group(1) != "0" or mv.group(2) != "0":
        bad.append("verify_oc: " + v.strip().splitlines()[-1])
    return bad


def boundary_check():
    rc = 0
    for d, _, fs in os.walk(NATIVE):
        for n in fs:
            if not n.endswith(".cpp"):
                continue
            s = open(os.path.join(d, n), encoding="utf-8", errors="replace").read()
            for m in re.finditer(r"reinterpret_cast<[^>]*\(\*\)[^>]*>\s*\(\s*(?:imageBase\(\)\s*\+\s*)?(0x[0-9a-fA-F]+)", s):
                print("%s: raw function pointer to %s (use the native:: symbol or a boundary wrapper)" % (n, m.group(1)))
                rc = 1
    if not os.path.exists("docs/data/native_boundary.tsv"):
        print("docs/data/native_boundary.tsv missing (X0b5)")
        rc = 1
    print("BOUNDARY OK" if rc == 0 else "BOUNDARY FAIL")
    return rc


def main():
    a = sys.argv[1:]
    if not a:
        print(__doc__)
        return 2
    if a == ["--boundary"]:
        return boundary_check()
    sz = sizes()
    rc = 0
    for x in a:
        rva = int(x, 16)
        if rva not in sz:
            print("%#x is not in docs/data/native_functions.tsv (add it with native_checklist_gen.py --add)" % rva)
            rc = 1
            continue
        bad = check(rva, sz[rva])
        for b in bad:
            print("  - " + b)
        print(("LIFTCHECK OK %#x" if not bad else "LIFTCHECK FAIL %#x") % rva)
        rc |= 1 if bad else 0
    return rc


sys.exit(main())
