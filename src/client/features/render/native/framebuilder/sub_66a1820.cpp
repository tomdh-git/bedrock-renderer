// LIFT 0x66a1820 size 0x36 1.26.62.01 sub_66a1820
#include "client/features/render/native/framebuilder/sub_66a1820.h"
#include "client/features/render/native/Lift.h"

#include <cstdint>

namespace native {

// sub_66a1820 (0x66a1820, size 0x36, 1.26.62.01, "Item group visitor").
//
// Reads a 2-qword pair from *a1 and copies it to *a0:
//   0x66a1824  mov rax,[rdx]           ; rax = a1+0x0
//   0x66a1827  cmp rax,0xFFFFFFFFFFFFFFFF
//   0x66a182b  je short 0x66A1850      ; fail if a1+0x0 == -1 (nothing written)
//   0x66a182d  mov rdx,[rdx+8]         ; rdx = a1+0x8
//   0x66a1831  mov [rcx],rax           ; a0+0x0 = rax
//   0x66a1834  mov [rcx+8],rdx         ; a0+0x8 = rdx
//   0x66a1838  test rdx,rdx
//   0x66a183b  setne dl                ; dl = (a1+0x8 != 0)
//   0x66a183e  test rax,rax
//   0x66a1841  sete al                 ; al = (a1+0x0 == 0)
//   0x66a1844  or al,dl                ; al = (a1+0x0 == 0) || (a1+0x8 != 0)
//   0x66a1846  je short 0x66a1850      ; fail if a1+0x0 != 0 && a1+0x8 == 0
//   0x66a1848  mov rax,rcx             ; return a0
// Failure path (0x66a1850..0x66a1856):
//   0x66a1850  call 0x78ED0            ; sub_78ed0, class crt boundary, noreturn; RCX = a0
//   0x66a1855  int3                    ; unreachable
//
// Same reads, same writes, same calls in the same order, same return. No null guard or SEH
// (the original has none; none added here). [V] every instruction line above, from the exe
// disassembly of [0x66a1820, 0x66a1856).

// Boundary callee, class crt (docs/data/native_boundary.tsv line 11).
// 0x78ed0 itself: `sub rsp,0x28 / call qword ptr [0xF9A8CF0]` then int3 padding; noreturn,
// never reaches a ret [V]. Called with RCX = a0, exactly as the original has it at both call
// sites (rcx is untouched between entry and either call) [V]. Same wrapper precedent as
// sub_bc5e120/sub_bc5e120 (0xbc5e1d6 call 0x78ED0 with rcx = 0).
native::Boundary<void, std::uintptr_t> sub_78ed0("sub_78ed0");

// 0x66a1820..0x66a182d: sub rsp,0x28; mov rax,[rdx]; cmp rax,-1; je short 0x66a1850
uint64_t* sub_66a1820(uint64_t* a0, uint64_t* a1) {
    const std::uint64_t v0 = a1[0];                        // 0x66a1824 mov rax,[rdx] ; R a1+0x0
    if (v0 != 0xFFFFFFFFFFFFFFFFULL) {                     // 0x66a1827 cmp rax,0xFFFFFFFFFFFFFFFF ; 0x66a182b je short 0x66a1850 (taken -> fail)
        // 0x66a182d..0x66a1838: mov rdx,[rdx+8]; mov [rcx],rax; mov [rcx+8],rdx
        const std::uint64_t v1 = a1[1];                    // 0x66a182d mov rdx,[rdx+8] ; R a1+0x8
        a0[0] = v0;                                        // 0x66a1831 mov [rcx],rax ; W a0+0x0
        a0[1] = v1;                                        // 0x66a1834 mov [rcx+8],rdx ; W a0+0x8
        // 0x66a1838..0x66a1848: test rdx,rdx / setne dl / test rax,rax / sete al / or al,dl / je short 0x66a1850 ; mov rax,rcx
        if (v1 != 0 || v0 == 0) return a0;                 // 0x66a1838..0x66a1846 test/setne/sete/or/je (not taken -> return a0) ; 0x66a1848 mov rax,rcx
    }
fail:                                                      // 0x66a1850..0x66a1856
    // 0x66a1850  call 0x78ED0   ; sub_78ed0 (crt boundary, noreturn); RCX = a0
    sub_78ed0(reinterpret_cast<std::uintptr_t>(a0));       // 0x66a1850  call 0x78ED0
    // 0x66a1855  int3           ; unreachable: sub_78ed0 never returns (thunk ends in int3 padding)
    return a0;                                             // unreachable: the original breaks into int3 at 0x66a1855
}

// Verbatim instructions of the function (matches `rdis dis 0x66a1820 0x36` from the exe,
// machine-checked with tools/sigs/verify_oc.py):
#if 0
0x66a1820  sub rsp,0x28
0x66a1824  mov rax,[rdx]
0x66a1827  cmp rax,0xFFFFFFFFFFFFFFFF
0x66a182b  je short 0x66A1850
0x66a182d  mov rdx,[rdx+8]
0x66a1831  mov [rcx],rax
0x66a1834  mov [rcx+8],rdx
0x66a1838  test rdx,rdx
0x66a183b  setne dl
0x66a183e  test rax,rax
0x66a1841  sete al
0x66a1844  or al,dl
0x66a1846  je short 0x66a1850
0x66a1848  mov rax,rcx
0x66a184b  add rsp,0x28
0x66a184f  ret
0x66a1850  call 0x78ED0
0x66a1855  int3
#endif

static native::Footprint sub_66a1820Footprint(uint64_t* a0, uint64_t* /*a1*/) {
    return {{a0, 0x10}}; // every byte the function writes: a0+0x0 and a0+0x8 [V]
}

LIFT_FN(sub_66a1820, "sub_66a1820", 0x66a1820, sub_66a1820, sub_66a1820Footprint);

} // namespace native
