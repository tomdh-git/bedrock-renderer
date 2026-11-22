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
- createTexture issuance chain from MC code [V live + dis r24]: sub_4e05e50 -> `0x4E05F77  call 0xBC41420` -> sub_bc41420 -> 0xc296b50 -> wrapper 0xbc73bf0 -> producer 0xbc73770 (command-byte-0x0E) -> bgfx dispatcher case 0xBC6A2C2 (`0xBC6A2B1  mov rax,[rax+0xD0]`, slot 26 = 0xe8143c0 [I BGFX_MAP]) -> `0xBC6A2C2  call qword ptr [0xF99FFA0]` -> createTexture 0xe8143c0 -> `0xE81455B  call 0xE81BF30` TextureD3D12::create (ret 0xe814560 [V live]). Returned handle `0xC296E1A  call 0xBC74120` (ax) -> `0xC296E26  mov [rdi],ax` at texture_obj+0x00 [V]; texture_obj = TexturePtr+0x58 (`0x4E05F68  add rdi,0x58`); sdk TexturePtr/ClientTexture [V file read].

## This session — new angle on the blocking fact (static link texgroup_load(0x5421c90) -> sub_4e05e50)

The blocking fact carried from r37: no [V]-proven static path texgroup_load -> sub_4e05e50; sub_4e05e50 has 0 static call xrefs and [0xF99FFA0] is a read-only .rdata initializer, not sub_4e05e50. This session tested whether sub_4e05e50 has ANY static reference that could re-establish the link.

### What was tried (all [V], all negative for a static call path)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| trampoline sub_eea6040 | 0xEEA6040 | 2 | - | `0xEEA6040  jmp rax` | trampoline: tail-call rax (the vtable[n] indirect-call target) | [V] |
| vptr load | [rcx+0x0] | 8 | [rcx+0x0] | `0x1289486  mov rax,[rcx]` | rax = object vptr (sub_12893d0) | [V] |
| vptr[1] load = callee in rax | [rax+0x8] | 8 | [rax+0x8] | `0x1289489  mov rax,[rax+8]` | rax = obj->vptr[1] = sub_4e05e50 at runtime | [V] |
| indirect call through [0xF99FFA0] | [0xF99FFA0] | 8 | [0xF99FFA0] | `0x1289490  call qword ptr [0xF99FFA0]` | trampoline tail-call; rax = vptr[1] = sub_4e05e50; pushed ret = 0x1289496 | [V] + [V live] |
| capture ret site | 0x1289496 | 1 | - | `0x1289496  nop` | instruction right after call; matches capture ret=0x1289496 in all 32 samples (docs/data/live/mc_root_4e05e50_callers.txt) | [V live] |
| [0xF99FFA0] init value (.rdata) | 0xF99FFA0 | 8 | [0xF99FFA0] | - | PE .rdata read-only initializer = 0x14EEA6040 | [V] |
| [0xF99FFA0] value decode | 0x14EEA6040 | 8 | imm | - | 0x14EEA6040 = ImageBase 0x140000000 + sub_eea6040 RVA 0xEEA6040 -> [0xF99FFA0] = trampoline sub_eea6040, NOT sub_4e05e50 | [V] |
| [0xF99FFA0] writer scan | [0xF99FFA0] | 8 | - | - | .text scanned for every `mov [rip+disp32],reg` / `mov [rip+disp32],imm32` targeting 0xF99FFA0 = 0 hits; .rdata read-only (section flags 0x40000040), so [0xF99FFA0] is a PE data initializer set by the loader — no code writer, never rewritten | [V] |
| dispatcher loads vtable[0xD0] | [rax+0xD0] | 8 | [rax+0xD0] | `0xBC6A2B1  mov rax,[rax+0xD0]` | rax = RendererContext vtable slot 26 = handler pointer; slot 26 = createTexture 0xe8143c0 [I BGFX_MAP] | [V] |
| dispatcher indirect call | [0xF99FFA0] | 8 | [0xF99FFA0] | `0xBC6A2C2  call qword ptr [0xF99FFA0]` | dispatcher tail-calls slot-26 handler via trampoline -> createTexture 0xe8143c0 | [V] |
| sub_4e05e50 as vtable[1] (NEW finding) | 0xF215840 | 8 | [0xF215840] (.rdata) | - | `rdis vt 0xF215838`: slot0 +0x000 sub_4e060b0, slot1 +0x008 sub_4e05e50, slot2 +0x010 non-code 0x0. `rdis ptr 0x4E05E50` -> f215840 (.rdata), 1 pointer: sub_4e05e50's only static reference is vtable[1] data | [V] |
| no static call to sub_4e05e50 | sub_4e05e50 | - | - | - | `rdis callers 0x4E05E50` = 0 calling functions; `xr 0x4E05E50` = 0 xrefs; `imm 0x4E05E50` = 0 hits; `imm 0x144E05E50` = 0 hits; ripscan 0x4E05E50 = 0 hits; fn 0x4E05E50..0x4E06074. sub_4e05e50 is referenced ONLY as vtable[1] data at 0xF215840, never as a call target | [V] |
| texture_obj = TexturePtr+0x58 | 0x4E05F68 | - | add rdi,0x58 | `0x4E05F68  add rdi,0x58` | rdi = TexturePtr; texture_obj = rdi+0x58 | [V] |
| sub_4e05e50 -> sub_bc41420 | 0x4E05F77 | 4 | call 0xBC41420 | `0x4E05F77  call 0xBC41420` | sub_4e05e50 (TexturePtr*) issues createTexture via sub_bc41420 -> 0xc296b50 -> wrapper 0xbc73bf0 -> producer 0xbc73770 (cmd 0x0E) | [V] + [V live] |
| returned handle (ax) | 0xC296E1A | 4 | call 0xBC74120 | `0xC296E1A  call 0xBC74120` | ax = createTexture handle from wrapper 0xbc73bf0/0xbc74120 (docs/data/live/dragon_texture_caller_bc41420.txt, createtexture_callers.txt) | [V live] |
| handle stored into TexturePtr | [texture_obj+0x00] | 2 | mov [rdi],ax | `0xC296E26  mov [rdi],ax` | [texture_obj+0x00] = ax; texture_obj = TexturePtr+0x58 (docs/data/live/dragon_texture_caller_bc41420.txt) | [V] |

## Interpretation

The createTexture issuance and the handle trace into TexturePtr are fully [V]-proven (issuance chain, dispatcher slot-26 vcall, returned handle stored at [texture_obj+0x00], texture_obj = TexturePtr+0x58, sdk TexturePtr/ClientTexture headers).

The single remaining gap is the static bind texgroup_load(0x5421c90) -> sub_4e05e50. This session's new angle confirms sub_4e05e50 DOES have a static reference — as vtable[1] at vtable 0xF215838 (+0x008 = 0xF215840, `rdis vt`/`rdis ptr`, [V]) — but it is referenced NOWHERE as a call target (`rdis callers`/`xr`/`imm`/`ripscan` all = 0 hits, [V]). The indirect call `0x1289490  call qword ptr [0xF99FFA0]` in sub_12893d0 tail-calls vptr[1] through trampoline [0xF99FFA0]; [0xF99FFA0] itself is the read-only .rdata initializer 0x14EEA6040 = sub_eea6040 (`jmp rax`), not sub_4e05e50, and has no code writer (.text store scan = 0 hits; .rdata read-only). The runtime target rax = vptr[1] = sub_4e05e50 is observed live [V live] (capture ret=0x1289496, all 32 samples in docs/data/live/mc_root_4e05e50_callers.txt).

All upward caller chains from sub_12893d0 (4 callers [V r24]) and the texture-job constructor sub_4e05450 (16 callers [V r22]) dead-end without reaching texgroup_load/texload/texload_task; texgroup_load's static callees (`0x54227AF call 0x18718D0`, `0x5421DEC call 0x5477A30`, `0x5421ED6 call 0x5475A30`, `0x5422869 call 0x5424000`, `0x5422C5D call 0x5424130` [V r24]) do not enter the sub_4e05e50 tree. Therefore the bind texgroup_load -> sub_4e05e50 is runtime-only (vtable[1] indirect dispatch through trampoline [0xF99FFA0] = sub_eea6040) and cannot be proven statically.

## CLOSES?

NO — blocking fact: no [V]-proven static path texgroup_load(0x5421c90) -> sub_4e05e50. sub_4e05e50 (0x4e05e50, fn 0x4E05E50..0x4E06074) has 0 static call xrefs; its only static reference is vtable[1] data at 0xF215840 (vtable 0xF215838, slot0 sub_4e060b0, slot1 sub_4e05e50, slot2 null [V rdis vt/ptr]). The indirect call `0x1289490  call qword ptr [0xF99FFA0]` (sub_12893d0) tail-calls vptr[1] through trampoline [0xF99FFA0]; [0xF99FFA0] = sub_eea6040 (`0xEEA6040  jmp rax`, .rdata read-only initializer = 0x14EEA6040 = ImageBase 0x140000000 + 0xEEA6040), NOT sub_4e05e50, with no code writer (.text store scan = 0 hits). Runtime target rax = vptr[1] = sub_4e05e50 observed live [V live] (capture ret site 0x1289496, docs/data/live/mc_root_4e05e50_callers.txt, all 32 samples). Everything else in L7e is [V]-proven (sampler flag decode + cache (6ax), D3D12 backend texture-management chain, command-byte-14 producer sub_bc73770 [V r4], dispatcher [vptr+0xD0]->createTexture 0xe8143c0 [V live + dis], returned handle stored at [texture_obj+0x00] `0xC296E26  mov [rdi],ax` size 2 [V] with texture_obj = TexturePtr+0x58 [V], TexturePtr/ClientTexture sdk headers [V file read]). Atlas stitchers (L8a/L8b) remain out of scope (MIRROR_SKIP).

## TOOL REQUESTS

- None. New-angle evidence gathered with rdis only (`vt`, `ptr`, `callers`, `xr`, `imm`, `dis`); ripscan.py used for 0x4E05E50. All instruction lines re-verified verbatim against a fresh rdis dis this session; live capture logs are read-only inputs. No helper scripts written; no temporary files left behind.
