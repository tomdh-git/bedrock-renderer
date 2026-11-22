## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): `- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending | PROGRESS 2026-11-21 oc_U-EL7e.md (verify_oc 185/185): D3D12 backend texture-management chain decoded [V] ...; Minecraft-side pack->GPU chain (texgroup_load 0x5421c90 -> texload 0x58a1310 -> texload_task 0x541bf00 -> undecoded 0x18718D0 at 0x54227af) and atlas stitchers still open (L8a/L8b)`

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; live capture logs under docs/data/live are read-only inputs produced by the orchestrator.

Tags: [V] saw in disassembly (RVA cited, verbatim line quoted) / [V live] saw in an orchestrator live capture log (file cited) / [I] inferred from structure or BGFX_MAP / [?] unknown or not located.

Row rule: one annotated row per distinct offset, all its read/store sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after the address, copied verbatim from rdis) | meaning ONLY if an instruction/string shows it else '-' | tag. Sizes from the instruction (movups/movaps/movdqu/movdqa 16, qword 8, dword/movss 4, word 2, byte 1). No input data pasted as-is; no skipped offsets among quoted sites; no raw instruction dumps outside tables; no ellipsis or catch-all rows.

## Already proven (cited from r1-r37; not re-quoted, not redone)

- Half 1 — sampler flag decode + sampler cache (6ax): [V] docs/functions/e820500.md decodes 0xe820500 instruction-complete; src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h carries the static_asserts; called from blit 0xe818bc0 and executor 0xe821120.
- Half 2a — D3D12 backend texture-management chain: [V] record table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0, updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0, blitSetup 0xe819750; BGFX_MAP 6z/6z-2/6aj confirm table base/stride and live texture records.
- createTexture issuance mechanism [V live + dis]: command-byte-14 producer sub_bc73770 writes `0xBC73AAA  mov byte ptr [rbp+0x2C],0xE` [V r4]; reached only via thin wrappers 0xbc73bf0/0xbc73ed0/0xbc74120 from dragon entries 0xc296b50/0xc297000/0xc2a3d90/0xbc63c80 [V r4 xref]; MC texture code calls none statically. bgfx dispatcher default path `0xBC6A2B1  mov rax,[rax+0xD0]` slot 26 = 0xe8143c0 [V BGFX_MAP] -> `0xBC6A2C2  call qword ptr [0xF99FFA0]` -> createTexture 0xe8143c0. Live capture docs/data/live/createtexture_callers.txt: ONE caller, ret=0xBC6A2C8 (call site just before it; R8 = 0x1C-byte create descriptor, "TEX" tag at +0x18) [V live]. Live capture docs/data/live/l8b_texcreate_record.txt (0xE81BF30 = TextureD3D12::create): caller ret=0xE814560, RCX = texture object (size dword 0x1C at +0x08) [V live]. Returned handle: `0xC296E1A  call 0xBC74120` (ax) -> `0xC296E26  mov [rdi],ax` (size 2) at texture_obj+0x00 [V r24]; texture sub-object at object+0x58 via `0x4E05F68  add rdi,0x58` [V]; sdk TexturePtr/ClientTexture [V file read: sizeof(TexturePtr)==32, static_assert, mClientTexture+0x00 / mResourceLocationPtr+0x10, ClientTexture empty, sizeof(BedrockTexture)==48].
- MC-side issuance [V live]: sub_4e05e50 (`0x4E05F77  call 0xBC41420`, return site `0x4E05F7C  nop`, capture ret=0x4E05F7C [V live docs/data/live/dragon_texture_caller_bc41420.txt]) -> sub_bc41420 -> dragon entry 0xc296b50 -> wrapper 0xbc73bf0 -> producer 0xbc73770 -> dispatcher -> createTexture 0xe8143c0. sub_4e05e50 takes the polymorphic texture object in RCX (constant vptr 0x7FF6A8215838 = base + 0xF215838 across 32 capture samples; vtable 0xF215838 slot 1 = sub_4e05e50 [V]), NOT a TexturePtr* (sizeof(TexturePtr)==32 [V file read]).

## This session — verbatim verification (new rows, all re-disassembled this session)

| offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| 0xEEA6040 | 2 | - | `0xEEA6040  jmp rax` | trampoline: tail-call rax; absolute target 0x14EEA6040 = ImageBase 0x140000000 + 0xEEA6040 | [V] |
| 0xF99FFA0 | 8 | [0xF99FFA0] R | - | PE .rdata read-only initializer = 0x14EEA6040 (trampoline sub_eea6040); .text store scan for mov [rip+disp32] reg / mov [rip+disp32] imm32 targeting 0xF99FFA0 = 0 hits; section flags 0x40000040 read-only, so never rewritten and no code writer exists | [V] |
| 0x1289486 | 8 | [rcx] R | `0x1289486  mov rax,[rcx]` | rax = object vptr (sub_12893d0 job-runner tail-call sequence; sub_12893d0 runs deferred texture jobs via job->vtbl[1], BGFX_MAP 6dv/6ew) | [V] |
| 0x1289489 | 8 | [rax+8] R | `0x1289489  mov rax,[rax+8]` | rax = obj->vptr[1]; vtable 0xF215838 slot 1 = sub_4e05e50 [V], so at runtime rax = sub_4e05e50 (live vptr 0x7FF6A8215838 in all 32 samples) | [V] + [V live] |
| 0x1289490 | 8 | [0xF99FFA0] R | `0x1289490  call qword ptr [0xF99FFA0]` | tail-call of obj->vptr[1] through trampoline [0xF99FFA0]; capture return site ret=0x1289496 in all 32 samples [V live docs/data/live/mc_root_4e05e50_callers.txt] | [V] + [V live] |
| 0x1289496 | 1 | - | `0x1289496  nop` | instruction immediately after the tail-call; matches capture ret=0x1289496 (first CALLER ret=0x1289496, all 32 samples) | [V live] |
| 0xF215838+0x008 | 8 | [0xF215838+8] R | - | rdis vt 0xF215838: `1 +0x008  sub_4e05e50` size 0x224 (slot 0 = sub_4e060b0 destructor, slot 2 = non-code) — static anchor of the indirect call target; live capture vptr = 0x7FF6A8215838 matches [V live] | [V] |
| 0xBC73AAA | 1 | [rbp+0x2C] W | `0xBC73AAA  mov byte ptr [rbp+0x2C],0xE` | command byte 0x0E (createTexture) written into the bgfx command buffer [rbx+0xDC5820] at pos [rbx+0xDC5818] (memcpy 0xEBCE390) — command-byte-14 producer sub_bc73770 | [V r4; re-dis this session] |
| 0xBC6A2B1 | 8 | [rax+0xD0] R | `0xBC6A2B1  mov rax,[rax+0xD0]` | bgfx dispatcher case loads RendererContext vtable slot 26 (offset 0xD0) = createTexture 0xe8143c0 [V BGFX_MAP 6et/6fb] | [V] |
| 0xBC6A2C2 | 8 | [0xF99FFA0] R | `0xBC6A2C2  call qword ptr [0xF99FFA0]` | dispatcher issues createTexture through the trampoline; docs/data/live/createtexture_callers.txt: ONE caller, ret=0xBC6A2C8 (call site just before it) | [V live] |
| 0xC296E1A | 5 | - | `0xC296E1A  call 0xBC74120` | wrapper 0xbc74120 converts the returned handle (ax) back to the dragon-layer caller | [V r24] |
| 0xC296E26 | 2 | [rdi] W | `0xC296E26  mov [rdi],ax` | u16 GPU handle stored at texture_obj+0x00; texture_obj = object+0x58 | [V r24] |
| 0x4E05F68 | 4 | - | `0x4E05F68  add rdi,0x58` | texture sub-object address = object + 0x58 (TexturePtr+0x58 base per prior rounds [V r24]); this is where the handle lands | [V] |
| 0x4E05689 | 16 | [rbx+0x58] W | `0x4E05689  movups [rbx+0x58],xmm1` | sub_4e05450 (texture job object constructor) initializes the texture sub-object at object+0x58 (16-byte movups) [V] | [V] |
| 0x4E05F77 | 5 | - | `0x4E05F77  call 0xBC41420` | sub_4e05e50 body issues createTexture via dragon bridge sub_bc41420; return site `0x4E05F7C  nop`, capture ret=0x4E05F7C [V live] | [V] + [V live] |
| 0x4E0564D | 7 | - | `0x4E0564D  lea r8,[0xF215838]` | sub_4e05450 constructor loads vtable address 0xF215838 | [V] |
| 0x4E05654 | 8 | [rbx+0x00] W | `0x4E05654  mov [rbx],r8` | vptr = 0xF215838 stored at job object+0x00, hence object vptr[1] = sub_4e05e50 [V] | [V] |
| 0x54227AF | 5 | - | `0x54227AF  call 0x18718D0` | texgroup_load's only texture-cache call; static chain terminates at cache 0x18718d0 (objects stamped vtable 0xEFCA680, never calls sub_4e05e50/sub_12893d0 [V r24]) | [V] |
| 0xEFCA580+0x020 | 8 | [0xEFCA580+0x20] R | - | rdis vt 0xEFCA580: slot 4 (+0x020) = sub_a3f10 (destructor, size 0x2d), 0 static callers, no bgfx call, no command-byte-0x0E write — the hint's "thin bgfx createTexture wrapper called from texture-object init via vtable 0xEFCA580 slot 4" conditional is NOT met | [V] |

## What was tried and failed (new angles this session, all negative)

- `rdis vt 0xF215838`: slot 1 = sub_4e05e50 statically [V] — anchors the indirect target, but does NOT create a static path from texgroup_load.
- `rdis callers 0x4E05450` (texture job constructor, sets vptr=0xF215838 at `0x4E05654  mov [rbx],r8`): 16 static callers — sub_4dfb810, sub_4dfbdf0, sub_4dfd780, sub_4dfdd90, sub_64f0810, sub_64f0ae0, sub_64f0dd0, sub_66232b0 (x2), sub_6632fd0, sub_668a140, sub_668ecb0, sub_668f080, sub_c28f220, sub_c294b90, sub_c294c90, sub_e86ced0 — none is texgroup_load(0x5421c90)/texload(0x58a1310)/texload_task(0x541bf00) [V].
- `rdis callers 0x12893D0` (job runner, tail-calls vtbl[1] at `0x1289490  call qword ptr [0xF99FFA0]`): 4 static callers — sub_1145c20, sub_6622610, sub_66232b0 (x8), sub_6632bf0 (x2) — all endFrame/deferred-transaction/drain functions; all upward chains dead-end at 0-static-caller functions [V r22/r33]; none is texgroup_load/texload/texload_task.
- `xref.py callers 0x4E05E50`: EMPTY — 0 static calling functions; fn 0x4E05E50..0x4E06074 size 0x224 [V rdis].
- texgroup_load's own [0xF99FFA0] call sites (0x5421d63, 0x5421d8a, 0x5421e43, 0x5421e63, 0x5421e8e, 0x5421ea4, 0x5421f31) resolve to allocator/factory dispatch through [0x1233E1A8]; one factory product is stamped vtable 0xF09AA70, NOT vtable 0xF215838 whose slot 1 is sub_4e05e50 [V r28].
- Hint conditional re-checked: vtable 0xEFCA580 slot 4 = sub_a3f10 destructor (row above), not a createTexture caller; wrappers reachable only from dragon entries [V r4]. No thin bgfx createTexture wrapper is called from any texture-object init.
- [0xF99FFA0] writer scan (prior rounds, not redone): 0 hits; it is a read-only .rdata PE data initializer holding sub_eea6040 `jmp rax`, never set to sub_4e05e50 [V].

## Blocking fact (runtime-only bind)

sub_4e05e50 has 0 static xrefs and is reached only via sub_12893d0's indirect vtable[1] tail-call (rax = obj->vptr[1] loaded by `0x1289486  mov rax,[rcx]` / `0x1289489  mov rax,[rax+8]`, tail-called through trampoline [0xF99FFA0] = sub_eea6040 `0xEEA6040  jmp rax`, return site `0x1289496  nop` [V live]). texgroup_load's static chain ends at `0x54227AF  call 0x18718D0` into the texture cache (vtable 0xEFCA680 objects — a separate system from the vtable 0xF215838 job objects whose slot 1 is sub_4e05e50). The bind texgroup_load -> sub_4e05e50 is therefore runtime-only, observed live [V live]; no static MC-side GPU-handle write into TexturePtr/ClientTexture is instruction-visible.

## CLOSES?

NO — blocking fact: no [V]-proven static path texgroup_load(0x5421c90) -> sub_4e05e50, hence no [V]-proven static path from Minecraft pack-loading code to the createTexture issuance and no static GPU-handle write into TexturePtr/ClientTexture. Everything else in the item IS [V]-proven: sampler flag decode + cache (6ax), D3D12 backend texture-management chain, command-byte-14 producer sub_bc73770 (`0xBC73AAA  mov byte ptr [rbp+0x2C],0xE`), dispatcher slot 26 = createTexture 0xe8143c0 (`0xBC6A2B1  mov rax,[rax+0xD0]` / `0xBC6A2C2  call qword ptr [0xF99FFA0]`, live ret=0xBC6A2C8 [V live]), returned handle stored at texture_obj+0x00 (`0xC296E26  mov [rdi],ax`, size 2, texture_obj = object+0x58 via `0x4E05F68  add rdi,0x58`), sdk TexturePtr/ClientTexture headers. Atlas stitchers (L8a/L8b) remain separate open items (oc_U-EL8a/oc_U-EL8b), out of scope (MIRROR_SKIP).

## TOOL REQUESTS

- None. All instruction lines re-verified verbatim against a fresh rdis dis this session; live capture logs are read-only inputs (docs/data/live/createtexture_callers.txt, mc_root_4e05e50_callers.txt, l8b_texcreate_record.txt, dragon_texture_caller_bc41420.txt, dragon_texture_entry_c296b50.txt). No helper scripts written; no temporary files left behind.
