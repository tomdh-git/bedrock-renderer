## NEXT
DONE — unit complete and closed.

## FILES
Created:
- src/client/features/render/native/framebuilder/sub_6622590.cpp (first line `// LIFT 0x6622590 size 0x72 1.26.62.01 sub_6622590`; faithful C++ translation, verbatim call quotes, static_asserts, footprint, LIFT_FN registry entry)
- src/client/features/render/native/framebuilder/sub_6622590.h (ScopeCounter layout +0x10/+0x12, static_asserts, boundary declarations, ABI signature)
- docs/functions/6622590.md (dossier: signature, argument map, phases, struct fields, callees, name check, 'Reversed source (complete)' section)

Changed:
- docs/progress/oc_U-EX4.6622590.md (this result file)

No other files edited (no Sigs.json, no shared headers, no CMake, no hooks, no builds).

## LIFTCHECK
`python tools/sigs/liftcheck.py 0x6622590` printed:
LIFTCHECK OK 0x6622590
(exit code 0)

## UNRESOLVED CALL
none — all three calls (0xe938cb0, 0xe935740, 0xe938d70) are `os` boundary functions in docs/data/native_boundary.tsv, called through native::boundary wrappers. 0 callees in the lift set.

CLOSES? YES
