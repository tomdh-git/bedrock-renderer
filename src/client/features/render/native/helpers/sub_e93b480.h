#pragma once
#include <cstdint>

// sub_e93b480 (0xe93b480, size 0x6, 1.26.62.01): the whole function is one
// instruction, followed by one padding byte inside the 6-byte span:
//
//   0xe93b480  jmp 0xE93B490   ; -> loc_e93b490      (0xe93b480..0xe93b485)
//   0xe93b485  int3             (0xe93b485..0xe93b486)
//
// It forwards its three register arguments unchanged to sub_e93b490 and returns
// sub_e93b490's result in RAX. It reads no struct fields and writes no memory,
// so there are no struct layout constants beyond the x64 ABI itself:
struct SubE93b480Layout {
    static_assert(sizeof(void*) == 8, "sub_e93b480: x64 ABI, pointer-sized register arguments and return");
    static_assert(sizeof(wchar_t) == 2, "sub_e93b480: searched character is a 16-bit wchar_t passed in R8");
};
static_assert(sizeof(SubE93b480Layout) > 0, "sub_e93b480: layout constant block");

namespace native {

// sub_e93b490 (0xe93b490): tail-jump target of sub_e93b480. It is not classified
// in docs/data/native_functions.tsv nor in docs/data/native_boundary.tsv, so the
// call from the lifted body of sub_e93b480 is tracked in the unit progress file
// (docs/progress/oc_U-EX7.e93b480.md).
// ABI recovered from its disassembly (identical to sub_e93b480, no register shuffling):
//   0xe93b490  mov eax,[0x1230A11C]   ; CPU feature global
//   0xe93b496  mov r9,rdx   /  sub r9,rcx     ; r9 = last - first (byte count)
//   0xe93b49c  mov r10,rdx                         ; r10 = last (end pointer)
//   ... searches [first, last) for (wchar_t)ch, returns pointer to first match or last (RAX)
extern "C" wchar_t* sub_e93b490(wchar_t* first, wchar_t* last, wchar_t ch);

// sub_e93b480 (0xe93b480): identical ABI to sub_e93b490 (tail forwarder, no register shuffling).
//   rcx = first (wchar_t*), rdx = last (wchar_t*), r8 = ch (wchar_t); rax = result pointer
wchar_t* sub_e93b480(wchar_t* first, wchar_t* last, wchar_t ch);

} // namespace native
