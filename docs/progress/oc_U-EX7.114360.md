## NEXT
DONE

## FILES
- src/client/features/render/native/helpers/sub_114360.h (finished: field names/types, callee ABIs, uintptr_t return)
- src/client/features/render/native/helpers/sub_114360.cpp (finished: introsort body, all 14 blocks translated, no debugbreak)
- docs/functions/114360.md (appended `## Reversed source (complete)` with the signature/field/callee decisions)

## LIFTCHECK
GATE OK 0x114360

=== cppsyntax src/client/features/render/native\helpers\sub_114360.cpp ===
src/client/features/render/native\helpers\sub_114360.cpp: OK (syntax)

=== liftcheck 0x114360 ===
LIFTCHECK OK 0x114360

## UNRESOLVED CALL
none

Notes: the four non-lift-set callees (0x114480, 0x1147e0, 0x114910, 0x1152e0) are declared in
sub_114360.h with the ABI their call sites require and are called as native::helpers symbols.
0xE951550 is called through the CRT boundary wrapper (declared with a register-wide result type
because the wrapper cannot be instantiated with a void result in this toolchain; the value is
discarded, matching the original's void call).

CLOSES? YES
