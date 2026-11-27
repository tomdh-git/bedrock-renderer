## NEXT
DONE - unit complete; CLOSES? YES

## UNIT
U-EX2.e87c6d0 — lift sub_e87c6d0 (0xe87c6d0, 0x9d bytes, depth 1, D0, d3d12 region).
Checklist line: X2.e87c6d0 LIFT sub_e87c6d0 (0xe87c6d0, 0x9d bytes, depth 1, D0, 1 callees in set).

## STATUS
- step 1 (write progress file): DONE
- step 2 (disassemble 0xe87c6d0): DONE — range [0xe87c6d0, 0xe87c76d), 42 instructions, 3 calls.
- step 3 (boundary classification): DONE — 0xbc75c30 lift set [V]; 0xe935700 class 'lift' per docs/data/native_boundary.tsv line 505 [V], called via native symbol (brief rule 66); call qword ptr [0xF9A8C78] is a data-slot indirect call (brief rule 69), pointer read from slot at call time, five zero args, not a blocker.
- step 4 (write header + source + dossier): DONE.
- step 5 (cppsyntax + liftcheck): DONE — cppsyntax OK; liftcheck printed LIFTCHECK OK 0xe87c6d0.

## FILES
- docs/progress/oc_U-EX2.e87c6d0.md (this result file)
- docs/functions/e87c6d0.md (dossier: signature, register map, Reversed source (complete), struct fields touched, callees, verification)
- src/client/features/render/native/d3d12/sub_e87c6d0.h (ArgLayout layout constants + static_asserts, forward declaration of native::sub_e935700, signature void sub_e87c6d0(void*))
- src/client/features/render/native/d3d12/sub_e87c6d0.cpp (first line `// LIFT 0xe87c6d0 size 0x9d 1.26.62.01 sub_e87c6d0`, full lift body, verbatim #if 0 quote block, static_asserts, LIFT_FN registry entry)

## LIFTCHECK
`python tools/sigs/liftcheck.py 0xe87c6d0` printed:

LIFTCHECK OK 0xe87c6d0

## UNRESOLVED CALL
none — every call target is either in the lift set (0xbc75c30 sub_bc75c30; 0xe935700 sub_e935700, boundary class 'lift', called through its native symbol) or a data-slot indirect call (0xe87c766 call qword ptr [0xF9A8C78], slot read at call time per brief rule 69, five null arguments).

CLOSES? YES
