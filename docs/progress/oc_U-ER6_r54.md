## NEXT
DONE

# U-ER6 — R6: LightAmbient / LightDirectional / Light tag 2 / tag 3 / tag 4 (1.26.62.01)

Goal: close R6 — tag value names, the group_visitors.md vs FrameBuilder.h LightGroupTag conflict, consumers of pass+0x800 / +0x648 / +0x4A0 / +0x1D0. Static analysis only; RVAs image-relative; every quoted `0xRVA  instr` line is copied verbatim from verified listings (r1/r2) and passes tools/sigs/verify_oc.py. Tags: [V] seen in disassembly (RVA cited) | [I] inferred | [?] unknown. Input data (read fully, not re-generated): docs/functions/6640d80_light_visitor.md; docs/functions/light_game_descriptions.md; docs/functions/group_visitors.md; docs/functions/5aba5c0.md; docs/data/live/light_visitor.txt; src/sdk/mc/deps/minecraft_renderer/framebuilder/FrameBuilder.h (LightGroupTag enum); Descriptions.h.

NEW THIS SESSION: nothing statically — static analysis is exhausted for this item (r2 whole-image `fld --r/--w`, all `0x5ABA5C0` callers, xr/callers/vt/struct/descscan2 angles already tried; see section 3). The only new angle available is the live capture tool: see section 4.

## 1. Tag -> type / value names (LightGroupTag) — resolved [V] (r1/r2, not redone)

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| variant+0x08 tag | 1 | `0x6640dc4  movzx eax,byte ptr [rdx+8]`<br>`0x6640de6  jmp rax` | tag byte at variant+0x08; dispatch `jmp rax` through jump table 0xF2BF2B0 (entries 0=0x6640de8, 1=0x66415b0, 2=0x6640f1b, 3=0x66410a0, 4=0x6640ec1, 5=0x66417af, 6=0x664187d, 7=0x6641524; targets parsed from PE) | [V] |
| tag 0 | 1 | `0x53e3511  mov byte ptr [rbp+0x138],0` | LightGroupTag::Ambient = 0 (FrameBuilder.h:79-88); producer clone 0x53e2c00, srcloc 0xF248E70 `__FUNCSIG__ FrameBuilder::insert [TDescription = RenderLightAmbientDescription]`; JT entry 0 | [V] |
| tag 1 | 1 | `0x53709d4  mov byte ptr [rbp+0x18],1` | LightGroupTag::Directional = 1; clone 0x5370960, srcloc 0xF248F70 (LightDirectionalDescription); JT entry 1 | [V] |
| tag 2 | 1 | `0x53e5fb4  mov byte ptr [rbp-0x18],2`<br>`0x53e5fbf  mov rax,[rax+0x380]` | LightGroupTag::GameplayMetadata = 2; clone 0x53e5910, Light vslot 0x380 insert 0x53e5fbf, srcloc 0xF248ED0 `__FUNCSIG__ ... gamecomponents::GameplayMetadata`; JT entry 2 | [V] |
| tag 3 | 1 | `0x535a9b7  mov byte ptr [rbp+0x278],3`<br>`0x535a9c1  mov rax,[rax+0x380]`<br>`0x535a9ce  call qword ptr [0xF99FFA0]` | LightGroupTag::LightPoint = 3; light clone 0x53599d0 insert 0x535a9ce, srcloc 0xF248DA0 `LightPointDescription`; JT entry 3 | [V] |
| tag 4 | 1 | `0x535a696  mov byte ptr [rbp+0x278],4`<br>`0x535a6a0  mov rax,[rax+0x380]` | LightGroupTag::ShadowAtlasFrame = 4; light clone 0x53599d0 insert 0x535a6a0, srcloc 0xF248D80 `ShadowAtlasFrameDescription`; JT entry 4 | [V] |
| tag-map conflict | - | FrameBuilder.h:79-88 `enum class LightGroupTag : uint64_t { Ambient = 0, Directional = 1, GameplayMetadata = 2, LightPoint = 3, ShadowAtlasFrame = 4, ServerGraphicsOverrideParameters = 5, VoxelVolume = 6, TransitioningVoxelVolume = 7 };` | CONFLICT RESOLVED [V]: producer tag stores + __FUNCSIG__ srclocs prove tag 2 = GameplayMetadata and tag 3 = LightPoint; FrameBuilder.h wins, group_visitors.md 6g/6ih rows (LightPoint@2 / GameplayMetadata@3) had them swapped and are superseded. Tags 5/6/7 = ServerGraphicsOverrideParameters / VoxelVolume / TransitioningVoxelVolume | [V] |
| description value names | - | - | Field VALUE NAMES unknown [?]: Descriptions.h types description members as mValue* placeholders with static_assert offsets only; no member-name strings or RTTI for description members exist in the exe; live dumps carry description values only, never names. | [?] |

## 2. Pass-vector writes by the Light visitor — proven [V] (r1/r2, not redone)

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| pass+0x800 | 8 | `0x6640e84  mov rdx,[rsi+0x800]`<br>`0x6640e8b  cmp rdx,[rsi+0x808]`<br>`0x6640eb4  add qword ptr [rsi+0x800],0x14`<br>`0x66417a2  add qword ptr [rsi+0x800],0x14`<br>`0x6641517  add qword ptr [rsi+0x800],0x14` | end cursor of the 0x14-byte summary list (cap +0x808); writers: Ambient 0x6640eb4, Directional 0x66417a2, Point 0x6641517 [V] | [V] |
| pass+0x648 | 8 | `0x66416f8  lea rcx,[rsi+0x648]`<br>`0x66416ff  call 0x675FB30`<br>`0x664145a  lea rcx,[rsi+0x648]`<br>`0x6641461  call 0x675FB30` | begin cursor of the 0x48-byte light-record vector (end +0x650); writers: Directional 0x66416ff, Point 0x6641461, via append fn 0x675FB30 [V] | [V] |
| pass+0x4A0 | 8 | `0x6640f78  mov r12,[rdi+0x4A0]`<br>`0x6641090  add qword ptr [rdi+0x4A0],0x84` | end cursor of the 0x84-byte GameplayMetadata vector (begin +0x498 / cap +0x4A8); writer tag 2, stride 0x84 [V] | [V] |
| pass+0x1D0 | 8 | `0x66419c6  add qword ptr [rsi+0x1D0],0x50` | end cursor of the 0x50-byte ShadowAtlasFrame vector (begin +0x1C8 / cap +0x1D8); writer tag 4, stride 0x50 [V] | [V] |

## 3. Consumers of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — not located anywhere in the exe [?]

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| pass+0x800 element read | 0x14 | - | no draining reader of the 0x14-element summary list located anywhere in the exe; only the cursor accesses in section 2 [V] | [?] |
| pass+0x648 element read | 0x48 | - | no draining reader of the 0x48-element light-record vector located anywhere in the exe; only the cursor accesses in section 2 [V] | [?] |
| pass+0x4A0 element read | 0x84 | - | no draining reader of the 0x84-element GameplayMetadata vector located anywhere in the exe; only the cursor accesses in section 2 [V] | [?] |
| pass+0x1D0 element read | 0x50 | - | no draining reader of the 0x50-element ShadowAtlasFrame vector located anywhere in the exe; only the cursor accesses in section 2 [V] | [?] |

Basis [r2 whole-image scans, not redone]: `rdis fld 0x800/0x648/0x4A0/0x1D0 --r/--w` enumerates every `[reg+disp]` access in the image (0x800: 1561 r / 1313 w; 0x648: 1766 r / 1410 w; 0x4A0: 3698 r / 3447 w; 0x1D0: per-base scans complete). Every hit is (a) a stack local ([rbp/rsp+disp]); (b) a begin/end/cap cursor access by the writers or grow/relocate code, e.g. `lea rcx,[reg+0x648]; sub eax,[reg+0x648]` computes (end-begin)/stride at append time; or (c) the same offset on an unrelated object. Writes are only end-cursor increments (`add qword ptr [rsi+0x800],0x14`, `,0x84`, `,0x50` — the three light writers); no `sub` end-cursor decrement (pop) exists anywhere; no `[pass_base + index]` element read exists for any of the four offsets. Begin-cursor reads (0x7F8: 723, 0x650: 1766, 0x498: 2246, 0x1C8 per-base complete) show only cursor/index math. All 18 `0x5ABA5C0` callers enumerated via `xref.py callers` [V]: endFrame uses pass+0x20/+0x50/+0x38 vectors (strides 0x250/0xF18 — not these four) plus visitor/extractor functions that only append; no caller drains these vectors. Same E2 consumer blocker as the R2/R5 groups. rdis xr/callers/vt/struct and descscan2 add no consumer candidate.

## 4. Live capture path (new tool, 2026-11-22)

- `python tools/livecap/request.py result oc_u_er6_light_desc` -> "no result yet (orchestrator has not run it)".
- Request `oc_u_er6_light_desc` is already pending in docs/progress/capture_requests.json: rva=0x6640D80 (light visitor entry 0x6640d80; RDX = desc pointer per docs/data/live/README.md CORRECTION 2026-11-15), size 0x100, max 6, why "R6: desc bytes for tag 3/tag 4 field sizes + ret= caller chain". `add` rejects it ("already queued"); 4/4 pending slots are in use, so no further request can be queued this unit.
- Existing live data `docs/data/live/light_visitor.txt` (visitor-kind, size=0x300 desc dumps) [V live]: 6 samples, tags 0/1/2/5 (no tag 3/4 in these samples). Tag-1 sample, line 5, descptr 0x14A400: +0x00..+0x0C = `0000803F` x4 = four f32 1.0f, confirming f32 field sizes at +0x00/+0x04/+0x08/+0x0C of the Directional description at runtime. Live bytes confirm field sizes/values only — never field names.
- What the capture CAN add [V live when it runs]: desc bytes at entry confirming tag-3 (LightPoint, 0x108B) and tag-4 (ShadowAtlasFrame, 0x50B) field sizes and runtime values vs Descriptions.h layouts; `ret=` (caller return address at function entry) names the light-visitor caller chain.
- What the capture CANNOT add: the draining readers/consumers of pass+0x800/+0x648/+0x4A0/+0x1D0 — livecap logs function-entry registers/pointees and the caller ret= only; it does not watch reads of pass-vector memory, so element consumers remain invisible to it. No livemem write-watch exists (brief: read-only, no debugger/breakpoints).

## Blocking fact

All four vectors are write-only in Minecraft.Windows.exe 1.26.62.01: only the Light-visitor writer cursor accesses exist [V] (section 2); no element read of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 was found by whole-image read/write scans, and no `0x5ABA5C0` caller drains them [V]. Description field value names also remain unknown [?] (no names in the exe; live bytes give values not names).

CLOSES? NO — single blocking fact: the consumers (draining readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 are not located in the exe: all four vectors are write-only statically [V], no element read found anywhere (r2 whole-image `fld` scans [V]). The live capture oc_u_er6_light_desc is pending; its ret= may name the visitor caller chain and its bytes may confirm tag-3/tag-4 description field sizes/values [V live], but it cannot observe pass-vector element reads, so CLOSES? YES requires the capture (or another live angle, e.g. livemem on a candidate consumer entry) to surface a consumer. Not available yet.

## TOOL REQUESTS

oc_u_er6_light_desc | rva 0x6640D80 (light-visitor entry, RDX = desc ptr), size 0x100, max 6 -> REG=value hit=N ret=0xRVA <desc bytes> | already queued pending in docs/progress/capture_requests.json (4/4 pending slots used, `add` rejects duplicates); result awaited in docs/data/live/oc_u_er6_light_desc.txt. Expect ret= to name the visitor caller chain and bytes to confirm tag-3/tag-4 desc field sizes/runtime values [V live]. Note for the orchestrator: this capture design cannot find the pass-vector element consumers; closing R6 needs a live read/watch of pass+0x800/+0x648/+0x4A0/+0x1D0 elements, which livecap does not provide.
