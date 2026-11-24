#pragma once

#include <cstddef>
#include <cstdint>

#include "client/features/render/native/Lift.h"

// sub_bc6af50: BgfxFrameBuilder slot 82 (size 0x1f3, 1.26.62.01).
// Reverse-engineered from the disassembly of [0xbc6af50, 0xbc6b143) in
// Minecraft.Windows.exe 1.26.62.01. Every offset below is observed in that
// listing and is cited beside the statement that uses it in
// src/client/features/render/native/bgfx/sub_bc6af50.cpp. [V]
//
// The function touches no named game struct. All memory accesses are:
//   * stack buffer at rsp+0x24 (size 0x9C, local only)
//   * caller-provided output array a2[] (uint32_t, indexed by sil)
//   * global data: cookie at 0x1230A0C0, array base at 0x127CA028 (0x28 stride)
//   * data slots for indirect calls: [0xF9A8770] (fn1), [0xF9A8780] (fn2)
//   * boundary call 0xE951550 on the stack-cookie-failure path (noreturn)

// Data slot addresses (RVA; VA = RewriteRegistry::imageBase() + slot). [V]
static constexpr std::uintptr_t kDataSlot_Fn1 = 0xF9A8770;  // mov r13,[0xF9A8770] @0xbc6af99; mov rbx,[0xF9A8770] @0xbc6b07f
static constexpr std::uintptr_t kDataSlot_Fn2 = 0xF9A8780;  // mov rbp,[0xF9A8780] @0xbc6afa0; mov r15,[0xF9A8780] @0xbc6b09f
static constexpr std::uintptr_t kDataCookie = 0x1230A0C0;   // mov rax,[0x1230A0C0] @0xbc6af63 / @0xbc6b110
static constexpr std::uintptr_t kDataArrayBase = 0x127CA028; // lea r15,[0x127CA028] @0xbc6af8b

// Stack buffer layout (rsp+0x24 base, size 0x9C). [V]
static constexpr std::uintptr_t kStackBufBase = 0x24;  // lea r14,[rsp+0x24] @0xbc6af94; lea rdi,[rsp+0x24] @0xbc6b053
static constexpr std::uintptr_t kStackBufCookieValOff = 0x00; // mov [rsp+0x24],rax @0xbc6afe4 / mov [rsp+0x24],r14 @0xbc6b072 / @0xbc6b0ca
static constexpr std::uintptr_t kStackBufDwordOff = 0x2C; // mov dword ptr [rsp+0x2C],2 @0xbc6afe9 / @0xbc6b077 / @0xbc6b0cf

// Immediate constants seen in the function. [V]
static constexpr std::uint32_t kMemsetSize = 0x9C;   // mov r8d,0x9C @0xbc6afca / @0xbc6b058 / @0xbc6b0ba
static constexpr std::uint64_t kBufInitVal = 0x50000009Cull; // mov rax,0x50000009C @0xbc6afda; mov r14,0x50000009C @0xbc6b068
static constexpr std::uint32_t kBufDwordVal = 2;     // mov dword ptr [rsp+0x2C],2 @0xbc6afe9 / @0xbc6b077 / @0xbc6b0cf
static constexpr std::uint8_t kFn1Arg3 = 5;          // mov r8b,5 @0xbc6aff8 / @0xbc6b006 / @0xbc6b08d / @0xbc6b0eb / @0xbc6b0de
static constexpr std::uint8_t kFn2Arg2 = 3;          // mov edx,3 @0xbc6b00f / @0xbc6b0a9 / @0xbc6b0f3
static constexpr std::uint8_t kMaxLoop = 0xB;        // cmp r12,0xB @0xbc6afb7
static constexpr std::uint8_t kByteCheckVal = 1;     // cmp byte ptr [r15],1 @0xbc6b039

// Stack cookie failure path calls 0xE951550 (boundary, crt) then int3 (noreturn).
// Declared here; the boundary wrapper is defined in the .cpp.
namespace native {

// fn1: indirect call through data slot [0xF9A8770].
// Called as (rcx: void*, edx: int, r8: int) -> returns void* (rax). [V]
extern "C" void* fn_F9A8770(void* a1, int a2, int a3);

// fn2: indirect call through data slot [0xF9A8780].
// Called as (rcx: void*, edx: int, r8: void*) -> returns int (eax). [V]
extern "C" int fn_F9A8780(void* a1, int a2, void* a3);

} // namespace native

namespace native::bgfx {

// Exact x64 Microsoft ABI signature of the original.
// RCX = a1 (uint8_t, tested at entry), RDX = a2 (uint32_t* output array).
// Return: EAX = ESI (0..11 range).
uint32_t sub_bc6af50(uint8_t a1, uint32_t* a2);

// Footprint: writes to the caller's output array a2[0..a1) (up to a1 u32s).
native::Footprint sub_bc6af50_footprint(uint8_t a1, uint32_t* a2);

} // namespace native::bgfx

// static_assert for layout: stack buffer (0x24..0xC0) is 0x9C bytes, matching
// the memset count and the cookie slot at rsp+0xC0. [V]
static_assert(0xC0 - kStackBufBase == kMemsetSize,
              "bc6af50: stack buffer at rsp+0x24 is 0x9C bytes before cookie at rsp+0xC0");
