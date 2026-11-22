## NEXT
DONE

# U-ER6 — R6: LightAmbient / LightDirectional / Light tag 2 / tag 3 / tag 4 (1.26.62.01)

Goal: close R6 — tag value names, the group_visitors.md vs FrameBuilder.h LightGroupTag conflict, and consumers (draining element readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0.
Static analysis only; RVAs image-relative to Minecraft.Windows.exe 1.26.62.01. Every `0xRVA  instr` line below is copied verbatim from a listing and passes tools/sigs/verify_oc.py.
Tags: [V] seen in disassembly (RVA cited) | [I] inferred from tool output | [?] unknown | [V live] confirmed by capture bytes / live read.

Input data (read fully, not re-generated): docs/functions/6640d80_light_visitor.md; docs/functions/5aba5c0.md (ThreadLocalObject::get; pass object = value at node+0x10); docs/functions/group_visitors.md; docs/functions/light_game_descriptions.md (pass-vector table: light records +0x648 stride 0x48, summary +0x800 stride 0x14, GameplayMetadata +0x498 stride 0x84, ShadowAtlasFrame +0x1C8 stride 0x50; every case appends a 0xC8 DrawItem record to pass+0x08 with per-type mask word + u16 vector indices); docs/data/live/light_visitor.txt (tags 0/1/2/5 only, no tag 3/4 samples); docs/data/live/README.md (light visitor args {desc,tag} in RDX); docs/data/live/_status.txt (DONE t=120); docs/BGFX_MAP.md sections 6gq/6ih/6hi; src/sdk/mc/deps/minecraft_renderer/framebuilder/FrameBuilder.h (LightGroupTag enum); Descriptions.h. Prior units r1-r27 carried [V] and NOT redone per RETRY #1.

## 1. Tag -> type / LightGroupTag and the tag-name conflict — RESOLVED [V]

| offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|
| variant+0x08 tag byte | 1 | 0x6640dc4, 0x6640de6 | `0x6640dc4  movzx eax,byte ptr [rdx+8]`<br>`0x6640de6  jmp rax` | tag byte at variant+0x08; indirect dispatch `jmp rax` via jump table 0xF2BF2B0 (entries: 0=0x6640de8, 1=0x66415b0, 2=0x6640f1b, 3=0x66410a0, 4=0x6640ec1, 5=0x66417af, 6=0x664187d, 7=0x6641524) | [V] |
| tag 0 = Ambient | 1 | 0x53e3511 | `0x53e3511  mov byte ptr [rbp+0x138],0` | LightGroupTag::Ambient = 0 (FrameBuilder.h:79-88); producer clone 0x53e2c00, srcloc 0xF248E70 RenderLightAmbientDescription; jump-table entry 0 (0x6640de8) | [V] |
| tag 1 = Directional | 1 | 0x53709d4 | `0x53709d4  mov byte ptr [rbp+0x18],1` | LightGroupTag::Directional = 1; thin clone 0x5370960, srcloc 0xF248F70 LightDirectionalDescription; entry 1 (0x66415b0) | [V] |
| tag 2 = GameplayMetadata | 1 | 0x53e5fb4, 0x53e5fbf | `0x53e5fb4  mov byte ptr [rbp-0x18],2`<br>`0x53e5fbf  mov rax,[rax+0x380]` | LightGroupTag::GameplayMetadata = 2; Light vslot 0x380 insert; clone 0x53e5910, srcloc 0xF248ED0 GameplayMetadata; entry 2 (0x6640f1b) | [V] |
| tag 3 = LightPoint | 1 | 0x535a9b7, 0x535a9c1 | `0x535a9b7  mov byte ptr [rbp+0x278],3`<br>`0x535a9c1  mov rax,[rax+0x380]` | LightGroupTag::LightPoint = 3; light clone 0x53599d0 insert; srcloc 0xF248DA0 LightPointDescription; entry 3 (0x66410a0) | [V] |
| tag 4 = ShadowAtlasFrame | 1 | 0x535a696, 0x535a6a0 | `0x535a696  mov byte ptr [rbp+0x278],4`<br>`0x535a6a0  mov rax,[rax+0x380]` | LightGroupTag::ShadowAtlasFrame = 4; light clone 0x53599d0 insert; srcloc 0xF248D80 ShadowAtlasFrameDescription; entry 4 (0x6640ec1) | [V] |
| tag-map conflict | - | FrameBuilder.h:79-88 | - | RESOLVED [V]: `enum class LightGroupTag : uint64_t { Ambient = 0, Directional = 1, GameplayMetadata = 2, LightPoint = 3, ShadowAtlasFrame = 4, ServerGraphicsOverrideParameters = 5, VoxelVolume = 6, TransitioningVoxelVolume = 7 }`; producer tag stores + __FUNCSIG__ srclocs prove tag 2 = GameplayMetadata and tag 3 = LightPoint; FrameBuilder.h wins; group_visitors.md had them swapped (LightPoint@2 / GameplayMetadata@3) and is superseded. Tags 5/6/7 = ServerGraphicsOverrideParameters / VoxelVolume / TransitioningVoxelVolume | [V] |

## 2. Description field value names — UNKNOWN [?]

| offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|
| description value names | - | - | - | unknown [?]: the release exe has no RTTI and no description member-name strings; LightDescriptions.h / LightGameDescriptions.h type every field as mValue* placeholders with static_assert offsets only; live dumps carry description bytes only (sizes confirmed), never member names. Producer-side semantics (e.g. Ambient +0x00 copied from Atmosphere +0xA4) are inference [I], not names. | [?] |

## 3. Light-visitor writers to pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — PROVEN [V]

Pass-object vectors (begin/end/cap cursors): summary +0x7F8/+0x800/+0x808 stride 0x14; light records +0x648/+0x650 stride 0x48; GameplayMetadata +0x498/+0x4A0/+0x4A8 stride 0x84; ShadowAtlasFrame +0x1C8/+0x1D0/+0x1D8 stride 0x50 [V]. Every write below is an end-cursor increment / grow-emplace; no end-cursor pop/decrement exists anywhere in the exe [V, whole-image fld --w scans].

| offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|
| pass+0x800 end cursor | 8 | 0x6640e84, 0x6640e8b, 0x6640eb4, 0x6641761, 0x66417a2, 0x6641517 | `0x6640e84  mov rdx,[rsi+0x800]`<br>`0x6640e8b  cmp rdx,[rsi+0x808]`<br>`0x6640eb4  add qword ptr [rsi+0x800],0x14`<br>`0x6641761  mov rdx,[rsi+0x800]`<br>`0x66417a2  add qword ptr [rsi+0x800],0x14`<br>`0x6641517  add qword ptr [rsi+0x800],0x14` | end cursor of the 0x14-byte summary list (cap cursor +0x808); writers: Ambient 0x6640eb4, Directional 0x66417a2, Point 0x6641517 (all increment by 0x14); cap compared at 0x6640e8b | [V] |
| pass+0x648 end cursor | 8 | 0x66416f8, 0x66416ff, 0x664145a, 0x6641461, 0x66ed5c0, 0x66ed5ce, 0x670e27c, 0x670e28a, 0x6725579, 0x6725587 | `0x66416f8  lea rcx,[rsi+0x648]`<br>`0x66416ff  call 0x675FB30`<br>`0x664145a  lea rcx,[rsi+0x648]`<br>`0x6641461  call 0x675FB30`<br>`0x66ed5c0  lea rcx,[r15+0x648]`<br>`0x66ed5ce  call 0x675FB30`<br>`0x670e27c  lea rcx,[r15+0x648]`<br>`0x670e28a  call 0x675FB30`<br>`0x6725579  lea rcx,[r14+0x648]`<br>`0x6725587  call 0x675FB30` | end cursor of the 0x48-byte light-record vector (begin +0x648 / end +0x650); Directional (0x66416ff) and Point (0x6641461) plus per-draw clones 0x66ed5c0 / 0x670e27c / 0x6725579 pass &end to grow-emplace 0x675FB30 | [V] |
| pass+0x650 end cursor | 4 | 0x6641729, 0x6641735, 0x6641738, 0x66ed5f0, 0x66ed5f7, 0x66ed5fe, 0x66ed601, 0x66ed607, 0x66ed609 | `0x6641729  mov eax,[rsi+0x650]`<br>`0x6641735  shr eax,3`<br>`0x6641738  imul eax,0xFFFF8E39`<br>`0x66ed5f0  mov eax,[r15+0x650]`<br>`0x66ed5f7  sub eax,[r15+0x648]`<br>`0x66ed5fe  shr eax,3`<br>`0x66ed601  imul eax,0xFFFF8E39`<br>`0x66ed607  dec eax`<br>`0x66ed609  mov [rbp+0x1172],ax` | light-record end cursor; element index = (end-begin)/0x48 - 1 stored as a u16 word into a local DrawItem record — a write of an index word, NOT an element read of the vector [V] | [V] |
| pass+0x4A0 end cursor | 8 | 0x6640f78, 0x6641090, 0x6640f7f | `0x6640f78  mov r12,[rdi+0x4A0]`<br>`0x6641090  add qword ptr [rdi+0x4A0],0x84`<br>`0x6640f7f  cmp r12,[rdi+0x4A8]` | end cursor of the 0x84-byte GameplayMetadata vector (begin +0x498 / cap +0x4A8); tag-2 writer, stride 0x84 | [V] |
| pass+0x1D0 end cursor | 8 | 0x66419c6 | `0x66419c6  add qword ptr [rsi+0x1D0],0x50` | end cursor of the 0x50-byte ShadowAtlasFrame vector (begin +0x1C8 / cap +0x1D8); tag-4 writer, stride 0x50 | [V] |

## 4. Consumers of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — NOT LOCATED [?]

| offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|
| pass+0x800 elements | - | - | - | no draining element read of the 0x14-byte summary vector anywhere in Minecraft.Windows.exe 1.26.62.01; end-cursor increment writes only; whole-image fld --r scans negative [V negative] | [?] |
| pass+0x648 elements | - | - | - | no draining element read of the 0x48-byte light-record vector anywhere in the exe; writes are grow-emplace calls to 0x675FB30 plus index-word stores only [V negative] | [?] |
| pass+0x4A0 elements | - | - | - | no draining element read of the 0x84-byte GameplayMetadata vector anywhere in the exe; writes are end-cursor increments only [V negative] | [?] |
| pass+0x1D0 elements | - | - | - | no draining element read of the 0x50-byte ShadowAtlasFrame vector anywhere in the exe; writes are end-cursor increments only [V negative] | [?] |

Negative angles already proven (NOT redone per RETRY #1): whole-image `fld --r/--w` scans for all four offsets + begin cursors (0x7F8/0x650/0x498/0x1C8) show only the four writer cursor accesses plus stack/unrelated same-offset hits; endFrame full listing (sub_66232b0) contains none of the four offsets though it calls 0x5ABA5C0 3x; all ~200 `0x5ABA5C0` callers (xref.py now shows 76 direct callers, all covered by fld) touch only stack locals or are other visitors; `rdis ptr 0x5aba5c0` (0 indirect slots) and `rdis imm 0x5aba5c0` (0 static data refs); grow path 0x675FB30 and shared case epilogue do cursor arithmetic only, never element reads; per-draw code 0x66ea3d0 appends u16 indices to the unrelated pass vector at +0x8A8 and reads none of the four cursors [V]; descscan2 on GameplayMetadata case 0x6640f1b reads ONLY desc+0x00..+0x84 (description fields copied INTO the pass), NO reads of pass+0x4A0 or any pass offset [V]; BGFX_MAP.md 6ih line 1843-1844: Sky vector at pass+0x548 also finds no reader — same consumer blocker for all pass vectors; line 2041: consumers of new pass vectors open [?]; line 2033: pool roles (consumer: U-PASS3's 0xBB.. task bodies) open [I from BGFX_MAP.md].

NEW ANGLE THIS SESSION — magic-multiplier imm scans (looking for consumers computing element indices via stride division), all negative for consumers:

| scan | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|
| imm 0xFFFF8E39 (÷0x48 light-record stride) | 4 | 0x66431a7 | `rdis imm 0xFFFF8E39` | 184 hits; nearly all in known group visitors. Non-visitor hits 0x66ea3d0, 0x670b6e0, 0x6722cb0, clouds 0x67375a0, flamebillboard 0x673d150, weather 0x6745440, 0x676xxx-0x67eab80 all proven MORE WRITERS to pass+0x648 (`lea rcx,[r15+0x648]; call 0x675FB30` then index-word store `mov eax,[r15+0x650]; sub eax,[r15+0x648]; shr eax,3; imul eax,0xFFFF8E39; dec eax; mov [rbp+off],ax`). No `[base + index*0x48]` element read anywhere. Only non-visitor GameplayMetadata-stride hit is inside light visitor itself (0x66431a7, the writer) | [V negative] |
| imm 0xFFFFCCCD (÷0x14 summary stride) | 4 | 0x2f2514e, 0x89e4367, bccb4ea, 0x666cb23 | `rdis imm 0xFFFFCCCD` | 11 hits; outside light visitor: Spawn Rules stride 0x28 stack array (unrelated), other object vectors, 0x28-stride objects, effect visitor. NONE reads pass+0x800 summary elements [base+index*0x14] | [V negative] |
| imm 0xFFFF83E1 (÷0x84 GameplayMetadata stride) | 4 | 0x66431a7 | `rdis imm 0xFFFF83E1` | EXACTLY ONE hit — 0x66431a7 inside light visitor itself (the writer's index computation). Negative: no GameplayMetadata element consumer computes indices this way | [V negative] |

## 5. Live capture status

Request oc_u_er6_light_desc (visitor entry 0x6640d80, size 0x100, max 6, state pending, result awaited in docs/data/live/oc_u_er6_light_desc.txt): RDX = desc pointer at entry (docs/data/live/README.md CORRECTION 2026-11-15: light visitor takes {desc,tag} in RDX). `python tools/livecap/request.py result oc_u_er6_light_desc` -> "no result yet (orchestrator has not run it)" [V live, request.py result command]. Existing live dump docs/data/live/light_visitor.txt shows tags 5/0/1/2/2/1 across its samples — no tag 3 (LightPoint) or tag 4 (ShadowAtlasFrame) sample yet [V live].

What the live data CAN add: description bytes per tag at visit time -> confirm field sizes/runtime values for tag 3 (0x108 B) and tag 4 (0x50 B) vs Descriptions.h layouts; ret= at entry names the visitor caller chain [V live when run].
What it CANNOT add (it is not a write-watch): it observes description bytes at visitor entry, not later reads of the pass vectors, so it cannot locate consumers of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — that needs a memory read/write watch on those element offsets, which this tool does not provide. Description value names also cannot come from live capture (values only, no names; no RTTI/name strings exist in the exe). Capture queue is FULL at 4 pending (er5_clone_4c8a5b0, l8b_resizetex_slot31, sub_1289440_callers, oc_u_er6_light_desc) so no new `add` this unit [V static]. livemem: the game IS running [V live] but there is no static pass-object target address (0x5ABA5C0 is a per-call ThreadLocalObject getter; rdis imm/ptr to 0x5aba5c0 = 0 refs/slots), so no livemem read was issued [V static].

## CLOSES?

CLOSES? NO — single blocking fact: no draining reader (element consumer) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 exists anywhere in Minecraft.Windows.exe 1.26.62.01; all four vectors are write-only statically (end-cursor increments / grow-emplace + index-word records only, no pop/decrement, no element-indexed read) [V negative]; whole-image fld scans, the endFrame listing 0x66232b0, all ~200 0x5ABA5C0 callers (xref.py 76 direct, all covered by fld), rdis ptr/imm/xr indirect checks, magic-multiplier imm scans (0xFFFF8E39/0xFFFFCCCD/0xFFFF83E1), descscan2 on the GameplayMetadata case, and write-site epilogue disassembly are all negative [V]; the pending live entry capture cannot install a read/write watch on the pass vectors, and livemem has no pass-object target address [V static]. Description value names also remain unknown [?]: no RTTI or description member-name strings in the release exe; headers use mValue* placeholders; live desc bytes confirm sizes only, never names.

Resolved [V], carried, not re-proven here: tag 2 = GameplayMetadata, tag 3 = LightPoint (FrameBuilder.h wins the group_visitors.md conflict which had 2/3 swapped); the four end-cursor writers to pass+0x800/+0x648/+0x4A0/+0x1D0 [V].

## TOOL REQUESTS

CAPTURE REQUESTED oc_u_er6_light_desc — already pending at visitor entry 0x6640d80 (size 0x100, max 6; result awaited in docs/data/live/oc_u_er6_light_desc.txt). Queue full at 4 pending so no new `add` this unit. The entry capture can add runtime desc bytes (which tags land in 6 samples is not controllable; no tag 3/4 bytes exist in any capture yet) plus ret= caller chain — bytes only, never member names, no read/write watchpoint, so it cannot close the consumer blocker. What would close consumers: a read/write watchpoint on pass+0x800/+0x648/+0x4A0/+0x1D0 (not available via this tool) or a live pass-object address for livemem (none exists: 0x5ABA5C0 = per-call TLS getter, rdis imm/ptr to 0x5aba5c0 = 0 refs/slots). Helper scripts: None.
