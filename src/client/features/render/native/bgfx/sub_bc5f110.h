#pragma once
#include <cstddef>
#include <cstdint>

namespace native::bgfx {

// sub_bc5f110 (0xbc5f110, size 0x121, 1.26.62.01): variadic log helper.
//
// Frame layout relative to the frame pointer RBP the function establishes at
// 0xbc5f121 (lea rbp,[rsp+0x80]) after the 0x2018-byte stack probe. The struct
// starts at RBP-0x78, the lowest address the function addresses through RBP.
//
//   RBP-0x78   pointer to the vararg register save area (RBP+0x1FD0)
//   RBP-0x70   0x2000-byte format buffer
//   RBP+0x1F90 stack cookie (RBP ^ __security_cookie)
//   RBP+0x1FD0 vararg save slot for R8
//   RBP+0x1FD8 vararg save slot for R9
struct SubBc5f110Frame {
    void* va_list_ptr;            // 0x0000 = RBP-0x78  0xbc5f14b..0xbc5f152
    char buffer[0x2000];          // 0x0008 = RBP-0x70  0xbc5f16e..0xbc5f17d
    std::uintptr_t cookie;        // 0x2008 = RBP+0x1F90 0xbc5f144
    std::uint8_t pad1[0x38];      // 0x2010 = RBP+0x1F98 saved registers
    std::uint64_t vararg_r8;      // 0x2048 = RBP+0x1FD0 0xbc5f12c
    std::uint64_t vararg_r9;      // 0x2050 = RBP+0x1FD8 0xbc5f133
};
static_assert(offsetof(SubBc5f110Frame, va_list_ptr) == 0x0000, "sub_bc5f110: va_list pointer at RBP-0x78");
static_assert(offsetof(SubBc5f110Frame, buffer) == 0x0008, "sub_bc5f110: format buffer at RBP-0x70");
static_assert(offsetof(SubBc5f110Frame, cookie) == 0x2008, "sub_bc5f110: stack cookie at RBP+0x1F90");
static_assert(offsetof(SubBc5f110Frame, vararg_r8) == 0x2048, "sub_bc5f110: R8 save slot at RBP+0x1FD0");
static_assert(offsetof(SubBc5f110Frame, vararg_r9) == 0x2050, "sub_bc5f110: R9 save slot at RBP+0x1FD8");
static_assert(sizeof(SubBc5f110Frame) == 0x2058, "sub_bc5f110: frame ends after the R9 save slot");

// Constants the function reads or writes.
inline constexpr std::uintptr_t kSubBc5f110CookieGlobal = 0x1230A0C0;  // 0xbc5f13a  mov rax,[0x1230A0C0]
inline constexpr std::uintptr_t kSubBc5f110LoggerGlobal = 0x12ADF808;  // 0xbc5f156  cmp qword ptr [0x12ADF808],0
inline constexpr std::uintptr_t kSubBc5f110CfgDispatchSlot = 0xF99FFA0; // 0xbc5f1db  call qword ptr [0xF99FFA0]
inline constexpr std::uintptr_t kSubBc5f110TerminateSlot = 0xF9A8CB0;  // 0xbc5f217  call qword ptr [0xF9A8CB0]
inline constexpr std::int32_t kSubBc5f110BufferSize = 0x2000;          // 0xbc5f175  mov edx,0x2000
inline constexpr std::size_t kSubBc5f110LogVtableSlot = 1;             // 0xbc5f1ce  mov rax,[rax+8]

// x64 Microsoft ABI: ECX = level (int32), RDX = format string, R8/R9 = the
// first two varargs. The function does not use va_start: it spills R8/R9 into a
// contiguous 2-slot block at RBP+0x1FD0/0x1FD8 (0xbc5f12c/0xbc5f133) and passes
// &[rbp+0x1FD0] as the va_list pointer to sub_ebcf430. Declared as 4 explicit
// parameters (same register assignment as variadic) so the LIFT_FN/Thunk
// machinery can take its address; stack varargs beyond R9 are ignored, exactly
// like the original (which only spills R8/R9).
extern "C" void sub_bc5f110(std::int32_t level, const char* fmt, std::uintptr_t varg1, std::uintptr_t varg2);

} // namespace native::bgfx
