#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout(s) for sub_6758b90, reverse-engineered from the disassembly
// of [0x6758b90, 0x6758c6d), Minecraft Windows 1.26.62.01. Offsets, widths and
// signedness come straight from the instruction operands.

// The object reached through RCX (the `this` argument). The function stores the
// static table address 0xF2BE800 into +0x00 and then reads eight object pointers
// at +0x08..+0x40, passing each one's +0x30 subobject to sub_a784c0. The eight
// pointers are loaded before the first call and consumed in descending offset
// order (0x40, 0x38, 0x30, 0x28, 0x20, 0x18, 0x10, 0x08).
#pragma pack(push, 1)
struct sub_6758b90_rcx {
    void* vtable;                     // +0x00 W (0x6758bb4): address 0xF2BE800
    void* owner08;                    // +0x08 R (0x6758bb7): base of a +0x30 subobject
    void* owner10;                    // +0x10 R (0x6758bbb): base of a +0x30 subobject
    void* owner18;                    // +0x18 R (0x6758bbf): base of a +0x30 subobject
    void* owner20;                    // +0x20 R (0x6758bc3): base of a +0x30 subobject
    void* owner28;                    // +0x28 R (0x6758bc7): base of a +0x30 subobject
    void* owner30;                    // +0x30 R (0x6758bcb): base of a +0x30 subobject
    void* owner38;                    // +0x38 R (0x6758bcf): base of a +0x30 subobject
    void* owner40;                    // +0x40 R (0x6758bd3): base of a +0x30 subobject
};
#pragma pack(pop)

// The payload returned by sub_a784c0 (node + 0x10). This function clears the
// single byte at +0x10 on every returned node.
#pragma pack(push, 1)
struct sub_6758b90_rax {
    std::uint8_t pad0x00[0x10];       // +0x00..+0x0f not accessed here
    std::uint8_t active;              // +0x10 W (0x6758be1, 0x6758bf2, 0x6758c03,
                                      //        0x6758c14, 0x6758c25, 0x6758c36,
                                      //        0x6758c47, 0x6758c58)
};
#pragma pack(pop)

// Frame bookkeeping slots of the prologue; they hold the frame cookie and the
// frame-pointer address and are not part of any callee-visible object.
#pragma pack(push, 1)
struct sub_6758b90_rbp {
    std::uint64_t cookie;             // +0x00 W (0x6758ba5): 0xFFFFFFFFFFFFFFFE
};
#pragma pack(pop)

#pragma pack(push, 1)
struct sub_6758b90_rsp {
    std::uint8_t pad0x00[0x20];       // +0x00..+0x1f
    std::uint8_t frame;               // +0x20 address only (0x6758ba0)
};
#pragma pack(pop)

static_assert(offsetof(sub_6758b90_rcx, vtable) == 0x0, "sub_0x6758b90 rcx+0x0 field");
static_assert(offsetof(sub_6758b90_rcx, owner08) == 0x8, "sub_0x6758b90 rcx+0x8 field");
static_assert(offsetof(sub_6758b90_rcx, owner10) == 0x10, "sub_0x6758b90 rcx+0x10 field");
static_assert(offsetof(sub_6758b90_rcx, owner18) == 0x18, "sub_0x6758b90 rcx+0x18 field");
static_assert(offsetof(sub_6758b90_rcx, owner20) == 0x20, "sub_0x6758b90 rcx+0x20 field");
static_assert(offsetof(sub_6758b90_rcx, owner28) == 0x28, "sub_0x6758b90 rcx+0x28 field");
static_assert(offsetof(sub_6758b90_rcx, owner30) == 0x30, "sub_0x6758b90 rcx+0x30 field");
static_assert(offsetof(sub_6758b90_rcx, owner38) == 0x38, "sub_0x6758b90 rcx+0x38 field");
static_assert(offsetof(sub_6758b90_rcx, owner40) == 0x40, "sub_0x6758b90 rcx+0x40 field");
static_assert(sizeof(sub_6758b90_rcx) >= 0x48, "sub_0x6758b90 rcx sizeof lower bound");

static_assert(offsetof(sub_6758b90_rax, active) == 0x10, "sub_0x6758b90 rax+0x10 field");
static_assert(sizeof(sub_6758b90_rax) >= 0x11, "sub_0x6758b90 rax sizeof lower bound");

static_assert(offsetof(sub_6758b90_rbp, cookie) == 0x0, "sub_0x6758b90 rbp+0x0 field");
static_assert(sizeof(sub_6758b90_rbp) >= 0x8, "sub_0x6758b90 rbp sizeof lower bound");

static_assert(offsetof(sub_6758b90_rsp, frame) == 0x20, "sub_0x6758b90 rsp+0x20 field");
static_assert(sizeof(sub_6758b90_rsp) >= 0x21, "sub_0x6758b90 rsp sizeof lower bound");

// Microsoft x64 ABI: one pointer argument in RCX, result in RAX. RAX holds the
// payload pointer of the last sub_a784c0 call (the one for owner08), which is
// still in the register at the epilogue (0x6758c6c ret).
void* sub_6758b90(sub_6758b90_rcx* self);

} // namespace native::helpers
