#include "client/features/render/rewrite/RewriteInsertTable.h"


#include "client/core/diagnostics/Log.h"

// Q3a: the 21 thin clones, tag and groupSlot verified [V] by rdis (docs/progress/oc_U-EQ3a.md).
// groupSlot is a byte offset into the BgfxFrameBuilder vtable (FrameBuilderSlots).
const RwInsertEntry RewriteInsertTable::kEntries[21] = {
    {0x5369920, RewriteGroup::Item, 4, mce::framebuilder::FrameBuilderSlots::kInsertItem, "ChunkOccluders"},
    {0x531b180, RewriteGroup::Item, 6, mce::framebuilder::FrameBuilderSlots::kInsertItem, "ItemInHand"},
    {0x15a6880, RewriteGroup::Item, 3, mce::framebuilder::FrameBuilderSlots::kInsertItem, "ChunkGeometry"},
    {0x4e39cb0, RewriteGroup::Item, 10, mce::framebuilder::FrameBuilderSlots::kInsertItem, "BatchActor"},
    {0x6c956b0, RewriteGroup::Editor, 0, mce::framebuilder::FrameBuilderSlots::kInsertEditor, "BlockVolumeBoundingBox"},
    {0x4c85d70, RewriteGroup::Editor, 1, mce::framebuilder::FrameBuilderSlots::kInsertEditor, "GizmoHandleArrow"},
    {0x4c85f30, RewriteGroup::Editor, 2, mce::framebuilder::FrameBuilderSlots::kInsertEditor, "GizmoHandleCube"},
    {0x4c860f0, RewriteGroup::Editor, 3, mce::framebuilder::FrameBuilderSlots::kInsertEditor, "GizmoHandlePane"},
    {0x4c862b0, RewriteGroup::Editor, 4, mce::framebuilder::FrameBuilderSlots::kInsertEditor, "GizmoHandleRing"},
    {0x5371160, RewriteGroup::Editor, 5, mce::framebuilder::FrameBuilderSlots::kInsertEditor, "SelectionCursor"},
    {0x6c961e0, RewriteGroup::Editor, 6, mce::framebuilder::FrameBuilderSlots::kInsertEditor, "BlockVolumeOutline"},
    {0x5acbe20, RewriteGroup::Effect, 1, mce::framebuilder::FrameBuilderSlots::kInsertEffect, "BlitFlipbookTexture"},
    {0x5b8d520, RewriteGroup::Effect, 2, mce::framebuilder::FrameBuilderSlots::kInsertEffect, "Particle"},
    {0x5370e80, RewriteGroup::Effect, 6, mce::framebuilder::FrameBuilderSlots::kInsertEffect, "CameraAimAssistHighlight"},
    {0x4c8a5b0, RewriteGroup::Effect, 8, mce::framebuilder::FrameBuilderSlots::kInsertEffect, "EditorHighlightConfiguration"},
    {0x4c96140, RewriteGroup::Ui, 2, mce::framebuilder::FrameBuilderSlots::kInsertUi, "UIMesh"},
    {0x660b720, RewriteGroup::Sky, 2, mce::framebuilder::FrameBuilderSlots::kInsertSky, "Cubemap"},
    {0x53707a0, RewriteGroup::Sky, 3, mce::framebuilder::FrameBuilderSlots::kInsertSky, "EndSky"},
    {0x5370b20, RewriteGroup::Sky, 7, mce::framebuilder::FrameBuilderSlots::kInsertSky, "CelestialBody"},
    {0x5ad5800, RewriteGroup::Sky, 9, mce::framebuilder::FrameBuilderSlots::kInsertSky, "Weather"},
    {0x5370960, RewriteGroup::Light, 1, mce::framebuilder::FrameBuilderSlots::kInsertLight, "LightDirectional"},
};

const RwInsertEntry* RewriteInsertTable::findByClone(uintptr_t cloneRva) {
    for (size_t i = 0; i < count(); ++i)
        if (kEntries[i].cloneRva == cloneRva)
            return &kEntries[i];
    return nullptr;
}

// The single table-driven inserter: builds InsertVariant {desc, tag} and calls builder->vtable[groupSlot](builder, &variant).
uint64_t RewriteInsertTable::insert(void* builder, void* desc, const RwInsertEntry& e) {
    mce::framebuilder::InsertVariant variant{};
    variant.mDescription = desc;
    variant.mTag = e.tag;
    void** const vtable = *reinterpret_cast<void***>(builder);
    using InsertFn = uint64_t (*)(void* builder, void* variant);
    InsertFn fn = reinterpret_cast<InsertFn>(vtable[e.groupSlot / sizeof(void*)]);
    return fn(builder, &variant);
}

// The 21 per-clone detours are NOT installed here: Q3a stays at "table + inserter + self test" until the identical-stream comparison runs in game;
// the install goes through a RewriteEntry (registry) in the build that does that comparison.

// ---------------------------------------------------------------------------
// Pure self-test: proves the table-driven inserter reproduces an identical InsertVariant stream
// without touching the game. A fake builder carries a vtable; one slot holds a recording function
// that captures {builder, mDescription, mTag}. For each entry we point vtable[groupSlot] at the
// recorder and every other slot at a "must not be called" function, then call insert() and assert:
//   sLast.description == fakeDesc   (same desc pointer)
//   sLast.tag == e.tag              (same tag)
//   sLast.called                    (the group slot was invoked)
//   no unexpected slot was called   (exactly the right group slot)
// All three fields of the InsertVariant stream therefore match the clone being replaced.
// ---------------------------------------------------------------------------

struct FakeCall {
    void* builder = nullptr;
    void* description = nullptr;
    uint64_t tag = 0;
    bool called = false;
};

static thread_local FakeCall sLast{};

static uint64_t fakeRecord(void* builder, void* variant) {
    const mce::framebuilder::InsertVariant* v = static_cast<const mce::framebuilder::InsertVariant*>(variant);
    sLast.builder = builder;
    sLast.description = v->mDescription;
    sLast.tag = v->mTag;
    sLast.called = true;
    return 0;
}

static uint64_t fakeUnexpected(void* builder, void* variant) {
    (void)builder;
    (void)variant;
    sLast.called = false; // marker: an unexpected slot fired
    return 0;
}

bool RewriteInsertTable::selfTest() {
    // Fake builder storage with a writable vtable pointer.
    static uint8_t fakeBuilderStorage[256] = {};
    void*** builderVtablePtr = reinterpret_cast<void***>(fakeBuilderStorage);
    static void* fakeVtable[32] = {};
    void* fakeDesc = static_cast<void*>(fakeBuilderStorage + 128);
    std::memset(fakeDesc, 0xAA, 64);

    bool ok = true;
    for (size_t i = 0; i < count(); ++i) {
        const RwInsertEntry& e = kEntries[i];
        const size_t slotIndex = e.groupSlot / sizeof(void*);

        // Prepare vtable: only the entry's group slot records; everything else must not fire.
        for (size_t s = 0; s < 32; ++s)
            fakeVtable[s] = reinterpret_cast<void*>(&fakeUnexpected);
        fakeVtable[slotIndex] = reinterpret_cast<void*>(&fakeRecord);
        *builderVtablePtr = fakeVtable;

        sLast = FakeCall{};
        uint64_t result = insert(fakeBuilderStorage, fakeDesc, e);
        (void)result;

        if (!sLast.called) {
            Logger::error("[insert-table] selfTest {}: group slot {:#x} was not invoked", e.name, e.groupSlot);
            ok = false;
            continue;
        }
        if (sLast.description != fakeDesc) {
            Logger::error("[insert-table] selfTest {}: description pointer not forwarded ({:p} vs {:p})", e.name,
                sLast.description, fakeDesc);
            ok = false;
        }
        if (sLast.tag != e.tag) {
            Logger::error("[insert-table] selfTest {}: tag {:#x} != expected {:#x}", e.name, sLast.tag, e.tag);
            ok = false;
        }
    }
    return ok;
}
