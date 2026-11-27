#pragma once

#include <cstddef>
#include <cstdint>

// sub_e903290: BgfxFrameBuilder slot 11 (size 0xc3, 1.26.62.01).
// Reverse-engineered from the disassembly of [0xe903290, 0xe903353) in
// Minecraft.Windows.exe 1.26.62.01. Every offset below is observed in that
// listing and is cited beside the statement that uses it in
// src/client/features/render/native/dragon/sub_e903290.cpp. [V]
//
// Data globals read by the function:
//   cookie global at 0x1230A0C0   [0xe90329c mov rax,[0x1230A0C0]; 0xe90332e mov rcx,[0x1230A0C0]]
//   selection table at 0xF440E10  [0xe9032cb lea rcx,[0xF440E10]; 0xe9032d2 mov ebx,[rcx+rax*4]]
//     dword elements, indexed by (uint8_t)(a2-1) when (uint8_t)(a2-1) <= 10 (indices 0..10).
// Stack frame (after sub rsp,0x60):
//   rsp+0x58: stack cookie slot (8 bytes)
//   rsp+0x2C..rsp+0x58: 11-u32 result buffer; passed as a2 to sub_bc6af50
// Calls:
//   0xe9032bc  call 0xBC6AF50   (lifted, native::bgfx::sub_bc6af50)
//   0xe90334d  call 0xE951550   (boundary, class crt, docs/data/native_boundary.tsv line 467; noreturn)
// No game struct fields are read or written.

namespace native::dragon {

static constexpr std::uintptr_t kDataCookie = 0x1230A0C0;   // [0xe90329c] [0xe90332e]
static constexpr std::uintptr_t kTableRva = 0xF440E10;      // [0xe9032cb]
static constexpr std::uint8_t kMaxResults = 11;             // callee a1: mov cl,0xB [0xe9032ba]
static constexpr std::uint8_t kMaxIndex = 10;               // cmp al,0xA [0xe9032c4]

static_assert(kMaxResults * sizeof(std::uint32_t) == 0x2C,
              "sub_e903290: result buffer at rsp+0x2C is 11 u32 (rsp+0x2C..rsp+0x58)");
static_assert(kMaxResults == 11 && kMaxIndex == 10,
              "sub_e903290: selection table indices are 0..10 inclusive");

// Exact x64 Microsoft ABI signature of the original:
//   RCX = a1 (std::uint8_t* output: a1[0] = dil when match found, a1[1] = result)
//   RDX = a2 (std::uint32_t): low byte stored at a1[0], (a2-1) indexes kTable
//   Return: RAX = a1 (same pointer)
std::uint8_t* sub_e903290(std::uint8_t* a1, std::uint32_t a2);

} // namespace native::dragon
