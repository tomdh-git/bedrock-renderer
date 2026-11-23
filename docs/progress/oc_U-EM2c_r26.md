## NEXT
DONE

# UNIT U-EM2c — M2c: reflected Cloud*/Shadow* parameter member tables (live-readable recipe)

GOAL (orchestrator, overrides prior runs): produce the recipe that lets the orchestrator read the CloudLightingParameters / CloudParameters / ShadowParameters / ShadowRange member tables live with Cheat Engine:
(1) where the registration stores the built type descriptor / member vector (global/static RVA or heap chain from a known global: [0xRVA] -> +off -> member begin/end);
(2) the member entry layout (stride, which entry field is the name std::string/char*, the offset, the type tag) read from the push_back/emplace in sub_11886f0 (stride = pointer arithmetic, fields = stores into the new entry);
(3) the vector begin/end field offsets in the descriptor.
Deliver as [V] instruction rows plus a one-line recipe:
  "read qword [exe+RVA] -> descriptor; members = [desc+Xbegin..desc+Xend) stride S; name at +a (std::string), offset at +b (u32), type at +c".
Path form requested: "[desc+0x78]->+0x48 begin, +0x50 end, stride S, name at +a, offset at +b, tag at +c".
CLOSES? YES when the recipe is complete and every RVA/offset in it is [V].

EXE (data only, RVA-relative to image base): C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe
All instruction lines below are verbatim from `rdis.exe dis` of that exe and re-checked with `tools/sigs/verify_oc.py`.
No game was launched, no build run, no existing hook/Sigs/CMake files edited. Only docs/progress/oc_U-EM2c.md created.

----------------------------------------------------------------
KNOWN FROM ORCHESTRATOR CE RUN (re-verified statically where possible; live values are per-instance evidence, not constants)
----------------------------------------------------------------
- registry [exe+0x1233E1A8] = heap/data object
- CloudLightingParameters live desc @0x22FC64D4560: +0x00=&global, +0x08=hash, +0x18=flags 0x80, +0x20=count 0x14, +0x28/+0x30/+0x40=callbacks exe+0x1188170/+0x11884A0/+0x11886F0, +0x60=0xD4C25870(u32), +0x68->node(+0x00 ptr,+0x30=0xF), +0x70->shared_ptr ctrl(vtable exe+0xF0DFBA0), +0x78->container object(+0x48 begin,+0x50 end)
- Callbacks stored in the descriptor: sub_1188170 (desc+0x28), sub_11884a0 (desc+0x30), sub_11886f0 (desc+0x40)

----------------------------------------------------------------
[V] PROOF — (1) REGISTRY GLOBAL READ [exe+0x1233E1A8] + ALLOCATOR THUNK [0xF99FFA0]
----------------------------------------------------------------
| registry/allocator item | size | site | instr | meaning [tag] |
|---|---|---|---|---|
| reg[0x1233E1A8] | 8 | sub_11884a0, sub_1188780 | `0x11884ce  mov rcx,[0x1233E1A8]` ; `0x118883e  mov rcx,[0x1233E1A8]` | registry object pointer from global [0x1233E1A8] [V] |
| reg+0x0 / reg+0x8 | 8 | sub_11884a0, sub_1188780 | `0x11884d5  mov rax,[rcx]` ; `0x11884d8  mov rax,[rax+8]` ; `0x1188845  mov rax,[rcx]` ; `0x1188848  mov rax,[rax+8]` | rax = [registry+8], passed to allocator [V] |
| allocator[0xF99FFA0] | - | sub_11884a0, sub_1188780 | `0x11884e1  call qword ptr [0xF99FFA0]` ; `0x118885c  call qword ptr [0xF99FFA0]` ; `0x1188887  call qword ptr [0xF99FFA0]` ; `0x118884c  cmp rdx,0xFFF` | sub_eea6040 allocator thunk (`jmp rax`); size compare at 0x118884c [V] |

----------------------------------------------------------------
[V] PROOF — (1) CLOUDLIGHTINGPARAMETERS TYPE-INIT sub_1188400  [0x1188400..0x1188491), size 0x91, 6 xrefs in
----------------------------------------------------------------
sub_1188400 is the CloudLightingParameters type registration: stores hash, RTTI name pointer, sizeof into the [0x128E48xx] metadata globals; sub_1188250 then builds the descriptor from them.

| type-init global | size | site | instr | meaning [tag] |
|---|---|---|---|---|
| g[0x128E48E0] | 4 | sub_1188400 | `0x1188425  mov eax,[0x128E48FC]` ; `0x118842b  mov [0x128E48E0],eax` | [0x128E48E0] = [0x128E48FC] (global whose address is stored at desc+0x00) [V] |
| g[0x128E48E4] | 4 | sub_1188400 | `0x1188431  mov dword ptr [0x128E48E4],0x8DE632ED` | type hash 0x8DE632ED (= desc+0x08) [V] |
| g[0x128E48E8] | 8 | sub_1188400 | `0x118843b  lea rax,[0xF6416AB]` ; `0x1188442  mov [0x128E48E8],rax` | RTTI name ptr "mce::framebuilder::CloudLightingParameters]" [V] |
| g[0x128E48F0] | 8 | sub_1188400 | `0x1188449  mov qword ptr [0x128E48F0],0x2A` | sizeof 0x2A (42) [V] |
| g[0x128E4900] | 4 | sub_1188400 | `0x1188404  mov eax,[0x128E4900]` | registration flag/counter (dedup vs [tls+4]) [V] |

Sibling type-inits (CloudParameters, ShadowParameters, ShadowRange) should follow the same pattern (hash -> [0x128E48xx] global, RTTI name ptr, sizeof). Only sub_1188400 (CloudLightingParameters) was located [V]; no separate sibling init was found in 0x1188000..0x1189000 (region contains sub_1188170 lookup, sub_1188250 builder, sub_1188390 release, sub_1188400 init, sub_11884a0/sub_11886f0 callbacks, sub_1188780 builder+allocator user). [I]

----------------------------------------------------------------
[V] PROOF — (1) DESCRIPTOR BUILDER sub_1188250  [0x1188250..0x1188384), size 0x134, 3 xrefs in (sub_1152460, sub_1188170, sub_1188780) — PLUS sub_11884a0 MUTATIONS
----------------------------------------------------------------
sub_1188250 builds the type descriptor at the pointer passed in rcx/rax. sub_11884a0 (stored at desc+0x30) later mutates several of the same fields. One row per distinct field, all sites merged.

| descriptor field | size | site | instr | meaning [tag] |
|---|---|---|---|---|
| desc+0x00 | 8 | sub_1188250, sub_11884a0 | `0x11882a2  lea rdx,[0x128E48E0]` ; `0x11882a9  mov [rax],rdx` (=&global [0x128E48E0]) ; `0x11884fd  mov [rsi],rax` (=allocator result, sub_11884a0) | desc+0x00 [V] |
| desc+0x08 | 8 | sub_1188250 | `0x1188258  mov ecx,[0x128E48F8]` ; `0x11882ac  mov [rax+8],ecx` | hash ([0x128E48E4]/counter) [V] |
| desc+0x10 | 8 | sub_1188250, sub_11884a0 | `0x11882af  mov qword ptr [rax+0x10],0` (=0) ; `0x11884ad  lea rax,[0x1188560]` ; `0x11884b4  mov [rcx+0x10],rax` (=sub_1188560) | [V] |
| desc+0x18 | 4 | sub_1188250, sub_11884a0 | `0x11882b7  mov dword ptr [rax+0x18],0x80` (flags) ; `0x11884bf  lea rax,[0x11886D0]` ; `0x11884c6  mov [rcx+0x18],rax` (=sub_11886d0) | [V] |
| desc+0x20 | 4|8 | sub_1188250, sub_11884a0 | `0x11882be  mov qword ptr [rax+0x20],0x14` (count 0x14, qword) ; `0x11884b8  mov dword ptr [rcx+0x20],0x8DE632ED` (dword, overwrites) | count then hash [V] |
| desc+0x24 | 1 | sub_11884a0 | `0x11884ca  mov byte ptr [rcx+0x24],1` | =1 [V] |
| desc+0x28 | 8 | sub_1188250, sub_11884a0 | `0x11882c6  lea rcx,[0x1188170]` ; `0x11882cd  mov [rax+0x28],rcx` (=sub_1188170) ; `0x1188500  mov [rsi+0x28],rdi` (=arg2) | [V] |
| desc+0x30 | 8 | sub_1188250, sub_11884a0 | `0x11882d1  lea rcx,[0x11884A0]` ; `0x11882d8  mov [rax+0x30],rcx` (=sub_11884a0) ; `0x1188504  mov qword ptr [rsi+0x30],0` (=0, clears own slot) | [V] |
| desc+0x38 | 8 | sub_1188250, sub_11884a0 | `0x11882dc  mov qword ptr [rax+0x38],0` (=0) ; `0x118850c  lea rax,[0x1188540]` ; `0x1188513  mov [rsi+0x38],rax` (=sub_1188540) | [V] |
| desc+0x40 | 8 | sub_1188250 | `0x11882e4  lea rcx,[0x11886F0]` ; `0x11882eb  mov [rax+0x40],rcx` | =sub_11886f0 (member entry initializer) [V] |
| desc+0x48 | 16 | sub_1188250 | `0x11882ef  xorps xmm0,xmm0` ; `0x11882f2  movups [rax+0x48],xmm0` | zeroed +0x48..+0x57 [V] |
| desc+0x54 | 16 | sub_1188250 | `0x11882f6  movups [rax+0x54],xmm0` | zeroed +0x54..+0x63 [V] |
| desc+0x60 | 16 | sub_1188250, sub_1188780 | `0x11882f6  movups [rax+0x54],xmm0` (covers +0x60 within zero block) ; `0x1188961  cmp dword ptr [rax+0x60],0xD4C25870` (runtime read, sub_1188780) | zero at build; CE: 0xD4C25870 live [V] |
| desc+0x68 | 16 | sub_1188250, sub_1188780 | `0x11882fa  movups [rax+0x68],xmm0` (zeroed +0x68..+0x77, covers +0x70) ; `0x118896a  cmp qword ptr [rax+0x68],0` (runtime read, sub_1188780) | zero at build; CE: node ptr live [V] |
| desc+0x70 | 16 | sub_1188250 | `0x11882fa  movups [rax+0x68],xmm0` (covers +0x70 within zero block) | zeroed +0x68..+0x77 [V] |
| desc+0x78 | 8 | sub_1188250 | `0x11882fe  mov qword ptr [rax+0x78],0` | =0 at construction; member-container pointer filled at runtime [V] |

desc+0x60 has no separate store (covered by the +0x54 movups block); desc+0x70 likewise (covered by +0x68 block). Runtime fields +0x60, +0x68, +0x70, +0x78 are populated after sub_1188250 via the indirect callback/allocator path; no static `mov [desc+0x78],<container>` store was located [see CLOSES?].

----------------------------------------------------------------
[V] PROOF — (2) CALLBACK sub_11886f0 (stored at desc+0x40; the member entry initializer / "push_back one entry")  [0x11886f0..0x1188772), size 0x82, 0 direct xrefs (invoked indirectly via desc+0x40)
----------------------------------------------------------------
sub_11886f0(rax=entry ptr, r8, r9, rdx) initializes ONE new member entry at rax. One row per distinct entry field, all branch sites merged.

| entry field | size | site | instr | meaning [tag] |
|---|---|---|---|---|
| entry+0x00 | 8 | sub_11886f0 | `0x1188726  mov [rax],r8` ; `0x118874e  mov [rax],r8` ; `0x1188757  mov [rax],r9` | name ptr (r8 or r9 pointer) [V] |
| entry+0x10 | 8 | sub_11886f0 | `0x1188705  lea rcx,[0x1188560]` ; `0x118870c  mov [rax+0x10],rcx` ; `0x1188732  mov [rax+0x10],rcx` | =sub_1188560 (fn ptr) [V] |
| entry+0x18 | 8 | sub_11886f0 | `0x1188717  lea rcx,[0x11886D0]` ; `0x118871e  mov [rax+0x18],rcx` ; `0x118873d  mov qword ptr [rax+0x18],0` | =sub_11886d0 or 0 (fn ptr) [V] |
| entry+0x20 | 4 | sub_11886f0 | `0x1188710  mov dword ptr [rax+0x20],0x8DE632ED` ; `0x1188736  mov dword ptr [rax+0x20],0x8DE632ED` | constant hash 0x8DE632ED (NOT a per-member type tag) [V] |
| entry+0x24 | 1 | sub_11886f0 | `0x1188722  mov byte ptr [rax+0x24],1` ; `0x118874a  mov byte ptr [rax+0x24],3` ; `0x1188753  mov byte ptr [rax+0x24],4` | kind byte 1 (both null) / 3 (r8) / 4 (r9 only) [V] |
| entry+0x28 | 8 | sub_11886f0 | `0x118875a  mov [rax+0x28],rdx` | rdx (offset candidate; stored as qword, not u32) [V] |
| entry+0x30 | 8 | sub_11886f0 | `0x118875e  mov qword ptr [rax+0x30],0` | =0 [V] |
| entry+0x38 | 8 | sub_11886f0 | `0x1188766  lea rcx,[0x1188540]` ; `0x118876d  mov [rax+0x38],rcx` | =sub_1188540 (fn ptr) [V] |

Entry extent: the last store into a new entry is entry+0x38 (8-byte store), so the entry spans +0x00..+0x3F and the implied stride is 0x40. [I] — inferred from entry extent; the actual pointer arithmetic (rax = begin + i*stride) is performed by the indirect caller of desc+0x40, which was NOT located statically (0 direct xrefs to sub_11886f0).
Branch logic [V]: `0x11886f3  test r8,r8` / `0x11886f6  sete cl` ; `0x11886f9  test r9,r9` / `0x11886fc  sete r10b` ; `0x1188700  or r10b,cl` ; `0x1188703  jne short 0x118872B`. Both r8,r9 zero -> entry+0x00=r8(=0), entry+0x24=1. Else entry+0x18=0, entry+0x20=0x8DE632ED; if r8!=0: entry+0x24=3, entry+0x00=r8; else: entry+0x24=4, entry+0x00=r9. Common tail: entry+0x28=rdx, entry+0x30=0, entry+0x38=sub_1188540.
Field mapping assessment [I/?]: name (char* pointer) at entry+0x00 [V]; offset candidate rdx at entry+0x28 but stored as qword (task asks for u32) [V size mismatch]; type tag not cleanly identified — entry+0x20 is a constant hash, entry+0x24 is a kind byte (1/3/4) [?]. A clean "name / u32-offset / type-tag" mapping is NOT fully established [V].

----------------------------------------------------------------
[V] PROOF — DESCRIPTOR GLOBAL STORAGE (sub_1188170 builds descriptor at global 0x128E4858)
----------------------------------------------------------------
sub_1188170 (lookup function, also calls sub_1188250) at 0x118821e: `0x118821e  lea rcx,[0x128E4858]` ; `0x1188225  call 0x1188250` — sub_1188250 builds the descriptor at global RVA 0x128E4858 (its desc+0x00 = &0x128E48E0). [V] Note: CE found the live descriptor on the HEAP (scanned for &[0x128E48E0]); the static global 0x128E4858 vs the heap live instance may be template vs. live copy — the registry->descriptor link is not [V]-resolved statically.

----------------------------------------------------------------
RECIPE (best-effort; [V] where marked, [I]/[?] where not statically resolvable)
----------------------------------------------------------------
Static [V] elements:
  - registry object pointer: read qword [exe+0x1233E1A8] [V] (sub_11884a0 `0x11884ce mov rcx,[0x1233E1A8]`)
  - descriptor layout: built by sub_1188250; desc+0x78 field exists and is zeroed at construction [V]; desc+0x28=sub_1188170, desc+0x30=sub_11884a0, desc+0x40=sub_11886f0 [V]
  - member entry initializer: sub_11886f0 stores name-ptr at entry+0x00, rdx at entry+0x28, kind byte at entry+0x24, implied stride 0x40 [V stores / I stride]
Not [V]-located statically (blocking the complete recipe):
  - the store that makes desc+0x78 hold the member-container pointer (sub_1188250 only zeroes it; the container write is via the indirect callback/allocator path, not found [V])
  - container object layout: container+0x48=begin, container+0x50=end (CE only; sub_118710's +0x48/+0x50/+0x78 writes are hash-map buckets, not confirmed as this container) [?]
  - entry stride S pointer arithmetic (caller of desc+0x40 not found; implied 0x40 from entry extent) [I]

One-line recipe (CE-validated path, partially [V]):
  read qword [exe+0x1233E1A8] -> registry object; walk to the CloudLightingParameters descriptor (desc+0x00=&[0x128E48E0]); members = [desc+0x78]->container+0x48 begin, +0x50 end; stride S=0x40 [I]; name at +0x00 (char* pointer), offset at +0x28 (rdx, stored qword), type tag at +0x24 (kind byte 1/3/4) [?].

----------------------------------------------------------------
WHAT CHANGED
----------------------------------------------------------------
Created: docs/progress/oc_U-EM2c.md. No other file created or edited. No src/, header, Sigs.json, CMake, or hook edits. Static analysis only; no build, no game launch or attach.

----------------------------------------------------------------
CLOSES?
----------------------------------------------------------------
NO — the recipe is not complete entirely [V]. The single blocking fact: the member-container pointer at desc+0x78, the container's +0x48/+0x50 begin/end fields, and the entry stride S pointer-arithmetic are populated at runtime through indirect calls through the descriptor callback slots (+0x30=sub_11884a0, +0x40=sub_11886f0) and the IAT allocator thunk [0xF99FFA0]=sub_eea6040; no static `mov [desc+0x78],<container>` store, no container layout, and no push_back pointer arithmetic are [V]-located in the 0x1188xxx code. Everything else (registry global [0x1233E1A8], full descriptor layout via sub_1188250, CloudLightingParameters type-init via sub_1188400, both callbacks sub_11884a0/sub_11886f0 entry stores) is [V]-proven above.

----------------------------------------------------------------
TOOL REQUESTS
----------------------------------------------------------------
None — used only rdis.exe dis/fn/callers/fld and tools/sigs/verify_oc.py/delegate.py, all already present.
