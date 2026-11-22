## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): `- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending | PROGRESS 2026-11-21 oc_U-EL7e.md (verify_oc 185/185): D3D12 backend texture-management chain decoded [V] ...; Minecraft-side pack->GPU chain (texgroup_load 0x5421c90 -> texload 0x58a1310 -> texload_task 0x541bf00 -> undecoded 0x18718D0 at 0x54227af) and atlas stitchers still open (L8a/L8b)`

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; live capture logs under docs/data/live are read-only inputs produced by the orchestrator.

Tags: [V] saw in disassembly (RVA cited, verbatim line quoted) / [V live] saw in an orchestrator live capture log (file cited) / [I] inferred from structure or BGFX_MAP / [?] unknown or not located.

Row rule: one annotated row per distinct offset, all its sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after address, copied verbatim from rdis) | meaning ONLY if an instruction/string shows it else '-' | tag. Sizes from the instruction (movups/movaps/movdqu/movdqa 16, qword 8, dword/movss 4, word 2, byte 1). No input data pasted as-is; no skipped offsets among quoted sites; no raw instruction dumps outside tables.

## Already proven (do NOT redo — cited from r1-r21 / verified files; not re-quoted here)

- Half 1 — sampler flag decode + sampler cache (6ax): [V] docs/functions/e820500.md decodes 0xe820500 instruction-complete; src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h carries the static_asserts; called from blit 0xe818bc0 and executor 0xe821120.
- Half 2a — D3D12 backend texture-management chain: [V] record table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0, updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0, blitSetup 0xe819750; BGFX_MAP 6z/6z-2/6aj confirm table base/stride and live texture records.
- r2 (not redone): xref.py callers 0xe8143c0 = EMPTY — createTexture 0xe8143c0 has no static caller, reached only via indirect [vptr+0xD0] thunks.
- r3 (not redone): texload 0x58a1310 and texload_task 0x541bf00 have EMPTY static caller lists and are never called by texgroup_load — the item-line sub-chain texgroup_load->texload->texload_task->0x18718d0 is NOT statically supported as written.
- 0x18718d0 fully decoded [V pre/0x18718d0_fn.md, not redone]: cache lookup loop; on miss builds an object with vtable 0xEFCA680 and calls completion 0x186dac0; never calls sub_4e05e50 or sub_12893d0.
- r4/r5 (not redone): command-byte-14 producer = sub_0xbc73770 writes 0x0E into the bgfx command buffer [V]; reached only via thin wrappers 0xbc73bf0/0xbc73ed0/0xbc74120 from dragon entries 0xc296b50/0xc297000/0xc2a3d90/0xbc63c80 [V]; MC texture code calls none statically [V xref evidence].
- sdk headers [V file read]: TexturePtr.h `static_assert(sizeof(TexturePtr) == 32)`, mClientTexture +0x00 / mResourceLocationPtr +0x10 (two shared_ptr); ClientTexture empty struct; BedrockTexture.h `static_assert(sizeof(BedrockTexture) == 48)`.

## This session — verified findings (re-checked verbatim via rdis this session)

### 1. texgroup_load(0x5421c90) static chain — negative evidence [V]

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| texgroup_load cache call | 0x54227AF | 5 | - | `0x54227AF  call 0x18718D0` | texgroup_load calls texture cache 0x18718d0 directly (not texload/texload_task) | [V] |

### 2. Indirect caller of sub_4e05e50 = sub_12893d0, decoded instruction-complete [V]

Note: rdis reports `sub_12893d0  [0x12893d0..0x12895d3) size 0x203 13 xrefs in` [V rdis fn]. Earlier notes treating 0x1289440 as a separate function are wrong: 0x1289440 is a local label inside sub_12893d0.

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| sub_12893d0 entry | 0x12893D0 | 1 | - | `0x12893D0  push rbp` | deferred-transaction processor entry; frame setup | [V] |
| array begin load | [rcx+0x0] | 8 | [rcx+0x0] | `0x1289406  mov r13,[rcx]` | r13 = deferred vector begin {ptr@0, ctrl@8} | [V] |
| array end load | [rcx+0x8] | 8 | [rcx+0x8] | `0x1289409  mov r14,[rcx+8]` | r14 = deferred vector end | [V] |
| shared ctrl load | [r13+0x8] | 8 | [r13+0x8] | `0x1289431  mov rcx,[r13+8]` | element+0x8 = shared control-block pointer | [V] |
| refcount load | [rcx+0x8] | 4 | [rcx+0x8] | `0x128943A  mov eax,[rcx+8]` | eax = refcount at ctrl+8 | [V] |
| add_ref CAS | [rcx+0x8] | 4 | [rcx+0x8] | `0x1289447  lock cmpxchg [rcx+8],edx` | atomic refcount increment, retry on failure | [V] |
| element copy 16B | [r13+0x0] | 16 | [r13+0x0] | `0x128944E  movups xmm0,[r13]` | copy element {ptr@0, ctrl@8} to local desc | [V] |
| object load | [r13+0x10] | 8 | [r13+0x10] | `0x128947D  mov rcx,[r13+0x10]` | rcx = element+0x10 = `this` for virtual call | [V] |
| vptr load | [rcx+0x0] | 8 | [rcx+0x0] | `0x1289486  mov rax,[rcx]` | rax = object vptr | [V] |
| vtable slot 1 load | [rax+0x8] | 8 | [rax+0x8] | `0x1289489  mov rax,[rax+8]` | rax = obj->vptr[1] = indirect call target | [V] |
| INDIRECT TAIL-CALL -> sub_4e05e50 | [0xF99FFA0] | 8 | [0xF99FFA0] | `0x1289490  call qword ptr [0xF99FFA0]` | trampoline sub_eea6040 `jmp rax`; rax = vptr[1] = sub_4e05e50 at runtime; pushed ret = 0x1289496 | [V] + [V live] |
| capture return site | 0x1289496 | 1 | - | `0x1289496  nop` | instruction right after call; matches capture ret=0x1289496 in all 32 samples | [V live] |
| object null-out / detach | [r13+0x10] | 8 | [r13+0x10] | `0x128949B  mov qword ptr [r13+0x10],0` | clear element+0x10 before release | [V] |
| release vptr load | [rcx+0x0] | 8 | [rcx+0x0] | `0x12894A8  mov rax,[rcx]` | rax = object vptr | [V] |
| release slot 0 load | [rax+0x0] | 8 | [rax+0x0] | `0x12894AB  mov rax,[rax]` | rax = obj->vptr[0] = destroying destructor | [V] |
| release indirect call | [0xF99FFA0] | 8 | [0xF99FFA0] | `0x12894B3  call qword ptr [0xF99FFA0]` | release object through same trampoline | [V] |

Meaning of sub_12893d0: for each 0x18-byte element {ptr@0, shared_ctrl@8, obj@0x10} it add_refs [ctrl+8], copies the 16-byte element, then tail-calls obj->vptr[1](&element_copy) through trampoline [0xF99FFA0] (= sub_eea6040 `jmp rax`), detaches obj slot and releases via vptr[0]. At capture time vptr[1] = sub_4e05e50. This is the deferred-texture-transaction flush that invokes the texture job's create/load method.

### 3. sub_12893d0 static callers — 4 functions, 13 sites [V rdis callers this session]

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| caller sub_6632bf0 site 1 | 0x6632C55 | 5 | - | `0x6632C55  call 0x12893D0` | deferred texture vector flush -> sub_12893d0 | [V] |
| caller sub_6632bf0 site 2 | 0x6632D1E | 5 | - | `0x6632D1E  call 0x12893D0` | deferred buffer vector flush -> sub_12893d0 | [V] |
| caller sub_1145c20 site | 0x1145D5A | 5 | - | `0x1145D5A  call 0x12893D0` | sub_1145c20 -> sub_12893d0 | [V] |
| caller sub_6622610 site | 0x6622662 | 5 | - | `0x6622662  call 0x12893D0` | sub_6622610 -> sub_12893d0 | [V] |
| caller sub_66232b0 sites | 0x66232B0 | - | - | (8 sites inside sub_66232b0) | sub_66232b0 -> sub_12893d0 x8 [V rdis callers] | [V] |

None of these four callers is texgroup_load(0x5421c90), texload(0x58a1310) or texload_task(0x541bf00). All upward chains from them dead-end at functions with 0 static callers [V r19, not redone].

### 4. sub_4e05e50 — texture-object vtable[1] create/load method, 0 static xrefs [V dis this session + V live]

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| sub_4e05e50 entry | 0x4E05E50 | 1 | - | `0x4E05E50  push rbp` | entry; rdis `sub_4e05e50 [0x4e05e50..0x4e06074) size 0x224 0 xrefs in` | [V] |
| object+0x18 load | [rcx+0x18] | 8 | [rcx+0x18] | `0x4E05E71  mov rax,[rcx+0x18]` | shared ctrl of member at object+0x18 | [V] |
| object+0x10 load | [rdi+0x10] | 8 | [rdi+0x10] | `0x4E05E8C  mov rdx,[rdi+0x10]` | shared_ptr member read | [V] |
| refcount load (sub_4e05e50) | [rdx+0x8] | 4 | [rdx+0x8] | `0x4E05E95  mov eax,[rdx+8]` | use count of the object+0x10 pointee | [V] |
| add_ref CAS (sub_4e05e50) | [rdx+0x8] | 4 | [rdx+0x8] | `0x4E05EA8  lock cmpxchg [rdx+8],r8d` | atomic use-count increment | [V] |
| renderer ctx load | [rdi+0xE0] | 8 | [rdi+0xE0] | `0x4E05F61  mov r9,[rdi+0xE0]` | object+0xE0 = renderer context -> R9 (object >= 0xE8 bytes) | [V] |
| texture sub-object | rdi+0x58 | - | reg | `0x4E05F68  add rdi,0x58` | rdi = embedded texture sub-object (TexturePtr+0x58) | [V] |
| dragon create call | 0xBC41420 | 5 | - | `0x4E05F77  call 0xBC41420` | sub_bc41420 -> 0xc296b50 -> ... -> createTexture | [V] |
| sub_4e05e50 ret site | 0x4E05F7C | 1 | - | `0x4E05F7C  nop` | return after sub_bc41420; live capture ret=0x4E05F7C | [V live] |

sub_4e05e50's RCX is the polymorphic texture OBJECT itself (constant vptr 0x00007FF6A8215838 at object+0x00 across all 32 capture samples; reads object+0xE0 proving size >= 0xE8) [V live + dis] — it is NOT a 32-byte TexturePtr* (TexturePtr is non-polymorphic, `static_assert(sizeof(TexturePtr) == 32)` [V file read]).

### 5. Vtable 0xF215838 — texture job object vtable (slot 1 = sub_4e05e50) [V dis + V live]

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| vtable slot 0 | 0xF215838+0x000 | 8 | [0xF215838] | `0x4E060BB  lea rax,[0xF215838]` / `0x4E060C2  mov [rcx],rax` | slot 0 = sub_4e060b0 (destroying destructor, size 0x6e) | [V] |
| vtable slot 1 | 0xF215838+0x008 | 8 | [0xF215838+8] | vtable [V rdis vt 0xF215838]: `0 +0x000 sub_4e060b0` / `1 +0x008 sub_4e05e50` | slot 1 = sub_4e05e50 (size 0x224) — matches live capture vptr+8 resolving to sub_4e05e50 | [V] |
| vtable slot 2 | 0xF215838+0x010 | 8 | [0xF215838+0x10] | vtable [V rdis vt 0xF215838]: `2 +0x010 non-code 0x0` | slot 2 = null/non-code | [V] |

rip-relative references to 0xF215838 [V ripscan]: `0x4E0564D` (func 0x4E05450), `0x4E05668` (func 0x4E05450), `0x4E060BE` (func 0x4E060b0). The 0x4E05450 references are the CONSTRUCTOR path setting vptr = 0xF215838 on new texture job objects.

### 6. Texture job object CONSTRUCTOR in sub_4e05450 — sets vptr=0xF215838, init at +0x58 and +0xE0 [V dis this session]

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| vptr load immediate | 0xF215838 | 8 | imm | `0x4E0564D  lea r8,[0xF215838]` | load vtable address 0xF215838 (data_f215838) | [V] |
| vptr store | [rbx+0x00] | 8 | [rbx+0x00] | `0x4E05654  mov [rbx],r8` | store vptr = 0xF215838 at object+0x00 | [V] |
| shared_ptr member store | [rbx+0x08] | 8 | [rbx+0x08] | `0x4E05657  mov [rbx+8],rdx` | object+0x08 = shared ctrl | [V] |
| object member store | [rbx+0x10] | 8 | [rbx+0x10] | `0x4E0565B  mov [rbx+0x10],rcx` | object+0x10 = object pointer | [V] |
| add_ref on object+0x0C | [rcx+0xC] | 4 | [rcx+0xC] | `0x4E0565F  lock inc dword ptr [rcx+0xC]` | add_ref on the object+0x10 pointee | [V] |
| alt path vptr store | [rbx+0x00] | 8 | [rbx+0x00] | `0x4E05665  lea rdx,[0xF215838]` / `0x4E0566C  mov [rbx],rdx` | vptr = 0xF215838 on null-object path | [V] |
| alt path zero +0x08 | [rbx+0x08] | 16 | [rbx+0x08] | `0x4E0566F  xorps xmm0,xmm0` / `0x4E05672  movups [rbx+8],xmm0` | object+0x08/+0x10 = 0 | [V] |
| object+0x18 zero | [rbx+0x18] | 16 | [rbx+0x18] | `0x4E05676  xorps xmm0,xmm0` / `0x4E05679  movups [rbx+0x18],xmm0` | object+0x18 = 0 | [V] |
| texture sub-object init 16B | [rbx+0x58] | 16 | [rbx+0x58] | `0x4E05685  movups xmm1,[r14]` / `0x4E05689  movups [rbx+0x58],xmm1` | copy 16 bytes from [r14] to object+0x58 (texture sub-object) | [V] |
| object+0x68 store | [rbx+0x68] | 8 | [rbx+0x68] | `0x4E0567D  mov rdx,[r14+0x10]` / `0x4E05681  mov [rbx+0x68],rdx` | object+0x68 = [r14+0x10] | [V] |
| renderer context store | [rbx+0xE0] | 8 | [rbx+0xE0] | `0x4E0573A  mov [rbx+0xE0],rax` | object+0xE0 = renderer context — matches sub_4e05e50 `0x4E05F61  mov r9,[rdi+0xE0]` | [V] |

sub_4e05450 is called by 16 functions [V rdis callers]: sub_4dfb810, sub_4dfbdf0, sub_4dfd780, sub_4dfdd90, sub_64f0810, sub_64f0ae0, sub_64f0dd0, sub_66232b0 (endFrame, x2), sub_6632fd0, sub_668a140, sub_668ecb0, sub_668f080, sub_c28f220, sub_c294b90, sub_c294c90, sub_e86ced0. None is texgroup_load(0x5421c90), texload(0x58a1310) or texload_task(0x541bf00). sub_4dfb810 -> sub_5aefcb0 -> sub_5aef370 -> {sub_5ac72a0, sub_5ad0a80, sub_6605050, sub_6bf7920} [V rdis callers]; none of these is texgroup_load either.

### 7. Handle store into the texture object (dragon entry 0xc296b50, via sub_bc41420) [V dis this session]

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| wrapper returns handle | 0xC296E1A | 5 | - | `0xC296E1A  call 0xBC74120` | wrapper 0xbc74120 returns 16-bit texture handle in ax (called from sub_bc41420 at 0xBC41B39) | [V] |
| invalid-handle fallback | 0xC296E22 | 2 | - | `0xC296E22  mov ax,0xFFFF` | 0xFFFF = invalid handle fallback | [V] |
| handle store word | [rdi+0x00] | 2 | [rdi+0x00] | `0xC296E26  mov [rdi],ax` | 16-bit handle stored at texture object +0x00 | [V] |
| rest of result | [rdi+0x08] | 16 | [rdi+0x08] | `0xC296E32  movups [rdi+8],xmm0` | 16 result bytes stored at texture object +0x08 | [V] |

texture object = TexturePtr+0x58 (`0x4E05F68  add rdi,0x58` [V]), so the created handle lands inside the texture object carried by sub_4e05e50.

### 8. createTexture issuance — dispatcher vcall [vptr+0xD0] -> createTexture 0xe8143c0 -> TextureD3D12::create [V dis this session + V live]

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| vtable slot 26 load | [rax+0xD0] | 8 | [rax+0xD0] | `0xBC6A2B1  mov rax,[rax+0xD0]` | slot 26 (0xD0/8) = createTexture address; BGFX_MAP line 403: slot 26 = 0xe8143c0 | [V] |
| dispatcher vcall | [0xF99FFA0] | 8 | [0xF99FFA0] | `0xBC6A2C2  call qword ptr [0xF99FFA0]` | trampoline tail-call; rax = [vptr+0xD0] = createTexture 0xe8143c0 | [V] + [V live ret=0xBC6A2C8] |
| result test | 0xBC6A2C8 | 4 | - | `0xBC6A2C8  test rax,rax` | handle/result tested; return site of live createTexture caller | [V] |
| createTexture -> TextureD3D12::create | 0xE81455B | 5 | - | `0xE81455B  call 0xE81BF30` | TextureD3D12::create fills the texture record; ret site 0xE814560 = live capture l8b ret=0xE814560 | [V] + [V live] |

### 9. Full live chain recap [V live] (capture logs, read-only inputs)

| name | source | ret= | meaning | tag |
|---|---|---|---|---|
| sub_4e05e50 caller | docs/data/live/mc_root_4e05e50_callers.txt | 0x1289496 | sub_12893d0 tail-calls sub_4e05e50; all 32 samples enter at ret=0x1289496 | [V live] |
| sub_bc41420 caller | docs/data/live/dragon_texture_caller_bc41420.txt | 0x4E05F7C | sub_4e05e50 calls sub_bc41420 (return site 0x4E05F7C nop) | [V live] |
| dragon entry caller | docs/data/live/dragon_texture_entry_c296b50.txt | 0xBC41B3E | sub_bc41420 calls dragon entry 0xc296b50 | [V live] |
| wrapper caller | docs/data/live/bgfx_texture_wrapper_bc73bf0.txt | 0xC296D7E | dragon entry 0xc296b50 calls wrapper 0xbc73bf0 | [V live] |
| createTexture caller | docs/data/live/createtexture_callers.txt | 0xBC6A2C8 | dispatcher case 0xBC6A2C2 vcall [vptr+0xD0] -> createTexture 0xe8143c0 | [V live] |

Chain (MC end proven [V live]): texture job object (vptr 0x7FF6A8215838 = RVA 0xF215838 + base; vptr[1] = sub_4e05e50) created by sub_4e05450 (`0x4E05654  mov [rbx],r8` stores vptr; `0x4E0573A  mov [rbx+0xE0],rax` stores renderer ctx) -> sub_12893d0@0x1289490 (tail-call via trampoline [0xF99FFA0] = sub_eea6040 `jmp rax`, return address 0x1289496) -> sub_4e05e50(object*, out_ptr) (`0x4E05F77  call 0xBC41420`, return site `0x4E05F7C  nop`) -> sub_bc41420 -> 0xc296b50 -> 0xbc73bf0 -> 0xbc73770 (command-byte-0x0E producer [V r4]) -> bgfx dispatcher case 0xBC6A2C2 (`0xBC6A2B1  mov rax,[rax+0xD0]`, slot 26 = 0xe8143c0 [V BGFX_MAP]) -> `0xBC6A2C2  call qword ptr [0xF99FFA0]` -> createTexture 0xe8143c0 -> `0xE81455B  call 0xE81BF30` TextureD3D12::create (record fill, ret 0xe814560) [V live + dis]. Returned handle: `0xC296E1A  call 0xBC74120` (ax) -> `0xC296E26  mov [rdi],ax` at texture_obj+0x00 [V dis]; texture_obj = TexturePtr+0x58 [V]; sdk TexturePtr/ClientTexture [V file read].

## TexturePtr connection

sub_4e05e50's RCX is the texture OBJECT itself (vtable[1] method; vptr at object+0x00, capture vptr constant 0x7FF6A8215838 across all 32 samples; sub_4e05e50 reads object+0xE0, proving the object is >= 0xE8 bytes) [V live + dis] — it is NOT a TexturePtr* (TexturePtr is 32 bytes and non-polymorphic per the sdk header) [V file read + V dis]. The texture object carries refcounted/shared_ptr-shaped members at object+0x10 and object+0x18 that sub_4e05e50 add_refs/releases via [0xF99FFA0] [V dis], matching the sdk TexturePtr shape (two shared_ptr members, sizeof 32) [V file read src/sdk/mc/deps/minecraft_renderer/renderer/TexturePtr.h; ClientTexture empty struct; BedrockTexture 48 bytes [V file read]]. The created handle lands at [obj+0x58+0] inside the job object [V dis].

The texture job object with vtable 0xF215838 is CONSTRUCTED by sub_4e05450 (vptr=0xF215838 at object+0x00 via `0x4E05654  mov [rbx],r8`; texture sub-object init at +0x58 via `0x4E05689  movups [rbx+0x58],xmm1`; renderer context at +0xE0 via `0x4E0573A  mov [rbx+0xE0],rax`). sub_4e05450 has 16 static callers [V rdis callers], none is texgroup_load(0x5421c90)/texload(0x58a1310)/texload_task(0x541bf00). The enqueue of the texture job into sub_6632bf0's deferred vector (this+0x00) during pack load is not statically located.

## What I tried that failed (this session; do not redo r1-r21)

- Upward caller chains from all four sub_12893d0 callers (sub_1145c20, sub_6622610, sub_66232b0, sub_6632bf0): every top function has 0 static callers [V rdis/xref] — reached only via indirect/vtable dispatch; none is texgroup_load/texload.
- sub_4e060b0 (vtable[0] destructor, also sets vptr=0xF215838): 0 static callers (`rdis callers 0x4E060B0` -> 0 calling functions). Called indirectly only.
- sub_4e05450 (texture job constructor): 16 static callers [V rdis callers], none is texgroup_load/texload/texload_task. Upward chains from sub_4dfb810 (sub_5aefcb0 -> sub_5aef370 -> 4 callers) also dead-end without reaching texgroup_load.
- rdis imm 0x4E05E50: 0 hits — sub_4e05e50's address never appears as an immediate in code (vtable[1] is a data reference, not code).
- rdis imm 0x4E060B0: 0 hits — same for the destructor/constructor.
- TexturePtr* claim for sub_4e05e50's RCX: refuted — RCX is a polymorphic texture object (constant vptr 0x7FF6A8215838, reads object+0xE0) [V live + dis], not a 32-byte TexturePtr [V file read].
- Prior negatives (not redone): xref.py callers 0xe8143c0 EMPTY; texload/texload_task EMPTY; 0x18718d0 cache miss path (vtable 0xEFCA680 object + completion 0x186dac0) never calls sub_4e05e50/sub_12893d0 [V prior]; cache 0x18718d0 builds objects with vtable 0xEFCA680, NOT 0xF215838 — different object type.

## Interpretation

Proven [V] this session and overall:
- sampler flag decode + cache (6ax) [V] — docs/functions/e820500.md.
- D3D12 backend texture-management chain [V] — table this+0xBDE178 stride 0xB8; slots 26/28/30-34.
- command-byte-14 producer sub_0xbc73770 [V r4]; dispatcher vcall [vptr+0xD0] -> createTexture 0xe8143c0 [V live + dis].
- Vtable 0xF215838: slot 0 = sub_4e060b0 (destructor), slot 1 = sub_4e05e50 (create/load) [V rdis vt]; matches live capture vptr = 0x7FF6A8215838 (RVA 0xF215838 + image base) [V live].
- Texture job object constructor: sub_4e05450 sets vptr=0xF215838 at `0x4E05654  mov [rbx],r8`, inits texture sub-object at +0x58 at `0x4E05689  movups [rbx+0x58],xmm1`, stores renderer ctx at +0xE0 at `0x4E0573A  mov [rbx+0xE0],rax` [V dis this session].
- MC-side texture object create/load method sub_4e05e50 invoked live via sub_12893d0 tail-call (ret=0x1289496, all 32 samples) [V live]; sub_4e05e50 -> sub_bc41420 -> dragon entry 0xc296b50 -> wrapper 0xbc73bf0 -> producer 0xbc73770 -> dispatcher -> createTexture -> TextureD3D12::create [V live + dis].
- returned handle stored at [texture_obj+0x00] by `0xC296E26  mov [rdi],ax` (size 2, word) [V]; texture_obj = TexturePtr+0x58 [V]; sdk TexturePtr/ClientTexture [V file read].

Not [V]-proven (single blocking fact): the STATIC link texgroup_load(0x5421c90) -> sub_4e05e50. sub_4e05e50 has 0 static xrefs and is reached only via sub_12893d0's indirect vtable[1] tail-call `0x1289490  call qword ptr [0xF99FFA0]` (capture ret site 0x1289496 [V live]); sub_12893d0's 4 static callers [V this session] none is texgroup_load/texload/texload_task, and all upward chains dead-end at 0-static-caller functions [V r19]; sub_4e05450 (the constructor that sets vptr=0xF215838) has 16 static callers, none is texgroup_load/texload/texload_task [V rdis callers this session]; texgroup_load's static chain ends at `0x54227AF call 0x18718D0` [V this session] and cache 0x18718d0 builds objects with vtable 0xEFCA680 (different vtable) which never calls sub_4e05e50/sub_12893d0 [V r19]. The bind is runtime-only (object vptr+8 = sub_4e05e50 via vtable 0xF215838, tail-call trampoline [0xF99FFA0] = sub_eea6040 `jmp rax`) and is observed live [V live].

Atlas stitchers (L8a/L8b) remain out of scope (MIRROR_SKIP).

## CLOSES?

NO — blocking fact: no [V]-proven static path texgroup_load(0x5421c90) -> sub_4e05e50. sub_4e05e50 has 0 static xrefs (`rdis callers 0x4E05E50` -> 0 calling functions; fn 0x4E05E50..0x4E06074, 0 xrefs in [V rdis]) and is only reached via sub_12893d0's indirect vtable[1] call `0x1289490  call qword ptr [0xF99FFA0]` (capture ret site 0x1289496 [V live]); sub_12893d0 (13 xrefs in [V rdis]) is statically called from endFrame->sub_6632bf0 (`0x6632C55`/`0x6632D1E call 0x12893D0` [V dis]) plus sub_1145c20/sub_6622610/sub_66232b0 [V rdis callers], but all upward chains dead-end at 0-static-caller functions [V rdis/xref]; the texture job constructor sub_4e05450 (sets vptr=0xF215838 at `0x4E05654  mov [rbx],r8`) has 16 static callers [V rdis callers this session], none is texgroup_load/texload/texload_task; texgroup_load's static callees (`0x54227AF call 0x18718D0`, `0x5421DEC call 0x5477A30`, `0x5421ED6 call 0x5475A30`, `0x5422869 call 0x5424000`, `0x5422C5D call 0x5424130` [V dis]) do not enter sub_12893d0's or sub_4e05450's caller trees. Everything else in the item is [V]-proven: sampler flag decode + cache (6ax), D3D12 backend texture-management chain, command-byte-14 producer sub_bc73770 [V r4], dispatcher [vptr+0xD0]->createTexture 0xe8143c0 [V live + dis], returned handle stored at [texture_obj+0x00] (`0xC296E26  mov [rdi],ax`, size 2) [V] with texture_obj = TexturePtr+0x58 [V], TexturePtr/ClientTexture sdk headers [V file read]. Atlas stitchers (L8a/L8b) remain out of scope (MIRROR_SKIP).

## TOOL REQUESTS

- None. Static analysis is exhausted: sub_4e05e50 (0 xrefs), sub_12893d0 (4 callers, all dead-end), sub_4e05450 (16 callers, none is texgroup_load), texgroup_load (5 callees, none enters the sub_4e05e50 tree). The vtable 0xF215838 (slot 1 = sub_4e05e50) is confirmed by rdis vt and matches the live capture vptr = 0x7FF6A8215838 [V live]. The bind texgroup_load -> sub_4e05e50 is runtime-only via vtable[1] indirect dispatch through trampoline [0xF99FFA0] = sub_eea6040 `jmp rax`, observed live [V live]. No helper scripts written; all instruction lines re-verified verbatim against a fresh rdis dis this session; live capture logs are read-only inputs; xref.py/rdis callers/fn/vt/imm/ripscan.py used for positive and negative findings.
