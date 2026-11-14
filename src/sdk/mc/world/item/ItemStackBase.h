#pragma once
#include "sdk/Layout.h"
// Member order: mItem (WeakPtr), mUserData, mBlock, mAuxValue, mCount,
// mValid_DeprecatedSeeComment, mShowPickUp, mWasPickedUp, mPickupTime,
// mCanPlaceOn(+Hash), mCanDestroy(+Hash), mBlockingTick, mChargedItem.
// Virtuals: dtor, reinit x3, setNull, toString, toDebugString.
// Offsets unproven; no data members here (ItemStack keeps the proven 152B
// body). Accessors below are TODO stubs, null-guarded defaults.

struct Item;
struct Block;

struct ItemStackBase {
    const Item* getItem() const {
        sdkLogStub("ItemStackBase::getItem");
        return nullptr;
    }
    short getAuxValue() const {
        sdkLogStub("ItemStackBase::getAuxValue");
        return 0;
    }
    unsigned char getCount() const {
        sdkLogStub("ItemStackBase::getCount");
        return 0;
    }
    bool isNull() const {
        sdkLogStub("ItemStackBase::isNull");
        return true;
    }
    // TODO: userData/block/placeOn/destroy/blockingTick/chargedItem/reinit/
    // setNull/toString when a caller needs them; each needs a proven offset.
};
