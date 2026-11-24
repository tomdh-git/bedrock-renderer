## NEXT
DONE — sub_e878bc0 (0xe878bc0, 0xba bytes) lifted; LIFTCHECK OK 0xe878bc0; no further steps.

## FILES
- docs/progress/oc_U-EX2.e878bc0.md (this result file)
- docs/functions/e878bc0.md (dossier: analysis + 'Reversed source (complete)')
- src/client/features/render/native/d3d12/sub_e878bc0.cpp (first line: // LIFT 0xe878bc0 size 0xba 1.26.62.01 sub_e878bc0; LIFT_FN registry entry)
- src/client/features/render/native/d3d12/sub_e878bc0.h (layout constants + static_asserts, callee forward declarations)

## LIFTCHECK
LIFTCHECK OK 0xe878bc0

## UNRESOLVED CALL
none — all calls are boundary/lift-class targets: 0x1f5ef50 (stl boundary, native_boundary.tsv line 211) called as boundary::sub_1f5ef50; 0xe935700 (lift class, forward-declared native::sub_e935700 in the unit header, own X7 unit); call qword ptr [0xF9A8C78] (IAT slot of _invoke_watson, noreturn, read at call time per the indirect-slot rule).

CLOSES? YES
