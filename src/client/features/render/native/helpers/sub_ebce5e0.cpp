// LIFT 0xebce5e0 size 0x8 1.26.62.01 sub_ebce5e0
#include "sub_ebce5e0.h"
#include "client/features/render/native/Lift.h"

#if 0
// Verbatim instructions from the exe, full logical body of sub_ebce5e0 [0xebce5e0, 0xebce601)
// (the data file records the guard portion as size 0x8):
0xebce5e0  test rcx,rcx
0xebce5e3  jne short 0xEBCE5E8
0xebce5e5  xor eax,eax
0xebce5e7  ret
0xebce5e8  mov rax,rcx
0xebce5eb  test edx,edx
0xebce5ed  jle short 0xEBCE5FE
0xebce5ef  nop
0xebce5f0  cmp byte ptr [rax],0
0xebce5f3  je short 0xEBCE5FE
0xebce5f5  inc rax
0xebce5f8  dec edx
0xebce5fa  test edx,edx
0xebce5fc  jg short 0xEBCE5F0
0xebce5fe  sub eax,ecx
0xebce600  ret
#endif

namespace native {

// Lifted body of sub_ebce5e0 (bounded C-string length / strnlen-like).
//
//   rcx = str (const char*), rdx = maxlen (std::int32_t); returns eax = length (std::int32_t).
//
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
// Citation: 0xebce5e0..0xebce5e8 (null guard), 0xebce5e8..0xebce601 (bounded-length body)
// Three exits all reach 0xebce5fe `sub eax,ecx` (return p - str) then 0xebce600 `ret`.
static_assert(sizeof(std::int32_t) == 4, "sub_ebce5e0: maxlen and length are 32-bit (edx/eax)");
std::int32_t sub_ebce5e0_lifted(const char* str, std::int32_t maxlen) {
    // 0xebce5e0..0xebce5e8
    // 0xebce5e0  test rcx,rcx
    // 0xebce5e3  jne short 0xEBCE5E8
    if (str == nullptr) {
        // 0xebce5e5  xor eax,eax
        // 0xebce5e7  ret
        return 0;                                // 0xebce5e5 xor eax,eax ; 0xebce5e7 ret
    }
    // 0xebce5e3  jne short 0xEBCE5E8 -> body below
    // 0xebce5e8  mov rax,rcx
    const char* p = str;
    // 0xebce5e8..0xebce601
    // 0xebce5eb  test edx,edx
    // 0xebce5ed  jle short 0xEBCE5FE
    if (maxlen <= 0) {
        // 0xebce5fe  sub eax,ecx   (eax = p - str = 0)
        // 0xebce600  ret
        return (std::int32_t)(p - str);          // 0xebce5fe sub eax,ecx ; 0xebce600 ret
    }
    // 0xebce5ef  nop
    for (;;) {                                   // 0xebce5f0 loop head
        // 0xebce5f0  cmp byte ptr [rax],0
        // 0xebce5f3  je short 0xEBCE5FE
        if (*p == '\0') {
            // 0xebce5fe  sub eax,ecx   (eax = p - str)
            // 0xebce600  ret
            return (std::int32_t)(p - str);      // 0xebce5fe sub eax,ecx ; 0xebce600 ret
        }
        // 0xebce5f5  inc rax
        ++p;
        // 0xebce5f8  dec edx
        --maxlen;
        // 0xebce5fa  test edx,edx
        // 0xebce5fc  jg short 0xEBCE5F0
        if (maxlen <= 0) {
            // 0xebce5fe  sub eax,ecx   (eax = p - str)
            // 0xebce600  ret
            return (std::int32_t)(p - str);      // 0xebce5fe sub eax,ecx ; 0xebce600 ret
        }
    }
} // namespace native

LIFT_FN(sub_ebce5e0, "sub_ebce5e0", 0xEBCE5E0, sub_ebce5e0_lifted, nullptr);
