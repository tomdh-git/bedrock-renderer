## NEXT
DONE

## UNIT
U-EX7.5aba5c0: ThreadLocalObject<T>::get (per-thread frame-data block), 0x5aba5c0, size 0x10f, depth 0, D2, callees all resolved (lift set: sub_eec59e0/eec59f0/eec5a00/eec5a10; boundary: sub_9bc830 alloc, sub_9bd4a0 os, sub_9bd6d0 os, sub_eea6040 vendor thunk via slot 0xF99FFA0)

## PLAN
Complete. All steps done.

## FILES
- src/client/features/render/native/helpers/sub_5aba5c0.h (created): layout constants + static_asserts + signature + forward declarations + LIFT_FN
- src/client/features/render/native/helpers/sub_5aba5c0.cpp (created): instruction-complete reversal, verbatim call quotes, LIFT_FN registry entry
- docs/functions/5aba5c0.md (extended): added 'Reversed source (complete)' section

## VERIFICATION
- python tools/cppsyntax.py sub_5aba5c0.cpp -> OK (syntax)
- python tools/sigs/liftcheck.py 0x5aba5c0 -> LIFTCHECK OK 0x5aba5c0
- python tools/ctx/gate.py 0x5aba5c0 -> GATE OK 0x5ABA5C0

## LIFTCHECK
LIFTCHECK OK 0x5aba5c0

## UNRESOLVED CALL
none

CLOSES? YES
