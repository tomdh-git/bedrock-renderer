## NEXT
DONE

## FILES
- src/client/features/render/native/helpers/sub_c28bc30.h (rewritten: real struct layout + offsetof/sizeof static_asserts)
- src/client/features/render/native/helpers/sub_c28bc30.cpp (rewritten: real lifted body, no placeholders)
- docs/functions/c28bc30.md (rewritten: full dossier with resolved DECISIONS)

## LIFTCHECK
GATE OK 0xC28BC30 / LIFTCHECK OK 0xc28bc30 (cppsyntax OK)

## UNRESOLVED CALL
none

## SUMMARY
Lifted sub_c28bc30 (0xc28bc30, size 0xbb). Walks a 0x10-byte element range [elementStart, elementEnd): for each element, acquires RefObject::refCount via lock cmpxchg (skip when 0), mutates the VftObject (stateByte +0x10 = 0; *refCountPtr +0x18 = 0xFFFF), then releases the RefObject (lock dec refCount -> sub_eea6040 via data slot 0xF99FFA0; lock dec weakCount -> sub_eea6040 via data slot 0xF99FFA0). Both eea6040 calls pass the object only (no flag), mirroring the listing. After the loop calls sub_6ae330(&this->nested), clears the nested range, returns 0 (rax zeroed via xorps). All calls go to lifted functions (sub_6ae330) or the vendor data slot (sub_eea6040). No stubs, no TODOs, no null guards the original lacks. GATE OK.

## CLOSES? YES
