## NEXT
DONE

## FILES
src/client/features/render/native/helpers/sub_66a6060.h
src/client/features/render/native/helpers/sub_66a6060.cpp
docs/functions/66a6060.md (appended ## Reversed source (complete))

## LIFTCHECK
GATE OK 0x66A6060
cppsyntax: OK (syntax)
liftcheck: LIFTCHECK OK 0x66a6060

## UNRESOLVED CALL
none — all three calls (0xe938cb0, 0xe935740, 0xe938d70) are os boundary functions called through native::boundary wrappers.

## DECISIONS
- callee signatures not derivable from the listing; wrappers declared as void sub_e938cb0/sub_e935740/sub_e938d70 (4x uintptr_t) per the sub_6622590 convention for the same callees.
- globals data_129441AC / data_128767C8 / data_129441B0 read as dwords at absolute image addresses; TLS via __readgsqword(0x58), stride 8, dword at slot+4 compared signed (jle/jg).
- struct fields renamed: rcx begin@0x28 / end@0x30 / tail@0x40; entry flag0x10@0x10 (bit 0, read via r12 and rsi); offsetof static_asserts for every field read.
- return value: AL = (begin != end) && flag; upper RAX bytes retain the begin pointer (original writes AL only).

CLOSES? YES
