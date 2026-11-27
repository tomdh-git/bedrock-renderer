#pragma once
// LIFT 0x3af4e0 size 0x83 1.26.62.01 sub_3af4e0
// Signature from disassembly: RCX=arg1, RDX=arg2, R8=arg3, R9=arg4, returns RAX from indirect call

#include <cstdint>

#include "sub_3b23c0.h"   // lift callee: std::uint64_t* sub_3b23c0(void)

namespace native {

// Layout constants for stack frame (verified against disassembly)
constexpr uint32_t kSub3af4e0_StackFrameSize = 0x40;
constexpr uint32_t kSub3af4e0_CookieSlotOffset = 0x38;
constexpr uint32_t kSub3af4e0_RbxSaveOffset = 0x30;
constexpr uint32_t kSub3af4e0_ShadowSpaceOffset = 0x20;
constexpr uint32_t kSub3af4e0_Arg3SaveOffset = 0x70;
constexpr uint32_t kSub3af4e0_Arg4SaveOffset = 0x78;

static_assert(kSub3af4e0_StackFrameSize == 0x40, "sub_3af4e0 stack frame size");
static_assert(kSub3af4e0_CookieSlotOffset == 0x38, "sub_3af4e0 cookie slot offset");
static_assert(kSub3af4e0_RbxSaveOffset == 0x30, "sub_3af4e0 rbx save offset");
static_assert(kSub3af4e0_Arg3SaveOffset == 0x70, "sub_3af4e0 arg3 save offset");
static_assert(kSub3af4e0_Arg4SaveOffset == 0x78, "sub_3af4e0 arg4 save offset");

// Stack cookie global (MSVC __security_cookie at 0x1230A0C0)
extern "C" uintptr_t __security_cookie;

// Boundary: 0xe951550 crt/__report_gsfailure (native_boundary.tsv)
// Called on stack cookie mismatch, noreturn
__declspec(noreturn) extern "C" void __report_gsfailure(uintptr_t);

// Function pointer type for indirect call through data slot 0xF9A8B30
// Called with: RCX=*sub_3b23c0(), RDX=arg1, R8=-1, R9=arg2
using slot_f9a8b30_t = uint64_t (*)(uint64_t, uint64_t, uint64_t, uint64_t);

// Lifted function signature (Microsoft x64 ABI, 4 register args + shadow space)
extern "C" uint64_t sub_3af4e0(uint64_t arg1, uint64_t arg2, uint64_t arg3, uint64_t arg4);

} // namespace native
