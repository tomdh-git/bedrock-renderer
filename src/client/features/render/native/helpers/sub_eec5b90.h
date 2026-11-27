#pragma once
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_eec5b90 (0xeec5b90, size 0x6, 1.26.62.01): the whole function is one instruction,
//   0xeec5b90  jmp qword ptr [0xF9A7560]     ; [data_f9a7560]
// an indirect tail jump through data slot 0xF9A7560 (.rdata). It reads no registers for
// its own logic beyond forwarding RCX, writes no memory, and transfers control straight
// to MSVCP140!_Cnd_broadcast with the same argument (RCX = _Cnd_t, a pointer) and the same
// return value (_Thrd_result in EAX); control never returns to this function's own epilogue.
//
// Slot 0xF9A7560 (.rdata) holds the import-by-name entry for MSVCP140.dll!_Cnd_broadcast:
// _Thrd_result _Cnd_broadcast(_Cnd_t) of the MSVC CRT [V: PE import table, slot RVA
// 0xF9A7560 -> MSVCP140.dll !_Cnd_broadcast; peptr reads the slot as 0xF9AB854,
// peimports lists 0F9A7560 MSVCP140.dll!_Cnd_broadcast]. At runtime the loader fills the
// slot with that function's address, so the jmp is a tail call to _Cnd_broadcast(cond).
//
// _Cnd_t is already defined by the MSVC CRT headers as _Cnd_internal_imp_t* (a pointer)
// and _Cnd_broadcast is already declared as _Thrd_result _Cnd_broadcast(_Cnd_t) noexcept;
// neither is redeclared here. The function reads no struct fields and writes none: there are
// no layout offsets to assert. The x64 ABI contract is asserted below.
struct sub_eec5b90Layout {
    static_assert(sizeof(void*) == 8, "sub_eec5b90: x64 ABI, pointer-sized address space");
    using Fn = _Thrd_result (__cdecl*)(_Cnd_t);
    static_assert(sizeof(Fn) == 8, "sub_eec5b90: x64 function pointer is 8 bytes");
};

namespace native {

// Signature of sub_eec5b90 itself: identical to the target (tail forwarder, no register
// shuffling). x64 Microsoft ABI: one pointer argument (RCX = _Cnd_t, the condition
// variable), _Thrd_result return; the original is a tail jump through data slot 0xF9A7560
// to MSVCP140!_Cnd_broadcast [V: rdis dis 0xeec5b90 = jmp qword ptr [0xF9A7560];
// peimports for the slot target].
_Thrd_result sub_eec5b90(_Cnd_t cond);

} // namespace native
