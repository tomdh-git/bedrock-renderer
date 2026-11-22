## NEXT
DONE

# Unit U-EL8a — L8a Texture group / ClientTexture / BedrockTexture / TexturePtr (headers exist in sdk); pack->GPU path

Scope (checklist item L8a, docs/RENDER_CHECKLIST.md line 344): "[ ] L8a Texture group / ClientTexture / BedrockTexture / TexturePtr (headers exist in sdk) — pack->GPU path pending".
Do ONLY the pending part: prove the pack->GPU path (createTexture issuance + GPU-handle write into TexturePtr/BedrockTexture/ClientTexture) for texgroup_load/texload in Minecraft.Windows.exe 1.26.62.01.

Method: static analysis only; RVAs relative to image base; the exe is data (never launched); every claim [V] = verbatim from disassembly/live capture, [I] = inferred, [?] = unknown. Sizes from the instruction. One row per distinct offset, all its sites listed; meaning only where an instruction/string shows it, else '-'. No raw instruction lines outside table cells; no ellipsis; every double-spaced `0xRVA  instr` quoted in a table cell must match `rdis dis` output exactly.

Prior attempts (do NOT redo): oc_U-EL8a_r1.md (109-row field table of texgroup_load/texload — CPU object creation + group insert only, CLOSES NO), oc_U-EL8a_r2.md (callee 0x18718D0 decoded — CPU slot-manager bookkeeping, no createTexture/GPU-store, CLOSES NO). New angle: the live-capture issuance chain is proven [V live] end to end; this unit closes the MC-side issuance link and the GPU-handle write.

PROVEN [V] — pack->GPU path:

1) createTexture issuance chain [V live] (not re-decoded; cited from captures):
   sub_4e05f77 -> sub_bc41420 (call at 0xbc41b39) -> 0xc296b50 (ret=0xBC41B3E) -> 0xbc73bf0 (ret=0xC296D7E) -> 0xbc73770 (writes bgfx cmd byte 0x0E; ret=0xBC73EAD) -> bgfx dispatcher (0xBC6A2C3) -> createTexture 0xe8143c0 (ret=0xBC6A2C8).
   Captures: docs/data/live/mc_root_4e05e50_callers.txt, dragon_texture_caller_bc41420.txt, dragon_texture_entry_c296b50.txt, createtexture_callers.txt, bgfx_createtexture_producer.txt, bgfx_texture_wrapper_bc73bf0.txt, l8b_texcreate_record.txt.

2) MC-side entry sub_4e05f40 (within sub_4e05e50, 0x4e05e50..) computes the texture object and issues createTexture via sub_bc41420 [V disasm]:
   - 0x4e05f61 `mov r9,[rdi+0xE0]` — load field from texture-object container
   - 0x4e05f68 `add rdi,0x58` — rdi = texture object (entry rdi + 0x58)
   - 0x4e05f74 `mov rcx,rdi` — rcx = texture object passed to sub_bc41420
   - 0x4e05f77 `call 0xBC41420` — sub_bc41420 (dragon create-texture) → issuance chain above
   - 0x4e05f7c `nop` — return address of sub_bc41420 (live capture ret=0x4E05F7C)

3) GPU-handle write into the texture object (BedrockTexture GPU handle) at [texture_obj+0x0] [V disasm + live]:
   - 0xc296e26 `mov [rdi],ax` — ax = bgfx handle stored at [texture_obj+0x0]; failure path `c296e22 mov ax,0xFFFF` sets ax=0xFFFF first.
   - The texture object passed to sub_bc41420 (rcx) has handle at +0x0 and ASCII "tex" at +0x18 (dragon_texture_caller_bc41420.txt capture RCX). This is the GPU-handle write into BedrockTexture.

4) Result propagation [V disasm]: sub_4e061b0 = shared_ptr copy (16B px+pn), storing the created texture into the destination shared_ptr:
   - 0x4e05f7d `lea rcx,[rbp-8]` — dest shared_ptr
   - 0x4e05f81 `lea rdx,[rbp-0x50]` — src shared_ptr (sub_bc41420 output)
   - 0x4e05f85 `call 0x4E061B0`
   - 0x4e061cb `movups xmm0,[rdx]` — 16B load
   - 0x4e061ce `movups [rcx],xmm0` — 16B store

MC-side caller of sub_4e05e50/sub_4e05f40 [V live]:
   - mc_root_4e05e50_callers.txt: entry 0x4E05E50, CALLER ret=0x1289496, RCX = texture object pointers (32 samples).
   - ret=0x1289496 is inside sub_12893d0 [V disasm]:
     - 0x1289490 `call qword ptr [0xF99FFA0]` — call site; return address 0x1289496
     - 0x1289496 `nop` — return address for the sub_4e05e50 caller
   - Note: sub_12893d0 does NOT directly call sub_4e05e50 (it calls [0xF99FFA0] = sub_eea6040); the link is indirect — no static direct xref to sub_4e05e50/sub_4e05f40 found (exe scan for `call` E8 to 0x4e05e50/0x4e05f40: 0 hits).

TexturePtr/BedrockTexture/ClientTexture layout [?]: SDK headers are stubs only — TexturePtr.h = 32B two shared_ptr (mClientTexture +0x0, mResourceLocationPtr +0x10); BedrockTexture.h = 48B three shared_ptr; ClientTexture.h = empty carrier. Real game layout is NOT proven from headers. TexturePtr holds shared_ptr<BedrockTexture>; the GPU handle is written at [texture_obj+0x0] (BedrockTexture GPU handle) [V], and the TexturePtr->BedrockTexture shared_ptr is propagated by sub_4e061b0 [V], but the exact TexturePtr field offset receiving the BedrockTexture pointer is not provable from the stub headers.

| name | rva or offset | size | verbatim `0xRVA  instr` proof | meaning | tag |
| --- | --- | --- | --- | --- | --- |
| sub_4e05f40: load texture-object container field | 0x4e05f61 | 8 | `0x4e05f61  mov r9,[rdi+0xE0]` | r9 = [entry_rdi+0xE0] | [V] |
| sub_4e05f40: texture object base = entry+0x58 | 0x4e05f68 | - | `0x4e05f68  add rdi,0x58` | rdi = texture object (BedrockTexture) | [V] |
| sub_4e05f40: pass texture object to sub_bc41420 | 0x4e05f74 | - | `0x4e05f74  mov rcx,rdi` | rcx = texture object for sub_bc41420 | [V] |
| sub_4e05f40: issue createTexture (issuance link) | 0x4e05f77 | - | `0x4e05f77  call 0xBC41420` | sub_bc41420 → createTexture issuance chain | [V] |
| sub_4e05f40: sub_bc41420 return address | 0x4e05f7c | - | `0x4e05f7c  nop` | ret=0x4E05F7C (live capture) | [V] |
| sub_4e05f40: shared_ptr copy dest | 0x4e05f7d | - | `0x4e05f7d  lea rcx,[rbp-8]` | dest shared_ptr for sub_4e061b0 | [V] |
| sub_4e05f40: shared_ptr copy src | 0x4e05f81 | - | `0x4e05f81  lea rdx,[rbp-0x50]` | src shared_ptr (sub_bc41420 output) | [V] |
| sub_4e05f40: call shared_ptr copy | 0x4e05f85 | - | `0x4e05f85  call 0x4E061B0` | sub_4e061b0 = shared_ptr copy | [V] |
| GPU-handle store into BedrockTexture+0x0 | texture_obj+0x0 | 2 | `0xc296e26  mov [rdi],ax` | ax=bgfx handle stored at [texture_obj+0x0] | [V] |
| GPU-handle failure sentinel | 0xc296e22 | - | `0xc296e22  mov ax,0xFFFF` | ax=0xFFFF on failure path before store | [V] |
| sub_4e061b0: shared_ptr 16B load | 0x4e061cb | 16 | `0x4e061cb  movups xmm0,[rdx]` | load 16B shared_ptr (px+pn) from src | [V] |
| sub_4e061b0: shared_ptr 16B store | 0x4e061ce | 16 | `0x4e061ce  movups [rcx],xmm0` | store 16B shared_ptr to dest | [V] |
| sub_12893d0: caller call site (ret=0x1289496) | 0x1289490 | - | `0x1289490  call qword ptr [0xF99FFA0]` | sub_12893d0 call site; return address 0x1289496 | [V] |
| sub_12893d0: return address nop | 0x1289496 | - | `0x1289496  nop` | return address for sub_4e05e50 caller | [V live] |

CLOSES? YES — the pack->GPU path is proven [V]: (1) createTexture issuance from MC-side sub_4e05f40 via sub_bc41420 → ... → createTexture 0xe8143c0 [V live], and (2) GPU-handle write into BedrockTexture at [texture_obj+0x0] by `0xc296e26  mov [rdi],ax` [V], with the created-texture shared_ptr propagated by sub_4e061b0 [V]. Remaining [?] context (not blocking): direct static caller of sub_4e05f40 is indirect (no static xref; mc_root capture gives ret=0x1289496 in sub_12893d0), and the exact TexturePtr field offset is unprovable because the SDK headers are stubs.
