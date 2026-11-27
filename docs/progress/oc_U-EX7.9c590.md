## NEXT
DONE

## GOAL
LIFT task for sub_9c590 (0x9c590, size 0xb4, depth 0, root D0, 0 callees in set per docs/progress/_d_U-EX7.9c590.txt). Unit id X7.9c590.

## DONE
- Disassembled [0x9c590, 0x9c644) with rdis dis 0x9c590; every instruction translated to C++, same reads/writes/calls/return as the exe, exact x64 ABI signature `void* sub_9c590(void* slot /* dead RCX */, void* node /* RDX */)`.
- Calls: 0x9C5C6 call 0x9C590 (recursive, this unit); 0x9C602 call 0xE935700 (lift-set callee sub_e935700, unit X7.e935700); 0x9C625 jmp 0x9C650 (tail to lift-classified sub_9c650, unit X7.9c650); 0x9C63D call qword ptr [0xF9A8C78] data-slot indirect call (brief rule 8: not a blocker; read at call time from imageBase()+0xF9A8C78, all arguments zero, block ends in int3/noreturn).
- Image base 0x140000000 (slot VA 0x14F9A8C78, consistent with existing lifted sources).
- Node layout: +0x28 child begin (R/W), +0x30 child end (R/W), +0x38 limit (R/W), stride 0x40, size prefix at [child-8]; static_asserts in the header.
- Recursion over children, sub_e935700 block release, slot fields cleared, tail to sub_9c650(node+0x10); heap-corruption fail path calls the data-slot handler then int3.

## FILES
- docs/progress/oc_U-EX7.9c590.md (this file, created)
- docs/functions/9c590.md (created: analysis + 'Reversed source (complete)' + verbatim call quotes)
- src/client/features/render/native/helpers/sub_9c590.h (created: layout constants, static_asserts, forward declarations)
- src/client/features/render/native/helpers/sub_9c590.cpp (created: first line `// LIFT 0x9c590 size 0xb4 1.26.62.01 sub_9c590`, reversed source, LIFT_FN entry)
No other files created or changed; no builds run; no Sigs.json/CMake/hook/shared-header edits.

## LIFTCHECK
LIFTCHECK OK 0x9c590

## UNRESOLVED CALL
none

## VERIFICATION
- cppsyntax: same LIFT_FN parse errors as the pre-existing helpers/sub_e935700.cpp (environmental; liftcheck does not compile).
- liftcheck.py 0x9c590: LIFTCHECK OK (exit 0) — coverage 100%, all 3 call instructions quoted verbatim, verify_oc mismatch=0 no-such-instr=0, no [?]/[I]/TODO/UNVERIFIED, static_assert present, LIFT_FN registry entry present, dossier present.
- CLOSES? YES
