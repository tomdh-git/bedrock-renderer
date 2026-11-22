## NEXT
DONE

# U-ER6 — R6: LightAmbient / LightDirectional / Light tag 2 / tag 3 / tag 4 (1.26.62.01)

Goal: close R6 — tag value names, the group_visitors.md vs FrameBuilder.h LightGroupTag conflict, and the consumers (draining element readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0. Static analysis only; RVAs image-relative. Every `0xRVA  instr` line is copied verbatim from verified listings (r1-r5 passed tools/sigs/verify_oc.py) and is not re-derived here. Tags: [V] seen in disassembly (RVA cited) | [I] inferred | [?] unknown.

Input data (read fully, not re-generated): docs/functions/6640d80_light_visitor.md; docs/functions/5aba5c0.md; docs/functions/group_visitors.md; docs/functions/light_game_descriptions.md; docs/data/live/light_visitor.txt; src/sdk/mc/deps/minecraft_renderer/framebuilder/FrameBuilder.h (LightGroupTag enum); Descriptions.h.

The pass object is the per-thread value of ThreadLocalObject 0x5ABA5C0 (value at node+0x10). Visitor cases call 0x5ABA5C0 with rcx = frameCtx+0x10+0x9D0 and get rsi = pass [V]. All four vectors live inside this pass object: begin/end/cap cursors at (+0x7F8/+0x800/+0x808) summary stride 0x14, (+0x648/+0x650) light-record stride 0x48, (+0x498/+0x4A0/+0x4A8) GameplayMetadata stride 0x84, (+0x1C8/+0x1D0/+0x1D8) ShadowAtlasFrame stride 0x50 [V, from the light-visitor listings].

## 1. Tag -> type / value names (LightGroupTag) and the tag-name conflict — resolved [V]

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| variant+0x08 tag | 1 | `0x6640dc4  movzx eax,byte ptr [rdx+8]`<br>`0x6640de6  jmp rax` | tag byte at variant+0x08; dispatch `jmp rax` via jump table 0xF2BF2B0 (entries: 0=0x6640de8 Ambient, 1=0x66415b0 Directional, 2=0x6640f1b GameplayMetadata, 3=0x66410a0 LightPoint, 4=0x6640ec1 ShadowAtlasFrame, 6=0x664187d VoxelVolume, 7=0x6641524 TransitioningVoxelVolume) [V] | [V] |
| tag 0 | 1 | `0x53e3511  mov byte ptr [rbp+0x138],0` | LightGroupTag::Ambient = 0 (FrameBuilder.h:79-88); producer clone 0x53e2c00, srcloc 0xF248E70 `FrameBuilder::insert [TDescription = RenderLightAmbientDescription]`; jump-table entry 0 [V] | [V] |
| tag 1 | 1 | `0x53709d4  mov byte ptr [rbp+0x18],1` | LightGroupTag::Directional = 1; thin clone 0x5370960, srcloc 0xF248F70 (LightDirectionalDescription); entry 1 [V] | [V] |
| tag 2 | 1 | `0x53e5fb4  mov byte ptr [rbp-0x18],2`<br>`0x53e5fbf  mov rax,[rax+0x380]` | LightGroupTag::GameplayMetadata = 2; clone 0x53e5910, Light vslot 0x380 insert 0x53e5fbf, srcloc 0xF248ED0 `__FUNCSIG__ ... gamecomponents::GameplayMetadata`; entry 2 [V] | [V] |
| tag 3 | 1 | `0x535a9b7  mov byte ptr [rbp+0x278],3`<br>`0x535a9c1  mov rax,[rax+0x380]`<br>`0x535a9ce  call qword ptr [0xF99FFA0]` | LightGroupTag::LightPoint = 3; light clone 0x53599d0 insert 0x535a9ce, srcloc 0xF248DA0 `LightPointDescription`; entry 3 [V] | [V] |
| tag 4 | 1 | `0x535a696  mov byte ptr [rbp+0x278],4`<br>`0x535a6a0  mov rax,[rax+0x380]` | LightGroupTag::ShadowAtlasFrame = 4; light clone 0x53599d0 insert 0x535a6a0, srcloc 0xF248D80 `ShadowAtlasFrameDescription`; entry 4 [V] | [V] |
| tag-map conflict | - | - | CONFLICT RESOLVED [V]: producer tag stores + __FUNCSIG__ srclocs prove tag 2 = GameplayMetadata and tag 3 = LightPoint, so FrameBuilder.h:79-88 wins and group_visitors.md rows 6g/6ih (LightPoint@2 / GameplayMetadata@3) had them swapped and are superseded. Tags 5/6/7 = ServerGraphicsOverrideParameters / VoxelVolume / TransitioningVoxelVolume [V] | [V] |

## 2. Pass-vector writes to pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — writers [V], consumers not located [?]

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| pass+0x800 | 8 | `0x6640e84  mov rdx,[rsi+0x800]`<br>`0x6640e8b  cmp rdx,[rsi+0x808]`<br>`0x6640eb4  add qword ptr [rsi+0x800],0x14`<br>`0x6641761  mov rdx,[rsi+0x800]`<br>`0x66417a2  add qword ptr [rsi+0x800],0x14`<br>`0x6641517  add qword ptr [rsi+0x800],0x14` | end cursor of the 0x14-byte summary list (cap +0x808); writers: Ambient 0x6640eb4, Directional 0x66417a2, Point 0x6641517 [V]; CONSUMER (draining element reader) NOT located anywhere in the exe — see section 4 [?] | [V]/[?] |
| pass+0x808 | 8 | `0x6640e8b  cmp rdx,[rsi+0x808]` | summary list cap cursor [V] | [V] |
| pass+0x648 | 8 | `0x66416f8  lea rcx,[rsi+0x648]`<br>`0x66416ff  call 0x675FB30`<br>`0x664145a  lea rcx,[rsi+0x648]`<br>`0x6641461  call 0x675FB30` | end cursor of the 0x48-byte light-record vector (begin +0x648 / end +0x650); writers Directional 0x66416ff and Point 0x6641461 via 0x675FB30 [V]; CONSUMER NOT located [?] | [V]/[?] |
| pass+0x650 | 4 | `0x6641729  mov eax,[rsi+0x650]`<br>`0x6641735  shr eax,3`<br>`0x6641738  imul eax,0xFFFF8E39` | light-record end cursor; light-record index = (end - begin)/0x48 - 1 [V] | [V] |
| pass+0x4A0 | 8 | `0x6640f78  mov r12,[rdi+0x4A0]`<br>`0x6641090  add qword ptr [rdi+0x4A0],0x84` | end cursor of the 0x84-byte GameplayMetadata vector (begin +0x498 / cap +0x4A8); writer tag 2, stride 0x84 [V]; CONSUMER NOT located [?] | [V]/[?] |
| pass+0x4A8 | 8 | `0x6640f7f  cmp r12,[rdi+0x4A8]` | GameplayMetadata vector cap cursor [V] | [V] |
| pass+0x1D0 | 8 | `0x66419c6  add qword ptr [rsi+0x1D0],0x50` | end cursor of the 0x50-byte ShadowAtlasFrame vector (begin +0x1C8 / cap +0x1D8); writer tag 4, stride 0x50 [V]; CONSUMER NOT located [?] | [V]/[?] |

## 3. Description field value names — unknown [?]

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| description value names | - | - | Field reads and sizes are proven [V] per case (descscan2 coverage recorded in earlier units: LightAmbient 0x18, LightDirectional 0x24, LightPoint 0x108, GameplayMetadata 0x84, ShadowAtlasFrame 0x50), but the exe has no RTTI and no description member name strings; headers type the fields as mValue* placeholders with static_assert offsets only, and live dumps carry values only. Producer-side semantics (e.g. Ambient +0x00 = Atmosphere +0xA4) are inference [I], not names. Live bytes for tags 3/4 were not captured (section 4). Value names: unknown [?] | [?] |

## 4. New angles tried this unit — all blocked

**Live capture at the light-visitor entry (producer side).** `python tools/livecap/request.py add oc_u_er6_light_desc 0x6640d80 --size 0x100 --max 6 --why "R6: ..."` was REJECTED: "4 requests already pending, ask again next unit". Pending queue: oc_u_el6b_desc, el10b_lighting_desc, oc_u_er2, oc_u_er1_producer. Not queued this unit. Even if queued, a producer-entry capture observes description bytes + ret= caller chain only; it cannot observe the downstream consumers of the pass vectors.

**livemem:** not applicable — no rdis-found consumer address to target (no candidate consumer exists in static analysis), and the live session is done (docs/data/live/_status.txt: DONE t=120). At most 12 livemem calls per unit, never scan or loop; nothing to point it at.

**Static angles already exhausted in prior units (not redone):** whole-image `rdis fld --r/--w` scans for all four offsets and begin cursors (0x7F8/0x650/0x498/0x1C8); endFrame's full listing sub_66232b0 (no access to any of the four offsets although it calls 0x5ABA5C0 three times); enumeration of all 0x5ABA5C0 callers (rdis xr ~200 + dossiers); `rdis ptr 0x5aba5c0` (0 indirect slots), `rdis imm 0x5aba5c0` (0 static data references). Every caller only appends; no end-cursor pop/decrement exists anywhere [V].

## Blocking fact

The consumers (draining element readers) of pass+0x800 / pass+0x648 / pass+0x4A0 / pass+0x1D0 are not located anywhere in Minecraft.Windows.exe 1.26.62.01: all four vectors are write-only in static analysis (only the three Light-visitor end-cursor writers are [V]); every write is an end-cursor increment, no pop/decrement, no element-indexed read of any of the four vectors exists; the live-capture angle cannot help (queue full; producer-entry capture cannot see downstream consumers; livemem has no target address). Description value names also remain symbolically unknown [?]. Tag names (tag 2 = GameplayMetadata, tag 3 = LightPoint) and the group_visitors.md vs FrameBuilder.h conflict are closed [V]; writers are closed [V].

CLOSES? NO — single blocking fact: consumers (draining element readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 are not located in the exe; write-only from static analysis, static analysis exhausted, live-capture slot unavailable this unit (queue full) and producer-side anyway, description value names symbolically unknown [?].

## TOOL REQUESTS

oc_u_er6_light_desc | `python tools/livecap/request.py add oc_u_er6_light_desc 0x6640d80 --size 0x100 --max 6` | REJECTED — 4 pending already (oc_u_el6b_desc, el10b_lighting_desc, oc_u_er2, oc_u_er1_producer). Re-request next unit: would confirm tag 3/4 description bytes + producer ret= caller chain [V live]; cannot find pass-vector consumers. No helper scripts written; none needed.
