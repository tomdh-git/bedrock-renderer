#pragma once
#include <cstddef>
#include <cstdint>
// Partial MaterialPass layout read from MaterialPass::findVariant 0xbcc7ce0 (docs/functions/bcc7ce0.md), 1.26.62.01 [V reads, I roles].
namespace mce::material {
struct MaterialPassLayout {
    static constexpr size_t kFlagTablePtr = 0x40;   // pointer to the flag definition table (arg 1 of the mask builder 0xe879eb0)
    static constexpr size_t kFlagSpanBegin = 0x48;  // 8-byte elements, [+0x48,+0x50) 
    static constexpr size_t kFlagSpanEnd = 0x50;
    static constexpr size_t kFlagDefs = 0x60;       // map passed as arg 3
    static constexpr size_t kDefaultMask = 0xA0;    // u64 variant key used when the define map is empty
    static constexpr size_t kVariantSentinel = 0x108; // unordered_map<u64 mask, VariantNode>
    static constexpr size_t kVariantBuckets = 0x118;
    static constexpr size_t kVariantBucketMask = 0x130;
    static constexpr size_t kNodeKey = 0x10;        // u64 mask
    static constexpr size_t kNodeProgram = 0x1C;    // u32 {u16 program, bit16 valid}
    static constexpr size_t kNodeData = 0x20;       // returned pointer
};
static_assert(MaterialPassLayout::kFlagSpanEnd - MaterialPassLayout::kFlagSpanBegin == 8);
static_assert(MaterialPassLayout::kNodeProgram + 4 == MaterialPassLayout::kNodeData);
inline constexpr uint64_t kFnv1Offset64 = 0xcbf29ce484222325ull, kFnv1Prime64 = 0x100000001b3ull;
constexpr uint64_t variantHash(uint64_t mask) {
    uint64_t h = kFnv1Offset64;
    for (int i = 0; i < 8; ++i) { h ^= (mask >> (8 * i)) & 0xFF; h *= kFnv1Prime64; } // FNV-1a: xor then multiply (0xbcc7d63..0xbcc7de3)
    return h;
}
} // namespace mce::material
