#pragma once
#include <cstddef>
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_5e2270 (0x5e2270, size 0x118, 1.26.62.01): destructor-shaped teardown of the
// object passed in RCX (a0 = this). It stores the vtable pointer, frees the two
// small-string-optimised buffers at +0x40 and +0x20, then releases the refcounted
// object held at +0x18. All offsets below are from the disassembly of
// [0x5e2270, 0x5e2388); the types follow the instruction operands.
//
// Object layout (a0):
//   +0x00 void* vfptr        [W] 8-byte store of imageBase()+0xF086408 (0x5e2278/0x5e227f)
//   +0x18 void* object       [R] object whose vtable[2] is queried (0x5e232d)
//   +0x20 void* buffer20     [R/W] char buffer; only byte 0x20 is zeroed on reset
//   +0x30 u64   size20       [W] = 0 on reset
//   +0x38 u64   capacity20   [R/W] = 0xF on reset; heap when >= 0x10
//   +0x40 void* buffer40     [R/W] wchar_t buffer; only word 0x40 is zeroed on reset
//   +0x50 u64   size40       [W] = 0 on reset
//   +0x58 u64   capacity40   [R/W] = 7 on reset; heap when >= 8
//
// Deallocation follows the MSVC container idiom: a heap buffer is freed directly
// when the deallocation size is below 0x1000, otherwise the size-prefixed header at
// [buffer-8] is the allocation base and a header bias of >= 0x20 traps through the
// failfast data slot at 0xF9A8C78.

namespace native {

// sub_e935700 (0xe935700, size 0x5): lift-set callee, a tail jump to sub_392960.
// ABI per sub_e935700.h: single argument in RCX, result in RAX.
void* sub_e935700(void* a0);

namespace boundary {

// sub_eea6040 (0xeea6040) is reached through the data slot at 0xF99FFA0. The
// installed wrapper takes the call target in RDX and transfers it to RAX before
// the thunk's `jmp rax`, so g_eea6040_thunk(rcx, target) performs target(rcx).
// Return type is void* here because the call at 0x5e233d uses RAX afterwards.
using eea6040_fn = void* (*)(void* rcx, void* rdx);
extern eea6040_fn g_eea6040_thunk;   // resolved from Sigs.json at install

} // namespace boundary

} // namespace native

namespace native::helpers {

// The base register RCX is the object (a0) itself.
#pragma pack(push, 1)
struct sub_5e2270_rcx {
    void* vfptr;                 // +0x00 [W] (0x5e227f mov [rcx],rax)
    std::uint8_t pad0x08[0x10];  // +0x08..+0x17 no access
    void* object;                // +0x18 [R] (0x5e232d mov rcx,[rsi+0x18])
    void* buffer20;              // +0x20 [R/W] (0x5e22e8 mov rcx,[rsi+0x20]; 0x5e2329 mov byte ptr [rsi+0x20],0)
    std::uint8_t pad0x28[0x8];   // +0x28..+0x2f no access
    std::uint64_t size20;        // +0x30 [W] (0x5e2319 mov qword ptr [rsi+0x30],0)
    std::uint64_t capacity20;    // +0x38 [R/W] (0x5e22de mov rax,[rsi+0x38]; 0x5e2321 mov qword ptr [rsi+0x38],0xF)
    void* buffer40;              // +0x40 [R/W] (0x5e228c mov rcx,[rsi+0x40]; 0x5e22d8 mov word ptr [rsi+0x40],0)
    std::uint8_t pad0x48[0x8];   // +0x48..+0x4f no access
    std::uint64_t size40;        // +0x50 [W] (0x5e22c8 mov qword ptr [rsi+0x50],0)
    std::uint64_t capacity40;    // +0x58 [R/W] (0x5e2282 mov rax,[rcx+0x58]; 0x5e22d0 mov qword ptr [rsi+0x58],7)
};
#pragma pack(pop)

// Virtual table of the queried object: slot 2 is read at 0x5e2339, slot 0 at
// 0x5e234b (through the vtable pointer loaded at 0x5e2348).
#pragma pack(push, 1)
struct sub_5e2270_rax {
    void* slot0;                 // +0x00 [R] (0x5e2348 mov rcx,[rax]; 0x5e234b mov r8,[rcx])
    std::uint8_t pad0x08[0x8];   // +0x08..+0x0f no access
    void* slot2;                 // +0x10 [R] (0x5e2339 mov rax,[rax+0x10])
};
#pragma pack(pop)

// R8 holds the allocation base read from [buffer-8] (0x5e234b mov r8,[rcx]).
#pragma pack(push, 1)
struct sub_5e2270_r8 {
    void* slot0;                 // +0x00 [R] (0x5e234b mov r8,[rcx])
};
#pragma pack(pop)

// Outgoing stack argument home slot used by the failfast path.
#pragma pack(push, 1)
struct sub_5e2270_rsp {
    std::uint8_t pad0x00[0x20];  // +0x00..+0x1f no access
    std::uint64_t arg4;          // +0x20 [W] (0x5e236e mov qword ptr [rsp+0x20],0)
};
#pragma pack(pop)

struct sub_5e2270Layout {
    static_assert(offsetof(sub_5e2270_rcx, vfptr) == 0x0, "sub_0x5e2270 rcx+0x0 field");
    static_assert(offsetof(sub_5e2270_rcx, object) == 0x18, "sub_0x5e2270 rcx+0x18 field");
    static_assert(offsetof(sub_5e2270_rcx, buffer20) == 0x20, "sub_0x5e2270 rcx+0x20 field");
    static_assert(offsetof(sub_5e2270_rcx, size20) == 0x30, "sub_0x5e2270 rcx+0x30 field");
    static_assert(offsetof(sub_5e2270_rcx, capacity20) == 0x38, "sub_0x5e2270 rcx+0x38 field");
    static_assert(offsetof(sub_5e2270_rcx, buffer40) == 0x40, "sub_0x5e2270 rcx+0x40 field");
    static_assert(offsetof(sub_5e2270_rcx, size40) == 0x50, "sub_0x5e2270 rcx+0x50 field");
    static_assert(offsetof(sub_5e2270_rcx, capacity40) == 0x58, "sub_0x5e2270 rcx+0x58 field");
    static_assert(sizeof(sub_5e2270_rcx) >= 0x60, "sub_0x5e2270 rcx sizeof lower bound");

    static_assert(offsetof(sub_5e2270_rax, slot0) == 0x0, "sub_0x5e2270 rax+0x0 field");
    static_assert(offsetof(sub_5e2270_rax, slot2) == 0x10, "sub_0x5e2270 rax+0x10 field");
    static_assert(sizeof(sub_5e2270_rax) >= 0x18, "sub_0x5e2270 rax sizeof lower bound");

    static_assert(offsetof(sub_5e2270_r8, slot0) == 0x0, "sub_0x5e2270 r8+0x0 field");
    static_assert(sizeof(sub_5e2270_r8) >= 0x8, "sub_0x5e2270 r8 sizeof lower bound");

    static_assert(offsetof(sub_5e2270_rsp, arg4) == 0x20, "sub_0x5e2270 rsp+0x20 field");
    static_assert(sizeof(sub_5e2270_rsp) >= 0x28, "sub_0x5e2270 rsp sizeof lower bound");

    static_assert(sizeof(void*) == 8, "sub_5e2270: x64 pointer-sized arguments (Microsoft x64 ABI)");
    static constexpr std::uintptr_t kVtableRva = 0xF086408;        // lea rax,[0xF086408]
    static constexpr std::uintptr_t kThunkSlotRva = 0xF99FFA0;     // call qword ptr [0xF99FFA0]
    static constexpr std::uintptr_t kFailfastSlotRva = 0xF9A8C78;  // call qword ptr [0xF9A8C78]
};

// sub_5e2270(void* a0) -> void
//   a0 (this) arrives in RCX. Neither epilogue path defines RAX, and the tail call
//   at 0x5e2365 forwards vtable[0](queried, 1); destructor call sites ignore it.
void sub_5e2270(void* a0);

} // namespace native::helpers
