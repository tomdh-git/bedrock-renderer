// LIFT header for bgfx::Context::frame chunk 0xbc685af..0xbc687b7 (part 2/2)
// Unit U-EX1.bc66de0.c01 — xdata::gpu::Context::frame, 1.26.62.01
#pragma once
#include <cstdint>
#include <cstddef>

namespace native { namespace bgfx {

// --- Lifted callees used by this chunk (forward declarations) ----------------
// 0xebce650  sub_ebce650  (native_boundary.tsv: lift)
void sub_ebce650(void* rcx, uint32_t edx, void* r8, uint32_t r9d);
// 0xebdbf20  sub_ebdbf20  (native_boundary.tsv: lift)
void sub_ebdbf20(void* rcx);
// 0xebce430  sub_ebce430  (thunk: movzx edx,dl; jmp 0xEEC6ED0 / CRT) -> memset
void sub_ebce430(void* dst, uint32_t byte, uint32_t count);

// --- Layout constants (Context / frame-object offsets) -----------------------
static constexpr uint32_t kViewCount_Off    = 0x4E8;       // u16 per-view count at this+0x4E8
static constexpr uint32_t kCopySrcCount_Off = 0x13CF0;     // u16 count for the 16-byte copy loop
static constexpr uint32_t kCopyDst_Off      = 0x13CF8;     // pointer (dst of copy loop)
static constexpr uint32_t kCopySrc_Off      = 0x13D08;     // pointer (src of copy loop)
static constexpr uint32_t kSrcCount_Off     = 0x13D00;     // u16 moved into this+0x13CF0
static constexpr uint32_t kSub_Off          = 0x3D0;       // arg to sub_ebdbf20
static constexpr uint32_t kFramePtr0_Off    = 0x1CFD0C0;   // pointer A
static constexpr uint32_t kFramePtr1_Off    = 0x1CFD0C8;   // pointer B
static constexpr uint32_t kFrameNum_Off     = 0xE746D8;    // u32 frame number
static constexpr uint32_t kSwapSrc_Off      = 0xDC57F0;    // u64 source of dword swap
static constexpr uint32_t kSwapDst_Off      = 0xE60E88;    // u64 destination of dword swap
static constexpr uint32_t kFlag_Off         = 0xD457C0;    // u32 = 1
static constexpr uint32_t kZero0_Off        = 0xDC57D0;    // u32 = 0
static constexpr uint32_t kZero1_Off        = 0xDC57E8;    // u32 = 0
static constexpr uint32_t kZeroW_Off        = 0xDC57EC;    // u16 = 0
static constexpr uint32_t kZeroQ_Off        = 0xDC57F0;    // u64 = 0
static constexpr uint32_t kConst_Off        = 0xDC5818;    // u64 = 0x4000000000000
static constexpr uint32_t kConst2_Off       = 0xE05820;    // u64 = 0x4000000000000
static constexpr uint32_t kZeroUW_Off       = 0xE74988;    // u16 = 0
static constexpr uint32_t kMemsetDst_Off    = 0x1EAAC60;   // memset(this+.., 0, 0x400)
static constexpr uint32_t kObjPtr_Off       = 0xE60DE0;    // pointer held by frame0/frame1
static constexpr uint32_t kShiftByte_Off    = 0x10;        // shift byte inside obj
static constexpr uint32_t kWide_Off         = 0x1EBF194;   // u32 (r8d >> 3)
static constexpr uint32_t kHigh_Off         = 0x1EBF198;   // u32 (>> cl)
static constexpr uint32_t kViewStride       = 0x138;       // per-view slot stride
static constexpr uint32_t kViewBase_Off     = 0x4F0;       // view array base at this+0x4F0
static constexpr uint64_t kSwapConst        = 0x4000000000000ull;
static constexpr uint64_t kAllocGlobal      = 0x12ADF800;   // global holding allocator
static constexpr uint64_t kAllocSlot        = 0x0F99FFA0;   // indirect call slot -> 0xeea6040 (vendor)
static constexpr uint32_t kMemsetCount      = 0x400;

// --- Live state handed to the chunk step function ----------------------------
struct ContextFrameChunkC01State {
    void*     ctx;        // rsi at entry: this (xdata::gpu::Context*)
    uint8_t*  viewDst;    // rdi: current per-view copy dst (ctx+0x4F0 + r12*0x138)
    uint64_t  r15;        // frame-relative src offset (0xE60EC8 + r12*0x138)
    uint32_t  r12;        // per-view loop counter
    uint64_t  r14;        // frame0 + r15 (src pointer)
    void*     frameBase;  // rbp: rsp+0x50
    uint32_t  local10;    // [rbp-0x10]
    uint64_t  local18;    // [rbp-0x18] (rbx points here)
};

static_assert(sizeof(ContextFrameChunkC01State) == 64, "chunk state layout");
static_assert(kViewStride == 0x138, "view stride must be 0x138");
static_assert(kSwapConst == 0x4000000000000ull, "swap constant");

} }