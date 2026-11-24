## NEXT
DONE - U-EX1.bc6f2a0 lift complete: sub_bc6f2a0.h + sub_bc6f2a0.cpp written, docs/functions/bc6f2a0.md extended with 'Reversed source (complete)', liftcheck printed LIFTCHECK OK 0xbc6f2a0.

## UNIT
U-EX1.bc6f2a0 LIFT sub_bc6f2a0 (0xbc6f2a0, 0xbb bytes, depth 3, D0, 0 callees in set)

## STEP LOG
step 1 DONE — result file created.
step 2 DONE — disassembly gathered [V]: sub_bc6f2a0 = 0xbc6f2a0..0xbc6f35b (0xbb bytes, 1 block, ret at 0xbc6f35a). Calls: 0xbc6f2c8 `call 0xEBDBF10` (lock, arg = &ctx->bgfxLock at ctx+0x1C0), 0xbc6f310 + 0xbc6f33c `call 0xEBCE390` (append bytes: rcx=dst, rdx=src, r8d=size), 0xbc6f34d `call 0xEBDBF20` (unlock). Fields verified verbatim: [rdi+0x1CFD0C8] Frame*, [rax+0xE47828] u16 count, [rax+rcx*2+0xE45828] u16 list, [rsi+0xE05820] u32 cursor, [rsi+0xE05828] cmd bytes. Callees not in native_functions.tsv / native_boundary.tsv → unclassified callees = blockers per hard rule #66. 0xEBCE390 is a jmp-forwarder to 0xEEC6EC0 (preflight 0xEBCE390), also unclassified.
step 3 DONE — wrote src/client/features/render/native/bgfx/sub_bc6f2a0.h (layout constants + static_asserts, signature, callee forward declarations) and sub_bc6f2a0.cpp (LIFT marker, per-block `// 0xA..0xB` ranges, verbatim call quotes, LIFT_FN registry entry); extended docs/functions/bc6f2a0.md with 'Reversed source (complete)', struct-fields and calls tables; `python tools/sigs/liftcheck.py 0xbc6f2a0` printed LIFTCHECK OK 0xbc6f2a0.

## FILES
- docs/progress/oc_U-EX1.bc6f2a0.md (this result file, written at every step)
- src/client/features/render/native/bgfx/sub_bc6f2a0.h (new: layout constants with static_asserts, exact ABI signature, callee forward declarations)
- src/client/features/render/native/bgfx/sub_bc6f2a0.cpp (new: first line `// LIFT 0xbc6f2a0 size 0xbb 1.26.62.01 sub_bc6f2a0`, lifted body, LIFT_FN registry entry)
- docs/functions/bc6f2a0.md (extended: kept existing analysis, added/replaced 'Reversed source (complete)' plus struct-fields and calls tables)

No other files edited (no Sigs.json, CMake, hooks, shared headers, or other units' files; no builds; no game).

## LIFTCHECK
LIFTCHECK OK 0xbc6f2a0

Exact command: `python tools/sigs/liftcheck.py 0xbc6f2a0` (exit code 0, no failure lines).

## UNRESOLVED CALL
0xebdbf10 — called at 0xbc6f2c8 `0xbc6f2c8  call 0xEBDBF10` (lock; argument is the address of the ctx+0x1C0 lock field): not in native_functions.tsv, not in native_boundary.tsv.
0xebce390 — called at 0xbc6f310 `0xbc6f310  call 0xEBCE390` and 0xbc6f33c `0xbc6f33c  call 0xEBCE390` (append bytes; rcx=dst, rdx=src, r8d=size): not in either table; entry 0xEBCE390 is itself a jmp-forwarder to 0xEEC6EC0 (preflight 0xEBCE390 `ebce390 jmp 0xEEC6EC0`), also unclassified.
0xebdbf20 — called at 0xbc6f34d `0xbc6f34d  call 0xEBDBF20` (unlock; argument is the address of the ctx+0x1C0 lock field): not in either table.
(0xEEC6EC0, the forwarder target of 0xEBCE390, is likewise unclassified.)

## CLOSES
CLOSES? NO UNRESOLVED CALL: 0xebdbf10, 0xebce390, 0xebdbf20 (called at 0xbc6f2c8 / 0xbc6f310+0xbc6f33c / 0xbc6f34d) are in neither native_functions.tsv nor native_boundary.tsv, so the calls cannot be bound from lifted code and no wrapper may be invented.
