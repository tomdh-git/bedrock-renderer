## NEXT
DONE

# U-ER6 — R6: LightAmbient / LightDirectional / Light tag 2 / tag 3 / tag 4 (1.26.62.01)

Goal: close R6 — tag value names, the group_visitors.md vs FrameBuilder.h LightGroupTag conflict, and consumers (draining element readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0.
Static analysis only; RVAs image-relative to Minecraft.Windows.exe 1.26.62.01. Every `0xRVA  instr` line below is copied verbatim from a listing and passes tools/sigs/verify_oc.py.
Tags: [V] seen in disassembly (RVA cited) | [I] inferred from tool output | [?] unknown | [V live] confirmed by capture bytes / live read.

Input data (read fully, not re-generated): docs/functions/6640d80_light_visitor.md; docs/functions/5aba5c0.md (ThreadLocalObject::get; pass object = value at node+0x10); docs/functions/group_visitors.md (superseded on tags 2/3); docs/functions/light_game_descriptions.md (pass-vector table: light records +0x648 stride 0x48, summary +0x800 stride 0x14, GameplayMetadata +0x498 stride 0x84, ShadowAtlasFrame +0x1C8 stride 0x50); docs/data/live/light_visitor.txt (tags 0/1/2/5 only, no tag 3/4 samples); docs/data/live/README.md (light visitor takes {desc,tag} in RDX); docs/data/live/_status.txt (oc_u_er6_light_desc queued at visitor entry 0x6640d80, size 0x100, max 6; no oc_u_er6_light_desc result file); docs/BGFX_MAP.md sections 6gq/6ih/6hi and 6w line 504; FrameBuilder.h LightGroupTag enum; Descriptions.h. Prior units r1-r32 carried [V] and are NOT redone per RETRY #1.

## NEW ANGLE TRIED THIS UNIT — how sub_6640ae0 (visitor's only direct caller) is entered

sub_6640ae0 builds the visitor's {desc, tag} variant, calls 0x6640d80 at 0x6640c44, then ends a profiler zone and returns; it reads none of pass+0x800/+0x648/+0x4A0/+0x1D0 and drains nothing [V carried]. It is not entered by any direct call: xref.py callers 0x6640ae0 -> nothing [V carried]. | sub_6640ae0 entry | - | - | - | how this visitor's only direct caller is entered: xref.py callers 0x6640ae0 -> nothing [V carried]; this unit: `rdis imm 0x6640ae0` -> `-- 0 hit(s)` [V], `rdis callers 0x6640ae0` -> `-- 0 calling function(s)` [V], `python tools/sigs/ripscan.py 0x6640ae0` -> no hits [V]; reached only indirectly (indirect call / jump-table slot), unresolved [?]; confirmed NOT a consumer of the four pass vectors [V carried]. No new consumer can be named from the entry side. | [?] |


## 1. Tag -> type / LightGroupTag and the tag-name conflict — RESOLVED [V] (carried r1-r32, not re-proven)

| offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|
| variant+0x08 tag byte | 1 | 0x6640dc4, 0x6640de6 | `0x6640dc4  movzx eax,byte ptr [rdx+8]`<br>`0x6640de6  jmp rax` | tag byte at variant+0x08; indirect dispatch `jmp rax` via jump table 0xF2BF2B0 (entries: 0=0x6640de8, 1=0x66415b0, 2=0x6640f1b, 3=0x66410a0, 4=0x6640ec1, 5=0x66417af, 6=0x664187d, 7=0x6641524) | [V] |
| tag 0 = Ambient | 1 | 0x53e3511 | `0x53e3511  mov byte ptr [rbp+0x138],0` | LightGroupTag::Ambient = 0 (FrameBuilder.h:79-88); producer clone 0x53e2c00, srcloc 0xF248E70 RenderLightAmbientDescription; jump-table entry 0 (0x6640de8) | [V] |
| tag 1 = Directional | 1 | 0x53709d4 | `0x53709d4  mov byte ptr [rbp+0x18],1` | LightGroupTag::Directional = 1; thin clone 0x5370960, srcloc 0xF248F70 LightDirectionalDescription; entry 1 (0x66415b0) | [V] |
| tag 2 = GameplayMetadata | 1 | 0x53e5fb4, 0x53e5fbf | `0x53e5fb4  mov byte ptr [rbp-0x18],2`<br>`0x53e5fbf  mov rax,[rax+0x380]` | LightGroupTag::GameplayMetadata = 2; Light vslot 0x380 insert; clone 0x53e5910, srcloc 0xF248ED0 GameplayMetadata; entry 2 (0x6640f1b); independently listed as Light tag 2 in BGFX_MAP.md 6w line 504 | [V] |
| tag 3 = LightPoint | 1 | 0x535a9b7, 0x535a9c1 | `0x535a9b7  mov byte ptr [rbp+0x278],3`<br>`0x535a9c1  mov rax,[rax+0x380]` | LightGroupTag::LightPoint = 3; light clone 0x53599d0 insert; srcloc 0xF248DA0 LightPointDescription; entry 3 (0x66410a0) | [V] |
| tag 4 = ShadowAtlasFrame | 1 | 0x535a696, 0x535a6a0 | `0x535a696  mov byte ptr [rbp+0x278],4`<br>`0x535a6a0  mov rax,[rax+0x380]` | LightGroupTag::ShadowAtlasFrame = 4; light clone 0x53599d0 insert; srcloc 0xF248D80 ShadowAtlasFrameDescription; entry 4 (0x6640ec1) | [V] |
| tag-map conflict | - | FrameBuilder.h:79-88 | - | RESOLVED [V]: `enum class LightGroupTag : uint64_t { Ambient = 0, Directional = 1, GameplayMetadata = 2, LightPoint = 3, ShadowAtlasFrame = 4, ServerGraphicsOverrideParameters = 5, VoxelVolume = 6, TransitioningVoxelVolume = 7 }`; producer tag stores + __FUNCSIG__ srclocs prove tag 2 = GameplayMetadata and tag 3 = LightPoint; FrameBuilder.h wins; group_visitors.md had them swapped (LightPoint@2 / GameplayMetadata@3) and is superseded; BGFX_MAP.md 6w line 504 agrees (Light group: 0 Ambient, 1 Directional, 2 GameplayMetadata) | [V] |

## 2. Light-visitor writers to pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — PROVEN [V] (carried r1-r32)

Pass-object vectors (begin/end/cap cursors): summary +0x7F8/+0x800/+0x808 stride 0x14; light records +0x648/+0x650 stride 0x48; GameplayMetadata +0x498/+0x4A0/+0x4A8 stride 0x84; ShadowAtlasFrame +0x1C8/+0x1D0/+0x1D8 stride 0x50 [V]. Every write below is an end-cursor increment / grow-emplace; no end-cursor pop/decrement exists anywhere in the exe [V, whole-image fld --w scans in prior units].

| offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|
| pass+0x800 end cursor | 8 | 0x6640e84, 0x6640e8b, 0x6640eb4, 0x6641761, 0x66417a2, 0x6641517 | `0x6640e84  mov rdx,[rsi+0x800]`<br>`0x6640e8b  cmp rdx,[rsi+0x808]`<br>`0x6640eb4  add qword ptr [rsi+0x800],0x14`<br>`0x6641761  mov rdx,[rsi+0x800]`<br>`0x66417a2  add qword ptr [rsi+0x800],0x14`<br>`0x6641517  add qword ptr [rsi+0x800],0x14` | end cursor of the 0x14-byte summary list (cap cursor +0x808); writers: Ambient 0x6640eb4, Directional 0x66417a2, Point 0x6641517 (all increment by 0x14); cap compared at 0x6640e8b | [V] |
| pass+0x648 end cursor | 8 | 0x66416f8, 0x66416ff, 0x664145a, 0x6641461 | `0x66416f8  lea rcx,[rsi+0x648]`<br>`0x66416ff  call 0x675FB30`<br>`0x664145a  lea rcx,[rsi+0x648]`<br>`0x6641461  call 0x675FB30` | end cursor of the 0x48-byte light-record vector (begin +0x648 / end +0x650); Directional (0x66416ff) and Point (0x6641461) pass &end to grow-emplace 0x675FB30; per-draw clones 0x66ed5c0/0x66ed5ce/0x670e27c/0x670e28a/0x6725579/0x6725587 do the same [V carried] | [V] |
| pass+0x4A0 end cursor | 8 | 0x6640f78, 0x6641090, 0x6640f7f | `0x6640f78  mov r12,[rdi+0x4A0]`<br>`0x6641090  add qword ptr [rdi+0x4A0],0x84`<br>`0x6640f7f  cmp r12,[rdi+0x4A8]` | end cursor of the 0x84-byte GameplayMetadata vector (begin +0x498 / cap +0x4A8); tag-2 writer, stride 0x84 | [V] |
| pass+0x1D0 end cursor | 8 | 0x66419c6 | `0x66419c6  add qword ptr [rsi+0x1D0],0x50` | end cursor of the 0x50-byte ShadowAtlasFrame vector (begin +0x1C8 / cap +0x1D8); tag-4 writer, stride 0x50 | [V] |

## 3. Description field value names — UNKNOWN [?] (no new data this unit; not redone)

| offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|
| description value names | - | - | - | unknown [?]: the release exe has no RTTI and no description member-name strings; LightDescriptions.h / LightGameDescriptions.h type every field as mValue* placeholders with static_assert offsets only; live dumps carry description bytes only (sizes confirmed), never member names. Producer-side semantics (e.g. Ambient +0x00 copied from Atmosphere +0xA4) are inference [I], not names. The queued live capture (desc bytes at visitor entry) can confirm field sizes per tag but never member names. | [?] |

## 4. Consumers of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — NOT LOCATED [?]

| offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|
| pass+0x800 elements | - | - | - | no draining element read of the 0x14-byte summary vector anywhere in Minecraft.Windows.exe 1.26.62.01; end-cursor increment writes only; whole-image fld --r scans in prior units negative [V carried]; this unit's imm/rip/xr checks on the visitor entry path found no new reader [V above] | [?] |
| pass+0x648 elements | - | - | - | no draining element read of the 0x48-byte light-record vector anywhere in the exe; writes are grow-emplace calls to 0x675FB30 plus index-word stores only [V carried] | [?] |
| pass+0x4A0 elements | - | - | - | no draining element read of the 0x84-byte GameplayMetadata vector anywhere in the exe; writes are end-cursor increments only [V carried] | [?] |
| pass+0x1D0 elements | - | - | - | no draining element read of the 0x50-byte ShadowAtlasFrame vector anywhere in the exe; writes are end-cursor increments only [V carried] | [?] |

`python tools/livecap/request.py result oc_u_er6_light_desc` -> "no result yet (orchestrator has not run it)" [V live, request.py result command]. `request.py add ... 0x6640d80 ...` -> "already queued", exit 1: the capture is already pending from prior units and the result is awaited in docs/data/live/oc_u_er6_light_desc.txt [V static, request.py output].

What the live data CAN add when run: description bytes per tag at visitor entry (RDX = desc pointer; docs/data/live/README.md CORRECTION 2026-11-15: light visitor takes {desc,tag} in RDX) -> confirm field sizes/runtime values per tag vs Descriptions.h layouts (tag 3 LightPoint ~0x108 B, tag 4 ShadowAtlasFrame ~0x50 B per static layout, IF tags 3/4 land in the 6 samples — not controllable; no tag 3/4 bytes exist in any capture yet) and ret= naming the visitor caller chain (statically already sub_6640ae0, see above) [V live when run].

What it CANNOT add (it is not a write-watch): it observes description bytes at visitor entry, not later reads of the pass vectors, so it cannot locate consumers of pass+0x800 / +0x648 / +0x4A0 / +0x1D0; description value names also cannot come from live capture (values only, no names; no RTTI/name strings in the exe). livemem: the game is running [V live] but there is no static pass-object target address (0x5ABA5C0 = per-call TLS getter; rdis imm/ptr to 0x5aba5c0 = 0 refs/slots [V carried]), so no livemem read was issued [V static].

Negative angles proven in prior units (NOT redone per RETRY #1): whole-image `fld --r/--w` scans for all four offsets + begin cursors (0x7F8/0x650/0x498/0x1C8) show only the four writer cursor accesses plus stack/unrelated same-offset hits; endFrame full listing (sub_66232b0) contains none of the four offsets though it calls 0x5ABA5C0 3x; all 0x5ABA5C0 callers touch only stack locals or are other visitors; `rdis ptr 0x5aba5c0` (0 indirect slots) and `rdis imm 0x5aba5c0` (0 static data refs); grow path 0x675FB30 and shared case epilogue do cursor arithmetic only, never element reads; per-draw code 0x66ea3d0 appends u16 indices to the unrelated pass vector at +0x8A8 and reads none of the four cursors [V]; descscan2 on GameplayMetadata case 0x6640f1b reads ONLY desc+0x00..+0x84 (description fields copied INTO the pass), NO reads of pass+0x4A0 or any pass offset [V]; magic-multiplier imm scans (0xFFFF8E39 ÷0x48, 0xFFFFCCCD ÷0x14, 0xFFFF83E1 ÷0x84) are negative for consumers — every hit is inside known writers [V negative]. BGFX_MAP.md sections read: 6gq = ThreadLocalObject getter, per-thread 0x8B8 blocks, visitors queue then a later merge [V]; 6hi = per-frame pending-job merge 0xc288880 (0x67591e0 over the seven loader weak_ptr/job queues — resource merge, not light vectors) [V]; 6w line 504 lists Light tags 0 Ambient, 1 Directional, 2 GameplayMetadata, 5 ServerGraphicsOverrideParameters [I from map]; 6ih lines 1843-1844: Sky vector at pass+0x548 also finds no reader — same consumer blocker for all pass vectors; line 2041: consumers of the new pass vectors open [?]; line 2033: pool roles (consumer: U-PASS3's 0xBB.. task bodies) open [I from BGFX_MAP.md]. No consumer of pass+0x800/+0x648/+0x4A0/+0x1D0 is named anywhere in BGFX_MAP.md [I from BGFX_MAP.md]. vt/vcalls negative [V carried].

## CLOSES?

CLOSES? NO — single blocking fact: no draining reader (element consumer) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 exists anywhere in Minecraft.Windows.exe 1.26.62.01; all four vectors are write-only statically (end-cursor increments / grow-emplace + index-word records only, no pop/decrement, no element-indexed read) [V negative carried]; whole-image fld scans, the endFrame listing 0x66232b0, all 0x5ABA5C0 callers, rdis ptr/imm/xr indirect checks, magic-multiplier imm scans, descscan2, vt/vcalls, BGFX_MAP.md 6gq/6ih/6w/6hi, and the visitor's only caller sub_6640ae0 are all negative [V carried]; this unit added rdis imm/callers/ripscan on sub_6640ae0 = 0 hits [V] and the live entry capture oc_u_er6_light_desc is queued but cannot install a read/write watch on the pass vectors [V static]; livemem has no pass-object target address [V static]. Description value names also remain unknown [?]: no RTTI or description member-name strings in the release exe; headers use mValue* placeholders; live desc bytes confirm sizes only, never names.

Resolved [V], carried, not re-proven here: tag 2 = GameplayMetadata, tag 3 = LightPoint (FrameBuilder.h wins the group_visitors.md conflict which had 2/3 swapped, corroborated by BGFX_MAP.md 6w line 504); the four end-cursor writers to pass+0x800/+0x648/+0x4A0/+0x1D0 [V].

## TOOL REQUESTS

CAPTURE REQUESTED oc_u_er6_light_desc at visitor entry 0x6640d80 (size 0x100, max 6; already queued from prior units, state pending; result awaited in docs/data/live/oc_u_er6_light_desc.txt). The entry capture can add runtime desc bytes per tag plus ret= caller chain — bytes only, never member names, no read/write watchpoint, so it cannot close the consumer blocker. What would close consumers: a read/write watchpoint on pass+0x800/+0x648/+0x4A0/+0x1D0 (not available via this tool) or a live pass-object address for livemem (none exists: 0x5ABA5C0 = per-call TLS getter, rdis imm/ptr to 0x5aba5c0 = 0 refs/slots). Helper scripts: None.
