## NEXT
DONE

# U-ER6 — R6: LightAmbient / LightDirectional / Light tag 2 / tag 3 / tag 4 (1.26.62.01)

Goal: close R6 — (a) tag-name conflict group_visitors.md vs FrameBuilder.h LightGroupTag, (b) consumers (draining element readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0, (c) description value names.
Static analysis only; exe never launched; RVAs image-relative; every `0xRVA  instr` line copied verbatim from listings and re-checked against Minecraft.Windows.exe 1.26.62.01 with tools/sigs/verify_oc.py. Tags: [V] seen in disassembly (RVA cited) | [I] inferred | [?] unknown | [V live] confirmed by docs/data/live capture bytes | [V doc] backed by a source doc (header/BGFX_MAP.md), not re-disassembled here.

## Input data (read fully, not re-generated)
docs/progress/oc_U-ER6_r1-r20.md (carried [V] proofs, not re-proven per RETRY #1), docs/functions/6640d80_light_visitor.md, docs/functions/5aba5c0.md, docs/functions/group_visitors.md, docs/functions/light_game_descriptions.md, docs/data/live/light_visitor.txt, docs/data/live/README.md, docs/data/live/_status.txt, docs/progress/capture_requests.json, docs/BGFX_MAP.md sections 3/6g/6w/6i/6h, src/sdk/mc/deps/minecraft_renderer/framebuilder/FrameBuilder.h (LightGroupTag enum, line 79), LightDescriptions.h / LightGameDescriptions.h (mValue* placeholder fields, static_assert offsets). Exe: C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe (image base; RVAs relative).

## Carried proven facts [V] — not re-proven this unit (RETRY #1); quoted instr lines re-verified against the exe

The pass object is the per-thread value of ThreadLocalObject 0x5ABA5C0 (value at node+0x10). Visitor cases call 0x5ABA5C0 with rcx = frameCtx+0x10+0x9D0 and get rsi = pass [V]. Jump table 0xF2BF2B0 (parsed from the PE): 0=0x6640de8 Ambient, 1=0x66415b0 Directional, 2=0x6640f1b GameplayMetadata, 3=0x66410a0 LightPoint, 4=0x6640ec1 ShadowAtlasFrame, 5=0x66417af ServerGraphicsOverrideParameters, 6=0x664187d VoxelVolume, 7=0x6641524 TransitioningVoxelVolume [V]. BGFX_MAP.md 3: `_insert(Light)` = BgfxFrameBuilder vtable slot +0x380 = 0x6640ae0 [V doc]; 6g: Light group clones LightAmbient 0x53e2c00, LightDirectional 0x5370960, LightPoint/ShadowAtlasFrame 0x53599d0, GameplayMetadata 0x53e5910 [V doc].

## 1. Tag -> type / LightGroupTag mapping — conflict resolved [V] (carried r17/r18)

| offset | size | site | instr | meaning | tag |
|---|---|---|---|---|---|
| variant+0x08 tag byte | 1 | 0x6640dc4, 0x6640de6 | `0x6640dc4  movzx eax,byte ptr [rdx+8]`<br>`0x6640de6  jmp rax` | tag byte at variant+0x08; indirect dispatch `jmp rax` through jump table 0xF2BF2B0 [V] | [V] |
| producer tag stores (variant slot before Light vslot 0x380 insert) | 1 | 0x53e3511, 0x53709d4, 0x53e5fb4, 0x53e5fbf, 0x535a9b7, 0x535a9c1, 0x535a696, 0x535a6a0 | `0x53e3511  mov byte ptr [rbp+0x138],0`<br>`0x53709d4  mov byte ptr [rbp+0x18],1`<br>`0x53e5fb4  mov byte ptr [rbp-0x18],2`<br>`0x53e5fbf  mov rax,[rax+0x380]`<br>`0x535a9b7  mov byte ptr [rbp+0x278],3`<br>`0x535a9c1  mov rax,[rax+0x380]`<br>`0x535a696  mov byte ptr [rbp+0x278],4`<br>`0x535a6a0  mov rax,[rax+0x380]` | producer clones store tag 0 Ambient (clone 0x53e2c00), 1 Directional (thin 0x5370960), 2 GameplayMetadata (clone 0x53e5910, insert 0x53e5fbf, __FUNCSIG__ GameplayMetadata), 3 LightPoint (clone 0x53599d0, insert 0x535a9c1, __FUNCSIG__ LightPointDescription), 4 ShadowAtlasFrame (clone 0x53599d0, insert 0x535a6a0, __FUNCSIG__ ShadowAtlasFrameDescription) before the insert call through [[rax]+0x380] [V] | [V] |
| tag-name conflict | - | FrameBuilder.h:79-88 | - | RESOLVED [V]: `enum class LightGroupTag : uint64_t { Ambient = 0, Directional = 1, GameplayMetadata = 2, LightPoint = 3, ShadowAtlasFrame = 4, ServerGraphicsOverrideParameters = 5, VoxelVolume = 6, TransitioningVoxelVolume = 7 };`; producer tag stores + __FUNCSIG__ zone records prove tag 2 = GameplayMetadata and tag 3 = LightPoint, so FrameBuilder.h wins and group_visitors.md (swapped: LightPoint@2 / GameplayMetadata@3) is superseded [V]; tags 5/6/7 corroborated by BGFX_MAP.md 6w/6i [V doc] | [V] |

## 2. Light-visitor end-cursor writers to pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — proven [V] (carried r17/r18)

Pass-object vectors (begin/end/cap cursors): summary +0x7F8/+0x800/+0x808 stride 0x14; light records +0x648/+0x650 stride 0x48; GameplayMetadata +0x498/+0x4A0/+0x4A8 stride 0x84; ShadowAtlasFrame +0x1C8/+0x1D0/+0x1D8 stride 0x50 [V, light-visitor listings + BGFX_MAP.md 6ih]. Every write below is an end-cursor increment; no end-cursor pop/decrement exists in the exe [V, whole-image fld --w scans].

| offset | size | site | instr | meaning | tag |
|---|---|---|---|---|---|
| pass+0x800 end cursor | 8 | 0x6640e84, 0x6640e8b, 0x6640eb4, 0x6641761, 0x66417a2, 0x6641517 | `0x6640e84  mov rdx,[rsi+0x800]`<br>`0x6640e8b  cmp rdx,[rsi+0x808]`<br>`0x6640eb4  add qword ptr [rsi+0x800],0x14`<br>`0x6641761  mov rdx,[rsi+0x800]`<br>`0x66417a2  add qword ptr [rsi+0x800],0x14`<br>`0x6641517  add qword ptr [rsi+0x800],0x14` | end cursor of the 0x14-byte summary list (cap cursor +0x808); writers: Ambient 0x6640eb4, Directional 0x66417a2, Point 0x6641517 (all increment by 0x14); cap compared at 0x6640e8b [V] | [V] |
| pass+0x808 cap cursor | 8 | 0x6640e8b | `0x6640e8b  cmp rdx,[rsi+0x808]` | summary-list cap cursor compared against end +0x800 [V] | [V] |
| pass+0x648 end cursor | 8 | 0x66416f8, 0x66416ff, 0x664145a, 0x6641461 | `0x66416f8  lea rcx,[rsi+0x648]`<br>`0x66416ff  call 0x675FB30`<br>`0x664145a  lea rcx,[rsi+0x648]`<br>`0x6641461  call 0x675FB30` | end cursor of the 0x48-byte light-record vector (begin +0x648/end +0x650); Directional 0x66416ff and Point 0x6641461 pass &end to grow-emplace 0x675FB30 [V] | [V] |
| pass+0x650 end cursor | 4 | 0x6641729, 0x6641735, 0x6641738 | `0x6641729  mov eax,[rsi+0x650]`<br>`0x6641735  shr eax,3`<br>`0x6641738  imul eax,0xFFFF8E39` | light-record end cursor; element index derived as (end-begin)/0x48 - 1 (shr 3 then magic multiply 0xFFFF8E39) [V] | [V] |
| pass+0x4A0 end cursor | 8 | 0x6640f78, 0x6641090 | `0x6640f78  mov r12,[rdi+0x4A0]`<br>`0x6641090  add qword ptr [rdi+0x4A0],0x84` | end cursor of the 0x84-byte GameplayMetadata vector (begin +0x498/cap +0x4A8); tag-2 write, stride 0x84 [V] | [V] |
| pass+0x4A8 cap cursor | 8 | 0x6640f7f | `0x6640f7f  cmp r12,[rdi+0x4A8]` | GameplayMetadata vector cap cursor compared against end +0x4A0 [V] | [V] |
| pass+0x1D0 end cursor | 8 | 0x66419c6 | `0x66419c6  add qword ptr [rsi+0x1D0],0x50` | end cursor of the 0x50-byte ShadowAtlasFrame vector (begin +0x1C8/cap +0x1D8); tag-4 write, stride 0x50 [V] | [V] |

## 3. Consumers (draining element readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — not located [?] (PENDING — single blocking fact)

No `[pass+cursor + index*stride]` element read exists for any of the four offsets anywhere in Minecraft.Windows.exe 1.26.62.01 [V negative]; the four vectors are write-only (end-cursor increments only, no pop/decrement). Carried sweeps (r1-r20, not re-run): whole-image `rdis fld --r/--w` scans for 0x800/0x648/0x4A0/0x1D0 and begin cursors 0x7F8/0x650/0x498/0x1C8 — hits are stack locals, writer cursor accesses, or the same offset on unrelated objects; endFrame listing 0x66232b0 touches none of the four offsets though it calls 0x5ABA5C0 3×; all ~200 `0x5ABA5C0` callers via `rdis xr` — none drain; `rdis ptr 0x5aba5c0` (0 indirect slots) and `rdis imm 0x5aba5c0` (0 static data refs) [V]; grow path 0x675FB30 and shared case epilogues — cursor arithmetic only, never element reads [V]. Side finding only: per-draw code 0x66ea3d0 appends u16 indices to the unrelated pass vector at +0x8A8 and reads none of the four cursors [V].

New angles tried this unit (all failed — recorded so they are not repeated):

- `python tools/livecap/request.py result oc_u_er6_light_desc` → "no result yet (orchestrator has not run it)". The capture is already queued in docs/progress/capture_requests.json (state=pending, rva 0x6640D80 = light-visitor entry). Queue is full at 4 pending (er5_clone_4c8a5b0, l8b_resizetex_slot31, sub_1289440_callers, oc_u_er6_light_desc), so no new `add` may be requested this unit. Even when run, the entry capture dumps RDX desc bytes + ret= caller chain only — it CANNOT install a read/write watchpoint on pass+0x800/+0x648/+0x4A0/+0x1D0, so it cannot locate the consumers [stated tool limitation].
- `rdis xr 0x675FB30` → 182 xrefs: grow-emplace is generic across all insert groups; the Light call sites are only 0x6641461 and 0x66416ff (both `lea rcx,[rsi+0x648]; call 0x675FB30` = end-cursor grow writes), no consumer path [V].
- `rdis dis` forward from each write site: `0x66419c6 add qword ptr [rsi+0x1D0],0x50` is immediately followed by `jmp 0x66437A9` (shared case epilogue); `0x6641090 add qword ptr [rdi+0x4A0],0x84` immediately followed by `jmp 0x6643172`; `0x6641517 add qword ptr [rsi+0x800],0x14` immediately followed by `jmp 0x6641E8C`. In each case the increment is the last cursor use — the function jumps to the epilogue, no downstream read of the just-incremented cursor [V].
- livemem: no pass-object target address — 0x5ABA5C0 is a function entry (ThreadLocalObject::get), `rdis imm 0x5aba5c0` = 0 static data references, `rdis ptr 0x5aba5c0` = 0 indirect slots, and the pass is computed per call (rcx = frameCtx+0x10+0x9D0 → 0x5ABA5C0 → &node+0x10 value); livemem cannot scan/loop over ranges and has no watchpoint capability; static-analysis-only brief rule; no livemem read issued [V static].

| offset | size | site | instr | meaning | tag |
|---|---|---|---|---|---|
| pass+0x800 element read | - | - | - | no draining element read of the 0x14-byte summary vector anywhere in Minecraft.Windows.exe 1.26.62.01; end-cursor increment writes only [V negative] | [?] |
| pass+0x648 element read | - | - | - | no draining element read of the 0x48-byte light-record vector anywhere in the exe; writes only [V negative] | [?] |
| pass+0x4A0 element read | - | - | - | no draining element read of the 0x84-byte GameplayMetadata vector anywhere in the exe; writes only [V negative] | [?] |
| pass+0x1D0 element read | - | - | - | no draining element read of the 0x50-byte ShadowAtlasFrame vector anywhere in the exe; writes only [V negative] | [?] |

## 4. Description field reads — offsets/sizes [V], value names [?]

Light-descriptions reads (visitor side, description pointer in rsi; tag-4 ShadowAtlasFrame case shown; tag 0/1/2/3 read patterns carried [V] from r1-r5 with the same descscan2-proven offsets/sizes). Header sizes read directly from LightDescriptions.h / LightGameDescriptions.h static_asserts: LightAmbientProducer 0x18, LightDirectionalProducer 0x24, LightPointProducer 0x108, GameplayMetadataProducer 0x84, ShadowAtlasFrameDescriptionReads 0x50 — they match the visitor read extents [V].

| offset | size | site | instr | meaning | tag |
|---|---|---|---|---|---|
| desc+0x00 | 16 | 0x6640ec1 | `0x6640ec1  movups xmm6,[rsi]` | tag-4 ShadowAtlasFrame description row +0x00 copied verbatim into the pass element (four 16-byte rows +0x00..+0x30) [V] | [V] |
| desc+0x10 | 16 | 0x6640ecb | `0x6640ecb  movups xmm7,[rsi+0x10]` | description row +0x10 [V] | [V] |
| desc+0x20 | 16 | 0x6640ed6 | `0x6640ed6  movups xmm8,[rsi+0x20]` | description row +0x20 [V] | [V] |
| desc+0x30 | 16 | 0x6640ee3 | `0x6640ee3  movups xmm9,[rsi+0x30]` | description row +0x30 [V] | [V] |
| desc+0x40 | 8 | 0x66418f0 | `0x66418f0  mov rbx,[rsi+0x40]` | description qword +0x40 (a pointer; with +0x48 a {ptr, control block} pair) [V] | [V] |
| desc+0x48 | 8 | 0x6640f01 | `0x6640f01  mov rcx,[rsi+0x48]` | description qword +0x48 shared handle / control block (`lock inc dword ptr [rcx+8]` at 0x6640f0e) [V] | [V] |

Description value names: unknown [?]. LightDescriptions.h / LightGameDescriptions.h type every field as mValue* placeholders with static_assert offsets only (read directly); the release exe has no RTTI and no description member-name strings; docs/data/live/light_visitor.txt [V live] carries description bytes for tags 0/1/2/5 only (never member names) and no tag 3/4 description bytes exist in any capture. Producer-side semantics are inference [I], not names. The pending capture oc_u_er6_light_desc (RDX = desc pointer at visitor entry, per docs/data/live/README.md CORRECTION 2026-11-15) can add runtime desc bytes for tags 3/4 [V live field sizes only] but bytes never yield member names, so value names cannot be closed by it either.

## 5. Live capture status (checked this unit)

`python tools/livecap/request.py result oc_u_er6_light_desc` → "no result yet (orchestrator has not run it)". Request already queued (capture_requests.json): name oc_u_er6_light_desc, rva 0x6640D80 (light-visitor entry 0x6640D80; BGFX_MAP.md 3: `_insert(Light)` dispatch), size 0x100, max 6, why "R6: dump RDX desc bytes at visitor entry for tags 3/4 field sizes vs Descriptions.h layouts; ret= names the visitor caller chain", state=pending. When the result lands in docs/data/live/oc_u_er6_light_desc.txt, cite [V live]: tag-3 (LightPoint, 0x108 B) / tag-4 (ShadowAtlasFrame, 0x50 B) description bytes confirm field sizes vs Descriptions.h static_asserts, and ret= names the visitor caller chain. It cannot close the consumer blocker (no pass-memory watchpoint) nor value names (bytes, not member names).

## CLOSES?

CLOSES? NO — the single blocking fact: no draining reader (element consumer) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 exists anywhere in Minecraft.Windows.exe 1.26.62.01; all four vectors are write-only statically (end-cursor increments only, no pop/decrement, no element-indexed read) [V]; whole-image fld scans, the endFrame listing 0x66232b0, all ~200 `0x5ABA5C0` callers, `rdis ptr`/`imm`/`xr` indirect checks, this unit's write-site epilogue disassembly and `rdis xr 0x675FB30` are all negative [V]; the queued live entry capture samples function-entry args (RDX = desc bytes, ret = caller chain) and cannot install a read/write watchpoint on the pass vectors, so even when run it cannot close this blocker; livemem has no pass-object target address [V static]. Description value names also remain unknown [?]: no RTTI or description member-name strings in the release exe; headers use mValue* placeholders; live desc bytes (capture pending) confirm sizes only, never names.
Resolved [V], carried, not re-proven here: tag 2 = GameplayMetadata, tag 3 = LightPoint (FrameBuilder.h wins the group_visitors.md conflict which had 2/3 swapped); the four end-cursor writers to pass+0x800/+0x648/+0x4A0/+0x1D0 [V].

## TOOL REQUESTS

CAPTURE REQUESTED oc_u_er6_light_desc — already queued in docs/progress/capture_requests.json (state=pending, rva 0x6640D80 = light-visitor entry 0x6640D80, size 0x100, max 6, why "R6: dump RDX desc bytes at visitor entry for tags 3/4 field sizes vs Descriptions.h layouts; ret= names the visitor caller chain"); `python tools/livecap/request.py result oc_u_er6_light_desc` → "no result yet (orchestrator has not run it)". Queue full at 4 pending so no new `add` this unit. The entry capture can add runtime desc bytes (which tags land in 6 samples is not controllable; no tag 3/4 bytes exist in any capture yet) plus ret= caller chain — bytes only, never member names, no read/write watchpoint, so it cannot close the consumer blocker. A read/write watchpoint on pass+0x800/+0x648/+0x4A0/+0x1D0 (or a live pass-object address for livemem) is what would be needed to close consumers. Helper scripts: None.
