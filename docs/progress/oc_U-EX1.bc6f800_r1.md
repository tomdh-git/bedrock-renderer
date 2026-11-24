## NEXT
DONE - U-EX1.bc6f800 lift complete: sub_bc6f800.h + sub_bc6f800.cpp written, docs/functions/bc6f800.md extended with 'Reversed source (complete)', `python tools/sigs/liftcheck.py 0xbc6f800` printed LIFTCHECK OK 0xbc6f800.

## UNIT
U-EX1.bc6f800 LIFT sub_bc6f800 (0xbc6f800, 0xbb bytes, depth 3, D0, 0 callees in set)

## STEP LOG
step 1 DONE — result file created (docs/progress/oc_U-EX1.bc6f800.md).
step 2 DONE — disassembly gathered [V]: sub_bc6f800 = 0xbc6f800..0xbc6f8bb (0xbb bytes, 1 block, ret at 0xbc6f8ba). Calls: 0xbc6f828 `0xbc6f828  call 0xEBDBF10` (lock; argument &ctx->bgfxLock at ctx+0x1C0), 0xbc6f870 `0xbc6f870  call 0xEBCE390` and 0xbc6f89c `0xbc6f89c  call 0xEBCE390` (append bytes; rcx=dst, rdx=src, r8d=size), 0xbc6f8ad `0xbc6f8ad  call 0xEBDBF20` (unlock). Fields [V] verbatim: [rdi+0x1CFD0C8] Frame*, [rax+0xE498AC] u16 count, [rax+rcx*2+0xE478AC] u16 list entry, [rsi+0xE05820] u32 cursor, [rsi+0xE05828] cmd-post bytes. Callee nature [V]: 0xEBCE390 = `jmp 0xEEC6EC0` forwarder; 0xEBDBF10 = `jmp qword ptr [0xF9A7B10]`; 0xEBDBF20 = `jmp qword ptr [0xF9A7B28]`. None of 0xebdbf10, 0xebce390, 0xebdbf20 is in native_functions.tsv or native_boundary.tsv → unclassified callees = blockers per hard rule #66; no wrapper invented (GOAL). Pattern: accepted U-EX1.bc6f2a0 unit has identical callees and liftcheck OK with sub_<rva> forward declarations.
step 3 DONE — wrote sub_bc6f800.h (layout constants + static_asserts, exact ABI signature, callee forward declarations) and sub_bc6f800.cpp (first line `// LIFT 0xbc6f800 size 0xbb 1.26.62.01 sub_bc6f800`, per-block `// 0xA..0xB` ranges with one verbatim instruction per line, verbatim call quotes, LIFT_FN registry entry); extended docs/functions/bc6f800.md with 'Reversed source (complete)' plus struct-fields and calls tables; `python tools/sigs/verify_oc.py` on source+dossier: claimed=43 match=43 mismatch=0 no-such-instr=0; `python tools/sigs/liftcheck.py 0xbc6f800` printed LIFTCHECK OK 0xbc6f800.

## FILES
- docs/progress/oc_U-EX1.bc6f800.md (this result file, written at every step)
- src/client/features/render/native/bgfx/sub_bc6f800.h (new: layout constants with static_asserts, exact ABI signature, callee forward declarations)
- src/client/features/render/native/bgfx/sub_bc6f800.cpp (new: first line `// LIFT 0xbc6f800 size 0xbb 1.26.62.01 sub_bc6f800`, lifted body, LIFT_FN registry entry)
- docs/functions/bc6f800.md (extended: kept existing analysis, added/replaced 'Reversed source (complete)' plus struct-fields and calls tables)

No other files edited (no Sigs.json, CMake, hooks, shared headers, or other units' files; no builds; no game).

## LIFTCHECK
claimed=43 match=43 mismatch=0 no-such-instr=0
LIFTCHECK OK 0xbc6f800

Exact command: `python tools/sigs/liftcheck.py 0xbc6f800` (exit code 0, no failure lines).

## UNRESOLVED CALL
0xebdbf10 — called at 0xbc6f828 `0xbc6f828  call 0xEBDBF10` (lock; argument is the address of the ctx+0x1C0 lock field): target is `jmp qword ptr [0xF9A7B10]`; not in native_functions.tsv, not in native_boundary.tsv.
0xebce390 — called at 0xbc6f870 `0xbc6f870  call 0xEBCE390` and 0xbc6f89c `0xbc6f89c  call 0xEBCE390` (append bytes; rcx=dst, rdx=src, r8d=size): target is `jmp 0xEEC6EC0`; not in either table.
0xebdbf20 — called at 0xbc6f8ad `0xbc6f8ad  call 0xEBDBF20` (unlock; argument is the address of the ctx+0x1C0 lock field): target is `jmp qword ptr [0xF9A7B28]`; not in either table.
Calls are bound in source via forward declarations `namespace native { void sub_ebdbf10(void*); void sub_ebce390(void*, const void*, std::uint32_t); void sub_ebdbf20(void*); }` (same pattern as the accepted U-EX1.bc6f2a0 unit); no wrapper invented per the GOAL.

CLOSES? NO UNRESOLVED CALL: 0xebdbf10, 0xebce390, 0xebdbf20 (called at 0xbc6f828 / 0xbc6f870+0xbc6f89c / 0xbc6f8ad) are in neither native_functions.tsv nor native_boundary.tsv, so the calls cannot be bound from lifted code and no wrapper may be invented.
