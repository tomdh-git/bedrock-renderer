#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Layout of the object passed to sub_67602c0 in rcx (this), reverse-engineered from the
// disassembly of [0x67602c0, 0x67603aa), Minecraft Windows 1.26.62.01.
// Every [reg+off] access listed below is a [V] fact (cited by instruction).
//
// Object fields (this = rcx = a0):
//   +0x08 (R, 8): heap/allocator handle                          0x67602cf  mov rcx,[rcx+8]
//   +0x10 (R, 8): block-array element count                      0x6760345  mov rax,[rsi+0x10]
//   +0x18 (R, 8): block array begin pointer                      0x67602dc  mov rdi,[rsi+0x18]
//   +0x20 (R, 8): block array end pointer                        0x67602e0  mov rbx,[rsi+0x20]
//
// Each array element is a 0x48-byte block (rdi walks [begin,end) in steps of 0x48):
//   +0x00 (R/W, 8): block begin pointer                          0x676030f  mov rcx,[rdi]
//                                                    0x67602f5  movups [rdi],xmm6  (writes +0x00,+0x08)
//   +0x10 (R/W, 8): block end pointer                            0x6760317  mov rdx,[rdi+0x10]
//                                                    0x67602f8  mov qword [rdi+0x10],0
//   +0x40 (R, 1):   flag byte (block processed only when == 1)   0x6760309  cmp byte [rdi+0x40],1
//
// Heap block at a block begin pointer: -0x8 (R, 8): block size header read on the
// large-buffer path                                             0x6760327  mov rax,[rcx-8]
// Heap block at the handle: -0x8 (R, 8): block size header       0x676035a  mov rax,[rcx-8]
//
// Callees:
//   - sub_e935700 (lift set): argument forwarded in RCX, result in RAX; called directly
//     through its native symbol, never a boundary wrapper.
//   - data slot 0xF9A8C78 (fail handler, noreturn): 4 zero args, then int3 pad.
//
// x64 Microsoft ABI: RCX = this, return in RAX (sub_e935700's result). No null guards and
// no SEH exist in the original; none are added.

struct sub_67602c0_block {
    void* begin;                            // +0x00 [R/W] block begin pointer
    std::uint8_t pad0x08[0x8];              // +0x08 [W] zeroed by the movups clear at +0x00
    void* end;                              // +0x10 [R/W] block end pointer
    std::uint8_t pad0x18[0x28];             // +0x18..0x3F
    std::uint8_t flag;                      // +0x40 [R] flag byte
};
static_assert(offsetof(sub_67602c0_block, begin) == 0x00, "sub_67602c0: block begin at +0x00");
static_assert(offsetof(sub_67602c0_block, end) == 0x10, "sub_67602c0: block end at +0x10");
static_assert(offsetof(sub_67602c0_block, flag) == 0x40, "sub_67602c0: block flag at +0x40");
static_assert(sizeof(sub_67602c0_block) == 0x48, "sub_67602c0: block size 0x48");

struct sub_67602c0_state {
    static constexpr std::size_t kOffHandle = 0x08;  // heap/allocator handle
    static constexpr std::size_t kOffCount = 0x10;   // block-array element count
    static constexpr std::size_t kOffBegin = 0x18;   // block array begin pointer
    static constexpr std::size_t kOffEnd = 0x20;     // block array end pointer

    std::uint8_t pad0x00[0x08];             // +0x00..0x07
    void* handle;                           // +0x08 [R] heap/allocator handle
    std::uint64_t count;                    // +0x10 [R] block-array element count
    void* begin;                            // +0x18 [R] block array begin pointer
    void* end;                              // +0x20 [R] block array end pointer
};
static_assert(offsetof(sub_67602c0_state, handle) == sub_67602c0_state::kOffHandle,
              "sub_67602c0: handle at +0x08");
static_assert(offsetof(sub_67602c0_state, count) == sub_67602c0_state::kOffCount,
              "sub_67602c0: count at +0x10");
static_assert(offsetof(sub_67602c0_state, begin) == sub_67602c0_state::kOffBegin,
              "sub_67602c0: begin at +0x18");
static_assert(offsetof(sub_67602c0_state, end) == sub_67602c0_state::kOffEnd,
              "sub_67602c0: end at +0x20");
static_assert(sizeof(sub_67602c0_state) == 0x28, "sub_67602c0: state mirror size");

// Data-slot RVA of the fail handler (call qword ptr [slot]; pointer read at call time).
static constexpr std::uintptr_t kRvaFailSlot = 0xF9A8C78;
static_assert(kRvaFailSlot == 0xF9A8C78, "sub_67602c0: fail-handler data slot RVA 0xF9A8C78");

// Signature (x64 Microsoft ABI): RCX = this (sub_67602c0_state*), return in RAX.
// Tail-calls sub_e935700 on every non-fail exit; the null-handle path returns with rax
// unset in the original (undefined), so this lift returns nullptr there.
void* sub_67602c0(sub_67602c0_state* self);

} // namespace native::helpers
