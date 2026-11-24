## NEXT
DONE: U-EX2.e8141e0 LIFT sub_e8141e0 complete. LIFTCHECK OK. CLOSES.

Checklist: X2.e8141e0 LIFT sub_e8141e0 (0xe8141e0, 0xd8 bytes, depth 0, D0, 0 callees in set)

## FILES
- docs/functions/e8141e0.md (new dossier: signature, arg map, callees, struct fields, Reversed source (complete))
- src/client/features/render/native/d3d12/sub_e8141e0.h (new: SlotEntry layout constants + static_asserts, ABI signature)
- src/client/features/render/native/d3d12/sub_e8141e0.cpp (new: LIFT marker, lifted body, #if 0 verbatim quotes, LIFT_FN registry)
- docs/progress/oc_U-EX2.e8141e0.md (this file)

## LIFTCHECK
```
$ python tools/sigs/liftcheck.py 0xe8141e0
LIFTCHECK OK 0xe8141e0
```

## UNRESOLVED CALL
none

## NOTES
- All three `call qword ptr [0xF99FFA0]` sites resolve to sub_eea6040, a `jmp rax` thunk
  classified `vendor`/boundary in docs/data/native_boundary.tsv. The lifted source loads the
  real target into rax exactly as the original (vtbl[1] of *[0x12ADF800] at sites 0xe814232 /
  0xe81429a; [rsi+0x10] at site 0xe814267) and calls it with the same register arguments
  (same mechanism as the already-lifted d3d12/sub_e809f40.cpp).
- Function releases one per-slot entry (0xB8 bytes) of the RendererContextD3D12 slot array at
  context offset 0xAAA178, indexed by the 16-bit slot argument. Layout constants + static_asserts
  in sub_e8141e0.h. No lift-set callees (callees_in_set empty per the data file).

CLOSES? YES