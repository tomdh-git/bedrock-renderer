## NEXT
DONE. Unit closed: scaffold.py built, selftest passed on three still-open items, cppsyntax.py accepts all three generated .cpp skeletons.

## UNIT
U-CP4 — build tools/ctx/scaffold.py <rva> [--out DIR]: generates .h (layout constants + static_asserts + signature from known facts), .cpp header (LIFT marker, LIFT_FN registry entry, quoted call lines), and docs/functions/<rva>.md dossier skeleton with ## DECISIONS. Refuses to overwrite; never invents a fact.

## FILES
Created:
- tools/ctx/__init__.py
- tools/ctx/scaffold.py
- docs/progress/scaffold/out/sub_bc34f70.h / sub_bc34f70.cpp / bc34f70.md
- docs/progress/scaffold/out/sub_bc453a0.h / sub_bc453a0.cpp / bc453a0.md
- docs/progress/scaffold/out/sub_bc45780.h / sub_bc45780.cpp / bc45780.md
- docs/progress/scaffold/SELFTEST.md

## SELFTEST
- Ran scaffold.py for three still-open items (bc34f70, bc453a0, bc45780) into --out dir.
- All three generated .cpp files pass `python tools/cppsyntax.py` (exit 0, "OK (syntax)").
- No files were overwritten; no facts invented (unknowns → [open] decisions in ## DECISIONS).

## VERIFICATION
- lookup from native_functions.tsv: size/name/region are read from the TSV, never guessed.
- disassembly from rdis `fn` covers exact [rva, rva+size) with control flow.
- observed [reg+off] → layout constants + static_asserts (all [V]).
- every call instruction quoted verbatim (direct + indirect) inside #if 0 for verify_oc parse.
- LIFT_FN placeholder registry entry in .cpp.
- dossier has ## DECISIONS section listing all [open] items (signature, struct layout, callee classes, return value, indirect targets).

## TOOL REQUESTS
None

CLOSES? YES