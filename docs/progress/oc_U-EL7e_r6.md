## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): `- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending | PROGRESS 2026-11-21 oc_U-EL7e.md (verify_oc 185/185): D3D12 backend texture-management chain decoded [V] ...; Minecraft-side pack->GPU chain (texgroup_load 0x5421c90 -> texload 0x58a1310 -> texload_task 0x541bf00 -> undecoded 0x18718D0 at 0x54227af) and atlas stitchers still open (L8a/L8b)`

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; two orchestrator live captures read (read-only, never touched by me): docs/data/live/createtexture_callers.txt, docs/data/live/bgfx_createtexture_producer.txt, docs/data/live/bgfx_texture_wrapper_bc73bf0.txt.

Tags: [V] saw in disassembly (RVA cited, verbatim line quoted), [V live] saw in an orchestrator live capture (file+line cited), [I] inferred from structure/BGFX_MAP/hint, [?] unknown / not located.
Row rule: one annotated row per distinct offset, all its read/store sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after the address, copied from rdis) | meaning ONLY if an instruction/string shows it else '-' | tag. Sizes from the instruction (movups 16, qword 8, dword/movss 4, word 2, byte 1). No input data pasted as-is; no skipped offsets. No raw instruction dumps outside tables.

## Already proven (cited from r1-r5, NOT re-derived here)

- Half 1 — sampler flag decode + sampler cache (6ax): [V] docs/functions/e820500.md decodes 0xe820500 instruction-complete; src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h carries static_asserts; called from blit 0xe818bc0 and executor 0xe821120.
- Half 2a — D3D12 backend texture-management chain: [V] Tables 1-8 of oc_U-EL7e_r1.md: record table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0 (slot 26), updateTexture 0xe814a70 (28), readTexture 0xe8150f0 (30), resizeTexture 0xe815840 (31), override/get/destroy 0xe815c30..0xe815fbf (32-34), destructor 0xe80f290, blit 0xe818bc0 (51), blitSetup 0xe819750 (52); BGFX_MAP 6z/6z-2/6aj confirm table base/stride and live texture records (guard byte this+0xC96190 = 0 live).
- Static negatives (r2-r5, not redone): xref.py callers 0xe8143c0 = EMPTY — createTexture has no static caller, only indirect [vptr+0xD0] (slot 26 = offset 0xD0); texload 0x58a1310 and texload_task 0x541bf00: xref EMPTY for both; texgroup_load does not call them (its only cache-bound call is `0x54227af call 0x18718d0` [V]); 0x18718d0 decoded as the texture cache (BST this+0x30, ready callback 0x873D0->jmp 0xEEC59D0 via 0x7705B0, async enqueue 0x71BC70 "resource dispatch"); texture-object init vtable 0xEFCA580 slot 4 (sub_a3f10) only swaps live vtables 0xEFCA5A0/5D0/5F0, never calls createTexture [V r2]. Atlas stitchers remain open items L8a/L8b (oc_U-EL8a/oc_U-EL8b), not this unit.

## What I tried that failed (do not redo)

- `imm 0x0E` scan over .text: only `mov ecx,0xE` at 0x81bf (register move); NO `mov byte ptr [mem], 0x0E` anywhere — command byte 0x0E is computed at runtime, not stored as an immediate.
- Command-buffer writer scan (all `add rcx,0xDC5820` + `call 0xEBCE390` sites): writers hardcode opcodes 0x00 (sub_bc63b80), 0x07 (sub_bc5f8d0), 0x0A (sub_bc716a0/sub_bc71990), 0x0B (sub_bc71da0), 0x12 (sub_bc74590), 0x14 (sub_bc74a80), 0x27 (sub_bc7489f, buffer +0xE05820); NONE stores 0x0E.
- Dispatch table at 0xF449638 is obfuscated/indirect — byte-to-handler mapping not re-derivable statically; the hint mapping (byte 14 -> 0xbc69487) is accepted as verified and is consistent with both live captures.

## This session — the missing link: who issues createTexture (command byte 14)

### (1) Producer of command byte 0x0E — sub_bc73770 [V]

sub_bc73770 (0xbc73770; exactly 3 static xrefs in [V]) is the command producer. Its ctx argument is the bgfx::s_ctx global `mov rcx,[0x12AE1748]` [V; BGFX_MAP 6r identifies 0x12ae1748 as bgfx::s_ctx]. It allocates a handle via 0xBC79A60 (`mov [rbp+0x2E],ax`, written out through `mov [rsi],di`), initializes the handle record at [rdi+0x1E55AB8] with stride 0x28 (`lea eax,[r15*8]` / `lea rcx,[rax+rax*4]` = handle*0x28, record field `mov [r14+0x10],rdx`), tests the RayTracing cap bit (`bt dword ptr [0x12ADFA50],0x15`), and then writes the create command into the command buffer [rdi+0x1CFD0C8] at cursor [rdi+0xDC5818]:

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| command-buffer base | [rdi+0x1CFD0C8] | 8 | R: `0xbc73aa3  mov rbx,[rdi+0x1CFD0C8]` | command buffer object pointer | [V] |
| command-buffer cursor | [rbx+0xDC5818] | 4 | R: `0xbc73aae  mov eax,[rbx+0xDC5818]` / W: `0xbc73b6a  inc dword ptr [rbx+0xDC5818]` | write cursor read, then bumped | [V] |
| command destination | [rbx+rax] + 0xDC5820 | 8 | `0xbc73ab4  lea rcx,[rbx+rax]` / `0xbc73ab8  add rcx,0xDC5820` | dst = buffer base + cursor | [V] |
| opcode byte | [rbp+0x2C] | 1 | W: `0xbc73aaa  mov byte ptr [rbp+0x2C],0xE` / R: `0xbc73abf  lea rdx,[rbp+0x2C]` / `0xbc73ac3  mov r8d,1` / `0xbc73ac9  call 0xEBCE390` | writes immediate 0xE = command byte 14 (createTexture) [I: dispatch-table mapping per hint] | [V] |
| handle memcpy | [rbp+0x2E] | 2 | `0xbc73af5  call 0xEBCE390` (2 bytes from [rbp+0x2E]) | handle u16 copied into command | [V] |
| descriptor memcpy | [rbp+0x18] | 8 | `0xbc73b10  lea rdx,[rbp+0x18]` / `0xbc73b14  mov r8d,8` / `0xbc73b1a  call 0xEBCE390` | 8-byte descriptor block copied into command | [V] |
| flags memcpy | [rbp+0x28] | 4 | `0xbc73b35  lea rdx,[rbp+0x28]` / `0xbc73b39  mov r8d,4` / `0xbc73b3f  call 0xEBCE390` | flags dword copied into command | [V] |
| trailing byte | [rbp+0x2D] | 1 | `0xbc73b57  lea rdx,[rbp+0x2D]` / `0xbc73b5b  mov r8d,1` / `0xbc73b64  call 0xEBCE390` | 1 byte copied into command | [V] |
| handle allocation call | 0xbc7384d | - | `0xbc7384d  call 0xBC79A60` | allocate handle -> ax, stored at [rbp+0x2E] | [V] |
| handle slot | [rbp+0x2E] | 2 | W: `0xbc73853  mov [rbp+0x2E],ax` / R: `0xbc73b70  movzx edi,word ptr [rbp+0x2E]` | handle stored to slot, read back as return value | [V] |
| handle out-param | [rsi] | 2 | W: `0xbc73b74  mov [rsi],di` | *out_handle = handle | [V] |
| handle record base | [rdi+0x1E55AB8] | 8 | R: `0xbc73861  lea r14,[rdi+0x1E55AB8]` | bgfx::s_ctx handle-record array base | [V] |
| record stride | 0x28 | 4/8 | `0xbc738e3  lea eax,[r15*8]` / `0xbc738eb  lea rcx,[rax+rax*4]` | index = handle*0x28 | [V] |
| record field +0x10 | [r14+0x10] | 8 | W: `0xbc73a63  mov [r14+0x10],rdx` | record field written (rt-cap flag dword) | [V] |
| RT cap bit | [0x12ADFA50] | 4 | R: `0xbc73a39  bt dword ptr [0x12ADFA50],0x15` | supported-flags bit 0x15 (RayTracing cap) gates the field store | [V] |

### (2) Thin bgfx createTexture wrappers that call the producer [V xref] [V live]

xref.py callers of 0xbc73770 = exactly {0xbc73bf0, 0xbc73ed0, 0xbc74120} [V]. Each wrapper builds a 0x1C descriptor (size field 0x1C, "TEX\0" magic `0x584554`, width/height u16s, name pointer, flags) and calls sub_bc73770 with rcx = [0x12AE1748] (bgfx::s_ctx), rdx = &handle, r8 = descriptor block, r9d = flags, then returns the handle (`movzx eax,word ptr [rsp+0x32]`).

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| "TEX" magic stamp (sub_bc73bf0) | [rsp+0x34] | 4 | W: `0xbc73dcc  mov dword ptr [rsp+0x34],0x584554` | descriptor magic "TEX\0" (0x584554) | [V] |
| "TEX" magic stamp (sub_bc73ed0 / sub_bc74120) | [rsp+0x3C] | 4 | W: `0xbc7401b  mov dword ptr [rsp+0x3C],0x584554` / `0xbc74266  mov dword ptr [rsp+0x3C],0x584554` | descriptor magic "TEX\0" (0x584554) | [V] |
| bgfx::s_ctx global | [0x12AE1748] | 8 | R: `0xbc73e8a  mov rcx,[0x12AE1748]` (sub_bc73bf0) / `0xbc740d8  mov rcx,[0x12AE1748]` (sub_bc73ed0) / `0xbc7432e  mov rcx,[0x12AE1748]` (sub_bc74120) | context passed to the producer [V: BGFX_MAP 6r = bgfx::s_ctx] | [V] |
| handle out-pointer | [rsp+0x32] | 8/2 | R: `0xbc73e9d  lea rdx,[rsp+0x32]` / `0xbc73ead  movzx eax,word ptr [rsp+0x32]` | &handle passed to producer; handle read back as the wrapper's return | [V] |
| descriptor block arg | r8 | - | `0xbc73ea2  mov r8,r14` | descriptor block passed to producer | [V] |
| flags arg | r9d | - | `0xbc73ea5  mov r9d,esi` | flags passed to producer | [V] |
| producer call | 0xbc73ea8 | - | `0xbc73ea8  call 0xBC73770` | sub_bc73bf0 -> sub_bc73770 (the live-call site) | [V] |
| wrapper epilogue | 0xbc73ecd | - | `0xbc73ecd  ret` | handle returned to the dragon-entry caller | [V] |

Live: capture `bgfx_createtexture_producer` (rva=0xBC73770) — all 16 hits `ret=0xBC73EAD`, i.e. the instruction immediately after `0xbc73ea8 call 0xBC73770` in sub_bc73bf0 [V live: docs/data/live/bgfx_createtexture_producer.txt, hit=1..16]; RDX=0x14C8D2 on entry, R8 = descriptor block beginning with "TEX\0". Separately `bgfx_texture_wrapper_bc73bf0.txt`: `CALLER ret=0xC296D7E` — dragon entry 0xc296b50 calls sub_bc73bf0 [V live].

### (3) Dragon entries that reach the wrappers [V xref]

xref.py callers of the wrappers (and of 0xc297000 per the hint's entry list):
- 0xbc63c80 -> {0xbc634b0} [V]; BGFX_MAP 6ai labels 0xbc63c80 TextVideoMemBlitter/debug-font setup [I].
- 0xc296b50 -> {0xbc41420, 0xbc42740, 0xbc432e0, 0xbc43550, 0xbc44120} [V].
- 0xc2a3d90 -> {0xc2a2d30} [V].
- 0xc297000 -> {0xc2aef20} [V].

All caller RVAs are engine/dragon-internal (0xbc4xxxx, 0xc2xxxx, 0xbc634b0); none is Minecraft texture code (texgroup_load 0x5421c90, 0x58CA10, sub_a3f10, 0x18718d0 never call them [V xref]). So the producer is reached from dragon entries via thin wrappers, NOT from the Minecraft ClientTexture/BedrockTexture/TexturePtr init path.

### (4) Dispatcher case byte 14 — consume side (how the descriptor is filled from the command stream) [V]

sub_bc68c00 is the command loop; sub_bc63150's render-thread frame step consumes the buffer (`0xbc6337b call 0xBC68E40` on buffer +0xDC5818, `0xbc633c4 call 0xBC68E40` on buffer +0xE05820 [V]). Case head 0xbc69487 decodes the command stream into stack fields via `call 0xEBCE390` copies, then compares the 4-byte magic:

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| case head | 0xbc69487 | - | `0xbc69487  and edx,0xFFFFFFFE` / `0xbc6948a  add edx,2` / `0xbc6948d  mov [rsi],edx` | command-byte 14 case head (cursor advance, [rsi] = cursor var) [I per hint mapping] | [V] |
| handle field | [rsp+0x6E] | 2 | W: `0xbc69492  lea rcx,[rsp+0x6E]` / `0xbc69497  mov r8d,2` / `0xbc6949d  call 0xEBCE390` / R: `0xbc6a2a9  movzx edx,word ptr [rsp+0x6E]` | handle u16 decoded from command stream | [V] |
| flags byte | [rsp+0x6A] | 1 | W: `0xbc694e9  lea rcx,[rsp+0x6A]` / `0xbc694ee  mov r8d,1` / `0xbc694f4  call 0xEBCE390` | 1 flag byte decoded from command stream | [V] |
| descriptor pointer field | [rsp+0x60] | 8 | W: `0xbc694af  lea rcx,[rsp+0x60]` / `0xbc694b4  mov r8d,8` / `0xbc694ba  call 0xEBCE390` / R: `0xbc6a2a4  mov r8,[rsp+0x60]` | descriptor pointer u64 decoded from command stream | [V] |
| magic field | [rsp+0x8C] | 4 | W: `0xbc6955d  lea rcx,[rsp+0x8C]` / `0xbc69565  mov r8,r15` / `0xbc69568  call 0xEBCE390` / R: `0xbc695a3  cmp dword ptr [rsp+0x8C],0x584554` / `0xbc695ae  jne 0xBC6A28C` | 4-byte magic compared to "TEX" (0x584554) [I]; "TEX" falls through to create-path prep, else default path | [V] |
| TEX-path create body | [rax+0x1C0] | 8 | R: `0xbc69693  mov rax,[rcx]` / `0xbc69696  mov rax,[rax+0x1C0]` / `0xbc6969d  call qword ptr [0xF99FFA0]` | TextureD3D12::create body vtable+0x1C0 ("TEX" path) [I] | [V] |
| default-path rendererCtx | [rdi+0x1EBF2D0] | 8 | R: `0xbc6a28f  mov rcx,[rdi+0x1EBF2D0]` | renderer-context object (vcall receiver) | [V] |
| vtable slot 26 | [rax+0xD0] | 8 | R: `0xbc6a2ae  mov rax,[rcx]` / `0xbc6a2b1  mov rax,[rax+0xD0]` | vtable+0xD0 = RendererContext slot 26 = createTexture 0xe8143c0 [I: vtable map BGFX_MAP 6k] | [V] |
| createTexture vcall | 0xbc6a2c2 | - | `0xbc6a2c2  call qword ptr [0xF99FFA0]` | args rdx=handle ([rsp+0x6E]), r8=desc ptr ([rsp+0x60]), r9d=[rsp+0x90] [I] | [V] |
| createTexture return | 0xbc6a2c8 | 8 | `0xbc6a2c8  test rax,rax` / `0xbc6a2d1  mov r15,rax` | ID3D12Resource* in r15; ret=0xBC6A2C8 is exactly the live-capture return address [V live] | [V] [V live] |
| resource store | [r8+0x10] / [rcx+0x10] | 8 | W: `0xbc6a498  add r8,r9` / `0xbc6a49b  mov [r8+0x10],r15` / `0xbc6a58d  mov [r8+0x10],r15` / `0xbc6a577  mov [rcx+0x10],r15` | ID3D12Resource* stored into the handle record at +0x10 (inline and paged paths) [I] | [V] |
| post-create resource vcall | [rax+0x140] | 8 | R: `0xbc6a3b6  mov rax,[rax+0x140]` / `... call qword ptr [0xF99FFA0]` | vtable+0x140 on the created resource [I] | [V] |

Live: capture `createtexture_callers` (rva=0xE8143C0) — `ret=0xBC6A2C8`, 25 hits [V live: docs/data/live/createtexture_callers.txt]; RCX = renderer context (0x5314A010000); R8 = 0x1C descriptor beginning "TEX\0" + texture name pointers ("sideTex", "world_download_default", textures/ui/...). So createTexture slot 26 (0xe8143c0) IS issued at runtime via command byte 14 -> handler 0xbc69487 -> default path -> vtable+0xD0 vcall. [V + V live]

### (5) Trace of the returned handle into TexturePtr/ClientTexture — NOT statically reachable [?]

sub_bc73770 writes the handle out (`mov [rsi],di`) and the wrapper returns it (`movzx eax,word ptr [rsp+0x32]`) to its dragon-entry caller. What 0xc296b50 / 0xc2a3d90 / 0xbc63c80 do with the returned handle is undecoded, and none of them is reachable from Minecraft texture code statically (Table 12 above). The wrappers ignore createTexture's returned ID3D12Resource*, so no GPU-handle write into a Minecraft texture object is instruction-visible anywhere. xref.py callers 0xe8143c0 = EMPTY [V r2-r5]; texture-object init vtable 0xEFCA580 slot 4 (sub_a3f10) only swaps live vtables and never calls createTexture or any wrapper [V r2]. Hence the Minecraft-side handle write (which TexturePtr/ClientTexture/BedrockTexture field receives the created handle, reached from texgroup_load 0x5421c90 -> cache 0x18718d0) has no [V] instruction row. [?]

## CLOSES?

NO — blocking fact: the createTexture issuance itself is now fully proven (producer sub_bc73770 writes command byte 0x0E `0xbc73aaa mov byte ptr [rbp+0x2C],0xE` [V]; thin wrappers 0xbc73bf0/0xbc73ed0/0xbc74120 call it [V xref]; live call ret=0xBC73EAD at `0xbc73ea8 call 0xBC73770` in sub_bc73bf0 [V live]; dispatcher default path `0xbc6a2ae mov rax,[rcx]` / `0xbc6a2b1 mov rax,[rax+0xD0]` / `0xbc6a2c2 call qword ptr [0xF99FFA0]` with live ret=0xBC6A2C8 [V live + V]); BUT there is still no static path from Minecraft-side texture code to this issuance and no [V]-proven write of the GPU handle into TexturePtr/ClientTexture: xref.py callers of 0xe8143c0 = EMPTY (only indirect [vptr+0xD0]); sub_bc73770's only static callers are the three thin wrappers, whose only static callers are dragon entries 0xc296b50/0xc2a3d90/0xbc63c80 (callers 0xbc41420/0xbc42740/0xbc432e0/0xbc43550/0xbc44120, 0xc2a2d30, 0xbc634b0, 0xc2aef20 — all engine-internal, none Minecraft texture code [V xref]); texture-object init vtable 0xEFCA580 slot 4 (sub_a3f10) never calls createTexture or any wrapper [V]; the wrappers return the handle to their dragon-entry caller and ignore createTexture's returned ID3D12Resource*, so the handle write into a Minecraft texture object is not instruction-visible [?]. The sampler half (6ax) [V] and the D3D12 backend texture-management chain [V] are already proven (r1 Tables 1-8); atlas stitchers are tracked by L8a/L8b (oc_U-EL8a/oc_U-EL8b). The pending half of L7e therefore cannot be closed by this unit.

## TOOL REQUESTS

- None (rdis dis + xref.py callers only; no helper scripts written, no temporary files left behind).
