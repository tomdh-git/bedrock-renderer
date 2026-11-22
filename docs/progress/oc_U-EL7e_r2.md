## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): `- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending | PROGRESS 2026-11-21 oc_U-EL7e.md (verify_oc 185/185): D3D12 backend texture-management chain decoded [V] ...; Minecraft-side pack->GPU chain (texgroup_load 0x5421c90 -> texload 0x58a1310 -> texload_task 0x541bf00 -> undecoded 0x18718D0 at 0x54227af) and atlas stitchers still open (L8a/L8b)`

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only.

Tags: [V] saw in disassembly (RVA cited, verbatim line quoted), [I] inferred from structure/BGFX_MAP, [?] unknown / not located.
Row rule: one annotated row per distinct offset, all its sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after address, copied from rdis) | meaning only if an instruction/string shows it else '-' | tag. Sizes from instruction (movups 16, qword 8, dword/movss 4, word 2, byte 1). No input data pasted as-is; no skipped offsets. No raw instruction dumps outside tables.

## Already proven (do NOT redo — cited from r1 / verified files)

- Half 1 — sampler flag decode + sampler cache (6ax): [V] docs/functions/e820500.md decodes 0xe820500 instruction-complete; src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h carries static_asserts. Called from blit 0xe818bc0 and executor 0xe821120.
- Half 2a — D3D12 backend texture-management chain: [V] Tables 1-8 in oc_U-EL7e_r1.md: record table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0, updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0, blitSetup 0xe819750. BGFX_MAP 6z/6z-2/6aj confirm table base/stride and live texture records (guard byte this+0xC96190 = 0, page list this+0xC96178).
- BGFX_MAP 6z: texture record fields (live-verified): +0x00 qword, +0x08 u32 state/type, +0x18 width u32, +0x20 height u32 +0x24 flags, +0x28 DXGI_FORMAT, +0x2c u32, +0x98 flags, +0x9C width, +0xA0 height, +0xAF requested format, +0xB0 actual format byte, +0xB1 numMips.

## New angle taken (NOT redoing r1)

Disassembled the previously "undecoded" callee 0x18718d0 itself (0x2000 bytes, 29 xrefs in) instead of assuming it hides createTexture. Listed its callers via xref (texgroup_load 0x5421c90 confirmed at call site 0x54227af; the earlier claim that the call sits in texload_task 0x541bf00 was NOT supported — 0x541bf00 is not among 0x18718d0's callers). Traced the three completion callbacks (0x186DAC0/0x186E1E0/0x186E460), the desc builder (0x58CA10 -> 0xA2050 -> 0x773320), the texture-object vtable 0xEFCA580 slot 4 (sub_a3f10/sub_a3f40), the ready-callback registration (0x7705B0, cb 0x873D0 -> jmp 0xEEC59D0), and the async enqueue (0x71BC70). Also ran xref.py callers 0xe8143c0 (createTexture slot 26): EMPTY — no static caller anywhere, only indirect [vptr+0xD0] thunks. descscan2/livemem not needed for this negative result; the chain statically terminates at the Minecraft texture-object init, not at the D3D12 backend.

## FAILED SO FAR (this session)

- xref.py callers 0xe8143c0 = empty: createTexture (D3D12 slot 26) has no static caller; only reachable via indirect call qword ptr [vptr+0xD0], which static analysis cannot bind to the texgroup_load chain. Could not close the GPU-creation link statically.
- No livemem call made (brief: static-only unless rdis points at a specific object that static analysis cannot settle; the open link is an indirect call target, not a live value).

## Table 1 — Minecraft-side pack->GPU chain (texgroup_load 0x5421c90 -> ... -> texture-object init; previously "undecoded 0x18718D0")

| name | offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| chain start | 0x5421c90 | - | - | `0x5421c90  push rbp` | texgroup_load entry (pack->GPU chain start; 7 xrefs in; calls the callee at 0x54227af) | [V] |
| cache fn entry | 0x18718d0 | - | - | `0x18718d0  push rbp` | sub_18718d0 texture-cache lookup/create (0x2000 bytes, 29 xrefs in); was the "undecoded 0x18718D0" callee | [V] |
| call site | 0x54227af | - | - | `0x54227af  call 0x18718D0` | texgroup_load calls sub_18718d0 | [V] |
| cache object root | this+0x30 | 8 | R: `0x18718fe  mov rcx,[rcx+0x30]` | cache object root pointer loaded | [V] |
| BST node live byte | node+0x19 | 1 | R: `0x1871906  cmp byte ptr [rdx+0x19],0` | node live byte; 0 -> keep walking the BST | [V] |
| BST node key | node+0x20 | 4 | R: `0x1871923  cmp [rdx+0x20],r8d` | BST node key compared with requested key r8d (idx = 0 or 0x10 via `shl r9d,4`) | [V] |
| BST children | node+0x00/+0x10 | 8 | R: `0x1871933  mov rdx,[rdx+r9]` | left/right child pointer walk | [V] |
| found texture object | found+0x28 | 8 | R: `0x18719aa  mov rdi,[rax+0x28]` | texture object pointer taken from the located node | [V] |
| control block | obj+0x10 | 8 | R: `0x18719b3  mov r14,[rdi+0x10]` | refcounted control block | [V] |
| entry list head | ctrl+0x60 | 8 | R: `0x18719b7  lea rbx,[r14+0x60]` | per-entry list head passed to 0xEEC59F0 | [V] |
| entry state | entry+0xAC | 4 | R: `0x18719cb  cmp dword ptr [r14+0xAC],0x7FFFFFFF` | entry state compared with ready sentinel 0x7FFFFFFF | [V] |
| next entry | entry+0xB8 | 8 | R: `0x18719dc  mov r14,[r14+0xB8]` | next entry in chain | [V] |
| get-or-create helpers | 0xEEC59F0/+0xEEC5A10 | - | R: `0x18719be  call 0xEEC59F0` / `0x18719e6  call 0xEEC5A10` | cache lookup / allocate entry | [V] |
| ready-callback name string | str 0xEFCA680 | - | R: `0x1871a15  lea rax,[0xEFCA680]` | ready-callback name string referenced | [V] |
| ready callback fn | 0x873D0 | - | R: `0x1871a20  lea rax,[0x873D0]` / `0x186d9c3  lea rax,[0x873D0]` | callback = thunk `0x873d0  jmp 0xEEC59D0` | [V] |
| callback registration | 0x7705B0 | - | R: `0x1871a33  call 0x7705B0` / `0x186d9d6  call 0x7705B0` | register ready callback on cache entry (also called from 0x186d960+0x13f) | [V] |
| completion paths | 0x186DAC0/0x186E1E0/0x186E460 | - | R: `0x1871ab7  call 0x186DAC0` / `0x1871cd8  call 0x186E1E0` / `0x1871ec8  call 0x186E460` | async load completion paths dispatched from the cache | [V] |
| load control object | ctrl+0x10 | 8 | R: `0x186daf5  mov rdi,[rcx+0x10]` | texture load control object | [V] |
| block threshold | 0x10 | 8 | R: `0x186dafd  cmp qword ptr [rdi+0x50],0x10` | inline-vs-heap block threshold | [V] |
| global allocator | 0x1233E1A8 | 8 | R: `0x186dba0  mov rcx,[0x1233E1A8]` | heap allocator used for request blocks | [V] |
| request-block alloc | alloc 0x48 | 4 | R: `0x186dbae  mov edx,0x48` / `0x186dbb3  call qword ptr [0xF99FFA0]` | 0x48-byte request block allocated | [V] |
| desc builder | 0x58CA10 | - | R: `0x186dcf9  call 0x58CA10` | builds the texture load desc | [V] |
| desc vtable | desc+0x0 | 8 | R: `0xa2255  lea rax,[0xEFCA580]` / `0xa225c  mov [r12],rax` | 0x190-byte desc (`mov edx,0x190` at 0xa222f, `call qword ptr [0xF99FFA0]` at 0xa2234) gets vtable 0xEFCA580 | [V] |
| state machine | 0x773320 | - | R: `0x58cb0f  call 0x773320` / `0x773337  mov eax,[rcx+0xB0]` / `0x773397  mov rax,[rax+0x20]` / `0x7733a2  call qword ptr [0xF99FFA0]` | state machine on obj+0xB0; virtual call vtable+0x20 = texture init path | [V] |
| vtable slot 4 target | sub_a3f10 0xa3f10 | - | R: `0xa3f10  push rsi` / `0xa3f1b  call 0xA3F40` / `0xa3f4c  lea rax,[0xEFCA5A0]` / `0xa3f56  lea rax,[0xEFCA5D0]` / `0xa3f64  lea rax,[0xEFCA5F0]` / `0xa404b  lea rax,[0xEFCD320]` / `0xa40ad  jmp 0x76B950` | vtable slot 4 target; sub_a3f40 sets live vtables 0xEFCA5A0/5D0/5F0, failure flips to dead 0xEFCD320/340 then tail-jumps 0x76B950 | [V] |
| result write | out rsi+0x0/+0x8/+0x10 | 8 | R: `0x58cb2b  mov [rsi],rdx` / `0x58cb32  mov [rsi+0x10],rdi` | 24-byte result {ptr, ptr, obj} written to caller out ptr | [V] |
| async enqueue | 0x71BC70 | - | R: `0x186de55  call 0x71BC70` | ResourceLoadManager async enqueue; task string "resource dispatch" at 0xF5B0748 | [V] |
| error state | entry+0xAC (fail) | 4 | W: `0x1871acd  mov dword ptr [r14+0xAC],0x7FFFFFFE` | entry marked failed (0x7FFFFFFE); notify 0xEEC5A00 ecx=6 (0x1871add) / ecx=5 (0x1871ac7) | [V] |
| createTexture slot 26 | 0xe8143c0 | - | - | - | `xref.py callers 0xe8143c0` = empty: NO static caller; only indirect `call qword ptr [vptr+0xD0]` thunks; NOT provably reached from texgroup_load | [?] |

## Interpretations ([I] notes, not row claims)

- 0x18718d0 is a texture *cache* lookup/create, not a D3D12 createTexture wrapper: BST at `this+0x30` (header node `[root+8]`, live byte +0x19, key +0x20, children +0x00/+0x10, texture object at +0x28), refcounted control block at obj+0x10, ready-callback registration via 0x7705B0 with cb 0x873D0->jmp 0xEEC59D0 and string 0xEFCA680.
- On a cache hit the three completion callbacks 0x186DAC0/0x186E1E0/0x186E460 are tail-called; each builds a 0x48 request block (allocator 0x1233E1A8, size 0x48) and calls 0x58CA10 -> 0xA2050 (0x190-byte desc, vtable 0xEFCA580 at desc+0x0) -> 0x773320 (state machine on obj+0xB0, virtual call vtable+0x20 -> sub_a3f10/sub_a3f40 texture init; live vtables 0xEFCA5A0/5D0/5F0; failure flips to 0xEFCD320/340) -> result {ptr, ptr, obj} written to caller out ptr (rsi+0x0/+0x8/+0x10).
- The load is async: ResourceLoadManager enqueue 0x71BC70 ("resource dispatch" task string 0xF5B0748). The D3D12 device createTexture call, if any, lives behind that completion continuation / inside sub_a3f10's 0x2000-byte body (only the head was decoded) and is not statically visible.
- xref.py callers 0xe8143c0 returned no callers at all: D3D12 slot-26 createTexture is only invoked through indirect `call qword ptr [0xF99FFA0]` thunks (vptr+0xD0 style), which static analysis cannot bind to this chain.

## CLOSES?

NO — blocking fact: the Minecraft-side pack->GPU chain decodes [V] from texgroup_load 0x5421c90 through the texture cache 0x18718d0 (call site 0x54227af), the ready-callback/notification machinery, the desc builder, and the texture-object init (vtable 0xEFCA580 slot 4), ending at the async ResourceLoadManager enqueue 0x71BC70 — but there is NO statically provable path to D3D12 createTexture 0xe8143c0 (xref.py callers = empty; only indirect [vptr+0xD0]) and hence no [V]-proven GPU handle write on the Minecraft side. The sampler half (6ax) [V] (e820500.md, SamplerFlags.h) and the D3D12 backend texture-management chain [V] (Tables 1-8 in oc_U-EL7e_r1.md) are already proven; atlas stitchers remain separate open items L8a/L8b (oc_U-EL8a/oc_U-EL8b), so the pending half of L7e cannot be closed by this unit.

## Verification

Verbaitm `0xRVA  instr` lines copied from `rdis.exe dis` output; `python tools/sigs/verify_oc.py docs/progress/oc_U-EL7e.md` and `python tools/delegate.py check docs/progress/oc_U-EL7e.md` both required to exit 0 before CLOSES? is final.

## TOOL REQUESTS

- None (all instruction lines taken verbatim from rdis disassembly of the 1.26.62.01 exe; xref.py callers for the negative finding; no helper scripts written, no temporary files left behind).
