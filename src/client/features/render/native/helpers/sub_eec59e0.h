#pragma once
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_eec59e0 (0xeec59e0, size 0x6, 1.26.62.01): the whole function is one instruction,
//   0xeec59e0  jmp qword ptr [0xF9A7310]     ; [data_f9a7310]
// an indirect tail jump through data slot 0xF9A7310. It reads no registers, writes no
// memory, forwards no arguments and never returns to its caller.
//
// Slot 0xF9A7310 (.rdata) holds the import-by-name RVA 0xF9AA638; the entry there
// (hint 652) is '?_Xbad_function_call@std@@YAXXZ', i.e. std::_Xbad_function_call(void)
// of the MSVC CRT. At runtime the loader fills the slot with that function's address,
// so the jmp is a tail call to std::_Xbad_function_call [V: PE import table, slot RVA
// 0xF9A7310 -> import-by-name RVA 0xF9AA638 -> name ?_Xbad_function_call@std@@YAXXZ].
//
// There are no struct fields to layout-assert; the x64 ABI contract is asserted below.
struct sub_eec59e0Layout {
    static_assert(sizeof(void*) == 8, "sub_eec59e0: x64 ABI, pointer-sized address space");
    using Fn = void (__cdecl*)(void);
    static_assert(sizeof(Fn) == 8, "sub_eec59e0: x64 function pointer is 8 bytes");
};

namespace std {
// std::_Xbad_function_call -- MSVC CRT import (?_Xbad_function_call@std@@YAXXZ).
// Declared with its real symbol so the lifted body of sub_eec59e0 can call it directly:
// that is exactly the target the original jumps to through data slot 0xF9A7310.
void _Xbad_function_call(void);
} // namespace std

namespace native {

// Signature of sub_eec59e0 itself: identical to the target (tail forwarder, no register
// shuffling). x64 Microsoft ABI: no register arguments, void return; control never
// returns to the caller because std::_Xbad_function_call throws std::bad_function_call
// or terminates [I: never-returns from CRT semantics of _Xbad_function_call].
void sub_eec59e0(void);

} // namespace native
