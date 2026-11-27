## NEXT
DONE — lift complete; GATE OK 0x1126680.

## FILES
src/client/features/render/native/helpers/sub_1126680.cpp — replaced block skeleton with the lifted gradient color lookup
src/client/features/render/native/helpers/sub_1126680.h — finalized 5-argument signature; fixed field padding so offsetof/sizeof static_asserts hold
docs/functions/1126680.md — dossier completed: signature, argument map, instruction-complete phases, struct field table, verbatim instruction quotes, 'Reversed source' section

## LIFTCHECK
GATE OK 0x1126680 (python tools/ctx/gate.py 0x1126680, exit 0):
- cppsyntax: OK (cl /Zs parse + type check, no errors)
- liftcheck: OK — dossier has a 'Reversed source' section free of [?]/[I]/TODO/UNVERIFIED; source has no stub/TODO text; LIFT_FN registry entry present; layout static_asserts present in source and header; instruction coverage complete over [0x1126680, 0x112677e) via block range comments and verbatim quotes; no call instructions (leaf); verify_oc mismatch=0, no-such-instr=0 on all quoted instruction lines

## UNRESOLVED CALL
none

## CLOSES?
YES
