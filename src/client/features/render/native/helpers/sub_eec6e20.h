// LIFT 0xeec6e20 size 0x6 1.26.62.01 sub_eec6e20
#pragma once
#include <cstdint>

namespace native {

// IAT slot for __std_exception_copy (patched by loader)
static constexpr uintptr_t kIatStdExceptionCopy = 0xF9A8A48;
static_assert(kIatStdExceptionCopy == 0xF9A8A48, "IAT slot RVA mismatch");

// Signature matches __std_exception_copy: void(void* dest, const void* src)
using StdExceptionCopyFn = void(*)(void* dest, const void* src);

// Lifted trampoline at 0xEEC6E20
// Original: jmp qword ptr [0xF9A8A48] (tail call through IAT)
extern "C" void sub_eec6e20(void* dest, const void* src);

// Registry entry
#define LIFT_FN_EEC6E20 \
    { 0xeec6e20, "sub_eec6e20", (void*)sub_eec6e20, NativeMode::Shadow }

} // namespace native