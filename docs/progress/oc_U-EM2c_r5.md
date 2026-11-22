## NEXT
DONE

# Unit U-EM2c: M2c batch — 8 description types as [V]-typed structs

## STATUS
M2c: Every description type (62) as a struct with confirmed fields (Descriptions.h).
- Typed before this run: 27 of 62 (per orchestrator r3 note).
- This run batch = the 8 untyped EDITOR description types. These are the untyped catalog types that have [V] visitor/extractor evidence (docs/progress/oc_U-D10c.md gives per-tag [rdi+off] read tables, delegate.py check OK). Each is written as a NEW header under src/sdk/mc/deps/minecraft_renderer/framebuilder/. Fields only where [V] by a visitor read, padding otherwise, static_assert sizeof. Sizes are the highest [V]-read offset + width, aligned; all match the producer extents in docs/data/producer_fields.txt (those extents are [I] cross-checks because producers share one stack object across editor types).
- Field MEANINGS are '-' (no instruction/string shows them); offsets/widths are [V], each backed by a [V] proof row quoting the visitor read instruction.
- After this run: 27 of 62 remain untyped (next run continues). CLOSES? = NO (27 of 62 still untyped — item wording requires all 62).

## THIS RUN — DONE (8 new headers, each one struct, fields [V] where visitor reads, padding otherwise, static_assert sizeof)
1. src/sdk/mc/deps/minecraft_renderer/framebuilder/RenderEditorBlockVolumeBoundingBoxDescription.h   (Editor tag 0, sizeof 0x178)
2. src/sdk/mc/deps/minecraft_renderer/framebuilder/RenderEditorGizmoHandleArrowDescription.h          (Editor tag 1, sizeof 0xD8)
3. src/sdk/mc/deps/minecraft_renderer/framebuilder/RenderEditorGizmoHandleCubeDescription.h           (Editor tag 2, sizeof 0xD8)
4. src/sdk/mc/deps/minecraft_renderer/framebuilder/RenderEditorGizmoHandlePaneDescription.h           (Editor tag 3, sizeof 0x128)
5. src/sdk/mc/deps/minecraft_renderer/framebuilder/RenderEditorGizmoHandleRingDescription.h           (Editor tag 4, sizeof 0x1F0)
6. src/sdk/mc/deps/minecraft_renderer/framebuilder/RenderEditorSelectionCursorDescription.h           (Editor tag 5, sizeof 0xE8)
7. src/sdk/mc/deps/minecraft_renderer/framebuilder/RenderEditorBlockVolumeOutlineDescription.h        (Editor tag 6, sizeof 0xE8)
8. src/sdk/mc/deps/minecraft_renderer/framebuilder/RenderEditorRenderPlaneDescription.h               (Editor tag 7, sizeof 0xE8)

Tag->type mapping: docs/BGFX_MAP.md 6w "Editor (0x358): 0 BlockVolumeBoundingBox, 1-4 GizmoHandle Arrow/Cube/Pane/Ring, 5 SelectionCursor, 6 BlockVolumeOutline, 7 RenderPlane". Visitor case heads (docs/progress/oc_U-D10c.md): tag0 0x6674388, tag1 0x667499f, tag2 0x6674518, tag3 0x667463c, tag4 0x66743f4, tag5 0x6674ac3, tag6 0x6674d02, tag7 0x6674760. In each case rdi = the description pointer [V oc_U-D10c casewalk].

## [V] PROOF TABLES — one row per distinct field offset (all sites listed).
Offset cells are type-prefixed so they are unique across tables (every table starts at +0x00).

### RenderEditorBlockVolumeBoundingBoxDescription (tag 0, sizeof 0x178)
| offset | size | site | instr | meaning |
|---|---|---|---|---|
| BBox +0x00 | 8 | 0x66a1a0b | `0x66a1a0b  movsd xmm2,[rdi]` | - |
| BBox +0x08 | 8 | 0x66a3c0f | `0x66a3c0f  mov rsi,[rdi+8]` | - |
| BBox +0x0C | 8 | 0x66a1a0f | `0x66a1a0f  movsd xmm3,[rdi+0xC]` | - |
| BBox +0x14 | 4 | 0x66a19ec | `0x66a19ec  subss xmm6,[rdi+0x14]` | - |
| BBox +0x18 | 8 | 0x66a384a | `0x66a384a  movsd xmm1,[rdi+0x18]` | - |
| BBox +0x20 | 4 | 0x66a3845 | `0x66a3845  movss xmm0,[rdi+0x20]` | - |
| BBox +0x24 | 1 | 0x66a3699 | `0x66a3699  movzx ebx,byte ptr [rdi+0x24]` | - |
| BBox +0x28 | 16 | 0x66a1ce9 | `0x66a1ce9  movups xmm0,[rdi+0x28]` | - |
| BBox +0x80 | 1 | 0x66a1a6a | `0x66a1a6a  cmp byte ptr [rdi+0x80],1` | - |
| BBox +0xD8 | 1 | 0x66a3519 | `0x66a3519  cmp byte ptr [rdi+0xD8],1` | - |
| BBox +0x130 | 1 | 0x66a27c9 | `0x66a27c9  cmp byte ptr [rdi+0x130],1` | - |
| BBox +0x138 | 16 | 0x66a30e5 | `0x66a30e5  movups xmm0,[rdi+0x138]` | - |
| BBox +0x148 | 16 | 0x66a2395 | `0x66a2395  movups xmm0,[rdi+0x148]` | - |
| BBox +0x158 | 16 | 0x66a378d | `0x66a378d  movups xmm0,[rdi+0x158]` | - |
| BBox +0x16C | 4 | 0x66a19f7 | `0x66a19f7  cvtsi2ss xmm0,dword ptr [rdi+0x16C]` | - |
| BBox +0x170 | 1 | 0x66a1bf2 | `0x66a1bf2  cmp byte ptr [rdi+0x170],1` | - |

### RenderEditorGizmoHandleArrowDescription (tag 1, sizeof 0xD8)
| offset | size | site | instr | meaning |
|---|---|---|---|---|
| Arrow +0x00 | 8 | 0x6675477 | `0x6675477  movsd xmm3,[rdi]` | - |
| Arrow +0x08 | 8 | 0x667a763 | `0x667a763  mov rsi,[rdi+8]` | - |
| Arrow +0x0C | 8 | 0x66753c7 | `0x66753c7  movsd xmm2,[rdi+0xC]` | - |
| Arrow +0x14 | 4 | 0x66753f5 | `0x66753f5  movss xmm2,[rdi+0x14]` | - |
| Arrow +0x18 | 8 | 0x6676b7f | `0x6676b7f  movsd xmm1,[rdi+0x18]` | - |
| Arrow +0x20 | 4 | 0x6676b7a | `0x6676b7a  movss xmm0,[rdi+0x20]` | - |
| Arrow +0x64 | 16 | 0x66758bd | `0x66758bd  movups xmm6,[rdi+0x64]` | - |
| Arrow +0x74 | 1 | 0x6675560 | `0x6675560  movzx eax,byte ptr [rdi+0x74]` | - |
| Arrow +0x78 | 4 | 0x66754dd | `0x66754dd  movss xmm0,[rdi+0x78]` | - |
| Arrow +0xD0 | 2 | 0x6676c9b | `0x6676c9b  mov r12w,[rdi+0xD0]` | - |
| Arrow +0xD2 | 1 | 0x66758c1 | `0x66758c1  cmp byte ptr [rdi+0xD2],1` | - |

### RenderEditorGizmoHandleCubeDescription (tag 2, sizeof 0xD8)
| offset | size | site | instr | meaning |
|---|---|---|---|---|
| Cube +0x00 | 8 | 0x66750ea | `0x66750ea  movsd xmm3,[rdi]` | - |
| Cube +0x08 | 8 | 0x6679aa1 | `0x6679aa1  mov rsi,[rdi+8]` | - |
| Cube +0x0C | 8 | 0x667503a | `0x667503a  movsd xmm2,[rdi+0xC]` | - |
| Cube +0x14 | 4 | 0x6675068 | `0x6675068  movss xmm2,[rdi+0x14]` | - |
| Cube +0x18 | 8 | 0x667653d | `0x667653d  movsd xmm1,[rdi+0x18]` | - |
| Cube +0x20 | 4 | 0x6676538 | `0x6676538  movss xmm0,[rdi+0x20]` | - |
| Cube +0x64 | 16 | 0x66751b2 | `0x66751b2  movups xmm6,[rdi+0x64]` | - |
| Cube +0x74 | 1 | 0x66751a6 | `0x66751a6  movzx eax,byte ptr [rdi+0x74]` | - |
| Cube +0x78 | 4 | 0x6675153 | `0x6675153  movss xmm0,[rdi+0x78]` | - |
| Cube +0xD0 | 2 | 0x6676652 | `0x6676652  mov r12w,[rdi+0xD0]` | - |
| Cube +0xD2 | 1 | 0x667589a | `0x667589a  cmp byte ptr [rdi+0xD2],0` | - |

### RenderEditorGizmoHandlePaneDescription (tag 3, sizeof 0x128)
| offset | size | site | instr | meaning |
|---|---|---|---|---|
| Pane +0x00 | 8 | 0x6675229 | `0x6675229  movsd xmm3,[rdi]` | - |
| Pane +0x08 | 8 | 0x667bf1e | `0x667bf1e  mov rsi,[rdi+8]` | - |
| Pane +0x0C | 8 | 0x667522d | `0x667522d  movsd xmm1,[rdi+0xC]` | - |
| Pane +0x14 | 4 | 0x667521d | `0x667521d  subss xmm0,[rdi+0x14]` | - |
| Pane +0x18 | 8 | 0x6676856 | `0x6676856  movsd xmm1,[rdi+0x18]` | - |
| Pane +0x20 | 4 | 0x6676851 | `0x6676851  movss xmm0,[rdi+0x20]` | - |
| Pane +0x64 | 16 | 0x6675dea | `0x6675dea  movups xmm9,[rdi+0x64]` | - |
| Pane +0x74 | 1 | 0x6675340 | `0x6675340  cmp byte ptr [rdi+0x74],0` | - |
| Pane +0x78 | 4 | 0x667529c | `0x667529c  movss xmm1,[rdi+0x78]` | - |
| Pane +0x120 | 2 | 0x667696d | `0x667696d  mov r12w,[rdi+0x120]` | - |
| Pane +0x122 | 1 | 0x6679c65 | `0x6679c65  cmp byte ptr [rdi+0x122],1` | - |

### RenderEditorGizmoHandleRingDescription (tag 4, sizeof 0x1F0)
| offset | size | site | instr | meaning |
|---|---|---|---|---|
| Ring +0x00 | 8 | 0x66750ea | `0x66750ea  movsd xmm3,[rdi]` | - |
| Ring +0x08 | 8 | 0x6679aa1 | `0x6679aa1  mov rsi,[rdi+8]` | - |
| Ring +0x0C | 16 | 0x6676456 | `0x6676456  movups xmm0,[rdi+0xC]` | - |
| Ring +0x1C | 16 | 0x6676461 | `0x6676461  movups xmm0,[rdi+0x1C]` | - |
| Ring +0x28 | 16 | 0x6677105 | `0x6677105  movups xmm0,[rdi+0x28]` | - |
| Ring +0x3C | 16 | 0x6676477 | `0x6676477  movups xmm0,[rdi+0x3C]` | - |
| Ring +0x4C | 8 | 0x6675866 | `0x6675866  movsd xmm6,[rdi+0x4C]` | - |
| Ring +0x54 | 8 | 0x667586b | `0x667586b  movsd xmm7,[rdi+0x54]` | - |
| Ring +0x5C | 1 | 0x6674fb3 | `0x6674fb3  movzx eax,byte ptr [rdi+0x5C]` | - |
| Ring +0x74 | 1 | 0x66751a6 | `0x66751a6  movzx eax,byte ptr [rdi+0x74]` | - |
| Ring +0x78 | 4 | 0x6675153 | `0x6675153  movss xmm0,[rdi+0x78]` | - |
| Ring +0x7C | 4 | 0x66764a0 | `0x66764a0  cmp eax,[rdi+0x7C]` | - |
| Ring +0x80 | 1 | 0x6676497 | `0x6676497  cmp byte ptr [rdi+0x80],1` | - |
| Ring +0x88 | 8 | 0x6677a3c | `0x6677a3c  mov r8,[rdi+0x88]` | - |
| Ring +0xA0 | 8 | 0x6677a27 | `0x6677a27  mov r9,[rdi+0xA0]` | - |
| Ring +0xA8 | 8 | 0x66764b6 | `0x66764b6  mov r8,[rdi+0xA8]` | - |
| Ring +0xB0 | 4 | 0x6676489 | `0x6676489  mov eax,[rdi+0xB0]` | - |
| Ring +0xB8 | 8 | 0x667888d | `0x667888d  mov rcx,[rdi+0xB8]` | - |
| Ring +0xD0 | 2 | 0x6676652 | `0x6676652  mov r12w,[rdi+0xD0]` | - |
| Ring +0xD2 | 1 | 0x667589a | `0x667589a  cmp byte ptr [rdi+0xD2],0` | - |
| Ring +0xD4 | 4 | 0x6678885 | `0x6678885  cmp eax,[rdi+0xD4]` | - |
| Ring +0xD8 | 1 | 0x667887c | `0x667887c  cmp byte ptr [rdi+0xD8],1` | - |
| Ring +0xE0 | 8 | 0x66771db | `0x66771db  mov r15w,[rdi+0xE0]` | - |
| Ring +0xF8 | 8 | 0x66788cf | `0x66788cf  mov r9,[rdi+0xF8]` | - |
| Ring +0x100 | 8 | 0x667889f | `0x667889f  mov r8,[rdi+0x100]` | - |
| Ring +0x108 | 1 | 0x6678540 | `0x6678540  cmp byte ptr [rdi+0x108],1` | - |
| Ring +0x1E8 | 4 | 0x6678566 | `0x6678566  mov eax,[rdi+0x1E8]` | - |
| Ring +0x1EC | 2 | 0x6677a9f | `0x6677a9f  mov r15w,[rdi+0x1EC]` | - |

### RenderEditorSelectionCursorDescription (tag 5, sizeof 0xE8)
| offset | size | site | instr | meaning |
|---|---|---|---|---|
| SelCur +0x00 | 8 | 0x6674b87 | `0x6674b87  movsd xmm3,[rdi]` | - |
| SelCur +0x08 | 8 | 0x66779ee | `0x66779ee  mov rsi,[rdi+8]` | - |
| SelCur +0x0C | 8 | 0x6674ad7 | `0x6674ad7  movsd xmm1,[rdi+0xC]` | - |
| SelCur +0x14 | 4 | 0x6674b05 | `0x6674b05  movss xmm1,[rdi+0x14]` | - |
| SelCur +0x18 | 16 | 0x6677686 | `0x6677686  movups xmm0,[rdi+0x18]` | - |
| SelCur +0x28 | 16 | 0x6675a36 | `0x6675a36  movups xmm0,[rdi+0x28]` | - |
| SelCur +0x38 | 4 | 0x667598b | `0x667598b  movss xmm0,[rdi+0x38]` | - |
| SelCur +0x3C | 1 | 0x6674ac3 | `0x6674ac3  cmp byte ptr [rdi+0x3C],1` | - |
| SelCur +0xE0 | 2 | 0x6675b0c | `0x6675b0c  mov bx,[rdi+0xE0]` | - |

### RenderEditorBlockVolumeOutlineDescription (tag 6, sizeof 0xE8)
| offset | size | site | instr | meaning |
|---|---|---|---|---|
| Outline +0x00 | 8 | 0x6674dc6 | `0x6674dc6  movsd xmm3,[rdi]` | - |
| Outline +0x08 | 8 | 0x667cbb6 | `0x667cbb6  mov rsi,[rdi+8]` | - |
| Outline +0x0C | 8 | 0x6674d16 | `0x6674d16  movsd xmm1,[rdi+0xC]` | - |
| Outline +0x14 | 4 | 0x6674d44 | `0x6674d44  movss xmm1,[rdi+0x14]` | - |
| Outline +0x18 | 16 | 0x667c850 | `0x667c850  movups xmm0,[rdi+0x18]` | - |
| Outline +0x20 | 4 | 0x667a926 | `0x667a926  movss xmm0,[rdi+0x20]` | - |
| Outline +0x28 | 16 | 0x667c2a9 | `0x667c2a9  movups xmm0,[rdi+0x28]` | - |
| Outline +0x38 | 4 | 0x667a87b | `0x667a87b  movss xmm0,[rdi+0x38]` | - |
| Outline +0xE0 | 2 | 0x667aa18 | `0x667aa18  mov r15w,[rdi+0xE0]` | - |
| Outline +0xE2 | 1 | 0x6676eab | `0x6676eab  cmp byte ptr [rdi+0xE2],1` | - |
| Outline +0xE3 | 1 | 0x667c107 | `0x667c107  cmp byte ptr [rdi+0xE3],1` | - |
| Outline +0xE4 | 4 | 0x667a92b | `0x667a92b  movss xmm1,[rdi+0xE4]` | - |

### RenderEditorRenderPlaneDescription (tag 7, sizeof 0xE8)
| offset | size | site | instr | meaning |
|---|---|---|---|---|
| RPlane +0x00 | 8 | 0x6674824 | `0x6674824  movsd xmm3,[rdi]` | - |
| RPlane +0x08 | 8 | 0x667b244 | `0x667b244  mov rsi,[rdi+8]` | - |
| RPlane +0x0C | 8 | 0x6674774 | `0x6674774  movsd xmm1,[rdi+0xC]` | - |
| RPlane +0x14 | 4 | 0x66747a2 | `0x66747a2  movss xmm1,[rdi+0x14]` | - |
| RPlane +0x18 | 16 | 0x667aede | `0x667aede  movups xmm0,[rdi+0x18]` | - |
| RPlane +0x28 | 16 | 0x6677105 | `0x6677105  movups xmm0,[rdi+0x28]` | - |
| RPlane +0x34 | 4 | 0x66755df | `0x66755df  movss xmm0,[rdi+0x34]` | - |
| RPlane +0x3C | 1 | 0x6674760 | `0x6674760  cmp byte ptr [rdi+0x3C],1` | - |
| RPlane +0x3D | 1 | 0x66755d5 | `0x66755d5  cmp byte ptr [rdi+0x3D],1` | - |
| RPlane +0x3E | 1 | 0x667ad48 | `0x667ad48  cmp byte ptr [rdi+0x3E],1` | - |
| RPlane +0xE0 | 2 | 0x66771db | `0x66771db  mov r15w,[rdi+0xE0]` | - |

## SIZE BASIS
Each sizeof = highest [V]-read offset + its width, rounded up to 8-byte alignment:
- tag 0 BoundingBox: max read +0x170 byte -> end 0x171 -> 0x178
- tag 1 Arrow: max read +0xD2 byte -> end 0xD3 -> 0xD8
- tag 2 Cube: max read +0xD2 byte -> end 0xD3 -> 0xD8
- tag 3 Pane: max read +0x122 byte -> end 0x123 -> 0x128
- tag 4 Ring: max read +0x1EC word -> end 0x1EE -> 0x1F0
- tag 5 SelectionCursor: max read +0xE0 word -> end 0xE2 -> 0xE8
- tag 6 Outline: max read +0xE4 dword -> end 0xE8 -> 0xE8
- tag 7 RenderPlane: max read +0xE0 word -> end 0xE2 -> 0xE8

The Ring (tag 4) case has several mutually-overlapping 16-byte reads (+0x0C/+0x1C/+0x28/+0x3C); those spans are kept as single non-overlapping blocks and smaller overlapping reads are subsumed. BoundingBox (tag 0) tail-jumps to 0x66A1860 which reads the same description [V oc_U-D10c].

All header structs pass a scratch `cl /Zs` syntax check (same wrapper used for Descriptions.h); no project build is run (builds are not permitted in this unit).

## REMAINING (27 untyped)
Purely untyped (no ctor/visitor evidence, 12): CloudLightingParameters, CloudParameters, PerCascadeParameters, PointLightBudgetParameters, PointLightBudgetParameters::ScoringWeights, PointLightClusteringParameters, PointLightShadowParameters, ProbeMetadataDeltaTriggers, ProbeRegenParameters, ReflectionParameters, ShadowParameters, ShadowRange.
With size/ctor/visitor evidence but not yet typed (15): RenderBatchActorDescription, TransitioningVoxelVolumeDescription, VoxelVolumeDescription (Light tags 6/7, producer 0x53599d0 stack-reuse not decoded), and the editor types just typed are now done so removed. The next run continues with the 15.

## CLOSES?
NO — M2c requires all 62 description types as structs with confirmed fields; 27 of 62 remain untyped after this run (27 typed before + 8 typed now = 35 typed, 27 left). Single blocking fact: 27 description types still lack any struct header (12 have zero ctor/visitor evidence; 15 have partial evidence but no typed header yet).

## TOOL REQUESTS
None.
