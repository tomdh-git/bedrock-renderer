## NEXT
DONE

## FILES
src/client/features/render/native/helpers/sub_1a1e80.h   (created)
src/client/features/render/native/helpers/sub_1a1e80.cpp (created)
docs/functions/1a1e80.md                                  (created)
docs/progress/oc_U-EX7.1a1e80.md                          (this file)

## GOAL (done)
Lifted sub_1a1e80 (0x1a1e80, size 0xd2, depth 0, D0) into C++ with the exact x64 ABI signature `void sub_1a1e80(void* a0)` (a0 = this in RCX, void return).

## LIFTCHECK
LIFTCHECK OK 0x1a1e80

## UNRESOLVED CALL
none

## NOTES
- Two direct calls: 0x1a1ec8 `call 0xE935700` and 0x1a1f16 `call 0xE935700`, both to native::sub_e935700 (lift set, already lifted: tail jump to sub_392960; declared via forward declaration matching sub_e935700.h, signature `void* sub_e935700(void*)`).
- One indirect call: 0x1a1f4b `call qword ptr [0xF9A8C78]` (failfast path, bias >= 0x20). Target read from data slot RVA 0xF9A8C78 at call time (PE: .rdata, stored qword is loader-resolved; runtime VA = imageBase() + 0xF9A8C78), called with (nullptr, nullptr, nullptr, nullptr) followed by `int3` at 0x1a1f51. Handled per brief rule 68 (indirect call through a data slot), exactly as the sibling lift sub_1a459d0 does for the same slot: `RewriteRegistry::imageBase() + kFailfastSlotRva`, `__debugbreak()` after. Slot RVA asserted in sub_1a1e80Layout.
- Field layout [V] from disassembly: this+0x40 flag byte (==1 required, reset to 0); buffers A (+0x20 ptr, +0x30, +0x38 vs 0x10) and B (+0x00 ptr, +0x10, +0x18 vs 0x18); ptr fields cleared with a single zero byte each (mov byte ptr), size fields reset to 0xF. Layout constants + offset static_asserts in sub_1a1e80.h (sub_1a1e80Layout).
- No null guards or SEH beyond the original's own tests; no skipped branches; every instruction of [0x1a1e80, 0x1a1f52) covered by cited ranges and/or verbatim quotes; all call quotes machine-checked by verify_oc via liftcheck.
- Registry entry: LIFT_FN(sub_1a1e80, "sub_1a1e80", 0x1a1e80, ::native::sub_1a1e80, nullptr).
- docs/data/native_boundary.tsv: 0x1a1e80 row class 'lift'; 0xe935700 row class 'lift'; data slot 0xF9A8C78 has no boundary row (not a blocker per brief rule 68).
- cppsyntax.py: OK (syntax). gate.py: GATE OK 0x1A1E80 (syntax + liftcheck + layout asserts).

## CLOSES?
CLOSES? YES
