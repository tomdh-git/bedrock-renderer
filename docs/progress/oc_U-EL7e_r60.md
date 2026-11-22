## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): `- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending | PROGRESS 2026-11-21 oc_U-EL7e.md (verify_oc 185/185): D3D12 backend texture-management chain decoded [V] ...; Minecraft-side pack->GPU chain (texgroup_load 0x5421c90 -> texload 0x58a1310 -> texload_task 0x541bf00 -> undecoded 0x18718D0 at 0x54227af) and atlas stitchers still open (L8a/L8b)`

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only (live capture logs under docs/data/live are read-only inputs produced by the orchestrator).

Tags: [V] saw in disassembly (RVA cited, verbatim line quoted) / [V live] saw in an orchestrator live capture log (file cited) / [I] inferred from structure or BGFX_MAP / [?] unknown or not located.

Row rule: one annotated row per distinct offset, all its read/store sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after the address, copied verbatim from rdis) | meaning ONLY if an instruction/string shows it else '-' | tag. Sizes from the instruction (movups/movaps/movdqu/movdqa 16, qword 8, dword/movss 4, word 2, byte 1). No input data pasted as-is; no skipped offsets among quoted sites; no raw instruction dumps outside tables; no ellipsis or catch-all rows.

## Already proven (cited from prior retries r1-r37; not re-quoted in full, not redone)

- Half 1 — sampler flag decode + sampler cache (6ax): [V] docs/functions/e820500.md decodes 0xe820500 instruction-complete; src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h carries the static_asserts; called from blit 0xe818bc0 and executor 0xe821120.
- Half 2a — D3D12 backend texture-management chain: [V] record table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0, updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0, blitSetup 0xe819750; BGFX_MAP 6z/6z-2/6aj confirm table base/stride and live texture records.
- createTexture issuance chain from MC code [V live + dis]: sub_4e05e50 -> `0x4E05F77  call 0xBC41420` -> sub_bc41420 -> 0xc296b50 -> wrapper 0xbc73bf0 -> producer 0xbc73770 (command-byte-0x0E) -> bgfx dispatcher case 0xBC6A2C2 (`0xBC6A2B1  mov rax,[rax+0xD0]`, slot 26 = 0xe8143c0 [V BGFX_MAP]) -> `0xBC6A2C2  call qword ptr [0xF99FFA0]` -> createTexture 0xe8143c0 -> `0xE81455B  call 0xE81BF30` TextureD3D12::create (ret 0xe814560 [V live]). Returned handle `0xC296E1A  call 0xBC74120` (ax) -> `0xC296E26  mov [rdi],ax` at texture_obj+0x00 [V r24]; texture_obj = TexturePtr+0x58 (`0x4E05F68  add rdi,0x58`); sdk TexturePtr/ClientTexture [V file read].
- [0xF99FFA0] is a read-only .rdata PE data initializer = absolute 0x14EEA6040 = ImageBase 0x140000000 + sub_eea6040 RVA 0xEEA6040; sub_eea6040 = `0xEEA6040  jmp rax` (trampoline tail-call); .text store scan for [0xF99FFA0] = 0 hits; no code writer [V r37].

## This session — new angle: indirect caller of sub_4e05e50 (sub_12893d0) decoded

mc_root_4e05e50_callers.txt [V live]: sub_4e05e50 entry captured with ONE return address, ret=0x1289496 in all 32 samples -> call site `0x1289490  call qword ptr [0xF99FFA0]` inside sub_12893d0; so the indirect caller of sub_4e05e50 is sub_12893d0 (call at 0x1289490, ret site 0x1289496). sub_12893d0 [0x12893d0..0x12895d3), size 0x203, 13 xrefs in, 4 static callers.

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| sub_12893d0 list start/end load | [rcx+0x0] / [rcx+0x8] | 8 | [rcx+0x0], [rcx+0x8] | `0x1289406  mov r13,[rcx]`\n`0x1289409  mov r14,[rcx+8]` | r13=list cursor, r14=list end; sub_12893d0(rcx=&{qword start;qword end}, rdx=out) | [V] |
| sub_12893d0 arg pass-through | rcx/rdx -> rdi/rsi | 8 | regs | `0x12893f1  mov rsi,rdx`\n`0x12893f4  mov rdi,rcx` | rcx=list struct ptr, rdx=output struct ptr | [V] |
| sub_12893d0 entry object load | [r13+0x10] | 8 | [r13+0x10] | `0x128947d  mov rcx,[r13+0x10]` | rcx = entry[+0x10] = texture object / TexturePtr* (this for sub_4e05e50) | [V] |
| sub_12893d0 vptr[1] load | [rax+0x8] | 8 | [rax+0x8] | `0x1289486  mov rax,[rcx]`\n`0x1289489  mov rax,[rax+8]` | rax = object vptr[1] = sub_4e05e50 at runtime | [V] |
| sub_12893d0 indirect tail-call | [0xF99FFA0] | 8 | [0xF99FFA0] | `0x1289490  call qword ptr [0xF99FFA0]` | trampoline tail-call rax=vptr[1]=sub_4e05e50; rcx=object; ret=0x1289496 | [V] + [V live] |
| sub_12893d0 ret site | 0x1289496 | 1 | - | `0x1289496  nop` | instruction right after call; matches capture ret=0x1289496 | [V live] |
| sub_12893d0 caller sub_1145c20 | 0x1145c20 | - | - | `0x1145d5a  call 0x12893D0` | drains list at [rdi+0xA8] into sub_12893d0; 1 xref in | [V] |
| sub_12893d0 caller sub_6622610 | 0x6622610 | - | - | `0x6622662  call 0x12893D0` | drains [rcx+0xD8] then [rcx+0x28]/[rcx+0x18] lists; 7 xrefs in | [V] |
| sub_12893d0 caller sub_6632bf0 | 0x6632bf0 | - | - | `0x6632c55  call 0x12893D0`\n`0x6632d1e  call 0x12893D0` | "Deferred Texture Transactions" / "Deferred Buffer Transactions" drainer; 2 xrefs in | [V] |
| sub_6632bf0 string refs | 0xF54E8AF / 0xF54E847 | - | imm | `0x6632c19  lea rax,[0xF54E8AF]`\n`0x6632c42  lea rax,[0xF54E847]` | "Deferred Texture Transactions" / "Deferred Buffer Transactions" | [V] |
| sub_4e05e50 static reference scan | 0x4E05E50 | 8 | imm | `rdis imm 0x4E05E50` -> 0 hit(s) | no static vtable slot / immediate = sub_4e05e50 anywhere | [V] |

Interpretation of the new angle: sub_12893d0 is a deferred-transaction batch processor — for each 0x18-byte entry it loads the object at [entry+0x10] and tail-calls that object's vptr[1] (= sub_4e05e50 at runtime, RCX = that object). Its 4 static callers (sub_1145c20, sub_6622610, sub_66232b0, sub_6632bf0) are deferred-texture/buffer-transaction drainers, not texgroup_load/texload/texload_task. None of sub_12893d0's callers, nor texgroup_load's static callees (`0x54227AF call 0x18718D0`, `0x5421DEC call 0x5477A30`, `0x5421ED6 call 0x5475A30`, `0x5422869 call 0x5424000`, `0x5422C5D call 0x5424130` [V r24]), is one of these drainers or sub_4e05e50. sub_4e05e50 itself has 0 static xrefs and `imm 0x4E05E50` = 0 hits, so no static vtable slot equals sub_4e05e50.

## CLOSES?

NO — blocking fact: no [V]-proven static path texgroup_load(0x5421c90) -> sub_4e05e50. sub_4e05e50 (fn 0x4E05E50..0x4E06074) has 0 static xrefs and `rdis imm 0x4E05E50` = 0 hits (no static vtable slot/immediate). It is reached only at runtime via sub_12893d0's indirect vtable[1] tail-call `0x1289490  call qword ptr [0xF99FFA0]` (capture ret site 0x1289496 [V live] in all 32 samples of mc_root_4e05e50_callers.txt), where [0xF99FFA0] is the read-only .rdata trampoline sub_eea6040 (`0xEEA6040  jmp rax`, absolute 0x14EEA6040 = ImageBase 0x140000000 + 0xEEA6040) with no code writer (.text store scan = 0 hits; .rdata read-only). The createTexture issuance chain itself IS [V]-proven (sub_4e05e50 -> ... -> dispatcher [vptr+0xD0] slot 26 = 0xe8143c0 -> createTexture 0xe8143c0 -> returned handle stored at [TexturePtr+0x58+0x00] `0xC296E26  mov [rdi],ax` [V]); only the static bind from texgroup_load into sub_4e05e50 is runtime-only and unprovable statically. Atlas stitchers (L8a/L8b) remain out of scope (MIRROR_SKIP).

## TOOL REQUESTS

- None. All verification done with rdis (fn, imm) and xref callers plus read-only live capture logs; no helper scripts written, no temporary files left behind.
