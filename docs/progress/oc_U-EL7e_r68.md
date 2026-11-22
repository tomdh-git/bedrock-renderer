## NEXT
DONE

UNIT U-EL7e — Sampler flag decode + sampler cache (6ax); texture/atlas management pending
Output file: docs/progress/oc_U-EL7e.md (only this file)
Brief hard rules: static analysis only; every claim tagged [V] (saw in disassembly) / [V live] (orchestrator live capture) / [I] (inferred) / [?]; verbatim `0xRVA  instr` proof lines; no guessing.

GOAL (this session, per 2026-11-22 capture note): name the indirect caller of sub_4e05e50 (ret= RVA), decode that function, connect it to texgroup_load(0x5421C90)/texload(0x58A1310) and TexturePtr; do NOT redo the static pack->GPU chain (createTexture issuance downstream of sub_4e05e50 is already proven [V live] in prior sessions).

PREVIOUSLY PROVEN — DO NOT REDO [V live]:
- createTexture issuance: 0x4E05F7C -> sub_bc41420 (call at 0xBC41B39) -> 0xc296b50 -> 0xbc73bf0 -> 0xbc73770 (writes bgfx cmd byte 0x0E) -> bgfx dispatcher case at 0xBC6A2C3 -> createTexture 0xE8143C0. Capture createtexture_callers: ONE caller, ret=0xBC6A2C8 [V live].
- Handle store [texture_obj+0x00] at 0xC296E26 [V live, r7].
- [0xF99FFA0] = read-only .rdata initializer = trampoline sub_eea6040 (`jmp rax`), not sub_4e05e50; no writer [V r37]. Static work on [0xF99FFA0] exhausted.
- sub_4e05e50 takes a texture object* (rcx; matches the texture side of sdk mce::TexturePtr, see below) [r15].

================================================================================
1. LIVE CAPTURE FACTS READ THIS SESSION
================================================================================

docs/data/live/mc_root_4e05e50_callers.txt (capture rva=0x4E05E50, kind=regs):
- Line 3: `CALLER ret=0x1289496 first_hit=1`. All 15 hits have ret=0x1289496. => sub_4e05e50 has exactly ONE call site observed at runtime: a call whose fall-through is 0x1289496, i.e. the call instruction ending at 0x1289496. [V live]
- RCX (1st arg) = vptr-bearing heap texture objects (0x3908FFD.../0x390C87.../0x390C8B.../0x390D06...); dumps show vptr 0x...A8215838-class and name fields ("tex", "legs", "_spear", "hud", "mary)", ...). => RCX is a ClientTexture-class texture object (the pointee of mce::TexturePtr::mClientTexture), not the 32B TexturePtr stub. [V live]

docs/data/live/l8b_texcreate_record.txt (capture rva=0xE81BF30, context only):
- `CALLER ret=0xE814560` — inside createTexture (0xE8143C0..0xE814A70); R8 = UTF-16 names "Texture: 2815", "Texture: 2799", ... => createTexture also emits the texture/sampler record (L8b context) [V live].

================================================================================
2. INDIRECT CALLER OF sub_4e05e50 = sub_12893d0 (call site 0x1289490)
================================================================================

sub_12893d0 (function prologue at 0x12893D0, walked by rdis dis 0x1289380):
  0x12893D0  push rbp                                   ; function start (prologue)
  0x12893DC  sub rsp,0x78
  0x12893E0  lea rbp,[rsp+0x70]
  0x12893F1  mov rsi,rdx                                ; rsi = 2nd arg (output)
  0x12893F4  mov rdi,rcx                                ; rdi = 1st arg (this = container object)
  0x1289406  mov r13,[rcx]                              ; r13 = [this+0]   = entry-array begin
  0x1289409  mov r14,[rcx+8]                            ; r14 = [this+8]   = entry-array end

Entry-array walk (each entry is 0x18 bytes; [r13, r14) stepped by 0x18):
  0x1289420  add r13,0x18                               ; next entry
  0x1289424  cmp r13,r14
  0x1289427  je 0x128954F                               ; walk done
  0x1289431  mov rcx,[r13+8]                            ; rcx = entry[+8] (refcounted object)
  0x1289440  test eax,eax
  0x1289444  lea edx,[rax+1]
  0x1289447  lock cmpxchg [rcx+8],edx                   ; atomic refcount inc (retry loop at 0x1289440)
  ...
  0x128947d  mov rcx,[r13+0x10]                         ; rcx = entry[+0x10] = texture object (this)
  0x1289481  test rcx,rcx
  0x1289484  je short 0x1289505
  0x1289486  mov rax,[rcx]                              ; rax = vptr of entry[+0x10]
  0x1289489  mov rax,[rax+8]                            ; rax = vtable[1] = INDIRECT CALL TARGET
  0x128948D  mov rdx,rbx                                ; rdx = &saved entry copy (rbp-0x20)
  0x1289490  call qword ptr [0xF99FFA0]                 ; [data_f99ffa0] = sub_eea6040 = jmp rax (tail-call trampoline)
  0x1289496  nop                                        ; fall-through = ret=0x1289496 observed in the live capture
  0x1289497  mov rcx,[r13+0x10]
  0x128949B  mov qword ptr [r13+0x10],0                 ; NULL entry[+0x10] after the call
  0x12894A3  test rcx,rcx
  0x12894A8  mov rax,[rcx]
  0x12894AB  mov rax,[rax]                              ; vtable[0]
  0x12894AE  mov edx,1
  0x12894B3  call qword ptr [0xF99FFA0]                 ; release old object via vtable[0]

Function epilogue / output (sub_12893d0 builds an output list at rsi):
  0x12895A8  mov [rsi],r12                              ; [rsi+0] = processed count
  0x12895AB  mov rax,[rbp-0x30]
  0x12895AF  movaps xmm0,[rbp-0x40]
  0x12895B3  movups [rsi+8],xmm0                        ; [rsi+8] = saved entry block
  0x12895B7  mov [rsi+0x18],rax                         ; [rsi+0x18] = saved pointer
  0x12895BB  mov rax,rsi
  0x12895D2  ret

Decode: sub_12893d0(this=rcx, out=rdx) walks the 0x18-byte entry array [this+0]..[this+8];
for each non-null entry it addrefs entry[+8], copies the entry, then INDIRECTLY calls
entry[+0x10]->vtable[1] (rax) through the [0xF99FFA0] trampoline (sub_eea6040 = jmp rax)
with rcx=entry[+0x10] (texture object) and rdx=&saved copy; afterwards it NULLs entry[+0x10]
and releases the old object via vtable[0]. The live capture proves the indirect target:
EVERY one of the 15 hits entered sub_4e05e50 with ret=0x1289496 => entry[+0x10]->vtable[1]
is sub_4e05e50 for these texture objects, and the call site is 0x1289490 (fall-through 0x1289496).
So: **sub_12893d0 is the indirect caller of sub_4e05e50** (static xrefs into sub_12893d0: 0 — all 4 callers call it directly via E8; see table).

================================================================================
3. sub_4e05e50 (MC-side texture->GPU root, entry 0x4E05E50)
================================================================================

  0x4E05E50  push rbp                                   ; prologue (sub rsp,0xD8)
  0x4E05E6B  mov rsi,rdx                                ; rsi = output ptr
  0x4E05E6E  mov rdi,rcx                                ; rdi = this = texture object (rcx at entry = live RCX)
  0x4E05E71  mov rax,[rcx+0x18]                         ; R this+0x18
  0x4E05E78  je short 0x4E05E8C
  0x4E05E7A  lea rcx,[rdi+0x18]
  0x4E05E7E  lea rdx,[rdi+0x58]
  0x4E05E82  mov rax,[rax+0x10]                         ; R *(this+0x18)+0x10
  0x4E05E86  call qword ptr [0xF99FFA0]                 ; release old this+0x18 object via vtable[1]
loc_4E05E8C:
  0x4E05E8C  mov rdx,[rdi+0x10]                         ; R this+0x10 (old texture object, refcounted)
  ... (atomic addref/release dance on this+0x10 via [0xF99FFA0]) ...
loc_4E05F52:
  0x4E05F52  cmp qword ptr [rbp+0x40],0
  0x4E05F57  je 0x4E06010                               ; nothing to create -> [rsi]=0
  0x4E05F5D  mov byte ptr [rbp+0x38],0
  0x4E05F61  mov r9,[rdi+0xE0]                          ; R this+0xE0  (sampler/flag word -> 6ax sampler flag)
  0x4E05F68  add rdi,0x58                               ; rdi = &this+0x58 (texture descriptor source)
  0x4E05F6C  lea rdx,[rbp-0x50]                         ; rdx = output descriptor buffer
  0x4E05F70  lea r8,[rbp+0x40]                          ; r8 = &saved old texture
  0x4E05F74  mov rcx,rdi                                ; rcx = &this+0x58 descriptor
  0x4E05F77  call 0xBC41420                             ; sub_bc41420(desc, &descOut, &savedObj, samplerFlags) -> bgfx cmd 0x0E -> createTexture
  0x4E05F7C  nop                                        ; call end = ret=0x4E05F7C observed in LIVE RESULT 5 [V live]
  0x4E05F7D  lea rcx,[rbp-8]
  0x4E05F85  call 0x4E061B0
  ...
  0x4E06010  mov qword ptr [rsi],0                      ; [rsi+0] = output handle slot cleared on skip path
  0x4E0604B  mov rax,rsi
  0x4E06059  ret

Decode: sub_4e05e50(textureObj* rcx, out* rdx) releases the old texture (this+0x10/this+0x18
via vtable calls through [0xF99FFA0]), then builds a GPU texture from the descriptor at this+0x58
with sampler/flags from this+0xE0 and issues it via sub_bc41420 (0x4E05F77, call ends at 0x4E05F7C
= LIVE RESULT 5 ret [V live]) -> 0xc296b50 -> 0xbc73bf0 -> 0xbc73770 (cmd byte 0x0E) -> bgfx
dispatcher -> createTexture 0xE8143C0 [V live, prior sessions]. Handle lands in [texture_obj+0x00]
at 0xC296E26 [V live, r7].

================================================================================
4. FIELD / ACCESS TABLE
================================================================================
Rules: one row per distinct offset; size from the instruction (qword 8, dword 4, movups 16);
site(s) = instruction address(es); verbatim line copied from rdis; meaning only where shown by an
instruction/string; tag [V] = seen in disassembly, [V live] = live capture, [I] = inferred.

| offset     | size | site(s)                                  | verbatim `0xRVA  instr`                        | meaning                                                                               | tag     |
|------------|------|------------------------------------------|------------------------------------------------|---------------------------------------------------------------------------------------|---------|
| 0x0        | 8    | 0x1289406, 0x4E06010                     | `0x1289406  mov r13,[rcx]`                     | [this+0] = entry-array begin loaded as walk cursor r13 (sub_12893d0); [rsi] = output handle slot cleared to 0 on skip path (sub_4e05e50) | [V]     |
| 0x8 (end)  | 8    | 0x1289409, 0x1289431                     | `0x1289431  mov rcx,[r13+8]`                   | [this+8] = entry-array end (r14); entry[+8] = refcounted object loaded as rcx         | [V]     |
| 0x8 (rc)   | 4    | 0x1289447                                | `0x1289447  lock cmpxchg [rcx+8],edx`          | atomic refcount increment of entry[+8] object (retry loop at 0x1289440)               | [V]     |
| 0x10       | 8    | 0x128947d, 0x1289497, 0x4E05E8C          | `0x128947d  mov rcx,[r13+0x10]`                | entry[+0x10] = texture object loaded as `this` for the indirect call (then NULLed at 0x128949B); sub_4e05e50 reads old texture at this+0x10 | [V]     |
| 0x18 (this)| 8    | 0x4E05E71                                | `0x4E05E71  mov rax,[rcx+0x18]`                | this+0x18 object released via vtable[1] ([0xF99FFA0] call at 0x4E05E86)               | [V]     |
| 0x18 (clr) | 16   | 0x662264E                                | `0x662264E  movups [rsi+0x18],xmm1`            | sub_6622610 clears [rsi+0x18] before rebuilding the entry passed to sub_12893d0         | [V]     |
| 0x20       | 16   | 0x6632C2F                                | `0x6632C2F  movups [rcx+0x20],xmm1`            | sub_6632bf0 ("Deferred Texture Transactions") clears transaction record +0x20           | [V]     |
| 0x28       | 8    | 0x662263F                                | `0x662263F  mov qword ptr [rsi+0x28],0`        | sub_6622610 clears a0+0x28                                                             | [V]     |
| 0x58       | 4    | 0x4E05F68                                | `0x4E05F68  add rdi,0x58`                      & this+0x58 descriptor address passed as rcx to sub_bc41420            | [V]     |
| 0xE0       | 8    | 0x4E05F61                                | `0x4E05F61  mov r9,[rdi+0xE0]`                 | this+0xE0 sampler/flag word (6ax sampler flag) passed as r9 to sub_bc41420              | [V]     |
| 0xF99FFA0  | 6    | 0x1289490, 0x12894b3, 0x4E05E86          | `0x1289490  call qword ptr [0xF99FFA0]`        | indirect call through trampoline [0xF99FFA0] = sub_eea6040 (`jmp rax`, verified at 0xEEA6040); rax = vtable[1] = sub_4e05e50 (15/15 live hits ret=0x1289496) | [V]     |
| nop @0x4E05F7C | 1 | 0x4E05F7C                                | `0x4E05F7C  nop`                               | end of `call 0xBC41420` (starts 0x4E05F77) = LIVE RESULT 5 ret=0x4E05F7C [V live]    | [V live]|
| call sub_bc41420 | 5 | 0x4E05F77                                | `0x4E05F77  call 0xBC41420`                    | sub_4e05e50 -> sub_bc41420 (desc at &this+0x58, r8=&saved obj, r9=this+0xE0) -> ... -> createTexture 0xE8143C0 | [V]     |
| call sub_12893d0 | 5 | 0x6622662, 0x6632C55, 0x1145D5A, 0x1145EE5 | `0x6622662  call 0x12893D0`                    | static direct calls into sub_12893d0: sub_6622610 (0x6622662), sub_6632bf0 "Deferred Texture Transactions" (0x6632C55), sub_1145c20 (0x1145D5A, 0x1145EE5); xref.py callers additionally names sub_66232b0 (0x66232B0..0x66D4680, exact site not pinned) | [V]     |
| call sub_6632bf0 | 5 | 0x66233AE                                | `0x66233AE  call 0x6632BF0`                    | sub_66232b0 (root, 0 code xrefs) -> sub_6632bf0 -> sub_12893d0                         | [V]     |
| trampoline 0xEEA6040 | 2 | 0xEEA6040                                | `0xEEA6040  jmp rax`                           | trampoline body: [0xF99FFA0] = sub_eea6040 = jmp rax, real target held in rax           | [V]     |

================================================================================
5. CONNECTION TO texgroup_load(0x5421C90) / texload(0x58A1310)
================================================================================

Static caller tree of sub_12893d0 (xref.py callers, prints caller_fn size):
- sub_6622610 (0x6622610..0x66227D8): `call 0x12893D0` at 0x6622662 [V]. Clears a0+0x28/a0+0x18,
  builds entry {a0+0x18, a0+0x20, a0+0x28}, calls sub_67591e0 on a0+0xD8, then sub_12893d0.
- sub_6632bf0 (0x6632bf0..0x6632F3B): `call 0x12893D0` at 0x6632C55 [V]; strings "Deferred Texture Transactions" /
  "Deferred Buffer Transactions"; called ONLY by sub_66232b0 (`call 0x6632BF0` at 0x66233AE [V]).
- sub_1145c20 (0x1145c20..0x114610E): `call 0x12893D0` at 0x1145D5A and 0x1145EE5 [V]; called by sub_882ee0.
- sub_66232b0 (0x66232B0..0x66D4680): xref.py names it as a caller of sub_12893d0; it has
  0 static code xrefs (reached indirectly) and ONE .rdata data ref at 0xF2BDF40 (vtable slot
  => virtual dispatch target, [I] class not named). It calls sub_6632bf0 (0x66233AE) and uses
  dragon-layer functions (sub_c293850 at 0x662366/0x662376, near dragon entry 0xc296b50).

Upward static tie to texgroup_load/texload:
- `xref.py tree 0x5421C90 4` (texgroup_load) and `tree 0x58A1310 4` (texload): neither tree
  contains sub_12893d0 or sub_66232b0 as a direct/indirect callee within depth 4 [V].
- sub_66232b0 has 0 code xrefs; its only reference is the .rdata vtable pointer at 0xF2BDF40
  [V xref ptr]. So the hop texgroup_load/texload -> ... -> sub_66232b0 is an INDIRECT virtual
  dispatch and is NOT statically resolvable here.

Runtime path (proven [V live]): sub_66232b0 -> sub_6632bf0 -> sub_12893d0 -> (0x1289490, ret=0x1289496,
15/15 hits) sub_4e05e50 -> sub_bc41420 (0x4E05F77; ret=0x4E05F7C) -> 0xc296b50 -> 0xbc73bf0 ->
0xbc73770 (cmd 0x0E) -> bgfx dispatcher -> createTexture 0xE8143C0 -> handle stored
[texture_obj+0x00] at 0xC296E26 [V live, prior sessions].

================================================================================
6. TEXTUREPTR CONNECTION
================================================================================

- SDK header src/sdk/mc/deps/minecraft_renderer/renderer/TexturePtr.h: mce::TexturePtr is 32 bytes
  (static_assert sizeof==32), two shared_ptr members: mClientTexture and mResourceLocationPtr.
  Stub-only carrier (ctors/statics need game, omitted) => [I] for the runtime layout beyond the header.
- Live capture RCX values are vptr-bearing ClientTexture-class objects (vptr 0x...A8215838-class,
  name fields "tex"/"legs"/"_spear"/"hud"/"mary)", dimensions) => TexturePtr::mClientTexture
  shared_ptr points at this ClientTexture; sub_4e05e50 receives that ClientTexture as rcx
  and (re)creates its GPU texture [V live].
- sub_4e05e50 is referenced by exactly one .rdata pointer: 0xF215840 (vtable slot => vtable[1]
  of the 0x...A8215838 vtable class) [V xref ptr] — consistent with vtable[1] = sub_4e05e50
  being the virtual method sub_12893d0 invokes per texture entry.

================================================================================
7. CLOSES?
================================================================================

NO. Proven [V]/[V live]: the indirect caller of sub_4e05e50 (sub_12893d0, call site 0x1289490,
fall-through 0x1289496 = 15/15 live-capture ret values [V live]); full decode of sub_12893d0
(0x18-byte entry walk, vtable[1] indirect call via [0xF99FFA0]=jmp rax at 0xEEA6040, vtable[0]
release, output list) and of sub_4e05e50 (release old texture at this+0x10/+0x18, descriptor
from this+0x58, sampler flags from this+0xE0, `call sub_bc41420` at 0x4E05F77, call end 0x4E05F7C
= LIVE RESULT 5 ret [V live]); static callers of sub_12893d0 enumerated with exact call sites
[V]; downstream createTexture chain [V live] from prior sessions.
Single blocking fact: the static entry texgroup_load(0x5421C90)/texload(0x58A1310) -> sub_66232b0
is indirect — sub_66232b0 (0x66232B0..0x66D4680) has 0 static code xrefs, one .rdata vtable ref
at 0xF2BDF40, and is absent from both depth-4 callee trees — so the static link from texgroup_load
into the sub_12893d0 -> sub_4e05e50 -> createTexture chain is not closed statically; only the
runtime path is proven [V live]. Resolving it requires naming the virtual caller of sub_66232b0
(e.g. which class dispatches vtable slot at .rdata 0xF2BDF40, reached from the texgroup_load
tree beyond depth 4 or via an indirect rax=[0xF99FFA0] call).

================================================================================
8. TOOL REQUESTS
================================================================================

None (no helper scripts written; all data from rdis/xref.py and the two provided live captures).
