## NEXT
DONE

## FILES
- src/client/features/render/native/dragon/sub_c283810.h (created: layout constants, static_asserts, signature, forward declarations)
- src/client/features/render/native/dragon/sub_c283810.cpp (created: lifted source, LIFT_FN registry, verbatim call quotes)
- docs/functions/c283810.md (created: dossier with analysis and Reversed source section)

## Analysis summary
Function sub_c283810 (0xc283810, 0x8b bytes, dragon, D0, "Frame renderer lambda") is a recursive tree-walk destructor over RenderNode nodes. Same structure as already-lifted sub_c283ce0/sub_c27ebd0, with an added type check at [node+0x38] gating refcount release (types 0,1,2 release; type >2 skips). Calls: self-recursive (0xc28383D call 0xC283810), two indirect calls through data slot 0xF99FFA0 to sub_eea6040 (vendor boundary, destructor vtable[0] at 0xc28387D and deallocator vtable[8] at 0xc283893).

## UNRESOLVED CALL
none

## LIFTCHECK
LIFTCHECK OK 0xc283810

CLOSES? YES