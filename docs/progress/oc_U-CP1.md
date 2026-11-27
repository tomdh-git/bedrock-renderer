## NEXT
DONE — CP1 (pack builder) and CP2 (tree) implemented and selftested.
Next: CP3 gate (tools/ctx/gate.py) and CP4 scaffold (tools/ctx/scaffold.py) per CTXPACK_PLAN.md.

## FILES CREATED/EDITED
- tools/ctx/__init__.py (new)
- tools/ctx/pack.py (new) — subcommands build, check, tree
- docs/progress/pack/SELFTEST.md (new) — real output from three item types

## VERIFICATION
- build 0xbc60d10 (single): OK — writes docs/progress/pack/bc60d10.md with all required sections, stamp line, DECISIONS
- check 0xbc60d10: FRESH
- tree 0xbc60d10 --depth 2: OK — one line per node with rva, name, status, signature, trust, size, boundary
- build 0xbc68e40 (plan): OK — same structure, picks up dossier + lifted sources
- check 0xbc68e40: FRESH
- tree 0xbc68e40 --depth 2: OK — walks 2 levels
- build 0xbc301c0 (chunk): OK — finds chunk function, lifted source, many callees
- check 0xbc301c0: FRESH
- tree 0xbc301c0 --depth 1: OK — lists direct callees with boundary class

All outputs under 60 lines by default; --full removes cap.

## TOOL REQUESTS
None

## OPEN
- None blocking this unit. CP1+CP2 complete.