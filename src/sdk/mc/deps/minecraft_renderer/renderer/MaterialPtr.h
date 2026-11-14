#pragma once
// Single shared_ptr member (16B).
// Ctors need game; omitted (stub-only carrier).
namespace mce {
struct MaterialPtr {
    std::shared_ptr<void> mInfo; // mRenderMaterialInfoPtr (shared_ptr, 16B)
    bool hasMaterial() const {
        return static_cast<bool>(mInfo);
    }
};
static_assert(sizeof(MaterialPtr) == 16);
} // namespace mce
