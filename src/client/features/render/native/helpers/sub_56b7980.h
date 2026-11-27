#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Layout of the state object (rcx / this) for sub_56b7980 (BgfxFrameBuilder::endFrame),
// reverse-engineered from the disassembly of [0x56b7980, 0x56b7a7c).
// Only offsets actually read or written are declared; the bytes between them are padding.
//   +0x00 mFirst: first sub-buffer descriptor / main buffer begin pointer
//                 R at 0x56b798e (mov rdi,[rcx]) and 0x56b7a12 (mov rdi,[rsi])
//                 W at 0x56b7a48 (movups [rsi],xmm0 = 0)
//   +0x08 mLimit: end of the sub-buffer descriptor array, loop bound
//                 R at 0x56b799d (mov rbx,[rcx+8])
//   +0x10 mMainEnd: main buffer end pointer
//                 R at 0x56b7a15 (mov rdx,[rsi+0x10])
//                 W at 0x56b7a4b (mov qword ptr [rsi+0x10],0)
struct sub_56b7980_state {
    void* mFirst;       // +0x00
    void* mLimit;       // +0x08
    void* mMainEnd;     // +0x10
};

static_assert(offsetof(sub_56b7980_state, mFirst) == 0x00, "sub_56b7980_state mFirst at +0x00");
static_assert(offsetof(sub_56b7980_state, mLimit) == 0x08, "sub_56b7980_state mLimit at +0x08");
static_assert(offsetof(sub_56b7980_state, mMainEnd) == 0x10, "sub_56b7980_state mMainEnd at +0x10");
static_assert(sizeof(sub_56b7980_state) >= 0x18, "sub_56b7980_state sizeof lower bound");

// One 0x140-byte sub-buffer descriptor within the [mFirst, mLimit) array.
//   +0xe8 mBegin: sub-buffer begin pointer
//                 R at 0x56b79dd (mov rcx,[r14]); W at 0x56b79b5 (movups [r14],xmm6 = 0)
//   +0xf8 mEnd:   sub-buffer end pointer
//                 R at 0x56b79e5 (mov rdx,[rdi+0xF8]); W at 0x56b79b9 (mov [r14+0x10],0)
//   +0x100 mFlag: enable byte, must be 1
//                 R at 0x56b79cd (cmp byte ptr [rdi+0x100],1)
struct BufferElement {
    std::uint8_t pad0[0xe8];   // +0x00..+0xe7
    void* mBegin;              // +0xe8
    std::uint8_t pad1[8];      // +0xf0..+0xf7
    void* mEnd;                // +0xf8
    std::uint8_t mFlag;        // +0x100
};

static_assert(offsetof(BufferElement, mBegin) == 0xe8, "BufferElement mBegin at +0xe8");
static_assert(offsetof(BufferElement, mEnd) == 0xf8, "BufferElement mEnd at +0xf8");
static_assert(offsetof(BufferElement, mFlag) == 0x100, "BufferElement mFlag at +0x100");
static_assert(sizeof(BufferElement) >= 0x101, "BufferElement sizeof lower bound");

// x64 Microsoft ABI: rcx = self (the state object). Returns uintptr_t in rax.
// On the dealloc path the return is sub_e935700's result; on the early-return path
// (mFirst == 0) the original leaves rax undefined, so the lift returns 0.
uintptr_t sub_56b7980(sub_56b7980_state* self);

} // namespace native::helpers
