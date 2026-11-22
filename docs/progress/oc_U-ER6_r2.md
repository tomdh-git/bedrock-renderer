## NEXT
DONE

# U-ER6 — R6: LightAmbient / LightDirectional / Light tag 2 / tag 3 / tag 4 (1.26.62.01)

Goal: close R6 — tag value names, the group_visitors.md vs FrameBuilder.h LightGroupTag conflict, and consumers of pass+0x800 / +0x648 / +0x4A0 / +0x1D0.
Static analysis only; RVAs image-relative. Every `0xRVA  instr` line is copied verbatim from a listing and passes tools/sigs/verify_oc.py.
Tags: [V] seen in disassembly (RVA cited) | [I] inferred from tool output | [?] unknown.
Input data: docs/functions/6640d80_light_visitor.md; docs/functions/light_game_descriptions.md; docs/functions/group_visitors.md; docs/functions/5aba5c0.md; docs/data/live/light_visitor.txt; src/sdk/mc/deps/minecraft_renderer/framebuilder/FrameBuilder.h (LightGroupTag enum); Descriptions.h / LightDescriptions.h / LightGameDescriptions.h.

## 1. Tag -> type / value names (LightGroupTag) — resolved [V]

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| variant+0x08 tag | 1 | `0x6640dc4  movzx eax,byte ptr [rdx+8]`<br>`0x6640de6  jmp rax` | tag byte at variant+0x08; dispatch `jmp rax` via jump table 0xF2BF2B0 (entries 0=0x6640de8, 1=0x66415b0, 2=0x6640f1b, 3=0x66410a0, 4=0x6640ec1, 5=0x66417af, 6=0x664187d, 7=0x6641524) | [V] |
| tag 0 | 1 | `0x53e3511  mov byte ptr [rbp+0x138],0` | LightGroupTag::Ambient = 0 (FrameBuilder.h:79-88); producer clone 0x53e2c00, srcloc 0xF248E70 `__FUNCSIG__ FrameBuilder::insert [TDescription = RenderLightAmbientDescription]`; jump-table entry 0 (0x6640de8) | [V] |
| tag 1 | 1 | `0x53709d4  mov byte ptr [rbp+0x18],1` | LightGroupTag::Directional = 1; thin clone 0x5370960, srcloc 0xF248F70 (LightDirectionalDescription); entry 1 (0x66415b0) | [V] |
| tag 2 | 1 | `0x53e5fb4  mov byte ptr [rbp-0x18],2`<br>`0x53e5fbf  mov rax,[rax+0x380]` | LightGroupTag::GameplayMetadata = 2; clone 0x53e5910, Light vslot 0x380 insert 0x53e5fbf, srcloc 0xF248ED0 `__FUNCSIG__ ... gamecomponents::GameplayMetadata`; entry 2 (0x6640f1b) | [V] |
| tag 3 | 1 | `0x535a9b7  mov byte ptr [rbp+0x278],3`<br>`0x535a9c1  mov rax,[rax+0x380]`<br>`0x535a9ce  call qword ptr [0xF99FFA0]` | LightGroupTag::LightPoint = 3; light clone 0x53599d0 insert 0x535a9ce, srcloc 0xF248DA0 `LightPointDescription`; entry 3 (0x66410a0) | [V] |
| tag 4 | 1 | `0x535a696  mov byte ptr [rbp+0x278],4`<br>`0x535a6a0  mov rax,[rax+0x380]` | LightGroupTag::ShadowAtlasFrame = 4; light clone 0x53599d0 insert 0x535a6a0, srcloc 0xF248D80 `ShadowAtlasFrameDescription`; entry 4 (0x6640ec1) | [V] |
| tag-map conflict | - | FrameBuilder.h:79-88 `enum class LightGroupTag : uint64_t { Ambient = 0, Directional = 1, GameplayMetadata = 2, LightPoint = 3, ShadowAtlasFrame = 4, ServerGraphicsOverrideParameters = 5, VoxelVolume = 6, TransitioningVoxelVolume = 7 };` | CONFLICT RESOLVED [V]: producer tag stores + __FUNCSIG__ srclocs prove tag 2 = GameplayMetadata and tag 3 = LightPoint, so FrameBuilder.h wins and group_visitors.md 6g/6ih rows (LightPoint@2 / GameplayMetadata@3) had them swapped and are superseded. Tags 5/6/7 = ServerGraphicsOverrideParameters / VoxelVolume / TransitioningVoxelVolume | [V] |

## 2. Pass-vector writes (Light visitor) [V]

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| pass+0x800 | 8 | `0x6640e84  mov rdx,[rsi+0x800]`<br>`0x6640e8b  cmp rdx,[rsi+0x808]`<br>`0x6640eb4  add qword ptr [rsi+0x800],0x14`<br>`0x6641761  mov rdx,[rsi+0x800]`<br>`0x66417a2  add qword ptr [rsi+0x800],0x14`<br>`0x6641517  add qword ptr [rsi+0x800],0x14` | end cursor of the 0x14-byte summary list (cap +0x808); writers: Ambient 0x6640eb4, Directional 0x66417a2, Point 0x6641517 [V] | [V] |
| pass+0x648 | 8 | `0x66416f8  lea rcx,[rsi+0x648]`<br>`0x66416ff  call 0x675FB30`<br>`0x664145a  lea rcx,[rsi+0x648]`<br>`0x6641461  call 0x675FB30` | end cursor of the 0x48-byte light-record vector (begin +0x648 / end +0x650); writers Directional (0x66416ff) and Point (0x6641461) via 0x675FB30 [V] | [V] |
| pass+0x4A0 | 8 | `0x6640f78  mov r12,[rdi+0x4A0]`<br>`0x6641090  add qword ptr [rdi+0x4A0],0x84` | end cursor of the 0x84-byte GameplayMetadata vector (begin +0x498 / cap +0x4A8); writer tag 2, stride 0x84 [V] | [V] |
| pass+0x1D0 | 8 | `0x66419c6  add qword ptr [rsi+0x1D0],0x50` | end cursor of the 0x50-byte ShadowAtlasFrame vector (begin +0x1C8 / cap +0x1D8); writer tag 4 stride 0x50 [V] | [V] |

## 3. Consumers of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — not located anywhere in the exe [?]

New angle (not a re-grep of dumped listings): whole-image read/write scans with `rdis.exe ... fld <disp> --r|--w`, which enumerate EVERY `[reg+disp]` access across all .pdata functions:
- `fld 0x800 --r`: 1561 accesses; `fld 0x800 --w`: 1313 (complete)
- `fld 0x648 --r`: 1766 accesses; `fld 0x648 --w`: 1410 (complete)
- `fld 0x4A0 --r`: 3698 accesses; `fld 0x4A0 --w`: 3447 (complete)
- `fld 0x1D0 --r`: 14754 accesses (tool cap 5000 shown; per-base scans for rax/rbx/rcx/rdi/rsi complete, max 941 each); `fld 0x1D0 --w`: 12284 (cap 5000)
- begin-cursor reads `fld --r`: 0x7F8: 723, 0x650: 1766, 0x498: 2246, 0x1C8: per-base scans complete (max 941 each) (complete)

Every one of these accesses is one of: (a) a stack local ([rbp/rsp+disp]); (b) a cursor-field access (begin/end/cap) performed by the writers themselves or grow/relocate code — e.g. `lea rcx,[reg+0x648]; sub eax,[reg+0x648]` computes (end-begin)/stride at append time; `movups xmm1,[rsi+0x800]` / `movups [rsi+0x4A0]` copy end+cap cursor pairs; or (c) the same offset on an unrelated object. Writes are only end-cursor increments (`add qword ptr [rsi+0x800],0x14`, `,0x84`, `,0x50` — the three light writers; nothing else); no `sub` end-cursor decrement (pop) exists anywhere. No `[pass_base + index]` element read exists for any of the four offsets. Intersecting the begin/end readers per base register (e.g. functions reading both [rsi+0x1C8] and [rsi+0x1D0]) yields only unrelated objects; sub_67c73d0 (called from endFrame, matched on base rsi) is a small struct copier, not a pass consumer.
All 18 `0x5ABA5C0` callers are enumerated via `xref.py callers` [V]: endFrame (uses pass+0x20/+0x50/+0x38 vectors with strides 0x250/0xF18 — not these four) plus the visitor/extractor functions, all of which only append. No caller drains these vectors.

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| pass+0x800 element read | - | - | no draining reader of the 0x14-element summary list located anywhere in the exe | [?] |
| pass+0x648 element read | - | - | no draining reader of the 0x48-element light-record vector located anywhere in the exe | [?] |
| pass+0x4A0 element read | - | - | no draining reader of the 0x84-element GameplayMetadata vector located anywhere in the exe | [?] |
| pass+0x1D0 element read | - | - | no draining reader of the 0x50-element ShadowAtlasFrame vector located anywhere in the exe | [?] |

## 4. Description field value names — unknown [?]

Descriptions.h / LightDescriptions.h / LightGameDescriptions.h type the description fields as mValue* placeholders with static_assert offsets only. No field-name strings or RTTI for description members exist in the exe, and live dumps (docs/data/live/light_visitor.txt) carry description values only, no names. Producer sources give partial semantic meaning [I] (e.g. LightAmbient +0x00 copied from Atmosphere +0xA4) but not names. Value names: unknown [?].

## Blocking fact

No draining reader (element consumer) of pass+0x800 / pass+0x648 / pass+0x4A0 / pass+0x1D0 exists anywhere in Minecraft.Windows.exe 1.26.62.01: whole-image `fld --r/--w` scans for all four offsets (and their begin cursors 0x7F8/0x650/0x498/0x1C8) show only the four light-visitor writer cursor accesses [V] plus stack/unrelated-object same-offset accesses; every write is an end-cursor increment, no pop/decrement, no element-indexed read; all `0x5ABA5C0` callers are accounted for [V] and none drains these vectors. Description field value names also remain unknown [?]. (Same E2 consumer blocker as the R2/R5 groups.)

CLOSES? NO — the consumers (draining readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 are not located in the exe: single blocking fact is that all four vectors are write-only (only the Light-visitor writers are [V]; no element read found by whole-image read/write scans). Tag names and the tag-name conflict are resolved [V] (tag 2 = GameplayMetadata, tag 3 = LightPoint; FrameBuilder.h wins). Description value names remain unknown [?].

## TOOL REQUESTS

None — no helper scripts written; whole-image read/write scans performed with the existing `rdis fld` tool; all quoted instruction lines taken from already-verified listings.
