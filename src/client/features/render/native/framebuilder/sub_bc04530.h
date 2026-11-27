#pragma once
#include <cstddef>
#include <cstdint>
#include <atomic>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_bc04530 (0xbc04530, size 0xc4, 1.26.62.01, "pass task render-thread body (class D)").
//
// Layout mirrors of the structs used by the function, with static_asserts for every offset
// the function reads or writes. All offsets [V] from the disassembly of [0xbc04530, 0xbc045f4).
//
// The function (exact x64 Microsoft ABI): RCX = a0 (PassBodyD*, class D render-thread body),
// RDX = a1 (u64, stored at *(a0+0x3B0)+0x18 then cleared to 0). Returns void (ends in ret).
//
// Callees:
//   - sub_eea6040 (boundary/vendor, via data slot 0xF99FFA0, docs/data/native_boundary.tsv):
//     body is `jmp rax`; caller leaves target funcptr in RAX (out-of-ABI), RCX = 1st arg,
//     RDX = 2nd arg; the target's `ret` returns to the instruction after the call.
//     Called 3x: 0xbc0459e (target = obj2->vtable[0x10], RCX = obj2, RDX = &saved_3a8),
//     0xbc045c9 (target = old_ref->vtable[0] destructor, RCX = old_ref),
//     0xbc045df (target = old_ref->vtable[8] deleter, RCX = old_ref).
//   - sub_eec59e0 (lift set, already lifted): noreturn, tail-jumps to std::_Xbad_function_call.
//     Called 1x: 0xbc045ed (when a0+0x70 == 0), RCX not set (no args).

static constexpr std::size_t kPassBodyDField0x70 = 0x70;
static constexpr std::size_t kPassBodyDField0x3A8 = 0x3A8;
static constexpr std::size_t kPassBodyDField0x3B0 = 0x3B0;
static constexpr std::size_t kPassBodyDField0x3B8 = 0x3B8;
static constexpr std::size_t kPassBodyDSize = 0x3C0;

static constexpr std::size_t kPassObjField0x18 = 0x18;
static constexpr std::size_t kPassObjSize = 0x20;

static constexpr std::size_t kRefCountedVtable = 0x0;
static constexpr std::size_t kRefCountedStrong = 0x8;
static constexpr std::size_t kRefCountedWeak = 0xC;
static constexpr std::size_t kRefCountedSize = 0x10;

struct RefCounted {
    void* vtable;                          // +0x0: R vtable (slot 0 = destructor, slot 8 = deleter) [V]
    std::atomic<std::uint32_t> strong;     // +0x8: R/W lock inc (addref at 0xbc04564) / lock dec (release at 0xbc045ba) [V]
    std::atomic<std::uint32_t> weak;       // +0xC: R/W lock dec (weak release at 0xbc045cf) [V]
};                                         // size 0x10

struct PassObj {
    std::uint8_t pad_0x0[0x18];
    std::uint64_t field_0x18;              // +0x18: W = a1 (RDX) at 0xbc04582, W = 0 at 0xbc045a9 [V]
};                                         // size 0x20

struct PassBodyD {
    std::uint8_t pad_0x0[0x70];
    void* field_0x70;                      // +0x70: R callback object (vtable) at 0xbc04586 [V]
    std::uint8_t pad_0x78[0x3A8 - 0x78];
    std::uint64_t field_0x3A8;             // +0x3A8: R at 0xbc04546, saved to local, passed by ref to callback [V]
    void* field_0x3B0;                     // +0x3B0: R obj1 (PassObj*) at 0xbc04573 [V]
    RefCounted* field_0x3B8;               // +0x3B8: R old_ref, addref'd at 0xbc04564, released at 0xbc045ba/0xbc045cf/0xbc045df [V]
};                                         // size 0x3C0

static_assert(offsetof(RefCounted, vtable) == kRefCountedVtable,
              "sub_bc04530: RefCounted+0x0 is the vtable pointer, read at 0xbc045c0/0xbc045c3 and 0xbc045d5/0xbc045d8");
static_assert(offsetof(RefCounted, strong) == kRefCountedStrong,
              "sub_bc04530: RefCounted+0x8 is lock inc at 0xbc04564 and lock dec at 0xbc045ba");
static_assert(offsetof(RefCounted, weak) == kRefCountedWeak,
              "sub_bc04530: RefCounted+0xC is lock dec at 0xbc045cf");
static_assert(sizeof(RefCounted) == kRefCountedSize,
              "sub_bc04530: RefCounted size");
static_assert(offsetof(PassObj, field_0x18) == kPassObjField0x18,
              "sub_bc04530: PassObj+0x18 written at 0xbc04582 and 0xbc045a9");
static_assert(sizeof(PassObj) == kPassObjSize,
              "sub_bc04530: PassObj size");
static_assert(offsetof(PassBodyD, field_0x70) == kPassBodyDField0x70,
              "sub_bc04530: PassBodyD+0x70 read at 0xbc04586");
static_assert(offsetof(PassBodyD, field_0x3A8) == kPassBodyDField0x3A8,
              "sub_bc04530: PassBodyD+0x3A8 read at 0xbc04546");
static_assert(offsetof(PassBodyD, field_0x3B0) == kPassBodyDField0x3B0,
              "sub_bc04530: PassBodyD+0x3B0 read at 0xbc04573");
static_assert(offsetof(PassBodyD, field_0x3B8) == kPassBodyDField0x3B8,
              "sub_bc04530: PassBodyD+0x3B8 read at 0xbc04558 and 0xbc04568");
static_assert(sizeof(PassBodyD) == kPassBodyDSize,
              "sub_bc04530: PassBodyD size");

namespace native {
namespace boundary {

// sub_eea6040 (0xeea6040, boundary/vendor via data slot 0xF99FFA0).
// Body is `jmp rax`: the caller must leave the target function pointer in RAX (out-of-ABI
// argument), RCX = 1st argument (this/object), RDX = 2nd argument (context). The target's
// `ret` returns to the instruction after `call qword ptr [0xF99FFA0]`.
// Resolved from Sigs.json at install; see native_boundary.tsv row 0xeea6040.
using eea6040_fn = void (*)(void* rcx, void* rdx);
extern eea6040_fn g_eea6040_thunk;

} // namespace boundary

// sub_eec59e0 (0xeec59e0, lift set): tail-jumps to std::_Xbad_function_call via data slot
// 0xF9A7310; noreturn. Forward-declared here (defined in sub_eec59e0.h/.cpp).
void sub_eec59e0(void);

// sub_bc04530 (0xbc04530, size 0xc4, 1.26.62.01): exact x64 Microsoft ABI mirror of the
// original. RCX = a0 (PassBodyD*), RDX = a1 (u64). Returns void.
void sub_bc04530(PassBodyD* a0, std::uint64_t a1);

} // namespace native