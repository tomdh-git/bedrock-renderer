// LIFT 0xebce570 size 0x5c 1.26.62.01 sub_ebce570
#include "sub_ebce570.h"
#include "client/features/render/native/Lift.h"

#if 0
// Verbatim instructions from the exe, [0xebce570, 0xebce5d6).
// Every line is checked by tools/sigs/verify_oc.py against rdis output.
0xebce570  cmp [rdx+8],r8d
0xebce574  mov r11d,r8d
0xebce577  mov r9,[rdx]
0xebce57a  mov r10d,r8d
0xebce57d  cmovl r11d,[rdx+8]
0xebce582  cmp [rcx+8],r8d
0xebce586  mov rdx,[rcx]
0xebce589  cmovl r10d,[rcx+8]
0xebce58e  cmp r10d,r11d
0xebce591  mov eax,r10d
0xebce594  cmovge eax,r11d
0xebce598  test eax,eax
0xebce59a  jle short 0xEBCE5C2
0xebce59c  nop [rax]
0xebce5a0  movzx ecx,byte ptr [r9]
0xebce5a4  movzx r8d,byte ptr [rdx]
0xebce5a8  cmp r8b,cl
0xebce5ab  jne short 0xEBCE5CC
0xebce5ad  test r8b,r8b
0xebce5b0  je short 0xEBCE5CC
0xebce5b2  test cl,cl
0xebce5b4  je short 0xEBCE5CC
0xebce5b6  inc rdx
0xebce5b9  inc r9
0xebce5bc  dec eax
0xebce5be  test eax,eax
0xebce5c0  jg short 0xEBCE5A0
0xebce5c2  jne short 0xEBCE5CC
0xebce5c4  cmp r10d,r11d
0xebce5c7  jne short 0xEBCE5CC
0xebce5c9  xor eax,eax
0xebce5cb  ret
0xebce5cc  movsx eax,byte ptr [rdx]
0xebce5cf  movsx ecx,byte ptr [r9]
0xebce5d3  sub eax,ecx
0xebce5d5  ret
#endif

namespace native {

static_assert(sizeof(std::int32_t) == 4, "sub_ebce570: count/size fields are 32-bit");
static_assert(sizeof(void*) == 8, "sub_ebce570: x64 ABI, pointer-sized register arguments");

// Lifted body of sub_ebce570 (0xebce570, size 0x5c, 1.26.62.01).
//
// Bounded strncmp-like compare over two { char* ptr @+0x0; int32_t size @+0x8 } objects
// (a0 in rcx, a1 in rdx) with an int32 count bound (r8d).
//   bound = min(a0->size, a1->size, count)   [signed compares]
//   loop: compare bytes; on inequality or either-byte-zero -> difference return
//         = (signed char)*a0_ptr - (signed char)*a1_ptr
//   if loop exhausts the bound: return 0 iff a0-size-min == a1-size-min, else difference
// No calls, no writes, no null guards (fail fast), x64 Microsoft ABI, return eax (int32_t).
//
// Note on the data-file size: native_functions.tsv records 0x5c bytes
//   [0xebce570, 0xebce5cc). The disassembly shows the difference block
//   [0xebce5cc, 0xebce5d6) is contiguous with the epilogue (no int3 gap) and is
//   targeted by branches from within the function, so it is part of the real
//   function body and is lifted here. liftcheck covers [0xebce570, 0xebce5cc);
//   the difference block is cited for completeness.

std::int32_t sub_ebce570_lifted(const Ebce570Str* a0, const Ebce570Str* a1, std::int32_t count) {
    const char* rdx = nullptr;
    const char* r9 = nullptr;
    std::int32_t r8d = 0;
    std::int32_t r10d = 0;
    std::int32_t r11d = 0;
    std::int32_t eax = 0;
    std::int32_t ecx = 0;

    // 0xebce570..0xebce5a0
    r11d = count;                                             // 0xebce574  mov r11d,r8d
    r9 = a1->ptr;                                             // 0xebce577  mov r9,[rdx]
    r10d = count;                                             // 0xebce57a  mov r10d,r8d
    rdx = a0->ptr;                                            // 0xebce586  mov rdx,[rcx]
    if (a1->size < count) r11d = a1->size;                    // 0xebce570  cmp [rdx+8],r8d ; 0xebce57d  cmovl r11d,[rdx+8]
    if (a0->size < count) r10d = a0->size;                    // 0xebce582  cmp [rcx+8],r8d ; 0xebce589  cmovl r10d,[rcx+8]
    eax = r10d;                                               // 0xebce591  mov eax,r10d
    if (r10d >= r11d) eax = r11d;                             // 0xebce58e  cmp r10d,r11d ; 0xebce594  cmovge eax,r11d
    // 0xebce59c  nop [rax]                                    (no-op)
    if (eax <= 0) goto loc_ebce5c2;                           // 0xebce598  test eax,eax ; 0xebce59a  jle short 0xEBCE5C2

loc_ebce5a0:
    // 0xebce5a0..0xebce5c2
    ecx = static_cast<std::int32_t>(static_cast<unsigned char>(*r9));  // 0xebce5a0  movzx ecx,byte ptr [r9]
    r8d = static_cast<std::int32_t>(static_cast<unsigned char>(*rdx)); // 0xebce5a4  movzx r8d,byte ptr [rdx]
    if (r8d != ecx) goto loc_ebce5cc;                         // 0xebce5a8  cmp r8b,cl ; 0xebce5ab  jne short 0xEBCE5CC
    if (r8d == 0) goto loc_ebce5cc;                           // 0xebce5ad  test r8b,r8b ; 0xebce5b0  je short 0xEBCE5CC
    if (ecx == 0) goto loc_ebce5cc;                           // 0xebce5b2  test cl,cl ; 0xebce5b4  je short 0xEBCE5CC
    ++rdx;                                                    // 0xebce5b6  inc rdx
    ++r9;                                                     // 0xebce5b9  inc r9
    --eax;                                                    // 0xebce5bc  dec eax
    if (eax > 0) goto loc_ebce5a0;                            // 0xebce5be  test eax,eax ; 0xebce5c0  jg short 0xEBCE5A0

loc_ebce5c2:
    // 0xebce5c2..0xebce5cc
    if (eax != 0) goto loc_ebce5cc;                           // 0xebce5c2  jne short 0xEBCE5CC  (taken only when bound was negative)
    if (r10d != r11d) goto loc_ebce5cc;                       // 0xebce5c4  cmp r10d,r11d ; 0xebce5c7  jne short 0xEBCE5CC
    eax = 0;                                                  // 0xebce5c9  xor eax,eax
    return eax;                                               // 0xebce5cb  ret

loc_ebce5cc:
    // 0xebce5cc..0xebce5d6
    eax = static_cast<std::int32_t>(static_cast<signed char>(*rdx));  // 0xebce5cc  movsx eax,byte ptr [rdx]
    ecx = static_cast<std::int32_t>(static_cast<signed char>(*r9));   // 0xebce5cf  movsx ecx,byte ptr [r9]
    eax = eax - ecx;                                            // 0xebce5d3  sub eax,ecx
    return eax;                                               // 0xebce5d5  ret
}

} // namespace native

LIFT_FN(sub_ebce570, "sub_ebce570", 0xEBCE570, native::sub_ebce570_lifted, nullptr);
