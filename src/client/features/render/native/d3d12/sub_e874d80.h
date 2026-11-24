#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// Layout recovered from the disassembly of 0xe874d80 (size 0x95, 1.26.62.01).
// BgfxFrameBuilder slot 16 primitive: reads one byte from a stream and validates it
// is 0 or 1; on success writes the byte to *out and returns 1, otherwise returns 0.
// On a stream-failure path it throws via sub_eec6d80 (0xEEC6D80, lift set).
// Every offset below is an instruction [reg+off] seen in the listing [V].

// Read-only data / globals referenced by the function [V].
static constexpr std::uintptr_t kGblCookie    = 0x1230A0C0u; // mov rax,[0x1230A0C0]  (/GS stack cookie)
static constexpr std::uintptr_t kIndirectSlot = 0xF9A7480u;  // call qword ptr [0xF9A7480] (stream read vcall slot)
static constexpr std::uintptr_t kData_F08E738 = 0xF08E738u;  // lea rax,[0xF08E738] (exception vptr, arg0)
static constexpr std::uintptr_t kData_FB3B080 = 0xFB3B080u;  // lea rdx,[0xFB3B080] (exception arg1)

// Stack frame layout used by the function (rsp-relative, frame size 0x50) [V].
static constexpr std::ptrdiff_t kCookieSlotOff = 0x48;   // mov [rsp+0x48], rax (/GS cookie)
static constexpr std::ptrdiff_t kByteBufOff   = 0x2F;   // lea rdx,[rsp+0x2F]; movzx eax,byte ptr [rsp+0x2F]
static constexpr std::ptrdiff_t kExceptArg0Off = 0x30;   // mov [rsp+0x30], rax (0xF08E738)
static constexpr std::ptrdiff_t kExceptArg1Off = 0x38;   // movups [rsp+0x38], xmm0 (zero)

static_assert(kCookieSlotOff == 0x48, "e874d80: /GS cookie slot at rsp+0x48");
static_assert(kByteBufOff   == 0x2F, "e874d80: byte buffer at rsp+0x2F");
static_assert(kExceptArg0Off == 0x30, "e874d80: exception arg0 at rsp+0x30");
static_assert(kExceptArg1Off == 0x38, "e874d80: exception arg1 at rsp+0x38");

// x64 Microsoft ABI: rcx = stream object (a0), rdx = out pointer (a1). Returns bool in al.
extern "C" bool sub_e874d80(void* stream, void* out);

} // namespace native