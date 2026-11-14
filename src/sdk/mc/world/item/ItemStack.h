#pragma once
#include "sdk/Layout.h"
#include "sdk/OffsetProvider.h"

struct Block;
struct Item;

// ItemStackBase + mNetIdVariant (ItemStackNetIdVariant 24B). Body is 152B inside ItemInHandRenderer, so 152B is the size; the members below are read
// by offset (OffsetProvider, LeviLamina 26.60 layout) and the rest stays opaque.
struct ItemStack {
    unsigned char mOpaque[152]{};

    // mItem is a WeakPtr<Item>: one pointer to a counter whose first member is the Item*. An empty stack has no counter.
    Item* item() const {
        void** counter = *reinterpret_cast<void** const*>(mOpaque + OffsetProvider::ItemStack_mItem);
        return counter ? static_cast<Item*>(*counter) : nullptr;
    }
    Block* block() const { return *reinterpret_cast<Block* const*>(mOpaque + OffsetProvider::ItemStack_mBlock); }
    uint8_t count() const { return mOpaque[OffsetProvider::ItemStack_mCount]; }
    bool isNull() const { return item() == nullptr || count() == 0; }
};
static_assert(sizeof(ItemStack) == 152);
