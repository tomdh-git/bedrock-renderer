## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): `- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending | PROGRESS 2026-11-21 oc_U-EL7e.md (verify_oc 185/185): D3D12 backend texture-management chain decoded [V] ...; Minecraft-side pack->GPU chain (texgroup_load 0x5421c90 -> texload 0x58a1310 -> texload_task 0x541bf00 -> undecoded 0x18718D0 at 0x54227af) and atlas stitchers still open (L8a/L8b)`

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only (live capture logs under docs/data/live are read-only inputs produced by the orchestrator).

Tags: [V] saw in disassembly (RVA cited, verbatim line quoted) / [V live] saw in an orchestrator live capture log (file cited) / [I] inferred from structure or BGFX_MAP / [?] unknown or not located.

Row rule: one annotated row per distinct offset, all its read/store sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after the address, copied verbatim from rdis) | meaning ONLY if an instruction/string shows it else '-' | tag. Sizes from the instruction (movups/movaps/movdqu/movdqa 16, qword 8, dword/movss 4, word 2, byte 1). No input data pasted as-is; no skipped offsets among quoted sites; no raw instruction dumps outside tables; no ellipsis or catch-all rows.

## Already proven (cited from r1-r37; not re-quoted, not redone)

- Half 1 — sampler flag decode + sampler cache (6ax): [V] docs/functions/e820500.md decodes 0xe820500 instruction-complete; src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h carries the static_asserts; called from blit 0xe818bc0 and executor 0xe821120.
- Half 2a — D3D12 backend texture-management chain: [V] record table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0, updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0, blitSetup 0xe819750; BGFX_MAP 6z/6z-2/6aj confirm table base/stride and live texture records.
- Issuance chain below sub_4e05e50 [V live + dis r24-r37]: sub_4e05e50 -> `call 0xBC41420` -> sub_bc41420 -> 0xc296b50 -> wrapper 0xbc73bf0 -> producer 0xbc73770 (bgfx command byte 0x0E) -> bgfx dispatcher [vptr+0xD0] slot 26 = 0xe8143c0 -> createTexture 0xe8143c0 -> TextureD3D12::create 0xE81BF30 -> returned 16-bit handle in ax -> `mov [rdi],ax` at texture_obj+0x00, texture_obj = TexturePtr+0x58; TexturePtr/ClientTexture sdk headers [V file read]. l8b_texcreate_record.txt [V live] confirms createTexture -> TextureD3D12::create (ret=0xE814560) with live texture records ("Texture: 2815", "Texture: 2799" name strings).
- [0xF99FFA0] [V r22/r37]: .rdata read-only initializer (section flags 0x40000040) = 0x14EEA6040 = trampoline sub_eea6040 (`jmp rax`); store scan of .text = 0 hits; never rewritten by static code.

## This session — new evidence: name the indirect caller, decode it, resolve rax at the jmp

mc_root_4e05e50_callers.txt [V live]: capture at entry rva=0x4E05E50, 150 hits / 32 samples. Every sample: `CALLER ret=0x1289496` (line 3) — sub_4e05e50 is entered ONLY via sub_12893d0's indirect call site. RCX (this) at entry = live texture-job object pointers (0x3908FFDExxx); line 4 (RCX=3908FFDE900) dump contains the ASCII string "tex\0" (bytes 74 65 78 00) — the object carries a texture name. RDX/R8/R9 are context pointers varying per sample.

l8b_texcreate_record.txt [V live]: capture at rva=0xE81BF30, ret=0xE814560 (line 3) — inside createTexture right after TextureD3D12::create; R8 texture-name strings confirm real records flow into the D3D12 backend record table (already proven r24). Cited, not redone.

| offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| sub_12893d0 entry | 1 | - | `0x12893d0  push rbp` | sub_12893d0 [0x12893d0..0x12895d3): deferred texture-job runner; stride-0x18 entry array, per entry refcount `lock cmpxchg [rcx+8]` (0x1289444), object at entry+0x10; 13 static xrefs in from sub_1145c20 x2, sub_6622610 x1, sub_66232b0 x8, sub_6632bf0 x2 | [V] |
| obj+0x0 | 8 | [rcx+0x0] | `0x1289486  mov rax,[rcx]` | rax = job object vptr; RCX = this = texture-job object pointer | [V] |
| obj+0x8 | 8 | [rax+0x8] | `0x1289489  mov rax,[rax+8]` | rax = obj->vptr[1] = the indirect callee | [V] |
| slot [0xF99FFA0] | 8 | [0xF99FFA0] | `0x1289490  call qword ptr [0xF99FFA0]` | indirect tail-call through the trampoline slot; pushed ret = 0x1289496 | [V] |
| ret site 0x1289496 | 1 | - | `0x1289496  nop` | instruction right after the indirect call; matches capture `CALLER ret=0x1289496` in all 32 samples | [V live] |
| trampoline 0xEEA6040 | 2 | - | `0xEEA6040  jmp rax` | trampoline: tail-calls rax; rax at the jmp = obj->vptr[1] = sub_4e05e50 entry 0x4E05E50 at runtime | [V] + [V live] |
| sub_4e05e50 entry | 1 | - | `0x4E05E50  push rbp` | sub_4e05e50 real prologue (capture target rva=0x4E05E50); RCX = this = texture-job object [V live line 4] | [V] |
| this+0x18 | 8 | [rcx+0x18] | `0x4E05E71  mov rax,[rcx+0x18]` | sub_4e05e50 reads this+0x18 (nested object pointer) | [V] |
| this+0x10 refcount | 8 | [rdx+0x8] | `0x4E05EA8  lock cmpxchg [rdx+8],r8d` | refcount increment on the this+0x10 pointee | [V] |
| this+0x58 | 4 | - | `0x4E05F68  add rdi,0x58` | rdi = this+0x58 (rdi = rcx set at 0x4E05E6E `mov rdi,rcx`) | [V] |
| call sub_bc41420 | 8 | - | `0x4E05F77  call 0xBC41420` | sub_4e05e50 -> sub_bc41420 with rcx = this+0x58 -> ... -> createTexture chain | [V] |
| after call 0xBC41420 | 1 | - | `0x4E05F7C  nop` | site immediately after the call | [V] |
| handle return | 8 | - | `0xC296E1A  call 0xBC74120` | returns the 16-bit bgfx handle in ax | [V] |
| texture_obj+0x0 | 2 | [rdi+0x0] | `0xC296E26  mov [rdi],ax` | 16-bit handle stored at this+0x58+0x00 (texture_obj = this+0x58); size 2 (ax) | [V] |
| texture_obj+0x8 | 16 | [rdi+0x8] | `0xC296E32  movups [rdi+8],xmm0` | texture object descriptor field +0x8 written from r12 | [V] |
| texture_obj+0x18 | 8 | [rdi+0x18] | `0xC296E3B  mov [rdi+0x18],rdx` | texture object field +0x18 written from [r12+0x10] | [V] |
| desc src [r12] | 16 | [r12] | `0xC296E2D  movups xmm0,[r12]` | descriptor source read (source offset not decoded) | [V] |
| dispatcher slot load | 8 | [rax+0xD0] | `0xBC6A2B1  mov rax,[rax+0xD0]` | bgfx dispatcher: RendererContext vtable slot 26 = 0xe8143c0 = createTexture [V BGFX_MAP] | [V] |
| dispatcher call | 8 | [0xF99FFA0] | `0xBC6A2C2  call qword ptr [0xF99FFA0]` | bgfx dispatcher issues createTexture via the same trampoline slot | [V] |
| [0xF99FFA0] data | 8 | - | - | PE .rdata initializer = 0x14EEA6040 = sub_eea6040; read-only section, store scan 0 hits, never rewritten | [V] |
| vtable scan 0x14004E05E50 | 8 | - | - | scan of all PE sections for qword 0x14004E05E50 (absolute addr of sub_4e05e50), absolute and RVA forms: 0 hits — no static vtable has slot 1 = sub_4e05e50; vptr[1] bind is runtime-patched only | [V] |

## Connection to texgroup_load / texload / TexturePtr

- Job runner placement: sub_6632bf0 ("Deferred Texture Transactions", string at 0x6632c19) is the deferred-texture-transactions flush; its dossier (docs/functions/6632bf0.md, tool-generated from the disassembly) shows it calls sub_12893d0 x2 and runs `job->vtbl[1]()` per texture job, then the destroying destructor `job->vtbl[0](1)`. sub_6632bf0 is called from BgfxFrameBuilder::endFrame (0x66232b0; frame-start and frame-end call sites) [V dossier + V rdis callers: sub_6632bf0 -> sub_12893d0 x2]. So the MC texture jobs enqueued by the texload path execute here, with vptr[1] = sub_4e05e50 at runtime [V live] — this is where sub_4e05e50 issues createTexture (cmd 0x0E via sub_bc73770 -> dispatcher -> slot 26).
- texgroup_load(0x5421c90) -> texload(0x58a1310) -> texload_task(0x541bf00) -> undecoded 0x18718D0 at 0x54227af [r24]: enqueues the texture jobs; static callees of texgroup_load do not enter the sub_4e05e50 tree [r24/r37].
- TexturePtr [V file read]: src/sdk/mc/deps/minecraft_renderer/renderer/TexturePtr.h — `mce::TexturePtr { shared_ptr<void> mClientTexture +0x00 (16B), shared_ptr<void> mResourceLocationPtr +0x10 (16B) }`, `static_assert(sizeof(TexturePtr) == 32)`. The returned handle lands at object+0x58 (`0x4E05F68 add rdi,0x58` then `0xC296E26 mov [rdi],ax`, size 2) [V]; r24 labels object base TexturePtr* with texture_obj = TexturePtr+0x58 [I]. The exact mce::TexturePtr member that holds the 16-bit bgfx handle is not byte-pinned in the exe beyond the store site itself [?].

## What was tried that failed (new angles, negative results)

- vtable/data reference scan for sub_4e05e50's entry: qword 0x14004E05E50 (absolute) and 0x004E05E50 (RVA form) — 0 hits in all PE sections. No static vtable or data refers to sub_4e05e50; the vptr[1] = sub_4e05e50 bind exists only at runtime (observed live [V live]).
- [0xF99FFA0] writer search [r22/r37, re-confirmed]: .text store scan for the slot = 0 hits; .rdata read-only; no code writer exists. The runtime value is produced by vptr[1] loading, not by storing to the slot.
- sub_4e05e50 static callers: 0 (`rdis callers`); reached only via sub_12893d0's indirect vtbl[1] tail-call.

## CLOSES?

NO — blocking fact: no [V]-proven static path texgroup_load(0x5421c90) -> sub_4e05e50. sub_4e05e50 (entry 0x4E05E50) has 0 static xrefs and no static vtable/data reference (section scan 0 hits); it is reached only as vtable[1] of deferred texture jobs, run by sub_12893d0 (called from sub_6632bf0 / BgfxFrameBuilder::endFrame 0x66232b0) through the trampoline [0xF99FFA0] = sub_eea6040 `jmp rax`, tail-calling rax = obj->vptr[1] = sub_4e05e50 at runtime. The bind is runtime-only, observed live [V live] (32/32 capture samples ret=0x1289496), and cannot be closed by static analysis of the exe.

Everything else in L7e is [V] or [V live]: sampler flag decode + cache (6ax), D3D12 backend texture-management chain, createTexture issuance (cmd 0x0E producer sub_bc73770 -> dispatcher slot 26 -> createTexture 0xe8143c0 -> TextureD3D12::create -> handle store at object+0x58), TexturePtr.h layout, deferred-texture-job flush sub_6632bf0/BgfxFrameBuilder::endFrame. Atlas stitchers (L8a/L8b) remain separate open items.

## TOOL REQUESTS

- None. No helper scripts written; the sub_4e05e50 vtable reference scan was a throwaway one-liner (not saved). No temporary files left behind.
