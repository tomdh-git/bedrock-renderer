#pragma once
#include <cstdint>
#include <cstddef>

namespace native { namespace bgfx {

// Chunk state for MaterialInstance::initFromMaterial chunk 5 (0xbccdf04..0xbccf341).
// Passed by reference to the static inline step function. Fields mirror the
// live rbp-frame slots and the two arguments of the original function.
// this = MaterialInstance* (rsi / [rbp+0x270]); m = const Material* (rdx).
struct ChunkState_MaterialInstance_initFromMaterial_chunk5 {
    void* this_;          // rsi, MaterialInstance*
    const void* m;        // rdx, const Material*
    void* rbp_frame_base; // rbp

    // [rbp+0x00..0x30] earlier state (set by chunks 1-4)
    void* s000;           // [rbp+0x000]
    void* s010;           // [rbp+0x010]
    void* s060;           // [rbp+0x060]
    void* s070;           // [rbp+0x070]
    void* s088;           // [rbp+0x088]
    void* s0D0;           // [rbp+0x0D0]
    void* s0D8;           // [rbp+0x0D8]
    // [rbp+0x100..0x170]
    uint64_t s100;        // [rbp+0x100]
    uint64_t s118;        // [rbp+0x118] allocator tag save
    uint64_t s120;        // [rbp+0x120]
    void* s128;           // [rbp+0x128]
    float s130f;          // [rbp+0x130]
    uint64_t s138;        // [rbp+0x138]
    uint64_t s140;        // [rbp+0x140]
    void* s148;           // [rbp+0x148]
    void* s150;           // [rbp+0x150]
    void* s158;           // [rbp+0x158]
    uint64_t s160;        // [rbp+0x160]
    uint64_t s168;        // [rbp+0x168]
    // [rbp+0x180..0x1B0] temp vector
    void* s180;           // [rbp+0x180]
    uint64_t s1A0;        // [rbp+0x1A0]
    uint64_t s1A8;        // [rbp+0x1A8]
    uint64_t s1B0;        // [rbp+0x1B0]
    // [rbp+0x210]
    uint8_t s210;         // [rbp+0x210]
    // [rbp+0x228..0x268] hash table state
    uint64_t s228;        // [rbp+0x228]
    void* s230;           // [rbp+0x230]
    // [rbp+0x238..0x250] second vector
    uint64_t s238;        // [rbp+0x238]
    uint64_t s240;        // [rbp+0x240]
    void* s258;           // [rbp+0x258]
    uint64_t s260;        // [rbp+0x260]
    uint64_t s268;        // [rbp+0x268]
    // [rbp+0x270] this (MaterialInstance*)
    // [rbp+0x2F8..0x320] variant loop state
    void* s2F8;           // [rbp+0x2F8]
    void* s300;           // [rbp+0x300]
    void* s310;           // [rbp+0x310]
    uint64_t s318;        // [rbp+0x318]
};

void MaterialInstance_initFromMaterial_chunk5(ChunkState_MaterialInstance_initFromMaterial_chunk5& s);

} } // namespace native::bgfx