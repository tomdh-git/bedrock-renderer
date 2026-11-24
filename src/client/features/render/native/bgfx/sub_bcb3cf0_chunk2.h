// LIFT 0xbcb3cf0 size 0x2119 1.26.62.01 VV frame-graph builder
// Chunk 2/2: 0xbcb54d0..0xbcb5e09

#pragma once

#include <cstdint>
#include <cstddef>

namespace native::bgfx {

// Forward declarations for lifted callees
void sub_130ee0(uintptr_t a0, uintptr_t a1, uintptr_t a2, uintptr_t a3);
void sub_5693a80(uintptr_t a0, uintptr_t a1, uintptr_t a2, uintptr_t a3);
void sub_568c420(uintptr_t a0, uintptr_t a1, uintptr_t a2, uintptr_t a3);
void sub_e935700(uintptr_t a0, uintptr_t a1, uintptr_t a2, uintptr_t a3);

// Boundary wrappers (stl/alloc/crt)
namespace boundary {
void sub_9d6d0(uintptr_t a0, uintptr_t a1, uintptr_t a2, uintptr_t a3);
void sub_9bc830(uintptr_t a0, uintptr_t a1, uintptr_t a2, uintptr_t a3);
void sub_78ed0(uintptr_t a0, uintptr_t a1, uintptr_t a2, uintptr_t a3);
void sub_75720(uintptr_t a0, uintptr_t a1, uintptr_t a2, uintptr_t a3);
void sub_75740(uintptr_t a0, uintptr_t a1, uintptr_t a2, uintptr_t a3);
} // namespace boundary

// Data slot thunks
using thunk_eea6040_t = void(*)(uintptr_t, uintptr_t, uintptr_t, uintptr_t);
using thunk_f9a8c78_t = void(*)(uintptr_t, uintptr_t, uintptr_t, uintptr_t);

// Unresolved callees (forward declared, will be resolved at link)
void sub_eec6de0(uintptr_t a0, uintptr_t a1, uintptr_t a2, uintptr_t a3);

// Chunk state struct matching the live register/stack state at chunk entry (0xbcb54d0)
// Per docs/functions/bcb3cf0.md and docs/data/native_chunks/bcb3cf0.tsv
struct ChunkState_bcb3cf0_c2 {
    // Preserved registers at chunk entry
    uintptr_t rbp;        // frame pointer = rsp + 0x80
    uintptr_t rbx;        // a1
    uintptr_t rsi;        // a2
    uintptr_t r12;        // from [r15+8] at function entry
    uintptr_t r13;        // from [a4+8] at function entry
    uintptr_t r14;
    uintptr_t r15;
    // xmm6 saved at [rbp+0x8F0]
    // We don't model xmm6 in this struct; it's saved/restored via stack

    // Stack frame base (rbp) - all locals accessed via rbp offsets
    // Local slots (per dossier):
    //   rbp-0x50: 16 bytes from a1
    //   rbp+0x40
    //   rbp+0x7D0/7D8
    //   rbp+0x7E0/7E8
    //   rbp+0x7F0..
    //   rbp+0x800/808/810/818
    //   rbp+0x838/840
    //   rbp+0x8B0
    //   rbp+0x8E0/8E8/8F0 (xmm6)
    //   rbp+0x970 = a4 (r13 saved)
    //   rbp+0x978 = a5 (r15 saved)
    //   rbp+0x5A0, 0x548, 0x560, 0x568, 0x550, 0x540, 0x468, 0x450, 0x460
    //   rbp+0x770, 0x758, 0x898, 0x880, 0x868, 0x850
    //   rbp+0x288, 0x508, 0x578, 0x410, 0x690, 0x700, 0x6D0, 0x6E8, 0x6F0, 0x6D8, 0x6C8
    //   rbp+0x1E8, 0x1D0, 0x1E0, 0x8C8, 0x8B0, 0x810, 0x7F8
    //   rbp+0x2C0, 0x448
    //   rbp+0x8D0, 0x8D8
    //   rbp+0x5A0, 0x728 (string buffers)
    // We model the stack as a byte array indexed by rbp offset
    alignas(16) uint8_t stack[0x988];  // Full frame size from prologue: sub rsp,0x988

    // Helper to access stack slots by rbp-relative offset
    template<typename T>
    T& at_rbp(ptrdiff_t offset) {
        return *reinterpret_cast<T*>(&stack[offset + 0x80]);  // rbp = rsp + 0x80, stack[0] = rsp
    }

    template<typename T>
    const T& at_rbp(ptrdiff_t offset) const {
        return *reinterpret_cast<const T*>(&stack[offset + 0x80]);
    }
};

// Layout constants and static_asserts for structs accessed in this chunk
// Offsets are from the dossier and disassembly analysis

// std::basic_string<char> (SSO) layout at various rbp offsets
// Size 0x30, capacity at +0x28, size at +0x20, data pointer at +0x10 or SSO buffer at +0x10
static constexpr size_t kStringSize = 0x30;
static constexpr size_t kStringCapacityOffset = 0x28;
static constexpr size_t kStringSizeOffset = 0x20;
static constexpr size_t kStringDataOffset = 0x10;
static constexpr size_t kStringSsoBufferOffset = 0x10;
static constexpr size_t kStringSsoCapacity = 0xF;  // 15 chars + null

static_assert(kStringSize == 0x30, "std::string size");

// Vector layout (24 bytes: ptr, size, capacity)
static constexpr size_t kVectorSize = 0x18;
static constexpr size_t kVectorPtrOffset = 0x0;
static constexpr size_t kVectorSizeOffset = 0x8;
static constexpr size_t kVectorCapacityOffset = 0x10;

static_assert(kVectorSize == 0x18, "std::vector size");

// Frame size constant
static constexpr size_t kFrameSize = 0x988;
static constexpr size_t kRbpOffset = 0x80;  // rbp = rsp + 0x80

// Data slot RVAs
static constexpr uintptr_t kDataSlot_F99FFA0 = 0xF99FFA0;  // -> sub_eea6040 (vendor thunk)
static constexpr uintptr_t kDataSlot_F9A8C78 = 0xF9A8C78;  // unresolved

// LIFT_FN registry entry (to be added in .cpp)
extern const void* kSub_bcb3cf0_Chunk2_Entry;

} // namespace native::bgfx