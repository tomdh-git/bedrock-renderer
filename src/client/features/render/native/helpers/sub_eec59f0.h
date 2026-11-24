#pragma once
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_eec59f0 (0xeec59f0, size 0x6, 1.26.62.01): the whole function is one instruction,
//   0xeec59f0  jmp qword ptr [0xF9A75A8]     ; [data_f9a75a8]
// an indirect tail jump through data slot 0xF9A75A8. The pointer argument arrives in RCX,
// is forwarded as-is, and control never returns to the caller.
//
// Slot 0xF9A75A8 (.rdata) holds the import-by-name RVA 0xF9AB92C (hint 1413); the entry
// there is 'MSVCP140.dll!_Mtx_lock': void _Mtx_lock(struct _Mtx*) [V: PE import table,
// slot RVA 0xF9A75A8 -> import-by-name RVA 0xF9AB92C -> name _Mtx_lock]. At runtime the
// loader fills the slot with that function's address, so the jmp is a tail call to _Mtx_lock.
//
// This function reads no struct fields and writes none: there are no layout offsets to
// assert. The x64 ABI contract is asserted below.
struct _Mtx;  // opaque MSVCP140 C11 mutex; the pointee is never inspected by this forwarder

// MSVCP140!_Mtx_lock, the target of data slot 0xF9A75A8. Declared with the real C
// signature so the lifted body can call it exactly as the original's jmp [slot] dispatches.
extern "C" void _Mtx_lock(struct _Mtx* mtx);

struct sub_eec59f0Layout {
    static_assert(sizeof(void*) == 8, "sub_eec59f0: x64 ABI, pointer-sized address space");
    using Fn = void (__cdecl*)(struct _Mtx*);
    static_assert(sizeof(Fn) == 8, "sub_eec59f0: x64 function pointer is 8 bytes");
};

namespace native {

// Signature of sub_eec59f0 itself: identical to the target (tail forwarder, no register
// shuffling). x64 Microsoft ABI: one pointer argument (RCX), void return; control never
// returns to the caller because control passes straight to _Mtx_lock.
void sub_eec59f0(struct _Mtx* mtx);

} // namespace native
