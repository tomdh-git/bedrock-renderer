## NEXT
DONE

# U-ER6 — R6: LightAmbient / LightDirectional / Light tag 2 / tag 3 / tag 4 (1.26.62.01)

Goal: close R6 — tag value names, the group_visitors.md vs FrameBuilder.h LightGroupTag conflict, and the consumers (draining readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0.
Static analysis only; RVAs image-relative. Every `0xRVA  instr` line copied verbatim from a listing / re-disassembly and passing tools/sigs/verify_oc.py.
Tags: [V] seen in disassembly (RVA cited) | [I] inferred | [?] unknown. [V live] = confirmed by docs/data/live capture bytes.

## Status carried over from earlier units (oc_U-ER6_r1..r3.md) — NOT redone

### 1. Tag -> type / value names (LightGroupTag) and the tag-name conflict — resolved [V]

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| variant+0x08 tag | 1 | `0x6640dc4  movzx eax,byte ptr [rdx+8]`<br>`0x6640de6  jmp rax` | tag byte at variant+0x08; dispatch `jmp rax` via jump table 0xF2BF2B0 (entries: 0=0x6640de8, 1=0x66415b0, 2=0x6640f1b, 3=0x66410a0, 4=0x6640ec1, 5=0x66417af, 6=0x664187d, 7=0x6641524) | [V] |
| tag 0 | 1 | `0x53e3511  mov byte ptr [rbp+0x138],0` | LightGroupTag::Ambient = 0 (FrameBuilder.h:79-88); producer clone 0x53e2c00, srcloc 0xF248E70 `__FUNCSIG__ FrameBuilder::insert [TDescription = RenderLightAmbientDescription]`; entry 0 (0x6640de8) | [V] |
| tag 1 | 1 | `0x53709d4  mov byte ptr [rbp+0x18],1` | LightGroupTag::Directional = 1; thin clone 0x5370960, srcloc 0xF248F70 (LightDirectionalDescription); entry 1 (0x66415b0) | [V] |
| tag 2 | 1 | `0x53e5fb4  mov byte ptr [rbp-0x18],2`<br>`0x53e5fbf  mov rax,[rax+0x380]` | LightGroupTag::GameplayMetadata = 2; clone 0x53e5910, Light vslot 0x380 insert 0x53e5fbf, srcloc 0xF248ED0 `__FUNCSIG__ ... gamecomponents::GameplayMetadata`; entry 2 (0x6640f1b) | [V] |
| tag 3 | 1 | `0x535a9b7  mov byte ptr [rbp+0x278],3`<br>`0x535a9c1  mov rax,[rax+0x380]` | LightGroupTag::LightPoint = 3; light clone 0x53599d0 insert 0x535a9c1, srcloc 0xF248DA0 `LightPointDescription`; entry 3 (0x66410a0) | [V] |
| tag 4 | 1 | `0x535a696  mov byte ptr [rbp+0x278],4`<br>`0x535a6a0  mov rax,[rax+0x380]` | LightGroupTag::ShadowAtlasFrame = 4; light clone 0x53599d0 insert 0x535a6a0, srcloc 0xF248D80 `ShadowAtlasFrameDescription`; entry 4 (0x6640ec1) | [V] |
| tag-map conflict | - | FrameBuilder.h:79-88 `enum class LightGroupTag : uint64_t { Ambient = 0, Directional = 1, GameplayMetadata = 2, LightPoint = 3, ShadowAtlasFrame = 4, ServerGraphicsOverrideParameters = 5, VoxelVolume = 6, TransitioningVoxelVolume = 7 };` | CONFLICT RESOLVED [V]: producer tag stores + __FUNCSIG__ srclocs prove tag 2 = GameplayMetadata and tag 3 = LightPoint; FrameBuilder.h wins; group_visitors.md 6g/6ih rows had them swapped (LightPoint@2 / GameplayMetadata@3) and are superseded. Tags 5/6/7 = ServerGraphicsOverrideParameters / VoxelVolume / TransitioningVoxelVolume | [V] |

### 2. Description field value names — unknown [?]; field sizes/offsets confirmed live [V live]

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| description value names | - | - | LightAmbientDescription (size 0x18), LightDirectionalDescription (0x24), LightPointDescription (0x108), GameplayMetadataDescription (0x84) field reads are proven [V] in the visitor cases, but the exe has no RTTI and no description member name strings; headers type the fields as mValue* placeholders with static_assert offsets only; producer-side semantics (e.g. Ambient +0x00 = Atmosphere +0xA4) are inference [I], not names. Value names: unknown [?]. Live bytes below confirm field sizes/offsets at runtime, not names. | [?] |

### 3. Description bytes captured live (docs/data/live/light_visitor.txt, tag descptr hex = description memory, byte 0 first)

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| live tag 0 ambient+0x00 | 8 | docs/data/live/light_visitor.txt line 2 (tag=0, desc=0x14A5B8): bytes at +0x00 `0000000000000000` | desc qword +0x00 = 0 at runtime (sample: inactive ambient light); 8-byte field present at ambient desc+0x00 (static read size 8 from movsd `0x6640dfb movsd xmm7,[rsi]`) | [V live] |
| live tag 0 ambient+0x08 | 4 | docs/data/live/light_visitor.txt line 2: bytes at +0x08 `00000000` | desc f32 +0x08 = 0.0 at runtime; 4-byte field present (static movss size 4 `0x6640df6 movss xmm6,[rsi+8]`) | [V live] |
| live tag 0 ambient+0x14 | 2 | docs/data/live/light_visitor.txt line 2: bytes at +0x14 `0000` | desc u16 +0x14 = 0 at runtime; 2-byte field present (static movzx size 2 `0x6640df1 movzx r12d,word ptr [rsi+0x14]`; feeds pass+0x8A0 u16 vector) | [V live] |
| live tag 1 directional+0x00 | 16 | docs/data/live/light_visitor.txt line 3 (tag=1, desc=0x14A400): bytes at +0x00 `0000803F0000803F0000803F0000803F` | desc vec4 +0x00 = (1,1,1,1) at runtime; 16-byte field present (static movups size 16 `0x66415cc movups xmm2,[rsi]`) | [V live] |
| live tag 1 directional+0x10 | 1 | docs/data/live/light_visitor.txt line 3: byte at +0x10 `00` | desc flag byte +0x10 = 0 at runtime; 1-byte field present (static movzx size 1 `0x66415c3 movzx ecx,byte ptr [rsi+0x10]`) | [V live] |
| live tag 1 directional+0x20 | 2 | docs/data/live/light_visitor.txt line 3: bytes at +0x20 `0080` | desc u16 +0x20 = 0x8000 at runtime; 2-byte field present (static movzx size 2 `0x66415bf movzx eax,word ptr [rsi+0x20]`; feeds pass+0x8A0 u16 vector) | [V live] |
| live tag 2 gameplaymeta+0x00 | 16 | docs/data/live/light_visitor.txt line 4 (tag=2, desc=0x14A5A0): bytes at +0x00 `000010410000803F0000004300007041` | desc f32s +0x00=9.0, +0x04=0.5, +0x08=160.0, +0x0C=15.0 at runtime; 16-byte field present (static movups size 16 `0x6640f8c movups xmm0,[rsi]`) | [V live] |
| live tag 2 gameplaymeta+0x1C | 4 | docs/data/live/light_visitor.txt line 4: bytes at +0x1C `04000000` | desc u32 +0x1C = 4 at runtime; 4-byte field present [V live] |
| live tag 2 gameplaymeta+0x20 | 4 | docs/data/live/light_visitor.txt line 4: bytes at +0x20 `50460000` | desc u32 +0x20 = 18000 at runtime; 4-byte field present [V live] |
| live tag 2 gameplaymeta+0x3C..+0x80 | 4 | docs/data/live/light_visitor.txt line 4: dwords +0x3C..+0x80 non-constant across samples (+0x3C `624901C4` f32=-517.1, +0x40 `E47A2C42` f32=43.12, +0x44 `3D9CFFC3` f32=-511.2, +0x48 `96D2643F` f32=0.894, +0x68 `C851B83D` f32=0.09); second tag-2 sample (line 5) differs at +0x18 | dwords +0x3C..+0x80 are live per-object data (not constants), matching the verbatim 0x84-byte copy (static `0x6641090 add qword ptr [rdi+0x4A0],0x84`, stride 0x84 [V]); producer-inferred meanings (+0x1C dimension, +0x20 biome) are [I], not names | [V live] |
| live tag 3/4 desc | - | not present in docs/data/live/light_visitor.txt (dump contains tags 5,0,1,2 only) | LightPointDescription (0x108B) and ShadowAtlasFrameDescription (0x50B) field sizes/values not yet confirmed live | [? pending] |

### 4. Light-visitor writers to pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — proven [V] (not redone this unit)

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| pass+0x800 | 8 | `0x6640e84  mov rdx,[rsi+0x800]`<br>`0x6640e8b  cmp rdx,[rsi+0x808]`<br>`0x6640eb4  add qword ptr [rsi+0x800],0x14`<br>`0x6641761  mov rdx,[rsi+0x800]`<br>`0x66417a2  add qword ptr [rsi+0x800],0x14`<br>`0x6641517  add qword ptr [rsi+0x800],0x14` | end cursor of the 0x14-byte summary list (cap +0x808); writers: Ambient 0x6640eb4, Directional 0x66417a2, Point 0x6641517 [V] | [V] |
| pass+0x808 | 8 | `0x6640e8b  cmp rdx,[rsi+0x808]` | summary list cap cursor [V] | [V] |
| pass+0x648 | 8 | `0x66416f8  lea rcx,[rsi+0x648]`<br>`0x66416ff  call 0x675FB30`<br>`0x664145a  lea rcx,[rsi+0x648]`<br>`0x6641461  call 0x675FB30` | end cursor of the 0x48-byte light-record vector (begin +0x648 / end +0x650); writers Directional (0x66416ff) and Point (0x6641461) via 0x675FB30 [V] | [V] |
| pass+0x650 | 4 | `0x6641729  mov eax,[rsi+0x650]`<br>`0x6641735  shr eax,3`<br>`0x6641738  imul eax,0xFFFF8E39` | light-record end cursor; light-record index = (end - begin)/0x48 - 1 [V] | [V] |
| pass+0x4A0 | 8 | `0x6640f78  mov r12,[rdi+0x4A0]`<br>`0x6641090  add qword ptr [rdi+0x4A0],0x84` | end cursor of the 0x84-byte GameplayMetadata vector (begin +0x498 / cap +0x4A8); writer tag 2, stride 0x84 [V] | [V] |
| pass+0x4A8 | 8 | `0x6640f7f  cmp r12,[rdi+0x4A8]` | GameplayMetadata vector cap cursor [V] | [V] |
| pass+0x1D0 | 8 | `0x66419c6  add qword ptr [rsi+0x1D0],0x50` | end cursor of the 0x50-byte ShadowAtlasFrame vector (begin +0x1C8 / cap +0x1D8); writer tag 4, stride 0x50 [V] | [V] |

Every one of these writes is an end-cursor increment; no end-cursor pop/decrement exists anywhere in the exe [V, whole-image fld --w scans, earlier units].

### 5. Consumers of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — not located [?] (single blocking fact)

Static sweep (earlier units, not redone): whole-image `rdis fld --r/--w` scans for all four offsets and begin cursors 0x7F8/0x650/0x498/0x1C8 — only the light-visitor writer cursor accesses [V] plus stack/unrelated same-offset accesses; every write is an end-cursor increment, no pop/decrement [V]; no `[pass_base + index*stride]` element read anywhere [?]; endFrame full listing contains none of the four offsets though it calls 0x5ABA5C0 three times [V]; the three other direct 0x5ABA5C0 callers touch only stack locals [V]; `rdis ptr 0x5aba5c0`: no indirect caller slot [V].

Live angle (this unit): `tools/livecap/request.py` logs function-entry REG/pointee bytes plus `ret=` caller only — hardware execute breakpoints, it CANNOT watch memory reads, and no consumer entry RVA is known to target. The pending capture below targets the producer side (description bytes + visitor caller chain), so it cannot name a vector consumer either.

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| pass+0x800 element read | - | - | no draining reader of the 0x14-byte summary elements located anywhere in Minecraft.Windows.exe 1.26.62.01; only the three light-visitor end-cursor writers above [V] | [?] |
| pass+0x648 element read | - | - | no draining reader of the 0x48-byte light-record elements located anywhere in the exe [?] | [?] |
| pass+0x4A0 element read | - | - | no draining reader of the 0x84-byte GameplayMetadata elements located anywhere in the exe [?] | [?] |
| pass+0x1D0 element read | - | - | no draining reader of the 0x50-byte ShadowAtlasFrame elements located anywhere in the exe [?] | [?] |

### 6. Live capture request (2026-11-22 orchestrator hint; static analysis exhausted)

CAPTURE REQUESTED oc_u_er6_light_desc — already queued (pending, rva=0x6640d80 light-visitor entry, size 0x100, max 6), requested by an earlier unit; request.py blocks re-adding a duplicate pending rva. Why: R6 — confirm tag 3 LightPoint (0x108B) and tag 4 ShadowAtlasFrame (0x50B) description field sizes/runtime values vs Descriptions.h layouts; ret= names the visitor caller chain (producer side: BgfxFrameBuilder Light-group insert). Result path: docs/data/live/oc_u_er6_light_desc.txt — check with `python tools/livecap/request.py result oc_u_er6_light_desc`. This capture cannot observe memory reads, so it cannot close the consumer blocking fact below.

## CLOSES?

NO — single blocking fact: no draining reader (element consumer) of pass+0x800 / pass+0x648 / pass+0x4A0 / pass+0x1D0 is located in Minecraft.Windows.exe 1.26.62.01; all four vectors are write-only [V writers]; static sweep exhausted [V negative]; the live capture tool cannot watch memory reads and no consumer entry RVA is known (pending capture targets desc bytes + producer caller chain only). Description field value names also remain unknown [?]: no RTTI and no description member name strings in the exe; live bytes confirm field sizes/offsets at runtime [V live] but not names. What IS closed [V]: tag names (tag 2 = GameplayMetadata, tag 3 = LightPoint) and the group_visitors.md vs FrameBuilder.h tag-name conflict (FrameBuilder.h wins; group_visitors.md had 2/3 swapped), plus the four Light-visitor writers to pass+0x800/+0x648/+0x4A0/+0x1D0.

## TOOL REQUESTS

CAPTURE REQUESTED oc_u_er6_light_desc (pending; see section 6). No helper scripts written; nothing to add — the `fld` per-offset scan blind spot (cursor-register indexed element reads) remains a tool gap, and the live capture tool logs function entry only, no data write-watch.
