#pragma once
#include <cstdint>
#include <cstddef>

// LIFT 0xe81a0c0 size 0x54a 1.26.62.01 sub_e81a0c0
//
// RendererContextD3D12 base slot 60 (docs/data/native_functions.tsv row 0xe81a0c0).
// In-place reset of two container buffers (each a {first,last,end} triple of 8-byte
// slots, reallocated to a zeroed 0x48-byte / 9-slot region) followed by a rebuild of
// the index buffer at this+0x08 as an identity map [0, count, 0, 1, 2, ..., count-1]
// (uint16 lanes), where count = ((uint16_t*)old_p08)[1].
//
// `this` (rcx) field offsets touched [V: 0xe81a0c0..0xe81a609]:
//   +0x08  void* p08        old index buffer; ((uint16_t*)p08)[1] is the count (0xe81a4a2/0xe81a4ba); replaced at end (0xe81a5fd)
//   +0x40  void* state40     zeroed (0xe81a2e2)
//   +0x48  void* vecA_first  (0xe81a0cb read, 0xe81a2a7 write)
//   +0x50  void* vecA_last   (0xe81a174 write, 0xe81a2de write)
//   +0x58  void* vecA_end    (0xe81a17c read, 0xe81a2af write)
//   +0x60  void* state60     zeroed (0xe81a4b2)
//   +0x68  void* vecB_first  (0xe81a2d6 read, 0xe81a477 write)
//   +0x70  void* vecB_last   (0xe81a34b write, 0xe81a4ae write)
//   +0x78  void* vecB_end    (0xe81a353 read, 0xe81a47f write)

namespace native::d3d12 {

// View of the `this` object: only the bytes sub_e81a0c0 reads/writes are named;
// the gaps are padding so every field lands at its observed offset.
struct S81a0c0 {
    uint8_t pad_0x00[0x08];   // +0x00
    void*   p08;              // +0x08
    uint8_t pad_0x10[0x30];   // +0x10..0x40
    void*   state40;          // +0x40
    void*   vecA_first;       // +0x48
    void*   vecA_last;        // +0x50
    void*   vecA_end;         // +0x58
    void*   state60;          // +0x60
    void*   vecB_first;       // +0x68
    void*   vecB_last;        // +0x70
    void*   vecB_end;         // +0x78
};

static_assert(sizeof(void*) == 8, "sub_e81a0c0: 64-bit target");
static_assert(offsetof(S81a0c0, p08)       == 0x08, "sub_e81a0c0: p08 @ +0x08");
static_assert(offsetof(S81a0c0, state40)    == 0x40, "sub_e81a0c0: state40 @ +0x40");
static_assert(offsetof(S81a0c0, vecA_first) == 0x48, "sub_e81a0c0: vecA_first @ +0x48");
static_assert(offsetof(S81a0c0, vecA_last)  == 0x50, "sub_e81a0c0: vecA_last @ +0x50");
static_assert(offsetof(S81a0c0, vecA_end)   == 0x58, "sub_e81a0c0: vecA_end @ +0x58");
static_assert(offsetof(S81a0c0, state60)    == 0x60, "sub_e81a0c0: state60 @ +0x60");
static_assert(offsetof(S81a0c0, vecB_first) == 0x68, "sub_e81a0c0: vecB_first @ +0x68");
static_assert(offsetof(S81a0c0, vecB_last)  == 0x70, "sub_e81a0c0: vecB_last @ +0x70");
static_assert(offsetof(S81a0c0, vecB_end)   == 0x78, "sub_e81a0c0: vecB_end @ +0x78");

} // namespace native::d3d12

// Exact x64 Microsoft ABI signature: __fastcall, `this` in rcx, no other parameters,
// no return value (RVA 0xe81a609 `ret`). C linkage, global scope (matches the .cpp definition).
extern "C" void sub_e81a0c0(void* rcx);