## NEXT
DONE

# U-ER6 — R6: LightAmbient / LightDirectional / Light tag 2 / tag 3 / tag 4 (1.26.62.01)

Goal: close R6 — description field value names, the group_visitors.md vs FrameBuilder.h LightGroupTag tag-name conflict, and the consumers (draining element readers) of pass+0x800 / pass+0x648 / pass+0x4A0 / pass+0x1D0. Static analysis only; RVAs image-relative (Minecraft.Windows.exe 1.26.62.01). Every `0xRVA  instr` line is copied verbatim from a verified listing/disassembly and re-checked with tools/sigs/verify_oc.py.
Tags: [V] seen in disassembly (RVA cited) | [V live] live capture bytes (docs/data/live/*.txt) | [I] inferred | [?] unknown.

Input data (read fully, not re-generated): docs/functions/6640d80_light_visitor.md; docs/functions/group_visitors.md; docs/functions/5aba5c0.md; docs/data/live/light_visitor.txt; src/sdk/mc/deps/minecraft_renderer/framebuilder/FrameBuilder.h (LightGroupTag enum); Descriptions.h/LightDescriptions.h/LightGameDescriptions.h. Earlier notes oc_U-ER6_r1..r3 are NOT redone; their [V] rows stand.

## 1. Already proven [V] (oc_U-ER6_r1..r3 — not repeated)

Tag dispatch and names:
- variant+0x08 tag byte loaded at `0x6640dc4  movzx eax,byte ptr [rdx+8]`, dispatched by `0x6640de6  jmp rax` through jump table 0xF2BF2B0 (entries: 0=0x6640de8, 1=0x66415b0, 2=0x6640f1b, 3=0x66410a0, 4=0x6640ec1, 5=0x66417af, 6=0x664187d, 7=0x6641524); rsi = description pointer, rdx = variant {desc+0x00, tag+0x08}.
- tag 0 Ambient: `0x53e3511  mov byte ptr [rbp+0x138],0` (producer clone 0x53e2c00, srcloc 0xF248E70 `FrameBuilder::insert [TDescription = RenderLightAmbientDescription]`).
- tag 1 Directional: `0x53709d4  mov byte ptr [rbp+0x18],1` (clone 0x5370960, srcloc 0xF248F70 LightDirectionalDescription).
- tag 2 GameplayMetadata: `0x53e5fb4  mov byte ptr [rbp-0x18],2` / `0x53e5fbf  mov rax,[rax+0x380]` (clone 0x53e5910, Light vslot 0x380 insert 0x53e5fbf, srcloc 0xF248ED0 `__FUNCSIG__ ... gamecomponents::GameplayMetadata`).
- tag 3 LightPoint: `0x535a9b7  mov byte ptr [rbp+0x278],3` / `0x535a9c1  mov rax,[rax+0x380]` (clone 0x53599d0 insert 0x535a9c1, srcloc 0xF248DA0 `LightPointDescription`).
- tag 4 ShadowAtlasFrame: `0x535a696  mov byte ptr [rbp+0x278],4` / `0x535a6a0  mov rax,[rax+0x380]` (clone 0x53599d0 insert 0x535a6a0, srcloc 0xF248D80 `ShadowAtlasFrameDescription`).
- Tag-name conflict RESOLVED [V]: FrameBuilder.h:79-88 defines `enum class LightGroupTag : uint64_t { Ambient = 0, Directional = 1, GameplayMetadata = 2, LightPoint = 3, ShadowAtlasFrame = 4, ServerGraphicsOverrideParameters = 5, VoxelVolume = 6, TransitioningVoxelVolume = 7 };`. Producer tag stores + __FUNCSIG__ srclocs prove tag 2 = GameplayMetadata and tag 3 = LightPoint; FrameBuilder.h wins and group_visitors.md (which had them swapped) is superseded.

Light-visitor writers to the four pass cursors [V] — write-only; consumers are section 3:
- pass+0x800 end cursor of the 0x14-byte summary list (cap +0x808): `0x6640e84  mov rdx,[rsi+0x800]` / `0x6640e8b  cmp rdx,[rsi+0x808]` / `0x6640eb4  add qword ptr [rsi+0x800],0x14` (Ambient); `0x6641761  mov rdx,[rsi+0x800]` / `0x66417a2  add qword ptr [rsi+0x800],0x14` (Directional); `0x6641517  add qword ptr [rsi+0x800],0x14` (Point).
- pass+0x648 end cursor of the 0x48-byte light-record vector (begin +0x648 / end +0x650): `0x66416f8  lea rcx,[rsi+0x648]` / `0x66416ff  call 0x675FB30` (Directional); `0x664145a  lea rcx,[rsi+0x648]` / `0x6641461  call 0x675FB30` (Point).
- pass+0x4A0 end cursor of the 0x84-byte GameplayMetadata vector (begin +0x498 / cap +0x4A8): `0x6640f78  mov r12,[rdi+0x4A0]` / `0x6641090  add qword ptr [rdi+0x4A0],0x84` (tag 2, stride 0x84).
- pass+0x1D0 end cursor of the 0x50-byte ShadowAtlasFrame vector (begin +0x1C8 / cap +0x1D8): `0x66419c6  add qword ptr [rsi+0x1D0],0x50` (tag 4, stride 0x50).
Every write is an end-cursor increment; no end-cursor pop/decrement exists anywhere in the exe [V, whole-image fld --w scans, oc_U-ER6_r2/r3].

## 2. New work this unit: live description bytes (description field value names)

The light-visitor entry 0x6640d80 was already captured as target `light_visitor` (kind=visitor, arg=RDX per the 2026-11-15 README correction: RDX = desc pointer), size=0x300; output docs/data/live/light_visitor.txt [V live]. Samples present: tag 0 at 0x14A5B8 (line 4), tag 1 at 0x14A400 (lines 5 and 8), tag 2 at 0x14A5A0 (lines 6 and 7). Tag 3 (LightPoint, 0x108 bytes) and tag 4 (ShadowAtlasFrame, 0x50 bytes) do NOT appear in any live sample — their bytes are awaited from capture request oc_u_er6_light_desc (state=pending, see TOOL REQUESTS).

Confirmed from live bytes [V live]: docs/data/live/light_visitor.txt line 6 (`2 14A5A0 ...`) — tag 2 description at 0x14A5A0 holds +0x00..+0x17 six 4-byte fields, +0x18 a 4-byte field that differs between samples (line 6: DE87E73D; line 7: 884CED3D → per-object data), +0x1C u32 = 4 and +0x20 u32 = 18000 (0x00004650) in both samples — field sizes match the statically proven visitor reads, bytes carry runtime values only. Tag 0/1 objects at 0x14A5B8/0x14A400 likewise confirm the Ambient/Directional description objects [V live].

Value names: the release exe contains no description-member name strings and no RTTI for description objects; FrameBuilder.h/Descriptions.h type the fields as mValue* placeholders with static_assert offsets only; live bytes give values, never names. Description value names: unknown [?]. No static or live source available to this unit can supply them.

## 3. Consumers of pass+0x800 / pass+0x648 / pass+0x4A0 / pass+0x1D0 — blocked (single blocking fact)

New angles tried this unit (nothing succeeded; oc_U-ER6_r2/r3 is not redone):
- All static consumer angles were already exhausted and proven [V] in r2/r3: whole-image `rdis fld --r/--w` scans for 0x800/0x648/0x4A0/0x1D0 and begin cursors 0x7F8/0x650/0x498/0x1C8 (complete scans); endFrame full listing sub_66232b0 (no access to any of the four offsets although it calls 0x5ABA5C0 3×); the three other direct 0x5ABA5C0 callers (0x66a6830, 0x66a9d50, 0x66bb7b0 — stack locals only); `rdis ptr 0x5aba5c0` (0 indirect caller slots); all 18 direct 0x5ABA5C0 callers enumerated via xref.py callers, none drains the vectors.
- Considered but not usable: livemem.py is read-only memory read and requires a specific known object address (brief: only after an rdis finding points at a specific object); no pass-object address is known from statics, and scanning/ranging memory is forbidden; read-only memory reads would show the pass object changing, not which code reads it.
- Live capture oc_u_er6_light_desc (pending) observes the description registers at visitor entry plus ret= (the visitor's caller); it cannot observe reads of pass-memory (pass+0x800 / pass+0x648 / pass+0x4A0 / pass+0x1D0), so it cannot surface a consumer either.

Result: no draining element reader is located for any of the four offsets [?]; all four vectors are write-only [V] — writers above, every write an end-cursor increment, no pop/decrement, no [cursor+index*stride] read anywhere [V].

## 4. Field map (one row per distinct offset; all sites listed)

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| variant+0x08 tag byte | 1 | `0x6640dc4  movzx eax,byte ptr [rdx+8]`<br>`0x6640de6  jmp rax` | tag byte at variant+0x08; dispatch `jmp rax` via jump table 0xF2BF2B0 (entries 0=0x6640de8, 1=0x66415b0, 2=0x6640f1b, 3=0x66410a0, 4=0x6640ec1, 5=0x66417af, 6=0x664187d, 7=0x6641524) | [V] |
| tag 0 Ambient | 1 | `0x53e3511  mov byte ptr [rbp+0x138],0` | LightGroupTag::Ambient = 0 (FrameBuilder.h:79-88); producer clone 0x53e2c00, srcloc 0xF248E70; JT entry 0 | [V] |
| tag 1 Directional | 1 | `0x53709d4  mov byte ptr [rbp+0x18],1` | LightGroupTag::Directional = 1; clone 0x5370960, srcloc 0xF248F70; JT entry 1 | [V] |
| tag 2 GameplayMetadata | 1 | `0x53e5fb4  mov byte ptr [rbp-0x18],2`<br>`0x53e5fbf  mov rax,[rax+0x380]` | LightGroupTag::GameplayMetadata = 2; clone 0x53e5910, Light vslot 0x380 insert 0x53e5fbf, srcloc 0xF248ED0 GameplayMetadata; JT entry 2 | [V] |
| tag 3 LightPoint | 1 | `0x535a9b7  mov byte ptr [rbp+0x278],3`<br>`0x535a9c1  mov rax,[rax+0x380]` | LightGroupTag::LightPoint = 3; clone 0x53599d0 insert 0x535a9c1, srcloc 0xF248DA0 LightPointDescription; JT entry 3 | [V] |
| tag 4 ShadowAtlasFrame | 1 | `0x535a696  mov byte ptr [rbp+0x278],4`<br>`0x535a6a0  mov rax,[rax+0x380]` | LightGroupTag::ShadowAtlasFrame = 4; clone 0x53599d0 insert 0x535a6a0, srcloc 0xF248D80 ShadowAtlasFrameDescription; JT entry 4 | [V] |
| tag-name conflict | - | FrameBuilder.h:79-88 `enum class LightGroupTag : uint64_t { Ambient = 0, Directional = 1, GameplayMetadata = 2, LightPoint = 3, ShadowAtlasFrame = 4, ServerGraphicsOverrideParameters = 5, VoxelVolume = 6, TransitioningVoxelVolume = 7 };` | CONFLICT RESOLVED [V]: producer tag stores + __FUNCSIG__ srclocs prove tag 2 = GameplayMetadata and tag 3 = LightPoint; FrameBuilder.h wins, group_visitors.md had them swapped and is superseded | [V] |
| description field sizes | - | - | visitor description read offsets/sizes proven [V] (section 1); live bytes for tags 0/1/2 at 0x14A5B8 / 0x14A400 / 0x14A5A0 (docs/data/live/light_visitor.txt lines 4-8) confirm the Ambient/Directional/GameplayMetadata objects [V live]; tags 3/4 description bytes not in any live sample (capture oc_u_er6_light_desc pending) | [V] / [V live] |
| description value names | - | - | no description-member name strings or RTTI in the release exe; headers use mValue* placeholders; live bytes carry values not names; tags 3/4 uncaptured → value names unknown [?] | [?] |
| pass+0x800 | 8 | `0x6640e84  mov rdx,[rsi+0x800]`<br>`0x6640e8b  cmp rdx,[rsi+0x808]`<br>`0x6640eb4  add qword ptr [rsi+0x800],0x14`<br>`0x6641761  mov rdx,[rsi+0x800]`<br>`0x66417a2  add qword ptr [rsi+0x800],0x14`<br>`0x6641517  add qword ptr [rsi+0x800],0x14` | end cursor of 0x14-byte summary list (cap +0x808); writers Ambient 0x6640eb4 / Directional 0x66417a2 / Point 0x6641517 [V]; draining element reader not located anywhere in the exe [?] | [V] / [?] |
| pass+0x648 | 8 | `0x66416f8  lea rcx,[rsi+0x648]`<br>`0x66416ff  call 0x675FB30`<br>`0x664145a  lea rcx,[rsi+0x648]`<br>`0x6641461  call 0x675FB30` | end cursor of 0x48-byte light-record vector (begin +0x648 / end +0x650); writers Directional 0x66416ff / Point 0x6641461 via 0x675FB30 [V]; element reader not located [?] | [V] / [?] |
| pass+0x4A0 | 8 | `0x6640f78  mov r12,[rdi+0x4A0]`<br>`0x6641090  add qword ptr [rdi+0x4A0],0x84` | end cursor of 0x84-byte GameplayMetadata vector (begin +0x498 / cap +0x4A8); writer tag 2, stride 0x84 [V]; element reader not located [?] | [V] / [?] |
| pass+0x1D0 | 8 | `0x66419c6  add qword ptr [rsi+0x1D0],0x50` | end cursor of 0x50-byte ShadowAtlasFrame vector (begin +0x1C8 / cap +0x1D8); writer tag 4, stride 0x50 [V]; element reader not located [?] | [V] / [?] |

## 5. CLOSES?

NO — single blocking fact: the consumers (draining element readers) of pass+0x800 / pass+0x648 / pass+0x4A0 / pass+0x1D0 are not located in Minecraft.Windows.exe 1.26.62.01: whole-image read/write scans show only the three light-visitor end-cursor writers [V] (table above), every write is an end-cursor increment with no pop/decrement [V], no function loads a pass cursor and then reads `[cursor+index*stride]` [V], and every 0x5ABA5C0 caller is accounted for and none drains them [V]. The live entry-capture available to this unit observes description registers at visitor entry and its ret= caller (oc_u_er6_light_desc, state=pending), not pass-memory reads, so it cannot surface a consumer; livemem read-only needs a pass-object address that statics do not provide. Description value names are a second open [?]: no name strings/RTTI for description members exist in the release exe. All other R6 parts are proven [V]: tag names (tag 2 = GameplayMetadata, tag 3 = LightPoint), the tag-name conflict (FrameBuilder.h wins over group_visitors.md), the four writers, and description field read offsets/sizes with live byte confirmation for tags 0/1/2 [V live].

## TOOL REQUESTS

CAPTURE REQUESTED oc_u_er6_light_desc — already queued by the orchestrator (state=pending), rva=0x6640d80 (light visitor entry, the proven dispatcher), size=0x100, max=6. Why: R6 — dump tag 3 (LightPoint) and tag 4 (ShadowAtlasFrame) description bytes at runtime to confirm field sizes vs Descriptions.h layouts; ret= names the visitor caller chain. Result expected at docs/data/live/oc_u_er6_light_desc.txt; cite as [V live] when available. The pending request queue is full (4 requests: er5_clone_4c8a5b0, l8b_resizetex_slot31, sub_1289440_callers, oc_u_er6_light_desc), so no further request can be added this unit. Helper scripts: none — all verification via existing tools (rdis dis through verify_oc.py; live data docs/data/live/light_visitor.txt; capture via tools/livecap/request.py).

