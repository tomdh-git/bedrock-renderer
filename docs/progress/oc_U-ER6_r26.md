## NEXT
DONE

# U-ER6 — R6: LightAmbient / LightDirectional / Light tag 2 / tag 3 / tag 4 (1.26.62.01)

Goal: close R6 — tag value names, the group_visitors.md vs FrameBuilder.h LightGroupTag conflict, and consumers (draining readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0.
Static analysis only; RVAs image-relative. Every `0xRVA  instr` line is copied verbatim from a listing and passes tools/sigs/verify_oc.py.
Tags: [V] seen in disassembly (RVA cited) | [I] inferred from tool output | [?] unknown.
Input data (read fully, not re-generated): docs/functions/6640d80_light_visitor.md; docs/functions/light_game_descriptions.md; docs/functions/group_visitors.md; docs/functions/5aba5c0.md; docs/data/live/light_visitor.txt; docs/BGFX_MAP.md sections 6gq/6h/6ih/6ib/6hi; src/sdk/mc/deps/minecraft_renderer/framebuilder/FrameBuilder.h (LightGroupTag enum); Descriptions.h.

Prior units (r1-r25, NOT redone): tag names resolved [V] (tag 2 = GameplayMetadata, tag 3 = LightPoint; FrameBuilder.h wins, group_visitors.md had them swapped); tag-value names unknown [?]; all four pass vectors are write-only [V] (light-visitor end-cursor writers proven); no element consumer located by whole-image fld --r/--w scans, endFrame full listing, the three other 0x5ABA5C0 callers (stack locals only), rdis ptr 0x5aba5c0 (no indirect slot). Blocking fact carried in: consumers of pass+0x800/+0x648/+0x4A0/+0x1D0 not located statically — needs live data (write-watch / caller chain).

## 1. Tag -> type / value names (LightGroupTag) and the tag-name conflict — RESOLVED [V]

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| variant+0x08 tag | 1 | `0x6640dc4  movzx eax,byte ptr [rdx+8]`<br>`0x6640de6  jmp rax` | tag byte at variant+0x08; dispatch `jmp rax` via jump table 0xF2BF2B0 (entries: 0=0x6640de8, 1=0x66415b0, 2=0x6640f1b, 3=0x66410a0, 4=0x6640ec1, 5=0x66417af, 6=0x664187d, 7=0x6641524) | [V] |
| tag 0 | 1 | `0x53e3511  mov byte ptr [rbp+0x138],0` | LightGroupTag::Ambient = 0 (FrameBuilder.h:79-88); producer clone 0x53e2c00, srcloc 0xF248E70 `FrameBuilder::insert [TDescription = RenderLightAmbientDescription]`; jump-table entry 0 (0x6640de8) | [V] |
| tag 1 | 1 | `0x53709d4  mov byte ptr [rbp+0x18],1` | LightGroupTag::Directional = 1; thin clone 0x5370960, srcloc 0xF248F70 (LightDirectionalDescription); entry 1 (0x66415b0) | [V] |
| tag 2 | 1 | `0x53e5fb4  mov byte ptr [rbp-0x18],2`<br>`0x53e5fbf  mov rax,[rax+0x380]` | LightGroupTag::GameplayMetadata = 2; clone 0x53e5910, Light vslot 0x380 insert 0x53e5fbf, srcloc 0xF248ED0 `__FUNCSIG__ ... gamecomponents::GameplayMetadata`; entry 2 (0x6640f1b) | [V] |
| tag 3 | 1 | `0x535a9b7  mov byte ptr [rbp+0x278],3`<br>`0x535a9c1  mov rax,[rax+0x380]` | LightGroupTag::LightPoint = 3; light clone 0x53599d0 insert 0x535a9c1, srcloc 0xF248DA0 `LightPointDescription`; entry 3 (0x66410a0) | [V] |
| tag 4 | 1 | `0x535a696  mov byte ptr [rbp+0x278],4`<br>`0x535a6a0  mov rax,[rax+0x380]` | LightGroupTag::ShadowAtlasFrame = 4; light clone 0x53599d0 insert 0x535a6a0, srcloc 0xF248D80 `ShadowAtlasFrameDescription`; entry 4 (0x6640ec1) | [V] |
| tag-map conflict | - | FrameBuilder.h:79-88 `enum class LightGroupTag : uint64_t { Ambient = 0, Directional = 1, GameplayMetadata = 2, LightPoint = 3, ShadowAtlasFrame = 4, ServerGraphicsOverrideParameters = 5, VoxelVolume = 6, TransitioningVoxelVolume = 7 };` | CONFLICT RESOLVED [V]: producer tag stores + __FUNCSIG__ srclocs prove tag 2 = GameplayMetadata and tag 3 = LightPoint; FrameBuilder.h wins; group_visitors.md 6g/6ih rows had them swapped (LightPoint@2 / GameplayMetadata@3) and are superseded. Tags 5/6/7 = ServerGraphicsOverrideParameters / VoxelVolume / TransitioningVoxelVolume | [V] |

## 2. Description field value names — UNKNOWN [?]

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| description value names | - | - | LightAmbientDescription (size 0x18), LightDirectionalDescription (0x24), LightPointDescription (0x108), GameplayMetadataDescription (0x84), ShadowAtlasFrameDescription (0x50): field reads are proven [V] in the visitor cases, but the exe has no RTTI and no description member name strings; headers type the fields as mValue* placeholders with static_assert offsets only; live dumps carry values only. Producer-side semantics (e.g. Ambient +0x00 copied from Atmosphere +0xA4) are inference [I], not names. Value names: unknown [?] — live capture of description bytes may confirm sizes/field layout [pending] | [?] |

## 3. Light-visitor writers to pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — PROVEN [V] (not redone this unit)

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| pass+0x800 | 8 | `0x6640e84  mov rdx,[rsi+0x800]`<br>`0x6640e8b  cmp rdx,[rsi+0x808]`<br>`0x6640eb4  add qword ptr [rsi+0x800],0x14`<br>`0x6641761  mov rdx,[rsi+0x800]`<br>`0x66417a2  add qword ptr [rsi+0x800],0x14`<br>`0x6641517  add qword ptr [rsi+0x800],0x14` | end cursor of the 0x14-byte summary list (cap +0x808); writers: Ambient 0x6640eb4, Directional 0x66417a2, Point 0x6641517 | [V] |
| pass+0x648 | 8 | `0x66416f8  lea rcx,[rsi+0x648]`<br>`0x66416ff  call 0x675FB30`<br>`0x664145a  lea rcx,[rsi+0x648]`<br>`0x6641461  call 0x675FB30` | end cursor of the 0x48-byte light-record vector (begin +0x648 / end +0x650); writers Directional (0x66416ff) and Point (0x6641461) via 0x675FB30 | [V] |
| pass+0x4A0 | 8 | `0x6640f78  mov r12,[rdi+0x4A0]`<br>`0x6641090  add qword ptr [rdi+0x4A0],0x84` | end cursor of the 0x84-byte GameplayMetadata vector (begin +0x498 / cap +0x4A8); writer tag 2, stride 0x84 | [V] |
| pass+0x1D0 | 8 | `0x66419c6  add qword ptr [rsi+0x1D0],0x50` | end cursor of the 0x50-byte ShadowAtlasFrame vector (begin +0x1C8 / cap +0x1D8); writer tag 4, stride 0x50 | [V] |

Every write is an end-cursor increment; no end-cursor pop/decrement exists anywhere in the exe [V, whole-image fld --w scans, prior units].

## 4. Consumers of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — NOT LOCATED statically [?]

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| pass+0x800 elements | - | - | - | [?] |
| pass+0x648 elements | - | - | - | [?] |
| pass+0x4A0 elements | - | - | - | [?] |
| pass+0x1D0 elements | - | - | - | [?] |

Negative angles already proven (NOT redone): whole-image fld --r/--w scans for all four offsets + begin cursors (0x7F8/0x650/0x498/0x1C8) show only the four writer cursor accesses plus stack/unrelated same-offset hits; endFrame full listing (sub_66232b0) contains none of the four offsets though it calls 0x5ABA5C0 3x; the three other direct 0x5ABA5C0 callers (0x66a6830, 0x66a9d50, 0x66bb7b0) touch only stack locals; rdis ptr 0x5aba5c0 finds no indirect caller slot; per-draw code 0x66ea3d0 appends to pass+0x8A8 only. No function loads a pass cursor and reads [cursor_reg + index*stride].

NEW ANGLE THIS UNIT (descscan2 --visitor light --case 2): descscan2 on GameplayMetadata case 0x6640f1b shows reads ONLY at desc+0x00..+0x3a and +0x3c..+0x84 (description fields copied verbatim into pass+0x4A0 vector), NO reads of pass+0x4A0 or any other pass offset — the case copies description data INTO the pass, never reads pass elements [V, tools/sigs/descscan2.py output]. No new consumer found.

NEW ANGLE THIS UNIT (unexamined 0x5ABA5C0 caller 0x5ab8e20): 0x5ab8e20 is a 0x2000-byte function ("ScreenshotInBuilder" string at 0x5ab8e8b, builds a screenshot request block). rdis dis of its first 60 instructions shows it reads [rcx+0x20..0x2E], [rdx+0x48], calls the engine allocator, then calls 0x5AB9970 — it does call 0x5ABA5C0 somewhere in its body but is a screenshot builder, not a light-pass consumer [V partial, timed out before full listing]. Not a consumer of the four pass vectors.

BGFX_MAP.md cross-check (sections 6gq/6h/6ih/6ib/6hi): 6gq confirms 0x5aba5c0 is ThreadLocalObject::get — per-thread 0x8B8-byte blocks, visitors queue into them, consumers merge later. 6ih line 1843-1844: Sky Atmosphere queues into pass+0x548, "a scan of 0x6600000-0x6800000 for [reg + 0x548] finds no reader" — same consumer blocker for all pass vectors. 6ih line 2041: "internals beyond the first fields and the consumers of the new pass vectors are open [?]". BGFX_MAP.md line 2032-2033: "Still open: roles of the pools (consumer: U-PASS3's 0xBB.. task bodies)." No consumer of pass+0x800/+0x648/+0x4A0/+0x1D0 named anywhere in BGFX_MAP.md [I from BGFX_MAP.md].

## 5. Live capture (orchestrator hint, 2026-11-22)

Request oc_u_er6_light_desc (visitor entry 0x6640D80, size 0x100, max 6, state pending, result awaited in docs/data/live/oc_u_er6_light_desc.txt): RDX = desc pointer at entry (docs/data/live/README.md CORRECTION 2026-11-15: light visitor takes {desc,tag} in RDX). `python tools/livecap/request.py result oc_u_er6_light_desc` → "no result yet (orchestrator has not run it)" [V live, request.py result command]. Existing live dump docs/data/live/light_visitor.txt shows tags 5/0/1/2/2/1 across its samples — no tag 3 (LightPoint) or tag 4 (ShadowAtlasFrame) sample yet [V live, docs/data/live/light_visitor.txt header + sample lines].

What the live data CAN add [V live when the orchestrator runs it]: description bytes per tag at visit time → confirm field sizes/runtime values for tag 3 (0x108 B) and tag 4 (0x50 B) vs Descriptions.h layouts; ret= at entry names the visitor caller chain.

What it CANNOT add (it is not a write-watch): it observes description bytes at visitor entry, not later reads of the pass vectors, so it cannot locate consumers of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — that needs a memory read/write watch on those element offsets, which this tool does not provide. Description value names also cannot come from live capture (values only, no names; no RTTI/name strings exist in the exe).

## CLOSES?

PENDING live result — see TOOL REQUESTS. NO until: (1) description value names confirmed [V live] or stated [?], and (2) either a consumer of one of pass+0x800/+0x648/+0x4A0/+0x1D0 is located [V live] OR a live capture proves no consumer drains them during the capture window (write-only confirmed live) — then CLOSES? NO with the single blocking fact "consumers not located; vectors write-only in live capture" OR YES if a consumer is named. Tag names and the tag-name conflict are closed [V]. Description value names remain unknown [?] (no RTTI/name strings; headers use mValue* placeholders).

## TOOL REQUESTS

CAPTURE REQUESTED oc_u_er6_light_desc — already pending at visitor entry 0x6640D80 (size 0x100, max 6); result awaited in docs/data/live/oc_u_er6_light_desc.txt. No new request added (4 pending slot limit reached; this is the R6 entry the orchestrator hint points at).