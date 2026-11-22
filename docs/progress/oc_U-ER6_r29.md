## NEXT
DONE

# U-ER6 — R6: LightAmbient / LightDirectional / Light tag 2 / tag 3 / tag 4 (1.26.62.01)

Goal: close R6 — tag value names, the group_visitors.md vs FrameBuilder.h LightGroupTag conflict, and consumers (draining element readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0.
Static analysis only; RVAs image-relative to Minecraft.Windows.exe 1.26.62.01. Every `0xRVA  instr` line below is copied verbatim from a listing and passes tools/sigs/verify_oc.py.
Tags: [V] seen in disassembly (RVA cited) | [I] inferred from tool output | [?] unknown | [V live] confirmed by capture bytes / live read.

Input data (read fully, not re-generated): docs/functions/6640d80_light_visitor.md; docs/functions/5aba5c0.md (ThreadLocalObject::get; pass object = value at node+0x10); docs/functions/group_visitors.md; docs/functions/light_game_descriptions.md (pass-vector table: light records +0x648 stride 0x48, summary +0x800 stride 0x14, GameplayMetadata +0x498 stride 0x84, ShadowAtlasFrame +0x1C8 stride 0x50); docs/data/live/light_visitor.txt (tags 0/1/2/5 only, no tag 3/4 samples); docs/data/live/README.md (light visitor args {desc,tag} in RDX); docs/data/live/_status.txt; docs/BGFX_MAP.md sections 6gq/6ih/6hi; src/sdk/mc/deps/minecraft_renderer/framebuilder/FrameBuilder.h (LightGroupTag enum); Descriptions.h. Prior units r1-r28 carried [V] and NOT redone per RETRY #1.

## 1. Tag -> type / LightGroupTag and the tag-name conflict — RESOLVED [V] (carried from r1-r28, not re-proven this unit)

| offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|
| variant+0x08 tag byte | 1 | 0x6640dc4, 0x6640de6 | proof lines below | tag byte at variant+0x08; indirect dispatch `jmp rax` via jump table 0xF2BF2B0 (entries: 0=0x6640de8, 1=0x66415b0, 2=0x6640f1b, 3=0x66410a0, 4=0x6640ec1, 5=0x66417af, 6=0x664187d, 7=0x6641524) | [V] |
| tag 0 = Ambient | 1 | 0x53e3511 | proof line below | LightGroupTag::Ambient = 0 (FrameBuilder.h:79-88); producer clone 0x53e2c00, srcloc 0xF248E70 RenderLightAmbientDescription; jump-table entry 0 (0x6640de8) | [V] |
| tag 1 = Directional | 1 | 0x53709d4 | proof line below | LightGroupTag::Directional = 1; thin clone 0x5370960, srcloc 0xF248F70 LightDirectionalDescription; entry 1 (0x66415b0) | [V] |
| tag 2 = GameplayMetadata | 1 | 0x53e5fb4, 0x53e5fbf | proof lines below | LightGroupTag::GameplayMetadata = 2; Light vslot 0x380 insert; clone 0x53e5910, srcloc 0xF248ED0 GameplayMetadata; entry 2 (0x6640f1b) | [V] |
| tag 3 = LightPoint | 1 | 0x535a9b7, 0x535a9c1 | proof lines below | LightGroupTag::LightPoint = 3; light clone 0x53599d0 insert; srcloc 0xF248DA0 LightPointDescription; entry 3 (0x66410a0) | [V] |
| tag 4 = ShadowAtlasFrame | 1 | 0x535a696, 0x535a6a0 | proof lines below | LightGroupTag::ShadowAtlasFrame = 4; light clone 0x53599d0 insert; srcloc 0xF248D80 ShadowAtlasFrameDescription; entry 4 (0x6640ec1) | [V] |
| tag-map conflict | - | FrameBuilder.h:79-88 | - | RESOLVED [V]: `enum class LightGroupTag : uint64_t { Ambient = 0, Directional = 1, GameplayMetadata = 2, LightPoint = 3, ShadowAtlasFrame = 4, ServerGraphicsOverrideParameters = 5, VoxelVolume = 6, TransitioningVoxelVolume = 7 }`; producer tag stores + __FUNCSIG__ srclocs prove tag 2 = GameplayMetadata and tag 3 = LightPoint; FrameBuilder.h wins; group_visitors.md had them swapped (LightPoint@2 / GameplayMetadata@3) and is superseded. Tags 5/6/7 = ServerGraphicsOverrideParameters / VoxelVolume / TransitioningVoxelVolume | [V] |

`0x6640dc4  movzx eax,byte ptr [rdx+8]`
`0x6640de6  jmp rax`
`0x53e3511  mov byte ptr [rbp+0x138],0`
`0x53709d4  mov byte ptr [rbp+0x18],1`
`0x53e5fb4  mov byte ptr [rbp-0x18],2`
`0x53e5fbf  mov rax,[rax+0x380]`
`0x535a9b7  mov byte ptr [rbp+0x278],3`
`0x535a9c1  mov rax,[rax+0x380]`
`0x535a696  mov byte ptr [rbp+0x278],4`
`0x535a6a0  mov rax,[rax+0x380]`

## 2. Light-visitor writers to pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — PROVEN [V] (carried)

Pass-object vectors (begin/end/cap cursors): summary +0x7F8/+0x800/+0x808 stride 0x14; light records +0x648/+0x650 stride 0x48; GameplayMetadata +0x498/+0x4A0/+0x4A8 stride 0x84; ShadowAtlasFrame +0x1C8/+0x1D0/+0x1D8 stride 0x50 [V]. Every write below is an end-cursor increment / grow-emplace; no end-cursor pop/decrement exists anywhere in the exe [V, whole-image fld --w scans].

| offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|
| pass+0x800 end cursor | 8 | 0x6640e84, 0x6640e8b, 0x6640eb4, 0x6641761, 0x66417a2, 0x6641517 | proof lines below | end cursor of the 0x14-byte summary list (cap cursor +0x808); writers: Ambient 0x6640eb4, Directional 0x66417a2, Point 0x6641517 (all increment by 0x14); cap compared at 0x6640e8b | [V] |
| pass+0x648 end cursor | 8 | 0x66416f8, 0x66416ff, 0x664145a, 0x6641461, 0x66ed5c0, 0x66ed5ce, 0x670e27c, 0x670e28a, 0x6725579, 0x6725587 | proof lines below | end cursor of the 0x48-byte light-record vector (begin +0x648 / end +0x650); Directional (0x66416ff) and Point (0x6641461) plus per-draw clones 0x66ed5c0 / 0x670e27c / 0x6725579 pass &end to grow-emplace 0x675FB30 | [V] |
| pass+0x4A0 end cursor | 8 | 0x6640f78, 0x6641090, 0x6640f7f | proof lines below | end cursor of the 0x84-byte GameplayMetadata vector (begin +0x498 / cap +0x4A8); tag-2 writer, stride 0x84 | [V] |
| pass+0x1D0 end cursor | 8 | 0x66419c6 | proof line below | end cursor of the 0x50-byte ShadowAtlasFrame vector (begin +0x1C8 / cap +0x1D8); tag-4 writer, stride 0x50 | [V] |

`0x6640e84  mov rdx,[rsi+0x800]`
`0x6640e8b  cmp rdx,[rsi+0x808]`
`0x6640eb4  add qword ptr [rsi+0x800],0x14`
`0x6641761  mov rdx,[rsi+0x800]`
`0x66417a2  add qword ptr [rsi+0x800],0x14`
`0x6641517  add qword ptr [rsi+0x800],0x14`
`0x66416f8  lea rcx,[rsi+0x648]`
`0x66416ff  call 0x675FB30`
`0x664145a  lea rcx,[rsi+0x648]`
`0x6641461  call 0x675FB30`
`0x6640f78  mov r12,[rdi+0x4A0]`
`0x6641090  add qword ptr [rdi+0x4A0],0x84`
`0x6640f7f  cmp r12,[rdi+0x4A8]`
`0x66419c6  add qword ptr [rsi+0x1D0],0x50`

## 3. Description field value names — UNKNOWN [?] (no new data this unit)

| offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|
| description value names | - | - | - | unknown [?]: the release exe has no RTTI and no description member-name strings; LightDescriptions.h / LightGameDescriptions.h type every field as mValue* placeholders with static_assert offsets only; live dumps carry description bytes only (sizes confirmed), never member names. Producer-side semantics (e.g. Ambient +0x00 copied from Atmosphere +0xA4) are inference [I], not names. | [?] |

## 4. NEW THIS UNIT — live capture at visitor entry 0x6640d80

`python tools/livecap/request.py add oc_u_er6_light_desc 0x6640d80 --size 0x100 --max 6 --why "R6: confirm tag-3 LightPoint (0x108B) and tag-4 ShadowAtlasFrame (0x50B) description bytes/sizes at visitor entry, and name the light-visitor caller chain via ret=; still hunting consumers of pass+0x800/+0x648/+0x4A0/+0x1D0"` -> "already queued", exit 1: the capture is already one of the 4 pending targets (mc_root_4e05e50_callers, oc_u_el6b_desc, l8b_texcreate_record, el10b_lighting_desc per docs/data/live/_status.txt); queue full, no new `add` possible this unit [V static, request.py output].
`python tools/livecap/request.py result oc_u_er6_light_desc` -> "no result yet (orchestrator has not run it)" [V live, request.py result command]; docs/data/live/ contains no oc_u_er6_light_desc.txt [V live, directory listing].
Existing live dump docs/data/live/light_visitor.txt shows tags 5/0/1/2/2/1 across its samples — no tag 3 (LightPoint) or tag 4 (ShadowAtlasFrame) sample yet [V live].

What the live data CAN add when the orchestrator runs it: description bytes per tag at visitor entry (RDX = desc pointer; docs/data/live/README.md CORRECTION 2026-11-15: the light visitor takes {desc,tag} in RDX) -> confirm field sizes/runtime values per tag vs Descriptions.h layouts (tag 3 0x108 B, tag 4 0x50 B); ret= at entry names the visitor caller chain [V live when run].
What it CANNOT add (it is not a write-watch): it observes description bytes at visitor entry, not later reads of the pass vectors, so it cannot locate consumers of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — that needs a memory read/write watch on those element offsets, which this tool does not provide. Description value names also cannot come from live capture (values only, no names; no RTTI/name strings exist in the exe). livemem: the game IS running [V live] but there is no static pass-object target address (0x5ABA5C0 is a per-call ThreadLocalObject getter; rdis imm/ptr to 0x5aba5c0 = 0 refs/slots), so no livemem read was issued [V static].

## 5. Consumers of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — NOT LOCATED [?]

| offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|
| pass+0x800 elements | - | - | - | no draining element read of the 0x14-byte summary vector anywhere in Minecraft.Windows.exe 1.26.62.01; end-cursor increment writes only; whole-image fld --r scans negative [V negative] | [?] |
| pass+0x648 elements | - | - | - | no draining element read of the 0x48-byte light-record vector anywhere in the exe; writes are grow-emplace calls to 0x675FB30 plus index-word stores only [V negative] | [?] |
| pass+0x4A0 elements | - | - | - | no draining element read of the 0x84-byte GameplayMetadata vector anywhere in the exe; writes are end-cursor increments only [V negative] | [?] |
| pass+0x1D0 elements | - | - | - | no draining element read of the 0x50-byte ShadowAtlasFrame vector anywhere in the exe; writes are end-cursor increments only [V negative] | [?] |

Negative angles proven (NOT redone per RETRY #1): whole-image `fld --r/--w` scans for all four offsets + begin cursors (0x7F8/0x650/0x498/0x1C8) show only the four writer cursor accesses plus stack/unrelated same-offset hits; endFrame full listing (sub_66232b0) contains none of the four offsets though it calls 0x5ABA5C0 3x; all ~200 `0x5ABA5C0` callers (xref.py shows 76 direct callers, all covered by fld) touch only stack locals or are other visitors; `rdis ptr 0x5aba5c0` (0 indirect slots) and `rdis imm 0x5aba5c0` (0 static data refs); grow path 0x675FB30 and shared case epilogue do cursor arithmetic only, never element reads; per-draw code 0x66ea3d0 appends u16 indices to the unrelated pass vector at +0x8A8 and reads none of the four cursors [V]; descscan2 on GameplayMetadata case 0x6640f1b reads ONLY desc+0x00..+0x84 (description fields copied INTO the pass), NO reads of pass+0x4A0 or any pass offset [V]; magic-multiplier imm scans (0xFFFF8E39 ÷0x48, 0xFFFFCCCD ÷0x14, 0xFFFF83E1 ÷0x84) are negative for consumers — every hit is inside known writers [V negative]. BGFX_MAP.md sections read this unit: 6gq = ThreadLocalObject getter, per-thread 0x8B8 blocks, visitors queue then a later merge [V]; 6hi = per-frame pending-job merge 0xc288880 (0x67591e0 over the seven loader weak_ptr/job queues — resource merge, not light vectors) [V]; 6ih lines 1843-1844: Sky vector at pass+0x548 also finds no reader — same consumer blocker for all pass vectors; line 2041: consumers of the new pass vectors open [?]; line 2033: pool roles (consumer: U-PASS3's 0xBB.. task bodies) open [I from BGFX_MAP.md]. No consumer of pass+0x800/+0x648/+0x4A0/+0x1D0 is named anywhere in BGFX_MAP.md [I from BGFX_MAP.md]. New static angles available to this unit (vt/vcalls, flow/path/rw/struct, descscan2 on the remaining light cases) add no consumer: descriptions are only copied INTO the pass, never read back from it [V static]. A consumer using computed addresses (lea + index with no immediate offset) would be invisible to these scans; ruling that out needs a live read/write watch on the four element offsets, which no available tool provides [I].

## CLOSES?

CLOSES? NO — single blocking fact: no draining reader (element consumer) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 exists anywhere in Minecraft.Windows.exe 1.26.62.01; all four vectors are write-only statically (end-cursor increments / grow-emplace + index-word records only, no pop/decrement, no element-indexed read) [V negative]; whole-image fld scans, the endFrame listing 0x66232b0, all 0x5ABA5C0 callers, rdis ptr/imm/xr indirect checks, magic-multiplier imm scans (0xFFFF8E39/0xFFFFCCCD/0xFFFF83E1), descscan2 on the GameplayMetadata case, and BGFX_MAP.md 6gq/6ih/6hi are all negative [V]; the live entry capture oc_u_er6_light_desc (queued, result pending) cannot install a read/write watch on the pass vectors, and livemem has no pass-object target address [V static]. Description value names also remain unknown [?]: no RTTI or description member-name strings in the release exe; headers use mValue* placeholders; live desc bytes confirm sizes only, never names.

Resolved [V], carried, not re-proven here: tag 2 = GameplayMetadata, tag 3 = LightPoint (FrameBuilder.h wins the group_visitors.md conflict which had 2/3 swapped); the four end-cursor writers to pass+0x800/+0x648/+0x4A0/+0x1D0.

## TOOL REQUESTS

CAPTURE REQUESTED oc_u_er6_light_desc — already pending at visitor entry 0x6640d80 (size 0x100, max 6; result awaited in docs/data/live/oc_u_er6_light_desc.txt). Queue full at 4 pending (mc_root_4e05e50_callers, oc_u_el6b_desc, l8b_texcreate_record, el10b_lighting_desc per _status.txt) so no new `add` this unit ("already queued", exit 1). The entry capture can add runtime desc bytes (which tags land in 6 samples is not controllable; no tag 3/4 bytes exist in any capture yet) plus ret= caller chain — bytes only, never member names, no read/write watchpoint, so it cannot close the consumer blocker. What would close consumers: a read/write watchpoint on pass+0x800/+0x648/+0x4A0/+0x1D0 (not available via this tool) or a live pass-object address for livemem (none exists: 0x5ABA5C0 = per-call TLS getter, rdis imm/ptr to 0x5aba5c0 = 0 refs/slots). Helper scripts: None.
