#pragma once
#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

#include <cstddef>
#include <cstdint>

// sub_bc2f1d0: bgfx field move / take (size 0x1ec, 1.26.62.01).
// Layout constants and static asserts for the lifted body.
// The argument object's real C++ type name is unknown; Bc2f1d0Object is a layout
// reconstruction built from the observed field accesses of 0xbc2f1d0..0xbc2f3bc.
// Every offset the function touches is asserted below (offsets are a reconstruction of
// the field meanings; per-field tags live in the dossier).

namespace native {

struct Bc2f1d0Object {
    std::uint64_t f00;                    // +0x00  qword move a1->a0
    std::uint64_t f08;                    // +0x08  qword move a1->a0; src zeroed
    std::uint64_t f10;                    // +0x10  qword move a1->a0
    std::uint64_t f18;                    // +0x18  dst zeroed (16-byte store with f20)
    std::uint64_t f20;                    // +0x20  dst zeroed (16-byte store with f18)
    std::uint64_t f28;                    // +0x28  dst = 0
    std::uint8_t  f30;                    // +0x30  byte move a1->a0
    std::uint8_t  pad31[7];               // +0x31..0x37
    std::uint64_t f38;                    // +0x38  16-byte move a1->a0 (with f40)
    std::uint64_t f40;                    // +0x40  src zeroed
    std::uint64_t f48;                    // +0x48  16-byte move a1->a0 (with f50); src zeroed
    std::uint64_t f50;                    // +0x50  src zeroed
    std::uint64_t f58;                    // +0x58  qword move a1->a0
    void*         f60;                    // +0x60  switch-dependent move (type byte at f70)
    void*         f68;                    // +0x68  switch-dependent move (+refcount inc, type 3)
    std::uint8_t  f70;                    // +0x70  type byte (0..3 switch; dst=0xFF first)
    std::uint8_t  pad71[7];               // +0x71..0x77
    std::uint64_t f78;                    // +0x78  16-byte move a1->a0 (with f80)
    std::uint64_t f80;                    // +0x80
    std::uint64_t f88;                    // +0x88  qword move a1->a0
    std::uint64_t f90;                    // +0x90  qword move a1->a0
    std::uint8_t  f98[0x78];              // +0x98..0x10F sub-object moved by sub_e869ff0
    void*         f110;                   // +0x110 pointer take: a0 = a1, a1 = nullptr
    std::uint8_t  f118[0x78];             // +0x118..0x18F float block moved by sub_5669770
    std::uint8_t  pad190[0xAC];           // +0x190..0x23B
    std::uint64_t f23c;                   // +0x23C 16-byte move a1->a0 (with f244)
    std::uint64_t f244;                   // +0x244
    std::uint32_t f24c;                   // +0x24C dword move a1->a0
    std::uint8_t  f250;                   // +0x250 byte move a1->a0
    std::uint8_t  pad251[3];              // +0x251..0x253
    float         f254;                   // +0x254 float move a1->a0
    float         f258;                   // +0x258 float move a1->a0
    float         f25c;                   // +0x25C float move a1->a0
    float         f260;                   // +0x260 float move a1->a0
    std::uint64_t f264;                   // +0x264 16-byte move a1->a0 (with f26c)
    std::uint64_t f26c;                   // +0x26C
    std::uint64_t f274;                   // +0x274 16-byte move a1->a0 (with f27c)
    std::uint64_t f27c;                   // +0x27C
    std::uint64_t f283;                   // +0x283 16-byte move a1->a0 (with f28b)
    std::uint64_t f28b;                   // +0x28B
    std::uint8_t  pad293;                 // +0x293
    std::uint16_t f294;                   // +0x294 word move a1->a0
};

static_assert(offsetof(Bc2f1d0Object, f00) == 0x00, "bc2f1d0: f00 offset");
static_assert(offsetof(Bc2f1d0Object, f08) == 0x08, "bc2f1d0: f08 offset");
static_assert(offsetof(Bc2f1d0Object, f10) == 0x10, "bc2f1d0: f10 offset");
static_assert(offsetof(Bc2f1d0Object, f18) == 0x18, "bc2f1d0: f18 offset");
static_assert(offsetof(Bc2f1d0Object, f20) == 0x20, "bc2f1d0: f20 offset");
static_assert(offsetof(Bc2f1d0Object, f28) == 0x28, "bc2f1d0: f28 offset");
static_assert(offsetof(Bc2f1d0Object, f30) == 0x30, "bc2f1d0: f30 offset");
static_assert(offsetof(Bc2f1d0Object, f38) == 0x38, "bc2f1d0: f38 offset");
static_assert(offsetof(Bc2f1d0Object, f40) == 0x40, "bc2f1d0: f40 offset");
static_assert(offsetof(Bc2f1d0Object, f48) == 0x48, "bc2f1d0: f48 offset");
static_assert(offsetof(Bc2f1d0Object, f50) == 0x50, "bc2f1d0: f50 offset");
static_assert(offsetof(Bc2f1d0Object, f58) == 0x58, "bc2f1d0: f58 offset");
static_assert(offsetof(Bc2f1d0Object, f60) == 0x60, "bc2f1d0: f60 offset");
static_assert(offsetof(Bc2f1d0Object, f68) == 0x68, "bc2f1d0: f68 offset");
static_assert(offsetof(Bc2f1d0Object, f70) == 0x70, "bc2f1d0: f70 offset");
static_assert(offsetof(Bc2f1d0Object, f78) == 0x78, "bc2f1d0: f78 offset");
static_assert(offsetof(Bc2f1d0Object, f80) == 0x80, "bc2f1d0: f80 offset");
static_assert(offsetof(Bc2f1d0Object, f88) == 0x88, "bc2f1d0: f88 offset");
static_assert(offsetof(Bc2f1d0Object, f90) == 0x90, "bc2f1d0: f90 offset");
static_assert(offsetof(Bc2f1d0Object, f98) == 0x98, "bc2f1d0: f98 offset");
static_assert(offsetof(Bc2f1d0Object, f110) == 0x110, "bc2f1d0: f110 offset");
static_assert(offsetof(Bc2f1d0Object, f118) == 0x118, "bc2f1d0: f118 offset");
static_assert(offsetof(Bc2f1d0Object, f23c) == 0x23C, "bc2f1d0: f23c offset");
static_assert(offsetof(Bc2f1d0Object, f244) == 0x244, "bc2f1d0: f244 offset");
static_assert(offsetof(Bc2f1d0Object, f24c) == 0x24C, "bc2f1d0: f24c offset");
static_assert(offsetof(Bc2f1d0Object, f250) == 0x250, "bc2f1d0: f250 offset");
static_assert(offsetof(Bc2f1d0Object, f254) == 0x254, "bc2f1d0: f254 offset");
static_assert(offsetof(Bc2f1d0Object, f258) == 0x258, "bc2f1d0: f258 offset");
static_assert(offsetof(Bc2f1d0Object, f25c) == 0x25C, "bc2f1d0: f25c offset");
static_assert(offsetof(Bc2f1d0Object, f260) == 0x260, "bc2f1d0: f260 offset");
static_assert(offsetof(Bc2f1d0Object, f264) == 0x264, "bc2f1d0: f264 offset");
static_assert(offsetof(Bc2f1d0Object, f26c) == 0x26C, "bc2f1d0: f26c offset");
static_assert(offsetof(Bc2f1d0Object, f274) == 0x274, "bc2f1d0: f274 offset");
static_assert(offsetof(Bc2f1d0Object, f27c) == 0x27C, "bc2f1d0: f27c offset");
static_assert(offsetof(Bc2f1d0Object, f283) == 0x283, "bc2f1d0: f283 offset");
static_assert(offsetof(Bc2f1d0Object, f28b) == 0x28B, "bc2f1d0: f28b offset");
static_assert(offsetof(Bc2f1d0Object, f294) == 0x294, "bc2f1d0: f294 offset");
static_assert(sizeof(Bc2f1d0Object) >= 0x296, "bc2f1d0: object covers the last touched byte");

// Lifted body of sub 0xbc2f1d0 (bgfx field move / take, size 0x1ec).
// Exact x64 Microsoft ABI signature: rcx = a0 (destination), rdx = a1 (source), returns void.
void SubBc2f1d0_lifted(Bc2f1d0Object* a0, Bc2f1d0Object* a1);

// Lift callees of 0xbc2f1d0 (class lift in docs/data/native_boundary.tsv rows 0xe869ff0 and
// 0x5669770). Defined by their own lift units; called from SubBc2f1d0_lifted as plain C++
// calls with the same arguments and order:
//   0xbc2f2db  call 0xE869FF0  rcx=&a0->f98[0], rdx=&a1->f98[0]
//   0xbc2f30c  call 0x5669770  rcx=&a0->f118[0], rdx=&a1->f118[0]
void sub_e869ff0(void* dst, void* src);
void sub_5669770(void* dst, void* src);

} // namespace native
