## NEXT
DONE

# U-ER6 — R6: LightAmbient / LightDirectional / Light tag 2 / tag 3 / tag 4 (1.26.62.01)

Goal: close R6 — description field value names, the group_visitors.md vs FrameBuilder.h LightGroupTag tag-name conflict, and consumers (draining element readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0. Exe Minecraft.Windows.exe 1.26.62.01, RVAs image-relative. Static analysis only (brief rule 1). Tags: [V] seen in disassembly (RVA cited, re-verified against the exe this unit) | [V carried] proven in earlier docs/progress/oc_U-ER6_r*.md, NOT re-proven per RETRY #1 | [V negative] whole-image scan found nothing | [?] unknown. Every `0xRVA  instr` line below is copied verbatim from a verified rdis listing of the exe.

## 1. Carried [V] — tag -> type / LightGroupTag; conflict RESOLVED (not re-proven per RETRY #1)

FrameBuilder.h:79-88 `enum class LightGroupTag : uint64_t { Ambient = 0, Directional = 1, GameplayMetadata = 2, LightPoint = 3, ShadowAtlasFrame = 4, ... };` wins over group_visitors.md (which had tag 2/3 swapped and is superseded). Producer tag stores + __FUNCSIG__ srclocs prove tag 2 = GameplayMetadata and tag 3 = LightPoint; BGFX_MAP.md 6w/6ih agree after correction. Tag byte at variant+0x08 dispatches through jump table 0xF2BF2B0 (`0x6640dc4  movzx eax,byte ptr [rdx+8]`, `0x6640de6  jmp rax`).

| name | offset | size | site RVA | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| tag 2 = GameplayMetadata | variant+0x08 tag byte | 1 | 0x53e5fb4, 0x53e5fbf | `0x53e5fb4  mov byte ptr [rbp-0x18],2`<br>`0x53e5fbf  mov rax,[rax+0x380]` | LightGroupTag::GameplayMetadata = 2; Light vslot 0x380 insert; JT entry 2; srcloc 0xF248ED0 GameplayMetadata | [V carried] |
| tag 3 = LightPoint | variant+0x08 tag byte | 1 | 0x535a9b7, 0x535a9c1 | `0x535a9b7  mov byte ptr [rbp+0x278],3`<br>`0x535a9c1  mov rax,[rax+0x380]` | LightGroupTag::LightPoint = 3; JT entry 3; srcloc 0xF248DA0 LightPointDescription | [V carried] |

(Tag 0 = Ambient, tag 1 = Directional, tag 4 = ShadowAtlasFrame likewise [V carried], not re-proven per RETRY #1.)

## 2. Carried [V] — Light-visitor writers to pass+0x800 / +0x648 / +0x4A0 / +0x1D0 (write-only)

Pass-object vectors (begin/end/cap cursors): summary +0x7F8/+0x800/+0x808 stride 0x14; light records +0x648/+0x650 stride 0x48; GameplayMetadata +0x498/+0x4A0/+0x4A8 stride 0x84; ShadowAtlasFrame +0x1C8/+0x1D0/+0x1D8 stride 0x50 [V carried]. Every write is an end-cursor increment / grow-emplace; no end-cursor pop/decrement exists anywhere in the exe [V negative]. rsi = pass object = return of TLS getter 0x5ABA5C0 (`0x6640e84  mov rdx,[rsi+0x800]`, `0x6640e8b  cmp rdx,[rsi+0x808]`).

| name | offset | size | site RVA | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| pass+0x800 end cursor | 0x800 end cursor | 8 | 0x6640eb4, 0x66417a2, 0x6641517 | `0x6640eb4  add qword ptr [rsi+0x800],0x14`<br>`0x66417a2  add qword ptr [rsi+0x800],0x14`<br>`0x6641517  add qword ptr [rsi+0x800],0x14` | end cursor of 0x14-byte summary list (cap cursor +0x808 compared at 0x6640e8b); writers Ambient 0x6640eb4, Directional 0x66417a2, LightPoint 0x6641517 (all increment by 0x14) | [V carried] |
| pass+0x648 end cursor | 0x648 end cursor | 8 | 0x66416f8, 0x66416ff | `0x66416f8  lea rcx,[rsi+0x648]`<br>`0x66416ff  call 0x675FB30` | end cursor of 0x48-byte light-record vector (begin +0x648 / end +0x650); Directional passes &end to grow-emplace 0x675FB30 (LightPoint 0x6641461 likewise [V carried]) | [V carried] |
| pass+0x4A0 end cursor | 0x4A0 end cursor | 8 | 0x6640f78, 0x6640f7f, 0x6641090 | `0x6640f78  mov r12,[rdi+0x4A0]`<br>`0x6640f7f  cmp r12,[rdi+0x4A8]`<br>`0x6641090  add qword ptr [rdi+0x4A0],0x84` | end cursor of 0x84-byte GameplayMetadata vector (begin +0x498 / cap +0x4A8); tag-2 writer, stride 0x84 | [V carried] |
| pass+0x1D0 end cursor | 0x1D0 end cursor | 8 | 0x66419c6 | `0x66419c6  add qword ptr [rsi+0x1D0],0x50` | end cursor of 0x50-byte ShadowAtlasFrame vector (begin +0x1C8 / cap +0x1D8); tag-4 writer, stride 0x50 | [V carried] |

## 3. Carried [V] — description field reads (sizes confirmed; value names unknown [?])

| name | offset | size | site RVA | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| desc+0x00 (tag 4 ShadowAtlasFrame) | desc+0x00 | 16 | 0x6640ec1 | `0x6640ec1  movups xmm6,[rsi]` | row 0 copied into pass+0x1C8 vector element +0x00 | [V] |
| desc+0x10 (tag 4) | desc+0x10 | 16 | 0x6640ecb | `0x6640ecb  movups xmm7,[rsi+0x10]` | element +0x10 | [V] |
| desc+0x20 (tag 4) | desc+0x20 | 16 | 0x6640ed6 | `0x6640ed6  movups xmm8,[rsi+0x20]` | element +0x20 | [V] |
| desc+0x30 (tag 4) | desc+0x30 | 16 | 0x6640ee3 | `0x6640ee3  movups xmm9,[rsi+0x30]` | element +0x30 | [V] |
| desc+0x40 (tag 4) | desc+0x40 | 8 | 0x66418f0 | `0x66418f0  mov rbx,[rsi+0x40]` | shared_ptr object pointer at +0x40 (with +0x48 the {ptr, control block} pair) | [V] |
| desc+0x48 (tag 4) | desc+0x48 | 8 | 0x6640f01 | `0x6640f01  mov rcx,[rsi+0x48]` | control block at +0x48; non-null -> `lock inc [rcx+8]` at 0x6640f0e | [V] |

Total description bytes consumed by tag 4 = 0x50 (matches ShadowAtlasFrame stride and sizeof in Descriptions.h) [V carried]. Member value NAMES are not in the release exe (no RTTI, no description member-name strings); headers type fields as mValue* placeholders with static_assert offsets only — value names stay [?]; parked in MIRROR_SKIP per prior review (r2 REVIEW 24/24 [V]), not the closure gate.

## 4. New angle tried this unit — live capture (the only remaining tool per the ORCHESTRATOR HINT 2026-11-22)

Static analysis is exhausted for the consumer blocker: whole-image fld --r/--w on 0x800/0x648/0x4A0/0x1D0 plus begin/cap cursors; imm/magic-multiplier scans (div 0x14=0xFFFFCCCD, div 0x48=0xFFFF8E39, div 0x84=0xFFFF83E1, div 0x50=0xCCCCCCCCCCCCCCCD); rdis walk from 0x66416f8 (3020 instructions) showing only grow-emplace 0x675FB30 and cursor index math, no `[base + index*stride]` element read; endFrame 0x66232b0 re-list; all 0x5ABA5C0 callers enumerated; descscan2; xr/callers; vt/vcalls n/a; BGFX_MAP.md 6gq/6ih/6hi/6w name no consumer — all carried negatives, NOT re-run per RETRY #1.

The new live-capture tool was checked:
- `python tools/livecap/request.py result oc_u_er6_light_desc` -> "no result yet (orchestrator has not run it)"; no docs/data/live/oc_u_er6_light_desc.txt exists.
- `python tools/livecap/request.py add oc_u_er6_light_desc 0x6640D80 --size 0x100 --max 6 --why "R6: ..."` -> "already queued" (exit 1): the light-visitor entry capture (rva 0x6640D80, size 0x100, max 6) is ALREADY PENDING in docs/progress/capture_requests.json; 4/4 pending slots are in use (er5_clone_4c8a5b0, l8b_resizetex_slot31, sub_1289440_callers, oc_u_er6_light_desc), so `add` rejects duplicates and new requests — no replacement or additional capture can be queued this unit.
- livemem: read-only (VM_READ), no breakpoints/watchpoints; no static pass-object address exists (0x5ABA5C0 = per-call TLS thread-local getter; the pass object is the node value at node+0x10, only reachable at runtime), so livemem cannot trace WHICH CODE reads pass-vector elements.

What the pending capture CAN add [V live when it runs]: tag-3 (LightPoint) and tag-4 (ShadowAtlasFrame) description bytes at visitor entry and the caller chain via ret= (visitor caller = wrapper 0x6640ae0, FrameBuilder slot 0x380 "FrameBuilder - Insert light"). What it CANNOT add: consumers of pass+0x800/+0x648/+0x4A0/+0x1D0 — function-entry sampling only, no read/write watch on pass-vector memory.

## 5. Pending: consumers (draining element readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — NOT LOCATED

| name | offset | size | site RVA | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| pass+0x800 elements | pass+0x800 elements | 0x14 | - | - | no draining element read of the 0x14-byte summary vector anywhere in Minecraft.Windows.exe 1.26.62.01; end-cursor increment writes only; whole-image fld --r scans negative; no `[base + index*stride]` element read | [V negative] |
| pass+0x648 elements | pass+0x648 elements | 0x48 | - | - | no draining element read of the 0x48-byte light-record vector anywhere in the exe; writes are grow-emplace calls to 0x675FB30 plus index-word stores only | [V negative] |
| pass+0x4A0 elements | pass+0x4A0 elements | 0x84 | - | - | no draining element read of the 0x84-byte GameplayMetadata vector anywhere in the exe; writes are end-cursor increments only | [V negative] |
| pass+0x1D0 elements | pass+0x1D0 elements | 0x50 | - | - | no draining element read of the 0x50-byte ShadowAtlasFrame vector anywhere in the exe; writes are end-cursor increments only | [V negative] |

## Blocking fact

All four vectors are write-only in Minecraft.Windows.exe 1.26.62.01: only end-cursor increment / grow-emplace writes exist [V] (section 2); no element read of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 was found anywhere in the exe [V negative]; no end-cursor pop/decrement exists [V negative]; no 0x5ABA5C0 caller drains them [V]. The pending entry capture oc_u_er6_light_desc and read-only livemem cannot install a read/write watch on pass-vector memory, and no static pass-object address exists for livemem (0x5ABA5C0 = per-call TLS getter). Description field value names are a second open [?] for the same reason (no names in the exe); parked in MIRROR_SKIP, not the closure gate.

## CLOSES?

CLOSES? NO — single blocking fact: no draining reader/consumer of pass+0x800 (0x14-byte summary list), pass+0x648 (0x48-byte light-record vector), pass+0x4A0 (0x84-byte GameplayMetadata vector) or pass+0x1D0 (0x50-byte ShadowAtlasFrame vector) exists anywhere in Minecraft.Windows.exe 1.26.62.01 [V negative]: all four vectors are write-only statically (end-cursor increments / grow-emplace, no pop/decrement, no `[base + index*stride]` element read); every static angle (whole-image fld scans, imm/magic-multiplier scans, rdis walk, endFrame re-list, all 0x5ABA5C0 callers, descscan2, xr/callers; vt/vcalls n/a) is negative; BGFX_MAP.md 6gq/6ih/6hi/6w name no consumer; the pending entry capture oc_u_er6_light_desc and read-only livemem cannot install a read/write watch on pass-vector memory, and no static pass-object address exists for livemem (0x5ABA5C0 = per-call TLS getter). Description field value names are also unknown [?] (no RTTI, no member-name strings; live bytes give sizes/values never names); parked in MIRROR_SKIP per prior review, not the closure gate.

## TOOL REQUESTS

CAPTURE REQUESTED oc_u_er6_light_desc — light-visitor entry capture (rva 0x6640D80 = 107220352, size 0x100, max 6) already pending in docs/progress/capture_requests.json (state pending; `add` rejected "already queued", 4/4 pending slots in use); result awaited via `python tools/livecap/request.py result oc_u_er6_light_desc` ("no result yet"). What it can add [V live when it runs]: tag-3/tag-4 description bytes at visitor entry and caller chain via ret=. What it cannot add: consumers of pass+0x800/+0x648/+0x4A0/+0x1D0 (no pass-memory read/write watch). What would close R6: a live read/write watchpoint on pass-vector memory or a live pass-object address plus a read trace — neither available to this unit. Helper scripts: None.
