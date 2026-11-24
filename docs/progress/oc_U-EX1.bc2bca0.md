## NEXT
DONE. Unit closed: liftcheck printed `LIFTCHECK OK 0xbc2bca0`. No further steps.

## UNIT
U-EX1.bc2bca0 — lift sub_0xbc2bca0 (0xbc2bca0, 0x172 bytes, depth 1, D0, bgfx, 0 callees in set, callees outside set: 0x655cea0). CLOSES? YES.

## FILES
Created:
- src/client/features/render/native/bgfx/sub_bc2bca0.h — layout constants (sub_bc2bca0_state, sub_bc2bca0_entry) + static_asserts for every offset used (0x00, 0x10, 0x18, 0x20, 0x60, 0x68, 0x70, 0x88, 0x90, 0x2F8) and signature declaration.
- src/client/features/render/native/bgfx/sub_bc2bca0.cpp — first line `// LIFT 0xbc2bca0 size 0x172 1.26.62.01 sub_bc2bca0`, complete reversed source with per-block `// 0xA..0xB` ranges, all 8 calls quoted verbatim, releaseRefObj/vtableCallSlot*/notifyGlobal helpers, LIFT_FN registry entry + footprint.
- docs/functions/bc2bca0.md — dossier with analysis, struct fields touched, callees, and 'Reversed source (complete)' section.
Changed (via `python tools/native_checklist_gen.py --add 0xbc2bca0`, required by liftcheck's size table):
- docs/data/native_functions.tsv (row 0xbc2bca0 0x172 depth 1 ms 1 region bgfx status D0 root added outside 0x655cea0)
- docs/data/native_roots.txt (appended root)
- docs/data/native_boundary_candidates.tsv (regenerated)
- docs/RENDER_CHECKLIST.md (regenerated, native)
- docs/progress/oc_U-EX1.bc2bca0.md (this file)

## DISASSEMBLY BASIS (all from rdis dis output, [0xbc2bca0, 0xbc2be12))
Verbatim calls (quoted in source and dossier):
0xbc2bcd0  call qword ptr [0xF99FFA0]      ([data_f99ffa0] = sub_eea6040 `jmp rax` thunk -> indirect vtable[4])
0xbc2bd05  call qword ptr [0xF99FFA0]      -> vtable[0]
0xbc2bd1b  call qword ptr [0xF99FFA0]      -> vtable[1]
0xbc2bd68  call qword ptr [0xF99FFA0]      -> vtable[0]
0xbc2bd7e  call qword ptr [0xF99FFA0]      -> vtable[1]
0xbc2bd98  call 0x655CEA0                  -> boundary stl, native symbol
0xbc2bdd2  call 0xE935700                  -> jmp 0x392960: global [VA 0x15233E1A8] vtable[2] if arg != 0
0xbc2be0b  call qword ptr [0xF9A8C78]      -> IAT slot of _invoke_watson, loader-patched, args (0,0,0,0,0), tail call
No lift-set callees. [0xF99FFA0] is a static data slot (contains VA of sub_eea6040), not a real callee: the 4x calls are raw vtable indirect calls. sub_655cea0 is called through its native symbol per repo convention (cf. sub_bc40a30.cpp). sub_e935700/_invoke_watson effects are invoked inline; no wrapper invented.

## LIFTCHECK
LIFTCHECK OK 0xbc2bca0

## UNRESOLVED CALL
none

## TOOL REQUESTS
None

CLOSES? YES
