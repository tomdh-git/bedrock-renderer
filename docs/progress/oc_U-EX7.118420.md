## NEXT
DONE

## UNIT
U-EX7.118420: function 0x118420, size 0x53 bytes, depth 0, milestone 7 (root/D0 region), callees in set: 0 per _d_U-EX7.118420.txt. LIFTED as `void sub_118420(void* a1, void* a2, void* a3, void* a4)` (x64 Microsoft ABI; a3 = list head). Recursive child/sibling walk over node list headed at a3: entry guard `cmp byte ptr [r8+0x19],0; jne` (0x118429/0x11842e); loop head 0x118440 reads node+0x10 (child) and recurses with args 1/2 preserved via rdi/rsi copies (0x118430/0x118433/0x118436); after return reads node+0x00 (next) (0x11844f), calls native::sub_e935700(node) at 0x11845a (lift-set callee, `call 0xE935700`, declared in sub_e935700.h), then `cmp byte ptr [r14+0x19],0; je` loops on next node or falls to epilogue (0x11845f/0x118464/0x118467). `mov edx,0x30` at 0x118452 is a dead store (sub_e935700 tail-jumps to sub_392960 which copies RCX→RDX itself). rax never written → void return [V]. No memory writes by sub_118420 itself [V]. No null guards/SEH [V]. Callee sub_e935700 is classified `lift` in docs/data/native_boundary.tsv line 505 and docs/data/native_functions.tsv size 0x5 — called through its native symbol, not a boundary wrapper (hard rule: lift callees are not blockers). No callees outside the lift set.

## FILES
- docs/progress/oc_U-EX7.118420.md (this result file; initial + final)
- docs/functions/118420.md (dossier: signature, register/argument map, verbatim instruction lines, Reversed source (complete), struct fields touched, callees, verification)
- src/client/features/render/native/helpers/sub_118420.h (layout constants + static_asserts, ABI signature, forward declaration of native::sub_e935700)
- src/client/features/render/native/helpers/sub_118420.cpp (first line `// LIFT 0x118420 size 0x53 1.26.62.01 sub_118420`, lifted body, verbatim call quotes in #if 0 block, LIFT_FN registry entry)

No edits to Sigs.json, shared headers, CMake, hooks, or other units' files. No builds, no game.

## LIFTCHECK
`python tools/sigs/liftcheck.py 0x118420` -> `LIFTCHECK OK 0x118420` (exit 0).
Checks passed: dossier `Reversed source` section present and clean; source first-line LIFT marker size 0x53 matches function size 0x53; no [?]/[I]/TODO/UNVERIFIED/stub; LIFT_FN registry entry present; static_assert present; all 34 instructions of [0x118420, 0x118473) inside cited ranges; both `call` instructions quoted verbatim (`0x11844a  call 0x118420`, `0x11845a  call 0xE935700`); verify_oc mismatch=0, no-such-instr=0.

## UNRESOLVED CALL
none — both call targets are in the lift set: `sub_118420` (recursion, native symbol) and `sub_e935700` (lift-set callee, forward-declared via sub_e935700.h).

CLOSES? YES
