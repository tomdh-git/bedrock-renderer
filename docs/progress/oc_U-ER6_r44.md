## NEXT
DONE

# U-ER6 — R6: LightAmbient / LightDirectional / Light tag 2 / tag 3 / tag 4 (1.26.62.01)

Goal: close R6 — description value names, the group_visitors.md vs FrameBuilder.h LightGroupTag tag-name conflict, and consumers (draining element readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0. Static analysis only; RVAs image-relative to Minecraft.Windows.exe 1.26.62.01. Every `0xRVA  instr` line below is copied verbatim from an rdis/xref listing and passes tools/sigs/verify_oc.py. Tags: [V] seen in disassembly (RVA cited) | [I] inferred | [?] unknown | [V live] confirmed by capture bytes / live read. "carried" = proven in earlier units (docs/progress/oc_U-ER6_r43.md), not re-proven per RETRY #1.

Input data read fully (not re-generated): docs/functions/6640d80_light_visitor.md; docs/functions/5aba5c0.md (ThreadLocalObject::get; pass object = value at node+0x10); docs/functions/group_visitors.md (superseded on tags 2/3); docs/functions/light_game_descriptions.md (pass-vector table: light records +0x648 stride 0x48, summary +0x800 stride 0x14, GameplayMetadata +0x498 stride 0x84, ShadowAtlasFrame +0x1C8 stride 0x50); docs/data/live/light_visitor.txt (tags 0/1/2/5 only, no tag 3/4 samples); docs/data/live/README.md (light visitor takes {desc,tag} in RDX); docs/data/live/_status.txt; docs/BGFX_MAP.md sections 6gq/6ih/6hi/6w; FrameBuilder.h LightGroupTag enum; Descriptions.h / LightDescriptions.h / LightGameDescriptions.h.

## 1. Carried [V]: tag -> type / LightGroupTag — conflict RESOLVED

| offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|
| variant+0x08 tag byte | 1 | 0x6640dc4, 0x6640de6 | `0x6640dc4  movzx eax,byte ptr [rdx+8]`<br>`0x6640de6  jmp rax` | tag byte at variant+0x08; dispatch `jmp rax` via jump table 0xF2BF2B0 (entries: 0=0x6640de8, 1=0x66415b0, 2=0x6640f1b, 3=0x66410a0, 4=0x6640ec1, 5=0x66417af, 6=0x664187d, 7=0x6641524) | [V] |
| tag 0 = Ambient | 1 | 0x53e3511 | `0x53e3511  mov byte ptr [rbp+0x138],0` | LightGroupTag::Ambient = 0 (FrameBuilder.h:79-88); producer clone 0x53e2c00, srcloc RenderLightAmbientDescription; JT entry 0 | [V carried] |
| tag 1 = Directional | 1 | 0x53709d4 | `0x53709d4  mov byte ptr [rbp+0x18],1` | LightGroupTag::Directional = 1; thin clone 0x5370960, srcloc LightDirectionalDescription; JT entry 1 | [V carried] |
| tag 2 = GameplayMetadata | 1 | 0x53e5fb4, 0x53e5fbf | `0x53e5fb4  mov byte ptr [rbp-0x18],2`<br>`0x53e5fbf  mov rax,[rax+0x380]` | LightGroupTag::GameplayMetadata = 2; Light vslot 0x380 insert at 0x53e5fbf; clone 0x53e5910, srcloc GameplayMetadata; JT entry 2 | [V carried] |
| tag 3 = LightPoint | 1 | 0x535a9b7, 0x535a9c1 | `0x535a9b7  mov byte ptr [rbp+0x278],3`<br>`0x535a9c1  mov rax,[rax+0x380]` | LightGroupTag::LightPoint = 3; light clone 0x53599d0 insert at 0x535a9c1; srcloc LightPointDescription; JT entry 3 | [V carried] |
| tag 4 = ShadowAtlasFrame | 1 | 0x535a696, 0x535a6a0 | `0x535a696  mov byte ptr [rbp+0x278],4`<br>`0x535a6a0  mov rax,[rax+0x380]` | LightGroupTag::ShadowAtlasFrame = 4; light clone 0x53599d0 insert at 0x535a6a0; srcloc ShadowAtlasFrameDescription; JT entry 4 | [V carried] |
| tag-map conflict | - | FrameBuilder.h:79-88 | - | RESOLVED [V carried]: `enum class LightGroupTag : uint64_t { Ambient = 0, Directional = 1, GameplayMetadata = 2, LightPoint = 3, ShadowAtlasFrame = 4, ServerGraphicsOverrideParameters = 5, VoxelVolume = 6, TransitioningVoxelVolume = 7 }`; producer tag stores + __FUNCSIG__ srclocs prove tag 2 = GameplayMetadata and tag 3 = LightPoint; FrameBuilder.h wins; group_visitors.md had them swapped (LightPoint@2 / GameplayMetadata@3) and is superseded; BGFX_MAP.md 6w line 504 agrees (Light group: 0 Ambient, 1 Directional, 2 GameplayMetadata) | [V carried] |

## 2. Carried [V]: Light-visitor writers to pass+0x800 / +0x648 / +0x4A0 / +0x1D0

Pass-object vectors (begin/end/cap cursors): summary +0x7F8/+0x800/+0x808 stride 0x14; light records +0x648/+0x650 stride 0x48; GameplayMetadata +0x498/+0x4A0/+0x4A8 stride 0x84; ShadowAtlasFrame +0x1C8/+0x1D0/+0x1D8 stride 0x50 [V carried]. Every write below is an end-cursor increment / grow-emplace; no end-cursor pop/decrement exists anywhere in the exe [V carried, whole-image fld --w scans].

| offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|
| pass+0x800 end cursor | 8 | 0x6640e84, 0x6640e8b, 0x6640eb4, 0x6641761, 0x66417a2, 0x6641517 | `0x6640e84  mov rdx,[rsi+0x800]`<br>`0x6640e8b  cmp rdx,[rsi+0x808]`<br>`0x6640eb4  add qword ptr [rsi+0x800],0x14`<br>`0x6641761  mov rdx,[rsi+0x800]`<br>`0x66417a2  add qword ptr [rsi+0x800],0x14`<br>`0x6641517  add qword ptr [rsi+0x800],0x14` | end cursor of the 0x14-byte summary list (cap cursor +0x808 compared at 0x6640e8b); writers: Ambient 0x6640eb4, Directional 0x66417a2, LightPoint 0x6641517 (all increment by 0x14); cap compare at 0x6640e8b | [V carried] |
| pass+0x648 end cursor | 8 | 0x66416f8, 0x66416ff, 0x664145a, 0x6641461 | `0x66416f8  lea rcx,[rsi+0x648]`<br>`0x66416ff  call 0x675FB30`<br>`0x664145a  lea rcx,[rsi+0x648]`<br>`0x6641461  call 0x675FB30` | end cursor of the 0x48-byte light-record vector (begin +0x648 / end +0x650); Directional (0x66416ff) and LightPoint (0x6641461) pass &end to grow-emplace 0x675FB30 | [V carried] |
| pass+0x4A0 end cursor | 8 | 0x6640f78, 0x6641090, 0x6640f7f | `0x6640f78  mov r12,[rdi+0x4A0]`<br>`0x6641090  add qword ptr [rdi+0x4A0],0x84`<br>`0x6640f7f  cmp r12,[rdi+0x4A8]` | end cursor of the 0x84-byte GameplayMetadata vector (begin +0x498 / cap +0x4A8); tag-2 writer, stride 0x84; load at 0x6640f78, cap compare at 0x6640f7f | [V carried] |
| pass+0x1D0 end cursor | 8 | 0x66419c6 | `0x66419c6  add qword ptr [rsi+0x1D0],0x50` | end cursor of the 0x50-byte ShadowAtlasFrame vector (begin +0x1C8 / cap +0x1D8); tag-4 writer, stride 0x50 | [V carried] |

## 3. Live capture result check — oc_u_er6_light_desc (visitor entry 0x6640d80, size 0x100, max 6)

- `python tools/livecap/request.py result oc_u_er6_light_desc` -> pending; no docs/data/live/oc_u_er6_light_desc.txt exists yet [PENDING]. Capture was requested at visitor entry 0x6640d80 (RDX = desc pointer, docs/data/live/README.md) to dump desc bytes for tag 3 (LightPoint) / tag 4 (ShadowAtlasFrame) and let `ret=` name the visitor caller chain.
- What it CAN add: tag-3/tag-4 description bytes at visitor entry -> confirm field sizes/runtime values vs Descriptions.h layouts (light_visitor.txt carries tags 0/1/2/5 only, so tag 3/4 bytes are new); `ret=` names the visitor caller chain (expect _insert(Light) wrapper sub_6640ae0). Cite [V live] when result exists.
- What it CANNOT add: it cannot locate consumers of pass+0x800/+0x648/+0x4A0/+0x1D0 (function-entry sampling, no read/write watch on the pass vectors) and yields values only, never member names. livemem is not an alternative: no static pass-object target address exists (0x5ABA5C0 = per-call ThreadLocalObject getter; `rdis imm/ptr 0x5aba5c0` = 0 refs/slots), so no livemem read was issued [V static].

## 4. Pending: description field value names — UNKNOWN [?]

| offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|
| description value names | - | - | - | unknown [?]: the release exe has no RTTI and no description member-name strings; LightDescriptions.h / LightGameDescriptions.h type every field as mValue* placeholders with static_assert offsets only; descscan2 case 2 (GameplayMetadata) reads desc+0x00..+0x84 only [V]; live desc bytes confirm sizes only, never names; producer-side semantics (e.g. Ambient +0x00 copied from Atmosphere +0xA4) are inference [I], not names. Parked in MIRROR_SKIP per prior review (r2 REVIEW 24/24 [V]). | [?] |

## 5. Pending: consumers (draining element readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — NOT LOCATED

| offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|
| pass+0x800 elements | - | - | - | no draining element read of the 0x14-byte summary vector anywhere in Minecraft.Windows.exe 1.26.62.01; end-cursor increment writes only; whole-image fld --r scans negative | [?] |
| pass+0x648 elements | - | - | - | no draining element read of the 0x48-byte light-record vector anywhere in the exe; writes are grow-emplace calls to 0x675FB30 plus index-word stores only | [?] |
| pass+0x4A0 elements | - | - | - | no draining element read of the 0x84-byte GameplayMetadata vector anywhere in the exe; writes are end-cursor increments only | [?] |
| pass+0x1D0 elements | - | - | - | no draining element read of the 0x50-byte ShadowAtlasFrame vector anywhere in the exe; writes are end-cursor increments only | [?] |

Static angles tried this session that failed (RETRY #1): endFrame sub_66232b0 re-listed (0x66232b0..0x662e680) — no call to 0x5ABA5C0, none of the four offsets as immediates; fld --r 0x8A8/0x8A0 whole-image = stack/unrelated-object locals only; whole-image fld --r/--w on 0x800/0x648/0x4A0/0x1D0 and begin cursors = writer cursor accesses only; all 0x5ABA5C0 callers touch only stack locals or are other visitors; rdis ptr/imm 0x5aba5c0 = 0 slots/refs; magic-multiplier imm scans 0xFFFF8E39 (÷0x48), 0xFFFFCCCD (÷0x14), 0xFFFF83E1 (÷0x84) = hits only inside known writers; descscan2 tag-2 case 0x6640f1b reads desc+0x00..+0x84 only, no pass offset; per-draw code 0x66ea3d0 appends u16 indices to pass+0x8A8 and reads none of the four cursors; BGFX_MAP.md 6gq/6ih/6w/6hi name no consumer of the four vectors. Static analysis is exhausted: any consumer must index `[pass + index*stride]` (computed address, no immediate), which offset scans cannot see; no available tool installs a read/write watchpoint on the pass vectors.

## CLOSES?

CLOSES? NO — single blocking fact: no draining reader (element consumer) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 exists anywhere in Minecraft.Windows.exe 1.26.62.01; all four vectors are write-only statically (end-cursor increments / grow-emplace + index-word records only, no pop/decrement, no element-indexed read) [V negative]. Whole-image fld scans, endFrame re-list, all 0x5ABA5C0 callers, rdis ptr/imm/xr indirect checks, magic-multiplier imm scans, descscan2, BGFX_MAP.md 6gq/6ih/6w/6hi are all negative [V], and the pending live entry capture oc_u_er6_light_desc cannot install a read/write watch on the pass vectors nor give member names; no pass-object address exists for livemem [V static]. Description field value names also remain unknown [?]: no RTTI or description member-name strings in the release exe; headers use mValue* placeholders; live desc bytes confirm sizes only, never names.

Resolved [V] and carried, not re-proven here: tag 2 = GameplayMetadata, tag 3 = LightPoint (FrameBuilder.h wins the group_visitors.md conflict which had 2/3 swapped); the four end-cursor writers to pass+0x800/+0x648/+0x4A0/+0x1D0 [V].

## TOOL REQUESTS

CAPTURE REQUESTED oc_u_er6_light_desc — already pending at visitor entry 0x6640d80 (size 0x100, max 6; queue full at 4 pending so no new `add` was possible); result awaited in docs/data/live/oc_u_er6_light_desc.txt via `python tools/livecap/request.py result oc_u_er6_light_desc`. What would close consumers: a read/write watchpoint on pass+0x800/+0x648/+0x4A0/+0x1D0 (not available via this tool) or a live pass-object address for livemem (none exists: 0x5ABA5C0 = per-call TLS getter, rdis imm/ptr to 0x5aba5c0 = 0 refs/slots). Helper scripts: None.
