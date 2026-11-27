#pragma once
#include <cstddef>
#include <cstdint>

namespace native {
void* sub_e935700(void* a0);
}

namespace native::helpers {

// Refcounted object pointed at by mRefCountedA / mRefCountedB.
// Touched fields: vptr +0x00, strong +0x08 (lock dec on release), weak +0x0C
// (lock dec after destroy). Virtual slot 0 = destroy, slot 1 = dealloc;
// both are invoked through the CFG-thunk data slot [0xF99FFA0] = sub_eea6040
// (`jmp rax`), so there is no static callee target.
struct RefCountedObject {
    void* vptr;                    // +0x00
    std::uint32_t strong;          // +0x08  lock dec on release
    std::uint32_t weak;            // +0x0C  lock dec after destroy
};

static_assert(offsetof(RefCountedObject, vptr) == 0x00, "6694560: refcounted vptr at +0x00");
static_assert(offsetof(RefCountedObject, strong) == 0x08, "6694560: refcounted strong at +0x08");
static_assert(offsetof(RefCountedObject, weak) == 0x0C, "6694560: refcounted weak at +0x0C");
static_assert(sizeof(RefCountedObject) == 0x10, "6694560: refcounted object size");

// Layout of the object passed in rcx (this), reverse-engineered from the
// disassembly of [0x6694560, 0x669465e). Only the offsets read or written are
// declared; everything between them is padding.
//
//   +0x08: refcounted object released second (mRefCountedB)
//   +0x18: refcounted object released first (mRefCountedA)
//   +0x228: heap buffer pointer (mBuffer)
//   +0x238: buffer count/position (mBufferCount)
//   +0x240: buffer size/end index (mBufferSize)
struct sub_6694560_state {
    std::uint8_t pad0x00[0x8];     // +0x00..0x07
    void* mRefCountedB;            // +0x08 refcounted object, released second
    std::uint8_t pad0x10[0x8];     // +0x10..0x17
    void* mRefCountedA;            // +0x18 refcounted object, released first
    std::uint8_t pad0x20[0x208];   // +0x20..0x227
    void* mBuffer;                 // +0x228 heap buffer pointer
    std::uint8_t pad0x230[0x8];    // +0x230..0x237
    std::uint64_t mBufferCount;    // +0x238 buffer count/position
    std::uint64_t mBufferSize;     // +0x240 buffer size/end index
};

static_assert(offsetof(sub_6694560_state, mRefCountedB) == 0x08, "6694560: mRefCountedB at +0x08");
static_assert(offsetof(sub_6694560_state, mRefCountedA) == 0x18, "6694560: mRefCountedA at +0x18");
static_assert(offsetof(sub_6694560_state, mBuffer) == 0x228, "6694560: mBuffer at +0x228");
static_assert(offsetof(sub_6694560_state, mBufferCount) == 0x238, "6694560: mBufferCount at +0x238");
static_assert(offsetof(sub_6694560_state, mBufferSize) == 0x240, "6694560: mBufferSize at +0x240");
static_assert(sizeof(sub_6694560_state) >= 0x248, "6694560: state sizeof lower bound");

// sub_6694560(self = rcx) -> uintptr_t, Minecraft Windows 1.26.62.01.
// BgfxFrameBuilder::endFrame: finalizes the frame buffer, calls sub_e935700,
// then releases the two refcounted members (mRefCountedA first, then
// mRefCountedB). On the weak-ref-zero path for mRefCountedB it tail-calls
// mRefCountedB->vptr[1](mRefCountedB) through the [0xF99FFA0] thunk and
// returns that result.
uintptr_t sub_6694560(sub_6694560_state* self);

} // namespace native::helpers
