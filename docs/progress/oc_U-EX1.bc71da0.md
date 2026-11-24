## NEXT
DONE: unit U-EX1.bc71da0 fully lifted; liftcheck printed LIFTCHECK OK 0xbc71da0; CLOSES? YES. Nothing left to resume.

## Log
- Read docs/OPENCODE_BRIEF.md, docs/RENDER_NATIVE_SPEC.md, input data _d_U-EX1.bc71da0.txt (0xbc71da0 size 0x167, "Frame renderer lambda", bgfx, D0, depth 6, 0 callees in set).
- Disassembled 0xbc71da0..0xbc71f07 with rdis (66 instructions, 6 calls, extent proven .pdata); sum confirmed range and return rax=a1.
- Callees: sub_ebdbf10 (0xbc71dce), sub_ebce390 x4 (0xbc71e0b/e37/e5c/e84), sub_ebdbf20 (0xbc71ef3). All three classified `lift` in docs/data/native_boundary.tsv (thunks: jmp [0xF9A7B10], jmp 0xEEC6EC0, jmp [0xF9A7B28]); not blockers per brief rule #66, forward-declared in the new header and called natively. No boundary calls, no unresolved calls.
- Key correction during analysis: bx tested after the first call is low16(a2), not the call's return; sub_ebdbf10's return is unused (matches sibling units bc6f800/bc6f2a0/bc6ee00). a2's low16 is the handle; a3 is written into the stream record; [rbp+0x50] (caller frame area, indeterminate) is copied as the trailing u64.
- Created docs/functions/bc71da0.md (dossier with analysis + 'Reversed source (complete)').
- Created src/client/features/render/native/bgfx/sub_bc71da0.h (Ctx/CommandStream overlays, offset constants, static_asserts, callee forward declarations, lifted signature).
- Created src/client/features/render/native/bgfx/sub_bc71da0.cpp (first line `// LIFT 0xbc71da0 size 0x167 1.26.62.01 sub_bc71da0`, full per-instruction cited body, LIFT_FN registry entry).
- No edits to Sigs.json, shared headers, CMake, hooks, BGFX_MAP, RENDER_CHECKLIST, or other units' files. No builds, no game.
- Ran python tools/sigs/liftcheck.py 0xbc71da0 -> LIFTCHECK OK 0xbc71da0 (verify_oc mismatch=0, no-such-instr=0; full instruction coverage; no banned tokens).

## FILES
docs/progress/oc_U-EX1.bc71da0.md
docs/functions/bc71da0.md
src/client/features/render/native/bgfx/sub_bc71da0.h
src/client/features/render/native/bgfx/sub_bc71da0.cpp

## LIFTCHECK
LIFTCHECK OK 0xbc71da0

## UNRESOLVED CALL
none

CLOSES? YES
