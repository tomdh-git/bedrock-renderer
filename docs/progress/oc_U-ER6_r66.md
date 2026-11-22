## NEXT
DONE

# U-ER6 — R6: LightAmbient / LightDirectional / Light tag 2 / tag 3 / tag 4 (1.26.62.01)

Goal: close R6 — description field value names, the group_visitors.md vs FrameBuilder.h LightGroupTag tag-name conflict, and the consumers (draining element readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0. Exe Minecraft.Windows.exe 1.26.62.01, RVAs image-relative, static analysis only (brief rule 1). Tags: [V] seen in disassembly (RVA cited) | [V carried] proven in earlier docs/progress/oc_U-ER6_r*.md, NOT re-proven per RETRY #1 | [V negative] whole-image scan found nothing | [?] unknown. Proof lines copied verbatim from verified rdis listings (docs/functions/6640d80_light_visitor.md verify_oc 112/112; docs/functions/light_game_descriptions.md verify_oc 869/869; producer lines re-checked with rdis in r62-r65).

Input data (read fully, not re-generated): docs/functions/6640d80_light_visitor.md; docs/functions/light_game_descriptions.md; docs/functions/5aba5c0.md; docs/functions/group_visitors.md; docs/data/live/light_visitor.txt; docs/data/live/README.md; docs/data/live/_status.txt; docs/progress/capture_requests.json; docs/progress/oc_verification.md (U-PASS .. U-PASS5); src/sdk/mc/deps/minecraft_renderer/framebuilder/FrameBuilder.h (LightGroupTag enum); docs/BGFX_MAP.md sections 6w, 6em, 6iq/6is.

## 1. Tag -> type / LightGroupTag; conflict RESOLVED [V carried]

FrameBuilder.h:79-88 `enum class LightGroupTag : uint64_t { Ambient = 0, Directional = 1, GameplayMetadata = 2, LightPoint = 3, ShadowAtlasFrame = 4, ServerGraphicsOverrideParameters = 5, VoxelVolume = 6, TransitioningVoxelVolume = 7 };` wins over group_visitors.md (which had tag 2/3 swapped; superseded). Jump table 0xF2BF2B0 parsed from the PE (8 entries: 0=0x6640de8, 1=0x66415b0, 2=0x6640f1b, 3=0x66410a0, 4=0x6640ec1, 5=0x66417af, 6=0x664187d, 7=0x6641524); BGFX_MAP.md 6w/6em/6iq/6is agree (Light: 2 GameplayMetadata, 3 LightPoint, 4 ShadowAtlasFrame, 5 ServerGraphicsOverrideParameters, 6 VoxelVolume, 7 TransitioningVoxelVolume) and name no light-vector consumer. Producer tag stores + __FUNCSIG__ srclocs prove tag 2 = GameplayMetadata and tag 3 = LightPoint.

| offset | size | site RVA | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| variant+0x08 tag byte dispatch | 1 | 0x6640dc4, 0x6640de6 | `0x6640dc4  movzx eax,byte ptr [rdx+8]`<br>`0x6640de6  jmp rax` | tag byte at variant+0x08 dispatched through JT 0xF2BF2B0; rsi = description, rdi = frame context, pass = result of TLS getter 0x5ABA5C0 (`mov ecx,0x9D0; add rcx,[rdi+0x10]; call 0x5ABA5C0; mov rsi,rax`) | [V carried] |
| tag 0 = Ambient | 1 | 0x53e3511 | `0x53e3511  mov byte ptr [rbp+0x138],0` | LightGroupTag::Ambient = 0; JT entry 0 = 0x6640de8; srcloc 0xF248E70 LightAmbientDescription | [V carried] |
| tag 1 = Directional | 1 | 0x53709d4 | `0x53709d4  mov byte ptr [rbp+0x18],1` | LightGroupTag::Directional = 1; JT entry 1 = 0x66415b0; srcloc 0xF248F70 LightDirectionalDescription | [V carried] |
| tag 2 = GameplayMetadata | 1 | 0x53e5fb4, 0x53e5fbf | `0x53e5fb4  mov byte ptr [rbp-0x18],2`<br>`0x53e5fbf  mov rax,[rax+0x380]` | LightGroupTag::GameplayMetadata = 2; Light vslot 0x380 insert; JT entry 2 = 0x6640f1b; srcloc 0xF248ED0 GameplayMetadata | [V carried] |
| tag 3 = LightPoint | 1 | 0x535a9b7, 0x535a9c1 | `0x535a9b7  mov byte ptr [rbp+0x278],3`<br>`0x535a9c1  mov rax,[rax+0x380]` | LightGroupTag::LightPoint = 3; JT entry 3 = 0x66410a0; srcloc 0xF248DA0 LightPointDescription | [V carried] |
| tag 4 = ShadowAtlasFrame | 1 | 0x535a696, 0x535a6a0 | `0x535a696  mov byte ptr [rbp+0x278],4`<br>`0x535a6a0  mov rax,[rax+0x380]` | LightGroupTag::ShadowAtlasFrame = 4; JT entry 4 = 0x6640ec1; srcloc 0xF248D80 ShadowAtlasFrameDescription | [V carried] |
| tag-name conflict (group_visitors.md vs FrameBuilder.h) | - | FrameBuilder.h:79-88 | - | RESOLVED [V carried]: producer tag stores + __FUNCSIG__ srclocs prove tag 2 = GameplayMetadata and tag 3 = LightPoint; FrameBuilder.h wins; group_visitors.md had them swapped (LightPoint@2 / GameplayMetadata@3) and is superseded; BGFX_MAP.md 6w/6em/6iq/6is agree after correction and name no light-vector consumer | [V carried] |
| tag 5 / 6 / 7 | - | - | - | ServerGraphicsOverrideParameters = 5 (JT entry 5 = 0x66417af), VoxelVolume = 6 (0x664187d), TransitioningVoxelVolume = 7 (0x6641524) | [V carried] |

## 2. Light-visitor writers to pass+0x800 / +0x648 / +0x4A0 / +0x1D0 [V carried] (write-only only)

Pass object rsi = return of TLS getter 0x5ABA5C0 (`mov ecx,0x9D0; add rcx,[rdi+0x10]; call 0x5ABA5C0; mov rsi,rax`, docs/functions/6640d80_light_visitor.md section 1). Pass-vector layout (begin/end/cap) from docs/functions/light_game_descriptions.md section 5: summary +0x7F8/+0x800/+0x808 stride 0x14 (tags 0/1/3); light records +0x648/+0x650 stride 0x48 (tags 1/3); GameplayMetadata +0x498/+0x4A0/+0x4A8 stride 0x84 (tag 2); ShadowAtlasFrame +0x1C8/+0x1D0/+0x1D8 stride 0x50 (tag 4). Every case also appends one 0xC8 DrawItem record to pass+0x08/+0x10. Every write below is an end-cursor increment / grow-emplace; no end-cursor pop/decrement exists anywhere in the exe [V negative].

| offset | size | site RVA | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| pass+0x800 end cursor | 8 | 0x6640e84, 0x6640e8b, 0x6640eb4, 0x66417a2, 0x6641517 | `0x6640e84  mov rdx,[rsi+0x800]`<br>`0x6640e8b  cmp rdx,[rsi+0x808]`<br>`0x6640eb4  add qword ptr [rsi+0x800],0x14` | end cursor of 0x14-byte summary list (cap +0x808 compared at 0x6640e8b); identical `add qword ptr [rsi+0x800],0x14` cursor increments at 0x66417a2 (Directional) and 0x6641517 (LightPoint) | [V carried] |
| pass+0x648 end cursor | 8 | 0x66416f8, 0x66416ff | `0x66416f8  lea rcx,[rsi+0x648]`<br>`0x66416ff  call 0x675FB30` | end cursor of 0x48-byte light-record vector (begin +0x648 / end +0x650); &end passed to grow-emplace 0x675FB30 (Directional 0x66416ff, LightPoint 0x6641461 [V carried]) | [V carried] |
| pass+0x4A0 end cursor | 8 | 0x6640f78, 0x6640f7f, 0x6641090 | `0x6640f78  mov r12,[rdi+0x4A0]`<br>`0x6640f7f  cmp r12,[rdi+0x4A8]`<br>`0x6641090  add qword ptr [rdi+0x4A0],0x84` | end cursor of 0x84-byte GameplayMetadata vector (begin +0x498 / cap +0x4A8); tag-2 writer, stride 0x84; load at 0x6640f78, cap compare at 0x6640f7f | [V carried] |
| pass+0x1D0 end cursor | 8 | 0x66419c6 | `0x66419c6  add qword ptr [rsi+0x1D0],0x50` | end cursor of 0x50-byte ShadowAtlasFrame vector (begin +0x1C8 / cap +0x1D8); tag-4 writer, stride 0x50 | [V carried] |

## 3. Consumers of pass+0x800 / +0x648 / +0x4A0 / +0x1D0: NOT LOCATED [V negative]

| offset | size | site RVA | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| pass+0x800 elements | 0x14 | - | - | no draining element read of the 0x14-byte summary vector anywhere in Minecraft.Windows.exe 1.26.62.01; end-cursor increment writes only; whole-image fld --r/--w scans on 0x800 and cursors +0x7F8/+0x808 negative; stride scan ÷0x14 = 0xFFFFCCCD negative; no `[base + index*stride]` element read | [V negative] |
| pass+0x648 elements | 0x48 | - | - | no draining element read of the 0x48-byte light-record vector anywhere in the exe; writes are grow-emplace calls to 0x675FB30 plus index-word stores only; stride scan ÷0x48 = 0xFFFF8E39 negative | [V negative] |
| pass+0x4A0 elements | 0x84 | - | - | no draining element read of the 0x84-byte GameplayMetadata vector anywhere in the exe; writes are end-cursor increments only; stride scan ÷0x84 = 0xFFFF83E1 negative | [V negative] |
| pass+0x1D0 elements | 0x50 | - | - | no draining element read of the 0x50-byte ShadowAtlasFrame vector anywhere in the exe; writes are end-cursor increments only; stride scan ÷0x50 = 0xCCCCCCCCCCCCCCCD negative | [V negative] |

## 4. Description field reads (tag 4 ShadowAtlasFrame): sizes confirmed [V], value names unknown [?]

| offset | size | site RVA | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| desc+0x00 | 16 | 0x6640ec1 | `0x6640ec1  movups xmm6,[rsi]` | row 0 copied into pass+0x1C8 vector element +0x00; rsi = description (visitor entry arg in RDX per docs/data/live/README.md correction 2026-11-15) | [V] |
| desc+0x10 | 16 | 0x6640ecb | `0x6640ecb  movups xmm7,[rsi+0x10]` | element +0x10 | [V] |
| desc+0x20 | 16 | 0x6640ed6 | `0x6640ed6  movups xmm8,[rsi+0x20]` | element +0x20 | [V] |
| desc+0x30 | 16 | 0x6640ee3 | `0x6640ee3  movups xmm9,[rsi+0x30]` | element +0x30 | [V] |
| desc+0x40 | 8 | 0x66418f0 | `0x66418f0  mov rbx,[rsi+0x40]` | shared_ptr object pointer at +0x40 (with +0x48 the {ptr, control block} pair) | [V] |
| desc+0x48 | 8 | 0x6640f01 | `0x6640f01  mov rcx,[rsi+0x48]` | control block at +0x48; non-null -> use count `lock inc [rcx+8]` at 0x6640f0e | [V] |

Total description bytes consumed by tag 4 = 0x50 (matches ShadowAtlasFrame stride and sizeof in Descriptions.h) [V carried]. Member value NAMES unknown [?]: no RTTI and no description member-name strings in the release exe; LightDescriptions.h/LightGameDescriptions.h use mValue* placeholders with static_assert offsets only; live bytes (docs/data/live/light_visitor.txt, tags 0/1/2/5 — tags 3 and 4 absent) confirm sizes/values, never names; parked in MIRROR_SKIP per prior review (r2 REVIEW 24/24 [V]), not the closure gate.

## 5. What this unit tried (new angle per ORCHESTRATOR HINT 2026-11-22)

- `python tools/livecap/request.py result oc_u_er6_light_desc` -> "no result yet (orchestrator has not run it)"; no docs/data/live/oc_u_er6_light_desc.txt exists; docs/data/live/_status.txt lists no oc_u_er6_light_desc result.
- `python tools/livecap/request.py add oc_u_er6_light_desc 0x6640D80 --size 0x100 --max 6` -> "already queued" (exit 1): capture oc_u_er6_light_desc is ALREADY QUEUED (state pending) at rva 0x6640D80 (light-visitor entry, RDX = desc pointer), size 256, max 6 in docs/progress/capture_requests.json; 4/4 pending slots are in use (er5_clone_4c8a5b0, l8b_resizetex_slot31, sub_1289440_callers, oc_u_er6_light_desc), so `add` rejects duplicates and new requests — no replacement or additional capture can be queued this unit.
- What the pending capture CAN add [V live when it runs]: tag-3 (LightPoint) and tag-4 (ShadowAtlasFrame) description bytes at visitor entry and the caller chain via ret= (visitor called through FrameBuilder vslot 0x380 / wrapper 0x6640ae0). What it CANNOT add: consumers of pass+0x800/+0x648/+0x4A0/+0x1D0 — function-entry sampling only, producer-side, no read/write watch on pass-vector memory.
- livemem: game is running (pid 13452, base 0x7ff7a59c0000, version OK) but livemem is VM_READ-only with no breakpoints/watchpoints (brief rule 1) and needs a static address; the pass object is per-thread TLS heap (0x5ABA5C0 = ThreadLocalObject::get returning node+0x10, docs/functions/5aba5c0.md; no data refs to the getter, no static pass-object address) -> livemem cannot read pass-vector contents and cannot trace WHICH CODE reads pass-vector elements. Ruled out for this item.
- Static angles are exhausted and were NOT re-run per RETRY #1: whole-image fld --r/--w on 0x800/0x648/0x4A0/0x1D0 plus begin/cap cursors (+0x7F8/+0x808, +0x648/+0x650, +0x498/+0x4A8, +0x1C8/+0x1D8); stride magic-multiplier scans (÷0x14=0xFFFFCCCD, ÷0x48=0xFFFF8E39, ÷0x84=0xFFFF83E1, ÷0x50=0xCCCCCCCCCCCCCCCD); rdis walk from 0x66416f8 (3020 instructions: only grow-emplace 0x675FB30 and cursor index math, no element read); endFrame 0x66232b0 re-list; all 0x5ABA5C0 callers enumerated (11: 0x5ab8e20, 0x66232b0 endFrame, 0x6640d80 light visitor, 0x6646980 item visitor, 0x66560f0 sky visitor, 0x6664a00 UI visitor, 0x666aca0 effect visitor, 0x66742f0 editor visitor, 0x66a6830, 0x66a9d50, 0x66ade80, 0x66bb7b0 — none drains); descscan2 tag cases read description fields only; xr/callers of visitor 0x6640d80 = 0; vt/vcalls n/a; xref str "LightAmbient"/"ShadowAtlasFrame"/"LightPoint" -> only __FUNCSIG__ srcloc records; BGFX_MAP.md 6w/6em/6iq/6is name no light-vector consumer; U-PASS3/U-PASS4B/U-PASS5 located the 0xC8 DrawItem-record consumer (0x6765020/0x6768c70 appending to pass+0x08/+0x10 via grow 0x5aba6d0), not the light vectors. No rdis angle remains.

## Blocking fact / CLOSES?

CLOSES? NO — single blocking fact: no draining reader/consumer of pass+0x800 (0x14-byte summary list), pass+0x648 (0x48-byte light-record vector), pass+0x4A0 (0x84-byte GameplayMetadata vector) or pass+0x1D0 (0x50-byte ShadowAtlasFrame vector) exists anywhere in Minecraft.Windows.exe 1.26.62.01 — all four vectors are write-only statically (end-cursor increments / grow-emplace only; no pop/decrement; no element read anywhere in the exe [V negative]); every static angle is negative (section 5); the queued entry capture oc_u_er6_light_desc cannot install a read/write watch on pass-vector memory and read-only livemem has no static pass-object address (0x5ABA5C0 = per-thread TLS getter); the capture result itself is not yet available ("no result yet"). Description field value names are also unknown [?] (no RTTI, no member-name strings; live bytes give sizes/values never names); parked in MIRROR_SKIP per prior review, not the closure gate.

## TOOL REQUESTS

CAPTURE REQUESTED oc_u_er6_light_desc — light-visitor entry capture (rva 0x6640D80 = 107220352, size 256, max 6) already pending in docs/progress/capture_requests.json; `add` rejected duplicates/new requests (4/4 pending slots in use); result awaited via `python tools/livecap/request.py result oc_u_er6_light_desc` ("no result yet"). What it can add [V live when it runs]: tag-3/tag-4 description bytes at visitor entry and caller chain via ret=. What it cannot add: consumers of pass+0x800/+0x648/+0x4A0/+0x1D0 (no pass-memory read/write watch). What would close R6: a live read/write watchpoint on pass-vector memory or a live pass-object address plus a read trace — neither available to this unit (livemem read-only, no watchpoints; 0x5ABA5C0 per-thread TLS, no static address). Helper scripts: None.
