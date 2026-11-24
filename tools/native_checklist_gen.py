#!/usr/bin/env python3
"""native_checklist_gen.py - builds docs/RENDER_NATIVE_CHECKLIST.md and its data files from the real call graph.

    python tools/native_checklist_gen.py            full regeneration (reads the exe through tools/sigs/inventory + xref; takes a few minutes)
    python tools/native_checklist_gen.py --cached   rebuild the checklist text from docs/data/native_functions.tsv (no exe needed)
    python tools/native_checklist_gen.py --expand   add chunk items for big functions whose plan file docs/data/native_chunks/<rva>.tsv exists
    python tools/native_checklist_gen.py --add RVA [RVA..] [--root NAME]
                                                    add functions found later (indirect callees, lambdas, helpers) to the lift set

One lift item per function. Ids: X<milestone>.<rva hex without 0x>, big functions (> BIG bytes) also get .plan / .cNN / .asm.
Done flags already ticked in the checklist are preserved. Dependencies (callees first, bottom-up) go to docs/data/native_deps.tsv,
read by tools/nextitems.py so a function is only handed out when everything it calls in the lift set is already done.
Spec: docs/RENDER_NATIVE_SPEC.md. Plan: docs/RENDER_DONE_STATE.md.
"""
import os, re, sys
from collections import defaultdict

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
os.chdir(ROOT)
D = "docs/data/"
FUNCS, DEPS, OUTSIDE = D + "native_functions.tsv", D + "native_deps.tsv", D + "native_boundary_candidates.tsv"
CHECK = "docs/RENDER_NATIVE_CHECKLIST.md"
_live = "docs/RENDER_CHECKLIST.md"   # after tools/native_activate.py the live checklist is the native one: regenerate it in place (ticks are kept)
if os.path.exists(_live) and "<!-- NATIVE -->" in open(_live, encoding="utf-8").read():
    CHECK = _live
BIG = 0x1800
MS = {"bgfx": 1, "d3d12": 2, "dragon": 3, "dragon-tasks": 3, "framebuilder": 4, "root": 4, "pass-tasks": 5, "frame-graph": 5}
TITLES = {
    1: "bgfx core, Frame, Encoder, handles, uniforms",
    2: "D3D12 backend: executor, flush, PSO, descriptors, resources",
    3: "RenderDragon: endFrame, generate, scheduler, task runner, Declarator",
    4: "FrameBuilder: inserts, visitors, extractors, descriptions, materials",
    5: "Frame-graph renderers and pass bodies (VV, Fancy, RTX, legacy)",
    7: "Indirect and helper functions found by closure expansion (X0a/X0b output)",
}
DIR = {1: "bgfx", 2: "d3d12", 3: "dragon", 4: "framebuilder", 5: "passes", 7: "helpers"}


def load():
    rows = []
    if not os.path.exists(FUNCS):
        return rows
    for l in open(FUNCS, encoding="utf-8"):
        if l.startswith("#") or not l.strip():
            continue
        f = l.rstrip("\n").split("\t")
        rows.append(dict(rva=int(f[0], 16), size=int(f[1], 16), depth=int(f[2]), ms=int(f[3]), region=f[4], status=f[5], name=f[6], root=f[7], callees=[int(x, 16) for x in f[8].split(",") if x], outside=[int(x, 16) for x in f[9].split(",") if x]))
    return rows


def save(rows):
    out = ["# rva\tsize\tdepth\tmilestone\tregion\tstatus\tname\troot\tcallees_in_set\tcallees_outside_set"]
    for r in sorted(rows, key=lambda r: r["rva"]):
        out.append("%#x\t%#x\t%d\t%d\t%s\t%s\t%s\t%s\t%s\t%s" % (r["rva"], r["size"], r["depth"], r["ms"], r["region"], r["status"], r["name"], r["root"], ",".join("%#x" % c for c in r["callees"]), ",".join("%#x" % c for c in r["outside"])))
    open(FUNCS, "w", encoding="utf-8").write("\n".join(out) + "\n")


def leaf_end(rva):
    """size recovery for functions without .pdata (leaf): walk instructions to the first ret/unconditional jmp that no earlier forward branch skips past"""
    import capstone
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_64); md.detail = False
    off = xref.rva2off(rva)
    if off is None:
        return None
    pc, far = rva, rva
    for ins in md.disasm(bytes(xref.f[off:off + 0x4000]), rva):
        pc = ins.address + ins.size
        if ins.mnemonic.startswith("j") and ins.op_str.startswith("0x"):
            t = int(ins.op_str, 16)
            if t > far and t < rva + 0x4000: far = t
        if ins.mnemonic in ("ret", "int3") or (ins.mnemonic == "jmp" and pc > far):
            return pc
    return None


def scan(extra_roots=None):
    """closure over the exe: reuse tools/sigs/closure.py (regions, ROOTS, status table) and keep the edges it throws away"""
    sys.path.insert(0, "tools/sigs")
    argv = sys.argv; sys.argv = ["x"]
    import closure, xref, inventory
    sys.argv = argv
    _, callees = inventory.call_map()
    st = closure.status_table()
    roots = dict(closure.ROOTS); roots.update(extra_roots or {})
    rp = D + "native_roots.txt"   # roots added with --add persist here: "<rva hex> <name>"
    if os.path.exists(rp):
        for l in open(rp, encoding="utf-8"):
            p = l.split(None, 1)
            if len(p) == 2 and not l.startswith("#"): roots[p[1].strip()] = int(p[0], 16)
    seen = {}
    from collections import deque
    q = deque()
    for n, r in roots.items():
        seen[r] = (0, n); q.append(r)
    while q:
        f = q.popleft(); d, root = seen[f]
        for c in callees.get(f, ()):
            if c in seen or closure.region(c) is None:
                continue
            seen[c] = (d + 1, root); q.append(c)
    rows = []
    for rva, (d, root) in seen.items():
        end = xref.fend(rva)
        if not end or end <= rva: end = leaf_end(rva)
        reg = closure.region(rva) or "root"
        s, name = st.get(rva, ("D0", ""))
        ins = sorted(c for c in callees.get(rva, ()) if c in seen and c != rva)
        outs = sorted(c for c in callees.get(rva, ()) if c not in seen)
        rows.append(dict(rva=rva, size=(end - rva) if end else 0, depth=d, ms=7 if (reg == "root" and root.startswith("added")) else MS[reg], region=reg, status=s, name=name or "", root=root, callees=ins, outside=outs))
    return rows


def sccs(nodes, edges):
    """Tarjan; returns {node: scc id}. Calls inside one SCC (recursion) are not dependencies."""
    idx, low, on, st, comp, n, c = {}, {}, set(), [], {}, [0], [0]
    sys.setrecursionlimit(100000)
    def go(v):
        idx[v] = low[v] = n[0]; n[0] += 1; st.append(v); on.add(v)
        for w in edges.get(v, ()):
            if w not in idx: go(w); low[v] = min(low[v], low[w])
            elif w in on: low[v] = min(low[v], idx[w])
        if low[v] == idx[v]:
            while True:
                w = st.pop(); on.discard(w); comp[w] = c[0]
                if w == v: break
            c[0] += 1
    for v in nodes:
        if v not in idx: go(v)
    return comp


def fid(r):
    return "X%d.%x" % (r["ms"], r["rva"])


def old_state():
    done, text = set(), {}
    if os.path.exists(CHECK):
        for l in open(CHECK, encoding="utf-8"):
            m = re.match(r"- \[(x| )\] (\S+) ", l)
            if m:
                text[m.group(2)] = l.rstrip("\n")
                if m.group(1) == "x": done.add(m.group(2))
    return done, text


def line(box, i, body):
    return "- [%s] %s %s" % (box, i, body)


def item_lines(r, done, chunks):
    i = fid(r); sz = r["size"]
    head = "%s (0x%x, 0x%x bytes, depth %d, %s, %d callees in set)" % (r["name"] or "sub_%x" % r["rva"], r["rva"], sz, r["depth"], r["status"], len(r["callees"]))
    if sz <= BIG:
        return [line("x" if i in done else " ", i, "LIFT " + head)]
    out = [line("x" if i + ".plan" in done else " ", i + ".plan", "PLAN %s: split 0x%x..0x%x at basic-block boundaries into chunks of <= 0x%x bytes, write docs/data/native_chunks/%x.tsv (start end role), then the checklist generator --expand adds the chunk items" % (r["name"] or "sub_%x" % r["rva"], r["rva"], r["rva"] + sz, BIG, r["rva"]))]
    ck = chunks.get(r["rva"])
    if ck:
        for n, (a, b) in enumerate(ck):
            out.append(line("x" if "%s.c%02d" % (i, n) in done else " ", "%s.c%02d" % (i, n), "LIFT CHUNK %s part %d/%d range 0x%x..0x%x" % (r["name"] or "sub_%x" % r["rva"], n + 1, len(ck), a, b)))
    out.append(line("x" if i + ".asm" in done else " ", i + ".asm", "LIFT ASSEMBLE %s: join the chunk sources into one function with the real prologue/epilogue and locals, one dossier, whole-function liftcheck" % (r["name"] or "sub_%x" % r["rva"]) if ck else "LIFT ASSEMBLE %s (waits for chunks)" % (r["name"] or "sub_%x" % r["rva"])))
    return out


def read_chunks():
    ck = {}
    p = D + "native_chunks"
    if os.path.isdir(p):
        for f in os.listdir(p):
            if f.endswith(".tsv"):
                rva = int(f[:-4], 16); rs = []
                for l in open(os.path.join(p, f), encoding="utf-8"):
                    if l.startswith("#") or not l.strip(): continue
                    a = l.split()
                    rs.append((int(a[0], 16), int(a[1], 16)))
                if rs: ck[rva] = rs
    return ck


def build(rows):
    done, old = old_state()
    chunks = read_chunks()
    by = {r["rva"]: r for r in rows}
    edges = {r["rva"]: [c for c in r["callees"] if c in by] for r in rows}
    comp = sccs(list(by), edges)
    height = {}
    def h(v):
        if v in height: return height[v]
        height[v] = 0
        height[v] = 1 + max([h(c) for c in edges[v] if comp[c] != comp[v]] or [-1])
        return height[v]
    for v in by: h(v)
    deps = []
    for r in rows:
        i = fid(r)
        ds = sorted({fid(by[c]) + (".asm" if by[c]["size"] > BIG else "") for c in edges[r["rva"]] if comp[c] != comp[r["rva"]]})
        if r["size"] > BIG:
            deps.append((i + ".plan", []))
            ck = chunks.get(r["rva"], [])
            for n in range(len(ck)): deps.append(("%s.c%02d" % (i, n), [i + ".plan"]))
            deps.append((i + ".asm", ds + [i + ".plan"] + ["%s.c%02d" % (i, n) for n in range(len(ck))]))
        else:
            deps.append((i, ds))
    open(DEPS, "w", encoding="utf-8").write("# id<TAB>ids that must be [x] first (callees in the lift set, SCC-internal calls excluded; X0 gates are implied for every X1-X7 id)\n" + "\n".join("%s\t%s" % (i, ",".join(d)) for i, d in deps) + "\n")
    secs = []
    for ms in sorted({r["ms"] for r in rows}):
        rs = sorted((r for r in rows if r["ms"] == ms), key=lambda r: (height[r["rva"]], r["rva"]))
        tb = sum(r["size"] for r in rs)
        secs.append("## X%d. %s\n\n%d functions, %d KB of machine code. Order = callees first. Source dir: `src/client/features/render/native/%s/`. Gate: X%dz.\n" % (ms, TITLES[ms], len(rs), tb // 1024, DIR[ms], ms))
        for r in rs:
            secs.append("\n".join(item_lines(r, done, chunks)))
        secs.append("- [ ] X%dz GATE (orchestrator): all X%d items [x]; build the DLL, fix compile errors, run the milestone verify scenes (docs/NATIVE_VERIFY_PROTOCOL.md), zero divergence; set functions.tsv rows to L2; push mirror" % (ms, ms))
        secs.append("")
    return "\n".join(secs), len(rows), sum(r["size"] for r in rows)


def head_and_x0():
    p = "docs/data/native_x0.md"   # hand-written X0 / X6 / XO sections live here so the generator never overwrites them
    return open(p, encoding="utf-8").read()


def write_check(rows):
    body, n, tb = build(rows)
    x0 = head_and_x0()
    fixed = x0.replace("{{GENERATED}}", body).replace("{{NFUNCS}}", str(n)).replace("{{NBYTES}}", "%.2f MB" % (tb / 1048576))
    # carry done flags of hand-written items
    done, _ = old_state()
    out = []
    for l in fixed.split("\n"):
        m = re.match(r"- \[ \] (\S+) ", l)
        if m and m.group(1) in done: l = l.replace("- [ ]", "- [x]", 1)
        out.append(l)
    open(CHECK, "w", encoding="utf-8").write("\n".join(out))
    print("%d functions, %.2f MB of code, checklist written to %s" % (n, tb / 1048576, CHECK))
    import subprocess
    env = dict(os.environ, CHECKLIST=CHECK, PYTHONUTF8="1")
    print(subprocess.run([sys.executable, "tools/checklist_status.py", "checklist