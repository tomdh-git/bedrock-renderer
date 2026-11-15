# UI and Editor group descriptions, Nametag / MeshFallback / BatchActor, and the six group tag enums (D8, D10, D11, D12)

Exe 1.26.62.01, RVAs image-relative, static analysis only. Tags: [V] instruction seen in a listing AND re-run with rdis (131 instruction claims re-run at the end of the pass, 0 mismatches), [I] inference, [?] open.
Typed read-views: `src/sdk/mc/deps/minecraft_renderer/framebuilder/UiEditorDescriptions.h` (offsetof asserts only for displacements seen; compiled standalone with MSVC /Zs together with FrameBuilder.h).
Enum tables: `FrameBuilder.h`. Pass method: per-case control-flow walk from each jump-table head over the exact listing (calls continue; `call 0x1A2800`, `call [0xF9A8C78]`, 0x75740, 0x75B60,
0x1166E0, ret and int3 end a path); the cold TLS-guard stubs are NOT followed past their terminating calls. All reachable sets still include the shared join code, so a displacement is attributed to a case
only when it is read on a path from that case's head.

## Listings (tools/sigs/dumplist.py, exact rdis text; function ends from docs/data/inventory_L4L5_builder.tsv: next function start)
| file | range | what |
|---|---|---|
| docs/data/listings/ui_visitor_6664a00_6668510.txt | 0x6664a00..0x6668510 (3152 lines) | UI group visitor: Gameface forwarder, HudIcon, UIMesh, UIText, UIImGui cases + cold stubs (ret at 0x6668106) |
| docs/data/listings/editor_visitor_66742f0_667e290.txt | 0x66742f0..0x667e290 (8170 lines) | Editor group visitor, all 8 cases + shared tails + cold stubs (ret at 0x667cd01) |
| docs/data/listings/gameface_66ade80_66b0eb0.txt | 0x66ade80..0x66b0eb0 (2414 lines) | Gameface/Renoir extractor (UI tag 0 tail jump) |
| docs/data/listings/nametag_ctor_668b6e0_668b850.txt | 77 lines | RenderNametagDescription constructor |
| docs/data/listings/meshfallback_ctor_668b850_668be49.txt | 299 lines | RenderMeshFallbackDescription constructor |
| docs/data/listings/batchactor_producer_4e355a0_4e3606c.txt | 635 lines | BatchActor producer 0x4e355a0 (call to the clone at 0x4e35ddf) |

## D12: tag -> type, per group [V unless marked]
Method: tag byte `mov byte ptr [rbp+X],N` before `mov rax,[rax+slot]` in each insert clone (script scratchpad tags.py = rdis dis of 1400 insns per clone), the type from the zone record
(tools/sigs/srcloc.py), the case count from the visitor jump table. Slots: Editor 0x358, Effect 0x360, UI 0x368, Sky 0x370, Item 0x378, Light 0x380.
| group | visitor / table / cases | tag: type (tag store address) |
|---|---|---|
| Editor | 0x66742f0 / 0xF2BF520 / 8 | 0 BlockVolumeBoundingBox (0x6c95724), 1 GizmoHandleArrow (0x4c85de4), 2 Cube (0x4c85fa4), 3 Pane (0x4c86164), 4 Ring (0x4c86324), 5 SelectionCursor (0x53711d4), 6 BlockVolumeOutline (0x6c96254), 7 RenderPlane (0x6d3d32d). Types from srcloc: 0x6c956b0, 0x4c85d70, 0x4c85f30, 0x4c860f0, 0x4c862b0, 0x5371160, 0x6c961e0, 0x6d3c040. Unchanged. |
| Effect | 0x666aca0 / 0xF2BF49C / 9 | 0 FlameBillboard (0x594eb1f, slot 0x594eb29), 1 BlitFlipbook (0x5acbe94), 2 Particle (0x5b8d594), 3 PlayerVision (0x53e66fc), 4 Shadow (0x53e73ef), 5 FadeToBlack [I: no clone found; order of BGFX_MAP 6g + the case at 0x666afde], 6 CameraAimAssistHighlight (0x5370ef4), 7 FullscreenEffect (0x530a67b), 8 EditorHighlight (0x4c8a624). CORRECTION: FrameBuilder.h had `UIGameface = 0`; the Gameface clone 0x1f44d80 stores tag 0 at 0x1f451e5 and calls the UI slot 0x368. |
| UI | 0x6664a00 / 0xF2BF468 / 5 | 0 Gameface (0x1f451e5), 1 HudIcon (0xe9b45b), 2 UIMesh (0x4c961b4), 3 UIText (0xe7217f), 4 UIImGui (added: case 0x6664aab builds material "Debug/ImGui", literal 0xF5AD096, length 0xB at 0x6664af7; no clone found). Table entries 0x6664a6c 0x6664d51 0x6664bd6 0x6664c83 0x6664aab. |
| Sky | 0x66560f0 / 0xF2BF39C / 11 | unchanged 0..10 (Atmosphere 0x53e3291, Clouds 0x53e915d, Cubemap 0x660b794, EndSky 0x5370814, LegacyCubemap 0x660b3dc, SkyStars 0x536a2d8, Celestial 0x5370b94, VolFog 0x53e4a36, Weather 0x5ad5874, SkyAmbientSamples 0x53e487b); `Stars = 6` ADDED (visitor case 0x6656812, docs/functions/66560f0_sky_cases.md section 5; the shared clone 0x5369b30 only stores 5). |
| Item | 0x6646980 / 0xF2BF2D0 / 11 | unchanged: 0 EnvText (0xe71c49), 1 Nametag (0x11274e4), 2 MeshFallback (0x4def8ed), 3 ChunkGeometry (0x15a68f4), 4 ChunkOccluders (0x5369994), 5 Crack (0x53a052a), 6 ItemInHand (0x531b1f4), 7 SkinnedMesh (0x4e3a4b4), 8 BlockSelectionOverlay (0x539c91d), 9 BlockChanges [I: variant order, no clone found], 10 BatchActor (0x4e39d24). |
| Light | 0x6640d80 / 0xF2BF2B0 / 8 | 0 Ambient (0x53e3511), 1 Directional (0x53709d4), 2 GameplayMetadata (0x53e5fb4), 3 LightPoint (0x535a9b7), 4 ShadowAtlasFrame (0x535a696), 5 ServerGraphicsOverrideParameters (clone 0x6c2e820: store 0x6c2f6dc, slot 0x380 at 0x6c2f6e6), 6 VoxelVolume (0x535ad34), 7 TransitioningVoxelVolume (0x535aeb9). Enum gained the four missing names. |
Open in D12: the names FadeToBlack (Effect 5), BlockChanges (Item 9) and the UIImGui description type have no clone with a zone record; the enum VALUES exist (case counts match) and the first two names rest on the variant order.

## D8 UI group
- Dispatch [V]: `movzx eax,byte ptr [r8+8]` 0x6664a44, `cmp rax,4`, table 0xF2BF468. In every UI case rdx = frame context, the description is `[r8]` (kept in r9). Gameface (tag 0) is a forwarder to 0x66ade80.
- **UIMesh (tag 2, case 0x6664bd6)** is inline and calls the UI draw function 0x674A3A0 with r8d = 0 (`xor r8d,r8d` 0x6664f47, `call` 0x6664f4a) [V]. Every displacement the case reads and the call slot it feeds
  is tabulated in the header comment (`+0x00,+0x08,+0x10` qwords, `+0x18` array address, `+0x28/+0x30` refs[1] pair only when the count at `+0x58` is >= 2, `+0x60,+0x68` qwords, `+0x70` float, `+0x78` qword, bytes `+0x80..+0x85`, address `+0x86`,
  variant at `+0x88`). `mode = +0x83 ? 2 : (+0x82 ? 1 : +0x84)` is computed from three flag bytes (0x6664bde..0x6664c03) and passed as a dword stack argument (`uiMeshMode`). All of it sits inside RenderUIMeshDescription (0xA8, Descriptions.h);
  the NEW facts are the roles above. Semantic names of the qwords: [?] (they are forwarded; the consumer 0x674a3a0 is documented in docs/functions/674a3a0.md / oc_U-UI5.md at call level, its stack-argument slots were not re-mapped here).
- **HudIcon (tag 1, case 0x6664d51)** [V]: material "UI/Blit" (0xF539A95, length 7) via 0x675E440. Correction of the earlier reading: description `+0x00` is a pointer to a source object, not data: `mov rsi,[r8]` (0x666524c) is the mce::Mesh
  (its +0x58/+0x60 vector sized /12 with the 0xAAAAAAAB multiply, +0x1B0/+0x1B8 shared pair, +0x1D0 u32 count and +0x1D4 flag at 0x66654fb/0x6665503 = RenderControllerMesh fields), `[r8+0x18]` is a vertex count (x12 bytes at 0x66652fa), `[r8+0x20]` the
  vec3 array, `[r8+0x28]` a float splatted into a vec4 (0x66651ae). The 4x4 at description `+0x08` (`lea rdi,[rcx+8]` 0x666531b) is multiplied (0xAA6580) into every vertex (loop 0x6665444..0x66654ee, stride 0xC in, 0x40 out); the word at `+0x48`
  goes to the draw record's 16-bit key. `HudIconSourceView` in the header. Case tail: the pass-record kind switch table 0xF2BF48C (4 entries) at 0x6665c7e, then the common append through 0x5ABA5C0 (0x9D0 pass object) at 0x6667985.
- **Gameface (tag 0)**: header GamefaceDescription.h re-verified against the new listing: reads of the description (r8 = rsi, spilled at [rbp+0x520] and reloaded into r14) are exactly +0x00 (kind), +0x04..+0x08 (blend), +0x0C, +0x0D, +0x0E, +0x0F and +0x13 windows,
  +0x17, +0x28, +0x30, +0x38, +0x40, +0x48, +0x50, +0x58 (movups 0x66ae227), +0x68, +0x80. NEW: `[desc+0x80]` is a pointer to a `{begin, end}` pair (0x66aecc2..0x66aecd0), records stride 0x1A0 (0x66aece0): `GamefaceRecordList`. The existing header calls +0x80 "list" and is correct only in that sense.
- **UIImGui (tag 4)**: material "Debug/ImGui" only; fields not decoded [?].

## D10 Editor group (all reads are rdi = description; per-case sets in UiEditorDescriptions.h)
- Dispatch [V]: `movzx eax,byte ptr [rdx+8]`, `cmp rax,7`, table 0xF2BF520: 0 0x6674388 (tail jump `jmp 0x66A1860`, block volumes), 1 0x667499f, 2 0x6674518, 3 0x667463c, 4 0x66743f4, 5 0x6674ac3, 6 0x6674d02, 7 0x6674760.
- Materials per case (string literals read from the exe): tags 1-4 "EditorBlockVolumeHull" (0xF5A123A, len 0x15); 5 "EditorSelectionCursor" (0xF560B28, len 0x15); 6 "EditorSelectionCursor" + "EditorBlockVolumeWireframe" (0xF5D0DB9, len 0x1A); 7 Wireframe.
- Tags 1-3 (Arrow, Cube, Pane): one head. vec3 at +0x00 (qword + dword +8), vec3 at +0x0C, vec3 at +0x18, mat4 at +0x24 (B operand of 0xAA6580, `lea r8,[rdi+0x24]` 0x6675530), colour vec4 +0x64, flag +0x74 (nonzero: constant 0xF0A40C0 instead of the colour), float +0x78 (scale),
  draw object at +0x80 validated by 0x66A6060 (0x6675522). Arrow and Cube then read word +0xD0 (sort key) and byte +0xD2 (compared with 1 for Arrow, 0 for Cube). Pane takes `lea +0xD0` (an object) and moves the key to word +0x120 with flag byte +0x122.
- Tag 4 (Ring) has a different layout: mat4 at +0x0C (four movups), translation lanes read at +0x3C/+0x44, vec2 +0x4C and +0x54 chosen by byte +0x5C, objects at +0x60 / +0xB8 / +0x110 with enable bytes +0x80 / +0xD8 / +0x108, key word +0x1EC, flag +0x1EE (extent 0x1F0).
- Tags 5-7 share the gate byte +0x3C and the box matrix build from +0x00/+0x0C. Cursor: +0x18/+0x28 blocks, +0x38 float, objects +0x40/+0x90, key +0xE0. Outline adds +0xE2/+0xE3 enables and float +0xE4. RenderPlane adds +0x34 float and gates +0x3D/+0x3E.
- Tag 0 stays EditorBlockVolumeDescription.h (docs/functions/66a1860.md); not re-read here.
- Blocking facts (why D10 stays open): the producers reuse one stack object across the four gizmo types with overlapping layouts (docs/progress/re-descriptions.md: the gizmo producer 0x4c83c80 writes mat4 and floats at conflicting offsets), so no
  struct SIZE is proven (only extents: 0xD8 arrow/cube, 0x128 pane, 0x1F0 ring, 0xE8 plane [I]); the padding between seen offsets (e.g. +0x80..+0xCF, the object bodies read inside 0x66a6060 / 0x66a6190) is not decoded; the roles of vecB/vecC, the second draw form
  and the colour constants are [I].

## D11 Nametag, MeshFallback, BatchActor
- **RenderNametagDescription (Descriptions.h, 0x98)** re-verified against the constructor listing 0x668b6e0 (77 lines): `[rax]=rdx` (owner), 16 floats `[r8+0..0x3C]` -> `[rax+8..0x44]`, 3 floats `[rdi]` -> `+0x48..+0x50`, SharedRef `+0x58/+0x60` (strong count increment first,
  0x668b7dd), 16 bytes `+0x68`, qword `+0x78`, word `+0x80`, optional vec4 `+0x84..+0x93` with the flag byte `+0x94` (0 at 0x668b806, 1 at 0x668b846) [V]. Every static_assert in Descriptions.h holds.
- **RenderMeshFallbackDescription (Descriptions.h, 0x1D0)** re-verified against the constructor listing 0x668b850..0x668be49: stores at +0x88, +0x90..+0xD8 (floats), +0xDC..+0xE0 (bytes), +0xE4/+0xF4 (16 B), +0x108/+0x110 (SharedRef), +0x118, +0x120..+0x150, +0x154..+0x160 (vec4), +0x164 flag (0 at 0x668bb20, 1 at 0x668bb60),
  +0x168 word, +0x170/+0x180, +0x188/+0x190/+0x198, +0x1A0 variant tag (0xFF at 0x668bb95), +0x1A8..+0x1CC (floats) [V]; the header's asserted offsets all fall on these stores.
- **RenderBatchActorDescription (FrameBuilder.h)**. CORRECTION: the producer's description is at [rbp-0x20], so description offset = rbp offset + 0x20. Re-read: head float[7] +0x00 (+ u16 +0x1C, byte +0x30, 16 B +0x34, byte +0x60), then spans {count, data} at
  +0x68 (stride 8), +0x78 (2), +0xC0 (0x14), +0xD0 (0x34), +0xE0 (0x48 = instances, the known count/array), +0xF0 (0x40), +0x100 (0x40) and seven raw begin pointers +0x88..+0xB8 (copied from r10+0x30, +0x48, ..., +0xC0), strides decoded from the magic divides
  (0x4EC4EC4EC4EC4EC5 = /13 after >>2, 0xCCCCCCCCCCCCCCCD = /5 after >>2, 0x8E38E38E38E38E39 = /9 after >>3). The last pair ends at +0x110, so kMinSize is now 0x110 (it was 0x100). The span meanings (shadow caster list, bones, ...) are [I]/[?]; second producer 0x6ebb510 not read.

## Re-verification (rdis, instruction text compared with the claim): 67 (dispatch, UIMesh, HudIcon, editor heads, clone tag stores, producer stores) + 64 (editor reads, BatchActor head and spans, Nametag/MeshFallback ctor stores, Gameface reads) = 131, 0 mismatches.
Exact instruction lines are in the listings above; spot examples: 0x6664f4a `call 0x674A3A0` (UIMesh), 0x666531b `lea rdi,[rcx+8]` (HudIcon matrix), 0x66743ef `jmp 0x66A1860` (tag 0), 0x6675542 `call 0xAA6580` with `lea r8,[rdi+0x24]` at 0x6675530,
0x6d3d32d `mov byte ptr [rbp+0x168],7` (RenderPlane tag), 0x594eb1f/0x594eb29 (Flame tag 0, slot 0x360), 0x6c2f6dc (SGO Light tag 5), 0x4e35d9e / 0x4e35dab (instance count/array = desc +0xE0/+0xE8).
