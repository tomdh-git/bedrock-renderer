#pragma once
// LIFT 0xe824a42 size 0x8aa1 1.26.62.01 sub_e824a42
// CHUNK 0xe827a1a..0xe829207

#include <cstdint>

namespace native {

// Chunk state for 0xe827a1a..0xe829207.
// The job frame base is rbx (0xE238-byte frame). All offsets below are
// relative to rbx and are documented in docs/functions/e824a42.md.
// This struct is a raw view: fields are accessed at their documented offsets.
struct ChunkState_e824a42_c02 {
    // Convenience: construct from the job frame base pointer.
    static inline ChunkState_e824a42_c02& from_frame(void* frame_base) {
        return *reinterpret_cast<ChunkState_e824a42_c02*>(frame_base);
    }

    // Access a field at offset off with type T.
    template <typename T>
    inline T& at(ptrdiff_t off) {
        return *reinterpret_cast<T*>(reinterpret_cast<char*>(this) + off);
    }
    template <typename T>
    inline const T& at(ptrdiff_t off) const {
        return *reinterpret_cast<const T*>(reinterpret_cast<const char*>(this) + off);
    }
};

void chunk_e824a42_c02(void* state);

} // namespace native