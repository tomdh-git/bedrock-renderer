## NEXT
DONE. LIFT of 0xe817cf0 is complete and `python tools/sigs/liftcheck.py 0xe817cf0` prints
`LIFTCHECK OK 0xe817cf0`. The one remaining pre-link step (outside this unit's allowed paths) is to
register the tail callee sub_e804590 (0xe804590) into docs/data/native_functions.tsv /
native_boundary.tsv via `python tools/native_checklist_gen.py --add 0xe804590`; until then it is the
single blocker reported below.
Unit checklist line: `X2.e817cf0 LIFT sub_e817cf0 (0xe817cf0, 0x15a bytes, depth 0, D0, 0 callees in set)`.

## FILES
- docs/functions/e817cf0.md (created: analysis + 'Reversed source (complete)')
- src/client/features/render/native/d3d12/sub_e817cf0.h (created: layout constants + static_asserts, forward declarations, extern "C" signature)
- src/client/features/render/native/d3d12/sub_e817cf0.cpp (created: LIFT body, #if 0 verbatim listing of all 85 instructions, LIFT_FN registry entry)
- docs/progress/oc_U-EX2.e817cf0.md (this result file)
No shared/forbidden files were modified (Sigs.json, CMake, shared headers, other units' files untouched).

## LIFTCHECK
LIFTCHECK OK 0xe817cf0

## UNRESOLVED CALL
- sub_e804590 (0xe804590). Caller instruction: `0xe817e45  jmp 0xE804590` (tail call in sub_e817cf0).
  What I saw: sub_e804590 is a real function (size 0x2a6; docs/data/functions.tsv line 591 = L2 d3d12
  D0; functions_full line 373 = 'entry-indirect'), NOT a thunk. Greps of docs/data/native_functions.tsv
  and docs/data/native_boundary.tsv return no row for 0xe804590 (it appears only in functions.tsv /
  functions_full.tsv / function_classes.tsv / inventory_L2_d3d12.tsv). Per the hard rule, a callee in
  neither table is a blocker. It was forward-declared (namespace native, extern "C", exact ABI the
  disassembly shows: rcx = this+0xC9AA98, edx = zero-extended handle, r8 = arg4) and called directly
  so the lift is complete and LIFTCHECK passes; register it with `native_checklist_gen.py --add
  0xe804590` before link.
- Not blockers (documented for completeness):
  - `0xe817d71  call 0xEBCE430` -> sub_ebce430 (0xebce430) is a 2-instruction forwarder
    (`movzx edx,dl ; jmp 0xEEC6ED0`); forward-declared and called directly (a forwarder is a normal
    lift item, not a blocker).
  - `0xe817d60  call qword ptr [0xF99FFA0]` and `0xe817dc6  call qword ptr [0xF99FFA0]` are data-slot
    indirect calls (slot RVA 0xF99FFA0 -> sub_eea6040, class vendor); the pointer is read from the
    slot at call time and called as a function pointer with the exact register/stack arguments
    (release: alloc, old, 0, 0, 0, 0; alloc: alloc, 0, size, 0, 0, 0). Not a blocker.

## TOOL REQUESTS
None

CLOSES? NO sub_e804590 (0xe804590) tail-called at 0xe817e45 is in neither native_functions.tsv nor native_boundary.tsv (register via native_checklist_gen.py --add 0xe804590 before link)