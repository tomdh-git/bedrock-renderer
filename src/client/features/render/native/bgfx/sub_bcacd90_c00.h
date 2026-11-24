// LIFT 0xbcacd90 chunk c00 header
#pragma once
#include <cstdint>

namespace native::bgfx {

// Layout constants for the sub_bcacd90 stack frame (rbp-relative).
static constexpr std::uintptr_t kFrameSize        = 0x1028;  // mov eax,0x1028 ; sub rsp,rax
static constexpr std::uintptr_t kRbpFromRsp       = 0x80;    // lea rbp,[rsp+0x80]
static constexpr std::uintptr_t kSlotVec4         = 0xA80;   // vec4 built per slot
static constexpr std::uintptr_t kSlotCountRec     = 0x310;   // {qword count=1, ptr data}
static constexpr std::uintptr_t kSlotDataPtr      = 0x318;
static constexpr std::uintptr_t kFrameArg1018     = 0x1018;  // owner / uniform-array owner
static constexpr std::uintptr_t kFrameArg1020     = 0x1020;  // params base (r15/rdi)
static constexpr std::uintptr_t kFrameArg1028     = 0x1028;  // ColorGrading params (rbx)
static constexpr std::uintptr_t kSpillF50         = 0xF50;   // = owner+8 (setUniform arg0)

// Uniform-array record layout (owner+0x38 base, owner+0x42 count).
static constexpr std::uintptr_t kUniformArrayBase = 0x38;
static constexpr std::uintptr_t kUniformArrayCount= 0x42;
static constexpr std::uintptr_t kUniformKeyField  = 0x28;    // [entry+0x28] compared to slot key
static constexpr std::uint32_t  kUniformStride    = 0x10;   // 16 bytes per entry

// Live state passed between chunks of sub_bcacd90.
struct ChunkState_bcacd90_c00 {
    void* frame_base;        // rbp (rsp+0x80 after the 0x1028 frame)
    void* r8_current_slot;   // current slot cursor
    std::uint64_t r9_remaining; // remaining slot count
    void* rdx_slot_base;     // slot base
    void* r12_scratch;
    void* r13_scratch;
    void* r14_scratch;
    void* r15_scratch;
    std::uintptr_t branch;   // set to a fail-handler RVA when an availability gate jumps out of the chunk (0 = fall through)
};

static_assert(kSlotVec4 + 0x10 <= kSlotCountRec, "vec4 must not overlap the count record");
static_assert(kSlotCountRec + 0x10 == kSlotDataPtr + 0x8, "count record layout");
static_assert(kFrameSize >= kSpillF50 + 0x8, "frame must hold the spills");

// Signature (static inline step function):
// static inline void sub_bcacd90_chunk00(ChunkState_bcacd90_c00& state);

} // namespace native::bgfx
