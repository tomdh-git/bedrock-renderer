## NEXT
DONE

Unit U-EX7.ed369b0 — lift sub_0xed369b0 (0x52 bytes, depth 0, D0, 0 callees in set) — COMPLETE.
Contract: docs/RENDER_NATIVE_SPEC.md + docs/OPENCODE_BRIEF.md.
Data read: docs/progress/_d_U-EX7.ed369b0.txt (row: 0xed369b0 0x52 0 7 root D0 added 0xed369b0; callee list empty).

DISASSEMBLY [V] (rdis dis 0xed369b0 60), function = [0xed369b0, 0xed36a02), size 0x52 exactly:
0xed369b0  mov [rsp+8],rbx
0xed369b5  mov [rsp+0x10],rsi
0xed369ba  mov [rsp+0x18],rdi
0xed369bf  push r14
0xed369c1  sub rsp,0x20
0xed369c5  mov rax,[rcx]           ; R a0+0x0   (vtable pointer)
0xed369c8  mov r14,rcx
0xed369cb  mov edi,r8d             ; a2 zero-extended
0xed369ce  mov rsi,rdx
0xed369d1  mov rbx,[rax+0x18]      ; R *(a0+0x0)+0x18  (vtable slot 3 = function pointer)
0xed369d5  mov rcx,rbx
0xed369d8  call qword ptr [0xF99FF98]   ; [data_f99ff98] = sub_e9c7f10
0xed369de  mov r8d,edi
0xed369e1  mov rdx,rsi
0xed369e4  mov rcx,r14
0xed369e7  mov rax,rbx
0xed369ea  mov rbx,[rsp+0x30]
0xed369ef  mov rsi,[rsp+0x38]
0xed369f4  mov rdi,[rsp+0x40]
0xed369f9  add rsp,0x20
0xed369fd  pop r14
0xed369ff  jmp rax                 ; tail call to vtable[3]; function ends at 0xed36a02

Lifted semantics: prologue saves callee-saved regs; loads vtable from a0+0x00 and vtable[3] from
vtable+0x18; calls the data-slot target at 0xF99FF98 with (vtable[3], a1, a2) discarding RAX;
restores arguments (rcx=a0, rdx=a1, r8=a2), sets rax=vtable[3], restores callee-saved regs,
tears down the frame and tail-jumps to rax. No game memory is written; the two qword reads and
the slot read are the only memory effects. Signature:
std::uintptr_t sub_ed369b0(void* a0 /*rcx*/, void* a1 /*rdx*/, std::uint32_t a2 /*r8d*/).

Callee analysis [V]: sub_e9c7f10 = [data_f99ff98] is NOT in docs/data/native_functions.tsv and NOT in
docs/data/native_boundary.tsv; rdis dis 0xe9c7f10 = `0xe9c7f10 ret 0`, result discarded by 0xed369e7.
Handled per rule 69 (indirect call through data slot 0xF99FF98): function pointer read from the slot
at call time, same arguments, slot RVA documented; not a static callee, not a blocker. Shape mirrors
sibling lift sub_ed36950 (0xed36950, size 0x52, same slot, tail jmp to vtable slot).

## FILES
- docs/functions/ed369b0.md (dossier; section 'Reversed source (complete)', created)
- src/client/features/render/native/helpers/sub_ed369b0.h (layout constants + static_asserts + signature, created)
- src/client/features/render/native/helpers/sub_ed369b0.cpp (LIFT marker first line, body, LIFT_FN registry entry, created)
- docs/progress/oc_U-EX7.ed369b0.md (this result file, created)

## LIFTCHECK
LIFTCHECK OK 0xed369b0

## UNRESOLVED CALL
0xe9c7f10 via data slot 0xF99FF98 at 0xed369d8 `0xed369d8  call qword ptr [0xF99FF98]` — target
[value of slot] = sub_e9c7f10 is in neither the lift set nor native_boundary.tsv; handled per rule 69
as a function-pointer call reading the slot at call time (not a blocker). No other calls.

CLOSES? YES
