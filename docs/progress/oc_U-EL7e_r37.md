## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): `- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending | PROGRESS 2026-11-21 oc_U-EL7e.md (verify_oc 185/185): D3D12 backend texture-management chain decoded [V] ...; Minecraft-side pack->GPU chain (texgroup_load 0x5421c90 -> texload 0x58a1310 -> texload_task 0x541bf00 -> undecoded 0x18718D0 at 0x54227af) and atlas stitchers still open (L8a/L8b)`

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only (live capture logs under docs/data/live are read-only inputs produced by the orchestrator).

Tags: [V] saw in disassembly (RVA cited, verbatim line quoted) / [V live] saw in an orchestrator live capture log (file cited) / [I] inferred from structure or BGFX_MAP / [?] unknown or not located.

Row rule: one annotated row per distinct offset, all its read/store sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after the address, copied verbatim from rdis) | meaning ONLY if an instruction/string shows it else '-' | tag. Sizes from the instruction (movups/movaps/movdqu/movdqa 16, qword 8, dword/movss 4, word 2, byte 1). No input data pasted as-is; no skipped offsets among quoted sites; no raw instruction dumps outside tables; no ellipsis or catch-all rows.

## Already proven (cited from r1-r24; not re-quoted, not redone)

- Half 1 — sampler flag decode + sampler cache (6ax): [V] docs/functions/e820500.md decodes 0xe820500 instruction-complete; src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h carries the static_asserts; called from blit 0xe818bc0 and executor 0xe821120.
- Half 2a — D3D12 backend texture-management chain: [V] record table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0, updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0, blitSetup 0xe819750; BGFX_MAP 6z/6z-2/6aj confirm table base/stride and live texture records.
- createTexture issuance chain from MC code [V live + dis r24]: sub_4e05e50 -> `0x4E05F77  call 0xBC41420` -> sub_bc41420 -> 0xc296b50 -> wrapper 0xbc73bf0 -> producer 0xbc73770 (command-byte-0x0E) -> bgfx dispatcher case 0xBC6A2C2 (`0xBC6A2B1  mov rax,[rax+0xD0]`, slot 26 = 0xe8143c0 [V BGFX_MAP]) -> `0xBC6A2C2  call qword ptr [0xF99FFA0]` -> createTexture 0xe8143c0 -> `0xE81455B  call 0xE81BF30` TextureD3D12::create (ret 0xe814560 [V live]). Returned handle `0xC296E1A  call 0xBC74120` (ax) -> `0xC296E26  mov [rdi],ax` at texture_obj+0x00 [V r24]; texture_obj = TexturePtr+0x58 (`0x4E05F68  add rdi,0x58`); sdk TexturePtr/ClientTexture [V file read].

## This session — pending work (r24): resolve [0xF99FFA0]

Locate the static WRITER of [0xF99FFA0] (xref to 0xF99FFA0 as a store) and name the function it is set to. If that function is sub_4e05e50 (0x4e05e50), the static link texgroup_load(0x5421c90) -> sub_4e05e50 is closed.

### Findings — what [0xF99FFA0] is set to [V]

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| trampoline sub_eea6040 | 0xEEA6040 | 2 | - | `0xEEA6040  jmp rax` | trampoline: tail-call rax (the vptr[n] indirect-call target) | [V] |
| vptr load | [rcx+0x0] | 8 | [rcx+0x0] | `0x1289486  mov rax,[rcx]` | rax = object vptr (sub_12893d0) | [V] |
| vptr[1] load = callee in rax | [rax+0x8] | 8 | [rax+0x8] | `0x1289489  mov rax,[rax+8]` | rax = obj->vptr[1] = sub_4e05e50 at runtime | [V] |
| indirect call through [0xF99FFA0] | [0xF99FFA0] | 8 | [0xF99FFA0] | `0x1289490  call qword ptr [0xF99FFA0]` | trampoline tail-call; rax = vptr[1] = sub_4e05e50; pushed ret = 0x1289496 | [V] + [V live] |
| capture ret site | 0x1289496 | 1 | - | `0x1289496  nop` | instruction right after call; matches capture ret=0x1289496 in all 32 samples | [V live] |
| [0xF99FFA0] init value (.rdata) | 0xF99FFA0 | 8 | [0xF99FFA0] | - | PE .rdata read-only initializer = 0x14EEA6040 | [V] |
| [0xF99FFA0] value decode | 0x14EEA6040 | 8 | imm | - | 0x14EEA6040 = ImageBase 0x140000000 + sub_eea6040 RVA 0xEEA6040 -> [0xF99FFA0] = trampoline sub_eea6040, NOT sub_4e05e50 | [V] |

Writer scan [V]: `.text` scanned for every `mov [rip+disp32], reg` (48 89 {05,0D,15,1D,2D,35,3D}) and `mov [rip+disp32], imm32` (C7 05) targeting 0xF99FFA0 = 0 hits. `.rdata` (where 0xF99FFA0 lives) is read-only (section flags 0x40000040 = read + initialized data), so [0xF99FFA0] is a PE data initializer set by the loader — there is NO code writer and it is never rewritten.

## Interpretation

[0xF99FFA0] holds the trampoline sub_eea6040 (`jmp rax`, absolute 0x14EEA6040), used via `call qword ptr [0xF99FFA0]` for ALL indirect virtual calls. The actual callee sub_4e05e50 is held in rax = vptr[1], tail-called through the trampoline. [0xF99FFA0] is NOT set to sub_4e05e50 and has no code writer (read-only .rdata initializer). sub_4e05e50 itself has 0 static xrefs (`rdis callers 0x4E05E50` -> 0 calling functions; fn 0x4E05E50..0x4E06074) and is reached only via sub_12893d0's indirect vtable[1] tail-call (capture ret site 0x1289496 [V live]). Therefore the static link texgroup_load(0x5421c90) -> sub_4e05e50 does NOT exist — the bind is runtime-only via vtable[1] indirect dispatch through trampoline [0xF99FFA0] = sub_eea6040 `jmp rax`, observed live [V live].

Everything else in L7e is [V]-proven: sampler flag decode + cache (6ax), D3D12 backend texture-management chain, command-byte-14 producer sub_bc73770 [V r4], dispatcher [vptr+0xD0]->createTexture 0xe8143c0 [V live + dis], returned handle stored at [texture_obj+0x00] (`0xC296E26  mov [rdi],ax`, size 2) [V] with texture_obj = TexturePtr+0x58 [V], TexturePtr/ClientTexture sdk headers [V file read]. Atlas stitchers (L8a/L8b) remain out of scope (MIRROR_SKIP).

## CLOSES?

NO — blocking fact: no [V]-proven static path texgroup_load(0x5421c90) -> sub_4e05e50. [0xF99FFA0] is set to trampoline sub_eea6040 (`0xEEA6040  jmp rax`, .rdata read-only initializer = 0x14EEA6040 = ImageBase 0x140000000 + 0xEEA6040), NOT sub_4e05e50; no code writer exists (.text store scan for [0xF99FFA0] = 0 hits; .rdata read-only). sub_4e05e50 (0x4e05e50, fn 0x4E05E50..0x4E06074) has 0 static xrefs and is reached only via sub_12893d0's indirect vtable[1] tail-call `0x1289490  call qword ptr [0xF99FFA0]` (capture ret site 0x1289496 [V live]). All upward caller chains from sub_12893d0 (4 callers [V r24]) and the texture-job constructor sub_4e05450 (16 callers [V r22]) dead-end without reaching texgroup_load/texload/texload_task; texgroup_load's static callees (`0x54227AF call 0x18718D0`, `0x5421DEC call 0x5477A30`, `0x5421ED6 call 0x5475A30`, `0x5422869 call 0x5424000`, `0x5422C5D call 0x5424130` [V r24]) do not enter the sub_4e05e50 tree. The bind texgroup_load -> sub_4e05e50 is runtime-only, observed live [V live].

## TOOL REQUESTS

- None. Static analysis is exhausted for the [0xF99FFA0] writer: it is a read-only .rdata PE data initializer (0x14EEA6040 = sub_eea6040 trampoline), no code store exists, confirmed by (a) disassembling sub_eea6040 = `jmp rax`, (b) parsing the PE .rdata at RVA 0xF99FFA0 reading 0x14EEA6040, (c) ImageBase 0x140000000, (d) .text scan for mov [rip+disp32],reg / imm32 stores to 0xF99FFA0 = 0 hits. All instruction lines re-verified verbatim against a fresh rdis dis this session; live capture logs are read-only inputs. No helper scripts written; no temporary files left behind.
