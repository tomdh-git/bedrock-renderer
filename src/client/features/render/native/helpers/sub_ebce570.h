#pragma once
#include <cstdint>
#include <cstddef>

namespace native {

// sub_ebce570 (0xebce570, size 0x5c, 1.26.62.01): bounded strncmp-like compare over two
//   { char* ptr @+0x0; int32_t size @+0x8 } objects with an int32 count bound.
//   Disassembly (every instruction [0xebce570, 0xebce5cc)):
//     0xebce570  cmp [rdx+8],r8d           ; a1->size vs count
//     0xebce574  mov r11d,r8d
//     0xebce577  mov r9,[rdx]              ; a1->ptr
//     0xebce57a  mov r10d,r8d
//     0xebce57d  cmovl r11d,[rdx+8]        ; r11d = min(count, a1->size)  [signed]
//     0xebce582  cmp [rcx+8],r8d           ; a0->size vs count
//     0xebce586  mov rdx,[rcx]             ; a0->ptr (overwrites a1->ptr)
//     0xebce589  cmovl r10d,[rcx+8]        ; r10d = min(count, a0->size)  [signed]
//     0xebce58e  cmp r10d,r11d
//     0xebce591  mov eax,r10d
//     0xebce594  cmovge eax,r11d           ; eax = min(r10d,r11d) = min(a0->size,a1->size,count)
//     0xebce598  test eax,eax
//     0xebce59a  jle short 0xEBCE5C2       ; bound <= 0 -> epilogue
//     0xebce59c  nop [rax]
//   loop (0xebce5a0..0xebce5c0):
//     0xebce5a0  movzx ecx,byte ptr [r9]   ; *a1_ptr (zero-extended)
//     0xebce5a4  movzx r8d,byte ptr [rdx]  ; *a0_ptr (zero-extended)
//     0xebce5a8  cmp r8b,cl                ; compare *a0_ptr vs *a1_ptr
//     0xebce5ab  jne short 0xEBCE5CC       ; differ -> difference
//     0xebce5ad  test r8b,r8b              ; *a0_ptr == 0 ?
//     0xebce5b0  je short 0xEBCE5CC        ; null -> difference
//     0xebce5b2  test cl,cl                ; *a1_ptr == 0 ?
//     0xebce5b4  je short 0xEBCE5CC        ; null -> difference
//     0xebce5b6  inc rdx                   ; a0_ptr++
//     0xebce5b9  inc r9                    ; a1_ptr++
//     0xebce5bc  dec eax                   ; count--
//     0xebce5be  test eax,eax
//     0xebce5c0  jg short 0xEBCE5A0        ; count > 0 -> loop
//   epilogue (0xebce5c2..0xebce5cb):
//     0xebce5c2  jne short 0xEBCE5CC       ; bound was negative -> difference
//     0xebce5c4  cmp r10d,r11d             ; a0-size-min vs a1-size-min
//     0xebce5c7  jne short 0xEBCE5CC       ; sizes differed -> difference
//     0xebce5c9  xor eax,eax               ; return 0 (equal)
//     0xebce5cb  ret
//   difference (0xebce5cc..0xebce5d5):
//     0xebce5cc  movsx eax,byte ptr [rdx]  ; (signed char)*a0_ptr
//     0xebce5cf  movsx ecx,byte ptr [r9]   ; (signed char)*a1_ptr
//     0xebce5d3  sub eax,ecx               ; *a0 - *a1
//     0xebce5d5  ret
// No calls; no struct writes; reads only ptr(+0x0) and size(+0x8) of both args.
// x64 Microsoft ABI: rcx = a0, rdx = a1, r8d = count (32-bit), return eax (int32_t).

// Layout of the { ptr, size } argument object read by sub_ebce570:
//   +0x00 char*  ptr   (8 bytes, pointer)
//   +0x08 int32_t size (4 bytes)
//   +0x0C padding      (4 bytes, implicit)
struct Ebce570Str {
    const char* ptr;   // +0x00
    std::int32_t size; // +0x08
};
struct Ebce570Layout {
    static_assert(offsetof(Ebce570Str, ptr) == 0x0, "sub_ebce570: ptr field at +0x0");
    static_assert(offsetof(Ebce570Str, size) == 0x8, "sub_ebce570: size field at +0x8");
    static_assert(sizeof(Ebce570Str) == 0x10, "sub_ebce570: object size 0x10 (ptr 8 + size 4 + pad 4)");
    static_assert(sizeof(std::int32_t) == 4, "sub_ebce570: count/size fields are 32-bit");
    static_assert(sizeof(void*) == 8, "sub_ebce570: x64 ABI, pointer-sized register arguments");
};

// Zero callees (docs/data/native_functions.tsv: 0 callees in set, 0 outside). No forward
// declarations needed; the function makes no calls.

// Signature of sub_ebce570 itself (x64 Microsoft ABI, sampled at 0xbc601a2, 0xbc6021d, ...):
//   rcx = pointer to { char* ptr @0; int32_t size @8 } object a0
//   rdx = pointer to { char* ptr @0; int32_t size @8 } object a1
//   r8d = int32_t count bound
//   rax = int32_t result (0 if equal within bound, else (signed char)*a0 - (signed char)*a1)
extern "C" std::int32_t sub_ebce570(const Ebce570Str* a0, const Ebce570Str* a1, std::int32_t count);

} // namespace native
