## NEXT
DONE

step 1 (done): wrote this file with first line "## NEXT" and second line "step 2".
step 2 (done): gathered all input data — read docs/OPENCODE_BRIEF.md, docs/RENDER_NATIVE_SPEC.md, docs/progress/_d_U-EX4.bc04270.txt (row: 0xbc04270 size 0x95 depth 0 milestone 4 root D0 "pass encode D", 0 callees in set), docs/data/native_functions.tsv, docs/data/native_boundary.tsv, docs/data/native_deps.tsv (X4.bc04270 has no deps); disassembled [0xbc04270, 0xbc04305) (40 instructions; ends `0xbc04300  jmp 0xBC61560` tail call); classified callees: sub_eea6040 (0xeea6040) = class vendor boundary via data slot 0xF99FFA0 (thunk body `jmp rax`, caller pre-loads rax with the vtable slot), sub_bc61560 = lift set ("custom item submit (key bit 53)", D2), sub_bc04530 = lift set ("pass task render-thread body (class D)", D2); studied framebuilder precedents (sub_66a1820, sub_66a17c0, bc68e40_chunk_c00) for LIFT marker, layout constants/static_asserts, LIFT_FN registry, and the data-slot thunk call pattern.
step 3 (done): wrote src/client/features/render/native/framebuilder/sub_bc04270.h — layout constants k* / static_asserts for structs RefCounted (+0x0 vtable, +0x8 strong atomic u32, +0xC weak atomic u32), PassDst (+0x3A8 u64, +0x3B0 ptr, +0x3B8 ptr; size 0x3C0), PassSrc (+0x0 u64, +0x8 ptr, +0x10 ptr; size 0x18), TaskNode (+0x8 u16, +0x10 ptr; size 0x18); signature void sub_bc04270(PassDst* a0, PassSrc* a1); forward declaration of lift-set sub_bc61560(void*, uint16_t, void*, void*).
step 4 (done): wrote src/client/features/render/native/framebuilder/sub_bc04270.cpp — first line `// LIFT 0xbc04270 size 0x95 1.26.62.01 sub_bc04270`; lifted body with per-instruction `// 0xA..0xB` range citations and verbatim call quotes (`0xbc042c5  call qword ptr [0xF99FFA0]`, `0xbc042db  call qword ptr [0xF99FFA0]` through eea6040_thunk reading the slot at call time); tail call `return sub_bc61560(*(void**)(node+0x10), (uint16_t)*(uint16_t*)(node+8), (void*)0xBC04530, a0);` implementing `0xbc04300  jmp 0xBC61560`; footprint {a0+0x3A8, 0x18}; LIFT_FN(sub_bc04270, "sub_bc04270", 0xbc04270, sub_bc04270, sub_bc04270Footprint); verbatim #if 0 quote block of all 40 instructions; `python tools/cppsyntax.py sub_bc04270.cpp` -> OK (syntax).
step 5 (done): wrote docs/functions/bc04270.md dossier with signature, argument map, instruction-complete phases, fields-touched table, callees table, and 'Reversed source (complete)' section quoting every instruction verbatim; fixed a liftcheck false positive (literal "[?]/[I]/TODO/UNVERIFIED" phrase) by rephrasing; `python tools/sigs/liftcheck.py 0xbc04270` -> LIFTCHECK OK 0xbc04270 (verify_oc mismatch=0, no-such-instr=0, 100% instruction coverage, both calls quoted verbatim, registry entry + static_assert present, no stub/TODO/[?]/[I]/UNVERIFIED).

## FILES
src/client/features/render/native/framebuilder/sub_bc04270.h (new)
src/client/features/render/native/framebuilder/sub_bc04270.cpp (new)
docs/functions/bc04270.md (new)
docs/progress/oc_U-EX4.bc04270.md (this result file, rewritten)

## LIFTCHECK
LIFTCHECK OK 0xbc04270

## UNRESOLVED CALL
none: both `call qword ptr [0xF99FFA0]` sites resolve to boundary sub_eea6040 (class vendor, docs/data/native_boundary.tsv) via data slot 0xF99FFA0, and the tail call `jmp 0xBC61560` targets lift-set sub_bc61560 (forward-declared, called by its native symbol); the function row declares 0 callees.

CLOSES? YES
