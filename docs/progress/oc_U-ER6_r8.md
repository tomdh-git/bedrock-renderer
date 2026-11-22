## NEXT
DONE

# U-ER6 — R6: LightAmbient / LightDirectional / Light tag 2 / tag 3 / tag 4 (1.26.62.01)

Goal: close R6 — tag value names, the group_visitors.md vs FrameBuilder.h LightGroupTag conflict, and the consumers (draining readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0.

Static analysis only; RVAs image-relative. Every quoted `0xRVA  instr` line is copied verbatim from a listing and passes tools/sigs/verify_oc.py. Tags: [V] seen in disassembly (RVA cited) | [I] inferred | [?] unknown.

Input data already read (not re-generated): docs/functions/6640d80_light_visitor.md; docs/functions/light_game_descriptions.md; docs/functions/group_visitors.md; docs/functions/5aba5c0.md; docs/data/live/light_visitor.txt; docs/BGFX_MAP.md; src/sdk/mc/deps/minecraft_renderer/framebuilder/FrameBuilder.h (LightGroupTag enum); Descriptions.h.

Earlier attempts oc_U-ER6_r1–r3.md are complete static analyses; their proven parts are NOT re-run here (static analysis exhausted for this item per the 2026-11-22 review: "pass+0x800/+0x648/+0x4A0/+0x1D0 are write-only statically; consumers not found. Needs a live write-watch, not more static work"). This unit attacks the blocking fact with the only remaining angle: the new live-capture request tool.

## 1. Tag -> type / value names (LightGroupTag) and the tag-name conflict — resolved [V]

FrameBuilder.h:79-88 `enum class LightGroupTag : uint64_t { Ambient = 0, Directional = 1, GameplayMetadata = 2, LightPoint = 3, ShadowAtlasFrame = 4, ServerGraphicsOverrideParameters = 5, VoxelVolume = 6, TransitioningVoxelVolume = 7 };` matches the producer tag stores: tag 0 `0x53e3511 mov byte ptr [rbp+0x138],0` (LightAmbient clone 0x53e2c00), tag 1 `0x53709d4 mov byte ptr [rbp+0x18],1` (LightDirectional thin clone 0x5370960), tag 2 `0x53e5fb4 mov byte ptr [rbp-0x18],2` (GameplayMetadata clone 0x53e5910), tag 3 `0x535a9b7 mov byte ptr [rbp+0x278],3` (LightPoint clone 0x53599d0), tag 4 `0x535a696 mov byte ptr [rbp+0x278],4` (ShadowAtlasFrame clone 0x53599d0) [V]; jump table 0xF2BF2B0 entries 0..7 = 0x6640de8/0x66415b0/0x6640f1b/0x66410a0/0x6640ec1/0x66417af/0x664187d/0x6641524 [V]. CONFLICT RESOLVED [V]: group_visitors.md had tag 2/3 swapped (LightPoint@2 / GameplayMetadata@3); producer tag stores + __FUNCSIG__ zone records prove tag 2 = GameplayMetadata and tag 3 = LightPoint, so FrameBuilder.h wins. Tags 5/6/7 = ServerGraphicsOverrideParameters / VoxelVolume / TransitioningVoxelVolume [V].

## 2. Light-visitor writers to pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — proven [V] (not re-run this unit)

The pass object is the 0x5ABA5C0 return value (ThreadLocalObject node value at node+0x10 [V]); vectors live inside it: begin/end/cap cursors. Every write below is an end-cursor increment; no end-cursor pop/decrement exists anywhere in the exe [V, whole-image fld --w scans, earlier units].

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| pass+0x800 | 8 | `0x6640e84  mov rdx,[rsi+0x800]`<br>`0x6640e8b  cmp rdx,[rsi+0x808]`<br>`0x6640eb4  add qword ptr [rsi+0x800],0x14`<br>`0x6641761  mov rdx,[rsi+0x800]`<br>`0x66417a2  add qword ptr [rsi+0x800],0x14`<br>`0x6641517  add qword ptr [rsi+0x800],0x14` | end cursor of the 0x14-byte summary list (cap +0x808); writers: Ambient 0x6640eb4, Directional 0x66417a2, Point 0x6641517 [V] | [V] |
| pass+0x648 | 8 | `0x66416f8  lea rcx,[rsi+0x648]`<br>`0x66416ff  call 0x675FB30`<br>`0x664145a  lea rcx,[rsi+0x648]`<br>`0x6641461  call 0x675FB30` | end cursor of the 0x48-byte light-record vector (begin +0x648 / end +0x650); writers: Directional 0x66416ff, Point 0x6641461 via 0x675FB30 [V] | [V] |
| pass+0x4A0 | 8 | `0x6640f78  mov r12,[rdi+0x4A0]`<br>`0x6641090  add qword ptr [rdi+0x4A0],0x84` | end cursor of the 0x84-byte GameplayMetadata vector (begin +0x498 / cap +0x4A8); writer tag 2, stride 0x84 [V] | [V] |
| pass+0x1D0 | 8 | `0x66419c6  add qword ptr [rsi+0x1D0],0x50` | end cursor of the 0x50-byte ShadowAtlasFrame vector (begin +0x1C8 / cap +0x1D8); writer tag 4, stride 0x50 [V] | [V] |

## 3. Consumers of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — NOT located (pending, [?])

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| pass+0x800 element read | - | - | no draining reader of the 0x14-byte summary elements anywhere in Minecraft.Windows.exe 1.26.62.01; only the three end-cursor writers above [V] | [?] |
| pass+0x648 element read | - | - | no draining reader of the 0x48-byte light-record elements anywhere in the exe [V writes only] | [?] |
| pass+0x4A0 element read | - | - | no draining reader of the 0x84-byte GameplayMetadata elements anywhere in the exe [V writes only] | [?] |
| pass+0x1D0 element read | - | - | no draining reader of the 0x50-byte ShadowAtlasFrame elements anywhere in the exe [V writes only] | [?] |

Attacked this unit (all negative, not re-proven from scratch — carried from oc_U-ER6_r2/r3): whole-image `rdis fld 0x800/0x648/0x4A0/0x1D0 --r/--w` scans plus begin cursors 0x7F8/0x650/0x498/0x1C8 show only writer cursor accesses and stack/unrelated same-offset hits [V]; endFrame 0x66232b0 full listing touches none of the four offsets though it calls 0x5ABA5C0 3× [V]; all direct 0x5ABA5C0 callers enumerated via xref.py (endFrame, the six group visitors, 0x66a6830, 0x66a9d50, 0x66ade80, 0x66bb7b0) — none drains [V]; `rdis ptr 0x5aba5c0`: no indirect caller slot [V]; the three non-visitor callers 0x66a6830/0x66a9d50/0x66bb7b0 touch only stack locals (`0x66a6ac4  mov rax,[rbp+0x650]`, `0x66a9d83  movaps [rbp+0x4A0],xmm12`, `0x66bb9be  mov [rbp+0x1D0],rax`) [V]. Accepted blind spot: a consumer that loads a cursor once and then indexes elements via `[cursor_reg+index*stride]` is invisible to offset scans; none of the enumerated cursor-reader functions does that [V]. Static analysis exhausted — locating consumers needs a live read/write watchpoint, which no available tool provides.

## 4. Description field value names — unknown [?]

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| description value names | - | - | LightAmbientDescription (0x18), LightDirectionalDescription (0x24), LightPointDescription (0x108), GameplayMetadataDescription (0x84) field reads are proven [V] in the visitor cases, but the release exe has no RTTI and no description member-name strings; the headers type the fields as mValue* placeholders with static_assert offsets only, and live dumps carry values only. Producer-side meanings (e.g. Ambient +0x00 = Atmosphere +0xA4 [I]) are inference, not names. Value names: unknown [?] | [?] |

## 5. Live capture (new tool, 2026-11-22)

Request `oc_u_er6_light_desc` (rva 0x6640d80 = light-visitor entry, the entry proven for this item; size 0x100, max 6) is already queued in docs/progress/capture_requests.json (state=pending). `python tools/livecap/request.py result oc_u_er6_light_desc` -> "no result yet (orchestrator has not run it)"; no docs/data/live/oc_u_er6_light_desc.txt exists, so nothing is cited as [V live] in this unit.

What the capture will add when the orchestrator runs it: description bytes at visitor entry (RDX = desc pointer per tools/livecap/targets.lua arg=RDX) for tags 3 (LightPoint, 0x108B) and 4 (ShadowAtlasFrame, 0x50B), confirming field sizes/runtime values vs Descriptions.h, plus `ret=` naming the visitor's caller chain (expect _insert(Light) wrapper 0x6640ae0). Limitation: function-entry sampling cannot install a read watchpoint on pass+0x800/+0x648/+0x4A0/+0x1D0, so the capture cannot locate the consumers — the blocking fact below stands regardless of the capture outcome.

## CLOSES?

CLOSES? NO — the consumers (draining element readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 are not located anywhere in Minecraft.Windows.exe 1.26.62.01: all four vectors are write-only statically (only the Light-visitor writers are [V]); whole-image read/write scans, endFrame re-read, 0x5ABA5C0 caller enumeration and `rdis ptr` found no element reader and no end-cursor pop (same E2 consumer blocker as the R2/R5 groups); the live-capture tool samples function entry and cannot install a read watchpoint, so it cannot find consumers either. Single blocking fact: no draining reader of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 exists in the exe, and no available tool can establish the read watchpoint that would find one. (Resolved [V]: tag 2 = GameplayMetadata, tag 3 = LightPoint; FrameBuilder.h wins the tag-name conflict. Open [?]: description value names — no RTTI/member-name source in the exe.)

## TOOL REQUESTS

CAPTURE REQUESTED oc_u_er6_light_desc — light-visitor entry capture (0x6640d80) queued in docs/progress/capture_requests.json, state=pending; awaiting docs/data/live/oc_u_er6_light_desc.txt from the orchestrator. Helper scripts: None (no throwaway scripts written; all evidence from existing tools and already-verified listings).
