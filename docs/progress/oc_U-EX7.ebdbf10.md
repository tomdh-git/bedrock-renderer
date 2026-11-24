## NEXT DONE — unit complete: sub_ebdbf10 lifted, LIFTCHECK OK, CLOSES? YES.

## FILES
- created src/client/features/render/native/helpers/sub_ebdbf10.cpp (first line: // LIFT 0xebdbf10 size 0x7 1.26.62.01 sub_ebdbf10)
- created src/client/features/render/native/helpers/sub_ebdbf10.h (layout constants + static_asserts + signature `void sub_ebdbf10(void* lock)`)
- created docs/functions/ebdbf10.md (dossier with Reversed source (complete))

## LIFTCHECK
LIFTCHECK OK 0xebdbf10
(exit code 0; `python tools/sigs/liftcheck.py 0xebdbf10`)

## UNRESOLVED CALL
none: the function body is a single indirect tail jump `jmp qword ptr [0xF9A7B10]` (0xebdbf10, 7 bytes) through loader-resolved data slot 0xF9A7B10 — handled per boundary rule #69 (read the slot at call time, document the slot RVA; invoked as a function pointer forwarding RCX), no `call` instruction, no callee in either table, no blocker.

## Verification summary [V]
- rdis `dis 0xebdbf10`: `0xebdbf10  jmp qword ptr [0xF9A7B10] ; [data_f9a7b10]`, size 0x7 (REX.W FF 25, 7 bytes, ebdbf10..ebdbf16); `int3` at ebdbf17 is padding past the function span.
- rdis `sum`: one 8-byte read at &data_f9a7b10, ip 0xebdbf10, rw=R, size=8; no writes, no calls, no other fields.
- Argument: void* lock in RCX — callers pass &ctx->lock at ctx+0x1C0 [V: sub_bc70ca0.h, sub_bc66c50.h, bc66c50.md, bc71da0.md]; result in RAX as the slot target leaves it (return unused by callers).
- Lifted body: `return reinterpret_cast<void (*)(void*)>(*reinterpret_cast<uintptr_t*>(RewriteRegistry::imageBase() + 0xF9A7B10ull))(lock);` — 8-byte load from the slot, tail jump, RAX result as-is; `static_assert(sizeof(void*) == 8)`; LIFT_FN registry entry; no struct fields touched, no static_assert failure.
- cppsyntax: no errors in the lifted code (identical pre-existing framework-header include environment as accepted units; off-limits shared files untouched).

CLOSES? YES
