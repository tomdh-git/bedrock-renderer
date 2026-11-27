## NEXT
DONE

## FILES
src/client/features/render/native/helpers/sub_9c650.h
src/client/features/render/native/helpers/sub_9c650.cpp
docs/functions/9c650.md

## LIFTCHECK
GATE OK 0x9C650
LIFTCHECK OK 0x9c650
cppsyntax: OK (syntax)
static_assert: present in source and dossier

## UNRESOLVED CALL
none

## NOTES
- Signature resolved: `void* sub_9c650(void* a0)` (RCX = release context { block@+0x0, end@+0x8, cap@+0x10 }); returns sub_e935700 result in RAX.
- sub_e935700 (`void* sub_e935700(void* a0)`) is a lift-set callee called directly via native symbol (forward-declared; see sub_e935700.h).
- Data-slot call at 0x9c73c `call qword ptr [0xF9A8C78]` modeled per brief rule 69: target read from data slot RVA 0xF9A8C78 at call time via `RewriteRegistry::imageBase() + 0xF9A8C78`, five zero arguments, noreturn (int3 follows). Not UNRESOLVED.
- All instructions of [0x9c650, 0x9c743) covered by range comment; all three calls quoted verbatim; no stub/TODO/[?]/UNVERIFIED left; no null guards or SEH the original does not have.

CLOSES? YES
