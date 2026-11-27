#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout(s) for sub_4e00c00, reverse-engineered from the disassembly
// of [0x4e00c00, 0x4e00d32), Minecraft Windows 1.26.62.01.
// One struct per base register that is dereferenced.
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it.

// a1 / rdx: object with target pointer (+0x0) and next pointer (+0x8)
#pragma pack(push, 1)
struct sub_4e00c00_rdx {
    void* target;   // +0x00: void* R  (0x4e00c20, 0x4e00c5a, 0x4e00cde, 0x4e00d0d)
    void* next;     // +0x08: void* R  (0x4e00cbc)
};
#pragma pack(pop)

// a2 / r8: object with source pointer (+0x0), refcounted pointer (+0x8), slot array (+0x10)
#pragma pack(push, 1)
struct sub_4e00c00_r8 {
    void* source;     // +0x00: void* R  (0x4e00c23, 0x4e00c8c, 0x4e00c9b, 0x4e00ce1)
    void* refcounted; // +0x08: void* R  (0x4e00c3d, 0x4e00c8f, 0x4e00cfb)
    void* slots[2];   // +0x10: void*[2] R  (0x4e00c30, 0x4e00c45, 0x4e00cd2, 0x4e00cee, 0x4e00d03)
};
#pragma pack(pop)

// rcx: refcounted object with vtable (+0x0), strong refcount (+0x8), weak refcount (+0xc)
#pragma pack(push, 1)
struct sub_4e00c00_rcx {
    void* vtable;                   // +0x00: void* R  (0x4e00c64, 0x4e00cb9)
    std::uint32_t strong_refcount;  // +0x08: std::uint32_t RW  (0x4e00c39, 0x4e00cf7)
    std::uint32_t weak_refcount;    // +0x0c: std::uint32_t RW  (0x4e00cb3)
    std::uint8_t pad0x10[0x8];      // +0x10..+0x17 padding (no observed access)
    std::uint8_t type_tag;          // +0x18: std::uint8_t W  (0x4e00d10)
};
#pragma pack(pop)

// rax: allocation result with two slot pairs (+0x0 and +0x10)
#pragma pack(push, 1)
struct sub_4e00c00_rax {
    void* slots0[2];  // +0x00: void*[2] W  (0x4e00c26, 0x4e00c86, 0x4e00ca7, 0x4e00ce4)
    void* slots1[2];  // +0x10: void*[2] W  (0x4e00c49, 0x4e00c82, 0x4e00cd6, 0x4e00d07)
};
#pragma pack(pop)

// rbx: single byte target (+0x0)
#pragma pack(push, 1)
struct sub_4e00c00_rbx {
    std::uint8_t byte0;  // +0x00: std::uint8_t W  (0x4e00c89)
};
#pragma pack(pop)

static_assert(offsetof(sub_4e00c00_rcx, vtable) == 0x0, "sub_4e00c00 rcx+0x0 field");
static_assert(offsetof(sub_4e00c00_rcx, strong_refcount) == 0x8, "sub_4e00c00 rcx+0x8 field");
static_assert(offsetof(sub_4e00c00_rcx, weak_refcount) == 0xc, "sub_4e00c00 rcx+0xc field");
static_assert(offsetof(sub_4e00c00_rcx, type_tag) == 0x18, "sub_4e00c00 rcx+0x18 field");
static_assert(sizeof(sub_4e00c00_rcx) >= 0x19, "sub_4e00c00 rcx sizeof lower bound");

static_assert(offsetof(sub_4e00c00_rdx, target) == 0x0, "sub_4e00c00 rdx+0x0 field");
static_assert(offsetof(sub_4e00c00_rdx, next) == 0x8, "sub_4e00c00 rdx+0x8 field");
static_assert(sizeof(sub_4e00c00_rdx) >= 0x10, "sub_4e00c00 rdx sizeof lower bound");

static_assert(offsetof(sub_4e00c00_r8, source) == 0x0, "sub_4e00c00 r8+0x0 field");
static_assert(offsetof(sub_4e00c00_r8, refcounted) == 0x8, "sub_4e00c00 r8+0x8 field");
static_assert(offsetof(sub_4e00c00_r8, slots) == 0x10, "sub_4e00c00 r8+0x10 field");
static_assert(sizeof(sub_4e00c00_r8) >= 0x20, "sub_4e00c00 r8 sizeof lower bound");

static_assert(offsetof(sub_4e00c00_rax, slots0) == 0x0, "sub_4e00c00 rax+0x0 field");
static_assert(offsetof(sub_4e00c00_rax, slots1) == 0x10, "sub_4e00c00 rax+0x10 field");
static_assert(sizeof(sub_4e00c00_rax) >= 0x20, "sub_4e00c00 rax sizeof lower bound");

static_assert(offsetof(sub_4e00c00_rbx, byte0) == 0x0, "sub_4e00c00 rbx+0x0 field");
static_assert(sizeof(sub_4e00c00_rbx) >= 0x1, "sub_4e00c00 rbx sizeof lower bound");

// Callee declarations
extern "C" uintptr_t sub_eea6040(void* a1, uint64_t a2);
extern "C" uintptr_t sub_9bc830(uint32_t size);

// Signature (x64 Microsoft ABI): self is used as jump-table index; a1/a2 are pointer args.
// 0x4e00c00  push r14; 0x4e00c02  push rsi; 0x4e00c03  push rdi; 0x4e00c04  push rbx
uintptr_t sub_4e00c00(uintptr_t self, void* a1, void* a2);

} // namespace native::helpers
