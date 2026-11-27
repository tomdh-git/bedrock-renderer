#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout(s) for sub_4e3b020, reverse-engineered from the disassembly of
// [0x4e3b020, 0x4e3b13e), Minecraft Windows 1.26.62.01. Offsets, widths and signedness
// come straight from the instruction operands; the field names follow the role the
// instructions give them (five released control blocks and their vtable/refcounts).
//
// The five released members are MSVC _Ref_count_base-compatible control blocks:
// +0x00 vptr, +0x08 strong count, +0x0C weak count. Each release does
// `lock dec [p+8]`; when that reaches zero it calls vtable[0](p), then `lock dec [p+0xC]`;
// when that reaches zero it calls vtable[1](p) (vptr re-read after the first call).

#pragma pack(push, 1)
struct sub_4e3b020_refcounted;

struct sub_4e3b020_vtable {
    std::uintptr_t (*destroy)(sub_4e3b020_refcounted*); // +0x00: slot 0, loaded at 0x4e3b038/0x4e3b03b, 0x4e3b06c/0x4e3b06f, 0x4e3b0a0/0x4e3b0a3, 0x4e3b0d4/0x4e3b0d7, 0x4e3b108/0x4e3b10b
    std::uintptr_t (*dealloc)(sub_4e3b020_refcounted*); // +0x08: slot 1, loaded at 0x4e3b04d/0x4e3b050, 0x4e3b081/0x4e3b084, 0x4e3b0b5/0x4e3b0b8, 0x4e3b0e9/0x4e3b0ec, 0x4e3b11d/0x4e3b120
};

struct sub_4e3b020_refcounted {
    sub_4e3b020_vtable* vtable; // +0x00: vptr (0x4e3b038:R, 0x4e3b04d:R, 0x4e3b06c:R, 0x4e3b081:R, 0x4e3b0a0:R, 0x4e3b0b5:R, 0x4e3b0d4:R, 0x4e3b0e9:R, 0x4e3b108:R, 0x4e3b11d:R)
    std::uint32_t strong;       // +0x08: strong count, `lock dec dword ptr [p+8]` (0x4e3b032:RW, 0x4e3b066:RW, 0x4e3b09a:RW, 0x4e3b0ce:RW, 0x4e3b102:RW)
    std::uint32_t weak;         // +0x0C: weak count, `lock dec dword ptr [p+0xC]` (0x4e3b047:RW, 0x4e3b07b:RW, 0x4e3b0af:RW, 0x4e3b0e3:RW, 0x4e3b117:RW)
};

struct sub_4e3b020_self {
    std::uint8_t pad0x00[0x8];               // +0x00..+0x07: no access in this function
    sub_4e3b020_refcounted* ref0x08;         // +0x08: released last (0x4e3b0f9:R)
    std::uint8_t pad0x10[0x8];               // +0x10..+0x17: no access in this function
    sub_4e3b020_refcounted* ref0x18;         // +0x18: released fourth (0x4e3b0c5:R)
    std::uint8_t pad0x20[0x10];              // +0x20..+0x2f: no access in this function
    sub_4e3b020_refcounted* ref0x30;         // +0x30: released third (0x4e3b091:R)
    std::uint8_t pad0x38[0x10];              // +0x38..+0x47: no access in this function
    sub_4e3b020_refcounted* ref0x48;         // +0x48: released second (0x4e3b05d:R)
    std::uint8_t pad0x50[0x8];               // +0x50..+0x57: no access in this function
    sub_4e3b020_refcounted* ref0x58;         // +0x58: released first (0x4e3b029:R)
};
#pragma pack(pop)

static_assert(offsetof(sub_4e3b020_vtable, destroy) == 0x0, "sub_0x4e3b020 vtable+0x0 slot");
static_assert(offsetof(sub_4e3b020_vtable, dealloc) == 0x8, "sub_0x4e3b020 vtable+0x8 slot");
static_assert(sizeof(sub_4e3b020_vtable) == 0x10, "sub_0x4e3b020 vtable size");

static_assert(offsetof(sub_4e3b020_refcounted, vtable) == 0x0, "sub_0x4e3b020 refcounted+0x0 field");
static_assert(offsetof(sub_4e3b020_refcounted, strong) == 0x8, "sub_0x4e3b020 refcounted+0x8 field");
static_assert(offsetof(sub_4e3b020_refcounted, weak) == 0xc, "sub_0x4e3b020 refcounted+0xc field");
static_assert(sizeof(sub_4e3b020_refcounted) == 0x10, "sub_0x4e3b020 refcounted size");

static_assert(offsetof(sub_4e3b020_self, ref0x08) == 0x8, "sub_0x4e3b020 self+0x8 field");
static_assert(offsetof(sub_4e3b020_self, ref0x18) == 0x18, "sub_0x4e3b020 self+0x18 field");
static_assert(offsetof(sub_4e3b020_self, ref0x30) == 0x30, "sub_0x4e3b020 self+0x30 field");
static_assert(offsetof(sub_4e3b020_self, ref0x48) == 0x48, "sub_0x4e3b020 self+0x48 field");
static_assert(offsetof(sub_4e3b020_self, ref0x58) == 0x58, "sub_0x4e3b020 self+0x58 field");
static_assert(sizeof(sub_4e3b020_self) == 0x60, "sub_0x4e3b020 self size");

// Signature (x64 Microsoft ABI): RCX = self; RAX = value left by the last virtual call.
// 0x4e3b020  push rsi; 0x4e3b021  push rdi; 0x4e3b022  sub rsp,0x28; 0x4e3b026  mov rsi,rcx
// C linkage: sub_4e69270.h declares this same entry point as `extern "C" uintptr_t
// sub_4e3b020(sub_4e69270_state* next)` and tail-jumps to it at 0x4e69355.
extern "C" std::uintptr_t sub_4e3b020(void* self);

} // namespace native::helpers
