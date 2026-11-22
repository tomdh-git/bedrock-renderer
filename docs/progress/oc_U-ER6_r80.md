## NEXT
DONE

# U-ER6 — R6: LightAmbient / LightDirectional / Light tag 2 / tag 3 / tag 4 (Minecraft.Windows.exe 1.26.62.01)

Goal (checklist item): tag value names, the group_visitors.md vs FrameBuilder.h LightGroupTag tag-name conflict, and the consumers (draining element readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0. `pass` = per-thread value of ThreadLocalObject 0x5ABA5C0 (value at node+0x10); visitor cases call 0x5ABA5C0 and receive pass in rsi/rdi [V, carried from oc_U-ER6_r1..r79; every `0xRVA  instr` quote below was re-copied verbatim from verified listings and passes tools/sigs/verify_oc.py]. RETRY #3: oc_U-ER6_r1-r79 carry all [V] proofs and are NOT re-run; this unit does ONLY what new data can add: (a) check the pending live capture oc_u_er6_light_desc (visitor entry 0x6640d80) — result not yet returned, so nothing [V live] can be added; (b) one genuinely new static consumer angle — a scaled-stride element-address scan over 0x6600000-0x6700000 (visitor + per-draw region), the only element-address class `fld` cannot see; (c) re-read docs/BGFX_MAP.md sections 6gq/6ih/6w/6ee for consumer info. Static analysis only; exe never launched; RVAs image-relative; no `0xRVA  instr` line here that was not verified with rdis. Tags: [V] seen in disassembly | [I] inferred | [?] unknown | [V live] confirmed by capture bytes / live read.

## 1. Tag -> type / value names (LightGroupTag) and tag-name conflict — resolved [V] (carried, not re-run)

| offset | size | site / verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|
| variant+0x08 tag byte | 1 | `0x6640dc4  movzx eax,byte ptr [rdx+8]`<br>`0x6640de6  jmp rax` | tag byte at variant+0x08; dispatch `jmp rax` via jump table 0xF2BF2B0 (entries: 0=0x6640de8 Ambient, 1=0x66415b0 Directional, 2=0x6640f1b GameplayMetadata, 3=0x66410a0 LightPoint, 4=0x6640ec1 ShadowAtlasFrame, 5=0x66417af ServerGraphicsOverrideParameters, 6=0x664187d VoxelVolume, 7=0x6641524 TransitioningVoxelVolume) [V] | [V] |
| tag 0 store | 1 | `0x53e3511  mov byte ptr [rbp+0x138],0` | LightGroupTag::Ambient = 0; clone 0x53e2c00, srcloc RenderLightAmbientDescription (0xF248E70); JT entry 0 [V] | [V] |
| tag 1 store | 1 | `0x53709d4  mov byte ptr [rbp+0x18],1` | LightGroupTag::Directional = 1; thin clone 0x5370960, srcloc LightDirectionalDescription (0xF248F70); JT entry 1 [V] | [V] |
| tag 2 store | 1 | `0x53e5fb4  mov byte ptr [rbp-0x18],2`<br>`0x53e5fbf  mov rax,[rax+0x380]` | LightGroupTag::GameplayMetadata = 2; clone 0x53e5910, Light vslot 0x380 insert 0x53e5fbf, srcloc `__FUNCSIG__ ...gamecomponents::GameplayMetadata` (0xF248ED0); JT entry 2 [V] | [V] |
| tag 3 store | 1 | `0x535a9b7  mov byte ptr [rbp+0x278],3`<br>`0x535a9c1  mov rax,[rax+0x380]`<br>`0x535a9ce  call qword ptr [0xF99FFA0]` | LightGroupTag::LightPoint = 3; light clone 0x53599d0 insert 0x535a9ce, srcloc LightPointDescription (0xF248DA0); JT entry 3 [V] | [V] |
| tag 4 store | 1 | `0x535a696  mov byte ptr [rbp+0x278],4`<br>`0x535a6a0  mov rax,[rax+0x380]` | LightGroupTag::ShadowAtlasFrame = 4; light clone 0x53599d0 insert 0x535a6a0, srcloc ShadowAtlasFrameDescription (0xF248D80); JT entry 4 [V] | [V] |
| tag-name conflict | - | FrameBuilder.h:79-88 `enum class LightGroupTag : uint64_t { Ambient = 0, Directional = 1, GameplayMetadata = 2, LightPoint = 3, ShadowAtlasFrame = 4, ServerGraphicsOverrideParameters = 5, VoxelVolume = 6, TransitioningVoxelVolume = 7 };` | CONFLICT RESOLVED [V]: producer tag stores + __FUNCSIG__ srclocs prove tag 2 = GameplayMetadata and tag 3 = LightPoint; FrameBuilder.h wins; group_visitors.md had them swapped (LightPoint@2 / GameplayMetadata@3) and is superseded. Tags 5/6/7 = ServerGraphicsOverrideParameters / VoxelVolume / TransitioningVoxelVolume [V]; BGFX_MAP.md 504/2038 agree (Light 2/3/4/5/6/7) [I from doc] | [V] |

## 2. Light-visitor writers to pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — proven [V] (carried, not re-run)

Pass-object vectors (begin/end/cap cursors): summary +0x7F8/+0x800/+0x808 stride 0x14; light records +0x648/+0x650 stride 0x48; GameplayMetadata +0x498/+0x4A0/+0x4A8 stride 0x84; ShadowAtlasFrame +0x1C8/+0x1D0/+0x1D8 stride 0x50 [V]. Every write below is an end-cursor increment / grow-emplace / element copy at the end cursor; no end-cursor pop/decrement exists anywhere in the exe [V, whole-image `fld --w` scans].

| offset | size | site / verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|
| pass+0x800 end cursor | 8 | `0x6640e84  mov rdx,[rsi+0x800]`<br>`0x6640e8b  cmp rdx,[rsi+0x808]`<br>`0x6640eb4  add qword ptr [rsi+0x800],0x14` | end cursor of the 0x14-byte summary list (cap +0x808); end += stride 0x14 per element; writers: Ambient 0x6640eb4, Directional 0x66417a2, LightPoint 0x6641517; loads at 0x6640e84 / 0x6641761 [V] | [V] |
| pass+0x808 cap cursor | 8 | `0x6640e8b  cmp rdx,[rsi+0x808]` | summary list cap cursor, compared against end at 0x6640e8b [V] | [V] |
| pass+0x648 end cursor | 8 | `0x66416f8  lea rcx,[rsi+0x648]`<br>`0x66416ff  call 0x675FB30`<br>`0x664145a  lea rcx,[rsi+0x648]`<br>`0x6641461  call 0x675FB30` | begin cursor of the 0x48-byte light-record vector (end +0x650); vector grow-emplace 0x675FB30 with &pass+0x648; writers: LightPoint 0x6641461, Directional 0x66416ff [V] | [V] |
| pass+0x650 light-record index | 4 | `0x6641729  mov eax,[rsi+0x650]`<br>`0x6641735  shr eax,3`<br>`0x6641738  imul eax,0xFFFF8E39` | light-record end cursor; index = (end - begin)/0x48 - 1 (0xFFFF8E39 = magic divide by 0x48) [V] | [V] |
| pass+0x4A0 end cursor | 8 | `0x6640f78  mov r12,[rdi+0x4A0]`<br>`0x6641090  add qword ptr [rdi+0x4A0],0x84` | end cursor of the 0x84-byte GameplayMetadata vector (begin +0x498, cap +0x4A8); end += stride 0x84; tag-2 writer at 0x6641090 [V] | [V] |
| pass+0x4A8 cap cursor | 8 | `0x6640f7f  cmp r12,[rdi+0x4A8]` | GameplayMetadata cap cursor [V] | [V] |
| pass+0x1D0 end cursor | 8 | `0x6641991  mov r14,[rsi+0x1D0]`<br>`0x6641998  cmp r14,[rsi+0x1D8]`<br>`0x66419c6  add qword ptr [rsi+0x1D0],0x50` | end cursor of the 0x50-byte ShadowAtlasFrame vector (begin +0x1C8, cap +0x1D8); end += stride 0x50; tag-4 writer at 0x66419c6; element copy rows at 0x66419a5-0x66419bc write at [r14] = end cursor only [V] | [V] |

## 3. Consumers of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — not located [?] (blocking fact)

New static angle this unit (the one class `fld` cannot see): scaled-stride element-address scan over 0x6600000-0x6700000 (visitor + per-draw region; 234,831 instruction lines, dump held at C:\Users\Atomi\AppData\Local\Temp\opencode\er6_text_6600000_6700000.list): zero `imul reg, imm` with stride immediate 0x14 / 0x48 / 0x50 / 0x84 and zero scaled addressing `[base+index*scale+disp]` with disp 0x800 / 0x648 / 0x4A0 / 0x1D0 / 0x7F8 / 0x650 / 0x498 / 0x4A8 / 0x1C8 / 0x1D8 [V]. Negative.

docs/BGFX_MAP.md re-read (sections 6gq/6ih/6w/6ee): consumers of ALL pass vectors are open [?] — line 1843-1844: Sky vector at pass+0x548 also readerless, same blocker; line 1855-1859: light vectors fed by the visitor are +0x1D0 (tag 4), +0x260 (tag 5), +0x4A0 (tag 2), +0x648 (directional records), +0x800 (summaries); tag-3 case 0x66410a0 reads the description through +0x100 (>=0x104 B [V]) but its queue target is not decoded; line 2035-2041: consumers of the new pass vectors (DrawItem words +0x08/+0x94/+0xAA/+0xAE/+0xA2) open [?]. The merge path is endFrame 0x66232b0 / 0xc288880; endFrame touches none of the four offsets [V, carried].

Carried negatives [V] (not re-run): whole-image `fld --r/--w` scans for all four offsets and begin cursors 0x7F8/0x650/0x498/0x1C8; all ~200 `0x5ABA5C0` callers; `rdis ptr 0x5aba5c0` = 0 indirect slots; `rdis imm 0x5aba5c0` = 0 static refs; `rdis xr 0x6640d80` = single caller 0x6640c44; `rdis fn 0x6640d80` = no vcall slots; `rdis callees 0x5aba5c0/0x5aba6d0` = TLS/grow-only; magic-multiplier imm scans (0xFFFF8E39 ÷0x48, 0xFFFFCCCD ÷0x14, 0xFFFF83E1 ÷0x84) = hits only inside known writers; lea register-relative scan for all cursors = only writer sites; endFrame sub_66232b0 listing (0x66232b0..0x662e680) and per-draw code 0x66ea3d0/0x66ecb03 (appends u16 indices to pass+0x8A8 only, reads none of the four cursors) [V]. `fld 0x8A8 --r` whole-image = 0 hits in visitor/endFrame/per-draw space [V].

| offset | size | site / verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|
| pass+0x800 element read | - | - | no draining element read of the 0x14-byte summary elements anywhere in Minecraft.Windows.exe 1.26.62.01; only the three end-cursor writers in section 2 [V writes only] | [?] |
| pass+0x648 element read | - | - | no draining element read of the 0x48-byte light-record elements anywhere in the exe [V writes only] | [?] |
| pass+0x4A0 element read | - | - | no draining element read of the 0x84-byte GameplayMetadata elements anywhere in the exe [V writes only] | [?] |
| pass+0x1D0 element read | - | - | no draining element read of the 0x50-byte ShadowAtlasFrame elements anywhere in the exe [V writes only] | [?] |

## 4. Description field value names — offsets/sizes [V], semantic names [?] (pending)

| offset | size | site / verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|
| description member value names | - | `0x66418f0  mov rbx,[rsi+0x40]`<br>`0x6640f01  mov rcx,[rsi+0x48]` | read offsets/sizes proven [V]: ShadowAtlasFrame tag 4 = 0x50 B (+0x00/+0x10/+0x20/+0x30 movups rows, +0x40 ptr, +0x48 shared ctrl); LightPoint tag 3 >= 0x104 B (reads through +0x100, three shared handles, not typed); GameplayMetadata tag 2 = 0x84 B (verbatim copy into pass+0x4A0). Member VALUE NAMES unknown [?]: release exe has no RTTI and no description member-name strings; LightDescriptions.h / LightGameDescriptions.h type every field as mValue* placeholders with static_assert offsets only; live capture bytes confirm sizes/values, never names. | [?] |

## 5. Live capture (2026-11-22 tool) — pending, nothing [V live] added yet

- `oc_u_er6_light_desc` (visitor entry 0x6640d80, RDX = desc pointer per docs/data/live/README.md correction, size 0x100, max 6) is state=pending in docs/progress/capture_requests.json; `python tools/livecap/request.py result oc_u_er6_light_desc` = "no result yet (orchestrator has not run it)"; docs/data/live/oc_u_er6_light_desc.txt absent; docs/data/live/_status.txt (DONE t=120) does not list it. Four captures are pending = limit reached; `request.py add` rejects a duplicate name, so it is NOT re-added here.
- What it can add [V live when available]: description bytes at entry to confirm tag-3 (>=0x104 B [V] static) / tag-4 (0x50 B [V] static) field sizes/runtime values vs Descriptions.h, plus `ret=` naming the visitor caller chain.
- What it CANNOT add: the consumers — function-entry sampling installs no read/write watchpoint on pass+0x800/+0x648/+0x4A0/+0x1D0, so no available live angle can locate a draining reader. livemem is not an alternative: no static pass-object target address exists (`rdis imm 0x5aba5c0` = 0 refs; `rdis ptr` = 0 slots) and livemem may not scan or loop over ranges [V static]. The blocking fact below stands regardless of capture outcome [I, tool capability].

## CLOSES?

CLOSES? NO — single blocking fact: no draining reader (element consumer) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 exists anywhere in Minecraft.Windows.exe 1.26.62.01; all four offsets are write-only statically (end-cursor increments / grow-emplace / element copies at the end cursor only, no pop/decrement, no element-indexed read) [V]; whole-image `fld --r/--w` scans, all `0x5ABA5C0` callers, `rdis ptr`/`imm`/`xr` indirect checks, magic-multiplier imm scans, the lea register-relative scan, descscan2, BGFX_MAP.md 6gq/6ih/6w/6ee, the `fld 0x8A8 --r` scan, and this unit's scaled-stride imul/scaled-address scan over 0x6600000-0x6700000 are all negative [V]. The pending entry-sampling capture cannot install a write watch on the four cursors and livemem has no target [I], so the consumers cannot be located statically. Description value names also remain unknown [?]: no RTTI or description member-name strings; headers use mValue* placeholders; live bytes confirm sizes only. Resolved [V] and carried, not re-proven this unit: tag 2 = GameplayMetadata, tag 3 = LightPoint (FrameBuilder.h wins the group_visitors.md conflict); the four end-cursor writers to pass+0x800/+0x648/+0x4A0/+0x1D0 [V].

## TOOL REQUESTS

CAPTURE REQUESTED oc_u_er6_light_desc — already pending at visitor entry 0x6640d80 (size 0x100, max 6) in docs/progress/capture_requests.json; do NOT re-add (duplicate name rejected, 4/4 pending slots used). Awaiting docs/data/live/oc_u_er6_light_desc.txt via `python tools/livecap/request.py result oc_u_er6_light_desc`; when returned it can confirm description sizes/caller chain [V live] but cannot close the consumer blocker (no read/write watch available, entry sampling only). Helper scripts: None.
