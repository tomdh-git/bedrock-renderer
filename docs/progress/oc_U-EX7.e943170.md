## NEXT
DONE

## Unit
U-EX7.e943170, function 0xe943170, size 0x7 bytes, depth 0, D0, 0 callees in set (docs/progress/_d_U-EX7.e943170.txt; docs/data/native_functions.tsv line 1627; docs/data/native_boundary.tsv classifies 0xe943170 as lift).

## DONE
- step 1: wrote this file with ## NEXT / step 2
- step 2: disassembled 0xe943170: `0xe943170  jmp qword ptr [0xF9A7AF0] ; [data_f9a7af0]`, next instruction per rdis at 0xe943177 => [0xe943170, 0xe943177) is exactly one instruction, 0x7 bytes [V]; no `call` instruction, 0 callees [V]; slot 0xF9A7AF0 = AcquireSRWLockExclusive [V: peimports.py, docs/progress/oc_U-EX0b1.md]
- step 3: wrote docs/functions/e943170.md (dossier, 'Reversed source (complete)' section), src/client/features/render/native/helpers/sub_e943170.h (layout constants + static_asserts + signature + declaration) and sub_e943170.cpp (LIFT marker, body, LIFT_FN registry entry)
- step 4: cppsyntax OK; liftcheck LIFTCHECK OK 0xe943170; gate GATE OK 0xE943170
- step 5: result file completed below

## FILES
- docs/progress/oc_U-EX7.e943170.md (created, this result file)
- docs/functions/e943170.md (created: dossier with Reversed source (complete))
- src/client/features/render/native/helpers/sub_e943170.h (created: sub_e943170Layout static_asserts, signature void sub_e943170(void*))
- src/client/features/render/native/helpers/sub_e943170.cpp (created: // LIFT 0xe943170 size 0x7 1.26.62.01 sub_e943170, verbatim call quote block, body, LIFT_FN(sub_e943170, "sub_e943170", 0xe943170, ::native::sub_e943170, nullptr))

## LIFTCHECK
LIFTCHECK OK 0xe943170
(exact output of `python tools/sigs/liftcheck.py 0xe943170`; cppsyntax: OK; gate: GATE OK 0xE943170)

## UNRESOLVED CALL
none — the function contains no `call` instruction; its only control transfer is the tail `jmp qword ptr [0xF9A7AF0]` through loader-resolved data slot 0xF9A7AF0, lifted by reading the 8-byte pointer from the slot at call time and tail-calling it as a function pointer (rule 68 slot-indirect call; not a lift-set callee, not a boundary wrapper). LIFTCHECK OK 0xe943170 confirms all calls (zero) are quoted and resolved.

CLOSES? YES
