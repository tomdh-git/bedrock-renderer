## NEXT
DONE

# U-ER6 — R6: LightAmbient / LightDirectional / Light tag 2 / tag 3 / tag 4 (1.26.62.01)

Goal: close R6 — tag value names, the group_visitors.md vs FrameBuilder.h LightGroupTag tag-name conflict, and the consumers (draining element readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0. Static analysis only; RVAs image-relative. Every quoted `0xRVA  instr` line is copied verbatim from a listing and passes tools/sigs/verify_oc.py. Tags: [V] seen in disassembly (RVA cited) | [I] inferred | [?] unknown.

Input data already read (not re-generated): docs/functions/6640d80_light_visitor.md; docs/functions/5aba5c0.md; docs/functions/group_visitors.md; docs/functions/light_game_descriptions.md; docs/data/live/light_visitor.txt; docs/BGFX_MAP.md; src/sdk/mc/deps/minecraft_renderer/framebuilder/FrameBuilder.h (LightGroupTag enum); Descriptions.h / LightDescriptions.h / LightGameDescriptions.h; docs/progress/pre/0x6640AE0.md (full light visitor listing, rdis verified).

The pass object is the per-thread value of ThreadLocalObject 0x5ABA5C0 (value at node+0x10). Visitor cases call 0x5ABA5C0 with rcx = frameCtx+0x10+0x9D0 and get rsi = pass [V]. All four vectors live inside this pass object: begin/end/cap cursors at (+0x7F8/+0x800/+0x808) summary stride 0x14, (+0x648/+0x650) light-record stride 0x48, (+0x498/+0x4A0/+0x4A8) GameplayMetadata stride 0x84, (+0x1C8/+0x1D0/+0x1D8) ShadowAtlasFrame stride 0x50 [V, from the light-visitor listings].

## 1. Tag -> type / value names (LightGroupTag) and the tag-name conflict — resolved [V]

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| variant+0x08 tag | 1 | `0x6640dc4  movzx eax,byte ptr [rdx+8]`<br>`0x6640de6  jmp rax` | tag byte at variant+0x08; dispatch `jmp rax` via jump table 0xF2BF2B0 (entries: 0=Ambient, 1=Directional, 2=GameplayMetadata, 3=LightPoint, 4=ShadowAtlasFrame, 6=VoxelVolume, 7=TransitioningVoxelVolume) [V] | [V] |
| tag 2 store | 1 | `0x53e5fb4  mov byte ptr [rbp-0x18],2` | LightGroupTag::GameplayMetadata = 2; clone 0x53e5910, srcloc 0xF248ED0 `__FUNCSIG__ ... gamecomponents::GameplayMetadata`; JT entry 2 [V] | [V] |
| tag 3 store | 1 | `0x535a9b7  mov byte ptr [rbp+0x278],3` | LightGroupTag::LightPoint = 3; light clone 0x53599d0, srcloc 0xF248DA0 `LightPointDescription`; JT entry 3 [V] | [V] |
| tag-map conflict | - | FrameBuilder.h:79-88 `enum class LightGroupTag : uint64_t { Ambient = 0, Directional = 1, GameplayMetadata = 2, LightPoint = 3, ShadowAtlasFrame = 4, ServerGraphicsOverrideParameters = 5, VoxelVolume = 6, TransitioningVoxelVolume = 7 };` | CONFLICT RESOLVED [V]: producer tag stores + __FUNCSIG__ zone records prove tag 2 = GameplayMetadata and tag 3 = LightPoint; FrameBuilder.h wins (group_visitors.md had them swapped: LightPoint@2 / GameplayMetadata@3). Tags 5/6/7 = ServerGraphicsOverrideParameters / VoxelVolume / TransitioningVoxelVolume [V] | [V] |

## 2. Light-visitor writers to pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — proven [V]

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| pass+0x800 | 8 | `0x6640e84  mov rdx,[rsi+0x800]`<br>`0x6640e8b  cmp rdx,[rsi+0x808]`<br>`0x6640eb4  add qword ptr [rsi+0x800],0x14`<br>`0x66417a2  add qword ptr [rsi+0x800],0x14`<br>`0x6641517  add qword ptr [rsi+0x800],0x14` | end cursor of the 0x14-byte summary list (cap +0x808); writers: Ambient 0x6640eb4, Directional 0x66417a2, Point 0x6641517 [V] | [V] |
| pass+0x648 | 8 | `0x66416f8  lea rcx,[rsi+0x648]`<br>`0x66416ff  call 0x675FB30`<br>`0x664145a  lea rcx,[rsi+0x648]`<br>`0x6641461  call 0x675FB30` | end cursor of the 0x48-byte light-record vector (begin +0x648 / end +0x650); writers: Directional 0x66416ff, Point 0x6641461 via 0x675FB30 [V] | [V] |
| pass+0x4A0 | 8 | `0x6640f78  mov r12,[rdi+0x4A0]`<br>`0x6641090  add qword ptr [rdi+0x4A0],0x84` | end cursor of the 0x84-byte GameplayMetadata vector (begin +0x498 / cap +0x4A8); writer tag 2, stride 0x84 [V] | [V] |
| pass+0x1D0 | 8 | `0x66419c6  add qword ptr [rsi+0x1D0],0x50` | end cursor of the 0x50-byte ShadowAtlasFrame vector (begin +0x1C8 / cap +0x1D8); writer tag 4, stride 0x50 [V] | [V] |

Every write above is an end-cursor increment; no end-cursor pop/decrement exists anywhere in the exe [V, whole-image fld --w scans, earlier units].

## 3. Consumers of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — NOT located

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| pass+0x800 element read | - | - | no draining reader of the 0x14-byte summary elements anywhere in Minecraft.Windows.exe 1.26.62.01; only the three end-cursor writers above [V] | [?] |
| pass+0x648 element read | - | - | no draining reader of the 0x48-byte light-record elements anywhere in the exe [V writes only] | [?] |
| pass+0x4A0 element read | - | - | no draining reader of the 0x84-byte GameplayMetadata elements anywhere in the exe [V writes only] | [?] |
| pass+0x1D0 element read | - | - | no draining reader of the 0x50-byte ShadowAtlasFrame elements anywhere in the exe [V writes only] | [?] |

Static angles exhausted for consumers: whole-image `rdis fld --r/--w` scans for all four offsets and begin cursors; endFrame 0x66232b0 full listing (touches none of the four offsets); all ~200 `0x5ABA5C0` callers enumerated; `rdis ptr 0x5aba5c0`: 0 indirect slots; `rdis callers 0x6640ae0`: 0 calling functions (indirect wrapper); `rdis vt 0x6640ae0`: not a vtable; descscan2 on light cases 2/3/4 confirms description reads only, no pass-vector element reads [V]. A consumer that loads a cursor once and indexes `[cursor_reg + index*stride]` is invisible to offset scans; none of the enumerated cursor-reader functions does that [V]. Static analysis exhausted — locating consumers needs a live read/write watchpoint, which no available tool provides.

## 4. Description field value names — unknown [?]

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| LightPoint desc +0x000 | 4 | `0x664127e  movss xmm5,[rsi]` | mValue00 read (descscan2 case 3, tag 3 = LightPoint) [V] | [V] |
| LightPoint desc +0x048 | 16 | `0x6641117  movups xmm5,[rsi+0x48]` | slice 0 vec4 read (descscan2 case 3) [V] | [V] |
| LightPoint desc +0x100 | 4 | `0x66410c9  movss xmm5,[rsi+0x100]` | mValue100 read (descscan2 case 3) [V] | [V] |
| ShadowAtlasFrame desc +0x000 | 16 | `0x6640ec1  movups xmm6,[rsi]` | mMatrix row 0 read (descscan2 case 4, tag 4 = ShadowAtlasFrame) [V] | [V] |
| ShadowAtlasFrame desc +0x048 | 8 | `0x6640f01  mov rcx,[rsi+0x48]` | mControlBlock shared_ptr read (descscan2 case 4) [V] | [V] |
| description value names | - | - | LightAmbientDescription (0x18), LightDirectionalDescription (0x24), LightPointDescription (0x108), GameplayMetadataDescription (0x84), ShadowAtlasFrameDescription (0x50) field reads are proven [V] in the visitor cases (descscan2 confirms cases 2/3/4), but the release exe has no RTTI and no description member-name strings; the headers type the fields as mValue*/mData placeholders with static_assert offsets only. Semantic value names: unknown [?] | [?] |

descscan2 results (new this unit): case 2 (GameplayMetadata) reads bytes 0x0-0x3a and 0x3c-0x84, gap 0x3a-0x3c [V]; case 3 (LightPoint) reads bytes 0x0-0x4, 0x8-0x21, 0x28-0x32, 0x38-0x104, gaps 0x4-0x8/0x21-0x28/0x32-0x38 [V]; case 4 (ShadowAtlasFrame) reads bytes 0x0-0x40, 0x48-0x50, gap 0x40-0x48 [V]. All reads confirmed verbatim from docs/progress/pre/0x6640AE0.md.

## 5. Live capture

Request `oc_u_er6_light_desc` (rva 0x6640d80 = light-visitor entry; size 0x100, max 6) is QUEUED in docs/progress/capture_requests.json (state=pending). `python tools/livecap/request.py result oc_u_er6_light_desc` -> "no result yet (orchestrator has not run it)"; no docs/data/live/oc_u_er6_light_desc.txt exists.

The capture can confirm description field sizes/runtime values for tags 3 and 4, and `ret=` can name the visitor caller chain (expect _insert(Light) wrapper 0x6640ae0). Limitation: function-entry sampling cannot install a read watchpoint on pass+0x800/+0x648/+0x4A0/+0x1D0, so the capture cannot locate consumers — the blocking fact stands regardless of capture outcome.

## CLOSES?

CLOSES? NO — the consumers (draining element readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 are not located anywhere in Minecraft.Windows.exe 1.26.62.01: all four vectors are write-only statically (only the Light-visitor writers are [V]); whole-image read/write scans, endFrame re-read, 0x5ABA5C0 caller enumeration, rdis callers/vt on the wrapper, and descscan2 on cases 2/3/4 found no element reader and no end-cursor pop; descscan2 confirms description field reads but no pass-vector element reads; the live-capture tool samples function entry and cannot install a read watchpoint, so it cannot find consumers either. Single blocking fact: no draining reader of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 exists in the exe, and no available tool can establish the read watchpoint that would find one. (Resolved [V]: tag 2 = GameplayMetadata, tag 3 = LightPoint; FrameBuilder.h wins the tag-name conflict. Writers [V]: pass+0x800/+0x648/+0x4A0/+0x1D0 end-cursor increments. Open [?]: description value names — no RTTI/member-name source in the exe.)

## TOOL REQUESTS

CAPTURE REQUESTED oc_u_er6_light_desc — light-visitor entry capture (0x6640d80) queued in docs/progress/capture_requests.json, state=pending; awaiting docs/data/live/oc_u_er6_light_desc.txt from the orchestrator. Helper scripts: None.
