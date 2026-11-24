#pragma once
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_eec5a00 (0xeec5a00, size 0x6, 1.26.62.01): the whole function is one instruction,
//   0xeec5a00  jmp qword ptr [0xF9A72F0]     ; [data_f9a72f0]
// an indirect tail jump through data slot 0xF9A72F0 (.rdata). It reads no registers for
// its own logic, writes no memory, and forwards its one argument (RCX = int error code)
// unchanged to the slot target; control transfers straight to the target (tail call) with
// the same return behavior the target has.
//
// Slot 0xF9A72F0 holds the MSVCP140.dll import-by-name
// '?_Throw_Cpp_error@std@@YAXH@Z' = std::_Throw_Cpp_error(int) [V: PE import table read,
// slot RVA 0xF9A72F0 -> MSVCP140.dll !?_Throw_Cpp_error@std@@YAXH@Z]. At runtime the
// loader fills the slot with that function's address, so the jmp is a tail call to
// std::_Throw_Cpp_error(int) [V: rdis dis 0xeec5a00 = jmp qword ptr [0xF9A72F0]; peimports.py for the slot target].
//
// There are no struct fields touched by the function, so there are no layout offsets to
// assert; the x64 ABI contract is asserted below.
struct sub_eec5a00Layout {
    static_assert(sizeof(void*) == 8, "sub_eec5a00: x64 ABI, pointer-sized address space");
    using Fn = void (__cdecl*)(int);
    static_assert(sizeof(Fn) == 8, "sub_eec5a00: x64 function pointer is 8 bytes");
};

namespace std {
// std::_Throw_Cpp_error -- MSVCP140 import (?_Throw_Cpp_error@std@@YAXH@Z).
// Declared with its real symbol so the lifted body of sub_eec5a00 can call it directly:
// that is exactly the target the original jumps to through data slot 0xF9A72F0.
void _Throw_Cpp_error(int errorCode);
} // namespace std

namespace native {

// Signature of sub_eec5a00 itself: identical to the target (tail forwarder, no register
// shuffling). x64 Microsoft ABI: the error code arrives in RCX, the return is void; the
// original is a tail jump through data slot 0xF9A72F0 to std::_Throw_Cpp_error(int)
// [V: rdis dis 0xeec5a00 = jmp qword ptr [0xF9A72F0]; peimports.py for the slot target].
void sub_eec5a00(int errorCode);

} // namespace native
