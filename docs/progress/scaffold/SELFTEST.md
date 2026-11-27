# CP4 scaffold.py selftest

## Command run
```
python tools/ctx/scaffold.py 0xbc34f70 --out docs/progress/scaffold/out
python tools/ctx/scaffold.py 0xbc453a0 --out docs/progress/scaffold/out
python tools/ctx/scaffold.py 0xbc45780 --out docs/progress/scaffold/out
```

## Results
All three generated scaffolds:
- docs/progress/scaffold/out/sub_bc34f70.h / .cpp / bc34f70.md
- docs/progress/scaffold/out/sub_bc453a0.h / .cpp / bc453a0.md
- docs/progress/scaffold/out/sub_bc45780.h / .cpp / bc45780.md

## cppsyntax.py verification
```
python tools/cppsyntax.py docs/progress/scaffold/out/sub_bc34f70.cpp docs/progress/scaffold/out/sub_bc453a0.cpp docs/progress/scaffold/out/sub_bc45780.cpp
```
Output:
```
docs/progress/scaffold/out/sub_bc34f70.cpp: OK (syntax)
docs/progress/scaffold/out/sub_bc453a0.cpp: OK (syntax)
docs/progress/scaffold/out/sub_bc45780.cpp: OK (syntax)
```
Exit code: 0 (all pass).

## Verification notes
- Each scaffold reads size/name/region from `docs/data/native_functions.tsv` (never guesses).
- Refuses to overwrite existing files.
- .h contains layout constants `off_0x...` + `static_assert`s for every observed [reg+off] access (from rdis `fn`).
- .cpp first line: `// LIFT 0x<rva> size 0x<size> 1.26.62.01 <name>`
- .cpp includes quoted verbatim `0xRVA  call ...` lines for every call instruction (direct + indirect) inside `#if 0` block.
- .cpp has LIFT_FN placeholder registry entry (standalone, no Lift.h include).
- .md dossier has `## DECISIONS` section listing every fact the scaffold could not derive (marked [open]).
- No invented facts: unknown things are [open] decisions, not guesses.

## Items tested (from RENDER_CHECKLIST.md, still [ ])
- X1.bc34f70 — sub_bc34f70 (0xbc34f70, 0x113 bytes, depth 1, D0, 1 callee in set)
- X1.bc453a0 — sub_bc453a0 (0xbc453a0, 0x3d9 bytes, depth 3, D0, 2 callees in set)
- X1.bc45780 — sub_bc45780 (0xbc45780, 0x1da bytes, depth 3, D0, 2 callees in set)