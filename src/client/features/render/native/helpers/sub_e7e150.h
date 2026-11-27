#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed views of every memory location touched by sub_e7e150 (0xe7e150..0xe7e25d).
// Offsets, widths, signedness and pointer-ness come from the instruction operands.
// Each struct is #pragma pack(1) so offsetof() equals the observed displacement; a
// real object may carry compiler alignment padding, so sizeof() is a lower bound.

// Argument a0 (rcx). The +0x000 pointer is also the vtable pointer of the
// polymorphic objects reached through a0+0x98 (read at 0xe7e180) and through the
// handle slot at [rbp-0x20] (read at 0xe7e1a8).
#pragma pack(push, 1)
struct sub_e7e150_rcx {
    void* vtable;                                   // +0x000: R 0xe7e180, 0xe7e1a8 (vtable pointer)
    std::uint8_t pad0x08[0x54];                     // +0x008..+0x05b (not accessed)
    float fallbackValue;                            // +0x05c: R 0xe7e248 (returned when no value is found)
    std::uint8_t pad0x60[0x38];                     // +0x060..+0x097 (not accessed)
    void* provider;                                 // +0x098: R 0xe7e179 (queried object)
    std::uint8_t pad0xa0[0xc10];                    // +0x0a0..+0x0caf (not accessed)
    std::uint8_t enabled;                           // +0x0cb0: R 0xe7e16c (must be 1 to take the query path)
};
#pragma pack(pop)

// Object returned by sub_88bb50 and the vtable arrays indexed through the queried
// object: +0x108 is slot 33 of the provider vtable (0xe7e183), +0x008 is slot 1 of
// the inner vtable (0xe7e1ab), +0x018 is the float result (0xe7e1c4).
#pragma pack(push, 1)
struct sub_e7e150_rax {
    void* f0;                                       // +0x000: R 0xe7e19f (byte), R 0xe7e1e6, 0xe7e222
    void* f8;                                       // +0x008: R 0xe7e1ab, 0xe7e1fb, 0xe7e237
    std::uint8_t pad0x10[0x8];                      // +0x010..+0x017 (not accessed)
    float value;                                    // +0x018: R 0xe7e1c4 (result float)
    std::uint8_t pad0x1c[0xec];                     // +0x01c..+0x107 (not accessed)
    void* f108;                                     // +0x108: R 0xe7e183 (vtable slot 33)
};
#pragma pack(pop)

// Reference-counted control block released at the end of the query path.
#pragma pack(push, 1)
struct sub_e7e150_rdi {
    void* vtable;                                   // +0x000: R 0xe7e1e3, 0xe7e1f8, 0xe7e21f, 0xe7e234
    std::uint32_t strongCount;                      // +0x008: RW 0xe7e1dd, 0xe7e219 (lock dec)
    std::uint32_t weakCount;                        // +0x00c: RW 0xe7e1f2, 0xe7e22e (lock dec)
};
#pragma pack(pop)

// Frame-base pointer produced by lea rbp,[rsp+0x50].
#pragma pack(push, 1)
struct sub_e7e150_rsp {
    std::uint8_t pad0x00[0x50];                     // +0x000..+0x04f (not accessed)
    std::uint8_t frameAnchor;                       // +0x050: R 0xe7e158 (lea rbp,[rsp+0x50])
};
#pragma pack(pop)

// Out parameter at [rbp-0x30], filled by the provider's vtable slot 33 and then
// cleared: 16 bytes at 0xe7e1d4 plus [rbp-0x20] at 0xe7e20c.
#pragma pack(push, 1)
struct sub_e7e150_Handle {
    void* f0;                                       // [rbp-0x30]: R 0xe7e194, zeroed 0xe7e1d4
    void* f8;                                       // [rbp-0x28]: R 0xe7e1d0, 0xe7e208, zeroed 0xe7e1d4
    void* f10;                                      // [rbp-0x20]: R 0xe7e1a4, zeroed 0xe7e20c
};
#pragma pack(pop)

static_assert(offsetof(sub_e7e150_rcx, vtable) == 0x0, "sub_0xe7e150 rcx+0x0 field");
static_assert(offsetof(sub_e7e150_rcx, fallbackValue) == 0x5c, "sub_0xe7e150 rcx+0x5c field");
static_assert(offsetof(sub_e7e150_rcx, provider) == 0x98, "sub_0xe7e150 rcx+0x98 field");
static_assert(offsetof(sub_e7e150_rcx, enabled) == 0xcb0, "sub_0xe7e150 rcx+0xcb0 field");
static_assert(sizeof(sub_e7e150_rcx) >= 0xcb1, "sub_0xe7e150 rcx sizeof lower bound");

static_assert(offsetof(sub_e7e150_rax, f0) == 0x0, "sub_0xe7e150 rax+0x0 field");
static_assert(offsetof(sub_e7e150_rax, f8) == 0x8, "sub_0xe7e150 rax+0x8 field");
static_assert(offsetof(sub_e7e150_rax, value) == 0x18, "sub_0xe7e150 rax+0x18 field");
static_assert(offsetof(sub_e7e150_rax, f108) == 0x108, "sub_0xe7e150 rax+0x108 field");
static_assert(sizeof(sub_e7e150_rax) >= 0x110, "sub_0xe7e150 rax sizeof lower bound");

static_assert(offsetof(sub_e7e150_rdi, vtable) == 0x0, "sub_0xe7e150 rdi+0x0 field");
static_assert(offsetof(sub_e7e150_rdi, strongCount) == 0x8, "sub_0xe7e150 rdi+0x8 field");
static_assert(offsetof(sub_e7e150_rdi, weakCount) == 0xc, "sub_0xe7e150 rdi+0xc field");
static_assert(sizeof(sub_e7e150_rdi) >= 0x10, "sub_0xe7e150 rdi sizeof lower bound");

static_assert(offsetof(sub_e7e150_rsp, frameAnchor) == 0x50, "sub_0xe7e150 rsp+0x50 field");
static_assert(sizeof(sub_e7e150_rsp) >= 0x51, "sub_0xe7e150 rsp sizeof lower bound");

static_assert(offsetof(sub_e7e150_Handle, f0) == 0x0, "sub_0xe7e150 handle+0x0 field");
static_assert(offsetof(sub_e7e150_Handle, f8) == 0x8, "sub_0xe7e150 handle+0x8 field");
static_assert(offsetof(sub_e7e150_Handle, f10) == 0x10, "sub_0xe7e150 handle+0x10 field");
static_assert(sizeof(sub_e7e150_Handle) >= 0x18, "sub_0xe7e150 handle sizeof lower bound");

// x64 Microsoft ABI: argument in rcx, float result in xmm0.
// 0xe7e150  push rbp; 0xe7e151  push rsi; 0xe7e152  push rdi; 0xe7e153  push rbx
float sub_e7e150(void* self);

} // namespace native::helpers
