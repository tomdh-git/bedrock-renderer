## NEXT

DONE

## FILES
src/client/features/render/native/helpers/sub_673cef0.cpp
src/client/features/render/native/helpers/sub_673cef0.h
docs/functions/673cef0.md

## LIFTCHECK
GATE OK 0x673CEF0 (tools/ctx/gate.py 0x673cef0). liftcheck LIFTCHECK OK; cppsyntax passed. Log: docs/progress/gate/0x673CEF0.log.

## UNRESOLVED CALL
none

## VERIFICATION
All 7 indirect calls via data slot 0xF99FFA0 go to vendor boundary sub_eea6040 (rdis fn: 5-byte jmp rax thunk at 0xeea6040), declared as ::native::Boundary<void*,void*,void*> sub_eea6040. Zero direct callees in the lift set. Struct layout verified by offsetof/static_asserts in .cpp inside namespace native::helpers. Four ref-counted objects released at self+0x50, self+0x40, self+0x30, self+0x08 in that order; last object's delete is a tail call (jmp rdx) and never returns. No exit path writes rax -> void return.

CLOSES? YES
