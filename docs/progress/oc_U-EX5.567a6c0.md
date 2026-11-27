## NEXT
DONE

## FILES
- src/client/features/render/native/helpers/sub_567a6c0.cpp
- src/client/features/render/native/helpers/sub_567a6c0.h
- docs/functions/567a6c0.md

## LIFTCHECK
LIFTCHECK OK 0x567a6c0
GATE OK 0x567A6C0

## UNRESOLVED CALL
none

## Summary
Lifted sub_567a6c0 (0x567a6c0, size 0xef) into C++. The function releases every 0x50-byte element in region [a0+0x18, a0+0x20), then releases the backing heap block at [a0+0x8]. Calls sub_e935700 (lift set, native symbol) for each releasable element and for the final heap block. On heap corruption, calls data slot 0xF9A8C78 (noreturn fail handler, 4 zero args). Null heap base returns immediately. Returns void* (sub_e935700's result via tail call, or nullptr on null path). Structs Sub567a6c0This and Sub567a6c0Elem with offsetof static_asserts for every accessed field. All instructions covered by range comments; both calls quoted verbatim; no stubs/TODO/[?]/UNVERIFIED markers.

CLOSES? YES
