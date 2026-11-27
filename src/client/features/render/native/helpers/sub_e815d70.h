#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout(s) for sub_e815d70, reverse-engineered from the disassembly
// of [0xe815d70, 0xe815e9b), Minecraft Windows 1.26.62.01. Offsets and widths
// come straight from the instruction operands; field names and meanings are
// inferred from the access pattern (guarded paged-heap element lookup).
//
// One struct per base register that is dereferenced (rcx/rdi self, rax heap
// object, rcx page cursor). Each struct is packed (#pragma pack(1)) so every
// declared field sits exactly at its observed offset and offsetof() matches it.
// The real object may have compiler-inserted alignment padding, so sizeof is a
// lower bound, not an exact size.

#pragma pack(push, 1)
// Base register rcx/rdi: the context object (RendererContextD3D12).
// +0xBDE178 is the base of the inline 0xB8-byte record array (index * 0xB8).
// +0xC96178 is a pointer to the paged-heap object.
// +0xC96190 is a guard-flag byte.
struct sub_e815d70_ctx {
    std::uint8_t pad0x00[0xBDE178];   // +0x00000000..+0xBDE177
    std::uint8_t fBDE178;             // +0xBDE178: inline record array base byte
    std::uint8_t pad0xBDE179[0xB7FFF]; // +0xBDE179..+0xC96177
    void* fC96178;                    // +0xC96178: paged-heap object pointer
    std::uint8_t pad0xC96180[0x10];   // +0xC96180..+0xC9618F
    std::uint8_t fC96190;             // +0xC96190: guard-flag byte
};
#pragma pack(pop)

// Base register rax = fC96178 target: paged-heap object; +0x00 is the first page.
#pragma pack(push, 1)
struct sub_e815d70_heap {
    void* f0;   // +0x00: first page pointer
};
#pragma pack(pop)

// Base register rcx (reused as a page cursor): a paged-heap page; +0xB8000 links on.
#pragma pack(push, 1)
struct sub_e815d70_page {
    std::uint8_t pad0x00[0xB8000];  // +0x00000000..+0xB7FFF page data
    void* fB8000;                   // +0xB8000: next page pointer
};
#pragma pack(pop)

static_assert(offsetof(sub_e815d70_ctx, fBDE178) == 0xBDE178, "sub_0xe815d70 ctx fBDE178 offset");
static_assert(offsetof(sub_e815d70_ctx, fC96178) == 0xC96178, "sub_0xe815d70 ctx fC96178 offset");
static_assert(offsetof(sub_e815d70_ctx, fC96190) == 0xC96190, "sub_0xe815d70 ctx fC96190 offset");
static_assert(sizeof(sub_e815d70_ctx) >= 0xC96191, "sub_0xe815d70 ctx sizeof lower bound");

static_assert(offsetof(sub_e815d70_heap, f0) == 0x00, "sub_0xe815d70 heap f0 offset");
static_assert(sizeof(sub_e815d70_heap) >= 0x08, "sub_0xe815d70 heap sizeof lower bound");

static_assert(offsetof(sub_e815d70_page, fB8000) == 0xB8000, "sub_0xe815d70 page fB8000 offset");
static_assert(sizeof(sub_e815d70_page) >= 0xB8008, "sub_0xe815d70 page sizeof lower bound");

// x64 Microsoft ABI: RCX = self (context), DX/EDX = element index (uint16).
// Returns the uint64 stored at the computed guarded-heap address.
uintptr_t sub_e815d70(void* self, std::uint16_t index);

} // namespace native::helpers
