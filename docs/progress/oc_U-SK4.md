# Unit U-SK4: Stars head 0x6656812 -> join a decoded region

Target: Minecraft.Windows.exe 1.26.62.01 (image-relative RVAs)
Function: sky visitor 0x66560f0, Stars case (tag 6) head starting at 0x6656812.
Stop rule: stop at the first address already covered by an existing opencode unit (coverage table in docs/functions/66560f0_sky_visitor.md), naming that address.
Method: `rdis.exe "<exe>" dis 0x<RVA> 40` per phase, 40 instructions at a time; restart at the next address after any (bad) line.

## NEXT
DONE — no further phases. Stars head is instruction-complete at 0x6656812..0x665697e (tail `jmp 0x6657562` into the covered SkyAmbientSamples body). The next linear address 0x6656983 is the SkyAmbientSamples case head (jump-table case 10), already covered by oc_U-SK3 (0x6656983..0x66569ac then `jmp 0x665708B` into its own body). 0x66569b1 is the VolumetricFog head (covered by oc_U-SK3). No further Stars-head code exists.

Tags: [V] = seen in this disassembly (cite RVA), [I] = inferred, [?] = unknown. Description-field reads noted as `[reg+off]`. No guesses written as fact.

## Phase 1 — 0x6656812, 40 instructions (0x6656812..0x66568f0)
[V rdis 0x6656812..0x66568f0] Stars head: two TLS-slot version guards then the material-string select.
- `mov eax,[0x129F9F60]`; `mov ecx,[0x128767C8]`; `mov rdx,gs:[0x58]`; `mov rcx,[rdx+rcx*8]`; `cmp eax,[rcx+4]`; `jg 0x665D356` — [V] TLS slot data_129f9f60 vs thread-local `[rcx+4]`; cold jump to 0x665D356 if not ready.
- `mov eax,[0x129F9F78]`; `mov ecx,[0x128767C8]`; `mov rdx,gs:[0x58]`; `mov rcx,[rdx+rcx*8]`; `cmp eax,[rcx+4]`; `jg 0x665D3BE` — [V] second TLS slot data_129f9f78; cold jump to 0x665D3BE.
- `cmp dword ptr [rsi+0x70],1` — [V] frame-context tag byte; `==1` selects "StarsForwardPBR" (0xF7CA19E) else "Stars" (0xF54C3E1) via `cmove rdx,rax` (0x6656876). [I: same [rsi+0x70] switch as Cubemap 0x6656388/Legacy 0x665621a]
- `mov r9,[rsi+0x40]`; `mov rcx,[rsi+0x68]` — [V] frame-context resource-cache args [rsi+0x40]/[rsi+0x68] (same as Cubemap H2 0x6656391/0x66563a7).
- `mov eax,0xF`; `mov r10d,5`; `cmove r10,rax` — [V] size r10 = 0xF when forward-PBR else 5.
- `lea rax,[0x129F9F68]`; `lea r8,[0x129F9F50]`; `cmove r8,rax` — [V] allocator/data SSO pointers data_129f9f68 / data_129f9f50.
- `xorps xmm0,xmm0`; `movaps [rbp+0x340],xmm0` — [V] zero 16 B at [rbp+0x340] (resource-out param block).
- `mov [rbp+0x1E0],rdx`; `mov [rbp+0x1E8],r10` — [V] store selected material string ptr at [rbp+0x1E0], size 0xF/5 at [rbp+0x1E8].
- `lea r12,[rbp+0x340]`; `mov [rsp+0x28],r12`; `lea rax,[rbp+0x1E0]`; `mov [rsp+0x20],rax`; `lea rdx,[rbp+0x320]`; `call 0x675E440` — [V] resource lookup call 0x675E440 (rcx=[rsi+0x68], rdx=&[rbp+0x320], r8=data_129f9f50, r9=[rsi+0x40], [rsp+0x20]=&[rbp+0x1E0] name, [rsp+0x28]=&[rbp+0x340]); matches Cubemap H2 (0x67D6D70 there) and Legacy E1/E3 (0x675E440) [I].
- `mov rax,[rbp+0x320]`; `mov r14,[rax]`; `test r14,r14`; `je 0x665AEE8` — [V] r14 = result shared_ptr; null => exit at 0x665AEE8 (Cubemap exit tail `mov rsi,[rbp+0x328]; jmp 0x665D124`).
- `mov eax,[0x129CA5E0]`; `mov ecx,[0x128767C8]` — [V] begin third TLS slot check (data_129ca5e0), continues into Phase 2.

No description-field reads in this phase (no `[rdi+off]`). Only frame-context [rsi+0x40]/[rsi+0x68]/[rsi+0x70] and locals.

## Phase 2 — 0x66568f0, 40 instructions (0x66568f0..0x66569ac)
[V rdis 0x66568f0..0x66569ac] Stars head: third TLS check, loaded-flag test, shared-ptr retain/release of the resource, then tail-join into the covered SkyAmbientSamples body. NOTE: 0x6656983 is the SkyAmbientSamples case head (jump-table case 10), NOT part of the Stars head — the Stars head ends at 0x665697e.
- `mov ecx,[0x128767C8]`; `mov rdx,gs:[0x58]`; `mov rcx,[rdx+rcx*8]`; `cmp eax,[rcx+4]`; `jg 0x665D50F` — [V] third TLS slot check (eax still from data_129ca5e0 loaded in Phase 1); cold jump 0x665D50F.
- `cmp byte ptr [r14+0x10],1`; `jne 0x665AEE8` — [V] `[r14+0x10]` byte == loaded-flag of the resource shared_ptr; not loaded => exit 0x665AEE8. Matches Cubemap H3 `cmp byte [r15+0x10],1; jne 0x665d11d` [I].
- `mov rax,[rbp+0x320]`; `mov rcx,[rax+8]`; `test rcx,rcx`; `je 0x6657558` — [V] ctrl block = `[rbp+0x320]`, its `[+8]` = ref count; zero => jump 0x6657558 (inside SkyAmbientSamples body 0x665708b..0x665803c — a covered region; branch only, not followed linearly).
- `lock inc dword ptr [rcx+8]` — [V] retain ctrl block.
- `mov rcx,[rax]`; `mov r14,[rax+8]`; `mov rax,[rcx+0x18]`; `mov r15,[rax]`; `test r14,r14`; `je 0x6657562` — [V] r14 = old ctrl block (now `[rbp+0x320]+8`), rax = `[ctrl]->[+0x18]`, r15 = `[rax]` (owner chain, cf. Cubemap C1 `[r14]->[+0x18]->[0]`); null old ctrl => 0x6657562 (covered SkyAmbientSamples body).
- `lock dec dword ptr [r14+8]`; `jne 0x6657562` — [V] release old ctrl; nonzero refcount => 0x6657562.
- `mov rax,[r14]`; `mov rax,[rax]`; `mov rcx,r14`; `call qword ptr [0xF99FFA0]` — [V] vcall release on old ctrl block (sub_eea6040, the count-tag/release vtable slot).
- `lock dec dword ptr [r14+0xC]`; `jne 0x6657562` — [V] second refcount `[r14+0xC]`; nonzero => 0x6657562.
- `mov rax,[r14]`; `mov rax,[rax+8]`; `mov rcx,r14`; `call qword ptr [0xF99FFA0]` — [V] second vcall release on old ctrl.
- `jmp 0x6657562` — [V] Stars head tail: join into the covered SkyAmbientSamples body at 0x6657562 (`test r15,r15; je 0x665AEE8`).
- `movzx ebx,word ptr [rdi]`; `mov [rbp+0x1E0],bx` — [V] **SkyAmbientSamples head (case 10)**: `[rdi+0x00]` u16 -> [rbp+0x1E0]. NOT Stars; this is the jump-table case-10 entry, already covered by SK3 (0x6656983..0x66569ac).
- `xorps xmm0,xmm0`; `movups [rbp+0x1E8],xmm0` — [V] zero 16 B at [rbp+0x1E8] (SkyAmbientSamples head).
- `mov rax,[rdi+0x10]`; `test rax,rax`; `je 0x6657088` — [V] `[rdi+0x10]` qword = shared-ptr ctrl block; null => 0x6657088 (SkyAmbientSamples body, covered).
- `lock inc dword ptr [rax+8]`; `mov r12,[rdi+0x10]` — [V] retain ctrl block; r12 = `[rdi+0x10]` (SkyAmbientSamples head).
- `jmp 0x665708B` — [V] SkyAmbientSamples head tail: join into its own body at 0x665708B (covered).

Stars head description fields read: NONE — the Stars head (0x6656812..0x665697e) performs only the material resource lookup and shared-ptr swap; it never dereferences `[rdi+off]`. The dossier's claim of Stars description reads (+0x00/+0x18/+0x58/+0x5A) at "0x6656812.." is therefore NOT satisfied by this head; the reads at 0x6656983/0x6656997 belong to the SkyAmbientSamples case head, not Stars [V].
