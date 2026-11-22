## NEXT
DONE

# U-ER6 — R6: LightAmbient / LightDirectional / Light tag 2 / tag 3 / tag 4 (1.26.62.01)

Goal: close R6 — description value names, the group_visitors.md vs FrameBuilder.h LightGroupTag tag-name conflict, and consumers (draining element readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0. Static analysis only; RVAs image-relative to Minecraft.Windows.exe 1.26.62.01. Every `0xRVA  instr` line below is copied verbatim from an rdis listing. Tags: [V] seen in disassembly (RVA cited) | [I] inferred | [?] unknown | [V live] confirmed by capture bytes / live read. "carried" = proven in earlier units (docs/progress/oc_U-ER6_r45.md), not re-proven per RETRY #1.

Input data read fully (not re-generated): docs/functions/6640d80_light_visitor.md; docs/functions/5aba5c0.md (ThreadLocalObject::get; pass object = value at node+0x10); docs/functions/group_visitors.md (superseded on tags 2/3); docs/functions/light_game_descriptions.md (pass-vector table: light records +0x648 stride 0x48, summary +0x800 stride 0x14, GameplayMetadata +0x498 stride 0x84, ShadowAtlasFrame +0x1C8 stride 0x50); docs/data/live/light_visitor.txt (tags 0/1/2/5 only, no tag 3/4 samples); docs/data/live/README.md (light visitor takes {desc,tag} in RDX); docs/data/live/_status.txt (capture status DONE t=120; oc_u_er6_light_desc not listed — not run yet); docs/BGFX_MAP.md sections 6gq (0x5aba5c0 = ThreadLocalObject::get: returns the calling thread's 0x8B8-byte data block, so the pass object is per-thread), 6ih (Light visitor register map: description = rsi; tag-0/1/2/3/4/5/6/7 reads), 6hi (per-frame pending-job merge from endFrame), 6w (Light group: 0 Ambient, 1 Directional, 2 GameplayMetadata); FrameBuilder.h LightGroupTag enum; Descriptions.h / LightDescriptions.h / LightGameDescriptions.h.

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
| pass+0x4A0 end cursor | 8 | 0x6640f78, 0x6640f7f, 0x6641090 | `0x6640f78  mov r12,[rdi+0x4A0]`<br>`0x6640f7f  cmp r12,[rdi+0x4A8]`<br>`0x6641090  add qword ptr [rdi+0x4A0],0x84` | end cursor of the 0x84-byte GameplayMetadata vector (begin +0x498 / cap +0x4A8); tag-2 writer, stride 0x84; load at 0x6640f78, cap compare at 0x6640f7f | [V carried] |
| pass+0x1D0 end cursor | 8 | 0x66419c6 | `0x66419c6  add qword ptr [rsi+0x1D0],0x50` | end cursor of the 0x50-byte ShadowAtlasFrame vector (begin +0x1C8 / cap +0x1D8); tag-4 writer, stride 0x50 | [V carried] |

## 3. Consumers (draining element readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — NOT LOCATED [?]

| offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|
| pass+0x800 elements | - | - | - | no draining element read of the 0x14-byte summary vector anywhere in Minecraft.Windows.exe 1.26.62.01; end-cursor increment writes only; whole-image fld --r scans negative | [?] |
| pass+0x648 elements | - | - | - | no draining element read of the 0x48-byte light-record vector anywhere in the exe; writes are grow-emplace calls to 0x675FB30 plus index-word stores only | [?] |
| pass+0x4A0 elements | - | - | - | no draining element read of the 0x84-byte GameplayMetadata vector anywhere in the exe; writes are end-cursor increments only | [?] |
| pass+0x1D0 elements | - | - | - | no draining element read of the 0x50-byte ShadowAtlasFrame vector anywhere in the exe; writes are end-cursor increments only | [?] |

### 3.1 New static angles tried this session that FAILED

- **rdis fld 0x808 --r** (cap cursor of the summary vector): 993 accesses, all `[rbp+0x808]` / `[reg+0x808]` stack or unrelated-object locals (sub_280fb0, sub_488540, sub_570700 families, ...); none traceable to the pass object — the pass object comes only from 0x5ABA5c0 (ThreadLocalObject::get, per-thread 0x8B8 block, BGFX_MAP.md 6gq), and all its callers are the light visitors plus endFrame, which reads none of the four offsets [V negative].
- **rdis fld 0x4A8 --r** (GameplayMetadata cap cursor): 2521 accesses, same picture — stack/unrelated locals only (sub_7a7e0, sub_ed150, sub_55f330 `mov rax,[rax+0x4A8]` register base not tied to the pass, ...) [V negative].
- **rdis fld 0x1D8 --r** (ShadowAtlasFrame cap cursor): 10702 accesses, same picture [V negative].
- Carried negatives not re-run per RETRY #1: whole-image `fld --r/--w` on 0x800/0x648/0x4A0/0x1D0 and begin cursors 0x7F8/0x650/0x498/0x1C8; endFrame 0x66232b0 re-list (no call to 0x5ABA5C0, none of the four offsets); all 0x5ABA5C0 callers touch only stack locals or are other visitors; `rdis xr/callers` of visitor entry 0x6640d80 = sole caller `sub_6640ae0+0x164 call 0x6640d80`, which never drains; `rdis ptr/imm 0x5aba5c0` = 0 slots/refs; magic-multiplier imm scans 0xFFFF8E39 (÷0x48), 0xFFFFCCCD (÷0x14), 0xFFFF83E1 (÷0x84) = writer hits only; descscan2 tag-2 case 0x6640f1b reads desc+0x00..+0x84 only, no pass offset; per-draw code 0x66ea3d0 appends u16 indices to pass+0x8A8 and reads none of the four cursors; ClusterLights body 0xbc5bad0 reads per-view light clusters through `[data_0x12AE1748] + view*0x1EAB090`, not the pass vectors [V negative]; BGFX_MAP.md 6gq/6ih/6hi/6w/6ha name no consumer of the four vectors (pass+0x548 Sky vector same readerless blocker, line 1843-1844).
- Conclusion [V negative]: any consumer must index `[pass + index*stride]` (computed address, no immediate), which offset scans cannot see; no available tool installs a read/write watch on the pass vectors. The pass object is per-thread (0x5aba5c0), so no static global pass-object address exists for livemem either [V static, 6gq].

## 4. Live capture status — oc_u_er6_light_desc (visitor entry 0x6640d80, size 0x100, max 6) — PENDING

- `python tools/livecap/request.py result oc_u_er6_light_desc` -> "no result yet (orchestrator has not run it)"; no docs/data/live/oc_u_er6_light_desc.txt exists [V checked this session]. `python tools/livecap/request.py list` shows it as the 4th of 4 pending slots (queue full: er5_clone_4c8a5b0, l8b_resizetex_slot31, sub_1289440_callers, oc_u_er6_light_desc); no new `add` possible while the queue is full [V request.py list].
- What it CAN add when run: tag-3 (LightPoint, 0x108 B) / tag-4 (ShadowAtlasFrame, 0x50 B) description bytes at visitor entry (RDX = desc pointer, docs/data/live/README.md) to confirm field sizes/runtime values vs Descriptions.h layouts (light_visitor.txt carries tags 0/1/2/5 only), and `ret=` to name the visitor caller chain (expect the _insert(Light) wrapper sub_6640ae0). Cite as [V live] when the result exists.
- What it CANNOT add: it cannot locate consumers of pass+0x800/+0x648/+0x4A0/+0x1D0 (function-entry sampling, no read/write watch on the pass vectors) and yields values only, never member names; no pass-object address exists for livemem (0x5ABA5C0 = per-call TLS getter; `rdis imm/ptr 0x5aba5c0` = 0 refs/slots) [V static].

## 5. Description field value names — UNKNOWN [?]

| offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|
| description value names | - | - | - | unknown [?]: the release exe has no RTTI and no description member-name strings; LightDescriptions.h / LightGameDescriptions.h type every field as mValue* placeholders with static_assert offsets only; descscan2 case 2 (GameplayMetadata) reads desc+0x00..+0x84 only [V]; live capture desc bytes confirm sizes only, never names; producer-side semantics (e.g. Ambient +0x00 copied from Atmosphere +0xA4) are inference [I], not names. Parked in MIRROR_SKIP per prior review (r2 REVIEW 24/24 [V]). | [?] |

## CLOSES?

CLOSES? NO — single blocking fact: no draining reader (element consumer) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 exists anywhere in Minecraft.Windows.exe 1.26.62.01; all four vectors are write-only statically (end-cursor increments / grow-emplace + index-word records only, no pop/decrement, no element-indexed read) [V negative]. Whole-image fld scans (including the new cap-cursor scans 0x808/0x4A8/0x1D8 this session), endFrame re-list, all 0x5ABA5C0 callers, rdis ptr/imm/xr indirect checks, magic-multiplier imm scans, descscan2, per-draw code, BGFX_MAP.md 6gq/6ih/6hi/6w/6ha, and ClusterLights 0xbc5bad0 are all negative [V]; the pending live entry capture oc_u_er6_light_desc cannot install a read/write watch on the pass vectors nor give member names; no pass-object address exists for livemem [V static]. Description field value names also remain unknown [?]: no RTTI or description member-name strings in the release exe; headers use mValue* placeholders; live desc bytes confirm sizes only, never names.

Resolved [V] and carried, not re-proven here: tag 2 = GameplayMetadata, tag 3 = LightPoint (FrameBuilder.h wins the group_visitors.md conflict which had 2/3 swapped); the four end-cursor writers to pass+0x800/+0x648/+0x4A0/+0x1D0 [V].

## TOOL REQUESTS

CAPTURE REQUESTED oc_u_er6_light_desc — light-visitor entry capture (0x6640d80, size 0x100, max 6) already PENDING at visitor entry 0x6640d80; result awaited in docs/data/live/oc_u_er6_light_desc.txt via `python tools/livecap/request.py result oc_u_er6_light_desc`. What would close the consumer blocker: a read/write watchpoint on pass+0x800/+0x648/+0x4A0/+0x1D0 (not available via this tool) or a live pass-object address for livemem (none exists: 0x5ABA5C0 = per-call TLS getter, rdis imm/ptr to 0x5aba5c0 = 0 refs/slots). Helper scripts: None.
