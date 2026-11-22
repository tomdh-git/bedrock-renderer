## NEXT
DONE

# U-ER6 — R6: LightAmbient / LightDirectional / Light tag 2 / tag 3 / tag 4 (1.26.62.01)

Goal: close R6 — description field value names, the group_visitors.md vs FrameBuilder.h LightGroupTag tag-name conflict, and consumers (draining element readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0. Exe Minecraft.Windows.exe 1.26.62.01, RVAs image-relative. Static analysis only (brief rule 1). Tags: [V] seen in disassembly (RVA cited, re-verified against the exe this unit) | [V carried] proven in earlier docs/progress/oc_U-ER6_r*.md notes and NOT re-proven per RETRY #1 | [V negative] whole-image scan found nothing | [V live] live capture bytes (docs/data/live/*.txt) | [I] inferred | [?] unknown. Every `0xRVA  instr` line is copied verbatim from a verified rdis listing of the exe.

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
| pass+0x800 end cursor | 8 | 0x6640e84, 0x6640e8b, 0x6640eb4, 0x66417a2, 0x6641517 | `0x6640e84  mov rdx,[rsi+0x800]`<br>`0x6640e8b  cmp rdx,[rsi+0x808]`<br>`0x6640eb4  add qword ptr [rsi+0x800],0x14`<br>`0x66417a2  add qword ptr [rsi+0x800],0x14`<br>`0x6641517  add qword ptr [rsi+0x800],0x14` | end cursor of the 0x14-byte summary list (cap cursor +0x808 compared at 0x6640e8b); writers: Ambient 0x6640eb4, Directional 0x66417a2, LightPoint 0x6641517 (all increment by 0x14); rsi = pass object = return of TLS getter 0x5ABA5C0 (rdis annotation `ret@5aba5c0+0x800`) | [V carried] |
| pass+0x648 end cursor | 8 | 0x66416f8, 0x66416ff, 0x664145a, 0x6641461 | `0x66416f8  lea rcx,[rsi+0x648]`<br>`0x66416ff  call 0x675FB30`<br>`0x664145a  lea rcx,[rsi+0x648]`<br>`0x6641461  call 0x675FB30` | end cursor of the 0x48-byte light-record vector (begin +0x648 / end +0x650); Directional 0x66416ff and LightPoint 0x6641461 pass &end to grow-emplace 0x675FB30 | [V carried] |
| pass+0x4A0 end cursor | 8 | 0x6640f78, 0x6640f7f, 0x6641090 | `0x6640f78  mov r12,[rdi+0x4A0]`<br>`0x6640f7f  cmp r12,[rdi+0x4A8]`<br>`0x6641090  add qword ptr [rdi+0x4A0],0x84` | end cursor of the 0x84-byte GameplayMetadata vector (begin +0x498 / cap +0x4A8); tag-2 writer, stride 0x84; load 0x6640f78, cap compare 0x6640f7f | [V carried] |
| pass+0x1D0 end cursor | 8 | 0x66419c6 | `0x66419c6  add qword ptr [rsi+0x1D0],0x50` | end cursor of the 0x50-byte ShadowAtlasFrame vector (begin +0x1C8 / cap +0x1D8); tag-4 writer, stride 0x50 | [V carried] |

## 3. Desc field read offsets/sizes re-verified this unit [V] — sizes confirmed, names still unknown

| offset | size | read/store address | verbatim `0xRVA  instr` line | meaning | tag |
|---|---|---|---|---|---|
| tag-4 (ShadowAtlasFrame) desc+0x00 | 16 | 0x6640ec1 | `0x6640ec1  movups xmm6,[rsi]` | rsi = description pointer (visitor entry arg in RDX per docs/data/live/README.md correction 2026-11-15); 16-byte field copied into the pass+0x1C8 vector element at +0x00 | [V] |
| desc+0x10 | 16 | 0x6640ecb | `0x6640ecb  movups xmm7,[rsi+0x10]` | element +0x10 | [V] |
| desc+0x20 | 16 | 0x6640ed6 | `0x6640ed6  movups xmm8,[rsi+0x20]` | element +0x20 | [V] |
| desc+0x30 | 16 | 0x6640ee3 | `0x6640ee3  movups xmm9,[rsi+0x30]` | element +0x30 | [V] |
| desc+0x48 | 8 | 0x6640f01 | `0x6640f01  mov rcx,[rsi+0x48]` | {ptr, control-block} pair at +0x40/+0x48; non-null ctrl use-count `lock inc [rcx+8]` at 0x6640f0e | [V] |
| tag-2 (GameplayMetadata) desc+0x00..+0x84 | - | 0x6640f1b | - | descscan2 tag-2 case 0x6640f1b reads desc+0x00..+0x84 only, no pass offset [V carried] | [V carried] |

Total description bytes consumed by tag 4 = 0x50 (matches ShadowAtlasFrame stride and sizeof in Descriptions.h) [V]. Member names are not in the release exe (no RTTI, no description member-name strings); headers type fields as mValue* placeholders with static_assert offsets only — value NAMES stay [?].

## 4. New static angles tried this unit on the consumer blocker — all fail

- `python tools/livecap/request.py result oc_u_er6_light_desc` -> "no result yet (orchestrator has not run it)"; no docs/data/live/oc_u_er6_light_desc.txt exists. Capture oc_u_er6_light_desc (rva 0x6640d80, size 256, max 6) is already pending in docs/progress/capture_requests.json; 4/4 pending slots are in use (er5_clone_4c8a5b0, l8b_resizetex_slot31, sub_1289440_callers, oc_u_er6_light_desc) so `add` rejects duplicates/new requests. What the capture CAN add [V live when it runs]: tag-3/tag-4 desc bytes at visitor entry plus caller chain via ret=. What it CANNOT add: consumers of pass+0x800/+0x648/+0x4A0/+0x1D0 — entry sampling only, no read/write watch on pass-vector memory.
- `python tools/sigs/xref.py str "LightAmbient"` / `"ShadowAtlasFrame"` / `"LightPoint"` -> only the FrameBuilder::insert `__FUNCSIG__` srcloc strings and the "LightAmbientColorAndIntensity" string (refs 0xbbd0fb7 in sub_bbce7b0, 0xbbf59a6 in sub_bbe2d50); no string names a pass-vector consumer [V].
- descscan2 on the tag cases: tag-2 case 0x6640f1b reads desc+0x00..+0x84; tag-4 case 0x6640ec1 reads desc+0x00..+0x48; no pass offset read in any case [V carried].
- livemem: `python tools/sigs/livemem.py status` -> pid 13452, base 0x7ff7a59c0000, version OK (game running; status only, no reads issued). The pass object is per-thread (visitor: `mov ecx,0x9D0; add rcx,[rdi+0x10]; call 0x5ABA5C0; mov rsi,rax`); no static pass-object address exists (rdis imm/ptr/xr to 0x5aba5c0 = 0 data refs/slots [V carried]); livemem is read-only with no breakpoints/watchpoints, so it cannot trace WHICH CODE reads pass-vector elements. Not usable for the consumer blocker.
- Whole-image fld --r/--w on 0x800/0x648/0x4A0/0x1D0 plus begin/cap cursors; imm/magic-multiplier scans (÷0x14=0xFFFFCCCD, ÷0x48=0xFFFF8E39, ÷0x84=0xFFFF83E1, ÷0x50=0xCCCCCCCCCCCCCCCD); rdis walk from 0x66416f8 (3020 instructions) showing only grow-emplace 0x675FB30 and cursor index math, no `[base + index*stride]` element read; endFrame 0x66232b0 re-list; all 0x5ABA5C0 callers enumerated; rdis xr/callers of visitor 0x6640ae0 = 0; BGFX_MAP.md 6gq/6ih/6hi/6w name no consumer — all carried negatives, NOT re-run per RETRY #1. Any consumer must compute `[pass + index*stride]` with no immediate, which offset scans cannot see; no read/write watch tool is available to this unit.

## 5. Pending: consumers (draining element readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — NOT LOCATED

| offset | size | read/store address | verbatim `0xRVA  instr` line | meaning | tag |
|---|---|---|---|---|---|
| pass+0x800 elements | 0x14 | - | - | no draining element read of the 0x14-byte summary vector anywhere in Minecraft.Windows.exe 1.26.62.01; end-cursor increment writes only; whole-image fld --r scans negative; no `[base + index*stride]` element read [V] | [V negative] |
| pass+0x648 elements | 0x48 | - | - | no draining element read of the 0x48-byte light-record vector anywhere in the exe; writes are grow-emplace calls to 0x675FB30 plus index-word stores only [V] | [V negative] |
| pass+0x4A0 elements | 0x84 | - | - | no draining element read of the 0x84-byte GameplayMetadata vector anywhere in the exe; writes are end-cursor increments only [V] | [V negative] |
| pass+0x1D0 elements | 0x50 | - | - | no draining element read of the 0x50-byte ShadowAtlasFrame vector anywhere in the exe; writes are end-cursor increments only [V] | [V negative] |

## 6. Pending: description field value names — UNKNOWN [?]

| offset | size | read/store address | verbatim `0xRVA  instr` line | meaning | tag |
|---|---|---|---|---|---|
| description field value names | - | - | - | unknown [?]: release exe has no RTTI and no description member-name strings; LightDescriptions.h/LightGameDescriptions.h type every field as mValue* placeholders with static_assert offsets only; descscan2 tag cases read desc fields only [V]; live bytes confirm sizes/values only, never names [V live]; parked in MIRROR_SKIP per prior review (r2 REVIEW 24/24 [V]), not the closure gate. | [?] |

## Blocking fact

All four vectors are write-only in Minecraft.Windows.exe 1.26.62.01: only end-cursor increment / grow-emplace writes exist [V] (section 2 table); no element read of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 was found by whole-image read scans [V negative], by the rdis-walk/LEA-gap angle [V], or by the new livemem/livecap angles this unit; no end-cursor pop/decrement exists [V negative]; no 0x5ABA5C0 caller drains them [V]. Closing consumers requires a live read/write watch on pass+0x800/+0x648/+0x4A0/+0x1D0 — not available to this unit; the pending capture oc_u_er6_light_desc samples entry registers/desc bytes and reports ret= only, it cannot watch pass-vector memory, and no static pass-object address exists for livemem (0x5ABA5C0 = per-call TLS getter). Description field value names are a second open [?] for the same reason (no names in the exe or dumps); parked in MIRROR_SKIP, not the closure gate.

## CLOSES?

CLOSES? NO — single blocking fact: no draining reader/consumer of pass+0x800 (0x14-byte summary list), pass+0x648 (0x48-byte light-record vector), pass+0x4A0 (0x84-byte GameplayMetadata vector) or pass+0x1D0 (0x50-byte ShadowAtlasFrame vector) exists anywhere in Minecraft.Windows.exe 1.26.62.01 [V negative]: all four vectors are write-only statically (end-cursor increments / grow-emplace, no pop/decrement, no `[base + index*stride]` element read); every static angle (whole-image fld scans, imm/magic-multiplier scans, rdis walk, endFrame re-list, all 0x5ABA5C0 callers, descscan2, xr/callers; vt/vcalls n/a) is negative; the pending entry capture oc_u_er6_light_desc and read-only livemem cannot install a read/write watch on pass-vector memory, and no static pass-object address exists for livemem. Description field value names are also unknown [?] (no RTTI, no member-name strings; live bytes give sizes/values never names); parked in MIRROR_SKIP per prior review, not the closure gate.

## TOOL REQUESTS

CAPTURE REQUESTED oc_u_er6_light_desc — light-visitor entry capture (rva 0x6640d80 = 107220352, size 256, max 6) already pending in docs/progress/capture_requests.json (state pending; 4/4 pending slots in use, `add` rejects duplicates/new requests); result checked this unit via `python tools/livecap/request.py result oc_u_er6_light_desc` -> "no result yet (orchestrator has not run it)". What it can add [V live when it runs]: tag-3 (LightPoint) and tag-4 (ShadowAtlasFrame) description bytes at visitor entry and the caller chain via ret= — cite [V live] when available. What it cannot add: consumers of pass+0x800/+0x648/+0x4A0/+0x1D0 (no pass-memory read/write watch). What would close R6: a live read/write watchpoint on pass-vector memory or a live pass-object address plus a read trace — neither available to this unit. Helper scripts: None.
