#pragma once
// Option virtuals: 0 dtor, 1 save, 2 load(string), 3 load(map), 4 load(Json).
// HideHand is IntOption: idx 2 no-ops (guard on [opt+8]+0x198 falls through to
// ret). Live 1.26.51 gdk 6764: opt 0x163e382d0 vt 0x7ff61e558f50,
// idx 16 = 0x7ff610701f90 parses "1"/"0" (call 0x7ff6106fe990), dword
// cmp/store [this+0x18], then notify. mValue dword at +0x18 (read 0).
#include "sdk/Layout.h"
#include "sdk/OffsetProvider.h"
#include "sdk/mc/client/options/OptionID.h"

struct Option {
    virtual ~Option() = default;
    virtual void save(std::vector<std::pair<std::string, std::string>>& propertyVector) = 0;
    virtual void load(std::string const& valueString) = 0;
    virtual void load(std::map<std::string, std::string>& propertyMap) {}
    virtual void load(const void* jsonValue) {} // Json::Value const&; the name clashes with our Json

    // IntOption value (mValue dword at +0x18) and the live-apply call (the
    // option_push sig: [rsi+10] byte + [rsi+50] renderer via notify).
    int getInt() const { return *reinterpret_cast<const int*>(reinterpret_cast<uintptr_t>(this) + OffsetProvider::Option_mValue); }
    void setInt(int v) { *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + OffsetProvider::Option_mValue) = v; }
    void push(); // option_push: makes a changed value take effect now
};
