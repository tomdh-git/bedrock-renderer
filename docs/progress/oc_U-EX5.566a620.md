## NEXT
DONE

## FILES
- src/client/features/render/native/helpers/sub_566a620.h (rewritten): sub_566a620_state layout (mRefCountedB +0x08, mRefCountedA +0x18, mData +0x28, mDataEnd +0x38, mFlag +0x40), RefCountedObject layout (vptr +0x00, strong +0x08, weak +0x0C), static_asserts for every field, void sub_566a620(sub_566a620_state* self) signature, forward declaration of native::sub_e935700
- src/client/features/render/native/helpers/sub_566a620.cpp (rewritten): complete lifted body with `// 0xA..0xB` range comments on every block, verbatim call quotes for all 5 calls, vtableDestroy/vtableDealloc helpers, reportWatsonFailure for [0xF9A8C78] data-slot noreturn handler, footprint declaration, LIFT_FN registration
- docs/functions/566a620.md (rewritten): dossier with Reversed source section, struct fields touched, callees, DECISIONS; all [open] markers resolved

## LIFTCHECK
`python tools/sigs/liftcheck.py 0x566a620` printed:
LIFTCHECK OK 0x566a620

`python tools/ctx/gate.py 0x566a620` printed:
GATE OK 0x566A620

## UNRESOLVED CALL
none. All five calls resolved: `call 0xE935700` x1 (lift callee sub_e935700, called directly), `call qword ptr [0xF99FFA0]` x3 (vtable slots 0/1 of mRefCountedA and mRefCountedB through the jmp-rax thunk, no static target by design), `call qword ptr [0xF9A8C78]` x1 (data-slot invalid-parameter handler, noreturn).

CLOSES? YES
