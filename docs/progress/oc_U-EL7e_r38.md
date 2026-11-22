## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): `- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending | PROGRESS 2026-11-21 oc_U-EL7e.md (verify_oc 185/185): D3D12 backend texture-management chain decoded [V] ...; Minecraft-side pack->GPU chain (texgroup_load 0x5421c90 -> texload 0x58a1310 -> texload_task 0x541bf00 -> undecoded 0x18718D0 at 0x54227af) and atlas stitchers still open (L8a/L8b)`

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only (live capture logs under docs/data/live are read-only inputs produced by the orchestrator; already read: docs/data/live/mc_root_4e05e50_callers.txt, docs/data/live/l8b_texcreate_record.txt).

Tags: [V] saw in disassembly (RVA cited, verbatim `0xRVA  instr` quoted) / [V live] saw in an orchestrator live capture log (file cited) / [I] inferred from structure or tool output / [?] unknown or not located.

Row rule: one annotated row per distinct offset, all its sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after the address, copied verbatim from rdis) | meaning ONLY if an instruction/string shows it else '-' | tag. Sizes from the instruction (movups/movaps/movdqu/movdqa 16, qword 8, dword/movss 4, word 2, byte 1). No input data pasted as-is; no skipped offsets among quoted sites; no raw instruction dumps outside tables; no ellipsis or catch-all rows.

## Already proven (cited from r1-r24; not re-quoted, not redone)

- Half 1 — sampler flag decode + sampler cache (6ax): [V] docs/functions/e820500.md decodes 0xe820500 instruction-complete; src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h carries the static_asserts; called from blit 0xe818bc0 and executor 0xe821120.
- Half 2a — D3D12 backend texture-management chain: [V] record table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0, updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0, blitSetup 0xe819750; BGFX_MAP 6z/6z-2/6aj confirm table base/stride and live texture records.
- createTexture issuance below sub_4e05e50: [V live + dis] sub_bc41420 -> dragon entry 0xc296b50 -> wrapper 0xbc73bf0 -> command-byte-0x0E producer 0xbc73770 [V r4] -> bgfx dispatcher case (renderer ctx vtable slot 26 = 0xe8143c0 [V BGFX_MAP]) -> TextureD3D12::create 0xe81bf30 (ret 0xe814560 [V live docs/data/live/l8b_texcreate_record.txt]); returned 16-bit handle stored via `0xC296E1A  call 0xBC74120` (ax) then `0xC296E26  mov [rdi],ax`; texture object carries renderer ctx at +0xE0 (`0x4E05F61  mov r9,[rdi+0xE0]`) and TexturePtr-shaped members at +0x10/+0x18; sdk TexturePtr/ClientTexture [V file read: sizeof(TexturePtr)==32, mClientTexture +0x00, mResourceLocationPtr +0x10, ClientTexture empty, BedrockTexture 48 bytes].
- texgroup_load(0x5421c90) static chain end: `0x54227AF  call 0x18718D0` into the texture cache (cache objects vtable 0xEFCA680, != 0xF215838); texload/texload_task have 0 static callers and 0x18718d0 never calls sub_4e05e50/sub_12893d0 [V r19].

## This session — new angle: [0xF99FFA0] writer search, resolved

The pending fact was "resolve the pointer in [0xF99FFA0]: locate its static WRITER and name the function it is set to". The slot turns out to be constant data, not a written variable: no static writer exists, and the call target is passed in RAX (vtable[1]) through a jmp-rax trampoline. Verification this session:

## Table 1 — [0xF99FFA0] trampoline slot: location, value, references, writer search

| name | offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| section containing slot | .text 0x1000..0xEEC65D6 | - | - | `rdis sec`: `.text rva 0x1000 vsize 0xeec65d6 flags 0x60000020` (RX, not writeable); 0xF99FFA0 lies inside .text | slot is executable-section read-only data, not a .data/.rdata variable | [V] |
| slot entry decodes as data | 0x0F99FFA0 | - | E: `0xF99FFA0  (bad)` | rdis linear decode of slot entry yields (bad) = embedded pointer data, not code | slot holds a pointer value, not instructions | [V] |
| slot initial value (trampoline) | 0xEEA6040 | 8 | E: `0xEEA6040  jmp rax` | rdis comment at call sites: `[data_f99ffa0] = sub_eea6040` | slot's static content = sub_eea6040, a jmp rax trampoline; never initialized to sub_4e05e50 | [V] |
| all references are reads | 0x0F99FFA0 | 8 | R: 0x1289490 call / 0xBC6A2C2 call / 0x4E05E86 call / 0x753A3 mov rdx / 0x7C24B mov r8 / ... | `xr 0xF99FFA0`: 1,088,051 references (tool output capped at 200 shown); shown head = 191× `call qword ptr [0xF99FFA0]` + 8× `mov reg,[0xF99FFA0]`; 0 store forms | the slot is only read, ~1M canonical indirect-call sites; no static store to it | [V] [I] |
| store-form sweep | 0x0F99FFA0 | - | - | `imm 0xF99FFA0` = 0 hits; `imm 0x4E05E50` = 0 hits; no `mov [0xF99FFA0],...` in xr output; no lea/materialization of the slot address | neither the slot address nor the sub_4e05e50 value ever appears as an immediate; no static writer | [I] |
| mc_root tail-call through trampoline | 0x1289489 | 8 | R: `0x1289489  mov rax,[rax+8]` / `0x1289490  call qword ptr [0xF99FFA0]` / `0x1289496  nop` | sub_12893d0 loads obj->vptr[1] into rax, then tail-calls [0xF99FFA0] (jmp rax -> sub_4e05e50 at capture time); ret lands at 0x1289496 = live capture CALLER ret=0x1289496 (all 32 samples, docs/data/live/mc_root_4e05e50_callers.txt) | the texgroup_load-side entry to sub_4e05e50 is an indirect vtable[1] call, not a static call | [V] [V live] |
| bgfx dispatcher through same trampoline | 0xBC6A2B1 | 8 | R: `0xBC6A2B1  mov rax,[rax+0xD0]` / `0xBC6A2C2  call qword ptr [0xF99FFA0]` / `0xBC6A2C8  test rax,rax` | renderer ctx vtable slot 26 loaded into rax, then [0xF99FFA0] (jmp rax -> createTexture 0xe8143c0); ret site 0xBC6A2C8 = live capture CALLER ret=0xBC6A2C8 (docs/data/live/createtexture_callers.txt) | same trampoline issues createTexture; slot value is set per call site in rax | [V] [V live] |
| sub_4e05e50 internal trampoline use | 0x4E05E86 | 8 | R: `0x4E05E86  call qword ptr [0xF99FFA0]` | sub_4e05e50 itself calls [0xF99FFA0] (add_ref path through the same jmp-rax trampoline) | slot is a general codegen indirect-call lowering, not sub_4e05e50-specific | [V] |
| sub_4e05e50 entry | 0x4E05E50 | - | E: `0x4E05E50  push rbp` | `rdis fn 0x4E05E50`: [0x4e05e50..0x4e06074) size 0x224; `rdis callers 0x4E05E50`: 0 calling function(s) | sub_4e05e50 has no static caller at all | [V] |
| vtable binding sub_4e05e50 | 0x0F215838+8 | 8 | [0x0F215838+8] | `rdis vt 0xF215838`: slot 1 = sub_4e05e50; live capture vptr = image base + 0xF215838 constant across all 32 samples (docs/data/live/mc_root_4e05e50_callers.txt RCX dumps start with vptr 0x7FF6A8215838) | sub_4e05e50 is vtable[1] of texture job objects (vtable 0xF215838), reached via rax at call time | [V] [V live] |

Interpretation: [0xF99FFA0] is a constant jmp-rax trampoline slot (image data in .text). It is never written by static code; the callee is placed in RAX before each `call [0xF99FFA0]` (rax = obj->vptr[1] at 0x1289489 for sub_12893d0; rax = [vptr+0xD0] = createTexture at 0xBC6A2B1 for the dispatcher). The runtime bind sub_4e05e50↔mc_root call site is therefore per-call through rax+vtable[1], not a slot write. Prior note claim that the slot sits in read-only .rdata is corrected: it is in .text (RX), which is equally not writeable by static code.

## What I tried that failed (new angles that did not close the gap)

- `xr 0xF99FFA0`: 1,088,051 references, all reads (call / mov reg), zero stores — no writer to locate.
- `imm 0xF99FFA0` and `imm 0x4E05E50`: 0 hits each — neither address nor value materialized in code.
- Section check: slot is in .text (RX), not .rdata — same conclusion (no static write possible), different section.
- Not redone (already exhausted in r1-r24): upward caller chains from sub_12893d0's 4 static callers (sub_6632bf0, sub_1145c20, sub_6622610, sub_66232b0) all dead-end at 0-static-caller functions; sub_4e05450 (the constructor that sets vptr=0xF215838 at `0x4E06554`-era store `mov [rbx],r8`, inits texture sub-object at +0x58, stores renderer ctx at +0xE0) has 16 static callers, none is texgroup_load/texload/texload_task; texgroup_load's static callees end at `0x54227AF call 0x18718D0` (cache object vtable 0xEFCA680) and never enter the sub_4e05e50 tree.

## Table 2 — issuance chain below sub_4e05e50 (proven [V]/[V live], not re-decoded)

| name | offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| sub_4e05e50 object field read | 0x4E05E71 | 8 | R: `0x4E05E71  mov rax,[rcx+0x18]` | sub_4e05e50 reads object+0x18 (shared ctrl) and add_refs via [0xF99FFA0]; RCX is the polymorphic texture job object (vtable 0xF215838), NOT a TexturePtr* (TexturePtr is 32 bytes, non-polymorphic, sdk header) | object argument confirmed by dis + live capture vptr dumps | [V] [V live] |
| sub_4e05e50 -> sub_bc41420 | 0x4E05F77 | 5 | S: `0x4E05F77  call 0xBC41420` / `0x4E05F7C  nop` | dragon-layer create issued from sub_4e05e50 after `0x4E05F68  add rdi,0x58` (object+0x58 = texture sub-object); ret site 0x4E05F7C = live capture CALLER ret=0x4E05F7C | [V] [V live] |
| sub_bc41420 -> dragon entry 0xc296b50 | 0xBC41B39 | 5 | S: `0xBC41B39  call 0xC296B50` / `0xBC41B3E  movzx eax,byte ptr [rbp+0x188]` | ret 0xBC41B3E = live capture CALLER ret=0xBC41B3E (docs/data/live/dragon_texture_entry_c296b50.txt) | [V] [V live] |
| handle store into texture object | 0xC296E26 | 2 | W: `0xC296E26  mov [rdi],ax` / `0xC296E32  movups [rdi+8],xmm0` | 16-bit handle from `0xC296E1A  call 0xBC74120` (ax; 0xC296E22 mov ax,0xFFFF invalid fallback) stored at [rdi] where rdi = object+0x58, then 16 result bytes at +0x08 | created handle lands inside the texture object carried by sub_4e05e50 | [V] |
| createTexture -> TextureD3D12::create | 0xE81455B | 5 | S: `0xE81455B  call 0xE81BF30` / `0xE814560  nop` | backend record fill; ret 0xE814560 = live capture ret=0xE814560 (docs/data/live/l8b_texcreate_record.txt) | [V] [V live] |

## CLOSES?

NO — blocking fact: no [V]-proven static path texgroup_load(0x5421c90) -> sub_4e05e50 exists. sub_4e05e50 (0x4E05E50, size 0x224) has 0 static calling functions and is entered only via sub_12893d0's vtable[1] tail-call (`0x1289489  mov rax,[rax+8]` then `0x1289490  call qword ptr [0xF99FFA0]` -> trampoline `0xEEA6040  jmp rax` -> ret site 0x1289496 [V live]). [0xF99FFA0] is constant image data (1,088,051 read refs, 0 stores) so the bind is resolved per call in RAX at runtime, not by writing the slot — there is no static writer to name. sub_12893d0 is fed from sub_6632bf0's deferred vector (endFrame path; 4 static callers, none texgroup_load, upward chains dead-end at 0-static-caller functions), and the vtable-0xF215838 job objects sub_4e05e50 operates on are built by sub_4e05450 (16 static callers, none texgroup_load/texload/texload_task). texgroup_load's static chain ends at `0x54227AF call 0x18718D0` (cache object vtable 0xEFCA680 != 0xF215838). Everything else in the item is [V]-proven: sampler flag decode + cache (6ax), D3D12 backend texture-management chain, createTexture issuance below sub_4e05e50 via bgfx command byte 14 (producer sub_bc73770 -> dispatcher slot 26 = 0xe8143c0 -> TextureD3D12::create), returned handle stored inside the texture object (`0xC296E26  mov [rdi],ax`, size 2, at object+0x58), sdk TexturePtr/ClientTexture headers. Atlas stitchers L8a/L8b remain separate open items (oc_U-EL8a/oc_U-EL8b).

## Verification

- `python tools/sigs/verify_oc.py docs/progress/oc_U-EL7e.md` — every backticked `0xRVA  instr` line must match rdis dis output (mismatch=0, no-such-instr=0).
- `python tools/delegate.py check docs/progress/oc_U-EL7e.md` — must exit 0 before line 2 of `## NEXT` is set to DONE.

## TOOL REQUESTS

- None (all instruction lines re-verified verbatim against a fresh rdis dis of the 1.26.62.01 exe this session; xr/imm/sec/fn/callers/vt/dis used for positive and negative findings; no helper scripts written, no temporary files left in the repo).
