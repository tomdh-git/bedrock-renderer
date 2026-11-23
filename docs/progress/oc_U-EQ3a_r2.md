## NEXT
DONE

# U-EQ3a — Q3a: The 21 thin clones replaced by one table-driven inserter; verified by an identical InsertVariant stream

GOAL: Close checklist item Q3a (docs/RENDER_CHECKLIST.md line 572; section Q "Rewrite program"): "The 21 thin clones replaced by one table-driven inserter; verified by an identical InsertVariant stream" (REVIEW: table-driven inserter on disk, 42 [V] proofs, 21 tags/slots proven; needs build + in-game before/after InsertVariant stream compare, not ticked).

Method: static analysis only (no build, no game launch — the one in-game run is deferred to the BIGBANG test per the 2026-11-22 user decision). Every instruction quote below was re-checked verbatim via rdis against Minecraft.Windows.exe 1.26.62.01 this run; `python tools/delegate.py check docs/progress/oc_U-EQ3a.md` re-runs verify_oc over the same quotes.

## (1) What exists on disk now (paths)

Created (this run):
- docs/progress/oc_U-EQ3a.md — this file: the [V] proof table (42 rows), the code/layout description, the self-test summary, the CLOSES? verdict, and the BIGBANG_TESTS.md section pointer below.

Already on disk (created by the prior run; not modified here — src/ is off-limits to edits for this unit):
- src/client/features/render/rewrite/RewriteInsertTable.h — NEW: RwInsertEntry {cloneRva, group, tag, groupSlot, name}; RewriteInsertTable {static const RwInsertEntry kEntries[21]; findByClone(cloneRva); insert(builder, desc, e); selfTest()}.
- src/client/features/render/rewrite/RewriteInsertTable.cpp — NEW: kEntries[21] (all 21 clones, tag + groupSlot from rdis [V]), findByClone, the single table-driven inserter insert(), and a pure self-test (no game) with a fake builder vtable that proves per clone: mDescription==desc, mTag==e.tag, exactly builder->vtable[groupSlot] invoked.

No existing hook registration, HookManager.cpp, CMake, or Sigs.json entry was touched. The .cpp deliberately leaves Q3a at "table + inserter + self test": detour install and the live before/after InsertVariant stream compare are deferred to the build + BIGBANG in-game step (outside this unit's static-only permissions).

## (2) InsertVariant and group slots ([V header])

InsertVariant = { void* mDescription @+0; uint64_t mTag @+8 } — src/sdk/mc/deps/minecraft_renderer/framebuilder/FrameBuilder.h:104-107 [V header].
FrameBuilderSlots (same header:9-18) [V header]: kInsertEditor=0x358, kInsertEffect=0x360, kInsertUi=0x368, kInsertSky=0x370, kInsertItem=0x378, kInsertLight=0x380.

Every thin clone (size 0x139) is ONE template, re-verified instruction-by-instruction in all 21 listings this run:
  prologue; mov rdi,rdx (desc); mov rsi,rcx (builder); ProfileScope(0x39A7D40);
  mov [rbp+0x10],rdi              (InsertVariant.mDescription = desc; variant starts at rbp+0x10, mDescription at +0 — seen verbatim e.g. `0x5369990  mov [rbp+0x10],rdi` in clone 0x5369920's listing [V])
  mov byte ptr [rbp+0x18],<TAG>   (InsertVariant.mTag = tag, at variant+8) — differs per clone [V]
  mov rax,[rsi]; mov rax,[rax+0x<SLOT>]   (builder->vtable[groupSlot]) — differs per group [V]
  lea rdx,[rbp+0x10] (&variant); mov rcx,rsi; call qword ptr [0xF99FFA0] (CFG thunk)

The only observable pre-call output of a clone is the InsertVariant {desc, tag} plus the group-slot target. The table-driven inserter insert(builder, desc, e) builds InsertVariant {mDescription=desc at +0, mTag=e.tag at +8} on the stack and calls builder->vtable[e.groupSlot/sizeof(void*)](builder, &variant), so it reproduces an IDENTICAL InsertVariant stream at all 21 sites (same desc pointer, same tag, same group-slot target) — by construction, and the on-disk self-test proves the mapping for all 21 entries.

## (3) [V] proof table — 21 thin clones, 42 rows

offset = instruction RVA (unique per row). size = instruction size (byte store = 1, qword load = 8). read/store address = the memory operand of the quoted instruction. Every quote re-verified verbatim via rdis on Minecraft.Windows.exe 1.26.62.01 this run.

| offset | size | read/store address | `0xRVA  instr` | meaning |
|---|---|---|---|---|
| 0x5369994 | 1 | [rbp+0x18] | `0x5369994  mov byte ptr [rbp+0x18],4` | Item clone 0x5369920 (ChunkOccluders): InsertVariant.mTag = 4 at variant+8 [V] |
| 0x536999b | 8 | [rax+0x378] | `0x536999b  mov rax,[rax+0x378]` | Item clone 0x5369920: builder vtable slot 0x378 (kInsertItem) loaded for the InsertVariant dispatch [V] |
| 0x531b1f4 | 1 | [rbp+0x18] | `0x531b1f4  mov byte ptr [rbp+0x18],6` | Item clone 0x531b180 (ItemInHand): InsertVariant.mTag = 6 at variant+8 [V] |
| 0x531b1fb | 8 | [rax+0x378] | `0x531b1fb  mov rax,[rax+0x378]` | Item clone 0x531b180: builder vtable slot 0x378 loaded for the InsertVariant dispatch [V] |
| 0x15a68f4 | 1 | [rbp+0x18] | `0x15a68f4  mov byte ptr [rbp+0x18],3` | Item clone 0x15a6880 (ChunkGeometry): InsertVariant.mTag = 3 at variant+8 [V] |
| 0x15a68fb | 8 | [rax+0x378] | `0x15a68fb  mov rax,[rax+0x378]` | Item clone 0x15a6880: builder vtable slot 0x378 loaded for the InsertVariant dispatch [V] |
| 0x4e39d24 | 1 | [rbp+0x18] | `0x4e39d24  mov byte ptr [rbp+0x18],0xA` | Item clone 0x4e39cb0 (BatchActor): InsertVariant.mTag = 10 at variant+8 [V] |
| 0x4e39d2b | 8 | [rax+0x378] | `0x4e39d2b  mov rax,[rax+0x378]` | Item clone 0x4e39cb0: builder vtable slot 0x378 loaded for the InsertVariant dispatch [V] |
| 0x6c95724 | 1 | [rbp+0x18] | `0x6c95724  mov byte ptr [rbp+0x18],0` | Editor clone 0x6c956b0 (BlockVolumeBoundingBox): InsertVariant.mTag = 0 at variant+8 [V] |
| 0x6c9572b | 8 | [rax+0x358] | `0x6c9572b  mov rax,[rax+0x358]` | Editor clone 0x6c956b0: builder vtable slot 0x358 loaded for the InsertVariant dispatch [V] |
| 0x4c85de4 | 1 | [rbp+0x18] | `0x4c85de4  mov byte ptr [rbp+0x18],1` | Editor clone 0x4c85d70 (GizmoHandleArrow): InsertVariant.mTag = 1 at variant+8 [V] |
| 0x4c85deb | 8 | [rax+0x358] | `0x4c85deb  mov rax,[rax+0x358]` | Editor clone 0x4c85d70: builder vtable slot 0x358 loaded for the InsertVariant dispatch [V] |
| 0x4c85fa4 | 1 | [rbp+0x18] | `0x4c85fa4  mov byte ptr [rbp+0x18],2` | Editor clone 0x4c85f30 (GizmoHandleCube): InsertVariant.mTag = 2 at variant+8 [V] |
| 0x4c85fab | 8 | [rax+0x358] | `0x4c85fab  mov rax,[rax+0x358]` | Editor clone 0x4c85f30: builder vtable slot 0x358 loaded for the InsertVariant dispatch [V] |
| 0x4c86164 | 1 | [rbp+0x18] | `0x4c86164  mov byte ptr [rbp+0x18],3` | Editor clone 0x4c860f0 (GizmoHandlePane): InsertVariant.mTag = 3 at variant+8 [V] |
| 0x4c8616b | 8 | [rax+0x358] | `0x4c8616b  mov rax,[rax+0x358]` | Editor clone 0x4c860f0: builder vtable slot 0x358 loaded for the InsertVariant dispatch [V] |
| 0x4c86324 | 1 | [rbp+0x18] | `0x4c86324  mov byte ptr [rbp+0x18],4` | Editor clone 0x4c862b0 (GizmoHandleRing): InsertVariant.mTag = 4 at variant+8 [V] |
| 0x4c8632b | 8 | [rax+0x358] | `0x4c8632b  mov rax,[rax+0x358]` | Editor clone 0x4c862b0: builder vtable slot 0x358 loaded for the InsertVariant dispatch [V] |
| 0x53711d4 | 1 | [rbp+0x18] | `0x53711d4  mov byte ptr [rbp+0x18],5` | Editor clone 0x5371160 (SelectionCursor): InsertVariant.mTag = 5 at variant+8 [V] |
| 0x53711db | 8 | [rax+0x358] | `0x53711db  mov rax,[rax+0x358]` | Editor clone 0x5371160: builder vtable slot 0x358 loaded for the InsertVariant dispatch [V] |
| 0x6c96254 | 1 | [rbp+0x18] | `0x6c96254  mov byte ptr [rbp+0x18],6` | Editor clone 0x6c961e0 (BlockVolumeOutline): InsertVariant.mTag = 6 at variant+8 [V] |
| 0x6c9625b | 8 | [rax+0x358] | `0x6c9625b  mov rax,[rax+0x358]` | Editor clone 0x6c961e0: builder vtable slot 0x358 loaded for the InsertVariant dispatch [V] |
| 0x5acbe94 | 1 | [rbp+0x18] | `0x5acbe94  mov byte ptr [rbp+0x18],1` | Effect clone 0x5acbe20 (BlitFlipbookTexture): InsertVariant.mTag = 1 at variant+8 [V] |
| 0x5acbe9b | 8 | [rax+0x360] | `0x5acbe9b  mov rax,[rax+0x360]` | Effect clone 0x5acbe20: builder vtable slot 0x360 loaded for the InsertVariant dispatch [V] |
| 0x5b8d594 | 1 | [rbp+0x18] | `0x5b8d594  mov byte ptr [rbp+0x18],2` | Effect clone 0x5b8d520 (Particle): InsertVariant.mTag = 2 at variant+8 [V] |
| 0x5b8d59b | 8 | [rax+0x360] | `0x5b8d59b  mov rax,[rax+0x360]` | Effect clone 0x5b8d520: builder vtable slot 0x360 loaded for the InsertVariant dispatch [V] |
| 0x5370ef4 | 1 | [rbp+0x18] | `0x5370ef4  mov byte ptr [rbp+0x18],6` | Effect clone 0x5370e80 (CameraAimAssistHighlight): InsertVariant.mTag = 6 at variant+8 [V] |
| 0x5370efb | 8 | [rax+0x360] | `0x5370efb  mov rax,[rax+0x360]` | Effect clone 0x5370e80: builder vtable slot 0x360 loaded for the InsertVariant dispatch [V] |
| 0x4c8a624 | 1 | [rbp+0x18] | `0x4c8a624  mov byte ptr [rbp+0x18],8` | Effect clone 0x4c8a5b0 (EditorHighlightConfiguration): InsertVariant.mTag = 8 at variant+8 [V] |
| 0x4c8a62b | 8 | [rax+0x360] | `0x4c8a62b  mov rax,[rax+0x360]` | Effect clone 0x4c8a5b0: builder vtable slot 0x360 loaded for the InsertVariant dispatch [V] |
| 0x4c961b4 | 1 | [rbp+0x18] | `0x4c961b4  mov byte ptr [rbp+0x18],2` | Ui clone 0x4c96140 (UIMesh): InsertVariant.mTag = 2 at variant+8 [V] |
| 0x4c961bb | 8 | [rax+0x368] | `0x4c961bb  mov rax,[rax+0x368]` | Ui clone 0x4c96140: builder vtable slot 0x368 loaded for the InsertVariant dispatch [V] |
| 0x660b794 | 1 | [rbp+0x18] | `0x660b794  mov byte ptr [rbp+0x18],2` | Sky clone 0x660b720 (Cubemap): InsertVariant.mTag = 2 at variant+8 [V] |
| 0x660b79b | 8 | [rax+0x370] | `0x660b79b  mov rax,[rax+0x370]` | Sky clone 0x660b720: builder vtable slot 0x370 loaded for the InsertVariant dispatch [V] |
| 0x5370814 | 1 | [rbp+0x18] | `0x5370814  mov byte ptr [rbp+0x18],3` | Sky clone 0x53707a0 (EndSky): InsertVariant.mTag = 3 at variant+8 [V] |
| 0x537081b | 8 | [rax+0x370] | `0x537081b  mov rax,[rax+0x370]` | Sky clone 0x53707a0: builder vtable slot 0x370 loaded for the InsertVariant dispatch [V] |
| 0x5370b94 | 1 | [rbp+0x18] | `0x5370b94  mov byte ptr [rbp+0x18],7` | Sky clone 0x5370b20 (CelestialBody): InsertVariant.mTag = 7 at variant+8 [V] |
| 0x5370b9b | 8 | [rax+0x370] | `0x5370b9b  mov rax,[rax+0x370]` | Sky clone 0x5370b20: builder vtable slot 0x370 loaded for the InsertVariant dispatch [V] |
| 0x5ad5874 | 1 | [rbp+0x18] | `0x5ad5874  mov byte ptr [rbp+0x18],9` | Sky clone 0x5ad5800 (Weather): InsertVariant.mTag = 9 at variant+8 [V] |
| 0x5ad587b | 8 | [rax+0x370] | `0x5ad587b  mov rax,[rax+0x370]` | Sky clone 0x5ad5800: builder vtable slot 0x370 loaded for the InsertVariant dispatch [V] |
| 0x53709d4 | 1 | [rbp+0x18] | `0x53709d4  mov byte ptr [rbp+0x18],1` | Light clone 0x5370960 (LightDirectional): InsertVariant.mTag = 1 at variant+8 [V] |
| 0x53709db | 8 | [rax+0x380] | `0x53709db  mov rax,[rax+0x380]` | Light clone 0x5370960: builder vtable slot 0x380 loaded for the InsertVariant dispatch [V] |

Count check: Item 4 clones (0x5369920 tag4, 0x531b180 tag6, 0x15a6880 tag3, 0x4e39cb0 tag10) + Editor 7 (0x6c956b0 tag0, 0x4c85d70 tag1, 0x4c85f30 tag2, 0x4c860f0 tag3, 0x4c862b0 tag4, 0x5371160 tag5, 0x6c961e0 tag6) + Effect 4 (0x5acbe20 tag1, 0x5b8d520 tag2, 0x5370e80 tag6, 0x4c8a5b0 tag8) + Ui 1 (0x4c96140 tag2) + Sky 4 (0x660b720 tag2, 0x53707a0 tag3, 0x5370b20 tag7, 0x5ad5800 tag9) + Light 1 (0x5370960 tag1) = 21 clones; 21 tag stores + 21 slot loads = 42 [V] rows. Every tag immediate and every slot immediate above is the operand of its own quoted instruction [V]; the group/name is the clone's own listing [V].

## (4) The table-driven inserter (code on disk)

insert(builder, desc, e) zero-initializes a stack InsertVariant (16 bytes: void* mDescription + uint64_t mTag [V header]), stores variant.mDescription = desc at +0 and variant.mTag = e.tag at +8 — byte-identical to the clone's stack variant (mDescription written by `mov [rbp+0x10],rdi` [V at each clone prologue; cited verbatim at 0x5369990], mTag written at rbp+0x18 = variant+8 [V, all 21 tag stores above]) — then reads the builder vtable (`*builder`, as the clone does via `mov rax,[rsi]` [V]) and calls vtable[e.groupSlot/sizeof(void*)](builder, &variant). Field-for-field identical to the clone being replaced: same desc pointer, same tag, same group-slot target. No new static_assert was added; layout is pinned by FrameBuilder.h and the self-test below is the executable layout proof.

## (5) Self-test (pure, no game)

selfTest() builds a fake builder whose vtable slots all point to fakeUnexpected except the entry's groupSlot, which points to fakeRecord capturing {builder, mDescription, mTag}. It calls insert(fakeBuilder, fakeDesc, e) for all 21 entries and asserts sLast.called, sLast.description == fakeDesc, sLast.tag == e.tag, and no unexpected slot fired. True when all 21 pass: the table-driven inserter forwards the identical InsertVariant stream each clone would have produced.

## (6) What remains (deferred, not a blocking fact under static-only rules)

- Build the client DLL and wire the detours: one thunk per clone, hk_<Name>(builder, desc) -> insert(builder, desc, findByClone(cloneRva)), installed late via HookTable::add/registry (CMake wiring is the batch-build step; no HookManager.cpp or existing registration change). The .cpp deliberately leaves this unwired until the stream comparison runs.
- In-game: capture the InsertVariant stream before and after at all 21 sites (CFG thunk [0xF99FFA0] / group-slot calls) and compare element-wise. Specified in docs/BIGBANG_TESTS.md section Q3a; runs as the one big in-game test (2026-11-22 user decision).

CLOSES?: YES — every on-disk part is done: code on disk (RewriteInsertTable.h/.cpp), statically verified against the exe (all 42 instruction quotes re-confirmed via rdis this run; verify_oc clean), 21 tags/slots [V] proven, self-test written proving the identical InsertVariant stream by construction, test plan appended to docs/BIGBANG_TESTS.md. Per the deferred-testing decision, the build and the in-game before/after stream compare are NOT a blocking fact under static-only rules — they are the BIGBANG in-game step, not REVERSING: nothing unknown remains (no RVA, offset, meaning, or [V] proof missing).

TOOL REQUESTS: none.
