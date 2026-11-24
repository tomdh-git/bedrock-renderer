## NEXT
DONE

## FILES
Created: docs/progress/oc_U-EX2.e878550.md (this result file)
Created: docs/functions/e878550.md (dossier with Reversed source (complete))
Created: src/client/features/render/native/d3d12/sub_e878550.h (layout constants, signature, boundary forward declarations)
Created: src/client/features/render/native/d3d12/sub_e878550.cpp (lifted C++ source, LIFT_FN registry entry)

## LIFTCHECK
LIFTCHECK OK 0xe878550

## UNRESOLVED CALL
none

## Summary
Lifted sub_e878550 (BgfxFrameBuilder_slot16, 0xe878550, size 0x225). Function allocates a 0x50-byte FrameBuilderNode via vendor allocator thunk (data slot 0xF99FFA0), copies string data (SSO inline for len<=0x15, heap-allocated with 32-byte alignment for longer), copies scalar fields from input node, then recursively processes left child ([inputNode+0]) and right child ([inputNode+0x10]), linking results into output node's leftChild/rightChild fields. Returns the output node pointer.

Calls:
- 0xe8785a9/0xe878649/0xe87867a: call r8 via data slot 0xF99FFA0 (vendor boundary thunk_f99ffa0) x3 [V]
- 0xe8786a5: call 0xEEC6EC0 (sub_eec6ec0, lift-set memcpy-like) x1 [V]
- 0xe8786df/0xe8786f3: call 0xE878550 (recursive) x2 [V]
- 0xe878725/0xe87873f/0xe87875a: call 0x9BC830 (alloc boundary, noreturn) x3 [V]
- 0xe87876e: call 0x75720 (stl boundary, noreturn) x1 [V]

All callees resolved: sub_eec6ec0 is lift-set (forward-declared in header), sub_9bc830 and sub_75720 are boundary (noreturn), thunk_f99ffa0 is boundary via data slot. No unresolved calls.

CLOSES? YES