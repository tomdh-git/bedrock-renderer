#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// State layout for the object reached through RCX (saved into RSI). Offsets and widths
// are the instruction operands of [0xa784c0, 0xa785cf). The struct is packed so every
// declared field sits at its observed offset; real compiler padding may make the true
// object larger, so sizeof checks are lower bounds except for the node, whose 0x28-byte
// allocation size is passed explicitly at 0xa784f7.
#pragma pack(push, 1)
struct sub_a784c0_rcx {
    std::uint8_t pad0x00[0x38];      // +0x00..+0x37 not accessed here
    void* factory;                   // +0x38 R (0xa78526): object whose vtable[2] fills the node
    std::uint8_t listHead;           // +0x40 address only (0xa7856b lea rax,[rsi+0x40])
    std::uint8_t pad0x41[0x7];       // +0x41..+0x47
    void* listTail;                  // +0x48 R/W (0xa7856f R, 0xa7857d W)
    std::uint8_t mutex;              // +0x50 address only (0xa7854f lea rbx,[rsi+0x50])
    std::uint8_t pad0x51[0x4b];      // +0x51..+0x9b
    std::uint32_t count;             // +0x9c R/W (0xa7855f R, 0xa785ba W)
    std::uint8_t tlsSlot;            // +0xa0 address only (0xa784cc lea rbx,[rcx+0xA0])
};
#pragma pack(pop)

// The 0x28-byte node allocated through the allocator vtable[1] (size in EDX at 0xa784f7).
// Its pointer is moved to RDI at 0xa78502; the payload returned to the caller begins at
// +0x10 (add rax,0x10 at 0xa78515 / return path).
#pragma pack(push, 1)
struct sub_a784c0_rax {
    void* next;                      // +0x00 W (0xa7850e self, 0xa78577 list head)
    void* prev;                      // +0x08 W (0xa78511 self, 0xa78573 old tail)
    std::uint8_t value[0x18];        // +0x10 first qword zeroed (0xa78519), filled through vtable[2]
};
#pragma pack(pop)

// RBX aliases the TLS slot first (0xa784cc) and the mutex afterwards (0xa7854f); it is
// used only as an address, never dereferenced by this function. The 8-byte slot keeps the
// link width seen through RCX at the store 0xa7857a.
#pragma pack(push, 1)
struct sub_a784c0_rbx {
    void* f0;                        // +0x00 link alias (0xa7857a W)
};
#pragma pack(pop)

// Stack temporary holding the payload address (mov [rsp+0x20],rax at 0xa78521); its
// address is passed in RDX to the factory vtable[2] call at 0xa78539/0xa7853e.
#pragma pack(push, 1)
struct sub_a784c0_rsp {
    std::uint8_t pad0x00[0x20];      // +0x00..+0x1f
    void* f20;                       // +0x20 R/W (0xa78521 W, 0xa78539 address taken)
};
#pragma pack(pop)

static_assert(offsetof(sub_a784c0_rcx, factory) == 0x38, "sub_0xa784c0 rcx+0x38 field");
static_assert(offsetof(sub_a784c0_rcx, listHead) == 0x40, "sub_0xa784c0 rcx+0x40 field");
static_assert(offsetof(sub_a784c0_rcx, listTail) == 0x48, "sub_0xa784c0 rcx+0x48 field");
static_assert(offsetof(sub_a784c0_rcx, mutex) == 0x50, "sub_0xa784c0 rcx+0x50 field");
static_assert(offsetof(sub_a784c0_rcx, count) == 0x9c, "sub_0xa784c0 rcx+0x9c field");
static_assert(offsetof(sub_a784c0_rcx, tlsSlot) == 0xa0, "sub_0xa784c0 rcx+0xa0 field");
static_assert(sizeof(sub_a784c0_rcx) >= 0xa1, "sub_0xa784c0 rcx sizeof lower bound");

static_assert(offsetof(sub_a784c0_rax, next) == 0x0, "sub_0xa784c0 rax+0x0 field");
static_assert(offsetof(sub_a784c0_rax, prev) == 0x8, "sub_0xa784c0 rax+0x8 field");
static_assert(offsetof(sub_a784c0_rax, value) == 0x10, "sub_0xa784c0 rax+0x10 field");
static_assert(sizeof(sub_a784c0_rax) == 0x28, "sub_0xa784c0 node allocation size");

static_assert(offsetof(sub_a784c0_rbx, f0) == 0x0, "sub_0xa784c0 rbx+0x0 field");
static_assert(sizeof(sub_a784c0_rbx) >= 0x8, "sub_0xa784c0 rbx sizeof lower bound");

static_assert(offsetof(sub_a784c0_rsp, f20) == 0x20, "sub_0xa784c0 rsp+0x20 field");
static_assert(sizeof(sub_a784c0_rsp) >= 0x28, "sub_0xa784c0 rsp sizeof lower bound");

// Microsoft x64 ABI: one pointer argument in RCX, pointer result in RAX. Both return
// paths hand back the address of the node payload at +0x10 (0xa784e0, 0xa78589).
void* sub_a784c0(void* self);

} // namespace native::helpers
