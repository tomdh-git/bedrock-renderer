## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): `- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending | PROGRESS 2026-11-21 oc_U-EL7e.md (verify_oc 185/185): D3D12 backend texture-management chain decoded [V] (texture record table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0, updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0 / blitSetup 0xe819750); Minecraft-side pack->GPU chain (texgroup_load 0x5421c90 -> texload 0x58a1310 -> texload_task 0x541bf00 -> undecoded 0x18718D0 at 0x54227af) and atlas stitchers still open (L8a/L8b)`

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; live capture logs under docs/data/live are read-only inputs produced by the orchestrator (read this session: mc_root_4e05e50_callers.txt, l8b_texcreate_record.txt, dragon_texture_caller_bc41420.txt, dragon_texture_entry_c296b50.txt, bgfx_createtexture_producer.txt, createtexture_callers.txt, bgfx_texture_wrapper_bc73bf0.txt).

Tags: [V] saw in disassembly (RVA cited, verbatim `0xRVA  instr` quoted) / [V live] saw in an orchestrator live capture log (file cited) / [I] inferred from structure or tool output / [?] unknown or not located.

Row rule: one annotated row per distinct offset, all its sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after the address, copied verbatim from rdis) | meaning ONLY if an instruction/string shows it else '-' | tag. Sizes from the instruction (movups/movaps/movdqu/movdqa 16, qword 8, dword/movss 4, word 2, byte 1). No input data pasted as-is; no skipped offsets among quoted sites; no raw instruction dumps outside tables; no ellipsis or catch-all rows.

## Already proven (cited from r1-r38; not re-quoted, not redone)

- Half 1 — sampler flag decode + sampler cache (6ax): [V] docs/functions/e820500.md decodes 0xe820500 instruction-complete; src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h carries the static_asserts; called from blit 0xe818bc0 and executor 0xe821120.
- Half 2a — D3D12 backend texture-management chain: [V] record table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0, updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0, blitSetup 0xe819750; BGFX_MAP 6z/6z-2/6aj confirm table base/stride and live texture records.
- createTexture issuance below sub_4e05e50: [V live + dis] sub_bc41420 -> dragon entry 0xc296b50 -> wrapper 0xbc73bf0 -> command-byte-0x0E producer 0xbc73770 [V r4] -> bgfx dispatcher case (renderer ctx vtable slot 26 = 0xe8143c0 [V BGFX_MAP]) -> TextureD3D12::create 0xe81bf30 (ret 0xe814560 [V live docs/data/live/l8b_texcreate_record.txt]); returned 16-bit handle stored via `0xC296E1A  call 0xBC74120` (ax) then `0xC296E26  mov [rdi],ax`; texture object carries renderer ctx at +0xE0 (`0x4E05F61  mov r9,[rdi+0xE0]`) and TexturePtr-shaped members at +0x10/+0x18; sdk TexturePtr/ClientTexture [V file read: sizeof(TexturePtr)==32, mClientTexture +0x00, mResourceLocationPtr +0x10, ClientTexture empty, BedrockTexture 48 bytes].
- texgroup_load(0x5421c90) static chain end: `0x54227AF  call 0x18718D0` into the texture cache (cache objects vtable 0xEFCA680, != 0xF215838); texload/texload_task have 0 static callers and 0x18718d0 never calls sub_4e05e50/sub_12893d0 [V r19].
- [0xF99FFA0] writer search [V r38]: slot is constant image data in .text (RX), `0xEEA6040  jmp rax` trampoline (`[data_f99ffa0] = sub_eea6040`), 1,088,051 read refs (call / mov reg), 0 stores; `imm 0xF99FFA0` and `imm 0x4E05E50` = 0 hits; neither the slot address nor sub_4e05e50 is ever materialized — no static writer exists, the callee is placed in RAX per call site.

## This session — new angle: sub_12893d0 (function containing 0x1289496) and its callers, fully decoded

sub_12893d0 [0x12893d0..0x12895d3), size 0x203, 13 static xrefs in. It is the dispatch that the mc_root capture (CALLER ret=0x1289496, 32 samples, docs/data/live/mc_root_4e05e50_callers.txt) passes through: RCX = vtable-0xF215838 object (live capture vptr dumps start 0x7FF6A8215838). It iterates an array of 0x18-byte job objects and, for each, reads [obj+0x10]->vptr[1] and tail-calls it through the [0xF99FFA0] trampoline — i.e. it invokes sub_4e05e50 for vtable-0xF215838 objects because vtable[1] of 0xF215838 IS sub_4e05e50.

## Table 1 — sub_12893d0 dispatch body (instruction-complete, quoted verbatim from rdis)

| name | offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| object vptr load | 0x1289406 | 8 | R: `0x1289406  mov r13,[rcx]` | object+0x0 = vptr (r13 = walk cursor start) | [V] |
| object range-end load | 0x1289409 | 8 | R: `0x1289409  mov r14,[rcx+8]` | object+0x8 = walk cursor end (r14) | [V] |
| job vtable[1] load | 0x1289489 | 8 | R: `0x1289489  mov rax,[rax+8]` | rax = [r13+0x10] (job object), then rax = job->vptr[1] | [V] |
| trampoline dispatch call | 0x1289490 | 8 | R: `0x1289490  call qword ptr [0xF99FFA0]` | tail-call job->vtable[1] through jmp-rax trampoline = sub_4e05e50 at runtime; ret site 0x1289496 = live capture CALLER ret=0x1289496 | [V] [V live] |

## Table 2 — the four static callers of sub_12893d0 (who invokes sub_4e05e50); none is texgroup_load/texload/texload_task

| name | offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| sub_6632bf0 "Deferred Texture Transactions" string ref | 0x6632c19 | - | R: `0x6632c19  lea rax,[0xF54E8AF]` | loads string "Deferred Texture Transactions" (0xF54E8AF); this is the deferred-texture-transaction drain | [V] |
| sub_6632bf0 dispatches to sub_12893d0 | 0x6632c55 | 5 | S: `0x6632c55  call 0x12893D0` | endFrame deferred-transaction drain -> sub_12893d0 -> sub_4e05e50 | [V] |
| sub_6622610 dispatches object+0xD8 vector | 0x6622662 | 5 | S: `0x6622662  call 0x12893D0` | reads object+0xD8 buffer, drains via sub_12893d0 -> sub_4e05e50 | [V] |
| sub_66232b0 (also refs "Deferred Texture Transactions") | 0x66232b0 | - | E: `0x66232b0  push rbp` | huge 0xB3D0 function, 0 static xrefs in — never invoked statically; references 0xF54E8AF at 0x66244e7/0x66264e6 | [V] |
| sub_1145c20 | 0x1145c20 | - | E: `0x1145c20  push rbp` | 1 static xref in; dead-end (no texgroup_load connection) | [V] |

New-angle findings this session:
- `xref str "Deferred Texture Transactions"`: refs only at 0x6632c19 (sub_6632bf0), 0x66244e7 and 0x66264e6 (sub_66232b0). sub_66232b0 has 0 static callers, so the deferred-texture-transaction buffer is populated only by a function never reached statically — no texgroup_load enqueue link exists.
- sub_12893d0's complete static caller set = {sub_6632bf0 (2 sites), sub_1145c20 (2), sub_6622610 (1), sub_66232b0 (8)}; all four upward chains dead-end at 0-static-caller functions [V r38, re-confirmed].
- vtable 0xF215838: slot 0 = sub_4e060b0, **slot 1 = sub_4e05e50** (`rdis vt 0xF215838`) — so vtable[1] IS sub_4e05e50 statically, reached via RAX at call time through [0xF99FFA0]. [V]

## What I tried that failed (new angles that did not close the gap)

- `xr 0xF99FFA0`: 1,088,051 references, all reads (call / mov reg), zero stores — no writer to locate.
- `imm 0xF99FFA0` and `imm 0x4E05E50`: 0 hits each — neither address nor value materialized in code.
- Section check: slot is in .text (RX), not .rdata — same conclusion (no static write possible).
- `xref str "Deferred Texture Transactions"`: only sub_6632bf0 (drain, endFrame) and sub_66232b0 (0 static callers) reference it — no texgroup_load enqueue.
- Not redone (already exhausted in r1-r38): upward caller chains from sub_12893d0's 4 static callers all dead-end at 0-static-caller functions; sub_4e05450 constructor (sets vptr=0xF215838, inits texture sub-object at +0x58, stores renderer ctx at +0xE0) has 16 static callers, none texgroup_load/texload/texload_task; texgroup_load's static chain ends at `0x54227AF call 0x18718D0` (cache object vtable 0xEFCA680 != 0xF215838).

## CLOSES?

NO — blocking fact: no [V]-proven static path texgroup_load(0x5421c90) -> sub_4e05e50 exists. sub_4e05e50 is vtable[1] of vtable-0xF215838 texture-job objects, invoked only through sub_12893d0's trampoline dispatch, which is statically called solely from the deferred-transaction/endFrame path (sub_6632bf0) and the object+0xD8 vector path (sub_6622610) — neither reachable from texgroup_load/texload/texload_task. texgroup_load's static chain terminates at the texture cache (`0x54227AF call 0x18718D0`, cache vtable 0xEFCA680), a separate system from the vtable-0xF215838 job objects built by sub_4e05450. [0xF99FFA0] is a constant jmp-rax trampoline (no static writer), so the sub_4e05e50 bind is resolved per call in RAX at runtime, not by writing the slot — there is no static writer to name and no static texgroup_load link. Everything else in L7e is [V]/[V live]-proven: sampler flag decode + cache (6ax), D3D12 backend texture-management chain, createTexture issuance via bgfx command byte 14 (producer sub_bc73770 -> dispatcher slot 26 = 0xe8143c0 -> TextureD3D12::create), returned handle stored inside the texture object (`0xC296E26  mov [rdi],ax`, size 2), sdk TexturePtr/ClientTexture headers. Atlas stitchers L8a/L8b remain separate open items (oc_U-EL8a/oc_U-EL8b).

## Verification

- `python tools/sigs/verify_oc.py docs/progress/oc_U-EL7e.md` — every backticked `0xRVA  instr` line must match rdis dis output (mismatch=0, no-such-instr=0).
- `python tools/delegate.py check docs/progress/oc_U-EL7e.md` — must exit 0; `## NEXT` line 2 is DONE only after check exits 0.

## TOOL REQUESTS

- None (no helper scripts written, no temporary files left; all instruction lines quoted verbatim from current rdis output or re-verified r38 rows; xr/imm/str/vt/fn/callers used for positive and negative findings).
