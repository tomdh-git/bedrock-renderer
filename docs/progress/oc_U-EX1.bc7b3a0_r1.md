## NEXT
DONE
Unit is lifted (LIFTCHECK OK). Close the unit NO: two callees (0xEEC75A0, 0xEEC73F0) have no liftable binding; only 0x78ed0 (boundary crt) is resolvable.

## FILES
docs/functions/bc7b3a0.md            (dossier: Reversed source, callee table, all calls quoted)
src/client/features/render/native/bgfx/sub_bc7b3a0.h   (signature, data RVAs, static_asserts)
src/client/features/render/native/bgfx/sub_bc7b3a0.cpp (LIFT marker, LIFT_FN, call quotes, trap block)

## LIFTCHECK
LIFTCHECK OK 0xbc7b3a0

## UNRESOLVED CALL
0xEEC75A0 — IAT thunk `jmp qword ptr [0xF9A8E60]`; `call 0xEEC75A0` at 0xbc7b41c, 0xbc7b4fb, 0xbc7b5d7 (per-channel index r0 inputs); absent from docs/data/native_functions.tsv and docs/data/native_boundary.tsv [V].
0xEEC73F0 — IAT thunk `jmp qword ptr [0xF9A8E08]`; `call 0xEEC73F0` at 0xbc7b44c, 0xbc7b524, 0xbc7b5ff (per-channel index r1 inputs); absent from docs/data/native_functions.tsv and docs/data/native_boundary.tsv [V].
Only resolvable callee: 0x78ed0 (boundary crt, native_boundary.tsv line 11), reached by `0xbc7b7bf  call 0x78ED0` followed by `0xbc7b7c4  int3` (trap block) [V].

CLOSES? NO sub_78ed0 is the only resolvable callee; 0xEEC75A0 and 0xEEC73F0 have no liftable binding, so the per-channel indices, table blends and stores cannot be reproduced
