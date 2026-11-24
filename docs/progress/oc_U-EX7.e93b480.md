## NEXT
DONE — lift written (cpp + h + dossier), cppsyntax parity with existing helper lifts, `python tools/sigs/liftcheck.py 0xe93b480` printed LIFTCHECK OK. Closure is blocked by one unclassified callee (see ## UNRESOLVED CALL); nothing else to do for this unit.

## FILES
created: src/client/features/render/native/helpers/sub_e93b480.cpp  (first line: `// LIFT 0xe93b480 size 0x6 1.26.62.01 sub_e93b480`; LIFT_FN registry entry; static_asserts; verbatim jmp/int3 quotes in #if 0 block; citation `// 0xe93b480..0xe93b486`)
created: src/client/features/render/native/helpers/sub_e93b480.h  (SubE93b480Layout with static_asserts; forward declaration of sub_e93b490 and signature of sub_e93b480, namespace native)
created: docs/functions/e93b480.md  (signature, register/argument map, 'Reversed source (complete)' section, struct fields touched, callees, no open questions)
created: docs/progress/oc_U-EX7.e93b480.md  (this result file)

## LIFTCHECK
LIFTCHECK OK 0xe93b480

## UNRESOLVED CALL
0xe93b490 (sub_e93b490): tail-jump target of sub_e93b480. Caller instruction (verbatim from rdis): `0xe93b480  jmp 0xE93B490` (-> loc_e93b490). The lifted body forwards to it as `return sub_e93b490(first, last, ch);` — identical register arguments in the same order (rcx = first wchar_t*, rdx = last wchar_t*, r8 = wchar_t ch), identical return (rax = pointer to first match or last), no register shuffling, no reads/writes/calls of its own in [0xe93b480, 0xe93b486). Target disassembly seen: `0xe93b490  mov eax,[0x1230A11C]`, `0xe93b496  mov r9,rdx`, `0xe93b499  sub r9,rcx`, `0xe93b49c  mov r10,rdx`, ... (wide-char search of [first,last) for (wchar_t)ch).
Status: 0xe93b490 is not in the CALLEES list for this unit (docs/progress/_d_U-EX7.e93b480.txt: 0 callees in set), not in docs/data/native_boundary.tsv, and not in docs/data/native_functions.tsv. Per the GOAL callee rule this is an UNRESOLVED CALL; no wrapper invented, no forwarder fabricated.

CLOSES? NO callee sub_e93b490 at 0xe93b490 (target of the tail jump `0xe93b480  jmp 0xE93B490`) is neither in the CALLEES list nor in docs/data/native_boundary.tsv (UNRESOLVED CALL); L1 cannot be claimed although liftcheck printed LIFTCHECK OK 0xe93b480
