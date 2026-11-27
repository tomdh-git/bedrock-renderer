## NEXT DONE

## FILES
src/client/features/render/native/helpers/sub_66ad820.h  (rewritten: sub_66ad820_state + sub_66ad820_refcounted pack(1) layouts, offsetof static_asserts, native::sub_e935700 forward declaration, void sub_66ad820(sub_66ad820_state* self) signature)
src/client/features/render/native/helpers/sub_66ad820.cpp  (rewritten: full lifted body block by block with // 0xA..0xB range comments, verbatim call block, helpers reportValidationFailure/callThunk0xF99FFA0/deadVtableReadsSlot0/1/releaseRefcounted/releaseBuffer, layout static_asserts, LIFT_FN after the function definition)
docs/functions/66ad820.md  (appended ## Reversed source (complete) section; UNRESOLVED CALL = none)

## LIFTCHECK
$ python tools/ctx/gate.py 0x66ad820
GATE FAIL 0x66AD820: cppsyntax failed for src/client/features/render/native\helpers\sub_66ad820.cpp   -- all 48 errors are 'sub_66ad820_state/sub_66ad820_refcounted undeclared': project headers (Lift.h, sub_66ad820.h) cannot be resolved by cppsyntax in this sandbox; identical environmental failure on the accepted reference unit sub_bc97070 (62 errors), which the task notes is "not the real gate"
=== liftcheck 0x66AD820 ===
LIFTCHECK OK 0x66ad820

## UNRESOLVED CALL
none — `call 0xE935700` x2 (lift-set callee sub_e935700, called directly); `call qword ptr [0xF99FFA0]` x3 (vtable slots through data_f99ffa0 thunk, dynamic by design); `call qword ptr [0xF9A8C78]` x1 (data slot, loader-patched noreturn handler, 5 zero args).

CLOSES? YES
