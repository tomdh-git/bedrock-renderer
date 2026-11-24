// LIFT 0xbc40a30 size 0x146 1.26.62.01 endFrame
#include "client/features/render/native/bgfx/sub_bc40a30.h"
#include <cstring>
#include <cstdlib>

// Layout assertions for the BgfxFrameBuilder offsets used by this function.
// (The full set of offset static_asserts lives in sub_bc40a30.h; this one
// anchors the header to the lifted function so liftcheck sees it here too.)
static_assert(offsetof(BgfxFrameBuilder, mSize) == 0x28, "endFrame reads src+0x28 as size");
static_assert(offsetof(BgfxFrameBuilder, mCapacity) == 0x30, "endFrame branches on src+0x30 capacity");

// Verbatim call instructions from the disassembly of [0xbc40a30, 0xbc40b76).
// All external targets are CRT/library intrinsics (spec §5/6): malloc via IAT,
// memcpy thunk, invalid_parameter, heap failure handler. None are game calls
// requiring a boundary wrapper; UNRESOLVED CALL = none.
// 0xbc40ad0  call qword ptr [0xF99FFA0]
// 0xbc40af4  call qword ptr [0xF99FFA0]
// 0xbc40b17  call 0xEEC6EC0
// 0xbc40b5b  call 0x9BC830
// 0xbc40b68  call 0x75720
// 0xbc40b70  call 0x9BC830

// CRT intrinsics called by the original (all noreturn or standard library).
extern "C" __declspec(noreturn) void invalid_parameter();
extern "C" __declspec(noreturn) void heap_failure(uint64_t alloc_size);

namespace native::bgfx {

BgfxFrameBuilder* endFrame(BgfxFrameBuilder* dst, void* src) {
    const BgfxFrameBuilder* s = static_cast<const BgfxFrameBuilder*>(src);

    // 0xbc40a43..0xbc40a4e: copy src+0x00(16B) and src+0x10(8B) to dst
    std::memcpy(dst, s, 16);                 // dst+0x00 = src+0x00 (16 bytes)
    dst->mField10 = s->mField10;             // dst+0x10 = src+0x10

    // 0xbc40a51..0xbc40a58: zero dst+0x18 (16B) and dst+0x28 (16B)
    std::memset(&dst->mData, 0, 16);         // dst+0x18 = 0 (mData + pad)
    std::memset(&dst->mSize, 0, 16);         // dst+0x28 = 0 (mSize + mCap)

    // 0xbc40a5c: rbx = src+0x28 (size)
    uint64_t size = s->mSize;

    // 0xbc40a60..0xbc40a71: branch on src capacity (0x10 threshold)
    void* srcData;
    if (s->mCapacity < 0x10) {
        // SSO source: inline data at &src+0x18
        srcData = static_cast<void*>(static_cast<uint8_t*>(src) + 0x18);
    } else {
        // Heap source: data pointer at src+0x18
        srcData = s->mData;
    }

    // 0xbc40a71: size < 0 -> invalid_parameter (noreturn)
    if (static_cast<int64_t>(size) < 0) {
        invalid_parameter();
    }

    // 0xbc40a7a: size > 0xF -> heap destination
    if (size > 0xF) {
        uint64_t rdx = size | 0xF;
        uint64_t r12 = 0x16;
        if (rdx >= 0x17) r12 = rdx;           // cmovae: size class

        void* allocated;
        if (rdx < 0xFFF) {
            // 0xbc40aec..0xbc40af4: fast path malloc(r12 + 1)
            allocated = std::malloc(r12 + 1);
            if (!allocated) {
                heap_failure(r12 + 1);        // 0xbc40b00 -> 0x9BC830 (noreturn)
            }
            dst->mData = allocated;           // 0xbc40b02
        } else {
            // 0xbc40ac8..0xbc40af4: slow path malloc(r12 + 0x28), align 32
            allocated = std::malloc(r12 + 0x28);
            if (!allocated) {
                heap_failure(r12 + 0x28);     // noreturn
            }
            uint8_t* p = static_cast<uint8_t*>(allocated);
            uintptr_t aligned = (reinterpret_cast<uintptr_t>(p) + 0x27) & ~0x1FULL;
            *reinterpret_cast<uintptr_t*>(aligned - 8) = reinterpret_cast<uintptr_t>(p);  // cookie
            dst->mData = reinterpret_cast<void*>(aligned);                                // 0xbc40b02
        }
        dst->mSize = size;                    // 0xbc40b06
        dst->mCapacity = r12;                 // 0xbc40b0a
        // 0xbc40b17: memcpy(dst_data, src_data, size + 1)
        std::memcpy(dst->mData, srcData, size + 1);
    } else {
        // SSO destination (size <= 0xF)
        dst->mSize = size;                    // 0xbc40a84
        dst->mCapacity = 0xF;                 // 0xbc40a88
        // 0xbc40a94: memcpy(&dst+0x18, srcData, 16)
        std::memcpy(&dst->mData, srcData, 16);
    }

    // 0xbc40b1c: common tail
    dst->mField3C = s->mField3C;              // 0xbc40b20
    dst->mField38 = s->mField38;              // 0xbc40b27
    dst->mField78 = 0;                        // 0xbc40b2a
    dst->mField80 = 0;                        // 0xbc40b2e
    std::memset(dst->mField40, 0, 16);        // 0xbc40b38
    std::memset(dst->mField50, 0, 16);        // 0xbc40b3c
    std::memset(dst->mField60, 0, 16);        // 0xbc40b40

    return dst;                               // 0xbc40b44: rax = rsi = dst
}

LIFT_FN(BgfxFrameBuilder_endFrame, "BgfxFrameBuilder::endFrame", 0xbc40a30, endFrame, nullptr);

} // namespace native::bgfx
