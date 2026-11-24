## NEXT
DONE: sub_bc6f2a0 lifted and verified; liftcheck printed LIFTCHECK OK 0xbc6f2a0; unit closed.

## GOAL
LIFT TASK (native render checklist): lift function 0xbc6f2a0 (bgfx destroy-handle enqueue, cmd 0x1C, size 0xbb, depth 3, region bgfx, milestone D0) to C++ with the exact x64 ABI signature, same reads/writes/calls/return as the exe.

## FILES
- docs/progress/oc_U-EX1.bc6f2a0.md — created (this result file; step 1 wrote "## NEXT" / "step 2", now finished)
- src/client/features/render/native/bgfx/sub_bc6f2a0.cpp — verified against disassembly (0xbc6f2a0..0xbc6f35b, 44 instructions, 6 cited ranges, 4 verbatim call quotes); first line `// LIFT 0xbc6f2a0 size 0xbb 1.26.62.01 sub_bc6f2a0`; no change needed
- src/client/features/render/native/bgfx/sub_bc6f2a0.h — changed: callee forward-declaration comment updated (targets are `lift` per native_boundary.tsv, not unresolved blockers)
- docs/functions/bc6f2a0.md — changed: Calls table rows reclassified from unclassified blocker to lift (native_boundary.tsv lines 509-511)

## VERIFICATION BASIS
Disassembly ground truth (tools/rdis ... dis 0xbc6f2a0 0xbb + dis 0xbc6f343 40), 44 instructions, all inside cited ranges [0xbc6f2a0..0xbc6f2c9), [0xbc6f2c9..0xbc6f2ea), [0xbc6f2ea..0xbc6f311), [0xbc6f311..0xbc6f32a), [0xbc6f32a..0xbc6f343), [0xbc6f343..0xbc6f35b):
- 0xbc6f2c8  call 0xEBDBF10  (lock, arg &ctx->bgfxLock = ctx+0x1C0)
- 0xbc6f310  call 0xEBCE390  (append opcode byte 0x1C at f+0xE05828+cursor0)
- 0xbc6f33c  call 0xEBCE390  (append u16 handle at f+0xE05828+aligned)
- 0xbc6f34d  call 0xEBDBF20  (unlock)
Same reads/writes in order: lock ctx+0x1C0; Frame* = ctx->fillFrame [ctx+0x1CFD0C8]; f->handleList[f->handleListCount++] = handle [0xE45828/0xE47828]; cmd-post cursor [0xE05820] load, append 0x1C, cursor = (cursor & ~1) + 2, append handle LE u16, cursor += 2; unlock. Calls in order. Returns void. Callees 0xebce390/0xebdbf10/0xebdbf20 are `lift` (native_boundary.tsv) and called via forward-declared native::sub_<rva> with exact signatures (void sub_ebdbf10(void*), void sub_ebce390(void*, const void*, uint32_t), void sub_ebdbf20(void*)). No stubs, no skipped branches, no null guards/SEH; layout constants with static_asserts in the header; LIFT_FN registry entry in the .cpp.

## LIFTCHECK
LIFTCHECK OK 0xbc6f2a0

## UNRESOLVED CALL
none — all three callees are classified lift in docs/data/native_boundary.tsv (lines 509-511: 0xebce390, 0xebdbf10, 0xebdbf20), forward-declared and called directly per the hard rule for lift callees.

CLOSES? YES
