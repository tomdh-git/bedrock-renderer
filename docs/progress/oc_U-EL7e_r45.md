## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): `- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending`. Half 1 (sampler flag decode + sampler cache, 6ax) is closed [V] from prior units (docs/functions/e820500.md instruction-complete; src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h static_asserts). This unit covers half 2: texture/atlas management — the Minecraft-side pack->GPU chain into D3D12 createTexture and the texture/atlas handle write.

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; live captures below are orchestrator-run (read-only reg dumps), cited as [V live] with file name.

Tags: [V] saw in disassembly (RVA cited, verbatim `0xRVA  instr` quoted from rdis), [V live] seen in an orchestrator live-capture reg dump, [I] inferred, '-' = no instruction/string shows a meaning. Row rule: one annotated row per distinct offset; all read/store sites listed; sizes from the instruction; verbatim lines copied exactly from rdis output. No input data pasted as-is; no raw instruction dumps outside tables; no ellipsis shorthand.

## Already proven (do NOT redo — cited from r1-r3, verify_oc 185/185)

- Half 1 — sampler flag decode + sampler cache (6ax): [V] docs/functions/e820500.md decodes 0xe820500 instruction-complete; key = bgfx HashMurmur2A over min(count,16) u32 flag words; map at heap+0x60; u16 free ring at heap+8; per-sampler D3D12_SAMPLER_DESC on the stack, ID3D12Device::CreateSampler (device [ctx+0x400], vtable +0xB0). Called from blit 0xe818bc0 and executor 0xe821120.
- Half 2a — D3D12 backend texture-management chain: [V] Tables 1-8 of oc_U-EL7e_r1.md: guarded texture record table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0 (`0xe8143c0  push rbp`), updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0, blitSetup 0xe819750; createTexture body `0xe81455b  call 0xE81BF30`; record fields per BGFX_MAP 6z (+0x00 resource ptr, +0x44 state, +0x9C/+0xA0 w/h, +0xAF/+0xB0 format, +0xB1 numMips).
- Static roots with 0 xrefs (rdis `fn` reports "0 xrefs in"; not redone): texgroup_load 0x5421c90 (item-line chain start), createTexture 0xe8143c0 (xref.py callers EMPTY — only indirect [vptr+0xD0] dispatch), sub_4e05e50 0x4E05E50, sub_1289400 0x1289400. texgroup_load -> texture cache 0x18718d0 at `0x54227af  call 0x18718D0` [V r2]; texload 0x58a1310 and texload_task 0x541bf00 have EMPTY static caller lists and were never decoded (item-line chain texgroup_load->texload->texload_task is NOT statically supported).

## New angle taken this session (NOT redoing r1-r3)

Attack from the live capture side: who PRODUCES bgfx command byte 14 (createTexture), how the descriptor gets to the dispatcher, and how the returned handle lands in the Minecraft texture object (TexturePtr/ClientTexture). Five orchestrator live captures were read in full: docs/data/live/createtexture_callers.txt, bgfx_createtexture_producer.txt, bgfx_texture_wrapper_bc73bf0.txt, dragon_texture_entry_c296b50.txt, dragon_texture_caller_bc41420.txt, mc_root_4e05e50_callers.txt, l8b_texcreate_record.txt.

## Table 1 — who produces command byte 14: sub_bc73770 writes the bgfx createTexture command into the command buffer

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| createTexture entry | 0xe8143c0 | - | E: `0xe8143c0  push rbp` | D3D12 backend slot-26 entry (BGFX_MAP 6aj) | [V] |
| bgfx command/lock state | [rdi+0x1CFD0C8] | 8 | R: `0xBC73AA3  mov rbx,[rdi+0x1CFD0C8]` | command-buffer state object (BGFX_MAP 6ai: API-thread command/lock state) | [V] |
| cmd write index | [rbx+0xDC5818] | 4 | R: `0xBC73AAE  mov eax,[rbx+0xDC5818]` / W: `0xBC73AE2  mov [rbx+0xDC5818],ecx` | ring write index, bumped by 2 after the 2-byte handle | [V] |
| command-buffer entry | [rbx+0xDC5820 + idx] | - | R: `0xBC73AB4  lea rcx,[rbx+rax]` / `0xBC73AB8  add rcx,0xDC5820` | entry address in the command buffer | [V] |
| **command byte 0x0E staged** | [rbp+0x2C] | 1 | W: `0xBC73AAA  mov byte ptr [rbp+0x2C],0xE` | byte 14 = createTexture command staged in the local descriptor | [V] |
| cmd byte write (1 B) | [rbx+0xDC5820+idx] | 1 | R: `0xBC73ABF  lea rdx,[rbp+0x2C]` / R: `0xBC73AC3  mov r8d,1` / `0xBC73AC9  call 0xEBCE390` | 1 byte (cmd 0x0E) written into the command buffer | [V] |
| 2-byte handle staged | [rbp+0x2E] | 2 | W: `0xBC73853  mov [rbp+0x2E],ax` | ax = handle index from sub_bc79a60 (0xFFFF = invalid) | [V] |
| handle write (2 B) | [rbx+0xDC5820+idx+1] | 2 | R: `0xBC73AEB  lea rdx,[rbp+0x2E]` / R: `0xBC73AEF  mov r8d,2` / `0xBC73AF5  call 0xEBCE390` | 2-byte handle written right after the cmd byte | [V] |

sub_bc73770 (0xBC73770, 3 xrefs in) is the command-byte-14 producer [V per r4]: it parses the bimg container (0xBC737C5  call 0xEBD2160), builds the 0x1C-byte create descriptor (width/height/format fields at [rbp-0xC..]), allocates the handle (0xBC7384D  call 0xBC79A60 -> [rbp+0x2E]), and stages cmd byte 0x0E + handle at `0xBC73AAA  mov byte ptr [rbp+0x2C],0xE` [V verbatim]. Capture bgfx_createtexture_producer.txt: RDX=14C8D2 points at the descriptor on every hit (`140054455800...` = {0x14=20 cmd?, "TEX\0" tag, 0x43=67 width, ...}); R8 points at the same descriptor ("54455800" = "TEX\0" tag visible in the hex dump).

## Table 2 — how the descriptor reaches createTexture: dispatcher [vptr+0xD0] vcall via CFG trampoline [0xF99FFA0]

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| vtable object ptr | [rdi+0x1EBF2D0] | 8 | R: `0xBC6A28F  mov rcx,[rdi+0x1EBF2D0]` | renderer-context-like object whose vtable is dispatched | [V] |
| vtable load | [rcx] | 8 | R: `0xBC6A2AE  mov rax,[rcx]` | vtable pointer loaded | [V] |
| **slot 26 function ptr** | [rax+0xD0] | 8 | R: `0xBC6A2B1  mov rax,[rax+0xD0]` | vtable slot 0xD0/8 = 26 = createTexture pointer loaded into rax | [V] |
| **createTexture issuance** | - | - | `0xBC6A2C2  call qword ptr [0xF99FFA0]` / `0xBC6A2C8  test rax,rax` | createTexture called via CFG trampoline; rax = returned handle; this is the ONLY static call site of 0xe8143c0 | [V] |

Capture createtexture_callers.txt: capture at 0xE8143C0, 1612 hits, ONE caller — `CALLER ret=0xBC6A2C8` on every hit, i.e. the instruction immediately after `0xBC6A2C2  call qword ptr [0xF99FFA0]` [V live]. R8 at the call = the 0x1C-byte create descriptor ("TEX" tag at +0x18 per the capture hex dump; width/height u16 near the end) [V live]. So: dispatcher sub_bc6a200-area issues createTexture via [reg+0xD0] vcall (matches the orchestrator hint: slot 26 = 0xe8143c0 reached via [reg+0xd0] vcall / bgfx command byte 14).

## Table 3 — CFG indirect-call trampoline [0xF99FFA0]

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| trampoline entry | 0xEEA6040 | - | E: `0xEEA6040  jmp rax` | CFG trampoline: jumps to whatever rax holds (0 xrefs in; body is jmp rax + int3 padding) | [V] |
| trampoline storage | [0xF99FFA0] | 8 | R: `eea6060  jmp qword ptr [0xF99FFA0]` ; [data_f99ffa0] = sub_eea6040 | .rdata cell holds the address of sub_eea6040 (rdis data xref annotation) | [V] |
| trampoline use | call qword ptr [0xF99FFA0] | - | W: none — read-only .rdata; r37: no writer found | every `call [0xF99FFA0]` = call sub_eea6040 = jmp rax; rax holds the real target set by the caller just before (vtable slot loads, e.g. Table 2) | [V] |

Meaning of [0xF99FFA0]: it is NOT a writable function pointer and it is NOT sub_4e05e50; it is the read-only trampoline address (r37, static work exhausted). The dynamic target is rax at each call site — only a live capture at 0xEEA6040 can read it (see TOOL REQUESTS).

## Table 4 — Minecraft-side pack->GPU chain: texture object -> sub_4e05e50 -> sub_bc41420 (live-proven)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| sub_4e05e50 entry | 0x4E05E50 | - | E: `0x4E05E50  push rbp` | MC texture create entry; RCX = texture object/TexturePtr* a0, RDX = out handle ptr rsi; 0 static xrefs | [V] |
| vtable slot-2 call | [*(a0+0x18)+0x10] | 8 | R: `0x4E05E71  mov rax,[rcx+0x18]` / R: `0x4E05E82  mov rax,[rax+0x10]` / `0x4E05E86  call qword ptr [0xF99FFA0]` | virtual call on the object at +0x18 (vtable slot 2 = 0x10/8) | [V] |
| shared_ptr ctrl block refcount | [a0+0x10]+8 | 4 | R: `0x4E05E95  mov eax,[rdx+8]` / W: `0x4E05EA8  lock cmpxchg [rdx+8],r8d` / W: `0x4E05EBD  lock inc dword ptr [rbx+8]` | refcounted control block (matches mce::TexturePtr shared_ptr layout: ptr at +0x00/+0x10, ctrl block +0x8/+0x18; sdk TexturePtr.h, sizeof==32) | [V] (sdk layout [I]) |
| desc pointer | a0+0x58 | 8 | R: `0x4E05F61  mov r9,[rdi+0xE0]` / `0x4E05F68  add rdi,0x58` | texture-object desc passed as r9 / RCX to sub_bc41420 | [V] |
| **sub_bc41420 call** | sub_bc41420 | - | `0x4E05F77  call 0xBC41420` / `0x4E05F7C  nop` | RCX = a0+0x58 (create descriptor); return address 0x4E05F7C | [V] |
| out-ptr result | [rsi] | 8 | W: `0x4E06010  mov qword ptr [rsi],0` / `0x4E0604B  mov rax,rsi` | output handle written to the caller's ptr (RDX); rax returns rsi | [V] |

Capture dragon_texture_caller_bc41420.txt: capture at 0xBC41420, `CALLER ret=0x4E05F7C` — the instruction right after `0x4E05F77  call 0xBC41420` [V live]. RCX on entry = 531A2FA4958; hexdump shows the 0x1C-byte create descriptor: flags 0x80000000, size 0x1C, tag "tex" (74657800), width 0x30=48, height 0xF0=240 [V live bytes]. Capture mc_root_4e05e50_callers.txt: capture at 0x4E05E50, 150 hits / 32 samples, `CALLER ret=0x1289496` on every hit; RCX = heap objects 0x3908FF.. (e.g. 0x3908FFDE900) whose bytes carry name strings ("legends", "tex", "spear") plus dimension/format fields [V live bytes]. So sub_4e05e50 is a texture-object vtable slot (only reachable indirectly — 0 static xrefs).

## Table 5 — texture-group iterator sub_1289400 (static root, 0 xrefs) calls sub_4e05e50 via the trampoline

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| sub_1289400 entry | 0x1289400 | - | E: `0x1289400  rol byte ptr [r8],1` | iterates an array of texture objects, stride 0x18; 0 static xrefs | [V] |
| stride-0x18 walk | - | - | `0x1289420  add r13,0x18` | next texture object in the group array | [V] |
| refcount gate | [rcx+8] | 4 | R: `0x128943A  mov eax,[rcx+8]` / `0x1289444  lea edx,[rax+1]` / `0x1289447  lock cmpxchg [rcx+8],edx` | bump-then-test refcount of the object at [r13] | [V] |
| per-object vtable slot-1 load | [*(r13+0x10)+8] | 8 | R: `0x128947D  mov rcx,[r13+0x10]` / R: `0x1289486  mov rax,[rcx]` / R: `0x1289489  mov rax,[rax+8]` | rax = vtable slot 1 of the texture object at [r13+0x10] | [V] |
| **indirect call to sub_4e05e50** | - | - | `0x1289490  call qword ptr [0xF99FFA0]` / `0x1289496  nop` | call site ends at ret=0x1289496 = the capture caller of sub_4e05e50 (RCX = [r13+0x10] texture object, RDX = rbx out ptr) | [V live] |

So the static entry link is: texgroup_load 0x5421c90 (pack->GPU root) -> fills group texture objects via cache 0x18718d0 -> sub_1289400 iterator -> sub_4e05e50 (vtable slot 1, via [0xF99FFA0] with runtime rax) -> sub_bc41420 -> ... -> createTexture. Every hop below sub_4e05e50 is proven; the entry hops (texgroup_load -> sub_1289400, sub_1289400 -> sub_4e05e50 target) are indirect through the read-only trampoline.

## Table 6 — dragon/renderer half: descriptor -> command byte 14 -> handle store back into the texture object

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| sub_bc41420 -> dragon entry | 0xC296B50 | - | `0xBC41B39  call 0xC296B50` / `0xBC41B3E  movzx eax,byte ptr [rbp+0x188]` | capture dragon_texture_caller_bc41420.txt: `CALLER ret=0xBC41B3E` [V live]; capture dragon_texture_entry_c296b50.txt: `CALLER ret=0xBC41B3E` [V live] | sub_bc41420 calls dragon entry 0xc296b50 with the create descriptor | [V live] |
| wrapper | 0xBC73BF0 | - | E: `0xBC73BF0  push r15` | bgfx::createTexture* wrapper; capture bgfx_texture_wrapper_bc73bf0.txt: `CALLER ret=0xC296D7E` (inside dragon entry 0xc296b50) [V live r4] | [V live] |
| cmd-0x0E producer | sub_bc73770 | - | Table 1 | writes cmd byte 0x0E + handle into the command buffer | [V] |
| **handle store into texture object** | [texture_obj+0x00] | 2 | W: `0xC296E26  mov [rdi],ax` / `0xC296DF0  jmp short 0xC296E26` | ax = the allocated handle stored at [texture_obj+0x00]; descriptor copied to +0x8 (`0xC296E2D  movups xmm0,[r12]` / `0xC296E32  movups [rdi+8],xmm0`) | [V] |
| createTexture body | 0xE81BF30 | - | `0xe81455b  call 0xE81BF30` (createTexture body) | TextureD3D12::create body -> record table this+0xBDE178 stride 0xB8 | [V r1] |
| create record (live) | - | - | capture l8b_texcreate_record.txt: `CALLER ret=0xE814560` (inside createTexture, right after `0xe81455b  call 0xE81BF30`); R8 = "Texture: 2815"/"Texture: 2799".. name strings | runtime-created texture records named "Texture: <n>" | [V live] |

## Interpretations ([I] notes, not row claims)

- End-to-end pack->GPU chain [V live below sub_4e05e50]: MC texture object (mce::TexturePtr-family, shared_ptr ctrl blocks at +0x10/+0x18, desc at +0x58, names legends/tex/spear) --sub_4e05e50(TexturePtr*)--> sub_bc41420 --dragon entry 0xc296b50--> wrapper 0xbc73bf0 --> sub_bc73770 writes bgfx command byte 0x0E (`0xBC73AAA  mov byte ptr [rbp+0x2C],0xE`) + 2-byte handle into the command buffer at [ctx+0x1CFD0C8]+0xDC5820 --> dispatcher `0xBC6A2AE  mov rax,[rcx]` / `0xBC6A2B1  mov rax,[rax+0xD0]` / `0xBC6A2C2  call qword ptr [0xF99FFA0]` ([vptr+0xD0] = slot 26 = createTexture 0xe8143c0, sole static caller, capture sole caller ret=0xBC6A2C8 [V live]) --> createTexture body 0xE81BF30 --> D3D12 texture record table this+0xBDE178 stride 0xB8 --> handle stored back at [texture_obj+0x00] (`0xC296E26  mov [rdi],ax` [V]).
- [0xF99FFA0] is the CFG indirect-call trampoline (sub_eea6040, `0xEEA6040  jmp rax`), read-only .rdata, no writer [V Table 2 + r37]; every `call [0xF99FFA0]` tails to rax. Vtable slot loads (`mov rax,[rcx]; mov rax,[rax+slot]`) feed rax at each call site.
- Sampler half (6ax) [V] from prior units; atlas stitchers remain separate open items L8a/L8b (oc_U-EL8a/oc_U-EL8b), not this unit.

## What I tried that failed (new angles, not redone)

- xref.py callers 0xe8143c0: EMPTY (r2, not redone); createTexture only reachable via indirect [vptr+0xD0] — solved via the live capture instead (sole caller ret=0xBC6A2C8).
- texload 0x58a1310 / texload_task 0x541bf00: xref.py callers EMPTY for both; never decoded; texgroup_load does not call them (its only cache-bound call is 0x54227af -> 0x18718d0 [V r2]).
- [0xF99FFA0] writer search: none — read-only .rdata initializer = sub_eea6040 (r37; confirmed verbatim: `eea6060  jmp qword ptr [0xF99FFA0]`).
- Static resolution of rax at the trampoline: not possible (rax set per call site from vtable loads); static work exhausted per r37.
- livemem: not applicable (static indirect-dispatch gap); no call made.

## CLOSES?

NO — blocking fact: the static entry hop texgroup_load(0x5421c90) -> sub_1289400 -> sub_4e05e50 is indirect through [0xF99FFA0] (sub_eea6040 `0xEEA6040  jmp rax`); [0xF99FFA0] is read-only .rdata with no writer (r37), so the rax target values at the entry call sites are not statically resolvable (static analysis exhausted). Everything below sub_4e05e50 is [V live]-proven (Tables 1, 2, 4, 5, 6). Capture at 0xEEA6040 (read rax) requested under TOOL REQUESTS; a hit with rax in {0x5421C90, 0x1289400, 0x4E05E50} at a matching caller ret closes the entry hop [V live], after which CLOSES? becomes YES.

## TOOL REQUESTS

- python tools/livecap/request.py add eea6040_rax_target 0xEEA6040 --why "U-EL7e: read rax at CFG trampoline sub_eea6040 entry (jmp rax; [0xF99FFA0] holds its address, read-only, no writer) to resolve the runtime indirect targets of the texgroup_load -> sub_1289400 -> sub_4e05e50 entry hops and close the remaining static gap of L7e texture/atlas management" -> REJECTED: "4 requests already pending, ask again next unit" (livecapture queue full; retry at start of next unit).
- No capture request landed in this unit. No helper scripts written; no temp files left behind.
- Resume next unit: (a) retry the eea6040_rax_target capture, (b) if a hit shows rax in {0x5421C90, 0x1289400, 0x4E05E50} at a matching caller ret, cite it [V live] and set CLOSES? YES; otherwise keep NO with the same blocking fact.
