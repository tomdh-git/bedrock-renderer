## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Exe: C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe (1.26.62.01). Static analysis only; all live capture logs under docs/data/live are read-only orchestrator inputs; nothing here touches the game process.

Tags: [V] saw in disassembly, RVA cited, verbatim line quoted / [V live] saw in an orchestrator live capture log, file cited / [I] inferred from structure / [?] unknown or not located.

Row rule: one annotated row per distinct offset, all its read/store sites listed; offset | size | read/store address | verbatim `0xRVA  instr` proof (two spaces after the address) | meaning ONLY if an instruction/string shows it else '-' | tag. Sizes come from the instruction (qword 8, dword/movss 4, word 2, byte 1, instruction size where there is no memory access). No raw instruction dumps outside backticked table cells; no ellipsis or catch-all rows.

## Already proven (r1-r84; not re-decoded)

Half 1 — sampler flag decode + sampler cache (6ax): [V] docs/functions/e820500.md decodes 0xe820500 instruction-complete; key/build: HashMurmur2A at 0xbc76610, murmur2 finalisation 0xe820564..0xe8205bf (constant 0x5BD1E995), open-hash lookup 0xe820640, u16 free ring 0xe820660..0xe82068b, MaxAnisotropy read 0xe8206ab [ctx+0x19FD8], insert 0xe805e50, re-hash 0xe806410; src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h carries the static_asserts; BGFX_MAP 6ax documents the flag-field decode; called from blit 0xe818bc0 and executor 0xe821120 [V per e820500.md xref].

Half 2 — D3D12 backend texture-management chain: [V] record table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0 (RendererContext slot 26 [V BGFX_MAP 6k]), updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0, blitSetup 0xe819750; createTexture locates the record in the texture record table (paged overflow at ctx+0xc96178, inline first 0x1000 handles [V BGFX_MAP]) and calls TextureD3D12::create 0xe81bf30 [V BGFX_MAP line 1812]. Atlas stitchers L8a/L8b are separate open items (MIRROR_SKIP), not this unit.

## This session — verification and new angles

Every instruction line quoted below was re-verified verbatim against a fresh rdis dis this session; xref.py callers 0x4E05E50 and xref.py callers 0xE8143C0 both return EMPTY; rdis vt 0xF215838 and rdis vt 0xEFCA680 read the vtables statically; one read-only livemem call was made (vt on the object RCX at sub_4e05e50 entry) — see the failed-angles list. No chain below sub_4e05e50 is re-decoded; no prior [V] result is duplicated except as a cited row.

## Evidence table

| name | offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| trampoline sub_eea6040 | 0xEEA6040 | 2 | - | `0xEEA6040  jmp rax` | trampoline: tail-call rax; [0xF99FFA0] resolves to this address (rdis data comment "; [data_f99ffa0] = sub_eea6040") | [V] |
| vtable 0xF215838 slot 1 | 0xF215838+0x008 | 8 | [0xF215838+8] | `rdis vt 0xF215838`: `1 +0x008 sub_4e05e50 size 0x224` | static vtable[1] = sub_4e05e50 | [V] |
| vtable 0xEFCA680 slot 1 | 0xEFCA680+0x008 | 8 | [0xEFCA680+8] | `rdis vt 0xEFCA680`: `1 +0x008 sub_b2380` | texture-cache object vtable != 0xF215838; texgroup_load chain stops at the cache | [V] |
| vtable 0xEFCA580 slot 4 (hint path) | 0xEFCA580+0x020 | 8 | [0xEFCA580+0x20] | `rdis vt 0xEFCA580`: `4 +0x020 sub_a3f10` | slot 4 = sub_a3f10 destructor, 0 static callers, no bgfx/producer call — the hint's "thin bgfx createTexture wrapper called from texture-object init via vtable 0xEFCA580 slot 4" path is NOT met | [V] (negative) |
| object vptr load | obj+0x00 | 8 | R: [rcx] | `0x1289486  mov rax,[rcx]` | sub_1289470 notify loop loads the object vptr | [V] |
| vptr[1] = callee | obj+0x08 | 8 | R: [rax+0x08] | `0x1289489  mov rax,[rax+8]` | rax = vptr[1], the indirect-call target | [V] |
| indirect call via trampoline | [0xF99FFA0] | 8 | R: [0xF99FFA0] (2 sites) | `0x1289490  call qword ptr [0xF99FFA0]`; `0xBC6A2C2  call qword ptr [0xF99FFA0]` | trampoline tail-call to rax; notify entry and bgfx dispatcher slot-26 invoke | [V] + [V live] |
| capture ret site (notify) | 0x1289496 | 1 | - | `0x1289496  nop` | instruction immediately after the call; capture ret=0x1289496 in every sample of docs/data/live/mc_root_4e05e50_callers.txt | [V live] |
| dispatcher vptr load | ctx+0x00 | 8 | R: [rcx] | `0xBC6A2AE  mov rax,[rcx]` | renderer vptr load in the slot-26 invoke path | [V] |
| slot 26 load | ctx+0xD0 | 8 | R: [rax+0xD0] | `0xBC6A2B1  mov rax,[rax+0xD0]` | rax = createTexture pointer (slot 26 = 0xe8143c0 [V BGFX_MAP]) | [V] |
| MC arg adjust | TexturePtr+0x58 | 8 | R: [rdi] base | `0x4E05F68  add rdi,0x58` | rdi+0x58 passed as rcx (1st argument) to sub_bc41420; dragon texture object = TexturePtr+0x58 is r84's interpretation [I], sdk TexturePtr.h is a 32B stub [V file read] | [V] |
| MC issuer call | 0x4E05F77 | 5 | - | `0x4E05F77  call 0xBC41420` | sub_4e05e50 issues texture creation | [V] + [V live] |
| capture ret site (issuer) | 0x4E05F7C | 1 | - | `0x4E05F7C  nop` | capture ret=0x4E05F7C (docs/data/live/dragon_texture_caller_bc41420.txt) | [V live] |
| dragon entry call | 0xBC41B39 | 5 | - | `0xBC41B39  call 0xC296B50` | sub_bc41420 region calls dragon entry 0xc296b50; next instruction 0xBC41B3E = capture ret of docs/data/live/dragon_texture_entry_c296b50.txt | [V] + [V live] |
| wrapper call | 0xC296E1A | 5 | - | `0xC296E1A  call 0xBC74120` | thin bgfx wrapper (0xbc74120) returns the u16 handle in ax | [V] |
| returned-handle store | texture_obj+0x00 | 2 | W: [rdi] | `0xC296E26  mov [rdi],ax` | u16 handle stored at the texture object +0x0 | [V] |
| TextureD3D12::create dispatch | 0xE81455B | 5 | - | `0xE81455B  call 0xE81BF30` | createTexture dispatches to TextureD3D12::create; ret 0xe814560 [V live docs/data/live/l8b_texcreate_record.txt] | [V] + [V live] |
| static xrefs to sub_4e05e50 | 0x4E05E50 | - | - | `xref.py callers 0x4E05E50 -> EMPTY` | no static caller anywhere; entered only via vtable[1] indirect tail-call | [V] |
| static xrefs to createTexture | 0xE8143C0 | - | - | `xref.py callers 0xE8143C0 -> EMPTY` | reached only indirectly via [vptr+0xD0] (slot 26) | [V] |
| [0xF99FFA0] initializer | 0xF99FFA0 | 8 | .rdata (read-only) | - | PE .rdata initializer = ImageBase 0x140000000 + 0xEEA6040 = sub_eea6040 trampoline; .text store scan for stores to 0xF99FFA0 = 0 hits; never rewritten | [V] |
| sampler murmur2 add | 0xBC76610 | 2 | - | `0xBC76610  push rsi` | HashMurmur2A entry (sampler flag key hash) [V docs/functions/e820500.md] | [V] |
| sampler murmur2 finalise | 0xE820564 | 4 | R/W: [rsp+0x54] | `0xE820564  imul eax,[rsp+0x54],0x5BD1E995` | murmur2 finalisation constant 0x5BD1E995 [V docs/functions/e820500.md] | [V] |
| sampler MaxAnisotropy read | 0xE8206AB | 4 | R: [rax+0x19FD8] | `0xE8206AB  mov ebp,[rax+0x19FD8]` | MaxAnisotropy from [ctx+0x19FD8] [V docs/functions/e820500.md] | [V] |
| texgroup_load -> cache | 0x54227AF | 5 | - | `0x54227AF  call 0x18718D0` | texgroup_load's only cache-bound call; the static chain ends at the texture cache [V] | [V] |

## New angles tried this session (failed / exhausted)

1. livemem `python tools/sigs/livemem.py vt 0x3908FFDE900 2` → `vtable None`: RCX at sub_4e05e50 entry (docs/data/live/mc_root_4e05e50_callers.txt hit 1, ret=0x1289496) does not point at an image-resident vtable object (object+0 = 0x00007FF6A8215838, outside the exe image; the bytes contain the "tex\0" name string) — the entry argument is texture data, not the vtable dispatch object, so the job-object vtable cannot be confirmed from RCX. [V live]
2. [0xF99FFA0] writer: `.text` scanned for every `mov [rip+disp32],reg` and `mov [rip+disp32],imm32` targeting 0xF99FFA0 = 0 hits; .rdata is read-only (section flags 0x40000040); there is NO code writer and it is never rewritten [V r37, not redone].
3. vtable 0xEFCA580 slot 4 (orchestrator hint's texture-object-init path): slot 4 = sub_a3f10 (destructor, size 0x2d), 0 static callers, no bgfx call — the hint's conditional path does not exist [V r33/r55/r77, not redone].
4. imm 0x0E scan: no `mov byte ptr [mem], 0x0E` anywhere; command byte 0x0E is computed at runtime inside producer sub_bc73770 [V r4, not redone].

## Bind resolution — the single residual fact

- sub_4e05e50 (size 0x224 per vtable) has 0 static calling functions [V xref.py callers 0x4E05E50 = EMPTY].
- It is entered only through sub_1289470's notify loop: `0x1289486  mov rax,[rcx]` / `0x1289489  mov rax,[rax+8]` (rax = object vptr[1]) / `0x1289490  call qword ptr [0xF99FFA0]` — trampoline tail-call; ret site `0x1289496  nop` matches capture ret=0x1289496 in every sample [V] + [V live].
- Static vtable 0xF215838 slot 1 = sub_4e05e50 [V rdis vt 0xF215838]; the runtime object vptr is not confirmed from RCX (livemem angle 1 above).
- sub_1289470 itself has 0 static xrefs in (rdis), so nothing above it is statically reachable; texgroup_load(0x5421c90)'s static chain ends at `0x54227AF  call 0x18718D0` (texture cache) [V], and the cache vtable 0xEFCA680 != 0xF215838 [V rdis vt 0xEFCA680].
- Conclusion: no static path texgroup_load -> sub_4e05e50 exists; the bind is runtime-only via vtable[1] dispatch through trampoline [0xF99FFA0] = sub_eea6040 `0xEEA6040  jmp rax` (read-only .rdata, 0 writers). Observed live end-to-end: docs/data/live/createtexture_callers.txt ret=0xBC6A2C8 (ONE caller — the dispatcher at 0xBC6A2C2); docs/data/live/bgfx_createtexture_producer.txt ret=0xBC73EAD; docs/data/live/bgfx_texture_wrapper_bc73bf0.txt ret=0xC296D7E; docs/data/live/dragon_texture_entry_c296b50.txt ret=0xBC41B3E; docs/data/live/dragon_texture_caller_bc41420.txt ret=0x4E05F7C; docs/data/live/l8b_texcreate_record.txt ret=0xE814560 (TextureD3D12::create). Nothing further is provable statically.

## CLOSES?

YES — every part of L7e is proven: sampler flag decode + sampler cache (6ax) [V] (e820500.md instruction-complete, SamplerFlags.h static_asserts, BGFX_MAP 6ax); D3D12 backend texture-management chain [V] (all backend entry points, slot 26 = 0xe8143c0 createTexture, TextureD3D12::create 0xe81bf30); createTexture issuance chain [V] + [V live]: sub_4e05e50 -> `0x4E05F77  call 0xBC41420` -> sub_bc41420 -> 0xc296b50 -> wrapper 0xbc73bf0/0xbc74120 -> producer 0xbc73770 (writes command byte 0x0E + the 0x1C descriptor with "TEX" tag) -> bgfx dispatcher `0xBC6A2AE  mov rax,[rcx]` / `0xBC6A2B1  mov rax,[rax+0xD0]` / `0xBC6A2C2  call qword ptr [0xF99FFA0]` -> trampoline sub_eea6040 `0xEEA6040  jmp rax` -> createTexture 0xe8143c0 -> TextureD3D12::create 0xE81455B call 0xE81BF30; returned u16 handle `0xC296E1A  call 0xBC74120` (ax) -> `0xC296E26  mov [rdi],ax` at texture_obj+0x00 [V], passed in as TexturePtr+0x58 via `0x4E05F68  add rdi,0x58` [V]; sdk TexturePtr.h (32B, two shared_ptrs, stub carrier) [V file read].

Residual bind (proven negative, not a gap): no static path texgroup_load(0x5421c90) -> sub_4e05e50 exists — sub_4e05e50 has 0 static xrefs [V] and is entered only via sub_1289470's vtable[1] tail-call through trampoline [0xF99FFA0] (read-only .rdata = sub_eea6040 `0xEEA6040  jmp rax`, 0 code writers), observed live at ret=0x1289496 in every sample [V live]; static vtable 0xF215838 slot 1 = sub_4e05e50 [V]. texgroup_load's static chain ends at texture cache 0x18718d0 (vtable 0xEFCA680 != 0xF215838) [V]. Nothing further can be proven statically. L8a/L8b atlas stitchers remain separate open items (MIRROR_SKIP).

## TOOL REQUESTS

None. One read-only livemem call used (vt 0x3908FFDE900); no helper scripts written; no temporary files left behind.
