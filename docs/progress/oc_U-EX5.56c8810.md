## NEXT
DONE

## GOAL
LIFT 0x56c8810 (size 0xc4, "pass task render-thread body (class C, same template)")

## FILES
- docs/progress/oc_U-EX5.56c8810.md (this result file)
- docs/functions/56c8810.md (dossier)
- src/client/features/render/native/passes/sub_56c8810.h (layout constants + static_asserts + signature + forward declaration)
- src/client/features/render/native/passes/sub_56c8810.cpp (LIFT marker, full body, LIFT_FN registry, verbatim call quotes)

## LIFTCHECK
LIFTCHECK OK 0x56c8810

## UNRESOLVED CALL
none

## NOTES
- _d file: 0x56c8810 size 0xc4 depth 0, 0 callees_in_set, D2 status
- pack: 1 direct callee (sub_eec59e0, "set"/lift, forward-declare), sub_eea6040 via data slot 0xF99FFA0 (vendor/boundary)
- Listing verified against rdis dis 0x56c8810 200 (full 0xc4 bytes)
- Function is sibling of 0x568bcd0 (same template, different offsets: +0x100/+0x108/+0x110 vs +0x2E0/+0x2E8/+0x2F0)
- sub_eec59e0 is [[noreturn]] (std::_Xbad_function_call via data slot 0xF9A7310)

## GATE
GATE OK 0x56C8810

CLOSES? YES