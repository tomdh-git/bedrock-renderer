#pragma once
#include "sdk/mc/deps/ecs/EnttStorage.h"

// The actor's attributes (health, absorption, ...), read from the game's own memory. The vectors are raw Release-STL
// triplets (GameVector) so the layout is right in Debug builds too.

// Attribute ids of this build (the map is keyed by them): minecraft:health 7, minecraft:absorption 14 (health is 7 here; 13 read a different attribute).
enum AttributeId { Health = 7, Absorption = 14 };

struct AttributeInstance {
    uint8_t _pad[0x68]; // vptr (virtual dtor+tick) + 0x60 of internals; no vtable here
    float mDefaultMinValue;
    float mDefaultMaxValue;
    float mDefaultValue;
    float mCurrentMinValue;
    float mCurrentMaxValue;
    float mCurrentValue; // 0x7C
    bool mValueChangedDuringTick;
    uint8_t _tail[7];    // the game's instances are 0x88 apart (vptr alignment): indexing the vector needs the real stride
};
static_assert(sizeof(AttributeInstance) == 0x88);

struct BaseAttributeMap {
    GameVector<int> mIds;
    GameVector<AttributeInstance> mInstances;
    uint8_t _pad[0x20];

    AttributeInstance* getInstance(unsigned int id) {
        for (size_t i = 0; i < mIds.size(); i++)
            if (mIds.first[i] == static_cast<int>(id))
                return &mInstances.first[i];
        return nullptr;
    }
};
static_assert(sizeof(BaseAttributeMap) == 0x50);

struct AttributesComponent {
    static constexpr uint32_t enttHash = 0xFD3B0613;
    BaseAttributeMap mBaseAttributeMap;
};
static_assert(sizeof(AttributesComponent) == 0x50);
