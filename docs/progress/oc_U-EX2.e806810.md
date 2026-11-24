## NEXT
DONE — unit complete.

## UNIT
U-EX2.e806810: lift sub_e806810 (0xe806810, 0x11c bytes, depth 1, D0, d3d12). Range [0xe806810, 0xe80692c). Calls: 0xe834520, 0xe834330 (lift set), 0xeec6de0/0xeec6ec0 (classified lift in docs/data/native_boundary.tsv). No boundary wrappers, no UNRESOLVED CALL.

## DONE
- docs/functions/e806810.md — dossier with signature, register/arg map, 'Reversed source (complete)', struct fields touched, callees, verbatim call quotes.
- src/client/features/render/native/d3d12/sub_e806810.h — layout constants + static_asserts + callee forward declarations + signature.
- src/client/features/render/native/d3d12/sub_e806810.cpp — first line `// LIFT 0xe806810 size 0x11c 1.26.62.01 sub_e806810`, full faithful lift, LIFT_FN registry entry, #if 0 verbatim call quotes.
- docs/progress/oc_U-EX2.e806810.md — this file.

## FILES
- docs/functions/e806810.md (created)
- src/client/features/render/native/d3d12/sub_e806810.h (created)
- src/client/features/render/native/d3d12/sub_e806810.cpp (created)
- docs/progress/oc_U-EX2.e806810.md (created/updated)

## LIFTCHECK
LIFTCHECK OK 0xe806810

## UNRESOLVED CALL
none — all five call targets resolved: 0xe834520 and 0xe834330 are lift-set (forward-declared, called via native symbol); 0xeec6de0 and 0xeec6ec0 are classified `lift` in docs/data/native_boundary.tsv (forward-declared, called via native symbol).

## CLOSES?
CLOSES? YES
