#pragma once
#include "sdk/mc/deps/ecs/EntityId.h"
#include "sdk/mc/deps/ecs/EnttStorage.h"
#include "client/core/threading/ThreadContract.h"

// Component types declare the game's entt type hash: static constexpr uint32_t enttHash = 0x...;
struct EntityContext {
    void* mEntityRegistry;
    void* mRegistry; // entt::basic_registry<EntityId>
    EntityId mEntity;

    template <typename T>
    T* tryGetComponent() {
        ThreadContract::warnIfNotGame("ecs read"); // warn-only by design: the off-thread read still runs, the log names it
        auto* pool = static_cast<EnttStorage<T>*>(storageFor(T::enttHash));
        return pool ? pool->tryGet(mEntity) : nullptr;
    }

    // The component's pool itself, for a reader that keeps it (the pool outlives every entity in it): a lookup in it is `pool->tryGet(entity)`. Resolve on the game thread.
    template <typename T>
    EnttStorage<T>* pool() { return static_cast<EnttStorage<T>*>(storageFor(T::enttHash)); }

    // Whether the entity has the component: the test for a tag (flag) component, which has no payload to get.
    template <typename T>
    bool has() { return probeComponent(T::enttHash) == 1; }

    // Type-independent presence test for generic probing: 1 has it, 0 does not, -1 the game has no pool for that hash (never created).
    int probeComponent(uint32_t hash);

    // The pool for a hash in any registry (EntityView walks pools without an entity), nullptr when the game never created one.
    static EnttSparseSet* poolOf(void* registry, uint32_t hash);

    // Every component pool the registry has, with the type's name (entt keeps it in the pool's type_info) and whether this
    // entity has the component. For tools that want to see what the game really uses.
    void forEachPool(const std::function<void(uint32_t hash, std::string name, bool present)>& fn);

private:
    // The pool for the hash from the registry, nullptr when the game never created one.
    void* storageFor(uint32_t hash);
};
static_assert(sizeof(EntityContext) == 0x18);
