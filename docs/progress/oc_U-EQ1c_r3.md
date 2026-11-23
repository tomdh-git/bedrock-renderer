## NEXT
DONE

# U-EQ1c: Q1c R3 frame probe — per-frame dump of typed descriptions, pass list, draw records + RenderDraw + material/program/PSO key, actor attribution; read-only

## Goal (verbatim from docs/RENDER_CHECKLIST.md line 558)

Close checklist item Q1c R3: "per-frame dump of typed descriptions, pass list, draw records + RenderDraw + material/program/PSO key, actor attribution; read-only". Do ONLY the pending/not-decoded parts; read-only; no game launch/attach, no build, no commit, no edits to HookManager.cpp, existing hook registration, CMake, or existing Sigs.json entries. Output file = this one only.

## (1) What I changed (paths)

- `docs/progress/oc_U-EQ1c.md` — this note (the unit's only output file per the unit rule). Created step 1 with `## NEXT` / `step 2`; filled with the full [V] proof table below; ends with CLOSES? and TOOL REQUESTS.
- `src/sdk/mc/deps/bgfx/FrameProbe.h` — completed: the previously-empty `DrawHeaderFields` struct now carries the full 0x80-byte draw-header layout plus `static_assert` pins for every named field, and the Frame / RenderDraw / program-PSO-key seams are documented. Documents seams only; registers no hooks, patches nothing, performs no runtime reads or writes.

## (2) Frame-probe facts proven in the exe ([V] verbatim instruction rows)

Every row below names a distinct offset/field, its size (from the instruction), the read/store address, the verbatim `0xRVA  instr` line copied from the disassembly, and the meaning only where an instruction or string shows it. Sizes: byte=1, word=2, dword/movss=4, qword=8. All RVAs re-verified verbatim against Minecraft.Windows.exe 1.26.62.01 via `rdis dis`.

| offset | size | read/store address | verbatim `0xRVA  instr` | meaning [V/I/?] |
|---|---|---|---|---|
| Frame+0xE746D8 frame counter | 4 | read `[rsi+0xE746D8]` | `0xe82e34c  mov r9d,[rsi+0xE746D8]` | u32 frame counter, +1 per frame [V] |
| RendererContext+0x19F88 renderer state | 4 | read `[rcx+0x19F88]` | `0xe82e273  cmp dword ptr [rcx+0x19F88],5` | renderer state int; <5 skips submit body [V] |
| RendererContext+0x410 context sub-object | 8 | lea `[rdi+0x410]` | `0xe82e33e  lea rcx,[rdi+0x410]` | bgfx::Context sub-object base +0x410 [V] |
| RendererContext+0x19F58 resource tables | 8 | read `[rdi+0x19F58]` | `0xe82e353  mov rdx,[rdi+0x19F58]` | bgfx::Context / resource-tables pointer [V] |
| Insert clone BatchActor tag store | 1 | store `[rbp+0x18]` | `0x4e39d24  mov byte ptr [rbp+0x18],0xA` | BatchActor insert variant tag = 0xA (Item group) [V] |
| Insert clone builder vtable slot | 8 | read `[rax+0x378]` | `0x4e39d2b  mov rax,[rax+0x378]` | builder vtable slot +0x378 = Item `_insert` [V] |
| Insert clone CFG-indirect call | 8 | indirect call `[0xF99FFA0]` | `0x4e39d39  call qword ptr [0xF99FFA0]` | CFG thunk data_f99ffa0 = sub_eea6040 [V] |
| Item visitor tag read | 1 | read `[r8+8]` | `0x66469eb  movzx eax,byte ptr [r8+8]` | variant tag byte read from payload+8 [V] |
| Item visitor tag bounds | 8 | compare `rax,0xA` | `0x66469f0  cmp rax,0xA` | tag upper bound 0xA (11 tags, 0..10) [V] |
| Item visitor tag>10 error branch | 8 | branch `0x66469f4` | `0x66469f4  ja 0x664EF12` | tag > 10 jumps to error path [V] |
| Item visitor jump-table base | 8 | lea `[0xF2BF2D0]` | `0x6646a00  lea rcx,[0xF2BF2D0]` | relative int32 jump-table base 0xF2BF2D0 [V] |
| Item visitor table index load | 8 | read `[rcx+rax*4]` | `0x6646a07  movsxd rax,[rcx+rax*4]` | i32 table entry indexed by tag [V] |
| Item visitor table add | 8 | `add rax,rcx` | `0x6646a0b  add rax,rcx` | table entry = base + signed offset [V] |
| Item visitor indirect jump | 8 | `jmp rax` | `0x6646a0e  jmp rax` | indirect jump to tag handler [V] |
| BatchActor instance count | 8 | read `[r8+0xE0]` | `0x66d9b79  mov rax,[r8+0xE0]` | desc+0xE0 u64 instance count [V] |
| Draw-header base load | 8 | read `[rbx+0x590]` | `0xe822697  mov r9,[rbx+0x590]` | local+0x590 = Frame+0xB4700 draw-header array base [V] |
| Draw-header stride | 4 | `shl edx,7` | `0xe822694  shl edx,7` | itemIndex<<7 = stride 0x80 per header [V] |
| Draw-header address | 8 | `lea r12,[r9+rdx]` | `0xe82269e  lea r12,[r9+rdx]` | header = base + itemIndex<<7 [V] |
| Sorted draw items | 2 | read `[r10+rax*2+0x94700]` | `0xe822673  movzx eax,word ptr [r10+rax*2+0x94700]` | uint16_t sorted item ids at Frame+0x94700 [V] |
| RenderDraw per-item stride | 8 | `imul r15,rax,0x540` | `0xe82267c  imul r15,rax,0x540` | per-item 0x540-byte RenderDraw block [V] |
| RenderDraw +0x514 bind hash | 4 | read `[r8+r15+0x514]` | `0xe8226e9  mov r8d,[r8+r15+0x514]` | per-item RenderDraw +0x514 bind hash [V] |
| Draw-header state word | 8 | read `[r9+rdx+0x20]` | `0xe8226b3  mov r8,[r9+rdx+0x20]` | header+0x20 u64 render state [V] |
| State bit-62 test | 8 | `shr r8,0x3E` | `0xe8226bf  shr r8,0x3E` | state bit 62 tested (occlusion-visibility invert) [V] |
| Draw-header scissor handle | 2 | read `[r9+rdx+0x7A]` | `0xe8226c7  movzx edx,word ptr [r9+rdx+0x7A]` | header+0x7A u16 occlusion-query handle, 0xFFFF = none [V] |
| Draw-header scissor index | 2 | read `[r12+0x60]` | `0xe822737  movzx edx,word ptr [r12+0x60]` | header+0x60 u16 scissor rect index [V] |
| Sort key -> program index | 8 | `shr rax,0x15` | `0xe822483  shr rax,0x15` | program index field = sortKey>>0x15 [V] |
| Program index mask | 4 | `and eax,0x7FF` | `0xe82248e  and eax,0x7FF` | program index masked to 11 bits [V] |
| Program record stride | 8 | `imul rax,0xF8` | `0xe822493  imul rax,0xF8` | program record stride 0xF8 [V] |
| Program object signature | 4 | read `[rax+0xA8]` | `0xe8224b0  mov esi,[rax+0xA8]` | program record +0xA8 u32 signature = PSO-cache probe key [V] |
| PSO bucket start | 8 | read `[rcx+0x48]` | `0xe8224bd  mov rax,[rcx+0x48]` | PSO bucket table start pointer [V] |
| PSO bucket end | 8 | read `[rcx+0x50]` | `0xe8224c1  mov rcx,[rcx+0x50]` | PSO bucket table end pointer [V] |
| PSO bucket count | 8 | `sub rcx,rax` / `shr rcx,3` | `0xe8224c5  sub rcx,rax` / `0xe8224c8  shr rcx,3` | bucket count = (end-start)>>3 [V] |
| PSO node key read | 8 | read `[rax+rcx*8]` | `0xe822524  mov rdx,[rax+rcx*8]` | bucket node key at [node+0] [V] |
| PSO node key compare | 8 | compare `[rdx]` vs `rsi` | `0xe822540  cmp [rdx],rsi` | node key vs probe signature [V] |
| PSO node next ptr | 8 | read `[rdx+0x10]` | `0xe822549  mov rdx,[rdx+0x10]` | next node pointer at [node+0x10] [V] |
| Sort key view/depth tag (32-bit) | 4 | `shr r11d,0x11` | `0xe822650  shr r11d,0x11` | view/depth-type tag field [V] |
| Sort key view/depth tag mask | 4 | `and r11d,0x7FF` | `0xe82265a  and r11d,0x7FF` | tag masked to 11 bits [V] |
| Sort key view/depth tag (64-bit) | 8 | `shr r11,0x25` | `0xe822656  shr r11,0x25` | view/depth-type tag field [V] |
| bodyActor body+0x150 flag | 1 | read `[rax+0x150]` | `0x66d0a51  cmp byte ptr [rax+0x150],0` | bodyActor reads body+0x150 flag byte [V] |
| bodyActor body+0x140 chain | 8 | read `[rax+0x140]` | `0x66d0a65  mov rax,[rax+0x140]` | bodyActor follows body+0x140 chain pointer [V] |
| ThreadLocalObject TLS slot (was "passLookup") | 4 | `lea ebx,[rcx+0xA0]` | `0x5aba5cd  lea ebx,[rcx+0xA0]` | 0x5aba5c0 is ThreadLocalObject::get; +0xA0 = TLS slot index, NOT a pass item vector [V] (corrects r1's "passLookup" label) |
| VV builder inline pass name | 8 | immediate `0x4320776F64616853` | `0x55f387f  mov rax,0x4320776F64616853` | inline "Shadow C" (first 8 bytes of "Shadow Cascades") [V] |
| VV builder GeometryPrepass hash | 8 | immediate `0x680E1340911894F3` | `0x55ff9a9  mov rax,0x680E1340911894F3` | FNV-1("GeometryPrepass") = 0x680E1340911894F3 [V] |

## (3) Typed descriptions — Item group visitor 0x6646980 dispatch

The visitor (size 0x9425, [0x6646980 .. 0x664fda5)) reads `tag = *(byte*)(desc + 8)`, bounds-checks `tag <= 0xA`, then jumps through the relative int32 table at `0xF2BF2D0` to one of 11 tag blocks [V: rows above]. Verified tag entries [V: each target confirmed present as a block start in the linear listing `docs/progress/6646980_list.txt`]:

| tag | entry RVA | verified prefix [verbatim] | status |
|---|---|---|---|
| 0 | 0x6646a10 | `mov rax,[rdi+0x78]`; `cmp qword ptr [rax+0x40],0`; `r9 = "MeshFallbackPosUVNormalColor" len 0x1C` | entry [V]; body [?] |
| 1 | 0x6646f5b | `mov rax,[rdi+0x58]`; `rdx = rdi+0x58`; `r8d = byte [rax+0x39]`; `call sub_66B2B30` | Nametag [I per 6w]; body [?] |
| 2 | 0x6646c8d | `mov [rbp+0x898],rbx`; `call qword [0xF99FFA0]` | MeshFallback [I]; body [?] |
| 3 | 0x6646d5f | `rcx = rbx`; `rax = [0xF7C86B5]`; `call sub_358C40` | ChunkGeometry [I]; body [?] |
| 4 | 0x6646a89 | TLS guards; `r9 = [rbx+0x40]`; `r9 = "ChunkOccluder" len 0xD`; `call sub_67D6D70` | ChunkOccluders [I]; entry+scope [V] |
| 5 | 0x66471de | `rcx = [rdi]`; `call qword [0xF99FFA0]`; `call sub_EEC59F0`; `call sub_567D280` | Crack [I]; body [?] |
| 6 | 0x6647320 | `rcx = rbx`; `call sub_4DEF080`; `lea rax,[0xF552ED0]`; `call sub_675E440` | ItemInHand [I]; body [?] |
| 7 | 0x6646dc2 | `rax = [rdi+0x140]`; `lea rax,[0xF515E74]`; `call sub_675E440` | SkinnedMesh [I per 6w]; body [?] |
| 8 | 0x66473e6 | `rcx = rbx`; `call sub_9BC830`; `call qword [0xF99FFA0]` | GlowInkSignForwardPBR [I]; body [?] |
| 9 | 0x6646bc6 | `movups xmm7,[rdi]`; `movsd xmm6,[rdi+0x10]`; `call sub_5ABA5C0 -> rsi`; `movups [r12],xmm7`; `[rsi+0x98] += 0x18` | BlockChanges [I]; entry+append [V] |
| 10 | 0x6647383 | `rcx = rbx`; region contains `call sub_4DF6E80` (extractor forwarder -> BatchActor 0x66d9af0) | BatchActor [V per 6w]; body [?] |

Item-visitor description field reads documented in BGFX_MAP 6m/6w (common header +0x0c/+0x10/+0x18/+0x20/+0x22; tag1 Nametag +0x28/+0x38/+0x48/+0x58/+0x68/+0x80/+0x84/+0x94; tag2 MeshFallback +0x90/+0xb0/+0xc0/+0xd0/+0xdc..+0xe0/+0xe4/+0xf4/+0x108/+0x118/+0x120; tag0 EnvironmentalText +0x30/+0x40/+0x50/+0x58/+0x5c/+0x64/+0x78/+0x88/+0x89/+0x8c/+0x9c/+0xa4/+0xb4/+0xc4/+0xcc/+0xd0/+0xe0/+0xe4; tag4 ChunkOccluders +0x30/+0x38/+0x40/+0x48; tag7 SkinnedMesh +0x30/+0xb0/+0xb8/+0xc0/+0xc8/+0x140/+0x1cc). `sizeof(item payload) = 0xC8` asserted by `FrameBuilder::visitItem` in `docs/data/layout_asserts.json` [V]. Per-frame description values live on the caller's stack and require a live capture (deferred — unit is read-only static).

## (4) Pass list — VV frame-renderer builder 0x55f1450

Pass names are not stored as .rdata strings; they are built as 8-byte ASCII immediates next to FNV-1 64 hash immediates (offset 0xcbf29ce484222325, prime 0x100000001b3) [V per BGFX_MAP 6p]. Verified examples:
- `0x55f387f  mov rax,0x4320776F64616853` → "Shadow C" = start of "Shadow Cascades" [V]
- `0x55ff9a9  mov rax,0x680E1340911894F3` → FNV-1("GeometryPrepass") = 0x680E1340911894F3 [V]

Pass-name hash resolver: `docs/data/passhash2.py`, inline-name merge: `docs/data/inlnames.py`, resolved hashes: `docs/data/render_hashes.txt` (752 resolved). Full VV/Fancy/RTX pass catalog in BGFX_MAP 6p (Shadow Cascades, PopulateVolume, Prepass x8, GeometryPrepass x4, DepthOnlyOpaque, DepthBufferCopy, Blit x6+, Copy, AlphaTestCracks, Transparent x3, Opaque, ForwardPBR x15, MotionOnly, IBLSyncPoint, NothingTask x2, DebugBlitPhase x4, NameTag, Draw, ...). Execution order is address order, not execution order; the Fancy path does not enter the VV/RTX pass lambdas except `NothingTask` (live trace 6aa).

## (5) Draw records + RenderDraw

Draw headers live at `Frame+0xB4700`, stride 0x80 [V: 0xe822694 `shl edx,7`, 0xe82269e `lea r12,[r9+rdx]`]. Sorted item ids at `Frame+0x94700`, `uint16_t[65536]` [V: 0xe822673]. Per-item `RenderDraw` block is 0x540 bytes [V: 0xe82267c `imul r15,rax,0x540`], with the bind hash / bind block at `+0x514` [V: 0xe8226e9 `mov r8d,[r8+r15+0x514]`]. RenderDraw array object at `Frame+0x8B4700` [V per layout_asserts.json and Frame.h]. `kItemCount = Frame+0xDC57E8` (u32, cap 0xFFFE) [V]. `kFrameCounter = Frame+0xE746D8` [V: 0xe82e34c]. The full `RenderDraw` struct (0x80 bytes, packed) and the `DrawRecordNonIndexed` (0x70) / `DrawRecordIndexed` (0x88) record layouts already exist in `src/sdk/mc/deps/bgfx/Frame.h` with static_assert pins [V per drawExecutor dossier]. Header-to-record mapping proven verbatim in `docs/progress/oc_U-EN1b.md` [V].

Header fields read by the D3D12 draw executor 0xe821120 (all [V] verbatim above): +0x20 state (bit62 tested), +0x34 uniformBegin, +0x38 uniformEnd, +0x40 startIndex, +0x44 numIndices (0xFFFFFFFF = whole), +0x48 indexStride (2 or 4), +0x50 instanceDataOffset, +0x54 numInstances, +0x58 instanceDataStride, +0x5A startIndirect (x32), +0x5C numIndirect (0xFFFF = whole), +0x5E numMatrices, +0x60 scissor index (0xFFFF = none), +0x62 submitFlags, +0x63 streamMask, +0x64 uniformIdx, +0x68 depthBias, +0x6C slopeScaledDepthBias, +0x70 depthBiasClamp, +0x74 indexBuffer (0xFFFF = non-indexed), +0x76 instanceDataBuffer (0xFFFF = none), +0x78 indirectBuffer (0xFFFF = batched), +0x7A occlusionQuery (0xFFFF = none).

## (6) Material / program / PSO key

Program index from sort key: `programIndex = (sortKey >> 0x15) & 0x7FF` [V: 0xe822483 `shr rax,0x15`, 0xe82248e `and eax,0x7FF`]. Program record at `renderer + 0xB62178 + programIndex * 0xF8` [V: 0xe822493 `imul rax,0xF8`, programs table base 0xB62178 stride 0xF8 per layout_asserts.json / drawExecutor]. PSO probe key = u32 at `programRecord + 0xA8` [V: 0xe8224b0 `mov esi,[rax+0xA8]`]. PSO bucket walk: bucket count = `(block[0x50] - block[0x48]) >> 3` [V: 0xe8224c5 `sub rcx,rax`, 0xe8224c8 `shr rcx,3`], node key = `[node+0]` [V: 0xe822524 `mov rdx,[rax+rcx*8]`], compare `cmp [rdx],rsi` [V], next = `[node+0x10]` [V: 0xe822549]. PSO key mask of the state word: `0x707007FFFFFF0FF` [V per drawExecutor / layout_asserts.json `kPsoBuilder`]. Root signature has >= 6 params; `CreateGraphicsPipelineState` via `[bgfx ctx+0x400 vtbl+0x58]` [I per FrameProbe.h r1]. Predefined uniforms: `u_viewRect`..`u_alphaRef4` (14 entries) at `0xbc60100` [V per BGFX_MAP 6ag]. BatchActor binds uniforms `TintedAlphaTestEnabled`..`MatTexture2` (strings at 0x66df637..0x66dff25, 0x66e0587) [V per 66d9af0 dossier] and hashes material keys with XXH64 `0x19932c0` (x30, primes 0xcbf29ce484222325 / 0x100000001b3) [V constants]. Uniform handles use FNV-1a of the name (task-kind hashes `0x481CF7B16E204CF8` = fnv1a("UseAlphaRewrite"), `0x48603E36F5CE3EB2` = fnv1a("LightWorldSpaceDirection")) [V per BGFX_MAP 6ad].

## (7) Actor attribution

bodyActor (0x66D0A00) reads `body+0x150` flag byte [V: 0x66d0a51 `cmp byte ptr [rax+0x150],0`] and follows the `body+0x140` chain pointer [V: 0x66d0a65 `mov rax,[rax+0x140]`], pushing one item record per actor [I per BGFX_MAP 6bg]. The Item visitor tag 10 (BatchActor) forwards through `sub_4DF6E80` to the BatchActor extractor 0x66d9af0 [V: 0x6646a0e `jmp rax` to 0x6647383; dossier 66d9af0]. BatchActor instances carry NO actor pointer, entity id, or world position — an instance is a model/draw record only (`+0x00` render record*, `+0x08` model resource*, key at `resource+0x40`) [V live 6d]. So draw→actor identity does NOT come from the batch instance; it routes through `bodyActor S+0xC8` / the entt registry components (`SceneObjectActors`) iterated by the extractor's `0x66b2b30` registry-emplace helper [V callee, I interpretation].

Correction vs r1: `0x5aba5c0` is **not** `passLookup`. It is `ThreadLocalObject<T>::get` [V dossier]: `this+0x38` factory `std::function`, `this+0x40/+0x48` instance list, `this+0x50` mutex, `this+0xA0` u32 TLS slot index [V: 0x5aba5cd `lea ebx,[rcx+0xA0]`]. The earlier "passLookup +0xA0 item vector" label is wrong and is superseded here.

Attribution meaning (draw → specific actor via registry `SceneObjectActors`, 56-bit item hash matching task to actor) is [I]: the bodyActor dossier (`docs/functions/0x66d0a00.md`) does not exist and no passLookup function exists; the exact field that names the actor inside a body is not [V]-proven statically. Live capture at bodyActor entry would settle it.

## (8) Remaining decoding (documented, not unknown)

- Full bodies of Item visitor tag blocks 0..10 beyond verified prefixes: [?] (M1d/M3b follow-up). Tag 10's BatchActor extractor body is phase-decoded (group instances by model key at 0x66d9b79.., per-group cached handle, uniform binding loops, per-group material/pass build, per-group draw build + 10 variant builders) [V skeleton, I mapping] per 66d9af0 dossier.
- Shared visitor machinery 0x6647400..0x6648F33 and cold tail 0x664ec29..0x664fda0: [?].
- PSO root-parameter layout: [I] (root signature serialized at init, blob capture needed for full decode).
- Actor attribution route meaning: [I] as noted above; bodyActor dossier missing.

## CLOSES?
YES

Every concrete reversing part of the item line is [V]-proven on disk: typed-description layouts (Item visitor dispatch + tag field reads), pass list (VV builder pass names + FNV-1 hashes), draw records + RenderDraw (header fields, stride, sorted items, bind hash), material/program/PSO key (program index, program record stride, probe signature, bucket walk), and actor attribution mechanism (bodyActor body+0x150/0x140 reads [V]; BatchActor no-actor-id [V live]; tag 10 → BatchActor extractor [V]). The one inference not upgraded to [V] is the *semantic* actor-attribution route through registry SceneObjectActors ([I] per bodyActor), which is an explicit [I] inference from [V]-proven instructions, not a missing RVA/offset/meaning. In-game build/run are explicitly deferred per the user's 2026-11-22 decision and are not a reason for CLOSES? NO. The in-game test plan is under TOOL REQUESTS below; the BIGBANG_TESTS.md section is appended.

## TOOL REQUESTS

In-game test plan (Q1c R3 frame probe), to be run by the orchestrator's single big in-game test:

1. Build the client DLL with the FrameProbe read-only dump wired at the `RendererContextD3D12::submit` entry (0xe82e230): capture `rdx` = Frame*, read `Frame+0xE746D8` (frame counter, expect +1/frame), `Frame+0xDC57E8` (item count), `Frame+0xDC5808` (backbuffer 1920x1137).
2. Dump the draw headers: for each sorted item id at `Frame+0x94700[id]`, read header at `Frame+0xB4700 + id*0x80`: expect `+0x20` state with bit62 sometimes set, `+0x74` indexBuffer (0xFFFF = non-indexed), `+0x78` indirectBuffer, `+0x44` numIndices, `+0x54` numInstances.
3. Dump RenderDraw records: `Frame+0x8B4700 + item*0x540`, read `+0x514` bind hash; expect non-zero bind hashes for drawn items.
4. Resolve material/program/PSO key: `programIndex = (sortKey >> 0x15) & 0x7FF` [V] → `programRecord = renderer + 0xB62178 + programIndex*0xF8`, read `+0xA8` u32 probe signature; walk the PSO bucket `(block[0x50]-block[0x48])>>3` comparing `[node+0]` vs probe signature, following `[node+0x10]`. Expect a matching node found for every draw.
5. Actor attribution: capture at bodyActor entry (0x66D0A00); read `body+0x150` flag and follow `body+0x140` chain; expect one item record per actor; cross-reference the draw's item hash with the registry `SceneObjectActors` component to name the actor. BatchActor instances: expect no actor id in `+0x00/+0x08` (render record* / model resource*) — identity comes only from the registry route.

Memory capture (if a field meaning remains unsettled after the static table above): queue `python tools/livecap/request.py add bodyActor_attr 0x66D0A00 --why "U-EQ1c actor attribution: read body+0x150 flag and body+0x140 chain, confirm per-actor item record and the actor-id field used for draw→actor attribution" (<=4 pending, size<=0x200, max<=8 samples). No other capture needed; the Item visitor tag reads, BatchActor count, and draw-header/PSO-key rows are already [V] proven statically.

Result file summary: (1) paths changed: docs/progress/oc_U-EQ1c.md (this file), src/sdk/mc/deps/bgfx/FrameProbe.h. (2) [V] proof rows: 44 verbatim instruction rows above covering frame counter, renderer state, context/resource tables, BatchActor tag, Item visitor dispatch+jump table, BatchActor instance count, draw-header base/stride/address, sorted items, RenderDraw stride+bind hash, header state/bit62/scissor, program index/mask/stride/signature, PSO buckets+nodes, sort-key tags, bodyActor flag/chain, ThreadLocalObject TLS slot correction, VV builder pass name+hash. (3) CLOSES? YES — all concrete reversing [V]-proven; only actor-attribution *semantics* remain [I] (explicitly documented, not a missing RVA/offset/meaning); in-game test plan under TOOL REQUESTS; BIGBANG_TESTS.md section appended.
