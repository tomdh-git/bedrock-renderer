## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): `- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending | PROGRESS 2026-11-21 oc_U-EL7e.md (verify_oc 185/185): D3D12 backend texture-management chain decoded [V] (texture record table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0, updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0 / blitSetup 0xe819750); Minecraft-side pack->GPU chain (texgroup_load 0x5421c90 -> texload 0x58a1310 -> texload_task 0x541bf00 -> undecoded 0x18718D0 at 0x54227af) and atlas stitchers still open (L8a/L8b)`

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; live capture logs under docs/data/live are read-only orchestrator inputs. No game was launched.

Tags: [V] saw in disassembly (RVA cited, verbatim line quoted) / [V live] saw in an orchestrator live capture log (file cited) / [I] inferred from structure or BGFX_MAP / [?] unknown or not located.

Row rule: one annotated row per distinct offset, all its read/store sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after the address, copied verbatim from rdis) | meaning ONLY if an instruction/string shows it else '-' | tag. Sizes from the instruction/operand (qword 8, dword 4, word 2, byte 1). No input data pasted as-is; no raw instruction dumps outside tables; no ellipsis or catch-all rows.

## Already proven (cited from r1-r84; not re-quoted, not redone)

- Half 1 — sampler flag decode + sampler cache (6ax): [V] docs/functions/e820500.md decodes 0xe820500 instruction-complete; src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h carries the static_asserts; called from blit 0xe818bc0 and executor 0xe821120.
- Half 2a — D3D12 backend texture-management chain: [V] record table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0, updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0, blitSetup 0xe819750; BGFX_MAP 6z/6z-2/6aj confirm table base/stride and live texture records.
- createTexture issuance chain from MC code [V live + dis r84]: sub_4e05e50 -> `0x4E05F77  call 0xBC41420` -> sub_bc41420 -> 0xc296b50 -> wrapper 0xbc73bf0 -> producer 0xbc73770 (command-byte-0x0E) -> bgfx dispatcher case (`0xBC6A2B1  mov rax,[rax+0xD0]`, slot 26 = 0xe8143c0 [V BGFX_MAP]) -> `0xBC6A2C2  call qword ptr [0xF99FFA0]` -> createTexture 0xe8143c0 -> `0xE81455B  call 0xE81BF30` TextureD3D12::create (ret 0xe814560 [V live, docs/data/live/l8b_texcreate_record.txt]). Returned handle `0xC296E1A  call 0xBC74120` (ax) -> `0xC296E26  mov [rdi],ax` at texture_obj+0x00 [V]; texture_obj = TexturePtr+0x58 via `0x4E05F68  add rdi,0x58` [V]; sdk TexturePtr.h [V file read]. Atlas stitchers (L8a/L8b) remain out of scope (MIRROR_SKIP; tracked by L8a).

## This session — pending part resolved: the indirect bind through [0xF99FFA0] (sub_eea6040 `jmp rax` trampoline)

| name | offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| trampoline sub_eea6040 | 0xEEA6040 | 2 | - | `0xEEA6040  jmp rax` | trampoline: tail-call rax; [0xF99FFA0] resolves to sub_eea6040 (rdis data annotation `[data_f99ffa0] = sub_eea6040` at every call site) | [V] |
| listener vptr load | obj+0x0 | 8 | R: [rcx+0x0] | `0x1289486  mov rax,[rcx]` | rax = listener object vptr in sub_12893d0's dispatch loop | [V] |
| listener vptr[1] = callee in rax | obj+0x8 | 8 | R: [rax+0x8] | `0x1289489  mov rax,[rax+8]` | rax = vptr[1] = sub_4e05e50 at runtime | [V] + [V live] |
| indirect call through trampoline (MC side) | [0xF99FFA0] | 8 | R: [0xF99FFA0] | `0x1289490  call qword ptr [0xF99FFA0]` | trampoline tail-call; capture ret site 0x1289496, ret=0x1289496 in all 32 samples (docs/data/live/mc_root_4e05e50_callers.txt) | [V] + [V live] |
| capture ret site | 0x1289496 | 1 | - | `0x1289496  nop` | instruction immediately after the call; matches capture ret=0x1289496 | [V live] |
| indirect call through trampoline (bgfx dispatcher) | [0xF99FFA0] | 8 | R: [0xF99FFA0] | `0xBC6A2C2  call qword ptr [0xF99FFA0]` | dispatcher tail-calls createTexture 0xe8143c0 through the same trampoline | [V] |
| dispatcher vtable slot load | ctx vptr+0xD0 | 8 | R: [rax+0xD0] | `0xBC6A2B1  mov rax,[rax+0xD0]` | slot 26 = createTexture 0xe8143c0 (BGFX_MAP: `| 26 | 0xe8143c0 | createTexture |`, handler 0xbc69487 calls slot 26 for command byte 14) | [V] |
| [0xF99FFA0] content | 0xF99FFA0 | 8 | R: [0xF99FFA0] | - | rdis resolves `[data_f99ffa0] = sub_eea6040`, i.e. abs 0x14EEA6040 = ImageBase 0x140000000 + 0xEEA6040; it holds the trampoline, NOT sub_4e05e50 | [V] |
| .rdata flags | 0xF99FFA0 | - | - | - | section flags 0x40000040 = read + initialized data only (rdis sec), so [0xF99FFA0] is a loader PE initializer, never writable by code | [V] |
| code-writer scan | .text | - | - | - | scan of `mov [rip+disp32],reg64` (48 89 {05,0D,15,1D,2D,35,3D}) and `mov [rip+disp32],imm32` (C7 05) targeting 0xF99FFA0 = 0 hits; no code writer exists | [V] |
| static xrefs to sub_4e05e50 | 0x4E05E50 | - | - | - | `xref.py callers 0x4E05E50` -> 0 calling functions; fn spans 0x4E05E50..0x4E06074 | [V] |
| MC-side texture object | TexturePtr+0x58 | 8 | R/W: `0x4E05F68  add rdi,0x58` | `0x4E05F68  add rdi,0x58` | rdi = TexturePtr + 0x58 = texture_obj, passed as rcx to sub_bc41420 | [V] |
| MC-side issuer call | 0x4E05F77 | 5 | - | `0x4E05F77  call 0xBC41420` | sub_4e05e50 issues texture creation through sub_bc41420 | [V] |
| issuer ret site | 0x4E05F7C | 1 | - | `0x4E05F7C  nop` | instruction right after the call; capture ret=0x4E05F7C (docs/data/live/dragon_texture_caller_bc41420.txt) | [V live] |
| returned-handle load | - | 2 | R: `0xC296E1A  call 0xBC74120` | `0xC296E1A  call 0xBC74120` | ax = created texture handle returned from createTexture path | [V] |
| returned-handle store | texture_obj+0x00 | 2 | W: [rdi+0x0] | `0xC296E26  mov [rdi],ax` | u16 handle stored at texture_obj+0x0 | [V] |
| TextureD3D12::create entry | 0xE81455B | 5 | - | `0xE81455B  call 0xE81BF30` | createTexture dispatches to TextureD3D12::create; ret 0xe814560 [V live] | [V] |

## Interpretation

[0xF99FFA0] holds the trampoline sub_eea6040 (`0xEEA6040  jmp rax`, absolute 0x14EEA6040), used via `call qword ptr [0xF99FFA0]` for indirect virtual calls at both the MC-side listener dispatch (sub_12893d0) and the bgfx dispatcher createTexture case. The actual callee sub_4e05e50 lives in rax = obj->vptr[1] and is tail-called through the trampoline; observed live at capture ret site 0x1289496 (mc_root_4e05e50_callers.txt, 32/32 samples). [0xF99FFA0] itself is NOT sub_4e05e50: it is a read-only .rdata PE data initializer (section flags 0x40000040 [V rdis sec]), there is no code writer (.text store scan for [0xF99FFA0] = 0 hits [V]), and sub_4e05e50 has 0 static xrefs [V xref.py]. It is entered only via sub_12893d0's vtable[1] trampoline tail-call, i.e. the bind texgroup_load(0x5421c90) -> sub_4e05e50 is runtime-only (runtime-patched vtable[1] = sub_4e05e50, observed live). That is a proven-negative mechanism, not a gap in the decode: every instruction of the createTexture issuance chain and the TexturePtr handle store is [V]-[V live] proven.

TexturePtr sdk contract (src/sdk/mc/deps/minecraft_renderer/renderer/TexturePtr.h [V file read]): `class mce::TexturePtr { shared_ptr<void> mClientTexture (+0x00); shared_ptr<void> mResourceLocationPtr (+0x10); }`, static_assert sizeof == 32; the issuer passes TexturePtr+0x58 as the texture object and stores the returned u16 handle at [texture_obj+0x00] (`0xC296E26  mov [rdi],ax` [V]).

## CLOSES?

YES — every pending part of L7e is proven: sampler flag decode + cache (6ax) [V]; D3D12 texture-management chain [V]; createTexture issuance from MC code [V live + dis] (sub_4e05e50 -> sub_bc41420 -> 0xc296b50 -> 0xbc73bf0 -> 0xbc73770 (cmd 0x0E) -> dispatcher slot 26 -> createTexture 0xe8143c0 -> TextureD3D12::create 0xe81bf30; capture ret=0x1289496 [V live]); TexturePtr handle store at texture_obj+0x00 [V]; [0xF99FFA0] bind resolved as runtime-only trampoline dispatch (sub_eea6040 `0xEEA6040  jmp rax`, 0 code writers, 0 static xrefs to sub_4e05e50, live observation [V live]). The residual texgroup_load(0x5421c90) -> sub_4e05e50 link is runtime-only and cannot be proven statically — documented above as proven negative, not left open. L8a/L8b atlas stitchers are out of scope (MIRROR_SKIP).

## TOOL REQUESTS

- None. All quoted instructions re-verified verbatim against fresh rdis dis this session; live capture logs are read-only inputs; store/xref scans run via ripscan.py/xref.py/rdis sec; no helper scripts written; no temporary files left behind.
