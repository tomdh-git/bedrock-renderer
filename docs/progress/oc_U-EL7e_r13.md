## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): `- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending | PROGRESS 2026-11-21 oc_U-EL7e.md (verify_oc 185/185): D3D12 backend texture-management chain decoded [V] ...; Minecraft-side pack->GPU chain (texgroup_load 0x5421c90 -> texload 0x58a1310 -> texload_task 0x541bf00 -> undecoded 0x18718D0 at 0x54227af) and atlas stitchers still open (L8a/L8b)`

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; live captures are read-only (orchestrator-produced, never touched the game).

Tags: [V] saw in disassembly (RVA cited, verbatim line quoted), [V live] saw in orchestrator live capture (file+line cited), [I] inferred from structure/BGFX_MAP/live capture, [?] unknown / not located.
Row rule: one annotated row per distinct offset, all its sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after address, copied from rdis/xref disassembly) | meaning only if an instruction/string shows it else '-' | tag. Sizes from instruction (movups 16, qword 8, dword/movss 4, word 2, byte 1). No input data pasted as-is; no skipped offsets. No raw instruction dumps outside tables.

## Already proven (do NOT redo — cited from r1/r2/r3 / verified files)

- Half 1 — sampler flag decode + sampler cache (6ax): [V] docs/functions/e820500.md decodes 0xe820500 instruction-complete; src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h carries static_asserts. Called from blit 0xe818bc0 and executor 0xe821120.
- Half 2a — D3D12 backend texture-management chain: [V] Tables 1-8 in oc_U-EL7e_r1.md: record table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0, updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0, blitSetup 0xe819750. BGFX_MAP 6z/6z-2/6aj confirm table base/stride and live texture records.
- r2 (not redone): xref.py callers 0xe8143c0 = EMPTY — createTexture has no static caller, only indirect [vptr+0xD0] thunks; static analysis cannot bind the pack->GPU hop to it.
- r3 (not redone): texgroup_load 0x5421c90 -> texture cache 0x18718d0 at `0x54227af  call 0x18718D0` [V]; texload 0x58a1310 / texload_task 0x541bf00 have EMPTY xref callers and are never called by texgroup_load statically; backend->cache adjacency [V] (`0xe84a62  call 0x18718D0`, sub_e82e00 -> sub_e84070 at 0xe830ce/0xe83280/0xe834e3/0xe83695).

## New angle taken this session (NOT redoing r1/r2/r3)

Attack the createTexture issuance from the bgfx command-buffer side (command byte 0x0E), using the queued live captures (read-only, produced by the orchestrator):

- LIVE RESULT createtexture_callers (docs/data/live/createtexture_callers.txt, 1612 hits): ONE caller, ret=0xBC6A2C8 (call site just before it). R8 points at a 0x1C-byte create descriptor ("TEX" tag at +0x18, width/height u16 near the end); RCX = renderer ctx. createTexture is issued from the bgfx command-buffer dispatcher around 0xBC6A2C3, not from MC texture code.
- r4 RESULT: command-byte-0x0E producer is sub_bc73770 (verified); thin wrappers 0xbc73bf0/0xbc73ed0/0xbc74120 reach it; MC texture code calls none statically.
- LIVE RESULT 3: wrapper 0xbc73bf0 has ONE caller, ret=0xC296D7E = inside dragon-layer entry 0xc296b50 (3206 hits). Chain: MC -> ? -> 0xc296b50 -> 0xbc73bf0 -> 0xbc73770 (writes cmd 0x0E) -> dispatcher -> createTexture 0xe8143c0.
- LIVE RESULT 4: dragon entry 0xc296b50 has ONE caller, ret=0xBC41B3E (141 hits). Handle store [texture_obj+0x00] at 0xc296e26 [V], caller sub_bc41420 (call at 0xbc41b39) [V live].
- r7 RESULT: sub_bc41420 has ONE caller, ret=0x4E05F7C (372 hits) = Minecraft-side code (0x4e0....). Full chain: 0x4E05F7C -> sub_bc41420 (bc41b39 call) -> 0xc296b50 -> 0xbc73bf0 -> 0xbc73770 -> dispatcher -> createTexture 0xe8143c0.
- LIVE RESULT mc_root_4e05e50_callers (docs/data/live/mc_root_4e05e50_callers.txt, 150 hits, 32 samples): CALLER ret=0x1289496 (inside function 0x12893d0..0x12895d3). RCX=MC_obj (texture object pointer), RDX=out-param. 0x12893d0 has 4 static callers: 0x1145c20, 0x6622610, 0x66232b0, 0x6632bf0. None connect to texgroup_load/texload (0x5421c90/0x58a1310) statically — texgroup_load's callers are 0x5958f0/0x596230/0x95e0f0/0x5420770/0x5424290; none of 0x12893d0's callers are in texgroup_load's caller/callee tree or the texture cache 0x18718d0's caller list.

## Table 1 — sub_4e05e50, MC-side pack->GPU root (0x4e05e50..0x4e06074, size 0x224, 0 static xrefs in)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| sub_4e05e50 entry | 0x4e05e50 | - | E: `0x4E05E50  push rbp` | MC root function entry; rdis header: size 0x224, 0 xrefs in — indirect entry only | [V] |
| save out-param | rdx | 8 | W: `0x4E05E6B  mov rsi,rdx` | out-param saved to rsi (later `0x4E06010 mov qword ptr [rsi],0` nulls it) | [V] |
| save MC_obj | rcx | 8 | W: `0x4E05E6E  mov rdi,rcx` | MC_obj (1st arg) saved to rdi | [V] |
| MC_obj+0x18 shared_ptr addref | MC_obj+0x18 | 8 | R: `0x4E05E71  mov rax,[rcx+0x18]` / `0x4E05E82  mov rax,[rax+0x10]` / `0x4E05E86  call qword ptr [rip+0xab9a114]` | shared_ptr at +0x18 addrefed via import thunk | [V] |
| MC_obj+0x10 shared_ptr refcount bump | MC_obj+0x10 | 4 | R: `0x4E05E8C  mov rdx,[rdi+0x10]` / `0x4E05EA8  lock cmpxchg dword ptr [rdx+8],r8d` | refcount increment on shared_ptr at +0x10 | [V] |
| MC_obj+0x8 pointer copy | MC_obj+0x8 | 8 | R: `0x4E05EB0  mov rcx,[rdi+8]` / W: `0x4E05EC1  mov [rbp+0x40],rcx` | pointer at +0x8 copied to stack block | [V] |
| MC_obj+0x10 shared_ptr copy | MC_obj+0x10 | 8 | R: `0x4E05EB4  mov rbx,[rdi+0x10]` / W: `0x4E05EC5  mov [rbp+0x48],rbx` | shared_ptr at +0x10 copied to stack block | [V] |
| MC_obj+0xE0 flags -> arg4 | MC_obj+0xE0 | 8 | R: `0x4E05F61  mov r9,[rdi+0xE0]` | flags/value at +0xE0 passed as 4th arg to sub_bc41420 | [V] |
| dragon_obj = MC_obj+0x58 | MC_obj+0x58 | 8 | W: `0x4E05F68  add rdi,0x58` / `0x4E05F74  mov rcx,rdi` | rdi = MC_obj+0x58 = dragon_obj, passed as RCX to sub_bc41420 | [V] |
| sub_bc41420 call | 0xbc41420 | - | S: `0x4E05F77  call 0xBC41420` | MC root -> dragon-layer bridge; live capture returns to 0x4E05F7C | [V] [V live] |
| return address | 0x4e05f7c | - | E: `0x4E05F7C  nop` | return address after call; matches live capture ret=0x4E05F7C | [V] [V live] |
| sub_4e061b0 call (descriptor copy out) | 0x4e061b0 | - | S: `0x4E05F85  call 0x4E061B0` | copies descriptor bytes out of out-struct2 into [rbp-8]; handle NOT copied | [V] |
| caller out-param nulled | [rsi] | 8 | W: `0x4E06010  mov qword ptr [rsi],0` | caller's out-param set to 0 | [V] |
| sub_4e05e50 has no static caller | 0x4e05e50 | - | - | xref.py callers 0x4e05e50 = EMPTY; rdis: 0 xrefs in; imm scan 0 hits; ripscan 0 hits | invoked only indirectly | [V] negative |

## Table 2 — sub_bc41420, dragon-layer bridge (0xbc41420..0xbc43420, called from 0x4e05f77)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| dragon_obj+0x28 nonzero guard | dragon_obj+0x28 | 4 | R: `0xBC41446  cmp qword ptr [rcx+0x28],0` | [dragon_obj+0x28] must be nonzero | [V] |
| r8 block -> rbx | r8 | 8 | W: `0xBC41454  mov rbx,r8` | rbx = 16-byte block {[MC_obj+0x8],[MC_obj+0x10]} passed by sub_4e05e50 | [V] |
| dragon_obj -> rsi | rcx | 8 | W: `0xBC4145A  mov rsi,rcx` | rsi = dragon_obj | [V] |
| dragon_obj+0x78 flag | dragon_obj+0x78 | 1 | R: `0xBC4145D  movzx eax,byte ptr [rcx+0x78]` | flag byte at +0x78 | [V] |
| call sub_c296b50 | 0xc296b50 | - | S: `0xBC41B39  call 0xC296B50` | dragon-layer bridge calls dragon entry 0xc296b50 | [V] |
| success flag read | [rbp+0x188] | 1 | R: `0xBC41B3E  movzx eax,byte ptr [rbp+0x188]` | success flag from sub_c296b50 | [V] |
| static xref in | 0xbc41420 | - | - | xref.py callers 0xbc41420 = 0x4e05e50(+0x224) — one static caller, MC root | [V] |

## Table 3 — sub_c296b50, dragon entry (0xc296b50..0xc296cad, size ~0x17e)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| sub_c296b50 entry | 0xc296b50 | - | E: `0xC296B50  push rbp` | dragon entry 0xc296b50; rdis header size ~0x17e | [V] |
| handle store error path | dragon_obj+0x00 | 2 | W: `0xC296E26  mov word ptr [rdi],ax` | u16 handle (0xFFFF on error) stored at dragon_obj+0x00 | [V] |
| desc copy to +0x08 | dragon_obj+0x08 | 16 | W: `0xC296E2D  movups xmm0,[r12]` / `0xC296E32  movups [rdi+8],xmm0` | 16-byte descriptor copied to dragon_obj+0x08 | [V] |
| ptr copy to +0x18 | dragon_obj+0x18 | 8 | R: `0xC296E36  mov rdx,[r12+0x10]` / W: `0xC296E3B  mov [rdi+0x18],rdx` | qword pointer copied to dragon_obj+0x18 | [V] |
| call wrapper 0xbc73bf0 | 0xbc73bf0 | - | S: `0xC296D79  call 0xBC73BF0` | dragon entry calls bgfx createTexture wrapper | [V] |
| jump to handle store | 0xc296e26 | - | S: `0xC296D7F  jmp 0xC296E26` | all success paths jump to handle store at 0xc296e26 | [V] |

## Table 4 — sub_4e061b0, MC-side out-block copy (0x4e061b0..0x4e06351)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| ready flag check | [rdx+0x40] | 1 | R: `0x4E061BD  cmp byte ptr [rdx+0x40],1` | checks success flag on source block | [V] |
| width/height copy | [rcx+0x10] | 8 | R: `0x4E061C3  mov r8,[rdx+0x10]` / W: `0x4E061C7  mov [rcx+0x10],r8` | width/height copied to dst+0x10 | [V] |
| handle+desc copy | [rcx+0x0] | 16 | R: `0x4E061CB  movups xmm0,[rdx]` / W: `0x4E061CE  movups [rcx],xmm0` | 16 bytes (handle+desc) copied to dst+0x0 | [V] |
| ready flag set | [rcx+0x40] | 1 | W: `0x4E062BB  mov byte ptr [rcx+0x40],1` | ready flag set to 1 at dst+0x40 | [V] |
| static callers | 0x4e061b0 | - | - | xref.py callers: 0x4e05e50, 0x4e06430, 0x4e067c0, 0x4e06a90, 0x56be030, 0x5aba280, 0x64f14f0, 0x67cb9a0, 0xc295880 — all same MC-root family, none is texgroup_load/texload | [V] |

## Table 5 — command-byte-0x0E producer and createTexture issuance (live-proven)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| cmd-byte-0x0E writer | sub_bc73770 | - | - | r4 RESULT: sub_bc73770 writes command byte 0x0E (`0xBC73AAA  mov byte ptr [rbp+0x2C],0xE`) | [V] (r4) |
| thin wrapper call | 0xbc73bf0 | - | S: `0xBC73EA8  call 0xBC73770` | wrapper 0xbc73bf0 calls producer sub_bc73770 | [V] (r4) [V live] |
| wrapper caller | 0xc296b50 | - | S: `0xC296D79  call 0xBC73BF0` | dragon entry calls wrapper 0xbc73bf0 | [V] [V live] |
| dispatcher default path | 0xbc6a2ae | 8 | R: `0xBC6A2AE  mov rax,[rcx]` / `0xBC6A2B1  mov rax,[rax+0xD0]` | vtable slot 26 (createTexture) loaded | [V] |
| dispatcher indirect call | 0xbc6a2c2 | - | S: `0xBC6A2C2  call qword ptr [0xF99FFA0]` | calls createTexture through import thunk | [V] |
| createTexture entry | 0xe8143c0 | - | E: `0xE8143C0  push rbp` | slot-26 createTexture entry | [V] |
| live caller of createTexture | 0xe8143c0 | - | - | LIVE capture: ONE caller, ret=0xBC6A2C8 (call site just before it) | [V live] |
| full issuance chain | MC -> 0x4e05e50 -> sub_bc41420 -> 0xc296b50 -> 0xbc73bf0 -> sub_bc73770 -> dispatcher -> createTexture 0xe8143c0 | - | - | live-proven: ret=0x4E05F7C, ret=0xBC41B3E, ret=0xBC73EAD, ret=0xBC6A2C8 | [V live] |

## Handle flow (end to end)

createTexture returns ID3D12Resource* (dispatcher default path `0xBC6A2AE  mov rax,[rcx]` / `0xBC6A2B1  mov rax,[rax+0xD0]` / `0xBC6A2C2  call qword ptr [0xF99FFA0]`, live ret=0xBC6A2C8 [V live]) -> handle u16 via wrapper -> sub_c296b50 stores it at dragon-layer object +0x0 (`0xC296E26  mov [rdi],ax` [V]) -> sub_bc41420 copies handle+desc block to out ptr +0x0 (`0xBC41CB9  movdqu [rdi],xmm0` [V] per r9/r11) and width/height to +0x10 (`0xBC41CB5  mov [rdi+0x10],rcx` [V] per r9/r11) and ready flag to +0x40 (`0xBC41CFD  mov byte ptr [rdi+0x40],1` [V] per r9/r11) -> sub_4e061b0 copies [rdx+0x0] handle+desc (16B) to [rcx+0x0] (`0x4E061CB  movups xmm0,[rdx]` / `0x4E061CE  movups [rcx],xmm0` [V]) and [rdx+0x10] w/h to [rcx+0x10] (`0x4E061C7  mov [rcx+0x10],r8` [V]) and sets [rcx+0x40]=1 (`0x4E062BB  mov byte ptr [rcx+0x40],1` [V]).

## TexturePtr/ClientTexture connection (NOT proven)

- SDK headers: TexturePtr (32B, mClientTexture shared_ptr at +0x00, mResourceLocationPtr shared_ptr at +0x10; src/sdk/mc/deps/minecraft_renderer/renderer/TexturePtr.h), ClientTexture (empty carrier; src/sdk/mc/deps/minecraft_renderer/resources/ClientTexture.h), BedrockTexture (48B, three shared_ptrs; src/sdk/mc/deps/minecraft_renderer/renderer/BedrockTexture.h), ServerTexture (empty carrier).
- No store to TexturePtr+0x00 (mClientTexture) anywhere in texgroup_load/texload/texload_task/0x18718D0/sub_a3f10/sub_bc41420/sub_4e05e50/sub_4e061b0/sub_c296b50 [V negative per r8-r11].
- sub_4e05e50 copies only descriptor bytes back (`0x4E061CB  movups xmm0,[rdx]` / `0x4E061CE  movups [rcx],xmm0`) and NULLs its out-param (`0x4E06010  mov qword ptr [rsi],0`) — the handle at [dragon_obj+0x00] is never copied back to MC_obj [V].
- The handle is stored in an internal ~0x88B RenderDragon texture object at [dragon_obj+0x00], where dragon_obj = MC_obj+0x58. MC_obj has fields at +0x08/+0x10/+0x18/+0xE0 (shared_ptr/pointer/flag reads) — consistent with an internal MC texture object, NOT provably TexturePtr/ClientTexture/BedrockTexture [I].
- vtable 0xEFCA580 slot 4 (sub_a3f10, texture-object init) does NOT call createTexture or any wrapper [V negative per r2].

## CLOSES?

NO — blocking fact: the handle returned by createTexture is stored in the internal dragon-layer texture object at [dragon_obj+0x00] (dragon_obj = MC_obj+0x58) and is never written into any TexturePtr/ClientTexture/BedrockTexture field. No store to TexturePtr+0x00 (mClientTexture shared_ptr) appears anywhere in the decoded chain. Additionally, sub_4e05e50 (the MC-side pack->GPU root that feeds MC_obj+0x58 into this chain) has no static caller — xref.py callers EMPTY, imm scan 0 hits, ripscan 0 hits, rdis reports 0 xrefs in. Its indirect caller is 0x12893d0 (ret=0x1289496, live capture mc_root_4e05e50_callers.txt line 3) but 0x12893d0's 4 static callers (0x1145c20/0x6622610/0x66232b0/0x6632bf0) do not connect to texgroup_load/texload (0x5421c90/0x58a1310) statically. Everything else in the item IS [V]-proven: sampler half (6ax) [V] (e820500.md/SamplerFlags.h); D3D12 backend texture-management chain [V] (Tables 1-8 of r1); createTexture issuance [V + V live] (producer sub_bc73770 writes command byte 0x0E `0xBC73AAA  mov byte ptr [rbp+0x2C],0xE`; wrappers 0xbc73bf0/0xbc73ed0/0xbc74120; dispatcher default path `0xBC6A2AE  mov rax,[rcx]` / `0xBC6A2B1  mov rax,[rax+0xD0]` / `0xBC6A2C2  call qword ptr [0xF99FFA0]`; live ret=0xBC6A2C8 [V live]; createTexture entry 0xe8143c0); handle traced into the dragon-layer texture object end to end [V]; sub_4e05e50 -> sub_bc41420 at `0x4E05F77  call 0xBC41420` [V] with live ret=0x4E05F7C [V live]; sub_4e061b0 copy [V]. Atlas stitchers remain separate open items L8a/L8b (oc_U-EL8a/oc_U-EL8b), not this unit.

## TOOL REQUESTS

- None (all instruction lines verified against rdis disassembly via delegate.py check; no helper scripts written, no temporary files left behind).
