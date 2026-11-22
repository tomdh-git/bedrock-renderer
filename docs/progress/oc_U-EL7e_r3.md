## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): `- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending | PROGRESS 2026-11-21 oc_U-EL7e.md (verify_oc 185/185): D3D12 backend texture-management chain decoded [V] ...; Minecraft-side pack->GPU chain (texgroup_load 0x5421c90 -> texload 0x58a1310 -> texload_task 0x541bf00 -> undecoded 0x18718D0 at 0x54227af) and atlas stitchers still open (L8a/L8b)`

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only.

Tags: [V] saw in disassembly (RVA cited, verbatim line quoted), [I] inferred from structure/BGFX_MAP, [?] unknown / not located.
Row rule: one annotated row per distinct offset, all its sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after address, copied from rdis) | meaning only if an instruction/string shows it else '-' | tag. Sizes from instruction (movups 16, qword 8, dword/movss 4, word 2, byte 1). No input data pasted as-is; no skipped offsets. No raw instruction dumps outside tables.

## Already proven (do NOT redo — cited from r1/r2 / verified files)

- Half 1 — sampler flag decode + sampler cache (6ax): [V] docs/functions/e820500.md decodes 0xe820500 instruction-complete; src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h carries static_asserts. Called from blit 0xe818bc0 and executor 0xe821120.
- Half 2a — D3D12 backend texture-management chain: [V] Tables 1-8 in oc_U-EL7e_r1.md: record table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0, updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0, blitSetup 0xe819750. BGFX_MAP 6z/6z-2/6aj confirm table base/stride and live texture records.
- BGFX_MAP 6z: texture record fields (live-verified): +0x00 qword, +0x08 u32 state/type, +0x18 width u32, +0x20 height u32 +0x24 flags, +0x28 DXGI_FORMAT, +0x2c u32, +0x98 flags, +0x9C width, +0xA0 height, +0xAF requested format, +0xB0 actual format byte, +0xB1 numMips. Guard byte this+0xC96190; page list this+0xC96178; bounds check 0xe83abb0.
- r2 (not redone): xref.py callers 0xe8143c0 = EMPTY — createTexture has no static caller, only indirect [vptr+0xD0] thunks; static analysis cannot bind the pack->GPU hop to it.

## New angle taken this session (NOT redoing r1/r2)

Attack direction: the REVERSE link — backend functions that CALL the Minecraft cache 0x18718d0, instead of assuming the cache hides createTexture. Precomputed input data (docs/progress/pre/, read fully, not re-run): pre/0x18718d0_fn.md (full 0x214-byte body, 29 xrefs in), pre/0x18718d0_callers.txt (25 callers incl. backend 0xe84070, 0xe85290, 0xe86630 and texgroup_load 0x5421c90), pre/0x5421c90_callers.txt (EMPTY), pre/0x58a1310_callers.txt (EMPTY), pre/0x186dac0_fn.md (completion callback body), pre/0xE84070_fn.md/.txt (full sub_e84070 body, 4 xrefs in).

Verbatim rdis results this session:
- `0x54227af  call 0x18718D0` — texgroup_load (0x5421c90..0x542359f, ret at 0x54231cc) calls the texture cache DIRECTLY; it never calls texload 0x58a1310 or texload_task 0x541bf00 statically. The item-line chain texgroup_load->texload->texload_task->0x18718d0 is NOT statically supported; texload/texload_task have no static callers (xref EMPTY) and were never decoded.
- `0xe84a62  call 0x18718D0` — sub_e84070 [0xe84070..0xe84da8) calls the Minecraft texture cache (rcx=[rbp+0x48] cache owner, rdx=[rbp+0x120] out ptr, r8d=9); afterwards it inserts {ptr,ptr} pairs into a table at [rcx+0x2E8] bumping count by 0x10 (`0xe84aa2  add qword ptr [rcx+0x2E8],0x10`) and calls 0xE87AC0 at 0xe84ab1.
- `0xe830ce  call 0xE84070`, `0xe83280  call 0xE84070`, `0xe834e3  call 0xE84070`, `0xe83695  call 0xE84070` — sub_e82e00 invokes sub_e84070 at four sites.
- `0xe837fa  call 0xE85290`, `0xe8395e  call 0xE85290` — sub_e82e00 also invokes sub_e85290 (xref lists 0xe85290 and 0xe86630 as additional callers of 0x18718d0; exact sites not re-verified verbatim).
- `0x914778  call 0xE863D0` — font-init root 0x914720 ("initWaitForDefaultFontsToLoad", string 0xF60228F at 0x91475f) calls sub_e863d0; roots 0x913b50 ("initDefaultFonts", 0xF544770 at 0x913b99) and 0x914890 ("initFontMetadata", 0xF60AFA4 at 0x9148c1) have no static callers and feed the same cluster.
- BGFX_MAP.md cites no RVA in the 0xe82e00..0xe86630 cluster (nearest named anchor: submit 0xe82e230), so these functions' names are not instruction-proven.

livemem: considered, not applicable — the gap is a static indirect-dispatch problem, not an unsettled live object value.

## Table 1 — Minecraft-side pack->GPU chain (proved [V] rows) plus the gap

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| texgroup_load entry | 0x5421c90 | - | E: `0x5421c90  push rbp` | pack->GPU chain entry (texture group load; 7 xrefs in; no static caller — root) | [V] |
| cache lookup call site | 0x54227af | - | S: `0x54227af  call 0x18718D0` | texgroup_load calls the Minecraft texture cache directly | [V] |
| cache BST root | this+0x30 | 8 | R: `0x18718fe  mov rcx,[rcx+0x30]` | cache object root pointer loaded | [V] |
| BST node live byte | node+0x19 | 1 | R: `0x1871906  cmp byte ptr [rdx+0x19],0` | node live byte; 0 keeps the BST walk going | [V] |
| BST node key | node+0x20 | 4 | R: `0x1871923  cmp [rdx+0x20],r8d` | node key compared with requested key | [V] |
| BST children | node+0x00/+0x10 | 8 | R: `0x1871933  mov rdx,[rdx+r9]` | left/right child pointer walk (idx 0 or 0x10 via shl r9d,4) | [V] |
| texture object from node | node+0x28 | 8 | R: `0x18719aa  mov rdi,[rax+0x28]` | texture object pointer taken from located node | [V] |
| control block | obj+0x10 | 8 | R: `0x18719b3  mov r14,[rdi+0x10]` | refcounted control block | [V] |
| entry list head | ctrl+0x60 | 8 | R: `0x18719b7  lea rbx,[r14+0x60]` | per-entry list head passed to 0xEEC59F0 | [V] |
| entry state vs ready sentinel | entry+0xAC | 4 | R: `0x18719cb  cmp dword ptr [r14+0xAC],0x7FFFFFFF` | entry state compared with ready sentinel 0x7FFFFFFF | [V] |
| next entry | entry+0xB8 | 8 | R: `0x18719dc  mov r14,[r14+0xB8]` | next entry in chain | [V] |
| cache lookup / allocate entry | 0xEEC59F0 / 0xEEC5A10 | - | S: `0x18719be  call 0xEEC59F0` / `0x18719e6  call 0xEEC5A10` | cache lookup / allocate entry | [V] |
| ready callback string | str 0xEFCA680 | - | R: `0x1871a15  lea rax,[0xEFCA680]` | ready-callback name string referenced | [V] |
| ready callback thunk | 0x873D0 | - | R: `0x1871a20  lea rax,[0x873D0]` | callback = thunk `0x873d0  jmp 0xEEC59D0` | [V] |
| callback registration | 0x7705B0 | - | S: `0x1871a33  call 0x7705B0` | register ready callback on cache entry | [V] |
| completion callback | 0x186DAC0 | - | S: `0x1871ab7  call 0x186DAC0` | cache lookup ends in the async completion callback | [V] |
| request block alloc | alloc 0x48 | 4 | S: `0x186dbae  mov edx,0x48` / `0x186dbb3  call qword ptr [0xF99FFA0]` | 0x48-byte request block allocated (allocator 0x1233E1A8) | [V] |
| desc builder | 0x58CA10 | - | S: `0x186dcf9  call 0x58CA10` | builds the texture load desc (0x190-byte desc, vtable 0xEFCA580 at desc+0x0) | [V] |
| async enqueue | 0x71BC70 | - | S: `0x186de55  call 0x71BC70` | ResourceLoadManager async enqueue ("resource dispatch", string 0xF5B0748 / 0xF820C35) | [V] |
| chain gap: texload / texload_task | 0x58a1310 / 0x541bf00 | - | - | named by the item line; xref.py callers EMPTY for both; never decoded; not called by texgroup_load statically | [?] |
| static Minecraft->GPU link (createTexture) | 0xe8143c0 | - | - | xref.py callers EMPTY (proven by r2, not redone); only indirect [vptr+0xD0] dispatch; no static path to GPU handle creation | [?] |

## Table 2 — New angle: backend/font-atlas -> Minecraft-cache adjacency (proved [V])

This is the only static connection found between the two halves; it is the REVERSE direction (backend reads the Minecraft cache), not the pack->GPU createTexture hop.

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| sub_e84070 entry | 0xe84070 | - | E: `0xe84070  push rbp` | backend function that calls the Minecraft texture cache | [V] |
| backend -> Minecraft cache | - | - | S: `0xe84a62  call 0x18718D0` | sub_e84070 calls the texture cache lookup | [V] |
| sub_e82e00 entry | 0xe82e00 | - | E: `0xe82e00  push rbp` | caller of sub_e84070/sub_e85290 (font-init cluster path) | [V] |
| sub_e82e00 -> sub_e84070 (four sites) | - | - | S: `0xe830ce  call 0xE84070` / `0xe83280  call 0xE84070` / `0xe834e3  call 0xE84070` / `0xe83695  call 0xE84070` | sub_e82e00 invokes the cache-consuming backend at four sites | [V] |
| sub_e82e00 -> sub_e85290 (two sites) | - | - | S: `0xe837fa  call 0xE85290` / `0xe8395e  call 0xE85290` | sub_e82e00 also invokes sub_e85290, another 0x18718d0 caller per xref | [V] |
| font-init root 0x914720 | 0x914720 | - | S: `0x914778  call 0xE863D0` | "initWaitForDefaultFontsToLoad" path (string 0xF60228F at 0x91475f) calls sub_e863d0 | [V] |
| font-init roots (no static callers) | 0x913b50 / 0x914890 | - | S: `0x913b99  lea rcx,[0xF544770]` / `0x9148c1  lea rcx,[0xF60AFA4]` | "initDefaultFonts" / "initFontMetadata" strings referenced | [V] |

## Interpretations ([I] notes, not row claims)

- The 0xe82e00/0xe84070/0xe85290 cluster is reached from font-init roots (0x913b50 initDefaultFonts, 0x914720 initWaitForDefaultFontsToLoad via 0xe863d0 at 0x914778, 0x914890 initFontMetadata) — a font/dynamic-atlas texture path that CONSUMES the Minecraft texture cache; its function names are not in BGFX_MAP.md and are not instruction-proven [I].
- Direction proved this session: backend -> Minecraft cache, the reverse of pack->GPU. The Minecraft->GPU write (which D3D12 texture record is created for which loaded texture, i.e. who calls createTexture with the loaded pixels) remains instruction-invisible [I].
- xref.py additionally lists 0xe85290 and 0xe86630 as callers of 0x18718d0 (caller-list finding; exact call sites not re-verified verbatim) [I].
- All [V] rows cite verbatim rdis lines of the 1.26.62.01 exe.

## What I tried that failed (new angles that did not close the gap)

- xref.py callers 0xe8143c0 (createTexture slot 26): EMPTY — no static caller, only indirect [vptr+0xD0] thunks (proven by r2; not redone per the no-redo rule).
- texload 0x58a1310 / texload_task 0x541bf00: xref.py callers EMPTY for both; never decoded; texgroup_load does not call them (its only cache-bound call is 0x54227af -> 0x18718d0).
- rdis/xref callers of 0xe82e00/0xe84070/0xe85290/0xe86630 lead only to font-init roots, not to createTexture or any texture-management slot.
- BGFX_MAP.md names nothing in the 0xe82e00..0xe86630 cluster — no named anchor to continue from statically.
- livemem: not applicable (static indirect-dispatch gap, not an unsettled live object value); no call made.

## CLOSES?

NO — blocking fact: no [V]-proven instruction path from the Minecraft-side pack->GPU chain to D3D12 GPU handle creation. What IS proved [V] (r1 + this session): sampler half (6ax) [V] via e820500.md/SamplerFlags.h; D3D12 backend texture-management chain [V] (Tables 1-8 of oc_U-EL7e_r1.md); texgroup_load 0x5421c90 -> texture cache 0x18718d0 at `0x54227af  call 0x18718D0` [V]; cache body/completion/enqueue decoded [V] (0x186dac0: 0x48 request block, allocator 0x1233E1A8, desc builder 0x58CA10, enqueue 0x71BC70); and the reverse adjacency backend->cache [V] (`0xe84a62  call 0x18718D0`, sub_e82e00 -> sub_e84070 at 0xe830ce/0xe83280/0xe834e3/0xe83695). What is NOT proved: createTexture 0xe8143c0 has no static caller (indirect [vptr+0xD0] only), texload 0x58a1310 and texload_task 0x541bf00 have no static callers and were never decoded, so the Minecraft->GPU hop (who creates the D3D12 handle/record for the loaded texture) has no [V] instruction row. Atlas stitchers are tracked by L8a/L8b (oc_U-EL8a/oc_U-EL8b), not this unit. The pending half of L7e therefore cannot be closed by this unit.

## TOOL REQUESTS

- verify_oc.py + delegate.py checks (used; no failures expected once line 2 is DONE). No new helper scripts written, no temporary files left behind; none needed.
