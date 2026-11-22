## NEXT
DONE

# U-ER6 — R6: LightAmbient / LightDirectional / Light tag 2 / tag 3 / tag 4 (1.26.62.01)

Goal: close R6 — description field value names, the group_visitors.md vs FrameBuilder.h LightGroupTag tag-name conflict, consumers (draining element readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0. Exe Minecraft.Windows.exe 1.26.62.01, RVAs image-relative. Static analysis only (game closed); live capture is orchestrator-provided and read-only. Tags: [V] seen in disassembly (RVA cited) | [V carried] proven in earlier docs/progress/oc_U-ER6_r*.md notes and not re-proven per RETRY #1 | [V negative] whole-image scan found nothing | [V live] live capture bytes (docs/data/live/*.txt) | [I] inferred | [?] unknown. Every `0xRVA  instr` line is copied verbatim from a verified listing/disassembly.

Input data (read fully, not re-generated): docs/functions/6640d80_light_visitor.md; docs/functions/5aba5c0.md; docs/functions/group_visitors.md (superseded on tags 2/3); docs/functions/light_game_descriptions.md; docs/data/live/light_visitor.txt; docs/data/live/README.md; docs/data/live/_status.txt; docs/BGFX_MAP.md sections 6gq/6ih/6hi/6w; src/sdk/mc/deps/minecraft_renderer/framebuilder/FrameBuilder.h (LightGroupTag enum); Descriptions.h/LightDescriptions.h/LightGameDescriptions.h.

## 1. Carried [V] — tag -> type / LightGroupTag, conflict RESOLVED (not re-proven)

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| variant+0x08 tag byte | 1 | `0x6640dc4  movzx eax,byte ptr [rdx+8]`<br>`0x6640de6  jmp rax` | tag byte at variant+0x08; dispatch `jmp rax` via jump table 0xF2BF2B0 (entries: 0=0x6640de8, 1=0x66415b0, 2=0x6640f1b, 3=0x66410a0, 4=0x6640ec1, 5=0x66417af, 6=0x664187d, 7=0x6641524) | [V carried] |
| tag 0 = Ambient | 1 | `0x53e3511  mov byte ptr [rbp+0x138],0` | LightGroupTag::Ambient = 0; JT entry 0; srcloc 0xF248E70 RenderLightAmbientDescription | [V carried] |
| tag 1 = Directional | 1 | `0x53709d4  mov byte ptr [rbp+0x18],1` | LightGroupTag::Directional = 1; JT entry 1; srcloc 0xF248F70 LightDirectionalDescription | [V carried] |
| tag 2 = GameplayMetadata | 1 | `0x53e5fb4  mov byte ptr [rbp-0x18],2`<br>`0x53e5fbf  mov rax,[rax+0x380]` | LightGroupTag::GameplayMetadata = 2; JT entry 2; srcloc 0xF248ED0 GameplayMetadata | [V carried] |
| tag 3 = LightPoint | 1 | `0x535a9b7  mov byte ptr [rbp+0x278],3`<br>`0x535a9c1  mov rax,[rax+0x380]` | LightGroupTag::LightPoint = 3; JT entry 3; srcloc 0xF248DA0 LightPointDescription | [V carried] |
| tag 4 = ShadowAtlasFrame | 1 | `0x535a696  mov byte ptr [rbp+0x278],4`<br>`0x535a6a0  mov rax,[rax+0x380]` | LightGroupTag::ShadowAtlasFrame = 4; JT entry 4; srcloc 0xF248D80 ShadowAtlasFrameDescription | [V carried] |
| tag-name conflict | - | FrameBuilder.h:79-88 `enum class LightGroupTag : uint64_t { Ambient = 0, Directional = 1, GameplayMetadata = 2, LightPoint = 3, ShadowAtlasFrame = 4, ServerGraphicsOverrideParameters = 5, VoxelVolume = 6, TransitioningVoxelVolume = 7 };` | CONFLICT RESOLVED [V carried]: producer tag stores + __FUNCSIG__ srclocs prove tag 2 = GameplayMetadata and tag 3 = LightPoint; FrameBuilder.h wins; group_visitors.md had them swapped (LightPoint@2 / GameplayMetadata@3) and is superseded; BGFX_MAP.md 6w agrees | [V carried] |

## 2. Carried [V] — Light-visitor writers to pass+0x800 / +0x648 / +0x4A0 / +0x1D0 (write-only)

Pass-object vectors (begin/end/cap cursors): summary +0x7F8/+0x800/+0x808 stride 0x14; light records +0x648/+0x650 stride 0x48; GameplayMetadata +0x498/+0x4A0/+0x4A8 stride 0x84; ShadowAtlasFrame +0x1C8/+0x1D0/+0x1D8 stride 0x50 [V carried]. Every write below is an end-cursor increment / grow-emplace; no end-cursor pop/decrement exists anywhere in the exe [V negative, whole-image fld --w].

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| pass+0x800 end cursor | 8 | `0x6640e84  mov rdx,[rsi+0x800]`<br>`0x6640e8b  cmp rdx,[rsi+0x808]`<br>`0x6640eb4  add qword ptr [rsi+0x800],0x14`<br>`0x6641761  mov rdx,[rsi+0x800]`<br>`0x66417a2  add qword ptr [rsi+0x800],0x14`<br>`0x6641517  add qword ptr [rsi+0x800],0x14` | end cursor of 0x14-byte summary list (cap +0x808); writers Ambient 0x6640eb4, Directional 0x66417a2, LightPoint 0x6641517 | [V carried] |
| pass+0x648 end cursor | 8 | `0x66416f8  lea rcx,[rsi+0x648]`<br>`0x66416ff  call 0x675FB30`<br>`0x664145a  lea rcx,[rsi+0x648]`<br>`0x6641461  call 0x675FB30` | end cursor of 0x48-byte light-record vector (begin +0x648 / end +0x650); Directional 0x66416ff and LightPoint 0x6641461 pass &end to grow-emplace 0x675FB30 | [V carried] |
| pass+0x4A0 end cursor | 8 | `0x6640f78  mov r12,[rdi+0x4A0]`<br>`0x6640f7f  cmp r12,[rdi+0x4A8]`<br>`0x6641090  add qword ptr [rdi+0x4A0],0x84` | end cursor of 0x84-byte GameplayMetadata vector (begin +0x498 / cap +0x4A8); tag-2 writer, stride 0x84 | [V carried] |
| pass+0x1D0 end cursor | 8 | `0x66419c6  add qword ptr [rsi+0x1D0],0x50` | end cursor of 0x50-byte ShadowAtlasFrame vector (begin +0x1C8 / cap +0x1D8); tag-4 writer, stride 0x50 | [V carried] |

## 3. Carried [V live] — description bytes confirm field SIZES only, never names (docs/data/live/light_visitor.txt)

- tag 2 GameplayMetadata desc at 0x14A5A0 (lines 6-7): +0x00..+0x14 six f32 (8.5, 1.0, 2.0, 15.0, 1.0, 0.5), +0x18 u32 per-object, +0x1C u32 = 4, +0x20 u32 = 18000 [V live].
- tag 0 Ambient desc at 0x14A5B8 (line 3): +0x00..+0x0F all zero [V live].
- tag 1 Directional desc at 0x14A400 (lines 5, 8): +0x00..+0x10 1.0 f32s [V live].
- Tags 3 (LightPoint, 0x108 B) and 4 (ShadowAtlasFrame, 0x50 B) do not appear in any sample; capture oc_u_er6_light_desc is pending to supply their bytes + ret= caller chain [V live when it runs].

## 4. Pending: consumers (draining element readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — NOT LOCATED

| offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|
| pass+0x800 elements | 0x14 | - | - | no draining element read of the 0x14-byte summary vector anywhere in Minecraft.Windows.exe 1.26.62.01; end-cursor increment writes only; whole-image fld --r scans negative | [V negative] |
| pass+0x648 elements | 0x48 | - | - | no draining element read of the 0x48-byte light-record vector anywhere in the exe; writes are grow-emplace calls to 0x675FB30 plus index-word stores only | [V negative] |
| pass+0x4A0 elements | 0x84 | - | - | no draining element read of the 0x84-byte GameplayMetadata vector anywhere in the exe; writes are end-cursor increments only | [V negative] |
| pass+0x1D0 elements | 0x50 | - | - | no draining element read of the 0x50-byte ShadowAtlasFrame vector anywhere in the exe; writes are end-cursor increments only | [V negative] |

Static angles already exhausted [V negative] (r2/r53/r54, not re-run): whole-image fld --r/--w on 0x800/0x648/0x4A0/0x1D0 and begin/cap cursors (all hits stack/unrelated locals or cursor/index math); endFrame 0x66232b0 re-list (no access to the four offsets); all 0x5ABA5C0 callers (none drain); rdis ptr/imm/xr to 0x5aba5c0 = 0 refs/slots (pass object has no static address, ThreadLocalObject node via 0x5ABA5C0, value at node+0x10); visitor 0x6640ae0 has 0 static callers/xrefs; imm 0x14/0x48/0x84/0x50 and magic-multiplier scans (÷0x14 ÷0x48 ÷0x84 ÷0x50) — writer hits only, no scaled-index element reader; descscan2 tag-2 case 0x6640f1b reads desc+0x00..+0x84 only; per-draw 0x66ea3d0 appends u16 indices to pass+0x8A8 and reads none of the four cursors; ClusterLights body 0xbc5bad0 reads other structures; BGFX_MAP.md 6gq/6ih/6hi/6w name no consumer. Any consumer must index `[pass + index*stride]` (computed address, no immediate), which offset scans cannot see.

NEW ANGLE THIS UNIT (flow/rw/struct, not yet tried): rdis walk from the cursor base-establishing instructions, tracking the base register, looking for `[base + index*stride]` element reads:
- 0x66416f8 `lea rcx,[rsi+0x648]` (pass+0x648 base in rcx), walk --reg rcx
- 0x6640f78 `mov r12,[rdi+0x4A0]` / `0x6641090 add qword ptr [rdi+0x4A0],0x84` (pass+0x4A0 base rdi), walk region of tag-2 case 0x6640f1b..0x66410c0
Results appended below after each rdis run.

## 5. Pending: description field value names — UNKNOWN [?]

Release exe has no RTTI and no description member-name strings; LightDescriptions.h/LightGameDescriptions.h type fields as mValue* placeholders with static_assert offsets only; descscan2 case 2 (GameplayMetadata) reads desc+0x00..+0x84 only [V]; live desc bytes confirm sizes only, never names [V live]; parked in MIRROR_SKIP per prior review (r2 REVIEW 24/24 [V]).

## Blocking fact

All four vectors are write-only in Minecraft.Windows.exe 1.26.62.01: only end-cursor increment / grow-emplace writes exist [V]; no element read of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 was found by whole-image read scans [V negative]; no 0x5ABA5C0 caller drains them [V]. New angle this unit: `rdis walk 0x66416f8 --reg rcx` (3020 instructions reachable from the Directional-case `lea rcx,[rsi+0x648]`) shows only the grow-emplace call 0x675FB30 and end/cursor index math (`mov eax,[rsi+0x650]; sub eax,[rsi+0x648]; shr eax,3; imul eax,0xFFFF8E39`) — no `[rcx + index*stride]` element read [V]. The live capture oc_u_er6_light_desc (already pending, rva 0x6640d80, size 256, max 6) can supply tag-3/tag-4 desc bytes and name the visitor caller chain via ret= [V live], but it CANNOT install a read/write watch on the pass vectors, so it cannot surface a consumer; no livemem target address exists statically (0x5ABA5C0 = per-call TLS getter, rdis imm/ptr to 0x5aba5c0 = 0 refs/slots [V static]).

## CLOSES?

CLOSES? NO — single blocking fact: no draining reader/consumer of pass+0x800 (0x14-byte summary list), pass+0x648 (0x48-byte light-record vector), pass+0x4A0 (0x84-byte GameplayMetadata vector) or pass+0x1D0 (0x50-byte ShadowAtlasFrame vector) exists anywhere in Minecraft.Windows.exe 1.26.62.01 [V negative]: whole-image fld --r scans negative, every write to the four end cursors is an end-cursor increment / grow-emplace (section 2 table, [V]), no `[base + index*stride]` element read found via the new rdis-walk/LEA-gap angle [V], every 0x5ABA5C0 caller accounted for [V], endFrame and descscan2 clean [V]. The four vectors are write-only statically. Closing consumers needs a live read/write watch on the pass vectors — livecap oc_u_er6_light_desc (pending) samples entry registers/desc bytes and reports ret= only; it cannot watch pass-vector memory, and no livemem target address exists statically. Description field value names are a second open [?] for the same reason (no RTTI, no description member-name strings in the release exe; headers use mValue* placeholders; live bytes give sizes/values never names); parked in MIRROR_SKIP, not the closure gate.

Resolved [V] and carried, not re-proven: tag 2 = GameplayMetadata, tag 3 = LightPoint (FrameBuilder.h wins the group_visitors.md conflict which had 2/3 swapped); the four end-cursor writers to pass+0x800/+0x648/+0x4A0/+0x1D0; description field read offsets/sizes with live byte confirmation for tags 0/1/2 [V live].

## TOOL REQUESTS

CAPTURE REQUESTED oc_u_er6_light_desc — light-visitor entry capture (rva 0x6640d80 = 107220352, size 256, max 6) already queued in docs/progress/capture_requests.json (state pending; 4/4 pending slots in use, `add` rejects duplicates). Result awaited in docs/data/live/oc_u_er6_light_desc.txt via `python tools/livecap/request.py result oc_u_er6_light_desc`. What it can add: tag-3 (LightPoint) and tag-4 (ShadowAtlasFrame) description bytes at visitor entry, plus caller chain via ret= — cite [V live] when available. What it cannot add: consumers of pass+0x800/+0x648/+0x4A0/+0x1D0 (no pass-memory read/write watch). Helper scripts: None.
