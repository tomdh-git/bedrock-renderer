#pragma once
// The frame-graph task list of 1.26.62.01 (docs/BGFX_MAP.md 6cx, 6da-6dc, 6dg, 6dy). The list is the argument of the task dispatch (rva 0xE9002E0): a vector of 0x80-byte entries, each pointing
// at a task object whose pass body is a type-erased functor. Walk it from a hook on the dispatch to see, rename, skip or reorder passes. Offsets are for the game thread's view; nothing here
// is compiled against the game. [V] live-verified, [I] inferred.

namespace dragon {

struct TaskRvas {
    static constexpr uintptr_t kDispatch = 0xE9002E0;      // [V] task list in rcx
    static constexpr uintptr_t kFrameGraphGenerate = 0xC273420; // [V]
    static constexpr uintptr_t kBgfxContextEndFrame = 0xC270460; // [V]
    static constexpr uintptr_t kFrameRenderer = 0x67C9C20;       // [V] "Frame renderer - Frame"
    static constexpr uintptr_t kSceneHudViewSetup = 0x568CD90;   // [V] per-view rect/matrices (bgfx/View.h)
    // Task class vtables and where each keeps its std::string name.
    static constexpr uintptr_t kVtCommonPass = 0xF25C7B0;   // "Scene" / "HUD"; object size 0x2E0, name at +0x2C0
    static constexpr uintptr_t kVtClearWrapper = 0xF25C850; // "[ClearColorDepth][Scene]" / "[ClearDepth][HUD]"; name at +0x88
    static constexpr uintptr_t kVtGenericPass = 0xF440770;  // "Pass"; name at +0x290
    static constexpr uintptr_t kVtTerrainAtlasBlit = 0xF43E9C0; // "TerrainAtlasBlit"; name at +0x130
    static constexpr uintptr_t kVtWaitOnChunk = 0xF25C080;  // "SceneWaitOnChunk"; name at +0x80
};

// One entry of the task list (stride 0x80). [V live]
struct TaskListEntry {
    void* task;          // +0x00 task object (its first qword is the vtable)
    void* controlBlock;  // +0x08 shared_ptr control block (refcounted: never free a task through the list)
    void* state;         // +0x10 heap pointer, per-task state
    uint64_t kind;       // +0x18 task param/kind index (5 for most scene tasks)
    uint64_t frameId;    // +0x20 value identical in every entry of a frame
    uint32_t live;       // +0x28 1 while live
    uint32_t debugColor; // +0x2C
    uint8_t rest[0x50];  // +0x30..+0x7F not decoded
};
static_assert(sizeof(TaskListEntry) == 0x80);

struct TaskList {
    TaskListEntry* begin; // +0x00
    TaskListEntry* end;   // +0x08
    void* cap;            // +0x10
    uint64_t extra;       // +0x18 (0 in the sampled frame)
    size_t size() const { return static_cast<size_t>(end - begin); }
};

struct TaskOffsets {
    static constexpr size_t kFunctor = 0x70; // std::function impl pointer (MSVC _Func_impl: slot 2 = _Do_call); replace it with a no-op impl to disable the pass
    static constexpr size_t kFunctorArgs = 0x78; // arguments block handed to the functor
    static constexpr size_t kObjNameHash = 0x08;    // [I static 6eo] task object: name HashedString hash (the generator matches it against endFrame's names vector)
    static constexpr size_t kObjNameString = 0x10;  // [I static 6eo] task object: name std::string
    static constexpr size_t kObjMatchedName = 0x30; // [I static 6eo] task object: pointer to the matched names-vector entry
    static constexpr size_t kRecordOrderKey = 0x78; // [I static 6eo] generator pass record (not the final TaskListEntry): index in the names vector, stable-sort key
    static constexpr size_t kCommonPassName = 0x2C0;
    static constexpr size_t kClearWrapperName = 0x88;
    static constexpr size_t kGenericPassName = 0x290;
    static constexpr size_t kTerrainAtlasBlitName = 0x130;
    static constexpr size_t kWaitOnChunkName = 0x80;
    // Common pass class (vtable kVtCommonPass), from the fully reversed render-thread body 0x568bcd0 (docs/functions/568bcd0.md). [V static]
    static constexpr size_t kCommonPassArg0 = 0x2E0;        // first field of the 0x18-byte argument block handed to the body
    static constexpr size_t kCommonPassViewRef = 0x2E8;     // ViewRef* (shared_ptr element), see ViewRefOffsets
    static constexpr size_t kCommonPassViewRefCtrl = 0x2F0; // its control block
};

// The view reference a pass task holds. The task's encode step queues `encoder->submitCustom(viewId, renderThreadBody, task)`; the D3D12
// executor later calls the body on the render thread and publishes its context (command list) at kExecCtx for the duration.
struct ViewRefOffsets {
    static constexpr size_t kViewId = 0x08;  // u16 bgfx view id
    static constexpr size_t kEncoder = 0x10; // bgfx::EncoderImpl*
    static constexpr size_t kExecCtx = 0x18; // {tag, job field, command list}*, null outside a render-thread body
};

// Every pass-task class ends with { std::string name (0x20); void* arg0; ViewRef* view; control block* } after its own payload, so
// arg0 = name + 0x20, view = name + 0x28, control = name + 0x30. Checked against the four render-thread bodies (identical code, only
// these displacements differ): docs/functions/568bcd0.md.
struct TaskTail {
    static constexpr size_t kArg0FromName = 0x20;
    static constexpr size_t kViewRefFromName = 0x28;
    static constexpr size_t kViewRefCtrlFromName = 0x30;
};
static_assert(TaskOffsets::kCommonPassName + TaskTail::kArg0FromName == TaskOffsets::kCommonPassArg0);
static_assert(TaskOffsets::kCommonPassName + TaskTail::kViewRefFromName == TaskOffsets::kCommonPassViewRef);
static_assert(TaskOffsets::kCommonPassName + TaskTail::kViewRefCtrlFromName == TaskOffsets::kCommonPassViewRefCtrl);

struct TaskBodyRvas { // 1.26.62.01; no unique signatures exist for these, re-find through Encoder::submitCustom's tail jumps
    static constexpr uintptr_t kCommonPassEncode = 0x568B9E0;
    static constexpr uintptr_t kCommonPassRenderBody = 0x568BCD0;
};

// The name of a task through its class: reads the embedded MSVC std::string (SSO when capacity < 16). `imageBase` is the exe base.
inline std::string_view taskName(const void* task, uintptr_t imageBase) {
    const uintptr_t vt = *static_cast<const uintptr_t*>(task) - imageBase;
    size_t at = 0;
    switch (vt) {
    case TaskRvas::kVtCommonPass: at = TaskOffsets::kCommonPassName; break;
    case TaskRvas::kVtClearWrapper: at = TaskOffsets::kClearWrapperName; break;
    case TaskRvas::kVtGenericPass: at = TaskOffsets::kGenericPassName; break;
    case TaskRvas::kVtTerrainAtlasBlit: at = TaskOffsets::kTerrainAtlasBlitName; break;
    case TaskRvas::kVtWaitOnChunk: at = TaskOffsets::kWaitOnChunkName; break;
    default: return {}; // an unknown class: its name offset is not known (RTX/VV frames use more classes)
    }
    const auto* str = static_cast<const uint8_t*>(task) + at; // std::string: {union{char buf[16]; char* ptr;}, size_t size, size_t cap}
    const size_t size = *reinterpret_cast<const size_t*>(str + 0x10);
    const size_t cap = *reinterpret_cast<const size_t*>(str + 0x18);
    const char* data = cap < 16 ? reinterpret_cast<const char*>(str) : *reinterpret_cast<const char* const*>(str);
    return {data, size};
}

} // namespace dragon
