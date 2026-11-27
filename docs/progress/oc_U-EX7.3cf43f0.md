## NEXT
DONE

## FILES
- src/client/features/render/native/helpers/sub_3cf43f0.cpp
- src/client/features/render/native/helpers/sub_3cf43f0.h
- docs/functions/3cf43f0.md

## LIFTCHECK
GATE OK 0x3CF43F0
cppsyntax: OK (syntax)
liftcheck: LIFTCHECK OK 0x3cf43f0

## UNRESOLVED CALL
0x3cf44e6  call qword ptr [0xF9A8C78] — data-slot indirect call in block 15 (error-path trap, unreachable for valid heap metadata); not a lift callee or boundary, left as data-slot reference documented in the dossier.

## Verbatim call quotes (in source #if 0 block)
0x3cf4420  call 0xE935700
0x3cf44a7  call 0xE935700
0x3cf44e6  call qword ptr [0xF9A8C78]

CLOSES? YES
