#pragma once
// LIFT 0xe878df0 size 0x1e2 1.26.62.01 sub_e878df0

#include <cstddef>
#include <cstdint>

namespace native {
namespace d3d12 {

// Global data slots [V from disassembly of 0xe878df0]
static constexpr std::uintptr_t kDataSlotAllocator = 0x1233E1A8u; // mov rcx,[0x1233E1A8] - allocator object
static constexpr std::uintptr_t kDataSlotF99FFA0   = 0xF99FFA0u;   // call qword ptr [0xF99FFA0] - vendor thunk (sub_eea6040)
static constexpr std::uintptr_t kDataSlotF9A8C78   = 0xF9A8C78u;   // call qword ptr [0xF9A8C78] - std::terminate (IAT, noreturn)

// ------------------------------------------------------------------
// State object layout (0x40 bytes) [V from disassembly of 0xe878df0]
// Both arguments (rcx=a0, rdx=a1) point to this 0x40-byte state.
// Bytes +0x04..+0x07 are read but never written by this function.
// ------------------------------------------------------------------
struct Slot16State {
    uint32_t field00;      // +0x00 - dword copied from a1+0x00
    uint8_t pad04[4];      // +0x04..0x07 - untouched by this function
    void* field08;         // +0x08 - pointer (list head / node)
    void* field10;         // +0x10 - pointer
    void* field18;         // +0x18 - pointer (buffer start)
    void* field20;         // +0x20 - pointer (buffer end/cursor)
    void* field28;         // +0x28 - pointer (buffer end)
    uint64_t field30;      // +0x30 - qword (a1 side set to 7)
    uint64_t field38;      // +0x38 - qword (a1 side set to 8)
}; // size 0x40

static_assert(sizeof(Slot16State) == 0x40, "e878df0: Slot16State size must be 0x40");
static_assert(offsetof(Slot16State, field00) == 0x00, "e878df0: field00 offset");
static_assert(offsetof(Slot16State, field08) == 0x08, "e878df0: field08 offset");
static_assert(offsetof(Slot16State, field10) == 0x10, "e878df0: field10 offset");
static_assert(offsetof(Slot16State, field18) == 0x18, "e878df0: field18 offset");
static_assert(offsetof(Slot16State, field20) == 0x20, "e878df0: field20 offset");
static_assert(offsetof(Slot16State, field28) == 0x28, "e878df0: field28 offset");
static_assert(offsetof(Slot16State, field30) == 0x30, "e878df0: field30 offset");
static_assert(offsetof(Slot16State, field38) == 0x38, "e878df0: field38 offset");

// ------------------------------------------------------------------
// Forward declarations of lift-set callees [V from native_boundary.tsv]
// sub_e935700: class lift, 0xe935700 = jmp 0x392960 (sized dealloc via allocator global)
//   rcx = pointer, rdx = size; return value unused by this caller (dead path)
extern "C" void sub_e935700(void* ptr, std::uint64_t size); // 0xe935700

// ------------------------------------------------------------------
// Boundary callees [V from native_boundary.tsv]
// 0x9bc830 = alloc (noreturn OOM handler)   [boundary.tsv line 149]
// 0xeea6040 = vendor thunk via data slot 0xF99FFA0 (sub_eea6040) [boundary.tsv line 506]
// 0xF9A8C78 = std::terminate (IAT, noreturn) - dead code path, followed by int3
namespace boundary {

// Vendor allocator thunk via data slot 0xF99FFA0 (sub_eea6040)
// Called as: call qword ptr [0xF99FFA0] with rcx = allocator object, rdx = size
void* thunk_f99ffa0(void* allocator, std::size_t size);

// Alloc boundary: sub_9bc830 (class alloc) - noreturn on allocation failure
__declspec(noreturn) void sub_9bc830(std::size_t size);

// CRT boundary: std::terminate via IAT data slot 0xF9A8C78 - noreturn
// Dead code path (followed by int3 at 0xe878fd1); reached only if the grow
//   block's inline-fail branch is taken. sub_9bc830 is noreturn so this is
//   unreachable in practice, but the instruction exists in the function body.
__declspec(noreturn) void terminate_f9a8c78();

} // namespace boundary

// ------------------------------------------------------------------
// Function signature: x64 Microsoft ABI
// rcx = a0 (state object, 0x40 bytes)
// rdx = a1 (state object, 0x40 bytes)
// Returns: rax = a0 (same pointer)
// ------------------------------------------------------------------
extern "C" void* sub_e878df0(void* a0, void* a1);

} // namespace d3d12
} // namespace native
