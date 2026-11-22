## NEXT
DONE

# U-ER6 — R6: LightAmbient / LightDirectional / Light tag 2 / tag 3 / tag 4 (1.26.62.01)

Goal: close R6 — description value names, the group_visitors.md vs FrameBuilder.h LightGroupTag tag-name conflict, and the consumers (draining element readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0. Static analysis only; exe never launched; RVAs image-relative; every `0xRVA  instr` line copied verbatim from verified listings and passing tools/sigs/verify_oc.py. Tags: [V] seen in disassembly (RVA cited) | [I] inferred | [?] unknown.

Input data (read fully, not re-generated): docs/functions/6640d80_light_visitor.md; docs/functions/5aba5c0.md; docs/functions/group_visitors.md; docs/functions/light_game_descriptions.md; docs/data/live/light_visitor.txt; docs/data/live/README.md; docs/data/live/_status.txt; docs/progress/capture_requests.json; docs/BGFX_MAP.md sections 3/6g/6w/6ih (lines 181, 277, 279, 1855-1859, 2037, 2051); src/sdk/mc/deps/minecraft_renderer/framebuilder/FrameBuilder.h (LightGroupTag enum, line 79, read directly); LightDescriptions.h / LightGameDescriptions.h (mValue* placeholder fields, static_assert offsets, read directly).

The pass object is the per-thread value of ThreadLocalObject 0x5ABA5C0 (value at node+0x10). Visitor cases call 0x5ABA5C0 with rcx = frameCtx+0x10+0x9D0 and get rsi = pass [V]. All four vectors live inside this pass object: begin/end/cap cursors at (+0x7F8/+0x800/+0x808) summary stride 0x14, (+0x648/+0x650) light-record stride 0x48, (+0x498/+0x4A0/+0x4A8) GameplayMetadata stride 0x84, (+0x1C8/+0x1D0/+0x1D8) ShadowAtlasFrame stride 0x50 [V, from the light-visitor listings and BGFX_MAP.md 6ih].

## 1. Tag -> type / LightGroupTag mapping and tag-name conflict — resolved [V]

| offset | size | site | instr | meaning | tag |
|---|---|---|---|---|---|
| variant+0x08 tag | 1 | 0x6640dc4, 0x6640de6 | `0x6640dc4  movzx eax,byte ptr [rdx+8]`<br>`0x6640de6  jmp rax` | tag byte at variant+0x08; indirect dispatch `jmp rax` via jump table 0xF2BF2B0 (entries: 0=0x6640de8 Ambient, 1=0x66415b0 Directional, 2=0x6640f1b GameplayMetadata, 3=0x66410a0 LightPoint, 4=0x6640ec1 ShadowAtlasFrame, 5=0x66417af ServerGraphicsOverrideParameters, 6=0x664187d VoxelVolume, 7=0x6641524 TransitioningVoxelVolume) [V] | [V] |
| producer tag stores | 1 | 0x53e3511, 0x53709d4, 0x53e5fb4, 0x53e5fbf, 0x535a9b7, 0x535a9c1, 0x53e5fbf, 0x535a696, 0x535a6a0 | `0x53e3511  mov byte ptr [rbp+0x138],0`<br>`0x53709d4  mov byte ptr [rbp+0x18],1`<br>`0x53e5fb4  mov byte ptr [rbp-0x18],2`<br>`0x53e5fbf  mov rax,[rax+0x380]`<br>`0x535a9b7  mov byte ptr [rbp+0x278],3`<br>`0x535a9c1  mov rax,[rax+0x380]`<br>`0x535a696  mov byte ptr [rbp+0x278],4`<br>`0x535a6a0  mov rax,[rax+0x380]` | producer clones store tag 0..4 at their variant slot before the Light vslot-0x380 insert: tag 0 Ambient (clone 0x53e2c00, srcloc RenderLightAmbientDescription), tag 1 Directional (clone 0x5370960), tag 2 GameplayMetadata (clone 0x53e5910, insert 0x53e5fbf, srcloc __FUNCSIG__ GameplayMetadata), tag 3 LightPoint (clone 0x53599d0, insert 0x535a9ce, srcloc LightPointDescription), tag 4 ShadowAtlasFrame (clone 0x53599d0, insert 0x535a6a0, srcloc ShadowAtlasFrameDescription) [V] | [V] |
| tag-map conflict | - | FrameBuilder.h:79-88 | - | CONFLICT RESOLVED [V]: FrameBuilder.h:79-88 `enum class LightGroupTag : uint64_t { Ambient = 0, Directional = 1, GameplayMetadata = 2, LightPoint = 3, ShadowAtlasFrame = 4, ServerGraphicsOverrideParameters = 5, VoxelVolume = 6, TransitioningVoxelVolume = 7 };`; producer tag stores + __FUNCSIG__ zone records prove tag 2 = GameplayMetadata and tag 3 = LightPoint, so FrameBuilder.h wins and group_visitors.md (which had them swapped: LightPoint@2 / GameplayMetadata@3) is superseded. Tags 5/6/7 = ServerGraphicsOverrideParameters / VoxelVolume / TransitioningVoxelVolume [V]; corroborated by BGFX_MAP.md lines 2037, 2051 [V doc]. | [V] |

## 2. Light-visitor end-cursor writers to pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — proven [V]

| offset | size | site | instr | meaning | tag |
|---|---|---|---|---|---|
| pass+0x800 end cursor | 8 | 0x6640e84, 0x6640e8b, 0x6640eb4, 0x6641761, 0x66417a2, 0x6641517 | `0x6640e84  mov rdx,[rsi+0x800]`<br>`0x6640e8b  cmp rdx,[rsi+0x808]`<br>`0x6640eb4  add qword ptr [rsi+0x800],0x14`<br>`0x6641761  mov rdx,[rsi+0x800]`<br>`0x66417a2  add qword ptr [rsi+0x800],0x14`<br>`0x6641517  add qword ptr [rsi+0x800],0x14` | end cursor of the 0x14-byte summary list (cap cursor +0x808); writers: Ambient 0x6640eb4, Directional 0x66417a2, Point 0x6641517 (all increment by 0x14); cap compared at 0x6640e8b [V] | [V] |
| pass+0x808 cap cursor | 8 | 0x6640e8b | `0x6640e8b  cmp rdx,[rsi+0x808]` | summary-list cap cursor compared against end +0x800 [V] | [V] |
| pass+0x648 end cursor | 8 | 0x66416f8, 0x66416ff, 0x664145a, 0x6641461 | `0x66416f8  lea rcx,[rsi+0x648]`<br>`0x66416ff  call 0x675FB30`<br>`0x664145a  lea rcx,[rsi+0x648]`<br>`0x6641461  call 0x675FB30` | end cursor of the 0x48-byte light-record vector (begin +0x648 / end +0x650); Directional 0x66416ff and Point 0x6641461 pass &end to grow-emplace 0x675FB30 [V] | [V] |
| pass+0x650 end cursor | 4 | 0x6641729, 0x6641735, 0x6641738 | `0x6641729  mov eax,[rsi+0x650]`<br>`0x6641735  shr eax,3`<br>`0x6641738  imul eax,0xFFFF8E39` | light-record end cursor; element index derived as (end-begin)/0x48 - 1 (shr 3 then magic multiply) [V] | [V] |
| pass+0x4A0 end cursor | 8 | 0x6640f78, 0x6641090 | `0x6640f78  mov r12,[rdi+0x4A0]`<br>`0x6641090  add qword ptr [rdi+0x4A0],0x84` | end cursor of the 0x84-byte GameplayMetadata vector (begin +0x498 / cap +0x4A8); tag-2 write, stride 0x84 [V] | [V] |
| pass+0x4A8 cap cursor | 8 | 0x6640f7f | `0x6640f7f  cmp r12,[rdi+0x4A8]` | GameplayMetadata vector cap cursor compared against end +0x4A0 [V] | [V] |
| pass+0x1D0 end cursor | 8 | 0x66419c6 | `0x66419c6  add qword ptr [rsi+0x1D0],0x50` | end cursor of the 0x50-byte ShadowAtlasFrame vector (begin +0x1C8 / cap +0x1D8); tag-4 write, stride 0x50 [V] | [V] |

Every write above is an end-cursor increment; no end-cursor pop/decrement exists anywhere in the exe [V, whole-image fld --w scans]; no `[pass_cursor + index*stride]` element read exists for any of the four offsets [V negative].

## 3. Consumers (draining element readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — not located [?]

| offset | size | site | instr | meaning | tag |
|---|---|---|---|---|---|
| pass+0x800 element read | - | - | - | no draining reader of the 0x14-byte summary elements anywhere in Minecraft.Windows.exe 1.26.62.01; only the three end-cursor writers in section 2 [V] | [?] |
| pass+0x648 element read | - | - | - | no draining reader of the 0x48-byte light-record elements anywhere in the exe [V writes only] | [?] |
| pass+0x4A0 element read | - | - | - | no draining reader of the 0x84-byte GameplayMetadata elements anywhere in the exe [V writes only] | [?] |
| pass+0x1D0 element read | - | - | - | no draining reader of the 0x50-byte ShadowAtlasFrame elements anywhere in the exe [V writes only] | [?] |

New angles tried this unit (in addition to oc_U-ER6_r1-r14, not re-run):

- Live capture `oc_u_er6_light_desc` (rva 0x6640D80, size 0x100, max 6): state=pending, result not yet available via `python tools/livecap/request.py result oc_u_er6_light_desc` → "no result yet (orchestrator has not run it)" [shell]. Queue full (4 pending: er5_clone_4c8a5b0, l8b_resizetex_slot31, sub_1289440_callers, oc_u_er6_light_desc), so no new `add` allowed. Function-entry sampling dumps RDX = desc bytes + ret = caller chain only; it cannot install a read/watchpoint on pass+0x800/+0x648/+0x4A0/+0x1D0, so even when run it cannot locate the consumers [stated tool limitation].
- livemem: no target — 0x5ABA5C0 is a function entry (ThreadLocalObject::get), `rdis imm 0x5aba5c0` = 0 static data references to a pass-object global, and the pass is computed per call (rcx = frameCtx+0x10+0x9D0); livemem cannot scan or loop over ranges, so there is no address to point it at [V static]. No livemem read issued this unit.
- Static angles carried from oc_U-ER6_r1-r14 (not re-run per RETRY #1, all [V]): whole-image `rdis fld --r/--w` scans for 0x800/0x648/0x4A0/0x1D0 and begin cursors 0x7F8/0x650/0x498/0x1C8 (every hit is a stack local, a writer cursor access, or the same offset on an unrelated object; writes are only end-cursor increments, no `sub` end-cursor decrement); endFrame listing sub_66232b0 (touches none of the four offsets although it calls 0x5ABA5C0 3×); all ~200 `0x5ABA5C0` callers via `rdis xr` (none drain); `rdis ptr 0x5aba5c0` (0 indirect slots) and `rdis imm 0x5aba5c0` (0 static data refs); grow path 0x675FB30 and shared case epilogue 0x66447a0..0x66447d1 (cursor arithmetic only, never element reads). Side finding only: per-draw code 0x66ea3d0 appends u16 indices to the unrelated pass vector at +0x8A8 and reads none of the four cursors [V].

## 4. Description field reads — offsets/sizes [V], member names [?]

| offset | size | site | instr | meaning | tag |
|---|---|---|---|---|---|
| desc+0x00 | 16 | 0x6640ec1 | `0x6640ec1  movups xmm6,[rsi]` | tag-4 ShadowAtlasFrame description row +0x00 copied verbatim into the pass element (four 16-byte rows +0x00..+0x30) [V] | [V] |
| desc+0x10 | 16 | 0x6640ecb | `0x6640ecb  movups xmm7,[rsi+0x10]` | description row +0x10 [V] | [V] |
| desc+0x20 | 16 | 0x6640ed6 | `0x6640ed6  movups xmm8,[rsi+0x20]` | description row +0x20 [V] | [V] |
| desc+0x30 | 16 | 0x6640ee3 | `0x6640ee3  movups xmm9,[rsi+0x30]` | description row +0x30 [V] | [V] |
| desc+0x40 | 8 | 0x66418f0 | `0x66418f0  mov rbx,[rsi+0x40]` | description qword +0x40 [V] | [V] |
| desc+0x48 | 8 | 0x6640f01 | `0x6640f01  mov rcx,[rsi+0x48]` | description qword +0x48 (shared handle / control block) [V] | [V] |

Same descscan2-proven read pattern (offsets/sizes) for LightAmbient (0x18), LightDirectional (0x24), GameplayMetadata (0x84), LightPoint (0x108) carried from oc_U-ER6_r1-r5 [V]. Header static_asserts read directly from LightDescriptions.h / LightGameDescriptions.h confirm sizeof: LightAmbientProducer 0x18, LightDirectionalProducer 0x24, LightPointProducer 0x108, GameplayMetadataProducer 0x84, ShadowAtlasFrameDescriptionReads 0x50 [V header]; these match the visitor-case read extents [V]. Member names: the headers type every field as mValue* placeholders (e.g. mValue08/mValue0C/… with static_assert offsets only) — read directly above — so they carry no value names; the release exe has no RTTI and no description member-name strings. Names unknown [?].

## 5. Live capture — pending, adds desc bytes only

| offset | size | site | instr | meaning | tag |
|---|---|---|---|---|---|
| oc_u_er6_light_desc capture | - | docs/progress/capture_requests.json + `python tools/livecap/request.py result oc_u_er6_light_desc` | - | queued state=pending (rva 0x6640D80, size 0x100, max 6); result not yet available; docs/data/live/_status.txt DONE t=120 does not list it. When run it will dump RDX desc bytes at visitor entry for whatever tags land in the 6 samples (docs/data/live/light_visitor.txt [V live] holds tags 0/1/2/5 bytes only — no tag 3/4 description bytes exist in any capture) plus `ret=` naming the visitor caller chain (static single caller: sub_6640ae0 via 0x6640c44 [V]). Bytes confirm field sizes/runtime values, never member names; entry sampling cannot install a read watchpoint, so it cannot find the consumers. | [V live when available] |

## 6. Description value names — unknown [?]

| offset | size | site | instr | meaning | tag |
|---|---|---|---|---|---|
| description member names | - | - | - | LightDescriptions.h / LightGameDescriptions.h type all fields as mValue* placeholders with static_assert offsets only (read directly); the release exe has no RTTI and no description member-name strings; light_visitor.txt [V live] carries bytes for tags 0/1/2/5 but never names and no tag 3/4 bytes exist in any capture. Producer-side semantics are inference [I], not names. Value names: unknown [?] | [?] |

## CLOSES?

CLOSES? NO — the single blocking fact: no draining reader (element consumer) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 exists anywhere in Minecraft.Windows.exe 1.26.62.01; all four vectors are write-only statically (end-cursor increments only, no pop/decrement, no element-indexed read) [V]; whole-image fld scans, the endFrame listing, all ~200 `0x5ABA5C0` callers, and `rdis ptr`/`imm`/`xr` indirect checks are negative [V] (carried r1-r14); the queued live capture oc_u_er6_light_desc samples function entry (RDX=desc bytes, ret=caller chain) and cannot install a read watchpoint on the pass vectors; livemem has no pass-object target address (0x5ABA5C0 is a function, no static data ref, no scan/loop) [V static]. Description value names also remain unknown [?]: no RTTI or member-name strings in the release exe; headers use mValue* placeholders. Resolved [V], not re-proven here: tag 2 = GameplayMetadata, tag 3 = LightPoint (FrameBuilder.h wins the group_visitors.md conflict); the four end-cursor writers to pass+0x800/+0x648/+0x4A0/+0x1D0 [V].

## TOOL REQUESTS

CAPTURE REQUESTED oc_u_er6_light_desc — already queued in docs/progress/capture_requests.json (state=pending, rva 0x6640D80 = light-visitor entry 0x6640D80, size 0x100, max 6, why "R6: dump RDX desc bytes at visitor entry for tags 3/4 field sizes vs Descriptions.h layouts; ret= names the visitor caller chain (sub_6640ae0 via 0x6640c44)"); `python tools/livecap/request.py result oc_u_er6_light_desc` → "no result yet"; queue full at 4 pending so no new `add` this unit. It can add runtime desc bytes (which tags land in 6 samples is not controllable; no tag 3/4 bytes exist in any capture yet) plus ret= caller chain — bytes only, never member names, no read/write watchpoint, so it cannot close the consumer blocker. A read/watchpoint capability on pass+0x800/+0x648/+0x4A0/+0x1D0 (or a live pass-object address for livemem) is what would be needed to close consumers. Helper scripts: None.
