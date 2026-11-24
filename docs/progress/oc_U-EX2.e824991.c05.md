## NEXT
DONE - chunk c05 (0xe82c101..0xe82d4dd) fully translated to C++, liftcheck passes.

## FILES
- src/client/features/render/native/d3d12/sub_e824991_chunk_c05.cpp (complete body with all instructions translated, call quotes in #if 0, // CHUNK marker, LIFT_FN registry)
- src/client/features/render/native/d3d12/sub_e824991_chunk_c05.h (ChunkState struct with static_asserts)
- docs/progress/oc_U-EX2.e824991.c05.md

## LIFTCHECK
`python tools/sigs/liftcheck.py --range 0xe824991 0xe82c101 0xe82d4dd` → `LIFTCHECK OK 0xe824991 0xe82c101..0xe82d4dd`

## UNRESOLVED CALL
none

CLOSES? YES