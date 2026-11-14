#pragma once

// The game's entt entity: 18 bits of index, 11 of version.
enum class EntityId : uint32_t {};

struct EntityIdTraits {
    static constexpr uint32_t entityMask = 0x3FFFF;
    static constexpr uint32_t versionMask = 0x7FF;
    static constexpr uint32_t null = entityMask | (versionMask << 18);
};
