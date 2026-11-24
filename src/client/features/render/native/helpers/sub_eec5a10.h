#pragma once
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_eec5a10 (0xeec5a10, size 0x6, 1.26.62.01): the whole function is one instruction,
//   0xeec5a10  jmp qword ptr [0xF9A75B8]     ; [data_f9a75b8]
// an indirect tail jump through IAT data slot 0xF9A75B8. The pointer argument arrives in
// RCX and is forwarded as-is to MSVCP140!_Mtx_unlock (the slot's imported address);
// no struct field is read or written by the instruction itself, and the return value is
// void.
//
// Slot 0xF9A75B8 (.rdata) holds the imported address of _Mtx_unlock
// [V: IAT table in docs/progress/oc_U-EX0b1.md (peimports.py): slot RVA 0xF9A75B8 -> _Mtx_unlock].
//
// There are no layout offsets to assert (no struct fields touched); the x64 ABI contract
// is asserted below.

struct _Mtx;  // opaque MSVCP140 C11 mutex; the pointee is never inspected by this forwarder

// MSVCP140!_Mtx_unlock, the target of data slot 0xF9A75B8. Declared with its real C
// signature so the lifted body of sub_eec5a10 calls exactly what the original's
// jmp qword ptr [0xF9A75B8] dispatches to at runtime.
extern "C" void _Mtx_unlock(struct _Mtx* mtx);

struct sub_eec5a10Layout {
    static_assert(sizeof(void*) == 8, "sub_eec5a10: x64 ABI, pointer-sized address space");
    using Fn = void (__cdecl*)(struct _Mtx*);
    static_assert(sizeof(Fn) == 8, "sub_eec5a10: x64 function pointer is 8 bytes");
};

namespace native {

// Signature of sub_eec5a10 itself: identical to the target (tail forwarder, no register
// shuffling). x64 Microsoft ABI: one pointer argument (RCX), void return; control passes
// straight to _Mtx_unlock.
void sub_eec5a10(struct _Mtx* mtx);

} // namespace native
