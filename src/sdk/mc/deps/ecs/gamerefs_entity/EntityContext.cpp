#include "sdk/mc/deps/ecs/gamerefs_entity/EntityContext.h"
#include "client/core/diagnostics/Log.h"

// The game's registry keeps its component pools in a dense_map<hash, shared_ptr<pool>> (entt 3.14): a vector of nodes
// { size_t next; uint32 key; shared_ptr value; }. Pools are read straight from that vector by hash, so no game function
// is called and no pool is created by looking.
struct PoolNode {
    size_t next;
    uint32_t key;
    void* pool; // shared_ptr's element pointer: the pool (a sparse set, vtable first)
    void* control;
};
static_assert(sizeof(PoolNode) == 0x20);

// Where the pool vector sits inside the registry is found once: the offset whose node array holds a component every
// actor has (the attributes).
static size_t poolsOffset(void* registry) {
    constexpr uint32_t anchor = 0xFD3B0613; // AttributesComponent
    static size_t found = 0;
    if (found)
        return found;
    for (size_t off = 0; off < 0x200; off += 8) {
        auto* v = reinterpret_cast<GameVector<PoolNode>*>(reinterpret_cast<uintptr_t>(registry) + off);
        size_t bytes = reinterpret_cast<uintptr_t>(v->last) - reinterpret_cast<uintptr_t>(v->first);
        if (!v->first || bytes == 0 || bytes % sizeof(PoolNode) || v->last > v->end || bytes / sizeof(PoolNode) > 4096)
            continue;
        for (PoolNode* n = v->first; n != v->last; n++)
            if (n->key == anchor && n->pool) {
                return found = off;
            }
    }
    Logger::fatal("[ecs] the registry's component pool table was not found");
    return 0;
}

static EnttSparseSet* poolFor(void* registry, uint32_t hash) {
    auto* v = reinterpret_cast<GameVector<PoolNode>*>(reinterpret_cast<uintptr_t>(registry) + poolsOffset(registry));
    for (PoolNode* n = v->first; n != v->last; n++)
        if (n->key == hash)
            return static_cast<EnttSparseSet*>(n->pool);
    return nullptr;
}

EnttSparseSet* EntityContext::poolOf(void* registry, uint32_t hash) {
    return poolFor(registry, hash);
}

void* EntityContext::storageFor(uint32_t hash) {
    return poolFor(mRegistry, hash);
}

int EntityContext::probeComponent(uint32_t hash) {
    EnttSparseSet* pool = poolFor(mRegistry, hash);
    if (!pool)
        return -1;
    return pool->indexOf(mEntity) >= 0 ? 1 : 0;
}

// The name of a pool's component type: entt's type_info is { uint32 seq; uint32 identifier; string_view alias }, the alias being
// the compiler's spelling of the type ("struct StateVectorComponent"). Pointers are checked with VirtualQuery before they are read.
static bool readable(const void* p, size_t n) {
    MEMORY_BASIC_INFORMATION mbi{};
    if (!p || !VirtualQuery(p, &mbi, sizeof(mbi)) || mbi.State != MEM_COMMIT || (mbi.Protect & (PAGE_NOACCESS | PAGE_GUARD)))
        return false;
    return reinterpret_cast<uintptr_t>(p) + n <= reinterpret_cast<uintptr_t>(mbi.BaseAddress) + mbi.RegionSize;
}

static std::string poolName(const EnttSparseSet* pool) {
    const auto* info = static_cast<const uint8_t*>(pool->info);
    if (!readable(info, 0x18))
        return "?";
    const char* text = *reinterpret_cast<const char* const*>(info + 8);
    const size_t len = *reinterpret_cast<const size_t*>(info + 16);
    if (len == 0 || len > 200 || !readable(text, len))
        return "?";
    std::string name(text, len);
    for (const char* prefix : {"struct ", "class "})
        if (name.rfind(prefix, 0) == 0)
            name.erase(0, strlen(prefix));
    return name;
}

void EntityContext::forEachPool(const std::function<void(uint32_t, std::string, bool)>& fn) {
    auto* v = reinterpret_cast<GameVector<PoolNode>*>(reinterpret_cast<uintptr_t>(mRegistry) + poolsOffset(mRegistry));
    for (PoolNode* n = v->first; n != v->last; n++) {
        const auto* pool = static_cast<const EnttSparseSet*>(n->pool);
        if (pool)
            fn(n->key, poolName(pool), pool->indexOf(mEntity) >= 0);
    }
}
