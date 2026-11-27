#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Layouts for sub_67c7020 [0x67c7020,0x67c713f), Minecraft 1.26.62.01.
// The function walks an MSVC std::map-style red-black tree with 0x30-byte nodes
// and a one-byte key. 0x0555555555555555 == 2^64 / 0x30 is the _Mysize max-size
// check, which confirms the node size. Field f<hex> sits at offset 0x<hex>.

#pragma pack(push, 1)
struct sub_67c7020_rcx {          // map object (rcx/rdi)
    void* f0;                      // +0x00 _Myhead   R 0x67c7037
    std::uint64_t f8;              // +0x08 _Mysize   R 0x67c70a4 (8 bytes)
};
#pragma pack(pop)

#pragma pack(push, 1)
struct sub_67c7020_rdx {          // tree node (rdx/r12/rbx)
    void* f0;                      // +0x00 _Left
    void* f8;                      // +0x08 _Parent          R 0x67c703a
    void* f10;                     // +0x10 _Right
    std::uint8_t f18;              // +0x18 _Color
    std::uint8_t f19;              // +0x19 _Isnil           R 0x67c7040,0x67c7079,0x67c7087
    std::uint8_t pad0x1a[0x2];
    std::uint8_t f1c;              // +0x1c key byte         R 0x67c7063,0x67c7091
    std::uint8_t pad0x1d[0x3];
    std::uint64_t f20;             // +0x20 mapped value     W 0x67c70d6
    std::uint32_t f28;             // +0x28 mapped value     W 0x67c70de
    std::uint8_t pad0x2c[0x4];
};
#pragma pack(pop)

#pragma pack(push, 1)
struct sub_67c7020_r15 {          // head node (r15)
    void* f0;                      // +0x00 _Left
    void* f8;                      // +0x08 _Parent          R 0x67c703a
    void* f10;                     // +0x10 _Right
    std::uint8_t f18;              // +0x18 _Color
    std::uint8_t f19;              // +0x19 _Isnil           R 0x67c704c,0x67c7087
    std::uint8_t pad0x1a[0x2];
    std::uint8_t f1c;              // +0x1c key byte         R 0x67c7091
    std::uint8_t pad0x1d[0x3];
    std::uint64_t f20;
    std::uint32_t f28;
    std::uint8_t pad0x2c[0x4];
};
#pragma pack(pop)

#pragma pack(push, 1)
struct sub_67c7020_r8 {           // key source (r8)
    std::uint8_t f0;               // +0x00 key byte         R 0x67c7054,0x67c708d,0x67c70cf
};
#pragma pack(pop)

#pragma pack(push, 1)
struct sub_67c7020_rax {          // freshly allocated node (rax/rbx)
    void* f0;                      // +0x00 _Left            W 0x67c70e5
    void* f8;                      // +0x08 _Parent          W 0x67c70e8
    void* f10;                     // +0x10 _Right           W 0x67c70ec
    std::uint8_t f18;              // +0x18 _Color           W 0x67c70f0
    std::uint8_t f19;              // +0x19 _Isnil           W 0x67c70f0
    std::uint8_t pad0x1a[0x2];
    std::uint8_t f1c;              // +0x1c key byte         W 0x67c70d3
    std::uint8_t pad0x1d[0x3];
    std::uint64_t f20;             // +0x20 mapped value     W 0x67c70d6
    std::uint32_t f28;             // +0x28 mapped value     W 0x67c70de
    std::uint8_t pad0x2c[0x4];
};
#pragma pack(pop)

#pragma pack(push, 1)
struct sub_67c7020_rsp {          // stack hint passed to the tree insert helper
    std::uint8_t pad0x00[0x20];
    void* f20;                     // +0x20 insertion parent W 0x67c70f6
    std::uint32_t f28;             // +0x28 left-insert flag W 0x67c70fb
    std::uint8_t pad0x2c[0x4];
};
#pragma pack(pop)

#pragma pack(push, 1)
struct sub_67c7020_rsi {          // result pair written through rsi (a1)
    void* f0;                      // +0x00 node/iterator    W 0x67c7111
    std::uint8_t f8;               // +0x08 inserted flag    W 0x67c7114
    std::uint8_t pad0x09[0x7];
};
#pragma pack(pop)

static_assert(offsetof(sub_67c7020_rcx, f0) == 0x0, "sub_0x67c7020 rcx+0x0 field");
static_assert(offsetof(sub_67c7020_rcx, f8) == 0x8, "sub_0x67c7020 rcx+0x8 field");
static_assert(sizeof(sub_67c7020_rcx) >= 0x9, "sub_0x67c7020 rcx sizeof lower bound");

static_assert(offsetof(sub_67c7020_rdx, f0) == 0x0, "sub_0x67c7020 rdx+0x0 field");
static_assert(offsetof(sub_67c7020_rdx, f8) == 0x8, "sub_0x67c7020 rdx+0x8 field");
static_assert(offsetof(sub_67c7020_rdx, f10) == 0x10, "sub_0x67c7020 rdx+0x10 field");
static_assert(offsetof(sub_67c7020_rdx, f18) == 0x18, "sub_0x67c7020 rdx+0x18 field");
static_assert(offsetof(sub_67c7020_rdx, f19) == 0x19, "sub_0x67c7020 rdx+0x19 field");
static_assert(offsetof(sub_67c7020_rdx, f1c) == 0x1c, "sub_0x67c7020 rdx+0x1c field");
static_assert(offsetof(sub_67c7020_rdx, f20) == 0x20, "sub_0x67c7020 rdx+0x20 field");
static_assert(offsetof(sub_67c7020_rdx, f28) == 0x28, "sub_0x67c7020 rdx+0x28 field");
static_assert(sizeof(sub_67c7020_rdx) >= 0x1d, "sub_0x67c7020 rdx sizeof lower bound");

static_assert(offsetof(sub_67c7020_r15, f0) == 0x0, "sub_0x67c7020 r15+0x0 field");
static_assert(offsetof(sub_67c7020_r15, f8) == 0x8, "sub_0x67c7020 r15+0x8 field");
static_assert(offsetof(sub_67c7020_r15, f10) == 0x10, "sub_0x67c7020 r15+0x10 field");
static_assert(offsetof(sub_67c7020_r15, f18) == 0x18, "sub_0x67c7020 r15+0x18 field");
static_assert(offsetof(sub_67c7020_r15, f19) == 0x19, "sub_0x67c7020 r15+0x19 field");
static_assert(offsetof(sub_67c7020_r15, f1c) == 0x1c, "sub_0x67c7020 r15+0x1c field");
static_assert(offsetof(sub_67c7020_r15, f20) == 0x20, "sub_0x67c7020 r15+0x20 field");
static_assert(offsetof(sub_67c7020_r15, f28) == 0x28, "sub_0x67c7020 r15+0x28 field");
static_assert(sizeof(sub_67c7020_r15) >= 0x1d, "sub_0x67c7020 r15 sizeof lower bound");

static_assert(offsetof(sub_67c7020_r8, f0) == 0x0, "sub_0x67c7020 r8+0x0 field");
static_assert(sizeof(sub_67c7020_r8) >= 0x1, "sub_0x67c7020 r8 sizeof lower bound");

static_assert(offsetof(sub_67c7020_rax, f0) == 0x0, "sub_0x67c7020 rax+0x0 field");
static_assert(offsetof(sub_67c7020_rax, f8) == 0x8, "sub_0x67c7020 rax+0x8 field");
static_assert(offsetof(sub_67c7020_rax, f10) == 0x10, "sub_0x67c7020 rax+0x10 field");
static_assert(offsetof(sub_67c7020_rax, f18) == 0x18, "sub_0x67c7020 rax+0x18 field");
static_assert(offsetof(sub_67c7020_rax, f19) == 0x19, "sub_0x67c7020 rax+0x19 field");
static_assert(offsetof(sub_67c7020_rax, f1c) == 0x1c, "sub_0x67c7020 rax+0x1c field");
static_assert(offsetof(sub_67c7020_rax, f20) == 0x20, "sub_0x67c7020 rax+0x20 field");
static_assert(offsetof(sub_67c7020_rax, f28) == 0x28, "sub_0x67c7020 rax+0x28 field");
static_assert(sizeof(sub_67c7020_rax) >= 0x2c, "sub_0x67c7020 rax sizeof lower bound");

static_assert(offsetof(sub_67c7020_rsp, f20) == 0x20, "sub_0x67c7020 rsp+0x20 field");
static_assert(offsetof(sub_67c7020_rsp, f28) == 0x28, "sub_0x67c7020 rsp+0x28 field");
static_assert(sizeof(sub_67c7020_rsp) >= 0x29, "sub_0x67c7020 rsp sizeof lower bound");

static_assert(offsetof(sub_67c7020_rsi, f0) == 0x0, "sub_0x67c7020 rsi+0x0 field");
static_assert(offsetof(sub_67c7020_rsi, f8) == 0x8, "sub_0x67c7020 rsi+0x8 field");
static_assert(sizeof(sub_67c7020_rsi) >= 0x9, "sub_0x67c7020 rsi sizeof lower bound");

// x64 Microsoft ABI: rcx = map object, rdx = result pair (also returned in rax),
// r8 = pointer to the one-byte key. Register roles from 0x67c702e..0x67c7037.
sub_67c7020_rsi* sub_67c7020(sub_67c7020_rcx* a0, sub_67c7020_rsi* a1,
                             const std::uint8_t* a2);

} // namespace native::helpers
