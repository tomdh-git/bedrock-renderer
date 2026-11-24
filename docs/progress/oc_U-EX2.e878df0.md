## NEXT
DONE — function 0xe878df0 lifted (size 0x1e2), all files written, LIFTCHECK OK.

## FILES
Created:
- src/client/features/render/native/d3d12/sub_e878df0.h (layout constants, static_asserts, signature, forward declarations, boundary wrappers)
- src/client/features/render/native/d3d12/sub_e878df0.cpp (LIFT marker line 1, full reversal with // 0xA..0xB range citations, LIFT_FN registry entry, verbatim call quotes in #if 0 block)
- docs/functions/e878df0.md (dossier: signature, register map, phases, struct fields, callees, Reversed source (complete))

Changed:
- docs/progress/oc_U-EX2.e878df0.md (this result file)

## LIFTCHECK
LIFTCHECK OK 0xe878df0

## UNRESOLVED CALL
none

All 6 calls resolved:
- 0xe878e2f call qword ptr [0xF99FFA0] -> boundary::thunk_f99ffa0 (vendor, sub_eea6040 via data slot)
- 0xe878e7b call qword ptr [0xF99FFA0] -> boundary::thunk_f99ffa0 (vendor, sub_eea6040 via data slot)
- 0xe878ec0 call 0xE935700 -> native::sub_e935700 (lift set, jmp 0x392960)
- 0xe878f9e call 0x9BC830 -> boundary::sub_9bc830 (alloc, noreturn)
- 0xe878fad call 0x9BC830 -> boundary::sub_9bc830 (alloc, noreturn)
- 0xe878fcb call qword ptr [0xF9A8C78] -> boundary::terminate_f9a8c78 (CRT, std::terminate via IAT, dead path followed by int3)

CLOSES? YES
