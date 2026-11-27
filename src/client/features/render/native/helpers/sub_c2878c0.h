#pragma once
#include <cstddef>
#include <cstdint>

#include "client/features/render/native/helpers/sub_c28a920.h"

namespace native::helpers {

// Typed state layout(s) for sub_c2878c0, reverse-engineered from the disassembly
// of [0xc2878c0, 0xc2879d0). [proven] offsets/widths come straight from the
// instruction operands; field NAMES/MEANINGS are lifted decisions.

// rcx-derivable state object passed as first argument (this). rcx = argument 1
// (a0). Field accesses: f0, f8 (via *f0), f10, f20, f28, f74, fa0.
#pragma pack(push, 1)
struct sub_c2878c0_a0 {
    void* f0;                                    // +0x00: void* R/W
    std::uint8_t pad0x08[0x8];                   // +0x08..+0x0f
    void* f10;                                   // +0x10: void* R/W
    std::uint8_t pad0x18[0x8];                   // +0x18..+0x1f
    std::uint64_t f20;                           // +0x20: std::uint64_t R
    std::uint8_t f28;                            // +0x28: std::uint8_t R
    std::uint8_t pad0x29[0x4b];                  // +0x29..+0x73
    std::uint32_t f74;                           // +0x74: std::uint32_t R/W
    std::uint8_t pad0x78[0x28];                  // +0x78..+0x9f
    std::uint8_t fa0;                            // +0xa0: std::uint8_t R (referenced via lea rcx,[rsi+0xA0])
};
#pragma pack(pop)

// State pointed to by f0 of a0 (rax states). Accesses: f0 (R/W), f8 (R).
#pragma pack(push, 1)
struct sub_c2878c0_rax {
    void* f0;   // +0x00: void* R/W
    void* f8;   // +0x08: void* R
};
#pragma pack(pop)

// Buffer state written at rsi+0x10 (rdi state). Accesses: f0 (16-byte zero), f10 (QWORD zero).
#pragma pack(push, 1)
struct sub_c2878c0_buf {
    std::uint64_t f0[2];   // +0x00: zeroed 16 bytes
    std::uint64_t f10;     // +0x10: zeroed QWORD
};
#pragma pack(pop)

// Stack scratch state (rsp base). Accesses: rsp+0x20 (W), rsp+0x30 (R).
#pragma pack(push, 1)
struct sub_c2878c0_rsp {
    std::uint8_t pad0x00[0x20];
    std::uint64_t f20;   // +0x20: written 0 before the indirect call
    std::uint8_t pad0x28[0x8];
    std::uint8_t f30;    // +0x30: read via lea rbp,[rsp+0x30]
};
#pragma pack(pop)

static_assert(offsetof(sub_c2878c0_a0, f0) == 0x0, "sub_0xc2878c0 a0+0x0 field");
static_assert(offsetof(sub_c2878c0_a0, f10) == 0x10, "sub_0xc2878c0 a0+0x10 field");
static_assert(offsetof(sub_c2878c0_a0, f20) == 0x20, "sub_0xc2878c0 a0+0x20 field");
static_assert(offsetof(sub_c2878c0_a0, f28) == 0x28, "sub_0xc2878c0 a0+0x28 field");
static_assert(offsetof(sub_c2878c0_a0, f74) == 0x74, "sub_0xc2878c0 a0+0x74 field");
static_assert(offsetof(sub_c2878c0_a0, fa0) == 0xa0, "sub_0xc2878c0 a0+0xa0 field");
static_assert(sizeof(sub_c2878c0_a0) >= 0xa1, "sub_0xc2878c0 a0 sizeof lower bound");

static_assert(offsetof(sub_c2878c0_rax, f0) == 0x0, "sub_0xc2878c0 rax+0x0 field");
static_assert(offsetof(sub_c2878c0_rax, f8) == 0x8, "sub_0xc2878c0 rax+0x8 field");
static_assert(sizeof(sub_c2878c0_rax) >= 0x10, "sub_0xc2878c0 rax sizeof lower bound");

static_assert(offsetof(sub_c2878c0_buf, f0) == 0x0, "sub_0xc2878c0 buf+0x0 field");
static_assert(offsetof(sub_c2878c0_buf, f10) == 0x10, "sub_0xc2878c0 buf+0x10 field");
static_assert(sizeof(sub_c2878c0_buf) >= 0x18, "sub_0xc2878c0 buf sizeof lower bound");

static_assert(offsetof(sub_c2878c0_rsp, f20) == 0x20, "sub_0xc2878c0 rsp+0x20 field");
static_assert(offsetof(sub_c2878c0_rsp, f30) == 0x30, "sub_0xc2878c0 rsp+0x30 field");
static_assert(sizeof(sub_c2878c0_rsp) >= 0x31, "sub_0xc2878c0 rsp sizeof lower bound");

// Callee signatures lifted into this translation unit via their lifted headers.
uintptr_t sub_c2878c0(void* self);

} // namespace native::helpers
