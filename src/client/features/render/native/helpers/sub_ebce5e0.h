#pragma once
#include <cstdint>
#include <cstddef>

namespace native {

// sub_ebce5e0 (0xebce5e0, size 0x8 per docs/data/native_functions.tsv; logical extent
// [0xebce5e0, 0xebce601)). Bounded C-string length (strnlen-like): returns 0 for a null
// string, otherwise the number of non-null bytes up to maxlen.
//
// Disassembly (verbatim):
//   0xebce5e0  test rcx,rcx
//   0xebce5e3  jne short 0xEBCE5E8
//   0xebce5e5  xor eax,eax
//   0xebce5e7  ret
//   0xebce5e8  mov rax,rcx
//   0xebce5eb  test edx,edx
//   0xebce5ed  jle short 0xEBCE5FE
//   0xebce5ef  nop
//   0xebce5f0  cmp byte ptr [rax],0
//   0xebce5f3  je short 0xEBCE5FE
//   0xebce5f5  inc rax
//   0xebce5f8  dec edx
//   0xebce5fa  test edx,edx
//   0xebce5fc  jg short 0xEBCE5F0
//   0xebce5fe  sub eax,ecx
//   0xebce600  ret
//
// x64 Microsoft ABI: rcx = str (const char*), rdx = maxlen (std::int32_t), eax = length
// result (std::int32_t). It reads one byte at a time at [str + i] and writes no memory, so it
// touches no struct fields and needs no field-layout constants beyond the ABI itself.
struct SubEbce5e0Layout {
    static_assert(sizeof(char) == 1, "sub_ebce5e0: one-byte character read at [rax]");
    static_assert(sizeof(std::int32_t) == 4, "sub_ebce5e0: maxlen and length are 32-bit (edx/eax)");
    static_assert(sizeof(void*) == 8, "sub_ebce5e0: x64 ABI, pointer argument arrives in rcx");
};

// Signature of the exe's sub_ebce5e0 (declared so other lifted code can call it; the detour
// is installed by LIFT_FN in sub_ebce5e0.cpp).
extern "C" std::int32_t sub_ebce5e0(const char* str, std::int32_t maxlen);

} // namespace native
