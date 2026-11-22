## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): `- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending | PROGRESS 2026-11-21 oc_U-EL7e.md (verify_oc 185/185): D3D12 backend texture-management chain decoded [V] (texture record table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0, updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0 / blitSetup 0xe819750); Minecraft-side pack->GPU chain (texgroup_load 0x5421c90 -> texload 0x58a1310 -> texload_task 0x541bf00 -> undecoded 0x18718D0 at 0x54227af) and atlas stitchers still open (L8a/L8b)`

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; live capture logs under docs/data/live are read-only inputs produced by the orchestrator.

Tags: [V] saw in disassembly (RVA cited, verbatim line quoted) / [V live] saw in an orchestrator live capture log (file cited) / [I] inferred from structure or BGFX_MAP / [?] unknown or not located.

Row rule: one annotated row per distinct offset, all its read/store sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after the address, copied verbatim from rdis) | meaning ONLY if an instruction/string shows it else '-' | tag. Sizes from the instruction (movups/movaps/movdqu/movdqa 16, qword 8, dword/movss 4, word 2, byte 1). No input data pasted as-is; no skipped offsets among quoted sites; no raw instruction dumps outside tables; no ellipsis or catch-all rows.

## Already proven (cited from r1-r37; not re-quoted, not redone)

- Half 1 — sampler flag decode + sampler cache (6ax): [V] docs/functions/e820500.md decodes 0xe820500 instruction-complete; src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h carries the static_asserts; called from blit 0xe818bc0 and executor 0xe821120.
- Half 2a — D3D12 backend texture-management chain: [V] record table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0, updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0, blitSetup 0xe819750; BGFX_MAP 6z/6z-2/6aj confirm table base/stride and live texture records.
- createTexture issuance chain from MC code [V live + dis r24]: sub_4e05e50 -> sub_bc41420 -> 0xc296b50 -> wrapper 0xbc73bf0 -> producer 0xbc73770 (command-byte-0x0E) -> bgfx dispatcher (vptr[slot 26] = 0xe8143c0 per BGFX_MAP) -> createTexture 0xe8143c0 -> TextureD3D12::create 0xE81BF30 (ret 0xe814560 [V live]); returned handle stored at texture_obj+0x00 [V]; texture_obj = TexturePtr+0x58 [V]; sdk TexturePtr/ClientTexture [V file read].
- [0xF99FFA0] = read-only .rdata initializer = trampoline sub_eea6040 `jmp rax` (0x14EEA6040 = ImageBase 0x140000000 + 0xEEA6040), no code writer [V]; indirect-call rax holds the real target (vptr[1] or vptr[26]) [V] / [V live].

All of the above is cited, not re-decoded this session; no instruction line from it is re-quoted here.

## This session — pending part: MC-side root sub_4e05e50 and the [0xF99FFA0] trampoline bind

New field-map rows (one row per distinct offset; all sites listed; every quoted line re-verified verbatim against a fresh rdis dis this session):

| offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| [rcx+0x0] | 8 | [rcx+0x0] | `0x1289486  mov rax,[rcx]` | rax = object vptr; sub_12893d0 walks an entry list ([rcx]->[rcx+8], stride 0x18) and calls vptr[1] of [r13+0x10] per entry | [V] |
| [rax+0x8] | 8 | [rax+0x8] | `0x1289489  mov rax,[rax+8]` | rax = obj->vptr[1]; at runtime vptr[1] = sub_4e05e50 — every sub_4e05e50 entry enters via this call (capture ret=0x1289496 below) | [V] [V live] |
| [0xF99FFA0] | 8 | [0xF99FFA0] | `0x1289490  call qword ptr [0xF99FFA0]`<br>`0xBC6A2C2  call qword ptr [0xF99FFA0]` | trampoline tail-call ([data_f99ffa0] = sub_eea6040): sub_12893d0 tail-calls vptr[1]=sub_4e05e50 at 0x1289490 (ret 0x1289496); dispatcher tail-calls vptr[26]=createTexture at 0xBC6A2C2 (ret 0xBC6A2C8) | [V] [V live] |
| 0x1289496 | 1 | - | `0x1289496  nop` | instruction right after the indirect call; matches capture ret=0x1289496 in all 32 samples (_status.txt: hits=150 samples=32) | [V live] |
| 0xEEA6040 | 8 | - | `0xEEA6040  jmp rax` | trampoline body: tail-call rax (real callee held in rax: vptr[1] at 0x1289489, or dispatcher vptr[26] at 0xBC6A2B1) | [V] |
| 0xF99FFA0 | 8 | [0xF99FFA0] | - | PE .rdata read-only initializer (section flags 0x40000040) = 0x14EEA6040 = ImageBase 0x140000000 + sub_eea6040 RVA 0xEEA6040; .text store scan for [0xF99FFA0] = 0 hits -> no code writer, never rewritten | [V] |
| TexturePtr+0x58 | 8 | - | `0x4E05F68  add rdi,0x58` | texture_obj = sub_4e05e50 arg (RCX) + 0x58; sdk TexturePtr.h = 32B (mClientTexture + mResourceLocationPtr shared_ptrs) [V src/sdk/mc/deps/minecraft_renderer/renderer/TexturePtr.h] | [V] |
| 0x4E05F77 | - | - | `0x4E05F77  call 0xBC41420` | sub_4e05e50 -> sub_bc41420 (RCX = texture_obj) | [V] |
| 0x4E05F7C | 1 | - | `0x4E05F7C  nop` | ret site after call 0xBC41420; dragon_texture_caller_bc41420.txt:3 CALLER ret=0x4E05F7C | [V live] |
| 0xC296E1A | - | - | `0xC296E1A  call 0xBC74120` | ax = returned bgfx texture handle | [V] |
| [rdi+0x0] | 2 | [rdi+0x0] | `0xC296E26  mov [rdi],ax` | handle store at texture_obj+0x00 | [V] |
| [rax+0xD0] | 8 | [rax+0xD0] | `0xBC6A2B1  mov rax,[rax+0xD0]` | rax = renderer-context vptr[slot 26] = createTexture 0xe8143c0 (BGFX_MAP) | [V] [I docs/BGFX_MAP.md slot 26] |
| 0xBC6A2C8 | 4 | - | `0xBC6A2C8  test rax,rax` | ret site after dispatcher call; matches capture ret=0xBC6A2C8; R8 = 0x1C create descriptor with 'TEX' tag (R8+0x10 "TEX\0") | [V live] |
| 0xE81455B | - | - | `0xE81455B  call 0xE81BF30` | createTexture -> TextureD3D12::create | [V] |
| 0xE814560 | 1 | - | `0xE814560  nop` | ret site; matches capture ret=0xE814560; RDX/R9 = descriptor block, R8 = UTF-16 texture name ('Texture: 2815') | [V live] |

### sub_12893d0 (function containing ret site 0x1289496) [V]
`rdis dis 0x12893d0 120`: sub_12893d0 [0x12893d0..0x128b3d0) size 0x2000, 13 xrefs in [V rdis]. Prologue saves rbx..rdi, rsi=rdx, rdi=rcx, then walks entries r13=[rcx] .. r14=[rcx+8] stride 0x18: each entry [r13+8] is a refcount (lock cmpxchg [rcx+8] at 0x1289447), [r13] an object ptr, [r13+0x10] the target object whose vptr[1] is tail-called through [0xF99FFA0] at 0x1289490 (ret 0x1289496); release path lock-decs [r15+8]/[r15+0xC] and calls vptr[0]/vptr[8]. It is a refcounted texture-list processor that issues one createTexture per live texture. Its 4 static callers are 0x1145c20, 0x6622610, 0x66232b0, 0x6632bf0 [V python tools/sigs/xref.py callers 0x12893d0]; none is texgroup_load(0x5421c90)/texload(0x58a1310)/texload_task(0x541bf00), and their chains dead-end [V r24].

### [0xF99FFA0] trampoline [V]
sub_eea6040 = `0xEEA6040  jmp rax` (verified this session); [0xF99FFA0] = 0x14EEA6040 PE .rdata initializer, read-only section, no code writer (0 .text store hits). Both call sites above (0x1289490 in sub_12893d0, 0xBC6A2C2 in the dispatcher) tail-call through it: the real callee is whatever rax holds — vptr[1] = sub_4e05e50 for the MC root, vptr[26] = createTexture for the dispatcher — both observed live [V live].

### MC-side root observed live [V live]
mc_root_4e05e50_callers.txt: capture at 0x4E05E50, hits=150 samples=32 (_status.txt:2-3); every sample has CALLER ret=0x1289496 (line 3) — i.e. sub_4e05e50 is entered only through sub_12893d0's vptr[1] tail-call at runtime. RCX = sub_4e05e50's first arg = TexturePtr* (sdk TexturePtr.h: 32B, two shared_ptrs [V file read]); RCX dumps carry texture descriptor data incl. name strings ('tex' line 4, '.legs' line 8) [V live].
dragon_texture_caller_bc41420.txt:3-4: sub_bc41420 entered with CALLER ret=0x4E05F7C; RCX = 0x1C create descriptor (size field 0x1C, name 'tex' at +0x18 "74657800") [V live].
drago
