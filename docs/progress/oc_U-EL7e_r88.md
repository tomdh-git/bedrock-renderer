## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): `- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending | PROGRESS 2026-11-21 oc_U-EL7e.md (verify_oc 185/185): D3D12 backend texture-management chain decoded [V] ...; Minecraft-side pack->GPU chain (texgroup_load 0x5421c90 -> texload 0x58a1310 -> texload_task 0x541bf00 -> undecoded 0x18718D0 at 0x54227af) and atlas stitchers still open (L8a/L8b)`

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; live capture logs under docs/data/live are read-only inputs produced by the orchestrator. Every quoted `0xRVA  instr` below is re-verified verbatim against a fresh rdis dis this session; nothing is redone that r1-r37 already proved [V].

Tags: [V] saw in disassembly (RVA cited, verbatim line quoted) / [V live] saw in an orchestrator live capture log (file cited) / [I] inferred from structure or BGFX_MAP / [?] unknown or not located.

Row rule: one annotated row per distinct offset, all its read/store sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after the address, copied verbatim from rdis) | meaning ONLY if an instruction/string shows it else '-' | tag. Sizes from the instruction (movups/movaps/movdqu/movdqa 16, qword 8, dword/movss 4, word 2, byte 1). No input data pasted as-is; no skipped offsets among quoted sites; no raw instruction dumps outside tables; no ellipsis or catch-all rows.

## Already proven (cited from r1-r37; not re-quoted, not redone)

- Half 1 — sampler flag decode + sampler cache (6ax): [V] docs/functions/e820500.md decodes 0xe820500 instruction-complete; src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h carries the static_asserts; called from blit 0xe818bc0 and executor 0xe821120.
- Half 2a — D3D12 backend texture-management chain: [V] record table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0, updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0, blitSetup 0xe819750; BGFX_MAP 6z/6z-2/6aj confirm table base/stride and live texture records.
- createTexture issuance chain from MC code [V live + dis r24]: sub_4e05e50 -> `0x4E05F77  call 0xBC41420` -> sub_bc41420 -> 0xc296b50 -> wrapper 0xbc73bf0 -> producer 0xbc73770 (command-byte-0x0E) -> bgfx dispatcher case 0xBC6A2C2 (`0xBC6A2B1  mov rax,[rax+0xD0]`, slot 26 = 0xe8143c0 [V BGFX_MAP]) -> `0xBC6A2C2  call qword ptr [0xF99FFA0]` -> createTexture 0xe8143c0 -> `0xE81455B  call 0xE81BF30` TextureD3D12::create (ret 0xe814560 [V live]). Returned handle `0xC296E1A  call 0xBC74120` (ax) -> `0xC296E26  mov [rdi],ax` at texture_obj+0x00 [V r24]; texture_obj = TexturePtr+0x58 (`0x4E05F68  add rdi,0x58`); sdk TexturePtr/ClientTexture [V file read]. Atlas stitchers (L8a/L8b) remain out of scope (MIRROR_SKIP).

## This session — pending item (r37): what rax holds at sub_eea6040's `jmp rax`

### Decode — sub_eea6040 trampoline [V]

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| trampoline sub_eea6040 | 0xEEA6040 | 2 | - | `0xEEA6040  jmp rax` | trampoline: tail-call rax (the vptr[n] indirect-call target); padded with int3 | [V] |
| [0xF99FFA0] init value (.rdata) | 0xF99FFA0 | 8 | [0xF99FFA0] | - | PE .rdata read-only initializer = 0x14EEA6040 = ImageBase 0x140000000 + 0xEEA6040 | [V] |
| [0xF99FFA0] writer scan | - | - | - | - | .text scanned for every `mov [rip+disp32],reg` / `mov [rip+disp32],imm32` targeting 0xF99FFA0 = 0 hits; .rdata is read-only (section flags 0x40000040), so [0xF99FFA0] is never rewritten by code; no writer exists | [V] |

### Resolution — rax at the `jmp rax` [V live + dis]

sub_12893d0 loads the object vptr, then vptr[1], into rax and tail-calls through the trampoline; every indirect virtual call in the binary goes through `call qword ptr [0xF99FFA0]` = sub_eea6040 `jmp rax`, so rax at the jmp is the value loaded from [vptr+8] just before the call:

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| vptr load | [obj+0x0] | 8 | [rcx+0x0] | `0x1289486  mov rax,[rcx]` | rax = object vptr (rcx = object this, reloaded from element+0x10 at 0x1289497/0x128947D) | [V] |
| vtable slot 1 load | [vptr+0x8] | 8 | [rax+0x8] | `0x1289489  mov rax,[rax+8]` | rax = obj->vptr[1] = indirect call target | [V] |
| indirect tail-call | [0xF99FFA0] | 8 | [0xF99FFA0] | `0x1289490  call qword ptr [0xF99FFA0]` | trampoline sub_eea6040 `jmp rax`; rax = vptr[1] = sub_4e05e50 at runtime; pushed ret = 0x1289496 | [V] + [V live] |
| capture return site | 0x1289496 | 1 | - | `0x1289496  nop` | instruction right after the call; matches capture ret=0x1289496 in all 32 samples of docs/data/live/mc_root_4e05e50_callers.txt | [V live] |

[V live] docs/data/live/mc_root_4e05e50_callers.txt: capture on sub_4e05e50 entry, CALLER ret=0x1289496, 32/32 samples enter sub_4e05e50 via sub_12893d0's trampoline call site; RCX = texture object with constant vptr 0x7FF6A8215838 = ImageBase 0x140000000 + vtable 0xF215838 across all samples; vtable 0xF215838 slot 1 = sub_4e05e50 [V rdis vt]. So rax at sub_eea6040's `jmp rax` = sub_4e05e50's absolute entry — resolved [V live + dis]; no further capture is needed and static work is exhausted per r37 (this does NOT make [0xF99FFA0] equal to sub_4e05e50: [0xF99FFA0] holds the trampoline, the callee is carried in rax).

## Field map — sub_12893d0 deferred flush (the indirect caller of sub_4e05e50), sub_4e05e50, constructor, handle store, dispatcher

sub_12893d0 [0x12893d0..0x12895d3) size 0x203, 13 xrefs in [V rdis fn]. For each 0x18-byte element {ptr@0, shared_ctrl@8, obj@0x10} of a deferred vector it add_refs [ctrl+8], copies the 16-byte element, then tail-calls obj->vptr[1](&element) through trampoline [0xF99FFA0] = sub_eea6040 `jmp rax`, detaches the object slot and releases via vptr[0]. At capture time vptr[1] = sub_4e05e50.

| offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| 0x12893D0 | 1 | - | `0x12893D0  push rbp` | sub_12893d0 entry; frame setup | [V] |
| [vec+0x0] | 8 | [rcx+0x0] | `0x1289406  mov r13,[rcx]` | rcx = deferred vector this; r13 = vector begin {ptr@0, ctrl@8} | [V] |
| [vec+0x8] | 8 | [rcx+0x8] | `0x1289409  mov r14,[rcx+8]` | r14 = vector end | [V] |
| [elem+0x8] | 8 | [r13+0x8] | `0x1289431  mov rcx,[r13+8]` | element+0x8 = shared control block; rcx = ctrl | [V] |
| [ctrl+0x8] | 4 | [rcx+0x8] | `0x128943A  mov eax,[rcx+8]` / `0x1289447  lock cmpxchg [rcx+8],edx` | refcount load + atomic add_ref CAS (retry on failure) | [V] |
| [elem+0x0] | 16 | [r13+0x0] | `0x128944E  movups xmm0,[r13]` | copy 16-byte element {ptr@0, ctrl@8} to local desc | [V] |
| [elem+0x10] | 8 | [r13+0x10] | `0x128947D  mov rcx,[r13+0x10]` / `0x128949B  mov qword ptr [r13+0x10],0` | object load (`this` for the virtual call) / detach null-out before release | [V] |
| [obj+0x0] | 8 | [rcx+0x0] | `0x1289486  mov rax,[rcx]` / `0x12894A8  mov rax,[rcx]` | vptr load for the virtual call / release vptr load | [V] |
| [vptr+0x8] | 8 | [rax+0x8] | `0x1289489  mov rax,[rax+8]` | rax = obj->vptr[1] = indirect call target | [V] |
| [0xF99FFA0] | 8 | [0xF99FFA0] | `0x1289490  call qword ptr [0xF99FFA0]` / `0x12894B3  call qword ptr [0xF99FFA0]` / `0x12894FF  call qword ptr [0xF99FFA0]` / `0x1289529  call qword ptr [0xF99FFA0]` / `0x1289544  call qword ptr [0xF99FFA0]` / `0x128957D  call qword ptr [0xF99FFA0]` / `0x1289599  call qword ptr [0xF99FFA0]` (sub_12893d0; 0x1289490 = vptr[1] tail-call, rest = release path) / `0x4E05E86  call qword ptr [0xF99FFA0]` / `0x4E05ED8  call qword ptr [0xF99FFA0]` / `0x4E05EEE  call qword ptr [0xF99FFA0]` / `0x4E05F36  call qword ptr [0xF99FFA0]` / `0x4E05F4C  call qword ptr [0xF99FFA0]` (sub_4e05e50 release path) / `0x4E05753  call qword ptr [0xF99FFA0]` (sub_4e05450 constructor release) / `0xBC6A2C2  call qword ptr [0xF99FFA0]` (bgfx dispatcher slot-26 vcall -> createTexture 0xe8143c0) | every indirect virtual call goes through trampoline sub_eea6040 `jmp rax`; rax holds the callee loaded from [vptr+n] | [V] + [V live] |
| [vptr+0x0] | 8 | [rax+0x0] | `0x12894AB  mov rax,[rax]` | obj->vptr[0] = destroying destructor (release path) | [V] |

sub_4e05e50 [0x4e05e50..0x4e06074) size 0x224, 0 static xrefs in [V rdis] — the texture-job object's vtable[1] create/load method; RCX is the polymorphic texture object itself (not a TexturePtr*, see TexturePtr connection section).

| offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| 0x4E05E50 | 1 | - | `0x4E05E50  push rbp` | entry; 0 static xrefs | [V] |
| [obj+0x18] | 8 | [rcx+0x18] | `0x4E05E71  mov rax,[rcx+0x18]` | shared ctrl of member at object+0x18 | [V] |
| [obj+0x10] | 8 | [rdi+0x10] | `0x4E05E8C  mov rdx,[rdi+0x10]` | shared_ptr member read | [V] |
| [use_cnt+0x8] | 4 | [rdx+0x8] | `0x4E05E95  mov eax,[rdx+8]` / `0x4E05EA8  lock cmpxchg [rdx+8],r8d` | use count load + atomic add_ref CAS | [V] |
| [obj+0xE0] | 8 | [rdi+0xE0] | `0x4E05F61  mov r9,[rdi+0xE0]` | renderer context; object size >= 0xE8 | [V] |
| obj+0x58 | - | reg | `0x4E05F68  add rdi,0x58` | rdi = embedded texture sub-object (TexturePtr+0x58) | [V] |
| 0x4E05F77 | 5 | - | `0x4E05F77  call 0xBC41420` | dragon create call -> sub_bc41420 -> 0xc296b50 -> ... -> createTexture | [V] |
| 0x4E05F7C | 1 | - | `0x4E05F7C  nop` | return site after sub_bc41420; live capture ret=0x4E05F7C | [V live] |

Texture-job object constructor sub_4e05450 — sets vptr = 0xF215838 (rdis vt: slot 0 = sub_4e060b0 destructor, slot 1 = sub_4e05e50; matches the constant live-capture vptr 0x7FF6A8215838):

| offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| [job+0x0] | 8 | [rbx+0x00] | `0x4E05654  mov [rbx],r8` | vptr store = 0xF215838 at object+0x00 | [V] |
| [job+0x8] | 8 | [rbx+0x08] | `0x4E05657  mov [rbx+8],rdx` | object+0x08 = shared ctrl store | [V] |
| [job+0x10] | 8 | [rbx+0x10] | `0x4E0565B  mov [rbx+0x10],rcx` | object+0x10 = object pointer store | [V] |
| [obj+0xC] | 4 | [rcx+0xC] | `0x4E0565F  lock inc dword ptr [rcx+0xC]` | add_ref on the object+0x10 pointee | [V] |
| [job+0x58] | 16 | [rbx+0x58] | `0x4E05689  movups [rbx+0x58],xmm1` | texture sub-object init, 16 bytes copied from [r14] | [V] |
| [job+0xE0] | 8 | [rbx+0xE0] | `0x4E0573A  mov [rbx+0xE0],rax` | renderer context store at object+0xE0 — matches sub_4e05e50 `0x4E05F61  mov r9,[rdi+0xE0]` | [V] |

Handle store — dragon entry 0xc296b50 region (reached via sub_bc41420 at 0xBC41B39; call sites [V live] dragon_texture_entry_c296b50.txt ret=0xBC41B3E):

| offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| 0xC296E1A | 5 | - | `0xC296E1A  call 0xBC74120` | wrapper 0xbc74120 returns 16-bit texture handle in ax [V live] bgfx_texture_wrapper_bc73bf0.txt ret=0xC296D7E | [V] + [V live] |
| 0xC296E22 | 2 | - | `0xC296E22  mov ax,0xFFFF` | 0xFFFF = invalid handle fallback | [V] |
| [texobj+0x0] | 2 | [rdi+0x00] | `0xC296E26  mov [rdi],ax` | 16-bit handle stored at texture object +0x00 | [V] |
| [texobj+0x8] | 16 | [rdi+0x08] | `0xC296E32  movups [rdi+8],xmm0` | 16 result bytes stored at texture object +0x08 | [V] |

createTexture issuance — dispatcher vcall [vptr+0xD0] -> createTexture 0xe8143c0 (createTexture itself has 0 static callers, reached only via indirect [vptr+0xD0] thunks [V r2]):

| offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| [vptr+0xD0] | 8 | [rax+0xD0] | `0xBC6A2B1  mov rax,[rax+0xD0]` | slot 26 (0xD0/8) = createTexture address; BGFX_MAP line 403: slot 26 = 0xe8143c0 [V BGFX_MAP]; the trampoline call through [0xF99FFA0] at 0xBC6A2C2 is listed in the row above | [V] |
| 0xBC6A2C8 | 4 | - | `0xBC6A2C8  test rax,rax` | handle/result tested; live capture caller return site | [V] + [V live] |
| 0xE81455B | 5 | - | `0xE81455B  call 0xE81BF30` | TextureD3D12::create fills the texture record; live ret site 0xe814560 [V live] l8b_texcreate_record.txt | [V] + [V live] |

texgroup_load(0x5421c90) static chain — negative evidence:

| offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| 0x54227AF | 5 | - | `0x54227AF  call 0x18718D0` | texgroup_load calls texture cache 0x18718d0 directly (cache builds objects with vtable 0xEFCA680, never calls sub_4e05e50/sub_12893d0 [V r19]) | [V] |

sub_12893d0 static callers — 4 functions, 13 direct sites [V rdis callers this session]; none is texgroup_load(0x5421c90)/texload(0x58a1310)/texload_task(0x541bf00):

| offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| 0x6632C55 | 5 | - | `0x6632C55  call 0x12893D0` | sub_6632bf0 site 1 (deferred texture vector flush) -> sub_12893d0 | [V] |
| 0x6632D1E | 5 | - | `0x6632D1E  call 0x12893D0` | sub_6632bf0 site 2 (deferred buffer vector flush) -> sub_12893d0 | [V] |
| 0x1145D5A | 5 | - | `0x1145D5A  call 0x12893D0` | sub_1145c20 site 1 -> sub_12893d0 | [V] |
| 0x1145EE5 | 5 | - | `0x1145EE5  call 0x12893D0` | sub_1145c20 site 2 -> sub_12893d0 | [V] |
| 0x6622662 | 5 | - | `0x6622662  call 0x12893D0` | sub_6622610 -> sub_12893d0 | [V] |
| 0x6624538 | 5 | - | `0x6624538  call 0x12893D0` | sub_66232b0 site 1 -> sub_12893d0 | [V] |
| 0x66245FF | 5 | - | `0x66245FF  call 0x12893D0` | sub_66232b0 site 2 -> sub_12893d0 | [V] |
| 0x6626536 | 5 | - | `0x6626536  call 0x12893D0` | sub_66232b0 site 3 -> sub_12893d0 | [V] |
| 0x662661D | 5 | - | `0x662661D  call 0x12893D0` | sub_66232b0 site 4 -> sub_12893d0 | [V] |
| 0x66266FD | 5 | - | `0x66266FD  call 0x12893D0` | sub_66232b0 site 5 -> sub_12893d0 | [V] |
| 0x66267BF | 5 | - | `0x66267BF  call 0x12893D0` | sub_66232b0 site 6 -> sub_12893d0 | [V] |
| 0x6626B86 | 5 | - | `0x6626B86  call 0x12893D0` | sub_66232b0 site 7 -> sub_12893d0 | [V] |
| 0x6626C6D | 5 | - | `0x6626C6D  call 0x12893D0` | sub_66232b0 site 8 -> sub_12893d0 | [V] |

## TexturePtr connection

sdk headers [V file read]: TexturePtr.h `static_assert(sizeof(TexturePtr) == 32)`, non-polymorphic, members mClientTexture +0x00 / mResourceLocationPtr +0x10 (two shared_ptr); ClientTexture empty struct; BedrockTexture.h `static_assert(sizeof(BedrockTexture) == 48)`.

sub_4e05e50's RCX is the polymorphic texture OBJECT itself (constant vptr 0x7FF6A8215838 = base + vtable 0xF215838 across all 32 mc_root capture samples; reads object+0xE0, proving size >= 0xE8) [V live + dis] — it is NOT a TexturePtr*. The texture object carries refcounted members at object+0x10 and object+0x18 that sub_4e05e50 add_refs/releases via [0xF99FFA0] [V dis], matching the sdk TexturePtr shape. The created 16-bit handle lands at [texobj+0x00] where texobj = TexturePtr+0x58 (`0x4E05F68  add rdi,0x58` [V]), i.e. inside the texture job object carried by sub_4e05e50 [V dis]. The job object is constructed by sub_4e05450 (vptr=0xF215838 at `0x4E05654  mov [rbx],r8`; texture sub-object at `0x4E05689  movups [rbx+0x58],xmm1`; renderer ctx at `0x4E0573A  mov [rbx+0xE0],rax`) [V dis]. sub_4e05450 has 16 static callers [V rdis callers], none is texgroup_load/texload/texload_task; the enqueue of the job into sub_6632bf0's deferred vector during pack load is not statically located.

## What I tried that failed (new angles per RETRY #1; do not redo)

- `rdis callers 0x4E05E50` -> 0 calling functions; fn 0x4E05E50..0x4E06074, 0 xrefs in [V rdis this session]. sub_4e05e50's address never appears as a code immediate: `rdis imm 0x4E05E50` = 0 hits, `rdis imm 0x4E060B0` = 0 hits (vtable[1]/vtable[0] are data references only) [V].
- `rdis callers 0x12893D0` -> 4 functions / 13 sites (sub_6632bf0 x2, sub_1145c20 x2, sub_6622610 x1, sub_66232b0 x8) [V this session]; none is texgroup_load/texload/texload_task, and all upward chains from them dead-end at functions with 0 static callers [V rdis/xref r19-r24].
- sub_4e05450 (texture-job constructor, sets vptr=0xF215838 at `0x4E05654  mov [rbx],r8`): 16 static callers [V rdis callers this session], none is texgroup_load/texload/texload_task; upward chain via sub_4dfb810 -> sub_5aefcb0 -> sub_5aef370 -> {sub_5ac72a0, sub_5ad0a80, sub_6605050, sub_6bf7920} also dead-ends [V rdis callers].
- texgroup_load's static callees (`0x54227AF call 0x18718D0`, `0x5421DEC call 0x5477A30`, `0x5421ED6 call 0x5475A30`, `0x5422869 call 0x5424000`, `0x5422C5D call 0x5424130` [V dis]) do not enter the sub_12893d0/sub_4e05450 caller trees; 0x18718d0 cache miss path (vtable 0xEFCA680 object + completion 0x186dac0 [V prior]) never calls sub_4e05e50/sub_12893d0.
- [0xF99FFA0] writer scan: .text store scan for `mov [rip+disp32],reg`/`imm32` targeting 0xF99FFA0 = 0 hits; .rdata read-only, so it is a PE loader initializer = trampoline sub_eea6040, never sub_4e05e50, never rewritten [V this session + r37].
- TexturePtr* claim for sub_4e05e50's RCX: refuted — RCX is a polymorphic object (constant vptr, reads object+0xE0) [V live + dis], not a 32-byte TexturePtr [V file read].

## Live capture evidence (read-only inputs, files cited)

| capture | target | CALLER ret= | samples | meaning | tag |
|---|---|---|---|---|---|
| mc_root_4e05e50_callers.txt | 0x4E05E50 (sub_4e05e50) | 0x1289496 | 32 of 150 hits | sub_12893d0 trampoline tail-calls sub_4e05e50; all samples enter at ret=0x1289496 (the nop after `0x1289490  call qword ptr [0xF99FFA0]`) | [V live] |
| dragon_texture_caller_bc41420.txt | 0xBC41420 | 0x4E05F7C | 7 | sub_4e05e50 calls sub_bc41420; return site `0x4E05F7C  nop` | [V live] |
| dragon_texture_entry_c296b50.txt | 0xC296B50 | 0xBC41B3E | 6 | sub_bc41420 calls dragon entry 0xc296b50 | [V live] |
| bgfx_texture_wrapper_bc73bf0.txt | 0xBC73BF0 | 0xC296D7E | 1 | dragon entry 0xc296b50 calls wrapper 0xbc73bf0 | [V live] |
| createtexture_callers.txt | 0xE8143C0 | 0xBC6A2C8 | 1 of 1612 hits | dispatcher case 0xBC6A2C2 vcall [vptr+0xD0] -> createTexture 0xe8143c0 | [V live] |
| l8b_texcreate_record.txt | 0xE81BF30 | 0xE814560 | 24 of 150 hits | createTexture -> TextureD3D12::create record fill; ret site 0xe814560 | [V live] |

## CLOSES?

NO — blocking fact: no [V]-proven STATIC path texgroup_load(0x5421c90) -> sub_4e05e50 exists. sub_4e05e50 (0x4e05e50) has 0 static xrefs and is reached only via sub_12893d0's indirect vtable[1] tail-call `0x1289490  call qword ptr [0xF99FFA0]` (trampoline sub_eea6040 `jmp rax`, capture ret site 0x1289496 [V live]); sub_12893d0's 4 static callers/13 sites [V this session] are none of texgroup_load/texload/texload_task and all upward chains dead-end at 0-static-caller functions [V rdis/xref]; the constructor sub_4e05450 (16 callers [V rdis]) and texgroup_load's 5 static callees [V dis] never enter the sub_4e05e50 tree. The bind is runtime-only (object vptr[1] = sub_4e05e50 via vtable 0xF215838, tail-call trampoline [0xF99FFA0] = sub_eea6040 `jmp rax`, read-only .rdata initializer, no code writer) and is observed live [V live].

Everything else in the item IS [V]-proven: sampler flag decode + cache (6ax) [V docs/functions/e820500.md], D3D12 backend texture-management chain [V], command-byte-14 producer sub_bc73770 [V r4], dispatcher [vptr+0xD0]->createTexture 0xe8143c0 [V live + dis], returned handle stored at [texobj+0x00] (`0xC296E26  mov [rdi],ax`, size 2) [V] with texobj = TexturePtr+0x58 [V], TexturePtr/ClientTexture sdk headers [V file read].

## TOOL REQUESTS

- None. All instruction lines re-verified verbatim against fresh rdis dis this session (sub_12893d0, sub_eea6040, sub_4e05e50, sub_4e05450 constructor, 0xc296e1x handle store, 0xBC6A2A0 dispatcher, 0xE81455B, 0x54227AF, all 13 sub_12893d0 call sites); caller/xref/vt/imm scans re-run and negative results confirmed. No helper scripts written; no temporary files left behind; static analysis for the texgroup_load -> sub_4e05e50 bind is exhausted (runtime-only vtable[1] bind through trampoline [0xF99FFA0]).
