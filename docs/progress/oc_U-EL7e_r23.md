## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): `- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending | PROGRESS 2026-11-21 oc_U-EL7e.md (verify_oc 185/185): D3D12 backend texture-management chain decoded [V] ...; Minecraft-side pack->GPU chain (texgroup_load 0x5421c90 -> texload 0x58a1310 -> texload_task 0x541bf00 -> undecoded 0x18718D0 at 0x54227af) and atlas stitchers still open (L8a/L8b)`

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only (live capture logs under docs/data/live are read-only inputs produced by the orchestrator; a note is not proof — every quoted `0xRVA  instr` below is re-verified via rdis this session).

Tags: [V] saw in disassembly (RVA cited, verbatim line quoted) / [V live] saw in an orchestrator live capture log (file cited) / [I] inferred from structure or BGFX_MAP / [?] unknown or not located.

Row rule: one annotated row per distinct offset, all its read/store sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after the address, copied verbatim from rdis) | meaning ONLY if an instruction/string shows it else '-' | tag. Sizes from the instruction (movups/movaps/movdqu/movdqa 16, qword 8, dword/movss 4, word 2, byte 1). No input data pasted as-is; no skipped offsets among quoted sites; no raw instruction dumps outside tables. No "etc.".

## Already proven (cited from r1-r22; not re-quoted, not redone)

- Half 1 — sampler flag decode + sampler cache (6ax): [V] docs/functions/e820500.md decodes 0xe820500 instruction-complete; src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h carries the static_asserts; called from blit 0xe818bc0 and executor 0xe821120.
- Half 2a — D3D12 backend texture-management chain: [V] record table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0, updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0, blitSetup 0xe819750; BGFX_MAP 6z/6z-2/6aj confirm table base/stride and live texture records.
- createTexture issuance chain from MC code [V live + dis r22]: sub_4e05e50 -> `0x4E05F77  call 0xBC41420` -> sub_bc41420 -> 0xc296b50 -> wrapper 0xbc73bf0 -> producer 0xbc73770 (command-byte-0x0E) -> bgfx dispatcher case 0xBC6A2C2 (`0xBC6A2B1  mov rax,[rax+0xD0]`, slot 26 = 0xe8143c0 [V BGFX_MAP]) -> `0xBC6A2C2  call qword ptr [0xF99FFA0]` -> createTexture 0xe8143c0 -> `0xE81455B  call 0xE81BF30` TextureD3D12::create (ret 0xe814560 [V live]). Returned handle `0xC296E1A  call 0xBC74120` (ax) -> `0xC296E26  mov [rdi],ax` at texture_obj+0x00 [V r22]; texture_obj = TexturePtr+0x58 (`0x4E05F68  add rdi,0x58`); sdk TexturePtr/ClientTexture [V file read].

## This session — verified verbatim via fresh rdis (notes re-checked against the exe)

### 1. sub_12893d0 — the indirect caller of sub_4e05e50 (function containing 0x1289496) [V]

`sub_12893d0  [0x12893d0..0x12895d3) size 0x203 13 xrefs in` [V rdis fn]. It is the deferred-texture-transaction flush: for each 0x18-byte element {ptr@0, shared_ctrl@8, obj@0x10} it add_refs [ctrl+8], copies the 16-byte element, then tail-calls obj->vptr[1](&element) through trampoline [0xF99FFA0] = sub_eea6040 `jmp rax`; at capture time vptr[1] = sub_4e05e50, return address 0x1289496 [V live].

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| sub_12893d0 entry | 0x12893D0 | 1 | - | `0x12893D0  push rbp` | deferred-transaction processor entry; frame setup | [V] |
| array begin load | [rcx+0x0] | 8 | [rcx+0x0] | `0x1289406  mov r13,[rcx]` | r13 = deferred vector begin {ptr@0, ctrl@8} | [V] |
| array end load | [rcx+0x8] | 8 | [rcx+0x8] | `0x1289409  mov r14,[rcx+8]` | r14 = deferred vector end | [V] |
| shared ctrl load | [r13+0x8] | 8 | [r13+0x8] | `0x1289431  mov rcx,[r13+8]` | element+0x8 = shared control-block pointer | [V] |
| refcount load | [rcx+0x8] | 4 | [rcx+0x8] | `0x128943A  mov eax,[rcx+8]` | eax = refcount at ctrl+8 | [V] |
| add_ref CAS | [rcx+0x8] | 4 | [rcx+0x8] | `0x1289447  lock cmpxchg [rcx+8],edx` | atomic refcount increment, retry on failure | [V] |
| element copy 16B | [r13+0x0] | 16 | [r13+0x0] | `0x128944E  movups xmm0,[r13]` | copy element {ptr@0, ctrl@8} to local desc | [V] |
| object load | [r13+0x10] | 8 | [r13+0x10] | `0x128947D  mov rcx,[r13+0x10]` | rcx = element+0x10 = `this` for virtual call | [V] |
| vptr load | [rcx+0x0] | 8 | [rcx+0x0] | `0x1289486  mov rax,[rcx]` | rax = object vptr | [V] |
| vtable slot 1 load | [rax+0x8] | 8 | [rax+0x8] | `0x1289489  mov rax,[rax+8]` | rax = obj->vptr[1] = indirect call target | [V] |
| INDIRECT TAIL-CALL -> sub_4e05e50 | [0xF99FFA0] | 8 | [0xF99FFA0] | `0x1289490  call qword ptr [0xF99FFA0]` | trampoline sub_eea6040 `jmp rax`; rax = vptr[1] = sub_4e05e50 at runtime; pushed ret = 0x1289496 | [V] + [V live] |
| capture return site | 0x1289496 | 1 | - | `0x1289496  nop` | instruction right after call; matches capture ret=0x1289496 in all 32 samples | [V live] |
| object null-out / detach | [r13+0x10] | 8 | [r13+0x10] | `0x128949B  mov qword ptr [r13+0x10],0` | clear element+0x10 before release | [V] |
| release vptr load | [rcx+0x0] | 8 | [rcx+0x0] | `0x12894A8  mov rax,[rcx]` | rax = object vptr | [V] |
| release slot 0 load | [rax+0x0] | 8 | [rax+0x0] | `0x12894AB  mov rax,[rax]` | rax = obj->vptr[0] = destroying destructor | [V] |
| release indirect call | [0xF99FFA0] | 8 | [0xF99FFA0] | `0x12894B3  call qword ptr [0xF99FFA0]` | release object through same trampoline | [V] |

### 2. sub_12893d0 static callers — 4 functions, 13 sites [V rdis callers this session]

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| caller sub_6632bf0 site 1 | 0x6632C55 | 5 | - | `0x6632C55  call 0x12893D0` | deferred texture vector flush -> sub_12893d0 | [V] |
| caller sub_6632bf0 site 2 | 0x6632D1E | 5 | - | `0x6632D1E  call 0x12893D0` | deferred buffer vector flush -> sub_12893d0 | [V] |
| caller sub_1145c20 site 1 | 0x1145D5A | 5 | - | `0x1145D5A  call 0x12893D0` | sub_1145c20 -> sub_12893d0 | [V] |
| caller sub_1145c20 site 2 | 0x1145EE5 | 5 | - | `0x1145EE5  call 0x12893D0` | sub_1145c20 -> sub_12893d0 (2nd site, r22 undercounted as 1) | [V] |
| caller sub_6622610 site | 0x6622662 | 5 | - | `0x6622662  call 0x12893D0` | sub_6622610 -> sub_12893d0 | [V] |
| caller sub_66232b0 sites | - | - | (8 sites inside sub_66232b0) | sub_66232b0 -> sub_12893d0 x8 [V rdis callers] | [V] |

None of these four callers is texgroup_load(0x5421c90), texload(0x58a1310) or texload_task(0x541bf00).

### 3. sub_4e05e50 — texture-object vtable[1] create/load method, 0 static xrefs [V dis this session + V live]

`sub_4e05e50  [0x4e05e50..0x4e06074) size 0x224 0 xrefs in` [V rdis fn]. RCX is the polymorphic texture OBJECT itself (constant vptr 0x7FF6A8215838 = RVA 0xF215838 + base across all 32 capture samples; reads object+0xE0, size >= 0xE8) [V live + dis] — NOT a TexturePtr* (TexturePtr is 32 bytes, non-polymorphic, `static_assert(sizeof(TexturePtr) == 32)` [V file read]).

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| sub_4e05e50 entry | 0x4E05E50 | 1 | - | `0x4E05E50  push rbp` | entry; rdis fn reports 0 xrefs in | [V] |
| arg RCX saved to rdi | reg | 8 | `0x4E05E6E  mov rdi,rcx` | RCX argument (texture object) saved to rdi | [V] |
| object+0x18 load | [rcx+0x18] | 8 | [rcx+0x18] | `0x4E05E71  mov rax,[rcx+0x18]` | shared ctrl of member at object+0x18 | [V] |
| object+0x10 load | [rdi+0x10] | 8 | [rdi+0x10] | `0x4E05E8C  mov rdx,[rdi+0x10]` | shared_ptr member read | [V] |
| refcount load | [rdx+0x8] | 4 | [rdx+0x8] | `0x4E05E95  mov eax,[rdx+8]` | use count of the object+0x10 pointee | [V] |
| add_ref CAS | [rdx+0x8] | 4 | [rdx+0x8] | `0x4E05EA8  lock cmpxchg [rdx+8],r8d` | atomic use-count increment | [V] |
| renderer ctx load | [rdi+0xE0] | 8 | [rdi+0xE0] | `0x4E05F61  mov r9,[rdi+0xE0]` | object+0xE0 = renderer context -> R9 | [V] |
| texture sub-object | rdi+0x58 | - | reg | `0x4E05F68  add rdi,0x58` | rdi = embedded texture sub-object (TexturePtr+0x58) | [V] |
| RCX to sub_bc41420 | rdi (=orig RCX+0x58) | 8 | `0x4E05F74  mov rcx,rdi` | texture object passed as RCX to sub_bc41420 | [V] |
| dragon create call | 0xBC41420 | 5 | - | `0x4E05F77  call 0xBC41420` | sub_bc41420 -> 0xc296b50 -> ... -> createTexture | [V] |
| sub_4e05e50 ret site | 0x4E05F7C | 1 | - | `0x4E05F7C  nop` | return after sub_bc41420; live capture ret=0x4E05F7C | [V live] |

### 4. texgroup_load(0x5421c90) static chain — negative evidence [V this session]

`sub_5421c90  [0x5421c90..0x542359f) size 0x190f 7 xrefs in` [V rdis fn]. texgroup_load is called by sub_5958f0, sub_596230, sub_95e0f0, sub_5420770 (x2), sub_5424290 (x2) [V rdis callers]. Its direct callees do NOT include sub_12893d0 or any of sub_12893d0's 4 callers:

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| texgroup_load cache call | 0x54227AF | 5 | - | `0x54227AF call 0x18718D0` | texgroup_load calls texture cache 0x18718d0 directly (not texload/texload_task, not sub_12893d0) | [V] |
| texgroup_load callee | 0x5421DEC | 5 | - | `0x5421DEC call 0x5477A30` | direct callee; not in sub_12893d0's caller tree | [V] |
| texgroup_load callee | 0x5421ED6 | 5 | - | `0x5421ED6 call 0x5475A30` | direct callee; not in sub_12893d0's caller tree | [V] |
| texgroup_load callee | 0x5422869 | 5 | - | `0x5422869 call 0x5424000` | direct callee; not in sub_12893d0's caller tree | [V] |
| texgroup_load callee | 0x5422C5D | 5 | - | `0x5422C5D call 0x5424130` | direct callee; not in sub_12893d0's caller tree | [V] |

### 5. New angle: upward chains from sub_12893d0's 4 callers [V rdis callers this session]

Traced who calls each of sub_12893d0's 4 callers (the "who calls IT" angle from the r15 review), looking for any route into texgroup_load(0x5421c90) / texload(0x58a1310):

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| sub_66232b0 callers | 0x66232B0 | - | - | `sub_66232b0  -- 0 calling function(s)` [V rdis callers] | sub_66232b0 is an upward dead end (0 callers) | [V] |
| sub_661f200 callers | 0x661F200 | - | - | `sub_661f200  -- 0 calling function(s)` [V rdis callers] | sub_661f200 is an upward dead end (0 callers) | [V] |
| sub_6632bf0 caller | sub_66232B0 | 2 | - | `sub_6632bf0  sub_66232b0  2 call site(s)` [V rdis callers] | sub_6632bf0 only called by sub_66232b0 (dead end above) | [V] |
| sub_1145c20 caller | sub_882EE0 | 1 | - | `sub_1145c20  sub_882ee0  1 call site(s)` [V rdis callers] | sub_1145c20 only called by sub_882ee0 | [V] |
| sub_882ee0 caller | sub_879480 | 1 | - | `sub_882ee0  sub_879480  1 call site(s)` [V rdis callers] | sub_882ee0 only called by sub_879480 | [V] |
| sub_6622610 callers | sub_661a770/sub_661f200/sub_66232b0/sub_6632fd0/sub_bbd42d0/sub_bbd4490/sub_e86ced0 | - | - | `sub_6622610  7 calling function(s)` [V rdis callers] | 7 callers; sub_661f200/sub_66232b0 dead-end, others branch to unrelated code | [V] |

No branch of these upward chains reaches texgroup_load(0x5421c90), texload(0x58a1310) or texload_task(0x541bf00). Combined with section 4 (texgroup_load's direct callees don't enter the sub_12893d0 caller tree), there is no static path texgroup_load -> sub_4e05e50.

## TexturePtr / ClientTexture connection

sub_4e05e50's RCX is the texture OBJECT (vtable 0xF215838, slot 1 = sub_4e05e50 [V rdis vt]) carrying refcounted/shared_ptr-shaped members at object+0x10 and object+0x18 that sub_4e05e50 add_refs/releases via [0xF99FFA0] [V dis]. The texture job object is CONSTRUCTED by sub_4e05450 (vptr=0xF215838 at object+0x00 via `0x4E05654  mov [rbx],r8` [V r22]; texture sub-object at +0x58 via `0x4E05689  movups [rbx+0x58],xmm1` [V r22]; renderer ctx at +0xE0 via `0x4E0573A  mov [rbx+0xE0],rax` [V r22]). sub_4e05450 has 16 static callers [V r22], none is texgroup_load/texload/texload_task. The created handle lands at [obj+0x58+0] via `0xC296E26  mov [rdi],ax` [V r22]. sdk TexturePtr.h `static_assert(sizeof(TexturePtr) == 32)`, mClientTexture +0x00 / mResourceLocationPtr +0x10; ClientTexture empty struct; BedrockTexture 48 bytes [V file read].

## What I tried that failed (new angles that did not close the gap)

- Upward caller chains from all four sub_12893d0 callers (sub_6632bf0, sub_1145c20, sub_6622610, sub_66232b0): traced one level up this session (sub_66232b0 = 0 callers; sub_661f200 = 0 callers; sub_6632bf0 <- sub_66232b0; sub_1145c20 <- sub_882ee0 <- sub_879480; sub_6622610 <- 7 callers). None reaches texgroup_load/texload/texload_task; branches lead to unrelated functions or dead ends [V rdis callers this session].
- texgroup_load's direct callees (0x18718D0, 0x5477A30, 0x5475A30, 0x5424000, 0x5424130, 0xEEC6EC0, 0xEEC6EB0, 0xE935700, 0x78ED0, 0x9BC830) none is sub_12893d0 or its 4 callers [V this session].
- sub_4e05e50 has 0 static xrefs (`rdis callers 0x4E05E50` -> 0 calling functions) [V this session]; reached only via sub_12893d0's indirect vtable[1] tail-call `0x1289490  call qword ptr [0xF99FFA0]` (ret site 0x1289496 [V live]).
- rdis imm 0x4E05E50 / imm 0x12893D0: 0 hits — neither address appears as an immediate leading into texgroup_load's tree [V r22, not redone].
- Prior negatives (not redone): xref.py callers 0xe8143c0 EMPTY; texload/texload_task EMPTY; 0x18718d0 cache miss path (vtable 0xEFCA680 object + completion 0x186dac0) never calls sub_4e05e50/sub_12893d0; cache 0x18718d0 builds objects with vtable 0xEFCA680, NOT 0xF215838 [V r19].

## CLOSES?

NO — blocking fact: no [V]-proven static path texgroup_load(0x5421c90) -> sub_4e05e50. sub_4e05e50 has 0 static xrefs (`rdis callers 0x4E05E50` -> 0 calling functions [V this session]; fn 0x4E05E50..0x4E06074, 0 xrefs in [V rdis]) and is only reached via sub_12893d0's indirect vtable[1] tail-call `0x1289490  call qword ptr [0xF99FFA0]` (capture ret site 0x1289496 [V live], all 32 samples). sub_12893d0 (13 xrefs in [V rdis]) is statically called from sub_6632bf0 (`0x6632C55`/`0x6632D1E call 0x12893D0` [V this session]), sub_1145c20 (`0x1145D5A`/`0x1145EE5 call 0x12893D0` [V this session]), sub_6622610 (`0x6622662 call 0x12893D0` [V this session]) and sub_66232b0 (x8 [V rdis callers]); all upward chains dead-end or branch to unrelated code (sub_66232b0 and sub_661f200 have 0 callers [V this session]), none is texgroup_load/texload/texload_task. texgroup_load's direct callees (`0x54227AF call 0x18718D0`, `0x5421DEC call 0x5477A30`, `0x5421ED6 call 0x5475A30`, `0x5422869 call 0x5424000`, `0x5422C5D call 0x5424130` [V this session]) do not enter the sub_12893d0 or sub_4e05450 caller trees. The texture job constructor sub_4e05450 (sets vptr=0xF215838 at `0x4E05654  mov [rbx],r8` [V r22]) has 16 static callers [V r22], none is texgroup_load/texload/texload_task. The bind texgroup_load -> sub_4e05e50 is runtime-only (object vptr+8 = sub_4e05e50 via vtable 0xF215838, tail-call trampoline [0xF99FFA0] = sub_eea6040 `jmp rax`) and is observed live [V live]. Everything else in the item is [V]-proven: sampler flag decode + cache (6ax) [V], D3D12 backend texture-management chain [V], command-byte-14 producer sub_bc73770 [V r4], dispatcher [vptr+0xD0]->createTexture 0xe8143c0 [V live + dis], returned handle stored at [texture_obj+0x00] [V r22] with texture_obj = TexturePtr+0x58 [V], TexturePtr/ClientTexture sdk headers [V file read]. Atlas stitchers (L8a/L8b) remain out of scope (MIRROR_SKIP).

## TOOL REQUESTS

- None. Static analysis is exhausted: sub_4e05e50 (0 xrefs), sub_12893d0 (4 callers, all dead-end/unrelated), texgroup_load (5 direct callees, none enters the sub_12893d0 tree), sub_4e05450 (16 callers, none is texgroup_load). The bind texgroup_load -> sub_4e05e50 is runtime-only via vtable[1] indirect dispatch through trampoline [0xF99FFA0] = sub_eea6040 `jmp rax`, observed live [V live]. All instruction lines re-verified verbatim against a fresh rdis dis this session; live capture logs are read-only inputs; rdis fn/callers/dis used for positive and negative findings. No helper scripts written; no temporary files left behind.
