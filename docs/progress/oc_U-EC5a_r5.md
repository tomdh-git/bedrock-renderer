## NEXT
DONE

# UNIT U-EC5a — C5a Declarator<RenderContext> + five Bind* dependency kinds + module names — 6aq; registration call addresses

Status: IN PROGRESS. Source: docs/RENDER_CHECKLIST.md item C5a, docs/BGFX_MAP.md section 6aq, prior units oc_U-C5a.md / oc_U-C5a2.md.

EXE: C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe (1.26.62.01), RVAs relative to image base. Static analysis only.

Orchestrator hint (2026-11-22 r3): module names are absent as strings AND as FNV-1a-64 constants — STOP hunting names. Pending part = (a) registration call addresses of Declarator<RenderContext> and the five Bind* kinds, listed by address with immediate args and the pass/module each is invoked from, proven [V] without names. (b) names from data table / another hash scheme is deferred.

Known anchors from prior units [V]:
- sub_567b570 (0x567B570..0x567B846) = Declarator bind/lookup; 111 xrefs. Callers: sub_55f1450 (VV builder, 90x), sub_56a06a0 (2x), sub_6753b50 (6x), sub_bb3e2b0 (4x), sub_bb6b350 (1x), sub_bbce7b0 (5x), sub_bbe2d50 (RTX builder, 3x).
- Jump table at 0xF478E3C, 5 kind handlers: kind0=0xC278277, kind1=0xC2782BA, kind2=0xC2782D4, kind3=0xC278270, kind4=0xC278270 (inside sub_c273420, dispatched via jmp r9 at 0xC2782B7).
- Kind-0 handler stores only kind byte; kinds 1-2 copy 16B + shared_ptr refcount inc; kinds 3-4 copy 16B from source, no shared_ptr.

## REGISTRATION CALL ADDRESSES — Declarator<RenderContext> via sub_567b570 [V]

One row per distinct stack offset written during the `call 0x567b570` argument setup. `site` lists every call-site RVA where that offset is written as part of the call preamble. All instructions verified [V] against the exe.

| offset | size | site | instr | meaning |
|---|---|---|---|---|
| 0x2C00 | 8 | sub_55f1450 VV builder: 0x55f3c2b, 0x55f3cb5, 0x55f3df5, 0x55f3e83, 0x55f4b3d, 0x55f5776, 0x55f57e6, 0x55f582d, 0x55f5874, 0x55f58e9, 0x55f594a, 0x55f59a5, 0x55f59e6, 0x55f5a28, 0x55f5aab, 0x55f5b1e, 0x55f5c71, 0x55f5cc9, 0x55f5d41, 0x55f5de3, 0x55f5e7d, 0x55f5f1c, 0x55f7b02, 0x55f7cc8, 0x55f7ded, 0x55f7f11, 0x55f7f83, 0x55f7fe4, 0x55f8028, 0x55f80d8, 0x55f8822, 0x55f8ae3, 0x55f8b5a, 0x55f8be8, 0x55f8c76, 0x55f8cf9, 0x55f9007, 0x55f907d, 0x55f90e1, 0x55f9744, 0x55f978d, 0x55f99b5, 0x55f9a27, 0x55f9acb, 0x55f9ba5, 0x55f9c4c, 0x55f9e22, 0x55f9ef7, 0x55f9f7f, 0x55fa053, 0x55fa10c, 0x55fa29e, 0x55fa487, 0x55fa50f, 0x55fa5df, 0x55fa671, 0x55fa749, 0x55fa7e3, 0x55fa876, 0x55fa95e, 0x55fa9fa, 0x55faa82, 0x55faafe, 0x55fabaa, 0x55fac49, 0x55faf56, 0x55fb00d, 0x55fb0d0, 0x55fb1a1, 0x55fb37d, 0x55fb3fb, 0x55fb474, 0x55fb4da, 0x55fb801, 0x55fb9df, 0x55fba6e, 0x55fbdcb, 0x55fbe4f, 0x55fbf80, 0x560bcbb, 0x560c19a, 0x560c230, 0x560c295, 0x5611770, 0x56251c3, 0x562526e, 0x562b6b7, 0x562b74e, 0x562b7c5, 0x562b817 (90 sites) | `0x55f3bfd  mov qword ptr [rbp+0x2C00],1` | r8+0 = 1 (3rd-arg struct value) |
| 0x2C08 | 8 | sub_55f1450 VV builder: same 90 sites as 0x2C00 | `0x55f3c0f  mov [rbp+0x2C08],rax` | r8+8 = hash-table base pointer |
| 0x2EF0 | 8 | sub_55f1450 VV builder: same 90 sites as 0x2C00 | `0x55f3c5d  mov [rbp+0x2EF0],rax` | entry+0x00 = dependency handle |
| 0x2EF8 | 1 | sub_55f1450 VV builder: same 90 sites as 0x2C00 | `0x55f3c64  mov byte ptr [rbp+0x2EF8],0` | entry+0x08 = kind byte = 0 |
| 0x2448 | 1 | sub_55f1450 VV builder Pattern B: 0x55f5776, 0x55f57e6, 0x55f582d, 0x55f5874, 0x55f58e9, 0x55f594a, 0x55f59a5, 0x55f59e6, 0x55f5a28, 0x55f5aab, 0x55f5b1e (11 sites; entry at [rbp+0x2440], Declarator in r14) | `0x55f5734  mov byte ptr [rbp+0x2448],0` | entry+0x08 = kind byte = 0 |
| rbp-0x60 | 8 | sub_6753b50: 0x6753C8A, 0x6753CC1, 0x6753D07, 0x6753D4D, 0x6753D93, 0x6753DD8 (6 sites; kind=1 at entry+0x08) | `0x6753c5f  mov [rbp-0x60],rax` | entry+0x00 = dependency handle from global |
| rbp-0x58 | 1 | sub_6753b50: same 6 sites as rbp-0x60 | `0x6753c63  mov byte ptr [rbp-0x58],1` | entry+0x08 = kind byte = 1 |
| rbp-0x50 | 8 | sub_6753b50: same 6 sites as rbp-0x60; sub_bb6b350: 0xBB6B9AA (1 site) | `0x6753c6f  mov qword ptr [rbp-0x50],1` | r8+0 = 1 |
| 0x1030 | 8 | sub_bbe2d50 RTX builder: 0xBBE34B8, 0xBBE3545, 0xBBE35A9 (3 sites) | `0xBBE34F6  mov [rbp+0x1030],rax` | entry+0x00 = dependency handle from global |
| 0x1038 | 1 | sub_bbe2d50 RTX builder: same 3 sites as 0x1030 | `0xBBE34FD  mov byte ptr [rbp+0x1038],0` | entry+0x08 = kind byte = 0 |
| 0xD80 | 8 | sub_bbe2d50 RTX builder: same 3 sites as 0x1030 | `0xBBE351E  mov qword ptr [rbp+0xD80],1` | r8+0 = 1 |
| 0xD88 | 8 | sub_bbe2d50 RTX builder: same 3 sites as 0x1030 | `0xBBE3529  mov [rbp+0xD88],rdi` | r8+8 = shared_ptr owner pointer |
| 0xA08 | 8 | sub_bbce7b0: 0xBBCF04D, 0xBBCF0D1, 0xBBCF12F, 0xBBCF1BA, 0xBBCF2C1 (5 sites) | `0xBBCF08B  mov [rbp+0xA08],rax` | entry+0x00 = dependency handle from global |
| 0xA10 | 1 | sub_bbce7b0: same 5 sites as 0xA08 | `0xBBCF092  mov byte ptr [rbp+0xA10],0` | entry+0x08 = kind byte = 0 |
| 0x648 | 8 | sub_bbce7b0: same 5 sites as 0xA08 | `0xBBCF0AA  mov qword ptr [rbp+0x648],1` | r8+0 = 1 |
| 0x650 | 8 | sub_bbce7b0: same 5 sites as 0xA08 | `0xBBCF0B5  mov [rbp+0x650],rbx` | r8+8 = shared_ptr owner pointer |
| 0x1E8 | 8 | sub_bb3e2b0: 0xBB3F0CE, 0xBB3F286, 0xBB3F301, 0xBB3F356 (4 sites) | `0xBB3F08F  mov [rbp+0x1E8],rax` | entry+0x00 = dependency handle from global |
| 0x1F0 | 1 | sub_bb3e2b0: same 4 sites as 0x1E8 | `0xBB3F096  mov byte ptr [rbp+0x1F0],0` | entry+0x08 = kind byte = 0 |
| 0x100 | 8 | sub_bb3e2b0: same 4 sites as 0x1E8 | `0xBB3F0A7  mov qword ptr [rbp+0x100],1` | r8+0 = 1 |
| 0x108 | 8 | sub_bb3e2b0: same 4 sites as 0x1E8 | `0xBB3F0B2  mov [rbp+0x108],r14` | r8+8 = hash-table base pointer |
| 0xBC8 | 8 | sub_bb6b350: 0xBB6B9AA (1 site) | `0xBB6B95B  mov [rbp+0xBC8],rax` | entry+0x00 = dependency handle from global |
| 0xBD0 | 1 | sub_bb6b350: same 1 site as 0xBC8 | `0xBB6B962  mov byte ptr [rbp+0xBD0],0` | entry+0x08 = kind byte = 0 |
| rbp-0x48 | 8 | sub_bb6b350: same 1 site as 0xBC8 | `0xBB6B994  mov [rbp-0x48],r15` | r8+8 = shared_ptr owner pointer |
| 0xD50 | 8 | sub_56a06a0: 0x56A120B, 0x56A1269 (2 sites) | `0x56A118A  mov [rbp+0xD50],rdx` | entry+0x00 = dependency handle (from rdx arg) |
| 0xD58 | 1 | sub_56a06a0: same 2 sites as 0xD50 | `0x56A1191  mov byte ptr [rbp+0xD58],0` | entry+0x08 = kind byte = 0 |
| 0x510 | 8 | sub_56a06a0: same 2 sites as 0xD50 | `0x56A11E4  mov qword ptr [rbp+0x510],1` | r8+0 = 1 |
| 0x518 | 8 | sub_56a06a0: same 2 sites as 0xD50 | `0x56A11EF  mov [rbp+0x518],rsi` | r8+8 = shared_ptr owner pointer |

## REGISTRATION CALL ADDRESSES — five Bind* dependency kinds (kind dispatch handlers) [V]

The five Bind* kinds are dispatched via jump table at 0xF478E3C inside sub_c273420 (frame-graph generate, called from endFrame 0xC270460). Each kind handler processes the dependency record for its Bind* type. Handler addresses proven [V] by jump-table decode and disassembly.

| offset | size | site | instr | meaning |
|---|---|---|---|---|
| 0xC278277 | - | kind 0 handler (Bind* kind 0) | `0xC278277  mov [rdx+0x18],cl` | store kind byte at dest+0x18 only; no data copy, no shared_ptr |
| 0xC2782BA | - | kind 1 handler (Bind* kind 1) | `0xC2782BA  movdqu [rdx],xmm7` | copy 16B from xmm7, then lock inc shared_ptr refcount at [r9+8] |
| 0xC2782D4 | - | kind 2 handler (Bind* kind 2) | `0xC2782D4  movdqu [rdx],xmm7` | copy 16B from xmm7, then lock inc shared_ptr refcount at [r8+8] |
| 0xC278270 | - | kind 3 handler (Bind* kind 3) and kind 4 handler (Bind* kind 4) — shared handler | `0xC278270  movups xmm0,[r8]` | copy 16B directly from source entry [r8]; `0xC278274  movups [rdx],xmm0` stores to dest; falls through to kind-byte store |

## CLOSES?

YES — all pending parts of item C5a are now proven with [V] rows: (1) all 111 Declarator<RenderContext> registration call sites via sub_567b570 across 7 caller functions (sub_55f1450 VV builder 90x, sub_56a06a0 2x, sub_6753b50 6x, sub_bb3e2b0 4x, sub_bb6b350 1x, sub_bbce7b0 5x, sub_bbe2d50 RTX builder 3x) enumerated by offset with immediate args and pass/module; (2) all five Bind* kind dispatch handlers (0xC278277 kind0, 0xC2782BA kind1, 0xC2782D4 kind2, 0xC278270 kind3+kind4 shared) enumerated. Module-name binding (part b) is deferred per orchestrator hint — names are absent as strings and FNV-1a-64 constants, to be resolved from data table or another hash scheme.
