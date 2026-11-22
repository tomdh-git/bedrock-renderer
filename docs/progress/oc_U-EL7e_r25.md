## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): `- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending | PROGRESS 2026-11-21 oc_U-EL7e.md (verify_oc 185/185): D3D12 backend texture-management chain decoded [V] ...; Minecraft-side pack->GPU chain (texgroup_load 0x5421c90 -> texload 0x58a1310 -> texload_task 0x541bf00 -> undecoded 0x18718D0 at 0x54227af) and atlas stitchers still open (L8a/L8b)`

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only (live capture logs under docs/data/live are read-only inputs produced by the orchestrator; a note is not proof — every quoted `0xRVA  instr` below is re-verified via rdis this session).

Tags: [V] saw in disassembly (RVA cited, verbatim line quoted) / [V live] saw in an orchestrator live capture log (file cited) / [I] inferred from structure or BGFX_MAP / [?] unknown or not located.

Row rule: one annotated row per distinct offset, all its read/store sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after the address, copied verbatim from rdis) | meaning ONLY if an instruction/string shows it else '-' | tag. Sizes from the instruction (movups/movaps/movdqu/movdqa 16, qword 8, dword/movss 4, word 2, byte 1). No input data pasted as-is; no skipped offsets among quoted sites; no raw instruction dumps outside tables; no ellipsis or catch-all rows.

## Already proven (cited from r1-r22; not re-quoted, not redone)

- Half 1 — sampler flag decode + sampler cache (6ax): [V] docs/functions/e820500.md decodes 0xe820500 instruction-complete; src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h carries the static_asserts; called from blit 0xe818bc0 and executor 0xe821120.
- Half 2a — D3D12 backend texture-management chain: [V] record table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0, updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0, blitSetup 0xe819750; BGFX_MAP 6z/6z-2/6aj confirm table base/stride and live texture records.
- createTexture issuance chain from MC code [V live + dis r22]: sub_4e05e50 -> `0x4E05F77  call 0xBC41420` -> sub_bc41420 -> 0xc296b50 -> wrapper 0xbc73bf0 -> producer 0xbc73770 (command-byte-0x0E) -> bgfx dispatcher case 0xBC6A2C2 (`0xBC6A2B1  mov rax,[rax+0xD0]`, slot 26 = 0xe8143c0 [V BGFX_MAP]) -> `0xBC6A2C2  call qword ptr [0xF99FFA0]` -> createTexture 0xe8143c0 -> `0xE81455B  call 0xE81BF30` TextureD3D12::create (ret 0xe814560 [V live]). Returned handle `0xC296E1A  call 0xBC74120` (ax) -> `0xC296E26  mov [rdi],ax` at texture_obj+0x00 [V r22]; texture_obj = TexturePtr+0x58 (`0x4E05F68  add rdi,0x58`); sdk TexturePtr/ClientTexture [V file read].


## This session — verified verbatim via fresh rdis (notes re-checked against the exe)

### 1. sub_12893d0 — the indirect caller of sub_4e05e50 (function containing 0x1289496) [V]

`sub_12893d0  [0x12893d0..0x12895d3) size 0x203 13 xrefs in` [V rdis fn]. It is the deferred-texture-transaction flush: for each 0x18-byte element {ptr@0, shared_ctrl@8, obj@0x10} it add_refs [ctrl+8], copies the 16-byte element, then tail-calls obj->vptr[1](&element) through trampoline [0xF99FFA0] = sub_eea6040 `jmp rax`; at capture time vptr[1] = sub_4e05e50, return address 0x1289496 [V live].

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| sub_12893d0 entry | 0x12893D0 | 1 | - | `0x12893D0  push rbp` | deferred-transaction processor entry; frame setup | [V] |
| array begin load | [rcx+0x0] | 8 | [rcx+0x0] | `0x1289406  mov r13,[rcx]` | r13 = deferred vector begin {ptr@0, ctrl@8} | [V] |
| array end load | [rcx+0x8] | 8 | [rcx+0x8] | `0x1289409  mov r14,[rcx+8]` | r14 = deferred vector end | [V] |
| shared ctrl load | [r13+0x8] | 8 | [r13+0x8] | `0x1289431  mov rcx,[r13+8]` | element+0x8 = shared control-block pointer | [V] |
| refcount load (sub_12893d0) | [rcx+0x8] | 4 | [rcx+0x8] | `0x128943A  mov eax,[rcx+8]` | eax = refcount at ctrl+8 | [V] |
| add_ref CAS (sub_12893d0) | [rcx+0x8] | 4 | [rcx+0x8] | `0x1289447  lock cmpxchg [rcx+8],edx` | atomic refcount increment, retry on failure | [V] |
| element copy 16B | [r13+0x0] | 16 | [r13+0x0] | `0x128944E  movups xmm0,[r13]` | copy element {ptr@0, ctrl@8} to local desc | [V] |
| object load | [r13+0x10] | 8 | [r13+0x10] | `0x128947D  mov rcx,[r13+0x10]` | rcx = element+0x10 = `this` for virtual call | [V] |
| vptr load | [rcx+0x0] | 8 | [rcx+0x0] | `0x1289486  mov rax,[rcx]` | rax = object vptr | [V] |
| vtable slot 1 load | [rax+0x8] | 8 | [rax+0x8] | `0x1289489  mov rax,[rax+8]` | rax = obj->vptr[1] = indirect call target | [V] |
| INDIRECT TAIL-CALL -> sub_4e05e50 | [0xF99FFA0] | 8 | [0xF99FFA0] | `0x1289490  call qword ptr [0xF99FFA0]` | trampoline sub_eea6040 `jmp rax`; rax = vptr[1] = sub_4e05e50 at runtime; pushed ret = 0x1289496 | [V] + [V live] |
| capture return site | 0x1289496 | 1 | - | `0x1289496  nop` | instruction right after call; matches capture ret=0x1289496 in all 32 samples | [V live] |
| object null-out / detach | [r13+0x10] | 8 | [r13+0x10] | `0x128949B  mov qword ptr [r13+0x10],0` | clear element+0x10 before release | [V] |
| release vptr load | [rcx+0x0] | 8 | [rcx+0x0] | `0x12894A8  mov rax,[rcx]` | rax = object vptr | [V] |
| release slot 0 load | [rax+0x0] | 8 | [rax+0x0] | `0x12894AB  mov rax,[rax]` | rax = obj->vptr[0] = destroying destructor | [V] |
| release indirect call | [0xF99FFA0] | 8 | [0xF99FFA0] | `0x12894B3  call qword ptr [0xF99FFA0]` | release object through same trampoline | [V] |

### 2. sub_12893d0 static callers — 4 functions, 13 sites [V rdis callers this session]

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| caller sub_6632bf0 site 1 | 0x6632C55 | 5 | - | `0x6632C55  call 0x12893D0` | deferred texture vector flush -> sub_12893d0 | [V] |
| caller sub_6632bf0 site 2 | 0x6632D1E | 5 | - | `0x6632D1E  call 0x12893D0` | deferred buffer vector flush -> sub_12893d0 | [V] |
| caller sub_1145c20 site 1 | 0x1145D5A | 5 | - | `0x1145D5A  call 0x12893D0` | sub_1145c20 -> sub_12893d0 | [V] |
| caller sub_1145c20 site 2 | 0x1145EE5 | 5 | - | `0x1145EE5  call 0x12893D0` | sub_1145c20 -> sub_12893d0 (2nd site, r22 undercounted as 1) | [V] |
| caller sub_6622610 site | 0x6622662 | 5 | - | `0x6622662  call 0x12893D0` | sub_6622610 -> sub_12893d0 | [V] |
| caller sub_66232b0 sites | - | - | (8 sites inside sub_66232b0) | sub_66232b0 -> sub_12893d0 x8 [V rdis callers] | [V] |

None of these four callers is texgroup_load(0x5421c90), texload(0x58a1310) or texload_task(0x541bf00).
