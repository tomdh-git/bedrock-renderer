## NEXT
DONE

# U-ER6 — R6: LightAmbient / LightDirectional / Light tag 2 / tag 3 / tag 4 (1.26.62.01)

Goal: close R6 — tag value names, the group_visitors.md vs FrameBuilder.h LightGroupTag conflict, and the consumers (draining readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0.

Static analysis only; RVAs image-relative. Every `0xRVA  instr` line below is copied verbatim from the listings already verified in oc_U-ER6_r1..r4 and is re-checked by tools/sigs/verify_oc.py on this file. Tags: [V] seen in disassembly (RVA cited) | [I] inferred | [?] unknown.

Input data (already computed by the orchestrator, not re-generated): docs/functions/6640d80_light_visitor.md; docs/functions/light_game_descriptions.md; docs/functions/group_visitors.md; docs/functions/5aba5c0.md; docs/data/live/light_visitor.txt; src/sdk/mc/deps/minecraft_renderer/framebuilder/FrameBuilder.h (LightGroupTag enum); Descriptions.h. A live-capture request for this item already exists: oc_u_er6_light_desc (visitor entry 0x6640D80, size 0x100, max 6, state pending, no result yet) — see section 5.

Pass layout (proven [V] in oc_U-ER6_r3/r4, not re-derived): the pass object is the per-thread value of ThreadLocalObject 0x5ABA5C0 (node 0x8B8 bytes, value at node+0x10); the visitor gets rsi = pass via 0x5ABA5C0 with rcx = frameCtx+0x10+0x9D0. Four vectors inside the pass: summary list (+0x7F8 begin / +0x800 end / +0x808 cap, stride 0x14), light records (+0x648 begin / +0x650 end, stride 0x48), GameplayMetadata (+0x498 begin / +0x4A0 end / +0x4A8 cap, stride 0x84), ShadowAtlasFrame (+0x1C8 begin / +0x1D0 end / +0x1D8 cap, stride 0x50) [V].

## 1. Tag -> type / LightGroupTag — RESOLVED [V]

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| variant+0x08 tag | 1 | `0x6640dc4  movzx eax,byte ptr [rdx+8]`<br>`0x6640de6  jmp rax` | tag byte at variant+0x08; dispatch jmp rax via jump table 0xF2BF2B0 (entries 0=0x6640de8, 1=0x66415b0, 2=0x6640f1b, 3=0x66410a0, 4=0x6640ec1, 5=0x66417af, 6=0x664187d, 7=0x6641524) | [V] |
| tag 0 | 1 | `0x53e3511  mov byte ptr [rbp+0x138],0` | LightGroupTag::Ambient = 0 (FrameBuilder.h:79-88); producer clone 0x53e2c00, srcloc 0xF248E70 `__FUNCSIG__ FrameBuilder::insert [TDescription = RenderLightAmbientDescription]`; jump-table entry 0 (0x6640de8) | [V] |
| tag 1 | 1 | `0x53709d4  mov byte ptr [rbp+0x18],1` | LightGroupTag::Directional = 1; thin clone 0x5370960, srcloc 0xF248F70 (LightDirectionalDescription); entry 1 (0x66415b0) | [V] |
| tag 2 | 1 | `0x53e5fb4  mov byte ptr [rbp-0x18],2`<br>`0x53e5fbf  mov rax,[rax+0x380]` | LightGroupTag::GameplayMetadata = 2; clone 0x53e5910, Light vslot 0x380 insert 0x53e5fbf, srcloc 0xF248ED0 `__FUNCSIG__ ... gamecomponents::GameplayMetadata`; entry 2 (0x6640f1b) | [V] |
| tag 3 | 1 | `0x535a9b7  mov byte ptr [rbp+0x278],3`<br>`0x535a9c1  mov rax,[rax+0x380]`<br>`0x535a9ce  call qword ptr [0xF99FFA0]` | LightGroupTag::LightPoint = 3; light clone 0x53599d0 insert 0x535a9ce, srcloc 0xF248DA0 `LightPointDescription`; entry 3 (0x66410a0) | [V] |
| tag 4 | 1 | `0x535a696  mov byte ptr [rbp+0x278],4`<br>`0x535a6a0  mov rax,[rax+0x380]` | LightGroupTag::ShadowAtlasFrame = 4; light clone 0x53599d0 insert 0x535a6a0, srcloc 0xF248D80 `ShadowAtlasFrameDescription`; entry 4 (0x6640ec1) | [V] |
| tag-map conflict | - | - | FrameBuilder.h:79-88 `enum class LightGroupTag : uint64_t { Ambient = 0, Directional = 1, GameplayMetadata = 2, LightPoint = 3, ShadowAtlasFrame = 4, ServerGraphicsOverrideParameters = 5, VoxelVolume = 6, TransitioningVoxelVolume = 7 };` — CONFLICT RESOLVED [V]: producer tag stores + __FUNCSIG__ srclocs prove tag 2 = GameplayMetadata and tag 3 = LightPoint, so FrameBuilder.h wins; group_visitors.md 6g/6ih rows (LightPoint@2 / GameplayMetadata@3) had them swapped and are superseded. Tags 5/6/7 = ServerGraphicsOverrideParameters / VoxelVolume / TransitioningVoxelVolume [V] | [V] |

## 2. Description field value names — UNKNOWN [?]

LightAmbientDescription (size 0x18), LightDirectionalDescription (0x24), LightPointDescription (0x108), GameplayMetadataDescription (0x84), ShadowAtlasFrameDescription (0x50): field reads/writes at offsets ambient+0x00..+0x14, directional+0x00..+0x20, gm+0x00..+0x3C, lp+0x00..+0xE8, sa+0x00..+0x48 are proven [V] in oc_U-ER6_r1..r4 (visitor reads description fields into pass elements). The exe has no RTTI and no description member name strings; headers type the fields as mValue* placeholders with static_assert offsets only; live dumps (docs/data/live/light_visitor.txt) carry values only. Producer-side semantics (e.g. Ambient +0x00 copied from Atmosphere +0xA4) are inference [I], not names. Value names: unknown [?].

## 3. Light-visitor writers to pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — PROVEN [V] (not re-derived this unit)

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| pass+0x800 | 8 | `0x6640e84  mov rdx,[rsi+0x800]`<br>`0x6640eb4  add qword ptr [rsi+0x800],0x14`<br>`0x6641761  mov rdx,[rsi+0x800]`<br>`0x66417a2  add qword ptr [rsi+0x800],0x14`<br>`0x6641517  add qword ptr [rsi+0x800],0x14` | end cursor of the 0x14-byte summary list (cap +0x808); writers: Ambient 0x6640eb4, Directional 0x66417a2, Point 0x6641517 [V] | [V] |
| pass+0x808 | 8 | `0x6640e8b  cmp rdx,[rsi+0x808]` | summary list cap cursor [V] | [V] |
| pass+0x648 | 8 | `0x66416f8  lea rcx,[rsi+0x648]`<br>`0x66416ff  call 0x675FB30`<br>`0x664145a  lea rcx,[rsi+0x648]`<br>`0x6641461  call 0x675FB30` | end cursor of the 0x48-byte light-record vector (begin +0x648 / end +0x650); writers Directional (0x66416ff) and Point (0x6641461) via 0x675FB30 [V] | [V] |
| pass+0x650 | 4 | `0x6641729  mov eax,[rsi+0x650]`<br>`0x6641735  shr eax,3`<br>`0x6641738  imul eax,0xFFFF8E39` | light-record end cursor; light-record index = (end - begin)/0x48 - 1 [V] | [V] |
| pass+0x4A0 | 8 | `0x6640f78  mov r12,[rdi+0x4A0]`<br>`0x6641090  add qword ptr [rdi+0x4A0],0x84` | end cursor of the 0x84-byte GameplayMetadata vector (begin +0x498 / cap +0x4A8); writer tag 2, stride 0x84 [V] | [V] |
| pass+0x4A8 | 8 | `0x6640f7f  cmp r12,[rdi+0x4A8]` | GameplayMetadata vector cap cursor [V] | [V] |
| pass+0x1D0 | 8 | `0x66419c6  add qword ptr [rsi+0x1D0],0x50` | end cursor of the 0x50-byte ShadowAtlasFrame vector (begin +0x1C8 / cap +0x1D8); writer tag 4, stride 0x50 [V] | [V] |

Every one of these writes is an end-cursor increment; no end-cursor pop/decrement exists anywhere in the exe [V, whole-image fld --w scans, earlier units]. Per-draw code 0x66ea3d0 obtains the pass via 0x5ABA5C0 (`0x66eca8f  call 0x5ABA5C0`) and appends u16 indices to the *other* pass vector at pass+0x8A8 (`0x66ecb03  mov rdx,[rbx+0x8A8]`, `0x66ecb1e  mov [rdx],ax`, `0x66ecb21  add qword ptr [rbx+0x8A8],2`) [V] — writes during draw recording, reads none of the four cursors.

## 4. Consumers of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — NOT LOCATED [?] (static analysis exhausted)

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| pass+0x800 elements | - | - | - | [?] |
| pass+0x648 elements | - | - | - | [?] |
| pass+0x4A0 elements | - | - | - | [?] |
| pass+0x1D0 elements | - | - | - | [?] |

New angles tried for consumers (all negative; not re-run here): endFrame listing sub_66232b0 [0x66232b0..0x662e680) contains no access to [reg+0x7F8/+0x800/+0x648/+0x650/+0x4A0/+0x498/+0x1D0/+0x1C8] though it calls 0x5ABA5C0 three times — endFrame uses other pass vectors instead [V]; the three other direct 0x5ABA5C0 callers (0x66a6830, 0x66a9d50, 0x66bb7b0) touch only stack locals at those offsets [V]; `rdis ptr 0x5aba5c0`: 0 indirect slots [V]; whole-image `fld 0x800/0x648/0x4A0/0x1D0 --r/--w` scans (plus begin cursors 0x7F8/0x650/0x498/0x1C8) show only the writer cursor accesses above — every write an end-cursor increment, no pop/decrement, no `[cursor_reg + index*stride]` element read anywhere [V].

## 5. Live capture (orchestrator hint, 2026-11-22)

Request oc_u_er6_light_desc (visitor entry 0x6640D80, size 0x100, max 6, state pending, result awaited in docs/data/live/oc_u_er6_light_desc.txt): RDX = desc pointer at entry (docs/data/live/README.md CORRECTION 2026-11-15: light visitor takes {desc,tag} in RDX). Existing live dump docs/data/live/light_visitor.txt (same target, earlier batch) shows tags 5/0/1/2/2/1 across its samples — no tag 3 (LightPoint) or tag 4 (ShadowAtlasFrame) sample yet [V live, docs/data/live/light_visitor.txt header + sample lines].

What the live data CAN add [V live when the orchestrator runs it]: description bytes per tag at visit time → confirm field sizes/runtime values for tag 3 (0x108 B) and tag 4 (0x50 B) vs Descriptions.h layouts; ret= at entry names the visitor caller chain.

What it CANNOT add (it is not a write-watch): it observes description bytes at visitor entry, not later reads of the pass vectors, so it cannot locate consumers of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — that needs a memory read/write watch on those element offsets, which this tool does not provide. Description value names also cannot come from live capture (values only, no names; no RTTI/name strings exist in the exe).

CLOSES? NO — single blocking fact: no draining reader (element consumer) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 exists anywhere in Minecraft.Windows.exe 1.26.62.01: all four vectors are write-only [V] (only end-cursor increments by the Light visitor: 0x6640eb4/0x66417a2/0x6641517 for +0x800, 0x66416ff/0x6641461 for +0x648, 0x6641090 for +0x4A0, 0x66419c6 for +0x1D0; no end-cursor pop/decrement and no element-indexed read anywhere — whole-image fld scans, endFrame listing, the three other 0x5ABA5C0 callers, rdis ptr all negative [V]). Static analysis is exhausted for consumers (2026-11-22 review); a live write-watch on those offsets would be needed, which the entry-point capture tool cannot provide. Tag names and the tag-name conflict are closed [V] (tag 2 = GameplayMetadata, tag 3 = LightPoint; FrameBuilder.h wins). Description value names remain unknown [?] (no RTTI/name strings; headers use mValue* placeholders).

## TOOL REQUESTS

CAPTURE REQUESTED oc_u_er6_light_desc — pending at visitor entry 0x6640D80 (size 0x100, max 6); result awaited in docs/data/live/oc_u_er6_light_desc.txt. No new request added (4 pending slot limit reached; this is the R6 entry the orchestrator hint points at).
