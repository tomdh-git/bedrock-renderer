## NEXT
DONE

## FILES
docs/progress/oc_U-EX1.bc56190.md
docs/functions/bc56190.md
src/client/features/render/native/bgfx/sub_bc56190.cpp
src/client/features/render/native/bgfx/sub_bc56190.h

## UNRESOLVED CALL
0xE935700 at 0xbc56577: `0xbc56577  call 0xE935700` — direct call target neither in the lift set (callees_in_set empty per unit data) nor in docs/data/native_boundary.tsv. Checked docs/data/native_functions.tsv, native_boundary.tsv, function_classes.tsv, native_deps.tsv, native_roots.txt, native_unresolved_indirect.tsv: no entry. Not emitted in lifted code (no wrapper per unit rules); quoted verbatim in source for coverage.
0xF9A8C78 at 0xbc56600: `0xbc56600  call qword ptr [0xF9A8C78]` — import-slot (IAT) indirect call on the fail path; slot contents not statically known, not in either table. Same import slot flagged unresolved in oc_U-B7a. Not emitted in lifted code; quoted verbatim in source for coverage.
Resolved: 0x3BAFDC0 at 0xbc56525 — class stl, boundary per docs/data/native_boundary.tsv row 228; called via native::Boundary<void,void*,void*,void*,void*>{"sub_3bafdc0"}(&out->f_e8, flagptr, qptr2, a3).

## LIFTCHECK
LIFTCHECK OK 0xbc56190

CLOSES? NO UNRESOLVED CALL 0xE935700 at 0xbc56577 (direct call 0xE935700: target neither lifted nor boundary); import-slot call qword ptr [0xF9A8C78] at 0xbc56600 likewise outside both tables
