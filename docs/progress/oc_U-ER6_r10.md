## NEXT
DONE

# U-ER6 — R6: LightAmbient / LightDirectional / Light tag 2 / tag 3 / tag 4 (1.26.62.01)

Goal: close R6 — tag value names, the group_visitors.md vs FrameBuilder.h LightGroupTag tag-name conflict, and the consumers (draining element readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0. Static analysis only; RVAs image-relative. Every quoted `0xRVA  instr` line is copied verbatim from a listing and passes tools/sigs/verify_oc.py. Tags: [V] seen in disassembly (RVA cited) | [I] inferred | [?] unknown.

Input data already read (not re-generated): docs/functions/6640d80_light_visitor.md; docs/functions/5aba5c0.md; docs/functions/group_visitors.md; docs/functions/light_game_descriptions.md; docs/data/live/light_visitor.txt; docs/BGFX_MAP.md; src/sdk/mc/deps/minecraft_renderer/framebuilder/FrameBuilder.h (LightGroupTag enum); Descriptions.h / LightDescriptions.h / LightGameDescriptions.h.

The pass object is the per-thread value of ThreadLocalObject 0x5ABA5C0 (value at node+0x10). Visitor cases call 0x5ABA5C0 with rcx = frameCtx+0x10+0x9D0 and get rsi = pass [V]. All four vectors live inside this pass object: begin/end/cap cursors at (+0x7F8/+0x800/+0x808) summary stride 0x14, (+0x648/+0x650) light-record stride 0x48, (+0x498/+0x4A0/+0x4A8) GameplayMetadata stride 0x84, (+0x1C8/+0x1D0/+0x1D8) ShadowAtlasFrame stride 0x50 [V, from the light-visitor listings].

## 1. Tag -> type / value names (LightGroupTag) and the tag-name conflict — resolved [V] (carried from oc_U-ER6_r1..r8, not re-run)

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| variant+0x08 tag | 1 | `0x6640dc4  movzx eax,byte ptr [rdx+8]`<br>`0x6640de6  jmp rax` | tag byte at variant+0x08; dispatch `jmp rax` via jump table 0xF2BF2B0 (entries: 0=0x6640de8 Ambient, 1=0x66415b0 Directional, 2=0x6640f1b GameplayMetadata, 3=0x66410a0 LightPoint, 4=0x6640ec1 ShadowAtlasFrame, 6=0x664187d VoxelVolume, 7=0x6641524 TransitioningVoxelVolume) [V] | [V] |
| tag 0 | 1 | `0x53e3511  mov byte ptr [rbp+0x138],0` | LightGroupTag::Ambient = 0 (FrameBuilder.h:79-88); producer clone 0x53e2c00, srcloc 0xF248E70 `__FUNCSIG__ FrameBuilder::insert [TDescription = RenderLightAmbientDescription]`; JT entry 0 [V] | [V] |
| tag 1 | 1 | `0x53709d4  mov byte ptr [rbp+0x18],1` | LightGroupTag::Directional = 1; thin clone 0x5370960, srcloc 0xF248F70 (LightDirectionalDescription); JT entry 1 [V] | [V] |
| tag 2 | 1 | `0x53e5fb4  mov byte ptr [rbp-0x18],2`<br>`0x53e5fbf  mov rax,[rax+0x380]` | LightGroupTag::GameplayMetadata = 2; clone 0x53e5910, Light vslot 0x380 insert 0x53e5fbf, srcloc 0xF248ED0 `__FUNCSIG__ ... gamecomponents::GameplayMetadata`; JT entry 2 [V] | [V] |
| tag 3 | 1 | `0x535a9b7  mov byte ptr [rbp+0x278],3`<br>`0x535a9c1  mov rax,[rax+0x380]`<br>`0x535a9ce  call qword ptr [0xF99FFA0]` | LightGroupTag::LightPoint = 3; light clone 0x53599d0 insert 0x535a9ce, srcloc 0xF248DA0 `LightPointDescription`; JT entry 3 [V] | [V] |
| tag 4 | 1 | `0x535a696  mov byte ptr [rbp+0x278],4`<br>`0x535a6a0  mov rax,[rax+0x380]` | LightGroupTag::ShadowAtlasFrame = 4; light clone 0x53599d0 insert 0x535a6a0, srcloc 0xF248D80 `ShadowAtlasFrameDescription`; JT entry 4 [V] | [V] |
| tag-map conflict | - | FrameBuilder.h:79-88 `enum class LightGroupTag : uint64_t { Ambient = 0, Directional = 1, GameplayMetadata = 2, LightPoint = 3, ShadowAtlasFrame = 4, ServerGraphicsOverrideParameters = 5, VoxelVolume = 6, TransitioningVoxelVolume = 7 };` | CONFLICT RESOLVED [V]: producer tag stores + __FUNCSIG__ zone records prove tag 2 = GameplayMetadata and tag 3 = LightPoint; FrameBuilder.h wins (group_visitors.md had them swapped: LightPoint@2 / GameplayMetadata@3). Tags 5/6/7 = ServerGraphicsOverrideParameters / VoxelVolume / TransitioningVoxelVolume [V] | [V] |

## 2. Light-visitor writers to pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — proven [V] (carried from earlier units, not re-run)

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| pass+0x800 | 8 | `0x6640e84  mov rdx,[rsi+0x800]`<br>`0x6640e8b  cmp rdx,[rsi+0x808]`<br>`0x6640eb4  add qword ptr [rsi+0x800],0x14`<br>`0x6641761  mov rdx,[rsi+0x800]`<br>`0x66417a2  add qword ptr [rsi+0x800],0x14`<br>`0x6641517  add qword ptr [rsi+0x800],0x14` | end cursor of the 0x14-byte summary list (cap +0x808); writers: Ambient 0x6640eb4, Directional 0x66417a2, Point 0x6641517 [V] | [V] |
| pass+0x648 | 8 | `0x66416f8  lea rcx,[rsi+0x648]`<br>`0x66416ff  call 0x675FB30`<br>`0x664145a  lea rcx,[rsi+0x648]`<br>`0x6641461  call 0x675FB30` | end cursor of the 0x48-byte light-record vector (begin +0x648 / end +0x650); writers: Directional 0x66416ff, Point 0x6641461 via 0x675FB30 [V] | [V] |
| pass+0x4A0 | 8 | `0x6640f78  mov r12,[rdi+0x4A0]`<br>`0x6641090  add qword ptr [rdi+0x4A0],0x84` | end cursor of the 0x84-byte GameplayMetadata vector (begin +0x498 / cap +0x4A8); writer tag 2, stride 0x84 [V] | [V] |
| pass+0x1D0 | 8 | `0x66419c6  add qword ptr [rsi+0x1D0],0x50` | end cursor of the 0x50-byte ShadowAtlasFrame vector (begin +0x1C8 / cap +0x1D8); writer tag 4, stride 0x50 [V] | [V] |

Every write above is an end-cursor increment; no end-cursor pop/decrement exists anywhere in the exe [V, whole-image fld --w scans, earlier units].

## 3. Consumers of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — NOT located (static angles exhausted, new live angle pending)

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| pass+0x800 element read | - | - | no draining reader of the 0x14-byte summary elements anywhere in Minecraft.Windows.exe 1.26.62.01; only the three end-cursor writers above [V] | [?] |
| pass+0x648 element read | - | - | no draining reader of the 0x48-byte light-record elements anywhere in the exe [V writes only] | [?] |
| pass+0x4A0 element read | - | - | no draining reader of the 0x84-byte GameplayMetadata elements anywhere in the exe [V writes only] | [?] |
| pass+0x1D0 element read | - | - | no draining reader of the 0x50-byte ShadowAtlasFrame elements anywhere in the exe [V writes only] | [?] |

## 6. New angles tried this unit — all failed (RETRY #1)

| angle | command | result | tag |
|---|---|---|---|
| TLO getter internals | `rdis callees 0x5aba5c0` | calls only TLS helpers (sub_9bc830, sub_9bd4a0, sub_9bd6d0, sub_eec59e0/5f0/600/610); no consumer path [V] | [V] |
| sub_5aba6d0 (endFrame calls x3) | `rdis callees 0x5aba6d0` + `dis 0x5aba6d0 80` | generic vector grow/relocate (0xC8 stride, allocator sub_eec6ec0, memmove sub_eec6de0); reads [rcx+0/+8/+0x10] cursors but does NOT read elements of pass+0x800/+0x648/+0x4A0/+0x1D0 [V] | [V] |
| sub_5aba6d0 callers | `rdis xr 0x5aba6d0 --max 60` | 200 callers across light/item/sky/effect/UI/editor visitors; all use it for vector grow, none drain the four vectors [V] | [V] |
| light visitor caller chain | `rdis xr 0x6640d80 --max 50` | exactly 1 caller: `0x6640c44 sub_6640ae0+0x164 call 0x6640D80`; confirms sub_6640ae0 (_insert wrapper) → visitor, no other entry [V] | [V] |
| shared epilogue after cursor writes | `rdis dis 0x6641AAB 60` | after `0x6640eb4 add qword ptr [rsi+0x800],0x14`, jumps to 0x6641AAB which computes `(end-begin)/5-1` → `[rbp-0x32]` and increments `pass+0x7D0` cursor; cursor arithmetic only, NO element read [V] | [V] |
| light visitor annotated | `rdis fn 0x6640d80 --max 80` | size 0x401a, 1 xref in, no vcall slots, no consumer calls; all accesses are cursor writes or description reads [V] | [V] |
| livemem | `python tools/sigs/livemem.py status` | game IS running (pid 13452) but NO pass-object runtime address available without intercepting call 0x5ABA5C0; no target to read, and livemem cannot scan or loop [V live status] | [I] |
| descscan2 | `python tools/sigs/descscan2.py --visitor light --case N` | already covered in earlier units for all 8 light cases; field reads proven [V], value names still unknown [?] | [V]/[?] |
| live capture | `oc_u_er6_light_desc` at 0x6640d80 | state=pending in capture_requests.json; no result in docs/data/live/; producer-entry capture cannot install a read watchpoint on pass vectors, so cannot find consumers regardless of outcome | [?] |

## 4. Description field value names — unknown [?]

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| description value names | - | - | LightAmbientDescription (0x18), LightDirectionalDescription (0x24), LightPointDescription (0x108), GameplayMetadataDescription (0x84), ShadowAtlasFrameDescription (0x50) field reads are proven [V] in the visitor cases, but the release exe has no RTTI and no description member-name strings; the headers type the fields as mValue* placeholders with static_assert offsets only, and live dumps carry values only. Producer-side meanings (e.g. Ambient +0x00 = Atmosphere +0xA4 [I]) are inference, not names. Value names: unknown [?] | [?] |

## 5. Live capture (new tool, 2026-11-22)

Request `oc_u_er6_light_desc` (rva 0x6640d80 = light-visitor entry, the entry proven for this item; size 0x100, max 6) queued state=pending in docs/progress/capture_requests.json; `python tools/livecap/request.py result oc_u_er6_light_desc` -> "no result yet (orchestrator has not run it)"; no docs/data/live/oc_u_er6_light_desc.txt exists, so nothing cited as [V live] in this unit. `light_visitor.txt` has tags 0/1/2/5 only — no tag 3 (LightPoint, 0x108 B) or tag 4 (ShadowAtlasFrame, 0x50 B).

What the capture will add when available: description bytes at visitor entry (RDX = desc pointer per tools/livecap/targets.lua arg=RDX) for tags 3 and 4, confirming field sizes/runtime values vs Descriptions.h, plus `ret=` naming the visitor's caller chain (expect sub_6640ae0 wrapper, confirmed by `rdis xr 0x6640d80`). Limitation: function-entry sampling cannot install a read watchpoint on pass+0x800/+0x648/+0x4A0/+0x1D0, so the capture cannot locate the consumers — the blocking fact below stands regardless of capture outcome.

## CLOSES?

CLOSES? NO — the consumers (draining element readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 are not located anywhere in Minecraft.Windows.exe 1.26.62.01: all four vectors are write-only statically (only the Light-visitor writers are [V]); whole-image read/write scans, endFrame re-read, 0x5ABA5C0 caller enumeration and `rdis ptr` found no element reader and no end-cursor pop (same E2 consumer blocker as the R2/R5 groups); the live-capture tool samples function entry and cannot install a read watchpoint, so it cannot find consumers either. Single blocking fact: no draining reader of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 exists in the exe, and no available tool can establish the read watchpoint that would find one. (Resolved [V]: tag 2 = GameplayMetadata, tag 3 = LightPoint; FrameBuilder.h wins the tag-name conflict. Open [?]: description value names — no RTTI/member-name source in the exe.)

## TOOL REQUESTS

CAPTURE REQUESTED oc_u_er6_light_desc — light-visitor entry capture (0x6640d80), state=pending in docs/progress/capture_requests.json; awaiting docs/data/live/oc_u_er6_light_desc.txt from the orchestrator. Helper scripts: None.
