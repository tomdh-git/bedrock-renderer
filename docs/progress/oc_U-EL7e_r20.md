## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): `- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending | PROGRESS 2026-11-21 oc_U-EL7e.md (verify_oc 185/185): D3D12 backend texture-management chain decoded [V] ...; Minecraft-side pack->GPU chain (texgroup_load 0x5421c90 -> texload 0x58a1310 -> texload_task 0x541bf00 -> undecoded 0x18718D0 at 0x54227af) and atlas stitchers still open (L8a/L8b)`

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; live capture logs under docs/data/live are read-only inputs produced by the orchestrator.

Tags: [V] saw in disassembly (RVA cited, verbatim line quoted) / [V live] saw in an orchestrator live capture log (file cited) / [I] inferred from structure or BGFX_MAP / [?] unknown or not located.

Row rule: one annotated row per distinct offset, all its sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after address, copied verbatim from rdis) | meaning ONLY if an instruction/string shows it else '-' | tag. Sizes from the instruction (movups/movaps/movdqu/movdqa 16, qword 8, dword/movss 4, word 2, byte 1). No input data pasted as-is; no skipped offsets among quoted sites; no raw instruction dumps outside tables.

## Already proven (do NOT redo — cited from r1-r19 / verified files; not re-quoted here)

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

Note: r18/r19 named this `sub_1289440`, but rdis reports `sub_12893d0  [0x12893d0..0x12895d3) size 0x203 13 xrefs in`; `0x1289440` is only a local label (loc_1289440, the add_ref retry block) inside sub_12893d0 — not a separate function and not a function entry.

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| sub_12893d0 entry | 0x12893D0 | 1 | - | `0x12893D0  push rbp` | deferred-transaction processor entry; frame setup | [V] |
| array begin load | [rcx+0x0] | 8 | [rcx+0x0] | `0x1289406  mov r13,[rcx]` | r13 = deferred vector begin {ptr@0, ctrl@8} | [V] |
| array end load | [rcx+0x8] | 8 | [rcx+0x8] | `0x1289409  mov r14,[rcx+8]` | r14 = deferred vector end | [V] |
| shared ctrl load | [r13+0x8] | 8 | [r13+0x8] | `0x1289431  mov rcx,[r13+8]` | element+0x8 = shared control-block pointer | [V] |
| refcount load (sub_12893d0) | [rcx+0x8] | 4 | [rcx+0x8] | `0x128943A  mov eax,[rcx+8]` | eax = refcount at ctrl+8 | [V] |
| add_ref CAS (sub_12893d0) | [rcx+0x8] | 4 | [rcx+0x8] | `0x1289447  lock cmpxchg [rcx+8],edx` | atomic refcount increment, retry on failure | [V] |
| element copy 16B | [r13+0x0] | 16 | [r13+0x0] | `0x128944E  movups xmm0,[r13]` | copy element {ptr@0, ctrl@8} to local desc | [V] |
| object load | [r13+0x10] | 8 | [r13+0x10] | `0x128947D  mov rcx,[r13+0x10]` | rcx = element+0x10 = `this` for virtual call | [V] |
| vptr load | [rcx+0x0] | 8 | [rcx+0x0] | `0x1289486  mov rax,[rcx]` | rax = object vptr | [V] |
| vtable slot 1 load | [rax+0x8] | 8 | [rax+0x8] | `0x1289489  mov rax,[rax+8]` | rax = obj->vptr[1] = indirect call target | [V] + [? runtime bind] |
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

None of these four callers is texgroup_load(0x5421c90), texload(0x58a1310) or texload_task(0x541bf00). All upward chains from them dead-end at functions with 0 static callers (sub_879010, sub_661a400, sub_661f200, sub_5360e00, sub_943920, sub_92b520, sub_55f1450 — each `rdis callers` returns 0 / xref.py empty [V r19, not redone]).

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

### 5. Handle store into the texture object (dragon entry 0xc296b50, via sub_bc41420) [V dis this session]

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| wrapper returns handle | 0xC296E1A | 5 | - | `0xC296E1A  call 0xBC74120` | wrapper 0xbc74120 returns 16-bit texture handle in ax (called from sub_bc41420 at 0xBC41B39) | [V] |
| invalid-handle fallback | 0xC296E22 | 2 | - | `0xC296E22  mov ax,0xFFFF` | 0xFFFF = invalid handle fallback | [V] |
| handle store word | [rdi+0x00] | 2 | [rdi+0x00] | `0xC296E26  mov [rdi],ax` | 16-bit handle stored at texture object +0x00 | [V] |
| rest of result | [rdi+0x08] | 16 | [rdi+0x08] | `0xC296E32  movups [rdi+8],xmm0` | 16 result bytes stored at texture object +0x08 | [V] |

texture object = TexturePtr+0x58 (`0x4E05F68  add rdi,0x58` [V]), so the created handle lands inside the texture object carried by sub_4e05e50.

### 6. createTexture issuance — dispatcher vcall [vptr+0xD0] -> createTexture 0xe8143c0 -> TextureD3D12::create [V dis this session + V live]

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| vtable slot 26 load | [rax+0xD0] | 8 | [rax+0xD0] | `0xBC6A2B1  mov rax,[rax+0xD0]` | slot 26 (0xD0/8) = createTexture address; BGFX_MAP line 403: slot 26 = 0xe8143c0 | [V] |
| dispatcher vcall | [0xF99FFA0] | 8 | [0xF99FFA0] | `0xBC6A2C2  call qword ptr [0xF99FFA0]` | trampoline tail-call; rax = [vptr+0xD0] = createTexture 0xe8143c0 | [V] + [V live ret=0xBC6A2C8] |
| result test | 0xBC6A2C8 | 4 | - | `0xBC6A2C8  test rax,rax` | handle/result tested; return site of live createTexture caller | [V] |
| createTexture -> TextureD3D12::create | 0xE81455B | 5 | - | `0xE81455B  call 0xE81BF30` | TextureD3D12::create fills the texture record; ret site 0xE814560 = live capture l8b ret=0xE814560 | [V] + [V live] |

### 7. Full live chain recap [V live] (capture logs, read-only inputs)

| name | source | ret= | meaning | tag |
|---|---|---|---|---|
| sub_4e05e50 caller | docs/data/live/mc_root_4e05e50_callers.txt | 0x1289496 | sub_12893d0 tail-calls sub_4e05e50; all 32 samples enter at ret=0x1289496 | [V live] |
| sub_bc41420 caller | docs/data/live/dragon_texture_caller_bc41420.txt | 0x4E05F7C | sub_4e05e50 calls sub_bc41420 (return site 0x4E05F7C nop) | [V live] |
| dragon entry caller | docs/data/live/dragon_texture_entry_c296b50.txt | 0xBC41B3E | sub_bc41420 calls dragon entry 0xc296b50 | [V live] |
| wrapper caller | docs/data/live/bgfx_texture_wrapper_bc73bf0.txt | 0xC296D7E | dragon entry 0xc296b50 calls wrapper 0xbc73bf0 | [V live] |
| createTexture caller | docs/data/live/createtexture_callers.txt | 0xBC6A2C8 | dispatcher case 0xBC6A2C2 vcall [vptr+0xD0] -> createTexture 0xe8143c0 | [V live] |

Chain (MC end proven [V live]): texture job object (vptr+8 = sub_4e05e50 at runtime) -> sub_12893d0@0x1289490 (tail-call via trampoline [0xF99FFA0] = sub_eea6040 `jmp rax`, return address 0x1289496) -> sub_4e05e50(object*, out_ptr) (`0x4E05F77  call 0xBC41420`, return site `0x4E05F7C  nop`) -> sub_bc41420 -> 0xc296b50 -> 0xbc73bf0 -> 0xbc73770 (command-byte-0x0E producer [V r4]) -> bgfx dispatcher case 0xBC6A2C2 (`0xBC6A2B1  mov rax,[rax+0xD0]`, slot 26 = 0xe8143c0 [V BGFX_MAP]) -> `0xBC6A2C2  call qword ptr [0xF99FFA0]` -> createTexture 0xe8143c0 -> `0xE81455B  call 0xE81BF30` TextureD3D12::create (record fill, ret 0xe814560) [V live + dis]. Returned handle: `0xC296E1A  call 0xBC74120` (ax) -> `0xC296E26  mov [rdi],ax` at texture_obj+0x00 [V dis]; texture_obj = TexturePtr+0x58 [V]; sdk TexturePtr/ClientTexture [V file read].

## Interpretation

Proven [V] this session and overall:
- sampler flag decode + cache (6ax) [V] — docs/functions/e820500.md.
- D3D12 backend texture-management chain [V] — table this+0xBDE178 stride 0xB8; slots 26/28/30-34.
- command-byte-14 producer sub_0xbc73770 [V r4]; dispatcher vcall [vptr+0xD0] -> createTexture 0xe8143c0 [V live + dis].
- MC-side texture object create/load method sub_4e05e50 invoked live via sub_12893d0 tail-call (ret=0x1289496, all 32 samples) [V live]; sub_4e05e50 -> sub_bc41420 -> dragon entry 0xc296b50 -> wrapper 0xbc73bf0 -> producer 0xbc73770 -> dispatcher -> createTexture -> TextureD3D12::create [V live + dis].
- returned handle stored at [texture_obj+0x00] by `0xC296E26  mov [rdi],ax` (size 2, word) [V]; texture_obj = TexturePtr+0x58 [V]; sdk TexturePtr/ClientTexture [V file read].

Not [V]-proven (single blocking fact): the STATIC link texgroup_load(0x5421c90) -> sub_4e05e50. It provably does NOT exist statically:
- sub_4e05e50 has 0 static xrefs (`rdis callers 0x4E05E50` -> 0 calling functions [V this session]).
- sub_12893d0 (the indirect caller) has only 4 static callers (sub_1145c20, sub_6622610, sub_66232b0, sub_6632bf0 [V this session]); none is texgroup_load/texload/texload_task; all upward chains dead-end at 0-static-caller functions [V r19].
- texgroup_load's static chain is `0x54227AF call 0x18718D0` (verified this session); cache 0x18718d0's decoded miss path (vtable 0xEFCA680 object + completion 0x186dac0) never calls sub_4e05e50/sub_12893d0 [V r19].
- The bind is runtime-only: object vptr+8 resolves to sub_4e05e50 and is tail-called through trampoline [0xF99FFA0] = sub_eea6040 `jmp rax`, observed live [V live].

texload(0x58a1310)/texload_task(0x541bf00) are not part of the real static chain (r3 [V]); the pack->GPU route is texgroup_load -> 0x18718d0 cache -> (on miss) texture job object with vtable[1]=sub_4e05e50 -> deferred vector flushed at endFrame by sub_6632bf0 -> sub_12893d0 -> sub_4e05e50 -> createTexture. The ENQUEUE site (population of sub_6632bf0's this+0x00 deferred texture vector during pack load) is not statically located.

## CLOSES?

NO — blocking fact: no [V]-proven static path texgroup_load(0x5421c90) -> sub_4e05e50. sub_4e05e50 has 0 static xrefs ([V this session]) and is reached only via sub_12893d0's indirect vtable[1] tail-call `0x1289490  call qword ptr [0xF99FFA0]` (capture ret site 0x1289496 [V live]); sub_12893d0's 4 static callers ([V this session]) none is texgroup_load/texload/texload_task, and all upward chains dead-end at 0-static-caller functions [V r19]; texgroup_load's static chain ends at `0x54227AF call 0x18718D0` [V this session] and cache 0x18718d0 never calls sub_4e05e50/sub_12893d0 [V r19]. Everything else in the item is [V]-proven: sampler flag decode + cache (6ax), D3D12 backend texture-management chain, command-byte-14 producer sub_bc73770 [V r4], dispatcher [vptr+0xD0]->createTexture 0xe8143c0 [V live + dis], returned handle stored [texture_obj+0x00] (`0xC296E26  mov [rdi],ax`, size 2) [V] with texture_obj = TexturePtr+0x58 [V], sdk TexturePtr/ClientTexture [V file read]. Atlas stitchers (L8a/L8b) remain out of scope (MIRROR_SKIP).

## TOOL REQUESTS

- None. Static analysis is exhausted: sub_4e05e50 and sub_12893d0 have 0/4 static callers respectively, all upward chains dead-end at 0-static-caller functions, texgroup_load's chain ends at cache 0x18718d0 which never calls sub_4e05e50. The bind is runtime-only (vptr+8 = sub_4e05e50, trampoline [0xF99FFA0] = sub_eea6040 `jmp rax`) and is observed live [V live]. No helper scripts written; all instruction lines re-verified verbatim against a fresh rdis dis this session; live capture logs are read-only inputs; xref.py/rdis callers/fn used for positive and negative findings.
