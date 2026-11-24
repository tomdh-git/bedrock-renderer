## NEXT
DONE — unit complete, LIFTCHECK OK.

## Unit
U-EX7.e935700: LIFT sub_e935700 at RVA 0xe935700, size 0x5 bytes, depth 0, milestone D0, region root.
Checklist: X7.e935700 LIFT sub_e935700 (0xe935700, 0x5 bytes, depth 0, D0, 0 callees in set).

## Findings (all [V] from rdis disassembly)
- 0xe935700  jmp 0x392960        ; -> sub_392960   (rdis `dis 0xe935700 8`; 0xe935705.. are int3 padding, outside the 0x5-byte function)
- Function size 0x5 per docs/data/native_functions.tsv. Exactly one instruction: a tail jump. No reads, no writes, no calls of its own.
- sub_392960 body [V]: 0x392960 push rbp; 0x392961 sub rsp,0x30; 0x392965 lea rbp,[rsp+0x30]; 0x39296a mov qword ptr [rbp-8],0xFFFFFFFFFFFFFFFE; 0x392972 mov rdx,rcx; 0x392975 mov rcx,[0x1233E1A8]; 0x39297c test rdx,rdx; 0x39297f je short 0x39298F; 0x392981 mov rax,[rcx]; 0x392984 mov rax,[rax+0x10]; 0x392988 call qword ptr [0xF99FFA0]; 0x39298e nop; 0x39298f add rsp,0x30; 0x392993 pop rbp; 0x392994 ret.
- sub_392960 classification: docs/data/native_boundary.tsv line 508 `0x392960 lift auto-unresolved->lift`; native_functions.tsv line 49 `0x392960 0x35 0 7 root D0`. Lift-set callee -> forward-declared and called through its native symbol `native::sub_392960` (brief rule 6); NOT a blocker, no boundary wrapper.
- Slot 0xF99FFA0 resolves to sub_eea6040, class `vendor` (native_boundary.tsv line 506) — inside sub_392960, not this unit.

## Lift design
sub_e935700(void* a0) { return sub_392960(a0); } — argument forwarded in RCX, result returned in RAX, exactly matching the tail jump (sub_392960 reads RCX as its only input argument; no stack argument is read by sub_392960 itself).

## FILES (created)
- docs/functions/e935700.md — dossier with 'Reversed source (complete)'
- src/client/features/render/native/helpers/sub_e935700.cpp — first line `// LIFT 0xe935700 size 0x5 1.26.62.01 sub_e935700`, body, LIFT_FN registration
- src/client/features/render/native/helpers/sub_e935700.h — layout constants + static_asserts, forward declarations/signatures
No other files changed (Sigs.json, shared headers, CMake, hooks untouched; no build run).

## LIFTCHECK
LIFTCHECK OK 0xe935700

## UNRESOLVED CALL
none (no `call` instruction in the function; jump target sub_392960 is in the lift set)

cppsyntax note: `tools/cppsyntax.py` reports 112 errors, all in pre-existing included headers (Detour.h, Profiler.h — missing STL/PCH in the /Zs environment); the identical errors occur on the untouched reference file sub_bc76380.cpp. No error is located in sub_e935700.cpp itself.

CLOSES? YES
