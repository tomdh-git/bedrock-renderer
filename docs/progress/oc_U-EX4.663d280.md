## NEXT
DONE

## FILES
- src/client/features/render/native/helpers/sub_663d280.h
- src/client/features/render/native/helpers/sub_663d280.cpp
- docs/functions/663d280.md

## LIFTCHECK
GATE OK 0x663D280
LIFTCHECK OK 0x663d280
cppsyntax: OK (syntax)

## UNRESOLVED CALL
none

## Summary
sub_663d280 releases up to three refcounted objects (at self+0x50/0x68/0x80, gated by flag bytes at self+0x58/0x70/0x88). Each release: lock dec refcount(+8); if zero, call destructor(vfptr[0]) via sub_eea6040 thunk; then lock dec count(+0xC); if zero, call operator delete(vfptr[1]) via sub_eea6040 thunk. Clears each flag after release. Finally clears self+0x90 and returns 0. Object base is in RDX (second parameter); RCX (first parameter, a1) is never read. sub_eea6040 is a boundary/vendor thunk via data slot 0xF99FFA0.

CLOSES? YES
