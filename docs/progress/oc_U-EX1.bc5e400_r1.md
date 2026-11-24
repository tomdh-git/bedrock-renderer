## NEXT
DONE — lift of sub_bc5e400 written (dossier + .h + .cpp), liftcheck prints LIFTCHECK OK 0xbc5e400; CLOSES? NO because of UNRESOLVED CALL(s) (see below).

step 2: read the contract (OPENCODE_BRIEF.md hard rules, RENDER_NATIVE_SPEC.md) and the unit input data (_d_U-EX1.bc5e400.txt): sub_bc5e400, size 0x2f1, depth 2, D0, region bgfx, root "VV frame-graph builder", callees outside set 0x75740,0x9bc830, 0 callees in set.
step 3: disassembled [0xbc5e400, 0xbc5e6f1) with rdis dis 0xbc5e400; identified all 9 call sites, every data read/write, and the exact byte end (0xbc5e400 + 0x2f1 = 0xbc5e6f1, ending on the int3 padding after 0xbc5e6ea call qword ptr [0xF9A8C78]).
step 4: classified callees against docs/data/native_boundary.tsv and docs/data/native_functions.tsv: 0x75740 = stl boundary (line 4), 0x9bc830 = alloc boundary (line 149); [0xF99FFA0] (import slot -> thunk sub_eea6040 at 0xEEA6040, `jmp qword ptr [0xF99FFA0]`, loader-resolved, no static target), 0xE935700 (forwarder `jmp 0x392960`), [0xF9A8C78] (contents 0x000F9B055E read with peptr.py) are in neither table -> UNRESOLVED CALL.
step 5: wrote src/client/features/render/native/bgfx/sub_bc5e400.h (Bc5e400Elem/Bc5e400RefCnt/Bc5e400Array layout constants + static_asserts, x64 ABI signature, footprint declaration) and sub_bc5e400.cpp (complete lift: first line `// LIFT 0xbc5e400 size 0x2f1 1.26.62.01 sub_bc5e400`, every block cited `// 0xA..0xB`, every call quoted verbatim `0xRVA  call ...`, LIFT_FN registration, static_asserts, no stubs/TODO/[?]/[I]/UNVERIFIED).
step 6: wrote docs/functions/bc5e400.md dossier (signature/register map, phase walk with verbatim instruction quotes, struct fields touched table, callee table, Reversed source (complete), ownership/threading, version anchors, verification, OPEN questions).
step 7: ran `python tools/sigs/liftcheck.py 0xbc5e400` -> LIFTCHECK OK 0xbc5e400 (dossier Reversed source clean, source size/marker/LIFT_FN/static_assert OK, coverage 100% of [0xbc5e400, 0xbc5e6f1), all 9 calls quoted verbatim, verify_oc mismatch=0 no-such-instr=0).

## FILES
docs/progress/oc_U-EX1.bc5e400.md (this result file)
docs/functions/bc5e400.md (dossier: analysis + Reversed source (complete))
src/client/features/render/native/bgfx/sub_bc5e400.cpp (lift source; first line is the LIFT marker)
src/client/features/render/native/bgfx/sub_bc5e400.h (layout constants, static_asserts, signature)
tools/sigs/peptr.py (helper: read the pointer stored at an RVA in the exe; used to resolve [0xF9A8C78] = 0x000F9B055E)

## LIFTCHECK
LIFTCHECK OK 0xbc5e400

## UNRESOLVED CALL
- 0xbc5e4a5  call qword ptr [0xF99FFA0] (same target at 0xbc5e4d6, 0xbc5e643, 0xbc5e65a): import slot [data_f99ffa0]; the statically visible target is thunk sub_eea6040 at 0xEEA6040 (`jmp qword ptr [0xF99FFA0]`), i.e. a loader-resolved IAT slot with no static code target; not in docs/data/native_functions.tsv or docs/data/native_boundary.tsv.
- 0xbc5e691  call 0xE935700: forwarder `jmp 0x392960`; neither 0xE935700 nor 0x392960 is in either table.
- 0xbc5e6ea  call qword ptr [0xF9A8C78]: slot contents 0x000F9B055E (peptr.py), not a known function; 0xF9B055E is a 0x4d-byte unreferenced blob; not in either table.
Resolved callees (boundary wrappers, native::Boundary<...> with the native symbol): 0x9BC830 sub_9bc830 (alloc), 0x75740 sub_75740 (stl).

## TOOL REQUESTS
peptr.py | RVA -> qword stored at that RVA in the exe (PE section parse, read-only) | resolved the indirect-call target [0xF9A8C78] = 0x000F9B055E without guessing; worth keeping as a general data-inspection helper.

CLOSES? NO UNRESOLVED CALL: the calls via import slot [0xF99FFA0] (sub_eea6040 thunk, loader-resolved), the direct call 0xE935700 (forwarder to 0x392960), and [0xF9A8C78] (holds 0xF9B055E, not a known function) resolve to no entry in docs/data/native_functions.tsv or docs/data/native_boundary.tsv, so no native::boundary wrapper exists for them and none may be invented.
