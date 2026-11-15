#pragma once
// Blob storage (24B) + ImageDescription (20B) == 44B.
namespace cg {
struct ImageBuffer {
    unsigned char mStorage[24]{};
    unsigned char mImageDescription[20]{};
};
static_assert(sizeof(ImageBuffer) == 44);
} // namespace cg
