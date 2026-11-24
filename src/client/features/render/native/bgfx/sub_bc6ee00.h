#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// Callees of sub_0xbc6ee00, all `lift` in docs/data/native_boundary.tsv (X0b5)
// [0xebdbf10, 0xeec6ec0, 0xebdbf20 = auto-unresolved->lift] [V]. Forward-declared
// here (namespace native, names sub_<rva>) and called directly from the lifted
// body exactly like the original calls (hard rule 66): each callee is lifted by
// its own unit, no wrapper is invented, no target address is hard-coded.
// Signatures are taken from the call sites only [V].
extern "C" void sub_ebdbf10(void* p);                    // 0xbc6ee27  call 0xEBDBF10  ; rcx = a0 + 0x1C0; rax dead
extern "C" void sub_eec6ec0(void* dst, const void* src, std::uint32_t count);  // 0xbc6ee43  call 0xEEC6EC0  ; rcx = a1, rdx = r14 + 0xE60DE8, r8d = 0xD0; rax dead
extern "C" void sub_ebdbf20(void* p);                    // 0xbc6ef0e  call 0xEBDBF20  ; rcx = a0 + 0x1C0; rax dead

} // namespace native

namespace native::bgfx {

// sub_0xbc6ee00 (VV frame-graph builder), Minecraft Windows 1.26.62.01,
// [0xbc6ee00, 0xbc6ef22), size 0x122, depth 5, D0.
// Callees: sub_ebdbf10 (0xebdbf10), sub_eec6ec0 (0xeec6ec0), sub_ebdbf20 (0xebdbf20)
//   — all `lift` in docs/data/native_boundary.tsv (X0b5); forward-declared above
//     in namespace native and called directly.
// All facts [V] from the disassembly; see docs/functions/bc6ee00.md.
//
// x64 Microsoft ABI: rcx = a0 (object base), rdx = a1 (destination base),
// return rax = a1. No /GS cookie and no SEH in the function [V].

// Slice of the a0 object: only offsets the function touches are real fields;
// everything between them is padding that carries no meaning [V].
struct A0 {
    std::byte pad_0x0000[0x1C0];
    void* p_0x1C0;                                // +0x1C0 [V]: lea rdi,[rcx+0x1C0] at 0xbc6ee1d;
                                                  // address passed to sub_ebdbf10/sub_ebdbf20, never dereferenced here
    std::byte pad_0x1C8[0x1CFD0C8 - 0x1C8];
    uint8_t* r14_0x1CFD0C8;                       // +0x1CFD0C8 [V]: mov r14,[rbx+0x1CFD0C8] at 0xbc6ee2c;
                                                  // byte base for the r14-relative reads below
    std::byte pad_0x1CFD0D0[0x1DDD308 - 0x1CFD0D0];
    std::uint16_t w_0x1DDD308;                    // +0x1DDD308 [V]: movzx eax,word ptr [rbx+0x1DDD308] at 0xbc6ee6e
    std::uint16_t w_0x1DE1348;                    // +0x1DE1348 [V] at 0xbc6ee79
    std::byte pad_0x1DE134A[0x1DFB48C - 0x1DE134A];
    std::uint16_t w_0x1DFB48C;                    // +0x1DFB48C [V] at 0xbc6ee84
    std::byte pad_0x1DFB48E[0x1DE534C - 0x1DFB48E];
    std::uint16_t w_0x1DE534C;                    // +0x1DE534C [V] at 0xbc6ee8f
    std::byte pad_0x1DE534E[0x1DFBE94 - 0x1DE534E];
    std::uint16_t w_0x1DFBE94;                    // +0x1DFBE94 [V] at 0xbc6ee9a
    std::byte pad_0x1DFBE96[0x1DF145C - 0x1DFBE96];
    std::uint16_t w_0x1DF145C;                    // +0x1DF145C [V] at 0xbc6eea5
    std::byte pad_0x1DF145E[0x1DED458 - 0x1DF145E];
    std::uint16_t w_0x1DED458;                    // +0x1DED458 [V] at 0xbc6eeb0
    std::byte pad_0x1DED45A[0x1DF7478 - 0x1DED45A];
    std::uint16_t w_0x1DF7478;                    // +0x1DF7478 [V] at 0xbc6eebe
    std::byte pad_0x1DF747A[0x1DFB690 - 0x1DF747A];
    std::uint16_t w_0x1DFB690;                    // +0x1DFB690 [V] at 0xbc6eecc
    std::byte pad_0x1DFB692[0x1DE9454 - 0x1DFB692];
    std::uint16_t w_0x1DE9454;                    // +0x1DE9454 [V] at 0xbc6eeda
    std::byte pad_0x1DE9456[0x1DE9350 - 0x1DE9456];
    std::uint16_t w_0x1DE9350;                    // +0x1DE9350 [V] at 0xbc6eee8
    std::byte pad_0x1DE9352[0x1EBF1D8 - 0x1DE9352];
    std::uint8_t block_0x1EBF1D8[16];             // +0x1EBF1D8 [V]: movdqu xmm0,[rbx+0x1EBF1D8] at 0xbc6eef6
};
static_assert(offsetof(A0, p_0x1C0) == 0x1C0, "sub_0xbc6ee00: A0::p_0x1C0 at +0x1C0");
static_assert(offsetof(A0, r14_0x1CFD0C8) == 0x1CFD0C8, "sub_0xbc6ee00: A0::r14_0x1CFD0C8 at +0x1CFD0C8");
static_assert(offsetof(A0, w_0x1DDD308) == 0x1DDD308, "sub_0xbc6ee00: A0::w_0x1DDD308 at +0x1DDD308");
static_assert(offsetof(A0, w_0x1DE1348) == 0x1DE1348, "sub_0xbc6ee00: A0::w_0x1DE1348 at +0x1DE1348");
static_assert(offsetof(A0, w_0x1DFB48C) == 0x1DFB48C, "sub_0xbc6ee00: A0::w_0x1DFB48C at +0x1DFB48C");
static_assert(offsetof(A0, w_0x1DE534C) == 0x1DE534C, "sub_0xbc6ee00: A0::w_0x1DE534C at +0x1DE534C");
static_assert(offsetof(A0, w_0x1DFBE94) == 0x1DFBE94, "sub_0xbc6ee00: A0::w_0x1DFBE94 at +0x1DFBE94");
static_assert(offsetof(A0, w_0x1DF145C) == 0x1DF145C, "sub_0xbc6ee00: A0::w_0x1DF145C at +0x1DF145C");
static_assert(offsetof(A0, w_0x1DED458) == 0x1DED458, "sub_0xbc6ee00: A0::w_0x1DED458 at +0x1DED458");
static_assert(offsetof(A0, w_0x1DF7478) == 0x1DF7478, "sub_0xbc6ee00: A0::w_0x1DF7478 at +0x1DF7478");
static_assert(offsetof(A0, w_0x1DFB690) == 0x1DFB690, "sub_0xbc6ee00: A0::w_0x1DFB690 at +0x1DFB690");
static_assert(offsetof(A0, w_0x1DE9454) == 0x1DE9454, "sub_0xbc6ee00: A0::w_0x1DE9454 at +0x1DE9454");
static_assert(offsetof(A0, w_0x1DE9350) == 0x1DE9350, "sub_0xbc6ee00: A0::w_0x1DE9350 at +0x1DE9350");
static_assert(offsetof(A0, block_0x1EBF1D8) == 0x1EBF1D8, "sub_0xbc6ee00: A0::block_0x1EBF1D8 at +0x1EBF1D8");

// Slice of the r14 pointer (loaded from a0+0x1CFD0C8), used as a byte base [V].
struct R14 {
    std::byte pad_0x0000[0xDC5808];
    std::uint16_t v_0xDC5808[4];                  // +0xDC5808 [V]: movq xmm0,[r14+0xDC5808] at 0xbc6ee48;
                                                  // shuffled (pshuflw 0xE8), low dword stored to a1+0xD0
    std::byte pad_0xDC5810[0xE60DE0 - 0xDC5810];
    uint8_t* p_0xE60DE0;                          // +0xE60DE0 [V]: mov rax,[r14+0xE60DE0] at 0xbc6ee5e;
                                                  // *(uint32_t*)(p + 0xC) is stored to a1+0xD4
    std::uint8_t src_0xE60DE8[0xD0];              // +0xE60DE8 [V]: lea rdx,[r14+0xE60DE8] at 0xbc6ee33;
                                                  // source buffer of the sub_eec6ec0 copy (0xD0 bytes)
};
static_assert(offsetof(R14, v_0xDC5808) == 0xDC5808, "sub_0xbc6ee00: R14::v_0xDC5808 at +0xDC5808");
static_assert(offsetof(R14, p_0xE60DE0) == 0xE60DE0, "sub_0xbc6ee00: R14::p_0xE60DE0 at +0xE60DE0");
static_assert(offsetof(R14, src_0xE60DE8) == 0xE60DE8, "sub_0xbc6ee00: R14::src_0xE60DE8 at +0xE60DE8");

// Slice of the a1 destination object: only touched offsets are real fields [V].
struct A1 {
    std::byte pad_0x0000[0x74];
    std::uint16_t w_0x74;                         // +0x74 [V]: mov [rsi+0x74],ax at 0xbc6ee75
    std::uint16_t w_0x76;                         // +0x76 [V] at 0xbc6ee80
    std::uint16_t w_0x78;                         // +0x78 [V] at 0xbc6ee8b
    std::uint16_t w_0x7A;                         // +0x7A [V] at 0xbc6ee96
    std::uint16_t w_0x7C;                         // +0x7C [V] at 0xbc6eea1
    std::uint16_t w_0x7E;                         // +0x7E [V] at 0xbc6eeac
    std::uint16_t w_0x80;                         // +0x80 [V] at 0xbc6eeb7
    std::uint16_t w_0x82;                         // +0x82 [V] at 0xbc6eec5
    std::uint16_t w_0x84;                         // +0x84 [V] at 0xbc6eed3
    std::uint16_t w_0x86;                         // +0x86 [V] at 0xbc6eee1
    std::uint16_t w_0x88;                         // +0x88 [V] at 0xbc6eeef
    std::byte pad_0x8A[0x90 - 0x8A];
    std::uint8_t block_0x90[16];                  // +0x90 [V]: movdqu [rsi+0x90],xmm0 at 0xbc6ef03;
                                                  // pshufd 0x4E rotation {d2,d3,d0,d1} of a0+0x1EBF1D8
    std::byte pad_0xA0[0xD0 - 0xA0];
    std::uint16_t shuffle_0xD0[2];                // +0xD0 [V]: movd [rsi+0xD0],xmm0 at 0xbc6ee56;
                                                  // {w0,w2} of pshuflw 0xE8 of r14+0xDC5808
    std::uint32_t d_0xD4;                         // +0xD4 [V]: mov [rsi+0xD4],eax at 0xbc6ee68
};
static_assert(offsetof(A1, w_0x74) == 0x74, "sub_0xbc6ee00: A1::w_0x74 at +0x74");
static_assert(offsetof(A1, w_0x76) == 0x76, "sub_0xbc6ee00: A1::w_0x76 at +0x76");
static_assert(offsetof(A1, w_0x78) == 0x78, "sub_0xbc6ee00: A1::w_0x78 at +0x78");
static_assert(offsetof(A1, w_0x7A) == 0x7A, "sub_0xbc6ee00: A1::w_0x7A at +0x7A");
static_assert(offsetof(A1, w_0x7C) == 0x7C, "sub_0xbc6ee00: A1::w_0x7C at +0x7C");
static_assert(offsetof(A1, w_0x7E) == 0x7E, "sub_0xbc6ee00: A1::w_0x7E at +0x7E");
static_assert(offsetof(A1, w_0x80) == 0x80, "sub_0xbc6ee00: A1::w_0x80 at +0x80");
static_assert(offsetof(A1, w_0x82) == 0x82, "sub_0xbc6ee00: A1::w_0x82 at +0x82");
static_assert(offsetof(A1, w_0x84) == 0x84, "sub_0xbc6ee00: A1::w_0x84 at +0x84");
static_assert(offsetof(A1, w_0x86) == 0x86, "sub_0xbc6ee00: A1::w_0x86 at +0x86");
static_assert(offsetof(A1, w_0x88) == 0x88, "sub_0xbc6ee00: A1::w_0x88 at +0x88");
static_assert(offsetof(A1, block_0x90) == 0x90, "sub_0xbc6ee00: A1::block_0x90 at +0x90");
static_assert(offsetof(A1, shuffle_0xD0) == 0xD0, "sub_0xbc6ee00: A1::shuffle_0xD0 at +0xD0");
static_assert(offsetof(A1, d_0xD4) == 0xD4, "sub_0xbc6ee00: A1::d_0xD4 at +0xD4");

// Named offset constants used by the lifted source; each is pinned above.
constexpr std::ptrdiff_t kA0_0x1C0 = 0x1C0;
constexpr std::ptrdiff_t kA0_0x1CFD0C8 = 0x1CFD0C8;
constexpr std::ptrdiff_t kA0_0x1DDD308 = 0x1DDD308;
constexpr std::ptrdiff_t kA0_0x1DE1348 = 0x1DE1348;
constexpr std::ptrdiff_t kA0_0x1DFB48C = 0x1DFB48C;
constexpr std::ptrdiff_t kA0_0x1DE534C = 0x1DE534C;
constexpr std::ptrdiff_t kA0_0x1DFBE94 = 0x1DFBE94;
constexpr std::ptrdiff_t kA0_0x1DF145C = 0x1DF145C;
constexpr std::ptrdiff_t kA0_0x1DED458 = 0x1DED458;
constexpr std::ptrdiff_t kA0_0x1DF7478 = 0x1DF7478;
constexpr std::ptrdiff_t kA0_0x1DFB690 = 0x1DFB690;
constexpr std::ptrdiff_t kA0_0x1DE9454 = 0x1DE9454;
constexpr std::ptrdiff_t kA0_0x1DE9350 = 0x1DE9350;
constexpr std::ptrdiff_t kA0_0x1EBF1D8 = 0x1EBF1D8;
constexpr std::ptrdiff_t kR14_0xDC5808 = 0xDC5808;
constexpr std::ptrdiff_t kR14_0xE60DE0 = 0xE60DE0;
constexpr std::ptrdiff_t kR14_0xE60DE8 = 0xE60DE8;
constexpr std::ptrdiff_t kA1_0x74 = 0x74;
constexpr std::ptrdiff_t kA1_0x76 = 0x76;
constexpr std::ptrdiff_t kA1_0x78 = 0x78;
constexpr std::ptrdiff_t kA1_0x7A = 0x7A;
constexpr std::ptrdiff_t kA1_0x7C = 0x7C;
constexpr std::ptrdiff_t kA1_0x7E = 0x7E;
constexpr std::ptrdiff_t kA1_0x80 = 0x80;
constexpr std::ptrdiff_t kA1_0x82 = 0x82;
constexpr std::ptrdiff_t kA1_0x84 = 0x84;
constexpr std::ptrdiff_t kA1_0x86 = 0x86;
constexpr std::ptrdiff_t kA1_0x88 = 0x88;
constexpr std::ptrdiff_t kA1_0x90 = 0x90;
constexpr std::ptrdiff_t kA1_0xD0 = 0xD0;
constexpr std::ptrdiff_t kA1_0xD4 = 0xD4;

// Exact x64 Microsoft ABI signature of sub_0xbc6ee00:
//   void* sub_bc6ee00(uint8_t* a0, void* a1);  rcx=a0, rdx=a1, rax=a1 [V]
void* sub_bc6ee00(uint8_t* a0, void* a1);

} // namespace native::bgfx
