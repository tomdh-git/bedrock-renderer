#pragma once
#include <cstddef>
#include <cstdint>

#include "client/features/render/native/helpers/sub_c28a920.h"

namespace native::helpers {

// Typed state layout(s) for sub_c2879f0, reverse-engineered from the disassembly
// of [0xc2879f0, 0xc287b10), Minecraft Windows 1.26.62.01. [proven] offsets/widths/signedness
// come straight from the instruction operands; field NAMES and MEANINGS are lifted decisions.
// One struct per base register that is dereferenced (rcx/rdx/r8/r9 this/a1/a2 and
// any other register used as a memory base). Field f<hex> is at offset 0x<hex>.

// Struct for base register rcx (the first argument / this pointer).
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size.
#pragma pack(push, 1)
struct sub_c2879f0_rcx {
    void* f0;                    // +0x00: pointer to the list head; read at 0xc287a93 and 0xc287ac5
    std::uint8_t pad0x08[0x8];   // +0x08..+0x0f padding (no observed access)
    void* f10;                   // +0x10: buffer begin; read at 0xc287a47, zeroed at 0xc287a88
    std::uint8_t pad0x18[0x8];   // +0x18..+0x1f (also covered by the 16-byte movups at 0xc287a88)
    std::uint64_t f20;           // +0x20: buffer end; read at 0xc287a50, zeroed at 0xc287a8b
    std::uint8_t f28;            // +0x28: first byte of the C11 mutex; address passed to _Mtx_lock/_Mtx_unlock
    std::uint8_t pad0x29[0x4b];  // +0x29..+0x73 padding (no observed access)
    std::uint32_t f74;           // +0x74: state word; compared at 0xc287a1b, written at 0xc287ae4
    std::uint8_t pad0x78[0x28];  // +0x78..+0x9f padding (no observed access)
    std::uint8_t fa0;            // +0xa0: first byte of the entry array passed to sub_c28a920 at 0xc287a3b
    std::uint8_t pad0xa1[0xdf];  // +0xa1..+0x17f padding (no observed access)
    std::uint64_t f180;          // +0x180: zeroed at 0xc287a30
};
#pragma pack(pop)

// Struct for base register rax: the object reached through self->f0.
// f0 is the first list node (or a node's next pointer); f8 points at the
// next-pointer slot of the last node and is written through at 0xc287a9a.
#pragma pack(push, 1)
struct sub_c2879f0_rax {
    void* f0;    // +0x00: first node / node next pointer; read at 0xc287aa1 and 0xc287ab0
    void** f8;   // +0x08: pointer to the tail's next-pointer slot; dereferenced at 0xc287a9a
};
#pragma pack(pop)

// Struct for the zeroed buffer descriptor at self+0x10 (rdi in the listing).
#pragma pack(push, 1)
struct sub_c2879f0_rdi {
    std::uint64_t f0[2];   // +0x00: 16 bytes zeroed by movups at 0xc287a88
    std::uint64_t f10;     // +0x10: zeroed at 0xc287a8b
};
#pragma pack(pop)

// Struct for base register rsp: the invalid-parameter tail's stack scratch.
#pragma pack(push, 1)
struct sub_c2879f0_rsp {
    std::uint8_t pad0x00[0x20];  // +0x00..+0x1f padding (no observed access)
    std::uint64_t f20;           // +0x20: 5th argument slot zeroed at 0xc287af6
    std::uint8_t pad0x28[0x8];   // +0x28..+0x2f padding (no observed access)
    std::uint8_t f30;            // +0x30: frame base read via lea rbp,[rsp+0x30] at 0xc2879f7
};
#pragma pack(pop)

static_assert(offsetof(sub_c2879f0_rcx, f0) == 0x0, "sub_0xc2879f0 rcx+0x0 field");
static_assert(offsetof(sub_c2879f0_rcx, f10) == 0x10, "sub_0xc2879f0 rcx+0x10 field");
static_assert(offsetof(sub_c2879f0_rcx, f20) == 0x20, "sub_0xc2879f0 rcx+0x20 field");
static_assert(offsetof(sub_c2879f0_rcx, f28) == 0x28, "sub_0xc2879f0 rcx+0x28 field");
static_assert(offsetof(sub_c2879f0_rcx, f74) == 0x74, "sub_0xc2879f0 rcx+0x74 field");
static_assert(offsetof(sub_c2879f0_rcx, fa0) == 0xa0, "sub_0xc2879f0 rcx+0xa0 field");
static_assert(offsetof(sub_c2879f0_rcx, f180) == 0x180, "sub_0xc2879f0 rcx+0x180 field");
static_assert(sizeof(sub_c2879f0_rcx) >= 0x188, "sub_0xc2879f0 rcx sizeof lower bound");

static_assert(offsetof(sub_c2879f0_rax, f0) == 0x0, "sub_0xc2879f0 rax+0x0 field");
static_assert(offsetof(sub_c2879f0_rax, f8) == 0x8, "sub_0xc2879f0 rax+0x8 field");
static_assert(sizeof(sub_c2879f0_rax) >= 0x10, "sub_0xc2879f0 rax sizeof lower bound");

static_assert(offsetof(sub_c2879f0_rdi, f0) == 0x0, "sub_0xc2879f0 rdi+0x0 field");
static_assert(offsetof(sub_c2879f0_rdi, f10) == 0x10, "sub_0xc2879f0 rdi+0x10 field");
static_assert(sizeof(sub_c2879f0_rdi) >= 0x18, "sub_0xc2879f0 rdi sizeof lower bound");

static_assert(offsetof(sub_c2879f0_rsp, f20) == 0x20, "sub_0xc2879f0 rsp+0x20 field");
static_assert(offsetof(sub_c2879f0_rsp, f30) == 0x30, "sub_0xc2879f0 rsp+0x30 field");
static_assert(sizeof(sub_c2879f0_rsp) >= 0x31, "sub_0xc2879f0 rsp sizeof lower bound");

// Signature (x64 Microsoft ABI): self arrives in RCX; the only returning path is the
// tail jump to sub_e935700 at 0xc287ad4, whose RAX result is returned unchanged.
uintptr_t sub_c2879f0(void* self);

} // namespace native::helpers
