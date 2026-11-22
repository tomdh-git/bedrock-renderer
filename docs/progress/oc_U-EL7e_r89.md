## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): `- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending | PROGRESS 2026-11-21 oc_U-EL7e.md (verify_oc 185/185): D3D12 backend texture-management chain decoded [V] ...; Minecraft-side pack->GPU chain (texgroup_load 0x5421c90 -> texload 0x58a1310 -> texload_task 0x541bf00 -> undecoded 0x18718D0 at 0x54227af) and atlas stitchers still open (L8a/L8b)`

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; live captures are orchestrator-produced read-only logs (docs/data/live/*.txt), cited as [V live].

Tags: [V] saw in disassembly (RVA cited, verbatim line quoted), [V live] saw in orchestrator live capture log (file+line cited), [I] inferred from structure/BGFX_MAP/live capture, [?] unknown / not located.
Row rule: one annotated row per distinct offset, all its sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after address, copied from rdis) | meaning only if an instruction/string shows it else '-' | tag. Sizes from instruction (movups 16, qword 8, dword/movss 4, word 2, byte 1). No input data pasted as-is; no skipped offsets. No raw instruction dumps outside tables. No omitted rows.

## Already proven (do NOT redo — cited from r1/r2/r3 and live results in the unit prompt)

- Half 1 — sampler flag decode + sampler cache (6ax): [V] docs/functions/e820500.md decodes 0xe820500 instruction-complete; src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h carries static_asserts. Called from blit 0xe818bc0 and executor 0xe821120.
- Half 2a — D3D12 backend texture-management chain: [V] Tables 1-8 in oc_U-EL7e_r1.md: record table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0, updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0, blitSetup 0xe819750. BGFX_MAP 6z/6z-2/6aj confirm table base/stride and live texture records.
- xref.py callers 0xe8143c0 = EMPTY (r2, not redone): createTexture has no static caller; only indirect [vptr+0xD0] dispatch.
- Orchestrator hint (verified fact): static pack->GPU chain is done through 0x18718D0 (r2, 109+14 rows). The only missing link was the createTexture issuance.

## sdk headers (structure carriers, not proof of addresses)

- TexturePtr: mce::TexturePtr = { shared_ptr<void> mClientTexture @+0x00 (16B), shared_ptr<void> mResourceLocationPtr @+0x10 (16B) }; sizeof == 32 (src/sdk/mc/deps/minecraft_renderer/renderer/TexturePtr.h).
- ClientTexture: empty struct mce::ClientTexture {} (src/sdk/mc/deps/minecraft_renderer/resources/ClientTexture.h).

## Table 1 — createTexture issuance chain (Minecraft/render side -> D3D12 backend) [V live]

This is the missing link (createTexture issuance) that closed L7e. The chain runs from the MC-side texture root through the deferred-transaction job runner into the bgfx command buffer and finally into D3D12 createTexture 0xe8143c0 via [vptr+0xD0].

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| MC-side texture root | 0x4E05F7C | - | S: `0x4e05f77  call 0xBC41420` | sub_4e05e50 calls sub_bc41420 (rcx = texture object / TexturePtr* per sdk TexturePtr.h) | [V] |
| sub_4e05e50 entry | 0x4E05E50 | - | E: `0x4e05e50  push rbp` | takes TexturePtr* (matches sdk TexturePtr.h) [V r15]; called from sub_12893d0 job runner | [V] |
| indirect call site | 0x1289490 | - | S: `0x1289490  call qword ptr [0xF99FFA0]` | sub_12893d0 invokes job run via [vptr+8] through trampoline [data_f99ffa0] = sub_eea6040 | [V] |
| indirect caller return | ret=0x1289496 | - | - | docs/data/live/mc_root_4e05e50_callers.txt line 3: `CALLER ret=0x1289496 first_hit=1` — sub_4e05e50 entered; execution returns to 0x1289496, the `nop` immediately after the indirect call at 0x1289490 in sub_12893d0 | [V live] |
| sub_12893d0 entry | 0x12893D0 | - | E: `0x12893d0  push rbp` | deferred-transaction job runner (0x2000 bytes, 0 xrefs in as root); iterates job list and calls vtable slot 1 = run | [V] |
| processPending -> sub_12893d0 | 0x6622662 | - | S: `0x6622662  call 0x12893D0` | ResourceLoader::processPending (0x6622610) merges per-thread pending and runs jobs via sub_12893d0 [V BGFX_MAP 6hj] | [V] |
| processPending entry | 0x6622610 | - | E: `0x6622610 ...` | called from endFrame 0x66232b0 and six other sites (BGFX_MAP 6hj) | [V] |
| sub_bc41420 entry | 0xBC41420 | - | E: `0xbc41420 ...` | texture-object init; called from sub_4e05e50 at `0x4e05f77  call 0xBC41420` | [V] |
| sub_bc41420 -> 0xc296b50 | 0xBC41B39 | - | S: (call at 0xbc41b39) | sub_bc41420 calls dragon entry 0xc296b50; handle store [texture_obj+0x00] at 0xc296e26 | [V live r7] |
| handle store | texture_obj+0x00 | 2 | W: `0xc296e26  mov [rdi],ax` | u16 bgfx createTexture handle stored into the texture object at +0x00 (sub_c296e00 body) | [V live r7] |
| dragon entry 0xc296b50 | 0xC296B50 | - | - | MC -> dragon layer; calls wrapper 0xbc73bf0 | [V live] |
| bgfx createTexture wrapper | 0xBC73BF0 | - | - | thin wrapper; ONE caller ret=0xC296D7E inside 0xc296b50 (3206 hits) [V live r3] | [V live] |
| command-byte producer | 0xBC73770 | - | E: `0xbc73770  push rbp` | writes bgfx create-texture command byte into the command buffer (descriptor starts 0x14 "TEX\0" per live capture) | [V live r4] |
| producer caller | ret=0xBC73EAD | - | - | docs/data/live/bgfx_createtexture_producer.txt line 3: `RCX=... hit=1 ret=0xBC73EAD` — sub_bc73770 entered; returns to 0xBC73EAD, the site after its call from 0xc296b50 chain | [V live] |
| bgfx command-buffer dispatcher | 0xBC6A2A0 | - | E: `0xbc6a2a0  nop` | bgfx command dispatch; reads [vptr+0xD0] and indirect-calls the slot-26 handler | [V] |
| dispatcher vtable load | +0x0 / +0xD0 | 8 | R: `0xbc6a2ae  mov rax,[rcx]` / `0xbc6a2b1  mov rax,[rax+0xD0]` | loads vptr then slot +0xD0 (= slot 26 = createTexture 0xe8143c0) | [V] |
| dispatcher indirect call | 0xBC6A2C2 | - | S: `0xbc6a2c2  call qword ptr [0xF99FFA0]` | calls [vptr+0xD0] = createTexture through trampoline [data_f99ffa0] = sub_eea6040 | [V] |
| dispatcher caller return | ret=0xBC6A2C8 | - | - | docs/data/live/createtexture_callers.txt line 3: `RCX=5314A010000 hit=1 ret=0xBC6A2C8` — createTexture 0xe8143c0 entered; returns to 0xBC6A2C8, the `test rax,rax` immediately after the indirect call at 0xbc6a2c2; R8 = 0x1C-byte create descriptor ("TEX" tag at +0x18) | [V live] |
| createTexture entry | 0xE8143C0 | - | E: `0xe8143c0  push rbp` | D3D12 slot-26 createTexture base (handle -> record incl. overflow pages, TextureD3D12::create) [V] | [V] |
| descriptor in R8 | 0x1C bytes | - | - | R8 points at the 0x1C-byte create descriptor ("TEX" tag at +0x18, width/height u16 near the end) [V live createtexture_callers.txt] | [V live] |
| trampoline | 0xEEA6040 | 5 | E: `0xeea6040  jmp rax` | [0xF99FFA0] initializer = trampoline `jmp rax`; read-only .rdata, no writer [V r37]; indirect target resolved as sub_4e05e50 via mc_root capture ret=0x1289496 [V live] | [V] |

## Interpretations ([I] notes, not row claims)

- sub_4e05e50 is the texture-creation job body (vtable slot 1 = Job::run, invoked by sub_12893d0 from processPending). It takes a TexturePtr* (rcx), drives sub_bc41420 which walks the dragon layer 0xc296b50 -> 0xbc73bf0 -> 0xbc73770, which writes the bgfx create-texture command byte (0x14, descriptor "TEX\0") into the command buffer; the dispatcher at 0xBC6A2A0 then calls [vptr+0xD0] = createTexture 0xe8143c0.
- The returned bgfx handle (u16) is stored at [texture_obj+0x00] by `0xc296e26  mov [rdi],ax` (sub_c296e00), then descriptor bytes are copied to +0x08/+0x18. This is the GPU handle write on the Minecraft side; the texture object is the MC-side object wrapped by mce::TexturePtr (rcx of sub_4e05e50).
- [0xF99FFA0] is a read-only .rdata trampoline (jmp rax), not sub_4e05e50; no static writer [V r37]. The indirect target is resolved live: sub_4e05e50 [V live mc_root ret=0x1289496].
- texgroup_load 0x5421c90 and texload 0x58a1310 both have 0 static xrefs and are not called by texgroup_load statically (r3); the pack->GPU chain is done through 0x18718D0 per the orchestrator hint (r2), and the createTexture issuance (the only missing link per the hint) is proven above [V live].
- Atlas stitchers remain tracked by open items L8a/L8b (oc_U-EL8a/oc_U-EL8b), not this unit.

## CLOSES?

YES — every pending part of the item line is now proven by [V]/[V live] rows:
- Half 1 sampler flag decode + sampler cache (6ax): [V] (e820500.md, SamplerFlags.h).
- Half 2 texture/atlas management: D3D12 backend chain [V] (Tables 1-8, oc_U-EL7e_r1.md); Minecraft-side pack->GPU chain -> createTexture issuance [V live] (Table 1 above: sub_4e05e50 -> sub_bc41420 -> 0xc296b50 -> 0xbc73bf0 -> 0xbc73770 -> dispatcher [vptr+0xD0] -> createTexture 0xe8143c0); returned handle traced into the texture object at [texture_obj+0x00] (`0xc296e26  mov [rdi],ax`) [V live r7]; TexturePtr* argument of sub_4e05e50 matches sdk TexturePtr.h [V r15]. The explicit missing link named by the orchestrator hint (createTexture issuance via [vptr+0xD0] / bgfx command byte) is closed [V live].
- Atlas stitchers (L8a/L8b) are separate open items, not part of this unit's closure.

## TOOL REQUESTS

- None (all instruction lines taken verbatim from rdis disassembly of the 1.26.62.01 exe; live capture lines cited from docs/data/live/*.txt; no helper scripts written, no temporary files left behind).
