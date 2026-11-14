#pragma once
#include "sdk/mc/deps/ecs/gamerefs_entity/EntityContext.h"

// The entities that have every one of the components: what entt's registry.view<A, B, ...>().each() gives, read straight from the game's pools. entt's own code
// never runs on the game's memory (our Debug STL lays std::vector out differently, and entt's dense_map and sparse_set are made of vectors), so a view is the
// same raw read as EntityContext::tryGetComponent, for many entities at once. An entity that lacks one of the components (an actor still being spawned, or
// being removed) is not in the view: that is how code that walks actors never meets a missing component. A pool the game never created has no entities: the
// view is empty. Game thread.
//
//     EntityView<ActorOwnerComponent, ActorTypeComponent> actors(ctx.mRegistry);
//     actors.each([](EntityId entity, ActorOwnerComponent& owner, ActorTypeComponent& type) { ... });
template <typename... Cs>
class EntityView {
    static_assert(sizeof...(Cs) >= 1);

public:
    explicit EntityView(void* registry) : mPools{static_cast<EnttStorage<Cs>*>(EntityContext::poolOf(registry, Cs::enttHash))...} {
        (requirePayload(std::get<EnttStorage<Cs>*>(mPools)), ...);
    }

    // fn(EntityId, Cs&...) for each entity in all the pools, walking the smallest one.
    template <typename Fn>
    void each(Fn&& fn) const {
        const std::array<const EnttSparseSet*, sizeof...(Cs)> sets{std::get<EnttStorage<Cs>*>(mPools)...};
        const EnttSparseSet* driver = sets[0];
        for (const EnttSparseSet* set : sets) {
            if (!set)
                return; // the game never created that pool: nothing has the component
            if (set->size() < driver->size())
                driver = set;
        }
        for (size_t i = 0; i < driver->size(); ++i) {
            const EntityId entity = driver->at(i);
            if (static_cast<uint32_t>(entity) == EntityIdTraits::null)
                continue;
            const std::tuple<Cs*...> components{std::get<EnttStorage<Cs>*>(mPools)->tryGet(entity)...};
            if (!std::apply([](auto*... c) { return (c && ...); }, components))
                continue;
            std::apply([&](Cs*... c) { fn(entity, *c...); }, components);
        }
    }

private:
    // A tag (flag) component's pool keeps no payload, so there is nothing to hand to fn: those are tested per entity with EntityContext::has.
    template <typename C>
    static void requirePayload(const EnttStorage<C>* pool) {
        BS_CHECK(!pool || pool->size() == 0 || pool->payload.size() != 0);
    }

    std::tuple<EnttStorage<Cs>*...> mPools;
};
