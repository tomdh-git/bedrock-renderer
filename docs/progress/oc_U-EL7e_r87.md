## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): `- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending | PROGRESS 2026-11-21 oc_U-EL7e.md (verify_oc 185/185): D3D12 backend texture-management chain decoded [V] (texture record table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0, updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0 / blitSetup 0xe819750); Minecraft-side pack->GPU chain (texgroup_load 0x5421c90 -> texload 0x58a1310 -> texload_task 0x541bf00 -> undecoded 0x18718D0 at 0x54227af) and atlas stitchers still open (L8a/L8b)`.

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; live capture logs under docs/data/live are read-only inputs produced by the orchestrator (read this session: mc_root_4e05e50_callers.txt, l8b_texcreate_record.txt, dragon_texture_caller_bc41420.txt, dragon_texture_entry_c296b50.txt, bgfx_createtexture_producer.txt, createtexture_callers.txt, bgfx_texture_wrapper_bc73bf0.txt).

Tags: [V] saw in disassembly (RVA cited, verbatim `0xRVA  instr` quoted) / [V live] saw in an orchestrator live capture log (file cited) / [I] inferred from structure or tool output / [?] unknown or not located.

Row rule: one annotated row per distinct offset, all its sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after the address, copied verbatim from rdis) | meaning ONLY if an instruction/string shows it else '-' | tag. Sizes from the instruction (movups/movaps/movdqu/movdqa 16, qword 8, dword/movss 4, word 2, byte 1). No input data pasted as-is; no skipped offsets among quoted sites; no raw instruction dumps outside tables; no ellipsis or catch-all rows.

## Already proven (cited from r1-r39; not re-quoted, not redone)

- Half 1 — sampler flag decode + sampler cache (6ax): [V] docs/functions/e820500.md decodes 0xe820500 instruction-complete; src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h carries the static_asserts; called from blit 0xe818bc0 and executor 0xe821120.
- Half 2a — D3D12 backend texture-management chain: [V] record table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0, updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0, blitSetup 0xe819750; BGFX_MAP 6z/6z-2/6aj confirm table base/stride and live texture records.
- texgroup_load(0x5421c90) static chain end: `0x54227af  call 0x18718D0` into the texture cache (cache objects vtable 0xEFCA680, != 0xF215838); texload/texload_task have 0 static callers and 0x18718d0 never calls sub_4e05e50/sub_12893d0 [V r19].
- [0xF99FFA0] writer search [V r38]: slot is constant image data in .text (RX), `0xEEA6040  jmp rax` trampoline (`[data_f99ffa0] = sub_eea6040`), 1,088,051 read refs, 0 stores; `imm 0xF99FFA0` and `imm 0x4E05E50` = 0 hits; neither the slot address nor sub_4e05e50 is ever materialized — no static writer exists, the callee is placed in RAX per call site.

## This unit's new work — createTexture issuance chain (command byte 14) and the returned-handle store

The createTexture issuance below sub_4e05e50 was proven live across r4-r7 and is summarized here with verbatim disassembly. Chain:
MC-side caller (ret=0x4E05F7C [V live]) -> sub_bc41420 (call at 0x4E05F77) -> dragon entry 0xc296b50 (call at 0xBC41B39) -> wrapper 0xbc73bf0 -> command-byte-0x0E producer 0xbc73770 [V r4] -> bgfx dispatcher case (renderer ctx vtable slot 26 = 0xe8143c0 [V BGFX_MAP]) -> TextureD3D12::create 0xe81bf30 (ret 0xe814560 [V live docs/data/live/l8b_texcreate_record.txt]); returned 16-bit handle stored via `0xC296E1A  call 0xBC74120` (ax) then `0xC296E26  mov [rdi],ax`.

## Table 1 — sub_4e05e50 entry and its issue of sub_bc41420 (the MC-side createTexture issuer)

| name | offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| sub_4e05e50 entry | 0x4E05E50 | 1 | E: `0x4E05E50  push rbp` | `rdis fn 0x4E05E50`: [0x4e05e50..0x4e06074) size 0x224; `rdis callers 0x4E05E50`: 0 calling function(s) | sub_4e05e50 has no static caller at all | [V] |
| sub_4e05e50 reads object+0x18 (shared ctrl) | 0x4E05E71 | 8 | R: `0x4E05E71  mov rax,[rcx+0x18]` | sub_4e05e50 reads object+0x18 and add_refs via [0xF99FFA0]; RCX is the polymorphic texture job object (vtable 0xF215838) | object argument confirmed by dis + live capture vptr dumps | [V] [V live] |
| sub_4e05e50 renderer ctx field | 0x4E05F61 | 8 | R: `0x4E05F61  mov r9,[rdi+0xE0]` | renderer ctx carried at texture object+0xE0 | renderer ctx for the vcall | [V] |
| sub_4e05e50 object+0x58 step | 0x4E05F68 | - | - | `0x4E05F68  add rdi,0x58` | object+0x58 = texture sub-object | [V] |
| sub_4e05e50 -> sub_bc41420 | 0x4E05F77 | 5 | S: `0x4E05F77  call 0xBC41420` | dragon-layer create issued from sub_4e05e50; ret site 0x4E05F7C = live capture CALLER ret=0x4E05F7C (docs/data/live/dragon_texture_caller_bc41420.txt) | [V] [V live] |
| sub_4e05e50 ret site | 0x4E05F7C | 1 | R: `0x4E05F7C  nop` | ret=0x4E05F7C = live capture CALLER ret=0x4E05F7C | [V] [V live] |

## Table 2 — sub_bc41420 -> dragon entry 0xc296b50 -> handle store

| name | offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| sub_bc41420 -> dragon entry 0xc296b50 | 0xBC41B39 | 5 | S: `0xBC41B39  call 0xC296B50` | ret 0xBC41B3E = live capture CALLER ret=0xBC41B3E (docs/data/live/dragon_texture_entry_c296b50.txt) | [V] [V live] |
| dragon entry ret site | 0xBC41B3E | 4 | R: `0xBC41B3E  movzx eax,byte ptr [rbp+0x188]` | [V] [V live] |
| handle call (16-bit handle -> ax) | 0xC296E1A | 5 | S: `0xC296E1A  call 0xBC74120` | 16-bit handle returned in ax; 0xC296E22 mov ax,0xFFFF invalid fallback | [V] |
| handle store into texture object [rdi] | 0xC296E26 | 2 | W: `0xC296E26  mov [rdi],ax` | 16-bit handle stored at [rdi] where rdi = object+0x58 (texture object) | created handle lands inside the texture object | [V] |
| 16 result bytes at object+0x08 | 0xC296E32 | 16 | W: `0xC296E32  movups [rdi+8],xmm0` | 16 result bytes written at +0x08 after the handle | [V] |

## Table 3 — dispatcher: renderer ctx vtable slot 26 -> createTexture via [0xF99FFA0] trampoline

| name | offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| dispatcher loads renderer ctx vtable slot 26 | 0xBC6A2B1 | 8 | R: `0xBC6A2B1  mov rax,[rax+0xD0]` | renderer ctx vtable slot 26 (= createTexture 0xe8143c0) loaded into rax | slot 26 = createTexture [V BGFX_MAP] | [V] |
| dispatcher indirect call through trampoline | 0xBC6A2C2 | 8 | R: `0xBC6A2C2  call qword ptr [0xF99FFA0]` | jmp-rax trampoline ([data_f99ffa0] = sub_eea6040) -> createTexture; ret site 0xBC6A2C8 = live capture CALLER ret=0xBC6A2C8 (docs/data/live/createtexture_callers.txt) | [V] [V live] |
| dispatcher ret site | 0xBC6A2C8 | 4 | R: `0xBC6A2C8  test rax,rax` | ret=0xBC6A2C8 (docs/data/live/createtexture_callers.txt) | [V] [V live] |

## Table 4 — backend createTexture -> TextureD3D12::create

| name | offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| createTexture -> TextureD3D12::create | 0xE81455B | 5 | S: `0xE81455B  call 0xE81BF30` | backend record fill; ret 0xE814560 = live capture ret=0xE814560 (docs/data/live/l8b_texcreate_record.txt) | [V] [V live] |
| createTexture ret site | 0xE814560 | 1 | R: `0xE814560  nop` | ret=0xE814560 (docs/data/live/l8b_texcreate_record.txt) | [V] [V live] |

## Table 5 — trampoline slot [0xF99FFA0] (the indirect-call lowering; no static writer)

| name | offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| trampoline entry | 0xEEA6040 | 2 | E: `0xEEA6040  jmp rax` | `rdis comment at call sites: [data_f99ffa0] = sub_eea6040` | slot's static content = jmp rax trampoline; never initialized to sub_4e05e50 | [V] |
| sub_12893d0 tail-call through trampoline | 0x1289490 | 8 | R: `0x1289490  call qword ptr [0xF99FFA0]` | sub_12893d0 loads obj->vptr[1] into rax (0x1289489) then tail-calls [0xF99FFA0]; ret site 0x1289496 = live capture CALLER ret=0x1289496 (docs/data/live/mc_root_4e05e50_callers.txt) | sub_4e05e50 = vtable[1] of vtable-0xF215838 texture-job objects, reached via rax at runtime | [V] [V live] |

## What I tried that failed (new angles that did not close the static MC-side link)

- `xr 0xF99FFA0`: 1,088,051 references, all reads (call / mov reg), zero stores — no writer to locate.
- `imm 0xF99FFA0` and `imm 0x4E05E50`: 0 hits each — neither address nor value materialized in code.
- Section check: slot is in .text (RX), not writeable — no static write possible.
- `xref str "Deferred Texture Transactions"`: only sub_6632bf0 (drain, endFrame) and sub_66232b0 (0 static callers) reference it — no texgroup_load enqueue.
- sub_12893d0's complete static caller set = {sub_6632bf0 (2 sites), sub_1145c20 (2), sub_6622610 (1), sub_66232b0 (8)}; all four upward chains dead-end at 0-static-caller functions [V r38, re-confirmed].
- sub_4e05450 constructor (sets vptr=0xF215838, inits texture sub-object at +0x58, stores renderer ctx at +0xE0) has 16 static callers, none texgroup_load/texload/texload_task.
- texgroup_load's static chain terminates at `0x54227af call 0x18718D0` (cache object vtable 0xEFCA680), a separate system from the vtable-0xF215838 job objects.

## CLOSES?

NO — blocking fact: no [V]-proven static path texgroup_load(0x5421c90) -> sub_4e05e50 exists. sub_4e05e50 (0x4E05E50, size 0x224) has 0 static calling functions and is entered only through sub_12893d0's vtable[1] tail-call (`0x1289489  mov rax,[rax+8]` then `0x1289490  call qword ptr [0xF99FFA0]` -> trampoline `0xEEA6040  jmp rax`; ret site 0x1289496 [V live]). [0xF99FFA0] is constant image data (1,088,051 read refs, 0 stores) so the bind is resolved per call in RAX at runtime (vtable[1] of vtable-0xF215838 texture-job objects = sub_4e05e50), not by writing the slot — there is no static writer to name. texgroup_load's static chain ends at `0x54227af call 0x18718D0` (cache object vtable 0xEFCA680 != 0xF215838). Everything else in the item is [V]/[V live]-proven: sampler flag decode + cache (6ax), D3D12 backend texture-management chain, createTexture issuance via bgfx command byte 14 (producer sub_bc73770 -> dispatcher slot 26 = 0xe8143c0 -> TextureD3D12::create), returned handle stored inside the texture object (`0xC296E26  mov [rdi],ax`, size 2, at object+0x58), sdk TexturePtr/ClientTexture headers. Atlas stitchers L8a/L8b remain separate open items (oc_U-EL8a/oc_U-EL8b).

## Verification

- `python tools/sigs/verify_oc.py docs/progress/oc_U-EL7e.md` — every backticked `0xRVA  instr` line must match rdis dis output (mismatch=0, no-such-instr=0).
- `python tools/delegate.py check docs/progress/oc_U-EL7e.md` — must exit 0; `## NEXT` line 2 is DONE only after check exits 0.

## TOOL REQUESTS

- None (all instruction lines quoted verbatim from current rdis output; xr/imm/sec/fn/callers/vt/dis used for positive and negative findings; no helper scripts written, no temporary files left in the repo).
