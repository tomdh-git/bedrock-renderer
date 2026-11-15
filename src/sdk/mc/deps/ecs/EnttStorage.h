#pragma once
#include "sdk/mc/deps/ecs/EntityId.h"

// The game's entt 3.14 pools (ENTT_SPARSE_PAGE 2048, ENTT_PACKED_PAGE 128) as raw Release-STL memory.
// Read by hand instead of through entt's API: our Debug STL lays std::vector out differently.
template <typename T>
struct GameVector {
    T* first;
    T* last;
    T* end;
    size_t size() const { return static_cast<size_t>(last - first); }
};
static_assert(sizeof(GameVector<int>) == 0x18);

struct EnttSparseSet {
    void* vtable;
    GameVector<uint32_t*> sparse;
    GameVector<uint32_t> packed;
    const void* info;
    uint32_t mode;
    size_t head;

    static constexpr size_t sparsePage = 2048;

    // Position of the entity in the packed array, or -1.
    ptrdiff_t indexOf(EntityId entity) const {
        const uint32_t e = static_cast<uint32_t>(entity);
        if (e == EntityIdTraits::null)
            return -1;
        const size_t pos = e & EntityIdTraits::entityMask;
        const size_t page = pos / sparsePage;
        if (!sparse.first || !sparse.last || sparse.last < sparse.first || page >= sparse.size())
            return -1;
        const uint32_t* pageData = sparse.first[page];
        if (!pageData)
            return -1;
        const uint32_t elem = pageData[pos % sparsePage];
        constexpr uint32_t versionBits = EntityIdTraits::null & ~EntityIdTraits::entityMask;
        if (((versionBits & e) ^ elem) >= EntityIdTraits::entityMask)
            return -1;
        const size_t packedIndex = elem & EntityIdTraits::entityMask;
        if (!packed.first || !packed.last || packed.last < packed.first || packedIndex >= packed.size())
            return -1;
        return static_cast<ptrdiff_t>(packedIndex);
    }

    size_t size() const { return packed.size(); }

    // The entity stored at packed index i, or null for a slot the game deleted in place (a tombstone keeps the slot, not the entity).
    EntityId at(size_t i) const {
        const uint32_t e = packed.first[i];
        return (e & EntityIdTraits::entityMask) == EntityIdTraits::entityMask ? static_cast<EntityId>(EntityIdTraits::null) : static_cast<EntityId>(e);
    }
};
static_assert(sizeof(EnttSparseSet) == 0x50);

template <typename T>
struct EnttStorage : EnttSparseSet {
    GameVector<T*> payload;

    static constexpr size_t packedPage = 128;

    T* tryGet(EntityId entity) const {
        const ptrdiff_t i = indexOf(entity);
        if (i < 0)
            return nullptr;
        const size_t index = static_cast<size_t>(i);
        const size_t page = index / packedPage;
        if (!payload.first || !payload.last || payload.last < payload.first || page >= payload.size())
            return nullptr;
        T* pageData = payload.first[page];
        if (!pageData)
            return nullptr;
        return &pageData[index % packedPage];
    }
};
