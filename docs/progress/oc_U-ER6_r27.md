## NEXT
DONE

# U-ER6 — R6: LightAmbient / LightDirectional / Light tag 2 / tag 3 / tag 4 (1.26.62.01)

Goal: close R6 — tag value names, the group_visitors.md vs FrameBuilder.h LightGroupTag conflict, and consumers (draining element readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0.
Static analysis only; RVAs image-relative to Minecraft.Windows.exe 1.26.62.01. Every `0xRVA  instr` line is copied verbatim from a listing and passes tools/sigs/verify_oc.py.
Tags: [V] seen in disassembly (RVA cited) | [I] inferred from tool output | [?] unknown | [V live] confirmed by capture bytes / live read.

Input data (read fully, not re-generated): docs/functions/6640d80_light_visitor.md; docs/functions/light_game_descriptions.md; docs/functions/group_visitors.md; docs/functions/5aba5c0.md; docs/data/live/light_visitor.txt; docs/BGFX_MAP.md sections 6gq/6h/6ih/6ib/6hi; src/sdk/mc/deps/minecraft_renderer/framebuilder/FrameBuilder.h (LightGroupTag enum); Descriptions.h.
Prior units (r1-r26, NOT redone per RETRY #1): tag names resolved [V] (tag 2 = GameplayMetadata, tag 3 = LightPoint; FrameBuilder.h wins, group_visitors.md had them swapped); tag-value names unknown [?]; all four pass vectors write-only [V] (light-visitor end-cursor writers proven); no element consumer located by whole-image fld --r/--w scans, endFrame full listing, the three other 0x5ABA5C0 callers (stack locals only), rdis ptr 0x5aba5c0 (no indirect slot). Blocking fact carried in: consumers of pass+0x800/+0x648/+0x4A0/+0x1D0 not located statically — write-only, needs live data.

## 1. Tag -> type / LightGroupTag and the tag-name conflict — RESOLVED [V]

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| variant+0x08 tag | 1 | `0x6640dc4  movzx eax,byte ptr [rdx+8]`<br>`0x6640de6  jmp rax` | tag byte at variant+0x08; dispatch `jmp rax` via jump table 0xF2BF2B0 (entries: 0=0x6640de8, 1=0x66415b0, 2=0x6640f1b, 3=0x66410a0, 4=0x6640ec1, 5=0x66417af, 6=0x664187d, 7=0x6641524) | [V] |
| tag 0 | 1 | `0x53e3511  mov byte ptr [rbp+0x138],0` | LightGroupTag::Ambient = 0 (FrameBuilder.h:79-88); producer clone 0x53e2c00, srcloc 0xF248E70 `FrameBuilder::insert [TDescription = RenderLightAmbientDescription]`; jump-table entry 0 (0x6640de8) | [V] |
| tag 1 | 1 | `0x53709d4  mov byte ptr [rbp+0x18],1` | LightGroupTag::Directional = 1; thin clone 0x5370960, srcloc 0xF248F70 (LightDirectionalDescription); entry 1 (0x66415b0) | [V] |
| tag 2 | 1 | `0x53e5fb4  mov byte ptr [rbp-0x18],2`<br>`0x53e5fbf  mov rax,[rax+0x380]` | LightGroupTag::GameplayMetadata = 2; clone 0x53e5910, Light vslot 0x380 insert 0x53e5fbf, srcloc 0xF248ED0 `__FUNCSIG__ ... gamecomponents::GameplayMetadata`; entry 2 (0x6640f1b) | [V] |
| tag 3 | 1 | `0x535a9b7  mov byte ptr [rbp+0x278],3`<br>`0x535a9c1  mov rax,[rax+0x380]` | LightGroupTag::LightPoint = 3; light clone 0x53599d0 insert 0x535a9c1, srcloc 0xF248DA0 `LightPointDescription`; entry 3 (0x66410a0) | [V] |
| tag 4 | 1 | `0x535a696  mov byte ptr [rbp+0x278],4`<br>`0x535a6a0  mov rax,[rax+0x380]` | LightGroupTag::ShadowAtlasFrame = 4; light clone 0x53599d0 insert 0x535a6a0, srcloc 0xF248D80 `ShadowAtlasFrameDescription`; entry 4 (0x6640ec1) | [V] |
| tag-map conflict | - | FrameBuilder.h:79-88 `enum class LightGroupTag : uint64_t { Ambient = 0, Directional = 1, GameplayMetadata = 2, LightPoint = 3, ShadowAtlasFrame = 4, ServerGraphicsOverrideParameters = 5, VoxelVolume = 6, TransitioningVoxelVolume = 7 };` | CONFLICT RESOLVED [V]: producer tag stores + __FUNCSIG__ srclocs prove tag 2 = GameplayMetadata and tag 3 = LightPoint; FrameBuilder.h wins; group_visitors.md had them swapped and is superseded. Tags 5/6/7 = ServerGraphicsOverrideParameters / VoxelVolume / TransitioningVoxelVolume | [V] |

## 2. Description field value names — UNKNOWN [?]

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| description value names | - | - | LightAmbientDescription (0x18), LightDirectionalDescription (0x24), LightPointDescription (0x108), GameplayMetadataDescription (0x84), ShadowAtlasFrameDescription (0x50): field reads are proven [V] in the visitor cases, but the exe has no RTTI and no description member-name strings; headers type the fields as mValue* placeholders with static_assert offsets only; live dumps carry values only. Producer-side semantics (e.g. Ambient +0x00 copied from Atmosphere +0xA4) are inference [I], not names. Value names: unknown [?] — live capture of description bytes may confirm sizes/field layout [pending] | [?] |

## 3. Light-visitor writers to pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — PROVEN [V] (not redone this unit)

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| pass+0x800 | 8 | `0x6640e84  mov rdx,[rsi+0x800]`<br>`0x6640e8b  cmp rdx,[rsi+0x808]`<br>`0x6640eb4  add qword ptr [rsi+0x800],0x14`<br>`0x6641761  mov rdx,[rsi+0x800]`<br>`0x66417a2  add qword ptr [rsi+0x800],0x14`<br>`0x6641517  add qword ptr [rsi+0x800],0x14` | end cursor of the 0x14-byte summary list (cap +0x808); writers: Ambient 0x6640eb4, Directional 0x66417a2, Point 0x6641517 | [V] |
| pass+0x648 | 8 | `0x66416f8  lea rcx,[rsi+0x648]`<br>`0x66416ff  call 0x675FB30`<br>`0x664145a  lea rcx,[rsi+0x648]`<br>`0x6641461  call 0x675FB30` | end cursor of the 0x48-byte light-record vector (begin +0x648 / end +0x650); writers Directional (0x66416ff) and Point (0x6641461) via 0x675FB30 | [V] |
| pass+0x4A0 | 8 | `0x6640f78  mov r12,[rdi+0x4A0]`<br>`0x6641090  add qword ptr [rdi+0x4A0],0x84` | end cursor of the 0x84-byte GameplayMetadata vector (begin +0x498 / cap +0x4A8); writer tag 2, stride 0x84 | [V] |
| pass+0x1D0 | 8 | `0x66419c6  add qword ptr [rsi+0x1D0],0x50` | end cursor of the 0x50-byte ShadowAtlasFrame vector (begin +0x1C8 / cap +0x1D8); writer tag 4, stride 0x50 | [V] |

Every write is an end-cursor increment; no end-cursor pop/decrement exists anywhere in the exe [V, whole-image fld --w scans, prior units].

## 4. NEW ANGLE THIS UNIT — callers of the pass getter 0x5ABA5C0

`python tools/sigs/xref.py callers 0x5aba5c0` returns 76 direct callers (r26's `rdis xr` reported ~200 and examined only 0x66a6830, 0x66a9d50, 0x66bb7b0 — stack locals only). Newly-revealed callers include 0x66bd430, 0x66bf290, 0x66c1920, 0x66c3840, 0x66c5760, 0x66c7680, 0x66c98e0, 0x66cba10, 0x66cc7a0, 0x66ce8d0, 0x66ea3d0 (per-draw, 0xf430 bytes), 0x670b6e0, 0x6722cb0, 0x67375a0 (clouds), 0x673d150 (flamebillboard/actor prepass), 0x6745440 (weather), and the 0x676xxx–0x67eab80 cluster.

This is covered by the carried [V] whole-image `fld --r/--w` scan for 0x800/0x648/0x4A0/0x1D0 (+ begin cursors 0x7F8/0x650/0x498/0x1C8), which is whole-image and therefore covers all 76 callers. It found only the four writer cursor accesses above — no `[reg + 0x800/0x648/0x4A0/0x1D0]` element read, no `[reg + begin-cursor]` begin load. So none of the newly-revealed callers drains the vectors: a consumer receiving vector pointers as register arguments would still have to load [pass+0x648], which fld shows does not happen as a read.

descscan2 on the GameplayMetadata case 0x6640f1b (prior unit) shows reads ONLY at desc+0x00..+0x84 (description fields copied into pass+0x4A0), NO reads of pass+0x4A0 or any other pass offset — the case copies description data INTO the pass, never reads pass elements [V, tools/sigs/descscan2.py output].

livemem: the game IS running (pid 13452, base 0x7ff7a59c0000, version OK) [V live, `python tools/sigs/livemem.py status`], but there is no static pass-object target address (0x5ABA5C0 is a ThreadLocalObject getter computed per call as rcx = frameCtx+0x10+0x9D0 -> node+0x10 value); livemem cannot scan/loop over ranges and has no watchpoint capability, so no livemem read was issued [V static]. The pending entry capture oc_u_er6_light_desc dumps description bytes at visitor entry, not pass-vector accesses — it cannot install a read/write watch on pass+0x800/+0x648/+0x4A0/+0x1D0.

## 5. Consumers of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — NOT LOCATED [?]

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| pass+0x800 elements | - | - | no draining element read of the 0x14-byte summary vector anywhere in Minecraft.Windows.exe 1.26.62.01; end-cursor increment writes only; whole-image fld --r scans negative [V negative] | [?] |
| pass+0x648 elements | - | - | no draining element read of the 0x48-byte light-record vector anywhere in the exe; writes are grow-emplace calls to 0x675FB30 only [V negative] | [?] |
| pass+0x4A0 elements | - | - | no draining element read of the 0x84-byte GameplayMetadata vector anywhere in the exe; writes are end-cursor increments only [V negative] | [?] |
| pass+0x1D0 elements | - | - | no draining element read of the 0x50-byte ShadowAtlasFrame vector anywhere in the exe; writes are end-cursor increments only [V negative] | [?] |

Negative angles already proven (NOT redone): whole-image fld --r/--w scans for all four offsets + begin cursors (0x7F8/0x650/0x498/0x1C8) show only the four writer cursor accesses plus stack/unrelated same-offset hits; endFrame full listing (sub_66232b0) contains none of the four offsets though it calls 0x5ABA5C0 3x; the three other direct 0x5ABA5C0 callers (0x66a6830, 0x66a9d50, 0x66bb7b0) touch only stack locals; rdis ptr 0x5aba5c0 finds no indirect caller slot; per-draw code 0x66ea3d0 appends to pass+0x8A8 only. No function loads a pass cursor and reads [cursor_reg + index*stride]. BGFX_MAP.md 6ih line 1843-1844: Sky vector at pass+0x548 also finds no reader in a 0x6600000-0x6800000 scan — same consumer blocker for all pass vectors; 6ih line 2041: consumers of the new pass vectors are open [?]; line 2033: roles of the pools (consumer: U-PASS3's 0xBB.. task bodies) open [I from BGFX_MAP.md].

## 6. Live capture status

Request oc_u_er6_light_desc (visitor entry 0x6640D80, size 0x100, max 6, state pending, result awaited in docs/data/live/oc_u_er6_light_desc.txt): RDX = desc pointer at entry (docs/data/live/README.md CORRECTION 2026-11-15: light visitor takes {desc,tag} in RDX). `python tools/livecap/request.py result oc_u_er6_light_desc` -> "no result yet (orchestrator has not run it)" [V live, request.py result command]. Existing live dump docs/data/live/light_visitor.txt shows tags 5/0/1/2/2/1 across its samples — no tag 3 (LightPoint) or tag 4 (ShadowAtlasFrame) sample yet [V live, docs/data/live/light_visitor.txt header + sample lines].

What the live data CAN add [V live when the orchestrator runs it]: description bytes per tag at visit time -> confirm field sizes/runtime values for tag 3 (0x108 B) and tag 4 (0x50 B) vs Descriptions.h layouts; ret= at entry names the visitor caller chain.

What it CANNOT add (it is not a write-watch): it observes description bytes at visitor entry, not later reads of the pass vectors, so it cannot locate consumers of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — that needs a memory read/write watch on those element offsets, which this tool does not provide. Description value names also cannot come from live capture (values only, no names; no RTTI/name strings exist in the exe).

## CLOSES?

CLOSES? NO — single blocking fact: no draining reader (element consumer) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 exists anywhere in Minecraft.Windows.exe 1.26.62.01; all four vectors are write-only statically (end-cursor increments only, no pop/decrement, no element-indexed read) [V negative]; whole-image fld scans, the endFrame listing 0x66232b0, all ~200 0x5ABA5C0 callers (xref.py now shows 76 direct callers, all covered by fld), rdis ptr/imm/xr indirect checks, descscan2 on the GameplayMetadata case, and write-site epilogue disassembly are all negative [V]; the pending live entry capture cannot install a read/write watch on the pass vectors, and livemem has no pass-object target address [V static]. Description value names also remain unknown [?]: no RTTI or description member-name strings in the release exe; headers use mValue* placeholders; live desc bytes confirm sizes only, never names.
Resolved [V], carried, not re-proven here: tag 2 = GameplayMetadata, tag 3 = LightPoint (FrameBuilder.h wins the group_visitors.md conflict which had 2/3 swapped); the four end-cursor writers to pass+0x800/+0x648/+0x4A0/+0x1D0 [V].

## TOOL REQUESTS

CAPTURE REQUESTED oc_u_er6_light_desc — already pending at visitor entry 0x6640D80 (size 0x100, max 6; result awaited in docs/data/live/oc_u_er6_light_desc.txt). Queue full at 4 pending (er5_clone_4c8a5b0, l8b_resizetex_slot31, sub_1289440_callers, oc_u_er6_light_desc) so no new `add` this unit. The entry capture can add runtime desc bytes (which tags land in 6 samples is not controllable; no tag 3/4 bytes exist in any capture yet) plus ret= caller chain — bytes only, never member names, no read/write watchpoint, so it cannot close the consumer blocker. What would close consumers: a read/write watchpoint on pass+0x800/+0x648/+0x4A0/+0x1D0 (not available via this tool) or a live pass-object address for livemem (none exists: 0x5ABA5C0 has no static data or indirect-slot references). Helper scripts: None.
