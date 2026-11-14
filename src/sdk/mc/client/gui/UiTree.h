#pragma once

// Reading the game's UI control tree (ScreenView -> VisualTree -> UIControl); the layouts are in OffsetProvider.h.
// Shared by StartScreen and PackLoaderHook (one definition: the build is unity, copies in anonymous namespaces collide).
#include "sdk/OffsetProvider.h"

namespace UiTree {

inline constexpr size_t kController = OffsetProvider::ScreenView_mController, kVisualTree = OffsetProvider::ScreenView_mVisualTree;
inline constexpr size_t kTreeRoot = OffsetProvider::VisualTree_mRoot, kTreeDirty = OffsetProvider::VisualTree_mDirty;
inline constexpr size_t kBits = OffsetProvider::UIControl_mBits, kPos = OffsetProvider::UIControl_mPos, kName = OffsetProvider::UIControl_mName;
inline constexpr size_t kSize = OffsetProvider::UIControl_mSize, kAlpha = OffsetProvider::UIControl_mAlpha, kChildren = OffsetProvider::UIControl_mChildren;

template <typename T>
T& at(const void* base, size_t offset) {
    return *reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(base) + offset);
}

// A 32 byte MSVC release std::string, read without constructing one (Debug and Release layouts differ, see the build notes).
inline std::string readString(const void* s) {
    const size_t size = at<size_t>(s, 0x10), cap = at<size_t>(s, 0x18);
    if (size > 256 || cap < size)
        return "<?>";
    const char* data = cap >= 16 ? at<const char*>(s, 0) : reinterpret_cast<const char*>(s);
    return std::string(data, size);
}

struct Children {
    uint8_t** begin; // shared_ptr<UIControl> entries: pointer + control block, so the control i is begin[i * 2]
    size_t count;
};

inline Children childrenOf(const uint8_t* control) {
    uint8_t* b = at<uint8_t*>(control, kChildren);
    uint8_t* e = at<uint8_t*>(control, kChildren + 8);
    return {reinterpret_cast<uint8_t**>(b), static_cast<size_t>(e - b) / 16};
}

inline const uint8_t* rootOf(void* screenView) {
    const uint8_t* tree = at<const uint8_t*>(screenView, kVisualTree);
    return tree ? at<const uint8_t*>(tree, kTreeRoot) : nullptr;
}

// The first control called `name`, depth first.
inline const uint8_t* find(const uint8_t* c, const char* name, int depth = 0) {
    if (readString(c + kName) == name)
        return c;
    const auto kids = childrenOf(c);
    if (depth > 40 || kids.count > 4096)
        return nullptr;
    for (size_t i = 0; i < kids.count; ++i)
        if (const uint8_t* child = reinterpret_cast<const uint8_t*>(kids.begin[i * 2]))
            if (const uint8_t* hit = find(child, name, depth + 1))
                return hit;
    return nullptr;
}

} // namespace UiTree
