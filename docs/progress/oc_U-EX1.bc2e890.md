## NEXT
DONE: sub_bc2e890 lifted (0xbc2e890, size 0x1de). Disassembly verified verbatim with rdis; both callees (0xE869FF0, 0x5669770) are class `lift` (docs/data/native_boundary.tsv lines 501-502) and are called via forward declarations native::sub_e869ff0 / native::sub_5669770 in the unit header. liftcheck prints `LIFTCHECK OK 0xbc2e890`.

## FILES
- docs/progress/oc_U-EX1.bc2e890.md (this file)
- docs/functions/bc2e890.md (analysis kept; 'Direct callees' and 'Calls not resolved' sections updated; 'Reversed source (complete)' replaced with the complete lifted source)
- src/client/features/render/native/bgfx/sub_bc2e890.h (rewritten: forward declarations of native::sub_e869ff0 / native::sub_5669770, layout constants, static_asserts, footprint)
- src/client/features/render/native/bgfx/sub_bc2e890.cpp (rewritten: complete lift, first line `// LIFT 0xbc2e890 size 0x1de 1.26.62.01 sub_bc2e890`, verbatim call quotes, LIFT_FN registry entry)

## LIFTCHECK
LIFTCHECK OK 0xbc2e890

## UNRESOLVED CALL
none

CLOSES? YES
