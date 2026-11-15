#pragma once
#include "sdk/Layout.h"
#include "sdk/OffsetProvider.h"
#include "sdk/mc/deps/core/string/GameString.h"

// Registry-owned definition. Only the raw name is mirrored; the rest has no caller and no proven offset.
struct Item {
    // The name without its namespace ("wool"), a string living in the item for as long as the registry does.
    std::string_view rawName() const {
        return reinterpret_cast<const GameString*>(reinterpret_cast<const uint8_t*>(this) + OffsetProvider::Item_mName)->view();
    }
    const char* shortName() const {
        sdkLogStub("Item::shortName");
        return "";
    }
    short itemId() const {
        sdkLogStub("Item::itemId");
        return 0;
    }
};
