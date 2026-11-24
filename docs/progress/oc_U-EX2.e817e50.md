## NEXT
DONE — X2.e817e50 lifted. If resuming: nothing pending; awaiting orchestrator review (liftcheck OK). Next unit if any: pick from docs/RENDER_NATIVE_CHECKLIST.md.

Checklist line: X2.e817e50 LIFT sub_e817e50 (0xe817e50, 0x1fe bytes, depth 0, D0, 0 callees in set)

## FILES
- src/client/features/render/native/d3d12/sub_e817e50.h (new: layout constants + static_asserts + ABI signature)
- src/client/features/render/native/d3d12/sub_e817e50.cpp (new: LIFT marker, verbatim disassembly block, reversed body, LIFT_FN registry)
- docs/functions/0xe817e50.md (extended: added '## Reversed source (complete)' section; kept prior analysis)
- docs/progress/oc_U-EX2.e817e50.md (this result file)

## LIFTCHECK
```
LIFTCHECK OK 0xe817e50
```

## UNRESOLVED CALL
none

The function has exactly one call instruction, `0xe817eca  call qword ptr [0xF99FFA0]`. Slot
0xF99FFA0 holds sub_eea6040, a "jmp rax" hotpatch thunk; the caller preloads the real target
into rax (vtable[1] of the allocator at *[0x12ADF800]). sub_eea6040 (0xeea6040) is classified
`vendor` in docs/data/native_boundary.tsv (row "0xeea6040 vendor thunk via data slot 0xF99FFA0").
This is an indirect call through a data slot to a boundary thunk — not a blocker (brief hard rule
on indirect calls through data slots + boundary). Lifted as a direct call to the loaded target with
the same register arguments (rcx=allocator, rdx=oldptr, r8=0, r9=0, stack args 0).

## CLOSES? YES