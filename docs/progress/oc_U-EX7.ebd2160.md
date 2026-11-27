## NEXT
DONE

## FILES
docs/progress/oc_U-EX7.ebd2160.md
docs/functions/ebd2160.md
src/client/features/render/native/helpers/sub_ebd2160.cpp
src/client/features/render/native/helpers/sub_ebd2160.h

## SUMMARY
Unit U-EX7.ebd2160: lift sub_ebd2160 (0xebd2160, 0x5c bytes, depth 0, D0, 0 callees in set). The function is one straight-line basic block (0xebd2160..0xebd21bc, verified against rdis dis 0xebd2160): it builds a 0x38-byte stack descriptor at r11-0x48 (rsp+0x20 after `sub rsp,0x68`) — +0x00 = 0x000000000F847A07, +0x08/+0x0c = 0, +0x10 = 0x000000000F449520, +0x18 = 0x000000000F449530, +0x20 = arg2 (rdx), +0x28 = 0, +0x30 = zero_extend(arg3 r8d) — then calls sub_ebd1f80 with rcx = (arg4 != 0 ? arg4 : &descriptor), rdx = &descriptor+0x10, r8 = same as rcx, r9 = 0x000000000F449530, and returns rax. Arg1 (rcx) is never read.

The complete reversal is in docs/functions/ebd2160.md (analysis + 'Reversed source (complete)') and lifted into src/client/features/render/native/helpers/sub_ebd2160.cpp (+ .h with layout constants and static_asserts, LIFT_FN registry entry).

## UNRESOLVED CALL
0xebd1f80 — caller instruction `0xebd21b1  call 0xEBD1F80` (disassembly annotation `; -> sub_ebd1f80`), at 0xebd21b1 inside sub_ebd2160 (0xebd2160..0xebd21bc). Target 0xebd1f80 (sub_ebd1f80) is not in docs/data/native_functions.tsv and not in docs/data/native_boundary.tsv; it is only listed as class `?` in docs/data/native_boundary_candidates.tsv:418. No wrapper invented, no signature fabricated (the source forward-declares it with the observed call-site signature so the lift can be completed once it is classified).

## LIFTCHECK
LIFTCHECK OK 0xebd2160

CLOSES? NO UNRESOLVED CALL 0xebd1f80 at 0xebd21b1 (`call 0xEBD1F80`): callee is in neither docs/data/native_functions.tsv nor docs/data/native_boundary.tsv; per the unit rules no wrapper was invented and the lift stops here.
