#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// sub_aa3c0 (0xaa3c0, size 0x8, Minecraft Windows 1.26.62.01).
//   0xaa3c0  lea rax,[0x128C1588]            ; [data_128c1588]
//   0xaa3c7  ret
// Takes no arguments; returns the address of the game global data_128c1588
// (the address loaded by the lea, RVA 0x128C1588) in RAX. Reads no memory,
// writes no memory, makes no calls [V: rdis dis/sum 0xaa3c0; calls empty,
// accesses empty, returns {ip 0xaa3c7, rax &data_128c1588}].
// The pointee type of data_128c1588 is not recoverable from this function
// alone (exactly one .text reference to 0x128C1588 exists, the lea at
// 0xaa3c3 itself [V]); callers of sub_aa3c0 determine the pointee type [I].
// No layout constants exist for this function: it touches no struct fields
// and no object fields of its own [V]. The static_assert below pins the x64
// ABI assumption (pointer-sized return in RAX).
static_assert(sizeof(void*) == 8, "sub_aa3c0: return value is an 8-byte pointer in RAX (x64 Microsoft ABI)");

void* sub_aa3c0(void);

} // namespace native
