#pragma once
#include "sdk/Layout.h"
#include "sdk/OffsetProvider.h"

struct ItemStack;

// A slot list. Only the virtual read is mirrored: the other members have no caller yet and no proven offset.
struct Container {
    ItemStack* getItem(int slot) {
        return callVirtual<ItemStack*>(OffsetProvider::Container_getItem, this, slot);
    }
    int size() const {
        sdkLogStub("Container::size");
        return 0;
    }
};
