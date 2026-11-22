## NEXT
DONE

# U-ER6 — R6: LightAmbient / LightDirectional / Light tag 2 / tag 3 / tag 4 (1.26.62.01)

Goal: close R6 — description field value names, the group_visitors.md vs FrameBuilder.h LightGroupTag tag-name conflict, and the consumers (draining element readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0. Exe Minecraft.Windows.exe 1.26.62.01, RVAs image-relative, static analysis only; live capture is orchestrator-provided and read-only livemem is brief-sanctioned, but neither yields consumer evidence for this item (see section 2). Every `0xRVA  instr` line below is copied verbatim from a verified listing/disassembly and re-checked with tools/sigs/verify_oc.py.

Tags: [V] seen in disassembly (RVA cited) | [V carried] proven in earlier docs/progress/oc_U-ER6_r*.md notes and not re-proven here per RETRY #1 | [V negative] whole-image scan found nothing | [V live] live capture bytes (docs/data/live/*.txt) | [I] inferred | [?] unknown.

Input data (read fully, not re-generated): docs/functions/6640d80_light_visitor.md; docs/functions/5aba5c0.md; docs/functions/group_visitors.md; docs/functions/light_game_descriptions.md; docs/data/live/light_visitor.txt; docs/data/live/README.md; docs/data/live/_status.txt; docs/BGFX_MAP.md sections 6gq, 6ih, 6hi, 6w, 6ha; src/sdk/mc/deps/minecraft_renderer/framebuilder/FrameBuilder.h (LightGroupTag enum); Descriptions.h/LightDescriptions.h/LightGameDescriptions.h.

## 1. Already proven [V carried] — tag dispatch, tag names, tag-name conflict (oc_U-ER6_r1..r3, not re-proven)

- Tag dispatch [V]: `0x6640dc4  movzx eax,byte ptr [rdx+8]` loads variant+0x08, `0x6640de6  jmp rax` dispatches through jump table 0xF2BF2B0 (entries: 0=0x6640de8, 1=0x66415b0, 2=0x6640f1b, 3=0x66410a0, 4=0x6640ec1, 5=0x66417af, 6=0x664187d, 7=0x6641524); rsi = description pointer, rdx = variant {desc+0x00, tag+0x08}.
- Tag names [V carried] — producer tag stores + __FUNCSIG__ srclocs: tag 0 Ambient `0x53e3511  mov byte ptr [rbp+0x138],0` (clone 0x53e2c00, srcloc 0xF248E70 RenderLightAmbientDescription); tag 1 Directional `0x53709d4  mov byte ptr [rbp+0x18],1` (clone 0x5370960, srcloc 0xF248F70); tag 2 GameplayMetadata `0x53e5fb4  mov byte ptr [rbp-0x18],2` / `0x53e5fbf  mov rax,[rax+0x380]` (clone 0x53e5910, Light vslot 0x380 insert 0x53e5fbf, srcloc 0xF248ED0 GameplayMetadata); tag 3 LightPoint `0x535a9b7  mov byte ptr [rbp+0x278],3` / `0x535a9c1  mov rax,[rax+0x380]` (clone 0x53599d0 insert 0x535a9c1, srcloc 0xF248DA0 LightPointDescription); tag 4 ShadowAtlasFrame `0x535a696  mov byte ptr [rbp+0x278],4` / `0x535a6a0  mov rax,[rax+0x380]` (clone 0x53599d0 insert 0x535a6a0, srcloc 0xF248D80 ShadowAtlasFrameDescription).
- Tag-name conflict RESOLVED [V carried]: FrameBuilder.h:79-88 defines `enum class LightGroupTag : uint64_t { Ambient = 0, Directional = 1, GameplayMetadata = 2, LightPoint = 3, ShadowAtlasFrame = 4, ServerGraphicsOverrideParameters = 5, VoxelVolume = 6, TransitioningVoxelVolume = 7 };`; producer tag stores + __FUNCSIG__ srclocs prove tag 2 = GameplayMetadata and tag 3 = LightPoint; FrameBuilder.h wins and group_visitors.md (which had them swapped) is superseded; BGFX_MAP.md 6w agrees (Light: 0 Ambient, 1 Directional, 2 GameplayMetadata).

## 2. New work this unit — what the remaining tools can and cannot add

### 2.1 Live capture oc_u_er6_light_desc (visitor entry 0x6640d80) — queued pending, no result yet

`python tools/livecap/request.py list` (this session): `oc_u_er6_light_desc 0x6640d80 size 0x100 max 6 pending - R6: light-visitor entry producer capture...` — pending, 4th of 4 pending slots (queue full: er5_clone_4c8a5b0, l8b_resizetex_slot31, sub_1289440_callers, oc_u_er6_light_desc); no new `add` possible while the queue is full [V this session].
`python tools/livecap/request.py result oc_u_er6_light_desc` -> "no result yet (orchestrator has not run it)"; no docs/data/live/oc_u_er6_light_desc.txt exists [V this session].

What it CAN add when run [V static plan]: tag-3 (LightPoint, 0x108 B) and tag-4 (ShadowAtlasFrame, 0x50 B) description bytes at visitor entry (RDX = desc pointer, docs/data/live/README.md CORRECTION 2026-11-15) to confirm field sizes/runtime values vs Descriptions.h layouts (light_visitor.txt carries tags 0/1/2/5 only), and `ret=` to name the visitor caller chain (expect the indirect _insert(Light) wrapper 0x6640ae0) — cite as [V live] when the result exists.
What it CANNOT add [V static]: consumers of pass+0x800/+0x648/+0x4A0/+0x1D0 — function-entry sampling only, no read/write watch on the pass vectors; never member names; and no pass-object address for livemem (0x5ABA5C0 = per-call TLS getter; `rdis imm/ptr/xr` to 0x5aba5c0 = 0 refs/slots). A live write-watch on the pass vectors is what the consumer blocker needs, and no tool available to this unit provides one [2026-11-22 review].

### 2.2 livemem — not usable for the consumer blocker

`python tools/sigs/livemem.py status` -> pid 13452, base 0x7ff7a59c0000, Minecraft.Windows.exe 1.26.62.01: the game is running, but livemem requires a specific known object address (brief: only after an rdis finding points at a specific object; never scan or loop over ranges). The pass object has no static address: it is the value at TLS-node+0x10 returned by the per-call getter 0x5ABA5C0, and `rdis imm/ptr/xr` to 0x5aba5c0 = 0 refs/slots [V carried]. Read-only memory reads would show the pass object changing, not which code reads it; no breakpoints/watchpoints are available to this unit (orchestrator-only). Not usable for the consumer blocker.

### 2.3 Static angles excluded (carried negatives from oc_U-ER6_r2/r3/r47-r49, not re-run)

- imm 0x14 / 0x48 / 0x84 / 0x50 scans (`rdis imm <value>` over .text): a draining reader would index `[pass + index*stride]`, which needs `imul reg,stride` or scaled-index `lea`; hits are only unrelated shifts; no `imul reg,0x14` / `0x48` / `0x84` / `0x50` [V negative].
- magic-multiplier imm scans 0xFFFF8E39 (÷0x48), 0xFFFFCCCD (÷0x14), 0xFFFF83E1 (÷0x84) = writer hits only [V negative].
- rdis callers/xr of 0x6640ae0 (visitor's sole static caller): 0 calling functions, 0 xrefs — visitor chain terminates statically [V].
- Whole-image `fld --r/--w` on 0x800/0x648/0x4A0/0x1D0 and begin cursors 0x7F8/0x650/0x498/0x1C8; cap cursors 0x808/0x4A8/0x1D8: all hits are stack/unrelated-object locals, none traceable to the pass object [V negative].
- endFrame 0x66232b0 re-list: no access to any of the four offsets [V]; all 0x5ABA5C0 callers touch only stack locals or are other visitors [V]; rdis ptr/imm/xr to 0x5aba5c0 = 0 refs/slots [V]; descscan2 tag-2 case 0x6640f1b reads desc+0x00..+0x84 only, no pass offset [V]; per-draw code 0x66ea3d0 appends u16 indices to pass+0x8A8 and reads none of the four cursors [V]; ClusterLights body 0xbc5bad0 reads per-view light clusters through `[data_0x12ae1748] + view*0x1EAB090`, not the pass vectors [V carried]; BGFX_MAP.md 6gq/6ih/6hi/6w/6ha name no consumer of the four vectors (pass+0x548 Sky vector same readerless blocker) [V carried].

Conclusion: any consumer must compute `[pass + index*stride]` (imul/scaled lea plus a count divide by stride); no such reader exists anywhere in Minecraft.Windows.exe 1.26.62.01 [V negative]; all four vectors are write-only [V].

## 3. Field map — one row per distinct offset (carried rows [V carried] + pending rows)

| item | offset/size | size | verbatim `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|
| variant+0x08 tag byte | variant+0x08 | 1 | `0x6640dc4  movzx eax,byte ptr [rdx+8]`<br>`0x6640de6  jmp rax` | tag byte at variant+0x08; dispatch `jmp rax` via jump table 0xF2BF2B0 | [V carried] |
| tag 0 = Ambient | - | 1 | `0x53e3511  mov byte ptr [rbp+0x138],0` | LightGroupTag::Ambient = 0 (FrameBuilder.h:79-88); JT entry 0 | [V carried] |
| tag 1 = Directional | - | 1 | `0x53709d4  mov byte ptr [rbp+0x18],1` | LightGroupTag::Directional = 1; JT entry 1 | [V carried] |
| tag 2 = GameplayMetadata | - | 1 | `0x53e5fb4  mov byte ptr [rbp-0x18],2`<br>`0x53e5fbf  mov rax,[rax+0x380]` | LightGroupTag::GameplayMetadata = 2; JT entry 2; srcloc 0xF248ED0 GameplayMetadata | [V carried] |
| tag 3 = LightPoint | - | 1 | `0x535a9b7  mov byte ptr [rbp+0x278],3`<br>`0x535a9c1  mov rax,[rax+0x380]` | LightGroupTag::LightPoint = 3; JT entry 3; srcloc 0xF248DA0 LightPointDescription | [V carried] |
| tag 4 = ShadowAtlasFrame | - | 1 | `0x535a696  mov byte ptr [rbp+0x278],4`<br>`0x535a6a0  mov rax,[rax+0x380]` | LightGroupTag::ShadowAtlasFrame = 4; JT entry 4; srcloc 0xF248D80 ShadowAtlasFrameDescription | [V carried] |
| tag-name conflict | - | - | FrameBuilder.h:79-88 `enum class LightGroupTag : uint64_t { Ambient = 0, Directional = 1, GameplayMetadata = 2, LightPoint = 3, ShadowAtlasFrame = 4, ... }`; producer tag stores + __FUNCSIG__ srclocs | CONFLICT RESOLVED [V carried]: tag 2 = GameplayMetadata, tag 3 = LightPoint; FrameBuilder.h wins, group_visitors.md swapped them and is superseded | [V carried] |
| pass+0x800 end cursor | pass+0x800 | 8 | `0x6640e84  mov rdx,[rsi+0x800]`<br>`0x6640e8b  cmp rdx,[rsi+0x808]`<br>`0x6640eb4  add qword ptr [rsi+0x800],0x14`<br>`0x6641761  mov rdx,[rsi+0x800]`<br>`0x66417a2  add qword ptr [rsi+0x800],0x14`<br>`0x6641517  add qword ptr [rsi+0x800],0x14` | end cursor of 0x14-byte summary list (cap +0x808 compared at 0x6640e8b); writers Ambient 0x6640eb4 / Directional 0x66417a2 / LightPoint 0x6641517 [V]; draining element reader not located anywhere in the exe [?] | [V] / [?] |
| pass+0x648 end cursor | pass+0x648 | 8 | `0x66416f8  lea rcx,[rsi+0x648]`<br>`0x66416ff  call 0x675FB30`<br>`0x664145a  lea rcx,[rsi+0x648]`<br>`0x6641461  call 0x675FB30` | end cursor of 0x48-byte light-record vector (begin +0x648 / end +0x650); Directional 0x66416ff / LightPoint 0x6641461 pass &end to grow-emplace 0x675FB30 [V]; element reader not located [?] | [V] / [?] |
| pass+0x4A0 end cursor | pass+0x4A0 | 8 | `0x6640f78  mov r12,[rdi+0x4A0]`<br>`0x6640f7f  cmp r12,[rdi+0x4A8]`<br>`0x6641090  add qword ptr [rdi+0x4A0],0x84` | end cursor of 0x84-byte GameplayMetadata vector (begin +0x498 / cap +0x4A8); tag-2 writer stride 0x84 [V]; element reader not located [?] | [V] / [?] |
| pass+0x1D0 end cursor | pass+0x1D0 | 8 | `0x66419c6  add qword ptr [rsi+0x1D0],0x50` | end cursor of 0x50-byte ShadowAtlasFrame vector (begin +0x1C8 / cap +0x1D8); tag-4 writer stride 0x50 [V]; element reader not located [?] | [V] / [?] |
| pass+0x800 elements (draining read) | pass+0x800 | - | - | no element read of [pass+0x800 + index*0x14] anywhere in Minecraft.Windows.exe 1.26.62.01; whole-image fld --r/--w scans negative; imm 0x14 and magic ÷0x14 scans negative [V negative] | [V negative] |
| pass+0x648 elements (draining read) | pass+0x648 | - | - | no element read of [pass+0x648 + index*0x48] anywhere in the exe; writes are grow-emplace calls to 0x675FB30 plus index-word stores only; imm 0x48 and magic ÷0x48 scans negative [V negative] | [V negative] |
| pass+0x4A0 elements (draining read) | pass+0x4A0 | - | - | no element read of [pass+0x4A0 + index*0x84] anywhere in the exe; writes are end-cursor increments only; imm 0x84 and magic ÷0x84 scans negative [V negative] | [V negative] |
| pass+0x1D0 elements (draining read) | pass+0x1D0 | - | - | no element read of [pass+0x1D0 + index*0x50] anywhere in the exe; writes are end-cursor increments only; imm 0x50 scan negative [V negative] | [V negative] |
| description field value names | - | - | - | unknown [?]: the release exe contains no RTTI and no description member-name strings; headers use mValue* placeholders with static_assert offsets only; live desc bytes carry values, never names; parked in MIRROR_SKIP per prior review (r2 REVIEW 24/24 [V]) | [?] |

## 4. CLOSES?

CLOSES? NO — single blocking fact: no draining reader/consumer of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 is located in Minecraft.Windows.exe 1.26.62.01; all four vectors are write-only statically (end-cursor increment / grow-emplace only, no pop/decrement, no element-indexed read) [V negative]; closing it requires a live write-watch on the pass vectors, which no tool available to this unit provides — the pending function-entry capture oc_u_er6_light_desc observes description registers at visitor entry only and cannot see pass-memory reads, and livemem needs a pass-object address that statics do not provide (per-thread TLS via 0x5ABA5C0, no static global). Description field value names remain unknown [?] (no RTTI or description member-name strings in the release exe; headers use mValue* placeholders; live bytes give values, never names) — parked in MIRROR_SKIP per prior review, an additional open item but not the closure gate.

Resolved [V] and carried, not re-proven here: tag 2 = GameplayMetadata and tag 3 = LightPoint (FrameBuilder.h wins the group_visitors.md conflict which had 2/3 swapped); the four end-cursor writers to pass+0x800/+0x648/+0x4A0/+0x1D0 [V]; description field read offsets/sizes with live byte confirmation for tags 0/1/2 [V live].

## TOOL REQUESTS

CAPTURE REQUESTED oc_u_er6_light_desc — already queued pending at light-visitor entry 0x6640d80, size 0x100, max 6 (why: R6 — dump tag 3/tag 4 description bytes at runtime to confirm field sizes vs Descriptions.h layouts; ret= names the visitor caller chain); result awaited in docs/data/live/oc_u_er6_light_desc.txt via `python tools/livecap/request.py result oc_u_er6_light_desc`; cite as [V live] when available. It can confirm tag-3/tag-4 description field sizes and the caller chain via ret=, but it cannot close the consumer blocker: that needs a read/write watch on pass+0x800/+0x648/+0x4A0/+0x1D0 (not available via this tool) or a live pass-object address for livemem (none exists: 0x5ABA5C0 = per-call TLS getter, rdis imm/ptr/xr to 0x5aba5c0 = 0 refs/slots). The pending queue is full (4 requests: er5_clone_4c8a5b0, l8b_resizetex_slot31, sub_1289440_callers, oc_u_er6_light_desc), so no further `add` is possible this unit. Helper scripts: None.
