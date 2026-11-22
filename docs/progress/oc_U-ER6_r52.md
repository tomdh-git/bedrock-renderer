## NEXT
DONE

# U-ER6 — R6: LightAmbient / LightDirectional / Light tag 2 / tag 3 / tag 4 (1.26.62.01)

Goal: close R6 — description field value names, the group_visitors.md vs FrameBuilder.h LightGroupTag tag-name conflict, and consumers (draining element readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0. Exe Minecraft.Windows.exe 1.26.62.01, RVAs image-relative. Static analysis only; live capture is orchestrator-provided and read-only. Tags: [V] seen in disassembly (RVA cited) | [V carried] proven in earlier docs/progress/oc_U-ER6_r*.md notes and not re-proven per RETRY #1 | [V negative] whole-image scan found nothing | [V live] live capture bytes (docs/data/live/*.txt) | [I] inferred | [?] unknown. Every `0xRVA  instr` line is copied verbatim from a verified listing/disassembly.

Input data (read fully, not re-generated): docs/functions/6640d80_light_visitor.md; docs/functions/group_visitors.md; docs/functions/5aba5c0.md; docs/functions/light_game_descriptions.md; docs/data/live/light_visitor.txt; docs/data/live/README.md; docs/data/live/_status.txt; docs/BGFX_MAP.md sections 6gq, 6ih, 6hi, 6w, 6ha; src/sdk/mc/deps/minecraft_renderer/framebuilder/FrameBuilder.h (LightGroupTag enum); Descriptions.h/LightDescriptions.h/LightGameDescriptions.h.

## 1. Already proven [V carried] — not re-proven (oc_U-ER6_r1..r3, r47-r51)

Tag dispatch and names:
- `0x6640dc4  movzx eax,byte ptr [rdx+8]` loads variant+0x08 tag byte; `0x6640de6  jmp rax` dispatches through jump table 0xF2BF2B0 (entries: 0=0x6640de8, 1=0x66415b0, 2=0x6640f1b, 3=0x66410a0, 4=0x6640ec1, 5=0x66417af, 6=0x664187d, 7=0x6641524); rsi = pass object, rdx = variant {desc+0x00, tag+0x08}.
- tag 0 = Ambient: `0x53e3511  mov byte ptr [rbp+0x138],0` (clone 0x53e2c00, srcloc 0xF248E70 RenderLightAmbientDescription); JT entry 0.
- tag 1 = Directional: `0x53709d4  mov byte ptr [rbp+0x18],1` (clone 0x5370960, srcloc 0xF248F70 LightDirectionalDescription); JT entry 1.
- tag 2 = GameplayMetadata: `0x53e5fb4  mov byte ptr [rbp-0x18],2` / `0x53e5fbf  mov rax,[rax+0x380]` (clone 0x53e5910, Light vslot 0x380 insert 0x53e5fbf, srcloc 0xF248ED0 GameplayMetadata); JT entry 2.
- tag 3 = LightPoint: `0x535a9b7  mov byte ptr [rbp+0x278],3` / `0x535a9c1  mov rax,[rax+0x380]` (clone 0x53599d0 insert 0x535a9c1, srcloc 0xF248DA0 LightPointDescription); JT entry 3.
- tag 4 = ShadowAtlasFrame: `0x535a696  mov byte ptr [rbp+0x278],4` / `0x535a6a0  mov rax,[rax+0x380]` (clone 0x53599d0 insert 0x535a6a0, srcloc 0xF248D80 ShadowAtlasFrameDescription); JT entry 4.
- Tag-name conflict RESOLVED [V carried]: FrameBuilder.h:79-88 `enum class LightGroupTag : uint64_t { Ambient = 0, Directional = 1, GameplayMetadata = 2, LightPoint = 3, ShadowAtlasFrame = 4, ServerGraphicsOverrideParameters = 5, VoxelVolume = 6, TransitioningVoxelVolume = 7 }`; producer tag stores + __FUNCSIG__ srclocs prove tag 2 = GameplayMetadata and tag 3 = LightPoint; FrameBuilder.h wins and group_visitors.md (which had them swapped) is superseded; BGFX_MAP.md 6w agrees.

Light-visitor writers to the four pass cursors [V carried] — write-only, every write an end-cursor increment / grow-emplace; no end-cursor pop/decrement anywhere in the exe [V negative]:
- pass+0x800 end cursor of the 0x14-byte summary list (cap +0x808): `0x6640e84  mov rdx,[rsi+0x800]` / `0x6640e8b  cmp rdx,[rsi+0x808]` / `0x6640eb4  add qword ptr [rsi+0x800],0x14` (Ambient); `0x6641761  mov rdx,[rsi+0x800]` / `0x66417a2  add qword ptr [rsi+0x800],0x14` (Directional); `0x6641517  add qword ptr [rsi+0x800],0x14` (LightPoint).
- pass+0x648 end cursor of the 0x48-byte light-record vector (begin +0x648 / end +0x650): `0x66416f8  lea rcx,[rsi+0x648]` / `0x66416ff  call 0x675FB30` (Directional); `0x664145a  lea rcx,[rsi+0x648]` / `0x6641461  call 0x675FB30` (LightPoint).
- pass+0x4A0 end cursor of the 0x84-byte GameplayMetadata vector (begin +0x498 / cap +0x4A8): `0x6640f78  mov r12,[rdi+0x4A0]` / `0x6640f7f  cmp r12,[rdi+0x4A8]` / `0x6641090  add qword ptr [rdi+0x4A0],0x84` (tag 2, stride 0x84).
- pass+0x1D0 end cursor of the 0x50-byte ShadowAtlasFrame vector (begin +0x1C8 / cap +0x1D8): `0x66419c6  add qword ptr [rsi+0x1D0],0x50` (tag 4, stride 0x50).

## 2. NEW work this unit — live capture oc_u_er6_light_desc (visitor entry 0x6640d80)

Status and result: PENDING IN THIS UNIT (checked below). Earlier notes (r49-r51) left it queued with 4 pending slots full; no result file existed then. The capture samples REG=value at visitor entry (RDX = desc pointer per docs/data/live/README.md CORRECTION 2026-11-15), dumping <bytes of the pointee>, and `ret=` names the visitor caller chain.

## 3. Static angles that CANNOT add to the consumer blocker (exhausted in r2/r3/r47-r49, not re-run)

- imm 0x14 / 0x48 / 0x84 / 0x50 scans over .text and magic-multiplier imm scans 0xFFFF8E39 (÷0x48), 0xFFFFCCCD (÷0x14), 0xFFFF83E1 (÷0x84): no stride-multiply reader `[pass + index*stride]` anywhere [V negative].
- Whole-image fld --r/--w on 0x800/0x648/0x4A0/0x1D0 and begin cursors 0x7F8/0x650/0x498/0x1C8; cap cursors 0x808/0x4A8/0x1D8: all hits stack/unrelated locals [V negative].
- rdis callers/xr of 0x6640ae0 (visitor's sole static caller): 0 calling functions, 0 xrefs — visitor chain terminates statically [V].
- rdis ptr/imm/xr to 0x5aba5c0: 0 refs/slots; all 0x5ABA5C0 callers touch only stack locals or are other visitors; pass object has no static address (per-thread TLS node) [V].
- endFrame 0x66232b0 re-list: no access to any of the four offsets [V]; descscan2 tag-2 case 0x6640f1b reads desc+0x00..+0x84 only, no pass offset [V]; per-draw code 0x66ea3d0 appends u16 indices to pass+0x8A8 and reads none of the four cursors [V]; ClusterLights body 0xbc5bad0 reads clusters through `[data_0x12ae1748] + view*0x1EAB090`, not the pass vectors [V carried]; BGFX_MAP.md 6gq/6ih/6hi/6w/6ha name no consumer [V carried].

## 4. Field map — one row per distinct offset (carried rows stand; [V live] rows added below from the capture result)

| item | offset/size | size | verbatim `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|
| variant+0x08 tag byte | variant+0x08 | 1 | `0x6640dc4  movzx eax,byte ptr [rdx+8]`<br>`0x6640de6  jmp rax` | tag byte at variant+0x08; dispatch `jmp rax` via jump table 0xF2BF2B0 | [V carried] |
| tag 0 = Ambient | - | 1 | `0x53e3511  mov byte ptr [rbp+0x138],0` | LightGroupTag::Ambient = 0; JT entry 0; srcloc 0xF248E70 RenderLightAmbientDescription | [V carried] |
| tag 1 = Directional | - | 1 | `0x53709d4  mov byte ptr [rbp+0x18],1` | LightGroupTag::Directional = 1; JT entry 1; srcloc 0xF248F70 LightDirectionalDescription | [V carried] |
| tag 2 = GameplayMetadata | - | 1 | `0x53e5fb4  mov byte ptr [rbp-0x18],2`<br>`0x53e5fbf  mov rax,[rax+0x380]` | LightGroupTag::GameplayMetadata = 2; JT entry 2; srcloc 0xF248ED0 GameplayMetadata | [V carried] |
| tag 3 = LightPoint | - | 1 | `0x535a9b7  mov byte ptr [rbp+0x278],3`<br>`0x535a9c1  mov rax,[rax+0x380]` | LightGroupTag::LightPoint = 3; JT entry 3; srcloc 0xF248DA0 LightPointDescription | [V carried] |
| tag 4 = ShadowAtlasFrame | - | 1 | `0x535a696  mov byte ptr [rbp+0x278],4`<br>`0x535a6a0  mov rax,[rax+0x380]` | LightGroupTag::ShadowAtlasFrame = 4; JT entry 4; srcloc 0xF248D80 ShadowAtlasFrameDescription | [V carried] |
| tag-name conflict | - | - | FrameBuilder.h:79-88 `enum class LightGroupTag ... { Ambient = 0, Directional = 1, GameplayMetadata = 2, LightPoint = 3, ShadowAtlasFrame = 4, ... }` | CONFLICT RESOLVED [V carried]: tag 2 = GameplayMetadata, tag 3 = LightPoint; FrameBuilder.h wins, group_visitors.md swapped them and is superseded | [V carried] |
| pass+0x800 end cursor | pass+0x800 | 8 | `0x6640e84  mov rdx,[rsi+0x800]`<br>`0x6640e8b  cmp rdx,[rsi+0x808]`<br>`0x6640eb4  add qword ptr [rsi+0x800],0x14`<br>`0x6641761  mov rdx,[rsi+0x800]`<br>`0x66417a2  add qword ptr [rsi+0x800],0x14`<br>`0x6641517  add qword ptr [rsi+0x800],0x14` | end cursor of 0x14-byte summary list (cap +0x808); writers Ambient/Directional/LightPoint [V carried]; draining element reader not located [V negative] | [V carried] / [V negative] |
| pass+0x648 end cursor | pass+0x648 | 8 | `0x66416f8  lea rcx,[rsi+0x648]`<br>`0x66416ff  call 0x675FB30`<br>`0x664145a  lea rcx,[rsi+0x648]`<br>`0x6641461  call 0x675FB30` | end cursor of 0x48-byte light-record vector (begin +0x648 / end +0x650); writers Directional/LightPoint via grow-emplace 0x675FB30 [V carried]; element reader not located [V negative] | [V carried] / [V negative] |
| pass+0x4A0 end cursor | pass+0x4A0 | 8 | `0x6640f78  mov r12,[rdi+0x4A0]`<br>`0x6640f7f  cmp r12,[rdi+0x4A8]`<br>`0x6641090  add qword ptr [rdi+0x4A0],0x84` | end cursor of 0x84-byte GameplayMetadata vector (begin +0x498 / cap +0x4A8); tag-2 writer stride 0x84 [V carried]; element reader not located [V negative] | [V carried] / [V negative] |
| pass+0x1D0 end cursor | pass+0x1D0 | 8 | `0x66419c6  add qword ptr [rsi+0x1D0],0x50` | end cursor of 0x50-byte ShadowAtlasFrame vector (begin +0x1C8 / cap +0x1D8); tag-4 writer stride 0x50 [V carried]; element reader not located [V negative] | [V carried] / [V negative] |
| description field value names | - | - | - | unknown [?]: release exe has no RTTI and no description member-name strings; headers use mValue* placeholders with static_assert offsets only; live capture bytes give values never names; parked in MIRROR_SKIP per prior review (r2 REVIEW 24/24 [V]) | [?] |

## 5. What the existing live data adds [V live] — and what it cannot add

Live capture already on disk: docs/data/live/light_visitor.txt (rva=0x6640D80, kind=visitor, size=0x300; line = tag descptr hexbytes). Samples present: tag 5 at 0x14AA80 (line 1), tag 0 at 0x14A5B8 (line 3), tag 1 at 0x14A400 (lines 5 and 8), tag 2 at 0x14A5A0 (lines 6 and 7). Tags 3 (LightPoint, 0x108 B) and 4 (ShadowAtlasFrame, 0x50 B) do NOT appear in any sample — their bytes await capture oc_u_er6_light_desc.

Confirmed by live bytes (runtime VALUES, never names):
- tag 2 GameplayMetadata desc at 0x14A5A0 (lines 6-7): +0x00..+0x14 six f32 (8.5, 1.0, 2.0, 15.0, 1.0, 0.5 — identical in both samples), +0x18 u32 differs per sample (line 6: DE87E73D; line 7: 884CED3D → per-object data), +0x1C u32 = 4 and +0x20 u32 = 18000 (0x00004650) in both samples. Sizes match the visitor reads (descscan2 tag-2 case 0x6640f1b reads desc+0x00..+0x84 [V]); names stay [?]. Cite: docs/data/live/light_visitor.txt lines 6-7 [V live].
- tag 0 Ambient desc at 0x14A5B8 (line 3): +0x00..+0x0F all zero (qword +0x00 = 0, f32 +0x08 = 0). Cite: docs/data/live/light_visitor.txt line 3 [V live].
- tag 1 Directional desc at 0x14A400 (lines 5, 8): +0x00..+0x10 five 1.0 f32s (0000803F x5 at the dump head). Cite: docs/data/live/light_visitor.txt lines 5 and 8 [V live].
No member names exist in the dumps or the exe [V live] — description value names stay [?] (no RTTI, no description-member name strings in the release exe; headers use mValue* placeholders; parked in MIRROR_SKIP per prior review r2 REVIEW 24/24 [V]).

New static angles considered this unit per RETRY #1 (all dead ends; carried negatives, not re-run):
- rdis xr/callers: visitor 0x6640ae0 has 0 calling functions / 0 xrefs; rdis imm/ptr/xr to 0x5aba5c0 = 0 refs/slots; all 0x5ABA5C0 callers enumerated (endFrame 0x66232b0, the six group visitors, 0x66a6830, 0x66a9d50, 0x66bb7b0) — none drains the vectors [V carried].
- flow/rw/struct: whole-image fld --r/--w on 0x800/0x648/0x4A0/0x1D0 plus begin/cap cursors — stack/unrelated locals only [V negative]; imm 0x14/0x48/0x84/0x50 and magic-multiplier scans (÷0x14 ÷0x48 ÷0x84) — writer hits only, no scaled-index/imul element reader [V negative].
- vt/vcalls: not applicable — the pass object has no static address (ThreadLocalObject per-thread node via 0x5ABA5C0; value at node+0x10), so no vtable or static call target to walk for a consumer [V carried].
- descscan2: tag-2 case 0x6640f1b reads desc+0x00..+0x84 only, no pass offset [V carried]; the tag-3/tag-4 cases write the cursors, they do not read elements.
- livemem: the game IS running (livemem.py status: pid 13452, base 0x7ff7a59c0000, version OK 1.26.62.01) but livemem is a read-only memory read at a specific known address — no pass-object address exists statically, and read-only reads show the pass object changing, never which code reads it; no breakpoints/watchpoints are available to this unit (orchestrator-only). Not usable for the consumer blocker [V static].

Pending capture: oc_u_er6_light_desc (visitor entry 0x6640d80, size 0x100, max 6) — `python tools/livecap/request.py add oc_u_er6_light_desc 0x6640d80 ...` returned "already queued" (exit 1); `python tools/livecap/request.py result oc_u_er6_light_desc` -> "no result yet (orchestrator has not run it)"; no docs/data/live/oc_u_er6_light_desc.txt exists. When run it can add tag-3/tag-4 description bytes at visitor entry and name the visitor caller chain via ret= [V live]; it CANNOT install a read/watch on pass+0x800/+0x648/+0x4A0/+0x1D0, so it cannot surface a consumer.

## 6. CLOSES?

CLOSES? NO — single blocking fact: no draining reader/consumer of pass+0x800 (0x14-byte summary list), pass+0x648 (0x48-byte light-record vector), pass+0x4A0 (0x84-byte GameplayMetadata vector) or pass+0x1D0 (0x50-byte ShadowAtlasFrame vector) exists anywhere in Minecraft.Windows.exe 1.26.62.01 [V negative]: every write to the four end cursors is an end-cursor increment / grow-emplace (section 4 table), no pop/decrement, no [cursor + index*stride] element read, no whole-image fld/imm/magic-multiplier hit traceable to the pass object, every 0x5ABA5C0 caller accounted for, endFrame and descscan2 clean, ClusterLights body 0xbc5bad0 and per-draw code 0x66ea3d0 read other structures. The four vectors are write-only statically. Closing it needs a live read/write watch on the pass vectors or a live pass-object address — neither available to this unit (the 0x6640d80 entry capture samples registers/description bytes only; livemem read-only needs an address statics do not provide). Description value names are a second open [?] for the same reason (no names in the exe or dumps); parked in MIRROR_SKIP, not the closure gate.

Everything else in R6 is proven [V]: tag dispatch via jump table 0xF2BF2B0 (0x6640dc4 / 0x6640de6); tag 2 = GameplayMetadata and tag 3 = LightPoint; tag-name conflict resolved (FrameBuilder.h wins over group_visitors.md, which had them swapped); the four end-cursor writers to pass+0x800/+0x648/+0x4A0/+0x1D0; description field read offsets/sizes with live byte confirmation for tags 0/1/2 [V live].

## TOOL REQUESTS

CAPTURE REQUESTED oc_u_er6_light_desc — light-visitor entry capture (rva 0x6640d80, size 0x100, max 6) already queued (`request.py add` -> "already queued"); result awaited in docs/data/live/oc_u_er6_light_desc.txt via `python tools/livecap/request.py result oc_u_er6_light_desc`. What it can add: tag-3 (LightPoint 0x108 B) and tag-4 (ShadowAtlasFrame 0x50 B) description bytes at visitor entry, and the caller chain via ret= — cite as [V live] when available. What it cannot add: consumers of pass+0x800/+0x648/+0x4A0/+0x1D0 (no pass-memory read/write watch). Helper scripts: None.
