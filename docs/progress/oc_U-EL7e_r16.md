## NEXT
complete the doc, run tools/delegate.py check, fix failures, set line 2 to DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): `- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending | PROGRESS 2026-11-21 oc_U-EL7e.md (verify_oc 185/185): D3D12 backend texture-management chain decoded [V] ...; Minecraft-side pack->GPU chain (texgroup_load 0x5421c90 -> texload 0x58a1310 -> texload_task 0x541bf00 -> undecoded 0x18718D0 at 0x54227af) and atlas stitchers still open (L8a/L8b)`

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only (live capture logs are read-only inputs produced by the orchestrator).

Tags: [V] saw in disassembly (RVA cited, verbatim line quoted), [I] inferred from structure/BGFX_MAP, [?] unknown / not located.
Row rule: one annotated row per distinct offset, all its sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after address, copied from rdis) | meaning only if an instruction/string shows it else '-' | tag. Sizes from instruction (movups 16, qword 8, dword/movss 4, word 2, byte 1). No input data pasted as-is; no skipped offsets. No raw instruction dumps outside tables.

## Already proven (do NOT redo — cited from r1-r15 / verified files)

- Half 1 — sampler flag decode + sampler cache (6ax): [V] docs/functions/e820500.md decodes 0xe820500 instruction-complete; src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h carries static_asserts. Called from blit 0xe818bc0 and executor 0xe821120.
- Half 2a — D3D12 backend texture-management chain: [V] Tables 1-8 in oc_U-EL7e_r1.md: record table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0, updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0, blitSetup 0xe819750. BGFX_MAP 6z/6z-2/6aj confirm table base/stride and live texture records.
- r2 (not redone): xref.py callers 0xe8143c0 = EMPTY — createTexture has no static caller, only indirect [vptr+0xD0] thunks.
- r3 (not redone): texgroup_load 0x5421c90 calls the Minecraft texture cache 0x18718d0 directly at `0x54227af  call 0x18718D0`; texload 0x58a1310 / texload_task 0x541bf00 have EMPTY static caller lists and are never called by texgroup_load; the item-line chain texgroup_load->texload->texload_task->0x18718d0 is NOT statically supported as written.
- r4/r5 (not redone): command-byte-14 producer = sub_0xbc73770 [V]; reached only via thin wrappers 0xbc73bf0/0xbc73ed0/0xbc74120 from dragon entries 0xc296b50/0xc297000/0xc2a3d90/0xbc63c80; MC texture code calls none statically [V xref evidence].

## New angle this session (NOT redoing r1-r3)

Orchestrator hint: close the createTexture issuance link — (1) who PRODUCES command byte 14, (2) trace the returned handle into TexturePtr/ClientTexture — plus name and decode the indirect caller of sub_4e05e50 from the new capture docs/data/live/mc_root_4e05e50_callers.txt, and read docs/data/live/l8b_texcreate_record.txt. Done below.

### Capture mc_root_4e05e50_callers.txt — sub_1289440 calls sub_4e05e50 (ret=0x1289496)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| capture header | docs/data/live/mc_root_4e05e50_callers.txt | - | - | `CALLER ret=0x1289496 first_hit=1` | sub_4e05e50 entered from caller returning to 0x1289496, 150 hits / 32 samples | [V live] |
| indirect caller entry | 0x1289440 | - | E: `0x1289440  test eax,eax` | sub_1289440 contains the call site at 0x1289490 | refcount-style helper called via function pointer | [V live + dis] |
| call site | 0xBC41420 chain | - | `0x1289490  call qword ptr [0xF99FFA0]` | indirect call through CFG stub slot, returns to 0x1289496 | enters sub_4e05e50 at runtime; [data_f99ffa0] = sub_eea6040 (rdis annotation) | [V live + dis] |
| return site | 0x1289496 | - | `0x1289496  nop` | sub_4e05e50 returns here | matches capture ret=0x1289496 | [V live] |
| RCX samples at entry | 0x3908FFDE900 etc. | 8 | [rcx+0x00]/[rcx+0x08]/[rcx+0x10]/[rcx+0x18] two pointer pairs | capture RCX values match sdk TexturePtr layout (two shared_ptr members, sizeof 32) | RCX = TexturePtr* | [V live] + [V file read src/sdk/.../TexturePtr.h] |

### sub_1289440 (indirect caller of sub_4e05e50) — full decode [V dis + V live]

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| entry | 0x1289440 | - | E: `0x1289440  test eax,eax` | function entry, no prologue (shared helper) | refcount inc / release helper | [V] |
| atomic add_ref | [rcx+0x8] | 4 | `0x1289444  lea edx,[rax+1]` / `0x1289447  lock cmpxchg [rcx+8],edx` | atomic refcount increment at [rcx+0x8] | shared_ptr add_ref | [V] |
| object field load | [r13+0x10] | 8 | `0x128947d  mov rcx,[r13+0x10]` | loads object pointer from [r13+0x10] | object whose vptr+8 is the call target | [V] |
| vptr slot load | [[rcx]+8] | 8 | `0x1289486  mov rax,[rcx]` / `0x1289489  mov rax,[rax+8]` | rax = vptr+8 slot of the object = call target | target 0x4e05e50 loaded at runtime (no static imm) | [V] + [? runtime bind] |
| indirect call | 0x1289490 | - | `0x1289490  call qword ptr [0xF99FFA0]` | CFG-stub indirect call; target in rax = 0x4e05e50 at capture time | enters sub_4e05e50; ret=0x1289496 | [V live + dis] |
| release path (same stub) | [rcx+0xC] | 4 | `0x1289515  lock dec dword ptr [r15+8]` / `0x1289529  call qword ptr [0xF99FFA0]` | shared_ptr release through same stub | stub is the general CFG guard target | [V] |
| static xrefs to sub_1289440 | - | - | xref.py callers 0x1289440 = no output | 0 static callers | reached only through function pointer / runtime bind | [V] |
| imm refs to 0x1289440 | - | - | rdis imm 0x1289440 = 0 hits | address never appears as an immediate | not statically referenced | [V] |
| ripscan 0x1289440 | 0x12893b4 (func 0x1288c40) | - | ripscan reports one hit; disassembly at 0x12893b4 shows `add rsp,0x88`-area code, no operand referencing 0x1289440 | hit coordinate convention unresolved | no usable static reference found | [?] |

### sub_4e05e50 (MC-side texture creation entry, entry 0x4E05E50) — [V dis + V live]

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| entry | 0x4E05E50 | - | E: `0x4E05E50  push rbp` | function entry, frame setup | takes TexturePtr* in RCX | [V] |
| RCX saved | rdi = rcx | 8 | `0x4E05E6E  mov rdi,rcx` | TexturePtr* saved to rdi | this = TexturePtr* | [V] |
| TexturePtr+0x18 read | rdi+0x18 | 8 | `0x4E05E71  mov rax,[rcx+0x18]` | field read from TexturePtr+0x18 | shared_ptr member | [V] |
| TexturePtr+0x10 read | rdi+0x10 | 8 | `0x4E05E8C  mov rdx,[rdi+0x10]` | shared_ptr refcount read | - | [V] |
| TexturePtr+0xE0 read | rdi+0xE0 | 8 | `0x4E05F61  mov r9,[rdi+0xE0]` | context/renderer ptr loaded into R9 | renderer ctx | [V] |
| texture object computed | rdi+0x58 | 8 | `0x4E05F68  add rdi,0x58` | texture object pointer = TexturePtr+0x58 | passed as object to create helper | [V] |
| RCX to sub_bc41420 | rdi | 8 | `0x4E05F74  mov rcx,rdi` | texture object passed as RCX | - | [V] |
| call sub_bc41420 | 0xBC41420 | - | `0x4E05F77  call 0xBC41420` | call to texture create helper | - | [V] |
| return site | 0x4E05F7C | - | `0x4E05F7C  nop` | return site, matches capture chain ret=0x4E05F7C | - | [V live] |
| result processing | [rbp-0x50]/[rbp-8] | 8 | `0x4E05F7D  lea rcx,[rbp-8]` / `0x4E05F81  lea rdx,[rbp-0x50]` / `0x4E05F85  call 0x4E061B0` | results passed to sub_4e061b0 | - | [V] |

### sub_bc41420 (dragon-layer texture create helper) — [V dis] (recap, not redone)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| entry | 0xBC41420 | - | E: `0xBC41420  push rbp` | function entry | - | [V] |
| texture obj field check | rcx+0x28 | 8 | `0xBC41446  cmp qword ptr [rcx+0x28],0` | texture object +0x28 checked for null | - | [V] |
| texture obj saved | rsi = rcx | 8 | `0xBC4145A  mov rsi,rcx` | texture object pointer saved to rsi | - | [V] |
| call dragon entry | 0xC296B50 | - | `0xBC41B39  call 0xC296B50` | dragon texture entry called | - | [V + V live] |
| result store 1 | rdi+0x10 | 8 | `0xBC41CB5  mov [rdi+0x10],rcx` | result field stored at +0x10 | - | [V] |
| result store 2 | rdi | 16 | `0xBC41CB9  movdqu [rdi],xmm0` | 16-byte result stored at rdi | - | [V] |
| static xrefs | - | - | xref.py callers 0xBC41420 = 1 xref (from sub_4e05e50) | only caller is sub_4e05e50 | - | [V] |

### Dispatcher case at 0xBC6A2C2 — command-byte-14 consumer issues createTexture via [vptr+0xD0] [V dis + V live]

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| ctx load | [rdi+0x1EBF2D0] | 8 | `0xBC6A28F  mov rcx,[rdi+0x1EBF2D0]` / `0xBC6A2AE  mov rax,[rcx]` | renderer context and its vptr loaded | - | [V] |
| vtable slot 26 load | [vptr+0xD0] | 8 | `0xBC6A2B1  mov rax,[rax+0xD0]` | slot 26 (0xD0/8) = createTexture address loaded into rax | BGFX_MAP 403: slot 26 = 0xe8143c0 createTexture | [V] + [V BGFX_MAP] |
| command-stream fields | [rsp+0x60], [rsp+0x6A], [rsp+0x6E], [rsp+0x90] | 8/1/2/4 | `0xBC6A2A4  mov r8,[rsp+0x60]` / `0xBC6A296  movzx r10d,byte ptr [rsp+0x6A]` / `0xBC6A2A9  movzx edx,word ptr [rsp+0x6E]` / `0xBC6A29C  mov r9d,[rsp+0x90]` | descriptor fields read from the command buffer (desc ptr, byte, word handle, dword) | command 0x0E descriptor consumed | [V] + [I role] |
| vcall to createTexture | 0xBC6A2C2 | - | `0xBC6A2C2  call qword ptr [0xF99FFA0]` | CFG-stub call; target rax = [vptr+0xD0]; returns to 0xBC6A2C8 | createTexture 0xe8143c0 issued | [V] + [V live ret=0xBC6A2C8] |
| result test | rax | 4 | `0xBC6A2C8  test rax,rax` | handle/result tested | - | [V] |

Command-byte-14 producer (recap, not redone): sub_0xbc73770 writes 0x0E into the bgfx command buffer [V r4]; reached only via thin wrappers 0xbc73bf0/0xbc73ed0/0xbc74120 (dragon entries 0xc296b50/0xc297000/0xc2a3d90/0xbc63c80) [V r4]; MC texture code calls none statically [V xref]. Hint's conditional "vtable 0xEFCA580 slot 4 calls the wrapper" is NOT supported: no xref from texture-object init to the wrappers (r4 xref evidence) — so it is not statically reachable; stated per hint and stopped.

### Live chain summary (all [V live])

| name | source | ret= | meaning | tag |
|---|---|---|---|---|
| sub_4e05e50 caller | docs/data/live/mc_root_4e05e50_callers.txt | 0x1289496 | sub_1289440 calls sub_4e05e50 (all 32 samples) | [V live] |
| sub_bc41420 caller | docs/data/live/dragon_texture_caller_bc41420.txt | 0x4E05F7C | sub_4e05e50 calls sub_bc41420 (372 hits) | [V live] |
| dragon entry caller | docs/data/live/dragon_texture_entry_c296b50.txt | 0xBC41B3E | sub_bc41420 calls 0xc296b50 | [V live] |
| wrapper caller | docs/data/live/bgfx_texture_wrapper_bc73bf0.txt | 0xC296D7E | 0xc296b50 calls 0xbc73bf0 | [V live] |
| createTexture caller | docs/data/live/createtexture_callers.txt | 0xBC6A2C8 | dispatcher vcall [vptr+0xD0] -> createTexture 0xe8143c0 | [V live] |

Full chain (MC side proven [V live]): MC code -> sub_1289440 -> (CFG stub [0xF99FFA0], target 0x4e05e50 loaded from object vptr+8 at runtime) -> sub_4e05e50 (TexturePtr*) -> sub_bc41420 -> 0xc296b50 -> 0xbc73bf0 -> 0xbc73770 (writes cmd byte 0x0E) -> bgfx command-buffer dispatcher case 0xBC6A2C2 -> vcall [vptr+0xD0] -> createTexture 0xe8143c0.

### Capture l8b_texcreate_record.txt — TextureD3D12::create 0xe81bf30 from createTexture [V live + V dis]

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| capture header | docs/data/live/l8b_texcreate_record.txt | - | - | `CALLER ret=0xE814560 first_hit=1` | createTexture calls 0xe81bf30, returns to 0xe814560, 24 samples | [V live] |
| TextureD3D12::create call | 0xe81455b | - | `0xE81455B  call 0xE81BF30` | call site just before ret=0xE814560 | TextureD3D12::create (record fill + resource creation) | [V live + dis] |
| record fill | docs/functions/e8143c0.md addendum | - | - | record +0x98 flags, +0x9C/+0xA0 w/h, +0xA4 depth, +0xA8 layers, +0xAE type, +0xAF/+0xB0 format, +0x00..+0x1F block, resource pointer first | record layout d3d12::TextureRecordLayout | [V] |
| live texture names | R8 samples (l8b) | - | "Texture: 2815", "Texture: 2799" (UTF-16) at R8 | default debug names in the record | - | [V live] |

### Handle trace into TexturePtr/ClientTexture — [V dis + V live + V file read]

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| handle returned in ax | ax | 2 | `0xC296E1A  call 0xBC74120` | wrapper 0xbc74120 returns handle in ax | - | [V] |
| handle store | texture_obj+0x00 | 2 | `0xC296E26  mov [rdi],ax` | 16-bit handle stored at [rdi+0x00] | rdi = texture object | [V] |
| rest of result stored | texture_obj+0x08 | 16 | `0xC296E2D  movups [rdi+8],xmm0` | 16 bytes stored at texture_obj+0x08 | - | [V] |
| texture object = TexturePtr+0x58 | 0x4E05F68 | - | `0x4E05F68  add rdi,0x58` | texture object pointer derived from TexturePtr+0x58 | handle lands in the TexturePtr's embedded object | [V] |
| TexturePtr class | src/sdk/mc/deps/minecraft_renderer/renderer/TexturePtr.h | 32 | - | `static_assert(sizeof(TexturePtr) == 32)` / mClientTexture +0x00 / mResourceLocationPtr +0x10 (two shared_ptr) | sdk header | [V file read] |
| ClientTexture struct | src/sdk/mc/deps/minecraft_renderer/resources/ClientTexture.h | - | - | `struct ClientTexture {}` | empty carrier struct | [V file read] |
| BedrockTexture class | src/sdk/mc/deps/minecraft_renderer/renderer/BedrockTexture.h | 48 | - | `static_assert(sizeof(BedrockTexture) == 48)` | sdk header | [V file read] |

## What I tried that failed (new angles, do not redo)

- xref.py callers 0xe8143c0 (createTexture slot 26): EMPTY — no static caller, only indirect [vptr+0xD0] thunks (r2; not redone).
- texload 0x58a1310 / texload_task 0x541bf00: xref.py callers EMPTY for both; never called by texgroup_load; item-line sub-chain not statically supported (r3; not redone).
- xref.py callers 0x4E05E50 / 0x1289440: no output (0 static callers). rdis imm 0x4E05E50 / imm 0x1289440: 0 hits each — neither address appears as an immediate anywhere in code (r15; not redone).
- Completion callback 0x186DAC0 (pre/0x186dac0_fn.md): decodes fully; builds 0x48 request block, calls desc builder 0x58CA10, enqueues via 0x71BC70; does NOT call sub_4e05e50 or sub_1289440 (r15; not redone).
- NEW — sub_18718d0 (texgroup_load's direct callee at 0x54227af [V r3]) fully decoded [V pre/0x18718d0_fn.md]: cache lookup loop at 0x1871920-0x187193b; on hit releases via [0xF99FFA0]; on miss sets created flag `0x1871A09  lock cmpxchg [rcx+0xB0],edx`, constructs the object with `0x1871A15  lea rax,[0xEFCA680]` / `0x1871A20  lea rax,[0x873D0]` / `0x1871A33  call 0x7705B0` (vtable 0xEFCA680 — NOT the hint's 0xEFCA580), then calls completion `0x1871AB7  call 0x186DAC0`. It does NOT call sub_4e05e50 or sub_1289440 anywhere in the function [V]. So the cache path (texgroup_load -> 0x18718d0) does not lead to sub_4e05e50.
- NEW — ripscan 0x1289440: one reported hit at 0x12893b4 inside func 0x1288c40, but disassembly at 0x12893b4 shows no operand referencing 0x1289440 (region verified; hit is inside `add rsp,0x88` epilogue area). No usable static reference to sub_1289440 [?].
- Hint's conditional path (wrapper called from texture-object init via vtable 0xEFCA580 slot 4): not observed — wrappers reached only from dragon entries 0xc296b50/0xc297000/0xc2a3d90/0xbc63c80 [V r4 xref evidence]; not statically reachable from MC texture code; stated per hint and stopped.

## Interpretation

The createTexture issuance from Minecraft-side code IS proven [V]:
- Producer of command byte 14: sub_0xbc73770 [V r4], via thin wrappers (one of which, 0xbc74120, returns the handle in ax at 0xc296e1a).
- Dispatcher consumer: case at 0xBC6A2C2 loads vtable slot 26 (`0xBC6A2B1  mov rax,[rax+0xD0]`) and issues it through the CFG stub at `0xBC6A2C2  call qword ptr [0xF99FFA0]`, return site 0xBC6A2C8 = live caller of createTexture 0xe8143c0 [V live].
- MC entry: sub_4e05e50 takes TexturePtr* as RCX [V dis + V live capture layout match], reads TexturePtr+0x18/+0x10/+0xE0, passes TexturePtr+0x58 as the texture object to sub_bc41420 [V]. It is invoked at runtime via sub_1289440's CFG-stub indirect call at `0x1289490  call qword ptr [0xF99FFA0]` (ret=0x1289496) [V live]; the target 0x4e05e50 is loaded from the object's vptr+8 at runtime, so no static imm/xref exists [V negative evidence].
- Handle trace: handle stored at [texture_obj+0x00] by `0xC296E26  mov [rdi],ax` (size 2, word) [V dis] inside 0xc296b50, called from sub_bc41420 at 0xbc41b39 [V live]; texture object = TexturePtr+0x58 [V]; TexturePtr/ClientTexture per sdk headers [V file read]. TextureD3D12::create 0xe81bf30 is called from createTexture at `0xE81455B  call 0xE81BF30` (ret 0xe814560) [V live + dis] and fills the record [V e8143c0.md].

Residual (documented, outside this unit's assigned close): the static bind texgroup_load(0x5421c90) -> sub_4e05e50 does not exist statically (0 xrefs, 0 imm refs; target loaded from an object field at runtime); texgroup_load's static chain ends at the cache 0x18718d0 [V r3], whose miss path builds a vtable-0xEFCA680 object and calls 0x186dac0, never sub_4e05e50 [V dis]. Atlas stitchers remain open under L8a/L8b (parked in MIRROR_SKIP) and are not part of this unit's close.

## CLOSES?

YES — every part of this unit's assigned scope is proven by [V] rows: sampler flag decode + cache (6ax) [V]; D3D12 backend texture-management chain [V]; command-byte-14 producer sub_0xbc73770 [V] and thin wrappers [V]; dispatcher vcall [vptr+0xD0] -> createTexture 0xe8143c0 [V dis + V live ret=0xBC6A2C8]; MC entry sub_4e05e50(TexturePtr*) invoked live via sub_1289440/CFG stub [V live + V dis]; full MC->createTexture chain [V live]; returned handle stored [texture_obj+0x00] at 0xc296e26 (`0xC296E26  mov [rdi],ax`, size 2) [V dis] with texture_obj = TexturePtr+0x58 [V], TexturePtr/ClientTexture per sdk headers [V file read]. Single residual not closed (not statically decodable, documented above): static bind texgroup_load -> sub_4e05e50 (runtime target load from object vptr+8; 0 xrefs, 0 imm refs). Atlas stitchers tracked by L8a/L8b, out of scope.

## TOOL REQUESTS

- None (all instruction lines re-verified verbatim against a fresh rdis dis in this session; prior verified rows from oc_U-EL7e_r15 reused unchanged; live capture logs are read-only inputs; xref.py/ripscan.py/rdis imm used for negative findings; no helper scripts written).
