// LIFT 0xeec5ae0 size 0x6 1.26.62.01 sub_eec5ae0
#include "sub_eec5ae0.h"

static_assert(sizeof(void*) == 8, "sub_eec5ae0: x64 ABI, pointer-sized address space");

namespace native {

// sub_eec5ae0 (0xeec5ae0, size 0x6, 1.26.62.01).
//
// The whole function is one instruction, an indirect tail jump through a data slot:
//   0xeec5ae0  jmp qword ptr [0xF9A7318]     ; [data_f9a7318]
//
// Slot 0xF9A7318 (.rdata) is the MSVCP140.dll import slot of std::_Xinvalid_argument:
// '?_Xinvalid_argument@std@@YAXPEBD@Z' = void _Xinvalid_argument(const char*) [V: PE import
// table read via tools/sigs/peimports.py: slot RVA 0xF9A7318 -> MSVCP140.dll
// !?_Xinvalid_argument@std@@YAXPEBD@Z]. At runtime the loader fills the slot with that
// function's address, so the jmp tail-calls std::_Xinvalid_argument. The message pointer
// arrives in RCX and is forwarded unchanged; nothing else is read or written and control
// never returns to the caller (_Xinvalid_argument throws std::invalid_argument).
//
// Every call site confirms the contract: 39 sites, all `lea rcx,[<string>];
// call 0xEEC5AE0`, return value unused [V: rdis xr 0xeec5ae0, e.g. 0x275314 lea rcx,["invalid stoi argument"]; 0x27531b call 0xEEC5AE0].
//
// Verbatim instruction of the function (matches rdis dis 0xeec5ae0):
#if 0
0xeec5ae0  jmp qword ptr [0xF9A7318]
#endif

void sub_eec5ae0(const char* message) {
    // 0xeec5ae0..0xeec5ae6: jmp qword ptr [0xF9A7318] ; tail call to std::_Xinvalid_argument via data slot 0xF9A7318
    return std::_Xinvalid_argument(message);   // 0xeec5ae0  jmp qword ptr [0xF9A7318]
}

} // namespace native

LIFT_FN(eec5ae0, "sub_eec5ae0", 0xEEC5AE0, sub_eec5ae0, nullptr);
