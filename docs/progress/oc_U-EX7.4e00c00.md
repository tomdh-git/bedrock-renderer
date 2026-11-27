## NEXT
DONE

## FILES
- src/client/features/render/native/helpers/sub_4e00c00.h
- src/client/features/render/native/helpers/sub_4e00c00.cpp
- docs/functions/4e00c00.md

## LIFTCHECK
GATE OK 0x4E00C00

## UNRESOLVED CALL
none

## Reversed source (complete)

Signature: `uintptr_t sub_4e00c00(uintptr_t self, void* a1, void* a2)` — `self` is used as a jump-table index into `0xF215890`; `a1` (rdx) is an object with a target pointer (+0x0) and next pointer (+0x8); `a2` (r8) is an object with source pointer (+0x0), refcounted pointer (+0x8), and slot array (+0x10). Return value is `rax` at epilogue; on the error path (allocation failure) `sub_9bc830(0x20)` is called for side effects and its result is discarded, then execution continues with null `rax`.

Struct layouts (packed, offsetof-verified):
- `sub_4e00c00_rdx` (a1): target@0x0, next@0x8
- `sub_4e00c00_r8` (a2): source@0x0, refcounted@0x8, slots[2]@0x10
- `sub_4e00c00_rcx` (refcounted object): vtable@0x0, strong_refcount@0x8, weak_refcount@0xc, type_tag@0x18
- `sub_4e00c00_rax` (allocation): slots0[2]@0x0, slots1[2]@0x10

Callees: `sub_eea6040` via IAT slot 0xF99FFA0 (vendor allocation/release thunk), `sub_9bc830` at 0x9BC830 (allocator fallback).

Control flow: 5-way switch on `self` (0..4). Case 0 → epilogue return. Case 1 → store type_tag=0, return 0. Case 4 → set target from source, zero fields, inc refcount, copy refcounted/slots, store type_tag=3. Case 3 → same as case 4 but type_tag=2. Case 2 → allocate via sub_eea6040(global,0x20); on failure call sub_9bc830(0x20) and continue with null; link allocation into target list; inc/dec refcounts; release old next via sub_eea6040; copy slots from rdi object; store type_tag=1.
CLOSES? YES
