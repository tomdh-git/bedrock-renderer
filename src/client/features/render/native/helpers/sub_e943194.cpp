// LIFT 0xe943194 size 0x7 1.26.62.01 sub_e943194
#include <windows.h>

#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_e943194.h"

namespace native {

// Verbatim instructions of [0xe943194, 0xe94319b) (rdis dis 0xe943194 7):
#if 0
0xe943194  jmp qword ptr [0xF9A7B30]
#endif

// Layout assertions (also in sub_e943194.h; repeated here so the source file is self-contained
// for liftcheck).
static_assert(sizeof(void*) == 8, "sub_e943194: x64 ABI, pointer-sized address space");
static_assert(sub_e943194Layout::kIatSlotRva == 0xF9A7B30, "sub_e943194: IAT data slot RVA 0xF9A7B30");

// sub_e943194() -> void
//   0xe943194  jmp qword ptr [0xF9A7B30]            ; [data_f9a7b30] -> ReleaseSRWLockExclusive
// Single indirect tail-jump through IAT data slot 0xF9A7B30. Read the function pointer stored at
// image-relative RVA 0xF9A7B30 (== GetModuleHandleW(nullptr) + 0xF9A7B30 at runtime) and tail-call
// it with the same argument (RCX = srwlock). ReleaseSRWLockExclusive(SRWLOCK*) returns void, so this
// forwarder returns void. No instruction falls through; the tail-call never returns to this frame.
// Reads: [imageBase + 0xF9A7B30] (the function pointer in the IAT slot). Writes: none. Calls: none
// (this is a jmp, not a call); the indirect target is ReleaseSRWLockExclusive via data slot 0xF9A7B30.
// x64 Microsoft ABI: argument in RCX, no return value. [V: rdis dis 0xe943194 7]
void sub_e943194(void* srwlock)
{
    // 0xe943194  jmp qword ptr [0xF9A7B30]            ; tail call ReleaseSRWLockExclusive(srwlock)
    const uintptr_t imageBase = reinterpret_cast<uintptr_t>(GetModuleHandleW(nullptr));
    void** const slot = reinterpret_cast<void**>(imageBase + sub_e943194Layout::kIatSlotRva);
    using ReleaseSRWLockExclusiveFn = void (*)(void*);
    const ReleaseSRWLockExclusiveFn target = reinterpret_cast<ReleaseSRWLockExclusiveFn>(*slot);
    target(srwlock);   // tail call; ReleaseSRWLockExclusive returns void, never returns here
    // Unreachable: the tail-call transfers control and does not return to this frame.
}

LIFT_FN(sub_e943194, "sub_e943194", 0xE943194, sub_e943194, nullptr);

} // namespace native
