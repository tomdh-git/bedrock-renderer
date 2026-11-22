## NEXT
DONE

# U-ER6 — R6: LightAmbient / LightDirectional / Light tag 2 / tag 3 / tag 4 (1.26.62.01)

Goal: close R6 — description value names, the group_visitors.md vs FrameBuilder.h LightGroupTag tag-name conflict, and the consumers (draining element readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0.
Static analysis only; exe never launched; RVAs image-relative; every `0xRVA  instr` line copied verbatim from verified listings and passing tools/sigs/verify_oc.py. Tags: [V] seen in disassembly (RVA cited) | [I] inferred | [?] unknown. [V live] = confirmed by docs/data/live capture bytes.

## Input data (already computed by the orchestrator; NOT re-run)
docs/progress/oc_U-ER6_r1-r18.md (carried [V] proofs, not re-proven here), docs/functions/6640d80_light_visitor.md, docs/functions/5aba5c0.md, docs/functions/group_visitors.md, docs/functions/light_game_descriptions.md, docs/data/live/light_visitor.txt, docs/data/live/README.md, docs/data/live/_status.txt, docs/progress/capture_requests.json, docs/BGFX_MAP.md sections 3/6g/6w/6ih, src/sdk/mc/deps/minecraft_renderer/framebuilder/FrameBuilder.h (LightGroupTag enum, line 79), LightDescriptions.h / LightGameDescriptions.h (mValue* placeholder fields, static_assert offsets). Exe: C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe (image base; RVAs relative).

## 1. Tag -> type / LightGroupTag mapping and tag-name conflict — resolved [V] (carried r17/r18)

The pass object is the per-thread value of ThreadLocalObject 0x5ABA5C0 (value at node+0x10). Visitor cases call 0x5ABA5C0 with rcx = frameCtx+0x10+0x9D0 and get rsi = pass [V]. All four vectors live inside this pass object: begin/end/cap cursors at (+0x7F8/+0x800/+0x808) summary stride 0x14, (+0x648/+0x650) light-record stride 0x48, (+0x498/+0x4A0/+0x4A8) GameplayMetadata stride 0x84, (+0x1C8/+0x1D0/+0x1D8) ShadowAtlasFrame stride 0x50 [V, from the light-visitor listings and BGFX_MAP.md 6ih].

| offset | size | site | instr | meaning | tag |
|---|---|---|---|---|---|
| variant+0x08 tag | 1 | 0x6640dc4, 0x6640de6 | `0x6640dc4  movzx eax,byte ptr [rdx+8]`<br>`0x6640de6  jmp rax` | tag byte at variant+0x08; indirect dispatch `jmp rax` via light-visitor jump table 0xF2BF2B0 (entries: 0=0x6640de8 Ambient, 1=0x66415b0 Directional, 2=0x6640f1b GameplayMetadata, 3=0x66410a0 LightPoint, 4=0x6640ec1 ShadowAtlasFrame, 5=0x66417af ServerGraphicsOverrideParameters, 6=0x664187d VoxelVolume, 7=0x6641524 TransitioningVoxelVolume) [V] | [V] |
| producer tag stores | 1 | 0x53e3511, 0x53709d4, 0x53e5fb4, 0x53e5fbf, 0x535a9b7, 0x535a9c1, 0x535a696, 0x535a6a0 | `0x53e3511  mov byte ptr [rbp+0x138],0`<br>`0x53709d4  mov byte ptr [rbp+0x18],1`<br>`0x53e5fb4  mov byte ptr [rbp-0x18],2`<br>`0x53e5fbf  mov rax,[rax+0x380]`<br>`0x535a9b7  mov byte ptr [rbp+0x278],3`<br>`0x535a9c1  mov rax,[rax+0x380]`<br>`0x535a696  mov byte ptr [rbp+0x278],4`<br>`0x535a6a0  mov rax,[rax+0x380]` | producer clones store tag 0..4 at their variant slot before the Light vslot-0x380 insert: tag 0 Ambient (clone 0x53e2c00), tag 1 Directional (thin clone 0x5370960), tag 2 GameplayMetadata (clone 0x53e5910, insert 0x53e5fbf, srcloc GameplayMetadata), tag 3 LightPoint (clone 0x53599d0, insert 0x535a9c1, srcloc LightPointDescription), tag 4 ShadowAtlasFrame (clone 0x53599d0, insert 0x535a6a0, srcloc ShadowAtlasFrameDescription) [V] | [V] |
| tag-map conflict | - | FrameBuilder.h:79-88 | - | CONFLICT RESOLVED [V]: FrameBuilder.h:79-88 `enum class LightGroupTag : uint64_t { Ambient = 0, Directional = 1, GameplayMetadata = 2, LightPoint = 3, ShadowAtlasFrame = 4, ServerGraphicsOverrideParameters = 5, VoxelVolume = 6, TransitioningVoxelVolume = 7 };`; producer tag stores + __FUNCSIG__ srclocs prove tag 2 = GameplayMetadata and tag 3 = LightPoint, so FrameBuilder.h wins and group_visitors.md (which had them swapped: LightPoint@2 / GameplayMetadata@3) is superseded. Tags 5/6/7 = ServerGraphicsOverrideParameters / VoxelVolume / TransitioningVoxelVolume [V]; corroborated by BGFX_MAP.md lines 2037, 2051 [V doc]. | [V] |

## 2. Light-visitor end-cursor writers to pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — proven [V] (carried r17/r18)

| offset | size | site | instr | meaning | tag |
|---|---|---|---|---|---|
| pass+0x800 end cursor | 8 | 0x6640e84, 0x6640e8b, 0x6640eb4, 0x6641761, 0x66417a2, 0x6641517 | `0x6640e84  mov rdx,[rsi+0x800]`<br>`0x6640e8b  cmp rdx,[rsi+0x808]`<br>`0x6640eb4  add qword ptr [rsi+0x800],0x14`<br>`0x6641761  mov rdx,[rsi+0x800]`<br>`0x66417a2  add qword ptr [rsi+0x800],0x14`<br>`0x6641517  add qword ptr [rsi+0x800],0x14` | end cursor of the 0x14-byte summary list (cap cursor +0x808); writers: Ambient 0x6640eb4, Directional 0x66417a2, Point 0x6641517 (all increment by 0x14); cap compared at 0x6640e8b [V] | [V] |
| pass+0x808 cap cursor | 8 | 0x6640e8b | `0x6640e8b  cmp rdx,[rsi+0x808]` | summary-list cap cursor compared against end +0x800 [V] | [V] |
| pass+0x648 end cursor | 8 | 0x66416f8, 0x66416ff, 0x664145a, 0x6641461 | `0x66416f8  lea rcx,[rsi+0x648]`<br>`0x66416ff  call 0x675FB30`<br>`0x664145a  lea rcx,[rsi+0x648]`<br>`0x6641461  call 0x675FB30` | end cursor of the 0x48-byte light-record vector (begin +0x648 / end +0x650); Directional 0x66416ff and Point 0x6641461 pass &end to grow-emplace 0x675FB30 [V] | [V] |
| pass+0x650 end cursor | 4 | 0x6641729, 0x6641735, 0x6641738 | `0x6641729  mov eax,[rsi+0x650]`<br>`0x6641735  shr eax,3`<br>`0x6641738  imul eax,0xFFFF8E39` | light-record end cursor; element index derived as (end-begin)/0x48 - 1 (shr 3 then magic multiply) [V] | [V] |
| pass+0x4A0 end cursor | 8 | 0x6640f78, 0x6641090 | `0x6640f78  mov r12,[rdi+0x4A0]`<br>`0x6641090  add qword ptr [rdi+0x4A0],0x84` | end cursor of the 0x84-byte GameplayMetadata vector (begin +0x498 / cap +0x4A8); tag-2 write, stride 0x84 [V] | [V] |
| pass+0x4A8 cap cursor | 8 | 0x6640f7f | `0x6640f7f  cmp r12,[rdi+0x4A8]` | GameplayMetadata vector cap cursor compared against end +0x4A0 [V] | [V] |
| pass+0x1D0 end cursor | 8 | 0x66419c6 | `0x66419c6  add qword ptr [rsi+0x1D0],0x50` | end cursor of the 0x50-byte ShadowAtlasFrame vector (begin +0x1C8 / cap +0x1D8); tag-4 write, stride 0x50 [V] | [V] |

Every write above is an end-cursor increment; no end-cursor pop/decrement exists anywhere in the exe [V, whole-image fld --w scans]; no `[pass_cursor + index*stride]` element read exists for any of the four offsets [V negative].

## 3. Consumers of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — not located [?] (PENDING — single blocking fact)

| offset | size | site | instr | meaning | tag |
|---|---|---|---|---|---|
| pass+0x800 element read | - | - | - | no draining reader of the 0x14-byte summary elements anywhere in Minecraft.Windows.exe 1.26.62.01; only the three end-cursor writers in section 2 [V] | [?] |
| pass+0x648 element read | - | - | - | no draining reader of the 0x48-byte light-record elements anywhere in the exe [V writes only] | [?] |
| pass+0x4A0 element read | - | - | - | no draining reader of the 0x84-byte GameplayMetadata elements anywhere in the exe [V writes only] | [?] |
| pass+0x1D0 element read | - | - | - | no draining reader of the 0x50-byte ShadowAtlasFrame elements anywhere in the exe [V writes only] | [?] |

Static sweep (carried r1-r18, not re-run per RETRY #1): whole-image `rdis fld --r/--w` scans for 0x800/0x648/0x4A0/0x1D0 and begin cursors 0x7F8/0x650/0x498/0x1C8 — only stack locals, writer cursor accesses, or same offset on unrelated objects; every write is an end-cursor increment, no pop/decrement [V]; endFrame listing sub_66232b0 touches none of the four offsets though it calls 0x5ABA5C0 3× [V]; all ~200 `0x5ABA5C0` callers via `rdis xr` — none drain [V]; `rdis ptr 0x5aba5c0` (0 indirect slots) and `rdis imm 0x5aba5c0` (0 static data refs) [V]; grow path 0x675FB30 and shared case epilogue 0x66447a0..0x66447d1 (cursor arithmetic only, never element reads) [V]. Side finding only: per-draw code 0x66ea3d0 appends u16 indices to the unrelated pass vector at +0x8A8 and reads none of the four cursors [V].

Live angle (2026-11-22 orchestrator hint): capture `oc_u_er6_light_desc` (light-visitor entry rva 0x6640D80, RDX = desc ptr per docs/data/live/README.md CORRECTION 2026-11-15) is queued state=pending; `python tools/livecap/request.py result oc_u_er6_light_desc` → "no result yet (orchestrator has not run it)". Function-entry sampling dumps RDX desc bytes + ret= caller chain; it CANNOT install a read/watchpoint on pass+0x800/+0x648/+0x4A0/+0x1D0, so even when run it cannot locate the consumers [stated tool limitation]. Queue full at 4 pending (er5_clone_4c8a5b0, l8b_resizetex_slot31, sub_1289440_callers, oc_u_er6_light_desc) — no new `add` allowed. livemem has no pass-object target address (0x5ABA5C0 is a function, no static data ref, no scan/loop) [V static]; no livemem read issued.

## 4. Description field value names — unknown [?]

| offset | size | site | instr | meaning | tag |
|---|---|---|---|---|---|
| description member names | - | - | - | LightDescriptions.h / LightGameDescriptions.h type every field as mValue* placeholders with static_assert offsets only (read directly); the release exe has no RTTI and no description member-name strings; light_visitor.txt [V live] carries bytes for tags 0/1/2/5 but never names and no tag 3/4 description bytes exist in any capture. Producer-side semantics are inference [I], not names. Value names: unknown [?] | [?] |

## CLOSES?

CLOSES? NO — the single blocking fact: no draining reader (element consumer) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 exists anywhere in Minecraft.Windows.exe 1.26.62.01; all four vectors are write-only statically (end-cursor increments only, no pop/decrement, no element-indexed read) [V]; whole-image fld scans, the endFrame listing, all ~200 `0x5ABA5C0` callers, and `rdis ptr`/`imm`/`xr` indirect checks are negative [V] (carried r1-r18); the queued live capture oc_u_er6_light_desc samples function entry (RDX=desc bytes + ret=caller chain) and cannot install a read/watchpoint on the pass vectors, so it cannot close the consumer blocker; livemem has no pass-object target address [V static]. Description value names also remain unknown [?]: no RTTI or description member-name strings in the release exe; headers use mValue* placeholders.
Resolved [V], not re-proven here: tag 2 = GameplayMetadata, tag 3 = LightPoint (FrameBuilder.h wins the group_visitors.md conflict; group_visitors.md had 2/3 swapped), plus the four Light-visitor writers to pass+0x800/+0x648/+0x4A0/+0x1D0 [V].

## TOOL REQUESTS

CAPTURE REQUESTED oc_u_er6_light_desc — already queued in docs/progress/capture_requests.json (state=pending, rva 0x6640D80 = light-visitor entry 0x6640D80, size 256, max 6, why "R6: dump RDX desc bytes at visitor entry for tags 3/4 field sizes vs Descriptions.h layouts; ret= names the visitor caller chain"); `python tools/livecap/request.py result oc_u_er6_light_desc` → "no result yet (orchestrator has not run it)". Queue full at 4 pending so no new `add` this unit. The entry capture can add runtime desc bytes (which tags land in 6 samples is not controllable; no tag 3/4 bytes exist in any capture yet) plus ret= caller chain — bytes only, never member names, no read/write watchpoint, so it cannot close the consumer blocker. A read/watchpoint capability on pass+0x800/+0x648/+0x4A0/+0x1D0 (or a live pass-object address for livemem) is what would be needed to close consumers. Helper scripts: None.
