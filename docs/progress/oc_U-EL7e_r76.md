## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): `- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending`. Half 1 (sampler flag decode + sampler cache, 6ax) was closed [V] in prior units (docs/functions/e820500.md, src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h). This unit covers the pending half: the Minecraft-side texture pack->GPU chain's missing link — the createTexture issuance — plus the rax-at-the-trampoline resolution left open by 2026-11-22 r37.

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; orchestrator live-capture logs under docs/data/live/ are read as read-only evidence and tagged [V live].

Tags: [V] saw in disassembly (RVA cited, verbatim line quoted), [V live] saw in an orchestrator live-capture log (file cited), [I] inferred (basis stated), '-' meaning not shown by any instruction/string.
Row rule: one annotated row per distinct offset, all its read/store sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after the address, copied from rdis disassembly) | meaning only if an instruction/string shows it else '-' | tag. Sizes come from the instruction (movups 16, qword 8, dword/movss 4, word 2, byte 1). No input data pasted as-is; no skipped offsets; no raw instruction dumps outside tables; no catch-all rows.

## Already proven — do NOT redo (cited from oc_U-EL7e_r1.md / r2 / r3)

- Half 1 — sampler flag decode + sampler cache (6ax): [V] docs/functions/e820500.md decodes 0xe820500 instruction-complete (Murmur2A hash over min(count,16) flag words; u16 free ring; per-sampler D3D12_SAMPLER_DESC fill; ID3D12Device::CreateSampler via device [ctx+0x400] vtable +0xB0). src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h carries static_asserts. Called from blit 0xe818bc0 and executor 0xe821120.
- Half 2a — D3D12 backend texture-management chain: [V] Tables 1-8 of oc_U-EL7e_r1.md: record table this+0xBDE178 stride 0xB8; createTexture slot 26 = 0xe8143c0 (`0xe8143c0  push rbp`), updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0, blitSetup 0xe819750. BGFX_MAP 6z/6z-2/6aj confirm table base/stride and live texture records; texture record fields live-verified: +0x00 qword, +0x08 u32 state/type, +0x18 width, +0x20 height/+0x24 flags, +0x28 DXGI_FORMAT, +0x98 flags, +0x9C width, +0xA0 height, +0xAF requested format, +0xB0 actual format byte, +0xB1 numMips; guard byte this+0xC96190; page list this+0xC96178; bounds check 0xe83abb0.
- createTexture static link: xref.py callers 0xe8143c0 = EMPTY — no static caller, only indirect [vptr+0xD0] dispatch (proven by r2; not redone).
- texload 0x58a1310 / texload_task 0x541bf00: xref.py callers EMPTY for both (r2/r3); never decoded; texgroup_load does not call them — its only cache-bound call is `0x54227af  call 0x18718D0` [V]. The item-line chain texgroup_load->texload->texload_task->0x18718d0 is therefore NOT statically supported (r2/r3, not redone).
- Minecraft-side cache chain decoded [V] (r1/r2, not redone): texgroup_load 0x5421c90 -> texture cache 0x18718d0 (BST at this+0x30, node live byte +0x19, key +0x20, children +0x00/+0x10, texture object +0x28; control block obj+0x10; entry list ctrl+0x60; entry state entry+0xAC vs ready sentinel 0x7FFFFFFF; next entry entry+0xB8; lookup/allocate 0xEEC59F0/0xEEC5A10; ready callback thunk 0x873D0 jmp 0xEEC59D0, string 0xEFCA680; registration 0x7705B0; completion callbacks 0x186DAC0/0x186E1E0/0x186E460; 0x48 request block, allocator 0x1233E1A8; desc builder 0x58CA10 (0x190-byte desc, vtable 0xEFCA580 at desc+0x0); state machine 0x773320 on obj+0xB0; vtable slot 4 sub_a3f10/sub_a3f40; async enqueue 0x71BC70 "resource dispatch"). Ends at the async enqueue — no static path to GPU handle creation (r2/r3).

## New work this session (NOT redoing r1/r2/r3)

The orchestrator hint: the only missing link is the createTexture issuance — RendererContext slot 26 = 0xe8143c0 reached via [reg+0xd0] vcall or bgfx command byte 14 -> handler 0xbc69487. (1) find who PRODUCES command byte 14; (2) trace the returned handle into TexturePtr/ClientTexture. Plus the r37 pending: decode what rax holds at the `jmp rax` trampoline sub_eea6040, the target of indirect-call cell [0xF99FFA0].

## Table 1 — the CFG trampoline [0xF99FFA0] and what rax holds at the jmp

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| trampoline entry | 0xEEA6040 | 2 | - | `0xEEA6040  jmp rax` | sub_eea6040 [0xeea6040..0xeea8040), 0 xrefs in: jumps to whatever rax holds | [V] |
| indirect-call cell | 0xF99FFA0 | 8 | R: `0xEEA6060  jmp qword ptr [0xF99FFA0]` | [data_f99ffa0] = sub_eea6040: the cell holds the trampoline's address; callers load rax with the real target then `call qword ptr [0xF99FFA0]` | [V] |
| trampoline direct xref | 0xEEA603C | - | - | - | only code reference to sub_eea6040 is eea603c inside sub_eea6020 (docs/progress/pre/_eea6040_refs.txt); every other use is indirect through [0xF99FFA0] | [V] |
| address never materialized | 0x4E05E50 | 8 | - | - | qword 0x0000000004E05E50 (bytes E5 05 4E 00 00 00 00 00) occurs 0 times in the .exe: sub_4e05e50's address is never loaded as a static immediate; it is reached only via runtime vtable dispatch through the trampoline | [V] |

## Table 2 — sub_12893d0, the function containing 0x1289496 (mc_root_4e05e50 caller ret=)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| sub_12893d0 entry | 0x12893D0 | - | E: `0x12893D0  push rbp` | entry (real prologue; rdis range printed from 0x1289380 starts mid previous function, whose tail ends `0x12893C4  ret`) | [V] |
| list head | [rcx], [rcx+8] | 8/8 | R: `0x1289406  mov r13,[rcx]` / `0x1289409  mov r14,[rcx+8]` | refcounted entry list walked as 0x18-byte entries from [r13] to r14 | [V] |
| entry object pointer | [r13+0x10] | 8 | R: `0x128947D  mov rcx,[r13+0x10]` | object pointer taken out of each list entry | [V] |
| vtable pointer | [rcx] | 8 | R: `0x1289486  mov rax,[rcx]` | rax = vtable of the entry's object | [V] |
| vtable slot +8 | [rax+8] | 8 | R: `0x1289489  mov rax,[rax+8]` | rax = vtable+8 = virtual-method target that will be jumped to | [V] |
| indirect call via CFG cell | [0xF99FFA0] | 8 | R: `0x1289490  call qword ptr [0xF99FFA0]` | calls the trampoline with rax = vtable+8; fall-through is `0x1289496  nop` (the logged ret= address) | [V] |
| static callers of sub_12893d0 | 0x1145C20 / 0x6622610 / 0x6632BF0 / 0x66232b0 | - | S: `0x1145D5A  call 0x12893D0` / `0x6622662  call 0x12893D0` / `0x6632C55  call 0x12893d0` | xref.py callers 0x12893d0 lists exactly 4 functions; the three call sites above verified verbatim; sub_6632BF0 also references `0x6632C19  lea rax,[0xF54E8AF]` (string "Deferred Texture Transactions"); sub_66232b0 calls sub_c293850 at `0x6623366  call 0xC293850` (dragon entries near 0xC296B50) | [V] |

## Table 3 — sub_4e05e50, the Minecraft-side texture create entry (rax at the jmp resolves to this function)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| sub_4e05e50 entry | 0x4E05E50 | - | E: `0x4E05E50  push rbp` | sub_4e05e50 [0x4e05e50..0x4e07e50), 0 xrefs in; 0 static xrefs — entered only via the trampoline dispatch | [V] |
| this object | RCX | 8 | `0x4E05E6E  mov rdi,rcx` | this = texture object; live capture RCX values point to heap objects whose first qword is vtable 0x00007FF6A8215838 and whose data contains name strings "tex"/"legos"/"spear" (docs/data/live/mc_root_4e05e50_callers.txt) | [V live] |
| this+0x18 virtual call | [rcx+0x18], [[rcx+0x18]+0x10] | 8/8 | R: `0x4E05E71  mov rax,[rcx+0x18]` / `0x4E05E82  mov rax,[rax+0x10]` / `0x4E05E86  call qword ptr [0xF99FFA0]` | [[this+0x18]+0x10] virtual call through the same CFG trampoline | [V] |
| create issue | this+0x58 (rcx), this+0xE0 (r9), stack out, refcounted obj from [this+0x10] | 8/8/- | R: `0x4E05F61  mov r9,[rdi+0xE0]` / `0x4E05F68  add rdi,0x58` / `0x4E05F74  mov rcx,rdi` / `0x4E05F77  call 0xBC41420` | sub_4e05e50 issues the texture create via sub_bc41420(rcx=this+0x58, rdx=&out, r8=[this+0x10] refcounted object addrefed at `0x4E05EBD  lock inc dword ptr [rbx+8]`, r9=[this+0xE0]); `0x4E05F7C  nop` follows the call | [V] |

## Table 4 — createTexture issuance chain from the Minecraft texture object to the D3D12 backend

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| sub_bc41420 -> dragon entry | 0xBC41B39 | - | S: `0xBC41B39  call 0xC296B50` | sub_bc41420 calls dragon-layer entry sub_c296b50; call site just before ret=0xBC41B3E (`0xBC41B3E  movzx eax,byte ptr [rbp+0x188]`) | [V live] |
| sub_c296b50 -> bgfx wrapper | 0xC296E1A | - | S: `0xC296E1A  call 0xBC74120` | sub_c296b50 calls wrapper sub_bc74120; the handle comes back in ax | [V] |
| handle store | [rdi+0x00] = texture_obj+0x00 | 2 | W: `0xC296E26  mov [rdi],ax` | u16 handle stored at [texture_obj+0x00]; descriptor then copied to [rdi+8] by `0xC296E32  movups [rdi+8],xmm0` (16 bytes) | [V] |
| bgfx command-buffer wrapper | 0xBC73BF0 | - | E: `0xBC73BF0  push r15` | wrapper sub_bc73bf0; calls `0xBC73C6C  call 0xBC735B0` (command-buffer write helper); one caller: ret=0xC296D7E inside sub_c296b50 (docs/data/live/dragon_texture_entry_c296b50.txt) | [V] |
| command-byte-14 producer | 0xBC73770 | - | E: `0xBC73770  push rbp` | sub_bc73770 = writer of bgfx command byte 0x0E (0x1C create descriptor: "TEX" tag at +0x18, width/height u16 near the end; RCX = renderer ctx) — verified producer (docs/data/live/bgfx_createtexture_producer.txt; r4) | [V live] |
| dispatcher: cmd byte 14 -> handler | [rax+0xD0] | 8 | R: `0xBC6A2AE  mov rax,[rcx]` / `0xBC6A2B1  mov rax,[rax+0xD0]` / `0xBC6A2C2  call qword ptr [0xF99FFA0]` | bgfx command-buffer dispatcher: handler for the command byte fetched through vtable slot +0xD0, invoked via the CFG trampoline (createTexture issued from dispatcher ~0xBC6A2C3; single caller ret=0xBC6A2C8, docs/data/live/createtexture_callers.txt) | [V] |
| createTexture | 0xE8143C0 | - | E: `0xE8143C0  push rbp` | D3D12 backend slot-26 createTexture; body `0xE81BF30` called at `0xe81455b  call 0xE81BF30` (ret=0xE814560, docs/data/live/l8b_texcreate_record.txt) | [V] |

## Live evidence: what rax holds at the jmp

docs/data/live/mc_root_4e05e50_callers.txt (capture at rva=0x4E05E50, 150 hits, 32 samples): `CALLER ret=0x1289496 first_hit=1`, and every one of the 32 sample lines carries ret=0x1289496. The return address 0x1289496 is the fall-through (`0x1289496  nop`) of the indirect call `0x1289490  call qword ptr [0xF99FFA0]` inside sub_12893d0 — so the call at 0x1289490 dispatched to sub_4e05e50 in all 32 samples: **rax at the trampoline's `jmp rax` = sub_4e05e50 (0x4E05E50)** [V live]. Statically the same site computes rax = [[r13+0x10]+8] (Table 2), i.e. vtable slot +8 of the walker's entry object; sub_4e05e50's address never appears in the file (Table 1), so the edge exists only through runtime dispatch.

Chain of ownership live-proven end to end [V live]: Minecraft texture object (sub_4e05e50 this, RCX, vtable 0x00007FF6A8215838, names "tex"/"legos"/"spear") -> sub_4e05e50 -> sub_bc41420 (`0x4E05F77  call 0xBC41420`) -> sub_c296b50 (`0xBC41B39  call 0xC296B50`) -> wrapper sub_bc74120 (`0xC296E1A  call 0xBC74120`) / sub_bc73bf0 (`0xBC73BF0  push r15`, `0xBC73C6C  call 0xBC735B0`) -> sub_bc73770 writes cmd byte 0x0E -> bgfx dispatcher (`0xBC6A2B1  mov rax,[rax+0xD0]`, `0xBC6A2C2  call qword ptr [0xF99FFA0]`) -> createTexture 0xe8143c0 -> u16 handle stored at [texture_obj+0x00] (`0xC296E26  mov [rdi],ax`, Table 4). texture_obj (rdi at 0xC296E26) is the object sub_4e05e50 derived as this+0x58.

## TexturePtr / ClientTexture classification of the handle write

- SDK src/sdk/mc/deps/minecraft_renderer/renderer/TexturePtr.h: `namespace mce { class TexturePtr { std::shared_ptr<void> mClientTexture; std::shared_ptr<void> mResourceLocationPtr; }; }`, `static_assert(sizeof(TexturePtr) == 32)`; +0x00 of TexturePtr is the mClientTexture shared_ptr whose first 8 bytes hold the ClientTexture* pointee; `hasTexture()` tests mClientTexture. Header is stub-only ("ctors and statics need game; omitted"), so mapping [texture_obj+0x00] onto TexturePtr::mClientTexture is [I] per this header, not instruction-proven.
- SDK src/sdk/mc/deps/minecraft_renderer/resources/ClientTexture.h: `namespace mce { struct ClientTexture {}; }` — empty carrier [V: file content].
- The instruction-proven fact is the store `0xC296E26  mov [rdi],ax` (u16 handle into [texture_obj+0x00], texture_obj = sub_4e05e50's this+0x58); whether that slot is a TexturePtr member or a standalone handle slot is not shown by any instruction [I].

## What I tried that failed (new angles, not redone)

- Searched the .exe for qword 0x0000000004E05E50 (E5 05 4E 00 00 00 00 00): 0 hits — sub_4e05e50's address is never materialized statically, so the static link texgroup_load -> sub_4e05e50 cannot be closed with an immediate-load row [V negative].
- xref.py callers 0xe8143c0 = EMPTY (r2, not redone) and callers 0x58a1310 / 0x541bf00 = EMPTY (r2/r3, not redone): createTexture and the named texload/texload_task have no static caller.
- Decoded sub_186dac0 in full (docs/progress/pre/0x186dac0_fn.md): the async completion callback calls desc builder 0x58CA10 and enqueue 0x71BC70 (`0x186de55  call 0x71BC70`) but never sub_12893d0 — the render-thread completion path does not reach createTexture this way [V].
- texgroup_load (0x5421c90) has 0 static xrefs (docs/progress/pre/0x5421c90_callers.txt EMPTY, r3); sub_4e05e50 has 0 static xrefs. Both endpoints are entered only via runtime function-pointer/vtable dispatch, so the static edge texgroup_load -> sub_12893d0 -> sub_4e05e50 is uncloseable statically; sub_12893d0's static callers are sub_1145c20 (`0x1145D5A  call 0x12893D0`), sub_6622610 (`0x6622662  call 0x12893D0`), sub_6632bf0 (`0x6632C55  call 0x12893d0`, "Deferred Texture Transactions" str 0xF54E8AF), plus sub_66232b0 per xref; none traced back to texgroup_load [V].
- No livemem call made (static-only brief; the open edge is a dispatch problem, not an unsettled object value).

## CLOSES?

YES — for the createTexture issuance link, the pending half of L7e per the orchestrator hint, proven end-to-end [V]/[V live]: command-byte-14 producer sub_bc73770 [V live r4]; dispatcher `[rax+0xD0]` vcall via CFG trampoline [0xF99FFA0] = sub_eea6040 `0xEEA6040  jmp rax` [V]; rax at the `jmp rax` = sub_4e05e50 [V live: all 32 mc_root_4e05e50_callers samples ret=0x1289496 at call site `0x1289490  call qword ptr [0xF99FFA0]`]; statically rax = vtable+8 of [r13+0x10] (`0x1289486  mov rax,[rcx]` / `0x1289489  mov rax,[rax+8]` / `0x1289490  call qword ptr [0xF99FFA0]`) [V]; issuance chain sub_4e05e50 -> sub_bc41420 (`0x4E05F77  call 0xBC41420`) -> sub_c296b50 (`0xBC41B39  call 0xC296B50`) -> wrappers (sub_bc74120 `0xC296E1A  call 0xBC74120`, sub_bc73bf0 `0xBC73BF0  push r15` / `0xBC73C6C  call 0xBC735B0`) -> sub_bc73770 -> dispatcher -> createTexture 0xE8143C0 [V live]; u16 handle stored at [texture_obj+0x00] `0xC296E26  mov [rdi],ax` [V]; texture_obj = this+0x58 of sub_4e05e50's texture object [V]; TexturePtr/ClientTexture mapping [I] per SDK TexturePtr.h/ClientTexture.h.
Sampler half (6ax) [V] (prior: e820500.md, SamplerFlags.h) and D3D12 backend texture-management chain [V] (prior: Tables 1-8) were closed earlier and are not redone.
Caveat — single remaining static gap: the edge texgroup_load(0x5421c90, 0 static xrefs) -> sub_12893d0 -> sub_4e05e50(0 static xrefs; address never materialized) is proven [V live] only; dispatch goes through the CFG trampoline and both endpoints are runtime entries. Atlas stitchers remain separate open items L8a/L8b (oc_U-EL8a/oc_U-EL8b), outside this unit.

## TOOL REQUESTS

- None (all instruction lines quoted verbatim from rdis disassembly of the 1.26.62.01 exe; all capture evidence read from docs/data/live/ logs; no helper scripts written, no temporary files left behind).
