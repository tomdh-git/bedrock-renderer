## NEXT
DONE. Unit complete: LIFTCHECK OK 0xed36950; CLOSES? YES.

## FILES
- docs/progress/oc_U-EX7.ed36950.md (this file, updated)
- docs/functions/ed36950.md (dossier: signature, register map, Reversed source complete, struct fields, callees, ownership, verification)
- src/client/features/render/native/helpers/sub_ed36950.h (layout constants + static_asserts + signature)
- src/client/features/render/native/helpers/sub_ed36950.cpp (lifted body, first line `// LIFT 0xed36950 size 0x52 1.26.62.01 sub_ed36950`, LIFT_FN registry entry)
No edits to Sigs.json, CMake, shared headers, hooks, or other units' files; no build, no game run.

## LIFTCHECK
`python tools/sigs/liftcheck.py 0xed36950` printed:
LIFTCHECK OK 0xed36950
(exit code 0)

## UNRESOLVED CALL
none. The only call in [0xed36950, 0xed369a2) is `0xed36978  call qword ptr [0xF99FF98]`, a loader-resolved data-slot indirect call handled per rule 68 (function-pointer call read from the slot at call time; [data_f99ff98] = sub_e9c7f10 [V]); it is not a static callee, not a blocker, and liftcheck passed with the call quoted verbatim.

## FACTS (from `rdis dis 0xed36950 80`; function span [0xed36950, 0xed369a2), size 0x52 [V])
- 0xed36950 mov [rsp+8],rbx ; 0xed36955 mov [rsp+0x10],rsi ; 0xed3695a mov [rsp+0x18],rdi ; 0xed3695f push r14 ; 0xed36961 sub rsp,0x20   (prologue, stack only)
- 0xed36965 mov rax,[rcx]        -> vtable = *(void**)a0          [V: R a0+0x00]
- 0xed36968 mov r14,rcx          -> r14 = a0
- 0xed3696b mov edi,r8d          -> a2 zero-extended (r8d = arg3, uint32)
- 0xed3696e mov rsi,rdx          -> rsi = a1
- 0xed36971 mov rbx,[rax+0x20]   -> iface = vtable[4]              [V: R *(a0+0x0)+0x20]
- 0xed36975 mov rcx,rbx          -> slot-call this = vtable[4]
- 0xed36978 call qword ptr [0xF99FF98]   ; [data_f99ff98] = sub_e9c7f10   [V]  (side-effect call; RAX discarded)
- 0xed3697e mov r8d,edi ; 0xed36981 mov rdx,rsi ; 0xed36984 mov rcx,r14   (args restored: this=a0, rdx=a1, r8=a2)
- 0xed36987 mov rax,rbx          -> rax = vtable[4] (slot result discarded)
- 0xed3698a mov rbx,[rsp+0x30] ; 0xed3698f mov rsi,[rsp+0x38] ; 0xed36994 mov rdi,[rsp+0x40] ; 0xed36999 add rsp,0x20 ; 0xed3699d pop r14   (epilogue, stack only)
- 0xed3699f jmp rax              -> tail call vtable[4](a0,a1,a2); RAX result is ours [V]
- Only call: 0xed36978, data-slot indirect (current slot value sub_e9c7f10 [V]); not in the lift set and not boundary -> rule 68 function-pointer call from the slot, not a blocker
- Image base 0x140000000 -> slot VA = imageBase() + 0xF99FF98 (same slot family as 0xF99FFA0 in sub_bc7a3d0/sub_ebdbf10)
- 0xed36950 is a row of docs/data/native_functions.tsv (line 1638: size 0x52, depth 0, milestone 7, region root, status D0)

## DECISIONS
- Signature: std::uintptr_t sub_ed36950(void* a0 /*rcx*/, void* a1 /*rdx*/, std::uint32_t a2 /*r8d*/); return = RAX of tail-called vtable[4] (pointer-sized, exact type of vtable[4] not statically known)
- Slot call: read *(uintptr_t*)(imageBase() + 0xF99FF98) at every call and indirect-call it with (iface, a1, a2); return discarded; not a Boundary wrapper (no Sigs.json symbol, rule 68)
- Tail call: iface(a0, a1, a2) with return propagated (jmp rax)
- Layout constants (with static_asserts): this->vtable at +0x00; vtable->target at +0x20; kThunkSlotRva = 0xF99FF98
- Footprint: nullptr (function writes no game memory)

## PLAN
write .h/.cpp -> cppsyntax -> liftcheck -> docs/functions/ed36950 dossier (Reversed source complete) -> re-liftcheck -> finish
