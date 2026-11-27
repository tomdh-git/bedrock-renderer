## NEXT
DONE

## FILES
- src/client/features/render/native/helpers/sub_568da90.h
- src/client/features/render/native/helpers/sub_568da90.cpp
- docs/functions/568da90.md

## LIFTCHECK
cppsyntax: OK (syntax)
liftcheck: LIFTCHECK OK 0x568da90
gate: GATE OK 0x568DA90

## UNRESOLVED CALL
none

## Verbatim call instructions (all present in the #if 0 block of the .cpp)
0x568dace  call 0x568DB90   -> sub_568db90 (lift set, native symbol)
0x568db0a  call 0xE935700   -> sub_e935700 (lift set, native symbol)
0x568db4e  call 0xE935700   -> sub_e935700 (lift set, native symbol)
0x568db80  call qword ptr [0xF9A8C78]   -> indirect via data slot 0xF9A8C78 (fail handler, 4 zero args, then int3 noreturn)

## Notes
- Signature: void sub_568da90(void* a0); RCX = context pointer, return void.
- sub_e935700 called with a single argument (RCX); return value unused.
- Buffer #1: begin at ctx+0x0, end at ctx+0x10. Buffer #2: begin at ctx+0x18, end at ctx+0x20, limit at ctx+0x28.
- Heap-header validation reads *(begin-8); fail path when probe >= 0x20 goes to the data-slot fail handler.
- Layout static_asserts in sub_568da90.h; Reversed source section in the dossier.
- CLOSES? YES
