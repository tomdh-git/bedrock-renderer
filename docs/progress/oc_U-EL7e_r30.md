## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): `- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending | PROGRESS 2026-11-21 oc_U-EL7e.md (verify_oc 185/185): D3D12 backend texture-management chain decoded [V] ...; Minecraft-side pack->GPU chain (texgroup_load 0x5421c90 -> texload 0x58a1310 -> texload_task 0x541bf00 -> undecoded 0x18718D0 at 0x54227af) and atlas stitchers still open (L8a/L8b)`

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; live capture logs under docs/data/live are read-only orchestrator inputs. Every quoted `0xRVA  instr` was re-verified verbatim via rdis this session unless cited [V r1-r29].

Tags: [V] saw in disassembly (verbatim line quoted, RVA cited) / [V live] saw in an orchestrator live capture log (file cited) / [I] inferred from structure or BGFX_MAP / [?] unknown or not located.

Row rule: one annotated row per distinct offset, all its read/store sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after address, copied verbatim from rdis) | meaning ONLY if an instruction/string shows it else '-' | tag. Sizes from the instruction (movups/movaps/movdqu/movdqa 16, qword 8, dword/movss 4, word 2, byte/nop 1). No input data pasted as-is; no skipped offsets among quoted sites; no raw instruction dumps outside tables; no catch-all or ellipsis rows

## Already proven (cited from r1-r29; not re-decoded, re-verified verbatim where quoted)

- Half 1 — sampler flag decode + sampler cache (6ax): [V] docs/functions/e820500.md decodes 0xe820500 instruction-complete; src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h carries static_asserts; called from blit 0xe818bc0 and executor 0xe821120.
- Half 2a — D3D12 backend texture-management chain: [V] record table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0, updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0, blitSetup 0xe819750; BGFX_MAP 6z/6z-2/6aj confirm table base/stride and live texture records.
- createTexture has no static caller (`xref.py callers 0xe8143c0` EMPTY [V r2]); reached via RendererContext [vptr+0xD0] slot 26 = 0xe8143c0 -> bgfx dispatcher vcall or command byte 14 -> handler 0xbc69487.

## Table 1 — createTexture issuance chain from MC-side code [V live + dis]

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| sub_4e05e50 entry | 0x4E05E50 | 1 | - | `0x4E05E50  push rbp` | texture-object create/load method (vtable[1]); rdis `sub_4e05e50 [0x4e05e50..0x4e06074) size 0x224 0 xrefs in` | [V] |
| renderer context load | [rdi+0xE0] | 8 | [rdi+0xE0] | `0x4E05F61  mov r9,[rdi+0xE0]` | object+0xE0 = renderer context -> R9 (object >= 0xE8 bytes) | [V] |
| texture sub-object | rdi+0x58 | - | reg | `0x4E05F68  add rdi,0x58` | rdi = embedded texture sub-object (TexturePtr+0x58) | [V] |
| dragon create call | 0x4E05F77 | 5 | - | `0x4E05F77  call 0xBC41420` | sub_bc41420 -> 0xc296b50 -> ... -> createTexture | [V] |
| sub_4e05e50 ret site | 0x4E05F7C | 1 | - | `0x4E05F7C  nop` | return after sub_bc41420; live capture ret=0x4E05F7C | [V] + [V live] |
| dragon entry call site | 0xBC41B39 | 5 | - | `0xBC41B39  call 0xC296B50` | sub_bc41420 calls dragon entry 0xc296b50; capture ret=0xBC41B3E | [V] + [V live] |
| wrapper returns handle | 0xC296E1A | 5 | - | `0xC296E1A  call 0xBC74120` | wrapper 0xbc74120 returns 16-bit texture handle in ax | [V] |
| invalid-handle fallback | 0xC296E22 | 2 | - | `0xC296E22  mov ax,0xFFFF` | 0xFFFF = invalid handle fallback | [V] |
| handle store word | [rdi+0x00] | 2 | [rdi+0x00] | `0xC296E26  mov [rdi],ax` | 16-bit handle stored at texture object +0x00 | [V] |
| rest of result | [rdi+0x08] | 16 | [rdi+0x08] | `0xC296E32  movups [rdi+8],xmm0` | 16 result bytes stored at texture object +0x08 | [V] |
| dispatcher slot-26 load | [rax+0xD0] | 8 | [rax+0xD0] | `0xBC6A2B1  mov rax,[rax+0xD0]` | slot 26 (0xD0/8) = createTexture address; BGFX_MAP line 403: slot 26 = 0xe8143c0 | [V] |
| dispatcher vcall | [0xF99FFA0] | 8 | [0xF99FFA0] | `0xBC6A2C2  call qword ptr [0xF99FFA0]` | trampoline tail-call; rax = [vptr+0xD0] = createTexture 0xe8143c0; capture ret=0xBC6A2C8 | [V] + [V live] |
| result test | 0xBC6A2C8 | 4 | - | `0xBC6A2C8  test rax,rax` | handle/result tested; return site of live createTexture caller | [V] |
| createTexture -> TextureD3D12::create | 0xE81455B | 5 | - | `0xE81455B  call 0xE81BF30` | TextureD3D12::create fills the texture record; ret site 0xE814560 = live capture l8b ret=0xE814560 | [V] + [V live] |

Chain (MC end proven [V live]): texture job object (vptr 0x7FF6A8215838 = RVA 0xF215838 + base; vptr[1] = sub_4e05e50) created by sub_4e05450 (`0x4E05654  mov [rbx],r8` stores vptr; `0x4E0573A  mov [rbx+0xE0],rax` stores renderer ctx; `0x4E05689  movups [rbx+0x58],xmm1` inits texture sub-object) -> sub_12893d0@0x1289490 (tail-call via trampoline [0xF99FFA0] = sub_eea6040 `jmp rax`, return address 0x1289496) -> sub_4e05e50 (`0x4E05F77  call 0xBC41420`, return site `0x4E05F7C  nop`) -> sub_bc41420 -> 0xc296b50 -> 0xbc73bf0 -> 0xbc73770 (command-byte-0x0E producer [V r4]) -> bgfx dispatcher case 0xBC6A2C2 -> `0xBC6A2C2  call qword ptr [0xF99FFA0]` -> createTexture 0xe8143c0 -> `0xE81455B  call 0xE81BF30` TextureD3D12::create. Returned handle: `0xC296E1A  call 0xBC74120` (ax) -> `0xC296E26  mov [rdi],ax` at texture_obj+0x00 [V]; texture_obj = TexturePtr+0x58 [V]; sdk TexturePtr/ClientTexture [V file read].

## Table 2 — TexturePtr / ClientTexture connection [V]

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| texture_obj = TexturePtr+0x58 | object+0x58 | - | reg | `0x4E05F68  add rdi,0x58` | the created handle lands inside the texture object carried by sub_4e05e50 | [V] |
| handle at texture_obj+0x00 | [rdi+0x00] | 2 | [rdi+0x00] | `0xC296E26  mov [rdi],ax` | 16-bit handle stored at texture object +0x00 | [V] |
| TexturePtr size check | sizeof(TexturePtr) | - | - | - | `static_assert(sizeof(TexturePtr) == 32)` [V file read src/sdk/mc/deps/minecraft_renderer/renderer/TexturePtr.h] | [V] |
| TexturePtr members | mClientTexture +0x00 / mResourceLocationPtr +0x10 | - | - | - | two shared_ptr members [V file read TexturePtr.h] | [V] |
| ClientTexture | empty struct | - | - | - | ClientTexture empty struct [V file read] | [V] |
| BedrockTexture size | sizeof(BedrockTexture) | - | - | - | `static_assert(sizeof(BedrockTexture) == 48)` [V file read BedrockTexture.h] | [V] |

sub_4e05e50's RCX is the polymorphic texture OBJECT itself (constant vptr 0x7FF6A8215838 across all 32 capture samples; reads object+0xE0 proving size >= 0xE8) [V live + dis] — it is NOT a TexturePtr* (TexturePtr is 32 bytes and non-polymorphic) [V file read + V dis].

## Table 3 — [0xF99FFA0] runtime indirect-call trampoline; resolved [V] (NEW ANGLE — writer search)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| static contents | 0xF99FFA0 | 8 | - | - | file bytes at RVA 0xF99FFA0 = 0x14EEA6040 = image base + RVA 0xEEA6040; statically holds sub_eea6040, NOT sub_4e05e50 (0x4E05E50) | [V] |
| thunk body | 0xEEA6040 | 2 | E: `0xEEA6040  jmp rax` | `0xEEA6040  jmp rax` | trampoline: jumps to rax (the real indirect-call target is materialized in rax by the caller) | [V] |
| alternate entry | 0xEEA6060 | 8 | [0xF99FFA0] | `0xEEA6060  jmp qword ptr [0xF99FFA0]` | second entry jumps through the same global slot; rdis resolves `[data_f99ffa0] = sub_eea6040` | [V] |
| dispatcher read site | [0xF99FFA0] | 8 | R: `0xBC6A2C2  call qword ptr [0xF99FFA0]` | `0xBC6A2C2  call qword ptr [0xF99FFA0]` | createTexture vcall through trampoline | [V] + [V live] |
| sub_12893d0 tail-call read | [0xF99FFA0] | 8 | R: `0x1289490  call qword ptr [0xF99FFA0]` | `0x1289490  call qword ptr [0xF99FFA0]` | obj->vptr[1] tail-call; capture return site `0x1289496  nop` = ret=0x1289496 in all 32 samples | [V] + [V live] |
| texgroup_load read site | [0xF99FFA0] | 8 | R: `0x5421d63  call qword ptr [0xF99FFA0]` | `0x5421d63  call qword ptr [0xF99FFA0]` | texgroup_load indirect call through trampoline | [V] |
| store hunt — writer of [0xF99FFA0] | .text | - | - | `xr 0xF99FFA0` over .text: zero `mov [0xF99FFA0],...` store destinations; only read sites | no code writer exists; never patched | [V r26/r29] |
| section writability | .rdata | - | - | rdis `sec`: `.rdata` flags read-only (MEM_READ, no MEM_WRITE); 0xF99FFA0 lies inside .rdata | cannot be modified at runtime | [V r26] |

[0xF99FFA0] is read-only, holds sub_eea6040 (`jmp rax`), is never written by code, and is NOT sub_4e05e50 (0x4E05E50). texgroup_load references 0x4E05E50 nowhere (rdis imm 0x4E05E50: 0 hits [V r22]).

## Table 4 — NEW ANGLE: texgroup_load's [0xF99FFA0] sites are global-allocator calls, not sub_4e05e50 [V]

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| global manager load | [data_1233e1a8] | 8 | R: `0x5421d45  mov rcx,[0x1233E1A8]` | `0x5421d45  mov rcx,[0x1233E1A8]` | rcx = global object at [0x1233E1A8] | [V] |
| manager vptr[1] load | [rcx] / [rax+8] | 8 | R: `0x5421d4c  mov rax,[rcx]` / R: `0x5421d4f  mov rax,[rax+8]` | `0x5421d4c  mov rax,[rcx]` / `0x5421d4f  mov rax,[rax+8]` | rax = [0x1233E1A8]->vptr[1] | [V] |
| trampoline call | [0xF99FFA0] | 8 | R: `0x5421d63  call qword ptr [0xF99FFA0]` | `0x5421d63  call qword ptr [0xF99FFA0]` | jumps to rax = vptr[1]; result -> rcx (`0x5421d90  mov rcx,rax`) | [V] |
| allocator identity | [0x1233E1A8] vtable+8 | - | - | docs/RENDER_CHECKLIST.md:338 CORRECTION: `[0x1233E1A8]` vtable+8 is the global allocator's allocate(size=edx) | those calls are allocations, not CreateHeap/texture create | [V] + checklist |

So texgroup_load's `[0xF99FFA0]` calls route through the global allocator's vtable[1] (`allocate(size=edx)`), not sub_4e05e50. This new angle is resolved NEGATIVE: no static link texgroup_load -> sub_4e05e50 via the trampoline.

## Table 5 — Missing static link: negative evidence [V]

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| texgroup_load cache call | 0x54227AF | 5 | - | `0x54227AF  call 0x18718D0` | texgroup_load calls texture cache 0x18718d0 directly (not texload/texload_task/sub_4e05e50) | [V] |
| sub_4e05e50 xrefs | 0x4E05E50 | - | - | `rdis callers 0x4E05E50` -> 0 calling functions | sub_4e05e50 has 0 static xrefs; fn [0x4E05E50..0x4E06074) size 0x224 | [V] |
| sub_4e05e50 reached only via | [0xF99FFA0] | 8 | R: `0x1289490  call qword ptr [0xF99FFA0]` | `0x1289490  call qword ptr [0xF99FFA0]` | sub_12893d0 tail-calls obj->vptr[1] through trampoline; at runtime vptr[1] = sub_4e05e50 (vtable 0xF215838 slot 1) | [V] + [V live] |
| sub_12893d0 static callers | 0x6632C55 / 0x6632D1E / 0x1145D5A / 0x6622662 / 0x66232b0 | 5 | - | `0x6632C55  call 0x12893D0` / `0x6632D1E  call 0x12893D0` / `0x1145D5A  call 0x12893D0` / `0x6622662  call 0x12893D0` | 13 xrefs in across sub_6632bf0/sub_1145c20/sub_6622610/sub_66232b0; none is texgroup_load/texload/texload_task | [V] |
| upward chains dead-end | sub_66232b0 / sub_661f200 | - | - | `rdis callers` -> 0 calling functions | all top functions have 0 static callers [V rdis/xref] | [V] |
| sub_4e05450 callers | sub_4e05450 | - | - | 16 static callers [V rdis callers]: sub_4dfb810, sub_4dfbdf0, ... none is texgroup_load/texload/texload_task | texture job constructor (sets vptr=0xF215838) never called by texgroup_load | [V] |
| cache object type | 0x18718d0 | - | - | cache 0x18718d0 builds objects with vtable 0xEFCA680 [V prior] | cache objects have vtable 0xEFCA680, NOT 0xF215838 whose slot 1 is sub_4e05e50 | [V] |

texgroup_load's static chain ends at `0x54227AF call 0x18718D0` plus allocator/release/factory trampoline sites (Table 4); none enters sub_4e05e50's tree. The bind texgroup_load -> sub_4e05e50 is runtime-only (object vptr+8 = sub_4e05e50 via vtable 0xF215838, tail-call trampoline [0xF99FFA0] = sub_eea6040 `jmp rax`) and is observed live [V live].

## What I tried that failed (do not redo)

- [0xF99FFA0] writer search (r22-directed new work): `rdis imm 0xEEA6040` -> 0 hits; `xref.py ptr 0xF99FFA0` -> only `.rdata 0xefc6a08`; sub_12893d0 contains no `mov [0xF99FFA0], ...`. Result: [0xF99FFA0] = sub_eea6040 trampoline, not sub_4e05e50 — r22 closure condition NOT met, static link NOT closed via this route [V r26-r29].
- texgroup_load [0xF99FFA0] sites (new angle this session): resolve to global allocator `[0x1233E1A8]` vtable+8 = `allocate(size=edx)` [V RENDER_CHECKLIST.md:338 + dis], not sub_4e05e50.
- Upward caller chains from all four sub_12893d0 callers (sub_1145c20, sub_6622610, sub_66232b0, sub_6632bf0): every top function has 0 static callers [V rdis/xref] — none is texgroup_load/texload. sub_4e060b0: 0 static callers. sub_4e05450: 16 static callers, none is texgroup_load/texload/texload_task. rdis imm 0x4E05E50: 0 hits. TexturePtr* claim for sub_4e05e50's RCX: refuted — RCX is a polymorphic texture object (constant vptr, reads object+0xE0) [V live + dis], not a 32-byte TexturePtr [V file read]. xref.py callers 0xe8143c0 EMPTY; texload/texload_task EMPTY; 0x18718d0 cache path (vtable 0xEFCA680) never calls sub_4e05e50/sub_12893d0 [V prior].

## CLOSES?

NO — blocking fact: no [V]-proven static path texgroup_load(0x5421c90) -> sub_4e05e50. sub_4e05e50 has 0 static xrefs and is reached only via sub_12893d0's indirect vtable[1] tail-call `0x1289490  call qword ptr [0xF99FFA0]` (capture ret site `0x1289496  nop` [V live]); `[0xF99FFA0]` = sub_eea6040 trampoline (`jmp rax`), never written (.rdata read-only), NOT sub_4e05e50 [V r26-r29]; texgroup_load's `[0xF99FFA0]` calls are global-allocator `allocate(size=edx)` via `[0x1233E1A8]` vtable+8 [V Table 4], not sub_4e05e50; texgroup_load's static chain ends at `0x54227AF call 0x18718D0` (cache 0x18718d0, vtable 0xEFCA680 objects) [V]; sub_12893d0's static callers all dead-end [V]; sub_4e05450 (constructor setting vptr=0xF215838 at `0x4E05654  mov [rbx],r8`) has 16 static callers, none is texgroup_load [V]. Everything else in the item IS [V]-proven: sampler flag decode + cache (6ax), D3D12 backend texture-management chain, command-byte-14 producer sub_bc73770 [V r4], dispatcher [vptr+0xD0]->createTexture 0xe8143c0 [V live + dis], returned handle stored at [texture_obj+0x00] (`0xC296E26  mov [rdi],ax`, size 2) [V] with texture_obj = TexturePtr+0x58 [V], TexturePtr/ClientTexture sdk headers [V file read]. Atlas stitchers (L8a/L8b) remain out of scope (MIRROR_SKIP).

## TOOL REQUESTS

- None. Static analysis is exhausted: [0xF99FFA0] and [0x1233E1A8] resolved (no writer, read-only trampoline/allocator), sub_4e05e50 (0 xrefs), sub_12893d0 (4 callers, all dead-end), sub_4e05450 (16 callers, none is texgroup_load), texgroup_load (static chain ends at cache 0x18718d0). All instruction lines re-verified verbatim against rdis; live capture logs are read-only inputs; xref.py/rdis callers/fn/vt/imm/ripscan.py used for positive and negative findings. No helper scripts written; no temporary files left behind.
