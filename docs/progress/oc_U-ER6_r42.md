## NEXT
DONE

# U-ER6 — R6: LightAmbient / LightDirectional / Light tag 2 / tag 3 / tag 4 (1.26.62.01)

Goal: close R6 — tag value names, the group_visitors.md vs FrameBuilder.h LightGroupTag conflict, and consumers (draining element readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0. Static analysis only; RVAs image-relative to Minecraft.Windows.exe 1.26.62.01. Every `0xRVA  instr` line below is copied verbatim from a listing and passes tools/sigs/verify_oc.py.

Tags: [V] seen in disassembly (RVA cited) | [I] inferred from tool output | [?] unknown | [V live] confirmed by capture bytes / live read. "carried" = proven in earlier units (docs/progress/oc_U-ER6_r28.md), not redone per RETRY #1.

Input data read fully (not re-generated): docs/functions/6640d80_light_visitor.md; docs/functions/5aba5c0.md (ThreadLocalObject::get; pass object = value at node+0x10); docs/functions/group_visitors.md; docs/functions/light_game_descriptions.md (pass-vector table: light records +0x648 stride 0x48, summary +0x800 stride 0x14, GameplayMetadata +0x498 stride 0x84, ShadowAtlasFrame +0x1C8 stride 0x50; every case appends a 0xC8 DrawItem record to pass+0x08 with per-type mask word + u16 vector indices); docs/data/live/light_visitor.txt (tags 0/1/2/5 only — no tag 3/4 sample); docs/data/live/README.md (light visitor args {desc,tag} in RDX); docs/BGFX_MAP.md sections 6gq/6ih/6hi; src/sdk/mc/deps/minecraft_renderer/framebuilder/FrameBuilder.h (LightGroupTag enum); Descriptions.h. Prior units r1-r28 carried [V] and are not redone.

## 1. Carried [V]: tag -> type / LightGroupTag — conflict RESOLVED

| offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|
| variant+0x08 tag byte | 1 | 0x6640dc4, 0x6640de6 | `0x6640dc4  movzx eax,byte ptr [rdx+8]`<br>`0x6640de6  jmp rax` | tag byte at variant+0x08; dispatch `jmp rax` via jump table 0xF2BF2B0 (entries: 0=0x6640de8, 1=0x66415b0, 2=0x6640f1b, 3=0x66410a0, 4=0x6640ec1, 5=0x66417af, 6=0x664187d, 7=0x6641524) | [V] |
| tag 2 = GameplayMetadata | 1 | 0x53e5fb4, 0x53e5fbf | `0x53e5fb4  mov byte ptr [rbp-0x18],2`<br>`0x53e5fbf  mov rax,[rax+0x380]` | LightGroupTag::GameplayMetadata = 2; clone 0x53e5910 inserts via Light vslot 0x380; __FUNCSIG__ srcloc 0xF248ED0 GameplayMetadata; jump-table entry 2 (0x6640f1b) | [V carried] |
| tag 3 = LightPoint | 1 | 0x535a9b7, 0x535a9c1 | `0x535a9b7  mov byte ptr [rbp+0x278],3`<br>`0x535a9c1  mov rax,[rax+0x380]` | LightGroupTag::LightPoint = 3; light clone 0x53599d0 insert; srcloc 0xF248DA0 LightPointDescription; entry 3 (0x66410a0) | [V carried] |
| tag 4 = ShadowAtlasFrame | 1 | 0x535a696, 0x535a6a0 | `0x535a696  mov byte ptr [rbp+0x278],4`<br>`0x535a6a0  mov rax,[rax+0x380]` | LightGroupTag::ShadowAtlasFrame = 4; light clone 0x53599d0 insert; srcloc 0xF248D80 ShadowAtlasFrameDescription; entry 4 (0x6640ec1) | [V carried] |
| tag-map conflict | - | FrameBuilder.h:79-88 | - | RESOLVED [V carried]: `enum class LightGroupTag : uint64_t { Ambient = 0, Directional = 1, GameplayMetadata = 2, LightPoint = 3, ShadowAtlasFrame = 4, ServerGraphicsOverrideParameters = 5, VoxelVolume = 6, TransitioningVoxelVolume = 7 }`; producer tag stores + __FUNCSIG__ srclocs prove tag 2 = GameplayMetadata and tag 3 = LightPoint; FrameBuilder.h wins; group_visitors.md had them swapped (LightPoint@2 / GameplayMetadata@3) and is superseded. Tags 0/1 = Ambient/Directional (producer clones 0x53e2c00 srcloc 0xF248E70 RenderLightAmbientDescription, 0x5370960 srcloc 0xF248F70 LightDirectionalDescription); tags 5/6/7 = ServerGraphicsOverrideParameters / VoxelVolume / TransitioningVoxelVolume | [V carried] |

## 2. Carried [V]: Light-visitor writers to pass+0x800 / +0x648 / +0x4A0 / +0x1D0

Pass-object vectors (begin/end/cap cursors): summary +0x7F8/+0x800/+0x808 stride 0x14; light records +0x648/+0x650 stride 0x48; GameplayMetadata +0x498/+0x4A0/+0x4A8 stride 0x84; ShadowAtlasFrame +0x1C8/+0x1D0/+0x1D8 stride 0x50 [V carried]. Every write below is an end-cursor increment / grow-emplace; no end-cursor pop/decrement exists anywhere in the exe [V carried, whole-image fld --w scans].

| offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|
| pass+0x800 end cursor | 8 | 0x6640e84, 0x6640e8b, 0x6640eb4, 0x6641761, 0x66417a2, 0x6641517 | `0x6640e84  mov rdx,[rsi+0x800]`<br>`0x6640e8b  cmp rdx,[rsi+0x808]`<br>`0x6640eb4  add qword ptr [rsi+0x800],0x14`<br>`0x6641761  mov rdx,[rsi+0x800]`<br>`0x66417a2  add qword ptr [rsi+0x800],0x14`<br>`0x6641517  add qword ptr [rsi+0x800],0x14` | end cursor of the 0x14-byte summary list (cap cursor +0x808); writers: Ambient 0x6640eb4, Directional 0x66417a2, Point 0x6641517 (all increment by 0x14); cap compared at 0x6640e8b | [V carried] |
| pass+0x648 end cursor | 8 | 0x66416f8, 0x66416ff, 0x664145a, 0x6641461 | `0x66416f8  lea rcx,[rsi+0x648]`<br>`0x66416ff  call 0x675FB30`<br>`0x664145a  lea rcx,[rsi+0x648]`<br>`0x6641461  call 0x675FB30` | end cursor of the 0x48-byte light-record vector (begin +0x648 / end +0x650); Directional (0x66416ff) and Point (0x6641461) pass &end to grow-emplace 0x675FB30; per-draw clones 0x66ed5c0/0x670e27c/0x6725579 same pattern [V carried] | [V carried] |
| pass+0x4A0 end cursor | 8 | 0x6640f78, 0x6640f7f, 0x6641090 | `0x6640f78  mov r12,[rdi+0x4A0]`<br>`0x6640f7f  cmp r12,[rdi+0x4A8]`<br>`0x6641090  add qword ptr [rdi+0x4A0],0x84` | end cursor of the 0x84-byte GameplayMetadata vector (begin +0x498 / cap +0x4A8); tag-2 writer, stride 0x84 | [V carried] |
| pass+0x1D0 end cursor | 8 | 0x66419c6 | `0x66419c6  add qword ptr [rsi+0x1D0],0x50` | end cursor of the 0x50-byte ShadowAtlasFrame vector (begin +0x1C8 / cap +0x1D8); tag-4 writer, stride 0x50 | [V carried] |

## 3. Pending: description value names — UNKNOWN [?]

| offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|
| description value names | - | - | - | unknown [?]: the release exe has no RTTI and no description member-name strings; LightDescriptions.h / LightGameDescriptions.h type every field as mValue* placeholders with static_assert offsets only; live capture yields description VALUES at visit time, never member names; producer-side semantics (e.g. Ambient +0x00 copied from Atmosphere +0xA4) are inference [I], not names. Parked in MIRROR_SKIP per prior review (r2 REVIEW 24/24 [V]). | [?] |

## 4. Pending: consumers of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — NOT LOCATED [?]

| offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|
| pass+0x800 elements | - | - | - | no draining element read of the 0x14-byte summary vector anywhere in Minecraft.Windows.exe 1.26.62.01; end-cursor increment writes only; whole-image fld --r scans negative [V negative carried] | [?] |
| pass+0x648 elements | - | - | - | no draining element read of the 0x48-byte light-record vector anywhere in the exe; writes are grow-emplace calls to 0x675FB30 plus index-word stores only [V negative carried] | [?] |
| pass+0x4A0 elements | - | - | - | no draining element read of the 0x84-byte GameplayMetadata vector anywhere in the exe; writes are end-cursor increments only [V negative carried] | [?] |
| pass+0x1D0 elements | - | - | - | no draining element read of the 0x50-byte ShadowAtlasFrame vector anywhere in the exe; writes are end-cursor increments only [V negative carried] | [?] |

## 5. What was tried this session that failed / cannot add (NEW ANGLE EXHAUSTED)

- Static angles proven NEGATIVE in prior units, NOT redone per RETRY #1: whole-image fld --r/--w scans for all four offsets + begin cursors (0x7F8/0x650/0x498/0x1C8) show only the four writer cursor accesses plus stack/unrelated same-offset hits; endFrame full listing (sub_66232b0) contains none of the four offsets though it calls 0x5ABA5C0 3x; all 76 direct 0x5ABA5C0 callers (xref.py) touch only stack locals or are other visitors, all covered by the fld scan; rdis ptr 0x5aba5c0 (0 indirect slots) and rdis imm 0x5aba5c0 (0 static data refs); magic-multiplier imm scans 0xFFFF8E39 (÷0x48), 0xFFFFCCCD (÷0x14), 0xFFFF83E1 (÷0x84) — hits only inside known writers, no `[base + index*stride]` element read anywhere; descscan2 on GameplayMetadata case 0x6640f1b reads ONLY desc+0x00..+0x84 (description fields copied INTO the pass), NO reads of pass+0x4A0 or any pass offset; per-draw code 0x66ea3d0 appends u16 indices to pass+0x8A8 and reads none of the four cursors. BGFX_MAP.md 6ih line 1843-1844: Sky vector at pass+0x548 also finds no reader — same consumer blocker for all pass vectors; line 2041: consumers of new pass vectors open [?]; line 2033: pool roles (consumer: U-PASS3's 0xBB.. task bodies) open [I from BGFX_MAP.md].
- Orchestrator review 2026-11-22 (28/28, CLOSES NO): static analysis alone is exhausted for this item; consumers not found; needs a live write-watch, not more static work.
- Live capture oc_u_er6_light_desc at visitor entry 0x6640d80 (size 0x100, max 6) is ALREADY PENDING (4th queue slot; `python tools/livecap/request.py list` shows it; result awaited in docs/data/live/oc_u_er6_light_desc.txt — no such file exists yet [V live, request.py list]). Queue full at 4 pending (er5_clone_4c8a5b0, l8b_resizetex_slot31, sub_1289440_callers, oc_u_er6_light_desc) so no new `add` was possible this unit [V static, request.py add limit: 4 pending max]. Existing light_visitor.txt samples show tags 5/0/1/2/2/1 — no tag 3 (LightPoint) or tag 4 (ShadowAtlasFrame) bytes yet [V live, docs/data/live/light_visitor.txt].
- Even when the capture returns: dumped description bytes confirm field sizes/values at visit time and ret= names the visitor caller chain [V live when run], but (a) it cannot install a read/write watch on pass+0x800/+0x648/+0x4A0/+0x1D0 so it cannot locate consumers — that needs a memory read/write watch this tool does not provide, and (b) values never give member names. What it can add: confirm tag 3 (0x108 B) and tag 4 (0x50 B) description sizes vs Descriptions.h layouts.
- livemem: the game IS running (_status.txt DONE t=120) [V live] but there is no static pass-object target address — 0x5ABA5C0 is a per-call ThreadLocalObject getter (rcx = frameCtx+0x10+0x9D0 -> node+0x10 value); rdis imm/ptr to 0x5aba5c0 = 0 refs/slots [V static carried], so no livemem read was issued [V static]. livemem has no watchpoint capability and cannot scan/loop over ranges.

## CLOSES?

CLOSES? NO — single blocking fact: no draining reader (element consumer) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 exists anywhere in Minecraft.Windows.exe 1.26.62.01; all four vectors are write-only statically (end-cursor increments / grow-emplace + index-word records only, no pop/decrement, no element-indexed read) [V negative carried]; the pending live entry capture cannot install a read/write watch on the pass vectors, and livemem has no pass-object address [V static]. Description value names also remain unknown [?]: no RTTI or description member-name strings in the release exe; headers use mValue* placeholders; live desc bytes confirm sizes only, never names.

Resolved [V] and carried, not re-proven here: tag 2 = GameplayMetadata, tag 3 = LightPoint (FrameBuilder.h wins the group_visitors.md conflict which had 2/3 swapped); the four end-cursor writers to pass+0x800/+0x648/+0x4A0/+0x1D0 [V].

## TOOL REQUESTS

CAPTURE REQUESTED oc_u_er6_light_desc — already pending at visitor entry 0x6640d80 (size 0x100, max 6; queue full at 4 pending so no new `add`; result awaited in docs/data/live/oc_u_er6_light_desc.txt). What would close consumers: a read/write watchpoint on pass+0x800/+0x648/+0x4A0/+0x1D0 (not available via this tool) or a live pass-object address for livemem (none exists: 0x5ABA5C0 = per-call TLS getter, rdis imm/ptr to 0x5aba5c0 = 0 refs/slots). Helper scripts: None.
