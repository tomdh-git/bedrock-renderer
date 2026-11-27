## NEXT
DONE

## FILES
- src/client/features/render/native/helpers/sub_bb67fd0.h (rewritten: real state structs SubBb67fd0State / SubBb67fd0SrcRange / SubBb67fd0Block with offsetof static_asserts, resolved signature, extern "C" declaration of sub_1197a0)
- src/client/features/render/native/helpers/sub_bb67fd0.cpp (rewritten: lifted body, block-by-block with // 0xA..0xB range comments, no stubs / no return 0)
- docs/functions/bb67fd0.md (rewritten: resolved signature, register map, phases, field table, callees, DECISIONS resolved, ## Reversed source (complete))

## LIFTCHECK
`python tools/ctx/gate.py 0xBB67FD0` -> GATE OK 0xBB67FD0 (exit 0)
- cppsyntax: OK (syntax)
- liftcheck: LIFTCHECK OK 0xbb67fd0
- layout static_assert: present in source

## UNRESOLVED CALL
none (all three calls 0xbb6803e/0xbb68074/0xbb680a8 go to sub_1197a0, declared extern "C" in the .h; sub_1197a0 is a boundary candidate, not in the lift set)

CLOSES? YES
