#include "client/features/render/rewrite/RewriteProbe.h"
#include "client/features/settings/preferences/Preferences.h"
#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteFunctions.h"
#include "client/features/hooks/Hook.h"
#include "client/features/hooks/hooks/render/TaskDispatchHook.h"
#include "sdk/mc/deps/minecraft_renderer/framebuilder/FrameBuilder.h"
#include "sdk/mc/deps/bgfx/Encoder.h"
#include "sdk/mc/deps/bgfx/Frame.h"
#include "sdk/mc/deps/bgfx/d3d12/D3D12Context.h"

static constexpr uint64_t kRwPsoKeyMask = 0x0707007FFFFFF0FFull; // the PSO builder's state mask (BGFX_MAP 6fs, 8a)
static constexpr uintptr_t kRwProgramVariantKey = 0xA8;          // u64 in the program record
static constexpr uint32_t kRwInlinePrograms = 512;               // programs held inline in the table (0x7C000 / 0xF8)
static std::mutex sRwPassMutex;
static std::vector<std::string> sRwPassNames; // the last frame's task list

struct RwDescRecord {
    RewriteGroup group;
    uint64_t tag;
    const char* name;
    size_t size;
    uint64_t hash;
    uint8_t head[0x20];
};
static std::mutex sRwDescMutex;
static std::vector<RwDescRecord> sRwDescCurrent; // inserts since the last endFrame
static std::vector<RwDescRecord> sRwDescLast;    // the previous game frame's, printed with the next captured Frame

uint32_t RewriteProbe::programOfKey(uint64_t key) {
    switch ((key >> 50) & 3) {
    case 0: return static_cast<uint32_t>((key >> 37) & 0x7FF);
    case 1: return static_cast<uint32_t>((key & 0xFFFF) >> 5);
    default: return static_cast<uint32_t>((key >> 17) & 0x7FF);
    }
}

void RewriteProbe::armFrames(uint32_t frames) {
    sArmed.store(frames, std::memory_order_relaxed);
}

void RewriteProbe::initFromEnvironment() {
    const std::string text = Preferences::Store::developer("probe_frames"); // BS_PROBE_FRAMES, or "developer.probe_frames"
    if (text.empty())
        return;
    armFrames(static_cast<uint32_t>(std::strtoul(text.c_str(), nullptr, 10)));
    RewriteEntry* sort = RewriteRegistry::find("Frame::sort"); // the probe reads the frame from inside this detour; mode stays Off, the original runs
    BS_CHECK(sort != nullptr);
    RewriteRegistry::install(*sort);
}

void RewriteProbe::notePassList(dragon::TaskList& list) {
    if (!armed())
        return;
    std::vector<std::string> names;
    for (size_t i = 0; i < list.size(); ++i)
        names.emplace_back(TaskDispatchHook::nameOf(list, i));
    std::lock_guard<std::mutex> lock(sRwPassMutex);
    sRwPassNames = std::move(names);
}

static uint64_t rwProgramVariantKey(uint32_t program) {
    if (program >= kRwInlinePrograms)
        return 0; // beyond the inline table: paged, not followed by the probe
    const uint8_t* const renderer = *reinterpret_cast<const uint8_t* const*>(RewriteRegistry::imageBase() + bgfx::d3d12::D3D12Rvas::kRendererGlobal);
    const uint8_t* const record = renderer + bgfx::d3d12::D3D12Tables::kPrograms + static_cast<size_t>(program) * bgfx::d3d12::D3D12Tables::kProgramsStride;
    return *reinterpret_cast<const uint64_t*>(record + kRwProgramVariantKey);
}

void RewriteProbe::captureFrame(const uint8_t* frame) {
    if (!armed())
        return;
    if (sArmed.fetch_sub(1, std::memory_order_relaxed) == 0) { // another thread took the last one
        sArmed.store(0, std::memory_order_relaxed);
        return;
    }
    const uint32_t counter = *reinterpret_cast<const uint32_t*>(frame + bgfx::FrameOffsets::kFrameCounter);
    const uint32_t items = *reinterpret_cast<const uint32_t*>(frame + bgfx::FrameOffsets::kItemCount);
    const uint32_t blits = *reinterpret_cast<const uint16_t*>(frame + bgfx::FrameOffsets::kBlitCount);
    const uint64_t* const keys = reinterpret_cast<const uint64_t*>(frame + bgfx::FrameOffsets::kSortKeys);
    const uint16_t* const ids = reinterpret_cast<const uint16_t*>(frame + bgfx::FrameOffsets::kSortedItems);
    uint32_t perView[256] = {};
    uint32_t marked = 0;
    for (uint32_t slot = 0; slot < items; ++slot) {
        ++perView[bgfx::SortKey::viewOf(keys[slot]) & 0xFF];
        const uint8_t mark = frame[bgfx::FrameOffsets::kDrawHeaders + (static_cast<size_t>(ids[slot]) << 7) + bgfx::RenderDrawHeader::kMarkByte];
        marked += (mark & 0x80) != 0;
    }
    std::string views;
    for (int v = 0; v < 256; ++v)
        if (perView[v])
            views += fmt::format(" v{}:{}", v, perView[v]);
    Logger::info("[probe] frame {} items {} blits {} actor-marked {} views{}", counter, items, blits, marked, views);
    for (uint32_t slot = 0; slot < items && slot < kMaxDrawLines; ++slot) {
        const bgfx::RenderDraw& d = *reinterpret_cast<const bgfx::RenderDraw*>(frame + bgfx::FrameOffsets::kDrawHeaders + (static_cast<size_t>(ids[slot]) << 7));
        const uint32_t program = programOfKey(keys[slot]);
        Logger::info("[probe]  slot {} id {} view {} key {:#x} program {} variant {:#x} pso {:#x} ib {:#x} vb {:#x} indices {} mark {:#x}", slot, ids[slot], bgfx::SortKey::viewOf(keys[slot]), keys[slot], program,
            rwProgramVariantKey(program), d.stateFlags & kRwPsoKeyMask, d.indexBuffer, d.stream[0].handle, d.numIndices, frame[bgfx::FrameOffsets::kDrawHeaders + (static_cast<size_t>(ids[slot]) << 7) + bgfx::RenderDrawHeader::kMarkByte]);
    }
    {
        std::lock_guard<std::mutex> lock(sRwDescMutex);
        Logger::info("[probe] frame {} descriptions of the previous game frame: {}", counter, sRwDescLast.size());
        for (const RwDescRecord& r : sRwDescLast) {
            std::string head;
            for (uint8_t b : r.head)
                head += fmt::format("{:02x}", b);
            Logger::info("[probe]  {}/{} tag {} size {:#x} fnv {:#x} head {}", RewriteDescriptions::groupName(r.group), r.name, r.tag, r.size, r.hash, head);
        }
    }
    std::lock_guard<std::mutex> lock(sRwPassMutex);
    std::string passes;
    for (const std::string& n : sRwPassNames)
        passes += n + ",";
    Logger::info("[probe] frame {} passes ({}): {}", counter, sRwPassNames.size(), passes);
}

void RewriteProbe::noteInsert(RewriteGroup group, const void* variant) {
    if (!armed())
        return;
    const uint64_t tag = reinterpret_cast<const mce::framebuilder::InsertVariant*>(variant)->mTag;
    const uint8_t* const description = static_cast<const uint8_t*>(reinterpret_cast<const mce::framebuilder::InsertVariant*>(variant)->mDescription);
    const RewriteDescInfo* info = RewriteDescriptions::find(group, tag);
    RwDescRecord r{};
    r.group = group;
    r.tag = tag;
    r.name = info ? info->name : "(unknown tag)";
    r.size = info && info->size ? info->size : 0x40;
    r.hash = RewriteHash::fnv1a(description, std::min<size_t>(r.size, 0x1000));
    std::memcpy(r.head, description, sizeof(r.head));
    std::lock_guard<std::mutex> lock(sRwDescMutex);
    sRwDescCurrent.push_back(r);
}

// The probe's own insert detours: (frame builder, variant, a3, a4) like FrameFilterHook's slots; the arguments the game does not show us are forwarded as they are.
static uint64_t rwEffectInsert(void* self, void* variant, uint64_t a3, uint64_t a4);
static uint64_t rwLightInsert(void* self, void* variant, uint64_t a3, uint64_t a4);
static uint64_t rwEditorInsert(void* self, void* variant, uint64_t a3, uint64_t a4);
static Detour* sRwEffectHook = nullptr;
static Detour* sRwLightHook = nullptr;
static Detour* sRwEditorHook = nullptr;

static uint64_t rwEffectInsert(void* self, void* variant, uint64_t a3, uint64_t a4) {
    RewriteProbe::noteInsert(RewriteGroup::Effect, variant);
    return sRwEffectHook->getOriginal<&rwEffectInsert>()(self, variant, a3, a4);
}
static uint64_t rwLightInsert(void* self, void* variant, uint64_t a3, uint64_t a4) {
    RewriteProbe::noteInsert(RewriteGroup::Light, variant);
    return sRwLightHook->getOriginal<&rwLightInsert>()(self, variant, a3, a4);
}
static uint64_t rwEditorInsert(void* self, void* variant, uint64_t a3, uint64_t a4) {
    RewriteProbe::noteInsert(RewriteGroup::Editor, variant);
    return sRwEditorHook->getOriginal<&rwEditorInsert>()(self, variant, a3, a4);
}

static Detour* rwHookSlot(void** vtable, uintptr_t slotOffset, const char* name, void* detour) {
    Detour* hook = HookTable::add(std::make_unique<Detour>(name, reinterpret_cast<uintptr_t>(vtable[slotOffset / sizeof(void*)]), detour));
    BS_CHECK(hook != nullptr);
    hook->enable();
    return hook;
}

void RewriteProbe::onEndFrame(void* frameBuilder) {
    if (!armed())
        return;
    static std::atomic<bool> sInstalled{false};
    if (!sInstalled.exchange(true)) {
        void** const vtable = *reinterpret_cast<void***>(frameBuilder);
        sRwEffectHook = rwHookSlot(vtable, mce::framebuilder::FrameBuilderSlots::kInsertEffect, "RewriteProbe::insertEffect", reinterpret_cast<void*>(&rwEffectInsert));
        sRwLightHook = rwHookSlot(vtable, mce::framebuilder::FrameBuilderSlots::kInsertLight, "RewriteProbe::insertLight", reinterpret_cast<void*>(&rwLightInsert));
        sRwEditorHook = rwHookSlot(vtable, mce::framebuilder::FrameBuilderSlots::kInsertEditor, "RewriteProbe::insertEditor", reinterpret_cast<void*>(&rwEditorInsert));
    }
    std::lock_guard<std::mutex> lock(sRwDescMutex);
    sRwDescLast.swap(sRwDescCurrent);
    sRwDescCurrent.clear();
}
