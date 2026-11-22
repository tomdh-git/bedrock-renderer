## NEXT
DONE

# U-ER6 — R6: LightAmbient / LightDirectional / Light tag 2 / tag 3 / tag 4 (1.26.62.01)

Goal: close R6 — tag value names, the group_visitors.md vs FrameBuilder.h LightGroupTag conflict, and consumers (draining element readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0.
Static analysis only; RVAs image-relative to Minecraft.Windows.exe 1.26.62.01. Every `0xRVA  instr` line below is copied verbatim from a listing and passes tools/sigs/verify_oc.py.
Tags: [V] seen in disassembly (RVA cited) | [I] inferred from tool output | [?] unknown | [V live] confirmed by capture bytes / live read.

Input data (read fully, not re-generated): docs/functions/6640d80_light_visitor.md; docs/functions/5aba5c0.md (ThreadLocalObject::get; pass object = value at node+0x10); docs/functions/group_visitors.md (superseded on tags 2/3); docs/functions/light_game_descriptions.md (pass-vector table: light records +0x648 stride 0x48, summary +0x800 stride 0x14, GameplayMetadata +0x498 stride 0x84, ShadowAtlasFrame +0x1C8 stride 0x50); docs/data/live/light_visitor.txt (tags 0/1/2/5 only, no tag 3/4 samples); docs/data/live/README.md (light visitor takes {desc,tag} in RDX); docs/data/live/_status.txt (oc_u_er6_light_desc NOT listed; no docs/data/live/oc_u_er6_light_desc.txt); docs/BGFX_MAP.md sections 6gq/6ih/6hi and 6w line 504; FrameBuilder.h LightGroupTag enum; Descriptions.h. Prior units r1-r30 carried [V] and are NOT redone per RETRY #1; their PROGRESS line stands: tag-name conflict resolved [V], writers to pass+0x800/+0x648/+0x4A0/+0x1D0 [V], description value names unknown [?], consumers not found [?], parked in MIRROR_SKIP.

## NEW ANGLE ATTEMPTED THIS UNIT — static (visitor caller via xref/callers; rdis flow of sub_6640ae0) plus the live-capture request

The light visitor 0x6640d80 has exactly ONE direct caller: sub_6640ae0 (xref.py callers 0x6640d80 -> 0x6640ae0+0x214; the call instruction itself is at 0x6640c44). sub_6640ae0 builds the visitor's {desc, tag} variant, calls it, then only ends a profiler zone and returns — it reads none of pass+0x800/+0x648/+0x4A0/+0x1D0 and drains nothing. sub_6640ae0 itself has NO incoming xrefs (xref.py callers 0x6640ae0 -> nothing; rdis sum "sub_6640ae0 [0x6640ae0..0x6642ae0) size 0x2000 0 xrefs in"), so how it is entered is unresolved [?], and it is not a consumer [V]. Whole-image fld --r/--w scans, the endFrame listing sub_66232b0, all 0x5ABA5C0 callers, rdis ptr/imm/xr checks, magic-multiplier imm scans, descscan2 on the GameplayMetadata case, BGFX_MAP.md 6gq/6ih/6w/6hi, and vt/vcalls all remain negative [V negative, r1-r30, not redone]. The remaining live angle is the entry capture below (desc bytes + ret= caller chain); it cannot install a read/write watch on the pass vectors, and livemem has no pass-object target address [V static].

## 1. Tag -> type / LightGroupTag and the tag-name conflict — RESOLVED [V] (carried from r1-r30, not re-proven)

| offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|
| variant+0x08 tag byte | 1 | 0x6640dc4, 0x6640de6 | `0x6640dc4  movzx eax,byte ptr [rdx+8]`<br>`0x6640de6  jmp rax` | tag byte at variant+0x08; indirect dispatch `jmp rax` via jump table 0xF2BF2B0 (entries: 0=0x6640de8, 1=0x66415b0, 2=0x6640f1b, 3=0x66410a0, 4=0x6640ec1, 5=0x66417af, 6=0x664187d, 7=0x6641524) | [V] |
| tag 0 = Ambient | 1 | 0x53e3511 | `0x53e3511  mov byte ptr [rbp+0x138],0` | LightGroupTag::Ambient = 0 (FrameBuilder.h:79-88); producer clone 0x53e2c00, srcloc 0xF248E70 RenderLightAmbientDescription; jump-table entry 0 (0x6640de8) | [V] |
| tag 1 = Directional | 1 | 0x53709d4 | `0x53709d4  mov byte ptr [rbp+0x18],1` | LightGroupTag::Directional = 1; thin clone 0x5370960, srcloc 0xF248F70 LightDirectionalDescription; entry 1 (0x66415b0) | [V] |
| tag 2 = GameplayMetadata | 1 | 0x53e5fb4, 0x53e5fbf | `0x53e5fb4  mov byte ptr [rbp-0x18],2`<br>`0x53e5fbf  mov rax,[rax+0x380]` | LightGroupTag::GameplayMetadata = 2; Light vslot 0x380 insert; clone 0x53e5910, srcloc 0xF248ED0 GameplayMetadata; entry 2 (0x6640f1b); independently listed as Light tag 2 in BGFX_MAP.md 6w line 504 | [V] |
| tag 3 = LightPoint | 1 | 0x535a9b7, 0x535a9c1 | `0x535a9b7  mov byte ptr [rbp+0x278],3`<br>`0x535a9c1  mov rax,[rax+0x380]` | LightGroupTag::LightPoint = 3; light clone 0x53599d0 insert; srcloc 0xF248DA0 LightPointDescription; entry 3 (0x66410a0) | [V] |
| tag 4 = ShadowAtlasFrame | 1 | 0x535a696, 0x535a6a0 | `0x535a696  mov byte ptr [rbp+0x278],4`<br>`0x535a6a0  mov rax,[rax+0x380]` | LightGroupTag::ShadowAtlasFrame = 4; light clone 0x53599d0 insert; srcloc 0xF248D80 ShadowAtlasFrameDescription; entry 4 (0x6640ec1) | [V] |
| tag-map conflict | - | FrameBuilder.h:79-88 | - | RESOLVED [V]: `enum class LightGroupTag : uint64_t { Ambient = 0, Directional = 1, GameplayMetadata = 2, LightPoint = 3, ShadowAtlasFrame = 4, ServerGraphicsOverrideParameters = 5, VoxelVolume = 6, TransitioningVoxelVolume = 7 }`; producer tag stores + __FUNCSIG__ srclocs prove tag 2 = GameplayMetadata and tag 3 = LightPoint; FrameBuilder.h wins; group_visitors.md had them swapped (LightPoint@2 / GameplayMetadata@3) and is superseded; BGFX_MAP.md 6w line 504 agrees (Light group: 0 Ambient, 1 Directional, 2 GameplayMetadata) | [V] |

## 2. Light-visitor writers to pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — PROVEN [V] (carried from r1-r30)

Pass-object vectors (begin/end/cap cursors): summary +0x7F8/+0x800/+0x808 stride 0x14; light records +0x648/+0x650 stride 0x48; GameplayMetadata +0x498/+0x4A0/+0x4A8 stride 0x84; ShadowAtlasFrame +0x1C8/+0x1D0/+0x1D8 stride 0x50 [V]. Every write below is an end-cursor increment / grow-emplace; no end-cursor pop/decrement exists anywhere in the exe [V, whole-image fld --w scans].

| offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|
| pass+0x800 end cursor | 8 | 0x6640e84, 0x6640e8b, 0x6640eb4, 0x6641761, 0x66417a2, 0x6641517 | `0x6640e84  mov rdx,[rsi+0x800]`<br>`0x6640e8b  cmp rdx,[rsi+0x808]`<br>`0x6640eb4  add qword ptr [rsi+0x800],0x14`<br>`0x6641761  mov rdx,[rsi+0x800]`<br>`0x66417a2  add qword ptr [rsi+0x800],0x14`<br>`0x6641517  add qword ptr [rsi+0x800],0x14` | end cursor of the 0x14-byte summary list (cap cursor +0x808); writers: Ambient 0x6640eb4, Directional 0x66417a2, Point 0x6641517 (all increment by 0x14); cap compared at 0x6640e8b | [V] |
| pass+0x648 end cursor | 8 | 0x66416f8, 0x66416ff, 0x664145a, 0x6641461, 0x66ed5c0, 0x66ed5ce, 0x670e27c, 0x670e28a, 0x6725579, 0x6725587 | `0x66416f8  lea rcx,[rsi+0x648]`<br>`0x66416ff  call 0x675fb30`<br>`0x664145a  lea rcx,[rsi+0x648]`<br>`0x6641461  call 0x675fb30` | end cursor of the 0x48-byte light-record vector (begin +0x648 / end +0x650); Directional (0x66416ff) and Point (0x6641461) plus per-draw clones 0x66ed5c0 / 0x670e27c / 0x6725579 pass &end to grow-emplace 0x675FB30 | [V] |
| pass+0x4A0 end cursor | 8 | 0x6640f78, 0x6641090, 0x6640f7f | `0x6640f78  mov r12,[rdi+0x4A0]`<br>`0x6641090  add qword ptr [rdi+0x4A0],0x84`<br>`0x6640f7f  cmp r12,[rdi+0x4A8]` | end cursor of the 0x84-byte GameplayMetadata vector (begin +0x498 / cap +0x4A8); tag-2 writer, stride 0x84 | [V] |
| pass+0x1D0 end cursor | 8 | 0x66419c6 | `0x66419c6  add qword ptr [rsi+0x1D0],0x50` | end cursor of the 0x50-byte ShadowAtlasFrame vector (begin +0x1C8 / cap +0x1D8); tag-4 writer, stride 0x50 | [V] |

## 3. Description field value names — UNKNOWN [?] (no new data this unit)

| offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|
| description value names | - | - | - | unknown [?]: the release exe has no RTTI and no description member-name strings; LightDescriptions.h / LightGameDescriptions.h type every field as mValue* placeholders with static_assert offsets only; live dumps carry description bytes only (sizes confirmed), never member names. Producer-side semantics (e.g. Ambient +0x00 copied from Atmosphere +0xA4) are inference [I], not names. The live capture below (desc bytes at visitor entry) can confirm field sizes per tag but never member names. | [?] |

## 4. Consumers of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — NOT LOCATED [?] — live capture queued

| offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|
| pass+0x800 elements | - | - | - | no draining element read of the 0x14-byte summary vector anywhere in Minecraft.Windows.exe 1.26.62.01; end-cursor increment writes only; whole-image fld --r scans negative [V negative] | [?] |
| pass+0x648 elements | - | - | - | no draining element read of the 0x48-byte light-record vector anywhere in the exe; writes are grow-emplace calls to 0x675FB30 plus index-word stores only [V negative] | [?] |
| pass+0x4A0 elements | - | - | - | no draining element read of the 0x84-byte GameplayMetadata vector anywhere in the exe; writes are end-cursor increments only [V negative] | [?] |
| pass+0x1D0 elements | - | - | - | no draining element read of the 0x50-byte ShadowAtlasFrame vector anywhere in the exe; writes are end-cursor increments only [V negative] | [?] |

`python tools/livecap/request.py result oc_u_er6_light_desc` -> no result file exists (docs/data/live/oc_u_er6_light_desc.txt absent; _status.txt lists only mc_root_4e05e50_callers, oc_u_el6b_desc, l8b_texcreate_record, el10b_lighting_desc at t=120) [V static, directory listing].
`python tools/livecap/request.py add oc_u_er6_light_desc 0x6640d80 --size 0x100 --max 6 --why "R6: confirm tag-3 LightPoint and tag-4 ShadowAtlasFrame description bytes/sizes at visitor entry (RDX=desc per docs/data/live/README.md CORRECTION 2026-11-15), name the visitor caller chain via ret=; still hunting consumers of pass+0x800/+0x648/+0x4A0/+0x1D0"` -> "already queued", exit 1: the capture is queued from this unit and the result is awaited in docs/data/live/oc_u_er6_light_desc.txt [V static, request.py output].
What the live data CAN add: description bytes per tag at visitor entry (confirm field sizes/runtime values per tag vs Descriptions.h layouts; tag 3 LightPoint ~0x108 B, tag 4 ShadowAtlasFrame ~0x50 B per static layout, IF tags 3/4 land in the 6 samples — not controllable; no tag 3/4 bytes exist in any capture yet) and ret= naming the visitor caller chain (statically already sub_6640ae0, see section 4b) [V live when run].
What it CANNOT add (not a write-watch): it observes description bytes at visitor entry, not later reads of the pass vectors, so it cannot locate consumers of pass+0x800/+0x648/+0x4A0/+0x1D0; description value names also cannot come from live capture (values only, no names; no RTTI/name strings in the exe). livemem: the game is running [V live] but there is no static pass-object target address (0x5ABA5C0 = per-call TLS getter; rdis imm/ptr to 0x5aba5c0 = 0 refs/slots), so no livemem read was issued [V static].

## 4b. Visitor's only direct caller sub_6640ae0 — checked for draining, none [V]

| offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|
| visitor call setup | - | 0x6640c3c, 0x6640c40, 0x6640c44 | `0x6640c3c  lea rcx,[rbp-0x28]`<br>`0x6640c40  lea rdx,[rbp-0x40]`<br>`0x6640c44  call 0x6640d80` | sub_6640ae0 builds the variant {desc pointer at [rdx+0x00], tag byte at [rdx+0x08]} and makes the only direct call to the light visitor; RCX = frame-context-like local, RDX = variant [V] | [V] |
| visitor call epilogue | - | 0x6640c4a, 0x6640c62, 0x6640c73 | `0x6640c4a  cmp byte ptr [rbp+0x68],1`<br>`0x6640c62  call 0x77a2500`<br>`0x6640c73  ret` | after the visitor returns, sub_6640ae0 only ends the profiler zone (0x77a2500) and returns; it reads none of pass+0x800/+0x648/+0x4A0/+0x1D0 and drains no vector [V] | [V] |
| sub_6640ae0 entry | - | - | - | xref.py callers 0x6640ae0 -> nothing; rdis sum reports "0 xrefs in" for [0x6640ae0..0x6642ae0): how sub_6640ae0 itself is entered is unresolved (indirect/jump-table entry possible) [?]; it is not a consumer of the four pass vectors [V] | [?] |

## CLOSES?

CLOSES? NO — single blocking fact: no draining reader (element consumer) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 exists anywhere in Minecraft.Windows.exe 1.26.62.01; all four vectors are write-only statically (end-cursor increments / grow-emplace + index-word records only, no pop/decrement, no element-indexed read) [V negative]; whole-image fld scans, endFrame listing 0x66232b0, all 0x5ABA5C0 callers, rdis ptr/imm/xr indirect checks, magic-multiplier imm scans, descscan2, BGFX_MAP.md 6gq/6ih/6w/6hi, vt/vcalls, and the visitor's only caller sub_6640ae0 are all negative [V]; the live entry capture oc_u_er6_light_desc cannot install a read/write watch on the pass vectors, and livemem has no pass-object target address [V static]. Description value names also remain unknown [?]: no RTTI or description member-name strings in the release exe; headers use mValue* placeholders; live desc bytes confirm sizes only, never names.

Resolved [V], carried, not re-proven here: tag 2 = GameplayMetadata, tag 3 = LightPoint (FrameBuilder.h wins the group_visitors.md conflict which had 2/3 swapped, corroborated by BGFX_MAP.md 6w line 504); the four end-cursor writers to pass+0x800/+0x648/+0x4A0/+0x1D0.

## TOOL REQUESTS

CAPTURE REQUESTED oc_u_er6_light_desc at visitor entry 0x6640d80 (size 0x100, max 6; queued via request.py add, exit 1 "already queued"; result awaited in docs/data/live/oc_u_er6_light_desc.txt). The entry capture can add runtime desc bytes per tag plus ret= caller chain — bytes only, never member names, no read/write watchpoint, so it cannot close the consumer blocker. What would close consumers: a read/write watchpoint on pass+0x800/+0x648/+0x4A0/+0x1D0 (not available via this tool) or a live pass-object address for livemem (none exists: 0x5ABA5C0 = per-call TLS getter, rdis imm/ptr to 0x5aba5c0 = 0 refs/slots). Helper scripts: None.
