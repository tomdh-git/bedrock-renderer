#pragma once
#include "sdk/mc/deps/core/string/GameString.h"

struct HashedString {
    uint64_t mStrHash;
    GameString mStr;
    const HashedString* mLastMatch;
};
static_assert(sizeof(HashedString) == 0x30);
