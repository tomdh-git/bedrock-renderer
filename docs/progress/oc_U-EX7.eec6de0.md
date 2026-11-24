## NEXT
DONE

## FILES
created: src/client/features/render/native/helpers/sub_eec6de0.cpp
created: src/client/features/render/native/helpers/sub_eec6de0.h
created: docs/functions/eec6de0.md

## LIFTCHECK
LIFTCHECK OK 0xeec6de0

## UNRESOLVED CALL
none

## Summary
Function 0xeec6de0 (size 0x6) is a single-instruction indirect tail-jump thunk:
  0xeec6de0  jmp qword ptr [0xF9A8AA0]     ; [data_f9a8aa0]
Slot 0xF9A8AA0 (.rdata) resolves to VCRUNTIME140.dll!memmove [V: tools/sigs/peimports.py `0F9A8AA0  VCRUNTIME140.dll!memmove`]. The lifted function forwards dst (RCX), src (RDX), size (R8) unchanged to memmove and returns memmove's RAX result, with the exact x64 Microsoft ABI signature `void* sub_eec6de0(void*, const void*, std::uint64_t)`. No `call` instruction exists (tail-jump thunk), callees_in_set = none, no struct fields touched. Mirrored the established sibling convention (sub_eec5850/sub_eec5ae0/sub_eec5a10) in helpers/.

cppsyntax: 0 errors in sub_eec6de0.cpp itself; the 112 reported errors are pre-existing missing standard-header includes in shared headers Detour.h/Profiler.h (identical for every sibling unit; shared headers may not be edited per the rules).
liftcheck: LIFTCHECK OK 0xeec6de0 (coverage, verbatim jmp quote, static_assert, LIFT_FN registry entry all pass).

CLOSES? YES
