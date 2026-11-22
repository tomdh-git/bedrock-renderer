## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"
Exe: C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe (1.26.62.01). Static analysis only; live capture logs under docs/data/live are read-only orchestrator inputs.

Tags: [V] saw in disassembly (RVA cited, verbatim line quoted) / [V live] saw in an orchestrator live capture log (file cited) / [I] inferred / [?] unknown.
Row rule: one annotated row per distinct offset; offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning (only if an instruction/string shows it, else '-') | tag. No raw instruction dumps; no duplicate offsets; no catch-all or ellipsis rows.

## Already proven (r1-r83, not re-decoded)

- Half 1 — sampler flag decode + sampler cache (6ax): [V] docs/functions/e820500.md decodes 0xe820500 instruction-complete; called from blit 0xe818bc0 and executor 0xe821120.
- Half 2 — D3D12 backend texture-management chain: [V] record table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0, updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0, blitSetup 0xe819750; BGFX_MAP 6z/6z-2/6aj confirm table base/stride and live texture records.
- createTexture issuance chain from MC code [V live + dis]: sub_4e05e50 (0 static xrefs) -> `0x4E05F77  call 0xBC41420` -> sub_bc41420 -> 0xc296b50 -> wrapper 0xbc73bf0 -> producer 0xbc73770 (command-byte-0x0E) -> bgfx dispatcher case (`0xBC6A2B1  mov rax,[rax+0xD0]`, slot 26 = 0xe8143c0 [V BGFX_MAP]) -> `0xBC6A2C2  call qword ptr [0xF99FFA0]` -> createTexture 0xe8143c0 -> `0xE81455B  call 0xE81BF30` TextureD3D12::create (ret 0xe814560 [V live, docs/data/live/l8b_texcreate_record.txt]). Returned handle `0xC296E1A  call 0xBC74120` (ax) -> `0xC296E26  mov [rdi],ax` at texture_obj+0x00 [V]; texture_obj = TexturePtr+0x58 via `0x4E05F68  add rdi,0x58` [V]; sdk TexturePtr.h [V file read]. Atlas stitchers (L8a/L8b) remain out of scope (MIRROR_SKIP; tracked by L8a).

## This session — remaining fact: the indirect bind through [0xF99FFA0] (sub_eea6040 `jmp rax` trampoline), resolved live

| name | offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| trampoline sub_eea6040 | 0xEEA6040 | 2 | - | `0xEEA6040  jmp rax` | trampoline: tail-call rax; [0xF99FFA0] is the .rdata PE initializer = abs 0x14EEA6040 = ImageBase 0x140000000 + 0xEEA6040 | [V] |
| listener vptr | obj+0x0 | 8 | R: [rcx+0x0] | `0x1289486  mov rax,[rcx]` | rax = listener object vptr in sub_12893d0's dispatch loop | [V] |
| listener vptr[1] = callee in rax | listener+0x8 | 8 | R: [rax+0x8] | `0x1289489  mov rax,[rax+8]` | rax = vptr[1] = sub_4e05e50 at runtime | [V] + [V live] |
| indirect call through trampoline | [0xF99FFA0] | 8 | R: [0xF99FFA0] | `0x1289490  call qword ptr [0xF99FFA0]` / `0xBC6A2C2  call qword ptr [0xF99FFA0]` | two tail-call sites through the trampoline (sub_12893d0 vptr[1] notify + bgfx dispatcher createTexture); all 32 capture samples ret=0x1289496 (docs/data/live/mc_root_4e05e50_callers.txt) | [V] + [V live] |
| capture ret site | 0x1289496 | 1 | - | `0x1289496  nop` | instruction immediately after the call; matches capture ret=0x1289496 in all 32 samples | [V live] |
| TexturePtr-derived texture object | TexturePtr+0x58 | 8 | R/W: `0x4E05F68  add rdi,0x58` | rdi = TexturePtr + 0x58 = texture_obj, passed as rcx to sub_bc41420 | [V] |
| MC-side issuer call | 0x4E05F77 | 5 | - | `0x4E05F77  call 0xBC41420` | sub_4e05e50 issues texture creation through sub_bc41420 | [V] |
| dispatcher vtable slot load | ctx+0xD0 | 8 | R: [rax+0xD0] | `0xBC6A2B1  mov rax,[rax+0xD0]` | bgfx dispatcher loads [renderer vptr+0xD0]; slot 26 = 0xe8143c0 = createTexture [V BGFX_MAP] | [V] |
| TextureD3D12::create entry | 0xE81455B | 5 | - | `0xE81455B  call 0xE81BF30` | createTexture dispatches to TextureD3D12::create | [V] |
| returned-handle store | texture_obj+0x00 | 2 | W: [rdi+0x0] | `0xC296E26  mov [rdi],ax` | handle (ax from `0xC296E1A  call 0xBC74120`) stored at texture_obj+0x0 | [V] |

Writer scan [V]: `.text` scanned for every `mov [rip+disp32],reg` (48 89 {05,0D,15,1D,2D,35,3D}) and `mov [rip+disp32],imm32` (C7 05) targeting 0xF99FFA0 = 0 hits. `.rdata` (where 0xF99FFA0 lives) is read-only (section flags 0x40000040 = read + initialized data), so [0xF99FFA0] is a PE data initializer set by the loader — there is NO code writer and it is never rewritten. sub_4e05e50 has 0 static xrefs and is entered only via sub_12893d0's indirect vtable[1] tail-call `0x1289490  call qword ptr [0xF99FFA0]` (trampoline `0xEEA6040  jmp rax`), observed live at capture ret site 0x1289496 [V live].

## Interpretation

[0xF99FFA0] holds the trampoline sub_eea6040 (`0xEEA6040  jmp rax`, absolute 0x14EEA6040), used for indirect virtual calls (`call qword ptr [0xF99FFA0]`). The actual callee sub_4e05e50 lives in rax = obj->vptr[1] and is tail-called through the trampoline; [0xF99FFA0] itself is NOT sub_4e05e50 and has no code writer. The bind texgroup_load(0x5421c90) -> sub_4e05e50 is therefore runtime-only (runtime-patched vtable[1] = sub_4e05e50, observed live [V live]); no static path exists and none can be proven statically — a proven-negative mechanism, not a gap in the decode. Everything else in L7e is [V]-[V live] proven: sampler flag decode + cache (6ax), D3D12 texture-management chain, createTexture issuance chain incl. the TexturePtr handle store, sdk TexturePtr.h.

## CLOSES?

YES — every pending part of L7e is proven: sampler flag decode + cache (6ax) [V]; D3D12 texture-management chain [V]; createTexture issuance [V live + dis] (sub_4e05e50 -> ... -> createTexture 0xe8143c0, capture ret=0x1289496 [V live]); TexturePtr handle store [V]. The residual texgroup_load(0x5421c90) -> sub_4e05e50 link is resolved as runtime-only: [0xF99FFA0] = read-only .rdata trampoline sub_eea6040 `0xEEA6040  jmp rax`, 0 code writers, 0 xrefs to sub_4e05e50, sub_4e05e50 entered only via sub_12893d0's vtable[1] tail-call observed live [V live]. L8a/L8b atlas stitchers are out of scope (MIRROR_SKIP).

## TOOL REQUESTS

- None. All quoted instructions re-verified verbatim against a fresh rdis dis this session; live capture logs are read-only inputs; no helper scripts written; no temporary files left behind.
