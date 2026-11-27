#pragma once

#include <cstddef>
#include <cstdint>

#include "client/features/render/native/RewriteRegistry.h"
#include "client/features/render/native/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_bc5e400: VV frame-graph builder (size 0x2f1, 1.26.62.01).

// Grow-and-insert for 16-byte refcounted elements; every layout offset below is taken from the

// disassembly of [0xbc5e400, 0xbc5e6f1) [V]:

//

//   struct Bc5e400Array { Elem* begin @+0x00; Elem* end @+0x08; Elem* cap_end @+0x10; }   sizeof 0x18

//   struct Bc5e400Elem  { void* field0 @+0x00; void* field1 @+0x08; }                   sizeof 0x10

//   refcounted object   (reached via element.field1): u32 strong @+0x08, u32 weak @+0x0C

//

// x64 Microsoft ABI: rcx = self (Bc5e400Array*), rdx = position (Elem* into the old array),

// r8 = element (const Elem* to insert), return = Elem* iterator to the inserted element (rax).

// r9 at entry is never read by the original.

//

// Calls out of lifted code [V]:

//   0xbc5e4a5 / 0xbc5e4d6  call qword ptr [0xF99FFA0]  allocator entry through data slot [0xF99FFA0]

//                            (loaded at call time: rcx = allocator interface from [0x1233E1A8], rdx = size)

//   0xbc5e643 / 0xbc5e65a  call qword ptr [0xF99FFA0]  same slot: destroy object / free control block (rcx = object)

//   0xbc5e4e7 / 0xbc5e6c5  call 0x9BC830               boundary alloc (native_boundary.tsv line 149)

//   0xbc5e6d2              call 0x75740                boundary stl  (native_boundary.tsv line 4)

//   0xbc5e691              call 0xE935700              class lift  (native_boundary.tsv line 505): declared below, called directly

//   0xbc5e6ea              call qword ptr [0xF9A8C78]  dead fail path through data slot [0xF9A8C78] (rcx=rdx=r8=r9=0)

namespace native {

struct Bc5e400Elem {
    void* field0;  // +0x00

    void* field1;  // +0x08  pointer to a refcounted object

};
static_assert(offsetof(Bc5e400Elem, field0) == 0x00, "bc5e400: elem field0 at +0x0");
static_assert(offsetof(Bc5e400Elem, field1) == 0x08, "bc5e400: elem field1 at +0x8");
static_assert(sizeof(Bc5e400Elem) == 0x10, "bc5e400: elem size 0x10");

struct Bc5e400RefCnt {
    std::uint32_t strong;  // refcounted object +0x00, reached as element.field1 + 8

    std::uint32_t weak;    // refcounted object +0x04, reached as element.field1 + 0xC

};
static_assert(offsetof(Bc5e400RefCnt, strong) == 0x00, "bc5e400: refcnt strong at +0x0");
static_assert(offsetof(Bc5e400RefCnt, weak) == 0x04, "bc5e400: refcnt weak at +0x4");
static_assert(sizeof(Bc5e400RefCnt) == 0x08, "bc5e400: refcnt size 0x8");

struct Bc5e400Array {
    Bc5e400Elem* begin;   // +0x00

    Bc5e400Elem* end;     // +0x08

    Bc5e400Elem* cap_end; // +0x10

};
static_assert(offsetof(Bc5e400Array, begin) == 0x00, "bc5e400: array begin at +0x0");
static_assert(offsetof(Bc5e400Array, end) == 0x08, "bc5e400: array end at +0x8");
static_assert(offsetof(Bc5e400Array, cap_end) == 0x10, "bc5e400: array cap_end at +0x10");
static_assert(sizeof(Bc5e400Array) == 0x18, "bc5e400: array size 0x18");

// The function rewrites the array header (begin/end/cap_end at +0x0/+0x8/+0x10) [V].

native::Footprint sub_bc5e400_footprint(Bc5e400Array* self, void*, const void*);

// 0xbc5e691  call 0xE935700  deallocates the old buffer base (rcx = base). Class lift per

// docs/data/native_boundary.tsv line 505: forward-declared here and called directly, not a Boundary.

void sub_e935700(void* base);

// Elem* sub_bc5e400(Bc5e400Array* self /*rcx*/, Bc5e400Elem* position /*rdx*/,

//                   const Bc5e400Elem* element /*r8*/);  return = iterator to inserted element (rax).

Bc5e400Elem* sub_bc5e400(Bc5e400Array* self, Bc5e400Elem* position, const Bc5e400Elem* element);

} // namespace native

