## NEXT
DONE — CLOSES? NO: no [V]-proven static path texgroup_load(0x5421c90) -> sub_4e05e50 (runtime-only deferred-txn job hop through sub_66232b0, vtable 0xF2BDF40 slot 0, zero static references); indirect target resolved [V]: vtable 0xF215838 slot[1] = sub_4e05e50. All other L7e parts [V]/[V live]-proven. See section 4.

UNIT U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"
Output file: docs/progress/oc_U-EL7e.md (only this file)
Source checklist line: docs/RENDER_CHECKLIST.md:338
Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; live capture logs under docs/data/live are read-only inputs produced by the orchestrator.
Tags: [V] saw in disassembly (RVA cited, verbatim `0xRVA  instr` quoted) / [V live] saw in an orchestrator live capture log (file cited) / [I] inferred / [?] unknown or not located.
Row rule: one annotated row per distinct offset, all its read/store sites listed; name | rva or offset | size | verbatim `0xRVA  instr` (two spaces after the address, copied verbatim from rdis) | meaning ONLY if an instruction/string shows it else '-' | tag. Sizes from the instruction (movups/movaps/movdqu/movdqa 16, qword 8, dword/movss 4, word 2, byte 1, call 5, jmp 2, nop/push 1). No input data pasted as-is; no skipped offsets; no raw instruction dumps outside tables.

================================================================================
1. ANSWER TABLE — pending work resolved this session (the indirect-call bind)
================================================================================

The pending part was the indirect createTexture issuance root: what `rax` holds
at the [0xF99FFA0] trampoline `jmp rax`, who creates the texture objects that
sub_12893d0 dispatches through vtable[1], and whether texgroup_load(0x5421c90)
reaches sub_4e05e50 statically. Every `0xRVA  instr` below was re-verified
verbatim against a fresh rdis disassembly of the 1.26.62.01 exe or cited from
the provided live capture logs. Half 1 (sampler flag decode + cache, 6ax) and
Half 2a (D3D12 backend texture-management chain) were closed in prior rounds
and are cited in section 2, not re-derived; atlas stitchers (L8a/L8b) are
separate open units (oc_U-EL8a/oc_U-EL8b), not this unit.

| name | rva or offset | size | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| trampoline entry | 0xEEA6040 | 2 | `0xEEA6040  jmp rax` | CFG indirect-call trampoline; tail-calls the function pointer currently held in rax | [V] |
| [0xF99FFA0] cell | [0xF99FFA0] | 8 | - | PE .rdata read-only initializer = sub_eea6040 (rdis data label [data_f99ffa0]); imm/ptr/xr scans for a writer = 0 hits; .rdata is read-only so the cell is never rewritten | [V] |
| [0xF99FFA0] indirect-call reads | [0xF99FFA0] | 8 | `0x1289490  call qword ptr [0xF99FFA0]` | sub_12893d0 tail-call through the trampoline; same cell read at 0x12894b3 (old-object release via vtable[0]), 0x4E05E86 (release this+0x18 via vtable[1]) and 0xBC6A2C2 (bgfx dispatcher slot-26 vcall -> createTexture) | [V] |
| vtable 0xF215838 slot[0] | 0xF215838 | 8 | `0x4E060BB  lea rax,[0xF215838]` | sub_4e060b0 (vtable slot 0, size 0x6c, `push rsi`) references its own vtable -> vtable base identity | [V] |
| vtable 0xF215838 slot[1] | 0xF215840 | 8 | `0x4E05E50  push rbp` | rdis `vt 0xF215838`: slot +0x008 = sub_4e05e50, size 0x224 (0x4E05E50..0x4E06074, entry `push rbp`) => entry[+0x10]->vtable[1] is STATICALLY sub_4e05e50, i.e. rax at the [0xF99FFA0] trampoline jmp resolves to sub_4e05e50 for any object with vptr 0xF215838 | [V] |
| vtable 0xF215838 slot[2] | 0xF215848 | 8 | - | non-code 0x0 (rdis `vt`) | - | [V] |
| ClientTexture ctor entry | 0x4E05450 | 1 | `0x4E05450  push rbp` | sub_4e05450 (0x4E05450..0x4E05843, size 0x3f3, 17 xrefs in); allocates a 0x30-byte control block and a 0xE8-byte texture object via [0xF99FFA0] | [V] |
| control-block alloc | 0x4E054E1 | 4 | `0x4E054E1  mov edx,0x30` | 0x30-byte control block allocated via `0x4E054E6  call qword ptr [0xF99FFA0]` | [V] |
| control-block vptr | 0x4E05507 | 8 | `0x4E05507  lea rax,[0xF215850]` | control-block vptr = 0xF215850 (slot 0 = sub_4e05de0 dtor), stored by `0x4E0550E  mov [rbx],rax` | [V] |
| texture-object alloc | 0x4E0561D | 4 | `0x4E0561D  mov edx,0xE8` | 0xE8-byte texture object allocated via `0x4E05622  call qword ptr [0xF99FFA0]` | [V] |
| vptr load | 0x4E0564D | 8 | `0x4E0564D  lea r8,[0xF215838]` | vtable 0xF215838 address loaded into r8 | [V] |
| vptr store | 0x4E05654 | 8 | `0x4E05654  mov [rbx],r8` | texture object vptr = 0xF215838 -> vtable[1] = sub_4e05e50; this object is sub_4e05e50's `this` | [V] |
| descriptor store | 0x4E05689 | 16 | `0x4E05689  movups [rbx+0x58],xmm1` | creation descriptor stored at texture_obj+0x58 (matches sub_4e05e50 `0x4E05F68 add rdi,0x58`) | [V] |
| flags store | 0x4E0573A | 8 | `0x4E0573A  mov [rbx+0xE0],rax` | sampler/flags word stored at texture_obj+0xE0 (matches sub_4e05e50 `0x4E05F61 mov r9,[rdi+0xE0]`) | [V] |
| deferred-txn root entry | 0x66232B0 | 1 | `0x66232B0  push rbp` | sub_66232b0 (size 0xb3d0 per rdis `vt`) = vtable 0xF2BDF40 slot 0 (deferred-texture-transaction job run slot) | [V] |
| root creates texture objects | 0x662405C | 5 | `0x662405C  call 0x4E05450` | sub_66232b0 creates ClientTexture objects via sub_4e05450 (2 sites: 0x662405C and 0x6624221; rdis `xr 0x4E05450` lists all 17 sites) | [V] |
| root drains entry queue | 0x66233AE | 5 | `0x66233AE  call 0x6632BF0` | sub_66232b0 -> sub_6632bf0 -> sub_12893d0; rdis `callers 0x6632bf0` = sub_66232b0 only (1 function, 2 call sites) | [V] |
| drain dispatch | 0x6632C55 | 5 | `0x6632C55  call 0x12893D0` | sub_6632bf0 -> sub_12893d0 (entry-array drain; static callers of sub_12893d0 also: sub_6622610 at 0x6622662, sub_1145c20 at 0x1145D5A/0x1145EE5) | [V] |
| static entry to root | [0xF2BDF40] | - | - | rdis `callers 0x66232b0` = 0; `imm 0xF2BDF40` = 0 hits; `ptr 0xF2BDF40` = 0 pointers; `xr 0xF2BDF40` = 0 xrefs -> sub_66232b0 is entered ONLY by runtime job-system virtual dispatch of vtable 0xF2BDF40 slot 0; no static store of its vptr exists | [V] |
| sub_4e05e50 static callers | 0x4E05E50 | - | - | rdis `callers 0x4E05E50` = 0 calling functions; reached only via sub_12893d0's indirect vtable[1] tail-call through [0xF99FFA0] | [V] |
| createTexture static callers | 0xE8143C0 | - | - | rdis `callers 0xe8143c0` = 0 calling functions; reached only via bgfx dispatcher slot-26 vtable[0xD0] vcall | [V] |

================================================================================
2. CHAIN SUMMARY (cited from prior rounds, not re-derived)
================================================================================

Resolved this session (section 1, all [V]):
- Indirect-call target resolved: vtable 0xF215838 slot[1] = sub_4e05e50 [V], so rax at the [0xF99FFA0] trampoline `jmp rax` (`0xEEA6040  jmp rax`) = sub_4e05e50 for vptr-0xF215838 objects [V]; confirmed live by mc_root_4e05e50_callers.txt: all 15/32 hits ret=0x1289496 (the fall-through of `0x1289490  call qword ptr [0xF99FFA0]`) and RCX vptr bytes `385821A8F67F0000` = 0x00007FF6A8215838 = runtime base 0x7FF699000000 + RVA 0xF215838 [I], with name fields "tex"/"legs"/"_spear"/"hud"/"mary" in the RCX heap dump = TexturePtr::mClientTexture pointee [V live].
- sub_4e05450 is the ClientTexture constructor: vptr = 0xF215838 (`0x4E0564D  lea r8,[0xF215838]` / `0x4E05654  mov [rbx],r8` [V]), descriptor at texture_obj+0x58 (`0x4E05689  movups [rbx+0x58],xmm1` [V]), sampler/flags at texture_obj+0xE0 (`0x4E0573A  mov [rbx+0xE0],rax` [V]) — exactly the layout sub_4e05e50 consumes.
- sub_66232b0 (deferred-txn job root, vtable 0xF2BDF40 slot 0, `0x66232B0  push rbp` [V]) both creates these objects (`0x662405C  call 0x4E05450`, `0x6624221  call 0x4E05450` [V]) and drains them (`0x66233AE  call 0x6632BF0` [V] -> `0x6632C55  call 0x12893D0` [V] -> sub_12893d0 -> `0x1289490  call qword ptr [0xF99FFA0]` tail-call, fall-through `0x1289496  nop` [V]).
- So the full issuance path is: sub_4e05450-created ClientTexture (vtable[1] = sub_4e05e50) -> sub_12893d0 vtable[1] dispatch -> sub_4e05e50 (`0x4E05E6E  mov rdi,rcx` [V]; old release at `0x4E05E71  mov rax,[rcx+0x18]` / `0x4E05E86  call qword ptr [0xF99FFA0]` [V]; sampler flags `0x4E05F61  mov r9,[rdi+0xE0]` [V]; descriptor `0x4E05F68  add rdi,0x58` [V]; `0x4E05F77  call 0xBC41420`, call end `0x4E05F7C  nop` = LIVE RESULT 5 ret [V live]; skip path `0x4E06010  mov qword ptr [rsi],0` [V]) -> sub_bc41420 (`0xBC41B39  call 0xC296B50` [V]) -> dragon entry 0xc296b50 -> wrapper 0xbc73bf0 -> producer sub_bc73770 (writes bgfx command byte 0x0E) -> bgfx dispatcher (`0xBC6A28F  mov rcx,[rdi+0x1EBF2D0]` / `0xBC6A2AE  mov rax,[rcx]` / `0xBC6A2B1  mov rax,[rax+0xD0]` = vptr[slot 26] = createTexture 0xe8143c0 [V]; `0xBC6A2C2  call qword ptr [0xF99FFA0]` -> createTexture; createtexture_callers.txt ONE caller ret=0xBC6A2C8 [V live]) -> createTexture 0xe8143c0 (`0xE8143C0  push rbp` [V]; no static caller [V]) -> `0xE81455B  call 0xE81BF30` TextureD3D12::create [V]; backend ret site `0xE814560  nop` = l8b_texcreate_record.txt CALLER ret=0xE814560 [V live].
- Handle trace into texture object / TexturePtr: returned u16 handle `0xC296E1A  call 0xBC74120` (ax) -> `0xC296E26  mov [rdi],ax` at [texture_obj+0x00] [V]; descriptor copied `0xC296E2D  movups xmm0,[r12]` / `0xC296E32  movups [rdi+8],xmm0` / ptr `0xC296E3B  mov [rdi+0x18],rdx` [V]; texture_obj = TexturePtr+0x58 (`0x4E05F68  add rdi,0x58` [V]); sdk TexturePtr/ClientTexture headers read from src tree [V file read].

Already proven in prior rounds (cited, not re-derived):
- sampler flag decode + sampler cache (6ax): docs/functions/e820500.md + src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h [V].
- D3D12 backend texture-management chain: record table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0 (slot 26), updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0 / blitSetup 0xe819750 [V].
- texgroup_load(0x5421c90) static graph: calls sub_eec6ec0/sub_eec6eb0, sub_5477a30, sub_5475a30, `0x54227af  call 0x18718D0`, sub_e935700, sub_5424000, sub_5424130; those terminate at texture-cache/ResourceLoadManager indirect dispatch cells (0xF9A8xxx range, e.g. [0xF9A8C78]) and async enqueue 0x71BC70 — none enters sub_4e05450/sub_66232b0/sub_4e05e50 [V].
- Atlas stitchers (L8a/L8b) remain separate open units (oc_U-EL8a/oc_U-EL8b); mip/compression builders are out of scope.

================================================================================
3. ANGLES TRIED THIS SESSION (new angle: static vtable bind; blocker re-confirmed)
================================================================================

NEW ANGLE — vtable bind (partially successful, resolves the indirect target):
- rdis `vt 0xF215838`: slot[0]=sub_4e060b0, slot[1]=sub_4e05e50 (size 0x224), slot[2]=non-code 0x0 -> sub_4e05e50 IS statically vtable[1] of vtable 0xF215838 [V].
- sub_4e05450 (ClientTexture ctor, 17 xrefs in) stores vptr = 0xF215838 to created texture objects (`0x4E0564D  lea r8,[0xF215838]` / `0x4E05654  mov [rbx],r8` [V]) with descriptor at +0x58 and flags at +0xE0, matching sub_4e05e50's reads [V].
- sub_66232b0 creates these objects (`0x662405C`/`0x6624221  call 0x4E05450` [V]) and drains them via sub_6632bf0 -> sub_12893d0 -> vtable[1] [V].
- Result: the indirect call target (what rax holds at the trampoline jmp) is now resolved STATICALLY, not just live.

STILL BLOCKED — static edge texgroup_load -> sub_66232b0 does not exist:
- sub_66232b0 (deferred-txn job root, vtable 0xF2BDF40 slot 0): `callers 0x66232b0` = 0; `imm 0xF2BDF40` = 0 hits; `ptr 0xF2BDF40` = 0 pointers; `xr 0xF2BDF40` = 0 xrefs -> entered ONLY by runtime job-system virtual dispatch [V negative evidence].
- texgroup_load -> 0x18718D0 -> ResourceLoadManager async enqueue 0x71BC70 ("resource dispatch") is the last static hop; the hop into sub_66232b0 is runtime-only (job system), so no [V]-proven static path texgroup_load(0x5421c90) -> sub_4e05e50 exists. The bind IS live-proven (mc_root_4e05e50_callers.txt, all hits ret=0x1289496) but not static.

FAILED ANGLES FROM PRIOR ROUNDS (do not redo):
- command-byte-0x0E producer search: no `mov byte ptr [mem],0x0E` anywhere (`imm 0x0E`); all command-buffer writers hardcode other opcodes (0x00/0x07/0x0A/0x0B/0x12/0x14/0x27); dispatch table obfuscated [V negative].
- [0xF99FFA0] code-writer search: 0 hits; read-only .rdata initializer holding sub_eea6040, never rewritten.
- xref.py callers 0x4E05E50 / 0xe8143c0 / 0x5421C90: all EMPTY; none enters sub_4e05e50.
- rdis immediate scan for vtable 0xF215838 (32-bit) = 0 hits (superseded: the real static store is the RIP-relative `lea r8,[0xF215838]` at 0x4E0564D found this session).

================================================================================
4. CLOSES?
================================================================================

NO — single blocking fact: no [V]-proven static path texgroup_load(0x5421c90) -> sub_4e05e50. texgroup_load's static graph ends at the texture-cache/ResourceLoadManager async enqueue (0x71BC70); the hop into the GPU-upload root is the runtime-only deferred-texture-transaction job (sub_66232b0, vtable 0xF2BDF40 slot 0, zero static references) -> sub_6632bf0 -> sub_12893d0 -> indirect vtable[1] call through [0xF99FFA0] -> sub_4e05e50 -> createTexture. That runtime bind IS observed ([V live] mc_root_4e05e50_callers.txt, all hits ret=0x1289496; the indirect target is now also STATICALLY known: vtable 0xF215838 slot[1] = sub_4e05e50 [V]) but the static texgroup_load -> sub_66232b0 edge cannot be established by static analysis.
Everything else in L7e is [V]/[V live]-proven: Half 1 sampler flag decode + cache (6ax); Half 2a D3D12 backend texture-management chain; createTexture issuance below sub_4e05e50 (producer sub_bc73770 writes bgfx cmd byte 0x0E -> dispatcher slot 26 -> createTexture 0xe8143c0 -> TextureD3D12::create 0xe81bf30); handle trace into texture object +0x00 / TexturePtr (TexturePtr+0x58); sdk TexturePtr/ClientTexture headers. Atlas stitchers (L8a/L8b) are separate open units, not this unit.

================================================================================
5. TOOL REQUESTS
================================================================================

None — all instruction lines taken verbatim from fresh rdis disassembly of the
1.26.62.01 exe (vt/imm/ptr/xr/callers/dis/fn), verified with
tools/sigs/verify_oc.py; live captures read from docs/data/live/*.txt; no helper
scripts written, no temporary files left behind.

## NEXT
step 2
