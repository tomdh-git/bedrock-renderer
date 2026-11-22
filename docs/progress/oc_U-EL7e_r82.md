## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"
Exe: C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe (1.26.62.01). Static analysis only; live capture logs under docs/data/live are read-only orchestrator inputs.

Tags: [V] saw in disassembly (RVA cited, verbatim line quoted) / [V live] saw in an orchestrator live capture log (file cited) / [I] inferred / [?] unknown.
Row rule: one annotated row per distinct offset; offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning (only if shown by an instruction/string, else '-') | tag. No raw instruction dumps; no duplicate offsets; no catch-all or ellipsis rows.

## Already proven (r1-r37, not re-decoded)

- Half 1 — sampler flag decode + sampler cache (6ax): [V] docs/functions/e820500.md decodes 0xe820500 instruction-complete; src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h carries the static_asserts; called from blit 0xe818bc0 and executor 0xe821120.
- Half 2 — D3D12 backend texture-management chain: [V] record table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0, updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0, blitSetup 0xe819750; BGFX_MAP 6z/6z-2/6aj confirm table base/stride and live texture records.
- createTexture issuance chain from MC code [V live + dis]: sub_4e05e50 -> `0x4E05F77  call 0xBC41420` -> sub_bc41420 -> 0xc296b50 -> wrapper 0xbc73bf0 -> producer 0xbc73770 (command-byte-0x0E) -> bgfx dispatcher case (`0xBC6A2B1  mov rax,[rax+0xD0]`, slot 26 = 0xe8143c0 [V BGFX_MAP]) -> `0xBC6A2C2  call qword ptr [0xF99FFA0]` -> createTexture 0xe8143c0 -> `0xE81455B  call 0xE81BF30` TextureD3D12::create (ret 0xe814560 [V live]). Returned handle `0xC296E1A  call 0xBC74120` (ax) -> `0xC296E26  mov [rdi],ax` at texture_obj+0x00 [V]; texture_obj = TexturePtr+0x58 (`0x4E05F68  add rdi,0x58`); sdk TexturePtr/ClientTexture [V file read].

## This session — resolve the indirect bind [0xF99FFA0] (the only remaining fact)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| trampoline sub_eea6040 | 0xEEA6040 | 2 | - | `0xEEA6040  jmp rax` | trampoline: tail-call rax (the vptr[n] indirect-call target) | [V] |
| vptr load | [rcx+0x0] | 8 | [rcx+0x0] | `0x1289486  mov rax,[rcx]` | rax = object vptr (sub_12893d0) | [V] |
| vptr[1] load = callee in rax | [rax+0x8] | 8 | [rax+0x8] | `0x1289489  mov rax,[rax+8]` | rax = obj->vptr[1] = sub_4e05e50 at runtime | [V] |
| indirect call through trampoline | [0xF99FFA0] | 8 | [0xF99FFA0] | `0x1289490  call qword ptr [0xF99FFA0]` | trampoline tail-call; rax = vptr[1] = sub_4e05e50; pushed ret = 0x1289496 | [V] + [V live] |
| capture ret site | 0x1289496 | 1 | - | `0x1289496  nop` | instruction right after the call; matches capture ret=0x1289496 in all 32 samples of docs/data/live/mc_root_4e05e50_callers.txt | [V live] |
| [0xF99FFA0] init value (.rdata) | 0xF99FFA0 | 8 | [0xF99FFA0] | - | PE .rdata read-only initializer = 0x14EEA6040 = ImageBase 0x140000000 + sub_eea6040 RVA 0xEEA6040 | [V] |

Writer scan [V]: `.text` scanned for every `mov [rip+disp32], reg` (48 89 {05,0D,15,1D,2D,35,3D}) and `mov [rip+disp32], imm32` (C7 05) targeting 0xF99FFA0 = 0 hits. `.rdata` (where 0xF99FFA0 lives) is read-only (section flags 0x40000040 = read + initialized data), so [0xF99FFA0] is a PE data initializer set by the loader — there is NO code writer and it is never rewritten.

## Captured issuer (docs/data/live/mc_root_4e05e50_callers.txt) [V live]

sub_4e05e50 is entered with return address ret=0x1289496 (the call site `0x1289490  call qword ptr [0xF99FFA0]` in sub_12893d0), matching in all 32 samples. RCX (first arg) = TexturePtr* values (e.g. 0x3908FFDE900) matching sdk TexturePtr.h. So the indirect caller of sub_4e05e50 is sub_12893d0 (ret site 0x1289496), passing a TexturePtr*. sub_12893d0 is a vtable[1] indirect-call thunk: `0x1289486  mov rax,[rcx]` / `0x1289489  mov rax,[rax+8]` / `0x1289490  call qword ptr [0xF99FFA0]`. Its 4 static callers and texgroup_load(0x5421c90)'s static callees (`0x54227AF call 0x18718D0`, `0x5421DEC call 0x5477A30`, `0x5421ED6 call 0x5475A30`, `0x5422869 call 0x5424000`, `0x5422C5D call 0x5424130`) dead-end — no static path texgroup_load -> sub_4e05e50 exists; the bind is runtime-only via vtable[1] = sub_4e05e50 through trampoline [0xF99FFA0] = sub_eea6040 `jmp rax`, observed live [V live].

## Interpretation

[0xF99FFA0] holds the trampoline sub_eea6040 (`0xEEA6040  jmp rax`, absolute 0x14EEA6040), used via `call qword ptr [0xF99FFA0]` for indirect virtual calls. The actual callee sub_4e05e50 is held in rax = obj->vptr[1] and tail-called through the trampoline. [0xF99FFA0] is NOT set to sub_4e05e50 and has no code writer (read-only .rdata initializer; 0 store hits in .text). sub_4e05e50 (0x4e05e50) has 0 static xrefs and is reached only via sub_12893d0's indirect vtable[1] tail-call (capture ret site 0x1289496 [V live]).

Everything in L7e is [V]-[V live] proven: sampler flag decode + cache (6ax), D3D12 backend texture-management chain, command-byte-14 producer sub_bc73770 [V], dispatcher [vptr+0xD0]->createTexture 0xe8143c0 [V live + dis], returned handle stored at [texture_obj+0x00] (`0xC296E26  mov [rdi],ax`, size 2) [V] with texture_obj = TexturePtr+0x58 [V], TexturePtr/ClientTexture sdk headers [V file read]. Atlas stitchers (L8a/L8b) remain out of scope (MIRROR_SKIP; tracked by L8a).

## CLOSES?

YES — every pending part of L7e is proven: sampler flag decode + cache (6ax) [V]; D3D12 texture-management chain [V]; createTexture issuance [V live + dis] (sub_4e05e50 -> ... -> createTexture 0xe8143c0, capture ret=0x1289496 [V live]); TexturePtr handle store [V]. The residual static-path question is resolved as a proven-negative mechanism: no static texgroup_load(0x5421c90) -> sub_4e05e50 path exists ([0xF99FFA0] = read-only .rdata trampoline sub_eea6040 `0xEEA6040  jmp rax`, 0 code writers, 0 xrefs to sub_4e05e50, sub_12893d0's callers dead-end); the bind is runtime vtable[1] = sub_4e05e50, observed live [V live]. L8a/L8b atlas stitchers are out of scope (MIRROR_SKIP).

## TOOL REQUESTS

- None. Static analysis is exhausted: [0xF99FFA0] is a read-only .rdata PE data initializer (0x14EEA6040 = sub_eea6040 trampoline), no code store exists (0 .text store hits), sub_4e05e50 has 0 static xrefs and is reached only via sub_12893d0's vtable[1] tail-call (capture ret=0x1289496 [V live]). All quoted instructions re-verified verbatim against a fresh rdis dis this session; live capture logs are read-only inputs. No helper scripts written; no temporary files left behind.
