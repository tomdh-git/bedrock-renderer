## NEXT
DONE

# U-ER6 — R6: LightAmbient / LightDirectional / Light tag 2 / tag 3 / tag 4 (1.26.62.01)

Goal: close R6 — description field value names, the group_visitors.md vs FrameBuilder.h LightGroupTag tag-name conflict, consumers (draining element readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0. Exe Minecraft.Windows.exe 1.26.62.01, RVAs image-relative. Static analysis only (game closed); live capture is orchestrator-run via tools/livecap/request.py — I never touch the game, I only queue/read results. Tags: [V] seen in disassembly (RVA cited) | [V carried] proven in earlier docs/progress/oc_U-ER6_r*.md notes and NOT re-proven per RETRY #1 | [V negative] whole-image scan found nothing | [V live] live capture bytes (docs/data/live/*.txt) | [I] inferred | [?] unknown. Every `0xRVA  instr` line is copied verbatim from a verified listing/disassembly.

Input data (read fully, not re-generated): docs/functions/6640d80_light_visitor.md; docs/functions/5aba5c0.md; docs/functions/group_visitors.md (superseded on tags 2/3); docs/functions/light_game_descriptions.md; docs/data/live/light_visitor.txt; docs/data/live/README.md; docs/data/live/_status.txt; docs/BGFX_MAP.md sections 6gq/6ih/6hi/6w; src/sdk/mc/deps/minecraft_renderer/framebuilder/FrameBuilder.h (LightGroupTag enum); Descriptions.h/LightDescriptions.h/LightGameDescriptions.h.

## 1. Carried [V] — tag -> type / LightGroupTag; conflict RESOLVED (not re-proven per RETRY #1)

| offset | size | read/store address | verbatim `0xRVA  instr` line | meaning | tag |
|---|---|---|---|---|---|
| variant+0x08 tag byte | 1 | 0x6640dc4, 0x6640de6 | `0x6640dc4  movzx eax,byte ptr [rdx+8]`<br>`0x6640de6  jmp rax` | tag byte at variant+0x08; `jmp rax` dispatches through jump table 0xF2BF2B0 (entries 0=0x6640de8, 1=0x66415b0, 2=0x6640f1b, 3=0x66410a0, 4=0x6640ec1, 5=0x66417af, 6=0x664187d, 7=0x6641524) | [V carried] |
| tag 2 = GameplayMetadata | 1 | 0x53e5fb4, 0x53e5fbf | `0x53e5fb4  mov byte ptr [rbp-0x18],2`<br>`0x53e5fbf  mov rax,[rax+0x380]` | LightGroupTag::GameplayMetadata = 2; Light vslot 0x380 insert; srcloc 0xF248ED0 `__FUNCSIG__ FrameBuilder::insert [TDescription = gamecomponents::GameplayMetadata]`; JT entry 2 = 0x6640f1b | [V carried] |
| tag 3 = LightPoint | 1 | 0x535a9b7, 0x535a9c1 | `0x535a9b7  mov byte ptr [rbp+0x278],3`<br>`0x535a9c1  mov rax,[rax+0x380]` | LightGroupTag::LightPoint = 3; Light vslot 0x380 insert; srcloc 0xF248DA0 `LightPointDescription`; JT entry 3 = 0x66410a0 | [V carried] |
| tag-name conflict (group_visitors.md vs FrameBuilder.h LightGroupTag) | - | FrameBuilder.h:79-88 | `enum class LightGroupTag : uint64_t { Ambient = 0, Directional = 1, GameplayMetadata = 2, LightPoint = 3, ShadowAtlasFrame = 4, ServerGraphicsOverrideParameters = 5, VoxelVolume = 6, TransitioningVoxelVolume = 7 };` | RESOLVED [V carried]: producer tag stores + __FUNCSIG__ srclocs (rows tag 2 / tag 3) prove tag 2 = GameplayMetadata and tag 3 = LightPoint; FrameBuilder.h wins; group_visitors.md had them swapped (LightPoint@2 / GameplayMetadata@3) and is superseded; BGFX_MAP.md 6w/6ih line 2051 agrees | [V carried] |

## 2. Carried [V] — Light-visitor writers to pass+0x800 / +0x648 / +0x4A0 / +0x1D0 (write-only; no end-cursor pop/decrement anywhere [V negative, whole-image fld --w])

| offset | size | read/store address | verbatim `0xRVA  instr` line | meaning | tag |
|---|---|---|---|---|---|
| pass+0x800 end cursor | 8 | 0x6640e84, 0x6640e8b, 0x6640eb4, 0x66417a2, 0x6641517 | `0x6640e84  mov rdx,[rsi+0x800]`<br>`0x6640e8b  cmp rdx,[rsi+0x808]`<br>`0x6640eb4  add qword ptr [rsi+0x800],0x14`<br>`0x66417a2  add qword ptr [rsi+0x800],0x14`<br>`0x6641517  add qword ptr [rsi+0x800],0x14` | end cursor of the 0x14-byte summary list (cap cursor +0x808 compared at 0x6640e8b); writers: Ambient 0x6640eb4, Directional 0x66417a2, LightPoint 0x6641517 (all increment by 0x14) | [V carried] |
| pass+0x648 end cursor | 8 | 0x66416f8, 0x66416ff, 0x664145a, 0x6641461 | `0x66416f8  lea rcx,[rsi+0x648]`<br>`0x66416ff  call 0x675FB30`<br>`0x664145a  lea rcx,[rsi+0x648]`<br>`0x6641461  call 0x675FB30` | end cursor of the 0x48-byte light-record vector (begin +0x648 / end +0x650); Directional 0x66416ff and LightPoint 0x6641461 pass &end to grow-emplace 0x675FB30 | [V carried] |
| pass+0x4A0 end cursor | 8 | 0x6640f78, 0x6640f7f, 0x6641090 | `0x6640f78  mov r12,[rdi+0x4A0]`<br>`0x6640f7f  cmp r12,[rdi+0x4A8]`<br>`0x6641090  add qword ptr [rdi+0x4A0],0x84` | end cursor of the 0x84-byte GameplayMetadata vector (begin +0x498 / cap +0x4A8); tag-2 writer, stride 0x84; load 0x6640f78, cap compare 0x6640f7f | [V carried] |
| pass+0x1D0 end cursor | 8 | 0x66419c6 | `0x66419c6  add qword ptr [rsi+0x1D0],0x50` | end cursor of the 0x50-byte ShadowAtlasFrame vector (begin +0x1C8 / cap +0x1D8); tag-4 writer, stride 0x50 | [V carried] |

## 3. Live capture status (NEW THIS UNIT)

- oc_u_er6_light_desc: pending at light-visitor entry 0x6640D80 (RDX = desc pointer, docs/data/live/README.md CORRECTION 2026-11-15), size 256, max 6, state "pending" in docs/progress/capture_requests.json; `python tools/livecap/request.py result oc_u_er6_light_desc` -> "no result yet (orchestrator has not run it)"; docs/data/live/_status.txt (DONE t=120) does not list it. 4/4 pending slots are in use and `add` rejects duplicates, so no replacement capture can be queued this unit.
- light_visitor.txt (pre-existing live capture, rva=0x6640D80, kind=visitor, size=0x300): 6 samples — tag 5 @0x14AA80 (line 3), tag 0 @0x14A5B8 (line 4), tag 2 @0x14A5A0 (lines 6-7), tag 1 @0x14A400 (lines 5, 8). [V live] confirms runtime field SIZES only: tag 0 Ambient +0x00..+0x0F all zero (line 4); tag 1 Directional +0x00..+0x0C = 1.0f x4 f32 (line 5); tag 2 GameplayMetadata +0x00..+0x14 six f32 (8.5, 1.0, 2.0, 15.0, 1.0, 0.5), +0x18 u32 per-object, +0x1C u32 = 4, +0x20 u32 = 18000 (lines 6-7). No tag 3/4 samples. Visitor-kind format is `tag descptr hex` only (README.md line 6-7) — no REG=/ret= caller lines.
- What the capture can add when it runs: desc bytes for whatever tag flows at entry + caller chain via ret= [V live]. What it CANNOT add: consumers of pass+0x800/+0x648/+0x4A0/+0x1D0 (entry sampling only, no read/write watch on pass-vector memory); and no livemem target exists statically (0x5ABA5C0 = per-call TLS thread-local getter; rdis imm/ptr to 0x5aba5c0 = 0 refs/slots [V static]).

## 4. NEW ANGLE TRIED THIS UNIT AND ITS RESULT (carried from r53, not re-run)

- rdis walk from 0x66416f8 `lea rcx,[rsi+0x648]` --reg rcx (3020 instructions reachable from the Directional-case pass+0x648 base): shows only the grow-emplace call 0x675FB30 and end/cursor index math (`mov eax,[rsi+0x650]; sub eax,[rsi+0x648]; shr eax,3; imul eax,0xFFFF8E39`) — no `[rcx + index*stride]` element read [V].
- Together with the carried negatives (whole-image fld --r/--w on 0x800/0x648/0x4A0/0x1D0 and begin/cap cursors = writer cursor accesses only; all 18 0x5ABA5C0 callers enumerated, none drains; descscan2 tag-2 case 0x6640f1b reads desc+0x00..+0x84 only, no pass offset; magic-multiplier imm scans ÷0x14/÷0x48/÷0x84/÷0x50 = writer hits only; endFrame 0x66232b0 re-list clean; BGFX_MAP.md 6gq/6ih/6hi/6w name no consumer of the four vectors) static analysis is exhausted: any consumer must compute `[pass + index*stride]` with no immediate, which offset scans cannot see; no tool available to me installs a read/write watchpoint on pass-vector memory.

## 5. Pending: consumers (draining element readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — NOT LOCATED

| offset | size | read/store address | verbatim `0xRVA  instr` line | meaning | tag |
|---|---|---|---|---|---|
| pass+0x800 elements | 0x14 | - | - | no draining element read of the 0x14-byte summary vector anywhere in Minecraft.Windows.exe 1.26.62.01; end-cursor increment writes only; whole-image fld --r scans negative | [V negative] |
| pass+0x648 elements | 0x48 | - | - | no draining element read of the 0x48-byte light-record vector anywhere in the exe; writes are grow-emplace calls to 0x675FB30 plus index-word stores only | [V negative] |
| pass+0x4A0 elements | 0x84 | - | - | no draining element read of the 0x84-byte GameplayMetadata vector anywhere in the exe; writes are end-cursor increments only | [V negative] |
| pass+0x1D0 elements | 0x50 | - | - | no draining element read of the 0x50-byte ShadowAtlasFrame vector anywhere in the exe; writes are end-cursor increments only | [V negative] |

## 6. Pending: description field value names — UNKNOWN [?]

| offset | size | read/store address | verbatim `0xRVA  instr` line | meaning | tag |
|---|---|---|---|---|---|
| description field value names | - | - | - | unknown [?]: release exe has no RTTI and no description member-name strings; LightDescriptions.h/LightGameDescriptions.h type every field as mValue* placeholders with static_assert offsets only (e.g. ShadowAtlasFrameDescriptionReads mRow0..mRow3, mTexture, mTextureCtrl; static_asserts at 0x00/0x10/0x20/0x30/0x40/0x48; sizeof 0x50); descscan2 tag-2 case 0x6640f1b reads desc+0x00..+0x84 only [V]; live bytes confirm sizes/values only, never names [V live] | [?] |

## Blocking fact

All four vectors are write-only in Minecraft.Windows.exe 1.26.62.01: only end-cursor increment / grow-emplace writes exist [V] (section 2 table); no element read of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 was found by whole-image read scans [V negative]; no 0x5ABA5C0 caller drains them [V]. Closing consumers needs a live read/write watch on pass-vector memory — livecap oc_u_er6_light_desc (pending, not yet run) samples entry registers/desc bytes and reports ret= only; it cannot watch pass-vector memory, and no livemem target address exists statically. Description field value names are a second open [?] for the same reason (no RTTI, no member-name strings; live bytes give sizes/values never names); parked in MIRROR_SKIP per prior review (r2 REVIEW 24/24 [V]), not the closure gate.

## CLOSES?

CLOSES? NO — single blocking fact: no draining reader/consumer of pass+0x800 (0x14-byte summary list), pass+0x648 (0x48-byte light-record vector), pass+0x4A0 (0x84-byte GameplayMetadata vector) or pass+0x1D0 (0x50-byte ShadowAtlasFrame vector) exists anywhere in Minecraft.Windows.exe 1.26.62.01 [V negative]: whole-image fld --r scans negative, every write to the four end cursors is an end-cursor increment / grow-emplace (section 2 table, [V]), no `[base + index*stride]` element read found via the new rdis-walk/LEA-gap angle [V], every 0x5ABA5C0 caller accounted for [V], endFrame and descscan2 clean [V]. The four vectors are write-only statically. Closing consumers needs a live read/write watch on the pass vectors — livecap oc_u_er6_light_desc (pending; result awaited via `python tools/livecap/request.py result oc_u_er6_light_desc`) samples entry registers/desc bytes and reports ret= only; it cannot watch pass-vector memory, and no livemem target address exists statically.

Resolved [V] and carried, not re-proven: tag 2 = GameplayMetadata, tag 3 = LightPoint (FrameBuilder.h:79-88 wins the group_visitors.md conflict which had 2/3 swapped); jump table 0xF2BF2B0 dispatch; the four end-cursor writers to pass+0x800/+0x648/+0x4A0/+0x1D0; tag 0/1/2 description field sizes confirmed by live bytes [V live].

## TOOL REQUESTS

oc_u_er6_light_desc | rva 0x6640D80 (light-visitor entry, RDX = desc ptr), size 256, max 6 -> REG=value hit=N ret=0xRVA <desc bytes> | already pending in docs/progress/capture_requests.json (state pending; 4/4 pending slots in use, `add` rejects duplicates); result awaited via `python tools/livecap/request.py result oc_u_er6_light_desc`. What it can add: desc bytes for the tag flowing at entry + caller chain via ret= [V live]. What it cannot add: consumers of pass+0x800/+0x648/+0x4A0/+0x1D0 (no pass-memory read/write watch). Helper scripts: None.
