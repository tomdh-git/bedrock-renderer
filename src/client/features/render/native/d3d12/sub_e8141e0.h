#pragma once
#include <cstddef>
#include <cstdint>

namespace native { namespace d3d12 {

// LIFT 0xe8141e0 size 0xd8 1.26.62.01 sub_e8141e0
// "RendererContextD3D12 base slot 23".
//
// The context (rcx / a0) holds an array of per-slot entries at offset
// kSlotArrayOff, each kSlotStride (0xB8) bytes, indexed by the 16-bit slot
// argument (rdx / a1). This function releases one slot entry's resources.
//
// Geometry (from the disassembly):
//   0xe8141e6  movzx eax,dx                 ; idx = zero-extended 16-bit slot
//   0xe8141e9  imul  rax,0xB8               ; idx * stride
//   0xe8141f0  lea   rdi,[rcx+rax]          ; base + idx*stride
//   0xe8141f4  add   rdi,0xAAA178          ; + slot array offset  => entry
//   0xe8141fb  mov   rdx,[rcx+rax+0xAAA180] ; entry+0x08 (release pointer)

constexpr std::size_t kSlotArrayOff = 0xAAA178; // entry array base inside the context
constexpr std::size_t kSlotStride   = 0xB8;     // sizeof(SlotEntry)

// One per-slot entry (0xB8 bytes). Only the fields this function touches are named;
// the rest is opaque padding preserved for the exact size.
struct SlotEntry {
    void*        p0;                  // +0x00  -> rsi; released then cleared to null
    void*        p8;                  // +0x08  -> rdx (this entry's release pointer)
    std::uint8_t pad10[0xA8 - 0x10];  // +0x10  opaque
    std::uint32_t d_A8;               // +0xA8  cleared to 0 at the end
    std::uint8_t  padAC[0xB0 - 0xAC]; // +0xAC  opaque
    std::uint8_t  b_B0;               // +0xB0  cleared to 0
    std::uint8_t  padB1[0xB8 - 0xB1]; // +0xB1  opaque
};

static_assert(sizeof(SlotEntry) == 0xB8,          "SlotEntry must be 0xB8 bytes");
static_assert(offsetof(SlotEntry, p0)  == 0x00,   "p0 at +0x00");
static_assert(offsetof(SlotEntry, p8)  == 0x08,   "p8 at +0x08");
static_assert(offsetof(SlotEntry, d_A8) == 0xA8,  "d_A8 at +0xA8");
static_assert(offsetof(SlotEntry, b_B0) == 0xB0,  "b_B0 at +0xB0");
static_assert(kSlotArrayOff == 0xAAA178,          "slot array offset");
static_assert(kSlotStride == 0xB8,                "slot stride");

// Exact x64 ABI: this in rcx (a0), slot index in dx (a1).
extern "C" void sub_e8141e0(void* a0, unsigned short a1);

} } // namespace