## NEXT
DONE

Unit: U-EX1.bc79a60 — lift sub_bc79a60 (0xbc79a60, size 0x46f, depth 7, bgfx, D0, 0 callees in set). COMPLETE.

Summary: sub_bc79a60 is the frame-graph builder slab allocator (this = builder object at +0x1DF3460; allocator fields at +0x4000 blockHead, +0x4008 cursor, +0x4010 limit, +0x4018 u16 count; inline slots +0x0000..+0x3FFF; 0x4008-byte chain blocks via loader allocator [0x12ADF800], realloc = vtable slot 1 through data slot [0xF99FFA0] = sub_eea6040 thunk; header block 0x18 bytes {head+0x00, tail+0x08, totalBytes+0x10}, block links at +0x4000). It increments count, stamps the handed-out slot with (u16)(cursor>>2), advances cursor by 4, and returns the new cursor in rax. All 206 instructions / 3 calls lifted verbatim; no branches skipped; no null guards/SEH (original has none).

Callees: 0xbc79b09  call qword ptr [0xF99FFA0] and 0xbc79b90  call qword ptr [0xF99FFA0] (slot -> sub_eea6040 `jmp rax` vendor thunk, boundary.tsv line 506; lifted as function-pointer call reading vtable slot 1 at call time per hard rule 69), 0xbc79ba4  call 0xEEC6ED0 (CRT memset, boundary.tsv line 507; lifted as std::memset per spec section 5). No callees in the lift set; no unresolved calls.

## FILES
- docs/progress/oc_U-EX1.bc79a60.md (this file)
- docs/functions/bc79a60.md (dossier with Reversed source (complete))
- src/client/features/render/native/bgfx/sub_bc79a60.h (layout constants + static_asserts, signature, allocator shim reuse)
- src/client/features/render/native/bgfx/sub_bc79a60.cpp (lifted source, first line `// LIFT 0xbc79a60 size 0x46f 1.26.62.01 sub_bc79a60`, LIFT_FN registry entry)

## LIFTCHECK
`python tools/sigs/liftcheck.py 0xbc79a60` printed:
LIFTCHECK OK 0xbc79a60

## UNRESOLVED CALL
none — every call target is either a library intrinsic (0xEEC6ED0 = CRT memset, std::memset) or a data-slot indirect call ([0xF99FFA0] = sub_eea6040 vendor thunk via allocator vtable slot 1), both documented; no callees in the lift set.

CLOSES? YES
