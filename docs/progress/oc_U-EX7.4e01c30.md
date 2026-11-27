## NEXT
DONE: sub_4e01c30 lifted (0x4e01c30, size 0x9d, depth 0, milestone 7, region D0, 0 callees in set). All work complete: liftcheck prints LIFTCHECK OK 0x4e01c30.

## FILES
- src/client/features/render/native/helpers/sub_4e01c30.h (new: layout constants + static_asserts + signature)
- src/client/features/render/native/helpers/sub_4e01c30.cpp (new: // LIFT 0x4e01c30 size 0x9d 1.26.62.01 sub_4e01c30, verbatim quote block, lifted body, LIFT_FN registry entry)
- docs/functions/4e01c30.md (created: analysis, phases, struct fields, callees, Reversed source (complete))

## LIFTCHECK
LIFTCHECK OK 0x4e01c30

## UNRESOLVED CALL
none — the 3 calls (`0x4e01c5e`, `0x4e01ca6`, `0x4e01cbf` `call qword ptr [0xF99FFA0]`) target sub_eea6040, class `vendor` boundary (docs/data/native_boundary.tsv: "thunk via data slot 0xF99FFA0 (loader-resolved)"), 0xeea6040 = `jmp rax` [V]; lifted as direct vtable-entry calls (behaviorally identical; thunk is only a tail jump to RAX), following the sub_4e00d40 precedent. The `0x4e01c44 jmp rcx` computed jump is not a call; unknown table targets are tail-jumped with the exact register state (RCX=target, RDX=a1, R8=a2). `0x4e01c81 jmp rdx` is the vfptr[1] tail call via the same thunk.

## TOOL REQUESTS
None

CLOSES? YES
