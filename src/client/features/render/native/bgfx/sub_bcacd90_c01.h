// LIFT 0xbcacd90 chunk state
// ChunkState for sub_bcacd90_chunk02 (range 0xbcae56d..0xbcafd5f):
// rbp frame base, r8 current slot ptr, r9 remaining count, rdx slot base,
// r12/r13/r14/r15 scratch, xmm6..9 live floats, branch = fail-handler RVA (0 = fall through)
#pragma once
#include <cstdint>

namespace native::bgfx {

struct ChunkState_bcacd90_c01 {
    void* rbp_frame_base;
    void* r8_current_slot;
    unsigned long long r9_remaining;
    void* rdx_slot_base;
    void* r12_scratch;
    void* r13_scratch;
    void* r14_scratch;
    void* r15_scratch;
    float xmm6_live;
    float xmm7_live;
    float xmm8_live;
    float xmm9_live;
    std::uintptr_t branch;
};

} // namespace native::bgfx