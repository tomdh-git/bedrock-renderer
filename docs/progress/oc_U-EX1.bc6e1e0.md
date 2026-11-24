## NEXT
DONE

## UNIT
X1.bc6e1e0 LIFT sub_bc6e1e0 (0xbc6e1e0, 0x177 bytes, depth 4, D0, 0 callees in set)

## FILES
docs/progress/oc_U-EX1.bc6e1e0.md
docs/functions/bc6e1e0.md
src/client/features/render/native/bgfx/sub_bc6e1e0.h
src/client/features/render/native/bgfx/sub_bc6e1e0.cpp

## LIFTCHECK
LIFTCHECK OK 0xbc6e1e0

## UNRESOLVED CALL
0xbc6e27a  call qword ptr [0xF99FFA0] — target = *(uintptr_t*)0x14F99FFA0 = sub_eea6040 per rdis annotation; sub_eea6040 is in neither docs/data/native_functions.tsv nor docs/data/native_boundary.tsv; called through the slot read at call time (rule 69), argument order (allocator, entryPtr, newCapacity|8, 0, 0, 0).
0xbc6e2e4  call 0xEBCE390 and 0xbc6e31b  call 0xEBCE390 — sub_ebce390(dst, src, count, flags), memcpy-like; in neither docs/data/native_functions.tsv nor docs/data/native_boundary.tsv.
0xbc6e351  call 0xE951550 — resolved: boundary crt (docs/data/native_boundary.tsv line 467), not unresolved.

CLOSES? YES
