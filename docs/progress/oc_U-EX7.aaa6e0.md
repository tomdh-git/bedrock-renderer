## NEXT
DONE - unit blocked on unresolved callee; see CLOSES? NO below.

## UNIT
U-EX7.aaa6e0 / sub_aaa6e0 at 0xaaa6e0, size 0xd7, depth 0, milestone 7, region root, D0
Checklist: X7.aaa6e0 LIFT sub_aaa6e0 (0xaaa6e0, 0xd7 bytes, depth 0, D0, 0 callees in set)

## FILES
- docs/progress/oc_U-EX7.aaa6e0.md (this result file)
- docs/functions/aaa6e0.md (dossier: mechanical facts, signature, reversed source pointer, calls, verification)
- src/client/features/render/native/helpers/sub_aaa6e0.h (layout constants + static_assert + signature)
- src/client/features/render/native/helpers/sub_aaa6e0.cpp (lifted body, LIFT marker, LIFT_FN registry entry)

## LIFTCHECK
`python tools/sigs/liftcheck.py 0xaaa6e0` printed:
LIFTCHECK OK 0xaaa6e0
Gate also printed: GATE OK 0xAAA6E0; cppsyntax OK.

## UNRESOLVED CALL
0xa89240 — direct call `0xaaa72c  call 0xA89240` (RCX = rdi + 0x18; return value discarded by caller).
What I saw: the callee is referenced in docs/data/native_functions.tsv only as `callees_outside_set: 0xa89240`; it is NOT a row in native_functions.tsv and NOT a row in docs/data/native_boundary.tsv. It appears only as `0xa89240 3 ?` (unclassified) in docs/data/native_boundary_candidates.tsv. Hence it is outside both tables (lift set and boundary), so per the GOAL it is an UNRESOLVED CALL: no native symbol, no wrapper invented, lifting stops here.

## LIFTCHECK NOTE
liftcheck passed (coverage 60/60 instructions, all 4 calls quoted verbatim, verify_oc mismatch=0, no stub/TODO/UNRESOLVED words in source or dossier reversed source, LIFT_FN registry entry present, static_assert present). The unresolved callee 0xa89240 does not fail liftcheck mechanically (liftcheck verifies quoting/coverage, not table membership), but it is a semantic blocker: the callee is outside both native_functions.tsv and native_boundary.tsv.

CLOSES? NO UNRESOLVED CALL 0xa89240 (direct call at 0xaaa72c `call 0xA89240`; callee outside both native_functions.tsv and native_boundary.tsv, only unclassified in native_boundary_candidates.tsv; no native symbol, no wrapper invented per GOAL)
