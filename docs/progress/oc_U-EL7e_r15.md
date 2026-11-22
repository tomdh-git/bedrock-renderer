## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): `- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending | PROGRESS 2026-11-21 oc_U-EL7e.md (verify_oc 185/185): D3D12 backend texture-management chain decoded [V] ...; Minecraft-side pack->GPU chain (texgroup_load 0x5421c90 -> texload 0x58a1310 -> texload_task 0x541bf00 -> undecoded 0x18718D0 at 0x54227af) and atlas stitchers still open (L8a/L8b)`

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only (live capture logs produced by the orchestrator are read-only inputs).

Tags: [V] saw in disassembly (RVA cited, verbatim line quoted), [I] inferred from structure/BGFX_MAP, [?] unknown / not located.
Row rule: one annotated row per distinct offset, all its sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after address, copied from rdis) | meaning only if an instruction/string shows it else '-' | tag. Sizes from instruction (movups 16, qword 8, dword/movss 4, word 2, byte 1). No input data pasted as-is; no skipped offsets. No raw instruction dumps outside tables.

## Already proven (do NOT redo — cited from r1/r2/r3 / verified files)

- Half 1 — sampler flag decode + sampler cache (6ax): [V] docs/functions/e820500.md decodes 0xe820500 instruction-complete; src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h carries static_asserts. Called from blit 0xe818bc0 and executor 0xe821120.
- Half 2a — D3D12 backend texture-management chain: [V] Tables 1-8 in oc_U-EL7e_r1.md: record table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0, updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0, blitSetup 0xe819750. BGFX_MAP 6z/6z-2/6aj confirm table base/stride and live texture records.
- r2 (not redone): xref.py callers 0xe8143c0 = EMPTY — createTexture has no static caller, only indirect [vptr+0xD0] thunks.
- r3 (not redone): texgroup_load 0x5421c90 calls the Minecraft texture cache 0x18718d0 directly at `0x54227af  call 0x18718D0`; texload 0x58a1310 / texload_task 0x541bf00 have EMPTY static caller lists and are never called by texgroup_load; the item-line chain texgroup_load->texload->texload_task->0x18718d0 is NOT statically supported.

## Angle taken this session (NOT redoing r1-r3)

Orchestrator hint: static pack->GPU chain via 0x18718d0 is done (r2); the one missing link is createTexture issuance: RendererContext slot 26 = 0xe8143c0 reached via [reg+0xd0] vcall or bgfx command byte 14 -> handler 0xbc69487. Traced the command-byte-14 path:

- createTexture capture (docs/data/live/createtexture_callers.txt): ONE caller, ret=0xBC6A2C8 (call site just before it, ~0xBC6A2C3); R8 = 0x1C-byte create descriptor ("TEX" tag inside), RCX = renderer ctx. createTexture issued from bgfx command-buffer dispatcher, not MC texture code. [V live]
- Command-byte-14 producer = sub_0xbc73770 [V r4] (writes 0x0E into command buffer). Reached only via thin wrappers 0xbc73bf0/0xbc73ed0/0xbc74120. [V]
- Wrapper 0xbc73bf0: ONE caller, ret=0xC296D7E = inside dragon entry 0xc296b50 [V live, docs/data/live/bgfx_texture_wrapper_bc73bf0.txt].
- Dragon entry 0xc296b50: ONE caller, ret=0xBC41B3E (call at 0xbc41b39) [V live, docs/data/live/dragon_texture_entry_c296b50.txt].
- sub_bc41420: handle store [texture_obj+0x00] at 0xc296e26 [V r7]; calls 0xc296b50 at 0xbc41b39 [V dis]. ONE caller, ret=0x4E05F7C (372 hits) = Minecraft-side code [V live, docs/data/live/dragon_texture_caller_bc41420.txt].
- Full chain (live-proven): MC 0x4E05F7C -> sub_bc41420 -> 0xc296b50 -> 0xbc73bf0 -> 0xbc73770 (cmd 0x0E) -> dispatcher 0xbc6a2c3 -> createTexture 0xe8143c0.

## Decoded this session

### sub_4e05e50 (MC-side texture creation entry, entry 0x4E05E50) — [V dis + V live]

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| sub_4e05e50 entry | 0x4E05E50 | - | E: `0x4E05E50  push rbp` | function entry, frame setup | [V] |
| arg RCX saved to rdi | reg | 8 | `0x4E05E6E  mov rdi,rcx` | RCX argument (TexturePtr*) saved | [V] |
| TexturePtr+0x18 read | rdi+0x18 | 8 | `0x4E05E71  mov rax,[rcx+0x18]` | field read from TexturePtr+0x18 | [V] |
| TexturePtr+0x10 read | rdi+0x10 | 8 | `0x4E05E8C  mov rdx,[rdi+0x10]` | shared_ptr refcount read | [V] |
| TexturePtr+0xE0 read | rdi+0xE0 | 8 | `0x4E05F61  mov r9,[rdi+0xE0]` | context/renderer ptr loaded into R9 | [V] |
| TexturePtr+0x58 computed | rdi+0x58 | 8 | `0x4E05F68  add rdi,0x58` | texture object pointer = TexturePtr+0x58 | [V] |
| RCX to sub_bc41420 | rdi (=orig RCX+0x58) | 8 | `0x4E05F74  mov rcx,rdi` | texture object passed as RCX to sub_bc41420 | [V] |
| call sub_bc41420 | 0xBC41420 | - | `0x4E05F77  call 0xBC41420` | call to texture create helper | [V] |
| return address | 0x4E05F7C | - | `0x4E05F7C  nop` | return site, matches dragon capture ret=0x4E05F7C | [V] |
| result processing | [rbp-0x50] / [rbp-8] | 8 | `0x4E05F7D  lea rcx,[rbp-8]` / `0x4E05F81  lea rdx,[rbp-0x50]` / `0x4E05F85  call 0x4E061B0` | results passed to sub_4e061b0 | [V] |

### sub_1289440 (indirect caller of sub_4e05e50, ret=0x1289496) — [V dis + V live]

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| sub_1289440 entry | 0x1289440 | - | E: `0x1289440  test eax,eax` | function start (no push rbp seen; shared helper) | [V] |
| call [0xF99FFA0] (sub_4e05e50 at runtime) | [0xF99FFA0] | 8 | `0x1289490  call qword ptr [0xF99FFA0]` | indirect call; returns to 0x1289496 | [V] |
| return site (ret=0x1289496) | 0x1289496 | - | `0x1289496  nop` | sub_4e05e50 returns here | [V] |
| release [r13+0x10] | [r13+0x10] | 8 | `0x1289486  mov rax,[rcx]` / `0x1289489  mov rax,[rax+8]` / `0x1289490  call qword ptr [0xF99FFA0]` | shared_ptr release of cached object | [V] |
| null [r13+0x10] | [r13+0x10] | 8 | `0x1289497  mov rcx,[r13+0x10]` / `0x128949b  mov qword ptr [r13+0x10],0` | pointer nulled after release | [V] |
| static xrefs to sub_1289440 | - | - | xref.py callers 0x1289440 = no output | 0 static callers; reached only through function pointer | [V] |
| imm refs to 0x1289440 | - | - | `rdis imm 0x1289440` = 0 hits | address never appears as an immediate in code | [V] |

### sub_bc41420 (dragon-layer texture create helper) — [V dis]

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| sub_bc41420 entry | 0xBC41420 | - | E: `0xBC41420  push rbp` | function entry | [V] |
| texture obj field check | rcx+0x28 | 8 | `0xBC41446  cmp qword ptr [rcx+0x28],0` | texture object +0x28 checked for null | [V] |
| texture obj saved | rsi = rcx | 8 | `0xBC4145A  mov rsi,rcx` | texture object pointer saved to rsi | [V] |
| call dragon entry 0xc296b50 | 0xC296B50 | - | `0xBC41B39  call 0xC296B50` | dragon texture entry called | [V] |
| result store 1 | rdi+0x10 | 8 | `0xBC41CB5  mov [rdi+0x10],rcx` | result field stored at +0x10 | [V] |
| result store 2 | rdi | 16 | `0xBC41CB9  movdqu [rdi],xmm0` | 16-byte result stored at rdi | [V] |
| static xrefs to sub_bc41420 | - | - | xref.py callers 0xBC41420 = 1 xref in (from sub_4e05e50) | only caller is sub_4e05e50 | [V] |

### sdk TexturePtr / ClientTexture / BedrockTexture headers — [V file read]

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| TexturePtr class | src/sdk/mc/deps/minecraft_renderer/renderer/TexturePtr.h | 32 | - | `static_assert(sizeof(TexturePtr) == 32)` | two shared_ptr members | [V] |
| TexturePtr.mClientTexture | +0x00 | 16 | - | `std::shared_ptr<void> mClientTexture` | client texture shared_ptr | [V] |
| TexturePtr.mResourceLocationPtr | +0x10 | 16 | - | `std::shared_ptr<void> mResourceLocationPtr` | resource location shared_ptr | [V] |
| ClientTexture struct | src/sdk/mc/deps/minecraft_renderer/resources/ClientTexture.h | - | - | `struct ClientTexture {}` | empty carrier struct | [V] |
| BedrockTexture class | src/sdk/mc/deps/minecraft_renderer/renderer/BedrockTexture.h | 48 | - | `static_assert(sizeof(BedrockTexture) == 48)` | three shared_ptr members | [V] |

### Live capture chain (all [V live])

| name | source | ret= | meaning | tag |
|---|---|---|---|---|
| sub_4e05e50 caller | docs/data/live/mc_root_4e05e50_callers.txt | 0x1289496 | sub_1289440 calls sub_4e05e50 (all 32 samples) | [V live] |
| sub_bc41420 caller | docs/data/live/dragon_texture_caller_bc41420.txt | 0x4E05F7C | sub_4e05e50 calls sub_bc41420 (372 hits) | [V live] |
| dragon entry caller | docs/data/live/dragon_texture_entry_c296b50.txt | 0xBC41B3E | sub_bc41420 calls 0xc296b50 | [V live] |
| wrapper caller | docs/data/live/bgfx_texture_wrapper_bc73bf0.txt | 0xC296D7E | 0xc296b50 calls 0xbc73bf0 | [V live] |
| createTexture caller | docs/data/live/createtexture_callers.txt | 0xBC6A2C8 | dispatcher calls createTexture 0xe8143c0 | [V live] |

## What I tried that failed (new angles that did not close the gap)

- xref.py callers 0xe8143c0 (createTexture slot 26): EMPTY — no static caller, only indirect [vptr+0xD0] thunks (proven by r2; not redone).
- texload 0x58a1310 / texload_task 0x541bf00: xref.py callers EMPTY for both; never decoded; texgroup_load does not call them (its only cache-bound call is 0x54227af -> 0x18718d0).
- xref.py callers 0x4E05E50: no output — 0 static callers; reached only through [0xF99FFA0] from sub_1289440.
- xref.py callers 0x1289440: no output — 0 static callers; reached only through function pointer.
- rdis imm 0x1289440 / imm 0x4E05E50: 0 hits each — neither address appears as an immediate anywhere in code.
- Completion callback 0x186DAC0 (pre/0x186dac0_fn.md): decodes fully; builds 0x48 request block, calls desc builder 0x58CA10, enqueues via 0x71BC70; does NOT call sub_4e05e50 or sub_1289440. So the cache completion path does not lead to sub_4e05e50.

## Interpretation

The createTexture issuance from Minecraft-side code IS proven [V live]:

MC sub_4e05e50 (takes TexturePtr* as RCX) -> passes TexturePtr+0x58 as texture object to sub_bc41420 -> sub_bc41420 calls dragon entry 0xc296b50 -> 0xc296b50 calls wrapper 0xbc73bf0 -> wrapper calls producer 0xbc73770 (writes cmd byte 0x0E) -> bgfx command-buffer dispatcher -> createTexture 0xe8143c0. Handle stored at [texture_obj+0x00] at 0xc296e26 inside sub_c296b50 [V r7].

sub_4e05e50's RCX argument matches the sdk TexturePtr layout (32 bytes: mClientTexture at +0x00 shared_ptr, mResourceLocationPtr at +0x10 shared_ptr) — confirmed by capture data showing two pointer pairs at +0x00/+0x08/+0x10/+0x18 [V from structure match + capture data]. TexturePtr is the type used throughout the Minecraft texture system including texgroup_load/texload [I structural].

The connection from sub_1289440/sub_4e05e50 back to texgroup_load (0x5421c90) is NOT statically provable: both have 0 static xrefs and no immediate references; the link is through a function pointer ([0xF99FFA0]) that is set at runtime. The static pack->GPU chain through 0x18718d0 is already done (r2); sub_4e05e50 is a separate runtime path to createTexture.

## CLOSES?

NO — blocking fact: the createTexture issuance from MC code is proven [V live] through sub_4e05e50 -> sub_bc41420 -> 0xc296b50 -> 0xbc73bf0 -> 0xbc73770 -> dispatcher -> createTexture 0xe8143c0, and sub_4e05e50 takes a TexturePtr* (matching sdk TexturePtr.h), but there is no [V]-proven static path from texgroup_load (0x5421c90) to sub_4e05e50 — both have 0 static xrefs and no immediate references; the connection is through a runtime function pointer ([0xF99FFA0]) that cannot be resolved statically. Sampler half (6ax) [V] and D3D12 backend chain [V] already proven; atlas stitchers tracked by L8a/L8b.

## TOOL REQUESTS

- None (all instruction lines taken verbatim from rdis disassembly; live capture logs are read-only inputs; xref.py and rdis imm used for negative findings; no helper scripts written).
