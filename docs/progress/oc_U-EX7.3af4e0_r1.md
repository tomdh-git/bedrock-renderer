## NEXT
DONE

## FILES
- docs/progress/oc_U-EX7.3af4e0.md (this result file)
- docs/functions/3af4e0.md (dossier: signature, register map, disassembly phases, reversed source complete, callees, struct fields touched, open questions)
- src/client/features/render/native/helpers/sub_3af4e0.h (header: layout constants with static_asserts, signature, forward declaration for UNRESOLVED CALL target 0x3b23c0)
- src/client/features/render/native/helpers/sub_3af4e0.cpp (lifted source: LIFT marker line 1, verbatim call quotes in #if 0 block, full C++ implementation with address-range citations, boundary __report_gsfailure declaration at global scope)

## LIFTCHECK
LIFTCHECK OK 0x3af4e0

## UNRESOLVED CALL
0x3b23c0 (sub_3b23c0): called via `0x3af510  call 0x3B23C0` at entry of sub_3af4e0; returns a pointer (RAX) whose first qword is read at `0x3af515  mov rcx, [rax]`. Not present in docs/data/native_functions.tsv or docs/data/native_boundary.tsv. Per the hard rule: a callee outside both tables is a blocker — name it as UNRESOLVED CALL with the address and stop.

CLOSES? NO single blocking fact: UNRESOLVED CALL at 0x3b23c0 (sub_3b23c0), called directly at 0x3af510, not in native_functions.tsv or native_boundary.tsv