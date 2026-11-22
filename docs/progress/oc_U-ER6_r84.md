## NEXT
DONE

# U-ER6 — R6: LightAmbient / LightDirectional / Light tag 2 / tag 3 / tag 4 (Minecraft.Windows.exe 1.26.62.01)

Goal: close R6 — tag value names, the group_visitors.md vs FrameBuilder.h LightGroupTag tag-name conflict, and the consumers (draining element readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0. `pass` = per-thread value of ThreadLocalObject 0x5ABA5C0 (value at node+0x10); visitor cases call 0x5ABA5C0 and receive pass in rsi/rdi [V, carried from oc_U-ER6_r1..r83, verify_oc 83/83].

Conventions: static analysis only; RVAs image-relative; exe never launched; every `0xRVA  instr` line copied verbatim from verified listings (r1-r83) and not re-run. Tags: [V] seen in disassembly (RVA cited) | [I] inferred | [?] unknown | [V live] confirmed by capture bytes / live read (docs/data/live/light_visitor.txt — livecap.lua visitor capture of the same target as the pending request.py capture oc_u_er6_light_desc, visitor entry 0x6640D80, arg {desc,tag} in RDX per README CORRECTION 2026-11-15; 6 samples: tags 5, 0, 1, 2, 2, 1 at descptrs 0x14AA80, 0x14A5B8, 0x14A400, 0x14A5A0, 0x14A5A0, 0x14A400).

## 1. Tag -> type / value names (LightGroupTag) and tag-name conflict — resolved [V] (carried from oc_U-ER6_r1..r83, not re-proven this unit)

| name | offset | size | site / verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| variant tag byte + JT dispatch | variant+0x08 | 1 | `0x6640dc4  movzx eax,byte ptr [rdx+8]`<br>`0x6640de6  jmp rax` | tag byte at variant+0x08 loaded by the Light visitor; dispatch `jmp rax` via jump table 0xF2BF2B0 (entries: 0=0x6640de8 Ambient, 1=0x66415b0 Directional, 2=0x6640f1b GameplayMetadata, 3=0x66410a0 LightPoint, 4=0x6640ec1 ShadowAtlasFrame, 5=0x66417af ServerGraphicsOverrideParameters, 6=0x664187d VoxelVolume, 7=0x6641524 TransitioningVoxelVolume) [V] | [V] |
| tag 0 store | tag 0 store | 1 | `0x53e3511  mov byte ptr [rbp+0x138],0` | LightGroupTag::Ambient = 0 (FrameBuilder.h:79-88); producer clone 0x53e2c00, srcloc RenderLightAmbientDescription (0xF248E70); JT entry 0 [V] | [V] |
| tag 1 store | tag 1 store | 1 | `0x53709d4  mov byte ptr [rbp+0x18],1` | LightGroupTag::Directional = 1; thin clone 0x5370960, srcloc LightDirectionalDescription (0xF248F70); JT entry 1 [V] | [V] |
| tag 2 store | tag 2 store | 1 | `0x53e5fb4  mov byte ptr [rbp-0x18],2`<br>`0x53e5fbf  mov rax,[rax+0x380]` | LightGroupTag::GameplayMetadata = 2; clone 0x53e5910, Light vslot 0x380 insert 0x53e5fbf, srcloc `__FUNCSIG__ ...gamecomponents::GameplayMetadata` (0xF248ED0); JT entry 2 [V] | [V] |
| tag 3 store | tag 3 store | 1 | `0x535a9b7  mov byte ptr [rbp+0x278],3`<br>`0x535a9c1  mov rax,[rax+0x380]`<br>`0x535a9ce  call qword ptr [0xF99FFA0]` | LightGroupTag::LightPoint = 3; light clone 0x53599d0 insert 0x535a9ce, srcloc LightPointDescription (0xF248DA0); JT entry 3 [V] | [V] |
| tag 4 store | tag 4 store | 1 | `0x535a696  mov byte ptr [rbp+0x278],4`<br>`0x535a6a0  mov rax,[rax+0x380]` | LightGroupTag::ShadowAtlasFrame = 4; light clone 0x53599d0 insert 0x535a6a0, srcloc ShadowAtlasFrameDescription (0xF248D80); JT entry 4 [V] | [V] |
| tag-name conflict | tag map (enum doc) | - | FrameBuilder.h:79-88 `enum class LightGroupTag : uint64_t { Ambient = 0, Directional = 1, GameplayMetadata = 2, LightPoint = 3, ShadowAtlasFrame = 4, ServerGraphicsOverrideParameters = 5, VoxelVolume = 6, TransitioningVoxelVolume = 7 };` | CONFLICT RESOLVED [V]: producer tag stores + __FUNCSIG__ srclocs prove tag 2 = GameplayMetadata and tag 3 = LightPoint; FrameBuilder.h wins; group_visitors.md had them swapped (LightPoint@2 / GameplayMetadata@3) and is superseded; tags 5/6/7 = ServerGraphicsOverrideParameters / VoxelVolume / TransitioningVoxelVolume [V]; BGFX_MAP.md 1855-1859 agrees [I from doc] | [V] |

## 2. Light-visitor writers to pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — proven [V] (carried from oc_U-ER6_r1..r83, not re-proven this unit)

Pass-object vectors (begin/end/cap cursors): summary +0x7F8/+0x800/+0x808 stride 0x14; light records +0x648/+0x650 stride 0x48; GameplayMetadata +0x498/+0x4A0/+0x4A8 stride 0x84; ShadowAtlasFrame +0x1C8/+0x1D0/+0x1D8 stride 0x50 [V]. Every write below is an end-cursor increment / grow-emplace / element copy at the end cursor; no end-cursor pop/decrement exists anywhere in the exe [V, whole-image fld --w scans].

| name | offset | size | site / verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| pass+0x800 end cursor | pass+0x800 | 8 | `0x6640e84  mov rdx,[rsi+0x800]`<br>`0x6640e8b  cmp rdx,[rsi+0x808]`<br>`0x6640eb4  add qword ptr [rsi+0x800],0x14`<br>`0x6641761  mov rdx,[rsi+0x800]`<br>`0x66417a2  add qword ptr [rsi+0x800],0x14`<br>`0x6641517  add qword ptr [rsi+0x800],0x14` | end cursor of the 0x14-byte summary list (cap +0x808); end += stride 0x14 per element; writers: Ambient 0x6640eb4, Directional 0x66417a2, LightPoint 0x6641517; loads at 0x6640e84 / 0x6641761 [V] | [V] |
| pass+0x808 cap cursor | pass+0x808 | 8 | `0x6640e8b  cmp rdx,[rsi+0x808]` | summary list cap cursor, compared against end at 0x6640e8b [V] | [V] |
| pass+0x648 begin cursor | pass+0x648 | 8 | `0x66416f8  lea rcx,[rsi+0x648]`<br>`0x66416ff  call 0x675FB30`<br>`0x664145a  lea rcx,[rsi+0x648]`<br>`0x6641461  call 0x675FB30` | begin cursor of the 0x48-byte light-record vector (end +0x650); vector grow-emplace 0x675FB30 with &pass+0x648; writers: LightPoint 0x6641461, Directional 0x66416ff [V] | [V] |
| pass+0x650 end cursor | pass+0x650 | 4 | `0x6641729  mov eax,[rsi+0x650]`<br>`0x6641735  shr eax,3`<br>`0x6641738  imul eax,0xFFFF8E39` | light-record end cursor; index = (end - begin)/0x48 - 1 (0xFFFF8E39 = magic divide by 6 after >>3 => /0x48) [V] | [V] |
| pass+0x4A0 end cursor | pass+0x4A0 | 8 | `0x6640f78  mov r12,[rdi+0x4A0]`<br>`0x6641090  add qword ptr [rdi+0x4A0],0x84`<br>`0x6643198  mov eax,[rdi+0x4A0]` | end cursor of the 0x84-byte GameplayMetadata vector (begin +0x498, cap +0x4A8); end += stride 0x84; tag-2 writer at 0x6641090 [V] | [V] |
| pass+0x4A8 cap cursor | pass+0x4A8 | 8 | `0x6640f7f  cmp r12,[rdi+0x4A8]` | GameplayMetadata cap cursor [V] | [V] |
| pass+0x1D0 end cursor | pass+0x1D0 | 8 | `0x6641991  mov r14,[rsi+0x1D0]`<br>`0x6641998  cmp r14,[rsi+0x1D8]`<br>`0x66419c6  add qword ptr [rsi+0x1D0],0x50` | end cursor of the 0x50-byte ShadowAtlasFrame vector (begin +0x1C8, cap +0x1D8); end += stride 0x50; tag-4 writer at 0x66419c6; element copy writes at [r14] = end cursor only, 0x66419a5-0x66419bc [V] | [V] |
| pass+0x1D8 cap cursor | pass+0x1D8 | 8 | `0x6641998  cmp r14,[rsi+0x1D8]` | ShadowAtlasFrame cap cursor [V] | [V] |

## 3. Consumers of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — not located [?] (blocking fact)

| name | offset | size | site / verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| pass+0x800 element read | pass+0x800 element read | - | - | no draining element read of the 0x14-byte summary elements anywhere in Minecraft.Windows.exe 1.26.62.01; only the three end-cursor writers in section 2 [V writes only] | [?] |
| pass+0x648 element read | pass+0x648 element read | - | - | no draining element read of the 0x48-byte light-record elements anywhere in the exe [V writes only] | [?] |
| pass+0x4A0 element read | pass+0x4A0 element read | - | - | no draining element read of the 0x84-byte GameplayMetadata elements anywhere in the exe [V writes only] | [?] |
| pass+0x1D0 element read | pass+0x1D0 element read | - | - | no draining element read of the 0x50-byte ShadowAtlasFrame elements anywhere in the exe [V writes only] | [?] |

New this unit (live angle; static is exhausted per 2026-11-22 r6 review, no re-run of r80-r83 static negatives):

- `python tools/livecap/request.py result oc_u_er6_light_desc` → "no result yet (orchestrator has not run it)"; docs/data/live/oc_u_er6_light_desc.txt absent [tried again this unit, no data]. The request is already queued at visitor entry 0x6640D80 (size 0x100, max 6); 4/4 pending slots are full (er5_clone_4c8a5b0, l8b_resizetex_slot31, sub_1289440_callers, oc_u_er6_light_desc) and `request.py add` rejects a duplicate name, so no new capture can be requested this unit.
- docs/data/live/light_visitor.txt (livecap.lua same target 0x6640D80, already on disk) read fully: 6 samples, tags 5/0/1/2/2/1 only — tag 3 (LightPoint) and tag 4 (ShadowAtlasFrame) never sampled [V live]. It is function-entry sampling: REG=descptr + description bytes, no ret= caller chain in this file, and crucially it installs NO read/write watchpoint on pass+0x800/+0x648/+0x4A0/+0x1D0, so it cannot locate a draining reader [V live, tool capability].
- livemem is not an alternative: no static pass-object target address exists (`rdis imm 0x5aba5c0` = 0 static refs [V]; `rdis ptr 0x5aba5c0` = 0 indirect slots [V]) and livemem may not scan or loop over ranges [brief rules].
- vt/vcalls: `rdis fn 0x6640d80` = no vcall slots [V r81-r83]. All other static consumer angles from r80-r83 carried, not re-run: whole-image fld --r/--w scans on all four offsets and begin cursors 0x7F8/0x650/0x498/0x1C8; all ~200 0x5ABA5C0 callers; rdis ptr/imm/xr indirect checks; magic-multiplier imm scans (0xFFFF8E39 /0x48, 0xFFFFCCCD /0x14, 0xFFFF83E1 /0x84 — hits only inside known writers); lea register-relative cursor scan = only writer sites; descscan2; scaled-stride imul/scaled-address scan over 0x6600000-0x6700000 = zero hits [V]; endFrame sub_66232b0 listing touches none of the four offsets [V]; per-draw code 0x66ea3d0/0x66ecb03 appends u16 indices to pass+0x8A8 only and reads none of the four cursors [V]; fld 0x8A8 --r whole-image = 0 [V]; docs/BGFX_MAP.md sections 6gq/6ih/6w/6ee: consumers of ALL pass vectors open [?]; Sky vector pass+0x548 readerless, same blocker [V].

Blocking fact restated: no draining element read of the 0x14-byte / 0x48-byte / 0x84-byte / 0x50-byte elements exists anywhere in Minecraft.Windows.exe 1.26.62.01; all four offsets are write-only statically (end-cursor increments / grow-emplace / element copies at the end cursor only, no pop/decrement, no element-indexed read) [V]; no live write watch is available, so the consumers cannot be located statically or via the available live tools [I].

## 4. Description field value names — offsets/sizes [V]; runtime bytes from live capture [V live]; semantic value names [?] (pending)

Read offsets/sizes proven [V] (not re-proven this unit): tag-3 LightPoint reads the description through +0x100 (>=0x104 B, three shared handles, not typed, `0x66418f0  mov rbx,[rsi+0x40]` / `0x6640f01  mov rcx,[rsi+0x48]`); tag-4 ShadowAtlasFrame = 0x50 B (+0x00/+0x10/+0x20/+0x30 movups rows, +0x40 ptr, +0x48 shared ctrl); tag-2 GameplayMetadata = 0x84 B verbatim copy into pass+0x4A0 (`0x6641090  add qword ptr [rdi+0x4A0],0x84`).

New this unit — live capture bytes at visitor entry 0x6640D80 [V live docs/data/live/light_visitor.txt]:

| name | offset | size | site / verbatim proof | meaning | tag |
|---|---|---|---|---|---|
| desc tag 0 (Ambient) | desc tag 0 | 768-byte (0x300) capture buffer | docs/data/live/light_visitor.txt line 3: `0 14A5B8 <hex>` | at visitor entry, descptr 0x14A5B8; first nonzero at +0x10 (u=65536), +0x18 (u=1353144); buffer size is the capture window, not a proven object size [V live] | [V live] |
| desc tag 1 (Directional) | desc tag 1 | 768-byte (0x300) capture buffer | lines 4 and 8: `1 14A400 <hex>` (two samples, same descptr 0x14A400) | +0x00/+0x04/+0x08/+0x0C f=1, +0x18 f=1, both samples identical [V live] | [V live] |
| desc tag 2 (GameplayMetadata) | desc tag 2 | 768-byte (0x300) capture buffer | lines 5-6: `2 14A5A0 <hex>` (two samples, same descptr 0x14A5A0) | +0x00 f=9, +0x04 f=1, +0x08 f=128, +0x0C f=15, +0x10 f=1, +0x14 f=0.5, +0x18 f≈0.11 (differs between samples = per-object data), +0x1C u=4, +0x20 u=18000 [V live]; static size 0x84 B [V] stands; no member names in bytes | [V live] |
| desc tag 5 (ServerGraphicsOverrideParameters) | desc tag 5 | 768-byte (0x300) capture buffer | line 2: `5 14AA80 <hex>` | +0x00 f=1, +0x08 f=0.165108 [V live] | [V live] |
| desc tag 3 (LightPoint) [not sampled] | desc tag 3 | - | absent from all 6 light_visitor.txt samples | runtime size/values not confirmed by live capture; static size >= 0x104 B [V] stands | [?] |
| desc tag 4 (ShadowAtlasFrame) [not sampled] | desc tag 4 | - | absent from all 6 light_visitor.txt samples | runtime size/values not confirmed by live capture; static size 0x50 B [V] stands | [?] |
| description member value names | descriptions (all fields) | - | `0x66418f0  mov rbx,[rsi+0x40]`<br>`0x6640f01  mov rcx,[rsi+0x48]` | member VALUE NAMES unknown [?]: release exe has no RTTI and no description member-name strings; headers type every field as mValue* placeholders with static_assert offsets only; live bytes confirm sizes/values at entry (lines 2-8 above) but carry no names [V live] | [?] |

## CLOSES?

CLOSES? NO — single blocking fact: no draining reader (element consumer) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 exists anywhere in Minecraft.Windows.exe 1.26.62.01; all four offsets are write-only statically (end-cursor increments / grow-emplace / element copies at the end cursor only, no pop/decrement, no element-indexed read) [V]; every static consumer angle is negative [V] (whole-image fld --r/--w scans, all 0x5ABA5C0 callers, rdis ptr/imm/xr indirect checks, magic-multiplier imm scans, lea cursor scan, descscan2, docs/BGFX_MAP.md 6gq/6ih/6w/6ee, fld 0x8A8 --r scan, scaled-stride scan over 0x6600000-0x6700000, endFrame sub_66232b0, per-draw 0x66ea3d0/0x66ecb03, vt/vcalls no vcall slots); the live tools available cannot close it: oc_u_er6_light_desc is still pending (4/4 slots full, duplicate rejected, result absent) and even when returned it installs no write watch on the four cursors; light_visitor.txt samples tags 0/1/2/5 only (no tag 3/4, no ret= chain); livemem has no target and may not scan [I]. Description member value names also remain unknown [?]: no RTTI or description member-name strings; headers use mValue* placeholders; live bytes confirm sizes/values only.

Resolved [V] and carried, not re-proven this unit: tag 2 = GameplayMetadata, tag 3 = LightPoint (FrameBuilder.h wins the group_visitors.md conflict; group_visitors.md had them swapped); the four end-cursor writers to pass+0x800/+0x648/+0x4A0/+0x1D0; tag runtime bytes for tags 0/1/2/5 confirmed [V live] (this unit), tag 3/4 not sampled [?].

## TOOL REQUESTS

CAPTURE REQUESTED oc_u_er6_light_desc — already pending at visitor entry 0x6640D80 (size 0x100, max 6); 4/4 pending slots used, do NOT re-add (duplicate name rejected); docs/data/live/oc_u_er6_light_desc.txt absent. light_visitor.txt (livecap.lua, same target) already on disk and used above [V live]; its 6 samples cover tags 0/1/2/5 only, so tag-3/tag-4 description bytes and any ret= caller chain still require a new capture once a pending slot frees. Helper scripts: None.
