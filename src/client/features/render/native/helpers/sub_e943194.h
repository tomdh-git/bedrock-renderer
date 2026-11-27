#pragma once
#include <cstddef>
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

namespace native {

// sub_e943194 (0xe943194, size 0x7, 1.26.62.01): SRW lock release forwarder.
//   0xe943194  jmp qword ptr [0xF9A7B30]            ; [data_f9a7b30] -> ReleaseSRWLockExclusive
// The entire function is a single indirect tail-jump through IAT data slot 0xF9A7B30, which at
// runtime holds the address of ReleaseSRWLockExclusive (OS boundary, class os). The argument
// (RCX) is the SRWLOCK* passed straight through; ReleaseSRWLockExclusive returns void, so the
// forwarder returns void. x64 Microsoft ABI: argument in RCX, no return value. [V: rdis dis 0xe943194 7]
struct sub_e943194Layout {
    static_assert(sizeof(void*) == 8, "sub_e943194: x64 ABI, pointer-sized address space");
    // IAT data slot (image-relative RVA) read by 0xe943194 `jmp qword ptr [0xF9A7B30]`; at runtime
    // it holds &ReleaseSRWLockExclusive [V: docs/progress/oc_U-EX0b1.md IAT resolution 0xF9A7B30=ReleaseSRWLockExclusive].
    static constexpr std::uintptr_t kIatSlotRva = 0xF9A7B30;
    static_assert(kIatSlotRva == 0xF9A7B30, "sub_e943194: IAT data slot RVA 0xF9A7B30");
};

// Exact x64 Microsoft ABI mirror of the original function.
// RCX = srwlock: the SRWLOCK* forwarded straight to ReleaseSRWLockExclusive through the IAT slot.
// Return: void (ReleaseSRWLockExclusive is VOID; the tail-jump never returns to this frame).
void sub_e943194(void* srwlock);

} // namespace native
