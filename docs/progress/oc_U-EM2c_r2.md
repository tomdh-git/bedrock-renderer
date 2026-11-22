## NEXT
DONE

# M2c Batch 1 — VoxelVolumeDescription + TransitioningVoxelVolumeDescription

## What changed (paths)

- NEW: src/sdk/mc/deps/minecraft_renderer/framebuilder/VoxelVolumeDescription.h
  - Struct `mce::framebuilder::VoxelVolumeDescription`, size 0x30, 5 [V] fields + padding, static_assert sizeof + offsetofs.
- NEW: src/sdk/mc/deps/minecraft_renderer/framebuilder/TransitioningVoxelVolumeDescription.h
  - Struct `mce::framebuilder::TransitioningVoxelVolumeDescription`, size 0x48, 8 [V] fields + padding, static_assert sizeof + offsetofs.
- No existing files edited (Descriptions.h not modified — the new headers are standalone; they can be included into Descriptions.h in a later pass).

## Types done this run (2 of 35 untyped)

| Type | Group/tag | Size | [V] fields | Evidence |
|---|---|---|---|---|
| VoxelVolumeDescription | Light / 6 | 0x30 | 5 | light visitor 0x6640d80 case 0x664187d [V] |
| TransitioningVoxelVolumeDescription | Light / 7 | 0x48 | 8 | light visitor 0x6640d80 case 0x6641524 [V] |

## Types still untyped (33 remain after this batch)

LightPointDescription, RenderBatchActorDescription, RenderEditorBlockVolumeBoundingBoxDescription,
RenderEditorBlockVolumeOutlineDescription, RenderEditorGizmoHandleArrowDescription,
RenderEditorGizmoHandleCubeDescription, RenderEditorGizmoHandlePaneDescription,
RenderEditorGizmoHandleRingDescription, RenderEditorSelectionCursorDescription, plus 24 further
description types not represented in the BGFX_MAP 6g clone list. (35 untyped total − 2 done = 33.)

## Blocker

Only 2 of the 8 targeted types have [V] field evidence from decoded extractors. The batch-actor
extractor (0x66d9af0, very large) and the editor visitor/extractor (0x66742f0 -> 0x66a1860, very
large) have not been reverse-decoded for description field reads. Editor thin clones have raw
producer stores only ([I] per producer_fields.txt), not [V] ctor/visitor/extractor reads.

## [V] proof rows (one row per distinct offset; all sites listed)

| offset | size | site | instr | meaning |
|---|---|---|---|---|
| +0x00 | 8 | 0x664187d, 0x664213a | `0x664187d  mov rax,[rsi]`; `0x664213a  mov rax,[rsi]` | VoxelVolume mPairA; TransitioningVoxelVolume mPairA — pointer to {object,ctrl} pair [V] |
| +0x08 | 8 | 0x6641b3a, 0x66421a9 | `0x6641b3a  mov rax,[rsi+8]`; `0x66421a9  mov rax,[rsi+8]` | VoxelVolume mPairB; TransitioningVoxelVolume mPairB — pointer to second {object,ctrl} pair [V] |
| +0x10 | 8 | 0x6641bb4, 0x6642223 | `0x6641bb4  mov r13,[rsi+0x10]`; `0x6642223  mov r12,[rsi+0x10]` | VoxelVolume mValue10; TransitioningVoxelVolume mValue10 — qword [V] |
| +0x18 | 8 | 0x6641bd8, 0x6641524 | `0x6641bd8  mov rcx,[rsi+0x18]`; `0x6641524  mov rax,[rsi+0x18]` | VoxelVolume mVecBegin; TransitioningVoxelVolume mValue18 [V] |
| +0x20 | 8 | 0x6641bd4, 0x6642244 | `0x6641bd4  mov rbx,[rsi+0x20]`; `0x6642244  mov rcx,[rsi+0x20]` | VoxelVolume mVecEnd; TransitioningVoxelVolume mVecBegin [V] |
| +0x28 | 8 | 0x6642240 | `0x6642240  mov rbx,[rsi+0x28]` | TransitioningVoxelVolume mVecEnd [V] |
| +0x38 | 8 | 0x6641548 | `0x6641548  mov rcx,[rsi+0x38]` | TransitioningVoxelVolume mDwordBegin [V] |
| +0x40 | 8 | 0x6641544 | `0x6641544  mov rbx,[rsi+0x40]` | TransitioningVoxelVolume mDwordEnd [V] |

## Sizes

- VoxelVolumeDescription: 0x30. Producer (0x53599d0) builds a 0x30-byte object [I producer extent]; visitor reads +0x00..+0x27 (5 qword reads) [V]. +0x28..+0x2F padding.
- TransitioningVoxelVolumeDescription: 0x48. Last read is +0x40 (8 bytes, ends at +0x48) [V]; dossier records "desc size >= 0x48". +0x30..+0x37 padding between mVecEnd (+0x28) and mDwordBegin (+0x38).

## CLOSES?

NO — M2c requires every description type (62) as a struct with confirmed fields. This batch types 2 of the 35 untyped types. 33 remain. The single blocking fact: only 2 of the 8 targeted types have [V] field evidence from decoded extractors; the batch-actor and editor extractors are not yet reverse-decoded for description field reads.
