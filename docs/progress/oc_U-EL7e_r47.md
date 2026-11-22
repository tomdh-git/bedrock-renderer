## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): `- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending`. Half 1 (sampler flag decode + sampler cache, 6ax) closed [V] in prior units (docs/functions/e820500.md instruction-complete; src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h static_asserts). This unit covers half 2: texture/atlas management — the Minecraft-side pack->GPU chain into D3D12 createTexture and the texture handle write.

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; live captures below are orchestrator-run read-only reg dumps, cited as [V live] with file name.

Tags: [V] saw in disassembly (RVA cited, verbatim `0xRVA  instr` quoted from fresh rdis this session) / [V live] saw in an orchestrator live-capture reg dump (file cited) / [I] inferred from structure or BGFX_MAP.md / '-' = no instruction or string shows a meaning. Row rule: one annotated row per distinct offset; all read/store sites listed; sizes from the instruction; verbatim lines copied exactly from rdis output. No input data pasted as-is; no raw instruction dumps outside tables; no ellipsis shorthand; no catch-all rows.

## Already proven (re-verified verbatim against fresh rdis this session; prior r1-r45 conclusions carried, not redone)

- Half 1 — sampler flag decode + sampler cache (6ax): [V] docs/functions/e820500.md decodes 0xe820500 instruction-complete; key = bgfx HashMurmur2A over min(count,16) u32 flag words; map at heap+0x60; u16 free ring at heap+8; per-sampler D3D12_SAMPLER_DESC on the stack, ID3D12Device::CreateSampler (device [ctx+0x400], vtable +0xB0). Called from blit 0xe818bc0 and executor 0xe821120.
- Half 2a — D3D12 backend texture-management chain: [V] texture record table at this+0xBDE178 stride 0xB8 (BGFX_MAP.md lines 403/541/1524); createTexture 0xe8143c0 = vtable slot 26 (BGFX_MAP.md line 403), updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0, blitSetup 0xe819750; TextureD3D12::create body 0xe81bf30 called at 0xe81455b. Record fields per BGFX_MAP 6z: +0x00 resource ptr, +0x44 state, +0x9C/+0xA0 w/h, +0xAF/+0xB0 format, +0xB1 numMips.
- Static roots with 0 xrefs (rdis `fn`/`xref.py` report empty this session): texgroup_load 0x5421c90, texload 0x58a1310, texload_task 0x541bf00, createTexture 0xe8143c0, sub_4e05e50 0x4E05E50, sub_1289400 0x1289400 (headers: `sub_1289400 [0x1289400..0x128b400) size 0x2000 0 xrefs in`, `sub_4e05e50 [0x4e05e50..0x4e07e50) size 0x2000 0 xrefs in`). texgroup_load's only cache-bound call is 0x54227af `call 0x18718d0` [V r2]; 0x18718D0 decoded [V r44]: texture-cache lookup/release (vtable 0xEFCA680); it does not reach sub_4e05e50. The item-line chain texgroup_load->texload->texload_task->0x18718D0 is NOT statically supported and is not the proven createTexture path.

## Table 1 — D3D12 backend createTexture record (proven [V], r1; verbatim re-checked this session)

| name | offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| createTexture entry | 0xe8143c0 | - | E: `0xe8143c0  push rbp` | D3D12 backend slot-26 entry | [V] |
| texture record table base | this+0xBDE178 | 8 | R: `0xe8143f3  lea r12,[rcx+0xBDE178]` | record table base = renderer ctx + 0xBDE178 | [V] |
| record stride | 0xe814427 | - | `0xe814427  imul r8,rbx,0xB8` | stride 0xB8 per record index | [V] |
| createTexture -> TextureD3D12::create | 0xe81455b | 5 | S: `0xe81455b  call 0xe81bf30` | backend record fill | [V] |
| backend create ret site (live) | 0xe814560 | 1 | - | `0xe814560  nop`; capture l8b_texcreate_record: sole caller ret=0xE814560; R8 = "Texture: 2815"/"Texture: 2799" runtime-created records | [V live] |

## Table 2 — who produces command byte 0x0E (createTexture): sub_bc73770 (r4, re-verified verbatim this session)

| name | offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| sub_bc73770 entry | 0xbc73770 | - | E: `0xbc73770  push rbp` | createTexture command producer; 3 xrefs in | [V] |
| bimg container parse | 0xbc737c5 | 5 | S: `0xbc737c5  call 0xebd2160` | parses the bimg/TEX container into the local descriptor | [V] |
| handle allocation | 0xbc7384d | 5 | S: `0xbc7384d  call 0xbc79a60` | allocates the 16-bit bgfx texture handle | [V] |
| handle staged | [rbp+0x2e] | 2 | W: `0xbc73853  mov [rbp+0x2e],ax` | ax = handle index from sub_bc79a60 (0xFFFF = invalid) staged | [V] |
| command-buffer state ptr | [rdi+0x1cfd0c8] | 8 | R: `0xbc73aa3  mov rbx,[rdi+0x1cfd0c8]` | API-thread command/lock state object (BGFX_MAP.md 6ai) | [V] |
| command byte 0x0E staged | [rbp+0x2c] | 1 | W: `0xbc73aaa  mov byte ptr [rbp+0x2c],0xe` | byte 14 = createTexture command staged (BGFX_MAP.md 6et: byte 14 = createTexture) | [V] |
| ring write index | [rbx+0xdc5818] | 4 | R: `0xbc73aae  mov eax,[rbx+0xdc5818]` / W: `0xbc73ae2  mov [rbx+0xdc5818],ecx` | ring write index, bumped by 2 after the handle | [V] |
| command-buffer entry | [rbx+0xdc5820+idx] | - | R: `0xbc73ab4  lea rcx,[rbx+rax]` / R: `0xbc73ab8  add rcx,0xdc5820` / R: `0xbc73abf  lea rdx,[rbp+0x2c]` / R: `0xbc73ac3  mov r8d,1` / S: `0xbc73ac9  call 0xebce390` / R: `0xbc73aeb  lea rdx,[rbp+0x2e]` / R: `0xbc73aef  mov r8d,2` / S: `0xbc73af5  call 0xebce390` | cmd byte (1 B) then handle (2 B) written into the command buffer entry via helper 0xebce390 | [V] |
| handle out to caller | [rsi] | 2 | R: `0xbc73b70  movzx edi,word ptr [rbp+0x2e]` / W: `0xbc73b74  mov [rsi],di` | 16-bit handle returned to the createTexture API caller | [V] |

sub_bc73770 also runs the descriptor staging at 0xBC73AA3..0xBC73AF5 above [V Table 2]; descriptor carries the "TEX" tag [V live bgfx_createtexture_producer.txt RDX dump: `14 00 54 45 58 00 ...`].

## Table 3 — CFG indirect-call trampoline [0xF99FFA0] = sub_eea6040 `jmp rax` (static, r37; verbatim re-checked this session)

| name | offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| trampoline entry | 0xeea6040 | 2 | E: `0xeea6040  jmp rax` | jumps to whatever rax holds | [V] |
| trampoline cell read | [0xF99FFA0] | 8 | R (rdis annotation on every `call qword ptr [0xF99FFA0]` site): `[data_f99ffa0] = sub_eea6040` | .rdata initializer holds the trampoline address | [V] |
| trampoline cell value | 0xF99FFA0 | 8 | - | PE .rdata read-only initializer = 0x14EEA6040 = ImageBase 0x140000000 + sub_eea6040 | [V] |
| trampoline cell writer | 0xF99FFA0 | 8 | - | .text store scan for [0xF99FFA0] = 0 hits (r37); .rdata section flags 0x40000040 = read-only; never rewritten; no writer anywhere (_f99ffa0_refs.txt lists only reads/calls, 1088051 xrefs) | [V] |
| indirect target held in rax | [rax+8] | 8 | R: `0x1289489  mov rax,[rax+8]` | rax = object vptr[1], the value tail-called through the trampoline | [V] |
| vtable decode | vtable+0x008 | 8 | - | `rdis vt 0xF215838`: `1 +0x008 sub_4e05e50 size 0x224 push rbp` | vptr[1] = sub_4e05e50 | [V] |
| vtable bind (ctor) | 0x4e060bb | 8 | `0x4e060bb  lea rax,[0xF215838]` / W: `0x4e060c2  mov [rcx],rax` (sub_4e060b0, vtable slot +0x000) | job-object vptr bound to 0xF215838 at construction | [V] |

## Table 4 — dispatcher: renderer-context vptr[slot 26] = createTexture (r4 orchestrator hint, re-verified verbatim this session)

| name | offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| renderer-context ptr | [rdi+0x1ebf2d0] | 8 | R: `0xbc6a28f  mov rcx,[rdi+0x1ebf2d0]` | renderer-context-like object whose vtable is dispatched | [V] |
| vtable load | [rcx] | 8 | R: `0xbc6a2ae  mov rax,[rcx]` | vtable pointer loaded into rax | [V] |
| slot 26 function ptr | [rax+0xd0] | 8 | R: `0xbc6a2b1  mov rax,[rax+0xd0]` | vtable slot 0xD0/8 = 26 = createTexture loaded into rax | [V] |
| createTexture issuance | 0xbc6a2c2 | - | `0xbc6a2c2  call qword ptr [0xf99ffa0]` / `0xbc6a2c8  test rax,rax` | createTexture called via trampoline; rax = returned handle; this is the only static call site of 0xe8143c0 | [V] |
| dispatcher slot-26 name | vtable slot 26 | - | - | BGFX_MAP.md line 403: `| 26 | 0xe8143c0 | createTexture |` | [I] |
| dispatcher sole caller (live) | capture createtexture_callers.txt | - | - | 1612 hits, one caller: `CALLER ret=0xBC6A2C8` on every hit = instruction right after `0xbc6a2c2  call qword ptr [0xf99ffa0]`; R8 = 0x1C create descriptor ("TEX" tag visible at +0x18) [V live] | [V live] |

## Table 5 — MC-side entry: sub_1289400, the indirect caller of sub_4e05e50 (decoded this session; 0 static xrefs in)

| name | offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| sub_1289400 entry | 0x1289400 | - | E: `0x1289400  rol byte ptr [r8],1` | iterates an array of texture objects, stride 0x18 | [V] |
| list cursor + refcount | [rcx+8] | 8/4 | R: `0x1289409  mov r14,[rcx+8]` / R: `0x1289431  mov rcx,[r13+8]` / R: `0x128943a  mov eax,[rcx+8]` / R: `0x1289444  lea edx,[rax+1]` / W: `0x1289447  lock cmpxchg [rcx+8],edx` | [rcx+8] = end cursor of the entry list, then entry+0x8 = refcounted object; bump-then-test its refcount | [V] |
| target object | [r13+0x10] | 8 | R: `0x128947d  mov rcx,[r13+0x10]` | entry+0x10 = target job/texture object whose vptr is dispatched | [V] |
| vptr load | [rcx] | 8 | R: `0x1289486  mov rax,[rcx]` | rax = object vptr | [V] |
| vptr[1] load = indirect callee | [rax+8] | 8 | R: `0x1289489  mov rax,[rax+8]` | rax = vptr[1] fed to the trampoline call | [V] |
| indirect call to sub_4e05e50 | 0x1289490 | - | `0x1289490  call qword ptr [0xF99FFA0]` / `0x1289496  nop` | call site ends at ret=0x1289496 = the mc_root capture caller of sub_4e05e50 on all 32 samples [V live] | [V live] |
| indirect caller name | sub_1289400 | - | - | sub_1289400 is the indirect caller of sub_4e05e50 (ret site 0x1289496); mc_root_4e05e50_callers.txt line 3: 150 hits / 32 samples, all `CALLER ret=0x1289496`; RCX = heap objects carrying names "legends"/"tex"/"spear" plus dims/format fields [V live bytes] | [V live] |

## Table 6 — Minecraft-side pack->GPU chain: sub_4e05e50 -> sub_bc41420 -> dragon entry -> wrapper -> cmd producer -> dispatcher -> createTexture -> handle store (proven below sub_4e05e50)

| name | offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| sub_4e05e50 entry | 0x4e05e50 | - | E: `0x4e05e50  push rbp` | MC texture create entry; RCX = TexturePtr* a0, RDX = out handle ptr; 0 static xrefs | [V] |
| virtual call on object at +0x18 | [*(a0+0x18)+0x10] | 8 | R: `0x4e05e71  mov rax,[rcx+0x18]` / R: `0x4e05e82  mov rax,[rax+0x10]` / S: `0x4e05e86  call qword ptr [0xF99FFA0]` | vtable slot 2 of the object at a0+0x18 | [V] |
| shared_ptr ctrl block refcount | [a0+0x10]+8 | 4 | R: `0x4e05e95  mov eax,[rdx+8]` / W: `0x4e05ea8  lock cmpxchg [rdx+8],r8d` / W: `0x4e05ebd  lock inc dword ptr [rbx+8]` | refcounted control block (matches sdk TexturePtr.h: two shared_ptrs, 32B, ptr at +0x00/+0x10, ctrl block +0x8/+0x18) | [V] (sdk layout [V file read]) |
| renderer context | [a0+0xE0] | 8 | R: `0x4e05f61  mov r9,[rdi+0xe0]` | renderer context passed as r9 | [V] |
| texture object = arg+0x58 | arg+0x58 | 8 | - | `0x4e05f68  add rdi,0x58`: rdi = texture object / create descriptor passed to sub_bc41420 | [V] |
| sub_bc41420 call | 0x4e05f77 | - | `0x4e05f77  call 0xbc41420` / `0x4e05f7c  nop` | RCX = texture object+0x58 (create descriptor); ret site 0x4E05F7C | [V] |
| dragon entry call | 0xbc41b39 | 5 | `0xbc41b39  call 0xc296b50` / `0xbc41b3e  movzx eax,byte ptr [rbp+0x188]` | sub_bc41420 calls dragon entry with the create descriptor; ret=0xBC41B3E [V live dragon_texture_caller_bc41420 + dragon_texture_entry_c296b50] | [V live] |
| wrapper 0xbc73bf0 | 0xbc73bf0 | - | E: `0xbc73bf0  push r15` | bgfx::createTexture* wrapper; capture bgfx_texture_wrapper_bc73bf0: `CALLER ret=0xC296D7E` inside dragon entry 0xc296b50 [V live r4] | [V live] |
| cmd-0x0E producer | sub_bc73770 | - | Table 2 | wrapper -> sub_bc73770 writes cmd byte 0x0E + handle into the command buffer | [V] |
| handle store into texture object | [texture_obj+0x00] | 2 | W: `0xc296e26  mov [rdi],ax` / R: `0xc296e1a  call 0xbc74120` (ax) / `0xc296e22  mov ax,0xFFFF` (invalid-handle fallback) | 16-bit bgfx texture handle stored at [texture_obj+0x00]; rdi = texture_obj = arg+0x58 | [V] |
| descriptor copy | [texture_obj+0x8] | 16 | R: `0xc296e2d  movups xmm0,[r12]` / W: `0xc296e32  movups [rdi+8],xmm0` | 0x1C-byte create descriptor copied to texture_obj+0x8 | [V] |

Capture chain index [V live]:
- dragon_texture_caller_bc41420.txt: capture at 0xBC41420, `CALLER ret=0x4E05F7C` (right after `0x4e05f77  call 0xbc41420`); RCX = 0x1C create descriptor (flags 0x80000000, size 0x1C, tag "tex", width/height fields) [V live bytes].
- dragon_texture_entry_c296b50.txt: capture at 0xC296B50, `CALLER ret=0xBC41B3E` [V live]; RCX/RDX/R8/R9 carry descriptor fields.
- createtexture_callers.txt: capture at 0xE8143C0, 1612 hits, one caller ret=0xBC6A2C8 [V live] (Table 4).
- l8b_texcreate_record.txt: capture at 0xE81BF30, `CALLER ret=0xE814560`; R8 = "Texture: 2815"/"Texture: 2799" name strings (runtime-created texture records) [V live].
- mc_root_4e05e50_callers.txt: capture at 0x4E05E50, 150 hits / 32 samples, all `CALLER ret=0x1289496`; RCX = heap objects carrying names "legends"/"tex"/"spear" plus dims/format fields [V live bytes].

End-to-end pack->GPU chain: MC texture object (mce::TexturePtr-family object, shared_ptr ctrl blocks at +0x10/+0x18 per sdk TexturePtr.h, names "legends"/"tex"/"spear" in captured RCX heaps [V live]) --sub_4e05e50(TexturePtr*, RCX)--> sub_bc41420 (`0x4e05f77  call 0xbc41420`, ret site 0x4E05F7C [V live]) --> dragon entry 0xc296b50 (`0xbc41b39  call 0xc296b50`, ret=0xBC41B3E [V live]) --> wrapper 0xbc73bf0 (ret=0xC296D7E inside 0xc296b50 [V live]) --> sub_bc73770 writes bgfx command byte 0x0E (`0xbc73aaa  mov byte ptr [rbp+0x2c],0xe`) + 2-byte handle into the command buffer at [ctx+0x1cfd0c8]+0xdc5820 [V Table 2] --> dispatcher `0xbc6a28f  mov rcx,[rdi+0x1ebf2d0]` / `0xbc6a2ae  mov rax,[rcx]` / `0xbc6a2b1  mov rax,[rax+0xd0]` / `0xbc6a2c2  call qword ptr [0xf99ffa0]` (slot 26 = createTexture 0xe8143c0 per BGFX_MAP.md line 403; sole caller ret=0xBC6A2C8 [V live]) --> createTexture body (`0xe81455b  call 0xe81bf30`, ret site 0xE814560 [V live]) --> D3D12 texture record table this+0xBDE178 stride 0xB8 --> returned handle stored back at [texture_obj+0x00] (`0xc296e26  mov [rdi],ax` [V]).

## Interpretations ([I], not row claims)

- slot 26 = 0xe8143c0 createTexture comes from BGFX_MAP.md line 403 and the vtable-slot layout; the dispatcher dis shows the slot load directly (`0xbc6a2b1  mov rax,[rax+0xd0]`) [V], the name is [I BGFX_MAP.md].
- byte 14 = createTexture in the bgfx command stream (BGFX_MAP.md lines 1476-1478: handler 0xbc69487 requires magic 0x00584554 'TEX', parses the 0x18-byte TextureCreate header, calls renderer vtable slot 26; returned pointer stored in the per-handle table ctx+0x1e55ab8 element+0x10) — [V code / [I] meaning] per BGFX_MAP.md; matches sub_bc73770 staging cmd byte 0x0E with the "TEX" descriptor tag [V live].
- mce::TexturePtr is 32B (static_assert in src/sdk/mc/deps/minecraft_renderer/renderer/TexturePtr.h [V file read]): mClientTexture shared_ptr at +0x00 (ptr +0x00, ctrl block +0x8), mResourceLocationPtr at +0x10 (ptr +0x10, ctrl block +0x18). sub_4e05e50's refcount code (`lock cmpxchg [rdx+8]`, `lock inc [rbx+8]`) matches that layout [V].
- Sampler half (6ax) [V] from prior units; atlas stitchers L8a/L8b remain separate open units (oc_U-EL8a/oc_U-EL8b), not this unit. MIRROR_SKIP applies to atlas stitchers.

## What I tried that failed (new angles, not redone)

- xref.py callers 0xe8143c0 / 0x4E05E50 / 0x1289400: EMPTY for all three (re-confirmed this session). createTexture reachable only via indirect [vptr+0xD0] — solved via the live capture instead (sole caller ret=0xBC6A2C8 [V live]).
- texload 0x58a1310 / texload_task 0x541bf00: xref.py callers EMPTY; never decoded; not on the proven path (texgroup_load's only cache-bound call is 0x54227af -> 0x18718d0 [V r2]; 0x18718D0 does not reach sub_4e05e50 [V r44]).
- [0xF99FFA0] writer search: none — read-only .rdata initializer = sub_eea6040 (r37; `.text` store scan 0 hits, .rdata flags 0x40000040 read-only, _f99ffa0_refs.txt lists only reads/calls).
- trampoline target rax: resolved statically, no capture needed — rax = vptr[1] = sub_4e05e50 via vtable 0xF215838 slot +0x008 [V rdis vt this session] + vtable bind sub_4e060b0 [`0x4e060bb  lea rax,[0xF215838]` / `0x4e060c2  mov [rcx],rax`] [V this session] + mc_root capture all 32 samples ret=0x1289496 [V live]. r37's suggested capture at 0xEEA6040 entry (read rax at the `jmp rax`) could not be requested this unit: 4 live captures already pending (orchestrator limit); the static resolution makes it non-blocking.
- texgroup_load -> sub_1289400 static link: absent (0 static xrefs into sub_1289400 [V this session]); reached at runtime only — documented in Table 5, not a blocker for the vtable-resolved entry hop; the one capture that would close it is at sub_1289400 entry (expect CALLER ret inside texgroup_load).

## CLOSES?

NO — blocking fact: no [V]-proven static path texgroup_load(0x5421c90) -> sub_1289400 -> sub_4e05e50. 0 static xrefs into sub_1289400 and sub_4e05e50 [V this session]; the bind is runtime-only via sub_1289400's vtable[1] indirect tail-call `0x1289490  call qword ptr [0xF99FFA0]` (trampoline [0xF99FFA0] = sub_eea6040 `jmp rax`, read-only .rdata initializer 0x14EEA6040, no code writer [V]); the indirect target IS resolved: rax = vptr[1] = sub_4e05e50 via vtable 0xF215838 slot +0x008 [V], ctor bind [V], mc_root capture all 32 samples ret=0x1289496 [V live]. Every hop below sub_4e05e50 is [V] or [V live]: command byte 0x0E producer sub_bc73770 (Table 2), dispatcher slot-26 issuance (Table 4, sole caller ret=0xBC6A2C8 [V live]), createTexture body 0xe8143c0 -> TextureD3D12::create 0xe81bf30 (ret site 0xe814560 [V live]), record table this+0xBDE178 stride 0xB8, returned handle stored at [texture_obj+0x00] (`0xc296e26  mov [rdi],ax` [V], texture_obj = TexturePtr+0x58 [V], sdk TexturePtr.h sizeof==32 [V file read]). Closing requires one live capture at sub_1289400 entry naming its runtime caller (expected inside texgroup_load) — pending, capture-limit reached this unit.

## TOOL REQUESTS

- Capture at sub_1289400 entry (name its runtime caller ret= inside texgroup_load 0x5421c90): closes the single blocking fact above. Could not be requested this unit — 4 live captures already pending (orchestrator limit).
- Capture at 0xEEA6040 entry (read rax at `jmp rax`): corroboration of the rax = sub_4e05e50 indirect target; static resolution already sufficient, low priority.
- No helper scripts written; no temporary files left behind.

## Verification

- `python tools/sigs/verify_oc.py docs/progress/oc_U-EL7e.md` — mismatch=0, no-such-instr=0 required (all quoted instruction lines re-verified against fresh rdis this session; vt/capture citations are tool evidence, not instruction claims).
- `python tools/delegate.py check docs/progress/oc_U-EL7e.md` — must exit 0; then set line 2 after `## NEXT` to DONE.
