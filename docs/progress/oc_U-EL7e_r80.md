## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): `- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending | PROGRESS 2026-11-21 oc_U-EL7e.md (verify_oc 185/185): D3D12 backend texture-management chain decoded [V] ...; Minecraft-side pack->GPU chain (texgroup_load 0x5421c90 -> texload 0x58a1310 -> texload_task 0x541bf00 -> undecoded 0x18718D0 at 0x54227af) and atlas stitchers still open (L8a/L8b)`

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; live capture logs under docs/data/live are read-only inputs produced by the orchestrator (read this session: mc_root_4e05e50_callers.txt, l8b_texcreate_record.txt, dragon_texture_caller_bc41420.txt, dragon_texture_entry_c296b50.txt, bgfx_createtexture_producer.txt, createtexture_callers.txt).

Tags: [V] saw in disassembly (RVA cited, verbatim `0xRVA  instr` quoted) / [V live] saw in an orchestrator live capture log (file cited) / [I] inferred from structure or tool output / [?] unknown or not located.

Row rule: one annotated row per distinct offset, all its sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after the address, copied verbatim from rdis) | meaning ONLY if an instruction/string shows it else '-' | tag. Sizes from the instruction (movups/movaps/movdqu/movdqa 16, qword 8, dword/movss 4, word 2, byte 1). No input data pasted as-is; no skipped offsets among quoted sites; no raw instruction dumps outside tables; no ellipsis or catch-all rows.

## Work this session (the one pending part of L7e)

Pending per r37/r38/r39: decode what rax holds at the `jmp rax` trampoline (`0xF99FFA0` slot) — i.e. resolve the indirect target of the MC-side entry to sub_4e05e50 — and confirm there is no static writer of [0xF99FFA0] to name. Everything below sub_4e05e50 (issuance chain, handle store, TexturePtr/sdk headers, backend chain, sampler half) was already [V]/[V live]-proven in r1-r39 and is not re-decoded here.

### 1. Trampoline slot [0xF99FFA0]: no static writer; holds jmp-rax trampoline

| name | offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| trampoline at slot value | 0xEEA6040 | 2 | - | `0xEEA6040  jmp rax` | [0xF99FFA0] = sub_eea6040: tail-call through rax | [V] |
| slot decodes as data | 0xF99FFA0 | - | E: `0xF99FFA0  (bad)` | linear decode of slot entry yields (bad) = embedded pointer data, not code | slot holds a pointer value | [V] |
| slot reads: mc_root dispatch | 0xF99FFA0 | 8 | R: `0x1289490  call qword ptr [0xF99FFA0]` | sub_12893d0 tail-calls job->vptr[1] through slot; ret lands at 0x1289496 | indirect-call site | [V] |
| slot reads: bgfx dispatcher | 0xF99FFA0 | 8 | R: `0xBC6A2C2  call qword ptr [0xF99FFA0]` | dispatcher calls renderer-ctx vtable[26] through slot | indirect-call site | [V] |
| slot reads: sub_4e05e50 internal | 0xF99FFA0 | 8 | R: `0x4E05E86  call qword ptr [0xF99FFA0]` | sub_4e05e50 itself lowers an indirect call through the same slot | general codegen lowering | [V] |
| writer search: imm slot address | 0xF99FFA0 | - | - | `imm 0xF99FFA0` = 0 hits | slot address never materialized in code | [I] |
| writer search: imm sub_4e05e50 | 0x4E05E50 | - | - | `imm 0x4E05E50` = 0 hits | sub_4e05e50 never materialized as an immediate | [I] |
| store forms to slot | 0xF99FFA0 | - | - | `xr 0xF99FFA0`: ~1.09M references, all reads (`call` / `mov reg`), 0 stores | no static writer exists | [V] [I] |

Interpretation: [0xF99FFA0] is constant image data (jmp-rax trampoline sub_eea6040). The callee is placed in RAX per call site and tail-called through the slot; there is no code writer to name and no static texgroup_load(0x5421c90) -> sub_4e05e50 link.

### 2. What rax holds at the jmp: sub_12893d0 loads obj->vptr[1] = sub_4e05e50 (vtable 0xF215838)

| name | offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| sub_12893d0 entry | 0x12893D0 | 1 | - | `0x12893D0  push rbp` | deferred job dispatch entry | [V] |
| job-object vptr load | 0x1289486 | 8 | R: `0x1289486  mov rax,[rcx]` | rax = job object vptr (job object at element+0x10) | vtable fetch | [V] |
| vtable slot 1 load = rax at jmp | 0x1289489 | 8 | R: `0x1289489  mov rax,[rax+8]` | rax = job->vptr[1] = value held in rax at the trampoline jmp | vtable[1] fetch | [V] |
| trampoline dispatch call | 0x1289490 | 8 | R: `0x1289490  call qword ptr [0xF99FFA0]` | tail-call rax through jmp-rax trampoline | dispatch to sub_4e05e50 at runtime | [V] |
| capture return site | 0x1289496 | 1 | - | `0x1289496  nop` | instruction after call; live capture CALLER ret=0x1289496 (all 32 samples) | [V live] |
| vtable 0xF215838 slot 1 | 0xF215838+8 | 8 | [0xF215838+8] | `rdis vt 0xF215838`: slot 1 = sub_4e05e50 | rax at the jmp = sub_4e05e50 statically (vtable[1]) | [V] |
| live vptr dumps | 0x7FF6A8215838 | 8 | - | mc_root_4e05e50_callers.txt RCX dumps start with vptr 0x7FF6A8215838 in all 32 samples | job object vtable = image base 0x140000000 + 0xF215838 | [V live] |

So rax at `0xEEA6040  jmp rax` = job->vptr[1] = sub_4e05e50 (vtable 0xF215838 slot 1 [V], observed live via ret=0x1289496 [V live]). This resolves the indirect target: sub_4e05e50 is entered only via this trampoline dispatch; `rdis callers 0x4E05E50` = 0 calling functions; sub_4e05e50 fn [0x4E05E50..0x4E06074) size 0x224.

### 3. MC-side connection: texgroup_load has no static link to sub_4e05e50 (blocking fact)

| name | offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| texgroup_load static chain end | 0x54227AF | 5 | S: `0x54227AF  call 0x18718D0` | texgroup_load's last static call enters the texture cache (cache objects vtable 0xEFCA680 != 0xF215838) | texgroup_load -> 0x18718D0 | [V] |
| sub_4e05e50 static callers | 0x4E05E50 | - | E: `0x4E05E50  push rbp` | `rdis callers 0x4E05E50`: 0 calling function(s) | no static caller of sub_4e05e50 | [V] |
| sub_12893d0 static callers | 0x12893D0 | - | E: `0x12893D0  push rbp` | 4 static callers (sub_6632bf0 x2, sub_1145c20 x2, sub_6622610 x1, sub_66232b0 x8); none is texgroup_load/texload/texload_task; all upward chains dead-end at 0-static-caller functions | dispatch feeders | [V] |
| sub_4e05450 constructor callers | 0x4E05450 | - | E: `0x4E05450  push rbp` | sets job-object vptr = 0xF215838 and inits texture sub-object at +0x58 / renderer ctx at +0xE0; 16 static callers, none texgroup_load/texload/texload_task | job-object builder | [V] |

## Already proven in r1-r39 (not re-decoded; cited)

- Half 1 — sampler flag decode + sampler cache (6ax): [V] docs/functions/e820500.md decodes 0xe820500 instruction-complete; src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h carries the static_asserts; called from blit 0xe818bc0 and executor 0xe821120.
- Half 2a — D3D12 backend texture-management chain: [V] record table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0, updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0, blitSetup 0xe819750; BGFX_MAP 6z/6z-2/6aj confirm table base/stride and live texture records.
- createTexture issuance below sub_4e05e50: [V live + dis] `0x4E05F77  call 0xBC41420` -> sub_bc41420 -> dragon entry 0xc296b50 -> wrapper 0xbc73bf0 -> command-byte-0x0E producer 0xbc73770 [V r4] -> bgfx dispatcher case (`0xBC6A2B1  mov rax,[rax+0xD0]`, slot 26 = 0xe8143c0 [V BGFX_MAP]) -> `0xBC6A2C2  call qword ptr [0xF99FFA0]` -> createTexture 0xe8143c0 -> `0xE81455B  call 0xE81BF30` TextureD3D12::create (ret 0xe814560 [V live]). Returned 16-bit handle `0xC296E1A  call 0xBC74120` (ax) -> `0xC296E26  mov [rdi],ax` (size 2) at job-object+0x58 (`0x4E05F68  add rdi,0x58`); texture object carries renderer ctx at +0xE0 (`0x4E05F61  mov r9,[rdi+0xE0]`). SDK TexturePtr/ClientTexture [V file read: sizeof(TexturePtr)==32, mClientTexture +0x00, mResourceLocationPtr +0x10]. Live: createtexture_callers.txt ONE caller ret=0xBC6A2C8; l8b_texcreate_record.txt ret=0xE814560; bgfx_createtexture_producer.txt ret=0xBC73EAD; dragon_texture_caller_bc41420.txt ret=0x4E05F7C; dragon_texture_entry_c296b50.txt ret=0xBC41B3E.

## CLOSES?

NO — blocking fact: no [V]-proven static path texgroup_load(0x5421c90) -> sub_4e05e50 exists. sub_4e05e50 has 0 static calling functions and is entered only via sub_12893d0's vtable[1] trampoline dispatch (`0x1289489  mov rax,[rax+8]` then `0x1289490  call qword ptr [0xF99FFA0]` -> `0xEEA6040  jmp rax` -> ret site 0x1289496 [V live]); vtable[1] of vtable 0xF215838 IS sub_4e05e50 [V] but that bind resolves in RAX per call through the constant trampoline slot [0xF99FFA0] (1.09M read refs, 0 stores — no static writer). texgroup_load's static chain ends at `0x54227AF  call 0x18718D0` (cache object vtable 0xEFCA680), a separate system from the vtable-0xF215838 job objects built by sub_4e05450. Every other pending part of L7e is [V]/[V live]-proven (sampler half 6ax; backend chain; command-byte-14 createTexture issuance; handle store into the texture object; TexturePtr/ClientTexture sdk headers). Atlas stitchers L8a/L8b remain separate open items (oc_U-EL8a/oc_U-EL8b).

## Verification

- `python tools/sigs/verify_oc.py docs/progress/oc_U-EL7e.md` — every backticked `0xRVA  instr` line must match rdis dis output (mismatch=0, no-such-instr=0).
- `python tools/delegate.py check docs/progress/oc_U-EL7e.md` — must exit 0; only then is the line after `## NEXT` set to DONE.

## TOOL REQUESTS

- None (no helper scripts written, no temporary files left; all instruction lines to be re-verified verbatim against a fresh rdis dis of the 1.26.62.01 exe; xr/imm/vt/fn/callers used for positive and negative findings; live capture logs are read-only inputs).
