## NEXT
DONE — sub_0xbc431b0 lifted; LIFTCHECK OK 0xbc431b0; UNRESOLVED CALL = none; CLOSES? YES

## UNIT
U-EX1.bc431b0 — lift sub_0xbc431b0 ("VV frame-graph builder"), rva 0xbc431b0 size 0x129 bytes, depth 1, D0, bgfx region, callees outside set: 0x75720 (stl), 0x9bc830 (alloc); callees in set: none. Both calls to 0x75720 / 0x9BC830 go through native::Boundary wrappers with native symbols; calls to [0xF99FFA0] (sub_eea6040) and 0xEEC6EC0 are compiled to STL equivalents per spec §5 (std::malloc / std::memcpy), so UNRESOLVED CALL = none.

## FILES
- docs/progress/oc_U-EX1.bc431b0.md (this result file)
- docs/functions/bc431b0.md (dossier: register map, phases, struct fields, callees, Reversed source (complete))
- src/client/features/render/native/bgfx/sub_bc431b0.h (layout constants + static_asserts, signature)
- src/client/features/render/native/bgfx/sub_bc431b0.cpp (lifted source, first line `// LIFT 0xbc431b0 size 0x129 1.26.62.01 sub_bc431b0`, LIFT_FN registry entry)

## LIFTCHECK
`python tools/sigs/liftcheck.py 0xbc431b0` printed:

LIFTCHECK OK 0xbc431b0

## UNRESOLVED CALL
none — every call target in the function is either a callee-list/boundary function (0x75720, 0x9BC830, both in docs/data/native_boundary.tsv) or a spec §5 library intrinsic replacement ([0xF99FFA0]=sub_eea6040 -> std::malloc, 0xEEC6EC0 -> std::memcpy); no call target is outside both sets.

## TOOL REQUESTS
None

## CLOSES?
CLOSES? YES
