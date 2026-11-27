## NEXT
DONE

## FILES
- src/client/features/render/native/helpers/sub_11666d0.h
- src/client/features/render/native/helpers/sub_11666d0.cpp
- docs/functions/11666d0.md (appended ## Reversed source (complete))

## LIFTCHECK
GATE OK 0x11666D0 (liftcheck OK; cppsyntax OK)

## UNRESOLVED CALL
none

## NOTES
- The indirect `call qword ptr [0xF99FFA0]` (block 14) targets sub_eea6040 through data slot 0xF99FFA0; no static target by design. It is an indirect data-slot call, not an unresolved direct callee, so it is emitted as a function-pointer read from 0xF99FFA0 called with RCX=object.
- sub_eec5a10 (0xEEC5A10) is reached by `jmp` (tail call to _Mtx_unlock), not a `call`; declared as a native void function and tail-called from block 19.
- sub_eec59f0 (_Mtx_lock) returns int (eax tested); sub_eec5a00 (_Throw_Cpp_error) is [[noreturn]].
- Signature: void sub_11666d0(void* self); normal exit is a tail jump to _Mtx_unlock (void), error exits throw, so the function returns no value.

CLOSES? YES
