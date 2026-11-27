## NEXT
DONE

## FILES
src/client/features/render/native/helpers/sub_c28a920.h
src/client/features/render/native/helpers/sub_c28a920.cpp
docs/functions/c28a920.md

## LIFTCHECK
`python tools/sigs/liftcheck.py 0xc28a920` printed:
LIFTCHECK OK 0xc28a920
Gate: GATE OK 0xC28A920 (cppsyntax OK, liftcheck OK, layout static_assert present).

## UNRESOLVED CALL
none. All four calls resolved: `call 0xE935700` x3 (lift callee native::sub_e935700, forward-declared and called directly at 0xc28a950/0xc28a95d/0xc28a9d4); `call qword ptr [0xF9A8C78]` x1 at 0xc28aa04 (fail-handler data-slot indirect call, brief rule 69, target read from the slot at call time via RewriteRegistry::imageBase() + 0xF9A8C78, noreturn path).

## TOOL REQUESTS
None (no repo scripts added; no scratch files left in the repo).

CLOSES? YES
