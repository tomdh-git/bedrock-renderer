## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): `- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending | PROGRESS 2026-11-21 oc_U-EL7e.md (verify_oc 185/185): D3D12 backend texture-management chain decoded [V] ...; Minecraft-side pack->GPU chain (texgroup_load 0x5421c90 -> texload 0x58a1310 -> texload_task 0x541bf00 -> undecoded 0x18718D0 at 0x54227af) and atlas stitchers still open (L8a/L8b)`

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; live capture logs under docs/data/live are read-only inputs produced by the orchestrator (read this session: mc_root_4e05e50_callers.txt, l8b_texcreate_record.txt, dragon_texture_caller_bc41420.txt, dragon_texture_entry_c296b50.txt, bgfx_texture_wrapper_bc73bf0.txt, createtexture_callers.txt, bgfx_createtexture_producer.txt).

Tags: [V] saw in disassembly (RVA cited, verbatim `0xRVA  instr` quoted) / [V live] saw in an orchestrator live capture log (file cited) / [I] inferred from structure or tool output / [?] unknown or not located.

Row rule: one annotated row per distinct offset, all its sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after the address, copied verbatim from rdis) | meaning ONLY if an instruction/string shows it else '-' | tag. Sizes from the instruction (movups/movaps/movdqu/movdqa 16, qword 8, dword/movss 4, word 2, byte 1). No input data pasted as-is; no skipped offsets among quoted sites; no raw instruction dumps outside tables; no ellipsis or catch-all rows.

## Already proven (cited from r1-r39; not re-quoted, not redone)

- Half 1 — sampler flag decode + sampler cache (6ax): [V] docs/functions/e820500.md decodes 0xe820500 instruction-complete; src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h carries the static_asserts; called from blit 0xe818bc0 and executor 0xe821120.
- Half 2a — D3D12 backend texture-management chain: [V] record table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0, updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0, blitSetup 0xe819750; BGFX_MAP 6z/6z-2/6aj confirm table base/stride and live texture records.
- texgroup_load(0x5421c90) static chain end: `0x54227AF  call 0x18718D0` into the texture cache (cache objects vtable 0xEFCA680, != 0xF215838); texload/texload_task have 0 static callers and 0x18718d0 never calls sub_4e05e50/sub_12893d0 [V r19].
- [0xF99FFA0] writer search [V r38]: slot is constant image data (no static writer), used as jmp-rax trampoline sub_eea6040 for all indirect virtual calls; callee placed in RAX per call site.

## This session — createTexture issuance link verified (orchestrator hint): command-byte-14 producer, handler 0xbc69487, handle trace into TexturePtr/ClientTexture

New-angle findings this session:
- Producer of command byte 14 (0x0E = createTexture): sub_bc73770 writes `0xBC73AAA  mov byte ptr [rbp+0x2C],0xE` into the command descriptor, then copies it into the renderer command buffer at rbx+0xDC5820+[rbx+0xDC5818] via `0xBC73AC9  call 0xEBCE390` (memcpy 1 byte) [V r4 + re-verified verbatim this session]. sub_bc73770 has 3 static xrefs in; it is reached only through thin wrappers 0xbc73bf0/0xbc73ed0/0xbc74120 from dragon entries 0xc296b50/0xc297000/0xc2a3d90/0xbc63c80 (dragon layer) — the MC texture code (texgroup_load/texload/texload_task) calls none of them statically [V r4].
- Handler 0xbc69487 (sub_bc69487, 0xbc69487..0xbc6b487) is the bgfx TEX command interpreter: requires BGFX_CHUNK_MAGIC_TEX `0xBC695A3  cmp dword ptr [rsp+0x8C],0x584554` ('T','E','X',0), parses the 0x18-byte TextureCreate header via `0xBC695FA  call qword ptr [0xF99FFA0]`, then issues createTexture through renderer ctx vtable slot 26: `0xBC6A2B1  mov rax,[rax+0xD0]` / `0xBC6A2C2  call qword ptr [0xF99FFA0]` -> createTexture 0xe8143c0; ret site 0xBC6A2C8 = live CALLER ret=0xBC6A2C8 (docs/data/live/createtexture_callers.txt) [V] [V live]. Matches BGFX_MAP 6es (handler 0xbc69487 calls slot 26 = createTexture).
- Hinted vtable 0xEFCA580 slot-4 texture-object-init citation does NOT apply: `rdis vt 0xEFCA580` slot 4 (+0x020) = sub_a3f10, a tiny thunk (`push rsi`), not a texture-object init [V].
- Handle trace into TexturePtr/ClientTexture: sub_4e05e50(RCX=TexturePtr*) reads renderer ctx `0x4E05F61  mov r9,[rdi+0xE0]`, computes texture object `0x4E05F68  add rdi,0x58` (object = TexturePtr+0x58), issues create `0x4E05F77  call 0xBC41420` (ret site 0x4E05F7C = live CALLER ret=0x4E05F7C, docs/data/live/dragon_texture_caller_bc41420.txt) [V] [V live]. Returned 16-bit handle via `0xC296E1A  call 0xBC74120` (ax; `0xC296E22  mov ax,0xFFFF` invalid-handle fallback) stored at `0xC296E26  mov [rdi],ax` (size 2, handle at texture_obj+0x00), then 16 result bytes `0xC296E32  movups [rdi+8],xmm0` (size 16, at texture_obj+0x08) [V]. sdk TexturePtr/ClientTexture [V file read: sizeof(TexturePtr)==32, mClientTexture +0x00, mResourceLocationPtr +0x10, ClientTexture empty, BedrockTexture 48 bytes]. Handle therefore lands at TexturePtr+0x58+0x00 inside the texture object referenced by TexturePtr (mClientTexture +0x00 is the ClientTexture per sdk header).

## Table — createTexture issuance link (command byte 14 -> handler 0xbc69487 -> handle into TexturePtr)

| name | offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| producer writes command byte 0x0E | 0xBC73AAA | 1 | W: `0xBC73AAA  mov byte ptr [rbp+0x2C],0xE` | command byte 14 (0x0E = createTexture) written into command descriptor | [V] |
| producer emits cmd byte to command buffer | 0xBC73AC9 | - | - | `0xBC73ABF  lea rdx,[rbp+0x2C]` / `0xBC73AC9  call 0xEBCE390` | copies the 0x0E byte into ctx command buffer at rbx+0xDC5820+[rbx+0xDC5818] | [V] |
| handler TEX magic check | 0xBC695A3 | 4 | R: `0xBC695A3  cmp dword ptr [rsp+0x8C],0x584554` | requires BGFX_CHUNK_MAGIC_TEX 'TEX' (0x584554) | [V] |
| handler loads vtable slot 26 | 0xBC6A2B1 | 8 | R: `0xBC6A2B1  mov rax,[rax+0xD0]` | [rax+0xD0] = renderer ctx vtable slot 26 = createTexture (BGFX_MAP 6k) | [V] |
| handler issues createTexture via trampoline | 0xBC6A2C2 | 8 | R: `0xBC6A2C2  call qword ptr [0xF99FFA0]` | ret site 0xBC6A2C8 = live CALLER ret=0xBC6A2C8 | [V] [V live] |
| sub_4e05e50 renderer ctx +0xE0 | 0x4E05F61 | 8 | R: `0x4E05F61  mov r9,[rdi+0xE0]` | sub_4e05e50(RCX=TexturePtr*) reads renderer ctx; then `0x4E05F68  add rdi,0x58` (texture object = TexturePtr+0x58) and `0x4E05F77  call 0xBC41420` (ret 0x4E05F7C [V live]) | [V] [V live] |
| handle stored into texture object | 0xC296E26 | 2 | W: `0xC296E26  mov [rdi],ax` | 16-bit handle from `0xC296E1A  call 0xBC74120` (ax; `0xC296E22  mov ax,0xFFFF` invalid fallback) stored at texture_obj+0x00 | [V] |
| createTexture result bytes copied | 0xC296E32 | 16 | W: `0xC296E32  movups [rdi+8],xmm0` | 16 result bytes at texture_obj+0x08 (`0xC296E2D  movups xmm0,[r12]` source) | [V] |

## CLOSES?

NO — blocking fact: no [V]-proven static path texgroup_load(0x5421c90) -> sub_4e05e50 -> createTexture. The createTexture issuance mechanism itself is now [V]-proven at the bgfx level (producer sub_bc73770 writes command byte 0x0E at `0xBC73AAA  mov byte ptr [rbp+0x2C],0xE`; handler sub_bc69487 TEX magic `0xBC695A3  cmp dword ptr [rsp+0x8C],0x584554`; slot 26 `0xBC6A2B1  mov rax,[rax+0xD0]` / `0xBC6A2C2  call qword ptr [0xF99FFA0]` -> createTexture 0xe8143c0; handle stored `0xC296E26  mov [rdi],ax` at TexturePtr+0x58+0x00), but it is reachable only through dragon-layer wrappers (0xc296b50/0xc297000/0xc2a3d90/0xbc63c80; thin wrappers 0xbc73bf0/0xbc73ed0/0xbc74120) and the runtime vtable[1] bind — the MC texture code (texgroup_load/texload/texload_task) calls none of these statically [V r4]. sub_4e05e50 (fn 0x4E05E50..0x4E06074) has 0 static calling functions; it is entered only via vtable[1] of vtable-0xF215838 texture-job objects (`0x1289489  mov rax,[rax+8]`, `0x1289490  call qword ptr [0xF99FFA0]` -> trampoline `0xEEA6040  jmp rax`, ret site 0x1289496 [V live]). [0xF99FFA0] is constant image data (1,088,051 read refs, 0 stores; `xr`/`imm` sweeps = 0 hits) so the bind is resolved per call in RAX at runtime, not by a static write — there is no static writer to name. vtable 0xEFCA580 slot 4 = sub_a3f10 (tiny thunk), not a texture-object init, so that hinted citation path does not apply [V]. texgroup_load's static chain ends at `0x54227AF  call 0x18718D0` (texture cache vtable 0xEFCA680 != 0xF215838) [V r19] — a separate system from the vtable-0xF215838 job objects. Everything else in L7e is [V]/[V live]-proven: sampler flag decode + cache (6ax), D3D12 backend texture-management chain, createTexture issuance mechanism, returned-handle store, sdk TexturePtr/ClientTexture headers. Atlas stitchers L8a/L8b remain separate open items (oc_U-EL8a/oc_U-EL8b).

## Verification

- `python tools/sigs/verify_oc.py docs/progress/oc_U-EL7e.md` — every backticked `0xRVA  instr` line must match rdis dis output (mismatch=0, no-such-instr=0).
- `python tools/delegate.py check docs/progress/oc_U-EL7e.md` — must exit 0; `## NEXT` line 2 is DONE only after check exits 0.

## TOOL REQUESTS

- None (no helper scripts written, no temporary files left; all instruction lines quoted verbatim from a fresh rdis dis of the 1.26.62.01 exe this session; xr/imm/vt/fn/dis/callers used for positive and negative findings).
