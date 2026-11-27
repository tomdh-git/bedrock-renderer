## NEXT
DONE — unit complete, GATE OK 0x19BBC0, CLOSES? YES

## Unit
U-EX7.19bbc0: LIFT sub_19bbc0 at RVA 0x19bbc0, size 0xce bytes, depth 0, milestone D0, region root.
Checklist: X7.19bbc0 LIFT sub_19bbc0 (0x19bbc0, 0xce bytes, depth 0, D0, 1 callee in lift set: sub_e935700).

## Files created
- docs/functions/19bbc0.md — dossier with signature, register/argument map, phases, struct fields, callees, 'Reversed source (complete)'
- src/client/features/render/native/helpers/sub_19bbc0.cpp — first line `// LIFT 0x19bbc0 size 0xce 1.26.62.01 sub_19bbc0`, full body with cited ranges and verbatim call quotes, LIFT_FN registration
- src/client/features/render/native/helpers/sub_19bbc0.h — layout constants (sub_19bbc0Layout) with static_asserts, forward declaration of sub_e935700, signature of sub_19bbc0
No other files changed (Sigs.json, shared headers, CMake, hooks untouched; no build run).

## Findings (all [V] from pack disassembly 0x19bbc0..0x19bc8e)
- 0x19bbc5 cmp byte ptr [rcx+0x40],1 ; jne 0x19BC6E — proceed flag at a0+0x40
- 0x19bbd2 mov rax,[rcx+0x38] — string 1 size at a0+0x38
- 0x19bbdc mov rcx,[rsi+0x20] — string 1 data at a0+0x20
- 0x19bbe4 cmp rdx,0x1000 ; jb short 0x19BC08 — size+1 < 0x1000 -> direct call
- 0x19bbed mov r8,[rcx-8] — refcount at [data-8]
- 0x19bbfc jae short 0x19BC74 — slow path via data slot 0xF9A8C78
- 0x19bc08 call 0xE935700 — sub_e935700 (lift-set callee)
- 0x19bc0d mov qword ptr [rsi+0x30],0 ; mov qword ptr [rsi+0x38],0xF ; mov byte ptr [rsi+0x20],0 — reset string 1
- 0x19bc21 mov rax,[rsi+0x18] — string 2 size at a0+0x18
- 0x19bc2b mov rcx,[rsi] — string 2 data at a0+0x0
- 0x19bc56 call 0xE935700 — sub_e935700 (second call)
- 0x19bc5b mov qword ptr [rsi+0x10],0 ; mov qword ptr [rsi+0x18],0xF ; mov byte ptr [rsi],0 — reset string 2
- 0x19bc87 call qword ptr [0xF9A8C78] — indirect call through data slot (slow path, not in any table)
- 0x19bc8d int3 — noreturn after slow path

## Calls (all quoted verbatim)
- 0x19bc08 `call 0xE935700` — sub_e935700, lift set, forward-declared in sub_19bbc0.h, called as native::sub_e935700
- 0x19bc56 `call 0xE935700` — sub_e935700, lift set, same
- 0x19bc87 `call qword ptr [0xF9A8C78]` — indirect call through data slot 0xF9A8C78 (slow path only), not in any table; modeled as function-pointer call

## Struct fields touched (all [V])
- a0+0x00 (string 2 data): R, W
- a0+0x10 (string 2 cap): W
- a0+0x18 (string 2 size): R, W
- a0+0x20 (string 1 data): R, W
- a0+0x30 (string 1 cap): W
- a0+0x38 (string 1 size): R, W
- a0+0x40 (proceed flag): R

## Verification
- cppsyntax: OK (no errors in my code; pre-existing sub_e935700.h empty-struct bug avoided by forward-declaring sub_e935700 directly)
- liftcheck: LIFTCHECK OK 0x19bbc0
- gate: GATE OK 0x19BBC0

## UNRESOLVED CALL
none (all calls resolved: sub_e935700 is lift-set; the indirect call through data slot 0xF9A8C78 is handled per the indirect-call rule)

CLOSES? YES
