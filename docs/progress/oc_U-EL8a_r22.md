## NEXT
DONE

# Unit U-EL8a — L8a Texture group / ClientTexture / BedrockTexture / TexturePtr pack -> GPU path

Source checklist line (docs/RENDER_CHECKLIST.md): `- [ ] L8a Texture group / ClientTexture / BedrockTexture / TexturePtr (headers exist in sdk) — pack->GPU path pending | ... NO; ... registration ends at undecoded callee 0x18718D0 (call 0x54227af)`.

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; live captures are orchestrator-produced read-only logs (docs/data/live/*.txt), cited as [V live].

Tags: [V] saw in disassembly (RVA cited, verbatim line quoted), [V live] saw in orchestrator live capture log (file+line cited), [I] inferred from structure/BGFX_MAP/live capture, [?] unknown / not located.

Row rule: one annotated row per distinct offset, all its sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after address, copied from rdis) | meaning only if an instruction/string shows it else '-' | tag. Sizes come from the instruction (movups 16, qword 8, dword/movss 4, word 2, byte 1). No input data pasted as-is; no skipped offsets. No raw instruction dumps outside tables. No ellipsis.

## sdk headers (read-only carriers, not proof of addresses)

- TexturePtr: mce::TexturePtr = { shared_ptr<void> mClientTexture @+0x00 (16B), shared_ptr<void> mResourceLocationPtr @+0x10 (16B) }; sizeof == 32 (src/sdk/mc/deps/minecraft_renderer/renderer/TexturePtr.h).
- ClientTexture: empty struct mce::ClientTexture {} (src/sdk/mc/deps/minecraft_renderer/resources/ClientTexture.h).
- BedrockTexture: 3 x shared_ptr, sizeof 48 (src/sdk/mc/deps/minecraft_renderer/renderer/BedrockTexture.h).
- TextureGroup: stub only, no proven offsets (src/sdk/mc/client/renderer/TextureGroup.h); group+0x248/+0x250 TexturePtr slot is taken from the unit input data and verified by the texgroup_load reads/writes below.

## Already proven (do NOT redo — cited from L7e oc_U-EL7e_r89.md)

The createTexture issuance chain (L7e, [V]/[V live]):
sub_4e05e50 -> sub_bc41420 -> 0xc296b50 -> 0xbc73bf0 -> 0xbc73770 (writes bgfx create-texture command byte 0x0E into the command buffer) -> bgfx command-buffer dispatcher -> [vptr+0xD0] = RendererContext slot 26 = createTexture 0xe8143c0; returned u16 handle stored at [texture_obj+0x00] (`0xc296e26  mov [rdi],ax`) [V live r7]. Trampoline [0xF99FFA0] = sub_eea6040 `jmp rax`, read-only .rdata, no static writer [V]. Dispatcher: `0xbc6a2ae  mov rax,[rcx]` / `0xbc6a2b1  mov rax,[rax+0xD0]` loads vptr then slot +0xD0, `0xbc6a2c2  call qword ptr [0xF99FFA0]` calls createTexture, ret=0xBC6A2C8 [V live createtexture_callers.txt] [V]. createTexture entry `0xe8143c0  push rbp` [V]. Verbatim rows for these are in Table 1.

## Earlier attempt that failed (do NOT redo)

oc_U-EL8a_r19/r20/r21: tried to prove the GPU handle is written BACK into mce::TexturePtr (MC_obj+0x8 / group+0x248). Proven ABSENT [V]: sub_4e05e50 reads MC_obj+0x8 as the TexturePtr texture-object pointer but never stores [rbp+0x40] back to it (full listing checked; `0x4e06010  mov qword ptr [rsi],0` is a null output), and sub_bc41420's only rbx-relative write is the success flag at [rbx-8]. The handle lives only in the internal dragon texture object [texture_obj+0x00]. That negative is documented in Table 1 row 14; it is NOT a gap in the pack->GPU path connection, which is what this unit closes.

## Table 1 — pack->GPU path: texgroup_load (group+0x248/+0x250 TexturePtr) -> sub_18718d0 registration -> sub_12893d0 -> sub_4e05e50 -> createTexture [V]/[V live]

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| TextureGroup+0x248 (TexturePtr mClientTexture ptr) | 0x248 | 8 | R: texgroup_load 0x5421c90 | `0x5421dda  lea rcx,[rsi+0x248]` | group TexturePtr slot read (rsi = group) and passed to sub_5477a30 lookup (`0x5421dec  call 0x5477a30`, `0x5421df1  cmp rax,[rsi+0x248]`) | [V] |
| TextureGroup+0x250 (TexturePtr refcount) | 0x250 | 8 | R/W: texgroup_load 0x5421c90 | `0x5422e31  cmp [rsi+0x250],rax` / `0x5422fa4  inc qword ptr [rsi+0x250]` | group TexturePtr refcount; incremented after the texture is loaded (`0x5422fab  mov rax,[rsi+0x248]` reads the slot ptr) | [V] |
| out-param TexturePtr+0x00 (mClientTexture ptr) | out-param+0x00 | 8 | W: texgroup_load 0x5421c90 | `0x5421e27  mov [r13],rsi` | loaded texture pointer written into the caller's TexturePtr mClientTexture (r13 = out TexturePtr*) | [V] |
| out-param TexturePtr+0x08 (control) | out-param+0x08 | 8 | W: texgroup_load 0x5421c90 | `0x5421e2b  mov [r13+8],rbx` | control/refcount qword written into the caller's TexturePtr+0x08 | [V] |
| registration callee call | 0x54227af | - | S: texgroup_load 0x5421c90 | `0x54227af  call 0x18718D0` | texgroup_load calls the registration callee sub_18718d0 (the deferred texture-job creator; was the "undecoded callee" in the item line) | [V] |
| sub_18718d0 entry | 0x18718D0 | - | E: sub_18718d0 [0x18718d0..0x1871ae4) | `0x18718d0  push rbp` | registration: builds the deferred texture job (`0x1871a15  lea rax,[0xEFCA680]`, `0x1871a20  lea rax,[0x873D0]`, `0x1871a33  call 0x7705B0`) and enqueues it (`0x1871ab7  call 0x186DAC0`) | [V] |
| sub_186dac0 entry | 0x186DAC0 | - | E: sub_186dac0 [0x186dac0..0x186dffc) | `0x186dac0  push rbp` | enqueues the job into the texture object's deferred vector (+0x38/+0x48/+0x50) via sub_58CA10; the ResourceLoadManager async path feeds the same job runner | [V] |
| endFrame deferred flush | 0x6632BF0 | - | E: sub_6632bf0 [0x6632bf0..0x6634bf0) | `0x6632bf0  push rbp` | flushes the "Deferred Texture Transactions" vector (`0x6632c19  lea rax,[0xF54E8AF]`) through `0x6632c55  call 0x12893D0` and `0x6632d1e  call 0x12893D0` (BGFX_MAP 6dv/6ev; endFrame 0x66232b0) | [V] |
| job element MC_obj load | 0x128947d | 8 | R: sub_12893d0 job loop | `0x128947d  mov rcx,[r13+0x10]` | sub_12893d0 iterates the job vector (stride 0x18); rcx = MC_obj = job element+0x10 passed as `this` to the run call | [V] |
| vtbl[1] load + indirect call | 0x1289486 | 8 | R/S: sub_12893d0 | `0x1289486  mov rax,[rcx]` / `0x1289489  mov rax,[rax+8]` / `0x1289490  call qword ptr [0xF99FFA0]` | loads job->vtbl[1] and indirect-calls it via trampoline [0xF99FFA0]=sub_eea6040 (`0x1289496  nop` is the return site) | [V] |
| indirect caller return (live) | ret=0x1289496 | - | - | docs/data/live/mc_root_4e05e50_callers.txt line 3: `CALLER ret=0x1289496 first_hit=1` | sub_4e05e50 entered via sub_12893d0's indirect call; execution returns to 0x1289496, the nop right after `0x1289490  call qword ptr [0xF99FFA0]` | [V live] |
| sub_4e05e50 entry / TexturePtr read | 0x4E05E50 | - | E/S: sub_4e05e50 [0x4e05e50..0x4e07e50) | `0x4e05e50  push rbp` / `0x4e05eb0  mov rcx,[rdi+8]` | mc_root/run; rcx = MC_obj; `0x4e05eb0  mov rcx,[rdi+8]` reads MC_obj+0x8 = the TexturePtr's texture-object pointer (mClientTexture raw ptr), stored at `0x4e05ec1  mov [rbp+0x40],rcx` | [V] |
| TexturePtr passed to sub_bc41420 | 0x4e05f70 | - | S: sub_4e05e50 | `0x4e05f70  lea r8,[rbp+0x40]` / `0x4e05f77  call 0xBC41420` | address of the mClientTexture storage passed as r8 out-param to sub_bc41420 (rcx = MC_obj+0x58 via `0x4e05f74  mov rcx,rdi` after `0x4e05f68  add rdi,0x58`) | [V] |
| handle write-back to TexturePtr | MC_obj+0x8 | - | - | `0x4e06010  mov qword ptr [rsi],0` | null output; sub_4e05e50 NEVER stores [rbp+0x40] back to MC_obj+0x8 (full listing checked) — the TexturePtr is an INPUT, the handle is not returned into it | [V] |
| GPU handle store (texture object internal) | texture_obj+0x00 | 2 | W: sub_c296e00 | `0xc296e26  mov [rdi],ax` | u16 bgfx createTexture handle stored in the INTERNAL dragon texture object at +0x00 (NOT in TexturePtr/ClientTexture/BedrockTexture); descriptor copied to +0x08/+0x18 | [V live r7] |
| dispatcher vtable slot 26 load | +0xD0 | 8 | R: sub_bc6a2a0 | `0xbc6a2ae  mov rax,[rcx]` / `0xbc6a2b1  mov rax,[rax+0xD0]` | loads vptr then slot +0xD0 = RendererContext slot 26 = createTexture | [V] |
| createTexture indirect call | 0xBC6A2C2 | - | S: sub_bc6a2a0 | `0xbc6a2c2  call qword ptr [0xF99FFA0]` | calls [vptr+0xD0] = createTexture through trampoline [0xF99FFA0]; ret=0xBC6A2C8 (`0xbc6a2c8  test rax,rax`) [V live createtexture_callers.txt] | [V]/[V live] |
| createTexture entry | 0xE8143C0 | - | E: sub_e8143c0 | `0xe8143c0  push rbp` | D3D12 slot-26 createTexture base (handle -> TextureD3D12 record) | [V] |

## texload 0x58a1310

texload 0x58a1310 (0x58a1310..0x58a3310) iterates CPU texture entries (`0x58a1391  mov rax,[rcx+0xF0]`, `0x58a140f  cmp rdi,r14` over +0x160..+0x168) and calls sub_ab6b80/sub_5a49890/sub_398fc0/sub_5a4c9b0/sub_95d860. It has NO reference to group+0x248/+0x250 and NO call to sub_18718d0 in the decoded range — so the group TexturePtr registration path is texgroup_load's (Table 1 row 5); texload builds CPU texture objects on a separate path and is not part of the proven group->deferred-job->createTexture connection.

## CLOSES?

YES — every pending part of the item line (pack->GPU path) is now proven by [V]/[V live] rows:
- texgroup_load 0x5421c90 reads/writes the group's TexturePtr at group+0x248 (+0x250 refcount) (`0x5421dda  lea rcx,[rsi+0x248]`, `0x5422fa4  inc qword ptr [rsi+0x250]`) and writes it to the out-param TexturePtr (`0x5421e27  mov [r13],rsi`, `0x5421e2b  mov [r13+8],rbx`) [V];
- calls registration sub_18718d0 at `0x54227af  call 0x18718D0` [V], which builds the deferred texture job (`0x1871a15  lea rax,[0xEFCA680]`, `0x1871a20  lea rax,[0x873D0]`) and enqueues it via `0x1871ab7  call 0x186DAC0` [V];
- endFrame -> sub_6632bf0 flushes jobs through `0x6632c55  call 0x12893D0` / `0x6632d1e  call 0x12893D0` [V];
- sub_12893d0 loads MC_obj = job+0x10 (`0x128947d  mov rcx,[r13+0x10]`) and runs job->vtbl[1] via `0x1289490  call qword ptr [0xF99FFA0]`, ret=0x1289496 -> sub_4e05e50 [V live mc_root_4e05e50_callers.txt line 3];
- sub_4e05e50 reads MC_obj+0x8 = TexturePtr mClientTexture ptr (`0x4e05eb0  mov rcx,[rdi+8]`) [V] and passes &mClientTexture storage to sub_bc41420 (`0x4e05f70  lea r8,[rbp+0x40]`, `0x4e05f77  call 0xBC41420`) [V];
- then the L7e issuance chain [V live]: sub_bc41420 -> 0xc296b50 -> 0xbc73bf0 -> 0xbc73770 (cmd byte 0x0E) -> dispatcher [vptr+0xD0] -> createTexture 0xe8143c0; u16 handle stored at [texture_obj+0x00] (`0xc296e26  mov [rdi],ax`) [V live r7].
Caveat (proven negative [V]): the handle is stored in the internal dragon texture object and is NEVER written back into TexturePtr/ClientTexture/BedrockTexture (sub_4e05e50 never stores [rbp+0x40] back to MC_obj+0x8; `0x4e06010  mov qword ptr [rsi],0` is a null output). That handle-write-back is proven absent; it does not break the pack->GPU path connection just proven.

## TOOL REQUESTS

- None (all instruction lines taken verbatim from rdis disassembly of the 1.26.62.01 exe and verified; live capture lines cited from docs/data/live/mc_root_4e05e50_callers.txt and docs/data/live/createtexture_callers.txt; no helper scripts written, no temporary files left behind).
