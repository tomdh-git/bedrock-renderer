## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): `- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending | PROGRESS 2026-11-21 oc_U-EL7e.md (verify_oc 185/185): D3D12 backend texture-management chain decoded [V] ...; Minecraft-side pack->GPU chain (texgroup_load 0x5421c90 -> texload 0x58a1310 -> texload_task 0x541bf00 -> undecoded 0x18718D0 at 0x54227af) and atlas stitchers still open (L8a/L8b)`

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; live capture logs under docs/data/live are read-only orchestrator inputs. Every quoted `0xRVA  instr` was re-verified verbatim via rdis this session unless cited [V r1-r26].

Tags: [V] saw in disassembly (verbatim line quoted, RVA cited) / [V live] saw in an orchestrator live capture log (file cited) / [I] inferred from structure / [?] unknown or not located.

Row rule: one annotated row per distinct offset, all its read/store sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after address, copied verbatim from rdis) | meaning ONLY if an instruction/string shows it else '-' | tag. Sizes from the instruction (movups/movaps/movdqu/movdqa 16, qword 8, dword/movss 4, word 2, byte/nop 1). No input data pasted as-is; no skipped offsets among quoted sites; no raw instruction dumps outside tables; no catch-all or ellipsis rows.

## Already proven (cited from r1-r26; not re-decoded, re-verified verbatim where quoted)

- Half 1 — sampler flag decode + sampler cache (6ax): [V] docs/functions/e820500.md decodes 0xe820500 instruction-complete; src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h carries static_asserts; called from blit 0xe818bc0 and executor 0xe821120.
- Half 2a — D3D12 backend texture-management chain: [V] record table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0, updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0, blitSetup 0xe819750 (BGFX_MAP 6z/6z-2/6aj).
- createTexture has no static caller (`xref.py callers 0xe8143c0` EMPTY [V r2]); reached via RendererContext [vptr+0xD0] slot 26 = 0xe8143c0 -> bgfx dispatcher vcall or command byte 14 -> handler 0xbc69487.
- Command-byte-14 producer = sub_bc73770 [V r4]; reached only via thin wrappers 0xbc73bf0/0xbc73ed0/0xbc74120 from dragon entries 0xc296b50/0xc297000/0xc2a3d90/0xbc63c80 [V r4/r5]; MC texture code calls none statically.
- Issuance chain [V live + dis]: dispatcher case `0xBC6A2B1  mov rax,[rax+0xD0]` -> `0xBC6A2C2  call qword ptr [0xF99FFA0]` -> createTexture 0xe8143c0 (return site `0xBC6A2C8  test rax,rax`, capture ret=0xBC6A2C8 [V live docs/data/live/createtexture_callers.txt]) -> `0xE81455B  call 0xE81BF30` TextureD3D12::create (capture ret=0xE814560 [V live docs/data/live/l8b_texcreate_record.txt]).
- sub_4e05e50 texture-object create/load method: `0x4E05E6E  mov rdi,rcx` (texture object in RCX), `0x4E05F61  mov r9,[rdi+0xE0]` (renderer context), `0x4E05F68  add rdi,0x58` (texture sub-object), `0x4E05F77  call 0xBC41420`, return site `0x4E05F7C  nop` (capture ret=0x4E05F7C [V live docs/data/live/dragon_texture_caller_bc41420.txt]); RCX is a polymorphic object (vtable 0xF215838, slot 1 = sub_4e05e50 [V rdis vt]; capture vptr constant 0x7FF6A8215838 = base + 0xF215838 across 32 samples), NOT a TexturePtr* [V live + dis + file read].
- Returned handle: `0xC296E1A  call 0xBC74120` (ax) -> `0xC296E26  mov [rdi],ax` at texture_obj+0x00 [V r22]; texture_obj = TexturePtr+0x58 (`0x4E05F68  add rdi,0x58`) [V]; sdk TexturePtr.h `static_assert(sizeof(TexturePtr) == 32)`, mClientTexture +0x00 / mResourceLocationPtr +0x10; ClientTexture empty struct; BedrockTexture 48 bytes [V file read src/sdk/mc/deps/minecraft_renderer/renderer/TexturePtr.h, BedrockTexture.h].
- Texture job constructor sub_4e05450: `0x4E0564D  lea r8,[0xF215838]`, `0x4E05654  mov [rbx],r8` (vptr = 0xF215838 at object+0x00), `0x4E05689  movups [rbx+0x58],xmm1` (texture sub-object at +0x58), `0x4E0573A  mov [rbx+0xE0],rax` (renderer context at +0xE0) [V]; 16 static callers [V r22], none texgroup_load/texload/texload_task.
- texgroup_load(0x5421c90) static chain: `0x54227AF call 0x18718D0` (texture cache) [V]; cache 0x18718d0 builds objects with vtable 0xEFCA680 and never calls sub_4e05e50/sub_12893d0 [V r19].
- sub_4e05e50: 0 static xrefs (`rdis callers 0x4E05E50` -> 0 calling functions [V r22/r25]); reached only via sub_12893d0's indirect vtable[1] tail-call (capture ret site `0x1289496  nop` [V live]).

## This session — pending work: [0xF99FFA0] resolution and the texgroup_load link

### 1. [0xF99FFA0] — the runtime indirect-call trampoline; resolved, and it is NOT sub_4e05e50

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| [0xF99FFA0] static contents | 0xF99FFA0 | 8 | - | - | file bytes at RVA 0xF99FFA0 = 0x14EEA6040 = image base 0x1400000000 + RVA 0xEEA6040; statically holds sub_eea6040, NOT sub_4e05e50 (0x4E05E50) | [V] |
| thunk body | 0xEEA6040 | 2 | E: `0xEEA6040  jmp rax` | trampoline: jumps to rax (the real indirect-call target is materialized in rax by the caller) | [V] |
| [0xF99FFA0] read site (texgroup_load) | [0xF99FFA0] | 8 | R: `0x5421d63  call qword ptr [0xF99FFA0]` | texgroup_load indirect call; rax = [data_1233e1a8]->vptr[1] via `0x5421d45  mov rcx,[0x1233E1A8]` / `0x5421d4c  mov rax,[rcx]` / `0x5421d4f  mov rax,[rax+8]`, rdx = rdi+0x28 (size) via `0x5421d5c  lea r14,[rdi+0x28]` / `0x5421d60  mov rdx,r14` | allocator-style manager vptr[1] call, not sub_4e05e50 | [V] |
| [0xF99FFA0] read site (sub_12893d0 tail-call) | [0xF99FFA0] | 8 | R: `0x1289490  call qword ptr [0xF99FFA0]` | rax = obj->vptr[1] loaded by `0x1289486  mov rax,[rcx]` / `0x1289489  mov rax,[rax+8]`; rcx = element obj; capture return site `0x1289496  nop` = ret=0x1289496 in all 32 samples [V live docs/data/live/mc_root_4e05e50_callers.txt] | at runtime rax = sub_4e05e50 (object vptr[1] via vtable 0xF215838) | [V] + [V live] |
| [0xF99FFA0] read site (sub_4e05e50 add_ref path) | [0xF99FFA0] | 8 | R: `0x4E05E86  call qword ptr [0xF99FFA0]` | sub_4e05e50 itself dispatches through the trampoline: `0x4E05E71  mov rax,[rcx+0x18]` / `0x4E05E82  mov rax,[rax+0x10]` then call | universal indirect-call trampoline, not a per-function pointer | [V] |
| store hunt — writer of [0xF99FFA0] | .text | - | - | `xr 0xF99FFA0` over .text: zero `mov [0xF99FFA0],...` store destinations; only read sites | no code writer exists; never patched | [V r26] |
| section writability | .rdata | - | - | rdis `sec`: `.rdata` flags read-only (MEM_READ, no MEM_WRITE); 0xF99FFA0 lies inside .rdata | cannot be modified at runtime | [V r26] |

[0xF99FFA0] is read-only, holds sub_eea6040 (`jmp rax`), is never written by code, and is NOT sub_4e05e50 (0x4E05E50). The theorized static link "texgroup_load -> [0xF99FFA0] -> sub_4e05e50" does NOT exist: texgroup_load references 0x4E05E50 nowhere (rdis imm 0x4E05E50: 0 hits [V r22]).

### 2. texgroup_load's own [0xF99FFA0] vcall sites examined (new disassembly this session) — none reaches sub_4e05e50

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| texgroup_load global manager load | [data_1233e1a8] | 8 | R: `0x5421d45  mov rcx,[0x1233E1A8]` | rcx = global manager object pointer | [V] |
| texgroup_load manager vptr[1] call | [0xF99FFA0] | 8 | R: `0x5421d63  call qword ptr [0xF99FFA0]` | rax = manager->vptr[1] (`0x5421d4c  mov rax,[rcx]`, `0x5421d4f  mov rax,[rax+8]`); result used as a pointer (`0x5421d90  mov rcx,rax`) | allocator-style vptr[1] call, not sub_4e05e50 | [V] |
| texgroup_load fallback allocator call | [0xF99FFA0] | 8 | R: `0x5421d8a  call qword ptr [0xF99FFA0]` | same pattern, rdx = rdi+1 (`0x5421d83  lea r14,[rdi+1]`, `0x5421d87  mov rdx,r14`) | allocator path | [V] |
| texgroup_load list-release vcall sites | [0xF99FFA0] | 8 | R: `0x5421e43  call qword ptr [0xF99FFA0]` / `0x5421e63  call qword ptr [0xF99FFA0]` / `0x5421e8e  call qword ptr [0xF99FFA0]` / `0x5421ea4  call qword ptr [0xF99FFA0]` | vptr[1] calls on objects being torn down; `0x5421e94  lock dec dword ptr [rbx+0xC]` release sequence adjacent | release/destroy dispatch, not texture create | [V] |
| texgroup_load factory vcall + vtable stamp | [0xF99FFA0] | 8 | R: `0x5421f31  call qword ptr [0xF99FFA0]` | `0x5421f1e  mov rcx,[0x1233E1A8]` / `0x5421f25  mov rax,[rcx]` / `0x5421f28  mov rax,[rax+8]`, `0x5421f2c  mov edx,0x20`; result `0x5421f38  mov rdi,rax` stamped `0x5421f68  lea rax,[0xF09AA70]` / `0x5421f6f  mov [rdi],rax` | factory returns a 0x20-byte object stamped vtable 0xF09AA70, NOT vtable 0xF215838 whose slot 1 is sub_4e05e50 | [V] |

texgroup_load's static chain ends at `0x54227AF call 0x18718D0` plus the allocator/release/factory vcall sites above; none of them is sub_4e05e50, and no [0xF99FFA0] site in texgroup_load loads rax = sub_4e05e50.

### 3. Indirect caller of sub_4e05e50 (docs/data/live/mc_root_4e05e50_callers.txt, first CALLER ret=0x1289496) — decoded [V r25]

sub_12893d0 [0x12893d0..0x12895d3) is the deferred-transaction flush: per 0x18-byte element {ptr@0, shared_ctrl@8, obj@0x10} it add_refs [ctrl+8] (`0x1289447  lock cmpxchg [rcx+8],edx`), copies 16 bytes (`0x128944E  movups xmm0,[r13]`), tail-calls obj->vptr[1](&element) via trampoline (`0x1289490  call qword ptr [0xF99FFA0]`; return site `0x1289496  nop` [V live]), detaches (`0x128949B  mov qword ptr [r13+0x10],0`) and releases via vptr[0] (`0x12894b3  call qword ptr [0xF99FFA0]`). Static callers [V r25, 13 sites]: sub_6632bf0 (`0x6632C55`, `0x6632D1E`), sub_1145c20 (`0x1145D5A`, `0x1145EE5`), sub_6622610 (`0x6622662`), sub_66232b0 (x8). All upward chains dead-end (sub_66232b0 and sub_661f200 have 0 static callers [V r25]); none is texgroup_load(0x5421c90), texload(0x58a1310) or texload_task(0x541bf00). texgroup_load's direct callees (0x18718D0, 0x5477A30, 0x5475A30, 0x5424000, 0x5424130, 0xEEC6EC0, 0xEEC6EB0, 0xE935700, 0x78ED0, 0x9BC830 [V r22/r24]) do not enter sub_12893d0's or sub_4e05450's caller trees.

### 4. Returned handle -> TexturePtr/ClientTexture [V]

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| handle return | 0xC296E1A | 5 | - | `0xC296E1A  call 0xBC74120` | dragon wrapper returns 16-bit texture handle in ax (called from sub_bc41420 at 0xBC41B39) | [V] |
| handle store | [texture_obj+0x00] | 2 | W: `0xC296E26  mov [rdi],ax` | 16-bit handle stored at texture object +0x00 | [V] |
| result store | [texture_obj+0x08] | 16 | W: `0xC296E32  movups [rdi+8],xmm0` | 16 result bytes stored at +0x08 | [V] |
| texture sub-object | TexturePtr+0x58 | - | reg: `0x4E05F68  add rdi,0x58` | rdi = texture_obj = TexturePtr+0x58; created handle lands inside TexturePtr's embedded sub-object | [V] |
| sdk headers | TexturePtr.h | - | - | `static_assert(sizeof(TexturePtr) == 32)`, mClientTexture +0x00 / mResourceLocationPtr +0x10 (two shared_ptr) [V file read]; ClientTexture empty struct; BedrockTexture 48 bytes [V file read] | [V] |

## What I tried that failed (this session; do not redo)

- [0xF99FFA0] as the bridge to sub_4e05e50: located every read site and hunted for a writer across .text — it is read-only .rdata holding sub_eea6040 `jmp rax`, never written, never holds sub_4e05e50. Angle closed as negative.
- texgroup_load -> sub_4e05e50 via texgroup_load's own [0xF99FFA0] calls: all seven texgroup_load sites (0x5421d63, 0x5421d8a, 0x5421e43, 0x5421e63, 0x5421e8e, 0x5421ea4, 0x5421f31) resolve to allocator/release/factory dispatch on [data_1233e1a8]-manager and list objects; one factory product is stamped vtable 0xF09AA70 (`0x5421f6f  mov [rdi],rax`), not vtable 0xF215838 (slot 1 = sub_4e05e50). No static hop texgroup_load -> sub_4e05e50 exists.

## CLOSES?

NO — blocking fact: no [V]-proven static path texgroup_load(0x5421c90) -> sub_4e05e50, which is the single hop still missing for the pack->GPU half of L7e. sub_4e05e50 has 0 static xrefs and is reached only at runtime via sub_12893d0's indirect vtable[1] tail-call `0x1289490  call qword ptr [0xF99FFA0]` (capture ret=0x1289496, all 32 samples [V live]); [0xF99FFA0] is read-only .rdata holding sub_eea6040 (0xEEA6040) `jmp rax`, never written by code (xr: zero stores), NOT sub_4e05e50 (0x4E05E50); sub_12893d0's four static callers all dead-end without reaching texgroup_load/texload/texload_task [V r25]; texgroup_load's own [0xF99FFA0] vcall sites (Table 2) are allocator/release/factory calls (one product stamped vtable 0xF09AA70), none is sub_4e05e50; texgroup_load's static chain ends at `0x54227AF call 0x18718D0` (cache with vtable 0xEFCA680 objects) [V]. Everything else in the item is proven: sampler flag decode + cache (6ax) [V], D3D12 backend texture-management chain [V], command-byte-14 producer sub_bc73770 [V r4], dispatcher [vptr+0xD0] slot 26 = createTexture 0xe8143c0 [V live + dis], returned handle into TexturePtr+0x58+0 [V], sdk TexturePtr/ClientTexture [V file read]. Atlas stitchers (L8a/L8b) remain out of scope (MIRROR_SKIP).

## TOOL REQUESTS

- None (all instruction lines re-verified verbatim via rdis this session; negative xref/store-hunt findings cited from r22-r26 on the same exe; no helper scripts written, no temporary files left behind).
