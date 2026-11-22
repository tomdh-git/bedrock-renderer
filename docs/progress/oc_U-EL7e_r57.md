## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): `- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending | PROGRESS 2026-11-21 oc_U-EL7e.md (verify_oc 185/185): D3D12 backend texture-management chain decoded [V] ...; Minecraft-side pack->GPU chain (texgroup_load 0x5421c90 -> texload 0x58a1310 -> texload_task 0x541bf00 -> undecoded 0x18718D0 at 0x54227af) and atlas stitchers still open (L8a/L8b)`

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; live capture logs under docs/data/live are read-only orchestrator outputs, cited as [V live] with file.

Tags: [V] saw in disassembly (RVA cited, verbatim `0xRVA  instr` quoted from a fresh rdis dis this session) / [V live] saw in an orchestrator live-capture reg dump (file cited) / [I] inferred from structure or BGFX_MAP.md / '-' = no instruction or string shows a meaning. Row rule: one annotated row per distinct offset, all its read/store sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after the address, copied verbatim from rdis) | meaning ONLY if an instruction/string shows it else '-' | tag. Sizes from the instruction (movups/movaps/movdqu/movdqa 16, qword 8, dword/movss 4, word 2, byte 1; direct call 5, indirect call qword ptr [mem] 8). No input data pasted as-is; no raw instruction dumps outside tables; no ellipsis or catch-all rows.

## Already proven (cited from r1-r55; not re-decoded, not re-quoted here)

- Half 1 — sampler flag decode + sampler cache (6ax): [V] docs/functions/e820500.md decodes 0xe820500 instruction-complete; src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h carries the static_asserts; called from blit 0xe818bc0 and executor 0xe821120.
- Half 2a — D3D12 backend texture-management chain: [V] texture record table at this+0xBDE178 stride 0xB8 (BGFX_MAP.md 6z/6z-2/6aj/1524 confirm base/stride); createTexture 0xe8143c0 = renderer-context vtable slot 26 (BGFX_MAP.md line 403); updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0, blitSetup 0xe819750; createTexture 0xe8143c0 -> TextureD3D12::create 0xe81bf30.
- texgroup_load(0x5421c90) static chain ends at `0x54227AF call 0x18718D0` (sub_18718d0 texture-cache lookup/release, vtable 0xEFCA680, vptr[0] destructor dispatch only); texload 0x58a1310 and texload_task 0x541bf00 have 0 static callers; the item-line texgroup_load->texload->texload_task->0x18718D0 chain is NOT statically supported. 0x18718d0 decoded [V r44] and never reaches sub_4e05e50.

## Pending item attacked this session (r37): rax held at the trampoline jmp (0xEEA6040 `jmp rax`)

Static work on [0xF99FFA0] is exhausted: it is a read-only .rdata PE initializer = sub_eea6040 (0x14EEA6040 = ImageBase 0x140000000 + 0xEEA6040); .text store scan for [0xF99FFA0] = 0 hits (no code writer, never rewritten). The trampoline just tail-calls rax, so the real target is whatever rax holds at the call site. Resolved statically below: sub_12893d0 loads job-object vptr[1] into rax, and job vtable 0xF215838 slot +0x008 is sub_4e05e50, so rax at the mc_root trampoline jmp = sub_4e05e50 [V]. Confirmed live: all 32 mc_root_4e05e50_callers samples enter sub_4e05e50 via ret site 0x1289496 [V live]. A live capture at 0xEEA6040 entry to read RAX is therefore unnecessary.

### Table 1 — CFG trampoline [0xF99FFA0] and the rax-at-jmp target

| offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| 0xEEA6040 | 2 | - | `0xEEA6040  jmp rax` | sub_eea6040 CFG-trampoline body: tail-call to whatever rax holds | [V] |
| [0xF99FFA0] | 8 | [0xF99FFA0] | `0x1289490  call qword ptr [0xF99FFA0]` / `0xBC6A2C2  call qword ptr [0xF99FFA0]` | trampoline tail-call at the mc_root dispatch and the bgfx dispatcher; rdis resolves `[data_f99ffa0] = sub_eea6040` at both sites; cell is a read-only .rdata PE initializer (0x14EEA6040), .text store scan = 0 hits -> no code writer | [V] |
| vtable 0xF215838 +0x008 | 8 | - | - | `rdis vt 0xF215838`: slot +0x008 = sub_4e05e50 size 0x224 push rbp -> job-object vptr[1] is statically sub_4e05e50, i.e. the rax held at the mc_root trampoline jmp | [V] |
| 0x4E060BB | 8 | - | `0x4E060BB  lea rax,[0xF215838]` | sub_4e060b0 loads the job vtable address (only static vptr=0xF215838 writer) | [V] |
| 0x4E060C2 | 8 | W: [rcx] | `0x4E060C2  mov [rcx],rax` | sub_4e060b0 writes job-object vptr = 0xF215838 into the job object +0x00 | [V] |
| 0x1289486 | 8 | R: [rcx] | `0x1289486  mov rax,[rcx]` | sub_12893d0: rax = job-object vptr (from entry+0x10) | [V] |
| 0x1289489 | 8 | R: [rax+8] | `0x1289489  mov rax,[rax+8]` | rax = job object->vptr[1] = the real indirect-call target | [V] |
| 0x1289490 | 8 | R: [0xF99FFA0] | `0x1289490  call qword ptr [0xF99FFA0]` | sub_12893d0 tail-calls vptr[1] through the trampoline; ret site = 0x1289496 | [V] |
| 0x1289496 | 1 | - | `0x1289496  nop` | instruction right after the indirect call = capture CALLER ret=0x1289496 in all 32 mc_root samples | [V] [V live] |

### Table 2 — sub_4e05e50 root (MC-side pack->GPU root) and issuance into the dragon layer

| offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| 0x4E05E50 | 1 | - | `0x4E05E50  push rbp` | sub_4e05e50 entry: MC-side pack->GPU root; `xref.py callers 0x4E05E50` -> EMPTY (0 static callers); entered only at runtime via sub_12893d0's vptr[1] trampoline tail-call | [V] |
| 0x4E05F61 | 8 | R: [rdi+0xE0] | `0x4E05F61  mov r9,[rdi+0xE0]` | sub_4e05e50 reads the renderer context from its argument object +0xE0 | [V] |
| 0x4E05F68 | 4 | - | `0x4E05F68  add rdi,0x58` | texture object = sub_4e05e50 argument + 0x58 | [V] |
| 0x4E05F77 | 5 | - | `0x4E05F77  call 0xBC41420` | sub_4e05e50 -> sub_bc41420 (rcx = texture object); ret site 0x4E05F7C | [V] [V live] |
| 0x4E05F7C | 1 | - | `0x4E05F7C  nop` | ret site after `call 0xBC41420` = dragon_texture_caller_bc41420 capture CALLER ret=0x4E05F7C | [V live] |
| 0xBC41B39 | 5 | - | `0xBC41B39  call 0xC296B50` | sub_bc41420 -> dragon entry 0xc296b50; ret site 0xBC41B3E | [V] [V live] |
| 0xC296D79 | 5 | - | `0xC296D79  call 0xBC73BF0` | dragon entry 0xc296b50 -> thin bgfx createTexture wrapper; ret site 0xC296D7E nop; fallthrough `0xC296D7F jmp 0xC296E26` to the handle store | [V] [V live] |
| 0xBC73EA8 | 5 | - | `0xBC73EA8  call 0xBC73770` | wrapper -> command-byte-0x0E producer; u16 handle read back `0xBC73EAD movzx eax,word ptr [rsp+0x32]` | [V] [V live] |

### Table 3 — command-byte-0x0E production, dispatcher slot-26 -> createTexture, handle store into TexturePtr/ClientTexture

| offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| 0xBC73770 | - | E: | `0xBC73770  push rbp` | sub_bc73770 entry = command-byte-0x0E producer (3 static xrefs, all dragon-layer wrappers) | [V] |
| [rdi+0x1CFD0C8] | 8 | R: | `0xBC73AA3  mov rbx,[rdi+0x1CFD0C8]` | command-buffer state object (BGFX_MAP.md 6ai) | [V] |
| [rbp+0x2C] | 1 | W: | `0xBC73AAA  mov byte ptr [rbp+0x2C],0xE` / R: `0xBC73ABF  lea rdx,[rbp+0x2C]` / `0xBC73AC9  call 0xEBCE390` | byte 14 = createTexture staged, then 1 byte written into the command buffer | [V] |
| [rbp+0x2E] | 2 | W: | `0xBC73AEB  lea rdx,[rbp+0x2E]` / `0xBC73AF5  call 0xEBCE390` | handle index staged, then 2 bytes written into the command buffer right after the cmd byte | [V] |
| [rbx+0xDC5818] | 4 | R/W: | `0xBC73AAE  mov eax,[rbx+0xDC5818]` / `0xBC73AE2  mov [rbx+0xDC5818],ecx` | ring write index, bumped by 2 after the handle | [V] |
| [rsi] | 2 | W: | `0xBC73B70  movzx edi,word ptr [rbp+0x2E]` / `0xBC73B74  mov [rsi],di` | 16-bit handle returned to the createTexture API caller | [V] |
| 0xBC6A28F | 8 | R: [rdi+0x1EBF2D0] | `0xBC6A28F  mov rcx,[rdi+0x1EBF2D0]` | bgfx dispatcher: rcx = renderer-context-like object | [V] |
| 0xBC6A2AE | 8 | R: [rcx+0x0] | `0xBC6A2AE  mov rax,[rcx]` | rax = renderer-context vptr | [V] |
| 0xBC6A2B1 | 8 | R: [rax+0xD0] | `0xBC6A2B1  mov rax,[rax+0xD0]` | rax = vptr[slot 26] = createTexture 0xe8143c0 (BGFX_MAP.md line 403) | [V] |
| 0xBC6A2C2 | 8 | R: [0xF99FFA0] | `0xBC6A2C2  call qword ptr [0xF99FFA0]` | createTexture issued via CFG trampoline; ret site 0xBC6A2C8 = capture CALLER ret=0xBC6A2C8 | [V] [V live] |
| 0xBC6A2C8 | 3 | - | `0xBC6A2C8  test rax,rax` | returned handle tested | [V] |
| 0xE8143C0 | - | E: | `0xE8143C0  push rbp` | createTexture entry (renderer-context vtable slot 26) | [V] |
| this+0xBDE178 | 8 | R: | `0xE8143F3  lea r12,[rcx+0xBDE178]` | texture record table base = renderer ctx + 0xBDE178 | [V] |
| 0xE814427 | 5 | - | `0xE814427  imul r8,rbx,0xB8` | record stride 0xB8 per record index | [V] |
| 0xE81455B | 5 | - | `0xE81455B  call 0xE81BF30` | createTexture -> TextureD3D12::create (backend record fill) | [V] |
| 0xE814560 | 1 | - | `0xE814560  nop` | ret site after `call 0xE81BF30` = l8b_texcreate_record capture CALLER ret=0xE814560 | [V] [V live] |
| 0xC296E1A | 5 | - | `0xC296E1A  call 0xBC74120` | ax = returned 16-bit bgfx texture handle | [V] |
| [texture object+0x00] | 2 | W: [rdi+0x0] | `0xC296E22  mov ax,0xFFFF` / `0xC296E26  mov [rdi],ax` | invalid-handle fallback (ax=0xFFFF); 16-bit handle stored at texture object +0x00 (texture object = arg+0x58) | [V] |
| [texture object+0x08] | 16 | R/W: | `0xC296E2D  movups xmm0,[r12]` / `0xC296E32  movups [rdi+8],xmm0` | 0x1C-byte create descriptor block copied to texture object +0x08 | [V] |
| [texture object+0x18] | 8 | W: [rdi+0x18] | `0xC296E3B  mov [rdi+0x18],rdx` | descriptor pointer stored at texture object +0x18 | [V] |
| 0x54227AF | 5 | - | `0x54227AF  call 0x18718D0` | texgroup_load/texload_task static chain end: sub_18718d0 texture-cache lookup/release (vtable 0xEFCA680, vptr[0] only) — never reaches sub_4e05e50 | [V] |

Handle trace into TexturePtr/ClientTexture [V live + V file read]: sub_4e05e50's RCX argument is a TexturePtr-carrying MC object (mc_root live dumps carry texture-descriptor data and name strings 'tex', 'legs', 'spear'); texture object = arg + 0x58 (`0x4E05F68 add rdi,0x58`); returned u16 bgfx handle stored at [texture object+0x00] (`0xC296E26 mov [rdi],ax`); create descriptor copied to +0x08 (`0xC296E2D movups xmm0,[r12]` / `0xC296E32 movups [rdi+8],xmm0`, size 16), descriptor pointer at +0x18 (`0xC296E3B mov [rdi+0x18],rdx`); sdk TexturePtr.h (sizeof 32, mClientTexture+0x00, mResourceLocationPtr+0x10 [V file read]) / ClientTexture.h (empty marker struct) [V file read].

## Orchestrator hint results (step 1 producer + step 2 handle trace; slot-4 angle)

1. Producer of bgfx command byte 0x0E: sub_bc73770 [V Table 1]; reached only from dragon-layer wrappers 0xbc73bf0/0xbc73ed0/0xbc74120 called from dragon entries 0xc296b50/0xc297000/0xc2a3d90/0xbc63c80 (`xref.py callers 0xBC73BF0` -> dragon entries only [V]); MC texture code calls none statically. NOT called from any texture-object init.
2. Returned handle traced into TexturePtr/ClientTexture: handle stored at texture object+0x00 [V Table 3], texture object = arg+0x58 [V], arg = TexturePtr-carrying object [V live + V file read].
3. Texture-object init vtable 0xEFCA580 slot 4 angle: NEGATIVE — slot 4 = sub_a3f10 (and written vptr 0xEFCA5A0 -> sub_a34a0); neither calls 0xbc73bf0/0xbc73ed0/0xbc74120/0xbc73770/0xe8143c0 (full-range scan) [V]; `xref.py callers 0xBC73BF0` -> dragon entries only [V]. Reported with xref/dis evidence; angle stopped.

## Static angles exhausted (what I tried that failed, not redone)

- `rdis imm 0xF215838`: 0 hits — no code materializes the job vtable address / no inline job-construction site [V].
- `xref.py callers 0x4E060B0`: EMPTY — the job vptr writer (sub_4e060b0, `0x4E060BB lea rax,[0xF215838]` / `0x4E060C2 mov [rcx],rax`) has no static caller [V].
- livemem read of the deferred transaction / job queue: not applicable — no statically-known anchor (sub_6632bf0's `this`/vector base not located); livemem is a last resort requiring a specific rdis-found address.
- Not redone (exhausted r1-r51): xref callers 0xe8143c0/0x4E05E50/0x12893d0 all EMPTY or dead-end; texload 0x58a1310/texload_task 0x541bf00 0 static callers and not on the proven path; [0xF99FFA0] writer search — read-only cell, 0 stores.

## CLOSES?

NO — single blocking fact: no [V]-proven static path texgroup_load(0x5421c90) -> sub_4e05e50 exists and provably cannot be built from static evidence: sub_4e05e50 (0x4E05E50..0x4E06074) has 0 static callers (`xref.py callers 0x4E05E50` -> EMPTY [V]) and is entered only at runtime via sub_12893d0's job-vtable[1] trampoline tail-call `0x1289490 call qword ptr [0xF99FFA0]` (ret site 0x1289496, all 32 mc_root live samples [V live]). The rax target held at the trampoline jmp IS resolved (job vtable 0xF215838[1] = sub_4e05e50 [V vt output]), but the texgroup_load -> sub_4e05e50 enqueue/bind is runtime-only (sub_4e060b0 vptr writer has 0 static callers; imm 0xF215838 = 0 hits; no statically-known job-queue anchor for livemem). Everything else in L7e IS [V]-proven: Half 1 sampler flag decode + cache (6ax); Half 2a D3D12 backend texture-management chain; createTexture issuance end-to-end below sub_4e05e50; returned u16 handle stored at texture object+0x00 (= TexturePtr+0x58); sdk TexturePtr/ClientTexture headers. Atlas stitchers (L8a/L8b) remain separate open units (oc_U-EL8a/oc_U-EL8b), MIRROR_SKIP, not this unit.

## Verification

- `python tools/sigs/verify_oc.py docs/progress/oc_U-EL7e.md` — mismatch=0, no-such-instr=0 required (every quoted `0xRVA  instr` line matched against a fresh rdis dis of the 1.26.62.01 exe this session).
- `python tools/delegate.py check docs/progress/oc_U-EL7e.md` — must exit 0; only then is line 2 after `## NEXT` set to DONE.

## TOOL REQUESTS

- None. No helper scripts written; no temporary files left behind in the repo.
