## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): `- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending | PROGRESS 2026-11-21 oc_U-EL7e.md (verify_oc 185/185): D3D12 backend texture-management chain decoded [V] ...; Minecraft-side pack->GPU chain (texgroup_load 0x5421c90 -> texload 0x58a1310 -> texload_task 0x541bf00 -> undecoded 0x18718D0 at 0x54227af) and atlas stitchers still open (L8a/L8b)`

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; live capture logs under docs/data/live are read-only inputs produced by the orchestrator.

Tags: [V] saw in disassembly (RVA cited, verbatim line quoted) / [V live] saw in an orchestrator live capture log (file cited) / [I] inferred from structure or BGFX_MAP / [?] unknown or not located.

Row rule: one annotated row per distinct offset, all its read/store sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after address, copied verbatim from rdis) | meaning ONLY if an instruction/string shows it else '-' | tag. Sizes from the instruction (movups/movaps/movdqu/movdqa 16, qword 8, dword/movss 4, word 2, byte 1). No input data pasted as-is; no skipped offsets among quoted sites; no raw instruction dumps outside tables; no ellipsis or catch-all rows.

## NEW WORK THIS SESSION — [0xF99FFA0] writer resolution (r22 directive)

Pending fact carried from r25 (CLOSES? NO): no [V]-proven static path texgroup_load(0x5421c90) -> sub_4e05e50. sub_4e05e50 has 0 static xrefs and is reached only via sub_12893d0's indirect tail-call through the global slot [0xF99FFA0]. r22's directed new work: "resolve the pointer in [0xF99FFA0] ... by locating its writer (xref to 0xF99FFA0 as a store) and name the function it is set to; if that is sub_4e05e50 the static link is closed."

### 1. Exact disassembly around the [0xF99FFA0] call (fresh rdis this session)

| offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| object vptr load | 0x1289486 | 8 | [rcx+0x0] | `0x1289486  mov rax,[rcx]` | rax = object vptr (rcx = texture job object) | [V] |
| vtable slot 1 load | 0x1289489 | 8 | [rax+0x8] | `0x1289489  mov rax,[rax+8]` | rax = obj->vptr[1] = indirect call target | [V] |
| argument setup | 0x128948d | 8 | reg | `0x128948d  mov rdx,rbx` | rdx = rbx (element pointer argument) | [V] |
| indirect tail-call | 0x1289490 | 8 | [0xF99FFA0] | `0x1289490  call qword ptr [0xF99FFA0]` | indirect call through global slot; rdis resolves `[data_f99ffa0] = sub_eea6040`; NO store to [0xF99FFA0] exists between 0x1289489 and 0x1289490 (only `mov rdx,rbx`) | [V] |
| capture return site | 0x1289496 | 1 | - | `0x1289496  nop` | instruction right after the call; matches capture ret=0x1289496 in all 32 samples (mc_root_4e05e50_callers.txt) | [V] + [V live] |

### 2. What [0xF99FFA0] is set to

| offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| trampoline body | 0xEEA6040 | 1 | - | `0xEEA6040  jmp rax` | sub_eea6040 is a single-instruction trampoline: tail-jump to rax (the target set by the caller) | [V] |
| alternate trampoline entry | 0xEEA6060 | 8 | [0xF99FFA0] | `0xEEA6060  jmp qword ptr [0xF99FFA0]` | second entry jumps through the same global slot; rdis resolves `[data_f99ffa0] = sub_eea6040` | [V] |

### 3. Writer search for [0xF99FFA0] — result

- `rdis imm 0xEEA6040` → `0 hit(s)`: no instruction in .text loads the trampoline's address as an immediate, so there is no static `mov [0xF99FFA0], offset sub_eea6040`-style writer in code [V].
- `xref.py ptr 0xF99FFA0` → `.rdata 0xefc6a08` only: a single data-section reference to the global's own address; no code writer located [V].
- sub_12893d0 (disassembled above) contains no `mov [0xF99FFA0], ...`: the target travels in `rax` and the global is only ever called/jumped through [V].
- rdis annotates every [0xF99FFA0] use site as `[data_f99ffa0] = sub_eea6040` (data/relocation resolution: the global is initialized by the image/loader) [V].

### 4. Resolution

[0xF99FFA0] is set to **sub_eea6040** (the `jmp rax` trampoline at 0xEEA6040), NOT to sub_4e05e50. No code writes sub_4e05e50's address into [0xF99FFA0]. The real call target `rax = obj->vptr[1]` is bound at runtime (vtable 0xF215838 slot 1 = sub_4e05e50, live vptr = 0x7FF6A8215838 across all 32 capture samples). r22's closure condition ("if that is sub_4e05e50 the static link is closed") is **NOT met**.

## Already proven (r1-r25; not re-quoted, not redone)

- Half 1 — sampler flag decode + sampler cache (6ax): [V] docs/functions/e820500.md decodes 0xe820500 instruction-complete; src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h carries the static_asserts; called from blit 0xe818bc0 and executor 0xe821120.
- Half 2a — D3D12 backend texture-management chain: [V] record table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0, updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0, blitSetup 0xe819750; BGFX_MAP 6z/6z-2/6aj confirm table base/stride and live texture records.
- createTexture issuance chain from MC code [V live + dis r22]: sub_4e05e50 -> `0x4E05F77  call 0xBC41420` -> sub_bc41420 -> 0xc296b50 -> wrapper 0xbc73bf0 -> producer 0xbc73770 (command-byte-0x0E) -> bgfx dispatcher case 0xBC6A2C2 (`0xBC6A2B1  mov rax,[rax+0xD0]`, slot 26 = 0xe8143c0 [V BGFX_MAP]) -> `0xBC6A2C2  call qword ptr [0xF99FFA0]` -> createTexture 0xe8143c0 -> `0xE81455B  call 0xE81BF30` TextureD3D12::create (ret 0xe814560 [V live]). Returned handle `0xC296E1A  call 0xBC74120` (ax) -> `0xC296E26  mov [rdi],ax` at texture_obj+0x00 [V r22]; texture_obj = TexturePtr+0x58 (`0x4E05F68  add rdi,0x58`); sdk TexturePtr/ClientTexture [V file read].
- sub_12893d0 = indirect caller of sub_4e05e50 [V]: deferred-texture-transaction flush; for each 0x18-byte element {ptr@0, shared_ctrl@8, obj@0x10} it add_refs [ctrl+8], copies the 16-byte element, then tail-calls obj->vptr[1](&element) through trampoline [0xF99FFA0] = sub_eea6040 `jmp rax`; at capture time vptr[1] = sub_4e05e50, return address 0x1289496 [V live]. 13 xrefs in; static callers sub_6632bf0 (2 sites), sub_1145c20 (2 sites), sub_6622610, sub_66232b0 (8 sites) — none is texgroup_load/texload/texload_task; all upward chains dead-end at 0-static-caller functions [V rdis/xref].
- sub_4e05e50: 0 static xrefs (`rdis callers 0x4E05E50` -> 0 calling functions; fn [0x4E05E50..0x4E06074) size 0x224). Entry `0x4E05E50  push rbp`; reads object+0xE0 renderer ctx (`0x4E05F61  mov r9,[rdi+0xE0]`), texture sub-object at object+0x58 (`0x4E05F68  add rdi,0x58`), calls `0x4E05F77  call 0xBC41420`, return site `0x4E05F7C  nop` [V live ret=0x4E05F7C]. RCX is a polymorphic texture OBJECT (constant vptr 0x7FF6A8215838 = RVA 0xF215838 + base; vptr[1] = sub_4e05e50), NOT a TexturePtr* (TexturePtr is 32 bytes, non-polymorphic, `static_assert(sizeof(TexturePtr) == 32)` [V file read]).
- Vtable 0xF215838: slot 0 = sub_4e060b0 (destroying destructor), slot 1 = sub_4e05e50 [V rdis vt]; live capture vptr = 0x7FF6A8215838 [V live]. Constructor sub_4e05450 sets vptr=0xF215838 (`0x4E05654  mov [rbx],r8`), inits texture sub-object at +0x58 (`0x4E05689  movups [rbx+0x58],xmm1`), stores renderer ctx at +0xE0 (`0x4E0573A  mov [rbx+0xE0],rax`) [V dis]. sub_4e05450 has 16 static callers, none is texgroup_load/texload/texload_task [V rdis callers].
- Full live chain [V live] (capture logs, read-only inputs): sub_4e05e50 caller ret=0x1289496 (mc_root_4e05e50_callers.txt, 32 samples); sub_bc41420 caller ret=0x4E05F7C (dragon_texture_caller_bc41420.txt); dragon entry caller ret=0xBC41B3E (dragon_texture_entry_c296b50.txt); wrapper caller ret=0xC296D7E (bgfx_texture_wrapper_bc73bf0.txt); createTexture caller ret=0xBC6A2C8 (createtexture_callers.txt).

## What I tried that failed (this session; do not redo r1-r25)

- [0xF99FFA0] writer search (the r22-directed new work): `rdis imm 0xEEA6040` → 0 hits; `xref.py ptr 0xF99FFA0` → only `.rdata 0xefc6a08`; sub_12893d0 contains no store to [0xF99FFA0]. Result: [0xF99FFA0] = sub_eea6040 trampoline, not sub_4e05e50 — r22 closure condition NOT met, static link NOT closed via this route.
- (carried from r25, not redone) Upward caller chains from all four sub_12893d0 callers (sub_1145c20, sub_6622610, sub_66232b0, sub_6632bf0): every top function has 0 static callers [V rdis/xref] — none is texgroup_load/texload. sub_4e060b0: 0 static callers. sub_4e05450: 16 static callers, none is texgroup_load/texload/texload_task. rdis imm 0x4E05E50: 0 hits. rdis imm 0x4E060B0: 0 hits. TexturePtr* claim for sub_4e05e50's RCX: refuted — RCX is a polymorphic texture object (constant vptr, reads object+0xE0) [V live + dis], not a 32-byte TexturePtr [V file read]. xref.py callers 0xe8143c0 EMPTY; texload/texload_task EMPTY; 0x18718d0 cache path (vtable 0xEFCA680) never calls sub_4e05e50/sub_12893d0 [V prior]; texgroup_load's static chain ends at `0x54227AF call 0x18718D0` [V].

## CLOSES?

NO — blocking fact: no [V]-proven static path texgroup_load(0x5421c90) -> sub_4e05e50. sub_4e05e50 has 0 static xrefs and is reached only via sub_12893d0's indirect tail-call `0x1289490  call qword ptr [0xF99FFA0]` through trampoline [0xF99FFA0] = sub_eea6040 (`jmp rax`; rax = obj->vptr[1] = sub_4e05e50 at runtime; capture ret site 0x1289496 [V live]). r22-directed writer search resolved [0xF99FFA0] to sub_eea6040 (image/loader-initialized; `rdis imm 0xEEA6040` → 0 hits; `xref.py ptr 0xF99FFA0` → only `.rdata 0xefc6a08`); no code writes sub_4e05e50 into [0xF99FFA0], so the static link is NOT closed. sub_12893d0's static callers (sub_6632bf0, sub_1145c20, sub_6622610, sub_66232b0 — 13 sites [V rdis callers this session]) none is texgroup_load/texload/texload_task and all upward chains dead-end at 0-static-caller functions [V rdis/xref]; sub_4e05450's 16 static callers none is texgroup_load/texload/texload_task [V rdis callers]; texgroup_load's static chain ends at `0x54227AF call 0x18718D0`, and cache 0x18718d0 builds objects with vtable 0xEFCA680 (different type, never calls sub_4e05e50/sub_12893d0) [V prior]. Everything else in the item is [V]-proven: sampler flag decode + cache (6ax), D3D12 backend texture-management chain, command-byte-14 producer sub_bc73770 [V r4], dispatcher [vptr+0xD0] -> createTexture 0xe8143c0 [V live + dis], returned handle stored at [texture_obj+0x00] (`0xC296E26  mov [rdi],ax`, size 2) [V], texture_obj = TexturePtr+0x58 [V], sdk TexturePtr/ClientTexture [V file read]. Atlas stitchers (L8a/L8b) remain out of scope (MIRROR_SKIP).

## TOOL REQUESTS

- None. Static analysis is exhausted: sub_4e05e50 has 0 static xrefs; [0xF99FFA0] resolves to the sub_eea6040 `jmp rax` trampoline with no code writer (imm search 0 hits, xref ptr single data ref); the texgroup_load -> sub_4e05e50 bind is runtime-only via vtable[1] indirect dispatch. No helper scripts written; all instruction lines re-verified verbatim against a fresh rdis dis this session; live capture logs are read-only inputs.
