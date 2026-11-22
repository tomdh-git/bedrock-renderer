## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): `- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending`. Half 1 (sampler flag decode + sampler cache, 6ax) is closed [V] from prior units (docs/functions/e820500.md instruction-complete; src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h static_asserts). This unit covers half 2: texture/atlas management — the Minecraft-side pack->GPU chain into D3D12 createTexture and the texture/atlas handle write.

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; live captures below are orchestrator-run read-only reg dumps, cited as [V live] with file name.

Tags: [V] saw in disassembly (RVA cited, verbatim `0xRVA  instr` quoted from fresh rdis this session) / [V live] saw in an orchestrator live-capture reg dump (file cited) / [I] inferred from structure or BGFX_MAP.md / '-' = no instruction or string shows a meaning. Row rule: one annotated row per distinct offset; all read/store sites listed; sizes from the instruction; verbatim lines copied exactly from rdis output. No input data pasted as-is; no raw instruction dumps outside tables; no ellipsis shorthand; no catch-all rows.

## Already proven (do NOT redo — cited from r1-r45; every instruction below re-verified verbatim against fresh rdis this session)

- Half 1 — sampler flag decode + sampler cache (6ax): [V] docs/functions/e820500.md decodes 0xe820500 instruction-complete; key = bgfx HashMurmur2A over min(count,16) u32 flag words; map at heap+0x60; u16 free ring at heap+8; per-sampler D3D12_SAMPLER_DESC on the stack, ID3D12Device::CreateSampler (device [ctx+0x400], vtable +0xB0). Called from blit 0xe818bc0 and executor 0xe821120.
- Half 2a — D3D12 backend texture-management chain: [V] texture record table at this+0xBDE178 stride 0xB8 (BGFX_MAP.md lines 403/541/1524); createTexture 0xe8143c0 = vtable slot 26 (BGFX_MAP.md line 403), updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0, blitSetup 0xe819750; TextureD3D12::create body 0xe81bf30 called at 0xe81455b. Record fields per BGFX_MAP 6z: +0x00 resource ptr, +0x44 state, +0x9C/+0xA0 w/h, +0xAF/+0xB0 format, +0xB1 numMips.
- Static roots with 0 xrefs (rdis `fn`/`xref.py` report empty; not redone): texgroup_load 0x5421c90, createTexture 0xe8143c0 (only indirect [vptr+0xD0]), sub_4e05e50 0x4E05E50, sub_1289400 0x1289400. texgroup_load's only cache-bound call is 0x54227af `call 0x18718d0` [V r2]; texload 0x58a1310/texload_task 0x541bf00 have empty caller lists and were never decoded — the texgroup_load->texload->texload_task->0x18718D0 item-line chain is NOT statically supported. 0x18718D0 decoded [V r44]: texture-cache lookup/release (vtable 0xEFCA680, vptr[0] destructor dispatch via the same trampoline); it does not reach sub_4e05e50.

## Table 1 — D3D12 backend createTexture record (proven [V], r1)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| createTexture entry | 0xe8143c0 | - | E: `0xe8143c0  push rbp` | D3D12 backend slot-26 entry | [V] |
| texture record table base | this+0xBDE178 | 8 | R: `0xe8143f3  lea r12,[rcx+0xbde178]` | record table base = renderer ctx + 0xBDE178 | [V] |
| record stride | - | - | `0xe814427  imul r8,rbx,0xb8` | stride 0xB8 per record index | [V] |
| createTexture -> TextureD3D12::create | 0xe81455b | 5 | S: `0xe81455b  call 0xe81bf30` | backend record fill | [V] |
| backend create ret site (live) | 0xe814560 | 1 | - | `0xe814560  nop`; capture l8b_texcreate_record: sole caller ret=0xE814560; R8 = "Texture: 2815"/"Texture: 2799" runtime-created records | [V live] |

## Table 2 — who produces command byte 0x0E (createTexture): sub_bc73770 (r4, re-verified verbatim)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| sub_bc73770 entry | 0xbc73770 | - | E: `0xbc73770  push rbp` | createTexture command producer; 3 xrefs in | [V] |
| bimg container parse | 0xbc737c5 | 5 | S: `0xbc737c5  call 0xebd2160` | parses the bimg/TEX container into the local descriptor | [V] |
| handle allocation | 0xbc7384d | 5 | S: `0xbc7384d  call 0xbc79a60` | allocates the 16-bit bgfx texture handle | [V] |
| handle staged | [rbp+0x2e] | 2 | W: `0xbc73853  mov [rbp+0x2e],ax` | ax = handle index from sub_bc79a60 (0xFFFF = invalid) staged | [V] |
| command-buffer state ptr | [rdi+0x1cfd0c8] | 8 | R: `0xbc73aa3  mov rbx,[rdi+0x1cfd0c8]` | API-thread command/lock state object (BGFX_MAP.md 6ai) | [V] |
| **command byte 0x0E staged** | [rbp+0x2c] | 1 | W: `0xbc73aaa  mov byte ptr [rbp+0x2c],0xe` | byte 14 = createTexture command staged (BGFX_MAP.md 6et: byte 14 = createTexture) | [V] |
| write index | [rbx+0xdc5818] | 4 | R: `0xbc73aae  mov eax,[rbx+0xdc5818]` / W: `0xbc73ae2  mov [rbx+0xdc5818],ecx` | ring write index, bumped by 2 after the handle | [V] |
| command-buffer entry | [rbx+0xdc5820 + idx] | - | R: `0xbc73ab4  lea rcx,[rbx+rax]` / `0xbc73ab8  add rcx,0xdc5820` | entry address in the command buffer | [V] |
| cmd byte write (1 B) | [rbx+0xdc5820+idx] | 1 | R: `0xbc73abf  lea rdx,[rbp+0x2c]` / R: `0xbc73ac3  mov r8d,1` / S: `0xbc73ac9  call 0xebce390` | 1 byte (cmd 0x0E) written into the command buffer | [V] |
| handle write (2 B) | [rbx+0xdc5820+idx+1] | 2 | R: `0xbc73aeb  lea rdx,[rbp+0x2e]` / R: `0xbc73aef  mov r8d,2` / S: `0xbc73af5  call 0xebce390` | 2-byte handle written right after the cmd byte | [V] |
| handle out to caller | [rsi] | 2 | R: `0xbc73b70  movzx edi,word ptr [rbp+0x2e]` / W: `0xbc73b74  mov [rsi],di` | 16-bit handle returned to the createTexture API caller | [V] |

sub_bc73770 also parses descriptor fields (width/height/format at [rbp-0xC..]) and runs the staging at 0xBC73AA3..0xBC73AF5 above [V]. Capture bgfx_createtexture_producer.txt: RDX/R8 point at the 0x1C-byte create descriptor ("TEX" tag visible in the hex dump) on every hit [V live].

## Table 3 — CFG indirect-call trampoline [0xF99FFA0] = sub_eea6040 `jmp rax` (static, r37)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| trampoline entry | 0xeea6040 | 2 | E: `0xeea6040  jmp rax` | jumps to whatever rax holds | [V] |
| trampoline cell | [0xF99FFA0] | 8 | R (rdis annotation on every call site): `... call qword ptr [0xf99ffa0] ; [data_f99ffa0] = sub_eea6040` | .rdata initializer holds the trampoline address | [V] |
| trampoline has no writer | - | - | - | .rdata is read-only; .text store scan found 0 writers (r37); never rewritten | [V] |

## Table 4 — dispatcher: renderer-context vptr[slot 26] = createTexture (r4 orchestrator hint, re-verified verbatim)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| renderer-context ptr | [rdi+0x1ebf2d0] | 8 | R: `0xbc6a28f  mov rcx,[rdi+0x1ebf2d0]` | renderer-context-like object whose vtable is dispatched | [V] |
| vtable load | [rcx] | 8 | R: `0xbc6a2ae  mov rax,[rcx]` | vtable pointer loaded into rax | [V] |
| slot 26 function ptr | [rax+0xd0] | 8 | R: `0xbc6a2b1  mov rax,[rax+0xd0]` | vtable slot 0xD0/8 = 26 = createTexture loaded into rax | [V] |
| **createTexture issuance** | - | - | `0xbc6a2c2  call qword ptr [0xf99ffa0]` / `0xbc6a2c8  test rax,rax` | createTexture called via trampoline; rax = returned handle; this is the only static call site of 0xe8143c0 | [V] |
| dispatcher slot-26 name | slot 26 | - | - | BGFX_MAP.md line 403: `| 26 | 0xe8143c0 | createTexture |` | [I] |
| dispatcher sole caller (live) | capture createtexture_callers.txt | - | - | 1612 hits, one caller: `CALLER ret=0xBC6A2C8` on every hit = instruction right after `0xbc6a2c2  call qword ptr [0xf99ffa0]`; R8 = 0x1C create descriptor ("TEX" tag visible) [V live] | [V live] |

## Table 5 — MC-side entry: texture-group iterator sub_1289400 -> sub_4e05e50 via the trampoline

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| sub_1289400 entry | 0x1289400 | - | E: `0x1289400  rol byte ptr [r8],1` | iterates an array of texture objects, stride 0x18; 0 static xrefs in | [V] |
| walk end cursor | [rcx+8] | 8 | R: `0x1289409  mov r14,[rcx+8]` | end cursor of the entry list | [V] |
| entry refcount object | [r13+8] | 8 | R: `0x1289431  mov rcx,[r13+8]` | entry+0x8 = ptr to refcounted object | [V] |
| refcount bump | [rcx+8] | 4 | R: `0x128943a  mov eax,[rcx+8]` / R: `0x1289444  lea edx,[rax+1]` / W: `0x1289447  lock cmpxchg [rcx+8],edx` | bump-then-test refcount of the object | [V] |
| target object | [r13+0x10] | 8 | R: `0x128947d  mov rcx,[r13+0x10]` | entry+0x10 = target job/texture object whose vptr is dispatched | [V] |
| vptr load | [rcx] | 8 | R: `0x1289486  mov rax,[rcx]` | rax = object vptr | [V] |
| **vptr[1] load** | [rax+8] | 8 | R: `0x1289489  mov rax,[rax+8]` | rax = vptr[1] fed to the trampoline call | [V] |
| **indirect call to sub_4e05e50** | - | - | `0x1289490  call qword ptr [0xf99ffa0]` / `0x1289496  nop` | call site ends at ret=0x1289496 = the mc_root capture caller of sub_4e05e50 on all 32 samples [V live] | [V live] |
| vtable 0xF215838 slot 1 | vtable+0x008 | 8 | - | - | [V] |
| vtable bind (ctor) | - | 8 | `0x4e060bb  lea rax,[0xf215838]` / `0x4e060c2  mov [rcx],rax` (sub_4e060b0, vtable slot +0x000) | job-object vptr bound to 0xF215838 at construction | [V] |
| mc_root capture (live) | capture mc_root_4e05e50_callers.txt | - | - | 150 hits / 32 samples, ALL `CALLER ret=0x1289496`; RCX = heap objects carrying names "legends"/"tex"/"spear" plus dims/format fields [V live bytes] | [V live] |

So the trampoline target rax at `0x1289490  call qword ptr [0xf99ffa0]` is statically sub_4e05e50: rax = vptr[1] (`0x1289489  mov rax,[rax+8]`) and `rdis vt 0xF215838` shows `1 +0x008 sub_4e05e50 size 0x224 push rbp` (slot +0x000 = sub_4e060b0, slot +0x010 = non-code 0x0) [V]. The vtable bind is static too: sub_4e060b0 writes the object vptr [`0x4e060bb  lea rax,[0xf215838]` / `0x4e060c2  mov [rcx],rax`] [V]. Live confirmation: mc_root capture enters sub_4e05e50 exclusively via ret=0x1289496, all 32 samples [V live]. The capture at 0xEEA6040 suggested by r37 is unnecessary — static work was not exhausted; the vtable decode settles the indirect target.

Note: no static xrefs into sub_1289400 (0 xrefs in [V]) — texgroup_load reaches it at runtime (indirect/runtime bind, same class as every hop below it); the vtable-level target and the live entry are both resolved.

## Table 6 — Minecraft-side pack->GPU chain: sub_4e05e50 -> sub_bc41420 -> dragon entry -> wrapper -> cmd producer -> dispatcher -> createTexture -> handle store (proven below sub_4e05e50)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| sub_4e05e50 entry | 0x4e05e50 | - | E: `0x4e05e50  push rbp` | MC texture create entry; RCX = TexturePtr* a0, RDX = out handle ptr; 0 static xrefs | [V] |
| virtual call on object at +0x18 | [*(a0+0x18)+0x10] | 8 | R: `0x4e05e71  mov rax,[rcx+0x18]` / R: `0x4e05e82  mov rax,[rax+0x10]` / S: `0x4e05e86  call qword ptr [0xf99ffa0]` | vtable slot 2 of the object at a0+0x18 | [V] |
| shared_ptr ctrl block refcount | [a0+0x10]+8 | 4 | R: `0x4e05e95  mov eax,[rdx+8]` / W: `0x4e05ea8  lock cmpxchg [rdx+8],r8d` / W: `0x4e05ebd  lock inc dword ptr [rbx+8]` | refcounted control block (matches sdk TexturePtr.h: two shared_ptrs, 32B, ptr at +0x00/+0x10, ctrl block +0x8/+0x18) | [V] (sdk layout [V file read]) |
| renderer context | [a0+0xE0] | 8 | R: `0x4e05f61  mov r9,[rdi+0xe0]` | renderer context passed as r9 | [V] |
| texture object = arg+0x58 | arg+0x58 | 8 | - | `0x4e05f68  add rdi,0x58`: rdi = texture object / create descriptor passed to sub_bc41420 | [V] |
| **sub_bc41420 call** | sub_bc41420 | - | `0x4e05f77  call 0xbc41420` / `0x4e05f7c  nop` | RCX = texture object+0x58 (create descriptor); ret site 0x4E05F7C | [V] |
| dragon sub_bc41420 -> dragon entry 0xc296b50 | 0xbc41b39 | 5 | `0xbc41b39  call 0xc296b50` / `0xbc41b3e  movzx eax,byte ptr [rbp+0x188]` | sub_bc41420 calls dragon entry with the create descriptor; ret=0xBC41B3E [V live dragon_texture_caller_bc41420 + dragon_texture_entry_c296b50] | [V live] |
| wrapper 0xbc73bf0 | 0xbc73bf0 | - | E: `0xbc73bf0  push r15` | bgfx::createTexture* wrapper; capture bgfx_texture_wrapper_bc73bf0: `CALLER ret=0xC296D7E` inside dragon entry 0xc296b50 [V live r4] | [V live] |
| cmd-0x0E producer | sub_bc73770 | - | Table 2 | wrapper -> sub_bc73770 writes cmd byte 0x0E + handle into the command buffer | [V] |
| handle store into texture object | [texture_obj+0x00] | 2 | W: `0xc296e26  mov [rdi],ax` / `0xc296e1a  call 0xbc74120` (ax) / `0xc296e22  mov ax,0xffff` (invalid-handle fallback) | 16-bit bgfx texture handle stored at [texture_obj+0x00]; rdi = texture_obj = arg+0x58 | [V] |
| descriptor copy | [texture_obj+0x8] | 16 | R: `0xc296e2d  movups xmm0,[r12]` / W: `0xc296e32  movups [rdi+8],xmm0` | 0x1C-byte create descriptor copied to texture_obj+0x8 | [V] |

Capture chain index [V live]:
- dragon_texture_caller_bc41420.txt: capture at 0xBC41420, `CALLER ret=0x4E05F7C` (right after `0x4e05f77  call 0xbc41420`); RCX = 0x1C create descriptor (flags 0x80000000, size 0x1C, tag "tex", width/height fields) [V live bytes].
- dragon_texture_entry_c296b50.txt: capture at 0xC296B50, `CALLER ret=0xBC41B3E` [V live]; RCX/RDX/R8/R9 carry descriptor fields.
- createtexture_callers.txt: capture at 0xE8143C0, 1612 hits, one caller ret=0xBC6A2C8 [V live] (Table 4).
- l8b_texcreate_record.txt: capture at 0xE81BF30, `CALLER ret=0xE814560`; R8 = "Texture: 2815"/"Texture: 2799".. name strings (runtime-created texture records) [V live].

End-to-end pack->GPU chain: MC texture object (mce::TexturePtr-family object, shared_ptr ctrl blocks at +0x10/+0x18 per sdk TexturePtr.h, name strings "legends"/"tex"/"spear" in the captured RCX heaps [V live]) --sub_4e05e50(TexturePtr*)--> sub_bc41420 (`0x4e05f77  call 0xbc41420`, ret site 0x4E05F7C [V live]) --> dragon entry 0xc296b50 (`0xbc41b39  call 0xc296b50`) --> wrapper 0xbc73bf0 --> sub_bc73770 writes bgfx command byte 0x0E (`0xbc73aaa  mov byte ptr [rbp+0x2c],0xe`) + 2-byte handle into the command buffer at [ctx+0x1cfd0c8]+0xdc5820 [V Table 2] --> dispatcher `0xbc6a28f  mov rcx,[rdi+0x1ebf2d0]` / `0xbc6a2ae  mov rax,[rcx]` / `0xbc6a2b1  mov rax,[rax+0xd0]` / `0xbc6a2c2  call qword ptr [0xf99ffa0]` (slot 26 = createTexture 0xe8143c0 per BGFX_MAP.md line 403; sole caller ret=0xBC6A2C8 [V live]) --> createTexture body (`0xe81455b  call 0xe81bf30`, ret site 0xE814560 [V live]) --> D3D12 texture record table this+0xBDE178 stride 0xB8 --> returned handle stored back at [texture_obj+0x00] (`0xc296e26  mov [rdi],ax` [V]).

## Interpretations ([I], not row claims)

- slot 26 = 0xe8143c0 createTexture comes from BGFX_MAP.md line 403 and the vtable-slot layout (line 683 jump-forward stub 0xe83d400 -> 0xe8143c0); the dispatcher dis shows the slot load directly (`0xbc6a2b1  mov rax,[rax+0xd0]`) [V], the name is [I BGFX_MAP.md].
- byte 14 = createTexture in the bgfx command stream (BGFX_MAP.md lines 1476-1478: handler 0xbc69487 requires magic 0x00584554 'TEX', parses the 0x18-byte TextureCreate header, calls renderer vtable slot 26; returned pointer stored in the per-handle table ctx+0x1e55ab8 element+0x10) — [V code / [I] meaning] per BGFX_MAP.md; matches sub_bc73770 staging cmd byte 0x0E with the "TEX" descriptor tag [V live].
- mce::TexturePtr is 32B (static_assert in src/sdk/mc/deps/minecraft_renderer/renderer/TexturePtr.h [V file read]): mClientTexture shared_ptr at +0x00 (ptr +0x00, ctrl block +0x8), mResourceLocationPtr at +0x10 (ptr +0x10, ctrl block +0x18). sub_4e05e50's refcount code (`lock cmpxchg [rdx+8]`, `lock inc [rbx+8]`) matches that layout [V].
- Sampler half (6ax) [V] from prior units; atlas stitchers L8a/L8b remain separate open units (oc_U-EL8a/oc_U-EL8b), not this unit. MIRROR_SKIP applies to atlas stitchers.

## What I tried that failed (new angles, not redone)

- xref.py callers 0xe8143c0 / 0x4E05E50 / 0x1289400: EMPTY for all three (not redone); createTexture reachable only via indirect [vptr+0xD0] — solved via the live capture instead (sole caller ret=0xBC6A2C8 [V live]).
- texload 0x58a1310 / texload_task 0x541bf00: xref.py callers EMPTY; never decoded; texgroup_load does not call them (its only cache-bound call is 0x54227af -> 0x18718d0 [V r2]). Not part of the proven createTexture path.
- [0xF99FFA0] writer search: none — read-only .rdata initializer = sub_eea6040 (r37; verbatim `... call qword ptr [0xf99ffa0] ; [data_f99ffa0] = sub_eea6040`).
- eea6040 rax capture (r37's suggested step): NOT requested / not needed — the indirect target is resolved statically: vtable 0xF215838 slot +0x008 = sub_4e05e50 [V rdis vt] + vtable bind sub_4e060b0 [`0x4e060bb  lea rax,[0xf215838]` / `0x4e060c2  mov [rcx],rax`] [V] + mc_root capture all 32 samples ret=0x1289496 [V live]. No livemem call made.
- texgroup_load -> sub_1289400 static link: absent (0 static xrefs into sub_1289400 [V rdis fn]); runtime bind only — documented in Table 5, not a blocker for the vtable-resolved entry hop.

## CLOSES?

YES — every pending part of L7e texture/atlas management (this unit's half 2) is proven [V] or [V live]:
1. D3D12 backend chain: [V] (table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0 = slot 26 per BGFX_MAP.md line 403; TextureD3D12::create 0xe81bf30; ret site 0xe814560 [V live]).
2. Command byte 0x0E producer: [V] sub_bc73770 stages `0xbc73aaa  mov byte ptr [rbp+0x2c],0xe`, handle alloc `0xbc7384d  call 0xbc79a60` / `0xbc73853  mov [rbp+0x2e],ax`, cmd+handle writes into [rbx+0xdc5820+idx] [V Table 2]; descriptor "TEX" tag [V live bgfx_createtexture_producer].
3. Dispatcher issuance: [V] `0xbc6a2b1  mov rax,[rax+0xd0]` (slot 26) / `0xbc6a2c2  call qword ptr [0xf99ffa0]`; sole static caller of createTexture; capture sole caller ret=0xBC6A2C8 [V live].
4. MC-side chain below sub_4e05e50: [V dis + V live] sub_4e05e50 (TexturePtr* entry, 0 static xrefs) -> sub_bc41420 (`0x4e05f77  call 0xbc41420`, ret=0x4E05F7C [V live]) -> dragon entry 0xc296b50 (`0xbc41b39  call 0xc296b50`, ret=0xBC41B3E [V live]) -> wrapper 0xbc73bf0 (ret=0xC296D7E inside 0xc296b50 [V live]) -> sub_bc73770 -> ... -> createTexture.
5. Trampoline target resolved: rax = vptr[1] = sub_4e05e50 via vtable 0xF215838 slot +0x008 [V] + ctor bind [V] + mc_root 32/32 samples ret=0x1289496 [V live] — the r37 blocking fact is closed statically, no capture needed.
6. Handle + TexturePtr: returned 16-bit handle stored at [texture_obj+0x00] (`0xc296e26  mov [rdi],ax` [V]); texture_obj = arg+0x58 (`0x4e05f68  add rdi,0x58` [V]); sub_4e05e50 arg = TexturePtr* [V live + sdk TexturePtr.h static_assert sizeof==32].

Caveat (documented, not a blocker for the vtable-resolved entry hop): texgroup_load(0x5421c90) -> sub_1289400 has no static link (0 xrefs into sub_1289400 [V]); reached at runtime. The live mc_root capture proves sub_1289400 is executing and calling sub_4e05e50 for captured texture objects (all 32 samples ret=0x1289496 [V live]).

## TOOL REQUESTS

None. No helper scripts written; no temporary files left behind.

## Verification

- `python tools/sigs/verify_oc.py docs/progress/oc_U-EL7e.md` — mismatch=0, no-such-instr=0 required (all quoted instruction lines re-verified against fresh rdis this session; vt/capture citations are tool evidence, not instruction claims).
- `python tools/delegate.py check docs/progress/oc_U-EL7e.md` — must exit 0; then set line 2 after `## NEXT` to DONE.
