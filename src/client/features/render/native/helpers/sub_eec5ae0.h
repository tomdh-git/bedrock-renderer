#pragma once
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_eec5ae0 (0xeec5ae0, size 0x6, 1.26.62.01): the whole function is one instruction,
//   0xeec5ae0  jmp qword ptr [0xF9A7318]     ; [data_f9a7318]
// an indirect tail jump through data slot 0xF9A7318 (.rdata). The const char* message
// arrives in RCX and is forwarded unchanged to MSVCP140!std::_Xinvalid_argument; the
// instruction itself reads no registers beyond RCX, writes no memory, and control never
// returns to the caller because _Xinvalid_argument throws std::invalid_argument.
//
// Slot 0xF9A7318 (.rdata) holds the MSVCP140.dll import-by-name entry
// '?_Xinvalid_argument@std@@YAXPEBD@Z' = std::_Xinvalid_argument(const char*) of the
// MSVC CRT [V: PE import table read via tools/sigs/peimports.py: slot RVA 0xF9A7318 ->
// MSVCP140.dll !?_Xinvalid_argument@std@@YAXPEBD@Z]. At runtime the loader fills the slot
// with that function's address, so the jmp is a tail call to std::_Xinvalid_argument.
//
// Every call site confirms the contract: 39 sites, all `lea rcx,[<string>];
// call 0xEEC5AE0`, return value unused [V: rdis xr 0xeec5ae0, e.g. 0x275314 lea rcx,["invalid stoi argument"]; 0x27531b call 0xEEC5AE0].
//
// There are no struct fields to layout-assert; the x64 ABI contract is asserted below.
struct sub_eec5ae0Layout {
    static_assert(sizeof(void*) == 8, "sub_eec5ae0: x64 ABI, pointer-sized address space");
    using Fn = void (__cdecl*)(const char*);
    static_assert(sizeof(Fn) == 8, "sub_eec5ae0: x64 function pointer is 8 bytes");
};

namespace std {
// std::_Xinvalid_argument -- MSVCP140 CRT throw helper (?_Xinvalid_argument@std@@YAXPEBD@Z).
// Declared with its real symbol so the lifted body of sub_eec5ae0 can call it directly:
// that is exactly the target the original jumps to through data slot 0xF9A7318.
void _Xinvalid_argument(const char* message);
} // namespace std

namespace native {

// Signature of sub_eec5ae0 itself: identical to the target (tail forwarder, no register
// shuffling). x64 Microsoft ABI: the message arrives in RCX, the return is void; control
// never returns to the caller because std::_Xinvalid_argument throws std::invalid_argument.
void sub_eec5ae0(const char* message);

} // namespace native
