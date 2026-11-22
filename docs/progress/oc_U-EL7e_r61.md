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
- createTexture issuance chain from MC code [V live + dis r24]: sub_4e05e50 -> `0x4E05F77  call 0xBC41420` -> sub_bc41420 -> 0xc296b50 -> wrapper 0xbc73bf0 -> producer 0xbc73770 (command-byte-0x0E) -> bgfx dispatcher case 0xBC6A2C2 (`0xBC6A2B1  mov rax,[rax+0xD0]`, slot 26 = 0xe8143c0 [V BGFX_MAP]) -> `0xBC6A2C2  call qword ptr [0xF99FFA0]` -> createTexture 0xe8143c0 -> `0xE81455B  call 0xE81BF30` TextureD3D12::create (ret 0xe814560 [V live]). Returned handle `0xC296E1A  call 0xBC74120` (ax) -> `0xC296E26  mov [rdi],ax` at texture_obj+0x00 [V r24]; texture_obj = TexturePtr+0x58 (`0x4E05F68  add rdi,0x58`); sdk TexturePtr/ClientTexture [V file read]. Atlas stitchers (L8a/L8b) remain out of scope (MIRROR_SKIP).

## This session — new angle on the single blocking fact

Blocking fact carried in from r1-r37: no [V]-proven static path texgroup_load(0x5421c90) -> sub_4e05e50. sub_4e05e50 (0x4E05E50) has 0 static xrefs and is reached only via an indirect vtable[1] tail-call through trampoline [0xF99FFA0].

New angle attempted: resolve sub_4e05e50 as a vtable[1] target using rdis `ptr`/`vt`, and locate any static store of that vtable address as an object vptr (constructor). Results below.

### Findings — verified this session, verbatim

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| trampoline sub_eea6040 | 0xEEA6040 | 2 | - | `0xEEA6040  jmp rax` | trampoline: jmp rax tail-call | [V] |
| vptr load | [rcx+0x0] | 8 | [rcx+0x0] | `0x1289486  mov rax,[rcx]` | rax = object vptr (sub_12893d0) | [V] |
| vptr[1] load = callee in rax | [rax+0x8] | 8 | [rax+0x8] | `0x1289489  mov rax,[rax+8]` | rax = obj->vptr[1] callee | [V] |
| arg copy | - | - | - | `0x128948d  mov rdx,rbx` | rdx = rbx | [V] |
| indirect tail-call via trampoline | [0xF99FFA0] | 8 | [0xF99FFA0] | `0x1289490  call qword ptr [0xF99FFA0]` | trampoline tail-call target | [V] |
| ret site | 0x1289496 | 1 | - | `0x1289496  nop` | instruction right after the call | [V live] |
| sub_4e05e50 entry | 0x4E05E50 | 8 | - | `0x4E05E50  push rbp` | sub_4e05e50 prologue | [V] |
| this copy | - | - | - | `0x4E05E6E  mov rdi,rcx` | rdi = rcx = texture object this | [V] |
| texgroup_load entry | 0x5421C90 | 8 | - | `0x5421C90  push rbp` | texgroup_load prologue | [V] |

### vtable resolution [V]

- `ptr 0x4E05E50` -> one pointer stored at RVA `0xF215840` (.rdata): sub_4e05e50's address is held as a vtable slot.
- `vt 0xF215838`: slot[0]=sub_4e060b0 (destructor), slot[1]=sub_4e05e50, slot[2]=non-code 0x0. So sub_4e05e50 = vptr[1] of vtable 0xF215838, size 0x224.
- `ptr 0xF215838` -> 0 pointers: no static store of the vtable address as an object vptr located; the constructor that binds vptr = vtable 0xF215838 was not found statically.

### New-angle attempts that failed

- `callers 0x4E05E50` -> `0 calling function(s)`: sub_4e05e50 has no static callers; reached only indirectly.
- `ptr 0xF215838` -> `0 pointer(s)`: the vtable address is not stored as a findable vptr in data; no static constructor located.
- [0xF99FFA0] writer scan (r37): `.text` scanned for every `mov [rip+disp32], reg` / `mov [rip+disp32], imm32` store to 0xF99FFA0 = 0 hits; .rdata is read-only, so [0xF99FFA0] is a PE data initializer with no code writer and is never rewritten.

## Interpretation

sub_4e05e50 is vptr[1] of vtable 0xF215838 (slot[1], size 0x224). sub_12893d0 loads rax = [rcx] (vptr), rax = [rax+8] (vptr[1] = sub_4e05e50 at runtime), then `0x1289490  call qword ptr [0xF99FFA0]` tail-calls through trampoline `0xEEA6040  jmp rax`. Therefore rax = vptr[1] = sub_4e05e50 at the jmp — confirmed [V static] by the vtable[1] resolution (vt 0xF215838 slot[1] = sub_4e05e50) and [V live] by docs/data/live/mc_root_4e05e50_callers.txt (capture at sub_4e05e50 entry rva=0x4E05E50, ret=0x1289496 in all 32 samples; RCX = texture object). [0xF99FFA0] is the read-only trampoline used for ALL indirect virtual calls; it is NOT set to sub_4e05e50 and has no code writer.

Everything else in L7e is [V]-proven: sampler flag decode + cache (6ax), D3D12 backend texture-management chain, command-byte-14 producer sub_bc73770 [V r4], dispatcher [vptr+0xD0]->createTexture 0xe8143c0 [V live + dis], returned handle stored at [texture_obj+0x00] (`0xC296E26  mov [rdi],ax`, size 2) [V] with texture_obj = TexturePtr+0x58 [V], TexturePtr/ClientTexture sdk headers [V file read].

## CLOSES?

NO — blocking fact: no [V]-proven static path texgroup_load(0x5421c90) -> sub_4e05e50. sub_4e05e50 (0x4E05E50, size 0x224) has 0 static xrefs (`callers 0x4E05E50` -> 0 calling functions) and is reached only via sub_12893d0's indirect vtable[1] tail-call `0x1289490  call qword ptr [0xF99FFA0]` through trampoline `0xEEA6040  jmp rax` ([0xF99FFA0] read-only .rdata initializer, no code writer, store scans = 0 hits). rax = vptr[1] = sub_4e05e50 at the jmp ([V] vtable 0xF215838 slot[1]; [V live] capture ret=0x1289496). All upward caller chains from sub_12893d0 and texgroup_load's static callees dead-end without reaching sub_4e05e50 (r1-r24); `ptr 0xF215838` located no static vptr assignment. The bind texgroup_load -> sub_4e05e50 is runtime-only (object vtable[1] dispatch through the read-only trampoline), observed live, not statically provable.

## TOOL REQUESTS

- None. No helper scripts written; no temporary files left behind.
