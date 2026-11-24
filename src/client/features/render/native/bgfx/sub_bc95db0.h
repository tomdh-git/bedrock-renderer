#pragma once

#include <cstddef>
#include <cstdint>

namespace native::bgfx {

// Layout of one small-string (SSO) object as touched by sub_bc95db0:
//   +0x00 mData  pointer (heap or inline)
//   +0x08 mBuf   16-byte inline buffer (read/written as one 16-byte xmm field)
//   +0x10 mSize  uint64  size
//   +0x18 mCapacity uint64 capacity (0xF marks SSO)
// Size 0x20 bytes. Only offsets the function touches are declared.
struct VvSmallString {
    void* mData;        // +0x00
    uint8_t mBuf[16];   // +0x08
    uint64_t mSize;     // +0x10
    uint64_t mCapacity; // +0x18
};

// sub_bc95db0(VvSmallString* dst = rcx, const VvSmallString* src = rdx) -> void
// Clears *src (zeroing ptr/size/capacity, capacity=0xF) and *dst (saving dst's old
// values into the stack frame), then re-initializes *dst as a copy/replacement of *src:
// if src->mSize < 0 it calls the stl handler (noreturn); otherwise dst takes src's data
// (inline when src->mCapacity < 0x10, heap-allocated+copied otherwise), dst->mSize=src->mSize,
// dst->mCapacity=src->mCapacity, and the old dst heap buffer is freed via sub_e935700.
static_assert(offsetof(VvSmallString, mData) == 0x00, "sub_bc95db0 reads/writes +0x00 mData");
static_assert(offsetof(VvSmallString, mBuf) == 0x08, "sub_bc95db0 reads/writes +0x08 mBuf (16B xmm field)");
static_assert(offsetof(VvSmallString, mSize) == 0x10, "sub_bc95db0 reads/writes +0x10 mSize");
static_assert(offsetof(VvSmallString, mCapacity) == 0x18, "sub_bc95db0 reads/writes +0x18 mCapacity");
static_assert(sizeof(VvSmallString) == 0x20, "sub_bc95db0 small-string is 0x20 bytes");

// Forward declarations of callees (native ABI signatures).
// 0xEEC6EC0: lift, memcpy-like (std::memcpy equivalent) — called directly.
void* sub_eec6ec0(void* dst, const void* src, uint64_t count);
// 0xE935700: lift, free — tail-called (jmp) on the success path, noreturn semantics.
void sub_e935700(void* ptr);
// 0x75720 (docs/data/native_boundary.tsv: stl) invalid_parameter-like handler, noreturn.
void sub_75720(void*);
// 0x9BC830 (docs/data/native_boundary.tsv: alloc) heap-failure handler, argument = alloc size.
void sub_9bc830(uint64_t allocSize);
// 0xF9A8C78: _invoke_watson IAT import slot (noreturn), boundary wrapper.
void sub_f9a8c78(void*, void*, void*, uint64_t, uint64_t);

void sub_bc95db0(VvSmallString* dst, VvSmallString* src);

} // namespace native::bgfx
