#pragma once
// Two shared_ptr members (16B + 16B).
// Ctors and statics need game; omitted (stub-only carrier).
namespace mce {
class TexturePtr {
public:
    std::shared_ptr<void> mClientTexture;     // mClientTexture (shared_ptr, 16B)
    std::shared_ptr<void> mResourceLocationPtr; // mResourceLocationPtr (shared_ptr, 16B)
    bool hasTexture() const {
        return static_cast<bool>(mClientTexture);
    }
};
static_assert(sizeof(TexturePtr) == 32);
} // namespace mce
