#pragma once
#include <cstdint>
#include "client/features/render/rewrite/RewriteRegistry.h"

// Layout constants for the string list head and node structures manipulated by sub_bcd40f0.
// Offsets are derived from the disassembly of 0xbcd40f0..0xbcd41b3.

// Head structure (pointed to by the function argument 'this'):
//   +0x00: Node* first  (first node in list, or null)
//   +0x08: uint64_t* field8  (pointer to a uint64_t that gets zeroed)
struct StringListHead {
    static constexpr std::uintptr_t kFirstOffset = 0x00;
    static constexpr std::uintptr_t kField8Offset = 0x08;
    static_assert(sizeof(void*) == 8, "StringListHead: pointer size");
};

// Node structure (each element in the linked list):
//   +0x00: Node* next   (next node, or null)
//   +0x10: union { char* heapData; char ssoBuffer[0x18]; }  (data pointer or SSO buffer)
//   +0x20: uint64_t size   (string length)
//   +0x28: uint64_t capacity  (capacity; < 0x10 indicates SSO)
struct StringListNode {
    static constexpr std::uintptr_t kNextOffset = 0x00;
    static constexpr std::uintptr_t kDataOffset = 0x10;
    static constexpr std::uintptr_t kSizeOffset = 0x20;
    static constexpr std::uintptr_t kCapacityOffset = 0x28;
    static constexpr std::uint64_t kSsoCapacityThreshold = 0x10;
    static constexpr std::uint64_t kSsoCapacityValue = 0xF;
    static constexpr std::uint64_t kLargeAllocThreshold = 0x1000;
    static constexpr std::uint64_t kAllocHeaderMinSize = 0x20;
    static_assert(sizeof(void*) == 8, "StringListNode: pointer size");
};

// Forward declarations for lift-set callees.
namespace native {
void* sub_e935700(void* a0);  // 0xE935700, lifted in sub_e935700.cpp
}

// Function pointer type for the abort handler at data slot 0xF9A8C78.
// Called with RCX=RDX=R8=R9=0 and 5th stack arg=0; marked noreturn (followed by int3).
using AbortHandlerFn = void(__cdecl*)(std::uint64_t, std::uint64_t, std::uint64_t, std::uint64_t, std::uint64_t);

namespace native {

// sub_bcd40f0 (0xbcd40f0, size 0xc3, 1.26.62.01): String list destructor / cleanup.
// Argument: rcx = StringListHead* this.
// Returns: void* (result of sub_e935700 on the head, via tail call when list empty;
//         otherwise does not return normally — loops through nodes and eventually
//         hits the abort handler on corruption, or tail-calls sub_e935700 on head).
void* sub_bcd40f0(void* thisPtr) noexcept;

} // namespace native