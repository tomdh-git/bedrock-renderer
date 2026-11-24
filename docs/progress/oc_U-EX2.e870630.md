## NEXT
DONE: LIFTCHECK OK 0xe870630. All required files created and verified.

## DONE
- Created docs/functions/e870630.md with complete dossier, Reversed source (complete) covering every instruction in [0xe870630, 0xe8706ab), verbatim call quotes for all three calls.
- Created src/client/features/render/native/d3d12/sub_e870630.h with layout constants (kCookieGlobal, kIndirectSlot, kErrStrRef, kErrCtxRef, kExpectedSize), namespace e870630 stack offsets, static_asserts, signature, forward declaration of native::sub_eec6d80 (lift callee).
- Created src/client/features/render/native/d3d12/sub_e870630.cpp with first line `// LIFT 0xe870630 size 0x7b 1.26.62.01 BgfxFrameBuilder slot 16`, #if 0 block quoting every verbatim instruction line from 0xe870630..0xe8706ab, implementation matching the disassembly exactly (same reads, writes, calls in same order, same return), LIFT_FN registry entry.
- Ran `python tools/sigs/liftcheck.py 0xe870630` → `LIFTCHECK OK 0xe870630`.

## FILES
- docs/progress/oc_U-EX2.e870630.md (this file)
- docs/functions/e870630.md
- src/client/features/render/native/d3d12/sub_e870630.cpp
- src/client/features/render/native/d3d12/sub_e870630.h

## LIFTCHECK
LIFTCHECK OK 0xe870630

## UNRESOLVED CALL
none (0xe951550 boundary crt via native::boundary::sub_e951550; 0xeec6d80 lift via forward-declared native::sub_eec6d80; 0xF9A7480 indirect slot read-at-call-time per hard rule)

CLOSES? YES