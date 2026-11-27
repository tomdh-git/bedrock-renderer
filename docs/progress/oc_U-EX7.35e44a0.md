## NEXT
DONE - all steps complete, LIFTCHECK OK

## UNIT
U-EX7.35e44a0: lift 0x35e44a0 (size 0x39, depth 0, milestone 7, region root, status D0, name empty, 0 callees in lift set per data file; disassembly reveals 2 calls: self-recursion and sub_e935700, both in lift set).
Contract: docs/RENDER_NATIVE_SPEC.md + docs/OPENCODE_BRIEF.md. Lift to C++ under src/client/features/render/native/helpers/ (sub_35e44a0 while name unknown), dossier docs/functions/35e44a0.md, result file this one.

## DONE
- step 1: progress file created (this file)
- step 2: disassembled 0x35e44a0 (0x39 bytes), analyzed control flow, identified struct fields at +0x0, +0x10, +0x19, two calls (self + sub_e935700)
- step 3: created dossier docs/functions/35e44a0.md with full reversed source section
- step 4: created header src/client/features/render/native/helpers/sub_35e44a0.h with layout constants (offsetof static_asserts) and forward declarations
- step 5: created source src/client/features/render/native/helpers/sub_35e44a0.cpp with LIFT marker, verbatim call quotes in #if 0, lifted body with instruction-range citations, LIFT_FN registration
- step 6: ran python tools/sigs/liftcheck.py 0x35e44a0 → LIFTCHECK OK

## FILES
- docs/functions/35e44a0.md
- src/client/features/render/native/helpers/sub_35e44a0.h
- src/client/features/render/native/helpers/sub_35e44a0.cpp
- docs/progress/oc_U-EX7.35e44a0.md (this file)

## LIFTCHECK
LIFTCHECK OK 0x35e44a0

## UNRESOLVED CALL
none

CLOSES? YES

## TOOL REQUESTS
None