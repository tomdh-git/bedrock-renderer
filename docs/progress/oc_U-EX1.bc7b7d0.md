## NEXT
DONE - unit complete, liftcheck passed.

## UNIT
U-EX1.bc7b7d0, function 0xbc7b7d0 (sub_bc7b7d0, "VV frame-graph builder"), size 0x28b bytes ([0xbc7b7d0, 0xbc7ba5b), xref.fend=0xbc7ba5b), depth 1, milestone 1, region bgfx, status D0. Registered in docs/data/native_functions.tsv via native_checklist_gen.py --add 0xbc7b7d0 (row: 0xbc7b7d0 0x28b depth 0 ms 1 bgfx D0, callees_in_set empty, callees_outside_set 0x78ed0).

## FILES
Created:
- docs/functions/bc7b7d0.md (dossier: signature, register map, Reversed source (complete), struct fields touched, callees, OPEN questions)
- src/client/features/render/native/bgfx/sub_bc7b7d0.h (CascadedTableRow {f0@0, pad04@4, f8@8} + static_asserts, data RVAs, signature, footprint declaration)
- src/client/features/render/native/bgfx/sub_bc7b7d0.cpp (first line // LIFT 0xbc7b7d0 size 0x28b 1.26.62.01 VV frame-graph builder; full lift; LIFT_FN registration)
- docs/progress/oc_U-EX1.bc7b7d0.md (this result file)
Changed (by the sanctioned native_checklist_gen.py --add tool, not hand-edited):
- docs/data/native_functions.tsv, docs/data/native_boundary_candidates.tsv, docs/RENDER_CHECKLIST.md

## LIFT
Lifted by hand from the rdis disassembly of [0xbc7b7d0, 0xbc7ba5b). Signature: float* sub_bc7b7d0(float* out /*rcx*/, const float* in /*rdx*/), returns out. Reads in[0x0], in[0x0C] and const data at RVAs 0xEFD32AC, 0xEFC6CF8, 0xEEE6700, 0xF10D440, 0xEEC8060, 0xF449710, 0xF449720 plus tables at 0xF449BEC / 0xF44AA20 (rows stride 0x0c, {f0, pad, f8}). Writes [out, out+0x0C). All 5 calls quoted verbatim with per-phase address ranges // 0xA..0xB beside every block.

Callees: 0xEEC75A0 (jmp [0xF9A8E60]) and 0xEEC73F0 (jmp [0xF9A8E08]) import-thunk float(float) calls, and 0x78ed0 (sub rsp,0x28 / call [0xF9A8CF0] / int3, noreturn crt). None are in docs/data/native_functions.tsv or docs/data/native_boundary.tsv with a resolvable symbol; per hard rule 69 each call reads the pointer from its data slot at call time (slots 0xF9A8E60, 0xF9A8E08, 0xF9A8CF0) and calls it as a function pointer - not a blocker. 0xbc7ba5a int3 follows the 0x78ed0 call (traps if the noreturn thunk returns).

## LIFTCHECK
LIFTCHECK OK 0xbc7b7d0

## UNRESOLVED CALL
none

CLOSES? YES
