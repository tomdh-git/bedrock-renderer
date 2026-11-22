## NEXT
DONE — CLOSES? NO: no [V]-proven static path texgroup_load(0x5421c90) -> sub_4e05e50 (runtime-only deferred-texture-transaction job through vtable 0xF2BDF40 slot 0 -> sub_6632bf0 -> sub_12893d0 -> indirect vtable[1] call through [0xF99FFA0]; target live-proven all ret=0x1289496 and statically vtable 0xF215838 slot[1] = sub_4e05e50 [V], but static texgroup_load -> sub_66232b0 edge not establishable). All other L7e parts [V]/[V live]-proven: Half 1 sampler flag decode + cache (6ax); Half 2a D3D12 backend texture-management chain; createTexture issuance below sub_4e05e50; handle trace into TexturePtr/ClientTexture; rax at trampoline jmp resolved. Atlas stitchers L8a/L8b are separate open units.

UNIT U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"
Output file: docs/progress/oc_U-EL7e.md (only this file)
Source checklist line: docs/RENDER_CHECKLIST.md:338
Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; live capture logs under docs/data/live are read-only inputs produced by the orchestrator.
Tags: [V] saw in disassembly (RVA cited, verbatim `0xRVA  instr` quoted) / [V live] saw in an orchestrator live capture log (file cited) / [I] inferred / [?] unknown or not located.
Row rule: one annotated row per distinct offset, all its read/store sites listed; name | rva or offset | size | verbatim `0xRVA  instr` (two spaces after the address, copied verbatim from rdis) | meaning ONLY if an instruction/string shows it else '-' | tag. Sizes from the instruction (movups/movaps/movdqu/movdqa 16, qword 8, dword/movss 4, word 2, byte 1, call 5, jmp 2, nop/push 1). No input data pasted as-is; no skipped offsets; no raw instruction dumps outside tables.

================================================================================
1. ANSWER TABLE — pending work resolved this session (indirect createTexture issuance root)
================================================================================

The pending part was the Minecraft-side texture->GPU root: who produces bgfx
command byte 0x0E, how the returned handle reaches the texture object /
TexturePtr::mClientTexture, what rax holds at the [0xF99FFA0] trampoline jmp,
and which object sub_4e05e50 consumes. Every `0xRVA  instr` below was
re-verified verbatim against a fresh rdis disassembly of the 1.26.62.01 exe
or cited from the provided live capture logs. Half 1 (sampler flag decode +
cache, 6ax: docs/functions/e820500.md + src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h)
and Half 2a (D3D12 backend texture-management chain) were closed in prior
rounds and are cited in section 2, not re-derived. Atlas stitchers (L8a/L8b)
are separate open units (oc_U-EL8a/oc_U-EL8b), not this unit.

| name | rva or offset | size | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| trampoline entry | 0xEEA6040 | 2 | `0xEEA6040  jmp rax` | CFG indirect-call trampoline; tail-calls the function pointer currently held in rax | [V] |
| [0xF99FFA0] cell initializer | 0xF99FFA0 | 8 | - | PE .rdata read-only initializer = sub_eea6040 (rdis data label [data_f99ffa0]); imm/ptr/xr scans for a writer = 0 hits; .rdata is read-only so the cell is never rewritten | [V] |
| [0xF99FFA0] indirect-call reads | 0x1289490, 0x12894b3, 0x4E05E86, 0xBC6A2C2 | 8 | `0x1289490  call qword ptr [0xF99FFA0]` | every indirect virtual call goes through this read-only cell; same cell also read at 0x12894b3 (old-object release via vtable[0]), 0x4E05E86 (release this+0x18 via vtable[1]) and 0xBC6A2C2 (bgfx dispatcher slot-26 vcall -> createTexture) | [V] |
| sub_12893d0 array begin | 0x1289406 | 8 | `0x1289406  mov r13,[rcx]` | [this+0] = entry-array begin loaded as walk cursor r13 (sub_12893d0 entry, 0x18-byte entries) | [V] |
| sub_12893d0 array end | 0x1289409 | 8 | `0x1289409  mov r14,[rcx+8]` | [this+8] = entry-array end (walk limit r14) | [V] |
| sub_12893d0 entry object load | 0x1289431 | 8 | `0x1289431  mov rcx,[r13+8]` | rcx = entry[+8] (refcounted texture entry object) | [V] |
| sub_12893d0 refcount inc | 0x1289447 | 4 | `0x1289447  lock cmpxchg [rcx+8],edx` | atomic refcount increment of entry[+8] object (retry loop at 0x1289440) | [V] |
| sub_12893d0 texture object load | 0x128947d | 8 | `0x128947d  mov rcx,[r13+0x10]` | entry[+0x10] = texture object loaded as `this` for the indirect call | [V] |
| sub_12893d0 vptr load | 0x1289486 | 8 | `0x1289486  mov rax,[rcx]` | rax = vptr of entry[+0x10] | [V] |
| sub_12893d0 vtable[1] load | 0x1289489 | 8 | `0x1289489  mov rax,[rax+8]` | rax = vtable[1] = indirect-call target held in rax at the trampoline jmp | [V] |
| sub_12893d0 indirect call | 0x1289490 | 5 | `0x1289490  call qword ptr [0xF99FFA0]` | tail-call through the trampoline; pushed ret = 0x1289496; mc_root_4e05e50_callers.txt line 3 `CALLER ret=0x1289496 first_hit=1`, every listed hit ret=0x1289496 => entry[+0x10]->vtable[1] = sub_4e05e50 at runtime | [V] [V live] |
| sub_12893d0 ret site | 0x1289496 | 1 | `0x1289496  nop` | instruction right after the indirect call = observed capture ret value | [V live] |
| sub_12893d0 NULL entry | 0x128949b | 8 | `0x128949b  mov qword ptr [r13+0x10],0` | NULLs entry[+0x10] after the call | [V] |
| sub_12893d0 release | 0x12894b3 | 5 | `0x12894b3  call qword ptr [0xF99FFA0]` | releases old object via vtable[0] | [V] |
| sub_4e05e50 entry | 0x4E05E50 | 1 | `0x4E05E50  push rbp` | sub_4e05e50 / mc_root pack->GPU root entry; `xref.py callers 0x4E05E50` = EMPTY (0 static callers) | [V] |
| sub_4e05e50 this copy | 0x4E05E6E | 8 | `0x4E05E6E  mov rdi,rcx` | rdi = RCX = texture object argument; mc_root RCX values are 0x390… heap objects whose hex dumps carry name fields "tex"/"legs"/"_spear"/"hud"/"mary" = TexturePtr::mClientTexture pointee | [V] [V live] |
| sub_4e05e50 +0x18 read | 0x4E05E71 | 8 | `0x4E05E71  mov rax,[rcx+0x18]` | reads texture_obj+0x18 (old texture object) | [V] |
| sub_4e05e50 old-release call | 0x4E05E86 | 5 | `0x4E05E86  call qword ptr [0xF99FFA0]` | releases old this+0x18 object via vtable[1] through the trampoline | [V] |
| sub_4e05e50 sampler flags | 0x4E05F61 | 8 | `0x4E05F61  mov r9,[rdi+0xE0]` | this+0xE0 sampler/flag word (6ax sampler flag) passed as r9 | [V] |
| sub_4e05e50 descriptor addr | 0x4E05F68 | 4 | `0x4E05F68  add rdi,0x58` | rdi = &texture_obj+0x58 = texture creation descriptor passed as rcx to sub_bc41420 | [V] |
| sub_4e05e50 -> sub_bc41420 | 0x4E05F77 | 5 | `0x4E05F77  call 0xBC41420` | issues createTexture via sub_bc41420; call end 0x4E05F7C = LIVE RESULT 5 ret (dragon_texture_caller_bc41420.txt `CALLER ret=0x4E05F7C`) | [V] [V live] |
| sub_4e05e50 call end | 0x4E05F7C | 1 | `0x4E05F7C  nop` | end of `call 0xBC41420` = LIVE RESULT 5 ret=0x4E05F7C [V live] | [V live] |
| sub_4e05e50 skip path | 0x4E06010 | 8 | `0x4E06010  mov qword ptr [rsi],0` | output handle slot cleared to 0 when nothing to create | [V] |
| ClientTexture ctor entry | 0x4E05450 | 1 | `0x4E05450  push rbp` | sub_4e05450 (0x4E05450..0x4E05843, size 0x3f3, 17 xrefs in); allocates a 0x30-byte control block and a 0xE8-byte texture object via [0xF99FFA0] | [V] |
| control-block alloc | 0x4E054E1 | 4 | `0x4E054E1  mov edx,0x30` | 0x30-byte control block allocated via `0x4E054E6  call qword ptr [0xF99FFA0]` | [V] |
| control-block vptr | 0x4E05507 | 8 | `0x4E05507  lea rax,[0xF215850]` | control-block vptr = 0xF215850 (slot 0 = sub_4e05de0 dtor), stored by `0x4E0550E  mov [rbx],rax` | [V] |
| control-block vptr store | 0x4E0550E | 8 | `0x4E0550E  mov [rbx],rax` | control-block vptr store | [V] |
| texture-object alloc | 0x4E0561D | 4 | `0x4E0561D  mov edx,0xE8` | 0xE8-byte texture object allocated via `0x4E05622  call qword ptr [0xF99FFA0]` | [V] |
| vptr load | 0x4E0564D | 8 | `0x4E0564D  lea r8,[0xF215838]` | vtable 0xF215838 address loaded into r8 | [V] |
| vptr store | 0x4E05654 | 8 | `0x4E05654  mov [rbx],r8` | texture object vptr = 0xF215838 -> vtable[1] = sub_4e05e50; this object is sub_4e05e50's `this` | [V] |
| descriptor store | 0x4E05689 | 16 | `0x4E05689  movups [rbx+0x58],xmm1` | creation descriptor stored at texture_obj+0x58 (matches sub_4e05e50 `0x4E05F68 add rdi,0x58`) | [V] |
| flags store | 0x4E0573A | 8 | `0x4E0573A  mov [rbx+0xE0],rax` | sampler/flags word stored at texture_obj+0xE0 (matches sub_4e05e50 `0x4E05F61 mov r9,[rdi+0xE0]`) | [V] |
| vtable 0xF215838 slot[0] | 0xF215838 | 8 | `0x4E060BB  lea rax,[0xF215838]` | sub_4e060b0 (vtable slot 0, size 0x6c, `push rsi`) references its own vtable -> vtable base identity | [V] |
| vtable 0xF215838 slot[1] | 0xF215840 | 8 | `0x4E05E50  push rbp` | rdis `vt 0xF215838`: slot +0x008 = sub_4e05e50, size 0x224 (0x4E05E50..0x4E06074, entry `push rbp`) => entry[+0x10]->vtable[1] is STATICALLY sub_4e05e50, i.e. rax at the [0xF99FFA0] trampoline jmp resolves to sub_4e05e50 for any object with vptr 0xF215838 | [V] |
| vtable 0xF215838 slot[2] | 0xF215848 | 8 | - | non-code 0x0 (rdis `vt`) | - | [V] |
| vtable 0xF2BDF40 slot[0] | 0xF2BDF40 | 8 | `0x66232B0  push rbp` | sub_66232b0 (size 0xb3d0 per rdis `vt`) = vtable 0xF2BDF40 slot 0 (deferred-texture-transaction job run slot) | [V] |
| root creates texture objects | 0x662405C | 5 | `0x662405C  call 0x4E05450` | sub_66232b0 creates ClientTexture objects via sub_4e05450 (2 sites: 0x662405C and 0x6624221; rdis `xr 0x4E05450` lists all 17 sites) | [V] |
| root drains entry queue | 0x66233AE | 5 | `0x66233AE  call 0x6632BF0` | sub_66232b0 -> sub_6632bf0 -> sub_12893d0; rdis `callers 0x6632bf0` = sub_66232b0 only (1 function, 2 call sites) | [V] |
| drain dispatch | 0x6632C55 | 5 | `0x6632C55  call 0x12893D0` | sub_6632bf0 -> sub_12893d0 (entry-array drain; static callers of sub_12893d0 also: sub_6622610 at 0x6622662, sub_1145c20 at 0x1145D5A/0x1145EE5) | [V] |
| static caller sub_6622610 | 0x6622662 | 5 | `0x6622662  call 0x12893D0` | sub_6622610 -> sub_12893d0 (entry rebuild before dispatch) | [V] |
| static caller sub_1145c20 | 0x1145D5A | 5 | `0x1145D5A  call 0x12893D0` | sub_1145c20 -> sub_12893d0 | [V] |
| static caller sub_1145c20 #2 | 0x1145EE5 | 5 | `0x1145EE5  call 0x12893D0` | sub_1145c20 second call site into sub_12893d0 | [V] |
| static entry to root | [0xF2BDF40] | - | - | rdis `callers 0x66232b0` = 0; `imm 0xF2BDF40` = 0 hits; `ptr 0xF2BDF40` = 0 pointers; `xr 0xF2BDF40` = 0 xrefs -> sub_66232b0 is entered ONLY by runtime job-system virtual dispatch of vtable 0xF2BDF40 slot 0; no static store of its vptr exists | [V] |
| sub_4e05e50 static callers | 0x4E05E50 | - | - | rdis `callers 0x4E05E50` = 0 calling functions; reached only via sub_12893d0's indirect vtable[1] tail-call through [0xF99FFA0] | [V] |
| bgfx dispatcher vtable load | 0xBC6A28F | 8 | `0xBC6A28F  mov rcx,[rdi+0x1EBF2D0]` | dispatcher: rcx = renderer-context vtable pointer | [V] |
| bgfx dispatcher vtable | 0xBC6A2AE | 8 | `0xBC6A2AE  mov rax,[rcx]` | rax = renderer-context vtable | [V] |
| bgfx dispatcher slot 26 | 0xBC6A2B1 | 8 | `0xBC6A2B1  mov rax,[rax+0xD0]` | rax = vptr[slot 26] = createTexture address 0xe8143c0 | [V] |
| bgfx dispatcher indirect call | 0xBC6A2C2 | 5 | `0xBC6A2C2  call qword ptr [0xF99FFA0]` | indirect vcall -> createTexture 0xe8143c0; createtexture_callers.txt: ONE caller ret=0xBC6A2C8 = instruction right after this call | [V] [V live] |
| createTexture entry | 0xE8143C0 | 1 | `0xE8143C0  push rbp` | slot-26 createTexture; no static caller (`xref.py callers 0xe8143c0` = EMPTY) | [V] |
| createTexture record table | 0xE8143F3 | 8 | `0xE8143F3  lea r12,[rcx+0xBDE178]` | record table this+0xBDE178 stride 0xB8 | [V] |
| createTexture -> backend create | 0xE81455B | 5 | `0xE81455B  call 0xE81BF30` | createTexture -> TextureD3D12::create (backend record table) | [V] |
| backend ret site | 0xE814560 | 1 | `0xE814560  nop` | ret site after call 0xE81BF30 = l8b_texcreate_record.txt `CALLER ret=0xE814560` [V live] | [V live] |
| returned handle call | 0xC296E1A | 5 | `0xC296E1A  call 0xBC74120` | ax = returned u16 bgfx handle | [V] |
| handle store | 0xC296E26 | 2 | `0xC296E26  mov [rdi],ax` | returned u16 handle stored at [texture_obj+0x00] | [V] |
| descriptor copy 1 | 0xC296E2D | 16 | `0xC296E2D  movups xmm0,[r12]` | 0x1C create descriptor load (16 B movups) | [V] |
| descriptor copy 2 | 0xC296E32 | 16 | `0xC296E32  movups [rdi+8],xmm0` | descriptor copied to texture object +0x08 (16 B movups) | [V] |
| descriptor ptr store | 0xC296E3B | 8 | `0xC296E3B  mov [rdi+0x18],rdx` | descriptor pointer stored at texture object +0x18 | [V] |
| sub_bc41420 -> dragon entry | 0xBC41B39 | 5 | `0xBC41B39  call 0xC296B50` | sub_bc41420 -> dragon entry 0xc296b50; ret site 0xBC41B3E = LIVE RESULT 4 ret (dragon_texture_entry_c296b50.txt `CALLER ret=0xBC41B3E`) | [V] [V live] |

================================================================================
2. CHAIN SUMMARY (cited from prior rounds, not re-derived)
================================================================================

Resolved this session (section 1, all [V]):
- Indirect caller of sub_4e05e50 = sub_12893d0 (entry 0x12893D0), call site
  `0x1289490  call qword ptr [0xF99FFA0]`, fall-through 0x1289496.
  mc_root_4e05e50_callers.txt: every listed hit ret=0x1289496 => entry[+0x10]->
  vtable[1] = sub_4e05e50 at runtime [V live]. RCX = vptr-bearing ClientTexture-class
  heap objects (name fields "tex"/"legs"/"_spear"/"hud"/"mary") = TexturePtr::mClientTexture
  pointee, not the 32B TexturePtr stub [V live]. So rax at the [0xF99FFA0] trampoline
  jmp = sub_4e05e50 (0x4E05E50) [V live]. This resolves the r37 pending item (decode
  rax at the jmp); static work on [0xF99FFA0] is exhausted (read-only .rdata
  initializer = trampoline sub_eea6040 `jmp rax`, no writer).
- sub_4e05e50 fully decoded: releases old texture at this+0x10/+0x18 via vtable
  calls through [0xF99FFA0], then builds a GPU texture from the descriptor at
  this+0x58 with sampler/flags from this+0xE0 and issues it via
  `0x4E05F77  call 0xBC41420` (call ends 0x4E05F7C = LIVE RESULT 5 ret [V live])
  -> sub_bc41420 -> dragon entry 0xc296b50 -> wrapper 0xbc73bf0 -> producer
  sub_bc73770 (writes bgfx command byte 0x0E) -> bgfx dispatcher
  (vptr[slot 26] = createTexture 0xe8143c0) -> createTexture 0xe8143c0 ->
  TextureD3D12::create 0xe81bf30 [V live + dis].
- Handle trace into texture object / TexturePtr: returned u16 handle stored at
  [texture_obj+0x00] at 0xC296E26 [V]; descriptor copied to texture_obj+0x08/+0x18;
  texture_obj = TexturePtr+0x58 (`0x4E05F68  add rdi,0x58` [V]); sdk
  TexturePtr/ClientTexture headers read from src tree [V file read].

Already proven in prior rounds (cited, not re-derived):
- sampler flag decode + sampler cache (6ax): docs/functions/e820500.md +
  src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h [V].
- D3D12 backend texture-management chain: record table this+0xBDE178 stride 0xB8;
  createTexture 0xe8143c0 (slot 26), updateTexture 0xe814a70, readTexture 0xe8150f0,
  resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor
  0xe80f290, blit 0xe818bc0 / blitSetup 0xe819750 [V].
- createTexture issuance end-to-end below sub_4e05e50 [V live]: producer sub_bc73770
  writes cmd byte 0x0E; dispatcher case -> createTexture 0xe8143c0;
  createtexture_callers.txt ONE caller ret=0xBC6A2C8 [V live].
- texgroup_load(0x5421c90) static graph: calls sub_eec6ec0/sub_eec6eb0, sub_5477a30,
  sub_5475a30, `0x54227af  call 0x18718D0`, sub_e935700, sub_5424000,
  sub_5424130; those terminate at texture-cache/ResourceLoadManager indirect dispatch
  cells (0xF9A8xxx range, e.g. [0xF9A8C78]) and async enqueue 0x71BC70 — none enters
  sub_4e05450/sub_66232b0/sub_4e05e50 [V].
- Atlas stitchers (L8a/L8b) remain separate open units (oc_U-EL8a/oc_U-EL8b); mip/
  compression builders are out of scope.

================================================================================
3. ANGLES TRIED (do not redo)
================================================================================

FAILED ANGLES FROM PRIOR ROUNDS:
- command-byte-0x0E producer search: no `mov byte ptr [mem],0x0E` anywhere
  (`imm 0x0E`); all command-buffer writers hardcode other opcodes (0x00/0x07/0x0A/0x0B/0x12/0x14/0x27);
  dispatch table obfuscated [V negative].
- [0xF99FFA0] code-writer search: 0 hits; read-only .rdata initializer holding
  sub_eea6040, never rewritten.
- xref.py callers 0x4E05E50 / 0xe8143c0 / 0x5421C90: all EMPTY; none enters
  sub_4e05e50.
- rdis immediate scan for vtable 0xF215838 (32-bit) = 0 hits (superseded: the real
  static store is the RIP-relative `lea r8,[0xF215838]` at 0x4E0564D).
- [0xF99FFA0] read at 0x12894b3 and 0x4E05E86 are releases through vtable[0]/vtable[1],
  not the createTexture issuance root.

================================================================================
4. CLOSES?
================================================================================

NO — single blocking fact: no [V]-proven STATIC path texgroup_load(0x5421c90)
-> sub_4e05e50. texgroup_load's static graph ends at the texture-cache /
ResourceLoadManager async enqueue (0x71BC70); the hop into the GPU-upload root
is the runtime-only deferred-texture-transaction job (sub_66232b0, vtable
0xF2BDF40 slot 0, zero static references) -> sub_6632bf0 -> sub_12893d0 ->
indirect vtable[1] call through [0xF99FFA0] -> sub_4e05e50 -> createTexture.
That runtime bind IS observed ([V live] mc_root_4e05e50_callers.txt, all hits
ret=0x1289496; the indirect target is now also STATICALLY known: vtable
0xF215838 slot[1] = sub_4e05e50 [V]) but the static texgroup_load ->
sub_66232b0 edge cannot be established by static analysis.
Everything else in L7e is [V]/[V live]-proven: Half 1 sampler flag decode +
cache (6ax); Half 2a D3D12 backend texture-management chain; createTexture
issuance below sub_4e05e50 (producer sub_bc73770 writes bgfx cmd byte 0x0E ->
dispatcher slot 26 -> createTexture 0xe8143c0 -> TextureD3D12::create
0xe81bf30); handle trace into texture object +0x00 / TexturePtr
(TexturePtr+0x58); sdk TexturePtr/ClientTexture headers. Atlas stitchers
(L8a/L8b) are separate open units, not this unit.

================================================================================
5. TOOL REQUESTS
================================================================================

None — all instruction lines taken verbatim from fresh rdis disassembly of the
1.26.62.01 exe (vt/imm/ptr/xr/callers/dis/fn), verified with
tools/sigs/verify_oc.py; live captures read from docs/data/live/*.txt; sdk
TexturePtr headers read from the src tree; no helper scripts written, no
temporary files left behind.
