## NEXT
DONE

## FILES
- src/client/features/render/native/helpers/sub_e93c790.cpp (rewrote body with real logic, removed __debugbreak/stub placeholders, added verbatim instruction quotes in #if 0 block)
- src/client/features/render/native/helpers/sub_e93c790.h (renamed struct fields, added r9 struct, static_asserts for every field, finalized signature)
- docs/functions/e93c790.md (filled DECISIONS, added Reversed source section, signature, phases, struct fields, calls)

## LIFTCHECK
GATE OK 0xE93C790
LIFTCHECK OK 0xe93c790
cppsyntax: OK (syntax)

## UNRESOLVED CALL
none

## Verification notes
- Function is a leaf: no call instructions, no boundary calls, no unresolved calls.
- Signature: std::uintptr_t sub_e93c790(std::uint8_t* a0 [RCX], std::uint8_t* a1 [RDX], std::uint32_t fill [R8]); returns RAX = R9 (destination pointer).
- Data tables data_EECAA20/EECB220/EECA910/EECAA10 and flag dword data_1230A11C read at imageBase()+RVA, matching the original's absolute-address operands.
- RBX spill/reload at [rsp+8] is callee-saved bookkeeping, no observable effect.
- RDX repurposed from end-pointer to SIMD mask index inside loops; R11 preserves original end for the scalar tail.
- No __debugbreak, no stubs, no TODO, no UNVERIFIED, no [?]/[I] markers remain.

CLOSES? YES
