#pragma once
// LIFT 0xe878010 size 0x4f2 1.26.62.01 BgfxFrameBuilder slot 16

#include <cstddef>
#include <cstdint>

namespace native {

// Global data slots [V from disassembly of 0xe878010]
static constexpr std::uintptr_t kDataSlotAllocator = 0x1233E1A8u; // mov rcx,[0x1233E1A8] - allocator object
static constexpr std::uintptr_t kDataSlotF99FFA0   = 0xF99FFA0u;   // call qword ptr [0xF99FFA0] - vendor thunk (sub_eea6040)

// ------------------------------------------------------------------
// Hash map node layout (0x50 bytes) [V from disassembly of 0xe878010]
// Used as the intrusive node type in the per-bucket red-black tree.
// ------------------------------------------------------------------
struct HashMapNode {
    // 0x00..0x07: left child / prev pointer
    void* left;
    // 0x08..0x0F: right child / next pointer
    void* right;
    // 0x10..0x17: parent / bucket head pointer
    void* parent;
    // 0x18..0x19: color/flags (byte at 0x18 = color, byte at 0x19 = flag)
    uint16_t flags;
    // 0x1A..0x1F: padding
    uint32_t pad1A;
    // 0x20..0x27: key data pointer (inline at this+0x20 or heap)
    void* keyData;
    // 0x28..0x2F: padding / part of inline key buffer
    uint64_t pad28;
    // 0x30..0x37: key length
    uint64_t keyLen;
    // 0x38..0x3F: key capacity (0xF = SSO inline)
    uint64_t keyCap;
    // 0x40..0x47: associated value / field40
    void* field40;
    // 0x48..0x4F: associated value / field48
    uint64_t field48;
};

static_assert(sizeof(HashMapNode) == 0x50, "e878010: HashMapNode size must be 0x50");
static_assert(offsetof(HashMapNode, left) == 0x00, "e878010: left offset");
static_assert(offsetof(HashMapNode, right) == 0x08, "e878010: right offset");
static_assert(offsetof(HashMapNode, parent) == 0x10, "e878010: parent offset");
static_assert(offsetof(HashMapNode, flags) == 0x18, "e878010: flags offset");
static_assert(offsetof(HashMapNode, keyData) == 0x20, "e878010: keyData offset");
static_assert(offsetof(HashMapNode, keyLen) == 0x30, "e878010: keyLen offset");
static_assert(offsetof(HashMapNode, keyCap) == 0x38, "e878010: keyCap offset");
static_assert(offsetof(HashMapNode, field40) == 0x40, "e878010: field40 offset");
static_assert(offsetof(HashMapNode, field48) == 0x48, "e878010: field48 offset");

// ------------------------------------------------------------------
// Container object layout (the `this` / a0 argument) [V from disassembly]
// +0x00: pointer to container A (HashMapNode-like)
// +0x08: pointer to container B (HashMapNode-like) - also size counter at [this+8]
// ------------------------------------------------------------------
struct HashMapContainer {
    void* containerA; // +0x00
    void* containerB; // +0x08 - also functions as size field (incremented at 0xe878274)
};

// Key string layout used by a2 argument [V from disassembly]
// +0x00: data pointer (heap) or inline buffer start (SSO)
// +0x10: size
// +0x18: capacity (0x10 = SSO threshold)
struct KeyString {
    void* data;   // +0x00
    uint64_t size; // +0x10
    uint64_t cap;  // +0x18
};

// ------------------------------------------------------------------
// Forward declarations of lift-set callees [V from native_boundary.tsv]
// sub_eec6eb0: key comparison function (lift)
//   rcx = keyA data, rdx = keyB data, r8 = min size
//   returns: comparison result in eax (0 = equal)
extern "C" int sub_eec6eb0(const void* keyA, const void* keyB, std::size_t minSize);

// sub_eec6ec0: memcpy-like copy (lift)
//   rcx = dst, rdx = src, r8 = count
extern "C" void sub_eec6ec0(void* dst, const void* src, std::size_t count);

// ------------------------------------------------------------------
// Boundary callees [V from native_boundary.tsv]
// docs/data/native_boundary.tsv: 0x75720=stl, 0xa4ea0=stl, 0x9bc830=alloc,
// 0xeea6040=vendor (via data slot 0xF99FFA0)
namespace boundary {

// Vendor allocator thunk via data slot 0xF99FFA0 (sub_eea6040)
// Called as: call qword ptr [0xF99FFA0] with rcx = allocator object, rdx = size
void* thunk_f99ffa0(void* allocator, std::size_t size);

// STL boundary: sub_75720 (class stl) - noreturn on invalid parameter
__declspec(noreturn) void sub_75720();

// STL boundary: sub_a4ea0 (class stl) - noreturn ("too long")
__declspec(noreturn) void sub_a4ea0();

// Alloc boundary: sub_9bc830 (class alloc) - noreturn on allocation failure
__declspec(noreturn) void sub_9bc830(std::size_t size);

} // namespace boundary

// ------------------------------------------------------------------
// Function signature: x64 Microsoft ABI
// rcx = a0 (this / hash map container)
// rdx = a1 (output parameter - pointer to pointer where result is stored)
// r8  = a2 (key string - source data for lookup/insert)
// returns: rax = a1 (the output pointer, same as rdx)
// The function finds or inserts a key in the hash map and stores the
// node pointer at *a1. Returns a1.
extern "C" void* sub_e878010(void* a0_container, void* a1_output, void* a2_key);

} // namespace native
