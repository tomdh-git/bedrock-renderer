## NEXT
DONE

# U-ER6 — R6: LightAmbient / LightDirectional / Light tag 2 / tag 3 / tag 4 (1.26.62.01)

Goal: close R6 — description value names, the group_visitors.md vs FrameBuilder.h LightGroupTag tag-name conflict, and the consumers (draining element readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0. RETRY #2: oc_U-ER6_r1-r76 carry all [V] proofs and are NOT re-run; this unit adds only genuinely new static angles (endFrame pass-acquisition sites, per-draw dispatch 0x66ea3d0 region, whole-image fld 0x8A8 --r) and reports CLOSES? honestly. Static analysis only; exe never launched; RVAs image-relative to Minecraft.Windows.exe 1.26.62.01; every `0xRVA  instr` line copied verbatim from verified listings. Tags: [V] seen in disassembly (RVA cited) | [I] inferred | [?] unknown | [V live] confirmed by capture bytes / live read.

Input data (read fully, not re-generated): docs/functions/6640d80_light_visitor.md; docs/functions/5aba5c0.md (ThreadLocalObject::get; pass object = value at node+0x10); docs/functions/group_visitors.md (superseded on tags 2/3); docs/functions/light_game_descriptions.md (pass-vector table); docs/data/live/README.md; docs/data/live/_status.txt; docs/data/live/light_visitor.txt; docs/progress/capture_requests.json; docs/progress/oc_U-ER6_r1-r76.md (carried); docs/BGFX_MAP.md sections 6gq/6ih/6w/6ee; src/sdk/mc/deps/minecraft_renderer/framebuilder/FrameBuilder.h (LightGroupTag enum, lines 79-88); Descriptions.h / LightDescriptions.h / LightGameDescriptions.h.

The pass object is the per-thread value of ThreadLocalObject 0x5ABA5C0 (value at node+0x10). Visitor cases call 0x5ABA5C0 with rcx = frameCtx+0x10+0x9D0 and get rsi = pass [V]. All four vectors live inside this pass object: begin/end/cap cursors at (+0x7F8/+0x800/+0x808) summary stride 0x14, (+0x648/+0x650) light-record stride 0x48, (+0x498/+0x4A0/+0x4A8) GameplayMetadata stride 0x84, (+0x1C8/+0x1D0/+0x1D8) ShadowAtlasFrame stride 0x50 [V, from the light-visitor listings].

## 1. Tag -> type / value names (LightGroupTag) and tag-name conflict — RESOLVED [V] (carried from oc_U-ER6_r1-r76, not re-run)

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| variant+0x08 tag | 1 | `0x6640dc4  movzx eax,byte ptr [rdx+8]` | tag byte at variant+0x08; dispatch `jmp rax` via jump table 0xF2BF2B0 (entries: 0=0x6640de8 Ambient, 1=0x66415b0 Directional, 2=0x6640f1b GameplayMetadata, 3=0x66410a0 LightPoint, 4=0x6640ec1 ShadowAtlasFrame, 6=0x664187d VoxelVolume, 7=0x6641524 TransitioningVoxelVolume) [V] | [V] |
| tag 0 Ambient | 1 | `0x53e3511  mov byte ptr [rbp+0x138],0` | LightGroupTag::Ambient = 0 (FrameBuilder.h:79-88); clone 0x53e2c00, srcloc 0xF248E70 `FrameBuilder::insert [TDescription = RenderLightAmbientDescription]`; JT entry 0 | [V] |
| tag 1 Directional | 1 | `0x53709d4  mov byte ptr [rbp+0x18],1` | LightGroupTag::Directional = 1; thin clone 0x5370960, srcloc 0xF248F70 (LightDirectionalDescription); JT entry 1 | [V] |
| tag 2 GameplayMetadata | 1 | `0x53e5fb4  mov byte ptr [rbp-0x18],2` | LightGroupTag::GameplayMetadata = 2; clone 0x53e5910, Light vslot 0x380 insert 0x53e5fbf, srcloc 0xF248ED0 `__FUNCSIG__ ... gamecomponents::GameplayMetadata`; JT entry 2 | [V] |
| tag 3 LightPoint | 1 | `0x535a9b7  mov byte ptr [rbp+0x278],3` | LightGroupTag::LightPoint = 3; light clone 0x53599d0 insert 0x535a9ce, srcloc 0xF248DA0 `LightPointDescription`; JT entry 3 | [V] |
| tag 4 ShadowAtlasFrame | 1 | `0x535a696  mov byte ptr [rbp+0x278],4` | LightGroupTag::ShadowAtlasFrame = 4; light clone 0x53599d0 insert 0x535a6a0, srcloc 0xF248D80 `ShadowAtlasFrameDescription`; JT entry 4 | [V] |
| tag-name conflict | - | FrameBuilder.h:79-88 `enum class LightGroupTag : uint64_t { Ambient = 0, Directional = 1, GameplayMetadata = 2, LightPoint = 3, ShadowAtlasFrame = 4, ServerGraphicsOverrideParameters = 5, VoxelVolume = 6, TransitioningVoxelVolume = 7 };` | CONFLICT RESOLVED [V]: producer tag stores + __FUNCSIG__ srclocs prove tag 2 = GameplayMetadata and tag 3 = LightPoint; FrameBuilder.h wins; group_visitors.md had them swapped (LightPoint@2 / GameplayMetadata@3) and is superseded. Tags 5/6/7 = ServerGraphicsOverrideParameters / VoxelVolume / TransitioningVoxelVolume | [V] |

Verbatim instruction lines:
0x6640dc4  movzx eax,byte ptr [rdx+8]
0x6640de6  jmp rax
0x53e3511  mov byte ptr [rbp+0x138],0
0x53709d4  mov byte ptr [rbp+0x18],1
0x53e5fb4  mov byte ptr [rbp-0x18],2
0x53e5fbf  mov rax,[rax+0x380]
0x535a9b7  mov byte ptr [rbp+0x278],3
0x535a9c1  mov rax,[rax+0x380]
0x535a9ce  call qword ptr [0xF99FFA0]
0x535a696  mov byte ptr [rbp+0x278],4
0x535a6a0  mov rax,[rax+0x380]

## 2. Light-visitor writers to pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — PROVEN [V] (carried from oc_U-ER6_r1-r76, not re-run)

Pass-object vectors (begin/end/cap cursors): summary +0x7F8/+0x800/+0x808 stride 0x14; light records +0x648/+0x650 stride 0x48; GameplayMetadata +0x498/+0x4A0/+0x4A8 stride 0x84; ShadowAtlasFrame +0x1C8/+0x1D0/+0x1D8 stride 0x50 [V]. Every write below is an end-cursor increment / grow-emplace; no end-cursor pop/decrement exists anywhere in the exe [V, whole-image `fld --w` scans].

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| pass+0x800 end cursor | 8 | `0x6640eb4  add qword ptr [rsi+0x800],0x14` | end cursor of the 0x14-byte summary list (cap +0x808 compared at 0x6640e8b); writers: Ambient 0x6640eb4, Directional 0x66417a2, LightPoint 0x6641517 (all increment by 0x14); loads at 0x6640e84 / 0x6641761 | [V] |
| pass+0x808 cap cursor | 8 | `0x6640e8b  cmp rdx,[rsi+0x808]` | summary list cap cursor [V] | [V] |
| pass+0x648 end cursor | 8 | `0x66416ff  call 0x675FB30` | end cursor of the 0x48-byte light-record vector (begin +0x648 / end +0x650); writers Directional 0x66416ff and LightPoint 0x6641461 via grow-emplace 0x675FB30 [V] | [V] |
| pass+0x650 end cursor | 4 | `0x6641729  mov eax,[rsi+0x650]` | light-record end cursor; light-record index = (end - begin)/0x48 - 1 [V] | [V] |
| pass+0x4A0 end cursor | 8 | `0x6641090  add qword ptr [rdi+0x4A0],0x84` | end cursor of the 0x84-byte GameplayMetadata vector (begin +0x498 / cap +0x4A8); tag-2 writer, stride 0x84 | [V] |
| pass+0x4A8 cap cursor | 8 | `0x6640f7f  cmp r12,[rdi+0x4A8]` | GameplayMetadata cap cursor [V] | [V] |
| pass+0x1D0 end cursor | 8 | `0x66419c6  add qword ptr [rsi+0x1D0],0x50` | end cursor of the 0x50-byte ShadowAtlasFrame vector (begin +0x1C8 / cap +0x1D8); tag-4 writer, stride 0x50 [V] | [V] |

Verbatim instruction lines:
0x6640e84  mov rdx,[rsi+0x800]
0x6640e8b  cmp rdx,[rsi+0x808]
0x6640eb4  add qword ptr [rsi+0x800],0x14
0x6641761  mov rdx,[rsi+0x800]
0x66417a2  add qword ptr [rsi+0x800],0x14
0x6641517  add qword ptr [rsi+0x800],0x14
0x66416f8  lea rcx,[rsi+0x648]
0x66416ff  call 0x675FB30
0x664145a  lea rcx,[rsi+0x648]
0x6641461  call 0x675FB30
0x6641729  mov eax,[rsi+0x650]
0x6641735  shr eax,3
0x6641738  imul eax,0xFFFF8E39
0x6640f78  mov r12,[rdi+0x4A0]
0x6641090  add qword ptr [rdi+0x4A0],0x84
0x6640f7f  cmp r12,[rdi+0x4A8]
0x66419c6  add qword ptr [rsi+0x1D0],0x50

Every write above is an end-cursor increment; no end-cursor pop/decrement exists anywhere in the exe [V, whole-image `fld --w` scans, oc_U-ER6_r1-r76]; no element-indexed read of any of the four vectors exists [V negative].

## 3. Consumers of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — NOT LOCATED [?] (blocking fact)

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| pass+0x800 element read | - | - | no draining element read of the 0x14-byte summary elements anywhere in Minecraft.Windows.exe 1.26.62.01; only the three end-cursor writers in section 2 [V] | [?] |
| pass+0x648 element read | - | - | no draining element read of the 0x48-byte light-record elements anywhere in the exe [V writes only] | [?] |
| pass+0x4A0 element read | - | - | no draining element read of the 0x84-byte GameplayMetadata elements anywhere in the exe [V writes only] | [?] |
| pass+0x1D0 element read | - | - | no draining element read of the 0x50-byte ShadowAtlasFrame elements anywhere in the exe [V writes only] | [?] |

Negative angles carried [V] from oc_U-ER6_r1-r76 (not re-run per RETRY #1):
- whole-image `rdis fld --r/--w` scans for all four offsets and begin cursors 0x7F8/0x650/0x498/0x1C8: every hit is a stack local, a writer cursor access, or the same offset on an unrelated object; writes are only end-cursor increments, no `sub` end-cursor decrement; no `[pass_cursor + index*stride]` element read for any of the four offsets.
- endFrame listing sub_66232b0 (0x66232b0..0x662e680): touches none of the four offsets although it calls 0x5ABA5C0 3× (0x662891e, 0x662ab42, 0x662b38c) [V].
- all ~200 `0x5ABA5C0` callers via `rdis xr`: none drain the four vectors [V].
- `rdis ptr 0x5aba5c0`: 0 indirect slots [V]; `rdis imm 0x5aba5c0`: 0 static data references to the TLO global [V]; `rdis xr 0x6640d80`: single caller 0x6640c44 in sub_6640ae0 [V]; `rdis fn 0x6640d80`: no vcall slots [V].
- descscan2 all light cases: field reads proven [V], names unknown [?].
- `rdis callees 0x5aba5c0`: calls only TLS helpers, no consumer path [V]; `rdis callees 0x5aba6d0` + `dis 0x5aba6d0`: generic vector grow/relocate, reads cursors but not elements of the four vectors [V]; `rdis xr 0x5aba6d0`: 200 callers across visitors, all grow-only [V].
- shared epilogue after cursor writes (`rdis dis 0x6641AAB 60`): computes `(end-begin)/5-1` → `[rbp-0x32]` and increments `pass+0x7D0` cursor; cursor arithmetic only, NO element read [V].
- magic-multiplier imm scans (0xFFFF8E39 ÷0x48, 0xFFFFCCCD ÷0x14, 0xFFFF83E1 ÷0x84) negative for consumers — every hit inside known writers.
- lea register-relative scan (tools/sigs/lea_reg_find.py) for disp 0x800/0x648/0x4A0/0x1D0/0x7F8/0x650/0x498/0x4A8/0x1C8/0x1D8: only writer sites and scattered unrelated .text hits — no clean draining element read.
- per-draw code 0x66ea3d0 obtains the pass via `0x66eca8f  call 0x5ABA5C0` and appends u16 indices to the *other* pass vector at pass+0x8A8 but reads none of the four cursors [V] (verbatim lines below).
- BGFX_MAP.md 6gq/6ih/6w/6hi name no consumer of the four vectors (6ih line 2041 leaves consumers open [?]; line 1843-1844: Sky vector at pass+0x548 also readerless — same blocker for all pass vectors).

New static angles attempted this unit — ALL NEGATIVE:
- endFrame sub_66232b0's three pass acquisitions: site 1 `0x662890b  mov ecx,0x9D0` / `0x6628910  mov rax,[rbp+0x19D0]` / `0x6628917  add rcx,[rax+0x380]` / `0x662891e  call 0x5ABA5C0` then `0x66289ad  mov rbx,[rsi+0x20]` / `0x66289d1  add qword ptr [rsi+0x20],0x250` (pass sub-object +0x20, stride 0x250); site 2 `0x662ab3f  mov rcx,rsi` / `0x662ab42  call 0x5ABA5C0` then `0x662abd1  mov rdi,[rsi+0x50]` / `0x662ad17  add qword ptr [rsi+0x50],0x2B0` (pass sub-object +0x50, stride 0x2B0); site 3 `0x662b385  mov rcx,[rbp+0x1848]` / `0x662b38c  call 0x5ABA5C0` then `0x662b41b  mov r12,[r15+0x38]` / `0x662b43b  add qword ptr [r15+0x38],0xF18` (pass sub-object +0x38, stride 0xF18) [V]. These are OTHER pass sub-objects (grow via 0x566CB20); none of the four light-vector offsets (0x800/0x648/0x4A0/0x1D0) is touched anywhere in sub_66232b0 [V]. `rdis callers 0x66232b0`: 0 static calling functions [V] — endFrame itself is not statically reached.
- per-draw dispatch sub_66ea3d0 region: `0x66eca8f  call 0x5ABA5C0` (pass in rbx), then twice `0x66ecb03  mov rdx,[rbx+8a8]` / `0x66ecb0a  cmp rdx,[rbx+0x8B0]` / `0x66ecb17  movzx eax,word ptr [rbp+0x15D8]` / `0x66ecb1e  mov [rdx],ax` / `0x66ecb21  add qword ptr [rbx+0x8A8],2` (and identical copy at 0x66ecc00-0x66ecc92: `0x66ecc00  call 0x5ABA5C0`, `0x66ecc74  mov rdx,[rbx+8a8]`, `0x66ecc7b  cmp rdx,[rbx+0x8B0]`, `0x66ecc88  movzx eax,word ptr [rbp+0x15D0]`, `0x66ecc8f  mov [rdx],ax`, `0x66ecc92  add qword ptr [rbx+0x8A8],2`): appends u16 indices to pass+0x8A8 only; reads none of pass+0x800/+0x648/+0x4A0/+0x1D0 cursors or elements [V].
- whole-image `rdis fld 0x8A8 --r --max 5000`: 1158 accesses; ~all are `[rbp+0x8A8]` stack locals or [reg+0x8A8] on unrelated objects; grep of the full output for addresses in the visitor/endFrame/per-draw space (0x662xxxx–0x66fxxxx) = 0 hits [V] — the pass+0x8A8 index vector has no element reader either.

Live-capture angle (2026-11-22 tool): `oc_u_er6_light_desc` is queued (state=pending) at visitor entry 0x6640d80, size 0x100, max 6; four requests pending = limit reached, so no new `add` is allowed. Entry sampling dumps RDX = desc bytes + ret = caller chain only; it CANNOT install a read/write watchpoint on pass+0x800/+0x648/+0x4A0/+0x1D0, so even when run it cannot locate the consumers (stated limitation). livemem is not an alternative: no static pass-object target address exists (`rdis imm 0x5aba5c0` = 0 refs; `rdis ptr` = 0 slots), and livemem may not scan or loop over ranges [V static + V live status]. docs/data/live/_status.txt: DONE t=120; oc_u_er6_light_desc not listed; light_visitor.txt holds tags 0/1/2/5 description bytes only — no tag 3 (LightPoint, 0x108 B) or tag 4 (ShadowAtlasFrame, 0x50 B) samples [V live].

Side finding (not a consumer): per-draw code 0x66ea3d0 appends u16 indices to pass+0x8A8 but reads none of the four cursors [V]; described so it is not confused with a consumer.

## 4. Description field value names — offsets/sizes [V], semantic names [?] (PENDING)

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| description value names | - | - | unknown [?]: the release exe has no RTTI and no description member-name strings; LightDescriptions.h / LightGameDescriptions.h type every field as mValue* placeholders with static_assert offsets only; live dumps carry values only (light_visitor.txt [V live] holds tags 0/1/2/5 bytes; no tag 3/4 description bytes in any capture). Producer-side semantics (e.g. Ambient +0x00 = Atmosphere +0xA4) are inference [I], not names. The pending capture oc_u_er6_light_desc would add runtime desc bytes + ret= caller chain [V live when available] but not symbolic names. | [?] |

## CLOSES?

CLOSES? NO — the single blocking fact: no draining reader (element consumer) of pass+0x800 / pass+0x648 / pass+0x4A0 / pass+0x1D0 exists anywhere in Minecraft.Windows.exe 1.26.62.01; all four vectors are write-only statically (end-cursor increments / grow-emplace + index-word records only, no pop/decrement, no element-indexed read) [V]; whole-image `fld --r/--w` scans, the endFrame listing, all `0x5ABA5C0` callers, `rdis ptr`/`imm`/`xr` indirect checks, magic-multiplier imm scans, descscan2, BGFX_MAP.md 6gq/6ih/6w/6hi, the lea register-relative scan, and the new `fld 0x8A8 --r` scan are all negative [V]. The live-capture tool cannot install a read/write watchpoint (entry sampling only) and livemem has no target [V static], so the consumers cannot be located statically. Description value names also remain unknown [?]: no RTTI or description member-name strings in the release exe; headers use mValue* placeholders; live desc bytes confirm sizes only, never names. Resolved [V] and not re-proven here: tag 2 = GameplayMetadata, tag 3 = LightPoint (FrameBuilder.h wins the group_visitors.md conflict); the four end-cursor writers to pass+0x800/+0x648/+0x4A0/+0x1D0 [V].

## TOOL REQUESTS

CAPTURE REQUESTED oc_u_er6_light_desc — already queued (state=pending) in docs/progress/capture_requests.json at visitor entry 0x6640d80 (size 0x100 = 256, max 6); do NOT re-add (`request.py add` rejects duplicate name; 4 pending = limit reached). Result awaited in docs/data/live/oc_u_er6_light_desc.txt via `python tools/livecap/request.py result oc_u_er6_light_desc`; when it lands it can confirm tag-3/tag-4 description sizes/caller chain [V live] but cannot close the consumer blocker (no read/write watch available, entry sampling only). Helper scripts: None (no throwaway scripts written this unit; all evidence from existing tools and already-verified listings; tools/sigs/lea_reg_find.py from a prior unit exists and was reused via its earlier results).
