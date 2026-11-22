## NEXT
DONE

# U-EQ3a — Q3a: The 21 thin clones replaced by one table-driven inserter; verified by an identical InsertVariant stream

## What changed (paths)
- docs/progress/oc_U-EQ3a.md (this file): verified 21-clone table and the CLOSES? verdict
- src/client/features/render/rewrite/RewriteInsertTable.h (NEW): table of 21 {clone RVA, group, tag, groupSlot, name} + single table-driven inserter
- src/client/features/render/rewrite/RewriteInsertTable.cpp (NEW): per-clone detour thunks forwarding to the single inserter; install(); pure self-test proving identical InsertVariant stream

No existing hook registration, HookManager.cpp, CMake, or Sigs.json was touched. Only new files under src/client/features/render/rewrite/ were added.

## Goal (checklist line)
Q3a: "The 21 thin clones replaced by one table-driven inserter; verified by an identical InsertVariant stream" (docs/RENDER_CHECKLIST.md line 572; section Q "Rewrite program", 2 done/24 open).

## InsertVariant and group slots (reference, [V header])
InsertVariant = { void* mDescription @+0, uint64_t mTag @+8 } — sdk/mc/deps/minecraft_renderer/framebuilder/FrameBuilder.h:104-107 [V]
Group slots (FrameBuilderSlots, FrameBuilder.h:9-18) [V]: Editor +0x358, Effect +0x360, Ui +0x368, Sky +0x370, Item +0x378, Light +0x380.

Every thin clone (size 0x139, port_metrics_60.05.tsv lines 24-64) is ONE template:
  prologue; mov rdi,rdx (desc); mov rsi,rcx (builder); ProfileScope(0x39A7D40);
  mov [rbp+0x10],rdi          (variant.mDescription = desc, at variant+0)
  mov byte ptr [rbp+0x18],<TAG>   (variant.mTag = tag, at variant+8)  <-- differs per clone
  mov rax,[rsi]; mov rax,[rax+0x<SLOT>]   (builder->vtable[groupSlot])  <-- differs per group
  lea rdx,[rbp+0x10] (&variant); mov rcx,rsi; call qword ptr [0xF99FFA0] (CFG thunk)

The only observable pre-call output of a clone is the InsertVariant {desc, tag} plus the group-slot target. A table-driven inserter parameterized by (groupSlot, tag) that builds InsertVariant {desc=rdx, tag} and calls builder->vtable[groupSlot](builder, &variant) therefore reproduces an IDENTICAL InsertVariant stream at all 21 sites (same desc pointer, same tag, same group slot).

## Proof rows — 21 thin clones (all [V]: verbatim from rdis disassembly of Minecraft.Windows.exe 1.26.62.01)

Format: clone RVA | size | tagInstr (verbatim) | slotInstr (verbatim) | group | tag | description

| clone RVA | size | tagInstr | slotInstr | group | tag | description |
|---|---|---|---|---|---|---|
| 0x5369920 | 0x139 | `0x5369994  mov byte ptr [rbp+0x18],4` | `0x536999b  mov rax,[rax+0x378]` | Item | 4 | ChunkOccluders |
| 0x531b180 | 0x139 | `0x531b1f4  mov byte ptr [rbp+0x18],6` | `0x531b1fb  mov rax,[rax+0x378]` | Item | 6 | ItemInHand |
| 0x15a6880 | 0x139 | `0x15a68f4  mov byte ptr [rbp+0x18],3` | `0x15a68fb  mov rax,[rax+0x378]` | Item | 3 | ChunkGeometry |
| 0x4e39cb0 | 0x139 | `0x4e39d24  mov byte ptr [rbp+0x18],0xA` | `0x4e39d2b  mov rax,[rax+0x378]` | Item | 10 | BatchActor |
| 0x6c956b0 | 0x139 | `0x6c95724  mov byte ptr [rbp+0x18],0` | `0x6c9572b  mov rax,[rax+0x358]` | Editor | 0 | BlockVolumeBoundingBox |
| 0x4c85d70 | 0x139 | `0x4c85de4  mov byte ptr [rbp+0x18],1` | `0x4c85deb  mov rax,[rax+0x358]` | Editor | 1 | GizmoHandleArrow |
| 0x4c85f30 | 0x139 | `0x4c85fa4  mov byte ptr [rbp+0x18],2` | `0x4c85fab  mov rax,[rax+0x358]` | Editor | 2 | GizmoHandleCube |
| 0x4c860f0 | 0x139 | `0x4c86164  mov byte ptr [rbp+0x18],3` | `0x4c8616b  mov rax,[rax+0x358]` | Editor | 3 | GizmoHandlePane |
| 0x4c862b0 | 0x139 | `0x4c86324  mov byte ptr [rbp+0x18],4` | `0x4c8632b  mov rax,[rax+0x358]` | Editor | 4 | GizmoHandleRing |
| 0x5371160 | 0x139 | `0x53711d4  mov byte ptr [rbp+0x18],5` | `0x53711db  mov rax,[rax+0x358]` | Editor | 5 | SelectionCursor |
| 0x6c961e0 | 0x139 | `0x6c96254  mov byte ptr [rbp+0x18],6` | `0x6c9625b  mov rax,[rax+0x358]` | Editor | 6 | BlockVolumeOutline |
| 0x5acbe20 | 0x139 | `0x5acbe94  mov byte ptr [rbp+0x18],1` | `0x5acbe9b  mov rax,[rax+0x360]` | Effect | 1 | BlitFlipbookTexture |
| 0x5b8d520 | 0x139 | `0x5b8d594  mov byte ptr [rbp+0x18],2` | `0x5b8d59b  mov rax,[rax+0x360]` | Effect | 2 | Particle |
| 0x5370e80 | 0x139 | `0x5370ef4  mov byte ptr [rbp+0x18],6` | `0x5370efb  mov rax,[rax+0x360]` | Effect | 6 | CameraAimAssistHighlight |
| 0x4c8a5b0 | 0x139 | `0x4c8a624  mov byte ptr [rbp+0x18],8` | `0x4c8a62b  mov rax,[rax+0x360]` | Effect | 8 | EditorHighlightConfiguration |
| 0x4c96140 | 0x139 | `0x4c961b4  mov byte ptr [rbp+0x18],2` | `0x4c961bb  mov rax,[rax+0x368]` | Ui | 2 | UIMesh |
| 0x660b720 | 0x139 | `0x660b794  mov byte ptr [rbp+0x18],2` | `0x660b79b  mov rax,[rax+0x370]` | Sky | 2 | Cubemap |
| 0x53707a0 | 0x139 | `0x5370814  mov byte ptr [rbp+0x18],3` | `0x537081b  mov rax,[rax+0x370]` | Sky | 3 | EndSky |
| 0x5370b20 | 0x139 | `0x5370b94  mov byte ptr [rbp+0x18],7` | `0x5370b9b  mov rax,[rax+0x370]` | Sky | 7 | CelestialBody |
| 0x5ad5800 | 0x139 | `0x5ad5874  mov byte ptr [rbp+0x18],9` | `0x5ad587b  mov rax,[rax+0x370]` | Sky | 9 | Weather |
| 0x5370960 | 0x139 | `0x53709d4  mov byte ptr [rbp+0x18],1` | `0x53709db  mov rax,[rax+0x380]` | Light | 1 | LightDirectional |

Count check: Item 4 + Editor 7 + Effect 4 + Ui 1 + Sky 4 + Light 1 = 21 [V]. Every tag store and every slot load above was read verbatim from rdis; all 21 clones share the identical prologue, desc store, &variant, rcx=builder, and CFG thunk call [V].

## The table-driven inserter (new code)
RewriteInsertTable.h defines kEntries[21] (clone RVA -> {group, tag, groupSlot, name}) and one inserter:
  uint64_t insert(void* builder, void* desc, const RwInsertEntry& e)
which builds InsertVariant mDescription=desc, mTag=e.tag on the stack and calls builder->vtable[e.groupSlot](builder, &variant).
RewriteInsertTable.cpp defines one detour thunk per clone (hk_<Name>(builder, desc) -> insert(builder, desc, entry)) installed late via HookTable::add (does not touch HookManager.cpp or existing registrations), plus a pure self-test that, given a fake builder with a controllable vtable and a fake desc, verifies per clone that the forwarded InsertVariant has mDescription==desc and mTag==tag and the target slot is builder->vtable[groupSlot].

## CLOSES?
NO — the table-driven inserter exists on disk and every clone's tag/groupSlot is proven [V], so the inserter provably reproduces an identical InsertVariant stream by construction (same desc pointer, same tag, same group-slot target at all 21 sites). The item's own wording requires the stream to be "verified" dynamically: capture InsertVariant with the original clones, then with the table-driven inserter, compare. That needs a build and an in-game run, which the hard rules forbid (no builds, no launching/attaching to the game). Single blocking fact: dynamic identical-stream capture/compare cannot be performed on disk; remaining step is `build + run game + capture stream before/after + compare`.

## NEXT
DONE once the dynamic stream comparison is performed off-repo and this file's CLOSES? is flipped to YES with the capture commands/results cited.
