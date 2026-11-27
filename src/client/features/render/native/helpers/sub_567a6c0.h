#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// sub_e935700 (lift set): void* sub_e935700(void* a0); forward-declared here
// so this header does not need to pull in helpers/sub_e935700.h.
void* sub_e935700(void* a0);

} // namespace native

namespace native::helpers {

// sub_567a6c0 (0x567a6c0, size 0xef, 1.26.62.01): releases every 0x50-byte element
// in a region, then releases the backing heap block. Reverse-engineered from the
// disassembly of [0x567a6c0, 0x567a7af).

// Offset constants for the self object (a0 = rcx at entry, copied to rsi).
// Observed accesses: [a0+0x8] R x2, [a0+0x10] R, [a0+0x18] R, [a0+0x20] R.
struct Sub567a6c0Layout {
    static constexpr std::size_t kOffHeapBase = 0x8;    // [R] heap base pointer ([a0+0x8])
    static constexpr std::size_t kOffCount0x10 = 0x10;  // [R] element count ([a0+0x10])
    static constexpr std::size_t kOffRegionBegin = 0x18; // [R] region begin pointer ([a0+0x18])
    static constexpr std::size_t kOffRegionEnd = 0x20;   // [R] region end pointer ([a0+0x20])
    static_assert(sizeof(void*) == 8, "sub_567a6c0: x64 pointers are 8 bytes");
};
static_assert(sizeof(Sub567a6c0Layout) > 0, "sub_567a6c0: layout constant block");

// Offset constants for each 0x50-byte element in the region (rdi walks the region).
// Observed accesses: [rdi+0x18] R/W, [rdi+0x28] W, [rdi+0x30] R/W, [rdi+0x40] R.
struct Sub567a6c0ElemLayout {
    static constexpr std::size_t kOffSubBuf0x18 = 0x18;  // [R/W] sub-buffer pointer ([rdi+0x18])
    static constexpr std::size_t kOffField0x28 = 0x28;   // [W] zeroed field ([rdi+0x28])
    static constexpr std::size_t kOffCount0x30 = 0x30;   // [R/W] element count ([rdi+0x30])
    static constexpr std::size_t kOffFlag0x40 = 0x40;    // [R] flag byte, compared to 6 ([rdi+0x40])
};
static_assert(sizeof(Sub567a6c0ElemLayout) > 0, "sub_567a6c0: elem layout constant block");

// Mirror of the self object at the accessed offsets (byte-exact; no semantics assumed
// beyond the observed accesses).
struct Sub567a6c0This {
    std::uint8_t pad0x00[0x8];           // +0x00..0x07
    void* heap_base;                     // +0x08 [R] heap base pointer
    std::uint64_t count;                 // +0x10 [R] element count
    void* region_begin;                  // +0x18 [R] region begin pointer
    void* region_end;                    // +0x20 [R] region end pointer
};

// Mirror of one 0x50-byte element at the accessed offsets.
struct Sub567a6c0Elem {
    std::uint8_t pad0x00[0x18];          // +0x00..0x17
    void* sub_buf;                       // +0x18 [R/W] sub-buffer pointer
    std::uint8_t pad0x20[0x8];           // +0x20..0x27
    std::uint64_t field0x28;             // +0x28 [W]
    std::uint64_t count;                 // +0x30 [R/W] element count
    std::uint8_t pad0x38[0x8];           // +0x38..0x3f
    std::uint8_t flag0x40;               // +0x40 [R] flag byte
};

// Heap block metadata is read at [ptr - 8] for both the sub-buffer (0x567a733)
// and the backing heap block (0x567a769). No struct models this; it is raw heap
// metadata accessed through a computed pointer.

static_assert(offsetof(Sub567a6c0This, heap_base) == Sub567a6c0Layout::kOffHeapBase,
              "sub_567a6c0: heap_base at +0x8");
static_assert(offsetof(Sub567a6c0This, count) == Sub567a6c0Layout::kOffCount0x10,
              "sub_567a6c0: count at +0x10");
static_assert(offsetof(Sub567a6c0This, region_begin) == Sub567a6c0Layout::kOffRegionBegin,
              "sub_567a6c0: region_begin at +0x18");
static_assert(offsetof(Sub567a6c0This, region_end) == Sub567a6c0Layout::kOffRegionEnd,
              "sub_567a6c0: region_end at +0x20");
static_assert(sizeof(Sub567a6c0This) == 0x28, "sub_567a6c0: this mirror size");

static_assert(offsetof(Sub567a6c0Elem, sub_buf) == Sub567a6c0ElemLayout::kOffSubBuf0x18,
              "sub_567a6c0: sub_buf at +0x18");
static_assert(offsetof(Sub567a6c0Elem, field0x28) == Sub567a6c0ElemLayout::kOffField0x28,
              "sub_567a6c0: field0x28 at +0x28");
static_assert(offsetof(Sub567a6c0Elem, count) == Sub567a6c0ElemLayout::kOffCount0x30,
              "sub_567a6c0: count at +0x30");
static_assert(offsetof(Sub567a6c0Elem, flag0x40) == Sub567a6c0ElemLayout::kOffFlag0x40,
              "sub_567a6c0: flag0x40 at +0x40");
static_assert(sizeof(Sub567a6c0Elem) >= 0x41, "sub_567a6c0: elem sizeof lower bound (+0x40 + 1 byte)");

// Signature (x64 Microsoft ABI).
//   0x567a6c0  push rsi; push rdi; push rbx; sub rsp,0x30; mov rsi,rcx   (self in RCX)
//   Returns void* in RAX: result of sub_e935700 on every non-null, non-fail exit
//   (tail call at 0x567a788), or nullptr on the null path (0x567a78d ret; rax
//   indeterminate in the original).
void* sub_567a6c0(void* self);

} // namespace native::helpers
