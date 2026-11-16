# oc U-F1b — VV pass order from frame builder 0x55f1450 (checklist F1b, BGFX_MAP 6ar)

Source: Minecraft.Windows.exe 1.26.62.01, RVAs relative to image base. Static analysis only (rdis disassembly of .text). Builder range: 0x55f1450..0x563f594 (size 0x4e144) [V preflight fn header].

## NEXT
Phase 1 (done): ran preflight 0x55f1450 -> docs/progress/pre/0x55f1450.md; fn header + callees captured. Phase 2: get full call skeleton of 0x55f1450..0x563f594 with vvskel.py, identify every pass-declaration call site in address order (callee = one of the 0x566xxxx-0x56a8xxx helpers, or other pass builders), then for each call site quote the call line plus surrounding name-building immediates and argument setup, resolve pass name via inline ASCII immediates / rdis str, note in/out resource ids from args. Write results phase by phase below; end with verify_oc.py. Unknowns flagged [UNVERIFIED: 0xrva question].

## Phase 1 — preflight (done)
- `PYTHONUTF8=1 python tools/preflight.py 0x55f1450` -> docs/progress/pre/0x55f1450.md [V]
- fn `sub_55f1450  [0x55f1450..0x563f594)  size 0x4e144  0 xrefs in` [V preflight]
- 0 direct callers (indirect/vtable dispatch only) [V preflight]
- Callees (from preflight, partial list through 0x56a8bb0): helpers in 0x566xxxx-0x569xxxx range called N..N times each are the candidate per-pass declaration helpers; full ordered call-site list still needed [V preflight callee set]

## Phase 2 — full ordered call skeleton of 0x55f1450..0x563f594
[pending] run `python tools/sigs/vvskel.py 0x55f1450 0x563f594` and filter for pass-declaration calls

## Phase 3 — per-pass entries (call site RVA, callee RVA, pass name, quoted instr lines, in/out resources)
[pending]

## Open
- Pass-name strings: names are built inline from 8-byte ASCII immediates (BGFX_MAP 6i), not .rdata strings; decode per call site or flag [UNVERIFIED: 0xrva]
- In/out resource identifiers per pass: visible only if passed as args in the declaration call; else [UNVERIFIED: 0xrva]

## TOOL REQUESTS
- None yet
