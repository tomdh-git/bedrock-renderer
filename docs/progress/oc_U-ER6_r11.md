## NEXT
DONE

# U-ER6 — R6: LightAmbient / LightDirectional / Light tag 2 / tag 3 / tag 4 (1.26.62.01)

Goal: close R6 — description value names, the group_visitors.md vs FrameBuilder.h LightGroupTag tag-name conflict, and the consumers (draining element readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0. RETRY #1: oc_U-ER6_r1..r10 exhausted static analysis (their quoted lines passed tools/sigs/verify_oc.py 83/83); this unit checks the live-capture result, tries the remaining live angles, and reports CLOSES? honestly. Static analysis only; RVAs image-relative; every `0xRVA  instr` line copied verbatim from verified listings. Tags: [V] seen in disassembly (RVA cited) | [I] inferred | [?] unknown. No skipped offsets.

Input data (read fully, not re-generated): docs/functions/6640d80_light_visitor.md; docs/functions/5aba5c0.md; docs/functions/group_visitors.md; docs/functions/light_game_descriptions.md; docs/data/live/light_visitor.txt; docs/data/live/README.md; docs/progress/capture_requests.json; src/sdk/mc/deps/minecraft_renderer/framebuilder/FrameBuilder.h (LightGroupTag enum); Descriptions.h / LightDescriptions.h / LightGameDescriptions.h.

The pass object is the per-thread value of ThreadLocalObject 0x5ABA5C0 (value at node+0x10). Visitor cases call 0x5ABA5C0 with rcx = frameCtx+0x10+0x9D0 and get rsi = pass [V]. All four vectors live inside this pass object: begin/end/cap cursors at (+0x7F8/+0x800/+0x808) summary stride 0x14, (+0x648/+0x650) light-record stride 0x48, (+0x498/+0x4A0/+0x4A8) GameplayMetadata stride 0x84, (+0x1C8/+0x1D0/+0x1D8) ShadowAtlasFrame stride 0x50 [V, from the light-visitor listings].

## 1. Tag -> type / value names (LightGroupTag) — resolved [V] (carried from oc_U-ER6_r1..r10, not re-run)

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| variant+0x08 tag | 1 | `0x6640dc4  movzx eax,byte ptr [rdx+8]`<br>`0x6640de6  jmp rax` | tag byte at variant+0x08 loaded by the Light visitor; dispatch `jmp rax` via jump table 0xF2BF2B0 (entries: 0=0x6640de8 Ambient, 1=0x66415b0 Directional, 2=0x6640f1b GameplayMetadata, 3=0x66410a0 LightPoint, 4=0x6640ec1 ShadowAtlasFrame, 6=0x664187d VoxelVolume, 7=0x6641524 TransitioningVoxelVolume) [V] | [V] |
| tag 0 | 1 | `0x53e3511  mov byte ptr [rbp+0x138],0` | LightGroupTag::Ambient = 0 (FrameBuilder.h:79-88); producer clone 0x53e2c00, srcloc 0xF248E70 `FrameBuilder::insert [TDescription = RenderLightAmbientDescription]`; JT entry 0 [V] | [V] |
| tag 1 | 1 | `0x53709d4  mov byte ptr [rbp+0x18],1` | LightGroupTag::Directional = 1; thin clone 0x5370960, srcloc 0xF248F70 (LightDirectionalDescription); JT entry 1 [V] | [V] |
| tag 2 | 1 | `0x53e5fb4  mov byte ptr [rbp-0x18],2`<br>`0x53e5fbf  mov rax,[rax+0x380]` | LightGroupTag::GameplayMetadata = 2; clone 0x53e5910, Light vslot 0x380 insert 0x53e5fbf, srcloc 0xF248ED0 `__FUNCSIG__ ... gamecomponents::GameplayMetadata`; JT entry 2 [V] | [V] |
| tag 3 | 1 | `0x535a9b7  mov byte ptr [rbp+0x278],3`<br>`0x535a9c1  mov rax,[rax+0x380]`<br>`0x535a9ce  call qword ptr [0xF99FFA0]` | LightGroupTag::LightPoint = 3; light clone 0x53599d0 insert 0x535a9ce, srcloc 0xF248DA0 `LightPointDescription`; JT entry 3 [V] | [V] |
| tag 4 | 1 | `0x535a696  mov byte ptr [rbp+0x278],4`<br>`0x535a6a0  mov rax,[rax+0x380]` | LightGroupTag::ShadowAtlasFrame = 4; light clone 0x53599d0 insert 0x535a6a0, srcloc 0xF248D80 `ShadowAtlasFrameDescription`; JT entry 4 [V] | [V] |
| tag-name conflict | - | FrameBuilder.h:79-88 `enum class LightGroupTag : uint64_t { Ambient = 0, Directional = 1, GameplayMetadata = 2, LightPoint = 3, ShadowAtlasFrame = 4, ServerGraphicsOverrideParameters = 5, VoxelVolume = 6, TransitioningVoxelVolume = 7 };` | CONFLICT RESOLVED [V]: producer tag stores + __FUNCSIG__ srclocs prove tag 2 = GameplayMetadata and tag 3 = LightPoint, so FrameBuilder.h wins; group_visitors.md rows had them swapped (LightPoint@2 / GameplayMetadata@3) and are superseded. Tags 5/6/7 = ServerGraphicsOverrideParameters / VoxelVolume / TransitioningVoxelVolume [V] | [V] |

## 2. Light-visitor writers to pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — proven [V] (carried from r1-r10, not re-run)

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| pass+0x800 | 8 | `0x6640e84  mov rdx,[rsi+0x800]`<br>`0x6640e8b  cmp rdx,[rsi+0x808]`<br>`0x6640eb4  add qword ptr [rsi+0x800],0x14`<br>`0x6641761  mov rdx,[rsi+0x800]`<br>`0x66417a2  add qword ptr [rsi+0x800],0x14`<br>`0x6641517  add qword ptr [rsi+0x800],0x14` | end cursor of the 0x14-byte summary list (cap +0x808); writers: Ambient 0x6640eb4, Directional 0x66417a2, Point 0x6641517 [V] | [V] |
| pass+0x808 | 8 | `0x6640e8b  cmp rdx,[rsi+0x808]` | summary list cap cursor [V] | [V] |
| pass+0x648 | 8 | `0x66416f8  lea rcx,[rsi+0x648]`<br>`0x66416ff  call 0x675FB30`<br>`0x664145a  lea rcx,[rsi+0x648]`<br>`0x6641461  call 0x675FB30` | end cursor of the 0x48-byte light-record vector (begin +0x648 / end +0x650); writers: Directional 0x66416ff, Point 0x6641461 via 0x675FB30 [V] | [V] |
| pass+0x650 | 4 | `0x6641729  mov eax,[rsi+0x650]`<br>`0x6641735  shr eax,3`<br>`0x6641738  imul eax,0xFFFF8E39` | light-record end cursor; light-record index = (end - begin)/0x48 - 1 [V] | [V] |
| pass+0x4A0 | 8 | `0x6640f78  mov r12,[rdi+0x4A0]`<br>`0x6641090  add qword ptr [rdi+0x4A0],0x84` | end cursor of the 0x84-byte GameplayMetadata vector (begin +0x498 / cap +0x4A8); writer tag 2, stride 0x84 [V] | [V] |
| pass+0x4A8 | 8 | `0x6640f7f  cmp r12,[rdi+0x4A8]` | GameplayMetadata vector cap cursor [V] | [V] |
| pass+0x1D0 | 8 | `0x66419c6  add qword ptr [rsi+0x1D0],0x50` | end cursor of the 0x50-byte ShadowAtlasFrame vector (begin +0x1C8 / cap +0x1D8); writer tag 4, stride 0x50 [V] | [V] |

Every write above is an end-cursor increment; no end-cursor pop/decrement exists anywhere in the exe [V, whole-image `fld --w` scans, r1-r10].

## 3. Consumers of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — NOT located (static angles exhausted; live angle checked this unit)

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| pass+0x800 element read | - | - | no draining reader of the 0x14-byte summary elements anywhere in Minecraft.Windows.exe 1.26.62.01; only the three end-cursor writers in section 2 [V] | [?] |
| pass+0x648 element read | - | - | no draining reader of the 0x48-byte light-record elements anywhere in the exe [V writes only] | [?] |
| pass+0x4A0 element read | - | - | no draining reader of the 0x84-byte GameplayMetadata elements anywhere in the exe [V writes only] | [?] |
| pass+0x1D0 element read | - | - | no draining reader of the 0x50-byte ShadowAtlasFrame elements anywhere in the exe [V writes only] | [?] |

New angles tried this unit (RETRY #1) — all negative or inapplicable:

- `python tools/livecap/request.py result oc_u_er6_light_desc` → "no result yet (orchestrator has not run it)" [shell]. The capture is already queued in docs/progress/capture_requests.json (name oc_u_er6_light_desc, rva 0x6640d80 = light-visitor entry, size 0x100, max 6, state=pending); 4 requests are pending so no new request can be added (tool limit, <=4 pending per batch). Even when run, function-entry sampling dumps RDX = desc bytes + ret = caller chain only; it cannot install a read/write watchpoint on pass+0x800/+0x648/+0x4A0/+0x1D0, so it cannot locate the consumers (stated limitation, oc_U-ER6_r7/r8).
- livemem: live session done (docs/data/live/_status.txt: DONE t=120); no pass-object runtime address available — `rdis imm 0x5aba5c0` = 0 hits, i.e. no static data reference to the ThreadLocalObject 0x5ABA5C0 global [V, oc_U-ER6_r10]; livemem cannot scan or loop over ranges, so there is nothing to point it at [V live status].
- Static angles carried from r1-r10 (not re-run, all [V]): whole-image `rdis fld --r/--w` scans for all four offsets and begin cursors 0x7F8/0x650/0x498/0x1C8 (every hit is a stack local, a writer cursor access, or the same offset on an unrelated object; writes are only end-cursor increments, no pop/decrement; no `[pass_cursor + index*stride]` element read for any of the four offsets); endFrame listing sub_66232b0 (no access to the four offsets although it calls 0x5ABA5C0 3×); all ~200 `0x5ABA5C0` callers via `rdis xr` (none drain); `rdis ptr 0x5aba5c0` (0 indirect slots), `rdis imm 0x5aba5c0` (0 static data refs); `rdis xr 0x6640d80` (single caller 0x6640c44 in sub_6640ae0); `rdis fn 0x6640d80` (no vcall slots); descscan2 all light cases (field reads proven [V], names unknown).

## 4. Description layouts and value names — offsets/sizes [V], semantic names [?]

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| description field reads (all light cases) | - | - | desc reads and sizes proven [V] per case via descscan2: LightAmbientDescription 0x18 (+0x00/+0x08/+0x10/+0x14 read), LightDirectionalDescription 0x24 (+0x00/+0x10/+0x14/+0x1C/+0x20), GameplayMetadataDescription 0x84 (+0x00..+0x80), LightPointDescription 0x108 (+0x00..+0x100), ShadowAtlasFrameDescription 0x50 (+0x00..+0x48); verbatim lines in oc_U-ER6_r1..r5 [V] | [V] |
| description value names | - | - | the release exe has no RTTI and no description member-name strings; headers type the fields as mValue* placeholders with static_assert offsets only; live dumps carry values only (light_visitor.txt has tags 0/1/2/5, no tag 3/4 bytes). Pending capture oc_u_er6_light_desc would add runtime bytes + ret= caller chain [V live when available] but not symbolic names. Value names: unknown [?] | [?] |

CLOSES? NO — the consumers (draining element readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 are not located anywhere in Minecraft.Windows.exe 1.26.62.01: all four vectors are write-only statically (only the Light-visitor end-cursor writers are [V]); every write is an end-cursor increment, no end-cursor pop/decrement exists, no element-indexed read of any of the four vectors exists; whole-image `fld --r/--w` scans, the endFrame listing, all ~200 `0x5ABA5C0` callers, and `rdis ptr`/`imm`/`xr` indirect checks are negative [V] (carried from r1-r10). The producer-entry live capture oc_u_er6_light_desc is queued [pending] but entry sampling cannot install a read watchpoint on the pass vectors, so even when it runs it cannot find consumers; livemem has no target (_status.txt DONE, no static data reference to the TLO global, no scan/loop) [V live status]. Single blocking fact: no draining reader of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 exists in the exe and no available tool can establish the watchpoint that would find one. Description value names also remain unknown [?]. Resolved [V]: tag 2 = GameplayMetadata, tag 3 = LightPoint; FrameBuilder.h wins the tag-name conflict; the four writers are closed [V].

## TOOL REQUESTS

CAPTURE REQUESTED oc_u_er6_light_desc | `python tools/livecap/request.py add oc_u_er6_light_desc 0x6640d80 --size 0x100 --max 6 --why "R6: light-visitor entry producer capture. RDX = desc pointer (docs/data/live/README.md CORRECTION 2026-11-15). Dump tag 3 (LightPoint, 0x108 B) and tag 4 (ShadowAtlasFrame, 0x50 B) desc bytes at runtime vs Descriptions.h layouts; ret= names the visitor caller chain (sub_6640ae0 wrapper, confirmed by `rdis xr 0x6640d80`)."` | already queued (state=pending) in docs/progress/capture_requests.json; awaiting docs/data/live/oc_u_er6_light_desc.txt. Producer-side only — cannot find pass-vector consumers; no read/write watchpoint tool available, so consumers stay [?]. Helper scripts: None (no throwaway scripts written; all evidence from existing tools and already-verified listings).
