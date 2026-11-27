#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Layout of the fields touched by sub_675b350, observed in the disassembly of
// [0x675b350, 0x675b44b), Minecraft Windows 1.26.62.01.
// Offsets and widths are [proven] straight from the instruction operands;
// field names and meanings are reconstructed. One packed struct per
// dereferenced base register. Explicit padding fields keep every observed
// field at its exact offset; sizeof is a lower bound (the real object may
// have more compiler-inserted alignment padding).

// Base = the function argument (rcx/a0, 'self'): [+0x8]=self2, [+0x10]=count,
// [+0x18]=chunk start, [+0x20]=chunk end.
#pragma pack(push, 1)
struct sub_675b350_self {
    std::uint8_t pad0x00[0x8];
    void* self2;          // +0x8  R (0x675b361, 0x675b3e2)
    std::uint64_t count;  // +0x10 R (0x675b3e6, 8-byte)
    void* start;          // +0x18 R (0x675b36e)
    void* end;            // +0x20 R (0x675b372)
};
#pragma pack(pop)

// Base = rdi (chunk pointer): [+0xe8]=buf, [+0xf8]=limit, [+0x100]=flag.
// [+0xe8] and [+0xf8] are also written through r14 = rdi+0xe8.
#pragma pack(push, 1)
struct sub_675b350_chunk {
    std::uint8_t pad0x00[0xe8];
    void* buf;                    // +0xe8 R/W (0x675b3a6 R, 0x675b385 W via r14)
    std::uint8_t pad0xf0[0x8];    // +0xf0..+0xf7 padding (no observed access)
    std::uint64_t limit;          // +0xf8 R/W (0x675b3b5 R, 0x675b389 W via r14+0x10)
    std::uint8_t flag;            // +0x100 R (0x675b39d)
};
#pragma pack(pop)

// Base = r14 (= chunk + 0xe8): [+0x0]=buf, [+0x10]=limit.
#pragma pack(push, 1)
struct sub_675b350_r14 {
    void* buf;                    // +0x0 R/W (0x675b3ad R, 0x675b385 W)
    std::uint8_t pad0x08[0x8];    // +0x08..+0x0f padding (no observed access)
    std::uint64_t limit;          // +0x10 W (0x675b389 W)
};
#pragma pack(pop)

// Base = rsp stack slots: [+0x20]=fail-handler arg area, [+0x30]=xmm6 save.
#pragma pack(push, 1)
struct sub_675b350_rsp {
    std::uint8_t pad0x00[0x20];
    std::uint64_t f20;            // +0x20 W (0x675b431)
    std::uint8_t pad0x28[0x8];    // +0x28..+0x2f padding (no observed access)
    std::uint8_t f30[16];         // +0x30 R/W (0x675b359 W, 0x675b40f R, 0x675b422 R)
};
#pragma pack(pop)

static_assert(offsetof(sub_675b350_self, self2) == 0x8, "sub_675b350 self+0x8 self2 field");
static_assert(offsetof(sub_675b350_self, count) == 0x10, "sub_675b350 self+0x10 count field");
static_assert(offsetof(sub_675b350_self, start) == 0x18, "sub_675b350 self+0x18 start field");
static_assert(offsetof(sub_675b350_self, end) == 0x20, "sub_675b350 self+0x20 end field");
static_assert(sizeof(sub_675b350_self) >= 0x28, "sub_675b350 self sizeof lower bound");

static_assert(offsetof(sub_675b350_chunk, buf) == 0xe8, "sub_675b350 chunk+0xe8 buf field");
static_assert(offsetof(sub_675b350_chunk, limit) == 0xf8, "sub_675b350 chunk+0xf8 limit field");
static_assert(offsetof(sub_675b350_chunk, flag) == 0x100, "sub_675b350 chunk+0x100 flag field");
static_assert(sizeof(sub_675b350_chunk) >= 0x101, "sub_675b350 chunk sizeof lower bound");

static_assert(offsetof(sub_675b350_r14, buf) == 0x0, "sub_675b350 r14+0x0 buf field");
static_assert(offsetof(sub_675b350_r14, limit) == 0x10, "sub_675b350 r14+0x10 limit field");
static_assert(sizeof(sub_675b350_r14) >= 0x18, "sub_675b350 r14 sizeof lower bound");

static_assert(offsetof(sub_675b350_rsp, f20) == 0x20, "sub_675b350 rsp+0x20 f20 field");
static_assert(offsetof(sub_675b350_rsp, f30) == 0x30, "sub_675b350 rsp+0x30 f30 field");
static_assert(sizeof(sub_675b350_rsp) >= 0x40, "sub_675b350 rsp sizeof lower bound");

// [rcx-8] (self2[-8] / buf[-8]) is read at a negative offset and is not
// represented by an offsetof field; it is accessed via pointer arithmetic in
// the lifted body.

// sub_e935700 (0xe935700, lift set, already lifted in helpers/sub_e935700.cpp):
// tail jump to sub_392960; argument forwarded in RCX, result in RAX.
// Called with rcx = buf (0x675b380 path, result ignored) and rcx = rax/self2
// (0x675b40f tail-call path, result returned). Declared via sub_e935700.h.

// Signature: x64 Microsoft ABI, self in RCX, result in RAX.
void* sub_675b350(void* self);

} // namespace native::helpers
