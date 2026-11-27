#pragma once
#include <cstddef>
#include <cstdint>

// sub_3cf44f0 (0x3cf44f0, size 0xe3, 1.26.62.01).
//
//   Reads [a0+0x8], [a0+0x10], [a0+0x18], [a0+0x20]; walks the entry array
//   [a0+0x18, a0+0x20) in 0x40-byte steps, zeroing each entry
//   (entry+0x00 byte, entry+0x10, entry+0x18) and conditionally calling
//   sub_e935700; ends with a tail call to sub_e935700. On the [a0+0x8]==0 path
//   it returns without touching RAX. One indirect call reads a function pointer
//   from data slot [0xF9A8C78] (VA 0x140F9A8C78) on the out-of-range path,
//   then int3.
//   Calls: sub_e935700 (lift set, 0x3cf4520), slot [0xF9A8C78] (0x3cf45cc).
//
// x64 Microsoft ABI: RCX = a0, return RAX = void*.

// Argument object layout (the RCX / a0 pointer).
struct sub_3cf44f0Arg {
    void* field00;   // +0x00: not read by this function
    void* field08;   // +0x08: [a0+0x8], null-tested; if zero the function returns early
    void* field10;   // +0x10: [a0+0x10], shl 6, used as tail-call RDX
    void* field18;   // +0x18: array start (rdi)
    void* field20;   // +0x20: array end (rbx)
};

// Array entry layout (0x40-byte stride).
struct sub_3cf44f0Entry {
    void* field00;                    // +0x00: entry pointer (rcx), read and written
    std::uint8_t pad08[0x10 - sizeof(void*)];
    std::uintptr_t field10;           // +0x10: count, written 0 then 0xF
    std::uintptr_t field18;           // +0x18: count, read then written 0xF
    std::uint8_t pad20[0x40 - 0x20];  // +0x20..0x3f
};

struct sub_3cf44f0Layout {
    static_assert(sizeof(void*) == 8, "sub_3cf44f0: x64 ABI, pointer-sized address space");
    static_assert(sizeof(sub_3cf44f0Arg) == 0x28, "sub_3cf44f0: arg object is 5 pointers");
    static_assert(offsetof(sub_3cf44f0Arg, field08) == 0x8, "sub_3cf44f0: arg+0x8");
    static_assert(offsetof(sub_3cf44f0Arg, field10) == 0x10, "sub_3cf44f0: arg+0x10");
    static_assert(offsetof(sub_3cf44f0Arg, field18) == 0x18, "sub_3cf44f0: arg+0x18");
    static_assert(offsetof(sub_3cf44f0Arg, field20) == 0x20, "sub_3cf44f0: arg+0x20");
    static_assert(offsetof(sub_3cf44f0Entry, field00) == 0x0, "sub_3cf44f0: entry+0x0");
    static_assert(offsetof(sub_3cf44f0Entry, field10) == 0x10, "sub_3cf44f0: entry+0x10");
    static_assert(offsetof(sub_3cf44f0Entry, field18) == 0x18, "sub_3cf44f0: entry+0x18");
    static_assert(sizeof(sub_3cf44f0Entry) == 0x40, "sub_3cf44f0: entry is 0x40 bytes");
    static constexpr std::uintptr_t kImageBase = 0x140000000ULL;   // [V: PE optional header ImageBase]
    static constexpr std::uintptr_t kRvaSlotF9a8c78 = 0xF9A8C78;  // [data_f9a8c78] indirect-call slot (RVA)
    static constexpr std::uintptr_t kSlotVA = kImageBase + kRvaSlotF9a8c78; // 0x14F9A8C78
    static constexpr std::uintptr_t kEntryStep = 0x40;              // entry stride
    static constexpr std::uintptr_t kHeapHeaderSize = 8;            // heap size field before an allocated pointer
    static constexpr std::uintptr_t kSmallCount = 0x10;             // count < 0x10 -> zero entry
    static constexpr std::uintptr_t kPage = 0x1000;                 // 0x1000 threshold
    static constexpr std::uintptr_t kMinAlloc = 0x20;               // 0x20 minimum
    static constexpr std::uintptr_t kExtra = 0x28;                  // rax + 0x28
    static constexpr std::uintptr_t kSlotTag = 0x27;                // or 0x27
    static_assert(kImageBase + kRvaSlotF9a8c78 == 0x14F9A8C78ULL, "sub_3cf44f0: slot VA 0x14F9A8C78");
    static_assert(kEntryStep == 0x40, "sub_3cf44f0: entry stride 0x40");
};
