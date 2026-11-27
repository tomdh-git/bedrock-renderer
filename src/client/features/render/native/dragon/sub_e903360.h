#pragma once

#include <cstddef>
#include <cstdint>

// sub_e903360: BgfxFrameBuilder slot 11 (size 0xa9, 1.26.62.01).
// Reverse-engineered from the disassembly of [0xe903360, 0xe903409) in
// Minecraft.Windows.exe 1.26.62.01. Every offset below is observed in that
// listing and is cited beside the statement that uses it in
// src/client/features/render/native/dragon/sub_e903360.cpp. [V]
//
// Data globals read by the function:
//   cookie global at 0x1230A0C0   [0xe903367 mov rax,[0x1230A0C0]; 0xe9033e2 mov r10,[0x1230A0C0]]
//   selection table at 0xF440E10  [0xe90338e lea rcx,[0xF440E10]; 0xe903395 mov edx,[rcx+rax*4]]
//     dword elements, indexed by (a1-1) when (uint8_t)(a1-1) <= 10 (indices 0..10).
// Stack frame (after sub rsp,0x60):
//   rsp+0x58: stack cookie slot (8 bytes)
//   rsp+0x2C..rsp+0x58: 11-u32 result buffer; passed as a2 to sub_bc6af50
// Calls:
//   0xe90337d  call 0xBC6AF50   (lifted, native::bgfx::sub_bc6af50)
//   0xe903403  call 0xE951550   (boundary, class crt, docs/data/native_boundary.tsv line 467; noreturn)
// No game struct fields are read or written.

namespace native::dragon {

static constexpr std::uintptr_t kDataCookie = 0x1230A0C0;   // [0xe903367] [0xe9033e2]
static constexpr std::uintptr_t kTableRva = 0xF440E10;      // [0xe90338e]
static constexpr std::uint8_t kMaxResults = 11;             // callee a1: mov cl,0xB [0xe90337b]
static constexpr std::uint8_t kMaxIndex = 10;               // cmp bl,0xA [0xe903386]

static_assert(kMaxResults * sizeof(std::uint32_t) == 0x2C,
              "sub_e903360: result buffer at rsp+0x2C is 11 u32 (rsp+0x2C..rsp+0x58)");
static_assert(kMaxResults == 11 && kMaxIndex == 10,
              "sub_e903360: selection table indices are 0..10 inclusive");

// Exact x64 Microsoft ABI signature of the original:
//   RCX = a1 (uint8_t); RDX = a2 at entry but never read: the original passes a
//   local buffer at rsp+0x2C as the callee's a2 (the incoming a2 is dead).
//   Return: EAX = AL = 0 or 1.
bool sub_e903360(std::uint8_t a1, std::uint32_t* a2);

} // namespace native::dragon
