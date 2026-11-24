#pragma once
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_eec5850 (0xeec5850, size 0x6, 1.26.62.01): the whole function is one instruction,
//   0xeec5850  jmp qword ptr [0xF9A7320]     ; [data_f9a7320]
// an indirect tail jump through data slot 0xF9A7320. It reads no registers, writes no
// memory, forwards its one argument (RCX = const char* message) unchanged, and never
// returns to its caller.
//
// Slot 0xF9A7320 (.rdata) holds import-by-name RVA 0xF9AA680: hint 654, name
// '?_Xlength_error@std@@YAXPEBD@Z' = std::_Xlength_error(const char*) of the MSVC CRT
// [V: PE import table read, slot RVA 0xF9A7320 -> import-by-name RVA 0xF9AA680 -> name
// ?_Xlength_error@std@@YAXPEBD@Z]. At runtime the loader fills the slot with that
// function's address, so the jmp is a tail call to std::_Xlength_error.
//
// There are no struct fields to layout-assert; the x64 ABI contract is asserted below.
struct sub_eec5850Layout {
    static_assert(sizeof(void*) == 8, "sub_eec5850: x64 ABI, pointer-sized address space");
    using Fn = void (__cdecl*)(const char*);
    static_assert(sizeof(Fn) == 8, "sub_eec5850: x64 function pointer is 8 bytes");
};

namespace std {
// std::_Xlength_error -- MSVC CRT throw helper (?_Xlength_error@std@@YAXPEBD@Z).
// Declared with its real symbol so the lifted body of sub_eec5850 can call it directly:
// that is exactly the target the original jumps to through data slot 0xF9A7320.
void _Xlength_error(const char* message);
} // namespace std

namespace native {

// Signature of sub_eec5850 itself: identical to the target (tail forwarder, no register
// shuffling). x64 Microsoft ABI: the message arrives in RCX, the return is void; control
// never returns to the caller because std::_Xlength_error throws std::length_error
// (never-returns per CRT semantics of _Xlength_error).
void sub_eec5850(const char* message);

} // namespace native
