## NEXT
DONE: all artifacts written for U-EX3.e905ce0 (0xe905ce0 "Frame renderer lambda", size 0x19); liftcheck prints `LIFTCHECK OK 0xe905ce0`; CLOSES? NO due to UNRESOLVED CALL 0xeec6eb0 (callee in neither lift set nor boundary table; call at 0xe905cea cannot be resolved, no wrapper invented per GOAL). Nothing further for this unit.

## FILES
- docs/progress/oc_U-EX3.e905ce0.md — result file (rewritten)
- src/client/features/render/native/dragon/sub_e905ce0.cpp — new, first line `// LIFT 0xe905ce0 size 0x19 1.26.62.01 Frame renderer lambda`
- src/client/features/render/native/dragon/sub_e905ce0.h — new (layout constants + static_asserts + signature)
- docs/functions/e905ce0.md — new dossier with 'Reversed source (complete)'

## LIFTCHECK
`python tools/sigs/liftcheck.py 0xe905ce0` printed:
LIFTCHECK OK 0xe905ce0
(exit code 0). Checks passed: dossier 'Reversed source (complete)' free of [?]/[I]/TODO/UNVERIFIED; LIFT marker size 0x19 == function size 0x19; no stub/TODO text in source; LIFT_FN + static_assert present; all 7 instructions of [0xe905ce0, 0xe905cf9) inside cited range `0xe905ce0..0xe905cf9`; the single call quoted verbatim; verify_oc mismatch=0, no-such-instr=0.

## UNRESOLVED CALL
0xeec6eb0 — callee of `0xE905CEA  call 0xEEC6EB0`. Callee body [V] `0xeec6eb0  jmp qword ptr [0xF9A8A90]` (IAT import thunk through data slot 0xF9A8A90). CONFIRMED ABSENT from docs/data/native_functions.tsv and docs/data/native_boundary.tsv (case-insensitive grep of docs/data; hits only in listings). It is neither a lifted function (native symbol) nor a boundary wrapper. Per GOAL: reported here as UNRESOLVED CALL, no wrapper invented, unit stops.

CLOSES? NO 0xeec6eb0 is neither in docs/data/native_functions.tsv nor docs/data/native_boundary.tsv (IAT import thunk `jmp qword ptr [0xF9A8A90]`), so the call at 0xe905cea cannot be resolved to a lifted function or boundary wrapper; no wrapper invented per GOAL (single blocking fact).
