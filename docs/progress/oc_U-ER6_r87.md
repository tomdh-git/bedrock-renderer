## NEXT
DONE

# U-ER6 — R6: LightAmbient / LightDirectional / Light tag 2 / tag 3 / tag 4 (Minecraft.Windows.exe 1.26.62.01)

Goal: close R6 — tag value names, the group_visitors.md vs FrameBuilder.h LightGroupTag tag-name conflict, and the consumers (draining element readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0. `pass` = per-thread value of ThreadLocalObject 0x5ABA5C0 (value at node+0x10); visitor cases call 0x5aba5c0 and receive pass in rsi/rdi [V, carried from oc_U-ER6_r1..r85, verify_oc 83/83].

Conventions: static analysis only; RVAs image-relative; exe never launched; every `0xRVA  instr` line copied verbatim from verified listings (oc_U-ER6_r1..r85) and not re-run. Tags: [V] seen in disassembly (RVA cited) | [I] inferred | [?] unknown | [V live] confirmed by capture bytes / live read.

## 1. Tag -> type / value names (LightGroupTag) — resolved [V] (carried, not re-proven this unit)

| name | offset | size | site / verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| variant tag byte + JT dispatch | variant+0x08 | 1 | `0x6640dc4  movzx eax,byte ptr [rdx+8]`<br>`0x6640de6  jmp rax` | tag byte at variant+0x08 loaded by the Light visitor; dispatch `jmp rax` via jump table 0xF2BF2B0 (entries: 0=0x6640de8 Ambient, 1=0x66415b0 Directional, 2=0x6640f1b GameplayMetadata, 3=0x66410a0 LightPoint, 4=0x6640ec1 ShadowAtlasFrame, 5=0x66417af ServerGraphicsOverrideParameters, 6=0x664187d VoxelVolume, 7=0x6641524 TransitioningVoxelVolume) [V] | [V] |
| tag 0 store | tag 0 store | 1 | `0x53e3511  mov byte ptr [rbp+0x138],0` | LightGroupTag::Ambient = 0 (FrameBuilder.h:79-88); producer clone 0x53e2c00, srcloc RenderLightAmbientDescription (0xF248E70); JT entry 0 [V] | [V] |
| tag 1 store | tag 1 store | 1 | `0x53709d4  mov byte ptr [rbp+0x18],1` | LightGroupTag::Directional = 1; thin clone 0x5370960, srcloc LightDirectionalDescription (0xF248F70); JT entry 1 [V] | [V] |
| tag 2 store | tag 2 store | 1 | `0x53e5fb4  mov byte ptr [rbp-0x18],2`<br>`0x53e5fbf  mov rax,[rax+0x380]` | LightGroupTag::GameplayMetadata = 2; clone 0x53e5910, Light vslot 0x380 insert 0x53e5fbf, srcloc `__FUNCSIG__ ...gamecomponents::GameplayMetadata` (0xF248ED0); JT entry 2 [V] | [V] |
| tag 3 store | tag 3 store | 1 | `0x535a9b7  mov byte ptr [rbp+0x278],3`<br>`0x535a9c1  mov rax,[rax+0x380]`<br>`0x535a9ce  call qword ptr [0xF99FFA0]` | LightGroupTag::LightPoint = 3; light clone 0x53599d0 insert 0x535a9ce, srcloc LightPointDescription (0xF248DA0); JT entry 3 [V] | [V] |
| tag 4 store | tag 4 store | 1 | `0x535a696  mov byte ptr [rbp+0x278],4`<br>`0x535a6a0  mov rax,[rax+0x380]` | LightGroupTag::ShadowAtlasFrame = 4; light clone 0x53599d0 insert 0x535a6a0, srcloc ShadowAtlasFrameDescription (0xF248D80); JT entry 4 [V] | [V] |
| tag-name conflict | tag map (enum doc) | - | FrameBuilder.h:79-88 `enum class LightGroupTag : uint64_t { Ambient = 0, Directional = 1, GameplayMetadata = 2, LightPoint = 3, ShadowAtlasFrame = 4, ServerGraphicsOverrideParameters = 5, VoxelVolume = 6, TransitioningVoxelVolume = 7 };` | CONFLICT RESOLVED [V]: producer tag stores + __FUNCSIG__ srclocs prove tag 2 = GameplayMetadata and tag 3 = LightPoint; FrameBuilder.h wins; group_visitors.md had them swapped (LightPoint@2 / GameplayMetadata@3) and is superseded; tags 5/6/7 = ServerGraphicsOverrideParameters / VoxelVolume / TransitioningVoxelVolume [V]; BGFX_MAP.md 1855-1859 agrees [I from doc] | [V] |

## 2. Light-visitor writers to pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — proven [V] (carried, not re-proven this unit)

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

## 2b. Live data available for this item — [V live]

The standard live-capture target `light_visitor.txt` (rva=0x6640D80, kind=visitor, size=0x300) exists (docs/data/live/README.md CORRECTION 2026-11-15: light visitor takes {desc,tag} in RDX; the earlier dump in docs/data/live_desc_sky_light_effect_1.26.62.01.txt is INVALID). Format per line: `tag descptr hexbytes`. Samples observed: line 3 tag 5 (ServerGraphicsOverrideParameters) descptr 14AA80; line 4 tag 0 (Ambient) descptr 14A5B8; line 5 tag 1 (Directional) descptr 14A400; lines 6-7 tag 2 (GameplayMetadata) descptr 14A5A0 (two samples); line 8 tag 1 (Directional) descptr 14A400. Tags 3 (LightPoint) and 4 (ShadowAtlasFrame) do NOT appear in the captured samples [V live]. This confirms runtime tag dispatch through the visitor entry 0x6640d80 with live description pointers, but the hex dump confirms field sizes/values only, never member value names; and it cannot locate any draining reader of pass+0x800/+0x648/+0x4A0/+0x1D0 (entry sampling installs no read/write watchpoint).

This unit's additional live angle — livemem read-only chain on the ThreadLocalObject (the game was running, pid 13452, base 0x7ff7a59c0000; `python tools/sigs/livemem.py status` OK [V live]): `python tools/sigs/livemem.py chain @0x5ABA5C0 0x10` -> `[0x7ff7ab47a5c0] = 0xEC8348FA53630EE9 (val); +0x10 -> None` [V live]. The TLS slot value is obfuscated (encoded pointer, not a raw VA), and node+0x10 reads as None, so no `pass` object VA is obtainable. livemem `read` requires a real VA and may not scan or loop over ranges [brief rule 30], so no cursor/vector content can be read live either. This cannot close the consumer blocker.

## 2c. What this unit tried (new angle — all blocked)

- `python tools/livecap/request.py result oc_u_er6_light_desc` -> "no result yet (orchestrator has not run it)"; docs/data/live/oc_u_er6_light_desc.txt absent; not listed in docs/data/live/_status.txt (DONE t=120 lists mc_root_4e05e50_callers, oc_u_el6b_desc, l8b_texcreate_record, el10b_lighting_desc only).
- `python tools/livecap/request.py list` -> oc_u_er6_light_desc 0x6640d80 size 0x100 max 6 pending (R6 light-visitor entry producer capture); 4 requests pending (er5_clone_4c8a5b0, l8b_resizetex_slot31, sub_1289440_callers, oc_u_er6_light_desc), so `add` rejects with "4 requests already pending, ask again next unit"; same-name re-add rejected ("already queued"); same-RVA re-add while pending also rejected.
- Even if returned, function-entry sampling installs NO read/write watchpoint on pass+0x800/+0x648/+0x4A0/+0x1D0, so it cannot locate a draining reader; it can only confirm description sizes/caller chain via ret=.
- livemem chain @0x5ABA5C0 0x10 (this unit): TLS slot value obfuscated `0xEC8348FA53630EE9`, `+0x10 -> None`; no `pass` VA obtainable; livemem read needs a VA and may not scan [V live, brief rule 30].
- One additional static angle checked this unit (not in r86): `rdis dis 0xc288880` (endFrame merge named in docs/BGFX_MAP.md 6ih line 1844) — body 0xc288880..0xc28a880 walks offsets 0x4C8/0x5A0/0x710/0x7E8/0x958/0xA30/0xE60/0xF38/0xBE8/0xCC0/0x10C0/0x1198/0x1308/0x13E0 and a stride-0x10 loop at 0xc288990; no read of pass+0x800/+0x648/+0x4A0/+0x1D0 [V].
- All other static consumer angles exhausted and carried (not re-run this unit): whole-image fld --r/--w scans on all four offsets and begin cursors 0x7F8/0x650/0x498/0x1C8; all ~200 `0x5ABA5C0` callers; `rdis ptr`/`imm`/`xr` indirect checks; magic-multiplier imm scans (0xFFFF8E39 /0x48, 0xFFFFCCCD /0x14, 0xFFFF83E1 /0x84 — hits only inside known writers); lea register-relative cursor scan for all cursors = only writer sites; descscan2; scaled-stride imul/scaled-address scan over 0x6600000-0x6700000 = zero hits [V r80]; endFrame sub_66232b0 listing touches none of the four offsets [V]; per-draw code 0x66ea3d0/0x66ecb03 appends u16 indices to pass+0x8A8 only and reads none of the four cursors [V]; `fld 0x8A8 --r` whole-image = 0 [V]; docs/BGFX_MAP.md sections 6gq/6ih/6w/6ee: consumers of ALL pass vectors open [?]; Sky vector pass+0x548 readerless, same blocker [V r80]; vt/vcalls: `rdis fn 0x6640d80` = no vcall slots [V r81-r83].

## 3. Consumers of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — not located [?] (blocking fact)

| name | offset | size | site / verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| pass+0x800 element read | pass+0x800 element read | - | - | no draining element read of the 0x14-byte summary elements anywhere in Minecraft.Windows.exe 1.26.62.01; only the three end-cursor writers in section 2 [V writes only] | [?] |
| pass+0x648 element read | pass+0x648 element read | - | - | no draining element read of the 0x48-byte light-record elements anywhere in the exe [V writes only] | [?] |
| pass+0x4A0 element read | pass+0x4A0 element read | - | - | no draining element read of the 0x84-byte GameplayMetadata elements anywhere in the exe [V writes only] | [?] |
| pass+0x1D0 element read | pass+0x1D0 element read | - | - | no draining element read of the 0x50-byte ShadowAtlasFrame elements anywhere in the exe [V writes only] | [?] |

## 4. Description field value names — offsets/sizes [V], semantic names [?] (pending)

| name | offset | size | site / verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| description member value names | descriptions (all fields) | - | `0x66418f0  mov rbx,[rsi+0x40]`<br>`0x6640f01  mov rcx,[rsi+0x48]` | read offsets/sizes proven [V]: tag-3 LightPoint reads the description through +0x100 (>=0x104 B, three shared handles, not typed); tag-4 ShadowAtlasFrame = 0x50 B (+0x00/+0x10/+0x20/+0x30 movups rows, +0x40 ptr, +0x48 shared ctrl); tag-2 GameplayMetadata = 0x84 B verbatim copy into pass+0x4A0. Member VALUE NAMES unknown [?]: release exe has no RTTI and no description member-name strings; LightDescriptions.h types every field as mValue* placeholders with static_assert offsets only; live capture bytes (light_visitor.txt lines 2-8) confirm sizes/values, never names. | [?] |

## CLOSES?

CLOSES? NO — single blocking fact: no draining reader (element consumer) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 exists anywhere in Minecraft.Windows.exe 1.26.62.01; all four offsets are write-only statically (end-cursor increments / grow-emplace / element copies at the end cursor only, no pop/decrement, no element-indexed read) [V]; every static consumer angle is negative [V] (whole-image fld --r/--w scans, all 0x5ABA5C0 callers, rdis ptr/imm/xr indirect checks, magic-multiplier imm scans, lea cursor scan, descscan2, docs/BGFX_MAP.md 6gq/6ih/6w/6ee, fld 0x8A8 --r scan, scaled-stride scan over 0x6600000-0x6700000, endFrame sub_66232b0, endFrame merge 0xc288880, per-draw 0x66ea3d0/0x66ecb03, vt/vcalls no vcall slots); the live tools available cannot close it: oc_u_er6_light_desc is still pending (result absent, 4/4 slots full, duplicate rejected) and even when returned it installs no write watch on the four cursors; light_visitor.txt samples tags 0/1/2/5 only (no tag 3/4, no ret= chain); livemem chain @0x5ABA5C0 0x10 yields an obfuscated TLS value + `+0x10 -> None` (no pass VA), read needs a VA and may not scan [V live], so no read/write watch is possible and the consumers cannot be located statically or via the available live tools [I]. Description member value names also remain unknown [?]: no RTTI or description member-name strings; headers use mValue* placeholders; live bytes confirm sizes/values only.

Resolved [V] and carried, not re-proven this unit: tag 2 = GameplayMetadata, tag 3 = LightPoint (FrameBuilder.h wins the group_visitors.md conflict; group_visitors.md had them swapped); the four end-cursor writers to pass+0x800/+0x648/+0x4A0/+0x1D0 [V].

## TOOL REQUESTS

CAPTURE REQUESTED oc_u_er6_light_desc — already pending at visitor entry 0x6640d80 (size 0x100, max 6); 4/4 pending slots used, do NOT re-add (duplicate name rejected); docs/data/live/oc_u_er6_light_desc.txt absent and not in _status.txt DONE list. Result absent ("no result yet"); when returned it can confirm tag-3/tag-4 description sizes/caller chain [V live] but cannot close the consumer blocker (no read/write watch available, entry sampling only). Helper scripts: None.

Next: run `python tools/delegate.py check docs/progress/oc_U-ER6.md` and fix every failure; only when it exits 0 set line 2 ("## NEXT" follower) to DONE.
