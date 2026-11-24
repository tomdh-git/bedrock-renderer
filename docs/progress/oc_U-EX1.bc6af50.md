## NEXT
DONE - liftcheck passed, unit complete

## FILES
- docs/progress/oc_U-EX1.bc6af50.md (this result file)
- src/client/features/render/native/bgfx/sub_bc6af50.h (new: layout constants, static_asserts, signature, fn1/fn2 declarations)
- src/client/features/render/native/bgfx/sub_bc6af50.cpp (new: lifted implementation, LIFT_FN registry entry)
- docs/functions/bc6af50.md (new: dossier with analysis and Reversed source)

## LIFTCHECK
LIFTCHECK OK 0xbc6af50

## UNRESOLVED CALL
none

All calls resolved:
- 0xEBCE430 (x3): library intrinsic memset, called via std::memset in C++
- [0xF9A8770] (x6): indirect fn1 through data slot, per spec section 69
- [0xF9A8780] (x4): indirect fn2 through data slot, per spec section 69
- 0xE951550 (x1): boundary crt, via native::Boundary wrapper (noreturn path)

## Ownership / threading
No shared mutable state; all writes are to stack-local buffer, caller-provided a2[] output array, or stack cookie slot. V2 footprint covers a2[0..a1).

CLOSES? YES
