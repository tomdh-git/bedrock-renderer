## NEXT
DONE - lift source complete: dossier docs/functions/bc5b130.md, source src/client/features/render/native/bgfx/sub_bc5b130.h and sub_bc5b130.cpp; `python tools/sigs/liftcheck.py 0xbc5b130` printed LIFTCHECK OK 0xbc5b130. Not closed: blocked by UNRESOLVED CALLs (0xEEC75A0 and [0xF9A8ED0] are outside the lift set and native_boundary.tsv). Resume classification of those callees to reach CLOSES? YES.

## UNIT
Unit U-EX1.bc5b130, function 0xbc5b130, size 0x472 bytes ([0xbc5b130, 0xbc5b5a2)), depth 2, milestone 1, region bgfx, status D0->L1, name "VV frame-graph builder". Callees in lift set: none (row lists 0 callees in set). Result file: docs/progress/oc_U-EX1.bc5b130.md.

## FILES
- docs/progress/oc_U-EX1.bc5b130.md (this result file; created)
- docs/functions/bc5b130.md (dossier; created)
- src/client/features/render/native/bgfx/sub_bc5b130.h (new; layout constants + static_asserts + signature + footprint declaration)
- src/client/features/render/native/bgfx/sub_bc5b130.cpp (new; lifted source, first line `// LIFT 0xbc5b130 size 0x472 1.26.62.01 VV frame-graph builder`, LIFT_FN registry entry)

No other files were created or changed (Sigs.json, shared headers, CMake, hooks, and other units' files were not touched; no build was run).

## LIFTCHECK
LIFTCHECK OK 0xbc5b130

## UNRESOLVED CALL
0xEEC75A0 - IAT thunk: `0xeec75a0 jmp qword ptr [0xF9A8E60]` (rdis fn, size 0x6e). Called via `0xbc5b2d1  call 0xEEC75A0`, `0xbc5b312  call 0xEEC75A0`, `0xbc5b354  call 0xEEC75A0`, `0xbc5b39e  call 0xEEC75A0`, `0xbc5b42b  call 0xEEC75A0`, `0xbc5b4a3  call 0xEEC75A0`, `0xbc5b532  call 0xEEC75A0` [V]. Not in native_functions.tsv and not in native_boundary.tsv.
[0xF9A8ED0] - indirect float function loaded via `0xbc5b3d7  mov rsi,[0xF9A8ED0]` then `call rsi`, called at 0xbc5b3e2, 0xbc5b3f1, 0xbc5b45a, 0xbc5b469, 0xbc5b4ed, 0xbc5b4fa [V]. Not in native_functions.tsv and not in native_boundary.tsv.

Both targets are outside the lift set (the unit row lists 0 callees in the lift set) and outside native_boundary.tsv, so per the GOAL no wrapper is invented and no call statement is emitted in the lifted source; the 13 call sites are quoted verbatim in the source and their results are left as uninitialized locals. This is the unit's blocking fact.

## LIFTCHECK NOTES
- Every instruction of [0xbc5b130, 0xbc5b5a2) is inside a cited `// 0xA..0xB` range or quoted verbatim (coverage complete; 231 instructions).
- All 13 `call` instructions are quoted verbatim (`0xRVA  call target`, two spaces) in the source.
- verify_oc: mismatch=0, no-such-instr=0.
- Source and dossier reversed-source block are free of [?]/[I]/TODO/UNVERIFIED/stub/incomplete/not-implemented.
- LIFT_FN registry entry and static_assert present in source.

CLOSES? NO UNRESOLVED CALL: 0xEEC75A0 and [0xF9A8ED0] are outside the lift set and native_boundary.tsv, so they cannot be wrapped or called from lifted code; the unit cannot reach CLOSES? YES until those callees are classified.
