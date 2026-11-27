## NEXT
DONE

## FILES
src/client/features/render/native/helpers/sub_6754880.h
src/client/features/render/native/helpers/sub_6754880.cpp
docs/functions/6754880.md

## LIFTCHECK
GATE OK 0x6754880

## UNRESOLVED CALL
none

## Reversed source (complete)

sub_6754880 releases refcounted control blocks held in two pointer ranges of the state object.
- Range 1: [self+0x28, self+0x30) stride 8 (loop cursor only, no data access)
- Range 2: [self+0x40, self+0x48) stride 0x10 (data elements, each +0x8 is a ctrl block ptr)
Each control block: +0x00 vtable, +0x08 int32 refcount, +0x0C int32 count0xC.
Loop 1: lock-inc then lock-dec refcount; if dec==0, call sub_eea6040(ctrl, vfptr[0]), then lock-dec count0xC; if ==0, call sub_eea6040(ctrl, vfptr[1]).
Loop 2: lock-dec refcount on each ctrl block; same destroy pattern on zero.
Finally empties range 1 (f30=f28) if non-empty, empties range 2 (f48=f40).
Return: f28 via block 12, f40 via block 19, 0 when both ranges empty at entry.
sub_eea6040 is a boundary/vendor thunk via data slot 0xF99FFA0.

CLOSES? YES
