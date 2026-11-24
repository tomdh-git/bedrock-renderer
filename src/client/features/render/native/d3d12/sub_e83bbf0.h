#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// Layout recovered from the disassembly of 0xe83bbf0 (size 0x1db, 1.26.62.01).
// Hash-table remove: given a container (rcx) and a 64-bit key (rdx), find the node
// whose key matches, release its payload via the indirect thunk at 0xF99FFA0
// (sub_eea6040), unlink it from the bucket chain and the node's prev/next links,
// notify an allocator-ish object at [0x12ADF800], and decrement the container count.
//
//   rcx = container* (a0), rdx = key (u64). Return: void.
//
// Indirect call: `call qword ptr [0xF99FFA0]` reads the pointer at runtime and calls
// it with (this=payload, ...) per the instruction sequence [V].

static constexpr std::uintptr_t kGuardSlot = 0xF99FFA0u; // call qword ptr [0xF99FFA0]
static constexpr std::uintptr_t kNotifyGlobal = 0x12ADF800u; // mov rcx,[0x12ADF800]

static constexpr std::size_t kContainerBegin = 0x08; // rax = [rcx+8] (bucket array base)
static constexpr std::size_t kContainerEnd   = 0x10; // r8  = [rcx+0x10] (end)
static constexpr std::size_t kContainerCount  = 0x00; // dec qword ptr [rsi] (count at +0)

static constexpr std::size_t kNodeKey   = 0x00; // cmp [rdi], rdx
static constexpr std::size_t kNodePayload = 0x08; // mov rcx,[rdi+8]; call [rax+0x10]
static constexpr std::size_t kNodeNext  = 0x10; // mov rdi,[rdi+0x10]
static constexpr std::size_t kNodePrevLink = 0x18; // mov [rcx+0x10]/[rcx+0x18]

static_assert(kContainerEnd - kContainerBegin == 0x08, "e83bbf0: end follows begin");
static_assert(kNodePayload - kNodeKey == 0x08, "e83bbf0: payload follows key");
static_assert(kNodeNext - kNodePayload == 0x08, "e83bbf0: next follows payload");
static_assert(kNodePrevLink - kNodeNext == 0x08, "e83bbf0: prevlink follows next");

extern "C" void sub_e83bbf0(void* container, std::uint64_t key);

} // namespace native
