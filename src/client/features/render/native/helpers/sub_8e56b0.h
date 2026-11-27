#pragma once
#include <cstddef>
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_e935700 (lift set, declared in sub_e935700.h) is forward-declared here
// rather than including sub_e935700.h, to avoid pulling that unit's header
// into this translation unit. Signature matches sub_e935700.h exactly.
namespace native {
void* sub_e935700(void* a0);
} // namespace native

// sub_8e56b0 (0x8e56b0, size 0x78, 1.26.62.01): recursive child/sibling walk
// over a node list headed at argument 1 (RCX), with refcounted-object teardown.
// Every field below is only READ by the function [V]:
//   +0x00  void* next        R  mov rsi,[rsi]                    (0x8e56ef)
//   +0x10  void* child       R  mov rcx,[rsi+0x10]               (0x8e56e6)
//   +0x19  u8   flag         R  cmp byte ptr [rcx+0x19],0        (0x8e56b7)
//                               cmp byte ptr [rsi+0x19],0        (0x8e56dd)
//   +0x30  void* obj         R  mov rbx,[rdi+0x30]               (0x8e56f2)
// Writes [V]: *(obj+0x8) lock dec (0x8e56fb); *(obj+0xC) lock dec (0x8e5710);
// the node itself is released by native::sub_e935700 (0x8e56d8), which calls
// the boundary thunk sub_eea6040 via data slot 0xF99FFA0.
// Callees [V]: sub_8e56b0 (self-recursion, 0x8e56ea); sub_e935700 (lift set,
// 0x8e56d8, declared in sub_e935700.h); sub_eea6040 (boundary/vendor via data
// slot 0xF99FFA0, 0x8e570a and 0x8e5720 - virtual destructor/delete through
// the 1-byte `jmp rax` thunk at 0xeea6040; RAX holds the target funcptr,
// RCX = obj, out-of-ABI).
static constexpr std::size_t kNodeOffsetNext   = 0x00;
static constexpr std::size_t kNodeOffsetChild  = 0x10;
static constexpr std::size_t kNodeOffsetFlag   = 0x19;
static constexpr std::size_t kNodeOffsetObj    = 0x30;
static constexpr std::size_t kObjOffsetVfptr   = 0x00;
static constexpr std::size_t kObjOffsetRefcount= 0x08;
static constexpr std::size_t kObjOffsetCountC  = 0x0C;

struct sub_8e56b0_node {
    void* next;                    // +0x00 [R] next sibling
    std::uint8_t pad0x08[0x10 - 0x08];
    void* child;                   // +0x10 [R] first child
    std::uint8_t pad0x18[0x19 - 0x18];
    std::uint8_t flag;             // +0x19 [R] stop-iteration flag
    std::uint8_t pad0x1a[0x30 - 0x1a];
    void* obj;                     // +0x30 [R] refcounted object owned by the node
};
struct sub_8e56b0_obj {
    void* vfptr;                   // +0x00 [R] vfptr[0]=destructor, vfptr[1]=operator delete
    std::uint32_t refcount;        // +0x08 [R/W] lock dec
    std::uint32_t count0xC;        // +0x0C [R/W] lock dec
};

struct sub_8e56b0Layout {
    static_assert(offsetof(sub_8e56b0_node, next) == kNodeOffsetNext,
                  "sub_8e56b0_node: next at +0x00");
    static_assert(offsetof(sub_8e56b0_node, child) == kNodeOffsetChild,
                  "sub_8e56b0_node: child at +0x10");
    static_assert(offsetof(sub_8e56b0_node, flag) == kNodeOffsetFlag,
                  "sub_8e56b0_node: flag at +0x19");
    static_assert(offsetof(sub_8e56b0_node, obj) == kNodeOffsetObj,
                  "sub_8e56b0_node: obj at +0x30");
    static_assert(offsetof(sub_8e56b0_obj, vfptr) == kObjOffsetVfptr,
                  "sub_8e56b0_obj: vfptr at +0x00");
    static_assert(offsetof(sub_8e56b0_obj, refcount) == kObjOffsetRefcount,
                  "sub_8e56b0_obj: refcount at +0x08");
    static_assert(offsetof(sub_8e56b0_obj, count0xC) == kObjOffsetCountC,
                  "sub_8e56b0_obj: count0xC at +0x0C");
    static_assert(sizeof(void*) == 8, "sub_8e56b0: x64 pointer-sized arguments (Microsoft x64 ABI)");
};

namespace native {
namespace boundary {

// sub_eea6040 (0xeea6040, boundary/vendor): 1-byte thunk `jmp rax` reached by
// `call qword ptr [0xF99FFA0]`; RAX holds the target function pointer
// (out-of-ABI argument), RCX = the object. See native_boundary.tsv row 0xeea6040.
using eea6040_fn = void(*)(void* rcx, void* rdx);
extern eea6040_fn g_eea6040_thunk;   // resolved from Sigs.json at install

} // namespace boundary

// sub_8e56b0(void* node) -> void
//   x64 Microsoft ABI: node in RCX; the return value is never meaningfully set
//   on any path, so the return type is void [V].
void sub_8e56b0(void* node);

} // namespace native
