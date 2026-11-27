#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// Layout of the handle-allocator object released by sub_0xbc771f0 ([V] from the disassembly of

// [0xbc771f0, 0xbc77347), Minecraft Windows 1.26.62.01; every offset read or written by the body):

//   +0x00 u32 pad00            (not read by release)

//   +0x04 u32 count            (live handle count; decremented on release)

//   +0x08 u32 dense[128]       (dense slot values, stride 4, spans +0x08..+0x207)

//   +0x208 u16 sparse[128]     (handle stored at each slot, or 0xFFFF when free; spans +0x208..+0x307)

//   +0x308 u16 refcount[]      (per-handle refcount, indexed by handle*2, just past sparse)

struct Alloc {
    uint32_t pad00;              // +0x00

    uint32_t count;              // +0x04

    uint32_t dense[128];         // +0x08 .. +0x207

    uint16_t sparse[128];        // +0x208 .. +0x307

};
static_assert(offsetof(Alloc, count) == 0x04, "sub_0xbc771f0: count at +0x04");
static_assert(offsetof(Alloc, dense) == 0x08, "sub_0xbc771f0: dense at +0x08");
static_assert(offsetof(Alloc, sparse) == 0x208, "sub_0xbc771f0: sparse at +0x208");
static_assert(offsetof(Alloc, sparse) + 2u * 128u == 0x308u,
              "sub_0xbc771f0: per-handle refcount base at +0x308");

// Base of the per-handle refcount array at a + 0x308, indexed by handle*2 ([V]: dec word ptr

// [rcx+r9*2+0x308] at 0xbc7720c).

inline uint16_t* refcountBase(Alloc* a) {
    return reinterpret_cast<uint16_t*>(reinterpret_cast<uint8_t*>(a) + 0x308);
}

} // namespace native


namespace native::bgfx {

// sub_0xbc771f0(a = rcx, out = rdx, handle = r8w) -> rax = out.

//

// handle-allocator release:

//   * if handle == 0xFFFF: *out = 0xFFFF, return out (invalid handle, no-op).

//   * else decrement the u16 refcount at +0x308 + handle*2; if it does not reach 0:

//     *out = 0xFFFF, return out (still referenced).

//   * else (refcount reached 0): remove handle from the sparse table at +0x208 (linear scan),

//     decrement count at +0x04, then run a hash-probed compaction over dense[+0x08]/sparse[+0x208]

//     (multiplicative hash (x*0x1EBCA77)>>19*49 & 0x7F). On success *out = handle; if the handle

//     is not present in the sparse table *out = handle as well (re-scan reaches the end).

//   * No calls. Same reads, writes and return as the original; fail-fast (no null guards, no SEH).

//   [V] every instruction of [0xbc771f0, 0xbc77347) is cited beside its block below.

uint16_t* sub_bc771f0(Alloc* a, uint16_t* out, uint16_t handle);

} // namespace native::bgfx

