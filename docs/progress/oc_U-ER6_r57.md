## NEXT
DONE

# U-ER6 — R6: LightAmbient / LightDirectional / Light tag 2 / tag 3 / tag 4 (1.26.62.01)

Goal: close R6 — description field value names, the group_visitors.md vs FrameBuilder.h LightGroupTag tag-name conflict, and consumers (draining element readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0. Exe Minecraft.Windows.exe 1.26.62.01, RVAs image-relative. Static analysis only (brief rule 1; the game was observed running at pid 13452 for a read-only livemem status check, no reads issued). Tags: [V] seen in disassembly (RVA cited) | [V carried] proven in earlier docs/progress/oc_U-ER6_r*.md notes and NOT re-proven per RETRY #1 | [V negative] whole-image scan found nothing | [V live] live capture bytes (docs/data/live/*.txt) | [I] inferred | [?] unknown. Every `0xRVA  instr` line is copied verbatim from a verified listing/disassembly.

Input data (read fully, not re-generated): docs/functions/6640d80_light_visitor.md; docs/functions/5aba5c0.md; docs/functions/group_visitors.md (superseded on tags 2/3); docs/functions/light_game_descriptions.md; docs/data/live/light_visitor.txt; docs/data/live/README.md; docs/data/live/_status.txt; docs/BGFX_MAP.md sections 6gq/6ih/6hi/6w; src/sdk/mc/deps/minecraft_renderer/framebuilder/FrameBuilder.h (LightGroupTag enum); Descriptions.h/LightDescriptions.h/LightGameDescriptions.h.

## 1. Carried [V] — tag -> type / LightGroupTag; conflict RESOLVED (not re-proven per RETRY #1)

| offset | size | read/store address | verbatim `0xRVA  instr` line | meaning | tag |
|---|---|---|---|---|---|
| variant+0x08 tag byte | 1 | 0x6640dc4, 0x6640de6 | `0x6640dc4  movzx eax,byte ptr [rdx+8]`<br>`0x6640de6  jmp rax` | tag byte at variant+0x08; `jmp rax` dispatches through jump table 0xF2BF2B0 (entries 0=0x6640de8, 1=0x66415b0, 2=0x6640f1b, 3=0x66410a0, 4=0x6640ec1, 5=0x66417af, 6=0x664187d, 7=0x6641524) | [V carried] |
| tag 0 = Ambient | 1 | 0x53e3511 | `0x53e3511  mov byte ptr [rbp+0x138],0` | LightGroupTag::Ambient = 0 (FrameBuilder.h:79-88); JT entry 0; srcloc 0xF248E70 RenderLightAmbientDescription | [V carried] |
| tag 1 = Directional | 1 | 0x53709d4 | `0x53709d4  mov byte ptr [rbp+0x18],1` | LightGroupTag::Directional = 1; JT entry 1; srcloc 0xF248F70 LightDirectionalDescription | [V carried] |
| tag 2 = GameplayMetadata | 1 | 0x53e5fb4, 0x53e5fbf | `0x53e5fb4  mov byte ptr [rbp-0x18],2`<br>`0x53e5fbf  mov rax,[rax+0x380]` | LightGroupTag::GameplayMetadata = 2; Light vslot 0x380 insert; JT entry 2; srcloc 0xF248ED0 GameplayMetadata | [V carried] |
| tag 3 = LightPoint | 1 | 0x535a9b7, 0x535a9c1 | `0x535a9b7  mov byte ptr [rbp+0x278],3`<br>`0x535a9c1  mov rax,[rax+0x380]` | LightGroupTag::LightPoint = 3; light clone 0x53599d0 insert; JT entry 3; srcloc 0xF248DA0 LightPointDescription | [V carried] |
| tag 4 = ShadowAtlasFrame | 1 | 0x535a696, 0x535a6a0 | `0x535a696  mov byte ptr [rbp+0x278],4`<br>`0x535a6a0  mov rax,[rax+0x380]` | LightGroupTag::ShadowAtlasFrame = 4; light clone 0x53599d0 insert; JT entry 4; srcloc 0xF248D80 ShadowAtlasFrameDescription | [V carried] |
| tag-name conflict | - | FrameBuilder.h:79-88 | `enum class LightGroupTag : uint64_t { Ambient = 0, Directional = 1, GameplayMetadata = 2, LightPoint = 3, ShadowAtlasFrame = 4, ServerGraphicsOverrideParameters = 5, VoxelVolume = 6, TransitioningVoxelVolume = 7 };` | RESOLVED [V carried]: producer tag stores + __FUNCSIG__ srclocs prove tag 2 = GameplayMetadata and tag 3 = LightPoint; FrameBuilder.h wins; group_visitors.md had them swapped (LightPoint@2 / GameplayMetadata@3) and is superseded; BGFX_MAP.md 6w agrees | [V carried] |

## 2. Carried [V] — Light-visitor writers to pass+0x800 / +0x648 / +0x4A0 / +0x1D0 (write-only)

Pass-object vectors (begin/end/cap cursors): summary +0x7F8/+0x800/+0x808 stride 0x14; light records +0x648/+0x650 stride 0x48; GameplayMetadata +0x498/+0x4A0/+0x4A8 stride 0x84; ShadowAtlasFrame +0x1C8/+0x1D0/+0x1D8 stride 0x50 [V carried]. Every write below is an end-cursor increment / grow-emplace; no end-cursor pop/decrement exists anywhere in the exe [V negative, whole-image fld --w].

| offset | size | read/store address | verbatim `0xRVA  instr` line | meaning | tag |
|---|---|---|---|---|---|
| pass+0x800 end cursor | 8 | 0x6640e84, 0x6640e8b, 0x6640eb4, 0x66417a2, 0x6641517 | `0x6640e84  mov rdx,[rsi+0x800]`<br>`0x6640e8b  cmp rdx,[rsi+0x808]`<br>`0x6640eb4  add qword ptr [rsi+0x800],0x14`<br>`0x66417a2  add qword ptr [rsi+0x800],0x14`<br>`0x6641517  add qword ptr [rsi+0x800],0x14` | end cursor of the 0x14-byte summary list (cap cursor +0x808 compared at 0x6640e8b); writers: Ambient 0x6640eb4, Directional 0x66417a2, LightPoint 0x6641517 (all increment by 0x14) | [V carried] |
| pass+0x648 end cursor | 8 | 0x66416f8, 0x66416ff, 0x664145a, 0x6641461 | `0x66416f8  lea rcx,[rsi+0x648]`<br>`0x66416ff  call 0x675FB30`<br>`0x664145a  lea rcx,[rsi+0x648]`<br>`0x6641461  call 0x675FB30` | end cursor of the 0x48-byte light-record vector (begin +0x648 / end +0x650); Directional 0x66416ff and LightPoint 0x6641461 pass &end to grow-emplace 0x675FB30 | [V carried] |
| pass+0x4A0 end cursor | 8 | 0x6640f78, 0x6640f7f, 0x6641090 | `0x6640f78  mov r12,[rdi+0x4A0]`<br>`0x6640f7f  cmp r12,[rdi+0x4A8]`<br>`0x6641090  add qword ptr [rdi+0x4A0],0x84` | end cursor of the 0x84-byte GameplayMetadata vector (begin +0x498 / cap +0x4A8); tag-2 writer, stride 0x84; load 0x6640f78, cap compare 0x6640f7f | [V carried] |
| pass+0x1D0 end cursor | 8 | 0x66419c6 | `0x66419c6  add qword ptr [rsi+0x1D0],0x50` | end cursor of the 0x50-byte ShadowAtlasFrame vector (begin +0x1C8 / cap +0x1D8); tag-4 writer, stride 0x50 | [V carried] |

## 3. Live capture status and NEW angles tried this unit (all fail on the consumer blocker)

- `python tools/livecap/request.py result oc_u_er6_light_desc` -> "no result yet (orchestrator has not run it)"; no docs/data/live/oc_u_er6_light_desc.txt exists (checked this unit; _status.txt lists only older done/skipped captures).
- Capture oc_u_er6_light_desc is ALREADY PENDING: rva 0x6640d80 (light-visitor entry; RDX = desc pointer per docs/data/live/README.md), size 256, max 6, in docs/progress/capture_requests.json (state pending). 4/4 pending slots are in use (er5_clone_4c8a5b0, l8b_resizetex_slot31, sub_1289440_callers, oc_u_er6_light_desc) and `add` rejects duplicates/new requests, so nothing can be re-queued this unit. What the capture CAN add [V live when it runs]: tag-3 (LightPoint) and tag-4 (ShadowAtlasFrame) description bytes at visitor entry plus the caller chain via ret=. What it CANNOT add: consumers of pass+0x800/+0x648/+0x4A0/+0x1D0 — function-entry sampling only, no read/write watch on pass-vector memory.
- livemem: `python tools/sigs/livemem.py status` -> pid 13452, base 0x7ff7a59c0000, version OK 1.26.62.01 (game running; status only, no read calls issued per brief rule 1). But the pass object is per-thread: the visitor does `mov ecx,0x9D0; add rcx,[rdi+0x10]; call 0x5ABA5C0; mov rsi,rax` so rsi = pass object = ThreadLocalObject node value at node+0x10; no static pass-object address exists (rdis imm/ptr/xr to 0x5aba5c0 = 0 refs/slots [V static]); livemem is read-only (VM_READ only, no breakpoints/watchpoints) so it cannot trace WHICH CODE reads pass-vector elements. TRIED: not usable for the consumer blocker.
- vt/vcalls: not applicable — the pass object has no static address or vtable to walk [V carried].
- descscan2: tag cases read desc fields only or write cursors; no pass offset [V carried].
- Static angles exhausted previously (carried negatives, not re-run per RETRY #1): whole-image fld --r/--w on 0x800/0x648/0x4A0/0x1D0 plus begin/cap cursors (stack/unrelated locals only); imm 0x14/0x48/0x84/0x50 and magic-multiplier scans (÷0x14=0xFFFFCCCD, ÷0x48=0xFFFF8E39, ÷0x84=0xFFFF83E1) — writer hits only; rdis walk from 0x66416f8 `lea rcx,[rsi+0x648]` (3020 instructions reachable) shows only grow-emplace 0x675FB30 and end/cursor index math, no `[rcx + index*stride]` element read [V]; endFrame 0x66232b0 re-list clean; all 0x5ABA5C0 callers enumerated, none drains; rdis xr/callers of visitor 0x6640ae0 = 0 [V]; per-draw 0x66ea3d0 appends u16 indices to pass+0x8A8 and reads none of the four cursors [V]; ClusterLights body 0xbc5bad0 reads other structures [V]; BGFX_MAP.md 6gq/6ih/6hi/6w name no consumer [V]. Any consumer must compute `[pass + index*stride]` (no immediate), which offset scans cannot see; no read/write watch tool is available to this unit.

## 4. Pending: consumers (draining element readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — NOT LOCATED

| offset | size | read/store address | verbatim `0xRVA  instr` line | meaning | tag |
|---|---|---|---|---|---|
| pass+0x800 elements | 0x14 | - | - | no draining element read of the 0x14-byte summary vector anywhere in Minecraft.Windows.exe 1.26.62.01; end-cursor increment writes only; whole-image fld --r scans negative; no `[base + index*stride]` element read via rdis-walk/LEA-gap angle [V] | [V negative] |
| pass+0x648 elements | 0x48 | - | - | no draining element read of the 0x48-byte light-record vector anywhere in the exe; writes are grow-emplace calls to 0x675FB30 plus index-word stores only [V] | [V negative] |
| pass+0x4A0 elements | 0x84 | - | - | no draining element read of the 0x84-byte GameplayMetadata vector anywhere in the exe; writes are end-cursor increments only [V] | [V negative] |
| pass+0x1D0 elements | 0x50 | - | - | no draining element read of the 0x50-byte ShadowAtlasFrame vector anywhere in the exe; writes are end-cursor increments only [V] | [V negative] |

## 5. Pending: description field value names — UNKNOWN [?]

| offset | size | read/store address | verbatim `0xRVA  instr` line | meaning | tag |
|---|---|---|---|---|---|
| description field value names | - | - | - | unknown [?]: the release exe has no RTTI and no description member-name strings; LightDescriptions.h/LightGameDescriptions.h type every field as mValue* placeholders with static_assert offsets only; descscan2 tag-2 case 0x6640f1b reads desc+0x00..+0x84 only [V]; live desc bytes confirm sizes/values only, never names [V live]; parked in MIRROR_SKIP per prior review (r2 REVIEW 24/24 [V]), not the closure gate. | [?] |

## Blocking fact

All four vectors are write-only in Minecraft.Windows.exe 1.26.62.01: only end-cursor increment / grow-emplace writes exist [V] (section 2 table); no element read of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 was found by whole-image read scans [V negative], by the rdis-walk/LEA-gap angle [V], or by the new livemem/livecap angles this unit; no end-cursor pop/decrement exists [V negative]; no 0x5ABA5C0 caller drains them [V]. Description field value names are a second open [?] for the same reason (no names in the exe or dumps); parked in MIRROR_SKIP, not the closure gate.

## CLOSES?

CLOSES? NO — single blocking fact: no draining reader/consumer of pass+0x800 (0x14-byte summary list), pass+0x648 (0x48-byte light-record vector), pass+0x4A0 (0x84-byte GameplayMetadata vector) or pass+0x1D0 (0x50-byte ShadowAtlasFrame vector) exists anywhere in Minecraft.Windows.exe 1.26.62.01 [V negative]: all four vectors are write-only statically (end-cursor increments / grow-emplace, no pop/decrement, no `[base + index*stride]` element read); every static angle (whole-image fld scans, imm/magic-multiplier scans, rdis walk, endFrame re-list, all 0x5ABA5C0 callers, descscan2, xr/callers; vt/vcalls n/a) is negative; the pending entry capture oc_u_er6_light_desc and read-only livemem cannot install a read/write watch on pass-vector memory, and no static pass-object address exists for livemem. Closing consumers requires a live read/write watch on pass+0x800/+0x648/+0x4A0/+0x1D0 — not available to this unit.

Resolved [V] and carried, not re-proven: tag 2 = GameplayMetadata, tag 3 = LightPoint; tag-name conflict resolved (FrameBuilder.h wins over group_visitors.md, which had them swapped); the four end-cursor writers to pass+0x800/+0x648/+0x4A0/+0x1D0 [V]; description field read offsets/sizes with live byte confirmation for tags 0/1/2 [V live].

## TOOL REQUESTS

CAPTURE REQUESTED oc_u_er6_light_desc — light-visitor entry capture (rva 0x6640d80 = 107220352, size 256, max 6) already pending in docs/progress/capture_requests.json (state pending; 4/4 pending slots in use, `add` rejects duplicates/new requests); result checked this unit via `python tools/livecap/request.py result oc_u_er6_light_desc` -> "no result yet (orchestrator has not run it)". What it can add: tag-3 (LightPoint) and tag-4 (ShadowAtlasFrame) description bytes at visitor entry and the caller chain via ret= — cite [V live] when available. What it cannot add: consumers of pass+0x800/+0x648/+0x4A0/+0x1D0 (no pass-memory read/write watch). What would close R6: a live read/write watchpoint on pass-vector memory or a live pass-object address plus a read trace — neither available to this unit. Helper scripts: None.
