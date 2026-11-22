## NEXT
DONE

# U-ER6 — R6: LightAmbient / LightDirectional / Light tag 2 / tag 3 / tag 4 (1.26.62.01)

Goal: close R6 — tag value names, the group_visitors.md vs FrameBuilder.h LightGroupTag conflict, and the consumers (draining readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0.
Static analysis only; RVAs image-relative. Every `0xRVA  instr` line is copied verbatim from a listing / re-disassembly and passes tools/sigs/verify_oc.py.
Tags: [V] seen in disassembly (RVA cited) | [I] inferred | [?] unknown.
Input data (read fully, not re-generated): docs/progress/oc_U-ER6_r1.md, oc_U-ER6_r2.md, oc_U-ER6_r3.md; docs/functions/6640d80_light_visitor.md; docs/functions/light_game_descriptions.md; docs/functions/group_visitors.md; docs/functions/5aba5c0.md; docs/data/live/light_visitor.txt; src/sdk/mc/deps/minecraft_renderer/framebuilder/FrameBuilder.h (LightGroupTag enum); Descriptions.h.

## Status carried forward from r1-r3 (NOT redone — proven [V])

- Tag->type/value names resolved [V] (tables in r3 section 1): tag byte at variant+0x08 (`0x6640dc4  movzx eax,byte ptr [rdx+8]`, `0x6640de6  jmp rax`), jump table 0xF2BF2B0 entries 0=0x6640de8, 1=0x66415b0, 2=0x6640f1b, 3=0x66410a0, 4=0x6640ec1, 5=0x66417af, 6=0x664187d, 7=0x6641524.
- tag 0 Ambient (`0x53e3511`), tag 1 Directional (`0x53709d4`), tag 2 GameplayMetadata (`0x53e5fb4 ... mov rax,[rax+0x380]`, clone 0x53e5910, srcloc 0xF248ED0 GameplayMetadata), tag 3 LightPoint (`0x535a9b7`, clone 0x53599d0, srcloc 0xF248DA0 LightPointDescription), tag 4 ShadowAtlasFrame (`0x535a696`, clone 0x53599d0, srcloc 0xF248D80 ShadowAtlasFrameDescription).
- TAG-NAME CONFLICT RESOLVED [V]: FrameBuilder.h:79-88 wins (tag 2 = GameplayMetadata, tag 3 = LightPoint); group_visitors.md 6g/6ih rows had them swapped and are superseded. Tags 5/6/7 = ServerGraphicsOverrideParameters / VoxelVolume / TransitioningVoxelVolume.
- Light-visitor writers to pass+0x800 (end cursor, stride 0x14, cap +0x808; `0x6640e84/0x6640e8b/0x6640eb4`, `0x6641761/0x66417a2`, `0x6641517`), pass+0x648/+0x650 (light-record vector stride 0x48; `0x66416f8/0x66416ff call 0x675FB30`, `0x664145a/0x6641461`, `0x6641729/0x6641735/0x6641738`), pass+0x4A0/+0x498/+0x4A8 (GameplayMetadata stride 0x84; `0x6640f78/0x6641090/0x6640f7f`), pass+0x1C8/+0x1D0/+0x1D8 (ShadowAtlasFrame stride 0x50; `0x66419c6`) — all end-cursor increments only, no pop/decrement anywhere in the exe [V].
- Description field reads proven [V] in visitor cases (ambient +0x00/+0x08/+0x10/+0x14; directional +0x00/+0x10/+0x14/+0x1C/+0x20; gm +0x00/+0x10/+0x20/+0x2A/+0x3C..+0x80 size 0x84; lp +0x00/+0x10/+0x14/+0x20/+0x28/+0x30/+0x38/+0x40/+0x58/+0x60/+0xE8 size 0x108; sa +0x00..+0x48 size 0x50) but real field VALUE NAMES unknown [?]: no RTTI, no description member name strings in the release exe; headers use mValue* placeholders.

## Pass-vector writer rows (proven [V] in r1-r3, not redone)

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| pass+0x800 | 8 | `0x6640eb4  add qword ptr [rsi+0x800],0x14` | Ambient end-cursor increment of 0x14-byte summary list (cap +0x808) [V] | [V] |
| pass+0x648 | 8 | `0x66416ff  call 0x675FB30` | Directional light-record append via grow fn (begin +0x648 / end +0x650, stride 0x48) [V] | [V] |
| pass+0x4A0 | 8 | `0x6641090  add qword ptr [rdi+0x4A0],0x84` | GameplayMetadata end-cursor increment (begin +0x498 / cap +0x4A8, stride 0x84) [V] | [V] |
| pass+0x1D0 | 8 | `0x66419c6  add qword ptr [rsi+0x1D0],0x50` | ShadowAtlasFrame end-cursor increment (begin +0x1C8 / cap +0x1D8, stride 0x50) [V] | [V] |

## NEW ANGLE TRIED THIS UNIT — live capture (static analysis exhausted per 2026-11-22 review)

The one fact not proven by static analysis: no draining reader (element consumer) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 exists anywhere in Minecraft.Windows.exe 1.26.62.01 (whole-image `fld --r/--w` scans, endFrame full listing 0x66232b0, all direct 0x5ABA5C0 callers including the three non-visitor ones 0x66a6830/0x66a9d50/0x66bb7b0, `rdis ptr 0x5aba5c0` no indirect slot — all in r2/r3). No static angle remains.

Already-captured live data (docs/data/live/light_visitor.txt, captured 2026-11-19 at 0x6640D80, kind=visitor, size=0x300): samples for tags 0 (Ambient), 1 (Directional), 2 (GameplayMetadata), 5 (ServerGraphicsOverrideParameters) — raw description bytes confirm runtime field VALUES/sizes but NOT field value names (headers use mValue* placeholders; bytes carry values only). Tags 3 (LightPoint, size 0x108) and 4 (ShadowAtlasFrame, size 0x50) are NOT present in that dump.

Live capture request `oc_u_er6_light_desc` is ALREADY QUEUED (state=pending) at rva=0x6640D80 (light-visitor entry, RDX=desc ptr per docs/data/live/README.md CORRECTION 2026-11-15), size=0x100, max=6. Why: "R6: light-visitor entry producer capture. Dump desc bytes to confirm tag 3 (LightPoint, 0x108 B) and tag 4 (ShadowAtlasFrame, 0x50 B) field sizes/runtime values vs Descriptions.h layouts; ret= names the visitor caller chain." Checked `python tools/livecap/request.py result oc_u_er6_light_desc` — no result yet (orchestrator has not run it). Result will give REG=value hit=N ret=0xRVA <desc bytes>; ret= names the caller chain; bytes confirm tag 3/tag 4 sizes at runtime.

What the live data CAN add: (a) runtime confirmation that tag 3 = LightPoint occupies 0x108 bytes and tag 4 = ShadowAtlasFrame occupies 0x50 bytes (size confirmation only, [V live]); (b) ret= names the light-visitor caller chain ([V live]). What it CANNOT add: element consumers of pass+0x800/+0x648/+0x4A0/+0x1D0 (capture is at the PRODUCER entry, not a consumer; write-only vectors have no element reads to capture), nor description field VALUE NAMES (bytes give values, headers give mValue* placeholders, no name strings exist in the release exe).

CLOSES? NO — single blocking fact: the consumers (draining element readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 are write-only statically and not located in the exe; description value names remain unknown [?] (no RTTI, no member name strings, live bytes give values not names). Tag names and the tag-name conflict ARE closed [V] (tag 2 = GameplayMetadata, tag 3 = LightPoint; FrameBuilder.h wins). Next step: wait for `oc_u_er6_light_desc` result; even with it, the consumer question is expected to remain open (producer-entry capture cannot find element consumers).

## TOOL REQUESTS

CAPTURE REQUESTED oc_u_er6_light_desc — already queued (pending) at light-visitor entry 0x6640D80; awaiting orchestrator result in docs/data/live/oc_u_er6_light_desc.txt. No new request needed (duplicate would be rejected).
