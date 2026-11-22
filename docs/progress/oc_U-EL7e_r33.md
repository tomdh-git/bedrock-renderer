## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): `- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending | PROGRESS 2026-11-21 oc_U-EL7e.md (verify_oc 185/185): D3D12 backend texture-management chain decoded [V] ...; Minecraft-side pack->GPU chain (texgroup_load 0x5421c90 -> texload 0x58a1310 -> texload_task 0x541bf00 -> undecoded 0x18718D0 at 0x54227af) and atlas stitchers still open (L8a/L8b)`

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; live capture logs under docs/data/live are read-only orchestrator inputs.

Tags: [V] saw in disassembly (verbatim line quoted, RVA cited) / [V live] saw in an orchestrator live capture log (file cited) / [I] inferred from structure or BGFX_MAP / [?] unknown or not located.

Row rule: one annotated row per distinct offset, all its read/store sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after address, copied verbatim from rdis) | meaning ONLY if an instruction/string shows it else '-' | tag. Sizes from the instruction (movups/movaps/movdqu/movdqa 16, qword 8, dword/movss 4, word 2, byte/nop 1). No input data pasted as-is; no skipped offsets among quoted sites; no raw instruction dumps outside tables; no catch-all or ellipsis rows.

## Live captures read this session (inputs, not re-queued)

- docs/data/live/mc_root_4e05e50_callers.txt: 150 hits, 32 samples; every sample CALLER ret=0x1289496 = sub_12893d0 tail-call into sub_4e05e50 (the ONLY live caller observed; recapitulates chain proven in r1-r32, nothing redone).
- docs/data/live/l8b_texcreate_record.txt: 24 samples, ret=0xE814560 = TextureD3D12::create return site (already proven [V live]).

## Already proven (prior sessions r1-r32 — NOT redone, cited only)

- Half 1 — sampler flag decode + sampler cache (6ax): [V] docs/functions/e820500.md decodes 0xe820500 instruction-complete; src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h carries static_asserts; called from blit 0xe818bc0 and executor 0xe821120.
- Half 2a — D3D12 backend texture-management chain: [V] record table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0, updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0, blitSetup 0xe819750; BGFX_MAP 6z/6z-2/6aj confirm table base/stride and live texture records.
- createTexture 0xe8143c0: no static caller (xref.py callers EMPTY [V r2]); reached only via indirect RendererContext [vptr+0xD0] slot 26 = 0xe8143c0 (BGFX_MAP line 403).
- Command-byte-14 producer sub_bc73770 [V r4]; wrappers 0xbc73bf0/0xbc73ed0/0xbc74120 from dragon entries 0xc296b50/0xc297000/0xc2a3d90/0xbc63c80 [V]; MC texture code calls none statically [V xref].
- Full live issuance chain [V live + dis]: sub_4e05e50 (`0x4E05F77  call 0xBC41420`, ret site `0x4E05F7C  nop` [V live]) -> sub_bc41420 -> 0xc296b50 -> 0xbc73bf0 -> 0xbc73770 (cmd byte 0x0E) -> bgfx dispatcher case 0xBC6A2C2 (`0xBC6A2B1  mov rax,[rax+0xD0]`, slot 26 = createTexture 0xe8143c0) -> `0xBC6A2C2  call qword ptr [0xF99FFA0]` -> createTexture 0xe8143c0 -> `0xE81455B  call 0xE81BF30` TextureD3D12::create (ret site 0xE814560 [V live]). Returned handle `0xC296E1A  call 0xBC74120` (ax) -> `0xC296E26  mov [rdi],ax` (size 2, word) at texture_obj+0x00 [V]; texture_obj = TexturePtr+0x58 (`0x4E05F68  add rdi,0x58`) [V].
- sdk headers [V file read]: TexturePtr.h `static_assert(sizeof(TexturePtr) == 32)`, mClientTexture +0x00 / mResourceLocationPtr +0x10; ClientTexture empty struct; BedrockTexture.h `static_assert(sizeof(BedrockTexture) == 48)`.
- sub_4e05e50: 0 static xrefs (`rdis callers 0x4E05E50` -> 0 calling functions; fn [0x4E05E50..0x4E06074) size 0x224 [V]); reached only via sub_12893d0's indirect vtable[1] tail-call `0x1289490  call qword ptr [0xF99FFA0]` (capture ret site `0x1289496  nop` = ret=0x1289496, all 32 samples [V live]).
- sub_12893d0 decoded instruction-complete [V r22-r32]: deferred-texture-transaction flush; per 0x18-byte element {ptr@0, shared_ctrl@8, obj@0x10} add_refs [ctrl+8], copies 16 bytes, tail-calls obj->vptr[1](&element) through trampoline [0xF99FFA0] = sub_eea6040 `jmp rax`, detach + release via vptr[0]. Static callers sub_6632bf0 (2 sites), sub_1145c20 (2 sites), sub_6622610, sub_66232b0 (8 sites) [V rdis callers] — none is texgroup_load/texload/texload_task; all upward chains dead-end at 0-static-caller functions [V rdis/xref].
- [0xF99FFA0] resolved [V r26-r32]: read-only .rdata slot, file bytes = 0x14EEA6040 = abs VA of sub_eea6040 (`jmp rax` trampoline); never written by code (`rdis imm 0xF99FFA0` 0 hits; ripscan .text zero stores; section flags read-only); NOT sub_4e05e50 (0x4E05E50). texgroup_load references 0x4E05E50 nowhere (`rdis imm 0x4E05E50` 0 hits).
- texgroup_load(0x5421c90): static chain ends at `0x54227AF  call 0x18718D0` (texture cache) [V]; direct callees do not enter sub_12893d0's caller tree [V r22-r30]; cache 0x18718d0 builds objects with vtable 0xEFCA680, never calls sub_4e05e50/sub_12893d0 [V r19].
- sub_4e05450 (texture job constructor, sets vptr=0xF215838 at `0x4E05654  mov [rbx],r8`, texture sub-object at +0x58, renderer ctx at +0xE0) has 16 static callers, none is texgroup_load/texload/texload_task [V rdis callers].
- Vtable 0xF215838: slot 0 = sub_4e060b0 (destructor), slot 1 = sub_4e05e50 [V rdis vt]; live capture vptr = 0x7FF6A8215838 [V live].
- Atlas stitchers (L8a/L8b): out of scope (MIRROR_SKIP).

## NEW ANGLE THIS SESSION: vtable 0xEFCA580 slot 4 (orchestrator hint conditional)

Per the orchestrator hint: "If the producer is a thin bgfx API wrapper called from the texture-object init (vtable 0xEFCA580 slot 4), cite that call. If it is not statically reachable, say so with the xref evidence and stop."

The cache object built by 0x18718d0 carries vtable 0xEFCA680 [V r19] — NOT 0xEFCA580. So 0xEFCA580 is a distinct vtable not previously examined. rdis `vt 0xEFCA580` slot 4 (+0x20) = sub_a3f10. Decoded sub_a3f10: it is a refcounted-object destructor/release path, NOT a texture-object init, and it does NOT call the bgfx producer sub_bc73770 or any wrapper (0xbc73bf0/0xbc73ed0/0xbc74120). rdis `vt` reports sub_a3f10 with 0 xrefs in (no static caller at all).

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| vtable 0xEFCA580 slot 0 | 0xEFCA580+0x000 | 8 | [0xEFCA580] | `0xEFCA580` slot 0 = sub_a2da0 | slot 0 target | [V] |
| vtable 0xEFCA580 slot 1 | 0xEFCA580+0x008 | 8 | [0xEFCA580+8] | `0xEFCA580+8` slot 1 = sub_76900 | slot 1 target | [V] |
| vtable 0xEFCA580 slot 2 | 0xEFCA580+0x010 | 8 | [0xEFCA580+0x10] | `0xEFCA580+0x10` slot 2 = sub_a4590 | slot 2 target | [V] |
| vtable 0xEFCA580 slot 3 | 0xEFCA580+0x018 | 8 | [0xEFCA580+0x18] | `0xEFCA580+0x18` slot 3 = sub_76920 | slot 3 target | [V] |
| vtable 0xEFCA580 slot 4 (hint target) | 0xEFCA580+0x020 | 8 | [0xEFCA580+0x20] | `0xEFCA580+0x20` slot 4 = sub_a3f10 | slot 4 = sub_a3f10, size 0x2d per vt header | [V] |
| sub_a3f10 entry | 0xA3F10 | 1 | - | `0xA3F10  push rsi` | destructor/release entry; rdis `sub_a3f10 ... 0 xrefs in` | [V] |
| vtable stamp 0xEFCA5A0 | [rcx+0x00] | 8 | W: `0xA3F53  mov [rcx],rax` | `0xA3F4C  lea rax,[0xEFCA5A0]` / `0xA3F53  mov [rcx],rax` | stamps vptr = 0xEFCA5A0 (different vtable) | [V] |
| vtable stamp 0xEFCA5D0 | [rcx+0x90] | 8 | W: `0xA3F5D  mov [rcx+0x90],rax` | `0xA3F56  lea rax,[0xEFCA5D0]` / `0xA3F5D  mov [rcx+0x90],rax` | stamps +0x90 = 0xEFCA5D0 | [V] |
| vtable stamp 0xEFCA5F0 | [rcx+0xA8] | 8 | W: `0xA3F6B  mov [rcx+0xA8],rax` | `0xA3F64  lea rax,[0xEFCA5F0]` / `0xA3F6B  mov [rcx+0xA8],rax` | stamps +0xA8 = 0xEFCA5F0 | [V] |
| trampoline call #1 | [0xF99FFA0] | 8 | R: `0xA3F8D  call qword ptr [0xF99FFA0]` | `0xA3F8D  call qword ptr [0xF99FFA0]` | vptr[0] release via trampoline sub_eea6040 | [V] |
| trampoline call #2 | [0xF99FFA0] | 8 | R: `0xA3FA3  call qword ptr [0xF99FFA0]` | `0xA3FA3  call qword ptr [0xF99FFA0]` | vptr[1] release via trampoline sub_eea6040 | [V] |
| trampoline call #3 | [0xF99FFA0] | 8 | R: `0xA3FF3  call qword ptr [0xF99FFA0]` | `0xA3FF3  call qword ptr [0xF99FFA0]` | list-element vptr+0x20 release via trampoline | [V] |
| operator delete | 0xE935700 | 5 | - | `0xA3F2E  call 0xE935700` / `0xA4038  call 0xE935700` | frees memory | [V] |
| trampoline call #4 | [0xF99FFA0] | 8 | R: `0xA407E  call qword ptr [0xF99FFA0]` | `0xA407E  call qword ptr [0xF99FFA0]` | +0xB0 member vptr+8 release via trampoline | [V] |
| trampoline call #5 | [0xF99FFA0] | 8 | R: `0xA409D  call qword ptr [0xF99FFA0]` | `0xA409D  call qword ptr [0xF99FFA0]` | +0xA0 member vptr+8 release via trampoline | [V] |
| other trampoline | [0xF9A8C78] | 8 | R: `0xA40C7  call qword ptr [0xF9A8C78]` | `0xA40C7  call qword ptr [0xF9A8C78]` | second indirect-call slot | [V] |
| tail jump | 0x76B950 | 5 | - | `0xA40AF  jmp 0x76B950` | tail to sub_76b950 | [V] |

sub_a3f10 callees: sub_a3f40, sub_e935700 (x2), [0xF99FFA0] (x5), [0xF9A8C78], sub_76b950 — NONE is sub_bc73770 or any bgfx wrapper/dragon entry. sub_a3f10 has 0 static callers. The ripscan hits for 0xEFCA580 (0xa2258, 0x26daafd, 0x524890f, 0x55fcc01) do not decode to clean vptr stamps of 0xEFCA580 leading to the producer (e.g. 0x55fcc01 stamps vtable 0xF25C640, a different vtable); they are not a texture-object init path either.

Finding: vtable 0xEFCA580 slot 4 = sub_a3f10 is a destructor path, NOT a texture-object init calling the bgfx command-byte-14 producer. The hint's conditional is NOT met: the producer sub_bc73770 is not statically reachable from vtable 0xEFCA580 slot 4, and there is no static call path from texgroup_load(0x5421c90) / cache 0x18718d0 into sub_4e05e50.

## What I tried that failed (do not redo)

- [0xF99FFA0] writer hunt: read-only .rdata, holds sub_eea6040 trampoline, zero stores, never = sub_4e05e50 [V r26-r32].
- sub_4e05e50 static callers: 0 xrefs [V].
- sub_12893d0 static callers: 4 functions, all dead-end [V rdis/xref].
- texgroup_load static chain: ends at cache 0x18718d0 (`0x54227AF call 0x18718D0` [V]); no callee enters sub_12893d0's tree.
- sub_4e05450 callers: 16, none is texgroup_load/texload/texload_task [V].
- vtable 0xEFCA580 slot 4 = sub_a3f10: destructor, 0 callers, no bgfx producer call [V this session].

## CLOSES?

NO — blocking fact: no [V]-proven static path texgroup_load(0x5421c90) -> sub_4e05e50, hence no static instruction path from MC pack-loading code into the createTexture issuance chain. sub_4e05e50 has 0 static xrefs and is reached only at runtime via sub_12893d0's indirect vtable[1] tail-call `0x1289490  call qword ptr [0xF99FFA0]` (trampoline [0xF99FFA0] = sub_eea6040 `jmp rax`, read-only .rdata, never written [V]); sub_12893d0's static callers all dead-end; texgroup_load's static chain ends at cache 0x18718d0 (vtable 0xEFCA680 objects, never calls sub_4e05e50 [V]); vtable 0xEFCA580 slot 4 = sub_a3f10 is a destructor with 0 callers and no bgfx producer call [V this session]. The bind is runtime-only via object vptr[1] = sub_4e05e50 (vtable 0xF215838), observed live [V live]. Everything else in the item IS [V]-proven: sampler flag decode + cache (6ax), D3D12 backend texture-management chain, command-byte-14 producer sub_bc73770 [V r4], dispatcher [vptr+0xD0]->createTexture 0xe8143c0 [V live + dis], returned handle into TexturePtr+0x58+0 [V], sdk TexturePtr/ClientTexture [V file read]. Atlas stitchers (L8a/L8b) remain out of scope (MIRROR_SKIP).

## TOOL REQUESTS

- None. New-angle work used existing rdis vt/dis and ripscan.py only; no helper scripts written, no temporary files left behind.
