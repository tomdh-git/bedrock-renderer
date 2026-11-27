## NEXT
DONE

## FILES
docs/progress/oc_U-EX7.87440.md
src/client/features/render/native/helpers/sub_87440.h
src/client/features/render/native/helpers/sub_87440.cpp
docs/functions/87440.md

## LIFTCHECK
LIFTCHECK OK 0x87440

## UNRESOLVED CALL
none

## Summary
Lifted sub_87440 (0x87440, size 0xcf, depth 0). All callees are lift-classified:
- 0x9C590 sub_9c590 (call 0x9C590 at 0x87486)
- 0xE935700 sub_e935700 (call 0xE935700 at 0x874CD)
- 0x9C650 sub_9c650 (jmp 0x9C650 tail call at 0x874F0)
- Data slot 0xF9A8C78 (call qword ptr [0xF9A8C78] at 0x87508, five zero args, noreturn block, per brief rule 69)

Created:
- helpers/sub_87440.h: ReleaseContext layout (+0x28 child_begin, +0x30 child_end, +0x38 limit, +0x40 flag), static_asserts, forward declarations, signature void* sub_87440(void* a0)
- helpers/sub_87440.cpp: LIFT marker, verbatim #if 0 instruction block, complete C++ translation, LIFT_FN registration
- docs/functions/87440.md: dossier with Reversed source (complete)

Note: gate.py cppsyntax step fails on the LIFT_FN line (C4430/C2440), but this is a pre-existing toolchain issue — sub_9c590.cpp (existing, known-good code) fails identically. liftcheck passes cleanly.

CLOSES? YES
