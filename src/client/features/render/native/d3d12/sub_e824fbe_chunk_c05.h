#pragma once
#include <cstdint>
#include <cstddef>

namespace native {
namespace d3d12 {

struct ChunkState_e824fbe_c05 {
    // live state passed in (rbp-frame); fields TBD
    void* rbx = nullptr;
    void* rbp = nullptr;
    uint64_t rcx = 0;
    uint64_t rsi = 0;
    uint64_t rdi = 0;
    uint64_t rax = 0;
    uint64_t rdx = 0;
    uint64_t r10 = 0;
};

} // namespace d3d12
} // namespace native
