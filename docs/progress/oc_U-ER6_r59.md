## NEXT
DONE

# U-ER6 — R6: LightAmbient / LightDirectional / Light tag 2 / tag 3 / tag 4 (1.26.62.01)

Goal: close R6 — description field value names, the group_visitors.md vs FrameBuilder.h LightGroupTag tag-name conflict, and consumers (draining element readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0. Exe Minecraft.Windows.exe 1.26.62.01, RVAs image-relative. Static analysis only (brief rule 1). Tags: [V] seen in disassembly (RVA cited, re-verified against the exe this unit) | [V carried] proven in earlier docs/progress/oc_U-ER6_r*.md notes and NOT re-proven per RETRY #1 | [V negative] whole-image scan found nothing | [V live] live capture bytes (docs/data/live/*.txt) | [I] inferred | [?] unknown. Every `0xRVA  instr` line is copied verbatim from a verified rdis listing of the exe.

Input data (read fully, not re-generated): docs/functions/6640d80_light_visitor.md; docs/functions/5aba5c0.md; docs/functions/group_visitors.md (superseded on tags 2/3); docs/functions/light_game_descriptions.md; docs/data/live/light_visitor.txt; docs/data/live/README.md; docs/data/live/_status.txt; docs/BGFX_MAP.md sections 6gq/6ih/6hi/6w; FrameBuilder.h LightGroupTag enum; Descriptions.h/LightDescriptions.h/LightGameDescriptions.h. Capture oc_u_er6_light_desc (rva 0x6640D80, size 0x100, max 6) state pending in docs/progress/capture_requests.json; `python tools/livecap/request.py result oc_u_er6_light_desc` -> "no result yet (orchestrator has not run it)"; no docs/data/live/oc_u_er6_light_desc.txt exists. Pre-existing live_visitor.txt (visitor kind, `tag descptr hex` lines, no REG=/ret= lines) confirms tag 0/1/2 field sizes only; no tag 3/4 samples.

## 1. Carried [V] — tag -> type / LightGroupTag; conflict RESOLVED (not re-proven per RETRY #1)

| offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| variant+0x08 tag byte | 1 | 0x6640dc4, 0x6640de6 | `0x6640dc4  movzx eax,byte ptr [rdx+8]`<br>`0x6640de6  jmp rax` | tag byte at variant+0x08; `jmp rax` dispatches through jump table 0xF2BF2B0 (entries 0=0x6640de8, 1=0x66415b0, 2=0x6640f1b, 3=0x66410a0, 4=0x6640ec1, 5=0x66417af, 6=0x664187d, 7=0x6641524) | [V carried] |
| tag 0 = Ambient | 1 | 0x53e3511 | `0x53e3511  mov byte ptr [rbp+0x138],0` | LightGroupTag::Ambient = 0 (FrameBuilder.h:79-88); JT entry 0; srcloc 0xF248E70 RenderLightAmbientDescription | [V carried] |
| tag 1 = Directional | 1 | 0x53709d4 | `0x53709d4  mov byte ptr [rbp+0x18],1` | LightGroupTag::Directional = 1; JT entry 1; srcloc 0xF248F70 LightDirectionalDescription | [V carried] |
| tag 2 = GameplayMetadata | 1 | 0x53e5fb4, 0x53e5fbf | `0x53e5fb4  mov byte ptr [rbp-0x18],2`<br>`0x53e5fbf  mov rax,[rax+0x380]` | LightGroupTag::GameplayMetadata = 2; Light vslot 0x380 insert; JT entry 2; srcloc 0xF248ED0 GameplayMetadata | [V carried] |
| tag 3 = LightPoint | 1 | 0x535a9b7, 0x535a9c1 | `0x535a9b7  mov byte ptr [rbp+0x278],3`<br>`0x535a9c1  mov rax,[rax+0x380]` | LightGroupTag::LightPoint = 3; JT entry 3; srcloc 0xF248DA0 LightPointDescription | [V carried] |
| tag 4 = ShadowAtlasFrame | 1 | 0x535a696, 0x535a6a0 | `0x535a696  mov byte ptr [rbp+0x278],4`<br>`0x535a6a0  mov rax,[rax+0x380]` | LightGroupTag::ShadowAtlasFrame = 4; JT entry 4; srcloc 0xF248D80 ShadowAtlasFrameDescription | [V carried] |
| tag-name conflict | - | FrameBuilder.h:79-88 | - | RESOLVED [V carried]: producer tag stores + __FUNCSIG__ srclocs prove tag 2 = GameplayMetadata and tag 3 = LightPoint; FrameBuilder.h wins; group_visitors.md had them swapped (LightPoint@2 / GameplayMetadata@3) and is superseded; BGFX_MAP.md 6w/6ih agree after correction | [V carried] |

## 2. Carried [V] — Light-visitor writers to pass+0x800 / +0x648 / +0x4A0 / +0x1D0 (write-only)

Pass-object vectors (begin/end/cap cursors): summary +0x7F8/+0x800/+0x808 stride 0x14; light records +0x648/+0x650 stride 0x48; GameplayMetadata +0x498/+0x4A0/+0x4A8 stride 0x84; ShadowAtlasFrame +0x1C8/+0x1D0/+0x1D8 stride 0x50 [V carried]. Every write below is an end-cursor increment / grow-emplace; no end-cursor pop/decrement exists anywhere in the exe [V negative, whole-image fld --w]. rsi = pass object = return of TLS getter 0x5ABA5C0 (rdis annotation `ret@5aba5c0+0x800`).

| offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| pass+0x800 end cursor | 8 | 0x6640e84, 0x6640e8b, 0x6640eb4, 0x66417a2, 0x6641517 | `0x6640e84  mov rdx,[rsi+0x800]`<br>`0x6640e8b  cmp rdx,[rsi+0x808]`<br>`0x6640eb4  add qword ptr [rsi+0x800],0x14`<br>`0x66417a2  add qword ptr [rsi+0x800],0x14`<br>`0x6641517  add qword ptr [rsi+0x800],0x14` | end cursor of the 0x14-byte summary list (cap cursor +0x808 compared at 0x6640e8b); writers: Ambient 0x6640eb4, Directional 0x66417a2, LightPoint 0x6641517 (all increment by 0x14) | [V carried] |
| pass+0x648 end cursor | 8 | 0x66416f8, 0x66416ff, 0x664145a, 0x6641461 | `0x66416f8  lea rcx,[rsi+0x648]`<br>`0x66416ff  call 0x675FB30`<br>`0x664145a  lea rcx,[rsi+0x648]`<br>`0x6641461  call 0x675FB30` | end cursor of the 0x48-byte light-record vector (begin +0x648 / end +0x650); Directional 0x66416ff and LightPoint 0x6641461 pass &end to grow-emplace 0x675FB30 | [V carried] |
| pass+0x4A0 end cursor | 8 | 0x6640f78, 0x6640f7f, 0x6641090 | `0x6640f78  mov r12,[rdi+0x4A0]`<br>`0x6640f7f  cmp r12,[rdi+0x4A8]`<br>`0x6641090  add qword ptr [rdi+0x4A0],0x84` | end cursor of the 0x84-byte GameplayMetadata vector (begin +0x498 / cap +0x4A8); tag-2 writer, stride 0x84; load 0x6640f78, cap compare 0x6640f7f | [V carried] |
| pass+0x1D0 end cursor | 8 | 0x66419c6 | `0x66419c6  add qword ptr [rsi+0x1D0],0x50` | end cursor of the 0x50-byte ShadowAtlasFrame vector (begin +0x1C8 / cap +0x1D8); tag-4 writer, stride 0x50 | [V carried] |

## 3. Carried [V] — description field reads (sizes confirmed; names unknown)

| offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| desc+0x00 (tag 4) | 16 | 0x6640ec1 | `0x6640ec1  movups xmm6,[rsi]` | ShadowAtlasFrame description row 0 copied into pass+0x1C8 vector element +0x00; rsi = description pointer (visitor entry arg in RDX per docs/data/live/README.md CORRECTION 2026-11-15) | [V carried] |
| desc+0x10 (tag 4) | 16 | 0x6640ecb | `0x6640ecb  movups xmm7,[rsi+0x10]` | element +0x10 | [V carried] |
| desc+0x20 (tag 4) | 16 | 0x6640ed6 | `0x6640ed6  movups xmm8,[rsi+0x20]` | element +0x20 | [V carried] |
| desc+0x30 (tag 4) | 16 | 0x6640ee3 | `0x6640ee3  movups xmm9,[rsi+0x30]` | element +0x30 | [V carried] |
| desc+0x40 (tag 4) | 8 | 0x66418f0 | `0x66418f0  mov rbx,[rsi+0x40]` | shared_ptr object pointer at +0x40 (with +0x48 the {ptr, control block} pair); non-null ctrl use-count `lock inc [rcx+8]` at 0x6640f0e | [V carried] |
| desc+0x48 (tag 4) | 8 | 0x6640f01 | `0x6640f01  mov rcx,[rsi+0x48]` | control block at +0x48 | [V carried] |
| desc+0x00..+0x84 (tag 2) | - | 0x6640f1b | - | descscan2 tag-2 case 0x6640f1b reads desc+0x00..+0x84 only, no pass offset [V carried] | [V carried] |

Total description bytes consumed by tag 4 = 0x50 (matches ShadowAtlasFrame stride and sizeof in Descriptions.h) [V carried]. Member value names are not in the release exe (no RTTI, no description member-name strings); headers type fields as mValue* placeholders with static_assert offsets only — value NAMES stay [?].

## 4. Live capture status (this unit)

- `python tools/livecap/request.py result oc_u_er6_light_desc` -> "no result yet (orchestrator has not run it)"; no docs/data/live/oc_u_er6_light_desc.txt exists. Capture oc_u_er6_light_desc (rva 0x6640D80 = light-visitor entry, RDX = desc pointer, size 256, max 6) state pending in docs/progress/capture_requests.json.
- 4/4 pending slots are in use (er5_clone_4c8a5b0, l8b_resizetex_slot31, sub_1289440_callers, oc_u_er6_light_desc); `add` rejects duplicates and rejects new requests when 4 are pending, so no replacement or additional capture can be queued this unit.
- What the pending capture CAN add [V live when it runs]: tag-3 (LightPoint, 0x108 B) and tag-4 (ShadowAtlasFrame, 0x50 B) description bytes at visitor entry (confirming field sizes/runtime values vs Descriptions.h layouts) and the caller chain via ret= (visitor caller = wrapper 0x6640ae0, FrameBuilder slot 0x380 "FrameBuilder - Insert light").
- What it CANNOT add: consumers of pass+0x800/+0x648/+0x4A0/+0x1D0 — function-entry sampling only, no read/write watch on pass-vector memory; and no static pass-object address exists for livemem (0x5ABA5C0 = per-call TLS thread-local getter; rdis imm/ptr/xr to 0x5aba5c0 = 0 refs/slots [V carried]).

## 5. BGFX_MAP.md sections 6gq/6ih/6hi/6w re-read (this unit)

- 6gq: passLookup/0x5ABA5C0 = thread-local getter [V]; no consumer of the four light pass vectors named.
- 6ih: Light tag reads typed (tag 0/1/2/3/4/5 desc layouts; tag 2 = GameplayMetadata, tag 3 = LightPoint, tag 4 = ShadowAtlasFrame); queue destinations are the four pass vectors; the consumers (lighting/environment passes) are not located [V carried].
- 6hi: per-frame pending-job merge; no light-vector consumer named.
- 6w: variant tag of every insert clone — Light (0x380): 0 Ambient, 1 Directional, 2 GameplayMetadata, 5 ServerGraphicsOverrideParameters; agrees with FrameBuilder.h [V carried].

All sections name no consumer of pass+0x800/+0x648/+0x4A0/+0x1D0; carried negatives stand, not re-run per RETRY #1.

## 6. Pending: consumers (draining element readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — NOT LOCATED

| offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| pass+0x800 elements | 0x14 | - | - | no draining element read of the 0x14-byte summary vector anywhere in Minecraft.Windows.exe 1.26.62.01; end-cursor increment writes only; whole-image fld --r scans negative; no `[base + index*stride]` element read | [V negative] |
| pass+0x648 elements | 0x48 | - | - | no draining element read of the 0x48-byte light-record vector anywhere in the exe; writes are grow-emplace calls to 0x675FB30 plus index-word stores only | [V negative] |
| pass+0x4A0 elements | 0x84 | - | - | no draining element read of the 0x84-byte GameplayMetadata vector anywhere in the exe; writes are end-cursor increments only | [V negative] |
| pass+0x1D0 elements | 0x50 | - | - | no draining element read of the 0x50-byte ShadowAtlasFrame vector anywhere in the exe; writes are end-cursor increments only | [V negative] |

## 7. Pending: description field value names — UNKNOWN [?]

| offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| description field value names | - | - | - | unknown [?]: release exe has no RTTI and no description member-name strings; LightDescriptions.h/LightGameDescriptions.h type every field as mValue* placeholders with static_assert offsets only; live bytes confirm sizes/values only, never names; parked in MIRROR_SKIP per prior review (r2 REVIEW 24/24 [V]), not the closure gate. | [?] |

## Blocking fact

All four vectors are write-only in Minecraft.Windows.exe 1.26.62.01: only end-cursor increment / grow-emplace writes exist [V] (section 2 table); no element read of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 was found by whole-image read scans [V negative], by the rdis-walk/LEA-gap angle [V carried], by descscan2 [V carried], by the BGFX_MAP.md 6gq/6ih/6hi/6w re-read this unit, or by livemem/livecap (entry sampling cannot trace pass-vector reads; no static pass-object address for livemem) [V carried]. No end-cursor pop/decrement exists [V negative]; no 0x5ABA5C0 caller drains them [V carried]. Closing consumers requires a live read/write watch on pass+0x800/+0x648/+0x4A0/+0x1D0 — not available to this unit; the pending capture oc_u_er6_light_desc samples entry registers/desc bytes and reports ret= only. Description field value names are a second open [?] for the same reason (no names in the exe or dumps); parked in MIRROR_SKIP, not the closure gate.

## CLOSES?

CLOSES? NO — single blocking fact: no draining reader/consumer of pass+0x800 (0x14-byte summary list), pass+0x648 (0x48-byte light-record vector), pass+0x4A0 (0x84-byte GameplayMetadata vector) or pass+0x1D0 (0x50-byte ShadowAtlasFrame vector) exists anywhere in Minecraft.Windows.exe 1.26.62.01 [V negative]: all four vectors are write-only statically (end-cursor increments / grow-emplace, no pop/decrement, no `[base + index*stride]` element read); every static angle (whole-image fld scans, imm/magic-multiplier scans, rdis walk, endFrame re-list, all 0x5ABA5C0 callers, descscan2, xr/callers; vt/vcalls n/a) is negative; BGFX_MAP.md 6gq/6ih/6hi/6w name no consumer; the pending entry capture oc_u_er6_light_desc and read-only livemem cannot install a read/write watch on pass-vector memory, and no static pass-object address exists for livemem (0x5ABA5C0 = per-call TLS getter). Description field value names are also unknown [?] (no RTTI, no member-name strings; live bytes give sizes/values never names); parked in MIRROR_SKIP per prior review, not the closure gate.

## TOOL REQUESTS

CAPTURE REQUESTED oc_u_er6_light_desc — light-visitor entry capture (rva 0x6640D80 = 107220352, size 256, max 6) already pending in docs/progress/capture_requests.json (state pending; 4/4 pending slots in use, `add` rejects duplicates/new requests); result checked this unit via `python tools/livecap/request.py result oc_u_er6_light_desc` -> "no result yet (orchestrator has not run it)". What it can add [V live when it runs]: tag-3 (LightPoint) and tag-4 (ShadowAtlasFrame) description bytes at visitor entry and the caller chain via ret= — cite [V live] when available. What it cannot add: consumers of pass+0x800/+0x648/+0x4A0/+0x1D0 (no pass-memory read/write watch). What would close R6: a live read/write watchpoint on pass-vector memory or a live pass-object address plus a read trace — neither available to this unit. Helper scripts: None.
