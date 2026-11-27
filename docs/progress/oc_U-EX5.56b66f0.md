## NEXT
DONE

## FILES
- src/client/features/render/native/helpers/sub_56b66f0.cpp (lifted body replacing the __debugbreak placeholder, block by block)
- src/client/features/render/native/helpers/sub_56b66f0.h (real field names/types for the rcx/r14/rdi/rsp state structs with offsetof static_asserts)
- docs/functions/56b66f0.md (Reversed source section, field table, callees, DECISIONS, verbatim call quotes)

## LIFTCHECK
GATE OK 0x56B66F0
LIFTCHECK OK 0x56b66f0
cppsyntax: OK (syntax)
verify_oc: mismatch=0 no-such-instr=0
Full log: docs/progress/gate/0x56B66F0.log

## UNRESOLVED CALL
none

All three calls resolved: `call 0xE935700` at 0x56b6720 and 0x56b67b0 invoke lift-set callee sub_e935700 through its native symbol address (imageBase + 0xE935700; the bare `sub_e935700` name is multiply declared with conflicting signatures across project headers, so it is not referenced by name); `call qword ptr [0xF9A8C78]` at 0x56b67e5 is the data-slot indirect call on the noreturn corruption path, read via imageBase + 0xF9A8C78 and invoked as a 5-argument __cdecl invalid-parameter handler with all-zero args (documented, matches the bc97070 precedent for data slot 0xF9A8C78).

## DECISIONS SUMMARY
- Signature: `uintptr_t sub_56b66f0(void* self)` (rcx = self; return in rax). Return is sub_e935700's rax result on the release path, 0 on the empty-input path.
- sub_e935700 ABI: `void*(void*)`, argument in RCX, result in RAX (tail-jump thunk to sub_392960); recovered from its disassembly.
- rdi +0xe8 typed as void* (buffer pointer read via r14 = rdi + 0xe8), not uint8_t; +0xf8 is u64 size; +0x100 is the u8 flag compared to 1.
- rsp +0x30 xmm6 spill slot modeled as a local __m128i; stack slot has no external effect.
- Corruption path (block 17) calls data slot 0xF9A8C78 with all-zero args then `__assume(false)` for the trailing int3 (noreturn); no null guards or SEH the original does not have.
- No stubs, no return-0 placeholders, no TODO/[?]/UNVERIFIED/UNRESOLVED CALL markers left in .h/.cpp.

CLOSES? YES
